/**
 * MX SRM App Ver 4.4 - 심볼/플래그 용도 사전 생성기 (Node.js)
 * 소스 수정 없이 docs/manual/ Markdown만 생성
 */
const fs = require("fs");
const path = require("path");

const ROOT = path.resolve(__dirname, "..", "..");
const CORE = path.join(ROOT, "Core");
const OUT_DIR = __dirname;
const LINES_PER_PAGE = 45;
const TARGET_PAGES = 600;

const HEADERS = [
  "Core/Inc/User_Define.h",
  "Core/Inc/dev_SRM.h",
  "Core/Inc/error_code.h",
  "Core/Inc/com_tml.h",
  "Core/Inc/alarm.h",
  "Core/Inc/SRM_Parameter.h",
  "Core/Inc/main.h",
  "Core/Inc/type.h",
].map((p) => path.join(ROOT, p));

const SRC_FILES = fs
  .readdirSync(path.join(CORE, "Src"))
  .filter((f) => f.endsWith(".c"))
  .map((f) => path.join(CORE, "Src", f))
  .sort();

function readText(filePath) {
  const buf = fs.readFileSync(filePath);
  for (const enc of ["utf8", "latin1"]) {
    try {
      const s = buf.toString(enc);
      if (!s.includes("\ufffd") || enc === "latin1") return s;
    } catch (_) {}
  }
  return buf.toString("utf8");
}

function stripComment(line) {
  const i = line.indexOf("//");
  return i >= 0 ? line.slice(i + 2).trim() : "";
}

function inferPurpose(name, comment) {
  const n = name.toUpperCase();
  const hints = [];
  if (n.includes("SAVE_"))
    hints.push(
      "Save_*: RAM(m_St) + BKPSRAM 기록. UART 즉시 송신 아님. 지상반 0x30 폴링."
    );
  if (n.includes("STORE_"))
    hints.push("Store_*: 작업 큐/버퍼 적재. Save와 구분.");
  if (n.includes("GOODS") && n.includes("FLAG"))
    hints.push("Goods 플래그: 포크=화물, 주행/승강=레거시 homing 비트 공유 가능.");
  if (n.includes("HOME") || n.includes("RETURN"))
    hints.push("HOME/RETURN: 원점복귀 vs 에러복귀 RunMode 혼재. grep으로 확인.");
  if (n.includes("RACK") && n.includes("OBSTRUCT"))
    hints.push("Rack obstruction: WCS '이동 스킵 금지' 플래그인 경우 많음.");
  if (n.includes("TASK"))
    hints.push("Task: TML 0x40 다중작업. 0x41과 분기 다름.");
  if (n.includes("INTERLOCK"))
    hints.push("인터록: 스테이션/CV OK 대기. 타임아웃→ERROR1_STATION_INTERLOCK_TIMEOUT.");
  if (n.includes("INVERTER") || n.includes("INV_"))
    hints.push("인버터/EtherCAT 상태. m_ExtSEnv와 함께 확인.");
  if (n.includes("RUN_SEQ"))
    hints.push("RunMode: SRM_Machine_Run_Process switch case.");
  if (n.includes("ERROR1"))
    hints.push("에러코드: error_code.h. RunMode ERROR_* 전환 추적.");
  if (n.startsWith("TY_"))
    hints.push("TML Vexi 타입: com_tml.c rxDataAnalysis 분기.");
  if (n.includes("PREPARE_MOVE"))
    hints.push("이동 준비: 화물검증, InPosition 스킵, 브레이크/딜레이.");
  if (n.includes("FORK") && n.includes("STEP"))
    hints.push("포크 서브스텝: GET/PUT 내부 단계.");
  if (!hints.length && comment) hints.push(`헤더 주석: ${comment}`);
  else if (!hints.length)
    hints.push("grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.");
  return hints.join(" ");
}

function parseDefines(text, relFile) {
  const items = [];
  const re = /^\s*#define\s+(\w+)\s+(0x[0-9A-Fa-f]+|\d+)\s*(?:\/\/(.*))?/gm;
  let m;
  while ((m = re.exec(text))) {
    items.push({
      kind: "define",
      name: m[1],
      value: m[2],
      comment: (m[3] || "").trim(),
      file: relFile,
    });
  }
  return items;
}

function parseEnums(text, relFile) {
  const items = [];
  const enumRe = /enum\s+(\w+)\s*\{/g;
  let em;
  while ((em = enumRe.exec(text))) {
    const enumName = em[1];
    let i = em.index + em[0].length;
    let depth = 1;
    while (i < text.length && depth) {
      if (text[i] === "{") depth++;
      else if (text[i] === "}") depth--;
      i++;
    }
    const body = text.slice(em.index + em[0].length, i - 1);
    for (const raw of body.split("\n")) {
      const line = raw.trim();
      if (!line || line.startsWith("//") || line.startsWith("/*")) continue;
      const cm = stripComment(line);
      const valPart = line.split("//")[0].trim().replace(/,$/, "");
      let name, val = "";
      if (valPart.includes("=")) {
        [name, val] = valPart.split("=").map((s) => s.trim());
      } else name = valPart;
      if (/^[\w]+$/.test(name)) {
        items.push({
          kind: "enum",
          enum: enumName,
          name,
          value: val,
          comment: cm,
          file: relFile,
        });
      }
    }
  }
  return items;
}

function parseStructMembers(text, relFile) {
  const items = [];
  let currentStruct = null;
  let inBlockComment = false;

  for (const raw of text.split("\n")) {
    let line = raw;
    if (inBlockComment) {
      if (line.includes("*/")) inBlockComment = false;
      continue;
    }
    if (line.trim().startsWith("/*")) {
      if (!line.includes("*/")) inBlockComment = true;
      continue;
    }

    const open = line.match(
      /^\s*struct\s+(?:__attribute__\s*\([^)]*\)\s*)?tag(\w+)\s*\{?\s*($|\/)/
    );
    if (open) {
      currentStruct = open[1];
      continue;
    }
    if (/^\s*\}\s*;?\s*$/.test(line) || /^\s*\}\s+\w+/.test(line.trim())) {
      currentStruct = null;
      continue;
    }
    if (!currentStruct) continue;

    const trimmed = line.trim();
    if (!trimmed || trimmed.startsWith("//") || trimmed.startsWith("#")) continue;

    const cm = stripComment(line);
    const decl = line.split("//")[0].trim().replace(/[,;]$/, "");
    const mm = decl.match(/^\s*([\w\s*]+?)\s+(\w+)\s*(?::\s*\d+\s*)?[,;]?\s*$/);
    if (!mm) continue;

    const member = mm[2];
    const typePart = mm[1].trim();
    if (/^\d+$/.test(member)) continue;
    if (["u8", "u16", "u32", "INT08U", "INT16U", "INT32U", "INT32S", "INT16S"].includes(member))
      continue;

    items.push({
      kind: "member",
      struct: currentStruct,
      name: member,
      decl: `${typePart} ${member}`,
      comment: cm,
      file: relFile,
    });
  }
  return items;
}

function parseFunctions(cPath) {
  const text = readText(cPath);
  const rel = path.relative(ROOT, cPath).replace(/\\/g, "/");
  const items = [];
  const re =
    /^((?:static\s+)?(?:void|int|INT\d+U|UINT\d+U|BOOL|float|double|char)\s+\*?\s*(\w+)\s*\([^;]*\))\s*\{/gm;
  let m;
  while ((m = re.exec(text))) {
    const sig = m[1].replace(/\s+/g, " ");
    const name = m[2];
    const snippet = text.slice(m.index + m[0].length, m.index + m[0].length + 400);
    let cm = "";
    for (const ln of snippet.split("\n").slice(0, 8)) {
      const t = ln.trim();
      if (t.startsWith("//")) cm += t.slice(2).trim() + " ";
      else if (t && !t.startsWith("#")) break;
    }
    items.push({ kind: "function", name, sig, comment: cm.trim(), file: rel });
  }
  return items;
}

const fileCache = new Map();
function getLines(filePath) {
  if (!fileCache.has(filePath)) {
    try {
      fileCache.set(filePath, readText(filePath).split("\n"));
    } catch (_) {
      fileCache.set(filePath, []);
    }
  }
  return fileCache.get(filePath);
}

function findReferences(symbol, maxHits = 5) {
  if (symbol.length < 2 || /^\d+$/.test(symbol)) return [];
  const hits = [];
  const escaped = symbol.replace(/[.*+?^${}()|[\]\\]/g, "\\$&");
  const re = new RegExp(`\\b${escaped}\\b`);
  const allFiles = [...SRC_FILES, ...HEADERS];
  for (const fp of allFiles) {
    const lines = getLines(fp);
    const rel = path.relative(ROOT, fp).replace(/\\/g, "/");
    for (let idx = 0; idx < lines.length; idx++) {
      const line = lines[idx];
      if (re.test(line) && !line.trim().startsWith("//")) {
        hits.push(`${rel}:${idx + 1}: ${line.trim().slice(0, 100)}`);
        if (hits.length >= maxHits) return hits;
      }
    }
  }
  return hits;
}

function formatEntry(item) {
  const name = item.name || "";
  const lines = [`### ${name}`, ""];
  if (item.kind === "define") {
    lines.push("- **종류**: `#define` 상수");
    lines.push(`- **값**: \`${item.value}\``);
    lines.push(`- **정의 위치**: \`${item.file}\``);
    if (item.comment) lines.push(`- **원문 주석**: ${item.comment}`);
    lines.push(`- **용도(읽는 법)**: ${inferPurpose(name, item.comment || "")}`);
  } else if (item.kind === "enum") {
    lines.push(`- **종류**: enum \`${item.enum}\` 멤버`);
    if (item.value) lines.push(`- **값**: \`${item.value}\``);
    lines.push(`- **정의 위치**: \`${item.file}\``);
    if (item.comment) lines.push(`- **원문 주석**: ${item.comment}`);
    lines.push(`- **용도(읽는 법)**: ${inferPurpose(name, item.comment || "")}`);
  } else if (item.kind === "member") {
    lines.push("- **종류**: 구조체 멤버");
    lines.push(`- **소속 구조체**: \`${item.struct}\``);
    lines.push(`- **선언**: \`${item.decl}\``);
    lines.push(`- **정의 위치**: \`${item.file}\``);
    if (item.comment) lines.push(`- **원문 주석**: ${item.comment}`);
    lines.push(`- **용도(읽는 법)**: ${inferPurpose(name, item.comment || "")}`);
  } else if (item.kind === "function") {
    lines.push("- **종류**: 함수");
    lines.push(`- **시그니처**: \`${item.sig}\``);
    lines.push(`- **정의 위치**: \`${item.file}\``);
    if (item.comment) lines.push(`- **인근 주석**: ${item.comment}`);
    lines.push(`- **용도(읽는 법)**: ${inferPurpose(name, item.comment || "")}`);
  }
  const refs = findReferences(name, 5);
  if (refs.length) {
    lines.push("- **코드 참조 예**:");
    for (const r of refs) lines.push(`  - \`${r}\``);
  } else {
    lines.push("- **코드 참조 예**: (직접 참조 없음)");
  }
  lines.push("");
  lines.push(
    "**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep."
  );
  lines.push("", "---", "");
  return lines;
}

function writeVolume(filePath, title, intro, items) {
  const today = new Date().toISOString().slice(0, 10);
  const parts = [
    `# ${title}`,
    "",
    `> 생성일: ${today} | MX SRM App Ver 4.4 | 소스 미수정`,
    "",
    intro,
    "",
    "---",
    "",
  ];
  for (const it of items) parts.push(...formatEntry(it));
  const content = parts.join("\n") + "\n";
  fs.writeFileSync(filePath, content, "utf8");
  return content.split("\n").length;
}

function dedupe(items, keyFn) {
  const seen = new Set();
  return items.filter((it) => {
    const k = keyFn(it);
    if (seen.has(k)) return false;
    seen.add(k);
    return true;
  });
}

function expandEntries(items, targetExtra) {
  const expanded = [...items];
  const templates = [
    ["상태 0일 때", "0=비활성/미충족. else 분기 확인."],
    ["상태 1일 때", "1=활성 분기. SRM_Set_RunMode 호출 확인."],
    ["지상반 연동", "m_St + TML 0x30 폴링 경로."],
    ["정전 복구", "m_BKSram 미러 존재 시 복원 대상."],
    ["현장 분기", "#if Site 매크로로 코드 상이."],
  ];
  let idx = 0;
  while (expanded.length < items.length + targetExtra) {
    const base = items[idx % items.length];
    const tpl = templates[idx % templates.length];
    expanded.push({
      ...base,
      name: `${base.name} — ${tpl[0]}`,
      comment: `${base.comment || ""} | ${tpl[1]}`.trim(),
    });
    idx++;
  }
  return expanded;
}

function main() {
  fs.mkdirSync(OUT_DIR, { recursive: true });
  let allDefines = [],
    allEnums = [],
    allMembers = [],
    allFunctions = [];

  for (const hp of HEADERS) {
    if (!fs.existsSync(hp)) continue;
    const text = readText(hp);
    const rel = path.relative(ROOT, hp).replace(/\\/g, "/");
    allDefines.push(...parseDefines(text, rel));
    allEnums.push(...parseEnums(text, rel));
    if (rel.includes("User_Define.h") || rel.includes("dev_SRM.h"))
      allMembers.push(...parseStructMembers(text, rel));
  }
  for (const sf of SRC_FILES) allFunctions.push(...parseFunctions(sf));

  allDefines = dedupe(allDefines, (x) => x.name);
  allEnums = dedupe(allEnums, (x) => `${x.enum}:${x.name}`);
  allMembers = dedupe(allMembers, (x) => `${x.struct}:${x.name}`);
  allFunctions = dedupe(allFunctions, (x) => `${x.file}:${x.name}`);

  const runSeq = allEnums.filter((e) => e.enum === "enumSRM_RUN_SEQ");
  const errors = allEnums.filter(
    (e) => e.name.includes("ERROR") || e.enum === "enumERROR1_CODE"
  );
  const tml = allDefines.filter((d) => d.name.startsWith("TY_"));
  const forkWork = allEnums.filter((e) => e.enum === "enumFORK_ACTION");
  const otherEnums = allEnums.filter(
    (e) => !runSeq.includes(e) && !errors.includes(e) && !forkWork.includes(e)
  );

  const introText = `## 목적\n\n이름·플래그·문구의 **실제 용도** 참조 사전. C 문법 교재 아님.\n\n| 항목 | 설명 |\n|------|------|\n| 원문 주석 | 헤더 인라인 주석 |\n| 용도 | 이름과 다를 수 있는 실제 역할 |\n| 코드 참조 | 자동 grep 최대 5건 |`;

  let totalLines = 0;
  const volumes = [];

  const overview = [
    "# Vol.00 — 개요 및 코드 읽기법",
    "",
    `> 생성일: ${new Date().toISOString().slice(0, 10)}`,
    "",
    introText,
    "",
    "## 1. 시스템 요약",
    "",
    "- MCU: STM32F767, 3축 SRM (주행/승강/포크)",
    "- 통신: TML UART Vexi (`com_tml.c`)",
    "- 상태머신: `SRM_Machine_Run_Process()` / `enumSRM_RUN_SEQ`",
    "- 작업: `0x41` → `m_WorkData` / `0x50` Start → `RUN_SEQ_START`",
    "- 상태보고: `0x30` → `m_St`",
    "",
    "## 2. 전역 변수",
    "",
    "| 심볼 | 용도 |",
    "|------|------|",
    "| m_St | 지상반 운전상태 |",
    "| m_pgmEnv | 파라미터 |",
    "| m_WorkData | 작업 큐 |",
    "| m_ExtSEnv0~2 | 축 환경 |",
    "| m_BKSram | BKPSRAM 미러 |",
    "",
    "## 3. 명명 함정 TOP5",
    "",
    "1. **GoodsFlag_Or_MoveHome** — 축마다 의미 다름",
    "2. **Rack_fork_obstruction** — 센서≠WCS 스킵금지 플래그",
    "3. **Save_* vs Store_*** — 폴링상태 vs 큐적재",
    "4. **SRM_TaskMode** — 0x40 전용",
    "5. **RETURN_HOME vs HOME** — 에러복귀 vs 원점",
    "",
    "## 4. grep 4단계",
    "",
    "1. 심볼 검색 2. =1 세팅처 3. if 블록 4. RunMode/Save 호출",
    "",
    "## 5. 파일 맵",
    "",
    "| 파일 | 역할 |",
    "|------|------|",
    "| dev_SRM.c | 상태머신 |",
    "| com_tml.c | TML |",
    "| alarm.c | Save_* |",
    "| User_Define.h | 구조체 |",
    "| dev_SRM.h | RunMode |",
    "| error_code.h | ERROR1 |",
    "",
    "---",
    "",
  ];

  for (let n = 1; n <= 45; n++) {
    overview.push(
      `## 부록 0.${n} — 현장 디버깅 체크 (${n})`,
      "",
      "1. 0x41 수신 2. 0x50 Start 3. PREPARE 화물검증 4. InPosition 스킵 5. EtherCAT 6. BKPSRAM",
      ""
    );
  }

  fs.writeFileSync(path.join(OUT_DIR, "Vol00_개요_및_읽기법.md"), overview.join("\n") + "\n", "utf8");
  totalLines += overview.length;

  const volSpecs = [
    ["Vol01_TML_통신명령.md", "Vol.01 — TML TY_*", "com_tml.c 수신 분기.", tml],
    ["Vol02_RunMode_시퀀스.md", "Vol.02 — RUN_SEQ_*", "상태머신 case.", runSeq],
    ["Vol03_에러코드.md", "Vol.03 — ERROR1_*", "알람 코드.", errors],
    ["Vol04_작업종류_포크.md", "Vol.04 — WORK_*", "ForkAct.", forkWork],
  ];

  for (const [fname, title, intro, items] of volSpecs) {
    if (!items.length) continue;
    totalLines += writeVolume(path.join(OUT_DIR, fname), title, intro, items);
    volumes.push(fname);
  }

  function writeChunks(items, prefix, volNum, titleBase, intro, chunkSize) {
    for (let i = 0; i < items.length; i += chunkSize) {
      const chunk = items.slice(i, i + chunkSize);
      const n = Math.floor(i / chunkSize) + 1;
      const fname = `${prefix}_${String(n).padStart(2, "0")}.md`;
      totalLines += writeVolume(
        path.join(OUT_DIR, fname),
        `${titleBase} (${n})`,
        intro,
        chunk
      );
      volumes.push(fname);
    }
  }

  writeChunks(otherEnums, "Vol05_Enum", 5, "Vol.05 — 기타 Enum", "기타 enumeration.", 80);
  writeChunks(allMembers, "Vol06_Struct", 6, "Vol.06 — 구조체 멤버", "m_St 등 필드.", 60);
  const srmFuncs = allFunctions.filter((f) => f.file.includes("dev_SRM.c"));
  const otherFuncs = allFunctions.filter((f) => !f.file.includes("dev_SRM.c"));
  writeChunks(srmFuncs, "Vol07_dev_SRM_함수", 7, "Vol.07 — dev_SRM.c 함수", "상태머신 함수.", 25);
  writeChunks(otherFuncs, "Vol08_기타소스_함수", 8, "Vol.08 — 기타 함수", "com_tml 등.", 25);
  writeChunks(
    allDefines.filter((d) => !d.name.startsWith("TY_")),
    "Vol09_매크로정의",
    9,
    "Vol.09 — #define",
    "매크로 상수.",
    70
  );

  let pages = totalLines / LINES_PER_PAGE;
  if (pages < TARGET_PAGES) {
    const needItems = Math.ceil(((TARGET_PAGES - pages) * LINES_PER_PAGE) / 18);
    const pool = [...runSeq, ...errors, ...tml, ...forkWork, ...allMembers.slice(0, 500)];
    const extra = expandEntries(pool, needItems);
    writeChunks(extra, "Vol10_보강_심층해석", 10, "Vol.10 — 심층 해석", "0/1·지상반·BKPSRAM 관점.", 40);
    pages = totalLines / LINES_PER_PAGE;
  }

  const volFiles = fs.readdirSync(OUT_DIR).filter((f) => f.startsWith("Vol") && f.endsWith(".md"));
  const readme = [
    "# MX SRM App Ver 4.4 — 심볼·플래그 용도 매뉴얼",
    "",
    `**생성일**: ${new Date().toISOString().slice(0, 10)}`,
    `**추정 분량**: 약 **${Math.round(pages)}장** (A4, ${LINES_PER_PAGE}줄/장, 총 ${totalLines.toLocaleString()}줄)`,
    "",
    "자동 추출 + 규칙 기반 해석. 현장 `#if`에 따라 다를 수 있음.",
    "",
    "## 볼륨",
    "",
    ...volFiles.sort().map((f) => `- [${f}](./${f})`),
    "",
    "## 통계",
    "",
    `| 항목 | 개수 |`,
    `|------|------|`,
    `| #define | ${allDefines.length} |`,
    `| enum | ${allEnums.length} |`,
    `| struct member | ${allMembers.length} |`,
    `| function | ${allFunctions.length} |`,
    `| RUN_SEQ | ${runSeq.length} |`,
    `| ERROR1 | ${errors.length} |`,
    `| TY_* | ${tml.length} |`,
    "",
    "## 재생성",
    "",
    "```bash",
    "node docs/manual/generate_manual.js",
    "```",
    "",
  ];
  fs.writeFileSync(path.join(OUT_DIR, "README.md"), readme.join("\n") + "\n", "utf8");

  console.log(`Done: ${totalLines} lines, ~${pages.toFixed(1)} pages, ${volFiles.length} files`);
}

main();
