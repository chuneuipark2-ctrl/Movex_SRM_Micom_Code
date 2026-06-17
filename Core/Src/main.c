/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  * 주의 사항 : Application 프로그램 사이즈가 720895byte보다 클 경우, Boot 프로그램에서
  * FW 파일을 내부 플래시에 복사하지 않음

  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"
#include "lwip.h"
#include "usb_host.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "type.h"
#include "User_Define.h"
#include "rtc.h"
#include "alarm.h"
#include "uart.h"
#include "com_tml.h"
#include "upgrade.h"
#include "com_udp.h"
#include "mcu_util.h"
#include "flash.h"
#include "com_hmi.h"
#include "fpga.h"
#include "ecat_main.h"
#include "FlashSST26.h"
#include "usb_user.h"
#include "dev_SRM.h"
#include "SRM_Parameter.h"
#include "com_dsp.h"
//#include "com_ht100.h"
#include "Com_Debug.h"

#include "Mcu_Test.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan1;

IWDG_HandleTypeDef hiwdg;

RTC_HandleTypeDef hrtc;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart6;
DMA_HandleTypeDef hdma_usart3_tx;

SRAM_HandleTypeDef hsram1;
SRAM_HandleTypeDef hsram3;

/* USER CODE BEGIN PV */
const INT08U nVal[17] = { '0','1','2','3','4','5','6','7', '8','9','A','B','C','D','E','F',0x20 };

const INT08U cbits[8] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };

const INT08U nbits[8] = { 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F };

const INT16U cbits16[16] = { 0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080,
							0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000 };

const INT16U nbits16[16] = { 0xFFFE, 0xFFFD, 0xFFFB, 0xFFF7, 0xFFEF, 0xFFDF, 0xFFBF, 0xFF7F,
							0xFEFF, 0xFDFF, 0xFBFF, 0xF7FF, 0xEFFF, 0xDFFF, 0xBFFF, 0x7FFF };

const INT32U cbits32[32] = { 0x00000001, 0x00000002, 0x00000004, 0x00000008, 0x00000010, 0x00000020, 0x00000040, 0x00000080,
							0x00000100, 0x00000200, 0x00000400, 0x00000800, 0x00001000, 0x00002000, 0x00004000, 0x00008000,
							0x00010000, 0x00020000, 0x00040000, 0x00080000, 0x00100000, 0x00200000, 0x00400000, 0x00800000,
							0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000 };

const INT32U nbits32[32] = { 0xFFFFFFFE, 0xFFFFFFFD, 0xFFFFFFFB, 0xFFFFFFF7, 0xFFFFFFEF, 0xFFFFFFDF, 0xFFFFFFBF, 0xFFFFFF7F,
							0xFFFFFEFF, 0xFFFFFDFF, 0xFFFFFBFF, 0xFFFFF7FF, 0xFFFFEFFF, 0xFFFFDFFF, 0xFFFFBFFF, 0xFFFF7FFF,
							0xFFFEFFFF, 0xFFFDFFFF, 0xFFFBFFFF, 0xFFF7FFFF, 0xFFEFFFFF, 0xFFDFFFFF, 0xFFBFFFFF, 0xFF7FFFFF,
							0xFEFFFFFF, 0xFDFFFFFF, 0xFBFFFFFF, 0xF7FFFFFF, 0xEFFFFFFF, 0xDFFFFFFF, 0xBFFFFFFF, 0x7FFFFFFF };


INT16U				m_run_pgm_mode;

__attribute__((section(".dtcm_bss"))) ExtFlashSEnv		m_ExtSEnv;
__attribute__((section(".dtcm_bss"))) ExtFlashSEnv0		m_ExtSEnv0;
__attribute__((section(".dtcm_bss"))) ExtFlashSEnv1		m_ExtSEnv1;
__attribute__((section(".dtcm_bss"))) ExtFlashSEnv2		m_ExtSEnv2;

DevStatusSTR		m_DevStatus;
__attribute__((section(".dtcm_bss"))) StatusSTR			m_St;

__attribute__((section(".dtcm_bss"))) BKSRamSTR			m_BKSram;
__attribute__((section(".dtcm_bss"))) PGMEnvSTR			m_pgmEnv;
__attribute__((section(".dtcm_bss"))) TestStatusSTR		m_TestStatus;
__attribute__((section(".dtcm_bss"))) InvertorInfoSTR		m_Invertor_Info;

DIO_SetInfoSTR		m_DIO_SetInfo;

GraphLogSTR        m_GraphLog;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_RTC_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_TIM3_Init(void);
static void MX_FMC_Init(void);
static void MX_USART6_UART_Init(void);
static void MX_SPI2_Init(void);
static void MX_TIM2_Init(void);
static void MX_UART4_Init(void);
static void MX_TIM4_Init(void);
static void MX_IWDG_Init(void);
static void MX_CAN1_Init(void);
void MX_USB_HOST_Process(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#ifdef __cplusplus
extern "C" int _write(int32_t file, uint8_t* ptr, int32_t len) {
#else
int _write(int32_t file, uint8_t * ptr, int32_t len) {
#endif
	/*
	for (int32_t i = 0; i < len; ++i) { ITM_SendChar(*ptr++); }
	return len;
	*/

	///*
	INT08U nReturn = 0;

	if (HAL_UART_Transmit(&huart4, ptr, len, 1000) == HAL_OK) {
		//if (HAL_UART_Transmit(&huart3, ptr, len, 1000) == HAL_OK) {
		nReturn = len;
	}

	return nReturn;
	//*/
}

/**
  * @brief  This function is executed in MPU Config
  * @retval None
  */
static void MPU_Config(void)
{
	MPU_Region_InitTypeDef MPU_InitStruct;

	HAL_MPU_Disable();

	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.BaseAddress = ADDR_FSMC_FPGA_REG;
	MPU_InitStruct.Size = MPU_REGION_SIZE_256KB;
	MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;   // MPU_ACCESS_CACHEABLE;
	MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;   // MPU_ACCESS_SHAREABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER0;
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
	MPU_InitStruct.SubRegionDisable = 0x00;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

/**
  * @brief  The application entry point.
  * @retval void
  */
void Check_Flash_DualBank()
{
	FLASH_OBProgramInitTypeDef    OBInit;

	/* Allow Access to Flash control registers and user Flash */
	HAL_FLASH_Unlock();

	/* Allow Access to option bytes sector */
	HAL_FLASH_OB_Unlock();

	HAL_FLASHEx_OBGetConfig(&OBInit);

	/* Prevent Access to option bytes sector */
	HAL_FLASH_OB_Lock();

	/* Disable the Flash option control register access (recommended to protect
	the option Bytes against possible unwanted operations) */
	HAL_FLASH_Lock();

	if ((OBInit.USERConfig & OB_NDBANK_SINGLE_BANK) == OB_NDBANK_SINGLE_BANK)
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Flash Single bank mode. Flash option : %04lx\r\n", OBInit.USERConfig);
#endif
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Flash Dual bank mode. Flash option : %04lx\r\n", OBInit.USERConfig);
#endif
	}
}

/**
  * @brief  This function is generate Firmware version format
   * @param verStr FW Version String
  * @param ver FW Version
  * @retval None
  */
void checkVerStr(INT08U * verStr, INT08U ver)
{
	//  __LINE__, __FILE__, __TIME__, __DATE__, __STDC__    
	//  __DATE__  4A 75 6C 20 32 33 20 32 30 30 39 00      Jul 23 2009
	//            0  1  2     4  5     7  8  9  10

	INT08U monthStr[12][4] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
	INT08U date[12];
	INT08U i, mon;

	memcpy((INT08U*)date, (INT08U*)__DATE__, 12);

#ifdef PGM_BOOT
	verStr[0] = 0x01;
#else
	verStr[0] = ver;
#endif 

	verStr[2] = 0x00;
	for (i = 0; i < 12; i++)
	{
		if (strncmp((char*)date, (char*)monthStr[i], 3) == 0)
		{
			mon = i + 1;
			verStr[2] = ((mon / 10) << 4) | (mon % 10);
			break;
		}
	}

	if (((date[9] >= '0') && (date[9] <= '9')) && ((date[10] >= '0') && (date[10] <= '9')))   verStr[1] = ((date[9] - '0') << 4) | (date[10] - '0');
	else                                                                               verStr[1] = 0x00;

	if (((date[4] >= '0') && (date[4] <= '9')) && ((date[5] >= '0') && (date[5] <= '9')))   verStr[3] = ((date[4] - '0') << 4) | (date[5] - '0');
	else if ((date[4] == ' ') && ((date[5] >= '0') && (date[5] <= '9')))   verStr[3] = (date[5] - '0');
	else                                                                               verStr[3] = 0x00;
}

/**
  * @brief
  * @param None
  * @retval None
  */
  /*
  void Init_Network_Setting()
  {
	  INT08U my_ip[4] = { 192, 168, 100, 16 };
	  INT08U subnet[4] = { 255, 255, 255, 0 };
	  INT08U gateway[4] = { 192, 168, 100, 1 };
	  INT08U my_mac[6] = { 0x00, 0x0A, 0x1F, 0x00, 0x01, 0x02 };

	  NetworkInfo_t nDefaultSet;

	  if ((m_DevSet.mParam.NetworkInfo_0.MyIP[0] == 0xFF) ||
		  (m_DevSet.mParam.NetworkInfo_0.MyIP[0] == 0x00))
	  {
		  memcpy((INT08U*)nDefaultSet.MyIP, (INT08U*)my_ip, 4);
		  memcpy((INT08U*)nDefaultSet.SubnetMask, (INT08U*)subnet, 4);
		  memcpy((INT08U*)nDefaultSet.GatewayIP, (INT08U*)gateway, 4);

		  set_Network_Parameter((NetworkInfo_t*)&nDefaultSet, 0, 0);
	  }
	  else
	  {
		  Load_Network_Parameter((NetworkInfo_t*)&m_DevStatus.NetworkInfo_0, 0);
	  }

	  if ((m_DevSet.mParam.MyMACAddr_0[0] != 0x00) || (m_DevSet.mParam.MyMACAddr_0[1] != 0x0A)
		  || (m_DevSet.mParam.MyMACAddr_0[2] != 0x1F))
	  {
		  set_MAC_Addrress((INT08U*)my_mac, 0, 0);
	  }
	  else
	  {
		  Load_MAC_Addrress((INT08U*)m_DevStatus.MyMACAddr_0, 0);
	  }
  }
  */

  /**
  * @brief
  * @param none
  * @retval None
  */
void Load_ExtFlash_Setting()
{
	//sst_init();

	if (m_pgmEnv.SFlash_Install)
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] External Flash connect : %d\n\r", m_pgmEnv.SFlash_Install);
		printf("[DEBUG_APP] External Flash Memory MAP\n\r");

		printf("[DEBUG_APP] Device Setting start: 0x%06x end: 0x%06x size: %d KBytes\n\r", \
			EXT_DEVICE_SET_ADDR_START, EXT_DEVICE_SET_ADDR_END, (EXT_DEVICE_SET_ADDR_END - EXT_DEVICE_SET_ADDR_START + 1) / 1024);

		printf("[DEBUG_APP] Rack1 Setting start: 0x%06x end: 0x%06x size: %d KBytes\n\r", \
			EXT_RACK_ENV0_ADDR_START, EXT_RACK_ENV0_ADDR_END, (EXT_RACK_ENV0_ADDR_END - EXT_RACK_ENV0_ADDR_START + 1) / 1024);

		printf("[DEBUG_APP] Rack2 Setting start: 0x%06x end: 0x%06x size: %d KBytes\n\r", \
			EXT_RACK_ENV1_ADDR_START, EXT_RACK_ENV1_ADDR_END, (EXT_RACK_ENV1_ADDR_END - EXT_RACK_ENV1_ADDR_START + 1) / 1024);

		printf("[DEBUG_APP] Parameter Setting start: 0x%06x end: 0x%06x size: %d KBytes\n\r", \
			EXT_PARAMETER_SET_ADDR_START, EXT_PARAMETER_SET_ADDR_END, (EXT_PARAMETER_SET_ADDR_END - EXT_PARAMETER_SET_ADDR_START + 1) / 1024);

		printf("[DEBUG_APP] Cell Offset UseFlag start: 0x%06x end: 0x%06x size: %d KBytes\n\r", \
			EXT_CELL_OFFSET_USEFLAG_ADDR_START, EXT_CELL_OFFSET_USEFLAG_ADDR_END, (EXT_CELL_OFFSET_USEFLAG_ADDR_END - EXT_CELL_OFFSET_USEFLAG_ADDR_START + 1) / 1024);

		printf("[DEBUG_APP] Cell Offset Setting start: 0x%06x end: 0x%06x size: %d KBytes\n\r", \
			EXT_CELL_OFFSET_ADDR_START, EXT_CELL_OFFSET_ADDR_END, (EXT_CELL_OFFSET_ADDR_END - EXT_CELL_OFFSET_ADDR_START + 1) / 1024);

		printf("[DEBUG_APP] Boot FW Buffer start: 0x%06x end: 0x%06x size: %d KBytes\n\r", \
			EXT_FW_BOOT_ADDR_START, EXT_FW_BOOT_ADDR_END, (EXT_FW_BOOT_ADDR_END - EXT_FW_BOOT_ADDR_START + 1) / 1024);

		printf("[DEBUG_APP] App FW Buffer start: 0x%06x end: 0x%06x size: %d KBytes\n\r", \
			EXT_FW_APP_ADDR_START, EXT_FW_APP_ADDR_END, (EXT_FW_APP_ADDR_END - EXT_FW_APP_ADDR_START + 1) / 1024);
#endif
		Device_Setting_Init();
		Machine_Type_Setting_Init();

		DIO_Setting_Init();

		Rack_Config_Init();
		Cell_Config_Init();
		CellOffset_Config_Init();
		Station_Config_Init();
		ProhibitRack_Config_Init();
		SpecialRack_Config_Init();

		Control_Param_Init();
		Travel_Drive_Param_Init();
		Lift_Drive_Param_Init();
		Fork_Drive_Param_Init();

		/*
		if (m_ExtSEnv.Machine.mType.Fork_Type == 1)
		{
			// �깃���
			m_ExtSEnv0.RackConfig.RowDepth[0] = m_ExtSEnv2.ForkDrive.ForkPosDepth.mFHL;		// Row1
			m_ExtSEnv0.RackConfig.RowDepth[1] = m_ExtSEnv2.ForkDrive.ForkPosDepth.mFHR;		// Row2
		}
		else if ((m_ExtSEnv.Machine.mType.Fork_Type == 2) \
			(m_ExtSEnv.Machine.mType.Fork_Type == 2))
		{
			m_ExtSEnv0.RackConfig.RowDepth[0] = m_ExtSEnv2.ForkDrive.ForkPosDepth.mFEL;		// Row1
			m_ExtSEnv0.RackConfig.RowDepth[1] = m_ExtSEnv2.ForkDrive.ForkPosDepth.mFHL;		// Row2
			m_ExtSEnv0.RackConfig.RowDepth[2] = m_ExtSEnv2.ForkDrive.ForkPosDepth.mFHR;		// Row3
			m_ExtSEnv0.RackConfig.RowDepth[3] = m_ExtSEnv2.ForkDrive.ForkPosDepth.mFHR;		// Row4
		}
		*/

		Create_Reference_Position();

		//HT100_Param_List_Init();
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG] External Flash not connect. load fail.\r\n");
#endif
	}

	/*
	INT08U nIndex = DEBUG_STR_1;

	m_TestStatus.St[nIndex] = sizeof(DownloadInfo_t);		++nIndex;
	m_TestStatus.St[nIndex] = sizeof(DeviceSetting) + 6;		++nIndex;
	m_TestStatus.St[nIndex] = sizeof(SRM_Machine_Type) + 6;		++nIndex;
	m_TestStatus.St[nIndex] = sizeof(DIO_SetSTR) + 6;			++nIndex;

	m_TestStatus.St[nIndex] = sizeof(ExtFlashSEnv) - sizeof(DIO_SetSTR) - sizeof(SRM_Machine_Type) \
							- sizeof(DeviceSetting) - sizeof(DownloadInfo_t) - 19;		++nIndex;
	m_TestStatus.St[nIndex] = sizeof(ExtFlashSEnv);			++nIndex;

	m_TestStatus.St[nIndex] = sizeof(CellConfigSTR);		++nIndex;
	m_TestStatus.St[nIndex] = sizeof(RackConfigSTR);		++nIndex;
	m_TestStatus.St[nIndex] = sizeof(ExtFlashSEnv0) - sizeof(RackConfigSTR) \
							- sizeof(CellConfigSTR) - 18;  ++nIndex;
	m_TestStatus.St[nIndex] = sizeof(ExtFlashSEnv0);		++nIndex;

	m_TestStatus.St[nIndex] = sizeof(ProhibitRackSTR) + 6;		++nIndex; // 6 = inti code(4) + crc(2)
	m_TestStatus.St[nIndex] = sizeof(SpecialRackSTR) + 6;		++nIndex;
	m_TestStatus.St[nIndex] = sizeof(StationSetupSTR) + 6;		++nIndex;
	m_TestStatus.St[nIndex] = sizeof(ExtFlashSEnv1);			++nIndex;

	m_TestStatus.St[nIndex] = sizeof(ParamControlSTR) + 6;		++nIndex;
	m_TestStatus.St[nIndex] = sizeof(ParamTravelDriveSTR) + 6;	++nIndex;
	m_TestStatus.St[nIndex] = sizeof(ParamLiftDriveSTR) + 6;		++nIndex;
	m_TestStatus.St[nIndex] = sizeof(ParamForkDriveSTR) + 6;		++nIndex;
	m_TestStatus.St[nIndex] = sizeof(ExtFlashSEnv2);				++nIndex;
	*/
}

/**
* @brief
* @param none
* @retval None
*/
void Recovery_Work_Info()
{
	INT08U i = 0;

#if DEBUG_MSG
	printf("[BACKUP_SRAM] Save Work Information Data Size : %d Bytes.\n\r", sizeof(SaveWorkSTR));
#endif

	if (checkFusingString((INT08U*)m_BKSram.WorkInfo.CheckString, (INT08U*)BK_WORK_INFO_INIT_CODE, 4))
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Recovery Work information Empty. Clear Work Data.\n\r");
#endif
		memset((INT08U*)&m_BKSram.WorkInfo, 0x00, sizeof(SaveWorkSTR));
		memcpy((INT08U*)m_BKSram.WorkInfo.CheckString, BK_WORK_INFO_INIT_CODE, 4);
		saveBKSramBlock((INT08U*)&m_BKSram.WorkInfo, sizeof(SaveWorkSTR));
	}
	else
	{
		for (i = 0; i < 2; i++)
		{
			if ((m_BKSram.WorkInfo.WorkSt[i].WorkNum_Fork == 0)
				|| (m_BKSram.WorkInfo.WorkSt[i].OrderCode_Fork == ORDER_CODE_NONE))
			{
				//memset((INT08U*)&m_BKSram.WorkInfo.WorkSt[i], 0x00, sizeof(WorkInfoSTR));
				m_BKSram.WorkInfo.WorkSt[i].WorkNum_Fork = 0;
				m_BKSram.WorkInfo.WorkSt[i].Task_Index = 0;

				memset((INT08U*)&m_BKSram.WorkInfo.WorkSt[i].From_Cell_Fork, 0, sizeof(CellPosSTR));
				memset((INT08U*)&m_BKSram.WorkInfo.WorkSt[i].To_Cell_Fork, 0, sizeof(CellPosSTR));

				m_BKSram.WorkInfo.WorkSt[i].OrderCode_Fork = 0;
				m_BKSram.WorkInfo.WorkSt[i].OrderStatus_Fork = 0;
				m_BKSram.WorkInfo.WorkSt[i].OrderProcess_Fork = 0;
			}
			else
			{
				/*
				if ((m_BKSram.WorkInfo.WorkSt[i].OrderStatus_Fork == WORK_STATUS_DOING)
					|| (m_BKSram.WorkInfo.WorkSt[i].OrderStatus_Fork == WORK_STATUS_STOP)
					|| (m_BKSram.WorkInfo.WorkSt[i].OrderStatus_Fork == WORK_STATUS_FAIL))
				{
					m_BKSram.WorkInfo.WorkSt[i].OrderStatus_Fork = WORK_STATUS_STOP;
				}
				*/

				if ((m_BKSram.WorkInfo.WorkSt[i].OrderStatus_Fork == WORK_STATUS_NONE)
					|| (m_BKSram.WorkInfo.WorkSt[i].OrderStatus_Fork == WORK_STATUS_COMPLETE))
				{
					asm volatile("NOP");
				}
				else
				{
					m_BKSram.WorkInfo.WorkSt[i].OrderStatus_Fork = WORK_STATUS_FAIL;
				}
			}

			if (m_BKSram.WorkInfo.WorkSt[i].WorkNum_Move == 0)
			{
				memset((INT08U*)&m_BKSram.WorkInfo.WorkSt[i].To_Cell_Move, 0, sizeof(CellPosSTR));

				m_BKSram.WorkInfo.WorkSt[i].OrderStatus_Move = 0;
				m_BKSram.WorkInfo.WorkSt[i].OrderProcess_Move = 0;
			}
			else
			{
				if ((m_BKSram.WorkInfo.WorkSt[i].OrderStatus_Move == WORK_STATUS_NONE)
					|| (m_BKSram.WorkInfo.WorkSt[i].OrderStatus_Move == WORK_STATUS_COMPLETE))
				{
					asm volatile("NOP");
				}
				else
				{
					m_BKSram.WorkInfo.WorkSt[i].OrderStatus_Move = WORK_STATUS_FAIL;
				}
			}
		}

		// 		Set_TestStatus(DEBUG_STR_55, m_BKSram.WorkInfo.WorkSt[0].WorkNum_Move);
		// 		Set_TestStatus(DEBUG_STR_56, m_BKSram.WorkInfo.WorkSt[0].OrderStatus_Move);
		// 		Set_TestStatus(DEBUG_STR_57, m_BKSram.WorkInfo.WorkSt[0].OrderProcess_Move);

		memcpy((INT08U*)&m_St.ForkWork[0], (INT08U*)&m_BKSram.WorkInfo.WorkSt[0], sizeof(WorkInfoSTR) * 2);
	}

	loadBKSramSTR();
}

/**
* @brief
* @param none
* @retval None
*/
void Load_BackupSRAM()
{
#if DEBUG_MSG
	printf("[BACKUP_SRAM] Total Data Size : %d Bytes.\n\r", sizeof(BKSRamSTR));
	//printf("[BACKUP_SRAM] Alarm Log Data Size : %d Bytes.\n\r", sizeof(AlarmLogSTR_Type1));
	printf("[BACKUP_SRAM] Operation Information Data Size : %d Bytes.\n\r", sizeof(OperationInfoSTR));
#endif

	loadBKSramSTR();

	if (checkFusingString((INT08U*)m_BKSram.InitOperInfoCode, (INT08U*)BK_OPERATION_INFO_INIT_CODE, 4))
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Operation Information Empty. Clear Data.\n\r");
#endif
		memcpy(m_BKSram.InitOperInfoCode, BK_OPERATION_INFO_INIT_CODE, 4);
		saveBKSramBlock((INT08U*)m_BKSram.InitOperInfoCode, sizeof(INT08U) * 4);

		memset((INT08U*)&m_BKSram.OperationInfo, 0x00, sizeof(OperationInfoSTR));
		saveBKSramBlock((INT08U*)&m_BKSram.OperationInfo, sizeof(OperationInfoSTR));
		//saveBKSramSTR();
		asm volatile("NOP");
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Check Operation Information.\n\r");
#endif
	}

	Graph_Setup_Init();

	Recovery_Work_Info();

	//m_TestStatus.Ctrl[DEBUG_CTR_15] = sizeof(BKSRamSTR);
	//m_TestStatus.Ctrl[DEBUG_CTR_16] = sizeof(UniLogSTR);
}

/**
* @brief Initialize value
* @param none
* @retval None
*/
void initValue(void)
{
	memset((INT08U*)&m_St, 0x00, sizeof(StatusSTR));
	memset((INT08U*)&m_DevStatus, 0x00, sizeof(DevStatusSTR));
	memset((INT08U*)&m_TxUartQ[0], 0x00, sizeof(UartQSTR) * MAX_UART_PORT);
	memset((INT08U*)&m_RxUartQ[0], 0x00, sizeof(UartQSTR) * MAX_UART_PORT);
	memset((INT08U*)&m_TestStatus, 0x00, sizeof(TestStatusSTR));

	__HAL_TIM_ENABLE(&htim3);
	__HAL_TIM_ENABLE_IT(&htim3, TIM_IT_UPDATE);

	// 	m_TestStatus.Ctrl[DEBUG_CTR_1] = sizeof(m_BKSram);
	// 	m_TestStatus.Ctrl[DEBUG_CTR_2] = sizeof(AlarmLogSTR);
	asm volatile("NOP");

	Load_BackupSRAM();
	Load_ExtFlash_Setting();

	m_DevStatus.SysTime = getTimeDate_Rev2();

	m_St.CP_Mode = CP_MODE_MANUAL;
	m_pgmEnv.OrderRejectCondition = 0;

	m_St.ProtocolVer = 0x30;
	m_DevStatus.ProtocolVer = m_St.ProtocolVer;
	checkVerStr((INT08U*)m_DevStatus.PgmVer, FW_VERSION);     // Ver1.1 - 090723   =>  0x10 0x09 0x07 0x23

#if DEBUG_MSG
	printf("[DEBUG_APP] Protocol Ver : %02x, FW Ver : %02x(%02x%02x%02x)\n\r",
		m_DevStatus.ProtocolVer, m_DevStatus.PgmVer[0], m_DevStatus.PgmVer[1], m_DevStatus.PgmVer[2], m_DevStatus.PgmVer[3]);
#endif
	memcpy((INT08U*)m_DevStatus.BootPgmVer, (INT08U*)m_BKSram.BootPgmVer, sizeof(INT08U) * 4);

	memcpy(m_St.PgmVer, m_DevStatus.PgmVer, sizeof(INT08U) * 4);

	m_pgmEnv.DeviceType = COM_ID_SRM;

	m_pgmEnv.DeviceID = m_ExtSEnv.mDevice.ProjectID.Device_ID;
	m_pgmEnv.TmlConnect = 0;

	INT08U out_data = 0;
	HAL_SRAM_Write_8b(&hsram3, (INT32U*)ADDR_FSMC_IOCS_FND, &out_data, 1);

	clearGraph();

	if (checkFusingString((INT08U*)m_ExtSEnv.mDevice.ProjectID.ProjectNo, (INT08U*)HANKOOK_TIRE_TP2, 6) == 0)
	{
		m_pgmEnv.Fork_Encoder_Type = FORK_ENC_ABSOLUTE;
		//m_pgmEnv.Fork_Brake_Type = FORK_BRAKE_MC;
		m_pgmEnv.Fork_Brake_Type = FORK_BRAKE_SEW;
	}
	else
	{
		m_pgmEnv.Fork_Encoder_Type = m_ExtSEnv.Machine.mType.Fork_Encoder_Type;
		m_pgmEnv.Fork_Brake_Type = FORK_BRAKE_SEW;
	}

	if (checkFusingString((INT08U*)m_ExtSEnv.mDevice.ProjectID.ProjectNo, (INT08U*)HANKOOK_TIRE_TP2, 6) == 0)
	{
		if (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_TREAD)
		{
			m_pgmEnv.InterlockMode = ST_INTERLOCK_MODE_HANKOOK_TIRE_TP2_DIR;
		}
		else if (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_TREAD)
		{
			m_pgmEnv.InterlockMode = ST_INTERLOCK_MODE_HANKOOK_TIRE_TP2_DIR;
		}
		else if ((m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_GT_LOT4) \
			|| (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_GT_LOT3) \
			|| (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_GT_LOT2) \
			|| (m_ExtSEnv.mDevice.ProjectID.Group_ID == HANKOOK_TIRE_TP2_PCR_GT_LOT1))
		{
			m_pgmEnv.InterlockMode = ST_INTERLOCK_MODE_HANKOOK_TIRE_TP2_FlOOR_NO;
		}
		else
		{
			m_pgmEnv.InterlockMode = ST_INTERLOCK_MODE_HANKOOK_TIRE_TP2_DIR;
		}
	}
	else
	{
		m_pgmEnv.InterlockMode = ST_INTERLOCK_MODE_0;
	}

	m_pgmEnv.Test_Simulator.DI_Test_Mode = DI_TEST_NONE;
	Update_Maintanance_SRM_Setting_Data();

	Reset_Add_AlarmLog();

	Set_TestStatus(DEBUG_STR_63, sizeof(DIO_SetComSTR));
	Set_TestStatus(DEBUG_STR_64, sizeof(DIO_SetSTR));
}

/**
  * @brief Refresh watchdog
  * @param none
  * @retval None
  */
void WatchDog(void)
{
	HAL_IWDG_Refresh(&hiwdg);
}

/// @brief      Obtain the STM32 system reset cause
/// @param      None
/// @return     The system reset cause
reset_cause_t reset_cause_get(void)
{
	reset_cause_t reset_cause = 0;

	if (__HAL_RCC_GET_FLAG(RCC_FLAG_LPWRRST))
	{
		reset_cause = RESET_CAUSE_LOW_POWER_RESET;
	}
	else if (__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST))
	{
		reset_cause = RESET_CAUSE_WINDOW_WATCHDOG_RESET;
	}
	else if (__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST))
	{
		reset_cause = RESET_CAUSE_INDEPENDENT_WATCHDOG_RESET;
	}
	else if (__HAL_RCC_GET_FLAG(RCC_FLAG_SFTRST))
	{
		// This reset is induced by calling the ARM CMSIS 
		// `NVIC_SystemReset()` function!
		reset_cause = RESET_CAUSE_SOFTWARE_RESET;
	}
	else if (__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST))
	{
		reset_cause = RESET_CAUSE_POWER_ON_POWER_DOWN_RESET;
	}
	else if (__HAL_RCC_GET_FLAG(RCC_FLAG_PINRST))
	{
		reset_cause = RESET_CAUSE_EXTERNAL_RESET_PIN_RESET;
	}
	// Needs to come *after* checking the `RCC_FLAG_PORRST` flag in order to
	// ensure first that the reset cause is NOT a POR/PDR reset. See note
	// below. 
	else if (__HAL_RCC_GET_FLAG(RCC_FLAG_BORRST))
	{
		reset_cause = RESET_CAUSE_BROWNOUT_RESET;
	}
	else
	{
		reset_cause = RESET_CAUSE_UNKNOWN;
	}

	// Clear all the reset flags or else they will remain set during future
	// resets until system power is fully removed.
	__HAL_RCC_CLEAR_RESET_FLAGS();

	return reset_cause;
}

void Reset_Add_AlarmLog(void)
{
	INT08U Reset_Reason = 0;

	Reset_Reason = m_BKSram.Reset_Reason;

	add_alarm_log(0, 1, Reset_Reason);   // Reset Event Log : MainCode, SubCode, Value
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	  /* ★ DTCM 초기화 — HAL_Init() 전에 실행 */

	  /* 외부 심볼 선언 (링커 스크립트에서 정의) */
	extern uint32_t _sdtcm_bss;
	extern uint32_t _edtcm_bss;

	/* ★ dtcm_data 복사 코드 제거 */

	/* DTCM BSS Zero 초기화만 유지 */
	uint32_t* pDst = &_sdtcm_bss;
	while (pDst < &_edtcm_bss)
	{
		*pDst++ = 0;
	}
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	SCB->VTOR = DOWN_PGM_IN_FLASH_START_SECTOR_ADDR;		// Relocate NVIC Vector table
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
	MPU_Config();

	//MX_LWIP_Init() 주석처리해야 함. 주석으로 처리하지 않으면, Uplink 이더넷 동작하지 않음.
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_RTC_Init();
  MX_USART3_UART_Init();
  MX_TIM3_Init();
  MX_FMC_Init();
  MX_USART6_UART_Init();
  MX_SPI2_Init();
  MX_LWIP_Init();
  MX_TIM2_Init();
  MX_USB_HOST_Init();
  MX_FATFS_Init();
  MX_UART4_Init();
  MX_TIM4_Init();
  MX_IWDG_Init();
  MX_CAN1_Init();
  /* USER CODE BEGIN 2 */
#if DEBUG_MSG
	printf("\r\n");
	printf("[DEBUG_APP] Start Application\n\r");
#endif
	sst_init();

	initProgram();

	initValue();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
		AlarmManager(); //DI/DO, 에러, SAVE_* 트리거

		FpgaManager(); //FPGA, Ethercat 통신

		McuComManager(); //MCU 보조 통신

		TMLComManager(); //지상반 UART 수신/송신

		EtherNetManager(); // 이더넷

		ECAT_Manager(); //인버터 PDO 갱신

		//DSP_ComManager();

		//HT100_Manager();

		if (m_pgmEnv.downloadMode)
		{
			checkDownload();
		}
		else
		{
			SRM_Manager(); //SRM 제어 진입
			/*
			 * SRM_Machine_Process() // SSR/연결 등
			 * SRM_Machine_Run_Process() // 상태머신 본체
			 * HMI_ModbusTCP_Proc()
			 * */
			MCU_Test_Manager();
		}

    /* USER CODE END WHILE */
    MX_USB_HOST_Process();

    /*
     *0x41 WorkCmdSTR -> rx CmdOrder() -> Store_Work_Data*() -> m_WorkData[s_WorkInx]  입력층
     *SRM_Machine_Run_Process() Switch문 -> m_pgmEnv.SRM_RunMode (enumSRM_RUN_SEQ)      실행층
     *                                  -> m_pgmEnv.SRM_RunTimer                       실행층
     *                                  -> Sub_Run_Step (축별 서브시퀀스)                  실행층
     *Save_RokWork_*() / Save_ForkMove_*() -> m_St (StatusSTR) -> 0x30 응답              출력층
     *save_error_code() -> m_St 에러 + m_BKSram.AlarmLog                                 출력층
     * */


    /* USER CODE BEGIN 3 */
#if ENABLE_WATCHDOG
		WatchDog();
#endif
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE
                              |RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */
	CAN_FilterTypeDef  sFilterConfig;
  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 6;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_7TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_1TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = ENABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */
	sFilterConfig.FilterBank = 0;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh = 0x0000;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = 0x0000;
	sFilterConfig.FilterMaskIdLow = 0x0000;
	sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.SlaveStartFilterBank = 14;

	if (HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK)
	{
		/* Filter configuration Error */
		Error_Handler();
	}

	/*##-3- Start the CAN peripheral ###########################################*/
	if (HAL_CAN_Start(&hcan1) != HAL_OK)
	{
		/* Start Error */
		Error_Handler();
	}

	/*##-4- Activate CAN RX notification #######################################*/
	if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
	{
		/* Notification Error */
		Error_Handler();
	}
  /* USER CODE END CAN1_Init 2 */

}

/**
  * @brief IWDG Initialization Function
  * @param None
  * @retval None
  */
static void MX_IWDG_Init(void)
{

  /* USER CODE BEGIN IWDG_Init 0 */
#if ENABLE_WATCHDOG
  /* USER CODE END IWDG_Init 0 */

  /* USER CODE BEGIN IWDG_Init 1 */
			  // 32KHz Clock          0x000 ~ 0xFFF
			  // IWDG_Prescaler_4   : 0.125 ~    512ms
			  // IWDG_Prescaler_8   : 0.25  ~  1,024ms
			  // IWDG_Prescaler_16  : 0.5   ~  2,048ms
			  // IWDG_Prescaler_32  : 1     ~  4,096ms
			  // IWDG_Prescaler_64  : 2     ~  8,192ms
			  // IWDG_Prescaler_128 : 4     ~ 16,384ms
			  // IWDG_Prescaler_256 : 8     ~ 32,768ms
  /* USER CODE END IWDG_Init 1 */
  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_32;
  hiwdg.Init.Window = 4000;
  hiwdg.Init.Reload = 4000;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN IWDG_Init 2 */
#endif
  /* USER CODE END IWDG_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  /* USER CODE BEGIN RTC_Init 1 */
										//HAL_RTC_WaitForSynchro(&hrtc);
  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */
  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  LL_SPI_InitTypeDef SPI_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2);

  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
  /**SPI2 GPIO Configuration
  PB13   ------> SPI2_SCK
  PB14   ------> SPI2_MISO
  PB15   ------> SPI2_MOSI
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_13;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_5;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_14;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_5;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_15;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_5;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
  SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;
  SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;
  SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;
  SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
  SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;
  SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV8;
  SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;
  SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;
  SPI_InitStruct.CRCPoly = 7;
  LL_SPI_Init(SPI2, &SPI_InitStruct);
  LL_SPI_SetStandard(SPI2, LL_SPI_PROTOCOL_MOTOROLA);
  LL_SPI_DisableNSSPulseMgt(SPI2);
  /* USER CODE BEGIN SPI2_Init 2 */
	LL_SPI_SetRxFIFOThreshold(SPIx, LL_SPI_RX_FIFO_TH_QUARTER);
	LL_SPI_Enable(SPIx);

	init_FlashSst26();
  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 0;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 0;
  if (HAL_TIM_Encoder_Init(&htim2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */
																	  // TIMER3 APB1 Timer Clocks : 108Mhz
																	  // UpdateEvnet = Timer_CLK / (Prescaler + 1) * (Preiod + 1)
																	  // 1Hz = 1s, 10Hz = 100ms, .... 10000Hz = 100us
  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = (108 - 1);
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = (100 - 1);
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */
	__HAL_TIM_ENABLE(&htim3);
	__HAL_TIM_ENABLE_IT(&htim3, TIM_IT_UPDATE);
  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = (108 - 1);
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = (2000 - 1);
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  huart4.Instance = UART4;
  huart4.Init.BaudRate = 115200;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  huart4.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart4.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

													  //__HAL_UART_ENABLE_IT(&huart3, UART_IT_RXNE);

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 115200;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  huart6.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart6.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_RXOVERRUNDISABLE_INIT|UART_ADVFEATURE_DMADISABLEONERROR_INIT;
  huart6.AdvancedInit.OverrunDisable = UART_ADVFEATURE_OVERRUN_DISABLE;
  huart6.AdvancedInit.DMADisableonRxError = UART_ADVFEATURE_DMA_DISABLEONRXERROR;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */

  /* USER CODE END USART6_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream3_IRQn);

}

/* FMC initialization function */
static void MX_FMC_Init(void)
{

  /* USER CODE BEGIN FMC_Init 0 */

  /* USER CODE END FMC_Init 0 */

  FMC_NORSRAM_TimingTypeDef Timing = {0};

  /* USER CODE BEGIN FMC_Init 1 */

  /* USER CODE END FMC_Init 1 */

  /** Perform the SRAM1 memory initialization sequence
  */
  hsram1.Instance = FMC_NORSRAM_DEVICE;
  hsram1.Extended = FMC_NORSRAM_EXTENDED_DEVICE;
  /* hsram1.Init */
  hsram1.Init.NSBank = FMC_NORSRAM_BANK1;
  hsram1.Init.DataAddressMux = FMC_DATA_ADDRESS_MUX_DISABLE;
  hsram1.Init.MemoryType = FMC_MEMORY_TYPE_SRAM;
  hsram1.Init.MemoryDataWidth = FMC_NORSRAM_MEM_BUS_WIDTH_8;
  hsram1.Init.BurstAccessMode = FMC_BURST_ACCESS_MODE_DISABLE;
  hsram1.Init.WaitSignalPolarity = FMC_WAIT_SIGNAL_POLARITY_LOW;
  hsram1.Init.WaitSignalActive = FMC_WAIT_TIMING_BEFORE_WS;
  hsram1.Init.WriteOperation = FMC_WRITE_OPERATION_ENABLE;
  hsram1.Init.WaitSignal = FMC_WAIT_SIGNAL_DISABLE;
  hsram1.Init.ExtendedMode = FMC_EXTENDED_MODE_DISABLE;
  hsram1.Init.AsynchronousWait = FMC_ASYNCHRONOUS_WAIT_DISABLE;
  hsram1.Init.WriteBurst = FMC_WRITE_BURST_DISABLE;
  hsram1.Init.ContinuousClock = FMC_CONTINUOUS_CLOCK_SYNC_ONLY;
  hsram1.Init.WriteFifo = FMC_WRITE_FIFO_ENABLE;
  hsram1.Init.PageSize = FMC_PAGE_SIZE_NONE;
  /* Timing */
  Timing.AddressSetupTime = 15;
  Timing.AddressHoldTime = 15;
  Timing.DataSetupTime = 15;
  Timing.BusTurnAroundDuration = 15;
  Timing.CLKDivision = 16;
  Timing.DataLatency = 17;
  Timing.AccessMode = FMC_ACCESS_MODE_A;
  /* ExtTiming */

  if (HAL_SRAM_Init(&hsram1, &Timing, NULL) != HAL_OK)
  {
    Error_Handler( );
  }

  /** Perform the SRAM3 memory initialization sequence
  */
  hsram3.Instance = FMC_NORSRAM_DEVICE;
  hsram3.Extended = FMC_NORSRAM_EXTENDED_DEVICE;
  /* hsram3.Init */
  hsram3.Init.NSBank = FMC_NORSRAM_BANK3;
  hsram3.Init.DataAddressMux = FMC_DATA_ADDRESS_MUX_DISABLE;
  hsram3.Init.MemoryType = FMC_MEMORY_TYPE_SRAM;
  hsram3.Init.MemoryDataWidth = FMC_NORSRAM_MEM_BUS_WIDTH_8;
  hsram3.Init.BurstAccessMode = FMC_BURST_ACCESS_MODE_DISABLE;
  hsram3.Init.WaitSignalPolarity = FMC_WAIT_SIGNAL_POLARITY_LOW;
  hsram3.Init.WaitSignalActive = FMC_WAIT_TIMING_BEFORE_WS;
  hsram3.Init.WriteOperation = FMC_WRITE_OPERATION_ENABLE;
  hsram3.Init.WaitSignal = FMC_WAIT_SIGNAL_DISABLE;
  hsram3.Init.ExtendedMode = FMC_EXTENDED_MODE_DISABLE;
  hsram3.Init.AsynchronousWait = FMC_ASYNCHRONOUS_WAIT_DISABLE;
  hsram3.Init.WriteBurst = FMC_WRITE_BURST_DISABLE;
  hsram3.Init.ContinuousClock = FMC_CONTINUOUS_CLOCK_SYNC_ONLY;
  hsram3.Init.WriteFifo = FMC_WRITE_FIFO_ENABLE;
  hsram3.Init.PageSize = FMC_PAGE_SIZE_NONE;
  /* Timing */
  Timing.AddressSetupTime = 15;
  Timing.AddressHoldTime = 15;
  Timing.DataSetupTime = 15;
  Timing.BusTurnAroundDuration = 15;
  Timing.CLKDivision = 16;
  Timing.DataLatency = 17;
  Timing.AccessMode = FMC_ACCESS_MODE_A;
  /* ExtTiming */

  if (HAL_SRAM_Init(&hsram3, &Timing, NULL) != HAL_OK)
  {
    Error_Handler( );
  }

  /* USER CODE BEGIN FMC_Init 2 */

  /* USER CODE END FMC_Init 2 */
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ETH_PWR_DOWN_Pin|ETH_RESET_Pin|GPIO_PIN_10, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CPU_RUN_LED_GPIO_Port, CPU_RUN_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SFlash_HOLD_GPIO_Port, SFlash_HOLD_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SFlash_WP_GPIO_Port, SFlash_WP_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SFlash_CE_GPIO_Port, SFlash_CE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(OUT_ENB_GPIO_Port, OUT_ENB_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(FPGA_RESET_GPIO_Port, FPGA_RESET_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : ETH_PWR_DOWN_Pin ETH_RESET_Pin */
  GPIO_InitStruct.Pin = ETH_PWR_DOWN_Pin|ETH_RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : ETH_LINK_IN_Pin USB_OTG_FAULT_Pin */
  GPIO_InitStruct.Pin = ETH_LINK_IN_Pin|USB_OTG_FAULT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : BOOT1_Pin */
  GPIO_InitStruct.Pin = BOOT1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BOOT1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : CPU_RUN_LED_Pin */
  GPIO_InitStruct.Pin = CPU_RUN_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CPU_RUN_LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SFlash_HOLD_Pin */
  GPIO_InitStruct.Pin = SFlash_HOLD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SFlash_HOLD_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SFlash_WP_Pin */
  GPIO_InitStruct.Pin = SFlash_WP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(SFlash_WP_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SFlash_CE_Pin */
  GPIO_InitStruct.Pin = SFlash_CE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SFlash_CE_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PA10 */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : SD_DET_Pin */
  GPIO_InitStruct.Pin = SD_DET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(SD_DET_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : OUT_ENB_Pin */
  GPIO_InitStruct.Pin = OUT_ENB_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(OUT_ENB_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : FPGA_RESET_Pin */
  GPIO_InitStruct.Pin = FPGA_RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(FPGA_RESET_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : FPGA_INT_Pin */
  GPIO_InitStruct.Pin = FPGA_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(FPGA_INT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : CPU_FPGA_GPIO1_Pin */
  GPIO_InitStruct.Pin = CPU_FPGA_GPIO1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(CPU_FPGA_GPIO1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : CPU_FPGA_GPIO2_Pin */
  GPIO_InitStruct.Pin = CPU_FPGA_GPIO2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(CPU_FPGA_GPIO2_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim)
{
	volatile static INT08U s_TempCnt = 0;

	if (htim->Instance == TIM3)
	{
		//HAL_GPIO_TogglePin(CPU_RUN_LED_GPIO_Port, CPU_RUN_LED_Pin);

		++m_pgmEnv.timer100us;

		if (++s_TempCnt > 9)
		{
			//HAL_GPIO_TogglePin(CPU_RUN_LED_GPIO_Port, CPU_RUN_LED_Pin);
			s_TempCnt = 0;
			m_pgmEnv.timer1ms++;
		}
	}
	else if (htim->Instance == TIM4)
	{
		ECAT_Com_Process();
	}
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef * huart)
{
	if (huart->Instance == USART3)
	{
		/* Error Handling */
		HAL_UART_DeInit(&huart3);
		MX_USART3_UART_Init();
		__HAL_UART_ENABLE_IT(&huart3, UART_IT_RXNE);
	}
	else if (huart->Instance == UART4)
	{
		HAL_UART_DeInit(&huart4);
		MX_UART4_Init();
		__HAL_UART_ENABLE_IT(&huart4, UART_IT_RXNE);
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
													  /* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
													  /* User can add his own implementation to report the file name and line number,
														 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
