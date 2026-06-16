# Vol.05 — 기타 Enum (2)

> 생성일: 2026-06-16 | MX SRM App Ver 4.4 | 소스 미수정

기타 enumeration.

---

### DEBUG_STR_49

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:1977: Set_TestStatus(DEBUG_STR_49, nID);`
  - `Core/Src/dev_SRM.c:730: Set_TestStatus(DEBUG_STR_49, acc);`
  - `Core/Src/dev_SRM.c:12700: Set_TestStatus(DEBUG_STR_49, m_St.Inv_St[INV_FORK_1].Status1.ForkOut_Left_OK);`
  - `Core/Src/dev_SRM.c:13688: Set_TestStatus(DEBUG_STR_49, m_St.Inv_St[INV_FORK_1].Status1.ForkOut_Left_OK);`
  - `Core/Src/dev_SRM.c:14674: Set_TestStatus(DEBUG_STR_49, m_St.Inv_St[INV_FORK_1].Status1.ForkOut_Left_OK);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_50

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:1978: Set_TestStatus(DEBUG_STR_50, nControl);`
  - `Core/Src/dev_SRM.c:731: Set_TestStatus(DEBUG_STR_50, dec);`
  - `Core/Src/dev_SRM.c:6668: Set_TestStatus(DEBUG_STR_50, s_RecvCnt[2]);`
  - `Core/Src/dev_SRM.c:12701: Set_TestStatus(DEBUG_STR_50, s_Result_Code_Left);`
  - `Core/Src/dev_SRM.c:13689: Set_TestStatus(DEBUG_STR_50, s_Result_Code_Left);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_51

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:732: Set_TestStatus(DEBUG_STR_51, JerkTime);`
  - `Core/Src/dev_SRM.c:6669: Set_TestStatus(DEBUG_STR_51, s_RecvCnt[3]);`
  - `Core/Src/dev_SRM.c:7154: Set_TestStatus(DEBUG_STR_51, 1);`
  - `Core/Src/dev_SRM.c:7160: Set_TestStatus(DEBUG_STR_51, 2);`
  - `Core/Src/dev_SRM.c:7174: Set_TestStatus(DEBUG_STR_51, 3);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_52

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:1209: Set_TestStatus(DEBUG_STR_52, pCtrl->Value);`
  - `Core/Src/dev_SRM.c:7186: Set_TestStatus(DEBUG_STR_52, nByteIndex);`
  - `Core/Src/dev_SRM.c:12703: Set_TestStatus(DEBUG_STR_52, m_St.Inv_St[INV_FORK_1].Status1.ForkOut_Right_OK);`
  - `Core/Src/dev_SRM.c:13691: Set_TestStatus(DEBUG_STR_52, m_St.Inv_St[INV_FORK_1].Status1.ForkOut_Right_OK);`
  - `Core/Src/dev_SRM.c:14677: Set_TestStatus(DEBUG_STR_52, m_St.Inv_St[INV_FORK_1].Status1.ForkOut_Right_OK);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_53

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:1210: Set_TestStatus(DEBUG_STR_53, s_TestVal);`
  - `Core/Src/dev_SRM.c:7187: Set_TestStatus(DEBUG_STR_53, nBitIndex);`
  - `Core/Src/dev_SRM.c:12704: Set_TestStatus(DEBUG_STR_53, s_Result_Code_Right);`
  - `Core/Src/dev_SRM.c:13692: Set_TestStatus(DEBUG_STR_53, s_Result_Code_Right);`
  - `Core/Src/dev_SRM.c:14678: Set_TestStatus(DEBUG_STR_53, s_Result_Code_Right);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_54

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:7267: Set_TestStatus(DEBUG_STR_54, nPort_Index);`
  - `Core/Src/dev_SRM.c:12705: Set_TestStatus(DEBUG_STR_54, s_Impossible_Code_Right);`
  - `Core/Src/dev_SRM.c:13693: Set_TestStatus(DEBUG_STR_54, s_Impossible_Code_Right);`
  - `Core/Src/dev_SRM.c:14679: Set_TestStatus(DEBUG_STR_54, s_Impossible_Code_Right);`
  - `Core/Src/dev_SRM.c:15148: Set_TestStatus(DEBUG_STR_54, nReadOffset.Lift_Left);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_55

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:7268: Set_TestStatus(DEBUG_STR_55, nWriteFlag);`
  - `Core/Src/dev_SRM.c:15149: Set_TestStatus(DEBUG_STR_55, nReadOffset.Lift_Right);`
  - `Core/Src/dev_SRM.c:25291: Set_TestStatus(DEBUG_STR_55, flag);`
  - `Core/Src/dev_SRM.c:25916: Set_TestStatus(DEBUG_STR_55, nSt_Lift_Target_Pos);`
  - `Core/Src/dev_SRM.c:26690: Set_TestStatus(DEBUG_STR_55, flag);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_56

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:7269: Set_TestStatus(DEBUG_STR_56, nByteIndex);`
  - `Core/Src/dev_SRM.c:15161: Set_TestStatus(DEBUG_STR_56, 20);`
  - `Core/Src/dev_SRM.c:15168: Set_TestStatus(DEBUG_STR_56, 10);`
  - `Core/Src/dev_SRM.c:25917: Set_TestStatus(DEBUG_STR_56, nPosition);`
  - `Core/Src/dev_SRM.c:26691: Set_TestStatus(DEBUG_STR_56, nDisable_Chk_Rack_Move);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_57

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:7270: Set_TestStatus(DEBUG_STR_57, nBitIndex);`
  - `Core/Src/dev_SRM.c:15203: Set_TestStatus(DEBUG_STR_57, nTrav_Com);`
  - `Core/Src/dev_SRM.c:25293: Set_TestStatus(DEBUG_STR_57, nTarget_Station);`
  - `Core/Src/dev_SRM.c:25918: Set_TestStatus(DEBUG_STR_57, flag);`
  - `Core/Src/dev_SRM.c:26692: Set_TestStatus(DEBUG_STR_57, nTarget_Station);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_58

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2690: Set_TestStatus(DEBUG_STR_58, accept[0]);`
  - `Core/Src/com_tml.c:2872: Set_TestStatus(DEBUG_STR_58, s_StartOn);`
  - `Core/Src/dev_SRM.c:7281: Set_TestStatus(DEBUG_STR_58, nByteIndex);`
  - `Core/Src/dev_SRM.c:15204: Set_TestStatus(DEBUG_STR_58, nPosition_upper);`
  - `Core/Src/dev_SRM.c:25919: Set_TestStatus(DEBUG_STR_58, nDisable_Chk_Rack_Move);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_59

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2691: Set_TestStatus(DEBUG_STR_59, ret_value[0]);`
  - `Core/Src/com_tml.c:2873: Set_TestStatus(DEBUG_STR_59, pCom->Data[0]);`
  - `Core/Src/dev_SRM.c:7282: Set_TestStatus(DEBUG_STR_59, nBitIndex);`
  - `Core/Src/dev_SRM.c:15205: Set_TestStatus(DEBUG_STR_59, nPosition_lower);`
  - `Core/Src/dev_SRM.c:25920: Set_TestStatus(DEBUG_STR_59, nTarget_Station);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_60

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2874: Set_TestStatus(DEBUG_STR_60, result);`
  - `Core/Src/dev_SRM.c:15221: Set_TestStatus(DEBUG_STR_60, nTrav_Com);`
  - `Core/Src/dev_SRM.c:27723: Set_TestStatus(DEBUG_STR_60, nTo_Level);`
  - `Core/Src/dev_SRM.c:37169: Set_TestStatus(DEBUG_STR_60, m_Manual_Run_Mode[nInvertor]);`
  - `Core/Src/dev_SRM.c:41995: Set_TestStatus(DEBUG_STR_60, s_Decel_Depth);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_61

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:15222: Set_TestStatus(DEBUG_STR_61, nPosition_upper);`
  - `Core/Src/dev_SRM.c:27653: Set_TestStatus(DEBUG_STR_61, nPosition);`
  - `Core/Src/dev_SRM.c:37170: Set_TestStatus(DEBUG_STR_61, s_StopReason);`
  - `Core/Src/dev_SRM.c:41996: Set_TestStatus(DEBUG_STR_61, s_AutoDec_Velocity);`
  - `Core/Src/dev_SRM.c:48277: Set_TestStatus(DEBUG_STR_61, Target_Pos + nOffset); // íì© ìí`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_62

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:5981: Set_TestStatus(DEBUG_STR_62, ++s_Test_Cnt);`
  - `Core/Src/dev_SRM.c:9111: Set_TestStatus(DEBUG_STR_62, m_St.Inv_St[INV_FORK_1].Current_Pos);`
  - `Core/Src/dev_SRM.c:15223: Set_TestStatus(DEBUG_STR_62, nPosition_lower);`
  - `Core/Src/dev_SRM.c:27654: Set_TestStatus(DEBUG_STR_62, nOffset);`
  - `Core/Src/dev_SRM.c:41997: Set_TestStatus(DEBUG_STR_62, nNow_Velocity);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_63

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:5982: Set_TestStatus(DEBUG_STR_63, nWordCnt);`
  - `Core/Src/dev_SRM.c:41998: Set_TestStatus(DEBUG_STR_63, s_Fork_Decel_Mode);`
  - `Core/Src/dev_SRM.c:48279: Set_TestStatus(DEBUG_STR_63, Get_Inverter_Motor_Turning(inverter)); // ëª¨í° íì ì¬ë¶`
  - `Core/Src/dev_SRM.c:48333: Set_TestStatus(DEBUG_STR_63, Get_Inverter_Motor_Turning(inverter));`
  - `Core/Src/dev_SRM.c:50921: Set_TestStatus(DEBUG_STR_63, ptrCell->Level_ID);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_STR_64

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/alarm.c:25: else if ((nIndex >= DEBUG_STR_33) && (nIndex <= DEBUG_STR_64))`
  - `Core/Src/alarm.c:37: else if ((nIndex >= DEBUG_STR_33) && (nIndex <= DEBUG_STR_64))`
  - `Core/Src/dev_SRM.c:50922: Set_TestStatus(DEBUG_STR_64, ptrCell->Row_ID);`
  - `Core/Src/dev_SRM.c:50941: Set_TestStatus(DEBUG_STR_64, ptrCell->Row_ID);`
  - `Core/Src/dev_SRM.c:50962: Set_TestStatus(DEBUG_STR_64, ptrCell->Row_ID);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MAX_DEBUG_STR

- **종류**: enum `enumDEBUG_STR` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:299: MAX_DEBUG_STR,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_CTR_1

- **종류**: enum `enumDEBUG_BUF` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Test 1
- **용도(읽는 법)**: 헤더 주석: Test 1
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:97: m_McuTestCtr.RS232_Test		= (INT08U)m_TestStatus.Ctrl[DEBUG_CTR_1];`
  - `Core/Src/alarm.c:51: if ((nIndex >= DEBUG_CTR_1) && (nIndex <= DEBUG_CTR_16))`
  - `Core/Src/alarm.c:59: if ((nIndex >= DEBUG_CTR_1) && (nIndex <= DEBUG_CTR_16))`
  - `Core/Src/alarm.c:1450: m_TestStatus.Ctrl[DEBUG_CTR_1] = Get_DI_State(IN_AUTO);`
  - `Core/Src/dev_SRM.c:2239: m_TestStatus.Ctrl[DEBUG_CTR_1] = nVelocity.Spd;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_CTR_2

- **종류**: enum `enumDEBUG_BUF` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Test 2
- **용도(읽는 법)**: 헤더 주석: Test 2
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:98: m_McuTestCtr.RS485_Test1	= (INT08U)m_TestStatus.Ctrl[DEBUG_CTR_2];`
  - `Core/Src/alarm.c:1451: m_TestStatus.Ctrl[DEBUG_CTR_2] = Get_DI_State(IN_INSP);`
  - `Core/Src/dev_SRM.c:2240: m_TestStatus.Ctrl[DEBUG_CTR_2] = nVelocity.Acc;`
  - `Core/Src/dev_SRM.c:16452: m_TestStatus.Ctrl[DEBUG_CTR_2] = m_pgmEnv.PosSeqCnt_Y_Left;`
  - `Core/Src/dev_SRM.c:17079: m_TestStatus.Ctrl[DEBUG_CTR_2] = m_pgmEnv.PosSeqCnt_Y_Left;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_CTR_3

- **종류**: enum `enumDEBUG_BUF` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Test 3
- **용도(읽는 법)**: 헤더 주석: Test 3
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:99: m_McuTestCtr.RS485_Test2	= (INT08U)m_TestStatus.Ctrl[DEBUG_CTR_3];`
  - `Core/Src/alarm.c:1452: m_TestStatus.Ctrl[DEBUG_CTR_3] = m_St.SRM_Status2.Bit.ModeSW;`
  - `Core/Src/com_tml.c:1792: m_TestStatus.Ctrl[DEBUG_CTR_3] = nInx;`
  - `Core/Src/dev_SRM.c:2241: m_TestStatus.Ctrl[DEBUG_CTR_3] = nVelocity.Dec;`
  - `Core/Src/dev_SRM.c:16453: m_TestStatus.Ctrl[DEBUG_CTR_3] = m_pgmEnv.Pos_X_Left;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_CTR_4

- **종류**: enum `enumDEBUG_BUF` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Test 4,
- **용도(읽는 법)**: 헤더 주석: Test 4,
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:100: m_McuTestCtr.RS422_Test1	= (INT08U)m_TestStatus.Ctrl[DEBUG_CTR_4];`
  - `Core/Src/com_tml.c:1793: m_TestStatus.Ctrl[DEBUG_CTR_4] = nGraph_Index;`
  - `Core/Src/dev_SRM.c:2242: m_TestStatus.Ctrl[DEBUG_CTR_4] = nVelocity.Jerk;`
  - `Core/Src/dev_SRM.c:16454: m_TestStatus.Ctrl[DEBUG_CTR_4] = m_pgmEnv.Pos_Y_Left;`
  - `Core/Src/dev_SRM.c:17081: m_TestStatus.Ctrl[DEBUG_CTR_4] = m_pgmEnv.Pos_Y_Left;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_CTR_5

- **종류**: enum `enumDEBUG_BUF` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Test 5,
- **용도(읽는 법)**: 헤더 주석: Test 5,
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:101: m_McuTestCtr.RS422_Test2	= (INT08U)m_TestStatus.Ctrl[DEBUG_CTR_5];`
  - `Core/Src/com_tml.c:1794: m_TestStatus.Ctrl[DEBUG_CTR_5] = nGraph_Index1;`
  - `Core/Src/dev_SRM.c:11619: m_TestStatus.Ctrl[DEBUG_CTR_5] = 10;`
  - `Core/Src/dev_SRM.c:11653: m_TestStatus.Ctrl[DEBUG_CTR_5] = 20;`
  - `Core/Src/dev_SRM.c:16455: m_TestStatus.Ctrl[DEBUG_CTR_5] = nCurrent_Bay[RACK_LEFT];`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_CTR_6

- **종류**: enum `enumDEBUG_BUF` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Test 6,
- **용도(읽는 법)**: 헤더 주석: Test 6,
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:102: m_McuTestCtr.CAN_Test1		= (INT08U)m_TestStatus.Ctrl[DEBUG_CTR_6];`
  - `Core/Src/dev_SRM.c:11620: m_TestStatus.Ctrl[DEBUG_CTR_6] = nLiftPostion;`
  - `Core/Src/dev_SRM.c:11654: m_TestStatus.Ctrl[DEBUG_CTR_6] = nLiftPostion;`
  - `Core/Src/dev_SRM.c:16456: m_TestStatus.Ctrl[DEBUG_CTR_6] = nCurrent_Level[RACK_LEFT];`
  - `Core/Src/dev_SRM.c:17083: m_TestStatus.Ctrl[DEBUG_CTR_6] = nCurrent_Level[RACK_LEFT];`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_CTR_7

- **종류**: enum `enumDEBUG_BUF` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Test 7,
- **용도(읽는 법)**: 헤더 주석: Test 7,
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:103: m_McuTestCtr.CAN_Test2		= (INT08U)m_TestStatus.Ctrl[DEBUG_CTR_7];`
  - `Core/Src/dev_SRM.c:11621: m_TestStatus.Ctrl[DEBUG_CTR_7] = nPoint_Diff_1;`
  - `Core/Src/dev_SRM.c:11655: m_TestStatus.Ctrl[DEBUG_CTR_7] = nPoint_Diff_1;`
  - `Core/Src/dev_SRM.c:16458: m_TestStatus.Ctrl[DEBUG_CTR_7] = m_pgmEnv.PosSeqCnt_X_Right;`
  - `Core/Src/dev_SRM.c:17085: m_TestStatus.Ctrl[DEBUG_CTR_7] = m_pgmEnv.PosSeqCnt_X_Right;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_CTR_8

- **종류**: enum `enumDEBUG_BUF` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Test 8,
- **용도(읽는 법)**: 헤더 주석: Test 8,
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:104: m_McuTestCtr.EtherNet_Test1 = (INT08U)m_TestStatus.Ctrl[DEBUG_CTR_8];`
  - `Core/Src/dev_SRM.c:11622: m_TestStatus.Ctrl[DEBUG_CTR_8] = nPoint_upper;`
  - `Core/Src/dev_SRM.c:11656: m_TestStatus.Ctrl[DEBUG_CTR_8] = nPoint_upper;`
  - `Core/Src/dev_SRM.c:16459: m_TestStatus.Ctrl[DEBUG_CTR_8] = m_pgmEnv.PosSeqCnt_Y_Right;`
  - `Core/Src/dev_SRM.c:17086: m_TestStatus.Ctrl[DEBUG_CTR_8] = m_pgmEnv.PosSeqCnt_Y_Right;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_CTR_9

- **종류**: enum `enumDEBUG_BUF` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Test 9,
- **용도(읽는 법)**: 헤더 주석: Test 9,
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:105: m_McuTestCtr.EtherNet_Test2 = (INT08U)m_TestStatus.Ctrl[DEBUG_CTR_9];`
  - `Core/Src/dev_SRM.c:11623: m_TestStatus.Ctrl[DEBUG_CTR_9] = nPoint_lower;`
  - `Core/Src/dev_SRM.c:11657: m_TestStatus.Ctrl[DEBUG_CTR_9] = nPoint_lower;`
  - `Core/Src/dev_SRM.c:16460: m_TestStatus.Ctrl[DEBUG_CTR_9] = m_pgmEnv.Pos_X_Right;`
  - `Core/Src/dev_SRM.c:17087: m_TestStatus.Ctrl[DEBUG_CTR_9] = m_pgmEnv.Pos_X_Right;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_CTR_10

- **종류**: enum `enumDEBUG_BUF` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Test 10,
- **용도(읽는 법)**: 헤더 주석: Test 10,
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:106: m_McuTestCtr.EtherCAT_Test  = (INT08U)m_TestStatus.Ctrl[DEBUG_CTR_10];`
  - `Core/Src/dev_SRM.c:16461: m_TestStatus.Ctrl[DEBUG_CTR_10] = m_pgmEnv.Pos_Y_Right;`
  - `Core/Src/dev_SRM.c:17088: m_TestStatus.Ctrl[DEBUG_CTR_10] = m_pgmEnv.Pos_Y_Right;`
  - `Core/Src/dev_SRM.c:17670: m_TestStatus.Ctrl[DEBUG_CTR_10] = m_pgmEnv.Pos_Y_Right;`
  - `Core/Src/dev_SRM.c:18310: m_TestStatus.Ctrl[DEBUG_CTR_10] = m_pgmEnv.Pos_Y_Right;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_CTR_11

- **종류**: enum `enumDEBUG_BUF` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Test 11,
- **용도(읽는 법)**: 헤더 주석: Test 11,
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:107: m_McuTestCtr.SSI_Test		= (INT08U)m_TestStatus.Ctrl[DEBUG_CTR_11];`
  - `Core/Src/dev_SRM.c:16462: m_TestStatus.Ctrl[DEBUG_CTR_11] = nCurrent_Bay[RACK_RIGHT];`
  - `Core/Src/dev_SRM.c:17089: m_TestStatus.Ctrl[DEBUG_CTR_11] = nCurrent_Bay[RACK_RIGHT];`
  - `Core/Src/dev_SRM.c:17671: m_TestStatus.Ctrl[DEBUG_CTR_11] = nCurrent_Bay[RACK_RIGHT];`
  - `Core/Src/dev_SRM.c:18311: m_TestStatus.Ctrl[DEBUG_CTR_11] = nCurrent_Bay[RACK_RIGHT];`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_CTR_12

- **종류**: enum `enumDEBUG_BUF` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Test 12,
- **용도(읽는 법)**: 헤더 주석: Test 12,
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:108: m_McuTestCtr.Encoder_Test	= (INT08U)m_TestStatus.Ctrl[DEBUG_CTR_12];`
  - `Core/Src/dev_SRM.c:16463: m_TestStatus.Ctrl[DEBUG_CTR_12] = nCurrent_Level[RACK_RIGHT];`
  - `Core/Src/dev_SRM.c:17090: m_TestStatus.Ctrl[DEBUG_CTR_12] = nCurrent_Level[RACK_RIGHT];`
  - `Core/Src/dev_SRM.c:17672: m_TestStatus.Ctrl[DEBUG_CTR_12] = nCurrent_Level[RACK_RIGHT];`
  - `Core/Src/dev_SRM.c:18312: m_TestStatus.Ctrl[DEBUG_CTR_12] = nCurrent_Level[RACK_RIGHT];`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_CTR_13

- **종류**: enum `enumDEBUG_BUF` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Test 13,
- **용도(읽는 법)**: 헤더 주석: Test 13,
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:109: m_McuTestCtr.PTO_Output		= (INT32U)m_TestStatus.Ctrl[DEBUG_CTR_13];`
  - `Core/Src/dev_SRM.c:16465: m_TestStatus.Ctrl[DEBUG_CTR_13] = nCurrent_Station_No;`
  - `Core/Src/dev_SRM.c:17092: m_TestStatus.Ctrl[DEBUG_CTR_13] = nCurrent_Station_No;`
  - `Core/Src/dev_SRM.c:17674: m_TestStatus.Ctrl[DEBUG_CTR_13] = nCurrent_Station_No;`
  - `Core/Src/dev_SRM.c:18314: m_TestStatus.Ctrl[DEBUG_CTR_13] = nCurrent_Station_No;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_CTR_14

- **종류**: enum `enumDEBUG_BUF` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Test 14,
- **용도(읽는 법)**: 헤더 주석: Test 14,
- **코드 참조 예**:
  - `Core/Src/Mcu_Test.c:110: m_McuTestCtr.DIO_Test		= (INT08U)m_TestStatus.Ctrl[DEBUG_CTR_14];`
  - `Core/Src/dev_SRM.c:16467: m_TestStatus.Ctrl[DEBUG_CTR_14] = m_pgmEnv.Move_PosFlag;`
  - `Core/Src/dev_SRM.c:17093: m_TestStatus.Ctrl[DEBUG_CTR_14] = m_pgmEnv.Move_PosFlag;`
  - `Core/Src/dev_SRM.c:17676: m_TestStatus.Ctrl[DEBUG_CTR_14] = m_pgmEnv.Move_PosFlag;`
  - `Core/Src/dev_SRM.c:18316: m_TestStatus.Ctrl[DEBUG_CTR_14] = m_pgmEnv.Move_PosFlag;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_CTR_15

- **종류**: enum `enumDEBUG_BUF` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Test 15,
- **용도(읽는 법)**: 헤더 주석: Test 15,
- **코드 참조 예**:
  - `Core/Src/com_tml.c:5430: m_TestStatus.Ctrl[DEBUG_CTR_15] = getCalcTimer1ms(s_RecvInternal);`
  - `Core/Src/dev_SRM.c:15703: m_TestStatus.Ctrl[DEBUG_CTR_15] = m_pgmEnv.Project_Site_No;`
  - `Core/Src/dev_SRM.c:16607: m_TestStatus.Ctrl[DEBUG_CTR_15] = m_pgmEnv.Project_Site_No;`
  - `Core/Src/dev_SRM.c:17158: m_TestStatus.Ctrl[DEBUG_CTR_15] = m_pgmEnv.Project_Site_No;`
  - `Core/Src/dev_SRM.c:17747: m_TestStatus.Ctrl[DEBUG_CTR_15] = m_pgmEnv.Project_Site_No;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DEBUG_CTR_16

- **종류**: enum `enumDEBUG_BUF` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Test 16,
- **용도(읽는 법)**: 헤더 주석: Test 16,
- **코드 참조 예**:
  - `Core/Src/alarm.c:51: if ((nIndex >= DEBUG_CTR_1) && (nIndex <= DEBUG_CTR_16))`
  - `Core/Src/alarm.c:59: if ((nIndex >= DEBUG_CTR_1) && (nIndex <= DEBUG_CTR_16))`
  - `Core/Src/com_tml.c:5434: m_TestStatus.Ctrl[DEBUG_CTR_16] = s_Max_RecvInternal;`
  - `Core/Src/dev_SRM.c:15704: m_TestStatus.Ctrl[DEBUG_CTR_16] = nSRM_No;`
  - `Core/Src/dev_SRM.c:16608: m_TestStatus.Ctrl[DEBUG_CTR_16] = nSRM_No;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### GRAPH_1

- **종류**: enum `enumGRAPH_INDEX` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Top View
- **용도(읽는 법)**: 헤더 주석: Top View
- **코드 참조 예**:
  - `Core/Src/alarm.c:258: m_GraphLog.GraphData[GRAPH_1][m_GraphLog.Index] = m_pgmEnv.GraphData[GRAPH_1];`
  - `Core/Src/dev_SRM.c:5481: m_pgmEnv.GraphData[GRAPH_1] = m_St.Inv_St[INV_TRAVEL].Current_Pos;`
  - `Core/Src/dev_SRM.c:5645: m_pgmEnv.GraphData[GRAPH_1] = m_St.Inv_St[INV_TRAVEL].Current_Pos;`
  - `Core/Src/dev_SRM.c:5819: m_pgmEnv.GraphData[GRAPH_1] = m_St.Inv_St[INV_TRAVEL].Current_Pos;`
  - `Core/Src/dev_SRM.c:40188: m_pgmEnv.GraphData[GRAPH_1] = m_St.Inv_St[nInv].Current_Vel;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### GRAPH_2

- **종류**: enum `enumGRAPH_INDEX` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Top View
- **용도(읽는 법)**: 헤더 주석: Top View
- **코드 참조 예**:
  - `Core/Src/alarm.c:259: m_GraphLog.GraphData[GRAPH_2][m_GraphLog.Index] = m_pgmEnv.GraphData[GRAPH_2];`
  - `Core/Src/dev_SRM.c:5482: m_pgmEnv.GraphData[GRAPH_2] = m_SRM_TxPDO[INV_FORK_1].CurPosition;`
  - `Core/Src/dev_SRM.c:5646: m_pgmEnv.GraphData[GRAPH_2] = m_SRM_TxPDO[INV_FORK_1].CurPosition;`
  - `Core/Src/dev_SRM.c:5820: m_pgmEnv.GraphData[GRAPH_2] = m_SRM_TxPDO[INV_FORK_1].CurPosition;`
  - `Core/Src/dev_SRM.c:40120: m_pgmEnv.GraphData[GRAPH_2] = pProfile->command_postion;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### GRAPH_3

- **종류**: enum `enumGRAPH_INDEX` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/alarm.c:260: m_GraphLog.GraphData[GRAPH_3][m_GraphLog.Index] = m_pgmEnv.GraphData[GRAPH_3];`
  - `Core/Src/dev_SRM.c:5484: m_pgmEnv.GraphData[GRAPH_3] = m_SRM_TxPDO[INV_TRAVEL].ActualSpeed;`
  - `Core/Src/dev_SRM.c:5648: m_pgmEnv.GraphData[GRAPH_3] = m_SRM_TxPDO[INV_TRAVEL].ActualSpeed;`
  - `Core/Src/dev_SRM.c:5822: m_pgmEnv.GraphData[GRAPH_3] = m_SRM_TxPDO[INV_TRAVEL].ActualSpeed;`
  - `Core/Src/dev_SRM.c:40121: m_pgmEnv.GraphData[GRAPH_3] = (INT32S)((velocity / 1000) * 60) * 100;	// mm/s -> m/min`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### GRAPH_4

- **종류**: enum `enumGRAPH_INDEX` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/alarm.c:261: m_GraphLog.GraphData[GRAPH_4][m_GraphLog.Index] = m_pgmEnv.GraphData[GRAPH_4];`
  - `Core/Src/dev_SRM.c:5276: m_pgmEnv.GraphData[GRAPH_4] = 100;`
  - `Core/Src/dev_SRM.c:5280: m_pgmEnv.GraphData[GRAPH_4] = 0;`
  - `Core/Src/dev_SRM.c:5485: m_pgmEnv.GraphData[GRAPH_4] = m_SRM_TxPDO[INV_TRAVEL].StatusWord.B.ReleaseBrake * 100;`
  - `Core/Src/dev_SRM.c:5649: m_pgmEnv.GraphData[GRAPH_4] = m_SRM_TxPDO[INV_TRAVEL].StatusWord.B.ReleaseBrake * 100;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### GRAPH_5

- **종류**: enum `enumGRAPH_INDEX` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/alarm.c:262: m_GraphLog.GraphData[GRAPH_5][m_GraphLog.Index] = m_pgmEnv.GraphData[GRAPH_5];`
  - `Core/Src/dev_SRM.c:5285: m_pgmEnv.GraphData[GRAPH_5] = 200;`
  - `Core/Src/dev_SRM.c:5289: m_pgmEnv.GraphData[GRAPH_5] = 0;`
  - `Core/Src/dev_SRM.c:5486: m_pgmEnv.GraphData[GRAPH_5] = m_SRM_TxPDO[INV_TRAVEL].StatusWord.B.TargetReached * 200;`
  - `Core/Src/dev_SRM.c:5650: m_pgmEnv.GraphData[GRAPH_5] = m_SRM_TxPDO[INV_TRAVEL].StatusWord.B.TargetReached * 200;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### GRAPH_6

- **종류**: enum `enumGRAPH_INDEX` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/alarm.c:263: m_GraphLog.GraphData[GRAPH_6][m_GraphLog.Index] = m_pgmEnv.GraphData[GRAPH_6];`
  - `Core/Src/dev_SRM.c:5294: m_pgmEnv.GraphData[GRAPH_6] = 300;`
  - `Core/Src/dev_SRM.c:5298: m_pgmEnv.GraphData[GRAPH_6] = 0;`
  - `Core/Src/dev_SRM.c:31652: m_pgmEnv.GraphData[GRAPH_6] = Get_Inverter_Motor_Turning(nInvertor);`
  - `Core/Src/dev_SRM.c:32690: m_pgmEnv.GraphData[GRAPH_6] = Get_Inverter_Motor_Turning(nInvertor);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### GRAPH_7

- **종류**: enum `enumGRAPH_INDEX` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/alarm.c:264: m_GraphLog.GraphData[GRAPH_7][m_GraphLog.Index] = m_pgmEnv.GraphData[GRAPH_7];`
  - `Core/Src/dev_SRM.c:5301: m_pgmEnv.GraphData[GRAPH_7] = m_St.Inv_St[INV_HOIST].Current_Vel;`
  - `Core/Src/dev_SRM.c:5489: m_pgmEnv.GraphData[GRAPH_7] = m_SRM_TxPDO[INV_FORK_1].ActualSpeed;`
  - `Core/Src/dev_SRM.c:5653: m_pgmEnv.GraphData[GRAPH_7] = m_SRM_TxPDO[INV_FORK_1].ActualSpeed;`
  - `Core/Src/dev_SRM.c:5827: m_pgmEnv.GraphData[GRAPH_7] = m_SRM_TxPDO[INV_FORK_1].ActualSpeed;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### GRAPH_8

- **종류**: enum `enumGRAPH_INDEX` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/alarm.c:265: m_GraphLog.GraphData[GRAPH_8][m_GraphLog.Index] = m_pgmEnv.GraphData[GRAPH_8];`
  - `Core/Src/dev_SRM.c:5305: m_pgmEnv.GraphData[GRAPH_8] = 100;`
  - `Core/Src/dev_SRM.c:5309: m_pgmEnv.GraphData[GRAPH_8] = 0;`
  - `Core/Src/dev_SRM.c:5490: m_pgmEnv.GraphData[GRAPH_8] = Get_Motor_Brake_Release(nInvertor) * 100;`
  - `Core/Src/dev_SRM.c:5654: m_pgmEnv.GraphData[GRAPH_8] = Get_Motor_Brake_Release(nInvertor) * 100;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### GRAPH_9

- **종류**: enum `enumGRAPH_INDEX` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/alarm.c:266: m_GraphLog.GraphData[GRAPH_9][m_GraphLog.Index] = m_pgmEnv.GraphData[GRAPH_9];`
  - `Core/Src/dev_SRM.c:5314: m_pgmEnv.GraphData[GRAPH_9] = 200;`
  - `Core/Src/dev_SRM.c:5318: m_pgmEnv.GraphData[GRAPH_9] = 0;`
  - `Core/Src/dev_SRM.c:5491: m_pgmEnv.GraphData[GRAPH_9] = m_SRM_TxPDO[INV_FORK_1].StatusWord.B.TargetReached * 200;`
  - `Core/Src/dev_SRM.c:5655: m_pgmEnv.GraphData[GRAPH_9] = m_SRM_TxPDO[INV_FORK_1].StatusWord.B.TargetReached * 200;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### GRAPH_10

- **종류**: enum `enumGRAPH_INDEX` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/alarm.c:267: m_GraphLog.GraphData[GRAPH_10][m_GraphLog.Index] = m_pgmEnv.GraphData[GRAPH_10];`
  - `Core/Src/dev_SRM.c:5323: m_pgmEnv.GraphData[GRAPH_10] = 300;`
  - `Core/Src/dev_SRM.c:5327: m_pgmEnv.GraphData[GRAPH_10] = 0;`
  - `Core/Src/dev_SRM.c:40127: m_pgmEnv.GraphData[GRAPH_10] = pProfile->command_postion;`
  - `Core/Src/dev_SRM.c:68230: m_pgmEnv.GraphData[GRAPH_10] = Get_Inverter_Actual_Touqe(INV_HOIST);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### GRAPH_11

- **종류**: enum `enumGRAPH_INDEX` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Top View
- **용도(읽는 법)**: 헤더 주석: Top View
- **코드 참조 예**:
  - `Core/Src/alarm.c:268: m_GraphLog.GraphData[GRAPH_11][m_GraphLog.Index] = m_pgmEnv.GraphData[GRAPH_11];`
  - `Core/Src/dev_SRM.c:40128: m_pgmEnv.GraphData[GRAPH_11] = (INT32S)((velocity / 1000) * 60) * 100;	// mm/s -> m/min`
  - `Core/Inc/User_Define.h:332: GRAPH_11,			// Top View`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### GRAPH_12

- **종류**: enum `enumGRAPH_INDEX` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Top View
- **용도(읽는 법)**: 헤더 주석: Top View
- **코드 참조 예**:
  - `Core/Src/alarm.c:269: m_GraphLog.GraphData[GRAPH_12][m_GraphLog.Index] = m_pgmEnv.GraphData[GRAPH_12];`
  - `Core/Src/dev_SRM.c:40130: m_pgmEnv.GraphData[GRAPH_12] = (m_St.Invertor_St[INV_LIFT].Current_Pos - pProfile->command_postion) `
  - `Core/Inc/User_Define.h:333: GRAPH_12,			// Top View`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MAX_GRAPH_COUNT

- **종류**: enum `enumGRAPH_INDEX` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:1796: if (nGraph_Index < MAX_GRAPH_COUNT)`
  - `Core/Inc/User_Define.h:334: MAX_GRAPH_COUNT`
  - `Core/Inc/User_Define.h:3615: INT32S GraphData[MAX_GRAPH_COUNT][MAX_GRAPH_DATA_COUNT];`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CP_MODE_MANUAL

- **종류**: enum `enumCP_MODE` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/main.c:600: m_St.CP_Mode = CP_MODE_MANUAL;`
  - `Core/Inc/User_Define.h:848: CP_MODE_MANUAL = 0,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CP_MODE_SEMI_AUTO

- **종류**: enum `enumCP_MODE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:849: CP_MODE_SEMI_AUTO,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CP_MODE_AUTO

- **종류**: enum `enumCP_MODE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:850: CP_MODE_AUTO,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_MOVE_STEP_NONE

- **종류**: enum `enumCMD_MOVE_STEP_PROCESS` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:46686: Store_Fork_WorkStatus(0, 0, ORDER_CODE_NONE, WORK_STATUS_NONE, CMD_MOVE_STEP_NONE);`
  - `Core/Inc/User_Define.h:1112: CMD_MOVE_STEP_NONE = 0,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_MOVE_STEP_RX

- **종류**: enum `enumCMD_MOVE_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:45561: , CMD_MOVE_STEP_RX, 0, 0, 0, 0);`
  - `Core/Src/dev_SRM.c:45611: , CMD_MOVE_STEP_RX, 0, 0, 0, 0);`
  - `Core/Src/dev_SRM.c:45663: , CMD_MOVE_STEP_RX, 0, 0, 0, 0);`
  - `Core/Src/dev_SRM.c:45750: tp.Bay_ID, tp.Level_ID, CMD_MOVE_STEP_RX, 0, 0, 0);// ë°ì´í°ë¥¼ ë²í¼ìì«ì`
  - `Core/Src/dev_SRM.c:46632: , CMD_MOVE_STEP_RX, 0, 0, pCmd->Fork[POS_FORK_1].Good_Type, pCmd->OperationFlag);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_MOVE_STEP_2

- **종류**: enum `enumCMD_MOVE_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:1114: CMD_MOVE_STEP_2,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_MOVE_STEP_3

- **종류**: enum `enumCMD_MOVE_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:1115: CMD_MOVE_STEP_3,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_MOVE_STEP_4

- **종류**: enum `enumCMD_MOVE_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:1116: CMD_MOVE_STEP_4,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_MOVE_STEP_5

- **종류**: enum `enumCMD_MOVE_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:1117: CMD_MOVE_STEP_5,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_MOVE_STEP_6

- **종류**: enum `enumCMD_MOVE_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:1118: CMD_MOVE_STEP_6,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_MOVE_STEP_MOVING

- **종류**: enum `enumCMD_MOVE_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:45912: & nTargetPos, CMD_MOVE_STEP_MOVING, 0, 0, pCmd->LoadFactor);`
  - `Core/Src/dev_SRM.c:58872: Save_ForkMove_OrderProcess(0, CMD_MOVE_STEP_MOVING);//mcu, ram, ì§ìë°ì ëª¨ë íì¬ì ìí`
  - `Core/Src/dev_SRM.c:63161: Save_ForkMove_OrderProcess(0, CMD_MOVE_STEP_MOVING);`
  - `Core/Inc/User_Define.h:1119: CMD_MOVE_STEP_MOVING,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_MOVE_STEP_COMPELTE

- **종류**: enum `enumCMD_MOVE_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:59522: Save_ForkMove_OrderProcess(0, CMD_MOVE_STEP_COMPELTE);`
  - `Core/Src/dev_SRM.c:59530: Save_ForkMove_OrderProcess(0, CMD_MOVE_STEP_COMPELTE);`
  - `Core/Src/dev_SRM.c:59586: Save_ForkMove_OrderProcess(0, CMD_MOVE_STEP_COMPELTE);`
  - `Core/Src/dev_SRM.c:63214: Save_ForkMove_OrderProcess(0, CMD_MOVE_STEP_COMPELTE);`
  - `Core/Inc/User_Define.h:1120: CMD_MOVE_STEP_COMPELTE,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_FORK_STEP_NONE

- **종류**: enum `enumCMD_FORK_STEP_PROCESS` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: 포크 서브스텝: GET/PUT 내부 단계.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:46700: Store_Fork_WorkStatus(0, 0, ORDER_CODE_NONE, WORK_STATUS_NONE, CMD_FORK_STEP_NONE);`
  - `Core/Inc/User_Define.h:1125: CMD_FORK_STEP_NONE = 0,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_FORK_STEP_RX

- **종류**: enum `enumCMD_FORK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 1		ï§ï¿½ï¿½ë±ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
- **용도(읽는 법)**: 포크 서브스텝: GET/PUT 내부 단계.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:46089: m_St.ForkWork[POS_FORK_1].OrderProcess_Fork = CMD_FORK_STEP_RX;`
  - `Core/Src/dev_SRM.c:46696: Store_Fork_WorkStatus(0, pCmd->Fork[POS_FORK_1].WorkNum, pCmd->OrderCode, WORK_STATUS_DOING, CMD_FOR`
  - `Core/Src/dev_SRM.c:47150: else if (m_St.ForkWork[0].OrderProcess_Fork == CMD_FORK_STEP_RX)`
  - `Core/Src/dev_SRM.c:47185: if ((m_St.ForkWork[0].OrderProcess_Fork >= CMD_FORK_STEP_RX) \`
  - `Core/Src/dev_SRM.c:47247: if ((m_St.ForkWork[0].OrderProcess_Fork == CMD_FORK_STEP_RX) \`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_FORK_STEP_MOVING_FROM

- **종류**: enum `enumCMD_FORK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 2		Fromï¿½ì°ï¿½ ï¿½ëï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
- **용도(읽는 법)**: 포크 서브스텝: GET/PUT 내부 단계.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:45917: & nTargetPos, CMD_FORK_STEP_MOVING_FROM, to_depth, 0, pCmd->LoadFactor);`
  - `Core/Src/dev_SRM.c:46643: CMD_FORK_STEP_MOVING_FROM, from_depth[POS_FORK_1], 0, pCmd->Fork[POS_FORK_1].Good_Type, pCmd->Operat`
  - `Core/Src/dev_SRM.c:46666: CMD_FORK_STEP_MOVING_FROM, from_depth[POS_FORK_1], 0, pCmd->Fork[POS_FORK_1].Good_Type, pCmd->Operat`
  - `Core/Src/dev_SRM.c:47290: CMD_FORK_STEP_MOVING_FROM, from_depth[0], 0, m_BKSram.WorkInfo.WorkCmd.Fork[1].Good_Type, 0);`
  - `Core/Src/dev_SRM.c:47311: CMD_FORK_STEP_MOVING_FROM, from_depth[0], 0, m_BKSram.WorkInfo.WorkCmd.Fork[1].Good_Type, 0);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_FORK_STEP_ARRIVED_FROM

- **종류**: enum `enumCMD_FORK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 3		From ï¿½ï¿½ï§¡ï¿½
- **용도(읽는 법)**: 포크 서브스텝: GET/PUT 내부 단계.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:59574: Save_ForkWork_OrderProcess(0, CMD_FORK_STEP_ARRIVED_FROM);`
  - `Core/Inc/User_Define.h:1128: CMD_FORK_STEP_ARRIVED_FROM,					//3		From ï¿½ï¿½ï§¡ï¿½`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_FORK_STEP_FORK_OUT_FROM

- **종류**: enum `enumCMD_FORK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 4		Fork ï§ï¿½ç°ï¿½
- **용도(읽는 법)**: 포크 서브스텝: GET/PUT 내부 단계.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:60593: Save_ForkWork_OrderProcess(0, CMD_FORK_STEP_FORK_OUT_FROM);`
  - `Core/Inc/User_Define.h:1129: CMD_FORK_STEP_FORK_OUT_FROM,				//4		Fork ï§ï¿½ç°ï¿½`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_FORK_STEP_FORK_UP_FROM

- **종류**: enum `enumCMD_FORK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 5		Fork ï¿½ï¿½ï¿½ï¿½ç§»ï¿½æ¿¡ï¿½ ï¿½ëï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
- **용도(읽는 법)**: 포크 서브스텝: GET/PUT 내부 단계.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:60848: Save_ForkWork_OrderProcess(0, CMD_FORK_STEP_FORK_UP_FROM);`
  - `Core/Inc/User_Define.h:1130: CMD_FORK_STEP_FORK_UP_FROM,					//5		Fork ï¿½ï¿½ï¿½ï¿½ç§»ï¿½æ¿¡ï¿½ ï¿½ëï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_FORK_STEP_FORK_IN_FROM

- **종류**: enum `enumCMD_FORK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 6		Fork è¹ë¦ï¿½ ï¿½ï¿½ï¿½ï¿½
- **용도(읽는 법)**: 포크 서브스텝: GET/PUT 내부 단계.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:47186: && (m_St.ForkWork[0].OrderProcess_Fork <= CMD_FORK_STEP_FORK_IN_FROM))`
  - `Core/Src/dev_SRM.c:60931: Save_ForkWork_OrderProcess(0, CMD_FORK_STEP_FORK_IN_FROM);`
  - `Core/Inc/User_Define.h:1131: CMD_FORK_STEP_FORK_IN_FROM,					//6		Fork è¹ë¦ï¿½ ï¿½ï¿½ï¿½ï¿½`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_FORK_STEP_MOVING_TO

- **종류**: enum `enumCMD_FORK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 7		toæ¿¡ï¿½ ï¿½ëï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
- **용도(읽는 법)**: 포크 서브스텝: GET/PUT 내부 단계.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:45922: & nTargetPos, CMD_FORK_STEP_MOVING_TO, to_depth, 0, pCmd->LoadFactor);`
  - `Core/Src/dev_SRM.c:46646: , CMD_FORK_STEP_MOVING_TO, to_depth[POS_FORK_1], 0, pCmd->Fork[1].Good_Type, pCmd->OperationFlag);`
  - `Core/Src/dev_SRM.c:46656: , CMD_FORK_STEP_MOVING_TO, to_depth[POS_FORK_1], 0, pCmd->Fork[1].Good_Type, pCmd->OperationFlag);`
  - `Core/Src/dev_SRM.c:47136: if ((m_St.ForkWork[0].OrderProcess_Fork >= CMD_FORK_STEP_MOVING_TO) \`
  - `Core/Src/dev_SRM.c:47214: else if ((m_St.ForkWork[0].OrderProcess_Fork >= CMD_FORK_STEP_MOVING_TO) \`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_FORK_STEP_ARRIVED_TO

- **종류**: enum `enumCMD_FORK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 8		to ï¿½ï¿½ï§¡ï¿½
- **용도(읽는 법)**: 포크 서브스텝: GET/PUT 내부 단계.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:59578: Save_ForkWork_OrderProcess(0, CMD_FORK_STEP_ARRIVED_TO);`
  - `Core/Inc/User_Define.h:1134: CMD_FORK_STEP_ARRIVED_TO,					//8		to ï¿½ï¿½ï§¡ï¿½`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_FORK_STEP_FORK_OUT_TO

- **종류**: enum `enumCMD_FORK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 9		Fork ï§ï¿½ç°ï¿½
- **용도(읽는 법)**: 포크 서브스텝: GET/PUT 내부 단계.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:61324: Save_ForkWork_OrderProcess(0, CMD_FORK_STEP_FORK_OUT_TO);`
  - `Core/Inc/User_Define.h:1135: CMD_FORK_STEP_FORK_OUT_TO,					//9		Fork ï§ï¿½ç°ï¿½`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_FORK_STEP_FORK_DOWN_TO

- **종류**: enum `enumCMD_FORK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 10	Fork ï¿½ï¿½ï¿½ï¿½ç§»ï¿½æ¿¡ï¿½ ï¿½ëï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
- **용도(읽는 법)**: 포크 서브스텝: GET/PUT 내부 단계.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:61621: Save_ForkWork_OrderProcess(0, CMD_FORK_STEP_FORK_DOWN_TO);`
  - `Core/Inc/User_Define.h:1136: CMD_FORK_STEP_FORK_DOWN_TO,					//10	Fork ï¿½ï¿½ï¿½ï¿½ç§»ï¿½æ¿¡ï¿½ ï¿½ëï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_FORK_STEP_FORK_IN_TO

- **종류**: enum `enumCMD_FORK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 11	Fork è¹ë¦ï¿½ ï¿½ï¿½ï¿½ï¿½
- **용도(읽는 법)**: 포크 서브스텝: GET/PUT 내부 단계.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:47137: && (m_St.ForkWork[0].OrderProcess_Fork <= CMD_FORK_STEP_FORK_IN_TO))`
  - `Core/Src/dev_SRM.c:47215: && (m_St.ForkWork[0].OrderProcess_Fork <= CMD_FORK_STEP_FORK_IN_TO))`
  - `Core/Src/dev_SRM.c:61679: Save_ForkWork_OrderProcess(0, CMD_FORK_STEP_FORK_IN_TO);`
  - `Core/Inc/User_Define.h:1137: CMD_FORK_STEP_FORK_IN_TO,					//11	Fork è¹ë¦ï¿½ ï¿½ï¿½ï¿½ï¿½`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_FORK_STEP_LODADED

- **종류**: enum `enumCMD_FORK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 12	ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ç·ï¿½
- **용도(읽는 법)**: 포크 서브스텝: GET/PUT 내부 단계.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:47200: else if (m_St.ForkWork[0].OrderProcess_Fork == CMD_FORK_STEP_LODADED)`
  - `Core/Src/dev_SRM.c:47360: WORK_STATUS_DOING, CMD_FORK_STEP_LODADED);`
  - `Core/Src/dev_SRM.c:61127: Save_ForkWork_OrderProcess(0, CMD_FORK_STEP_LODADED);`
  - `Core/Inc/User_Define.h:1139: CMD_FORK_STEP_LODADED,						//12	ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ç·ï¿½`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_FORK_STEP_UNLODADED

- **종류**: enum `enumCMD_FORK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 13	ï¿½ëï¿½ï¿½ ï¿½ï¿½ç·ï¿½
- **용도(읽는 법)**: 포크 서브스텝: GET/PUT 내부 단계.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:47163: else if (m_St.ForkWork[0].OrderProcess_Fork == CMD_FORK_STEP_UNLODADED)`
  - `Core/Src/dev_SRM.c:47228: else if (m_St.ForkWork[0].OrderProcess_Fork == CMD_FORK_STEP_UNLODADED)`
  - `Core/Src/dev_SRM.c:47305: WORK_STATUS_COMPLETE, CMD_FORK_STEP_UNLODADED);`
  - `Core/Src/dev_SRM.c:61818: Save_ForkWork_OrderProcess(0, CMD_FORK_STEP_UNLODADED); // 5: íë¬¼ì´ì¬ìë£`
  - `Core/Inc/User_Define.h:1140: CMD_FORK_STEP_UNLODADED,					//13	ï¿½ëï¿½ï¿½ ï¿½ï¿½ç·ï¿½`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_FORK_STEP_STICKY_MOVING_FROM

- **종류**: enum `enumCMD_FORK_STEP_PROCESS` 멤버
- **값**: `0x10`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 16	SRM äºì³ï¿½ï¿½ è«ï¿½ ï¿½ë±ï¿½ï¿½åªï¿½ ï¿½ï¿½ï¿½ï¿½
- **용도(읽는 법)**: 포크 서브스텝: GET/PUT 내부 단계.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:47248: || (m_St.ForkWork[0].OrderProcess_Fork == CMD_FORK_STEP_STICKY_MOVING_FROM) \`
  - `Core/Src/dev_SRM.c:47402: WORK_STATUS_DOING, CMD_FORK_STEP_STICKY_MOVING_FROM);`
  - `Core/Src/dev_SRM.c:58931: Save_ForkWork_OrderProcess(0, CMD_FORK_STEP_STICKY_MOVING_FROM); //íë¬¼ê°ì§ë¥¼ ìíë ëª¨ëë`
  - `Core/Src/dev_SRM.c:58943: Save_ForkWork_OrderProcess(0, CMD_FORK_STEP_STICKY_MOVING_FROM); //ì¤í°í¤ ì´ëëªë ¹ì ì§ìë`
  - `Core/Inc/User_Define.h:1142: CMD_FORK_STEP_STICKY_MOVING_FROM = 0x10,	//16	SRM äºì³ï¿½ï¿½ è«ï¿½ ï¿½ë±ï¿½ï¿½åªï¿½ ï¿½ï¿½ï¿½ï¿`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_FORK_STEP_STICKY_ARRIVED_FROM

- **종류**: enum `enumCMD_FORK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 17	SRM ï§â¹ï¿½ï¿½ï§ï¿½ ï¿½ï¿½ï§¡ï¿½
- **용도(읽는 법)**: 포크 서브스텝: GET/PUT 내부 단계.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:59582: Save_ForkWork_OrderProcess(0, CMD_FORK_STEP_STICKY_ARRIVED_FROM);`
  - `Core/Inc/User_Define.h:1143: CMD_FORK_STEP_STICKY_ARRIVED_FROM,			//17	SRM ï§â¹ï¿½ï¿½ï§ï¿½ ï¿½ï¿½ï§¡ï¿½`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_FORK_STEP_STICKY_FORK_OUT_FROM

- **종류**: enum `enumCMD_FORK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 18	Fork ï§ï¿½ç°ï¿½
- **용도(읽는 법)**: 포크 서브스텝: GET/PUT 내부 단계.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:47249: || (m_St.ForkWork[0].OrderProcess_Fork == CMD_FORK_STEP_STICKY_FORK_OUT_FROM))`
  - `Core/Src/dev_SRM.c:61901: Save_ForkWork_OrderProcess(0, CMD_FORK_STEP_STICKY_FORK_OUT_FROM);`
  - `Core/Inc/User_Define.h:1144: CMD_FORK_STEP_STICKY_FORK_OUT_FROM,			//18	Fork ï§ï¿½ç°ï¿½`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_FORK_STEP_STICKY_FORK_UP_FROM

- **종류**: enum `enumCMD_FORK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 19	ï§¦ï¿½ç±Ñï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
- **용도(읽는 법)**: 포크 서브스텝: GET/PUT 내부 단계.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:47261: else if ((m_St.ForkWork[0].OrderProcess_Fork >= CMD_FORK_STEP_STICKY_FORK_UP_FROM) \`
  - `Core/Src/dev_SRM.c:62137: Save_ForkWork_OrderProcess(0, CMD_FORK_STEP_STICKY_FORK_UP_FROM);`
  - `Core/Inc/User_Define.h:1145: CMD_FORK_STEP_STICKY_FORK_UP_FROM,			//19	ï§¦ï¿½ç±Ñï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_FORK_STEP_STICKY_FORK_DOWN_FROM

- **종류**: enum `enumCMD_FORK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 20	ï§¦ï¿½ç±Ñï¿½ ï¿½ï¿½åªï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
- **용도(읽는 법)**: 포크 서브스텝: GET/PUT 내부 단계.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:62270: Save_ForkWork_OrderProcess(0, CMD_FORK_STEP_STICKY_FORK_DOWN_FROM);`
  - `Core/Inc/User_Define.h:1146: CMD_FORK_STEP_STICKY_FORK_DOWN_FROM,		//20	ï§¦ï¿½ç±Ñï¿½ ï¿½ï¿½åªï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_FORK_STEP_STICKY_FORK_IN_FROM

- **종류**: enum `enumCMD_FORK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 21	Fork è¹ë¦ï¿½
- **용도(읽는 법)**: 포크 서브스텝: GET/PUT 내부 단계.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:47262: && (m_St.ForkWork[0].OrderProcess_Fork <= CMD_FORK_STEP_STICKY_FORK_IN_FROM))`
  - `Core/Src/dev_SRM.c:62339: Save_ForkWork_OrderProcess(0, CMD_FORK_STEP_STICKY_FORK_IN_FROM);`
  - `Core/Inc/User_Define.h:1147: CMD_FORK_STEP_STICKY_FORK_IN_FROM,			//21	Fork è¹ë¦ï¿½`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_FORK_STEP_STICKY_DONE

- **종류**: enum `enumCMD_FORK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 22	STICKY ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ç·ï¿½
- **용도(읽는 법)**: 포크 서브스텝: GET/PUT 내부 단계.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:47274: else if (m_St.ForkWork[0].OrderProcess_Fork == CMD_FORK_STEP_STICKY_DONE)`
  - `Core/Src/dev_SRM.c:47317: WORK_STATUS_COMPLETE, CMD_FORK_STEP_STICKY_DONE);`
  - `Core/Src/dev_SRM.c:47399: WORK_STATUS_DOING, CMD_FORK_STEP_STICKY_DONE);`
  - `Core/Src/dev_SRM.c:62520: Save_ForkWork_OrderProcess(0, CMD_FORK_STEP_STICKY_DONE);`
  - `Core/Inc/User_Define.h:1148: CMD_FORK_STEP_STICKY_DONE,					//22	STICKY ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ç·ï¿½`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TASK_STATUS_NONE

- **종류**: enum `enumCMD_TASK_STATUS` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: Task: TML 0x40 다중작업. 0x41과 분기 다름.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:3100: || (m_St.TaskWork[i].OrderState == TASK_STATUS_NONE))`
  - `Core/Inc/User_Define.h:1153: TASK_STATUS_NONE = 0,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

