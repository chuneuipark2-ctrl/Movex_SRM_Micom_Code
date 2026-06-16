/*
 * Mcu_Test.c
 *
 *  Created on: Feb 12, 2023
 *      Author: 
 */

#include "Mcu_Test.h"
#include "fpga.h"
#include "com_hmi.h"
#include "encoder.h"
#include "can.h"
#include "com_tml.h"
#include "usb_user.h"

#include "ecat_main.h"

extern TIM_HandleTypeDef htim2;

McuTestCtrSTR	m_McuTestCtr;
McuTestStSTR	m_McuTestSt;

INT32S conv_Graycode_TravPosition(INT32U gray_code)
{
	INT32S pos = 0;

	// PXV100S    
	// bit 0 : Err      1:Reader aligned incorrectly(rotated 180), 2:Position Error
	// bit 1 : Wrn      Reserved
	// bit 2 : No Position codes in the reading window
	//pos = gray_code / 4;
	pos = gray_code >> 3;

	return pos;
}

/*
void PTO_Test_Proc()
{
	static INT32U s_Seq_Timer;
	static INT08U s_PTO_Test_mode;

	static INT32U s_SetPTO_Freq;
	static INT32U s_CmdPTO_Freq;

	switch (s_PTO_Test_mode)
	{
	case 0:
		if (m_pgmEnv.isFpgaRun)
		{
			s_SetPTO_Freq = 0;
			s_CmdPTO_Freq = 0;

			//m_TestStatus.Ctrl[DEBUG_CTR_16] = 0;

			set_FPGA_PTO_Pulse_Freq(s_SetPTO_Freq);
			s_Seq_Timer = m_pgmEnv.timer1ms;
			s_PTO_Test_mode = 1;
		}
		break;

	case 1:
		if (getCalcTimer1ms(s_Seq_Timer) > 100)
		{
			s_CmdPTO_Freq = m_McuTestCtr.PTO_Output;
			if (s_CmdPTO_Freq != s_SetPTO_Freq)
			{
				s_SetPTO_Freq = s_CmdPTO_Freq;

				set_FPGA_PTO_Pulse_Freq(s_SetPTO_Freq);

				m_McuTestSt.PTO_Output = s_SetPTO_Freq;
			}

			s_Seq_Timer = m_pgmEnv.timer1ms;
		}
		break;

	case 2:
		break;

	case 3:
		break;

	case 4:
		break;

	case 5:
		break;
	}
}
*/

void Test_MCU_Test_Control()
{
	/*
	m_McuTestCtr.RS232_Test		= (INT08U)m_TestStatus.Ctrl[DEBUG_CTR_1];
	m_McuTestCtr.RS485_Test1	= (INT08U)m_TestStatus.Ctrl[DEBUG_CTR_2];
	m_McuTestCtr.RS485_Test2	= (INT08U)m_TestStatus.Ctrl[DEBUG_CTR_3];
	m_McuTestCtr.RS422_Test1	= (INT08U)m_TestStatus.Ctrl[DEBUG_CTR_4];
	m_McuTestCtr.RS422_Test2	= (INT08U)m_TestStatus.Ctrl[DEBUG_CTR_5];
	m_McuTestCtr.CAN_Test1		= (INT08U)m_TestStatus.Ctrl[DEBUG_CTR_6];
	m_McuTestCtr.CAN_Test2		= (INT08U)m_TestStatus.Ctrl[DEBUG_CTR_7];
	m_McuTestCtr.EtherNet_Test1 = (INT08U)m_TestStatus.Ctrl[DEBUG_CTR_8];
	m_McuTestCtr.EtherNet_Test2 = (INT08U)m_TestStatus.Ctrl[DEBUG_CTR_9];
	m_McuTestCtr.EtherCAT_Test  = (INT08U)m_TestStatus.Ctrl[DEBUG_CTR_10];
	m_McuTestCtr.SSI_Test		= (INT08U)m_TestStatus.Ctrl[DEBUG_CTR_11];
	m_McuTestCtr.Encoder_Test	= (INT08U)m_TestStatus.Ctrl[DEBUG_CTR_12];
	m_McuTestCtr.PTO_Output		= (INT32U)m_TestStatus.Ctrl[DEBUG_CTR_13];
	m_McuTestCtr.DIO_Test		= (INT08U)m_TestStatus.Ctrl[DEBUG_CTR_14];
// 	m_McuTestCtr.SD_Card_Test	= (INT08U)m_TestStatus.Ctrl[DEBUG_CTR_14];
// 	m_McuTestCtr.USB_Test		= (INT08U)m_TestStatus.Ctrl[DEBUG_CTR_15];
	*/

	/*
	m_TestStatus.St[DEBUG_STR_1] = m_McuTestSt.RS232_RecvCnt;
	m_TestStatus.St[DEBUG_STR_2] = m_McuTestSt.RS485_P1_Enable;
	m_TestStatus.St[DEBUG_STR_3] = m_McuTestSt.RS485_P1_RecvCnt;
	m_TestStatus.St[DEBUG_STR_4] = m_McuTestSt.RS485_P2_Enable;
	m_TestStatus.St[DEBUG_STR_5] = m_McuTestSt.RS485_P2_RecvCnt;
	m_TestStatus.St[DEBUG_STR_6] = m_McuTestSt.RS422_P1_Enable;
	m_TestStatus.St[DEBUG_STR_7] = m_McuTestSt.RS422_P1_RecvCnt;
	m_TestStatus.St[DEBUG_STR_8] = m_McuTestSt.RS422_P2_Enable;
	m_TestStatus.St[DEBUG_STR_9] = m_McuTestSt.RS422_P2_RecvCnt;
	m_TestStatus.St[DEBUG_STR_10] = m_McuTestSt.CAN1_RecvCnt;
	m_TestStatus.St[DEBUG_STR_11] = m_McuTestSt.CAN2_RecvCnt;
	m_TestStatus.St[DEBUG_STR_12] = m_McuTestSt.EtherNet1_RecvCnt;
	m_TestStatus.St[DEBUG_STR_13] = m_McuTestSt.EtherNet2_RecvCnt;
	m_TestStatus.St[DEBUG_STR_14] = m_McuTestSt.EtherCAT_Test;
	m_TestStatus.St[DEBUG_STR_15] = m_McuTestSt.SSI_Position;
	m_TestStatus.St[DEBUG_STR_16] = (INT32S)m_McuTestSt.Encoder_In;
	m_TestStatus.St[DEBUG_STR_17] = m_McuTestSt.PTO_Output;
	m_TestStatus.St[DEBUG_STR_18] = m_McuTestSt.DOSt;
	m_TestStatus.St[DEBUG_STR_19] = m_McuTestSt.DISt;

	m_TestStatus.St[DEBUG_STR_20] = m_McuTestSt.USB_Test_Enable;
	m_TestStatus.St[DEBUG_STR_21] = m_McuTestSt.USB_Test;
	*/

}

void Update_Mcu_Test_Status()
{
	m_McuTestSt.ProtocolVer = m_DevStatus.ProtocolVer;
	memcpy((INT08U*)m_McuTestSt.PgmVer, (INT08U*)m_DevStatus.PgmVer, 4);
	
	m_McuTestSt.SysTime = m_St.SysTime;
	
	m_McuTestSt.Mode_SW = m_DevStatus.Mode_SW;
	m_McuTestSt.ID_SW = m_DevStatus.ID_SW;

	m_McuTestSt.FPGA_Connect = m_pgmEnv.isFpgaRun;
	m_McuTestSt.ExtFlash_Connect = m_pgmEnv.SFlash_Install;
}

void FND_Test_Proc(INT08U* s_InitFlag)
{
	static INT32U s_Timer;

	if (*s_InitFlag == 0)
	{
		*s_InitFlag = 1;
		m_McuTestSt.FND_Display = 0;

		s_Timer = m_pgmEnv.timer1ms;
	}
	else
	{
		//if (getCalcTimer1ms(s_Timer) > 1000)
		if (getCalcTimer1ms(s_Timer) > 300)
		{
			++m_McuTestSt.FND_Display;
			if (m_McuTestSt.FND_Display > 9)
			{
				m_McuTestSt.FND_Display = 0;
			}

			s_Timer = m_pgmEnv.timer1ms;
		}
	}
}

void RS232_Test_Proc(INT08U* s_InitFlag)
{
	static INT08U s_Test_Flag;

	if (*s_InitFlag == 0)
	{
		*s_InitFlag = 1;

		m_McuTestSt.RS232_Enable = 0;
		m_McuTestSt.RS232_RecvCnt = 0;

		s_Test_Flag = 0;
	}
	else
	{
		if (s_Test_Flag != m_McuTestCtr.RS232_Test)
		{
			s_Test_Flag = m_McuTestCtr.RS232_Test;

			if (s_Test_Flag == 1)
			{
				// 0 -> 1
				m_McuTestSt.RS232_Enable = 1;
				m_McuTestSt.RS232_RecvCnt = 0;
			}
			else
			{
				// 1 -> 0
				m_McuTestSt.RS232_Enable = 0;
			}
		}
	}
}

void RS485_Test1_Proc(INT08U* s_InitFlag)
{
	static INT08U s_Test_Flag;

	if (*s_InitFlag == 0)
	{
		*s_InitFlag = 1;

		m_McuTestSt.RS485_P1_Enable = 0;
		m_McuTestSt.RS485_P1_RecvCnt = 0;

		s_Test_Flag = 0;
	}
	else
	{
		if (s_Test_Flag != m_McuTestCtr.RS485_Test1)
		{
			s_Test_Flag = m_McuTestCtr.RS485_Test1;

			if (s_Test_Flag == 1)
			{
				// 0 -> 1
				if ((m_McuTestCtr.RS485_Test2 == 0) \
					&& (m_McuTestCtr.RS422_Test1 == 0) \
					&& (m_McuTestCtr.RS422_Test2 == 0))
				{
					m_McuTestSt.RS485_P1_Enable = 1;
					m_McuTestSt.RS485_P1_RecvCnt = 0;
					Set_RS485_422_Mode(0);
				}
			}
			else
			{
				// 1 -> 0
				m_McuTestSt.RS485_P1_Enable = 0;
			}
		}
	}
}

void RS485_Test2_Proc(INT08U* s_InitFlag)
{
	static INT08U s_Test_Flag;

	if (*s_InitFlag == 0)
	{
		*s_InitFlag = 1;

		m_McuTestSt.RS485_P2_Enable = 0;
		m_McuTestSt.RS485_P2_RecvCnt = 0;

		s_Test_Flag = 0;
	}
	else
	{
		if (s_Test_Flag != m_McuTestCtr.RS485_Test2)
		{
			s_Test_Flag = m_McuTestCtr.RS485_Test2;

			if (s_Test_Flag == 1)
			{
				// 0 -> 1
				if ((m_McuTestCtr.RS485_Test1 == 0) \
					&& (m_McuTestCtr.RS422_Test1 == 0) \
					&& (m_McuTestCtr.RS422_Test2 == 0))
				{
					m_McuTestSt.RS485_P2_Enable = 1;
					m_McuTestSt.RS485_P2_RecvCnt = 0;
					Set_RS485_422_Mode(0);
				}
			}
			else
			{
				// 1 -> 0
				m_McuTestSt.RS485_P2_Enable = 0;
			}
		}
	}
}

void RS422_Test1_Proc(INT08U* s_InitFlag)
{
	static INT08U s_Test_Flag;

	if (*s_InitFlag == 0)
	{
		*s_InitFlag = 1;

		m_McuTestSt.RS422_P1_Enable = 0;
		m_McuTestSt.RS422_P1_RecvCnt = 0;

		s_Test_Flag = 0;
	}
	else
	{
		if (s_Test_Flag != m_McuTestCtr.RS422_Test1)
		{
			s_Test_Flag = m_McuTestCtr.RS422_Test1;

			if (s_Test_Flag == 1)
			{
				// 0 -> 1
				if ((m_McuTestCtr.RS485_Test1 == 0) \
					&& (m_McuTestCtr.RS485_Test2 == 0) \
					&& (m_McuTestCtr.RS422_Test2 == 0))
				{
					m_McuTestSt.RS422_P1_Enable = 1;
					m_McuTestSt.RS422_P1_RecvCnt = 0;
					Set_RS485_422_Mode(1);
				}
			}
			else
			{
				// 1 -> 0
				m_McuTestSt.RS422_P1_Enable = 0;
			}
		}
	}
}

void RS422_Test2_Proc(INT08U* s_InitFlag)
{
	static INT08U s_Test_Flag;

	if (*s_InitFlag == 0)
	{
		*s_InitFlag = 1;

		m_McuTestSt.RS422_P2_Enable = 0;
		m_McuTestSt.RS422_P2_RecvCnt = 0;

		s_Test_Flag = 0;
	}
	else
	{
		if (s_Test_Flag != m_McuTestCtr.RS422_Test2)
		{
			s_Test_Flag = m_McuTestCtr.RS422_Test2;

			if (s_Test_Flag == 1)
			{
				// 0 -> 1
				if ((m_McuTestCtr.RS485_Test1 == 0) \
					&& (m_McuTestCtr.RS485_Test2 == 0) \
					&& (m_McuTestCtr.RS422_Test1 == 0))
				{
					m_McuTestSt.RS422_P2_Enable = 1;
					m_McuTestSt.RS422_P2_RecvCnt = 0;
					Set_RS485_422_Mode(1);
				}
			}
			else
			{
				// 1 -> 0
				m_McuTestSt.RS422_P2_Enable = 0;
			}
		}
	}
}

void Ethernet1_Test_Proc(INT08U* s_InitFlag)
{
	static INT08U s_Test_Flag;

	if (*s_InitFlag == 0)
	{
		*s_InitFlag = 1;

		m_McuTestSt.EtherNet1_Enable = 0;
		m_McuTestSt.EtherNet1_RecvCnt = 0;

		s_Test_Flag = 0;
	}
	else
	{
		if (s_Test_Flag != m_McuTestCtr.EtherNet_Test1)
		{
			s_Test_Flag = m_McuTestCtr.EtherNet_Test1;

			if (s_Test_Flag == 1)
			{
				// 0 -> 1
				m_McuTestSt.EtherNet1_Enable = 1;
				m_McuTestSt.EtherNet1_RecvCnt = 0;
			}
			else
			{
				// 1 -> 0
				m_McuTestSt.EtherNet1_Enable = 0;
			}
		}
	}
}

void Ethernet2_Test_Proc(INT08U* s_InitFlag)
{
	static INT08U s_Test_Flag;

	if (*s_InitFlag == 0)
	{
		*s_InitFlag = 1;

		m_McuTestSt.EtherNet2_Enable = 0;
		m_McuTestSt.EtherNet2_RecvCnt = 0;

		s_Test_Flag = 0;
	}
	else
	{
		if (s_Test_Flag != m_McuTestCtr.EtherNet_Test2)
		{
			s_Test_Flag = m_McuTestCtr.EtherNet_Test2;

			if (s_Test_Flag == 1)
			{
				// 0 -> 1
				m_McuTestSt.EtherNet2_Enable = 1;
				m_McuTestSt.EtherNet2_RecvCnt = 0;
			}
			else
			{
				// 1 -> 0
				m_McuTestSt.EtherNet2_Enable = 0;
			}
		}
	}
}

void CAN1_Test_Proc(INT08U* s_InitFlag)
{
	static INT08U s_Test_Flag;

	if (*s_InitFlag == 0)
	{
		*s_InitFlag = 1;

		m_McuTestSt.CAN1_Enable = 0;
		m_McuTestSt.CAN1_RecvCnt = 0;

		s_Test_Flag = 0;
	}
	else
	{
		if (s_Test_Flag != m_McuTestCtr.CAN_Test1)
		{
			s_Test_Flag = m_McuTestCtr.CAN_Test1;

			if (s_Test_Flag == 1)
			{
				// 0 -> 1
				m_McuTestSt.CAN1_Enable = 1;
				m_McuTestSt.CAN1_RecvCnt = 0;
				/*
				if (m_McuTestSt.CAN2_Enable == 0)
				{
					m_McuTestSt.CAN1_Enable = 1;
					m_McuTestSt.CAN1_RecvCnt = 0;
				}
				*/
			}
			else
			{
				// 1 -> 0
				m_McuTestSt.CAN1_Enable = 0;
				memset((INT08U*)&m_McuTestSt.CAN1_Data, 0, sizeof(CanRecvData));
			}
		}
	}
}

void CAN2_Test_Proc(INT08U* s_InitFlag)
{
	static INT08U s_Test_Flag;

	if (*s_InitFlag == 0)
	{
		*s_InitFlag = 1;

		m_McuTestSt.CAN2_Enable = 0;
		m_McuTestSt.CAN2_RecvCnt = 0;

		s_Test_Flag = 0;
	}
	else
	{
		if (s_Test_Flag != m_McuTestCtr.CAN_Test2)
		{
			s_Test_Flag = m_McuTestCtr.CAN_Test2;

			if (s_Test_Flag == 1)
			{
				// 0 -> 1
				m_McuTestSt.CAN2_Enable = 1;
				m_McuTestSt.CAN2_RecvCnt = 0;
				/*
				if (m_McuTestSt.CAN1_Enable == 0)
				{
					m_McuTestSt.CAN2_Enable = 1;
					m_McuTestSt.CAN2_RecvCnt = 0;
				}
				*/
			}
			else
			{
				// 1 -> 0
				m_McuTestSt.CAN2_Enable = 0;
				memset((INT08U*)&m_McuTestSt.CAN2_Data, 0, sizeof(CanRecvData));
			}
		}
	}
}

void SSI_Test_Proc(INT08U* s_InitFlag)
{
	static INT08U s_Test_Flag;

	static INT08U s_SSI_run_mode = 0;
	static INT32U s_chkTimer = 0;
	static INT08U s_errcnt = 0;
	static INT32S s_Now_pos;
	INT08U nSSI_status = 0;
	INT32U nGray_code_pos = 0;
	INT08U nError = 0;
	INT32U nInterval = 100;

	INT32U nSPI_Divider = 200;

	if (*s_InitFlag == 0)
	{
		*s_InitFlag = 1;

		m_McuTestSt.SSI_Enable = 0;
		m_McuTestSt.SSI_Position = 0;

		s_Test_Flag = 0;

		s_SSI_run_mode = 0;
	}
	else
	{
		if (s_Test_Flag != m_McuTestCtr.SSI_Test)
		{
			s_Test_Flag = m_McuTestCtr.SSI_Test;

			if (s_Test_Flag == 1)
			{
				// 0 -> 1
				m_McuTestSt.SSI_Position = 0;
				m_McuTestSt.SSI_Enable = 1;

				s_chkTimer = m_pgmEnv.timer100us;
				s_SSI_run_mode = 1;
			}
			else
			{
				// 1 -> 0
				m_McuTestSt.SSI_Enable = 0;
				s_SSI_run_mode = 0;	// Stop
			}
		}
	}

	m_McuTestSt.SSI_Freq_Set = m_McuTestCtr.SSI_Freq_Cmd;

	switch (s_SSI_run_mode)
	{
	case 0:
		break;

	case 1:
		if (getCalcTimer100us(s_chkTimer) >= 100)
		{
			if (m_McuTestCtr.SSI_Freq_Cmd)
			{
				nSPI_Divider = (INT16U)(10000000 / ((INT32U)m_McuTestCtr.SSI_Freq_Cmd * 2000));	// 1: 10Khz
			}
			else
			{
				nSPI_Divider = 200;
			}
			//m_TestStatus.St[DEBUG_STR_21] = nSPI_Divider;
			set_FPGA_SSI_Clk(nSPI_Divider);
			//m_TestStatus.St[DEBUG_STR_22] = get_FPGA_SSI_Clk();

			set_FPGA_SSI_Send_Bit(25);	// Bit 0 ~ 24, Total : 25 bit

			//s_initTimer = m_pgmEnv.timer100us;
			s_chkTimer = m_pgmEnv.timer100us;
			s_SSI_run_mode = 2;
		}
		break;

	case 2:
		set_FPGA_SSI_Send_Cmd(1);
		s_chkTimer = m_pgmEnv.timer100us;
		s_SSI_run_mode = 3;
		break;

	case 3:
		if (getCalcTimer100us(s_chkTimer) >= nInterval)
		{
			nError = 0;
			nSSI_status = get_FPGA_SSI_Status();

			//m_TestStatus.St[DEBUG_STR_23] = nSSI_status;
			if (nSSI_status)
			{
				nError = 4;
			}
			else
			{
				nGray_code_pos = get_FPGA_SSI_Read_Data();
				if (nGray_code_pos & 0x00000001)  nError = nGray_code_pos >> 3;
				
				//m_TestStatus.St[DEBUG_STR_24] = nGray_code_pos;
				//m_TestStatus.St[DEBUG_STR_25] = nError;
			}

			if (nError)
			{
				if (++s_errcnt >= 10)
				{
					s_errcnt = 10;
				}

				if (++m_pgmEnv.BarcodeContinueError > 1000)
				{
					m_pgmEnv.BarcodeContinueError = 1000;
					m_McuTestSt.SSI_Position = 0xFFFFFFFF;			
					//m_TestStatus.St[DEBUG_STR_21] = nSPI_Divider;
				}
			}
			else
			{
				s_errcnt = 0;
				m_pgmEnv.TravSSIError = 0;

				s_Now_pos = conv_Graycode_TravPosition(nGray_code_pos);

				m_McuTestSt.SSI_Position = s_Now_pos;
				m_pgmEnv.BarcodeContinueError = 0;
			}


			s_chkTimer = m_pgmEnv.timer100us;
			s_SSI_run_mode = 4;
		}
		break;

	case 4:
		if (getCalcTimer100us(s_chkTimer) >= nInterval)
		{
			s_chkTimer = m_pgmEnv.timer100us;
			s_SSI_run_mode = 2;
		}
		break;
	}
}

void Encoder_Test_Proc(INT08U* s_InitFlag)
{
	static INT08U s_Test_Flag;

	if (*s_InitFlag == 0)
	{
		*s_InitFlag = 1;
		m_McuTestSt.Encoder_Enable = 0;
		m_McuTestSt.Encoder_In = 0;

		s_Test_Flag = 0;
	}
	else
	{
		if (s_Test_Flag != m_McuTestCtr.Encoder_Test)
		{
			s_Test_Flag = m_McuTestCtr.Encoder_Test;

			if (s_Test_Flag == 1)
			{
				// 0 -> 1
				HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
				__HAL_TIM_SET_COUNTER(&htim2, DEF_ENC_PRESET);
				//__HAL_TIM_SET_COUNTER(&htim2, 0);
				//__HAL_TIM_SET_COUNTER(&htim2, 32767);

				m_McuTestSt.Encoder_Enable = 1;
				m_McuTestSt.Encoder_In = 0;
			}
			else
			{
				// 1 -> 0
				HAL_TIM_Encoder_Stop(&htim2, TIM_CHANNEL_ALL);

				m_McuTestSt.Encoder_Enable = 0;
			}
		}
	}

	if (m_McuTestSt.Encoder_Enable)
	{
		m_McuTestSt.Encoder_In = GetEncoderCounter();
	}

	//m_TestStatus.St[DEBUG_STR_25] = __HAL_TIM_GET_COUNTER(&htim2);
}

void EtherCAT_Test_Proc(INT08U* s_InitFlag)
{
	static INT08U s_Test_Flag;

	if (*s_InitFlag == 0)
	{
		*s_InitFlag = 1;
		m_McuTestSt.EtherCAT_Enable = 0;
		m_McuTestSt.EtherCAT_Test = 0;

		s_Test_Flag = 0;
	}
	else
	{
		if (s_Test_Flag != m_McuTestCtr.EtherCAT_Test)
		{
			s_Test_Flag = m_McuTestCtr.EtherCAT_Test;

			if (s_Test_Flag == 1)
			{
				// 0 -> 1
				m_McuTestSt.EtherCAT_Enable = 1;
			}
			else
			{
				// 1 -> 0
				m_McuTestSt.EtherCAT_Enable = 0;
				m_McuTestSt.EtherCAT_Test = 0;
				m_McuTestSt.EtherCAT_Wkc = 0;
			}
		}
	}

	ECAT_TestManager(m_McuTestSt.EtherCAT_Enable, &m_McuTestSt.EtherCAT_Test, &m_McuTestSt.EtherCAT_Wkc);

	/*
	m_McuTestSt.EtherCAT_Wkc = EthercatTestManager(m_McuTestSt.EtherCAT_Enable);
	if (m_McuTestSt.EtherCAT_Enable)
	{
		if (m_McuTestSt.EtherCAT_Wkc == 2)
		{
			m_McuTestSt.EtherCAT_Test = 2;
		}
	}
	*/
}

void PTO_Test_Proc(INT08U* s_InitFlag)
{
	static INT08U s_Test_Pto_Output;
	static INT32U s_Update_Timer;

	if (*s_InitFlag == 0)
	{
		*s_InitFlag = 1;

		m_McuTestSt.PTO_Enable = 0;

		m_McuTestCtr.PTO_Output = 0;
		m_McuTestSt.PTO_Output = m_McuTestCtr.PTO_Output;

		s_Test_Pto_Output = 0;

		set_FPGA_PTO_Pulse_Freq(s_Test_Pto_Output);
	}
	else
	{
		if (s_Test_Pto_Output != m_McuTestCtr.PTO_Output)
		{
			s_Test_Pto_Output = m_McuTestCtr.PTO_Output;

			if (m_pgmEnv.isFpgaRun)
			{
				if (getCalcTimer1ms(s_Update_Timer) > 100)
				{
					set_FPGA_PTO_Pulse_Freq(m_McuTestCtr.PTO_Output);

					m_McuTestSt.PTO_Output = m_McuTestCtr.PTO_Output;

					s_Update_Timer = m_pgmEnv.timer1ms;
				}
			}
		}
	}

	
}

void DIO_Test_Proc(INT08U* s_InitFlag)
{
	static INT08U s_Test_Flag;
	INT08U i = 0;

	if (*s_InitFlag == 0)
	{
		*s_InitFlag = 1;

		m_McuTestSt.DIO_Test_Enable = 0;

		s_Test_Flag = 0;
	}
	else
	{
		if (s_Test_Flag != m_McuTestCtr.DIO_Test)
		{
			s_Test_Flag = m_McuTestCtr.DIO_Test;

			if (s_Test_Flag == 1)
			{
				// 0 -> 1
				m_McuTestSt.DIO_Test_Enable = 1;
			}
			else
			{
				// 1 -> 0
				m_McuTestSt.DIO_Test_Enable = 0;
			}
		}
	}

	if (m_McuTestSt.DIO_Test_Enable)
	{
		for (i = 0; i < 8; i++)
		{
			if (m_pgmEnv.DISt & cbits[i])
			{
				MCU_Output_Control(i, 1);
			}
			else
			{
				MCU_Output_Control(i, 0);
			}
		}

		m_McuTestSt.DISt = m_pgmEnv.DISt;
		m_McuTestSt.DOSt = m_pgmEnv.DOSt;
	}
}

void USB_Mem_Test_Proc(INT08U* s_InitFlag)
{
	static INT08U s_Test_Flag;

	if (*s_InitFlag == 0)
	{
		*s_InitFlag = 1;
		s_Test_Flag = 0;
	}
	else
	{
		if (s_Test_Flag != m_McuTestCtr.USB_Test)
		{
			s_Test_Flag = m_McuTestCtr.USB_Test;
			if (s_Test_Flag == 1)
			{
				// 0 -> 1
			}
			else
			{
				// 1 -> 0
			}
		}
	}

	m_McuTestSt.USB_Test_Enable = s_Test_Flag;
	m_McuTestSt.USB_Test = USB_Test_Proc_1(s_Test_Flag);
}

void SampleCode_Test_Proc(INT08U* s_InitFlag)
{
	static INT08U s_Test_Flag;

	if (*s_InitFlag == 0)
	{
		*s_InitFlag = 1;
		m_McuTestSt.EtherNet1_RecvCnt = 0;

		s_Test_Flag = 0;
	}
	else
	{
		if (s_Test_Flag != m_McuTestCtr.EtherNet_Test1)
		{
			s_Test_Flag = m_McuTestCtr.EtherNet_Test1;

			if (s_Test_Flag == 1)
			{
				// 0 -> 1
				m_McuTestSt.EtherNet1_RecvCnt = 0;
			}
			else
			{
				// 1 -> 0
			}
		}
	}
}

void MCU_Test_Manager(void)
{
	static INT08U s_HwInit = 0;
	static McuTestStSTR s_TestFlag;

	if (!m_pgmEnv.MCU_Test_Mode)
	{
		return;
	}
	else
	{
		if (s_HwInit == 0)
		{
			s_HwInit = 1;
		}
		else
		{
			//Encoder_Manager();
			HMI_Com_Manager();
		
			if (!m_pgmEnv.PortLinkSt[rsMCU_DEBUG_Port])
			{
				memset((INT08U*)&m_McuTestCtr, 0, sizeof(McuTestCtrSTR));

				if (s_TestFlag.Encoder_Enable)
				{
					s_TestFlag.Encoder_Enable = 0;
					Encoder_Test_Proc(&s_TestFlag.Encoder_Enable);
				}

				if (s_TestFlag.PTO_Enable)
				{

					s_TestFlag.PTO_Enable = 0;
					PTO_Test_Proc(&s_TestFlag.PTO_Enable);
				}

				m_pgmEnv.MCU_Test_Mode = 0;
				memset((INT08U*)&s_TestFlag, 0, sizeof(McuTestStSTR));

				//memset((INT08U*)&m_McuTestSt, 0, sizeof(McuTestStSTR));
			}
			else
			{
				Update_Mcu_Test_Status();

				Test_MCU_Test_Control();	// Mcu Test 제어 테스트 코드. 기능 구현 후 주석 처리.

				FND_Test_Proc(&s_TestFlag.FND_Display);

				RS232_Test_Proc(&s_TestFlag.RS232_Enable);

				RS485_Test1_Proc(&s_TestFlag.RS485_P1_Enable);
				RS485_Test2_Proc(&s_TestFlag.RS485_P2_Enable);
				RS422_Test1_Proc(&s_TestFlag.RS422_P1_Enable);
				RS422_Test2_Proc(&s_TestFlag.RS422_P2_Enable);

				CAN1_Test_Proc(&s_TestFlag.CAN1_Enable);
				CAN2_Test_Proc(&s_TestFlag.CAN2_Enable);

				Ethernet1_Test_Proc(&s_TestFlag.EtherNet1_Enable);
				Ethernet2_Test_Proc(&s_TestFlag.EtherNet2_Enable);

				EtherCAT_Test_Proc(&s_TestFlag.EtherCAT_Enable);

				SSI_Test_Proc(&s_TestFlag.SSI_Enable);

				Encoder_Test_Proc(&s_TestFlag.Encoder_Enable);

				PTO_Test_Proc(&s_TestFlag.PTO_Enable);

				DIO_Test_Proc(&s_TestFlag.DIO_Test_Enable);

				USB_Mem_Test_Proc(&s_TestFlag.USB_Test_Enable);
			}
		}
	}
}
