/**
 * SRM 구조체 멤버 용도 사전 생성기
 * - m_St, m_pgmEnv, m_WorkData, m_BKSram 중심
 * - 멤버별 실제 코드 사용처 grep
 * - 출력: .docx + .html (브라우저 인쇄→PDF)
 */
const fs = require("fs");
const path = require("path");

const ROOT = path.resolve(__dirname, "..", "..");
const CORE = path.join(ROOT, "Core");
const OUT_DIR = __dirname;

const HEADER_PATH = path.join(CORE, "Inc", "User_Define.h");
const DEV_SRM_PATH = path.join(CORE, "Src", "dev_SRM.c");
const SRC_DIR = path.join(CORE, "Src");

const ROOT_GLOBALS = [
  {
    var: "m_St",
    type: "StatusSTR",
    title: "지상반 상태보고 (0x30 응답 본체)",
    note: "지상반/WCS가 폴링하는 운전 상태. Save_* 함수가 여기와 m_BKSram에 동시 기록하는 경우 많음.",
  },
  {
    var: "m_pgmEnv",
    type: "PGMEnvSTR",
    title: "MCU 내부 런타임 환경",
    note: "지상반에 직접 안 나가는 내부 변수. RunMode(SRM_RunMode), 타이머, 통신링크, 플래그.",
  },
  {
    var: "m_WorkData",
    type: "SRM_WorkDataSTR",
    title: "현재 사이클 작업 데이터 (내부 큐)",
    note: "0x41 작업수신 후 dev_SRM.c에서 채움. static 배열[30]. 지상반 m_St와 별개.",
    sourceFile: DEV_SRM_PATH,
  },
  {
    var: "m_BKSram",
    type: "BKSRamSTR",
    title: "정전 복구용 BKPSRAM 미러",
    note: "전원 꺼져도 유지. 작업번호/알람로그/운행정보 복원.",
  },
  {
    var: "m_WorkData (WorkCmd 수신)",
    type: "WorkCmdSTR",
    title: "TML 0x41 수신 작업명령 원본 형식",
    note: "com_tml.c rxCmdOrder에서 파싱. OperationFlag, Fork[] 포함.",
    indirect: true,
  },
];

function readText(fp) {
  return fs.readFileSync(fp, "utf8");
}

function parseStructs(text) {
  /** @type {Map<string, {tag:string, typedef:string, members:Array}>} */
  const byTypedef = new Map();
  const byTag = new Map();
  const lines = text.split("\n");

  let i = 0;
  while (i < lines.length) {
    const line = lines[i];
    const tagMatch = line.match(/struct\s+(?:__attribute__\s*\(\([^)]*\)\)\s*)?tag(\w+)/);
    if (!tagMatch) {
      i++;
      continue;
    }

    const tag = tagMatch[1];
    let depth = 0;
    let started = false;

    if (line.includes("{")) {
      depth = 1;
      started = true;
    }

    const memberLines = [];
    i++;

    while (i < lines.length) {
      const ln = lines[i];
      if (!started) {
        if (ln.trim() === "{") {
          depth = 1;
          started = true;
          i++;
          continue;
        }
        if (ln.trim().startsWith("{")) {
          depth = 1;
          started = true;
          memberLines.push(ln.slice(ln.indexOf("{") + 1));
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
        const bitType = t.match(/^(\w+)\s+(\w+)\s*;/);
        if (bitType) {
          members.push({
            name: bitType[2],
            type: bitType[1],
            comment: "",
            isUnionBit: true,
          });
        }
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
        members.push({
          name: arr[2],
          type: `${arr[1].trim()}[${arr[3]}]`,
          comment: cm,
          isArray: true,
        });
        continue;
      }

      const norm = decl.match(/^([\w\s*]+?)\s+(\w+)\s*$/);
      if (norm) {
        const name = norm[2];
        if (!["u8", "u16", "u32"].includes(name)) {
          members.push({ name, type: norm[1].trim(), comment: cm });
        }
      }
    }

    const info = { tag, typedef, members };
    byTypedef.set(typedef, info);
    byTag.set(tag, info);
  }

  return { byTypedef, byTag };
}

function resolveType(typeName, maps) {
  const t = typeName.replace(/\*$/, "").replace(/\[\d+\]$/, "").trim();
  return maps.byTypedef.get(t) || maps.byTag.get(t.replace(/^tag/, "")) || null;
}

function flattenStruct(typeName, pathPrefix, maps, depth = 0, maxDepth = 3) {
  const struct = maps.byTypedef.get(typeName) || maps.byTag.get(typeName);
  if (!struct) return [];

  const rows = [];
  for (const m of struct.members) {
    const fullPath = `${pathPrefix}.${m.name}`;
    const baseType = m.type.replace(/\[.*\]$/, "").trim();

    rows.push({
      path: fullPath,
      member: m.name,
      type: m.type,
      comment: m.comment,
      struct: typeName,
    });

    if (m.isBitfield || m.isUnionBit) continue;

    const nested = resolveType(baseType, maps);
    if (!nested) continue;

    // union { Bit; D; } 래퍼 — Bit 하위 비트만 펼침
    if (m.name === "Bit" || baseType.endsWith("Bit_t") || baseType.endsWith("_Bit")) {
      const bitStruct =
        baseType.endsWith("Bit_t") || baseType.endsWith("_Bit")
          ? nested
          : resolveType(nested.members[0]?.type || baseType, maps);
      if (bitStruct) {
        for (const bm of bitStruct.members) {
          rows.push({
            path: `${fullPath}.${bm.name}`,
            member: bm.name,
            type: bm.type,
            comment: bm.comment,
            struct: bitStruct.typedef,
            isStatusBit: true,
          });
        }
      }
      continue;
    }

    if (
      ["DeviceStatus1", "DeviceStatus2", "DeviceMode_t", "PositionFlag1", "PositionFlag2"].includes(
        baseType
      )
    ) {
      const bitMember = nested.members.find((x) => x.name === "Bit");
      if (bitMember) {
        const bitStruct = resolveType(bitMember.type, maps);
        if (bitStruct) {
          for (const bm of bitStruct.members) {
            rows.push({
              path: `${fullPath}.Bit.${bm.name}`,
              member: bm.name,
              type: bm.type,
              comment: bm.comment,
              struct: bitStruct.typedef,
              isStatusBit: true,
            });
          }
        }
      }
      continue;
    }

    if (depth < maxDepth) {
      const childPrefix =
        m.isArray && baseType !== "INT08U" && baseType !== "INT16U"
          ? `${fullPath}[i]`
          : fullPath;
      rows.push(
        ...flattenStruct(nested.typedef, childPrefix, maps, depth + 1, maxDepth)
      );
    }
  }
  return rows;
}

function loadSourceLines() {
  const files = fs.readdirSync(SRC_DIR).filter((f) => f.endsWith(".c"));
  const cache = new Map();
  for (const f of files) {
    const fp = path.join(SRC_DIR, f);
    cache.set(f, readText(fp).split("\n"));
  }
  cache.set("com_tml.c", cache.get("com_tml.c") || []);
  cache.set("alarm.c", cache.get("alarm.c") || []);
  cache.set("dev_SRM.c", readText(DEV_SRM_PATH).split("\n"));
  return cache;
}

function analyzeUsage(globalVar, memberPath, memberName, srcCache) {
  const patterns = [];
  const tail = memberPath.replace(/^[^.]+\./, "");
  if (globalVar === "m_WorkData") {
    patterns.push(`m_WorkData`, `${memberName}`);
  } else {
    patterns.push(`${globalVar}.${tail}`, `${globalVar}.${memberName}`);
    if (memberName.length > 4) patterns.push(`.${memberName}`);
  }

  const writes = [];
  const reads = [];
  const key = memberName.replace(/[.*+?^${}()|[\]\\]/g, "\\$&");

  for (const [file, lines] of srcCache) {
    for (let i = 0; i < lines.length; i++) {
      const line = lines[i].trim();
      if (!line || line.startsWith("//") || line.startsWith("*")) continue;
      if (!line.includes(memberName) && !line.includes(tail)) continue;
      if (globalVar !== "m_WorkData" && !line.includes(globalVar.split(" ")[0]))
        continue;

      const isWrite = /=/.test(line) && !line.match(/==|!=|<=|>=/);
      const entry = `${file}:${i + 1}`;
      if (isWrite && writes.length < 3) writes.push(entry);
      else if (!isWrite && reads.length < 3) reads.push(entry);
    }
  }

  return { writes, reads };
}

function inferUsagePurpose(globalVar, row, usage) {
  const n = row.member;
  const p = row.path;
  const c = row.comment || "";

  const rules = [
    [/SRM_RunMode/i, "상태머신 RunMode. dev_SRM.c switch(case)의 현재 단계."],
    [/SRM_TaskMode/i, "TML 0x40 Task 배치 실행 모드. 0x41과 다름."],
    [/StartOn/i, "지상반 Start ON(0x50). 1=운전 시작 요청 상태."],
    [/EmergencyStop/i, "비상정지 상태 비트. 지상반 표시 + 동작 차단."],
    [/GoodsFlag_Or_MoveHome/i, "포크=화물적재, 주행/승강=홈복귀(레거시). 축 맥락 필수."],
    [/InPosition/i, "정위치 도달. PREPARE_MOVE에서 이동 스킵 판단에 사용."],
    [/Rack_fork_obstruction/i, "WCS 지정 '주행/승강 스킵 금지' 플래그. 센서 충돌 아님."],
    [/OperationFlag/i, "0x41 작업 옵션 비트필드. 현장별 해석 다름."],
    [/OrderStatus/i, "작업 상태(대기/진행/완료). Save_Fork*가 m_St에 기록."],
    [/OrderProcess/i, "작업 진행 단계(세부 스텝). 지상반 폴링용."],
    [/ForkAct/i, "작업 종류: MOVE_ONLY/GET/PUT/STICKY 분기 기준."],
    [/MainErrCode/i, "메인 에러코드(ERROR1_*). 지상반 알람 번호."],
    [/InterLock_CVOK/i, "스테이션 CV OK 인터록. 포크 구동 허가."],
    [/ForkWork/i, "포크별 작업 From/To/상태. 0x30 응답 포함."],
    [/Inv_St/i, "인버터 4축 상태(주행/승강/포크1/2)."],
    [/Current_Pos/i, "현재 위치(엔코더/카운트)."],
    [/Target_Pos/i, "이동 목표 위치."],
    [/WorkNum/i, "작업 번호(WCS 부여)."],
    [/Not_Check_Goods/i, "1이면 공출고/공입고 검사 생략."],
    [/PLC_Interlock/i, "1이면 PLC 인터락 확인 생략."],
    [/NormalStopFlag/i, "정지(0x54) 요청 플래그."],
    [/EmergencyStopFlag/i, "비상정지 요청 플래그."],
    [/Move_Home_Flag/i, "홈위치 이동(0x51) 명령 플래그."],
    [/TmlConnect/i, "지상반 TML 통신 연결 상태."],
  ];

  for (const [re, desc] of rules) {
    if (re.test(n) || re.test(p)) return desc;
  }

  if (c) return c;
  if (usage.writes.length)
    return `주로 쓰기: ${usage.writes[0].split(":")[0]} — 값을 세팅하는 내부 상태/보고용.`;
  if (usage.reads.length)
    return `주로 읽기: ${usage.reads[0].split(":")[0]} — 조건 분기/판단에 사용.`;
  return "코드 참조 적음. 예약/미사용 가능성.";
}

function escHtml(s) {
  return String(s)
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;");
}

function buildHtml(sections) {
  const css = `
    body { font-family: "Malgun Gothic", sans-serif; font-size: 11pt; line-height: 1.5; margin: 2cm; color: #111; }
    h1 { font-size: 20pt; border-bottom: 2px solid #333; padding-bottom: 8px; }
    h2 { font-size: 15pt; margin-top: 28px; color: #1a4; page-break-before: always; }
    h2:first-of-type { page-break-before: avoid; }
    h3 { font-size: 12pt; margin-top: 18px; color: #333; }
    .note { background: #f5f5f5; padding: 10px; border-left: 4px solid #1a4; margin: 12px 0; }
    table { width: 100%; border-collapse: collapse; margin: 10px 0 20px; font-size: 10pt; }
    th { background: #2c3e50; color: #fff; padding: 8px; text-align: left; }
    td { border: 1px solid #ccc; padding: 6px 8px; vertical-align: top; }
    tr:nth-child(even) { background: #fafafa; }
    .path { font-family: Consolas, monospace; font-size: 9pt; color: #066; }
    .toc a { text-decoration: none; color: #066; }
    @media print { h2 { page-break-before: always; } }
  `;

  let body = `<h1>MX SRM — 구조체 멤버 용도 사전</h1>
<p>생성일: ${new Date().toISOString().slice(0, 10)} | Ver 4.4 | <b>구조체 변수 → 멤버 → 실제 용도</b></p>
<div class="note">이 문서는 함수 사전이 아닙니다. <b>m_St / m_pgmEnv / m_WorkData / m_BKSram</b> 멤버가 코드에서 무엇에 쓰이는지 정리했습니다.<br>
PDF 저장: 브라우저에서 이 HTML 열기 → 인쇄 → "PDF로 저장"</div>
<h2 id="toc">목차</h2><ul class="toc">`;

  for (const sec of sections) {
    const id = sec.id;
    body += `<li><a href="#${id}">${escHtml(sec.title)}</a> (${sec.rows.length}항목)</li>`;
  }
  body += "</ul>";

  for (const sec of sections) {
    body += `<h2 id="${sec.id}">${escHtml(sec.title)}</h2>`;
    body += `<div class="note">${escHtml(sec.note)}</div>`;
    body += `<table><thead><tr>
      <th style="width:28%">멤버 경로</th>
      <th style="width:10%">타입</th>
      <th style="width:22%">헤더 주석</th>
      <th style="width:25%">실제 용도</th>
      <th style="width:15%">사용 파일</th>
    </tr></thead><tbody>`;

    for (const r of sec.rows) {
      const files = [...new Set([...r.usage.writes, ...r.usage.reads].map((x) => x.split(":")[0]))]
        .slice(0, 3)
        .join(", ");
      body += `<tr>
        <td class="path">${escHtml(r.path)}</td>
        <td>${escHtml(r.type)}</td>
        <td>${escHtml(r.comment || "-")}</td>
        <td>${escHtml(r.purpose)}</td>
        <td>${escHtml(files || "-")}</td>
      </tr>`;
    }
    body += "</tbody></table>";
  }

  return `<!DOCTYPE html><html lang="ko"><head><meta charset="utf-8">
<title>SRM 구조체 멤버 용도 사전</title><style>${css}</style></head><body>${body}</body></html>`;
}

function buildRtf(sections) {
  const esc = (s) => {
    let o = "";
    for (const ch of String(s || "")) {
      const c = ch.codePointAt(0);
      if (c > 127) o += `\\u${c}?`;
      else if (ch === "\\") o += "\\\\";
      else if (ch === "{") o += "\\{";
      else if (ch === "}") o += "\\}";
      else if (ch === "\n") o += "\\line ";
      else o += ch;
    }
    return o;
  };

  let rtf = "{\\rtf1\\ansi\\deff0{\\fonttbl{\\f0\\fmodern Malgun Gothic;}}\\f0\\fs22\n";
  rtf += `\\b MX SRM 구조체 멤버 용도 사전\\b0\\line `;
  rtf += `생성일: ${new Date().toISOString().slice(0, 10)}\\line\\line `;

  for (const sec of sections) {
    rtf += `\\page\\b ${esc(sec.title)}\\b0\\line `;
    rtf += `${esc(sec.note)}\\line\\line `;
    for (const r of sec.rows) {
      const files = [...new Set([...r.usage.writes, ...r.usage.reads].map((x) => x.split(":")[0]))]
        .slice(0, 3)
        .join(", ");
      rtf += `\\b ${esc(r.path)}\\b0\\line `;
      rtf += `타입: ${esc(r.type)} | 주석: ${esc(r.comment || "-")}\\line `;
      rtf += `용도: ${esc(r.purpose)}\\line `;
      rtf += `파일: ${esc(files || "-")}\\line\\line `;
    }
  }
  rtf += "}";
  return rtf;
}

async function buildDocx(sections) {
  let docx;
  try {
    docx = require("docx");
  } catch (_) {
    return false;
  }

  const {
    Document,
    Packer,
    Paragraph,
    HeadingLevel,
    Table,
    TableRow,
    TableCell,
    TextRun,
    WidthType,
    BorderStyle,
  } = docx;

  const children = [
    new Paragraph({
      text: "MX SRM — 구조체 멤버 용도 사전",
      heading: HeadingLevel.TITLE,
    }),
    new Paragraph({
      children: [
        new TextRun({
          text: `생성일: ${new Date().toISOString().slice(0, 10)} | 구조체 멤버 → 실제 용도`,
          italics: true,
        }),
      ],
    }),
    new Paragraph({ text: "" }),
  ];

  for (const sec of sections) {
    children.push(
      new Paragraph({ text: sec.title, heading: HeadingLevel.HEADING_1 }),
      new Paragraph({ text: sec.note }),
      new Paragraph({ text: "" })
    );

    const headerRow = new TableRow({
      children: ["멤버 경로", "타입", "주석", "실제 용도", "사용 파일"].map(
        (t) =>
          new TableCell({
            children: [new Paragraph({ children: [new TextRun({ text: t, bold: true })] })],
            width: { size: 20, type: WidthType.PERCENTAGE },
          })
      ),
    });

    const dataRows = sec.rows.map((r) => {
      const files = [...new Set([...r.usage.writes, ...r.usage.reads].map((x) => x.split(":")[0]))]
        .slice(0, 3)
        .join(", ");
      return new TableRow({
        children: [r.path, r.type, r.comment || "-", r.purpose, files || "-"].map(
          (t) =>
            new TableCell({
              children: [new Paragraph({ text: String(t).slice(0, 500) })],
            })
        ),
      });
    });

    children.push(
      new Table({
        rows: [headerRow, ...dataRows],
        width: { size: 100, type: WidthType.PERCENTAGE },
      }),
      new Paragraph({ text: "" })
    );
  }

  const doc = new Document({ sections: [{ children }] });
  const buf = await Packer.toBuffer(doc);
  fs.writeFileSync(path.join(OUT_DIR, "SRM_구조체멤버_용도사전.docx"), buf);
  return true;
}

async function main() {
  const headerText = readText(HEADER_PATH);
  const devText = readText(DEV_SRM_PATH);
  const maps = parseStructs(headerText + "\n" + devText);

  // dev_SRM.c 전용 struct 추가 파싱
  const devMaps = parseStructs(devText);
  for (const [k, v] of devMaps.byTypedef) {
    if (!maps.byTypedef.has(k)) maps.byTypedef.set(k, v);
  }

  const srcCache = loadSourceLines();
  const sections = [];

  for (const g of ROOT_GLOBALS) {
    if (g.indirect) continue;
    const gVar = g.var.split(" ")[0];
    const rows = flattenStruct(g.type, gVar, maps, 0, g.type === "StatusSTR" ? 4 : 3);

    for (const row of rows) {
      row.usage = analyzeUsage(gVar, row.path, row.member, srcCache);
      row.purpose = inferUsagePurpose(gVar, row, row.usage);
    }

    sections.push({
      id: gVar.replace(/[^a-zA-Z0-9]/g, "_"),
      title: `${gVar} — ${g.title}`,
      note: g.note,
      rows,
    });
  }

  // WorkCmdSTR 별도 (0x41 수신)
  const workCmdRows = flattenStruct("WorkCmdSTR", "WorkCmd", maps, 0, 2);
  for (const row of workCmdRows) {
    row.usage = analyzeUsage("WorkCmd", row.path, row.member, srcCache);
    row.purpose = inferUsagePurpose("WorkCmd", row, row.usage);
  }
  sections.push({
    id: "WorkCmdSTR",
    title: "WorkCmdSTR — TML 0x41 수신 작업명령",
    note: "com_tml.c rxCmdOrder 파싱 결과. m_WorkData로 변환되기 전 원본 구조.",
    rows: workCmdRows,
  });

  const html = buildHtml(sections);
  fs.writeFileSync(path.join(OUT_DIR, "SRM_구조체멤버_용도사전.html"), html, "utf8");

  const rtf = buildRtf(sections);
  fs.writeFileSync(path.join(OUT_DIR, "SRM_구조체멤버_용도사전.rtf"), rtf, "utf8");

  const docxOk = await buildDocx(sections);

  const totalMembers = sections.reduce((a, s) => a + s.rows.length, 0);
  const readme = `# 구조체 멤버 용도 사전 (권장)

이전 \`Vol01~\` 자동 사전은 **함수/enum 위주**라 원하신 내용과 맞지 않았습니다.
아래 파일이 **구조체 멤버 용도** 중심 문서입니다.

| 파일 | 용도 |
|------|------|
| **SRM_구조체멤버_용도사전.html** | 브라우저 → **인쇄 → PDF 저장** (표 형식, 가독성 최고) |
| **SRM_구조체멤버_용도사전.rtf** | **Word에서 바로 열기** (더블클릭) |
| **SRM_구조체멤버_용도사전.docx** | Word 네이티브 ${docxOk ? "(생성됨)" : "(npm install docx 후 재생성)"} |

## 통계
- 구조체 그룹: ${sections.length}개
- 멤버 항목: ${totalMembers}개

## 재생성
\`\`\`bash
cd docs/manual
npm install
node generate_struct_manual.js
\`\`\`

## 분류
1. **m_St** — 지상반 0x30 상태
2. **m_pgmEnv** — MCU 내부 RunMode/플래그
3. **m_WorkData** — 작업 사이클 데이터
4. **m_BKSram** — 정전복구
5. **WorkCmdSTR** — 0x41 수신 원본
`;
  fs.writeFileSync(path.join(OUT_DIR, "README.md"), readme, "utf8");

  console.log(`Members: ${totalMembers}, sections: ${sections.length}`);
  console.log(`HTML: ${path.join(OUT_DIR, "SRM_구조체멤버_용도사전.html")}`);
  console.log(`RTF: ${path.join(OUT_DIR, "SRM_구조체멤버_용도사전.rtf")}`);
}

main().catch((e) => {
  console.error(e);
  process.exit(1);
});
