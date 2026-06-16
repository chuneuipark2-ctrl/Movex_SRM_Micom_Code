/**
  ******************************************************************************
  * @file            : upgrade.c
  * @version         :
  * @author          :
  * @brief           : This file implements FW Update.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

#include "main.h"
#include "alarm.h"
#include "upgrade.h"
#include "uart.h"
#include "com_tml.h"
#include "flash.h"
#include "com_udp.h"
#include "tcpipstack.h"

#include "FlashSST26.h"

typedef  void(*pJumpFunction)(void);    // 지정된 어드레스로 JUMP 하는 코드 생성.

// vu32  => volatile INT32U

pJumpFunction JumpCode;
INT32U        JumpAddress, StackAddress;
INT32U        StartAddress, EndAddress;

void jumpDownCode(void) // upgradeJumpAppl
{
	StartAddress = DOWN_PGM_IN_FLASH_START_SECTOR_ADDR;
	EndAddress = DOWN_PGM_IN_FLASH_END_SECTOR_ADDR;

	StackAddress = *(volatile INT32U*)(StartAddress + 0);
	JumpAddress = *(volatile INT32U*)(StartAddress + 4);
	if ((JumpAddress >= StartAddress) && (JumpAddress <= EndAddress))
	{
		if ((StackAddress & 0xFFF00000) == 0x20000000)
		{
			JumpCode = (pJumpFunction)JumpAddress;
			__set_MSP(*(volatile INT32U*)StartAddress);
			JumpCode();
		}
	}
}


#define APPLICATION_ADDRESS   DOWN_PGM_IN_FLASH_START_SECTOR_ADDR

typedef  void(*pFunction)(void);

pFunction JumpToApplication;
uint32_t JumpAddress;

void jumpApplication(void) // upgradeJumpAppl
{
	// Test if user code is programmed starting from address "APPLICATION_ADDRESS" 
	if (((*(__IO uint32_t*)APPLICATION_ADDRESS) & 0x2FFE0000) == 0x20000000)
	{
		NVIC->ICER[0] = 0xFFFFFFFF;
		NVIC->ICER[1] = 0xFFFFFFFF;
		NVIC->ICER[2] = 0xFFFFFFFF;
		NVIC->ICER[3] = 0xFFFFFFFF;
		NVIC->ICER[4] = 0xFFFFFFFF;
		NVIC->ICER[5] = 0xFFFFFFFF;
		NVIC->ICER[6] = 0xFFFFFFFF;
		NVIC->ICER[7] = 0xFFFFFFFF;

		SCB_DisableICache();
		SCB_DisableDCache();

		// Jump to user application 
		JumpAddress = *(__IO uint32_t*)(APPLICATION_ADDRESS + 4);
		JumpToApplication = (pFunction)JumpAddress;

		// Initialize user application's Stack Pointer 
		__set_MSP(*(__IO uint32_t*)APPLICATION_ADDRESS);
		JumpToApplication();
	}
}

INT08U checkFusingString(INT08U* s, INT08U* d, INT08U len)
{
	INT08U i = 0;

#if DEBUG_UPGRADE_MSG
	//printf("[UPGRADE] Check checkFusingString\r\n");
#endif

	for (i = 0; i < len; i++)
	{
#if DEBUG_UPGRADE_MSG
		//printf("[UPGRADE] s[%d] : %c / d[%d] : %c \r\n", i, s[i], i, d[i]);
#endif
		if (s[i] != d[i])  return 1;
	}

	return 0;
}

INT16U getStr2ShortValue(INT08U* str)
{
	INT16U result = 0;

	result |= ((INT16U)str[0]);
	result |= ((INT16U)str[1] << 8);

	return result;
}

INT32U getStr2LongValue(INT08U* str)
{
	INT32U result = 0;

	result |= ((INT32U)str[0]);
	result |= ((INT32U)str[1] << 8);
	result |= ((INT32U)str[2] << 16);
	result |= ((INT32U)str[3] << 24);

	return result;
}

#define PROJECT_CODE_POS     0x200

const INT08U project_rom_code[] __attribute__((section(".PROJECT_Rom_Code"))) = "PROJECT-20230405-MX_MCU_CONTROLLER-SRM";

const INT08U project_rom_boot_code[] = "PROJECT-20230405-MX_MCU_CONTROLLER-BOOT";
const INT08U project_rom_app_code[] = "PROJECT-20230405-MX_MCU_CONTROLLER-SRM";

INT08U checkDownloadCode(INT08U* d, INT08U mode)
{
	INT32U chk_mem[4] = { 0, };
	INT16U size = 0;
	INT08U project_code[64] = { 0, };
	INT08U nReturn = 0;

	chk_mem[0] = getStr2LongValue(&d[0x00]);
	chk_mem[1] = getStr2LongValue(&d[0x04]);
	chk_mem[2] = getStr2LongValue(&d[0x08]);
	chk_mem[3] = getStr2LongValue(&d[0x0C]);
	
	if ((chk_mem[0] & 0xFFF00000) != 0x20000000)  nReturn = 1;
	if ((chk_mem[1] & 0xFFC00000) != 0x08000000)  nReturn = 2;
	if ((chk_mem[2] & 0xFFC00000) != 0x08000000)  nReturn = 3;
	if ((chk_mem[3] & 0xFFC00000) != 0x08000000)  nReturn = 4;

	if (mode == 0)  // APP
	{
		size = sizeof(project_rom_app_code);
		if (size >= 7)
		{
			size -= 1;
			memcpy((INT08U*)project_code, (INT08U*)project_rom_app_code, size);
			if (checkFusingString((INT08U*)&d[PROJECT_CODE_POS], (INT08U*)project_code, size) != 0)  nReturn = 5;
		}
		else
		{
			nReturn = 6;
		}
	}
	else if (mode == 1)  // APP 타입무시
	{
		size = sizeof(project_rom_app_code);
		if (size >= 7)
		{
			size -= 1;
			memcpy((INT08U*)project_code, (INT08U*)project_rom_app_code, size);
			if (checkFusingString((INT08U*)&d[PROJECT_CODE_POS], (INT08U*)project_code, size) != 0)  nReturn = 5;
		}
		else
		{
			nReturn = 6;
		}
	}
	else if (mode == 2)
	{
		size = sizeof(project_rom_boot_code);
		if (size >= 7)
		{
			size -= 1;
			memcpy((INT08U*)project_code, (INT08U*)project_rom_boot_code, size);
			if (checkFusingString((INT08U*)&d[PROJECT_CODE_POS], (INT08U*)project_code, size) != 0)  nReturn = 5;
		}
		else
		{
			nReturn = 6;
		}
	}
	else
	{
		nReturn = 7;
	}
#if DEBUG_UPGRADE_MSG
	/*
	printf("[UPGRADE] Check Download code\r\n"); 
	printf("[UPGRADE] Chk_mem[0]:0x%08lx Chk_mem[1]:0x%08lx Chk_mem[2]:0x%08lx Chk_mem[3]:0x%08lx\r\n",
		chk_mem[0], chk_mem[1], chk_mem[2], chk_mem[3]);
	printf("[UPGRADE] Result : %d\r\n", nReturn);
	*/
#endif

	return nReturn;
}

INT08U checkDownloadCode_1(INT32U nRead_Addr, INT08U mode)
{
	INT32U chk_mem[4] = { 0, };
	INT16U size = 0;
	INT08U project_code[64] = { 0, };
	INT08U nReturn = 0;

	INT08U nReadBuffer[SIZE_PAGE] = { 0, };

	sst26_read(nRead_Addr, SIZE_PAGE, nReadBuffer);

	chk_mem[0] = getStr2LongValue(&nReadBuffer[0x00]);
	chk_mem[1] = getStr2LongValue(&nReadBuffer[0x04]);
	chk_mem[2] = getStr2LongValue(&nReadBuffer[0x08]);
	chk_mem[3] = getStr2LongValue(&nReadBuffer[0x0C]);

	if ((chk_mem[0] & 0xFFF00000) != 0x20000000)  nReturn = 1;
	if ((chk_mem[1] & 0xFFC00000) != 0x08000000)  nReturn = 2;
	if ((chk_mem[2] & 0xFFC00000) != 0x08000000)  nReturn = 3;
	if ((chk_mem[3] & 0xFFC00000) != 0x08000000)  nReturn = 4;

	sst26_read(nRead_Addr + PROJECT_CODE_POS, SIZE_PAGE, nReadBuffer);

	if (mode == 0)  // APP
	{
		size = sizeof(project_rom_app_code);
		if (size >= 7)
		{
			size -= 1;
			memcpy((INT08U*)project_code, (INT08U*)project_rom_app_code, size);
			if (checkFusingString((INT08U*)&nReadBuffer[0], (INT08U*)project_code, size) != 0)  nReturn = 5;
		}
		else
		{
			nReturn = 6;
		}
	}
	/*
	else if (mode == 1)  // APP 타입무시
	{
		size = sizeof(project_rom_app_code);
		if (size >= 7)
		{
			size -= 1;
			memcpy((INT08U*)project_code, (INT08U*)project_rom_app_code, size);
			if (checkFusingString((INT08U*)&nReadBuffer[PROJECT_CODE_POS], (INT08U*)project_code, size) != 0)  nReturn = 5;
		}
		else
		{
			nReturn = 6;
		}
	}
	*/
	else if (mode == 2)
	{
		size = sizeof(project_rom_boot_code);
		if (size >= 7)
		{
			size -= 1;
			memcpy((INT08U*)project_code, (INT08U*)project_rom_boot_code, size);
			if (checkFusingString((INT08U*)&nReadBuffer[0], (INT08U*)project_code, size) != 0)  nReturn = 5;
		}
		else
		{
			nReturn = 6;
		}
	}
	else
	{
		nReturn = 7;
	}
#if DEBUG_UPGRADE_MSG
	/*
	printf("[UPGRADE] Check Download code\r\n");
	printf("[UPGRADE] Chk_mem[0]:0x%08lx Chk_mem[1]:0x%08lx Chk_mem[2]:0x%08lx Chk_mem[3]:0x%08lx\r\n",
		chk_mem[0], chk_mem[1], chk_mem[2], chk_mem[3]);
	printf("[UPGRADE] Result : %d\r\n", nReturn);
	*/
#endif

	return nReturn;
}

const INT08U isDownloadRun = 0x01;

void initProgram(void)
{
	INT32U bootStartAddr = 0, bootEndAddr = 0;
	INT32U pgmStartAddr = 0, pgmSize = 0;
	//INT32U pgmInfoStartAddr = 0;
	INT32U addr = 0;
	INT16U calCrc = 0;

	addr = (INT32U)(&isDownloadRun);

	bootStartAddr = BOOT_PGM_IN_FLASH_START_SECTOR_ADDR;
	bootEndAddr = BOOT_PGM_IN_FLASH_END_SECTOR_ADDR;

#if DEBUG_MSG
	printf("[DEBUG_APP] bootStartAddr:0x%07lx, bootEndAddr:0x%07lx, isDownloadRun Addr:0x%07lx\n\r", \
		bootStartAddr, bootEndAddr, addr);
#endif

	if ((addr >= bootStartAddr) && (addr <= bootEndAddr))
	{
		// Boot Program Running
#if DEBUG_MSG
		printf("[DEBUG_APP] Boot Program Running. Run Stop. \n\r");
#endif
		while (1)
		{
			asm volatile("NOP");
		}
	}
	else
	{
		pgmStartAddr = DOWN_PGM_IN_FLASH_START_SECTOR_ADDR;
		pgmSize = DOWN_PGM_IN_FLASH_END_SECTOR_ADDR - DOWN_PGM_IN_FLASH_START_SECTOR_ADDR;

		ExtFlash_ReadData(EXT_DEVICE_SET_ADDR_START, (INT08U*)&m_ExtSEnv, sizeof(ExtFlashSEnv));
		memcpy((INT08U*)&m_pgmEnv.Fw_Info, (INT08U*)&m_ExtSEnv.FW_Info, sizeof(DownloadInfo_t));
		
		if (checkFusingString((INT08U*)m_pgmEnv.Fw_Info.APP_ExecFile.isFusing, (INT08U*)"Write App", 10) == 0)
		{
#if DEBUG_MSG
			char msg[50] = { 0, };

			printf("[DEBUG_APP] App ExecFile Information\n\r");
			sprintf(msg, "[DEBUG_APP] isFusion:%s\n", m_pgmEnv.Fw_Info.APP_ExecFile.isFusing);
			printf("%s\r", msg);
			printf("[DEBUG_APP] MadeBy:%d DeviceType:%d Version:%d FileType:%d\n\r",
				m_pgmEnv.Fw_Info.APP_ExecFile.MadeBy, m_pgmEnv.Fw_Info.APP_ExecFile.ProgramType, m_pgmEnv.Fw_Info.APP_ExecFile.DownloadType, m_pgmEnv.Fw_Info.APP_ExecFile.FileType);
			printf("[DEBUG_APP] TotalSize:%ld SuccessSize:%ld FileCRC:0x%x DownBuffPos:0x%lx\n\r",
				m_pgmEnv.Fw_Info.APP_ExecFile.TotalSize, m_pgmEnv.Fw_Info.APP_ExecFile.SuccessSize, m_pgmEnv.Fw_Info.APP_ExecFile.FileCrc, m_pgmEnv.Fw_Info.APP_ExecFile.DownloadBufPos);
#endif
			if ((m_pgmEnv.Fw_Info.APP_ExecFile.TotalSize > 0) && (m_pgmEnv.Fw_Info.APP_ExecFile.TotalSize < pgmSize))
			{
				calCrc = crcInitStrCalc(0x0000, (INT08U*)pgmStartAddr, m_pgmEnv.Fw_Info.APP_ExecFile.TotalSize);

#if DEBUG_MSG
				printf("[DEBUG_APP] Check CRC application. calCrc: 0x%04x FileCrc: 0x%04x\n\r", \
					calCrc, m_pgmEnv.Fw_Info.APP_ExecFile.FileCrc);
#endif
				if (m_ExtSEnv.DebugMode)
				{
					NOP;
				}
				else
				{
					if (m_pgmEnv.Fw_Info.APP_ExecFile.FileCrc == calCrc)
					{
#if DEBUG_MSG
						printf("[DEBUG_APP] Download Program Running.\n\r");
#endif
						m_run_pgm_mode |= cbits16[1];
					}
					else
					{
						m_run_pgm_mode |= cbits16[6];
					}
				}
			}
			else
			{
				m_run_pgm_mode |= cbits16[5];
			}
		}
		else
		{
#if DEBUG_MSG
			printf("[DEBUG_App] App ExecFile information Empty.\n\r");
#endif
			//m_run_pgm_mode |= cbits16[4];
		}
	}

#if DEBUG_MSG
	printf("[DEBUG_APP] Program Initialization Complete.\n\r");
	printf("[DEBUG_APP] Run Mode : 0x%04x.\n\r", m_run_pgm_mode);

	if (m_run_pgm_mode & cbits16[0]) printf("[DEBUG_APP] Boot Run.\n\r");
	if (m_run_pgm_mode & cbits16[1]) printf("[DEBUG_APP] Application Run.\n\r");
	if (m_run_pgm_mode & cbits16[2]) printf("[DEBUG_APP] Boot Mode Switch On.\n\r");
	if (m_run_pgm_mode & cbits16[3]) printf("[DEBUG_APP] Boot Mode Switch Off.\n\r");
	//if (m_run_pgm_mode & cbits16[4]) printf("[DEBUG_APP] Application Program Not Exist.\n\r");
	if (m_run_pgm_mode & cbits16[5]) printf("[DEBUG_APP] Application Program Size Fail.\n\r");
	if (m_run_pgm_mode & cbits16[6]) printf("[DEBUG_APP] Application Program CRC Fail.\n\r");
	if (m_run_pgm_mode & cbits16[7]) printf("[DEBUG_APP] Download Buffer Exist.\n\r");
	if (m_run_pgm_mode & cbits16[8]) printf("[DEBUG_APP] Download Buffer Data Size Error.\n\r");
	if (m_run_pgm_mode & cbits16[9]) printf("[DEBUG_APP] Download Buffer Address Error.\n\r");
	if (m_run_pgm_mode & cbits16[10]) printf("[DEBUG_APP] Download Buffer CRC Error.\n\r");
	if (m_run_pgm_mode & cbits16[11]) printf("[DEBUG_APP] Download Buffer Copy Error.\n\r");
	if (m_run_pgm_mode & cbits16[12]) printf("[DEBUG_APP] Download Buffer Ok.\n\r");
	printf("\n\r");
#endif
	m_pgmEnv.programRun = (m_run_pgm_mode & cbits16[0]) ? 0x01 : 0x02;  // 0x01:Boot, 0x02:App

#if DEBUG_MSG
	if (m_pgmEnv.programRun == 1)
	{
		printf("[DEBUG_APP] Run BootLoader program.\n\r");
	}
	else if (m_pgmEnv.programRun == 2)
	{
		printf("[DEBUG_APP] Run Application program.\n\r");
	}
#endif


	asm volatile("NOP");
}

/////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////

static INT08U m_is_code_check = 0;
//static INT08U m_Download_Type = 0;

/*
void initDownload(void)
{
	m_pgmEnv.downloadMode = 0;
	m_pgmEnv.downloadDevType = 0;
	m_pgmEnv.downloadFileType = 0;
	m_pgmEnv.downloadTimer = m_pgmEnv.timer1ms;
}
*/

/**
  * @brief	Set_Download_Info
  * @param  DownloadInfo_t* pSetting
  * @retval void
  */
void Set_Firmware_Info(DownloadInfo_t* pSetting)
{
	ExtFlash_ReadData(EXT_DEVICE_SET_ADDR_START, (INT08U*)&m_ExtSEnv, sizeof(ExtFlashSEnv));

	if (memcmp((INT08U*)&m_ExtSEnv.FW_Info, (INT08U*)pSetting, sizeof(DownloadInfo_t)))
	{
		memcpy((INT08U*)&m_ExtSEnv.FW_Info, (INT08U*)pSetting, sizeof(DownloadInfo_t));
	
		ExtFlash_WriteData(EXT_DEVICE_SET_ADDR_START, (INT08U*)&m_ExtSEnv, sizeof(ExtFlashSEnv));

#if DEBUG_MSG
		printf("[DEBUG_APP] Download Information save to external flash.\r\n");
#endif
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Download Information same setting. Do not save in external flash.\r\n");
#endif
	}
}

INT16U m_Download_CRC = 0;

/**
  * @brief  FW Download Start Command
  * @details
  * Result
  * 0 : 정상
  * 1 : 에러 - 장비 동작 중
  * 2 : 에러(현재 타장비로부터 다운로드 진행중)
  * 2 : 에러(디바이스 Type이 틀릴 때)
  * 3 : 에러(프로그램 Version이 틀릴 때)
  * 4 : 에러(파일크기가 수신버퍼크기를 벗어났을 때)
  * 5 : 에러(기타)
  * @param  port 수신 포트
  * @param  pCom 수신데이터 버퍼 포인터
  * @return None
  */
void rxDownloadStart(INT08U port, TMLComPTR pCom)
{
	INT08U reason = 0x00;
	INT32U downloadSize = 0;
	INT32U startAddr = 0, endAddr = 0;
	INT32U pgmSize = 0;

	INT08U nEraseFlag = 0;

	if (m_pgmEnv.SFlash_Install == 0)
	{
		if (reason == 0)	reason = 0x19;
	}

	if (m_pgmEnv.downloadMode)
	{
		if (reason == 0)	reason = 0x011;
	}
		
	if (m_pgmEnv.SRM_RunMode)
	{
		if (reason == 0)	reason = 0x12;
	}
		
	if (m_St.SRM_Mode.Bit.Auto)
	{
		if (reason == 0)	reason = 0x13;
	}

	m_pgmEnv.Fw_Info.Buf_ExecFile.ProgramType = pCom->Data[0];
	m_pgmEnv.Fw_Info.Buf_ExecFile.DownloadType = pCom->Data[1];
	m_pgmEnv.Fw_Info.Buf_ExecFile.TotalSize = getStr2LongValue(&pCom->Data[2]);

	m_pgmEnv.Fw_Info.Buf_ExecFile.FileType = 0;
	m_pgmEnv.Fw_Info.Buf_ExecFile.MadeBy = 0;
	m_pgmEnv.Fw_Info.Buf_ExecFile.SuccessSize = 0;
	m_pgmEnv.Fw_Info.Buf_ExecFile.FileCrc = 0;
	m_pgmEnv.Fw_Info.Buf_ExecFile.DownloadBufPos = 0;

	if (m_pgmEnv.Fw_Info.Buf_ExecFile.ProgramType == 0x00)
	{
		// App 프로그램
		startAddr = EXT_FW_APP_ADDR_START;
		endAddr = EXT_FW_APP_ADDR_END;
	}
	else if (m_pgmEnv.Fw_Info.Buf_ExecFile.ProgramType == 0x01)
	{
		// Boot 프로그램
		startAddr = EXT_FW_BOOT_ADDR_START;
		endAddr = EXT_FW_BOOT_ADDR_END;
	}
	else
	{
		if (reason == 0)	reason = 0x14;
	}

	pgmSize = endAddr - startAddr;
	downloadSize = m_pgmEnv.Fw_Info.Buf_ExecFile.TotalSize;
	if (m_pgmEnv.Fw_Info.Buf_ExecFile.TotalSize > pgmSize)
	{
		if (reason == 0)	reason = 0x15;

		downloadSize = pgmSize;
	}
	else
	{
		// 현재 다운로드프로그램이 돌고있으면 버퍼 영역에 기록
		//m_pgmEnv.Download_Info.BuffExecFile.DownloadBufPos = startAddr;
	}

	if (m_pgmEnv.programRun == 0x02)  // Run App 
	{
		if (m_pgmEnv.Fw_Info.Buf_ExecFile.DownloadType > 2)
		{
			if (reason == 0)	reason = 0x17;
		}
	}
	
	if (reason == 0)
	{
		if ((m_pgmEnv.Fw_Info.Buf_ExecFile.DownloadType == 0) \
			|| (m_pgmEnv.Fw_Info.Buf_ExecFile.DownloadType == 2))
		{
			m_is_code_check = 1;
		}
		else if (m_pgmEnv.Fw_Info.Buf_ExecFile.DownloadType == 1)
		{
			m_is_code_check = 0;
		}

		//m_St.SRM_Mode.D = 0;

		m_pgmEnv.downloadMode = 1;
		m_pgmEnv.downloadTimer = m_pgmEnv.timer1ms;

		if (port < MAX_UART_PORT)  m_pgmEnv.FlashUartDisable = 1;
		else                        m_pgmEnv.FlashUartDisable = 0;

		
		nEraseFlag = ExtFlash_EraseData(startAddr, pgmSize);

		if (nEraseFlag)
		{
			/*
			if (port == rsETHUDPPort_Uplink)
			{
				udp_Set_Fw_Download_IP_Info();
			}
			*/
			if (port == rsETHUDPPort_Uplink)
			{
				udp_Set_Fw_Download_IP_Info();
			}


			m_pgmEnv.Fw_Info.Buf_ExecFile.DownloadBufPos = startAddr;

			m_Download_CRC = 0;
		}
		else
		{
			reason = 0x18;
		}
	}

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);
	crcClear(port);
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 8);
	txPutcPort(port, reason ? 0x01 : 0x00);
	txPutcPort(port, reason);
	txPutlPort(port, downloadSize);
	txPutwPort(port, FW_BLOCK_SIZE);
	txCRCPort(port);
	rsPutmPort(port, FRAME_ETX, 1);
	sendTxBuf(port);

#if DEBUG_UPGRADE_MSG
	printf("[UPGRADE] Start reason: %02x BufferPos: 0x%08lx, startAddr: 0x%08lx, endAddr: 0x%08lx Port: %d\r\n",
		reason, m_pgmEnv.Fw_Info.Buf_ExecFile.DownloadBufPos, startAddr, endAddr, port);
#endif
	asm volatile("NOP");
}


/**
  * @brief  FW Binary Download
  * @details
  * Result
  * 0 : 정상
  * 1 : 에러(수신되는 데이터위치가 잘못되었을때)
  * 2 : 에러(데이타 크기가 수신버퍼범위를 벗어났을때)
  * 3 : 에러(프로젝트코드 체크 오류)
  * 4 : 에러(기타)
  * @param  port 수신 포트
  * @param  pCom 수신데이터 버퍼 포인터
  * @return None
  */
void rxDownloadData(INT08U port, TMLComPTR pCom)
{
	INT08U  reason = 0, response = 0;
	INT16U  download_size = 0;
	INT32U  download_pos = 0;
	INT32U  flashadr = 0;
	INT32U  stack_address = 0, jump_address = 0;
	INT32U  start_address = 0, stop_address = 0;

	if (m_pgmEnv.downloadMode == 1)
	{
		m_pgmEnv.downloadTimer = m_pgmEnv.timer1ms;

		download_pos = getStr2LongValue(&pCom->Data[0]);
		download_size = getStr2ShortValue(&pCom->Data[4]);

		if (download_pos == m_pgmEnv.Fw_Info.Buf_ExecFile.SuccessSize)
		{
			asm volatile ("NOP");
		}
		else if (download_pos == (m_pgmEnv.Fw_Info.Buf_ExecFile.SuccessSize - FW_BLOCK_SIZE))
		{
#if DEBUG_UPGRADE_MSG
			printf("[UPGRADE] Duplicate Data download_pos:%ld Size:%ld\r\n", \
				download_pos, m_pgmEnv.Fw_Info.Buf_ExecFile.SuccessSize);
#endif
			reason = 0x26;
		}
		else
		{
			reason = 0x21;
		}

		if (download_size > FW_BLOCK_SIZE)  reason = 0x22;

		if (reason == 0)
		{
			// Code Check : Stack Address, Jump Address, Project Code
			if (m_pgmEnv.Fw_Info.Buf_ExecFile.SuccessSize == 0)
			{
				stack_address = getStr2LongValue(&pCom->Data[0x0000 + 6]);  // Stack Address 0x0000 + 2
				jump_address = getStr2LongValue(&pCom->Data[0x0004 + 6]);  // Jump  Address 0x0004 + 2

				if ((m_pgmEnv.Fw_Info.Buf_ExecFile.DownloadType == 0) \
					|| (m_pgmEnv.Fw_Info.Buf_ExecFile.DownloadType == 1))
				{
					start_address = DOWN_PGM_IN_FLASH_START_SECTOR_ADDR;
					stop_address = DOWN_PGM_IN_FLASH_END_SECTOR_ADDR;
				}
				else
				{
					start_address = BOOT_PGM_IN_FLASH_START_SECTOR_ADDR;
					stop_address = BOOT_PGM_IN_FLASH_END_SECTOR_ADDR;
				}

				if (((stack_address & 0xFFF00000) != 0x20000000)
					|| (jump_address < start_address)
					|| (jump_address > stop_address))
				{
					reason = 0x2A;
				}
					
			}

			if ((reason == 0) && m_is_code_check)
			{
				if (m_pgmEnv.Fw_Info.Buf_ExecFile.SuccessSize > (PROJECT_CODE_POS + sizeof(project_rom_code)))
				{
					if ((checkDownloadCode_1(m_pgmEnv.Fw_Info.Buf_ExecFile.DownloadBufPos, \
						m_pgmEnv.Fw_Info.Buf_ExecFile.DownloadType)) == 0)
					{
						m_is_code_check = 0;
					}
					else
					{
						//m_pgmEnv.Download_Info.Buffer_ExecFile.SuccessSize = 0;
						reason = 0x24;
					}
				}
			}

			if (reason == 0)
			{
				flashadr = m_pgmEnv.Fw_Info.Buf_ExecFile.DownloadBufPos \
					+ m_pgmEnv.Fw_Info.Buf_ExecFile.SuccessSize;

				response = ExtFlash_WriteFW(flashadr, (INT08U*)&pCom->Data[6], download_size, &m_Download_CRC);

				if (response == 0)
				{
					reason = 0x23;
					m_pgmEnv.Fw_Info.Buf_ExecFile.SuccessSize = 0;
				}
				else
				{
					m_pgmEnv.Fw_Info.Buf_ExecFile.SuccessSize += download_size;
				}
			}
		}
	}
	else
	{
		reason = 0x25;
	}

	if (reason == 0x26)		reason = 0;

	clearTxBuf(port);
	rsPutmPort(port, FRAME_STX, 4);		
	crcClear(port);                     
	txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 6);
	txPutcPort(port, reason ? 0x01 : 0x00);
	txPutcPort(port, reason);

	if (reason == 0x26) {
		txPutlPort(port, (m_pgmEnv.Fw_Info.Buf_ExecFile.SuccessSize - download_size));                       // Data
	}
	else {
		txPutlPort(port, m_pgmEnv.Fw_Info.Buf_ExecFile.SuccessSize); // Data
	}

	txCRCPort(port);                  // Transmit CRC
	rsPutmPort(port, FRAME_ETX, 1);   // ETX : 0xF5
	sendTxBuf(port);

#if DEBUG_UPGRADE_MSG
	printf("[UPGRADE] Data Download reason:%02x, download_pos:%ld Size:%ld CRC: 0x%04x, port: %d\r\n", \
		reason, download_pos, m_pgmEnv.Fw_Info.Buf_ExecFile.SuccessSize, m_Download_CRC, port);
#endif
}


/**
  * @brief  FW Binary Download
  * @details
  * Result
  * 0 : 정상
  * 1 : 에러(수신된 파일크기가 틀릴때)
  * 2 : 에러(수신된 데이터의 CRC가 틀릴때)
  * 3 : 에러(기타)
  * @param  port 수신 포트
  * @param  pCom 수신데이터 버퍼 포인터
  * @return None
  */
void rxDownloadFinish(INT08U port, TMLComPTR pCom)
{
	//INT16U fileCrc = 0, calCrc = 0;
	INT16U fileCrc = 0;
	INT08U reason = 0;
	INT08U response = 0;
	INT32U startAddr = 0, endAddr = 0;
	INT32U success_size = 0, buffer_pos = 0;
	INT32U status = 0;

	if (m_pgmEnv.downloadMode == 1)
	{
		fileCrc = (pCom->Data[0] << 8) | pCom->Data[1];

		success_size = m_pgmEnv.Fw_Info.Buf_ExecFile.SuccessSize;
		if (m_pgmEnv.Fw_Info.Buf_ExecFile.TotalSize != success_size)  reason = 0x31;
		else
		{
			if (fileCrc != m_Download_CRC)  reason = 0x32;
		}

		clearTxBuf(port);
		rsPutmPort(port, FRAME_STX, 4);
		crcClear(port);
		txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 8);
		txPutcPort(port, reason ? 0x01 : 0x00);
		txPutcPort(port, reason);
		txPutlPort(port, m_pgmEnv.Fw_Info.Buf_ExecFile.SuccessSize);
		txPutiPort(port, m_Download_CRC);
		txCRCPort(port);
		rsPutmPort(port, FRAME_ETX, 1);
		sendTxBuf(port);

#if DEBUG_MSG
		printf("[UPGRADE] Finish reason:%02x buffer_pos:0x%lx SuccessSize:%ld fileCrc:0x%x calCrc:0x%x\r\n", \
			reason, buffer_pos, m_pgmEnv.Fw_Info.Buf_ExecFile.SuccessSize, fileCrc, m_Download_CRC);
#endif

		if (reason == 0x00)
		{
			if ((m_pgmEnv.Fw_Info.Buf_ExecFile.DownloadType == 0) \
				|| (m_pgmEnv.Fw_Info.Buf_ExecFile.DownloadType == 1))
			{
				m_pgmEnv.Fw_Info.Buf_ExecFile.FileCrc = m_Download_CRC;
				memcpy((INT08U*)m_pgmEnv.Fw_Info.Buf_ExecFile.isFusing, (INT08U*)"Write App", 10);

				m_pgmEnv.FlashUartDisable = 0;

				Set_Firmware_Info(&m_pgmEnv.Fw_Info);
#if DEBUG_MSG
				char msg[50] = { 0, };

				printf("[DEBUG_APP] Buffer ExecFile Information\n\r");
				sprintf(msg, "[DEBUG_APP] isFusion:%s\n", m_pgmEnv.Fw_Info.Buf_ExecFile.isFusing);
				//printf("%s\n\r", msg);
				printf("[DEBUG_APP] MadeBy:%d DeviceType:%d Version:%d FileType:%d\n\r",
					m_pgmEnv.Fw_Info.Buf_ExecFile.MadeBy, m_pgmEnv.Fw_Info.Buf_ExecFile.ProgramType,
					m_pgmEnv.Fw_Info.Buf_ExecFile.DownloadType, m_pgmEnv.Fw_Info.Buf_ExecFile.FileType);
				printf("[DEBUG_APP] TotalSize:%ld SuccessSize:%ld FileCRC:0x%x DownBuffPos:0x%lx\n\r",
					m_pgmEnv.Fw_Info.Buf_ExecFile.TotalSize, m_pgmEnv.Fw_Info.Buf_ExecFile.SuccessSize, m_pgmEnv.Fw_Info.Buf_ExecFile.FileCrc,
					m_pgmEnv.Fw_Info.Buf_ExecFile.DownloadBufPos);
#endif
			}
			else
			{
				FLASH_User_EraseSector(BOOT_PGM_IN_FLASH_START_SECTOR_ADDR, BOOT_PGM_IN_FLASH_END_SECTOR_ADDR);
				FLASH_User_WriteData_1(BOOT_PGM_IN_FLASH_START_SECTOR_ADDR, m_pgmEnv.Fw_Info.Buf_ExecFile.DownloadBufPos, \
					m_pgmEnv.Fw_Info.Buf_ExecFile.TotalSize);
			}

			wait1ms(100);
			controlCpuReset();
		}
	}
	else
	{
		reason = 0x35;

		clearTxBuf(port);
		rsPutmPort(port, FRAME_STX, 4);                                        // STX : 0x16 0x16 0x16 0x16
		crcClear(port);                                                      // Clear CRC
		txPutHeader(port, (ComHeaderSTR*)&pCom->Header, pCom->Header.Cmd | 0x80, pCom->Header.Cmd2, 8);
		txPutcPort(port, reason ? 0x01 : 0x00);                                // Data ACK
		txPutcPort(port, reason);                                // Nack Reason
		txPutlPort(port, m_pgmEnv.Fw_Info.Buf_ExecFile.SuccessSize);                       // Data
		txPutiPort(port, m_Download_CRC);                                              // Data
		txCRCPort(port);                                                      // Transmit CRC
		rsPutmPort(port, FRAME_ETX, 1);                                        // ETX : 0xF5
		sendTxBuf(port);

#if DEBUG_UPGRADE_MSG
		printf("[UPGRADE] Finish Error reason:%02x SuccessSize:%ld\r\n", \
			reason, m_pgmEnv.Fw_Info.Buf_ExecFile.SuccessSize);
#endif
	}
}

/**
  * @brief  
  * @param  None
  * @retval None
  */
void checkDownload(void)
{
	if (m_pgmEnv.downloadMode)
	{
		FpgaTcpIpStackProcess();

		if (getCalcTimer1ms(m_pgmEnv.downloadTimer) >= 10000)
		//if (getCalcTimer1ms(m_pgmEnv.downloadTimer) >= 3000)
		{
#if DEBUG_UPGRADE_MSG
			printf("[UPGRADE] Forced Stop.\r\n");
#endif
			m_pgmEnv.downloadMode = 0;
		}
	}
}


