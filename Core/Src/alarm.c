/*
 * alarm.c
 *
 *  Created on: 2022. 6. 15.
 *      Author: ARTWARE
 */

#include "main.h"

//#include "type.h"
#include "User_Define.h"
#include "rtc.h"
#include "dev_SRM.h"
#include "alarm.h"
#include "upgrade.h"

extern SRAM_HandleTypeDef hsram3;

void Set_TestStatus(INT32S nIndex, INT32S nData)
{
	if ((nIndex >= DEBUG_STR_1) && (nIndex <= DEBUG_STR_32))
	{
		m_TestStatus.St[nIndex] = nData;
	}
	else if ((nIndex >= DEBUG_STR_33) && (nIndex <= DEBUG_STR_64))
	{
		m_TestStatus.St2[nIndex - DEBUG_STR_33] = nData;
	}
}

void Clear_TestStatus(INT32S nIndex)
{
	if ((nIndex >= DEBUG_STR_1) && (nIndex <= DEBUG_STR_32))
	{
		m_TestStatus.St[nIndex] = 0;
	}
	else if ((nIndex >= DEBUG_STR_33) && (nIndex <= DEBUG_STR_64))
	{
		m_TestStatus.St2[nIndex - DEBUG_STR_33] = 0;
	}
}

void All_Clear_TestStatus()
{
	memset((INT32U*)m_TestStatus.St, 0, sizeof(INT32U) * 32);
	memset((INT32U*)m_TestStatus.St2, 0, sizeof(INT32U) * 32);
}

void Set_TestControl(INT32S nIndex, INT32S nData)
{
	if ((nIndex >= DEBUG_CTR_1) && (nIndex <= DEBUG_CTR_16))
	{
		m_TestStatus.Ctrl[nIndex] = nData;
	}
}

void Clear_TestControl(INT32S nIndex)
{
	if ((nIndex >= DEBUG_CTR_1) && (nIndex <= DEBUG_CTR_16))
	{
		m_TestStatus.Ctrl[nIndex] = 0;
	}
}

void All_Clear_TestControl()
{
	memset((INT32U*)m_TestStatus.Ctrl, 0, sizeof(INT32S) * 16);
}

void SetTimer1ms(INT32U* nTimer)
{
	*nTimer = m_pgmEnv.timer1ms;
}

void SetTimer100us(INT32U* nTimer)
{
	*nTimer = m_pgmEnv.timer100us;
}

INT32U getCalcTimer100us(INT32U startTime)
{
	if (m_pgmEnv.timer100us >= startTime)
		return(m_pgmEnv.timer100us - startTime);
	else
		return((0xFFFFFFFF - startTime) + m_pgmEnv.timer100us);
}

INT32U getCalcTimer1ms(INT32U startTime)
{
	if (m_pgmEnv.timer1ms >= startTime)
		return(m_pgmEnv.timer1ms - startTime);
	else
		return((0xFFFFFFFF - startTime) + m_pgmEnv.timer1ms);
}

void wait100us(INT32U time)
{
	INT32U chkTimer = 0;

	chkTimer = m_pgmEnv.timer100us;
	while (getCalcTimer100us(chkTimer) < time)
	{
#if ENABLE_WATCHDOG
		WatchDog();
#endif
	}
}

void wait1ms(INT32U time)
{
	INT32U chkTimer = 0;

	chkTimer = m_pgmEnv.timer1ms;
	while (getCalcTimer1ms(chkTimer) < time)
	{
#if ENABLE_WATCHDOG
		WatchDog();
#endif
	}
}

void wait1ms_no_wd(INT32U time)
{
	INT32U chkTimer = 0;

	chkTimer = m_pgmEnv.timer1ms;
	while (getCalcTimer1ms(chkTimer) < time);
}

void uSleep_ms(INT32U time)
{
	INT32U i = 0, j = 0;

	for (i = 0; i < time; i++)
	{
		for (j = 0; j < 100; j++)
		{
			asm volatile("NOP");
		}

#if ENABLE_WATCHDOG
		WatchDog();
#endif
	}
}

void MCU_Output_Control(INT08U nPin, INT08U nFlag)
{
	INT08U nOutdata = 0x00;
	INT08U i = 0;

	if (nPin > 8)	return;

	(nFlag) ? (m_pgmEnv.DOSt |= cbits[nPin]) : (m_pgmEnv.DOSt &= nbits[nPin]);

	for (i = 0; i < 8; i++)
	{
		if (m_pgmEnv.DOSt & cbits[i])  
			nOutdata &= nbits[i];
		else                        
			nOutdata |= cbits[i];
	}

	HAL_SRAM_Write_8b(&hsram3, (INT32U*)ADDR_FSMC_IOCS_DO, &nOutdata, 1);
	HAL_SRAM_Write_8b(&hsram3, (INT32U*)ADDR_FSMC_IOCS_DO, &nOutdata, 1);

	HAL_GPIO_WritePin(OUT_ENB_GPIO_Port, OUT_ENB_Pin, GPIO_PIN_RESET);
}

////////////////////////////////////////////////////////////////
//#define UPDATE_GRAPH_TIME	1	// 10ms
#define UPDATE_GRAPH_TIME	2	// 20ms
//#define UPDATE_GRAPH_TIME	5	// 40ms

void Graph_Update(void)
{
	static INT08U s_Update_Cnt;

	//if (!m_pgmEnv.Graph_Enable)		return;

	if (s_Update_Cnt >= UPDATE_GRAPH_TIME)
	{
		s_Update_Cnt = 0;

		if (m_GraphLog.Index < MAX_GRAPH_DATA_COUNT)
		{
			m_GraphLog.GraphData[0][m_GraphLog.Index] = m_pgmEnv.GraphData[0];
			m_GraphLog.GraphData[1][m_GraphLog.Index] = m_pgmEnv.GraphData[1];
			m_GraphLog.GraphData[2][m_GraphLog.Index] = m_pgmEnv.GraphData[2];
			m_GraphLog.GraphData[3][m_GraphLog.Index] = m_pgmEnv.GraphData[3];
			m_GraphLog.GraphData[4][m_GraphLog.Index] = m_pgmEnv.GraphData[4];
			m_GraphLog.GraphData[5][m_GraphLog.Index] = m_pgmEnv.GraphData[5];
			m_GraphLog.GraphData[6][m_GraphLog.Index] = m_pgmEnv.GraphData[6];
			m_GraphLog.GraphData[7][m_GraphLog.Index] = m_pgmEnv.GraphData[7];
			m_GraphLog.GraphData[8][m_GraphLog.Index] = m_pgmEnv.GraphData[8];
			m_GraphLog.GraphData[9][m_GraphLog.Index] = m_pgmEnv.GraphData[9];
			m_GraphLog.GraphData[10][m_GraphLog.Index] = m_pgmEnv.GraphData[10];
			m_GraphLog.GraphData[11][m_GraphLog.Index] = m_pgmEnv.GraphData[11];
			m_GraphLog.GraphData[12][m_GraphLog.Index] = m_pgmEnv.GraphData[12];
			m_GraphLog.GraphData[13][m_GraphLog.Index] = m_pgmEnv.GraphData[13];
			m_GraphLog.GraphData[14][m_GraphLog.Index] = m_pgmEnv.GraphData[14];
			m_GraphLog.GraphData[15][m_GraphLog.Index] = m_pgmEnv.GraphData[15];

			if (++m_GraphLog.Index >= MAX_GRAPH_DATA_COUNT)  m_GraphLog.Index = MAX_GRAPH_DATA_COUNT;
		}
	}

	++s_Update_Cnt;
}

void Graph_Update_Mode(void)
{
	// Interrpt interval : 10ms
	static INT32U s_Update_Cnt;
	static INT32U s_Update_Timer;
	static INT32U s_Update_Time;

	INT08U nRecodingFlag = 0;

	if ((m_BKSram.Graph_Type == GRAPH_START_RECORDING_WHEN_DRIVING_BEGINS) \
		|| (m_BKSram.Graph_Type == GRAPH_START_RECORDING_IMMEDIATELY))
	{
		// 0: 雅��놂옙占� 占쏙옙占쏙옙占쏙옙 疫꿸�占� 占쏙옙占쏙옙
		nRecodingFlag = 1;
	}
	else if (m_BKSram.Graph_Type == GRAPH_START_RECORDING_FROM_THE_SET_DRIVING_LOCATION)
	{
		nRecodingFlag = 1;
		
		/*
		if (m_St.Driving_INV.Current_Pos >= m_BKSram.Graph_Start_mm)
		{
			nRecodingFlag = 1;
		}
		else
		{
			if (m_GraphLog.Index)
			{
				clearGraph();
			}
		}
		*/
	}

	if (nRecodingFlag)
	{
		if (s_Update_Cnt >= m_BKSram.Graph_Interval)
		{
			s_Update_Cnt = 0;
			s_Update_Time = getCalcTimer1ms(s_Update_Timer);

			//m_TestStatus.Ctrl[DEBUG_CTR_16] = s_Update_Time;

			s_Update_Timer = m_pgmEnv.timer1ms;

			if (m_GraphLog.Index < MAX_GRAPH_DATA_COUNT)
			{
				m_GraphLog.GraphData[GRAPH_1][m_GraphLog.Index] = m_pgmEnv.GraphData[GRAPH_1];
				m_GraphLog.GraphData[GRAPH_2][m_GraphLog.Index] = m_pgmEnv.GraphData[GRAPH_2];
				m_GraphLog.GraphData[GRAPH_3][m_GraphLog.Index] = m_pgmEnv.GraphData[GRAPH_3];
				m_GraphLog.GraphData[GRAPH_4][m_GraphLog.Index] = m_pgmEnv.GraphData[GRAPH_4];
				m_GraphLog.GraphData[GRAPH_5][m_GraphLog.Index] = m_pgmEnv.GraphData[GRAPH_5];
				m_GraphLog.GraphData[GRAPH_6][m_GraphLog.Index] = m_pgmEnv.GraphData[GRAPH_6];
				m_GraphLog.GraphData[GRAPH_7][m_GraphLog.Index] = m_pgmEnv.GraphData[GRAPH_7];
				m_GraphLog.GraphData[GRAPH_8][m_GraphLog.Index] = m_pgmEnv.GraphData[GRAPH_8];
				m_GraphLog.GraphData[GRAPH_9][m_GraphLog.Index] = m_pgmEnv.GraphData[GRAPH_9];
				m_GraphLog.GraphData[GRAPH_10][m_GraphLog.Index] = m_pgmEnv.GraphData[GRAPH_10];
				m_GraphLog.GraphData[GRAPH_11][m_GraphLog.Index] = m_pgmEnv.GraphData[GRAPH_11];
				m_GraphLog.GraphData[GRAPH_12][m_GraphLog.Index] = m_pgmEnv.GraphData[GRAPH_12];

				if (++m_GraphLog.Index >= MAX_GRAPH_DATA_COUNT)  m_GraphLog.Index = MAX_GRAPH_DATA_COUNT;
			}
		}

		++s_Update_Cnt;
	}

}

void clearGraph(void)
{
	memset((INT08U *)&m_GraphLog, 0x00, sizeof(GraphLogSTR));
	m_GraphLog.StartTimer = m_pgmEnv.timer1ms;
}

/**
  * @brief Initialize Graph Setting
  * @param None
  * @retval None
  */
void Graph_Setup_Init()
{
	INT08U nSaveFlag = 0;

	if ((m_BKSram.Graph_Type != GRAPH_START_RECORDING_WHEN_DRIVING_BEGINS) \
		&& (m_BKSram.Graph_Type != GRAPH_START_RECORDING_FROM_THE_SET_DRIVING_LOCATION) \
		&& (m_BKSram.Graph_Type != GRAPH_START_RECORDING_IMMEDIATELY))
	{
		m_BKSram.Graph_Type = GRAPH_START_RECORDING_WHEN_DRIVING_BEGINS;
		m_BKSram.Graph_Start_mm = 0;
		nSaveFlag = 1;
	}

	if ((m_BKSram.Graph_Interval < 1) || (m_BKSram.Graph_Interval > 50))
	{
		m_BKSram.Graph_Interval = 1;
		m_BKSram.Graph_Start_mm = 0;
		nSaveFlag = 1;
	}

	if (nSaveFlag)
	{
		saveBKSramBlock((INT08U*)&m_BKSram.Graph_Type, sizeof(INT08U) * 6);
	}

	//Generate_Graph_TestData();

	//clearGraph();
}

/**
  * @brief Graph Setting
  * @param None
  * @retval None
  */
void Graph_Setup(INT08U nGraphType, INT08U nInterval, INT32U nStart_Postion)
{
	INT08U nSaveFlag = 0;

	if ((nGraphType == GRAPH_START_RECORDING_WHEN_DRIVING_BEGINS) \
		|| (nGraphType == GRAPH_START_RECORDING_FROM_THE_SET_DRIVING_LOCATION) \
		|| (nGraphType == GRAPH_START_RECORDING_IMMEDIATELY))
	{
		m_BKSram.Graph_Type = nGraphType;
		nSaveFlag = 1;
	}

	if ((nInterval >= 1) && (nInterval <= 50))
	{
		m_BKSram.Graph_Interval = nInterval;
		nSaveFlag = 1;
	}

	if (m_BKSram.Graph_Type == GRAPH_START_RECORDING_FROM_THE_SET_DRIVING_LOCATION)
	{
		m_BKSram.Graph_Start_mm = nStart_Postion;
		nSaveFlag = 1;
	}

	if (nSaveFlag)
	{
		saveBKSramBlock((INT08U*)&m_BKSram.Graph_Type, sizeof(INT08U) * 6);

		if (nGraphType == GRAPH_START_RECORDING_IMMEDIATELY)
		{
			// 筌�占쏙옙占� 占쏙옙占싸쏙옙占쏙옙占쏙옙����, 域밸�占쏙옙占쏙옙 占쎄�占쎈��占쏙옙 占쎈����占쏙옙
			clearGraph();
		}
	}
}


////////////////////////////////////////////////////////////////

void add_alarm_log(INT08U MainCode, INT08U SubCode, INT08U Value)
{
	// BackUpSRAM 
	if (m_BKSram.AlarmLog.Inx >= MAX_ALARM_LOG_COUNT)
	{
		m_BKSram.AlarmLog.Repeat = 0;
		m_BKSram.AlarmLog.Inx = 0;
	}

	m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].SysTime = m_DevStatus.SysTime;
	m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].MainCode = MainCode;
	m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].SubCode = SubCode;
	m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].Value = Value;
#if DEF_ALARM_LOG_TYPE == 1
// 	m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].Pos.Station = m_St.TargetFork1.Station;
// 	m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].Pos.Row_ID = m_St.TargetFork1.Row_ID;
// 	m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].Pos.Bay_ID = m_St.TargetFork1.Bay_ID;
	//m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].Pos.Level_ID = m_St.TargetFork1.Level_ID;
	m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].Pos.Station = m_St.PosFork1.St_No;
 	m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].Pos.Row_ID = m_St.PosFork1.Row_ID;
 	m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].Pos.Bay_ID = m_St.PosFork1.Bay_No;
	m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].Pos.Level_ID = m_St.PosFork1.Level_No;
	m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].Fork[0].OrderCode = m_St.ForkWork[0].OrderCode_Fork;
	m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].Fork[0].OrderProcess = m_St.ForkWork[0].OrderProcess_Fork;
	m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].Fork[1].OrderCode = m_St.ForkWork[1].OrderCode_Fork;
	m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].Fork[1].OrderProcess = m_St.ForkWork[1].OrderProcess_Fork;
#elif DEF_ALARM_LOG_TYPE == 2
	m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].Pos.Station = m_St.PosFork1.St_No;
	m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].Pos.Row_ID = m_St.PosFork1.Row_ID;
	m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].Pos.Bay_ID = m_St.PosFork1.Bay_No;
	m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].Pos.Level_ID = m_St.PosFork1.Level_No;
	m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].Fork.OrderCode = m_St.ForkWork[0].OrderCode_Fork;
	m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].Fork.OrderProcess = m_St.ForkWork[0].OrderProcess_Fork;
	m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].WorkNo = m_St.ForkWork[0].WorkNum_Fork;

	memset((INT08U*)&m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr, 0, sizeof(UniLogSTR_InvErr));

	if (MainCode == ERROR1_IN_POSITION)
	{
		if ((SubCode == 1) || (SubCode == 2) || (SubCode == 3) || (SubCode == 4))
		{
			m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr.Position = m_St.Inv_St[INV_TRAVEL].Current_Pos;
			m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr.Speed = m_St.PosFork1.Position1.Data;
		}
		else if ((SubCode == 5) || (SubCode == 6) || (SubCode == 7) || (SubCode == 8))
		{
			m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr.Position = m_St.Inv_St[INV_HOIST].Current_Pos;
			m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr.Speed = m_St.PosFork1.Position1.Data;
		}
		else if ((SubCode == 9) || (SubCode == 10) || (SubCode == 11) || (SubCode == 12))
		{
			m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr.Position = m_St.Inv_St[INV_FORK_1].Current_Pos;
			m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr.Speed = m_St.PosFork1.Position2.Data;
		}
	}

	if (Get_Inverter_Fault_State(INV_TRAVEL))
	{
		m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr.Position = Get_Inverter_CurPosition(INV_TRAVEL);
		m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr.Speed = Get_Inverter_Actual_Speed(INV_TRAVEL);
		m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr.MainCode = Get_Inverter_MainError(INV_TRAVEL);
		m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr.SubCode = Get_Inverter_SubError(INV_TRAVEL);
		m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr.FBCode = Get_Inverter_FbError(INV_TRAVEL);
	}
	else if (Get_Inverter_Fault_State(INV_HOIST))
	{
		m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr.Position = Get_Inverter_CurPosition(INV_HOIST);
		m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr.Speed = Get_Inverter_Actual_Speed(INV_HOIST);
		m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr.MainCode = Get_Inverter_MainError(INV_HOIST);
		m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr.SubCode = Get_Inverter_SubError(INV_HOIST);
		m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr.FBCode = Get_Inverter_FbError(INV_HOIST);
	}
	else if (Get_Inverter_Fault_State(INV_FORK_1))
	{
		m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr.Position = Get_Inverter_CurPosition(INV_FORK_1);
		m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr.Speed = Get_Inverter_Actual_Speed(INV_FORK_1);
		m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr.MainCode = Get_Inverter_MainError(INV_FORK_1);
		m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr.SubCode = Get_Inverter_SubError(INV_FORK_1);
		m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].InvErr.FBCode = Get_Inverter_FbError(INV_FORK_1);
	}


	for (INT08U i = 0; i < 3; i++)
	{
		if (Get_Inverter_Fault_State(i))
		{
			m_St.InvErrorCode.Inverter[i].MainError = Get_Inverter_MainError(i);
			m_St.InvErrorCode.Inverter[i].SubError = Get_Inverter_SubError(i);
		}
		else
		{
			m_St.InvErrorCode.Inverter[i].MainError = 0;
			m_St.InvErrorCode.Inverter[i].SubError = 0;
		}
	}
#endif

	memcpy((INT08U*)m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].Digital_Input, (INT08U*)m_St.Digital_Input, sizeof(INT08U) * 20);
	memcpy((INT08U*)m_BKSram.AlarmLog.Log[m_BKSram.AlarmLog.Inx].Digital_Output, (INT08U*)m_St.Digital_Output, sizeof(INT08U) * 9);

	if (++m_BKSram.AlarmLog.Inx >= MAX_ALARM_LOG_COUNT)
	{
		m_BKSram.AlarmLog.Repeat = 1;
		m_BKSram.AlarmLog.Inx = 0;
	}

	saveBKSramBlock((INT08U*)&m_BKSram.AlarmLog, sizeof(AlarmLogSTR));
	/*
#if DEF_ALARM_LOG_TYPE == 1
	saveBKSramBlock((INT08U*)&m_BKSram.AlarmLog, sizeof(AlarmLogSTR));
#elif DEF_ALARM_LOG_TYPE == 2
	saveBKSramBlock((INT08U*)&m_BKSram.AlarmLog, sizeof(AlarmLogSTR));
#endif
	*/
}


////////////////////////////////////////////////////////////////

void save_error_code(INT08U main_error_code, INT08U sub_error_code, INT16U error_reason)
{
	//SRM_Warning_reset();

	if (!m_St.SRM_Status1.Bit.Fault)
	{
		if (m_St.SRM_Mode.Bit.Auto)
		{
			Change_DeviceMode(DEVICE_MANUAL_MODE, 1);
		}

		m_St.SRM_Status1.Bit.Fault = 1;
		m_St.SRM_Status1.Bit.Warning = 0;

		m_St.MainErrCode = main_error_code;
		m_St.SubErrCode = sub_error_code;
		m_St.ErrReason = error_reason;

// 		Set_TestStatus(DEBUG_STR_62, m_St.Inv_St[INV_TRAV].Current_Pos);
// 		Set_TestStatus(DEBUG_STR_63, m_St.Inv_St[INV_LIFT].Current_Pos);

		add_alarm_log(m_St.MainErrCode, m_St.SubErrCode, error_reason);
	}
}

void save_error_code_Invertor(INT08U main_error_code, INT08U sub_error_code, INT16U error_reason)
{
	if (m_St.SRM_Mode.Bit.Auto)
	{
		Change_DeviceMode(DEVICE_MANUAL_MODE, 1);
	}

	m_St.SRM_Status1.Bit.Fault = 1;

	m_St.MainErrCode = main_error_code;
	m_St.SubErrCode = sub_error_code;
	m_St.ErrReason = error_reason;

	add_alarm_log(m_St.MainErrCode, m_St.SubErrCode, error_reason);
}

void Event_Warning_Code(INT08U main_error_code, INT08U sub_error_code, INT16U error_reason)
{
	if (m_St.SRM_Status1.Bit.Fault == 0)
	{
		m_St.SRM_Status1.Bit.Warning = 1;

		m_St.MainErrCode = main_error_code;
		m_St.SubErrCode = sub_error_code;
		m_St.ErrReason = error_reason;

		m_pgmEnv.Clear_Warning_Timer = m_pgmEnv.timer1ms;
	}
}

////////////////////////////////////////////////////////////////

void controlCpuReset(void)
{
#if DEBUG_MSG
	printf("[DEBUG_APP] Reset CPU....\r\n");
#endif
	wait1ms(100);
	NVIC_SystemReset();
}

///////////////////////////////////////////////////////////////////////////////

void Set_MCU_Input_FilterTime(void)
{
	INT16U i = 0, j = 0;
	INT08U nType = 0;
	INT08U nPin = 0;
	INT08U nFilterTime = 0;

	for (i = 0; i < MAX_DI_CNT; i++)
	{
		if (i <= IN_DSTRR2)
		{
			nType = m_DIO_SetInfo.Set.DI_Set[i].Type;
			nPin = m_DIO_SetInfo.Set.DI_Set[i].Pin;

			nFilterTime = m_DIO_SetInfo.Set.DI_Set[i].FilterTime;
		}
		else
		{
			nType = m_DIO_SetInfo.Set.DI_Set2[i - IN_LSTH].Type;
			nPin = m_DIO_SetInfo.Set.DI_Set2[i - IN_LSTH].Pin;

			nFilterTime = m_DIO_SetInfo.Set.DI_Set2[i - IN_LSTH].FilterTime;
		}

		if (nType == 0)
		{
			for (j = 0; j < 8; j++)
			{
				if (nPin == j)
				{
					m_pgmEnv.InputFilterTime[j] = nFilterTime;
				}
			}
		}
	}
}

void get_main_controller_di(void)
{
	static INT08U s_Init = 0;

	INT08U i;

	INT08U nTmpBuf = 0;
	INT08U nCur_DI[8] = { 0, };
	static INT08U s_Pre_DI[8] = { 0, };

	static INT32U s_InputTimer[8] = { 0, };
	static INT08U s_InputFilterTimerFlag[8] = { 0, };

	HAL_SRAM_Read_8b(&hsram3, (INT32U*)ADDR_FSMC_IOCS_DI, &nTmpBuf, 1);
	//nCur_DI = ~nTmpBuf;
	for (i = 0; i < 8; i++)
	{
		((~nTmpBuf) & cbits[i]) ? (nCur_DI[i] |= cbits[i]) : (nCur_DI[i] &= nbits[i]);
	}
	
	if (!s_Init)
	{
		s_Init = 1;

		Set_MCU_Input_FilterTime();

		memcpy(s_Pre_DI, nCur_DI, sizeof(INT08U) * 8);

		for (i = 0; i < 8; i++)
		{
			if (s_Pre_DI[i] & cbits[i])
			{
				m_pgmEnv.DISt |= cbits[i];
			}
			else
			{
				m_pgmEnv.DISt &= nbits[i];
			}
		}
	}
	else
	{
		for (i = 0; i < 8; i++)
		{
			if (s_Pre_DI[i] != nCur_DI[i])
			{
				s_Pre_DI[i] = nCur_DI[i];

				s_InputFilterTimerFlag[i] = TRUE;
				SetTimer1ms(&s_InputTimer[i]);
			}
			else
			{
				if (s_InputFilterTimerFlag[i])
				{
					if (getCalcTimer1ms(s_InputTimer[i]) >= m_pgmEnv.InputFilterTime[i])
					{
						s_InputFilterTimerFlag[i] = FALSE;

						if (s_Pre_DI[i] & cbits[i])
						{
							m_pgmEnv.DISt |= cbits[i];
						}
						else
						{
							m_pgmEnv.DISt &= nbits[i];
						}
					}
				}
			}
		}
	}      
}

void get_main_controller_Mode_SW(void)
{
	INT32U nDef_FilterTime = 10;
	static INT32U s_InputFilterTimer;
	static INT08U s_InputFilterTimerFlag;

	static INT08U s_Pre_Mode = 0;

	INT08U nTmpBuf = 0;
	INT08U sw = 0;

	HAL_SRAM_Read_8b(&hsram3, (INT32U*)ADDR_FSMC_IOCS_MODE, &nTmpBuf, 1);
	sw = (~nTmpBuf) & 0x0F;

	if (s_Pre_Mode != sw)
	{
		s_Pre_Mode = sw;
		SetTimer1ms(&s_InputFilterTimer);
		s_InputFilterTimerFlag = TRUE;
	}
	else
	{
		if (s_InputFilterTimerFlag)
		{
			if (getCalcTimer1ms(s_InputFilterTimer) > nDef_FilterTime)
			{
				s_InputFilterTimerFlag = FALSE;
				m_DevStatus.Mode_SW = s_Pre_Mode;

				//m_TestStatus.St[DEBUG_STR_11] = m_DevStatus.Mode_SW;
			}
		}
	}
	
	/*
	CALC_BITS(m_DevSt.ModeSWSt, sw & cbits[0], 0);
	CALC_BITS(m_DevSt.ModeSWSt, sw & cbits[1], 1);
	CALC_BITS(m_DevSt.ModeSWSt, sw & cbits[2], 2);
	CALC_BITS(m_DevSt.ModeSWSt, sw & cbits[3], 3);
	CALC_BITS(m_DevSt.ModeSWSt, sw & cbits[4], 3);
	CALC_BITS(m_DevSt.ModeSWSt, sw & cbits[5], 2);
	CALC_BITS(m_DevSt.ModeSWSt, sw & cbits[6], 1);
	CALC_BITS(m_DevSt.ModeSWSt, sw & cbits[7], 0);
	*/
}

void get_main_controller_ID_SW(void)
{
	INT32U nDef_FilterTime = 10;
	static INT32U s_InputFilterTimer;
	static INT08U s_InputFilterTimerFlag;

	static INT08U s_Pre_ID = 0;

	INT08U nTmpBuf = 0;
	INT08U sw = 0;

	HAL_SRAM_Read_8b(&hsram3, (INT32U*)ADDR_FSMC_IOCS_ID_SW, &nTmpBuf, 1);
	nTmpBuf = (~nTmpBuf);

	CALC_BITS(sw, nTmpBuf & cbits[0], 4);
	CALC_BITS(sw, nTmpBuf & cbits[1], 5);
	CALC_BITS(sw, nTmpBuf & cbits[2], 6);
	CALC_BITS(sw, nTmpBuf & cbits[3], 7);
	CALC_BITS(sw, nTmpBuf & cbits[4], 0);
	CALC_BITS(sw, nTmpBuf & cbits[5], 1);
	CALC_BITS(sw, nTmpBuf & cbits[6], 2);
	CALC_BITS(sw, nTmpBuf & cbits[7], 3);

	if (s_Pre_ID != sw)
	{
		s_Pre_ID = sw;
		SetTimer1ms(&s_InputFilterTimer);
		s_InputFilterTimerFlag = TRUE;
	}
	else
	{
		if (s_InputFilterTimerFlag)
		{
			if (getCalcTimer1ms(s_InputFilterTimer) > nDef_FilterTime)
			{
				s_InputFilterTimerFlag = FALSE;

				m_DevStatus.ID_SW = s_Pre_ID;
			}
		}
	}
}

void DIManager(void)
{
	get_main_controller_di();
	get_main_controller_Mode_SW();
	get_main_controller_ID_SW();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AIManager(void)
{
	static INT32U chkTimer = 0;

	if (getCalcTimer1ms(chkTimer) >= 10)
	{
		chkTimer = m_pgmEnv.timer1ms;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                 0x01
//                ------
//               |      |
//          0x20 |      | 0x02
//               | 0x40 |
//                ------
//               |      |
//          0x10 |      | 0x04
//               |      |
//                ------
//                0x08
//
//                        0     1     2     3     4     5     6     7     8     9     10    11    12    13    14    15   16   17    18    19    20    21
//                        0     1     2     3     4     5     6     7     8     9     A     b     C     d     E     F         -     H     [     ]     _
INT08U FND_font[22] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x00, 0x40, 0x76, 0x39, 0x0F, 0x08 };

void controlFND(INT08U value, INT08U point)
{
	INT08U out_data;
	INT08U nWriteBuf = 0;;

	if (value < 22)  out_data = FND_font[value];
	else              out_data = 0x00;

	if (point)  out_data |= 0x80;

	//*((INT08U *)ADDR_FSMC_IOCS_FND) = ~out_data;

	nWriteBuf = ~out_data;
	HAL_SRAM_Write_8b(&hsram3, (INT32U*)ADDR_FSMC_IOCS_FND, &nWriteBuf, 1);
}

static INT08U DispCnt = 0;
static INT08U DispInx = 0;
static INT08U DispData[30];

void FNDManager(void)
{
	static INT32U runTimer = 0;
	INT08U p = 0;
	INT08U id;
	INT08U merr, serr;

	if (m_pgmEnv.MCU_Test_Mode)
	{
		controlFND(m_McuTestSt.FND_Display, 0);
	}
	else
	{
		if (getCalcTimer1ms(runTimer) >= 400)
		{
			runTimer = m_pgmEnv.timer1ms;

			if (DispInx == 0)
			{
				//if (1/*m_St.Error*/)
				if (m_St.SRM_Status1.Bit.Fault)
				{
					merr = m_St.MainErrCode;
					serr = m_St.SubErrCode;

					DispData[p++] = 16; // ' '
					DispData[p++] = 14; // 'E'
					DispData[p++] = 16; // ' '
					DispData[p++] = 17; // '-'
					DispData[p++] = 16; // ' '

					if (merr >= 100)
					{
						DispData[p++] = merr / 100;   merr %= 100;
						DispData[p++] = 16; // ' '
						DispData[p++] = merr / 10;
						DispData[p++] = 16; // ' '
						DispData[p++] = merr % 10;
						DispData[p++] = 16; // ' '
					}
					else if (merr >= 10)
					{
						DispData[p++] = merr / 10;
						DispData[p++] = 16; // ' '
						DispData[p++] = merr % 10;
						DispData[p++] = 16; // ' '
					}
					else
					{
						DispData[p++] = merr;
						DispData[p++] = 16; // ' '
					}

					DispData[p++] = 17; // '-'
					DispData[p++] = 16; // ' '

					if (serr >= 100)
					{
						DispData[p++] = serr / 100;   serr %= 100;
						DispData[p++] = 16; // ' '
						DispData[p++] = serr / 10;
						DispData[p++] = 16; // ' '
						DispData[p++] = serr % 10;
						DispData[p++] = 16; // ' '
					}
					else if (serr >= 10)
					{
						DispData[p++] = serr / 10;
						DispData[p++] = 16; // ' '
						DispData[p++] = serr % 10;
						DispData[p++] = 16; // ' '
					}
					else
					{
						DispData[p++] = serr;
						DispData[p++] = 16; // ' '
					}

					DispData[p++] = 16; // ' '
					DispCnt = p;
				}
				else
				{
					id = m_pgmEnv.DeviceID;
					if (id > 32)  id = 99;
					DispData[p++] = 16; // ' '
					DispData[p++] = id / 10;
					DispData[p++] = 16; // ' '
					DispData[p++] = id % 10;
					DispData[p++] = 16; // ' '
					DispData[p++] = 16; // ' '
					DispCnt = p;
				}

				controlFND(DispData[DispInx++], 0);
			}
			else
			{
				if (DispInx >= DispCnt)
				{
					DispInx = 0;
					controlFND(16, 0);
				}
				else
				{
					controlFND(DispData[DispInx++], 0);
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void getSystemDateTime(void)
{
	static INT32U runTimer = 0;

	//if (getCalcTimer1ms(runTimer) >= 500)
	if (getCalcTimer1ms(runTimer) >= 100)
	{
		runTimer = m_pgmEnv.timer1ms;
		//m_DevStatus.SysTime = getTimeDate();
		m_DevStatus.SysTime = getTimeDate_Rev2();

		m_St.SysTime = m_DevStatus.SysTime;
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void runningLED(void)
{
	static INT32U s_RunTimer = 0;

	if (getCalcTimer1ms(s_RunTimer) >= 300)
	{
		HAL_GPIO_TogglePin(CPU_RUN_LED_GPIO_Port, CPU_RUN_LED_Pin);
		s_RunTimer = m_pgmEnv.timer1ms;
	}
}

void LED_Bar_Control(INT08U nColor)
{
	if (m_ExtSEnv.Machine.mType.Lamp_Type == 0)
	{
		// LED Bar
		switch (nColor)
		{
		case LAMP_OFF:
			DO_Control(OUT_LED_RD, 0);	// R
			DO_Control(OUT_LED_GR, 0);	// G
			DO_Control(OUT_LED_BU, 0);	// B
			break;
		case LAMP_RED:
			DO_Control(OUT_LED_RD, 1);		// R
			DO_Control(OUT_LED_GR, 0);		// G
			DO_Control(OUT_LED_BU, 0);		// B
			break;
		case LAMP_YELLOW:
			DO_Control(OUT_LED_RD, 1);	// R
			DO_Control(OUT_LED_GR, 1);	// G
			DO_Control(OUT_LED_BU, 0);	// B
			break;
		case LAMP_GREEN:
			DO_Control(OUT_LED_RD, 0);
			DO_Control(OUT_LED_GR, 1);
			DO_Control(OUT_LED_BU, 0);
			break;
		case LAMP_BLUE:
			DO_Control(OUT_LED_RD, 0);
			DO_Control(OUT_LED_GR, 0);
			DO_Control(OUT_LED_BU, 1);
			break;
		case LAMP_MAGENTA:
			DO_Control(OUT_LED_RD, 1);
			DO_Control(OUT_LED_GR, 0);
			DO_Control(OUT_LED_BU, 1);
			break;
		case LAMP_CYAN:
			DO_Control(OUT_LED_RD, 0);
			DO_Control(OUT_LED_GR, 1);
			DO_Control(OUT_LED_BU, 1);
			break;
		case LAMP_WHITE:
			DO_Control(OUT_LED_RD, 1);
			DO_Control(OUT_LED_GR, 1);
			DO_Control(OUT_LED_BU, 1);
			break;
		default:
			break;
		}
	}
	else
	{

	}
}

void LED_Bar_Control_Proc()
{
	static INT32U s_chkTimer = 0;
	static INT08U s_LampToggleMode = 0;

	if (getCalcTimer1ms(s_chkTimer) >= 300)
	{
		s_chkTimer = m_pgmEnv.timer1ms;

		if (s_LampToggleMode == 0)
		{
			m_pgmEnv.Buzzer = 0;

			if (m_St.SRM_Status1.Bit.Fault)
			{
				LED_Bar_Control(LAMP_RED);
			}
			else
			{
				if (m_pgmEnv.Home_Lamp_Flag)
				{
					LED_Bar_Control(LAMP_YELLOW);

					s_LampToggleMode = 1;
				}
				else
				{
					if (m_St.SRM_Mode.Bit.Manual)
					{
						LED_Bar_Control(LAMP_CYAN);
					}
					else if (m_St.SRM_Mode.Bit.Auto)
					{
						if (m_St.SRM_Status1.Bit.StartOn)
						{
							if ((m_pgmEnv.SRM_RunMode >= RUN_SEQ_START)
								&& (m_pgmEnv.SRM_RunMode <= RUN_SEQ_COMPLETE))
							{
								s_LampToggleMode = 1;
							}
							LED_Bar_Control(LAMP_GREEN);
						}
						else
						{
							LED_Bar_Control(LAMP_WHITE);
						}
					}
					else if (m_St.SRM_Mode.Bit.Setup)
					{
						if (!m_St.SRM_Status1.Bit.Fault)
						{
							LED_Bar_Control(LAMP_YELLOW);
						}
					}
				}
			}
		}
		else
		{
			LED_Bar_Control(LAMP_OFF);
			s_LampToggleMode = 0;
		}
	}
}

void TowerLamp_Control_Proc_1()
{
	static INT32U s_chkTimer = 0;
	static INT08U s_LampToggleMode = 0;

	if (getCalcTimer1ms(s_chkTimer) >= 300)
	{
		s_chkTimer = m_pgmEnv.timer1ms;

		if (s_LampToggleMode == 0)
		{
			m_pgmEnv.Buzzer = 0;

			if (m_St.SRM_Status1.Bit.Fault)
			{
				DO_Control(OUT_RED, 1);	// 
				DO_Control(OUT_BL, 0);	// 
				DO_Control(OUT_YEL, 0);	// 
				DO_Control(OUT_GRN, 0);	// 
			}
			else
			{
				if (m_pgmEnv.Home_Lamp_Flag)
				{
					DO_Control(OUT_RED, 0);	// 
					DO_Control(OUT_BL, 0);	// 
					DO_Control(OUT_YEL, 1);	// 
					DO_Control(OUT_GRN, 0);	// 

					s_LampToggleMode = 1;
				}
				else
				{
					if (m_St.SRM_Mode.Bit.Manual)
					{
						if (m_St.SRM_Status2.Bit.ManualSW)
						{
							DO_Control(OUT_RED, 0);		// 
							DO_Control(OUT_BL, 1);		// 
							DO_Control(OUT_YEL, 1);		// 
							DO_Control(OUT_GRN, 0);		// 
						}
						else
						{
							if (m_St.SRM_Mode.Bit.Force)
							{
								DO_Control(OUT_RED, 0);		// 
								DO_Control(OUT_BL, 0);		// 
								DO_Control(OUT_YEL, 1);		// 
								DO_Control(OUT_GRN, 0);		// 
							}
							else
							{
								DO_Control(OUT_RED, 0);		// 
								DO_Control(OUT_BL, 1);		// 
								DO_Control(OUT_YEL, 0);		// 
								DO_Control(OUT_GRN, 0);		// 
							}
							
						}
					}
					else if (m_St.SRM_Mode.Bit.Auto)
					{
						if (m_St.SRM_Status1.Bit.StartOn)
						{
							if ((m_pgmEnv.SRM_RunMode >= RUN_SEQ_START)
								&& (m_pgmEnv.SRM_RunMode <= RUN_SEQ_COMPLETE))
							{
								s_LampToggleMode = 1;
							}
							else if ((m_pgmEnv.SRM_RunMode >= RUN_SEQ_STICKY_START)
								&& (m_pgmEnv.SRM_RunMode <= RUN_SEQ_STICKY_COMPLETE))
							{
								s_LampToggleMode = 1;
							}

							DO_Control(OUT_RED, 0);		// 
							DO_Control(OUT_BL, 0);		// 
							DO_Control(OUT_YEL, 0);		// 
							DO_Control(OUT_GRN, 1);		// 
						}
						else
						{
							DO_Control(OUT_RED, 0);		// 
							DO_Control(OUT_BL, 1);		// 
							DO_Control(OUT_YEL, 0);		// 
							DO_Control(OUT_GRN, 1);		// 
						}
					}
					else if (m_St.SRM_Mode.Bit.Setup)
					{
						if (!m_St.SRM_Status1.Bit.Fault)
						{
							DO_Control(OUT_RED, 0);	// 
							DO_Control(OUT_BL, 1);	// 
							DO_Control(OUT_YEL, 1);	// 
							DO_Control(OUT_GRN, 1);	// 
						}
					}
				}
			}
		}
		else
		{
			s_LampToggleMode = 0;

			DO_Control(OUT_RED, 0);	// 
			DO_Control(OUT_BL, 0);	// 
			DO_Control(OUT_YEL, 0);	// 
			DO_Control(OUT_GRN, 0);	// 
		}
	}
}

void TowerLamp_Control_Proc_2()
{
	static INT32U s_chkTimer = 0;
	static INT08U s_LampToggleMode = 0;

	if (getCalcTimer1ms(s_chkTimer) >= 300)
	{
		s_chkTimer = m_pgmEnv.timer1ms;

		if (s_LampToggleMode == 0)
		{
			m_pgmEnv.Buzzer = 0;

			if (m_St.SRM_Status1.Bit.Fault)
			{
				DO_Control(OUT_RED, 1);	// 
				DO_Control(OUT_BL, 0);	// 
				DO_Control(OUT_YEL, 0);	// 
				DO_Control(OUT_GRN, 0);	// 
			}
			else
			{
				if (m_pgmEnv.Home_Lamp_Flag)
				{
					DO_Control(OUT_RED, 0);	// 
					DO_Control(OUT_BL, 0);	// 
					DO_Control(OUT_YEL, 1);	// 
					DO_Control(OUT_GRN, 0);	// 

					s_LampToggleMode = 1;
				}
				else
				{
					if (m_St.SRM_Mode.Bit.Manual)
					{
						if (m_St.SRM_Status2.Bit.ManualSW)
						{
							if (m_St.SRM_Mode.Bit.Force)
							{
								DO_Control(OUT_RED, 0);		// 
								DO_Control(OUT_BL, 0);		// 
								DO_Control(OUT_YEL, 1);		// 
								DO_Control(OUT_GRN, 0);		// 
								DO_Control(OUT_WHI, 1);		// 
							}
							else
							{
								DO_Control(OUT_RED, 0);		// 
								DO_Control(OUT_BL, 1);		// 
								DO_Control(OUT_YEL, 0);		// 
								DO_Control(OUT_GRN, 0);		// 
								DO_Control(OUT_WHI, 1);		// 
							}
						}
						else
						{
							if (m_St.SRM_Mode.Bit.Force)
							{
								DO_Control(OUT_RED, 0);		// 
								DO_Control(OUT_BL, 0);		// 
								DO_Control(OUT_YEL, 1);		// 
								DO_Control(OUT_GRN, 0);		// 
								DO_Control(OUT_WHI, 0);		// 
							}
							else
							{
								DO_Control(OUT_RED, 0);		// 
								DO_Control(OUT_BL, 1);		// 
								DO_Control(OUT_YEL, 0);		// 
								DO_Control(OUT_GRN, 0);		// 
								DO_Control(OUT_WHI, 0);		// 
							}
						}
					}
					else if (m_St.SRM_Mode.Bit.Auto)
					{
						if (m_St.SRM_Status1.Bit.StartOn)
						{
							if ((m_pgmEnv.SRM_RunMode >= RUN_SEQ_START)
								&& (m_pgmEnv.SRM_RunMode <= RUN_SEQ_COMPLETE))
							{
								s_LampToggleMode = 1;
							}
							else if ((m_pgmEnv.SRM_RunMode >= RUN_SEQ_STICKY_START)
								&& (m_pgmEnv.SRM_RunMode <= RUN_SEQ_STICKY_COMPLETE))
							{
								s_LampToggleMode = 1;
							}

							DO_Control(OUT_RED, 0);		// 
							DO_Control(OUT_BL, 0);		// 
							DO_Control(OUT_YEL, 0);		// 
							DO_Control(OUT_GRN, 1);		// 
							DO_Control(OUT_WHI, 0);		// 
						}
						else
						{
							DO_Control(OUT_RED, 0);		// 
							DO_Control(OUT_BL, 0);		// 
							DO_Control(OUT_YEL, 0);		// 
							DO_Control(OUT_GRN, 0);		// 
							DO_Control(OUT_WHI, 1);		// 
						}
					}
					else if (m_St.SRM_Mode.Bit.Setup)
					{
						if (!m_St.SRM_Status1.Bit.Fault)
						{
							DO_Control(OUT_RED, 0);		// 
							DO_Control(OUT_BL, 1);		// 
							DO_Control(OUT_YEL, 1);		// 
							DO_Control(OUT_GRN, 1);		// 
							DO_Control(OUT_WHI, 1);		// 
						}
					}
				}
			}
		}
		else
		{
			s_LampToggleMode = 0;

			DO_Control(OUT_RED, 0);	// 
			DO_Control(OUT_BL, 0);	// 
			DO_Control(OUT_YEL, 0);	// 
			DO_Control(OUT_GRN, 0);	// 
			DO_Control(OUT_WHI, 0);		// 
		}
	}
}

void SignalLampManager(void)
{
	static INT08U s_Init = 0;
	static void (*s_fpPosition)();   // 반환값과 매개변수가 없는 함수 포인터 fp 선언

	if (m_ExtSEnv.Machine.mType.Lamp_Type == 0)
	{
		// LED BAR
		LED_Bar_Control_Proc();
	}
	else
	{
		// TOWER LAMP
		if (s_Init == 0)
		{
			s_Init = 1;

			if (checkFusingString((INT08U*)m_ExtSEnv.mDevice.ProjectID.ProjectNo, (INT08U*)HANKOOK_TIRE_TP2, 6) == 0)
			{
				s_fpPosition = TowerLamp_Control_Proc_1;
			}
			else
			{
				s_fpPosition = TowerLamp_Control_Proc_2;
			}
		}
		else
		{
			s_fpPosition();
		}
	}
}


void ModeKeyManager(void)
{
	static INT08U s_Init;
	static INT08U s_PreSRM_Mode;
	static INT08U s_Manual_SW;

	static INT08U s_Manual_SW_Timer_Flag;
	static INT32U s_Manual_SW_Timer;

	INT08U nCur_Manual_SW = 0;

#if DEBUG_HMI_TEST_MODE
	asm volatile("NOP");
#else
	if (m_pgmEnv.Test_Simulator.Test_Manual_Mode)
	{
		if (m_pgmEnv.Test_Simulator.Test_Manual_Mode_Ctr == 1)
		{
			nCur_Manual_SW = 1;
		}
		else
		{
			nCur_Manual_SW = 0;
		}
	}
	else
	{
		if (Get_DI_UseFlag(IN_AUTO) && Get_DI_UseFlag(IN_INSP))
		{
			if (Get_DI_State(IN_AUTO) && (Get_DI_State(IN_INSP) == 0))
			{
				nCur_Manual_SW = 0;
			}

			if (Get_DI_State(IN_INSP) && (Get_DI_State(IN_AUTO) == 0))
			{
				nCur_Manual_SW = 1;
			}
		}
		else if (Get_DI_UseFlag(IN_AUTO))
		{
			Get_DI_State(IN_AUTO) ? (nCur_Manual_SW = 1) : (nCur_Manual_SW = 0);
		}
	}
	

	if (!s_Init)
	{
		s_Init = 1;

		s_Manual_SW = nCur_Manual_SW;
		m_St.SRM_Status2.Bit.ManualSW = s_Manual_SW;
	}
	else
	{
		if (s_Manual_SW != nCur_Manual_SW)
		{
			s_Manual_SW = nCur_Manual_SW;
			s_Manual_SW_Timer_Flag = 1;
			s_Manual_SW_Timer = m_pgmEnv.timer1ms;
		}
		else
		{
			if (s_Manual_SW_Timer_Flag)
			{
				if (getCalcTimer1ms(s_Manual_SW_Timer) > 100)
				{
					s_Manual_SW_Timer_Flag = 0;

					m_St.SRM_Status2.Bit.ManualSW = s_Manual_SW;

					if (m_St.SRM_Status2.Bit.ManualSW)
					{
						// 疫꿸�占쏙옙獄�占� 占쏙옙占쏙옙 -> 占쏙옙占쏙옙
						// 占쏙옙占쏙옙筌��ㅿ옙占쏙옙占쏙옙占� 疫꿸�占쏙옙獄�占� 占쏙옙占쏙옙 占쏙옙, 占쏙옙占쏙옙筌��ㅿ옙占썸에占� 癰�占썲��占�.
						if (m_St.SRM_Mode.Bit.Auto)
						{
							Change_DeviceMode(DEVICE_MANUAL_MODE, 1);
						}
					}
					else
					{
						// 疫꿸�占쏙옙獄�占� 占쏙옙占쏙옙 -> 占쏙옙占쏙옙
						m_pgmEnv.Manual_SW_Change_Auto = 1;

						// 揶�占쏙옙占쏙��ㅿ옙占� 占썬�쇽옙占� 占쎈��猿�
						if (m_St.SRM_Mode.Bit.Force)
						{
							m_St.SRM_Mode.Bit.Force = 0;
						}
					}
				}
			}
		}
	}
#endif

	/*
	m_TestStatus.Ctrl[DEBUG_CTR_1] = Get_DI_State(IN_AUTO);
	m_TestStatus.Ctrl[DEBUG_CTR_2] = Get_DI_State(IN_INSP);
	m_TestStatus.Ctrl[DEBUG_CTR_3] = m_St.SRM_Status2.Bit.ModeSW;
	*/
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Delete_ForkMoveInfo(INT08U num)
{
	if (num < 2)
	{
		m_St.ForkWork[num].WorkNum_Move = 0;
		m_St.ForkWork[num].OrderStatus_Move = 0;
		m_St.ForkWork[num].OrderProcess_Move = 0;
		//m_St.ForkWork[num].OrderCode_Fork = 0;
	}
}

//포크 이동상태 저장 (포크번호, 작업상태)
void Save_ForkMove_OrderStatus(INT08U num, INT08U st)
{
	// 전달받은 숫자가 2보다 작으면 실행
	if (num < 2)
	{
		if (m_St.ForkWork[num].OrderStatus_Move != st)// 포크가 1번과 2번이 있는데 포크모터의 번호같음, 포크모터 1번의 작업이동상태가 넘겨받는 작업상태인듯 ---> 이코드에서는 포크 1의 작업상태가 이동이 아닌경우)
		{
			m_St.ForkWork[num].OrderStatus_Move = st;//m_St.ForkWork[num].OrderStatus_Move = st; ---> 지상반쪽 0x30 상태요구 응답에 실림
			m_BKSram.WorkInfo.WorkSt[num].OrderStatus_Move = st;// 전달받은 상태를 MCU SRAM에 씀 -> DTCM RAM 미러 (mcu안 구조체 복사본)
			saveBKSramBlock((INT08U*)&m_BKSram.WorkInfo.WorkSt[num].OrderStatus_Move, 1);//VBAT 있으면 전원 꺼져도 유지함 뒤에 숫자 1은 1바이트라는 뜻
		}

		//m_St.ForkWork[num].OrderStatus_Move = st;
	}
}

void Save_ForkMove_OrderProcess(INT08U num, INT08U st)
{
	if (num < 2)
	{
		if (m_St.ForkWork[num].OrderProcess_Move != st)
		{
			m_St.ForkWork[num].OrderProcess_Move = st;
			m_BKSram.WorkInfo.WorkSt[num].OrderProcess_Move = st;
			saveBKSramBlock((INT08U*)&m_BKSram.WorkInfo.WorkSt[num].OrderProcess_Move, 1);
		}

		//m_St.ForkWork[num].OrderProcess_Move = st;
	}
}

void Delete_ForkWorkInfo(INT08U num)
{
	if (num < 2)
	{
		m_St.ForkWork[num].WorkNum_Fork = 0;
		m_St.ForkWork[num].OrderStatus_Fork = 0;
		m_St.ForkWork[num].OrderProcess_Fork = 0;
		m_St.ForkWork[num].OrderCode_Fork = 0;
	}
}


void Save_ForkWork_OrderStatus(INT08U num, INT08U nStatus)
{
	if (num < 2)
	{
		if (m_St.ForkWork[num].OrderStatus_Fork != nStatus)
		{
			m_St.ForkWork[num].OrderStatus_Fork = nStatus;
			m_BKSram.WorkInfo.WorkSt[num].OrderStatus_Fork = nStatus;
			saveBKSramBlock((INT08U*)&m_BKSram.WorkInfo.WorkSt[num].OrderStatus_Fork, 1);
		}
	}
}

void Save_ForkWork_OrderProcess(INT08U num, INT08U nProcess)
{
	if (num < 2)
	{
		if (m_St.ForkWork[num].OrderProcess_Fork != nProcess)
		{
			m_St.ForkWork[num].OrderProcess_Fork = nProcess;

			m_BKSram.WorkInfo.WorkSt[num].OrderProcess_Fork = nProcess;
			saveBKSramBlock((INT08U*)&m_BKSram.WorkInfo.WorkSt[num].OrderProcess_Fork, 1);
		}
	}
}

void Save_ForkWork_Information(INT08U num, INT08U OrderStatus, INT08U OrderProcess)
{
	if (num < 2)
	{
		if ((m_St.ForkWork[num].OrderProcess_Fork != OrderProcess)
			|| (m_St.ForkWork[num].OrderStatus_Fork != OrderStatus))
		{
			m_St.ForkWork[num].OrderStatus_Fork = OrderStatus;
			m_St.ForkWork[num].OrderProcess_Fork = OrderProcess;

			memcpy((INT08U*)&m_BKSram.WorkInfo.WorkSt[num], (INT08U*)&m_St.ForkWork[num], sizeof(WorkInfoSTR));
			saveBKSramBlock((INT08U*)&m_BKSram.WorkInfo.WorkSt[num], sizeof(WorkInfoSTR));
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ComPortLinkCheck(void)
{
	static INT32U s_runTimer = 0;
	INT08U nPort;

	if (getCalcTimer1ms(s_runTimer) >= 100)
	{
		s_runTimer = m_pgmEnv.timer1ms;

		for (nPort = 0; nPort < 20; nPort++)
		{
			if (m_pgmEnv.PortLinkSt[nPort])
			{
				//if (getCalcTimer1ms(m_pgmEnv.PortLinkTimer[nPort]) >= 1500)
				if (getCalcTimer1ms(m_pgmEnv.PortLinkTimer[nPort]) >= 2000)
				{
					m_pgmEnv.PortLinkSt[nPort] = 0;
				}
			}
		}
	}

	(m_pgmEnv.PortLinkSt[rsTMLPort]) ? \
		(m_DevStatus.mLinkStatus.TML_RS232 = 1) : (m_DevStatus.mLinkStatus.TML_RS232 = 0);

	(m_pgmEnv.PortLinkSt[rsETHUDPPort_Uplink]) ? \
		(m_DevStatus.mLinkStatus.EtherNet_LAN0 = 1) : (m_DevStatus.mLinkStatus.EtherNet_LAN0 = 0);

	(m_pgmEnv.PortLinkSt[rsETHUDPPort_DwLink]) ? \
		(m_DevStatus.mLinkStatus.EtherNet_LAN1 = 1) : (m_DevStatus.mLinkStatus.EtherNet_LAN1 = 0);

	(m_pgmEnv.PortLinkSt[rsMCU_DEBUG_Port]) ? \
		(m_DevStatus.mLinkStatus.DBG_TTL232 = 1) : (m_DevStatus.mLinkStatus.DBG_TTL232 = 0);

	(m_pgmEnv.PortLinkSt[rsRS485_422_Port]) ? \
		(m_DevStatus.mLinkStatus.HMI_RS485 = 1) : (m_DevStatus.mLinkStatus.HMI_RS485 = 0);

	(m_pgmEnv.PortLinkSt[rsHMI_Port]) ? \
		(m_DevStatus.mLinkStatus.Extra_Slave |= cbits[2]) : (m_DevStatus.mLinkStatus.Extra_Slave &= nbits[2]);
	
	(m_pgmEnv.PortLinkSt[rsHMI_UP_Port]) ? \
		(m_DevStatus.mLinkStatus.Extra_Slave |= cbits[5]) : (m_DevStatus.mLinkStatus.Extra_Slave &= nbits[5]);
}

void PDoorCheck(void)
{
	if (m_ExtSEnv2.CtrParam.DoorSensor_UseFlag == 1)
	{
		if (m_pgmEnv.SRM_RunMode == 0)
		{
			// 雅��놂옙占�/占쎈객占썰빳占� 占쏙옙占쏙옙 占쎈����揶�占쏙�占쏙옙占쏙옙占� 野���占쎄�占� 占쏙옙占쏙옙.
			if (Get_DI_State(IN_PDOOR) == 0)
			{
				DO_Control(OUT_PLAMP, 1);
			}
			else
			{
				DO_Control(OUT_PLAMP, 0);
			}
		}
	}
}

void Fan_Ctrl_Process(void)
{
	static INT32U s_chkTimer = 0;
	static INT32U s_chkTimer1 = 0;
	//m_TestStatus.St[DEBUG_STR_17] = m_pgmEnv.SRM_RunMode;

	if ((m_St.SRM_Mode.Bit.Auto == 1) && (m_St.SRM_Status1.Bit.StartOn == 1))
	{
		if ((m_pgmEnv.SRM_RunMode >= RUN_SEQ_START) && (m_pgmEnv.SRM_RunMode <= RUN_SEQ_COMPLETE))
		{
			DO_Control(OUT_PFAN, 1);
			s_chkTimer = m_pgmEnv.timer1ms;
		}
		else
		{
			if (getCalcTimer1ms(s_chkTimer) >= m_ExtSEnv2.CtrParam.FanControl.OperTime * 1000)
			{
				DO_Control(OUT_PFAN, 0);
				s_chkTimer = m_pgmEnv.timer1ms;
			}
		}
	}
	else
	{
		if (m_ExtSEnv2.CtrParam.FanControl.TempSensor_Install)
		{
			if (getCalcTimer1ms(s_chkTimer1) >= 5000)
			{
				if (Get_DI_State(IN_PTH) == 1)
				{
					DO_Control(OUT_PFAN, 1);
					s_chkTimer1 = m_pgmEnv.timer1ms;
				}
				else
				{
					DO_Control(OUT_PFAN, 0);
					s_chkTimer1 = m_pgmEnv.timer1ms;
				}
			}
		}
		else
		{
			if (getCalcTimer1ms(s_chkTimer) >= m_ExtSEnv2.CtrParam.FanControl.OperTime * 1000)
			{
				DO_Control(OUT_PFAN, 0);
				s_chkTimer = m_pgmEnv.timer1ms;
			}
		}
	}
}

enum BZ_STEP {
	BZ_STANBY = 0,
	BZ_ERROR,
	BZ_WARNING,
	BZ_AUTO_ON,
	BZ_AUTO_OFF,
	BZ_AUTO_START,
};


void Buzzer_Control_Proc(void)
{
	static INT32U s_chkTimer = 0;
	static INT32U s_RunTimer = 0;
	static INT08U s_bzStep = BZ_STANBY, s_Bz_Toggle_Cnt = 0;
	static INT08U s_OnOff_Flag = 0;

	INT32U nAutoBuzzerTime = 0;

	switch (s_bzStep)
	{
	case BZ_STANBY :
		if (m_St.SRM_Status1.Bit.Fault)
		{
			s_chkTimer = m_pgmEnv.timer1ms;
			s_bzStep = BZ_ERROR;
			break;
		}
		else
		{
			m_pgmEnv.Bz_Force_Stop = 0;
		}

		if (m_St.SRM_Status1.Bit.Warning)
		{
			s_chkTimer = m_pgmEnv.timer1ms;
			s_bzStep = BZ_WARNING;
			break;
		}

		if (m_pgmEnv.Buzzer_OneShot)
		{
			m_pgmEnv.Buzzer_OneShot = 0;

			DO_Control(OUT_SUD, 1);
			
			s_chkTimer = m_pgmEnv.timer1ms;
			s_bzStep = BZ_AUTO_START;
			break;
		}
		
		if (m_pgmEnv.Buzzer_Online)
		{
			//m_TestStatus.Ctrl[DEBUG_CTR_12] = m_pgmEnv.Buzzer_Online;
			m_pgmEnv.Buzzer_Online = 0;
			
			s_Bz_Toggle_Cnt = 0; 
			s_chkTimer = m_pgmEnv.timer1ms;
			s_bzStep = BZ_AUTO_ON;
			break;
		}
		
		DO_Control(OUT_SUD, 0);
		s_OnOff_Flag = 0;

		//s_chkTimer = m_pgmEnv.timer1ms;
		break;

	case BZ_ERROR:
		if (m_St.MainErrCode == 0)
		{
			m_pgmEnv.Bz_Force_Stop = 0;
			DO_Control(OUT_SUD, 0);

			s_bzStep = BZ_STANBY;
		}
		else
		{
			if (m_pgmEnv.Bz_Force_Stop)
			{
				DO_Control(OUT_SUD, 0);
			}
			else
			{
				if (checkFusingString((INT08U*)m_ExtSEnv.mDevice.ProjectID.ProjectNo, (INT08U*)HANKOOK_TIRE_TP2, 6) == 0)
				{
					// Lamp Buzzer Toggle Type
					if (m_ExtSEnv2.CtrParam.BuzzerCtr.Fault_OnTime > 0)
					{
						if (getCalcTimer1ms(s_chkTimer) >= m_ExtSEnv2.CtrParam.BuzzerCtr.Fault_OnTime * 10)
						{
							DO_Control(OUT_SUD, 0);
						}
						else
						{
							DO_Control(OUT_SUD, 1);
						}
					}
				}
				else
				{
					if (m_ExtSEnv2.CtrParam.BuzzerCtr.Fault_OnTime > 0)
					{
						if (getCalcTimer1ms(s_chkTimer) >= m_ExtSEnv2.CtrParam.BuzzerCtr.Fault_OnTime * 10)
						{
							DO_Control(OUT_SUD, 0);
						}
						else
						{
							if (getCalcTimer1ms(s_RunTimer) >= DEF_FAULT_BUZZER_INTERVAL)
							{
								s_OnOff_Flag ^= 0x01;
								DO_Control(OUT_SUD, s_OnOff_Flag);

								s_RunTimer = m_pgmEnv.timer1ms;
							}
						}
					}
					else
					{
						if (getCalcTimer1ms(s_RunTimer) >= DEF_FAULT_BUZZER_INTERVAL)
						{
							s_OnOff_Flag ^= 0x01;
							DO_Control(OUT_SUD, s_OnOff_Flag);

							s_RunTimer = m_pgmEnv.timer1ms;
						}
					}
				}
			}
		}
		break;

	case BZ_WARNING:
		if (m_St.MainErrCode == 0)
		{
			m_pgmEnv.Bz_Force_Stop = 0;
			DO_Control(OUT_SUD, 0);

			s_bzStep = BZ_STANBY;
		}
		else
		{
			if (m_pgmEnv.Bz_Force_Stop)
			{
				DO_Control(OUT_SUD, 0);
			}
			else
			{
				if (checkFusingString((INT08U*)m_ExtSEnv.mDevice.ProjectID.ProjectNo, (INT08U*)HANKOOK_TIRE_TP2, 6) == 0)
				{
					if (m_ExtSEnv2.CtrParam.BuzzerCtr.Fault_OnTime > 0)
					{
						if (getCalcTimer1ms(s_chkTimer) >= m_ExtSEnv2.CtrParam.BuzzerCtr.Warning_OnTime * 10)
						{
							DO_Control(OUT_SUD, 0);
						}
						else
						{
							DO_Control(OUT_SUD, 1);
						}
					}
				}
				else
				{
					if (m_ExtSEnv2.CtrParam.BuzzerCtr.Fault_OnTime > 0)
					{
						if (getCalcTimer1ms(s_chkTimer) >= m_ExtSEnv2.CtrParam.BuzzerCtr.Warning_OnTime * 10)
						{
							DO_Control(OUT_SUD, 0);
						}
						else
						{
							if (getCalcTimer1ms(s_RunTimer) >= DEF_WARNING_BUZZER_INTERVAL)
							{
								s_OnOff_Flag ^= 0x01;
								DO_Control(OUT_SUD, s_OnOff_Flag);

								s_RunTimer = m_pgmEnv.timer1ms;
							}
						}
					}
					else
					{
						if (getCalcTimer1ms(s_RunTimer) >= DEF_WARNING_BUZZER_INTERVAL)
						{
							s_OnOff_Flag ^= 0x01;
							DO_Control(OUT_SUD, s_OnOff_Flag);

							s_RunTimer = m_pgmEnv.timer1ms;
						}
					}
				}
				
			}
		}
		break;

	case BZ_AUTO_ON:
		if (checkFusingString((INT08U*)m_ExtSEnv.mDevice.ProjectID.ProjectNo, (INT08U*)HANKOOK_TIRE_TP2, 6) == 0)
		{
			nAutoBuzzerTime = (m_ExtSEnv2.CtrParam.BuzzerCtr.AutoChange_OnTime * 10) \
							+ (m_ExtSEnv2.CtrParam.BuzzerCtr.AutoChange_OffTime * 10);

			if (getCalcTimer1ms(s_chkTimer) > nAutoBuzzerTime)
			{
				s_bzStep = BZ_AUTO_START;
			}
		}
		else
		{
			if (s_Bz_Toggle_Cnt == 0)
			{
				DO_Control(OUT_SUD, 1);

				s_chkTimer = m_pgmEnv.timer1ms;
				s_bzStep = BZ_AUTO_OFF;
			}
			else
			{
				if (getCalcTimer1ms(s_chkTimer) > m_ExtSEnv2.CtrParam.BuzzerCtr.AutoChange_OnTime * 10)
				{
					DO_Control(OUT_SUD, 1);

					s_chkTimer = m_pgmEnv.timer1ms;
					s_bzStep = BZ_AUTO_OFF;
				}
			}
		}
		break;

	case BZ_AUTO_OFF:
		if (getCalcTimer1ms(s_chkTimer) > m_ExtSEnv2.CtrParam.BuzzerCtr.AutoChange_OffTime * 10)
		{
			DO_Control(OUT_SUD, 0);

			s_chkTimer = m_pgmEnv.timer1ms;

			++s_Bz_Toggle_Cnt;
			if (s_Bz_Toggle_Cnt >= m_ExtSEnv2.CtrParam.BuzzerCtr.AutoChange_Toggle_Cnt)
			{
				s_bzStep = BZ_STANBY;
			}
			else
			{
				s_bzStep = BZ_AUTO_ON;
			}
		}
		break;

	case BZ_AUTO_START:
		//if (getCalcTimer1ms(s_chkTimer) > m_ExtSEnv2.RtvCtrParam.BuzzerCtr.Change_AutoMode_OnTime * 10)
		if (getCalcTimer1ms(s_chkTimer) > 1000)
		{
			DO_Control(OUT_SUD, 0);

			s_bzStep = BZ_STANBY;
		}
		break;
	}
	
	//Set_TestStatus(DEBUG_STR_63, s_bzStep);
	//m_TestStatus.Ctrl[DEBUG_CTR_13] = s_bzStep;
}

void AlarmManager(void)
{
	runningLED();

	getSystemDateTime();

	DIManager();
	AIManager();
	FNDManager();
	ModeKeyManager();

	SignalLampManager();	

	ComPortLinkCheck();

	PDoorCheck();

	Fan_Ctrl_Process();

	Buzzer_Control_Proc();

	//m_TestStatus.St[DEBUG_STR_23] = m_pgmEnv.DOSt;
}
