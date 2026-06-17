/**
 * 함수/RunMode case 자동 맥락 분석 → L1/L2 HTML (한국어)
 */
function esc(s) {
  return String(s ?? "")
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;");
}

const FN_ROLE = {
  rx: "TML UART 수신 핸들러 — 지상반 명령 디스패치",
  Store_: "입력층 — m_WorkData / PDO 큐 적재 (Store)",
  Save_: "출력층 — m_St / BKPSRAM 보고 (Save)",
  Auto_Ctr_: "자동 축 제어 — RunMode에서 호출, PDO 경로",
  Control_Manual_: "수동 조작 — 0x80 또는 HMI",
  MANUAL_CTR_: "수동 포크 PDO 직접 출력",
  Motor_: "모터/브레이크/인버터 보조",
  Check_: "조건 검사 — 0/1 반환, 거부·에러 판단에 사용",
  Scan_: "Setup 센서 스캔·티칭",
  Set_: "Flash 파라미터 쓰기",
  Init: "부팅/Flash 초기화·CRC",
  ECAT_: "EtherCAT PDO",
  SRM_: "SRM 상태머신·작업 명령",
  Create_: "RAM 참조 테이블·좌표 생성",
  rxCmd: "TML 작업/제어 명령 수신",
};

function guessRole(name) {
  for (const [prefix, role] of Object.entries(FN_ROLE)) {
    if (name.startsWith(prefix) || name.includes(prefix)) return role;
  }
  if (/^rx/.test(name)) return FN_ROLE.rx;
  return "펌웨어 내부 함수 — 호출 관계는 L2 분석 참고";
}

function extractPatterns(body) {
  const p = {
    errors: [],
    runModes: [],
    stores: [],
    saves: [],
    stWrites: [],
    workWrites: [],
    flash: [],
    retValues: [],
    commandErrors: [],
    timers: [],
    inv: [],
  };
  for (const line of body.split("\n")) {
    const t = line.trim();
    let m;
    if ((m = t.match(/save_error_code\s*\(\s*(ERROR\w+)/))) p.errors.push(m[1]);
    if ((m = t.match(/SRM_RunMode\s*=\s*(RUN_SEQ_\w+)/))) p.runModes.push(m[1]);
    if ((m = t.match(/(Store_\w+)\s*\(/))) p.stores.push(m[1]);
    if ((m = t.match(/(Save_\w+)\s*\(/))) p.saves.push(m[1]);
    if (/m_St\./.test(t)) p.stWrites.push(t.slice(0, 100));
    if (/m_WorkData/.test(t)) p.workWrites.push(t.slice(0, 100));
    if (/m_ExtSEnv|ExtFlash/.test(t)) p.flash.push(t.slice(0, 80));
    if ((m = t.match(/ret_value\[?\d*\]?\s*=\s*(COMMAND_ERROR_\w+|\d+)/))) p.retValues.push(m[1]);
    if ((m = t.match(/return\s+(COMMAND_ERROR_\w+)/))) p.commandErrors.push(m[1]);
    if (/SRM_RunTimer|timer1ms|getCalcTimer1ms/.test(t)) p.timers.push(t.slice(0, 90));
    if (/INV_\w+|Store_SRM_RxPDO/.test(t)) p.inv.push(t.slice(0, 90));
  }
  const uniq = (a) => [...new Set(a)];
  return {
    errors: uniq(p.errors),
    runModes: uniq(p.runModes),
    stores: uniq(p.stores),
    saves: uniq(p.saves),
    stWrites: uniq(p.stWrites).slice(0, 12),
    workWrites: uniq(p.workWrites).slice(0, 10),
    flash: uniq(p.flash).slice(0, 8),
    retValues: uniq(p.retValues),
    commandErrors: uniq(p.commandErrors),
    timers: uniq(p.timers).slice(0, 6),
    inv: uniq(p.inv).slice(0, 8),
  };
}

function buildAnalysisHtml(p, name) {
  let html = "";
  if (p.commandErrors.length || p.retValues.length) {
    html += `<h5>거부/응답 코드</h5><ul>`;
    for (const c of [...p.commandErrors, ...p.retValues]) html += `<li class="mono">${esc(c)}</li>`;
    html += `</ul>`;
  }
  if (p.errors.length) {
    html += `<h5>save_error_code (알람 기록)</h5><ul>`;
    for (const e of p.errors) html += `<li class="mono">${esc(e)}</li>`;
    html += `</ul>`;
  }
  if (p.runModes.length) {
    html += `<h5>RunMode 전이 (이 함수에서 설정)</h5><p>${p.runModes.map((r) => `<span class="mono">${esc(r)}</span>`).join(", ")}</p>`;
  }
  if (p.stores.length) {
    html += `<h5>Store_* (입력/큐)</h5><p>${p.stores.map((s) => `<span class="mono">${esc(s)}</span>`).join(", ")}</p>`;
  }
  if (p.saves.length) {
    html += `<h5>Save_* (지상반 보고)</h5><p>${p.saves.map((s) => `<span class="mono">${esc(s)}</span>`).join(", ")}</p>`;
  }
  if (p.inv.length) {
    html += `<h5>인버터/PDO</h5><ul>`;
    for (const i of p.inv) html += `<li><code>${esc(i)}</code></li>`;
    html += `</ul>`;
  }
  if (p.flash.length) {
    html += `<h5>Flash/파라미터</h5><ul>`;
    for (const f of p.flash) html += `<li><code>${esc(f)}</code></li>`;
    html += `</ul>`;
  }
  if (p.timers.length) {
    html += `<h5>타이머 (1ms 기준)</h5><ul>`;
    for (const t of p.timers) html += `<li><code>${esc(t)}</code></li>`;
    html += `</ul>`;
  }
  if (p.workWrites.length) {
    html += `<h5>m_WorkData 접근</h5><ul>`;
    for (const w of p.workWrites) html += `<li><code>${esc(w)}</code></li>`;
    html += `</ul>`;
  }
  if (p.stWrites.length) {
    html += `<h5>m_St / 상태 갱신 (발췌)</h5><ul>`;
    for (const s of p.stWrites) html += `<li><code>${esc(s)}</code></li>`;
    html += `</ul>`;
  }
  if (!html) html = `<p class="note">자동 추출 패턴 없음 — 순수 계산/보조 함수이거나 static inline 분기. L4 소스 전체를 읽으세요.</p>`;
  return html;
}

function autoAnalyzeFunction(body, name, fileHint) {
  const role = guessRole(name);
  const p = extractPatterns(body);
  const lines = body.split("\n").length;
  const oneLiner = `<p><b>${esc(name)}</b> (${lines}줄${fileHint ? ", " + esc(fileHint) : ""}) — ${esc(role)}</p>`;

  let contextHtml = `<p>${esc(role)}</p>`;
  if (name.startsWith("rx")) {
    contextHtml += `<p>TMLComManager switch → <code>${esc(name)}</code>. STX/Header/CRC/ETX 프레임 처리 후 <code>sendTxBuf</code> 응답.</p>`;
  }
  if (name.includes("Run_Process") || name === "SRM_Manager") {
    contextHtml += `<p>main while(1) → SRM_Manager() → 본 함수. ECAT_Manager() 직후, AlarmManager() 이후.</p>`;
  }
  if (name.startsWith("Store_")) {
    contextHtml += `<p>데이터 <b>입력층</b>. 0x41 또는 RunMode 진입 시 레시피 적재. Save_* 와 혼동 금지.</p>`;
  }
  if (name.startsWith("Save_")) {
    contextHtml += `<p>데이터 <b>출력층</b>. m_St.ForkWork.OrderProcess 등 → 0x30 폴링.</p>`;
  }

  return {
    oneLiner,
    contextHtml,
    analysisHtml: buildAnalysisHtml(p, name),
    patterns: p,
  };
}

function autoAnalyzeRunCase(c, incoming) {
  const p = extractPatterns(c.snippet);
  let html = `<h5>이 case의 역할 (자동 요약)</h5>`;
  const name = c.name.replace("RUN_SEQ_", "");
  if (/STAND_BY|START/.test(c.name)) html += `<p>대기·시작 — 자동 시퀀스 진입/대기점.</p>`;
  else if (/PREPARE|BRAKE|MOVE/.test(c.name)) html += `<p>주행·승강 이동 준비/실행 — Trav/Lift PDO, 브레이크 interlock.</p>`;
  else if (/LOADING|GET/.test(c.name)) html += `<p>적재(GET) — From 셀 포크 진출·리프트·화물.</p>`;
  else if (/UNLOADING|PUT/.test(c.name)) html += `<p>이재(PUT) — To 셀 포크 진출·리프트 다운.</p>`;
  else if (/ERROR|STOP/.test(c.name)) html += `<p>에러/정지 — save_error_code, 감속 정지 RunMode.</p>`;
  else if (/ORIGIN|SCAN|RACK|HORIZONTAL/.test(c.name)) html += `<p>원점·Setup·스캔·랙 설정.</p>`;
  else if (/HOME|RETURN/.test(c.name)) html += `<p>홈복귀 — 스테이션/대기 위치.</p>`;
  else if (/MANUAL/.test(c.name)) html += `<p>수동 시퀀스.</p>`;
  else html += `<p>RunMode <span class="mono">${esc(c.name)}</span> — dev_SRM.c L${c.line}.</p>`;

  html += buildAnalysisHtml(p, c.name);
  if (incoming.length) {
    html += `<h5>들어오는 경로 (${incoming.length}건)</h5><ul>`;
    for (const inc of incoming.slice(0, 15)) {
      html += `<li>L${inc.line} ← <span class="mono">${esc(inc.from)}</span></li>`;
    }
    if (incoming.length > 15) html += `<li>… 외 ${incoming.length - 15}건</li>`;
    html += `</ul>`;
  }
  return html;
}

module.exports = { autoAnalyzeFunction, autoAnalyzeRunCase, guessRole, extractPatterns };
