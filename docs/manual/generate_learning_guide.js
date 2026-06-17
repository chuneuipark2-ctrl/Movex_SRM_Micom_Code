/**
 * SRM 전체코드 학습가이드 HTML 생성
 * 출력: SRM_전체코드_학습가이드_YYYYMMDD.html
 */
const fs = require("fs");
const path = require("path");

const ROOT = path.resolve(__dirname, "..", "..");
const CORE = path.join(ROOT, "Core");
const INC = path.join(CORE, "Inc");
const SRC = path.join(CORE, "Src");
const OUT = __dirname;

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

function parseRunSeq(text) {
  const items = [];
  const start = text.indexOf("enum enumSRM_RUN_SEQ");
  if (start < 0) return items;
  const body = text.slice(start);
  const end = body.indexOf("};");
  const block = body.slice(0, end);
  for (const line of block.split("\n")) {
    const m = line.match(/^\s*(RUN_SEQ_\w+)(?:\s*=\s*(\d+))?\s*(?:,\s*(?:\/\/(.*))?)?$/);
    if (!m) continue;
    items.push({ name: m[1], val: m[2] || "", comment: (m[3] || "").trim() });
  }
  return items;
}

function countLines(fp) {
  return read(fp).split("\n").length;
}

function grepCount(symbol, file) {
  const re = new RegExp(`\\b${symbol.replace(/[.*+?^${}()|[\]\\]/g, "\\$&")}\\b`, "g");
  return (read(file).match(re) || []).length;
}

const FILE_ROLES = {
  "main.c": { tier: 1, role: "부트·HAL·main 루프", desc: "전역변수 정의, 타이머 ISR, while(1)에서 Manager들 호출" },
  "dev_SRM.c": { tier: 1, role: "SRM 제어 본체", desc: "상태머신 SRM_Machine_Run_Process(), 축 제어, 작업 실행" },
  "com_tml.c": { tier: 1, role: "지상반 TML 통신", desc: "0x41 작업명령, 0x50 Start, 0x30 상태 응답" },
  "alarm.c": { tier: 1, role: "상태 기록·DI/DO", desc: "Save_* → m_St/BKPSRAM, DI 채터링, 에러 저장" },
  "SRM_Parameter.c": { tier: 2, role: "파라미터 Flash", desc: "m_ExtSEnv0~2 읽기/쓰기, 셀·랙·스테이션 설정" },
  "ecat_main.c": { tier: 2, role: "EtherCAT 마스터", desc: "인버터 PDO 송수신, m_SRM_TxPDO/RxPDO" },
  "encoder.c": { tier: 2, role: "엔코더", desc: "위치 피드백 PDO" },
  "rtc.c": { tier: 2, role: "BKPSRAM", desc: "정전 복구 데이터 saveBKSramBlock()" },
  "com_hmi.c": { tier: 2, role: "HMI Modbus", desc: "MW 레지스터 ↔ m_St 비트맵" },
  "com_udp.c": { tier: 3, role: "UDP 통신", desc: "이더넷 보조 통신" },
  "fpga.c": { tier: 3, role: "FPGA", desc: "FPGA 레지스터, TCP 스택 연동" },
  "upgrade.c": { tier: 3, role: "펌웨어 다운로드", desc: "TY_DOWNLOAD_* 처리" },
  "Mcu_Test.c": { tier: 3, role: "MCU 자가진단", desc: "m_McuTestCtr/St" },
};

const RUN_GROUPS = [
  {
    id: "standby",
    title: "대기·시작",
    color: "#e8f4ec",
    members: ["RUN_SEQ_STAND_BY", "RUN_SEQ_START"],
    desc: "지상반 0x50 Start 수신 전 대기. Start 후 작업 분석 시작.",
  },
  {
    id: "prepare",
    title: "이동 준비 (주행·승강)",
    color: "#fff8e6",
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
    ],
    desc: "InPosition 판단, 브레이크 해제, 딜레이, 주행·승강 이동, 안정화.",
  },
  {
    id: "loading",
    title: "적재 (GET)",
    color: "#e6f0ff",
    members: [
      "RUN_SEQ_FORK_START",
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
    desc: "인터록 → 포크 진출 → 리프트 업 → 포크 복귀 → 화물 확인.",
  },
  {
    id: "unloading",
    title: "이재 (PUT)",
    color: "#f0e6ff",
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
    desc: "인터록 → 포크 진출 → 리프트 다운 → 포크 복귀 → 공출고 확인.",
  },
  {
    id: "complete",
    title: "완료·PLC",
    color: "#e8ffe8",
    members: ["RUN_SEQ_COMPLETE", "RUN_SEQ_PLC_COM_0", "RUN_SEQ_PLC_COM_1", "RUN_SEQ_PLC_COM_2", "RUN_SEQ_PLC_COM_3"],
    desc: "작업 완료 보고, PLC 연동 통신.",
  },
  {
    id: "error",
    title: "에러 정지",
    color: "#ffe6e6",
    members: [
      "RUN_SEQ_ERROR_FORK_STOP",
      "RUN_SEQ_ERROR_TRAV_LIFF_STOP",
      "RUN_SEQ_ERROR_TRAV_LIFT_STOP_1",
      "RUN_SEQ_ERROR_TRAV_LIFT_STOP_2",
      "RUN_SEQ_ERROR_TRAV_LIFT_STOP_3",
    ],
    desc: "축별 정지, 브레이크 체결, 속도 0 확인 후 에러 상태 유지.",
  },
  {
    id: "origin",
    title: "원점·설정",
    color: "#f5f5f5",
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
    desc: "축별 원점 설정, 수평 설정, 자동 랙 설정.",
  },
  {
    id: "home",
    title: "홈복귀",
    color: "#fff0e6",
    members: [
      "RUN_SEQ_RETURN_HOME_0",
      "RUN_SEQ_RETURN_HOME_0_1",
      "RUN_SEQ_RETURN_HOME_0_2",
      "RUN_SEQ_RETURN_HOME_1",
      "RUN_SEQ_RETURN_HOME_MOVING",
      "RUN_SEQ_RETURN_HOME_3",
      "RUN_SEQ_RETURN_HOME_4",
    ],
    desc: "에러/완료 후 홈 위치 복귀. 브레이크 해제 확인 포함.",
  },
  {
    id: "misc",
    title: "수동·시험·스캔",
    color: "#f0f0f0",
    members: [
      "RUN_SEQ_MANUAL_MOVE",
      "RUN_SEQ_FORK_PUT_MOVE_ST_0",
      "RUN_SEQ_FORK_PUT_MOVE_ST_1",
      "RUN_SEQ_FORK_PUT_MOVE_ST_2",
      "RUN_SEQ_FORK_PUT_MOVE_ST_3",
      "RUN_SEQ_FORK_PUT_MOVE_ST_4",
      "RUN_SEQ_FORK_PUT_MOVE_ST_5",
      "RUN_SEQ_FORK1_CHECK_CENTER_0",
      "RUN_SEQ_FORK1_CHECK_CENTER_1",
      "RUN_SEQ_FORK2_CHECK_CENTER_0",
      "RUN_SEQ_FORK2_CHECK_CENTER_1",
      "RUN_SEQ_FORK_ERROR_CENTER",
      "RUN_SEQ_FORK_TEST_0",
      "RUN_SEQ_FORK_TEST_1",
      "RUN_SEQ_FORK_TEST_2",
      "RUN_SEQ_FORK_TEST_3",
      "RUN_SEQ_FORK_TEST_4",
      "RUN_SEQ_TRAV_SCAN_SENSOR_0",
      "RUN_SEQ_TRAV_SCAN_SENSOR_1",
      "RUN_SEQ_TRAV_SCAN_SENSOR_STOP",
      "RUN_SEQ_LIFT_SCAN_SENSOR_0",
      "RUN_SEQ_LIFT_SCAN_SENSOR_1",
      "RUN_SEQ_LIFT_SCAN_SENSOR_STOP",
      "RUN_SEQ_FORK_SCAN_SENSOR_0",
      "RUN_SEQ_FORK_SCAN_SENSOR_1",
      "RUN_SEQ_FORK_SCAN_SENSOR_STOP",
    ],
    desc: "수동 이동, 포크 센터 확인, 센서 스캔, 시험 모드.",
  },
];

const PATTERNS = [
  {
    title: "RunMode case (상태머신 한 스텝)",
    file: "dev_SRM.c",
    code: `case RUN_SEQ_XXX:
    if (getCalcTimer1ms(m_pgmEnv.SRM_RunTimer) > DELAY_MS)
    {
        // 조건 검사
        if (조건_OK)
            m_pgmEnv.SRM_RunMode = RUN_SEQ_다음;
        else
            save_error_code(ERROR1_*, sub, nFlag);
    }
    break;`,
    explain:
      "모든 자동 시퀀스의 기본 뼈대. SRM_RunTimer로 경과시간 측정, 조건 만족 시 RunMode만 바꿔 다음 case로 넘김. break 필수.",
  },
  {
    title: "비트 플래그 nFlag (축/센서 상태 묶음)",
    file: "main.c cbits[]",
    code: `nFlag = 0;
if (Get_Motor_Brake_Release(INV_TRAVEL))  nFlag |= cbits[0]; // bit0=주행
if (Get_Motor_Brake_Release(INV_HOIST))     nFlag |= cbits[1]; // bit1=승강
// 0x00=둘다미해제, 0x01=주행만, 0x02=승강만, 0x03=둘다해제
save_error_code(ERROR1_WORK_TIMEOUT, 1, nFlag); // 서브코드로 전달`,
    explain:
      "여러 축 상태를 한 바이트에 담아 에러 서브코드로 넘김. cbits[n]=1<<n. negative/방향과 무관.",
  },
  {
    title: "Store_* vs Save_*",
    file: "dev_SRM.c / alarm.c",
    code: `// Store: 내부 작업 큐 적재 (지상반에 안 나감)
Store_Work_Data_1(...);  // → m_WorkData[s_WorkInx]

// Save: 지상반 보고용 상태 기록 (0x30 폴링으로 읽힘)
Save_ForkWork_OrderProcess(0, CMD_FORK_STEP_MOVING_FROM);`,
    explain:
      "Store=실행 데이터 준비, Save=WCS에 보여줄 진행상태. 혼동하면 디버깅 지옥.",
  },
  {
    title: "타이머 패턴",
    file: "전역",
    code: `m_pgmEnv.SRM_RunTimer = m_pgmEnv.timer1ms;  // 시작 시각 기록
// ... 나중에 case 안에서:
if (getCalcTimer1ms(m_pgmEnv.SRM_RunTimer) > 3000) { ... }`,
    explain:
      "timer1ms는 1ms ISR에서 증가. getCalcTimer1ms는 오버플로 안전 경과시간. 모든 딜레이/타임아웃의 기반.",
  },
  {
    title: "서브 시퀀스 (축별)",
    file: "dev_SRM.c",
    code: `m_Trav_Sub_Run_Step = 10;   // 주행 서브스텝
m_Lift_Sub_Run_Step = 20;    // 승강 서브스텝
m_Fork_Sub_Run_Step = 30;    // 포크 서브스텝`,
    explain:
      "RunMode는 큰 흐름, Sub_Run_Step은 한 축의 세부 제어(가속/감속/정위치). 이중 상태머신 구조.",
  },
  {
    title: "인버터 제어 호출",
    file: "dev_SRM.c",
    code: `Motor_Brake_Release(INV_TRAVEL);     // 브레이크 해제 명령
Get_Motor_Brake_Release(INV_TRAVEL);     // 1=해제됨, 0=걸림
Auto_Ctr_Travel(TargetPos, Speed);     // 자동 위치 제어
Motor_Application_Stop(INV_TRAVEL, vel);`,
    explain:
      "EtherCAT PDO를 통해 SEW/MOVI 인버터 제어. Vendor별 분기는 Get_Motor_Brake_Release 안에 캡슐화.",
  },
];

const NAMING_TRAPS = [
  {
    name: "GoodsFlag_Or_MoveHome",
    trap: "이름은 '화물 OR 홈이동' 같지만 축마다 의미 다름",
    real: "포크=화물유무, 주행/승강=홈복귀중 플래그. 반드시 축(INV_*) 맥락에서 읽을 것.",
  },
  {
    name: "Rack_fork_obstruction",
    trap: "랙-포크 물리적 간섭 센서 같음",
    real: "WCS가 '이미 InPosition'이라 스킵하려 할 때 MCU가 '그래도 이동해야 함' 표시. 1이면 InPosition이어도 재이동.",
  },
  {
    name: "ENABLE_TRAV_LEFT_MOVE_BRAKE_RELEASE",
    trap: "좌측 이동 시에만 브레이크 해제",
    real: "컴파일 옵션(0/1). 주행+승강 이동 전 브레이크 해제 확인 서브시퀀스 on/off. LEFT는 레거시 네이밍.",
  },
  {
    name: "Save_* vs Store_*",
    trap: "둘 다 '저장' 같음",
    real: "Save=m_St 지상반 보고, Store=m_WorkData 내부 큐.",
  },
  {
    name: "SRM_TaskMode / 0x40",
    trap: "RunMode와 같은 것",
    real: "0x40 Task Order 전용. 일반 0x41 작업과 별도 경로.",
  },
  {
    name: "RETURN_HOME vs ORIGIN",
    trap: "둘 다 홈",
    real: "ORIGIN=축 원점 설정(기준점 잡기), RETURN_HOME=운전 중 홈 위치로 복귀.",
  },
  {
    name: "TRAV_MOVE_FORWARD / REVERSE",
    trap: "좌/우 방향",
    real: "엔코더 좌표 기준 TargetPos > StartPos면 FORWARD. 현장 좌/우는 파라미터·설치 방향에 따름.",
  },
  {
    name: "m_pgmEnv vs m_St",
    trap: "둘 다 상태",
    real: "m_pgmEnv=MCU 내부( RunMode, 타이머, 통신링크). m_St=지상반에 보여주는 얼굴.",
  },
];

const EXERCISES = [
  { q: "지상반 작업명령(0x41)을 처음 받는 함수는?", a: "com_tml.c → rxCmdOrder()", hint: "TY_CMD_ORDER case" },
  { q: "0x50 Start를 받으면 RunMode가 어디로 바뀌나?", a: "RUN_SEQ_START (com_tml.c rxCmdStart)", hint: "SRM_RunMode =" },
  { q: "실제 이번 사이클 작업 데이터는 어디에?", a: "dev_SRM.c static m_WorkData[30]", hint: "Store_Work_Data" },
  { q: "지상반 0x30 폴링으로 읽는 상태 구조체는?", a: "m_St (StatusSTR)", hint: "TY_STATUS_REQ" },
  { q: "상태머신 본체 함수는?", a: "SRM_Machine_Run_Process() in dev_SRM.c", hint: "switch(m_pgmEnv.SRM_RunMode)" },
  { q: "RunMode enum 정의 헤더는?", a: "dev_SRM.h → enumSRM_RUN_SEQ", hint: "RUN_SEQ_STAND_BY" },
  { q: "에러 코드 ERROR1_* 정의 헤더는?", a: "error_code.h", hint: "save_error_code" },
  { q: "cbits[0]의 값은?", a: "0x01 (bit0 마스크)", hint: "main.c const INT08U cbits" },
  { q: "InPosition인데도 주행·승강을 다시 이동시키는 플래그?", a: "m_WorkData[].Rack_fork_obstruction", hint: "PREPARE_MOVE_0" },
  { q: "정전 복구용 백업 SRAM 미러?", a: "m_BKSram (BKSRamSTR)", hint: "rtc.c saveBKSramBlock" },
  { q: "주행·승강·포크 파라미터 3분할?", a: "m_ExtSEnv0(주행/랙), m_ExtSEnv1(승강/스테이션), m_ExtSEnv2(포크/제어)", hint: "ExtFlashSEnv" },
  { q: "main while(1)에서 SRM 제어 진입점?", a: "SRM_Manager() → SRM_Machine_Run_Process()", hint: "main.c 843행 근처" },
];

function buildRunSeqTable(allRunSeq) {
  const nameSet = new Map(allRunSeq.map((r) => [r.name, r]));
  let html = "";
  for (const g of RUN_GROUPS) {
    html += `<details class="run-group" open><summary><b>${esc(g.title)}</b> — ${esc(g.desc)}</summary>`;
    html += `<table class="data-table"><thead><tr><th>RunMode</th><th>값</th><th>주석</th><th>dev_SRM.c case</th></tr></thead><tbody>`;
    for (const name of g.members) {
      const r = nameSet.get(name) || { name, val: "", comment: "" };
      const hasCase = grepCount(name, path.join(SRC, "dev_SRM.c")) > 0;
      html += `<tr>
        <td class="mono">${esc(r.name)}</td>
        <td>${esc(r.val || "auto")}</td>
        <td>${esc(r.comment || "-")}</td>
        <td>${hasCase ? "✓ case 있음" : "enum만/간접"}</td>
      </tr>`;
    }
    html += `</tbody></table></details>`;
  }
  // ungrouped
  const grouped = new Set(RUN_GROUPS.flatMap((g) => g.members));
  const rest = allRunSeq.filter((r) => !grouped.has(r.name));
  if (rest.length) {
    html += `<details class="run-group"><summary><b>기타 RunMode</b> (${rest.length}개)</summary><ul>`;
    for (const r of rest) html += `<li class="mono">${esc(r.name)}${r.comment ? " — " + esc(r.comment) : ""}</li>`;
    html += `</ul></details>`;
  }
  return html;
}

function buildFileTable() {
  const files = fs.readdirSync(SRC).filter((f) => f.endsWith(".c")).sort();
  let html = `<table class="data-table"><thead><tr>
    <th>우선순위</th><th>파일</th><th>줄수</th><th>역할</th><th>설명</th>
  </tr></thead><tbody>`;
  for (const f of files) {
    const info = FILE_ROLES[f] || { tier: 4, role: "보조/인프라", desc: "HAL, 통신 하위, 유틸" };
    const tierLabel = info.tier === 1 ? "★★★ 필수" : info.tier === 2 ? "★★ 중요" : info.tier === 3 ? "★ 참고" : "인프라";
    html += `<tr>
      <td>${tierLabel}</td>
      <td class="mono">${esc(f)}</td>
      <td>${countLines(path.join(SRC, f)).toLocaleString()}</td>
      <td>${esc(info.role)}</td>
      <td>${esc(info.desc)}</td>
    </tr>`;
  }
  html += `</tbody></table>`;
  return html;
}

function main() {
  const runSeq = parseRunSeq(read(path.join(INC, "dev_SRM.h")));
  const devLines = countLines(path.join(SRC, "dev_SRM.c"));
  const tmlLines = countLines(path.join(SRC, "com_tml.c"));

  const css = `
    * { box-sizing: border-box; }
    body { font-family: "Malgun Gothic", "Apple SD Gothic Neo", sans-serif; margin: 0; color: #111; line-height: 1.65; }
    .layout { display: flex; min-height: 100vh; }
    nav.sidebar { width: 280px; background: #1a2e1f; color: #e8f0ea; position: sticky; top: 0; height: 100vh;
      overflow-y: auto; padding: 16px 12px; flex-shrink: 0; font-size: 9.5pt; }
    nav.sidebar a { color: #b8dcc8; text-decoration: none; display: block; padding: 3px 8px; border-radius: 4px; }
    nav.sidebar a:hover { background: #2a4a35; color: #fff; }
    nav.sidebar .part { color: #7ec99a; font-weight: 700; margin: 14px 0 4px; font-size: 8.5pt; text-transform: uppercase; }
    main { flex: 1; padding: 28px 40px 80px; max-width: 1100px; }
    h1 { font-size: 22pt; border-bottom: 4px solid #1a6b3c; padding-bottom: 12px; margin-top: 0; }
    h2 { font-size: 15pt; background: #2c3e50; color: #fff; padding: 10px 16px; margin: 40px 0 16px; border-radius: 4px; }
    h3 { font-size: 12pt; color: #1a5; border-left: 5px solid #1a6b3c; padding-left: 10px; margin: 24px 0 10px; }
    h4 { font-size: 11pt; color: #333; margin: 16px 0 8px; }
    .meta { background: #f0f7f2; padding: 12px 16px; border-radius: 8px; margin-bottom: 24px; font-size: 10pt; }
    .note { background: #fafafa; border-left: 4px solid #1a6b3c; padding: 12px 16px; margin: 12px 0; font-size: 10pt; }
    .warn { background: #fff8f0; border-left: 4px solid #e67e22; padding: 12px 16px; margin: 12px 0; }
    .goal { background: #e8f4ec; border: 1px solid #b8d4c4; border-radius: 8px; padding: 16px 20px; margin: 16px 0; }
    pre.code { background: #1e2a22; color: #d4ecd8; padding: 14px 18px; border-radius: 8px; overflow-x: auto;
      font-family: Consolas, "Courier New", monospace; font-size: 9pt; line-height: 1.5; }
    .data-table { width: 100%; border-collapse: collapse; font-size: 9.5pt; margin: 12px 0 20px; }
    .data-table th { background: #1a6b3c; color: #fff; padding: 8px 10px; text-align: left; }
    .data-table td { border: 1px solid #ddd; padding: 7px 10px; vertical-align: top; }
    .data-table tr:nth-child(even) { background: #fafcfa; }
    .mono { font-family: Consolas, monospace; color: #055; font-size: 9pt; }
    .flow-box { background: #f5f5f5; border-radius: 8px; padding: 16px; overflow-x: auto; margin: 12px 0; }
    .flow-pre { font-family: Consolas, monospace; font-size: 9pt; margin: 0; line-height: 1.55; white-space: pre; }
    .mermaid-wrap { background: #fff; border: 1px solid #ddd; border-radius: 8px; padding: 20px; margin: 16px 0; overflow-x: auto; }
    details.run-group { margin: 10px 0; border: 1px solid #ccc; border-radius: 6px; padding: 0 12px 10px; }
    details.run-group > summary { cursor: pointer; padding: 10px 4px; font-size: 10.5pt; }
    .pattern-card { border: 1px solid #c8e0d0; border-radius: 8px; padding: 14px 18px; margin: 14px 0; background: #fafcfa; }
    .pattern-card h4 { margin-top: 0; color: #1a5; }
    .trap-card { border-left: 4px solid #e67e22; padding: 10px 14px; margin: 10px 0; background: #fffaf5; }
    .trap-card .name { font-family: Consolas, monospace; font-weight: 700; color: #c0392b; }
    .week-card { border: 1px solid #ddd; border-radius: 8px; padding: 14px; margin: 10px 0; }
    .week-card b { color: #1a5; }
    .exercise details { margin: 8px 0; border: 1px solid #eee; border-radius: 6px; padding: 8px 12px; }
    .exercise summary { cursor: pointer; font-weight: 600; }
    .tier1 { background: #e8f4ec !important; }
    a.ext { color: #1a6b3c; }
    @media print { nav.sidebar { display: none; } main { max-width: 100%; } h2 { page-break-before: always; } }
  `;

  const mermaidScript = `
<script src="https://cdn.jsdelivr.net/npm/mermaid@10/dist/mermaid.min.js"></script>
<script>mermaid.initialize({startOnLoad:true,theme:'base',themeVariables:{primaryColor:'#e8f4ec',primaryTextColor:'#111',primaryBorderColor:'#1a6b3c',lineColor:'#333',secondaryColor:'#f5f5f5',tertiaryColor:'#fff',fontSize:'13px'}});</script>`;

  const nav = `
<div class="part">시작</div>
<a href="#intro">이 가이드 목적</a>
<a href="#relation">사전과의 관계</a>
<a href="#curriculum">4주 학습 로드맵</a>
<div class="part">Part 1 — 아키텍처</div>
<a href="#arch">시스템 전체 구조</a>
<a href="#mainloop">main 루프·Manager</a>
<a href="#dataflow">데이터 3층</a>
<a href="#structs">핵심 8대 구조체</a>
<div class="part">Part 2 — 통신</div>
<a href="#tml">TML 프로토콜</a>
<a href="#cmd41">0x41 작업명령 흐름</a>
<a href="#cmd50">0x50 Start 흐름</a>
<a href="#cmd30">0x30 상태 보고</a>
<div class="part">Part 3 — 상태머신</div>
<a href="#runmode-intro">RunMode 개념</a>
<a href="#runmode-flow">자동운전 흐름도</a>
<a href="#runmode-table">RunMode 전체 표</a>
<a href="#prepare">PREPARE_MOVE 상세</a>
<a href="#get-cycle">GET 사이클</a>
<a href="#put-cycle">PUT 사이클</a>
<a href="#error-flow">에러·홈복귀</a>
<div class="part">Part 4 — 코드 읽기·쓰기</div>
<a href="#files">파일 맵·읽기 순서</a>
<a href="#patterns">코딩 패턴 6종</a>
<a href="#traps">명명 함정 8선</a>
<a href="#subseq">서브 시퀀스</a>
<a href="#grep">grep 추적법</a>
<a href="#order-work">ORDER↔WORK 매핑</a>
<a href="#save-funcs">Save_* API</a>
<a href="#get-detail">GET 전이 상세</a>
<a href="#inv-axes">인버터 4축</a>
<a href="#param">파라미터 3분할</a>
<a href="#new-step">새 step 설계법</a>
<a href="#tml-funcs">com_tml 함수</a>
<a href="#glossary">용어 사전</a>
<div class="part">Part 5 — 실전</div>
<a href="#debug">현장 디버깅 체크</a>
<a href="#exercise">연습문제</a>
<a href="#transfer">타 설비 이식</a>
<a href="#next">다음 단계</a>
<a class="ext" href="SRM_전체심볼_용도사전.html">→ 심볼 용도 사전</a>
<a class="ext" href="SRM_구조체트리.html">→ 구조체 트리</a>`;

  const body = `
<h1>MX SRM 전체코드 학습가이드 <span style="font-size:14pt;color:#666">${TODAY_DISP}</span></h1>
<div class="meta">
  <b>버전</b> MX SRM App Ver 4.4 &nbsp;|&nbsp;
  <b>MCU</b> STM32F767 &nbsp;|&nbsp;
  <b>RunMode</b> ${runSeq.length}개 &nbsp;|&nbsp;
  <b>dev_SRM.c</b> ${devLines.toLocaleString()}줄 &nbsp;|&nbsp;
  <b>com_tml.c</b> ${tmlLines.toLocaleString()}줄
</div>

<div class="goal" id="intro">
  <h3 style="margin-top:0;border:none;padding:0">이 문서의 목적</h3>
  <p><b>AI 없이, 다른 설비 제어를 맡아도 스스로 코드를 짜낼 수 있도록</b> 이 펌웨어 전체를 체계적으로 이해하는 학습 가이드입니다.</p>
  <ul>
    <li><b>사전(용도사전 HTML)</b> = 심볼이 <em>뭐냐</em> (Ctrl+F 도구)</li>
    <li><b>이 가이드</b> = 코드가 <em>왜 이렇게 짜였고, 어떤 순서로 읽고, 어떤 패턴으로 짜는지</em></li>
  </ul>
  <p>크레인/물류 설비 제어의 본질 — <b>명령 수신 → 내부 큐 → 상태머신 → 축 제어 → 상태 보고</b> — 을 이 코드에서 완성형으로 배웁니다.</p>
</div>

<div class="note" id="relation">
  <b>함께 쓰는 문서</b><br>
  • <a href="SRM_전체심볼_용도사전.html">SRM_전체심볼_용도사전.html</a> — 7,770항목 심볼 사전, 구조체 242개 트리<br>
  • <a href="SRM_구조체트리.html">SRM_구조체트리.html</a> — 구조체 포함관계만 가볍게<br>
  <b>읽는 법</b>: 이 가이드로 흐름을 잡고 → 막히는 심볼은 사전에서 검색
</div>

<h2 id="curriculum">4주 학습 로드맵</h2>
<div class="week-card"><b>1주차 — 뼈대 잡기</b><br>
  main.c while(1) → Manager 목록 → m_St / m_pgmEnv / m_WorkData 역할 구분<br>
  이 가이드 Part1 전체 + 심볼사전 섹션0(코드 전체 맵)</div>
<div class="week-card"><b>2주차 — 통신·명령</b><br>
  com_tml.c: TY_STATUS_REQ(0x30), TY_CMD_ORDER(0x41), TY_CMD_START(0x50)<br>
  rxCmdOrder → Store_Work_Data* → m_WorkData 채워지는 과정 추적</div>
<div class="week-card"><b>3주차 — 상태머신</b><br>
  dev_SRM.c SRM_Machine_Run_Process() switch 전체<br>
  GET 1사이클: STAND_BY→START→PREPARE→MOVE→LOADING_*→COMPLETE 끝까지 따라가기</div>
<div class="week-card"><b>4주차 — 패턴·실전</b><br>
  코딩 패턴 6종 암기 수준으로 이해, 연습문제 풀기<br>
  직접 case 하나에 한글 주석 달며 읽기, 에러 경로 추적</div>

<h2 id="arch">Part 1 — 시스템 전체 구조</h2>
<h3>한 줄 요약</h3>
<p>STM32 MCU가 <b>지상반(TML UART)</b>에서 작업을 받고, <b>상태머신</b>으로 주행·승강·포크를 제어하며, <b>EtherCAT</b>으로 인버터를 돌리고, <b>0x30 폴링</b>으로 상태를 돌려준다.</p>

<div class="mermaid-wrap"><pre class="mermaid">
flowchart TB
  subgraph Ground["지상반 WCS"]
    CMD41["0x41 작업명령"]
    CMD50["0x50 Start"]
    POLL30["0x30 상태폴링"]
  end
  subgraph MCU["STM32F767"]
    TML["com_tml.c"]
    STORE["Store_Work_Data*"]
    WDATA["m_WorkData static"]
    RUN["SRM_Machine_Run_Process"]
    RUNMODE["m_pgmEnv.SRM_RunMode"]
    SAVE["Save_* alarm.c"]
    MST["m_St StatusSTR"]
    ECAT["ecat_main.c PDO"]
  end
  subgraph Field["현장"]
    TRAV["주행 인버터"]
    LIFT["승강 인버터"]
    FORK["포크 인버터"]
  end
  CMD41 --> TML --> STORE --> WDATA
  CMD50 --> TML --> RUN
  WDATA --> RUN
  RUN --> RUNMODE
  RUN --> ECAT --> TRAV & LIFT & FORK
  RUN --> SAVE --> MST
  POLL30 --> TML
  MST --> TML --> POLL30
</pre></div>

<h3>레이어 4단</h3>
<table class="data-table">
  <tr><th>레이어</th><th>역할</th><th>대표 파일</th><th>비유</th></tr>
  <tr class="tier1"><td>L1 통신</td><td>지상반·HMI·EtherCAT I/O</td><td>com_tml.c, com_hmi.c, ecat_main.c</td><td>전화 받는 교환원</td></tr>
  <tr class="tier1"><td>L2 논리</td><td>작업 해석, 상태머신, 조건검사</td><td>dev_SRM.c</td><td>두뇌·판단</td></tr>
  <tr class="tier1"><td>L3 상태</td><td>지상반 보고, BKPSRAM, 에러</td><td>alarm.c, rtc.c</td><td>일기장·얼굴</td></tr>
  <tr><td>L4 HW</td><td>HAL, FPGA, 타이머, Flash</td><td>main.c, fpga.c, flash.c</td><td>신체·근육</td></tr>
</table>

<h2 id="mainloop">main 루프와 Manager 체계</h2>
<pre class="code">// main.c while(1) — 매 사이클 반복
AlarmManager();      // DI/DO, 에러, Save_* 트리거
FpgaManager();       // FPGA 통신
McuComManager();     // MCU 보조 통신
TMLComManager();     // ★ 지상반 UART 수신/송신
EtherNetManager();   // 이더넷
ECAT_Manager();      // ★ 인버터 PDO 갱신
SRM_Manager();       // ★ SRM 제어 진입
  └─ SRM_Machine_Process()      // SSR/연결 등
  └─ SRM_Machine_Run_Process()  // ★★ 상태머신 본체
  └─ HMI_ModbusTCP_Proc()</pre>

<div class="note">
  <b>임베디드 관점</b>: super loop 구조. RTOS 태스크가 아니라 <b>while(1) 협력적 멀티태스킹</b>.
  상태머신은 <code>SRM_Machine_Run_Process()</code> 한 함수의 giant switch.
  1ms 타이머 ISR에서 <code>m_pgmEnv.timer1ms++</code> → 모든 딜레이의 시계.
</div>

<h2 id="dataflow">데이터 3층 — 반드시 구분</h2>
<div class="flow-box"><pre class="flow-pre">[입력층]  0x41 WorkCmdSTR  →  rxCmdOrder()  →  Store_Work_Data*()  →  m_WorkData[s_WorkInx]
                                                                              │
[실행층]  m_pgmEnv.SRM_RunMode (enumSRM_RUN_SEQ)  ←── SRM_Machine_Run_Process() switch
          m_pgmEnv.SRM_RunTimer, Sub_Run_Step (축별 서브시퀀스)
                                                                              │
[출력층]  Save_ForkWork_*() / Save_ForkMove_*()  →  m_St (StatusSTR)  →  0x30 응답
          save_error_code()  →  m_St 에러 + m_BKSram.AlarmLog</pre></div>

<div class="warn">
  <b>초보가 가장 많이 헷갈리는 것</b>: m_WorkData(실행용)와 m_St(보고용)를 동시에 본다.<br>
  디버깅 시 "지상반 화면에 뭐가 보이나" → m_St / "MCU가 실제 뭘 실행하나" → m_WorkData + RunMode
</div>

<h2 id="structs">핵심 8대 구조체</h2>
<table class="data-table">
  <tr><th>변수</th><th>타입</th><th>누가 씀</th><th>한 줄 역할</th></tr>
  <tr><td class="mono">m_St</td><td>StatusSTR</td><td>지상반 0x30</td><td>운전상태 얼굴. ForkWork[], Inv_St[], DI/DO</td></tr>
  <tr><td class="mono">m_pgmEnv</td><td>PGMEnvSTR</td><td>MCU 내부</td><td>RunMode, timer1ms, 통신링크, 내부 플래그</td></tr>
  <tr><td class="mono">m_WorkData</td><td>SRM_WorkDataSTR[30]</td><td>dev_SRM static</td><td>이번 사이클 작업 큐. ForkAct, TargetPos, DrvData</td></tr>
  <tr><td class="mono">m_BKSram</td><td>BKSRamSTR</td><td>rtc.c</td><td>정전복구. AlarmLog, WorkInfo</td></tr>
  <tr><td class="mono">m_ExtSEnv0</td><td>ExtFlashSEnv0</td><td>파라미터</td><td>랙·셀·주행 드라이브</td></tr>
  <tr><td class="mono">m_ExtSEnv1</td><td>ExtFlashSEnv1</td><td>파라미터</td><td>승강·스테이션·인터록</td></tr>
  <tr><td class="mono">m_ExtSEnv2</td><td>ExtFlashSEnv2</td><td>파라미터</td><td>포크·CtrParam·타임아웃</td></tr>
  <tr><td class="mono">WorkCmd</td><td>WorkCmdSTR</td><td>com_tml</td><td>0x41 수신 직후 원본. OrderCode, Fork[]</td></tr>
</table>
<p>멤버 상세 트리 → <a href="SRM_구조체트리.html">구조체 트리 HTML</a></p>

<h2 id="tml">Part 2 — TML 통신 (Vexi)</h2>
<h3>주요 TY_* 타입</h3>
<table class="data-table">
  <tr><th>코드</th><th>이름</th><th>방향</th><th>역할</th></tr>
  <tr><td>0x30</td><td>TY_STATUS_REQ</td><td>지상반→MCU</td><td>상태 폴링. m_St 기반 응답</td></tr>
  <tr><td>0x41</td><td>TY_CMD_ORDER</td><td>지상반→MCU</td><td>작업 명령. WorkCmdSTR 파싱</td></tr>
  <tr><td>0x50</td><td>TY_CMD_START</td><td>지상반→MCU</td><td>Start ON. RunMode=START</td></tr>
  <tr><td>0x51</td><td>TY_CMD_MOVE_HOME</td><td>지상반→MCU</td><td>홈 위치 이동</td></tr>
  <tr><td>0x52</td><td>TY_CMD_ERROR_RESET</td><td>지상반→MCU</td><td>에러 리셋</td></tr>
  <tr><td>0x53</td><td>TY_CMD_ORDER_DELETE</td><td>지상반→MCU</td><td>작업 삭제</td></tr>
  <tr><td>0x55</td><td>TY_EMERGENCY_STOP_REQ</td><td>지상반→MCU</td><td>비상정지</td></tr>
  <tr><td>0xA3~A8</td><td>파라미터</td><td>양방향</td><td>ExtSEnv 다운로드/업로드</td></tr>
</table>

<h2 id="cmd41">0x41 작업명령 수신 흐름</h2>
<div class="mermaid-wrap"><pre class="mermaid">
sequenceDiagram
  participant WCS as 지상반
  participant TML as com_tml rxCmdOrder
  participant Store as Store_Work_Data*
  participant WD as m_WorkData
  WCS->>TML: TY_CMD_ORDER 0x41
  TML->>TML: STAND_BY? Auto? Fault? ForkCenter?
  alt 수락
    TML->>Store: OrderCode별 분기
    Store->>WD: ForkAct, TargetPos, From/To Step
    TML-->>WCS: accept OK
  else 거부
    TML-->>WCS: COMMAND_ERROR_*
  end
</pre></div>

<p><b>rxCmdOrder() 진입 조건 (거부 사유)</b>:</p>
<ul>
  <li>Fault 상태, Manual SW, RunMode≠STAND_BY, 포크 센터 이탈, Auto 모드 아님</li>
  <li>GET/PUT 시 StartOn==0 이면 NON_ONLINE</li>
  <li>화물 센서 이상 (GoodsFlag, DISABLE 설정 시 생략)</li>
</ul>
<p>수락 후 <code>Store_Work_Data / Store_Work_Data_1 / Store_Work_Data_Fix</code> 등 OrderCode·ForkAct에 따라 m_WorkData 채움.</p>

<h2 id="cmd50">0x50 Start 흐름</h2>
<pre class="code">// com_tml.c rxCmdStart() 요지
m_pgmEnv.SRM_RunMode = RUN_SEQ_START;
// 이후 dev_SRM.c SRM_Machine_Run_Process()의 case RUN_SEQ_START: 에서
// m_WorkData[s_WorkInx].ForkAct 에 따라 LOADING/UNLOADING/MOVE 분기</pre>

<h2 id="cmd30">0x30 상태 보고</h2>
<p>지상반이 주기 폴링 → MCU가 <code>m_St</code> 내용을 패킷으로 응답.</p>
<ul>
  <li><code>m_St.ForkWork[i]</code> — 작업별 OrderStatus, OrderProcess(스텝)</li>
  <li><code>m_St.Inv_St[4]</code> — 축별 위치·속도·GoodsFlag</li>
  <li><code>m_St.SRM_Status1/2</code> — Auto, StartOn, Fault 비트</li>
</ul>
<p><b>Save_*</b> 함수가 m_St를 갱신. UART로 즉시 push가 아니라 <b>다음 0x30 폴링</b> 때 반영.</p>

<h2 id="runmode-intro">Part 3 — RunMode (상태머신)</h2>
<h3>개념</h3>
<p><code>m_pgmEnv.SRM_RunMode</code> = enum <code>enumSRM_RUN_SEQ</code> (dev_SRM.h, ${runSeq.length}개)</p>
<p><code>SRM_Machine_Run_Process()</code> = <b>거대한 switch-case</b>. 매 main 루프마다 현재 case <b>한 스텝</b>만 실행.</p>
<p>case 안에서 조건 충족 시 <code>m_pgmEnv.SRM_RunMode = 다음값</code> 으로 전이. <b>break 필수.</b></p>

<h2 id="runmode-flow">자동운전 전체 흐름도</h2>
<div class="mermaid-wrap"><pre class="mermaid">
stateDiagram-v2
  [*] --> STAND_BY
  STAND_BY --> START: 0x50 Start
  START --> PREPARE_MOVE_0: 작업분석완료
  PREPARE_MOVE_0 --> BRAKE_RELEASE: ENABLE옵션
  PREPARE_MOVE_0 --> MOVE_DELAY: InPosition스킵
  BRAKE_RELEASE --> MOVE_DELAY: nFlag==0x03
  MOVE_DELAY --> START_MOVE_0
  START_MOVE_0 --> TRAV_LIFT_MOVING
  TRAV_LIFT_MOVING --> TRAV_LIFT_AFTER_MOVE: 도착
  TRAV_LIFT_AFTER_MOVE --> FORK_START: 이동완료
  FORK_START --> LOADING: GET
  FORK_START --> UNLOADING: PUT
  LOADING --> COMPLETE: LOAD_COMPLETE
  UNLOADING --> COMPLETE: UNLOAD_COMPLETE
  COMPLETE --> STAND_BY: 사이클종료
  TRAV_LIFT_MOVING --> ERROR_TRAV: 타임아웃/이상
  LOADING --> ERROR_FORK: 포크이상
  ERROR_TRAV --> RETURN_HOME
  ERROR_FORK --> RETURN_HOME
</pre></div>

<h2 id="runmode-table">RunMode 전체 그룹별 표</h2>
${buildRunSeqTable(runSeq)}

<h2 id="prepare">PREPARE_MOVE 구간 상세 (지금 보고 계신 부분)</h2>
<h4>case RUN_SEQ_PREPARE_MOVE_0</h4>
<ol>
  <li><code>Check_Trav_lift_In_Postion()</code> — 주행·승강 목표 도착 여부</li>
  <li><code>Rack_fork_obstruction</code> — 1이면 InPosition이어도 재이동</li>
  <li>이동 필요 시: StartPos/TargetPos/Move_Dir 계산, 브레이크 해제 옵션 분기</li>
  <li><code>Save_ForkWork_OrderProcess()</code> — 지상반에 "이동중" 스텝 보고</li>
</ol>

<h4>case RUN_SEQ_PREPARE_MOVE_BRAKE_RELEASE_0</h4>
<pre class="code">nFlag = 0;
if (Get_Motor_Brake_Release(INV_TRAVEL))  nFlag |= cbits[0]; // bit0=주행 해제OK
if (Get_Motor_Brake_Release(INV_HOIST))     nFlag |= cbits[1]; // bit1=승강 해제OK
// 3초 내 nFlag==0x03 → RUN_SEQ_MOVE_BEFORE_DELAY
// 타임아웃 → save_error_code(ERROR1_WORK_TIMEOUT, 1, nFlag)</pre>

<h2 id="get-cycle">GET(적재) 사이클 단계</h2>
<table class="data-table">
  <tr><th>순서</th><th>RunMode 구간</th><th>현장 동작</th><th>보고 스텝 예</th></tr>
  <tr><td>1</td><td>PREPARE → MOVE</td><td>From 셀까지 주행·승강</td><td>CMD_FORK_STEP_MOVING_FROM</td></tr>
  <tr><td>2</td><td>LOADING_INTERLOCK</td><td>스테이션/CV 인터록 확인</td><td>—</td></tr>
  <tr><td>3</td><td>LOADING_FORK_OUT</td><td>포크 랙 진출</td><td>CMD_FORK_STEP_FORK_OUT</td></tr>
  <tr><td>4</td><td>LOADING_FORK_OUT_LIFT_UP</td><td>리프트 업(적재)</td><td>CMD_FORK_STEP_LIFT_UP</td></tr>
  <tr><td>5</td><td>LOADING_FORK_IN</td><td>포크 복귀</td><td>CMD_FORK_STEP_FORK_IN</td></tr>
  <tr><td>6</td><td>LOADING_COMPLETE</td><td>화물 센서 확인</td><td>WORK_STATUS_COMPLETE</td></tr>
</table>

<h2 id="put-cycle">PUT(이재) 사이클 — GET과 대칭</h2>
<p>LOADING → UNLOADING, LIFT_UP → LIFT_DOWN, 화물 있어야 진행(GoodsFlag), 공출고 검사 등 차이.</p>
<p>RunMode 번호: LOADING=30대, UNLOADING=50대 (dev_SRM.h enum 값 의도적 간격 — 중간에 서브 case 삽입 여지)</p>

<h2 id="error-flow">에러·홈복귀 경로</h2>
<div class="mermaid-wrap"><pre class="mermaid">
flowchart LR
  E1[RUN_SEQ_ERROR_FORK_STOP] --> S1[포크 정지]
  E2[RUN_SEQ_ERROR_TRAV_LIFT_*] --> S2[주행·승강 정지]
  S1 & S2 --> B[브레이크 체결 확인]
  B --> H[RUN_SEQ_RETURN_HOME_*]
  H --> SB[RUN_SEQ_STAND_BY]
</pre></div>
<p><code>save_error_code(ERROR1_*, sub, nFlag)</code> → m_St 에러 비트 + AlarmLog. nFlag는 어느 축/센서 문제인지 서브코드.</p>

<h2 id="files">Part 4 — 파일 맵과 읽기 순서</h2>
${buildFileTable()}

<h3>권장 읽기 순서 (처음부터)</h3>
<ol>
  <li><b>User_Define.h</b> — StatusSTR, PGMEnvSTR, SRM_WorkDataSTR 구조만 먼저</li>
  <li><b>dev_SRM.h</b> — enumSRM_RUN_SEQ, WORK_*, INV_* enum</li>
  <li><b>com_tml.h</b> — TY_*, ORDER_CODE_*</li>
  <li><b>main.c</b> — while(1), timer1ms ISR</li>
  <li><b>com_tml.c</b> — rxCmdOrder, rxCmdStart (약 2340행~)</li>
  <li><b>dev_SRM.c</b> — SRM_Machine_Run_Process (약 58437행~). <b>한번에 안 읽음. RunMode 그룹별로.</b></li>
  <li><b>alarm.c</b> — Save_* 함수들</li>
</ol>

<h2 id="patterns">코딩 패턴 6종 (타 설비에도 그대로 쓰임)</h2>
${PATTERNS.map((p) => `
<div class="pattern-card">
  <h4>${esc(p.title)} <span class="mono" style="font-weight:normal">— ${esc(p.file)}</span></h4>
  <pre class="code">${esc(p.code)}</pre>
  <p>${esc(p.explain)}</p>
</div>`).join("")}

<h2 id="traps">명명 함정 8선</h2>
${NAMING_TRAPS.map((t) => `
<div class="trap-card">
  <div class="name">${esc(t.name)}</div>
  <div><b>함정</b>: ${esc(t.trap)}</div>
  <div><b>실제</b>: ${esc(t.real)}</div>
</div>`).join("")}

<h2 id="subseq">이중 상태머신 — RunMode + Sub_Run_Step</h2>
<p>RunMode가 "지금 GET 중 포크 진출 단계"라면, 포크 모터 세부 제어는 <code>m_Fork_Sub_Run_Step</code> switch가 담당.</p>
<table class="data-table">
  <tr><th>변수</th><th>축</th><th>예시 함수</th></tr>
  <tr><td class="mono">m_Trav_Sub_Run_Step</td><td>주행</td><td>Auto_Ctr_Travel(), 감속 dog 처리</td></tr>
  <tr><td class="mono">m_Lift_Sub_Run_Step</td><td>승강</td><td>Auto_Ctr_Lift()</td></tr>
  <tr><td class="mono">m_Fork_Sub_Run_Step</td><td>포크</td><td>포크 진출/복귀 위치제어</td></tr>
</table>
<p>큰 흐름 읽을 때는 RunMode만, 축 모터 이상 디버깅 시 Sub_Run_Step 추가 추적.</p>

<h2 id="grep">grep 4단계 추적법</h2>
<ol>
  <li><b>심볼 검색</b> — 예: <code>Rack_fork_obstruction</code></li>
  <li><b>쓰기(=) 찾기</b> — 누가 1로 세팅하나</li>
  <li><b>if 조건</b> — 어떤 분기에서 참/거짓</li>
  <li><b>RunMode/Save 연결</b> — 최종적으로 어느 case·보고로 이어지나</li>
</ol>
<p>사전 HTML에 사용 파일 열이 있으면 1단계 생략 가능.</p>

<h2 id="debug">Part 5 — 현장 디버깅 체크리스트</h2>
<p>작업이 안 돌 때 이 순서로:</p>
<ol>
  <li>0x41 수락됐나 (COMMAND_ERROR 코드)</li>
  <li>0x50 Start 됐나 (m_St.StartOn, RunMode≠STAND_BY)</li>
  <li>m_WorkData[s_WorkInx].ForkAct / TargetPos 값</li>
  <li>RunMode 현재값 (HMI DEBUG 또는 m_TestStatus)</li>
  <li>GoodsFlag / ForkCenter / InPosition 스킵 조건</li>
  <li>EtherCAT 링크·인버터 Fault (m_St.Inv_St)</li>
  <li>BKPSRAM WorkInfo 복구 이상 여부</li>
</ol>

<h2 id="exercise">연습문제 (클릭하여 정답)</h2>
<div class="exercise">
${EXERCISES.map((e, i) => `
<details><summary>Q${i + 1}. ${esc(e.q)}</summary>
  <p><b>힌트</b>: ${esc(e.hint)}</p>
  <p><b>정답</b>: ${esc(e.a)}</p>
</details>`).join("")}
</div>

<h2 id="transfer">타 설비 제어로 이식할 때 가져갈 것</h2>
<table class="data-table">
  <tr><th>이식 요소</th><th>SRM에서의 구현</th><th>다른 설비 적용</th></tr>
  <tr><td>명령-실행-보고 3층</td><td>WorkCmd→m_WorkData→m_St</td><td>PLC명령→내부레시피→상태레지스터</td></tr>
  <tr><td>상태머신 switch</td><td>enumSRM_RUN_SEQ</td><td>공정 단계 enum + case</td></tr>
  <tr><td>이중 시퀀스</td><td>RunMode + Sub_Run_Step</td><td>공정스텝 + 축별 모션스텝</td></tr>
  <tr><td>비트 플래그 에러</td><td>nFlag |= cbits[n]</td><td>알람 워드 비트맵</td></tr>
  <tr><td>타이머 기반 대기</td><td>timer1ms + getCalcTimer1ms</td><td>OS tick / HW timer</td></tr>
  <tr><td>파라미터 분리</td><td>ExtSEnv0~2 Flash</td><td>Recipe DB / NV RAM</td></tr>
  <tr><td>정전복구</td><td>m_BKSram</td><td>배터리백업 SRAM / FRAM</td></tr>
</table>

<h2 id="order-work">ORDER_CODE ↔ WORK_ForkAct 매핑</h2>
<p>0x41의 OrderCode가 내부 <code>m_WorkData[].ForkAct</code>으로 변환됩니다. 이 매핑이 상태머신 분기의 시작점입니다.</p>
<table class="data-table">
  <tr><th>ORDER_CODE (0x41)</th><th>값</th><th>→ ForkAct</th><th>RunMode 진입</th></tr>
  <tr><td>ORDER_CODE_MOVE</td><td>0x01</td><td>WORK_MOVE_ONLY</td><td>이동만, LOADING/UNLOADING 생략</td></tr>
  <tr><td>ORDER_CODE_STORE</td><td>0x12</td><td>WORK_FORK1_GET 등</td><td>RUN_SEQ_LOADING_*</td></tr>
  <tr><td>ORDER_CODE_UNSTORE</td><td>0x13</td><td>WORK_FORK1_PUT 등</td><td>RUN_SEQ_UNLOADING_*</td></tr>
  <tr><td>ORDER_CODE_RACK_TO_RACK</td><td>0x14</td><td>GET+PUT 조합</td><td>From GET → To PUT 연속</td></tr>
  <tr><td>ORDER_CODE_STATION_TO_STATION</td><td>0x15</td><td>스테이션 반송</td><td>IsStation 플래그 사용</td></tr>
  <tr><td>ORDER_CODE_STICKY</td><td>0x1A</td><td>WORK_FORK1_STICKY</td><td>화물검사 생략 가능</td></tr>
</table>

<h2 id="save-funcs">Save_* 함수 — 지상반 보고 API</h2>
<p>alarm.c에 정의. <b>m_St만</b> 갱신. UART 즉시 송신 아님 → 다음 0x30 때 반영.</p>
<table class="data-table">
  <tr><th>함수</th><th>갱신 필드</th><th>호출 시점 예</th></tr>
  <tr><td class="mono">Save_ForkWork_OrderStatus</td><td>m_St.ForkWork[n].OrderStatus</td><td>WORK_STATUS_DOING/COMPLETE/FAIL</td></tr>
  <tr><td class="mono">Save_ForkWork_OrderProcess</td><td>m_St.ForkWork[n].OrderProcess</td><td>CMD_FORK_STEP_MOVING_FROM 등 스텝</td></tr>
  <tr><td class="mono">Save_ForkMove_OrderStatus</td><td>m_St.ForkMove.OrderStatus</td><td>WORK_MOVE_ONLY 시</td></tr>
  <tr><td class="mono">Save_ForkMove_OrderProcess</td><td>m_St.ForkMove.OrderProcess</td><td>CMD_MOVE_STEP_*</td></tr>
</table>

<h2 id="start-case">case RUN_SEQ_START — 작업 분기의 시작</h2>
<p><code>SRM_Machine_Run_Process()</code> 약 58437행. static 변수들이 이 함수 안에서 사이클 전체 유지:</p>
<table class="data-table">
  <tr><th>static 변수</th><th>역할</th></tr>
  <tr><td class="mono">s_WorkInx</td><td>현재 처리 중 m_WorkData 인덱스</td></tr>
  <tr><td class="mono">s_Work_Fork_Flag</td><td>포크1/2 동시 작업 비트플래그</td></tr>
  <tr><td class="mono">s_No_movement</td><td>주행·승강 이동 없이 포크만 할지</td></tr>
  <tr><td class="mono">s_Delay_Time</td><td>Read_DelayTime()으로 읽은 대기 ms</td></tr>
  <tr><td class="mono">s_Brake_Release_Retry</td><td>브레이크 해제 재시도 횟수</td></tr>
</table>
<p>START case에서 <code>m_WorkData[s_WorkInx].ForkAct</code> switch → PREPARE_MOVE / LOADING_START / UNLOADING_START / FORK_START 등으로 첫 분기.</p>

<h2 id="get-detail">GET 사이클 — RunMode 전이 상세</h2>
<div class="mermaid-wrap"><pre class="mermaid">
flowchart TD
  A[RUN_SEQ_START] --> B[RUN_SEQ_PREPARE_MOVE_0]
  B --> C{InPosition?}
  C -->|이동필요| D[BRAKE_RELEASE or MOVE_DELAY]
  C -->|스킵| E[TRAV_LIFT_AFTER_MOVE]
  D --> F[START_MOVE_0]
  F --> G[TRAV_LIFT_MOVING]
  G --> H[TRAV_LIFT_AFTER_MOVE]
  H --> I[RUN_SEQ_FORK_START]
  I --> J[RUN_SEQ_LOADING_START]
  J --> K[LOADING_INTERLOCK]
  K --> L[LOADING_FORK_OUT]
  L --> M[LOADING_FORK_OUT_LIFT_UP]
  M --> N[LOADING_FORK_IN]
  N --> O[LOADING_COMPLETE]
  O --> P[RUN_SEQ_COMPLETE]
  P --> Q[RUN_SEQ_STAND_BY]
</pre></div>

<h3>각 LOADING 단계에서 볼 것</h3>
<table class="data-table">
  <tr><th>case</th><th>조건/타이머</th><th>축 제어</th><th>Save 보고</th></tr>
  <tr><td>LOADING_INTERLOCK</td><td>Check_Station_CVOK, 타임아웃</td><td>—</td><td>인터록 실패 시 에러</td></tr>
  <tr><td>LOADING_PRE_FORK_OUT</td><td>Read_DelayTime PRE_FORK</td><td>—</td><td>CMD_FORK_STEP_PRE_OUT</td></tr>
  <tr><td>LOADING_FORK_OUT</td><td>m_Fork_Sub_Run_Step</td><td>포크 진출 Auto_Ctr</td><td>CMD_FORK_STEP_FORK_OUT</td></tr>
  <tr><td>LOADING_FORK_OUT_LIFT_UP</td><td>리프트 인터록</td><td>승강 업</td><td>CMD_FORK_STEP_LIFT_UP</td></tr>
  <tr><td>LOADING_FORK_IN</td><td>센터센서/정위치</td><td>포크 복귀</td><td>CMD_FORK_STEP_FORK_IN</td></tr>
  <tr><td>LOADING_COMPLETE</td><td>GOX 화물센서</td><td>—</td><td>WORK_STATUS_COMPLETE</td></tr>
</table>

<h2 id="inv-axes">인버터 4축 인덱스</h2>
<table class="data-table">
  <tr><th>enum</th><th>축</th><th>PDO</th><th>주요 함수</th></tr>
  <tr><td class="mono">INV_TRAVEL</td><td>주행</td><td>m_SRM_TxPDO[INV_TRAVEL]</td><td>Auto_Ctr_Travel, Motor_Brake_Release</td></tr>
  <tr><td class="mono">INV_HOIST</td><td>승강</td><td>m_SRM_TxPDO[INV_HOIST]</td><td>Auto_Ctr_Lift</td></tr>
  <tr><td class="mono">INV_FORK_1</td><td>포크1</td><td>—</td><td>포크 위치제어, GoodsFlag</td></tr>
  <tr><td class="mono">INV_FORK_2</td><td>포크2</td><td>—</td><td>듀얼포크 시</td></tr>
</table>
<p><code>m_St.Inv_St[INV_*]</code> — Current_Pos, Current_Vel, Status1(GoodsFlag, MoveFlag, InPosition)</p>

<h2 id="param">파라미터 3분할 — 현장 튜닝 지점</h2>
<table class="data-table">
  <tr><th>구조체</th><th>내용</th><th>바꾸면 뭐가 달라지나</th></tr>
  <tr><td>m_ExtSEnv0</td><td>랙·셀 좌표, 주행 드라이브</td><td>셀 위치, 주행 속도/가감속</td></tr>
  <tr><td>m_ExtSEnv1</td><td>승강 드라이브, 스테이션, 인터록</td><td>스테이션 CV OK 조건</td></tr>
  <tr><td>m_ExtSEnv2</td><td>포크 드라이브, CtrParam, 타임아웃</td><td>딜레이 ms, 타임아웃, 홈복귀 옵션</td></tr>
</table>
<p>Read_DelayTime(ForkAct, DELAY_*) — m_ExtSEnv2의 Setup/Auto 타임아웃 테이블 참조.</p>

<h2 id="new-step">[심화] 새 시퀀스 step을 설계한다면</h2>
<div class="pattern-card">
  <h4>체크리스트 (다른 설비에도 동일)</h4>
  <ol>
    <li><b>enum에 case 추가</b> — dev_SRM.h enumSRM_RUN_SEQ (번호 간격 여유 확인)</li>
    <li><b>진입 조건</b> — 어느 case에서 m_pgmEnv.SRM_RunMode = 새값 으로 넘기나</li>
    <li><b>case 본문</b> — 타이머 시작, 조건검사, 축 명령, break</li>
    <li><b>탈출 조건</b> — 성공 시 다음 RunMode, 실패 시 ERROR_*</li>
    <li><b>Save 보고</b> — 지상반이 볼 스텝 코드 정의 (CMD_FORK_STEP_* 등)</li>
    <li><b>에러 서브코드</b> — nFlag 비트 할당 문서화</li>
    <li><b>파라미터</b> — 딜레이/타임아웃을 ExtSEnv2에 넣을지 결정</li>
  </ol>
</div>

<h2 id="tml-funcs">com_tml.c 주요 수신 함수</h2>
<table class="data-table">
  <tr><th>TY_*</th><th>함수</th><th>핵심 동작</th></tr>
  <tr><td>0x30</td><td>txStatus / rx 처리</td><td>m_St 패킷 응답</td></tr>
  <tr><td>0x41</td><td>rxCmdOrder</td><td>WorkCmdSTR → Store_Work_Data*</td></tr>
  <tr><td>0x50</td><td>rxCmdStart</td><td>RUN_SEQ_START</td></tr>
  <tr><td>0x51</td><td>rxCmdMoveHome</td><td>홈 이동 명령</td></tr>
  <tr><td>0x52</td><td>rxCmdErrorReset</td><td>에러 클리어</td></tr>
  <tr><td>0x53</td><td>rxCmdOrderDelete</td><td>작업 큐 삭제</td></tr>
  <tr><td>0x55</td><td>rxEmergencyStop</td><td>비상정지</td></tr>
</table>

<h2 id="memory">메모리·전역 배치</h2>
<ul>
  <li><b>DTCM</b> — main.c의 m_St, m_pgmEnv 등 (__attribute__ dtcm_bss) : 빠른 접근</li>
  <li><b>BKPSRAM</b> — m_BKSram : 배터리 백업, rtc.c에서 블록 단위 저장</li>
  <li><b>dev_SRM.c static</b> — m_WorkData[30] : extern 아님, 상태머신 전용</li>
  <li><b>Flash</b> — m_ExtSEnv0~2 : SRM_Parameter.c로 읽기/쓰기</li>
</ul>

<h2 id="read-method">효율적인 코드 읽기 방법 (이 가이드 + 사전 병행)</h2>
<table class="data-table">
  <tr><th>단계</th><th>할 일</th><th>도구</th></tr>
  <tr><td>1. 질문 정의</td><td>"GET 시 포크 진출 전 딜레이는?"</td><td>—</td></tr>
  <tr><td>2. RunMode 찾기</td><td>LOADING_PRE_FORK_OUT</td><td>이 가이드 RunMode 표</td></tr>
  <tr><td>3. case 열기</td><td>dev_SRM.c 해당 case</td><td>IDE 검색</td></tr>
  <tr><td>4. 심볼 풀이</td><td>Read_DelayTime, s_Delay_Time</td><td>심볼 용도 사전</td></tr>
  <tr><td>5. 연결 추적</td><td>누가 RunMode를 여기로 넘기나</td><td>grep "RUN_SEQ_LOADING_PRE"</td></tr>
  <tr><td>6. 현장 의미</td><td>지상반 화면 스텝 번호</td><td>Save_ForkWork_OrderProcess 인자</td></tr>
</table>

<h2 id="glossary">용어 사전 (현장 ↔ 코드)</h2>
<table class="data-table">
  <tr><th>현장/지상반</th><th>코드</th></tr>
  <tr><td>작업명령</td><td>0x41, WorkCmdSTR, OrderCode</td></tr>
  <tr><td>Start ON</td><td>0x50, m_St.SRM_Status1.StartOn, RUN_SEQ_START</td></tr>
  <tr><td>적재/GET</td><td>ORDER_CODE_STORE, WORK_FORK1_GET, LOADING_*</td></tr>
  <tr><td>이재/PUT</td><td>ORDER_CODE_UNSTORE, WORK_FORK1_PUT, UNLOADING_*</td></tr>
  <tr><td>스텝/진행상태</td><td>OrderProcess, CMD_FORK_STEP_*</td></tr>
  <tr><td>작업결과</td><td>OrderStatus, WORK_STATUS_*</td></tr>
  <tr><td>이상/알람</td><td>save_error_code, ERROR1_*, m_St.Fault</td></tr>
  <tr><td>인포지션</td><td>Check_Trav_lift_In_Postion, InPosition 비트</td></tr>
  <tr><td>홈복귀</td><td>RETURN_HOME_*, TY_CMD_MOVE_HOME</td></tr>
  <tr><td>원점</td><td>ORIGIN_*, 축별 원점 설정</td></tr>
</table>

<h2 id="exercise2">추가 연습 — 시퀀스 추적 (스스로 해보기)</h2>
<div class="exercise">
<details><summary>브레이크 해제 타임아웃 3초는 어디서?</summary>
  <p><b>정답</b>: RUN_SEQ_PREPARE_MOVE_BRAKE_RELEASE_0, getCalcTimer1ms &gt; 3000</p>
</details>
<details><summary>GET 완료 후 STAND_BY로 돌아가기까지 거치는 case?</summary>
  <p><b>정답</b>: LOADING_COMPLETE → RUN_SEQ_COMPLETE → (PLC_COM) → RUN_SEQ_STAND_BY</p>
</details>
<details><summary>주행 방향은 누가 결정?</summary>
  <p><b>정답</b>: Check_Trav_Move_Dir() — StartPos vs TargetPos → TRAV_MOVE_FORWARD/REVERSE</p>
</details>
<details><summary>에러 80-1 (WORK_TIMEOUT) 서브코드 nFlag=0x01이면?</summary>
  <p><b>정답</b>: 주행(INV_TRAVEL) 브레이크만 해제 실패. 승강은 OK.</p>
</details>
<details><summary>m_WorkData는 extern인가?</summary>
  <p><b>정답</b>: 아님. dev_SRM.c static. 다른 파일에서 직접 접근 불가.</p>
</details>
</div>

<ol>
  <li>이 가이드 4주 로드맵 완주</li>
  <li>dev_SRM.c 에 <b>한 개 case</b>를 골라 조건·전이·Save 호출 <b>손으로 주석 달기</b></li>
  <li>연습: <b>딜레이 200ms 추가</b> — Read_DelayTime / DEF_DELAY_* / case 타이머 중 어디를 바꿀지 찾기만 (실제 수정은 테스트 환경에서)</li>
  <li>연습: <b>새 RunMode case 하나</b> 설계해보기 (종이에 전이도 그리기)</li>
  <li>심볼 사전으로 모르는 이름 즉시 검색 — <b>이 습관이 자립의 핵심</b></li>
</ol>

<div class="goal">
  <b>최종 목표</b>: 이 HTML + 심볼 사전만으로 현장에서 "어느 case가 문제인지" 스스로 좁히고,
  다른 크레인/컨베이어/스태커에서도 <b>같은 4층 구조</b>로 제어 코드를 설계할 수 있는 것.
</div>
`;

  const html = `<!DOCTYPE html>
<html lang="ko"><head>
<meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<title>SRM 전체코드 학습가이드 ${TODAY_DISP}</title>
<style>${css}</style>
</head><body>
<div class="layout">
<nav class="sidebar">${nav}</nav>
<main>${body}</main>
</div>
${mermaidScript}
</body></html>`;

  const outName = `SRM_전체코드_학습가이드_${TODAY}.html`;
  const outPath = path.join(OUT, outName);
  fs.writeFileSync(outPath, html, "utf8");

  const readmeAdd = `

## 학습 가이드 (신규)

| 파일 | 내용 |
|------|------|
| **${outName}** | **학습 가이드** — 아키텍처, 통신, 상태머신, 패턴, 4주 로드맵, 연습문제 |

- 심볼 사전 = Ctrl+F 찾기용
- 학습 가이드 = 흐름·패턴·읽기 순서용
`;
  let readme = read(path.join(OUT, "README.md"));
  if (!readme.includes("학습 가이드")) {
    readme = readme.trimEnd() + readmeAdd;
    fs.writeFileSync(path.join(OUT, "README.md"), readme, "utf8");
  }

  console.log(`Done: ${outPath}`);
  console.log(`Size: ${(fs.statSync(outPath).size / 1024).toFixed(1)} KB`);
}

main();
