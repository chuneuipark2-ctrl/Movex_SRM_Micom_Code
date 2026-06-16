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
  {
    var: "m_St",
    type: "StatusSTR",
    title: "m_St (StatusSTR) — 지상반 0x30 상태",
    note: "지상반 폴링 운전상태. Save_*가 여기 기록.",
    purpose:
      "지상반/WCS에 보여주는 '얼굴'. 자동·Start·에러코드·포크위치·Inv_St[4축]·ForkWork[]·DI/DO·인터록 CV OK 등. Save_* 후 0x30 폴링으로 읽힘.",
    who: "지상반 (0x30 상태요구)",
    relation: "Save_Fork* → m_St.ForkWork[]",
  },
  {
    var: "m_pgmEnv",
    type: "PGMEnvSTR",
    title: "m_pgmEnv (PGMEnvSTR) — MCU 내부 런타임",
    note: "RunMode, 타이머, 통신, 내부 플래그.",
    purpose:
      "MCU 안에서만 쓰는 두뇌 상태. SRM_RunMode(상태머신 case), 타이머, TML/UDP/EtherCAT 링크, 비상·정지 플래그, 수동조작. 지상반에 직접 안 나감.",
    who: "펌웨어 내부 (dev_SRM.c, com_tml.c)",
    relation: "m_pgmEnv.SRM_RunMode ↔ dev_SRM switch(case)",
  },
  {
    var: "m_BKSram",
    type: "BKSRamSTR",
    title: "m_BKSram — 정전복구 BKPSRAM",
    note: "BKPSRAM 미러.",
    purpose:
      "배터리 백업 SRAM 미러. 알람로그, 운행정보, WorkInfo(작업복구), 그래프·장치설정. 전원 꺼져도 유지.",
    who: "MCU + rtc.c / saveBKSramBlock()",
    relation: "m_St와 겹치는 값 → 재기동 후 여기서 복원",
  },
  {
    var: "m_WorkData",
    type: "SRM_WorkDataSTR",
    title: "m_WorkData — 현재 사이클 작업 큐",
    note: "dev_SRM.c static[30]. GET/PUT 사이클.",
    purpose:
      "이번 사이클 실제 작업 데이터. ForkAct(GET/PUT), TargetPos, Rack_fork_obstruction, Step(From/To), DrvData[주행/승강/포크]. static 배열[30].",
    who: "dev_SRM.c 상태머신 전용",
    relation: "0x41 수신 → Store_Work_Data* → m_WorkData → PREPARE/GET/PUT",
  },
  {
    var: "m_ExtSEnv0",
    type: "ExtFlashSEnv0",
    title: "m_ExtSEnv0 — 주행·랙·셀 파라미터",
    note: "셀/랙/주행 드라이브 설정.",
    purpose:
      "설계(파라미터) 데이터. 랙·셀 위치, 셀 오프셋, 주행 드라이브. Flash/0xA4 다운로드로 세팅.",
    who: "파라미터 툴 / TML 0xA3~A8",
    relation: "TargetPos와 비교해 주행 이동량 계산",
  },
  {
    var: "m_ExtSEnv1",
    type: "ExtFlashSEnv1",
    title: "m_ExtSEnv1 — 승강·스테이션·인터록",
    note: "승강, 스테이션, 인터록 설정.",
    purpose:
      "승강 드라이브, 스테이션 설정, 금지랙·스페셜랙, 스테이션 인터록 타입.",
    who: "파라미터 / StationEnv",
    relation: "m_WorkData.IsStation + Check_Station_CVOK",
  },
  {
    var: "m_ExtSEnv2",
    type: "ExtFlashSEnv2",
    title: "m_ExtSEnv2 — 포크·제어·타임아웃",
    note: "포크, 타임아웃, 제어 파라미터.",
    purpose:
      "CtrParam(제어옵션), 포크 드라이브, Setup/Auto 타임아웃, 화물검사·홈복귀 등 현장 옵션.",
    who: "파라미터 / CtrParam",
    relation: "HomeReturn_Fault_UseFlag, 공출고 검사 생략 등",
  },
  {
    var: "WorkCmd",
    type: "WorkCmdSTR",
    title: "WorkCmdSTR — TML 0x41 수신 원본",
    note: "com_tml rxCmdOrder 파싱 형식.",
    purpose:
      "지상반 작업명령 패킷 파싱 직후 형식. OrderCode, OperationFlag, Fork[](WorkNum/From/To). 실행 시 m_WorkData로 변환.",
    who: "com_tml.c rxCmdOrder (0x41)",
    relation: "WorkCmd → m_WorkData → m_St.ForkWork[] 보고",
  },
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
    const ln = lines[i];
    if (/^\s*typedef\s+/.test(ln)) {
      i++;
      continue;
    }
    const tagMatch = ln.match(/^\s*struct\s+(?:__attribute__\s*\(\([^)]*\)\)\s*)?tag(\w+)/);
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
      const line = lines[i];
      if (/^\s*#\s*(if|elif|else|endif)/.test(line)) {
        i++;
        continue;
      }
      if (!started) {
        if (line.trim() === "{" || line.trim().startsWith("{")) {
          depth = 1;
          started = true;
          i++;
          continue;
        }
        i++;
        continue;
      }
      for (const ch of line) {
        if (ch === "{") depth++;
        else if (ch === "}") depth--;
      }
      if (depth > 0) memberLines.push(line);
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

function buildMermaidChart(tree, depthLimit = 1, nodeLimit = 20) {
  const lines = ["flowchart TB"];
  const rootId = mermaidSafeId(tree.label);
  lines.push(
    `  ${rootId}["<b>${tree.label}</b><br/><i>${tree.type}</i>"]:::root`
  );
  let count = 1;
  const childIds = [];

  function walk(parentId, node, depth) {
    if (depth > depthLimit || count >= nodeLimit) return;
    for (const ch of node.children || []) {
      if (count >= nodeLimit) break;
      const id = mermaidSafeId(`${node.label}_${ch.label}`);
      childIds.push(id);
      const lbl = ch.label.replace(/"/g, "'");
      const typ = (ch.type || "").replace(/"/g, "'").slice(0, 36);
      lines.push(`  ${id}["${lbl}<br/><i>${typ}</i>"]:::node`);
      lines.push(`  ${parentId} --> ${id}`);
      count++;
      if (ch.children?.length && depth < depthLimit) walk(id, ch, depth + 1);
    }
  }

  walk(rootId, tree, 1);
  lines.push("  classDef root fill:#1a6b3c,stroke:#0d4a28,color:#fff,font-weight:bold");
  lines.push("  classDef node fill:#f5f5f5,stroke:#333333,color:#111111");
  if (count > 1) lines.push(`  class ${rootId} root`);
  if (childIds.length) lines.push(`  class ${childIds.join(",")} node`);
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

  const open = "";
  const kids = node.children.map((c) => renderTreeLi(c, depth + 1)).join("");
  return `<li class="tree-branch"><details${open}><summary><span class="t-name">${esc(node.label)}</span>${typeSpan}${cmSpan}<span class="t-badge">${node.children.length}</span></summary><ul>${kids}</ul></details></li>`;
}

function buildStructTreeSection(roots, maps) {
  mermaidSeq = 0;
  let html = `<h2 id="struct_tree">0. 구조체 포함 관계 (트리 · 다이어그램)</h2>
<div class="note">
  <b>8대 핵심 구조체</b> — SRM 데이터가 어디에 저장되고 누가 읽는지.<br>
  <b>접이식 트리</b>: 멤버 포함 관계 전체. <b>다이어그램</b>: 「다이어그램 보기」클릭 시 렌더 (버벅임 방지).<br>
  <button type="button" class="tree-btn" onclick="treeExpandAll(true)">트리 전체 펼치기</button>
  <button type="button" class="tree-btn" onclick="treeExpandAll(false)">트리 전체 접기</button>
</div>

<h3>데이터 흐름 (한 장)</h3>
<div class="flow-box">
<pre class="flow-text">지상반 0x41 ──► WorkCmdSTR (수신 형식)
                    │
                    ▼
              m_WorkData[]  ◄── 상태머신(dev_SRM) 읽기/쓰기
                    │
        ┌───────────┼───────────┐
        ▼           ▼           ▼
   m_pgmEnv     m_ExtSEnv0~2   m_St.ForkWork[]
   (RunMode)    (파라미터)     (0x30 지상반 보고)
        │
        ▼
   m_BKSram (정전 복구)</pre>
</div>

<h3>8개 구조체 용도 요약</h3>
<table class="summary-table"><thead><tr>
  <th>변수</th><th>타입</th><th>누가 씀</th><th>용도</th><th>연관</th>
</tr></thead><tbody>`;

  for (const g of roots) {
    html += `<tr>
      <td class="path">${esc(g.var)}</td>
      <td>${esc(g.type)}</td>
      <td>${esc(g.who || "-")}</td>
      <td>${esc(g.purpose || g.note)}</td>
      <td>${esc(g.relation || "-")}</td>
    </tr>`;
  }
  html += `</tbody></table>`;

  for (const g of roots) {
    const maxD = g.type.startsWith("ExtFlash") ? 3 : g.type === "StatusSTR" ? 4 : 4;
    const tree = buildStructTree(g.var, g.type, maps, maxD);
    const chartId = `mermaid_${g.var.replace(/[^a-zA-Z0-9]/g, "_")}`;
    const chart = buildMermaidChart(tree, 1, g.type === "StatusSTR" ? 18 : 22);
    const chartEsc = chart.replace(/&/g, "&amp;").replace(/</g, "&lt;");

    html += `<h3 id="tree_${esc(g.var)}">${esc(g.var)} <span class="kind">(${esc(g.type)})</span></h3>`;
    html += `<div class="purpose-box"><b>용도</b>: ${esc(g.purpose || g.note)}<br>`;
    html += `<b>사용처</b>: ${esc(g.who || "-")} &nbsp;|&nbsp; <b>연관</b>: ${esc(g.relation || "-")}</div>`;
    html += `<details class="mermaid-lazy"><summary class="mermaid-summary">▶ 다이어그램 보기 (1단계 개요, 클릭 시 렌더)</summary>`;
    html += `<div class="mermaid-wrap"><pre class="mermaid-pending" data-chart-id="${chartId}">${chartEsc}</pre></div></details>`;
    html += `<details class="tree-lazy" open><summary class="tree-summary">▼ 멤버 트리 (포함 관계)</summary>`;
    html += `<div class="struct-tree-box"><ul class="struct-tree">${renderTreeLi(tree)}</ul></div></details>`;
  }
  return html;
}

const GLOBAL_PURPOSE_OVERRIDES = {
  m_DevStatus: {
    who: "장치 초기화/상태",
    purpose: "DevStatusSTR — 장치 연결·초기화 상태. 기동 시 장치 식별.",
    relation: "main / 초기화 루틴",
  },
  m_ExtSEnv: {
    who: "Flash 파라미터 (통합)",
    purpose: "ExtFlashSEnv — 외부 Flash 환경 통합 구조 (레거시/공통). ExtSEnv0~2와 역할 분리.",
    relation: "m_ExtSEnv0~2",
  },
  m_TestStatus: {
    who: "시험·시뮬레이터",
    purpose: "TestStatusSTR — 시운전/테스트 모드 상태.",
    relation: "m_pgmEnv.Test_Simulator",
  },
  m_Invertor_Info: {
    who: "EtherCAT/인버터",
    purpose: "InvertorInfoSTR — 인버터 PDO/통신 상태 버퍼.",
    relation: "m_St.Inv_St[], EtherCAT",
  },
  m_DIO_SetInfo: {
    who: "DIO 설정",
    purpose: "DIO_SetInfoSTR — 디지털 입출력 형상/매핑 설정.",
    relation: "m_St.Digital_Input/Output",
  },
  m_GraphLog: {
    who: "그래프 로깅",
    purpose: "GraphLogSTR — 주행/승강/포크 그래프 데이터 기록.",
    relation: "m_BKSram.Graph_Type",
  },
  m_McuTestCtr: {
    who: "MCU 테스트",
    purpose: "McuTestCtrSTR — MCU 자가진단 제어.",
    relation: "Mcu_Test.c",
  },
  m_McuTestSt: {
    who: "MCU 테스트",
    purpose: "McuTestStSTR — MCU 자가진단 결과 상태.",
    relation: "Mcu_Test.c",
  },
  m_run_pgm_mode: {
    who: "부트로더",
    purpose: "0x01=Boot, 0x02=Download — 펌웨어 다운로드 모드 구분.",
    relation: "upgrade.c / download",
  },
};

const FILE_PURPOSES = {
  "dev_SRM.c": "상태머신 본체 — RunMode, 주행/승강/포크 제어",
  "com_tml.c": "TML Vexi — 지상반 UART 통신 (0x30/0x41/0x50)",
  "alarm.c": "Save_* — m_St/BKPSRAM 상태 기록, 에러 저장",
  "main.c": "전역변수 정의, HAL 초기화, main 루프",
  "com_hmi.c": "HMI Modbus 레지스터 통신",
  "com_udp.c": "UDP 이더넷 통신",
  "SRM_Parameter.c": "파라미터 읽기/쓰기 Flash",
  "rtc.c": "BKPSRAM 저장/복구",
  "ecat_main.c": "EtherCAT 마스터",
  "encoder.c": "엔코더 PDO",
  "fpga.c": "FPGA 통신",
  "upgrade.c": "펌웨어 다운로드",
  "Mcu_Test.c": "MCU 테스트",
};

function inferStructTypePurpose(typeName, memberCount = 0) {
  const n = typeName.toUpperCase();
  const rules = [
    [/ALARM/, "알람·이상 로그 기록/조회"],
    [/PARAM|ENV|CONFIG|SETTING/, "파라미터·환경설정 (Flash/TML)"],
    [/WORK|FORK|CMD|ORDER/, "작업명령·포크 작업 데이터"],
    [/STATUS|STATE/, "운전/장치 상태 보고"],
    [/INV|INVERT|MOVI|DRIVE|PDO/, "인버터/EtherCAT PDO"],
    [/CELL|RACK|STATION/, "셀·랙·스테이션 위치/설정"],
    [/HMI|MW\d/, "HMI Modbus 레지스터 비트맵"],
    [/MODBUS/, "Modbus TCP 프레임"],
    [/GRAPH/, "그래프/트렌드 로그"],
    [/COM|HEADER|TML/, "통신 프레임 헤더"],
    [/VELOC|PROFILE/, "속도·프로파일"],
    [/LOG/, "로그 버퍼"],
    [/TEST|SIMUL/, "시험·시뮬레이터"],
    [/DOWNLOAD|EXEC/, "펌웨어 다운로드"],
    [/BIT/, "비트필드 (union 래퍼)"],
  ];
  for (const [re, d] of rules) if (re.test(n)) return d;
  return `구조체 타입 (${memberCount}개 멤버). 아래 트리·섹션3 표 참조.`;
}

function parseAllExternGlobalsFixed(headerText, maps) {
  const items = [];
  for (const line of headerText.split("\n")) {
    const m = line.match(/^\s*extern\s+([\w\s*]+?)\s+(\w+)\s*;\s*(?:\/\/(.*))?/);
    if (!m) continue;
    const type = m[1].trim().replace(/\s+/g, " ");
    const name = m[2];
    const comment = (m[3] || "").trim();
    const ov = GLOBAL_PURPOSE_OVERRIDES[name] || {};
    const tn = type.replace(/\s+/g, "").replace(/\*$/, "");
    const isStruct = maps.byTypedef.has(tn);
    items.push({
      var: name,
      type,
      comment,
      isStruct,
      who: ov.who || (name.startsWith("m_") ? "전역 extern" : "상수 테이블"),
      purpose: ov.purpose || comment || (isStruct ? inferStructTypePurpose(tn, 0) : `스칼라/배열 (${type})`),
      relation: ov.relation || "-",
    });
  }
  return items;
}

function parseMainFileGlobals(mainPath, maps) {
  const items = [];
  const text = read(mainPath);
  const re =
    /^(?:__attribute__\s*\([^)]*\)\s*)?([\w]+)\s+(\w+)\s*;/gm;
  let m;
  while ((m = re.exec(text))) {
    const type = m[1];
    const name = m[2];
    if (["static", "void", "int"].includes(type)) continue;
    if (items.some((x) => x.var === name)) continue;
    const ov = GLOBAL_PURPOSE_OVERRIDES[name] || {};
    items.push({
      var: name,
      type,
      comment: "",
      isStruct: maps.byTypedef.has(type),
      who: ov.who || "main.c 정의",
      purpose: ov.purpose || inferStructTypePurpose(type, 0),
      relation: ov.relation || "DTCM .dtcm_bss",
    });
  }
  return items;
}

function parseStaticStructVars(maps) {
  const items = [];
  const seen = new Set();
  for (const f of fs.readdirSync(SRC).filter((x) => x.endsWith(".c"))) {
    const text = read(path.join(SRC, f));
    const re =
      /^\s*static\s+([\w]+)\s+(\w+)(\[[^\]]*\])?\s*(?:=\s*[^;]*)?;/gm;
    let m;
    while ((m = re.exec(text))) {
      const type = m[1];
      const name = m[2];
      const arr = m[3] || "";
      if (!maps.byTypedef.has(type)) continue;
      const key = `${f}:${name}`;
      if (seen.has(key)) continue;
      seen.add(key);
      items.push({
        file: f,
        var: name,
        type,
        arr,
        purpose: inferStructTypePurpose(type, maps.byTypedef.get(type)?.members?.length || 0),
      });
    }
  }
  return items.sort((a, b) => a.file.localeCompare(b.file) || a.var.localeCompare(b.var));
}

function buildFileIndexHtml() {
  const files = fs.readdirSync(SRC).filter((f) => f.endsWith(".c")).sort();
  let html = `<h3 id="file_index">소스 파일 색인 (Core/Src)</h3>
<table class="summary-table"><thead><tr><th>파일</th><th>역할</th><th>줄 수</th></tr></thead><tbody>`;
  for (const f of files) {
    const lines = read(path.join(SRC, f)).split("\n").length;
    const role = FILE_PURPOSES[f] || "Core 애플리케이션";
    html += `<tr><td class="path">${esc(f)}</td><td>${esc(role)}</td><td>${lines}</td></tr>`;
  }
  html += `</tbody></table>`;
  return html;
}

function renderStructTypeBlock(typeName, maps, prefix, maxDepth, showMermaid) {
  if (!maps.byTypedef.has(typeName)) {
    return `<p class="kind">타입 ${esc(typeName)} 정의 없음 (포인터/기본형)</p>`;
  }
  const tree = buildStructTree(prefix, typeName, maps, 0, maxDepth);
  const mc = maps.byTypedef.get(typeName)?.members?.length || 0;
  let html = "";
  if (showMermaid) {
    const chart = buildMermaidChart(tree, 1, 16);
    const chartEsc = chart.replace(/&/g, "&amp;").replace(/</g, "&lt;");
    html += `<details class="mermaid-lazy"><summary class="mermaid-summary">▶ 다이어그램 보기</summary>`;
    html += `<div class="mermaid-wrap"><pre class="mermaid-pending">${chartEsc}</pre></div></details>`;
  }
  html += `<details class="tree-lazy"><summary class="tree-summary">▶ 멤버 트리 (${mc}개 최상위 멤버)</summary>`;
  html += `<div class="struct-tree-box"><ul class="struct-tree">${renderTreeLi(tree)}</ul></div></details>`;
  return html;
}

function buildCompleteStructSection(maps, headerText) {
  mermaidSeq = 0;
  const externGlobals = parseAllExternGlobalsFixed(headerText, maps);
  const mainGlobals = parseMainFileGlobals(path.join(SRC, "main.c"), maps);
  const staticStructs = parseStaticStructVars(maps);

  const globalMap = new Map();
  for (const g of [...externGlobals, ...mainGlobals]) {
    if (!globalMap.has(g.var)) globalMap.set(g.var, g);
  }
  const allGlobals = [...globalMap.values()];

  const allTypes = [...maps.byTypedef.keys()].sort((a, b) => a.localeCompare(b));
  const typesFromGlobals = new Set(allGlobals.filter((g) => g.isStruct).map((g) => g.type.replace(/\s+/g, "")));

  let html = `<h2 id="struct_tree">0. 코드 전체 맵 — 구조체·전역·파일</h2>
<div class="note">
  <b>완전판</b>: User_Define.h + dev_SRM.h + dev_SRM.c 에 정의된 <b>모든 구조체 타입(${allTypes.length}개)</b>,
  전역 변수, static 구조체 변수 포함.<br>
  <b>성능</b>: 대용량 트리/표는 접혀 있음 — 펼칠 때만 표시. 다이어그램은 클릭 시 렌더.<br>
  <button type="button" class="tree-btn" onclick="treeExpandAll(true)">트리 전체 펼치기</button>
  <button type="button" class="tree-btn" onclick="treeExpandAll(false)">트리 전체 접기</button>
</div>`;

  html += buildFileIndexHtml();

  html += `<h3>데이터 흐름 (핵심)</h3>
<div class="flow-box"><pre class="flow-text">지상반 0x41 ──► WorkCmdSTR
                    ▼
              m_WorkData[] (dev_SRM static)
                    │
     ┌──────────────┼──────────────┐
     ▼              ▼              ▼
 m_pgmEnv      m_ExtSEnv0~2    m_St ──► 0x30 지상반
 (RunMode)      (파라미터)      ForkWork[], Inv_St[]
     ▼
 m_BKSram (정전복구)</pre></div>`;

  html += `<h3 id="all_globals">전역 변수 전체 (${allGlobals.length}개)</h3>
<table class="summary-table"><thead><tr>
  <th>변수명</th><th>타입</th><th>구조체?</th><th>용도</th><th>비고</th>
</tr></thead><tbody>`;
  for (const g of allGlobals) {
    html += `<tr>
      <td class="path">${esc(g.var)}</td>
      <td>${esc(g.type)}</td>
      <td>${g.isStruct ? "예" : "-"}</td>
      <td>${esc(g.purpose)}</td>
      <td>${esc(g.who)} ${g.relation !== "-" ? "· " + esc(g.relation) : ""}</td>
    </tr>`;
  }
  html += `</tbody></table>`;

  html += `<h3>핵심 8대 구조체 (상세)</h3>
<table class="summary-table"><thead><tr>
  <th>변수/타입</th><th>타입</th><th>누가 씀</th><th>용도</th><th>연관</th>
</tr></thead><tbody>`;
  for (const g of STRUCT_ROOTS) {
    html += `<tr>
      <td class="path">${esc(g.var)}</td><td>${esc(g.type)}</td>
      <td>${esc(g.who || "-")}</td><td>${esc(g.purpose || g.note)}</td><td>${esc(g.relation || "-")}</td>
    </tr>`;
  }
  html += `</tbody></table>`;

  for (const g of STRUCT_ROOTS) {
    const maxD = g.type.startsWith("ExtFlash") ? 3 : g.type === "StatusSTR" ? 4 : 4;
    html += `<h4 id="tree_${esc(g.var)}">${esc(g.var)} <span class="kind">(${esc(g.type)})</span></h4>`;
    html += `<div class="purpose-box"><b>용도</b>: ${esc(g.purpose || g.note)}<br>`;
    html += `<b>사용처</b>: ${esc(g.who || "-")} | <b>연관</b>: ${esc(g.relation || "-")}</div>`;
    html += renderStructTypeBlock(g.type, maps, g.var, maxD, true);
  }

  const otherStructGlobals = allGlobals.filter(
    (g) => g.isStruct && !STRUCT_ROOTS.some((r) => r.var === g.var)
  );
  if (otherStructGlobals.length) {
    html += `<h3 id="other_globals">기타 전역 구조체 변수 (${otherStructGlobals.length}개)</h3>`;
    for (const g of otherStructGlobals) {
      const tn = g.type.replace(/\s+/g, "");
      html += `<details class="struct-index-item"><summary class="path">${esc(g.var)}</summary>`;
      html += `<div class="purpose-box">${esc(g.purpose)}</div>`;
      html += renderStructTypeBlock(tn, maps, g.var, 3, false);
      html += `</details>`;
    }
  }

  if (staticStructs.length) {
    html += `<h3 id="static_structs">static 구조체 변수 (${staticStructs.length}개)</h3>
<div class="note">.c 파일 내부 전용. extern 아님. dev_SRM.c의 m_WorkData 등.</div>`;
    for (const s of staticStructs) {
      html += `<details class="struct-index-item"><summary><span class="path">${esc(s.file)} :: ${esc(s.var)}${esc(s.arr)}</span> <span class="kind">${esc(s.type)}</span></summary>`;
      html += `<div class="purpose-box">${esc(s.purpose)}</div>`;
      html += renderStructTypeBlock(s.type, maps, `${s.file}:${s.var}`, 3, false);
      html += `</details>`;
    }
  }

  html += `<h3 id="all_struct_types">전체 구조체 타입 색인 (${allTypes.length}개)</h3>
<div class="note">User_Define.h · dev_SRM.h · dev_SRM.c 등 모든 <code>typedef struct</code>.
타입명 클릭 → 멤버 포함 트리. 전역 변수에 없는 내부/통신용 구조체도 포함.</div>`;

  for (const typeName of allTypes) {
    const info = maps.byTypedef.get(typeName);
    const mc = info?.members?.length || 0;
    const purpose = inferStructTypePurpose(typeName, mc);
    const usedBy = allGlobals.filter((g) => g.type.replace(/\s+/g, "") === typeName).map((g) => g.var);
    const usedLabel = usedBy.length ? ` — 전역: ${usedBy.join(", ")}` : "";
    const maxD = typeName === "StatusSTR" || typeName === "PGMEnvSTR" ? 4 : typeName.startsWith("ExtFlash") ? 3 : 2;
    html += `<details class="struct-index-item" id="type_${esc(typeName)}">`;
    html += `<summary><b>${esc(typeName)}</b> <span class="kind">(${mc} members)${esc(usedLabel)}</span> — ${esc(purpose)}</summary>`;
    html += renderStructTypeBlock(typeName, maps, typeName, maxD, false);
    html += `</details>`;
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

function makeStructMemberRow({ path, type, comment }) {
  const member = path.split(".").pop().replace(/\[.*\]/, "");
  return {
    path,
    type: type || "struct",
    comment: comment || "",
    purpose: comment || inferPurpose(member, "struct", comment, path),
    files: "-",
    kind: "struct",
  };
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
const MERMAID_SCRIPT = `
<script src="https://cdn.jsdelivr.net/npm/mermaid@10/dist/mermaid.min.js"></script>
<script>
  mermaid.initialize({
    startOnLoad: false,
    theme: "base",
    themeVariables: {
      primaryColor: "#f5f5f5",
      primaryTextColor: "#111111",
      primaryBorderColor: "#333333",
      lineColor: "#1a6b3c",
      secondaryColor: "#e8f5ee",
      tertiaryColor: "#ffffff",
      mainBkg: "#f5f5f5",
      textColor: "#111111",
      labelTextColor: "#111111",
      nodeTextColor: "#111111"
    },
    flowchart: { useMaxWidth: true, htmlLabels: true }
  });

  function treeExpandAll(open) {
    document.querySelectorAll(".struct-tree details").forEach(function(d) { d.open = open; });
  }

  async function renderMermaidIn(el) {
    if (!el || el.dataset.rendered === "1") return;
    var code = el.textContent.trim();
    if (!code) return;
    el.dataset.rendered = "1";
    try {
      var id = "mmd_" + Math.random().toString(36).slice(2, 9);
      var out = await mermaid.render(id, code);
      el.innerHTML = out.svg;
      el.classList.remove("mermaid-pending");
      el.classList.add("mermaid-done");
    } catch (e) {
      el.textContent = "다이어그램 렌더 실패: " + e.message;
    }
  }

  document.querySelectorAll("details.mermaid-lazy").forEach(function(det) {
    det.addEventListener("toggle", function() {
      if (!det.open) return;
      var pre = det.querySelector(".mermaid-pending");
      renderMermaidIn(pre);
    });
  });
</script>`;

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
      padding: 16px; margin: 10px 0 16px; overflow-x: auto; min-height: 80px; }
  /* Mermaid SVG 글자 검정 강제 */
    .mermaid-wrap svg .nodeLabel, .mermaid-wrap svg .nodeLabel p,
    .mermaid-wrap svg .nodeLabel span, .mermaid-wrap svg .label,
    .mermaid-wrap svg text, .mermaid-wrap svg tspan { fill: #111 !important; color: #111 !important; }
    .mermaid-wrap svg .root .nodeLabel, .mermaid-wrap svg .root .nodeLabel p { fill: #fff !important; color: #fff !important; }
    .mermaid-summary, .tree-summary { cursor: pointer; font-weight: 600; color: #1a6b3c; padding: 6px 0; }
    .mermaid-lazy, .tree-lazy { margin-bottom: 16px; }
    .purpose-box { background: #f8faf8; border: 1px solid #c8e0d0; padding: 10px 14px;
      margin: 8px 0 12px; font-size: 10pt; line-height: 1.6; }
    .flow-box { background: #f5f5f5; border-radius: 8px; padding: 12px 16px; margin: 12px 0 20px; overflow-x: auto; }
    .flow-text { font-family: Consolas, monospace; font-size: 9.5pt; margin: 0; color: #111; line-height: 1.55; }
    .summary-table { font-size: 9.5pt; margin-bottom: 24px; }
    .summary-table th { background: #1a6b3c; position: static; }
    .sec-collapse { margin-bottom: 20px; border: 1px solid #ddd; border-radius: 8px; padding: 0 12px 12px; }
    .sec-collapse > summary { cursor: pointer; font-weight: 700; font-size: 11pt; padding: 12px 4px;
      color: #2c3e50; list-style: none; }
    .sec-collapse > summary::-webkit-details-marker { display: none; }
    .sec-collapse > summary::before { content: "▶ "; color: #1a6b3c; }
    .sec-collapse[open] > summary::before { content: "▼ "; }
    .perf-note { font-size: 9pt; color: #666; margin-top: 8px; }
    .struct-index-item { margin: 6px 0; border: 1px solid #ddd; border-radius: 6px; padding: 0 10px 8px; background: #fafafa; }
    .struct-index-item > summary { cursor: pointer; padding: 10px 4px; list-style: none; font-size: 10pt; }
    .struct-index-item > summary::-webkit-details-marker { display: none; }
    .struct-index-item > summary::before { content: "▶ "; color: #1a6b3c; font-size: 9pt; }
    .struct-index-item[open] > summary::before { content: "▼ "; }
    h4 { font-size: 10.5pt; color: #333; margin: 16px 0 6px; border-left: 4px solid #1a6b3c; padding-left: 8px; }
    @media print {
      h2 { page-break-before: always; }
      th { position: static; }
      .tree-branch > details { open: true; }
      .tree-branch > details > summary::before { content: "▼ "; }
      .mermaid-wrap { page-break-inside: avoid; }
    }
  `;

  let body = `<h1>MX SRM — 전체 변수·함수·심볼 용도 사전</h1>
<div class="meta">
  <b>생성일</b>: ${new Date().toISOString().slice(0, 10)} &nbsp;|&nbsp;
  <b>Ver</b> 4.4 &nbsp;|&nbsp;
  <b>총 항목</b>: ${stats.total.toLocaleString()} &nbsp;|&nbsp;
  <b>구조체 타입</b>: ${stats.typeCount || "?"}개 &nbsp;|&nbsp;
  추정 ${stats.pages}장 (A4)
</div>
<div class="note">
  <b>용도</b>: 구조체 멤버, 전역/static 변수, enum, #define, 함수 이름이 <b>실제로 무엇에 쓰이는지</b> 정리.<br>
  <b>성능</b>: 아래 표 섹션은 <b>접혀 있음</b> — 펼칠 때만 로드 (4천+행). 섹션0 트리·요약표는 바로 보임.<br>
  <b>구조체 트리</b>: <a href="#struct_tree">섹션 0</a> (포함 관계 다이어그램)
</div>
${treeBlock}
<h2 id="toc">목차</h2><div class="toc"><ul>
<li><a href="#struct_tree"><b>0. 코드 전체 맵 (구조체 ${stats.typeCount || "?"}개)</b></a></li>
<li><a href="#all_globals">전역 변수</a></li>
<li><a href="#all_struct_types">전체 구조체 타입</a></li>
<li><a href="#file_index">소스 파일 색인</a></li>`;

  for (const sec of sections) {
    body += `<li><a href="#${sec.id}">${esc(sec.title)}</a> <span class="kind">(${sec.rows.length})</span></li>`;
  }
  body += `</ul></div>`;

  for (const sec of sections) {
    const rowCount = sec.rows.length;
    body += `<details class="sec-collapse" id="${sec.id}">`;
    body += `<summary>${esc(sec.title)} <span class="kind">(${rowCount}항목 — 클릭하여 펼치기)</span></summary>`;
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
    body += `<p class="perf-note">Ctrl+F로 이 섹션 내 검색 가능.</p></details>`;
  }

  return `<!DOCTYPE html><html lang="ko"><head><meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>SRM 전체 심볼 용도 사전</title><style>${css}</style></head><body>${body}${MERMAID_SCRIPT}</body></html>`;
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

  console.log("Complete struct map...");
  const allHeaderText = HEADER_FILES.map(read).join("\n");
  const treeBlock = buildCompleteStructSection(maps, allHeaderText);

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
<title>SRM 구조체 포함관계 트리</title><style>
body{font-family:"Malgun Gothic",sans-serif;margin:1.5cm 2cm;color:#111}
h1{border-bottom:3px solid #1a5}
.summary-table{width:100%;border-collapse:collapse;font-size:9.5pt;margin-bottom:20px}
.summary-table th{background:#1a6b3c;color:#fff;padding:8px}
.summary-table td{border:1px solid #ddd;padding:6px 8px}
.path{font-family:Consolas,monospace;color:#055}
${treeCss}
.mermaid-wrap svg .nodeLabel,.mermaid-wrap svg text,.mermaid-wrap svg tspan{fill:#111!important;color:#111!important}
</style></head><body>
<h1>MX SRM — 구조체 포함 관계</h1>
<p><a href="SRM_전체심볼_용도사전.html">← 전체 사전으로</a></p>
${treeBlock}
${MERMAID_SCRIPT}
</body></html>`;
  fs.writeFileSync(path.join(OUT, "SRM_구조체트리.html"), treeOnlyHtml, "utf8");

  // 1. 전역 extern
  console.log("Globals...");
  const globals = parseExternGlobals(read(path.join(INC, "User_Define.h")), "User_Define.h");
  sections.push(...chunkSection("globals", "1. 전역 변수 (extern)", "main.c / User_Define.h 선언. DTCM 배치 변수 포함.", globals));

  // 2. static — Core/Src 전체
  console.log("Static...");
  let staticAll = [];
  for (const f of fs.readdirSync(SRC).filter((x) => x.endsWith(".c")).sort()) {
    staticAll = staticAll.concat(parseStaticGlobals(path.join(SRC, f)));
  }
  sections.push(...chunkSection("static", "2. 파일 static 변수 (전체)", "Core/Src 모든 .c 내부 static. dev_SRM.c m_WorkData 등.", staticAll, 350));

  // 3. 구조체 멤버 — 핵심 8개 (grep 사용 파일 참조)
  console.log("Structs (core)...");
  const coreTypes = new Set(STRUCT_ROOTS.map((g) => g.type));
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
    sections.push(...chunkSection(`struct_${gVar}`, `3a. 구조체 — ${g.title}`, g.note, rows));
  }

  // 3b. 나머지 모든 구조체 타입 멤버
  console.log("Structs (all types)...");
  const allTypes = [...maps.byTypedef.keys()].sort((a, b) => a.localeCompare(b));
  for (const typeName of allTypes) {
    if (coreTypes.has(typeName)) continue;
    const info = maps.byTypedef.get(typeName);
    const mc = info?.members?.length || 0;
    if (!mc) continue;
    const maxD =
      typeName === "StatusSTR" || typeName === "PGMEnvSTR"
        ? 4
        : typeName.startsWith("ExtFlash")
          ? 3
          : 2;
    const prefix = typeName;
    const flat = flattenStruct(typeName, prefix, maps, 0, maxD);
    const purpose = inferStructTypePurpose(typeName, mc);
    const rows = flat.map((r) =>
      makeStructMemberRow({ path: r.path, type: r.type, comment: r.comment })
    );
    sections.push(
      ...chunkSection(
        `struct_type_${typeName}`,
        `3b. 구조체 타입 — ${typeName}`,
        purpose,
        rows,
        300
      )
    );
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
  const html = buildHtml(sections, { total, pages, typeCount: maps.byTypedef.size }, treeBlock);
  const outPath = path.join(OUT, "SRM_전체심볼_용도사전.html");
  fs.writeFileSync(outPath, html, "utf8");

  const typeCount = maps.byTypedef.size;
  const readme = `# SRM 심볼 용도 사전 (완전판)

## 권장 파일

| 파일 | 내용 |
|------|------|
| **SRM_전체심볼_용도사전.html** | **완전판** — 구조체 타입 ${typeCount}개 전체 트리 + 전역/static + 함수/enum/define ${total}항목 |
| **SRM_구조체트리.html** | 구조체 맵만 (가볍게) |

## 섹션 0 포함 내용
- Core/Src 파일 색인
- 전역 변수 전체
- 핵심 8대 구조체 상세
- 기타 전역 구조체 변수
- static 구조체 변수 (m_WorkData 등)
- **전체 구조체 타입 ${typeCount}개** — typedef struct 멤버 트리

## PDF 저장
\`SRM_전체심볼_용도사전.html\` → Chrome → 인쇄 → PDF

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
