/**
  ******************************************************************************
  * @file            : usb_user.c
  * @author          :
  * @version         :
  * @brief           : This file implements USB Memory
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

#include "main.h"
#include "fatfs.h"
#include "usb_host.h"
#include "usb_user.h"

#include "type.h"
#include "alarm.h"

extern ApplicationTypeDef Appli_state;


enum enumSEQ_STEP {
	SEQ_STAND_BY = 0,
	SEQ_STEP_0,
	SEQ_STEP_0_1,
	SEQ_STEP_0_2,
	SEQ_STEP_0_3,
	SEQ_STEP_1,
	SEQ_STEP_2,
	SEQ_STEP_3,
	SEQ_STEP_4,
	SEQ_STEP_5,
	SEQ_STEP_6,
	SEQ_STEP_7,
	SEQ_STEP_8,
	SEQ_STEP_9,
	SEQ_STEP_10,
	SEQ_STEP_11,
	SEQ_STEP_12,
	SEQ_STEP_13,
	SEQ_STEP_14,
	SEQ_STEP_15,
};

FILINFO fno;
FRESULT fresult;  // result
UINT br, bw;  // File read/write count

/**** capacity related *****/
FATFS* pfs;
DWORD fre_clust;
uint32_t total, free_space;


void OpenFile()
{
	FRESULT res = f_open(&USBHFile, "hello.txt", FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
	if (res != FR_OK) Error_Handler();
}

void CloseFile()
{
	FRESULT res = f_close(&USBHFile);
	if (res != FR_OK) Error_Handler();
}

uint32_t ReadFile(uint8_t* buff, uint16_t len)
{
	uint32_t bytesRead;

	memset(buff, 0, len);
	FRESULT res = f_read(&USBHFile, buff, len, (void*)&bytesRead);
	if (res != FR_OK) Error_Handler();

	return bytesRead;
}

uint32_t WriteFile(uint8_t* buff, uint16_t len)
{
	uint32_t bytesWritten;

	FRESULT res;
	res = f_lseek(&USBHFile, f_size(&USBHFile));
	if (res != FR_OK) Error_Handler();

	res = f_write(&USBHFile, buff, len, (void*)&bytesWritten);
	if (res != FR_OK) Error_Handler();

	return bytesWritten;
}


/**
   * @brief USB Test code, File Read, Write
   * @param  None
   * @retval None
   */
void USB_Test_Proc(void)
{
	//const char FileName[] = "Test.txt";
	//const char FileName[] = "1:Test.txt";
	const char FileName[] = "Test.txt";
	char FilePath[20];
	char* msg = "Hello! STM32 Mass Storage Testing...\r\n";

	//static INT32U s_Size;
	static INT32U s_SrcSize;		// Read Source Buffer size

	FRESULT res;
	static INT32U s_Timer;
	static INT08U s_Step;
	static INT16U s_ErrCnt;

	INT08U nRetryCnt = 10;

	INT32U nWritten = 0, nRead = 0;

	switch (s_Step)
	{
	case SEQ_STAND_BY:
		if (Appli_state == APPLICATION_READY)
		{
#if DEBUG_FILE_MEM_MSG
			printf("[USB]Start Test.\r\n");
#endif
			s_ErrCnt = 0;

			SetTimer1ms(&s_Timer);
			s_Step = SEQ_STEP_0;
		}
		break;

	case SEQ_STEP_0:
		if (getCalcTimer1ms(s_Timer) > 50)
		{
			res = f_mount(&USBHFatFS, (TCHAR const*)USBHPath, 0);

			if (res == FR_OK)
			{
#if DEBUG_FILE_MEM_MSG
				printf("[FATFS]Mount path:%s\r\n", USBHPath);
#endif
				s_ErrCnt = 0;

				SetTimer1ms(&s_Timer);
				s_Step = SEQ_STEP_1;
			}
			else
			{
#if DEBUG_FILE_MEM_MSG
				printf("[FATFS]f_mount path:%s res : %d\r\n", USBHPath, res);
#endif
				if (s_ErrCnt > nRetryCnt)
				{
					//Event Error
					s_Step = SEQ_STEP_12;
				}
				else
				{
					++s_ErrCnt;
					SetTimer1ms(&s_Timer);
				}
			}
		}
		break;

	case SEQ_STEP_1:
		if (getCalcTimer1ms(s_Timer) > 50)
		{
			strcpy(FilePath, USBHPath);
			strcat(FilePath, FileName);

			//res = f_open(&USBHFile, FileName, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
			res = f_open(&USBHFile, FilePath, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);

			if (res == FR_OK)
			{
				s_ErrCnt = 0;
				s_SrcSize = f_size(&USBHFile);
#if DEBUG_FILE_MEM_MSG
				printf("[FATFS]File Open [%s] Size:%ld\r\n", FilePath, s_SrcSize);
#endif
				SetTimer1ms(&s_Timer);

				s_Step = SEQ_STEP_2;
			}
			else
			{
#if DEBUG_FILE_MEM_MSG
				printf("[FATFS]f_open [%s] res : %d\r\n", FilePath, res);
#endif
				if (s_ErrCnt > nRetryCnt)
				{
					//Event Error
					s_Step = SEQ_STEP_12;
				}
				else
				{
					++s_ErrCnt;
					SetTimer1ms(&s_Timer);
				}
			}
		}
		break;

	case SEQ_STEP_2:
		nWritten = WriteFile((INT08U*)msg, strlen(msg));

#if DEBUG_FILE_MEM_MSG
		printf("%lu bytes written\r\n", nWritten);
#endif
		SetTimer1ms(&s_Timer);
		s_Step = SEQ_STEP_3;
		break;

	case SEQ_STEP_3:
		if (getCalcTimer1ms(s_Timer) > 50)
		{
			f_close(&USBHFile);
#if DEBUG_FILE_MEM_MSG
			printf("[FATFS]Close File [%s]\r\n", FileName);
#endif
			res = f_mount(NULL, (TCHAR const*)USBHPath, 0);
#if DEBUG_FILE_MEM_MSG
			printf("[FATFS]f_unmount res : %d\r\n", res);

			printf("[USB] Test Complete.\r\n");
#endif

	 		s_Step = SEQ_STEP_4;
		}
		break;

	case SEQ_STEP_4:
		if (Appli_state == APPLICATION_DISCONNECT)
		{
#if DEBUG_FILE_MEM_MSG
			printf("[USB] Disconnect.\r\n");
#endif
			SetTimer1ms(&s_Timer);
			s_Step = SEQ_STEP_5;
		}
		break;

	case SEQ_STEP_5:
		if (getCalcTimer1ms(s_Timer) > 1000)
		{
			s_Step = SEQ_STAND_BY;
		}
		break;

	case SEQ_STEP_12:
		if (getCalcTimer1ms(s_Timer) > 50)
		{
			f_close(&USBHFile);
#if DEBUG_FILE_MEM_MSG
			printf("[FATFS]Close File [%s]\r\n", FileName);
			HAL_Delay(10);
#endif
			res = f_mount(NULL, (TCHAR const*)USBHPath, 0);
#if DEBUG_FILE_MEM_MSG
			printf("[FATFS]f_unmount res : %d\r\n", res);
#endif
			s_Step = SEQ_STEP_4;
		}
		break;
	}
}

/**
   * @brief USB Test code, File Read, Write
   * @param  None
   * @retval None
   */
INT08U USB_Test_Proc_1(INT08U nEnable)
{
	//const char FileName[] = "Test.txt";
	//const char FileName[] = "1:Test.txt";
	const char FileName[] = "Test.txt";
	char FilePath[20];
	char* msg = "Hello! STM32 Mass Storage Testing...\r\n";

	//static INT32U s_Size;
	static INT32U s_SrcSize;		// Read Source Buffer size

	FRESULT res;
	static INT32U s_Timer;
	static INT08U s_Step;
	static INT16U s_ErrCnt;

	INT08U nRetryCnt = 10;

	INT32U nWritten = 0, nRead = 0;

	static INT08U s_TestResult = 0;

	switch (s_Step)
	{
	case SEQ_STAND_BY:
		s_TestResult = 0;

		if (Appli_state == APPLICATION_READY)
		{
			if (nEnable)
			{
#if DEBUG_FILE_MEM_MSG
				printf("[USB]Start Test.\r\n");
#endif
				s_ErrCnt = 0;

				SetTimer1ms(&s_Timer);
				s_Step = SEQ_STEP_0;
			}
		}
		break;

	case SEQ_STEP_0:
		if (getCalcTimer1ms(s_Timer) > 50)
		{
			s_TestResult = 1;
			res = f_mount(&USBHFatFS, (TCHAR const*)USBHPath, 0);

			if (res == FR_OK)
			{
#if DEBUG_FILE_MEM_MSG
				printf("[FATFS]Mount path:%s\r\n", USBHPath);
#endif
				s_ErrCnt = 0;

				s_TestResult = 1;

				SetTimer1ms(&s_Timer);
				s_Step = SEQ_STEP_1;
			}
			else
			{
#if DEBUG_FILE_MEM_MSG
				printf("[FATFS]f_mount path:%s res : %d\r\n", USBHPath, res);
#endif
				if (s_ErrCnt > nRetryCnt)
				{
					//Event Error
					s_Step = SEQ_STEP_12;
				}
				else
				{
					++s_ErrCnt;
					SetTimer1ms(&s_Timer);
				}
			}
		}
		break;

	case SEQ_STEP_1:
		if (getCalcTimer1ms(s_Timer) > 50)
		{
			strcpy(FilePath, USBHPath);
			strcat(FilePath, FileName);

			//res = f_open(&USBHFile, FileName, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
			res = f_open(&USBHFile, FilePath, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);

			if (res == FR_OK)
			{
				s_ErrCnt = 0;
				s_SrcSize = f_size(&USBHFile);
#if DEBUG_FILE_MEM_MSG
				printf("[FATFS]File Open [%s] Size:%ld\r\n", FilePath, s_SrcSize);
#endif
				SetTimer1ms(&s_Timer);

				s_Step = SEQ_STEP_2;
			}
			else
			{
#if DEBUG_FILE_MEM_MSG
				printf("[FATFS]f_open [%s] res : %d\r\n", FilePath, res);
#endif
				if (s_ErrCnt > nRetryCnt)
				{
					//Event Error
					s_Step = SEQ_STEP_12;
				}
				else
				{
					++s_ErrCnt;
					SetTimer1ms(&s_Timer);
				}
			}
		}
		break;

	case SEQ_STEP_2:
		nWritten = WriteFile((INT08U*)msg, strlen(msg));

#if DEBUG_FILE_MEM_MSG
		printf("%lu bytes written\r\n", nWritten);
#endif
		SetTimer1ms(&s_Timer);
		s_Step = SEQ_STEP_3;
		break;

	case SEQ_STEP_3:
		if (getCalcTimer1ms(s_Timer) > 50)
		{
			f_close(&USBHFile);
#if DEBUG_FILE_MEM_MSG
			printf("[FATFS]Close File [%s]\r\n", FileName);
#endif
			res = f_mount(NULL, (TCHAR const*)USBHPath, 0);
#if DEBUG_FILE_MEM_MSG
			printf("[FATFS]f_unmount res : %d\r\n", res);

			printf("[USB] Test Complete.\r\n");
#endif
			s_TestResult = 2;

			s_Step = SEQ_STEP_4;
		}
		break;

	case SEQ_STEP_4:
		if ((Appli_state == APPLICATION_DISCONNECT) || (nEnable == 0))
		{
#if DEBUG_FILE_MEM_MSG
			printf("[USB] Disconnect.\r\n");
#endif
			SetTimer1ms(&s_Timer);
			s_Step = SEQ_STEP_5;
		}
		break;

	case SEQ_STEP_5:
		if (getCalcTimer1ms(s_Timer) > 1000)
		{
			s_Step = SEQ_STAND_BY;
		}
		break;

	case SEQ_STEP_12:
		if (getCalcTimer1ms(s_Timer) > 50)
		{
			s_TestResult = 3;

			f_close(&USBHFile);
#if DEBUG_FILE_MEM_MSG
			printf("[FATFS]Close File [%s]\r\n", FileName);
			HAL_Delay(10);
#endif
			res = f_mount(NULL, (TCHAR const*)USBHPath, 0);
#if DEBUG_FILE_MEM_MSG
			printf("[FATFS]f_unmount res : %d\r\n", res);
#endif
			s_Step = SEQ_STEP_4;
		}
		break;
	}

	return s_TestResult;
}

/**
   * @brief
   * @param  None
   * @retval None
   */
void User_MSC_Proc(void)
{
	USB_Test_Proc();
}