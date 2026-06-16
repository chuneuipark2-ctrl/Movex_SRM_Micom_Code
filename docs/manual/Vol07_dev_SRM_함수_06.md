# Vol.07 — dev_SRM.c 함수 (6)

> 생성일: 2026-06-16 | MX SRM App Ver 4.4 | 소스 미수정

상태머신 함수.

---

### Check_Fork_Move_Mode

- **종류**: 함수
- **시그니처**: `INT08U Check_Fork_Move_Mode(INT08U nForkNo, INT08U nOperMode)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:32871: INT08U Check_Fork_Move_Mode(INT08U nForkNo, INT08U nOperMode)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Warning_FOUT_Impossible

- **종류**: 함수
- **시그니처**: `INT08U Warning_FOUT_Impossible(INT08U nForkOper)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:33018: INT08U Warning_FOUT_Impossible(INT08U nForkOper)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Manual_Control_Fork1_Proc

- **종류**: 함수
- **시그니처**: `void Manual_Control_Fork1_Proc(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **인근 주석**: INT08U flag;
- **용도(읽는 법)**: 헤더 주석: INT08U flag;
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:33095: void Manual_Control_Fork1_Proc(void)`
  - `Core/Src/dev_SRM.c:37218: Manual_Control_Fork1_Proc();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Manual_Control_Fork1_Single_Deep_Type1

- **종류**: 함수
- **시그니처**: `void Manual_Control_Fork1_Single_Deep_Type1(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **인근 주석**: INT08U flag;
- **용도(읽는 법)**: 헤더 주석: INT08U flag;
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:34198: void Manual_Control_Fork1_Single_Deep_Type1(void)`
  - `Core/Src/dev_SRM.c:37225: Manual_Control_Fork1_Single_Deep_Type1();`
  - `Core/Src/dev_SRM.c:37229: Manual_Control_Fork1_Single_Deep_Type1();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Manual_Control_Fork1_Double_Deep

- **종류**: 함수
- **시그니처**: `void Manual_Control_Fork1_Double_Deep(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **인근 주석**: INT08U flag;
- **용도(읽는 법)**: 헤더 주석: INT08U flag;
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:35449: void Manual_Control_Fork1_Double_Deep(void)`
  - `Core/Src/dev_SRM.c:37239: Manual_Control_Fork1_Double_Deep();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Manual_Position_Move_Process

- **종류**: 함수
- **시그니처**: `void Manual_Position_Move_Process(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:37199: void Manual_Position_Move_Process(void)`
  - `Core/Src/dev_SRM.c:63224: Manual_Position_Move_Process();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Invertor_Parameter_Proc

- **종류**: 함수
- **시그니처**: `void Invertor_Parameter_Proc()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:37261: void Invertor_Parameter_Proc()`
  - `Core/Src/dev_SRM.c:68069: Invertor_Parameter_Proc();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Set_All_Profile_Scurve

- **종류**: 함수
- **시그니처**: `void Set_All_Profile_Scurve(INT08U nInv, INT32S position, INT08U vel_type)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:37692: void Set_All_Profile_Scurve(INT08U nInv, INT32S position, INT08U vel_type)`
  - `Core/Src/dev_SRM.c:40148: Set_All_Profile_Scurve(nInv, position, FORK_VEL_AUTO_H);`
  - `Core/Src/dev_SRM.c:59223: Set_All_Profile_Scurve(INV_TRAVEL, m_WorkData[s_WorkInx].DrvData[INV_TRAVEL].TargetPos, \`
  - `Core/Src/dev_SRM.c:59270: Set_All_Profile_Scurve(INV_HOIST, m_WorkData[s_WorkInx].DrvData[INV_HOIST].TargetPos, \`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Set_Decelation_Stop_Scurve

- **종류**: 함수
- **시그니처**: `void Set_Decelation_Stop_Scurve(INT08U nInv, INT32S nTargetPos, INT08U vel_type)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:38042: void Set_Decelation_Stop_Scurve(INT08U nInv, INT32S nTargetPos, INT08U vel_type)`
  - `Core/Src/dev_SRM.c:39892: Set_Decelation_Stop_Scurve(nInvertor, pProfile->TargetPos, pProfile->vel_type);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Set_Decelation_Move_Scurve

- **종류**: 함수
- **시그니처**: `void Set_Decelation_Move_Scurve(INT08U nInv, INT08U vel_type)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:38303: void Set_Decelation_Move_Scurve(INT08U nInv, INT08U vel_type)`
  - `Core/Src/dev_SRM.c:40168: Set_Decelation_Move_Scurve(nInv, FORK_VEL_AUTO_L);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### set_Fork_All_Profile_Scurve

- **종류**: 함수
- **시그니처**: `void set_Fork_All_Profile_Scurve(INT32S position, INT08U vel_type)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:38563: void set_Fork_All_Profile_Scurve(INT32S position, INT08U vel_type)`
  - `Core/Src/dev_SRM.c:40715: set_Fork_All_Profile_Scurve(position, vel_type);`
  - `Core/Inc/dev_SRM.h:42: void set_Fork_All_Profile_Scurve(INT32S position, INT08U vel_type);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### set_Fork_Accelation_Move_Scurve

- **종류**: 함수
- **시그니처**: `void set_Fork_Accelation_Move_Scurve(INT32S position, INT08U vel_type)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:38882: void set_Fork_Accelation_Move_Scurve(INT32S position, INT08U vel_type)`
  - `Core/Inc/dev_SRM.h:43: void set_Fork_Accelation_Move_Scurve(INT32S position, INT08U vel_type);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### set_Fork_Decelation_Stop_Scurve

- **종류**: 함수
- **시그니처**: `void set_Fork_Decelation_Stop_Scurve(INT32S position, INT08U vel_type)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:39218: void set_Fork_Decelation_Stop_Scurve(INT32S position, INT08U vel_type)`
  - `Core/Src/dev_SRM.c:40273: set_Fork_Decelation_Stop_Scurve(ForkProfile.TargetPos, ForkProfile.vel_type);`
  - `Core/Inc/dev_SRM.h:44: void set_Fork_Decelation_Stop_Scurve(INT32S position, INT08U vel_type);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### set_Fork_Decelation_Move_Scurve

- **종류**: 함수
- **시그니처**: `void set_Fork_Decelation_Move_Scurve(INT16S nTarget_Velocity, INT08U nVelType)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:39378: void set_Fork_Decelation_Move_Scurve(INT16S nTarget_Velocity, INT08U nVelType)`
  - `Core/Src/dev_SRM.c:41240: set_Fork_Decelation_Move_Scurve(s_AutoDec_Velocity, FORK_VEL_AUTO_L);`
  - `Core/Src/dev_SRM.c:41250: set_Fork_Decelation_Move_Scurve(s_AutoDec_Velocity, FORK_VEL_AUTO_L);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Set_Fork_Stop_Scurve

- **종류**: 함수
- **시그니처**: `void Set_Fork_Stop_Scurve(INT08U vel_type)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:39539: void Set_Fork_Stop_Scurve(INT08U vel_type)`
  - `Core/Src/dev_SRM.c:41490: Set_Fork_Stop_Scurve(s_Velocy_Mode);`
  - `Core/Src/dev_SRM.c:41495: Set_Fork_Stop_Scurve(s_Velocy_Mode);`
  - `Core/Inc/dev_SRM.h:45: void Set_Fork_Stop_Scurve(INT08U vel_type);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### calc_scurve_profile

- **종류**: 함수
- **시그니처**: `void calc_scurve_profile(ScurveProfileSTR* pData, double run_time)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:39800: void calc_scurve_profile(ScurveProfileSTR* pData, double run_time)`
  - `Core/Src/dev_SRM.c:39928: calc_scurve_profile(pProfile, run_time);`
  - `Core/Src/dev_SRM.c:39968: calc_scurve_profile(pProfile, run_time);`
  - `Core/Src/dev_SRM.c:39996: calc_scurve_profile(pProfile, run_time);`
  - `Core/Src/dev_SRM.c:40032: calc_scurve_profile(pProfile, run_time);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Profile_Scurve_Control

- **종류**: 함수
- **시그니처**: `void Profile_Scurve_Control(INT08U nInvertor)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **인근 주석**: INT08U result = 0;
- **용도(읽는 법)**: 헤더 주석: INT08U result = 0;
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:39853: void Profile_Scurve_Control(INT08U nInvertor)`
  - `Core/Src/dev_SRM.c:40182: Profile_Scurve_Control(nInv);`
  - `Core/Src/dev_SRM.c:55304: Profile_Scurve_Control(INV_TRAVEL);`
  - `Core/Src/dev_SRM.c:55984: Profile_Scurve_Control(INV_HOIST);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### test_profile

- **종류**: 함수
- **시그니처**: `void test_profile(INT32S position)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:40139: void test_profile(INT32S position)`
  - `Core/Inc/dev_SRM.h:68: void test_profile(INT32S position);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Fork_Profile_Scurve_Control

- **종류**: 함수
- **시그니처**: `void Fork_Profile_Scurve_Control(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:40210: void Fork_Profile_Scurve_Control(void)`
  - `Core/Src/dev_SRM.c:40700: Fork_Profile_Scurve_Control();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Fork1_Profile_Control_Proc

- **종류**: 함수
- **시그니처**: `INT08U Fork1_Profile_Control_Proc(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6679: Fork1_Profile_Control_Proc();`
  - `Core/Src/dev_SRM.c:40688: INT08U Fork1_Profile_Control_Proc(void)`
  - `Core/Inc/dev_SRM.h:69: INT08U Fork1_Profile_Control_Proc(void);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_Fork_profile_Control

- **종류**: 함수
- **시그니처**: `void SRM_Fork_profile_Control(INT08U vel_type, INT32S position)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **인근 주석**: INT32S move_position = 0;
- **용도(읽는 법)**: 헤더 주석: INT32S move_position = 0;
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:40706: void SRM_Fork_profile_Control(INT08U vel_type, INT32S position)`
  - `Core/Src/dev_SRM.c:41125: SRM_Fork_profile_Control(s_Velocy_Mode, nTarget_Depth);`
  - `Core/Inc/dev_SRM.h:50: void SRM_Fork_profile_Control(INT08U vel_type, INT32S position);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Fork_Auto_Control_NextStep

- **종류**: 함수
- **시그니처**: `void Fork_Auto_Control_NextStep(INT32U* pStep, INT32U nNextStepNo) { if (m_pgmEnv.Debug_Fork_Control_Flag) { if (m_pgmEnv.Debug_Fork_Control_NextStep)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: 포크 서브스텝: GET/PUT 내부 단계.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:40860: void Fork_Auto_Control_NextStep(INT32U* pStep, INT32U nNextStepNo)`
  - `Core/Src/dev_SRM.c:41002: Fork_Auto_Control_NextStep(&m_Fork_Sub_Run_Step, 12);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Fork_Auto_Profile_Control

- **종류**: 함수
- **시그니처**: `void Fork_Auto_Profile_Control(INT08U nMode, INT32S nTarget_Depth, SRM_WorkDataSTR* pWorkData)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:40883: void Fork_Auto_Profile_Control(INT08U nMode, INT32S nTarget_Depth, SRM_WorkDataSTR* pWorkData)`
  - `Core/Src/dev_SRM.c:60753: Fork_Auto_Profile_Control(s_Fork_Oper_Mode, s_Fork_TargetPos[0], &m_WorkData[s_WorkInx]);`
  - `Core/Src/dev_SRM.c:61001: Fork_Auto_Profile_Control(s_Fork_Oper_Mode, s_Fork_TargetPos[0], &m_WorkData[s_WorkInx]);`
  - `Core/Src/dev_SRM.c:61529: Fork_Auto_Profile_Control(s_Fork_Oper_Mode, s_Fork_TargetPos[0], &m_WorkData[s_WorkInx]);`
  - `Core/Src/dev_SRM.c:61741: Fork_Auto_Profile_Control(s_Fork_Oper_Mode, s_Fork_TargetPos[0], &m_WorkData[s_WorkInx]);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Fork_Auto_Position_Control

- **종류**: 함수
- **시그니처**: `void Fork_Auto_Position_Control(INT08U nMode, INT32S nTarget_Depth, SRM_WorkDataSTR* pWorkData, INT08U nInterlock_Not_Use)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:41538: void Fork_Auto_Position_Control(INT08U nMode, INT32S nTarget_Depth, SRM_WorkDataSTR* pWorkData, INT0`
  - `Core/Src/dev_SRM.c:60758: Fork_Auto_Position_Control(s_Fork_Oper_Mode, s_Fork_TargetPos[0], &m_WorkData[s_WorkInx], m_WorkData`
  - `Core/Src/dev_SRM.c:61007: Fork_Auto_Position_Control(s_Fork_Oper_Mode, s_Fork_TargetPos[0], &m_WorkData[s_WorkInx], m_WorkData`
  - `Core/Src/dev_SRM.c:61534: Fork_Auto_Position_Control(s_Fork_Oper_Mode, s_Fork_TargetPos[0], &m_WorkData[s_WorkInx], m_WorkData`
  - `Core/Src/dev_SRM.c:61746: Fork_Auto_Position_Control(s_Fork_Oper_Mode, s_Fork_TargetPos[0], &m_WorkData[s_WorkInx], m_WorkData`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Fork_Auto_Position_Control_Rev1

- **종류**: 함수
- **시그니처**: `void Fork_Auto_Position_Control_Rev1(INT08U nMode, INT32S nTarget_Depth, SRM_WorkDataSTR* pWorkData, INT08U nInterlock_Not_Use)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:42468: void Fork_Auto_Position_Control_Rev1(INT08U nMode, INT32S nTarget_Depth, SRM_WorkDataSTR* pWorkData,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

