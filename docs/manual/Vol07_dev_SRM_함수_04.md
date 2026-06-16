# Vol.07 — dev_SRM.c 함수 (4)

> 생성일: 2026-06-16 | MX SRM App Ver 4.4 | 소스 미수정

상태머신 함수.

---

### ModbusTCP_Com_Manager

- **종류**: 함수
- **시그니처**: `void ModbusTCP_Com_Manager()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6876: void ModbusTCP_Com_Manager()`
  - `Core/Src/dev_SRM.c:68071: ModbusTCP_Com_Manager();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Write_EtherCAT_Output

- **종류**: 함수
- **시그니처**: `INT08U Write_EtherCAT_Output(INT08U nSlaveID, INT08U nPin, INT08U nFlag)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6967: INT08U Write_EtherCAT_Output(INT08U nSlaveID, INT08U nPin, INT08U nFlag)`
  - `Core/Src/dev_SRM.c:7072: nWriteFlag = Write_EtherCAT_Output(m_DIO_SetInfo.Set.DO_Set[nPort].Type, \`
  - `Core/Src/dev_SRM.c:7109: nWriteFlag = Write_EtherCAT_Output(m_DIO_SetInfo.Set.DO_Set2[nPort_Index].Type, \`
  - `Core/Src/dev_SRM.c:7223: nWriteFlag = Write_EtherCAT_Output(m_DIO_SetInfo.Set.DO_Set[nPort].Type, \`
  - `Core/Src/dev_SRM.c:7261: nWriteFlag = Write_EtherCAT_Output(m_DIO_SetInfo.Set.DO_Set2[nPort_Index].Type, \`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DO_Control

- **종류**: 함수
- **시그니처**: `void DO_Control(INT08U nPort, INT08U nFlag)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/alarm.c:959: DO_Control(OUT_LED_RD, 0);	// R`
  - `Core/Src/alarm.c:960: DO_Control(OUT_LED_GR, 0);	// G`
  - `Core/Src/alarm.c:961: DO_Control(OUT_LED_BU, 0);	// B`
  - `Core/Src/alarm.c:964: DO_Control(OUT_LED_RD, 1);		// R`
  - `Core/Src/alarm.c:965: DO_Control(OUT_LED_GR, 0);		// G`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DO_Control_Manual

- **종류**: 함수
- **시그니처**: `void DO_Control_Manual(INT08U nPort, INT08U nFlag)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:1987: DO_Control_Manual(i, nControl);`
  - `Core/Src/com_tml.c:1993: DO_Control_Manual(nID - 1, nControl);`
  - `Core/Src/dev_SRM.c:7131: void DO_Control_Manual(INT08U nPort, INT08U nFlag)`
  - `Core/Inc/dev_SRM.h:60: void DO_Control_Manual(INT08U nPort, INT08U nFlag);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DO_Control_Init

- **종류**: 함수
- **시그니처**: `void DO_Control_Init()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:7296: void DO_Control_Init()`
  - `Core/Src/ecat_main.c:4306: DO_Control_Init();`
  - `Core/Inc/dev_SRM.h:61: void DO_Control_Init();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Read_EtherCAT_Input

- **종류**: 함수
- **시그니처**: `INT08U Read_EtherCAT_Input(INT08U nSlaveID, INT08U nPin)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:7312: INT08U Read_EtherCAT_Input(INT08U nSlaveID, INT08U nPin)`
  - `Core/Src/dev_SRM.c:7454: nReadInputState = Read_EtherCAT_Input(nSlaveIndex, nPin);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Get_DI_State

- **종류**: 함수
- **시그니처**: `INT08U Get_DI_State(INT08U nPort)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/alarm.c:1381: if (Get_DI_State(IN_AUTO) && (Get_DI_State(IN_INSP) == 0))`
  - `Core/Src/alarm.c:1386: if (Get_DI_State(IN_INSP) && (Get_DI_State(IN_AUTO) == 0))`
  - `Core/Src/alarm.c:1393: Get_DI_State(IN_AUTO) ? (nCur_Manual_SW = 1) : (nCur_Manual_SW = 0);`
  - `Core/Src/alarm.c:1450: m_TestStatus.Ctrl[DEBUG_CTR_1] = Get_DI_State(IN_AUTO);`
  - `Core/Src/alarm.c:1451: m_TestStatus.Ctrl[DEBUG_CTR_2] = Get_DI_State(IN_INSP);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Get_DI_UseFlag

- **종류**: 함수
- **시그니처**: `INT08U Get_DI_UseFlag(INT08U nPort)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/alarm.c:1379: if (Get_DI_UseFlag(IN_AUTO) && Get_DI_UseFlag(IN_INSP))`
  - `Core/Src/alarm.c:1391: else if (Get_DI_UseFlag(IN_AUTO))`
  - `Core/Src/dev_SRM.c:7744: INT08U Get_DI_UseFlag(INT08U nPort)`
  - `Core/Src/dev_SRM.c:7889: (Get_DI_UseFlag(i)) ? (s_DI_UseFlag[i] = 1) : (s_DI_UseFlag[i] = 0);`
  - `Core/Src/dev_SRM.c:9320: if (Get_DI_UseFlag(IN_FCL1))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Get_DO_UseFlag

- **종류**: 함수
- **시그니처**: `INT08U Get_DO_UseFlag(INT08U nPort)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:7021: if (Get_DO_UseFlag(nPort) == 0)`
  - `Core/Src/dev_SRM.c:7786: INT08U Get_DO_UseFlag(INT08U nPort)`
  - `Core/Src/dev_SRM.c:9852: if (Get_DO_UseFlag(OUT_FK1_JOG) \`
  - `Core/Src/dev_SRM.c:9853: && Get_DO_UseFlag(OUT_FK1_JOG_L) && Get_DO_UseFlag(OUT_FK1_JOG_R))`
  - `Core/Src/dev_SRM.c:43902: if (Get_DO_UseFlag(OUT_FK1_STO1))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Scan_Digital_Input

- **종류**: 함수
- **시그니처**: `void Scan_Digital_Input(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:7816: void Scan_Digital_Input(void)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Get_DI_FilterTime

- **종류**: 함수
- **시그니처**: `INT08U Get_DI_FilterTime(INT08U nPort)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:7841: INT08U Get_DI_FilterTime(INT08U nPort)`
  - `Core/Src/dev_SRM.c:7902: s_InputChatteing[i] = Get_DI_FilterTime(i);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Scan_Digital_Input_Chattering

- **종류**: 함수
- **시그니처**: `void Scan_Digital_Input_Chattering(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:7862: void Scan_Digital_Input_Chattering(void)`
  - `Core/Src/dev_SRM.c:67948: Scan_Digital_Input_Chattering();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Get_DI_State_Filter

- **종류**: 함수
- **시그니처**: `INT08U Get_DI_State_Filter(INT08U nPort)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:5274: if (Get_DI_State_Filter(IN_TDF))`
  - `Core/Src/dev_SRM.c:5283: if (Get_DI_State_Filter(IN_TDR))`
  - `Core/Src/dev_SRM.c:5292: if (Get_DI_State_Filter(IN_THP))`
  - `Core/Src/dev_SRM.c:5303: if (Get_DI_State_Filter(IN_LDU))`
  - `Core/Src/dev_SRM.c:5312: if (Get_DI_State_Filter(IN_LDD))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Get_DO_State

- **종류**: 함수
- **시그니처**: `INT08U Get_DO_State(INT08U nPort)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:7978: INT08U Get_DO_State(INT08U nPort)`
  - `Core/Src/dev_SRM.c:9855: if (Get_DO_State(OUT_FK1_JOG))`
  - `Core/Src/dev_SRM.c:9857: if ((Get_DO_State(OUT_FK1_JOG_L) == 1) && (Get_DO_State(OUT_FK1_JOG_R) == 0))`
  - `Core/Src/dev_SRM.c:9861: else if ((Get_DO_State(OUT_FK1_JOG_L) == 0) && (Get_DO_State(OUT_FK1_JOG_R) == 1))`
  - `Core/Src/dev_SRM.c:57311: if (Get_DO_State(OUT_CVNO1 + nInterLock_No))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_Travel_Reference_Start

- **종류**: 함수
- **시그니처**: `void SRM_Travel_Reference_Start()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:8054: void SRM_Travel_Reference_Start()`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_Travel_Reference_Process

- **종류**: 함수
- **시그니처**: `void SRM_Travel_Reference_Process()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:8064: void SRM_Travel_Reference_Process()`
  - `Core/Src/dev_SRM.c:63279: SRM_Travel_Reference_Process();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_Lift_Reference_Start

- **종류**: 함수
- **시그니처**: `void SRM_Lift_Reference_Start()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:8403: void SRM_Lift_Reference_Start()`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_Lift_Reference_Process

- **종류**: 함수
- **시그니처**: `void SRM_Lift_Reference_Process()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:8413: void SRM_Lift_Reference_Process()`
  - `Core/Src/dev_SRM.c:63298: SRM_Lift_Reference_Process();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_Fork_Reference_Start

- **종류**: 함수
- **시그니처**: `void SRM_Fork_Reference_Start() { } /** * @brief * @param None * @retval None */ void SRM_Fork_Reference_Process()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:8721: void SRM_Fork_Reference_Start()`
  - `Core/Inc/dev_SRM.h:71: void SRM_Fork_Reference_Start();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Fork_OriginSensor

- **종류**: 함수
- **시그니처**: `INT08U Check_Fork_OriginSensor()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:8869: if (Check_Fork_OriginSensor())`
  - `Core/Src/dev_SRM.c:8964: if (Check_Fork_OriginSensor())`
  - `Core/Src/dev_SRM.c:8993: if (Check_Fork_OriginSensor() == 0)`
  - `Core/Src/dev_SRM.c:9029: if (Check_Fork_OriginSensor())`
  - `Core/Src/dev_SRM.c:9310: * @brief	Check_Fork_OriginSensor`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Fork_CenterSensor

- **종류**: 함수
- **시그니처**: `INT08U Check_Fork_CenterSensor()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:9347: * @brief	Check_Fork_CenterSensor`
  - `Core/Src/dev_SRM.c:9351: INT08U Check_Fork_CenterSensor()`
  - `Core/Src/dev_SRM.c:9892: if (Check_Fork_CenterSensor())`
  - `Core/Src/dev_SRM.c:10679: if (Check_Fork_CenterSensor())`
  - `Core/Src/dev_SRM.c:41443: if (Check_Fork_CenterSensor())`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Fork_Center_State

- **종류**: 함수
- **시그니처**: `INT08U Check_Fork_Center_State()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:9408: * @brief	Check_Fork_Center_State`
  - `Core/Src/dev_SRM.c:9412: INT08U Check_Fork_Center_State()`
  - `Core/Inc/dev_SRM.h:74: INT08U Check_Fork_Center_State();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Fork_Status

- **종류**: 함수
- **시그니처**: `void Check_Fork_Status()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **인근 주석**: static INT32S s_PreForkPos;
- **용도(읽는 법)**: 헤더 주석: static INT32S s_PreForkPos;
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:9720: void Check_Fork_Status()`
  - `Core/Src/dev_SRM.c:58555: Check_Fork_Status(); // í¬í¬ ìì¹ ì¤ì¬ ê¹ì´ ì¸í¬ì§ì ê°±ì`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Create_Reference_Position

- **종류**: 함수
- **시그니처**: `void Create_Reference_Position()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:3848: Create_Reference_Position();`
  - `Core/Src/com_tml.c:4105: Create_Reference_Position();`
  - `Core/Src/dev_SRM.c:10822: void Create_Reference_Position()`
  - `Core/Src/main.c:397: Create_Reference_Position();`
  - `Core/Inc/dev_SRM.h:75: void Create_Reference_Position();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Fork_Out_Enable_State_Blank

- **종류**: 함수
- **시그니처**: `void Check_Fork_Out_Enable_State_Blank()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:11715: void Check_Fork_Out_Enable_State_Blank()`
  - `Core/Src/dev_SRM.c:22131: s_fpForkEnable = Check_Fork_Out_Enable_State_Blank;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

