# Vol.07 — dev_SRM.c 함수 (2)

> 생성일: 2026-06-16 | MX SRM App Ver 4.4 | 소스 미수정

상태머신 함수.

---

### Auto_Ctr_Travel

- **종류**: 함수
- **시그니처**: `INT08U Auto_Ctr_Travel(INT32S position, INT08U VelType)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:2041: INT08U Auto_Ctr_Travel(INT32S position, INT08U VelType)`
  - `Core/Src/dev_SRM.c:52409: nTrav_Control_Error = Auto_Ctr_Travel(s_Move_TargetPos, nDef_Move_Speed);`
  - `Core/Src/dev_SRM.c:52460: nTrav_Control_Error = Auto_Ctr_Travel(s_Move_TargetPos, nDef_Move_Speed);`
  - `Core/Src/dev_SRM.c:52570: nTrav_Control_Error = Auto_Ctr_Travel(s_Move_TargetPos, nDef_Move_Speed);`
  - `Core/Src/dev_SRM.c:54746: nTrav_Control_Error = Auto_Ctr_Travel(s_Move_TargetPos, nDef_Move_Speed);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Manual_Ctr_Travel

- **종류**: 함수
- **시그니처**: `INT08U Manual_Ctr_Travel(INT32S position, INT08U VelType)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:2156: INT08U Manual_Ctr_Travel(INT32S position, INT08U VelType)`
  - `Core/Src/dev_SRM.c:22557: nMotor = Manual_Ctr_Travel(nPosition, nVelocity_type);`
  - `Core/Src/dev_SRM.c:23080: nMotor = Manual_Ctr_Travel(nPosition, nVelocity_type);`
  - `Core/Src/dev_SRM.c:24066: nMotor = Manual_Ctr_Travel(nPosition, nVelocity_type);`
  - `Core/Src/dev_SRM.c:24696: nMotor = Manual_Ctr_Travel(nPosition, nVelocity_type);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Motor_Travel_Jog

- **종류**: 함수
- **시그니처**: `INT08U Motor_Travel_Jog(INT08U nAct, INT08U VelType)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:2247: INT08U Motor_Travel_Jog(INT08U nAct, INT08U VelType)`
  - `Core/Src/dev_SRM.c:8142: Motor_Travel_Jog(JOG_TRAV_FORWARD, TRAV_VEL_ORIGIN);`
  - `Core/Src/dev_SRM.c:8152: Motor_Travel_Jog(JOG_TRAV_REVERSE, TRAV_VEL_ORIGIN);`
  - `Core/Src/dev_SRM.c:8171: Motor_Travel_Jog(JOG_TRAV_STOP_MOVE, TRAV_VEL_ORIGIN);`
  - `Core/Src/dev_SRM.c:8179: Motor_Travel_Jog(JOG_TRAV_REVERSE, TRAV_VEL_ORIGIN);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Auto_Ctr_Lift

- **종류**: 함수
- **시그니처**: `INT08U Auto_Ctr_Lift(INT32S position, INT08U VelType)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:2456: INT08U Auto_Ctr_Lift(INT32S position, INT08U VelType)`
  - `Core/Src/dev_SRM.c:52843: nLift_Control_Error = Auto_Ctr_Lift(s_Move_TargetPos, nDef_Move_Speed);`
  - `Core/Src/dev_SRM.c:52894: nLift_Control_Error = Auto_Ctr_Lift(s_Move_TargetPos, nDef_Move_Speed);`
  - `Core/Src/dev_SRM.c:53004: nLift_Control_Error = Auto_Ctr_Lift(s_Move_TargetPos, nDef_Move_Speed);`
  - `Core/Src/dev_SRM.c:54952: nLift_Control_Error = Auto_Ctr_Lift(s_Move_TargetPos, nDef_Move_Speed);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Manual_Control_Lift

- **종류**: 함수
- **시그니처**: `INT08U Manual_Control_Lift(INT32S position, INT08U VelType)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:2579: INT08U Manual_Control_Lift(INT32S position, INT08U VelType)`
  - `Core/Src/dev_SRM.c:25271: nMotor = Manual_Control_Lift(nPosition, nVelocity_type);`
  - `Core/Src/dev_SRM.c:25895: nMotor = Manual_Control_Lift(nPosition, nVelocity_type);`
  - `Core/Src/dev_SRM.c:26667: nMotor = Manual_Control_Lift(nPosition, nVelocity_type);`
  - `Core/Src/dev_SRM.c:27697: nMotor = Manual_Control_Lift(nPosition, nVelocity_type);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Motor_Lift_Jog

- **종류**: 함수
- **시그니처**: `INT08U Motor_Lift_Jog(INT08U nAct, INT08U VelType)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:2658: INT08U Motor_Lift_Jog(INT08U nAct, INT08U VelType)`
  - `Core/Src/dev_SRM.c:8490: Motor_Lift_Jog(JOG_LIFT_UP, LIFT_VEL_ORIGIN);`
  - `Core/Src/dev_SRM.c:8499: Motor_Lift_Jog(JOG_LIFT_DOWN, LIFT_VEL_ORIGIN);`
  - `Core/Src/dev_SRM.c:8520: Motor_Lift_Jog(JOG_LIFT_STOP_MOVE, LIFT_VEL_ORIGIN);`
  - `Core/Src/dev_SRM.c:8554: Motor_Lift_Jog(JOG_LIFT_STOP_MOVE, LIFT_VEL_ORIGIN);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Motor_Fork_Velocity_Command

- **종류**: 함수
- **시그니처**: `INT08U Motor_Fork_Velocity_Command(INT08S nWard, INT16S nCmdVelocity)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:2859: INT08U Motor_Fork_Velocity_Command(INT08S nWard, INT16S nCmdVelocity)`
  - `Core/Src/dev_SRM.c:40675: Motor_Fork_Velocity_Command(ForkProfile.ward, nCommand_Velocity);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Motor_Manual_Fork1

- **종류**: 함수
- **시그니처**: `INT08U Motor_Manual_Fork1(INT08U nAct, INT08U VelType)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:2925: INT08U Motor_Manual_Fork1(INT08U nAct, INT08U VelType)`
  - `Core/Src/dev_SRM.c:3224: INT08U Motor_Manual_Fork1(INT08U nAct, INT08U VelType)`
  - `Core/Src/dev_SRM.c:8890: Motor_Manual_Fork1(JOG_FORK_RIGHT, FORK_VEL_ORIGIN);`
  - `Core/Src/dev_SRM.c:8898: Motor_Manual_Fork1(JOG_FORK_LEFT, FORK_VEL_ORIGIN);`
  - `Core/Src/dev_SRM.c:8911: Motor_Manual_Fork1(JOG_FORK_RIGHT, FORK_VEL_ORIGIN);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Auto_Position_Control_Fork

- **종류**: 함수
- **시그니처**: `INT08U Auto_Position_Control_Fork(INT32S position, INT08U VelType)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:3609: INT08U Auto_Position_Control_Fork(INT32S position, INT08U VelType)`
  - `Core/Src/dev_SRM.c:41838: m_Fork_Sub_Run_Error = Auto_Position_Control_Fork(nTarget_Depth, s_Velocy_Mode);`
  - `Core/Src/dev_SRM.c:42047: m_Fork_Sub_Run_Error = Auto_Position_Control_Fork(nTarget_Depth, FORK_VEL_AUTO_L);`
  - `Core/Src/dev_SRM.c:42421: Auto_Position_Control_Fork(0, FORK_VEL_EMG);`
  - `Core/Src/dev_SRM.c:42787: m_Fork_Sub_Run_Error = Auto_Position_Control_Fork(nTarget_Depth, s_Velocy_Mode);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MANUAL_CTR_Fork

- **종류**: 함수
- **시그니처**: `INT08U MANUAL_CTR_Fork(INT32S position, INT08U VelType)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:3707: INT08U MANUAL_CTR_Fork(INT32S position, INT08U VelType)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Motor_Move_Stop

- **종류**: 함수
- **시그니처**: `void Motor_Move_Stop(INT08U nInvertor, INT08U VelType)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:3787: void Motor_Move_Stop(INT08U nInvertor, INT08U VelType)`
  - `Core/Src/dev_SRM.c:22525: Motor_Move_Stop(INV_TRAVEL, nVelocity_type);`
  - `Core/Src/dev_SRM.c:23048: Motor_Move_Stop(INV_TRAVEL, nVelocity_type);`
  - `Core/Src/dev_SRM.c:24034: Motor_Move_Stop(INV_TRAVEL, nVelocity_type);`
  - `Core/Src/dev_SRM.c:24664: Motor_Move_Stop(INV_TRAVEL, nVelocity_type);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Motor_Application_Stop

- **종류**: 함수
- **시그니처**: `void Motor_Application_Stop(INT08U nInvertor, INT08U VelType)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:3877: void Motor_Application_Stop(INT08U nInvertor, INT08U VelType)`
  - `Core/Src/dev_SRM.c:40571: Motor_Application_Stop(INV_FORK_1, FORK_VEL_AUTO_H);`
  - `Core/Src/dev_SRM.c:40583: Motor_Application_Stop(INV_FORK_1, FORK_VEL_AUTO_H);`
  - `Core/Src/dev_SRM.c:40637: Motor_Application_Stop(INV_FORK_1, FORK_VEL_AUTO_H);`
  - `Core/Src/dev_SRM.c:40651: Motor_Application_Stop(INV_FORK_1, FORK_VEL_AUTO_H);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Motor_Emergency_Stop

- **종류**: 함수
- **시그니처**: `void Motor_Emergency_Stop(INT08U nInvertor)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:3974: void Motor_Emergency_Stop(INT08U nInvertor)`
  - `Core/Src/dev_SRM.c:30698: Motor_Emergency_Stop(nInvertor);`
  - `Core/Src/dev_SRM.c:30713: Motor_Emergency_Stop(nInvertor);`
  - `Core/Src/dev_SRM.c:30828: Motor_Emergency_Stop(nInvertor);`
  - `Core/Src/dev_SRM.c:31607: Motor_Emergency_Stop(nInvertor);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Motor_BrakeOn

- **종류**: 함수
- **시그니처**: `INT08U Check_Motor_BrakeOn(INT08U nInverter)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:1246: if (Check_Motor_BrakeOn(nInverter))`
  - `Core/Src/dev_SRM.c:4070: INT08U Check_Motor_BrakeOn(INT08U nInverter)`
  - `Core/Src/dev_SRM.c:55131: if (Check_Motor_BrakeOn(INV_FORK_1) == 0)`
  - `Core/Inc/dev_SRM.h:33: INT08U Check_Motor_BrakeOn(INT08U nInverter);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Motor_Brake_Enable

- **종류**: 함수
- **시그니처**: `void Motor_Brake_Enable(INT08U nInvertor)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:1252: Motor_Brake_Enable(nInverter);`
  - `Core/Src/dev_SRM.c:4197: void Motor_Brake_Enable(INT08U nInvertor)`
  - `Core/Src/dev_SRM.c:4424: Motor_Brake_Enable(INV_TRAVEL);`
  - `Core/Src/dev_SRM.c:4493: Motor_Brake_Enable(INV_HOIST);`
  - `Core/Src/dev_SRM.c:8291: Motor_Brake_Enable(INV_TRAVEL);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Motor_Brake_Release

- **종류**: 함수
- **시그니처**: `void Motor_Brake_Release(INT08U nInvertor)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:1248: Motor_Brake_Release(nInverter);`
  - `Core/Src/dev_SRM.c:4282: void Motor_Brake_Release(INT08U nInvertor)`
  - `Core/Src/dev_SRM.c:40968: Motor_Brake_Release(nInvertor);`
  - `Core/Src/dev_SRM.c:41710: Motor_Brake_Release(nInvertor);`
  - `Core/Src/dev_SRM.c:42658: Motor_Brake_Release(nInvertor);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Motor_Brake_Process

- **종류**: 함수
- **시그니처**: `void Motor_Brake_Process(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:4369: void Motor_Brake_Process(void)`
  - `Core/Src/dev_SRM.c:58593: Motor_Brake_Process(); // ëª¨í°ì ë¸ë ì´í¬ë¥¼ ë«ìì§ íë¨íë íë¡ì¸ì¤ ìì (ì¬ë`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Motor_Jog_Constant

- **종류**: 함수
- **시그니처**: `void Motor_Jog_Constant(INT08U inverter, INT08U act) // 0:stop, 1:CW, 2:CCW { if (act == JOG_FORK_APP_STOP) { if (m_pgmEnv.JogFlag[inverter])`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:4521: void Motor_Jog_Constant(INT08U inverter, INT08U act)  // 0:stop, 1:CW, 2:CCW`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Motor_jog_Velocity

- **종류**: 함수
- **시그니처**: `void Motor_jog_Velocity(INT08U inverter, INT08U act, INT16S Velocity) // 0:stop, 1:CW, 2:CCW { if (act == JOG_FORK_APP_STOP) { if (m_pgmEnv.JogFlag[inverter])`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:4557: void Motor_jog_Velocity(INT08U inverter, INT08U act, INT16S Velocity)  // 0:stop, 1:CW, 2:CCW`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Invertor_reference_set

- **종류**: 함수
- **시그니처**: `void Invertor_reference_set(INT08U inverter, INT08U nFlag)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:4598: void Invertor_reference_set(INT08U inverter, INT08U nFlag)`
  - `Core/Src/dev_SRM.c:8305: Invertor_reference_set(INV_TRAVEL, 1);`
  - `Core/Src/dev_SRM.c:8315: Invertor_reference_set(INV_TRAVEL, 0);`
  - `Core/Src/dev_SRM.c:8329: Invertor_reference_set(INV_TRAVEL, 2);`
  - `Core/Src/dev_SRM.c:8336: Invertor_reference_set(INV_TRAVEL, 2);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_Warning_reset

- **종류**: 함수
- **시그니처**: `void SRM_Warning_reset(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **인근 주석**: if (!(m_St.SRM_Status1.Bit.Fault && m_St.SRM_Status1.Bit.Warning))  return;
- **용도(읽는 법)**: 헤더 주석: if (!(m_St.SRM_Status1.Bit.Fault && m_St.SRM_Status1.Bit.Warning))  return;
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2662: SRM_Warning_reset();`
  - `Core/Src/dev_SRM.c:4893: void SRM_Warning_reset(void)`
  - `Core/Src/dev_SRM.c:5132: SRM_Warning_reset();`
  - `Core/Src/dev_SRM.c:30966: SRM_Warning_reset();`
  - `Core/Src/dev_SRM.c:30974: SRM_Warning_reset();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Invertor_Fault_Reset

- **종류**: 함수
- **시그니처**: `void Invertor_Fault_Reset()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:4906: void Invertor_Fault_Reset()`
  - `Core/Src/dev_SRM.c:5118: Invertor_Fault_Reset();`
  - `Core/Src/dev_SRM.c:63738: Invertor_Fault_Reset();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_fault_reset

- **종류**: 함수
- **시그니처**: `void SRM_fault_reset(void) { if (m_St.SRM_Status1.Bit.Warning)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:3034: SRM_fault_reset();`
  - `Core/Src/dev_SRM.c:5088: void SRM_fault_reset(void)`
  - `Core/Src/dev_SRM.c:5126: SRM_fault_reset();`
  - `Core/Src/dev_SRM.c:9215: SRM_fault_reset();`
  - `Core/Src/dev_SRM.c:44644: SRM_fault_reset();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ControlPanel_Fault_Reset

- **종류**: 함수
- **시그니처**: `void ControlPanel_Fault_Reset(void) { if (m_pgmEnv.SRM_RunMode == 0)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:5122: void ControlPanel_Fault_Reset(void)`
  - `Core/Inc/dev_SRM.h:41: void ControlPanel_Fault_Reset(void);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### control_SRM_reference_Start

- **종류**: 함수
- **시그니처**: `void control_SRM_reference_Start(INT08U nInvertor)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2716: control_SRM_reference_Start(INV_FORK_1);`
  - `Core/Src/com_tml.c:2726: control_SRM_reference_Start(INV_FORK_1);`
  - `Core/Src/com_tml.c:2735: control_SRM_reference_Start(INV_TRAVEL);`
  - `Core/Src/com_tml.c:2756: control_SRM_reference_Start(INV_TRAVEL);`
  - `Core/Src/com_tml.c:2768: control_SRM_reference_Start(INV_HOIST);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

