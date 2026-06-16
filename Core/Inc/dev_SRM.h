/*
 * Dev_SRM.h
 *
 *  Created on: Jul 12, 2022
 *      Author: ARTWARE
 */

#ifndef INC_DEV_SRM_H_
#define INC_DEV_SRM_H_

#include "type.h"
#include "User_Define.h"

INT32S Get_Inverter_CurPosition(INT08U nInverter);
INT16S Get_Inverter_Actual_Speed(INT08U nInv);
INT08U Get_Inverter_Fault_State(INT08U nInv);
INT16U Get_Inverter_MainError(INT08U nInverter);
INT16U Get_Inverter_SubError(INT08U nInverter);
INT16U Get_Inverter_FbError(INT08U nInverter);
INT08U Get_Inverter_STO_State(INT08U nInverter);
INT32S Get_Inverter_Target_Position(INT08U nInverter);
INT16S Get_Inverter_SetPoint_Speed(INT08U nInverter);
//void TxPDO_Update(void);

INT08U Auto_Ctr_Travel(INT32S position, INT08U VelType);
INT08U Manual_Ctr_Travel(INT32S position, INT08U VelType);
INT08U Auto_Ctr_Lift(INT32S position, INT08U VelType);
//INT08U Manual_Ctr_Lift(INT32S position, INT08U VelType);

//INT08U Manual_Ctr_Fork(INT32S position, INT08U VelType);
void Motor_Application_Stop(INT08U nInvertor, INT08U VelType);
void Motor_Emergency_Stop(INT08U nInvertor);
INT08U Check_Motor_BrakeOn(INT08U nInverter);
void Motor_Brake_Enable(INT08U Invertor);
void Motor_Brake_Release(INT08U Invertor);
//void Motor_jog_Velocity(INT08U inverter, INT08U act, INT16S Velocity);

void SRM_Warning_reset(void);
void SRM_fault_reset(void);

void ControlPanel_Fault_Reset(void);
void set_Fork_All_Profile_Scurve(INT32S position, INT08U vel_type);
void set_Fork_Accelation_Move_Scurve(INT32S position, INT08U vel_type);
void set_Fork_Decelation_Stop_Scurve(INT32S position, INT08U vel_type);
void Set_Fork_Stop_Scurve(INT08U vel_type);

INT32S calc_dec_distance(double velocity, double dec, double djt);
INT32S calc_dec_distance_velocity(INT08U, double velocity, INT08U vel_type);

void SRM_Fork_profile_Control(INT08U vel_type, INT32S position);

void control_SRM_reference_Start(INT08U nInvertor);

INT16S Calc_Velocity_mms_mpm(INT16S nCurrent_MMS);
INT16S Calc_Velocity_mpm_mms(INT16S nCurrent_mpm);
void BE2LE_HMI_TxPDO(INT16U* pData, INT16U nData_Cnt);
void HMI_Write_RealTime_MW1(INT16U nData);
void RxModbusTcpData(INT08U nSocket, INT08U* data, INT16U len);
void DO_Control(INT08U nPort, INT08U nFlag);
void DO_Control_Manual(INT08U nPort, INT08U nFlag);
void DO_Control_Init();
INT08U Get_DI_State(INT08U nPort);
INT08U Get_DI_UseFlag(INT08U nPort);

INT08U Get_DO_UseFlag(INT08U nPort);
INT08U Get_DI_State_Filter(INT08U nPort);
INT08U Get_DO_State(INT08U nPort);
void test_profile(INT32S position);
INT08U Fork1_Profile_Control_Proc(void);

void SRM_Fork_Reference_Start();
INT08U Check_Fork_OriginSensor();
INT08U Check_Fork_CenterSensor();
INT08U Check_Fork_Center_State();
void Create_Reference_Position();

INT08U Check_Fork_Center_Alarm(void);

#define INVERTOR_INSTALL_COUNT 3

struct __attribute__((__packed__)) tagControlWord_A
{
	INT16U Reserved0 : 1;			// Bit0
	INT16U Enable_EmgStop : 1;		// Bit1, Velocity, Enable/Emergency stop
	INT16U Enable_AppStop : 1;		// Bit2, Velocity, Enable/Application stop
	INT16U ReadParam : 1;			// Bit3
	INT16U WriteParam : 1;			// Bit4
	INT16U Set_Variable : 1;		// Bit5
	INT16U FaultReset : 1;			// Bit6,
	INT16U DisableHW_Limit : 1;		// Bit7, On : limit 해제, Off: limit 활성화
	INT16U Start : 1;				// Bit8, Start AutoMode
	INT16U Jog_Positive : 1;		// Bit9,
	INT16U Jog_Negative : 1;		// Bit10,
	INT16U Mode : 2;				// Bit11-12, 01b:jog, 10:origin, 11:auto
	INT16U Reserved4 : 1;			// Bit13
	INT16U Reserved5 : 1;			// Bit14
	INT16U ForkReached : 1;			// Bit15,
};
typedef struct tagControlWord_A  ControlWordSTR_A;

typedef union
{
	INT16U W;
	ControlWordSTR_A B;
}ControlWord_A_t;

struct __attribute__((__packed__)) tagStatusWord_A
{
	INT16U MotorRunning : 1;			// Bit0, Motor rotate
	INT16U Ready : 1;					// Bit1,
	INT16U IPOS_ref : 1;				// Bit2, complete origin
	INT16U TargetReached : 1;			// Bit3,
	INT16U ReleaseBrake : 1;			// Bit4,
	INT16U Fault : 1;					// Bit5,
	INT16U ReadParamFlag : 1;			// Bit6,
	INT16U HeartBit : 1;				// Bit7,
	INT16U Status_Fault_Code : 8;		// Bit8-15,
};
typedef struct tagStatusWord_A  StatusWordSTR_A;

typedef union
{
	INT16U W;
	StatusWordSTR_A B;
}StatusWord_t_A;

// MOVI-C MultiMotion
struct __attribute__((__packed__)) tagMoviC_RxPDO
{
	ControlWord_A_t	ControlWord;			// PO01
	INT32S			TargetPosition;			// PO02-3 : [mm]
	INT16S			Setpoint_Speed;			// PO04 : [m/min]
	INT16S			Setpoint_Acc;			// PO05 : [mm/s2]
	INT16S			Setpoint_Dec;			// PO06 : [mm/s2]
	INT16U			JerkTime;				// PO07 : [ms]
	INT16U			ParamMainIndex;			// PO09
	INT16U			ParamSubIndex;			// PO10
	INT32S			WriteParamData;			// PO11 - PO11
	INT32S			Set_RefOffset;			// PO12 - PO13. Reference Position
	INT32U			Set_PosGain;			// PO14 - PO15, 위치 게인
	INT16U			Set_PosWindow;			// PO16, 정위치 오차 범위
};
typedef struct tagMoviC_RxPDO  MoviC_RxPDO;

struct __attribute__((__packed__)) tagMoviC_TxPDO
{
	StatusWord_t_A	StatusWord;				// PI01
	INT32S			CurPosition;			// PI02-3 현재 위치(2word)[mm]
	INT16S			ActualSpeed;			// PI04 현재 속도[m/min]
	INT16S			ActualTorque;			// PI05 현재 토크[%mot]
	INT16U			ParamValueMSB;			// PI06
	INT16U			ParamValueLSB;			// PI07
	INT16U			ErrorMainCode;			// PI08
	INT16U			ErrorSubCode;			// PI09
	INT16U			FBErrorCode;			// PI10
	INT16U			ExternalEncoder;		// PI11
	INT32S			Acutal_RefOffset;			// PI12 - PI13. Reference Position
	INT32S			Acutal_PosGain;			// PI14 - PI15, 위치 게인
	INT16U			Acutal_PosWindow;			// PI16, 정위치 오차 범위
};
typedef struct tagMoviC_TxPDO  MoviC_TxPDO;

// MOVIKIT® Positioning
struct __attribute__((__packed__)) tagMOVIKIT_POS_Control
{
	INT16U Enable_EmgStop : 1;				// Bit0, On : 구동 활성화, Off: 긴급 정지(FCB 14)
	INT16U Enable_AppStop : 1;				// Bit1, On : 구동 활성화, Off: 어플리케이션 리미트 정지(FCB 13)
	INT16U Reserved_2 : 1;					// Bit2
	INT16U Release_brake : 1;				// Bit3, 브레이크 강제 개방 (Brake/Dynastop on시)
	INT16U Jog_Positive : 1;				// Bit4, 조그 정방향
	INT16U Jog_Negative : 1;				// Bit5, 조그 역방향
	INT16U Accept_relative_position : 1;	// Bit6, 상대 위치 제어 시 재기동 명령
	INT16U Start : 1;						// Bit7, On : 모드 스타트(Positioning & Referencing), Off: 필드버스 감속 램프 타임 정지
	INT16U ResetFault : 1;					// Bit8
	INT16U Reserved_9 : 1;					// Bit9
	INT16U Activate_drive_train_2 : 1;		// Bit10, 파라미터 2군 사용
	INT16U Reserved_11 : 1;					// Bit11
	INT16U Disable_limit_switch : 1;		// Bit12, On : limit 해제, Off: limit 활성화
	INT16U Inhibit : 1;						// Bit13, Inhibit (강제 브레이크 해제 시 사용) 
	INT16U Activate_stanby_mode : 1;		// Bit14, 절전 모드 활성화
	INT16U HandshakeIn : 1;					// Bit15, 핸드 쉐이크 인(통신 확인용으로, 0.5초 Blink 추천)
};
typedef struct tagMOVIKIT_POS_Control  MOVKIT_POS_ControlSTR;

typedef union
{
	INT16U W;
	MOVKIT_POS_ControlSTR B;
}MOVKIT_POS_Control_t;

struct __attribute__((__packed__)) tagMOVKIT_POS_Status
{
	INT16U Ready : 1;							// Bit0, 인버터 구동 가능 상태
	INT16U STO_inactive : 1;					// Bit1, STO 비활성화 상태
	INT16U Inhibit_enabled : 1;					// Bit2, 인버터 출력 활성화 상태
	INT16U Brake_realesed : 1;					// Bit3, 브레이크 개방 상태
	INT16U Motor_turning : 1;					// Bit4, 모터 회전 상태
	INT16U Active_drive_referenced : 1;			// Bit5, 원점 결정 상태
	INT16U New_relative_position_applied : 1;	// Bit6, 새로운 상대 위치 적용
	INT16U In_position : 1;						// Bit7, 위치 도착 완료
	INT16U Fault : 1;							// Bit8, 폴트 발생
	INT16U Warning : 1;							// Bit9, 주의 발생
	INT16U Drive_train_2_active : 1;			// Bit10, 파라미터 2군 사용 중
	INT16U Speed_reached : 1;					// Bit11, 타깃 속도 도달
	INT16U Limit_switch_inactive : 1;			// Bit12, S/W limit switch 비활성화 상태
	INT16U Reserved_13 : 1;						// Bit13
	INT16U Stanby_mode_Activated : 1;			// Bit14, 절전 모드 활성화 상태
	INT16U HandshakeOut : 1;					// Bit15, 핸드 쉐이크 아웃 (핸드 쉐이크 인의 신호 미러링)
};
typedef struct tagMOVKIT_POS_Status  MOVKIT_POS_StatusSTR;

typedef union
{
	INT16U W;
	MOVKIT_POS_StatusSTR B;
}MOVKIT_POS_Status_t;

struct __attribute__((__packed__)) tagMOVIKIT_MAC_Control
{
	INT16U Enable_EmgStop : 1;				// Bit0, 
	INT16U Enable_AppStop : 1;				// Bit1, 
	INT16U Reserved_2 : 1;					// Bit2
	INT16U Release_brake : 1;				// Bit3, 
	INT16U Jog_Positive : 1;				// Bit4, 
	INT16U Jog_Negative : 1;				// Bit5, 
	INT16U Accept_relative_position : 1;	// Bit6, 
	INT16U Start : 1;						// Bit7, On : 모드 스타트(Positioning & Referencing), Off: 필드버스 감속 램프 타임 정지
	INT16U ResetFault : 1;					// Bit8
	INT16U Reserved_9 : 1;					// Bit9
	INT16U Reserved_10 : 1;					// Bit10
	INT16U Reserved_11 : 1;					// Bit11
	INT16U Disable_limit_switch : 1;		// Bit12, On : limit 해제, Off: limit 활성화
	INT16U Inhibit : 1;						// Bit13, Inhibit (강제 브레이크 해제 시 사용) 
	INT16U Activate_stanby_mode : 1;		// Bit14, 절전 모드 활성화
	INT16U HandshakeIn : 1;					// Bit15, 핸드 쉐이크 인(통신 확인용으로, 0.5초 Blink 추천)
};
typedef struct tagMOVIKIT_MAC_Control  MOVKIT_MAC_ControlSTR;

typedef union
{
	INT16U W;
	MOVKIT_MAC_ControlSTR B;
}MOVKIT_MAC_Control_t;

struct __attribute__((__packed__)) tagMOVKIT_MAC_Status
{
	INT16U Ready : 1;							// Bit0, 인버터 구동 가능 상태
	INT16U STO_inactive : 1;					// Bit1, STO 비활성화 상태
	INT16U Inhibit_enabled : 1;					// Bit2, 인버터 출력 활성화 상태
	INT16U Brake_realesed : 1;					// Bit3, 브레이크 개방 상태
	INT16U Motor_turning : 1;					// Bit4, 모터 회전 상태
	INT16U Active_drive_referenced : 1;			// Bit5, 원점 결정 상태
	INT16U New_relative_position_applied : 1;	// Bit6, 새로운 상대 위치 적용
	INT16U In_position : 1;						// Bit7, 위치 도착 완료
	INT16U Fault : 1;							// Bit8, 폴트 발생
	INT16U Warning : 1;							// Bit9, 주의 발생
	INT16U Reserved_10 : 1;						// Bit10, 
	INT16U Speed_reached : 1;					// Bit11, 타깃 속도 도달
	INT16U Limit_switch_inactive : 1;			// Bit12, S/W limit switch 비활성화 상태
	INT16U Reserved_13 : 1;						// Bit13
	INT16U Stanby_mode_Activated : 1;			// Bit14, 절전 모드 활성화 상태
	INT16U HandshakeOut : 1;					// Bit15, 핸드 쉐이크 아웃 (핸드 쉐이크 인의 신호 미러링)
};
typedef struct tagMOVKIT_MAC_Status  MOVKIT_MAC_StatusSTR;

typedef union
{
	INT16U W;
	MOVKIT_MAC_StatusSTR B;
}MOVKIT_MAC_Status_t;

struct __attribute__((__packed__)) tagMOVKIT_StatusCode
{
	INT08U StatusCode;		// 하위8Bit : 상태 or 폴트 서브코드
	INT08U MainErrCode;		// 상위8Bit : 폴트 메인코드
};
typedef struct tagMOVKIT_StatusCode  MOVKIT_MAC_StatusCode;

typedef union
{
	INT16U W;
	MOVKIT_MAC_StatusCode B;
}MOVKIT_StatusCode_t;


struct __attribute__((__packed__)) tagMOVIKIT_MAC_Control2
{
	INT16U Disable_Member1 : 1;							// Bit0, 1번 멤버 MAC 비활성화
	INT16U Disable_Member2 : 1;							// Bit1, 2번 멤버 MAC 비활성화
	INT16U Disable_Member3 : 1;							// Bit2, 3번 멤버 MAC 비활성화
	INT16U Disable_Member4 : 1;							// Bit3, 4번 멤버 MAC 비활성화
	INT16U Release_brake_without_enable_member1 : 1;	// Bit4, 1번 멤버 강제 브레이크 해제
	INT16U Release_brake_without_enable_member2 : 1;	// Bit5, 2번 멤버 강제 브레이크 해제
	INT16U Release_brake_without_enable_member3 : 1;	// Bit6, 3번 멤버 강제 브레이크 해제
	INT16U Release_brake_without_enable_member4 : 1;	// Bit7, 4번 멤버 강제 브레이크 해제
	INT16U Deactivate_balance_controller : 1;			// Bit8, 밸런싱 제어 비활성화
	INT16U Disable_position_controller : 1;				// Bit9, 포지션 컨트롤 비활성화
	INT16U Disable_Skew_error : 1;						// Bit10, Skew 에러 비활성화
	INT16U Allow_skew_compensation : 1;					// Bit11, Skewing 기울기 균형 활성화
	INT16U Reset_encoder_difference : 1;				// Bit12, 엔코더 간 오차 리셋
	INT16U Deactivate_external_encoders : 1;			// Bit13, 외부 엔코더 비활성화
	INT16U Reserved_14 : 1;								// Bit14,
	INT16U Reserved_15 : 1;								// Bit15,
};
typedef struct tagMOVIKIT_MAC_Control2  MOVKIT_MAC_Control2_STR;

typedef union
{
	INT16U W;
	MOVKIT_MAC_Control2_STR B;
}MOVKIT_MAC_Control2_t;

struct __attribute__((__packed__)) tagMOVKIT_MAC_Status2
{
	INT16U Member1_disabled : 1;				// Bit0, 1번 멤버 MAC 비활성화
	INT16U Member2_disabled : 1;				// Bit1, 2번 멤버 MAC 비활성화
	INT16U Member3_disabled : 1;				// Bit2, 3번 멤버 MAC 비활성화
	INT16U Member4_disabled : 1;				// Bit3, 4번 멤버 MAC 비활성화
	INT16U Member1_brake_Released : 1;			// Bit4, 1번 멤버 강제 브레이크 해제
	INT16U Member2_brake_Released : 1;			// Bit5, 2번 멤버 강제 브레이크 해제
	INT16U Member3_brake_Released : 1;			// Bit6, 3번 멤버 강제 브레이크 해제
	INT16U Member4_brake_Released : 1;			// Bit7, 4번 멤버 강제 브레이크 해제
	INT16U Deactivate_balance_controller : 1;	// Bit8, 밸런싱 제어 비활성화
	INT16U Position_controller_disabled : 1;	// Bit9, 포지션 컨트롤 비활성화
	INT16U Skew_in_Skew_window : 1;				// Bit10, Skew 윈도우 내에 위치함
	INT16U Overload_guard_active : 1;			// Bit11, 오버로드 가드 활성화 중
	INT16U Reserved_12 : 1;						// Bit12, 
	INT16U External_encoder_deactivated : 1;	// Bit13, 외부 엔코더 비활성화
	INT16U Reserved_14 : 1;						// Bit14,
	INT16U Reserved_15 : 1;						// Bit15,
};
typedef struct tagMOVKIT_MAC_Status2  MOVKIT_MAC_Status2_STR;

typedef union
{
	INT16U W;
	MOVKIT_MAC_Status2_STR B;
}MOVKIT_MAC_Status2_t;

enum enumOP_MODE {
	OP_MODE_NONE = 0,				// 모드 없음, 모드 없이 기동 시 알람 발생.
	OP_MODE_JOG_POS = 100,			// 조그모드 (포지션기반 FCB06)
	OP_MODE_JOG_SPD = 101,			// 조그모드 (스피드기반 FCB06)
	OP_MODE_SPD_CTR = 200,			// 속도 제어 (스피드기반 FCB06)
	OP_MODE_REF = 300,				// 원점모드
	OP_MODE_REF_OFFSET = 301,		// 원점모드 with 필드버스 유저오프셋
	OP_MODE_ABSOLUTE_POS = 400,		// 절대 위치 제어 (FCB06)
	OP_MODE_RELATIVE_POS = 401,		// 상대 위치 제어 (FCB06)
};

struct __attribute__((__packed__)) tagMOVKIT_MAC_PO
{
	MOVKIT_MAC_Control_t	ControlWord;			// PO01
	INT16S					Setpoint_Speed;			// PO02 : [m/min]
	INT16S					Setpoint_Acc;			// PO03 : [mm/s2]
	INT16S					Setpoint_Dec;			// PO04 : [mm/s2]
	INT16U					Forced_DO;				// PO05 : 
	INT16U					Operating_mode;			// PO06 : 
	INT32S					TargetPosition;			// PO07-8 : [mm]
	INT16U					JerkTime;				// PO09 : [ms]
	MOVKIT_MAC_Control2_t	ControlWord2;			// PO10
};
typedef struct tagMOVKIT_MAC_PO  MOVKIT_MAC_PO;

struct __attribute__((__packed__)) tagMOVKIT_MAC_PI
{
	MOVKIT_MAC_Status_t		StatusWord;				// PI01
	INT16S					ActualSpeed;			// PI02 현재 속도[m/min]
	MOVKIT_StatusCode_t		StatusCode;				// PI03
	INT16S					ActualTorque;			// PI04 현재 토크[%mot]
	INT16U					DI_Status;				// PI05
	INT16U					Operating_mode;			// PI06 : 
	INT32S					CurPosition;			// PI07-8 현재 위치(2word)[mm]
	INT16U					JerkTime;				// PI09 : [ms]
	MOVKIT_MAC_Status2_t	StatusWord2;			// PO10
};
typedef struct tagMOVKIT_MAC_PI MOVKIT_MAC_PI;

struct __attribute__((__packed__)) tagMOVKIT_POS_PO
{
	MOVKIT_POS_Control_t	ControlWord;			// PO01
	INT16S					Setpoint_Speed;			// PO02 : [m/min]
	INT16S					Setpoint_Acc;			// PO03 : [mm/s2]
	INT16S					Setpoint_Dec;			// PO04 : [mm/s2]
	INT16U					Forced_DO;				// PO05 : 
	INT16U					Operating_mode;			// PO06 : 
	INT32S					TargetPosition;			// PO07-8 : [mm]
	INT16U					JerkTime;				// PO09 : [ms]
};
typedef struct tagMOVKIT_POS_PO  MOVKIT_POS_PO;

struct __attribute__((__packed__)) tagMOVKIT_POS_PI
{
	MOVKIT_POS_Status_t		StatusWord;				// PI01
	INT16S					ActualSpeed;			// PI02 현재 속도[m/min]
	MOVKIT_StatusCode_t		StatusCode;				// PI03
	INT16S					ActualTorque;			// PI04 현재 토크[%mot]
	INT16U					DI_Status;				// PI05
	INT16U					Operating_mode;			// PI06 : 
	INT32S					CurPosition;			// PI07-8 현재 위치(2word)[mm]
	INT16U					JerkTime;				// PI09 : [ms]
};
typedef struct tagMOVKIT_POS_PI MOVKIT_POS_PI;

// INV_VENDOR_SEW_VER2_ANTI_SWAY
struct __attribute__((__packed__)) tagMOVKIT_PO_TYPE1_2
{
	MOVKIT_MAC_PO Hoist;
	MOVKIT_MAC_PO Travel;
	MOVKIT_POS_PO Fork;
};
typedef struct tagMOVKIT_PO_TYPE1_2 MOVKIT_PO_TYPE_1;

struct __attribute__((__packed__)) tagMOVKIT_PI_TYPE1_2
{
	MOVKIT_MAC_PI Hoist;
	MOVKIT_MAC_PI Travel;
	MOVKIT_POS_PI Fork;
};
typedef struct tagMOVKIT_PI_TYPE1_2 MOVKIT_PI_TYPE_1;

// INV_VENDOR_SEW_VER2
struct __attribute__((__packed__)) tagMOVKIT_PO_TYPE2
{
	MOVKIT_POS_PO Hoist;
	INT16U	Reserved0;				//
	MOVKIT_POS_PO Travel;
	INT16U	Reserved1;				//
	MOVKIT_POS_PO Fork;
};
typedef struct tagMOVKIT_PO_TYPE2 MOVKIT_PO_TYPE_2;

struct __attribute__((__packed__)) tagMOVKIT_PI_TYPE2
{
	MOVKIT_POS_PI Hoist;
	INT16U	Reserved0;				//
	MOVKIT_POS_PI Travel;
	INT16U	Reserved1;				//
	MOVKIT_POS_PI Fork;
};
typedef struct tagMOVKIT_PI_TYPE2 MOVKIT_PI_TYPE_2;

// INV_VENDOR_SEW_VER2_SYNC_TRAVEL
struct __attribute__((__packed__)) tagMOVKIT_PO_TYPE3
{
	MOVKIT_POS_PO Hoist;
	INT16U	Reserved0;				//
	MOVKIT_MAC_PO Travel;
	MOVKIT_POS_PO Fork;
};
typedef struct tagMOVKIT_PO_TYPE3 MOVKIT_PO_TYPE_3;

struct __attribute__((__packed__)) tagMOVKIT_PI_TYPE3
{
	MOVKIT_POS_PI Hoist;
	INT16U	Reserved0;				//
	MOVKIT_MAC_PI Travel;
	MOVKIT_POS_PI Fork;
};
typedef struct tagMOVKIT_PI_TYPE3 MOVKIT_PI_TYPE_3;

struct __attribute__((__packed__)) tagHMI_MW0_Bit
{
	INT16U Manual_Travel_S_FW : 1;		// Bit 0
	INT16U Manual_Travel_S_BW : 1;		// Bit 1
	INT16U Manual_Travel_M_FW : 1;		// Bit 2
	INT16U Manual_Travel_M_BW : 1;		// Bit 3
	INT16U Reserved_0 : 1;				// Bit 4
	INT16U Reserved_1 : 1;				// Bit 5
	INT16U Manual_Lift_S_Up : 1;		// Bit 6
	INT16U Manual_Lift_S_Down : 1;		// Bit 7
	INT16U Manual_Lift_M_Up : 1;		// Bit 8
	INT16U Manual_Lift_M_Down : 1;		// Bit 9
	INT16U Manual_Fork1_Center : 1;		// Bit 10
	INT16U Manual_Fork2_Center : 1;		// Bit 11
	INT16U Manual_Fork1_Left : 1;		// Bit 12
	INT16U Manual_Fork1_Right : 1;		// Bit 13
	INT16U Manual_Fork2_Left : 1;		// Bit 14
	INT16U Manual_Fork2_Right : 1;		// Bit 15
};
typedef struct tagHMI_MW0_Bit  HMI_MW0_Bit;

struct __attribute__((__packed__)) tagHMI_MW0
{
	union
	{
		WORD_User			Word;
		HMI_MW0_Bit			Bit;
	};
};
typedef struct tagHMI_MW0  HMI_Regi_MW0;

struct __attribute__((__packed__)) tagHMI_MW1_Bit
{
	INT16U DB_Start : 1;				// Bit 0, 크레인 시작 명령 / 온라인
	INT16U Buzzer_Off : 1;				// Bit 1
	INT16U Reset_Error : 1;				// Bit 2
	INT16U DB_Stop : 1;					// Bit 3, 크레인 정지
	INT16U Delete_Fork1_WorkData : 1;	// Bit 4
	INT16U Delete_Fork2_WorkData : 1;	// Bit 5
	INT16U Complete_Fork1_Job : 1;		// Bit 6
	INT16U Complete_Fork2_Job : 1;		// Bit 7
	INT16U Manual_Return_Home : 1;		// Bit 8
	INT16U Reserved_9 : 1;				// Bit 9
	INT16U Reserved_10 : 1;				// Bit 10
	INT16U Reserved_11 : 1;				// Bit 11
	INT16U Reserved_12 : 1;				// Bit 12
	INT16U Reserved_13 : 1;				// Bit 13
	INT16U Reserved_14 : 1;				// Bit 14
	INT16U Enable_ForcedMode : 1;				// Bit 15
};
typedef struct tagHMI_MW1_Bit  HMI_MW1_Bit;

struct __attribute__((__packed__)) tagHMI_MW1
{
	union
	{
		WORD_User	Word;
		HMI_MW1_Bit	Bit;
	};
};
typedef struct tagHMI_MW1  HMI_Regi_MW1;

struct __attribute__((__packed__)) tagHMI_MW2_Bit
{
	INT16U Manual_Fork1_Left_Pos : 1;	// Bit 0, 수동 포크1 좌 기준 버튼
	INT16U Manual_Fork1_Right_Pos : 1;	// Bit 1, 수동 포크1 우 기준 버튼
	INT16U Manual_Fork2_Left_Pos : 1;	// Bit 2
	INT16U Manual_Fork2_Right_Pos : 1;	// Bit 3, 
	INT16U Manual_Fork_End : 1;			// Bit 4
	INT16U Manual_Fork_Middle : 1;		// Bit 5
	INT16U Manual_Fork_Half : 1;		// Bit 6
	INT16U Reserved_7 : 1;				// Bit 7
	INT16U Reserved_8 : 1;				// Bit 8
	INT16U Reserved_9 : 1;				// Bit 9
	INT16U Reserved_10 : 1;				// Bit 10
	INT16U Travel_Home_Ref : 1;			// Bit 11
	INT16U Lift_Home_Ref : 1;			// Bit 12
	INT16U Fork1_Center_Ref : 1;		// Bit 13
	INT16U Fork2_Center_Ref : 1;		// Bit 14
	INT16U Reserved_15 : 1;				// Bit 15
};
typedef struct tagHMI_MW2_Bit  HMI_MW2_Bit;

struct __attribute__((__packed__)) tagHMI_MW2
{
	union
	{
		WORD_User	Word;
		HMI_MW2_Bit	Bit;
	};
};
typedef struct tagHMI_MW2  HMI_Regi_MW2;

struct __attribute__((__packed__)) tagHMI_MW4_Bit
{
	INT16U Crane_Type_Fork_Single : 1;			// Bit 0, 
	INT16U Crane_Type_Fork_Twin : 1;			// Bit 1,
	INT16U Reserved_2 : 1;						// Bit 2
	INT16U Crane_Fork_Pos_Single : 1;			// Bit 3, 
	INT16U Crane_Fork_Pos_Double_2Pos : 1;		// Bit 4
	INT16U Crane_Fork_Pos_Double_3Pos : 1;		// Bit 5
	INT16U Crane_Fork_Pos_Double_4Pos : 1;		// Bit 6
	INT16U Reserved_7 : 1;						// Bit 7
	INT16U Crane_Fork_Pos_Variant_2Pos : 1;		// Bit 8
	INT16U Crane_Fork_Pos_Variant_3Pos : 1;		// Bit 9
	INT16U Crane_Fork_Pos_Variant_4Pos : 1;		// Bit 10
	INT16U Reserved_11 : 1;						// Bit 11
	INT16U Reserved_12 : 1;						// Bit 12
	INT16U Controller_Type : 1;					// Bit 13
	INT16U Fork_Encoder_Use : 1;				// Bit 14
	INT16U Crane_Type : 1;						// Bit 15
};
typedef struct tagHMI_MW4_Bit  HMI_MW4_Bit;

struct __attribute__((__packed__)) tagHMI_MW4
{
	union
	{
		WORD_User	Word;
		HMI_MW4_Bit	Bit;
	};
};
typedef struct tagHMI_MW4  HMI_Regi_MW4;

struct __attribute__((__packed__)) tagHMI_MW5_Bit
{
	INT16U GCP_Auto_SW : 1;				// Bit 0 
	INT16U GCP_Manual_SW : 1;			// Bit 1
	INT16U GCP_Semi_Auto_SW : 1;		// Bit 2
	INT16U GCP_EMG_SW : 1;				// Bit 3
	INT16U Crane_Auto : 1;				// Bit 4
	INT16U Crane_Manual : 1;			// Bit 5
	INT16U Crane_Semi_Auto : 1;			// Bit 6
	INT16U Crane_Fault : 1;				// Bit 7

	INT16U Crane_Warnning : 1;			// Bit 8
	INT16U Touch_PLC_Heart_Beat : 1;	// Bit 9
	INT16U GCP_Heart_Beat : 1;			// Bit 10
	INT16U WCS_Heart_Beat : 1;			// Bit 11
	INT16U Reserved_12 : 1;				// Bit 12
	INT16U Reserved_13 : 1;				// Bit 13
	INT16U Reserved_14 : 1;				// Bit 14
	INT16U Reserved_15 : 1;				// Bit 15
};
typedef struct tagHMI_MW5_Bit  HMI_MW5_Bit;

struct __attribute__((__packed__)) tagHMI_MW5
{
	union
	{
		WORD_User	Word;
		HMI_MW5_Bit	Bit;
	};
};
typedef struct tagHMI_MW5  HMI_Regi_MW5;

struct __attribute__((__packed__)) tagHMI_MW101_Bit
{
	INT16U CVNO1 : 1;		// Bit 0 
	INT16U CVNO2 : 1;		// Bit 1
	INT16U CVNO3 : 1;		// Bit 2
	INT16U CVNO4 : 1;		// Bit 3
	INT16U CVNO5 : 1;		// Bit 4
	INT16U CVNO6 : 1;		// Bit 5
	INT16U CVNO7 : 1;		// Bit 6
	INT16U CVNO8 : 1;		// Bit 7
	INT16U CVOK1 : 1;		// Bit 8
	INT16U CVOK2 : 1;		// Bit 9
	INT16U CVOK3 : 1;		// Bit 10
	INT16U CVOK4 : 1;		// Bit 11
	INT16U CVOK5 : 1;		// Bit 12
	INT16U CVOK6 : 1;		// Bit 13
	INT16U CVOK7 : 1;		// Bit 14
	INT16U CVOK8 : 1;		// Bit 15
};
typedef struct tagHMI_MW101_Bit  HMI_MW101_Bit;

struct __attribute__((__packed__)) tagHMI_MW101
{
	union
	{
		WORD_User		Word;
		HMI_MW101_Bit	Bit;
	};
};
typedef struct tagHMI_MW101  HMI_Regi_MW101;

struct __attribute__((__packed__)) tagHMI_MW103_Bit
{
	INT16U EM : 1;			// Bit 0, 
	INT16U AUTO : 1;		// Bit 1,
	INT16U MAN : 1;			// Bit 2
	INT16U RDF : 1;			// Bit 3, 
	INT16U LST_LSTH : 1;	// Bit 4
	INT16U TST_TSTH : 1;	// Bit 5
	INT16U MFLT : 1;		// Bit 6
	INT16U GOV : 1;			// Bit 7
	INT16U LSTE : 1;		// Bit 8
	INT16U TSTE : 1;		// Bit 9
	INT16U LD : 1;			// Bit 10
	INT16U TD : 1;			// Bit 11
	INT16U RVDR1 : 1;		// Bit 12
	INT16U RVDR2 : 1;		// Bit 13
	INT16U RVDL1 : 1;		// Bit 14
	INT16U RVDL2 : 1;		// Bit 15
};
typedef struct tagHMI_MW103_Bit  HMI_MW103_Bit;

struct __attribute__((__packed__)) tagHMI_MW103
{
	union
	{
		WORD_User		Word;
		HMI_MW103_Bit	Bit;
	};
};
typedef struct tagHMI_MW103  HMI_Regi_MW103;

struct __attribute__((__packed__)) tagHMI_MW104_Bit
{
	INT16U IINH : 1;			// Bit 0, 
	INT16U Reserved_1 : 1;		// Bit 1,
	INT16U FCD : 1;				// Bit 2
	INT16U RDE : 1;				// Bit 3, 
	INT16U RED : 1;				// Bit 4
	INT16U YEL : 1;				// Bit 5
	INT16U GRN : 1;				// Bit 6
	INT16U BU : 1;				// Bit 7
	INT16U WH : 1;				// Bit 8
	INT16U SUD : 1;				// Bit 9
	INT16U Reserved_10 : 1;		// Bit 10
	INT16U Reserved_11 : 1;		// Bit 11
	INT16U Reserved_12 : 1;		// Bit 12
	INT16U LED_RD : 1;			// Bit 13
	INT16U LED_GR : 1;			// Bit 14
	INT16U LED_BU : 1;			// Bit 15
};
typedef struct tagHMI_MW104_Bit  HMI_MW104_Bit;

struct __attribute__((__packed__)) tagHMI_MW104
{
	union
	{
		WORD_User		Word;
		HMI_MW104_Bit	Bit;
	};
};
typedef struct tagHMI_MW104  HMI_Regi_MW104;

struct __attribute__((__packed__)) tagHMI_MW105_Bit
{
	INT16U MCF : 1;			// Bit 0
	INT16U MC1F : 1;		// Bit 1
	INT16U PDR : 1;			// Bit 2
	INT16U PTH : 1;			// Bit 3
	INT16U MCTMF : 1;		// Bit 4
	INT16U MCFMF : 1;		// Bit 5
	INT16U T1PSF : 1;		// Bit 6
	INT16U T1OSO : 1;		// Bit 7
	INT16U LBMMSF1 : 1;		// Bit 8
	INT16U TBMMSF1 : 1;		// Bit 9
	INT16U FBMMSF1 : 1;		// Bit 10
	INT16U TBMMSF2 : 1;		// Bit 11
	INT16U TDF : 1;			// Bit 12
	INT16U TDR : 1;			// Bit 13
	INT16U THP : 1;			// Bit 14
	INT16U TSP : 1;			// Bit 15
};
typedef struct tagHMI_MW105_Bit  HMI_MW105_Bit;

struct __attribute__((__packed__)) tagHMI_MW105
{
	union
	{
		WORD_User		Word;
		HMI_MW105_Bit	Bit;
	};
};
typedef struct tagHMI_MW105  HMI_Regi_MW105;

struct __attribute__((__packed__)) tagHMI_MW106_Bit
{
	INT16U MCE : 1;			// Bit 0
	INT16U MCUB : 1;		// Bit 1
	INT16U PLAMP : 1;		// Bit 2
	INT16U PFAN : 1;		// Bit 3
	INT16U MCTM : 1;		// Bit 4
	INT16U MCFM1 : 1;		// Bit 5
	INT16U T1FSPC : 1;		// Bit 6
	INT16U T1SPO : 1;		// Bit 7
	INT16U Reserved_8 : 1;	// Bit 8
	INT16U Reserved_9 : 1;	// Bit 9
	INT16U MCFB1 : 1;		// Bit 10
	INT16U Reserved_11 : 1;	// Bit 11
	INT16U Reserved_12 : 1;	// Bit 12
	INT16U Reserved_13 : 1;	// Bit 13
	INT16U Reserved_14 : 1;	// Bit 14
	INT16U Reserved_15 : 1;	// Bit 15
};
typedef struct tagHMI_MW106_Bit  HMI_MW106_Bit;

struct __attribute__((__packed__)) tagHMI_MW106
{
	union
	{
		WORD_User		Word;
		HMI_MW106_Bit	Bit;
	};
};
typedef struct tagHMI_MW106  HMI_Regi_MW106;

struct __attribute__((__packed__)) tagHMI_MW107_Bit
{
	INT16U CFLT : 1;	// Bit 0
	INT16U CRD : 1;		// Bit 1
	INT16U MC2F : 1;	// Bit 2
	INT16U MCLMF : 1;	// Bit 3
	INT16U MCTM : 1;	// Bit 4
	INT16U MCFM1 : 1;	// Bit 5
	INT16U T1PSF : 1;	// Bit 6
	INT16U T1SPO : 1;	// Bit 7
	INT16U CVOK1 : 1;	// Bit 8
	INT16U CVOK2 : 1;	// Bit 9
	INT16U CVOK3 : 1;	// Bit 10
	INT16U CVOK4 : 1;	// Bit 11
	INT16U CVOK5 : 1;	// Bit 12
	INT16U CVOK6 : 1;	// Bit 13
	INT16U CVOK7 : 1;	// Bit 14
	INT16U CVOK8 : 1;	// Bit 15
};
typedef struct tagHMI_MW107_Bit  HMI_MW107_Bit;

struct __attribute__((__packed__)) tagHMI_MW107
{
	union
	{
		WORD_User		Word;
		HMI_MW107_Bit	Bit;
	};
};
typedef struct tagHMI_MW107  HMI_Regi_MW107;

struct __attribute__((__packed__)) tagHMI_MW108_Bit
{
	INT16U COSE : 1;	// Bit 0
	INT16U CENB : 1;		// Bit 1
	INT16U CRST : 1;	// Bit 2
	INT16U MCLM : 1;	// Bit 3
	INT16U MCFM2 : 1;	// Bit 4
	INT16U LFSPC : 1;	// Bit 5
	INT16U LSPO : 1;	// Bit 6
	INT16U MCFB2 : 1;	// Bit 7
	INT16U CVNO1 : 1;	// Bit 8
	INT16U CVNO2 : 1;	// Bit 9
	INT16U CVNO3 : 1;	// Bit 10
	INT16U CVNO4 : 1;	// Bit 11
	INT16U CVNO5 : 1;	// Bit 12
	INT16U CVNO6 : 1;	// Bit 13
	INT16U CVNO7 : 1;	// Bit 14
	INT16U CVNO8 : 1;	// Bit 15
};
typedef struct tagHMI_MW108_Bit  HMI_MW108_Bit;

struct __attribute__((__packed__)) tagHMI_MW108
{
	union
	{
		WORD_User		Word;
		HMI_MW108_Bit	Bit;
	};
};
typedef struct tagHMI_MW108  HMI_Regi_MW108;

struct __attribute__((__packed__)) tagHMI_MW109_Bit
{
	INT16U GRA : 1;			// Bit 0
	INT16U DEVICE_FLT : 1;	// Bit 1
	INT16U TS1_ENB : 1;		// Bit 2
	INT16U TS2_ENB : 1;		// Bit 3
	INT16U M_EST : 1;		// Bit 4
	INT16U M_KEYSW : 1;		// Bit 5
	INT16U M_FLT : 1;		// Bit 6
	INT16U M_DOORSW : 1;	// Bit 7
	INT16U LBMMSF2 : 1;		// Bit 8
	INT16U TBMMSF2 : 1;		// Bit 9
	INT16U FK1_FLT : 1;		// Bit 10
	INT16U FK1_STOP : 1;	// Bit 11
	INT16U FK2_FLT : 1;		// Bit 12
	INT16U FK2_STOP : 1;		// Bit 13
	INT16U Reserved_14 : 1;		// Bit 14
	INT16U Reserved_15 : 1;		// Bit 15
};
typedef struct tagHMI_MW109_Bit  HMI_MW109_Bit;

struct __attribute__((__packed__)) tagHMI_MW109
{
	union
	{
		WORD_User		Word;
		HMI_MW109_Bit	Bit;
	};
};
typedef struct tagHMI_MW109  HMI_Regi_MW109;

struct __attribute__((__packed__)) tagHMI_MW110_Bit
{
	INT16U GRA_RST : 1;			// Bit 0
	INT16U DEVICE_RST : 1;		// Bit 1
	INT16U FK1_STO1 : 1;		// Bit 2
	INT16U FK1_STO2 : 1;		// Bit 3
	INT16U FK1_JOG : 1;			// Bit 4
	INT16U FK1_R : 1;			// Bit 5
	INT16U FK1_L : 1;			// Bit 6
	INT16U FK1_RST : 1;			// Bit 7
	INT16U FK2_STO1 : 1;		// Bit 8
	INT16U FK2_STO2 : 1;		// Bit 9
	INT16U FK2_JOG : 1;			// Bit 10
	INT16U FK2_R : 1;			// Bit 11
	INT16U FK2_L : 1;			// Bit 12
	INT16U FK2_RST : 1;		// Bit 13
	INT16U Reserved_14 : 1;		// Bit 14
	INT16U Reserved_15 : 1;		// Bit 15
};
typedef struct tagHMI_MW110_Bit  HMI_MW110_Bit;

struct __attribute__((__packed__)) tagHMI_MW110
{
	union
	{
		WORD_User		Word;
		HMI_MW110_Bit	Bit;
	};
};
typedef struct tagHMI_MW110  HMI_Regi_MW110;

struct __attribute__((__packed__)) tagHMI_MW111_Bit
{
	INT16U GOX1 : 1;			// Bit 0
	INT16U GOXH1 : 1;	// Bit 1
	INT16U GOXM1 : 1;		// Bit 2
	INT16U GOXS1 : 1;		// Bit 3
	INT16U GWL1 : 1;		// Bit 4
	INT16U GWR1 : 1;		// Bit 5
	INT16U GWLe1 : 1;		// Bit 6
	INT16U GWRe1 : 1;		// Bit 7
	INT16U GDFL1 : 1;		// Bit 8
	INT16U GDFR1 : 1;		// Bit 9
	INT16U GDRL1 : 1;		// Bit 10
	INT16U GDRR1 : 1;		// Bit 11
	INT16U GHL1 : 1;		// Bit 12
	INT16U GHR1 : 1;		// Bit 13
	INT16U FOKL1 : 1;		// Bit 14
	INT16U FOKR1 : 1;		// Bit 15
};
typedef struct tagHMI_MW111_Bit  HMI_MW111_Bit;

struct __attribute__((__packed__)) tagHMI_MW111
{
	union
	{
		WORD_User		Word;
		HMI_MW111_Bit	Bit;
	};
};
typedef struct tagHMI_MW111  HMI_Regi_MW111;

struct __attribute__((__packed__)) tagHMI_MW112_Bit
{
	INT16U FEL1 : 1;		// Bit 0
	INT16U FER1 : 1;		// Bit 1
	INT16U FCL1 : 1;		// Bit 2
	INT16U FCR1 : 1;		// Bit 3
	INT16U DSTL1 : 1;		// Bit 4
	INT16U DSTR1 : 1;		// Bit 5
	INT16U DSTLe1 : 1;		// Bit 6
	INT16U DSTRe1 : 1;		// Bit 7
	INT16U RTF : 1;			// Bit 8
	INT16U RTR : 1;			// Bit 9
	INT16U RTF2 : 1;		// Bit 10
	INT16U RTR2 : 1;		// Bit 11
	INT16U Reserved_12 : 1;	// Bit 12
	INT16U LDU : 1;			// Bit 13
	INT16U LDD : 1;			// Bit 14
	INT16U LHP : 1;			// Bit 15
};
typedef struct tagHMI_MW112_Bit  HMI_MW112_Bit;

struct __attribute__((__packed__)) tagHMI_MW112
{
	union
	{
		WORD_User		Word;
		HMI_MW112_Bit	Bit;
	};
};
typedef struct tagHMI_MW112  HMI_Regi_MW112;

struct __attribute__((__packed__)) tagHMI_MW113_Bit
{
	INT16U GOX2 : 1;		// Bit 0
	INT16U GOXH2 : 1;		// Bit 1
	INT16U GOXM2 : 1;		// Bit 2
	INT16U GOXS2 : 1;		// Bit 3
	INT16U GWL2 : 1;		// Bit 4
	INT16U GWR2 : 1;		// Bit 5
	INT16U GWLe2 : 1;		// Bit 6
	INT16U GWRe2 : 1;		// Bit 7
	INT16U GDFL2 : 1;		// Bit 8
	INT16U GDFR2 : 1;		// Bit 9
	INT16U GDRL2 : 1;		// Bit 10
	INT16U GDRR2 : 1;		// Bit 12
	INT16U GHL2 : 1;		// Bit 12
	INT16U GHR2 : 1;		// Bit 13
	INT16U FOKL2 : 1;		// Bit 14
	INT16U FOKR2 : 1;		// Bit 15
};
typedef struct tagHMI_MW113_Bit  HMI_MW113_Bit;

struct __attribute__((__packed__)) tagHMI_MW113
{
	union
	{
		WORD_User		Word;
		HMI_MW113_Bit	Bit;
	};
};
typedef struct tagHMI_MW113  HMI_Regi_MW113;

struct __attribute__((__packed__)) tagHMI_MW114_Bit
{
	INT16U FEL2 : 1;		// Bit 0
	INT16U FER2 : 1;		// Bit 1
	INT16U FCL2 : 1;		// Bit 2
	INT16U FCR2 : 1;		// Bit 3
	INT16U DSTL2 : 1;		// Bit 4
	INT16U DSTR2 : 1;		// Bit 5
	INT16U DSTLe2 : 1;		// Bit 6
	INT16U DSTRe2 : 1;		// Bit 7
	INT16U Reserved_8 : 1;		// Bit 8
	INT16U Reserved_9 : 1;		// Bit 9
	INT16U Reserved_10 : 1;		// Bit 10
	INT16U Reserved_11 : 1;		// Bit 11
	INT16U Reserved_12 : 1;		// Bit 12
	INT16U Reserved_13 : 1;		// Bit 13
	INT16U Reserved_14 : 1;		// Bit 14
	INT16U Reserved_15 : 1;		// Bit 15
};
typedef struct tagHMI_MW114_Bit  HMI_MW114_Bit;

struct __attribute__((__packed__)) tagHMI_MW114
{
	union
	{
		WORD_User		Word;
		HMI_MW114_Bit	Bit;
	};
};
typedef struct tagHMI_MW114  HMI_Regi_MW114;

struct __attribute__((__packed__)) tagHMI_MW115_Bit
{
	INT16U FML1 : 1;		// Bit 0
	INT16U FMR1 : 1;		// Bit 1
	INT16U FHL1 : 1;		// Bit 2
	INT16U FHR1 : 1;		// Bit 3
	INT16U FML2 : 1;		// Bit 4
	INT16U FMR2 : 1;		// Bit 5
	INT16U FHL2 : 1;		// Bit 6
	INT16U FHR2 : 1;		// Bit 7
	INT16U ODSTL1 : 1;		// Bit 8
	INT16U ODSTR1 : 1;		// Bit 9
	INT16U DSTLR1 : 1;		// Bit 10
	INT16U DSTRR1 : 1;		// Bit 11
	INT16U ODSTL2 : 1;		// Bit 12
	INT16U ODSTR2 : 1;		// Bit 13
	INT16U DSTLR2 : 1;		// Bit 14
	INT16U DSTRR2 : 1;		// Bit 15
};
typedef struct tagHMI_MW115_Bit  HMI_MW115_Bit;

struct __attribute__((__packed__)) tagHMI_MW115
{
	union
	{
		WORD_User		Word;
		HMI_MW115_Bit	Bit;
	};
};
typedef struct tagHMI_MW115  HMI_Regi_MW115;

struct __attribute__((__packed__)) tagHMI_Time_Byte
{
	INT16U Minutes : 8;
	INT16U Hours : 8;
};
typedef struct tagHMI_Time_Byte  HMI_Time_Byte;

struct __attribute__((__packed__)) tagHMI_MW134
{
	union
	{
		WORD_User		Word;
		HMI_Time_Byte	Byte;
	};
};
typedef struct tagHMI_MW134  HMI_MW134;

struct __attribute__((__packed__)) tagHMI_MW136_Bit
{
	INT16U Value : 15;
	INT16U Flag : 1;
};
typedef struct tagHMI_MW136_Bit  HMI_MW136_Bit;

struct __attribute__((__packed__)) tagHMI_MW136
{
	union
	{
		WORD_User		Word;
		HMI_MW136_Bit	Byte;
	};
};
typedef struct tagHMI_MW136  HMI_MW136;

struct __attribute__((__packed__)) tagHMI_MW139
{
	union
	{
		WORD_User		Word;
		HMI_Time_Byte	Byte;
	};
};
typedef struct tagHMI_MW139  HMI_MW139;

struct __attribute__((__packed__)) tagHMI_SystemData
{
	WORD_User Current_Year;		// MW131
	WORD_User Current_Mon;		// MW132
	WORD_User Current_Date;		// MW133

	HMI_MW134 Current_Time;		// MW134

	WORD_User PageNum;			// MW135

	HMI_MW136 Set_Year;			// MW136
	WORD_User Set_Mon;			// MW137
	WORD_User Set_Date;			// MW138

	HMI_MW139 Set_Time;			// MW139
};
typedef struct tagHMI_SystemData  HMI_SystemData;


struct __attribute__((__packed__)) tagHMI_Realtime_Str
{
	HMI_Regi_MW0	MW0;
	HMI_Regi_MW1	MW1;
	HMI_Regi_MW2	MW2;
	WORD_User		MW3;
	HMI_Regi_MW4	MW4;
	HMI_Regi_MW5    MW5;
	WORD_User       MW6;
	WORD_User       MW7;
	WORD_User       MW8;
	WORD_User       MW9;	
	WORD_User       MW10;	
	WORD_User       MW11;	
	DWORD_User      MW12;	
	DWORD_User      MW14;
	DWORD_User      MW16;
	DWORD_User      MW18;
	DWORD_User      MW20;
	DWORD_User      MW22;
	DWORD_User      MW24;
	DWORD_User      MW26;
	WORD_User		MW28;
	WORD_User 		MW29;
	WORD_User 		MW30;
	WORD_User 		MW31;
	WORD_User 		MW32;
	WORD_User 		MW33;
	WORD_User 		MW34;
	WORD_User 		MW35;
	WORD_User 		MW36;
	WORD_User 		MW37;
	WORD_User 		MW38;
	WORD_User 		MW39;
	WORD_User 		MW40;
	WORD_User 		MW41;
	WORD_User 		MW42;
	WORD_User 		MW43;
	WORD_User 		MW44;
	WORD_User 		MW45;
	WORD_User 		MW46;
	WORD_User 		MW47;
	WORD_User 		MW48;
	WORD_User 		MW49;
	WORD_User 		MW50;
	WORD_User 		MW51;
	WORD_User 		MW52;
	WORD_User 		MW53;
	WORD_User 		MW54;
	WORD_User 		MW55;
	WORD_User 		MW56;
	WORD_User 		MW57;
	WORD_User 		MW58;
	WORD_User 		MW59;
	WORD_User 		MW60;
	WORD_User 		MW61;
	WORD_User 		MW62;
	WORD_User 		MW63;
	WORD_User 		MW64;
	WORD_User 		MW65;
	WORD_User 		MW66;				// [Mode] Main Warning Code
	WORD_User 		MW67;				// [Mode] Sub Warning Code
	WORD_User		MW_Not_Define0[33];
	HMI_Regi_MW101	MW101;
	WORD_User		MW102;
	HMI_Regi_MW103	MW103;
	HMI_Regi_MW104	MW104;
	HMI_Regi_MW105	MW105;
	HMI_Regi_MW106	MW106;
	HMI_Regi_MW107	MW107;
	HMI_Regi_MW108	MW108;
	HMI_Regi_MW109	MW109;
	HMI_Regi_MW110	MW110;
	HMI_Regi_MW111	MW111;
	HMI_Regi_MW112	MW112;
	HMI_Regi_MW113	MW113;
	HMI_Regi_MW114	MW114;
	HMI_Regi_MW115	MW115;
	WORD_User		MW_Not_Define1;
};
typedef struct tagHMI_Realtime_Str  HMI_Realtime_Str;

struct __attribute__((__packed__)) tagHMI_RealTime_Register
{
	union
	{
		WORD_User			Word[117];
		HMI_Realtime_Str	Register;
	};
};
typedef struct tagHMI_RealTime_Register  HMI_RealTime_Register;

struct __attribute__((__packed__)) tagHMI_Register_Str
{
	HMI_RealTime_Register	RealTime;
};
typedef struct tagHMI_Register_Str  HMI_Register;


struct __attribute__((__packed__)) tagHMI_Realtime_Str1
{
	HMI_Regi_MW0	MW0;
	HMI_Regi_MW1	MW1;
	HMI_Regi_MW2	MW2;
	WORD_User		MW3;			// Page Number
	HMI_Regi_MW4	MW4;
	HMI_Regi_MW5    MW5;
	WORD_User       MW6;
	WORD_User       MW7;
	WORD_User       MW8;
	WORD_User       MW9;
	WORD_User       MW10;
	WORD_User       MW11;
	DWORD_User      MW12;
	DWORD_User      MW14;
	DWORD_User      MW16;
	DWORD_User      MW18;
	DWORD_User      MW20;
	DWORD_User      MW22;
	DWORD_User      MW24;
	DWORD_User      MW26;
	WORD_User		MW28;
	WORD_User 		MW29;
	WORD_User 		MW30;
	WORD_User 		MW31;
	WORD_User 		MW32;
	WORD_User 		MW33;
	WORD_User 		MW34;
	WORD_User 		MW35;
	WORD_User 		MW36;
	WORD_User 		MW37;
	WORD_User 		MW38;
	WORD_User 		MW39;
	WORD_User 		MW40;
	WORD_User 		MW41;
	WORD_User 		MW42;
	WORD_User 		MW43;
	WORD_User 		MW44;
	WORD_User 		MW45;
	WORD_User 		MW46;
	WORD_User 		MW47;
	WORD_User 		MW48;
	WORD_User 		MW49;
	WORD_User 		MW50;
	WORD_User 		MW51;
	WORD_User 		MW52;
	WORD_User 		MW53;
	WORD_User 		MW54;
	WORD_User 		MW55;
	WORD_User 		MW56;
	WORD_User 		MW57;
	WORD_User 		MW58;
	WORD_User 		MW59;
	WORD_User 		MW60;
	WORD_User 		MW61;
	WORD_User 		MW62;
	WORD_User 		MW63;
	WORD_User 		MW64;
	WORD_User 		MW65;
	WORD_User 		MW66;				// [Mode] Main Warning Code
	WORD_User 		MW67;				// [Mode] Sub Warning Code
	WORD_User		MW_Not_Define0[33];
	HMI_Regi_MW101	MW101;
	WORD_User		MW102;
	HMI_Regi_MW103	MW103;
	HMI_Regi_MW104	MW104;
	HMI_Regi_MW105	MW105;
	HMI_Regi_MW106	MW106;
	HMI_Regi_MW107	MW107;
	HMI_Regi_MW108	MW108;
	HMI_Regi_MW109	MW109;
	HMI_Regi_MW110	MW110;
	HMI_Regi_MW111	MW111;
	HMI_Regi_MW112	MW112;
	HMI_Regi_MW113	MW113;
	HMI_Regi_MW114	MW114;
	HMI_Regi_MW115	MW115;
	WORD_User		MW116;
	WORD_User		MW117;
	WORD_User		MW118;
	WORD_User		MW119;
	WORD_User		MW120;
	WORD_User		MW121;
	WORD_User		MW122;
	WORD_User		MW123;
	WORD_User		MW124;
	WORD_User		MW125;
	WORD_User		MW126;
	WORD_User		MW127;
	WORD_User		MW128;
	WORD_User		MW129;
	WORD_User		MW130;
	HMI_SystemData	SystemData;
};
typedef struct tagHMI_Realtime_Str1  HMI_Realtime_Str1;

struct __attribute__((__packed__)) tagHMI_RealTime_Register1
{
	union
	{
		WORD_User			Word[140];
		HMI_Realtime_Str1	Register;
	};
};
typedef struct tagHMI_RealTime_Register1  HMI_RealTime_Register1;

struct __attribute__((__packed__)) tagHMI_Register_Str1
{
	HMI_RealTime_Register1	RealTime;
};
typedef struct tagHMI_Register_Str1  HMI_Register1;

enum enumHMI_OPERATION_FLAG {
	HMI_STAND_BY = 0,
	HMI_READ_REALTIME_REGISTER,
	HMI_READ_SYS_TIME,
	HMI_WRITE_REALTIME_REGISTER,
	HMI_WRITE_REALTIME_MW1,
	HMI_WRITE_SYS_TIME,
};

enum enumHMI_REGISTER_ADDRRESS {
	HMI_ADDRESS_REALTIME = 0,
	HMI_ADDRESS_SYS_TIME = 131,
	HMI_ADDRESS_PAGE_NO = 135,
	HMI_ADDRESS_SYS_TIME_SET = 136,
};

#define TCP_SOCKET_HMI			(1)
#define HMI_UNIT_ID	(0)

struct __attribute__((__packed__)) tagHMI_Control
{
	HMI_Regi_MW0	MW0;
	HMI_Regi_MW1	MW1;
	HMI_Regi_MW2	MW2;
};
typedef struct tagHMI_Control  HMI_Control;

struct __attribute__((__packed__)) tagHMI_Com
{
	INT08U			Req_Flag;
	INT08U			Req_DataCount;
	INT16U			Req_StatAddress;

	INT16U			nTx_Data_Count;

	INT08U			Recv_Flag;

	INT08U			Mode;

	INT32U			ConnectTimer;
	HMI_Control		ControlFlag;

	INT08U			Manual_Ctr_Flag;
};
typedef struct tagHMI_Com  HMI_Com;


//extern MoviC_RxPDO  m_SRM_RxPDO[INVERTOR_INSTALL_COUNT];

// PDO4      PDO5        PDO6        PDO7
// Speed     Accel       Decel       Jerk
#define INV_TRAVEL	0	// 80m/min  500mm/s^2  500mm/s^2   500mm/s^2
#define INV_HOIST    1	// 240m/min  600mm/s^2  600mm/s^2   600mm/s^2
#define INV_FORK_1	2	//  80m/min   200mm/s^2   200mm/s^2  200mm/s^2
#define INV_FORK_2	3	//  80m/min   200mm/s^2   200mm/s^2  200mm/s^2

#define FORK_1	0	//
#define FORK_2	1	//

#define DEFAULT_SINGLE_FORK_DEPTH		(1500)		// 랙설정 Fork Depth 범위

#define RACK_SET_TRAV_START				(-10000)	//

#define RACK_SET_LIFT_START				(-10000)	//

#define RACK_SET_VERIENT_LT_OFFSET	(255)	//

//#define RACK_SET_LEVEL_UP_OFFSET_MAX		(200)	//
#define RACK_SET_LEVEL_UP_OFFSET_MAX		(255)	//
#define RACK_SET_LEVEL_UP_OFFSET_MIN		(20)	//

#define RACK_SET_LEVEL_DN_OFFSET_MAX		(-20)	//
#define RACK_SET_LEVEL_DN_OFFSET_MIN		(-128)	// insigned int

//#define MAX_TRAVEL_VEL_AUTO			(210)	// m/min
//#define MAX_TRAVEL_VEL_AUTO			(220)	// m/min, 2024. 04. 25 동원시스템즈
#define MAX_TRAVEL_VEL_AUTO			(300)	// m/min, 2025. 02. 13 한타 TP2

#define MAX_TRAVEL_VEL_MAN_M		(50)	// m/min

#define MAX_TRAVEL_VEL_MAN_L		(5)	// m/min

#define MAX_TRAVEL_VEL_FORCE		(5)	// m/min
#define MAX_TRAVEL_VEL_CREEP		(2)	// m/min

//#define MAX_TRAVEL_ACC				(600)	// mm/s^2
//#define MAX_TRAVEL_DEC				(600)	// mm/s^2

#define MAX_TRAVEL_ACC				(5000)	// mm/s^2, 2025. 02. 13 한타 TP2
#define MAX_TRAVEL_DEC				(5000)	// mm/s^2, 2025. 02. 13 한타 TP2

#define MAX_TRAVEL_JERK				(5000)	// ms
//#define MIN_TRAVEL_JERK				(1000)	// ms
#define MIN_TRAVEL_JERK				(100)	// ms


//#define MAX_LIFT_VEL_AUTO_H	(63)	// m/min, 무부하
#define MAX_LIFT_VEL_AUTO_H		(150)	// m/min, 무부하, 2025. 02. 13 한타 TP2

//#define MAX_LIFT_VEL_AUTO_M	(50)	// m/min
#define MAX_LIFT_VEL_AUTO_M		(150)	// m/min, 부하, 2025. 02. 13 한타 TP2

#define MAX_LIFT_VEL_MAN_M		(30)	// m/min
#define MAX_LIFT_VEL_MAN_L		(10)	// m/min

// #define MAX_LIFT_ACC			(500)	// mm/s^2
// #define MAX_LIFT_DEC			(500)	// mm/s^2

#define MAX_LIFT_ACC			(5000)	// mm/s^2, 2025. 02. 13 한타 TP2
#define MAX_LIFT_DEC			(5000)	// mm/s^2, 2025. 02. 13 한타 TP2

#define MAX_LIFT_JERK			(5000)	// ms
//#define MIN_LIFT_JERK			(1000)	// ms
#define MIN_LIFT_JERK			(100)	// ms

//#define MAX_FORK_VEL_AUTO		(100)	// m/min
#define MAX_FORK_VEL_AUTO		(60)	// m/min
#define MAX_FORK_VEL_MAN		(15)	// m/min

//#define MAX_FORK_ACC			(1000)	// mm/s^2
//#define MAX_FORK_DEC			(1000)	// mm/s^2

#define MAX_FORK_ACC			(5000)	// mm/s^2, 2025. 02. 13 한타 TP2
#define MAX_FORK_DEC			(5000)	// mm/s^2, 2025. 02. 13 한타 TP2

#define MAX_FORK_JERK			(5000)	// ms, 
#define MIN_FORK_JERK			(100)	// ms, 

#define MIN_POSITION				(-999999)
#define MAX_POSITION				(999999)


#define AUTO_TEACH_LIFT_SOFT_MARGIN_LOW_MM   (20) //PCE 260604
#define AUTO_TEACH_LIFT_SOFT_MARGIN_HIGH_MM  (20) //PCE 260604

#define MIN_TRAV_IN_POS			(1)
//#define MAX_TRAV_IN_POS			(5)
#define MAX_TRAV_IN_POS			(10)

#define MIN_TRAV_HYSTERESIS		(1)
//#define MAX_TRAV_HYSTERESIS		(5)
#define MAX_TRAV_HYSTERESIS		(100)

#define MIN_LIFT_IN_POS			(1)
//#define MAX_LIFT_IN_POS			(5)
#define MAX_LIFT_IN_POS			(10)

#define MIN_LIFT_HYSTERESIS		(1)
//#define MAX_LIFT_HYSTERESIS		(5)
#define MAX_LIFT_HYSTERESIS		(100)

#define MIN_FORK_IN_POS			(1)
//#define MAX_FORK_IN_POS			(5)
#define MAX_FORK_IN_POS			(10)

#define MIN_FORK_HYSTERESIS		(1)
//#define MAX_FORK_HYSTERESIS		(5)
#define MAX_FORK_HYSTERESIS		(10)

/*
#define MIN_FORK_ORIGIN_OFFSET			(0)
#define MAX_FORK_ORIGIN_OFFSET			(50)
*/

/*
#define MIN_FORK_ORIGIN_OFFSET			(-30)
#define MAX_FORK_ORIGIN_OFFSET			(30)
*/

// 2025. 3. 23 한국타이어 TP2
#define MIN_FORK_ORIGIN_OFFSET			(-100)
#define MAX_FORK_ORIGIN_OFFSET			(100)

#define MIN_TRAV_OVERTORQUE				(100)	// 10.0%
#define MAX_TRAV_OVERTORQUE				(2000)	// 200.0%

#define MIN_LIFT_OVERTORQUE				(100)	// 10.0%
#define MAX_LIFT_OVERTORQUE				(2000)	// 200.0%

#define MIN_FORK_OVERTORQUE				(100)	// 10.0%
#define MAX_FORK_OVERTORQUE				(2000)	// 200.0%

#define MIN_BRAKE_ON_TIME				(1)		// 0.01 sec
#define MAX_BRAKE_ON_TIME				(60000)	// 600.00 sec

#define MIN_FORK_AUTO_HOME_CNT			(0)		// 0
#define MAX_FORK_AUTO_HOME_CNT			(10000)	// 10000 cnt

#define MIN_DEALY_TIME					(0)		// 0.00 sec
#define MAX_DELAY_TIME					(60000)	// 600.00 sec

#define MIN_POSI_LAG_RETRY_CNT			(0)		// 
#define MAX_POSI_LAG_RETRY_CNT			(10)	// 

#define MIN_POSI_LAG_RETRY_MM			(0)		// 
#define MAX_POSI_LAG_RETRY_MM			(200)	// 

#define MIN_FORCE_MODE_RELEASE_TIME		(0)		// 
#define MAX_FORCE_MODE_RELEASE_TIME		(1000)	// 

#define MIN_FAN_ON_TIME				(0)		// 0 sec
#define MAX_FAN_ON_TIME				(1000)	// 1000 sec

#define MIN_BZ_FAULT_ON_TIME		(0)		// 0.00 sec
#define MAX_BZ_FAULT_ON_TIME		(60000)	// 600.00 sec

#define MIN_BZ_WARNING_ON_TIME		(0)		// 0.00 sec
#define MAX_BZ_WARNING_ON_TIME		(60000)	// 600.00 sec

#define MIN_BZ_AUTO_MODE_TIME		(0)		// 0.00 sec
#define MAX_BZ_AUTO_MODE_TIME		(60000)	// 600.00 sec

#define MIN_BZ_AUTO_MODE_CNT		(0)		// 
#define MAX_BZ_AUTO_MODE_CNT		(100)	// 

#define MIN_UBK_OPER_CNT			(0)		// 
#define MAX_UBK_OPER_CNT			(100)	// 

#define MIN_UBK_OPER_ON_TIME		(0)		// 0.00 sec
#define MAX_UBK_OPER_ON_TIME		(60000)	// 600.00 sec

#define MIN_UBK_OPER_OFF_TIME		(0)		// 0.00 sec
#define MAX_UBK_OPER_OFF_TIME		(60000)	// 600.00 sec

#define MIN_RACK_BAY_COUNT			(1)		//
#define MAX_RACK_BAY_COUNT			(256)	//

#define MIN_RACK_LEVEL_COUNT		(1)		//
#define MAX_RACK_LEVEL_COUNT		(128)	//

#define MIN_RACK_OFFSET_MM			(-125)		//
#define MAX_RACK_OFFSET_MM			(125)	//

#define DEF_TRAV_IN_POS_OFFSET		(5)
#define DEF_LIFT_IN_POS_OFFSET		(5)
#define DEF_FORK_IN_POS_OFFSET		(5)

#define DEF_TRAV_POS_HYSTERESIS		(1)
#define DEF_LIFT_POS_HYSTERESIS		(1)
#define DEF_FORK_POS_HYSTERESIS		(1)

#define DEF_MAN_FORK_IN_POS_OFFSET		(2)

//#define DEF_FORK_ORIGIN_OFFSET		(15)
#define DEF_FORK_ORIGIN_OFFSET		(17)

#define DEF_FORK_CENTER_OFFSET		(4)		// 포크 중심 Offset

#define DEF_STATION_POS_OFFSET		(200)

#define DEF_MANUAL_CTR_TIMEOUT		(1500)		// 상위 명령 송신시간 설정에 따라 변경되야 함. (상위 설정 500mm)

#define DEF_POSITION_OFFSET			(1)			// 정지상태에서 정위치 Offset

#define DEF_MOVE_POS_OFFSET			(2)			// 이동 후 정위치 Offset

#define DEF_DEALY_TRAV_LEFT_MOVE_SEQ	(100)

#define DEF_FORK_STORE_OFFSET			(0)		// 화물 적재시 Rack Depth Offset, 닫힘 레버와 박스 간섭을 막기위해 추가.

#define DEF_DELAY_BEFORE_MOVE				(500)
#define DEF_DELAY_AFTER_MOVE				(500)
//#define DEF_DELAY_AFTER_MOVE				(1000)
#define DEF_DELAY_PRE_FORK_OUT_GET			(500)
#define DEF_DELAY_FORK_OUT_GET				(500)
#define DEF_DELAY_PRE_FK_LIFT_GET			(500)
#define DEF_DELAY_FK_LIFT_GET				(500)
#define DEF_DELAY_PRE_FK_IN_GET				(500)
#define DEF_DELAY_FK_IN_GET					(500)
#define DEF_DELAY_CHK_GOX_GET				(1000)

#define DEF_TIMEOUT_MOVE					(600000)	// 10min
#define DEF_TIMEOUT_FORK_MOVE				(20000)
//#define DEF_TIMEOUT_PRE_FK_LIFT_GET		(20000)
#define DEF_TIMEOUT_FORK_OUT_LIFT			(20000)
//#define DEF_TIMEOUT_PRE_FK_IN_GET			(20000)
#define DEF_TIMEOUT_FK_CENTER				(20000)
#define DEF_TIMEOUT_CHK_GOX					(5000)
#define DEF_TIMEOUT_WAIT_INTERLOCK			(5000)

#define DEF_DELAY_PRE_FORK_OUT_PUT			(500)
#define DEF_DELAY_FORK_OUT_PUT				(500)
#define DEF_DELAY_PRE_FK_LIFT_PUT			(500)
#define DEF_DELAY_FK_LIFT_PUT				(500)
#define DEF_DELAY_PRE_FK_IN_PUT				(500)
#define DEF_DELAY_FK_IN_PUT					(500)
#define DEF_DELAY_CHK_GOX_PUT				(500)

#define DEF_TIMEOUT_PRE_FORK_OUT_PUT		(20000)
#define DEF_TIMEOUT_FORK_OUT_PUT			(20000)
#define DEF_TIMEOUT_PRE_FK_LIFT_PUT			(20000)
#define DEF_TIMEOUT_FK_LIFT_PUT				(20000)
#define DEF_TIMEOUT_PRE_FK_IN_PUT			(20000)
#define DEF_TIMEOUT_FK_IN_PUT				(20000)
#define DEF_TIMEOUT_CHK_GOX_PUT				(5000)

#define DEF_FORK_MANUAL_LOW_SPEED_AREA		(250)

/*
#define DEF_TRAV_MANUAL_STOP_DELAY			(1500)
#define DEF_LIFT_MANUAL_STOP_DELAY			(1000)
#define DEF_FORK_MANUAL_STOP_DELAY			(100)
*/

#define DEF_TRAV_MANUAL_STOP_DELAY			(100)
#define DEF_LIFT_MANUAL_STOP_DELAY			(100)
#define DEF_FORK_MANUAL_STOP_DELAY			(100)

#define DEF_TRAV_MOVE_SYNCTIME_OFFSET		(2300)	// ms
//#define DEF_TRAV_MOVE_SYNCTIME_OFFSET		(3000)	// ms
#define DEF_LIFT_MOVE_SYNC_OFFSET		(-2000)	// ms

#define DEF_TRAV_BRAKE_ON_DELAY			(10)	// second
#define DEF_LIFT_BRAKE_ON_DELAY			(10)	// second

//#define DEF_TRAV_OVERTORQUE			(1000)	// 100.0%
#define DEF_TRAV_OVERTORQUE			(2000)	// 100.0%
//#define DEF_LIFT_OVERTORQUE			(1000)	// 100.0%
#define DEF_LIFT_OVERTORQUE			(2000)	// 100.0%
#define DEF_FORK_OVERTORQUE			(2000)	// 100.0%

#define DEF_FORK_LAG_ERROR_L		(50)
#define DEF_FORK_LAG_ERROR_H		(150)

#define DEF_LT_LEVEL_UP_MM			(80)	// 승강 상위치 기본값
#define DEF_LT_LEVEL_DOWN_MM		(-30)	// 승강 하위치 기본값

#define DEF_TRAVEL_MANUAL_LOW_SPEED_MM				(7000)

#define DEF_TRAVEL_MANUAL_LOW_SPEED_MM_NOT_USE		(0)

#define DEF_LIFT_MANUAL_LOW_SPEED_MM		(1000)

#define DEF_MANUAL_TRAV_LOW_RESTART (3000)
#define DEF_MANUAL_LIFT_LOW_RESTART (3000)

#define DEF_FAULT_BUZZER_INTERVAL	(1000)
#define DEF_WARNING_BUZZER_INTERVAL	(500)

#define DEF_DEFAULT_TRAV_HOME_POS	(1000)
#define DEF_DEFAULT_LIFT_HOME_POS	(1000)

/*
#define DEF_FORK_STOP_DELAY			(300)
#define DEF_FORK_BRAKE_ON_DELAY		(300)
*/
#define DEF_FORK_STOP_DELAY			(200)
#define DEF_FORK_BRAKE_ON_DELAY		(200)

enum enumGRAPH_TYPE {
	GRAPH_START_RECORDING_WHEN_DRIVING_BEGINS = 0,			// 주행 시작시 기록 시작
	GRAPH_START_RECORDING_FROM_THE_SET_DRIVING_LOCATION,	// 설정된 주행 위치부터 기록 시작
	GRAPH_START_RECORDING_IMMEDIATELY,
};

enum enumINVERTER_VENDOR {
	INV_VENDOR_SEW = 1,					// SEW MOVI-C
	INV_VENDOR_SIMENS,
	INV_VENDOR_SEW_VER2,				// SEW 표준프로토콜
	INV_VENDOR_SEW_VER2_ANTI_SWAY,		// SEW 표준프로토콜 + MAC
	INV_VENDOR_SEW_VER2_SYNC_TRAVEL,	// SEW 표준프로토콜 + MAC
};

enum enumFORK_ENCODER_TYPE {
	FORK_ENC_ABSOLUTE = 0,
	FORK_ENC_INCREMENTAL,		// 전원리셋 시, 포크 원점 재설정 필요.
};

enum enumSRM_FORK_TYPE{
	FORK_TYPE_NONE = 0,
	FORK_TYPE_SINGLE_DEEP,
	FORK_TYPE_DOUBLE_DEEP_2POS,
	FORK_TYPE_DOUBLE_DEEP_3POS,
};

enum enumLAMP_COLOR {
	LAMP_OFF = 0x00,
	LAMP_RED = 0x01,
	LAMP_YELLOW = 0x02,
	LAMP_GREEN = 0x04,
	LAMP_BLUE = 0x08,
	LAMP_MAGENTA = 0x10,
	LAMP_CYAN = 0x20,
	LAMP_WHITE = 0x40,
};

enum enumMOTOR_CONTROL_ERROR {
	M_CTR_ERROR_NONE = 0,
	M_CTR_ERROR_VELOCITY,
	M_CTR_ERROR_CMD_SOFT_LIMIT,
	M_CTR_ERROR_CMD_TARGET_POS,
	M_CTR_ERROR_NOT_READY,
	M_CTR_ERROR_IPOS_REF,
	M_CTR_ERROR_FALUT,
	//M_CTR_ERROR_BREAK_REALEASE,
	//M_CTR_ERROR_TIMEOUT,
};

enum enumSRM_MACHINE_STATE {
	SRM_MACHINE_INIT = 0,
	SRM_MACHINE_POWER_ON = 10,
	SRM_MACHINE_DRIVE_ON = 20,
	SRM_MACHINE_MANUAL = 30,
	SRM_MACHINE_STAND_BY_0 = 40,
	SRM_MACHINE_STAND_BY_1 = 50,
	SRM_MACHINE_ONLINE = 60,
	SRM_MACHINE_SETUP = 70,
	SRM_MACHINE_FAULT = 80,
};

enum enumSRM_FORK_ORIGIN_SENSOR {
	FORK_ORIGIN_FCL = 0,
	FORK_ORIGIN_FCR,
};

enum enumMANUAL_CONTROL_FLAG {
	MAN_CTR_NONE = 0,
	MAN_CTR_TRAV,
	MAN_CTR_LIFT,
	MAN_CTR_FORK_1,
	MAN_CTR_FORK_2,
};

/*
enum enumSRM_MACHINE_STATE_SEQ {
	SRM_MACHINE_STATE_ = 0,
	SRM_MACHINE_POWER_ON,
	SRM_MACHINE_DRIVE_ON,
	SRM_MACHINE_MANUAL,
	SRM_MACHINE_STAND_BY_0,
	SRM_MACHINE_STAND_BY_1,
	SRM_MACHINE_ONLINE,
	SRM_MACHINE_SETUP,
	SRM_MACHINE_FAULT,
};
*/

enum enumPOSITION_FORK_INDEX {
	POS_FORK_1 = 0,
	POS_FORK_2,
	MAX_FEED_COUNT
};

enum enumFORK_MOVE_DIR {
	FORK_MOVE_LEFT = 0,
	FORK_MOVE_RIGHT,
	FORK_MOVE_CENTER,
};

enum enumFORK_ACTION {
	WORK_MOVE_ONLY = 0,
	WORK_FORK1_GET,			// #1 적재
	WORK_FORK2_GET,			// #2 적재
	WORK_FORKB_GET,			// #1, #2 적재
	WORK_FORK1_PUT,			// #1 이재
	WORK_FORK2_PUT,			// #2 이재
	WORK_FORKB_PUT,			// #1, #2 이재
	WORK_FORK1_STICKY,
	WORK_FORKB_TEST,
};

enum enumTARVEL_MOVE_FLAG {
	TRAV_NO_MOVEMNT = 0,
	TRAV_MOVE_FORWARD,
	TRAV_MOVE_REVERSE,
};

enum enumLIFT_MOVE_FLAG {
	LIFT_NO_MOVEMNT = 0,
	LIFT_MOVE_UP,
	LIFT_MOVE_DOWN,
};

enum enumFORK_JOG_CONTROL {
	JOG_FORK_APP_STOP = 0,
	JOG_FORK_RIGHT,
	JOG_FORK_LEFT,
	JOG_FORK_STOP_1,
	JOG_FORK_STOP_R,	// 조그 운전중 정지
	JOG_FORK_STOP_L,	// 조그 운전중 정지

	JOG_FORK_STOP_R_1,	// 조그 운전중 정지, 브레이크 MC 제어타입
	JOG_FORK_STOP_L_1,	// 조그 운전중 정지, 브레이크 MC 제어타입
};

enum enumTRAV_JOG_CONTROL {
	JOG_TRAV_STOP_BRAKE_ON = 0,
	JOG_TRAV_REVERSE,
	JOG_TRAV_FORWARD,
	JOG_TRAV_STOP_MOVE,	// 조그 운전중 정지
	JOG_TRAV_BRAKE,
};

enum enumLIFT_JOG_CONTROL {
	JOG_LIFT_STOP_BRAKE_ON = 0,
	JOG_LIFT_DOWN,
	JOG_LIFT_UP,
	JOG_LIFT_STOP_MOVE,	// 조그 운전중 정지
	JOG_LIFT_BRAKE,
};

enum enumRACK_POSITON {
	RACK_LEFT = 0,
	RACK_RIGHT,
};

enum enumFORK_MOVE_FLAG {
	FORK_MOVE_CENTER_TO_FEL_NO_LOAD = 0,	// 화물무, Center -> FEL
	FORK_MOVE_FEL_TO_CENTER_NO_LOAD,		// 화물무, FEL -> Center
	FORK_MOVE_CENTER_TO_FER_NO_LOAD,		// 화물무, Center -> FER
	FORK_MOVE_FER_TO_CENTER_NO_LOAD,		// 화물무, FER -> Center
	FORK_MOVE_CENTER_TO_FML_NO_LOAD,		// 화물무, Center -> FML
	FORK_MOVE_FML_TO_CENTER_NO_LOAD,		// 화물무, FML -> Center
	FORK_MOVE_CENTER_TO_FMR_NO_LOAD,		// 화물무, Center -> FMR
	FORK_MOVE_FMR_TO_CENTER_NO_LOAD,		// 화물무, FMR -> Center
	FORK_MOVE_CENTER_TO_FHL_NO_LOAD,		// 화물무, Center -> FHL
	FORK_MOVE_FHL_TO_CENTER_NO_LOAD,		// 화물무, FHL -> Center
	FORK_MOVE_CENTER_TO_FHR_NO_LOAD,		// 화물무, Center -> FHR
	FORK_MOVE_FHR_TO_CENTER_NO_LOAD,		// 화물무, FHR -> Center
	FORK_MOVE_CENTER_TO_FEL_LOAD,			// 화물유, Center -> FEL
	FORK_MOVE_FEL_TO_CENTER_LOAD,			// 화물유, FEL -> Center
	FORK_MOVE_CENTER_TO_FER_LOAD,			// 화물유, Center -> FER
	FORK_MOVE_FER_TO_CENTER_LOAD,			// 화물유, FER -> Center
	FORK_MOVE_CENTER_TO_FML_LOAD,			// 화물유, Center -> FML
	FORK_MOVE_FML_TO_CENTER_LOAD,			// 화물유, FML -> Center
	FORK_MOVE_CENTER_TO_FMR_LOAD,			// 화물유, Center -> FMR
	FORK_MOVE_FMR_TO_CENTER_LOAD,			// 화물유, FMR -> Center
	FORK_MOVE_CENTER_TO_FHL_LOAD,			// 화물유, Center -> FHL
	FORK_MOVE_FHL_TO_CENTER_LOAD,			// 화물유, FHL -> Center
	FORK_MOVE_CENTER_TO_FHR_LOAD,			// 화물유, Center -> FHR
	FORK_MOVE_FHR_TO_CENTER_LOAD,			// 화물유, FHR -> Center
};

enum enumDEVICE_MODE {
	DEVICE_SETUP_MODE = 0,
	DEVICE_MANUAL_MODE,
	DEVICE_SEMI_AUTO_MODE,
	DEVICE_AUTO_MODE,
};

enum enumTRAVEL_LIMIT_STATE {
	TRAVEL_LIMIT_NONE = 0,
	TRAVEL_LIMIT_FWD,
	TRAVEL_LIMIT_RVS,
};

enum enumHOIST_LIMIT_STATE {
	HOIST_LIMIT_NONE = 0,
	HOIST_LIMIT_DOWN,
	HOIST_LIMIT_UP,
};

enum enumSRM_RUN_SEQ {
	RUN_SEQ_STAND_BY = 0,

	RUN_SEQ_START,

	RUN_SEQ_PREPARE_MOVE_0,
	
	RUN_SEQ_PREPARE_MOVE_BRAKE_RELEASE_0,		// 주행. 승강 브레이크 해제 확인
	RUN_SEQ_PREPARE_MOVE_BRAKE_RELEASE_1,
	
	RUN_SEQ_MOVE_BEFORE_DELAY,			// 주행, 승강 이동 전 대기
	RUN_SEQ_START_MOVE_0,			// 주행, 승강 동작 명령 전송

	RUN_SEQ_START_MOVE_1,			// 주행, 승강 브레이크 해제시간 측정
	RUN_SEQ_TRAV_LIFT_MOVING,
	RUN_SEQ_TRAV_LIFT_STABILZATION_TIME,	// 이동 완료 후, 안정화 시간처리
	RUN_SEQ_TRAV_LIFT_AFTER_MOVE,

	RUN_SEQ_FORK_START,

	RUN_SEQ_LOADING_START = 30,
	RUN_SEQ_LOADING_INTERLOCK,					// 
	RUN_SEQ_LOADING_INTERLOCK_NO_USE,			// 
	RUN_SEQ_LOADING_PRE_FORK_OUT,				// 
	RUN_SEQ_LOADING_FORK_OUT,					//	화물 적재 Fork Out
	RUN_SEQ_LOADING_AFTER_FORK_OUT,				//	화물 적재 Fork Out
	RUN_SEQ_LOADING_FORK_OUT_PRE_LIFT,			//
	RUN_SEQ_LOADING_FORK_OUT_LIFT_UP,			//
	RUN_SEQ_LOADING_FORK_OUT_AFTER_LIFT_UP,		//
	RUN_SEQ_LOADING_PRE_FORK_IN,				//
	RUN_SEQ_LOADING_FORK_IN,					//
	RUN_SEQ_LOADING_AFTER_FORK_IN,				//
	RUN_SEQ_LOADING_COMPLETE,					// 화물 적재 완료, 화물 확인

	RUN_SEQ_UNLOADING_START = 50,				// 
	RUN_SEQ_UNLOADING_INTERLOCK,
	RUN_SEQ_UNLOADING_INTERLOCK_NO_USE,
	RUN_SEQ_UNLOADING_PRE_FORK_OUT,				// 
	RUN_SEQ_UNLOADING_FORK_OUT,					//
	RUN_SEQ_UNLOADING_AFTER_FORK_OUT,			//
	RUN_SEQ_UNLOADING_FORK_OUT_PRE_LIFT,		//
	RUN_SEQ_UNLOADING_FORK_OUT_LIFT_DOWN,
	RUN_SEQ_UNLOADING_FORK_OUT_AFTER_LIFT_DOWN,
	RUN_SEQ_UNLOADING_FORK_IN,
	RUN_SEQ_UNLOADING_AFTER_FORK_IN,
	RUN_SEQ_UNLOADING_COMPLETE,

	RUN_SEQ_COMPLETE = 70,

	RUN_SEQ_PLC_COM_0 = 85,
	RUN_SEQ_PLC_COM_1,
	RUN_SEQ_PLC_COM_2,
	RUN_SEQ_PLC_COM_3,

	RUN_SEQ_ERROR_FORK_STOP = 90,		// 포크 동작중 에러 발생 정지 
	RUN_SEQ_ERROR_TRAV_LIFF_STOP,		// 주행, 승강중 에러 발생 정지
	RUN_SEQ_ERROR_TRAV_LIFT_STOP_1,
	RUN_SEQ_ERROR_TRAV_LIFT_STOP_2,
	RUN_SEQ_ERROR_TRAV_LIFT_STOP_3,

	RUN_SEQ_FORK_ORIGIN_0 = 100,	//
	RUN_SEQ_FORK_ORIGIN_1,

	RUN_SEQ_TRAV_ORIGIN_0,	//0
	RUN_SEQ_TRAV_ORIGIN_1,

	RUN_SEQ_LIFT_ORIGIN_0,	//
	RUN_SEQ_LIFT_ORIGIN_1,

	RUN_SEQ_LIFT_SET_HORIZONTAL_0 = 110,
	RUN_SEQ_LIFT_SET_HORIZONTAL_1,

	RUN_SEQ_SET_AUTO_RACK_0 = 120,
	RUN_SEQ_SET_AUTO_RACK_1,
	RUN_SEQ_SET_AUTO_RACK_STOP = 125,

	RUN_SEQ_RETURN_HOME_0 = 150,
	RUN_SEQ_RETURN_HOME_0_1,
	RUN_SEQ_RETURN_HOME_0_2,
	RUN_SEQ_RETURN_HOME_1,
	RUN_SEQ_RETURN_HOME_MOVING,			// 홈위치로 이동중
	RUN_SEQ_RETURN_HOME_3,
	RUN_SEQ_RETURN_HOME_4,

	RUN_SEQ_MANUAL_MOVE = 160,

	RUN_SEQ_FORK_PUT_MOVE_ST_0 = 230,
	RUN_SEQ_FORK_PUT_MOVE_ST_1,
	RUN_SEQ_FORK_PUT_MOVE_ST_2,
	RUN_SEQ_FORK_PUT_MOVE_ST_3,
	RUN_SEQ_FORK_PUT_MOVE_ST_4,
	RUN_SEQ_FORK_PUT_MOVE_ST_5,

	RUN_SEQ_FORK1_CHECK_CENTER_0 = 250,
	RUN_SEQ_FORK1_CHECK_CENTER_1,
	RUN_SEQ_FORK2_CHECK_CENTER_0,
	RUN_SEQ_FORK2_CHECK_CENTER_1,
	RUN_SEQ_FORK_ERROR_CENTER,

	RUN_SEQ_FORK_TEST_0 = 270,
	RUN_SEQ_FORK_TEST_1,
	RUN_SEQ_FORK_TEST_2,
	RUN_SEQ_FORK_TEST_3,
	RUN_SEQ_FORK_TEST_4,

	RUN_SEQ_TRAV_SCAN_SENSOR_0 = 280,
	RUN_SEQ_TRAV_SCAN_SENSOR_1,
	RUN_SEQ_TRAV_SCAN_SENSOR_STOP,

	RUN_SEQ_LIFT_SCAN_SENSOR_0 = 290,
	RUN_SEQ_LIFT_SCAN_SENSOR_1,
	RUN_SEQ_LIFT_SCAN_SENSOR_STOP,

	RUN_SEQ_FORK_SCAN_SENSOR_0 = 300,
	RUN_SEQ_FORK_SCAN_SENSOR_1,
	RUN_SEQ_FORK_SCAN_SENSOR_STOP,

	RUN_SEQ_TRAV_SETUP_MOVE_0 = 310,
	RUN_SEQ_TRAV_SETUP_MOVE_1,
	RUN_SEQ_TRAV_SETUP_MOVE_STOP,

	RUN_SEQ_LIFT_SETUP_MOVE_0 = 330,
	RUN_SEQ_LIFT_SETUP_MOVE_1,
	RUN_SEQ_LIFT_SETUP_MOVE_STOP,

	RUN_SEQ_FORK_SETUP_MOVE_0 = 340,
	RUN_SEQ_FORK_SETUP_MOVE_1,
	RUN_SEQ_FORK_SETUP_MOVE_STOP,

	RUN_SEQ_STICKY_START = 400,
	RUN_SEQ_STICKY_PRE_FORK_OUT,				// 
	RUN_SEQ_STICKY_FORK_OUT,					//	화물 적재 Fork Out
	RUN_SEQ_STICKY_AFTER_FORK_OUT,				//	화물 적재 Fork Out
	RUN_SEQ_STICKY_FORK_OUT_PRE_LIFT_UP,		//
	RUN_SEQ_STICKY_FORK_OUT_LIFT_UP,			//
	RUN_SEQ_STICKY_FORK_OUT_AFTER_LIFT_UP,		//
	RUN_SEQ_STICKY_FORK_OUT_PRE_LIFT_DOWN,		//
	RUN_SEQ_STICKY_FORK_OUT_LIFT_DOWN,			//
	RUN_SEQ_STICKY_FORK_OUT_AFTER_LIFT_DOWN,	//
	RUN_SEQ_STICKY_PRE_FORK_IN,					//	화물 이재 Fork In
	RUN_SEQ_STICKY_FORK_IN,						//	화물 이재 Fork In
	RUN_SEQ_STICKY_AFTER_FORK_IN,				//
	RUN_SEQ_STICKY_COMPLETE,					// 	화물 없는지 확인
	
	MAX_RUN_MODE_SEQ,
};

enum enumMANUAL_CTR_MODE {
	MANUAL_CTR_MODE_VEXI = 0,
	MANUAL_CTR_MODE_HMI,
};


enum enumMANUAL_TRAV_CTR {
	MANUAL_CTR_TRAV_STOP = 0,
	MANUAL_CTR_TRAV_FWD_LOW = 1,
	MANUAL_CTR_TRAV_RVS_LOW = 2,
	MANUAL_CTR_TRAV_FWD_MID = 11,
	MANUAL_CTR_TRAV_RVS_MID = 12,
};

enum enumMANUAL_LIFT_CTR {
	MANUAL_CTR_LIFT_STOP = 0,
	MANUAL_CTR_LIFT_UP_LOW = 1,
	MANUAL_CTR_LIFT_DOWN_LOW = 2,
	MANUAL_CTR_LIFT_UP_MID = 11,
	MANUAL_CTR_LIFT_DOWN_MID = 12,
};

enum enumMOVE_POSITION_FLAG {
	MOVE_POSITION_NONE = 0,
	MOVE_POSITION_FORK1_L,
	MOVE_POSITION_FORK1_R,
	MOVE_POSITION_FORK2_L,
	MOVE_POSITION_FORK2_R,
};

enum enumMANUAL_CTR_FORK_DIR {
	MANUAL_CTR_FORK_STOP = 0,
	MANUAL_CTR_FORK_CENTER,
	MANUAL_CTR_FORK_LEFT,
	MANUAL_CTR_FORK_RIGHT,
};

enum enumHMI_MANUAL_KEY_FLAG {
	HMI_MANUAL_KEY_TRAV_FWD_LOW,	
	HMI_MANUAL_KEY_TRAV_RVS_LOW,
	HMI_MANUAL_KEY_TRAV_FWD_MID,
	HMI_MANUAL_KEY_TRAV_RVS_MID,
	HMI_MANUAL_KEY_5,
	HMI_MANUAL_KEY_6,
	HMI_MANUAL_KEY_LIFT_UP_LOW,
	HMI_MANUAL_KEY_LIFT_DOWN_LOW,
	HMI_MANUAL_KEY_LIFT_UP_MID,
	HMI_MANUAL_KEY_LIFT_DOWN_MID,
	HMI_MANUAL_KEY_FORK1_CENTER,
	HMI_MANUAL_KEY_FORK2_CENTER,
	HMI_MANUAL_KEY_FORK1_LEFT,
	HMI_MANUAL_KEY_FORK1_RIGHT,
	HMI_MANUAL_KEY_FORK2_LEFT,
	HMI_MANUAL_KEY_FORK2_RIGHT,

	MAX_HMI_MANUAL_KEY,
};

enum enumHMI_MANUAL_KEY_FLAG2 {
	HMI_MANUAL_KEY2_DB_START,
	HMI_MANUAL_KEY2_BUZZER_OFF,
	HMI_MANUAL_KEY2_RESET_ERROR,
	HMI_MANUAL_KEY2_STOP,
	HMI_MANUAL_KEY2_DELETE_WORK_DATA_FORK1,
	HMI_MANUAL_KEY2_DELETE_WORK_DATA_FORK2,
	HMI_MANUAL_KEY2_JOB_OK_FORK1,
	HMI_MANUAL_KEY2_JOB_OK_FORK2,
	HMI_MANUAL_KEY2_RETURN_HOME,
	HMI_MANUAL_KEY2_9,
	HMI_MANUAL_KEY2_10,
	HMI_MANUAL_KEY2_11,
	HMI_MANUAL_KEY2_12,
	HMI_MANUAL_KEY2_13,
	HMI_MANUAL_KEY2_14,
	HMI_MANUAL_KEY2_FORCED_MODE,
	HMI_MANUAL_KEY2_RACK_POSITION_FORK1_LEFT,
	HMI_MANUAL_KEY2_RACK_POSITION_FORK1_RIGHT,
	HMI_MANUAL_KEY2_RACK_POSITION_FORK2_LEFT,
	HMI_MANUAL_KEY2_RACK_POSITION_FORK2_RIGHT,
	HMI_MANUAL_KEY2_FORK_POSITION_END,
	HMI_MANUAL_KEY2_FORK_POSITION_MID,
	HMI_MANUAL_KEY2_FORK_POSITION_HALF,
	HMI_MANUAL_KEY2_23,
	HMI_MANUAL_KEY2_24,
	HMI_MANUAL_KEY2_25,
	HMI_MANUAL_KEY2_26,
	HMI_MANUAL_KEY2_HOME_TRAV,
	HMI_MANUAL_KEY2_HOME_LIFT,
	HMI_MANUAL_KEY2_HOME_FORK1,
	HMI_MANUAL_KEY2_HOME_FORK2,
	HMI_MANUAL_KEY2_31,
	MAX_HMI_MANUAL_KEY2
};


enum enumMANUAL_CTR_TRAV_SEQ {
	MANUAL_CTR_TRAV_STAND_BY = 0,
	MANUAL_CTR_TRAV_STEP_START,

	MANUAL_CTR_TRAV_STEP_JOG_FWD_LOW,
	MANUAL_CTR_TRAV_STEP_JOG_FWD_MID,
	MANUAL_CTR_TRAV_STEP_JOG_RVS_LOW,
	MANUAL_CTR_TRAV_STEP_JOG_RVS_MID,

	MANUAL_CTR_TRAV_STEP_POSITION = 9,

	MANUAL_CTR_TRAV_STEP_STOP_0 = 10,
	MANUAL_CTR_TRAV_STEP_STOP_1,
	MANUAL_CTR_TRAV_STEP_NO_MOVE,		// No move

	MANUAL_CTR_TRAV_STEP_JOG_STOP_0 = 15,
	MANUAL_CTR_TRAV_STEP_JOG_STOP_1,
	MANUAL_CTR_TRAV_STEP_JOG_STOP_2,

	MANUAL_CTR_TRAV_STEP_POSITION_STOP_0 = 20,
	MANUAL_CTR_TRAV_STEP_POSITION_STOP_1,

	MANUAL_CTR_TRAV_STEP_BRAKE_ON,
};

enum enumMANUAL_CTR_HOIST_SEQ {
	MANUAL_CTR_HOIST_STAND_BY = 0,
	MANUAL_CTR_HOIST_STEP_START,

	MANUAL_CTR_HOIST_STEP_JOG_UP_LOW,
	MANUAL_CTR_HOIST_STEP_JOG_UP_MID,
	MANUAL_CTR_HOIST_STEP_JOG_DOWN_LOW,
	MANUAL_CTR_HOIST_STEP_JOG_DOWN_MID,

	MANUAL_CTR_HOIST_STEP_POSITION = 9,

	MANUAL_CTR_HOIST_STEP_STOP_0 = 10,
	MANUAL_CTR_HOIST_STEP_STOP_1,
	MANUAL_CTR_HOIST_STEP_NO_MOVE,		// No move

	MANUAL_CTR_HOIST_STEP_JOG_STOP_0 = 15,
	MANUAL_CTR_HOIST_STEP_JOG_STOP_1,
	MANUAL_CTR_HOIST_STEP_JOG_STOP_2,

	MANUAL_CTR_HOIST_STEP_POSITION_STOP_0 = 20,
	MANUAL_CTR_HOIST_STEP_POSITION_STOP_1,

	MANUAL_CTR_HOIST_STEP_BRAKE_ON,
};

enum enumMANUAL_CTR_FORK_SEQ {
	MANUAL_CTR_FORK_STAND_BY = 0,
	MANUAL_CTR_FORK_STEP_START,
	MANUAL_CTR_FORK_STEP_START_1,
	MANUAL_CTR_FORK_STEP_START_1_1,
	MANUAL_CTR_FORK_STEP_START_2,

	MANUAL_CTR_FORK_STEP_STOP_0,
	MANUAL_CTR_FORK_STEP_STOP_1,
	MANUAL_CTR_FORK_STEP_STOP_2,

	MANUAL_CTR_FORK_STEP_NO_MOVE,

	MANUAL_CTR_FORK_MOVE_CENTER_0 = 10,
	MANUAL_CTR_FORK_MOVE_CENTER_1,

	MANUAL_CTR_FORK_MOVE_LEFT_0 = 20,
	MANUAL_CTR_FORK_MOVE_LEFT_1,

	MANUAL_CTR_FORK_MOVE_LEFT_1_1,

	MANUAL_CTR_FORK_MOVE_LEFT_2,

	MANUAL_CTR_FORK_MOVE_RIGHT_0 = 30,
	MANUAL_CTR_FORK_MOVE_RIGHT_1,
	MANUAL_CTR_FORK_MOVE_RIGHT_2,

	MANUAL_CTR_FORK_TEST_LEFT_0 = 40,
	MANUAL_CTR_FORK_TEST_LEFT_1,

	MANUAL_CTR_FORK_TEST_RIGHT_0 = 50,
	MANUAL_CTR_FORK_TEST_RIGHT_1,


	MANUAL_CTR_FORK_STEP_END = 100,

};

enum enumMAN_CTR_FORK_MOVE {
	MAN_CTR_FORK_MOVE_STAND_BY = 0,
	MAN_CTR_FORK_MOVE_FROM_CENTER_TO_FHL,
	MAN_CTR_FORK_MOVE_FROM_CENTER_TO_FML,
	MAN_CTR_FORK_MOVE_FROM_CENTER_TO_FEL,
	MAN_CTR_FORK_MOVE_FROM_FHL_TO_FEL,
	MAN_CTR_FORK_MOVE_FROM_FML_TO_FEL,
	MAN_CTR_FORK_MOVE_FROM_FHL_TO_CENTER,
	MAN_CTR_FORK_MOVE_FROM_FML_TO_CENTER,
	MAN_CTR_FORK_MOVE_FROM_FEL_TO_CENTER,
	MAN_CTR_FORK_MOVE_FROM_FEL_TO_FHL,
	MAN_CTR_FORK_MOVE_FROM_FEL_TO_FML,
	MAN_CTR_FORK_MOVE_FROM_CENTER_TO_FHR,
	MAN_CTR_FORK_MOVE_FROM_CENTER_TO_FMR,
	MAN_CTR_FORK_MOVE_FROM_CENTER_TO_FER,
	MAN_CTR_FORK_MOVE_FROM_FHR_TO_FER,
	MAN_CTR_FORK_MOVE_FROM_FMR_TO_FER,
	MAN_CTR_FORK_MOVE_FROM_FHR_TO_CENTER,
	MAN_CTR_FORK_MOVE_FROM_FMR_TO_CENTER,
	MAN_CTR_FORK_MOVE_FROM_FER_TO_CENTER,
	MAN_CTR_FORK_MOVE_FROM_FER_TO_FHR,
	MAN_CTR_FORK_MOVE_FROM_FER_TO_FMR,
};

enum enumMANUAL_CTR_FORK_STOP_CASE {
	MAN_CTR_FORK_STOP_NONE = 0,
	MAN_CTR_FORK_STOP_CASE_1,		// 정지명령 수신.
	MAN_CTR_FORK_STOP_CASE_2,		// An error occurred.
	MAN_CTR_FORK_STOP_CASE_3,		// 강제모드 수동조작중 포크1 인버터이상 발생.
	MAN_CTR_FORK_STOP_CASE_4,		// 상위 수동 조작중 비상정지 동작.(상위: 지상반, Vexi, ...)
	MAN_CTR_FORK_STOP_CASE_5,		// 상위 수동 조작중 안전플러그 동작.(상위: 지상반, Vexi, ...)
	MAN_CTR_FORK_STOP_CASE_6,		// 상위 수동 조작중 명령수신 타임아웃 발생.
	MAN_CTR_FORK_STOP_CASE_7,		// HMI 수동 조작중 비상정지 동작.
	MAN_CTR_FORK_STOP_CASE_8,		// HMI 수동 조작중 명령수신 타임아웃 발생.
	MAN_CTR_FORK_STOP_CASE_9,		// 상위 수동 조작중 기상반 스위치 수동으로 변경.
	MAN_CTR_FORK_STOP_CASE_10,		// HMI 수동 조작중 기상반 스위치 자동으로 변경.
	MAN_CTR_FORK_STOP_CASE_11,		// 상위 수동제어모드에서 모터 정지 및 수동정지 유지상태가 타임아웃 시간 이상유지 시, 동작 정지 처리.  
	MAN_CTR_FORK_STOP_CASE_12,		// HMI 수동제어모드에서 모터 정지 및 수동정지 유지상태가 타임아웃 시간 이상유지 시, 동작 정지 처리.  
	MAN_CTR_FORK_STOP_CASE_13,		// 승강정위치가 아닌 상태
	MAN_CTR_FORK_STOP_CASE_14,		// 포크 좌측 끝위치
	MAN_CTR_FORK_STOP_CASE_15,		// 포크 우측 끝위치
	MAN_CTR_FORK_STOP_CASE_16,		// 포크 원점 미확인 상태
	MAN_CTR_FORK_STOP_CASE_17,		// 스페셜랙 화물 타입 이상
	MAN_CTR_FORK_STOP_CASE_18,		// 포크 진출 불가 상태
	MAN_CTR_FORK_STOP_CASE_19,		// 주행정위치가 아닌 상태
	MAN_CTR_FORK_STOP_CASE_20,		// 포크 위치번호 미확인 상태
	MAN_CTR_FORK_STOP_CASE_21,		// 인터락 이상
	MAN_CTR_FORK_STOP_CASE_22,		// 이동전 정위치 상태
	MAN_CTR_FORK_STOP_CASE_23,		// 동작중 과부하 발생
	MAN_CTR_FORK_STOP_CASE_24,		// 포크 정위치 정지
	MAN_CTR_FORK_STOP_CASE_25,		// 포크 더블딥 위치 설정이 안됨.
	MAN_CTR_FORK_STOP_CASE_26,
	MAN_CTR_FORK_STOP_CASE_27,
	MAN_CTR_FORK_STOP_CASE_28,
	MAN_CTR_FORK_STOP_CASE_29,
	MAN_CTR_FORK_STOP_CASE_30,
	MAN_CTR_FORK_STOP_CASE_31,
	MAN_CTR_FORK_STOP_CASE_32,
	MAN_CTR_FORK_STOP_CASE_33,
	MAN_CTR_FORK_STOP_CASE_34,
	MAN_CTR_FORK_STOP_CASE_35,
	MAN_CTR_FORK_STOP_CASE_36,
	MAN_CTR_FORK_STOP_CASE_37,
	MAN_CTR_FORK_STOP_CASE_38,
	MAN_CTR_FORK_STOP_CASE_39,
	MAN_CTR_FORK_STOP_CASE_40,
};

enum enumAUTO_POS_CTR_FORK_SEQ {
	AUTO_POS_CTR_FORK_STAND_BY = 0,

	AUTO_POS_CTR_FORK_START = 10,
	AUTO_POS_CTR_FORK_RELEASE_BRAKE,
	AUTO_POS_CTR_FORK_MOVE_1,
	AUTO_POS_CTR_FORK_MOVE_2,
	AUTO_POS_CTR_FORK_MOVE_2_1_A,
	AUTO_POS_CTR_FORK_MOVE_2_2_A,
	AUTO_POS_CTR_FORK_MOVE_2_1_B,
	AUTO_POS_CTR_FORK_MOVE_2_2_B,
	AUTO_POS_CTR_FORK_MOVE_2_3,
	AUTO_POS_CTR_FORK_CHK_SENSOR,

	AUTO_POS_CTR_FORK_COMPLETE = 50,

	AUTO_POS_CTR_FORK_ERROR_STOP = 100,
	AUTO_POS_CTR_FORK_STOP_1,
	AUTO_POS_CTR_FORK_STOP_2,
	AUTO_POS_CTR_FORK_STOP_3,

	AUTO_POS_CTR_FORK_USER_STOP = 110,
};

enum enumFORK_BRAKE_TYPE {
	FORK_BRAKE_SEW = 0,
	FORK_BRAKE_MC
};

enum enumFORK_POS_CEHCK {
	FORK_POS_CEHCK_POS_SENSOR = 0,	// 위치값 + 포크센서
	FORK_POS_CEHCK_POS,				// 위치값
};

enum enumHMI_COM_PORT {
	HMI_COM_UPLINK = 0,
	HMI_COM_DOWNLINK,
};

INT08U Get_DI_State(INT08U nPort);

INT08U Control_Manual_Trav_Start(INT08U mode, INT08U nOriginStandard);

INT08U Control_Manual_Lift_Start(INT08U mode, INT08U nOriginStandard);
INT08U Control_Manual_Fork_Start(INT08U mode);

INT08U HMI_Control_Manual_Trav_Start(INT08U mode);
INT08U HMI_Control_Manual_Lift_Start(INT08U mode);
INT08U HMI_Control_Manual_Fork_Start(INT08U mode);

INT08U Get_Cell_Position_Add_Offset_1(CellPosSTR* pPos, INT32U* trav_pos, INT32U* lift_pos, INT16S* fork_Depth);
//void SRM_Home_Return(INT32S nTravHome, INT32S nLiftHome);
INT08U SRM_Move_Home_Cmd();
INT08U SRM_Move_Maintanence_Cmd();
INT08U SRM_Task_work_cmd(TaskCommand* pCmd, INT08U nIndex);
INT08U SRM_Fork_Work_Cmd(WorkCmdSTR* pCmd);
INT08U SRM_Start_On(void);
void SRM_Start_Off(void);
INT08U Is_Exist_Goods(INT08U nFeeding);
INT32S Get_Travel_Position(INT08U nFeeding, INT16U nBayNo);
INT32S Get_Lift_Position(INT08U nFeed, INT16U nLevel);
//INT32S Get_Lift_Position_Dir(INT08U nDir, INT16U nLevelNo);
INT32S Get_Rack_Lift_Position_Dir(INT08U nFeeding, INT08U nPosFlag, INT16U nLevelNo);
INT32S Get_Rack_ForkOut_Lift_Position(INT08U nPosFlag, INT16U nLevelNo, INT08U nGoodFlag);
INT08U Check_Fork_Center_Position(void);

INT08U check_inverter_In_position_reach(INT08U invertor, INT32S position);
INT08U Check_Fork_InPosition(INT32S nTarget_Position);

void Set_LastPosition(INT08U nFlag);

void Save_LastPosition_Proc();
INT08U Check_Trav_Software_Limit(INT32S nPostion);
INT08U Check_Lift_Software_Limit(INT32S nPostion);
INT08U Auto_Teaching_Check_Lift_Software_Limit(INT32S nPosition); ////PCE 260604
INT08U Check_SRM_Error_State();
INT08U CheckCmdCellPosition(INT08U OrderCode, ForkWorkCmdSTR* ForkWorkCmd);
INT08U Check_Task_CellPosition(INT08U nCmd, CellPosSTR* CellPos);
INT08U Check_Prohibit_Rack(CellPosSTR* ptrCell);
INT08U Check_Order_Prohibit_Rack(INT08U OrderCode, ForkWorkCmdSTR* ForkWorkCmd);
INT08U Check_Task_Prohibit_Rack(INT08U nTaskCmd, CellPosSTR* pCellPos);
INT08U Check_Special_Rack(CellPosSTR* ptrCell, INT08U nType);
INT08U Check_Order_Special_Rack(INT08U OrderCode, ForkWorkCmdSTR* ForkWorkCmd);
INT08U Check_Task_Special_Rack(INT08U nTaskCmd, CellPosSTR* pCellPos, INT08U nGoodType);

void Update_Operation_Info_Time(INT08U nInvertor, INT32U nOperationTime_ms);
void Update_Operation_Info_Distance(INT08U nInvertor, INT32U nOperDistance_mm);

void Update_BrakeOpen_CountUp(INT08U nInvertor);
INT32U Read_DelayTime(INT08U nForkAct, INT08U nTimerIndex);
void Clear_Operation_Info_Data();
void Travel_Setup_Move_Position_Start(INT32S nTargetPosition);
void Travel_Setup_Move_Bay_Start(INT32S nTargetPosition);
void Lift_Setup_Move_Position_Start(INT32S nTargetPosition);
void Lift_Setup_Move_Level_Start(INT32S nTargetPosition);
void Fork_Setup_Move_Position_Start(INT32S nTargetPosition);
void Create_Reference_Position();

INT08U Check_Station_CVOK(INT08U nStatinNo);
INT08U Check_Station_CVOK_Rev2(INT08U nStatinNo);
INT08U Check_AutoMode_Station_CVOK_Rev2(INT08U nStatinNo, INT08U nForkJob);
INT08U Get_Station_Interlock_CVNO_State(INT08U nStatinNo);
void Clear_Station_Interlock_Contol();
void Station_Interlock_Control(INT08U nStatinNo, INT08U nFlag);
void Station_Manual_Interlock_Control(INT08U nStatinNo, INT08U nFlag);
INT08U Check_St_ForkOut_DSTx(INT08U nStationNo, INT08U nDir);
INT08U Check_St_ForkOut_DSTx_1(INT08U nStationNo);
INT08U Check_DSTx_Sensor(INT08U nFork, INT08U nDir);
INT08U Check_DSTxR_Sensor(INT08U nFork, INT08U nDir);
INT08U Check_ODSTx_Sensor(INT08U nFork, INT08U nDir);
//void Change_DeviceMode(INT08U nMode);
void Change_DeviceMode(INT08U nMode, INT08U nFoced);
void Update_RealTime_Register();
void SRM_HMI_Manual_Control_Proc(INT08U nNow_SSR);
void SRM_Normal_Stop(void);
void SRM_Emergency_Stop(void);
INT08U SRM_Return_Home(void);
void Update_Maintanance_SRM_Setting_Data(void);
void Check_Limit_State(void);
void SRM_Manager(void);

#endif /* INC_DEV_SRM_H_ */
