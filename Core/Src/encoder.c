/**
  ******************************************************************************
  * @file            : encoder.c
  * @version         : 
  * @author          :
  * @brief           : This file implements the encoder
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

#include "main.h"

#include "type.h"
#include "User_Define.h"
#include "alarm.h"
#include "encoder.h"

extern TIM_HandleTypeDef htim2;

/**
   * @brief
   * @param  None
   * @retval None
   */
int GetEncoderCounter()
{
	//static INT32U s_CheckTimer;
	//static int s_prevCounter = 0;
	int currCounter = 0;
	int timerCounter = 0;

	timerCounter = __HAL_TIM_GET_COUNTER(&htim2);

	//currCounter = 32767 - (((timerCounter - 1) & 0xFFFF) / 2);
	//currCounter = (((timerCounter - 1) & 0xFFFF) / 2) - 32767;

	//currCounter = 15000 - (((timerCounter - 1) & 0xFFFF) / 2);

	//currCounter = (((timerCounter - 1) & 0xFFFF) / 2);

	currCounter = (DEF_ENC_PRESET - timerCounter) >> 1;  
	
	/*
	if (getCalcTimer1ms(s_CheckTimer) > 500)
	{
		timerCounter = __HAL_TIM_GET_COUNTER(&htim2);

		currCounter = 32767 - ((timerCounter - 1) & 0xFFFF) / 2;

		if (currCounter != s_prevCounter)
		{
#if DEBUG_ENCODER_MSG
			printf("[ENCODER] Timer Counter : %d, Current Counter : %d\n\r", timerCounter, currCounter);
#endif

			s_prevCounter = currCounter;
		}

		SetTimer1ms(&s_CheckTimer);
	}
	*/

	return currCounter;
}

 /**
	* @brief
	* @param  None
	* @retval None
	*/
void Encoder_Manager(void)
{
	static INT08U s_Init;

	if (!s_Init)
	{
		s_Init = 1;
		HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
	}
	else
	{
		//GetEncoderCounter();
	}
}
