/**
  ******************************************************************************
  * @file            : com_hmi.c
  * @author          :
  * @version         :
  * @brief           : This file implements HMI Communication
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

#include "main.h"
#include "type.h"
#include "User_Define.h"
#include "uart.h"
#include "com_tml.h"
#include "com_hmi.h"
#include "alarm.h"

extern SRAM_HandleTypeDef hsram3;
extern UART_HandleTypeDef huart6;

extern UartQSTR		m_TxUartQ[MAX_UART_PORT];

//extern TMLComSTR	TMLCom;

static TMLComSTR	HMICom;

#define RS485_MODE		(0)		// 0 : RS422
//#define RS485_MODE		(1)		// 0 : RS422, 1: RS485

 /**
   * @brief
   * @param  None
   * @retval None
   */
void RS485_Mode_Control(INT08U nFlag)
{
	INT08U out_data = 0;

	if (nFlag == RS485_RX_MODE)
	{
		out_data &= nbits[0];	//	UART6_/RE #1 - Level low 
		out_data &= nbits[1];	//	UART6_DE #1 - Level low 
		out_data |= cbits[2];	//	UART6_/RE #2 - Level high 
		out_data |= cbits[3];	//	UART6_DE #2 - Level high 
	}
	else if (nFlag == RS485_TX_MODE)
	{
		out_data |= cbits[0];	//	UART6_/RE #1 - Level high 
		out_data |= cbits[1];	//	UART6_DE #1 - Level high 
		out_data |= cbits[2];	//	UART6_/RE #2 - Level high 
		out_data |= cbits[3];	//	UART6_DE #2 - Level high 
	}

	HAL_SRAM_Write_8b(&hsram3, (INT32U*)ADDR_FSMC_IOCS_RS422_485, &out_data, 1);
}

/**
  * @brief
  * @param  None
  * @retval None
  */
void RS422_Mode_Enable(void)
{
	INT08U out_data = 0;

	///*
	out_data |= cbits[0];	//	UART6_/RE #1 - Level High
	out_data |= cbits[1];	//	UART6_DE #1 - Level High 
	out_data &= nbits[2];	//	UART6_/RE #2 - Level low 
	out_data &= nbits[3];	//	UART6_DE #2 - Level low 
	//*/
	/*
	out_data &= nbits[0];	//	UART6_/RE #1 - Level low 
	out_data &= nbits[1];	//	UART6_DE #1 - Level low 
	out_data |= cbits[2];	//	UART6_/RE #2 - Level high 
	out_data |= cbits[3];	//	UART6_DE #2 - Level high 
	*/
	HAL_SRAM_Write_8b(&hsram3, (INT32U*)ADDR_FSMC_IOCS_RS422_485, &out_data, 1);
}

static INT08U  s_rsIsData = 0;
static INT08U  rsComData;
static INT08U  rsComMode = 0;
static INT16U  rsComLen = 0;
static INT16U  rsCRCValue = 0;
static INT16U  rsLen = 0;
static INT08U  rsHeader[FRAME_HEADER_SIZE];
static INT08U  rsComBuffer[FRAME_MAX_DATA_LEN];

static INT32U s_HMI_rx_com_chkTimer = 0;

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
		s_rsIsData = 1;
		memcpy((INT08U*)&HMICom.Header, (INT08U*)rsHeader, FRAME_HEADER_SIZE);
		memcpy((INT08U*)&HMICom.Data[0], (INT08U*)rsComBuffer, rsLen);
	}

	rsComLen = 0;
	rsComMode = 0;
}

void rsComHandler_485(INT08U rsData)
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

	s_HMI_rx_com_chkTimer = m_pgmEnv.timer1ms;
}

/**
   * @brief
   * @param  None
   * @retval None
   */
void HMI_Com_Receive_Proc()
{
	if (m_TxUartQ[rsRS485_422_Port].RS485_422_Tx_Flag)	return;
	
	if (s_rsIsData)
	{
#if DEBUG_HMI_MSG
		printf("[HMI] Receive SRC Type:%02x ID:%02x DST Type:%02x ID:%02x CMD1:%02x CMD2:%02x\r\n",
			HMICom.Header.SrcID.Type, HMICom.Header.SrcID.Index, HMICom.Header.DstID.Type, HMICom.Header.DstID.Index
			, HMICom.Header.Cmd, HMICom.Header.Cmd2);
#endif

		rxDataAnalysis(rsRS485_422_Port, (TMLComPTR)&HMICom);
		s_rsIsData = 0;

		rsComMode = 0;
		rsComLen = 0;
	}
	else
	{
		if (rsComMode)
		{
			if (getCalcTimer1ms(s_HMI_rx_com_chkTimer) >= 20)
			{
				rsComMode = 0;
				rsComLen = 0;
			}
		}
	}
}

/**
   * @brief
   * @param  None
   * @retval None
   */
void HMI_Com_Transmit_Proc()
{
	static INT08U	s_Step;
	static INT32U	s_StepTimer;

	if (m_TxUartQ[rsRS485_422_Port].RS485_Mode)
	{
		switch (s_Step)
		{
		case 0:
			if (m_TxUartQ[rsRS485_422_Port].RS485_422_Tx_Flag)
			{
				RS485_Mode_Control(RS485_TX_MODE);
				//SetTimer100us(&s_StepTimer);
				s_Step = 1;
			}
			break;

		case 1:
			if (1/*getCalcTimer100us(s_StepTimer) > 1*/)	// 100us
			{
#if DEBUG_HMI_MSG
				printf("[HMI] Transmit Data");

				for (INT16U i = 0; i < m_TxUartQ[rsRS485_422_Port].Len; i++)
				{
					if ((i % 20) == 0) printf("\r\n");
					printf(" [%02x]", m_TxUartQ[rsRS485_422_Port].Data[i]);
				}

				printf("\r\n");
#endif
				HAL_UART_Transmit(&huart6, m_TxUartQ[rsRS485_422_Port].Data, m_TxUartQ[rsRS485_422_Port].Len, 1000);

				//asm volatile("NOP");
				RS485_Mode_Control(RS485_RX_MODE);

				m_TxUartQ[rsRS485_422_Port].RS485_422_Tx_Flag = 0;
				s_Step = 0;
			}
			break;

		case 2:
			break;

		case 3:
			break;
		}
	}
	else
	{
		switch (s_Step)
		{
		case 0:
			if (m_TxUartQ[rsRS485_422_Port].RS485_422_Tx_Flag)
			{
#if DEBUG_HMI_MSG
				printf("[HMI] Transmit Data");

				for (INT16U i = 0; i < m_TxUartQ[rsRS485_422_Port].Len; i++)
				{
					if ((i % 20) == 0) printf("\r\n");
					printf(" [%02x]", m_TxUartQ[rsRS485_422_Port].Data[i]);
				}

				printf("\r\n");
#endif
				HAL_UART_Transmit(&huart6, m_TxUartQ[rsRS485_422_Port].Data, m_TxUartQ[rsRS485_422_Port].Len, 1000);

				s_Step = 1;

			}
			break;

		case 1:
			m_TxUartQ[rsRS485_422_Port].RS485_422_Tx_Flag = 0;
			s_Step = 0;
			break;
		}
	}
}

void Set_RS485_422_Mode(INT08U nMode)
{
	if (nMode == 0)
	{
		// RS485
		RS485_Mode_Control(RS485_RX_MODE);
		m_TxUartQ[rsRS485_422_Port].RS485_Mode = 1;
	}
	else
	{	
		// RS422
		RS422_Mode_Enable();
		m_TxUartQ[rsRS485_422_Port].RS485_Mode = 0;
	}
}

/**
   * @brief
   * @param  None
   * @retval None
   */
void HMI_Com_Manager(void)
{
	static INT08U s_Init;

	if (!s_Init)
	{
		__HAL_UART_ENABLE_IT(&huart6, UART_IT_RXNE);

		Set_RS485_422_Mode(1);
		/*
#if RS485_MODE
		RS485_Mode_Control(RS485_RX_MODE);
		m_TxUartQ[rsHMIPort].RS485_Mode = 1;
#else
		RS422_Mode_Enable();
		m_TxUartQ[rsHMIPort].RS485_Mode = 0;
#endif
		*/

		s_Init = 1;
	}
	else
	{
		HMI_Com_Receive_Proc();

		HMI_Com_Transmit_Proc();
	}
}
