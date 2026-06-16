# Vol.07 — dev_SRM.c 함수 (11)

> 생성일: 2026-06-16 | MX SRM App Ver 4.4 | 소스 미수정

상태머신 함수.

---

### Check_DSTxR_Sensor

- **종류**: 함수
- **시그니처**: `INT08U Check_DSTxR_Sensor(INT08U nFork, INT08U nDir)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:58022: INT08U Check_DSTxR_Sensor(INT08U nFork, INT08U nDir)`
  - `Core/Src/dev_SRM.c:61268: if (Check_DSTxR_Sensor(POS_FORK_1, FORK_MOVE_LEFT))  nDstState = 5;`
  - `Core/Src/dev_SRM.c:61285: if (Check_DSTxR_Sensor(POS_FORK_1, FORK_MOVE_RIGHT))  nDstState = 6;`
  - `Core/Inc/dev_SRM.h:2385: INT08U Check_DSTxR_Sensor(INT08U nFork, INT08U nDir);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_ODSTx_Sensor

- **종류**: 함수
- **시그니처**: `INT08U Check_ODSTx_Sensor(INT08U nFork, INT08U nDir)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:58087: INT08U Check_ODSTx_Sensor(INT08U nFork, INT08U nDir)`
  - `Core/Src/dev_SRM.c:60550: if (Check_ODSTx_Sensor(POS_FORK_1, FORK_MOVE_LEFT))  nFlag = 1;`
  - `Core/Src/dev_SRM.c:60554: if (Check_ODSTx_Sensor(POS_FORK_1, FORK_MOVE_RIGHT))  nFlag = 2;`
  - `Core/Src/dev_SRM.c:61886: if (Check_ODSTx_Sensor(POS_FORK_1, FORK_MOVE_LEFT))  nFlag = 1;`
  - `Core/Src/dev_SRM.c:61890: if (Check_ODSTx_Sensor(POS_FORK_1, FORK_MOVE_RIGHT))  nFlag = 2;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_ForkOut_After_MoveLift_ForkSensor

- **종류**: 함수
- **시그니처**: `INT08U Check_ForkOut_After_MoveLift_ForkSensor(INT08U nForkOpMode)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:58152: INT08U Check_ForkOut_After_MoveLift_ForkSensor(INT08U nForkOpMode)`
  - `Core/Src/dev_SRM.c:60924: if (Check_ForkOut_After_MoveLift_ForkSensor(s_Fork_Oper_Mode))`
  - `Core/Src/dev_SRM.c:61672: if (Check_ForkOut_After_MoveLift_ForkSensor(s_Fork_Oper_Mode))`
  - `Core/Src/dev_SRM.c:62214: if (Check_ForkOut_After_MoveLift_ForkSensor(s_Fork_Oper_Mode))`
  - `Core/Src/dev_SRM.c:62322: if (Check_ForkOut_After_MoveLift_ForkSensor(s_Fork_Oper_Mode))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Update_Invertor_Param

- **종류**: 함수
- **시그니처**: `void Update_Invertor_Param()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:58285: void Update_Invertor_Param()`
  - `Core/Src/dev_SRM.c:58667: Update_Invertor_Param();	// Reference Offset, Position Gain, Position Window ê° ê°±ì`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_SetupMode_Position_Ctr_Proc

- **종류**: 함수
- **시그니처**: `void SRM_SetupMode_Position_Ctr_Proc(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:58408: void SRM_SetupMode_Position_Ctr_Proc(void)`
  - `Core/Src/dev_SRM.c:58567: SRM_SetupMode_Position_Ctr_Proc();//ìì ìì¹ì´ë íì© 10ë¶ íìììë§ ê´ë¦¬`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_Machine_Run_Process

- **종류**: 함수
- **시그니처**: `void SRM_Machine_Run_Process()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **인근 주석**: íë³µê·, ë³´ììì¹ ì´ë ìë
- **용도(읽는 법)**: 헤더 주석: íë³µê·, ë³´ììì¹ ì´ë ìë
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:58437: void SRM_Machine_Run_Process()`
  - `Core/Src/dev_SRM.c:67954: SRM_Machine_Run_Process();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_Machine_State_Process

- **종류**: 함수
- **시그니처**: `void SRM_Machine_State_Process()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:63535: void SRM_Machine_State_Process()`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_Machine_Process

- **종류**: 함수
- **시그니처**: `void SRM_Machine_Process(INT08U nSEW_Connection_Flag)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **인근 주석**: Scan_DigitalInput();
- **용도(읽는 법)**: 헤더 주석: Scan_DigitalInput();
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:63555: void SRM_Machine_Process(INT08U nSEW_Connection_Flag)`
  - `Core/Src/dev_SRM.c:67950: SRM_Machine_Process(s_now_SSR);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Change_DeviceMode

- **종류**: 함수
- **시그니처**: `void Change_DeviceMode(INT08U nMode, INT08U nFoced)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/alarm.c:492: Change_DeviceMode(DEVICE_MANUAL_MODE, 1);`
  - `Core/Src/alarm.c:513: Change_DeviceMode(DEVICE_MANUAL_MODE, 1);`
  - `Core/Src/alarm.c:1429: Change_DeviceMode(DEVICE_MANUAL_MODE, 1);`
  - `Core/Src/com_tml.c:3184: Change_DeviceMode(DEVICE_MANUAL_MODE, 0);`
  - `Core/Src/com_tml.c:3188: Change_DeviceMode(DEVICE_SETUP_MODE, 0);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Init_RealTime_Register

- **종류**: 함수
- **시그니처**: `void Init_RealTime_Register() { if (m_ExtSEnv.Machine.mType.Fork_Count == 1)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:64086: void Init_RealTime_Register()`
  - `Core/Src/dev_SRM.c:65501: Init_RealTime_Register();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Update_RealTime_Register

- **종류**: 함수
- **시그니처**: `void Update_RealTime_Register()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:64113: void Update_RealTime_Register()`
  - `Core/Src/dev_SRM.c:65514: Update_RealTime_Register();`
  - `Core/Inc/dev_SRM.h:2389: void Update_RealTime_Register();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HMI_Com_Process

- **종류**: 함수
- **시그니처**: `INT08U HMI_Com_Process()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **인근 주석**: INT16U nCom_Interval = 1000; INT16U nCom_Interval = 500;
- **용도(읽는 법)**: 헤더 주석: INT16U nCom_Interval = 1000; INT16U nCom_Interval = 500;
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:65462: INT08U HMI_Com_Process()`
  - `Core/Src/dev_SRM.c:65946: if (HMI_Com_Process())`
  - `Core/Src/dev_SRM.c:66087: if (HMI_Com_Process())`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HMI_UpLink_ModbusTCP_Manager

- **종류**: 함수
- **시그니처**: `void HMI_UpLink_ModbusTCP_Manager()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_udp.c:678: *         연결 시작은 HMI_UpLink_ModbusTCP_Manager() case 1 에서 담당`
  - `Core/Src/com_udp.c:693: *   HMI_UpLink_ModbusTCP_Manager() case 1 에서 명시적으로 호출 */`
  - `Core/Src/com_udp.c:702: *   tcp_client_connect() 호출 권한은 호출자(HMI_UpLink_ModbusTCP_Manager 등)에게 있음.`
  - `Core/Src/com_udp.c:815: *         기존 HMI_UpLink_ModbusTCP_Manager() 의 s_now_SSR 값과 1:1 매핑`
  - `Core/Src/com_udp.c:844: *         HMI_UpLink_ModbusTCP_Manager() case 1 에서 명시적으로 호출`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HMI_DownLink_ModbusTCP_Manager

- **종류**: 함수
- **시그니처**: `void HMI_DownLink_ModbusTCP_Manager()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:65996: void HMI_DownLink_ModbusTCP_Manager()`
  - `Core/Src/dev_SRM.c:66157: s_fpPosition = HMI_DownLink_ModbusTCP_Manager;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HMI_ModbusTCP_Proc

- **종류**: 함수
- **시그니처**: `void HMI_ModbusTCP_Proc()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:66136: void HMI_ModbusTCP_Proc()`
  - `Core/Src/dev_SRM.c:67956: HMI_ModbusTCP_Proc();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HMI_Press_Manual_Ctr_Button

- **종류**: 함수
- **시그니처**: `void HMI_Press_Manual_Ctr_Button(INT16U nButton) { switch (nButton)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:66167: void HMI_Press_Manual_Ctr_Button(INT16U nButton)`
  - `Core/Src/dev_SRM.c:66333: HMI_Press_Manual_Ctr_Button(i);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HMI_Release_Manual_Ctr_Button

- **종류**: 함수
- **시그니처**: `void HMI_Release_Manual_Ctr_Button(INT16U nButton) { switch (nButton)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:66229: void HMI_Release_Manual_Ctr_Button(INT16U nButton)`
  - `Core/Src/dev_SRM.c:66277: HMI_Release_Manual_Ctr_Button(i);`
  - `Core/Src/dev_SRM.c:66340: HMI_Release_Manual_Ctr_Button(i);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_HMI_Manual_Control

- **종류**: 함수
- **시그니처**: `void SRM_HMI_Manual_Control(HMI_Regi_MW0 nEventKey, INT08U nStopFlag)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:66264: void SRM_HMI_Manual_Control(HMI_Regi_MW0 nEventKey, INT08U nStopFlag)`
  - `Core/Src/dev_SRM.c:66567: SRM_HMI_Manual_Control(m_HMI_Com.ControlFlag.MW0, 0);`
  - `Core/Src/dev_SRM.c:66573: SRM_HMI_Manual_Control(m_HMI_Com.ControlFlag.MW0, 0);`
  - `Core/Src/dev_SRM.c:66639: SRM_HMI_Manual_Control(m_HMI_Com.ControlFlag.MW0, 1);`
  - `Core/Src/dev_SRM.c:66649: SRM_HMI_Manual_Control(m_HMI_Com.ControlFlag.MW0, 1);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HMI_Press_Key_Button

- **종류**: 함수
- **시그니처**: `void HMI_Press_Key_Button(INT16U nButton) { switch (nButton) { case HMI_MANUAL_KEY2_DB_START: if (m_St.SRM_Status1.Bit.StartOn)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:66351: void HMI_Press_Key_Button(INT16U nButton)`
  - `Core/Src/dev_SRM.c:66492: HMI_Press_Key_Button(i);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HMI_Release_Key_Button

- **종류**: 함수
- **시그니처**: `void HMI_Release_Key_Button(INT16U nButton) { switch (nButton)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:66419: void HMI_Release_Key_Button(INT16U nButton)`
  - `Core/Src/dev_SRM.c:66498: HMI_Release_Key_Button(i);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_HMI_Key_Proc

- **종류**: 함수
- **시그니처**: `void SRM_HMI_Key_Proc()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:66463: void SRM_HMI_Key_Proc()`
  - `Core/Src/dev_SRM.c:66618: SRM_HMI_Key_Proc();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_HMI_Manual_Control_Proc

- **종류**: 함수
- **시그니처**: `void SRM_HMI_Manual_Control_Proc(INT08U nNow_SSR)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:65987: SRM_HMI_Manual_Control_Proc(s_now_SSR);`
  - `Core/Src/dev_SRM.c:66128: SRM_HMI_Manual_Control_Proc(s_now_SSR);`
  - `Core/Src/dev_SRM.c:66506: void SRM_HMI_Manual_Control_Proc(INT08U nNow_SSR)`
  - `Core/Inc/dev_SRM.h:2390: void SRM_HMI_Manual_Control_Proc(INT08U nNow_SSR);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_Normal_Stop

- **종류**: 함수
- **시그니처**: `void SRM_Normal_Stop(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:5325: SRM_Normal_Stop();`
  - `Core/Src/dev_SRM.c:66378: SRM_Normal_Stop();`
  - `Core/Src/dev_SRM.c:66673: void SRM_Normal_Stop(void)`
  - `Core/Inc/dev_SRM.h:2391: void SRM_Normal_Stop(void);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_Emergency_Stop

- **종류**: 함수
- **시그니처**: `void SRM_Emergency_Stop(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:5339: SRM_Emergency_Stop();`
  - `Core/Src/dev_SRM.c:52123: SRM_Emergency_Stop();`
  - `Core/Src/dev_SRM.c:52216: SRM_Emergency_Stop();`
  - `Core/Src/dev_SRM.c:66693: void SRM_Emergency_Stop(void)`
  - `Core/Inc/dev_SRM.h:2392: void SRM_Emergency_Stop(void);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_Return_Home

- **종류**: 함수
- **시그니처**: `INT08U SRM_Return_Home(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: HOME/RETURN: 원점복귀 vs 에러복귀 RunMode 혼재. grep으로 확인.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2907: result = SRM_Return_Home();`
  - `Core/Src/dev_SRM.c:66394: SRM_Return_Home();`
  - `Core/Src/dev_SRM.c:66744: INT08U SRM_Return_Home(void)`
  - `Core/Inc/dev_SRM.h:2393: INT08U SRM_Return_Home(void);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

