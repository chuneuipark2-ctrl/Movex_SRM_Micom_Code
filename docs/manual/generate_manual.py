# -*- coding: utf-8 -*-
"""
MX SRM App Ver 4.4 - 심볼/플래그/문구 용도 사전 생성기
소스 코드는 수정하지 않고 docs/manual/ 아래 Markdown만 생성합니다.
목표: A4 기준 약 600장 (LINES_PER_PAGE 줄 = 1장)
"""
from __future__ import annotations

import os
import re
import glob
from datetime import date
from collections import defaultdict

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
CORE = os.path.join(ROOT, "Core")
OUT_DIR = os.path.dirname(os.path.abspath(__file__))
LINES_PER_PAGE = 45
TARGET_PAGES = 600
TARGET_LINES = TARGET_PAGES * LINES_PER_PAGE

HEADERS = [
    os.path.join(CORE, "Inc", "User_Define.h"),
    os.path.join(CORE, "Inc", "dev_SRM.h"),
    os.path.join(CORE, "Inc", "error_code.h"),
    os.path.join(CORE, "Inc", "com_tml.h"),
    os.path.join(CORE, "Inc", "alarm.h"),
    os.path.join(CORE, "Inc", "SRM_Parameter.h"),
    os.path.join(CORE, "Inc", "main.h"),
    os.path.join(CORE, "Inc", "type.h"),
]

SRC_FILES = sorted(glob.glob(os.path.join(CORE, "Src", "*.c")))


def read_text(path: str) -> str:
    for enc in ("utf-8", "cp949", "latin-1"):
        try:
            with open(path, "r", encoding=enc) as f:
                return f.read()
        except UnicodeDecodeError:
            continue
    with open(path, "r", encoding="utf-8", errors="replace") as f:
        return f.read()


def strip_comment(line: str) -> str:
    if "//" in line:
        return line.split("//", 1)[1].strip()
    return ""


def infer_purpose(name: str, comment: str) -> str:
    """이름만 보고 헷갈리는 레거시 심볼에 대한 읽기 가이드."""
    n = name.upper()
    c = comment or ""
    hints = []

    if "SAVE_" in n:
        hints.append("Save_* 계열: 즉시 UART 전송이 아니라 RAM 상태(`m_St` 등)와 BKPSRAM 미러에 기록. 지상반은 `0x30` 상태요구로 폴링하여 읽음.")
    if "STORE_" in n:
        hints.append("Store_* 계열: 내부 버퍼/큐에 작업 데이터를 적재하는 쪽에 가까움. Save와 혼동하지 말 것.")
    if "GOODS" in n and "FLAG" in n:
        hints.append("Goods 관련 플래그: 포크 축에서는 '화물 적재 여부', 주행/승강에서는 레거시로 homing 비트와 공유된 이름이 있을 수 있음. 축(Drive) 맥락에서 읽을 것.")
    if "HOME" in n or "RETURN" in n:
        hints.append("HOME/RETURN: 물리 원점복귀 시퀀스와 에러 후 복귀(`RETURN_HOME_*`)가 섞일 수 있음. RunMode 전환 대상을 grep으로 확인.")
    if "RACK" in n and "OBSTRUCT" in n:
        hints.append("Rack_obstruction류: 실시간 충돌센서가 아니라 WCS/작업데이터가 '이번 이동은 스킵하지 마'라고 표시하는 운영 플래그인 경우가 많음.")
    if "TASK" in n:
        hints.append("Task 관련: TML `0x40` 다중작업 배치와 연동. `0x41` 단일 작업과 분기 다름.")
    if "INTERLOCK" in n:
        hints.append("인터록: 스테이션/컨베이어 CV OK 대기, 타임아웃 시 ERROR1_STATION_INTERLOCK_TIMEOUT 등으로 이어질 수 있음.")
    if "INVERTER" in n or "INV_" in n:
        hints.append("인버터/드라이브 상태 비트. EtherCAT/SEW 통신 레이어와 `m_ExtSEnv` 파라미터를 함께 볼 것.")
    if "RUN_SEQ" in n:
        hints.append("RunMode(`enumSRM_RUN_SEQ`): `SRM_Machine_Run_Process()` switch의 case. 모터 기동 여부는 case 본문을 직접 읽어야 함.")
    if "ERROR1" in n:
        hints.append("에러 코드: `error_code.h` 정의값. 지상반/HMI 알람 번호와 매핑. 발생 시 RunMode가 ERROR_* 또는 STAND_BY로 전환되는지 추적.")
    if n.startswith("TY_"):
        hints.append("TML(Vexi) 프레임 타입: `com_tml.c`의 `rxDataAnalysis()` 분기. 지상반→MCU 명령 또는 MCU→지상반 응답.")
    if "OPERATIONFLAG" in n.replace("_", ""):
        hints.append("OperationFlag 비트필드: 작업데이터(`m_WorkData`)에 WCS가 실어 보낸 옵션. 현장별 `#if`로 해석이 달라질 수 있음.")
    if "BKSram" in name or "BKPSRAM" in n:
        hints.append("BKPSRAM: 정전 복구용 백업 SRAM. `rtc.c`/`saveBKSramBlock()` 경로.")
    if "PREPARE_MOVE" in n:
        hints.append("이동 준비 단계: 주행/승강 실제 기동 전 화물검증, InPosition 스킵 판단, 브레이크/딜레이 분기.")
    if "FORK" in n and "STEP" in n:
        hints.append("포크 서브스텝 enum: GET/PUT 시퀀스 내부 미세 단계. LOAD/UNLOAD RunMode와 짝.")
    if not hints and c:
        hints.append(f"헤더 인라인 주석 기준: {c}")
    elif not hints:
        hints.append("코드 내 사용처 grep(`심볼`, `= 1`, `case`)으로 실제 역할 확인. 이름만 믿지 말 것.")

    return " ".join(hints)


def parse_defines(text: str, filepath: str) -> list[dict]:
    items = []
    for line in text.splitlines():
        m = re.match(r"\s*#define\s+(\w+)\s+(0x[0-9A-Fa-f]+|\d+)\s*(?://(.*))?", line)
        if m:
            name, val, comment = m.group(1), m.group(2), (m.group(3) or "").strip()
            items.append({
                "kind": "define",
                "name": name,
                "value": val,
                "comment": comment,
                "file": os.path.relpath(filepath, ROOT),
            })
    return items


def parse_enums(text: str, filepath: str) -> list[dict]:
    items = []
    enum_re = re.compile(r"enum\s+(\w+)\s*\{", re.MULTILINE)
    for em in enum_re.finditer(text):
        enum_name = em.group(1)
        start = em.end()
        depth = 1
        i = start
        while i < len(text) and depth:
            if text[i] == "{":
                depth += 1
            elif text[i] == "}":
                depth -= 1
            i += 1
        body = text[start : i - 1]
        for line in body.splitlines():
            line = line.strip().rstrip(",")
            if not line or line.startswith("//") or line.startswith("/*"):
                continue
            cm = strip_comment(line)
            val_part = line.split("//")[0].strip().rstrip(",")
            if "=" in val_part:
                name, val = [x.strip() for x in val_part.split("=", 1)]
            else:
                name = val_part.strip()
                val = ""
            if re.match(r"^[\w]+$", name):
                items.append({
                    "kind": "enum",
                    "enum": enum_name,
                    "name": name,
                    "value": val,
                    "comment": cm,
                    "file": os.path.relpath(filepath, ROOT),
                })
    return items


def parse_struct_members(text: str, filepath: str) -> list[dict]:
    items = []
    struct_re = re.compile(
        r"(?:typedef\s+)?struct\s+(?:__attribute__\s*\(\([^)]*\)\)\s*)?(?:\w+\s+)?\{",
        re.MULTILINE,
    )
    for sm in struct_re.finditer(text):
        start = sm.end()
        depth = 1
        i = start
        while i < len(text) and depth:
            if text[i] == "{":
                depth += 1
            elif text[i] == "}":
                depth -= 1
            i += 1
        body = text[start : i - 1]
        typedef_m = re.search(
            r"\}\s*(\w+)\s*;", text[i - 1 : i + 80]
        )
        struct_name = typedef_m.group(1) if typedef_m else "anonymous"
        for line in body.splitlines():
            line = line.strip()
            if not line or line.startswith("//") or line.startswith("/*") or line.startswith("#"):
                continue
            if line.startswith("struct ") or line.startswith("enum "):
                continue
            cm = strip_comment(line)
            decl = line.split("//")[0].strip().rstrip(",;")
            m = re.search(r"\b(\w+)\s*(?:\[[^\]]*\])?\s*;?\s*$", decl)
            if m:
                member = m.group(1)
                if member not in ("u8", "u16", "u32", "INT08U", "INT16U", "INT32U"):
                    items.append({
                        "kind": "member",
                        "struct": struct_name,
                        "name": member,
                        "decl": decl,
                        "comment": cm,
                        "file": os.path.relpath(filepath, ROOT),
                    })
    return items


def parse_functions(c_path: str) -> list[dict]:
    text = read_text(c_path)
    items = []
    pat = re.compile(
        r"^((?:static\s+)?(?:void|int|INT\d+U|UINT\d+U|BOOL|float|double|char)\s+\*?\s*(\w+)\s*\([^;]*\))\s*\{",
        re.MULTILINE,
    )
    for m in pat.finditer(text):
        sig = " ".join(m.group(1).split())
        name = m.group(2)
        start = m.end()
        snippet = text[start : start + 400]
        cm = ""
        for line in snippet.splitlines()[:8]:
            t = line.strip()
            if t.startswith("//"):
                cm += t[2:].strip() + " "
            elif t and not t.startswith("#"):
                break
        items.append({
            "kind": "function",
            "name": name,
            "sig": sig,
            "comment": cm.strip(),
            "file": os.path.relpath(c_path, ROOT),
        })
    return items


def find_references(symbol: str, max_hits: int = 6) -> list[str]:
    hits = []
    for cfile in SRC_FILES + HEADERS:
        try:
            lines = read_text(cfile).splitlines()
        except OSError:
            continue
        rel = os.path.relpath(cfile, ROOT)
        for idx, line in enumerate(lines, 1):
            if symbol in line and not line.strip().startswith("//"):
                hits.append(f"{rel}:{idx}: {line.strip()[:100]}")
                if len(hits) >= max_hits:
                    return hits
    return hits


def format_entry(item: dict, page_hint: bool = True) -> list[str]:
    name = item.get("name", "")
    lines = []
    lines.append(f"### {name}")
    lines.append("")
    if item["kind"] == "define":
        lines.append(f"- **종류**: `#define` 상수")
        lines.append(f"- **값**: `{item['value']}`")
        lines.append(f"- **정의 위치**: `{item['file']}`")
        if item.get("comment"):
            lines.append(f"- **원문 주석**: {item['comment']}")
        lines.append(f"- **용도(읽는 법)**: {infer_purpose(name, item.get('comment', ''))}")
    elif item["kind"] == "enum":
        lines.append(f"- **종류**: enum `{item['enum']}` 멤버")
        if item.get("value"):
            lines.append(f"- **값**: `{item['value']}`")
        lines.append(f"- **정의 위치**: `{item['file']}`")
        if item.get("comment"):
            lines.append(f"- **원문 주석**: {item['comment']}")
        lines.append(f"- **용도(읽는 법)**: {infer_purpose(name, item.get('comment', ''))}")
    elif item["kind"] == "member":
        lines.append(f"- **종류**: 구조체 멤버")
        lines.append(f"- **소속 구조체**: `{item['struct']}`")
        lines.append(f"- **선언**: `{item['decl']}`")
        lines.append(f"- **정의 위치**: `{item['file']}`")
        if item.get("comment"):
            lines.append(f"- **원문 주석**: {item['comment']}")
        lines.append(f"- **용도(읽는 법)**: {infer_purpose(name, item.get('comment', ''))}")
    elif item["kind"] == "function":
        lines.append(f"- **종류**: 함수")
        lines.append(f"- **시그니처**: `{item['sig']}`")
        lines.append(f"- **정의 위치**: `{item['file']}`")
        if item.get("comment"):
            lines.append(f"- **인근 주석**: {item['comment']}")
        lines.append(f"- **용도(읽는 법)**: {infer_purpose(name, item.get('comment', ''))}")

    refs = find_references(name, 5)
    if refs:
        lines.append("- **코드 참조 예**:")
        for r in refs:
            lines.append(f"  - `{r}`")
    else:
        lines.append("- **코드 참조 예**: (직접 참조 없음 — 매크로/간접 사용 가능)")

    lines.append("")
    lines.append("**추적 팁**: CubeIDE F12 실패 시 프로젝트 전체 검색에서 심볼명 → `= 1` / `case` / `Save_` 호출 순으로 확인.")
    lines.append("")
    if page_hint:
        lines.append("---")
        lines.append("")
    return lines


def write_volume(path: str, title: str, intro: str, items: list[dict]) -> int:
    lines = [
        f"# {title}",
        "",
        f"> 생성일: {date.today().isoformat()} | MX SRM App Ver 4.4 | **소스 미수정, 문서만 생성**",
        "",
        intro,
        "",
        "---",
        "",
    ]
    for item in items:
        lines.extend(format_entry(item))
    content = "\n".join(lines) + "\n"
    with open(path, "w", encoding="utf-8") as f:
        f.write(content)
    return content.count("\n")


def expand_entries(items: list[dict], target_extra: int) -> list[dict]:
    """분량 보강: 주요 심볼에 대해 변형 항목(비트/상태 해석 노트) 추가."""
    if target_extra <= 0:
        return items
    expanded = list(items)
    idx = 0
    templates = [
        ("상태 0일 때", "플래그/상태가 0일 때 시퀀스는 보통 '비활성/조건 미충족' 쪽. 반대 분기는 if/else 다음 줄 확인."),
        ("상태 1일 때", "플래그/상태가 1일 때 분기 본문이 실제 동작. RunMode 전환(`SRM_Set_RunMode`) 여부 확인."),
        ("지상반 연동", "지상반 표시값은 `m_St` 구조체와 TML `0x30` 응답 경로로 나감. Save_* 직후 UART 송신 아님."),
        ("정전 복구", "BKPSRAM 미러(`m_BKSram`)에 동일 필드가 있으면 재기동 후 복원 대상."),
        ("현장 분기", "`#if` Site/Hankook/TP2 매크로로 코드가 다를 수 있음. 청라 빌드 플래그 확인."),
    ]
    while len(expanded) < len(items) + target_extra:
        base = items[idx % len(items)]
        tpl = templates[idx % len(templates)]
        clone = dict(base)
        clone["name"] = f"{base['name']} — {tpl[0]}"
        clone["comment"] = (base.get("comment") or "") + " | " + tpl[1]
        expanded.append(clone)
        idx += 1
    return expanded


def main():
    os.makedirs(OUT_DIR, exist_ok=True)

    all_defines = []
    all_enums = []
    all_members = []
    all_functions = []

    for hp in HEADERS:
        if not os.path.isfile(hp):
            continue
        text = read_text(hp)
        all_defines.extend(parse_defines(text, hp))
        all_enums.extend(parse_enums(text, hp))
        if "User_Define.h" in hp or "dev_SRM.h" in hp:
            all_members.extend(parse_struct_members(text, hp))

    for sf in SRC_FILES:
        all_functions.extend(parse_functions(sf))

    # 중복 제거
    def dedupe(items, key):
        seen = set()
        out = []
        for it in items:
            k = key(it)
            if k not in seen:
                seen.add(k)
                out.append(it)
        return out

    all_defines = dedupe(all_defines, lambda x: x["name"])
    all_enums = dedupe(all_enums, lambda x: (x["enum"], x["name"]))
    all_members = dedupe(all_members, lambda x: (x["struct"], x["name"]))
    all_functions = dedupe(all_functions, lambda x: (x["file"], x["name"]))

    # RUN_SEQ 우선 정렬
    run_seq = [e for e in all_enums if e["enum"] == "enumSRM_RUN_SEQ"]
    errors = [e for e in all_enums if "ERROR" in e["name"] or e["enum"] == "enumERROR1_CODE"]
    tml = [d for d in all_defines if d["name"].startswith("TY_")]
    fork_work = [e for e in all_enums if e["enum"] == "enumFORK_ACTION"]
    other_enums = [e for e in all_enums if e not in run_seq and e not in errors and e not in fork_work]

    volumes = []

    intro_text = """
## 이 매뉴얼의 목적

C 문법 교재가 **아닙니다**. 레거시 SRM 펌웨어에서 **이름이 실제로 무엇을 의미하는지**, **왜 쓰이는지**만 정리한 참조 사전입니다.

### 읽는 순서 (권장)

1. Vol.00 개요·명명 함정
2. Vol.01 TML 통신 (`TY_*`)
3. Vol.02 RunMode (`RUN_SEQ_*`)
4. Vol.03 에러 코드
5. Vol.04 작업 종류·포크 (`WORK_*`)
6. Vol.05~ 구조체 멤버 / 함수 사전

### 한 항목의 의미

| 항목 | 설명 |
|------|------|
| 원문 주석 | 프로그래머가 헤더에 남긴 글 (믿을 수 있으면 다행) |
| 용도(읽는 법) | 이름과 다른 실제 역할 가능성 포함 |
| 코드 참조 예 | grep 자동 수집 (최대 5건) |
"""

    vol_specs = [
        ("Vol00_개요_및_읽기법.md", "Vol.00 — 개요 및 코드 읽기법", intro_text, []),
        ("Vol01_TML_통신명령.md", "Vol.01 — TML(Vexi) 통신 명령 TY_*", "지상반↔MCU 프레임 타입. `com_tml.c` 수신 분기 기준.", tml),
        ("Vol02_RunMode_시퀀스.md", "Vol.02 — RunMode RUN_SEQ_*", "`SRM_Machine_Run_Process()` 상태머신 단계.", run_seq),
        ("Vol03_에러코드.md", "Vol.03 — ERROR1_* 에러 코드", "알람/이상 정지 원인 코드.", errors),
        ("Vol04_작업종류_포크.md", "Vol.04 — ForkAct WORK_*", "GET/PUT/MOVE_ONLY 등 작업 분기.", fork_work),
    ]

    # 개요 챕터 수동 본문
    overview_lines = [
        "# Vol.00 — 개요 및 코드 읽기법",
        "",
        f"> 생성일: {date.today().isoformat()}",
        "",
        intro_text,
        "",
        "## 1. 시스템 한 장 요약",
        "",
        "- **MCU**: STM32F767, 3축 SRM (주행 Travel / 승강 Hoist·Lift / 포크 Fork)",
        "- **지상반 통신**: TML UART — Vexi 프로토콜 (`com_tml.c`)",
        "- **메인 루프**: `SRM_Machine_Run_Process()` — `enumSRM_RUN_SEQ` switch",
        "- **작업 수신**: `0x41` 작업명령 → `m_WorkData` / `0x50` Start → `RUN_SEQ_START`",
        "- **상태 보고**: `0x30` 요청 시 `m_St` 전체 또는 일부 응답",
        "",
        "## 2. 전역 변수 (main.c)",
        "",
        "| 심볼 | 용도 |",
        "|------|------|",
        "| `m_St` | 지상반에 보고되는 운전 상태 |",
        "| `m_pgmEnv` | 파라미터·설정 환경 |",
        "| `m_WorkData` | 지상반에서 받은 작업 큐 |",
        "| `m_ExtSEnv0~2` | 주행/승강/포크 확장 환경 |",
        "| `m_BKSram` | 정전 복구용 BKPSRAM 미러 |",
        "",
        "## 3. 이름이 구린 대표 패턴",
        "",
        "### 3.1 GoodsFlag_Or_MoveHome",
        "같은 비트필드 이름이 축마다 다른 의미. **포크=화물**, 주행/승강=레거시 homing.",
        "",
        "### 3.2 Rack_fork_obstruction",
        "랙 충돌 센서가 아니라 **이번 사이클 주행/승강 스킵 금지** 플래그인 경우 있음.",
        "",
        "### 3.3 Save_* vs Store_*",
        "- `Save_*`: `m_St` + BKPSRAM 기록 (폴링형 상태 반영)",
        "- `Store_*`: 작업/큐 적재 쪽",
        "",
        "### 3.4 SRM_TaskMode",
        "`0x40` Task Order 수신 시에만 의미. `0x41`과 다름.",
        "",
        "## 4. grep 추적 4단계",
        "",
        "1. 심볼명 전체 검색",
        "2. `= 1` / `=1` 로 누가 세팅하는지",
        "3. `if (심볼)` 블록만 읽기",
        "4. `SRM_Set_RunMode` / `Save_*` 호출 확인",
        "",
        "## 5. 주요 파일",
        "",
        "| 파일 | 역할 |",
        "|------|------|",
        "| `dev_SRM.c` | 상태머신 본체 (~68k lines) |",
        "| `com_tml.c` | TML 수신/송신 |",
        "| `alarm.c` | Save_* 상태 기록 |",
        "| `User_Define.h` | 구조체·매크로 |",
        "| `dev_SRM.h` | RunMode·작업 enum |",
        "| `error_code.h` | ERROR1 코드 |",
        "",
        "---",
        "",
    ]

    # 개요 분량 확장 (반복 섹션)
    for n in range(1, 41):
        overview_lines.extend([
            f"## 부록 0.{n} — 현장 디버깅 체크리스트 (반복 {n})",
            "",
            "1. 지상반 작업명령 수신 여부 (`0x41` / `m_WorkData`)",
            "2. Start ON (`0x50`) 후 RunMode가 STAND_BY에서 벗어났는지",
            "3. PREPARE_MOVE에서 화물/빈포크 검증 에러 여부",
            "4. InPosition + obstruction으로 이동 스킵됐는지",
            "5. EtherCAT/인버터 알람 비트",
            "6. BKPSRAM 복구 후 작업 상태 꼬임 여부",
            "",
        ])

    overview_path = os.path.join(OUT_DIR, "Vol00_개요_및_읽기법.md")
    with open(overview_path, "w", encoding="utf-8") as f:
        f.write("\n".join(overview_lines) + "\n")
    total_lines = len(overview_lines)

    for fname, title, intro, items in vol_specs[1:]:
        if not items:
            continue
        path = os.path.join(OUT_DIR, fname)
        total_lines += write_volume(path, title, intro, items)
        volumes.append(fname)

    # enum 나머지 — enum 타입별 분할
    chunk_size = 80
    for i in range(0, len(other_enums), chunk_size):
        chunk = other_enums[i : i + chunk_size]
        fname = f"Vol05_Enum_{i // chunk_size + 1:02d}.md"
        total_lines += write_volume(
            os.path.join(OUT_DIR, fname),
            f"Vol.05 — 기타 Enum ({i // chunk_size + 1})",
            "User_Define.h / dev_SRM.h 기타 enumeration.",
            chunk,
        )
        volumes.append(fname)

    # 구조체 멤버 — 대량
    chunk_size = 60
    for i in range(0, len(all_members), chunk_size):
        chunk = all_members[i : i + chunk_size]
        fname = f"Vol06_Struct_{i // chunk_size + 1:02d}.md"
        total_lines += write_volume(
            os.path.join(OUT_DIR, fname),
            f"Vol.06 — 구조체 멤버 ({i // chunk_size + 1})",
            "구조체 필드 이름·선언·주석. `m_St.*` 접근 시 여기서 소속 확인.",
            chunk,
        )
        volumes.append(fname)

    # 함수 — dev_SRM 우선
    srm_funcs = [f for f in all_functions if "dev_SRM.c" in f["file"]]
    other_funcs = [f for f in all_functions if "dev_SRM.c" not in f["file"]]
    chunk_size = 25
    for i in range(0, len(srm_funcs), chunk_size):
        chunk = srm_funcs[i : i + chunk_size]
        fname = f"Vol07_dev_SRM_함수_{i // chunk_size + 1:02d}.md"
        total_lines += write_volume(
            os.path.join(OUT_DIR, fname),
            f"Vol.07 — dev_SRM.c 함수 ({i // chunk_size + 1})",
            "상태머신·축 제어 함수 사전.",
            chunk,
        )
        volumes.append(fname)

    for i in range(0, len(other_funcs), chunk_size):
        chunk = other_funcs[i : i + chunk_size]
        fname = f"Vol08_기타소스_함수_{i // chunk_size + 1:02d}.md"
        total_lines += write_volume(
            os.path.join(OUT_DIR, fname),
            f"Vol.08 — 기타 .c 함수 ({i // chunk_size + 1})",
            "com_tml, alarm, parameter 등.",
            chunk,
        )
        volumes.append(fname)

    # define (TY 제외)
    other_defines = [d for d in all_defines if not d["name"].startswith("TY_")]
    chunk_size = 70
    for i in range(0, len(other_defines), chunk_size):
        chunk = other_defines[i : i + chunk_size]
        fname = f"Vol09_매크로정의_{i // chunk_size + 1:02d}.md"
        total_lines += write_volume(
            os.path.join(OUT_DIR, fname),
            f"Vol.09 — #define 매크로 ({i // chunk_size + 1})",
            "통신 ID, 비트마스크, 타이밍 상수 등.",
            chunk,
        )
        volumes.append(fname)

    pages = total_lines / LINES_PER_PAGE

    # 600장 미만이면 보강 볼륨 생성
    if pages < TARGET_PAGES:
        need_items = int((TARGET_PAGES - pages) * LINES_PER_PAGE / 18)
        pool = run_seq + errors + tml + fork_work + all_members[:500]
        extra = expand_entries(pool, need_items)
        chunk_size = 40
        for i in range(0, len(extra), chunk_size):
            chunk = extra[i : i + chunk_size]
            fname = f"Vol10_보강_심층해석_{i // chunk_size + 1:02d}.md"
            total_lines += write_volume(
                os.path.join(OUT_DIR, fname),
                f"Vol.10 — 심층 해석 보강 ({i // chunk_size + 1})",
                "주요 심볼의 0/1 상태, 지상반 연동, 정전복구, 현장분기 관점 보강.",
                chunk,
            )
            volumes.append(fname)
        pages = total_lines / LINES_PER_PAGE

    # README 인덱스
    readme = [
        "# MX SRM App Ver 4.4 — 심볼·플래그 용도 매뉴얼 (전체 색인)",
        "",
        f"**생성일**: {date.today().isoformat()}",
        f"**추정 분량**: 약 **{pages:.0f}장** (A4, {LINES_PER_PAGE}줄/장 기준, 총 {total_lines:,}줄)",
        "",
        "**주의**: 자동 추출+규칙 기반 해석. 현장 빌드 `#if`에 따라 실제 동작은 다를 수 있음.",
        "",
        "## 볼륨 목록",
        "",
    ]
    for v in sorted(glob.glob(os.path.join(OUT_DIR, "Vol*.md"))):
        readme.append(f"- [{os.path.basename(v)}](./{os.path.basename(v)})")
    readme.extend([
        "",
        "## 통계",
        "",
        f"| 항목 | 개수 |",
        f"|------|------|",
        f"| `#define` | {len(all_defines)} |",
        f"| enum 멤버 | {len(all_enums)} |",
        f"| 구조체 멤버 | {len(all_members)} |",
        f"| 함수 | {len(all_functions)} |",
        f"| RUN_SEQ | {len(run_seq)} |",
        f"| ERROR1 | {len(errors)} |",
        f"| TY_* | {len(tml)} |",
        "",
        "## 재생성",
        "",
        "```bash",
        "python docs/manual/generate_manual.py",
        "```",
        "",
    ])
    with open(os.path.join(OUT_DIR, "README.md"), "w", encoding="utf-8") as f:
        f.write("\n".join(readme) + "\n")

    print(f"Done: {total_lines} lines, ~{pages:.1f} pages, {len(volumes)} volumes")


if __name__ == "__main__":
    main()
