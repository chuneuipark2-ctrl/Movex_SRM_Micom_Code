# Vol.05 — 기타 Enum (4)

> 생성일: 2026-06-16 | MX SRM App Ver 4.4 | 소스 미수정

기타 enumeration.

---

### FORK_VEL_AUTO_L

- **종류**: enum `enumFORK_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:5228: case FORK_VEL_AUTO_L:`
  - `Core/Src/SRM_Parameter.c:5341: case FORK_VEL_AUTO_L:`
  - `Core/Src/dev_SRM.c:2942: || (VelType == FORK_VEL_AUTO_L) \`
  - `Core/Src/dev_SRM.c:3326: || (VelType == FORK_VEL_AUTO_L) \`
  - `Core/Src/dev_SRM.c:3630: if ((VelType == FORK_VEL_AUTO_H) || (VelType == FORK_VEL_AUTO_M) || (VelType == FORK_VEL_AUTO_L))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_VEL_MAN_M

- **종류**: enum `enumFORK_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:5271: case FORK_VEL_MAN_M:`
  - `Core/Src/SRM_Parameter.c:5383: case FORK_VEL_MAN_M:`
  - `Core/Src/dev_SRM.c:3646: else if ((VelType == FORK_VEL_MAN_M) || (VelType == FORK_VEL_MAN_L) || (VelType == FORK_VEL_ORIGIN))`
  - `Core/Src/dev_SRM.c:33100: static INT08U s_ActVelocity = FORK_VEL_MAN_M;`
  - `Core/Src/dev_SRM.c:33244: s_ActVelocity = FORK_VEL_MAN_M;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_VEL_MAN_L

- **종류**: enum `enumFORK_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:5270: case FORK_VEL_MAN_L:`
  - `Core/Src/SRM_Parameter.c:5361: case FORK_VEL_MAN_L:`
  - `Core/Src/dev_SRM.c:3646: else if ((VelType == FORK_VEL_MAN_M) || (VelType == FORK_VEL_MAN_L) || (VelType == FORK_VEL_ORIGIN))`
  - `Core/Src/dev_SRM.c:33248: s_ActVelocity = FORK_VEL_MAN_L;`
  - `Core/Src/dev_SRM.c:33715: s_ActVelocity = FORK_VEL_MAN_L;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_VEL_FORCE

- **종류**: enum `enumFORK_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:5248: case FORK_VEL_FORCE:`
  - `Core/Src/SRM_Parameter.c:5384: case FORK_VEL_FORCE:`
  - `Core/Src/SRM_Parameter.c:6201: if (m_ExtSEnv2.ForkDrive.Vel[FORK_VEL_FORCE].Spd > MAX_FORK_VEL_MAN)`
  - `Core/Src/SRM_Parameter.c:6203: m_ExtSEnv2.ForkDrive.Vel[FORK_VEL_FORCE].Spd = MAX_FORK_VEL_MAN;`
  - `Core/Src/dev_SRM.c:33709: s_ActVelocity = FORK_VEL_FORCE;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_VEL_CREEP

- **종류**: enum `enumFORK_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:5286: case FORK_VEL_CREEP:`
  - `Core/Src/SRM_Parameter.c:5399: case FORK_VEL_CREEP:`
  - `Core/Src/dev_SRM.c:2982: if (VelType == FORK_VEL_CREEP)`
  - `Core/Src/dev_SRM.c:3023: if (VelType == FORK_VEL_CREEP)`
  - `Core/Src/dev_SRM.c:3366: if (VelType == FORK_VEL_CREEP)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_VEL_ORIGIN

- **종류**: enum `enumFORK_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:5272: case FORK_VEL_ORIGIN:`
  - `Core/Src/SRM_Parameter.c:5385: case FORK_VEL_ORIGIN:`
  - `Core/Src/dev_SRM.c:3646: else if ((VelType == FORK_VEL_MAN_M) || (VelType == FORK_VEL_MAN_L) || (VelType == FORK_VEL_ORIGIN))`
  - `Core/Src/dev_SRM.c:8890: Motor_Manual_Fork1(JOG_FORK_RIGHT, FORK_VEL_ORIGIN);`
  - `Core/Src/dev_SRM.c:8898: Motor_Manual_Fork1(JOG_FORK_LEFT, FORK_VEL_ORIGIN);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_VEL_EMG

- **종류**: enum `enumFORK_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:5297: case FORK_VEL_EMG:`
  - `Core/Src/SRM_Parameter.c:5410: case FORK_VEL_EMG:`
  - `Core/Src/dev_SRM.c:3640: else if (VelType == FORK_VEL_EMG)`
  - `Core/Src/dev_SRM.c:3655: if (VelType != FORK_VEL_EMG)`
  - `Core/Src/dev_SRM.c:3999: memcpy((INT08U*)&StopVelocity, (INT08U*)&m_ExtSEnv2.ForkDrive.Vel[FORK_VEL_EMG], sizeof(UnitVelocity`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_VEL_AUTO_DEC_1

- **종류**: enum `enumFORK_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:5242: case FORK_VEL_AUTO_DEC_1:`
  - `Core/Src/SRM_Parameter.c:5355: case FORK_VEL_AUTO_DEC_1:`
  - `Core/Src/dev_SRM.c:2943: || (VelType == FORK_VEL_AUTO_DEC_1) || (VelType == FORK_VEL_AUTO_DEC_2))`
  - `Core/Src/dev_SRM.c:3327: || (VelType == FORK_VEL_AUTO_DEC_1) || (VelType == FORK_VEL_AUTO_DEC_2))`
  - `Core/Src/dev_SRM.c:3635: else if ((VelType == FORK_VEL_AUTO_DEC_1) || (VelType == FORK_VEL_AUTO_DEC_2))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_VEL_AUTO_DEC_2

- **종류**: enum `enumFORK_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:5243: case FORK_VEL_AUTO_DEC_2:`
  - `Core/Src/SRM_Parameter.c:5356: case FORK_VEL_AUTO_DEC_2:`
  - `Core/Src/dev_SRM.c:2943: || (VelType == FORK_VEL_AUTO_DEC_1) || (VelType == FORK_VEL_AUTO_DEC_2))`
  - `Core/Src/dev_SRM.c:3327: || (VelType == FORK_VEL_AUTO_DEC_1) || (VelType == FORK_VEL_AUTO_DEC_2))`
  - `Core/Src/dev_SRM.c:3635: else if ((VelType == FORK_VEL_AUTO_DEC_1) || (VelType == FORK_VEL_AUTO_DEC_2))`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_VELOCITY_SPARE_1

- **종류**: enum `enumFORK_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2127: FORK_VELOCITY_SPARE_1,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_VELOCITY_SPARE_2

- **종류**: enum `enumFORK_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2128: FORK_VELOCITY_SPARE_2,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_VELOCITY_SPARE_3

- **종류**: enum `enumFORK_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2129: FORK_VELOCITY_SPARE_3,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_VELOCITY_SPARE_4

- **종류**: enum `enumFORK_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2130: FORK_VELOCITY_SPARE_4,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### FORK_VELOCITY_SPARE_5

- **종류**: enum `enumFORK_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2131: FORK_VELOCITY_SPARE_5,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MAX_FORK_VELOCITY_CNT

- **종류**: enum `enumFORK_VELOCITY_TYPE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/com_tml.c:5210: for (i = 0; i < MAX_FORK_VELOCITY_CNT; i++)`
  - `Core/Src/com_tml.c:5242: for (i = 0; i < MAX_FORK_VELOCITY_CNT; i++)`
  - `Core/Src/dev_SRM.c:37713: if (vel_type >= MAX_FORK_VELOCITY_CNT)  vel_type = FORK_VEL_MAN_L;`
  - `Core/Src/dev_SRM.c:38064: if (vel_type >= MAX_FORK_VELOCITY_CNT)  vel_type = FORK_VEL_MAN_L;`
  - `Core/Src/dev_SRM.c:38323: if (vel_type >= MAX_FORK_VELOCITY_CNT)  vel_type = FORK_VEL_MAN_L;`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DRIVE_VELOCITY_AUTO_H

- **종류**: enum `enumDRIVE_VELOCITY_MODE` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2136: DRIVE_VELOCITY_AUTO_H = 0,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DRIVE_VELOCITY_AUTO_M

- **종류**: enum `enumDRIVE_VELOCITY_MODE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2137: DRIVE_VELOCITY_AUTO_M,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DRIVE_VELOCITY_AUTO_L

- **종류**: enum `enumDRIVE_VELOCITY_MODE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:3684: nInitParam.Home_Spd_Mode = DRIVE_VELOCITY_AUTO_L;`
  - `Core/Src/SRM_Parameter.c:3687: nInitParam.Maintenance_Spd_Mode = DRIVE_VELOCITY_AUTO_L;`
  - `Core/Src/SRM_Parameter.c:5059: nInitParam.Home_Spd_Mode = DRIVE_VELOCITY_AUTO_L;`
  - `Core/Src/SRM_Parameter.c:5062: nInitParam.Maintenance_Spd_Mode = DRIVE_VELOCITY_AUTO_L;`
  - `Core/Inc/User_Define.h:2138: DRIVE_VELOCITY_AUTO_L,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DRIVE_VELOCITY_MANUAL_M

- **종류**: enum `enumDRIVE_VELOCITY_MODE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2139: DRIVE_VELOCITY_MANUAL_M,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DRIVE_VELOCITY_MANUAL_L

- **종류**: enum `enumDRIVE_VELOCITY_MODE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2140: DRIVE_VELOCITY_MANUAL_L,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DRIVE_VELOCITY_CREEP

- **종류**: enum `enumDRIVE_VELOCITY_MODE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2141: DRIVE_VELOCITY_CREEP,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DRIVE_VELOCITY_ORIGIN

- **종류**: enum `enumDRIVE_VELOCITY_MODE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:4243: if (pSetting->Home_Spd_Mode > DRIVE_VELOCITY_ORIGIN)`
  - `Core/Src/SRM_Parameter.c:4319: if (pSetting->Home_Spd_Mode > DRIVE_VELOCITY_ORIGIN)`
  - `Core/Src/SRM_Parameter.c:4398: if (pSetting->Maintenance_Spd_Mode > DRIVE_VELOCITY_ORIGIN)`
  - `Core/Src/SRM_Parameter.c:4462: if (pSetting->Maintenance_Spd_Mode > DRIVE_VELOCITY_ORIGIN)`
  - `Core/Inc/User_Define.h:2142: DRIVE_VELOCITY_ORIGIN,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MAX_DRIVE_VELOCITY_CNT

- **종류**: enum `enumDRIVE_VELOCITY_MODE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2143: MAX_DRIVE_VELOCITY_CNT`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DECEL_MODE_NOT_USE

- **종류**: enum `enumDECEL_RANGE_MODE` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:3690: nInitParam.DecelRange1_Mode = DECEL_MODE_NOT_USE;`
  - `Core/Src/SRM_Parameter.c:3691: nInitParam.DecelRange2_Mode = DECEL_MODE_NOT_USE;`
  - `Core/Src/SRM_Parameter.c:5065: nInitParam.DecelRange1_Mode = DECEL_MODE_NOT_USE;`
  - `Core/Src/SRM_Parameter.c:5066: nInitParam.DecelRange2_Mode = DECEL_MODE_NOT_USE;`
  - `Core/Inc/User_Define.h:2147: DECEL_MODE_NOT_USE = 0,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DECEL_VELOCITY1_DRIVE

- **종류**: enum `enumDECEL_RANGE_MODE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2148: DECEL_VELOCITY1_DRIVE,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DECEL_VELOCITY2_DRIVE

- **종류**: enum `enumDECEL_RANGE_MODE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2149: DECEL_VELOCITY2_DRIVE,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DECEL_VELOCITY1_OVERSPEED

- **종류**: enum `enumDECEL_RANGE_MODE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2150: DECEL_VELOCITY1_OVERSPEED,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DECEL_VELOCITY2_OVERSPEED

- **종류**: enum `enumDECEL_RANGE_MODE` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:4532: if (pSetting->DecelRange1_Mode > DECEL_VELOCITY2_OVERSPEED)`
  - `Core/Src/SRM_Parameter.c:4537: if (pSetting->DecelRange2_Mode > DECEL_VELOCITY2_OVERSPEED)`
  - `Core/Src/SRM_Parameter.c:4554: if (pSetting->DecelRange1_Mode > DECEL_VELOCITY2_OVERSPEED)`
  - `Core/Src/SRM_Parameter.c:4559: if (pSetting->DecelRange2_Mode > DECEL_VELOCITY2_OVERSPEED)`
  - `Core/Inc/User_Define.h:2151: DECEL_VELOCITY2_OVERSPEED,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DELAY_PREFORE_MOVE

- **종류**: enum `enumDELAY_TIME` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:51599: if (nTimerIndex == DELAY_PREFORE_MOVE)`
  - `Core/Src/dev_SRM.c:51817: m_St.MaintananceInfo.load_travel_lift_moving_before_delay = m_ExtSEnv2.CtrParam.Loading_Delay.mSetVa`
  - `Core/Src/dev_SRM.c:51826: m_St.MaintananceInfo.unload_travel_lift_moving_before_delay = m_ExtSEnv2.CtrParam.Unloading_Delay.mS`
  - `Core/Src/dev_SRM.c:58984: s_Delay_Time = Read_DelayTime(m_WorkData[s_WorkInx].ForkAct, DELAY_PREFORE_MOVE);`
  - `Core/Src/dev_SRM.c:59031: s_Delay_Time = Read_DelayTime(m_WorkData[s_WorkInx].ForkAct, DELAY_PREFORE_MOVE);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DELAY_AFTER_MOVE

- **종류**: enum `enumDELAY_TIME` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:51603: else if (nTimerIndex == DELAY_AFTER_MOVE)`
  - `Core/Src/dev_SRM.c:51641: if (nTimerIndex == DELAY_AFTER_MOVE)`
  - `Core/Src/dev_SRM.c:51818: m_St.MaintananceInfo.load_travel_lift_moving_after_delay = m_ExtSEnv2.CtrParam.Loading_Delay.mSetVal`
  - `Core/Src/dev_SRM.c:51827: m_St.MaintananceInfo.unload_travel_lift_moving_after_delay = m_ExtSEnv2.CtrParam.Unloading_Delay.mSe`
  - `Core/Src/dev_SRM.c:59393: s_Delay_Time = Read_DelayTime(m_WorkData[s_WorkInx].ForkAct, DELAY_AFTER_MOVE);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DELAY_BEFORE_FORK_OUT

- **종류**: enum `enumDELAY_TIME` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:51616: else if (nTimerIndex == DELAY_BEFORE_FORK_OUT)`
  - `Core/Src/dev_SRM.c:51819: m_St.MaintananceInfo.load_fork_extend_moving_before_delay = m_ExtSEnv2.CtrParam.Loading_Delay.mSetVa`
  - `Core/Src/dev_SRM.c:51828: m_St.MaintananceInfo.unload_fork_extend_moving_before_delay = m_ExtSEnv2.CtrParam.Unloading_Delay.mS`
  - `Core/Src/dev_SRM.c:60513: s_Delay_Time = Read_DelayTime(m_WorkData[s_WorkInx].ForkAct, DELAY_BEFORE_FORK_OUT);`
  - `Core/Src/dev_SRM.c:60521: s_Delay_Time = Read_DelayTime(m_WorkData[s_WorkInx].ForkAct, DELAY_BEFORE_FORK_OUT);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DELAY_AFTER_FORK_OUT

- **종류**: enum `enumDELAY_TIME` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:2536: nInitParam.Loading_Delay.mSetValue[DELAY_AFTER_FORK_OUT] = 10;		// 0.1s, Unit 0.01 sec`
  - `Core/Src/SRM_Parameter.c:2537: nInitParam.Unloading_Delay.mSetValue[DELAY_AFTER_FORK_OUT] = 10;	// 0.1s, Unit 0.01 sec`
  - `Core/Src/dev_SRM.c:41683: s_Delay_Time = Read_DelayTime(pWorkData->ForkAct, DELAY_AFTER_FORK_OUT);`
  - `Core/Src/dev_SRM.c:42631: s_Delay_Time = Read_DelayTime(pWorkData->ForkAct, DELAY_AFTER_FORK_OUT);`
  - `Core/Src/dev_SRM.c:51621: else if (nTimerIndex == DELAY_AFTER_FORK_OUT)`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DELAY_BEFORE_FORK_OUT_LIFT

- **종류**: enum `enumDELAY_TIME` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:51607: else if (nTimerIndex == DELAY_BEFORE_FORK_OUT_LIFT)`
  - `Core/Src/dev_SRM.c:51821: m_St.MaintananceInfo.load_forking_lift_moving_before_delay = m_ExtSEnv2.CtrParam.Loading_Delay.mSetV`
  - `Core/Src/dev_SRM.c:51830: m_St.MaintananceInfo.unload_forking_lift_moving_before_delay = m_ExtSEnv2.CtrParam.Unloading_Delay.m`
  - `Core/Src/dev_SRM.c:60779: s_Delay_Time = Read_DelayTime(m_WorkData[s_WorkInx].ForkAct, DELAY_BEFORE_FORK_OUT_LIFT);`
  - `Core/Src/dev_SRM.c:60786: s_Delay_Time = Read_DelayTime(m_WorkData[s_WorkInx].ForkAct, DELAY_BEFORE_FORK_OUT_LIFT);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DELAY_AFTER_FORK_OUT_LIFT

- **종류**: enum `enumDELAY_TIME` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:51611: else if (nTimerIndex == DELAY_AFTER_FORK_OUT_LIFT)`
  - `Core/Src/dev_SRM.c:51822: m_St.MaintananceInfo.load_forking_lift_moving_after_delay = m_ExtSEnv2.CtrParam.Loading_Delay.mSetVa`
  - `Core/Src/dev_SRM.c:51831: m_St.MaintananceInfo.unload_forking_lift_moving_after_delay = m_ExtSEnv2.CtrParam.Unloading_Delay.mS`
  - `Core/Src/dev_SRM.c:60905: s_Delay_Time = Read_DelayTime(m_WorkData[s_WorkInx].ForkAct, DELAY_AFTER_FORK_OUT_LIFT);`
  - `Core/Src/dev_SRM.c:61653: s_Delay_Time = Read_DelayTime(m_WorkData[s_WorkInx].ForkAct, DELAY_AFTER_FORK_OUT_LIFT);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DELAY_BEFORE_FORK_CENTER

- **종류**: enum `enumDELAY_TIME` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/dev_SRM.c:51625: else if (nTimerIndex == DELAY_BEFORE_FORK_CENTER)`
  - `Core/Src/dev_SRM.c:51823: m_St.MaintananceInfo.load_fork_fold_moving_before_delay = m_ExtSEnv2.CtrParam.Loading_Delay.mSetValu`
  - `Core/Src/dev_SRM.c:51832: m_St.MaintananceInfo.unload_fork_fold_moving_before_delay = m_ExtSEnv2.CtrParam.Unloading_Delay.mSet`
  - `Core/Src/dev_SRM.c:60933: s_Delay_Time = Read_DelayTime(m_WorkData[s_WorkInx].ForkAct, DELAY_BEFORE_FORK_CENTER);`
  - `Core/Src/dev_SRM.c:62330: s_Over_Time = Read_DelayTime(m_WorkData[s_WorkInx].ForkAct, DELAY_BEFORE_FORK_CENTER);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DELAY_AFTER_FORK_CENTER

- **종류**: enum `enumDELAY_TIME` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:2305: for (i = 0; i <= DELAY_AFTER_FORK_CENTER; i++)`
  - `Core/Src/SRM_Parameter.c:2321: for (i = 0; i <= DELAY_AFTER_FORK_CENTER; i++)`
  - `Core/Src/SRM_Parameter.c:2530: for (i = 0; i <= DELAY_AFTER_FORK_CENTER; i++)`
  - `Core/Src/SRM_Parameter.c:2539: nInitParam.Loading_Delay.mSetValue[DELAY_AFTER_FORK_CENTER] = 10;		// 0.1s, Unit 0.01 sec`
  - `Core/Src/SRM_Parameter.c:2540: nInitParam.Unloading_Delay.mSetValue[DELAY_AFTER_FORK_CENTER] = 10;	// 0.1s, Unit 0.01 sec`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DELAY_TIME_SPARE8

- **종류**: enum `enumDELAY_TIME` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2177: DELAY_TIME_SPARE8,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DELAY_TIME_SPARE9

- **종류**: enum `enumDELAY_TIME` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2178: DELAY_TIME_SPARE9,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DELAY_TIME_SPARE10

- **종류**: enum `enumDELAY_TIME` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2179: DELAY_TIME_SPARE10,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DELAY_TIME_SPARE11

- **종류**: enum `enumDELAY_TIME` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2180: DELAY_TIME_SPARE11,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DELAY_TIME_SPARE12

- **종류**: enum `enumDELAY_TIME` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2181: DELAY_TIME_SPARE12,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DELAY_TIME_SPARE13

- **종류**: enum `enumDELAY_TIME` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2182: DELAY_TIME_SPARE13,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DELAY_TIME_SPARE14

- **종류**: enum `enumDELAY_TIME` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2183: DELAY_TIME_SPARE14,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DELAY_TIME_SPARE15

- **종류**: enum `enumDELAY_TIME` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2184: DELAY_TIME_SPARE15,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DELAY_TIME_SPARE16

- **종류**: enum `enumDELAY_TIME` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2185: DELAY_TIME_SPARE16,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DELAY_TIME_SPARE17

- **종류**: enum `enumDELAY_TIME` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2186: DELAY_TIME_SPARE17,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DELAY_TIME_SPARE18

- **종류**: enum `enumDELAY_TIME` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2187: DELAY_TIME_SPARE18,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DELAY_TIME_SPARE19

- **종류**: enum `enumDELAY_TIME` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2188: DELAY_TIME_SPARE19,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MAX_DELAY_TIME_CNT

- **종류**: enum `enumDELAY_TIME` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2189: MAX_DELAY_TIME_CNT`
  - `Core/Inc/User_Define.h:2194: INT16U mSetValue[MAX_DELAY_TIME_CNT];`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SETUP_TIMEOUT_TRAVEL_ORIGIN

- **종류**: enum `enumSETUP_TIMEOUT` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: ì£¼í ìì ì¤ì 
- **용도(읽는 법)**: 헤더 주석: ì£¼í ìì ì¤ì 
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:2549: nInitParam.SetupTimeOut.mSetValue[SETUP_TIMEOUT_TRAVEL_ORIGIN] = 60000;		// 600.00s, Unit 0.01 sec`
  - `Core/Src/dev_SRM.c:8088: if (m_ExtSEnv2.CtrParam.SetupTimeOut.mSetValue[SETUP_TIMEOUT_TRAVEL_ORIGIN])`
  - `Core/Src/dev_SRM.c:8090: if (getCalcTimer1ms(s_Over_timer) > (m_ExtSEnv2.CtrParam.SetupTimeOut.mSetValue[SETUP_TIMEOUT_TRAVEL`
  - `Core/Inc/User_Define.h:2199: SETUP_TIMEOUT_TRAVEL_ORIGIN = 0,	// ì£¼í ìì ì¤ì `

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SETUP_TIMEOUT_LIFT_ORIGIN

- **종류**: enum `enumSETUP_TIMEOUT` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: ì¹ê° ìì ì¤ì 
- **용도(읽는 법)**: 헤더 주석: ì¹ê° ìì ì¤ì 
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:2550: nInitParam.SetupTimeOut.mSetValue[SETUP_TIMEOUT_LIFT_ORIGIN] = 30000;		// 300.00s, Unit 0.01 sec`
  - `Core/Src/dev_SRM.c:8436: if (m_ExtSEnv2.CtrParam.SetupTimeOut.mSetValue[SETUP_TIMEOUT_LIFT_ORIGIN])`
  - `Core/Src/dev_SRM.c:8438: if (getCalcTimer1ms(s_Over_timer) > (m_ExtSEnv2.CtrParam.SetupTimeOut.mSetValue[SETUP_TIMEOUT_LIFT_O`
  - `Core/Inc/User_Define.h:2200: SETUP_TIMEOUT_LIFT_ORIGIN,			// ì¹ê° ìì ì¤ì `

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SETUP_TIMEOUT_FORK_ORIGIN

- **종류**: enum `enumSETUP_TIMEOUT` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: í¬í¬ ìì ì¤ì 
- **용도(읽는 법)**: 헤더 주석: í¬í¬ ìì ì¤ì 
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:2348: for (i = 0; i <= SETUP_TIMEOUT_FORK_ORIGIN; i++)`
  - `Core/Src/SRM_Parameter.c:2543: for (i = 0; i <= SETUP_TIMEOUT_FORK_ORIGIN; i++)`
  - `Core/Src/SRM_Parameter.c:2551: nInitParam.SetupTimeOut.mSetValue[SETUP_TIMEOUT_FORK_ORIGIN] = 3000;		// 30.00s, Unit 0.01 sec`
  - `Core/Src/dev_SRM.c:8802: if (m_ExtSEnv2.CtrParam.SetupTimeOut.mSetValue[SETUP_TIMEOUT_FORK_ORIGIN])`
  - `Core/Src/dev_SRM.c:8804: if (getCalcTimer1ms(s_Over_timer) > (m_ExtSEnv2.CtrParam.SetupTimeOut.mSetValue[SETUP_TIMEOUT_FORK_O`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SETUP_TIMEOUT_SPARE3

- **종류**: enum `enumSETUP_TIMEOUT` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2202: SETUP_TIMEOUT_SPARE3,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SETUP_TIMEOUT_SPARE4

- **종류**: enum `enumSETUP_TIMEOUT` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2203: SETUP_TIMEOUT_SPARE4,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SETUP_TIMEOUT_SPARE5

- **종류**: enum `enumSETUP_TIMEOUT` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2204: SETUP_TIMEOUT_SPARE5,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SETUP_TIMEOUT_SPARE6

- **종류**: enum `enumSETUP_TIMEOUT` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2205: SETUP_TIMEOUT_SPARE6,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SETUP_TIMEOUT_SPARE7

- **종류**: enum `enumSETUP_TIMEOUT` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2206: SETUP_TIMEOUT_SPARE7,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SETUP_TIMEOUT_SPARE8

- **종류**: enum `enumSETUP_TIMEOUT` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2207: SETUP_TIMEOUT_SPARE8,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SETUP_TIMEOUT_SPARE9

- **종류**: enum `enumSETUP_TIMEOUT` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2208: SETUP_TIMEOUT_SPARE9,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SETUP_TIMEOUT_SPARE10

- **종류**: enum `enumSETUP_TIMEOUT` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2209: SETUP_TIMEOUT_SPARE10,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SETUP_TIMEOUT_SPARE11

- **종류**: enum `enumSETUP_TIMEOUT` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2210: SETUP_TIMEOUT_SPARE11,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SETUP_TIMEOUT_SPARE12

- **종류**: enum `enumSETUP_TIMEOUT` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2211: SETUP_TIMEOUT_SPARE12,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SETUP_TIMEOUT_SPARE13

- **종류**: enum `enumSETUP_TIMEOUT` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2212: SETUP_TIMEOUT_SPARE13,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SETUP_TIMEOUT_SPARE14

- **종류**: enum `enumSETUP_TIMEOUT` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2213: SETUP_TIMEOUT_SPARE14,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SETUP_TIMEOUT_SPARE15

- **종류**: enum `enumSETUP_TIMEOUT` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2214: SETUP_TIMEOUT_SPARE15,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SETUP_TIMEOUT_SPARE16

- **종류**: enum `enumSETUP_TIMEOUT` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2215: SETUP_TIMEOUT_SPARE16,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SETUP_TIMEOUT_SPARE17

- **종류**: enum `enumSETUP_TIMEOUT` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2216: SETUP_TIMEOUT_SPARE17,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SETUP_TIMEOUT_SPARE18

- **종류**: enum `enumSETUP_TIMEOUT` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2217: SETUP_TIMEOUT_SPARE18,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### SETUP_TIMEOUT_SPARE19

- **종류**: enum `enumSETUP_TIMEOUT` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2218: SETUP_TIMEOUT_SPARE19,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### MAX_SETUP_TIMEOUT_CNT

- **종류**: enum `enumSETUP_TIMEOUT` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2219: MAX_SETUP_TIMEOUT_CNT`
  - `Core/Inc/User_Define.h:2230: INT16U mSetValue[MAX_SETUP_TIMEOUT_CNT];`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DRIVE_TIMEOUT_MANUAL_RXCOM

- **종류**: enum `enumDRIVE_TIMEOUT` 멤버
- **값**: `0`
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: ìëì ì´ ëªë ¹ ìì íììì
- **용도(읽는 법)**: 헤더 주석: ìëì ì´ ëªë ¹ ìì íììì
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:2553: nInitParam.DrvTimeout.SetValue[DRIVE_TIMEOUT_MANUAL_RXCOM] = 150;	// 1.5s, Unit 0.01 sec`
  - `Core/Src/dev_SRM.c:30615: INT32U nManual_Timeout = (INT32U)m_ExtSEnv2.CtrParam.DrvTimeout.SetValue[DRIVE_TIMEOUT_MANUAL_RXCOM]`
  - `Core/Src/dev_SRM.c:31703: INT32U nManual_Timeout = (INT32U)m_ExtSEnv2.CtrParam.DrvTimeout.SetValue[DRIVE_TIMEOUT_MANUAL_RXCOM]`
  - `Core/Src/dev_SRM.c:33118: INT32U nManual_Timeout = (INT32U)m_ExtSEnv2.CtrParam.DrvTimeout.SetValue[DRIVE_TIMEOUT_MANUAL_RXCOM]`
  - `Core/Src/dev_SRM.c:34222: INT32U nManual_Timeout = (INT32U)m_ExtSEnv2.CtrParam.DrvTimeout.SetValue[DRIVE_TIMEOUT_MANUAL_RXCOM]`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DRIVE_TIMEOUT_HOME_RETURN

- **종류**: enum `enumDRIVE_TIMEOUT` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **원문 주석**: íë³µê·
- **용도(읽는 법)**: HOME/RETURN: 원점복귀 vs 에러복귀 RunMode 혼재. grep으로 확인.
- **코드 참조 예**:
  - `Core/Src/SRM_Parameter.c:2364: for (i = 0; i <= DRIVE_TIMEOUT_HOME_RETURN; i++)`
  - `Core/Src/SRM_Parameter.c:2554: nInitParam.DrvTimeout.SetValue[DRIVE_TIMEOUT_HOME_RETURN] = 60000;	// 1.5s, Unit 0.01 sec`
  - `Core/Src/dev_SRM.c:51764: else if (nTimerIndex == DRIVE_TIMEOUT_HOME_RETURN)`
  - `Core/Src/dev_SRM.c:58910: s_Over_Time = Get_OverTime_Drive(DRIVE_TIMEOUT_HOME_RETURN);//íë³µê· ìµëíì©ìê° ì ì¥`
  - `Core/Src/dev_SRM.c:61069: s_Over_Time = Get_OverTime_Drive(DRIVE_TIMEOUT_HOME_RETURN);`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DRIVE_TIMEOUT_SPARE2

- **종류**: enum `enumDRIVE_TIMEOUT` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2237: DRIVE_TIMEOUT_SPARE2,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DRIVE_TIMEOUT_SPARE3

- **종류**: enum `enumDRIVE_TIMEOUT` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2238: DRIVE_TIMEOUT_SPARE3,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DRIVE_TIMEOUT_SPARE4

- **종류**: enum `enumDRIVE_TIMEOUT` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2239: DRIVE_TIMEOUT_SPARE4,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DRIVE_TIMEOUT_SPARE5

- **종류**: enum `enumDRIVE_TIMEOUT` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2240: DRIVE_TIMEOUT_SPARE5,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DRIVE_TIMEOUT_SPARE6

- **종류**: enum `enumDRIVE_TIMEOUT` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2241: DRIVE_TIMEOUT_SPARE6,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DRIVE_TIMEOUT_SPARE7

- **종류**: enum `enumDRIVE_TIMEOUT` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2242: DRIVE_TIMEOUT_SPARE7,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DRIVE_TIMEOUT_SPARE8

- **종류**: enum `enumDRIVE_TIMEOUT` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2243: DRIVE_TIMEOUT_SPARE8,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

### DRIVE_TIMEOUT_SPARE9

- **종류**: enum `enumDRIVE_TIMEOUT` 멤버
- **정의 위치**: `Core/Inc/User_Define.h`
- **용도(읽는 법)**: grep(심볼, =1, case)으로 역할 확인. 이름만 믿지 말 것.
- **코드 참조 예**:
  - `Core/Inc/User_Define.h:2244: DRIVE_TIMEOUT_SPARE9,`

**추적 팁**: F12 실패 시 심볼 → `= 1` → `case` → `Save_*` 순 grep.

---

