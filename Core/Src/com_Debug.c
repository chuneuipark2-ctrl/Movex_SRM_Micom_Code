/*
 * com_Debug.c
 *
 *  Created on: 2023. 2. 12.
 *      Author:
 */

#include "com_tml.h"
#include "uart.h"
#include "alarm.h"
#include "upgrade.h"
#include "rtc.h"

#include "Com_Debug.h"

extern UART_HandleTypeDef huart4;

TMLComSTR          DebugCom;

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
		memcpy((INT08U*)&DebugCom.Header, (INT08U*)rsHeader, FRAME_HEADER_SIZE);
		memcpy((INT08U*)&DebugCom.Data[0], (INT08U*)rsComBuffer, rsLen);
	}

	rsComLen = 0;
	rsComMode = 0;
}

void rsComHandler_1(INT08U rsData)
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

/**
  * @brief  TTL232 Communication.
  * @param  None
  * @retval None
  */
void McuComManager(void)
{
	static INT08U s_Init;

	if (!s_Init)
	{
		s_Init = 1;
		__HAL_UART_ENABLE_IT(&huart4, UART_IT_RXNE);
	}
	else
	{
		if (rsIsData)
		{
			rxDataAnalysis(rsMCU_DEBUG_Port, (TMLComPTR)&DebugCom);
			rsIsData = 0;

			rsComMode = 0;
			rsComLen = 0;

			// Test Code. 
			m_pgmEnv.MCU_Test_Mode = 1;
		}
		else
		{
			if (rsComMode)
			{
				//if (getCalcTimer1ms(m_Rx_com_chkTimer) >= 20)
				if (getCalcTimer1ms(m_Rx_com_chkTimer) >= 5)
				{
					rsComMode = 0;
					rsComLen = 0;
				}
			}
		}
	}
}
