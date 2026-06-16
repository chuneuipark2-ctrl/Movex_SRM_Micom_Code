/*
 * com_dsp.c
 *
 *  Created on: 2023. 1. 3.
 *      Author: ARTWARE
 */

#include "main.h"
#include "User_Define.h"
#include "uart.h"
#include "alarm.h"
#include "com_udp.h"
#include "com_hmi.h"

#include "com_dsp.h"

extern UART_HandleTypeDef huart6;

DspStatusSTR			m_DspStatus[DEF_DSP_SLAVE_CNT];
static DspDataSTR		m_DspData;
RecvDspData				m_RecvDspData[DEF_DSP_SLAVE_CNT];

INT08U		m_Recv_DSP_ID;

static INT08U	m_Slave_Index;
static INT16U	m_DSP_Com_Seq;

static INT08U	m_DSP_Connect_Flag[DEF_DSP_SLAVE_CNT];
static INT32U	m_DSP_Connect_Timer[DEF_DSP_SLAVE_CNT];

void Request_DSP_Status(INT08U port, INT08U SlaveNo)
{
	TMLComSTR nComData;

#if DEBUG_DSP
	printf("[DEBUG_DSP] Request DSP Status Slave :%d Seq:%d\r\n", SlaveNo, m_DSP_Com_Seq);
#endif

	if (SlaveNo >= DEF_DSP_SLAVE_CNT)
	{
		return;
	}
	else
	{
		memcpy((INT08U*)m_pgmEnv.DSPUdpDstIP, m_ExtSEnv.Machine.DSP_Set.NetIf[SlaveNo].IP, sizeof(INT08U) * 4);
		//m_pgmEnv.DSPUdpDstPort = m_ExtSEnv.Machine.DSP_Set.NetIf[SlaveNo].RemotePort;

		m_pgmEnv.DSPUdpDstPort = DEF_DSP_REMOTE_PORT;

		memset((INT08U*)&nComData, 0x00, sizeof(TMLComSTR));

		nComData.Header.DstID.Type = COM_ID_DSP;
		nComData.Header.DstID.Index = SlaveNo + 1;
		nComData.Header.Cmd = 0x02;
		//nComData.Header.Cmd = 0x01;
		nComData.Header.Cmd2 = TY_DSP_STATUS;
		nComData.Header.Seq = m_DSP_Com_Seq;
		++m_DSP_Com_Seq;

		clearTxBuf(port);
		rsPutmPort(port, FRAME_STX, 4);										// STX : 0x16 0x16 0x16 0x16
		crcClear(port);														// Clear CRC
		txPutHeader_1(port, (ComHeaderSTR*)&nComData.Header, 20);
		txPutnPort(port, (INT08U*)&nComData.Data, sizeof(INT08U) * 20);		// Data
		txCRCPort(port);													// Transmit CRC
		rsPutmPort(port, FRAME_ETX, 1);										// ETX : 0xF5
		sendTxBuf(port);
		
		m_Recv_DSP_ID = 0;
	}
}

void Request_DSP_Control(INT08U port, INT08U SlaveNo)
{
	TMLComSTR nComData;

#if DEBUG_DSP
	printf("[DEBUG_DSP] Request DSP Control Slave :%d\r\n", SlaveNo);
#endif

	if (SlaveNo >= DEF_DSP_SLAVE_CNT)
	{
		return;
	}
	else
	{
		memcpy((INT08U*)m_pgmEnv.DSPUdpDstIP, m_ExtSEnv.Machine.DSP_Set.NetIf[SlaveNo].IP, sizeof(INT08U) * 4);
		//m_pgmEnv.DSPUdpDstPort = m_ExtSEnv.Machine.DSP_Set.NetIf[SlaveNo].RemotePort;

		m_pgmEnv.DSPUdpDstPort = DEF_DSP_REMOTE_PORT;

		memset((INT08U*)&nComData, 0x00, sizeof(TMLComSTR));

		nComData.Header.DstID.Type = COM_ID_DSP;
		nComData.Header.DstID.Index = SlaveNo + 1;
		nComData.Header.Cmd = 0x02;
		nComData.Header.Cmd2 = TY_DSP_DATA;
		nComData.Header.Seq = m_DSP_Com_Seq;
		++m_DSP_Com_Seq;

		clearTxBuf(port);
		rsPutmPort(port, FRAME_STX, 4);										// STX : 0x16 0x16 0x16 0x16
		crcClear(port);														// Clear CRC
		txPutHeader_1(port, (ComHeaderSTR*)&nComData.Header, sizeof(DspDataSTR));
		txPutnPort(port, (INT08U*)&m_DspData, sizeof(DspDataSTR));		// Data
		txCRCPort(port);													// Transmit CRC
		rsPutmPort(port, FRAME_ETX, 1);										// ETX : 0xF5
		sendTxBuf(port);

		m_Recv_DSP_ID = 0;
	}
}

#define DSP_MAX_STR	(5)

typedef struct
{
	/** Error code returned from SDO */
	/** Readable error description */
	char          description[DSP_MAX_STR + 1];
} Dsplist_t;

const Dsplist_t RemoconStr[] = {
	{"NONE "},
	{"AUTO "},
	{"STOP "},
	{"FOR  "},
	{"REV  "},
	{"C/L  "},
	{"U/R  "},
	{"ENTER"},
	{"     "},
	{"M1/MO"},
	{"M2/SE"},
	{"UP   "},
	{"DN   "},
	{"START"},
	{"RESET"},
	{"     "},
	{"     "},
	{"KEY-1"},
	{"KEY-2"},
	{"KEY-3"},
	{"KEY-4"},
	{"KEY-5"},
};

void Update_DSP_Screen_Test(void)
{
	m_DspData.Status1[0] = 'A';
	m_DspData.Status1[1] = 'B';
	m_DspData.Status1[2] = 'C';
	m_DspData.Status1[3] = 'D';
	m_DspData.Status1[4] = 'E';
	m_DspData.Status1[5] = 'F';

	m_DspData.Status2[0] = 'A';
	m_DspData.Status2[1] = 'B';
	m_DspData.Status2[2] = 'C';
	m_DspData.Status2[3] = '-';
	m_DspData.Status2[4] = 'E';
	m_DspData.Status2[5] = 'F';

	m_DspData.Color.Code = DSP_COLOR_GREEN;
	m_DspData.Color.Full = 0;

	m_DspData.ToggleTime = 0;		// 300ms
	m_DspData.Buzzer = 0;		// 300ms
	m_DspData.BuzzerTime = 0;		// 300ms
}

void Update_DSP_Screen(void)
{
	INT08U nMode = 0;

	if (m_St.SRM_Status1.Bit.Fault)
	{
		m_DspData.Status1[0] = 'E';
		m_DspData.Status1[1] = '0' + m_St.MainErrCode / 10;
		m_DspData.Status1[2] = '0' + m_St.MainErrCode % 10;
		m_DspData.Status1[3] = '-';
		m_DspData.Status1[4] = '0' + m_St.SubErrCode / 10;
		m_DspData.Status1[5] = '0' + m_St.SubErrCode % 10;

		m_DspData.Color.Code = DSP_COLOR_RED;
		m_DspData.Color.Full = 0;

		m_DspData.ToggleTime = 50;		// 300ms
		m_DspData.Buzzer = 1;		// 300ms
		m_DspData.BuzzerTime = 50;		// 300ms
	}
	else
	{
		if (m_St.SRM_Status1.Bit.Warning)
		{
			m_DspData.Status1[0] = 'W';
			m_DspData.Status1[1] = '0' + m_St.MainErrCode / 10;
			m_DspData.Status1[2] = '0' + m_St.MainErrCode % 10;
			m_DspData.Status1[3] = '-';
			m_DspData.Status1[4] = '0' + m_St.SubErrCode / 10;
			m_DspData.Status1[5] = '0' + m_St.SubErrCode % 10;

			m_DspData.Color.Code = DSP_COLOR_YELLOW;
			m_DspData.Color.Full = 0;

			m_DspData.ToggleTime = 50;		// 300ms
			m_DspData.Buzzer = 1;		// 300ms
			m_DspData.BuzzerTime = 50;		// 300ms
		}
		else
		{
			/*
			m_DspData.Status1[0] = 'P';
			m_DspData.Status1[1] = '0' + m_St.PosFork1.Bay_ID / 10;
			m_DspData.Status1[2] = '0' + m_St.PosFork1.Bay_ID % 10;
			m_DspData.Status1[3] = '-';
			m_DspData.Status1[4] = '0' + m_St.PosFork1.Level_ID / 10;
			m_DspData.Status1[5] = '0' + m_St.PosFork1.Level_ID % 10;

			m_DspData.Color.Code = DSP_COLOR_GREEN;
			m_DspData.Color.Full = 0;

			m_DspData.ToggleTime = 0;		// 300ms
			m_DspData.Buzzer = 0;		// 300ms
			m_DspData.BuzzerTime = 0;		// 300ms
			*/

			memset((INT08U*)m_DspData.Status1, 0x00, sizeof(INT08U) * 6);

			/*
			if (m_DspStatus[0].ModeSw == 0x06)
			{
				// RTV Rear
				m_DspData.Status1[0] = 'R';
				m_DspData.Status1[1] = 'T';
				m_DspData.Status1[2] = 'V';
				m_DspData.Status1[3] = '-';
				m_DspData.Status1[4] = 'R';
			}
			else if (m_DspStatus[0].ModeSw == 0x09)
			{
				// RTV Front
				m_DspData.Status1[0] = 'R';
				m_DspData.Status1[1] = 'T';
				m_DspData.Status1[2] = 'V';
				m_DspData.Status1[3] = '-';
				m_DspData.Status1[4] = 'F';
			}
			*/
			///*
			if (m_DspStatus[0].ModeSw & 0x02)
			{
				// EMS Left
				m_DspData.Status1[0] = 'E';
				m_DspData.Status1[1] = 'M';
				m_DspData.Status1[2] = 'S';
				m_DspData.Status1[3] = '-';
				m_DspData.Status1[4] = 'L';
			}
			else if (m_DspStatus[0].ModeSw & 0x01)
			{
				m_DspData.Status1[0] = 'E';
				m_DspData.Status1[1] = 'M';
				m_DspData.Status1[2] = 'S';
				m_DspData.Status1[3] = '-';
				m_DspData.Status1[4] = 'R';
			}
			//*/

			m_DspData.Color.Code = DSP_COLOR_GREEN;
			m_DspData.Color.Full = 0;

			m_DspData.ToggleTime = 0;		// 300ms
			m_DspData.Buzzer = 0;		// 300ms
			m_DspData.BuzzerTime = 0;		// 300ms
		}
	}

	if (m_pgmEnv.RemoconKey == 0)
	{
		memset((INT08U*)m_DspData.Status2, 0x00, sizeof(INT08U) * 6);
		memcpy((INT08U*)m_DspData.Status2, RemoconStr[0].description, sizeof(INT08U) * 5);
	}
	else
	{
		///*
		for (INT08U i = 0; i < 21; i++)
		{
			if (m_pgmEnv.RemoconKey & cbits32[i])
			{
				memset((INT08U*)m_DspData.Status2, 0x00, sizeof(INT08U) * 6);
				memcpy((INT08U*)m_DspData.Status2, RemoconStr[i + 1].description, sizeof(INT08U) * 5);

				nMode = i + 1;
				break;
			}
		}
		//*/

		switch (nMode)
		{
		case 0:
			break;

		case 1:
			// AUTO/MAN
			m_DspData.Color.Code = DSP_COLOR_GREEN;
			m_DspData.Color.Full = 1;
			break;

		case 2:
			// S.STOP
			m_DspData.Color.Code = DSP_COLOR_GREEN;
			m_DspData.Color.Full = 1;

			m_DspData.ToggleTime = 10;		//
			break;

		case 3:
			//Forward
			m_DspData.Status2[4] = 0xA4;	// Up Arrow
			//m_DspData.Status2[4] = 0xA7;	// Right Arrow
			break;

		case 4:
			//Backward
			m_DspData.Status2[4] = 0xA5;	// Down Arrow
			//m_DspData.Status2[4] = 0xA6;	// Left Arrow
			break;

		case 5:
			//Catch/L
			m_DspData.Status2[4] = 0xA7;	// Left Arrow
			//m_DspData.Status2[4] = 0x88;	// Big Circle
			break;

		case 6:
			//Uncatch/R
			m_DspData.Status2[4] = 0xA6;	// Right Arrow
			//m_DspData.Status2[4] = 0x89;	// Big Circle(empty)
			break;

		case 11:
			m_DspData.Status2[4] = 0xAC;	// Up triangle
			break;

		case 12:
			m_DspData.Status2[4] = 0xAD;	// Down triangle
			break;

		case 7:
			// ENTER
			m_DspData.Color.Code = DSP_COLOR_GREEN;
			m_DspData.Color.Full = 1;

			m_DspData.ToggleTime = 255;		//
			break;


		default:
			break;
		}
	}
	
	/*
	m_DspData.Status2[0] = 'M';
	m_DspData.Status2[1] = '0' + m_St.SRM_OperationCode / 10;
	m_DspData.Status2[2] = '0' + m_St.SRM_OperationCode & 10;

	if (m_St.PosFork1.Position1.Bit.Trav_Left || m_St.PosFork1.Position1.Bit.Trav_Right)
	{
		m_DspData.Status2[3] = 0x87;	// Big Rect(empty)
	}
	else
	{
		m_DspData.Status2[3] = 0x86;	// Big Rect(empty)
	}

	if ()
	{
	}
	*/
}

/**
   * @brief
   * @param  None
   * @retval None
   */
void DSP_ComManager(void)
{
	static INT08U s_Step;
	static INT32U s_StepTimer;

	static INT32U s_ComRetry = 0;
	static INT08U s_ComPort = 0;

	INT08U i = 0;

	if (m_ExtSEnv.Machine.DSP_Set.Com_Type == 2)
	{
		HMI_Com_Receive_Proc();
	}

	switch (s_Step)
	{
	case 0:
		if (m_ExtSEnv.Machine.DSP_Set.Com_Type == 1)
		{
			// UDP
			if (m_pgmEnv.UPLinkInitFlag)
			{
				SetTimer1ms(&s_StepTimer);
				s_Step = 1;
			}
		}
		else if (m_ExtSEnv.Machine.DSP_Set.Com_Type == 2)
		{
			// RS485
			SetTimer1ms(&s_StepTimer);
			s_Step = 2;
		}
		break;

	case 1:
		if (getCalcTimer1ms(s_StepTimer) > 5000)
		{
#if DEBUG_DSP
			printf("[DEBUG_DSP] Initialize DSP UDP Socket\r\n");
#endif
			udp_com_init_DSP();

			s_ComPort = rsDSP_UDP_Port;

			m_DSP_Com_Seq = 0;
			m_Slave_Index = 0;

			s_ComRetry = 0;

			SetTimer1ms(&s_StepTimer);
			s_Step = 10;
		}
		break;

	case 2:
		if (getCalcTimer1ms(s_StepTimer) > 5000)
		{
#if DEBUG_DSP
			printf("[DEBUG_DSP] Initialize RS485 Port\r\n");
#endif
			__HAL_UART_ENABLE_IT(&huart6, UART_IT_RXNE);

			s_ComPort = rsRS485_422_Port;

			RS485_Mode_Control(RS485_RX_MODE);
			m_TxUartQ[rsRS485_422_Port].RS485_Mode = 1;

			s_ComRetry = 0;

			m_DSP_Com_Seq = 0;
			m_Slave_Index = 0;

			SetTimer1ms(&s_StepTimer);
			s_Step = 10;
		}
		break;

	case 10:
		if (getCalcTimer1ms(s_StepTimer) > 50)
		{
			Request_DSP_Status( s_ComPort, m_Slave_Index);

			SetTimer1ms(&s_StepTimer);
			s_Step = 11;
		}
		break;

	case 11:
		if (getCalcTimer1ms(s_StepTimer) > 100)
		{
			SetTimer1ms(&s_StepTimer);

			++s_ComRetry;
			if (s_ComRetry > 3)
			{
				s_ComRetry = 0;
				++m_Slave_Index;
				if (m_Slave_Index >= m_ExtSEnv.Machine.DSP_Set.Connect_Count)
				{
					m_Slave_Index = 0;
					s_Step = 20;
				}
			}
			else
			{
				s_Step = 10;
			}
		}
		else
		{
			if (m_Recv_DSP_ID == (m_Slave_Index + 1))
			{
#if DEBUG_DSP
				printf("[DEBUG_DSP] Receive DSP Status Slave :%d\r\n", m_Slave_Index);
#endif
				m_DSP_Connect_Flag[m_Slave_Index] = 1;

				++m_Slave_Index;
				SetTimer1ms(&s_StepTimer);
				if (m_Slave_Index >= m_ExtSEnv.Machine.DSP_Set.Connect_Count)
				{
					s_ComRetry = 0;
					m_Slave_Index = 0;
					s_Step = 20;
				}
				else
				{
					s_Step = 10;
				}
			}
		}
		break;

	case 20:
		if (getCalcTimer1ms(s_StepTimer) > 30)
		{
			Update_DSP_Screen_Test();
			
			SetTimer1ms(&s_StepTimer);

			if (m_DSP_Connect_Flag[m_Slave_Index])
			{
				Request_DSP_Control(s_ComPort, m_Slave_Index);

				s_Step = 21;
			}
			else
			{
				++m_Slave_Index;
				if (m_Slave_Index >= m_ExtSEnv.Machine.DSP_Set.Connect_Count)
				{
					m_Slave_Index = 0;
				}
			}
		}
		break;

	case 21:
		if (getCalcTimer1ms(s_StepTimer) > 100)
		{
			++s_ComRetry;
			if (s_ComRetry > 3)
			{
				s_ComRetry = 0;

				++m_Slave_Index;
				if (m_Slave_Index >= m_ExtSEnv.Machine.DSP_Set.Connect_Count)
				{
					m_Slave_Index = 0;
				}
			}

			SetTimer1ms(&s_StepTimer);
			s_Step = 20;
		}
		else
		{
			if (m_Recv_DSP_ID == (m_Slave_Index + 1))
			{
#if DEBUG_DSP
				printf("[DEBUG_DSP] Receive DSP Control Slave :%d\r\n", m_Slave_Index);
#endif
				m_pgmEnv.RemoconKey = 0;
				m_pgmEnv.RemoconKey = ((INT32U)m_RecvDspData[m_Slave_Index].RemoconKey[2] << 16) & 0x00FF0000;
				m_pgmEnv.RemoconKey |= ((INT32U)m_RecvDspData[m_Slave_Index].RemoconKey[1] << 8) & 0x0000FF00;
				m_pgmEnv.RemoconKey |= (INT32U)m_RecvDspData[m_Slave_Index].RemoconKey[0] & 0x000000FF;

				m_DSP_Connect_Timer[m_Slave_Index] = m_pgmEnv.timer1ms;

				m_DevStatus.mLinkStatus.Extra_Slave |= cbits[m_Slave_Index];

				++m_Slave_Index;
				if (m_Slave_Index >= m_ExtSEnv.Machine.DSP_Set.Connect_Count)
				{
					m_Slave_Index = 0;
					SetTimer1ms(&s_StepTimer);
					//s_Step = 20;
					s_Step = 10;
				}
			}
		}
		break;
	}

	if (m_ExtSEnv.Machine.DSP_Set.Com_Type == 2)
	{
		HMI_Com_Transmit_Proc();
	}

	
	for (i = 0; i < m_ExtSEnv.Machine.DSP_Set.Connect_Count; i++)
	{
		if (m_DSP_Connect_Flag[i])
		{
			if (getCalcTimer1ms(m_DSP_Connect_Timer[i]) > 1500)
			{
				m_DevStatus.mLinkStatus.Extra_Slave &= nbits[i];
			}
		}
		else
		{
			m_DevStatus.mLinkStatus.Extra_Slave &= nbits[i];
		}
	}
}
