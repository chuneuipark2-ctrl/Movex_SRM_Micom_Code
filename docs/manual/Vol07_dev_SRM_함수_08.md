# Vol.07 — dev_SRM.c 함수 (8)

> 생성일: 2026-06-16 | MX SRM App Ver 4.4 | 소스 미수정

상태머신 함수.

---

### Check_Fork_Center_Position

- **종류**: 함수
- **시그니처**: `INT08U Check_Fork_Center_Position(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:29730: if (Check_Fork_Center_Position())`
  - `Core/Src/dev_SRM.c:29734: Event_Warning_Code(WARNING_CODE_1, Check_Fork_Center_Position(), 0);`
  - `Core/Src/dev_SRM.c:32105: if (Check_Fork_Center_Position())`
  - `Core/Src/dev_SRM.c:32109: Event_Warning_Code(WARNING_CODE_2, Check_Fork_Center_Position(), 0);`
  - `Core/Src/dev_SRM.c:32170: if (Check_Fork_Center_Position())`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Fork_Center_Alarm

- **종류**: 함수
- **시그니처**: `INT08U Check_Fork_Center_Alarm(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2226: else if (Check_Fork_Center_Alarm())`
  - `Core/Src/com_tml.c:2378: else if (Check_Fork_Center_Alarm())`
  - `Core/Src/com_tml.c:2754: if (Check_Fork_Center_Alarm() == 0)`
  - `Core/Src/com_tml.c:2787: if (Check_Fork_Center_Alarm() == 0)`
  - `Core/Src/com_tml.c:2976: if (Check_Fork_Center_Alarm())//포크가 센터가 아닐때`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Trav_lift_In_Postion

- **종류**: 함수
- **시그니처**: `INT08U Check_Trav_lift_In_Postion(INT32S nWorkInx) { if ((m_St.Inv_St[INV_TRAVEL].Current_Pos >= (m_WorkData[nWorkInx].DrvData[INV_TRAVEL].TargetPos - DEF_POSITION_OFFSET)) && (m_St.Inv_St[INV_TRAVEL].Current_Pos <= (m_WorkData[nWorkInx].DrvData[INV_TRAVEL].TargetPos + DEF_POSITION_OFFSET)) && (m_St.Inv_St[INV_HOIST].Current_Pos >= (m_WorkData[nWorkInx].DrvData[INV_HOIST].TargetPos - DEF_POSITION_OFFSET)) && (m_St.Inv_St[INV_HOIST].Current_Pos <= (m_WorkData[nWorkInx].DrvData[INV_HOIST].TargetPos + DEF_POSITION_OFFSET)))`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:48019: INT08U Check_Trav_lift_In_Postion(INT32S nWorkInx)`
  - `Core/Src/dev_SRM.c:58973: if (Check_Trav_lift_In_Postion(s_WorkInx))//ì£¼í ì¹ê° ì¸í¬ì§ìê° ì²´í¬ê° ì¼ì§ë©´`
  - `Core/Src/dev_SRM.c:59146: if (Check_Trav_lift_In_Postion(s_WorkInx))// ì¸í¬ì§ìê° ì²´í¬`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Trav_Move_Dir

- **종류**: 함수
- **시그니처**: `INT08U Check_Trav_Move_Dir(INT32S nWorkInx)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:48034: INT08U Check_Trav_Move_Dir(INT32S nWorkInx)`
  - `Core/Src/dev_SRM.c:58981: m_WorkData[s_WorkInx].DrvData[INV_TRAVEL].Move_Dir = Check_Trav_Move_Dir(s_WorkInx);`
  - `Core/Src/dev_SRM.c:59028: m_WorkData[s_WorkInx].DrvData[INV_TRAVEL].Move_Dir = Check_Trav_Move_Dir(s_WorkInx);`
  - `Core/Src/dev_SRM.c:63124: m_WorkData[s_WorkInx].DrvData[INV_TRAVEL].Move_Dir = Check_Trav_Move_Dir(s_WorkInx);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Lift_Move_Dir

- **종류**: 함수
- **시그니처**: `INT08U Check_Lift_Move_Dir(INT32S nWorkInx)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:48056: INT08U Check_Lift_Move_Dir(INT32S nWorkInx)`
  - `Core/Src/dev_SRM.c:58982: m_WorkData[s_WorkInx].DrvData[INV_HOIST].Move_Dir = Check_Lift_Move_Dir(s_WorkInx);`
  - `Core/Src/dev_SRM.c:59029: m_WorkData[s_WorkInx].DrvData[INV_HOIST].Move_Dir = Check_Lift_Move_Dir(s_WorkInx);`
  - `Core/Src/dev_SRM.c:63125: m_WorkData[s_WorkInx].DrvData[INV_HOIST].Move_Dir = Check_Lift_Move_Dir(s_WorkInx);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Move_Complete

- **종류**: 함수
- **시그니처**: `INT08U Check_Move_Complete(INT08U invertor, INT32S s_WorkInx)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:48078: INT08U Check_Move_Complete(INT08U invertor, INT32S s_WorkInx)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### check_inverter_In_position_reach

- **종류**: 함수
- **시그니처**: `INT08U check_inverter_In_position_reach(INT08U inverter, INT32S Target_Pos)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: 인버터/EtherCAT 상태. m_ExtSEnv와 함께 확인.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:42066: if (check_inverter_In_position_reach(INV_FORK_1, nTarget_Depth))`
  - `Core/Src/dev_SRM.c:43103: if (check_inverter_In_position_reach(INV_FORK_1, nTarget_Depth))`
  - `Core/Src/dev_SRM.c:48097: INT08U check_inverter_In_position_reach(INT08U inverter, INT32S Target_Pos)`
  - `Core/Src/dev_SRM.c:52433: if (check_inverter_In_position_reach(INV_TRAVEL, s_Move_TargetPos))`
  - `Core/Src/dev_SRM.c:52557: if (check_inverter_In_position_reach(INV_TRAVEL, s_Move_TargetPos))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Fork_InPosition

- **종류**: 함수
- **시그니처**: `INT08U Check_Fork_InPosition(INT32S nTarget_Position)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:42137: if (Check_Fork_InPosition(nTarget_Depth))`
  - `Core/Src/dev_SRM.c:43175: if (Check_Fork_InPosition(nTarget_Depth))`
  - `Core/Src/dev_SRM.c:48375: INT08U Check_Fork_InPosition(INT32S nTarget_Position)`
  - `Core/Inc/dev_SRM.h:2344: INT08U Check_Fork_InPosition(INT32S nTarget_Position);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Set_LastPosition

- **종류**: 함수
- **시그니처**: `void Set_LastPosition(INT08U nFlag)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:48410: void Set_LastPosition(INT08U nFlag)`
  - `Core/Inc/dev_SRM.h:2346: void Set_LastPosition(INT08U nFlag);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Modem_Alarm

- **종류**: 함수
- **시그니처**: `void Check_Modem_Alarm() { if (m_ExtSEnv2.CtrParam.LaserModem_AlarmFlag) { if (Get_DI_State(IN_MFLT))`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:48443: void Check_Modem_Alarm()`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Modem_Alarm_1

- **종류**: 함수
- **시그니처**: `INT08U Check_Modem_Alarm_1(INT08U nCheckFlag) { if (nCheckFlag) { if (Get_DI_State(IN_MFLT))`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:48467: INT08U Check_Modem_Alarm_1(INT08U nCheckFlag)`
  - `Core/Src/dev_SRM.c:49429: if (Check_Modem_Alarm_1(0))`
  - `Core/Src/dev_SRM.c:49650: if (Check_Modem_Alarm_1(1))`
  - `Core/Src/dev_SRM.c:49785: if (Check_Modem_Alarm_1(1))`
  - `Core/Src/dev_SRM.c:49923: if (Check_Modem_Alarm_1(0))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_PDoor_Alarm

- **종류**: 함수
- **시그니처**: `INT08U Check_PDoor_Alarm(INT08U nCheckFlag)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:48508: INT08U Check_PDoor_Alarm(INT08U nCheckFlag)`
  - `Core/Src/dev_SRM.c:49434: if (Check_PDoor_Alarm(1))`
  - `Core/Src/dev_SRM.c:49656: if (Check_PDoor_Alarm(1))`
  - `Core/Src/dev_SRM.c:49790: if (Check_PDoor_Alarm(1))`
  - `Core/Src/dev_SRM.c:49928: if (Check_PDoor_Alarm(1))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Invertor_Fault

- **종류**: 함수
- **시그니처**: `INT08U Check_Invertor_Fault()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:48561: INT08U Check_Invertor_Fault()`
  - `Core/Src/dev_SRM.c:49348: if (Check_Invertor_Fault())`
  - `Core/Src/dev_SRM.c:63732: Check_Invertor_Fault();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Trav_Software_Limit

- **종류**: 함수
- **시그니처**: `INT08U Check_Trav_Software_Limit(INT32S nPostion) { if (m_ExtSEnv2.TravDrive.SoftLimitErr.CheckFlag & cbits[0]) { if (nPostion < m_ExtSEnv2.TravDrive.SoftLimitErr.HomePos \ - m_ExtSEnv2.TravDrive.InPos_Tolerance - m_ExtSEnv2.TravDrive.InPos_Hysteresis)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:2109: if (Check_Trav_Software_Limit(position))`
  - `Core/Src/dev_SRM.c:2198: if (Check_Trav_Software_Limit(position))`
  - `Core/Src/dev_SRM.c:48739: INT08U Check_Trav_Software_Limit(INT32S nPostion)`
  - `Core/Src/dev_SRM.c:49773: nErrorReason = Check_Trav_Software_Limit(m_St.Inv_St[INV_TRAVEL].Current_Pos);`
  - `Core/Inc/dev_SRM.h:2349: INT08U Check_Trav_Software_Limit(INT32S nPostion);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Lift_Software_Limit

- **종류**: 함수
- **시그니처**: `INT08U Check_Lift_Software_Limit(INT32S nPosition) { if (m_ExtSEnv2.LiftDrive.SoftLimitErr.CheckFlag & cbits[0]) { if (nPosition < m_ExtSEnv2.LiftDrive.SoftLimitErr.HomePos \ - m_ExtSEnv2.LiftDrive.InPos_Tolerance - m_ExtSEnv2.LiftDrive.InPos_Hysteresis)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:2534: if(Check_Lift_Software_Limit(position))`
  - `Core/Src/dev_SRM.c:2621: if (Check_Lift_Software_Limit(position))`
  - `Core/Src/dev_SRM.c:3751: if (Check_Lift_Software_Limit(position))`
  - `Core/Src/dev_SRM.c:48767: INT08U Check_Lift_Software_Limit(INT32S nPosition)`
  - `Core/Src/dev_SRM.c:49755: nErrorReason = Check_Lift_Software_Limit(m_St.Inv_St[INV_HOIST].Current_Pos);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Trav_Home_Sensor_Position

- **종류**: 함수
- **시그니처**: `INT08U Check_Trav_Home_Sensor_Position()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: HOME/RETURN: 원점복귀 vs 에러복귀 RunMode 혼재. grep으로 확인.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:48825: INT08U Check_Trav_Home_Sensor_Position()`
  - `Core/Src/dev_SRM.c:49414: nErrorReason = Check_Trav_Home_Sensor_Position();`
  - `Core/Src/dev_SRM.c:49742: nErrorReason = Check_Trav_Home_Sensor_Position();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Lift_Home_Sensor_Position

- **종류**: 함수
- **시그니처**: `INT08U Check_Lift_Home_Sensor_Position()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: HOME/RETURN: 원점복귀 vs 에러복귀 RunMode 혼재. grep으로 확인.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:48869: INT08U Check_Lift_Home_Sensor_Position()`
  - `Core/Src/dev_SRM.c:49420: nErrorReason = Check_Lift_Home_Sensor_Position();`
  - `Core/Src/dev_SRM.c:49764: nErrorReason = Check_Lift_Home_Sensor_Position();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Limit_Alarm_State

- **종류**: 함수
- **시그니처**: `INT08U Check_Limit_Alarm_State(INT08U nInvertor)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **인근 주석**: INT32S nPosition = 0;
- **용도(읽는 법)**: 헤더 주석: INT32S nPosition = 0;
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:48914: INT08U Check_Limit_Alarm_State(INT08U nInvertor)`
  - `Core/Src/dev_SRM.c:49191: Check_Limit_Alarm_State(INV_TRAVEL);`
  - `Core/Src/dev_SRM.c:49192: Check_Limit_Alarm_State(INV_HOIST);`
  - `Core/Src/dev_SRM.c:49373: Check_Limit_Alarm_State(INV_TRAVEL);`
  - `Core/Src/dev_SRM.c:49374: Check_Limit_Alarm_State(INV_HOIST);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Roof_Alarm_State

- **종류**: 함수
- **시그니처**: `INT08U Check_Roof_Alarm_State() { if (Get_DI_State_Filter(IN_RTF))`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:49131: INT08U Check_Roof_Alarm_State()`
  - `Core/Src/dev_SRM.c:49193: Check_Roof_Alarm_State();`
  - `Core/Src/dev_SRM.c:49375: Check_Roof_Alarm_State();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Always_Error_Monitoring

- **종류**: 함수
- **시그니처**: `void Check_Always_Error_Monitoring()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:49156: void Check_Always_Error_Monitoring()`
  - `Core/Src/dev_SRM.c:50559: Check_Always_Error_Monitoring();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_SRM_Error_State

- **종류**: 함수
- **시그니처**: `INT08U Check_SRM_Error_State()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:8100: if (Check_SRM_Error_State())`
  - `Core/Src/dev_SRM.c:8449: if (Check_SRM_Error_State())`
  - `Core/Src/dev_SRM.c:8787: if (Check_SRM_Error_State())`
  - `Core/Src/dev_SRM.c:30691: if (Check_SRM_Error_State())`
  - `Core/Src/dev_SRM.c:31803: if (Check_SRM_Error_State())`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CheckCmdCellPosition

- **종류**: 함수
- **시그니처**: `INT08U CheckCmdCellPosition(INT08U OrderCode, ForkWorkCmdSTR* ForkWorkCmd)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2464: accept[0] = CheckCmdCellPosition(pCmd->OrderCode, (ForkWorkCmdSTR*)&pCmd->Fork[0]);`
  - `Core/Src/com_tml.c:2492: accept[0] = CheckCmdCellPosition(pCmd->OrderCode, (ForkWorkCmdSTR*)&pCmd->Fork[0]);`
  - `Core/Src/com_tml.c:2552: if (CheckCmdCellPosition(pCmd->OrderCode, (ForkWorkCmdSTR*)&pCmd->Fork[0]))`
  - `Core/Src/com_tml.c:2592: if (CheckCmdCellPosition(pCmd->OrderCode, (ForkWorkCmdSTR*)&pCmd->Fork[0]))`
  - `Core/Src/com_tml.c:2623: if (CheckCmdCellPosition(pCmd->OrderCode, (ForkWorkCmdSTR*)&pCmd->Fork[0]))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Task_CellPosition

- **종류**: 함수
- **시그니처**: `INT08U Check_Task_CellPosition(INT08U nCmd, CellPosSTR* CellPos)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: Task: TML 0x40 다중작업. 0x41과 분기 다름.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2255: if (Check_Task_CellPosition(pCmd->TaskWork[i].Cmd, &pCmd->TaskWork[i].TargetPos))`
  - `Core/Src/dev_SRM.c:50822: INT08U Check_Task_CellPosition(INT08U nCmd, CellPosSTR* CellPos)`
  - `Core/Inc/dev_SRM.h:2354: INT08U Check_Task_CellPosition(INT08U nCmd, CellPosSTR* CellPos);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Prohibit_Rack

- **종류**: 함수
- **시그니처**: `INT08U Check_Prohibit_Rack(CellPosSTR* ptrCell)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:12139: if (Check_Prohibit_Rack(&nTmpRackPostion))`
  - `Core/Src/dev_SRM.c:12244: if (Check_Prohibit_Rack(&nTmpRackPostion))`
  - `Core/Src/dev_SRM.c:12449: if (Check_Prohibit_Rack(&nTmpRackPostion))`
  - `Core/Src/dev_SRM.c:12459: if (Check_Prohibit_Rack(&nTmpRackPostion))`
  - `Core/Src/dev_SRM.c:12653: if (Check_Prohibit_Rack(&nTmpRackPostion))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Order_Prohibit_Rack

- **종류**: 함수
- **시그니처**: `INT08U Check_Order_Prohibit_Rack(INT08U OrderCode, ForkWorkCmdSTR* ForkWorkCmd)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2500: accept[0] = Check_Order_Prohibit_Rack(pCmd->OrderCode, (ForkWorkCmdSTR*)&pCmd->Fork[0]);`
  - `Core/Src/com_tml.c:2559: if (Check_Order_Prohibit_Rack(pCmd->OrderCode, (ForkWorkCmdSTR*)&pCmd->Fork[0]))`
  - `Core/Src/com_tml.c:2599: if (Check_Order_Prohibit_Rack(pCmd->OrderCode, (ForkWorkCmdSTR*)&pCmd->Fork[0]))`
  - `Core/Src/com_tml.c:2630: if (Check_Order_Prohibit_Rack(pCmd->OrderCode, (ForkWorkCmdSTR*)&pCmd->Fork[0]))`
  - `Core/Src/dev_SRM.c:51194: INT08U Check_Order_Prohibit_Rack(INT08U OrderCode, ForkWorkCmdSTR* ForkWorkCmd)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

