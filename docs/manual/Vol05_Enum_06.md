# Vol.05 — 기타 Enum (6)

> 생성일: 2026-06-16 | MX SRM App Ver 4.4 | 소스 미수정

기타 enumeration.

---

### REMOCON_KEY_SPARE1

- **종류**: enum `enumREMOCON_KEY` 멤버
- **값**: `0x00010000`
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:3539: REMOCON_KEY_SPARE1		= 0x00010000,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### REMOCON_KEY_SPARE2

- **종류**: enum `enumREMOCON_KEY` 멤버
- **값**: `0x00020000`
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:3540: REMOCON_KEY_SPARE2		= 0x00020000,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### REMOCON_KEY_SPARE3

- **종류**: enum `enumREMOCON_KEY` 멤버
- **값**: `0x00040000`
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:3541: REMOCON_KEY_SPARE3		= 0x00040000,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### REMOCON_KEY_SPARE4

- **종류**: enum `enumREMOCON_KEY` 멤버
- **값**: `0x00080000`
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:3542: REMOCON_KEY_SPARE4		= 0x00080000,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### REMOCON_KEY_SPARE5

- **종류**: enum `enumREMOCON_KEY` 멤버
- **값**: `0x00100000`
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:3543: REMOCON_KEY_SPARE5		= 0x00100000,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### OP_MODE_NONE

- **종류**: enum `enumOP_MODE` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 모드 없음, 모드 없이 기동 시 알람 발생.
- **용도(읽는 법)**: 헤더 주석: 모드 없음, 모드 없이 기동 시 알람 발생.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:4707: Store_SRM_RxPDO_2(inverter, OP_MODE_NONE, 0, 0, (UnitVelocitySTR*)pVel);`
  - `Core/Src/dev_SRM.c:4787: Store_SRM_RxPDO_2(inverter, OP_MODE_NONE, 0, 0, (UnitVelocitySTR*)pVel);`
  - `Core/Src/dev_SRM.c:4866: Store_SRM_RxPDO_2(inverter, OP_MODE_NONE, 0, 0, (UnitVelocitySTR*)pVel);`
  - `Core/Src/dev_SRM.c:43668: Store_SRM_RxPDO_2(INV_TRAVEL, OP_MODE_NONE, nControlWord.W, 0, &DefaultTravVelocity);`
  - `Core/Src/dev_SRM.c:43669: Store_SRM_RxPDO_2(INV_HOIST, OP_MODE_NONE, nControlWord.W, 0, &DefaultLiftVelocity);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### OP_MODE_JOG_POS

- **종류**: enum `enumOP_MODE` 멤버
- **값**: `100`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 조그모드 (포지션기반 FCB06)
- **용도(읽는 법)**: 헤더 주석: 조그모드 (포지션기반 FCB06)
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:342: OP_MODE_JOG_POS = 100,			// 조그모드 (포지션기반 FCB06)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### OP_MODE_JOG_SPD

- **종류**: enum `enumOP_MODE` 멤버
- **값**: `101`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 조그모드 (스피드기반 FCB06)
- **용도(읽는 법)**: 헤더 주석: 조그모드 (스피드기반 FCB06)
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:2307: Store_SRM_RxPDO_2(INV_TRAVEL, OP_MODE_JOG_SPD, nControlWord_1.W, 0, &nVelocity);`
  - `Core/Src/dev_SRM.c:2318: Store_SRM_RxPDO_2(INV_TRAVEL, OP_MODE_JOG_SPD, nControlWord_2.W, 0, &nVelocity);`
  - `Core/Src/dev_SRM.c:2341: Store_SRM_RxPDO_2(INV_TRAVEL, OP_MODE_JOG_SPD, nControlWord_1.W, 0, &nVelocity);`
  - `Core/Src/dev_SRM.c:2350: Store_SRM_RxPDO_2(INV_TRAVEL, OP_MODE_JOG_SPD, nControlWord_2.W, 0, &nVelocity);`
  - `Core/Src/dev_SRM.c:2373: Store_SRM_RxPDO_2(INV_TRAVEL, OP_MODE_JOG_SPD, nControlWord_1.W, 0, &nVelocity);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### OP_MODE_SPD_CTR

- **종류**: enum `enumOP_MODE` 멤버
- **값**: `200`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 속도 제어 (스피드기반 FCB06)
- **용도(읽는 법)**: 헤더 주석: 속도 제어 (스피드기반 FCB06)
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:344: OP_MODE_SPD_CTR = 200,			// 속도 제어 (스피드기반 FCB06)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### OP_MODE_REF

- **종류**: enum `enumOP_MODE` 멤버
- **값**: `300`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 원점모드
- **용도(읽는 법)**: 헤더 주석: 원점모드
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:4641: nMode = OP_MODE_REF;`
  - `Core/Src/dev_SRM.c:4651: nMode = OP_MODE_REF;`
  - `Core/Src/dev_SRM.c:4660: nMode = OP_MODE_REF;`
  - `Core/Src/dev_SRM.c:4670: nMode = OP_MODE_REF;`
  - `Core/Src/dev_SRM.c:4679: nMode = OP_MODE_REF;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### OP_MODE_REF_OFFSET

- **종류**: enum `enumOP_MODE` 멤버
- **값**: `301`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 원점모드 with 필드버스 유저오프셋
- **용도(읽는 법)**: 헤더 주석: 원점모드 with 필드버스 유저오프셋
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:4646: nMode = OP_MODE_REF_OFFSET;`
  - `Core/Src/dev_SRM.c:4665: nMode = OP_MODE_REF_OFFSET;`
  - `Core/Src/dev_SRM.c:4683: nMode = OP_MODE_REF_OFFSET;`
  - `Core/Src/dev_SRM.c:4726: nMode = OP_MODE_REF_OFFSET;`
  - `Core/Src/dev_SRM.c:4745: nMode = OP_MODE_REF_OFFSET;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### OP_MODE_ABSOLUTE_POS

- **종류**: enum `enumOP_MODE` 멤버
- **값**: `400`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 절대 위치 제어 (FCB06)
- **용도(읽는 법)**: 헤더 주석: 절대 위치 제어 (FCB06)
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:2132: Store_SRM_RxPDO_2(INV_TRAVEL, OP_MODE_ABSOLUTE_POS, nControlWord_1.W, position, &nCmdVelocity);`
  - `Core/Src/dev_SRM.c:2140: Store_SRM_RxPDO_2(INV_TRAVEL, OP_MODE_ABSOLUTE_POS, nControlWord_2.W, position, &nCmdVelocity);`
  - `Core/Src/dev_SRM.c:2148: Store_SRM_RxPDO_2(INV_TRAVEL, OP_MODE_ABSOLUTE_POS, nControlWord_1.W, position, &nCmdVelocity);`
  - `Core/Src/dev_SRM.c:2219: Store_SRM_RxPDO_2(INV_TRAVEL, OP_MODE_ABSOLUTE_POS, nControlWord_1.W, position, &nVelocity);`
  - `Core/Src/dev_SRM.c:2227: Store_SRM_RxPDO_2(INV_TRAVEL, OP_MODE_ABSOLUTE_POS, nControlWord_2.W, position, &nVelocity);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### OP_MODE_RELATIVE_POS

- **종류**: enum `enumOP_MODE` 멤버
- **값**: `401`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 상대 위치 제어 (FCB06)
- **용도(읽는 법)**: 헤더 주석: 상대 위치 제어 (FCB06)
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:348: OP_MODE_RELATIVE_POS = 401,		// 상대 위치 제어 (FCB06)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HMI_STAND_BY

- **종류**: enum `enumHMI_OPERATION_FLAG` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1328: HMI_STAND_BY = 0,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HMI_READ_REALTIME_REGISTER

- **종류**: enum `enumHMI_OPERATION_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:5967: if (m_HMI_Com.Req_Flag == HMI_READ_REALTIME_REGISTER)`
  - `Core/Src/dev_SRM.c:6252: m_HMI_Com.Req_Flag = HMI_READ_REALTIME_REGISTER;`
  - `Core/Src/dev_SRM.c:6574: if (m_HMI_Com.Req_Flag == HMI_READ_REALTIME_REGISTER)`
  - `Core/Src/dev_SRM.c:65499: if (m_HMI_Com.Recv_Flag == HMI_READ_REALTIME_REGISTER)`
  - `Core/Src/dev_SRM.c:65564: if (m_HMI_Com.Recv_Flag == HMI_READ_REALTIME_REGISTER)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HMI_READ_SYS_TIME

- **종류**: enum `enumHMI_OPERATION_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:5985: else if (m_HMI_Com.Req_Flag == HMI_READ_SYS_TIME)`
  - `Core/Src/dev_SRM.c:6270: m_HMI_Com.Req_Flag = HMI_READ_SYS_TIME;`
  - `Core/Src/dev_SRM.c:6582: else if (m_HMI_Com.Req_Flag == HMI_READ_SYS_TIME)`
  - `Core/Src/dev_SRM.c:65720: if (m_HMI_Com.Recv_Flag == HMI_READ_SYS_TIME)`
  - `Core/Inc/dev_SRM.h:1330: HMI_READ_SYS_TIME,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HMI_WRITE_REALTIME_REGISTER

- **종류**: enum `enumHMI_OPERATION_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6229: m_HMI_Com.Req_Flag = HMI_WRITE_REALTIME_REGISTER;`
  - `Core/Src/dev_SRM.c:6612: if (m_HMI_Com.Req_Flag == HMI_WRITE_REALTIME_REGISTER)`
  - `Core/Src/dev_SRM.c:65532: if (m_HMI_Com.Recv_Flag == HMI_WRITE_REALTIME_REGISTER)`
  - `Core/Inc/dev_SRM.h:1331: HMI_WRITE_REALTIME_REGISTER,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HMI_WRITE_REALTIME_MW1

- **종류**: enum `enumHMI_OPERATION_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6294: m_HMI_Com.Req_Flag = HMI_WRITE_REALTIME_MW1;`
  - `Core/Src/dev_SRM.c:6617: else if (m_HMI_Com.Req_Flag == HMI_WRITE_REALTIME_MW1)`
  - `Core/Src/dev_SRM.c:65619: if (m_HMI_Com.Recv_Flag == HMI_WRITE_REALTIME_MW1)`
  - `Core/Inc/dev_SRM.h:1332: HMI_WRITE_REALTIME_MW1,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HMI_WRITE_SYS_TIME

- **종류**: enum `enumHMI_OPERATION_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6316: m_HMI_Com.Req_Flag = HMI_WRITE_SYS_TIME;`
  - `Core/Src/dev_SRM.c:6622: else if (m_HMI_Com.Req_Flag == HMI_WRITE_SYS_TIME)`
  - `Core/Src/dev_SRM.c:65658: if (m_HMI_Com.Recv_Flag == HMI_WRITE_SYS_TIME)`
  - `Core/Src/dev_SRM.c:65691: if (m_HMI_Com.Recv_Flag == HMI_WRITE_SYS_TIME)`
  - `Core/Inc/dev_SRM.h:1333: HMI_WRITE_SYS_TIME,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HMI_ADDRESS_REALTIME

- **종류**: enum `enumHMI_REGISTER_ADDRRESS` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6224: INT16U nWriteAddress = HMI_ADDRESS_REALTIME + 3;`
  - `Core/Src/dev_SRM.c:6259: ModbusTcpRead(TCP_SOCKET_HMI, HMI_UNIT_ID, HMI_ADDRESS_REALTIME, nReadWordCnt);`
  - `Core/Src/dev_SRM.c:6288: INT16U nWriteAddress = HMI_ADDRESS_REALTIME + 1;`
  - `Core/Inc/dev_SRM.h:1337: HMI_ADDRESS_REALTIME = 0,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HMI_ADDRESS_SYS_TIME

- **종류**: enum `enumHMI_REGISTER_ADDRRESS` 멤버
- **값**: `131`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:5989: nAddress = HMI_ADDRESS_SYS_TIME;`
  - `Core/Src/dev_SRM.c:6277: ModbusTcpRead(TCP_SOCKET_HMI, HMI_UNIT_ID, HMI_ADDRESS_SYS_TIME, nReadWordCnt);`
  - `Core/Inc/dev_SRM.h:1338: HMI_ADDRESS_SYS_TIME = 131,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HMI_ADDRESS_PAGE_NO

- **종류**: enum `enumHMI_REGISTER_ADDRRESS` 멤버
- **값**: `135`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1339: HMI_ADDRESS_PAGE_NO = 135,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HMI_ADDRESS_SYS_TIME_SET

- **종류**: enum `enumHMI_REGISTER_ADDRRESS` 멤버
- **값**: `136`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6309: INT16U nWriteAddress = HMI_ADDRESS_SYS_TIME_SET;`
  - `Core/Inc/dev_SRM.h:1340: HMI_ADDRESS_SYS_TIME_SET = 136,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### GRAPH_START_RECORDING_WHEN_DRIVING_BEGINS

- **종류**: enum `enumGRAPH_TYPE` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 주행 시작시 기록 시작
- **용도(읽는 법)**: 헤더 주석: 주행 시작시 기록 시작
- **코드 참조 예**:
  - `Core/Src/alarm.c:220: if ((m_BKSram.Graph_Type == GRAPH_START_RECORDING_WHEN_DRIVING_BEGINS) \`
  - `Core/Src/alarm.c:295: if ((m_BKSram.Graph_Type != GRAPH_START_RECORDING_WHEN_DRIVING_BEGINS) \`
  - `Core/Src/alarm.c:299: m_BKSram.Graph_Type = GRAPH_START_RECORDING_WHEN_DRIVING_BEGINS;`
  - `Core/Src/alarm.c:330: if ((nGraphType == GRAPH_START_RECORDING_WHEN_DRIVING_BEGINS) \`
  - `Core/Inc/dev_SRM.h:1677: GRAPH_START_RECORDING_WHEN_DRIVING_BEGINS = 0,			// 주행 시작시 기록 시작`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### GRAPH_START_RECORDING_FROM_THE_SET_DRIVING_LOCATION

- **종류**: enum `enumGRAPH_TYPE` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 설정된 주행 위치부터 기록 시작
- **용도(읽는 법)**: 헤더 주석: 설정된 주행 위치부터 기록 시작
- **코드 참조 예**:
  - `Core/Src/alarm.c:226: else if (m_BKSram.Graph_Type == GRAPH_START_RECORDING_FROM_THE_SET_DRIVING_LOCATION)`
  - `Core/Src/alarm.c:296: && (m_BKSram.Graph_Type != GRAPH_START_RECORDING_FROM_THE_SET_DRIVING_LOCATION) \`
  - `Core/Src/alarm.c:331: || (nGraphType == GRAPH_START_RECORDING_FROM_THE_SET_DRIVING_LOCATION) \`
  - `Core/Src/alarm.c:344: if (m_BKSram.Graph_Type == GRAPH_START_RECORDING_FROM_THE_SET_DRIVING_LOCATION)`
  - `Core/Inc/dev_SRM.h:1678: GRAPH_START_RECORDING_FROM_THE_SET_DRIVING_LOCATION,	// 설정된 주행 위치부터 기록 시작`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### GRAPH_START_RECORDING_IMMEDIATELY

- **종류**: enum `enumGRAPH_TYPE` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/alarm.c:221: || (m_BKSram.Graph_Type == GRAPH_START_RECORDING_IMMEDIATELY))`
  - `Core/Src/alarm.c:297: && (m_BKSram.Graph_Type != GRAPH_START_RECORDING_IMMEDIATELY))`
  - `Core/Src/alarm.c:332: || (nGraphType == GRAPH_START_RECORDING_IMMEDIATELY))`
  - `Core/Src/alarm.c:354: if (nGraphType == GRAPH_START_RECORDING_IMMEDIATELY)`
  - `Core/Inc/dev_SRM.h:1679: GRAPH_START_RECORDING_IMMEDIATELY,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### INV_VENDOR_SEW

- **종류**: enum `enumINVERTER_VENDOR` 멤버
- **값**: `1`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: SEW MOVI-C
- **용도(읽는 법)**: 인버터/EtherCAT 상태. m_ExtSEnv와 함께 확인.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:293: m_ExtSEnv.Machine.mType.Inverter_Vendor = INV_VENDOR_SEW;`
  - `Core/Src/dev_SRM.c:1129: if (m_ExtSEnv.Machine.mType.Inverter_Vendor == INV_VENDOR_SEW)`
  - `Core/Src/dev_SRM.c:1256: if (m_ExtSEnv.Machine.mType.Inverter_Vendor == INV_VENDOR_SEW)`
  - `Core/Src/dev_SRM.c:1313: if (m_ExtSEnv.Machine.mType.Inverter_Vendor == INV_VENDOR_SEW)`
  - `Core/Src/dev_SRM.c:1370: if (m_ExtSEnv.Machine.mType.Inverter_Vendor == INV_VENDOR_SEW)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### INV_VENDOR_SIMENS

- **종류**: enum `enumINVERTER_VENDOR` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: 인버터/EtherCAT 상태. m_ExtSEnv와 함께 확인.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1684: INV_VENDOR_SIMENS,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### INV_VENDOR_SEW_VER2

- **종류**: enum `enumINVERTER_VENDOR` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: SEW 표준프로토콜
- **용도(읽는 법)**: 인버터/EtherCAT 상태. m_ExtSEnv와 함께 확인.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:942: else if (m_ExtSEnv.Machine.mType.Inverter_Vendor == INV_VENDOR_SEW_VER2)`
  - `Core/Src/dev_SRM.c:983: else if (m_ExtSEnv.Machine.mType.Inverter_Vendor == INV_VENDOR_SEW_VER2)`
  - `Core/Src/dev_SRM.c:1033: else if (m_ExtSEnv.Machine.mType.Inverter_Vendor == INV_VENDOR_SEW_VER2)`
  - `Core/Src/dev_SRM.c:1176: else if (m_ExtSEnv.Machine.mType.Inverter_Vendor == INV_VENDOR_SEW_VER2)`
  - `Core/Src/dev_SRM.c:1275: else if (m_ExtSEnv.Machine.mType.Inverter_Vendor == INV_VENDOR_SEW_VER2)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### INV_VENDOR_SEW_VER2_ANTI_SWAY

- **종류**: enum `enumINVERTER_VENDOR` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: SEW 표준프로토콜 + MAC
- **용도(읽는 법)**: 인버터/EtherCAT 상태. m_ExtSEnv와 함께 확인.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:931: if (m_ExtSEnv.Machine.mType.Inverter_Vendor == INV_VENDOR_SEW_VER2_ANTI_SWAY)`
  - `Core/Src/dev_SRM.c:972: if (m_ExtSEnv.Machine.mType.Inverter_Vendor == INV_VENDOR_SEW_VER2_ANTI_SWAY)`
  - `Core/Src/dev_SRM.c:1022: if (m_ExtSEnv.Machine.mType.Inverter_Vendor == INV_VENDOR_SEW_VER2_ANTI_SWAY)`
  - `Core/Src/dev_SRM.c:1140: else if (m_ExtSEnv.Machine.mType.Inverter_Vendor == INV_VENDOR_SEW_VER2_ANTI_SWAY)`
  - `Core/Src/dev_SRM.c:1260: else if (m_ExtSEnv.Machine.mType.Inverter_Vendor == INV_VENDOR_SEW_VER2_ANTI_SWAY)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### INV_VENDOR_SEW_VER2_SYNC_TRAVEL

- **종류**: enum `enumINVERTER_VENDOR` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: SEW 표준프로토콜 + MAC
- **용도(읽는 법)**: 인버터/EtherCAT 상태. m_ExtSEnv와 함께 확인.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:1395: if (m_ExtSEnv.Machine.mType.Inverter_Vendor == INV_VENDOR_SEW_VER2_SYNC_TRAVEL)`
  - `Core/Src/dev_SRM.c:953: else if (m_ExtSEnv.Machine.mType.Inverter_Vendor == INV_VENDOR_SEW_VER2_SYNC_TRAVEL)`
  - `Core/Src/dev_SRM.c:994: else if (m_ExtSEnv.Machine.mType.Inverter_Vendor == INV_VENDOR_SEW_VER2_SYNC_TRAVEL)`
  - `Core/Src/dev_SRM.c:1044: else if (m_ExtSEnv.Machine.mType.Inverter_Vendor == INV_VENDOR_SEW_VER2_SYNC_TRAVEL)`
  - `Core/Src/dev_SRM.c:1212: else if (m_ExtSEnv.Machine.mType.Inverter_Vendor == INV_VENDOR_SEW_VER2_SYNC_TRAVEL)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_ENC_ABSOLUTE

- **종류**: enum `enumFORK_ENCODER_TYPE` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/main.c:627: m_pgmEnv.Fork_Encoder_Type = FORK_ENC_ABSOLUTE;`
  - `Core/Inc/dev_SRM.h:1691: FORK_ENC_ABSOLUTE = 0,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_ENC_INCREMENTAL

- **종류**: enum `enumFORK_ENCODER_TYPE` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 전원리셋 시, 포크 원점 재설정 필요.
- **용도(읽는 법)**: 헤더 주석: 전원리셋 시, 포크 원점 재설정 필요.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:58639: if (m_pgmEnv.Fork_Encoder_Type == FORK_ENC_INCREMENTAL)`
  - `Core/Inc/dev_SRM.h:1692: FORK_ENC_INCREMENTAL,		// 전원리셋 시, 포크 원점 재설정 필요.`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_TYPE_NONE

- **종류**: enum `enumSRM_FORK_TYPE` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1696: FORK_TYPE_NONE = 0,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_TYPE_SINGLE_DEEP

- **종류**: enum `enumSRM_FORK_TYPE` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:292: m_ExtSEnv.Machine.mType.Fork_Type = FORK_TYPE_SINGLE_DEEP;`
  - `Core/Src/SRM_Parameter.c:5929: if (m_ExtSEnv.Machine.mType.Fork_Type == FORK_TYPE_SINGLE_DEEP)`
  - `Core/Src/SRM_Parameter.c:5974: if (m_ExtSEnv.Machine.mType.Fork_Type == FORK_TYPE_SINGLE_DEEP)`
  - `Core/Src/com_tml.c:5439: if (m_ExtSEnv.Machine.mType.Fork_Type == FORK_TYPE_SINGLE_DEEP)`
  - `Core/Src/dev_SRM.c:9571: if (m_ExtSEnv.Machine.mType.Fork_Type == FORK_TYPE_SINGLE_DEEP)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_TYPE_DOUBLE_DEEP_2POS

- **종류**: enum `enumSRM_FORK_TYPE` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:5943: else if (m_ExtSEnv.Machine.mType.Fork_Type == FORK_TYPE_DOUBLE_DEEP_2POS)`
  - `Core/Src/SRM_Parameter.c:5993: else if (m_ExtSEnv.Machine.mType.Fork_Type == FORK_TYPE_DOUBLE_DEEP_2POS)`
  - `Core/Src/dev_SRM.c:9583: else if (m_ExtSEnv.Machine.mType.Fork_Type == FORK_TYPE_DOUBLE_DEEP_2POS)`
  - `Core/Src/dev_SRM.c:10008: else if (m_ExtSEnv.Machine.mType.Fork_Type == FORK_TYPE_DOUBLE_DEEP_2POS)`
  - `Core/Src/dev_SRM.c:10362: else if (m_ExtSEnv.Machine.mType.Fork_Type == FORK_TYPE_DOUBLE_DEEP_2POS)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_TYPE_DOUBLE_DEEP_3POS

- **종류**: enum `enumSRM_FORK_TYPE` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:9662: else if (m_ExtSEnv.Machine.mType.Fork_Type == FORK_TYPE_DOUBLE_DEEP_3POS)`
  - `Core/Src/dev_SRM.c:10749: else if (m_ExtSEnv.Machine.mType.Fork_Type == FORK_TYPE_DOUBLE_DEEP_3POS)`
  - `Core/Src/dev_SRM.c:12269: || (m_ExtSEnv.Machine.mType.Fork_Type == FORK_TYPE_DOUBLE_DEEP_3POS))`
  - `Core/Src/dev_SRM.c:13257: || (m_ExtSEnv.Machine.mType.Fork_Type == FORK_TYPE_DOUBLE_DEEP_3POS))`
  - `Core/Src/dev_SRM.c:14243: || (m_ExtSEnv.Machine.mType.Fork_Type == FORK_TYPE_DOUBLE_DEEP_3POS))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LAMP_OFF

- **종류**: enum `enumLAMP_COLOR` 멤버
- **값**: `0x00`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/alarm.c:958: case LAMP_OFF:`
  - `Core/Src/alarm.c:1067: LED_Bar_Control(LAMP_OFF);`
  - `Core/Inc/dev_SRM.h:1703: LAMP_OFF = 0x00,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LAMP_RED

- **종류**: enum `enumLAMP_COLOR` 멤버
- **값**: `0x01`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/alarm.c:963: case LAMP_RED:`
  - `Core/Src/alarm.c:1023: LED_Bar_Control(LAMP_RED);`
  - `Core/Inc/dev_SRM.h:1704: LAMP_RED = 0x01,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LAMP_YELLOW

- **종류**: enum `enumLAMP_COLOR` 멤버
- **값**: `0x02`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/alarm.c:968: case LAMP_YELLOW:`
  - `Core/Src/alarm.c:1029: LED_Bar_Control(LAMP_YELLOW);`
  - `Core/Src/alarm.c:1059: LED_Bar_Control(LAMP_YELLOW);`
  - `Core/Inc/dev_SRM.h:1705: LAMP_YELLOW = 0x02,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LAMP_GREEN

- **종류**: enum `enumLAMP_COLOR` 멤버
- **값**: `0x04`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/alarm.c:973: case LAMP_GREEN:`
  - `Core/Src/alarm.c:1048: LED_Bar_Control(LAMP_GREEN);`
  - `Core/Inc/dev_SRM.h:1706: LAMP_GREEN = 0x04,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LAMP_BLUE

- **종류**: enum `enumLAMP_COLOR` 멤버
- **값**: `0x08`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/alarm.c:978: case LAMP_BLUE:`
  - `Core/Inc/dev_SRM.h:1707: LAMP_BLUE = 0x08,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LAMP_MAGENTA

- **종류**: enum `enumLAMP_COLOR` 멤버
- **값**: `0x10`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/alarm.c:983: case LAMP_MAGENTA:`
  - `Core/Inc/dev_SRM.h:1708: LAMP_MAGENTA = 0x10,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LAMP_CYAN

- **종류**: enum `enumLAMP_COLOR` 멤버
- **값**: `0x20`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/alarm.c:988: case LAMP_CYAN:`
  - `Core/Src/alarm.c:1037: LED_Bar_Control(LAMP_CYAN);`
  - `Core/Inc/dev_SRM.h:1709: LAMP_CYAN = 0x20,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LAMP_WHITE

- **종류**: enum `enumLAMP_COLOR` 멤버
- **값**: `0x40`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/alarm.c:993: case LAMP_WHITE:`
  - `Core/Src/alarm.c:1052: LED_Bar_Control(LAMP_WHITE);`
  - `Core/Inc/dev_SRM.h:1710: LAMP_WHITE = 0x40,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_MACHINE_INIT

- **종류**: enum `enumSRM_MACHINE_STATE` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:63570: case SRM_MACHINE_INIT:`
  - `Core/Src/dev_SRM.c:63620: m_pgmEnv.SRM_Machine_State = SRM_MACHINE_INIT;`
  - `Core/Src/dev_SRM.c:63645: m_pgmEnv.SRM_Machine_State = SRM_MACHINE_INIT;`
  - `Core/Src/dev_SRM.c:63761: m_pgmEnv.SRM_Machine_State = SRM_MACHINE_INIT;`
  - `Core/Inc/dev_SRM.h:1726: SRM_MACHINE_INIT = 0,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_MACHINE_POWER_ON

- **종류**: enum `enumSRM_MACHINE_STATE` 멤버
- **값**: `10`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:43602: m_pgmEnv.SRM_Machine_State = SRM_MACHINE_POWER_ON;`
  - `Core/Src/dev_SRM.c:43711: m_pgmEnv.SRM_Machine_State = SRM_MACHINE_POWER_ON;`
  - `Core/Src/dev_SRM.c:43804: m_pgmEnv.SRM_Machine_State = SRM_MACHINE_POWER_ON;`
  - `Core/Src/dev_SRM.c:43970: m_pgmEnv.SRM_Machine_State = SRM_MACHINE_POWER_ON;`
  - `Core/Src/dev_SRM.c:63599: if ((m_pgmEnv.SRM_Machine_State == SRM_MACHINE_POWER_ON)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_MACHINE_DRIVE_ON

- **종류**: enum `enumSRM_MACHINE_STATE` 멤버
- **값**: `20`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:44108: m_pgmEnv.SRM_Machine_State = SRM_MACHINE_DRIVE_ON;`
  - `Core/Src/dev_SRM.c:63624: else if ((m_pgmEnv.SRM_Machine_State == SRM_MACHINE_DRIVE_ON)`
  - `Core/Src/dev_SRM.c:63632: case SRM_MACHINE_DRIVE_ON:`
  - `Core/Inc/dev_SRM.h:1728: SRM_MACHINE_DRIVE_ON = 20,`
  - `Core/Inc/dev_SRM.h:1754: SRM_MACHINE_DRIVE_ON,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_MACHINE_MANUAL

- **종류**: enum `enumSRM_MACHINE_STATE` 멤버
- **값**: `30`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:15707: if (m_pgmEnv.SRM_Machine_State < SRM_MACHINE_MANUAL)	return;`
  - `Core/Src/dev_SRM.c:16611: if (m_pgmEnv.SRM_Machine_State < SRM_MACHINE_MANUAL)	return;`
  - `Core/Src/dev_SRM.c:17162: if (m_pgmEnv.SRM_Machine_State < SRM_MACHINE_MANUAL)	return;`
  - `Core/Src/dev_SRM.c:17751: if (m_pgmEnv.SRM_Machine_State < SRM_MACHINE_MANUAL)	return;`
  - `Core/Src/dev_SRM.c:18398: if (m_pgmEnv.SRM_Machine_State < SRM_MACHINE_MANUAL)	return;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_MACHINE_STAND_BY_0

- **종류**: enum `enumSRM_MACHINE_STATE` 멤버
- **값**: `40`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:63747: case SRM_MACHINE_STAND_BY_0:`
  - `Core/Inc/dev_SRM.h:1730: SRM_MACHINE_STAND_BY_0 = 40,`
  - `Core/Inc/dev_SRM.h:1756: SRM_MACHINE_STAND_BY_0,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_MACHINE_STAND_BY_1

- **종류**: enum `enumSRM_MACHINE_STATE` 멤버
- **값**: `50`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:63750: case SRM_MACHINE_STAND_BY_1:`
  - `Core/Inc/dev_SRM.h:1731: SRM_MACHINE_STAND_BY_1 = 50,`
  - `Core/Inc/dev_SRM.h:1757: SRM_MACHINE_STAND_BY_1,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_MACHINE_ONLINE

- **종류**: enum `enumSRM_MACHINE_STATE` 멤버
- **값**: `60`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:63753: case SRM_MACHINE_ONLINE:`
  - `Core/Inc/dev_SRM.h:1732: SRM_MACHINE_ONLINE = 60,`
  - `Core/Inc/dev_SRM.h:1758: SRM_MACHINE_ONLINE,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_MACHINE_SETUP

- **종류**: enum `enumSRM_MACHINE_STATE` 멤버
- **값**: `70`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:63756: case SRM_MACHINE_SETUP:`
  - `Core/Inc/dev_SRM.h:1733: SRM_MACHINE_SETUP = 70,`
  - `Core/Inc/dev_SRM.h:1759: SRM_MACHINE_SETUP,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_MACHINE_FAULT

- **종류**: enum `enumSRM_MACHINE_STATE` 멤버
- **값**: `80`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:63616: m_pgmEnv.SRM_Machine_State = SRM_MACHINE_FAULT;`
  - `Core/Src/dev_SRM.c:63641: m_pgmEnv.SRM_Machine_State = SRM_MACHINE_FAULT;`
  - `Core/Src/dev_SRM.c:63709: m_pgmEnv.SRM_Machine_State = SRM_MACHINE_FAULT;`
  - `Core/Src/dev_SRM.c:63733: m_pgmEnv.SRM_Machine_State = SRM_MACHINE_FAULT;`
  - `Core/Src/dev_SRM.c:63759: case SRM_MACHINE_FAULT:`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_ORIGIN_FCL

- **종류**: enum `enumSRM_FORK_ORIGIN_SENSOR` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:6162: nInitParam.OriginSensor = FORK_ORIGIN_FCL;`
  - `Core/Src/dev_SRM.c:8770: if (m_ExtSEnv2.ForkDrive.OriginSensor == FORK_ORIGIN_FCL)`
  - `Core/Src/dev_SRM.c:9318: if (m_ExtSEnv2.ForkDrive.OriginSensor == FORK_ORIGIN_FCL)`
  - `Core/Inc/dev_SRM.h:1738: FORK_ORIGIN_FCL = 0,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_ORIGIN_FCR

- **종류**: enum `enumSRM_FORK_ORIGIN_SENSOR` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1739: FORK_ORIGIN_FCR,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MAN_CTR_NONE

- **종류**: enum `enumMANUAL_CONTROL_FLAG` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:30078: /*if ((m_pgmEnv.SRM_RunMode == RUN_SEQ_STAND_BY) && (m_MANUAL_CTR_Flag == MAN_CTR_NONE))*/`
  - `Core/Src/dev_SRM.c:34777: m_Manual_Ctr_Flag = MAN_CTR_NONE;`
  - `Core/Src/dev_SRM.c:34795: m_Manual_Ctr_Flag = MAN_CTR_NONE;`
  - `Core/Src/dev_SRM.c:35382: m_Manual_Ctr_Flag = MAN_CTR_NONE;`
  - `Core/Src/dev_SRM.c:35408: m_Manual_Ctr_Flag = MAN_CTR_NONE;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MAN_CTR_TRAV

- **종류**: enum `enumMANUAL_CONTROL_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:29667: if (m_Manual_Ctr_Flag == MAN_CTR_TRAV)`
  - `Core/Src/dev_SRM.c:29685: if (m_Manual_Ctr_Flag == MAN_CTR_TRAV)`
  - `Core/Src/dev_SRM.c:29699: if (m_Manual_Ctr_Flag == MAN_CTR_TRAV)`
  - `Core/Src/dev_SRM.c:29801: m_Manual_Ctr_Flag = MAN_CTR_TRAV;`
  - `Core/Src/dev_SRM.c:30167: if (m_Manual_Ctr_Flag == MAN_CTR_TRAV)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MAN_CTR_LIFT

- **종류**: enum `enumMANUAL_CONTROL_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:29842: if (m_Manual_Ctr_Flag == MAN_CTR_LIFT)`
  - `Core/Src/dev_SRM.c:29860: if (m_Manual_Ctr_Flag == MAN_CTR_LIFT)`
  - `Core/Src/dev_SRM.c:29874: if (m_Manual_Ctr_Flag == MAN_CTR_LIFT)`
  - `Core/Src/dev_SRM.c:29975: m_Manual_Ctr_Flag = MAN_CTR_LIFT;`
  - `Core/Src/dev_SRM.c:30317: if (m_Manual_Ctr_Flag == MAN_CTR_LIFT)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MAN_CTR_FORK_1

- **종류**: enum `enumMANUAL_CONTROL_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:30029: if (m_Manual_Ctr_Flag == MAN_CTR_FORK_1)`
  - `Core/Src/dev_SRM.c:30047: if (m_Manual_Ctr_Flag == MAN_CTR_FORK_1)`
  - `Core/Src/dev_SRM.c:30062: if (m_Manual_Ctr_Flag == MAN_CTR_FORK_1)`
  - `Core/Src/dev_SRM.c:30081: m_Manual_Ctr_Flag = MAN_CTR_FORK_1;`
  - `Core/Src/dev_SRM.c:30112: m_Manual_Ctr_Flag = MAN_CTR_FORK_1;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MAN_CTR_FORK_2

- **종류**: enum `enumMANUAL_CONTROL_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1747: MAN_CTR_FORK_2,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_MACHINE_STATE_

- **종류**: enum `enumSRM_MACHINE_STATE_SEQ` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1752: SRM_MACHINE_STATE_ = 0,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_MACHINE_POWER_ON

- **종류**: enum `enumSRM_MACHINE_STATE_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:43602: m_pgmEnv.SRM_Machine_State = SRM_MACHINE_POWER_ON;`
  - `Core/Src/dev_SRM.c:43711: m_pgmEnv.SRM_Machine_State = SRM_MACHINE_POWER_ON;`
  - `Core/Src/dev_SRM.c:43804: m_pgmEnv.SRM_Machine_State = SRM_MACHINE_POWER_ON;`
  - `Core/Src/dev_SRM.c:43970: m_pgmEnv.SRM_Machine_State = SRM_MACHINE_POWER_ON;`
  - `Core/Src/dev_SRM.c:63599: if ((m_pgmEnv.SRM_Machine_State == SRM_MACHINE_POWER_ON)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_MACHINE_DRIVE_ON

- **종류**: enum `enumSRM_MACHINE_STATE_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:44108: m_pgmEnv.SRM_Machine_State = SRM_MACHINE_DRIVE_ON;`
  - `Core/Src/dev_SRM.c:63624: else if ((m_pgmEnv.SRM_Machine_State == SRM_MACHINE_DRIVE_ON)`
  - `Core/Src/dev_SRM.c:63632: case SRM_MACHINE_DRIVE_ON:`
  - `Core/Inc/dev_SRM.h:1728: SRM_MACHINE_DRIVE_ON = 20,`
  - `Core/Inc/dev_SRM.h:1754: SRM_MACHINE_DRIVE_ON,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_MACHINE_MANUAL

- **종류**: enum `enumSRM_MACHINE_STATE_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:15707: if (m_pgmEnv.SRM_Machine_State < SRM_MACHINE_MANUAL)	return;`
  - `Core/Src/dev_SRM.c:16611: if (m_pgmEnv.SRM_Machine_State < SRM_MACHINE_MANUAL)	return;`
  - `Core/Src/dev_SRM.c:17162: if (m_pgmEnv.SRM_Machine_State < SRM_MACHINE_MANUAL)	return;`
  - `Core/Src/dev_SRM.c:17751: if (m_pgmEnv.SRM_Machine_State < SRM_MACHINE_MANUAL)	return;`
  - `Core/Src/dev_SRM.c:18398: if (m_pgmEnv.SRM_Machine_State < SRM_MACHINE_MANUAL)	return;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_MACHINE_STAND_BY_0

- **종류**: enum `enumSRM_MACHINE_STATE_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:63747: case SRM_MACHINE_STAND_BY_0:`
  - `Core/Inc/dev_SRM.h:1730: SRM_MACHINE_STAND_BY_0 = 40,`
  - `Core/Inc/dev_SRM.h:1756: SRM_MACHINE_STAND_BY_0,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_MACHINE_STAND_BY_1

- **종류**: enum `enumSRM_MACHINE_STATE_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:63750: case SRM_MACHINE_STAND_BY_1:`
  - `Core/Inc/dev_SRM.h:1731: SRM_MACHINE_STAND_BY_1 = 50,`
  - `Core/Inc/dev_SRM.h:1757: SRM_MACHINE_STAND_BY_1,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_MACHINE_ONLINE

- **종류**: enum `enumSRM_MACHINE_STATE_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:63753: case SRM_MACHINE_ONLINE:`
  - `Core/Inc/dev_SRM.h:1732: SRM_MACHINE_ONLINE = 60,`
  - `Core/Inc/dev_SRM.h:1758: SRM_MACHINE_ONLINE,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_MACHINE_SETUP

- **종류**: enum `enumSRM_MACHINE_STATE_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:63756: case SRM_MACHINE_SETUP:`
  - `Core/Inc/dev_SRM.h:1733: SRM_MACHINE_SETUP = 70,`
  - `Core/Inc/dev_SRM.h:1759: SRM_MACHINE_SETUP,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SRM_MACHINE_FAULT

- **종류**: enum `enumSRM_MACHINE_STATE_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:63616: m_pgmEnv.SRM_Machine_State = SRM_MACHINE_FAULT;`
  - `Core/Src/dev_SRM.c:63641: m_pgmEnv.SRM_Machine_State = SRM_MACHINE_FAULT;`
  - `Core/Src/dev_SRM.c:63709: m_pgmEnv.SRM_Machine_State = SRM_MACHINE_FAULT;`
  - `Core/Src/dev_SRM.c:63733: m_pgmEnv.SRM_Machine_State = SRM_MACHINE_FAULT;`
  - `Core/Src/dev_SRM.c:63759: case SRM_MACHINE_FAULT:`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### POS_FORK_1

- **종류**: enum `enumPOSITION_FORK_INDEX` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:10636: if (Is_Exist_Goods(POS_FORK_1))`
  - `Core/Src/dev_SRM.c:12085: if (Check_DSTx_Sensor(POS_FORK_1, FORK_MOVE_LEFT))`
  - `Core/Src/dev_SRM.c:12190: if (Check_DSTx_Sensor(POS_FORK_1, FORK_MOVE_RIGHT))`
  - `Core/Src/dev_SRM.c:13082: if (Check_DSTx_Sensor(POS_FORK_1, FORK_MOVE_LEFT))`
  - `Core/Src/dev_SRM.c:13187: if (Check_DSTx_Sensor(POS_FORK_1, FORK_MOVE_RIGHT))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### POS_FORK_2

- **종류**: enum `enumPOSITION_FORK_INDEX` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:44948: m_WorkData[m_WorkCnt].ForkDepth[POS_FORK_2] = Fork2Depth;`
  - `Core/Src/dev_SRM.c:45006: m_WorkData[m_WorkCnt].ForkDepth[POS_FORK_2] = Fork2Depth;`
  - `Core/Src/dev_SRM.c:45050: m_WorkData[m_WorkCnt].ForkDepth[POS_FORK_2] = Fork2Depth;`
  - `Core/Src/dev_SRM.c:45119: m_WorkData[m_WorkCnt].ForkDepth[POS_FORK_2] = Fork2Depth;`
  - `Core/Src/dev_SRM.c:47499: else if (nFeeding == POS_FORK_2)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MAX_FEED_COUNT

- **종류**: enum `enumPOSITION_FORK_INDEX` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1767: MAX_FEED_COUNT`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_MOVE_LEFT

- **종류**: enum `enumFORK_MOVE_DIR` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:12085: if (Check_DSTx_Sensor(POS_FORK_1, FORK_MOVE_LEFT))`
  - `Core/Src/dev_SRM.c:13082: if (Check_DSTx_Sensor(POS_FORK_1, FORK_MOVE_LEFT))`
  - `Core/Src/dev_SRM.c:14059: if (Check_DSTx_Sensor(POS_FORK_1, FORK_MOVE_LEFT))`
  - `Core/Src/dev_SRM.c:33395: if (Check_DSTx_Sensor(POS_FORK_1, FORK_MOVE_LEFT))`
  - `Core/Src/dev_SRM.c:57813: nDir = FORK_MOVE_LEFT;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_MOVE_RIGHT

- **종류**: enum `enumFORK_MOVE_DIR` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:12190: if (Check_DSTx_Sensor(POS_FORK_1, FORK_MOVE_RIGHT))`
  - `Core/Src/dev_SRM.c:13187: if (Check_DSTx_Sensor(POS_FORK_1, FORK_MOVE_RIGHT))`
  - `Core/Src/dev_SRM.c:14164: if (Check_DSTx_Sensor(POS_FORK_1, FORK_MOVE_RIGHT))`
  - `Core/Src/dev_SRM.c:33549: if (Check_DSTx_Sensor(POS_FORK_1, FORK_MOVE_RIGHT))`
  - `Core/Src/dev_SRM.c:57809: nDir = FORK_MOVE_RIGHT;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_MOVE_CENTER

- **종류**: enum `enumFORK_MOVE_DIR` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1773: FORK_MOVE_CENTER,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TRAV_NO_MOVEMNT

- **종류**: enum `enumTARVEL_MOVE_FLAG` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:48050: nDir = TRAV_NO_MOVEMNT;`
  - `Core/Src/dev_SRM.c:55298: if (m_WorkData[nWorkIdx].DrvData[INV_TRAVEL].Move_Dir != TRAV_NO_MOVEMNT)`
  - `Core/Src/dev_SRM.c:59221: if (m_WorkData[s_WorkInx].DrvData[INV_TRAVEL].Move_Dir != TRAV_NO_MOVEMNT)`
  - `Core/Src/dev_SRM.c:59268: if (m_WorkData[s_WorkInx].DrvData[INV_TRAVEL].Move_Dir != TRAV_NO_MOVEMNT)`
  - `Core/Inc/dev_SRM.h:1789: TRAV_NO_MOVEMNT = 0,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TRAV_MOVE_FORWARD

- **종류**: enum `enumTARVEL_MOVE_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:48041: nDir = TRAV_MOVE_FORWARD;`
  - `Core/Src/dev_SRM.c:55325: if (m_WorkData[nWorkIdx].DrvData[INV_TRAVEL].Move_Dir == TRAV_MOVE_FORWARD)`
  - `Core/Inc/dev_SRM.h:1790: TRAV_MOVE_FORWARD,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TRAV_MOVE_REVERSE

- **종류**: enum `enumTARVEL_MOVE_FLAG` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:48046: nDir = TRAV_MOVE_REVERSE;`
  - `Core/Src/dev_SRM.c:55469: else if (m_WorkData[nWorkIdx].DrvData[INV_TRAVEL].Move_Dir == TRAV_MOVE_REVERSE)`
  - `Core/Inc/dev_SRM.h:1791: TRAV_MOVE_REVERSE,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LIFT_NO_MOVEMNT

- **종류**: enum `enumLIFT_MOVE_FLAG` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:48072: nDir = LIFT_NO_MOVEMNT;`
  - `Core/Src/dev_SRM.c:55977: if (m_WorkData[nWorkIdx].DrvData[INV_HOIST].Move_Dir != LIFT_NO_MOVEMNT)`
  - `Core/Src/dev_SRM.c:59246: if (m_WorkData[s_WorkInx].DrvData[INV_HOIST].Move_Dir == LIFT_NO_MOVEMNT)`
  - `Core/Inc/dev_SRM.h:1795: LIFT_NO_MOVEMNT = 0,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

