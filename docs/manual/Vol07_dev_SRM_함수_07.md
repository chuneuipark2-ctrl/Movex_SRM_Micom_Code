# Vol.07 — dev_SRM.c 함수 (7)

> 생성일: 2026-06-16 | MX SRM App Ver 4.4 | 소스 미수정

상태머신 함수.

---

### SRM_Machine_Init_Process

- **종류**: 함수
- **시그니처**: `void SRM_Machine_Init_Process(INT08U* pInit_Step)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **인근 주석**: static INT32U s_RunStep = 0;
- **용도(읽는 법)**: 헤더 주석: static INT32U s_RunStep = 0;
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:43503: void SRM_Machine_Init_Process(INT08U* pInit_Step)`
  - `Core/Src/dev_SRM.c:63576: SRM_Machine_Init_Process(&s_Init_RunStep);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_Machine_Init_Process_1

- **종류**: 함수
- **시그니처**: `void SRM_Machine_Init_Process_1(INT08U* pInit_Step)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:43632: void SRM_Machine_Init_Process_1(INT08U* pInit_Step)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_Machine_Init_Process_2

- **종류**: 함수
- **시그니처**: `void SRM_Machine_Init_Process_2(INT08U* pInit_Step)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:43728: void SRM_Machine_Init_Process_2(INT08U* pInit_Step)`
  - `Core/Src/dev_SRM.c:63587: SRM_Machine_Init_Process_2(&s_Init_RunStep);`
  - `Core/Src/dev_SRM.c:63591: SRM_Machine_Init_Process_2(&s_Init_RunStep);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_Machine_Init_Process_3

- **종류**: 함수
- **시그니처**: `void SRM_Machine_Init_Process_3(INT08U* pInit_Step)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:43821: void SRM_Machine_Init_Process_3(INT08U* pInit_Step)`
  - `Core/Src/dev_SRM.c:63582: SRM_Machine_Init_Process_3(&s_Init_RunStep);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_Machine_PowerOn_Process

- **종류**: 함수
- **시그니처**: `INT08U SRM_Machine_PowerOn_Process(INT08U* pRunStep)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:43987: INT08U SRM_Machine_PowerOn_Process(INT08U* pRunStep)`
  - `Core/Src/dev_SRM.c:63607: s_Init_Error = SRM_Machine_PowerOn_Process(&s_Init_RunStep);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_Machine_Drive_On_Process

- **종류**: 함수
- **시그니처**: `INT08U SRM_Machine_Drive_On_Process(INT08U* pRunStep)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:44132: INT08U SRM_Machine_Drive_On_Process(INT08U* pRunStep)`
  - `Core/Src/dev_SRM.c:63633: s_Init_Error = SRM_Machine_Drive_On_Process(&s_Init_RunStep);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_Machine_ManualMode_Proc

- **종류**: 함수
- **시그니처**: `INT08U SRM_Machine_ManualMode_Proc(INT08U* pRunStep)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:44418: INT08U SRM_Machine_ManualMode_Proc(INT08U* pRunStep)`
  - `Core/Src/dev_SRM.c:63658: s_Init_Error = SRM_Machine_ManualMode_Proc(&s_Init_RunStep);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Store_Fork_WorkStatus

- **종류**: 함수
- **시그니처**: `static void Store_Fork_WorkStatus(INT08U ForkNum, INT32U WorkNum, INT08U OrderCode, INT08U OrderStatus, INT08U OrderProcess) { if (OrderCode == ORDER_CODE_MOVE)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: Store_*: 작업 큐/버퍼 적재. Save와 구분.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:44877: static void Store_Fork_WorkStatus(INT08U ForkNum, INT32U WorkNum, INT08U OrderCode, INT08U OrderStat`
  - `Core/Src/dev_SRM.c:46682: Store_Fork_WorkStatus(0, pCmd->Fork[POS_FORK_1].WorkNum, pCmd->OrderCode, WORK_STATUS_DOING, CMD_MOV`
  - `Core/Src/dev_SRM.c:46686: Store_Fork_WorkStatus(0, 0, ORDER_CODE_NONE, WORK_STATUS_NONE, CMD_MOVE_STEP_NONE);`
  - `Core/Src/dev_SRM.c:46696: Store_Fork_WorkStatus(0, pCmd->Fork[POS_FORK_1].WorkNum, pCmd->OrderCode, WORK_STATUS_DOING, CMD_FOR`
  - `Core/Src/dev_SRM.c:46700: Store_Fork_WorkStatus(0, 0, ORDER_CODE_NONE, WORK_STATUS_NONE, CMD_FORK_STEP_NONE);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Store_Fork_Work_1

- **종류**: 함수
- **시그니처**: `static void Store_Fork_Work_1(INT08U ForkNum, INT32U WorkNum, INT08U OrderCode, INT08U OrderStatus, INT08U OrderProcess, CellPosSTR FromPos, CellPosSTR ToPos) { if (OrderCode == ORDER_CODE_MOVE)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: Store_*: 작업 큐/버퍼 적재. Save와 구분.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:44910: static void Store_Fork_Work_1(INT08U ForkNum, INT32U WorkNum, INT08U OrderCode, INT08U OrderStatus, `

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Store_Work_Data

- **종류**: 함수
- **시그니처**: `static void Store_Work_Data(INT32S TravPos, INT32S LiftPos, INT08U ForkAct, INT08U IsStation, \ INT08U Sta, INT08U Bay, INT08U Lvl, INT08U Step, INT16S Fork1Depth, INT16S Fork2Depth, INT08U GoodsType)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: Store_*: 작업 큐/버퍼 적재. Save와 구분.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:44936: static void Store_Work_Data(INT32S TravPos, INT32S LiftPos, INT08U ForkAct, INT08U IsStation, \`
  - `Core/Src/dev_SRM.c:45749: Store_Work_Data(to_tpos, to_lpos, WORK_MOVE_ONLY, 0, tp.Station, \`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Store_Work_Data_Fix

- **종류**: 함수
- **시그니처**: `static void Store_Work_Data_Fix(INT32S TravPos, INT32S LiftPos, INT08U ForkAct, INT08U IsStation, \ CellPosSTR nPos, INT08U Step, INT16S Fork1Depth, INT16S Fork2Depth, INT08U GoodsType, INT08U nOperFlag)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: Store_*: 작업 큐/버퍼 적재. Save와 구분.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:44994: static void Store_Work_Data_Fix(INT32S TravPos, INT32S LiftPos, INT08U ForkAct, INT08U IsStation, \`
  - `Core/Src/dev_SRM.c:45560: Store_Work_Data_Fix(to_tpos, to_lpos, WORK_MOVE_ONLY, to_is_sta, tp \`
  - `Core/Src/dev_SRM.c:45610: Store_Work_Data_Fix(to_tpos, to_lpos, WORK_MOVE_ONLY, to_is_sta, tp \`
  - `Core/Src/dev_SRM.c:45662: Store_Work_Data_Fix(to_tpos, to_lpos, WORK_MOVE_ONLY, to_is_sta, tp \`
  - `Core/Src/dev_SRM.c:46631: Store_Work_Data_Fix(to_tpos[POS_FORK_1], to_lpos[POS_FORK_1], WORK_MOVE_ONLY, to_is_sta[POS_FORK_1],`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Store_Work_Data_1

- **종류**: 함수
- **시그니처**: `static void Store_Work_Data_1(INT32S TravPos, INT32S LiftPos, INT08U ForkAct, INT08U IsStation, \ CellPosSTR* nToPos, INT08U Step, INT16S Fork1Depth, INT16S Fork2Depth, INT08U GoodsType, INT08U nOperFlag)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: Store_*: 작업 큐/버퍼 적재. Save와 구분.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:45038: static void Store_Work_Data_1(INT32S TravPos, INT32S LiftPos, INT08U ForkAct, INT08U IsStation, \`
  - `Core/Src/dev_SRM.c:46642: Store_Work_Data_1(from_tpos[POS_FORK_1], from_lpos[POS_FORK_1], WORK_FORK1_GET, from_is_sta[POS_FORK`
  - `Core/Src/dev_SRM.c:46645: Store_Work_Data_1(to_tpos[POS_FORK_1], to_lpos[POS_FORK_1], WORK_FORK1_PUT, to_is_sta[POS_FORK_1], &`
  - `Core/Src/dev_SRM.c:46655: Store_Work_Data_1(to_tpos[POS_FORK_1], to_lpos[POS_FORK_1], WORK_FORK1_PUT, to_is_sta[POS_FORK_1], &`
  - `Core/Src/dev_SRM.c:46665: Store_Work_Data_1(from_tpos[POS_FORK_1], from_lpos[POS_FORK_1], WORK_FORK1_STICKY, from_is_sta[POS_F`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Store_Work_Data_Task

- **종류**: 함수
- **시그니처**: `static void Store_Work_Data_Task(INT32S TravPos, INT32S LiftPos, INT08U ForkAct, INT08U IsStation, \ CellPosSTR* pPos, INT08U Step, INT16S Fork1Depth, INT16S Fork2Depth, INT08U GoodsType)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: Store_*: 작업 큐/버퍼 적재. Save와 구분. Task: TML 0x40 다중작업. 0x41과 분기 다름.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:45107: static void Store_Work_Data_Task(INT32S TravPos, INT32S LiftPos, INT08U ForkAct, INT08U IsStation, \`
  - `Core/Src/dev_SRM.c:45911: Store_Work_Data_Task(to_tpos, to_lpos, WORK_MOVE_ONLY, to_is_sta, \`
  - `Core/Src/dev_SRM.c:45916: Store_Work_Data_Task(to_tpos, to_lpos, WORK_FORK1_GET, to_is_sta, \`
  - `Core/Src/dev_SRM.c:45921: Store_Work_Data_Task(to_tpos, to_lpos, WORK_FORK1_PUT, to_is_sta, \`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### calc_travel_distance

- **종류**: 함수
- **시그니처**: `double calc_travel_distance(INT32S tpos1, INT32S lpos1, INT32S tpos2, INT32S lpos2)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:45157: double calc_travel_distance(INT32S tpos1, INT32S lpos1, INT32S tpos2, INT32S lpos2)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### get_home_position

- **종류**: 함수
- **시그니처**: `INT08U get_home_position(INT32U* trav_pos, INT32U* lift_pos)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **인근 주석**: *trav_pos = m_ExtSEnv0.RackConfig.HomePos.TravPos; *lift_pos = m_ExtSEnv0.RackConfig.HomePos.LiftPos;
- **용도(읽는 법)**: HOME/RETURN: 원점복귀 vs 에러복귀 RunMode 혼재. grep으로 확인.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:45170: INT08U get_home_position(INT32U* trav_pos, INT32U* lift_pos)`
  - `Core/Src/dev_SRM.c:45805: if (get_home_position((INT32U*)&to_tpos, (INT32U*)&to_lpos))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### get_station_position

- **종류**: 함수
- **시그니처**: `INT08U get_station_position(INT08U station_no, INT32U* trav_pos, INT32U* lift_pos) { if (station_no <= m_ExtSEnv1.StationEnv.TotalUseCnt) // Station { if (m_ExtSEnv1.StationEnv.StationSet[station_no].Type == STATION_NOT_USE)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:45217: INT08U get_station_position(INT08U station_no, INT32U* trav_pos, INT32U* lift_pos)`
  - `Core/Src/dev_SRM.c:45533: nFlag = get_station_position(0, (INT32U*)&to_tpos, (INT32U*)&to_lpos);`
  - `Core/Src/dev_SRM.c:45635: nFlag = get_station_position(nHomeStationNo - 1, (INT32U*)&to_tpos, (INT32U*)&to_lpos);`
  - `Core/Src/dev_SRM.c:45816: if (get_station_position(nTargetPos.Station - 1, (INT32U*)&to_tpos, (INT32U*)&to_lpos))`
  - `Core/Src/dev_SRM.c:46163: get_station_position(tp[POS_FORK_1].Station - 1, (INT32U*)&to_tpos[POS_FORK_1], (INT32U*)&to_lpos[PO`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Get_Cell_Position_Add_Offset

- **종류**: 함수
- **시그니처**: `INT08U Get_Cell_Position_Add_Offset(CellPosSTR* pPos, INT32U* trav_pos, INT32U* lift_pos)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:45243: INT08U Get_Cell_Position_Add_Offset(CellPosSTR* pPos, INT32U* trav_pos, INT32U* lift_pos)`
  - `Core/Src/dev_SRM.c:45858: if (Get_Cell_Position_Add_Offset(&nTargetPos, (INT32U*)&to_tpos, (INT32U*)&to_lpos))`
  - `Core/Src/dev_SRM.c:46199: error[POS_FORK_1] = Get_Cell_Position_Add_Offset(&tp[POS_FORK_1], (INT32U*)&to_tpos[POS_FORK_1], (IN`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Get_Cell_Position_Add_Offset_1

- **종류**: 함수
- **시그니처**: `INT08U Get_Cell_Position_Add_Offset_1(CellPosSTR* pPos, INT32U* trav_pos, INT32U* lift_pos, INT16S* fork_Depth)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:45334: INT08U Get_Cell_Position_Add_Offset_1(CellPosSTR* pPos, INT32U* trav_pos, INT32U* lift_pos, INT16S* `
  - `Core/Src/dev_SRM.c:46310: error[POS_FORK_1] = Get_Cell_Position_Add_Offset_1(&fp[POS_FORK_1], \`
  - `Core/Src/dev_SRM.c:46387: error[POS_FORK_1] = Get_Cell_Position_Add_Offset_1(&tp[POS_FORK_1], (INT32U*)&to_tpos[POS_FORK_1], (`
  - `Core/Src/dev_SRM.c:46486: error[POS_FORK_1] = Get_Cell_Position_Add_Offset_1(&tp[POS_FORK_1], (INT32U*)&to_tpos[POS_FORK_1], (`
  - `Core/Src/dev_SRM.c:46574: error[POS_FORK_1] = Get_Cell_Position_Add_Offset_1(&fp[POS_FORK_1], (INT32U*)&from_tpos[POS_FORK_1],`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_Move_Home_Cmd

- **종류**: 함수
- **시그니처**: `INT08U SRM_Move_Home_Cmd()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: HOME/RETURN: 원점복귀 vs 에러복귀 RunMode 혼재. grep으로 확인.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:45515: INT08U SRM_Move_Home_Cmd()`
  - `Core/Src/dev_SRM.c:64040: if (SRM_Move_Home_Cmd())`
  - `Core/Src/dev_SRM.c:66807: nResult = SRM_Move_Home_Cmd();`
  - `Core/Inc/dev_SRM.h:2329: INT08U SRM_Move_Home_Cmd();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_Move_Maintanence_Cmd

- **종류**: 함수
- **시그니처**: `INT08U SRM_Move_Maintanence_Cmd()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:3017: result = SRM_Move_Maintanence_Cmd();//아니면 이동`
  - `Core/Src/dev_SRM.c:45694: INT08U SRM_Move_Maintanence_Cmd()`
  - `Core/Inc/dev_SRM.h:2330: INT08U SRM_Move_Maintanence_Cmd();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_Task_work_cmd

- **종류**: 함수
- **시그니처**: `INT08U SRM_Task_work_cmd(TaskCommand* pCmd, INT08U nIndex)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: Task: TML 0x40 다중작업. 0x41과 분기 다름.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2278: Task_FailReason[i] = SRM_Task_work_cmd(&pCmd->TaskWork[i], i);`
  - `Core/Src/dev_SRM.c:45785: INT08U SRM_Task_work_cmd(TaskCommand* pCmd, INT08U nIndex)`
  - `Core/Inc/dev_SRM.h:2331: INT08U SRM_Task_work_cmd(TaskCommand* pCmd, INT08U nIndex);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_Fork_Work_Cmd

- **종류**: 함수
- **시그니처**: `INT08U SRM_Fork_Work_Cmd(WorkCmdSTR* pCmd)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2664: ret_value[0] = SRM_Fork_Work_Cmd((WorkCmdSTR*)pCmd);`
  - `Core/Src/dev_SRM.c:45934: INT08U SRM_Fork_Work_Cmd(WorkCmdSTR* pCmd)`
  - `Core/Src/dev_SRM.c:67010: SRM_Fork_Work_Cmd(&nDemoCmd);`
  - `Core/Src/dev_SRM.c:67069: SRM_Fork_Work_Cmd(&nDemoCmd);`
  - `Core/Src/dev_SRM.c:67123: SRM_Fork_Work_Cmd(&nDemoCmd);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_Start_On

- **종류**: 함수
- **시그니처**: `INT08U SRM_Start_On(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2867: result = SRM_Start_On();`
  - `Core/Src/dev_SRM.c:46804: INT08U SRM_Start_On(void)`
  - `Core/Src/dev_SRM.c:58579: SRM_Start_On(); //ì§ìì ì´ë° ëë wcs -> ììì§ë ¹ ìì  -> íì ì ì¥(ëê¸°), ì´ì `
  - `Core/Src/dev_SRM.c:66358: SRM_Start_On();`
  - `Core/Inc/dev_SRM.h:2333: INT08U SRM_Start_On(void);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_Start_Off

- **종류**: 함수
- **시그니처**: `void SRM_Start_Off(void) { if (m_St.SRM_Status1.Bit.StartOn)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2863: SRM_Start_Off();`
  - `Core/Src/dev_SRM.c:47470: void SRM_Start_Off(void)`
  - `Core/Src/dev_SRM.c:52128: SRM_Start_Off();`
  - `Core/Src/dev_SRM.c:63806: SRM_Start_Off();`
  - `Core/Src/dev_SRM.c:63836: SRM_Start_Off();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Is_Exist_Goods

- **종류**: 함수
- **시그니처**: `INT08U Is_Exist_Goods(INT08U nFeeding)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:10636: if (Is_Exist_Goods(POS_FORK_1))`
  - `Core/Src/dev_SRM.c:47488: INT08U Is_Exist_Goods(INT08U nFeeding)`
  - `Core/Src/dev_SRM.c:47541: if (Is_Exist_Goods(nFeeding))`
  - `Core/Src/dev_SRM.c:59212: if (Is_Exist_Goods(POS_FORK_1)) {`
  - `Core/Src/dev_SRM.c:61119: if (!Is_Exist_Goods(POS_FORK_1))  nFinish_flag |= cbits[0];`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

