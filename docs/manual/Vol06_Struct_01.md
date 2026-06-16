# Vol.06 — 구조체 멤버 (1)

> 생성일: 2026-06-16 | MX SRM App Ver 4.4 | 소스 미수정

m_St 등 필드.

---

### SafetyPlugOn

- **종류**: 구조체 멤버
- **소속 구조체**: `ControlPanelStatusBit`
- **선언**: `INT08U SafetyPlugOn`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit0, 0: On, 1: Off
- **용도(읽는 법)**: 헤더 주석: Bit0, 0: On, 1: Off
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2350: if (m_St.CP_State.Bit.SafetyPlugOn)`
  - `Core/Src/dev_SRM.c:30789: if (m_St.CP_State.Bit.SafetyPlugOn || m_St.CP_State.Bit.EmergencyStop)`
  - `Core/Src/dev_SRM.c:31906: if (m_St.CP_State.Bit.SafetyPlugOn || m_St.CP_State.Bit.EmergencyStop)`
  - `Core/Src/dev_SRM.c:33184: if (m_St.CP_State.Bit.SafetyPlugOn || m_St.CP_State.Bit.EmergencyStop)`
  - `Core/Src/dev_SRM.c:34287: if (m_St.CP_State.Bit.SafetyPlugOn || m_St.CP_State.Bit.EmergencyStop)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### EmergencyStop

- **종류**: 구조체 멤버
- **소속 구조체**: `ControlPanelStatusBit`
- **선언**: `INT08U EmergencyStop`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit1, 0: Switch Off, 1: Switch On
- **용도(읽는 법)**: 헤더 주석: Bit1, 0: Switch Off, 1: Switch On
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:30789: if (m_St.CP_State.Bit.SafetyPlugOn || m_St.CP_State.Bit.EmergencyStop)`
  - `Core/Src/dev_SRM.c:30808: if (m_St.CP_State.Bit.EmergencyStop)`
  - `Core/Src/dev_SRM.c:31906: if (m_St.CP_State.Bit.SafetyPlugOn || m_St.CP_State.Bit.EmergencyStop)`
  - `Core/Src/dev_SRM.c:31924: if (m_St.CP_State.Bit.EmergencyStop)`
  - `Core/Src/dev_SRM.c:33184: if (m_St.CP_State.Bit.SafetyPlugOn || m_St.CP_State.Bit.EmergencyStop)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FaultReset

- **종류**: 구조체 멤버
- **소속 구조체**: `ControlPanelStatusBit`
- **선언**: `INT08U FaultReset`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit2, 0: Switch Off, 1: Switch On
- **용도(읽는 법)**: 헤더 주석: Bit2, 0: Switch Off, 1: Switch On
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:43556: nRxPDO.ControlWord.B.FaultReset = 1;`
  - `Core/Src/dev_SRM.c:43572: nRxPDO.ControlWord.B.FaultReset = 0;`
  - `Core/Src/dev_SRM.c:44469: nRxPDO.ControlWord.B.FaultReset = 1;`
  - `Core/Src/dev_SRM.c:44524: nRxPDO.ControlWord.B.FaultReset = 0;`
  - `Core/Src/dev_SRM.c:52262: nCurResetSwitch = m_pgmEnv.Recv_CP_State.Bit.FaultReset;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HeartBit

- **종류**: 구조체 멤버
- **소속 구조체**: `ControlPanelStatusBit`
- **선언**: `INT08U HeartBit`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit3, HeartBit
- **용도(읽는 법)**: 헤더 주석: Bit3, HeartBit
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2106: m_St.CP_State.Bit.HeartBit = pCmd->CP_State.Bit.HeartBit;`
  - `Core/Inc/User_Define.h:615: INT08U HeartBit : 1;		// Bit3, HeartBit`
  - `Core/Inc/dev_SRM.h:116: INT16U HeartBit : 1;				// Bit7,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HostCom

- **종류**: 구조체 멤버
- **소속 구조체**: `ControlPanelStatusBit`
- **선언**: `INT08U HostCom`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit4,
- **용도(읽는 법)**: 헤더 주석: Bit4,
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:64190: if (m_St.CP_State.Bit.HostCom == 1)`
  - `Core/Src/dev_SRM.c:68164: m_St.CP_State.Bit.HostCom = 0;`
  - `Core/Src/dev_SRM.c:68171: Set_TestStatus(DEBUG_STR_47, m_St.CP_State.Bit.HostCom);`
  - `Core/Inc/User_Define.h:616: INT08U HostCom : 1;			// Bit4,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Reserved2

- **종류**: 구조체 멤버
- **소속 구조체**: `ControlPanelStatusBit`
- **선언**: `INT08U Reserved2`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit5,
- **용도(읽는 법)**: 헤더 주석: Bit5,
- **코드 참조 예**:
  - `Core/Src/fpga.c:63: INT08U  Reserved2[7];      // 0x9 ~ 0xF`
  - `Core/Src/fpga.c:73: INT08U  Reserved2[4];         // 0x04 ~ 0x07`
  - `Core/Src/fpga.c:98: INT08U  Reserved2[4];         // 0x04 ~ 0x07`
  - `Core/Inc/User_Define.h:544: INT08U				Reserved2[32];`
  - `Core/Inc/User_Define.h:583: INT08U				Reserved2[30];`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Reserved3

- **종류**: 구조체 멤버
- **소속 구조체**: `ControlPanelStatusBit`
- **선언**: `INT08U Reserved3`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit6,
- **용도(읽는 법)**: 헤더 주석: Bit6,
- **코드 참조 예**:
  - `Core/Src/fpga.c:75: INT08U  Reserved3[4];         // 0x0C ~ 0x0F`
  - `Core/Src/fpga.c:100: INT08U  Reserved3[4];         // 0x0C ~ 0x0F`
  - `Core/Inc/User_Define.h:552: INT08U				Reserved3[10];`
  - `Core/Inc/User_Define.h:618: INT08U Reserved3 : 1;		// Bit6,`
  - `Core/Inc/User_Define.h:643: INT08U Reserved3 : 1;		// Bit7,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Reserved4

- **종류**: 구조체 멤버
- **소속 구조체**: `ControlPanelStatusBit`
- **선언**: `INT08U Reserved4`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit7,
- **용도(읽는 법)**: 헤더 주석: Bit7,
- **코드 참조 예**:
  - `Core/Src/fpga.c:76: INT08U  Reserved4[0x10];      // 0x10 ~ 0x1F`
  - `Core/Src/fpga.c:101: INT08U  Reserved4[0x10];      // 0x10 ~ 0x1F`
  - `Core/Inc/User_Define.h:559: INT08U				Reserved4[29];`
  - `Core/Inc/User_Define.h:619: INT08U Reserved4 : 1;		// Bit7,`
  - `Core/Inc/User_Define.h:686: INT08U Reserved4 : 1;	// Bit4,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Auto

- **종류**: 구조체 멤버
- **소속 구조체**: `DeviceModeBit`
- **선언**: `INT08U Auto`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit0,
- **용도(읽는 법)**: 헤더 주석: Bit0,
- **코드 참조 예**:
  - `Core/Src/alarm.c:490: if (m_St.SRM_Mode.Bit.Auto)`
  - `Core/Src/alarm.c:511: if (m_St.SRM_Mode.Bit.Auto)`
  - `Core/Src/alarm.c:1039: else if (m_St.SRM_Mode.Bit.Auto)`
  - `Core/Src/alarm.c:1134: else if (m_St.SRM_Mode.Bit.Auto)`
  - `Core/Src/alarm.c:1261: else if (m_St.SRM_Mode.Bit.Auto)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Manual

- **종류**: 구조체 멤버
- **소속 구조체**: `DeviceModeBit`
- **선언**: `INT08U Manual`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit1,
- **용도(읽는 법)**: 헤더 주석: Bit1,
- **코드 참조 예**:
  - `Core/Src/alarm.c:1035: if (m_St.SRM_Mode.Bit.Manual)`
  - `Core/Src/alarm.c:1106: if (m_St.SRM_Mode.Bit.Manual)`
  - `Core/Src/alarm.c:1220: if (m_St.SRM_Mode.Bit.Manual)`
  - `Core/Src/com_tml.c:2721: if ((m_St.SRM_Mode.Bit.Manual == 1)`
  - `Core/Src/dev_SRM.c:9587: if ((m_St.SRM_Mode.Bit.Manual == 1) || (m_St.SRM_Mode.Bit.Auto == 1))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Force

- **종류**: 구조체 멤버
- **소속 구조체**: `DeviceModeBit`
- **선언**: `INT08U Force`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit2,
- **용도(읽는 법)**: 헤더 주석: Bit2,
- **코드 참조 예**:
  - `Core/Src/alarm.c:1117: if (m_St.SRM_Mode.Bit.Force)`
  - `Core/Src/alarm.c:1224: if (m_St.SRM_Mode.Bit.Force)`
  - `Core/Src/alarm.c:1243: if (m_St.SRM_Mode.Bit.Force)`
  - `Core/Src/alarm.c:1438: if (m_St.SRM_Mode.Bit.Force)`
  - `Core/Src/alarm.c:1440: m_St.SRM_Mode.Bit.Force = 0;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Setup

- **종류**: 구조체 멤버
- **소속 구조체**: `DeviceModeBit`
- **선언**: `INT08U Setup`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit3,
- **용도(읽는 법)**: 헤더 주석: Bit3,
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:431: printf("[DEBUG_APP] Machine_Type Setting Empty. Write Default Setup.\n\r");`
  - `Core/Src/alarm.c:1055: else if (m_St.SRM_Mode.Bit.Setup)`
  - `Core/Src/alarm.c:1162: else if (m_St.SRM_Mode.Bit.Setup)`
  - `Core/Src/alarm.c:1291: else if (m_St.SRM_Mode.Bit.Setup)`
  - `Core/Src/com_tml.c:590: if (!m_St.SRM_Mode.Bit.Setup)	return;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Reserved0

- **종류**: 구조체 멤버
- **소속 구조체**: `DeviceModeBit`
- **선언**: `INT08U Reserved0`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit4,
- **용도(읽는 법)**: 헤더 주석: Bit4,
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:640: INT08U Reserved0 : 1;		// Bit4,`
  - `Core/Inc/User_Define.h:735: INT08U Reserved0 : 1;	// Bit7,`
  - `Core/Inc/User_Define.h:787: INT08U Reserved0 : 1;		// Bit5,`
  - `Core/Inc/User_Define.h:948: INT08U				Reserved0;`
  - `Core/Inc/User_Define.h:1014: INT08U				Reserved0[2];`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Reserved1

- **종류**: 구조체 멤버
- **소속 구조체**: `DeviceModeBit`
- **선언**: `INT08U Reserved1`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit5,
- **용도(읽는 법)**: 헤더 주석: Bit5,
- **코드 참조 예**:
  - `Core/Src/fpga.c:70: INT08U  Reserved1[2];         // 0x00 ~ 0x01`
  - `Core/Src/fpga.c:95: INT08U  Reserved1[2];         // 0x00 ~ 0x01`
  - `Core/Inc/User_Define.h:532: INT08U				Reserved1;`
  - `Core/Inc/User_Define.h:641: INT08U Reserved1 : 1;		// Bit5,`
  - `Core/Inc/User_Define.h:665: INT08U Reserved1 : 1;		// Bit6,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Reserved2

- **종류**: 구조체 멤버
- **소속 구조체**: `DeviceModeBit`
- **선언**: `INT08U Reserved2`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit6,
- **용도(읽는 법)**: 헤더 주석: Bit6,
- **코드 참조 예**:
  - `Core/Src/fpga.c:63: INT08U  Reserved2[7];      // 0x9 ~ 0xF`
  - `Core/Src/fpga.c:73: INT08U  Reserved2[4];         // 0x04 ~ 0x07`
  - `Core/Src/fpga.c:98: INT08U  Reserved2[4];         // 0x04 ~ 0x07`
  - `Core/Inc/User_Define.h:544: INT08U				Reserved2[32];`
  - `Core/Inc/User_Define.h:583: INT08U				Reserved2[30];`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Reserved3

- **종류**: 구조체 멤버
- **소속 구조체**: `DeviceModeBit`
- **선언**: `INT08U Reserved3`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit7,
- **용도(읽는 법)**: 헤더 주석: Bit7,
- **코드 참조 예**:
  - `Core/Src/fpga.c:75: INT08U  Reserved3[4];         // 0x0C ~ 0x0F`
  - `Core/Src/fpga.c:100: INT08U  Reserved3[4];         // 0x0C ~ 0x0F`
  - `Core/Inc/User_Define.h:552: INT08U				Reserved3[10];`
  - `Core/Inc/User_Define.h:618: INT08U Reserved3 : 1;		// Bit6,`
  - `Core/Inc/User_Define.h:643: INT08U Reserved3 : 1;		// Bit7,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### StartOn

- **종류**: 구조체 멤버
- **소속 구조체**: `DeviceStatus1Bit`
- **선언**: `INT08U StartOn`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit0,
- **용도(읽는 법)**: 헤더 주석: Bit0,
- **코드 참조 예**:
  - `Core/Src/alarm.c:1041: if (m_St.SRM_Status1.Bit.StartOn)`
  - `Core/Src/alarm.c:1136: if (m_St.SRM_Status1.Bit.StartOn)`
  - `Core/Src/alarm.c:1263: if (m_St.SRM_Status1.Bit.StartOn)`
  - `Core/Src/alarm.c:1626: if ((m_St.SRM_Mode.Bit.Auto == 1) && (m_St.SRM_Status1.Bit.StartOn == 1))`
  - `Core/Src/com_tml.c:2234: else if (!(m_St.SRM_Status1.Bit.StartOn))  // 시작On이 아니면`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### EmergencyStop

- **종류**: 구조체 멤버
- **소속 구조체**: `DeviceStatus1Bit`
- **선언**: `INT08U EmergencyStop`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit1,
- **용도(읽는 법)**: 헤더 주석: Bit1,
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:30789: if (m_St.CP_State.Bit.SafetyPlugOn || m_St.CP_State.Bit.EmergencyStop)`
  - `Core/Src/dev_SRM.c:30808: if (m_St.CP_State.Bit.EmergencyStop)`
  - `Core/Src/dev_SRM.c:31906: if (m_St.CP_State.Bit.SafetyPlugOn || m_St.CP_State.Bit.EmergencyStop)`
  - `Core/Src/dev_SRM.c:31924: if (m_St.CP_State.Bit.EmergencyStop)`
  - `Core/Src/dev_SRM.c:33184: if (m_St.CP_State.Bit.SafetyPlugOn || m_St.CP_State.Bit.EmergencyStop)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Warning

- **종류**: 구조체 멤버
- **소속 구조체**: `DeviceStatus1Bit`
- **선언**: `INT08U Warning`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit2,
- **용도(읽는 법)**: 헤더 주석: Bit2,
- **코드 참조 예**:
  - `Core/Src/alarm.c:496: m_St.SRM_Status1.Bit.Warning = 0;`
  - `Core/Src/alarm.c:529: m_St.SRM_Status1.Bit.Warning = 1;`
  - `Core/Src/alarm.c:1704: if (m_St.SRM_Status1.Bit.Warning)`
  - `Core/Src/com_dsp.c:194: if (m_St.SRM_Status1.Bit.Warning)`
  - `Core/Src/dev_SRM.c:1564: || m_SRM_PI_Type_1.Travel.StatusWord.B.Warning)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Fault

- **종류**: 구조체 멤버
- **소속 구조체**: `DeviceStatus1Bit`
- **선언**: `INT08U Fault`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit3,
- **용도(읽는 법)**: 헤더 주석: Bit3,
- **코드 참조 예**:
  - `Core/Src/alarm.c:488: if (!m_St.SRM_Status1.Bit.Fault)`
  - `Core/Src/alarm.c:495: m_St.SRM_Status1.Bit.Fault = 1;`
  - `Core/Src/alarm.c:516: m_St.SRM_Status1.Bit.Fault = 1;`
  - `Core/Src/alarm.c:527: if (m_St.SRM_Status1.Bit.Fault == 0)`
  - `Core/Src/alarm.c:828: if (m_St.SRM_Status1.Bit.Fault)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### InvertorConnect

- **종류**: 구조체 멤버
- **소속 구조체**: `DeviceStatus1Bit`
- **선언**: `INT08U InvertorConnect`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit4,
- **용도(읽는 법)**: 헤더 주석: Bit4,
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6450: m_St.SRM_Status1.Bit.InvertorConnect = 1;`
  - `Core/Src/dev_SRM.c:6470: m_St.SRM_Status1.Bit.InvertorConnect = 1;`
  - `Core/Src/dev_SRM.c:6490: m_St.SRM_Status1.Bit.InvertorConnect = 1;`
  - `Core/Src/dev_SRM.c:6511: m_St.SRM_Status1.Bit.InvertorConnect = 1;`
  - `Core/Src/dev_SRM.c:29695: else if (m_St.SRM_Status1.Bit.InvertorConnect == 0)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RequestWork

- **종류**: 구조체 멤버
- **소속 구조체**: `DeviceStatus1Bit`
- **선언**: `INT08U RequestWork`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit5,	ìììêµ¬
- **용도(읽는 법)**: 헤더 주석: Bit5,	ìììêµ¬
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:58673: m_St.SRM_Status1.Bit.RequestWork = 1;`
  - `Core/Src/dev_SRM.c:58677: m_St.SRM_Status1.Bit.RequestWork = 0;`
  - `Core/Src/dev_SRM.c:58815: m_St.SRM_Status1.Bit.RequestWork = 0;`
  - `Core/Src/dev_SRM.c:64564: if (m_St.SRM_Status1.Bit.RequestWork == 1)`
  - `Core/Inc/User_Define.h:664: INT08U RequestWork : 1;		// Bit5,	ìììêµ¬`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Reserved1

- **종류**: 구조체 멤버
- **소속 구조체**: `DeviceStatus1Bit`
- **선언**: `INT08U Reserved1`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit6,
- **용도(읽는 법)**: 헤더 주석: Bit6,
- **코드 참조 예**:
  - `Core/Src/fpga.c:70: INT08U  Reserved1[2];         // 0x00 ~ 0x01`
  - `Core/Src/fpga.c:95: INT08U  Reserved1[2];         // 0x00 ~ 0x01`
  - `Core/Inc/User_Define.h:532: INT08U				Reserved1;`
  - `Core/Inc/User_Define.h:641: INT08U Reserved1 : 1;		// Bit5,`
  - `Core/Inc/User_Define.h:665: INT08U Reserved1 : 1;		// Bit6,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Reserved2

- **종류**: 구조체 멤버
- **소속 구조체**: `DeviceStatus1Bit`
- **선언**: `INT08U Reserved2`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit7,
- **용도(읽는 법)**: 헤더 주석: Bit7,
- **코드 참조 예**:
  - `Core/Src/fpga.c:63: INT08U  Reserved2[7];      // 0x9 ~ 0xF`
  - `Core/Src/fpga.c:73: INT08U  Reserved2[4];         // 0x04 ~ 0x07`
  - `Core/Src/fpga.c:98: INT08U  Reserved2[4];         // 0x04 ~ 0x07`
  - `Core/Inc/User_Define.h:544: INT08U				Reserved2[32];`
  - `Core/Inc/User_Define.h:583: INT08U				Reserved2[30];`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### HomePos

- **종류**: 구조체 멤버
- **소속 구조체**: `DeviceStatus2_Bit`
- **선언**: `INT08U HomePos`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit0,
- **용도(읽는 법)**: HOME/RETURN: 원점복귀 vs 에러복귀 RunMode 혼재. grep으로 확인.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:3311: if (pSetting->SoftLimitErr.HomePos == 0)`
  - `Core/Src/SRM_Parameter.c:3313: pSetting->SoftLimitErr.HomePos = m_ExtSEnv2.TravDrive.ManualDrive.StartPos;`
  - `Core/Src/SRM_Parameter.c:3345: if (pSetting->SoftLimitErr.HomePos == 0)`
  - `Core/Src/SRM_Parameter.c:3347: pSetting->SoftLimitErr.HomePos = m_ExtSEnv2.TravDrive.ManualDrive.StartPos;`
  - `Core/Src/SRM_Parameter.c:3350: pWrBuf->SoftLimitErr.HomePos = pSetting->SoftLimitErr.HomePos;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MaintanencePos

- **종류**: 구조체 멤버
- **소속 구조체**: `DeviceStatus2_Bit`
- **선언**: `INT08U MaintanencePos`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit1,
- **용도(읽는 법)**: 헤더 주석: Bit1,
- **코드 참조 예**:
  - `Core/Src/com_tml.c:3011: if (m_St.SRM_Status2.Bit.MaintanencePos)//이미 보수위치 이면 결과값 9반환`
  - `Core/Src/dev_SRM.c:15425: m_St.SRM_Status2.Bit.MaintanencePos = 1;`
  - `Core/Src/dev_SRM.c:15429: m_St.SRM_Status2.Bit.MaintanencePos = 0;`
  - `Core/Src/dev_SRM.c:16516: m_St.SRM_Status2.Bit.MaintanencePos = 1;`
  - `Core/Src/dev_SRM.c:16520: m_St.SRM_Status2.Bit.MaintanencePos = 0;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Reserved2

- **종류**: 구조체 멤버
- **소속 구조체**: `DeviceStatus2_Bit`
- **선언**: `INT08U Reserved2`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit2,
- **용도(읽는 법)**: 헤더 주석: Bit2,
- **코드 참조 예**:
  - `Core/Src/fpga.c:63: INT08U  Reserved2[7];      // 0x9 ~ 0xF`
  - `Core/Src/fpga.c:73: INT08U  Reserved2[4];         // 0x04 ~ 0x07`
  - `Core/Src/fpga.c:98: INT08U  Reserved2[4];         // 0x04 ~ 0x07`
  - `Core/Inc/User_Define.h:544: INT08U				Reserved2[32];`
  - `Core/Inc/User_Define.h:583: INT08U				Reserved2[30];`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Reserved3

- **종류**: 구조체 멤버
- **소속 구조체**: `DeviceStatus2_Bit`
- **선언**: `INT08U Reserved3`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit3,
- **용도(읽는 법)**: 헤더 주석: Bit3,
- **코드 참조 예**:
  - `Core/Src/fpga.c:75: INT08U  Reserved3[4];         // 0x0C ~ 0x0F`
  - `Core/Src/fpga.c:100: INT08U  Reserved3[4];         // 0x0C ~ 0x0F`
  - `Core/Inc/User_Define.h:552: INT08U				Reserved3[10];`
  - `Core/Inc/User_Define.h:618: INT08U Reserved3 : 1;		// Bit6,`
  - `Core/Inc/User_Define.h:643: INT08U Reserved3 : 1;		// Bit7,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Reserved4

- **종류**: 구조체 멤버
- **소속 구조체**: `DeviceStatus2_Bit`
- **선언**: `INT08U Reserved4`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit4,
- **용도(읽는 법)**: 헤더 주석: Bit4,
- **코드 참조 예**:
  - `Core/Src/fpga.c:76: INT08U  Reserved4[0x10];      // 0x10 ~ 0x1F`
  - `Core/Src/fpga.c:101: INT08U  Reserved4[0x10];      // 0x10 ~ 0x1F`
  - `Core/Inc/User_Define.h:559: INT08U				Reserved4[29];`
  - `Core/Inc/User_Define.h:619: INT08U Reserved4 : 1;		// Bit7,`
  - `Core/Inc/User_Define.h:686: INT08U Reserved4 : 1;	// Bit4,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Reserved5

- **종류**: 구조체 멤버
- **소속 구조체**: `DeviceStatus2_Bit`
- **선언**: `INT08U Reserved5`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit5,
- **용도(읽는 법)**: 헤더 주석: Bit5,
- **코드 참조 예**:
  - `Core/Src/fpga.c:79: INT08U  Reserved5[0x10];      // 0x30 ~ 0x3F`
  - `Core/Src/fpga.c:108: INT08U  Reserved5[0x10];      // 0x31 ~ 0x3F`
  - `Core/Inc/User_Define.h:687: INT08U Reserved5 : 1;	// Bit5,`
  - `Core/Inc/User_Define.h:989: INT08U				Reserved5[3];`
  - `Core/Inc/dev_SRM.h:96: INT16U Reserved5 : 1;			// Bit14`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ManualSW

- **종류**: 구조체 멤버
- **소속 구조체**: `DeviceStatus2_Bit`
- **선언**: `INT08U ManualSW`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit6,
- **용도(읽는 법)**: 헤더 주석: Bit6,
- **코드 참조 예**:
  - `Core/Src/alarm.c:1108: if (m_St.SRM_Status2.Bit.ManualSW)`
  - `Core/Src/alarm.c:1222: if (m_St.SRM_Status2.Bit.ManualSW)`
  - `Core/Src/alarm.c:1403: m_St.SRM_Status2.Bit.ManualSW = s_Manual_SW;`
  - `Core/Src/alarm.c:1421: m_St.SRM_Status2.Bit.ManualSW = s_Manual_SW;`
  - `Core/Src/alarm.c:1423: if (m_St.SRM_Status2.Bit.ManualSW)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### EmergencySW

- **종류**: 구조체 멤버
- **소속 구조체**: `DeviceStatus2_Bit`
- **선언**: `INT08U EmergencySW`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit7,
- **용도(읽는 법)**: 헤더 주석: Bit7,
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:49176: m_St.SRM_Status2.Bit.EmergencySW = 1;`
  - `Core/Src/dev_SRM.c:49181: m_St.SRM_Status2.Bit.EmergencySW = 0;`
  - `Core/Src/dev_SRM.c:49225: m_St.SRM_Status2.Bit.EmergencySW = 1;`
  - `Core/Src/dev_SRM.c:49235: m_St.SRM_Status2.Bit.EmergencySW = 0;`
  - `Core/Inc/User_Define.h:689: INT08U EmergencySW : 1;	// Bit7,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Trav_Left

- **종류**: 구조체 멤버
- **소속 구조체**: `PositionFlag1_Bit`
- **선언**: `INT08U Trav_Left`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit0,
- **용도(읽는 법)**: 헤더 주석: Bit0,
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:1423: nWriteBuf[i].Trav_Left = 1;`
  - `Core/Src/SRM_Parameter.c:1678: pReadBuf->Bay_No, pReadBuf->Lv_No, pReadBuf->Trav_Left, pReadBuf->Lift_Left, pReadBuf->Fork_Left, \`
  - `Core/Src/SRM_Parameter.c:1781: if (pBuf->Trav_Left || pBuf->Trav_Right || pBuf->Lift_Left || pBuf->Lift_Right`
  - `Core/Src/SRM_Parameter.c:1910: if (pBuf->Trav_Left || pBuf->Trav_Right`
  - `Core/Src/com_dsp.c:370: if (m_St.PosFork1.Position1.Bit.Trav_Left || m_St.PosFork1.Position1.Bit.Trav_Right)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LiftUp_Left

- **종류**: 구조체 멤버
- **소속 구조체**: `PositionFlag1_Bit`
- **선언**: `INT08U LiftUp_Left`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit1,
- **용도(읽는 법)**: 헤더 주석: Bit1,
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:12061: if (m_St.PosFork1.Position1.Bit.LiftUp_Left \`
  - `Core/Src/dev_SRM.c:12083: if (m_St.PosFork1.Position1.Bit.LiftUp_Left)`
  - `Core/Src/dev_SRM.c:12283: if (m_St.PosFork1.Position1.Bit.LiftUp_Left)`
  - `Core/Src/dev_SRM.c:13050: if (m_St.PosFork1.Position1.Bit.LiftUp_Left \`
  - `Core/Src/dev_SRM.c:13072: if (m_St.PosFork1.Position1.Bit.LiftUp_Left)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LiftDown_Left

- **종류**: 구조체 멤버
- **소속 구조체**: `PositionFlag1_Bit`
- **선언**: `INT08U LiftDown_Left`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit2,
- **용도(읽는 법)**: 헤더 주석: Bit2,
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:12062: || m_St.PosFork1.Position1.Bit.LiftDown_Left)`
  - `Core/Src/dev_SRM.c:12114: else if (m_St.PosFork1.Position1.Bit.LiftDown_Left)`
  - `Core/Src/dev_SRM.c:12356: else if (m_St.PosFork1.Position1.Bit.LiftDown_Left)`
  - `Core/Src/dev_SRM.c:13051: || m_St.PosFork1.Position1.Bit.LiftDown_Left)`
  - `Core/Src/dev_SRM.c:13103: else if (m_St.PosFork1.Position1.Bit.LiftDown_Left)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Trav_Right

- **종류**: 구조체 멤버
- **소속 구조체**: `PositionFlag1_Bit`
- **선언**: `INT08U Trav_Right`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit3,
- **용도(읽는 법)**: 헤더 주석: Bit3,
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:1426: nWriteBuf[i].Trav_Right = 1;`
  - `Core/Src/SRM_Parameter.c:1679: pReadBuf->Trav_Right, pReadBuf->Lift_Right, pReadBuf->Fork_Right);`
  - `Core/Src/SRM_Parameter.c:1781: if (pBuf->Trav_Left || pBuf->Trav_Right || pBuf->Lift_Left || pBuf->Lift_Right`
  - `Core/Src/SRM_Parameter.c:1910: if (pBuf->Trav_Left || pBuf->Trav_Right`
  - `Core/Src/com_dsp.c:370: if (m_St.PosFork1.Position1.Bit.Trav_Left || m_St.PosFork1.Position1.Bit.Trav_Right)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LiftUp_Right

- **종류**: 구조체 멤버
- **소속 구조체**: `PositionFlag1_Bit`
- **선언**: `INT08U LiftUp_Right`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit4,
- **용도(읽는 법)**: 헤더 주석: Bit4,
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:12167: if (m_St.PosFork1.Position1.Bit.LiftUp_Right \`
  - `Core/Src/dev_SRM.c:12188: if (m_St.PosFork1.Position1.Bit.LiftUp_Right)`
  - `Core/Src/dev_SRM.c:12488: if (m_St.PosFork1.Position1.Bit.LiftUp_Right)`
  - `Core/Src/dev_SRM.c:13156: if (m_St.PosFork1.Position1.Bit.LiftUp_Right \`
  - `Core/Src/dev_SRM.c:13177: if (m_St.PosFork1.Position1.Bit.LiftUp_Right)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LiftDown_Right

- **종류**: 구조체 멤버
- **소속 구조체**: `PositionFlag1_Bit`
- **선언**: `INT08U LiftDown_Right`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit5,
- **용도(읽는 법)**: 헤더 주석: Bit5,
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:12168: || m_St.PosFork1.Position1.Bit.LiftDown_Right)`
  - `Core/Src/dev_SRM.c:12220: else if (m_St.PosFork1.Position1.Bit.LiftDown_Right)`
  - `Core/Src/dev_SRM.c:12561: else if (m_St.PosFork1.Position1.Bit.LiftDown_Right)`
  - `Core/Src/dev_SRM.c:13157: || m_St.PosFork1.Position1.Bit.LiftDown_Right)`
  - `Core/Src/dev_SRM.c:13208: else if (m_St.PosFork1.Position1.Bit.LiftDown_Right)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ForkCenter

- **종류**: 구조체 멤버
- **소속 구조체**: `PositionFlag2_Bit`
- **선언**: `INT08U ForkCenter`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit0,
- **용도(읽는 법)**: 헤더 주석: Bit0,
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:9890: m_St.PosFork1.Position2.Bit.ForkCenter = 1;`
  - `Core/Src/dev_SRM.c:9894: m_St.PosFork1.Position2.Bit.ForkCenter = 1;`
  - `Core/Src/dev_SRM.c:9898: m_St.PosFork1.Position2.Bit.ForkCenter = 0;`
  - `Core/Src/dev_SRM.c:9904: m_St.PosFork1.Position2.Bit.ForkCenter = 0;`
  - `Core/Src/dev_SRM.c:9907: if (m_St.PosFork1.Position2.Bit.ForkCenter == 0)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ForkLeft1

- **종류**: 구조체 멤버
- **소속 구조체**: `PositionFlag2_Bit`
- **선언**: `INT08U ForkLeft1`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit1,
- **용도(읽는 법)**: 헤더 주석: Bit1,
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:10463: m_St.PosFork1.Position2.Bit.ForkLeft1 = 1;  //`
  - `Core/Src/dev_SRM.c:10472: m_St.PosFork1.Position2.Bit.ForkLeft1 = 0;  //`
  - `Core/Src/dev_SRM.c:10599: m_St.PosFork1.Position2.Bit.ForkLeft1 = 1;  //`
  - `Core/Src/dev_SRM.c:10612: m_St.PosFork1.Position2.Bit.ForkLeft1 = 0;  //`
  - `Core/Src/dev_SRM.c:10619: m_St.PosFork1.Position2.Bit.ForkLeft1 = 0;  //`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ForkLeft2

- **종류**: 구조체 멤버
- **소속 구조체**: `PositionFlag2_Bit`
- **선언**: `INT08U ForkLeft2`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit2,
- **용도(읽는 법)**: 헤더 주석: Bit2,
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:10603: m_St.PosFork1.Position2.Bit.ForkLeft2 = 1;  //`
  - `Core/Src/dev_SRM.c:10613: m_St.PosFork1.Position2.Bit.ForkLeft2 = 0;  //`
  - `Core/Src/dev_SRM.c:10620: m_St.PosFork1.Position2.Bit.ForkLeft2 = 0;  //`
  - `Core/Src/dev_SRM.c:10789: m_St.PosFork1.Position2.Bit.ForkLeft2 = 1;`
  - `Core/Src/dev_SRM.c:10793: m_St.PosFork1.Position2.Bit.ForkLeft2 = 0;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ForkLeft3

- **종류**: 구조체 멤버
- **소속 구조체**: `PositionFlag2_Bit`
- **선언**: `INT08U ForkLeft3`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit3,
- **용도(읽는 법)**: 헤더 주석: Bit3,
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:10337: m_St.PosFork1.Position2.Bit.ForkLeft3 = 1;  //`
  - `Core/Src/dev_SRM.c:10341: m_St.PosFork1.Position2.Bit.ForkLeft3 = 0;  //`
  - `Core/Src/dev_SRM.c:10349: m_St.PosFork1.Position2.Bit.ForkLeft3 = 1;  //`
  - `Core/Src/dev_SRM.c:10353: m_St.PosFork1.Position2.Bit.ForkLeft3 = 0;  //`
  - `Core/Src/dev_SRM.c:10359: m_St.PosFork1.Position2.Bit.ForkLeft3 = 0;  //`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ForkRight1

- **종류**: 구조체 멤버
- **소속 구조체**: `PositionFlag2_Bit`
- **선언**: `INT08U ForkRight1`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit4,
- **용도(읽는 법)**: 헤더 주석: Bit4,
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:10108: m_St.PosFork1.Position2.Bit.ForkRight1 = 1;  //`
  - `Core/Src/dev_SRM.c:10117: m_St.PosFork1.Position2.Bit.ForkRight1 = 0;  //`
  - `Core/Src/dev_SRM.c:10123: m_St.PosFork1.Position2.Bit.ForkRight1 = 0;  //`
  - `Core/Src/dev_SRM.c:10242: m_St.PosFork1.Position2.Bit.ForkRight1 = 1;  //`
  - `Core/Src/dev_SRM.c:10255: m_St.PosFork1.Position2.Bit.ForkRight1 = 0;  //`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ForkRight2

- **종류**: 구조체 멤버
- **소속 구조체**: `PositionFlag2_Bit`
- **선언**: `INT08U ForkRight2`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit5,
- **용도(읽는 법)**: 헤더 주석: Bit5,
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:10246: m_St.PosFork1.Position2.Bit.ForkRight2 = 1;  //`
  - `Core/Src/dev_SRM.c:10256: m_St.PosFork1.Position2.Bit.ForkRight2 = 0;  //`
  - `Core/Src/dev_SRM.c:10263: m_St.PosFork1.Position2.Bit.ForkRight2 = 0;  //`
  - `Core/Src/dev_SRM.c:10762: m_St.PosFork1.Position2.Bit.ForkRight2 = 1;`
  - `Core/Src/dev_SRM.c:10766: m_St.PosFork1.Position2.Bit.ForkRight2 = 0;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ForkRight3

- **종류**: 구조체 멤버
- **소속 구조체**: `PositionFlag2_Bit`
- **선언**: `INT08U ForkRight3`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit6,
- **용도(읽는 법)**: 헤더 주석: Bit6,
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:9996: m_St.PosFork1.Position2.Bit.ForkRight3 = 1;`
  - `Core/Src/dev_SRM.c:10000: m_St.PosFork1.Position2.Bit.ForkRight3 = 0;`
  - `Core/Src/dev_SRM.c:10005: m_St.PosFork1.Position2.Bit.ForkRight3 = 0;  //`
  - `Core/Src/dev_SRM.c:10112: m_St.PosFork1.Position2.Bit.ForkRight3 = 1;  //`
  - `Core/Src/dev_SRM.c:10118: m_St.PosFork1.Position2.Bit.ForkRight3 = 0;  //`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Reserved0

- **종류**: 구조체 멤버
- **소속 구조체**: `PositionFlag2_Bit`
- **선언**: `INT08U Reserved0`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit7,
- **용도(읽는 법)**: 헤더 주석: Bit7,
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:640: INT08U Reserved0 : 1;		// Bit4,`
  - `Core/Inc/User_Define.h:735: INT08U Reserved0 : 1;	// Bit7,`
  - `Core/Inc/User_Define.h:787: INT08U Reserved0 : 1;		// Bit5,`
  - `Core/Inc/User_Define.h:948: INT08U				Reserved0;`
  - `Core/Inc/User_Define.h:1014: INT08U				Reserved0[2];`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MoveFlag

- **종류**: 구조체 멤버
- **소속 구조체**: `DriveStatus1`
- **선언**: `INT08U MoveFlag`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit0, 0: Stop
- **용도(읽는 법)**: 헤더 주석: Bit0, 0: Stop
- **코드 참조 예**:
  - `Core/Src/com_tml.c:1778: if (m_St.Inv_St[INV_TRAVEL].Status1.MoveFlag)	return;`
  - `Core/Src/com_tml.c:1779: if (m_St.Inv_St[INV_HOIST].Status1.MoveFlag)	return;`
  - `Core/Src/com_tml.c:1780: if (m_St.Inv_St[INV_FORK_1].Status1.MoveFlag)	return;`
  - `Core/Src/dev_SRM.c:5221: m_St.Inv_St[i].Status1.MoveFlag = m_SRM_TxPDO[i].StatusWord.B.MotorRunning;`
  - `Core/Src/dev_SRM.c:5386: m_St.Inv_St[INV_TRAVEL].Status1.MoveFlag = m_SRM_PI_Type_1.Travel.StatusWord.B.Motor_turning;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### AccelState

- **종류**: 구조체 멤버
- **소속 구조체**: `DriveStatus1`
- **선언**: `INT08U AccelState`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit2, 0: Stop
- **용도(읽는 법)**: 헤더 주석: Bit2, 0: Stop
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:9760: m_St.Inv_St[INV_FORK_1].Status1.AccelState = 0;`
  - `Core/Src/dev_SRM.c:9765: m_St.Inv_St[INV_FORK_1].Status1.AccelState = 1;`
  - `Core/Src/dev_SRM.c:9770: m_St.Inv_St[INV_FORK_1].Status1.AccelState = 0;`
  - `Core/Src/dev_SRM.c:9778: m_St.Inv_St[INV_FORK_1].Status1.AccelState = 0;`
  - `Core/Src/dev_SRM.c:9784: m_St.Inv_St[INV_FORK_1].Status1.AccelState = 0;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DecelState

- **종류**: 구조체 멤버
- **소속 구조체**: `DriveStatus1`
- **선언**: `INT08U DecelState`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit1, 0: Stop
- **용도(읽는 법)**: 헤더 주석: Bit1, 0: Stop
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:9759: m_St.Inv_St[INV_FORK_1].Status1.DecelState = 1;`
  - `Core/Src/dev_SRM.c:9764: m_St.Inv_St[INV_FORK_1].Status1.DecelState = 0;`
  - `Core/Src/dev_SRM.c:9769: m_St.Inv_St[INV_FORK_1].Status1.DecelState = 0;`
  - `Core/Src/dev_SRM.c:9777: m_St.Inv_St[INV_FORK_1].Status1.DecelState = 0;`
  - `Core/Src/dev_SRM.c:9783: m_St.Inv_St[INV_FORK_1].Status1.DecelState = 0;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MoveDirection

- **종류**: 구조체 멤버
- **소속 구조체**: `DriveStatus1`
- **선언**: `INT08U MoveDirection`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit3, 0: Forward
- **용도(읽는 법)**: 헤더 주석: Bit3, 0: Forward
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:9825: m_St.Inv_St[INV_FORK_1].Status1.MoveDirection = 0;		// ì ë°©í¥`
  - `Core/Src/dev_SRM.c:9829: m_St.Inv_St[INV_FORK_1].Status1.MoveDirection = 1;		// ì­ë°©í¥`
  - `Core/Src/dev_SRM.c:9859: m_St.Inv_St[INV_FORK_1].Status1.MoveDirection = 1;		// ì¢ì¸¡ ì´ë`
  - `Core/Src/dev_SRM.c:9863: m_St.Inv_St[INV_FORK_1].Status1.MoveDirection = 0;		// ì°ì¸¡ ì´ë`
  - `Core/Src/dev_SRM.c:14764: m_St.Inv_St[i].Status1.MoveDirection = 0;		// ì ë°©í¥`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### InPosition

- **종류**: 구조체 멤버
- **소속 구조체**: `DriveStatus1`
- **선언**: `INT08U InPosition`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit4, 1: Complete
- **용도(읽는 법)**: 헤더 주석: Bit4, 1: Complete
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:4257: if (nTmpPostion > m_ExtSEnv1.StationEnv.StationSet[0].InPosition.LiftPos)`
  - `Core/Src/SRM_Parameter.c:4259: nTmpPostion = m_ExtSEnv1.StationEnv.StationSet[0].InPosition.LiftPos;`
  - `Core/Src/SRM_Parameter.c:4333: if (nTmpPostion > m_ExtSEnv1.StationEnv.StationSet[0].InPosition.LiftPos)`
  - `Core/Src/SRM_Parameter.c:4335: nTmpPostion = m_ExtSEnv1.StationEnv.StationSet[0].InPosition.LiftPos;`
  - `Core/Src/com_tml.c:3948: if ((pCtrl->StationSet[i].InPosition.TravPos >= m_ExtSEnv2.TravDrive.ManualDrive.StartPos) &&`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### GoodsFlag_Or_MoveHome

- **종류**: 구조체 멤버
- **소속 구조체**: `DriveStatus1`
- **선언**: `INT08U GoodsFlag_Or_MoveHome`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit5, ì£¼í, ì¹ê° íë³µê·
- **용도(읽는 법)**: Goods 플래그: 포크=화물, 주행/승강=레거시 homing 비트 공유 가능. HOME/RETURN: 원점복귀 vs 에러복귀 RunMode 혼재. grep으로 확인.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:773: m_St.Inv_St[INV_FORK_1].Status1.GoodsFlag_Or_MoveHome = 0;`
  - `Core/Src/com_tml.c:917: m_St.Inv_St[INV_FORK_1].Status1.GoodsFlag_Or_MoveHome = 1;`
  - `Core/Src/com_tml.c:921: m_St.Inv_St[INV_FORK_1].Status1.GoodsFlag_Or_MoveHome = 0;`
  - `Core/Src/com_tml.c:1282: m_St.Inv_St[INV_FORK_1].Status1.GoodsFlag_Or_MoveHome = 0;`
  - `Core/Src/com_tml.c:1446: m_St.Inv_St[INV_FORK_1].Status1.GoodsFlag_Or_MoveHome = 1;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ForkOut_Left_OK

- **종류**: 구조체 멤버
- **소속 구조체**: `DriveStatus1`
- **선언**: `INT08U ForkOut_Left_OK`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit6,
- **용도(읽는 법)**: 헤더 주석: Bit6,
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:11761: m_St.Inv_St[INV_FORK_1].Status1.ForkOut_Left_OK = 1;`
  - `Core/Src/dev_SRM.c:11804: m_St.Inv_St[INV_FORK_1].Status1.ForkOut_Left_OK = 0;`
  - `Core/Src/dev_SRM.c:11812: m_St.Inv_St[INV_FORK_1].Status1.ForkOut_Left_OK = 1;`
  - `Core/Src/dev_SRM.c:11846: m_St.Inv_St[INV_FORK_1].Status1.ForkOut_Left_OK = 0;`
  - `Core/Src/dev_SRM.c:11852: m_St.Inv_St[INV_FORK_1].Status1.ForkOut_Left_OK = 1;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ForkOut_Right_OK

- **종류**: 구조체 멤버
- **소속 구조체**: `DriveStatus1`
- **선언**: `INT08U ForkOut_Right_OK`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit7,
- **용도(읽는 법)**: 헤더 주석: Bit7,
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:11762: m_St.Inv_St[INV_FORK_1].Status1.ForkOut_Right_OK = 1;`
  - `Core/Src/dev_SRM.c:11945: m_St.Inv_St[INV_FORK_1].Status1.ForkOut_Right_OK = 0;`
  - `Core/Src/dev_SRM.c:11953: m_St.Inv_St[INV_FORK_1].Status1.ForkOut_Right_OK = 1;`
  - `Core/Src/dev_SRM.c:11987: m_St.Inv_St[INV_FORK_1].Status1.ForkOut_Right_OK = 0;`
  - `Core/Src/dev_SRM.c:11993: m_St.Inv_St[INV_FORK_1].Status1.ForkOut_Right_OK = 1;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Connect

- **종류**: 구조체 멤버
- **소속 구조체**: `DriveStatus2`
- **선언**: `INT08U Connect`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit0,
- **용도(읽는 법)**: 헤더 주석: Bit0,
- **코드 참조 예**:
  - `Core/Src/com_udp.c:164: /* Connect to the remote client */`
  - `Core/Src/com_udp.c:365: /* Connect to the remote client */`
  - `Core/Src/com_udp.c:419: /* Connect to the remote client */`
  - `Core/Src/com_udp.c:484: printf("[TCP] Connect failed, err : %d\r\n", err);`
  - `Core/Src/com_udp.c:966: printf("[DEBUG_APP] Connect EtherNET LAN1. UDP Socket Init.\r\n");`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Alarm

- **종류**: 구조체 멤버
- **소속 구조체**: `DriveStatus2`
- **선언**: `INT08U Alarm`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit1,
- **용도(읽는 법)**: 헤더 주석: Bit1,
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:14: #include "Alarm.h"`
  - `Core/Src/dev_SRM.c:5114: if (m_St.Inv_St[INV_TRAVEL].Status2.Alarm \`
  - `Core/Src/dev_SRM.c:5115: || m_St.Inv_St[INV_HOIST].Status2.Alarm \`
  - `Core/Src/dev_SRM.c:5116: || m_St.Inv_St[INV_FORK_1].Status2.Alarm)`
  - `Core/Src/dev_SRM.c:5253: m_St.Inv_St[i].Status2.Alarm = 0;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### IPOS_ref

- **종류**: 구조체 멤버
- **소속 구조체**: `DriveStatus2`
- **선언**: `INT08U IPOS_ref`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit2, 1: Complete
- **용도(읽는 법)**: 헤더 주석: Bit2, 1: Complete
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:1432: nFlag = m_SRM_TxPDO[nInv].StatusWord.B.IPOS_ref;`
  - `Core/Src/dev_SRM.c:5238: m_St.Inv_St[i].Status2.IPOS_ref = m_SRM_TxPDO[i].StatusWord.B.IPOS_ref;`
  - `Core/Src/dev_SRM.c:5246: m_St.Inv_St[i].Status2.IPOS_ref = m_SRM_TxPDO[i].StatusWord.B.IPOS_ref;`
  - `Core/Src/dev_SRM.c:5387: m_St.Inv_St[INV_TRAVEL].Status2.IPOS_ref = m_SRM_PI_Type_1.Travel.StatusWord.B.Active_drive_referenc`
  - `Core/Src/dev_SRM.c:5417: m_St.Inv_St[INV_HOIST].Status2.IPOS_ref = m_SRM_PI_Type_1.Hoist.StatusWord.B.Active_drive_referenced`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Tuning_Noload

- **종류**: 구조체 멤버
- **소속 구조체**: `DriveStatus2`
- **선언**: `INT08U Tuning_Noload`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit3,
- **용도(읽는 법)**: 헤더 주석: Bit3,
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:785: INT08U Tuning_Noload : 1;	// Bit3,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Tuning_load

- **종류**: 구조체 멤버
- **소속 구조체**: `DriveStatus2`
- **선언**: `INT08U Tuning_load`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit4,
- **용도(읽는 법)**: 헤더 주석: Bit4,
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:786: INT08U Tuning_load : 1;		// Bit4,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Reserved0

- **종류**: 구조체 멤버
- **소속 구조체**: `DriveStatus2`
- **선언**: `INT08U Reserved0`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit5,
- **용도(읽는 법)**: 헤더 주석: Bit5,
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:640: INT08U Reserved0 : 1;		// Bit4,`
  - `Core/Inc/User_Define.h:735: INT08U Reserved0 : 1;	// Bit7,`
  - `Core/Inc/User_Define.h:787: INT08U Reserved0 : 1;		// Bit5,`
  - `Core/Inc/User_Define.h:948: INT08U				Reserved0;`
  - `Core/Inc/User_Define.h:1014: INT08U				Reserved0[2];`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

