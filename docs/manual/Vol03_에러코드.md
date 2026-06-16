# Vol.03 — ERROR1_*

> 생성일: 2026-06-16 | MX SRM App Ver 4.4 | 소스 미수정

알람 코드.

---

### SOFT_ERROR_MODE_NOT_USE

- **종류**: enum `enumSOFT_ERROR_MODE` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:3693: nInitParam.SoftLimitErr.CheckFlag = SOFT_ERROR_MODE_NOT_USE;`
  - `Core/Src/SRM_Parameter.c:3704: nInitParam.OriginDogErr.CheckFlag = SOFT_ERROR_MODE_NOT_USE;`
  - `Core/Src/SRM_Parameter.c:3711: nInitParam.DecelDogErr.CheckFlag = SOFT_ERROR_MODE_NOT_USE;`
  - `Core/Src/SRM_Parameter.c:5068: nInitParam.SoftLimitErr.CheckFlag = SOFT_ERROR_MODE_NOT_USE;`
  - `Core/Src/SRM_Parameter.c:5079: nInitParam.OriginDogErr.CheckFlag = SOFT_ERROR_MODE_NOT_USE;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SOFT_ERROR_MODE_1

- **종류**: enum `enumSOFT_ERROR_MODE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Error Home
- **용도(읽는 법)**: 헤더 주석: Error Home
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2156: SOFT_ERROR_MODE_1,			// Error Home`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SOFT_ERROR_MODE_2

- **종류**: enum `enumSOFT_ERROR_MODE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Error End
- **용도(읽는 법)**: 헤더 주석: Error End
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2157: SOFT_ERROR_MODE_2,			// Error End`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SOFT_ERROR_MODE_3

- **종류**: enum `enumSOFT_ERROR_MODE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Error Home, End
- **용도(읽는 법)**: 헤더 주석: Error Home, End
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:4585: if (pSetting->SoftLimitErr.CheckFlag > SOFT_ERROR_MODE_3)`
  - `Core/Src/SRM_Parameter.c:4619: if (pSetting->SoftLimitErr.CheckFlag > SOFT_ERROR_MODE_3)`
  - `Core/Inc/User_Define.h:2158: SOFT_ERROR_MODE_3,			// Error Home, End`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### M_CTR_ERROR_NONE

- **종류**: enum `enumMOTOR_CONTROL_ERROR` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:2153: return M_CTR_ERROR_NONE;`
  - `Core/Src/dev_SRM.c:2244: return M_CTR_ERROR_NONE;`
  - `Core/Src/dev_SRM.c:2453: return M_CTR_ERROR_NONE;`
  - `Core/Src/dev_SRM.c:2576: return M_CTR_ERROR_NONE;`
  - `Core/Src/dev_SRM.c:2655: return M_CTR_ERROR_NONE;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### M_CTR_ERROR_VELOCITY

- **종류**: enum `enumMOTOR_CONTROL_ERROR` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:2179: return M_CTR_ERROR_VELOCITY;`
  - `Core/Src/dev_SRM.c:2269: return M_CTR_ERROR_VELOCITY;`
  - `Core/Src/dev_SRM.c:2501: return M_CTR_ERROR_VELOCITY;`
  - `Core/Src/dev_SRM.c:2602: return M_CTR_ERROR_VELOCITY;`
  - `Core/Src/dev_SRM.c:2680: return M_CTR_ERROR_VELOCITY;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### M_CTR_ERROR_CMD_SOFT_LIMIT

- **종류**: enum `enumMOTOR_CONTROL_ERROR` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:2111: return M_CTR_ERROR_CMD_SOFT_LIMIT;`
  - `Core/Src/dev_SRM.c:2200: return M_CTR_ERROR_CMD_SOFT_LIMIT;`
  - `Core/Src/dev_SRM.c:2528: return M_CTR_ERROR_CMD_SOFT_LIMIT;`
  - `Core/Src/dev_SRM.c:2536: return M_CTR_ERROR_CMD_SOFT_LIMIT;`
  - `Core/Src/dev_SRM.c:2623: return M_CTR_ERROR_CMD_SOFT_LIMIT;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### M_CTR_ERROR_CMD_TARGET_POS

- **종류**: enum `enumMOTOR_CONTROL_ERROR` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:2100: return M_CTR_ERROR_CMD_TARGET_POS;`
  - `Core/Src/dev_SRM.c:2105: return M_CTR_ERROR_CMD_TARGET_POS;`
  - `Core/Src/dev_SRM.c:2190: return M_CTR_ERROR_CMD_TARGET_POS;`
  - `Core/Src/dev_SRM.c:2195: return M_CTR_ERROR_CMD_TARGET_POS;`
  - `Core/Src/dev_SRM.c:2514: return M_CTR_ERROR_CMD_TARGET_POS;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### M_CTR_ERROR_NOT_READY

- **종류**: enum `enumMOTOR_CONTROL_ERROR` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:2059: if (Get_Inverter_Ready_State(INV_TRAVEL) == 0)	return M_CTR_ERROR_NOT_READY;`
  - `Core/Src/dev_SRM.c:2172: if (Get_Inverter_Ready_State(INV_TRAVEL) == 0)			return M_CTR_ERROR_NOT_READY;`
  - `Core/Src/dev_SRM.c:2263: if (Get_Inverter_Ready_State(INV_TRAVEL) == 0)	return M_CTR_ERROR_NOT_READY;`
  - `Core/Src/dev_SRM.c:2474: if (Get_Inverter_Ready_State(INV_HOIST) == 0)			return M_CTR_ERROR_NOT_READY;`
  - `Core/Src/dev_SRM.c:2595: if (Get_Inverter_Ready_State(INV_HOIST) == 0)	return M_CTR_ERROR_NOT_READY;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### M_CTR_ERROR_IPOS_REF

- **종류**: enum `enumMOTOR_CONTROL_ERROR` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:2060: if (Get_Inverter_Referenced_State(INV_TRAVEL) == 0)		return M_CTR_ERROR_IPOS_REF;`
  - `Core/Src/dev_SRM.c:2173: if (Get_Inverter_Referenced_State(INV_TRAVEL) == 0)		return M_CTR_ERROR_IPOS_REF;`
  - `Core/Src/dev_SRM.c:2475: if (Get_Inverter_Referenced_State(INV_HOIST) == 0)		return M_CTR_ERROR_IPOS_REF;`
  - `Core/Src/dev_SRM.c:2596: if (Get_Inverter_Referenced_State(INV_HOIST) == 0)		return M_CTR_ERROR_IPOS_REF;`
  - `Core/Src/dev_SRM.c:2872: if (Get_Inverter_Referenced_State(INV_FORK_1) == 0)		return M_CTR_ERROR_IPOS_REF;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### M_CTR_ERROR_FALUT

- **종류**: enum `enumMOTOR_CONTROL_ERROR` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:2057: if ((m_SRM_Inverter_Error) || (Get_Inverter_Fault_State(INV_TRAVEL))) return M_CTR_ERROR_FALUT;`
  - `Core/Src/dev_SRM.c:2170: if ((m_SRM_Inverter_Error) || Get_Inverter_Fault_State(INV_TRAVEL)) return M_CTR_ERROR_FALUT;`
  - `Core/Src/dev_SRM.c:2472: if ((m_SRM_Inverter_Error) || Get_Inverter_Fault_State(INV_HOIST)) return M_CTR_ERROR_FALUT;`
  - `Core/Src/dev_SRM.c:2593: if ((m_SRM_Inverter_Error) || Get_Inverter_Fault_State(INV_HOIST)) return M_CTR_ERROR_FALUT;`
  - `Core/Src/dev_SRM.c:2672: if ((m_SRM_Inverter_Error) || Get_Inverter_Fault_State(INV_HOIST)) return M_CTR_ERROR_FALUT;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_ERROR_FORK_STOP

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **값**: `90`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 포크 동작중 에러 발생 정지
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:58597: if ((m_pgmEnv.SRM_RunMode >= RUN_SEQ_ERROR_FORK_STOP) \`
  - `Core/Src/dev_SRM.c:58736: m_pgmEnv.SRM_RunMode = RUN_SEQ_ERROR_FORK_STOP;`
  - `Core/Src/dev_SRM.c:58753: m_pgmEnv.SRM_RunMode = RUN_SEQ_ERROR_FORK_STOP;`
  - `Core/Src/dev_SRM.c:58799: m_pgmEnv.SRM_RunMode = RUN_SEQ_ERROR_FORK_STOP;`
  - `Core/Src/dev_SRM.c:58921: m_pgmEnv.SRM_RunMode = RUN_SEQ_ERROR_FORK_STOP;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_ERROR_TRAV_LIFF_STOP

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 주행, 승강중 에러 발생 정지
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:49352: m_pgmEnv.SRM_RunMode = RUN_SEQ_ERROR_TRAV_LIFF_STOP;`
  - `Core/Src/dev_SRM.c:58610: m_pgmEnv.SRM_RunMode = RUN_SEQ_ERROR_TRAV_LIFF_STOP; // 91ë² ìë¬ìíë¡ ë¹ ì§ë¤.`
  - `Core/Src/dev_SRM.c:58885: m_pgmEnv.SRM_RunMode = RUN_SEQ_ERROR_TRAV_LIFF_STOP; //ì£¼íì¹ê°ì ì§ ë¹í¸ë¥¼ ìë¬ ë³ìì`
  - `Core/Src/dev_SRM.c:58938: m_pgmEnv.SRM_RunMode = RUN_SEQ_ERROR_TRAV_LIFF_STOP;`
  - `Core/Src/dev_SRM.c:59071: m_pgmEnv.SRM_RunMode = RUN_SEQ_ERROR_TRAV_LIFF_STOP;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_ERROR_TRAV_LIFT_STOP_1

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:62752: m_pgmEnv.SRM_RunMode = RUN_SEQ_ERROR_TRAV_LIFT_STOP_1;`
  - `Core/Src/dev_SRM.c:62755: case RUN_SEQ_ERROR_TRAV_LIFT_STOP_1:`
  - `Core/Inc/dev_SRM.h:1935: RUN_SEQ_ERROR_TRAV_LIFT_STOP_1,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_ERROR_TRAV_LIFT_STOP_2

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:62783: m_pgmEnv.SRM_RunMode = RUN_SEQ_ERROR_TRAV_LIFT_STOP_2;`
  - `Core/Src/dev_SRM.c:62788: case RUN_SEQ_ERROR_TRAV_LIFT_STOP_2:`
  - `Core/Inc/dev_SRM.h:1936: RUN_SEQ_ERROR_TRAV_LIFT_STOP_2,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_ERROR_TRAV_LIFT_STOP_3

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:58598: && (m_pgmEnv.SRM_RunMode <= RUN_SEQ_ERROR_TRAV_LIFT_STOP_3))`
  - `Core/Src/dev_SRM.c:62762: m_pgmEnv.SRM_RunMode = RUN_SEQ_ERROR_TRAV_LIFT_STOP_3;`
  - `Core/Src/dev_SRM.c:62792: m_pgmEnv.SRM_RunMode = RUN_SEQ_ERROR_TRAV_LIFT_STOP_3;`
  - `Core/Src/dev_SRM.c:62823: m_pgmEnv.SRM_RunMode = RUN_SEQ_ERROR_TRAV_LIFT_STOP_3;`
  - `Core/Src/dev_SRM.c:62829: case RUN_SEQ_ERROR_TRAV_LIFT_STOP_3:`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_FORK_ERROR_CENTER

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1976: RUN_SEQ_FORK_ERROR_CENTER,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HMI_MANUAL_KEY2_RESET_ERROR

- **종류**: enum `enumHMI_MANUAL_KEY_FLAG2` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:66373: case HMI_MANUAL_KEY2_RESET_ERROR:`
  - `Core/Src/dev_SRM.c:66429: case HMI_MANUAL_KEY2_RESET_ERROR:`
  - `Core/Inc/dev_SRM.h:2087: HMI_MANUAL_KEY2_RESET_ERROR,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### AUTO_POS_CTR_FORK_ERROR_STOP

- **종류**: enum `enumAUTO_POS_CTR_FORK_SEQ` 멤버
- **값**: `100`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:41602: m_Fork_Sub_Run_Step = AUTO_POS_CTR_FORK_ERROR_STOP;`
  - `Core/Src/dev_SRM.c:41615: m_Fork_Sub_Run_Step = AUTO_POS_CTR_FORK_ERROR_STOP;`
  - `Core/Src/dev_SRM.c:41677: m_Fork_Sub_Run_Step = AUTO_POS_CTR_FORK_ERROR_STOP;`
  - `Core/Src/dev_SRM.c:41722: m_Fork_Sub_Run_Step = AUTO_POS_CTR_FORK_ERROR_STOP;`
  - `Core/Src/dev_SRM.c:41799: m_Fork_Sub_Run_Step = AUTO_POS_CTR_FORK_ERROR_STOP;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_MAIN_NONE

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/error_code.h`
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Inc/error_code.h:5: ERROR1_MAIN_NONE = 0,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_DETECT_FALLING_OBJECT

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `2`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 낙하물 감지
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Inc/error_code.h:7: ERROR1_DETECT_FALLING_OBJECT = 2,		// 낙하물 감지`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_EMBERGENCY_STOP

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `3`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 비상정지 동작
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2207: save_error_code(ERROR1_EMBERGENCY_STOP, 1, 0);`
  - `Core/Src/com_tml.c:2750: save_error_code(ERROR1_EMBERGENCY_STOP, 1, 0);`
  - `Core/Src/com_tml.c:2782: save_error_code(ERROR1_EMBERGENCY_STOP, 1, 0);`
  - `Core/Src/com_tml.c:2842: save_error_code(ERROR1_EMBERGENCY_STOP, 1, 0);`
  - `Core/Src/com_tml.c:2896: save_error_code(ERROR1_EMBERGENCY_STOP, 1, 0);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_SAFETY_PULG_ON

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `6`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 안전플러그 동작
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2213: save_error_code(ERROR1_SAFETY_PULG_ON, 1, 10);`
  - `Core/Src/com_tml.c:2352: save_error_code(ERROR1_SAFETY_PULG_ON, 1, 2);`
  - `Core/Src/com_tml.c:2746: save_error_code(ERROR1_SAFETY_PULG_ON, 1, 0);`
  - `Core/Src/com_tml.c:2778: save_error_code(ERROR1_SAFETY_PULG_ON, 1, 0);`
  - `Core/Src/com_tml.c:2847: save_error_code(ERROR1_SAFETY_PULG_ON, 1, 3);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_LIFT_ROPE_TENSION

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `10`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 승강 로프텐션 이상
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:49135: save_error_code(ERROR1_LIFT_ROPE_TENSION, 1, 1);`
  - `Core/Src/dev_SRM.c:49140: save_error_code(ERROR1_LIFT_ROPE_TENSION, 1, 2);`
  - `Core/Src/dev_SRM.c:49145: save_error_code(ERROR1_LIFT_ROPE_TENSION, 2, 1);`
  - `Core/Src/dev_SRM.c:49150: save_error_code(ERROR1_LIFT_ROPE_TENSION, 2, 2);`
  - `Core/Src/dev_SRM.c:49198: save_error_code(ERROR1_LIFT_ROPE_TENSION, 3, m_pgmEnv.SRM_RunMode);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_IN_POSITION

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `11`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 정위치 이상
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/alarm.c:402: if (MainCode == ERROR1_IN_POSITION)`
  - `Core/Src/dev_SRM.c:42292: save_error_code(ERROR1_IN_POSITION, 9, nDiff);`
  - `Core/Src/dev_SRM.c:42297: save_error_code(ERROR1_IN_POSITION, 10, nDiff);`
  - `Core/Src/dev_SRM.c:42301: save_error_code(ERROR1_IN_POSITION, 11, nDiff);`
  - `Core/Src/dev_SRM.c:43330: save_error_code(ERROR1_IN_POSITION, 9, nDiff);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_RACK_POST_DETECTION

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `12`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 렉 포스트 감지 이상
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Inc/error_code.h:13: ERROR1_RACK_POST_DETECTION = 12,		// 렉 포스트 감지 이상`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_GOODS_WIDTH

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `20`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 화물 가로폭 이탈 이상
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:34899: save_error_code(ERROR1_GOODS_WIDTH, 1, m_pgmEnv.SRM_RunMode);	// íë¬¼ ê°ë¡í­ ì´í ì´ì - ì¢`
  - `Core/Src/dev_SRM.c:34925: save_error_code(ERROR1_GOODS_WIDTH, 2, m_pgmEnv.SRM_RunMode);	// íë¬¼ ê°ë¡í­ ì´í ì´ì - ì¢`
  - `Core/Src/dev_SRM.c:36283: save_error_code(ERROR1_GOODS_WIDTH, 1, m_pgmEnv.SRM_RunMode);	// íë¬¼ ê°ë¡í­ ì´í ì´ì - ì¢`
  - `Core/Src/dev_SRM.c:36309: save_error_code(ERROR1_GOODS_WIDTH, 2, m_pgmEnv.SRM_RunMode);	// íë¬¼ ê°ë¡í­ ì´í ì´ì - ì¢`
  - `Core/Src/dev_SRM.c:41925: save_error_code(ERROR1_GOODS_WIDTH, 5, m_pgmEnv.SRM_RunMode);	// íë¬¼ ê°ë¡í­ ì´í ì´ì - ì¢`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_GOODS_VERTICAL

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `21`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 화물 세로폭 이탈 이상
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:49553: save_error_code(ERROR1_GOODS_VERTICAL, 1, m_pgmEnv.SRM_RunMode);	//`
  - `Core/Src/dev_SRM.c:49558: save_error_code(ERROR1_GOODS_VERTICAL, 2, m_pgmEnv.SRM_RunMode);	//`
  - `Core/Src/dev_SRM.c:49563: save_error_code(ERROR1_GOODS_VERTICAL, 3, m_pgmEnv.SRM_RunMode);	//`
  - `Core/Src/dev_SRM.c:49568: save_error_code(ERROR1_GOODS_VERTICAL, 4, m_pgmEnv.SRM_RunMode);	//`
  - `Core/Src/dev_SRM.c:49573: save_error_code(ERROR1_GOODS_VERTICAL, 11, m_pgmEnv.SRM_RunMode);	//`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_SPECIAL_RACK

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `23`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 스페셜랙 이상
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2514: save_error_code(ERROR1_SPECIAL_RACK, 1, accept[0]);`
  - `Core/Src/com_tml.c:2570: save_error_code(ERROR1_SPECIAL_RACK, 1, 0);`
  - `Core/Src/com_tml.c:2610: save_error_code(ERROR1_SPECIAL_RACK, 1, pCmd->OrderCode);`
  - `Core/Src/com_tml.c:2641: save_error_code(ERROR1_SPECIAL_RACK, 1, 0);`
  - `Core/Inc/error_code.h:17: ERROR1_SPECIAL_RACK = 23,				// 스페셜랙 이상`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_LIMIT

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `26`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 비상정지 (리미트스위치)
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:29744: save_error_code(ERROR1_LIMIT, 2, 4);	// ì£¼í HP ìì¹ ê°ì§`
  - `Core/Src/dev_SRM.c:29757: save_error_code(ERROR1_LIMIT, 2, 5);	// ì£¼í OP ìì¹ ê°ì§`
  - `Core/Src/dev_SRM.c:29904: save_error_code(ERROR1_LIMIT, 1, 5);	// ì¹ê° OP ìì¹ ê°ì§`
  - `Core/Src/dev_SRM.c:29922: save_error_code(ERROR1_LIMIT, 1, 4);	// ì¹ê° HP ìì¹ ê°ì§`
  - `Core/Src/dev_SRM.c:30244: save_error_code(ERROR1_LIMIT, 2, 4);	// ì£¼í HP ìì¹ ê°ì§`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_FORK_SENSOR

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `33`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 포크 센서 이상 (원점)
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:41654: save_error_code(ERROR1_FORK_SENSOR, 27, 0);`
  - `Core/Src/dev_SRM.c:41659: save_error_code(ERROR1_FORK_SENSOR, 28, 0);`
  - `Core/Src/dev_SRM.c:41666: save_error_code(ERROR1_FORK_SENSOR, 27, 1);`
  - `Core/Src/dev_SRM.c:41673: save_error_code(ERROR1_FORK_SENSOR, 28, 1);`
  - `Core/Src/dev_SRM.c:42241: save_error_code(ERROR1_FORK_SENSOR, 11, m_pgmEnv.SRM_RunMode);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_LIFT_SENSOR

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `38`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 승강 센서 이상 (감속, 원점)
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:49423: save_error_code(ERROR1_LIFT_SENSOR, 3, nErrorReason);`
  - `Core/Src/dev_SRM.c:49444: save_error_code(ERROR1_LIFT_SENSOR, 1, 0);`
  - `Core/Src/dev_SRM.c:49460: save_error_code(ERROR1_LIFT_SENSOR, 2, 1);`
  - `Core/Src/dev_SRM.c:49464: save_error_code(ERROR1_LIFT_SENSOR, 2, 2);`
  - `Core/Src/dev_SRM.c:49767: save_error_code(ERROR1_LIFT_SENSOR, 2, nErrorReason);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_TRAVEL_SENSOR

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `39`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 주행 센서 이상 (감속, 원점)
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:49417: save_error_code(ERROR1_TRAVEL_SENSOR, 3, nErrorReason);`
  - `Core/Src/dev_SRM.c:49476: save_error_code(ERROR1_TRAVEL_SENSOR, 1, 0);`
  - `Core/Src/dev_SRM.c:49492: save_error_code(ERROR1_TRAVEL_SENSOR, 2, 1);`
  - `Core/Src/dev_SRM.c:49496: save_error_code(ERROR1_TRAVEL_SENSOR, 2, 2);`
  - `Core/Src/dev_SRM.c:49745: save_error_code(ERROR1_TRAVEL_SENSOR, 3, nErrorReason);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_POWER_REGENERATION

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `42`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 전력 회생 유닛 이상, 미적용
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Inc/error_code.h:25: ERROR1_POWER_REGENERATION = 42,		// 전력 회생 유닛 이상, 미적용`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_INVERTER_FORK

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `44`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 포크 인버터 이상
- **용도(읽는 법)**: 인버터/EtherCAT 상태. m_ExtSEnv와 함께 확인. 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:8958: save_error_code(ERROR1_INVERTER_FORK, 5, abs(nActualTorque / 10));`
  - `Core/Src/dev_SRM.c:8987: save_error_code(ERROR1_INVERTER_FORK, 5, abs(nActualTorque / 10));`
  - `Core/Src/dev_SRM.c:9023: save_error_code(ERROR1_INVERTER_FORK, 5, abs(nActualTorque / 10));`
  - `Core/Src/dev_SRM.c:9057: save_error_code(ERROR1_INVERTER_FORK, 5, abs(nActualTorque / 10));`
  - `Core/Src/dev_SRM.c:33153: if (m_St.MainErrCode == ERROR1_INVERTER_FORK)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_INVERTER_FORK2

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `45`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 포크2 인버터 이상
- **용도(읽는 법)**: 인버터/EtherCAT 상태. m_ExtSEnv와 함께 확인. 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:67713: save_error_code(ERROR1_INVERTER_FORK2, 1, 3);`
  - `Core/Inc/error_code.h:27: ERROR1_INVERTER_FORK2 = 45,			// 포크2 인버터 이상`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_INVERTER_TRAVEL

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `46`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 주행 인버터 이상
- **용도(읽는 법)**: 인버터/EtherCAT 상태. m_ExtSEnv와 함께 확인. 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:30696: if (m_St.MainErrCode == ERROR1_INVERTER_TRAVEL)`
  - `Core/Src/dev_SRM.c:30711: if (m_St.MainErrCode == ERROR1_INVERTER_TRAVEL)`
  - `Core/Src/dev_SRM.c:30768: save_error_code(ERROR1_INVERTER_TRAVEL, 5, abs(Get_Inverter_Actual_Touqe(nInvertor) / 10));`
  - `Core/Src/dev_SRM.c:44693: save_error_code(ERROR1_INVERTER_TRAVEL, 3, nSto_State);`
  - `Core/Src/dev_SRM.c:48592: save_error_code_Invertor(ERROR1_INVERTER_TRAVEL, 1, 2);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_INVERTER_HOIST

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `47`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 승강 인버터 이상
- **용도(읽는 법)**: 인버터/EtherCAT 상태. m_ExtSEnv와 함께 확인. 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:31808: if (m_St.MainErrCode == ERROR1_INVERTER_HOIST)`
  - `Core/Src/dev_SRM.c:31824: if (m_St.MainErrCode == ERROR1_INVERTER_HOIST)`
  - `Core/Src/dev_SRM.c:31884: save_error_code(ERROR1_INVERTER_HOIST, 5, abs(Get_Inverter_Actual_Touqe(nInvertor) / 10));`
  - `Core/Src/dev_SRM.c:44642: && (m_St.MainErrCode <= ERROR1_INVERTER_HOIST))`
  - `Core/Src/dev_SRM.c:44689: save_error_code(ERROR1_INVERTER_HOIST, 3, nSto_State);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_INVERTER_TRAVEL2

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `49`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 주행2 인버터 이상
- **용도(읽는 법)**: 인버터/EtherCAT 상태. m_ExtSEnv와 함께 확인. 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Inc/error_code.h:30: ERROR1_INVERTER_TRAVEL2 = 49,			// 주행2 인버터 이상`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_LIFT_DECEL_DOG

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `53`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 승강 감속 이상
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:56013: save_error_code(ERROR1_LIFT_DECEL_DOG, 1, 1);`
  - `Core/Src/dev_SRM.c:56024: save_error_code(ERROR1_LIFT_DECEL_DOG, 1, 2);`
  - `Core/Src/dev_SRM.c:56035: save_error_code(ERROR1_LIFT_DECEL_DOG, 1, 3);`
  - `Core/Src/dev_SRM.c:56049: save_error_code(ERROR1_LIFT_DECEL_DOG, 1, 4);`
  - `Core/Src/dev_SRM.c:56081: save_error_code(ERROR1_LIFT_DECEL_DOG, 3, 1);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_TRAV_DECEL_DOG

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `54`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 주행 감속 이상
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:55345: save_error_code(ERROR1_TRAV_DECEL_DOG, 1, 1);`
  - `Core/Src/dev_SRM.c:55356: save_error_code(ERROR1_TRAV_DECEL_DOG, 1, 2);`
  - `Core/Src/dev_SRM.c:55367: save_error_code(ERROR1_TRAV_DECEL_DOG, 1, 3);`
  - `Core/Src/dev_SRM.c:55381: save_error_code(ERROR1_TRAV_DECEL_DOG, 1, 4);`
  - `Core/Src/dev_SRM.c:55413: save_error_code(ERROR1_TRAV_DECEL_DOG, 3, 1);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_DOUBLE_ENTRY_LEFT

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `60`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 이중입고 이상 (좌)
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:60697: save_error_code(ERROR1_DOUBLE_ENTRY_LEFT, 14, nFlag);`
  - `Core/Src/dev_SRM.c:60708: save_error_code(ERROR1_DOUBLE_ENTRY_LEFT, 1, 0);`
  - `Core/Src/dev_SRM.c:60712: save_error_code(ERROR1_DOUBLE_ENTRY_LEFT, 15, 0);`
  - `Core/Src/dev_SRM.c:61425: save_error_code(ERROR1_DOUBLE_ENTRY_LEFT, 4, s_Cur_DST_State);`
  - `Core/Src/dev_SRM.c:61429: save_error_code(ERROR1_DOUBLE_ENTRY_LEFT, 17, s_Cur_DST_State);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_DOUBLE_ENTRY_RIGHT

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `61`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 이중입고 이상 (우)
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:60702: save_error_code(ERROR1_DOUBLE_ENTRY_RIGHT, 14, nFlag);`
  - `Core/Src/dev_SRM.c:60719: save_error_code(ERROR1_DOUBLE_ENTRY_RIGHT, 1, 0);`
  - `Core/Src/dev_SRM.c:60723: save_error_code(ERROR1_DOUBLE_ENTRY_RIGHT, 15, 0);`
  - `Core/Src/dev_SRM.c:61439: save_error_code(ERROR1_DOUBLE_ENTRY_RIGHT, 4, s_Cur_DST_State);`
  - `Core/Src/dev_SRM.c:61474: save_error_code(ERROR1_DOUBLE_ENTRY_RIGHT, 1, s_Cur_DST_State);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_CARRIER_GOODS_SENSOR_1

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `62`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 화물 이상1
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Inc/error_code.h:37: ERROR1_CARRIER_GOODS_SENSOR_1 = 62,		// 화물 이상1`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_CARRIER_GOODS_SENSOR_2

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `63`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 화물 이상2
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2416: save_error_code(ERROR1_CARRIER_GOODS_SENSOR_2, 3, pCmd->OrderCode);`
  - `Core/Src/dev_SRM.c:46077: save_error_code(ERROR1_CARRIER_GOODS_SENSOR_2, 4, 1);`
  - `Core/Src/dev_SRM.c:46262: save_error_code(ERROR1_CARRIER_GOODS_SENSOR_2, 3, 1);`
  - `Core/Src/dev_SRM.c:46441: save_error_code(ERROR1_CARRIER_GOODS_SENSOR_2, 4, 2);`
  - `Core/Src/dev_SRM.c:46531: save_error_code(ERROR1_CARRIER_GOODS_SENSOR_2, 3, 1);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_EMPTY_GOODS

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `64`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 공출고/공입고
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:58920: save_error_code(ERROR1_EMPTY_GOODS, 1, m_pgmEnv.SRM_RunMode); // ê·¸ë¥ ë°ë¡ ìë¬ë¥¼ ëì´ë¤.`
  - `Core/Src/dev_SRM.c:61057: save_error_code(ERROR1_EMPTY_GOODS, 4, m_pgmEnv.SRM_RunMode);`
  - `Core/Src/dev_SRM.c:61080: save_error_code(ERROR1_EMPTY_GOODS, 1, m_pgmEnv.SRM_RunMode);`
  - `Core/Src/dev_SRM.c:62462: save_error_code(ERROR1_EMPTY_GOODS, 4, m_pgmEnv.SRM_RunMode);`
  - `Core/Src/dev_SRM.c:62485: save_error_code(ERROR1_EMPTY_GOODS, 1, m_pgmEnv.SRM_RunMode);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_LOADED_GOODS

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `65`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: LOADED
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:58884: save_error_code(ERROR1_LOADED_GOODS, 1, 1); //ìë¬ë¥¼ ëì´ë¤`
  - `Core/Src/dev_SRM.c:58937: save_error_code(ERROR1_LOADED_GOODS, 1, 1); // ìë¬ë¥¼ ëì`
  - `Core/Src/dev_SRM.c:61794: save_error_code(ERROR1_LOADED_GOODS, 1, nFlag);`
  - `Core/Inc/error_code.h:40: ERROR1_LOADED_GOODS = 65,				// LOADED`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_ORDER_ABNORMAL

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `66`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 작업 명령 이상
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2506: save_error_code(ERROR1_ORDER_ABNORMAL, 1, pCmd->OrderCode);`
  - `Core/Src/com_tml.c:2562: save_error_code(ERROR1_ORDER_ABNORMAL, 1, pCmd->OrderCode);`
  - `Core/Src/com_tml.c:2602: save_error_code(ERROR1_ORDER_ABNORMAL, 1, pCmd->OrderCode);`
  - `Core/Src/com_tml.c:2633: save_error_code(ERROR1_ORDER_ABNORMAL, 1, pCmd->OrderCode);`
  - `Core/Src/dev_SRM.c:50646: save_error_code(ERROR1_ORDER_ABNORMAL, 5, nStationNO + 1);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_WORK_TIMEOUT

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `80`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 반송 동작 시간 초과
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:55677: save_error_code(ERROR1_WORK_TIMEOUT, 2, nFlag);`
  - `Core/Src/dev_SRM.c:55685: save_error_code(ERROR1_WORK_TIMEOUT, 2, 0);`
  - `Core/Src/dev_SRM.c:55812: save_error_code(ERROR1_WORK_TIMEOUT, 2, 3);`
  - `Core/Src/dev_SRM.c:56346: save_error_code(ERROR1_WORK_TIMEOUT, 3, nFlag);`
  - `Core/Src/dev_SRM.c:56353: save_error_code(ERROR1_WORK_TIMEOUT, 3, 0);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_FORK_TIMEOUT

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `81`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 포킹 동작 시간 초과
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:40989: save_error_code(ERROR1_FORK_TIMEOUT, 3, m_pgmEnv.SRM_RunMode);`
  - `Core/Src/dev_SRM.c:41721: save_error_code(ERROR1_FORK_TIMEOUT, 3, m_pgmEnv.SRM_RunMode);`
  - `Core/Src/dev_SRM.c:42669: save_error_code(ERROR1_FORK_TIMEOUT, 3, m_pgmEnv.SRM_RunMode);`
  - `Core/Src/dev_SRM.c:60737: save_error_code(ERROR1_FORK_TIMEOUT, 1, m_pgmEnv.SRM_RunMode);`
  - `Core/Src/dev_SRM.c:60987: save_error_code(ERROR1_FORK_TIMEOUT, 2, m_pgmEnv.SRM_RunMode);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_STATION_INTERLOCK_TIMEOUT

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `82`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 스테이션 인터록 대기시간 초과
- **용도(읽는 법)**: 인터록: 스테이션/CV OK 대기. 타임아웃→ERROR1_STATION_INTERLOCK_TIMEOUT. 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:60500: save_error_code(ERROR1_STATION_INTERLOCK_TIMEOUT, 1, m_pgmEnv.SRM_RunMode);`
  - `Core/Src/dev_SRM.c:61167: save_error_code(ERROR1_STATION_INTERLOCK_TIMEOUT, 1, m_pgmEnv.SRM_RunMode);`
  - `Core/Inc/error_code.h:47: ERROR1_STATION_INTERLOCK_TIMEOUT = 82,	// 스테이션 인터록 대기시간 초과`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_REFERENCE_CHECK

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `89`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 원점 확인 이상
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:8092: save_error_code(ERROR1_REFERENCE_CHECK, 2, 10);`
  - `Core/Src/dev_SRM.c:8441: save_error_code(ERROR1_REFERENCE_CHECK, 2, 10);`
  - `Core/Src/dev_SRM.c:8806: save_error_code(ERROR1_REFERENCE_CHECK, 3, 10);`
  - `Core/Src/dev_SRM.c:8862: save_error_code(ERROR1_REFERENCE_CHECK, 3, nForkState);`
  - `Core/Src/dev_SRM.c:8883: save_error_code(ERROR1_REFERENCE_CHECK, 3, 4);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_MODEM_ALARM

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `96`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 광모뎀 이상
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:49431: save_error_code(ERROR1_MODEM_ALARM, 1, 0);`
  - `Core/Src/dev_SRM.c:49652: save_error_code(ERROR1_MODEM_ALARM, 1, 0);`
  - `Core/Src/dev_SRM.c:49787: save_error_code(ERROR1_MODEM_ALARM, 1, 0);`
  - `Core/Src/dev_SRM.c:49925: save_error_code(ERROR1_MODEM_ALARM, 1, 0);`
  - `Core/Src/dev_SRM.c:49938: save_error_code(ERROR1_MODEM_ALARM, 1, 0);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_DOOR_OPEN

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `97`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 기상반 도어 열림
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:49436: save_error_code(ERROR1_DOOR_OPEN, 1, 0);`
  - `Core/Src/dev_SRM.c:49658: save_error_code(ERROR1_DOOR_OPEN, 1, 0);`
  - `Core/Src/dev_SRM.c:49792: save_error_code(ERROR1_DOOR_OPEN, 1, 0);`
  - `Core/Src/dev_SRM.c:49930: save_error_code(ERROR1_DOOR_OPEN, 1, 0);`
  - `Core/Src/dev_SRM.c:49943: save_error_code(ERROR1_DOOR_OPEN, 1, 0);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_DEVICE_EMG

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `98`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 기상반 비상정지 동작
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:49177: save_error_code(ERROR1_DEVICE_EMG, 1, 0);`
  - `Core/Src/dev_SRM.c:49226: save_error_code(ERROR1_DEVICE_EMG, 1, 0);`
  - `Core/Inc/error_code.h:53: ERROR1_DEVICE_EMG = 98,				//기상반 비상정지 동작`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_SEW_COM

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `100`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: SEW MoviC PLC 통신 이상
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:58608: if ((m_St.MainErrCode == ERROR1_SEW_COM) || (m_St.MainErrCode == ERROR1_ETHERCAT))//sew ì¸ë²í° í`
  - `Core/Src/dev_SRM.c:59373: save_error_code(ERROR1_SEW_COM, 1, 2);`
  - `Core/Src/dev_SRM.c:63717: save_error_code(ERROR1_SEW_COM, 1, 0);`
  - `Core/Src/dev_SRM.c:68109: save_error_code(ERROR1_SEW_COM, 1, 1);`
  - `Core/Inc/error_code.h:55: ERROR1_SEW_COM = 100,				// SEW MoviC PLC 통신 이상`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_ETHERCAT

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `101`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 이더켓 통신 이상
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:49725: save_error_code(ERROR1_ETHERCAT, 10, 1);`
  - `Core/Src/dev_SRM.c:58608: if ((m_St.MainErrCode == ERROR1_SEW_COM) || (m_St.MainErrCode == ERROR1_ETHERCAT))//sew ì¸ë²í° í`
  - `Core/Src/ecat_main.c:4002: save_error_code(ERROR1_ETHERCAT, 1, 1);`
  - `Core/Src/ecat_main.c:4129: save_error_code(ERROR1_ETHERCAT, 4, i);`
  - `Core/Src/ecat_main.c:4137: save_error_code(ERROR1_ETHERCAT, 3, i);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_BRAKE_MMS_TRIP

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `102`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 브레이크 전원 MMS트립
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:49303: save_error_code(ERROR1_BRAKE_MMS_TRIP, 2, 0);`
  - `Core/Src/dev_SRM.c:49321: save_error_code(ERROR1_BRAKE_MMS_TRIP, 1, 0);`
  - `Core/Src/dev_SRM.c:49339: save_error_code(ERROR1_BRAKE_MMS_TRIP, 3, 0);`
  - `Core/Inc/error_code.h:59: ERROR1_BRAKE_MMS_TRIP = 102,		// 브레이크 전원 MMS트립`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_POWER_INIT_ERROR

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `103`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 제어전원 초기화 이상
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:63614: save_error_code(ERROR1_POWER_INIT_ERROR, s_Init_Error, 0);`
  - `Core/Inc/error_code.h:60: ERROR1_POWER_INIT_ERROR = 103,		// 제어전원 초기화 이상`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_CONVERTOR

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `104`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 컨버터 이상
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:63640: save_error_code(ERROR1_CONVERTOR, s_Init_Error, 0);`
  - `Core/Inc/error_code.h:61: ERROR1_CONVERTOR = 104,					// 컨버터 이상`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_INTERLOCK_CVOK

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `105`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 포크 동작중 인터락 이상
- **용도(읽는 법)**: 인터록: 스테이션/CV OK 대기. 타임아웃→ERROR1_STATION_INTERLOCK_TIMEOUT. 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:41160: save_error_code(ERROR1_INTERLOCK_CVOK, pWorkData->Station_No, nInterLock_No);`
  - `Core/Src/dev_SRM.c:41882: save_error_code(ERROR1_INTERLOCK_CVOK, pWorkData->Station_No, nInterLock_No);`
  - `Core/Src/dev_SRM.c:42834: save_error_code(ERROR1_INTERLOCK_CVOK, pWorkData->Station_No, nInterLock_No);`
  - `Core/Inc/error_code.h:67: ERROR1_INTERLOCK_CVOK = 105,		// 포크 동작중 인터락 이상`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_TRAV_POSITION

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `106`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 주행 위치 이상
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:49776: save_error_code(ERROR1_TRAV_POSITION, 2, nErrorReason);`
  - `Core/Inc/error_code.h:68: ERROR1_TRAV_POSITION = 106,			// 주행 위치 이상`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_LIFT_POSITION

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `107`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 승강 위치 이상
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:49760: save_error_code(ERROR1_LIFT_POSITION, 2, nErrorReason);`
  - `Core/Inc/error_code.h:69: ERROR1_LIFT_POSITION = 107,			// 승강 위치 이상`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_FORK_POSITION

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `108`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: 포크 위치 이상
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:40626: save_error_code(ERROR1_FORK_POSITION, 1, ForkProfile.mode);`
  - `Core/Src/dev_SRM.c:41210: save_error_code(ERROR1_FORK_POSITION, 5, 1);`
  - `Core/Src/dev_SRM.c:41223: save_error_code(ERROR1_FORK_POSITION, 5, 2);`
  - `Core/Src/dev_SRM.c:41291: save_error_code(ERROR1_FORK_POSITION, 2, 3);`
  - `Core/Src/dev_SRM.c:41317: save_error_code(ERROR1_FORK_POSITION, 2, 2);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERRRO1_LIDAR_FAULT

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `109`
- **정의 위치**: `Core/Inc/error_code.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:67868: save_error_code(ERRRO1_LIDAR_FAULT, 1, 0);`
  - `Core/Src/dev_SRM.c:67887: save_error_code(ERRRO1_LIDAR_FAULT, 2, 0);`
  - `Core/Inc/error_code.h:72: ERRRO1_LIDAR_FAULT = 109,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ERROR1_MCU_PARAM_DATA

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `110`
- **정의 위치**: `Core/Inc/error_code.h`
- **원문 주석**: MICOM 데이터 이상
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:182: save_error_code(ERROR1_MCU_PARAM_DATA, 1, 1);`
  - `Core/Src/SRM_Parameter.c:209: save_error_code(ERROR1_MCU_PARAM_DATA, 1, 2);`
  - `Core/Src/SRM_Parameter.c:435: save_error_code(ERROR1_MCU_PARAM_DATA, 2, 1);`
  - `Core/Src/SRM_Parameter.c:451: save_error_code(ERROR1_MCU_PARAM_DATA, 2, 0);`
  - `Core/Src/SRM_Parameter.c:572: save_error_code(ERROR1_MCU_PARAM_DATA, 3, 0);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MAX_ERROR1_CODE

- **종류**: enum `enumERROR1_CODE` 멤버
- **값**: `255`
- **정의 위치**: `Core/Inc/error_code.h`
- **용도(읽는 법)**: 에러코드: error_code.h. RunMode ERROR_* 전환 추적.
- **코드 참조 예**:
  - `Core/Inc/error_code.h:85: MAX_ERROR1_CODE = 255,				//`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### COMMAND_ERROR_NONE

- **종류**: enum `enumCOMMAND_ERROR` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/error_code.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:46096: return COMMAND_ERROR_NONE;`
  - `Core/Src/dev_SRM.c:46149: if (error[POS_FORK_1] == COMMAND_ERROR_NONE)`
  - `Core/Src/dev_SRM.c:46201: if (error[POS_FORK_1] == COMMAND_ERROR_NONE)`
  - `Core/Src/dev_SRM.c:46229: if (error[POS_FORK_1] == COMMAND_ERROR_NONE)`
  - `Core/Src/dev_SRM.c:46268: if (error[POS_FORK_1] == COMMAND_ERROR_NONE)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### COMMAND_ERROR_FALUT_STATE

- **종류**: enum `enumCOMMAND_ERROR` 멤버
- **정의 위치**: `Core/Inc/error_code.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2368: ret_value[0] = COMMAND_ERROR_FALUT_STATE;  // 이상 발생`
  - `Core/Src/com_tml.c:2503: ret_value[0] = COMMAND_ERROR_FALUT_STATE;`
  - `Core/Src/com_tml.c:2513: ret_value[0] = COMMAND_ERROR_FALUT_STATE;`
  - `Core/Src/com_tml.c:2563: ret_value[0] = COMMAND_ERROR_FALUT_STATE;`
  - `Core/Src/com_tml.c:2571: ret_value[0] = COMMAND_ERROR_FALUT_STATE;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### COMMAND_ERROR_FORK_CENTER_OFF

- **종류**: enum `enumCOMMAND_ERROR` 멤버
- **정의 위치**: `Core/Inc/error_code.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2381: ret_value[0] = COMMAND_ERROR_FORK_CENTER_OFF;`
  - `Core/Src/dev_SRM.c:46861: nResult = COMMAND_ERROR_FORK_CENTER_OFF;`
  - `Core/Inc/error_code.h:135: COMMAND_ERROR_FORK_CENTER_OFF,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### COMMAND_ERROR_TRAVEL_POSITION_IS_OUT_OF_SET_RANGE

- **종류**: enum `enumCOMMAND_ERROR` 멤버
- **정의 위치**: `Core/Inc/error_code.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:46233: error[POS_FORK_1] = COMMAND_ERROR_TRAVEL_POSITION_IS_OUT_OF_SET_RANGE;`
  - `Core/Src/dev_SRM.c:46334: error[POS_FORK_1] = COMMAND_ERROR_TRAVEL_POSITION_IS_OUT_OF_SET_RANGE;`
  - `Core/Src/dev_SRM.c:46410: error[POS_FORK_1] = COMMAND_ERROR_TRAVEL_POSITION_IS_OUT_OF_SET_RANGE;`
  - `Core/Src/dev_SRM.c:46509: error[POS_FORK_1] = COMMAND_ERROR_TRAVEL_POSITION_IS_OUT_OF_SET_RANGE;`
  - `Core/Src/dev_SRM.c:46597: error[POS_FORK_1] = COMMAND_ERROR_TRAVEL_POSITION_IS_OUT_OF_SET_RANGE;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### COMMAND_ERROR_LIFT_POSITION_IS_OUT_OF_SET_RANGE

- **종류**: enum `enumCOMMAND_ERROR` 멤버
- **정의 위치**: `Core/Inc/error_code.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:46238: error[POS_FORK_1] = COMMAND_ERROR_LIFT_POSITION_IS_OUT_OF_SET_RANGE;`
  - `Core/Src/dev_SRM.c:46340: error[POS_FORK_1] = COMMAND_ERROR_LIFT_POSITION_IS_OUT_OF_SET_RANGE;`
  - `Core/Src/dev_SRM.c:46415: error[POS_FORK_1] = COMMAND_ERROR_LIFT_POSITION_IS_OUT_OF_SET_RANGE;`
  - `Core/Src/dev_SRM.c:46514: error[POS_FORK_1] = COMMAND_ERROR_LIFT_POSITION_IS_OUT_OF_SET_RANGE;`
  - `Core/Src/dev_SRM.c:46603: error[POS_FORK_1] = COMMAND_ERROR_LIFT_POSITION_IS_OUT_OF_SET_RANGE;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### COMMAND_ERROR_NON_AUTOMATIC_MODE

- **종류**: enum `enumCOMMAND_ERROR` 멤버
- **정의 위치**: `Core/Inc/error_code.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2385: ret_value[0] = COMMAND_ERROR_NON_AUTOMATIC_MODE;   // 수동모드`
  - `Core/Src/dev_SRM.c:46127: return COMMAND_ERROR_NON_AUTOMATIC_MODE;`
  - `Core/Inc/error_code.h:138: COMMAND_ERROR_NON_AUTOMATIC_MODE,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### COMMAND_ERROR_NON_ONLINE

- **종류**: enum `enumCOMMAND_ERROR` 멤버
- **정의 위치**: `Core/Inc/error_code.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2404: ret_value[0] = COMMAND_ERROR_NON_ONLINE;`
  - `Core/Src/dev_SRM.c:46120: return COMMAND_ERROR_NON_ONLINE;`
  - `Core/Src/dev_SRM.c:46854: nResult = COMMAND_ERROR_NON_ONLINE;`
  - `Core/Inc/error_code.h:139: COMMAND_ERROR_NON_ONLINE,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### COMMAND_ERROR_RACK_POSITION_BLANK

- **종류**: enum `enumCOMMAND_ERROR` 멤버
- **정의 위치**: `Core/Inc/error_code.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:45994: return COMMAND_ERROR_RACK_POSITION_BLANK;`
  - `Core/Inc/error_code.h:140: COMMAND_ERROR_RACK_POSITION_BLANK,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### COMMAND_ERROR_STATION_POSITION

- **종류**: enum `enumCOMMAND_ERROR` 멤버
- **정의 위치**: `Core/Inc/error_code.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:46065: return COMMAND_ERROR_STATION_POSITION;`
  - `Core/Inc/error_code.h:141: COMMAND_ERROR_STATION_POSITION,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### COMMAND_ERROR_FORK_DEPTH_IS_OUT_OF_SET_RANGE

- **종류**: enum `enumCOMMAND_ERROR` 멤버
- **정의 위치**: `Core/Inc/error_code.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:45370: nReturn = COMMAND_ERROR_FORK_DEPTH_IS_OUT_OF_SET_RANGE;`
  - `Core/Src/dev_SRM.c:45392: nReturn = COMMAND_ERROR_FORK_DEPTH_IS_OUT_OF_SET_RANGE;`
  - `Core/Src/dev_SRM.c:45419: nReturn = COMMAND_ERROR_FORK_DEPTH_IS_OUT_OF_SET_RANGE;`
  - `Core/Src/dev_SRM.c:45423: nReturn = COMMAND_ERROR_FORK_DEPTH_IS_OUT_OF_SET_RANGE;`
  - `Core/Src/dev_SRM.c:45439: nReturn = COMMAND_ERROR_FORK_DEPTH_IS_OUT_OF_SET_RANGE;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### COMMAND_ERROR_NOT_WITHIN_THE_SET_RANGE

- **종류**: enum `enumCOMMAND_ERROR` 멤버
- **값**: `10`
- **정의 위치**: `Core/Inc/error_code.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2466: if (accept[0])  ret_value[0] = COMMAND_ERROR_NOT_WITHIN_THE_SET_RANGE;  // 설정범위를 벗어남`
  - `Core/Src/com_tml.c:2495: ret_value[0] = COMMAND_ERROR_NOT_WITHIN_THE_SET_RANGE;  // 설정범위를 벗어남`
  - `Core/Src/com_tml.c:2554: ret_value[0] = COMMAND_ERROR_NOT_WITHIN_THE_SET_RANGE;  // 설정범위를 벗어남`
  - `Core/Src/com_tml.c:2595: ret_value[0] = COMMAND_ERROR_NOT_WITHIN_THE_SET_RANGE;  // 설정범위를 벗어남`
  - `Core/Src/com_tml.c:2625: ret_value[0] = COMMAND_ERROR_NOT_WITHIN_THE_SET_RANGE;  // 설정범위를 벗어남`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### COMMAND_ERROR_CARGO_DETECTION_STATUS

- **종류**: enum `enumCOMMAND_ERROR` 멤버
- **정의 위치**: `Core/Inc/error_code.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2419: ret_value[0] = COMMAND_ERROR_CARGO_DETECTION_STATUS;   // 이상상황`
  - `Core/Inc/error_code.h:145: COMMAND_ERROR_CARGO_DETECTION_STATUS,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### COMMAND_ERROR_PREVIOUS_TASK_PAUSE

- **종류**: enum `enumCOMMAND_ERROR` 멤버
- **정의 위치**: `Core/Inc/error_code.h`
- **용도(읽는 법)**: Task: TML 0x40 다중작업. 0x41과 분기 다름.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2481: ret_value[0] = COMMAND_ERROR_PREVIOUS_TASK_PAUSE;`
  - `Core/Src/com_tml.c:2536: ret_value[0] = COMMAND_ERROR_PREVIOUS_TASK_PAUSE;`
  - `Core/Inc/error_code.h:146: COMMAND_ERROR_PREVIOUS_TASK_PAUSE,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### COMMAND_ERROR_PREVIOUS_TASK_FAILURE

- **종류**: enum `enumCOMMAND_ERROR` 멤버
- **정의 위치**: `Core/Inc/error_code.h`
- **용도(읽는 법)**: Task: TML 0x40 다중작업. 0x41과 분기 다름.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2485: ret_value[0] = COMMAND_ERROR_PREVIOUS_TASK_FAILURE;`
  - `Core/Inc/error_code.h:147: COMMAND_ERROR_PREVIOUS_TASK_FAILURE,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### COMMAND_ERROR_EXECUTING_PREVIOUS_COMMAND

- **종류**: enum `enumCOMMAND_ERROR` 멤버
- **정의 위치**: `Core/Inc/error_code.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2376: ret_value[0] = COMMAND_ERROR_EXECUTING_PREVIOUS_COMMAND;`
  - `Core/Src/com_tml.c:2460: ret_value[0] = COMMAND_ERROR_EXECUTING_PREVIOUS_COMMAND;`
  - `Core/Src/com_tml.c:2477: ret_value[0] = COMMAND_ERROR_EXECUTING_PREVIOUS_COMMAND;`
  - `Core/Src/com_tml.c:2532: ret_value[0] = COMMAND_ERROR_EXECUTING_PREVIOUS_COMMAND;`
  - `Core/Src/dev_SRM.c:46140: error[POS_FORK_1] = COMMAND_ERROR_EXECUTING_PREVIOUS_COMMAND;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### COMMAND_ERROR_JOB_NUMBER_ZEOR

- **종류**: enum `enumCOMMAND_ERROR` 멤버
- **정의 위치**: `Core/Inc/error_code.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2522: ret_value[0] = COMMAND_ERROR_JOB_NUMBER_ZEOR;`
  - `Core/Inc/error_code.h:149: COMMAND_ERROR_JOB_NUMBER_ZEOR,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### COMMAND_ERROR_JOB_NUMBER_ABNORMAL

- **종류**: enum `enumCOMMAND_ERROR` 멤버
- **정의 위치**: `Core/Inc/error_code.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2651: ret_value[0] = COMMAND_ERROR_JOB_NUMBER_ABNORMAL;`
  - `Core/Src/dev_SRM.c:46135: error[POS_FORK_1] = COMMAND_ERROR_JOB_NUMBER_ABNORMAL;`
  - `Core/Inc/error_code.h:150: COMMAND_ERROR_JOB_NUMBER_ABNORMAL,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### COMMAND_ERROR_RECEIVING_DESTINATION_CHANGE_COMMAND_IN_JOB_COMPLETION_STATUS

- **종류**: enum `enumCOMMAND_ERROR` 멤버
- **정의 위치**: `Core/Inc/error_code.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2586: ret_value[0] = COMMAND_ERROR_RECEIVING_DESTINATION_CHANGE_COMMAND_IN_JOB_COMPLETION_STATUS;`
  - `Core/Inc/error_code.h:151: COMMAND_ERROR_RECEIVING_DESTINATION_CHANGE_COMMAND_IN_JOB_COMPLETION_STATUS,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### COMMAND_ERROR_MANUAL_SW_ON

- **종류**: enum `enumCOMMAND_ERROR` 멤버
- **정의 위치**: `Core/Inc/error_code.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2372: ret_value[0] = COMMAND_ERROR_MANUAL_SW_ON;`
  - `Core/Inc/error_code.h:152: COMMAND_ERROR_MANUAL_SW_ON,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### COMMAND_ERROR_DENIED_RACK_CHG

- **종류**: enum `enumCOMMAND_ERROR` 멤버
- **정의 위치**: `Core/Inc/error_code.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:46100: return COMMAND_ERROR_DENIED_RACK_CHG;`
  - `Core/Src/dev_SRM.c:46106: return COMMAND_ERROR_DENIED_RACK_CHG;`
  - `Core/Inc/error_code.h:153: COMMAND_ERROR_DENIED_RACK_CHG,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### COMMAND_ERROR_CMD_NO_DEFINE

- **종류**: enum `enumCOMMAND_ERROR` 멤버
- **정의 위치**: `Core/Inc/error_code.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:46615: error[POS_FORK_1] = COMMAND_ERROR_CMD_NO_DEFINE;`
  - `Core/Inc/error_code.h:154: COMMAND_ERROR_CMD_NO_DEFINE,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

