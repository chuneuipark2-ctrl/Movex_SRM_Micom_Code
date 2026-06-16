# Vol.07 — dev_SRM.c 함수 (3)

> 생성일: 2026-06-16 | MX SRM App Ver 4.4 | 소스 미수정

상태머신 함수.

---

### control_miniloder_level_adjust

- **종류**: 함수
- **시그니처**: `void control_miniloder_level_adjust(void) { if (m_pgmEnv.SRM_RunMode == RUN_SEQ_STAND_BY)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:5150: void control_miniloder_level_adjust(void)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### InitTcpIpStackNetworkInfo

- **종류**: 함수
- **시그니처**: `static void InitTcpIpStackNetworkInfo(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:5163: static void InitTcpIpStackNetworkInfo(void)`
  - `Core/Src/dev_SRM.c:67966: InitTcpIpStackNetworkInfo();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Modbus_TxPDO_Update

- **종류**: 함수
- **시그니처**: `void Modbus_TxPDO_Update(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:5190: void Modbus_TxPDO_Update(void)`
  - `Core/Src/dev_SRM.c:6430: Modbus_TxPDO_Update();`
  - `Core/Src/dev_SRM.c:6458: Modbus_TxPDO_Update();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Modbus_TxPDO_Update_1

- **종류**: 함수
- **시그니처**: `void Modbus_TxPDO_Update_1(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:5352: void Modbus_TxPDO_Update_1(void)`
  - `Core/Src/dev_SRM.c:6478: Modbus_TxPDO_Update_1();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Modbus_TxPDO_Update_2

- **종류**: 함수
- **시그니처**: `void Modbus_TxPDO_Update_2(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:5506: void Modbus_TxPDO_Update_2(void)`
  - `Core/Src/dev_SRM.c:6498: Modbus_TxPDO_Update_2();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Modbus_TxPDO_Update_3

- **종류**: 함수
- **시그니처**: `void Modbus_TxPDO_Update_3(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:5672: void Modbus_TxPDO_Update_3(void)`
  - `Core/Src/dev_SRM.c:6519: Modbus_TxPDO_Update_3();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### BE2LE_ModbusTxPDO

- **종류**: 함수
- **시그니처**: `void BE2LE_ModbusTxPDO(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:5846: void BE2LE_ModbusTxPDO(void)`
  - `Core/Src/dev_SRM.c:6429: BE2LE_ModbusTxPDO();`
  - `Core/Src/dev_SRM.c:6457: BE2LE_ModbusTxPDO();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### BE2LE_ModbusTxPDO_1

- **종류**: 함수
- **시그니처**: `void BE2LE_ModbusTxPDO_1(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:5866: void BE2LE_ModbusTxPDO_1(void)`
  - `Core/Src/dev_SRM.c:6477: BE2LE_ModbusTxPDO_1();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### BE2LE_ModbusTxPDO_2

- **종류**: 함수
- **시그니처**: `void BE2LE_ModbusTxPDO_2(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:5898: void BE2LE_ModbusTxPDO_2(void)`
  - `Core/Src/dev_SRM.c:6497: BE2LE_ModbusTxPDO_2();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### BE2LE_ModbusTxPDO_3

- **종류**: 함수
- **시그니처**: `void BE2LE_ModbusTxPDO_3(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:5929: void BE2LE_ModbusTxPDO_3(void)`
  - `Core/Src/dev_SRM.c:6518: BE2LE_ModbusTxPDO_3();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### BE2LE_HMI_TxPDO

- **종류**: 함수
- **시그니처**: `void BE2LE_HMI_TxPDO(INT16U* pData, INT16U nWordCnt)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:5960: void BE2LE_HMI_TxPDO(INT16U* pData, INT16U nWordCnt)`
  - `Core/Src/dev_SRM.c:6605: BE2LE_HMI_TxPDO((INT16U*)&nRecvDataBuf, (ModbusRxPkt.FC03Resp.ByteCount >> 1));`
  - `Core/Inc/dev_SRM.h:56: void BE2LE_HMI_TxPDO(INT16U* pData, INT16U nData_Cnt);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LE2BE_Modbus_RxPDO

- **종류**: 함수
- **시그니처**: `void LE2BE_Modbus_RxPDO(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6002: void LE2BE_Modbus_RxPDO(void)`
  - `Core/Src/dev_SRM.c:6723: LE2BE_Modbus_RxPDO();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LE2BE_Modbus_RxPDO_1

- **종류**: 함수
- **시그니처**: `void LE2BE_Modbus_RxPDO_1()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6033: void LE2BE_Modbus_RxPDO_1()`
  - `Core/Src/dev_SRM.c:6777: LE2BE_Modbus_RxPDO_1();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LE2BE_Modbus_RxPDO_2

- **종류**: 함수
- **시그니처**: `void LE2BE_Modbus_RxPDO_2()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6097: void LE2BE_Modbus_RxPDO_2()`
  - `Core/Src/dev_SRM.c:6815: LE2BE_Modbus_RxPDO_2();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LE2BE_Modbus_RxPDO_3

- **종류**: 함수
- **시그니처**: `void LE2BE_Modbus_RxPDO_3()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6158: void LE2BE_Modbus_RxPDO_3()`
  - `Core/Src/dev_SRM.c:6871: LE2BE_Modbus_RxPDO_3();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HMI_Write_RealTime_Register

- **종류**: 함수
- **시그니처**: `void HMI_Write_RealTime_Register(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6221: void HMI_Write_RealTime_Register(void)`
  - `Core/Src/dev_SRM.c:65515: HMI_Write_RealTime_Register();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HMI_Read_RealTime_Register

- **종류**: 함수
- **시그니처**: `void HMI_Read_RealTime_Register(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6248: void HMI_Read_RealTime_Register(void)`
  - `Core/Src/dev_SRM.c:65485: HMI_Read_RealTime_Register();`
  - `Core/Src/dev_SRM.c:65549: HMI_Read_RealTime_Register();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HMI_Read_SystemTime_Register

- **종류**: 함수
- **시그니처**: `void HMI_Read_SystemTime_Register(void)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6266: void HMI_Read_SystemTime_Register(void)`
  - `Core/Src/dev_SRM.c:65705: HMI_Read_SystemTime_Register();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HMI_Write_RealTime_MW1

- **종류**: 함수
- **시그니처**: `void HMI_Write_RealTime_MW1(INT16U nData)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6284: void HMI_Write_RealTime_MW1(INT16U nData)`
  - `Core/Src/dev_SRM.c:65590: HMI_Write_RealTime_MW1(0);`
  - `Core/Inc/dev_SRM.h:57: void HMI_Write_RealTime_MW1(INT16U nData);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HMI_Write_SystemTime_Register

- **종류**: 함수
- **시그니처**: `void HMI_Write_SystemTime_Register(INT08U nFlag)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6306: void HMI_Write_SystemTime_Register(INT08U nFlag)`
  - `Core/Src/dev_SRM.c:65641: HMI_Write_SystemTime_Register(1);`
  - `Core/Src/dev_SRM.c:65673: HMI_Write_SystemTime_Register(0);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RxModbusTcpData

- **종류**: 함수
- **시그니처**: `void RxModbusTcpData(INT08U nSocket, INT08U* data, INT16U len)`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_udp.c:602: RxModbusTcpData(1, s_AssemBuf, frame_total);`
  - `Core/Src/dev_SRM.c:6364: void RxModbusTcpData(INT08U nSocket, INT08U* data, INT16U len)`
  - `Core/Src/fpgatcpipstack.c:438: RxModbusTcpData(i, (INT08U*)&EthData[EthHdrLen + hdrlen], len);`
  - `Core/Inc/dev_SRM.h:58: void RxModbusTcpData(INT08U nSocket, INT08U* data, INT16U len);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ModbusTCP_Com_SEW_Ver1_Proc

- **종류**: 함수
- **시그니처**: `void ModbusTCP_Com_SEW_Ver1_Proc()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6673: void ModbusTCP_Com_SEW_Ver1_Proc()`
  - `Core/Src/dev_SRM.c:6886: ModbusTCP_Com_SEW_Ver1_Proc();`
  - `Core/Src/dev_SRM.c:6915: ModbusTCP_Com_SEW_Ver1_Proc();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ModbusTCP_Com_SEW_Ver2_Proc1

- **종류**: 함수
- **시그니처**: `void ModbusTCP_Com_SEW_Ver2_Proc1()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6729: void ModbusTCP_Com_SEW_Ver2_Proc1()`
  - `Core/Src/dev_SRM.c:6890: ModbusTCP_Com_SEW_Ver2_Proc1();`
  - `Core/Src/dev_SRM.c:6928: ModbusTCP_Com_SEW_Ver2_Proc1();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ModbusTCP_Com_SEW_Ver2_Proc2

- **종류**: 함수
- **시그니처**: `void ModbusTCP_Com_SEW_Ver2_Proc2()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6782: void ModbusTCP_Com_SEW_Ver2_Proc2()`
  - `Core/Src/dev_SRM.c:6894: ModbusTCP_Com_SEW_Ver2_Proc2();`
  - `Core/Src/dev_SRM.c:6941: ModbusTCP_Com_SEW_Ver2_Proc2();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ModbusTCP_Com_SEW_Ver2_Proc3

- **종류**: 함수
- **시그니처**: `void ModbusTCP_Com_SEW_Ver2_Proc3()`
- **정의 위치**: `Core/Src/dev_SRM.c`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6820: void ModbusTCP_Com_SEW_Ver2_Proc3()`
  - `Core/Src/dev_SRM.c:6898: ModbusTCP_Com_SEW_Ver2_Proc3();`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

