/*
 * can.c
 *
 *  Created on: 2022. 6. 15.
 *      Author: ARTWARE
 */

#include "main.h"
#include "type.h"
#include "User_Define.h"
#include "alarm.h"

extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;


CAN_RxHeaderTypeDef   RxHeader;
uint8_t               TxData[8];
uint8_t               RxData[8];

extern McuTestCtrSTR	m_McuTestCtr;
extern McuTestStSTR		m_McuTestSt;

void CAN1_Tx_Message(uint32_t nStdID, uint32_t nLen, uint8_t* pData);

/**
  * @brief  Rx Fifo 0 message pending callback
  * @param  hcan: pointer to a CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @retval None
  */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan)
{
	//INT08U nCan1_CheckData[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	//INT08U nCan2_CheckData[8] = { 8, 7, 6, 5, 4, 3, 2, 1 };

	if (hcan->Instance == CAN1)
	{
		/* Get RX message */
		if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
		{
			/* Reception Error */
			Error_Handler();
		}

#if DEBUG_CAN_MSG
		printf("[CAN1]Rx Message StdID:0x%03lx IDE:%ld DLC:%ld", \
			RxHeader.StdId, RxHeader.IDE, RxHeader.DLC);

		printf(" DATA:");
		for (INT08U i = 0; i < RxHeader.DLC; i++)
		{
			printf(" [%02x]", RxData[i]);
		}
		printf("\r\n");
#endif
		if (m_McuTestSt.CAN1_Enable)
		{
			if ((RxHeader.StdId == 0x001) && (RxHeader.IDE == CAN_ID_STD) && (RxHeader.DLC == 8))
			{
				m_McuTestSt.CAN1_Data.StdID = RxHeader.StdId;
				m_McuTestSt.CAN1_Data.DLC = RxHeader.DLC;
				memcpy((INT08U*)m_McuTestSt.CAN1_Data.Value, (INT08U*)RxData, sizeof(INT08U) * RxHeader.DLC);

				asm volatile("NOP");
				++m_McuTestSt.CAN1_RecvCnt;

				/*
				if (memcmp((INT08U*)RxData, (INT08U*)nCan1_CheckData, 8) == 0)
				{
					++m_McuTestSt.CAN1_RecvCnt;
				}
				*/

				CAN1_Tx_Message(0x003, 8, (INT08U*)RxData);
			}
		}
		
		if (m_McuTestSt.CAN2_Enable)
		{
			if ((RxHeader.StdId == 0x002) && (RxHeader.IDE == CAN_ID_STD) && (RxHeader.DLC == 8))
			{
				m_McuTestSt.CAN2_Data.StdID = RxHeader.StdId;
				m_McuTestSt.CAN2_Data.DLC = RxHeader.DLC;
				memcpy((INT08U*)m_McuTestSt.CAN2_Data.Value, (INT08U*)RxData, sizeof(INT08U) * RxHeader.DLC);

				asm volatile("NOP");
				++m_McuTestSt.CAN2_RecvCnt;

				CAN1_Tx_Message(0x004, 8, (INT08U*)RxData);
			}
		}
	}
}

/**
  * @brief  Tx Fifo0
  * @param
  *
  * @retval None
  */
void CAN1_Tx_Message(uint32_t nStdID, uint32_t nLen, uint8_t* pData)
{
	uint32_t TxMailbox;
	CAN_TxHeaderTypeDef   TxHeader;
	uint8_t               TxData[8];

	TxHeader.StdId = nStdID;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.DLC = nLen;

	memcpy(TxData, pData, sizeof(INT08U) * nLen);

	TxMailbox = HAL_CAN_GetTxMailboxesFreeLevel(&hcan1);
	if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) != HAL_OK)
	{
		/* Transmission request Error */
		Error_Handler();
	}

#if DEBUG_CAN_MSG
	printf("[CAN1]Tx Message StdID:0x%03lx IDE:%ld DLC:%ld", \
		TxHeader.StdId, TxHeader.IDE, TxHeader.DLC);

	printf(" DATA:");
	for (INT08U i = 0; i < TxHeader.DLC; i++)
	{
		printf(" [%02x]", TxData[i]);
	}
	printf("\r\n");
#endif
}

/**
  * @brief  Tx Fifo0
  * @param
  *
  * @retval None
  */
void CAN2_Tx_Message(uint32_t nStdID, uint32_t nLen, uint8_t* pData)
{
	uint32_t TxMailbox;
	CAN_TxHeaderTypeDef   TxHeader;
	uint8_t               TxData[8];

	TxHeader.StdId = nStdID;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.DLC = nLen;

	memcpy(TxData, pData, sizeof(INT08U) * nLen);

	TxMailbox = HAL_CAN_GetTxMailboxesFreeLevel(&hcan2);
	if (HAL_CAN_AddTxMessage(&hcan2, &TxHeader, TxData, &TxMailbox) != HAL_OK)
	{
		/* Transmission request Error */
		Error_Handler();
	}

#if DEBUG_CAN_MSG
	printf("[CAN2]Tx Message StdID:0x%03lx IDE:%ld DLC:%ld", \
		TxHeader.StdId, TxHeader.IDE, TxHeader.DLC);

	printf(" DATA:");
	for (INT08U i = 0; i < TxHeader.DLC; i++)
	{
		printf(" [%02x]", TxData[i]);
	}
	printf("\r\n");
#endif
}

/**
  * @brief  Can Main Function. Test Code.
  * @param  None
  * @retval None
  */
void CAN_Manager(void)
{
	static INT08U s_Step;
	static INT32U s_StepTimer;

	uint8_t csend[] = { 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08 };

	switch (s_Step)
	{
	case 0:
		SetTimer1ms(&s_StepTimer);
		s_Step = 1;
		break;

	case 1:
		if (getCalcTimer1ms(s_StepTimer) > 1000)
		{
			SetTimer1ms(&s_StepTimer);
			s_Step = 2;
		}
		break;

	case 2:
		if (getCalcTimer1ms(s_StepTimer) > 500)
		{
			CAN1_Tx_Message(0x010, 4, csend);
			SetTimer1ms(&s_StepTimer);
		}
		break;
	}
}
