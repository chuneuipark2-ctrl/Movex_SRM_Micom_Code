/**
 * SRM 전체 심볼 용도 사전 (HTML)
 * - 구조체 멤버, 전역/static 변수, enum, #define, 함수
 * - 출력: SRM_전체심볼_용도사전.html
 */
const fs = require("fs");
const path = require("path");

const ROOT = path.resolve(__dirname, "..", "..");
const CORE = path.join(ROOT, "Core");
const INC = path.join(CORE, "Inc");
const SRC = path.join(CORE, "Src");
const OUT = __dirname;

const HEADER_FILES = [
  "User_Define.h",
  "dev_SRM.h",
  "error_code.h",
  "com_tml.h",
  "alarm.h",
  "SRM_Parameter.h",
  "main.h",
].map((f) => path.join(INC, f));

const DEV_SRM = path.join(SRC, "dev_SRM.c");

const STRUCT_ROOTS = [
  { var: "m_St", type: "StatusSTR", title: "m_St (StatusSTR) — 지상반 0x30 상태", note: "지상반 폴링 운전상태. Save_*가 여기 기록." },
  { var: "m_pgmEnv", type: "PGMEnvSTR", title: "m_pgmEnv (PGMEnvSTR) — MCU 내부", note: "RunMode, 타이머, 통신, 내부 플래그." },
  { var: "m_BKSram", type: "BKSRamSTR", title: "m_BKSram — 정전복구", note: "BKPSRAM 미러." },
  { var: "m_WorkData", type: "SRM_WorkDataSTR", title: "m_WorkData — 작업 큐", note: "dev_SRM.c static[30]. GET/PUT 사이클." },
  { var: "m_ExtSEnv0", type: "ExtFlashSEnv0", title: "m_ExtSEnv0 — 주행 파라미터", note: "셀/랙/주행 드라이브 설정." },
  { var: "m_ExtSEnv1", type: "ExtFlashSEnv1", title: "m_ExtSEnv1 — 승강/스테이션", note: "승강, 스테이션, 인터록 설정." },
  { var: "m_ExtSEnv2", type: "ExtFlashSEnv2", title: "m_ExtSEnv2 — 포크/제어", note: "포크, 타임아웃, 제어 파라미터." },
  { var: "WorkCmd", type: "WorkCmdSTR", title: "WorkCmdSTR — 0x41 수신", note: "com_tml rxCmdOrder 파싱 형식." },
];

function read(fp) {
  return fs.readFileSync(fp, "utf8");
}

function esc(s) {
  return String(s ?? "")
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;");
}

// ─── struct parser (from generate_struct_manual.js) ───
function parseStructs(text) {
  const byTypedef = new Map();
  const byTag = new Map();
  const lines = text.split("\n");
  let i = 0;
  while (i < lines.length) {
    const tagMatch = lines[i].match(/struct\s+(?:__attribute__\s*\(\([^)]*\)\)\s*)?tag(\w+)/);
    if (!tagMatch) {
      i++;
      continue;
    }
    const tag = tagMatch[1];
    let depth = 0;
    let started = false;
    if (lines[i].includes("{")) {
      depth = 1;
      started = true;
    }
    const memberLines = [];
    i++;
    while (i < lines.length) {
      const ln = lines[i];
      if (!started) {
        if (ln.trim() === "{" || ln.trim().startsWith("{")) {
          depth = 1;
          started = true;
          i++;
          continue;
        }
        i++;
        continue;
      }
      for (const ch of ln) {
        if (ch === "{") depth++;
        else if (ch === "}") depth--;
      }
      if (depth > 0) memberLines.push(ln);
      i++;
      if (depth <= 0) break;
    }
    let typedef = tag;
    for (let j = i - 1; j < Math.min(i + 4, lines.length); j++) {
      const tm = lines[j].match(/typedef\s+struct\s+tag\w+\s+(\w+)\s*;/);
      if (tm) {
        typedef = tm[1];
        break;
      }
      const tm2 = lines[j].match(/\}\s*(\w+)\s*;/);
      if (tm2) {
        typedef = tm2[1];
        break;
      }
    }
    const members = [];
    let inUnion = false;
    let unionDepth = 0;
    for (const raw of memberLines) {
      const t = raw.trim();
      if (!t || t.startsWith("/*") || t.startsWith("*") || t.startsWith("#")) continue;
      if (t.startsWith("union")) {
        inUnion = true;
        unionDepth = t.includes("{") ? 1 : 0;
        continue;
      }
      if (inUnion) {
        if (t.includes("{")) unionDepth += (t.match(/\{/g) || []).length;
        if (t.includes("}")) unionDepth -= (t.match(/\}/g) || []).length;
        const bt = t.match(/^(\w+)\s+(\w+)\s*;/);
        if (bt) members.push({ name: bt[2], type: bt[1], comment: "", isUnionBit: true });
        if (unionDepth <= 0) inUnion = false;
        continue;
      }
      const cm = raw.includes("//") ? raw.split("//")[1].trim() : "";
      const decl = raw.split("//")[0].trim().replace(/[,;]$/, "");
      if (!decl || decl === "{" || decl === "}") continue;
      const bf = decl.match(/^([\w\s*]+?)\s+(\w+)\s*:\s*(\d+)\s*$/);
      if (bf) {
        members.push({ name: bf[2], type: `bit:${bf[3]}`, comment: cm, isBitfield: true });
        continue;
      }
      const arr = decl.match(/^([\w\s*]+?)\s+(\w+)\s*\[([^\]]+)\]\s*$/);
      if (arr) {
        members.push({ name: arr[2], type: `${arr[1].trim()}[${arr[3]}]`, comment: cm, isArray: true });
        continue;
      }
      const norm = decl.match(/^([\w\s*]+?)\s+(\w+)\s*$/);
      if (norm && !["u8", "u16", "u32"].includes(norm[2])) {
        members.push({ name: norm[2], type: norm[1].trim(), comment: cm });
      }
    }
    const info = { tag, typedef, members };
    byTypedef.set(typedef, info);
    byTag.set(tag, info);
  }
  return { byTypedef, byTag };
}

function resolveType(t, maps) {
  const n = t.replace(/\*$/, "").replace(/\[\d+\]$/, "").trim();
  return maps.byTypedef.get(n) || maps.byTag.get(n) || null;
}

function flattenStruct(typeName, prefix, maps, depth = 0, maxDepth = 3) {
  const struct = maps.byTypedef.get(typeName) || maps.byTag.get(typeName);
  if (!struct) return [];
  const rows = [];
  for (const m of struct.members) {
    const fullPath = `${prefix}.${m.name}`;
    const baseType = m.type.replace(/\[.*\]$/, "").trim();
    rows.push({ path: fullPath, member: m.name, type: m.type, comment: m.comment, kind: "struct" });
    if (m.isBitfield || m.isUnionBit) continue;
    const nested = resolveType(baseType, maps);
    if (!nested) continue;
    if (["DeviceStatus1", "DeviceStatus2", "DeviceMode_t", "PositionFlag1", "PositionFlag2"].includes(baseType)) {
      const bitM = nested.members.find((x) => x.name === "Bit");
      if (bitM) {
        const bs = resolveType(bitM.type, maps);
        if (bs) {
          for (const bm of bs.members) {
            rows.push({
              path: `${fullPath}.Bit.${bm.name}`,
              member: bm.name,
              type: bm.type,
              comment: bm.comment,
              kind: "struct-bit",
            });
          }
        }
      }
      continue;
    }
    if (depth < maxDepth) {
      const cp = m.isArray && !/INT\d+U/.test(baseType) ? `${fullPath}[i]` : fullPath;
      rows.push(...flattenStruct(nested.typedef, cp, maps, depth + 1, maxDepth));
    }
  }
  return rows;
}

const UNION_BIT_WRAPPERS = [
  "DeviceStatus1",
  "DeviceStatus2",
  "DeviceMode_t",
  "PositionFlag1",
  "PositionFlag2",
];

function memberToTreeNode(m, maps, depth, maxDepth) {
  const label = m.isArray ? `${m.name}[]` : m.name;
  const node = {
    label,
    type: m.type,
    comment: m.comment || "",
    children: [],
  };
  if (m.isBitfield || m.isUnionBit) return node;

  const baseType = m.type.replace(/\[.*\]$/, "").trim();
  const nested = resolveType(baseType, maps);
  if (!nested) return node;

  if (UNION_BIT_WRAPPERS.includes(baseType)) {
    const bitM = nested.members.find((x) => x.name === "Bit");
    const bs = bitM ? resolveType(bitM.type, maps) : null;
    if (bs) {
      node.children = bs.members.map((bm) => ({
        label: `Bit.${bm.name}`,
        type: bm.type,
        comment: bm.comment || "",
        children: [],
      }));
    }
    return node;
  }

  if (depth >= maxDepth) return node;
  node.children = nested.members.map((cm) => memberToTreeNode(cm, maps, depth + 1, maxDepth));
  return node;
}

function buildStructTree(varName, typeName, maps, maxDepth = 4) {
  const struct = maps.byTypedef.get(typeName) || maps.byTag.get(typeName);
  if (!struct) {
    return { label: varName, type: typeName, comment: "", children: [] };
  }
  return {
    label: varName,
    type: typeName,
    comment: "",
    children: struct.members.map((m) => memberToTreeNode(m, maps, 1, maxDepth)),
  };
}

let mermaidSeq = 0;
function mermaidSafeId(prefix) {
  mermaidSeq++;
  return `N${mermaidSeq}_${prefix.replace(/[^a-zA-Z0-9]/g, "")}`;
}

function buildMermaidChart(tree, depthLimit = 2, nodeLimit = 48) {
  const lines = ["flowchart TB"];
  const rootId = mermaidSafeId(tree.label);
  lines.push(
    `  ${rootId}["<b>${tree.label}</b><br/><i>${tree.type}</i>"]:::root`
  );
  let count = 1;

  function walk(parentId, node, depth) {
    if (depth > depthLimit || count >= nodeLimit) return;
    for (const ch of node.children || []) {
      if (count >= nodeLimit) break;
      const id = mermaidSafeId(`${node.label}_${ch.label}`);
      const lbl = ch.label.replace(/"/g, "'");
      const typ = (ch.type || "").replace(/"/g, "'").slice(0, 40);
      const cm = (ch.comment || "").replace(/"/g, "'").slice(0, 30);
      const extra = cm ? `<br/><small>${cm}</small>` : "";
      lines.push(`  ${id}["${lbl}<br/><i>${typ}</i>${extra}"]`);
      lines.push(`  ${parentId} --> ${id}`);
      count++;
      if (ch.children?.length && depth < depthLimit) walk(id, ch, depth + 1);
    }
  }

  walk(rootId, tree, 1);
  lines.push("  classDef root fill:#1a6b3c,stroke:#0d4a28,color:#fff,font-weight:bold");
  lines.push("  classDef mid fill:#e8f5ee,stroke:#1a6b3c,color:#111");
  if (count > 1) lines.push(`  class ${rootId} root`);
  return lines.join("\n");
}

function renderTreeLi(node, depth = 0) {
  const typeSpan = node.type
    ? `<span class="t-type" title="타입">${esc(node.type)}</span>`
    : "";
  const cmSpan = node.comment
    ? `<span class="t-cm" title="주석">${esc(node.comment)}</span>`
    : "";
  const hasKids = node.children && node.children.length > 0;

  if (!hasKids) {
    return `<li class="tree-leaf"><span class="t-name">${esc(node.label)}</span>${typeSpan}${cmSpan}</li>`;
  }

  const open = depth < 1 ? " open" : "";
  const kids = node.children.map((c) => renderTreeLi(c, depth + 1)).join("");
  return `<li class="tree-branch"><details${open}><summary><span class="t-name">${esc(node.label)}</span>${typeSpan}${cmSpan}<span class="t-badge">${node.children.length}</span></summary><ul>${kids}</ul></details></li>`;
}

function buildStructTreeSection(roots, maps) {
  mermaidSeq = 0;
  let html = `<h2 id="struct_tree">0. 구조체 포함 관계 (트리 · 다이어그램)</h2>
<div class="note">
  <b>접이식 트리</b>: 클릭해서 펼치기/접기. 상위 구조체 → 하위 멤버 → 중첩 구조체 포함 관계.<br>
  <b>Mermaid 다이어그램</b>: 2단계 개요 (인터넷 연결 시 렌더링). PDF 인쇄 전 페이지 로딩 완료 후 인쇄 권장.<br>
  <button type="button" class="tree-btn" onclick="treeExpandAll(true)">전체 펼치기</button>
  <button type="button" class="tree-btn" onclick="treeExpandAll(false)">전체 접기</button>
</div>`;

  for (const g of roots) {
    const maxD = g.type.startsWith("ExtFlash") ? 3 : g.type === "StatusSTR" ? 4 : 4;
    const tree = buildStructTree(g.var, g.type, maps, maxD);
    const chartId = `mermaid_${g.var.replace(/[^a-zA-Z0-9]/g, "_")}`;
    const chart = buildMermaidChart(tree, 2, g.type === "StatusSTR" ? 36 : 48);

    html += `<h3 id="tree_${esc(g.var)}">${esc(g.var)} <span class="kind">(${esc(g.type)})</span></h3>`;
    html += `<p class="tree-desc">${esc(g.note)}</p>`;
    html += `<div class="mermaid-wrap"><pre class="mermaid" id="${chartId}">${chart}</pre></div>`;
    html += `<div class="struct-tree-box"><ul class="struct-tree">${renderTreeLi(tree)}</ul></div>`;
  }
  return html;
}

// ─── source cache & grep ───
let SRC_CACHE = null;
function loadSrc() {
  if (SRC_CACHE) return SRC_CACHE;
  SRC_CACHE = new Map();
  for (const f of fs.readdirSync(SRC).filter((x) => x.endsWith(".c"))) {
    SRC_CACHE.set(f, read(path.join(SRC, f)).split("\n"));
  }
  for (const f of HEADER_FILES) {
    const bn = path.basename(f);
    if (!SRC_CACHE.has(bn)) SRC_CACHE.set(bn, read(f).split("\n"));
  }
  return SRC_CACHE;
}

function grepSymbol(name, limit = 5, globalHint = "") {
  if (!name || name.length < 2 || /^\d+$/.test(name)) return { writes: [], reads: [] };
  const escN = name.replace(/[.*+?^${}()|[\]\\]/g, "\\$&");
  const re = new RegExp(`\\b${escN}\\b`);
  const writes = [];
  const reads = [];
  for (const [file, lines] of loadSrc()) {
    for (let i = 0; i < lines.length; i++) {
      const line = lines[i];
      if (!re.test(line) || line.trim().startsWith("//")) continue;
      if (globalHint && !line.includes(globalHint) && !line.includes(name)) continue;
      const isW = /=/.test(line) && !/==|!=|<=|>=/.test(line);
      const e = `${file}:${i + 1}`;
      if (isW && writes.length < limit) writes.push(e);
      else if (!isW && reads.length < limit) reads.push(e);
      if (writes.length >= limit && reads.length >= limit) return { writes, reads };
    }
  }
  return { writes, reads };
}

function filesFromUsage(u) {
  return [...new Set([...u.writes, ...u.reads].map((x) => x.split(":")[0]))].slice(0, 4).join(", ");
}

function inferPurpose(name, kind, comment, pathStr = "") {
  const n = name.toUpperCase();
  const p = pathStr.toUpperCase();
  const rules = [
    [/SAVE_/, "Save_*: m_St/BKPSRAM 기록. UART 즉시 송신 아님."],
    [/STORE_/, "Store_*: m_WorkData/내부 큐에 작업 적재."],
    [/SRM_MACHINE_RUN|SRM_Set_RunMode/, "상태머신 RunMode 전환/실행."],
    [/CHECK_|_CHECK/, "조건 검사. 실패 시 에러/분기."],
    [/RX|TX_|SEND_|RECV/, "통신 송수신 관련."],
    [/ERROR|FAULT|ALARM/, "에러/알람 처리."],
    [/ORIGIN|HOME|REFERENCE/, "원점/홈/기준점 동작."],
    [/FORK/, "포크 축 제어/상태."],
    [/TRAV|TRAVEL/, "주행 축."],
    [/LIFT|HOIST/, "승강 축."],
    [/ETHERCAT|INVERTOR|INV_/, "인버터/EtherCAT."],
    [/GOODSFLAG_OR_MOVEHOME/, "포크=화물, 주행/승강=홈(레거시). 축 맥락 필수."],
    [/RACK_FORK_OBSTRUCTION/, "WCS 이동스킵 금지 플래그."],
    [/SRM_RUNMODE/, "enumSRM_RUN_SEQ 현재값."],
    [/OPERATIONFLAG/, "0x41 작업 옵션 비트."],
    [/TY_/, "TML Vexi 프레임 타입."],
    [/ERROR1_/, "error_code.h 알람 코드."],
    [/RUN_SEQ_/, "상태머신 case 단계."],
    [/WORK_/, "ForkAct/작업 종류 enum."],
    [/INTERLOCK/, "스테이션/CV 인터록."],
    [/MX_|HAL_|GPIO/, "STM32 Cube HAL 초기화 (보드 레벨)."],
  ];
  for (const [re, d] of rules) {
    if (re.test(n) || re.test(p)) return d;
  }
  if (comment) return comment;
  if (kind === "function") return "호출처 grep으로 역할 확인.";
  if (kind === "enum") return "enum 멤버. switch/case 분기에 사용.";
  if (kind === "define") return "#define 상수/매크로.";
  if (kind === "global") return "전역 변수. 읽기/쓰기 파일 참조 확인.";
  return "코드 참조로 용도 확인.";
}

function makeRow({ path, type, comment, kind, globalHint = "" }) {
  const member = path.split(".").pop().replace(/\[.*\]/, "");
  const usage = grepSymbol(member, 5, globalHint.includes(".") ? globalHint.split(".")[0] : globalHint);
  return {
    path,
    type: type || kind,
    comment: comment || "",
    purpose: inferPurpose(member, kind, comment, path),
    files: filesFromUsage(usage),
    kind,
  };
}

// ─── parsers ───
function parseExternGlobals(text, file) {
  const rows = [];
  for (const line of text.split("\n")) {
    const m = line.match(/^\s*extern\s+([\w\s*]+?)\s+(\w+)\s*;\s*(?:\/\/(.*))?/);
    if (!m) continue;
    const name = m[2];
    if (name.startsWith("n") && name.endsWith("bits")) continue;
    rows.push(
      makeRow({
        path: name,
        type: m[1].trim(),
        comment: (m[3] || "").trim(),
        kind: "global",
        globalHint: name,
      })
    );
  }
  return rows;
}

function parseStaticGlobals(cPath) {
  const text = read(cPath);
  const file = path.basename(cPath);
  const rows = [];
  const re = /^\s*static\s+([\w\s*]+?)\s+(\w+)(\s*\[[^\]]*\])?\s*(?:=\s*[^;]+)?;/gm;
  let m;
  while ((m = re.exec(text))) {
    const name = m[2];
    if (name.startsWith("MX_") || name.startsWith("Init")) continue;
    rows.push(
      makeRow({
        path: `${file}:${name}`,
        type: m[1].trim() + (m[3] || ""),
        comment: "",
        kind: "static",
        globalHint: name,
      })
    );
  }
  return rows;
}

function parseEnums(text, file) {
  const rows = [];
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
      if (!line || line.startsWith("//")) continue;
      const cm = line.includes("//") ? line.split("//")[1].trim() : "";
      const vp = line.split("//")[0].trim().replace(/,$/, "");
      let name, val = "";
      if (vp.includes("=")) [name, val] = vp.split("=").map((s) => s.trim());
      else name = vp;
      if (!/^[\w]+$/.test(name)) continue;
      rows.push(
        makeRow({
          path: `${enumName}.${name}`,
          type: val ? `=${val}` : "enum",
          comment: cm,
          kind: "enum",
          globalHint: name,
        })
      );
    }
  }
  return rows;
}

function parseDefines(text) {
  const rows = [];
  const re = /^\s*#define\s+(\w+)\s+(\S+)\s*(?:\/\/(.*))?/gm;
  let m;
  while ((m = re.exec(text))) {
    rows.push(
      makeRow({
        path: m[1],
        type: m[2],
        comment: (m[3] || "").trim(),
        kind: "define",
        globalHint: m[1],
      })
    );
  }
  return rows;
}

function parseFunctions(cPath) {
  const text = read(cPath);
  const file = path.basename(cPath);
  const rows = [];
  const re =
    /\/\*\*([\s\S]*?)\*\/\s*((?:static\s+)?(?:void|int|INT\d+U|UINT\d+U|BOOL|float|double|char)\s+\*?\s*(\w+)\s*\([^;]*\))\s*\{/g;
  let m;
  while ((m = re.exec(text))) {
    const doc = m[1].replace(/\s*\*\s*@?\w*\s*/g, " ").replace(/\s+/g, " ").trim();
    const sig = m[2].replace(/\s+/g, " ");
    const name = m[3];
    rows.push(
      makeRow({
        path: `${file} :: ${name}`,
        type: sig.slice(0, 120),
        comment: doc.slice(0, 200),
        kind: "function",
        globalHint: name,
      })
    );
  }
  // functions without doxygen
  const re2 =
    /^((?:static\s+)?(?:void|int|INT\d+U|UINT\d+U|BOOL|float|double|char)\s+\*?\s*(\w+)\s*\([^;]*\))\s*\{/gm;
  const seen = new Set(rows.map((r) => r.path));
  while ((m = re2.exec(text))) {
    const name = m[2];
    const key = `${file} :: ${name}`;
    if (seen.has(key) || name.startsWith("MX_")) continue;
    seen.add(key);
    rows.push(
      makeRow({
        path: key,
        type: m[1].replace(/\s+/g, " ").slice(0, 120),
        comment: "",
        kind: "function",
        globalHint: name,
      })
    );
  }
  return rows;
}

// ─── HTML ───
function buildHtml(sections, stats, treeBlock = "") {
  const css = `
    body { font-family: "Malgun Gothic", sans-serif; font-size: 10.5pt; line-height: 1.45; margin: 1.5cm 2cm; color: #111; }
    h1 { font-size: 22pt; border-bottom: 3px solid #1a5; padding-bottom: 10px; }
    h2 { font-size: 14pt; margin-top: 32px; color: #fff; background: #2c3e50; padding: 10px 14px; page-break-before: always; }
    h2:first-of-type { page-break-before: avoid; }
    h3 { font-size: 11pt; margin: 20px 0 8px; color: #1a5; border-bottom: 1px solid #ccc; }
    .meta { background: #f0f7f0; padding: 12px 16px; border-radius: 6px; margin: 16px 0; }
    .note { background: #fafafa; padding: 8px 12px; border-left: 4px solid #1a5; margin: 8px 0 14px; font-size: 10pt; }
    table { width: 100%; border-collapse: collapse; margin-bottom: 24px; font-size: 9.5pt; }
    th { background: #34495e; color: #fff; padding: 7px 8px; text-align: left; position: sticky; top: 0; }
    td { border: 1px solid #ddd; padding: 5px 8px; vertical-align: top; }
    tr:nth-child(even) td { background: #f9f9f9; }
    .path { font-family: Consolas, monospace; font-size: 9pt; color: #055; word-break: break-all; }
    .kind { font-size: 8pt; color: #888; }
    .toc { columns: 2; font-size: 10pt; line-height: 1.8; }
    .toc a { color: #066; text-decoration: none; }
    .toc a:hover { text-decoration: underline; }
    /* ── 구조체 트리 ── */
    .tree-btn { margin: 4px 6px 4px 0; padding: 5px 12px; font-size: 9pt; cursor: pointer;
      background: #1a6b3c; color: #fff; border: none; border-radius: 4px; }
    .tree-btn:hover { background: #0d4a28; }
    .tree-desc { font-size: 10pt; color: #444; margin: 4px 0 10px; }
    .struct-tree-box { background: #fafcfa; border: 1px solid #c8e0d0; border-radius: 8px;
      padding: 14px 18px; margin: 12px 0 28px; overflow-x: auto; }
    ul.struct-tree { list-style: none; margin: 0; padding-left: 0; }
    ul.struct-tree ul { list-style: none; margin: 4px 0 4px 0; padding-left: 22px;
      border-left: 2px solid #b8d4c4; }
    .tree-branch > details > summary { cursor: pointer; padding: 4px 6px; border-radius: 4px; list-style: none; }
    .tree-branch > details > summary::-webkit-details-marker { display: none; }
    .tree-branch > details > summary::before { content: "▶ "; color: #1a6b3c; font-size: 9pt; }
    .tree-branch > details[open] > summary::before { content: "▼ "; }
    .tree-branch > details > summary:hover { background: #e8f5ee; }
    .tree-leaf { padding: 3px 6px 3px 18px; position: relative; }
    .tree-leaf::before { content: "•"; position: absolute; left: 4px; color: #1a6b3c; }
    .t-name { font-family: Consolas, monospace; font-weight: 600; color: #055; font-size: 9.5pt; }
    .t-type { font-family: Consolas, monospace; font-size: 8.5pt; color: #666; margin-left: 8px;
      background: #eee; padding: 1px 6px; border-radius: 3px; }
    .t-cm { font-size: 8.5pt; color: #1a6b3c; margin-left: 8px; }
    .t-badge { font-size: 7.5pt; background: #1a6b3c; color: #fff; padding: 1px 6px;
      border-radius: 10px; margin-left: 6px; }
    .mermaid-wrap { background: #fff; border: 1px solid #ddd; border-radius: 8px;
      padding: 16px; margin: 10px 0 16px; overflow-x: auto; }
    .mermaid-wrap .mermaid { margin: 0; }
    @media print {
      h2 { page-break-before: always; }
      th { position: static; }
      .tree-branch > details { open: true; }
      .tree-branch > details > summary::before { content: "▼ "; }
      .mermaid-wrap { page-break-inside: avoid; }
    }
  `;

  const treeScript = `
<script src="https://cdn.jsdelivr.net/npm/mermaid@10/dist/mermaid.min.js"></script>
<script>
  mermaid.initialize({ startOnLoad: true, theme: "neutral", flowchart: { useMaxWidth: true, htmlLabels: true } });
  function treeExpandAll(open) {
    document.querySelectorAll(".struct-tree details").forEach(function(d) { d.open = open; });
  }
</script>`;

  let body = `<h1>MX SRM — 전체 변수·함수·심볼 용도 사전</h1>
<div class="meta">
  <b>생성일</b>: ${new Date().toISOString().slice(0, 10)} &nbsp;|&nbsp;
  <b>Ver</b> 4.4 &nbsp;|&nbsp;
  <b>총 항목</b>: ${stats.total.toLocaleString()} &nbsp;|&nbsp;
  추정 ${stats.pages}장 (A4)
</div>
<div class="note">
  <b>용도</b>: 구조체 멤버, 전역/static 변수, enum, #define, 함수 이름이 <b>실제로 무엇에 쓰이는지</b> 정리.<br>
  <b>PDF</b>: 브라우저 인쇄 → PDF로 저장 &nbsp;|&nbsp; <b>검색</b>: Ctrl+F &nbsp;|&nbsp;
  <b>구조체 트리</b>: <a href="#struct_tree">섹션 0</a> (포함 관계 다이어그램)
</div>
${treeBlock}
<h2 id="toc">목차</h2><div class="toc"><ul>
<li><a href="#struct_tree"><b>0. 구조체 포함 관계 (트리)</b></a></li>`;

  for (const sec of sections) {
    body += `<li><a href="#${sec.id}">${esc(sec.title)}</a> <span class="kind">(${sec.rows.length})</span></li>`;
  }
  body += `</ul></div>`;

  for (const sec of sections) {
    body += `<h2 id="${sec.id}">${esc(sec.title)}</h2>`;
    if (sec.note) body += `<div class="note">${esc(sec.note)}</div>`;

    const chunk = 400;
    for (let c = 0; c < sec.rows.length; c += chunk) {
      const part = sec.rows.slice(c, c + chunk);
      if (sec.rows.length > chunk) {
        body += `<h3>${esc(sec.title)} — ${c + 1}~${c + part.length}</h3>`;
      }
      body += `<table><thead><tr>
        <th style="width:26%">이름 / 경로</th>
        <th style="width:12%">종류·타입</th>
        <th style="width:18%">원문 주석</th>
        <th style="width:28%">실제 용도</th>
        <th style="width:16%">사용 파일</th>
      </tr></thead><tbody>`;
      for (const r of part) {
        body += `<tr>
          <td class="path">${esc(r.path)}</td>
          <td><span class="kind">${esc(r.kind)}</span><br>${esc(r.type)}</td>
          <td>${esc(r.comment || "-")}</td>
          <td>${esc(r.purpose)}</td>
          <td>${esc(r.files || "-")}</td>
        </tr>`;
      }
      body += `</tbody></table>`;
    }
  }

  return `<!DOCTYPE html><html lang="ko"><head><meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>SRM 전체 심볼 용도 사전</title><style>${css}</style></head><body>${body}${treeScript}</body></html>`;
}

function chunkSection(id, title, note, rows, maxPerSection = 350) {
  if (rows.length <= maxPerSection) return [{ id, title, note, rows }];
  const out = [];
  for (let i = 0; i < rows.length; i += maxPerSection) {
    const n = Math.floor(i / maxPerSection) + 1;
    out.push({
      id: `${id}_${n}`,
      title: `${title} (${n})`,
      note,
      rows: rows.slice(i, i + maxPerSection),
    });
  }
  return out;
}

function main() {
  console.log("Loading sources...");
  const headerText = HEADER_FILES.map(read).join("\n") + "\n" + read(DEV_SRM);
  const maps = parseStructs(headerText);
  const devMaps = parseStructs(read(DEV_SRM));
  for (const [k, v] of devMaps.byTypedef) if (!maps.byTypedef.has(k)) maps.byTypedef.set(k, v);

  loadSrc();
  const sections = [];

  console.log("Struct trees...");
  const treeBlock = buildStructTreeSection(STRUCT_ROOTS, maps);

  // 트리 전용 경량 HTML (빠른 참조)
  const treeCss = `
    .tree-btn{margin:4px 6px 4px 0;padding:5px 12px;font-size:9pt;cursor:pointer;background:#1a6b3c;color:#fff;border:none;border-radius:4px}
    .note{background:#fafafa;padding:8px 12px;border-left:4px solid #1a5;margin:8px 0 14px;font-size:10pt}
    h2{font-size:14pt;background:#2c3e50;color:#fff;padding:10px 14px}
    h3{color:#1a5;border-bottom:1px solid #ccc}
    .struct-tree-box{background:#fafcfa;border:1px solid #c8e0d0;border-radius:8px;padding:14px 18px;margin:12px 0 28px;overflow-x:auto}
    ul.struct-tree{list-style:none;margin:0;padding-left:0}
    ul.struct-tree ul{list-style:none;margin:4px 0;padding-left:22px;border-left:2px solid #b8d4c4}
    .tree-branch>details>summary{cursor:pointer;padding:4px 6px;list-style:none}
    .tree-branch>details>summary::-webkit-details-marker{display:none}
    .tree-branch>details>summary::before{content:"▶ ";color:#1a6b3c}
    .tree-branch>details[open]>summary::before{content:"▼ "}
    .t-name{font-family:Consolas,monospace;font-weight:600;color:#055}
    .t-type{font-family:Consolas,monospace;font-size:8.5pt;color:#666;margin-left:8px;background:#eee;padding:1px 6px;border-radius:3px}
    .t-cm{font-size:8.5pt;color:#1a6b3c;margin-left:8px}
    .t-badge{font-size:7.5pt;background:#1a6b3c;color:#fff;padding:1px 6px;border-radius:10px;margin-left:6px}
    .mermaid-wrap{background:#fff;border:1px solid #ddd;border-radius:8px;padding:16px;margin:10px 0 16px;overflow-x:auto}
    .kind{font-size:8pt;color:#888}`;
  const treeOnlyHtml = `<!DOCTYPE html><html lang="ko"><head><meta charset="utf-8">
<title>SRM 구조체 포함관계 트리</title><style>body{font-family:"Malgun Gothic",sans-serif;margin:1.5cm 2cm}${treeCss}</style></head><body>
<h1>MX SRM — 구조체 포함 관계</h1>
<p><a href="SRM_전체심볼_용도사전.html">← 전체 사전으로</a></p>
${treeBlock}
<script src="https://cdn.jsdelivr.net/npm/mermaid@10/dist/mermaid.min.js"></script>
<script>mermaid.initialize({startOnLoad:true,theme:"neutral"});
function treeExpandAll(o){document.querySelectorAll(".struct-tree details").forEach(d=>d.open=o);}
</script></body></html>`;
  fs.writeFileSync(path.join(OUT, "SRM_구조체트리.html"), treeOnlyHtml, "utf8");

  // 1. 전역 extern
  console.log("Globals...");
  const globals = parseExternGlobals(read(path.join(INC, "User_Define.h")), "User_Define.h");
  sections.push(...chunkSection("globals", "1. 전역 변수 (extern)", "main.c / User_Define.h 선언. DTCM 배치 변수 포함.", globals));

  // 2. static (주요 파일)
  console.log("Static...");
  const staticFiles = ["dev_SRM.c", "com_tml.c", "alarm.c", "com_hmi.c", "SRM_Parameter.c"];
  let staticAll = [];
  for (const f of staticFiles) {
    const fp = path.join(SRC, f);
    if (fs.existsSync(fp)) staticAll = staticAll.concat(parseStaticGlobals(fp));
  }
  sections.push(...chunkSection("static", "2. 파일 static 변수", "해당 .c 내부 전용. dev_SRM.c m_WorkData 등.", staticAll));

  // 3. 구조체 멤버
  console.log("Structs...");
  for (const g of STRUCT_ROOTS) {
    const gVar = g.var;
    const maxD = g.type.startsWith("ExtFlash") ? 2 : g.type === "StatusSTR" ? 4 : 3;
    const flat = flattenStruct(g.type, gVar, maps, 0, maxD);
    const rows = flat.map((r) =>
      makeRow({
        path: r.path,
        type: r.type,
        comment: r.comment,
        kind: r.kind || "struct",
        globalHint: gVar,
      })
    );
    sections.push(...chunkSection(`struct_${gVar}`, `3. 구조체 — ${g.title}`, g.note, rows));
  }

  // 4. enum
  console.log("Enums...");
  let enums = [];
  for (const hf of HEADER_FILES) enums = enums.concat(parseEnums(read(hf), path.basename(hf)));
  const enumDedup = new Map();
  for (const e of enums) enumDedup.set(e.path, e);
  enums = [...enumDedup.values()].sort((a, b) => a.path.localeCompare(b.path));
  sections.push(...chunkSection("enum", "4. Enum 멤버", "RunMode, ERROR, WORK, 속도타입 등.", enums, 400));

  // 5. #define — 분류
  console.log("Defines...");
  let defines = [];
  for (const hf of HEADER_FILES) defines = defines.concat(parseDefines(read(hf)));
  const defDedup = new Map();
  for (const d of defines) defDedup.set(d.path, d);
  defines = [...defDedup.values()].sort((a, b) => a.path.localeCompare(b.path));
  const ty = defines.filter((d) => d.path.startsWith("TY_"));
  const err = defines.filter((d) => d.path.includes("ERROR") || d.path.startsWith("ORDER_"));
  const rest = defines.filter((d) => !ty.includes(d) && !err.includes(d));
  sections.push(...chunkSection("define_tml", "5a. #define — TML TY_*", "Vexi 통신 타입.", ty));
  sections.push(...chunkSection("define_order", "5b. #define — ORDER/ERROR 관련", "작업코드, 스텝 등.", err));
  sections.push(...chunkSection("define_other", "5c. #define — 기타", "비트, 타이밍, 설정 상수.", rest, 400));

  // 6. 함수 — 파일별
  console.log("Functions...");
  const cFiles = fs.readdirSync(SRC).filter((f) => f.endsWith(".c")).sort();
  for (const f of cFiles) {
    const funcs = parseFunctions(path.join(SRC, f));
    if (!funcs.length) continue;
    const id = `fn_${f.replace(".c", "")}`;
    sections.push(
      ...chunkSection(id, `6. 함수 — ${f}`, `${f} 정의 함수.`, funcs, 80)
    );
  }

  const total = sections.reduce((a, s) => a + s.rows.length, 0);
  const estLines = total * 6 + sections.length * 30;
  const pages = Math.round(estLines / 45);

  console.log(`Writing HTML (${total} items, ~${pages} pages)...`);
  const html = buildHtml(sections, { total, pages }, treeBlock);
  const outPath = path.join(OUT, "SRM_전체심볼_용도사전.html");
  fs.writeFileSync(outPath, html, "utf8");

  const readme = `# SRM 심볼 용도 사전

## 권장 파일

| 파일 | 내용 |
|------|------|
| **SRM_전체심볼_용도사전.html** | 변수+함수+enum+define+구조체 **전체** + **섹션0 구조체 트리** |
| **SRM_구조체트리.html** | 구조체 포함관계만 (트리+다이어그램, 가볍게) |
| **SRM_구조체멤버_용도사전.html** | 구조체 멤버 표만 |

## PDF 저장
\`SRM_전체심볼_용도사전.html\` → Chrome/Edge → 인쇄 → PDF로 저장

## 재생성
\`\`\`bash
node docs/manual/generate_full_manual.js
\`\`\`

생성: ${new Date().toISOString()}
`;
  fs.writeFileSync(path.join(OUT, "README.md"), readme, "utf8");
  console.log(`Done: ${outPath}`);
  console.log(`Items: ${total}, sections: ${sections.length}, ~${pages} pages`);
}

main();
