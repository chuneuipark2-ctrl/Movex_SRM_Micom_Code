# Vol.06 — 구조체 멤버 (2)

> 생성일: 2026-06-16 | MX SRM App Ver 4.4 | 소스 미수정

m_St 등 필드.

---

### IO_Control

- **종류**: 구조체 멤버
- **소속 구조체**: `DriveStatus2`
- **선언**: `INT08U IO_Control`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit5,
- **용도(읽는 법)**: 헤더 주석: Bit5,
- **코드 참조 예**:
  - `Core/Src/com_tml.c:5486: m_St.Inv_St[INV_FORK_1].Status2.IO_Control = 0;`
  - `Core/Src/com_tml.c:5490: m_St.Inv_St[INV_FORK_1].Status2.IO_Control = 1;`
  - `Core/Src/com_tml.c:5498: m_St.Inv_St[INV_FORK_2].Status2.IO_Control = 0;`
  - `Core/Src/com_tml.c:5502: m_St.Inv_St[INV_FORK_2].Status2.IO_Control = 1;`
  - `Core/Src/dev_SRM.c:3236: if (m_St.Inv_St[INV_FORK_1].Status2.IO_Control)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Com_Control

- **종류**: 구조체 멤버
- **소속 구조체**: `DriveStatus2`
- **선언**: `INT08U Com_Control`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit6,
- **용도(읽는 법)**: 헤더 주석: Bit6,
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:63664: m_St.Inv_St[INV_FORK_1].Status2.Com_Control = 0;`
  - `Core/Src/dev_SRM.c:63669: m_St.Inv_St[INV_FORK_1].Status2.Com_Control = 1;`
  - `Core/Src/dev_SRM.c:63675: m_St.Inv_St[INV_FORK_1].Status2.Com_Control = 0;`
  - `Core/Src/dev_SRM.c:63684: m_St.Inv_St[INV_FORK_2].Status2.Com_Control = 0;`
  - `Core/Src/dev_SRM.c:63689: m_St.Inv_St[INV_FORK_2].Status2.Com_Control = 1;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Detect1

- **종류**: 구조체 멤버
- **소속 구조체**: `LidarStatus`
- **선언**: `INT08U Detect1`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit0,
- **용도(읽는 법)**: 헤더 주석: Bit0,
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:927: INT08U Detect1 : 1;			// Bit0,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Detect2

- **종류**: 구조체 멤버
- **소속 구조체**: `LidarStatus`
- **선언**: `INT08U Detect2`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit1,
- **용도(읽는 법)**: 헤더 주석: Bit1,
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:928: INT08U Detect2 : 1;			// Bit1,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Detect3

- **종류**: 구조체 멤버
- **소속 구조체**: `LidarStatus`
- **선언**: `INT08U Detect3`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit2,
- **용도(읽는 법)**: 헤더 주석: Bit2,
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:929: INT08U Detect3 : 1;			// Bit2,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### Fault

- **종류**: 구조체 멤버
- **소속 구조체**: `LidarStatus`
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

### Select_Zone

- **종류**: 구조체 멤버
- **소속 구조체**: `LidarStatus`
- **선언**: `INT08U Select_Zone`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit4 - 7,
- **용도(읽는 법)**: 헤더 주석: Bit4 - 7,
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:931: INT08U Select_Zone : 4;		// Bit4 - 7,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### mFCL_FCR

- **종류**: 구조체 멤버
- **소속 구조체**: `ForkPosSensorSetup_Bit`
- **선언**: `INT08U mFCL_FCR`
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:9356: if (m_ExtSEnv2.ForkDrive.PosSensorUse.Setting.Bit.mFCL_FCR == 0)`
  - `Core/Src/dev_SRM.c:9380: else if (m_ExtSEnv2.ForkDrive.PosSensorUse.Setting.Bit.mFCL_FCR == 1)`
  - `Core/Src/dev_SRM.c:9391: else if (m_ExtSEnv2.ForkDrive.PosSensorUse.Setting.Bit.mFCL_FCR == 2)`
  - `Core/Src/dev_SRM.c:9490: if (m_ExtSEnv2.ForkDrive.PosSensorUse.Setting.Bit.mFCL_FCR == 0)`
  - `Core/Src/dev_SRM.c:9519: else if (m_ExtSEnv2.ForkDrive.PosSensorUse.Setting.Bit.mFCL_FCR == 1)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### mFHL

- **종류**: 구조체 멤버
- **소속 구조체**: `ForkPosSensorSetup_Bit`
- **선언**: `INT08U mFHL`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit2,
- **용도(읽는 법)**: 헤더 주석: Bit2,
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:5960: if (pSetting->ForkPosDepth.mFEL > pSetting->ForkPosDepth.mFHL)`
  - `Core/Src/SRM_Parameter.c:5962: pSetting->ForkPosDepth.mFHL = 0;`
  - `Core/Src/SRM_Parameter.c:5988: pSetting->ForkPosDepth.mFHL = 0;`
  - `Core/Src/SRM_Parameter.c:6002: if (pSetting->ForkPosDepth.mFEL > pSetting->ForkPosDepth.mFHL)`
  - `Core/Src/SRM_Parameter.c:6004: pSetting->ForkPosDepth.mFHL = 0;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### mFML

- **종류**: 구조체 멤버
- **소속 구조체**: `ForkPosSensorSetup_Bit`
- **선언**: `INT08U mFML`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit3,
- **용도(읽는 법)**: 헤더 주석: Bit3,
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:5986: pSetting->ForkPosDepth.mFML = 0;`
  - `Core/Src/SRM_Parameter.c:6029: pSetting->ForkPosDepth.mFML = 0;`
  - `Core/Src/dev_SRM.c:9697: if ((m_St.Inv_St[INV_FORK_1].Current_Pos < m_ExtSEnv2.ForkDrive.ForkPosDepth.mFML - nDef_InPos_Offse`
  - `Core/Src/dev_SRM.c:9698: && m_ExtSEnv2.ForkDrive.ForkPosDepth.mFML)`
  - `Core/Src/dev_SRM.c:10499: if (m_ExtSEnv2.ForkDrive.ForkPosDepth.mFML < 0)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### mFEL

- **종류**: 구조체 멤버
- **소속 구조체**: `ForkPosSensorSetup_Bit`
- **선언**: `INT08U mFEL`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit4,
- **용도(읽는 법)**: 헤더 주석: Bit4,
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:5932: if (pSetting->ManualDrive.LeftPos > pSetting->ForkPosDepth.mFEL)`
  - `Core/Src/SRM_Parameter.c:5934: pSetting->ForkPosDepth.mFEL = pSetting->ManualDrive.LeftPos;`
  - `Core/Src/SRM_Parameter.c:5945: if (m_ExtSEnv2.ForkDrive.ManualDrive.LeftPos > pSetting->ForkPosDepth.mFEL)`
  - `Core/Src/SRM_Parameter.c:5947: pSetting->ForkPosDepth.mFEL = m_ExtSEnv2.ForkDrive.ManualDrive.LeftPos;`
  - `Core/Src/SRM_Parameter.c:5960: if (pSetting->ForkPosDepth.mFEL > pSetting->ForkPosDepth.mFHL)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### mFHR

- **종류**: 구조체 멤버
- **소속 구조체**: `ForkPosSensorSetup_Bit`
- **선언**: `INT08U mFHR`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit5,
- **용도(읽는 법)**: 헤더 주석: Bit5,
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:5955: if (pSetting->ForkPosDepth.mFER < pSetting->ForkPosDepth.mFHR)`
  - `Core/Src/SRM_Parameter.c:5957: pSetting->ForkPosDepth.mFHR = 0;`
  - `Core/Src/SRM_Parameter.c:5989: pSetting->ForkPosDepth.mFHR = 0;`
  - `Core/Src/SRM_Parameter.c:6019: if (pSetting->ForkPosDepth.mFER < pSetting->ForkPosDepth.mFHR)`
  - `Core/Src/SRM_Parameter.c:6021: pSetting->ForkPosDepth.mFHR = 0;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### mFMR

- **종류**: 구조체 멤버
- **소속 구조체**: `ForkPosSensorSetup_Bit`
- **선언**: `INT08U mFMR`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit6,
- **용도(읽는 법)**: 헤더 주석: Bit6,
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:5987: pSetting->ForkPosDepth.mFMR = 0;`
  - `Core/Src/SRM_Parameter.c:6030: pSetting->ForkPosDepth.mFMR = 0;`
  - `Core/Src/dev_SRM.c:9673: if ((m_St.Inv_St[INV_FORK_1].Current_Pos > m_ExtSEnv2.ForkDrive.ForkPosDepth.mFMR + nDef_InPos_Offse`
  - `Core/Src/dev_SRM.c:9674: && m_ExtSEnv2.ForkDrive.ForkPosDepth.mFMR)`
  - `Core/Src/dev_SRM.c:10146: if (m_ExtSEnv2.ForkDrive.ForkPosDepth.mFMR > 0)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### mFER

- **종류**: 구조체 멤버
- **소속 구조체**: `ForkPosSensorSetup_Bit`
- **선언**: `INT08U mFER`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Bit7,
- **용도(읽는 법)**: 헤더 주석: Bit7,
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:5938: if (pSetting->ManualDrive.RightPos < pSetting->ForkPosDepth.mFER)`
  - `Core/Src/SRM_Parameter.c:5940: pSetting->ForkPosDepth.mFER = pSetting->ManualDrive.RightPos;`
  - `Core/Src/SRM_Parameter.c:5950: if (m_ExtSEnv2.ForkDrive.ManualDrive.RightPos < pSetting->ForkPosDepth.mFER)`
  - `Core/Src/SRM_Parameter.c:5952: pSetting->ForkPosDepth.mFER = m_ExtSEnv2.ForkDrive.ManualDrive.RightPos;`
  - `Core/Src/SRM_Parameter.c:5955: if (pSetting->ForkPosDepth.mFER < pSetting->ForkPosDepth.mFHR)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

