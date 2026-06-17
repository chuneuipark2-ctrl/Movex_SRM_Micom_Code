/**
 * 핵심 함수 L3 — 현장 해설 (수동 작성, 맥락·함정 포함)
 * 키: 함수명
 */
function esc(s) {
  return String(s ?? "")
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;");
}

const DEEP = {
  rxCmdOrder: `
<h4>0x41 반송지령 — 전체 흐름</h4>
<p>지상반 → TML → <code>WorkCmdSTR</code> 파싱 → <b>1차 게이트</b> → switch 상세검사 → <code>SRM_Fork_Work_Cmd</code> → 응답(accept/ret_value).</p>
<p><b>0x41 직후 RunMode는 STAND_BY</b>. 모터는 0x50 Start 후에 움직임.</p>

<h4>1차 게이트 (if ~ else if)</h4>
<table class="data-table"><tr><th>조건</th><th>ret_value</th><th>현장 의미</th></tr>
<tr><td>SRM_Status1.Fault</td><td>COMMAND_ERROR_FALUT_STATE</td><td>에러 상태에서 새 명령 거부</td></tr>
<tr><td>SRM_Status2.ManualSW</td><td>COMMAND_ERROR_MANUAL_SW_ON</td><td>기상반 수동 스위치 ON</td></tr>
<tr><td>RunMode ≠ STAND_BY</td><td>COMMAND_ERROR_EXECUTING_PREVIOUS_COMMAND</td><td>이전 시퀀스 실행 중</td></tr>
<tr><td>Check_Fork_Center_Alarm()</td><td>COMMAND_ERROR_FORK_CENTER_OFF</td><td>포크 센터 아님</td></tr>
<tr><td>SRM_Mode.Auto == 0</td><td>COMMAND_ERROR_NON_AUTOMATIC_MODE</td><td>자동 모드 아님</td></tr>
</table>

<h4>OrderCode별 추가 (1차 게이트 else 블록)</h4>
<ul>
<li><b>ORDER_CODE_MOVE (0x01)</b>: StartOn·화물센서 검사 <b>없음</b> (NOP). 이동만은 온라인 전에도 접수 가능한 설계.</li>
<li><b>STORE/UNSTORE/랙간/스테이션/Sticky</b>: StartOn==0 → NON_ONLINE. FK1 GoodsFlag → CARGO_DETECTION_STATUS.</li>
</ul>

<h4>NOP ≠ NACK</h4>
<p><code>asm volatile("NOP")</code> = CPU 빈 명령. 통신 거부 아님.</p>
<p><b>ACK/NACK</b> = 함수 맨 끝 <code>txPutcPort(port, accept[0])</code> + <code>ret_value[0]</code>.</p>
<table class="data-table"><tr><th>accept[0]</th><th>ret_value[0]</th><th>의미</th></tr>
<tr><td>0</td><td>0</td><td>ACK — 명령 큐 적재 OK</td></tr>
<tr><td>1</td><td>≠0</td><td>NACK — COMMAND_ERROR_* 사유</td></tr>
</table>
<p>ret_value에 에러 있으면 끝에서 <code>accept[0]=1</code> 강제.</p>
`,

  SRM_Fork_Work_Cmd: `
<h4>역할</h4>
<p>0x41 수락 후 실제 <b>작업 레시피</b> 생성. OrderCode별 From/To → Trav/Lift mm, Fork depth 계산 → <code>Store_Work_Data_*</code> → <code>m_WorkData</code>.</p>

<h4>목적지 변경 (0x16 / 0x17) — StartOn==0 일 때만</h4>
<p><code>nCheck_RackChange_Enable</code> 두 조건 (OR):</p>
<ol>
<li>지상반 WorkNum <b>있음</b> && SRM WorkNum_Fork <b>0</b> — SRM에 작업 없는데 지상반만 번호 줌</li>
<li>지상반 WorkNum == SRM WorkNum_Fork — 같은 작업의 목적지만 변경</li>
</ol>
<p>둘 다 아니면 <code>COMMAND_ERROR_DENIED_RACK_CHG</code>.</p>

<h4>0x16 RACK_CHG_DST</h4>
<ul>
<li>Bay/Level/Row <b>하나라도 0</b> → RACK_POSITION_BLANK (전부 0이 아니라 OR)</li>
<li>싱글딥: Row_ID 1(좌) → mFEL&lt;0 / Row_ID 2(우) → mFER&gt;0</li>
<li>mFEL/mFER = Flash 포크 진출 한계(mm). 0이면 그 방향 랙 불가.</li>
</ul>

<h4>0x17 STATION_CHG_DST (else 분기 — 랙 꺼짐 아님!)</h4>
<ul>
<li>ToCell.<b>Station</b> 1~TotalUseCnt</li>
<li>배열 인덱스 = Station - 1</li>
<li>Type이 OUT 또는 IN_OUT만 nEnable_Change_Dst=1 (입고 전용 STATION_IN_TYPE 거부)</li>
</ul>

<h4>성공 시</h4>
<p>m_St.ForkWork 초기화 → WorkNum/OrderCode/STOP/RX 스텝 → BKPSRAM 저장. Start 전 목적지만 갱신.</p>
`,

  rxCmdStart: `
<h4>0x50 Start</h4>
<p>0x41로 쌓인 <code>m_WorkData</code> 실행 개시. 성공 시 <code>StartOn=1</code>, <code>RunMode=RUN_SEQ_START</code>.</p>
<p>거부: Fault, !Auto, 이미 StartOn, 포크 센터, RunMode≠STAND_BY, OrderReject(비상/안전플러그).</p>
`,

  SRM_Start_On: `
<h4>Start 본체 (dev_SRM.c)</h4>
<p><code>RUN_SEQ_START</code> case에서 WorkInx 선택 → ForkAct에 따라 PREPARE / LOADING_START / UNLOADING_START 분기.</p>
<p>Row_ID, Move_PosFlag, 스테이션 여부 설정 후 상태머신 진입.</p>
`,

  rxCmdManual: `
<h4>0x80 수동</h4>
<p>pCom-&gt;Data[0] 비트: bit0=주행, bit1=승강, bit2=포크, bit5/6=포크 IO.</p>
<p>거부: Emergency, SafetyPlug, !초기화, Fault(Force 제외), ManualSW 중복, Auto 모드.</p>
<p>수동 → Control_Manual_* → RunMode 또는 직접 PDO (MANUAL_CTR_Fork).</p>
`,

  rxCellEnvSet: `
<h4>TY_CELL_ENV_SET — 랙/셀 티칭</h4>
<p>Setup 모드에서 Bay/Lv mm 좌표 수신 → 검증(nError 1~10) → Flash m_ExtSEnv0 → Create_Reference_Position().</p>
<p>nDataType: 1=Left Bay, 2=Left Lv, 3=Right Bay, 4=Right Lv.</p>
`,

  ECAT_Manager: `
<h4>EtherCAT PDO 사이클</h4>
<p>main 루프에서 SRM_Manager <b>앞</b>. 슬레이브 검출→OP→Rx/Tx PDO 교환.</p>
<p>Store_SRM_RxPDO* 가 큐에 넣은 명령을 인버터로, 피드백은 m_St.Inv_St[].</p>
`,

  Store_SRM_RxPDO_queue: `
<h4>MCU→인버터 명령 큐</h4>
<p>ControlWord + TargetPosition(mm) + Speed(m/min) + Acc/Dec/Jerk → m_SRM_RxPDOQ[]. Ring buffer Front++.</p>
<p>RunMode/Auto_Ctr_* 가 호출. ECAT_Manager가 소비.</p>
`,

  Create_Reference_Position: `
<h4>RAM 참조 테이블</h4>
<p>Flash Cell/Station 좌표 → nPosSeq_X/Y_Left/Right[] 정렬·병합. 부팅·티칭 후 호출.</p>
<p>자동운전 시 Bay/Lv/Station → mm 변환 기준.</p>
`,

  SRM_Manager: `
<h4>매 루프 SRM 진입점</h4>
<p>다운로드 모드 아니면 SRM_Machine_Process + SRM_Machine_Run_Process (RunMode switch).</p>
`,

  SRM_Machine_Run_Process: `
<h4>상태머신 본체</h4>
<p>switch(m_pgmEnv.SRM_RunMode) — 113+ case. 한 루프 1 case 1 step, break 필수.</p>
<p>타이머: m_pgmEnv.SRM_RunTimer vs timer1ms.</p>
`,

  AlarmManager: `
<h4>alarm.c — DI/DO·에러·Save 트리거</h4>
<p>main 첫 Manager. Save_* 가 m_St/BKPSRAM 갱신 → 0x30 폴링으로 지상반 전달.</p>
`,

  Scan_Travel_Position_Sensor: `
<h4>주행 센서 스캔</h4>
<p>RUN_SEQ_TRAV_SCAN_SENSOR_* 에서 호출. StartPos 이동 → JOG 스캔 → 센서 위치 평균 → 파라미터 반영.</p>
<p>SubStep 50=완료→STAND_BY, 100=에러.</p>
`,

  Auto_Ctr_Travel: `
<h4>자동 주행 제어</h4>
<p>목표 mm + VelType → Store_SRM_RxPDO(INV_TRAVEL). InPosition은 m_St.Inv_St 피드백 비교.</p>
`,

  Control_Manual_Trav_Start: `
<h4>수동 주행</h4>
<p>MANUAL_CTR_TRAV_* → 저속/중속 JOG 시퀀스 → PDO. CREEP와 별도 VelType.</p>
`,

  Store_Work_Data_1: `
<h4>작업 큐 적재</h4>
<p>0x41 / RunMode에서 호출. From/To Trav·Lift mm, ForkAct, Fork depth → <code>m_WorkData[]</code> static 큐.</p>
<p>GET+PUT 한 번에 2슬롯 적재 가능. RunMode는 아직 STAND_BY.</p>
`,

  Save_ForkWork_OrderProcess: `
<h4>지상반 스텝 보고</h4>
<p><code>m_St.ForkWork[0].OrderProcess_Fork</code> = CMD_FORK_STEP_* → 0x30 폴링.</p>
<p>Save=출력층. Store와 혼동 금지.</p>
`,

  rxCmdManual: `
<h4>0x80 수동 — L3 요약</h4>
<p>Data[0] bit0=주행, bit1=승강, bit2=포크. Control_Manual_* → PDO/RunMode.</p>
<p>CREEP = 저속 정밀(VelType), 그립(grip) 아님.</p>
`,

  Scan_Lift_Position_Sensor: `
<h4>승강 센서 스캔</h4>
<p>RUN_SEQ_LIFT_SCAN_SENSOR_* — Scan_Travel과 대칭. SubStep 50/100.</p>
`,

  Set_Rack_Config: `
<h4>Flash RackConfig</h4>
<p>memcmp 변경 시만 ExtFlash_WriteData. CRC CheckCRC_RackConfig.</p>
`,

  Set_Cell_Config_1: `
<h4>Flash Cell Left/Right</h4>
<p>nDir 0=Left, 1=Right. BayPos/LvPos 배열 + CRC.</p>
`,
};

function getDeepNarrative(fnName) {
  return DEEP[fnName] || null;
}

module.exports = { getDeepNarrative, DEEP };
