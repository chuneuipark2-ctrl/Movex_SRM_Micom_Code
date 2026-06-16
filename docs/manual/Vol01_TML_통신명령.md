# Vol.01 — TML TY_*

> 생성일: 2026-06-16 | MX SRM App Ver 4.4 | 소스 미수정

com_tml.c 수신 분기.

---

### TY_DEVICE_STATUS

- **종류**: `#define` 상수
- **값**: `0x10`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ÀåÄ¡ »óÅÂ ¿ä±¸
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6344: case TY_DEVICE_STATUS: rxDeviceStatusReq(port, (TMLComPTR)pCom);      break;`
  - `Core/Src/com_tml.c:6429: case TY_DEVICE_STATUS: rxDeviceStatusReq(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:23: #define TY_DEVICE_STATUS              0x10      // ÀåÄ¡ »óÅÂ ¿ä±¸`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_DEVICE_CONTROL

- **종류**: `#define` 상수
- **값**: `0x11`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ÀåÄ¡ Á¦¾î ¸í·É
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6345: case TY_DEVICE_CONTROL: rxDeviceControlReq(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:24: #define TY_DEVICE_CONTROL             0x11      // ÀåÄ¡ Á¦¾î ¸í·É`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_TEST_STATUS

- **종류**: `#define` 상수
- **값**: `0x12`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: Request Test Status
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6346: case TY_TEST_STATUS: rxTestStatusReq(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:26: #define TY_TEST_STATUS					0x12      // Request Test Status`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_TEST_CONTROL

- **종류**: `#define` 상수
- **값**: `0x13`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: Control Test Status
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6347: case TY_TEST_CONTROL: rxTestControlReq(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:27: #define TY_TEST_CONTROL					0x13      // Control Test Status`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_FUNC_CONTROL

- **종류**: `#define` 상수
- **값**: `0x14`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: Control Function Command
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6355: case TY_FUNC_CONTROL: rxFuncControlReq(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:28: #define TY_FUNC_CONTROL					0x14      // Control Function Command`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_GRAPH_REQUEST

- **종류**: `#define` 상수
- **값**: `0x15`
- **정의 위치**: `Core/Inc/com_tml.h`
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6348: case TY_GRAPH_REQUEST: rxGraphRequest(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:30: #define TY_GRAPH_REQUEST				0x15`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_MANUNAL_OUTPUT_CONTROL

- **종류**: `#define` 상수
- **값**: `0x16`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: Manual Output Control
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6349: case TY_MANUNAL_OUTPUT_CONTROL: rxManualOutCTR_Request(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:32: #define TY_MANUNAL_OUTPUT_CONTROL		0x16      // Manual Output Control`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_DOWNLOAD_START

- **종류**: `#define` 상수
- **값**: `0x20`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ´Ù¿î·Îµå ½ÃÀÛ
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6351: case TY_DOWNLOAD_START: rxDownloadStart(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:34: #define TY_DOWNLOAD_START				0x20      // ´Ù¿î·Îµå ½ÃÀÛ`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_DOWNLOAD_DATA

- **종류**: `#define` 상수
- **값**: `0x21`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ´Ù¿î·Îµå Data
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6352: case TY_DOWNLOAD_DATA: rxDownloadData(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:35: #define TY_DOWNLOAD_DATA				0x21      // ´Ù¿î·Îµå Data`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_DOWNLOAD_END

- **종류**: `#define` 상수
- **값**: `0x22`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ´Ù¿î·Îµå ¿Ï·á
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6353: case TY_DOWNLOAD_END: rxDownloadFinish(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:36: #define TY_DOWNLOAD_END					0x22      // ´Ù¿î·Îµå ¿Ï·á`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_DIO_FORM_REQ

- **종류**: `#define` 상수
- **값**: `0x23`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: DIO Çü»óÁ¤º¸ Á¶È¸
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6357: case TY_DIO_FORM_REQ: rxDigital_IO_Form_Req(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:38: #define TY_DIO_FORM_REQ					0x23      // DIO Çü»óÁ¤º¸ Á¶È¸`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_DIO_FORM_CONTROL

- **종류**: `#define` 상수
- **값**: `0x24`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: DIO Çü»óÁ¤º¸ ¼³Á¤
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6358: case TY_DIO_FORM_CONTROL: rxDigital_IO_Form_Control(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:39: #define TY_DIO_FORM_CONTROL				0x24      // DIO Çü»óÁ¤º¸ ¼³Á¤`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_MACHINE_SPEC_STATUS

- **종류**: `#define` 상수
- **값**: `0x25`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ±â°è»ç¾ç »óÅÂ ¿ä±¸
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6360: case TY_MACHINE_SPEC_STATUS: rxMachine_Type_Req(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:41: #define TY_MACHINE_SPEC_STATUS			0x25      // ±â°è»ç¾ç »óÅÂ ¿ä±¸`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_MACHINE_SPEC_CONTROL

- **종류**: `#define` 상수
- **값**: `0x26`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ±â°è»ç¾ç ¼³Á¤ ¸í·É
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6361: case TY_MACHINE_SPEC_CONTROL: rxMachine_Type_Set(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:42: #define TY_MACHINE_SPEC_CONTROL			0x26      // ±â°è»ç¾ç ¼³Á¤ ¸í·É`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_STATUS_REQ

- **종류**: `#define` 상수
- **값**: `0x30`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: »óÅÂ¿ä±¸
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6257: case TY_STATUS_REQ:`
  - `Core/Inc/com_tml.h:44: #define TY_STATUS_REQ					0x30      // »óÅÂ¿ä±¸`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_OPERATION_INFO_REQ

- **종류**: `#define` 상수
- **값**: `0x31`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ¿îÇàÁ¤º¸ ¿ä±¸
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6271: case TY_OPERATION_INFO_REQ: rxOperationInfo_Req(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:45: #define TY_OPERATION_INFO_REQ			0x31      // ¿îÇàÁ¤º¸ ¿ä±¸`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_INVERTOR_INFO_REQ

- **종류**: `#define` 상수
- **값**: `0x32`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ÀÎ¹öÅÍ »óÅÂ Á¦¾î
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6273: case TY_INVERTOR_INFO_REQ: rxInvertorInfo_Req(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:46: #define TY_INVERTOR_INFO_REQ			0x32      // ÀÎ¹öÅÍ »óÅÂ Á¦¾î`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_ALARMLOG_REQUEST

- **종류**: `#define` 상수
- **값**: `0x34`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ¾Ë¶÷·Î±× Á¶È¸
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6268: case TY_ALARMLOG_REQUEST: rxAlarmLogRequest(port, (TMLComPTR)pCom);      break;`
  - `Core/Src/com_tml.c:6402: case TY_ALARMLOG_REQUEST: rxAlarmLogRequest(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:48: #define TY_ALARMLOG_REQUEST           0x34      // ¾Ë¶÷·Î±× Á¶È¸`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_ALARMLOG_DELETE

- **종류**: `#define` 상수
- **값**: `0x35`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ¾Ë¶÷·Î±× »èÁ¦
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6269: case TY_ALARMLOG_DELETE: rxAlarmLogDelete(port, (TMLComPTR)pCom);      break;`
  - `Core/Src/com_tml.c:6403: case TY_ALARMLOG_DELETE: rxAlarmLogDelete(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:49: #define TY_ALARMLOG_DELETE            0x35      // ¾Ë¶÷·Î±× »èÁ¦`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_CMD_TASK_ORDER

- **종류**: `#define` 상수
- **값**: `0x40`
- **정의 위치**: `Core/Inc/com_tml.h`
- **용도(읽는 법)**: Task: TML 0x40 다중작업. 0x41과 분기 다름. TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6275: case TY_CMD_TASK_ORDER: rxTaskCmdOrder(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:51: #define TY_CMD_TASK_ORDER			0x40		//`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_CMD_ORDER

- **종류**: `#define` 상수
- **값**: `0x41`
- **정의 위치**: `Core/Inc/com_tml.h`
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6277: case TY_CMD_ORDER: rxCmdOrder(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:53: #define TY_CMD_ORDER				0x41		//`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_CMD_REFERENCE

- **종류**: `#define` 상수
- **값**: `0x44`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: Invertor Reference Setup
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6279: case TY_CMD_REFERENCE: rxCmdReferenceSearch(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:55: #define TY_CMD_REFERENCE			0x44		// Invertor Reference Setup`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_CMD_START

- **종류**: `#define` 상수
- **값**: `0x50`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ½ÃÀÛ¸í·É
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6281: case TY_CMD_START: rxCmdStart(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:57: #define TY_CMD_START				0x50		// ½ÃÀÛ¸í·É`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_CMD_MOVE_HOME

- **종류**: `#define` 상수
- **값**: `0x51`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: È¨À§Ä¡ ÀÌµ¿
- **용도(읽는 법)**: HOME/RETURN: 원점복귀 vs 에러복귀 RunMode 혼재. grep으로 확인. TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6282: case TY_CMD_MOVE_HOME: rxCmd_MoveHome(port, (TMLComPTR)pCom); break;`
  - `Core/Inc/com_tml.h:58: #define TY_CMD_MOVE_HOME			0x51		// È¨À§Ä¡ ÀÌµ¿`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_CMD_ERROR_RESET

- **종류**: `#define` 상수
- **값**: `0x52`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ÀÌ»ó¸®¼Â¸í·É
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6285: case TY_CMD_ERROR_RESET: rxCmdErrorReset(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:59: #define TY_CMD_ERROR_RESET			0x52		// ÀÌ»ó¸®¼Â¸í·É`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_CMD_ORDER_DELETE

- **종류**: `#define` 상수
- **값**: `0x53`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ÀÛ¾÷»èÁ¦¸í·É
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6286: case TY_CMD_ORDER_DELETE: rxCmdOrderDelete(port, (TMLComPTR)pCom);	break;`
  - `Core/Inc/com_tml.h:60: #define TY_CMD_ORDER_DELETE			0x53		// ÀÛ¾÷»èÁ¦¸í·É`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_NORMAL_STOP_REQ

- **종류**: `#define` 상수
- **값**: `0x54`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: Á¤Áö, ½ÃÀÛ OFF
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6288: case TY_NORMAL_STOP_REQ: rxCmdNormalStop(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:61: #define TY_NORMAL_STOP_REQ			0x54		// Á¤Áö, ½ÃÀÛ OFF`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_EMERGENCY_STOP_REQ

- **종류**: `#define` 상수
- **값**: `0x55`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ºñ»óÁ¤Áö
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6290: case TY_EMERGENCY_STOP_REQ: rxCmdEmergencyStop(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:62: #define TY_EMERGENCY_STOP_REQ		0x55		// ºñ»óÁ¤Áö`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_MODE_CHANGE

- **종류**: `#define` 상수
- **값**: `0x58`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ÀåÄ¡ ¸ðµå º¯°æ
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6292: case TY_MODE_CHANGE: rxModeChange(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:63: #define TY_MODE_CHANGE				0x58		// ÀåÄ¡ ¸ðµå º¯°æ`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_CMD_MOVE_MAINTANENCE

- **종류**: `#define` 상수
- **값**: `0x59`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: º¸¼ö À§Ä¡ ÀÌµ¿
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6283: case TY_CMD_MOVE_MAINTANENCE: rxCmdMoveMaintanence(port, (TMLComPTR)pCom); break;`
  - `Core/Inc/com_tml.h:64: #define TY_CMD_MOVE_MAINTANENCE		0x59		// º¸¼ö À§Ä¡ ÀÌµ¿`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_CMD_DEMO_CONTROL

- **종류**: `#define` 상수
- **값**: `0x60`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: µ¥¸ð ¿îÀü Á¦¾î
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6398: case TY_CMD_DEMO_CONTROL:	rxDemoControl(port, (TMLComPTR)pCom);	break;`
  - `Core/Inc/com_tml.h:66: #define TY_CMD_DEMO_CONTROL			0x60		// µ¥¸ð ¿îÀü Á¦¾î`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_CMD_SCAN_POSITION_SENSOR

- **종류**: `#define` 상수
- **값**: `0x61`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: À§Ä¡ ¼¾¼­ ½ºÄµ
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6400: case TY_CMD_SCAN_POSITION_SENSOR: rxScan_Position_Sensor_Control(port, (TMLComPTR)pCom); break;`
  - `Core/Inc/com_tml.h:68: #define TY_CMD_SCAN_POSITION_SENSOR	0x61		// À§Ä¡ ¼¾¼­ ½ºÄµ`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_CMD_MANUAL

- **종류**: `#define` 상수
- **값**: `0x80`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: Manual Control
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6294: case TY_CMD_MANUAL:	rxCmdManual(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:70: #define TY_CMD_MANUAL				0x80		// Manual Control`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_INVERTOR_PARAM_REQ

- **종류**: `#define` 상수
- **값**: `0x90`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ÆÄ¶ó¹ÌÅÍ ÁÖ¼Ò°ª Á¢±Ù Á¶È¸
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6296: case TY_INVERTOR_PARAM_REQ: rxInvertorParameterReq(port, (TMLComPTR)pCom);      break;`
  - `Core/Src/com_tml.c:6363: case TY_INVERTOR_PARAM_REQ: rxInvertorParameterReq(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:72: #define TY_INVERTOR_PARAM_REQ		0x90		// ÆÄ¶ó¹ÌÅÍ ÁÖ¼Ò°ª Á¢±Ù Á¶È¸`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_INVERTOR_PARAM_SET

- **종류**: `#define` 상수
- **값**: `0x91`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ÆÄ¶ó¹ÌÅÍ ÁÖ¼Ò°ª Á¢±Ù º¯°æ
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6297: case TY_INVERTOR_PARAM_SET: rxInvertorParameterSet(port, (TMLComPTR)pCom);      break;`
  - `Core/Src/com_tml.c:6364: case TY_INVERTOR_PARAM_SET: rxInvertorParameterSet(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:73: #define TY_INVERTOR_PARAM_SET		0x91		// ÆÄ¶ó¹ÌÅÍ ÁÖ¼Ò°ª Á¢±Ù º¯°æ`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_NOT_DEF_PROCOTOL

- **종류**: `#define` 상수
- **값**: `0x92`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ·¢ ¼³Á¤ Á¶È¸. 23. 8. 21 »èÁ¦
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Inc/com_tml.h:75: #define TY_NOT_DEF_PROCOTOL			0x92		// ·¢ ¼³Á¤ Á¶È¸. 23. 8. 21 »èÁ¦`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_NOT_DEF_PROTOCOL1

- **종류**: `#define` 상수
- **값**: `0x93`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ·¢ ¼³Á¤ º¯°æ. 23. 8. 21 »èÁ¦
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Inc/com_tml.h:76: #define TY_NOT_DEF_PROTOCOL1		0x93		// ·¢ ¼³Á¤ º¯°æ. 23. 8. 21 »èÁ¦`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_CELL_ENV_REQ

- **종류**: `#define` 상수
- **값**: `0x94`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ¼¿ ¼³Á¤ Á¶È¸
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6302: case TY_CELL_ENV_REQ: rxCellEnvReq(port, (TMLComPTR)pCom);      break;`
  - `Core/Src/com_tml.c:6369: case TY_CELL_ENV_REQ: rxCellEnvReq(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:78: #define TY_CELL_ENV_REQ				0x94		// ¼¿ ¼³Á¤ Á¶È¸`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_CELL_ENV_SET

- **종류**: `#define` 상수
- **값**: `0x95`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ¼¿ ¼³Á¤ ¹ø°æ
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6303: case TY_CELL_ENV_SET: rxCellEnvSet(port, (TMLComPTR)pCom);      break;`
  - `Core/Src/com_tml.c:6370: case TY_CELL_ENV_SET: rxCellEnvSet(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:79: #define TY_CELL_ENV_SET				0x95		// ¼¿ ¼³Á¤ ¹ø°æ`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_CELL_OFFSET_ENV_REQ

- **종류**: `#define` 상수
- **값**: `0x96`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ¼¿¿ÀÇÁ¼Â ¼³Á¤ Á¶È¸
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6305: case TY_CELL_OFFSET_ENV_REQ: rxCell_Offset_EnvReq(port, (TMLComPTR)pCom);      break;`
  - `Core/Src/com_tml.c:6372: case TY_CELL_OFFSET_ENV_REQ: rxCell_Offset_EnvReq(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:80: #define TY_CELL_OFFSET_ENV_REQ		0x96		// ¼¿¿ÀÇÁ¼Â ¼³Á¤ Á¶È¸`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_CELL_OFFSET_ENV_SET

- **종류**: `#define` 상수
- **값**: `0x97`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ¼¿¿ÀÇÁ¼Â ¼³Á¤ º¯°æ
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6306: case TY_CELL_OFFSET_ENV_SET: rxCell_Offset_EnvSet(port, (TMLComPTR)pCom);      break;`
  - `Core/Src/com_tml.c:6373: case TY_CELL_OFFSET_ENV_SET: rxCell_Offset_EnvSet(port, (TMLComPTR)pCom);      break;`
  - `Core/Inc/com_tml.h:81: #define TY_CELL_OFFSET_ENV_SET		0x97		// ¼¿¿ÀÇÁ¼Â ¼³Á¤ º¯°æ`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_STATION_ENV_REQ

- **종류**: `#define` 상수
- **값**: `0x98`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ½ºÅ×ÀÌ¼Ç ¼³Á¤ Á¶È¸
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6308: case TY_STATION_ENV_REQ: rxStationEnvReq(port, (TMLComPTR)pCom); break;`
  - `Core/Src/com_tml.c:6375: case TY_STATION_ENV_REQ: rxStationEnvReq(port, (TMLComPTR)pCom); break;`
  - `Core/Inc/com_tml.h:82: #define TY_STATION_ENV_REQ			0x98		// ½ºÅ×ÀÌ¼Ç ¼³Á¤ Á¶È¸`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_STATION_ENV_SET

- **종류**: `#define` 상수
- **값**: `0x99`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ½ºÅ×ÀÌ¼Ç ¼³Á¤ º¯°æ
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6309: case TY_STATION_ENV_SET: rxStationEnvSet(port, (TMLComPTR)pCom); break;`
  - `Core/Src/com_tml.c:6376: case TY_STATION_ENV_SET: rxStationEnvSet(port, (TMLComPTR)pCom); break;`
  - `Core/Inc/com_tml.h:83: #define TY_STATION_ENV_SET			0x99		// ½ºÅ×ÀÌ¼Ç ¼³Á¤ º¯°æ`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_PROHIBIT_RACK_ENV_REQ

- **종류**: `#define` 상수
- **값**: `0x9C`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ±ÝÁö·¢ ¼³Á¤ Á¶È¸
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6311: case TY_PROHIBIT_RACK_ENV_REQ: rxProhibitRackEnvReq(port, (TMLComPTR)pCom); break;`
  - `Core/Src/com_tml.c:6378: case TY_PROHIBIT_RACK_ENV_REQ: rxProhibitRackEnvReq(port, (TMLComPTR)pCom); break;`
  - `Core/Inc/com_tml.h:88: #define TY_PROHIBIT_RACK_ENV_REQ	0x9C		// ±ÝÁö·¢ ¼³Á¤ Á¶È¸`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_PROHIBIT_RACK_ENV_SET

- **종류**: `#define` 상수
- **값**: `0x9D`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ±ÝÁö·¢ ¼³Á¤ º¯°æ
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6312: case TY_PROHIBIT_RACK_ENV_SET: rxProhibitRackEnvSet(port, (TMLComPTR)pCom); break;`
  - `Core/Src/com_tml.c:6379: case TY_PROHIBIT_RACK_ENV_SET: rxProhibitRackEnvSet(port, (TMLComPTR)pCom); break;`
  - `Core/Inc/com_tml.h:89: #define TY_PROHIBIT_RACK_ENV_SET	0x9D		// ±ÝÁö·¢ ¼³Á¤ º¯°æ`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_SPECIAL_RACK_ENV_REQ

- **종류**: `#define` 상수
- **값**: `0x9E`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ½ºÆä¼È·¢ ¼³Á¤ Á¶È¸
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6314: case TY_SPECIAL_RACK_ENV_REQ: rxSpecialRackEnvReq(port, (TMLComPTR)pCom); break;`
  - `Core/Src/com_tml.c:6381: case TY_SPECIAL_RACK_ENV_REQ: rxSpecialRackEnvReq(port, (TMLComPTR)pCom); break;`
  - `Core/Inc/com_tml.h:90: #define TY_SPECIAL_RACK_ENV_REQ		0x9E		// ½ºÆä¼È·¢ ¼³Á¤ Á¶È¸`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_SPECIAL_RACK_ENV_SET

- **종류**: `#define` 상수
- **값**: `0x9F`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ½ºÆä¼È·¢ ¼³Á¤ º¯°æ
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6315: case TY_SPECIAL_RACK_ENV_SET: rxSpecialRackEnvSet(port, (TMLComPTR)pCom); break;`
  - `Core/Src/com_tml.c:6382: case TY_SPECIAL_RACK_ENV_SET: rxSpecialRackEnvSet(port, (TMLComPTR)pCom); break;`
  - `Core/Inc/com_tml.h:91: #define TY_SPECIAL_RACK_ENV_SET		0x9F		// ½ºÆä¼È·¢ ¼³Á¤ º¯°æ`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_SETUP_INITIALIZE_SET

- **종류**: `#define` 상수
- **값**: `0xA0`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ¼³Á¤ ÃÊ±âÈ­
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6317: case TY_SETUP_INITIALIZE_SET: rxRackEnvInitializeSet(port, (TMLComPTR)pCom); break;`
  - `Core/Src/com_tml.c:6384: case TY_SETUP_INITIALIZE_SET: rxRackEnvInitializeSet(port, (TMLComPTR)pCom); break;`
  - `Core/Inc/com_tml.h:93: #define TY_SETUP_INITIALIZE_SET			0xA0		// ¼³Á¤ ÃÊ±âÈ­`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_CONTROL_REQ

- **종류**: `#define` 상수
- **값**: `0xA1`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: Á¦¾î ¼³Á¤ Á¶È¸
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6319: case TY_CONTROL_REQ: rxControlParamterReq(port, (TMLComPTR)pCom); break;`
  - `Core/Src/com_tml.c:6386: case TY_CONTROL_REQ: rxControlParamterReq(port, (TMLComPTR)pCom); break;`
  - `Core/Inc/com_tml.h:95: #define TY_CONTROL_REQ				0xA1		// Á¦¾î ¼³Á¤ Á¶È¸`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_CONTROL_SET

- **종류**: `#define` 상수
- **값**: `0xA2`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: Á¦¾î ¼³Á¤ º¯°æ
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6320: case TY_CONTROL_SET: rxControlParamterSet(port, (TMLComPTR)pCom); break;`
  - `Core/Src/com_tml.c:6387: case TY_CONTROL_SET: rxControlParamterSet(port, (TMLComPTR)pCom); break;`
  - `Core/Inc/com_tml.h:96: #define TY_CONTROL_SET				0xA2		// Á¦¾î ¼³Á¤ º¯°æ`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_TRAVEL_DRIVE_REQ

- **종류**: `#define` 상수
- **값**: `0xA3`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ÁÖÇà µå¶óÀÌºê ¼³Á¤ Á¶È¸
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6322: case TY_TRAVEL_DRIVE_REQ: rxTravelDriveParamterReq(port, (TMLComPTR)pCom); break;`
  - `Core/Src/com_tml.c:6389: case TY_TRAVEL_DRIVE_REQ: rxTravelDriveParamterReq(port, (TMLComPTR)pCom); break;`
  - `Core/Inc/com_tml.h:97: #define TY_TRAVEL_DRIVE_REQ			0xA3		// ÁÖÇà µå¶óÀÌºê ¼³Á¤ Á¶È¸`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_TRAVEL_DRIVE_SET

- **종류**: `#define` 상수
- **값**: `0xA4`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ÁÖÇà µå¶óÀÌºê ¼³Á¤ º¯°æ
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6323: case TY_TRAVEL_DRIVE_SET: rxTravelDriveParamterSet(port, (TMLComPTR)pCom); break;`
  - `Core/Src/com_tml.c:6390: case TY_TRAVEL_DRIVE_SET: rxTravelDriveParamterSet(port, (TMLComPTR)pCom); break;`
  - `Core/Inc/com_tml.h:98: #define TY_TRAVEL_DRIVE_SET			0xA4		// ÁÖÇà µå¶óÀÌºê ¼³Á¤ º¯°æ`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_LIFT_DRIVE_REQ

- **종류**: `#define` 상수
- **값**: `0xA5`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ½Â°­ µå¶óÀÌºê ¼³Á¤ Á¶È¸
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6325: case TY_LIFT_DRIVE_REQ: rxLiftDriveParamterReq(port, (TMLComPTR)pCom); break;`
  - `Core/Src/com_tml.c:6392: case TY_LIFT_DRIVE_REQ: rxLiftDriveParamterReq(port, (TMLComPTR)pCom); break;`
  - `Core/Inc/com_tml.h:99: #define TY_LIFT_DRIVE_REQ			0xA5		// ½Â°­ µå¶óÀÌºê ¼³Á¤ Á¶È¸`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_LIFT_DRIVE_SET

- **종류**: `#define` 상수
- **값**: `0xA6`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ½Â°­ µå¶óÀÌºê ¼³Á¤ º¯°æ
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6326: case TY_LIFT_DRIVE_SET: rxLiftDriveParamterSet(port, (TMLComPTR)pCom); break;`
  - `Core/Src/com_tml.c:6393: case TY_LIFT_DRIVE_SET: rxLiftDriveParamterSet(port, (TMLComPTR)pCom); break;`
  - `Core/Inc/com_tml.h:100: #define TY_LIFT_DRIVE_SET			0xA6		// ½Â°­ µå¶óÀÌºê ¼³Á¤ º¯°æ`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_FORK_DRIVE_REQ

- **종류**: `#define` 상수
- **값**: `0xA7`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: Æ÷Å© µå¶óÀÌºê ¼³Á¤ Á¶È¸
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6328: case TY_FORK_DRIVE_REQ: rx_Fork_Drive_Paramter_Req(port, (TMLComPTR)pCom); break;`
  - `Core/Src/com_tml.c:6395: case TY_FORK_DRIVE_REQ: rx_Fork_Drive_Paramter_Req(port, (TMLComPTR)pCom); break;`
  - `Core/Inc/com_tml.h:101: #define TY_FORK_DRIVE_REQ			0xA7		// Æ÷Å© µå¶óÀÌºê ¼³Á¤ Á¶È¸`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_FORK_DRIVE_SET

- **종류**: `#define` 상수
- **값**: `0xA8`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: Æ÷Å© µå¶óÀÌºê ¼³Á¤ º¯°æ
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6329: case TY_FORK_DRIVE_SET: rx_Fork_Drive_Paramter_Set(port, (TMLComPTR)pCom); break;`
  - `Core/Src/com_tml.c:6396: case TY_FORK_DRIVE_SET: rx_Fork_Drive_Paramter_Set(port, (TMLComPTR)pCom); break;`
  - `Core/Inc/com_tml.h:102: #define TY_FORK_DRIVE_SET			0xA8		// Æ÷Å© µå¶óÀÌºê ¼³Á¤ º¯°æ`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_PARA_VELOCITY_REQ

- **종류**: `#define` 상수
- **값**: `0xA9`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ¼Óµµ ¼³Á¤ Á¶È¸
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Inc/com_tml.h:104: #define TY_PARA_VELOCITY_REQ		0xA9		// ¼Óµµ ¼³Á¤ Á¶È¸`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_PARA_VELOCITY_SET

- **종류**: `#define` 상수
- **값**: `0xAA`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: ¼Óµµ ¼³Á¤ º¯°æ
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Inc/com_tml.h:105: #define TY_PARA_VELOCITY_SET		0xAA		// ¼Óµµ ¼³Á¤ º¯°æ`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_MCU_TEST

- **종류**: `#define` 상수
- **값**: `0xBF`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: MCU Test
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:6405: case TY_MCU_TEST: rxMcuTestReq(port, (TMLComPTR)pCom);	break;`
  - `Core/Src/com_tml.c:6431: case TY_MCU_TEST: rxMcuTestReq(port, (TMLComPTR)pCom);	break;`
  - `Core/Inc/com_tml.h:107: #define TY_MCU_TEST					0xBF		// MCU Test`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_DSP_STATUS

- **종류**: `#define` 상수
- **값**: `0xC0`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: Display Board »óÅÂ Á¶È¸
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_dsp.c:56: nComData.Header.Cmd2 = TY_DSP_STATUS;`
  - `Core/Src/com_tml.c:6421: case TY_DSP_STATUS: rxDSP_Status(port, (TMLComPTR)pCom);	break;`
  - `Core/Inc/com_tml.h:109: #define TY_DSP_STATUS				0xC0		// Display Board »óÅÂ Á¶È¸`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_DSP_DATA

- **종류**: `#define` 상수
- **값**: `0xC2`
- **정의 위치**: `Core/Inc/com_tml.h`
- **원문 주석**: Display Board Á¦¾î
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Src/com_dsp.c:97: nComData.Header.Cmd2 = TY_DSP_DATA;`
  - `Core/Src/com_tml.c:6422: case TY_DSP_DATA: rxDSP_Control(port, (TMLComPTR)pCom);	break;`
  - `Core/Inc/com_tml.h:110: #define TY_DSP_DATA					0xC2		// Display Board Á¦¾î`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_READ_GROUP_LIST

- **종류**: `#define` 상수
- **값**: `0xD0`
- **정의 위치**: `Core/Inc/com_tml.h`
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Inc/com_tml.h:112: #define TY_READ_GROUP_LIST			0xD0      //`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_READ_PARAM_LIST

- **종류**: `#define` 상수
- **값**: `0xD1`
- **정의 위치**: `Core/Inc/com_tml.h`
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Inc/com_tml.h:113: #define TY_READ_PARAM_LIST			0xD1      //`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_READ_PARAM_INFO

- **종류**: `#define` 상수
- **값**: `0xD2`
- **정의 위치**: `Core/Inc/com_tml.h`
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Inc/com_tml.h:115: #define TY_READ_PARAM_INFO			0xD2      //`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TY_WRITE_PARAM_SET

- **종류**: `#define` 상수
- **값**: `0xD3`
- **정의 위치**: `Core/Inc/com_tml.h`
- **용도(읽는 법)**: TML Vexi 타입: com_tml.c rxDataAnalysis 분기.
- **코드 참조 예**:
  - `Core/Inc/com_tml.h:116: #define TY_WRITE_PARAM_SET			0xD3      //`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

