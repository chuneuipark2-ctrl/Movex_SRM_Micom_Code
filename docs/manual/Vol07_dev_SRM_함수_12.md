# Vol.07 — dev_SRM.c 함수 (12)

> 생성일: 2026-06-16 | MX SRM App Ver 4.4 | 소스 미수정

상태머신 함수.

---

### Clear_Warning_Manager

- **종류**: 함수
- **시그니처**: `void Clear_Warning_Manager(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:66827: void Clear_Warning_Manager(void)`
  - `Core/Src/dev_SRM.c:68151: Clear_Warning_Manager();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Test_Simulater_Manager

- **종류**: 함수
- **시그니처**: `void Test_Simulater_Manager(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:66823: * @brief Test_Simulater_Manager`
  - `Core/Src/dev_SRM.c:66852: * @brief Test_Simulater_Manager`
  - `Core/Src/dev_SRM.c:66856: void Test_Simulater_Manager(void)`
  - `Core/Src/dev_SRM.c:68153: Test_Simulater_Manager();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_Demo_Mode_1

- **종류**: 함수
- **시그니처**: `void SRM_Demo_Mode_1()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:66925: void SRM_Demo_Mode_1()`
  - `Core/Src/dev_SRM.c:67606: SRM_Demo_Mode_1();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_Demo_Mode_2

- **종류**: 함수
- **시그니처**: `void SRM_Demo_Mode_2()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:67201: void SRM_Demo_Mode_2()`
  - `Core/Src/dev_SRM.c:67615: SRM_Demo_Mode_2();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_Demo_Run_Process

- **종류**: 함수
- **시그니처**: `void SRM_Demo_Run_Process() { if (checkFusingString((INT08U*)m_ExtSEnv.mDevice.ProjectID.ProjectNo, (INT08U*)MOVEX_RND, 6) == 0)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:67602: void SRM_Demo_Run_Process()`
  - `Core/Src/dev_SRM.c:67952: SRM_Demo_Run_Process();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Check_Limit_State

- **종류**: 함수
- **시그니처**: `void Check_Limit_State(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:58551: Check_Limit_State(); //ì£¼í, ì¹ê° íëì¨ì´ ë¦¬ë¯¸í¸ ì½ê¸°`
  - `Core/Src/dev_SRM.c:67625: void Check_Limit_State(void)`
  - `Core/Inc/dev_SRM.h:2395: void Check_Limit_State(void);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Fork_Inverter_IO_Proc

- **종류**: 함수
- **시그니처**: `void Fork_Inverter_IO_Proc(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: 인버터/EtherCAT 상태. m_ExtSEnv와 함께 확인.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:67682: void Fork_Inverter_IO_Proc(void)`
  - `Core/Src/dev_SRM.c:68147: Fork_Inverter_IO_Proc();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Lidar_Select_Zone_Rack

- **종류**: 함수
- **시그니처**: `void Lidar_Select_Zone_Rack(INT08U nRowNo, INT08U nZone) { if (m_ExtSEnv.Machine.mType.Fork_Type == FORK_TYPE_SINGLE_DEEP) { if (nRowNo == 1) { // Rack left if (nZone == 0)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:67738: void Lidar_Select_Zone_Rack(INT08U nRowNo, INT08U nZone)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Lidar_IO_Proc

- **종류**: 함수
- **시그니처**: `void Lidar_IO_Proc(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:67856: void Lidar_IO_Proc(void)`
  - `Core/Src/dev_SRM.c:68149: Lidar_IO_Proc();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_Manager

- **종류**: 함수
- **시그니처**: `void SRM_Manager(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:67917: void SRM_Manager(void)`
  - `Core/Src/main.c:843: SRM_Manager();`
  - `Core/Inc/dev_SRM.h:2396: void SRM_Manager(void);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

