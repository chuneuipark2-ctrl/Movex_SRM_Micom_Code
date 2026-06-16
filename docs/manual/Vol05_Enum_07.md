# Vol.05 — 기타 Enum (7)

> 생성일: 2026-06-16 | MX SRM App Ver 4.4 | 소스 미수정

기타 enumeration.

---

### LIFT_MOVE_UP

- **종류**: enum `enumLIFT_MOVE_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:48063: nDir = LIFT_MOVE_UP;`
  - `Core/Src/dev_SRM.c:55993: if (m_WorkData[nWorkIdx].DrvData[INV_HOIST].Move_Dir == LIFT_MOVE_UP)`
  - `Core/Src/dev_SRM.c:59266: if (m_WorkData[s_WorkInx].DrvData[INV_HOIST].Move_Dir == LIFT_MOVE_UP)`
  - `Core/Src/dev_SRM.c:60883: if (m_WorkData[s_WorkInx].DrvData[INV_HOIST].Move_Dir == LIFT_MOVE_UP)`
  - `Core/Src/dev_SRM.c:62173: if (m_WorkData[s_WorkInx].DrvData[INV_HOIST].Move_Dir == LIFT_MOVE_UP)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LIFT_MOVE_DOWN

- **종류**: enum `enumLIFT_MOVE_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:48068: nDir = LIFT_MOVE_DOWN;`
  - `Core/Src/dev_SRM.c:56137: else if (m_WorkData[nWorkIdx].DrvData[INV_HOIST].Move_Dir == LIFT_MOVE_DOWN)`
  - `Core/Src/dev_SRM.c:59306: else if (m_WorkData[s_WorkInx].DrvData[INV_HOIST].Move_Dir == LIFT_MOVE_DOWN)`
  - `Core/Src/dev_SRM.c:60887: else if (m_WorkData[s_WorkInx].DrvData[INV_HOIST].Move_Dir == LIFT_MOVE_DOWN)`
  - `Core/Src/dev_SRM.c:62177: else if (m_WorkData[s_WorkInx].DrvData[INV_HOIST].Move_Dir == LIFT_MOVE_DOWN)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### JOG_FORK_APP_STOP

- **종류**: enum `enumFORK_JOG_CONTROL` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:2950: if (nAct == JOG_FORK_APP_STOP)`
  - `Core/Src/dev_SRM.c:3275: case JOG_FORK_APP_STOP:`
  - `Core/Src/dev_SRM.c:3334: if (nAct == JOG_FORK_APP_STOP)`
  - `Core/Src/dev_SRM.c:4523: if (act == JOG_FORK_APP_STOP)`
  - `Core/Src/dev_SRM.c:4559: if (act == JOG_FORK_APP_STOP)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### JOG_FORK_RIGHT

- **종류**: enum `enumFORK_JOG_CONTROL` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:2977: else if (nAct == JOG_FORK_RIGHT)`
  - `Core/Src/dev_SRM.c:3289: case JOG_FORK_RIGHT:`
  - `Core/Src/dev_SRM.c:3361: else if (nAct == JOG_FORK_RIGHT)`
  - `Core/Src/dev_SRM.c:8890: Motor_Manual_Fork1(JOG_FORK_RIGHT, FORK_VEL_ORIGIN);`
  - `Core/Src/dev_SRM.c:8911: Motor_Manual_Fork1(JOG_FORK_RIGHT, FORK_VEL_ORIGIN);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### JOG_FORK_LEFT

- **종류**: enum `enumFORK_JOG_CONTROL` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:3018: else if (nAct == JOG_FORK_LEFT)`
  - `Core/Src/dev_SRM.c:3299: case JOG_FORK_LEFT:`
  - `Core/Src/dev_SRM.c:3402: else if (nAct == JOG_FORK_LEFT)`
  - `Core/Src/dev_SRM.c:8898: Motor_Manual_Fork1(JOG_FORK_LEFT, FORK_VEL_ORIGIN);`
  - `Core/Src/dev_SRM.c:8917: Motor_Manual_Fork1(JOG_FORK_LEFT, FORK_VEL_ORIGIN);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### JOG_FORK_STOP_1

- **종류**: enum `enumFORK_JOG_CONTROL` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:3057: else if (nAct == JOG_FORK_STOP_1)`
  - `Core/Src/dev_SRM.c:3276: case JOG_FORK_STOP_1:`
  - `Core/Src/dev_SRM.c:3441: else if (nAct == JOG_FORK_STOP_1)`
  - `Core/Src/dev_SRM.c:8966: Motor_Manual_Fork1(JOG_FORK_STOP_1, FORK_VEL_ORIGIN);`
  - `Core/Src/dev_SRM.c:9003: Motor_Manual_Fork1(JOG_FORK_STOP_1, FORK_VEL_ORIGIN);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### JOG_FORK_STOP_R

- **종류**: enum `enumFORK_JOG_CONTROL` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 조그 운전중 정지
- **용도(읽는 법)**: 헤더 주석: 조그 운전중 정지
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:3096: else if (nAct == JOG_FORK_STOP_R)`
  - `Core/Src/dev_SRM.c:3277: case JOG_FORK_STOP_R:`
  - `Core/Src/dev_SRM.c:3480: else if (nAct == JOG_FORK_STOP_R)`
  - `Core/Src/dev_SRM.c:34709: Motor_Manual_Fork1(JOG_FORK_STOP_R, FORK_VEL_MAN_M);`
  - `Core/Src/dev_SRM.c:36084: Motor_Manual_Fork1(JOG_FORK_STOP_R, FORK_VEL_MAN_M);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### JOG_FORK_STOP_L

- **종류**: enum `enumFORK_JOG_CONTROL` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 조그 운전중 정지
- **용도(읽는 법)**: 헤더 주석: 조그 운전중 정지
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:3156: else if (nAct == JOG_FORK_STOP_L)`
  - `Core/Src/dev_SRM.c:3278: case JOG_FORK_STOP_L:`
  - `Core/Src/dev_SRM.c:3540: else if (nAct == JOG_FORK_STOP_L)`
  - `Core/Src/dev_SRM.c:34715: Motor_Manual_Fork1(JOG_FORK_STOP_L, FORK_VEL_MAN_M);`
  - `Core/Src/dev_SRM.c:36090: Motor_Manual_Fork1(JOG_FORK_STOP_L, FORK_VEL_MAN_M);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### JOG_FORK_STOP_R_1

- **종류**: enum `enumFORK_JOG_CONTROL` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 조그 운전중 정지, 브레이크 MC 제어타입
- **용도(읽는 법)**: 헤더 주석: 조그 운전중 정지, 브레이크 MC 제어타입
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:3129: else if (nAct == JOG_FORK_STOP_R_1)`
  - `Core/Src/dev_SRM.c:3279: case JOG_FORK_STOP_R_1:`
  - `Core/Src/dev_SRM.c:3513: else if (nAct == JOG_FORK_STOP_R_1)`
  - `Core/Inc/dev_SRM.h:1808: JOG_FORK_STOP_R_1,	// 조그 운전중 정지, 브레이크 MC 제어타입`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### JOG_FORK_STOP_L_1

- **종류**: enum `enumFORK_JOG_CONTROL` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 조그 운전중 정지, 브레이크 MC 제어타입
- **용도(읽는 법)**: 헤더 주석: 조그 운전중 정지, 브레이크 MC 제어타입
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:3188: else if (nAct == JOG_FORK_STOP_L_1)`
  - `Core/Src/dev_SRM.c:3280: case JOG_FORK_STOP_L_1:`
  - `Core/Src/dev_SRM.c:3573: else if (nAct == JOG_FORK_STOP_L_1)`
  - `Core/Inc/dev_SRM.h:1809: JOG_FORK_STOP_L_1,	// 조그 운전중 정지, 브레이크 MC 제어타입`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### JOG_TRAV_STOP_BRAKE_ON

- **종류**: enum `enumTRAV_JOG_CONTROL` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:2281: if (nAct == JOG_TRAV_STOP_BRAKE_ON)`
  - `Core/Src/dev_SRM.c:8367: Motor_Travel_Jog(JOG_TRAV_STOP_BRAKE_ON, TRAV_VEL_ORIGIN);`
  - `Core/Src/dev_SRM.c:31576: Motor_Travel_Jog(JOG_TRAV_STOP_BRAKE_ON, TRAV_VEL_MAN_L);`
  - `Core/Inc/dev_SRM.h:1813: JOG_TRAV_STOP_BRAKE_ON = 0,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### JOG_TRAV_REVERSE

- **종류**: enum `enumTRAV_JOG_CONTROL` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:2321: else if (nAct == JOG_TRAV_REVERSE)`
  - `Core/Src/dev_SRM.c:8152: Motor_Travel_Jog(JOG_TRAV_REVERSE, TRAV_VEL_ORIGIN);`
  - `Core/Src/dev_SRM.c:8179: Motor_Travel_Jog(JOG_TRAV_REVERSE, TRAV_VEL_ORIGIN);`
  - `Core/Src/dev_SRM.c:8252: Motor_Travel_Jog(JOG_TRAV_REVERSE, TRAV_VEL_ORIGIN);`
  - `Core/Src/dev_SRM.c:30984: Motor_Travel_Jog(JOG_TRAV_REVERSE, TRAV_VEL_FORCE);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### JOG_TRAV_FORWARD

- **종류**: enum `enumTRAV_JOG_CONTROL` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:2353: else if (nAct == JOG_TRAV_FORWARD)`
  - `Core/Src/dev_SRM.c:8142: Motor_Travel_Jog(JOG_TRAV_FORWARD, TRAV_VEL_ORIGIN);`
  - `Core/Src/dev_SRM.c:30968: Motor_Travel_Jog(JOG_TRAV_FORWARD, TRAV_VEL_FORCE);`
  - `Core/Src/dev_SRM.c:30976: Motor_Travel_Jog(JOG_TRAV_FORWARD, TRAV_VEL_FORCE);`
  - `Core/Src/dev_SRM.c:31034: Motor_Travel_Jog(JOG_TRAV_FORWARD, TRAV_VEL_FORCE);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### JOG_TRAV_STOP_MOVE

- **종류**: enum `enumTRAV_JOG_CONTROL` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 조그 운전중 정지
- **용도(읽는 법)**: 헤더 주석: 조그 운전중 정지
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:2385: else if (nAct == JOG_TRAV_STOP_MOVE)`
  - `Core/Src/dev_SRM.c:2792: else if (nAct == JOG_TRAV_STOP_MOVE)`
  - `Core/Src/dev_SRM.c:8171: Motor_Travel_Jog(JOG_TRAV_STOP_MOVE, TRAV_VEL_ORIGIN);`
  - `Core/Src/dev_SRM.c:8208: Motor_Travel_Jog(JOG_TRAV_STOP_MOVE, TRAV_VEL_ORIGIN);`
  - `Core/Src/dev_SRM.c:8281: Motor_Travel_Jog(JOG_TRAV_STOP_MOVE, TRAV_VEL_ORIGIN);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### JOG_TRAV_BRAKE

- **종류**: enum `enumTRAV_JOG_CONTROL` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:2418: else if (nAct == JOG_TRAV_BRAKE)`
  - `Core/Inc/dev_SRM.h:1817: JOG_TRAV_BRAKE,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### JOG_LIFT_STOP_BRAKE_ON

- **종류**: enum `enumLIFT_JOG_CONTROL` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:2692: if (nAct == JOG_LIFT_STOP_BRAKE_ON)`
  - `Core/Src/dev_SRM.c:8677: Motor_Lift_Jog(JOG_LIFT_STOP_BRAKE_ON, LIFT_VEL_ORIGIN);`
  - `Core/Src/dev_SRM.c:32615: Motor_Travel_Jog(JOG_LIFT_STOP_BRAKE_ON, TRAV_VEL_MAN_L);`
  - `Core/Inc/dev_SRM.h:1821: JOG_LIFT_STOP_BRAKE_ON = 0,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### JOG_LIFT_DOWN

- **종류**: enum `enumLIFT_JOG_CONTROL` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:2729: else if (nAct == JOG_LIFT_DOWN)`
  - `Core/Src/dev_SRM.c:8499: Motor_Lift_Jog(JOG_LIFT_DOWN, LIFT_VEL_ORIGIN);`
  - `Core/Src/dev_SRM.c:8570: Motor_Lift_Jog(JOG_LIFT_DOWN, LIFT_VEL_ORIGIN);`
  - `Core/Src/dev_SRM.c:32091: Motor_Lift_Jog(JOG_LIFT_DOWN, LIFT_VEL_FORCE);`
  - `Core/Src/dev_SRM.c:32099: Motor_Lift_Jog(JOG_LIFT_DOWN, LIFT_VEL_FORCE);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### JOG_LIFT_UP

- **종류**: enum `enumLIFT_JOG_CONTROL` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:2761: else if (nAct == JOG_LIFT_UP)`
  - `Core/Src/dev_SRM.c:8490: Motor_Lift_Jog(JOG_LIFT_UP, LIFT_VEL_ORIGIN);`
  - `Core/Src/dev_SRM.c:32075: Motor_Lift_Jog(JOG_LIFT_UP, LIFT_VEL_FORCE);`
  - `Core/Src/dev_SRM.c:32083: Motor_Lift_Jog(JOG_LIFT_UP, LIFT_VEL_FORCE);`
  - `Core/Src/dev_SRM.c:32305: Motor_Lift_Jog(JOG_LIFT_UP, LIFT_VEL_FORCE);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### JOG_LIFT_STOP_MOVE

- **종류**: enum `enumLIFT_JOG_CONTROL` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 조그 운전중 정지
- **용도(읽는 법)**: 헤더 주석: 조그 운전중 정지
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:8520: Motor_Lift_Jog(JOG_LIFT_STOP_MOVE, LIFT_VEL_ORIGIN);`
  - `Core/Src/dev_SRM.c:8554: Motor_Lift_Jog(JOG_LIFT_STOP_MOVE, LIFT_VEL_ORIGIN);`
  - `Core/Src/dev_SRM.c:8584: Motor_Lift_Jog(JOG_LIFT_STOP_MOVE, LIFT_VEL_ORIGIN);`
  - `Core/Src/dev_SRM.c:32578: Motor_Lift_Jog(JOG_LIFT_STOP_MOVE, LIFT_VEL_MAN_L);`
  - `Core/Inc/dev_SRM.h:1824: JOG_LIFT_STOP_MOVE,	// 조그 운전중 정지`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### JOG_LIFT_BRAKE

- **종류**: enum `enumLIFT_JOG_CONTROL` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:2824: else if (nAct == JOG_LIFT_BRAKE)`
  - `Core/Inc/dev_SRM.h:1825: JOG_LIFT_BRAKE,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RACK_LEFT

- **종류**: enum `enumRACK_POSITON` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:15647: INT08U nDef_Bay_Start_L[10] = { 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 };		// nCurrent_Bay[RACK_LEFT] = m_pgmE`
  - `Core/Src/dev_SRM.c:15648: INT08U nDef_Lv_Start_L[10] = { 2, 2, 2, 2, 0, 0, 0, 0, 0, 0 };		// nCurrent_Level[RACK_LEFT] = m_pgm`
  - `Core/Src/dev_SRM.c:15885: nCurrent_Bay[RACK_LEFT] = m_pgmEnv.Pos_X_Left - nDef_Bay_Start_L[nSRM_No];		// Bay 1 ~`
  - `Core/Src/dev_SRM.c:15893: if (nCurrent_Bay[RACK_LEFT])`
  - `Core/Src/dev_SRM.c:15897: nCurrent_Level[RACK_LEFT] = 0;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RACK_RIGHT

- **종류**: enum `enumRACK_POSITON` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:15651: INT08U nDef_Lv_Start_R[10] = { 2, 2, 2, 2, 0, 0, 0, 0, 0, 0 };		// nCurrent_Level[RACK_RIGHT] = m_pg`
  - `Core/Src/dev_SRM.c:15970: nCurrent_Bay[RACK_RIGHT] = m_pgmEnv.Pos_X_Right - nDef_Bay_Start_R[nSRM_No];`
  - `Core/Src/dev_SRM.c:15978: if (nCurrent_Bay[RACK_RIGHT])`
  - `Core/Src/dev_SRM.c:15982: nCurrent_Level[RACK_RIGHT] = 0;`
  - `Core/Src/dev_SRM.c:15988: nCurrent_Level[RACK_RIGHT] = m_pgmEnv.Pos_Y_Right - nDef_Lv_Start_R[nSRM_No]; // LV 1 ~`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_MOVE_CENTER_TO_FEL_NO_LOAD

- **종류**: enum `enumFORK_MOVE_FLAG` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물무, Center -> FEL
- **용도(읽는 법)**: 헤더 주석: 화물무, Center -> FEL
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:41009: if ((nMode >= FORK_MOVE_CENTER_TO_FEL_NO_LOAD) \`
  - `Core/Src/dev_SRM.c:41039: if ((nMode >= FORK_MOVE_CENTER_TO_FEL_NO_LOAD) \`
  - `Core/Src/dev_SRM.c:41052: if ((nMode >= FORK_MOVE_CENTER_TO_FEL_NO_LOAD) \`
  - `Core/Src/dev_SRM.c:41057: if ((nMode == FORK_MOVE_CENTER_TO_FEL_NO_LOAD) \`
  - `Core/Src/dev_SRM.c:41098: if ((nMode == FORK_MOVE_CENTER_TO_FEL_NO_LOAD) \`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_MOVE_FEL_TO_CENTER_NO_LOAD

- **종류**: enum `enumFORK_MOVE_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물무, FEL -> Center
- **용도(읽는 법)**: 헤더 주석: 화물무, FEL -> Center
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:41435: else if ((nMode == FORK_MOVE_FEL_TO_CENTER_NO_LOAD) || (nMode == FORK_MOVE_FER_TO_CENTER_NO_LOAD) \`
  - `Core/Src/dev_SRM.c:41632: if ((nMode == FORK_MOVE_FEL_TO_CENTER_NO_LOAD) \`
  - `Core/Src/dev_SRM.c:42569: if ((nMode == FORK_MOVE_FEL_TO_CENTER_NO_LOAD) \`
  - `Core/Src/dev_SRM.c:61685: s_Fork_Oper_Mode = FORK_MOVE_FEL_TO_CENTER_NO_LOAD;`
  - `Core/Src/dev_SRM.c:62357: s_Fork_Oper_Mode = FORK_MOVE_FEL_TO_CENTER_NO_LOAD;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_MOVE_CENTER_TO_FER_NO_LOAD

- **종류**: enum `enumFORK_MOVE_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물무, Center -> FER
- **용도(읽는 법)**: 헤더 주석: 화물무, Center -> FER
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:41357: else if ((nMode == FORK_MOVE_CENTER_TO_FER_NO_LOAD) || (nMode == FORK_MOVE_CENTER_TO_FER_LOAD))`
  - `Core/Src/dev_SRM.c:42156: else if ((nMode == FORK_MOVE_CENTER_TO_FER_NO_LOAD) || \`
  - `Core/Src/dev_SRM.c:42329: else if ((nMode == FORK_MOVE_CENTER_TO_FER_NO_LOAD) || (nMode == FORK_MOVE_CENTER_TO_FER_LOAD))`
  - `Core/Src/dev_SRM.c:43194: else if ((nMode == FORK_MOVE_CENTER_TO_FER_NO_LOAD) || \`
  - `Core/Src/dev_SRM.c:43367: else if ((nMode == FORK_MOVE_CENTER_TO_FER_NO_LOAD) || (nMode == FORK_MOVE_CENTER_TO_FER_LOAD))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_MOVE_FER_TO_CENTER_NO_LOAD

- **종류**: enum `enumFORK_MOVE_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물무, FER -> Center
- **용도(읽는 법)**: 헤더 주석: 화물무, FER -> Center
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:41063: || (nMode == FORK_MOVE_FER_TO_CENTER_NO_LOAD) \`
  - `Core/Src/dev_SRM.c:41104: || (nMode == FORK_MOVE_FER_TO_CENTER_NO_LOAD) \`
  - `Core/Src/dev_SRM.c:41435: else if ((nMode == FORK_MOVE_FEL_TO_CENTER_NO_LOAD) || (nMode == FORK_MOVE_FER_TO_CENTER_NO_LOAD) \`
  - `Core/Src/dev_SRM.c:41633: || (nMode == FORK_MOVE_FER_TO_CENTER_NO_LOAD) \`
  - `Core/Src/dev_SRM.c:41822: || (nMode == FORK_MOVE_FER_TO_CENTER_NO_LOAD) \`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_MOVE_CENTER_TO_FML_NO_LOAD

- **종류**: enum `enumFORK_MOVE_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물무, Center -> FML
- **용도(읽는 법)**: 헤더 주석: 화물무, Center -> FML
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:41058: || (nMode == FORK_MOVE_CENTER_TO_FML_NO_LOAD) \`
  - `Core/Src/dev_SRM.c:41099: || (nMode == FORK_MOVE_CENTER_TO_FML_NO_LOAD) \`
  - `Core/Src/dev_SRM.c:41305: else if ((nMode == FORK_MOVE_CENTER_TO_FML_NO_LOAD) || (nMode == FORK_MOVE_CENTER_TO_FML_LOAD))`
  - `Core/Src/dev_SRM.c:41817: || (nMode == FORK_MOVE_CENTER_TO_FML_NO_LOAD) \`
  - `Core/Src/dev_SRM.c:42171: else if ((nMode == FORK_MOVE_CENTER_TO_FML_NO_LOAD) || \`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_MOVE_FML_TO_CENTER_NO_LOAD

- **종류**: enum `enumFORK_MOVE_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물무, FML -> Center
- **용도(읽는 법)**: 헤더 주석: 화물무, FML -> Center
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:41436: || (nMode == FORK_MOVE_FML_TO_CENTER_NO_LOAD) || (nMode == FORK_MOVE_FMR_TO_CENTER_NO_LOAD) \`
  - `Core/Src/dev_SRM.c:41634: || (nMode == FORK_MOVE_FML_TO_CENTER_NO_LOAD) \`
  - `Core/Src/dev_SRM.c:42571: || (nMode == FORK_MOVE_FML_TO_CENTER_NO_LOAD) \`
  - `Core/Src/dev_SRM.c:61689: s_Fork_Oper_Mode = FORK_MOVE_FML_TO_CENTER_NO_LOAD;`
  - `Core/Src/dev_SRM.c:62361: s_Fork_Oper_Mode = FORK_MOVE_FML_TO_CENTER_NO_LOAD;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_MOVE_CENTER_TO_FMR_NO_LOAD

- **종류**: enum `enumFORK_MOVE_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물무, Center -> FMR
- **용도(읽는 법)**: 헤더 주석: 화물무, Center -> FMR
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:41383: else if ((nMode == FORK_MOVE_CENTER_TO_FMR_NO_LOAD) || (nMode == FORK_MOVE_CENTER_TO_FMR_LOAD))`
  - `Core/Src/dev_SRM.c:42186: else if ((nMode == FORK_MOVE_CENTER_TO_FMR_NO_LOAD) || \`
  - `Core/Src/dev_SRM.c:42385: else if ((nMode == FORK_MOVE_CENTER_TO_FMR_NO_LOAD) || (nMode == FORK_MOVE_CENTER_TO_FMR_LOAD))`
  - `Core/Src/dev_SRM.c:43224: else if ((nMode == FORK_MOVE_CENTER_TO_FMR_NO_LOAD) || \`
  - `Core/Src/dev_SRM.c:43423: else if ((nMode == FORK_MOVE_CENTER_TO_FMR_NO_LOAD) || (nMode == FORK_MOVE_CENTER_TO_FMR_LOAD))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_MOVE_FMR_TO_CENTER_NO_LOAD

- **종류**: enum `enumFORK_MOVE_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물무, FMR -> Center
- **용도(읽는 법)**: 헤더 주석: 화물무, FMR -> Center
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:41064: || (nMode == FORK_MOVE_FMR_TO_CENTER_NO_LOAD) \`
  - `Core/Src/dev_SRM.c:41105: || (nMode == FORK_MOVE_FMR_TO_CENTER_NO_LOAD) \`
  - `Core/Src/dev_SRM.c:41436: || (nMode == FORK_MOVE_FML_TO_CENTER_NO_LOAD) || (nMode == FORK_MOVE_FMR_TO_CENTER_NO_LOAD) \`
  - `Core/Src/dev_SRM.c:41635: || (nMode == FORK_MOVE_FMR_TO_CENTER_NO_LOAD) \`
  - `Core/Src/dev_SRM.c:41823: || (nMode == FORK_MOVE_FMR_TO_CENTER_NO_LOAD) \`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_MOVE_CENTER_TO_FHL_NO_LOAD

- **종류**: enum `enumFORK_MOVE_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물무, Center -> FHL
- **용도(읽는 법)**: 헤더 주석: 화물무, Center -> FHL
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:41059: || (nMode == FORK_MOVE_CENTER_TO_FHL_NO_LOAD) \`
  - `Core/Src/dev_SRM.c:41100: || (nMode == FORK_MOVE_CENTER_TO_FHL_NO_LOAD) \`
  - `Core/Src/dev_SRM.c:41331: else if ((nMode == FORK_MOVE_CENTER_TO_FHL_NO_LOAD) || (nMode == FORK_MOVE_CENTER_TO_FHL_LOAD))`
  - `Core/Src/dev_SRM.c:41818: || (nMode == FORK_MOVE_CENTER_TO_FHL_NO_LOAD) \`
  - `Core/Src/dev_SRM.c:42201: else if ((nMode == FORK_MOVE_CENTER_TO_FHL_NO_LOAD) || \`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_MOVE_FHL_TO_CENTER_NO_LOAD

- **종류**: enum `enumFORK_MOVE_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물무, FHL -> Center
- **용도(읽는 법)**: 헤더 주석: 화물무, FHL -> Center
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:41437: || (nMode == FORK_MOVE_FHL_TO_CENTER_NO_LOAD) || (nMode == FORK_MOVE_FHR_TO_CENTER_NO_LOAD) \`
  - `Core/Src/dev_SRM.c:41636: || (nMode == FORK_MOVE_FHL_TO_CENTER_NO_LOAD) \`
  - `Core/Src/dev_SRM.c:42573: || (nMode == FORK_MOVE_FHL_TO_CENTER_NO_LOAD) \`
  - `Core/Src/dev_SRM.c:61693: s_Fork_Oper_Mode = FORK_MOVE_FHL_TO_CENTER_NO_LOAD;`
  - `Core/Src/dev_SRM.c:62365: s_Fork_Oper_Mode = FORK_MOVE_FHL_TO_CENTER_NO_LOAD;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_MOVE_CENTER_TO_FHR_NO_LOAD

- **종류**: enum `enumFORK_MOVE_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물무, Center -> FHR
- **용도(읽는 법)**: 헤더 주석: 화물무, Center -> FHR
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:41409: else if ((nMode == FORK_MOVE_CENTER_TO_FHR_NO_LOAD) || (nMode == FORK_MOVE_CENTER_TO_FHR_LOAD))`
  - `Core/Src/dev_SRM.c:42216: else if ((nMode == FORK_MOVE_CENTER_TO_FHR_NO_LOAD) || \`
  - `Core/Src/dev_SRM.c:42357: else if ((nMode == FORK_MOVE_CENTER_TO_FHR_NO_LOAD) || (nMode == FORK_MOVE_CENTER_TO_FHR_LOAD))`
  - `Core/Src/dev_SRM.c:43254: else if ((nMode == FORK_MOVE_CENTER_TO_FHR_NO_LOAD) || \`
  - `Core/Src/dev_SRM.c:43395: else if ((nMode == FORK_MOVE_CENTER_TO_FHR_NO_LOAD) || (nMode == FORK_MOVE_CENTER_TO_FHR_LOAD))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_MOVE_FHR_TO_CENTER_NO_LOAD

- **종류**: enum `enumFORK_MOVE_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물무, FHR -> Center
- **용도(읽는 법)**: 헤더 주석: 화물무, FHR -> Center
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:41010: && (nMode <= FORK_MOVE_FHR_TO_CENTER_NO_LOAD))`
  - `Core/Src/dev_SRM.c:41040: && (nMode <= FORK_MOVE_FHR_TO_CENTER_NO_LOAD))`
  - `Core/Src/dev_SRM.c:41065: || (nMode == FORK_MOVE_FHR_TO_CENTER_NO_LOAD) \`
  - `Core/Src/dev_SRM.c:41106: || (nMode == FORK_MOVE_FHR_TO_CENTER_NO_LOAD) \`
  - `Core/Src/dev_SRM.c:41437: || (nMode == FORK_MOVE_FHL_TO_CENTER_NO_LOAD) || (nMode == FORK_MOVE_FHR_TO_CENTER_NO_LOAD) \`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_MOVE_CENTER_TO_FEL_LOAD

- **종류**: enum `enumFORK_MOVE_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물유, Center -> FEL
- **용도(읽는 법)**: 헤더 주석: 화물유, Center -> FEL
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:41014: else if ((nMode >= FORK_MOVE_CENTER_TO_FEL_LOAD) \`
  - `Core/Src/dev_SRM.c:41044: else if ((nMode >= FORK_MOVE_CENTER_TO_FEL_LOAD) \`
  - `Core/Src/dev_SRM.c:41060: || (nMode == FORK_MOVE_CENTER_TO_FEL_LOAD) \`
  - `Core/Src/dev_SRM.c:41101: || (nMode == FORK_MOVE_CENTER_TO_FEL_LOAD) \`
  - `Core/Src/dev_SRM.c:41279: if ((nMode == FORK_MOVE_CENTER_TO_FEL_NO_LOAD) || (nMode == FORK_MOVE_CENTER_TO_FEL_LOAD))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_MOVE_FEL_TO_CENTER_LOAD

- **종류**: enum `enumFORK_MOVE_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물유, FEL -> Center
- **용도(읽는 법)**: 헤더 주석: 화물유, FEL -> Center
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:41438: || (nMode == FORK_MOVE_FEL_TO_CENTER_LOAD) || (nMode == FORK_MOVE_FER_TO_CENTER_LOAD) \`
  - `Core/Src/dev_SRM.c:41638: || (nMode == FORK_MOVE_FEL_TO_CENTER_LOAD) \`
  - `Core/Src/dev_SRM.c:42575: || (nMode == FORK_MOVE_FEL_TO_CENTER_LOAD) \`
  - `Core/Src/dev_SRM.c:60952: s_Fork_Oper_Mode = FORK_MOVE_FEL_TO_CENTER_LOAD;`
  - `Core/Inc/dev_SRM.h:1847: FORK_MOVE_FEL_TO_CENTER_LOAD,			// 화물유, FEL -> Center`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_MOVE_CENTER_TO_FER_LOAD

- **종류**: enum `enumFORK_MOVE_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물유, Center -> FER
- **용도(읽는 법)**: 헤더 주석: 화물유, Center -> FER
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:41357: else if ((nMode == FORK_MOVE_CENTER_TO_FER_NO_LOAD) || (nMode == FORK_MOVE_CENTER_TO_FER_LOAD))`
  - `Core/Src/dev_SRM.c:42157: (nMode == FORK_MOVE_CENTER_TO_FER_LOAD))`
  - `Core/Src/dev_SRM.c:42329: else if ((nMode == FORK_MOVE_CENTER_TO_FER_NO_LOAD) || (nMode == FORK_MOVE_CENTER_TO_FER_LOAD))`
  - `Core/Src/dev_SRM.c:43195: (nMode == FORK_MOVE_CENTER_TO_FER_LOAD))`
  - `Core/Src/dev_SRM.c:43367: else if ((nMode == FORK_MOVE_CENTER_TO_FER_NO_LOAD) || (nMode == FORK_MOVE_CENTER_TO_FER_LOAD))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_MOVE_FER_TO_CENTER_LOAD

- **종류**: enum `enumFORK_MOVE_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물유, FER -> Center
- **용도(읽는 법)**: 헤더 주석: 화물유, FER -> Center
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:41066: || (nMode == FORK_MOVE_FER_TO_CENTER_LOAD) \`
  - `Core/Src/dev_SRM.c:41107: || (nMode == FORK_MOVE_FER_TO_CENTER_LOAD) \`
  - `Core/Src/dev_SRM.c:41438: || (nMode == FORK_MOVE_FEL_TO_CENTER_LOAD) || (nMode == FORK_MOVE_FER_TO_CENTER_LOAD) \`
  - `Core/Src/dev_SRM.c:41639: || (nMode == FORK_MOVE_FER_TO_CENTER_LOAD) \`
  - `Core/Src/dev_SRM.c:41825: || (nMode == FORK_MOVE_FER_TO_CENTER_LOAD) \`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_MOVE_CENTER_TO_FML_LOAD

- **종류**: enum `enumFORK_MOVE_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물유, Center -> FML
- **용도(읽는 법)**: 헤더 주석: 화물유, Center -> FML
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:41061: || (nMode == FORK_MOVE_CENTER_TO_FML_LOAD) \`
  - `Core/Src/dev_SRM.c:41102: || (nMode == FORK_MOVE_CENTER_TO_FML_LOAD) \`
  - `Core/Src/dev_SRM.c:41305: else if ((nMode == FORK_MOVE_CENTER_TO_FML_NO_LOAD) || (nMode == FORK_MOVE_CENTER_TO_FML_LOAD))`
  - `Core/Src/dev_SRM.c:41820: || (nMode == FORK_MOVE_CENTER_TO_FML_LOAD) \`
  - `Core/Src/dev_SRM.c:42172: (nMode == FORK_MOVE_CENTER_TO_FML_LOAD))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_MOVE_FML_TO_CENTER_LOAD

- **종류**: enum `enumFORK_MOVE_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물유, FML -> Center
- **용도(읽는 법)**: 헤더 주석: 화물유, FML -> Center
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:41439: || (nMode == FORK_MOVE_FML_TO_CENTER_LOAD) || (nMode == FORK_MOVE_FMR_TO_CENTER_LOAD) \`
  - `Core/Src/dev_SRM.c:41640: || (nMode == FORK_MOVE_FML_TO_CENTER_LOAD) \`
  - `Core/Src/dev_SRM.c:42577: || (nMode == FORK_MOVE_FML_TO_CENTER_LOAD) \`
  - `Core/Src/dev_SRM.c:60956: s_Fork_Oper_Mode = FORK_MOVE_FML_TO_CENTER_LOAD;`
  - `Core/Inc/dev_SRM.h:1851: FORK_MOVE_FML_TO_CENTER_LOAD,			// 화물유, FML -> Center`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_MOVE_CENTER_TO_FMR_LOAD

- **종류**: enum `enumFORK_MOVE_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물유, Center -> FMR
- **용도(읽는 법)**: 헤더 주석: 화물유, Center -> FMR
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:41383: else if ((nMode == FORK_MOVE_CENTER_TO_FMR_NO_LOAD) || (nMode == FORK_MOVE_CENTER_TO_FMR_LOAD))`
  - `Core/Src/dev_SRM.c:42187: (nMode == FORK_MOVE_CENTER_TO_FMR_LOAD))`
  - `Core/Src/dev_SRM.c:42385: else if ((nMode == FORK_MOVE_CENTER_TO_FMR_NO_LOAD) || (nMode == FORK_MOVE_CENTER_TO_FMR_LOAD))`
  - `Core/Src/dev_SRM.c:43225: (nMode == FORK_MOVE_CENTER_TO_FMR_LOAD))`
  - `Core/Src/dev_SRM.c:43423: else if ((nMode == FORK_MOVE_CENTER_TO_FMR_NO_LOAD) || (nMode == FORK_MOVE_CENTER_TO_FMR_LOAD))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_MOVE_FMR_TO_CENTER_LOAD

- **종류**: enum `enumFORK_MOVE_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물유, FMR -> Center
- **용도(읽는 법)**: 헤더 주석: 화물유, FMR -> Center
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:41067: || (nMode == FORK_MOVE_FMR_TO_CENTER_LOAD) \`
  - `Core/Src/dev_SRM.c:41108: || (nMode == FORK_MOVE_FMR_TO_CENTER_LOAD) \`
  - `Core/Src/dev_SRM.c:41439: || (nMode == FORK_MOVE_FML_TO_CENTER_LOAD) || (nMode == FORK_MOVE_FMR_TO_CENTER_LOAD) \`
  - `Core/Src/dev_SRM.c:41641: || (nMode == FORK_MOVE_FMR_TO_CENTER_LOAD) \`
  - `Core/Src/dev_SRM.c:41826: || (nMode == FORK_MOVE_FMR_TO_CENTER_LOAD) \`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_MOVE_CENTER_TO_FHL_LOAD

- **종류**: enum `enumFORK_MOVE_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물유, Center -> FHL
- **용도(읽는 법)**: 헤더 주석: 화물유, Center -> FHL
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:41062: || (nMode == FORK_MOVE_CENTER_TO_FHL_LOAD) \`
  - `Core/Src/dev_SRM.c:41103: || (nMode == FORK_MOVE_CENTER_TO_FHL_LOAD) \`
  - `Core/Src/dev_SRM.c:41331: else if ((nMode == FORK_MOVE_CENTER_TO_FHL_NO_LOAD) || (nMode == FORK_MOVE_CENTER_TO_FHL_LOAD))`
  - `Core/Src/dev_SRM.c:41821: || (nMode == FORK_MOVE_CENTER_TO_FHL_LOAD) \`
  - `Core/Src/dev_SRM.c:42202: (nMode == FORK_MOVE_CENTER_TO_FHL_LOAD))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_MOVE_FHL_TO_CENTER_LOAD

- **종류**: enum `enumFORK_MOVE_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물유, FHL -> Center
- **용도(읽는 법)**: 헤더 주석: 화물유, FHL -> Center
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:41440: || (nMode == FORK_MOVE_FHL_TO_CENTER_LOAD) || (nMode == FORK_MOVE_FHR_TO_CENTER_LOAD))`
  - `Core/Src/dev_SRM.c:41642: || (nMode == FORK_MOVE_FHL_TO_CENTER_LOAD) \`
  - `Core/Src/dev_SRM.c:42579: || (nMode == FORK_MOVE_FHL_TO_CENTER_LOAD) \`
  - `Core/Src/dev_SRM.c:60960: s_Fork_Oper_Mode = FORK_MOVE_FHL_TO_CENTER_LOAD;`
  - `Core/Inc/dev_SRM.h:1855: FORK_MOVE_FHL_TO_CENTER_LOAD,			// 화물유, FHL -> Center`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_MOVE_CENTER_TO_FHR_LOAD

- **종류**: enum `enumFORK_MOVE_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물유, Center -> FHR
- **용도(읽는 법)**: 헤더 주석: 화물유, Center -> FHR
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:41409: else if ((nMode == FORK_MOVE_CENTER_TO_FHR_NO_LOAD) || (nMode == FORK_MOVE_CENTER_TO_FHR_LOAD))`
  - `Core/Src/dev_SRM.c:42217: (nMode == FORK_MOVE_CENTER_TO_FHR_LOAD))`
  - `Core/Src/dev_SRM.c:42357: else if ((nMode == FORK_MOVE_CENTER_TO_FHR_NO_LOAD) || (nMode == FORK_MOVE_CENTER_TO_FHR_LOAD))`
  - `Core/Src/dev_SRM.c:43255: (nMode == FORK_MOVE_CENTER_TO_FHR_LOAD))`
  - `Core/Src/dev_SRM.c:43395: else if ((nMode == FORK_MOVE_CENTER_TO_FHR_NO_LOAD) || (nMode == FORK_MOVE_CENTER_TO_FHR_LOAD))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_MOVE_FHR_TO_CENTER_LOAD

- **종류**: enum `enumFORK_MOVE_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물유, FHR -> Center
- **용도(읽는 법)**: 헤더 주석: 화물유, FHR -> Center
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:41015: && (nMode <= FORK_MOVE_FHR_TO_CENTER_LOAD))`
  - `Core/Src/dev_SRM.c:41045: && (nMode <= FORK_MOVE_FHR_TO_CENTER_LOAD))`
  - `Core/Src/dev_SRM.c:41053: && (nMode <= FORK_MOVE_FHR_TO_CENTER_LOAD))`
  - `Core/Src/dev_SRM.c:41068: || (nMode == FORK_MOVE_FHR_TO_CENTER_LOAD)`
  - `Core/Src/dev_SRM.c:41109: || (nMode == FORK_MOVE_FHR_TO_CENTER_LOAD)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEVICE_SETUP_MODE

- **종류**: enum `enumDEVICE_MODE` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:3188: Change_DeviceMode(DEVICE_SETUP_MODE, 0);`
  - `Core/Src/dev_SRM.c:44448: Change_DeviceMode(DEVICE_SETUP_MODE, 1);`
  - `Core/Src/dev_SRM.c:44633: Change_DeviceMode(DEVICE_SETUP_MODE, 1);`
  - `Core/Src/dev_SRM.c:63800: if (nMode == DEVICE_SETUP_MODE)`
  - `Core/Src/dev_SRM.c:66893: Change_DeviceMode(DEVICE_SETUP_MODE, 1);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEVICE_MANUAL_MODE

- **종류**: enum `enumDEVICE_MODE` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/alarm.c:492: Change_DeviceMode(DEVICE_MANUAL_MODE, 1);`
  - `Core/Src/alarm.c:513: Change_DeviceMode(DEVICE_MANUAL_MODE, 1);`
  - `Core/Src/alarm.c:1429: Change_DeviceMode(DEVICE_MANUAL_MODE, 1);`
  - `Core/Src/com_tml.c:3184: Change_DeviceMode(DEVICE_MANUAL_MODE, 0);`
  - `Core/Src/dev_SRM.c:44628: Change_DeviceMode(DEVICE_MANUAL_MODE, 1);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEVICE_SEMI_AUTO_MODE

- **종류**: enum `enumDEVICE_MODE` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:3192: Change_DeviceMode(DEVICE_SEMI_AUTO_MODE, 0);`
  - `Core/Src/dev_SRM.c:63866: else if (nMode == DEVICE_SEMI_AUTO_MODE)`
  - `Core/Inc/dev_SRM.h:1863: DEVICE_SEMI_AUTO_MODE,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEVICE_AUTO_MODE

- **종류**: enum `enumDEVICE_MODE` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:63948: else if (nMode == DEVICE_AUTO_MODE)`
  - `Core/Src/dev_SRM.c:67436: Change_DeviceMode(DEVICE_AUTO_MODE, 0);`
  - `Core/Inc/dev_SRM.h:1864: DEVICE_AUTO_MODE,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TRAVEL_LIMIT_NONE

- **종류**: enum `enumTRAVEL_LIMIT_STATE` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:30693: if (m_St.SRM_Mode.Bit.Force || (m_pgmEnv.Travel_Limit_Flag != TRAVEL_LIMIT_NONE))`
  - `Core/Src/dev_SRM.c:30708: if (m_pgmEnv.Travel_Limit_Flag != TRAVEL_LIMIT_NONE)`
  - `Core/Src/dev_SRM.c:44789: if (m_pgmEnv.Travel_Limit_Flag == TRAVEL_LIMIT_NONE)`
  - `Core/Src/dev_SRM.c:44807: if (m_pgmEnv.Travel_Limit_Flag == TRAVEL_LIMIT_NONE)`
  - `Core/Inc/dev_SRM.h:1868: TRAVEL_LIMIT_NONE = 0,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TRAVEL_LIMIT_FWD

- **종류**: enum `enumTRAVEL_LIMIT_STATE` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:29739: if (m_pgmEnv.Travel_Limit_Flag == TRAVEL_LIMIT_FWD)`
  - `Core/Src/dev_SRM.c:30239: if (m_pgmEnv.Travel_Limit_Flag == TRAVEL_LIMIT_FWD)`
  - `Core/Src/dev_SRM.c:30719: if (m_pgmEnv.Travel_Limit_Flag == TRAVEL_LIMIT_FWD)`
  - `Core/Src/dev_SRM.c:67648: nTravel_Limit = TRAVEL_LIMIT_FWD;`
  - `Core/Inc/dev_SRM.h:1869: TRAVEL_LIMIT_FWD,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TRAVEL_LIMIT_RVS

- **종류**: enum `enumTRAVEL_LIMIT_STATE` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:29752: else if (m_pgmEnv.Travel_Limit_Flag == TRAVEL_LIMIT_RVS)`
  - `Core/Src/dev_SRM.c:30252: else if (m_pgmEnv.Travel_Limit_Flag == TRAVEL_LIMIT_RVS)`
  - `Core/Src/dev_SRM.c:30734: else if (m_pgmEnv.Travel_Limit_Flag == TRAVEL_LIMIT_RVS)`
  - `Core/Src/dev_SRM.c:67638: nTravel_Limit = TRAVEL_LIMIT_RVS;`
  - `Core/Inc/dev_SRM.h:1870: TRAVEL_LIMIT_RVS,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HOIST_LIMIT_NONE

- **종류**: enum `enumHOIST_LIMIT_STATE` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:31805: if (m_St.SRM_Mode.Bit.Force || (m_pgmEnv.Hoist_Limit_Flag != HOIST_LIMIT_NONE))`
  - `Core/Src/dev_SRM.c:31821: if (m_pgmEnv.Hoist_Limit_Flag != HOIST_LIMIT_NONE)`
  - `Core/Src/dev_SRM.c:44741: if (m_pgmEnv.Hoist_Limit_Flag == HOIST_LIMIT_NONE)`
  - `Core/Src/dev_SRM.c:44765: if (m_pgmEnv.Hoist_Limit_Flag == HOIST_LIMIT_NONE)`
  - `Core/Inc/dev_SRM.h:1874: HOIST_LIMIT_NONE = 0,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HOIST_LIMIT_DOWN

- **종류**: enum `enumHOIST_LIMIT_STATE` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:29912: else if (m_pgmEnv.Hoist_Limit_Flag == HOIST_LIMIT_DOWN)`
  - `Core/Src/dev_SRM.c:30405: else if (m_pgmEnv.Hoist_Limit_Flag == HOIST_LIMIT_DOWN)`
  - `Core/Src/dev_SRM.c:30442: else if (m_pgmEnv.Hoist_Limit_Flag == HOIST_LIMIT_DOWN)`
  - `Core/Src/dev_SRM.c:31833: if (m_pgmEnv.Hoist_Limit_Flag == HOIST_LIMIT_DOWN)`
  - `Core/Src/dev_SRM.c:67657: nHoist_Limit = HOIST_LIMIT_DOWN;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HOIST_LIMIT_UP

- **종류**: enum `enumHOIST_LIMIT_STATE` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:29899: if (m_pgmEnv.Hoist_Limit_Flag == HOIST_LIMIT_UP)`
  - `Core/Src/dev_SRM.c:30392: if (m_pgmEnv.Hoist_Limit_Flag == HOIST_LIMIT_UP)`
  - `Core/Src/dev_SRM.c:30429: if (m_pgmEnv.Hoist_Limit_Flag == HOIST_LIMIT_UP)`
  - `Core/Src/dev_SRM.c:31848: else if (m_pgmEnv.Hoist_Limit_Flag == HOIST_LIMIT_UP)`
  - `Core/Src/dev_SRM.c:67667: nHoist_Limit = HOIST_LIMIT_UP;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MANUAL_CTR_MODE_VEXI

- **종류**: enum `enumMANUAL_CTR_MODE` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:29806: m_Manual_Ctr_Master = MANUAL_CTR_MODE_VEXI;`
  - `Core/Src/dev_SRM.c:29980: m_Manual_Ctr_Master = MANUAL_CTR_MODE_VEXI;`
  - `Core/Src/dev_SRM.c:30117: m_Manual_Ctr_Master = MANUAL_CTR_MODE_VEXI;`
  - `Core/Src/dev_SRM.c:30781: if (m_Manual_Ctr_Master == MANUAL_CTR_MODE_VEXI)`
  - `Core/Src/dev_SRM.c:30851: if (m_Manual_Ctr_Master == MANUAL_CTR_MODE_VEXI)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MANUAL_CTR_MODE_HMI

- **종류**: enum `enumMANUAL_CTR_MODE` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:30286: m_Manual_Ctr_Master = MANUAL_CTR_MODE_HMI;`
  - `Core/Src/dev_SRM.c:30473: m_Manual_Ctr_Master = MANUAL_CTR_MODE_HMI;`
  - `Core/Src/dev_SRM.c:30570: m_Manual_Ctr_Master = MANUAL_CTR_MODE_HMI;`
  - `Core/Src/dev_SRM.c:30805: else if (m_Manual_Ctr_Master == MANUAL_CTR_MODE_HMI)`
  - `Core/Src/dev_SRM.c:30860: else if (m_Manual_Ctr_Master == MANUAL_CTR_MODE_HMI)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MANUAL_CTR_TRAV_STOP

- **종류**: enum `enumMANUAL_TRAV_CTR` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:29647: case MANUAL_CTR_TRAV_STOP: // ì ì§`
  - `Core/Src/dev_SRM.c:29662: if (mode == MANUAL_CTR_TRAV_STOP)`
  - `Core/Src/dev_SRM.c:29690: m_Manual_Run_Mode[nInvertor] = MANUAL_CTR_TRAV_STOP;`
  - `Core/Src/dev_SRM.c:29701: m_Manual_Run_Mode[nInvertor] = MANUAL_CTR_TRAV_STOP;`
  - `Core/Src/dev_SRM.c:30152: case MANUAL_CTR_TRAV_STOP: // ì ì§`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MANUAL_CTR_TRAV_FWD_LOW

- **종류**: enum `enumMANUAL_TRAV_CTR` 멤버
- **값**: `1`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:22501: case MANUAL_CTR_TRAV_FWD_LOW: // ì ì ì ì§ ì¢ì¸¡`
  - `Core/Src/dev_SRM.c:22540: case MANUAL_CTR_TRAV_FWD_LOW: // ì ì ì ì§`
  - `Core/Src/dev_SRM.c:23021: case MANUAL_CTR_TRAV_FWD_LOW: // ì ì ì ì§`
  - `Core/Src/dev_SRM.c:23063: case MANUAL_CTR_TRAV_FWD_LOW: // ì ì ì ì§`
  - `Core/Src/dev_SRM.c:24007: case MANUAL_CTR_TRAV_FWD_LOW: // ì ì ì ì§`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MANUAL_CTR_TRAV_RVS_LOW

- **종류**: enum `enumMANUAL_TRAV_CTR` 멤버
- **값**: `2`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:22502: case MANUAL_CTR_TRAV_RVS_LOW: // ì ì íì§ ì¢ì¸¡`
  - `Core/Src/dev_SRM.c:22545: case MANUAL_CTR_TRAV_RVS_LOW: // ì ì íì§`
  - `Core/Src/dev_SRM.c:23022: case MANUAL_CTR_TRAV_RVS_LOW: // ì ì íì§`
  - `Core/Src/dev_SRM.c:23068: case MANUAL_CTR_TRAV_RVS_LOW: // ì ì íì§`
  - `Core/Src/dev_SRM.c:24008: case MANUAL_CTR_TRAV_RVS_LOW: // ì ì íì§`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MANUAL_CTR_TRAV_FWD_MID

- **종류**: enum `enumMANUAL_TRAV_CTR` 멤버
- **값**: `11`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:22541: case MANUAL_CTR_TRAV_FWD_MID: // ì¤ì ì ì§`
  - `Core/Src/dev_SRM.c:23023: case MANUAL_CTR_TRAV_FWD_MID: // ì¤ì ì ì§`
  - `Core/Src/dev_SRM.c:23064: case MANUAL_CTR_TRAV_FWD_MID: // ì¤ì ì ì§`
  - `Core/Src/dev_SRM.c:24009: case MANUAL_CTR_TRAV_FWD_MID: // ì¤ì ì ì§`
  - `Core/Src/dev_SRM.c:24050: case MANUAL_CTR_TRAV_FWD_MID: // ì¤ì ì ì§`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MANUAL_CTR_TRAV_RVS_MID

- **종류**: enum `enumMANUAL_TRAV_CTR` 멤버
- **값**: `12`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:22546: case MANUAL_CTR_TRAV_RVS_MID: // ì¤ì íì§`
  - `Core/Src/dev_SRM.c:23024: case MANUAL_CTR_TRAV_RVS_MID: // ì¤ì ì ì§`
  - `Core/Src/dev_SRM.c:23069: case MANUAL_CTR_TRAV_RVS_MID: // ì¤ì íì§`
  - `Core/Src/dev_SRM.c:24010: case MANUAL_CTR_TRAV_RVS_MID: // ì¤ì ì ì§`
  - `Core/Src/dev_SRM.c:24055: case MANUAL_CTR_TRAV_RVS_MID: // ì¤ì íì§`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MANUAL_CTR_LIFT_STOP

- **종류**: enum `enumMANUAL_LIFT_CTR` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:24924: if (nAction == MANUAL_CTR_LIFT_STOP)  // Stop`
  - `Core/Src/dev_SRM.c:24978: if (nAction == MANUAL_CTR_LIFT_STOP)  // Stop`
  - `Core/Src/dev_SRM.c:25243: if (nAction == MANUAL_CTR_LIFT_STOP)`
  - `Core/Src/dev_SRM.c:25396: if (nAction == MANUAL_CTR_LIFT_STOP)  // Stop`
  - `Core/Src/dev_SRM.c:25450: if (nAction == MANUAL_CTR_LIFT_STOP)  // Stop`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MANUAL_CTR_LIFT_UP_LOW

- **종류**: enum `enumMANUAL_LIFT_CTR` 멤버
- **값**: `1`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:24929: else if (nAction == MANUAL_CTR_LIFT_UP_LOW)`
  - `Core/Src/dev_SRM.c:24983: else if ((nAction == MANUAL_CTR_LIFT_UP_LOW) || (nAction == MANUAL_CTR_LIFT_DOWN_LOW))	 // Move Low `
  - `Core/Src/dev_SRM.c:25015: if (nAction == MANUAL_CTR_LIFT_UP_LOW)`
  - `Core/Src/dev_SRM.c:25056: if (nAction == MANUAL_CTR_LIFT_UP_LOW)`
  - `Core/Src/dev_SRM.c:25122: if (nAction == MANUAL_CTR_LIFT_UP_LOW)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MANUAL_CTR_LIFT_DOWN_LOW

- **종류**: enum `enumMANUAL_LIFT_CTR` 멤버
- **값**: `2`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:24952: else if (nAction == MANUAL_CTR_LIFT_DOWN_LOW)`
  - `Core/Src/dev_SRM.c:24983: else if ((nAction == MANUAL_CTR_LIFT_UP_LOW) || (nAction == MANUAL_CTR_LIFT_DOWN_LOW))	 // Move Low `
  - `Core/Src/dev_SRM.c:25027: else if (nAction == MANUAL_CTR_LIFT_DOWN_LOW)`
  - `Core/Src/dev_SRM.c:25088: else if (nAction == MANUAL_CTR_LIFT_DOWN_LOW)`
  - `Core/Src/dev_SRM.c:25126: else if (nAction == MANUAL_CTR_LIFT_DOWN_LOW)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MANUAL_CTR_LIFT_UP_MID

- **종류**: enum `enumMANUAL_LIFT_CTR` 멤버
- **값**: `11`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:24935: else if (nAction == MANUAL_CTR_LIFT_UP_MID)`
  - `Core/Src/dev_SRM.c:25200: else if (nAction == MANUAL_CTR_LIFT_UP_MID)	// ì¤ì ìì¹`
  - `Core/Src/dev_SRM.c:25255: case MANUAL_CTR_LIFT_UP_MID: // ì¤ì ìì¹`
  - `Core/Src/dev_SRM.c:25407: else if (nAction == MANUAL_CTR_LIFT_UP_MID)`
  - `Core/Src/dev_SRM.c:25765: else if (nAction == MANUAL_CTR_LIFT_UP_MID)	// ì¤ì ìì¹`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MANUAL_CTR_LIFT_DOWN_MID

- **종류**: enum `enumMANUAL_LIFT_CTR` 멤버
- **값**: `12`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:24958: else if (nAction == MANUAL_CTR_LIFT_DOWN_MID)`
  - `Core/Src/dev_SRM.c:25220: else if (nAction == MANUAL_CTR_LIFT_DOWN_MID)  // ì¤ì íê°`
  - `Core/Src/dev_SRM.c:25260: case MANUAL_CTR_LIFT_DOWN_MID: // ì¤ì íê°`
  - `Core/Src/dev_SRM.c:25430: else if (nAction == MANUAL_CTR_LIFT_DOWN_MID)`
  - `Core/Src/dev_SRM.c:25815: else if (nAction == MANUAL_CTR_LIFT_DOWN_MID)  // ì¤ì íê°`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MOVE_POSITION_NONE

- **종류**: enum `enumMOVE_POSITION_FLAG` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:15855: || (m_pgmEnv.Move_PosFlag == MOVE_POSITION_NONE))`
  - `Core/Src/dev_SRM.c:16861: || (m_pgmEnv.Move_PosFlag == MOVE_POSITION_NONE))`
  - `Core/Src/dev_SRM.c:17443: || (m_pgmEnv.Move_PosFlag == MOVE_POSITION_NONE))`
  - `Core/Src/dev_SRM.c:18081: || (m_pgmEnv.Move_PosFlag == MOVE_POSITION_NONE))`
  - `Core/Src/dev_SRM.c:18770: || (m_pgmEnv.Move_PosFlag == MOVE_POSITION_NONE))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MOVE_POSITION_FORK1_L

- **종류**: enum `enumMOVE_POSITION_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:5443: if ((m_pgmEnv.Move_PosFlag == MOVE_POSITION_FORK1_L) \`
  - `Core/Src/com_tml.c:5463: if ((m_pgmEnv.Move_PosFlag == MOVE_POSITION_FORK1_L) \`
  - `Core/Src/dev_SRM.c:15853: if ((m_pgmEnv.Move_PosFlag == MOVE_POSITION_FORK1_L) \`
  - `Core/Src/dev_SRM.c:16859: if ((m_pgmEnv.Move_PosFlag == MOVE_POSITION_FORK1_L) \`
  - `Core/Src/dev_SRM.c:17441: if ((m_pgmEnv.Move_PosFlag == MOVE_POSITION_FORK1_L) \`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MOVE_POSITION_FORK1_R

- **종류**: enum `enumMOVE_POSITION_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:5448: else if ((m_pgmEnv.Move_PosFlag == MOVE_POSITION_FORK1_R) \`
  - `Core/Src/com_tml.c:5468: else if ((m_pgmEnv.Move_PosFlag == MOVE_POSITION_FORK1_R) \`
  - `Core/Src/dev_SRM.c:22234: else if ((m_pgmEnv.Move_PosFlag == MOVE_POSITION_FORK1_R) \`
  - `Core/Src/dev_SRM.c:22349: else if ((m_pgmEnv.Move_PosFlag == MOVE_POSITION_FORK1_R) || (m_pgmEnv.Move_PosFlag == MOVE_POSITION`
  - `Core/Src/dev_SRM.c:22413: else if ((m_pgmEnv.Move_PosFlag == MOVE_POSITION_FORK1_R) || (m_pgmEnv.Move_PosFlag == MOVE_POSITION`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MOVE_POSITION_FORK2_L

- **종류**: enum `enumMOVE_POSITION_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:5444: || (m_pgmEnv.Move_PosFlag == MOVE_POSITION_FORK2_L))`
  - `Core/Src/com_tml.c:5464: || (m_pgmEnv.Move_PosFlag == MOVE_POSITION_FORK2_L))`
  - `Core/Src/dev_SRM.c:15854: || (m_pgmEnv.Move_PosFlag == MOVE_POSITION_FORK2_L) \`
  - `Core/Src/dev_SRM.c:16860: || (m_pgmEnv.Move_PosFlag == MOVE_POSITION_FORK2_L) \`
  - `Core/Src/dev_SRM.c:17442: || (m_pgmEnv.Move_PosFlag == MOVE_POSITION_FORK2_L) \`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MOVE_POSITION_FORK2_R

- **종류**: enum `enumMOVE_POSITION_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:5449: || (m_pgmEnv.Move_PosFlag == MOVE_POSITION_FORK2_R))`
  - `Core/Src/com_tml.c:5469: || (m_pgmEnv.Move_PosFlag == MOVE_POSITION_FORK2_R))`
  - `Core/Src/dev_SRM.c:22235: || (m_pgmEnv.Move_PosFlag == MOVE_POSITION_FORK2_R))`
  - `Core/Src/dev_SRM.c:22349: else if ((m_pgmEnv.Move_PosFlag == MOVE_POSITION_FORK1_R) || (m_pgmEnv.Move_PosFlag == MOVE_POSITION`
  - `Core/Src/dev_SRM.c:22413: else if ((m_pgmEnv.Move_PosFlag == MOVE_POSITION_FORK1_R) || (m_pgmEnv.Move_PosFlag == MOVE_POSITION`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MANUAL_CTR_FORK_STOP

- **종류**: enum `enumMANUAL_CTR_FORK_DIR` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:30013: case  MANUAL_CTR_FORK_STOP:		// Move stop`
  - `Core/Src/dev_SRM.c:30025: if (mode == MANUAL_CTR_FORK_STOP)`
  - `Core/Src/dev_SRM.c:30064: m_Manual_Run_Mode[nInvertor] = MANUAL_CTR_FORK_STOP;`
  - `Core/Src/dev_SRM.c:30497: case  MANUAL_CTR_FORK_STOP:		// Move stop`
  - `Core/Src/dev_SRM.c:30507: if (mode == MANUAL_CTR_FORK_STOP)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MANUAL_CTR_FORK_CENTER

- **종류**: enum `enumMANUAL_CTR_FORK_DIR` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:30014: case  MANUAL_CTR_FORK_CENTER:	// Move center`
  - `Core/Src/dev_SRM.c:30498: case  MANUAL_CTR_FORK_CENTER:	// Move center`
  - `Core/Src/dev_SRM.c:32900: if (nOperMode == MANUAL_CTR_FORK_CENTER)`
  - `Core/Src/dev_SRM.c:32916: if (nOperMode == MANUAL_CTR_FORK_CENTER)`
  - `Core/Src/dev_SRM.c:32939: if (nOperMode == MANUAL_CTR_FORK_CENTER)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MANUAL_CTR_FORK_LEFT

- **종류**: enum `enumMANUAL_CTR_FORK_DIR` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:30015: case  MANUAL_CTR_FORK_LEFT:		// Move left`
  - `Core/Src/dev_SRM.c:30107: else if (mode == MANUAL_CTR_FORK_LEFT)`
  - `Core/Src/dev_SRM.c:30499: case  MANUAL_CTR_FORK_LEFT:		// Move left`
  - `Core/Src/dev_SRM.c:30560: else if (mode == MANUAL_CTR_FORK_LEFT)`
  - `Core/Src/dev_SRM.c:32904: else if (nOperMode == MANUAL_CTR_FORK_LEFT)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MANUAL_CTR_FORK_RIGHT

- **종류**: enum `enumMANUAL_CTR_FORK_DIR` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:30016: case  MANUAL_CTR_FORK_RIGHT:	// Move right`
  - `Core/Src/dev_SRM.c:30103: if (mode == MANUAL_CTR_FORK_RIGHT)`
  - `Core/Src/dev_SRM.c:30500: case  MANUAL_CTR_FORK_RIGHT:	// Move right`
  - `Core/Src/dev_SRM.c:30556: if (mode == MANUAL_CTR_FORK_RIGHT)`
  - `Core/Src/dev_SRM.c:32908: else if (nOperMode == MANUAL_CTR_FORK_RIGHT)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HMI_MANUAL_KEY_TRAV_FWD_LOW

- **종류**: enum `enumHMI_MANUAL_KEY_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:66171: case HMI_MANUAL_KEY_TRAV_FWD_LOW:`
  - `Core/Src/dev_SRM.c:66233: case HMI_MANUAL_KEY_TRAV_FWD_LOW:`
  - `Core/Inc/dev_SRM.h:2064: HMI_MANUAL_KEY_TRAV_FWD_LOW,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HMI_MANUAL_KEY_TRAV_RVS_LOW

- **종류**: enum `enumHMI_MANUAL_KEY_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:66175: case HMI_MANUAL_KEY_TRAV_RVS_LOW:`
  - `Core/Src/dev_SRM.c:66234: case HMI_MANUAL_KEY_TRAV_RVS_LOW:`
  - `Core/Inc/dev_SRM.h:2065: HMI_MANUAL_KEY_TRAV_RVS_LOW,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HMI_MANUAL_KEY_TRAV_FWD_MID

- **종류**: enum `enumHMI_MANUAL_KEY_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:66179: case HMI_MANUAL_KEY_TRAV_FWD_MID:`
  - `Core/Src/dev_SRM.c:66235: case HMI_MANUAL_KEY_TRAV_FWD_MID:`
  - `Core/Inc/dev_SRM.h:2066: HMI_MANUAL_KEY_TRAV_FWD_MID,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

