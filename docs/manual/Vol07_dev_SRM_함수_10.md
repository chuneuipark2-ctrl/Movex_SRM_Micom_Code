# Vol.07 — dev_SRM.c 함수 (10)

> 생성일: 2026-06-16 | MX SRM App Ver 4.4 | 소스 미수정

상태머신 함수.

---

### Lift_Setup_Move_Position_Start

- **종류**: 함수
- **시그니처**: `void Lift_Setup_Move_Position_Start(INT32S nTargetPosition)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:1185: Lift_Setup_Move_Position_Start((INT32S)pCtrl->Value);`
  - `Core/Src/dev_SRM.c:54285: void Lift_Setup_Move_Position_Start(INT32S nTargetPosition)`
  - `Core/Inc/dev_SRM.h:2370: void Lift_Setup_Move_Position_Start(INT32S nTargetPosition);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Lift_Setup_Move_Level_Start

- **종류**: 함수
- **시그니처**: `void Lift_Setup_Move_Level_Start(INT32S nTargetPosition)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:1190: Lift_Setup_Move_Level_Start((INT32S)pCtrl->Value);`
  - `Core/Src/dev_SRM.c:54443: void Lift_Setup_Move_Level_Start(INT32S nTargetPosition)`
  - `Core/Inc/dev_SRM.h:2371: void Lift_Setup_Move_Level_Start(INT32S nTargetPosition);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Fork_Setup_Move_Position_Start

- **종류**: 함수
- **시그니처**: `void Fork_Setup_Move_Position_Start(INT32S nTargetPosition)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:1197: Fork_Setup_Move_Position_Start((INT32S)pCtrl->Value);`
  - `Core/Src/dev_SRM.c:54593: void Fork_Setup_Move_Position_Start(INT32S nTargetPosition)`
  - `Core/Inc/dev_SRM.h:2372: void Fork_Setup_Move_Position_Start(INT32S nTargetPosition);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Travel_Setup_Move_Position

- **종류**: 함수
- **시그니처**: `void Travel_Setup_Move_Position()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:54648: void Travel_Setup_Move_Position()`
  - `Core/Src/dev_SRM.c:63421: Travel_Setup_Move_Position();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Lift_Setup_Move_Position

- **종류**: 함수
- **시그니처**: `void Lift_Setup_Move_Position()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:54822: void Lift_Setup_Move_Position()`
  - `Core/Src/dev_SRM.c:63447: Lift_Setup_Move_Position();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Fork_Setup_Move_Position

- **종류**: 함수
- **시그니처**: `void Fork_Setup_Move_Position()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:55029: void Fork_Setup_Move_Position()`
  - `Core/Src/dev_SRM.c:63473: Fork_Setup_Move_Position();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Travel_Move_Process

- **종류**: 함수
- **시그니처**: `void Travel_Move_Process(INT08U nWorkIdx)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:55203: void Travel_Move_Process(INT08U nWorkIdx)`
  - `Core/Src/dev_SRM.c:59379: Travel_Move_Process(s_WorkInx);`
  - `Core/Src/dev_SRM.c:63196: Travel_Move_Process(s_WorkInx);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Lift_Move_Process

- **종류**: 함수
- **시그니처**: `void Lift_Move_Process(INT08U nWorkIdx)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:55882: void Lift_Move_Process(INT08U nWorkIdx)`
  - `Core/Src/dev_SRM.c:59380: Lift_Move_Process(s_WorkInx);`
  - `Core/Src/dev_SRM.c:63197: Lift_Move_Process(s_WorkInx);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Fwd_Decel_Pos_Setup

- **종류**: 함수
- **시그니처**: `INT08U Check_Fwd_Decel_Pos_Setup(INT08U nInvertor) { if (nInvertor == INV_TRAVEL) { if (m_ExtSEnv2.TravDrive.DecelDogErr.Fwd1_Pos1 && m_ExtSEnv2.TravDrive.DecelDogErr.Fwd1_Pos2 && m_ExtSEnv2.TravDrive.DecelDogErr.Fwd2_Pos1)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:56503: INT08U Check_Fwd_Decel_Pos_Setup(INT08U nInvertor)`
  - `Core/Src/dev_SRM.c:56579: if (Check_Fwd_Decel_Pos_Setup(INV_TRAVEL))`
  - `Core/Src/dev_SRM.c:56637: if (Check_Fwd_Decel_Pos_Setup(INV_HOIST))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Rvs_DecelPos_Setup

- **종류**: 함수
- **시그니처**: `INT08U Check_Rvs_DecelPos_Setup(INT08U nInvertor) { if (nInvertor == INV_TRAVEL) { if (m_ExtSEnv2.TravDrive.DecelDogErr.Rvr1_Pos1 && m_ExtSEnv2.TravDrive.DecelDogErr.Rvr1_Pos2 && m_ExtSEnv2.TravDrive.DecelDogErr.Rvr2_Pos1)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:56535: INT08U Check_Rvs_DecelPos_Setup(INT08U nInvertor)`
  - `Core/Src/dev_SRM.c:56605: if (Check_Rvs_DecelPos_Setup(INV_TRAVEL))`
  - `Core/Src/dev_SRM.c:56663: if (Check_Rvs_DecelPos_Setup(INV_HOIST))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Scan_Decelation_Area_Proc

- **종류**: 함수
- **시그니처**: `void Scan_Decelation_Area_Proc()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:56572: void Scan_Decelation_Area_Proc()`
  - `Core/Src/dev_SRM.c:58561: Scan_Decelation_Area_Proc();//ì§ê¸ ì´ë ê°ìêµ¬ê°ì¸ì§ íë¨`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ForceMode_Manage_Proc

- **종류**: 함수
- **시그니처**: `void ForceMode_Manage_Proc()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:56693: void ForceMode_Manage_Proc()`
  - `Core/Src/dev_SRM.c:58563: ForceMode_Manage_Proc();//ê°ì ëª¨ë ìëí´ì  + fcd ì¶ë ¥`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Manual_Output_Manage_Proc

- **종류**: 함수
- **시그니처**: `void Manual_Output_Manage_Proc()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:56756: void Manual_Output_Manage_Proc()`
  - `Core/Src/dev_SRM.c:58565: Manual_Output_Manage_Proc();//ìëì¶ë ¥ ìíëª¨ë ê´ë¦¬(ìë<->ìë ì íì do ì ë¦¬)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Station_CVOK

- **종류**: 함수
- **시그니처**: `INT08U Check_Station_CVOK(INT08U nStatinNo)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:56828: INT08U Check_Station_CVOK(INT08U nStatinNo)`
  - `Core/Inc/dev_SRM.h:2375: INT08U Check_Station_CVOK(INT08U nStatinNo);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Station_CVOK_Rev2

- **종류**: 함수
- **시그니처**: `INT08U Check_Station_CVOK_Rev2(INT08U nStatinNo)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:33373: if (Check_Station_CVOK_Rev2(m_St.PosFork1.St_No))`
  - `Core/Src/dev_SRM.c:33461: if (Check_Station_CVOK_Rev2(m_St.PosFork1.St_No))`
  - `Core/Src/dev_SRM.c:33527: if (Check_Station_CVOK_Rev2(m_St.PosFork1.St_No))`
  - `Core/Src/dev_SRM.c:33616: if (Check_Station_CVOK_Rev2(m_St.PosFork1.St_No))`
  - `Core/Src/dev_SRM.c:34568: if (Check_Station_CVOK_Rev2(m_St.PosFork1.St_No))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_AutoMode_Station_CVOK_Rev2

- **종류**: 함수
- **시그니처**: `INT08U Check_AutoMode_Station_CVOK_Rev2(INT08U nStatinNo, INT08U nForkJob)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:57079: INT08U Check_AutoMode_Station_CVOK_Rev2(INT08U nStatinNo, INT08U nForkJob)`
  - `Core/Src/dev_SRM.c:60508: if (Check_AutoMode_Station_CVOK_Rev2(m_WorkData[s_WorkInx].Station_No, m_WorkData[s_WorkInx].ForkAct`
  - `Core/Src/dev_SRM.c:61185: if (Check_AutoMode_Station_CVOK_Rev2(m_WorkData[s_WorkInx].Station_No, m_WorkData[s_WorkInx].ForkAct`
  - `Core/Inc/dev_SRM.h:2377: INT08U Check_AutoMode_Station_CVOK_Rev2(INT08U nStatinNo, INT08U nForkJob);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Man_ForkOut_Station_CVOK

- **종류**: 함수
- **시그니처**: `INT08U Check_Man_ForkOut_Station_CVOK(INT08U nStatinNo)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:57242: INT08U Check_Man_ForkOut_Station_CVOK(INT08U nStatinNo)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Get_Station_Interlock_CVNO_State

- **종류**: 함수
- **시그니처**: `INT08U Get_Station_Interlock_CVNO_State(INT08U nStatinNo)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: 인터록: 스테이션/CV OK 대기. 타임아웃→ERROR1_STATION_INTERLOCK_TIMEOUT.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:57297: INT08U Get_Station_Interlock_CVNO_State(INT08U nStatinNo)`
  - `Core/Src/dev_SRM.c:58706: if (Get_Station_Interlock_CVNO_State(i))`
  - `Core/Inc/dev_SRM.h:2378: INT08U Get_Station_Interlock_CVNO_State(INT08U nStatinNo);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Clear_Station_Interlock_Contol

- **종류**: 함수
- **시그니처**: `void Clear_Station_Interlock_Contol()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: 인터록: 스테이션/CV OK 대기. 타임아웃→ERROR1_STATION_INTERLOCK_TIMEOUT.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:57342: void Clear_Station_Interlock_Contol()`
  - `Core/Src/dev_SRM.c:58690: Clear_Station_Interlock_Contol();`
  - `Core/Src/dev_SRM.c:58714: Clear_Station_Interlock_Contol();`
  - `Core/Inc/dev_SRM.h:2379: void Clear_Station_Interlock_Contol();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Station_Interlock_Control

- **종류**: 함수
- **시그니처**: `void Station_Interlock_Control(INT08U nStatinNo, INT08U nFlag)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: 인터록: 스테이션/CV OK 대기. 타임아웃→ERROR1_STATION_INTERLOCK_TIMEOUT.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:57352: void Station_Interlock_Control(INT08U nStatinNo, INT08U nFlag)`
  - `Core/Src/dev_SRM.c:58686: Station_Interlock_Control(m_pgmEnv.Station_Error_No, 0);`
  - `Core/Src/dev_SRM.c:58708: Station_Interlock_Control(m_St.PosFork1.St_No, 0);`
  - `Core/Src/dev_SRM.c:62510: Station_Interlock_Control(m_WorkData[s_WorkInx].Station_No, 0);`
  - `Core/Inc/dev_SRM.h:2380: void Station_Interlock_Control(INT08U nStatinNo, INT08U nFlag);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Station_Manual_Interlock_Control

- **종류**: 함수
- **시그니처**: `void Station_Manual_Interlock_Control(INT08U nStatinNo, INT08U nFlag)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: 인터록: 스테이션/CV OK 대기. 타임아웃→ERROR1_STATION_INTERLOCK_TIMEOUT.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:35066: Station_Manual_Interlock_Control(m_St.PosFork1.St_No, 1);`
  - `Core/Src/dev_SRM.c:35239: Station_Manual_Interlock_Control(m_St.PosFork1.St_No, 1);`
  - `Core/Src/dev_SRM.c:35392: Station_Manual_Interlock_Control(m_St.PosFork1.St_No, 0);`
  - `Core/Src/dev_SRM.c:36620: Station_Manual_Interlock_Control(m_St.PosFork1.St_No, 1);`
  - `Core/Src/dev_SRM.c:36981: Station_Manual_Interlock_Control(m_St.PosFork1.St_No, 1);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Station_AutoMode_Interlock_Control

- **종류**: 함수
- **시그니처**: `void Station_AutoMode_Interlock_Control(INT08U nStatinNo, INT08U nFlag, INT08U nForkJob)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: 인터록: 스테이션/CV OK 대기. 타임아웃→ERROR1_STATION_INTERLOCK_TIMEOUT.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:57578: void Station_AutoMode_Interlock_Control(INT08U nStatinNo, INT08U nFlag, INT08U nForkJob)`
  - `Core/Src/dev_SRM.c:60511: Station_AutoMode_Interlock_Control(m_WorkData[s_WorkInx].Station_No, 1, m_WorkData[s_WorkInx].ForkAc`
  - `Core/Src/dev_SRM.c:61106: Station_AutoMode_Interlock_Control(m_WorkData[s_WorkInx].Station_No, 0, m_WorkData[s_WorkInx].ForkAc`
  - `Core/Src/dev_SRM.c:61188: Station_AutoMode_Interlock_Control(m_WorkData[s_WorkInx].Station_No, 1, m_WorkData[s_WorkInx].ForkAc`
  - `Core/Src/dev_SRM.c:61810: Station_AutoMode_Interlock_Control(m_WorkData[s_WorkInx].Station_No, 0, m_WorkData[s_WorkInx].ForkAc`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_St_ForkOut_DSTx

- **종류**: 함수
- **시그니처**: `INT08U Check_St_ForkOut_DSTx(INT08U nStationNo, INT08U nDir)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:57760: INT08U Check_St_ForkOut_DSTx(INT08U nStationNo, INT08U nDir)`
  - `Core/Inc/dev_SRM.h:2382: INT08U Check_St_ForkOut_DSTx(INT08U nStationNo, INT08U nDir);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_St_ForkOut_DSTx_1

- **종류**: 함수
- **시그니처**: `INT08U Check_St_ForkOut_DSTx_1(INT08U nStationNo)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:11808: if ((Check_St_ForkOut_DSTx_1(i)) == 0)`
  - `Core/Src/dev_SRM.c:11949: if ((Check_St_ForkOut_DSTx_1(i)) == 0)`
  - `Core/Src/dev_SRM.c:12797: if ((Check_St_ForkOut_DSTx_1(i)) == 0)`
  - `Core/Src/dev_SRM.c:12938: if ((Check_St_ForkOut_DSTx_1(i)) == 0)`
  - `Core/Src/dev_SRM.c:13790: if ((Check_St_ForkOut_DSTx_1(i)) == 0)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_DSTx_Sensor

- **종류**: 함수
- **시그니처**: `INT08U Check_DSTx_Sensor(INT08U nFork, INT08U nDir)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:12085: if (Check_DSTx_Sensor(POS_FORK_1, FORK_MOVE_LEFT))`
  - `Core/Src/dev_SRM.c:12190: if (Check_DSTx_Sensor(POS_FORK_1, FORK_MOVE_RIGHT))`
  - `Core/Src/dev_SRM.c:13082: if (Check_DSTx_Sensor(POS_FORK_1, FORK_MOVE_LEFT))`
  - `Core/Src/dev_SRM.c:13187: if (Check_DSTx_Sensor(POS_FORK_1, FORK_MOVE_RIGHT))`
  - `Core/Src/dev_SRM.c:14059: if (Check_DSTx_Sensor(POS_FORK_1, FORK_MOVE_LEFT))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

