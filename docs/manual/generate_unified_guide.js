/**
 * SRM MX 통합코드백과 — 책형 구조 (큰 개념 → 작은 개념)
 * 길이 제한 없음. 모든 rx/Store/Save/RunMode/파라미터 함수 소스 포함.
 */
const fs = require("fs");
const path = require("path");
const { execSync } = require("child_process");
const lg = require("./generate_learning_guide.js");

const OUT = lg.OUT;
const TODAY = lg.TODAY;
const TODAY_DISP = lg.TODAY_DISP;
const {
  read,
  esc,
  countLines,
  extractFunctionBody,
  parseEnumBlock,
  parseRunSeq,
  extractRunCases,
  extractTmlHandlers,
  extractSaveFunctions,
  extractStoreFunctions,
  buildThreeLayersDeep,
  buildRxCmdOrderDeep,
  buildStartOnDeep,
  buildMainLoopDeep,
  buildPrepareMoveDeep,
  buildLoadingFlowTable,
  buildPutFlowTable,
  buildAllRunCaseIndex,
  buildForkStepTable,
  buildFileTable,
  buildStructEight,
  RUN_GROUPS,
  PATTERNS,
  TRAPS,
} = lg;

const ECAT_MAIN = path.join(lg.SRC, "ecat_main.c");
const PARAM = path.join(lg.SRC, "SRM_Parameter.c");
const DEV_HDR = path.join(lg.INC, "dev_SRM.h");
const USER_DEF = path.join(lg.INC, "User_Define.h");
const UNIFIED_PREFIX = "SRM_MX_통합코드백과";

function getRevisionInfo() {
  const re = new RegExp(`^${UNIFIED_PREFIX}_(\\d{8})_REV(\\d+)\\.html$`);
  const prev = [];
  for (const f of fs.readdirSync(OUT)) {
    const m = f.match(re);
    if (m && m[1] === TODAY) prev.push({ file: f, rev: parseInt(m[2], 10) });
  }
  prev.sort((a, b) => a.rev - b.rev);
  return { rev: prev.length ? Math.max(...prev.map((p) => p.rev)) + 1 : 0, previous: prev };
}

function extractHtmlBody(htmlPath) {
  const html = read(htmlPath);
  const m = html.match(/<body[^>]*>([\s\S]*)<\/body>/i);
  if (!m) return "";
  return m[1]
    .replace(/<div class="layout">[\s\S]*?<nav class="sidebar">[\s\S]*?<\/nav>/i, "")
    .replace(/<\/main><\/div>/i, "")
    .replace(/^<main>/i, "")
    .replace(/<script[\s\S]*?<\/script>/gi, "");
}

function fnBlock(source, name, label) {
  const body = extractFunctionBody(source, name, 0);
  return `<details class="fn-item" id="fn_${name}"><summary class="mono">${esc(name)}()</summary>
<p>${esc(label || "")}</p><pre class="code-sm">${esc(body)}</pre></details>`;
}

function extractRxFunctionNames(text) {
  const names = [];
  for (const line of text.split("\n")) {
    const m = line.match(/^void\s+(rx\w+)\s*\(/);
    if (m) names.push(m[1]);
  }
  return names;
}

function extractCFunctions(text, prefix = "") {
  const fns = [];
  for (const line of text.split("\n")) {
    const m = line.match(new RegExp(`^(?:static\\s+)?(?:void|INT\\w+U?)\\s+(${prefix}\\w+)\\s*\\(`));
    if (m) fns.push(m[1]);
  }
  return [...new Set(fns)];
}

const TML_CATEGORIES = [
  {
    id: "tml-cat-status",
    title: "9.1 상태·제어·모드",
    match: /Status|Control|Mode|Operation|Device|Func|Test|Graph|ManualOut|Digital_IO|Demo|DataAnalysis/,
  },
  {
    id: "tml-cat-work",
    title: "9.2 작업 명령 (자동운전 핵심)",
    match: /CmdOrder|CmdStart|CmdReference|Cmd_Move|CmdMove|CmdError|CmdOrderDelete|CmdNormal|CmdEmergency|CmdManual|TaskCmd/,
  },
  {
    id: "tml-cat-env",
    title: "9.3 Setup 환경 (랙·셀·스테이션·금지랙)",
    match: /RackEnv|CellEnv|StationEnv|ProhibitRack|SpecialRack|RackEnvInitialize|Cell_Offset/,
  },
  {
    id: "tml-cat-drive",
    title: "9.4 드라이브 파라미터 (주행·승강·포크)",
    match: /TravelDrive|LiftDrive|Fork_Drive|ControlParamter|InvertorParameter/,
  },
  {
    id: "tml-cat-scan",
    title: "9.5 센서 스캔·시험",
    match: /Scan_Position|Machine_Type|McuTest|DSP_|AlarmLog|InvertorInfo/,
  },
];

function categorizeRx(fn) {
  for (const c of TML_CATEGORIES) {
    if (c.match.test(fn)) return c.id;
  }
  return "tml-cat-misc";
}

function buildRevBanner(revInfo) {
  const prevLinks =
    revInfo.previous.length > 0
      ? `<p>이전 개정: ${revInfo.previous.map((p) => `<a href="${esc(p.file)}">REV${p.rev}</a>`).join(" · ")}</p>`
      : "";
  return `<div class="rev-banner" id="rev-info">
  <span class="rev-tag">REV${revInfo.rev}</span> ${TODAY_DISP}
  <span class="rev-latest">★ 당일 최신 개정본</span>
  ${prevLinks}
</div>`;
}

function buildBookNav() {
  return `
<div class="part">제0권 · 서문</div>
<a href="#intro">0.1 이 책 읽는 법</a>
<a href="#big-picture">0.2 SRM 전체 그림</a>
<a href="#files">0.3 파일 지도</a>
<div class="part">제1권 · 실행 골격</div>
<a href="#mainloop">1.1 main 루프</a>
<a href="#managers">1.2 Manager 체계</a>
<div class="part">제2권 · 데이터</div>
<a href="#layers">2.1 데이터 3층</a>
<a href="#struct8">2.2 8대 구조체</a>
<div class="part">제3권 · 상태머신 개론</div>
<a href="#runmode-enum">3.1 RunMode enum</a>
<a href="#statemachine-intro">3.2 상태머신 역할</a>
<div class="part">제4권 · TML 통신</div>
<a href="#tml-overview">4.1 TML 개요</a>
<a href="#tml-core">4.2 0x30·0x41·0x50</a>
<a href="#tml-all-src">4.3 TML 핸들러 전체</a>
<div class="part">제5권 · Store/Save</div>
<a href="#store-all">5.1 Store_* 전체</a>
<a href="#save-all">5.2 Save_* 전체</a>
<div class="part">제6권 · 모터·PDO</div>
<a href="#pdo-overview">6.1 PDO 위치</a>
<a href="#pdo-store">6.2 Store_SRM_RxPDO*</a>
<a href="#ecat-mgr">6.3 ECAT_Manager</a>
<a href="#axis-auto">6.4 Auto_Ctr_*</a>
<a href="#axis-manual">6.5 수동·CREEP</a>
<div class="part">제7권 · 자동운전</div>
<a href="#get-flow-table">7.1 GET</a>
<a href="#put-flow">7.2 PUT</a>
<a href="#prepare-deep">7.3 PREPARE</a>
<a href="#fork-steps">7.4 스텝코드</a>
<a href="#runmode-all">7.5 RunMode 전체</a>
<div class="part">제8권 · Setup·티칭</div>
<a href="#setup-overview">8.1 Setup 개요</a>
<a href="#setup-tml">8.2 환경설정 TML</a>
<a href="#rack-logic">8.3 랙/셀 저장</a>
<a href="#ref-pos">8.4 Reference Position</a>
<a href="#scan-autoteach">8.5 스캔·오토티칭</a>
<div class="part">제9권 · Flash 파라미터</div>
<a href="#param-all">9.1 SRM_Parameter.c</a>
<div class="part">부록</div>
<a href="#patterns">A. 패턴</a>
<a href="#traps">B. 함정</a>
<a href="#symbol-dict">C. 심볼 사전</a>
<a href="#struct-tree-embed">D. 구조체 트리</a>
<a href="#source-full">E. Core/Src 전체 소스</a>`;
}

function buildVol0(revInfo, meta) {
  return `
${buildRevBanner(revInfo)}
<h1>MX SRM 펌웨어 통합코드백과 <small>REV${revInfo.rev}</small></h1>
<div class="meta" id="intro">
<h3>0.1 이 책 읽는 법</h3>
<p><b>큰 개념 → 작은 개념</b> 순서입니다. PDO·수동·랙티칭은 각각 해당 장(6권·8권)에서 다룹니다.</p>
<ul>
<li><b>제0~2권</b>: 설비·main·데이터 — "무엇이 어디에 있는가"</li>
<li><b>제3~5권</b>: 상태머신·TML·Store/Save — "명령이 어떻게 들어와 저장되는가"</li>
<li><b>제6권</b>: PDO/EtherCAT — "모터가 실제로 움직이는 계층"</li>
<li><b>제7권</b>: GET/PUT RunMode — "자동운전 시퀀스"</li>
<li><b>제8~9권</b>: Setup·Flash 파라미터</li>
<li><b>부록</b>: 심볼 ${meta.symbolItems || "7700+"}항목 내장</li>
</ul>
<p>소스는 <b>생략 없이</b> 함수 단위로 펼칩니다. RunMode ${meta.runCases}개 · TML ${meta.tmlHandlers}개 · Store ${meta.stores} · Save ${meta.saves}</p>
</div>

<h2 id="big-picture">0.2 SRM 전체 그림 (지상반 → MCU → 인버터)</h2>
<div class="mermaid-wrap"><pre class="mermaid">
flowchart TB
  subgraph WCS["지상반"]
    O41["0x41 작업명령"]
    S50["0x50 Start"]
    P30["0x30 상태"]
    SET["Setup: Cell/Rack/Station"]
  end
  subgraph MCU["STM32 while(1)"]
    TML["TMLComManager"]
    ECAT["ECAT_Manager"]
    SRM["SRM_Manager\\nRunMode switch"]
    ALM["AlarmManager\\nSave_*"]
  end
  subgraph MEM["메모리"]
    WD["m_WorkData"]
    RM["SRM_RunMode"]
    ST["m_St"]
    FL["ExtFlash"]
  end
  subgraph MOT["EtherCAT"]
    PDO["RxPDO 큐 → 인버터"]
    FB["TxPDO 피드백"]
  end
  O41 --> TML --> WD
  S50 --> RM
  SET --> TML --> FL
  WD --> SRM --> RM
  SRM --> PDO --> FB --> ST
  ECAT --> PDO
  SRM --> ALM --> ST --> P30
</pre></div>

${buildFileTable()}
`;
}

function buildVol1(mainText) {
  const loop = mainText.split("\n").slice(818, 866).join("\n");
  return `
<h2 id="mainloop">제1권 · 1.1 main.c — 부팅 후 무한 루프</h2>
${buildMainLoopDeep()}
<h3>1.1.1 while(1) 원본</h3>
<pre class="code-sm">${esc(loop)}</pre>

<h2 id="managers">1.2 Manager 호출 순서 (한 사이클)</h2>
<table class="data-table">
<tr><th>순서</th><th>함수</th><th>파일</th><th>역할</th></tr>
<tr><td>1</td><td class="mono">AlarmManager</td><td>alarm.c</td><td>DI/DO, 에러 latch, Save_* 트리거</td></tr>
<tr><td>2</td><td class="mono">FpgaManager</td><td>fpga</td><td>FPGA·EtherCAT PHY</td></tr>
<tr><td>3</td><td class="mono">TMLComManager</td><td>com_tml.c</td><td>지상반 UART 수신→rx* 디스패치</td></tr>
<tr><td>4</td><td class="mono">ECAT_Manager</td><td>ecat_main.c</td><td>PDO 송수신·슬레이브 상태</td></tr>
<tr><td>5</td><td class="mono">SRM_Manager</td><td>dev_SRM.c</td><td>RunMode 상태머신·축제어</td></tr>
</table>
<p><code>timer1ms</code>는 SysTick ISR에서 증가. RunMode 타이머·타임아웃은 모두 이 기준.</p>
`;
}

function buildVol2() {
  return `
<h2 id="layers">제2권 · 2.1 데이터 3층 (입력·실행·출력)</h2>
${buildThreeLayersDeep()}
<h2 id="struct8">2.2 핵심 8대 구조체</h2>
${buildStructEight()}
`;
}

function buildVol3(devText, devHdrText, runSeq) {
  let enumTable = `<table class="data-table"><tr><th>RunMode</th><th>값</th><th>주석</th></tr>`;
  for (const r of runSeq) {
    enumTable += `<tr><td class="mono">${esc(r.name)}</td><td>${esc(r.val || "—")}</td><td>${esc(r.comment || "")}</td></tr>`;
  }
  enumTable += `</table>`;

  return `
<h2 id="runmode-enum">제3권 · 3.1 enumSRM_RUN_SEQ 전체 (${runSeq.length}항목)</h2>
${enumTable}

<h2 id="statemachine-intro">3.2 상태머신 — SRM_Manager → SRM_Machine_Run_Process</h2>
<div class="note">RunMode는 <code>m_pgmEnv.SRM_RunMode</code> 하나로 전체 자동·Setup·원점·에러 시퀀스를 표현합니다.
매 루프 <code>switch(SRM_RunMode)</code> 한 case만 실행 후 break. <b>모든 case 소스는 제7권 7.5절</b>에 전부 수록.</div>
<h3>3.2.1 SRM_Manager — 전체</h3>
<pre class="code-sm">${esc(extractFunctionBody(devText, "SRM_Manager", 0))}</pre>
<p><code>SRM_Machine_Run_Process()</code> 내부의 거대한 switch 본문은 제7권 RunMode ${runSeq.length}항목과 1:1 대응합니다.</p>
`;
}

function buildVol4TmlOverview(handlers) {
  let table = `<table class="data-table"><tr><th>TY_*</th><th>rx 함수</th></tr>`;
  for (const h of handlers) {
    table += `<tr><td class="mono">${esc(h.ty)}</td><td class="mono">${esc(h.fn)}</td></tr>`;
  }
  return `
<h2 id="tml-overview">제4권 · 4.1 TML 통신 개요</h2>
<p>프레임: STX → Header(Cmd/Cmd2/Len) → Data → CRC → ETX. <code>TMLComManager</code> 수신 후 <code>Header.Cmd</code> 로 switch.</p>
<h3>4.1.1 TY_* ↔ rx 함수 매핑 (${handlers.length}개)</h3>
${table}
`;
}

function buildVol4TmlCore(tmlText) {
  return `
<h2 id="tml-core">4.2 핵심 명령 — 0x30 / 0x41 / 0x50</h2>
${buildRxCmdOrderDeep()}
${buildStartOnDeep()}
<h3>4.2.1 rxStatusReq (0x30) — 전체</h3>
${fnBlock(tmlText, "rxStatusReq", "m_St 전체 또는 일부를 지상반에 응답")}
`;
}

function buildVol4TmlAllSource(tmlText, handlers) {
  const rxNames = extractRxFunctionNames(tmlText);
  const byCat = {};
  for (const c of TML_CATEGORIES) byCat[c.id] = [];
  byCat["tml-cat-misc"] = [];
  for (const fn of rxNames) {
    byCat[categorizeRx(fn)].push(fn);
  }

  let html = `<h2 id="tml-all-src">4.3 com_tml.c rx* 핸들러 전체 소스 (${rxNames.length}함수)</h2>
<div class="warn">각 함수 클릭 시 <b>전체 소스</b> (생략 없음).</div>`;

  for (const cat of [...TML_CATEGORIES, { id: "tml-cat-misc", title: "9.6 기타" }]) {
    const fns = byCat[cat.id] || [];
    if (!fns.length) continue;
    html += `<h3 id="${cat.id}">${esc(cat.title)} (${fns.length})</h3>`;
    for (const fn of fns) {
      const h = handlers.find((x) => x.fn === fn);
      html += fnBlock(tmlText, fn, h ? `${h.ty}` : "");
    }
  }
  return html;
}

function buildVol5StoreSave(devText, alarmText, stores, saves) {
  let html = `<h2 id="store-all">제5권 · 5.1 Store_* — 입력·큐 (dev_SRM.c, ${stores.length}개)</h2>
<p>0x41 수신·RunMode 진입 시 <code>m_WorkData</code>·PDO 큐에 레시피 적재.</p>`;
  for (const s of stores) {
    html += fnBlock(devText, s.name, `L${s.line}`);
  }

  html += `<h2 id="save-all">5.2 Save_* — 출력·보고 (alarm.c, ${saves.length}개)</h2>
<p>RunMode 진행 중 <code>m_St</code>·BKPSRAM 갱신 → 0x30 폴링으로 지상반 전달.</p>`;
  for (const fn of saves) {
    html += fnBlock(alarmText, fn, "→ m_St / m_BKSram");
  }
  return html;
}

function buildVol6Pdo(devText, ecatText, mainText, devHdrText, userDef, tmlText) {
  const invAxes = [];
  for (const line of devHdrText.split("\n")) {
    const m = line.match(/#define\s+(INV_\w+)\s+(\d+)/);
    if (m) invAxes.push(m);
  }

  const storeFns = extractCFunctions(devText, "Store_SRM_RxPDO");
  const autoFns = ["Auto_Ctr_Travel", "Auto_Ctr_Lift", "Auto_Ctr_Fork", "Auto_Ctr_Fork_1", "Auto_Ctr_Fork_2"].filter(
    (f) => devText.includes(`${f}(`)
  );

  let html = `
<h2 id="pdo-overview">제6권 · 6.1 PDO — RunMode와 인버터 사이</h2>
<div class="note">상태머신(7권)이 "목표 위치·속도"를 정하면, 6권 Store_SRM_RxPDO* 가 EtherCAT RxPDO 큐에 넣고,
<code>ECAT_Manager</code>가 인버터와 교환합니다. 피드백은 <code>m_St.Inv_St[]</code>.</div>
<h3>6.1.1 main 루프 내 위치</h3>
<pre class="code-sm">${esc(mainText.split("\n").slice(818, 866).join("\n"))}</pre>

<h3>6.1.2 INV 축 인덱스</h3>
<table class="data-table"><tr><th>#define</th><th>값</th></tr>`;
  for (const m of invAxes) {
    html += `<tr><td class="mono">${esc(m[1])}</td><td>${esc(m[2])}</td></tr>`;
  }
  html += `</table>`;

  html += `<h2 id="pdo-store">6.2 Store_SRM_RxPDO* 전체 (${storeFns.length}개)</h2>`;
  for (const fn of storeFns) {
    html += fnBlock(devText, fn, "MCU→인버터 RxPDO 큐 적재");
  }

  html += `<h2 id="ecat-mgr">6.3 ECAT_Manager — 전체</h2>`;
  html += fnBlock(ecatText, "ECAT_Manager", "슬레이브 검출·OP·PDO cycle");

  html += `<h2 id="axis-auto">6.4 Auto_Ctr_* — 자동 축제어</h2>`;
  for (const fn of autoFns) {
    html += fnBlock(devText, fn, "RunMode에서 호출되는 자동 이동");
  }

  html += buildVol6Manual(devText, tmlText, devHdrText, userDef);
  return html;
}

function buildVol6Manual(devText, tmlText, devHdrText, userDef) {
  const trav = parseEnumBlock(devHdrText, "enumMANUAL_TRAV_CTR");
  const lift = parseEnumBlock(devHdrText, "enumMANUAL_LIFT_CTR");
  const fork = parseEnumBlock(devHdrText, "enumMANUAL_CTR_FORK_DIR");
  const velTypes = [];
  for (const en of ["enumTRAV_VELOCITY_TYPE", "enumLIFT_VELOCITY_TYPE", "enumFORK_VELOCITY_TYPE"]) {
    velTypes.push(...parseEnumBlock(userDef, en));
  }

  let html = `<h2 id="axis-manual">6.5 수동 조작 · CREEP 속도</h2>
<p>수동은 TML <code>TY_CMD_MANUAL</code>(4권) → <code>Control_Manual_*</code> → 6권 PDO 경로.</p>
<h3>6.5.1 rxCmdManual — 전체</h3>
${fnBlock(tmlText, "rxCmdManual", "0x80 수동 명렘")}
<h3>6.5.2 Control_Manual_Trav_Start</h3>
${fnBlock(devText, "Control_Manual_Trav_Start", "")}
<h3>6.5.3 Control_Manual_Lift_Start</h3>
${fnBlock(devText, "Control_Manual_Lift_Start", "")}
<h3>6.5.4 Control_Manual_Fork_Start</h3>
${fnBlock(devText, "Control_Manual_Fork_Start", "")}
<h3>6.5.5 MANUAL_CTR_Fork</h3>
${fnBlock(devText, "MANUAL_CTR_Fork", "")}

<h3>6.5.6 속도 enum (CREEP 포함)</h3>
<table class="data-table"><tr><th>이름</th><th>값</th></tr>`;
  for (const e of velTypes) {
    html += `<tr><td class="mono">${esc(e.name)}</td><td>${esc(e.val || "—")}</td></tr>`;
  }
  html += `</table>`;
  html += `<p><b>CREEP</b> = 저속 정밀 접근. 자동 포크·오토티칭 감속 구간에서 <code>FORK_VEL_CREEP</code> 등 사용.</p>`;
  return html;
}

function buildVol7Auto(runCases, devText, runSeq, forkSteps, workStatus) {
  return `
<h2 id="get-flow-table">제7권 · 7.1 GET(적재) 단계</h2>
${buildLoadingFlowTable()}
<h2 id="put-flow">7.2 PUT(이재) 단계</h2>
${buildPutFlowTable()}
<h2 id="prepare-deep">7.3 PREPARE_MOVE · 브레이크</h2>
${buildPrepareMoveDeep()}
<h2 id="fork-steps">7.4 지상반 스텝 (OrderProcess)</h2>
${buildForkStepTable(forkSteps, workStatus)}
<h2 id="runmode-all">7.5 RunMode case 전체 (${runCases.length}개 — 소스 생략 없음)</h2>
${buildAllRunCaseIndex(runCases, devText, runSeq)}
`;
}

function buildVol8Setup(tmlText, paramText, devText) {
  const envFns = extractRxFunctionNames(tmlText).filter((f) =>
    /RackEnv|CellEnv|StationEnv|ProhibitRack|SpecialRack|Cell_Offset|Scan_Position|RackEnvInitialize/.test(f)
  );
  const paramEnvFns = [
    "Set_Rack_Config",
    "Set_Cell_Config",
    "Set_Cell_Config_1",
    "Set_Station_Config",
    "Set_ProhibitRack_Config",
    "Set_SpecialRack_Config",
    "Clear_Rack_Config",
    "Clear_Cell_Config",
    "Rack_Config_Init",
    "Cell_Config_Init",
    "Station_Config_Init",
  ];

  let html = `
<h2 id="setup-overview">제8권 · 8.1 Setup 모드 — Flash 환경설정</h2>
<p><code>m_St.SRM_Mode.Bit.Setup</code> 일 때만 랙/셀/스테이션 쓰기 허용. 실패 시 NACK+ErrorCode.</p>

<h2 id="setup-tml">8.2 Setup TML 핸들러 (${envFns.length}개)</h2>`;
  for (const fn of envFns) {
    html += fnBlock(tmlText, fn, "");
  }

  html += `<h2 id="rack-logic">8.3 Flash 저장 함수 (SRM_Parameter.c)</h2>`;
  for (const fn of paramEnvFns) {
    if (paramText.includes(`${fn}(`)) html += fnBlock(paramText, fn, "ExtFlash + CRC");
  }

  html += `<h2 id="ref-pos">8.4 Create_Reference_Position — 전체</h2>
<p>셀/스테이션 좌표 변경 후 RAM 참조 테이블 재생성. 부팅·티칭 완료 시 호출.</p>
${fnBlock(devText, "Create_Reference_Position", "")}

<h2 id="scan-autoteach">8.5 센서 스캔 · 오토티칭</h2>
<h3>8.5.1 Scan_Travel_Position_Sensor — 전체</h3>
${fnBlock(devText, "Scan_Travel_Position_Sensor", "")}
<h3>8.5.2 Scan_Lift_Position_Sensor — 전체</h3>
${fnBlock(devText, "Scan_Lift_Position_Sensor", "")}
<h3>8.5.3 Auto_Teaching_Check_Lift_Software_Limit — 전체</h3>
${fnBlock(devText, "Auto_Teaching_Check_Lift_Software_Limit", "")}
<h3>8.5.4 RunMode SCAN_SENSOR</h3>
<p><code>RUN_SEQ_TRAV_SCAN_SENSOR_0/1</code> → Scan_Travel…, SubStep 50=완료, 100=에러.</p>
<p><code>RUN_SEQ_LIFT_SCAN_SENSOR_0/1</code> → Scan_Lift…</p>`;
  return html;
}

function buildVol9Params(paramText) {
  const fns = extractCFunctions(paramText, "");
  let html = `<h2 id="param-all">제9권 · SRM_Parameter.c 함수 전체 (${fns.length}개)</h2>
<p>장치·랙·셀·스테이션·금지랙·오프셋·드라이브·타임아웃 Flash read/write/CRC.</p>`;
  for (const fn of fns) {
    html += fnBlock(paramText, fn, "");
  }
  return html;
}

function buildAppendixFullSources() {
  const files = [
    ["main.c", lg.MAIN, "부팅·HAL·while(1)"],
    ["com_tml.c", lg.COM_TML, "TML UART·rx* 전체"],
    ["dev_SRM.c", lg.DEV_SRM, "상태머신·축제어·Store_* (~6.8만줄)"],
    ["alarm.c", lg.ALARM, "Save_*·DI/DO·에러"],
    ["ecat_main.c", ECAT_MAIN, "EtherCAT·PDO"],
    ["SRM_Parameter.c", PARAM, "Flash 파라미터"],
  ];
  let html = `<h2 id="source-full">부록 E — Core/Src 전체 소스 (생략 없음)</h2>
<div class="warn">함수 단위 설명(제4~9권)과 별도로, 원본 .c 파일 전체를 그대로 수록합니다. Ctrl+F로 라인 단위 검색.</div>`;
  for (const [name, fp, desc] of files) {
    const lines = countLines(fp);
    html += `<h3 id="src_${name.replace(".", "_")}">${esc(name)} (${lines.toLocaleString()}줄) — ${esc(desc)}</h3>`;
    html += `<pre class="code-sm source-full">${esc(read(fp))}</pre>`;
  }
  return html;
}

function buildAppendix(patterns, traps, symbolBody, structBody) {
  return `
<h2 id="patterns">부록 A — 코딩 패턴</h2>
${patterns.map((p) => `<div class="pattern-card"><h4>${esc(p.title)}</h4><pre class="code">${esc(p.code)}</pre><p>${esc(p.explain)}</p></div>`).join("")}
<h2 id="traps">부록 B — 명명 함정</h2>
${traps.map((t) => `<div class="trap-card"><div class="mono">${esc(t.name)}</div><b>함정</b>: ${esc(t.trap)}<br><b>실제</b>: ${esc(t.real)}</div>`).join("")}
<h2 id="symbol-dict">부록 C — 전체 심볼 용도 사전 (내장)</h2>
<div class="symbol-embed">${symbolBody}</div>
<h2 id="struct-tree-embed">부록 D — 구조체 트리 (내장)</h2>
<div class="struct-embed">${structBody}</div>
${buildAppendixFullSources()}`;
}

function buildBook(ctx, revInfo) {
  const {
    devText,
    tmlText,
    alarmText,
    paramText,
    mainText,
    devHdrText,
    userDef,
    runSeq,
    runCases,
    tmlHandlers,
    stores,
    saves,
    forkSteps,
    workStatus,
    symbolBody,
    structBody,
  } = ctx;

  const meta = {
    runCases: runCases.length,
    tmlHandlers: tmlHandlers.length,
    stores: stores.length,
    saves: saves.length,
  };

  return (
    buildVol0(revInfo, meta) +
    buildVol1(mainText) +
    buildVol2() +
    buildVol3(devText, devHdrText, runSeq) +
    buildVol4TmlOverview(tmlHandlers) +
    buildVol4TmlCore(tmlText) +
    buildVol4TmlAllSource(tmlText, tmlHandlers) +
    buildVol5StoreSave(devText, alarmText, stores, saves) +
    buildVol6Pdo(devText, ctx.ecatText, mainText, devHdrText, userDef, tmlText) +
    buildVol7Auto(runCases, devText, runSeq, forkSteps, workStatus) +
    buildVol8Setup(tmlText, paramText, devText) +
    buildVol9Params(paramText) +
    buildAppendix(PATTERNS, TRAPS, symbolBody, structBody)
  );
}

function main() {
  console.log("=== SRM MX 통합코드백과 (책형·무제한) ===");
  const revInfo = getRevisionInfo();
  const outName = `${UNIFIED_PREFIX}_${TODAY}_REV${revInfo.rev}.html`;
  const outPath = path.join(OUT, outName);

  console.log("1/4 심볼 사전…");
  execSync("node generate_full_manual.js", { cwd: OUT, stdio: "inherit" });

  console.log("2/4 소스 로드…");
  const devText = read(lg.DEV_SRM);
  const tmlText = read(lg.COM_TML);
  const alarmText = read(lg.ALARM);
  const paramText = read(PARAM);
  const mainText = read(lg.MAIN);
  const ecatText = read(ECAT_MAIN);
  const devHdrText = read(DEV_HDR);
  const userDef = read(USER_DEF);

  const runSeq = parseRunSeq(devHdrText);
  const runCases = extractRunCases(devText);
  const tmlHandlers = extractTmlHandlers(tmlText);
  const stores = extractStoreFunctions(devText);
  const saves = extractSaveFunctions(alarmText);
  const forkSteps = parseEnumBlock(userDef, "enumCMD_FORK_STEP_PROCESS");
  const workStatus = [];
  for (const line of userDef.split("\n")) {
    const m = line.match(/#define\s+(WORK_STATUS_\w+)\s+(\d+)/);
    if (m) workStatus.push({ name: m[1], val: m[2], comment: "" });
  }

  let symbolBody = extractHtmlBody(path.join(OUT, "SRM_전체심볼_용도사전.html")).replace(/<h1>[^<]*<\/h1>/, "");
  let structBody = extractHtmlBody(path.join(OUT, "SRM_구조체트리.html")).replace(/<h1>[^<]*<\/h1>/, "");

  const ctx = {
    devText,
    tmlText,
    alarmText,
    paramText,
    mainText,
    ecatText,
    devHdrText,
    userDef,
    runSeq,
    runCases,
    tmlHandlers,
    stores,
    saves,
    forkSteps,
    workStatus,
    symbolBody,
    structBody,
  };

  console.log("3/4 책 본문 조립…");
  const body = buildBook(ctx, revInfo);

  const css = `
    *{box-sizing:border-box}
    body{font-family:"Malgun Gothic",sans-serif;margin:0;color:#111;line-height:1.65}
    .layout{display:flex;min-height:100vh}
    nav.sidebar{width:280px;background:#1a2e1f;color:#e8f0ea;position:sticky;top:0;height:100vh;overflow-y:auto;padding:12px;font-size:8.5pt;flex-shrink:0}
    nav.sidebar a{color:#b8dcc8;text-decoration:none;display:block;padding:2px 6px;border-radius:3px}
    nav.sidebar a:hover{background:#2a4a35;color:#fff}
    nav.sidebar .part{color:#7ec99a;font-weight:700;margin:10px 0 3px;font-size:7.5pt;text-transform:uppercase}
    main{flex:1;padding:20px 32px 80px;max-width:1000px}
    h1{font-size:19pt;border-bottom:4px solid #1a6b3c;padding-bottom:8px}
    h2{font-size:13pt;background:#2c3e50;color:#fff;padding:9px 12px;margin:32px 0 12px;border-radius:4px}
    h3{font-size:11pt;color:#1a5;border-left:4px solid #1a6b3c;padding-left:8px;margin:16px 0 6px}
    .meta,.note,.warn,.goal{padding:10px 14px;margin:10px 0;border-radius:6px;font-size:9.5pt}
    .meta{background:#f0f7f2}.note{background:#fafafa;border-left:4px solid #1a6b3c}
    .warn{background:#fff8f0;border-left:4px solid #e67e22}
    .goal{background:#e8f4ec;border:1px solid #b8d4c4}
    pre.code,pre.code-sm{background:#1e2a22;color:#d4ecd8;padding:10px 14px;border-radius:6px;overflow-x:auto;font-size:7.5pt;line-height:1.4}
    pre.code-sm{max-height:none}
    .data-table{width:100%;border-collapse:collapse;font-size:8.5pt;margin:8px 0 14px}
    .data-table th{background:#1a6b3c;color:#fff;padding:5px 7px;text-align:left}
    .data-table td{border:1px solid #ddd;padding:4px 7px;vertical-align:top}
    .mono{font-family:Consolas,monospace;color:#055;font-size:8pt}
    details.fn-item,details.case-item{margin:4px 0;border:1px solid #ccc;border-radius:5px;padding:0 10px 8px;background:#fafafa}
    details>summary{cursor:pointer;padding:6px 2px;list-style:none;font-size:9pt}
    details>summary::-webkit-details-marker{display:none}
    .mermaid-wrap{background:#fff;border:1px solid #ddd;border-radius:6px;padding:12px;margin:10px 0;overflow-x:auto}
    .rev-banner{background:#1a3a2a;color:#e8f5ec;padding:12px 16px;border-radius:8px;margin-bottom:16px;font-size:9.5pt}
    .rev-tag{background:#ffd54f;color:#111;font-weight:800;padding:2px 10px;border-radius:4px;margin-right:8px}
    .rev-latest{color:#a5f3b4;font-weight:600;margin-left:10px}
    .symbol-embed,.struct-embed{font-size:9pt}
    pre.source-full{font-size:6.5pt;line-height:1.35}
    .pattern-card,.trap-card{margin:8px 0;padding:8px 12px;border-radius:6px;background:#fafcfa;border:1px solid #c8e0d0}
    @media print{nav.sidebar{display:none}main{max-width:100%}}
  `;

  const mermaid = `<script src="https://cdn.jsdelivr.net/npm/mermaid@10/dist/mermaid.min.js"></script>
<script>mermaid.initialize({startOnLoad:true,theme:'base'});</script>`;

  const html = `<!DOCTYPE html><html lang="ko"><head><meta charset="utf-8">
<title>SRM MX 통합코드백과 ${TODAY_DISP} REV${revInfo.rev}</title><style>${css}</style></head>
<body><div class="layout"><nav class="sidebar">${buildBookNav()}</nav><main>${body}</main></div>${mermaid}</body></html>`;

  console.log("4/4 저장…");
  fs.writeFileSync(outPath, html, "utf8");
  const mb = (fs.statSync(outPath).size / 1024 / 1024).toFixed(2);

  fs.writeFileSync(
    path.join(OUT, "README.md"),
    `# SRM 통합코드백과

## ★ 사용 파일
| 파일 | 설명 |
|------|------|
| **${outName}** | **REV${revInfo.rev} — 책형 통합본 (${mb} MB)** |

## 구조 (큰 개념 → 작은 개념)
- 제0권: 서문·전체 그림
- 제1권: main·Manager
- 제2권: 데이터 3층·구조체
- 제3권: RunMode 개론
- 제4권: TML (rx* 전체 소스)
- 제5권: Store/Save
- 제6권: PDO·수동·CREEP
- 제7권: GET/PUT·RunMode case 전체
- 제8권: Setup·티칭·스캔
- 제9권: SRM_Parameter.c 전 함수
- 부록 E: **Core/Src 6개 .c 전체 소스** (main·com_tml·dev_SRM·alarm·ecat·Parameter)

## 재생성
\`\`\`bash
cd docs/manual && node generate_unified_guide.js
\`\`\`

생성: ${TODAY_DISP} REV${revInfo.rev}
`,
    "utf8"
  );

  console.log(`완료: ${outPath} (${mb} MB)`);
}

main();
