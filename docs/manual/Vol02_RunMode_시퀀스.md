# Vol.02 — RUN_SEQ_*

> 생성일: 2026-06-16 | MX SRM App Ver 4.4 | 소스 미수정

상태머신 case.

---

### RUN_SEQ_STAND_BY

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:2374: else if (m_pgmEnv.SRM_RunMode != RUN_SEQ_STAND_BY)`
  - `Core/Src/com_tml.c:2412: if (m_pgmEnv.SRM_RunMode == RUN_SEQ_STAND_BY)`
  - `Core/Src/com_tml.c:2709: if (m_pgmEnv.SRM_RunMode == RUN_SEQ_STAND_BY)`
  - `Core/Src/com_tml.c:3000: if (m_pgmEnv.SRM_RunMode != RUN_SEQ_STAND_BY) // 스텐바이 모드가 아닐때`
  - `Core/Src/com_tml.c:3052: if (m_pgmEnv.SRM_RunMode == RUN_SEQ_STAND_BY)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_START

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/alarm.c:1043: if ((m_pgmEnv.SRM_RunMode >= RUN_SEQ_START)`
  - `Core/Src/alarm.c:1138: if ((m_pgmEnv.SRM_RunMode >= RUN_SEQ_START)`
  - `Core/Src/alarm.c:1265: if ((m_pgmEnv.SRM_RunMode >= RUN_SEQ_START)`
  - `Core/Src/alarm.c:1628: if ((m_pgmEnv.SRM_RunMode >= RUN_SEQ_START) && (m_pgmEnv.SRM_RunMode <= RUN_SEQ_COMPLETE))`
  - `Core/Src/com_tml.c:2321: m_pgmEnv.SRM_RunMode = RUN_SEQ_START;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_PREPARE_MOVE_0

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case. 이동 준비: 화물검증, InPosition 스킵, 브레이크/딜레이.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:58861: m_pgmEnv.SRM_RunMode = RUN_SEQ_PREPARE_MOVE_0;`
  - `Core/Src/dev_SRM.c:58866: case RUN_SEQ_PREPARE_MOVE_0:`
  - `Core/Src/dev_SRM.c:62569: m_pgmEnv.SRM_RunMode = RUN_SEQ_PREPARE_MOVE_0;`
  - `Core/Src/dev_SRM.c:62667: m_pgmEnv.SRM_RunMode = RUN_SEQ_PREPARE_MOVE_0;`
  - `Core/Inc/dev_SRM.h:1884: RUN_SEQ_PREPARE_MOVE_0,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_PREPARE_MOVE_BRAKE_RELEASE_0

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 주행. 승강 브레이크 해제 확인
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case. 이동 준비: 화물검증, InPosition 스킵, 브레이크/딜레이.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:58994: m_pgmEnv.SRM_RunMode = RUN_SEQ_PREPARE_MOVE_BRAKE_RELEASE_0;`
  - `Core/Src/dev_SRM.c:59041: m_pgmEnv.SRM_RunMode = RUN_SEQ_PREPARE_MOVE_BRAKE_RELEASE_0;`
  - `Core/Src/dev_SRM.c:59048: case RUN_SEQ_PREPARE_MOVE_BRAKE_RELEASE_0:`
  - `Core/Src/dev_SRM.c:59121: m_pgmEnv.SRM_RunMode = RUN_SEQ_PREPARE_MOVE_BRAKE_RELEASE_0;`
  - `Core/Inc/dev_SRM.h:1886: RUN_SEQ_PREPARE_MOVE_BRAKE_RELEASE_0,		// 주행. 승강 브레이크 해제 확인`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_PREPARE_MOVE_BRAKE_RELEASE_1

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case. 이동 준비: 화물검증, InPosition 스킵, 브레이크/딜레이.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:59086: m_pgmEnv.SRM_RunMode = RUN_SEQ_PREPARE_MOVE_BRAKE_RELEASE_1;`
  - `Core/Src/dev_SRM.c:59099: case RUN_SEQ_PREPARE_MOVE_BRAKE_RELEASE_1:`
  - `Core/Inc/dev_SRM.h:1887: RUN_SEQ_PREPARE_MOVE_BRAKE_RELEASE_1,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_MOVE_BEFORE_DELAY

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 주행, 승강 이동 전 대기
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:58996: m_pgmEnv.SRM_RunMode = RUN_SEQ_MOVE_BEFORE_DELAY;`
  - `Core/Src/dev_SRM.c:59043: m_pgmEnv.SRM_RunMode = RUN_SEQ_MOVE_BEFORE_DELAY;`
  - `Core/Src/dev_SRM.c:59094: m_pgmEnv.SRM_RunMode = RUN_SEQ_MOVE_BEFORE_DELAY;`
  - `Core/Src/dev_SRM.c:59125: case RUN_SEQ_MOVE_BEFORE_DELAY: // Move Before Delay`
  - `Core/Inc/dev_SRM.h:1889: RUN_SEQ_MOVE_BEFORE_DELAY,			// 주행, 승강 이동 전 대기`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_START_MOVE_0

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 주행, 승강 동작 명령 전송
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:4386: if ((m_pgmEnv.SRM_RunMode >= RUN_SEQ_START_MOVE_0) && (m_pgmEnv.SRM_RunMode <= RUN_SEQ_TRAV_LIFT_MOV`
  - `Core/Src/dev_SRM.c:4446: if ((m_pgmEnv.SRM_RunMode >= RUN_SEQ_START_MOVE_0) && (m_pgmEnv.SRM_RunMode <= RUN_SEQ_TRAV_LIFT_MOV`
  - `Core/Src/dev_SRM.c:59139: m_pgmEnv.SRM_RunMode = RUN_SEQ_START_MOVE_0;`
  - `Core/Src/dev_SRM.c:59143: case RUN_SEQ_START_MOVE_0:`
  - `Core/Inc/dev_SRM.h:1890: RUN_SEQ_START_MOVE_0,			// 주행, 승강 동작 명령 전송`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_START_MOVE_1

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 주행, 승강 브레이크 해제시간 측정
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:49710: case RUN_SEQ_START_MOVE_1:`
  - `Core/Src/dev_SRM.c:59332: m_pgmEnv.SRM_RunMode = RUN_SEQ_START_MOVE_1;`
  - `Core/Src/dev_SRM.c:59335: case RUN_SEQ_START_MOVE_1:`
  - `Core/Inc/dev_SRM.h:1892: RUN_SEQ_START_MOVE_1,			// 주행, 승강 브레이크 해제시간 측정`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_TRAV_LIFT_MOVING

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:4386: if ((m_pgmEnv.SRM_RunMode >= RUN_SEQ_START_MOVE_0) && (m_pgmEnv.SRM_RunMode <= RUN_SEQ_TRAV_LIFT_MOV`
  - `Core/Src/dev_SRM.c:4446: if ((m_pgmEnv.SRM_RunMode >= RUN_SEQ_START_MOVE_0) && (m_pgmEnv.SRM_RunMode <= RUN_SEQ_TRAV_LIFT_MOV`
  - `Core/Src/dev_SRM.c:49711: case RUN_SEQ_TRAV_LIFT_MOVING:`
  - `Core/Src/dev_SRM.c:59356: m_pgmEnv.SRM_RunMode = RUN_SEQ_TRAV_LIFT_MOVING;`
  - `Core/Src/dev_SRM.c:59359: case RUN_SEQ_TRAV_LIFT_MOVING:`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_TRAV_LIFT_STABILZATION_TIME

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 이동 완료 후, 안정화 시간처리
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:59404: m_pgmEnv.SRM_RunMode = RUN_SEQ_TRAV_LIFT_STABILZATION_TIME;`
  - `Core/Src/dev_SRM.c:59451: case RUN_SEQ_TRAV_LIFT_STABILZATION_TIME:`
  - `Core/Inc/dev_SRM.h:1894: RUN_SEQ_TRAV_LIFT_STABILZATION_TIME,	// 이동 완료 후, 안정화 시간처리`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_TRAV_LIFT_AFTER_MOVE

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:49712: case RUN_SEQ_TRAV_LIFT_AFTER_MOVE:`
  - `Core/Src/dev_SRM.c:59018: m_pgmEnv.SRM_RunMode = RUN_SEQ_TRAV_LIFT_AFTER_MOVE;`
  - `Core/Src/dev_SRM.c:59152: m_pgmEnv.SRM_RunMode = RUN_SEQ_TRAV_LIFT_AFTER_MOVE;`
  - `Core/Src/dev_SRM.c:59394: m_pgmEnv.SRM_RunMode = RUN_SEQ_TRAV_LIFT_AFTER_MOVE;`
  - `Core/Src/dev_SRM.c:59409: m_pgmEnv.SRM_RunMode = RUN_SEQ_TRAV_LIFT_AFTER_MOVE;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_FORK_START

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:4497: if ((m_pgmEnv.SRM_RunMode >= RUN_SEQ_FORK_START)`
  - `Core/Src/dev_SRM.c:60401: m_pgmEnv.SRM_RunMode = RUN_SEQ_FORK_START;`
  - `Core/Src/dev_SRM.c:60407: case RUN_SEQ_FORK_START:`
  - `Core/Inc/dev_SRM.h:1897: RUN_SEQ_FORK_START,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_LOADING_START

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **값**: `30`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:60437: m_pgmEnv.SRM_RunMode = RUN_SEQ_LOADING_START;`
  - `Core/Src/dev_SRM.c:60469: case RUN_SEQ_LOADING_START:`
  - `Core/Inc/dev_SRM.h:1899: RUN_SEQ_LOADING_START = 30,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_LOADING_INTERLOCK

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: 인터록: 스테이션/CV OK 대기. 타임아웃→ERROR1_STATION_INTERLOCK_TIMEOUT. RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:60492: m_pgmEnv.SRM_RunMode = RUN_SEQ_LOADING_INTERLOCK;`
  - `Core/Src/dev_SRM.c:60497: case RUN_SEQ_LOADING_INTERLOCK:`
  - `Core/Inc/dev_SRM.h:1900: RUN_SEQ_LOADING_INTERLOCK,					//`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_LOADING_INTERLOCK_NO_USE

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: 인터록: 스테이션/CV OK 대기. 타임아웃→ERROR1_STATION_INTERLOCK_TIMEOUT. RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:60488: m_pgmEnv.SRM_RunMode = RUN_SEQ_LOADING_INTERLOCK_NO_USE;`
  - `Core/Src/dev_SRM.c:60529: case RUN_SEQ_LOADING_INTERLOCK_NO_USE:`
  - `Core/Inc/dev_SRM.h:1901: RUN_SEQ_LOADING_INTERLOCK_NO_USE,			//`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_LOADING_PRE_FORK_OUT

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:4456: else if ((m_pgmEnv.SRM_RunMode >= RUN_SEQ_LOADING_PRE_FORK_OUT) && (m_pgmEnv.SRM_RunMode <= RUN_SEQ_`
  - `Core/Src/dev_SRM.c:60516: m_pgmEnv.SRM_RunMode = RUN_SEQ_LOADING_PRE_FORK_OUT;`
  - `Core/Src/dev_SRM.c:60524: m_pgmEnv.SRM_RunMode = RUN_SEQ_LOADING_PRE_FORK_OUT;`
  - `Core/Src/dev_SRM.c:60533: m_pgmEnv.SRM_RunMode = RUN_SEQ_LOADING_PRE_FORK_OUT;`
  - `Core/Src/dev_SRM.c:60536: case RUN_SEQ_LOADING_PRE_FORK_OUT:`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_LOADING_FORK_OUT

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물 적재 Fork Out
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:49922: case RUN_SEQ_LOADING_FORK_OUT:`
  - `Core/Src/dev_SRM.c:60690: m_pgmEnv.SRM_RunMode = RUN_SEQ_LOADING_FORK_OUT;`
  - `Core/Src/dev_SRM.c:60732: case RUN_SEQ_LOADING_FORK_OUT:`
  - `Core/Inc/dev_SRM.h:1903: RUN_SEQ_LOADING_FORK_OUT,					//	화물 적재 Fork Out`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_LOADING_AFTER_FORK_OUT

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물 적재 Fork Out
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:60767: m_pgmEnv.SRM_RunMode = RUN_SEQ_LOADING_AFTER_FORK_OUT;`
  - `Core/Src/dev_SRM.c:60778: case RUN_SEQ_LOADING_AFTER_FORK_OUT:`
  - `Core/Inc/dev_SRM.h:1904: RUN_SEQ_LOADING_AFTER_FORK_OUT,				//	화물 적재 Fork Out`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_LOADING_FORK_OUT_PRE_LIFT

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:60782: m_pgmEnv.SRM_RunMode = RUN_SEQ_LOADING_FORK_OUT_PRE_LIFT;`
  - `Core/Src/dev_SRM.c:60789: m_pgmEnv.SRM_RunMode = RUN_SEQ_LOADING_FORK_OUT_PRE_LIFT;`
  - `Core/Src/dev_SRM.c:60794: case RUN_SEQ_LOADING_FORK_OUT_PRE_LIFT:`
  - `Core/Src/dev_SRM.c:62077: m_pgmEnv.SRM_RunMode = RUN_SEQ_LOADING_FORK_OUT_PRE_LIFT;`
  - `Core/Inc/dev_SRM.h:1905: RUN_SEQ_LOADING_FORK_OUT_PRE_LIFT,			//`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_LOADING_FORK_OUT_LIFT_UP

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:50422: case RUN_SEQ_LOADING_FORK_OUT_LIFT_UP:`
  - `Core/Src/dev_SRM.c:60855: m_pgmEnv.SRM_RunMode = RUN_SEQ_LOADING_FORK_OUT_LIFT_UP;`
  - `Core/Src/dev_SRM.c:60860: case RUN_SEQ_LOADING_FORK_OUT_LIFT_UP:`
  - `Core/Inc/dev_SRM.h:1906: RUN_SEQ_LOADING_FORK_OUT_LIFT_UP,			//`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_LOADING_FORK_OUT_AFTER_LIFT_UP

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:60908: m_pgmEnv.SRM_RunMode = RUN_SEQ_LOADING_FORK_OUT_AFTER_LIFT_UP;`
  - `Core/Src/dev_SRM.c:60914: case RUN_SEQ_LOADING_FORK_OUT_AFTER_LIFT_UP:`
  - `Core/Inc/dev_SRM.h:1907: RUN_SEQ_LOADING_FORK_OUT_AFTER_LIFT_UP,		//`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_LOADING_PRE_FORK_IN

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:60936: m_pgmEnv.SRM_RunMode = RUN_SEQ_LOADING_PRE_FORK_IN;`
  - `Core/Src/dev_SRM.c:60943: case RUN_SEQ_LOADING_PRE_FORK_IN:`
  - `Core/Inc/dev_SRM.h:1908: RUN_SEQ_LOADING_PRE_FORK_IN,				//`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_LOADING_FORK_IN

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:50114: case RUN_SEQ_LOADING_FORK_IN:`
  - `Core/Src/dev_SRM.c:60978: m_pgmEnv.SRM_RunMode = RUN_SEQ_LOADING_FORK_IN;`
  - `Core/Src/dev_SRM.c:60982: case RUN_SEQ_LOADING_FORK_IN:`
  - `Core/Inc/dev_SRM.h:1909: RUN_SEQ_LOADING_FORK_IN,					//`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_LOADING_AFTER_FORK_IN

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:4456: else if ((m_pgmEnv.SRM_RunMode >= RUN_SEQ_LOADING_PRE_FORK_OUT) && (m_pgmEnv.SRM_RunMode <= RUN_SEQ_`
  - `Core/Src/dev_SRM.c:61016: m_pgmEnv.SRM_RunMode = RUN_SEQ_LOADING_AFTER_FORK_IN;`
  - `Core/Src/dev_SRM.c:61027: case RUN_SEQ_LOADING_AFTER_FORK_IN:`
  - `Core/Inc/dev_SRM.h:1910: RUN_SEQ_LOADING_AFTER_FORK_IN,				//`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_LOADING_COMPLETE

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물 적재 완료, 화물 확인
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:50318: case RUN_SEQ_LOADING_COMPLETE:`
  - `Core/Src/dev_SRM.c:61043: m_pgmEnv.SRM_RunMode = RUN_SEQ_LOADING_COMPLETE;`
  - `Core/Src/dev_SRM.c:61047: case RUN_SEQ_LOADING_COMPLETE:`
  - `Core/Inc/dev_SRM.h:1911: RUN_SEQ_LOADING_COMPLETE,					// 화물 적재 완료, 화물 확인`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_UNLOADING_START

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **값**: `50`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:60443: m_pgmEnv.SRM_RunMode = RUN_SEQ_UNLOADING_START;`
  - `Core/Src/dev_SRM.c:61135: case RUN_SEQ_UNLOADING_START: // Fork UnSotre Before Delay`
  - `Core/Inc/dev_SRM.h:1913: RUN_SEQ_UNLOADING_START = 50,				//`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_UNLOADING_INTERLOCK

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: 인터록: 스테이션/CV OK 대기. 타임아웃→ERROR1_STATION_INTERLOCK_TIMEOUT. RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:61157: m_pgmEnv.SRM_RunMode = RUN_SEQ_UNLOADING_INTERLOCK;`
  - `Core/Src/dev_SRM.c:61162: case RUN_SEQ_UNLOADING_INTERLOCK:`
  - `Core/Inc/dev_SRM.h:1914: RUN_SEQ_UNLOADING_INTERLOCK,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_UNLOADING_INTERLOCK_NO_USE

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: 인터록: 스테이션/CV OK 대기. 타임아웃→ERROR1_STATION_INTERLOCK_TIMEOUT. RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:61151: m_pgmEnv.SRM_RunMode = RUN_SEQ_UNLOADING_INTERLOCK_NO_USE;`
  - `Core/Src/dev_SRM.c:61206: case RUN_SEQ_UNLOADING_INTERLOCK_NO_USE:`
  - `Core/Inc/dev_SRM.h:1915: RUN_SEQ_UNLOADING_INTERLOCK_NO_USE,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_UNLOADING_PRE_FORK_OUT

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:4461: else if ((m_pgmEnv.SRM_RunMode >= RUN_SEQ_UNLOADING_PRE_FORK_OUT) && (m_pgmEnv.SRM_RunMode <= RUN_SE`
  - `Core/Src/dev_SRM.c:61180: m_pgmEnv.SRM_RunMode = RUN_SEQ_UNLOADING_PRE_FORK_OUT;`
  - `Core/Src/dev_SRM.c:61193: m_pgmEnv.SRM_RunMode = RUN_SEQ_UNLOADING_PRE_FORK_OUT;`
  - `Core/Src/dev_SRM.c:61202: m_pgmEnv.SRM_RunMode = RUN_SEQ_UNLOADING_PRE_FORK_OUT;`
  - `Core/Src/dev_SRM.c:61213: m_pgmEnv.SRM_RunMode = RUN_SEQ_UNLOADING_PRE_FORK_OUT;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_UNLOADING_FORK_OUT

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:49934: case RUN_SEQ_UNLOADING_FORK_OUT:`
  - `Core/Src/dev_SRM.c:61413: m_pgmEnv.SRM_RunMode = RUN_SEQ_UNLOADING_FORK_OUT;`
  - `Core/Src/dev_SRM.c:61507: case RUN_SEQ_UNLOADING_FORK_OUT:`
  - `Core/Inc/dev_SRM.h:1917: RUN_SEQ_UNLOADING_FORK_OUT,					//`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_UNLOADING_AFTER_FORK_OUT

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:50031: case RUN_SEQ_UNLOADING_AFTER_FORK_OUT:`
  - `Core/Src/dev_SRM.c:61546: m_pgmEnv.SRM_RunMode = RUN_SEQ_UNLOADING_AFTER_FORK_OUT;`
  - `Core/Src/dev_SRM.c:61556: case RUN_SEQ_UNLOADING_AFTER_FORK_OUT:`
  - `Core/Inc/dev_SRM.h:1918: RUN_SEQ_UNLOADING_AFTER_FORK_OUT,			//`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_UNLOADING_FORK_OUT_PRE_LIFT

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:61560: m_pgmEnv.SRM_RunMode = RUN_SEQ_UNLOADING_FORK_OUT_PRE_LIFT;`
  - `Core/Src/dev_SRM.c:61585: case RUN_SEQ_UNLOADING_FORK_OUT_PRE_LIFT:`
  - `Core/Inc/dev_SRM.h:1919: RUN_SEQ_UNLOADING_FORK_OUT_PRE_LIFT,		//`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_UNLOADING_FORK_OUT_LIFT_DOWN

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:50423: case RUN_SEQ_UNLOADING_FORK_OUT_LIFT_DOWN:`
  - `Core/Src/dev_SRM.c:61625: m_pgmEnv.SRM_RunMode = RUN_SEQ_UNLOADING_FORK_OUT_LIFT_DOWN;`
  - `Core/Src/dev_SRM.c:61629: case RUN_SEQ_UNLOADING_FORK_OUT_LIFT_DOWN:`
  - `Core/Inc/dev_SRM.h:1920: RUN_SEQ_UNLOADING_FORK_OUT_LIFT_DOWN,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_UNLOADING_FORK_OUT_AFTER_LIFT_DOWN

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:61656: m_pgmEnv.SRM_RunMode = RUN_SEQ_UNLOADING_FORK_OUT_AFTER_LIFT_DOWN;`
  - `Core/Src/dev_SRM.c:61662: case RUN_SEQ_UNLOADING_FORK_OUT_AFTER_LIFT_DOWN:`
  - `Core/Inc/dev_SRM.h:1921: RUN_SEQ_UNLOADING_FORK_OUT_AFTER_LIFT_DOWN,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_UNLOADING_FORK_IN

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:50207: case RUN_SEQ_UNLOADING_FORK_IN:`
  - `Core/Src/dev_SRM.c:61713: m_pgmEnv.SRM_RunMode = RUN_SEQ_UNLOADING_FORK_IN;`
  - `Core/Src/dev_SRM.c:61719: case RUN_SEQ_UNLOADING_FORK_IN:`
  - `Core/Inc/dev_SRM.h:1922: RUN_SEQ_UNLOADING_FORK_IN,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_UNLOADING_AFTER_FORK_IN

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:4461: else if ((m_pgmEnv.SRM_RunMode >= RUN_SEQ_UNLOADING_PRE_FORK_OUT) && (m_pgmEnv.SRM_RunMode <= RUN_SE`
  - `Core/Src/dev_SRM.c:61755: m_pgmEnv.SRM_RunMode = RUN_SEQ_UNLOADING_AFTER_FORK_IN;`
  - `Core/Src/dev_SRM.c:61765: case RUN_SEQ_UNLOADING_AFTER_FORK_IN:`
  - `Core/Inc/dev_SRM.h:1923: RUN_SEQ_UNLOADING_AFTER_FORK_IN,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_UNLOADING_COMPLETE

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:4498: && (m_pgmEnv.SRM_RunMode >= RUN_SEQ_UNLOADING_COMPLETE))`
  - `Core/Src/dev_SRM.c:61771: m_pgmEnv.SRM_RunMode = RUN_SEQ_UNLOADING_COMPLETE;`
  - `Core/Src/dev_SRM.c:61775: case RUN_SEQ_UNLOADING_COMPLETE:`
  - `Core/Inc/dev_SRM.h:1924: RUN_SEQ_UNLOADING_COMPLETE,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_COMPLETE

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **값**: `70`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/alarm.c:1044: && (m_pgmEnv.SRM_RunMode <= RUN_SEQ_COMPLETE))`
  - `Core/Src/alarm.c:1139: && (m_pgmEnv.SRM_RunMode <= RUN_SEQ_COMPLETE))`
  - `Core/Src/alarm.c:1266: && (m_pgmEnv.SRM_RunMode <= RUN_SEQ_COMPLETE))`
  - `Core/Src/alarm.c:1628: if ((m_pgmEnv.SRM_RunMode >= RUN_SEQ_START) && (m_pgmEnv.SRM_RunMode <= RUN_SEQ_COMPLETE))`
  - `Core/Src/dev_SRM.c:59526: m_pgmEnv.SRM_RunMode = RUN_SEQ_COMPLETE;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_PLC_COM_0

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **값**: `85`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1928: RUN_SEQ_PLC_COM_0 = 85,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_PLC_COM_1

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1929: RUN_SEQ_PLC_COM_1,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_PLC_COM_2

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1930: RUN_SEQ_PLC_COM_2,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_PLC_COM_3

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1931: RUN_SEQ_PLC_COM_3,`

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

### RUN_SEQ_FORK_ORIGIN_0

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **값**: `100`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:5136: m_pgmEnv.SRM_RunMode = RUN_SEQ_FORK_ORIGIN_0;`
  - `Core/Src/dev_SRM.c:61832: m_pgmEnv.SRM_RunMode = RUN_SEQ_FORK_ORIGIN_0;`
  - `Core/Src/dev_SRM.c:63227: case RUN_SEQ_FORK_ORIGIN_0:`
  - `Core/Inc/dev_SRM.h:1939: RUN_SEQ_FORK_ORIGIN_0 = 100,	//`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_FORK_ORIGIN_1

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:49639: case RUN_SEQ_FORK_ORIGIN_1:`
  - `Core/Src/dev_SRM.c:63238: m_pgmEnv.SRM_RunMode = RUN_SEQ_FORK_ORIGIN_1;`
  - `Core/Src/dev_SRM.c:63242: case RUN_SEQ_FORK_ORIGIN_1:`
  - `Core/Inc/dev_SRM.h:1940: RUN_SEQ_FORK_ORIGIN_1,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_TRAV_ORIGIN_0

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 0
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:5140: m_pgmEnv.SRM_RunMode = RUN_SEQ_TRAV_ORIGIN_0;`
  - `Core/Src/dev_SRM.c:8056: m_pgmEnv.SRM_RunMode = RUN_SEQ_TRAV_ORIGIN_0;`
  - `Core/Src/dev_SRM.c:63271: case RUN_SEQ_TRAV_ORIGIN_0:`
  - `Core/Inc/dev_SRM.h:1942: RUN_SEQ_TRAV_ORIGIN_0,	//0`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_TRAV_ORIGIN_1

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:49644: case RUN_SEQ_TRAV_ORIGIN_1:`
  - `Core/Src/dev_SRM.c:63275: m_pgmEnv.SRM_RunMode = RUN_SEQ_TRAV_ORIGIN_1;`
  - `Core/Src/dev_SRM.c:63278: case RUN_SEQ_TRAV_ORIGIN_1:`
  - `Core/Inc/dev_SRM.h:1943: RUN_SEQ_TRAV_ORIGIN_1,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_LIFT_ORIGIN_0

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:5144: m_pgmEnv.SRM_RunMode = RUN_SEQ_LIFT_ORIGIN_0;`
  - `Core/Src/dev_SRM.c:8405: m_pgmEnv.SRM_RunMode = RUN_SEQ_LIFT_ORIGIN_0;`
  - `Core/Src/dev_SRM.c:63289: case RUN_SEQ_LIFT_ORIGIN_0:`
  - `Core/Inc/dev_SRM.h:1945: RUN_SEQ_LIFT_ORIGIN_0,	//`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_LIFT_ORIGIN_1

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:49677: case RUN_SEQ_LIFT_ORIGIN_1:`
  - `Core/Src/dev_SRM.c:63294: m_pgmEnv.SRM_RunMode = RUN_SEQ_LIFT_ORIGIN_1;`
  - `Core/Src/dev_SRM.c:63297: case RUN_SEQ_LIFT_ORIGIN_1:`
  - `Core/Inc/dev_SRM.h:1946: RUN_SEQ_LIFT_ORIGIN_1,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_LIFT_SET_HORIZONTAL_0

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **값**: `110`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:5154: m_pgmEnv.SRM_RunMode = RUN_SEQ_LIFT_SET_HORIZONTAL_0; // 110;`
  - `Core/Inc/dev_SRM.h:1948: RUN_SEQ_LIFT_SET_HORIZONTAL_0 = 110,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_LIFT_SET_HORIZONTAL_1

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1949: RUN_SEQ_LIFT_SET_HORIZONTAL_1,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_SET_AUTO_RACK_0

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **값**: `120`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1951: RUN_SEQ_SET_AUTO_RACK_0 = 120,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_SET_AUTO_RACK_1

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1952: RUN_SEQ_SET_AUTO_RACK_1,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_SET_AUTO_RACK_STOP

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **값**: `125`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1953: RUN_SEQ_SET_AUTO_RACK_STOP = 125,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_RETURN_HOME_0

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **값**: `150`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: HOME/RETURN: 원점복귀 vs 에러복귀 RunMode 혼재. grep으로 확인. RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:58914: m_pgmEnv.SRM_RunMode = RUN_SEQ_RETURN_HOME_0; //RunModeë¥¼ ì´ì¬ ì¤ë¹/ì´ëì´ ìëë¼ íë³µê`
  - `Core/Src/dev_SRM.c:61073: m_pgmEnv.SRM_RunMode = RUN_SEQ_RETURN_HOME_0;`
  - `Core/Src/dev_SRM.c:62478: m_pgmEnv.SRM_RunMode = RUN_SEQ_RETURN_HOME_0;`
  - `Core/Src/dev_SRM.c:62902: case RUN_SEQ_RETURN_HOME_0:`
  - `Core/Inc/dev_SRM.h:1955: RUN_SEQ_RETURN_HOME_0 = 150,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_RETURN_HOME_0_1

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: HOME/RETURN: 원점복귀 vs 에러복귀 RunMode 혼재. grep으로 확인. RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:4396: if ((m_pgmEnv.SRM_RunMode >= RUN_SEQ_RETURN_HOME_0_1) && (m_pgmEnv.SRM_RunMode <= RUN_SEQ_RETURN_HOM`
  - `Core/Src/dev_SRM.c:4466: if ((m_pgmEnv.SRM_RunMode >= RUN_SEQ_RETURN_HOME_0_1) && (m_pgmEnv.SRM_RunMode <= RUN_SEQ_RETURN_HOM`
  - `Core/Src/dev_SRM.c:62924: m_pgmEnv.SRM_RunMode = RUN_SEQ_RETURN_HOME_0_1;`
  - `Core/Src/dev_SRM.c:62932: case RUN_SEQ_RETURN_HOME_0_1:`
  - `Core/Src/dev_SRM.c:63006: m_pgmEnv.SRM_RunMode = RUN_SEQ_RETURN_HOME_0_1;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_RETURN_HOME_0_2

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: HOME/RETURN: 원점복귀 vs 에러복귀 RunMode 혼재. grep으로 확인. RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:62959: m_pgmEnv.SRM_RunMode = RUN_SEQ_RETURN_HOME_0_2;`
  - `Core/Src/dev_SRM.c:62984: case RUN_SEQ_RETURN_HOME_0_2:`
  - `Core/Inc/dev_SRM.h:1957: RUN_SEQ_RETURN_HOME_0_2,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_RETURN_HOME_1

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: HOME/RETURN: 원점복귀 vs 에러복귀 RunMode 혼재. grep으로 확인. RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:62926: m_pgmEnv.SRM_RunMode = RUN_SEQ_RETURN_HOME_1;`
  - `Core/Src/dev_SRM.c:62979: m_pgmEnv.SRM_RunMode = RUN_SEQ_RETURN_HOME_1;`
  - `Core/Src/dev_SRM.c:63010: case RUN_SEQ_RETURN_HOME_1:`
  - `Core/Inc/dev_SRM.h:1958: RUN_SEQ_RETURN_HOME_1,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_RETURN_HOME_MOVING

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 홈위치로 이동중
- **용도(읽는 법)**: HOME/RETURN: 원점복귀 vs 에러복귀 RunMode 혼재. grep으로 확인. RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:4396: if ((m_pgmEnv.SRM_RunMode >= RUN_SEQ_RETURN_HOME_0_1) && (m_pgmEnv.SRM_RunMode <= RUN_SEQ_RETURN_HOM`
  - `Core/Src/dev_SRM.c:4466: if ((m_pgmEnv.SRM_RunMode >= RUN_SEQ_RETURN_HOME_0_1) && (m_pgmEnv.SRM_RunMode <= RUN_SEQ_RETURN_HOM`
  - `Core/Src/dev_SRM.c:49713: case RUN_SEQ_RETURN_HOME_MOVING:`
  - `Core/Src/dev_SRM.c:63164: m_pgmEnv.SRM_RunMode = RUN_SEQ_RETURN_HOME_MOVING;`
  - `Core/Src/dev_SRM.c:63168: case RUN_SEQ_RETURN_HOME_MOVING:`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_RETURN_HOME_3

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: HOME/RETURN: 원점복귀 vs 에러복귀 RunMode 혼재. grep으로 확인. RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:49714: case RUN_SEQ_RETURN_HOME_3:`
  - `Core/Src/dev_SRM.c:63202: m_pgmEnv.SRM_RunMode = RUN_SEQ_RETURN_HOME_3;`
  - `Core/Src/dev_SRM.c:63211: case RUN_SEQ_RETURN_HOME_3:`
  - `Core/Inc/dev_SRM.h:1960: RUN_SEQ_RETURN_HOME_3,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_RETURN_HOME_4

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: HOME/RETURN: 원점복귀 vs 에러복귀 RunMode 혼재. grep으로 확인. RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1961: RUN_SEQ_RETURN_HOME_4,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_MANUAL_MOVE

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **값**: `160`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:4401: else if (m_pgmEnv.SRM_RunMode == RUN_SEQ_MANUAL_MOVE)`
  - `Core/Src/dev_SRM.c:4471: else if (m_pgmEnv.SRM_RunMode == RUN_SEQ_MANUAL_MOVE)`
  - `Core/Src/dev_SRM.c:29665: if (m_pgmEnv.SRM_RunMode == RUN_SEQ_MANUAL_MOVE)`
  - `Core/Src/dev_SRM.c:29683: if (m_pgmEnv.SRM_RunMode == RUN_SEQ_MANUAL_MOVE)`
  - `Core/Src/dev_SRM.c:29697: if (m_pgmEnv.SRM_RunMode == RUN_SEQ_MANUAL_MOVE)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_FORK_PUT_MOVE_ST_0

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **값**: `230`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1965: RUN_SEQ_FORK_PUT_MOVE_ST_0 = 230,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_FORK_PUT_MOVE_ST_1

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1966: RUN_SEQ_FORK_PUT_MOVE_ST_1,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_FORK_PUT_MOVE_ST_2

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1967: RUN_SEQ_FORK_PUT_MOVE_ST_2,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_FORK_PUT_MOVE_ST_3

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1968: RUN_SEQ_FORK_PUT_MOVE_ST_3,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_FORK_PUT_MOVE_ST_4

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1969: RUN_SEQ_FORK_PUT_MOVE_ST_4,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_FORK_PUT_MOVE_ST_5

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1970: RUN_SEQ_FORK_PUT_MOVE_ST_5,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_FORK1_CHECK_CENTER_0

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **값**: `250`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1972: RUN_SEQ_FORK1_CHECK_CENTER_0 = 250,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_FORK1_CHECK_CENTER_1

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1973: RUN_SEQ_FORK1_CHECK_CENTER_1,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_FORK2_CHECK_CENTER_0

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1974: RUN_SEQ_FORK2_CHECK_CENTER_0,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_FORK2_CHECK_CENTER_1

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1975: RUN_SEQ_FORK2_CHECK_CENTER_1,`

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

### RUN_SEQ_FORK_TEST_0

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **값**: `270`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:49705: case RUN_SEQ_FORK_TEST_0:`
  - `Core/Src/dev_SRM.c:63310: case RUN_SEQ_FORK_TEST_0:`
  - `Core/Inc/dev_SRM.h:1978: RUN_SEQ_FORK_TEST_0 = 270,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_FORK_TEST_1

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:49706: case RUN_SEQ_FORK_TEST_1:`
  - `Core/Src/dev_SRM.c:63318: m_pgmEnv.SRM_RunMode = RUN_SEQ_FORK_TEST_1;`
  - `Core/Src/dev_SRM.c:63326: case RUN_SEQ_FORK_TEST_1:`
  - `Core/Inc/dev_SRM.h:1979: RUN_SEQ_FORK_TEST_1,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_FORK_TEST_2

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1980: RUN_SEQ_FORK_TEST_2,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_FORK_TEST_3

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1981: RUN_SEQ_FORK_TEST_3,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_FORK_TEST_4

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Inc/dev_SRM.h:1982: RUN_SEQ_FORK_TEST_4,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_TRAV_SCAN_SENSOR_0

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **값**: `280`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:5674: m_pgmEnv.SRM_RunMode = RUN_SEQ_TRAV_SCAN_SENSOR_0;`
  - `Core/Src/com_tml.c:5683: if ((m_pgmEnv.SRM_RunMode == RUN_SEQ_TRAV_SCAN_SENSOR_0)`
  - `Core/Src/dev_SRM.c:63336: case RUN_SEQ_TRAV_SCAN_SENSOR_0:`
  - `Core/Inc/dev_SRM.h:1984: RUN_SEQ_TRAV_SCAN_SENSOR_0 = 280,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_TRAV_SCAN_SENSOR_1

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:5684: || (m_pgmEnv.SRM_RunMode == RUN_SEQ_TRAV_SCAN_SENSOR_1))`
  - `Core/Src/dev_SRM.c:49645: case RUN_SEQ_TRAV_SCAN_SENSOR_1:`
  - `Core/Src/dev_SRM.c:63339: m_pgmEnv.SRM_RunMode = RUN_SEQ_TRAV_SCAN_SENSOR_1;`
  - `Core/Src/dev_SRM.c:63342: case RUN_SEQ_TRAV_SCAN_SENSOR_1:`
  - `Core/Inc/dev_SRM.h:1985: RUN_SEQ_TRAV_SCAN_SENSOR_1,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_TRAV_SCAN_SENSOR_STOP

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:5686: m_pgmEnv.SRM_RunMode = RUN_SEQ_TRAV_SCAN_SENSOR_STOP;`
  - `Core/Src/dev_SRM.c:63357: case RUN_SEQ_TRAV_SCAN_SENSOR_STOP:`
  - `Core/Inc/dev_SRM.h:1986: RUN_SEQ_TRAV_SCAN_SENSOR_STOP,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_LIFT_SCAN_SENSOR_0

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **값**: `290`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:5704: m_pgmEnv.SRM_RunMode = RUN_SEQ_LIFT_SCAN_SENSOR_0;`
  - `Core/Src/com_tml.c:5713: if ((m_pgmEnv.SRM_RunMode == RUN_SEQ_LIFT_SCAN_SENSOR_0)`
  - `Core/Src/dev_SRM.c:63362: case RUN_SEQ_LIFT_SCAN_SENSOR_0:`
  - `Core/Inc/dev_SRM.h:1988: RUN_SEQ_LIFT_SCAN_SENSOR_0 = 290,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_LIFT_SCAN_SENSOR_1

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:5714: || (m_pgmEnv.SRM_RunMode == RUN_SEQ_LIFT_SCAN_SENSOR_1))`
  - `Core/Src/dev_SRM.c:49678: case RUN_SEQ_LIFT_SCAN_SENSOR_1:`
  - `Core/Src/dev_SRM.c:63365: m_pgmEnv.SRM_RunMode = RUN_SEQ_LIFT_SCAN_SENSOR_1;`
  - `Core/Src/dev_SRM.c:63368: case RUN_SEQ_LIFT_SCAN_SENSOR_1:`
  - `Core/Inc/dev_SRM.h:1989: RUN_SEQ_LIFT_SCAN_SENSOR_1,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_LIFT_SCAN_SENSOR_STOP

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:5716: m_pgmEnv.SRM_RunMode = RUN_SEQ_LIFT_SCAN_SENSOR_STOP;`
  - `Core/Src/dev_SRM.c:63383: case RUN_SEQ_LIFT_SCAN_SENSOR_STOP:`
  - `Core/Inc/dev_SRM.h:1990: RUN_SEQ_LIFT_SCAN_SENSOR_STOP,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_FORK_SCAN_SENSOR_0

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **값**: `300`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:5734: m_pgmEnv.SRM_RunMode = RUN_SEQ_FORK_SCAN_SENSOR_0;`
  - `Core/Src/com_tml.c:5743: if ((m_pgmEnv.SRM_RunMode == RUN_SEQ_FORK_SCAN_SENSOR_0)`
  - `Core/Src/dev_SRM.c:63388: case RUN_SEQ_FORK_SCAN_SENSOR_0:`
  - `Core/Inc/dev_SRM.h:1992: RUN_SEQ_FORK_SCAN_SENSOR_0 = 300,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_FORK_SCAN_SENSOR_1

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:5744: || (m_pgmEnv.SRM_RunMode == RUN_SEQ_FORK_SCAN_SENSOR_1))`
  - `Core/Src/dev_SRM.c:49640: case RUN_SEQ_FORK_SCAN_SENSOR_1:`
  - `Core/Src/dev_SRM.c:63391: m_pgmEnv.SRM_RunMode = RUN_SEQ_FORK_SCAN_SENSOR_1;`
  - `Core/Src/dev_SRM.c:63394: case RUN_SEQ_FORK_SCAN_SENSOR_1:`
  - `Core/Inc/dev_SRM.h:1993: RUN_SEQ_FORK_SCAN_SENSOR_1,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_FORK_SCAN_SENSOR_STOP

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:5746: m_pgmEnv.SRM_RunMode = RUN_SEQ_FORK_SCAN_SENSOR_STOP;`
  - `Core/Src/dev_SRM.c:63409: case RUN_SEQ_FORK_SCAN_SENSOR_STOP:`
  - `Core/Inc/dev_SRM.h:1994: RUN_SEQ_FORK_SCAN_SENSOR_STOP,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_TRAV_SETUP_MOVE_0

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **값**: `310`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:54105: m_pgmEnv.SRM_RunMode = RUN_SEQ_TRAV_SETUP_MOVE_0;`
  - `Core/Src/dev_SRM.c:54130: m_pgmEnv.SRM_RunMode = RUN_SEQ_TRAV_SETUP_MOVE_0;`
  - `Core/Src/dev_SRM.c:54229: m_pgmEnv.SRM_RunMode = RUN_SEQ_TRAV_SETUP_MOVE_0;`
  - `Core/Src/dev_SRM.c:54254: m_pgmEnv.SRM_RunMode = RUN_SEQ_TRAV_SETUP_MOVE_0;`
  - `Core/Src/dev_SRM.c:63414: case RUN_SEQ_TRAV_SETUP_MOVE_0:`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_TRAV_SETUP_MOVE_1

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:4391: else if (m_pgmEnv.SRM_RunMode == RUN_SEQ_TRAV_SETUP_MOVE_1)`
  - `Core/Src/dev_SRM.c:63417: m_pgmEnv.SRM_RunMode = RUN_SEQ_TRAV_SETUP_MOVE_1;`
  - `Core/Src/dev_SRM.c:63420: case RUN_SEQ_TRAV_SETUP_MOVE_1:`
  - `Core/Inc/dev_SRM.h:1997: RUN_SEQ_TRAV_SETUP_MOVE_1,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_TRAV_SETUP_MOVE_STOP

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:63431: m_pgmEnv.SRM_RunMode = RUN_SEQ_TRAV_SETUP_MOVE_STOP;`
  - `Core/Src/dev_SRM.c:63435: case RUN_SEQ_TRAV_SETUP_MOVE_STOP:`
  - `Core/Inc/dev_SRM.h:1998: RUN_SEQ_TRAV_SETUP_MOVE_STOP,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_LIFT_SETUP_MOVE_0

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **값**: `330`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:54353: m_pgmEnv.SRM_RunMode = RUN_SEQ_LIFT_SETUP_MOVE_0;`
  - `Core/Src/dev_SRM.c:54380: m_pgmEnv.SRM_RunMode = RUN_SEQ_LIFT_SETUP_MOVE_0;`
  - `Core/Src/dev_SRM.c:54409: m_pgmEnv.SRM_RunMode = RUN_SEQ_LIFT_SETUP_MOVE_0;`
  - `Core/Src/dev_SRM.c:54503: m_pgmEnv.SRM_RunMode = RUN_SEQ_LIFT_SETUP_MOVE_0;`
  - `Core/Src/dev_SRM.c:54530: m_pgmEnv.SRM_RunMode = RUN_SEQ_LIFT_SETUP_MOVE_0;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_LIFT_SETUP_MOVE_1

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:4451: else if (m_pgmEnv.SRM_RunMode == RUN_SEQ_LIFT_SETUP_MOVE_1)`
  - `Core/Src/dev_SRM.c:63443: m_pgmEnv.SRM_RunMode = RUN_SEQ_LIFT_SETUP_MOVE_1;`
  - `Core/Src/dev_SRM.c:63446: case RUN_SEQ_LIFT_SETUP_MOVE_1:`
  - `Core/Inc/dev_SRM.h:2001: RUN_SEQ_LIFT_SETUP_MOVE_1,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_LIFT_SETUP_MOVE_STOP

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:63457: m_pgmEnv.SRM_RunMode = RUN_SEQ_LIFT_SETUP_MOVE_STOP;`
  - `Core/Src/dev_SRM.c:63461: case RUN_SEQ_LIFT_SETUP_MOVE_STOP:`
  - `Core/Inc/dev_SRM.h:2002: RUN_SEQ_LIFT_SETUP_MOVE_STOP,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_FORK_SETUP_MOVE_0

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **값**: `340`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:54622: m_pgmEnv.SRM_RunMode = RUN_SEQ_FORK_SETUP_MOVE_0;`
  - `Core/Src/dev_SRM.c:63466: case RUN_SEQ_FORK_SETUP_MOVE_0:`
  - `Core/Inc/dev_SRM.h:2004: RUN_SEQ_FORK_SETUP_MOVE_0 = 340,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_FORK_SETUP_MOVE_1

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:63469: m_pgmEnv.SRM_RunMode = RUN_SEQ_FORK_SETUP_MOVE_1;`
  - `Core/Src/dev_SRM.c:63472: case RUN_SEQ_FORK_SETUP_MOVE_1:`
  - `Core/Inc/dev_SRM.h:2005: RUN_SEQ_FORK_SETUP_MOVE_1,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_FORK_SETUP_MOVE_STOP

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:63483: m_pgmEnv.SRM_RunMode = RUN_SEQ_FORK_SETUP_MOVE_STOP;`
  - `Core/Src/dev_SRM.c:63487: case RUN_SEQ_FORK_SETUP_MOVE_STOP:`
  - `Core/Inc/dev_SRM.h:2006: RUN_SEQ_FORK_SETUP_MOVE_STOP,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_STICKY_START

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **값**: `400`
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/alarm.c:1143: else if ((m_pgmEnv.SRM_RunMode >= RUN_SEQ_STICKY_START)`
  - `Core/Src/alarm.c:1270: else if ((m_pgmEnv.SRM_RunMode >= RUN_SEQ_STICKY_START)`
  - `Core/Src/dev_SRM.c:60449: m_pgmEnv.SRM_RunMode = RUN_SEQ_STICKY_START;`
  - `Core/Src/dev_SRM.c:61852: case RUN_SEQ_STICKY_START:`
  - `Core/Inc/dev_SRM.h:2008: RUN_SEQ_STICKY_START = 400,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_STICKY_PRE_FORK_OUT

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:61869: m_pgmEnv.SRM_RunMode = RUN_SEQ_STICKY_PRE_FORK_OUT;`
  - `Core/Src/dev_SRM.c:61872: case RUN_SEQ_STICKY_PRE_FORK_OUT:`
  - `Core/Inc/dev_SRM.h:2009: RUN_SEQ_STICKY_PRE_FORK_OUT,				//`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_STICKY_FORK_OUT

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물 적재 Fork Out
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:61998: m_pgmEnv.SRM_RunMode = RUN_SEQ_STICKY_FORK_OUT;`
  - `Core/Src/dev_SRM.c:62018: case RUN_SEQ_STICKY_FORK_OUT:`
  - `Core/Inc/dev_SRM.h:2010: RUN_SEQ_STICKY_FORK_OUT,					//	화물 적재 Fork Out`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_STICKY_AFTER_FORK_OUT

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물 적재 Fork Out
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:62053: m_pgmEnv.SRM_RunMode = RUN_SEQ_STICKY_AFTER_FORK_OUT;`
  - `Core/Src/dev_SRM.c:62064: case RUN_SEQ_STICKY_AFTER_FORK_OUT:`
  - `Core/Inc/dev_SRM.h:2011: RUN_SEQ_STICKY_AFTER_FORK_OUT,				//	화물 적재 Fork Out`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_STICKY_FORK_OUT_PRE_LIFT_UP

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:62070: m_pgmEnv.SRM_RunMode = RUN_SEQ_STICKY_FORK_OUT_PRE_LIFT_UP;`
  - `Core/Src/dev_SRM.c:62082: case RUN_SEQ_STICKY_FORK_OUT_PRE_LIFT_UP:`
  - `Core/Inc/dev_SRM.h:2012: RUN_SEQ_STICKY_FORK_OUT_PRE_LIFT_UP,		//`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_STICKY_FORK_OUT_LIFT_UP

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:62144: m_pgmEnv.SRM_RunMode = RUN_SEQ_STICKY_FORK_OUT_LIFT_UP;`
  - `Core/Src/dev_SRM.c:62149: case RUN_SEQ_STICKY_FORK_OUT_LIFT_UP:`
  - `Core/Inc/dev_SRM.h:2013: RUN_SEQ_STICKY_FORK_OUT_LIFT_UP,			//`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_STICKY_FORK_OUT_AFTER_LIFT_UP

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:62198: m_pgmEnv.SRM_RunMode = RUN_SEQ_STICKY_FORK_OUT_AFTER_LIFT_UP;`
  - `Core/Src/dev_SRM.c:62204: case RUN_SEQ_STICKY_FORK_OUT_AFTER_LIFT_UP:`
  - `Core/Inc/dev_SRM.h:2014: RUN_SEQ_STICKY_FORK_OUT_AFTER_LIFT_UP,		//`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_STICKY_FORK_OUT_PRE_LIFT_DOWN

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:62224: m_pgmEnv.SRM_RunMode = RUN_SEQ_STICKY_FORK_OUT_PRE_LIFT_DOWN;`
  - `Core/Src/dev_SRM.c:62231: case RUN_SEQ_STICKY_FORK_OUT_PRE_LIFT_DOWN:`
  - `Core/Inc/dev_SRM.h:2015: RUN_SEQ_STICKY_FORK_OUT_PRE_LIFT_DOWN,		//`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_STICKY_FORK_OUT_LIFT_DOWN

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:62274: m_pgmEnv.SRM_RunMode = RUN_SEQ_STICKY_FORK_OUT_LIFT_DOWN;`
  - `Core/Src/dev_SRM.c:62279: case RUN_SEQ_STICKY_FORK_OUT_LIFT_DOWN:`
  - `Core/Inc/dev_SRM.h:2016: RUN_SEQ_STICKY_FORK_OUT_LIFT_DOWN,			//`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_STICKY_FORK_OUT_AFTER_LIFT_DOWN

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:62306: m_pgmEnv.SRM_RunMode = RUN_SEQ_STICKY_FORK_OUT_AFTER_LIFT_DOWN;`
  - `Core/Src/dev_SRM.c:62312: case RUN_SEQ_STICKY_FORK_OUT_AFTER_LIFT_DOWN:`
  - `Core/Inc/dev_SRM.h:2017: RUN_SEQ_STICKY_FORK_OUT_AFTER_LIFT_DOWN,	//`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_STICKY_PRE_FORK_IN

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물 이재 Fork In
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:62341: m_pgmEnv.SRM_RunMode = RUN_SEQ_STICKY_PRE_FORK_IN;`
  - `Core/Src/dev_SRM.c:62348: case RUN_SEQ_STICKY_PRE_FORK_IN:`
  - `Core/Inc/dev_SRM.h:2018: RUN_SEQ_STICKY_PRE_FORK_IN,					//	화물 이재 Fork In`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_STICKY_FORK_IN

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물 이재 Fork In
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:62383: m_pgmEnv.SRM_RunMode = RUN_SEQ_STICKY_FORK_IN;`
  - `Core/Src/dev_SRM.c:62387: case RUN_SEQ_STICKY_FORK_IN:`
  - `Core/Inc/dev_SRM.h:2019: RUN_SEQ_STICKY_FORK_IN,						//	화물 이재 Fork In`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_STICKY_AFTER_FORK_IN

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:62421: m_pgmEnv.SRM_RunMode = RUN_SEQ_STICKY_AFTER_FORK_IN;`
  - `Core/Src/dev_SRM.c:62432: case RUN_SEQ_STICKY_AFTER_FORK_IN:`
  - `Core/Inc/dev_SRM.h:2020: RUN_SEQ_STICKY_AFTER_FORK_IN,				//`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### RUN_SEQ_STICKY_COMPLETE

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **원문 주석**: 화물 없는지 확인
- **용도(읽는 법)**: RunMode: SRM_Machine_Run_Process switch case.
- **코드 참조 예**:
  - `Core/Src/alarm.c:1144: && (m_pgmEnv.SRM_RunMode <= RUN_SEQ_STICKY_COMPLETE))`
  - `Core/Src/alarm.c:1271: && (m_pgmEnv.SRM_RunMode <= RUN_SEQ_STICKY_COMPLETE))`
  - `Core/Src/dev_SRM.c:62448: m_pgmEnv.SRM_RunMode = RUN_SEQ_STICKY_COMPLETE;`
  - `Core/Src/dev_SRM.c:62452: case RUN_SEQ_STICKY_COMPLETE:`
  - `Core/Inc/dev_SRM.h:2021: RUN_SEQ_STICKY_COMPLETE,					// 	화물 없는지 확인`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MAX_RUN_MODE_SEQ

- **종류**: enum `enumSRM_RUN_SEQ` 멤버
- **정의 위치**: `Core/Inc/dev_SRM.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:743: if (pCtrl->Value < MAX_RUN_MODE_SEQ)`
  - `Core/Inc/dev_SRM.h:2023: MAX_RUN_MODE_SEQ,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

