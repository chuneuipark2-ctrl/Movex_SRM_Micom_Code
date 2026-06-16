
//#include "stm32f7xx_hal.h"

#include "com_tml.h"
#include "uart.h"
#include "alarm.h"
#include "upgrade.h"
#include "rtc.h"
#include "com_udp.h"
#include "FlashSST26.h"
//#include "flash.h"
//#include "ecat.h"
#include "dev_SRM.h"
#include "SRM_Parameter.h"
#include "com_dsp.h"

//#include "com_ht100.h"

extern UART_HandleTypeDef huart3;

extern HMI_Com		m_HMI_Com;

TMLComSTR          TMLCom;

static INT08U  rsIsData = 0;
static INT08U  rsComData;
static INT08U  rsComMode = 0;
static INT16U  rsComLen = 0;
static INT16U  rsCRCValue = 0;
static INT16U  rsLen = 0;
static INT08U  rsHeader[FRAME_HEADER_SIZE];
static INT08U  rsComBuffer[FRAME_MAX_DATA_LEN];

static INT32U m_Rx_com_chkTimer = 0;

static void rsStartCheck(void)
{
	if (rsComData == FRAME_STX)
	{
		if (++rsComLen >= FRAME_SYNC_SIZE)
		{
			rsComMode = 1;
			rsCRCValue = 0;
			rsComLen = 0;
		}
	}
	else rsComLen = 0;
}

static void rsHeaderCheck(void)
{
	rsCRCValue = crcByteCalc(rsCRCValue, rsComData);
	rsComBuffer[rsComLen] = rsComData;

	if (++rsComLen >= FRAME_HEADER_SIZE)
	{
		memcpy((INT08U*)&rsHeader, (INT08U*)rsComBuffer, FRAME_HEADER_SIZE);
		rsLen = (INT16U)rsHeader[8] | ((INT16U)rsHeader[9] << 8);
		rsLen -= 1;
		rsComLen = 0;

		if (rsLen > FRAME_MAX_DATA_LEN)  rsComMode = 0;
		else if (rsLen)                  rsComMode = 2;
		else                              rsComMode = 3;
	}
}

static void rsDataCheck(void)
{
	rsCRCValue = crcByteCalc(rsCRCValue, rsComData);
	rsComBuffer[rsComLen] = rsComData;

	if (++rsComLen >= rsLen)
	{
		rsComLen = 0;
		rsComMode = 3;
	}
}

static void rsCrcCheck(void)
{
	rsCRCValue = crcByteCalc(rsCRCValue, rsComData);

	if (++rsComLen >= FRAME_CRC_SIZE)
	{
		rsComLen = 0;
		rsComMode = 4;
	}
}

static void rsEndCheck(void)
{
	if ((rsComData == FRAME_ETX) && (rsCRCValue == 0))
	{
		rsIsData = 1;
		memcpy((INT08U*)&TMLCom.Header, (INT08U*)rsHeader, FRAME_HEADER_SIZE);
		memcpy((INT08U*)&TMLCom.Data[0], (INT08U*)rsComBuffer, rsLen);
	}

	rsComLen = 0;
	rsComMode = 0;
}

void rsComHandler(INT08U rsData)
{
	rsComData = rsData;

	switch (rsComMode)
	{
	case 0: rsStartCheck();          break;
	case 1: rsHeaderCheck();         break;
	case 2: rsDataCheck();           break;
	case 3: rsCrcCheck();            break;
	case 4: rsEndCheck();            break;
	}

	m_Rx_com_chkTimer = m_pgmEnv.timer1ms;
}

void rsComFrame_Parsing(const INT08U* data, INT16U len)
{
	INT16U nRecvIndex = 0;

	for (nRecvIndex = 0; nRecvIndex < len; nRecvIndex++)
	{
		rsComData = *(data + nRecvIndex);

		switch (rsComMode)
		{
		case 0: rsStartCheck();          break;
		case 1: rsHeaderCheck();         break;
		case 2: rsDataCheck();           break;
		case 3: rsCrcCheck();            break;
		case 4: rsEndCheck();            break;
		}
	}
}


#define ARRAY_LEN(x)	(sizeof(x) / sizeof((x)[0]))

void rsComHandlerDMA()
{
	static INT16U	pos = 0;
	static INT16U	old_pos = 0;
	static INT16U	rcvdLen = 0;

	pos = ARRAY_LEN(m_RxUartQ[rsTMLPort].Data) - (__HAL_DMA_GET_COUNTER(huart3.hdmarx));

	if (pos != old_pos)
	{
		if (pos > old_pos)
		{
			rcvdLen = pos - old_pos;
			rsComFrame_Parsing(&m_RxUartQ[rsTMLPort].Data[old_pos], rcvdLen);
		}
		else
		{
			rsComFrame_Parsing(&m_RxUartQ[rsTMLPort].Data[old_pos], ARRAY_LEN(m_RxUartQ[rsTMLPort].Data) - old_pos);

			if (pos > 0)
			{
				rsComFrame_Parsing(&m_RxUartQ[rsTMLPort].Data[0], pos);
			}
		}

		m_RxUartQ[rsTMLPort].Front = old_pos;
		m_RxUartQ[rsTMLPort].Rear = pos;
		m_RxUartQ[rsTMLPort].Len += rcvdLen;

		old_pos = pos;

		asm volatile("NOP");
	}

	SetTimer1ms(&m_Rx_com_chkTimer);
}

///////////////////////////////////////////////////////////////////////


void clearTxBuf(INT08U port)
{
	switch (port)
	{
	case rsTMLPort:
		m_TxUartQ[port].Len = 0;
		break;

	case rsMCU_DEBUG_Port:
	case rsOPTPort:
	case rsEXTPort:
	case rsRS485_422_Port:
		m_TxUartQ[port].Len = 0;
		break;

		/*
	case rsUSBPort:
		m_pgmEnv.txUsbComLen = 0;
		break;
		*/
	case rsETHUDPPort_Uplink:
		m_pgmEnv.txEthUdpComLen = 0;
		break;
	case rsETHTCPPort:
		//m_pgmEnv.txEthTcpComLen = 0;
		break;
	case rsETHUDPPort_DwLink:
		m_pgmEnv.txInvUdpComLen = 0;
		break;

	case rsINVTCPPort:
		//m_pgmEnv.txInvTcpComLen = 0;
		break;

	case rsDSP_UDP_Port:
		m_pgmEnv.txDSPComLen = 0;
		break;
	}
}

void enableTXEN(INT08U port)
{
	if (port == rsRS485_422_Port)
	{
#if defined (SET_DEVICE_TYPE_MINILODER)
		GPIOG->ODR |= GPIO_Pin_7;    // UART6_/RE #1 
		GPIOG->ODR |= GPIO_Pin_10;   // UART6_DE  #1 
		GPIOC->ODR &= ~GPIO_Pin_9;    // UART6_/RE_#2 
		GPIOB->ODR &= ~GPIO_Pin_5;    // UART6_DE  #2 
#else
		/*
		GPIOG->ODR |=  GPIO_Pin_7;    // UART6_/RE #1
		GPIOG->ODR |=  GPIO_Pin_10;   // UART6_DE  #1
		GPIOC->ODR &= ~GPIO_Pin_9;    // UART6_/RE_#2
		GPIOB->ODR &= ~GPIO_Pin_5;    // UART6_DE  #2
		*/

		// 		GPIOG->ODR |= GPIO_Pin_7;    // UART6_/RE #1 
		// 		GPIOG->ODR |= GPIO_Pin_10;   // UART6_DE  #1 
		// 		GPIOC->ODR |= GPIO_Pin_9;    // UART6_/RE_#2 
		// 		GPIOB->ODR |= GPIO_Pin_5;    // UART6_DE  #2 

		//wait1ms(2);
#endif    	
	}
}

void sendTxBuf(INT08U port)
{
	switch (port)
	{
	case rsTMLPort:
		Send_Uart_Polling(port);
		//Send_Uart_DMA(port);
		break;

	case rsMCU_DEBUG_Port:
		Send_Uart_Polling(port);
		//Send_Uart_DMA(port);
		break;

	case rsRS485_422_Port:
		/*
		Send_Uart_Polling(port);

		asm volatile("NOP");
		RS485_Mode_Control(RS485_RX_MODE);
		*/

		m_TxUartQ[port].RS485_422_Tx_Flag = 1;
		break;

	case rsOPTPort:
	case rsEXTPort:
		break;

		/*
	case rsUSBPort:
		//putUsbPacket( (INT08U *)m_pgmEnv.txUsbComBuffer, m_pgmEnv.txUsbComLen );
		m_pgmEnv.txUsbComLen = 0;
		break;
		*/

	case rsETHUDPPort_Uplink:
		udp_SendBuf();

		m_pgmEnv.txEthUdpComLen = 0;
		break;

	case rsETHTCPPort:
		//putTcpSocketData( (INT08U *)m_pgmEnv.txEthTcpComBuffer, m_pgmEnv.txEthTcpComLen );
		//m_pgmEnv.txEthTcpComLen = 0;
		break;

	case rsETHUDPPort_DwLink:
		sendUdpTxBuf_Downlink();

		m_pgmEnv.txInvUdpComLen = 0;
		break;

	case rsINVTCPPort:
		break;

	case rsDSP_UDP_Port:
		udp_SendBuf_DSP((INT32U*)m_pgmEnv.DSPUdpDstIP, m_pgmEnv.DSPUdpDstPort);

		m_pgmEnv.txDSPComLen = 0;
		break;
	}
}

////////////////////////////////////////////////////////////////////////

/**
  * @brief  송신 데이터 해더 생성
  * @param  port		송신 포트
  * @param  pRxHeader	수신 해더 정보
  * @param  Cmd			명령
  * @param  Cmd2		명령2
  * @param  Len		송신 데이터 길이
  * @retval None
  */
void txPutHeader(INT08U port, ComHeaderSTR* pRxHeader, INT08U Cmd, INT08U Cmd2, INT16U Len)
{
	txPutcPort(port, m_pgmEnv.DeviceType);		// Src ID - Type
	txPutcPort(port, m_pgmEnv.DeviceID);		// Src ID - Index
	txPutcPort(port, pRxHeader->SrcID.Type);	// Dst ID - Type
	txPutcPort(port, pRxHeader->SrcID.Index);	// Dst ID - Index
	txPutcPort(port, pRxHeader->Seq);			// Seq
	txPutcPort(port, pRxHeader->Bypass[0]);		// Bypass 0
	txPutcPort(port, pRxHeader->Bypass[1]);		// Bypass 1
	txPutcPort(port, Cmd);                                               // Command
	txPutwPort(port, Len + 1);						// Length, Cmd2 1byte 포함.
	txPutcPort(port, Cmd2);						// Command

	//m_TestStatus.St[DEBUG_STR_20] = pRxHeader->Seq;
}

/**
  * @brief  송신 데이터 해더 생성
  * @param  port		송신 포트
  * @param  pRxHeader	수신 해더 정보
  * @param  Cmd			명령
  * @param  Cmd2		명령2
  * @param  Len		송신 데이터 길이
  * @retval None
  */
void txPutHeader_1(INT08U port, ComHeaderSTR* pRxHeader, INT16U Len)
{
	txPutcPort(port, m_pgmEnv.DeviceType);		// Src ID - Type
	txPutcPort(port, m_pgmEnv.DeviceID);		// Src ID - Index
	txPutcPort(port, pRxHeader->DstID.Type);	// Dst ID - Type
	txPutcPort(port, pRxHeader->DstID.Index);	// Dst ID - Index
	txPutcPort(port, pRxHeader->Seq);			// Seq
	txPutcPort(port, pRxHeader->Bypass[0]);		// Bypass 0
	txPutcPort(port, pRxHeader->Bypass[1]);		// Bypass 1
	txPutcPort(port, pRxHeader->Cmd);           // Command
	txPutwPort(port, Len + 1);					// Length, Cmd2 1byte 포함.
	txPutcPort(port, pRxHeader->Cmd2);			// Command
}

/**
  * @brief  장치 상태 요청 응답
  * @param  port 수신 포트
  * @param  pCom 수신 데이터
  * @retval None
  */
void rxDeviceStatusReq(INT08U port, TMLComPTR pCom)
{
#if DEBUG_MSG
	/*
	INT32U nProcessTime = 0;
	nProcessTime = m_pgmEnv.timer1ms;
	*/
#endif

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);                                        // STX : 0x16 0x16 0x16 0x16
	crcClear(port);                                                      // Clear CRC
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, sizeof(DevStatusSTR));
	txPutnPort(port, (INT08U*)&m_DevStatus, sizeof(DevStatusSTR));                  // Data
	txCRCPort(port);                                                      // Transmit CRC
	rsPutmPort(port, FRAME_ETX, 1);                                        // ETX : 0xF5
	sendTxBuf(port);

#if DEBUG_MSG
	//printf("[DEBUG_APP] Request Device Status ProcessTime : %ld ms\r\n", getCalcTimer1ms(nProcessTime));
#endif
	if (m_pgmEnv.MCU_Test_Mode)
	{
		switch (port)
		{
		case rsTMLPort:
			if (m_McuTestCtr.RS232_Test)
			{
				++m_McuTestSt.RS232_RecvCnt;
			}
			break;

		case rsRS485_422_Port:
			if (m_McuTestSt.RS485_P1_Enable)
			{
				if (pCom->Header.DstID.Index == 1)
				{
					++m_McuTestSt.RS485_P1_RecvCnt;
				}
			}
			else if (m_McuTestSt.RS485_P2_Enable)
			{
				//if (pCom->Header.DstID.Index == 2)
				if ((pCom->Header.DstID.Index == 1) \
					|| (pCom->Header.DstID.Index == 2))
				{
					++m_McuTestSt.RS485_P2_RecvCnt;
				}
			}
			else if (m_McuTestSt.RS422_P1_Enable)
			{
				if (pCom->Header.DstID.Index == 1)
				{
					++m_McuTestSt.RS422_P1_RecvCnt;
				}
			}
			else if (m_McuTestSt.RS422_P2_Enable)
			{
				//if (pCom->Header.DstID.Index == 2)
				if ((pCom->Header.DstID.Index == 1) \
					|| (pCom->Header.DstID.Index == 2))
				{
					++m_McuTestSt.RS422_P2_RecvCnt;
				}
			}
			break;

		case rsETHUDPPort_Uplink:
			if (m_McuTestCtr.EtherNet_Test1)
			{
				++m_McuTestSt.EtherNet1_RecvCnt;
			}
			break;

		case rsETHUDPPort_DwLink:
			if (m_McuTestCtr.EtherNet_Test2)
			{
				++m_McuTestSt.EtherNet2_RecvCnt;
			}
			break;
		}
	}
}

/**
  * @brief  장치 상태 제어 응답
  * @param  port 수신 포트
  * @param  pCom 수신 데이터
  * @retval None
  */
void rxDeviceControlReq(INT08U port, TMLComPTR pCom)
{
	INT08U is_reset = 0;
	INT08U is_save = 0;

	DevControlSTR* pCtrl;
	DeviceSetting  nSetVlaue;

	//if (m_St.SRM_Mode.Bit.Auto)		return;

	pCtrl = (DevControlSTR*)&pCom->Data[4];

	///*
	memcpy((INT08U*)&nSetVlaue, (INT08U*)&m_ExtSEnv.mDevice, sizeof(DeviceSetting));
	//*/
	/*
	memcpy((INT08U*)&nSetVlaue.NetworkInfo_0, (INT08U*)&m_ExtSEnv.mDevice.NetworkInfo_0, sizeof(NetworkInfo_t));
	memcpy((INT08U*)&nSetVlaue.NetworkInfo_1, (INT08U*)&m_ExtSEnv.mDevice.NetworkInfo_1, sizeof(NetworkInfo_t));
	memcpy((INT08U*)&nSetVlaue.MyMACAddr_0, (INT08U*)&m_ExtSEnv.mDevice.MyMACAddr_0, sizeof(INT08U) * 6);
	memcpy((INT08U*)&nSetVlaue.MyMACAddr_1, (INT08U*)&m_ExtSEnv.mDevice.MyMACAddr_1, sizeof(INT08U) * 6);
	memcpy((INT08U*)&nSetVlaue.ProjectID, (INT08U*)&m_ExtSEnv.mDevice.ProjectID, sizeof(ProjectID_t));
	*/

	asm volatile("NOP");
	
	if (m_St.SRM_Mode.Bit.Auto == 0)
	{
		if (pCom->Data[0] & cbits[0])  is_reset = 1;   // Device Reset
	}

	/* 네크워크 설정 변경시, Software Reset 후 설정 적용*/
	if (pCom->Data[1] & cbits[0])
	{
		//setTimeDate(pCtrl->SysTime);
		setTimeDate_Rev2(pCtrl->SysTime);
		m_DevStatus.SysTime = getTimeDate_Rev2();
		//m_DevStatus.SysTime = getTimeDate();
	}

	if (pCom->Data[1] & 0x3E)
	{
		if (m_St.SRM_Mode.Bit.Auto == 0)
		{
			is_save = 1;
			if (pCom->Data[1] & cbits[1])
			{
				memcpy((INT08U*)&nSetVlaue.NetworkInfo_0, (INT08U*)&pCtrl->NetworkInfo_0, sizeof(NetworkInfo_t));
			}

			if (pCom->Data[1] & cbits[2])
			{
				memcpy((INT08U*)&nSetVlaue.MyMACAddr_0, (INT08U*)&pCtrl->MyMACAddr_0, sizeof(INT08U) * 6);
			}

			if (pCom->Data[1] & cbits[3])
			{
				memcpy((INT08U*)&nSetVlaue.NetworkInfo_1, (INT08U*)&pCtrl->NetworkInfo_1, sizeof(NetworkInfo_t));
			}

			if (pCom->Data[1] & cbits[4])
			{
				memcpy((INT08U*)&nSetVlaue.MyMACAddr_1, (INT08U*)&pCtrl->MyMACAddr_1, sizeof(INT08U) * 6);
			}

			if (pCom->Data[1] & cbits[5])
			{
				memcpy((INT08U*)&nSetVlaue.ProjectID, (INT08U*)&pCtrl->ProjectID, sizeof(ProjectID_t));
			}
		}
	}

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);		// STX : 0x16 0x16 0x16 0x16
	crcClear(port);		// Clear CRC
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 0);
	txCRCPort(port);	// Transmit CRC
	rsPutmPort(port, FRAME_ETX, 1);	// ETX : 0xF5
	sendTxBuf(port);

	if (is_save)
	{
		// 네트워크 정보 수정 후, Reset 처리하면 안됨.
		// 양산GUI, JIG에서 네트워크 정보 수정 후, 통신 끊김현상 발생.
		// JIG에서 네트워크 정보 수정 후, Reset 처리해서 네트워크 초기화 해야함.
		Set_Device_Parameter(&nSetVlaue);	/*saveFlashSEnvSTR();*/
	}

	if (is_reset)	controlCpuReset();
}

/**
  * @brief  기계 사양 요청 응답
  * @param  port 수신 포트
  * @param  pCom 수신 데이터
  * @retval None
  */
void rxMachine_Type_Req(INT08U port, TMLComPTR pCom)
{
#if DEBUG_MSG
	INT32U nProcessTime = 0;
	nProcessTime = m_pgmEnv.timer1ms;
#endif

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);	// STX : 0x16 0x16 0x16 0x16
	crcClear(port);		// Clear CRC
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, sizeof(SRM_Machine_TypeCom));
	txPutnPort(port, (INT08U*)&m_ExtSEnv.Machine, sizeof(SRM_Machine_TypeCom));	// Data
	txCRCPort(port);	// Transmit CRC
	rsPutmPort(port, FRAME_ETX, 1);	// ETX : 0xF5
	sendTxBuf(port);

#if DEBUG_MSG
	printf("[DEBUG_APP] Request Machine Type ProcessTime : %ld ms\r\n", getCalcTimer1ms(nProcessTime));
#endif
}

/**
  * @brief  기계 사양 설정 응답
  * @param  port 수신 포트
  * @param  pCom 수신 데이터
  * @retval None
  */
void rxMachine_Type_Set(INT08U port, TMLComPTR pCom)
{
	INT08U is_reset = 0;
	INT08U is_save = 0;
	INT08U nError = 0;

	SRM_Machine_Type* pCtrl;

	if (!m_St.SRM_Mode.Bit.Setup)	return;

	pCtrl = (SRM_Machine_Type*)&pCom->Data[3];

	if (pCom->Data[0] & cbits[7])
	{
		is_reset = Set_Machine_Parameter((SRM_Machine_STR*)&pCtrl->mType);
		Set_DSP_Parameter((MX_DSP_Setting*)&pCtrl->DSP_Set);
	}
	else
	{
		if (pCom->Data[0] & cbits[0])
		{
			is_reset = Set_Machine_Parameter((SRM_Machine_STR*)&pCtrl->mType);
		}

		if (pCom->Data[0] & cbits[1])
		{
			Set_DSP_Parameter((MX_DSP_Setting*)&pCtrl->DSP_Set);
		}
	}


	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);                                        // STX : 0x16 0x16 0x16 0x16
	crcClear(port);                                                      // Clear CRC
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 2);
	if (nError == 0)
	{
		txPutcPort(port, 0);
		txPutcPort(port, 0);
	}
	else
	{
		txPutcPort(port, 1);
		txPutcPort(port, nError);
	}
	txCRCPort(port);                                                      // Transmit CRC
	rsPutmPort(port, FRAME_ETX, 1);                                        // ETX : 0xF5
	sendTxBuf(port);

	if (is_reset)	controlCpuReset();
}

void rxTestStatusReq(INT08U port, TMLComPTR pCom)
{
#if DEBUG_MSG
	/*
	INT32U nProcessTime = 0;
	nProcessTime = m_pgmEnv.timer1ms;
	*/
#endif

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);        // STX : 0x16 0x16 0x16 0x16
	crcClear(port);                        // Clear CRC
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, sizeof(TestStatusSTR));
	txPutnPort(port, (INT08U*)&m_TestStatus, sizeof(TestStatusSTR));      // Data
	txCRCPort(port);                       // Transmit CRC
	rsPutmPort(port, FRAME_ETX, 1);        // ETX : 0xF5
	sendTxBuf(port);

#if DEBUG_MSG
	//printf("[DEBUG_APP] Request Test Status ProcessTime : %ld ms\r\n", getCalcTimer1ms(nProcessTime));
#endif
}

void rxTestControlReq(INT08U port, TMLComPTR pCom)
{
	INT08U i;
	TestControlSTR* pCtrl;

	pCtrl = (TestControlSTR*)&pCom->Data[2];

	for (i = 0; i < 8; i++)
	{
		//if (pCom->Data[0] & cbits[7 - i])
		if (pCom->Data[0] & cbits[i])
		{
			m_TestStatus.Ctrl[i] = pCtrl->Ctrl[i];
		}
	}

	for (i = 0; i < 8; i++)
	{
		//if (pCom->Data[1] & cbits[7 - i])
		if (pCom->Data[1] & cbits[i])
		{
			m_TestStatus.Ctrl[8 + i] = pCtrl->Ctrl[8 + i];
		}
	}

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);                                        // STX : 0x16 0x16 0x16 0x16
	crcClear(port);                                                      // Clear CRC
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 0);
	txCRCPort(port);                                                      // Transmit CRC
	rsPutmPort(port, FRAME_ETX, 1);                                        // ETX : 0xF5
	sendTxBuf(port);
}

struct __attribute__((__packed__)) tagFuncControl
{
	INT08U  Index;
	INT32S  Value;
};
typedef struct tagFuncControl  FuncControlSTR;

extern MX_EXT_RxPDO m_MX_EXT_RxPDO;
extern EncoderRxPDO_1 m_Enx_RxPDO_1;

void rxFuncControlReq(INT08U port, TMLComPTR pCom)
{
	INT32U i = 0;
	//INT08U flag = 0;
	FuncControlSTR* pCtrl;

	//CellOffsetSTR nBuf;

	INT32U nTimer = 0;;

	static INT32U s_TestVal = 0;

	pCtrl = (FuncControlSTR*)&pCom->Data[0];

#if DEBUG_INVERTER_SIMULATION
	switch (pCtrl->Index)
	{
	case  1:
		m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

		m_pgmEnv.Test_Simulator.Test_InvSt[INV_TRAVEL].Current_Pos = pCtrl->Value;
		break;

	case  2:
		m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

		m_pgmEnv.Test_Simulator.Test_InvSt[INV_HOIST].Current_Pos = pCtrl->Value;
		break;

	case  3:
		m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

		m_pgmEnv.Test_Simulator.Test_InvSt[INV_FORK_1].Current_Pos = pCtrl->Value;
		break;

	case  4:
		m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

		m_pgmEnv.Move_PosFlag = pCtrl->Value;
		break;

	case  5:
		if (pCtrl->Value < MAX_RUN_MODE_SEQ)
		{
			m_pgmEnv.Test_Simulator.SRM_RunMode_Step = pCtrl->Value;
		}
		break;

	case  6:
		// (Test)Mode
		if (pCtrl->Value == 0)
		{
			memset((INT08U*)&m_pgmEnv.Test_Simulator, 0, sizeof(Test_Simulator_t));
		}
		else if (pCtrl->Value == 1)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			if (m_pgmEnv.Test_Simulator.Goods_State_Mode == 0)
			{
				m_pgmEnv.Test_Simulator.GCP_Change_Mode_Disable = 1;

				m_pgmEnv.Test_Simulator.Goods_State_Mode = 1;

				m_pgmEnv.Test_Simulator.DI_Test_Mode = 0;
				m_pgmEnv.Test_Simulator.DI_Test_State = 0;
				/*
				m_pgmEnv.Test_Simulator.DSTx_Test_Mode = 0;
				m_pgmEnv.Test_Simulator.ODSTx_Test_Mode = 0;
				m_pgmEnv.Test_Simulator.InterLock_Test_Mode = 0;
				*/

				m_St.Inv_St[INV_FORK_1].Status1.GoodsFlag_Or_MoveHome = 0;
			}
		}
		else if (pCtrl->Value == 2)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			if (m_pgmEnv.Test_Simulator.DI_Test_Mode == 0)
			{
				m_pgmEnv.Test_Simulator.GCP_Change_Mode_Disable = 1;

				m_pgmEnv.Test_Simulator.DI_Test_Mode = DI_TEST_DSTx;
				m_pgmEnv.Test_Simulator.DI_Test_State = 0;
				/*
				m_pgmEnv.Test_Simulator.Goods_State_Mode = 0;
				m_pgmEnv.Test_Simulator.DSTx_Test_Mode = 1;
				m_pgmEnv.Test_Simulator.ODSTx_Test_Mode = 0;
				m_pgmEnv.Test_Simulator.InterLock_Test_Mode = 0;
				m_pgmEnv.Test_Simulator.DI_Test_State = 0;
				*/
			}
		}
		else if (pCtrl->Value == 3)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			if (m_pgmEnv.Test_Simulator.DI_Test_Mode == 0)
			{
				m_pgmEnv.Test_Simulator.GCP_Change_Mode_Disable = 1;

				m_pgmEnv.Test_Simulator.DI_Test_Mode = DI_TEST_ODSTx;
				m_pgmEnv.Test_Simulator.DI_Test_State = 0;
				/*
				m_pgmEnv.Test_Simulator.Goods_State_Mode = 0;
				m_pgmEnv.Test_Simulator.DSTx_Test_Mode = 0;
				m_pgmEnv.Test_Simulator.ODSTx_Test_Mode = 1;
				m_pgmEnv.Test_Simulator.InterLock_Test_Mode = 0;

				m_pgmEnv.Test_Simulator.DI_Test_State = 0;
				*/
			}
		}
		else if (pCtrl->Value == 4)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			if (m_pgmEnv.Test_Simulator.DI_Test_Mode == 0)
			{
				m_pgmEnv.Test_Simulator.GCP_Change_Mode_Disable = 1;

				m_pgmEnv.Test_Simulator.DI_Test_Mode = DI_TEST_INTERLOCK;
				m_pgmEnv.Test_Simulator.DI_Test_State = 0;
				/*
				m_pgmEnv.Test_Simulator.Goods_State_Mode = 0;
				m_pgmEnv.Test_Simulator.DSTx_Test_Mode = 0;
				m_pgmEnv.Test_Simulator.ODSTx_Test_Mode = 0;
				m_pgmEnv.Test_Simulator.InterLock_Test_Mode = 1;

				m_pgmEnv.Test_Simulator.DI_Test_State = 0;
				*/
			}
		}
		else if (pCtrl->Value == 5)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			m_pgmEnv.Test_Simulator.GCP_Change_Mode_Disable = 1;

			m_pgmEnv.Test_Simulator.HMI_Test_Mode = 1;
			m_pgmEnv.Test_Simulator.HMI_Test_Fork1_Left_Pos = 0;
			m_pgmEnv.Test_Simulator.HMI_Test_Fork1_Right_Pos = 0;
			m_pgmEnv.Test_Simulator.HMI_Test_ManualKey = 0;
		}
		else if (pCtrl->Value == 6)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			m_pgmEnv.Test_Simulator.GCP_Change_Mode_Disable = 1;

			m_pgmEnv.Test_Simulator.Test_Manual_Mode = 1;
			m_pgmEnv.Test_Simulator.Test_Manual_Mode_Ctr ^= 1;
		}
		else if (pCtrl->Value == 7)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			m_pgmEnv.Test_Simulator.GCP_Change_Mode_Disable = 1;
		}
		else if (pCtrl->Value == 8)
		{
			// 비상 정지 입력 시험
			if (m_pgmEnv.Test_Simulator.DI_Test_Mode == 0)
			{
				m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

				m_pgmEnv.Test_Simulator.DI_Test_Mode = DI_TEST_EM;
				m_pgmEnv.Test_Simulator.DI_Test_State = 0;
				//m_pgmEnv.Test_Simulator.DI_Test_Mode == DI_TEST_EM = 1;
			}
		}
		else if (pCtrl->Value == 9)
		{
			if (m_pgmEnv.Test_Simulator.DI_Test_Mode == 0)
			{
				m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

				m_pgmEnv.Test_Simulator.DI_Test_Mode = DI_TEST_LIMIT;
				m_pgmEnv.Test_Simulator.DI_Test_State = 0;
				//m_pgmEnv.Test_Simulator.DI_Test_Mode == DI_TEST_EM = 1;
			}
		}
		else if (pCtrl->Value == 11)
		{
			if (m_pgmEnv.Test_Simulator.Test_Fault_Warning == 0)
			{
				m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

				m_pgmEnv.Test_Simulator.Test_Fault_Warning = 1;
			}
		}
		else if (pCtrl->Value == 22)
		{
			if (m_pgmEnv.Test_Simulator.Clear_OperationInfo == 0)
			{
				m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

				m_pgmEnv.Test_Simulator.Clear_OperationInfo = 1;
			}
		}
		else if (pCtrl->Value == 1000)
		{
			memset(&m_TestStatus.St[0], 0, sizeof(INT32U) * 32);
			memset(&m_TestStatus.St2[0], 0, sizeof(INT32U) * 32);
		}
		break;

	case  7:
		// (Test)State
		if (m_pgmEnv.Test_Simulator.Goods_State_Mode == 1)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			if (pCtrl->Value == 1)
			{
				m_St.Inv_St[INV_FORK_1].Status1.GoodsFlag_Or_MoveHome = 1;
			}
			else
			{
				m_St.Inv_St[INV_FORK_1].Status1.GoodsFlag_Or_MoveHome = 0;
			}
		}
		else if (m_pgmEnv.Test_Simulator.Clear_OperationInfo == 1)
		{
			if (pCtrl->Value == 9300)
			{
				m_pgmEnv.Test_Simulator.Clear_OperationInfo = 0;

				Clear_Operation_Info_Data();
			}
		}
		else if (m_pgmEnv.Test_Simulator.DI_Test_Mode == DI_TEST_EM)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			if (pCtrl->Value == 1)
			{
				m_pgmEnv.Test_Simulator.DI_Test_State = 1;
			}
			else
			{
				m_pgmEnv.Test_Simulator.DI_Test_State = 0;
			}
		}
		else if (m_pgmEnv.Test_Simulator.HMI_Test_Mode == 1)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			if (pCtrl->Value == 0)
			{
				m_pgmEnv.Test_Simulator.HMI_Test_Fork1_Left_Pos = 0;
				m_pgmEnv.Test_Simulator.HMI_Test_Fork1_Right_Pos = 0;
			}
			else if (pCtrl->Value == 1)
			{
				m_pgmEnv.Test_Simulator.HMI_Test_Fork1_Left_Pos = 1;
				m_pgmEnv.Test_Simulator.HMI_Test_Fork1_Right_Pos = 0;
			}
			else if (pCtrl->Value == 2)
			{
				m_pgmEnv.Test_Simulator.HMI_Test_Fork1_Left_Pos = 0;
				m_pgmEnv.Test_Simulator.HMI_Test_Fork1_Right_Pos = 1;
			}
		}
		else if (m_pgmEnv.Test_Simulator.DI_Test_Mode == DI_TEST_LIMIT)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			if (pCtrl->Value == 0)
			{
				// 전체 OFF
				m_pgmEnv.Test_Simulator.DI_Test_State = 0;
			}
			else if (pCtrl->Value == 1)
			{
				// LST 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[0];
			}
			else if (pCtrl->Value == 2)
			{
				// TST 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[1];
			}
			else if (pCtrl->Value == 3)
			{
				// LSTH 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[2];
			}
			else if (pCtrl->Value == 4)
			{
				// LSTE 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[3];
			}
			else if (pCtrl->Value == 5)
			{
				// TSTH 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[4];
			}
			else if (pCtrl->Value == 6)
			{
				// TSTE 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[5];
			}
		}
		else if (m_pgmEnv.Test_Simulator.DI_Test_Mode == DI_TEST_DSTx)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			if (pCtrl->Value == 0)
			{
				// 이중입고 센서 전체 OFF
				m_pgmEnv.Test_Simulator.DI_Test_State = 0;
			}
			else if (pCtrl->Value == 1)
			{
				// DSTL1 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[0];
			}
			else if (pCtrl->Value == 2)
			{
				// DSTR1 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[1];
			}
			else if (pCtrl->Value == 3)
			{
				// DSTLe1 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[2];
			}
			else if (pCtrl->Value == 4)
			{
				// DSTRe1 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[3];
			}
			else if (pCtrl->Value == 5)
			{
				// DSTLR1 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[4];
			}
			else if (pCtrl->Value == 6)
			{
				// DSTRR1 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[5];
			}
		}
		else if (m_pgmEnv.Test_Simulator.DI_Test_Mode == DI_TEST_ODSTx)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			if (pCtrl->Value == 0)
			{
				// 전체 OFF
				m_pgmEnv.Test_Simulator.DI_Test_State = 0;
			}
			else if (pCtrl->Value == 1)
			{
				// ODSTL1 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[0];
			}
			else if (pCtrl->Value == 2)
			{
				// ODSTR1 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[1];
			}
		}
		else if (m_pgmEnv.Test_Simulator.DI_Test_Mode == DI_TEST_INTERLOCK )
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			if (pCtrl->Value == 0)
			{
				// 전체 OFF
				m_pgmEnv.Test_Simulator.DI_Test_State = 0;
			}
			else if (pCtrl->Value == 1)
			{
				// CVOK1 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[0];
			}
			else if (pCtrl->Value == 2)
			{
				// CVOK2 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[1];
			}
			else if (pCtrl->Value == 3)
			{
				// CVOK3 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[2];
			}
			else if (pCtrl->Value == 4)
			{
				// CVOK4 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[3];
			}
			else if (pCtrl->Value == 5)
			{
				// CVOK5 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[4];
			}
			else if (pCtrl->Value == 6)
			{
				// CVOK6 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[5];
			}
			else if (pCtrl->Value == 7)
			{
				// CVOK7 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[6];
			}
			else if (pCtrl->Value == 8)
			{
				// CVOK8 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[7];
			}
		}
		else if (m_pgmEnv.Test_Simulator.Test_Fault_Warning == 1)
		{
			if (pCtrl->Value == 1)
			{
				save_error_code(m_pgmEnv.Test_Simulator.Test_Fault_MainCode, m_pgmEnv.Test_Simulator.Test_Fault_SubCode, 0);
			}
			else if (pCtrl->Value == 2)
			{	
				Event_Warning_Code(m_pgmEnv.Test_Simulator.Test_Fault_MainCode, m_pgmEnv.Test_Simulator.Test_Fault_SubCode, 0);
			}
		}
		break;

	case  8:
		// (Test)Control_1
		if (m_pgmEnv.Test_Simulator.HMI_Test_Mode == 1)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			if (pCtrl->Value == 0)
			{
				m_pgmEnv.Test_Simulator.HMI_Test_ManualKey = 0;
			}
			else
			{
				m_pgmEnv.Test_Simulator.HMI_Test_ManualKey = (INT16U)cbits16[pCtrl->Value - 1];
			}
		}
		else if (m_pgmEnv.Test_Simulator.Test_Fault_Warning == 1)
		{
			m_pgmEnv.Test_Simulator.Test_Fault_MainCode = pCtrl->Value;
		}
		break;

	case  9:
		// (Test)Control_2
		if (m_pgmEnv.Test_Simulator.Test_Fault_Warning == 1)
		{
			m_pgmEnv.Test_Simulator.Test_Fault_SubCode = pCtrl->Value;
		}
		break;

	case 10:
		if (pCtrl->Value == 1)
		{
			All_Clear_TestStatus();
		}
		else if (pCtrl->Value == 2)
		{
			All_Clear_TestControl();
		}
		break;
	}
#else
// 	Set_TestStatus(DEBUG_STR_63, pCtrl->Index);
// 	Set_TestStatus(DEBUG_STR_64, pCtrl->Value);

	switch (pCtrl->Index)
	{
	case  1:
		if (m_pgmEnv.Enable_Setup_Move_Position)
		{
			Travel_Setup_Move_Position_Start((INT32S)pCtrl->Value);
		}
		break;

	case  2:
		if (m_pgmEnv.Enable_Setup_Move_Position == 1)
		{
			Lift_Setup_Move_Position_Start((INT32S)pCtrl->Value);
		}
		else if ((m_pgmEnv.Enable_Setup_Move_Position == 2) \
			|| (m_pgmEnv.Enable_Setup_Move_Position == 3))
		{
			Lift_Setup_Move_Level_Start((INT32S)pCtrl->Value);
		}
		break;

	case  3:
		if (m_pgmEnv.Enable_Setup_Move_Position == 1)
		{
			Fork_Setup_Move_Position_Start((INT32S)pCtrl->Value);
		}
		else if ((m_pgmEnv.Enable_Setup_Move_Position == 2) \
			|| (m_pgmEnv.Enable_Setup_Move_Position == 3))
		{
			Travel_Setup_Move_Bay_Start((INT32S)pCtrl->Value);
		}
		break;

	case  4:
		/*
		++s_TestVal;
		Set_TestStatus(DEBUG_STR_52, pCtrl->Value);
		Set_TestStatus(DEBUG_STR_53, s_TestVal);
		*/
		if ((m_St.SRM_Mode.Bit.Setup == 1) && (m_St.SRM_Mode.Bit.Force == 0))
		{
			if (pCtrl->Value == 9300)
			{
				m_pgmEnv.Enable_Setup_Move_Position = 1;
				m_pgmEnv.Enable_Setup_Move_Position_Timer = m_pgmEnv.timer1ms;
			}
			else if (pCtrl->Value == 9301)
			{
				m_pgmEnv.Enable_Setup_Move_Position = 2;
				m_pgmEnv.Enable_Setup_Move_Position_Timer = m_pgmEnv.timer1ms;
			}
			else if (pCtrl->Value == 9302)
			{
				m_pgmEnv.Enable_Setup_Move_Position = 3;
				m_pgmEnv.Enable_Setup_Move_Position_Timer = m_pgmEnv.timer1ms;
			}
			else if (pCtrl->Value == 0)
			{
				m_pgmEnv.Enable_Setup_Move_Position = 0;
			}
		}
		else
		{
			if (pCtrl->Value == 0)
			{
				m_pgmEnv.Enable_Setup_Move_Position = 0;
			}
		} 
		break;

	case  5:
		INT08U nInverter = pCtrl->Value - 1;

		if (Check_Motor_BrakeOn(nInverter))
		{
			Motor_Brake_Release(nInverter);
		}
		else
		{
			Motor_Brake_Enable(nInverter);
		}

		asm volatile("NOP");
		break;

	case  6:
		// (Test)Mode
		if (pCtrl->Value == 0)
		{
			memset((INT08U*)&m_pgmEnv.Test_Simulator, 0, sizeof(Test_Simulator_t));
		}
		else if (pCtrl->Value == 1)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			if (m_pgmEnv.Test_Simulator.Goods_State_Mode == 0)
			{
				m_pgmEnv.Test_Simulator.GCP_Change_Mode_Disable = 1;

				m_pgmEnv.Test_Simulator.Goods_State_Mode = 1;

				m_pgmEnv.Test_Simulator.DI_Test_Mode = 0;
				m_pgmEnv.Test_Simulator.DI_Test_State = 0;
				/*
				m_pgmEnv.Test_Simulator.DSTx_Test_Mode = 0;
				m_pgmEnv.Test_Simulator.ODSTx_Test_Mode = 0;
				m_pgmEnv.Test_Simulator.InterLock_Test_Mode = 0;
				*/

				m_St.Inv_St[INV_FORK_1].Status1.GoodsFlag_Or_MoveHome = 0;
			}
		}
		else if (pCtrl->Value == 2)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			if (m_pgmEnv.Test_Simulator.DI_Test_Mode == 0)
			{
				m_pgmEnv.Test_Simulator.GCP_Change_Mode_Disable = 1;

				m_pgmEnv.Test_Simulator.DI_Test_Mode = DI_TEST_DSTx;
				m_pgmEnv.Test_Simulator.DI_Test_State = 0;
				/*
				m_pgmEnv.Test_Simulator.Goods_State_Mode = 0;
				m_pgmEnv.Test_Simulator.DSTx_Test_Mode = 1;
				m_pgmEnv.Test_Simulator.ODSTx_Test_Mode = 0;
				m_pgmEnv.Test_Simulator.InterLock_Test_Mode = 0;
				m_pgmEnv.Test_Simulator.DI_Test_State = 0;
				*/
			}
		}
		else if (pCtrl->Value == 3)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			if (m_pgmEnv.Test_Simulator.DI_Test_Mode == 0)
			{
				m_pgmEnv.Test_Simulator.GCP_Change_Mode_Disable = 1;

				m_pgmEnv.Test_Simulator.DI_Test_Mode = DI_TEST_ODSTx;
				m_pgmEnv.Test_Simulator.DI_Test_State = 0;
				/*
				m_pgmEnv.Test_Simulator.Goods_State_Mode = 0;
				m_pgmEnv.Test_Simulator.DSTx_Test_Mode = 0;
				m_pgmEnv.Test_Simulator.ODSTx_Test_Mode = 1;
				m_pgmEnv.Test_Simulator.InterLock_Test_Mode = 0;

				m_pgmEnv.Test_Simulator.DI_Test_State = 0;
				*/
			}
		}
		else if (pCtrl->Value == 4)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			if (m_pgmEnv.Test_Simulator.DI_Test_Mode == 0)
			{
				m_pgmEnv.Test_Simulator.GCP_Change_Mode_Disable = 1;

				m_pgmEnv.Test_Simulator.DI_Test_Mode = DI_TEST_INTERLOCK;
				m_pgmEnv.Test_Simulator.DI_Test_State = 0;
				/*
				m_pgmEnv.Test_Simulator.Goods_State_Mode = 0;
				m_pgmEnv.Test_Simulator.DSTx_Test_Mode = 0;
				m_pgmEnv.Test_Simulator.ODSTx_Test_Mode = 0;
				m_pgmEnv.Test_Simulator.InterLock_Test_Mode = 1;

				m_pgmEnv.Test_Simulator.DI_Test_State = 0;
				*/
			}
		}
		else if (pCtrl->Value == 5)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			m_pgmEnv.Test_Simulator.GCP_Change_Mode_Disable = 1;

			m_pgmEnv.Test_Simulator.HMI_Test_Mode = 1;
			m_pgmEnv.Test_Simulator.HMI_Test_Fork1_Left_Pos = 0;
			m_pgmEnv.Test_Simulator.HMI_Test_Fork1_Right_Pos = 0;
			m_pgmEnv.Test_Simulator.HMI_Test_ManualKey = 0;
		}
		else if (pCtrl->Value == 6)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			m_pgmEnv.Test_Simulator.GCP_Change_Mode_Disable = 1;

			m_pgmEnv.Test_Simulator.Test_Manual_Mode = 1;
			m_pgmEnv.Test_Simulator.Test_Manual_Mode_Ctr ^= 1;
		}
		else if (pCtrl->Value == 7)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			m_pgmEnv.Test_Simulator.GCP_Change_Mode_Disable = 1;
		}
		else if (pCtrl->Value == 8)
		{
			// 비상 정지 입력 시험
			if (m_pgmEnv.Test_Simulator.DI_Test_Mode == 0)
			{
				m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

				m_pgmEnv.Test_Simulator.DI_Test_Mode = DI_TEST_EM;
				m_pgmEnv.Test_Simulator.DI_Test_State = 0;
				//m_pgmEnv.Test_Simulator.DI_Test_Mode == DI_TEST_EM = 1;
			}
		}
		else if (pCtrl->Value == 9)
		{
			if (m_pgmEnv.Test_Simulator.DI_Test_Mode == 0)
			{
				m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

				m_pgmEnv.Test_Simulator.DI_Test_Mode = DI_TEST_LIMIT;
				m_pgmEnv.Test_Simulator.DI_Test_State = 0;
				//m_pgmEnv.Test_Simulator.DI_Test_Mode == DI_TEST_EM = 1;
			}
		}
		else if (pCtrl->Value == 10)
		{
			if (m_ExtSEnv.Machine.mType.Inverter_Vendor == INV_VENDOR_SEW_VER2_SYNC_TRAVEL)
			{
				if (m_pgmEnv.Test_Simulator.Test_Sync_Travel_Enable == 0)
				{
					if (m_pgmEnv.Trial_Run_Mode)
					{
						m_pgmEnv.Test_Simulator.Test_Sync_Travel_Enable = 1;

						m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;
					}
				}
			}
		}
		else if (pCtrl->Value == 12)
		{
			m_pgmEnv.Set_HMI_SysTime_Flag = 1;
		}
		/*
		else if (pCtrl->Value == 13)
		{
			if (m_pgmEnv.Test_Simulator.HMI_Set_Flag != 2)
			{
				m_pgmEnv.Test_Simulator.HMI_Set_Flag = 2;
				m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;
			}
		}
		*/
		else if (pCtrl->Value == 22)
		{
			if (m_pgmEnv.Test_Simulator.Clear_OperationInfo == 0)
			{
				m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

				m_pgmEnv.Test_Simulator.Clear_OperationInfo = 1;
			}
		}
		else if (pCtrl->Value == 1000)
		{
			memset(&m_TestStatus.St[0], 0, sizeof(INT32U) * 32);
			memset(&m_TestStatus.St2[0], 0, sizeof(INT32U) * 32);
		}
		break;

	case  7:
		// (Test)State
		if (m_pgmEnv.Test_Simulator.Goods_State_Mode == 1)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			if (pCtrl->Value == 1)
			{
				m_St.Inv_St[INV_FORK_1].Status1.GoodsFlag_Or_MoveHome = 1;
			}
			else
			{
				m_St.Inv_St[INV_FORK_1].Status1.GoodsFlag_Or_MoveHome = 0;
			}
		}
		else if (m_pgmEnv.Test_Simulator.Clear_OperationInfo == 1)
		{
			if (pCtrl->Value == 9300)
			{
				m_pgmEnv.Test_Simulator.Clear_OperationInfo = 0;

				Clear_Operation_Info_Data();
			}
		}
		else if (m_pgmEnv.Test_Simulator.DI_Test_Mode == DI_TEST_EM)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			if (pCtrl->Value == 1)
			{
				m_pgmEnv.Test_Simulator.DI_Test_State = 1;
			}
			else
			{
				m_pgmEnv.Test_Simulator.DI_Test_State = 0;
			}
		}
		else if (m_pgmEnv.Test_Simulator.HMI_Test_Mode == 1)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			if (pCtrl->Value == 0)
			{
				m_pgmEnv.Test_Simulator.HMI_Test_Fork1_Left_Pos = 0;
				m_pgmEnv.Test_Simulator.HMI_Test_Fork1_Right_Pos = 0;
			}
			else if (pCtrl->Value == 1)
			{
				m_pgmEnv.Test_Simulator.HMI_Test_Fork1_Left_Pos = 1;
				m_pgmEnv.Test_Simulator.HMI_Test_Fork1_Right_Pos = 0;
			}
			else if (pCtrl->Value == 2)
			{
				m_pgmEnv.Test_Simulator.HMI_Test_Fork1_Left_Pos = 0;
				m_pgmEnv.Test_Simulator.HMI_Test_Fork1_Right_Pos = 1;
			}
		}
		else if (m_pgmEnv.Test_Simulator.DI_Test_Mode == DI_TEST_LIMIT)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			if (pCtrl->Value == 0)
			{
				// 전체 OFF
				m_pgmEnv.Test_Simulator.DI_Test_State = 0;
			}
			else if (pCtrl->Value == 1)
			{
				// LST 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[0];
			}
			else if (pCtrl->Value == 2)
			{
				// TST 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[1];
			}
			else if (pCtrl->Value == 3)
			{
				// LSTH 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[2];
			}
			else if (pCtrl->Value == 4)
			{
				// LSTE 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[3];
			}
			else if (pCtrl->Value == 5)
			{
				// TSTH 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[4];
			}
			else if (pCtrl->Value == 6)
			{
				// TSTE 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[5];
			}
		}
		else if (m_pgmEnv.Test_Simulator.DI_Test_Mode == DI_TEST_DSTx)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			if (pCtrl->Value == 0)
			{
				// 이중입고 센서 전체 OFF
				m_pgmEnv.Test_Simulator.DI_Test_State = 0;
			}
			else if (pCtrl->Value == 1)
			{
				// DSTL1 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[0];
			}
			else if (pCtrl->Value == 2)
			{
				// DSTR1 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[1];
			}
			else if (pCtrl->Value == 3)
			{
				// DSTLe1 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[2];
			}
			else if (pCtrl->Value == 4)
			{
				// DSTRe1 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[3];
			}
			else if (pCtrl->Value == 5)
			{
				// DSTLR1 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[4];
			}
			else if (pCtrl->Value == 6)
			{
				// DSTRR1 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[5];
			}
		}
		else if (m_pgmEnv.Test_Simulator.DI_Test_Mode == DI_TEST_ODSTx)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			if (pCtrl->Value == 0)
			{
				// 전체 OFF
				m_pgmEnv.Test_Simulator.DI_Test_State = 0;
			}
			else if (pCtrl->Value == 1)
			{
				// ODSTL1 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[0];
			}
			else if (pCtrl->Value == 2)
			{
				// ODSTR1 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[1];
			}
		}
		else if (m_pgmEnv.Test_Simulator.DI_Test_Mode == DI_TEST_INTERLOCK)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			if (pCtrl->Value == 0)
			{
				// 전체 OFF
				m_pgmEnv.Test_Simulator.DI_Test_State = 0;
			}
			else if (pCtrl->Value == 1)
			{
				// CVOK1 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[0];
			}
			else if (pCtrl->Value == 2)
			{
				// CVOK2 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[1];
			}
			else if (pCtrl->Value == 3)
			{
				// CVOK3 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[2];
			}
			else if (pCtrl->Value == 4)
			{
				// CVOK4 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[3];
			}
			else if (pCtrl->Value == 5)
			{
				// CVOK5 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[4];
			}
			else if (pCtrl->Value == 6)
			{
				// CVOK6 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[5];
			}
			else if (pCtrl->Value == 7)
			{
				// CVOK7 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[6];
			}
			else if (pCtrl->Value == 8)
			{
				// CVOK8 제어
				m_pgmEnv.Test_Simulator.DI_Test_State ^= cbits[7];
			}
		}
		break;

	case  8:
		// (Test)Control_1
		if (m_pgmEnv.Test_Simulator.HMI_Test_Mode == 1)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			if (pCtrl->Value == 0)
			{
				m_pgmEnv.Test_Simulator.HMI_Test_ManualKey = 0;
			}
			else
			{
				m_pgmEnv.Test_Simulator.HMI_Test_ManualKey = (INT16U)cbits16[pCtrl->Value - 1];
			}
		}
		else if (m_pgmEnv.Test_Simulator.Test_Sync_Travel_Enable == 1)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			if (pCtrl->Value == 0)
			{
				m_pgmEnv.Test_Simulator.Test_Sync_Travel_Control.W = 0;
			}
			else if (pCtrl->Value == 1)
			{
				m_pgmEnv.Test_Simulator.Test_Sync_Travel_Control.B.Disable_Member1 ^= 1;
			}
			else if (pCtrl->Value == 2)
			{
				m_pgmEnv.Test_Simulator.Test_Sync_Travel_Control.B.Disable_Member2 ^= 1;
			}
			else if (pCtrl->Value == 3)
			{
				m_pgmEnv.Test_Simulator.Test_Sync_Travel_Control.B.Disable_Member3 ^= 1;
			}
			else if (pCtrl->Value == 4)
			{
				m_pgmEnv.Test_Simulator.Test_Sync_Travel_Control.B.Disable_Member4 ^= 1;
			}
		}
		break;

	case  9:
		// (Test)Control_2
		if (m_pgmEnv.Test_Simulator.Test_Sync_Travel_Enable == 1)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			if (pCtrl->Value == 0)
			{
				m_pgmEnv.Test_Simulator.Test_Sync_Travel_Control.W = 0;
			}
			else if (pCtrl->Value == 1)
			{
				m_pgmEnv.Test_Simulator.Test_Sync_Travel_Control.B.Release_brake_without_enable_member1 ^= 1;
			}
			else if (pCtrl->Value == 2)
			{
				m_pgmEnv.Test_Simulator.Test_Sync_Travel_Control.B.Release_brake_without_enable_member2 ^= 1;
			}
			else if (pCtrl->Value == 3)
			{
				m_pgmEnv.Test_Simulator.Test_Sync_Travel_Control.B.Release_brake_without_enable_member3 ^= 1;
			}
			else if (pCtrl->Value == 4)
			{
				m_pgmEnv.Test_Simulator.Test_Sync_Travel_Control.B.Release_brake_without_enable_member4 ^= 1;
			}
		}
		/*
		if (m_pgmEnv.Test_Simulator.HMI_Test_Mode == 1)
		{
			m_pgmEnv.Test_Simulator.Auto_Release_Timer = m_pgmEnv.timer1ms;

			if (pCtrl->Value == 0)
			{
				m_pgmEnv.Test_Simulator.HMI_Test_EventKey = 0;
			}
			else
			{
				m_pgmEnv.Test_Simulator.HMI_Test_EventKey = (INT32U)cbits32[pCtrl->Value - 1];
			}
		}
		*/
		break;

	case 10:
		/*
		if (pCtrl->Value == 1234)
		{
			memset(&m_TestStatus.St[0], 0, sizeof(INT32U) * 32);
			memset(&m_TestStatus.St2[0], 0, sizeof(INT32U) * 32);
			memset(&m_TestStatus.Ctrl[0], 0, sizeof(INT32U) * 16);
		}
		*/

		/*
		if (pCtrl->Value == 123456789)
		{
			sst26_chiperase();
		}
		*/
		break;
	}
#endif

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);                                        // STX : 0x16 0x16 0x16 0x16
	crcClear(port);                                                      // Clear CRC
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 0);
	txCRCPort(port);                                                      // Transmit CRC
	rsPutmPort(port, FRAME_ETX, 1);                                        // ETX : 0xF5
	sendTxBuf(port);
}


void rxGraphRequest(INT08U port, TMLComPTR pCom)
{
	INT08U nReqMode = 0;
	INT08U nInx = 0;

	INT08U nGraph_Index = 0;
	INT08U nGraph_Index1 = 0;

	INT16U nGraph_Start = 0;

	INT08U nGraph_Type = 0;
	INT08U nGraph_Interval = 0;
	INT32U nGraph_Start_mm = 0;
	//INT08U group;

	if (m_St.Inv_St[INV_TRAVEL].Status1.MoveFlag)	return;
	if (m_St.Inv_St[INV_HOIST].Status1.MoveFlag)	return;
	if (m_St.Inv_St[INV_FORK_1].Status1.MoveFlag)	return;

	nReqMode = pCom->Data[0];

	if (nReqMode == 0)
	{
		// 0: 조회 
		nInx = pCom->Data[1];

		nGraph_Index = nInx / 2;
		nGraph_Index1 = nInx % 2;
		/*
		m_TestStatus.Ctrl[DEBUG_CTR_3] = nInx;
		m_TestStatus.Ctrl[DEBUG_CTR_4] = nGraph_Index;
		m_TestStatus.Ctrl[DEBUG_CTR_5] = nGraph_Index1;
		*/
		if (nGraph_Index < MAX_GRAPH_COUNT)
		{
			if (nGraph_Index1 == 1)
			{
				nGraph_Start = MAX_GRAPH_DATA_COUNT / 2;
			}

			//m_TestStatus.Ctrl[DEBUG_CTR_6] = nGraph_Start;

			clearTxBuf(port);
			rsPutmPort(port, FRAME_STX, 4);                                      // STX : 0x16 0x16 0x16 0x16
			crcClear(port);                                                      // Clear CRC
			txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 1408);  // 1402
			txPutcPort(port, nInx);
			txPutcPort(port, 0);
			txPutcPort(port, m_BKSram.Graph_Type);
			txPutcPort(port, m_BKSram.Graph_Interval);
			txPutlPort(port, m_BKSram.Graph_Start_mm);
			txPutnPort(port, (INT08U*)&m_GraphLog.GraphData[nGraph_Index][nGraph_Start], 350 * 4);    // 700*2
			txCRCPort(port);                                                      // Transmit CRC
			rsPutmPort(port, FRAME_ETX, 1);                                        // ETX : 0xF5
			sendTxBuf(port);
		}
	}
	else if (nReqMode == 1)
	{
		// 1: 기록 설정
		nGraph_Type = pCom->Data[3];
		nGraph_Interval = pCom->Data[4];
		memcpy((INT08U*)&nGraph_Start_mm, (INT08U*)&pCom->Data[5], sizeof(INT32U));

		Graph_Setup(nGraph_Type, nGraph_Interval, nGraph_Start_mm);

		clearTxBuf(port);
		rsPutmPort(port, FRAME_STX, 4);                                      // STX : 0x16 0x16 0x16 0x16
		crcClear(port);                                                      // Clear CRC
		txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 1408);  // 8 + 1400
		txPutcPort(port, nInx);
		txPutcPort(port, 0);
		txPutcPort(port, m_BKSram.Graph_Type);
		txPutcPort(port, m_BKSram.Graph_Interval);
		txPutlPort(port, m_BKSram.Graph_Start_mm);
		txPutnPort(port, (INT08U*)&m_GraphLog.GraphData[nInx][0], 350 * sizeof(INT32S));    // 350 * 4
		txCRCPort(port);                                                      // Transmit CRC
		rsPutmPort(port, FRAME_ETX, 1);                                        // ETX : 0xF5
		sendTxBuf(port);
	}
	else if (nReqMode == 2)
	{
		// 2: 기록설정 불러오기
		clearTxBuf(port);
		rsPutmPort(port, FRAME_STX, 4);                                      // STX : 0x16 0x16 0x16 0x16
		crcClear(port);                                                      // Clear CRC
		txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 1408);  // 8 + 1400
		txPutcPort(port, nInx);
		txPutcPort(port, 0);
		txPutcPort(port, m_BKSram.Graph_Type);
		txPutcPort(port, m_BKSram.Graph_Interval);
		txPutlPort(port, m_BKSram.Graph_Start_mm);
		txPutnPort(port, (INT08U*)&m_GraphLog.GraphData[nInx][0], 350 * sizeof(INT32S));    // 350 * 4 = 1400
		txCRCPort(port);					// Transmit CRC
		rsPutmPort(port, FRAME_ETX, 1);		// ETX : 0xF5
		sendTxBuf(port);
	}
}

void rxManualOutCTR_Request(INT08U port, TMLComPTR pCom)
{
	INT08U i = 0, nByteIdx = 0, nBitIndex = 0;
	INT08U nFlag = 0, nResult = 0x01, nID = 0, nMode = 0, nControl = 0;

	if ((m_St.SRM_Status2.Bit.ManualSW) || (m_pgmEnv.Trial_Run_Mode))
	{
		nFlag = pCom->Data[0];

		if (nFlag & cbits[0])
		{
			// 수동 출력 제어 모드 제어
			nID = pCom->Data[1];
			nMode = pCom->Data[2];
			if (nID == 255)
			{
				// 전체 출력 수동모드 제어
				nResult = 0;
				for (i = 0; i < MAX_DO_CNT; i++)
				{
					if (i <= OUT_FK1_JOG_L)
					{
						nByteIdx = i / 8;	
						nBitIndex = i % 8;
						
						if (nMode)
						{
							m_St.ManualOutputMode[nByteIdx] |= cbits[nBitIndex];
						}
						else
						{
							m_St.ManualOutputMode[nByteIdx] &= nbits[nBitIndex];
						}
					}
					else
					{
						nByteIdx = (i - OUT_FK1_RESET) / 8;	
						nBitIndex = (i - OUT_FK1_RESET) % 8;
						
						if (nMode)
						{
							m_St.ManualOutputMode2[nByteIdx] |= cbits[nBitIndex];
						}
						else
						{
							m_St.ManualOutputMode2[nByteIdx] &= nbits[nBitIndex];
						}
					}
				}
			}
			else if ((nID > 0) && (nID <= MAX_DO_CNT))
			{
				nResult = 0;

				nID -= 1;

#if DEBUG_MANUAL_OUTPUT
				Set_TestStatus(DEBUG_STR_33, nID);
				Set_TestStatus(DEBUG_STR_34, nMode);
#endif

				if (nID <= OUT_FK1_JOG_L)
				{
					nByteIdx = nID / 8;	
					nBitIndex = nID % 8;

#if DEBUG_MANUAL_OUTPUT
					Set_TestStatus(DEBUG_STR_35, nID);
					Set_TestStatus(DEBUG_STR_36, nByteIdx);
					Set_TestStatus(DEBUG_STR_37, nBitIndex);
#endif
					
					if (nMode)
					{
						m_St.ManualOutputMode[nByteIdx] |= cbits[nBitIndex];
					}
					else
					{
						m_St.ManualOutputMode[nByteIdx] &= nbits[nBitIndex];
					}
				}
				else
				{
					nByteIdx = (nID - OUT_FK1_RESET) / 8;	
					nBitIndex = (nID - OUT_FK1_RESET) % 8;

#if DEBUG_MANUAL_OUTPUT
					Set_TestStatus(DEBUG_STR_35, nID - OUT_FK1_RESET);
					Set_TestStatus(DEBUG_STR_36, nByteIdx);
					Set_TestStatus(DEBUG_STR_37, nBitIndex);
#endif
					
					if (nMode)
					{
						m_St.ManualOutputMode2[nByteIdx] |= cbits[nBitIndex];
					}
					else
					{
						m_St.ManualOutputMode2[nByteIdx] &= nbits[nBitIndex];
					}
				}
			}

		}

		if (nFlag & cbits[1])
		{
			// 수동 출력 제어
			nID = pCom->Data[3];
			nControl = pCom->Data[4];

			//m_TestStatus.St[DEBUG_STR_20] = nID;
			//m_TestStatus.St[DEBUG_STR_21] = nControl;

#if DEBUG_MANUAL_OUTPUT
			Set_TestStatus(DEBUG_STR_49, nID);
			Set_TestStatus(DEBUG_STR_50, nControl);
#endif

			if (nID == 255)
			{
				// 전체 출력 수동모드 제어
				nResult = 0;
				for (i = 0; i < MAX_DO_CNT; i++)
				{
					DO_Control_Manual(i, nControl);
				}
			}
			else if ((nID > 0) && (nID <= MAX_DO_CNT))
			{
				nResult = 0;
				DO_Control_Manual(nID - 1, nControl);
			}
		}
	}

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);                                        // STX : 0x16 0x16 0x16 0x16
	crcClear(port);                                                      // Clear CRC
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 1);
	txPutcPort(port, 0);
	txCRCPort(port);                                                      // Transmit CRC
	rsPutmPort(port, FRAME_ETX, 1);                                        // ETX : 0xF5
	sendTxBuf(port);
}

void CP_Time_Synchronization(INT32U nSysTime_Utc)
{
	static INT08U s_HMI_Time_Init = 0;

	static INT32U s_chkTimer = 0;

	INT32U d_registers[6] = { 0, };

	if (getCalcTimer1ms(s_chkTimer) >= 10000)
	{
		s_chkTimer = m_pgmEnv.timer1ms;

		// 1577840400 : 2020/01/01 01:00:00
		// 2524568399 : 2049/12/31 23:59:59
		if ((nSysTime_Utc >= 1577840400) && (nSysTime_Utc <= 2524568399))
		{
			if ((m_DevStatus.SysTime < (nSysTime_Utc - 10)) || (m_DevStatus.SysTime > (nSysTime_Utc + 10)))
			{
				setTimeDate_Rev2(nSysTime_Utc);

				m_DevStatus.SysTime = getTimeDate_Rev2();
				//m_DevStatus.SysTime = getTimeDate();

				m_St.SysTime = m_DevStatus.SysTime;

				
				if (m_pgmEnv.HMI_Com_Port == HMI_COM_UPLINK)
				{
					if (m_pgmEnv.PortLinkSt[rsHMI_UP_Port])
					{
						m_pgmEnv.Set_HMI_SysTime_Flag = 1;
					}
				}
				else
				{
					if (m_pgmEnv.PortLinkSt[rsHMI_Port])
					{
						m_pgmEnv.Set_HMI_SysTime_Flag = 1;
					}
				}
			}
			else
			{				
				if (s_HMI_Time_Init == 0)
				{
					if (m_pgmEnv.HMI_Com_Port == HMI_COM_UPLINK)
					{
						if (m_pgmEnv.PortLinkSt[rsHMI_UP_Port])
						{
							m_pgmEnv.Set_HMI_SysTime_Flag = 1;
						}
					}
					else
					{
						if (m_pgmEnv.PortLinkSt[rsHMI_Port])
						{
							m_pgmEnv.Set_HMI_SysTime_Flag = 1;
						}
					}
				}
			}
		}
	}
}

void rxStatusReq(INT08U port, TMLComPTR pCom)
{
	//static ControlPanelSTR s_Pre_CP_State;
	//static INT08U s_Pre_KeyState = 0;

	StatusReqSTR* pCmd;

#if DEBUG_MSG
	/*
	INT32U nProcessTime = 0;
	nProcessTime = m_pgmEnv.timer1ms;
	*/
#endif

	if (pCom->Data[0] == 0)
	{
		asm volatile("NOP");
	}
	else
	{
		pCmd = (StatusReqSTR*)&pCom->Data[0];

		if (pCmd->UseFlag & cbits[0])
		{
			CP_Time_Synchronization(pCmd->SysTime);
		}

		if (pCmd->UseFlag & cbits[1])
		{
			m_St.CP_Mode = pCmd->CP_Mode;
			//m_St.CP_State.Data = pCmd->CP_State.Data;
			m_pgmEnv.Recv_CP_State.Data = pCmd->CP_State.Data;

			m_St.CP_State.Bit.HeartBit = pCmd->CP_State.Bit.HeartBit;
		}

		if (pCmd->UseFlag & cbits[2])
		{
			memcpy((INT08U*)m_St.InterLock_CVOK, (INT08U*)pCmd->InterLock_CVOK, sizeof(INT08U) * 8);
		}
	}

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, sizeof(StatusSTR));
	txPutnPort(port, (INT08U*)&m_St, sizeof(StatusSTR));
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);
	sendTxBuf(port);

	++m_pgmEnv.StatusReqCount;

	//++m_TestStatus.Ctrl[DEBUG_CTR_5];

#if DEBUG_MSG
	//printf("[DEBUG_APP] Request SRM Status ProcessTime : %ld ms\r\n", getCalcTimer1ms(nProcessTime));
#endif
}

/**
  * @brief
  * @param  port 수신 포트
  * @param  pCom 수신 데이터
  * @retval None
  */
void rxOperationInfo_Req(INT08U port, TMLComPTR pCom)
{
	INT08U i = 0;
	OperationInfoReqSTR nOperationInfo;

	memset((INT08U*)&nOperationInfo, 0, sizeof(OperationInfoReqSTR));

	for (i = 0; i < 4; i++)
	{
		nOperationInfo.SumTime[i] = m_BKSram.OperationInfo.Operation_Time[i].Sum_Minute;
		nOperationInfo.SumDistance[i] = m_BKSram.OperationInfo.Moving_Distance[i].Sum_Meter;
		nOperationInfo.SumCount[i] = m_BKSram.OperationInfo.BrakeOpen_Count[i];
	}

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, sizeof(OperationInfoReqSTR));
	txPutnPort(port, (INT08U*)&nOperationInfo, sizeof(OperationInfoReqSTR));                  // Data
	txCRCPort(port);                                                      // Transmit CRC
	rsPutmPort(port, FRAME_ETX, 1);                                        // ETX : 0xF5
	sendTxBuf(port);
}

/**
  * @brief
  * @param  port 수신 포트
  * @param  pCom 수신 데이터
  * @retval None
  */
void rxInvertorInfo_Req(INT08U port, TMLComPTR pCom)
{
#if DEBUG_MSG
	/*
	INT32U nProcessTime = 0;
	nProcessTime = m_pgmEnv.timer1ms;
	*/
#endif

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, sizeof(InvertorInfoSTR));
	txPutnPort(port, (INT08U*)&m_Invertor_Info, sizeof(InvertorInfoSTR));                  // Data
	txCRCPort(port);                                                      // Transmit CRC
	rsPutmPort(port, FRAME_ETX, 1);                                        // ETX : 0xF5
	sendTxBuf(port);

#if DEBUG_MSG
	//printf("[DEBUG_APP] Request Invertor Information ProcessTime : %ld ms\r\n", getCalcTimer1ms(nProcessTime));
#endif
}

void rxTaskCmdOrder(INT08U port, TMLComPTR pCom)
{
	TaskOrder* pCmd;

	INT08U Task_FailReason[20] = { 0 };

	INT08U ret_value = 0;

	//INT08U run_st = 0;
	//INT08U plc_flag = 0;
	INT08U i = 0;
	INT08U nForkCenterError = 0;

	if (m_pgmEnv.OrderRejectCondition & cbits[0])
	{
		save_error_code(ERROR1_EMBERGENCY_STOP, 1, 0);
		return;
	}

	if (m_pgmEnv.OrderRejectCondition & cbits[1])
	{
		save_error_code(ERROR1_SAFETY_PULG_ON, 1, 10);
		return;
	}

	if (m_St.SRM_Status2.Bit.ManualSW)
	{
		return;		// 기상반 수동
	}
	
	if (m_St.SRM_Status1.Bit.Fault)
	{
		ret_value = 34;   // 이상상황 발생중
	}
	else if (Check_Fork_Center_Alarm())
	{
		ret_value = 34;		// 포크 중심 이상
	}
	else if (!m_St.SRM_Mode.Bit.Auto)  // 수동모드
	{
		ret_value = 35;   // 수동모드 / 시작Off 동작중
	}
	else if (!(m_St.SRM_Status1.Bit.StartOn))  // 시작On이 아니면
	{
		ret_value = 35;   // 수동모드/시작Off 동작중
	}
	else if ((m_St.ForkWork[0].OrderStatus_Fork == WORK_STATUS_DOING)
		|| (m_St.ForkWork[0].OrderStatus_Fork == WORK_STATUS_STOP)
		|| (m_St.ForkWork[0].OrderStatus_Fork == WORK_STATUS_FAIL))
	{
		ret_value = 33;  // 이전지령 수행중이거나 작업실패
	}

	pCmd = (TaskOrder*)&pCom->Data[0];

	if (ret_value == 0)
	{
		for (i = 0; i < MAX_TASK_COUNT; i++)
		{
			Task_FailReason[i] = 0;

			if (pCmd->TaskWork[i].Cmd)
			{
				if (Check_Task_CellPosition(pCmd->TaskWork[i].Cmd, &pCmd->TaskWork[i].TargetPos))
				{
					Task_FailReason[i] = 1; // 설정범위를 벗어남
				}

				if (Check_Task_Prohibit_Rack(pCmd->TaskWork[i].Cmd, &pCmd->TaskWork[i].TargetPos))
				{
					Task_FailReason[i] = 5; // 금지랙
				}

				if (Check_Task_Special_Rack(pCmd->TaskWork[i].Cmd, \
					& pCmd->TaskWork[i].TargetPos, pCmd->TaskWork[i].GoodsType))
				{
					Task_FailReason[i] = 4; // 스페셜랙 허용화물이 아님
				}

				if (pCmd->TaskWork[i].WorkForkNo != 1)
				{
					Task_FailReason[i] = 2;
				}

				if (Task_FailReason[i] == 0)
				{
					Task_FailReason[i] = SRM_Task_work_cmd(&pCmd->TaskWork[i], i);

					if (Task_FailReason[i])
					{
						ret_value = Task_FailReason[i];
						//break;
					}
				}
				else
				{
					ret_value = Task_FailReason[i];
					//break;
				}

				m_TestStatus.St[i] = Task_FailReason[i];
			}
			else
			{
				//memcpy((INT08U*)&m_St.TaskWork[i], (INT08U*)&pCmd->TaskWork[i], sizeof(TaskCommand));
			}
		}
	}

	if (ret_value == 0)
	{
		if (!m_pgmEnv.SRM_TaskMode)
		{
			for (i = 0; i < MAX_TASK_COUNT; i++)
			{
				if (pCmd->TaskWork[i].Cmd)
				{
					memcpy((INT08U*)&m_St.TaskWork[i], (INT08U*)&pCmd->TaskWork[i], sizeof(TaskCommand));

					m_St.TaskWork[i].OrderState = TASK_STATUS_STAND_BY;
				}
			}

			m_St.Transfer_WorkNo = pCmd->Transfer_WorkNo;
			//m_St.Task_Operation = 1;

			m_pgmEnv.SRM_TaskMode = 1;
			m_pgmEnv.SRM_TaskIndex = 0;

			m_pgmEnv.SRM_RunMode = RUN_SEQ_START;
		}
	}

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 6);
	txPutlPort(port, pCmd->Transfer_WorkNo);
	txPutcPort(port, ret_value);
	txPutcPort(port, 0);
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);
	sendTxBuf(port);

	//m_TestStatus.Ctrl[DEBUG_CTR_1] = ret_value[0];
}


void rxCmdOrder(INT08U port, TMLComPTR pCom)
{
	WorkCmdSTR* pCmd;
	INT08U accept[2] = { 0 };
	INT08U ret_value[2] = { 0 };
	//INT08U run_st = 0;
	//INT08U plc_flag = 0;

	static INT32U s_RecvCount = 0;

	if (m_St.CP_State.Bit.SafetyPlugOn)
	{
		save_error_code(ERROR1_SAFETY_PULG_ON, 1, 2);
		//return;
	}

	/*
	if (m_St.SRM_Status2.Bit.ManualSW)
	{
		Event_Warning_Code(WARNING_CODE_13, 0, 0);
		return;		// 기상반 수동
	}
	*/

	pCmd = (WorkCmdSTR*)&pCom->Data[0];

	if (m_St.SRM_Status1.Bit.Fault)
	{
		ret_value[0] = COMMAND_ERROR_FALUT_STATE;  // 이상 발생
	}
	else if (m_St.SRM_Status2.Bit.ManualSW)
	{
		ret_value[0] = COMMAND_ERROR_MANUAL_SW_ON;
	}
	else if (m_pgmEnv.SRM_RunMode != RUN_SEQ_STAND_BY)
	{
		ret_value[0] = COMMAND_ERROR_EXECUTING_PREVIOUS_COMMAND;
	}
	else if (Check_Fork_Center_Alarm())
	{
		// 24. 08. 09 - 명령 수신시, 포크 중심이 아닌경우 에러로 처리.
		ret_value[0] = COMMAND_ERROR_FORK_CENTER_OFF;
	}
	else if (m_St.SRM_Mode.Bit.Auto == 0)
	{
		ret_value[0] = COMMAND_ERROR_NON_AUTOMATIC_MODE;   // 수동모드
	}
	else
	{
		if (pCmd->OrderCode == ORDER_CODE_MOVE)
		{
			asm volatile("NOP");
		}
		else
		{
			if ((pCmd->OrderCode == ORDER_CODE_STORE)
				|| (pCmd->OrderCode == ORDER_CODE_UNSTORE)
				|| (pCmd->OrderCode == ORDER_CODE_RACK_TO_RACK)
				|| (pCmd->OrderCode == ORDER_CODE_STATION_TO_STATION)
				|| (pCmd->OrderCode == ORDER_CODE_STICKY))
			{
				if (m_St.SRM_Status1.Bit.StartOn == 0)  // 시작On이 아니면
				{
					//Event_Warning_Code(WARNING_CODE_20, 2, 0);
					ret_value[0] = COMMAND_ERROR_NON_ONLINE;
				}

#if DISABLE_ERROR_CARRIER_GOODS_SENSOR
				asm volatile("NOP");
#else
				if (m_St.Inv_St[INV_FORK_1].Status1.GoodsFlag_Or_MoveHome)
				{
					if (m_pgmEnv.SRM_RunMode == RUN_SEQ_STAND_BY)
					{
						// 명령 수행중이 아닌 경우에만 이상 발생.
						// ONLINE LOAD 작업 시작 전 화물 감지상태 (FK1)
						save_error_code(ERROR1_CARRIER_GOODS_SENSOR_2, 3, pCmd->OrderCode);
					}

					ret_value[0] = COMMAND_ERROR_CARGO_DETECTION_STATUS;   // 이상상황
				}
#endif
			}
		}
	}

#if DEBUG_CMD
	/*
	++s_RecvCount;
	if (s_RecvCount > 10000)
	{
		s_RecvCount = 0;
	}

	Set_TestStatus(DEBUG_STR_33, s_RecvCount);
	Set_TestStatus(DEBUG_STR_34, pCmd->OperationFlag);
	Set_TestStatus(DEBUG_STR_35, pCmd->OrderCode);
	Set_TestStatus(DEBUG_STR_36, pCmd->Fork[0].WorkNum);
	Set_TestStatus(DEBUG_STR_37, pCmd->Fork[0].FromCell.Station);
	Set_TestStatus(DEBUG_STR_38, pCmd->Fork[0].FromCell.Row_ID);
	Set_TestStatus(DEBUG_STR_39, pCmd->Fork[0].FromCell.Bay_ID);
	Set_TestStatus(DEBUG_STR_40, pCmd->Fork[0].FromCell.Level_ID);
	Set_TestStatus(DEBUG_STR_41, pCmd->Fork[0].ToCell.Station);
	Set_TestStatus(DEBUG_STR_42, pCmd->Fork[0].ToCell.Row_ID);
	Set_TestStatus(DEBUG_STR_43, pCmd->Fork[0].ToCell.Bay_ID);
	Set_TestStatus(DEBUG_STR_44, pCmd->Fork[0].ToCell.Level_ID);
	*/
#endif
	
	//if ((ret_value[0] == 0) && (ret_value[1] == 0))
	if ((ret_value[0] == 0))
	{
		switch (pCmd->OrderCode)
		{
		case ORDER_CODE_MOVE: 
			// 수동이동 : 작업상태 변경없음
			if ((m_St.ForkWork[0].OrderStatus_Move == WORK_STATUS_DOING))  accept[0] |= cbits[0];

			if (accept[0])
			{
				ret_value[0] = COMMAND_ERROR_EXECUTING_PREVIOUS_COMMAND;
			}
			else
			{
				accept[0] = CheckCmdCellPosition(pCmd->OrderCode, (ForkWorkCmdSTR*)&pCmd->Fork[0]);

				if (accept[0])  ret_value[0] = COMMAND_ERROR_NOT_WITHIN_THE_SET_RANGE;  // 설정범위를 벗어남
			}
			break;

		case ORDER_CODE_STORE: // 입고
		case ORDER_CODE_UNSTORE: // 출고
		case ORDER_CODE_RACK_TO_RACK: // 랙간반송
		case ORDER_CODE_STATION_TO_STATION: //
		case ORDER_CODE_STICKY:				// Sticky
			if (m_St.ForkWork[0].OrderStatus_Fork == WORK_STATUS_DOING)
			{
				ret_value[0] = COMMAND_ERROR_EXECUTING_PREVIOUS_COMMAND;
			}
			else if (m_St.ForkWork[0].OrderStatus_Fork == WORK_STATUS_STOP)
			{
				ret_value[0] = COMMAND_ERROR_PREVIOUS_TASK_PAUSE;
			}
			else if (m_St.ForkWork[0].OrderStatus_Fork == WORK_STATUS_FAIL)
			{
				ret_value[0] = COMMAND_ERROR_PREVIOUS_TASK_FAILURE;
			}

			if (ret_value[0] == 0)
			{
				if (pCmd->Fork[0].WorkNum != 0)
				{
					accept[0] = CheckCmdCellPosition(pCmd->OrderCode, (ForkWorkCmdSTR*)&pCmd->Fork[0]);
					if (accept[0])
					{
						ret_value[0] = COMMAND_ERROR_NOT_WITHIN_THE_SET_RANGE;  // 설정범위를 벗어남
						//ret_value[1] = accept[0];  // 설정범위를 벗어남
					}
					else
					{
						accept[0] = Check_Order_Prohibit_Rack(pCmd->OrderCode, (ForkWorkCmdSTR*)&pCmd->Fork[0]);
						if (accept[0])
						{
							ret_value[0] = COMMAND_ERROR_FALUT_STATE;

							// 에러코드 66-1 작업명령이상, 금지랙 
							save_error_code(ERROR1_ORDER_ABNORMAL, 1, pCmd->OrderCode);
						}
						else
						{
							accept[0] = Check_Order_Special_Rack(pCmd->OrderCode, (ForkWorkCmdSTR*)&pCmd->Fork[0]);
							if (accept[0])
							{
								ret_value[0] = COMMAND_ERROR_FALUT_STATE;
								save_error_code(ERROR1_SPECIAL_RACK, 1, accept[0]);
							}
						}
					}
				}
				else
				{
					accept[0] = 1;
					ret_value[0] = COMMAND_ERROR_JOB_NUMBER_ZEOR;
				}
			}
			break;

		case ORDER_CODE_RACK_CHG_DST: // 목적지변경
		case ORDER_CODE_STATION_CHG_DST: // 목적지변경
			// 자동모드
			if (m_St.ForkWork[0].OrderStatus_Fork == WORK_STATUS_DOING)
			{
				ret_value[0] = COMMAND_ERROR_EXECUTING_PREVIOUS_COMMAND;
			}
			else if (m_St.ForkWork[0].OrderStatus_Fork == WORK_STATUS_STOP)
			{
				ret_value[0] = COMMAND_ERROR_PREVIOUS_TASK_PAUSE;
			}
			/*
			else if (m_St.ForkWork[0].OrderStatus_Fork == WORK_STATUS_COMPLETE)
			{
				accept[0] |= cbits[0];
				accept[1] |= cbits[0];
			}
			if (accept[0])  ret_value[0] = 31;
			*/

			if (ret_value[0] == 0)
			{
				if (m_St.ForkWork[0].WorkNum_Fork == 0)
				{
					// 작업 삭제 상태
					if (CheckCmdCellPosition(pCmd->OrderCode, (ForkWorkCmdSTR*)&pCmd->Fork[0]))
					{
						ret_value[0] = COMMAND_ERROR_NOT_WITHIN_THE_SET_RANGE;  // 설정범위를 벗어남
						accept[0] = 1;
					}
					else
					{
						if (Check_Order_Prohibit_Rack(pCmd->OrderCode, (ForkWorkCmdSTR*)&pCmd->Fork[0]))
						{
							// 에러코드 66-1 작업명령이상, 금지랙 
							save_error_code(ERROR1_ORDER_ABNORMAL, 1, pCmd->OrderCode);
							ret_value[0] = COMMAND_ERROR_FALUT_STATE;
							accept[0] = 1;
						}
						else
						{
							if (Check_Order_Special_Rack(pCmd->OrderCode, (ForkWorkCmdSTR*)&pCmd->Fork[0]))
							{
								save_error_code(ERROR1_SPECIAL_RACK, 1, 0);
								ret_value[0] = COMMAND_ERROR_FALUT_STATE;
								accept[0] = 1;
							}
						}
					}
				}
				else
				{
					// 랙목적지 변경 수신 시, 이전 작업이 삭제되지 않았을 경우,
					if ((m_St.ForkWork[0].WorkNum_Fork == pCmd->Fork[0].WorkNum))
					{
						// 랙목적지 변경 작업번호가 현재 작업 번호와 같은 경우, 
						// 현재 작업이 작업완료가 아닌 경우(실패 상태인 경우) 실행.
						if (m_St.ForkWork[0].OrderStatus_Fork == WORK_STATUS_COMPLETE)
						{
							ret_value[0] = COMMAND_ERROR_RECEIVING_DESTINATION_CHANGE_COMMAND_IN_JOB_COMPLETION_STATUS;
							accept[0] = 1;
						}
						else if (m_St.ForkWork[0].OrderStatus_Fork == WORK_STATUS_FAIL)
						{
							// 실패 작업번호과 수신 작업번호가 같아야 하고, 현재 작업은 실패
							if (CheckCmdCellPosition(pCmd->OrderCode, (ForkWorkCmdSTR*)&pCmd->Fork[0]))
							{
								accept[0] = 1;
								ret_value[0] = COMMAND_ERROR_NOT_WITHIN_THE_SET_RANGE;  // 설정범위를 벗어남
							}
							else
							{
								if (Check_Order_Prohibit_Rack(pCmd->OrderCode, (ForkWorkCmdSTR*)&pCmd->Fork[0]))
								{
									// 에러코드 66-1 작업명령이상, 금지랙 
									save_error_code(ERROR1_ORDER_ABNORMAL, 1, pCmd->OrderCode);
									ret_value[0] = COMMAND_ERROR_FALUT_STATE;
									accept[0] = 1;
								}
								else
								{
									if (Check_Order_Special_Rack(pCmd->OrderCode, (ForkWorkCmdSTR*)&pCmd->Fork[0]))
									{
										save_error_code(ERROR1_SPECIAL_RACK, 1, pCmd->OrderCode);
										ret_value[0] = COMMAND_ERROR_FALUT_STATE;
										accept[0] = 1;
									}
								}
							}
						}
					}
					else
					{
						if (pCmd->Fork[0].WorkNum >= 0x0001000)
						{
							// Vexi 반송지령 작업 번호 영역
							if (CheckCmdCellPosition(pCmd->OrderCode, (ForkWorkCmdSTR*)&pCmd->Fork[0]))
							{
								ret_value[0] = COMMAND_ERROR_NOT_WITHIN_THE_SET_RANGE;  // 설정범위를 벗어남
								accept[0] = 1;
							}
							else
							{
								if (Check_Order_Prohibit_Rack(pCmd->OrderCode, (ForkWorkCmdSTR*)&pCmd->Fork[0]))
								{
									// 에러코드 66-1 작업명령이상, 금지랙 
									save_error_code(ERROR1_ORDER_ABNORMAL, 1, pCmd->OrderCode);
									ret_value[0] = COMMAND_ERROR_FALUT_STATE;
									accept[0] = 1;
								}
								else
								{
									if (Check_Order_Special_Rack(pCmd->OrderCode, (ForkWorkCmdSTR*)&pCmd->Fork[0]))
									{
										save_error_code(ERROR1_SPECIAL_RACK, 1, 0);
										ret_value[0] = COMMAND_ERROR_FALUT_STATE;
										accept[0] = 1;
									}
								}
							}
						}
						else
						{
							// 84-1 랙목적지변경 작업번호 이상
							ret_value[0] = COMMAND_ERROR_JOB_NUMBER_ABNORMAL;
							accept[0] = 1; // Command 이상
						}
					}
				}
			}
			break;
		}

		if (accept[0] == 0)
		{
			SRM_Warning_reset();

			ret_value[0] = SRM_Fork_Work_Cmd((WorkCmdSTR*)pCmd);
		}
	}

	if (!((ret_value[0] == 0) && (ret_value[1] == 0)))
	{
		accept[0] = 1;
	}

	
	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 11);
	txPutcPort(port, pCmd->OrderCode);
	txPutlPort(port, pCmd->Fork[0].WorkNum);
	txPutlPort(port, pCmd->Fork[1].WorkNum);
	txPutcPort(port, accept[0]);
	txPutcPort(port, ret_value[0]);
	txPutcPort(port, ret_value[1]);
	txPutcPort(port, 0x00);				// Reserved
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);
	sendTxBuf(port);
	
#if DEBUG_CMD
	Set_TestStatus(DEBUG_STR_58, accept[0]);
	Set_TestStatus(DEBUG_STR_59, ret_value[0]);
#endif

}

void rxCmdReferenceSearch(INT08U port, TMLComPTR pCom)
{
	INT08U result = 1;

	INT08U nMode = 0;
	//INT08U nFork1 = 1;

	if (m_St.SRM_Status2.Bit.ManualSW)	return;		// 기상반 수동

	if (m_St.SRM_Status1.Bit.StartOn == 0)  // 시작 Off 이면
	{
		nMode = pCom->Data[0];

		if (m_pgmEnv.SRM_RunMode == RUN_SEQ_STAND_BY)
		{
			if (nMode & cbits[2])
			{
				if (m_pgmEnv.Trial_Run_Mode)
				{
					//Fork1 중심 설정
					control_SRM_reference_Start(INV_FORK_1);
					result = 0;
				}
				else
				{
					if ((m_St.SRM_Mode.Bit.Manual == 1)
						|| (m_St.SRM_Mode.Bit.Force == 1)
						|| (m_St.SRM_Mode.Bit.Setup == 1))
					{
						//Fork1 중심 설정
						control_SRM_reference_Start(INV_FORK_1);
						result = 0;
					}
				}
			}
			else if (nMode & cbits[0])
			{
				if (m_pgmEnv.Trial_Run_Mode)
				{
					control_SRM_reference_Start(INV_TRAVEL);
					result = 0;	
				}
				else
				{
#if TRAV_ORIGIN_ENABLE_FLAG
					if (m_St.SRM_Mode.Bit.Setup == 1)
					{
						// 주행 원점 설정
						if (m_pgmEnv.OrderRejectCondition & cbits[1])
						{
							save_error_code(ERROR1_SAFETY_PULG_ON, 1, 0);
						}
						else if (m_pgmEnv.OrderRejectCondition & cbits[0])
						{
							save_error_code(ERROR1_EMBERGENCY_STOP, 1, 0);
						}
						else
						{
							if (Check_Fork_Center_Alarm() == 0)
							{
								control_SRM_reference_Start(INV_TRAVEL);
								result = 0;
							}
						}
					}
#endif
				}
			}
			else if (nMode & cbits[1])
			{
				if (m_pgmEnv.Trial_Run_Mode)
				{
					control_SRM_reference_Start(INV_HOIST);
					result = 0;
				}
				else
				{
#if LIFT_ORIGIN_ENABLE_FLAG
					if (m_St.SRM_Mode.Bit.Setup == 1)
					{
						if (m_pgmEnv.OrderRejectCondition & cbits[1])
						{
							save_error_code(ERROR1_SAFETY_PULG_ON, 1, 0);
						}
						else if (m_pgmEnv.OrderRejectCondition & cbits[0])
						{
							save_error_code(ERROR1_EMBERGENCY_STOP, 1, 0);
						}
						else
						{
							// 승강 원점 설정
							if (Check_Fork_Center_Alarm() == 0)
							{
								control_SRM_reference_Start(INV_HOIST);
								result = 0;
							}
						}
					}
#endif
				}
			}
			else if (nMode & cbits[3])
			{
				// Fork2 원점 설정
				if (m_pgmEnv.Trial_Run_Mode)
				{
					asm volatile("NOP");
				}
				else
				{
					if (m_St.SRM_Mode.Bit.Setup == 1)
					{
						asm volatile("NOP");
					}
				}
			}
		}
	}

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);                                        // STX : 0x16 0x16 0x16 0x16
	crcClear(port);                                                      // Clear CRC
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 1);
	txPutcPort(port, result);                                                   // S
	txCRCPort(port);                                                      // Transmit CRC
	rsPutmPort(port, FRAME_ETX, 1);                                        // ETX : 0xF5
	sendTxBuf(port);
}

void rxCmdStart(INT08U port, TMLComPTR pCom)
{
	INT08U result = 0;
	static INT32U s_StartOn;

	if (pCom->Header.SrcID.Type == COM_ID_GCP)
	{
		if (m_pgmEnv.Test_Simulator.GCP_Change_Mode_Disable)
		{
			result = 6;
		}
	}

	++s_StartOn;

	if (m_pgmEnv.OrderRejectCondition & cbits[0])
	{
		save_error_code(ERROR1_EMBERGENCY_STOP, 1, 0);
		result = 5;
	}
	else if (m_pgmEnv.OrderRejectCondition & cbits[1])
	{
		save_error_code(ERROR1_SAFETY_PULG_ON, 1, 3);
		result = 4;
	}
	else if (m_St.SRM_Status1.Bit.Fault)
	{
		result = 2;
	}
	else if (!m_St.SRM_Mode.Bit.Auto)
	{
		result = 3;
	}

	if (result == 0)
	{
		if (pCom->Data[0] == 0)
		{
			SRM_Start_Off();
		}
		else
		{
			result = SRM_Start_On();
		}
	}

	/*
	Set_TestStatus(DEBUG_STR_58, s_StartOn);
	Set_TestStatus(DEBUG_STR_59, pCom->Data[0]);
	Set_TestStatus(DEBUG_STR_60, result);
	*/
	//m_TestStatus.Ctrl[DEBUG_CTR_10] = result;

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);                                        // STX : 0x16 0x16 0x16 0x16
	crcClear(port);                                                      // Clear CRC
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 1);
	txPutcPort(port, result);                                                   // S
	txCRCPort(port);                                                      // Transmit CRC
	rsPutmPort(port, FRAME_ETX, 1);                                        // ETX : 0xF5
	sendTxBuf(port);
}

void rxCmd_MoveHome(INT08U port, TMLComPTR pCom)
{
	INT08U result = 0;

	//if (m_St.SRM_Mode.Bit.Setup)			return;

	if (m_pgmEnv.OrderRejectCondition & cbits[0])
	{
		save_error_code(ERROR1_EMBERGENCY_STOP, 1, 0);
		return;
	}

	if (m_pgmEnv.OrderRejectCondition & cbits[1])
	{
		save_error_code(ERROR1_SAFETY_PULG_ON, 1, 4);
		return;
	}

	// 홈복귀 실행 시, 입고 작업 수행
	result = SRM_Return_Home();

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);                                        // STX : 0x16 0x16 0x16 0x16
	crcClear(port);                                                      // Clear CRC
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 1);
	txPutcPort(port, result);                                                   // S
	txCRCPort(port);                                                      // Transmit CRC
	rsPutmPort(port, FRAME_ETX, 1);                                        // ETX : 0xF5
	sendTxBuf(port);
}


//보수위치 이동
void rxCmdMoveMaintanence(INT08U port, TMLComPTR pCom)
{

	/*
	 * reseult 정의
	 *
	 * 0 : 정상-> 명령수락 보수이동 시퀀스 시작
	 * 2 : SRM Fault 상태
	 * 5.A : 포크 중심 아님
	 * 5.B : 주행 보수위치 미설정
	 * 6.A : 이동 작업 수행 중
	 * 6.B : 주행 보수위치가 수동운전 범위 밖
	 * 7.A : 포크 작업 수행중
	 * 7.B : 승강 보수위치 미설정
	 * 8.A : 시퀀스 대기 아님
	 * 8.B : 승강 보수위치 범위 밖
	 * 9.A : 이미 보수위치
	 *
	 * */


	INT08U result = 0;

	if (m_pgmEnv.OrderRejectCondition & cbits[0])//명령거부조건
	{
		save_error_code(ERROR1_EMBERGENCY_STOP, 1, 0); //EMO가 눌려있으면, 에러
		return;
	}

	if (m_pgmEnv.OrderRejectCondition & cbits[1])
	{
		save_error_code(ERROR1_SAFETY_PULG_ON, 1, 5);//SAFETY PLUG가 뽑혀있으면, 에러
		return;
	}

	if (m_St.SRM_Status1.Bit.Fault)//SRM이 오류인 상태면 결과값 2반환
	{
		result = 2;
	}
	/*
	else if (m_St.SRM_Mode.Bit.Auto)
	{
		result = 3;
	}
	*/

	if (result == 0) //결과 값이 0인경우
	{
		if (m_St.SRM_Mode.Bit.Force)//강제모드일땐 조건안봄
		{
			asm volatile("NOP");	
		}
		else
		{
			// 강제모드 Off
			if (Check_Fork_Center_Alarm())//포크가 센터가 아닐때
			{
				if (result == 0)
				{
					result = 5;
				}
			}

			if ((m_St.ForkWork[0].OrderStatus_Move == WORK_STATUS_DOING)) //이동 작업 진행중일때
			{
				if (result == 0)
				{
					result = 6;
				}
			}
				
			if ((m_St.ForkWork[0].OrderStatus_Fork == WORK_STATUS_DOING)) // 포크작업 진행중일때
			{
				if (result == 0)
				{
					result = 7;
				}
			}
			
			if (m_pgmEnv.SRM_RunMode != RUN_SEQ_STAND_BY) // 스텐바이 모드가 아닐때
			{
				if (result == 0)
				{
					result = 8;
				}
			}
		}

		if (result == 0)
		{
			if (m_St.SRM_Status2.Bit.MaintanencePos)//이미 보수위치 이면 결과값 9반환
			{
				result = 9;
			}
			else
			{
				result = SRM_Move_Maintanence_Cmd();//아니면 이동
			}
		}
	}
	
	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);                                        // STX : 0x16 0x16 0x16 0x16
	crcClear(port);                                                      // Clear CRC
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 1);
	txPutcPort(port, result);                                                   // S
	txCRCPort(port);                                                      // Transmit CRC
	rsPutmPort(port, FRAME_ETX, 1);                                        // ETX : 0xF5
	sendTxBuf(port);
}

void rxCmdErrorReset(INT08U port, TMLComPTR pCom)
{
	SRM_fault_reset();

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);                                        // STX : 0x16 0x16 0x16 0x16
	crcClear(port);                                                      // Clear CRC
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 1);
	txPutcPort(port, 0);                                                   // S
	txCRCPort(port);                                                      // Transmit CRC
	rsPutmPort(port, FRAME_ETX, 1);                                        // ETX : 0xF5
	sendTxBuf(port);
}

void rxCmdOrderDelete(INT08U port, TMLComPTR pCom)
{
	INT08U i = 0;
	INT08U result[3] = { 0 };
	INT08U work[3] = { 0 };

	if (m_pgmEnv.SRM_RunMode == RUN_SEQ_STAND_BY)
	{
		///*
		if (pCom->Data[0] & cbits[0])
		{
			// Fork1 작업 삭제
			if (m_St.ForkWork[0].OrderStatus_Fork == WORK_STATUS_DOING)
			{
				if (m_St.SRM_Mode.Bit.Force)
				{
					work[0] = 1;
				}
				else
				{
					result[0] = 1;
				}
			}
			else
			{
				work[0] = 1;
			}
		}
		else if (pCom->Data[0] & cbits[1])
		{
			// Fork2 작업 삭제

			if (m_St.ForkWork[1].OrderStatus_Fork == WORK_STATUS_DOING)
			{
				if (m_St.SRM_Mode.Bit.Force)
				{
					work[1] = 1;
				}
				else
				{
					result[1] = 1;
				}
			}
			else
			{
				work[1] = 1;
			}
		}
		else if (pCom->Data[0] & cbits[2])
		{
			// 대기상태의 Task Command 모두 삭제
			for (i = 0; i < MAX_TASK_COUNT; i++)
			{
				if ((m_St.TaskWork[i].OrderState == TASK_STATUS_STAND_BY)
					|| (m_St.TaskWork[i].OrderState == TASK_STATUS_NONE))
				{
					memset((INT08U*)&m_St.TaskWork[i], 0, sizeof(TaskCommand));
				}
			}
		}
		//*/

		if (work[0])
		{
			memset((INT08U*)&m_St.ForkWork[0], 0, sizeof(WorkInfoSTR));
		}

		if (work[1])
		{
			memset((INT08U*)&m_St.ForkWork[1], 0, sizeof(WorkInfoSTR));
		}

		if ((work[0]) || (work[1]))
		{
			m_St.TargetFork1.Station = 0;
			m_St.TargetFork1.Bay_ID = 0;
			m_St.TargetFork1.Level_ID = 0;
			m_St.TargetFork1.Row_ID = 0;

			m_St.TargetFork2.Station = 0;
			m_St.TargetFork2.Bay_ID = 0;
			m_St.TargetFork2.Level_ID = 0;
			m_St.TargetFork2.Row_ID = 0;

			m_St.Inv_St[INV_TRAVEL].Target_Pos = 0;
			m_St.Inv_St[INV_HOIST].Target_Pos = 0;
			m_St.Inv_St[INV_FORK_1].Target_Pos = 0;
			m_St.Inv_St[INV_FORK_2].Target_Pos = 0;

			memcpy((INT08U*)&m_BKSram.WorkInfo.WorkSt[0], (INT08U*)&m_St.ForkWork[0], sizeof(WorkInfoSTR) * 2);

			saveBKSramBlock((INT08U*)&m_BKSram.WorkInfo, sizeof(SaveWorkSTR));
		}
	}
	else
	{
		result[0] = 1;
		result[1] = 1;
	}

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 3);
	txPutcPort(port, result[0]);
	txPutcPort(port, result[1]);
	txPutcPort(port, result[2]);
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);                                        // ETX : 0xF5
	sendTxBuf(port);
}


/**
	@brief      모드 변경
	@details
	@date		2023/07/15
	@param		INT08U port, TMLComPTR pCom
	@return		void
	@remarks
*/
void rxModeChange(INT08U port, TMLComPTR pCom)
{
	INT08U i = 0;

	//if (m_St.SRM_Status2.Bit.ManualSW)	return;		// 기상반 수동
	if (m_pgmEnv.Test_Simulator.GCP_Change_Mode_Disable)
	{
		if (pCom->Header.SrcID.Type == COM_ID_GCP)
		{
			return;
		}
	}

	if (pCom->Data[0] == 0)
	{
		//m_pgmEnv.Check_Home_Flag = 0;
		// Manual Mode
		Change_DeviceMode(DEVICE_MANUAL_MODE, 0);
	}
	else if (pCom->Data[0] == 1)
	{
		Change_DeviceMode(DEVICE_SETUP_MODE, 0);
	}
	else if (pCom->Data[0] == 2)
	{
		Change_DeviceMode(DEVICE_SEMI_AUTO_MODE, 0);
	}

	if (m_St.SRM_Mode.Bit.Auto)
	{
		m_St.SRM_Mode.Bit.Force = 0;
	}
	else
	{
		if (pCom->Data[1] & cbits[0])
		{
			if (m_St.SRM_Mode.Bit.Force == 0)
			{
				m_St.SRM_Mode.Bit.Force = 1;
				m_pgmEnv.Buzzer_OneShot = 1;
			}
		}
		else
		{
			m_St.SRM_Mode.Bit.Force = 0;
			asm volatile("NOP");
		}
	}

	//m_TestStatus.Ctrl[DEBUG_CTR_1] = pCom->Data[0];
	//m_TestStatus.Ctrl[DEBUG_CTR_2] = pCom->Data[1];

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);                                        // STX : 0x16 0x16 0x16 0x16
	crcClear(port);                                                      // Clear CRC
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 1);
	txPutcPort(port, 0);
	txCRCPort(port);                                                      // Transmit CRC
	rsPutmPort(port, FRAME_ETX, 1);                                        // ETX : 0xF5
	sendTxBuf(port);
}

/**
  * @brief  입출력 형상 조회
  * @param  port
  * @param  pCom
  * @retval None
  */
void rxDigital_IO_Form_Req(INT08U port, TMLComPTR pCom)
{
#if DEBUG_MSG
	INT32U nProcessTime = 0;
	nProcessTime = m_pgmEnv.timer1ms;
#endif
	memcpy((INT08U*)&m_DIO_SetInfo.Set.DI_Set, (INT08U*)&m_ExtSEnv.DIO_Set.DI_Set, sizeof(DI_t) * 122);
	memcpy((INT08U*)&m_DIO_SetInfo.Set.DO_Set, (INT08U*)&m_ExtSEnv.DIO_Set.DO_Set, sizeof(DO_t) * 43);

	memcpy((INT08U*)&m_DIO_SetInfo.Set.DI_Set2, (INT08U*)&m_ExtSEnv.DIO_Set.DI_Set2, sizeof(DI_t) * 27);
	memcpy((INT08U*)&m_DIO_SetInfo.Set.DO_Set2, (INT08U*)&m_ExtSEnv.DIO_Set.DO_Set2, sizeof(DO_t) * 26);
	
	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);	// STX : 0x16 0x16 0x16 0x16
	crcClear(port);		// Clear CRC
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, sizeof(DIO_SetInfoSTR));
	txPutnPort(port, (INT08U*)&m_DIO_SetInfo, sizeof(DIO_SetInfoSTR));	// Data
	txCRCPort(port);	// Transmit CRC
	rsPutmPort(port, FRAME_ETX, 1);	// ETX : 0xF5
	sendTxBuf(port);

#if DEBUG_MSG
	printf("[DEBUG_APP] Request DIO Form ProcessTime : %ld ms\r\n", getCalcTimer1ms(nProcessTime));
#endif
}

/**
  * @brief  입출력 형상 설정
  * @param  port
  * @param  pCom
  * @retval None
  */
void rxDigital_IO_Form_Control(INT08U port, TMLComPTR pCom)
{
	DIO_SetSTR* pCtrl;
	INT08U nError = 0;
	//INT16U i = 0;

	if (!m_St.SRM_Mode.Bit.Setup)	return;

	pCtrl = (DIO_SetSTR*)&pCom->Data[30];

	/*
	for (i = 0; i < MAX_DI_CNT; i++)
	{
		if (pCtrl->DI_Set[i].Type == 255)
		{
			// Not use pin initialize config
			memset((INT08U*)&pCtrl->DI_Set[i].Pin, 0x00, sizeof(INT08U) * 4);
		}

	}

	for (i = 0; i < MAX_DO_CNT; i++)
	{
		if (pCtrl->DO_Set[i].Type == 255)
		{
			// Not use pin initialize config
			memset((INT08U*)&pCtrl->DO_Set[i].Pin, 0x00, sizeof(INT08U) * 2);
		}

	}
	*/

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 2);
	if (nError == 0)
	{
		txPutcPort(port, 0);
		txPutcPort(port, 0);
	}
	else
	{
		txPutcPort(port, 1);
		txPutcPort(port, nError);
	}
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);
	sendTxBuf(port);

	Set_DIO_Parameter(pCtrl);

	Set_MCU_Input_FilterTime();
}

/**
  * @brief  Read Rack Config
  * @param  port Receive Port
  * @param  pCom Pointer Receive Data
  * @retval None
  */
void rxRackEnvReq(INT08U port, TMLComPTR pCom)
{
	//RackConfigComSTR nSendRackConfig;
#if DEBUG_MSG
	INT32U nProcessTime = 0;
	nProcessTime = m_pgmEnv.timer1ms;
#endif
	ExtFlash_ReadData(EXT_RACK_ENV0_ADDR_START, (INT08U*)&m_ExtSEnv0, sizeof(ExtFlashSEnv0));

	//memset((INT08U*)&nSendRackConfig, 0, sizeof(RackConfigComSTR));
	//memcpy((INT08U*)&nSendRackConfig, (INT08U*)&m_ExtSEnv0.RackConfig, sizeof(RackConfigComSTR));

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, sizeof(RackConfigComSTR));
	txPutnPort(port, (INT08U*)&m_ExtSEnv0.RackConfig, sizeof(RackConfigComSTR));
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);
	sendTxBuf(port);

#if DEBUG_MSG
	printf("[DEBUG_APP] Request Rack Config ProcessTime : %ld ms\r\n", getCalcTimer1ms(nProcessTime));
#endif
}

/**
  * @brief  Write Rack Config
  * @param  port Receive Port
  * @param  pCom Pointer Receive Data
  * @retval None
  */
void rxRackEnvSet(INT08U port, TMLComPTR pCom)
{
	//INT08U i = 0;
	INT08U error_rack = 0;

	RackConfigSTR* pCtrl;

	if (m_St.SRM_Mode.Bit.Setup)
	{
		pCtrl = (RackConfigSTR*)&pCom->Data[0];

		if (pCtrl->RackType == 1)
		{
			if ((pCtrl->BayCount < 1) || (pCtrl->BayCount > MAX_BAY_COUNT))	error_rack = 2;

			if ((pCtrl->LvCount < 1) || (pCtrl->LvCount > MAX_LEVEL_COUNT))
			{
				if (!error_rack)	error_rack = 3;
			}

			if ((pCtrl->ForkType == 2) || (pCtrl->ForkType == 4) || (pCtrl->ForkType == 6))
			{
				asm volatile("NOP");
			}
			else
			{
				if (!error_rack)	error_rack = 4;
			}

			/*
			if ((m_ExtSEnv2.Fork_Drv.Manual_Drv.LeftPos != 0) &&
				(m_ExtSEnv2.Fork_Drv.Manual_Drv.RightPos != 0))
			{
				if (pCtrl->RowCount == 2)
				{
					if (pCtrl->RowDepth[0] >= 0 || pCtrl->RowDepth[0] < m_ExtSEnv2.Fork_Drv.Manual_Drv.LeftPos)
					{
						if (!error_rack)	error_rack = 5;
					}

					if (pCtrl->RowDepth[1] <= 0 || pCtrl->RowDepth[1] > m_ExtSEnv2.Fork_Drv.Manual_Drv.RightPos)
					{
						if (!error_rack)	error_rack = 5;
					}
				}
				else if ((pCtrl->RowCount == 4) || (pCtrl->RowCount == 6))
				{
					if (pCtrl->RowDepth[0] >= 0 || pCtrl->RowDepth[0] < m_ExtSEnv2.Fork_Drv.Manual_Drv.LeftPos ||
						pCtrl->RowDepth[0] >= pCtrl->RowDepth[1])
					{
						if (!error_rack)	error_rack = 5;
					}
					if (pCtrl->RowDepth[1] >= 0 || pCtrl->RowDepth[1] < m_ExtSEnv2.Fork_Drv.Manual_Drv.LeftPos ||
						pCtrl->RowDepth[1] <= pCtrl->RowDepth[0])
					{
						if (!error_rack)	error_rack = 5;
					}
					if (pCtrl->RowDepth[2] <= 0 || pCtrl->RowDepth[2] > m_ExtSEnv2.Fork_Drv.Manual_Drv.RightPos ||
						pCtrl->RowDepth[2] >= pCtrl->RowDepth[3])
					{
						if (!error_rack)	error_rack = 5;
					}
					if (pCtrl->RowDepth[3] <= 0 || pCtrl->RowDepth[3] > m_ExtSEnv2.Fork_Drv.Manual_Drv.RightPos ||
						pCtrl->RowDepth[3] <= pCtrl->RowDepth[2])
					{
						if (!error_rack)	error_rack = 5;
					}
				}
			}
			*/

			if (pCtrl->Veriant_LT_Offset > RACK_SET_VERIENT_LT_OFFSET)
			{
				if (!error_rack)	error_rack = 6;
			}

			if ((pCtrl->LevelUpOffset < RACK_SET_LEVEL_UP_OFFSET_MIN) || (pCtrl->LevelUpOffset > RACK_SET_LEVEL_UP_OFFSET_MAX))
			{
				if (!error_rack)	error_rack = 7;
			}
			else
			{
				if (pCtrl->LevelUpOffset == 0)
				{
					pCtrl->LevelUpOffset = DEF_LT_LEVEL_UP_MM;
				}
			}

			if ((pCtrl->LevelDnOffset > RACK_SET_LEVEL_DN_OFFSET_MAX) || (pCtrl->LevelDnOffset < RACK_SET_LEVEL_DN_OFFSET_MIN))
			{
				if (!error_rack)	error_rack = 8;
			}
			else
			{
				if (pCtrl->LevelDnOffset == 0)
				{
					pCtrl->LevelDnOffset = DEF_LT_LEVEL_DOWN_MM;
				}
			}
		}
		/*else if (pCtrl->RackType == 2)
		{

		}*/
		else
		{
			error_rack = 1;
		}
	}
	else
	{
		error_rack = 10;
	}

	if (error_rack)
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Fail Rack Config - error_rack : %d.\r\n", error_rack);
#endif
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Success Rack Config.\r\n");
#endif
		Set_Rack_Config(pCtrl);
		//Create_Reference_Position();
	}

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 2);
	txPutcPort(port, (error_rack) ? 1 : 0);		// 0 : ACK, 1 : NACK
	txPutcPort(port, error_rack);								// Error Rack Code
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);
	sendTxBuf(port);
}

/**
  * @brief  Read Cell Config
  * @param  port Receive Port
  * @param  pCom Pointer Receive Data
  * @retval None
  */
void rxCellEnvReq(INT08U port, TMLComPTR pCom)
{
	INT08U nDataIdx = 0;

	INT08U nRackType = 0;		// 1 : SRM
	INT08U nDataType = 0;		// 1 : Bay, 2 : Lv

	INT08U nStart = 0;
	INT08U nEnd = 0;

	INT32U nCellData[MAX_BAY_COUNT] = { 0, };
	//INT08U nCellDataCnt = 0;
	INT16U nCellDataCnt = 0;

	INT08U nError = 0;

#if DEBUG_MSG
	INT32U nProcessTime = 0;
	nProcessTime = m_pgmEnv.timer1ms;
#endif

	nRackType = pCom->Data[nDataIdx];		++nDataIdx;

	if (nRackType == 1)
	{
		nDataType = pCom->Data[nDataIdx];		++nDataIdx;
		nStart = pCom->Data[nDataIdx];		++nDataIdx;
		nEnd = pCom->Data[nDataIdx];		++nDataIdx;

		if (nStart > nEnd)
		{
			nError = 2;
		}
		else
		{
			nCellDataCnt = (nEnd - nStart) + 1;

			ExtFlash_ReadData(EXT_RACK_ENV0_ADDR_START, (INT08U*)&m_ExtSEnv0, sizeof(ExtFlashSEnv0));

			if (nDataType == 1)
			{
				memcpy((INT08U*)nCellData, (INT08U*)&m_ExtSEnv0.CellConfig_Left.BayPos[nStart], sizeof(INT32U) * nCellDataCnt);
			}
			else if (nDataType == 2)
			{
				memcpy((INT08U*)nCellData, (INT08U*)&m_ExtSEnv0.CellConfig_Left.LvPos[nStart], sizeof(INT32U) * nCellDataCnt);
			}
			else if (nDataType == 3)
			{
				memcpy((INT08U*)nCellData, (INT08U*)&m_ExtSEnv0.CellConfig_Right.BayPos[nStart], sizeof(INT32U) * nCellDataCnt);
			}
			else if (nDataType == 4)
			{
				memcpy((INT08U*)nCellData, (INT08U*)&m_ExtSEnv0.CellConfig_Right.LvPos[nStart], sizeof(INT32U) * nCellDataCnt);
			}
			else
			{
				nError = 3;
			}
		}
	}
	else
	{
		nError = 1;
	}

#if DEBUG_CELL_CONFIG
	printf("[DEBUG_APP] Read RackConfig DataType:%d, Start:%d, End:%d, DataCnt:%d Error:%d\r\n",
		nDataType, nStart, nEnd, nCellDataCnt, nError);
#endif

	if (nError == 0)
	{
		clearTxBuf(port);
		rsPutmPort(port, FRAME_STX, 4);
		crcClear(port);
		txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, (sizeof(INT32U) * nCellDataCnt) + 8);
		txPutcPort(port, nRackType);
		txPutwPort(port, m_ExtSEnv0.RackConfig.BayCount);
		txPutwPort(port, m_ExtSEnv0.RackConfig.LvCount);
		txPutcPort(port, nDataType);
		txPutcPort(port, nStart);
		txPutcPort(port, nEnd);
		// 		txPutwPort(port, m_ExtSEnv0.RackConfig.BayCount);
		// 		txPutwPort(port, m_ExtSEnv0.RackConfig.LvCount);
		txPutnPort(port, (INT08U*)nCellData, sizeof(INT32U) * nCellDataCnt);
		txCRCPort(port);
		rsPutmPort(port, FRAME_ETX, 1);
		sendTxBuf(port);
	}

#if DEBUG_MSG
	printf("[DEBUG_APP] Request Cell Config ProcessTime : %ld ms\r\n", getCalcTimer1ms(nProcessTime));
#endif
}

void rxCellEnvSet(INT08U port, TMLComPTR pCom)
{
	INT16U i = 0;

	INT08U nDataIdx = 0;
	INT08U nRackType = 0;		// 1 : SRM
	INT08U nDataType = 0;		// 1 : Bay, 2 : Lv

	INT16U nStart = 0;
	INT16U nEnd = 0;

	INT08U* pCellData;
	//INT08U nCellDataCnt = 0;
	INT16U nCellDataCnt = 0;

	CellConfigSTR nWrite_Cell;
	//CellConfigSTR nWrite_Cell_R;
	RackConfigSTR nWrite_RackCfg;

	INT16U nDataCount = 0;

	INT08U nError = 0;

	//static INT32U s_BayPos[MAX_BAY_COUNT] = { 0, };
	//static INT32U s_LvPos[MAX_LEVEL_COUNT] = { 0, };

	INT32U nBayPos[MAX_BAY_COUNT] = { 0, };
	INT32U nLvPos[MAX_LEVEL_COUNT] = { 0, };

	WORD_User nBayCount;
	WORD_User nLvCount;

	nRackType = pCom->Data[nDataIdx];		++nDataIdx;

	nBayCount.W = 0;
	nBayCount.B[0] = pCom->Data[nDataIdx];		++nDataIdx;
	nBayCount.B[1] = pCom->Data[nDataIdx];		++nDataIdx;

	nLvCount.W = 0;
	nLvCount.B[0] = pCom->Data[nDataIdx];		++nDataIdx;
	nLvCount.B[1] = pCom->Data[nDataIdx];		++nDataIdx;

	nDataType = pCom->Data[nDataIdx];	++nDataIdx;
	nStart = pCom->Data[nDataIdx];		++nDataIdx;
	nEnd = pCom->Data[nDataIdx];		++nDataIdx;

	if (m_St.SRM_Mode.Bit.Setup)
	{
		if (nRackType == 1)
		{
			if (nStart != 0)
			{
				nError = 3;		// Start No가 0이 아님
			}
			else if (nStart > nEnd)
			{
				nError = 3;		//
			}
			else
			{
				nCellDataCnt = nEnd + 1;
				pCellData = (INT08U*)&pCom->Data[nDataIdx];

				//nDataCount = (pCom->Header.Len - 4) / 4;
				nDataCount = (pCom->Header.Len - 8) / 4;

				if (nBayCount.W > MAX_BAY_COUNT)
				{
					nBayCount.W = 0;
				}

				if (nLvCount.W > MAX_LEVEL_COUNT)
				{
					nLvCount.W = 0;
				}

				if (nCellDataCnt == nDataCount)
				{
					if ((nDataType == 1) || ((nDataType == 3)))
					{
						if (nCellDataCnt > MAX_BAY_COUNT)
						{
							nError = 4;		// 최대 개수 초과
						}
						//else if (nCellDataCnt > m_ExtSEnv0.RackConfig.BayCount)
						else if ((nStart + nCellDataCnt) > nBayCount.W)
						{
							nError = 4;		// End No가 랙구성 Bay(Level) Count - 1 값이 아닌 경우
						}
						else
						{
							memcpy((INT08U*)&nBayPos[0], (INT08U*)pCellData, sizeof(INT32U) * nCellDataCnt);

							for (i = 0; i < nEnd; i++)
							{
								if (nBayPos[i] > nBayPos[i + 1])
								{
									nError = 6;		// 베이 오름차순 오류
									break;
								}
							}

							for (i = 0; i <= nEnd; i++)
							{
								if ((m_ExtSEnv2.TravDrive.ManualDrive.StartPos != 0)
									&& (m_ExtSEnv2.TravDrive.ManualDrive.EndPos != 0))
								{
									if (nBayPos[i] < m_ExtSEnv2.TravDrive.ManualDrive.StartPos ||
										nBayPos[i] > m_ExtSEnv2.TravDrive.ManualDrive.EndPos)
									{
										nError = 7;		// 주행 최소, 최대 범위 오류
										break;
									}
								}
							}
						}
					}
					else if ((nDataType == 2) || (nDataType == 4))
					{
						if (nCellDataCnt > MAX_LEVEL_COUNT)
						{
							nError = 4;		// 최대 개수 초과
						}
						//else if ((nStart + nCellDataCnt) > m_ExtSEnv0.RackConfig.LvCount)
						else if ((nStart + nCellDataCnt) > nLvCount.W)
						{
							nError = 4;		// End No가 랙구성 Bay(Level) Count - 1 값이 아닌 경우
						}
						else
						{
							memcpy((INT08U*)&nLvPos[0], (INT08U*)pCellData, sizeof(INT32U) * nCellDataCnt);

							for (i = 0; i < nEnd; i++)
							{
								if (nLvPos[i] > nLvPos[i + 1])
								{
									nError = 6;		// 레벨 오름차순 오류
									break;
								}
							}

							for (i = 0; i <= nEnd; i++)
							{
								if ((m_ExtSEnv2.LiftDrive.ManualDrive.StartPos != 0)
									&& (m_ExtSEnv2.LiftDrive.ManualDrive.EndPos != 0))
								{
									if (nLvPos[i] < m_ExtSEnv2.LiftDrive.ManualDrive.StartPos ||
										nLvPos[i] > m_ExtSEnv2.LiftDrive.ManualDrive.EndPos)
									{
										nError = 7;		// 리프트 최소, 최대 범위 오류
										break;
									}
								}
							}
						}
					}
					else
					{
						nError = 2;		// Data Type 필드값 이상
					}
				}
				else
				{
					nError = 5;		// 위치값 데이터 개수가 (End No - Start No + 1)개가 아님
				}
			}
		}
		else
		{
			nError = 1;	// Rack Type 필드값 이상
		}
	}
	else
	{
		nError = 10;	// 장치의 모드가 셋업모드가 아님
	}

#if DEBUG_CELL_CONFIG
	printf("[DEBUG_APP] Receive RackConfig DataType:%d, Start:%d, End:%d, CellCnt:%d DataCnt:%d Error:%d\r\n",
		nDataType, nStart, nEnd, nCellDataCnt, nDataCount, nError);
#endif

	if (!nError)
	{
		ExtFlash_ReadData(EXT_RACK_ENV0_ADDR_START, (INT08U*)&m_ExtSEnv0, sizeof(ExtFlashSEnv0));

		memset((INT08U*)&nWrite_Cell, 0, sizeof(CellConfigSTR));
		memset((INT08U*)&nWrite_RackCfg, 0, sizeof(RackConfigSTR));

		if (nDataType == 1)
		{
			
			memcpy((INT08U*)&nWrite_Cell, (INT08U*)&m_ExtSEnv0.CellConfig_Left, sizeof(CellConfigSTR));

			// 이전데이터 삭제
			memset((INT08U*)&nWrite_Cell.BayPos[nStart], 0, sizeof(INT32U)* MAX_BAY_COUNT);
			memcpy((INT08U*)&nWrite_Cell.BayPos[nStart], (INT08U*)&nBayPos[nStart], sizeof(INT32U) * nCellDataCnt);

			Set_Cell_Config_1(&nWrite_Cell, 0);
		}
		else if (nDataType == 2)
		{
			memcpy((INT08U*)&nWrite_Cell, (INT08U*)&m_ExtSEnv0.CellConfig_Left, sizeof(CellConfigSTR));

			// 이전데이터 삭제
			memset((INT08U*)&nWrite_Cell.LvPos[nStart], 0, sizeof(INT32U)* MAX_LEVEL_COUNT);
			memcpy((INT08U*)&nWrite_Cell.LvPos[nStart], (INT08U*)&nLvPos[nStart], sizeof(INT32U) * nCellDataCnt);

			Set_Cell_Config_1(&nWrite_Cell, 0);
		}
		else if (nDataType == 3)
		{
			// 이전데이터 로딩 삭제. Bay, Level 개수가 다를 경우, 이전 설정이 지워지지 않음.
			memcpy((INT08U*)&nWrite_Cell, (INT08U*)&m_ExtSEnv0.CellConfig_Right, sizeof(CellConfigSTR));

			// 이전데이터 삭제
			memset((INT08U*)&nWrite_Cell.BayPos[nStart], 0, sizeof(INT32U)* MAX_BAY_COUNT);
			memcpy((INT08U*)&nWrite_Cell.BayPos[nStart], (INT08U*)&nBayPos[nStart], sizeof(INT32U) * nCellDataCnt);

			Set_Cell_Config_1(&nWrite_Cell, 1);
		}
		else if (nDataType == 4)
		{
			// 이전데이터 로딩 삭제. Bay, Level 개수가 다를 경우, 이전 설정이 지워지지 않음.
			memcpy((INT08U*)&nWrite_Cell, (INT08U*)&m_ExtSEnv0.CellConfig_Right, sizeof(CellConfigSTR));

			// 이전데이터 삭제
			memset((INT08U*)&nWrite_Cell.LvPos[nStart], 0, sizeof(INT32U)* MAX_LEVEL_COUNT);
			memcpy((INT08U*)&nWrite_Cell.LvPos[nStart], (INT08U*)&nLvPos[nStart], sizeof(INT32U) * nCellDataCnt);

			Set_Cell_Config_1(&nWrite_Cell, 1);
		}

		memcpy((INT08U*)&nWrite_RackCfg, (INT08U*)&m_ExtSEnv0.RackConfig, sizeof(RackConfigSTR));

		if (nBayCount.W <= MAX_BAY_COUNT)
		{
			nWrite_RackCfg.BayCount = nBayCount.W;
		}

		if (nLvCount.W <= MAX_LEVEL_COUNT)
		{
			nWrite_RackCfg.LvCount = nLvCount.W;
		}
		Set_Rack_Config(&nWrite_RackCfg);

		Create_Reference_Position();
	}

	wait1ms(100);

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 10);
	txPutcPort(port, nRackType);
	txPutwPort(port, nBayCount.W);
	txPutwPort(port, nLvCount.W);
	txPutcPort(port, nDataType);
	txPutcPort(port, nStart);
	txPutcPort(port, nEnd);
	txPutcPort(port, (nError) ? 1 : 0);		// 0 : ACK, 1 : NACK
	txPutcPort(port, nError);				// Error Code
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);
	sendTxBuf(port);
}

/**
  * @brief
  * @param  port Receive Port
  * @param  pCom Pointer Receive Data
  * @retval None
  */
void rxStationEnvReq(INT08U port, TMLComPTR pCom)
{
#if DEBUG_MSG
	INT32U nProcessTime = 0;
	nProcessTime = m_pgmEnv.timer1ms;
#endif
	ExtFlash_ReadData(EXT_RACK_ENV1_ADDR_START, (INT08U*)&m_ExtSEnv1, sizeof(ExtFlashSEnv1));

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, sizeof(StationSetupSTR));
	txPutnPort(port, (INT08U*)&m_ExtSEnv1.StationEnv, sizeof(StationSetupSTR));
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);
	sendTxBuf(port);

#if DEBUG_MSG
	printf("[DEBUG_APP] Request Station Config ProcessTime : %ld ms\r\n", getCalcTimer1ms(nProcessTime));
#endif
}

/**
  * @brief  Write Rack Config
  * @param  port Receive Port
  * @param  pCom Pointer Receive Data
  * @retval None
  */
void rxStationEnvSet(INT08U port, TMLComPTR pCom)
{
	INT08U i = 0;
	INT08U nError_code = 0;

	INT08U nUse_Count = 0;
	//INT08U nError_St_No = 0;

	StationSetupSTR* pCtrl;
	StationSetupSTR  nWriteBuf;

	if (m_St.SRM_Mode.Bit.Setup)
	{
		memset((INT08U*)&nWriteBuf, 0, sizeof(StationSetupSTR));

		pCtrl = (StationSetupSTR*)&pCom->Data[0];

		memcpy((INT08U*)&nWriteBuf, (INT08U*)pCtrl, sizeof(StationSetupSTR));		// Reserved 영역 변경 사항 복사

		if (pCtrl->TotalUseCnt <= MAX_STATION_COUNT)
		{
			nWriteBuf.TotalUseCnt = pCtrl->TotalUseCnt;

			if ((pCtrl->InterLock_Type >= ST_INTERLOCK_NOT_USE) &&
				(pCtrl->InterLock_Type <= ST_INTERLOCK_COM))
			{
				nWriteBuf.InterLock_Type = pCtrl->InterLock_Type;

				for (i = 0; i < pCtrl->TotalUseCnt; i++)
				{
					if (pCtrl->StationSet[i].Type == STATION_NOT_USE)
					{
						memset((INT08U*)&nWriteBuf.StationSet[i], 0, sizeof(StationSet_t));
					}
					else if ((pCtrl->StationSet[i].Type >= STATION_IN_TYPE) &&
						(pCtrl->StationSet[i].Type <= STATION_VIRTUAL_TYPE))
					{
						if (pCtrl->StationSet[i].Type != STATION_NOT_USE)//
						{
							if (pCtrl->StationSet[i].Goods_Type)
							{
								if (1/*(m_ExtSEnv2.TravDrive.ManualDrive.StartPos != 0)
									&& (m_ExtSEnv2.TravDrive.ManualDrive.EndPos != 0)*/)
								{
									if ((pCtrl->StationSet[i].InPosition.TravPos >= m_ExtSEnv2.TravDrive.ManualDrive.StartPos) &&
										(pCtrl->StationSet[i].InPosition.TravPos <= m_ExtSEnv2.TravDrive.ManualDrive.EndPos))
									{
										if (1/*(m_ExtSEnv2.LiftDrive.ManualDrive.StartPos != 0)
											&& (m_ExtSEnv2.LiftDrive.ManualDrive.EndPos != 0)*/)
										{
											if ((pCtrl->StationSet[i].InPosition.LiftPos >= m_ExtSEnv2.LiftDrive.ManualDrive.StartPos) &&
												(pCtrl->StationSet[i].InPosition.LiftPos <= m_ExtSEnv2.LiftDrive.ManualDrive.EndPos))
											{
												if ((pCtrl->StationSet[i].ForkDepth >= m_ExtSEnv2.ForkDrive.ManualDrive.LeftPos) &&
													(pCtrl->StationSet[i].ForkDepth <= m_ExtSEnv2.ForkDrive.ManualDrive.RightPos))
												{
													if ((pCtrl->StationSet[i].LevelUpOffset >= RACK_SET_LEVEL_UP_OFFSET_MIN) &&
														(pCtrl->StationSet[i].LevelUpOffset <= RACK_SET_LEVEL_UP_OFFSET_MAX))
													{
														if (pCtrl->StationSet[i].LevelUpOffset == 0)
														{
															// 설정값이 0일 경우, 기본값 적용
															pCtrl->StationSet[i].LevelUpOffset = DEF_LT_LEVEL_UP_MM;
														}

														if (pCtrl->StationSet[i].Stabilzation_Time > 250)
														{
															pCtrl->StationSet[i].Stabilzation_Time = 250;
														}

														if ((pCtrl->StationSet[i].LevelDnOffset <= RACK_SET_LEVEL_DN_OFFSET_MAX) &&
															(pCtrl->StationSet[i].LevelDnOffset >= RACK_SET_LEVEL_DN_OFFSET_MIN))
														{
															if (pCtrl->StationSet[i].LevelDnOffset == 0)
															{
																// 설정값이 0일 경우, 기본값 적용
																pCtrl->StationSet[i].LevelDnOffset = DEF_LT_LEVEL_DOWN_MM;
															}

															if (pCtrl->InterLock_Type == ST_INTERLOCK_8BIT)
															{
																if ((pCtrl->StationSet[i].InterLock_No >= 0) &&
																	(pCtrl->StationSet[i].InterLock_No <= 8))
																{
																	++nUse_Count;
																	memcpy((INT08U*)&nWriteBuf.StationSet[i], (INT08U*)&pCtrl->StationSet[i], sizeof(StationSet_t));
																	asm volatile("NOP");
																}
																else
																{
																	nError_code = 9;	// 스테이션 인터록 번호 이상
																	break;
																}
															}
															else if (pCtrl->InterLock_Type == ST_INTERLOCK_COM)
															{
																if ((pCtrl->StationSet[i].InterLock_No >= 0) &&
																	(pCtrl->StationSet[i].InterLock_No <= MAX_STATION_COUNT))
																{
																	++nUse_Count;
																	memcpy((INT08U*)&nWriteBuf.StationSet[i], (INT08U*)&pCtrl->StationSet[i], sizeof(StationSet_t));
																	asm volatile("NOP");
																}
																else
																{
																	nError_code = 9;	// 스테이션 인터록 번호 이상
																	break;
																}
															}
															else
															{
																++nUse_Count;
																memcpy((INT08U*)&nWriteBuf.StationSet[i], (INT08U*)&pCtrl->StationSet[i], sizeof(StationSet_t));
															}
														}
														else
														{
															nError_code = 8;	// 하강 정위치 오프셋 설정 이상
															break;
														}
													}
													else
													{
														nError_code = 7;	// 상승 정위치 오프셋 설정 이상
														break;
													}
												}
												else
												{
													nError_code = 6;	// 포크 위치 설정 이상
													break;
												}
											}
											else
											{
												nError_code = 5;	// 승강 위치 설정 이상
												break;
											}
										}
									}
									else
									{
										nError_code = 4;	// 주행 위치 설정 이상
										break;
									}
								}
							}
						}
					}
					else
					{
						nError_code = 3;	// 스테이션 타입 이상
						break;
					}
				}
			}
			else
			{
				i = 0;
				nError_code = 2;	// 스테이션 인터록타입 이상
			}
		}
		else
		{
			i = 0;
			nError_code = 1;
		}
	}
	else
	{
		nError_code = 10;
	}


	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 3);
	txPutcPort(port, (nError_code) ? 1 : 0);		// 0 : ACK, 1 : NACK
	txPutcPort(port, i);
	txPutcPort(port, nError_code);
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);
	sendTxBuf(port);

	if (nError_code)
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Fail Station Config St_No:%d error code : %d.\r\n", \
			i + 1, nError_code);
#endif
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Success Station Config. Total Count: %d, Use Count: %d\r\n", pCtrl->TotalUseCnt, nUse_Count);
#endif
		nWriteBuf.TotalUseCnt = nUse_Count;

		Set_Station_Config(&nWriteBuf);

		Create_Reference_Position();
	}
}

/**
  * @brief
  * @param  port Receive Port
  * @param  pCom Pointer Receive Data
  * @retval None
  */
void rxProhibitRackEnvReq(INT08U port, TMLComPTR pCom)
{
	ProhibitRackComSTR nSendComData;

	ExtFlash_ReadData(EXT_RACK_ENV1_ADDR_START, (INT08U*)&m_ExtSEnv1, sizeof(ExtFlashSEnv1));
	memcpy((INT08U*)&nSendComData, (INT08U*)&m_ExtSEnv1.ProhibitRack, sizeof(ProhibitRackComSTR));

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, sizeof(ProhibitRackComSTR));
	txPutnPort(port, (INT08U*)&nSendComData, sizeof(ProhibitRackComSTR));
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);
	sendTxBuf(port);
}

/**
  * @brief
  * @param  port Receive Port
  * @param  pCom Pointer Receive Data
  * @retval None
  */
void rxProhibitRackEnvSet(INT08U port, TMLComPTR pCom)
{
	INT08U i = 0;
	INT08U error = 0;
	//INT08U error_inx = 0;
	//INT08U type;
	ProhibitRackSTR* pCtrl;
	//InhibitRackSet_t* pSetData;

	if (m_St.SRM_Mode.Bit.Setup)
	{
		pCtrl = (ProhibitRackSTR*)&pCom->Data[0];

		for (i = 0; i < pCtrl->Count; i++)
		{
			if (Check_InhibitRack_Data(&pCtrl->SetData[i]))
			{
				error = 1;
				break;
			}
		}
	}
	else
	{
		error = 10;
	}

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 2);
	txPutcPort(port, error ? 1 : 0);		// 0 : ACK, 1 : NACK
	txPutcPort(port, error);				// Error Code
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);
	sendTxBuf(port);

	if (!error)
	{
		Set_ProhibitRack_Config(pCtrl);
	}
}

/**
  * @brief
  * @param  port Receive Port
  * @param  pCom Pointer Receive Data
  * @retval None
  */
void rxSpecialRackEnvReq(INT08U port, TMLComPTR pCom)
{
	//SpecialRackComSTR nSendComData;

	ExtFlash_ReadData(EXT_RACK_ENV1_ADDR_START, (INT08U*)&m_ExtSEnv1, sizeof(ExtFlashSEnv1));
	//memcpy((INT08U*)&nSendComData, (INT08U*)&m_ExtSEnv1.SpecialRack, sizeof(SpecialRackComSTR));

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, sizeof(SpecialRackComSTR));
	txPutnPort(port, (INT08U*)&m_ExtSEnv1.SpecialRack, sizeof(SpecialRackComSTR));
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);
	sendTxBuf(port);
}

/**
  * @brief
  * @param  port Receive Port
  * @param  pCom Pointer Receive Data
  * @retval None
  */
void rxSpecialRackEnvSet(INT08U port, TMLComPTR pCom)
{
	INT08U error = 0;
	//INT08U error_inx = 0;
	//INT08U type;
	SpecialRackSTR* pCtrl;

	if (m_St.SRM_Mode.Bit.Setup)
	{
		pCtrl = (SpecialRackSTR*)&pCom->Data[0];
	}
	else
	{
		error = 10;
	}

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 2);
	txPutcPort(port, error ? 1 : 0);		// 0 : ACK, 1 : NACK
	txPutcPort(port, error);				// Error Code
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);
	sendTxBuf(port);

	if (!error)
	{
		Set_SpecialRack_Config(pCtrl);
	}
}

/**
  * @brief
  * @param  port Receive Port
  * @param  pCom Pointer Receive Data
  * @retval None
  */
void rxRackEnvInitializeSet(INT08U port, TMLComPTR pCom)
{
	INT08U is_reset = 0;
	INT08U error = 0;
	INT08U nInitializeFlag = 0;

	if (m_St.SRM_Mode.Bit.Setup)
	{
		nInitializeFlag = pCom->Data[1];

		if (pCom->Data[0] == 1)
		{
			if (nInitializeFlag & cbits[7])
			{
				Clear_Rack_Config();
				is_reset = 1;
				/*
				if (Check_RackEnv_Config())
				{
					Clear_Rack_Config();
					is_reset = 1;
				}
				*/
			}

			if (nInitializeFlag & cbits[6])
			{
				Clear_Cell_Config();
				is_reset = 1;
				/*
				if (Check_CellEnv_Config())
				{
					Clear_Cell_Config();
					is_reset = 1;
				}
				*/
			}

			if (nInitializeFlag & cbits[5])
			{
				Clear_CellOffset_Config();
				/*
				if (Check_Cell_Offset_Config())
				{
					Clear_CellOffset_Config();
					//is_reset = 1;
				}
				*/
			}

			if (nInitializeFlag & cbits[4])
			{
				Clear_Station_Config();
				/*
				if (Check_StationEnv_Config())
				{
					Clear_Station_Config();
					is_reset = 1;
				}
				*/
			}

			if (nInitializeFlag & cbits[3])
			{
				Clear_ProhibitRack_Config();
				/*
				if (Check_ProhibitRack_Config())
				{
					Clear_ProhibitRack_Config();
					//is_reset = 1;
				}
				*/
			}

			if (nInitializeFlag & cbits[2])
			{
				Clear_SpecialRack_Config();
				/*
				if (Check_SpecialRack_Config())
				{
					Clear_SpecialRack_Config();
					//is_reset = 1;
				}
				*/
			}
		}
		else
		{
			error = 1;
		}
	}
	else
	{
		error = 10;
	}

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 3);
	txPutcPort(port, nInitializeFlag);		// 0 : ACK, 1 : NACK
	txPutcPort(port, error ? 1 : 0);		// 0 : ACK, 1 : NACK
	txPutcPort(port, error);				// Error Code
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);
	sendTxBuf(port);

	if (is_reset)	controlCpuReset();
}

/**
  * @brief
  * @param  port Receive Port
  * @param  pCom Pointer Receive Data
  * @retval None
  */
void rxCell_Offset_EnvReq(INT08U port, TMLComPTR pCom)
{
	INT08U nDef_Req_Max = 150;
	INT08U nError = 0;

	INT08U nRackType = 0;		// 1 : SRM
	//INT16U nTotalIndex = 0;		// 0 ~
	INT16U nReqIndex = 0;		// 0 ~

	CellOffsetSTR nReadCellOffset;
	CellOffsetSTR nTranData[150];

	//INT16U i = 0;
	INT16U nTransCount = 0;		// transmit cell offset count

	INT16U nByteIdx = 0;
	INT08U nBitIdx = 0;

	static INT16U s_Process_Idx = 0;

#if DEBUG_MSG
	INT32U nProcessTime = 0;
	nProcessTime = m_pgmEnv.timer1ms;
#endif
	if (m_St.SRM_Mode.Bit.Auto)		return;

	nRackType = pCom->Data[0];

	if (nRackType == 1)
	{
		if (m_pgmEnv.CellOffsetUseCount > 0)
		{
			nReqIndex = ((INT16U)pCom->Data[1]) & 0x00FF;
			nReqIndex |= ((INT16U)pCom->Data[2] << 8) & 0xFF00;

			if (nReqIndex == 0)
			{
				s_Process_Idx = 0;
			}
		}
		else
		{
			// Cell offset use count zero.
			nError = 2;
		}
	}
	else
	{
		nError = 1;
	}

	if (!nError)
	{
		//for (i = 0; i < nDef_Req_Max; i++)
		while (s_Process_Idx < 32768)
		{
			nByteIdx = s_Process_Idx / 8;
			nBitIdx = s_Process_Idx % 8;

			if (!(m_pgmEnv.CellOffsetUseFlag[nByteIdx] & cbits[nBitIdx]))
			{
				Read_CellOffset_Addr(s_Process_Idx, &nReadCellOffset);

				memcpy((INT08U*)&nTranData[nTransCount], (INT08U*)&nReadCellOffset, sizeof(CellOffsetSTR));
				++nTransCount;

#if DEBUG_CELL_OFFSET
				/*
				printf("[CELL OFFSET] Read Index: %d, nByteIdx: %d, nBitIdx: %d, Bay: %d Lv: %d\r\n",
					s_Process_Idx, nByteIdx, nBitIdx, nReadCellOffset.Bay_No, nReadCellOffset.Lv_No);
					*/
#endif
			}

			++s_Process_Idx;

			if (nTransCount >= nDef_Req_Max)
			{
				break;
			}
			else if (nTransCount >= m_pgmEnv.CellOffsetUseCount)
			{
				break;
			}
		}

#if DEBUG_CELL_OFFSET
		/*
		printf("[CELL OFFSET] Total: %d, Request: %d, Process_Idx: %d, TransCount: %d,  ProcessTime: %ldms.\r\n",
			m_pgmEnv.CellOffsetUseCount, nReqIndex, s_Process_Idx, nTransCount, getCalcTimer1ms(nProcessTime));
		*/
#endif
	}
	else
	{
		s_Process_Idx = 0;
	}



	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, (sizeof(CellOffsetSTR) * nTransCount) + 6);
	txPutcPort(port, nRackType);
	txPutwPort(port, m_pgmEnv.CellOffsetUseCount);
	txPutwPort(port, nReqIndex);
	txPutcPort(port, nTransCount);
	txPutnPort(port, (INT08U*)&nTranData[0], sizeof(CellOffsetSTR) * nTransCount);
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);

#if DEBUG_MSG
	printf("[DEBUG_APP] Read CellOFfset Total: %d, Request: %d, Process_Idx: %d, TransCount: %d, ProcessTime: %ldms. Packet Size: %d\r\n",
		m_pgmEnv.CellOffsetUseCount, nReqIndex, s_Process_Idx, nTransCount, getCalcTimer1ms(nProcessTime), m_pgmEnv.txEthUdpComLen);
#endif

	sendTxBuf(port);
}

/**
  * @brief
  * @param  port Receive Port
  * @param  pCom Pointer Receive Data
  * @retval None
  */
void rxCell_Offset_EnvSet(INT08U port, TMLComPTR pCom)
{
	INT08U nDef_Recv_Max = 128;
	INT08U nError = 0;

	INT08U nDataIndex = 0;

	INT08U nRackType = 0;			// 1 : SRM
	INT16U nTotalOffsetCount = 0;
	INT16U nNowIndex = 0;			// 0 ~
	INT08U nRecvDataCount = 0;

	INT16U nCell_Idx = 0;

	CellOffsetSTR nRecvCellOffset[200] = { 0, };

	INT08U nCurBlockNo = 0, nPreBlockNo = 0;
	//INT08U nBay_Idx = 0, nLv_Idx = 0;

	CellOffsetSTR nWriteBuf[512];	// 4K
	INT08U nWriteCellCount = 0;
	INT08U nWriteCellTotalCount = 0;
	INT08U nCheckCount = 0;

	static INT08U s_TmpUseFlag[4096];	// 4K
	static INT16U s_Process_Idx = 0;

	INT32U nProcessTime = 0;
	nProcessTime = m_pgmEnv.timer1ms;

	nRackType = pCom->Data[nDataIndex];		++nDataIndex;

	nTotalOffsetCount = ((INT16U)pCom->Data[nDataIndex]) & 0x00FF;			++nDataIndex;
	nTotalOffsetCount |= ((INT16U)pCom->Data[nDataIndex] << 8) & 0xFF00;	++nDataIndex;

	nNowIndex = ((INT16U)pCom->Data[nDataIndex]) & 0x00FF;					++nDataIndex;
	nNowIndex |= ((INT16U)pCom->Data[nDataIndex] << 8) & 0xFF00;			++nDataIndex;

	nRecvDataCount = pCom->Data[nDataIndex];		++nDataIndex;

	if (m_St.SRM_Mode.Bit.Setup)
	{
		if (nRackType == 1)
		{
			if (nTotalOffsetCount)
			{
				if (nNowIndex == 0)
				{
					memset((INT08U*)s_TmpUseFlag, 0xFF, sizeof(INT08U) * 4096);
					s_Process_Idx = 0;

#if DEBUG_CELL_OFFSET
					printf("[CELL OFFSET] Clear UseFlag Now Index: %d, Process Index: %d\r\n", nNowIndex, s_Process_Idx);
#endif
				}
				else
				{
					asm volatile("NOP");
				}


				if (nRecvDataCount > nDef_Recv_Max)
				{
					nError = 2;
				}
				else
				{
					if (nRecvDataCount > 0)
					{
						nProcessTime = m_pgmEnv.timer1ms;

						memcpy((INT08U*)nRecvCellOffset, (INT08U*)&pCom->Data[nDataIndex], sizeof(CellOffsetSTR) * nRecvDataCount);

						nCurBlockNo = Check_CellOffset_BlockNo(&nRecvCellOffset[0]);
						nPreBlockNo = nCurBlockNo;

						Read_CellOffset_Block(nCurBlockNo, (INT08U*)nWriteBuf);
#if DEBUG_CELL_OFFSET
						/*
						printf("[CELL OFFSET] Start Write NowIndex: 0x%d, size: %d CurBlockNo: %d.\r\n",
							nNowIndex, sizeof(CellOffsetSTR) * nRecvDataCount, nCurBlockNo);
							*/
#endif

						nWriteCellTotalCount = nRecvDataCount;
						while (nWriteCellTotalCount)
						{
							//nBay_Idx = nRecvCellOffset[nCheckCount].Bay_No;
							//nLv_Idx = nRecvCellOffset[nCheckCount].Lv_No;

							nCurBlockNo = Check_CellOffset_BlockNo(&nRecvCellOffset[nCheckCount]);
							if (nPreBlockNo != nCurBlockNo)
							{
								if (nWriteCellCount)
								{
									Write_CellOffset_Block(nPreBlockNo, (INT08U*)nWriteBuf);
									nWriteCellCount = 0;
								}

								nPreBlockNo = nCurBlockNo;

								Read_CellOffset_Block(nCurBlockNo, (INT08U*)nWriteBuf);
								nCell_Idx = 0;
							}

							if ((nWriteBuf[nCell_Idx].Bay_No == nRecvCellOffset[nCheckCount].Bay_No)
								&& (nWriteBuf[nCell_Idx].Lv_No == nRecvCellOffset[nCheckCount].Lv_No))
							{
								memcpy((INT08U*)&nWriteBuf[nCell_Idx].Trav_Left, (INT08U*)&nRecvCellOffset[nCheckCount].Trav_Left, sizeof(INT08U) * 6);
								++nWriteCellCount;
								--nWriteCellTotalCount;

								++nCheckCount;
								++s_Process_Idx;

								Check_CellOffset_UseFlag(&nWriteBuf[nCell_Idx], s_TmpUseFlag);
							}

							++nCell_Idx;
						}

						if (nWriteCellCount)
						{
							Write_CellOffset_Block(nPreBlockNo, (INT08U*)nWriteBuf);
							nWriteCellCount = 0;
						}

#if DEBUG_CELL_OFFSET
						printf("[CELL OFFSET] Write Total: %d, NowIndex: 0x%d, RecvData: %d, ProcessData: %d, ProcessTime: %ldms.\r\n",
							nTotalOffsetCount, nNowIndex, nRecvDataCount, s_Process_Idx, getCalcTimer1ms(nProcessTime));
#endif
					}
					else
					{
						nError = 3;
					}
				}
			}
			else
			{
				// Clear Total CellOffset
				if (Check_Cell_Offset_Config())
				{
					nError = 2;

					Clear_CellOffset_Config();
				}
			}
		}
		else
		{
			nError = 1;
		}
	}
	else
	{
		nError = 10;
	}

	if (nError)
	{
		s_Process_Idx = 0;
	}
	else
	{
		if (nTotalOffsetCount > 0)
		{
			if (nTotalOffsetCount == s_Process_Idx)
			{
				Write_CellOffset_InitCode();

				memcpy((INT08U*)m_pgmEnv.CellOffsetUseFlag, (INT08U*)s_TmpUseFlag, sizeof(INT08U) * 4096);
				ExtFlash_WriteData(EXT_CELL_OFFSET_USEFLAG_ADDR_START, (INT08U*)m_pgmEnv.CellOffsetUseFlag, sizeof(INT08U) * 4096);

				m_pgmEnv.CellOffsetUseCount = Scan_CellOffset_UseCount();
			}
		}
	}


	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 8);
	txPutcPort(port, nRackType);
	txPutwPort(port, nTotalOffsetCount);
	txPutwPort(port, nNowIndex);
	txPutcPort(port, nRecvDataCount);
	txPutcPort(port, (nError) ? 1 : 0);
	txPutcPort(port, nError);
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);
	sendTxBuf(port);

#if DEBUG_MSG
	printf("[DEBUG_APP] Set Cell Offset ProcessTime : %ld ms\r\n", getCalcTimer1ms(nProcessTime));
#endif
}

/**
  * @brief
  * @param  port Receive Port
  * @param  pCom Pointer Receive Data
  * @retval None
  */
void rxControlParamterReq(INT08U port, TMLComPTR pCom)
{
#if DEBUG_MSG
	INT32U nProcessTime = 0;
	nProcessTime = m_pgmEnv.timer1ms;
#endif
	//ParamControlComSTR nSendComData;

	ExtFlash_ReadData(EXT_PARAMETER_SET_ADDR_START, (INT08U*)&m_ExtSEnv2, sizeof(ExtFlashSEnv2));
	//memcpy((INT08U*)&nSendComData, (INT08U*)&m_ExtSEnv2.CtrParam, sizeof(ParamControlComSTR));

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, sizeof(ParamControlComSTR));
	txPutnPort(port, (INT08U*)&m_ExtSEnv2.CtrParam, sizeof(ParamControlComSTR));
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);
	sendTxBuf(port);

#if DEBUG_MSG
	printf("[DEBUG_APP] Request Control Parameter ProcessTime : %ld ms\r\n", getCalcTimer1ms(nProcessTime));
#endif
}

/**
  * @brief
  * @param  port Receive Port
  * @param  pCom Pointer Receive Data
  * @retval None
  */
void rxControlParamterSet(INT08U port, TMLComPTR pCom)
{
	INT08U nError = 0;
	INT08U is_save = 0;
	ParamControlSTR* pSetParam;

#if DEBUG_MSG
	INT32U nProcessTime = 0;
	nProcessTime = m_pgmEnv.timer1ms;
#endif

	if (m_St.SRM_Mode.Bit.Setup)
	{
		pSetParam = (ParamControlSTR*)&pCom->Data[34];

		if (pCom->Data[0] & cbits[7])	// Total Set Flag
		{
			pCom->Data[1] = 0xFF;//헤더
			pCom->Data[2] = 0x1F;//헤더
			pCom->Data[3] = 0x7F;//헤더
			pCom->Data[4] = 0x1F;//헤더

			is_save = 1;
		}

		if (pCom->Data[1] & cbits[0])	is_save = Set_SafetyPlug_Type(pSetParam);//안전플러그 타입
		if (pCom->Data[1] & cbits[1])	is_save = Set_DoorSensor_UseFlag(pSetParam);//도어센서 사용여부
		if (pCom->Data[1] & cbits[2])	is_save = Set_DoorSensor_AlarmFlag(pSetParam);//도어알람 사용여부
		if (pCom->Data[1] & cbits[3])	is_save = Set_LaserModem_AlarmFlag(pSetParam);
		if (pCom->Data[1] & cbits[4])	is_save = Set_AutoChange_Mode(pSetParam);
		if (pCom->Data[1] & cbits[5])	is_save = Set_TravLift_OperTime_SyncFlag(pSetParam);
		if (pCom->Data[1] & cbits[6])	is_save = Set_Cargo_Adnormal_HomeReturn_UseFlag(pSetParam);
		if (pCom->Data[1] & cbits[7])	is_save = Set_Forking_Sensor_AlarmFlag(pSetParam);

		if (pCom->Data[2] & cbits[0])	is_save = Set_OutputStation_DoubleEntry_AlarmFlag(pSetParam);
		if (pCom->Data[2] & cbits[1])	is_save = Set_Forking_Interlock_AlarmFlag(pSetParam);
		if (pCom->Data[2] & cbits[2])	is_save = Set_Forking_Interlock_CheckFlag(pSetParam);
		if (pCom->Data[2] & cbits[3])	is_save = Set_Forking_lift_BrakeOn_UseFlag(pSetParam);

		if (pCom->Data[2] & cbits[4])
		{
			Set_Forking_Origin_OperCount(pSetParam);
		}

		if (pCom->Data[3] & cbits[0])	Set_RetryInPositon(pSetParam);
		if (pCom->Data[3] & cbits[1])	Set_Loading_DelayTime(pSetParam);
		if (pCom->Data[3] & cbits[2])	Set_Unloading_DelayTime(pSetParam);
		if (pCom->Data[3] & cbits[3])
		{
			Set_Fork_Origin_DelayTime(pSetParam);
		}

		if (pCom->Data[3] & cbits[4])	Set_Setup_TimeOut(pSetParam);
		if (pCom->Data[3] & cbits[5])	Set_Drive_Timeout(pSetParam);
		if (pCom->Data[3] & cbits[6])	Set_Auto_Timeout(pSetParam);

		if (pCom->Data[3] & 0x7F)
		{
			is_save = 1;
		}

		if (pCom->Data[4] & cbits[0])
		{
			Set_ForceMode_ReleaseTime(pSetParam);
		}

		if (pCom->Data[4] & cbits[1])	is_save = Set_Fan_Control(pSetParam);
		if (pCom->Data[4] & cbits[2])	Set_Buzzer_Control(pSetParam);
		if (pCom->Data[4] & cbits[3])	Set_UpperBrakeSetup(pSetParam);
		if (pCom->Data[4] & cbits[4])	is_save = Set_AutoFork_PositionSensor_Alarm(pSetParam);
		if (pCom->Data[4] & cbits[5])	is_save = Set_Carriage_Stabilzation_Time(pSetParam);

		if (pCom->Data[4] & 0x06)
		{
			is_save = 1;
		}
	}
	else
	{
		nError = 10;
	}

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 2);
	txPutcPort(port, (nError) ? 1 : 0);
	txPutcPort(port, nError);
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);
	sendTxBuf(port);

	if (!nError)
	{
		if (is_save)
		{
			Save_Control_Param(pSetParam);

			Update_Maintanance_SRM_Setting_Data();
		}
	}

#if DEBUG_MSG
	printf("[DEBUG_APP] Set Control Parameter ProcessTime : %ld ms\r\n", getCalcTimer1ms(nProcessTime));
#endif
}

/**
  * @brief
  * @param  port Receive Port
  * @param  pCom Pointer Receive Data
  * @retval None
  */
void rxTravelDriveParamterReq(INT08U port, TMLComPTR pCom)
{
	ParamTravelDriveComSTR nSendComData;

	ExtFlash_ReadData(EXT_PARAMETER_SET_ADDR_START, (INT08U*)&m_ExtSEnv2, sizeof(ExtFlashSEnv2));
	memcpy((INT08U*)&nSendComData, (INT08U*)&m_ExtSEnv2.TravDrive, sizeof(ParamTravelDriveComSTR));


	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, sizeof(ParamTravelDriveComSTR));
	txPutnPort(port, (INT08U*)&nSendComData, sizeof(ParamTravelDriveComSTR));
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);
	sendTxBuf(port);
}

/**
  * @brief
  * @param  port Receive Port
  * @param  pCom Pointer Receive Data
  * @retval None
  */
void rxTravelDriveParamterSet(INT08U port, TMLComPTR pCom)
{
	INT08U nError = 0;
	INT08U i = 0, is_save = 0;
	ParamTravelDriveSTR* pSetParam;

	ParamTravelDriveSTR nWriteParam;

	INT32U nProcessTime = 0;
	nProcessTime = m_pgmEnv.timer1ms;

	if (m_St.SRM_Mode.Bit.Setup)//셋업모드일때
	{
		pSetParam = (ParamTravelDriveSTR*)&pCom->Data[35];//pCom.내 Data 36번째 주소를 ParameTravelDriveSTR*로 명명한다.

		if (pCom->Data[0] & 0x80)//데이터를 일부만 받을지 전체를 다받을지에 대한정의 0x80이면 전체일괄 저장을 뜻함 0이면 비트마스크로 항목별 일부분 저장
		{
			for (i = 0; i < MAX_TRAV_VELOCITY_CNT; i++)// 주행최고카운트
			{
				if ((i >= 0) && (i <= 7))
				{
					Set_Trav_Velocity(i, &pSetParam->Vel[i]);
				}
				else if ((i >= 8) && (i <= 15))
				{
					Set_Trav_Velocity(i, &pSetParam->Vel[i]);
				}
			}

			Set_Trav_InPostion_Tolerance(pSetParam);
			Set_Trav_InPostion_Hysteresis(pSetParam);
			Set_Trav_Manual_Drive(pSetParam);
			Set_Trav_BrakeOn_DelayTime(pSetParam);
			//Set_Trav_Origin_Position(pSetParam);
			Set_Trav_Home_Position(pSetParam);
			Set_Trav_Maintenance_Position(pSetParam);
			Set_Trav_DecelationRange_Mode(pSetParam);
			Set_Trav_SoftLimit_Error(pSetParam);
			Set_Trav_SoftDecelation_Error(pSetParam);
			Set_Trav_OriginDog_Postion_Error(pSetParam);
			Set_Trav_DecelDog_Position_Error(pSetParam);
			Set_Trav_Invertor_Param(pSetParam);

			is_save = 2;
		}
		else
		{
			memcpy((INT08U*)&nWriteParam, (INT08U*)&m_ExtSEnv2.TravDrive, sizeof(ParamTravelDriveSTR));

			for (i = 0; i < MAX_TRAV_VELOCITY_CNT; i++)
			{
				if ((i >= 0) && (i <= 7))
				{
					if (pCom->Data[1] & cbits[i])
					{
						//Set_Trav_Velocity(i, &pSetParam->Vel[i]);
						Set_Trav_Velocity_1(i, &pSetParam->Vel[i], &nWriteParam.Vel[i]);
						is_save = 1;
					}
				}
				else if ((i >= 8) && (i <= 15))
				{
					if (pCom->Data[2] & cbits[i - 8])
					{
						//Set_Trav_Velocity(i, &pSetParam->Vel[i]);
						Set_Trav_Velocity_1(i, &pSetParam->Vel[i], &nWriteParam.Vel[i]);
						is_save = 1;
					}
				}
			}

			if (pCom->Data[3] & cbits[0])
			{
				Set_Trav_InPostion_Tolerance_1(pSetParam, &nWriteParam);
				Set_Trav_InPostion_Hysteresis_1(pSetParam, &nWriteParam);
			}

			if (pCom->Data[3] & cbits[1]) Set_Trav_Manual_Drive_1(pSetParam, &nWriteParam);
			if (pCom->Data[3] & cbits[2]) Set_Trav_BrakeOn_DelayTime_1(pSetParam, &nWriteParam);
			//if (pCom->Data[3] & cbits[3]) Set_Trav_Origin_Position_1(pSetParam, &nWriteParam);
			if (pCom->Data[3] & cbits[4]) is_save = Set_Trav_Home_Position_1(pSetParam, &nWriteParam);
			if (pCom->Data[3] & cbits[5]) is_save = Set_Trav_Maintenance_Position_1(pSetParam, &nWriteParam);
			if (pCom->Data[3] & cbits[6]) is_save = Set_Trav_DecelationRange_Mode_1(pSetParam, &nWriteParam);
			if (pCom->Data[3] & cbits[7]) is_save = Set_Trav_SoftLimit_Error_1(pSetParam, &nWriteParam);

			if (pCom->Data[3] & 0x0F)	is_save = 1;

			if (pCom->Data[4] & cbits[0]) is_save = Set_Trav_SoftDecelation_Error_1(pSetParam, &nWriteParam);
			if (pCom->Data[4] & cbits[1]) is_save = Set_Trav_OriginDog_Postion_Error_1(pSetParam, &nWriteParam);
			if (pCom->Data[4] & cbits[2]) is_save = Set_Trav_DecelDog_Postion_Error_1(pSetParam, &nWriteParam);

			if (pCom->Data[4] & cbits[3]) Set_Trav_Invertor_Param_1(pSetParam, &nWriteParam);

			if (pCom->Data[4] & 0x0F)	is_save = 1;
		}
	}
	else
	{
		nError = 10;
	}

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 2);
	txPutcPort(port, (nError) ? 1 : 0);//ack, nack 전문날리기
	txPutcPort(port, nError);
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);
	sendTxBuf(port);

	if (!nError)
	{
		if (is_save == 1)
		{
			Save_Travel_Drive_Param(&nWriteParam);

			Update_Maintanance_SRM_Setting_Data();
		}
		else if (is_save == 2)
		{
			Save_Travel_Drive_Param(pSetParam);

			Update_Maintanance_SRM_Setting_Data();
		}
	}

	//m_TestStatus.Ctrl[DEBUG_CTR_10] = getCalcTimer1ms(nProcessTime);
#if DEBUG_MSG
	printf("[DEBUG_APP] Set Travel Drive Parameter ProcessTime : %ld ms\r\n", getCalcTimer1ms(nProcessTime));
#endif
}

/**
  * @brief
  * @param  port Receive Port
  * @param  pCom Pointer Receive Data
  * @retval None
  */
void rxLiftDriveParamterReq(INT08U port, TMLComPTR pCom)
{
	//ParamLiftDriveComSTR nSendComData;

	ExtFlash_ReadData(EXT_PARAMETER_SET_ADDR_START, (INT08U*)&m_ExtSEnv2, sizeof(ExtFlashSEnv2));
	//memcpy((INT08U*)&nSendComData, (INT08U*)&m_ExtSEnv2.LiftDrive, sizeof(ParamLiftDriveComSTR));

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, sizeof(ParamLiftDriveComSTR));
	txPutnPort(port, (INT08U*)&m_ExtSEnv2.LiftDrive, sizeof(ParamLiftDriveComSTR));
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);
	sendTxBuf(port);
}

/**
  * @brief
  * @param  port Receive Port
  * @param  pCom Pointer Receive Data
  * @retval None
  */
void rxLiftDriveParamterSet(INT08U port, TMLComPTR pCom)
{
	INT08U nError = 0;
	INT08U i = 0, is_save = 0;
	ParamLiftDriveSTR* pSetParam;

	ParamLiftDriveSTR nWriteParam;

	INT32U nProcessTime = 0;
	nProcessTime = m_pgmEnv.timer1ms;


	//if (m_St.SRM_Mode.Bit.Setup || m_St.SRM_Mode.Bit.Manual)
	if (m_St.SRM_Mode.Bit.Setup)
	{
		// 셋업모드 이외에 외부 플래시에 저장시, TCP Socket 연결이 끊어져 알람 발생.
		pSetParam = (ParamLiftDriveSTR*)&pCom->Data[35];

		if (pCom->Data[0] & 0x80)
		{
			for (i = 0; i < MAX_LIFT_VELOCITY_CNT; i++)
			{
				if ((i >= 0) && (i <= 7))
				{
					Set_Lift_Velocity(i, &pSetParam->Vel[i]);
				}
				else if ((i >= 8) && (i <= 15))
				{
					Set_Lift_Velocity(i, &pSetParam->Vel[i]);
				}
			}

			Set_Lift_InPostion_Tolerance(pSetParam);
			Set_Lift_InPostion_Hysteresis(pSetParam);
			Set_Lift_Manual_Drive(pSetParam);
			Set_Lift_BrakeOn_DelayTime(pSetParam);
			//Set_Lift_Origin_Position(pSetParam);
			Set_Lift_Home_Position(pSetParam);
			Set_Lift_Maintanance_Position(pSetParam);
			Set_Lift_DecelationRange_Mode(pSetParam);
			Set_Lift_SoftLimit_Error(pSetParam);
			Set_Lift_SoftDecelation_Error(pSetParam);
			Set_Lift_OriginDog_Postion_Error(pSetParam);
			Set_Lift_DecelDog_Postion_Error(pSetParam);
			Set_Lift_ForkOut_Jerk_Set(pSetParam);
			Set_Lift_Invertor_Param(pSetParam);
			Set_Lift_LevelUpOffset(pSetParam);
			Set_Lift_LevelDnOffset(pSetParam);
			Set_Lift_Veriant_LT_Offset(pSetParam);

			is_save = 2;
		}
		else
		{
			memcpy((INT08U*)&nWriteParam, (INT08U*)&m_ExtSEnv2.LiftDrive, sizeof(ParamLiftDriveSTR));

			for (i = 0; i < MAX_LIFT_VELOCITY_CNT; i++)
			{
				if ((i >= 0) && (i <= 7))
				{
					if (pCom->Data[1] & cbits[i])
					{
						Set_Lift_Velocity_1(i, &pSetParam->Vel[i], &nWriteParam.Vel[i]);
						is_save = 1;
					}
				}
				else if ((i >= 8) && (i <= 15))
				{
					if (pCom->Data[2] & cbits[i - 8])
					{
						Set_Lift_Velocity_1(i, &pSetParam->Vel[i], &nWriteParam.Vel[i]);
						is_save = 1;
					}
				}
			}

			if (pCom->Data[3] & cbits[0])
			{
				Set_Lift_InPostion_Tolerance_1(pSetParam, &nWriteParam);
				Set_Lift_InPostion_Hysteresis_1(pSetParam, &nWriteParam);
			}

			if (pCom->Data[3] & cbits[1]) Set_Lift_Manual_Drive_1(pSetParam, &nWriteParam);
			if (pCom->Data[3] & cbits[2]) Set_Lift_BrakeOn_DelayTime_1(pSetParam, &nWriteParam);
			if (pCom->Data[3] & cbits[3]) Set_Lift_Origin_Position_1(pSetParam, &nWriteParam);
			if (pCom->Data[3] & cbits[4]) is_save = Set_Lift_Home_Position_1(pSetParam, &nWriteParam);
			if (pCom->Data[3] & cbits[5]) is_save = Set_Lift_Maintanance_Position_1(pSetParam, &nWriteParam);
			if (pCom->Data[3] & cbits[6]) is_save = Set_Lift_DecelationRange_Mode_1(pSetParam, &nWriteParam);
			if (pCom->Data[3] & cbits[7]) is_save = Set_Lift_SoftLimit_Error_1(pSetParam, &nWriteParam);

			if (pCom->Data[3] & 0x0F)	is_save = 1;


			if (pCom->Data[4] & cbits[0]) Set_Lift_SoftDecelation_Error_1(pSetParam, &nWriteParam);
			if (pCom->Data[4] & cbits[1]) Set_Lift_OriginDog_Postion_Error_1(pSetParam, &nWriteParam);
			if (pCom->Data[4] & cbits[2]) Set_Lift_DecelDog_Postion_Error_1(pSetParam, &nWriteParam);
			if (pCom->Data[4] & cbits[3]) Set_Lift_ForkOut_Jerk_Set_1(pSetParam, &nWriteParam);
			if (pCom->Data[4] & cbits[4]) Set_Lift_Invertor_Param_1(pSetParam, &nWriteParam);
			if (pCom->Data[3] & cbits[5]) Set_Lift_LevelUpOffset_1(pSetParam, &nWriteParam);
			if (pCom->Data[3] & cbits[6]) Set_Lift_LevelDnOffset_1(pSetParam, &nWriteParam);
			if (pCom->Data[3] & cbits[7]) Set_Lift_Veriant_LT_Offset_1(pSetParam, &nWriteParam);

			if (pCom->Data[4] & 0xFF)	is_save = 1;
		}
	}
	else
	{
		nError = 10;
	}

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 2);
	txPutcPort(port, (nError) ? 1 : 0);
	txPutcPort(port, nError);
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);
	sendTxBuf(port);

	if (!nError)
	{
		if (is_save == 1)
		{
			Save_Lift_Drive_Param(&nWriteParam);

			Update_Maintanance_SRM_Setting_Data();
		}
		else if (is_save == 2)
		{
			Save_Lift_Drive_Param(pSetParam);

			Update_Maintanance_SRM_Setting_Data();
		}
	}

	//m_TestStatus.Ctrl[DEBUG_CTR_11] = getCalcTimer1ms(nProcessTime);
#if DEBUG_MSG
	printf("[DEBUG_APP] Set Lift Drive Parameter ProcessTime : %ld ms\r\n", getCalcTimer1ms(nProcessTime));
#endif
}

/**
  * @brief
  * @param  port Receive Port
  * @param  pCom Pointer Receive Data
  * @retval None
  */
void rx_Fork_Drive_Paramter_Req(INT08U port, TMLComPTR pCom)
{
	ExtFlash_ReadData(EXT_PARAMETER_SET_ADDR_START, (INT08U*)&m_ExtSEnv2, sizeof(ExtFlashSEnv2));

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, sizeof(ParamForkDriveComSTR));
	txPutnPort(port, (INT08U*)&m_ExtSEnv2.ForkDrive, sizeof(ParamForkDriveComSTR));
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);
	sendTxBuf(port);
}

/**
  * @brief
  * @param  port Receive Port
  * @param  pCom Pointer Receive Data
  * @retval None
  */
void rx_Fork_Drive_Paramter_Set(INT08U port, TMLComPTR pCom)
{
	INT08U nError = 0;
	INT08U i = 0, is_save = 0;
	ParamForkDriveSTR* pSetParam;
	ParamForkDriveSTR nWriteParam;

	INT32U nProcessTime = 0;
	nProcessTime = m_pgmEnv.timer1ms;


	if (m_St.SRM_Mode.Bit.Setup)
	{
		pSetParam = (ParamForkDriveSTR*)&pCom->Data[35];

		if (pCom->Data[0] & 0x80)
		{
			for (i = 0; i < MAX_FORK_VELOCITY_CNT; i++)
			{
				if ((i >= 0) && (i <= 7))
				{
					Set_Fork_Velocity(i, &pSetParam->Vel[i]);
				}
				else if ((i >= 8) && (i <= 15))
				{
					Set_Fork_Velocity(i, &pSetParam->Vel[i]);
				}
			}


			Set_Fork_InPostion_Tolerance(pSetParam);
			Set_Fork_InPostion_Hysteresis(pSetParam);
			Set_Fork_Manual_Drive(pSetParam);
			Set_Fork_Encoder_Setup(pSetParam);
			Set_Fork_Origin_Offset(pSetParam);
			//Set_Fork_LagError_Offset(pSetParam);
			//Set_Fork_P_Gain(pSetParam);
			Set_Fork_Decelation_Control(pSetParam);
			Set_Fork_TwinFork_Setup(pSetParam);
			Set_Fork_Position_UseFlag(pSetParam);
			Set_Fork_Position_Depth(pSetParam);
			Set_Fork_Invertor_Param(pSetParam);

			is_save = 2;
		}
		else
		{
			memcpy((INT08U*)&nWriteParam, (INT08U*)&m_ExtSEnv2.ForkDrive, sizeof(ParamForkDriveSTR));

			for (i = 0; i < MAX_FORK_VELOCITY_CNT; i++)
			{
				if ((i >= 0) && (i <= 7))
				{
					if (pCom->Data[1] & cbits[i])
					{
						Set_Fork_Velocity_1(i, &pSetParam->Vel[i], &nWriteParam.Vel[i]);
						is_save = 1;
					}
				}
				else if ((i >= 8) && (i <= 15))
				{
					if (pCom->Data[2] & cbits[i - 8])
					{
						Set_Fork_Velocity_1(i, &pSetParam->Vel[i], &nWriteParam.Vel[i]);
						is_save = 1;
					}
				}
			}

			if (pCom->Data[3] & cbits[0])
			{
				Set_Fork_InPostion_Tolerance_1(pSetParam, &nWriteParam);
				Set_Fork_InPostion_Hysteresis_1(pSetParam, &nWriteParam);
				is_save = 1;
			}

			if (pCom->Data[3] & cbits[1]) Set_Fork_Manual_Drive_1(pSetParam, &nWriteParam);
			if (pCom->Data[3] & cbits[2]) is_save = Set_Fork_Encoder_Setup_1(pSetParam, &nWriteParam);
			if (pCom->Data[3] & cbits[3]) Set_Fork_Origin_Offset_1(pSetParam, &nWriteParam);
			//if (pCom->Data[3] & cbits[4]) Set_Fork_LagError_Offset_1(pSetParam, &nWriteParam);
			//if (pCom->Data[3] & cbits[5]) Set_Fork_P_Gain_1(pSetParam, &nWriteParam);
			if (pCom->Data[3] & cbits[6]) is_save = Set_Fork_Decelation_Control_1(pSetParam, &nWriteParam);
			if (pCom->Data[3] & cbits[7]) Set_Fork_TwinFork_Setup_1(pSetParam, &nWriteParam);

			if (pCom->Data[3] & 0xFF)	is_save = 1;

			if (pCom->Data[4] & cbits[0]) Set_Fork_Position_UseFlag_1(pSetParam, &nWriteParam);
			if (pCom->Data[4] & cbits[1]) Set_Fork_Position_Depth_1(pSetParam, &nWriteParam);
			if (pCom->Data[4] & cbits[2]) Set_Fork_Invertor_Param_1(pSetParam, &nWriteParam);

			if (pCom->Data[4] & 0x07)	is_save = 1;
		}
	}
	else
	{
		nError = 10;
	}

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 2);
	txPutcPort(port, (nError) ? 1 : 0);
	txPutcPort(port, nError);
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);
	sendTxBuf(port);

	if (!nError)
	{
		if (is_save == 1)
		{
			Save_Fork_Drive_Param(&nWriteParam);

			Update_Maintanance_SRM_Setting_Data();
		}
		else if (is_save == 2)
		{
			Save_Fork_Drive_Param(pSetParam);

			Update_Maintanance_SRM_Setting_Data();
		}
	}

	//m_TestStatus.Ctrl[DEBUG_CTR_12] = getCalcTimer1ms(nProcessTime);
#if DEBUG_MSG
	printf("[DEBUG_APP] Set Fork Drive Parameter ProcessTime : %ld ms\r\n", getCalcTimer1ms(nProcessTime));
#endif
}

void rxCmdNormalStop(INT08U port, TMLComPTR pCom)
{
	SRM_Normal_Stop();

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 1);
	txPutcPort(port, 0x00);
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);
	sendTxBuf(port);
}

void rxCmdEmergencyStop(INT08U port, TMLComPTR pCom)
{
	SRM_Emergency_Stop();

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 1);
	txPutcPort(port, 0x00);
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);
	sendTxBuf(port);
}

void rxCmdManual(INT08U port, TMLComPTR pCom)
{
	//ManualCmdSTR* pCtrl;
	//pCtrl = (ManualCmdSTR*)&pCom->Data[2];

	static INT32U s_RecvInternal;
	static INT32U s_Max_RecvInternal = 0;

	INT08U nResult = 0;

	if (m_pgmEnv.OrderRejectCondition & cbits[0])
	{
		if (m_St.SRM_Mode.Bit.Force)
		{
			asm volatile("NOP");
		}
		else
		{
			save_error_code(ERROR1_EMBERGENCY_STOP, 1, 0);
			nResult = 1;
		}
	}

	if (m_pgmEnv.OrderRejectCondition & cbits[1])
	{
		// 안전플러그 On 상태
		if (m_St.SRM_Status2.Bit.ManualSW)
		{
			// 기상반스위치 수동상태
			asm volatile("NOP");
		}
		else
		{
			if (m_St.SRM_Mode.Bit.Force == 1)
			{
				asm volatile("NOP");
			}
			else
			{
				save_error_code(ERROR1_SAFETY_PULG_ON, 1, 1);
				nResult = 1;
			}
		}
	}

	if (m_St.SRM_Mode.D == 0)
	{
		// 초기화 미완료 상태
		nResult = 1;
	}

	if (m_St.SRM_Status1.Bit.Fault)
	{
		if (m_St.SRM_Mode.Bit.Force)
		{
			// 에러상태에서 강제모드인 경우, 수동조작 허용.
			asm volatile ("NOP");
		}
		else
		{
			nResult = 1;
		}
	}

	if (m_St.SRM_Status2.Bit.ManualSW)
	{
		// 기상반 수동상태에서 상위 수동명령 수신
		Event_Warning_Code(WARNING_CODE_15, 0, 0);
		nResult = 1;
	}

	if (m_St.SRM_Mode.Bit.Auto)
	{
		// 자동모드에서 상위 수동명령 수신
		Event_Warning_Code(WARNING_CODE_10, 0, 0);
		nResult = 1;
	}

	/*
	m_TestStatus.Ctrl[DEBUG_CTR_15] = getCalcTimer1ms(s_RecvInternal);
	if (getCalcTimer1ms(s_RecvInternal) > s_Max_RecvInternal)
	{
		s_Max_RecvInternal = getCalcTimer1ms(s_RecvInternal);
		m_TestStatus.Ctrl[DEBUG_CTR_16] = s_Max_RecvInternal;
	}
	SetTimer1ms((INT32U*)&s_RecvInternal);
	*/

	if (m_ExtSEnv.Machine.mType.Fork_Type == FORK_TYPE_SINGLE_DEEP)
	{
		if (m_St.PosFork1.St_No == 0)
		{
			if ((m_pgmEnv.Move_PosFlag == MOVE_POSITION_FORK1_L) \
				|| (m_pgmEnv.Move_PosFlag == MOVE_POSITION_FORK2_L))
			{
				m_St.PosFork1.Row_ID = 1;
			}
			else if ((m_pgmEnv.Move_PosFlag == MOVE_POSITION_FORK1_R) \
				|| (m_pgmEnv.Move_PosFlag == MOVE_POSITION_FORK2_R))
			{
				m_St.PosFork1.Row_ID = 2;
			}
		}
		else
		{
			m_St.PosFork1.Row_ID = 0;
		}
	}
	else
	{
		if (m_St.PosFork1.St_No == 0)
		{
			if ((m_pgmEnv.Move_PosFlag == MOVE_POSITION_FORK1_L) \
				|| (m_pgmEnv.Move_PosFlag == MOVE_POSITION_FORK2_L))
			{
				m_St.PosFork1.Row_ID = 1;
			}
			else if ((m_pgmEnv.Move_PosFlag == MOVE_POSITION_FORK1_R) \
				|| (m_pgmEnv.Move_PosFlag == MOVE_POSITION_FORK2_R))
			{
				m_St.PosFork1.Row_ID = 4;
			}
		}
		else
		{
			m_St.PosFork1.Row_ID = 0;
		}
	}

	//m_pgmEnv.ManualCtrlTimer = m_pgmEnv.timer1ms;

	if (pCom->Data[0] & cbits[5])
	{
		if (pCom->Data[15] == 0)
		{
			m_St.Inv_St[INV_FORK_1].Status2.IO_Control = 0;
		}
		else
		{
			m_St.Inv_St[INV_FORK_1].Status2.IO_Control = 1;
		}
	}

	if (pCom->Data[0] & cbits[6])
	{
		if (pCom->Data[16] == 0)
		{
			m_St.Inv_St[INV_FORK_2].Status2.IO_Control = 0;
		}
		else
		{
			m_St.Inv_St[INV_FORK_2].Status2.IO_Control = 1;
		}
	}

	if (nResult == 0)
	{
		if (pCom->Data[0] & cbits[0])
		{
#if DISABLE_MANUAL_CTR_TRAVEL
			asm volatile("NOP");
#else
			nResult = Control_Manual_Trav_Start(pCom->Data[2], pCom->Data[17]);
#endif
		}

		if (pCom->Data[0] & cbits[1])
		{
			nResult = Control_Manual_Lift_Start(pCom->Data[3], pCom->Data[17]);
		}

		if (pCom->Data[0] & cbits[2])
		{
			m_pgmEnv.Manual_Fork_PositionFlag = pCom->Data[16];

			nResult = Control_Manual_Fork_Start(pCom->Data[4]);
		}

		if (pCom->Data[0] & cbits[5])
		{
			if (pCom->Data[15] == 1)
			{
				m_pgmEnv.Fork_IO_Manual_Control[FORK_1] = 1;
			}
			else
			{
				m_pgmEnv.Fork_IO_Manual_Control[FORK_1] = 0;
			}
		}

		if (pCom->Data[0] & cbits[6])
		{
			if (pCom->Data[16] == 1)
			{
				m_pgmEnv.Fork_IO_Manual_Control[FORK_2] = 1;
			}
			else
			{
				m_pgmEnv.Fork_IO_Manual_Control[FORK_2] = 0;
			}
		}
	}

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 1);
	txPutcPort(port, nResult);
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);
	sendTxBuf(port);
}

/**
  * @brief
  * @param  port Receive Port
  * @param  pCom Pointer Receive Data
  * @retval None
  */
void rxDemoControl(INT08U port, TMLComPTR pCom)
{
	INT08U nEnable = 0;
	INT08U nResult = 0;
#if DEBUG_MSG
	INT32U nProcessTime = 0;
	nProcessTime = m_pgmEnv.timer1ms;
#endif
	if (checkFusingString((INT08U*)m_ExtSEnv.mDevice.ProjectID.ProjectNo, (INT08U*)HANKOOK_TIRE_TP2, 6) == 0)
	{
		if ((m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_GT_LOT4) \
			|| (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_GT_LOT3) \
			|| (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_GT_LOT2) \
			|| (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_GT_LOT1))
		{
			nEnable = 2;
		}
	}

	if (nEnable)
	{
		if (m_pgmEnv.OrderRejectCondition & cbits[1])
		{
			save_error_code(ERROR1_SAFETY_PULG_ON, 1, 10);
			return;
		}

		if (m_St.SRM_Status2.Bit.ManualSW)
		{
			// 기상반 수동상태에서 상위 수동명령 수신
			Event_Warning_Code(WARNING_CODE_15, 0, 1);
			return;		// 기상반 수동
		}

		if (!m_St.SRM_Mode.Bit.Auto)  // 수동모드
		{
			nResult = 35;   // 수동모드 / 시작Off 동작중
		}
		else
		{
			if (nResult == 0)
			{
				m_pgmEnv.Demo_Control = pCom->Data[0];
				m_pgmEnv.Demo_Option = pCom->Data[1];
			}
		}

		clearTxBuf(port);
		rsPutmPort(port, FRAME_STX, 4);
		crcClear(port);
		txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 1);
		txPutcPort(port, nResult);
		txCRCPort(port);
		rsPutmPort(port, FRAME_ETX, 1);
		sendTxBuf(port);

#if DEBUG_MSG
		printf("[DEBUG_APP] Request Rack Config ProcessTime : %ld ms\r\n", getCalcTimer1ms(nProcessTime));
#endif
	}
}

/**
  * @brief
  * @param  port Receive Port
  * @param  pCom Pointer Receive Data
  * @retval None
  */
void rxScan_Position_Sensor_Control(INT08U port, TMLComPTR pCom)
{
	INT08U nResult = 0;
	INT08U nInvertor = 0;
#if DEBUG_MSG
	INT32U nProcessTime = 0;
	nProcessTime = m_pgmEnv.timer1ms;
#endif
	if (m_pgmEnv.OrderRejectCondition & cbits[0])
	{
		save_error_code(ERROR1_EMBERGENCY_STOP, 1, 0);
		return;
	}

	if (m_pgmEnv.OrderRejectCondition & cbits[1])
	{
		save_error_code(ERROR1_SAFETY_PULG_ON, 1, 8);
		return;
	}

	if (m_St.SRM_Status2.Bit.ManualSW)	return;		// 기상반 수동

	if (!m_St.SRM_Mode.Bit.Setup)  // 수동모드
	{
		nResult = 1;   // 수동모드 / 시작Off 동작중
	}
	else
	{
		nInvertor = pCom->Data[1] - 1;

		if (nInvertor == INV_TRAVEL)
		{
			if (pCom->Data[0] == 1)
			{
				if (m_pgmEnv.SRM_RunMode == RUN_SEQ_STAND_BY)
				{
					m_pgmEnv.SRM_RunMode = RUN_SEQ_TRAV_SCAN_SENSOR_0;
				}
				else
				{
					nResult = 1;
				}
			}
			else if (pCom->Data[0] == 0)
			{
				if ((m_pgmEnv.SRM_RunMode == RUN_SEQ_TRAV_SCAN_SENSOR_0)
					|| (m_pgmEnv.SRM_RunMode == RUN_SEQ_TRAV_SCAN_SENSOR_1))
				{
					m_pgmEnv.SRM_RunMode = RUN_SEQ_TRAV_SCAN_SENSOR_STOP;
				}
				else
				{
					nResult = 1;
				}
			}
			else
			{
				nResult = 1;
			}
		}
		else if (nInvertor == INV_HOIST)
		{
			if (pCom->Data[0] == 1)
			{
				if (m_pgmEnv.SRM_RunMode == RUN_SEQ_STAND_BY)
				{
					m_pgmEnv.SRM_RunMode = RUN_SEQ_LIFT_SCAN_SENSOR_0;
				}
				else
				{
					nResult = 1;
				}
			}
			else if (pCom->Data[0] == 0)
			{
				if ((m_pgmEnv.SRM_RunMode == RUN_SEQ_LIFT_SCAN_SENSOR_0)
					|| (m_pgmEnv.SRM_RunMode == RUN_SEQ_LIFT_SCAN_SENSOR_1))
				{
					m_pgmEnv.SRM_RunMode = RUN_SEQ_LIFT_SCAN_SENSOR_STOP;
				}
				else
				{
					nResult = 1;
				}
			}
			else
			{
				nResult = 1;
			}
		}
		else if (nInvertor == INV_FORK_1)
		{
			if (pCom->Data[0] == 1)
			{
				if (m_pgmEnv.SRM_RunMode == RUN_SEQ_STAND_BY)
				{
					m_pgmEnv.SRM_RunMode = RUN_SEQ_FORK_SCAN_SENSOR_0;
				}
				else
				{
					nResult = 1;
				}
			}
			else if (pCom->Data[0] == 0)
			{
				if ((m_pgmEnv.SRM_RunMode == RUN_SEQ_FORK_SCAN_SENSOR_0)
					|| (m_pgmEnv.SRM_RunMode == RUN_SEQ_FORK_SCAN_SENSOR_1))
				{
					m_pgmEnv.SRM_RunMode = RUN_SEQ_FORK_SCAN_SENSOR_STOP;
				}
				else
				{
					nResult = 1;
				}
			}
			else
			{
				nResult = 1;
			}
		}
		else
		{
			nResult = 1;
		}
	}

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 1);
	txPutcPort(port, nResult);
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);
	sendTxBuf(port);

#if DEBUG_MSG
	printf("[DEBUG_APP] Request Scan Position Sensor ProcessTime : %ld ms\r\n", getCalcTimer1ms(nProcessTime));
#endif
}

void txAlarmLog(INT08U port, TMLComPTR pCom, INT16U req_inx, INT08U req_type, INT32U start_time, INT32U end_time)
{
	INT16U i;
	INT16U start = 0;
	INT16U tot_cnt = 0;
	INT08U now_cnt = 0;
	INT16U pos = 0;
	INT08U one_size = 0;

#if DEF_ALARM_LOG_TYPE == 1 
	INT08U nMax_Cnt = 30;
#elif DEF_ALARM_LOG_TYPE == 2
	INT08U nMax_Cnt = 20;
#endif

	if (req_inx < MAX_ALARM_LOG_COUNT)
	{
		if (m_BKSram.AlarmLog.Repeat)
		{
			tot_cnt = MAX_ALARM_LOG_COUNT;

			now_cnt = tot_cnt - req_inx;
			if (now_cnt > nMax_Cnt)
			{
				now_cnt = nMax_Cnt;
			}
			else
			{
				now_cnt = tot_cnt - req_inx;
			}

			start = (m_BKSram.AlarmLog.Inx + req_inx) % MAX_ALARM_LOG_COUNT;
		}
		else
		{
			if (m_BKSram.AlarmLog.Inx)
			{
				tot_cnt = m_BKSram.AlarmLog.Inx;
				now_cnt = tot_cnt - req_inx;
				if (now_cnt > nMax_Cnt)
				{
					now_cnt = nMax_Cnt;
				}
				else
				{
					now_cnt = tot_cnt - req_inx;
				}

				start = req_inx;
			}
			else
			{
				start = 0;
				tot_cnt = 0;
				now_cnt = 0;
			}
		}
	}
	else
	{
		start = 0;
		tot_cnt = 0;
		now_cnt = 0;
	}

#if DEF_ALARM_LOG_TYPE == 1
	one_size = sizeof(UniLogSTR_Type1);
#elif DEF_ALARM_LOG_TYPE == 2
	one_size = sizeof(UniLogSTR_Type2);
#endif
	//m_TestStatus.Ctrl[DEBUG_CTR_15] = one_size;

	if (1/*tot_cnt*/)
	{
		clearTxBuf(port);
		rsPutmPort(port, FRAME_STX, 4);
		crcClear(port);
		txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, (now_cnt * one_size) + 7);
		txPutwPort(port, tot_cnt);
		txPutwPort(port, req_inx);
		txPutcPort(port, now_cnt);
#if DEF_ALARM_LOG_TYPE == 1
		txPutcPort(port, 1);		// 로그 데이터 형식 1
#elif DEF_ALARM_LOG_TYPE == 2
		txPutcPort(port, 2);		// 로그 데이터 형식 2
#endif
		
		txPutcPort(port, 0);					// 항목별 음수처리 유무
		for (i = 0; i < now_cnt; i++)
		{
			//pos = (start + req_inx + i) % MAX_ALARM_LOG_COUNT;
			pos = (start + i) % MAX_ALARM_LOG_COUNT;
			txPutnPort(port, (INT08U*)&m_BKSram.AlarmLog.Log[pos].SysTime, one_size);
		}
		txCRCPort(port);
		rsPutmPort(port, FRAME_ETX, 1);
		sendTxBuf(port);
	}
}

void rxAlarmLogRequest(INT08U port, TMLComPTR pCom)
{
	INT16U req_inx = 0;
	INT08U req_type = 0;
	INT08U log_type = 0;
	INT32U start_time = 0;
	INT32U end_time = 0;

	/*
	req_inx = ((INT16U)pCom->Data[0] << 0) | ((INT16U)pCom->Data[1] << 8);
	req_type = pCom->Data[2];
	log_type = pCom->Data[3];
	start_time = ((INT32U)pCom->Data[4] << 0) | ((INT32U)pCom->Data[5] << 8) | ((INT32U)pCom->Data[6] << 16) | ((INT32U)pCom->Data[7] << 24);
	end_time = ((INT32U)pCom->Data[8] << 0) | ((INT32U)pCom->Data[9] << 8) | ((INT32U)pCom->Data[10] << 16) | ((INT32U)pCom->Data[11] << 24);
	*/

	log_type = pCom->Data[0];
	req_type = pCom->Data[1];
	req_inx = ((INT16U)pCom->Data[2] << 0) | ((INT16U)pCom->Data[3] << 8);
	start_time = ((INT32U)pCom->Data[4] << 0) | ((INT32U)pCom->Data[5] << 8) | ((INT32U)pCom->Data[6] << 16) | ((INT32U)pCom->Data[7] << 24);
	end_time = ((INT32U)pCom->Data[8] << 0) | ((INT32U)pCom->Data[9] << 8) | ((INT32U)pCom->Data[10] << 16) | ((INT32U)pCom->Data[11] << 24);

	//m_TestStatus.Ctrl[DEBUG_CTR_6] = start_time;
	//m_TestStatus.Ctrl[DEBUG_CTR_8] = end_time;

	if (log_type == 0) // 0:AlarmLog, 1:EventLog
	{
		txAlarmLog(port, (TMLComPTR)pCom, req_inx, req_type, start_time, end_time);
	}
	else
	{
		//txEventLog(port, (TMLComPTR)pCom, req_inx, req_type, start_time, end_time);
	}
}

void rxAlarmLogDelete(INT08U port, TMLComPTR pCom)
{
	INT08U nResult = 1;

	if (pCom->Data[0] == 1)
	{
		//ClearEventLog();

		nResult = 0;
	}
	else if (pCom->Data[0] == 0)
	{
		/*
		m_BKSram.AlarmLog.Repeat = 0;
		m_BKSram.AlarmLog.Inx = 0;
		*/
		memset((INT08U*)&m_BKSram.AlarmLog, 0, sizeof(AlarmLogSTR));

		saveBKSramSTR();

		nResult = 0;
	}

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 1);
	txPutcPort(port, nResult);
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);
	sendTxBuf(port);
}

void rxDSP_Status(INT08U port, TMLComPTR pCom)
{
	DspStatusSTR* pData;
	INT08U nSlaveIndex = 0;

	if (pCom->Header.SrcID.Type == COM_ID_DSP)
	{
		nSlaveIndex = pCom->Header.SrcID.Index - 1;

		if (nSlaveIndex < 2)
		{
			m_Recv_DSP_ID = pCom->Header.SrcID.Index;

			pData = (DspStatusSTR*)&pCom->Data[0];

			memcpy((INT08U*)&m_DspStatus[nSlaveIndex], pData, sizeof(DspStatusSTR));
		}
	}
}

void rxDSP_Control(INT08U port, TMLComPTR pCom)
{
	RecvDspData* pData;
	INT08U nSlaveIndex = 0;

	if (pCom->Header.SrcID.Type == COM_ID_DSP)
	{
		nSlaveIndex = pCom->Header.SrcID.Index - 1;

		if (nSlaveIndex < 2)
		{
			m_Recv_DSP_ID = pCom->Header.SrcID.Index;

			pData = (RecvDspData*)&pCom->Data[0];

			memcpy((INT08U*)&m_RecvDspData[nSlaveIndex], pData, sizeof(RecvDspData));
		}
	}
}

/**
  * @brief
  * @param  port 수신 포트
  * @param  pCom 수신 데이터
  * @retval None
  */
void rxMcuTestReq(INT08U port, TMLComPTR pCom)
{
	McuTestCtrSTR* pTestCtr;
#if DEBUG_MSG
	/*
	INT32U nProcessTime = 0;
	nProcessTime = m_pgmEnv.timer1ms;
	*/
#endif
	pTestCtr = (McuTestCtrSTR*)&pCom->Data[0];

	if (port == rsMCU_DEBUG_Port)
	{
		//++m_TestStatus.Ctrl[DEBUG_CTR_1];
	}
	else if (port == rsTMLPort)
	{
		//++m_TestStatus.Ctrl[DEBUG_CTR_2];
	}

	memcpy((INT08U*)&m_McuTestCtr, (INT08U*)pTestCtr, sizeof(McuTestCtrSTR));

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);                                        // STX : 0x16 0x16 0x16 0x16
	crcClear(port);                                                      // Clear CRC
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, sizeof(McuTestStSTR));
	txPutnPort(port, (INT08U*)&m_McuTestSt, sizeof(McuTestStSTR));                  // Data
	txCRCPort(port);                                                      // Transmit CRC
	rsPutmPort(port, FRAME_ETX, 1);                                        // ETX : 0xF5
	sendTxBuf(port);

#if DEBUG_MSG
	//printf("[DEBUG_APP] Request Device Status ProcessTime : %ld ms\r\n", getCalcTimer1ms(nProcessTime));
#endif
}

/**
  * @brief
  * @param None
  * @retval None
  */
void Send_Read_Invertor_Parameter()
{
	INT08U nPort = 0;
	ComHeaderSTR nHeader;

	nPort = m_pgmEnv.InvParamCtr.RecvComPort;
	memcpy((INT08U*)&nHeader, (INT08U*)&m_pgmEnv.InvParamCtr.RecvHeader, sizeof(ComHeaderSTR));

	clearTxBuf(nPort);
	rsPutmPort(nPort, FRAME_STX, 4);
	crcClear(nPort);
	txPutHeader(nPort, (ComHeaderSTR*)&nHeader, nHeader.Cmd | 0x80, nHeader.Cmd2, sizeof(InvParamData_t) + 1);
	txPutcPort(nPort, 1);		// 1: SRM
	txPutnPort(nPort, (INT08U*)&m_pgmEnv.InvParamCtr.rData, sizeof(InvParamData_t));
	txCRCPort(nPort);
	rsPutmPort(nPort, FRAME_ETX, 1);
	sendTxBuf(nPort);
}

/**
  * @brief
  * @param None
  * @retval None
  */
void Send_Write_Invertor_Parameter(INT08U nAck)
{
	INT08U nPort = 0;
	ComHeaderSTR nHeader;

	nPort = m_pgmEnv.InvParamCtr.RecvComPort;
	memcpy((INT08U*)&nHeader, (INT08U*)&m_pgmEnv.InvParamCtr.RecvHeader, sizeof(ComHeaderSTR));

	clearTxBuf(nPort);
	rsPutmPort(nPort, FRAME_STX, 4);
	crcClear(nPort);
	txPutHeader(nPort, (ComHeaderSTR*)&nHeader, nHeader.Cmd | 0x80, nHeader.Cmd2, 2);
	txPutcPort(nPort, 1);		// 1: SRM
	txPutcPort(nPort, m_pgmEnv.InvParamCtr.wData.Drive);
	txPutcPort(nPort, 0);		// 0: ACK, 1: NACK
	txCRCPort(nPort);
	rsPutmPort(nPort, FRAME_ETX, 1);
	sendTxBuf(nPort);
}

/**
  * @brief
  * @param  port Receive Port
  * @param  pCom Pointer Receive Data
  * @retval None
  */
void rxInvertorParameterReq(INT08U port, TMLComPTR pCom)
{
	INT08U nType = 0, nLen = 0;;
	InvParamData_t nTemp;
	WORD_User nWord;

	nType = pCom->Data[nLen];	++nLen;

	memset((INT08U*)&nTemp, 0, sizeof(InvParamData_t));
	nTemp.Drive = pCom->Data[nLen];		++nLen;

	if (nType == 1)
	{
		// SRM 
		m_pgmEnv.InvParamCtr.RecvComPort = port;
		memcpy((INT08U*)&m_pgmEnv.InvParamCtr.RecvHeader, (INT08U*)&pCom->Header, sizeof(ComHeaderSTR));

		/*
		nWord.B[1] = pCom->Data[nLen];		++nLen;
		nWord.B[0] = pCom->Data[nLen];		++nLen;
		nTemp.Main_Addr = nWord.W;

		nWord.B[1] = pCom->Data[nLen];		++nLen;
		nWord.B[0] = pCom->Data[nLen];		++nLen;
		nTemp.Sub_Addr = nWord.W;
		*/
		nWord.B[0] = pCom->Data[nLen];		++nLen;
		nWord.B[1] = pCom->Data[nLen];		++nLen;
		nTemp.Main_Addr = nWord.W;

		nWord.B[0] = pCom->Data[nLen];		++nLen;
		nWord.B[1] = pCom->Data[nLen];		++nLen;
		nTemp.Sub_Addr = nWord.W;

		m_pgmEnv.InvParamCtr.Mode = 1;
		m_pgmEnv.InvParamCtr.rData.Drive = nTemp.Drive;
		m_pgmEnv.InvParamCtr.rData.Main_Addr = nTemp.Main_Addr;
		m_pgmEnv.InvParamCtr.rData.Sub_Addr = nTemp.Sub_Addr;

		/*
		// Test Code
		if ((m_pgmEnv.InvParamCtr.rData.Main_Addr == 8404) && (m_pgmEnv.InvParamCtr.rData.Sub_Addr == 4))
		{
			m_pgmEnv.InvParamCtr.rData.Data = 100;
		}
		else if ((m_pgmEnv.InvParamCtr.rData.Main_Addr == 8404) && (m_pgmEnv.InvParamCtr.rData.Sub_Addr == 5))
		{
			m_pgmEnv.InvParamCtr.rData.Data = 40;
		}
		else if ((m_pgmEnv.InvParamCtr.rData.Main_Addr == 8510) && (m_pgmEnv.InvParamCtr.rData.Sub_Addr == 4))
		{
			if (m_pgmEnv.InvParamCtr.rData.Drive == 1)
			{
				m_pgmEnv.InvParamCtr.rData.Data = 42602;
			}
			else if (m_pgmEnv.InvParamCtr.rData.Drive == 2)
			{
				m_pgmEnv.InvParamCtr.rData.Data = 2802;
			}
			else if (m_pgmEnv.InvParamCtr.rData.Drive == 3)
			{
				m_pgmEnv.InvParamCtr.rData.Data = 18259;
			}
		}
		else if ((m_pgmEnv.InvParamCtr.rData.Main_Addr == 8550) && (m_pgmEnv.InvParamCtr.rData.Sub_Addr == 2))
		{
			m_pgmEnv.InvParamCtr.rData.Data = 50;
		}
		else if ((m_pgmEnv.InvParamCtr.rData.Main_Addr == 8357) && (m_pgmEnv.InvParamCtr.rData.Sub_Addr == 15))
		{
			m_pgmEnv.InvParamCtr.rData.Data = 100;
		}

		Send_Read_Invertor_Parameter();		// 통신 테스트 후 삭제
		*/
	}
	else
	{
		clearTxBuf(port);
		rsPutmPort(port, FRAME_STX, 4);
		crcClear(port);
		txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, \
			pCom->Header.Cmd2, sizeof(InvParamData_t) + 1);
		txPutcPort(port, nType);
		txPutnPort(port, (INT08U*)&nTemp, sizeof(InvParamData_t));
		txCRCPort(port);
		rsPutmPort(port, FRAME_ETX, 1);
		sendTxBuf(port);
	}

#if DEBUG_MSG
	printf("[DEBUG_APP] Read Inverter Parameter Type: %d, Drive:%d, M_Addr: %d, S_Addr: %d\r\n", \
		nType, nTemp.Drive, nTemp.Main_Addr, nTemp.Sub_Addr);
#endif
}

/**
  * @brief
  * @param  port Receive Port
  * @param  pCom Pointer Receive Data
  * @retval None
  */
void rxInvertorParameterSet(INT08U port, TMLComPTR pCom)
{
	INT08U nType = 0, nLen = 0, nDrive = 0;
	InvParamData_t* pWriteParam;

	nType = pCom->Data[nLen];	++nLen;

	pWriteParam = (InvParamData_t*)&pCom->Data[nLen];
	memcpy((INT08U*)&m_pgmEnv.InvParamCtr.wData, (INT08U*)pWriteParam, sizeof(InvParamData_t));

	if (nType == 1)
	{
		m_pgmEnv.InvParamCtr.RecvComPort = port;
		memcpy((INT08U*)&m_pgmEnv.InvParamCtr.RecvHeader, (INT08U*)&pCom->Header, sizeof(ComHeaderSTR));
		m_pgmEnv.InvParamCtr.Mode = 2;

		Send_Write_Invertor_Parameter(0);	// 통신 테스트 후 삭제
	}
	else
	{
		clearTxBuf(port);
		rsPutmPort(port, FRAME_STX, 4);
		crcClear(port);
		txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, \
			pCom->Header.Cmd2, 2);
		txPutcPort(port, nType);
		txPutcPort(port, pWriteParam->Drive);
		txPutcPort(port, 1);
		txCRCPort(port);
		rsPutmPort(port, FRAME_ETX, 1);
		sendTxBuf(port);
	}

#if DEBUG_MSG
	printf("[DEBUG_APP] Write Inverter Parameter Type: %d, Drive:%d, M_Addr: %d, S_Addr: %d Data: %ld\r\n", \
		nType, pWriteParam->Drive, pWriteParam->Main_Addr, pWriteParam->Sub_Addr, pWriteParam->Data);
#endif
}

/**
  * @brief  RS232 수신데이터 처리
  * @param  port 수신 포트
  * @param  pCom 수신데이터 버퍼 포인터
  * @retval None
  */
void rxDataAnalysis(INT08U port, TMLComPTR pCom)
{
	//m_TestStatus.Ctrl[DEBUG_CTR_3] = pCom->Header.DstID.Type;
	//m_TestStatus.Ctrl[DEBUG_CTR_4] = pCom->Header.DstID.Index;

	if ((port != rsTMLPort) && (port != rsMCU_DEBUG_Port))
	{
		if (m_pgmEnv.MCU_Test_Mode)
		{
			asm volatile("NOP");
		}
		else
		{
			if (pCom->Header.SrcID.Type != COM_ID_HT100)
			{
				if (pCom->Header.DstID.Type != COM_ID_SRM)	return;
				if (pCom->Header.DstID.Index != m_DevStatus.ProjectID.Device_ID)	return;
			}
		}
	}

	//m_TestStatus.St[DEBUG_STR_19] = pCom->Header.Seq;

	if (pCom->Header.Cmd == 0x00)
	{
		switch (pCom->Header.Cmd2)
		{
		case TY_STATUS_REQ:
			if (pCom->Header.SrcID.Type == COM_ID_GCP)
			{
				++m_pgmEnv.RxStatus_Cnt;
				m_pgmEnv.RxStatus_Flag = 1;
				m_pgmEnv.GCP_Connect = 1;
			}
			
			rxStatusReq(port, (TMLComPTR)pCom);      
			break;

		case TY_ALARMLOG_REQUEST: rxAlarmLogRequest(port, (TMLComPTR)pCom);      break;
		case TY_ALARMLOG_DELETE: rxAlarmLogDelete(port, (TMLComPTR)pCom);      break;

		case TY_OPERATION_INFO_REQ: rxOperationInfo_Req(port, (TMLComPTR)pCom);      break;

		case TY_INVERTOR_INFO_REQ: rxInvertorInfo_Req(port, (TMLComPTR)pCom);      break;

		case TY_CMD_TASK_ORDER: rxTaskCmdOrder(port, (TMLComPTR)pCom);      break;

		case TY_CMD_ORDER: rxCmdOrder(port, (TMLComPTR)pCom);      break;

		case TY_CMD_REFERENCE: rxCmdReferenceSearch(port, (TMLComPTR)pCom);      break;

		case TY_CMD_START: rxCmdStart(port, (TMLComPTR)pCom);      break;
		case TY_CMD_MOVE_HOME: rxCmd_MoveHome(port, (TMLComPTR)pCom); break;
		case TY_CMD_MOVE_MAINTANENCE: rxCmdMoveMaintanence(port, (TMLComPTR)pCom); break;

		case TY_CMD_ERROR_RESET: rxCmdErrorReset(port, (TMLComPTR)pCom);      break;
		case TY_CMD_ORDER_DELETE: rxCmdOrderDelete(port, (TMLComPTR)pCom);	break;

		case TY_NORMAL_STOP_REQ: rxCmdNormalStop(port, (TMLComPTR)pCom);      break;

		case TY_EMERGENCY_STOP_REQ: rxCmdEmergencyStop(port, (TMLComPTR)pCom);      break;

		case TY_MODE_CHANGE: rxModeChange(port, (TMLComPTR)pCom);      break;

		case TY_CMD_MANUAL:	rxCmdManual(port, (TMLComPTR)pCom);      break;

		case TY_INVERTOR_PARAM_REQ: rxInvertorParameterReq(port, (TMLComPTR)pCom);      break;
		case TY_INVERTOR_PARAM_SET: rxInvertorParameterSet(port, (TMLComPTR)pCom);      break;

			/*case TY_RACK_ENV_REQ: rxRackEnvReq(port, (TMLComPTR)pCom);      break;*/
			/*case TY_RACK_ENV_SET: rxRackEnvSet(port, (TMLComPTR)pCom);      break;*/

		case TY_CELL_ENV_REQ: rxCellEnvReq(port, (TMLComPTR)pCom);      break;
		case TY_CELL_ENV_SET: rxCellEnvSet(port, (TMLComPTR)pCom);      break;
			
		case TY_CELL_OFFSET_ENV_REQ: rxCell_Offset_EnvReq(port, (TMLComPTR)pCom);      break;
		case TY_CELL_OFFSET_ENV_SET: rxCell_Offset_EnvSet(port, (TMLComPTR)pCom);      break;

		case TY_STATION_ENV_REQ: rxStationEnvReq(port, (TMLComPTR)pCom); break;
		case TY_STATION_ENV_SET: rxStationEnvSet(port, (TMLComPTR)pCom); break;

		case TY_PROHIBIT_RACK_ENV_REQ: rxProhibitRackEnvReq(port, (TMLComPTR)pCom); break;
		case TY_PROHIBIT_RACK_ENV_SET: rxProhibitRackEnvSet(port, (TMLComPTR)pCom); break;

		case TY_SPECIAL_RACK_ENV_REQ: rxSpecialRackEnvReq(port, (TMLComPTR)pCom); break;
		case TY_SPECIAL_RACK_ENV_SET: rxSpecialRackEnvSet(port, (TMLComPTR)pCom); break;

		case TY_SETUP_INITIALIZE_SET: rxRackEnvInitializeSet(port, (TMLComPTR)pCom); break;

		case TY_CONTROL_REQ: rxControlParamterReq(port, (TMLComPTR)pCom); break;
		case TY_CONTROL_SET: rxControlParamterSet(port, (TMLComPTR)pCom); break;

		case TY_TRAVEL_DRIVE_REQ: rxTravelDriveParamterReq(port, (TMLComPTR)pCom); break;
		case TY_TRAVEL_DRIVE_SET: rxTravelDriveParamterSet(port, (TMLComPTR)pCom); break;

		case TY_LIFT_DRIVE_REQ: rxLiftDriveParamterReq(port, (TMLComPTR)pCom); break;
		case TY_LIFT_DRIVE_SET: rxLiftDriveParamterSet(port, (TMLComPTR)pCom); break;

		case TY_FORK_DRIVE_REQ: rx_Fork_Drive_Paramter_Req(port, (TMLComPTR)pCom); break;
		case TY_FORK_DRIVE_SET: rx_Fork_Drive_Paramter_Set(port, (TMLComPTR)pCom); break;

		//case TY_READ_GROUP_LIST: rxHT100_GroupListReq(port, (TMLComPTR)pCom); break;
		//case TY_READ_PARAM_LIST: ++m_TestStatus.St[DEBUG_STR_32]; break;

// 		case TY_READ_PARAM_INFO: rxHT100_ParamInfo(port, (TMLComPTR)pCom); break;
// 		case TY_WRITE_PARAM_SET: rxHT100_WriteParamSet(port, (TMLComPTR)pCom); break;

		//case TY_MCU_TEST: rxMcuTestReq(port, (TMLComPTR)pCom);	break;
		}
	}
	else if (pCom->Header.Cmd == 0x01)
	{
		switch (pCom->Header.Cmd2)
		{
		case TY_DEVICE_STATUS: rxDeviceStatusReq(port, (TMLComPTR)pCom);      break;
		case TY_DEVICE_CONTROL: rxDeviceControlReq(port, (TMLComPTR)pCom);      break;
		case TY_TEST_STATUS: rxTestStatusReq(port, (TMLComPTR)pCom);      break;
		case TY_TEST_CONTROL: rxTestControlReq(port, (TMLComPTR)pCom);      break;
		case TY_GRAPH_REQUEST: rxGraphRequest(port, (TMLComPTR)pCom);      break;
		case TY_MANUNAL_OUTPUT_CONTROL: rxManualOutCTR_Request(port, (TMLComPTR)pCom);      break;

		case TY_DOWNLOAD_START: rxDownloadStart(port, (TMLComPTR)pCom);      break;
		case TY_DOWNLOAD_DATA: rxDownloadData(port, (TMLComPTR)pCom);      break;
		case TY_DOWNLOAD_END: rxDownloadFinish(port, (TMLComPTR)pCom);      break;

		case TY_FUNC_CONTROL: rxFuncControlReq(port, (TMLComPTR)pCom);      break;

		case TY_DIO_FORM_REQ: rxDigital_IO_Form_Req(port, (TMLComPTR)pCom);      break;
		case TY_DIO_FORM_CONTROL: rxDigital_IO_Form_Control(port, (TMLComPTR)pCom);      break;

		case TY_MACHINE_SPEC_STATUS: rxMachine_Type_Req(port, (TMLComPTR)pCom);      break;
		case TY_MACHINE_SPEC_CONTROL: rxMachine_Type_Set(port, (TMLComPTR)pCom);      break;

		case TY_INVERTOR_PARAM_REQ: rxInvertorParameterReq(port, (TMLComPTR)pCom);      break;
		case TY_INVERTOR_PARAM_SET: rxInvertorParameterSet(port, (TMLComPTR)pCom);      break;

			/*case TY_RACK_ENV_REQ: rxRackEnvReq(port, (TMLComPTR)pCom);      break;*/
			/*case TY_RACK_ENV_SET: rxRackEnvSet(port, (TMLComPTR)pCom);      break;*/

		case TY_CELL_ENV_REQ: rxCellEnvReq(port, (TMLComPTR)pCom);      break;
		case TY_CELL_ENV_SET: rxCellEnvSet(port, (TMLComPTR)pCom);      break;

		case TY_CELL_OFFSET_ENV_REQ: rxCell_Offset_EnvReq(port, (TMLComPTR)pCom);      break;
		case TY_CELL_OFFSET_ENV_SET: rxCell_Offset_EnvSet(port, (TMLComPTR)pCom);      break;

		case TY_STATION_ENV_REQ: rxStationEnvReq(port, (TMLComPTR)pCom); break;
		case TY_STATION_ENV_SET: rxStationEnvSet(port, (TMLComPTR)pCom); break;

		case TY_PROHIBIT_RACK_ENV_REQ: rxProhibitRackEnvReq(port, (TMLComPTR)pCom); break;
		case TY_PROHIBIT_RACK_ENV_SET: rxProhibitRackEnvSet(port, (TMLComPTR)pCom); break;

		case TY_SPECIAL_RACK_ENV_REQ: rxSpecialRackEnvReq(port, (TMLComPTR)pCom); break;
		case TY_SPECIAL_RACK_ENV_SET: rxSpecialRackEnvSet(port, (TMLComPTR)pCom); break;

		case TY_SETUP_INITIALIZE_SET: rxRackEnvInitializeSet(port, (TMLComPTR)pCom); break;

		case TY_CONTROL_REQ: rxControlParamterReq(port, (TMLComPTR)pCom); break;
		case TY_CONTROL_SET: rxControlParamterSet(port, (TMLComPTR)pCom); break;

		case TY_TRAVEL_DRIVE_REQ: rxTravelDriveParamterReq(port, (TMLComPTR)pCom); break;
		case TY_TRAVEL_DRIVE_SET: rxTravelDriveParamterSet(port, (TMLComPTR)pCom); break;

		case TY_LIFT_DRIVE_REQ: rxLiftDriveParamterReq(port, (TMLComPTR)pCom); break;
		case TY_LIFT_DRIVE_SET: rxLiftDriveParamterSet(port, (TMLComPTR)pCom); break;

		case TY_FORK_DRIVE_REQ: rx_Fork_Drive_Paramter_Req(port, (TMLComPTR)pCom); break;
		case TY_FORK_DRIVE_SET: rx_Fork_Drive_Paramter_Set(port, (TMLComPTR)pCom); break;

		case TY_CMD_DEMO_CONTROL:	rxDemoControl(port, (TMLComPTR)pCom);	break;

		case TY_CMD_SCAN_POSITION_SENSOR: rxScan_Position_Sensor_Control(port, (TMLComPTR)pCom); break;

		case TY_ALARMLOG_REQUEST: rxAlarmLogRequest(port, (TMLComPTR)pCom);      break;
		case TY_ALARMLOG_DELETE: rxAlarmLogDelete(port, (TMLComPTR)pCom);      break;

		case TY_MCU_TEST: rxMcuTestReq(port, (TMLComPTR)pCom);	break;
		}
	}
	else if (pCom->Header.Cmd == 0x81)
	{
		// MCU 요청 후 응답데이터 처리
		switch (pCom->Header.Cmd2)
		{
			//case TY_DSP_STATUS: rxDSP_Status(port, (TMLComPTR)pCom);	break;
		}
	}
	else if (pCom->Header.Cmd == 0x82)
	{
		// MCU 요청 후 응답데이터 처리
		switch (pCom->Header.Cmd2)
		{
		case TY_DSP_STATUS: rxDSP_Status(port, (TMLComPTR)pCom);	break;
		case TY_DSP_DATA: rxDSP_Control(port, (TMLComPTR)pCom);	break;
		}
	}
	else
	{
		switch (pCom->Header.Cmd2)
		{
		case TY_DEVICE_STATUS: rxDeviceStatusReq(port, (TMLComPTR)pCom);      break;

		case TY_MCU_TEST: rxMcuTestReq(port, (TMLComPTR)pCom);	break;
		}

	}

	if (port < 20)
	{
		m_pgmEnv.PortLinkSt[port] = 1;
		m_pgmEnv.PortLinkTimer[port] = m_pgmEnv.timer1ms;
	}
}

/**
  * @brief  RS232 Communication.
  * @param  None
  * @retval None
  */
void TMLComManager(void)
{
	static INT08U s_Init;

	if (!s_Init)
	{
		s_Init = 1;
		__HAL_UART_ENABLE_IT(&huart3, UART_IT_RXNE);
	}
	else
	{
		if (rsIsData)
		{
#if DEBUG_TML_MSG
			printf("[TML] Receive SRC Type:%02x ID:%02x DST Type:%02x ID:%02x CMD1:%02x CMD2:%02x\r\n",
				TMLCom.Header.SrcID.Type, TMLCom.Header.SrcID.Index, TMLCom.Header.DstID.Type, TMLCom.Header.DstID.Index
				, TMLCom.Header.Cmd, TMLCom.Header.Cmd2);
#endif

			rxDataAnalysis(rsTMLPort, (TMLComPTR)&TMLCom);
			rsIsData = 0;

			m_pgmEnv.TmlConnectTimer = m_pgmEnv.timer1ms;
			m_pgmEnv.TmlConnect = 1;

			rsComMode = 0;
			rsComLen = 0;
		}

		{
			if (rsComMode)
			{
				if (getCalcTimer1ms(m_Rx_com_chkTimer) >= 20)
				{
					rsComMode = 0;
					rsComLen = 0;
				}
			}
		}

		if (getCalcTimer1ms(m_pgmEnv.TmlConnectTimer) >= 3000)
		{
			m_pgmEnv.TmlConnect = 0;
		}
	}
}
