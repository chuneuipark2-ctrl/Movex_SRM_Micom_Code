# Vol.07 — dev_SRM.c 함수 (1)

> 생성일: 2026-06-16 | MX SRM App Ver 4.4 | 소스 미수정

상태머신 함수.

---

### swap_16U

- **종류**: 함수
- **시그니처**: `INT16U swap_16U(INT16U val)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:124: INT16U swap_16U(INT16U val)`
  - `Core/Src/dev_SRM.c:189: ModbusTxPkt.TransactionID = swap_16U(ModbusTxPkt.TransactionID);`
  - `Core/Src/dev_SRM.c:190: ModbusTxPkt.ProtocolID = swap_16U(ModbusTxPkt.ProtocolID);`
  - `Core/Src/dev_SRM.c:191: ModbusTxPkt.Length = swap_16U(ModbusTxPkt.Length);`
  - `Core/Src/dev_SRM.c:192: ModbusTxPkt.FC03Send.ReferenceNumber = swap_16U(ModbusTxPkt.FC03Send.ReferenceNumber);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### swap_32U

- **종류**: 함수
- **시그니처**: `INT32U swap_32U(INT32U val)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:136: INT32U swap_32U(INT32U val)`
  - `Core/Src/dev_SRM.c:5851: m_SRM_TxPDO[i].CurPosition = swap_32U(m_Recv_TxPDO[i].CurPosition);`
  - `Core/Src/dev_SRM.c:5856: m_SRM_TxPDO[i].ErrorMainCode = swap_32U(m_Recv_TxPDO[i].ErrorMainCode);`
  - `Core/Src/dev_SRM.c:5860: m_SRM_TxPDO[i].Acutal_RefOffset = swap_32U(m_Recv_TxPDO[i].Acutal_RefOffset);`
  - `Core/Src/dev_SRM.c:5861: m_SRM_TxPDO[i].Acutal_PosGain = swap_32U(m_Recv_TxPDO[i].Acutal_PosGain);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ModbusTcpRead

- **종류**: 함수
- **시그니처**: `void ModbusTcpRead(INT08U nSocket, INT16U nUnitID, INT16U ref, INT16U cnt)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:168: void ModbusTcpRead(INT08U nSocket, INT16U nUnitID, INT16U ref, INT16U cnt)`
  - `Core/Src/dev_SRM.c:6259: ModbusTcpRead(TCP_SOCKET_HMI, HMI_UNIT_ID, HMI_ADDRESS_REALTIME, nReadWordCnt);`
  - `Core/Src/dev_SRM.c:6277: ModbusTcpRead(TCP_SOCKET_HMI, HMI_UNIT_ID, HMI_ADDRESS_SYS_TIME, nReadWordCnt);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ModbusTcpWrite

- **종류**: 함수
- **시그니처**: `void ModbusTcpWrite(INT08U nSocket, INT08U nUnitID, INT16U ref, INT16U cnt, INT16U* data)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:206: void ModbusTcpWrite(INT08U nSocket, INT08U nUnitID, INT16U ref, INT16U cnt, INT16U* data)`
  - `Core/Src/dev_SRM.c:6241: ModbusTcpWrite(TCP_SOCKET_HMI, HMI_UNIT_ID, nWriteAddress, nWriteWordCnt, (INT16U*)nWriteData);`
  - `Core/Src/dev_SRM.c:6303: ModbusTcpWrite(TCP_SOCKET_HMI, HMI_UNIT_ID, nWriteAddress, nWriteWordCnt, (INT16U*)&nWriteData);`
  - `Core/Src/dev_SRM.c:6361: ModbusTcpWrite(TCP_SOCKET_HMI, HMI_UNIT_ID, nWriteAddress, nWriteWordCnt, (INT16U*)nWriteData);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ModbusTcpWriteRead_1

- **종류**: 함수
- **시그니처**: `void ModbusTcpWriteRead_1(INT08U nSocket, INT16U read_ref, INT16U read_cnt, INT16U write_ref, INT16U write_cnt, INT16U* data)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:274: void ModbusTcpWriteRead_1(INT08U nSocket, INT16U read_ref, INT16U read_cnt, INT16U write_ref, INT16U`
  - `Core/Src/dev_SRM.c:6724: ModbusTcpWriteRead_1(0, 4, m_pgmEnv.Invertor_RxPDO_Size, 4,`
  - `Core/Src/dev_SRM.c:6778: ModbusTcpWriteRead_1(0, 0, m_pgmEnv.Invertor_RxPDO_Size, 0,`
  - `Core/Src/dev_SRM.c:6816: ModbusTcpWriteRead_1(0, 0, m_pgmEnv.Invertor_RxPDO_Size, 0,`
  - `Core/Src/dev_SRM.c:6872: ModbusTcpWriteRead_1(0, 0, m_pgmEnv.Invertor_RxPDO_Size, 0,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Store_SRM_RxPDO_queue

- **종류**: 함수
- **시그니처**: `void Store_SRM_RxPDO_queue(INT08U nInverter, INT16U control_word, INT32S position, UnitVelocitySTR* pVel)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: Store_*: 작업 큐/버퍼 적재. Save와 구분.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:541: void Store_SRM_RxPDO_queue(INT08U nInverter, INT16U control_word, INT32S position, UnitVelocitySTR* `
  - `Core/Src/dev_SRM.c:4935: Store_SRM_RxPDO_queue(inv, control_word1, 0, (UnitVelocitySTR*)pVel);`
  - `Core/Src/dev_SRM.c:4936: Store_SRM_RxPDO_queue(inv, control_word1, 0, (UnitVelocitySTR*)pVel);`
  - `Core/Src/dev_SRM.c:4937: Store_SRM_RxPDO_queue(inv, control_word1, 0, (UnitVelocitySTR*)pVel);`
  - `Core/Src/dev_SRM.c:4938: Store_SRM_RxPDO_queue(inv, control_word2, 0, (UnitVelocitySTR*)pVel);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Store_SRM_RxPDO_queue_1

- **종류**: 함수
- **시그니처**: `void Store_SRM_RxPDO_queue_1(MOVKIT_PO_TYPE_1* pPO)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: Store_*: 작업 큐/버퍼 적재. Save와 구분.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:627: void Store_SRM_RxPDO_queue_1(MOVKIT_PO_TYPE_1* pPO)`
  - `Core/Src/dev_SRM.c:4966: Store_SRM_RxPDO_queue_1(&nPO_Buf);`
  - `Core/Src/dev_SRM.c:4967: Store_SRM_RxPDO_queue_1(&nPO_Buf);`
  - `Core/Src/dev_SRM.c:4968: Store_SRM_RxPDO_queue_1(&nPO_Buf);`
  - `Core/Src/dev_SRM.c:4969: Store_SRM_RxPDO_queue_1(&nPO_Buf);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Store_SRM_RxPDO_queue_2

- **종류**: 함수
- **시그니처**: `void Store_SRM_RxPDO_queue_2(MOVKIT_PO_TYPE_2* pPO)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: Store_*: 작업 큐/버퍼 적재. Save와 구분.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:637: void Store_SRM_RxPDO_queue_2(MOVKIT_PO_TYPE_2* pPO)`
  - `Core/Src/dev_SRM.c:4973: Store_SRM_RxPDO_queue_2((MOVKIT_PO_TYPE_2*)&nPO_Buf);`
  - `Core/Src/dev_SRM.c:4974: Store_SRM_RxPDO_queue_2((MOVKIT_PO_TYPE_2*)&nPO_Buf);`
  - `Core/Src/dev_SRM.c:4975: Store_SRM_RxPDO_queue_2((MOVKIT_PO_TYPE_2*)&nPO_Buf);`
  - `Core/Src/dev_SRM.c:4976: Store_SRM_RxPDO_queue_2((MOVKIT_PO_TYPE_2*)&nPO_Buf);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Store_SRM_RxPDO_queue_3

- **종류**: 함수
- **시그니처**: `void Store_SRM_RxPDO_queue_3(MOVKIT_PO_TYPE_3* pPO)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: Store_*: 작업 큐/버퍼 적재. Save와 구분.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:647: void Store_SRM_RxPDO_queue_3(MOVKIT_PO_TYPE_3* pPO)`
  - `Core/Src/dev_SRM.c:4980: Store_SRM_RxPDO_queue_3((MOVKIT_PO_TYPE_3*)&nPO_Buf);`
  - `Core/Src/dev_SRM.c:4981: Store_SRM_RxPDO_queue_3((MOVKIT_PO_TYPE_3*)&nPO_Buf);`
  - `Core/Src/dev_SRM.c:4982: Store_SRM_RxPDO_queue_3((MOVKIT_PO_TYPE_3*)&nPO_Buf);`
  - `Core/Src/dev_SRM.c:4983: Store_SRM_RxPDO_queue_3((MOVKIT_PO_TYPE_3*)&nPO_Buf);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Store_SRM_RxPDO

- **종류**: 함수
- **시그니처**: `void Store_SRM_RxPDO(INT08U Inv, INT16U control_word, INT32S position, UnitVelocitySTR* pVel)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: Store_*: 작업 큐/버퍼 적재. Save와 구분.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:658: void Store_SRM_RxPDO(INT08U Inv, INT16U control_word, INT32S position, UnitVelocitySTR* pVel)`
  - `Core/Src/dev_SRM.c:2124: Store_SRM_RxPDO(INV_TRAVEL, nControlWord.W, position, &nCmdVelocity);`
  - `Core/Src/dev_SRM.c:2211: Store_SRM_RxPDO(INV_TRAVEL, nControlWord.W, position, &nVelocity);`
  - `Core/Src/dev_SRM.c:2294: Store_SRM_RxPDO(INV_TRAVEL, nControlWord.W, 0, &nVelocity);`
  - `Core/Src/dev_SRM.c:2331: Store_SRM_RxPDO(INV_TRAVEL, nControlWord.W, 0, &nVelocity);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Store_SRM_RxPDO_1

- **종류**: 함수
- **시그니처**: `void Store_SRM_RxPDO_1(INT08U Inv, INT16U nMode, INT16U control_word, INT32S position, UnitVelocitySTR* pVel)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: Store_*: 작업 큐/버퍼 적재. Save와 구분.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:744: void Store_SRM_RxPDO_1(INT08U Inv, INT16U nMode, INT16U control_word, INT32S position, UnitVelocityS`
  - `Core/Src/dev_SRM.c:44493: Store_SRM_RxPDO_1(INV_TRAVEL, OP_MODE_NONE, nControlWord.W, 0, &DefaultTravVelocity);`
  - `Core/Src/dev_SRM.c:44494: Store_SRM_RxPDO_1(INV_HOIST, OP_MODE_NONE, nControlWord.W, 0, &DefaultLiftVelocity);`
  - `Core/Src/dev_SRM.c:44495: Store_SRM_RxPDO_1(INV_FORK_1, OP_MODE_NONE, nControlWord.W, 0, &DefaultForkVelocity);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Store_SRM_RxPDO_2

- **종류**: 함수
- **시그니처**: `void Store_SRM_RxPDO_2(INT08U Inv, INT16U nMode, INT16U control_word, INT32S position, UnitVelocitySTR* pVel)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: Store_*: 작업 큐/버퍼 적재. Save와 구분.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:862: void Store_SRM_RxPDO_2(INT08U Inv, INT16U nMode, INT16U control_word, INT32S position, UnitVelocityS`
  - `Core/Src/dev_SRM.c:2132: Store_SRM_RxPDO_2(INV_TRAVEL, OP_MODE_ABSOLUTE_POS, nControlWord_1.W, position, &nCmdVelocity);`
  - `Core/Src/dev_SRM.c:2140: Store_SRM_RxPDO_2(INV_TRAVEL, OP_MODE_ABSOLUTE_POS, nControlWord_2.W, position, &nCmdVelocity);`
  - `Core/Src/dev_SRM.c:2148: Store_SRM_RxPDO_2(INV_TRAVEL, OP_MODE_ABSOLUTE_POS, nControlWord_1.W, position, &nCmdVelocity);`
  - `Core/Src/dev_SRM.c:2219: Store_SRM_RxPDO_2(INV_TRAVEL, OP_MODE_ABSOLUTE_POS, nControlWord_1.W, position, &nVelocity);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Store_SRM_Fork_RxPDO

- **종류**: 함수
- **시그니처**: `void Store_SRM_Fork_RxPDO(INT16U control_word, INT16S nCmdVelocity)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: Store_*: 작업 큐/버퍼 적재. Save와 구분.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:1071: void Store_SRM_Fork_RxPDO(INT16U control_word, INT16S nCmdVelocity)`
  - `Core/Src/dev_SRM.c:2890: Store_SRM_Fork_RxPDO(nControlWord.W, nCmdVelocity);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Store_ReadParam_RxPDO_queue

- **종류**: 함수
- **시그니처**: `void Store_ReadParam_RxPDO_queue(INT08U Inv, INT08U nReadFlag, INT16U MainIndex, INT16U Subndex)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: Store_*: 작업 큐/버퍼 적재. Save와 구분.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:1081: void Store_ReadParam_RxPDO_queue(INT08U Inv, INT08U nReadFlag, INT16U MainIndex, INT16U Subndex)`
  - `Core/Src/dev_SRM.c:37319: Store_ReadParam_RxPDO_queue((m_pgmEnv.InvParamCtr.rData.Drive - 1), 1, nParam_Main, nParam_Sub);`
  - `Core/Src/dev_SRM.c:37353: Store_ReadParam_RxPDO_queue(i, 1, nParam_Main, nParam_Sub);`
  - `Core/Src/dev_SRM.c:37409: Store_ReadParam_RxPDO_queue(i, 0, nParam_Main, nParam_Sub);`
  - `Core/Src/dev_SRM.c:37445: Store_ReadParam_RxPDO_queue(nInvertor_ID, 0, 0, 0);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Store_WriteParam_RxPDO_queue

- **종류**: 함수
- **시그니처**: `void Store_WriteParam_RxPDO_queue(INT08U Inv, INT08U nWriteFlag, INT16U MainIndex, INT16U Subndex, INT32S nData)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: Store_*: 작업 큐/버퍼 적재. Save와 구분.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:1094: void Store_WriteParam_RxPDO_queue(INT08U Inv, INT08U nWriteFlag, INT16U MainIndex, INT16U Subndex, I`
  - `Core/Src/dev_SRM.c:37335: Store_WriteParam_RxPDO_queue((m_pgmEnv.InvParamCtr.wData.Drive - 1), 1, nParam_Main, nParam_Sub, \`
  - `Core/Src/dev_SRM.c:37521: Store_WriteParam_RxPDO_queue(nInvertor_ID, 0, nParam_Main, nParam_Sub, 0);`
  - `Core/Src/dev_SRM.c:37549: Store_WriteParam_RxPDO_queue(nInvertor_ID, 0, nParam_Main, nParam_Sub, 0);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Store_InvParam_RxPDO_Queue

- **종류**: 함수
- **시그니처**: `void Store_InvParam_RxPDO_Queue(INT08U Inv, INT08U nSet, INT32S nRefOffset, INT32U nPosGain, INT08U nPosWindow)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: Store_*: 작업 큐/버퍼 적재. Save와 구분.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:1109: void Store_InvParam_RxPDO_Queue(INT08U Inv, INT08U nSet, INT32S nRefOffset, INT32U nPosGain, INT08U `
  - `Core/Src/dev_SRM.c:44305: Store_InvParam_RxPDO_Queue(INV_TRAVEL, m_ExtSEnv2.TravDrive.InvParam.UseFlag, \`
  - `Core/Src/dev_SRM.c:44310: Store_InvParam_RxPDO_Queue(INV_HOIST, m_ExtSEnv2.LiftDrive.InvParam.UseFlag, \`
  - `Core/Src/dev_SRM.c:44315: Store_InvParam_RxPDO_Queue(INV_FORK_1, m_ExtSEnv2.ForkDrive.InvParam.UseFlag, \`
  - `Core/Src/dev_SRM.c:58372: Store_InvParam_RxPDO_Queue(INV_TRAVEL, 1, m_ExtSEnv2.TravDrive.InvParam.RefOffset, \`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Get_Motor_Brake_Release

- **종류**: 함수
- **시그니처**: `INT08U Get_Motor_Brake_Release(INT08U Inverter)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:1125: INT08U Get_Motor_Brake_Release(INT08U Inverter)`
  - `Core/Src/dev_SRM.c:4409: if (Get_Motor_Brake_Release(INV_TRAVEL))`
  - `Core/Src/dev_SRM.c:4479: if (Get_Motor_Brake_Release(INV_HOIST))`
  - `Core/Src/dev_SRM.c:5490: m_pgmEnv.GraphData[GRAPH_8] = Get_Motor_Brake_Release(nInvertor) * 100;`
  - `Core/Src/dev_SRM.c:5654: m_pgmEnv.GraphData[GRAPH_8] = Get_Motor_Brake_Release(nInvertor) * 100;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Get_Inverter_Referenced_State

- **종류**: 함수
- **시그니처**: `INT08U Get_Inverter_Referenced_State(INT08U nInv)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: 인버터/EtherCAT 상태. m_ExtSEnv와 함께 확인.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:1423: INT08U Get_Inverter_Referenced_State(INT08U nInv)`
  - `Core/Src/dev_SRM.c:2060: if (Get_Inverter_Referenced_State(INV_TRAVEL) == 0)		return M_CTR_ERROR_IPOS_REF;`
  - `Core/Src/dev_SRM.c:2173: if (Get_Inverter_Referenced_State(INV_TRAVEL) == 0)		return M_CTR_ERROR_IPOS_REF;`
  - `Core/Src/dev_SRM.c:2475: if (Get_Inverter_Referenced_State(INV_HOIST) == 0)		return M_CTR_ERROR_IPOS_REF;`
  - `Core/Src/dev_SRM.c:2596: if (Get_Inverter_Referenced_State(INV_HOIST) == 0)		return M_CTR_ERROR_IPOS_REF;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Get_Inverter_Ready_State

- **종류**: 함수
- **시그니처**: `INT08U Get_Inverter_Ready_State(INT08U nInv)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: 인버터/EtherCAT 상태. m_ExtSEnv와 함께 확인.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:1484: INT08U Get_Inverter_Ready_State(INT08U nInv)`
  - `Core/Src/dev_SRM.c:2059: if (Get_Inverter_Ready_State(INV_TRAVEL) == 0)	return M_CTR_ERROR_NOT_READY;`
  - `Core/Src/dev_SRM.c:2172: if (Get_Inverter_Ready_State(INV_TRAVEL) == 0)			return M_CTR_ERROR_NOT_READY;`
  - `Core/Src/dev_SRM.c:2263: if (Get_Inverter_Ready_State(INV_TRAVEL) == 0)	return M_CTR_ERROR_NOT_READY;`
  - `Core/Src/dev_SRM.c:2474: if (Get_Inverter_Ready_State(INV_HOIST) == 0)			return M_CTR_ERROR_NOT_READY;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Get_Inverter_Fault_State

- **종류**: 함수
- **시그니처**: `INT08U Get_Inverter_Fault_State(INT08U nInv)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: 인버터/EtherCAT 상태. m_ExtSEnv와 함께 확인.
- **코드 참조 예**:
  - `Core/Src/alarm.c:421: if (Get_Inverter_Fault_State(INV_TRAVEL))`
  - `Core/Src/alarm.c:429: else if (Get_Inverter_Fault_State(INV_HOIST))`
  - `Core/Src/alarm.c:437: else if (Get_Inverter_Fault_State(INV_FORK_1))`
  - `Core/Src/alarm.c:449: if (Get_Inverter_Fault_State(i))`
  - `Core/Src/dev_SRM.c:1546: INT08U Get_Inverter_Fault_State(INT08U nInv)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Get_Inverter_Motor_Turning

- **종류**: 함수
- **시그니처**: `INT08U Get_Inverter_Motor_Turning(INT08U nInverter)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: 인버터/EtherCAT 상태. m_ExtSEnv와 함께 확인.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:1657: INT08U Get_Inverter_Motor_Turning(INT08U nInverter)`
  - `Core/Src/dev_SRM.c:4412: if (Get_Inverter_Motor_Turning(INV_TRAVEL))`
  - `Core/Src/dev_SRM.c:4482: if (Get_Inverter_Motor_Turning(INV_HOIST))`
  - `Core/Src/dev_SRM.c:9810: m_St.Inv_St[INV_FORK_1].Status1.MoveFlag = Get_Inverter_Motor_Turning(INV_FORK_1);`
  - `Core/Src/dev_SRM.c:14778: if (Get_Inverter_Motor_Turning(INV_TRAVEL))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Get_Inverter_MainError

- **종류**: 함수
- **시그니처**: `INT16U Get_Inverter_MainError(INT08U nInverter)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: 인버터/EtherCAT 상태. m_ExtSEnv와 함께 확인.
- **코드 참조 예**:
  - `Core/Src/alarm.c:425: m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr.MainCode = Get_Inverter_MainError(INV_TRAVEL);`
  - `Core/Src/alarm.c:433: m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr.MainCode = Get_Inverter_MainError(INV_HOIST);`
  - `Core/Src/alarm.c:441: m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr.MainCode = Get_Inverter_MainError(INV_FORK_1);`
  - `Core/Src/alarm.c:451: m_St.InvErrorCode.Inverter[i].MainError = Get_Inverter_MainError(i);`
  - `Core/Src/dev_SRM.c:1714: INT16U Get_Inverter_MainError(INT08U nInverter)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Get_Inverter_SubError

- **종류**: 함수
- **시그니처**: `INT16U Get_Inverter_SubError(INT08U nInverter)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: 인버터/EtherCAT 상태. m_ExtSEnv와 함께 확인.
- **코드 참조 예**:
  - `Core/Src/alarm.c:426: m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr.SubCode = Get_Inverter_SubError(INV_TRAVEL);`
  - `Core/Src/alarm.c:434: m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr.SubCode = Get_Inverter_SubError(INV_HOIST);`
  - `Core/Src/alarm.c:442: m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr.SubCode = Get_Inverter_SubError(INV_FORK_1);`
  - `Core/Src/alarm.c:452: m_St.InvErrorCode.Inverter[i].SubError = Get_Inverter_SubError(i);`
  - `Core/Src/dev_SRM.c:1771: INT16U Get_Inverter_SubError(INT08U nInverter)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Get_Inverter_FbError

- **종류**: 함수
- **시그니처**: `INT16U Get_Inverter_FbError(INT08U nInverter)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: 인버터/EtherCAT 상태. m_ExtSEnv와 함께 확인.
- **코드 참조 예**:
  - `Core/Src/alarm.c:427: m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr.FBCode = Get_Inverter_FbError(INV_TRAVEL);`
  - `Core/Src/alarm.c:435: m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr.FBCode = Get_Inverter_FbError(INV_HOIST);`
  - `Core/Src/alarm.c:443: m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr.FBCode = Get_Inverter_FbError(INV_FORK_1);`
  - `Core/Src/dev_SRM.c:1828: INT16U Get_Inverter_FbError(INT08U nInverter)`
  - `Core/Inc/dev_SRM.h:19: INT16U Get_Inverter_FbError(INT08U nInverter);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Get_Inverter_STO_State

- **종류**: 함수
- **시그니처**: `INT08U Get_Inverter_STO_State(INT08U nInverter)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: 인버터/EtherCAT 상태. m_ExtSEnv와 함께 확인.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:1854: INT08U Get_Inverter_STO_State(INT08U nInverter)`
  - `Core/Src/dev_SRM.c:44661: if (Get_Inverter_STO_State(INV_HOIST))`
  - `Core/Src/dev_SRM.c:44666: if (Get_Inverter_STO_State(INV_TRAVEL))`
  - `Core/Src/dev_SRM.c:44671: if (Get_Inverter_STO_State(INV_FORK_1))`
  - `Core/Src/dev_SRM.c:44835: if (Get_Inverter_STO_State(INV_HOIST))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

