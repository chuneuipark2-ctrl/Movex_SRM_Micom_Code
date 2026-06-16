/**
  ******************************************************************************
  * @file           : user_define.h
  * @brief          : Header for user_define.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

  /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MX_DEFINE_H
#define __MX_DEFINE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

#include "type.h"
#include "error_code.h"

#define FW_VERSION			(0x44)		// Ver4.0

#define ENABLE_WATCHDOG		(0)

// 1 : St-Link Debug 사용. FW CRC코드 확인하지 않음. 
#define FW_DEBUG			(0)		

//#define EVENT_LOG_TYPE		0

#define DEF_ALARM_LOG_TYPE					(2)		// Alarm Type2

#define TRAV_ORIGIN_ENABLE_FLAG				(0)		// 주행 자동 원점 설정

#define LIFT_ORIGIN_ENABLE_FLAG				(0)		// 승강 자동 원점 설정

#define ENABLE_TRAV_LEFT_MOVE_BRAKE_RELEASE	(0)		// 이동전 브레이크 해제 동작

#define HMI_MEMORY_MAP_VERSION				(1)

// 1: 랙, 스테이션 설정완료 후, Bay/Level/Station 번호 m_TestStatus.Ctrl 확인
#define DEBUG_BAY_LV_ST_POSITON				(1)

#define DEBUG_INV_ERROR						(1)		

#define DEBUG_INV_DATA						(1)		

#define DEBUG_CMD							(0)		

#define DEBUG_TRAVEL_MAN_CTR				(0)		

#define DEBUG_HOIST_MAN_CTR					(0)

#define DEBUG_FORK_MAN_CTR					(1)

#define DEBUG_AUTO_FORK_CREEP				(0)		

#define DEBUG_START_ON						(0)	

#define DEBUG_INPOS_STOP					(0)

#define DEBUG_HOIST_INPOS_STOP				(0)

#define DEBUG_CELL_OFFSET_1					(0)

#define DEBUG_GT_DEMO						(0)

#define DEBUG_WORK_INFO						(0)

#define DEBUG_WORK_DATA						(0)		

#define DEBUG_HMI_COM_STATUS				(0)

#define DEBUG_HMI_TIME						(0)

#define DEBUG_HMI_DEBUG						(0)		

#define DEBUG_MANUAL_OUTPUT					(0)

#define TEST_DESK_MODE_FLAG					(0)		// 사무실에서 테스트시 

#if TEST_DESK_MODE_FLAG
// 테스트 모드

#define TEST_INTERLOCK		(0)

// 입고, 출고, 랙간반송, 스테이션 반송명령 수신시, 화물감지 이상 확인하지 않음.
#define DISABLE_ERROR_CARRIER_GOODS_SENSOR	(0)		

#define DISABLE_MANUAL_CTR_TRAVEL	(0)				// 주행수동모드 허용금지

#define DISABLE_ECAT_PROC	(0)						// 이더켓 통신 사용여부

#define DISABLE_HMI_PROC	(0)						// HMI 통신 사용여부

#define DEBUG_HMI_TEST_MODE	(0)

#define TEST_FORK_ALARM_IGNORE_FLAG		(0)

#define DEBUG_INVERTER_SIMULATION		(1)			// 현재 위치값 시뮬레이션

#define DISABLE_CHECK_FORK_STATE		(1)			// 수동 주행, 승강시 포크상태확인 안함.

//#define DEBUG_CARGO_DETECTION_STATUS	(1)

#define DEBUG_MSG_ENABLE	(1)

#if DEBUG_MSG_ENABLE
#define DEBUG_MSG					1		//
#define DEBUG_FLASH_MSG				0		//  
#define DEBUG_TML_MSG				0		//
#define DEBUG_MCU_DEBUG_MSG			0		//
#define DEBUG_UPLINK_MSG			0		//
#define DEBUG_DSP_UDP_MSG			0		//
#define DEBUG_UPGRADE_MSG			0		//  
#define DEBUG_CAN_MSG				0		//  
#define DEBUG_HMI_MSG				0		//  
#define DEBUG_ENCODER_MSG			0		//
#define DEBUG_FPGA_MSG				0		//
#define DEBUG_ETHERCAT_MSG			0		//
#define DEBUG_EXT_SFLASH_MSG		0		//
#define DEBUG_FILE_MEM_MSG			0		//
#define DEBUG_RTC					0		//
#define DEBUG_MODBUSTCP				0		//
#define DEBUG_MODBUS_HMI			1		//
#define DEBUG_MODBUS_SEW			0		//
#define DEBUG_ETHERCAT_EC_MODULE	0		//
#define DEBUG_CELL_CONFIG			0		//
#define DEBUG_CELL_OFFSET			0		//
#define DEBUG_BACKUPSRAM			0		//
#define DEBUG_DSP					0		//
#define DEBUG_HT100					0		//
#define DEBUG_TCP_MSG				1		//
#endif

#else
// 현장 동작 모드

#endif


// Initialization Code
// 초기화코드 변경 시, App,Boot 소스 초기화 코드도 변경해야 함.
#define DEVICE_INIT_CODE				("Devi")
#define MACHINE_TYPE_INIT_CODE			("MecH")
#define DIO_INIT_CODE					("Dios")
// 초기화코드 변경 시, App,Boot 소스 초기화 코드도 변경해야 함.

#define RACK_INIT_CODE					("RacK")
#define CELL_INIT_CODE					("Cell")
#define CELL_OFFSET_INIT_CODE			("offs")
#define STATION_INIT_CODE				("Stat")
#define PROHIBIT_RACK_INIT_CODE			("Proh")
#define SPECIAL_RACK_INIT_CODE			("Spec")

#define CONTROL_PARAM_INIT_CODE			("Cont")
#define TRAVEL_DRIVE_PARAM_INIT_CODE	("Trav")
#define LIFT_DRIVE_PARAM_INIT_CODE		("Lift")
#define FORK_DRIVE_PARAM_INIT_CODE		("Fork")

#define BK_OPERATION_INFO_INIT_CODE		("Oper")
#define BK_WORK_INFO_INIT_CODE			("Work")

#define POSITION_INIT_CODE				("PoSI")

// 프로젝트 코드
#define MOVEX_RND							("A00002")		// 현대무벡스 청라 쇼품
#define HANKOOK_TIRE_TP2					("E13398")		// 2025.07.07 HankookTire TP2

#define YUHAN_CORPORATION_OSONG_PLANT		("F10328")		// 2026.04.22 유한양행 오송공장 
#define NATURE_AND_PEOPLE_CORPORATION		("F10339")		// 2026.04.30 자연과 사람들

enum enumHANKOOK_TIRE_TP2_LINE {
	HANKOOK_TIRE_TP2_PCR_INNER_LINE = 1,	// 1, PCR - INNER LINE (I/L)
	HANKOOK_TIRE_TP2_PCR_TREAD,				// 2, PCR - Tread(T/D) 자동창고 (압출)
	HANKOOK_TIRE_TP2_PCR_SIDE_WALL,			// 3, PCR - Side Wall(S/W) 자동창고(압출)
	HANKOOK_TIRE_TP2_PCR_CARCASS,			// 4, PCR - Carcass(C/C) 자동창고 (재단)
	HANKOOK_TIRE_TP2_PCR_BW,				// 5, PCR - PCR 반제품 (B/W)
	HANKOOK_TIRE_TP2_PCR_JLB,				// 6, PCR - PCR 반제품 (JLB)
	HANKOOK_TIRE_TP2_PCR_BELT,				// 7, PCR - Belt(B/T) 자동창고 (재단)
	HANKOOK_TIRE_TP2_PCR_BEAD,				// 8, PCR - 완성Bead(B/D, B/F)자동창고 (재단)
	HANKOOK_TIRE_TP2_TBR_TREAD,				// 9, TBR - Tread(T/D) 자동창고 (압출)
	HANKOOK_TIRE_TP2_TBR_STRIP,				// 10, TBR - TBR 반제품 (재단, Strip)
	HANKOOK_TIRE_TP2_TBR_CARCASS,			// 11, TBR - Carcass(C/C) 자동창고 (재단)
	HANKOOK_TIRE_TP2_TBR_BELT,				// 12, TBR - Belt(B/T) 자동창고 (재단)
	HANKOOK_TIRE_TP2_TBR_BEAD,				// 13, TBR - 완성Bead(B/D or B/F)자동창고 (재단)
	HANKOOK_TIRE_TP2_TBR_MOLD,				// 14, TBR - TBR MOLD 창고
	HANKOOK_TIRE_TP2_PCR_STEEL_ROLL,		// 15, PCR - 압연 Steel Roll

	HANKOOK_TIRE_TP2_PCR_GT_LOT4,			// 16, PCR - GT LOT4
	HANKOOK_TIRE_TP2_PCR_GT_LOT3,			// 17, PCR - GT LOT3
	HANKOOK_TIRE_TP2_PCR_MOLD,				// 18, PCR - MOLD
	HANKOOK_TIRE_TP2_PCR_GT_LOT2,			// 19, PCR - GT LOT2
	HANKOOK_TIRE_TP2_PCR_GT_LOT1,			// 20, PCR - GT LOT1
	HANKOOK_TIRE_TP2_TBR_SIDEWALL,			// 21, TBR - TBR SIDEWALL
	HANKOOK_TIRE_TP2_TBR_INNER,				// 22, TBR - TBR INNER

	HANKOOK_TIRE_TP2_PCR_TEXTILE_ROLL = 50, // 50, PCR - PCR - 압연 TEXTILE Roll
};


#define SYNC0TIME (2000000)		// sample interval in ns, here 2ms
#define ETHERCAT_UPDATE_TIME (((SYNC0TIME) / 1000) - 1)

#define DEF_DSP_REMOTE_PORT		(8000)

//typedef enum _BOOL { FALSE = 0, TRUE } BOOL;	// Undefined size
#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

#define NOP	asm volatile("nop\n")

typedef enum reset_cause_e
{
	RESET_CAUSE_UNKNOWN = 0,
	RESET_CAUSE_LOW_POWER_RESET,
	RESET_CAUSE_WINDOW_WATCHDOG_RESET,
	RESET_CAUSE_INDEPENDENT_WATCHDOG_RESET,
	RESET_CAUSE_SOFTWARE_RESET,
	RESET_CAUSE_POWER_ON_POWER_DOWN_RESET,
	RESET_CAUSE_EXTERNAL_RESET_PIN_RESET,
	RESET_CAUSE_BROWNOUT_RESET,
} reset_cause_t;

enum enumDEBUG_STR {
	DEBUG_STR_1 = 0,	// 
	DEBUG_STR_2,		// 
	DEBUG_STR_3,		// 
	DEBUG_STR_4,		// 
	DEBUG_STR_5,		// 
	DEBUG_STR_6,		// 
	DEBUG_STR_7,		// 
	DEBUG_STR_8,		// 
	DEBUG_STR_9,		// 
	DEBUG_STR_10,		// 
	DEBUG_STR_11,		// 
	DEBUG_STR_12,		// 
	DEBUG_STR_13,		// 
	DEBUG_STR_14,		// 
	DEBUG_STR_15,		// 
	DEBUG_STR_16,		// 
	DEBUG_STR_17,		// 
	DEBUG_STR_18,		// 
	DEBUG_STR_19,		// 
	DEBUG_STR_20,		// 
	DEBUG_STR_21,		// 
	DEBUG_STR_22,		// 
	DEBUG_STR_23,		// 
	DEBUG_STR_24,		// 
	DEBUG_STR_25,		// 
	DEBUG_STR_26,		// 
	DEBUG_STR_27,		//
	DEBUG_STR_28,		// 
	DEBUG_STR_29,		// 
	DEBUG_STR_30,		//
	DEBUG_STR_31,		//
	DEBUG_STR_32,		// 
	DEBUG_STR_33,		// 
	DEBUG_STR_34,		// 
	DEBUG_STR_35,		// 
	DEBUG_STR_36,		// 
	DEBUG_STR_37,		// 
	DEBUG_STR_38,		// 
	DEBUG_STR_39,		// 
	DEBUG_STR_40,		// 
	DEBUG_STR_41,		// 
	DEBUG_STR_42,		// 
	DEBUG_STR_43,		// 
	DEBUG_STR_44,		// 
	DEBUG_STR_45,		// 
	DEBUG_STR_46,		// 
	DEBUG_STR_47,		// 
	DEBUG_STR_48,		// 
	DEBUG_STR_49,		// 
	DEBUG_STR_50,		// 
	DEBUG_STR_51,		// 
	DEBUG_STR_52,		// 
	DEBUG_STR_53,		// 
	DEBUG_STR_54,		// 
	DEBUG_STR_55,		// 
	DEBUG_STR_56,		// 
	DEBUG_STR_57,		// 
	DEBUG_STR_58,		// 
	DEBUG_STR_59,		// 
	DEBUG_STR_60,		// 
	DEBUG_STR_61,		// 
	DEBUG_STR_62,		//
	DEBUG_STR_63,		// 
	DEBUG_STR_64,		//
	MAX_DEBUG_STR,
};

enum enumDEBUG_BUF {
	DEBUG_CTR_1 = 0,	// Test 1
	DEBUG_CTR_2,		// Test 2
	DEBUG_CTR_3,		// Test 3
	DEBUG_CTR_4,		// Test 4,
	DEBUG_CTR_5,		// Test 5,
	DEBUG_CTR_6,		// Test 6,
	DEBUG_CTR_7,		// Test 7,
	DEBUG_CTR_8,		// Test 8,
	DEBUG_CTR_9,		// Test 9,
	DEBUG_CTR_10,		// Test 10,
	DEBUG_CTR_11,		// Test 11,
	DEBUG_CTR_12,		// Test 12,
	DEBUG_CTR_13,		// Test 13,
	DEBUG_CTR_14,		// Test 14,
	DEBUG_CTR_15,		// Test 15,
	DEBUG_CTR_16,		// Test 16,
};

enum enumGRAPH_INDEX {
	GRAPH_1 = 0,		// Top View
	GRAPH_2,			// Top View
	GRAPH_3,
	GRAPH_4,
	GRAPH_5,
	GRAPH_6,
	GRAPH_7,
	GRAPH_8,
	GRAPH_9,			
	GRAPH_10,
	GRAPH_11,			// Top View
	GRAPH_12,			// Top View
	MAX_GRAPH_COUNT
};

struct __attribute__((__packed__)) tagWORD
{
	union
	{
		INT16S	W;
		INT08S	B[2];
	};
};
typedef struct tagWORD  WORD_User;

struct __attribute__((__packed__)) tagDWORD
{
	union
	{
		INT32S	Dw;
		INT16S	W[2];
		INT08S	B[4];
	};
};
typedef struct tagDWORD  DWORD_User;

//#define FW_BLOCK_SIZE		 512		// 수신 FW Data Size
#define FW_BLOCK_SIZE		 1024		// 수신 FW Data Size

#define ADDR_FSMC_FPGA                 ((INT32U)0x60000000)   // FSMC_NE1
#define ADDR_FSMC_NE2                  ((INT32U)0x64000000)   // FSMC_NE2
#define ADDR_FSMC_IOCS                 ((INT32U)0x68000000)   // FSMC_NE3
#define ADDR_FSMC_NE4                 ((INT32U)0x6C000000)   // FSMC_NE4

#define ADDR_FSMC_IOCS_DI              ((INT32U)0x68000000)   // FSMC_NE3
#define ADDR_FSMC_IOCS_DO              ((INT32U)0x68000001)   // FSMC_NE3
#define ADDR_FSMC_IOCS_MODE            ((INT32U)0x68000002)   // FSMC_NE3
#define ADDR_FSMC_IOCS_FND             ((INT32U)0x68000003)   // FSMC_NE3
#define ADDR_FSMC_IOCS_ID_SW           ((INT32U)0x68000004)   // FSMC_NE3
#define ADDR_FSMC_IOCS_RS422_485       ((INT32U)0x68000005)   // FSMC_NE3
#define ADDR_FSMC_IOCS_NULL            ((INT32U)0x68000007)   // FSMC_NE3

#define ADDR_FSMC_FPGA_REG             ((INT32U)0x60000000)   // 
#define ADDR_FSMC_ETHERNET_RX_MEM      ((INT32U)0x60001000)   // 
#define ADDR_FSMC_ETHERNET_TX_MEM      ((INT32U)0x60001800)   // 
#define ADDR_FSMC_ETHERCAT_RX_MEM      ((INT32U)0x60002000)   // 
#define ADDR_FSMC_ETHERCAT_TX_MEM      ((INT32U)0x60002800)   // 

/*******************************************************************************/
/* Frame Sync 占쏙옙占쏙옙                                                             */
/*******************************************************************************/
#define FRAME_STX                     0x16
#define FRAME_ETX                     0xF5

/*******************************************************************************/
/* Frame 占쏙옙占쏙옙 Feild占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙                                               */
/*******************************************************************************/
#define FRAME_SYNC_SIZE                  4
//#define FRAME_HEADER_SIZE               10
#define FRAME_HEADER_SIZE               11
#define FRAME_CRC_SIZE                   2
#define FRAME_MAX_DATA_LEN            2048
#define FRAME_DSP_DATA_LEN            128
//#define FRAME_MAX_DATA_LEN            5
//#define FRAME_ETH_MAX_DATA_LEN        2048
//#define FRAME_MAX_DATA_LEN            1560
#define FRAME_ETH_MAX_DATA_LEN        1560

#define FRAME_HHT_HEADER_SIZE           6

#define MAX_UART_PORT                   6

#define UART_1                          0
#define UART_2                          1
#define UART_3                          2
#define UART_4                          3
#define UART_5                          4
#define UART_6                          5

/*******************************************************************************/
/* 占쏙옙占� 占쏙옙트 占쏙옙호占쏙옙占쏙옙                                                           */
/*******************************************************************************/
#define rsTMLPort                       UART_3
#define rsMCU_DEBUG_Port                UART_4
#define rsOPTPort                       UART_5		// RS422
#define rsRS485_422_Port                UART_6		// RS485
#define rsEXTPort                       UART_1
#define rsUSBPort                       11
#define rsETHUDPPort_Uplink             12			// Uplink
#define rsETHTCPPort                    13
#define rsETHUDPPort_DwLink             14			// Downlink
#define rsINVTCPPort                    15
#define rsDSP_UDP_Port                  16
#define rsHMI_Port						17
#define rsHMI_UP_Port					18
#define rsDSP_RS485_Port                UART_6

/*******************************************************************************/
/* 占쏙옙占� Frame 占쏙옙占쏙옙체                                                            */
/*******************************************************************************/

// CIM_ID Type
#define COM_ID_GCP   0x00		// 지상반
#define COM_ID_WCS          0x01
#define COM_ID_GUI          0x02
#define COM_ID_HMI          0x03
#define COM_ID_SHUTTLE      0x10
#define COM_ID_LIFTER_OUT   0x20
#define COM_ID_LIFTER_IN    0x21
#define COM_ID_MINILODER    0x30
#define COM_ID_RTV          0x40
#define COM_ID_EMS          0x50
#define COM_ID_SRM          0x60
#define COM_ID_WIFI_CTRL    0x80
#define COM_ID_WIFI_AP      0x90
#define COM_ID_WIFI_STA     0xA0

#define COM_ID_DSP			0xE4

#define COM_ID_HT100        0xE6

struct __attribute__((__packed__)) tagComID
{
	INT08U  Type;
	INT08U  Index;
};
typedef struct tagComID  ComIDSTR;

struct __attribute__((__packed__)) tagComHeader
{
	ComIDSTR  SrcID;                       /* Sub ID             */
	ComIDSTR  DstID;                       /* Sub ID             */
	INT08U    Seq;                         /* Sequence Number    */
	INT08U    Bypass[2];
	INT08U    Cmd;                         /* Frame Command1         */
	INT16U    Len;                         /* Frame Length       */
	INT08U    Cmd2;                         /* Frame Command2 */
};
typedef struct tagComHeader  ComHeaderSTR;

struct __attribute__((__packed__)) tagHHTCom
{
	INT08U  SrcID;                         /* Sub ID             */
	INT08U  DstID;                         /* Sub ID             */
	INT08U  Seq;                           /* Sequence Number    */
	INT08U  Cmd;                           /* Frame Type         */
	INT16U  Len;                           /* Frame Length       */
	INT08U  Data[FRAME_MAX_DATA_LEN];      /* Frame占쏙옙 占쏙옙占쏙옙 Data  */
};
typedef struct tagHHTCom  HHTComSTR;
typedef struct tagHHTCom* HHTComPTR;

//////////////////////////////////////////////////////////////////////////////

#define MAX_CELL_OFFSET_COUNT (32768)	

#define MAX_ALARM_LOG_COUNT  50

#define MAX_TASK_COUNT 20

struct __attribute__((__packed__)) tagLogForkWorkSTR
{
	INT08U         OrderCode;          // 
	INT08U         OrderProcess;       //
};
typedef struct tagLogForkWorkSTR  LogForkWorkSTR;

struct __attribute__((__packed__)) tagNetworkInfo
{
	INT08U         MyIP[4];
	INT08U         SubnetMask[4];
	INT08U         GatewayIP[4];
};
typedef struct tagNetworkInfo  NetworkInfo_t;

struct __attribute__((__packed__)) tagProjectID
{
	INT08U		ProjectNo[6];
	INT08U		Group_ID;
	INT16U		Device_ID;
};
typedef struct tagProjectID  ProjectID_t;

struct __attribute__((__packed__)) tagDeviceLink
{
	INT08U EtherNet_LAN0 : 1;	// Bit 0
	INT08U EtherNet_LAN1 : 1;	// Bit 1
	INT08U reserved : 1;		// Bit 2
	INT08U DBG_TTL232 : 1;		// Bit 3
	INT08U TML_RS232 : 1;		// Bit 4
	INT08U HMI_RS485 : 1;		// Bit 5
	INT08U CAN : 1;				// Bit 6
	INT08U SSI : 1;				// Bit 7
	INT16U EtherCAT_Slave;		// 
	INT08U Extra_Slave;			// Bit0: MX_DSP_1, Bit1: MX_DSP_2, Bit2: HMI
};
typedef struct tagDeviceLink  DeviceLINK;

struct __attribute__((__packed__)) tagDevStatus
{
	INT08U				Reserved1;
	INT08U				ProtocolVer;
	INT08U				PgmVer[4];
	INT32U				SysTime;   // UTC Time

	NetworkInfo_t		NetworkInfo_0;
	INT08U				MyMACAddr_0[6];

	NetworkInfo_t		NetworkInfo_1;
	INT08U				MyMACAddr_1[6];

	INT08U				BootPgmVer[4];
	INT08U				Reserved2[32];
// 	NetworkInfo_t		NetworkInfo_2;
// 	INT08U				MyMACAddr_2[6];
// 
// 	INT08U				Reserved2[18];

	ProjectID_t			ProjectID;

	INT08U				Reserved3[10];

	INT08U				Mode_SW;
	INT08U				ID_SW;

	DeviceLINK			mLinkStatus;

	INT08U				Reserved4[29];
};
typedef struct tagDevStatus  DevStatusSTR;

//////////////////////////////////////////////////////////////////////////////////

struct __attribute__((__packed__)) tagControl
{
	INT32U            SysTime;   // UTC Time

	/* LAN1, MCU LWIP */
	NetworkInfo_t		NetworkInfo_0;
	INT08U				MyMACAddr_0[6];

	/* LAN2, FPGA1 */
	NetworkInfo_t		NetworkInfo_1;
	INT08U				MyMACAddr_1[6];

	/* LAN3, FPGA2 */
	NetworkInfo_t		NetworkInfo_2;
	INT08U				MyMACAddr_2[6];

	ProjectID_t			ProjectID;

	INT08U				Reserved2[30];
};
typedef struct tagControl  DevControlSTR;

//////////////////////////////////////////////////////////////////////////////////

struct __attribute__((__packed__)) tagUnitVelocitySTR
{
	INT16U  Spd;
	INT16U  Acc;
	INT16U  Dec;
	INT16U  Jerk;
};
typedef struct tagUnitVelocitySTR  UnitVelocitySTR;

//////////////////////////////////////////////////////////////////////////////////

struct __attribute__((__packed__)) tagCellPos
{
	INT08U	Station;	//
	INT08U	Row_ID;		//
	INT16U	Bay_ID;		//
	INT08U	Level_ID;	//
};
typedef struct tagCellPos  CellPosSTR;

//struct __attribute__((__packed__)) tagGroupCtrStatus
struct tagControlPanelStatusBit
{
	INT08U SafetyPlugOn : 1;	// Bit0, 0: On, 1: Off
	INT08U EmergencyStop : 1;	// Bit1, 0: Switch Off, 1: Switch On
	INT08U FaultReset : 1;		// Bit2, 0: Switch Off, 1: Switch On
	INT08U HeartBit : 1;		// Bit3, HeartBit
	INT08U HostCom : 1;			// Bit4, 
	INT08U Reserved2 : 1;		// Bit5,
	INT08U Reserved3 : 1;		// Bit6,
	INT08U Reserved4 : 1;		// Bit7,
};
typedef struct tagControlPanelStatusBit  ControlPanelSTR_Bit;

struct __attribute__((__packed__)) tagGroupCtrStatus
{
	union
	{
		ControlPanelSTR_Bit Bit;
		INT08U				Data;
	};
};
typedef struct tagGroupCtrStatus  ControlPanelSTR;

//struct __attribute__((__packed__)) tagDeviceMode
struct tagDeviceModeBit
{
	INT08U Auto : 1;		// Bit0,
	INT08U Manual : 1;		// Bit1,
	INT08U Force : 1;		// Bit2,
	INT08U Setup : 1;		// Bit3,
	INT08U Reserved0 : 1;		// Bit4, 
	INT08U Reserved1 : 1;		// Bit5, 
	INT08U Reserved2 : 1;		// Bit6,
	INT08U Reserved3 : 1;		// Bit7,
};
typedef struct tagDeviceModeBit  DeviceModeBit_t;

struct __attribute__((__packed__)) tagDeviceMode
{
	union
	{
		DeviceModeBit_t Bit;
		INT08U			D;
	};
};
typedef struct tagDeviceMode  DeviceMode_t;

struct tagDeviceStatus1Bit
{
	INT08U StartOn : 1;			// Bit0,
	INT08U EmergencyStop : 1;	// Bit1,
	INT08U Warning : 1;			// Bit2, 
	INT08U Fault : 1;			// Bit3,
	INT08U InvertorConnect : 1;	// Bit4,
	INT08U RequestWork : 1;		// Bit5,	작업요구
	INT08U Reserved1 : 1;		// Bit6,
	INT08U Reserved2 : 1;		// Bit7,
};
typedef struct tagDeviceStatus1Bit  DeviceStatus1Bit_t;

struct __attribute__((__packed__)) tagDeviceStatus1
{
	union
	{
		DeviceStatus1Bit_t Bit;
		INT08U			D;
	};
};
typedef struct tagDeviceStatus1  DeviceStatus1;

struct tagDeviceStatus2_Bit
{
	INT08U HomePos : 1;	// Bit0, 
	INT08U MaintanencePos : 1;	// Bit1, 
	INT08U Reserved2 : 1;	// Bit2,
	INT08U Reserved3 : 1;	// Bit3,
	INT08U Reserved4 : 1;	// Bit4,
	INT08U Reserved5 : 1;	// Bit5,
	INT08U ManualSW : 1;		// Bit6,
	INT08U EmergencySW : 1;	// Bit7,
};
typedef struct tagDeviceStatus2_Bit  DeviceStatus2Bit_t;

struct __attribute__((__packed__)) tagDeviceStatus2
{
	union
	{
		DeviceStatus2Bit_t Bit;
		INT08U			D;
	};
};
typedef struct tagDeviceStatus2  DeviceStatus2;

struct tagPositionFlag1_Bit
{
	INT08U Trav_Left : 1;		// Bit0,
	INT08U LiftUp_Left : 1;		// Bit1,
	INT08U LiftDown_Left : 1;	// Bit2,
	INT08U Trav_Right : 1;		// Bit3,
	INT08U LiftUp_Right : 1;	// Bit4,
	INT08U LiftDown_Right : 1;	// Bit5,
	//INT08U St_LiftUp : 1;		// Bit6, 
	//INT08U St_LiftDown : 1;		// Bit7, 
};
typedef struct tagPositionFlag1_Bit  PositionFlag1_Bit;

struct __attribute__((__packed__)) tagPositionFlag1
{
	union
	{
		PositionFlag1_Bit Bit;
		INT08U			Data;
	};
};
typedef struct tagPositionFlag1  PositionFlag1;

struct tagPositionFlag2_Bit
{
	INT08U ForkCenter : 1;	// Bit0,
	INT08U ForkLeft1 : 1;	// Bit1,
	INT08U ForkLeft2 : 1;	// Bit2,
	INT08U ForkLeft3 : 1;	// Bit3,
	INT08U ForkRight1 : 1;	// Bit4,
	INT08U ForkRight2 : 1;	// Bit5,
	INT08U ForkRight3 : 1;	// Bit6, 
	INT08U Reserved0 : 1;	// Bit7, 
};
typedef struct tagPositionFlag2_Bit  PositionFlag2_Bit;

struct __attribute__((__packed__)) tagPositionFlag2
{
	union
	{
		PositionFlag2_Bit Bit;
		INT08U			Data;
	};
};
typedef struct tagPositionFlag2  PositionFlag2;

struct __attribute__((__packed__)) tagForkPosInfo
{
	INT08U	St_No;
	INT16U	Bay_No;
	INT08U	Level_No;
	INT08S	Fork_PosNo;				// 0: Center, 1: Left, 2: Right
	PositionFlag1	Position1;
	PositionFlag2	Position2;
	INT16U	Row_ID;
	//INT08U	Reserved[2];
};
typedef struct tagForkPosInfo  ForkPosInfo;

struct tagDriveStatus1
{
	INT08U MoveFlag : 1;				// Bit0, 0: Stop
	INT08U AccelState : 1;				// Bit2, 0: Stop
	INT08U DecelState : 1;				// Bit1, 0: Stop
	INT08U MoveDirection : 1;			// Bit3, 0: Forward
	INT08U InPosition : 1;				// Bit4, 1: Complete
	INT08U GoodsFlag_Or_MoveHome : 1;				// Bit5, 주행, 승강 홈복귀
	INT08U ForkOut_Left_OK : 1;			// Bit6,
	INT08U ForkOut_Right_OK : 1;		// Bit7,
	/*
	INT08U IPOS_ref : 1;				// Bit5, 1: Complete
	INT08U ForwardDecelationArea : 1;	// Bit6,
	INT08U ReverseDecelationArea : 1;	// Bit7,
	*/
};
typedef struct tagDriveStatus1  DriveStatus1;

struct tagDriveStatus2
{
	INT08U Connect : 1;			// Bit0,
	INT08U Alarm : 1;			// Bit1,
	INT08U IPOS_ref : 1;		// Bit2, 1: Complete
	INT08U Tuning_Noload : 1;	// Bit3, 
	INT08U Tuning_load : 1;		// Bit4,
	INT08U Reserved0 : 1;		// Bit5,
	INT08U IO_Control : 1;		// Bit5,
	INT08U Com_Control : 1;		// Bit6,
};
typedef struct tagDriveStatus2  DriveStatus2;

typedef union
{
	INT08U Loaded_GoodType;
	INT08U Forward_Decel_No;
} MULTI_FUNC_VAL_1;

struct __attribute__((__packed__)) tagDriveStatus
{
	DriveStatus1	Status1;
	DriveStatus2	Status2;
	MULTI_FUNC_VAL_1	U;
	INT08U	Reverse_Decel_No_Or_Gox;
	INT32S	Current_Pos;
	INT16S	Current_Vel;
	INT32S	Target_Pos;
	INT16S	Target_Vel;
};
typedef struct tagDriveStatus  DriveStatus;

struct __attribute__((__packed__)) tagWorkInfo
{
	INT32U			WorkNum_Fork;
	INT08U			Task_Index;			// 0 : It's not task work
	CellPosSTR		From_Cell_Fork;
	CellPosSTR		To_Cell_Fork;
	INT08U			OrderCode_Fork;
	INT08U			OrderStatus_Fork;
	INT08U			OrderProcess_Fork;
	INT32U			WorkNum_Move;
	CellPosSTR		To_Cell_Move;
	INT08U			OrderStatus_Move;
	INT08U			OrderProcess_Move;
};
typedef struct tagWorkInfo  WorkInfoSTR;

struct __attribute__((__packed__)) tagTaskCommand
{
	INT08U			Cmd;
	INT08U			LoadFactor;
	INT08U			WorkForkNo;
	CellPosSTR		TargetPos;
	INT08U			GoodsType;
	INT08U			OrderState;
	INT08U			Reserved;
};
typedef struct tagTaskCommand  TaskCommand;

struct __attribute__((__packed__)) tagInvertorIO
{
	INT08U			Input;
	INT08U			Output;
};
typedef struct tagInvertorIO  InvertorIO;

enum enumCP_MODE {
	CP_MODE_MANUAL = 0,
	CP_MODE_SEMI_AUTO,
	CP_MODE_AUTO,
};

struct __attribute__((__packed__)) tagDIO_Status
{
	INT08U	In[20];
	INT08U	Output[9];
};
typedef struct tagDIO_Status  DIO_Status;

struct __attribute__((__packed__)) tagInvErrCode
{
	INT08U	MainError;
	INT08U	SubError;
};
typedef struct tagInvErrCode  InvErrCode;

struct __attribute__((__packed__)) tagInvErrCode_Str
{
	InvErrCode  Inverter[4];
};
typedef struct tagInvErrCode_Str  InvErrCode_Str;

// Date : 2025. 08. 06
// WCS 예지보전 용 부가 정보
struct __attribute__((__packed__)) tagMaintanance_Info
{
	INT32S travel_setting_speed;
	INT32S lift_setting_speed;
	INT32S fork1_setting_speed;
	INT32S fork2_setting_speed;
	INT32S travel_setting_acceleration;
	INT32S lift_setting_acceleration;
	INT32S fork1_setting_acceleration;
	INT32S fork2_setting_acceleration;
	INT32S travel_setting_deceleration;
	INT32S lift_setting_deceleration;
	INT32S fork1_setting_deceleration;
	INT32S fork2_setting_deceleration;
	INT32S travel_setting_jeck;
	INT32S lift_setting_jerk;
	INT32S fork1_setting_jerk;
	INT32S fork2_setting_jerk;
	INT16U load_travel_lift_moving_before_delay;
	INT16U load_travel_lift_moving_after_delay;
	INT16U load_fork_extend_moving_before_delay;
	INT16U load_fork_extend_moving_after_delay;
	INT16U load_forking_lift_moving_before_delay;
	INT16U load_forking_lift_moving_after_delay;
	INT16U load_fork_fold_moving_before_delay;
	INT16U load_fork_fold_moving_after_delay;
	INT16U unload_travel_lift_moving_before_delay;
	INT16U unload_travel_lift_moving_after_delay;
	INT16U unload_fork_extend_moving_before_delay;
	INT16U unload_fork_extend_moving_after_delay;
	INT16U unload_forking_lift_moving_before_delay;
	INT16U unload_forking_lift_moving_after_delay;
	INT16U unload_fork_fold_moving_before_delay;
	INT16U unload_fork_fold_moving_after_delay;
	INT32S travel_motor_torque;
	INT32S lift_motor_torque;
	INT32S fork1_moter_torque;
	INT32S fork2_moter_torque;
	INT32S plc_operation_time;
	INT32S travel_operation_time;
	INT32S lift_operation_time;
	INT32S fork1_operation_time;
	INT32S fork2_operation_time;
	INT32S travel_brake_open_count;
	INT32S lift_brake_open_count;
	INT32S fork1_brake_open_count;
	INT32S fork2_brake_open_count;
};
typedef struct tagMaintanance_Info  Maintanance_Info;

struct tagLidarStatus
{
	INT08U Detect1 : 1;			// Bit0,
	INT08U Detect2 : 1;			// Bit1,
	INT08U Detect3 : 1;			// Bit2,
	INT08U Fault : 1;			// Bit3, 
	INT08U Select_Zone : 4;		// Bit4 - 7,
};
typedef struct tagLidarStatus  LidarStatus;

struct __attribute__((__packed__)) tagLidar_Str
{
	LidarStatus  Fork1_L;
	LidarStatus  Fork1_R;
	LidarStatus  Fork2_L;
	LidarStatus  Fork2_R;
};
typedef struct tagLidar_Str  Lidar_Str;

struct __attribute__((__packed__)) tagStatus
{
	//INT08U				Reserved0[2];
	INT08U				DeviceType;
	INT08U				Reserved0;
	INT08U				ProtocolVer;
	INT08U				PgmVer[4];
	INT32U				SysTime;				// UTC Time
	ProjectID_t			ProjectID;
	INT16U				MachineType;
	INT08U				CP_Mode;
	ControlPanelSTR		CP_State;
	INT08U				InterLock_CVOK[8];		// 포크 구동가능
	INT08U				InterLock_CVNO[8];		// CV 구동금지
	DeviceMode_t		SRM_Mode;			// 	
	DeviceStatus1		SRM_Status1;		// 
	DeviceStatus2		SRM_Status2;		// 
	INT08U				SRM_OperationCode;
	INT08U				MainErrCode;
	INT08U				SubErrCode;
	INT16U				ErrReason;
	ForkPosInfo			PosFork1;
	ForkPosInfo			PosFork2;
	CellPosSTR			TargetFork1;
	INT08U				Reserved1[2];
	CellPosSTR			TargetFork2;
	INT08U				Reserved2[2];
	INT08U				Reserved3[11];
	DriveStatus			Inv_St[4];
	WorkInfoSTR			ForkWork[2];

	INT32U				Transfer_WorkNo;
	INT08U				Task_Operation;
	INT08U				Reserved4;
	TaskCommand			TaskWork[MAX_TASK_COUNT];

	INT08U				Digital_Input[20];
	INT08U				Digital_Output[9];

	INT08U				ManualOutputMode[5];

	InvErrCode_Str		InvErrorCode;

	INT08U				ManualOutputMode2[4];

	INT08U				Reserved5[3];

	Lidar_Str			Lidar;
	//INT08U				Reserved5[7];

	Maintanance_Info		MaintananceInfo;
};
typedef struct tagStatus  StatusSTR;

struct __attribute__((__packed__)) tagStatusReq
{
	INT08U				UseFlag;	// 
	INT08U				Reserved[5];
	INT32U				SysTime;				// UTC Time
	INT08U				CP_Mode;				// 
	ControlPanelSTR		CP_State;			//
	INT08U				InterLock_CVOK[8];
	INT08U				InterLock_CVNO[8];
	INT08U				HMI_Data[54];
	INT08U				Reserved1[5];
};
typedef struct tagStatusReq  StatusReqSTR;

struct __attribute__((__packed__)) tagDSP_ReqStatus
{
	INT08U				Reserved0[2];
	INT32U				SysTime;				// UTC Time
	INT32U				InterLock0;
	INT32U				InterLock1;
	DeviceMode_t		SRM_Mode;			// 	
	DeviceStatus1		SRM_Status1;		// 
	DeviceStatus2		SRM_Status2;		// 
	INT08U				SRM_OperationCode;
	INT08U				MainErrCode;
	INT08U				SubErrCode;
	INT16U				ErrReason;
	ForkPosInfo			PosFork1;
	ForkPosInfo			PosFork2;
	CellPosSTR			TargetFork1;
	INT08U				Reserved1[1];
	CellPosSTR			TargetFork2;
	INT08U				Reserved2[1];
	INT08U				LoadFactor;
	INT08U				Buzzer_Use;
	INT08U				Reserved3[9];

	DriveStatus			Invertor_St[4];

	WorkInfoSTR			ForkWork[2];

	INT08U				Digital_IO[20];
};
typedef struct tagDSP_ReqStatus  DSP_ReqStatus;

struct __attribute__((__packed__)) tagTaskOrder
{
	INT32U				Transfer_WorkNo;
	INT16U				Reserved0;
	TaskCommand			TaskWork[MAX_TASK_COUNT];
};
typedef struct tagTaskOrder  TaskOrder;

struct __attribute__((__packed__)) tagUniLogSTR_T1
{
	INT32U			SysTime;
	INT08U			MainCode;
	INT08U			SubCode;
	INT08U			Value;
	CellPosSTR		Pos;      //
	LogForkWorkSTR	Fork[2];  //
	INT08U			Digital_Input[20];
	INT08U			Digital_Output[9];
};
typedef struct tagUniLogSTR_T1  UniLogSTR_Type1;

struct __attribute__((__packed__)) tagUniLogSTR_InvErr
{
	INT32U			Position;
	INT16S			Speed;
	INT16U			MainCode;
	INT16U			SubCode;
	INT16U			FBCode;
};
typedef struct tagUniLogSTR_InvErr  UniLogSTR_InvErr;

struct __attribute__((__packed__)) tagUniLogSTR_T2
{
	INT32U				SysTime;
	INT08U				MainCode;
	INT08U				SubCode;
	INT08U				Value;
	CellPosSTR			Pos;		//
	LogForkWorkSTR		Fork;		//
	INT32U				WorkNo;
	UniLogSTR_InvErr	InvErr;
	INT08U				Digital_Input[20];
	INT08U				Digital_Output[9];
};
typedef struct tagUniLogSTR_T2  UniLogSTR_Type2;

struct __attribute__((__packed__)) tagAlarmLogSTR
{
	INT16U    Repeat;
	INT16U    Inx;

#if DEF_ALARM_LOG_TYPE == 1 
	UniLogSTR_Type1 Log[MAX_ALARM_LOG_COUNT];
#elif DEF_ALARM_LOG_TYPE == 2
	UniLogSTR_Type2 Log[MAX_ALARM_LOG_COUNT];
#endif
};
typedef struct tagAlarmLogSTR  AlarmLogSTR;


#define WORK_STATUS_NONE			0
#define WORK_STATUS_IMPOSSIBLE		1
#define WORK_STATUS_DOING			2
#define WORK_STATUS_FAIL			3
#define WORK_STATUS_COMPLETE		4
#define WORK_STATUS_STOP			5

enum enumCMD_MOVE_STEP_PROCESS
{
	CMD_MOVE_STEP_NONE = 0,
	CMD_MOVE_STEP_RX,
	CMD_MOVE_STEP_2,
	CMD_MOVE_STEP_3,
	CMD_MOVE_STEP_4,
	CMD_MOVE_STEP_5,
	CMD_MOVE_STEP_6,
	CMD_MOVE_STEP_MOVING,
	CMD_MOVE_STEP_COMPELTE,
};

enum enumCMD_FORK_STEP_PROCESS
{
	CMD_FORK_STEP_NONE = 0,
	CMD_FORK_STEP_RX,							//1		紐��뱀�� ����
	CMD_FORK_STEP_MOVING_FROM,					//2		From�쇰� �대�� ���� ���� 
	CMD_FORK_STEP_ARRIVED_FROM,					//3		From ��李� 
	CMD_FORK_STEP_FORK_OUT_FROM,				//4		Fork 吏�異�
	CMD_FORK_STEP_FORK_UP_FROM,					//5		Fork ����移�濡� �대�� ���� 
	CMD_FORK_STEP_FORK_IN_FROM,					//6		Fork 蹂듦� ���� 
	
	CMD_FORK_STEP_MOVING_TO,					//7		to濡� �대�� ���� ���� 
	CMD_FORK_STEP_ARRIVED_TO,					//8		to ��李� 
	CMD_FORK_STEP_FORK_OUT_TO,					//9		Fork 吏�異�
	CMD_FORK_STEP_FORK_DOWN_TO,					//10	Fork ����移�濡� �대�� ���� 
	CMD_FORK_STEP_FORK_IN_TO,					//11	Fork 蹂듦� ����
	
	CMD_FORK_STEP_LODADED,						//12	���� ��猷� 
	CMD_FORK_STEP_UNLODADED,					//13	�댁�� ��猷� 
	
	CMD_FORK_STEP_STICKY_MOVING_FROM = 0x10,	//16	SRM 二쇳�� 諛� �뱁��媛� ����  
	CMD_FORK_STEP_STICKY_ARRIVED_FROM,			//17	SRM 紐⑹��吏� ��李�
	CMD_FORK_STEP_STICKY_FORK_OUT_FROM,			//18	Fork 吏�異�
	CMD_FORK_STEP_STICKY_FORK_UP_FROM,			//19	罹�由ъ� ���� ���� ���� 
	CMD_FORK_STEP_STICKY_FORK_DOWN_FROM,		//20	罹�由ъ� ��媛� ���� ���� 
	CMD_FORK_STEP_STICKY_FORK_IN_FROM,			//21	Fork 蹂듦�
	CMD_FORK_STEP_STICKY_DONE,					//22	STICKY ���� ��猷� 
};

enum enumCMD_TASK_STATUS
{
	TASK_STATUS_NONE = 0,
	TASK_STATUS_STAND_BY,
	TASK_STATUS_DOING,
	TASK_STATUS_FAIL,
	TASK_STATUS_COMPLETE,
};

enum enumCMD_TASK_STEP_PROCESS
{
	CMD_TASK_STEP_NONE = 0x80,
	CMD_TASK_STEP_RX,
	CMD_TASK_STEP_MOVING_FROM,
	CMD_TASK_STEP_ARRIVED_FROM,
	CMD_TASK_STEP_FORK_OUT_FROM,
	CMD_TASK_STEP_FORK_UP_FROM,
	CMD_TASK_STEP_FORK_IN_FROM,
	CMD_TASK_STEP_MOVING_TO,
	CMD_TASK_STEP_ARRIVED_TO,
	CMD_TASK_STEP_FORK_OUT_TO,
	CMD_TASK_STEP_FORK_DOWN_TO,
	CMD_TASK_STEP_FORK_IN_TO,
	CMD_TASK_STEP_LODADED,
	CMD_TASK_STEP_UNLODADED,
};

//
/*
#define WORK_STEP_NONE				0		//
#define WORK_STEP_CMD_RX			1		//
#define WORK_STEP_FROM_MOVE			2		//
#define WORK_STEP_STORE				3		//
#define WORK_STEP_TO_MOVE			4		//
#define WORK_STEP_UNSTORE			5		//
#define WORK_STEP_WRITE_WORKNUM		6		//
#define WORK_STEP_TO_MOVING			7		//
#define WORK_STEP_TO_MOVE_COMPLETE	8		//
*/

#define ORDER_CODE_NONE					0x00	//
#define ORDER_CODE_MOVE					0x01	//
#define ORDER_CODE_STORE				0x12	// 
#define ORDER_CODE_UNSTORE				0x13	// 
#define ORDER_CODE_RACK_TO_RACK			0x14	// 
#define ORDER_CODE_STATION_TO_STATION	0x15	// 
#define ORDER_CODE_RACK_CHG_DST			0x16	// 
#define ORDER_CODE_STATION_CHG_DST		0x17	// 
#define ORDER_CODE_STICKY				0x1A	// 

struct __attribute__((__packed__)) tagForkWorkCmd
{
	INT32U		WorkNum;
	CellPosSTR	FromCell;
	CellPosSTR	ToCell;
	INT08U		Good_Type;
	INT08U		Reserved[5];
};
typedef struct tagForkWorkCmd  ForkWorkCmdSTR;

struct __attribute__((__packed__)) tagWorkCmd
{
	INT08U			OrderCode;
	INT08U			OperationFlag;
	INT08U			Reserved[4];
	ForkWorkCmdSTR	Fork[2];
};
typedef struct tagWorkCmd  WorkCmdSTR;

struct __attribute__((__packed__)) tagWorkDelete
{
	INT08U         Flag1;
	INT32U         WorkNum1;

	INT08U         Flag2;
	INT32U         WorkNum2;
};
typedef struct tagWorkDelete  WorkDeleteSTR;

struct __attribute__((__packed__)) tagWorkAddDelete
{
	INT08U         Cmd;
	INT08U         Level;
	INT32U         WorkNum;
};
typedef struct tagWorkAddDelete  WorkAddDeleteSTR;

//////////////////////////////////////////////////////////////////////////////////

struct __attribute__((__packed__)) tagManualCmdSTR
{
	INT08U		Trav;				// Travel manual command
	INT08U		Lift;				// Lift manual command
	INT08U		Fork[2];			// Fork manual command
	INT08U		Reserved[10];
	INT08U		ForkRefPos;			// Fork Move Reference location
	INT08U		TravLiftRefPos;		// Trav, Lift Move Reference location
};
typedef struct tagManualCmdSTR  ManualCmdSTR;

//////////////////////////////////////////////////////////////////////////////////
struct __attribute__((__packed__)) tagCellSTR
{
	INT32S    TravPos;
	INT32S    LiftPos;
};
typedef struct tagCellSTR  CellSTR;

struct __attribute__((__packed__)) tagStaTravPosSTR
{
	INT08U		Type;				// 1:Load,	2:Unload, 3:Load/Unload
	INT16S		ForkDepth;
	CellSTR		Pos;
	INT08S		LevelUpOffset;
	INT08S		LevelDnOffset;
	INT08U		InterLock_SenNo;	// 8bit Sensor InterLock Number
	INT08U		PLC_IpAddr[4];
	INT16U		PLC_PortNum;
	INT16U		PLC_Addr;
	INT08U		PLC_Station_ID;
};
typedef struct tagStaTravPosSTR  StationSTR;

// Vexi Protocol 구조제
struct __attribute__((__packed__)) tagRackConfigComStruct
{
	INT08U			RackType;			// 1:SRM, 2:RTV
	INT16U			BayCount;
	INT16U			LvCount;
	INT08U			ForkType;
	INT16S			RowDepth[4];
	INT08U			Veriant_LT_Offset;
	INT08S			LevelUpOffset;
	INT08S			LevelDnOffset;
};
typedef struct tagRackConfigComStruct  RackConfigComSTR;

// 217 bytes
// External Flash 구초제
struct __attribute__((__packed__)) tagRackConfigStruct
{
	INT08U			RackType;			// 1:SRM, 2:RTV
	INT16U			BayCount;
	INT16U			LvCount;
	INT08U			ForkType;
	INT16S			RowDepth[4];
	INT08U			Veriant_LT_Offset;
	INT08S			LevelUpOffset;
	INT08S			LevelDnOffset;
	INT08U			Reseved[200];
};
typedef struct tagRackConfigStruct  RackConfigSTR;

// 1536 bytes
#define MAX_BAY_COUNT		(256)
#define MAX_LEVEL_COUNT		(128)
struct __attribute__((__packed__)) tagCellConfigSTR
{
	INT32U		BayPos[MAX_BAY_COUNT];
	INT32U		LvPos[MAX_LEVEL_COUNT];
};
typedef struct tagCellConfigSTR  CellConfigSTR;
/**/
struct __attribute__((__packed__)) tagCellConfigSTR_1
{
	INT32U		BayPos_1[MAX_BAY_COUNT];
	INT32U		LvPos_1[MAX_LEVEL_COUNT];
};
typedef struct tagCellConfigSTR_1  CellConfigSTR_1;
/**/
struct __attribute__((__packed__)) tagCellOffsetSTR
{
	INT08U		Bay_No;	// 0 -> Bay 1
	INT08U		Lv_No;	// 0 -> Lv 1
	INT08S		Trav_Left;
	INT08S		Lift_Left;
	INT08S		Fork_Left;
	INT08S		Trav_Right;
	INT08S		Lift_Right;
	INT08S		Fork_Right;
};
typedef struct tagCellOffsetSTR  CellOffsetSTR;

enum enumSTATION_INTERLOCK_TYPE {
	ST_INTERLOCK_NOT_USE = 0,
	ST_INTERLOCK_8BIT,			// 8bit Sensor
	ST_INTERLOCK_COM,			// 지상반 통신
};

enum enumSTATION_TYPE {
	STATION_NOT_USE = 0,
	STATION_IN_TYPE,			// 입고
	STATION_OUT_TYPE,			// 출고
	STATION_IN_OUT_TYPE,		// 입출고
	STATION_VIRTUAL_TYPE,		// 가상스테이션
};

enum enumSTATION_INTERLOCK_MODE {
	ST_INTERLOCK_MODE_0 = 0,						// Default
	ST_INTERLOCK_MODE_HANKOOK_TIRE_TP2_DIR,			// HankookTire TP2 입고, 출고, 화물 방향
	ST_INTERLOCK_MODE_HANKOOK_TIRE_TP2_FlOOR_NO,	// HankookTire TP2 입고, 출고, 층 번호
};

struct __attribute__((__packed__)) tagStationStruct
{
	INT08U		Type;				// 1:Load,	2:Unload, 3:Load/Unload 4: Virtual 
	INT08U		Goods_Type;
	CellSTR		InPosition;
	INT16S		ForkDepth;
	INT08U		LevelUpOffset;
	INT08S		LevelDnOffset;
	INT08U		InterLock_No;					// InterLock Number, 한국타이어 TP2 입고 InterLock Number
	INT08U		Stabilzation_Time;
	INT08U		Station_DSTLR_Fault_Flag;		// 스테이션 이중입고 알람 설정
	INT08U		InterLock_No_Out;				// 한국타이어 TP2 출고 InterLock Number
	INT08U		Reserved[2];
};
typedef struct tagStationStruct  StationSet_t;

#define MAX_STATION_COUNT		(50)

struct __attribute__((__packed__)) tagStationSetupStruct
{
	INT08U			TotalUseCnt;		// 사용할 스테이션 개수
	INT08U			InterLock_Type;
	INT08U			Reserved[16];
	StationSet_t	StationSet[MAX_STATION_COUNT];
};
typedef struct tagStationSetupStruct  StationSetupSTR;

//////////////////////////////////////////////////////////////////////////////////

struct __attribute__((__packed__)) tagProhibitRackPos
{
	INT08U		Row_Apply;		// 1 ~ 4
	INT16U		Bay_No;		// 
	INT08U		Lv_No;		//
	INT08U		Reserved;
};
typedef struct tagProhibitRackPos  InhibitRackSet_t;

#define MAX_INH_RACK_COUNT		(100)

struct __attribute__((__packed__)) tagProhibitRackCom
{
	INT08U				Count;
	INT08U				Reserved;
	InhibitRackSet_t	SetData[MAX_INH_RACK_COUNT];
	//INT08U				Reserved1[516];
};
typedef struct tagProhibitRackCom ProhibitRackComSTR;

struct __attribute__((__packed__)) tagProhibitRack
{
	INT08U				Count;
	INT08U				Reserved;
	InhibitRackSet_t	SetData[MAX_INH_RACK_COUNT];
	INT08U				Reserved1[516];
};
typedef struct tagProhibitRack ProhibitRackSTR;

struct __attribute__((__packed__)) tagSpecialRackPos
{
	INT08U		Goods_Type;
	//INT08U		Postion_Type;   //
	INT08U		Row_No;         // 
	INT16U		Bay_No;         // 
	INT08U		Lv_No;          // 
	INT08U		Reserved[4];
};
typedef struct tagSpecialRackPos  SpecialRackSet_t;

#define MAX_SPECIAL_RACK_COUNT		(100)

struct __attribute__((__packed__)) tagSpecialRackCom
{
	INT08U				Count;
	INT08U				Reserved;
	SpecialRackSet_t	SetData[MAX_SPECIAL_RACK_COUNT];
	//INT08U				Reserved1[116];
};
typedef struct tagSpecialRackCom SpecialRackComSTR;

struct __attribute__((__packed__)) tagSpecialRack
{
	INT08U				Count;
	INT08U				Reserved;
	SpecialRackSet_t	SetData[MAX_SPECIAL_RACK_COUNT];
	INT08U				Reserved1[116];
};
typedef struct tagSpecialRack SpecialRackSTR;

//////////////////////////////////////////////////////////////////////////////////

struct __attribute__((__packed__)) tagSaveWork
{
	INT08U         CheckString[4];
	WorkInfoSTR    WorkSt[2];
	WorkCmdSTR     WorkCmd;
};
typedef struct tagSaveWork SaveWorkSTR;

#define DEF_PARAM_COUNT		8

//////////////////////////////////////////////////////////////////////////////////
struct __attribute__((__packed__)) tagInvertor_TxData
{
	INT16U	StatusWord;		// 
	INT32S	CurPosition;	// 
	INT16S	ActualSpeed;	// 
	INT16S	ActualTorque;	// 
	INT16U	ErrorCodeMSB;	// 
	INT16U	ErrorCodeLSB;	// 
	INT16U	FBErrorCode;	//
	INT32S	Param[DEF_PARAM_COUNT];
	INT32S	Actual_Reference_offset;
	INT32S	Actual_Position_gain;
	INT16U	Actual_Position_Window;
	INT16U	Reserved[15];	//
};
typedef struct tagInvertor_TxData  Invertor_TxData;

struct __attribute__((__packed__)) tagInvertor_RxData
{
	INT16U	ControlWord;		//
	INT32S	TargetPosition;		//
	INT16S	Setpoint_Speed;		//
	INT16S	Setpoint_Acc;		//
	INT16S	Setpoint_Dec;		//
	INT16U	JerkTime;			//
	INT32S	Set_Reference_offset;
	INT32S	Set_Position_gain;
	INT16U	Set_Position_Window;
	INT16U	Reserved[15];		//
};
typedef struct tagInvertor_RxData  Invertor_RxData;

struct __attribute__((__packed__)) tagInvertorInfo
{
	Invertor_TxData		TxPDO[6];
	Invertor_RxData		RxPDO[6];
};
typedef struct tagInvertorInfo  InvertorInfoSTR;


struct __attribute__((__packed__)) tagTestStatus
{
	INT32S	St[32];
	INT32S	Ctrl[16];
	INT32S	St2[32];
};
typedef struct tagTestStatus  TestStatusSTR;

struct __attribute__((__packed__)) tagTestControl
{
	INT32S                Ctrl[16];
};
typedef struct tagTestControl  TestControlSTR;

struct __attribute__((__packed__)) tagPosition
{
	INT08U         PosType;
	INT08S         TravWard;

	INT32S         NowPosition;
	INT32S         TargetPosition;
	INT16S         Velocity;
	INT16S         DecelDistance;
};
typedef struct tagPosition  PositionSTR;

struct __attribute__((__packed__)) tagPlcConnect
{
	INT08U         InterfaceType;
	INT08U         Reserved1;
	INT08U         IpAddr[4];
	INT16U         PortNum;
	INT08U         StationIndex;
	INT08U         Reserved2[3];
};
typedef struct tagPlcConnect  PlcConnectSTR;

struct __attribute__((__packed__)) tagPlcInfo
{
	INT16U         StartAddr;
	PlcConnectSTR  PlcSta[6];
};
typedef struct tagPlcInfo  PlcInfoSTR;

struct __attribute__((__packed__)) tagPlcManualCtrl
{
	INT08U         Reserved1;
	INT08U         PLC_ControlMode;
	INT08U         Reserved2;

	INT08U         StationNo;   // 1~4
	INT08U         Mode;
	INT32U         WorkNum[2];
};
typedef struct tagPlcManualCtrl  PlcManualCtrlSTR;

/////////////////////////////////////////////////////////

#define MAX_EVENT_SECTOR            4
#define MAX_EVENT_PER_SECTOR    16384	// 0x3FFF
#define VIEW_EVENT_COUNT         5000  

/*
#if defined (SET_DEVICE_TYPE_LIFT)
#define SAVE_EVENT_TYPE          0x06  
#endif

#if defined (SET_DEVICE_TYPE_SHUTTLE)
#define SAVE_EVENT_TYPE          0x07  
#endif
*/

/*******************************************************************************/
/* 占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙                                                             */
/*******************************************************************************/
struct __attribute__((__packed__)) tagExecFile
{
	INT08U  isFusing[10];

	INT08U  MadeBy;
	INT08U  ProgramType;
	INT08U  DownloadType;
	INT08U  FileType;
	INT32U  TotalSize;
	INT32U  SuccessSize;
	INT16U  FileCrc;
	INT32U  DownloadBufPos;
};
typedef struct tagExecFile  ExecFileSTR;

struct __attribute__((__packed__)) tagDeviceSetting
{
	NetworkInfo_t		NetworkInfo_0;
	INT08U				MyMACAddr_0[6];

	NetworkInfo_t		NetworkInfo_1;
	INT08U				MyMACAddr_1[6];

	NetworkInfo_t		NetworkInfo_2;
	INT08U				MyMACAddr_2[6];

	ProjectID_t			ProjectID;

	INT08U				Reserved[30];
};
typedef struct tagDeviceSetting  DeviceSetting;

struct __attribute__((__packed__)) tagSRM_Machine_Type
{
	INT08U		Fork_Count;				//< Fork Count - 1:Single, 2:Twin
	INT08U		Drive_Invertor_Count;	/**< 주행드라이브 수량	*/
	INT08U		Drive_Type;				/*!< 주행 구동 방식 - 1:휠구동, 2:타이밍벨트	*/
	INT08U		Fork_Type;				/*!< 포크 구동 타입 - 1:싱글딥, 2:더블딥2POS, 3:더블딥3POS, 4:더블딥2POS_베리언트, 5:더블딥3POS_베리언트	*/
	INT08U		Inverter_Vendor;		/*!< 적용인버터 - 1:SEW, 2:SIMENS	*/
	INT08U		Fork_Drive_Type;		/*!< 포크 인버터 구동방식 - 1:주행/승강인버터 공용, 2:별도 구성	*/
	INT08U		Fork_Sensor_Type;		/*!< 포크 위치 센서	*/
	INT08U		Drive_Sensor_Type;		/*!< 주행 위치 센서	*/
	INT08U		Lift_Sensor_Type;		/*!< 승강 위치 센서	*/
	INT08U		Lamp_Type;				/*!< 램프 타입 0 : LED BAR, 1: Tower Lamp	*/
	INT08U		Fork_Encoder_Type;		/*!< 포크 엔코더 타입 0 : Absolute, 1:  Incremental	*/
};
typedef struct tagSRM_Machine_Type  SRM_Machine_STR;

struct __attribute__((__packed__)) tagMX_DSP_IP
{
	INT08U		IP[4];
	INT16U		Reserved;
	//INT16U		RemotePort;
};
typedef struct tagMX_DSP_IP  MX_DSP_IP;

struct __attribute__((__packed__)) tagMX_DSP_Setting
{
	INT08U		Com_Type;		// 0: Not Use, 1: EtherNet, 2: RS485
	INT08U		Connect_Count;	// 
	MX_DSP_IP	NetIf[2];
};
typedef struct tagMX_DSP_Setting  MX_DSP_Setting;

// Vexi 통신 구조체
struct __attribute__((__packed__)) tagSRM_SettingCom
{
	SRM_Machine_STR		mType;
	INT08U				Reserved[14];
	MX_DSP_Setting		DSP_Set;			// 11 Bytes
};
typedef struct tagSRM_SettingCom  SRM_Machine_TypeCom;

// External Flash 메모리 구조체
struct __attribute__((__packed__)) tagSRM_Setting
{
	SRM_Machine_STR		mType;
	INT08U				Reserved[14];
	MX_DSP_Setting		DSP_Set;			// 11 Bytes
	INT08U				Reserved1[50];
};
typedef struct tagSRM_Setting  SRM_Machine_Type;

struct __attribute__((__packed__)) tagDI_Struct
{
	INT08U	Type;		//< 255 : Not Use, 0 : MCU, 1 ~ : EtherCAT Slave ID
	INT08U	Pin;		//< 0 ~ 31
	INT08U	NO_NC;		//< 0 : Normal Open, 1: Normal Close
	INT08U	FilterTime;	//< 0 ~ 255
	INT08U	duplexing;	//< 0 : Not Use, 1:OR, 2:AND
};

typedef struct tagDI_Struct  DI_t;

struct __attribute__((__packed__)) tagDO_Struct
{
	INT08U	Type;		//< 255 : Not Use, 0 : MCU, 1 ~ : EtherCAT Slave ID
	INT08U	Pin;		//< 0 ~ 31
	INT08U	NO_NC;		//< 0 : Normal Open, 1: Normal Close
};

typedef struct tagDO_Struct  DO_t;

/*! SRM Input Map */
enum INPUT_MAP {
	IN_EM = 0,	/*!< ID 1, Emergency switch */
	IN_AUTO,	/*!< ID 2, Auto Switch */
	IN_INSP,	/*!< ID 3, Manual Switch */
	IN_RDF,		/*!< ID 4, Ready Feedback */
	IN_LST,		/*!< ID 5, Lift Limit Switch */
	IN_TST,		/*!< ID 6, Travel Limit Switch */
	IN_MFLT,	/*!< ID 7, Modem Fault */
	IN_GOV,		/*!< ID 8, Governor */
	IN_MCF,		/*!< ID 9, Control Power Feedback */
	IN_MC1F,	/*!< ID 9, MC1 Feedback */
	IN_PDOOR,	/*!< ID 10, ContolBox Door State */
	IN_PTH,		/*!< ID 11, ContolBox Temperature State */
	IN_MCTMF,	/*!< ID 13, 주행모터 MC 피드백 */
	IN_MCFMF,	/*!< ID 14, 포크1 모터 MC 피드백 */
	IN_T1PSF,	/*!< ID 15, 주행-포크1 모터 선택 상태 */
	IN_T1OSO,	/*!< ID 16, 주행-포크1 인버터 출력 상태 */
	IN_LBMMSF1,	/*!< ID 17, 승강1 브레이크 MMS트립 감지 */
	IN_TBMMSF1,	/*!< ID 18, 주행1 브레이크 MMS트립 감지 */
	IN_FBMMSF1,	/*!< ID 19, 포크1 브레이크 MMS트립 감지 */
	IN_CPTF,	/*!< ID 20, */
	IN_TDF,		/*!< ID 21, 주행 전진 감속 */
	IN_TDR,		/*!< ID 22, 주행 후진 감속 */
	IN_THP,		/*!< ID 23, 주행 원점 */
	IN_TSP,		/*!< ID 24, 주행 정위치 */
	IN_CFLT,	/*!< ID 25, 컨버터 이상 - PRU 이상 */
	IN_CRD,		/*!< ID 26, 컨버터 준비 */
	IN_MC2F,		/*!< ID 27, MC2 피드백 */
	IN_MCLMF,		/*!< ID 28, 승강모터 MC 피드백 */
	IN_MCLM2F,		/*!< ID 29, 포크2 모터 MC 피드백 */
	IN_T2PSF,		/*!< ID 30, 승강-포크2 모터 선택 상태 */
	IN_T2OSO,		/*!< ID 31, 주행-포크2 인버터 출력 상태 */
	IN_FBMMSF2,		/*!< ID 32, */
	IN_CVOK1,		/*!< ID 33, 스테이션 8bit 인터록 */
	IN_CVOK2,		/*!< ID 34, 스테이션 8bit 인터록 */
	IN_CVOK3,		/*!< ID 35, 스테이션 8bit 인터록 */
	IN_CVOK4,		/*!< ID 36, 스테이션 8bit 인터록 */
	IN_CVOK5,		/*!< ID 37, 스테이션 8bit 인터록 */
	IN_CVOK6,		/*!< ID 38, 스테이션 8bit 인터록 */
	IN_CVOK7,		/*!< ID 39, 스테이션 8bit 인터록 */
	IN_CVOK8,		/*!< ID 40, 스테이션 8bit 인터록 */
	IN_FAN_FAULT,	/*!< ID 41, FAN FAULT */
	IN_TS1_ENB,		/*!< ID 42, Mobile HMI Enabling button */
	IN_TS2_ENB,		/*!< ID 43, Mobile HMI Enabling button */
	IN_RVDR1,		/*!< ID 44, Rack 수직도 우측 1 */
	IN_RVDR2,		/*!< ID 45, Rack 수직도 우측 2 */
	IN_RVDL1,		/*!< ID 46, Rack 수직도 좌측 1 */
	IN_RVDL2,		/*!< ID 47, Rack 수직도 좌측 2 */
	IN_LBMMSF2,		/*!< ID 48, 승강2 브레이크 MMS트립 감지 */
	IN_TBMMSF2,		/*!< ID 49, 주행2 브레이크 MMS트립 감지 */
	IN_F1ENC,		/*!< ID 50, */
	IN_LDU,			/*!< ID 51, */
	IN_LDD,			/*!< ID 52, */
	IN_LHP,			/*!< ID 53, */
	IN_LSP,			/*!< ID 54, */
	IN_GOX1,		/*!< ID 55, */
	IN_GOXH1,		/*!< ID 56, */
	IN_GOXM1,		/*!< ID 57, */
	IN_GOXS1,		/*!< ID 58, */
	IN_GWL1,		/*!< ID 59, */
	IN_GWR1,		/*!< ID 60, */
	IN_GWLe1,		/*!< ID 61, */
	IN_GWRe1,		/*!< ID 62, */
	IN_GDFL1,		/*!< ID 63, */
	IN_GDFR1,		/*!< ID 64, */
	IN_GDRL1,		/*!< ID 65, */
	IN_GDRR1,		/*!< ID 66, */
	IN_GHL1,		/*!< ID 67, */
	IN_GHR1,		/*!< ID 68, */
	IN_FOKL1,		/*!< ID 69, */
	IN_FOKR1,		/*!< ID 70, */
	IN_FEL1,		/*!< ID 71, */
	IN_FER1,		/*!< ID 72, */
	IN_FCL1,		/*!< ID 74, */
	IN_FCR1,		/*!< ID 73, */
	IN_DSTL1,		/*!< ID 75, */
	IN_DSTR1,		/*!< ID 76, */
	IN_DSTLe1,		/*!< ID 77, */
	IN_DSTRe1,		/*!< ID 78, */
	IN_RTF,			/*!< ID 79, */
	IN_RTR,			/*!< ID 80, */
	IN_RTF2,		/*!< ID 81, */
	IN_RTR2,		/*!< ID 82, */
	IN_GOX2,		/*!< ID 83, */
	IN_GOXH2,		/*!< ID 84, */
	IN_GOXM2,		/*!< ID 85, */
	IN_GOXS2,		/*!< ID 86, */
	IN_GWL2,		/*!< ID 87, */
	IN_GWR2,		/*!< ID 88, */
	IN_GWLe2,		/*!< ID 89, */
	IN_GWRe2,		/*!< ID 90, */
	IN_GDFL2,		/*!< ID 91, */
	IN_GDFR2,		/*!< ID 92, */
	IN_GDRL2,		/*!< ID 93, */
	IN_GDRR2,		/*!< ID 94, */
	IN_GHL2,		/*!< ID 95, */
	IN_GHR2,		/*!< ID 96, */
	IN_FOKL2,		/*!< ID 97, */
	IN_FOKR2,		/*!< ID 98, */
	IN_FEL2,		/*!< ID 99, */
	IN_FER2,		/*!< ID 100, */
	IN_FCR2,		/*!< ID 101, */
	IN_FCL2,		/*!< ID 102, */
	IN_DSTL2,		/*!< ID 103, */
	IN_DSTR2,		/*!< ID 104, */
	IN_DSTLe2,		/*!< ID 105, */
	IN_DSTRe2,		/*!< ID 106, */
	IN_FML1,		/*!< ID 107, */
	IN_FMR1,		/*!< ID 108, */
	IN_FHL1,		/*!< ID 109, */
	IN_FHR1,		/*!< ID 110, */
	IN_FML2,		/*!< ID 111, */
	IN_FMR2,		/*!< ID 112, */
	IN_FHL2,		/*!< ID 113, */
	IN_FHR2,		/*!< ID 114, */
	IN_ODSTL1,		/*!< ID 115, */
	IN_ODSTR1,		/*!< ID 116, */
	IN_DSTLR1,		/*!< ID 117, */
	IN_DSTRR1,		/*!< ID 118, */
	IN_ODSTL2,		/*!< ID 119, */
	IN_ODSTR2,		/*!< ID 120, */
	IN_DSTLR2,		/*!< ID 121, */
	IN_DSTRR2,		/*!< ID 122, */
	IN_LSTH,			/*!< ID 123, */
	IN_LSTE,			/*!< ID 124, */
	IN_LD,				/*!< ID 125, */
	IN_TSTH,			/*!< ID 126, */
	IN_TSTE,			/*!< ID 127, */
	IN_TD,				/*!< ID 128, */
	IN_FK1_FAULT,		/*!< ID 129, */
	IN_FK1_STOP,		/*!< ID 130, */
	IN_FK2_FAULT,		/*!< ID 131, */
	IN_FK2_STOP,		/*!< ID 132, */
	IN_SAFETY_FLT,		/*!< ID 133, */
	IN_LIDAR1_FAULT,	/*!< ID 134, */
	IN_LIDAR2_FAULT,	/*!< ID 135, */
	IN_RESERVED_136,	/*!< ID 136, */
	IN_RESERVED_137,	/*!< ID 137, */
	IN_RESERVED_138,	/*!< ID 138, */
	IN_RESERVED_139,	/*!< ID 139, */
	IN_RESERVED_140,	/*!< ID 140, */
	IN_RESERVED_141,	/*!< ID 141, */
	IN_RESERVED_142,	/*!< ID 142, */
	IN_RESERVED_143,	/*!< ID 143, */
	IN_RESERVED_144,	/*!< ID 144, */
	IN_RESERVED_145,	/*!< ID 145, */
	IN_RESERVED_146,	/*!< ID 146, */
	IN_RESERVED_147,	/*!< ID 147, */
	IN_RESERVED_148,	/*!< ID 148, */
	IN_RESERVED_149,	/*!< ID 149, */
	MAX_DI_CNT
};

/*! SRM Output Map */
enum OUTPUT_MAP {
	OUT_IINH = 0,	/*!< ID 1, 주행, 승강 인버터 Inhibit */
	OUT_FCD,		/*!< ID 2, 강제모드 */
	OUT_BL,			/*!< ID 3, 타워램프 (청색) */
	OUT_RED,		/*!< ID 4, 타워램프 (적색) */
	OUT_YEL,		/*!< ID 5, 타워램프 (황색) */
	OUT_GRN,		/*!< ID 6, 타워램프 (녹색) */
	OUT_SUD,		/*!< ID 7, 타워램프 (부저) */
	OUT_MCE,		/*!< ID 8, 구동전원 MC (MC1, MC2) */

	OUT_MCUB,		/*!< ID 9, 상부 브레이크 MC */
	OUT_PLAMP,		/*!< ID 10, 제어반 램프 */
	OUT_PFAN,		/*!< ID 11, 제어반 쿨링팬 */
	OUT_MCTM,		/*!< ID 12, 주행 모터 MC */
	OUT_MCFF1,		/*!< ID 13, 포크1 모터 MC */
	OUT_T1FSPC,		/*!< ID 14, 포크1 방향 */
	OUT_T1SPO,		/*!< ID 15, SPARE */
	OUT_MCFB1,		/*!< ID 16, 포크1 브레이크 MC */

	OUT_COSE,		/*!< ID 17, 컨버터/회생 유닛 Output Stage Enable */
	OUT_CENB,		/*!< ID 18, 컨버터/회생 유닛 Enable */
	OUT_CRST,		/*!< ID 19, 컨버터/회생 유닛 Reset */
	OUT_MCLM,		/*!< ID 20, 승강 모터 MC */
	OUT_MCFM2,		/*!< ID 21, 포크2 모터 MC */
	OUT_LFSPC,		/*!< ID 22, 포크2 방향 */
	OUT_LSPO,		/*!< ID 23, SPARE */
	OUT_MCFB2,		/*!< ID 24, 포크2 브레이크 MC */

	OUT_CVNO1,		/*!< ID 25, 스테이션 8bit 인터록 */
	OUT_CVNO2,			/*!< ID 26, 스테이션 8bit 인터록 */
	OUT_CVNO3,			/*!< ID 27, 스테이션 8bit 인터록 */
	OUT_CVNO4,			/*!< ID 28, 스테이션 8bit 인터록 */
	OUT_CVNO5,			/*!< ID 29, 스테이션 8bit 인터록 */
	OUT_CVNO6,			/*!< ID 30, 스테이션 8bit 인터록 */
	OUT_CVNO7,			/*!< ID 31, 스테이션 8bit 인터록 */
	OUT_CVNO8,			/*!< ID 32, 스테이션 8bit 인터록 */

	OUT_RDE,			/*!< ID 33, 장비 준비 */
	OUT_DEVICE_RST,		/*!< ID 34, 장치 리셋 */
	OUT_LED_RD,			/*!< ID 35, LED BAR RED */
	OUT_LED_GR,			/*!< ID 36, LED BAR GREEN */
	OUT_LED_BU,			/*!< ID 37, LED BAR BLUE */
	OUT_FK1_JOG,		/*!< ID 38, FK1_JOG */
	OUT_FK1_JOG_R,		/*!< ID 39, FK1_JOG_R */
	OUT_FK1_JOG_L,		/*!< ID 40, FK1_JOG_L */

	/* ManualOutputMode End*/

	/* ManualOutputMode2 Start */
	OUT_FK1_RESET,		/*!< ID 41, FK1_RESET */
	OUT_FK1_STO1,		/*!< ID 42, FK1_STO1 */
	OUT_FK1_STO2,		/*!< ID 43, FK1_STO2 */

	/* DO_Set End*/

	/* DO_Set2 Start */
	OUT_FK2_JOG,		/*!< ID 44, FK2_JOG */
	OUT_FK2_JOG_R,		/*!< ID 45, FK2_JOG_R */
	OUT_FK2_JOG_L,		/*!< ID 46, FK2_JOG_L */
	OUT_FK2_RESET,		/*!< ID 47, FK2_RESET */
	OUT_FK2_STO1,		/*!< ID 48, FK2_STO1 */
	OUT_FK2_STO2,		/*!< ID 49, FK2_STO2 */
	OUT_WHI,			/*!< ID 50 */
	OUT_LSTH,			/*!< ID 51 */
	OUT_LSTE,			/*!< ID 52 */
	OUT_LIDAR1_S1,		/*!< ID 53 */
	OUT_LIDAR1_S2,		/*!< ID 54 */
	OUT_LIDAR1_S3,		/*!< ID 55 */
	OUT_LIDAR1_RESET,	/*!< ID 56 */
	OUT_LIDAR2_S1,		/*!< ID 57 */
	OUT_LIDAR2_S2,		/*!< ID 58 */
	OUT_LIDAR2_S3,		/*!< ID 59 */
	OUT_LIDAR2_RESET,	/*!< ID 60 */
	OUT_RESERVED_61,	/*!< ID 61 */
	OUT_RESERVED_62,	/*!< ID 62 */
	OUT_RESERVED_63,	/*!< ID 63 */
	OUT_RESERVED_64,	/*!< ID 64 */
	OUT_RESERVED_65,	/*!< ID 65 */
	OUT_RESERVED_66,	/*!< ID 66 */
	OUT_RESERVED_67,	/*!< ID 67 */
	OUT_RESERVED_68,	/*!< ID 68 */
	OUT_RESERVED_69,	/*!< ID 69 */
	MAX_DO_CNT,
};

enum ETHERCAT_SLAVE_PRODUCT_ID {
	MX_DIO_101 = 1,
	MX_DIO_201,
	MX_DIO_301,
	MX_RLY_101,
	MX_EXT_101,
	GX_MD1611,
	GX_ID1618,
	GX_ID3218,
	GX_EC0211,
	GX_MD1621,
	NOT_DEFINE = 255,
};

#define MAX_DIO_MODULE_CNT	10

struct __attribute__((__packed__)) tagDIO_Set_StructCom
{
	INT08U	SlaveID[MAX_DIO_MODULE_CNT];

	INT08U	Reserved0[5];

	DI_t	DI_Set[122];		// Digital IN 1 ~ 122
	DO_t	DO_Set[43];			// Digital Out 1 ~ 43

	DI_t	DI_Set2[27];		// Digital IN 123 ~ 159
	DO_t	DO_Set2[26];		// Digital Out 44 ~ 69
};
typedef struct tagDIO_Set_StructCom  DIO_SetComSTR;

struct __attribute__((__packed__)) tagDIO_Set_Struct
{
	INT08U	SlaveID[MAX_DIO_MODULE_CNT];

	INT08U	Reserved0[5];

	DI_t	DI_Set[122];		// Digital IN 1 ~ 122
	DO_t	DO_Set[43];			// Digital Out 1 ~ 43
	
	DI_t	DI_Set2[27];		// Digital IN 123 ~ 149
	DO_t	DO_Set2[26];		// Digital Out 44 ~ 69
	
	INT08U	Reserved1[39];
	//INT08U	Reserved1[192];			
};
typedef struct tagDIO_Set_Struct  DIO_SetSTR;

struct __attribute__((__packed__)) tagEtherCAT_SCAN_Struct
{
	INT08U	SlaveID;		//< 
	INT08U	Alias_Addr;		//< 0 ~ 31
};
typedef struct tagEtherCAT_SCAN_Struct  EtherCAT_Scan_t;

struct __attribute__((__packed__)) tagDIO_STR_Struct
{
	EtherCAT_Scan_t		Scan[10];
	INT08U				Reserved0[10];

	DIO_SetComSTR		Set;
};
typedef struct tagDIO_STR_Struct  DIO_SetInfoSTR;

/*******************************************************************************/
/* Flash */
/*******************************************************************************/
/*
struct __attribute__((__packed__)) tagSEnv
{
	INT08U			InitCode[4];   // "Devi"
	DeviceSetting	mParam;
	SRM_Setting		mSRM_Type;
	INT16U          Check_CRC;
};
typedef struct tagSEnv  DevSettingSTR;
*/

struct __attribute__((__packed__)) tagLastPositionSTR
{
	INT32S         Trav;
	INT32S         Lift;
	INT32S         Fork1;
	INT32S         Fork2;
	INT32S         Reserved[5];
};
typedef struct tagLastPositionSTR  LastPosition_Struct;

typedef union
{
	INT32S				B[9];
	LastPosition_Struct S;
} LastPositionSTR;

struct __attribute__((__packed__)) tagMachineSTR
{
	INT32S         Trav;
	INT32S         Lift;
	INT32S         Fork1;
	INT32S         Fork2;
	INT32S         Reserved[5];
};
typedef struct tagLastPositionSTR  LastPosition_Struct;

struct __attribute__((__packed__)) tagSumOperateTimeSTR
{
	INT32U		Sum_Second;
	INT32U		Sum_Minute;
};
typedef struct tagSumOperateTimeSTR  SumOperateTimeSTR;

struct __attribute__((__packed__)) tagSumDistanceSTR
{
	INT32U		Sum_mm;
	INT32U		Sum_Meter;
};
typedef struct tagSumDistanceSTR  SumDistanceSTR;

struct __attribute__((__packed__)) tagOperationInfoSTR
{
	SumOperateTimeSTR	Operation_Time[4];
	SumDistanceSTR		Moving_Distance[4];
	INT32U				BrakeOpen_Count[4];
	INT08U				reserved[20];
};
typedef struct tagOperationInfoSTR  OperationInfoSTR;

struct __attribute__((__packed__)) tagOperationInfoReqSTR
{
	INT32U				SumTime[4];
	INT32U				SumDistance[4];
	INT32U				SumCount[4];
	INT08U				reserved[20];
};
typedef struct tagOperationInfoReqSTR  OperationInfoReqSTR;

struct __attribute__((__packed__)) tagAlarmLogUnitSTR
{
	INT32U			SysTime;
	INT08U			MainCode;
	INT08U			SubCode;
	INT08U			Value;
	CellPosSTR		Pos;			//	Current Position
	LogForkWorkSTR	Fork[2];		// 
};
typedef struct tagAlarmLogUnitSTR  AlarmLogUnitSTR_0;

struct __attribute__((__packed__)) tagAlarmLogUnitSTR_1
{
	INT32U			SysTime;
	INT08U			MainCode;
	INT08U			SubCode;
	INT08U			Value;
	CellPosSTR		Pos;			//	Current Position
	LogForkWorkSTR	Fork[2];		// 
	INT08U			Digital_Input[20];
	INT08U			Digital_Output[9];
};
typedef struct tagAlarmLogUnitSTR_1  AlarmLogUnitSTR_1;

#define MAX_VELOCITY_CNT	16

enum enumTRAV_VELOCITY_TYPE {
	TRAV_VEL_AUTO_H = 0,
	TRAV_VEL_AUTO_M,
	TRAV_VEL_AUTO_L,
	TRAV_VEL_MAN_M,
	TRAV_VEL_MAN_L,
	TRAV_VEL_FORCE,
	TRAV_VEL_CREEP,
	TRAV_VEL_ORIGIN,
	TRAV_VEL_EMG,
	TRAV_VEL_AUTO_DEC_1,
	TRAV_VEL_AUTO_DEC_2,
	TRAV_VEL_SPARE_1,
	TRAV_VELOCITY_SPARE_2,
	TRAV_VELOCITY_SPARE_3,
	TRAV_VELOCITY_SPARE_4,
	TRAV_VELOCITY_SPARE_5,
	MAX_TRAV_VELOCITY_CNT
};

enum enumLIFT_VELOCITY_TYPE {
	LIFT_VEL_AUTO_H = 0,
	LIFT_VEL_AUTO_M,
	LIFT_VEL_AUTO_L,
	LIFT_VEL_MAN_M,
	LIFT_VEL_MAN_L,
	LIFT_VEL_FORCE,
	LIFT_VEL_CREEP,
	LIFT_VEL_ORIGIN,
	LIFT_VEL_EMG,
	LIFT_VEL_AUTO_DEC_1,
	LIFT_VEL_AUTO_DEC_2,
	LIFT_VEL_LIFT_AUTO_FORKOUT,
	LIFT_VEL_LIFT_MAN_FORKOUT,
	LIFT_VEL_LIFT_STICKY,
	LIFT_VELOCITY_SPARE_2,
	LIFT_VELOCITY_SPARE_3,
	MAX_LIFT_VELOCITY_CNT
};

enum enumFORK_VELOCITY_TYPE {
	FORK_VEL_AUTO_H = 0,
	FORK_VEL_AUTO_M,
	FORK_VEL_AUTO_L,
	FORK_VEL_MAN_M,
	FORK_VEL_MAN_L,
	FORK_VEL_FORCE,
	FORK_VEL_CREEP,
	FORK_VEL_ORIGIN,
	FORK_VEL_EMG,
	FORK_VEL_AUTO_DEC_1,
	FORK_VEL_AUTO_DEC_2,
	FORK_VELOCITY_SPARE_1,
	FORK_VELOCITY_SPARE_2,
	FORK_VELOCITY_SPARE_3,
	FORK_VELOCITY_SPARE_4,
	FORK_VELOCITY_SPARE_5,
	MAX_FORK_VELOCITY_CNT
};

enum enumDRIVE_VELOCITY_MODE {
	DRIVE_VELOCITY_AUTO_H = 0,
	DRIVE_VELOCITY_AUTO_M,
	DRIVE_VELOCITY_AUTO_L,
	DRIVE_VELOCITY_MANUAL_M,
	DRIVE_VELOCITY_MANUAL_L,
	DRIVE_VELOCITY_CREEP,
	DRIVE_VELOCITY_ORIGIN,
	MAX_DRIVE_VELOCITY_CNT
};

enum enumDECEL_RANGE_MODE {
	DECEL_MODE_NOT_USE = 0,
	DECEL_VELOCITY1_DRIVE,
	DECEL_VELOCITY2_DRIVE,
	DECEL_VELOCITY1_OVERSPEED,
	DECEL_VELOCITY2_OVERSPEED,
};

enum enumSOFT_ERROR_MODE {
	SOFT_ERROR_MODE_NOT_USE = 0,
	SOFT_ERROR_MODE_1,			// Error Home
	SOFT_ERROR_MODE_2,			// Error End
	SOFT_ERROR_MODE_3,			// Error Home, End
};

struct __attribute__((__packed__)) tagRetryInPositon
{
	INT08U RetryCount;
	INT16U RetryOffset;
};
typedef struct tagRetryInPositon  RetryInPositonSTR;

enum enumDELAY_TIME {
	DELAY_PREFORE_MOVE = 0,
	DELAY_AFTER_MOVE,
	DELAY_BEFORE_FORK_OUT,
	DELAY_AFTER_FORK_OUT,
	DELAY_BEFORE_FORK_OUT_LIFT,
	DELAY_AFTER_FORK_OUT_LIFT,
	DELAY_BEFORE_FORK_CENTER,
	DELAY_AFTER_FORK_CENTER,
	DELAY_TIME_SPARE8,
	DELAY_TIME_SPARE9,
	DELAY_TIME_SPARE10,
	DELAY_TIME_SPARE11,
	DELAY_TIME_SPARE12,
	DELAY_TIME_SPARE13,
	DELAY_TIME_SPARE14,
	DELAY_TIME_SPARE15,
	DELAY_TIME_SPARE16,
	DELAY_TIME_SPARE17,
	DELAY_TIME_SPARE18,
	DELAY_TIME_SPARE19,
	MAX_DELAY_TIME_CNT
};

struct __attribute__((__packed__)) tagDelayTime
{
	INT16U mSetValue[MAX_DELAY_TIME_CNT];
};
typedef struct tagDelayTime  DelayTimeSTR;

enum enumSETUP_TIMEOUT {
	SETUP_TIMEOUT_TRAVEL_ORIGIN = 0,	// 주행 원점설정
	SETUP_TIMEOUT_LIFT_ORIGIN,			// 승강 원점설정
	SETUP_TIMEOUT_FORK_ORIGIN,			// 포크 원점설정
	SETUP_TIMEOUT_SPARE3,
	SETUP_TIMEOUT_SPARE4,
	SETUP_TIMEOUT_SPARE5,
	SETUP_TIMEOUT_SPARE6,
	SETUP_TIMEOUT_SPARE7,
	SETUP_TIMEOUT_SPARE8,
	SETUP_TIMEOUT_SPARE9,
	SETUP_TIMEOUT_SPARE10,
	SETUP_TIMEOUT_SPARE11,
	SETUP_TIMEOUT_SPARE12,
	SETUP_TIMEOUT_SPARE13,
	SETUP_TIMEOUT_SPARE14,
	SETUP_TIMEOUT_SPARE15,
	SETUP_TIMEOUT_SPARE16,
	SETUP_TIMEOUT_SPARE17,
	SETUP_TIMEOUT_SPARE18,
	SETUP_TIMEOUT_SPARE19,
	MAX_SETUP_TIMEOUT_CNT
};

struct __attribute__((__packed__)) tagSetupTimeOut
{
	/*
	INT16U Travel_Origin;
	INT16U Lift_Origin;
	INT16U Fork_Origin;
	INT16U Reserved[17];
	*/
	INT16U mSetValue[MAX_SETUP_TIMEOUT_CNT];
};
typedef struct tagSetupTimeOut  SetupTimeOutSTR;

enum enumDRIVE_TIMEOUT {
	DRIVE_TIMEOUT_MANUAL_RXCOM = 0,		// 수동제어 명령 수신타임아웃
	DRIVE_TIMEOUT_HOME_RETURN,			// 홈복귀 
	DRIVE_TIMEOUT_SPARE2,
	DRIVE_TIMEOUT_SPARE3,
	DRIVE_TIMEOUT_SPARE4,
	DRIVE_TIMEOUT_SPARE5,
	DRIVE_TIMEOUT_SPARE6,
	DRIVE_TIMEOUT_SPARE7,
	DRIVE_TIMEOUT_SPARE8,
	DRIVE_TIMEOUT_SPARE9,
	DRIVE_TIMEOUT_SPARE10,
	DRIVE_TIMEOUT_SPARE11,
	DRIVE_TIMEOUT_SPARE12,
	DRIVE_TIMEOUT_SPARE13,
	DRIVE_TIMEOUT_SPARE14,
	DRIVE_TIMEOUT_SPARE15,
	DRIVE_TIMEOUT_SPARE16,
	DRIVE_TIMEOUT_SPARE17,
	DRIVE_TIMEOUT_SPARE18,
	DRIVE_TIMEOUT_SPARE19,
	MAX_DRIVE_TIMEOUT_CNT
};

struct __attribute__((__packed__)) tagDriveTimeOut
{
	/*
	INT16U Manual_RxCom;
	INT16U HomeReturn;
	INT16U Reserved[18];
	*/
	INT16U SetValue[MAX_DRIVE_TIMEOUT_CNT];
};
typedef struct tagDriveTimeOut  DriveTimeOutSTR;

enum enumAUTO_TIMEOUT {
	AUTO_TIMEOUT_MOVE_TRAV_LIFT = 0,
	AUTO_TIMEOUT_MOVE_FORK_OUT,
	AUTO_TIMEOUT_MOVE_FORK_OUT_LIFT,
	AUTO_TIMEOUT_MOVE_FORK_CENTER,
	AUTO_TIMEOUT_WAIT_INTERLOCK,
	AUTO_TIMEOUT_DETECT_GOODS,
	AUTO_TIMEOUT_SPARE6,
	AUTO_TIMEOUT_SPARE7,
	AUTO_TIMEOUT_SPARE8,
	AUTO_TIMEOUT_SPARE9,
	AUTO_TIMEOUT_SPARE10,
	AUTO_TIMEOUT_SPARE11,
	AUTO_TIMEOUT_SPARE12,
	AUTO_TIMEOUT_SPARE13,
	AUTO_TIMEOUT_SPARE14,
	AUTO_TIMEOUT_SPARE15,
	AUTO_TIMEOUT_SPARE16,
	AUTO_TIMEOUT_SPARE17,
	AUTO_TIMEOUT_SPARE18,
	AUTO_TIMEOUT_SPARE19,
	MAX_AUTO_TIMEOUT_CNT
};

struct __attribute__((__packed__)) tagAutoTimeOut
{
	/*
	INT16U Move;
	INT16U Fork_Out;
	INT16U Fork_Out_Lift;
	INT16U Fork_Center;
	INT16U St_Interlock_Wait;
	INT16U Reserved[15];
	*/
	INT16U mSetValue[MAX_AUTO_TIMEOUT_CNT];
};
typedef struct tagAutoTimeOut  AutoTimeOutSTR;

struct __attribute__((__packed__)) tagFanControl
{
	INT16U OperTime;
	INT08U TempSensor_Install;
	INT08U Reserved[10];
};
typedef struct tagFanControl  FanControlSTR;

struct __attribute__((__packed__)) tagBuzzerControl
{
	INT16U Fault_OnTime;
	INT16U Warning_OnTime;
	INT16U AutoChange_OnTime;
	INT16U AutoChange_OffTime;
	INT08U AutoChange_Toggle_Cnt;
	INT08U Reserved[10];
};
typedef struct tagBuzzerControl  BuzzerControlSTR;

struct __attribute__((__packed__)) tagTwinForkSet
{
	INT16U Distance_between_Fork;
	INT08U Reserved[20];
};
typedef struct tagTwinForkSet  TwinForkSetSTR;

struct __attribute__((__packed__)) tagUpperBrakeSet
{
	INT16U Operation_Count;
	INT16U ON_Time;
	INT16U OFF_Time;
	INT08U Reserved[10];
};
typedef struct tagUpperBrakeSet  UpperBrakeSetupSTR;

struct __attribute__((__packed__)) tagStabilzation_TimeSet
{
	INT08U Time;
	INT08U StartLevel;
	INT08U EndLevel;
};
typedef struct tagStabilzation_TimeSet  Stabilzation_TimeSetSTR;

struct __attribute__((__packed__)) tagStabilzationTime_Param
{
	INT08U CaseCount;
	Stabilzation_TimeSetSTR mSetting[10];
};
typedef struct tagStabilzationTime_Param  StabilzationTimeSTR;

struct __attribute__((__packed__)) tagParamControlCom
{
	INT08U				SafetyPlug_Type;						// 0: Start off, 1: Emergency stop
	INT08U				DoorSensor_UseFlag;						// 0: not use, 1: use
	INT08U				DoorSensor_AlarmFlag;					// 0: not use, 1: use
	INT08U				LaserModem_AlarmFlag;					// 광모뎀 알람 설정.
	INT08U				AutoChange_Mode;						// 자동모드 전환 조건.
	INT08U				TravLift_OperTime_SyncFlag;
	INT08U				HomeReturn_Fault_UseFlag;
	INT08U				ForkOut_Fault_Flag;				// 포크 동작중 이탈센서 알람 설정.
	INT08U				Station_DSTLR_Fault_Flag;
	INT08U				Auto_ForkOut_Interlock_Fault;
	INT08U				Man_ForkOut_Interlock_Fault;
	INT08U				ForkOut_LT_BrakeOn_Flag;
	INT16U				Fork_Auto_Home_Count;
	INT08U				Reserved0[40];

	RetryInPositonSTR	InPositon[3];
	DelayTimeSTR		Loading_Delay;
	DelayTimeSTR		Unloading_Delay;
	INT16U				Fork_Origin_DelayTime;
	INT08U				Reserved1[20];

	SetupTimeOutSTR		SetupTimeOut;
	DriveTimeOutSTR		DrvTimeout;
	AutoTimeOutSTR		AutoTimeout;

	INT16U				ForceMode_ReleaseTime;
	FanControlSTR		FanControl;
	BuzzerControlSTR	BuzzerCtr;
	UpperBrakeSetupSTR	UpperBrake;

	INT08U				Auto_Fork_Pos_Sensor_Fault;

	StabilzationTimeSTR CarrigeStabilzationSet;

	//INT08U				Reserved2[651];
	//INT08U				Reserved2[682];
};
typedef struct tagParamControlCom  ParamControlComSTR;

struct __attribute__((__packed__)) tagParamControl
{
	INT08U				SafetyPlug_Type;						// 0: Start off, 1: Emergency stop
	INT08U				DoorSensor_UseFlag;						// 0: not use, 1: use
	INT08U				DoorSensor_AlarmFlag;					// 0: not use, 1: use
	INT08U				LaserModem_AlarmFlag;					// 광모뎀 알람 설정.
	INT08U				AutoChange_Mode;						// 자동모드 전환 조건.
	INT08U				TravLift_OperTime_SyncFlag;
	INT08U				HomeReturn_Fault_UseFlag;
	INT08U				ForkOut_cargo_misalignment_alarm;						// 포크 동작중 이탈센서 알람 설정.
	INT08U				Station_DSTLR_Fault_Flag;				// Not use
	INT08U				Auto_ForkOut_Interlock_Fault;			// 스테이션 인터록 이상 알람 설정
	INT08U				Man_ForkOut_Interlock_Fault;			// 포크 수동동작 스테이션 인터록 확인 설정
	INT08U				ForkOut_LT_BrakeOn_Flag;
	INT16U				Fork_Auto_Home_Count;
	INT08U				Reserved0[40];

	RetryInPositonSTR	InPositon[3];
	DelayTimeSTR		Loading_Delay;
	DelayTimeSTR		Unloading_Delay;
	INT16U				Fork_Origin_DelayTime;
	INT08U				Reserved1[20];

	SetupTimeOutSTR		SetupTimeOut;
	DriveTimeOutSTR		DrvTimeout;
	AutoTimeOutSTR		AutoTimeout;

	INT16U				ForceMode_ReleaseTime;
	FanControlSTR		FanControl;
	BuzzerControlSTR	BuzzerCtr;
	UpperBrakeSetupSTR	UpperBrake;

	INT08U				Auto_Fork_Pos_Sensor_Fault;

	StabilzationTimeSTR Stabilzation_TimeSet;

	INT08U				Reserved2[651];
	//INT08U				Reserved2[682];
};
typedef struct tagParamControl  ParamControlSTR;

struct __attribute__((__packed__)) tagTravManualDrive
{
	INT16S Torque_Alarm;
	INT32S StartPos;
	INT32S EndPos;
	INT08U Reserved[20];
};
typedef struct tagTravManualDrive  TravManualDriveSTR;


struct __attribute__((__packed__)) tagSoftLimitError
{
	INT08U CheckFlag;
	INT32S HomePos;
	INT32S EndPos;
};
typedef struct tagSoftLimitError  SoftLimitErrorSTR;

struct __attribute__((__packed__)) tagSoftDecelError
{
	INT08U CheckFlag;
	INT16U ErrorOffset;
	INT32S Braking_Distance_Auto_H_Decel;
	INT32S Braking_Distance_Auto_M_Decel;
	INT32S Braking_Distance_Auto_H_Emg;
	INT32S Braking_Distance_Auto_M_Emg;
};
typedef struct tagSoftDecelError  SoftDecelErrorSTR;

struct __attribute__((__packed__)) tagOriginDogError
{
	INT08U CheckFlag;
	INT16U ErrorOffset;
	INT32S HomePos1;
	INT32S Reseved0;
	INT32S EndPos1;
	INT32S Reseved1;
};
typedef struct tagOriginDogError  OriginDogErrorSTR;

struct __attribute__((__packed__)) tagDecelationDogError
{
	INT08U CheckFlag;
	INT16U Offset;
	INT32S Fwd1_Pos1;
	INT32S Fwd1_Pos2;
	INT32S Fwd2_Pos1;
	INT32S Reseved0;
	INT32S Rvr1_Pos1;
	INT32S Rvr1_Pos2;
	INT32S Rvr2_Pos1;
	INT32S Reseved1;
};
typedef struct tagDecelationDogError  DecelationDogErrorSTR;

struct __attribute__((__packed__)) tagInvertorParam
{
	INT32S RefOffset;
	INT32U PosGain;
	INT08U PosWindow;
	INT08U UseFlag;
};
typedef struct tagInvertorParam  InvertorParam;

// 외부 플래시 저장 구조체
struct __attribute__((__packed__)) tagParamTravelDrive
{
	UnitVelocitySTR			Vel[MAX_TRAV_VELOCITY_CNT];
	INT08U					InPos_Tolerance;
	INT08U					InPos_Hysteresis;
	TravManualDriveSTR		ManualDrive;
	INT16U					BrakeOnDelayTime;
	INT32S					Reserved2;
	INT08U					Home_Spd_Mode;
	INT08U					Home_Pos_StationNo;
	INT08U					Home_Pos_BayNo;
	INT08U					Reserved1[2];
	INT08U					Maintenance_Spd_Mode;
	INT32S					Maintenance_Pos;
	INT08U					DecelRange1_Mode;
	INT08U					DecelRange2_Mode;
	SoftLimitErrorSTR		SoftLimitErr;
	SoftDecelErrorSTR		SoftDecelErr;
	OriginDogErrorSTR		OriginDogErr;
	DecelationDogErrorSTR	DecelDogErr;
	InvertorParam			InvParam;

	INT08U Reserved[748];
};
typedef struct tagParamTravelDrive  ParamTravelDriveSTR;

// Vexi 통신 구조체
struct __attribute__((__packed__)) tagParamTravelDriveCom
{
	UnitVelocitySTR			Vel[MAX_TRAV_VELOCITY_CNT];
	INT08U					InPos_Tolerance;
	INT08U					InPos_Hysteresis;
	TravManualDriveSTR		ManualDrive;
	INT16U					BrakeOnDelayTime;
	INT32S					Reserved2;
	INT08U					Home_Spd_Mode;
	INT08U					Home_Pos_StationNo;
	INT08U					Home_Pos_BayNo;
	INT08U					Reserved1[2];
	INT08U					Maintenance_Spd_Mode;
	INT32S					Maintenance_Pos;
	INT08U					DecelRange1_Mode;
	INT08U					DecelRange2_Mode;
	SoftLimitErrorSTR		SoftLimitErr;
	SoftDecelErrorSTR		SoftDecelErr;
	OriginDogErrorSTR		OriginDogErr;
	DecelationDogErrorSTR	DecelDogErr;
	InvertorParam			InvParam;
};
typedef struct tagParamTravelDriveCom  ParamTravelDriveComSTR;

struct __attribute__((__packed__)) tagLiftManualDrive
{
	INT16U Torque_Alarm;
	INT32S StartPos;
	INT32S EndPos;
	INT08U Reserved[20];
};
typedef struct tagLiftManualDrive  LiftManualDriveSTR;

struct __attribute__((__packed__)) tagForkOutLiftJerkSetup
{
	INT08U	Jerk_Mode;
	INT16U	Normal_Jerk;
	INT16U	Setup_Jerk;
	INT16U	Turning_Jerk;
};
typedef struct tagForkOutLiftJerkSetup  ForkOutLiftJerkSetupSTR;

struct __attribute__((__packed__)) tagParamLiftDrive
{
	UnitVelocitySTR			Vel[MAX_LIFT_VELOCITY_CNT];
	INT08U					InPos_Tolerance;
	INT08U					InPos_Hysteresis;
	LiftManualDriveSTR		ManualDrive;
	INT16U					BrakeOnDelayTime;
	INT32S					Origin_Pos;
	INT08U					Home_Spd_Mode;
	INT32S					Home_Pos;
	INT08U					Maintenance_Spd_Mode;
	INT32S					Maintenance_Pos;
	INT08U					DecelRange1_Mode;
	INT08U					DecelRange2_Mode;
	SoftLimitErrorSTR		SoftLimitErr;
	SoftDecelErrorSTR		SoftDecelErr;
	OriginDogErrorSTR		OriginDogErr;
	DecelationDogErrorSTR	DecelDogErr;
	ForkOutLiftJerkSetupSTR ForkOut_LiftJerkSet;
	InvertorParam			InvParam;
	INT08U					LevelUpOffset;
	INT08S					LevelDnOffset;
	INT08U					Veriant_LT_Offset;

	//INT08U Reserved[742];
	//INT08U Reserved[739];
	INT08U Reserved[738];
};
typedef struct tagParamLiftDrive  ParamLiftDriveSTR;

struct __attribute__((__packed__)) tagParamLiftDriveCom
{
	UnitVelocitySTR			Vel[MAX_LIFT_VELOCITY_CNT];
	INT08U					InPos_Tolerance;
	INT08U					InPos_Hysteresis;
	LiftManualDriveSTR		ManualDrive;
	INT16U					BrakeOnDelayTime;
	INT32S					Origin_Pos;
	INT08U					Home_Spd_Mode;
	INT32S					Home_Pos;
	INT08U					Maintenance_Spd_Mode;
	INT32S					Maintenance_Pos;
	INT08U					DecelRange1_Mode;
	INT08U					DecelRange2_Mode;
	SoftLimitErrorSTR		SoftLimitErr;
	SoftDecelErrorSTR		SoftDecelErr;
	OriginDogErrorSTR		OriginDogErr;
	DecelationDogErrorSTR	DecelDogErr;
	ForkOutLiftJerkSetupSTR ForkOut_LiftJerkSet;
	InvertorParam			InvParam;
	INT08S					LevelUpOffset;
	INT08S					LevelDnOffset;
	INT08U					Veriant_LT_Offset;
};
typedef struct tagParamLiftDriveCom  ParamLiftDriveComSTR;

struct __attribute__((__packed__)) tagForkManualDrive
{
	INT16U Torque_Alarm;
	INT32S LeftPos;
	INT32S RightPos;
	INT08U Creep_Offset;
	INT08U ControlDir;		// 0:CW, 1:CCW
	INT08U Reserved[19];
	//INT08U Reserved[20];
};
typedef struct tagForkManualDrive  ForkManualDriveSTR;

struct __attribute__((__packed__)) tagForkEncoderSetup
{
	INT08U	Dir;
	INT08U	Input_Pulse;
	INT32U	Preset_Count;
	INT32U	Pulse_Distance;
};
typedef struct tagForkEncoderSetup  ForkEncoderSetupSTR;

enum enumFORK_DECELATION_SETUP {
	NO_LOADED_MOVE_CENTER_TO_FEL = 0,
	NO_LOADED_MOVE_FEL_TO_CENTER,
	NO_LOADED_MOVE_CENTER_TO_FER,
	NO_LOADED_MOVE_FER_TO_CENTER,
	NO_LOADED_MOVE_CENTER_TO_FML,
	NO_LOADED_MOVE_FML_TO_CENTER,
	NO_LOADED_MOVE_CENTER_TO_FMR,
	NO_LOADED_MOVE_FMR_TO_CENTER,
	NO_LOADED_MOVE_CENTER_TO_FHL,
	NO_LOADED_MOVE_FHL_TO_CENTER,
	NO_LOADED_MOVE_CENTER_TO_FHR,
	NO_LOADED_MOVE_FHR_TO_CENTER,
	LOADED_MOVE_CENTER_TO_FEL,
	LOADED_MOVE_FEL_TO_CENTER,
	LOADED_MOVE_CENTER_TO_FER,
	LOADED_MOVE_FER_TO_CENTER,
	LOADED_MOVE_CENTER_TO_FML,
	LOADED_MOVE_FML_TO_CENTER,
	LOADED_MOVE_CENTER_TO_FMR,
	LOADED_MOVE_FMR_TO_CENTER,
	LOADED_MOVE_CENTER_TO_FHL,
	LOADED_MOVE_FHL_TO_CENTER,
	LOADED_MOVE_CENTER_TO_FHR,
	LOADED_MOVE_FHR_TO_CENTER,
	MAX_FORK_DECELATION_SETUP
};

struct __attribute__((__packed__)) tagAutoForkDecelCtrSetup
{
	INT08U	UseFlag;
	INT16S	Position[MAX_FORK_DECELATION_SETUP];
};
typedef struct tagAutoForkDecelCtrSetup  AutoForkDecelCtrSetupSTR;

struct __attribute__((__packed__)) tagTwinForkSetup
{
	INT16U	Between_Distance;
	INT08U	Reserved[20];
};
typedef struct tagTwinForkSetup  TwinForkSetupSTR;

struct tagForkPosSensorSetup_Bit
{
	//INT08U mFCR : 1;	// Bit0, 
	//INT08U mFCL : 1;	// Bit1, 
	INT08U mFCL_FCR : 2;
	INT08U mFHL : 1;	// Bit2,
	INT08U mFML : 1;	// Bit3,
	INT08U mFEL : 1;	// Bit4,
	INT08U mFHR : 1;	// Bit5,
	INT08U mFMR : 1;	// Bit6,
	INT08U mFER : 1;	// Bit7,
};
typedef struct tagForkPosSensorSetup_Bit  ForkPosSensorSetup_Bit_T;

struct __attribute__((__packed__)) tagForkPosSensorSetup_D
{
	union
	{
		ForkPosSensorSetup_Bit_T Bit;
		INT08U			D;
	};
};
typedef struct tagForkPosSensorSetup_D  ForkPosSensorSetup_D;

struct __attribute__((__packed__)) tagForkPosSensorSetup
{
	ForkPosSensorSetup_D	Setting;

	INT08U	Reserved[2];
};
typedef struct tagForkPosSensorSetup  ForkPosSensorSTR;

struct __attribute__((__packed__)) tagForkPosDepthSetup
{
	INT16S	mFHL;
	INT16S	mFML;
	INT16S	mFEL;
	INT16S	mFHR;
	INT16S	mFMR;
	INT16S	mFER;
};
typedef struct tagForkPosDepthSetup  ForkPosDepthSTR;

struct __attribute__((__packed__)) tagParamForkDrive
{
	UnitVelocitySTR				Vel[MAX_FORK_VELOCITY_CNT];
	INT08U						InPos_Tolerance;
	INT08U						InPos_Hysteresis;
	ForkManualDriveSTR			ManualDrive;
	ForkEncoderSetupSTR			EncoderSetup;

	INT08S						OriginOffset_FCL;
	INT08S						OriginOffset_FCR;
	INT08U						OriginSensor;
	INT08U						Reserved0;
	
	AutoForkDecelCtrSetupSTR	ForkDecelCtr;
	TwinForkSetupSTR			TwinForkSetup;
	ForkPosSensorSTR			PosSensorUse;
	ForkPosDepthSTR				ForkPosDepth;
	InvertorParam				InvParam;

	//INT08U						Reserved[748];
	INT08U						Reserved1[747];
};
typedef struct tagParamForkDrive  ParamForkDriveSTR;

struct __attribute__((__packed__)) tagParamForkDriveCom
{
	UnitVelocitySTR				Vel[MAX_FORK_VELOCITY_CNT];
	INT08U						InPos_Tolerance;
	INT08U						InPos_Hysteresis;
	ForkManualDriveSTR			ManualDrive;
	ForkEncoderSetupSTR			EncoderSetup;
	INT08S						OriginOffset_FCL;
	INT08S						OriginOffset_FCR;
	INT08U						OriginSensor;
	INT08U						Reserved0;
	AutoForkDecelCtrSetupSTR	ForkDecelCtr;
	TwinForkSetupSTR			TwinForkSetup;
	ForkPosSensorSTR			PosSensorUse;
	ForkPosDepthSTR				ForkPosDepth;
	InvertorParam				InvParam;
};
typedef struct tagParamForkDriveCom  ParamForkDriveComSTR;

/*******************************************************************************/
/* BackupSRAM */
/*******************************************************************************/
// MAX Size : 4K(4096) bytes.
struct __attribute__((__packed__)) tagBKSRam
{
	// 장치별 메모리 시작 영역 : 3993bytes
	AlarmLogSTR			AlarmLog;				// 2454 bytes
#if DEF_ALARM_LOG_TYPE == 1 
	INT08U				Reseved1[1485];
#elif DEF_ALARM_LOG_TYPE == 2
	INT08U				Reseved1[785];
#endif

	INT08U				InitOperInfoCode[4];	// "Oper"
	OperationInfoSTR	OperationInfo;

	SaveWorkSTR			WorkInfo;				// 108

	INT08U				Graph_Type;				//	그래프 기록 타입
	INT08U				Graph_Interval;			//	Graph saving interval
	INT32U				Graph_Start_mm;			//	Graph saving position mm

	INT08U				Reseved2[36];
	// 장치별 메모리 영역 끝

	// 공통 메모리 영역 시작, Size 103bytes
	INT08U				BootPgmVer[4];
	INT08U				Reset_Reason;

	INT08U				InitDeviceCode[4];		// "Devi"
	DeviceSetting		mDevice;				// Size: 93 bytes

	INT08U				Reserved_Fix;			// 
	// 공통 메모리 영역 끝
};
typedef struct tagBKSRam  BKSRamSTR;

struct __attribute__((__packed__)) tagDownloadInfo
{
	ExecFileSTR  APP_ExecFile;
	ExecFileSTR  Buf_ExecFile;
};
typedef struct tagDownloadInfo  DownloadInfo_t;

/*******************************************************************************/
/* External Flash */
/*******************************************************************************/
// MAX Size : 4K(4096) bytes.
struct __attribute__((__packed__)) tagExtFlash
{
	INT08U				DebugMode;

	DownloadInfo_t		FW_Info;

	INT08U				InitDeviceCode[4];		// "Devi"
	DeviceSetting		mDevice;				// Size: 63 bytes
	INT16U				CheckCRC_Device;

	INT08U				InitMachineCode[4];		// "Mach"
	SRM_Machine_Type	Machine;				// Size: 39 bytes
	INT16U				CheckCRC_MachineType;

	INT08U				InitDIOCode[4];			// "DioS", Digital IO Set
	DIO_SetSTR			DIO_Set;				// Size: 1006 bytes
	INT16U				CheckCRC_DIO_Set;

	INT08U				Reserved[2833];
};
typedef struct tagExtFlash  ExtFlashSEnv;

// MAX Size : 4K(4096) bytes.
struct __attribute__((__packed__)) tagExtFlash0
{
	INT08U				InitCellOffsetCode[4];	// "Offs", 
	INT16U				CheckCRC_CellOffset;

	INT08U				InitRackCode[4];		// "Rack", 
	RackConfigSTR		RackConfig;				// Size: 217 bytes
	INT16U				CheckCRC_RackConfig;

	INT08U				InitCellCode[4];		// "Cell", 
	CellConfigSTR		CellConfig_Left;		// Size: 1536 bytes
	CellConfigSTR		CellConfig_Right;		// Size: 1536 bytes
	INT16U				CheckCRC_CellData;

	INT08U				Reserved[789];
};
typedef struct tagExtFlash0  ExtFlashSEnv0;

// MAX Size : 4K(4096) bytes.
struct __attribute__((__packed__)) tagExtFlash1
{
	INT08U				InitProhibitCode[4];		// 
	ProhibitRackSTR		ProhibitRack;			// Size : 1018 Bytes
	INT16U				CRC_ProhibitRack;		// Total : 1024( data(1018) + init(4) + crc(2))

	INT08U				InitSpecialCode[4];		// 
	SpecialRackSTR		SpecialRack;			// Data Size : 1018 Bytes
	INT16U				CRC_SpecialRack;		// Total : 1024( data(1018) + init(4) + crc(2))

	INT08U				InitStationCode[4];		// 
	StationSetupSTR		StationEnv;				// Data Size : 1018 bytes
	INT16U				CRC_StationSet;			// Total : 1024( data(1018) + init(4) + crc(2))

	INT08U				Reserved[1024];
};
typedef struct tagExtFlash1  ExtFlashSEnv1;

// MAX Size : 4K(4096) bytes.
struct __attribute__((__packed__)) tagExtFlash2
{
	INT08U				InitControlCode[4];		// 재어 설정 초기화 코드
	ParamControlSTR		CtrParam;
	INT16U				CRC_Control;

	INT08U				InitTravelDriveCode[4];	// 주행 설정 초기화 코드
	ParamTravelDriveSTR TravDrive;				// 주행 설정
	INT16U				CRC_TravelDrive;		// 주행 설정 CRC

	INT08U				InitLiftDriveCode[4];	//
	ParamLiftDriveSTR	LiftDrive;
	INT16U				CRC_LiftDrive;

	INT08U				InitForkDriveCode[4];	//
	ParamForkDriveSTR	ForkDrive;
	INT16U				CRC_ForkDrive;
};
typedef struct tagExtFlash2  ExtFlashSEnv2;

struct __attribute__((__packed__)) tagScurveProfile
{
	// 0 : 구동프로파일 없음
	// 1 : 가속/등속/감속 구동프로파일 생성  가속/등속/감속 PID적용
	// 2 : 가속/등속 구동프로파일 생성     PID 미적용   가속후 등속계속유지
	// 3 : 감속/등속 구동프로파일 생성     PID 미적용   감속후 등속계속유지
	// 4 : 감속 구동프로파일 생성        PID 적용     감속후 목표위치도달시 정지
	INT08U control;
	INT08U vel_type;

	INT08S ward;          // 1:전진, -1:후진
	INT08U mode;
	INT32U index;

	INT32U start_timer;

	INT16S start_velocity;
	INT16S creep_velocity;
	INT16S target_velocity;

	INT32S StartPos;
	INT32S TargetPos;
	INT32S Move_Distance;

	double max_velocity;
	double acc;
	double dec;
	double acc_jerk;
	double dec_jerk;

	double acc_jerk_time;
	double dec_jerk_time;
	double acc_linear_time;
	double dec_linear_time;
	double constant_time;

	// 0 : 시작속도               
	// 1 : 저크종료속도         
	// 2 : 가속종료속도         
	// 3 : 저크종료속도(등속속도) 
	// 4 : 등속종료속도(등속속도) 
	// 5 : 저크종료속도           
	// 6 : 감속종료속도           
	// 7 : 저크종료속도(크립속도) 
	// 8 : 크립종료속도
	double v[9];
	double s[9];
	double t[9];

	INT32S Cmd_postion;
	INT32S Cmd_velocity;
};
typedef struct tagScurveProfile  ScurveProfileSTR;

struct __attribute__((__packed__)) tagProfileControl
{
	INT32S			remain_distance;
	INT32S			dec_distance;

	INT08U			Target_Reach;

	INT32S			Oper_Time[8];
	INT32S			Oper_Timeout[8];
	INT32S			OperateTime;		// 프로파일 계산 주행시간

	INT32S			Lag_Diff_Value;

	ScurveProfileSTR	CTR;
};
typedef struct tagProfileControl  ProfileControl;

struct __attribute__((__packed__)) tagInvParamData
{
	INT08U			Drive;		// 1: Trav, 2: Lift, 3:Fork1
	INT16U			Main_Addr;
	INT16U			Sub_Addr;
	INT32S			Data;
};
typedef struct tagInvParamData  InvParamData_t;

struct __attribute__((__packed__)) tagInvParamCom
{
	INT08U			RecvComPort;
	ComHeaderSTR	RecvHeader;

	INT08U			Mode;		// 1: Read, 2: Write

	InvParamData_t	rData;
	InvParamData_t	wData;
};
typedef struct tagInvParamCom  InvParamCom_t;

enum enumDI_TEST_MODE {
	DI_TEST_NONE = 0,
	DI_TEST_DSTx,
	DI_TEST_ODSTx,
	DI_TEST_INTERLOCK,
	DI_TEST_EM,
	DI_TEST_LIMIT,
};

struct __attribute__((__packed__)) tagMOVIKIT_MAC_Control2_Test
{
	INT16U Disable_Member1 : 1;							// Bit0, 1踰� 硫ㅻ� MAC 鍮����깊��
	INT16U Disable_Member2 : 1;							// Bit1, 2踰� 硫ㅻ� MAC 鍮����깊��
	INT16U Disable_Member3 : 1;							// Bit2, 3踰� 硫ㅻ� MAC 鍮����깊��
	INT16U Disable_Member4 : 1;							// Bit3, 4踰� 硫ㅻ� MAC 鍮����깊��
	INT16U Release_brake_without_enable_member1 : 1;	// Bit4, 1踰� 硫ㅻ� 媛��� 釉����댄�� �댁��
	INT16U Release_brake_without_enable_member2 : 1;	// Bit5, 2踰� 硫ㅻ� 媛��� 釉����댄�� �댁��
	INT16U Release_brake_without_enable_member3 : 1;	// Bit6, 3踰� 硫ㅻ� 媛��� 釉����댄�� �댁��
	INT16U Release_brake_without_enable_member4 : 1;	// Bit7, 4踰� 硫ㅻ� 媛��� 釉����댄�� �댁��
	INT16U Deactivate_balance_controller : 1;			// Bit8, 諛몃�곗�� ���� 鍮����깊��
	INT16U Disable_position_controller : 1;				// Bit9, �ъ��� 而⑦�몃· 鍮����깊��
	INT16U Disable_Skew_error : 1;						// Bit10, Skew ���� 鍮����깊��
	INT16U Allow_skew_compensation : 1;					// Bit11, Skewing 湲곗�멸린 洹��� ���깊��
	INT16U Reset_encoder_difference : 1;				// Bit12, ��肄��� 媛� �ㅼ감 由ъ��
	INT16U Deactivate_external_encoders : 1;			// Bit13, �몃� ��肄��� 鍮����깊��
	INT16U Reserved_14 : 1;								// Bit14,
	INT16U Reserved_15 : 1;								// Bit15,
};
typedef struct tagMOVIKIT_MAC_Control2_Test  MOVKIT_MAC_Control2_STR_Test;

typedef union
{
	INT16U W;
	MOVKIT_MAC_Control2_STR_Test B;
}SyncTravel_test;

struct __attribute__((__packed__)) tagTestSimulator
{
	DriveStatus		Test_InvSt[4];

	INT32U			Auto_Release_Timer;

	INT08U			GCP_Change_Mode_Disable;

	INT08U			Goods_State_Mode;

	INT08U			DI_Test_Mode;
	INT08U			DI_Test_State;

// 	INT08U			DSTx_Test_Mode;				// 이중입고 테스트
// 	INT08U			DSTx_Test_State;

// 	INT08U			ODSTx_Test_Mode;			// 출고화물 테스트
// 	INT08U			ODSTx_Test_State;

// 	INT08U			InterLock_Test_Mode;		// 인터락 테스트
// 	INT08U			InterLock_Test_State;

	INT08U			Test_Manual_Mode;			// 기상반 모드 테스트
	INT08U			Test_Manual_Mode_Ctr;

	INT08U			HMI_Test_Mode;				// 인터락 테스트
	INT08U			HMI_Test_Fork1_Left_Pos;
	INT08U			HMI_Test_Fork1_Right_Pos;
	INT16U			HMI_Test_ManualKey;
	INT32U			HMI_Test_EventKey;

// 	INT08U			EM_Test_Mode;			// 비상정지 입력
// 	INT08U			EM_Test_State;

	INT16U			SRM_RunMode_Step;
	INT08U			SRM_Work_Index;

	INT08U				Test_Sync_Travel_Enable;
	SyncTravel_test		Test_Sync_Travel_Control;

	INT08U		Test_Fault_Warning;
	INT08U		Test_Fault_MainCode;
	INT08U		Test_Fault_SubCode;

	INT08U		Clear_OperationInfo;

	INT08U		HMI_Set_Flag;
};
typedef struct tagTestSimulator  Test_Simulator_t;

struct __attribute__((__packed__)) tagPGMEnv
{
	//INT16U       FlashSize;

	INT08U       programRun;    // 0x01:Boot Program, 0x02:Downlog Program

	INT32U       timer100us;
	INT32U       timer1ms;

	DownloadInfo_t	Fw_Info;

	INT08U       downloadMode;
	INT32U       downloadTimer;

	INT08U			Download_port;
	ComHeaderSTR	Download_Header;
	INT32U			DownloadSize;

	INT08U			System_Reset_Flag;

	// 	INT16U       txUsbComLen;
	// 	INT08U       txUsbComBuffer[FRAME_MAX_DATA_LEN];

	// 	INT08U       EthUdpDstIP[4];
	// 	INT16U       EthUdpDstPort;

	INT16U       txEthUdpComLen;
	INT08U       txEthUdpComBuffer[FRAME_MAX_DATA_LEN];

	// 	INT16U       txEthTcpComLen;
	// 	INT08U       txEthTcpComBuffer[FRAME_MAX_DATA_LEN];

	// 	INT08U       InvUdpDstIP[4];
	// 	INT16U       InvUdpDstPort;

	INT16U       txInvUdpComLen;
	INT08U       txInvUdpComBuffer[FRAME_MAX_DATA_LEN];

	// 	INT16U       txInvTcpComLen;
	// 	INT08U       txInvTcpComBuffer[FRAME_MAX_DATA_LEN];

	INT08U       DSPUdpDstIP[4];
	INT16U       DSPUdpDstPort;
	INT16U       txDSPComLen;
	INT08U       txDSPComBuffer[FRAME_DSP_DATA_LEN];

	INT08U       TmlConnect;
	INT32U       TmlConnectTimer;

	INT08U       UPLink;
	INT08U       UPLinkInitFlag;
	INT08U       UDPConnect;
	INT32U       UDPConnectTimer;

	INT08U       DSP_Connect;
	INT32U       DSP_ConnectTimer;

	INT08U       DownLink;
	INT08U       DownLinkInitFlag;

	INT16U		CellOffsetUseCount;
	INT08U		CellOffsetUseFlag[4096];

	INT08U		DeviceType;
	INT08U		DeviceID;

	//INT16U       TestValue;

	INT08U       DOSt;
	INT08U       DISt;
	INT32U       InputFilterTime[8];

	INT08U       DeviceHwMode;

	INT08U       SignalLamp;    // 0:Off, 1:RED, 2:GRN, 3:BLU
	INT08U       Buzzer;        // 0:Off, 1:On

	INT08U		 EtherCAT_Connection;

	INT32U		EtherCAT_DelayCount;
	INT32U		EtherCAT_MaxDelayCount;
	INT32U		EtherCAT_TimeOutCount;

	INT16U       PosSeqCnt_X_Left;
	INT32S       PosSeq_X_Left[310];

	INT16U       PosSeqCnt_Y_Left;
	INT32S       PosSeq_Y_Left[180];

	INT16U       PosSeqCnt_X_Right;
	INT32S       PosSeq_X_Right[310];

	INT16U       PosSeqCnt_Y_Right;
	INT32S       PosSeq_Y_Right[180];

	INT08U		Station_Point_L[10][4];
	INT08U		Station_Point_R[10][4];

// 	INT16S       Pos_X;
// 	INT16S       Pos_Y;

	INT16S       Pos_X_Left;
	INT16S       Pos_Y_Left;

	INT16S       Pos_X_Right;
	INT16S       Pos_Y_Right;

	INT16S       InPos_Start_X_Left;
	INT16S       InPos_End_X_Left;
	INT16S       InPos_Start_Y_Left;
	INT16S       InPos_End_Y_Left;

	INT16S       InPos_Start_X_Right;
	INT16S       InPos_End_X_Right;
	INT16S       InPos_Start_Y_Right;
	INT16S       InPos_End_Y_Right;

	INT16U		SRM_RunMode;
	INT32U		SRM_RunTimer;

	INT16U		SRM_TaskMode;
	INT16U		SRM_TaskIndex;

	//INT08S       TravWard;      //

	INT32S       GraphData[16];

	INT16U       ManualHmiCtrl[20];
	INT32U       ManualHmiTimer;

	INT32U       ServerLink;
	INT32U       ServerPeriodicTimer;

	INT08U       PortLinkSt[20];
	INT32U       PortLinkTimer[20];

	//INT32U       InvertorBrakeTimer[3];

	INT32U       TravBrakeTimer;
	INT32U       LiftBrakeTimer;

	INT16U       OrderRejectCondition;

	INT08U       NowTravIhbOut;
	INT08U       NowLiftIhbOut;

	INT08U       RemoconConnect;
	INT32U       RemoconTimer;

	INT08U       FlashUartDisable;

	INT08U       FpgaNetReadInx;
	INT08U       FpgaNetRecvInx;

	INT08U       FpgaCatReadInx;
	INT08U       FpgaCatRecvInx;

	INT08U       isFpgaRun;

	//                POS    JOG
	// TRAV #1        11     16
	// LIFT #1        21     26
	// LIFT #2        22     27
	// LIFT ALL       20     25
	// FORK/FEED #1   31     36
	// FORK/FEED #2   32     37
	// FORK WIDTH #1  41     46
	// FORK WIDTH #2  42     4700
	INT08U       ManualCtrlMode;
	INT32U       ManCtrTimeover;

	//INT08U       ForkCtrlPossible[2];
	//INT08U       CtrlPlcNo;

	INT08U       StartOnChange;
	INT32U       StartOnChangeTimer;

	INT32U		SysTime_1ms;

	INT08U		SFlash_Install;

	INT16U		EtherCAT_DO[10];

	INT08U		NormalStopFlag;
	INT08U		EmergencyStopFlag;
	INT08U		ForceForkStopFlag;

	INT16U		Invertor_RxPDO_Size;
	INT16U		Invertor_TxPDO_Size;
	INT16U		Invertor_Com_Start;

	INT32U		Invertor_ComTimeOver;

	INT08U		JogFlag[3];

	INT08U		Fork_ReferenceSet;

	INT08U		SRM_Machine_State;
	INT08U		SRM_Complete_Machine_State;

	INT08U		MX_DSP_ProtocolVer;
	INT08U		MX_DSP_PgmVer[4];

	INT08U		MX_DSP_Remocon[2];

	INT08U		Encoder_ComErr_Setting;
	INT08U		Encoder_ComDC_Setting;

	INT08U		Encoder_Dir_Setting;
	INT08U		Encoder_Input_Setting;

	INT08U		Read_Param_Flag;

	INT08U		Start_Off_Flag;

	ProfileControl	Profile[3];

	INT08U		Fork_Profile_Target_Reach;
	INT08U		Run_Fork_VelType;
	INT32S		ForkProfile_Time[8];
	INT32S		ForkProfile_Timeout[8];
	INT32S		Fork_OperateTime;		// 프로파일 계산 주행시간

	//INT08U		TravAdnormal_Flag;

	//INT08U		Shuttle_Goods_Exist;

	INT08U		Home_Lamp_Flag;		// 원점 동작시 램프 동작

	INT08U		Fork_Test_Mode;
	INT32S		Fork_Test_Position;

	INT08U		Alarm_LaserModem;

	INT08U		Alarm_DoorOpen;

	INT08U		Check_Home_Flag;

	INT08U		Move_Home_Flag;

	INT08U		Move_Maintanence_Flag;

	INT08U		Demo_Control;
	INT08U		Demo_Option;

	INT32U		StatusReqCount;

	INT08U		Fork_EmergencyStop;

	INT32U		Fork_Orgin_Operate_Auto;
	INT32U		Fork_Orgin_Index;

	INT08U		Move_PosFlag;
	INT08U		Manual_Fork_PositionFlag;

	INT08U		Machine_Init_Fail;

	INT32U		RemoconKey;

	INT08U       TravSSIError;
	INT08U       TravSSIRun;
	INT16U       BarcodeContinueError;

	INT08U		MCU_Test_Mode;

	InvParamCom_t	InvParamCtr;

	INT08U		Trial_Run_Mode;		// 시운전 모드

	INT08U		Limit_Run_Mode;		// 리미트 운전 모드

	INT32U		RecvModbusTCP_Time;

	INT08U		Bz_Force_Stop;

	INT08U		Debug_Fork_Control_Flag;
	INT08U		Debug_Fork_Control_NextStep;

	INT32S		Setup_Target_Pos[3];

	INT08U		Buzzer_OneShot;
	INT08U		Buzzer_Online;

	INT16S		MaxAcutalTouqe[3];

	INT08U		Test_Wirte_Flag;
	INT32U		Tset_ControlData[2];

	INT08U		Enable_Setup_Move_Position;		
	INT32U		Enable_Setup_Move_Position_Timer;

	INT16U		Project_Site_No;
	INT16U		Manual_Trav_Site_No;
	INT16U		Manual_Lift_Site_No;

	INT08U		Manual_SW_Change_Auto;		// 기상반 스위치 수동에서 자동으로 변경.

	INT08U		Fork_Encoder_Type;			//
	INT08U		Fork_Brake_Type;			// 0: SEW Brake Unit, 1:MC
	INT08U		Fork_Man_Control_Type;		// 0: Normal, 1:HKT TP2 GT

	INT08U		Station_Error_No;

	ControlPanelSTR		Recv_CP_State;

	Test_Simulator_t	Test_Simulator;

	INT08U		FOUT_Impossible_Reason_L;
	INT08U		FOUT_Impossible_Reason_R;

	INT32U		Clear_Warning_Timer;

	INT32U		Man_Travel_Low_Distance;
	INT32U		Man_Hoist_Low_Distance;

	INT08U		InterlockMode;

	INT08U		Travel_Limit_Flag;	// 1: 전진 리미트 감지, 2: 후진 리미트 감지
	INT08U		Hoist_Limit_Flag;	// 1: 하강 리미트 감지, 2: 상승 리미트 감지


	INT08U		FPGA_Reset_Flag;

	INT32S		Hoist_Max_Touqe;

	INT32U		RxStatus_Cnt;
	INT08U		RxStatus_Flag;
	INT32U		RxStatus_Timer;

	INT08U		GCP_Connect;

	INT08U		Set_HMI_SysTime_Flag;
	INT16U		Set_HMI_SysTime_Year;
	INT16U		Set_HMI_SysTime_Mon;
	INT16U		Set_HMI_SysTime_Day;
	INT16U		Set_HMI_SysTime_Hour;
	INT16U		Set_HMI_SysTime_Min;

	struct tm	SysTime;

	INT08U		Fork_IO_Manual_Control[2];

	INT08U		HMI_Com_Port;

	INT08U		TCPConnect;
	INT32U		TCPConnectTimer;
};
typedef struct tagPGMEnv  PGMEnvSTR;


struct __attribute__((__packed__)) tagMcuTestCtr
{
	INT08U RS232_Test;
	INT08U RS485_Test1;
	INT08U RS485_Test2;
	INT08U RS422_Test1;
	INT08U RS422_Test2;
	INT08U CAN_Test1;
	INT08U CAN_Test2;
	INT08U EtherNet_Test1;
	INT08U EtherNet_Test2;
	INT08U EtherCAT_Test;
	INT08U SSI_Test;
	INT08U Encoder_Test;
	INT32U PTO_Output;				// 제어 주파수 값
	INT08U DIO_Test;				//
	INT08U USB_Test;				//
	INT16U SSI_Freq_Cmd;			//
	INT08U All_Test_Result;			//
	INT16U Test_Complete_Code;		//
	INT16U Init_Parameter_Code;		//
	INT08U Reserved[20];
};
typedef struct tagMcuTestCtr  McuTestCtrSTR;

struct __attribute__((__packed__)) tagCanRecvData
{
	INT08U StdID;
	INT08U DLC;
	INT08U Value[8];
};
typedef struct tagCanRecvData  CanRecvData;

struct __attribute__((__packed__)) tagMcuTestStatus
{
	INT08U		ProtocolVer;
	INT08U		PgmVer[4];
	INT08U		FPGA_Connect;
	INT08U		ExtFlash_Connect;
	INT08U		FND_Display;
	INT08U		Mode_SW;
	INT08U		ID_SW;
	INT08U		RS232_Enable;
	INT08U		RS232_RecvCnt;
	INT08U		RS485_P1_Enable;
	INT08U		RS485_P1_RecvCnt;
	INT08U		RS485_P2_Enable;
	INT08U		RS485_P2_RecvCnt;
	INT08U		RS422_P1_Enable;
	INT08U		RS422_P1_RecvCnt;
	INT08U		RS422_P2_Enable;
	INT08U		RS422_P2_RecvCnt;
	INT08U		CAN1_Enable;
	INT08U		CAN1_RecvCnt;
	CanRecvData CAN1_Data;
	INT08U		CAN2_Enable;
	INT08U		CAN2_RecvCnt;
	CanRecvData CAN2_Data;
	INT08U		EtherNet1_Enable;
	INT08U		EtherNet1_RecvCnt;
	INT08U		EtherNet2_Enable;
	INT08U		EtherNet2_RecvCnt;
	INT08U		EtherCAT_Enable;
	INT08U		EtherCAT_Test;
	INT08U		EtherCAT_Wkc;
	INT08U		SSI_Enable;
	INT32U		SSI_Position;
	INT08U		Encoder_Enable;
	INT16S		Encoder_In;
	INT08U		PTO_Enable;
	INT32U		PTO_Output;
	INT08U		DIO_Test_Enable;
	INT08U		DOSt;
	INT08U		DISt;
	INT08U		USB_Test_Enable;
	INT08U		USB_Test;
	INT16U		SSI_Freq_Set;			//
	INT16U		TestCompleteCode;
	INT08U		Init_Param_Oper;
	INT32U		SysTime;				// UTC Time
	INT08U		Reserved[16];
	//INT08U		Reserved[20];
};
typedef struct tagMcuTestStatus  McuTestStSTR;

enum enumREMOCON_KEY {
	REMOCON_KEY_NONE		= 0x00000000,
	REMOCON_KEY_AUTO_MAN	= 0x00000001,
	REMOCON_KEY_SSTOP		= 0x00000002,
	REMOCON_KEY_FORWARD		= 0x00000004,
	REMOCON_KEY_REVERSE		= 0x00000008,
	REMOCON_KEY_CATCH_L		= 0x00000010,
	REMOCON_KEY_CATCH_R		= 0x00000020,
	REMOCON_KEY_ENTER		= 0x00000040,
	REMOCON_KEY_RESERVED0	= 0x00000080,
	REMOCON_KEY_M1_MODE		= 0x00000100,
	REMOCON_KEY_M2_SET		= 0x00000200,
	REMOCON_KEY_UP			= 0x00000400,
	REMOCON_KEY_DOWN		= 0x00000800,
	REMOCON_KEY_START		= 0x00001000,
	REMOCON_KEY_RESET		= 0x00002000,
	REMOCON_KEY_RESERVED1	= 0x00004000,
	REMOCON_KEY_RESERVED2	= 0x00008000,
	REMOCON_KEY_SPARE1		= 0x00010000,
	REMOCON_KEY_SPARE2		= 0x00020000,
	REMOCON_KEY_SPARE3		= 0x00040000,
	REMOCON_KEY_SPARE4		= 0x00080000,
	REMOCON_KEY_SPARE5		= 0x00100000,
};

struct __attribute__((__packed__)) tagEncoderTxPDO
{
	INT08U Ch1_Counter_Status;
	INT08U Ch2_Counter_Status;
	INT32U Ch1_Present_Value;
	INT32U Ch2_Present_Value;
	INT32U Ch1_Latch_A;
	INT32U Ch2_Latch_A;
	INT32U Ch1_Latch_B;
	INT32U Ch2_Latch_B;
};
typedef struct tagEncoderTxPDO  EncoderTxPDO;

struct __attribute__((__packed__)) tagEncoderRxPDO
{
	INT08U Ch1_Switch0;
	INT08U Ch1_Switch1;
	INT08U Ch2_Switch0;
	INT08U Ch2_Switch1;
	INT32U Ch1_Preset_Value;
	INT32U Ch2_Preset_Value;
};
typedef struct tagEncoderRxPDO  EncoderRxPDO;

struct __attribute__((__packed__)) tagEncoderTxPDO_1
{
	INT08U DI;
	INT08U Counter_Status;
	INT32U Present_Value;
};
typedef struct tagEncoderTxPDO_1  EncoderTxPDO_1;

struct __attribute__((__packed__)) tagEncoderRxPDO_1
{
	INT08U DO;
	INT08U Switch;
	INT32U Preset_Value;
};
typedef struct tagEncoderRxPDO_1  EncoderRxPDO_1;

struct __attribute__((__packed__)) tagMX_EXT_TxPDO
{
	INT08U DI;
	INT08U ENC_Status;
	INT32U ENC_Postion;
	INT32U SSI_Postion;
};
typedef struct tagMX_EXT_TxPDO  MX_EXT_TxPDO;

struct __attribute__((__packed__)) tagMX_EXT_RxPDO
{
	INT08U DO;
	INT08U ENC_Switch;
	INT32U ENC_Preset_Value;
	INT08U SSI_Switch;
	INT32U PTO_Freq;
};
typedef struct tagMX_EXT_RxPDO  MX_EXT_RxPDO;

///////////////////////////////////////////////////////////////////

//#define MAX_GRAPH_COUNT         12
#define MAX_GRAPH_DATA_COUNT   700

struct __attribute__((__packed__)) tagGraphLog
{
	INT16U Index;
	INT32U StartTimer;
	INT08U Reserved[2];
	INT32S GraphData[MAX_GRAPH_COUNT][MAX_GRAPH_DATA_COUNT];
};
typedef struct tagGraphLog  GraphLogSTR;

extern INT16U				m_run_pgm_mode;

extern ExtFlashSEnv			m_ExtSEnv;
extern ExtFlashSEnv0		m_ExtSEnv0;
extern ExtFlashSEnv1		m_ExtSEnv1;
extern ExtFlashSEnv2		m_ExtSEnv2;

extern DevStatusSTR			m_DevStatus;
extern StatusSTR			m_St;			// SRM 상태 구조체
extern BKSRamSTR			m_BKSram;
extern PGMEnvSTR			m_pgmEnv;
extern TestStatusSTR		m_TestStatus;
extern InvertorInfoSTR		m_Invertor_Info;

extern DIO_SetInfoSTR		m_DIO_SetInfo;

extern GraphLogSTR        m_GraphLog;

extern McuTestCtrSTR	m_McuTestCtr;
extern McuTestStSTR		m_McuTestSt;

extern const INT08U nVal[];
extern const INT08U cbits[];
extern const INT08U nbits[];
extern const INT16U cbits16[];
extern const INT16U nbits16[];
extern const INT32U cbits32[];
extern const INT32U nbits32[];

#define  CALC_BITS( value, st, inx )   \
if (st) value |= cbits32[inx]; \
	   else     value &= nbits32[inx];



#endif /* __MX_DEFINE_H */


