# Vol.07 — dev_SRM.c 함수 (9)

> 생성일: 2026-06-16 | MX SRM App Ver 4.4 | 소스 미수정

상태머신 함수.

---

### Check_Order_Prohibit_Rack_1

- **종류**: 함수
- **시그니처**: `INT08U Check_Order_Prohibit_Rack_1(INT08U OrderCode, ForkWorkCmdSTR* ForkWorkCmd)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:51266: INT08U Check_Order_Prohibit_Rack_1(INT08U OrderCode, ForkWorkCmdSTR* ForkWorkCmd)`
  - `Core/Src/dev_SRM.c:67308: if (Check_Order_Prohibit_Rack_1(nDemoCmd.OrderCode, (ForkWorkCmdSTR*)&nDemoCmd.Fork[0]))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Task_Prohibit_Rack

- **종류**: 함수
- **시그니처**: `INT08U Check_Task_Prohibit_Rack(INT08U nTaskCmd, CellPosSTR* pCellPos)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: Task: TML 0x40 다중작업. 0x41과 분기 다름.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2260: if (Check_Task_Prohibit_Rack(pCmd->TaskWork[i].Cmd, &pCmd->TaskWork[i].TargetPos))`
  - `Core/Src/dev_SRM.c:51342: INT08U Check_Task_Prohibit_Rack(INT08U nTaskCmd, CellPosSTR* pCellPos)`
  - `Core/Inc/dev_SRM.h:2357: INT08U Check_Task_Prohibit_Rack(INT08U nTaskCmd, CellPosSTR* pCellPos);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Special_Rack

- **종류**: 함수
- **시그니처**: `INT08U Check_Special_Rack(CellPosSTR* ptrCell, INT08U nCmdGoodsType)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:33422: if (Check_Special_Rack(&nCurPos, m_St.Inv_St[INV_FORK_1].U.Loaded_GoodType))`
  - `Core/Src/dev_SRM.c:33576: if (Check_Special_Rack(&nCurPos, m_St.Inv_St[INV_FORK_1].U.Loaded_GoodType))`
  - `Core/Src/dev_SRM.c:34594: if (Check_Special_Rack(&nCurPos, m_St.Inv_St[INV_FORK_1].U.Loaded_GoodType))`
  - `Core/Src/dev_SRM.c:34662: if (Check_Special_Rack(&nCurPos, m_St.Inv_St[INV_FORK_1].U.Loaded_GoodType))`
  - `Core/Src/dev_SRM.c:35883: if (Check_Special_Rack(&nCurPos, m_St.Inv_St[INV_FORK_1].U.Loaded_GoodType))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Order_Special_Rack

- **종류**: 함수
- **시그니처**: `INT08U Check_Order_Special_Rack(INT08U OrderCode, ForkWorkCmdSTR* ForkWorkCmd)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2510: accept[0] = Check_Order_Special_Rack(pCmd->OrderCode, (ForkWorkCmdSTR*)&pCmd->Fork[0]);`
  - `Core/Src/com_tml.c:2568: if (Check_Order_Special_Rack(pCmd->OrderCode, (ForkWorkCmdSTR*)&pCmd->Fork[0]))`
  - `Core/Src/com_tml.c:2608: if (Check_Order_Special_Rack(pCmd->OrderCode, (ForkWorkCmdSTR*)&pCmd->Fork[0]))`
  - `Core/Src/com_tml.c:2639: if (Check_Order_Special_Rack(pCmd->OrderCode, (ForkWorkCmdSTR*)&pCmd->Fork[0]))`
  - `Core/Src/dev_SRM.c:51432: INT08U Check_Order_Special_Rack(INT08U OrderCode, ForkWorkCmdSTR* ForkWorkCmd)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Task_Special_Rack

- **종류**: 함수
- **시그니처**: `INT08U Check_Task_Special_Rack(INT08U nTaskCmd, CellPosSTR* pCellPos, INT08U nGoodType)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: Task: TML 0x40 다중작업. 0x41과 분기 다름.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2265: if (Check_Task_Special_Rack(pCmd->TaskWork[i].Cmd, \`
  - `Core/Src/dev_SRM.c:51490: INT08U Check_Task_Special_Rack(INT08U nTaskCmd, CellPosSTR* pCellPos, INT08U nGoodType)`
  - `Core/Inc/dev_SRM.h:2360: INT08U Check_Task_Special_Rack(INT08U nTaskCmd, CellPosSTR* pCellPos, INT08U nGoodType);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Update_Operation_Info_Time

- **종류**: 함수
- **시그니처**: `void Update_Operation_Info_Time(INT08U nItem, INT32U nOperationTime_ms)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:51511: void Update_Operation_Info_Time(INT08U nItem, INT32U nOperationTime_ms)`
  - `Core/Src/dev_SRM.c:51950: Update_Operation_Info_Time(i, getCalcTimer1ms(s_OperateTimer[i]));`
  - `Core/Src/dev_SRM.c:52027: Update_Operation_Info_Time(3, getCalcTimer1ms(s_OperateTimer[3]));`
  - `Core/Src/dev_SRM.c:62187: Update_Operation_Info_Time(INV_HOIST, getCalcTimer1ms(s_Lift_Move_Timer));`
  - `Core/Inc/dev_SRM.h:2362: void Update_Operation_Info_Time(INT08U nInvertor, INT32U nOperationTime_ms);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Update_Operation_Info_Distance

- **종류**: 함수
- **시그니처**: `void Update_Operation_Info_Distance(INT08U nItem, INT32U nOperDistance_mm)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:51533: void Update_Operation_Info_Distance(INT08U nItem, INT32U nOperDistance_mm)`
  - `Core/Src/dev_SRM.c:51949: Update_Operation_Info_Distance(i, s_OperateDistance[i]);`
  - `Core/Src/dev_SRM.c:60896: Update_Operation_Info_Distance(INV_HOIST, s_Lift_MoveDistance);`
  - `Core/Src/dev_SRM.c:62186: Update_Operation_Info_Distance(INV_HOIST, s_Lift_MoveDistance);`
  - `Core/Inc/dev_SRM.h:2363: void Update_Operation_Info_Distance(INT08U nInvertor, INT32U nOperDistance_mm);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Update_BrakeOpen_CountUp

- **종류**: 함수
- **시그니처**: `void Update_BrakeOpen_CountUp(INT08U nInvertor) { if (m_BKSram.OperationInfo.BrakeOpen_Count[nInvertor] < 0xFFFFFFFF)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:51551: void Update_BrakeOpen_CountUp(INT08U nInvertor)`
  - `Core/Src/dev_SRM.c:51972: Update_BrakeOpen_CountUp(i);`
  - `Core/Inc/dev_SRM.h:2365: void Update_BrakeOpen_CountUp(INT08U nInvertor);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Read_DelayTime

- **종류**: 함수
- **시그니처**: `INT32U Read_DelayTime(INT08U nForkAct, INT08U nTimerIndex)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:41645: s_Delay_Time = Read_DelayTime(pWorkData->ForkAct, DELAY_AFTER_FORK_CENTER);`
  - `Core/Src/dev_SRM.c:41683: s_Delay_Time = Read_DelayTime(pWorkData->ForkAct, DELAY_AFTER_FORK_OUT);`
  - `Core/Src/dev_SRM.c:42582: s_Delay_Time = Read_DelayTime(pWorkData->ForkAct, DELAY_AFTER_FORK_CENTER);`
  - `Core/Src/dev_SRM.c:42631: s_Delay_Time = Read_DelayTime(pWorkData->ForkAct, DELAY_AFTER_FORK_OUT);`
  - `Core/Src/dev_SRM.c:51560: INT32U Read_DelayTime(INT08U nForkAct, INT08U nTimerIndex)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Get_Stabilzation_Time

- **종류**: 함수
- **시그니처**: `INT32U Get_Stabilzation_Time(SRM_WorkDataSTR* pWorkData)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:51658: INT32U Get_Stabilzation_Time(SRM_WorkDataSTR* pWorkData)`
  - `Core/Src/dev_SRM.c:59398: s_Delay_Time = Get_Stabilzation_Time(&m_WorkData[s_WorkInx]);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Get_OverTime_Auto

- **종류**: 함수
- **시그니처**: `INT32U Get_OverTime_Auto(INT08U nTimerIndex)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:51704: INT32U Get_OverTime_Auto(INT08U nTimerIndex)`
  - `Core/Src/dev_SRM.c:55292: s_Move_TimeOut = Get_OverTime_Auto(AUTO_TIMEOUT_MOVE_TRAV_LIFT);`
  - `Core/Src/dev_SRM.c:55839: s_Move_TimeOut = Get_OverTime_Auto(AUTO_TIMEOUT_MOVE_TRAV_LIFT);`
  - `Core/Src/dev_SRM.c:55971: s_Move_TimeOver = Get_OverTime_Auto(AUTO_TIMEOUT_MOVE_TRAV_LIFT);`
  - `Core/Src/dev_SRM.c:56465: s_Move_TimeOver = Get_OverTime_Auto(AUTO_TIMEOUT_MOVE_TRAV_LIFT);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Get_OverTime_Drive

- **종류**: 함수
- **시그니처**: `INT32U Get_OverTime_Drive(INT08U nTimerIndex)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:51749: INT32U Get_OverTime_Drive(INT08U nTimerIndex)`
  - `Core/Src/dev_SRM.c:58910: s_Over_Time = Get_OverTime_Drive(DRIVE_TIMEOUT_HOME_RETURN);//íë³µê· ìµëíì©ìê° ì ì¥`
  - `Core/Src/dev_SRM.c:61069: s_Over_Time = Get_OverTime_Drive(DRIVE_TIMEOUT_HOME_RETURN);`
  - `Core/Src/dev_SRM.c:62474: s_Over_Time = Get_OverTime_Drive(DRIVE_TIMEOUT_HOME_RETURN);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Update_Maintanance_SRM_Setting_Data

- **종류**: 함수
- **시그니처**: `void Update_Maintanance_SRM_Setting_Data(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:4824: Update_Maintanance_SRM_Setting_Data();`
  - `Core/Src/com_tml.c:4980: Update_Maintanance_SRM_Setting_Data();`
  - `Core/Src/com_tml.c:4986: Update_Maintanance_SRM_Setting_Data();`
  - `Core/Src/com_tml.c:5151: Update_Maintanance_SRM_Setting_Data();`
  - `Core/Src/com_tml.c:5157: Update_Maintanance_SRM_Setting_Data();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Update_Maintanance_SRM_Touqe

- **종류**: 함수
- **시그니처**: `void Update_Maintanance_SRM_Touqe(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:51841: void Update_Maintanance_SRM_Touqe(void)`
  - `Core/Src/dev_SRM.c:52044: Update_Maintanance_SRM_Touqe();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Clear_Operation_Info_Data

- **종류**: 함수
- **시그니처**: `void Clear_Operation_Info_Data()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:930: Clear_Operation_Info_Data();`
  - `Core/Src/com_tml.c:1459: Clear_Operation_Info_Data();`
  - `Core/Src/dev_SRM.c:51851: void Clear_Operation_Info_Data()`
  - `Core/Inc/dev_SRM.h:2367: void Clear_Operation_Info_Data();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Operation_Information_Proc

- **종류**: 함수
- **시그니처**: `void Operation_Information_Proc()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:51858: void Operation_Information_Proc()`
  - `Core/Src/dev_SRM.c:58557: Operation_Information_Proc();//ì´íê±°ë¦¬ ì´íìê° ë¸ë ì´í¬ íì ëì (ì§ê³ì©)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_CP_Safety_Plug_Proc

- **종류**: 함수
- **시그니처**: `void SRM_CP_Safety_Plug_Proc()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:52076: void SRM_CP_Safety_Plug_Proc()`
  - `Core/Src/dev_SRM.c:52312: SRM_CP_Safety_Plug_Proc();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_CP_EmergencySwitch_Proc

- **종류**: 함수
- **시그니처**: `void SRM_CP_EmergencySwitch_Proc()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:52165: void SRM_CP_EmergencySwitch_Proc()`
  - `Core/Src/dev_SRM.c:52313: SRM_CP_EmergencySwitch_Proc();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_CP_ResetSwitch_Proc

- **종류**: 함수
- **시그니처**: `void SRM_CP_ResetSwitch_Proc()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:52246: void SRM_CP_ResetSwitch_Proc()`
  - `Core/Src/dev_SRM.c:52314: SRM_CP_ResetSwitch_Proc();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_CP_Switch_Proc

- **종류**: 함수
- **시그니처**: `void SRM_CP_Switch_Proc()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:52310: void SRM_CP_Switch_Proc()`
  - `Core/Src/dev_SRM.c:58559: SRM_CP_Switch_Proc();//ìì íë¬ê·¸, ë¹ìì ì§, ë¦¬ì ì¤ìì¹ ì²ë¦¬`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Scan_Travel_Position_Sensor

- **종류**: 함수
- **시그니처**: `void Scan_Travel_Position_Sensor()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:52323: void Scan_Travel_Position_Sensor()`
  - `Core/Src/dev_SRM.c:63343: Scan_Travel_Position_Sensor();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Scan_Lift_Position_Sensor

- **종류**: 함수
- **시그니처**: `void Scan_Lift_Position_Sensor()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:52760: void Scan_Lift_Position_Sensor()`
  - `Core/Src/dev_SRM.c:63369: Scan_Lift_Position_Sensor();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Scan_Fork_Position_Sensor

- **종류**: 함수
- **시그니처**: `void Scan_Fork_Position_Sensor()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **인근 주석**: static INT32U s_OperationTime = 0;
- **용도(읽는 법)**: 헤더 주석: static INT32U s_OperationTime = 0;
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:53193: void Scan_Fork_Position_Sensor()`
  - `Core/Src/dev_SRM.c:63395: Scan_Fork_Position_Sensor();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Travel_Setup_Move_Position_Start

- **종류**: 함수
- **시그니처**: `void Travel_Setup_Move_Position_Start(INT32S nTargetPosition)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:1178: Travel_Setup_Move_Position_Start((INT32S)pCtrl->Value);`
  - `Core/Src/dev_SRM.c:54072: void Travel_Setup_Move_Position_Start(INT32S nTargetPosition)`
  - `Core/Inc/dev_SRM.h:2368: void Travel_Setup_Move_Position_Start(INT32S nTargetPosition);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Travel_Setup_Move_Bay_Start

- **종류**: 함수
- **시그니처**: `void Travel_Setup_Move_Bay_Start(INT32S nTargetPosition)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:1202: Travel_Setup_Move_Bay_Start((INT32S)pCtrl->Value);`
  - `Core/Src/dev_SRM.c:54161: void Travel_Setup_Move_Bay_Start(INT32S nTargetPosition)`
  - `Core/Inc/dev_SRM.h:2369: void Travel_Setup_Move_Bay_Start(INT32S nTargetPosition);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

