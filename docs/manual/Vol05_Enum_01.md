# Vol.05 — 기타 Enum (1)

> 생성일: 2026-06-16 | MX SRM App Ver 4.4 | 소스 미수정

기타 enumeration.

---

### HANKOOK_TIRE_TP2_PCR_INNER_LINE

- **종류**: enum `enumHANKOOK_TIRE_TP2_LINE` 멤버
- **값**: `1`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 1, PCR - INNER LINE (I/L)
- **용도(읽는 법)**: 헤더 주석: 1, PCR - INNER LINE (I/L)
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:22033: if ((m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_INNER_LINE) \`
  - `Core/Src/dev_SRM.c:30636: if (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_INNER_LINE)`
  - `Core/Src/dev_SRM.c:31738: if (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_INNER_LINE)`
  - `Core/Inc/User_Define.h:178: HANKOOK_TIRE_TP2_PCR_INNER_LINE = 1,	// 1, PCR - INNER LINE (I/L)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HANKOOK_TIRE_TP2_PCR_TREAD

- **종류**: enum `enumHANKOOK_TIRE_TP2_LINE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 2, PCR - Tread(T/D) ìëì°½ê³  (ìì¶)
- **용도(읽는 법)**: 헤더 주석: 2, PCR - Tread(T/D) ìëì°½ê³  (ìì¶)
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:22034: || (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_TREAD) \`
  - `Core/Src/main.c:639: if (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_TREAD)`
  - `Core/Src/main.c:643: else if (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_TREAD)`
  - `Core/Inc/User_Define.h:179: HANKOOK_TIRE_TP2_PCR_TREAD,				// 2, PCR - Tread(T/D) ìëì°½ê³  (ìì¶)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HANKOOK_TIRE_TP2_PCR_SIDE_WALL

- **종류**: enum `enumHANKOOK_TIRE_TP2_LINE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 3, PCR - Side Wall(S/W) ìëì°½ê³ (ìì¶)
- **용도(읽는 법)**: 헤더 주석: 3, PCR - Side Wall(S/W) ìëì°½ê³ (ìì¶)
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:22035: || (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_SIDE_WALL) \`
  - `Core/Inc/User_Define.h:180: HANKOOK_TIRE_TP2_PCR_SIDE_WALL,			// 3, PCR - Side Wall(S/W) ìëì°½ê³ (ìì¶)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HANKOOK_TIRE_TP2_PCR_CARCASS

- **종류**: enum `enumHANKOOK_TIRE_TP2_LINE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 4, PCR - Carcass(C/C) ìëì°½ê³  (ì¬ë¨)
- **용도(읽는 법)**: 헤더 주석: 4, PCR - Carcass(C/C) ìëì°½ê³  (ì¬ë¨)
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:22036: || (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_CARCASS) \`
  - `Core/Inc/User_Define.h:181: HANKOOK_TIRE_TP2_PCR_CARCASS,			// 4, PCR - Carcass(C/C) ìëì°½ê³  (ì¬ë¨)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HANKOOK_TIRE_TP2_PCR_BW

- **종류**: enum `enumHANKOOK_TIRE_TP2_LINE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 5, PCR - PCR ë°ì í (B/W)
- **용도(읽는 법)**: 헤더 주석: 5, PCR - PCR ë°ì í (B/W)
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:22037: || (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_BW) \`
  - `Core/Inc/User_Define.h:182: HANKOOK_TIRE_TP2_PCR_BW,				// 5, PCR - PCR ë°ì í (B/W)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HANKOOK_TIRE_TP2_PCR_JLB

- **종류**: enum `enumHANKOOK_TIRE_TP2_LINE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 6, PCR - PCR ë°ì í (JLB)
- **용도(읽는 법)**: 헤더 주석: 6, PCR - PCR ë°ì í (JLB)
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:22038: || (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_JLB) \`
  - `Core/Inc/User_Define.h:183: HANKOOK_TIRE_TP2_PCR_JLB,				// 6, PCR - PCR ë°ì í (JLB)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HANKOOK_TIRE_TP2_PCR_BELT

- **종류**: enum `enumHANKOOK_TIRE_TP2_LINE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 7, PCR - Belt(B/T) ìëì°½ê³  (ì¬ë¨)
- **용도(읽는 법)**: 헤더 주석: 7, PCR - Belt(B/T) ìëì°½ê³  (ì¬ë¨)
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:22039: || (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_BELT) \`
  - `Core/Inc/User_Define.h:184: HANKOOK_TIRE_TP2_PCR_BELT,				// 7, PCR - Belt(B/T) ìëì°½ê³  (ì¬ë¨)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HANKOOK_TIRE_TP2_PCR_BEAD

- **종류**: enum `enumHANKOOK_TIRE_TP2_LINE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 8, PCR - ìì±Bead(B/D, B/F)ìëì°½ê³  (ì¬ë¨)
- **용도(읽는 법)**: 헤더 주석: 8, PCR - ìì±Bead(B/D, B/F)ìëì°½ê³  (ì¬ë¨)
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:22040: || (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_BEAD) \`
  - `Core/Inc/User_Define.h:185: HANKOOK_TIRE_TP2_PCR_BEAD,				// 8, PCR - ìì±Bead(B/D, B/F)ìëì°½ê³  (ì¬ë¨)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HANKOOK_TIRE_TP2_TBR_TREAD

- **종류**: enum `enumHANKOOK_TIRE_TP2_LINE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 9, TBR - Tread(T/D) ìëì°½ê³  (ìì¶)
- **용도(읽는 법)**: 헤더 주석: 9, TBR - Tread(T/D) ìëì°½ê³  (ìì¶)
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:22041: || (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_TBR_TREAD) \`
  - `Core/Inc/User_Define.h:186: HANKOOK_TIRE_TP2_TBR_TREAD,				// 9, TBR - Tread(T/D) ìëì°½ê³  (ìì¶)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HANKOOK_TIRE_TP2_TBR_STRIP

- **종류**: enum `enumHANKOOK_TIRE_TP2_LINE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 10, TBR - TBR ë°ì í (ì¬ë¨, Strip)
- **용도(읽는 법)**: 헤더 주석: 10, TBR - TBR ë°ì í (ì¬ë¨, Strip)
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:22042: || (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_TBR_STRIP) \`
  - `Core/Inc/User_Define.h:187: HANKOOK_TIRE_TP2_TBR_STRIP,				// 10, TBR - TBR ë°ì í (ì¬ë¨, Strip)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HANKOOK_TIRE_TP2_TBR_CARCASS

- **종류**: enum `enumHANKOOK_TIRE_TP2_LINE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 11, TBR - Carcass(C/C) ìëì°½ê³  (ì¬ë¨)
- **용도(읽는 법)**: 헤더 주석: 11, TBR - Carcass(C/C) ìëì°½ê³  (ì¬ë¨)
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:22043: || (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_TBR_CARCASS) \`
  - `Core/Inc/User_Define.h:188: HANKOOK_TIRE_TP2_TBR_CARCASS,			// 11, TBR - Carcass(C/C) ìëì°½ê³  (ì¬ë¨)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HANKOOK_TIRE_TP2_TBR_BELT

- **종류**: enum `enumHANKOOK_TIRE_TP2_LINE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 12, TBR - Belt(B/T) ìëì°½ê³  (ì¬ë¨)
- **용도(읽는 법)**: 헤더 주석: 12, TBR - Belt(B/T) ìëì°½ê³  (ì¬ë¨)
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:22044: || (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_TBR_BELT) \`
  - `Core/Inc/User_Define.h:189: HANKOOK_TIRE_TP2_TBR_BELT,				// 12, TBR - Belt(B/T) ìëì°½ê³  (ì¬ë¨)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HANKOOK_TIRE_TP2_TBR_BEAD

- **종류**: enum `enumHANKOOK_TIRE_TP2_LINE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 13, TBR - ìì±Bead(B/D or B/F)ìëì°½ê³  (ì¬ë¨)
- **용도(읽는 법)**: 헤더 주석: 13, TBR - ìì±Bead(B/D or B/F)ìëì°½ê³  (ì¬ë¨)
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:22045: || (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_TBR_BEAD) \`
  - `Core/Inc/User_Define.h:190: HANKOOK_TIRE_TP2_TBR_BEAD,				// 13, TBR - ìì±Bead(B/D or B/F)ìëì°½ê³  (ì¬ë¨)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HANKOOK_TIRE_TP2_TBR_MOLD

- **종류**: enum `enumHANKOOK_TIRE_TP2_LINE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 14, TBR - TBR MOLD ì°½ê³
- **용도(읽는 법)**: 헤더 주석: 14, TBR - TBR MOLD ì°½ê³
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:22105: else if ((m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_TBR_MOLD))`
  - `Core/Src/dev_SRM.c:30655: else if (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_TBR_MOLD)`
  - `Core/Src/dev_SRM.c:31761: else if (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_TBR_MOLD)`
  - `Core/Inc/User_Define.h:191: HANKOOK_TIRE_TP2_TBR_MOLD,				// 14, TBR - TBR MOLD ì°½ê³`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HANKOOK_TIRE_TP2_PCR_STEEL_ROLL

- **종류**: enum `enumHANKOOK_TIRE_TP2_LINE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 15, PCR - ìì° Steel Roll
- **용도(읽는 법)**: 헤더 주석: 15, PCR - ìì° Steel Roll
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:22054: else if ((m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_STEEL_ROLL) \`
  - `Core/Src/dev_SRM.c:50285: if (m_ExtSEnv.mDevice.ProjectID.Group_ID != HANKOOK_TIRE_TP2_PCR_STEEL_ROLL)`
  - `Core/Inc/User_Define.h:192: HANKOOK_TIRE_TP2_PCR_STEEL_ROLL,		// 15, PCR - ìì° Steel Roll`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HANKOOK_TIRE_TP2_PCR_GT_LOT4

- **종류**: enum `enumHANKOOK_TIRE_TP2_LINE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 16, PCR - GT LOT4
- **용도(읽는 법)**: 헤더 주석: 16, PCR - GT LOT4
- **코드 참조 예**:
  - `Core/Src/com_tml.c:5580: if ((m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_GT_LOT4) \`
  - `Core/Src/dev_SRM.c:14917: || (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_GT_LOT4) \`
  - `Core/Src/dev_SRM.c:22062: else if (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_GT_LOT4)`
  - `Core/Src/dev_SRM.c:24555: if (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_GT_LOT4)`
  - `Core/Src/dev_SRM.c:30644: else if ((m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_GT_LOT4) \`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HANKOOK_TIRE_TP2_PCR_GT_LOT3

- **종류**: enum `enumHANKOOK_TIRE_TP2_LINE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 17, PCR - GT LOT3
- **용도(읽는 법)**: 헤더 주석: 17, PCR - GT LOT3
- **코드 참조 예**:
  - `Core/Src/com_tml.c:5581: || (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_GT_LOT3) \`
  - `Core/Src/dev_SRM.c:14916: || (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_GT_LOT3) \`
  - `Core/Src/dev_SRM.c:22069: else if (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_GT_LOT3)`
  - `Core/Src/dev_SRM.c:24568: else if (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_GT_LOT3)`
  - `Core/Src/dev_SRM.c:30645: || (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_GT_LOT3) \`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HANKOOK_TIRE_TP2_PCR_MOLD

- **종류**: enum `enumHANKOOK_TIRE_TP2_LINE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 18, PCR - MOLD
- **용도(읽는 법)**: 헤더 주석: 18, PCR - MOLD
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:14918: || (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_MOLD)`
  - `Core/Src/dev_SRM.c:22090: else if ((m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_MOLD))`
  - `Core/Src/dev_SRM.c:31756: else if (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_MOLD)`
  - `Core/Inc/User_Define.h:196: HANKOOK_TIRE_TP2_PCR_MOLD,				// 18, PCR - MOLD`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HANKOOK_TIRE_TP2_PCR_GT_LOT2

- **종류**: enum `enumHANKOOK_TIRE_TP2_LINE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 19, PCR - GT LOT2
- **용도(읽는 법)**: 헤더 주석: 19, PCR - GT LOT2
- **코드 참조 예**:
  - `Core/Src/com_tml.c:5582: || (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_GT_LOT2) \`
  - `Core/Src/dev_SRM.c:14915: || (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_GT_LOT2) \`
  - `Core/Src/dev_SRM.c:22076: else if (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_GT_LOT2)`
  - `Core/Src/dev_SRM.c:24581: else if (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_GT_LOT2)`
  - `Core/Src/dev_SRM.c:30646: || (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_GT_LOT2) \`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HANKOOK_TIRE_TP2_PCR_GT_LOT1

- **종류**: enum `enumHANKOOK_TIRE_TP2_LINE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 20, PCR - GT LOT1
- **용도(읽는 법)**: 헤더 주석: 20, PCR - GT LOT1
- **코드 참조 예**:
  - `Core/Src/com_tml.c:5583: || (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_GT_LOT1))`
  - `Core/Src/dev_SRM.c:14914: if ((m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_GT_LOT1) \`
  - `Core/Src/dev_SRM.c:22083: else if (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_GT_LOT1)`
  - `Core/Src/dev_SRM.c:24594: else if (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_GT_LOT1)`
  - `Core/Src/dev_SRM.c:30647: || (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_GT_LOT1))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HANKOOK_TIRE_TP2_TBR_SIDEWALL

- **종류**: enum `enumHANKOOK_TIRE_TP2_LINE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 21, TBR - TBR SIDEWALL
- **용도(읽는 법)**: 헤더 주석: 21, TBR - TBR SIDEWALL
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:22113: else if (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_TBR_SIDEWALL)`
  - `Core/Src/dev_SRM.c:31766: else if (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_TBR_SIDEWALL)`
  - `Core/Inc/User_Define.h:199: HANKOOK_TIRE_TP2_TBR_SIDEWALL,			// 21, TBR - TBR SIDEWALL`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HANKOOK_TIRE_TP2_TBR_INNER

- **종류**: enum `enumHANKOOK_TIRE_TP2_LINE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 22, TBR - TBR INNER
- **용도(읽는 법)**: 헤더 주석: 22, TBR - TBR INNER
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:22046: || (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_TBR_INNER)`
  - `Core/Src/dev_SRM.c:31772: else if (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_TBR_INNER)`
  - `Core/Inc/User_Define.h:200: HANKOOK_TIRE_TP2_TBR_INNER,				// 22, TBR - TBR INNER`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HANKOOK_TIRE_TP2_PCR_TEXTILE_ROLL

- **종류**: enum `enumHANKOOK_TIRE_TP2_LINE` 멤버
- **값**: `50`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 50, PCR - PCR - ìì° TEXTILE Roll
- **용도(읽는 법)**: 헤더 주석: 50, PCR - PCR - ìì° TEXTILE Roll
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:22055: || (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_TEXTILE_ROLL))`
  - `Core/Inc/User_Define.h:202: HANKOOK_TIRE_TP2_PCR_TEXTILE_ROLL = 50, // 50, PCR - PCR - ìì° TEXTILE Roll`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FALSE

- **종류**: enum `_BOOL` 멤버
- **값**: `0, TRUE`
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/alarm.c:646: s_InputFilterTimerFlag[i] = FALSE;`
  - `Core/Src/alarm.c:689: s_InputFilterTimerFlag = FALSE;`
  - `Core/Src/alarm.c:744: s_InputFilterTimerFlag = FALSE;`
  - `Core/Src/ecat_coe.c:164: NotLast = FALSE;`
  - `Core/Src/ecat_coe.c:179: NotLast = FALSE;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RESET_CAUSE_UNKNOWN

- **종류**: enum `reset_cause_e` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/main.c:725: reset_cause = RESET_CAUSE_UNKNOWN;`
  - `Core/Inc/User_Define.h:224: RESET_CAUSE_UNKNOWN = 0,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RESET_CAUSE_LOW_POWER_RESET

- **종류**: enum `reset_cause_e` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/main.c:692: reset_cause = RESET_CAUSE_LOW_POWER_RESET;`
  - `Core/Inc/User_Define.h:225: RESET_CAUSE_LOW_POWER_RESET,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RESET_CAUSE_WINDOW_WATCHDOG_RESET

- **종류**: enum `reset_cause_e` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/main.c:696: reset_cause = RESET_CAUSE_WINDOW_WATCHDOG_RESET;`
  - `Core/Inc/User_Define.h:226: RESET_CAUSE_WINDOW_WATCHDOG_RESET,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RESET_CAUSE_INDEPENDENT_WATCHDOG_RESET

- **종류**: enum `reset_cause_e` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/main.c:700: reset_cause = RESET_CAUSE_INDEPENDENT_WATCHDOG_RESET;`
  - `Core/Inc/User_Define.h:227: RESET_CAUSE_INDEPENDENT_WATCHDOG_RESET,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RESET_CAUSE_SOFTWARE_RESET

- **종류**: enum `reset_cause_e` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/main.c:706: reset_cause = RESET_CAUSE_SOFTWARE_RESET;`
  - `Core/Inc/User_Define.h:228: RESET_CAUSE_SOFTWARE_RESET,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RESET_CAUSE_POWER_ON_POWER_DOWN_RESET

- **종류**: enum `reset_cause_e` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/main.c:710: reset_cause = RESET_CAUSE_POWER_ON_POWER_DOWN_RESET;`
  - `Core/Inc/User_Define.h:229: RESET_CAUSE_POWER_ON_POWER_DOWN_RESET,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RESET_CAUSE_EXTERNAL_RESET_PIN_RESET

- **종류**: enum `reset_cause_e` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/main.c:714: reset_cause = RESET_CAUSE_EXTERNAL_RESET_PIN_RESET;`
  - `Core/Inc/User_Define.h:230: RESET_CAUSE_EXTERNAL_RESET_PIN_RESET,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RESET_CAUSE_BROWNOUT_RESET

- **종류**: enum `reset_cause_e` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/main.c:721: reset_cause = RESET_CAUSE_BROWNOUT_RESET;`
  - `Core/Inc/User_Define.h:231: RESET_CAUSE_BROWNOUT_RESET,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_1

- **종류**: enum `enumDEBUG_STR` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:116: m_TestStatus.St[DEBUG_STR_1] = m_McuTestSt.RS232_RecvCnt;`
  - `Core/Src/alarm.c:21: if ((nIndex >= DEBUG_STR_1) && (nIndex <= DEBUG_STR_32))`
  - `Core/Src/alarm.c:33: if ((nIndex >= DEBUG_STR_1) && (nIndex <= DEBUG_STR_32))`
  - `Core/Src/dev_SRM.c:37972: m_TestStatus.St[DEBUG_STR_1] = (INT32S)(t[0] * 1000);`
  - `Core/Src/dev_SRM.c:38242: m_TestStatus.St[DEBUG_STR_1] = (INT32S)(t[0] * 1000);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_2

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:117: m_TestStatus.St[DEBUG_STR_2] = m_McuTestSt.RS485_P1_Enable;`
  - `Core/Src/dev_SRM.c:37973: m_TestStatus.St[DEBUG_STR_2] = (INT32S)(t[1] * 1000);`
  - `Core/Src/dev_SRM.c:38243: m_TestStatus.St[DEBUG_STR_2] = (INT32S)(t[1] * 1000);`
  - `Core/Src/dev_SRM.c:38492: m_TestStatus.St[DEBUG_STR_2] = (INT32S)(t[1] * 1000);`
  - `Core/Src/dev_SRM.c:39350: m_TestStatus.St[DEBUG_STR_2] = (INT32S)(t[1] * 1000);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_3

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:118: m_TestStatus.St[DEBUG_STR_3] = m_McuTestSt.RS485_P1_RecvCnt;`
  - `Core/Src/dev_SRM.c:37974: m_TestStatus.St[DEBUG_STR_3] = (INT32S)(t[2] * 1000);`
  - `Core/Src/dev_SRM.c:38244: m_TestStatus.St[DEBUG_STR_3] = (INT32S)(t[2] * 1000);`
  - `Core/Src/dev_SRM.c:38493: m_TestStatus.St[DEBUG_STR_3] = (INT32S)(t[2] * 1000);`
  - `Core/Src/dev_SRM.c:39351: m_TestStatus.St[DEBUG_STR_3] = (INT32S)(t[2] * 1000);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_4

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:119: m_TestStatus.St[DEBUG_STR_4] = m_McuTestSt.RS485_P2_Enable;`
  - `Core/Src/dev_SRM.c:37975: m_TestStatus.St[DEBUG_STR_4] = (INT32S)(t[3] * 1000);`
  - `Core/Src/dev_SRM.c:38245: m_TestStatus.St[DEBUG_STR_4] = (INT32S)(t[3] * 1000);`
  - `Core/Src/dev_SRM.c:38494: m_TestStatus.St[DEBUG_STR_4] = (INT32S)(t[3] * 1000);`
  - `Core/Src/dev_SRM.c:39352: m_TestStatus.St[DEBUG_STR_4] = (INT32S)(t[3] * 1000);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_5

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:120: m_TestStatus.St[DEBUG_STR_5] = m_McuTestSt.RS485_P2_RecvCnt;`
  - `Core/Src/dev_SRM.c:37976: m_TestStatus.St[DEBUG_STR_5] = (INT32S)(t[4] * 1000);`
  - `Core/Src/dev_SRM.c:38246: m_TestStatus.St[DEBUG_STR_5] = (INT32S)(t[4] * 1000);`
  - `Core/Src/dev_SRM.c:38495: m_TestStatus.St[DEBUG_STR_5] = (INT32S)(t[4] * 1000);`
  - `Core/Src/dev_SRM.c:39353: m_TestStatus.St[DEBUG_STR_5] = (INT32S)(t[4] * 1000);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_6

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:121: m_TestStatus.St[DEBUG_STR_6] = m_McuTestSt.RS422_P1_Enable;`
  - `Core/Src/dev_SRM.c:37977: m_TestStatus.St[DEBUG_STR_6] = (INT32S)(t[5] * 1000);`
  - `Core/Src/dev_SRM.c:38247: m_TestStatus.St[DEBUG_STR_6] = (INT32S)(t[5] * 1000);`
  - `Core/Src/dev_SRM.c:38496: m_TestStatus.St[DEBUG_STR_6] = (INT32S)(t[5] * 1000);`
  - `Core/Src/dev_SRM.c:39354: m_TestStatus.St[DEBUG_STR_6] = (INT32S)(t[5] * 1000);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_7

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:122: m_TestStatus.St[DEBUG_STR_7] = m_McuTestSt.RS422_P1_RecvCnt;`
  - `Core/Src/dev_SRM.c:37978: m_TestStatus.St[DEBUG_STR_7] = (INT32S)(t[6] * 1000);`
  - `Core/Src/dev_SRM.c:38248: m_TestStatus.St[DEBUG_STR_7] = (INT32S)(t[6] * 1000);`
  - `Core/Src/dev_SRM.c:38497: m_TestStatus.St[DEBUG_STR_7] = (INT32S)(t[6] * 1000);`
  - `Core/Src/dev_SRM.c:39355: m_TestStatus.St[DEBUG_STR_7] = (INT32S)(t[6] * 1000);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_8

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:123: m_TestStatus.St[DEBUG_STR_8] = m_McuTestSt.RS422_P2_Enable;`
  - `Core/Src/dev_SRM.c:37979: m_TestStatus.St[DEBUG_STR_8] = (INT32S)(t[7] * 1000);`
  - `Core/Src/dev_SRM.c:38249: m_TestStatus.St[DEBUG_STR_8] = (INT32S)(t[7] * 1000);`
  - `Core/Src/dev_SRM.c:38498: m_TestStatus.St[DEBUG_STR_8] = (INT32S)(t[7] * 1000);`
  - `Core/Src/dev_SRM.c:39356: m_TestStatus.St[DEBUG_STR_8] = (INT32S)(t[7] * 1000);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_9

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:124: m_TestStatus.St[DEBUG_STR_9] = m_McuTestSt.RS422_P2_RecvCnt;`
  - `Core/Src/dev_SRM.c:37981: m_TestStatus.St[DEBUG_STR_9] = (INT32S)v[0];`
  - `Core/Src/dev_SRM.c:38251: m_TestStatus.St[DEBUG_STR_9] = (INT32S)((v[0] * 60) / 1000);		// mm/s -> m/min`
  - `Core/Src/dev_SRM.c:38500: m_TestStatus.St[DEBUG_STR_9] = (INT32S)v[0];		// mm/s`
  - `Core/Src/dev_SRM.c:38821: m_TestStatus.St[DEBUG_STR_9] = (INT32S)(t[0] * 1000);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_10

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:125: m_TestStatus.St[DEBUG_STR_10] = m_McuTestSt.CAN1_RecvCnt;`
  - `Core/Src/dev_SRM.c:9293: m_TestStatus.St[DEBUG_STR_10] = m_ExtSEnv2.ForkDrive.OriginOffset_FCL;`
  - `Core/Src/dev_SRM.c:37590: m_TestStatus.St[DEBUG_STR_10] = s_RunStep;`
  - `Core/Src/dev_SRM.c:37982: m_TestStatus.St[DEBUG_STR_10] = (INT32S)v[1];`
  - `Core/Src/dev_SRM.c:38252: m_TestStatus.St[DEBUG_STR_10] = (INT32S)((v[1] * 60) / 1000);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_11

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:126: m_TestStatus.St[DEBUG_STR_11] = m_McuTestSt.CAN2_RecvCnt;`
  - `Core/Src/dev_SRM.c:9294: m_TestStatus.St[DEBUG_STR_11] = m_ExtSEnv2.ForkDrive.OriginOffset_FCR;`
  - `Core/Src/dev_SRM.c:34181: m_TestStatus.St[DEBUG_STR_11] = m_Manual_Run_Step[nInvertor];`
  - `Core/Src/dev_SRM.c:37591: m_TestStatus.St[DEBUG_STR_11] = s_ReadIndex;`
  - `Core/Src/dev_SRM.c:37983: m_TestStatus.St[DEBUG_STR_11] = (INT32S)v[2];`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_12

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:127: m_TestStatus.St[DEBUG_STR_12] = m_McuTestSt.EtherNet1_RecvCnt;`
  - `Core/Src/dev_SRM.c:9295: m_TestStatus.St[DEBUG_STR_12] = m_ExtSEnv2.ForkDrive.OriginSensor;`
  - `Core/Src/dev_SRM.c:16273: m_TestStatus.St[DEBUG_STR_12] = nReadOffset.Bay_No;`
  - `Core/Src/dev_SRM.c:34182: m_TestStatus.St[DEBUG_STR_12] = m_Manual_Run_Mode[nInvertor];`
  - `Core/Src/dev_SRM.c:37592: m_TestStatus.St[DEBUG_STR_12] = m_pgmEnv.InvParamCtr.Mode;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_13

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:128: m_TestStatus.St[DEBUG_STR_13] = m_McuTestSt.EtherNet2_RecvCnt;`
  - `Core/Src/dev_SRM.c:9296: m_TestStatus.St[DEBUG_STR_13] = nDef_Fork_Origin_Offset;`
  - `Core/Src/dev_SRM.c:16274: m_TestStatus.St[DEBUG_STR_13] = nReadOffset.Lv_No;`
  - `Core/Src/dev_SRM.c:34183: m_TestStatus.St[DEBUG_STR_13] = nMoveRange_Upper;`
  - `Core/Src/dev_SRM.c:37598: m_TestStatus.St[DEBUG_STR_13] |= cbits32[i];`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_14

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:129: m_TestStatus.St[DEBUG_STR_14] = m_McuTestSt.EtherCAT_Test;`
  - `Core/Src/dev_SRM.c:9297: m_TestStatus.St[DEBUG_STR_14] = m_SRM_Sub_RunStep_0;`
  - `Core/Src/dev_SRM.c:16275: m_TestStatus.St[DEBUG_STR_14] = nReadOffset.Trav_Left;`
  - `Core/Src/dev_SRM.c:34184: m_TestStatus.St[DEBUG_STR_14] = nMoveRange_Lower;`
  - `Core/Src/dev_SRM.c:37607: m_TestStatus.St[DEBUG_STR_14] |= cbits32[i];`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_15

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:130: m_TestStatus.St[DEBUG_STR_15] = m_McuTestSt.SSI_Position;`
  - `Core/Src/dev_SRM.c:9298: m_TestStatus.St[DEBUG_STR_15] = s_ForkOriginPos;`
  - `Core/Src/dev_SRM.c:16276: m_TestStatus.St[DEBUG_STR_15] = nReadOffset.Trav_Right;`
  - `Core/Src/dev_SRM.c:34185: m_TestStatus.St[DEBUG_STR_15] = s_StopReason;`
  - `Core/Src/dev_SRM.c:37987: m_TestStatus.St[DEBUG_STR_15] = (INT32S)v[6];`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_16

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:131: m_TestStatus.St[DEBUG_STR_16] = (INT32S)m_McuTestSt.Encoder_In;`
  - `Core/Src/dev_SRM.c:16277: m_TestStatus.St[DEBUG_STR_16] = nReadOffset.Lift_Left;`
  - `Core/Src/dev_SRM.c:34186: m_TestStatus.St[DEBUG_STR_16] = s_MoveWard;`
  - `Core/Src/dev_SRM.c:37988: m_TestStatus.St[DEBUG_STR_16] = (INT32S)v[7];`
  - `Core/Src/dev_SRM.c:38258: m_TestStatus.St[DEBUG_STR_16] = (INT32S)((v[7] * 60) / 1000);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_17

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:132: m_TestStatus.St[DEBUG_STR_17] = m_McuTestSt.PTO_Output;`
  - `Core/Src/dev_SRM.c:16278: m_TestStatus.St[DEBUG_STR_17] = nReadOffset.Lift_Right;`
  - `Core/Src/dev_SRM.c:34187: m_TestStatus.St[DEBUG_STR_17] = s_ActWard;`
  - `Core/Src/dev_SRM.c:37999: m_TestStatus.St[DEBUG_STR_17] = (INT32S)s[0];`
  - `Core/Src/dev_SRM.c:38260: m_TestStatus.St[DEBUG_STR_17] = (INT32S)s[0];`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_18

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:133: m_TestStatus.St[DEBUG_STR_18] = m_McuTestSt.DOSt;`
  - `Core/Src/dev_SRM.c:34188: m_TestStatus.St[DEBUG_STR_18] = s_ActVelocity;`
  - `Core/Src/dev_SRM.c:38000: m_TestStatus.St[DEBUG_STR_18] = (INT32S)s[1];`
  - `Core/Src/dev_SRM.c:38261: m_TestStatus.St[DEBUG_STR_18] = (INT32S)s[1];`
  - `Core/Src/dev_SRM.c:38519: m_TestStatus.St[DEBUG_STR_18] = (INT32S)s[1];`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_19

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:134: m_TestStatus.St[DEBUG_STR_19] = m_McuTestSt.DISt;`
  - `Core/Src/dev_SRM.c:34189: m_TestStatus.St[DEBUG_STR_19] = s_StopCenterFlag;`
  - `Core/Src/dev_SRM.c:38001: m_TestStatus.St[DEBUG_STR_19] = (INT32S)s[2];`
  - `Core/Src/dev_SRM.c:38262: m_TestStatus.St[DEBUG_STR_19] = (INT32S)s[2];`
  - `Core/Src/dev_SRM.c:38520: m_TestStatus.St[DEBUG_STR_19] = (INT32S)s[2];`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_20

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:136: m_TestStatus.St[DEBUG_STR_20] = m_McuTestSt.USB_Test_Enable;`
  - `Core/Src/dev_SRM.c:6039: Set_TestStatus(DEBUG_STR_20, s_TransCnt);`
  - `Core/Src/dev_SRM.c:6103: Set_TestStatus(DEBUG_STR_20, s_TransCnt);`
  - `Core/Src/dev_SRM.c:6164: Set_TestStatus(DEBUG_STR_20, s_TransCnt);`
  - `Core/Src/dev_SRM.c:8707: m_TestStatus.St[DEBUG_STR_20] = m_SRM_Sub_RunStep_0;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_21

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:137: m_TestStatus.St[DEBUG_STR_21] = m_McuTestSt.USB_Test;`
  - `Core/Src/dev_SRM.c:5363: Set_TestStatus(DEBUG_STR_21, s_RecvCnt);`
  - `Core/Src/dev_SRM.c:5517: Set_TestStatus(DEBUG_STR_21, s_RecvCnt);`
  - `Core/Src/dev_SRM.c:5683: Set_TestStatus(DEBUG_STR_21, s_RecvCnt);`
  - `Core/Src/dev_SRM.c:8708: m_TestStatus.St[DEBUG_STR_21] = s_SenseHomePosDiff;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_22

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6041: Set_TestStatus(DEBUG_STR_22, m_SRM_PO_Type_1.Travel.ControlWord.W);`
  - `Core/Src/dev_SRM.c:6105: Set_TestStatus(DEBUG_STR_22, m_SRM_PO_Type_2.Travel.ControlWord.W);`
  - `Core/Src/dev_SRM.c:6166: Set_TestStatus(DEBUG_STR_22, m_SRM_PO_Type_3.Travel.ControlWord.W);`
  - `Core/Src/dev_SRM.c:8709: m_TestStatus.St[DEBUG_STR_22] = s_RetryCnt;`
  - `Core/Src/dev_SRM.c:25298: m_TestStatus.St[DEBUG_STR_22] = flag;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_23

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:5365: Set_TestStatus(DEBUG_STR_23, m_SRM_PI_Type_1.Travel.StatusWord.W);`
  - `Core/Src/dev_SRM.c:5519: Set_TestStatus(DEBUG_STR_23, m_SRM_PI_Type_2.Travel.StatusWord.W);`
  - `Core/Src/dev_SRM.c:5685: Set_TestStatus(DEBUG_STR_23, m_SRM_PI_Type_3.Travel.StatusWord.W);`
  - `Core/Src/dev_SRM.c:8710: m_TestStatus.St[DEBUG_STR_23] = getCalcTimer1ms(s_RunTimer);`
  - `Core/Src/dev_SRM.c:9302: m_TestStatus.St[DEBUG_STR_23] = m_Enx_TxPDO.Ch1_Present_Value;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_24

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6042: Set_TestStatus(DEBUG_STR_24, m_SRM_PO_Type_1.Hoist.ControlWord.W);`
  - `Core/Src/dev_SRM.c:6106: Set_TestStatus(DEBUG_STR_24, m_SRM_PO_Type_2.Hoist.ControlWord.W);`
  - `Core/Src/dev_SRM.c:6167: Set_TestStatus(DEBUG_STR_24, m_SRM_PO_Type_3.Hoist.ControlWord.W);`
  - `Core/Src/dev_SRM.c:8711: m_TestStatus.St[DEBUG_STR_24] = s_Over_time_Flag;`
  - `Core/Src/dev_SRM.c:9303: m_TestStatus.St[DEBUG_STR_24] = m_Enx_RxPDO.Ch1_Preset_Value;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_25

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:5366: Set_TestStatus(DEBUG_STR_25, m_SRM_PI_Type_1.Hoist.StatusWord.W);`
  - `Core/Src/dev_SRM.c:5520: Set_TestStatus(DEBUG_STR_25, m_SRM_PI_Type_2.Hoist.StatusWord.W);`
  - `Core/Src/dev_SRM.c:5686: Set_TestStatus(DEBUG_STR_25, m_SRM_PI_Type_3.Hoist.StatusWord.W);`
  - `Core/Src/dev_SRM.c:8712: m_TestStatus.St[DEBUG_STR_25] = getCalcTimer1ms(s_Over_timer);`
  - `Core/Src/dev_SRM.c:9304: m_TestStatus.St[DEBUG_STR_25] = m_Enx_TxPDO.Ch1_Counter_Status;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_26

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6043: Set_TestStatus(DEBUG_STR_26, m_SRM_PO_Type_1.Fork.ControlWord.W);`
  - `Core/Src/dev_SRM.c:6107: Set_TestStatus(DEBUG_STR_26, m_SRM_PO_Type_2.Fork.ControlWord.W);`
  - `Core/Src/dev_SRM.c:6168: Set_TestStatus(DEBUG_STR_26, m_SRM_PO_Type_3.Fork.ControlWord.W);`
  - `Core/Src/dev_SRM.c:9305: m_TestStatus.St[DEBUG_STR_26] = m_Enx_RxPDO.Ch1_Switch0;`
  - `Core/Src/dev_SRM.c:25302: m_TestStatus.St[DEBUG_STR_26] = start_pos;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_27

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:5367: Set_TestStatus(DEBUG_STR_27, m_SRM_PI_Type_1.Fork.StatusWord.W);`
  - `Core/Src/dev_SRM.c:5521: Set_TestStatus(DEBUG_STR_27, m_SRM_PI_Type_2.Fork.StatusWord.W);`
  - `Core/Src/dev_SRM.c:5687: Set_TestStatus(DEBUG_STR_27, m_SRM_PI_Type_3.Fork.StatusWord.W);`
  - `Core/Src/dev_SRM.c:25303: m_TestStatus.St[DEBUG_STR_27] = end_pos;`
  - `Core/Src/dev_SRM.c:25930: m_TestStatus.St[DEBUG_STR_27] = end_pos;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_28

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:5369: Set_TestStatus(DEBUG_STR_28, m_SRM_PI_Type_1.Travel.StatusCode.W);`
  - `Core/Src/dev_SRM.c:5373: Set_TestStatus(DEBUG_STR_28, m_SRM_PI_Type1.Travel.StatusCode.B.StatusCode);`
  - `Core/Src/dev_SRM.c:5524: Set_TestStatus(DEBUG_STR_28, m_SRM_PO_Type_2.Travel.Operating_mode);`
  - `Core/Src/dev_SRM.c:5530: Set_TestStatus(DEBUG_STR_28, m_SRM_PI_Type_2.Travel.StatusCode.W);`
  - `Core/Src/dev_SRM.c:5690: Set_TestStatus(DEBUG_STR_28, m_SRM_PO_Type_3.Travel.Operating_mode);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_29

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:5370: Set_TestStatus(DEBUG_STR_29, m_SRM_PI_Type_1.Hoist.StatusCode.W);`
  - `Core/Src/dev_SRM.c:5374: Set_TestStatus(DEBUG_STR_29, m_SRM_PI_Type1.Hoist.StatusCode.B.StatusCode);`
  - `Core/Src/dev_SRM.c:5525: Set_TestStatus(DEBUG_STR_29, m_SRM_PO_Type_2.Travel.TargetPosition);`
  - `Core/Src/dev_SRM.c:5531: Set_TestStatus(DEBUG_STR_29, m_SRM_PI_Type_2.Hoist.StatusCode.W);`
  - `Core/Src/dev_SRM.c:5691: Set_TestStatus(DEBUG_STR_29, m_SRM_PO_Type_3.Travel.TargetPosition);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_30

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:5371: Set_TestStatus(DEBUG_STR_30, m_SRM_PI_Type_1.Fork.StatusCode.W);`
  - `Core/Src/dev_SRM.c:5375: Set_TestStatus(DEBUG_STR_30, m_SRM_PI_Type1.Fork.StatusCode.B.StatusCode);`
  - `Core/Src/dev_SRM.c:5526: Set_TestStatus(DEBUG_STR_30, m_SRM_PI_Type_2.Travel.StatusCode.B.StatusCode);`
  - `Core/Src/dev_SRM.c:5532: Set_TestStatus(DEBUG_STR_30, m_SRM_PI_Type_2.Fork.StatusCode.W);`
  - `Core/Src/dev_SRM.c:5692: Set_TestStatus(DEBUG_STR_30, m_SRM_PI_Type_3.Travel.StatusCode.B.StatusCode);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_31

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:5527: Set_TestStatus(DEBUG_STR_31, m_SRM_PI_Type_2.Travel.Operating_mode);`
  - `Core/Src/dev_SRM.c:5693: Set_TestStatus(DEBUG_STR_31, m_SRM_PI_Type_3.Travel.Operating_mode);`
  - `Core/Src/dev_SRM.c:38845: m_TestStatus.St[DEBUG_STR_31] = (INT32S)s[6];`
  - `Core/Src/dev_SRM.c:45774: m_TestStatus.St[DEBUG_STR_31] = m_WorkData[0].TargetPos.Level_ID;`
  - `Core/Inc/User_Define.h:265: DEBUG_STR_31,		//`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_32

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/alarm.c:21: if ((nIndex >= DEBUG_STR_1) && (nIndex <= DEBUG_STR_32))`
  - `Core/Src/alarm.c:33: if ((nIndex >= DEBUG_STR_1) && (nIndex <= DEBUG_STR_32))`
  - `Core/Src/dev_SRM.c:38846: m_TestStatus.St[DEBUG_STR_32] = (INT32S)s[7];`
  - `Core/Inc/User_Define.h:266: DEBUG_STR_32,		//`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_33

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/alarm.c:25: else if ((nIndex >= DEBUG_STR_33) && (nIndex <= DEBUG_STR_64))`
  - `Core/Src/alarm.c:27: m_TestStatus.St2[nIndex - DEBUG_STR_33] = nData;`
  - `Core/Src/alarm.c:37: else if ((nIndex >= DEBUG_STR_33) && (nIndex <= DEBUG_STR_64))`
  - `Core/Src/alarm.c:39: m_TestStatus.St2[nIndex - DEBUG_STR_33] = 0;`
  - `Core/Src/com_tml.c:1919: Set_TestStatus(DEBUG_STR_33, nID);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_34

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:1920: Set_TestStatus(DEBUG_STR_34, nMode);`
  - `Core/Src/com_tml.c:2435: Set_TestStatus(DEBUG_STR_34, pCmd->OperationFlag);`
  - `Core/Src/dev_SRM.c:22575: Set_TestStatus(DEBUG_STR_34, nAction);`
  - `Core/Src/dev_SRM.c:23098: Set_TestStatus(DEBUG_STR_34, nAction);`
  - `Core/Src/dev_SRM.c:24084: Set_TestStatus(DEBUG_STR_34, nAction);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_35

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:1929: Set_TestStatus(DEBUG_STR_35, nID);`
  - `Core/Src/com_tml.c:1949: Set_TestStatus(DEBUG_STR_35, nID - OUT_FK1_RESET);`
  - `Core/Src/com_tml.c:2436: Set_TestStatus(DEBUG_STR_35, pCmd->OrderCode);`
  - `Core/Src/dev_SRM.c:22576: Set_TestStatus(DEBUG_STR_35, nStart_pos);`
  - `Core/Src/dev_SRM.c:23099: Set_TestStatus(DEBUG_STR_35, start_pos);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_36

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:1930: Set_TestStatus(DEBUG_STR_36, nByteIdx);`
  - `Core/Src/com_tml.c:1950: Set_TestStatus(DEBUG_STR_36, nByteIdx);`
  - `Core/Src/com_tml.c:2437: Set_TestStatus(DEBUG_STR_36, pCmd->Fork[0].WorkNum);`
  - `Core/Src/dev_SRM.c:22577: Set_TestStatus(DEBUG_STR_36, nEnd_pos);`
  - `Core/Src/dev_SRM.c:23100: Set_TestStatus(DEBUG_STR_36, end_pos);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_37

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:1931: Set_TestStatus(DEBUG_STR_37, nBitIndex);`
  - `Core/Src/com_tml.c:1951: Set_TestStatus(DEBUG_STR_37, nBitIndex);`
  - `Core/Src/com_tml.c:2438: Set_TestStatus(DEBUG_STR_37, pCmd->Fork[0].FromCell.Station);`
  - `Core/Src/dev_SRM.c:3239: Set_TestStatus(DEBUG_STR_37, 2);`
  - `Core/Src/dev_SRM.c:3313: Set_TestStatus(DEBUG_STR_37, 1);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_38

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2439: Set_TestStatus(DEBUG_STR_38, pCmd->Fork[0].FromCell.Row_ID);`
  - `Core/Src/dev_SRM.c:3285: Set_TestStatus(DEBUG_STR_38, 1);`
  - `Core/Src/dev_SRM.c:3295: Set_TestStatus(DEBUG_STR_38, 2);`
  - `Core/Src/dev_SRM.c:3305: Set_TestStatus(DEBUG_STR_38, 3);`
  - `Core/Src/dev_SRM.c:22579: Set_TestStatus(DEBUG_STR_38, m_St.PosFork1.Bay_No);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_39

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2440: Set_TestStatus(DEBUG_STR_39, pCmd->Fork[0].FromCell.Bay_ID);`
  - `Core/Src/dev_SRM.c:3232: Set_TestStatus(DEBUG_STR_39, nAct);`
  - `Core/Src/dev_SRM.c:22580: Set_TestStatus(DEBUG_STR_39, m_St.PosFork1.Level_No);`
  - `Core/Src/dev_SRM.c:23103: Set_TestStatus(DEBUG_STR_39, m_St.PosFork1.Level_No);`
  - `Core/Src/dev_SRM.c:24089: Set_TestStatus(DEBUG_STR_39, m_St.PosFork1.Level_No);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_40

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2441: Set_TestStatus(DEBUG_STR_40, pCmd->Fork[0].FromCell.Level_ID);`
  - `Core/Src/dev_SRM.c:3233: Set_TestStatus(DEBUG_STR_40, VelType);`
  - `Core/Src/dev_SRM.c:22581: Set_TestStatus(DEBUG_STR_40, nTravCom);`
  - `Core/Src/dev_SRM.c:23104: Set_TestStatus(DEBUG_STR_40, nTravCom);`
  - `Core/Src/dev_SRM.c:24090: Set_TestStatus(DEBUG_STR_40, nTravCom);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_41

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2442: Set_TestStatus(DEBUG_STR_41, pCmd->Fork[0].ToCell.Station);`
  - `Core/Src/dev_SRM.c:6601: Set_TestStatus(DEBUG_STR_41, ++s_RecvCnt[0]);`
  - `Core/Src/dev_SRM.c:22582: Set_TestStatus(DEBUG_STR_41, nPosition);`
  - `Core/Src/dev_SRM.c:23105: Set_TestStatus(DEBUG_STR_41, nPosition);`
  - `Core/Src/dev_SRM.c:24091: Set_TestStatus(DEBUG_STR_41, nPosition);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_42

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2443: Set_TestStatus(DEBUG_STR_42, pCmd->Fork[0].ToCell.Row_ID);`
  - `Core/Src/dev_SRM.c:6579: Set_TestStatus(DEBUG_STR_42, ModbusRxPkt.FC03Resp.ByteCount);`
  - `Core/Src/dev_SRM.c:22583: Set_TestStatus(DEBUG_STR_42, nOffset);`
  - `Core/Src/dev_SRM.c:23106: Set_TestStatus(DEBUG_STR_42, nOffset);`
  - `Core/Src/dev_SRM.c:24092: Set_TestStatus(DEBUG_STR_42, nOffset);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_43

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2444: Set_TestStatus(DEBUG_STR_43, pCmd->Fork[0].ToCell.Bay_ID);`
  - `Core/Src/dev_SRM.c:6602: Set_TestStatus(DEBUG_STR_43, ++s_RecvCnt[7]);`
  - `Core/Src/dev_SRM.c:22584: Set_TestStatus(DEBUG_STR_43, nVelocity_type);`
  - `Core/Src/dev_SRM.c:23107: Set_TestStatus(DEBUG_STR_43, nVelocity_type);`
  - `Core/Src/dev_SRM.c:24093: Set_TestStatus(DEBUG_STR_43, nVelocity_type);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_44

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2445: Set_TestStatus(DEBUG_STR_44, pCmd->Fork[0].ToCell.Level_ID);`
  - `Core/Src/dev_SRM.c:6586: Set_TestStatus(DEBUG_STR_44, ModbusRxPkt.FC03Resp.ByteCount);`
  - `Core/Src/dev_SRM.c:23108: Set_TestStatus(DEBUG_STR_44, nTo_Bay_No);`
  - `Core/Src/dev_SRM.c:24094: Set_TestStatus(DEBUG_STR_44, nTo_Bay_No);`
  - `Core/Src/dev_SRM.c:24724: Set_TestStatus(DEBUG_STR_44, nTo_Bay_No);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_45

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:23109: Set_TestStatus(DEBUG_STR_45, nTo_Bay_InPos);`
  - `Core/Src/dev_SRM.c:24095: Set_TestStatus(DEBUG_STR_45, nTo_Bay_InPos);`
  - `Core/Src/dev_SRM.c:24725: Set_TestStatus(DEBUG_STR_45, nTo_Bay_InPos);`
  - `Core/Src/dev_SRM.c:42945: Set_TestStatus(DEBUG_STR_45, s_Creep_Depth);`
  - `Core/Src/dev_SRM.c:45067: Set_TestStatus(DEBUG_STR_45, m_St.ForkWork[0].From_Cell_Fork.Row_ID);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_46

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:727: Set_TestStatus(DEBUG_STR_46, control_word);`
  - `Core/Src/dev_SRM.c:6666: Set_TestStatus(DEBUG_STR_46, s_RecvCnt[1]);`
  - `Core/Src/dev_SRM.c:24610: Set_TestStatus(DEBUG_STR_46, nPosition);`
  - `Core/Src/dev_SRM.c:25282: Set_TestStatus(DEBUG_STR_46, start_pos);`
  - `Core/Src/dev_SRM.c:26681: Set_TestStatus(DEBUG_STR_46, start_pos);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_47

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:728: Set_TestStatus(DEBUG_STR_47, position);`
  - `Core/Src/dev_SRM.c:24643: Set_TestStatus(DEBUG_STR_47, nOffset);`
  - `Core/Src/dev_SRM.c:25283: Set_TestStatus(DEBUG_STR_47, end_pos);`
  - `Core/Src/dev_SRM.c:26682: Set_TestStatus(DEBUG_STR_47, end_pos);`
  - `Core/Src/dev_SRM.c:28516: Set_TestStatus(DEBUG_STR_47, end_pos);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_48

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:729: Set_TestStatus(DEBUG_STR_48, vel);`
  - `Core/Src/dev_SRM.c:6667: Set_TestStatus(DEBUG_STR_48, s_RecvCnt[0]);`
  - `Core/Src/dev_SRM.c:12699: Set_TestStatus(DEBUG_STR_48, s_Force_ForkOut_Enable);`
  - `Core/Src/dev_SRM.c:13687: Set_TestStatus(DEBUG_STR_48, s_Force_ForkOut_Enable);`
  - `Core/Src/dev_SRM.c:14673: Set_TestStatus(DEBUG_STR_48, s_Force_ForkOut_Enable);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

