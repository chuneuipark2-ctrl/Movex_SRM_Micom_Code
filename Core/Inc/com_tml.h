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
/* ��ſ� ���õ� INDEX ����                                                     */
/*******************************************************************************/
#define TY_DEVICE_STATUS              0x10      // ��ġ ���� �䱸
#define TY_DEVICE_CONTROL             0x11      // ��ġ ���� ���

#define TY_TEST_STATUS					0x12      // Request Test Status
#define TY_TEST_CONTROL					0x13      // Control Test Status
#define TY_FUNC_CONTROL					0x14      // Control Function Command

#define TY_GRAPH_REQUEST				0x15

#define TY_MANUNAL_OUTPUT_CONTROL		0x16      // Manual Output Control

#define TY_DOWNLOAD_START				0x20      // �ٿ�ε� ����
#define TY_DOWNLOAD_DATA				0x21      // �ٿ�ε� Data
#define TY_DOWNLOAD_END					0x22      // �ٿ�ε� �Ϸ�

#define TY_DIO_FORM_REQ					0x23      // DIO �������� ��ȸ
#define TY_DIO_FORM_CONTROL				0x24      // DIO �������� ����

#define TY_MACHINE_SPEC_STATUS			0x25      // ����� ���� �䱸
#define TY_MACHINE_SPEC_CONTROL			0x26      // ����� ���� ���

#define TY_STATUS_REQ					0x30      // ���¿䱸
#define TY_OPERATION_INFO_REQ			0x31      // �������� �䱸
#define TY_INVERTOR_INFO_REQ			0x32      // �ι��� ���� ����

#define TY_ALARMLOG_REQUEST           0x34      // �˶��α� ��ȸ
#define TY_ALARMLOG_DELETE            0x35      // �˶��α� ����

#define TY_CMD_TASK_ORDER			0x40		//

#define TY_CMD_ORDER				0x41		// 지상반에서 전달한 반송지령 구분작업(이동 LOAD, UNLOAD) -> m_WorkData[]에 넘겨줌

#define TY_CMD_REFERENCE			0x44		// Invertor Reference Setup

#define TY_CMD_START				0x50		// ���۸��
#define TY_CMD_MOVE_HOME			0x51		// Ȩ��ġ �̵�
#define TY_CMD_ERROR_RESET			0x52		// �̻󸮼¸��
#define TY_CMD_ORDER_DELETE			0x53		// �۾��������
#define TY_NORMAL_STOP_REQ			0x54		// ����, ���� OFF
#define TY_EMERGENCY_STOP_REQ		0x55		// �������
#define TY_MODE_CHANGE				0x58		// ��ġ ��� ����
#define TY_CMD_MOVE_MAINTANENCE		0x59		// ���� ��ġ �̵�

#define TY_CMD_DEMO_CONTROL			0x60		// ���� ���� ����

#define TY_CMD_SCAN_POSITION_SENSOR	0x61		// ��ġ ���� ��ĵ

#define TY_CMD_MANUAL				0x80		// Manual Control

#define TY_INVERTOR_PARAM_REQ		0x90		// �Ķ���� �ּҰ� ���� ��ȸ
#define TY_INVERTOR_PARAM_SET		0x91		// �Ķ���� �ּҰ� ���� ����

#define TY_NOT_DEF_PROCOTOL			0x92		// �� ���� ��ȸ. 23. 8. 21 ����
#define TY_NOT_DEF_PROTOCOL1		0x93		// �� ���� ����. 23. 8. 21 ����

#define TY_CELL_ENV_REQ				0x94		// �� ���� ��ȸ
#define TY_CELL_ENV_SET				0x95		// �� ���� ����
#define TY_CELL_OFFSET_ENV_REQ		0x96		// �������� ���� ��ȸ
#define TY_CELL_OFFSET_ENV_SET		0x97		// �������� ���� ����
#define TY_STATION_ENV_REQ			0x98		// �����̼� ���� ��ȸ
#define TY_STATION_ENV_SET			0x99		// �����̼� ���� ����

//#define TY_ST_INTERLOCK_ENV_REQ		0x9A		// �����̼� ���ͷ� ���� ��ȸ
//#define TY_ST_INTERLOCK_ENV_SET		0x9B		// �����̼� ���ͷ� ���� ����

#define TY_PROHIBIT_RACK_ENV_REQ	0x9C		// ������ ���� ��ȸ
#define TY_PROHIBIT_RACK_ENV_SET	0x9D		// ������ ���� ����
#define TY_SPECIAL_RACK_ENV_REQ		0x9E		// ����ȷ� ���� ��ȸ
#define TY_SPECIAL_RACK_ENV_SET		0x9F		// ����ȷ� ���� ����

#define TY_SETUP_INITIALIZE_SET			0xA0		// ���� �ʱ�ȭ

#define TY_CONTROL_REQ				0xA1		// ���� ���� ��ȸ
#define TY_CONTROL_SET				0xA2		// ���� ���� ����
#define TY_TRAVEL_DRIVE_REQ			0xA3		// ���� ����̺� ���� ��ȸ
#define TY_TRAVEL_DRIVE_SET			0xA4		// ���� ����̺� ���� ����
#define TY_LIFT_DRIVE_REQ			0xA5		// �°� ����̺� ���� ��ȸ
#define TY_LIFT_DRIVE_SET			0xA6		// �°� ����̺� ���� ����
#define TY_FORK_DRIVE_REQ			0xA7		// ��ũ ����̺� ���� ��ȸ
#define TY_FORK_DRIVE_SET			0xA8		// ��ũ ����̺� ���� ����

#define TY_PARA_VELOCITY_REQ		0xA9		// �ӵ� ���� ��ȸ
#define TY_PARA_VELOCITY_SET		0xAA		// �ӵ� ���� ����

#define TY_MCU_TEST					0xBF		// MCU Test

#define TY_DSP_STATUS				0xC0		// Display Board ���� ��ȸ                                    
#define TY_DSP_DATA					0xC2		// Display Board ����

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

