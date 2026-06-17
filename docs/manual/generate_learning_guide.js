/**
 * SRM 전체코드 학습가이드 — 완전판 HTML 생성
 * 큰 흐름 → 작은 흐름, 코드 자동 추출 포함
 */
const fs = require("fs");
const path = require("path");

const ROOT = path.resolve(__dirname, "..", "..");
const CORE = path.join(ROOT, "Core");
const INC = path.join(CORE, "Inc");
const SRC = path.join(CORE, "Src");
const OUT = __dirname;

const DEV_SRM = path.join(SRC, "dev_SRM.c");
const COM_TML = path.join(SRC, "com_tml.c");
const ALARM = path.join(SRC, "alarm.c");
const MAIN = path.join(SRC, "main.c");

const TODAY = new Date().toISOString().slice(0, 10).replace(/-/g, "");
const TODAY_DISP = new Date().toISOString().slice(0, 10);

function read(fp) {
  return fs.readFileSync(fp, "utf8");
}
function esc(s) {
  return String(s ?? "")
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;");
}
function countLines(fp) {
  return read(fp).split("\n").length;
}

/** C 소스에서 함수 본문 추출. maxLines=0 이면 끝까지(생략 없음) */
function extractFunctionBody(source, funcName, maxLines = 0) {
  const patterns = [
    new RegExp(`^[\\t ]*(?:void|INT\\w+U?)\\s+${funcName}\\s*\\(`, "m"),
    new RegExp(`^[\\t ]*static\\s+(?:void|INT\\w+U?)\\s+${funcName}\\s*\\(`, "m"),
  ];
  let idx = -1;
  for (const re of patterns) {
    idx = source.search(re);
    if (idx >= 0) break;
  }
  if (idx < 0) return `/* ${funcName} — 소스에서 찾을 수 없음 */`;
  const lines = source.slice(idx).split("\n");
  let depth = 0;
  let started = false;
  const out = [];
  for (const line of lines) {
    out.push(line);
    for (const ch of line) {
      if (ch === "{") {
        depth++;
        started = true;
      } else if (ch === "}") depth--;
    }
    if (started && depth === 0) break;
    if (maxLines > 0 && out.length >= maxLines) {
      out.push("/* ... 이후 생략 (함수가 매우 김) */");
      break;
    }
  }
  return out.join("\n");
}

function parseRunSeq(text) {
  const items = [];
  const start = text.indexOf("enum enumSRM_RUN_SEQ");
  if (start < 0) return items;
  const block = text.slice(start, text.indexOf("};", start));
  for (const line of block.split("\n")) {
    const m = line.match(/^\s*(RUN_SEQ_\w+)(?:\s*=\s*(\d+))?\s*(?:,\s*(?:\/\/(.*))?)?$/);
    if (m) items.push({ name: m[1], val: m[2] || "", comment: (m[3] || "").trim() });
  }
  return items;
}

/** dev_SRM.c 모든 case RUN_SEQ_* 추출 */
function extractRunCases(text) {
  const lines = text.split("\n");
  const cases = [];
  for (let i = 0; i < lines.length; i++) {
    const m = lines[i].match(/^\s*case\s+(RUN_SEQ_\w+)\s*:/);
    if (!m) continue;
    const name = m[1];
    const snippet = [];
    const saves = [];
    const stores = [];
    const errors = [];
    const transitions = [];
    for (let j = i; j < lines.length; j++) {
      const ln = lines[j];
      snippet.push(ln);
      const tm = ln.match(/SRM_RunMode\s*=\s*(RUN_SEQ_\w+)/);
      if (tm) transitions.push(tm[1]);
      if (/Save_Fork|Save_ForkMove/.test(ln)) saves.push(ln.trim());
      if (/Store_Work|Store_Fork/.test(ln)) stores.push(ln.trim());
      if (/save_error_code/.test(ln)) errors.push(ln.trim());
      if (/^\s*break\s*;/.test(ln) && j > i) break;
      if (j > i && /^\s*case\s+RUN_SEQ_/.test(ln)) break;
    }
    cases.push({
      name,
      line: i + 1,
      snippet: snippet.join("\n"),
      transitions: [...new Set(transitions)],
      saves,
      stores,
      errors,
    });
  }
  return cases;
}

/** 누가 이 RunMode로 점프하는지 (전 파일 grep) */
function findIncomingTransitions(text, targetCase) {
  const incoming = [];
  const lines = text.split("\n");
  const re = new RegExp(`SRM_RunMode\\s*=\\s*${targetCase.replace(/[.*+?^${}()|[\]\\]/g, "\\$&")}`);
  for (let i = 0; i < lines.length; i++) {
    if (re.test(lines[i])) {
      let ctx = "";
      for (let j = Math.max(0, i - 15); j <= i; j++) {
        const cm = lines[j].match(/case\s+(RUN_SEQ_\w+)/);
        if (cm) ctx = cm[1];
      }
      incoming.push({ line: i + 1, from: ctx || "(함수/초기화)", code: lines[i].trim() });
    }
  }
  return incoming;
}

function extractTmlHandlers(text) {
  const handlers = [];
  const re = /case\s+(TY_\w+)\s*:\s*(?:\/\*.*?\*\/)?\s*(?:rx\w+\([^)]*\)|break)/g;
  let m;
  const seen = new Set();
  while ((m = re.exec(text))) {
    const ty = m[1];
    const line = text.slice(0, m.index).split("\n").length;
    const full = text.slice(m.index, m.index + 120).split("\n")[0];
    const fn = full.match(/(rx\w+)\s*\(/)?.[1] || "—";
    if (!seen.has(ty + fn)) {
      seen.add(ty + fn);
      handlers.push({ ty, fn, line });
    }
  }
  // simpler line-based
  const out = [];
  const seen2 = new Set();
  for (const line of text.split("\n")) {
    const m2 = line.match(/case\s+(TY_\w+).*?(rx\w+)\s*\(/);
    if (m2 && !seen2.has(m2[1])) {
      seen2.add(m2[1]);
      out.push({ ty: m2[1], fn: m2[2] });
    }
  }
  return out.length ? out : handlers;
}

function extractSaveFunctions(text) {
  const fns = [];
  for (const line of text.split("\n")) {
    const m = line.match(/^void\s+(Save_\w+)\s*\(/);
    if (m) fns.push(m[1]);
  }
  return fns;
}

function extractStoreFunctions(text) {
  const fns = [];
  for (const line of text.split("\n")) {
    const m = line.match(/^static void\s+(Store_\w+)\s*\(/);
    if (m) fns.push({ name: m[1], line: text.split("\n").indexOf(line) + 1 });
  }
  return fns;
}

const RUN_GROUPS = [
  { id: "standby", title: "0. 대기·시작", members: ["RUN_SEQ_STAND_BY", "RUN_SEQ_START"] },
  {
    id: "prepare",
    title: "1. 이동 준비·주행승강",
    members: [
      "RUN_SEQ_PREPARE_MOVE_0",
      "RUN_SEQ_PREPARE_MOVE_BRAKE_RELEASE_0",
      "RUN_SEQ_PREPARE_MOVE_BRAKE_RELEASE_1",
      "RUN_SEQ_MOVE_BEFORE_DELAY",
      "RUN_SEQ_START_MOVE_0",
      "RUN_SEQ_START_MOVE_1",
      "RUN_SEQ_TRAV_LIFT_MOVING",
      "RUN_SEQ_TRAV_LIFT_STABILZATION_TIME",
      "RUN_SEQ_TRAV_LIFT_AFTER_MOVE",
      "RUN_SEQ_FORK_START",
    ],
  },
  {
    id: "loading",
    title: "2. 적재 GET",
    members: [
      "RUN_SEQ_LOADING_START",
      "RUN_SEQ_LOADING_INTERLOCK",
      "RUN_SEQ_LOADING_INTERLOCK_NO_USE",
      "RUN_SEQ_LOADING_PRE_FORK_OUT",
      "RUN_SEQ_LOADING_FORK_OUT",
      "RUN_SEQ_LOADING_AFTER_FORK_OUT",
      "RUN_SEQ_LOADING_FORK_OUT_PRE_LIFT",
      "RUN_SEQ_LOADING_FORK_OUT_LIFT_UP",
      "RUN_SEQ_LOADING_FORK_OUT_AFTER_LIFT_UP",
      "RUN_SEQ_LOADING_PRE_FORK_IN",
      "RUN_SEQ_LOADING_FORK_IN",
      "RUN_SEQ_LOADING_AFTER_FORK_IN",
      "RUN_SEQ_LOADING_COMPLETE",
    ],
  },
  {
    id: "unloading",
    title: "3. 이재 PUT",
    members: [
      "RUN_SEQ_UNLOADING_START",
      "RUN_SEQ_UNLOADING_INTERLOCK",
      "RUN_SEQ_UNLOADING_INTERLOCK_NO_USE",
      "RUN_SEQ_UNLOADING_PRE_FORK_OUT",
      "RUN_SEQ_UNLOADING_FORK_OUT",
      "RUN_SEQ_UNLOADING_AFTER_FORK_OUT",
      "RUN_SEQ_UNLOADING_FORK_OUT_PRE_LIFT",
      "RUN_SEQ_UNLOADING_FORK_OUT_LIFT_DOWN",
      "RUN_SEQ_UNLOADING_FORK_OUT_AFTER_LIFT_DOWN",
      "RUN_SEQ_UNLOADING_FORK_IN",
      "RUN_SEQ_UNLOADING_AFTER_FORK_IN",
      "RUN_SEQ_UNLOADING_COMPLETE",
    ],
  },
  { id: "complete", title: "4. 완료·PLC", members: ["RUN_SEQ_COMPLETE", "RUN_SEQ_PLC_COM_0", "RUN_SEQ_PLC_COM_1", "RUN_SEQ_PLC_COM_2", "RUN_SEQ_PLC_COM_3"] },
  {
    id: "error",
    title: "5. 에러 정지",
    members: [
      "RUN_SEQ_ERROR_FORK_STOP",
      "RUN_SEQ_ERROR_TRAV_LIFF_STOP",
      "RUN_SEQ_ERROR_TRAV_LIFT_STOP_1",
      "RUN_SEQ_ERROR_TRAV_LIFT_STOP_2",
      "RUN_SEQ_ERROR_TRAV_LIFT_STOP_3",
    ],
  },
  {
    id: "origin",
    title: "6. 원점·설정",
    members: [
      "RUN_SEQ_FORK_ORIGIN_0",
      "RUN_SEQ_FORK_ORIGIN_1",
      "RUN_SEQ_TRAV_ORIGIN_0",
      "RUN_SEQ_TRAV_ORIGIN_1",
      "RUN_SEQ_LIFT_ORIGIN_0",
      "RUN_SEQ_LIFT_ORIGIN_1",
      "RUN_SEQ_LIFT_SET_HORIZONTAL_0",
      "RUN_SEQ_LIFT_SET_HORIZONTAL_1",
      "RUN_SEQ_SET_AUTO_RACK_0",
      "RUN_SEQ_SET_AUTO_RACK_1",
      "RUN_SEQ_SET_AUTO_RACK_STOP",
    ],
  },
  {
    id: "home",
    title: "7. 홈복귀",
    members: [
      "RUN_SEQ_RETURN_HOME_0",
      "RUN_SEQ_RETURN_HOME_0_1",
      "RUN_SEQ_RETURN_HOME_0_2",
      "RUN_SEQ_RETURN_HOME_1",
      "RUN_SEQ_RETURN_HOME_MOVING",
      "RUN_SEQ_RETURN_HOME_3",
      "RUN_SEQ_RETURN_HOME_4",
    ],
  },
];

const LOADING_FLOW = [
  { step: 1, run: "RUN_SEQ_PREPARE_MOVE_0", do: "화물검증, InPosition, StartPos/TargetPos 계산", save: "Save_ForkWork_OrderProcess(MOVING_FROM)" },
  { step: 2, run: "RUN_SEQ_PREPARE_MOVE_BRAKE_RELEASE_0", do: "주행·승강 브레이크 해제 확인 (nFlag 0x03)", save: "—" },
  { step: 3, run: "RUN_SEQ_MOVE_BEFORE_DELAY", do: "Read_DelayTime(PREFORE_MOVE) 대기", save: "—" },
  { step: 4, run: "RUN_SEQ_START_MOVE_0", do: "Auto_Ctr_Travel/Lift 명령", save: "—" },
  { step: 5, run: "RUN_SEQ_TRAV_LIFT_MOVING", do: "이동 중, 도착/InPosition 검사", save: "MOVING_FROM/TO" },
  { step: 6, run: "RUN_SEQ_TRAV_LIFT_AFTER_MOVE", do: "이동 후 안정화", save: "ARRIVED_FROM" },
  { step: 7, run: "RUN_SEQ_LOADING_INTERLOCK", do: "스테이션 CV 인터록", save: "—" },
  { step: 8, run: "RUN_SEQ_LOADING_PRE_FORK_OUT", do: "포크 진출 전 딜레이", save: "PRE_OUT" },
  { step: 9, run: "RUN_SEQ_LOADING_FORK_OUT", do: "m_Fork_Sub_Run_Step 포크 진출", save: "FORK_OUT" },
  { step: 10, run: "RUN_SEQ_LOADING_FORK_OUT_LIFT_UP", do: "리프트 업", save: "LIFT_UP" },
  { step: 11, run: "RUN_SEQ_LOADING_FORK_IN", do: "포크 복귀(센터)", save: "FORK_IN" },
  { step: 12, run: "RUN_SEQ_LOADING_COMPLETE", do: "GOX 화물센서 확인", save: "WORK_STATUS_COMPLETE" },
];

function buildThreeLayersDeep() {
  return `
<h2 id="layers">Part A — 데이터 3층 (완전 해설)</h2>
<div class="warn"><b>주의</b>: 아래 3층은 <b>동시에 한 줄로 흐르는 파이프가 아닙니다</b>.
<b>역할(책임) 분리 + 시간축</b>입니다. 0x41 시점에 입력·출력이 <b>겹치기도</b> 합니다.</div>

<h3 id="layers-roles">A.1 세 층의 역할</h3>
<table class="data-table">
<tr><th>층</th><th>한 줄</th><th>주요 변수</th><th>비유</th></tr>
<tr><td><b>입력층</b></td><td>지상반 명령 → 실행 <b>레시피</b> 작성</td><td>WorkCmdSTR → m_WorkData[]</td><td>주문서 → 조리 지시서</td></tr>
<tr><td><b>실행층</b></td><td>레시피 보고 모터·시퀀스 구동</td><td>SRM_RunMode, Sub_Run_Step, s_WorkInx</td><td>주방 조리</td></tr>
<tr><td><b>출력층</b></td><td>지상반에 진행·에러 <b>보고</b></td><td>m_St → 0x30, m_BKSram.AlarmLog</td><td>진행률 표시</td></tr>
</table>

<h3 id="layers-time">A.2 시간순 — GET 1건 전체 (T0→Tn)</h3>
<div class="flow-box"><pre class="flow-pre">[T0] 0x41 TY_CMD_ORDER ─────────────────── 입력층
     com_tml.c  rxCmdOrder()                    (약 2340행)
       ├─ 검증: STAND_BY? Auto? Fault? ForkCenter?
       └─ SRM_Fork_Work_Cmd(pCmd)               dev_SRM.c 약 45936행
            ├─ Store_Work_Data_1()  → m_WorkData[0],[1]…  ★ 실행 레시피
            └─ Store_Fork_WorkStatus() → m_St.ForkWork[]  ★ 지상반 1차 기록
     ※ 이 시점: 모터 안 움. RunMode = STAND_BY

[T1] 0x50 TY_CMD_START ─────────────────── 입력→실행 연결
     rxCmdStart() → SRM_Start_On()           (46806행)
       ├─ m_St.SRM_Status1.StartOn = 1
       └─ m_pgmEnv.SRM_RunMode = RUN_SEQ_START

[T2] 매 while(1) ───────────────────────── 실행층 (super loop)
     main.c → SRM_Manager() → SRM_Machine_Run_Process()  (58437행)
       switch(SRM_RunMode) — case 한 스텝만 실행 후 break
       ├─ m_WorkData[s_WorkInx] 읽음 (TargetPos, ForkAct…)
       ├─ Motor_Brake / Auto_Ctr_Travel / Auto_Ctr_Lift
       └─ Save_ForkWork_OrderProcess()  ────── 출력층 갱신

[T3] 0x30 TY_STATUS_REQ (주기 폴링) ───── 출력층 읽기
     rxStatusReq() → m_St 패킷 응답
     Save가 바꿔둔 OrderProcess/Status가 지상반 화면에 표시</pre></div>

<h3 id="layers-vars">A.3 층별 디버깅 — 무엇을 보나</h3>
<table class="data-table">
<tr><th>궁금한 것</th><th>볼 변수/함수</th><th>파일</th></tr>
<tr><td>명령 받았나?</td><td>m_St.ForkWork[0].WorkNum_Fork, OrderProcess=CMD_FORK_STEP_RX</td><td>Store_Fork_WorkStatus</td></tr>
<tr><td>뭘 실행하나?</td><td>m_WorkData[0].ForkAct, TargetPos, DrvData[]</td><td>dev_SRM.c static</td></tr>
<tr><td>지금 어느 단계?</td><td>m_pgmEnv.SRM_RunMode</td><td>enumSRM_RUN_SEQ</td></tr>
<tr><td>지상반 스텝?</td><td>m_St.ForkWork[0].OrderProcess_Fork</td><td>Save_ForkWork_*</td></tr>
<tr><td>에러?</td><td>m_St.Fault, save_error_code, AlarmLog</td><td>alarm.c</td></tr>
</table>

<h3 id="store-save">A.4 Store_* vs Save_* (이름 같아서 지옥)</h3>
<table class="data-table">
<tr><th></th><th>Store_*</th><th>Save_*</th></tr>
<tr><td><b>시점</b></td><td>주로 0x41 (SRM_Fork_Work_Cmd)</td><td>실행 중 RunMode case</td></tr>
<tr><td><b>m_WorkData</b></td><td>✅ 채움 (TargetPos, ForkAct…)</td><td>❌ 거의 안 씀</td></tr>
<tr><td><b>m_St</b></td><td>✅ Store_Fork_WorkStatus도 m_St 씀</td><td>✅ 스텝/상태 갱신</td></tr>
<tr><td><b>BKPSRAM</b></td><td>일부</td><td>✅ saveBKSramBlock</td></tr>
<tr><td><b>의미</b></td><td>명령 접수 + 실행 큐</td><td>돌면서 진행 보고</td></tr>
</table>

<h3 id="layers-diagram">A.5 수정된 흐름도 (겹침 표시)</h3>
<div class="flow-box"><pre class="flow-pre">지상반                         MCU
──────                         ───

0x41 ──► rxCmdOrder
           └─► Store ──► m_WorkData (실행 레시피)
           └─► Store_Fork_WorkStatus ──► m_St (작업번호·RX)  ← 입력+출력 겹침

         (대기: StartOn=0, RunMode=STAND_BY)

0x50 ──► SRM_Start_On ──► RunMode=START
                              │
                              ▼
                    SRM_Machine_Run_Process (매 루프)
                              │
              ┌───────────────┼───────────────┐
              ▼               ▼               ▼
         m_WorkData      인버터/EtherCAT    Save_* → m_St
                                              │
0x30 ◄────────────────────────────────────────┘ 폴링</pre></div>

<h3 id="mpgmenv-mst">A.6 m_pgmEnv vs m_St</h3>
<p><b>m_pgmEnv</b> (PGMEnvSTR): MCU 내부 전용. SRM_RunMode, timer1ms, 통신 링크, 내부 플래그.
지상반 0x30에 <b>직접 안 나감</b>.</p>
<p><b>m_St</b> (StatusSTR): 지상반 "얼굴". ForkWork[], Inv_St[], DI/DO, Fault.
<b>Save_*</b>가 여기 씀 → 0x30 폴링.</p>
<p><b>m_WorkData</b>: dev_SRM.c <code>static SRM_WorkDataSTR m_WorkData[30]</code> — extern 아님.
상태머신만 접근하는 <b>실행 큐</b>.</p>
`;
}

function buildRxCmdOrderDeep() {
  return `
<h2 id="rx41">Part B — 0x41 rxCmdOrder() 완전 추적</h2>
<p><b>파일</b>: com_tml.c 약 <code>2340</code>행 <code>void rxCmdOrder()</code></p>

<h3>B.1 진입 ~ 검증 (거부 사유)</h3>
<ol>
<li><code>pCmd = (WorkCmdSTR*)&amp;pCom-&gt;Data[0]</code> — 패킷 → 구조체</li>
<li>Fault → COMMAND_ERROR_FALUT_STATE</li>
<li>ManualSW → COMMAND_ERROR_MANUAL_SW_ON</li>
<li><code>SRM_RunMode != RUN_SEQ_STAND_BY</code> → 이전 명령 실행 중</li>
<li><code>Check_Fork_Center_Alarm()</code> → 포크 센터 이탈</li>
<li>Auto==0 → 수동 모드</li>
<li>GET/PUT 시 StartOn==0 → NON_ONLINE (온라인 아님)</li>
<li>GoodsFlag 검사 (DISABLE_ERROR_CARRIER_GOODS_SENSOR로 생략 가능)</li>
<li>CheckCmdCellPosition, 금지랙, 스페셜랙</li>
</ol>

<h3>B.2 수락 시 — SRM_Fork_Work_Cmd()</h3>
<p><code>ret_value[0] = SRM_Fork_Work_Cmd(pCmd)</code> — dev_SRM.c 약 45936행</p>
<ul>
<li>OrderCode별 From/To 좌표 → TravPos/LiftPos 계산</li>
<li><code>Store_Work_Data_1()</code> — GET+PUT면 m_WorkData에 2슬롯 (From GET, To PUT)</li>
<li><code>Store_Fork_WorkStatus()</code> — m_St.ForkWork[0]에 WorkNum, OrderCode, RX 스텝</li>
<li>Store_Work_Data 내부에서 From_Cell/To_Cell을 m_St에 memcpy하기도 함</li>
</ul>

<h3>B.3 0x41 직후 상태</h3>
<table class="data-table">
<tr><th>항목</th><th>값</th></tr>
<tr><td>RunMode</td><td>STAND_BY (아직 Start 전)</td></tr>
<tr><td>m_WorkData</td><td>채워짐 (실행 대기)</td></tr>
<tr><td>m_St.ForkWork</td><td>WorkNum, OrderCode, OrderProcess=RX</td></tr>
<tr><td>모터</td><td>안 움</td></tr>
</table>
`;
}

function buildStartOnDeep() {
  return `
<h2 id="rx50">Part C — 0x50 Start / SRM_Start_On()</h2>
<p><code>rxCmdStart()</code> com_tml.c 2825행 → <code>SRM_Start_On()</code> dev_SRM.c 46806행</p>

<h3>C.1 Start 거부 조건</h3>
<ul>
<li>OrderRejectCondition (비상/안전플러그)</li>
<li>Fault, !Auto</li>
<li>이미 StartOn==1 (NON_ONLINE)</li>
<li>포크 센터 이탈</li>
<li>RunMode != STAND_BY</li>
</ul>

<h3>C.2 Start 성공 시</h3>
<ul>
<li><code>m_St.SRM_Status1.Bit.StartOn = 1</code></li>
<li><code>m_pgmEnv.SRM_RunMode = RUN_SEQ_START</code> (47431행 근처)</li>
<li>WorkInfo → BKPSRAM 저장</li>
</ul>

<h3>C.3 RUN_SEQ_START case (58792행~)</h3>
<ul>
<li><code>s_WorkInx = 0</code> (또는 TaskMode면 SRM_TaskIndex)</li>
<li>스테이션/Row_ID → Move_PosFlag 설정</li>
<li><code>m_WorkData[s_WorkInx].ForkAct</code>에 따라 PREPARE / LOADING_START / UNLOADING_START 분기</li>
</ul>
`;
}

function buildMainLoopDeep() {
  return `
<h2 id="mainloop">Part D — main 루프 · Manager · 타이머</h2>
<pre class="code">// main.c while(1) — 협력적 super loop (RTOS 아님)
AlarmManager();       // DI/DO, 에러
TMLComManager();      // ★ UART 수신 → rxCmdOrder/Start/Status
ECAT_Manager();       // ★ 인버터 PDO
SRM_Manager();        // ★ SRM_Machine_Run_Process()

// 1ms ISR (main.c)
m_pgmEnv.timer1ms++;  // 모든 getCalcTimer1ms()의 시계</pre>

<h3>D.1 SRM_Manager() (67918행)</h3>
<ol>
<li>Scan_Digital_Input_Chattering()</li>
<li>SRM_Machine_Process() — SSR/연결</li>
<li><b>SRM_Machine_Run_Process()</b> — 상태머신 본체</li>
<li>HMI_ModbusTCP_Proc()</li>
</ol>

<h3>D.2 SRM_Machine_Run_Process() static 변수 (58463행~)</h3>
<table class="data-table">
<tr><th>변수</th><th>역할</th></tr>
<tr><td>s_WorkInx</td><td>현재 m_WorkData 인덱스</td></tr>
<tr><td>s_Work_Fork_Flag</td><td>포크1/2 동시 작업 비트</td></tr>
<tr><td>s_No_movement</td><td>주행·승강 스킵, 포크만</td></tr>
<tr><td>s_Delay_Time</td><td>Read_DelayTime() 결과 ms</td></tr>
<tr><td>s_Brake_Release_Retry</td><td>브레이크 해제 재시도</td></tr>
</table>
`;
}

function buildPrepareMoveDeep() {
  return `
<h2 id="prepare-deep">Part E — PREPARE_MOVE · 브레이크 해제 (상세)</h2>

<h3>E.1 RUN_SEQ_PREPARE_MOVE_0</h3>
<ol>
<li><code>Check_Trav_lift_In_Postion(s_WorkInx)</code> — 목표 도착?</li>
<li><code>Rack_fork_obstruction != 0</code> — InPosition이어도 재이동 (WCS 스킵 방지)</li>
<li>이동 필요: StartPos←Current_Pos, Move_Dir←Check_Trav/Lift_Move_Dir</li>
<li><code>Save_ForkWork_OrderProcess(MOVING_FROM/TO)</code></li>
<li>ENABLE_TRAV_LEFT_MOVE_BRAKE_RELEASE → BRAKE_RELEASE_0 else MOVE_BEFORE_DELAY</li>
</ol>

<h3>E.2 RUN_SEQ_PREPARE_MOVE_BRAKE_RELEASE_0</h3>
<pre class="code">nFlag = 0;
if (Get_Motor_Brake_Release(INV_TRAVEL))  nFlag |= cbits[0]; // bit0=주행
if (Get_Motor_Brake_Release(INV_HOIST))     nFlag |= cbits[1]; // bit1=승강
// nFlag: 0x00=둘다미해제, 0x01=주행, 0x02=승강, 0x03=둘다해제
// 3초 내 nFlag==0x03 → MOVE_BEFORE_DELAY
// 타임아웃 → save_error_code(ERROR1_WORK_TIMEOUT, 1, nFlag)</pre>
<p><code>Get_Motor_Brake_Release</code> 1124행: 1=Brake Off(해제), 0=Brake On</p>
`;
}

function buildLoadingFlowTable() {
  let html = `<h2 id="get-flow-table">Part F — GET(적재) 단계별 RunMode 표</h2><table class="data-table">
<tr><th>#</th><th>RunMode</th><th>하는 일</th><th>Save 보고(개요)</th></tr>`;
  for (const s of LOADING_FLOW) {
    html += `<tr><td>${s.step}</td><td class="mono">${esc(s.run)}</td><td>${esc(s.do)}</td><td class="mono">${esc(s.save)}</td></tr>`;
  }
  html += `</table><p>PUT(UNLOADING_*)는 LIFT_UP→LIFT_DOWN 등 대칭. dev_SRM.h enum 50번대.</p>`;
  return html;
}

function buildAllRunCaseIndex(runCases, devText, runSeqEnum) {
  const caseMap = new Map(runCases.map((c) => [c.name, c]));
  const enumMap = new Map(runSeqEnum.map((r) => [r.name, r]));
  let html = `<h2 id="runmode-all">Part G — RunMode case 전체 (${runCases.length}개, 코드 추출)</h2>
<div class="note">각 case 클릭 → dev_SRM.c 소스 일부, 다음 RunMode, Save/에러 호출, <b>누가 이 case로 들어오나</b></div>`;

  for (const g of RUN_GROUPS) {
    html += `<h3 id="grp-${g.id}">${esc(g.title)}</h3>`;
    for (const name of g.members) {
      const c = caseMap.get(name);
      const en = enumMap.get(name);
      if (!c) {
        html += `<details class="case-item"><summary class="mono">${esc(name)}</summary><p>case 본문 없음 (enum만)</p></details>`;
        continue;
      }
      const incoming = findIncomingTransitions(devText, name);
      html += `<details class="case-item" id="case_${name}">`;
      html += `<summary><span class="mono">${esc(name)}</span>`;
      if (en?.comment) html += ` <span class="kind">— ${esc(en.comment)}</span>`;
      html += ` <span class="kind">dev_SRM.c:${c.line}</span></summary>`;

      if (incoming.length) {
        html += `<p><b>← 들어오는 전이</b> (${incoming.length}건)</p><ul>`;
        for (const inc of incoming) {
          html += `<li>L${inc.line} from <span class="mono">${esc(inc.from)}</span>: <code>${esc(inc.code)}</code></li>`;
        }
        html += `</ul>`;
      }
      if (c.transitions.length) {
        html += `<p><b>→ 나가는 전이</b>: ${c.transitions.map((t) => `<span class="mono">${esc(t)}</span>`).join(", ")}</p>`;
      }
      if (c.saves.length) html += `<p><b>Save_*</b>: ${c.saves.map((s) => `<code>${esc(s)}</code>`).join("<br>")}</p>`;
      if (c.errors.length) html += `<p><b>save_error_code</b>: ${c.errors.map((s) => `<code>${esc(s)}</code>`).join("<br>")}</p>`;
      html += `<pre class="code-sm">${esc(c.snippet)}</pre>`;
      html += `</details>`;
    }
  }

  // ungrouped cases
  const grouped = new Set(RUN_GROUPS.flatMap((g) => g.members));
  const rest = runCases.filter((c) => !grouped.has(c.name));
  if (rest.length) {
    html += `<h3 id="grp-misc">8. 기타 RunMode (${rest.length}개)</h3>`;
    for (const c of rest) {
      html += `<details class="case-item"><summary class="mono">${esc(c.name)}</summary>`;
      html += `<p>L${c.line} → ${c.transitions.map(esc).join(", ") || "—"}</p>`;
      html += `<pre class="code-sm">${esc(c.snippet)}</pre>`;
      html += `</details>`;
    }
  }
  return html;
}

function buildTmlTable(handlers) {
  const core = [
    ["TY_STATUS_REQ (0x30)", "rxStatusReq", "m_St 폴링 응답"],
    ["TY_CMD_ORDER (0x41)", "rxCmdOrder", "작업명령 → SRM_Fork_Work_Cmd"],
    ["TY_CMD_START (0x50)", "rxCmdStart", "SRM_Start_On → RUN_SEQ_START"],
    ["TY_CMD_MOVE_HOME (0x51)", "rxCmd_MoveHome", "홈 이동"],
    ["TY_CMD_ERROR_RESET (0x52)", "rxCmdErrorReset", "에러 리셋"],
    ["TY_CMD_ORDER_DELETE (0x53)", "rxCmdOrderDelete", "작업 삭제"],
    ["TY_EMERGENCY_STOP (0x55)", "rxCmdEmergencyStop", "비상정지"],
  ];
  let html = `<h2 id="tml-all">Part H — TML 수신 핸들러</h2>
<h3>H.1 핵심 7개 (자동운전)</h3><table class="data-table">
<tr><th>TY_*</th><th>함수</th><th>역할</th></tr>`;
  for (const [ty, fn, role] of core) {
    html += `<tr><td>${esc(ty)}</td><td class="mono">${esc(fn)}</td><td>${esc(role)}</td></tr>`;
  }
  html += `</table><h3>H.2 전체 (com_tml.c switch, ${handlers.length}개)</h3>
<details><summary>파라미터·다운로드·시험 포함 전체 목록</summary>
<table class="data-table"><tr><th>TY_*</th><th>rx 함수</th></tr>`;
  for (const h of handlers) {
    html += `<tr><td class="mono">${esc(h.ty)}</td><td class="mono">${esc(h.fn)}</td></tr>`;
  }
  html += `</table></details>`;
  return html;
}

function buildStoreSaveChapter(stores, saves) {
  let html = `<h2 id="store-save-fns">Part I — Store_* / Save_* 함수 목록</h2>
<h3>I.1 Store_* (dev_SRM.c static — 입력/큐)</h3><ul>`;
  for (const s of stores) html += `<li class="mono">${esc(s.name)} (L${s.line})</li>`;
  html += `</ul><h3>I.2 Save_* (alarm.c — 출력/보고)</h3><ul>`;
  for (const s of saves) html += `<li class="mono">${esc(s)}() → m_St + BKPSRAM</li>`;
  html += `</ul>`;
  return html;
}

function buildNav() {
  return `
<div class="part">시작</div>
<a href="#intro">목적·읽는법</a>
<a href="#curriculum">4주 로드맵</a>
<a href="#layers">A. 데이터 3층 완전해설</a>
<a href="#layers-time">A.2 시간순 T0→Tn</a>
<a href="#store-save">A.4 Store vs Save</a>
<div class="part">통신·시작</div>
<a href="#rx41">B. 0x41 rxCmdOrder</a>
<a href="#rx50">C. 0x50 Start</a>
<a href="#mainloop">D. main 루프</a>
<a href="#tml-all">H. TML 핸들러</a>
<div class="part">상태머신</div>
<a href="#prepare-deep">E. PREPARE·브레이크</a>
<a href="#get-flow-table">F. GET 단계표</a>
<a href="#runmode-all">G. RunMode case 전체</a>
<a href="#fork-steps">J. 스텝 enum</a>
<a href="#put-flow">F2. PUT 흐름</a>
<a href="#files">K. 파일 맵</a>
<a href="#struct8">L. 8대 구조체</a>
<div class="part">함수·실전</div>
<a href="#store-save-fns">I. Store/Save 함수</a>
<a href="#patterns">코딩 패턴</a>
<a href="#traps">명명 함정</a>
<a href="#exercise">연습문제</a>
<a href="#transfer">타 설비 이식</a>
<a class="ext" href="SRM_전체심볼_용도사전.html">→ 심볼 사전</a>
<a class="ext" href="SRM_구조체트리.html">→ 구조체 트리</a>`;
}

const PATTERNS = [
  { title: "RunMode case", code: `case RUN_SEQ_XXX:\n  if (getCalcTimer1ms(m_pgmEnv.SRM_RunTimer) > MS)\n    m_pgmEnv.SRM_RunMode = RUN_SEQ_다음;\n  break;`, explain: "매 루프 1스텝. break 필수." },
  { title: "nFlag 비트맵", code: `nFlag |= cbits[0]; // bit0\n// 0x03 = 둘 다 OK`, explain: "축 상태를 에러 서브코드로." },
  { title: "Store vs Save", code: `Store_Work_Data_1(...); // m_WorkData\nSave_ForkWork_OrderProcess(0, STEP); // m_St`, explain: "Store=레시피, Save=보고." },
  { title: "타이머", code: `m_pgmEnv.SRM_RunTimer = m_pgmEnv.timer1ms;\ngetCalcTimer1ms(...) > 3000`, explain: "1ms ISR 기반." },
];

const TRAPS = [
  { name: "GoodsFlag_Or_MoveHome", trap: "화물 플래그?", real: "축마다 다름. 포크=화물, 주행/승강=홈복귀." },
  { name: "Rack_fork_obstruction", trap: "물리 간섭?", real: "InPosition 스킵 방지. 1이면 재이동." },
  { name: "Store vs Save", trap: "둘 다 저장", real: "Store=큐+접수, Save=진행보고." },
  { name: "ENABLE_TRAV_LEFT_MOVE_BRAKE_RELEASE", trap: "좌측 이동?", real: "컴파일 옵션. 주행+승강 브레이크 확인." },
];

function parseEnumBlock(text, enumName) {
  const items = [];
  const start = text.indexOf(`enum ${enumName}`);
  if (start < 0) return items;
  const block = text.slice(start, text.indexOf("};", start));
  for (const line of block.split("\n")) {
    const m = line.match(/^\s*(\w+)\s*(?:=\s*([^,/]+))?\s*,?\s*(?:\/\/(.*))?$/);
    if (!m || m[1] === "enum") continue;
    items.push({ name: m[1], val: (m[2] || "").trim(), comment: (m[3] || "").trim() });
  }
  return items;
}

function buildForkStepTable(forkSteps, workStatus) {
  let html = `<h2 id="fork-steps">Part J — 지상반 스텝 코드 (OrderProcess)</h2>
<h3>J.1 WORK_STATUS (작업 결과)</h3><table class="data-table"><tr><th>이름</th><th>값</th></tr>`;
  for (const w of workStatus.filter((x) => x.name.startsWith("WORK_STATUS"))) {
    html += `<tr><td class="mono">${esc(w.name)}</td><td>${esc(w.val)}</td></tr>`;
  }
  html += `</table><h3>J.2 CMD_FORK_STEP (포크 작업 진행 — Save_ForkWork_OrderProcess 인자)</h3>
<table class="data-table"><tr><th>enum</th><th>값</th><th>현장 의미(개요)</th></tr>`;
  const meanings = {
    CMD_FORK_STEP_RX: "0x41 명령 수신됨",
    CMD_FORK_STEP_MOVING_FROM: "From 셀 쪽으로 주행·승강 이동 중",
    CMD_FORK_STEP_ARRIVED_FROM: "From 위치 도착",
    CMD_FORK_STEP_FORK_OUT_FROM: "From에서 포크 진출",
    CMD_FORK_STEP_FORK_UP_FROM: "적재 리프트 업",
    CMD_FORK_STEP_FORK_IN_FROM: "From 후 포크 복귀",
    CMD_FORK_STEP_MOVING_TO: "To 셀 쪽 이동 중",
    CMD_FORK_STEP_ARRIVED_TO: "To 위치 도착",
    CMD_FORK_STEP_FORK_OUT_TO: "To에서 포크 진출",
    CMD_FORK_STEP_FORK_DOWN_TO: "이재 리프트 다운",
    CMD_FORK_STEP_FORK_IN_TO: "To 후 포크 복귀",
    CMD_FORK_STEP_LODADED: "적재 완료(화물 확인)",
    CMD_FORK_STEP_UNLODADED: "이재 완료",
  };
  for (const s of forkSteps) {
    html += `<tr><td class="mono">${esc(s.name)}</td><td>${esc(s.val || "auto")}</td><td>${esc(meanings[s.name] || s.comment || "—")}</td></tr>`;
  }
  html += `</table><p>지상반 화면 "스텝" = <code>m_St.ForkWork[0].OrderProcess_Fork</code> 이 값.</p>`;
  return html;
}

function buildPutFlowTable() {
  const put = [
    { step: 1, run: "UNLOADING_START", do: "PUT 분기 진입, 화물 있음 검사" },
    { step: 2, run: "UNLOADING_INTERLOCK", do: "스테이션 인터록" },
    { step: 3, run: "UNLOADING_PRE_FORK_OUT", do: "포크 진출 전 딜레이" },
    { step: 4, run: "UNLOADING_FORK_OUT", do: "포크 To 랙 진출" },
    { step: 5, run: "UNLOADING_FORK_OUT_LIFT_DOWN", do: "리프트 다운(이재)" },
    { step: 6, run: "UNLOADING_FORK_IN", do: "포크 복귀" },
    { step: 7, run: "UNLOADING_COMPLETE", do: "공출고/화물 없음 확인" },
  ];
  let html = `<h2 id="put-flow">Part F2 — PUT(이재) 단계</h2><table class="data-table"><tr><th>#</th><th>RunMode</th><th>하는 일</th></tr>`;
  for (const s of put) {
    html += `<tr><td>${s.step}</td><td class="mono">RUN_SEQ_${esc(s.run)}</td><td>${esc(s.do)}</td></tr>`;
  }
  return html + `</table>`;
}

function buildFileTable() {
  const roles = {
    "main.c": "부트·HAL·while(1)·timer1ms",
    "dev_SRM.c": "상태머신·축제어·Store_*",
    "com_tml.c": "TML 0x30/0x41/0x50",
    "alarm.c": "Save_*·DI/DO·에러",
    "SRM_Parameter.c": "Flash 파라미터",
    "ecat_main.c": "EtherCAT PDO",
    "rtc.c": "BKPSRAM",
    "com_hmi.c": "HMI Modbus",
  };
  let html = `<h2 id="files">Part K — Core/Src 파일 맵</h2><table class="data-table"><tr><th>파일</th><th>줄</th><th>역할</th></tr>`;
  for (const f of fs.readdirSync(SRC).filter((x) => x.endsWith(".c")).sort()) {
    html += `<tr><td class="mono">${esc(f)}</td><td>${countLines(path.join(SRC, f)).toLocaleString()}</td><td>${esc(roles[f] || "인프라/보조")}</td></tr>`;
  }
  return html + `</table>`;
}

function buildStructEight() {
  return `<h2 id="struct8">Part L — 핵심 8대 구조체 (변수 ↔ 역할)</h2>
<table class="data-table">
<tr><th>변수</th><th>타입</th><th>층</th><th>역할</th></tr>
<tr><td class="mono">m_St</td><td>StatusSTR</td><td>출력</td><td>0x30 지상반 상태. ForkWork[], Inv_St[]</td></tr>
<tr><td class="mono">m_pgmEnv</td><td>PGMEnvSTR</td><td>실행</td><td>RunMode, timer1ms, 내부 플래그 (지상반 비공개)</td></tr>
<tr><td class="mono">m_WorkData</td><td>SRM_WorkDataSTR[30]</td><td>입력/실행</td><td>static 실행 큐. ForkAct, TargetPos</td></tr>
<tr><td class="mono">m_BKSram</td><td>BKSRamSTR</td><td>출력/복구</td><td>정전복구 AlarmLog, WorkInfo</td></tr>
<tr><td class="mono">m_ExtSEnv0~2</td><td>ExtFlash*</td><td>파라미터</td><td>랙/스테이션/포크/타임아웃 Flash</td></tr>
<tr><td class="mono">WorkCmd</td><td>WorkCmdSTR</td><td>입력</td><td>0x41 패킷 파싱 형식</td></tr>
</table>
<p>멤버 트리 → <a href="SRM_구조체트리.html">구조체 트리</a></p>`;
}

function buildLearningGuide() {
  console.log("Loading sources...");
  const devText = read(DEV_SRM);
  const tmlText = read(COM_TML);
  const alarmText = read(ALARM);
  const runSeq = parseRunSeq(read(path.join(INC, "dev_SRM.h")));
  const runCases = extractRunCases(devText);
  const tmlHandlers = extractTmlHandlers(tmlText);
  const stores = extractStoreFunctions(devText);
  const saves = extractSaveFunctions(alarmText);
  const userDef = read(path.join(INC, "User_Define.h"));
  const forkSteps = parseEnumBlock(userDef, "enumCMD_FORK_STEP_PROCESS");
  const workStatus = [];
  for (const line of userDef.split("\n")) {
    const m = line.match(/#define\s+(WORK_STATUS_\w+)\s+(\d+)/);
    if (m) workStatus.push({ name: m[1], val: m[2], comment: "" });
  }

  const css = `
    *{box-sizing:border-box}
    body{font-family:"Malgun Gothic",sans-serif;margin:0;color:#111;line-height:1.65}
    .layout{display:flex;min-height:100vh}
    nav.sidebar{width:300px;background:#1a2e1f;color:#e8f0ea;position:sticky;top:0;height:100vh;overflow-y:auto;padding:14px;font-size:9pt;flex-shrink:0}
    nav.sidebar a{color:#b8dcc8;text-decoration:none;display:block;padding:3px 8px;border-radius:4px}
    nav.sidebar a:hover{background:#2a4a35;color:#fff}
    nav.sidebar .part{color:#7ec99a;font-weight:700;margin:12px 0 4px;font-size:8pt}
    main{flex:1;padding:24px 36px 100px;max-width:960px}
    h1{font-size:20pt;border-bottom:4px solid #1a6b3c;padding-bottom:10px}
    h2{font-size:14pt;background:#2c3e50;color:#fff;padding:10px 14px;margin:36px 0 14px;border-radius:4px}
    h3{font-size:11.5pt;color:#1a5;border-left:5px solid #1a6b3c;padding-left:10px;margin:20px 0 8px}
    .meta,.note,.warn,.goal{padding:12px 16px;margin:12px 0;border-radius:8px;font-size:10pt}
    .meta{background:#f0f7f2}.note{background:#fafafa;border-left:4px solid #1a6b3c}
    .warn{background:#fff8f0;border-left:4px solid #e67e22}
    .goal{background:#e8f4ec;border:1px solid #b8d4c4}
    pre.code{background:#1e2a22;color:#d4ecd8;padding:12px 16px;border-radius:8px;overflow-x:auto;font-size:8.5pt;line-height:1.45}
    pre.code-sm{background:#f4f8f5;border:1px solid #ccc;padding:10px;overflow-x:auto;font-size:7.5pt;line-height:1.35;max-height:400px;overflow-y:auto}
    .data-table{width:100%;border-collapse:collapse;font-size:9pt;margin:10px 0 18px}
    .data-table th{background:#1a6b3c;color:#fff;padding:7px 9px;text-align:left}
    .data-table td{border:1px solid #ddd;padding:6px 9px;vertical-align:top}
    .data-table tr:nth-child(even){background:#fafcfa}
    .mono{font-family:Consolas,monospace;color:#055;font-size:8.5pt}
    .kind{font-size:8pt;color:#666}
    .flow-box{background:#f5f5f5;border-radius:8px;padding:14px;overflow-x:auto;margin:10px 0}
    .flow-pre{font-family:Consolas,monospace;font-size:8.5pt;margin:0;white-space:pre;line-height:1.5}
    details.case-item{margin:6px 0;border:1px solid #ccc;border-radius:6px;padding:0 12px 10px;background:#fafafa}
    details.case-item>summary{cursor:pointer;padding:8px 4px;list-style:none;font-size:9.5pt}
    details.case-item>summary::-webkit-details-marker{display:none}
    .mermaid-wrap{background:#fff;border:1px solid #ddd;border-radius:8px;padding:16px;margin:12px 0;overflow-x:auto}
    .pattern-card{border:1px solid #c8e0d0;border-radius:8px;padding:12px;margin:10px 0;background:#fafcfa}
    .trap-card{border-left:4px solid #e67e22;padding:8px 12px;margin:8px 0;background:#fffaf5}
    a.ext{color:#1a6b3c}
    @media print{nav.sidebar{display:none}main{max-width:100%}h2{page-break-before:always}}
  `;

  const mermaid = `<script src="https://cdn.jsdelivr.net/npm/mermaid@10/dist/mermaid.min.js"></script>
<script>mermaid.initialize({startOnLoad:true,theme:'base',themeVariables:{primaryTextColor:'#111',fontSize:'12px'}});</script>`;

  let body = `
<h1>MX SRM 전체코드 학습가이드 — 완전판 <span style="font-size:13pt;color:#666">${TODAY_DISP}</span></h1>
<div class="meta">
  Ver 4.4 | RunMode case <b>${runCases.length}</b>개 추출 | dev_SRM.c <b>${countLines(DEV_SRM).toLocaleString()}</b>줄 |
  com_tml.c <b>${countLines(COM_TML).toLocaleString()}</b>줄
</div>

<div class="goal" id="intro">
<h3 style="margin-top:0;border:none;padding:0">이 문서의 목적</h3>
<p><b>큰 흐름 → 작은 흐름</b> 순으로, AI 없이 이 펌웨어와 타 설비 제어를 스스로 짤 수 있게 하는 <b>완전판 학습 HTML</b>.</p>
<ul>
<li><b>Part A~I</b>: 개념·시간축·통신·상태머신 (사람이 쓴 해설)</li>
<li><b>Part G</b>: dev_SRM.c에서 <b>자동 추출</b>한 ${runCases.length}개 case 소스·전이</li>
<li><b>심볼 사전</b>: Ctrl+F로 이름 검색 (<a href="SRM_전체심볼_용도사전.html">링크</a>)</li>
</ul>
<p><b>읽는 법</b>: A(3층·시간) → B(0x41) → C(0x50) → D(루프) → F(GET표) → G(case 펼치기)</p>
</div>

<h2 id="curriculum">4주 학습 로드맵</h2>
<div class="note"><b>1주</b> Part A+D + 심볼사전 섹션0 |
<b>2주</b> Part B+C+H (0x41/0x50) |
<b>3주</b> Part E+F+G (PREPARE~GET case) |
<b>4주</b> Part I + 연습 + case 주석 달기</div>

<div class="mermaid-wrap"><pre class="mermaid">
flowchart TB
  subgraph G["지상반"]
    A41["0x41 명령"]
    A50["0x50 Start"]
    A30["0x30 폴링"]
  end
  subgraph M["MCU"]
    TML["com_tml"]
    WD["m_WorkData"]
    RM["SRM_RunMode"]
    ST["m_St"]
  end
  A41-->TML-->WD
  A50-->RM
  RM-->ST
  ST-->A30
</pre></div>

${buildThreeLayersDeep()}
${buildRxCmdOrderDeep()}
${buildStartOnDeep()}
${buildMainLoopDeep()}
${buildPrepareMoveDeep()}
${buildLoadingFlowTable()}
${buildPutFlowTable()}
${buildAllRunCaseIndex(runCases, devText, runSeq)}
${buildTmlTable(tmlHandlers)}
${buildStoreSaveChapter(stores, saves)}
${buildForkStepTable(forkSteps, workStatus)}
${buildFileTable()}
${buildStructEight()}

<h2 id="patterns">코딩 패턴</h2>
${PATTERNS.map((p) => `<div class="pattern-card"><h4>${esc(p.title)}</h4><pre class="code">${esc(p.code)}</pre><p>${esc(p.explain)}</p></div>`).join("")}

<h2 id="traps">명명 함정</h2>
${TRAPS.map((t) => `<div class="trap-card"><div class="mono">${esc(t.name)}</div><b>함정</b>: ${esc(t.trap)}<br><b>실제</b>: ${esc(t.real)}</div>`).join("")}

<h2 id="exercise">연습문제</h2>
<details><summary>0x41 후 RunMode는?</summary><p>STAND_BY (Start 전)</p></details>
<details><summary>실행 레시피 변수?</summary><p>m_WorkData (static)</p></details>
<details><summary>지상반 스텝 보고 함수?</summary><p>Save_ForkWork_OrderProcess</p></details>
<details><summary>nFlag 0x03?</summary><p>주행+승강 브레이크 둘 다 해제 확인</p></details>

<h2 id="transfer">타 설비 이식</h2>
<p>명령→큐→상태머신→보고 4층, RunMode switch, nFlag 에러, timer1ms — SRM에서 완성형 패턴.</p>
`;

  return {
    body,
    css,
    mermaid,
    nav: buildNav(),
    meta: {
      runCases: runCases.length,
      tmlHandlers: tmlHandlers.length,
      devLines: countLines(DEV_SRM),
      tmlLines: countLines(COM_TML),
    },
    sources: { devText, tmlText, alarmText, userDef, runSeq, runCases, tmlHandlers, stores, saves, forkSteps, workStatus },
  };
}

function main() {
  const g = buildLearningGuide();
  const html = `<!DOCTYPE html><html lang="ko"><head><meta charset="utf-8">
<title>SRM 전체코드 학습가이드 완전판 ${TODAY_DISP}</title><style>${g.css}</style></head>
<body><div class="layout"><nav class="sidebar">${g.nav}</nav><main>${g.body}</main></div>${g.mermaid}</body></html>`;

  const outName = `SRM_전체코드_학습가이드_완전판_${TODAY}.html`;
  const outPath = path.join(OUT, outName);
  fs.writeFileSync(outPath, html, "utf8");
  fs.writeFileSync(path.join(OUT, `SRM_전체코드_학습가이드_${TODAY}.html`), html, "utf8");

  const mb = (fs.statSync(outPath).size / 1024 / 1024).toFixed(2);
  console.log(`Done: ${outPath}`);
  console.log(`Cases: ${g.meta.runCases}, Size: ${mb} MB`);
}

module.exports = {
  ROOT,
  CORE,
  INC,
  SRC,
  OUT,
  DEV_SRM,
  COM_TML,
  ALARM,
  MAIN,
  TODAY,
  TODAY_DISP,
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
  findIncomingTransitions,
  buildLearningGuide,
  buildNav,
  buildThreeLayersDeep,
  buildRxCmdOrderDeep,
  buildStartOnDeep,
  buildMainLoopDeep,
  buildPrepareMoveDeep,
  buildLoadingFlowTable,
  buildPutFlowTable,
  buildAllRunCaseIndex,
  buildTmlTable,
  buildStoreSaveChapter,
  buildForkStepTable,
  buildFileTable,
  buildStructEight,
  RUN_GROUPS,
  PATTERNS,
  TRAPS,
};

if (require.main === module) main();
