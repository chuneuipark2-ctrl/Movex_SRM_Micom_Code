# Vol.07 — dev_SRM.c 함수 (5)

> 생성일: 2026-06-16 | MX SRM App Ver 4.4 | 소스 미수정

상태머신 함수.

---

### Check_Fork_Out_Enable_State

- **종류**: 함수
- **시그니처**: `void Check_Fork_Out_Enable_State()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:11720: void Check_Fork_Out_Enable_State()`
  - `Core/Src/dev_SRM.c:22026: s_fpForkEnable = Check_Fork_Out_Enable_State;`
  - `Core/Src/dev_SRM.c:22050: s_fpForkEnable = Check_Fork_Out_Enable_State;`
  - `Core/Src/dev_SRM.c:22058: s_fpForkEnable = Check_Fork_Out_Enable_State;`
  - `Core/Src/dev_SRM.c:22100: s_fpForkEnable = Check_Fork_Out_Enable_State;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Fork_Out_Enable_State_1

- **종류**: 함수
- **시그니처**: `void Check_Fork_Out_Enable_State_1()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:12709: void Check_Fork_Out_Enable_State_1()`
  - `Core/Src/dev_SRM.c:22065: s_fpForkEnable = Check_Fork_Out_Enable_State_1;`
  - `Core/Src/dev_SRM.c:22072: s_fpForkEnable = Check_Fork_Out_Enable_State_1;`
  - `Core/Src/dev_SRM.c:22079: s_fpForkEnable = Check_Fork_Out_Enable_State_1;`
  - `Core/Src/dev_SRM.c:22086: s_fpForkEnable = Check_Fork_Out_Enable_State_1;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Fork_Out_Enable_State_2

- **종류**: 함수
- **시그니처**: `void Check_Fork_Out_Enable_State_2()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:13697: void Check_Fork_Out_Enable_State_2()`
  - `Core/Src/dev_SRM.c:22096: s_fpForkEnable = Check_Fork_Out_Enable_State_2;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Travel_Hoist_Motor_State

- **종류**: 함수
- **시그니처**: `void Check_Travel_Hoist_Motor_State()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:14683: void Check_Travel_Hoist_Motor_State()`
  - `Core/Src/dev_SRM.c:15752: Check_Travel_Hoist_Motor_State();`
  - `Core/Src/dev_SRM.c:16839: Check_Travel_Hoist_Motor_State();`
  - `Core/Src/dev_SRM.c:17412: Check_Travel_Hoist_Motor_State();`
  - `Core/Src/dev_SRM.c:18049: Check_Travel_Hoist_Motor_State();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Travel_Hoist_Position_State

- **종류**: 함수
- **시그니처**: `void Check_Travel_Hoist_Position_State()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:14879: void Check_Travel_Hoist_Position_State()`
  - `Core/Src/dev_SRM.c:17096: Check_Travel_Hoist_Position_State();`
  - `Core/Src/dev_SRM.c:17679: Check_Travel_Hoist_Position_State();`
  - `Core/Src/dev_SRM.c:18319: Check_Travel_Hoist_Position_State();`
  - `Core/Src/dev_SRM.c:19006: Check_Travel_Hoist_Position_State();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Trav_Lift_Position_No_Site_Blank

- **종류**: 함수
- **시그니처**: `void Check_Trav_Lift_Position_No_Site_Blank(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:15609: void Check_Trav_Lift_Position_No_Site_Blank(void)`
  - `Core/Src/dev_SRM.c:22130: s_fpPosition = Check_Trav_Lift_Position_No_Site_Blank;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Trav_Lift_Position_No_Site_5

- **종류**: 함수
- **시그니처**: `void Check_Trav_Lift_Position_No_Site_5(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **인근 주석**: m_pgmEnv.Pos_X_Left, m_pgmEnv.Pos_Y_Left, StationNo
- **용도(읽는 법)**: 헤더 주석: m_pgmEnv.Pos_X_Left, m_pgmEnv.Pos_Y_Left, StationNo
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:15614: void Check_Trav_Lift_Position_No_Site_5(void)`
  - `Core/Src/dev_SRM.c:22025: s_fpPosition = Check_Trav_Lift_Position_No_Site_5;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Trav_Lift_Position_No_Site_8

- **종류**: 함수
- **시그니처**: `void Check_Trav_Lift_Position_No_Site_8(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:16553: void Check_Trav_Lift_Position_No_Site_8(void)`
  - `Core/Src/dev_SRM.c:22049: s_fpPosition = Check_Trav_Lift_Position_No_Site_8;`
  - `Core/Src/dev_SRM.c:22122: s_fpPosition = Check_Trav_Lift_Position_No_Site_8;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Trav_Lift_Position_No_Site_9

- **종류**: 함수
- **시그니처**: `void Check_Trav_Lift_Position_No_Site_9(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:17102: void Check_Trav_Lift_Position_No_Site_9(void)`
  - `Core/Src/dev_SRM.c:22057: s_fpPosition = Check_Trav_Lift_Position_No_Site_9;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Trav_Lift_Position_No_Site_10

- **종류**: 함수
- **시그니처**: `void Check_Trav_Lift_Position_No_Site_10(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:17685: void Check_Trav_Lift_Position_No_Site_10(void)`
  - `Core/Src/dev_SRM.c:22064: s_fpPosition = Check_Trav_Lift_Position_No_Site_10;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Trav_Lift_Position_No_Site_11

- **종류**: 함수
- **시그니처**: `void Check_Trav_Lift_Position_No_Site_11(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:18325: void Check_Trav_Lift_Position_No_Site_11(void)`
  - `Core/Src/dev_SRM.c:22071: s_fpPosition = Check_Trav_Lift_Position_No_Site_11;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Trav_Lift_Position_No_Site_12

- **종류**: 함수
- **시그니처**: `void Check_Trav_Lift_Position_No_Site_12(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:19012: void Check_Trav_Lift_Position_No_Site_12(void)`
  - `Core/Src/dev_SRM.c:22092: s_fpPosition = Check_Trav_Lift_Position_No_Site_12;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Trav_Lift_Position_No_Site_13

- **종류**: 함수
- **시그니처**: `void Check_Trav_Lift_Position_No_Site_13(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:19603: void Check_Trav_Lift_Position_No_Site_13(void)`
  - `Core/Src/dev_SRM.c:22107: s_fpPosition = Check_Trav_Lift_Position_No_Site_13;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Trav_Lift_Position_No_Site_15

- **종류**: 함수
- **시그니처**: `void Check_Trav_Lift_Position_No_Site_15(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:20154: void Check_Trav_Lift_Position_No_Site_15(void)`
  - `Core/Src/dev_SRM.c:22078: s_fpPosition = Check_Trav_Lift_Position_No_Site_15;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Trav_Lift_Position_No_Site_16

- **종류**: 함수
- **시그니처**: `void Check_Trav_Lift_Position_No_Site_16(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:20831: void Check_Trav_Lift_Position_No_Site_16(void)`
  - `Core/Src/dev_SRM.c:22085: s_fpPosition = Check_Trav_Lift_Position_No_Site_16;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Trav_Lift_Position_No_Site_17

- **종류**: 함수
- **시그니처**: `void Check_Trav_Lift_Position_No_Site_17(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:21436: void Check_Trav_Lift_Position_No_Site_17(void)`
  - `Core/Src/dev_SRM.c:22115: s_fpPosition = Check_Trav_Lift_Position_No_Site_17;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Trav_Lift_Postion_State_Proc

- **종류**: 함수
- **시그니처**: `void Check_Trav_Lift_Postion_State_Proc(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:22005: void Check_Trav_Lift_Postion_State_Proc(void)`
  - `Core/Src/dev_SRM.c:58553: Check_Trav_Lift_Postion_State_Proc(); //íì¬ bay/level/station ìì¹ ê³ì° ê°±ì`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Control_Manual_Trav_Start

- **종류**: 함수
- **시그니처**: `INT08U Control_Manual_Trav_Start(INT08U mode, INT08U nOriginStandard)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:5513: nResult = Control_Manual_Trav_Start(pCom->Data[2], pCom->Data[17]);`
  - `Core/Src/dev_SRM.c:29640: INT08U Control_Manual_Trav_Start(INT08U mode, INT08U nOriginStandard)`
  - `Core/Inc/dev_SRM.h:2318: INT08U Control_Manual_Trav_Start(INT08U mode, INT08U nOriginStandard);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Control_Manual_Lift_Start

- **종류**: 함수
- **시그니처**: `INT08U Control_Manual_Lift_Start(INT08U mode, INT08U nOriginStandard)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:5519: nResult = Control_Manual_Lift_Start(pCom->Data[3], pCom->Data[17]);`
  - `Core/Src/dev_SRM.c:29816: INT08U Control_Manual_Lift_Start(INT08U mode, INT08U nOriginStandard)`
  - `Core/Inc/dev_SRM.h:2320: INT08U Control_Manual_Lift_Start(INT08U mode, INT08U nOriginStandard);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Control_Manual_Fork_Start

- **종류**: 함수
- **시그니처**: `INT08U Control_Manual_Fork_Start(INT08U mode)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:5526: nResult = Control_Manual_Fork_Start(pCom->Data[4]);`
  - `Core/Src/dev_SRM.c:29996: INT08U Control_Manual_Fork_Start(INT08U mode)`
  - `Core/Inc/dev_SRM.h:2321: INT08U Control_Manual_Fork_Start(INT08U mode);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HMI_Control_Manual_Trav_Start

- **종류**: 함수
- **시그니처**: `INT08U HMI_Control_Manual_Trav_Start(INT08U mode)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:30144: INT08U HMI_Control_Manual_Trav_Start(INT08U mode)`
  - `Core/Src/dev_SRM.c:66172: HMI_Control_Manual_Trav_Start(MANUAL_CTR_TRAV_FWD_LOW);`
  - `Core/Src/dev_SRM.c:66176: HMI_Control_Manual_Trav_Start(MANUAL_CTR_TRAV_RVS_LOW);`
  - `Core/Src/dev_SRM.c:66180: HMI_Control_Manual_Trav_Start(MANUAL_CTR_TRAV_FWD_MID);`
  - `Core/Src/dev_SRM.c:66184: HMI_Control_Manual_Trav_Start(MANUAL_CTR_TRAV_RVS_MID);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HMI_Control_Manual_Lift_Start

- **종류**: 함수
- **시그니처**: `INT08U HMI_Control_Manual_Lift_Start(INT08U mode)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:30295: INT08U HMI_Control_Manual_Lift_Start(INT08U mode)`
  - `Core/Src/dev_SRM.c:66188: HMI_Control_Manual_Lift_Start(MANUAL_CTR_LIFT_UP_LOW);`
  - `Core/Src/dev_SRM.c:66192: HMI_Control_Manual_Lift_Start(MANUAL_CTR_LIFT_DOWN_LOW);`
  - `Core/Src/dev_SRM.c:66196: HMI_Control_Manual_Lift_Start(MANUAL_CTR_LIFT_UP_MID);`
  - `Core/Src/dev_SRM.c:66200: HMI_Control_Manual_Lift_Start(MANUAL_CTR_LIFT_DOWN_MID);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HMI_Control_Manual_Fork_Start

- **종류**: 함수
- **시그니처**: `INT08U HMI_Control_Manual_Fork_Start(INT08U mode)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:30487: INT08U HMI_Control_Manual_Fork_Start(INT08U mode)`
  - `Core/Src/dev_SRM.c:66204: HMI_Control_Manual_Fork_Start(MANUAL_CTR_FORK_CENTER);`
  - `Core/Src/dev_SRM.c:66208: HMI_Control_Manual_Fork_Start(MANUAL_CTR_FORK_LEFT);`
  - `Core/Src/dev_SRM.c:66212: HMI_Control_Manual_Fork_Start(MANUAL_CTR_FORK_RIGHT);`
  - `Core/Src/dev_SRM.c:66251: HMI_Control_Manual_Fork_Start(MANUAL_CTR_FORK_STOP);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Manual_Control_Trav_Proc

- **종류**: 함수
- **시그니처**: `void Manual_Control_Trav_Proc(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **인근 주석**: INT08U flag;
- **용도(읽는 법)**: 헤더 주석: INT08U flag;
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:30583: void Manual_Control_Trav_Proc(void)`
  - `Core/Src/dev_SRM.c:37207: Manual_Control_Trav_Proc();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Manual_Control_Lift_Proc

- **종류**: 함수
- **시그니처**: `void Manual_Control_Lift_Proc(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **인근 주석**: INT08U flag;
- **용도(읽는 법)**: 헤더 주석: INT08U flag;
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:31679: void Manual_Control_Lift_Proc(void)`
  - `Core/Src/dev_SRM.c:37211: Manual_Control_Lift_Proc();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

