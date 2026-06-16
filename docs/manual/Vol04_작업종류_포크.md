# Vol.04 — WORK_*

> 생성일: 2026-06-16 | MX SRM App Ver 4.4 | 소스 미수정

ForkAct.

---

### WORK_MOVE_ONLY

- **종류**: enum `enumFORK_ACTION` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:44977: if (ForkAct == WORK_MOVE_ONLY)`
  - `Core/Src/dev_SRM.c:45013: if (ForkAct == WORK_MOVE_ONLY)`
  - `Core/Src/dev_SRM.c:45057: if (ForkAct == WORK_MOVE_ONLY)`
  - `Core/Src/dev_SRM.c:45141: if (ForkAct == WORK_MOVE_ONLY)`
  - `Core/Src/dev_SRM.c:45560: Store_Work_Data_Fix(to_tpos, to_lpos, WORK_MOVE_ONLY, to_is_sta, tp \`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### WORK_FORK1_GET

- **종류**: enum `enumFORK_ACTION` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: #1 적재
- **용도(읽는 법)**: 헤더 주석: #1 적재
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:44954: if ((ForkAct == WORK_FORK1_GET) || (ForkAct == WORK_FORK1_PUT))`
  - `Core/Src/dev_SRM.c:44981: else if (ForkAct == WORK_FORK1_GET)`
  - `Core/Src/dev_SRM.c:45026: else if (ForkAct == WORK_FORK1_GET)`
  - `Core/Src/dev_SRM.c:45061: else if (ForkAct == WORK_FORK1_GET)`
  - `Core/Src/dev_SRM.c:45125: if ((ForkAct == WORK_FORK1_GET) || (ForkAct == WORK_FORK1_PUT))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### WORK_FORK2_GET

- **종류**: enum `enumFORK_ACTION` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: #2 적재
- **용도(읽는 법)**: 헤더 주석: #2 적재
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1779: WORK_FORK2_GET,			// #2 적재`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### WORK_FORKB_GET

- **종류**: enum `enumFORK_ACTION` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: #1, #2 적재
- **용도(읽는 법)**: 헤더 주석: #1, #2 적재
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1780: WORK_FORKB_GET,			// #1, #2 적재`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### WORK_FORK1_PUT

- **종류**: enum `enumFORK_ACTION` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: #1 이재
- **용도(읽는 법)**: 헤더 주석: #1 이재
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:44954: if ((ForkAct == WORK_FORK1_GET) || (ForkAct == WORK_FORK1_PUT))`
  - `Core/Src/dev_SRM.c:44985: else if (ForkAct == WORK_FORK1_PUT)`
  - `Core/Src/dev_SRM.c:45030: else if (ForkAct == WORK_FORK1_PUT)`
  - `Core/Src/dev_SRM.c:45072: else if (ForkAct == WORK_FORK1_PUT)`
  - `Core/Src/dev_SRM.c:45125: if ((ForkAct == WORK_FORK1_GET) || (ForkAct == WORK_FORK1_PUT))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### WORK_FORK2_PUT

- **종류**: enum `enumFORK_ACTION` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: #2 이재
- **용도(읽는 법)**: 헤더 주석: #2 이재
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1782: WORK_FORK2_PUT,			// #2 이재`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### WORK_FORKB_PUT

- **종류**: enum `enumFORK_ACTION` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: #1, #2 이재
- **용도(읽는 법)**: 헤더 주석: #1, #2 이재
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1783: WORK_FORKB_PUT,			// #1, #2 이재`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### WORK_FORK1_STICKY

- **종류**: enum `enumFORK_ACTION` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:45076: else if (ForkAct == WORK_FORK1_STICKY)`
  - `Core/Src/dev_SRM.c:46665: Store_Work_Data_1(from_tpos[POS_FORK_1], from_lpos[POS_FORK_1], WORK_FORK1_STICKY, from_is_sta[POS_F`
  - `Core/Src/dev_SRM.c:47310: Store_Work_Data_1(from_tpos[0], from_lpos[0], WORK_FORK1_STICKY, from_is_sta[0], &FromPos[0], \`
  - `Core/Src/dev_SRM.c:58927: else if (m_WorkData[s_WorkInx].ForkAct == WORK_FORK1_STICKY) //ììë°ì´í°ì í¬í¬ìíê° ì`
  - `Core/Src/dev_SRM.c:58964: else if (m_WorkData[s_WorkInx].ForkAct == WORK_FORK1_STICKY) //í¬í¬1 ì¤í°í¤ëª¨ëì¼ë`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### WORK_FORKB_TEST

- **종류**: enum `enumFORK_ACTION` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1785: WORK_FORKB_TEST,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

