# Vol.05 — 기타 Enum (3)

> 생성일: 2026-06-16 | MX SRM App Ver 4.4 | 소스 미수정

기타 enumeration.

---

### TASK_STATUS_STAND_BY

- **종류**: enum `enumCMD_TASK_STATUS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: Task: TML 0x40 다중작업. 0x41과 분기 다름.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2311: m_St.TaskWork[i].OrderState = TASK_STATUS_STAND_BY;`
  - `Core/Src/com_tml.c:3099: if ((m_St.TaskWork[i].OrderState == TASK_STATUS_STAND_BY)`
  - `Core/Inc/User_Define.h:1154: TASK_STATUS_STAND_BY,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TASK_STATUS_DOING

- **종류**: enum `enumCMD_TASK_STATUS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: Task: TML 0x40 다중작업. 0x41과 분기 다름.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:58808: m_St.TaskWork[s_WorkInx].OrderState = TASK_STATUS_DOING;`
  - `Core/Src/dev_SRM.c:62566: m_St.TaskWork[s_WorkInx].OrderState = TASK_STATUS_DOING;`
  - `Core/Inc/User_Define.h:1155: TASK_STATUS_DOING,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TASK_STATUS_FAIL

- **종류**: enum `enumCMD_TASK_STATUS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: Task: TML 0x40 다중작업. 0x41과 분기 다름.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:62728: m_St.TaskWork[s_WorkInx].OrderState = TASK_STATUS_FAIL;`
  - `Core/Src/dev_SRM.c:62890: m_St.TaskWork[s_WorkInx].OrderState = TASK_STATUS_FAIL;`
  - `Core/Inc/User_Define.h:1156: TASK_STATUS_FAIL,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TASK_STATUS_COMPLETE

- **종류**: enum `enumCMD_TASK_STATUS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: Task: TML 0x40 다중작업. 0x41과 분기 다름.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:62535: m_St.TaskWork[s_WorkInx].OrderState = TASK_STATUS_COMPLETE;`
  - `Core/Inc/User_Define.h:1157: TASK_STATUS_COMPLETE,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_TASK_STEP_NONE

- **종류**: enum `enumCMD_TASK_STEP_PROCESS` 멤버
- **값**: `0x80`
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: Task: TML 0x40 다중작업. 0x41과 분기 다름.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:1162: CMD_TASK_STEP_NONE = 0x80,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_TASK_STEP_RX

- **종류**: enum `enumCMD_TASK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: Task: TML 0x40 다중작업. 0x41과 분기 다름.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:1163: CMD_TASK_STEP_RX,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_TASK_STEP_MOVING_FROM

- **종류**: enum `enumCMD_TASK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: Task: TML 0x40 다중작업. 0x41과 분기 다름.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:1164: CMD_TASK_STEP_MOVING_FROM,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_TASK_STEP_ARRIVED_FROM

- **종류**: enum `enumCMD_TASK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: Task: TML 0x40 다중작업. 0x41과 분기 다름.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:1165: CMD_TASK_STEP_ARRIVED_FROM,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_TASK_STEP_FORK_OUT_FROM

- **종류**: enum `enumCMD_TASK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: Task: TML 0x40 다중작업. 0x41과 분기 다름. 포크 서브스텝: GET/PUT 내부 단계.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:1166: CMD_TASK_STEP_FORK_OUT_FROM,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_TASK_STEP_FORK_UP_FROM

- **종류**: enum `enumCMD_TASK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: Task: TML 0x40 다중작업. 0x41과 분기 다름. 포크 서브스텝: GET/PUT 내부 단계.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:1167: CMD_TASK_STEP_FORK_UP_FROM,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_TASK_STEP_FORK_IN_FROM

- **종류**: enum `enumCMD_TASK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: Task: TML 0x40 다중작업. 0x41과 분기 다름. 포크 서브스텝: GET/PUT 내부 단계.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:1168: CMD_TASK_STEP_FORK_IN_FROM,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_TASK_STEP_MOVING_TO

- **종류**: enum `enumCMD_TASK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: Task: TML 0x40 다중작업. 0x41과 분기 다름.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:1169: CMD_TASK_STEP_MOVING_TO,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_TASK_STEP_ARRIVED_TO

- **종류**: enum `enumCMD_TASK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: Task: TML 0x40 다중작업. 0x41과 분기 다름.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:1170: CMD_TASK_STEP_ARRIVED_TO,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_TASK_STEP_FORK_OUT_TO

- **종류**: enum `enumCMD_TASK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: Task: TML 0x40 다중작업. 0x41과 분기 다름. 포크 서브스텝: GET/PUT 내부 단계.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:1171: CMD_TASK_STEP_FORK_OUT_TO,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_TASK_STEP_FORK_DOWN_TO

- **종류**: enum `enumCMD_TASK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: Task: TML 0x40 다중작업. 0x41과 분기 다름. 포크 서브스텝: GET/PUT 내부 단계.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:1172: CMD_TASK_STEP_FORK_DOWN_TO,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_TASK_STEP_FORK_IN_TO

- **종류**: enum `enumCMD_TASK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: Task: TML 0x40 다중작업. 0x41과 분기 다름. 포크 서브스텝: GET/PUT 내부 단계.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:1173: CMD_TASK_STEP_FORK_IN_TO,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_TASK_STEP_LODADED

- **종류**: enum `enumCMD_TASK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: Task: TML 0x40 다중작업. 0x41과 분기 다름.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:1174: CMD_TASK_STEP_LODADED,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### CMD_TASK_STEP_UNLODADED

- **종류**: enum `enumCMD_TASK_STEP_PROCESS` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: Task: TML 0x40 다중작업. 0x41과 분기 다름.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:1175: CMD_TASK_STEP_UNLODADED,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ST_INTERLOCK_NOT_USE

- **종류**: enum `enumSTATION_INTERLOCK_TYPE` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: 인터록: 스테이션/CV OK 대기. 타임아웃→ERROR1_STATION_INTERLOCK_TIMEOUT.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:3927: if ((pCtrl->InterLock_Type >= ST_INTERLOCK_NOT_USE) &&`
  - `Core/Inc/User_Define.h:1335: ST_INTERLOCK_NOT_USE = 0,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ST_INTERLOCK_8BIT

- **종류**: enum `enumSTATION_INTERLOCK_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: 8bit Sensor
- **용도(읽는 법)**: 인터록: 스테이션/CV OK 대기. 타임아웃→ERROR1_STATION_INTERLOCK_TIMEOUT.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:3983: if (pCtrl->InterLock_Type == ST_INTERLOCK_8BIT)`
  - `Core/Src/dev_SRM.c:56836: if (m_ExtSEnv1.StationEnv.InterLock_Type == ST_INTERLOCK_8BIT)`
  - `Core/Src/dev_SRM.c:56886: if (m_ExtSEnv1.StationEnv.InterLock_Type == ST_INTERLOCK_8BIT)`
  - `Core/Src/dev_SRM.c:57089: if (m_ExtSEnv1.StationEnv.InterLock_Type == ST_INTERLOCK_8BIT)`
  - `Core/Src/dev_SRM.c:57251: if (m_ExtSEnv1.StationEnv.InterLock_Type == ST_INTERLOCK_8BIT)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ST_INTERLOCK_COM

- **종류**: enum `enumSTATION_INTERLOCK_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: ì§ìë° íµì
- **용도(읽는 법)**: 인터록: 스테이션/CV OK 대기. 타임아웃→ERROR1_STATION_INTERLOCK_TIMEOUT.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:3928: (pCtrl->InterLock_Type <= ST_INTERLOCK_COM))`
  - `Core/Src/com_tml.c:3998: else if (pCtrl->InterLock_Type == ST_INTERLOCK_COM)`
  - `Core/Src/dev_SRM.c:56855: else if (m_ExtSEnv1.StationEnv.InterLock_Type == ST_INTERLOCK_COM)`
  - `Core/Src/dev_SRM.c:57059: else if (m_ExtSEnv1.StationEnv.InterLock_Type == ST_INTERLOCK_COM)`
  - `Core/Src/dev_SRM.c:57217: else if (m_ExtSEnv1.StationEnv.InterLock_Type == ST_INTERLOCK_COM)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### STATION_NOT_USE

- **종류**: enum `enumSTATION_TYPE` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:3934: if (pCtrl->StationSet[i].Type == STATION_NOT_USE)`
  - `Core/Src/com_tml.c:3941: if (pCtrl->StationSet[i].Type != STATION_NOT_USE)//`
  - `Core/Src/dev_SRM.c:45221: if (m_ExtSEnv1.StationEnv.StationSet[station_no].Type == STATION_NOT_USE)`
  - `Core/Src/dev_SRM.c:57266: if (m_ExtSEnv1.StationEnv.StationSet[nStatinNo - 1].Type == STATION_NOT_USE)`
  - `Core/Src/dev_SRM.c:57270: else if (m_ExtSEnv1.StationEnv.StationSet[nStatinNo - 1].Type == STATION_NOT_USE)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### STATION_IN_TYPE

- **종류**: enum `enumSTATION_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: ìê³
- **용도(읽는 법)**: 헤더 주석: ìê³
- **코드 참조 예**:
  - `Core/Src/com_tml.c:3938: else if ((pCtrl->StationSet[i].Type >= STATION_IN_TYPE) &&`
  - `Core/Src/dev_SRM.c:50655: if ((m_ExtSEnv1.StationEnv.StationSet[nStationNO].Type == STATION_IN_TYPE)`
  - `Core/Src/dev_SRM.c:56913: if (m_ExtSEnv1.StationEnv.StationSet[nStatinNo - 1].Type == STATION_IN_TYPE)`
  - `Core/Src/dev_SRM.c:57018: if (m_ExtSEnv1.StationEnv.StationSet[nStatinNo - 1].Type == STATION_IN_TYPE)`
  - `Core/Src/dev_SRM.c:57421: if (m_ExtSEnv1.StationEnv.StationSet[nStatinNo - 1].Type == STATION_IN_TYPE)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### STATION_OUT_TYPE

- **종류**: enum `enumSTATION_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: ì¶ê³
- **용도(읽는 법)**: 헤더 주석: ì¶ê³
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:46057: if ((m_ExtSEnv1.StationEnv.StationSet[nChange_DST_Station].Type == STATION_OUT_TYPE) \`
  - `Core/Src/dev_SRM.c:50771: if ((m_ExtSEnv1.StationEnv.StationSet[nStationNO].Type == STATION_OUT_TYPE)`
  - `Core/Src/dev_SRM.c:56937: else if (m_ExtSEnv1.StationEnv.StationSet[nStatinNo - 1].Type == STATION_OUT_TYPE)`
  - `Core/Src/dev_SRM.c:57030: if (m_ExtSEnv1.StationEnv.StationSet[nStatinNo - 1].Type == STATION_OUT_TYPE)`
  - `Core/Src/dev_SRM.c:57442: else if (m_ExtSEnv1.StationEnv.StationSet[nStatinNo - 1].Type == STATION_OUT_TYPE)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### STATION_IN_OUT_TYPE

- **종류**: enum `enumSTATION_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: ìì¶ê³
- **용도(읽는 법)**: 헤더 주석: ìì¶ê³
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:46058: || (m_ExtSEnv1.StationEnv.StationSet[nChange_DST_Station].Type == STATION_IN_OUT_TYPE))`
  - `Core/Src/dev_SRM.c:50656: || (m_ExtSEnv1.StationEnv.StationSet[nStationNO].Type == STATION_IN_OUT_TYPE))`
  - `Core/Src/dev_SRM.c:50772: || (m_ExtSEnv1.StationEnv.StationSet[nStationNO].Type == STATION_IN_OUT_TYPE))`
  - `Core/Src/dev_SRM.c:56961: else if (m_ExtSEnv1.StationEnv.StationSet[nStatinNo - 1].Type == STATION_IN_OUT_TYPE)`
  - `Core/Src/dev_SRM.c:57042: if (m_ExtSEnv1.StationEnv.StationSet[nStatinNo - 1].Type == STATION_IN_OUT_TYPE)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### STATION_VIRTUAL_TYPE

- **종류**: enum `enumSTATION_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: ê°ìì¤íì´ì
- **용도(읽는 법)**: 헤더 주석: ê°ìì¤íì´ì
- **코드 참조 예**:
  - `Core/Src/com_tml.c:3939: (pCtrl->StationSet[i].Type <= STATION_VIRTUAL_TYPE))`
  - `Core/Inc/User_Define.h:1345: STATION_VIRTUAL_TYPE,		// ê°ìì¤íì´ì`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ST_INTERLOCK_MODE_0

- **종류**: enum `enumSTATION_INTERLOCK_MODE` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: Default
- **용도(읽는 법)**: 인터록: 스테이션/CV OK 대기. 타임아웃→ERROR1_STATION_INTERLOCK_TIMEOUT.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:56889: if (m_pgmEnv.InterlockMode == ST_INTERLOCK_MODE_0)`
  - `Core/Src/dev_SRM.c:57092: if (m_pgmEnv.InterlockMode == ST_INTERLOCK_MODE_0)`
  - `Core/Src/dev_SRM.c:57404: if (m_pgmEnv.InterlockMode == ST_INTERLOCK_MODE_0)`
  - `Core/Src/dev_SRM.c:57589: if (m_pgmEnv.InterlockMode == ST_INTERLOCK_MODE_0)`
  - `Core/Src/dev_SRM.c:58684: if (m_pgmEnv.InterlockMode == ST_INTERLOCK_MODE_0)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ST_INTERLOCK_MODE_HANKOOK_TIRE_TP2_DIR

- **종류**: enum `enumSTATION_INTERLOCK_MODE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: HankookTire TP2 ìê³ , ì¶ê³ , íë¬¼ ë°©í¥
- **용도(읽는 법)**: 인터록: 스테이션/CV OK 대기. 타임아웃→ERROR1_STATION_INTERLOCK_TIMEOUT.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:56907: else if (m_pgmEnv.InterlockMode == ST_INTERLOCK_MODE_HANKOOK_TIRE_TP2_DIR)`
  - `Core/Src/dev_SRM.c:57110: else if (m_pgmEnv.InterlockMode == ST_INTERLOCK_MODE_HANKOOK_TIRE_TP2_DIR)`
  - `Core/Src/dev_SRM.c:57419: else if (m_pgmEnv.InterlockMode == ST_INTERLOCK_MODE_HANKOOK_TIRE_TP2_DIR)`
  - `Core/Src/dev_SRM.c:57603: else if (m_pgmEnv.InterlockMode == ST_INTERLOCK_MODE_HANKOOK_TIRE_TP2_DIR)`
  - `Core/Src/main.c:641: m_pgmEnv.InterlockMode = ST_INTERLOCK_MODE_HANKOOK_TIRE_TP2_DIR;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### ST_INTERLOCK_MODE_HANKOOK_TIRE_TP2_FlOOR_NO

- **종류**: enum `enumSTATION_INTERLOCK_MODE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: HankookTire TP2 ìê³ , ì¶ê³ , ì¸µ ë²í¸
- **용도(읽는 법)**: 인터록: 스테이션/CV OK 대기. 타임아웃→ERROR1_STATION_INTERLOCK_TIMEOUT.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:57013: else if (m_pgmEnv.InterlockMode == ST_INTERLOCK_MODE_HANKOOK_TIRE_TP2_FlOOR_NO)`
  - `Core/Src/dev_SRM.c:57167: else if (m_pgmEnv.InterlockMode == ST_INTERLOCK_MODE_HANKOOK_TIRE_TP2_FlOOR_NO)`
  - `Core/Src/dev_SRM.c:57511: else if (m_pgmEnv.InterlockMode == ST_INTERLOCK_MODE_HANKOOK_TIRE_TP2_FlOOR_NO)`
  - `Core/Src/dev_SRM.c:57693: else if (m_pgmEnv.InterlockMode == ST_INTERLOCK_MODE_HANKOOK_TIRE_TP2_FlOOR_NO)`
  - `Core/Src/main.c:652: m_pgmEnv.InterlockMode = ST_INTERLOCK_MODE_HANKOOK_TIRE_TP2_FlOOR_NO;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### IN_EM

- **종류**: enum `INPUT_MAP` 멤버
- **값**: `0,	/*!< ID 1, Emergency switch */`
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:7654: if (nPort == IN_EM)`
  - `Core/Src/dev_SRM.c:43882: if (Get_DI_UseFlag(IN_EM))`
  - `Core/Src/dev_SRM.c:43884: if (Get_DI_State(IN_EM) == 0)`
  - `Core/Src/dev_SRM.c:49172: if (Get_DI_UseFlag(IN_EM))`
  - `Core/Src/dev_SRM.c:49174: if (Get_DI_State(IN_EM))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MAX_DI_CNT

- **종류**: enum `INPUT_MAP` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:476: for (i = 0; i < MAX_DI_CNT; i++)`
  - `Core/Src/alarm.c:559: for (i = 0; i < MAX_DI_CNT; i++)`
  - `Core/Src/com_tml.c:3278: for (i = 0; i < MAX_DI_CNT; i++)`
  - `Core/Src/dev_SRM.c:7411: if (nPort < MAX_DI_CNT)`
  - `Core/Src/dev_SRM.c:7749: if (nPort < MAX_DI_CNT)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### OUT_IINH

- **종류**: enum `OUTPUT_MAP` 멤버
- **값**: `0,	/*!< ID 1, ì£¼í, ì¹ê° ì¸ë²í° Inhibit */`
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:44711: DO_Control(OUT_IINH, 1);`
  - `Core/Src/dev_SRM.c:44824: DO_Control(OUT_IINH, 0);`
  - `Core/Src/dev_SRM.c:44828: DO_Control(OUT_IINH, 1);`
  - `Core/Src/dev_SRM.c:44855: DO_Control(OUT_IINH, 0);`
  - `Core/Src/dev_SRM.c:44859: DO_Control(OUT_IINH, 1);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MAX_DO_CNT

- **종류**: enum `OUTPUT_MAP` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:481: for (i = 0; i < MAX_DO_CNT; i++)`
  - `Core/Src/com_tml.c:1880: for (i = 0; i < MAX_DO_CNT; i++)`
  - `Core/Src/com_tml.c:1912: else if ((nID > 0) && (nID <= MAX_DO_CNT))`
  - `Core/Src/com_tml.c:1985: for (i = 0; i < MAX_DO_CNT; i++)`
  - `Core/Src/com_tml.c:1990: else if ((nID > 0) && (nID <= MAX_DO_CNT))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MX_DIO_101

- **종류**: enum `ETHERCAT_SLAVE_PRODUCT_ID` 멤버
- **값**: `1`
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:7370: case MX_DIO_101:`
  - `Core/Src/ecat_main.c:3661: m_DIO_SetInfo.Scan[i - 1].SlaveID = MX_DIO_101;`
  - `Core/Src/ecat_main.c:3741: m_DIO_SetInfo.Scan[i - 1].SlaveID = MX_DIO_101;`
  - `Core/Inc/User_Define.h:1915: MX_DIO_101 = 1,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MX_DIO_201

- **종류**: enum `ETHERCAT_SLAVE_PRODUCT_ID` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6973: case MX_DIO_201:`
  - `Core/Src/dev_SRM.c:7352: case MX_DIO_201:`
  - `Core/Src/ecat_main.c:3665: m_DIO_SetInfo.Scan[i - 1].SlaveID = MX_DIO_201;`
  - `Core/Src/ecat_main.c:3745: m_DIO_SetInfo.Scan[i - 1].SlaveID = MX_DIO_201;`
  - `Core/Inc/User_Define.h:1916: MX_DIO_201,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MX_DIO_301

- **종류**: enum `ETHERCAT_SLAVE_PRODUCT_ID` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6974: case MX_DIO_301:`
  - `Core/Src/dev_SRM.c:7351: case MX_DIO_301:`
  - `Core/Src/ecat_main.c:3669: m_DIO_SetInfo.Scan[i - 1].SlaveID = MX_DIO_301;`
  - `Core/Src/ecat_main.c:3749: m_DIO_SetInfo.Scan[i - 1].SlaveID = MX_DIO_301;`
  - `Core/Inc/User_Define.h:1917: MX_DIO_301,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MX_RLY_101

- **종류**: enum `ETHERCAT_SLAVE_PRODUCT_ID` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6975: case MX_RLY_101:`
  - `Core/Src/dev_SRM.c:7350: case MX_RLY_101:`
  - `Core/Src/ecat_main.c:3673: m_DIO_SetInfo.Scan[i - 1].SlaveID = MX_RLY_101;`
  - `Core/Src/ecat_main.c:3753: m_DIO_SetInfo.Scan[i - 1].SlaveID = MX_RLY_101;`
  - `Core/Inc/User_Define.h:1918: MX_RLY_101,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MX_EXT_101

- **종류**: enum `ETHERCAT_SLAVE_PRODUCT_ID` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6985: case MX_EXT_101:`
  - `Core/Src/dev_SRM.c:7318: case MX_EXT_101:`
  - `Core/Src/ecat_main.c:3677: m_DIO_SetInfo.Scan[i - 1].SlaveID = MX_EXT_101;`
  - `Core/Src/ecat_main.c:3757: m_DIO_SetInfo.Scan[i - 1].SlaveID = MX_EXT_101;`
  - `Core/Inc/User_Define.h:1919: MX_EXT_101,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### GX_MD1611

- **종류**: enum `ETHERCAT_SLAVE_PRODUCT_ID` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6986: case GX_MD1611:`
  - `Core/Src/dev_SRM.c:7332: case GX_MD1611:`
  - `Core/Src/ecat_main.c:3649: m_DIO_SetInfo.Scan[i - 1].SlaveID = GX_MD1611;`
  - `Core/Src/ecat_main.c:3729: m_DIO_SetInfo.Scan[i - 1].SlaveID = GX_MD1611;`
  - `Core/Inc/User_Define.h:1920: GX_MD1611,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### GX_ID1618

- **종류**: enum `ETHERCAT_SLAVE_PRODUCT_ID` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:7353: case GX_ID1618:`
  - `Core/Src/ecat_main.c:3645: m_DIO_SetInfo.Scan[i - 1].SlaveID = GX_ID1618;`
  - `Core/Src/ecat_main.c:3725: m_DIO_SetInfo.Scan[i - 1].SlaveID = GX_ID1618;`
  - `Core/Inc/User_Define.h:1921: GX_ID1618,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### GX_ID3218

- **종류**: enum `ETHERCAT_SLAVE_PRODUCT_ID` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:7371: case GX_ID3218:`
  - `Core/Src/ecat_main.c:3657: m_DIO_SetInfo.Scan[i - 1].SlaveID = GX_ID3218;`
  - `Core/Src/ecat_main.c:3737: m_DIO_SetInfo.Scan[i - 1].SlaveID = GX_ID3218;`
  - `Core/Inc/User_Define.h:1922: GX_ID3218,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### GX_EC0211

- **종류**: enum `ETHERCAT_SLAVE_PRODUCT_ID` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/ecat_main.c:3638: m_DIO_SetInfo.Scan[i - 1].SlaveID = GX_EC0211;`
  - `Core/Src/ecat_main.c:3718: m_DIO_SetInfo.Scan[i - 1].SlaveID = GX_EC0211;`
  - `Core/Src/ecat_main.c:4532: External_Encoder_Proc();		// GX_EC0211`
  - `Core/Inc/User_Define.h:1923: GX_EC0211,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### GX_MD1621

- **종류**: enum `ETHERCAT_SLAVE_PRODUCT_ID` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:6987: case GX_MD1621:`
  - `Core/Src/dev_SRM.c:7333: case GX_MD1621:`
  - `Core/Src/ecat_main.c:3653: m_DIO_SetInfo.Scan[i - 1].SlaveID = GX_MD1621;`
  - `Core/Src/ecat_main.c:3733: m_DIO_SetInfo.Scan[i - 1].SlaveID = GX_MD1621;`
  - `Core/Inc/User_Define.h:1924: GX_MD1621,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### NOT_DEFINE

- **종류**: enum `ETHERCAT_SLAVE_PRODUCT_ID` 멤버
- **값**: `255`
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/ecat_main.c:3681: m_DIO_SetInfo.Scan[i - 1].SlaveID = NOT_DEFINE;`
  - `Core/Src/ecat_main.c:3761: m_DIO_SetInfo.Scan[i - 1].SlaveID = NOT_DEFINE;`
  - `Core/Inc/User_Define.h:1925: NOT_DEFINE = 255,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TRAV_VEL_AUTO_H

- **종류**: enum `enumTRAV_VELOCITY_TYPE` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:2675: case TRAV_VEL_AUTO_H:`
  - `Core/Src/SRM_Parameter.c:2806: case TRAV_VEL_AUTO_H:`
  - `Core/Src/dev_SRM.c:2062: if ((VelType == TRAV_VEL_AUTO_H) || (VelType == TRAV_VEL_AUTO_M) || (VelType == TRAV_VEL_AUTO_L))`
  - `Core/Src/dev_SRM.c:2175: if ((VelType == TRAV_VEL_AUTO_H) || (VelType == TRAV_VEL_AUTO_M) \`
  - `Core/Src/dev_SRM.c:2265: if ((VelType == TRAV_VEL_AUTO_H) || (VelType == TRAV_VEL_AUTO_M) \`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TRAV_VEL_AUTO_M

- **종류**: enum `enumTRAV_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:2676: case TRAV_VEL_AUTO_M:`
  - `Core/Src/SRM_Parameter.c:2807: case TRAV_VEL_AUTO_M:`
  - `Core/Src/dev_SRM.c:2062: if ((VelType == TRAV_VEL_AUTO_H) || (VelType == TRAV_VEL_AUTO_M) || (VelType == TRAV_VEL_AUTO_L))`
  - `Core/Src/dev_SRM.c:2175: if ((VelType == TRAV_VEL_AUTO_H) || (VelType == TRAV_VEL_AUTO_M) \`
  - `Core/Src/dev_SRM.c:2265: if ((VelType == TRAV_VEL_AUTO_H) || (VelType == TRAV_VEL_AUTO_M) \`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TRAV_VEL_AUTO_L

- **종류**: enum `enumTRAV_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:2677: case TRAV_VEL_AUTO_L:`
  - `Core/Src/SRM_Parameter.c:2808: case TRAV_VEL_AUTO_L:`
  - `Core/Src/dev_SRM.c:2062: if ((VelType == TRAV_VEL_AUTO_H) || (VelType == TRAV_VEL_AUTO_M) || (VelType == TRAV_VEL_AUTO_L))`
  - `Core/Src/dev_SRM.c:2176: || (VelType == TRAV_VEL_AUTO_L)	\`
  - `Core/Src/dev_SRM.c:2266: || (VelType == TRAV_VEL_AUTO_L)	\`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TRAV_VEL_MAN_M

- **종류**: enum `enumTRAV_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:2699: case TRAV_VEL_MAN_M:`
  - `Core/Src/SRM_Parameter.c:2828: case TRAV_VEL_MAN_M:`
  - `Core/Src/dev_SRM.c:2081: else if ((VelType == TRAV_VEL_MAN_M) || (VelType == TRAV_VEL_MAN_L) || (VelType == TRAV_VEL_ORIGIN))`
  - `Core/Src/dev_SRM.c:22283: nVelocity_type = TRAV_VEL_MAN_M;`
  - `Core/Src/dev_SRM.c:22299: nVelocity_type = TRAV_VEL_MAN_M;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TRAV_VEL_MAN_L

- **종류**: enum `enumTRAV_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:2713: case TRAV_VEL_MAN_L:`
  - `Core/Src/SRM_Parameter.c:2829: case TRAV_VEL_MAN_L:`
  - `Core/Src/dev_SRM.c:2081: else if ((VelType == TRAV_VEL_MAN_M) || (VelType == TRAV_VEL_MAN_L) || (VelType == TRAV_VEL_ORIGIN))`
  - `Core/Src/dev_SRM.c:22180: INT08U nVelocity_type = TRAV_VEL_MAN_L;`
  - `Core/Src/dev_SRM.c:22259: nVelocity_type = TRAV_VEL_MAN_L;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TRAV_VEL_FORCE

- **종류**: enum `enumTRAV_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:2727: case TRAV_VEL_FORCE:`
  - `Core/Src/SRM_Parameter.c:2843: case TRAV_VEL_FORCE:`
  - `Core/Src/SRM_Parameter.c:3765: if (m_ExtSEnv2.TravDrive.Vel[TRAV_VEL_FORCE].Spd > MAX_TRAVEL_VEL_MAN_M)`
  - `Core/Src/SRM_Parameter.c:3767: m_ExtSEnv2.TravDrive.Vel[TRAV_VEL_FORCE].Spd = MAX_TRAVEL_VEL_MAN_M;`
  - `Core/Src/dev_SRM.c:22317: (m_St.SRM_Mode.Bit.Force) ? (nVelocity_type = TRAV_VEL_FORCE) : (nVelocity_type = TRAV_VEL_MAN_L);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TRAV_VEL_CREEP

- **종류**: enum `enumTRAV_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:2764: case TRAV_VEL_CREEP:`
  - `Core/Src/SRM_Parameter.c:2879: case TRAV_VEL_CREEP:`
  - `Core/Src/dev_SRM.c:2274: if (VelType == TRAV_VEL_CREEP)`
  - `Core/Src/dev_SRM.c:22491: || (nVelocity_type == TRAV_VEL_FORCE) || (nVelocity_type == TRAV_VEL_CREEP))`
  - `Core/Src/dev_SRM.c:23011: || (nVelocity_type == TRAV_VEL_FORCE) || (nVelocity_type == TRAV_VEL_CREEP))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TRAV_VEL_ORIGIN

- **종류**: enum `enumTRAV_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:2750: case TRAV_VEL_ORIGIN:`
  - `Core/Src/SRM_Parameter.c:2865: case TRAV_VEL_ORIGIN:`
  - `Core/Src/dev_SRM.c:2081: else if ((VelType == TRAV_VEL_MAN_M) || (VelType == TRAV_VEL_MAN_L) || (VelType == TRAV_VEL_ORIGIN))`
  - `Core/Src/dev_SRM.c:8142: Motor_Travel_Jog(JOG_TRAV_FORWARD, TRAV_VEL_ORIGIN);`
  - `Core/Src/dev_SRM.c:8152: Motor_Travel_Jog(JOG_TRAV_REVERSE, TRAV_VEL_ORIGIN);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TRAV_VEL_EMG

- **종류**: enum `enumTRAV_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:2779: case TRAV_VEL_EMG:`
  - `Core/Src/SRM_Parameter.c:2892: case TRAV_VEL_EMG:`
  - `Core/Src/dev_SRM.c:2074: else if (VelType == TRAV_VEL_EMG)`
  - `Core/Src/dev_SRM.c:2092: if (VelType != TRAV_VEL_EMG)`
  - `Core/Src/dev_SRM.c:3991: memcpy((INT08U*)&StopVelocity, (INT08U*)&m_ExtSEnv2.TravDrive.Vel[TRAV_VEL_EMG], sizeof(UnitVelocity`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TRAV_VEL_AUTO_DEC_1

- **종류**: enum `enumTRAV_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:2691: case TRAV_VEL_AUTO_DEC_1:`
  - `Core/Src/SRM_Parameter.c:2822: case TRAV_VEL_AUTO_DEC_1:`
  - `Core/Src/dev_SRM.c:2068: else if ((VelType == TRAV_VEL_AUTO_DEC_1) || (VelType == TRAV_VEL_AUTO_DEC_2))`
  - `Core/Src/dev_SRM.c:2177: || (VelType == TRAV_VEL_AUTO_DEC_1) || (VelType == TRAV_VEL_AUTO_DEC_2))`
  - `Core/Src/dev_SRM.c:2267: || (VelType == TRAV_VEL_AUTO_DEC_1) || (VelType == TRAV_VEL_AUTO_DEC_2))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TRAV_VEL_AUTO_DEC_2

- **종류**: enum `enumTRAV_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:2692: case TRAV_VEL_AUTO_DEC_2:`
  - `Core/Src/SRM_Parameter.c:2823: case TRAV_VEL_AUTO_DEC_2:`
  - `Core/Src/dev_SRM.c:2068: else if ((VelType == TRAV_VEL_AUTO_DEC_1) || (VelType == TRAV_VEL_AUTO_DEC_2))`
  - `Core/Src/dev_SRM.c:2177: || (VelType == TRAV_VEL_AUTO_DEC_1) || (VelType == TRAV_VEL_AUTO_DEC_2))`
  - `Core/Src/dev_SRM.c:2267: || (VelType == TRAV_VEL_AUTO_DEC_1) || (VelType == TRAV_VEL_AUTO_DEC_2))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TRAV_VEL_SPARE_1

- **종류**: enum `enumTRAV_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2087: TRAV_VEL_SPARE_1,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TRAV_VELOCITY_SPARE_2

- **종류**: enum `enumTRAV_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2088: TRAV_VELOCITY_SPARE_2,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TRAV_VELOCITY_SPARE_3

- **종류**: enum `enumTRAV_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2089: TRAV_VELOCITY_SPARE_3,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TRAV_VELOCITY_SPARE_4

- **종류**: enum `enumTRAV_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2090: TRAV_VELOCITY_SPARE_4,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### TRAV_VELOCITY_SPARE_5

- **종류**: enum `enumTRAV_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2091: TRAV_VELOCITY_SPARE_5,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MAX_TRAV_VELOCITY_CNT

- **종류**: enum `enumTRAV_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:3664: for (i = 0; i < MAX_TRAV_VELOCITY_CNT; i++)`
  - `Core/Src/com_tml.c:4880: for (i = 0; i < MAX_TRAV_VELOCITY_CNT; i++)// 주행최고카운트`
  - `Core/Src/com_tml.c:4912: for (i = 0; i < MAX_TRAV_VELOCITY_CNT; i++)`
  - `Core/Inc/User_Define.h:2092: MAX_TRAV_VELOCITY_CNT`
  - `Core/Inc/User_Define.h:2506: UnitVelocitySTR			Vel[MAX_TRAV_VELOCITY_CNT];`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LIFT_VEL_AUTO_H

- **종류**: enum `enumLIFT_VELOCITY_TYPE` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:3846: case LIFT_VEL_AUTO_H:`
  - `Core/Src/SRM_Parameter.c:3980: case LIFT_VEL_AUTO_H:`
  - `Core/Src/dev_SRM.c:2477: if ((VelType == LIFT_VEL_AUTO_H) || (VelType == LIFT_VEL_AUTO_M) \`
  - `Core/Src/dev_SRM.c:2598: if ((VelType == LIFT_VEL_AUTO_H) || (VelType == LIFT_VEL_AUTO_M) \`
  - `Core/Src/dev_SRM.c:2676: if ((VelType == LIFT_VEL_AUTO_H) || (VelType == LIFT_VEL_AUTO_M) \`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LIFT_VEL_AUTO_M

- **종류**: enum `enumLIFT_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:3860: case LIFT_VEL_AUTO_M:`
  - `Core/Src/SRM_Parameter.c:3981: case LIFT_VEL_AUTO_M:`
  - `Core/Src/dev_SRM.c:2477: if ((VelType == LIFT_VEL_AUTO_H) || (VelType == LIFT_VEL_AUTO_M) \`
  - `Core/Src/dev_SRM.c:2598: if ((VelType == LIFT_VEL_AUTO_H) || (VelType == LIFT_VEL_AUTO_M) \`
  - `Core/Src/dev_SRM.c:2676: if ((VelType == LIFT_VEL_AUTO_H) || (VelType == LIFT_VEL_AUTO_M) \`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LIFT_VEL_AUTO_L

- **종류**: enum `enumLIFT_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:3861: case LIFT_VEL_AUTO_L:`
  - `Core/Src/SRM_Parameter.c:3982: case LIFT_VEL_AUTO_L:`
  - `Core/Src/dev_SRM.c:2478: || (VelType == LIFT_VEL_AUTO_L) || (VelType == LIFT_VEL_LIFT_AUTO_FORKOUT) \`
  - `Core/Src/dev_SRM.c:2599: || (VelType == LIFT_VEL_AUTO_L) || (VelType == LIFT_VEL_LIFT_AUTO_FORKOUT)`
  - `Core/Src/dev_SRM.c:2677: || (VelType == LIFT_VEL_AUTO_L) || (VelType == LIFT_VEL_LIFT_AUTO_FORKOUT)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LIFT_VEL_MAN_M

- **종류**: enum `enumLIFT_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:3882: case LIFT_VEL_MAN_M:`
  - `Core/Src/SRM_Parameter.c:4002: case LIFT_VEL_MAN_M:`
  - `Core/Src/dev_SRM.c:2495: else if ((VelType == LIFT_VEL_MAN_M) || (VelType == LIFT_VEL_MAN_L) || (VelType == LIFT_VEL_ORIGIN))`
  - `Core/Src/dev_SRM.c:24947: nVelocity_type = LIFT_VEL_MAN_M;`
  - `Core/Src/dev_SRM.c:24970: nVelocity_type = LIFT_VEL_MAN_M;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LIFT_VEL_MAN_L

- **종류**: enum `enumLIFT_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:3896: case LIFT_VEL_MAN_L:`
  - `Core/Src/SRM_Parameter.c:4003: case LIFT_VEL_MAN_L:`
  - `Core/Src/dev_SRM.c:2495: else if ((VelType == LIFT_VEL_MAN_M) || (VelType == LIFT_VEL_MAN_L) || (VelType == LIFT_VEL_ORIGIN))`
  - `Core/Src/dev_SRM.c:24744: INT08U nVelocity_type = LIFT_VEL_MAN_L;`
  - `Core/Src/dev_SRM.c:24926: nVelocity_type = LIFT_VEL_MAN_L;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LIFT_VEL_FORCE

- **종류**: enum `enumLIFT_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:3910: case LIFT_VEL_FORCE:`
  - `Core/Src/SRM_Parameter.c:4017: case LIFT_VEL_FORCE:`
  - `Core/Src/SRM_Parameter.c:5144: if (m_ExtSEnv2.LiftDrive.Vel[LIFT_VEL_FORCE].Spd > MAX_LIFT_VEL_MAN_M)`
  - `Core/Src/SRM_Parameter.c:5146: m_ExtSEnv2.LiftDrive.Vel[LIFT_VEL_FORCE].Spd = MAX_LIFT_VEL_MAN_M;`
  - `Core/Src/dev_SRM.c:24990: (m_St.SRM_Mode.Bit.Force) ? (nVelocity_type = LIFT_VEL_FORCE) : (nVelocity_type = LIFT_VEL_MAN_L);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LIFT_VEL_CREEP

- **종류**: enum `enumLIFT_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:3949: case LIFT_VEL_CREEP:`
  - `Core/Src/SRM_Parameter.c:4055: case LIFT_VEL_CREEP:`
  - `Core/Src/dev_SRM.c:2685: if (VelType == LIFT_VEL_CREEP)`
  - `Core/Src/dev_SRM.c:58445: LIFT_VEL_MAN_M, LIFT_VEL_MAN_L, LIFT_VEL_CREEP,`
  - `Core/Inc/User_Define.h:2102: LIFT_VEL_CREEP,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LIFT_VEL_ORIGIN

- **종류**: enum `enumLIFT_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:3934: case LIFT_VEL_ORIGIN:`
  - `Core/Src/SRM_Parameter.c:4041: case LIFT_VEL_ORIGIN:`
  - `Core/Src/dev_SRM.c:2495: else if ((VelType == LIFT_VEL_MAN_M) || (VelType == LIFT_VEL_MAN_L) || (VelType == LIFT_VEL_ORIGIN))`
  - `Core/Src/dev_SRM.c:8490: Motor_Lift_Jog(JOG_LIFT_UP, LIFT_VEL_ORIGIN);`
  - `Core/Src/dev_SRM.c:8499: Motor_Lift_Jog(JOG_LIFT_DOWN, LIFT_VEL_ORIGIN);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LIFT_VEL_EMG

- **종류**: enum `enumLIFT_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:3960: case LIFT_VEL_EMG:`
  - `Core/Src/SRM_Parameter.c:4067: case LIFT_VEL_EMG:`
  - `Core/Src/dev_SRM.c:2489: else if (VelType == LIFT_VEL_EMG)`
  - `Core/Src/dev_SRM.c:2504: if (VelType != LIFT_VEL_EMG)`
  - `Core/Src/dev_SRM.c:3995: memcpy((INT08U*)&StopVelocity, (INT08U*)&m_ExtSEnv2.LiftDrive.Vel[LIFT_VEL_EMG], sizeof(UnitVelocity`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LIFT_VEL_AUTO_DEC_1

- **종류**: enum `enumLIFT_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:3875: case LIFT_VEL_AUTO_DEC_1:`
  - `Core/Src/SRM_Parameter.c:3996: case LIFT_VEL_AUTO_DEC_1:`
  - `Core/Src/dev_SRM.c:2484: else if ((VelType == LIFT_VEL_AUTO_DEC_1) || (VelType == LIFT_VEL_AUTO_DEC_2))`
  - `Core/Src/dev_SRM.c:2600: || (VelType == LIFT_VEL_AUTO_DEC_1) || (VelType == LIFT_VEL_AUTO_DEC_2))`
  - `Core/Src/dev_SRM.c:2678: || (VelType == LIFT_VEL_AUTO_DEC_1) || (VelType == LIFT_VEL_AUTO_DEC_2))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LIFT_VEL_AUTO_DEC_2

- **종류**: enum `enumLIFT_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:3876: case LIFT_VEL_AUTO_DEC_2:`
  - `Core/Src/SRM_Parameter.c:3997: case LIFT_VEL_AUTO_DEC_2:`
  - `Core/Src/dev_SRM.c:2484: else if ((VelType == LIFT_VEL_AUTO_DEC_1) || (VelType == LIFT_VEL_AUTO_DEC_2))`
  - `Core/Src/dev_SRM.c:2600: || (VelType == LIFT_VEL_AUTO_DEC_1) || (VelType == LIFT_VEL_AUTO_DEC_2))`
  - `Core/Src/dev_SRM.c:2678: || (VelType == LIFT_VEL_AUTO_DEC_1) || (VelType == LIFT_VEL_AUTO_DEC_2))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LIFT_VEL_LIFT_AUTO_FORKOUT

- **종류**: enum `enumLIFT_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:3932: case LIFT_VEL_LIFT_AUTO_FORKOUT:`
  - `Core/Src/SRM_Parameter.c:4039: case LIFT_VEL_LIFT_AUTO_FORKOUT:`
  - `Core/Src/dev_SRM.c:2478: || (VelType == LIFT_VEL_AUTO_L) || (VelType == LIFT_VEL_LIFT_AUTO_FORKOUT) \`
  - `Core/Src/dev_SRM.c:2599: || (VelType == LIFT_VEL_AUTO_L) || (VelType == LIFT_VEL_LIFT_AUTO_FORKOUT)`
  - `Core/Src/dev_SRM.c:2677: || (VelType == LIFT_VEL_AUTO_L) || (VelType == LIFT_VEL_LIFT_AUTO_FORKOUT)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LIFT_VEL_LIFT_MAN_FORKOUT

- **종류**: enum `enumLIFT_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:3933: case LIFT_VEL_LIFT_MAN_FORKOUT:`
  - `Core/Src/SRM_Parameter.c:4040: case LIFT_VEL_LIFT_MAN_FORKOUT:`
  - `Core/Src/dev_SRM.c:25140: (m_St.SRM_Mode.Bit.Force) ? (nVelocity_type = LIFT_VEL_FORCE) : (nVelocity_type = LIFT_VEL_LIFT_MAN_`
  - `Core/Src/dev_SRM.c:25249: if (nVelocity_type <= LIFT_VEL_LIFT_MAN_FORKOUT)`
  - `Core/Src/dev_SRM.c:25577: (m_St.SRM_Mode.Bit.Force) ? (nVelocity_type = LIFT_VEL_FORCE) : (nVelocity_type = LIFT_VEL_LIFT_MAN_`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LIFT_VEL_LIFT_STICKY

- **종류**: enum `enumLIFT_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:3935: case LIFT_VEL_LIFT_STICKY:`
  - `Core/Src/dev_SRM.c:2479: || (VelType == LIFT_VEL_LIFT_STICKY))`
  - `Core/Src/dev_SRM.c:62118: nLift_Control_Error = Auto_Ctr_Lift(s_Lift_MoveTarget, LIFT_VEL_LIFT_STICKY);`
  - `Core/Src/dev_SRM.c:62260: nLift_Control_Error = Auto_Ctr_Lift(s_Lift_MoveTarget, LIFT_VEL_LIFT_STICKY);`
  - `Core/Inc/User_Define.h:2109: LIFT_VEL_LIFT_STICKY,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LIFT_VELOCITY_SPARE_2

- **종류**: enum `enumLIFT_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2110: LIFT_VELOCITY_SPARE_2,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### LIFT_VELOCITY_SPARE_3

- **종류**: enum `enumLIFT_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2111: LIFT_VELOCITY_SPARE_3,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MAX_LIFT_VELOCITY_CNT

- **종류**: enum `enumLIFT_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:5040: for (i = 0; i < MAX_LIFT_VELOCITY_CNT; i++)`
  - `Core/Src/SRM_Parameter.c:6139: for (i = 0; i < MAX_LIFT_VELOCITY_CNT; i++)`
  - `Core/Src/com_tml.c:5045: for (i = 0; i < MAX_LIFT_VELOCITY_CNT; i++)`
  - `Core/Src/com_tml.c:5081: for (i = 0; i < MAX_LIFT_VELOCITY_CNT; i++)`
  - `Core/Inc/User_Define.h:2112: MAX_LIFT_VELOCITY_CNT`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_VEL_AUTO_H

- **종류**: enum `enumFORK_VELOCITY_TYPE` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:5226: case FORK_VEL_AUTO_H:`
  - `Core/Src/SRM_Parameter.c:5339: case FORK_VEL_AUTO_H:`
  - `Core/Src/dev_SRM.c:2941: if ((VelType == FORK_VEL_AUTO_H) || (VelType == FORK_VEL_AUTO_M) \`
  - `Core/Src/dev_SRM.c:3325: if ((VelType == FORK_VEL_AUTO_H) || (VelType == FORK_VEL_AUTO_M) \`
  - `Core/Src/dev_SRM.c:3630: if ((VelType == FORK_VEL_AUTO_H) || (VelType == FORK_VEL_AUTO_M) || (VelType == FORK_VEL_AUTO_L))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_VEL_AUTO_M

- **종류**: enum `enumFORK_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:5227: case FORK_VEL_AUTO_M:`
  - `Core/Src/SRM_Parameter.c:5340: case FORK_VEL_AUTO_M:`
  - `Core/Src/dev_SRM.c:2941: if ((VelType == FORK_VEL_AUTO_H) || (VelType == FORK_VEL_AUTO_M) \`
  - `Core/Src/dev_SRM.c:3325: if ((VelType == FORK_VEL_AUTO_H) || (VelType == FORK_VEL_AUTO_M) \`
  - `Core/Src/dev_SRM.c:3630: if ((VelType == FORK_VEL_AUTO_H) || (VelType == FORK_VEL_AUTO_M) || (VelType == FORK_VEL_AUTO_L))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

