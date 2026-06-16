#ifndef _ERROR_CODE_H
#define _ERROR_CODE_H

enum enumERROR1_CODE {
	ERROR1_MAIN_NONE = 0,

	ERROR1_DETECT_FALLING_OBJECT = 2,		// 낙하물 감지
	ERROR1_EMBERGENCY_STOP = 3,				// 비상정지 동작
	ERROR1_SAFETY_PULG_ON = 6,				// 안전플러그 동작
	
	ERROR1_LIFT_ROPE_TENSION = 10,			// 승강 로프텐션 이상
	ERROR1_IN_POSITION = 11,				// 정위치 이상
	ERROR1_RACK_POST_DETECTION = 12,		// 렉 포스트 감지 이상

	ERROR1_GOODS_WIDTH = 20,				// 화물 가로폭 이탈 이상
	ERROR1_GOODS_VERTICAL = 21,				// 화물 세로폭 이탈 이상
	ERROR1_SPECIAL_RACK = 23,				// 스페셜랙 이상
	ERROR1_LIMIT = 26,					// 비상정지 (리미트스위치)

	ERROR1_FORK_SENSOR = 33,			// 포크 센서 이상 (원점)

	ERROR1_LIFT_SENSOR = 38,			// 승강 센서 이상 (감속, 원점)
	ERROR1_TRAVEL_SENSOR = 39,			// 주행 센서 이상 (감속, 원점)

	ERROR1_POWER_REGENERATION = 42,		// 전력 회생 유닛 이상, 미적용
	ERROR1_INVERTER_FORK = 44,			// 포크 인버터 이상
	ERROR1_INVERTER_FORK2 = 45,			// 포크2 인버터 이상
	ERROR1_INVERTER_TRAVEL = 46,			// 주행 인버터 이상
	ERROR1_INVERTER_HOIST = 47,			// 승강 인버터 이상
	ERROR1_INVERTER_TRAVEL2 = 49,			// 주행2 인버터 이상

	ERROR1_LIFT_DECEL_DOG = 53,				// 승강 감속 이상
	ERROR1_TRAV_DECEL_DOG = 54,				// 주행 감속 이상

	ERROR1_DOUBLE_ENTRY_LEFT = 60,			// 이중입고 이상 (좌)	
	ERROR1_DOUBLE_ENTRY_RIGHT = 61,			// 이중입고 이상 (우)	
	ERROR1_CARRIER_GOODS_SENSOR_1 = 62,		// 화물 이상1
	ERROR1_CARRIER_GOODS_SENSOR_2 = 63,		// 화물 이상2
	ERROR1_EMPTY_GOODS = 64,				// 공출고/공입고
	ERROR1_LOADED_GOODS = 65,				// LOADED

	ERROR1_ORDER_ABNORMAL = 66,				// 작업 명령 이상

	// Timeout fault
	ERROR1_WORK_TIMEOUT = 80,				// 반송 동작 시간 초과
	ERROR1_FORK_TIMEOUT = 81,				// 포킹 동작 시간 초과
	ERROR1_STATION_INTERLOCK_TIMEOUT = 82,	// 스테이션 인터록 대기시간 초과
	
	ERROR1_REFERENCE_CHECK = 89,		// 원점 확인 이상

	ERROR1_MODEM_ALARM = 96,			// 광모뎀 이상
	ERROR1_DOOR_OPEN = 97,				// 기상반 도어 열림
	ERROR1_DEVICE_EMG = 98,				//기상반 비상정지 동작

	ERROR1_SEW_COM = 100,				// SEW MoviC PLC 통신 이상
	ERROR1_ETHERCAT = 101,				// 이더켓 통신 이상

	// Hardware Fault
	ERROR1_BRAKE_MMS_TRIP = 102,		// 브레이크 전원 MMS트립
	ERROR1_POWER_INIT_ERROR = 103,		// 제어전원 초기화 이상
	ERROR1_CONVERTOR = 104,					// 컨버터 이상
	//ERROR1_CP_TRIP,					// CP트립, 미적용
	//ERROR1_TRAV_MC_ERROR,				// MC 확인신호 이상 (주행, 승강), 미적용
	//ERROR1_HOIST_MC_ERROR,			// MC 확인신호 이상 (주행, 승강), 미적용
	// Hardware Fault

	ERROR1_INTERLOCK_CVOK = 105,		// 포크 동작중 인터락 이상
	ERROR1_TRAV_POSITION = 106,			// 주행 위치 이상
	ERROR1_LIFT_POSITION = 107,			// 승강 위치 이상
	ERROR1_FORK_POSITION = 108,			// 포크 위치 이상

	ERRRO1_LIDAR_FAULT = 109,
	// Data fault
	ERROR1_MCU_PARAM_DATA = 110,		// MICOM 데이터 이상
// 	ERROR1_TRAV_PARAM_DATA,				// 주행 데이터 이상
// 	ERROR1_LIFT_PARAM_DATA,				// 승강 데이터 이상
// 	ERROR1_FORK_PARAM_DATA,				// 포크 데이터 이상

	
	
	// Safety Sensor Fault
	//ERROR1_LIFT_SAFETY_DEVICE_ON,			// 승강 세이프티 디바이스 동작
	//ERROR1_LIFT_AREA_OBJECT_DETECTION,	// 승강 영역 이상 감지센서 동작

	MAX_ERROR1_CODE = 255,				// 
};

enum enumWARNING_CODE {
	WARNING_NONE = 0,
	WARNING_CODE_1,					// 주행 금지
	WARNING_CODE_2,					// 승강 금지
	WARNING_CODE_3,					// 포크 이동 금지
	WARNING_CODE_4,					// 
	WARNING_CODE_5,					// 
	WARNING_CODE_6,					// 
	WARNING_CODE_7,					// 
	WARNING_CODE_8,					// 
	WARNING_CODE_9,					// 
	WARNING_CODE_10,				// 자동모드에서 수동 조작.
	  
	WARNING_CODE_14 = 14,			// 스테이션 위치에서 구동금지 OFF상태 포크 진출  
	WARNING_CODE_15,				// 기상반 수동모드에서 상위 조작 명령 수신
	WARNING_CODE_16,				// 상위 수동 조작 중, 기상반 수동모드로 변경. 
	WARNING_CODE_17,				// HMI 수동 조작 중, 기상반 자동모드로 변경.

	WARNING_CODE_50 = 50,			// 주행 센서 위치 스캔 실패 - 주행 시작, 끝위치 설정
	WARNING_CODE_51,
	WARNING_CODE_52,

	WARNING_CODE_60 = 60,			//
	WARNING_CODE_61,
	WARNING_CODE_62,
};

enum enumFORK_OUT_IMPOSSIBLE_REASON {
	FOUT_IMPOSSIBLE_REASON_NONE = 0,
	FOUT_IMPOSSIBLE_REASON_1,			// 주행 정위치 아님
	FOUT_IMPOSSIBLE_REASON_2,			// 승강 정위치 아님
	FOUT_IMPOSSIBLE_REASON_3,			// 랙 간섭 - 승강 하위치, 화물감지상태에서 진출시, 랙에 파레트 간섭이 발생하여 진출하지 않음.
	FOUT_IMPOSSIBLE_REASON_4,			// 싱글딥 위치의 화물 감지(DSTL1 / DSTR1 신호 감지)
	FOUT_IMPOSSIBLE_REASON_5,			// 싱글딥 위치의 화물 감지(DSTLe1 / DSTRe1 신호 감지)
	FOUT_IMPOSSIBLE_REASON_6,			// 더블딥 위치의 화물 감지(DSTLR1 / DSTRR1 신호 감지)
	FOUT_IMPOSSIBLE_REASON_7,			// 싱글딥 위치의 선입품 화물감지(ODSTL1 / ODSTR1 신호 감지)
	FOUT_IMPOSSIBLE_REASON_8,			// 좌측 끝위치 도달
	FOUT_IMPOSSIBLE_REASON_9,			// 우측 끝위치 도달
	FOUT_IMPOSSIBLE_REASON_10,			// 방향 반대으로 동작
	FOUT_IMPOSSIBLE_REASON_11,			// 금지랙
	FOUT_IMPOSSIBLE_REASON_12,			// 스페셜랙, 스페셜랙 설정과 캐리지 적재 화물 타입이 다름.
	FOUT_IMPOSSIBLE_REASON_13,			// 인터락이상
};

enum enumCOMMAND_ERROR {
	COMMAND_ERROR_NONE = 0,
	COMMAND_ERROR_FALUT_STATE,
	COMMAND_ERROR_FORK_CENTER_OFF,
	COMMAND_ERROR_TRAVEL_POSITION_IS_OUT_OF_SET_RANGE,
	COMMAND_ERROR_LIFT_POSITION_IS_OUT_OF_SET_RANGE,
	COMMAND_ERROR_NON_AUTOMATIC_MODE,
	COMMAND_ERROR_NON_ONLINE,
	COMMAND_ERROR_RACK_POSITION_BLANK,
	COMMAND_ERROR_STATION_POSITION,
	COMMAND_ERROR_FORK_DEPTH_IS_OUT_OF_SET_RANGE,

	COMMAND_ERROR_NOT_WITHIN_THE_SET_RANGE = 10,
	COMMAND_ERROR_CARGO_DETECTION_STATUS,
	COMMAND_ERROR_PREVIOUS_TASK_PAUSE,
	COMMAND_ERROR_PREVIOUS_TASK_FAILURE,
	COMMAND_ERROR_EXECUTING_PREVIOUS_COMMAND,
	COMMAND_ERROR_JOB_NUMBER_ZEOR,
	COMMAND_ERROR_JOB_NUMBER_ABNORMAL,
	COMMAND_ERROR_RECEIVING_DESTINATION_CHANGE_COMMAND_IN_JOB_COMPLETION_STATUS,
	COMMAND_ERROR_MANUAL_SW_ON,
	COMMAND_ERROR_DENIED_RACK_CHG,
	COMMAND_ERROR_CMD_NO_DEFINE,
};

#endif

