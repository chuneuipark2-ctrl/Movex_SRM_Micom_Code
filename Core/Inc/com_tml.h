/**
  ******************************************************************************
  * @file           : com_tml.h
  * @brief          : Header for user_define.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COM_TML_H
#define __COM_TML_H

#include "type.h"
#include "User_Define.h"

/*******************************************************************************/
/* 통신에 관련된 INDEX 정의                                                     */
/*******************************************************************************/
#define TY_DEVICE_STATUS              0x10      // 장치 상태 요구
#define TY_DEVICE_CONTROL             0x11      // 장치 제어 명령

#define TY_TEST_STATUS					0x12      // Request Test Status
#define TY_TEST_CONTROL					0x13      // Control Test Status
#define TY_FUNC_CONTROL					0x14      // Control Function Command

#define TY_GRAPH_REQUEST				0x15

#define TY_MANUNAL_OUTPUT_CONTROL		0x16      // Manual Output Control

#define TY_DOWNLOAD_START				0x20      // 다운로드 시작
#define TY_DOWNLOAD_DATA				0x21      // 다운로드 Data
#define TY_DOWNLOAD_END					0x22      // 다운로드 완료

#define TY_DIO_FORM_REQ					0x23      // DIO 형상정보 조회
#define TY_DIO_FORM_CONTROL				0x24      // DIO 형상정보 설정

#define TY_MACHINE_SPEC_STATUS			0x25      // 기계사양 상태 요구
#define TY_MACHINE_SPEC_CONTROL			0x26      // 기계사양 설정 명령

#define TY_STATUS_REQ					0x30      // 상태요구
#define TY_OPERATION_INFO_REQ			0x31      // 운행정보 요구
#define TY_INVERTOR_INFO_REQ			0x32      // 인버터 상태 제어

#define TY_ALARMLOG_REQUEST           0x34      // 알람로그 조회
#define TY_ALARMLOG_DELETE            0x35      // 알람로그 삭제

#define TY_CMD_TASK_ORDER			0x40		//

#define TY_CMD_ORDER				0x41		//

#define TY_CMD_REFERENCE			0x44		// Invertor Reference Setup

#define TY_CMD_START				0x50		// 시작명령
#define TY_CMD_MOVE_HOME			0x51		// 홈위치 이동
#define TY_CMD_ERROR_RESET			0x52		// 이상리셋명령
#define TY_CMD_ORDER_DELETE			0x53		// 작업삭제명령
#define TY_NORMAL_STOP_REQ			0x54		// 정지, 시작 OFF
#define TY_EMERGENCY_STOP_REQ		0x55		// 비상정지
#define TY_MODE_CHANGE				0x58		// 장치 모드 변경
#define TY_CMD_MOVE_MAINTANENCE		0x59		// 보수 위치 이동

#define TY_CMD_DEMO_CONTROL			0x60		// 데모 운전 제어

#define TY_CMD_SCAN_POSITION_SENSOR	0x61		// 위치 센서 스캔

#define TY_CMD_MANUAL				0x80		// Manual Control

#define TY_INVERTOR_PARAM_REQ		0x90		// 파라미터 주소값 접근 조회
#define TY_INVERTOR_PARAM_SET		0x91		// 파라미터 주소값 접근 변경

#define TY_NOT_DEF_PROCOTOL			0x92		// 랙 설정 조회. 23. 8. 21 삭제
#define TY_NOT_DEF_PROTOCOL1		0x93		// 랙 설정 변경. 23. 8. 21 삭제

#define TY_CELL_ENV_REQ				0x94		// 셀 설정 조회
#define TY_CELL_ENV_SET				0x95		// 셀 설정 번경
#define TY_CELL_OFFSET_ENV_REQ		0x96		// 셀오프셋 설정 조회
#define TY_CELL_OFFSET_ENV_SET		0x97		// 셀오프셋 설정 변경
#define TY_STATION_ENV_REQ			0x98		// 스테이션 설정 조회
#define TY_STATION_ENV_SET			0x99		// 스테이션 설정 변경

//#define TY_ST_INTERLOCK_ENV_REQ		0x9A		// 스테이션 인터록 설정 조회
//#define TY_ST_INTERLOCK_ENV_SET		0x9B		// 스테이션 인터록 설정 변경

#define TY_PROHIBIT_RACK_ENV_REQ	0x9C		// 금지랙 설정 조회
#define TY_PROHIBIT_RACK_ENV_SET	0x9D		// 금지랙 설정 변경
#define TY_SPECIAL_RACK_ENV_REQ		0x9E		// 스페셜랙 설정 조회
#define TY_SPECIAL_RACK_ENV_SET		0x9F		// 스페셜랙 설정 변경

#define TY_SETUP_INITIALIZE_SET			0xA0		// 설정 초기화

#define TY_CONTROL_REQ				0xA1		// 제어 설정 조회
#define TY_CONTROL_SET				0xA2		// 제어 설정 변경
#define TY_TRAVEL_DRIVE_REQ			0xA3		// 주행 드라이브 설정 조회
#define TY_TRAVEL_DRIVE_SET			0xA4		// 주행 드라이브 설정 변경
#define TY_LIFT_DRIVE_REQ			0xA5		// 승강 드라이브 설정 조회
#define TY_LIFT_DRIVE_SET			0xA6		// 승강 드라이브 설정 변경
#define TY_FORK_DRIVE_REQ			0xA7		// 포크 드라이브 설정 조회
#define TY_FORK_DRIVE_SET			0xA8		// 포크 드라이브 설정 변경

#define TY_PARA_VELOCITY_REQ		0xA9		// 속도 설정 조회
#define TY_PARA_VELOCITY_SET		0xAA		// 속도 설정 변경

#define TY_MCU_TEST					0xBF		// MCU Test

#define TY_DSP_STATUS				0xC0		// Display Board 상태 조회                                    
#define TY_DSP_DATA					0xC2		// Display Board 제어

#define TY_READ_GROUP_LIST			0xD0      //                                          
#define TY_READ_PARAM_LIST			0xD1      // 

#define TY_READ_PARAM_INFO			0xD2      // 
#define TY_WRITE_PARAM_SET			0xD3      // 

struct __attribute__((__packed__)) tagTMLCom
{
	ComHeaderSTR  Header;
	INT08U        Data[FRAME_MAX_DATA_LEN];       /* Frame Data  */
};
typedef struct tagTMLCom  TMLComSTR;
typedef struct tagTMLCom* TMLComPTR;

extern void rsComHandler(INT08U rsData);
extern void rsComHandlerDMA();

extern void txPutHeader(INT08U port, ComHeaderSTR* pRxHeader, INT08U Cmd, INT08U Cmd2, INT16U Len);
extern void txPutHeader_1(INT08U port, ComHeaderSTR* pRxHeader, INT16U Len);

extern void sendTxBuf(INT08U port);
extern void clearTxBuf(INT08U port);

extern void sendUdpTxBuf_Downlink();
extern void Send_Read_Invertor_Parameter();
//extern void Send_Write_Invertor_Parameter();
extern void Send_Write_Invertor_Parameter(INT08U nAck);
extern void rxDataAnalysis(INT08U port, TMLComPTR pCom);

extern void TMLComManager(void);

#endif /* __COM_TML_H */

