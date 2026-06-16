/*
 * SRM_Parameter.c
 *
 *  Created on: 2022. 10. 26.
 *      Author: ARTWARE
 */

#include "uart.h"
#include "alarm.h"
#include "upgrade.h"
#include "dev_SRM.h"

#include "FlashSST26.h"

#include "SRM_Parameter.h"
#include "rtc.h"

extern void WatchDog(void);

/**
 * @brief
 * @param DeviceSetting
 * @retval None
 */
void BackUp_Device_Parameter(DeviceSetting* pSet)
{
	// 2024. 8. 29
	// FW 다운로드 시작 시, extFlash 초기화되는 문제 발생 시 기본정보 삭제.
	// BackUpSRAM에 설정 백업.
	memcpy((INT08U*)m_BKSram.InitDeviceCode, DEVICE_INIT_CODE, sizeof(INT08U) * 4);
	memcpy((INT08U*)&m_BKSram.mDevice, (INT08U*)pSet, sizeof(DeviceSetting));

	saveBKSramBlock((INT08U*)m_BKSram.InitDeviceCode, sizeof(DeviceSetting) + (sizeof(INT08U) * 4));
}

/**
 * @brief
 * @param
 * @retval None
 * 변경 시, App,Boot 소스 초기화 코드도 변경해야 함.
 */
void Default_Device_Setting()
{
	/*
	INT08U my_ip[3][4] = { { 192, 168, 100, 20 },
							{ 192, 168, 10, 3 },
							{ 192, 168, 10, 10 } };
	*/
	INT08U my_ip[3][4] = { { 192, 168, 100, 16 },		// Uplink
							{ 192, 168, 10, 3 },		// Dowlink
							{ 192, 168, 10, 10 } };		// EtherCAT

	INT08U subnet[3][4] = { { 255, 255, 255, 0 },
							{ 255, 255, 255, 0 },
							{ 255, 255, 255, 0 } };

	INT08U gateway[3][4] = { { 192, 168, 100, 1 },
							{ 192, 168, 10, 1 },
							{ 192, 168, 10, 1 } };

	/*
	INT08U my_mac[3][6] = { { 0x00, 0x0A, 0x1F, 0x00, 0x01, 0x02 },
							{ 0x00, 0x0A, 0x1F, 0x00, 0x01, 0x03 },
							{ 0x00, 0x0A, 0x1F, 0x00, 0x01, 0x04 } };
	*/

	INT08U my_mac[3][6] = { { 0x00, 0x0A, 0x1F, 0x00, 0x01, 0x05 },
							{ 0x00, 0x0A, 0x1F, 0x00, 0x01, 0x06 },
							{ 0x00, 0x0A, 0x1F, 0x00, 0x01, 0x07 } };
	
	INT08U ProjectNo[6] = { 'A','0','0','0','0','1' };

	INT16U crc = 0x0000;

	ExtFlash_ReadData(EXT_DEVICE_SET_ADDR_START, (INT08U*)&m_ExtSEnv, sizeof(ExtFlashSEnv));

	memcpy(m_ExtSEnv.InitDeviceCode, DEVICE_INIT_CODE, 4);

	memcpy((INT08U*)m_ExtSEnv.mDevice.NetworkInfo_0.MyIP, (INT08U*)&my_ip[0], sizeof(INT08U) * 4);
	memcpy((INT08U*)m_ExtSEnv.mDevice.NetworkInfo_0.SubnetMask, (INT08U*)&subnet[0], sizeof(INT08U) * 4);
	memcpy((INT08U*)m_ExtSEnv.mDevice.NetworkInfo_0.GatewayIP, (INT08U*)&gateway[0], sizeof(INT08U) * 4);

	memcpy((INT08U*)m_ExtSEnv.mDevice.NetworkInfo_1.MyIP, (INT08U*)&my_ip[1], sizeof(INT08U) * 4);
	memcpy((INT08U*)m_ExtSEnv.mDevice.NetworkInfo_1.SubnetMask, (INT08U*)&subnet[1], sizeof(INT08U) * 4);
	memcpy((INT08U*)m_ExtSEnv.mDevice.NetworkInfo_1.GatewayIP, (INT08U*)&gateway[1], sizeof(INT08U) * 4);

	memcpy((INT08U*)m_ExtSEnv.mDevice.NetworkInfo_2.MyIP, (INT08U*)&my_ip[2], sizeof(INT08U) * 4);
	memcpy((INT08U*)m_ExtSEnv.mDevice.NetworkInfo_2.SubnetMask, (INT08U*)&subnet[2], sizeof(INT08U) * 4);
	memcpy((INT08U*)m_ExtSEnv.mDevice.NetworkInfo_2.GatewayIP, (INT08U*)&gateway[2], sizeof(INT08U) * 4);

	memcpy((INT08U*)m_ExtSEnv.mDevice.MyMACAddr_0, (INT08U*)&my_mac[0], sizeof(INT08U) * 6);
	memcpy((INT08U*)m_ExtSEnv.mDevice.MyMACAddr_1, (INT08U*)&my_mac[1], sizeof(INT08U) * 6);
	memcpy((INT08U*)m_ExtSEnv.mDevice.MyMACAddr_2, (INT08U*)&my_mac[2], sizeof(INT08U) * 6);

	memcpy((INT08U*)m_ExtSEnv.mDevice.ProjectID.ProjectNo, (INT08U*)ProjectNo, sizeof(INT08U) * 6);

	m_ExtSEnv.mDevice.ProjectID.Group_ID = 1;
	m_ExtSEnv.mDevice.ProjectID.Device_ID = 1;

	m_ExtSEnv.CheckCRC_Device = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv.mDevice, sizeof(DeviceSetting));

	ExtFlash_WriteData(EXT_DEVICE_SET_ADDR_START, (INT08U*)&m_ExtSEnv, sizeof(ExtFlashSEnv));
	asm volatile("NOP");

	BackUp_Device_Parameter(&m_ExtSEnv.mDevice);
}

/**
 * @brief
 * @param DeviceSetting
 * @retval None
 */
INT08U Set_Device_Parameter(DeviceSetting* pSet)
{
	INT16U crc = 0x0000;

	ExtFlash_ReadData(EXT_DEVICE_SET_ADDR_START, (INT08U*)&m_ExtSEnv, sizeof(ExtFlashSEnv));

	if (memcmp((INT08U*)&m_ExtSEnv.mDevice, (INT08U*)&pSet->NetworkInfo_0, sizeof(DeviceSetting)))
	{
		memcpy(m_ExtSEnv.InitDeviceCode, DEVICE_INIT_CODE, 4);

		memcpy((INT08U*)&m_ExtSEnv.mDevice.NetworkInfo_0, (INT08U*)&pSet->NetworkInfo_0, sizeof(NetworkInfo_t));
		memcpy((INT08U*)&m_ExtSEnv.mDevice.NetworkInfo_1, (INT08U*)&pSet->NetworkInfo_1, sizeof(NetworkInfo_t));
		//memcpy((INT08U*)&m_ExtSEnv.mDevice.NetworkInfo_2, (INT08U*)&pSet->NetworkInfo_2, sizeof(NetworkInfo_t));

		memcpy((INT08U*)m_ExtSEnv.mDevice.MyMACAddr_0, (INT08U*)pSet->MyMACAddr_0, sizeof(INT08U) * 6);
		memcpy((INT08U*)m_ExtSEnv.mDevice.MyMACAddr_1, (INT08U*)pSet->MyMACAddr_1, sizeof(INT08U) * 6);
		//memcpy((INT08U*)m_ExtSEnv.mDevice.MyMACAddr_2, (INT08U*)pSet->MyMACAddr_2, sizeof(INT08U) * 6);

		memcpy((INT08U*)m_ExtSEnv.mDevice.ProjectID.ProjectNo, (INT08U*)&pSet->ProjectID, sizeof(ProjectID_t));

		memcpy((INT08U*)&m_DevStatus.NetworkInfo_0, (INT08U*)&m_ExtSEnv.mDevice.NetworkInfo_0, sizeof(NetworkInfo_t));
		memcpy((INT08U*)&m_DevStatus.NetworkInfo_1, (INT08U*)&m_ExtSEnv.mDevice.NetworkInfo_1, sizeof(NetworkInfo_t));
		//memcpy((INT08U*)&m_DevStatus.NetworkInfo_2, (INT08U*)&m_ExtSEnv.mDevice.NetworkInfo_2, sizeof(NetworkInfo_t));

		memcpy((INT08U*)m_DevStatus.MyMACAddr_0, (INT08U*)m_ExtSEnv.mDevice.MyMACAddr_0, sizeof(INT08U) * 6);
		memcpy((INT08U*)m_DevStatus.MyMACAddr_1, (INT08U*)m_ExtSEnv.mDevice.MyMACAddr_1, sizeof(INT08U) * 6);
		//memcpy((INT08U*)m_DevStatus.MyMACAddr_2, (INT08U*)m_ExtSEnv.mDevice.MyMACAddr_2, sizeof(INT08U) * 6);

		memcpy((INT08U*)&m_DevStatus.ProjectID, (INT08U*)&m_ExtSEnv.mDevice.ProjectID, sizeof(ProjectID_t));

		m_ExtSEnv.CheckCRC_Device = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv.mDevice, sizeof(DeviceSetting));

		ExtFlash_WriteData(EXT_DEVICE_SET_ADDR_START, (INT08U*)&m_ExtSEnv, sizeof(ExtFlashSEnv));

		BackUp_Device_Parameter(&m_ExtSEnv.mDevice);
#if DEBUG_MSG
		printf("[DEBUG_APP] Device Setting save to external flash. DataCRC: 0x%04x\r\n", m_ExtSEnv.CheckCRC_Device);
#endif
		return 1;
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Device Setting same setting. Do not save in external flash.\r\n");
#endif

		return 0;
	}
}

/**
  * @brief
  * @param None
  * @retval None
  */
void Device_Setting_Init()
{
	INT16U crc = 0x0000;

	ExtFlash_ReadData(EXT_DEVICE_SET_ADDR_START, (INT08U*)&m_ExtSEnv, sizeof(ExtFlashSEnv));

	if (checkFusingString((INT08U*)m_ExtSEnv.InitDeviceCode, (INT08U*)DEVICE_INIT_CODE, 4))
	{
		// Check BackUp
		if (checkFusingString((INT08U*)m_BKSram.InitDeviceCode, (INT08U*)DEVICE_INIT_CODE, 4))
		{
#if DEBUG_MSG
			printf("[DEBUG_APP] Device Setting Empty. Write Default Setting.\n\r");
#endif
			save_error_code(ERROR1_MCU_PARAM_DATA, 1, 1);
			Default_Device_Setting();
		}
		else
		{
			//save_error_code(ERROR1_MCU_PARAM_DATA, 1, 2);
			Set_Device_Parameter(&m_BKSram.mDevice);
		}
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Checked Device Setting.\n\r");
#endif

		crc = 0x0000;
		crc = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv.mDevice, sizeof(DeviceSetting));
		if (m_ExtSEnv.CheckCRC_Device != crc)
		{
#if DEBUG_MSG
			printf("[DEBUG_APP] Not equal CRC Device config. Write Default Setting.\n\r");
#endif
			if (checkFusingString((INT08U*)m_BKSram.InitDeviceCode, (INT08U*)DEVICE_INIT_CODE, 4))
			{
#if DEBUG_MSG
				printf("[DEBUG_APP] Device Setting Empty. Write Default Setting.\n\r");
#endif
				save_error_code(ERROR1_MCU_PARAM_DATA, 1, 2);
				Default_Device_Setting();
			}
			else
			{
				Set_Device_Parameter(&m_BKSram.mDevice);
			}

			//save_error_code(ERROR1_MCU_PARAM_DATA, 1, 0);

			//Default_Device_Setting();
		}
		else
		{
#if DEBUG_MSG
			printf("[DEBUG_APP] Equal CRC Device config. DataCrc: 0x%04x CalcCRC: 0x%04x\n\r",
				m_ExtSEnv.CheckCRC_Device, crc);
#endif
		}
	}

	// Check BackUp
	if (checkFusingString((INT08U*)m_BKSram.InitDeviceCode, (INT08U*)DEVICE_INIT_CODE, 4))
	{
		// 2024. 8. 29
		// FW 다운로드 시작 시, extFlash 초기화되는 문제 발생 시 기본정보 삭제.
		// BackUpSRAM에 설정 백업.
		memcpy((INT08U*)m_BKSram.InitDeviceCode, DEVICE_INIT_CODE, sizeof(INT08U) * 4);
		memcpy((INT08U*)&m_BKSram.mDevice, (INT08U*)&m_ExtSEnv.mDevice, sizeof(DeviceSetting));

		saveBKSramBlock((INT08U*)m_BKSram.InitDeviceCode, sizeof(DeviceSetting) + (sizeof(INT08U) * 4));
	}

	memcpy((INT08U*)&m_DevStatus.NetworkInfo_0, (INT08U*)&m_ExtSEnv.mDevice.NetworkInfo_0, sizeof(NetworkInfo_t));
	memcpy((INT08U*)&m_DevStatus.NetworkInfo_1, (INT08U*)&m_ExtSEnv.mDevice.NetworkInfo_1, sizeof(NetworkInfo_t));
	//memcpy((INT08U*)&m_DevStatus.NetworkInfo_2, (INT08U*)&m_ExtSEnv.mDevice.NetworkInfo_2, sizeof(NetworkInfo_t));

	memcpy((INT08U*)m_DevStatus.MyMACAddr_0, (INT08U*)m_ExtSEnv.mDevice.MyMACAddr_0, sizeof(INT08U) * 6);
	memcpy((INT08U*)m_DevStatus.MyMACAddr_1, (INT08U*)m_ExtSEnv.mDevice.MyMACAddr_1, sizeof(INT08U) * 6);
	//memcpy((INT08U*)m_DevStatus.MyMACAddr_2, (INT08U*)m_ExtSEnv.mDevice.MyMACAddr_2, sizeof(INT08U) * 6);

	memcpy((INT08U*)&m_DevStatus.ProjectID, (INT08U*)&m_ExtSEnv.mDevice.ProjectID, sizeof(ProjectID_t));

	memcpy((INT08U*)&m_St.ProjectID, (INT08U*)&m_ExtSEnv.mDevice.ProjectID, sizeof(ProjectID_t));

#if FW_DEBUG
	if (m_ExtSEnv.DebugMode != 1)
	{
		m_ExtSEnv.DebugMode = 1;

		ExtFlash_WriteData(EXT_DEVICE_SET_ADDR_START, (INT08U*)&m_ExtSEnv, sizeof(ExtFlashSEnv));
	}
#else
	if (m_ExtSEnv.DebugMode != 0)
	{
		m_ExtSEnv.DebugMode = 0;

		ExtFlash_WriteData(EXT_DEVICE_SET_ADDR_START, (INT08U*)&m_ExtSEnv, sizeof(ExtFlashSEnv));
	}
#endif
}

/**
 * @brief
 * @param
 * @retval None
 */
void Default_MachineType_Setting()
{
	INT08U Dsp_default_ip[2][4] = {
								{ 192, 168, 100, 20 },
								{ 192, 168, 100, 21 }
	};

	INT16U crc = 0x0000;

	ExtFlash_ReadData(EXT_DEVICE_SET_ADDR_START, (INT08U*)&m_ExtSEnv, sizeof(ExtFlashSEnv));

	memcpy(m_ExtSEnv.InitMachineCode, MACHINE_TYPE_INIT_CODE, 4);

	m_ExtSEnv.Machine.mType.Fork_Count = 1;
	m_ExtSEnv.Machine.mType.Drive_Invertor_Count = 2;
	m_ExtSEnv.Machine.mType.Drive_Type = 1;
	m_ExtSEnv.Machine.mType.Fork_Type = FORK_TYPE_SINGLE_DEEP;
	m_ExtSEnv.Machine.mType.Inverter_Vendor = INV_VENDOR_SEW;
	m_ExtSEnv.Machine.mType.Fork_Drive_Type = 2;				/*!< 포크 인버터 구동방식 - 1:주행/승강인버터 공용, 2:별도 구성	*/ 
	m_ExtSEnv.Machine.mType.Fork_Sensor_Type = 0;
	m_ExtSEnv.Machine.mType.Drive_Sensor_Type = 0;
	m_ExtSEnv.Machine.mType.Lift_Sensor_Type = 0;
	m_ExtSEnv.Machine.mType.Lamp_Type = 0;

	memset((INT08U*)m_ExtSEnv.Machine.Reserved, 0x00, sizeof(INT08U) * 16);

	m_ExtSEnv.Machine.DSP_Set.Com_Type = 0;
	m_ExtSEnv.Machine.DSP_Set.Connect_Count = 0;

	for (INT08U i = 0; i < 2; i++)
	{
		memcpy((INT08U*)&m_ExtSEnv.Machine.DSP_Set.NetIf[i].IP, (INT08U*)&Dsp_default_ip[i], sizeof(INT08U) * 4);
		m_ExtSEnv.Machine.DSP_Set.NetIf[i].Reserved = 0;
		//m_ExtSEnv.Machine.DSP_Set.NetIf[i].RemotePort = DEF_DSP_REMOTE_PORT;
	}

	m_ExtSEnv.CheckCRC_MachineType = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv.Machine, sizeof(SRM_Machine_Type));

	ExtFlash_WriteData(EXT_DEVICE_SET_ADDR_START, (INT08U*)&m_ExtSEnv, sizeof(ExtFlashSEnv));
}

/**
  * @brief
  * @param DeviceSetting
  * @retval None
  */
  //void Set_Machine_Parameter(SRM_Machine_Type* pSet)
  /*
  INT08U Set_Machine_Parameter(SRM_Machine_Type* pSet)
  {
	  INT16U crc = 0x0000;

	  ExtFlash_ReadData(EXT_DEVICE_SET_ADDR_START, (INT08U*)&m_ExtSEnv, sizeof(ExtFlashSEnv));

	  if (memcmp((INT08U*)&m_ExtSEnv.Machine, pSet, sizeof(SRM_Machine_Type)))
	  {
		  memcpy(m_ExtSEnv.InitMachineCode, MACHINE_TYPE_INIT_CODE, 4);

		  memcpy((INT08U*)&m_ExtSEnv.Machine, (INT08U*)pSet, sizeof(SRM_Machine_Type));

		  m_ExtSEnv.CheckCRC_MachineType = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv.Machine, sizeof(SRM_Machine_Type));

		  ExtFlash_WriteData(EXT_DEVICE_SET_ADDR_START, (INT08U*)&m_ExtSEnv, sizeof(ExtFlashSEnv));

  #if DEBUG_MSG
		  printf("[DEBUG_APP] Machine type save to external flash. DataCRC: 0x%04x\r\n", m_ExtSEnv.CheckCRC_MachineType);
  #endif
		  return 1;
	  }
	  else
	  {
  #if DEBUG_MSG
		  printf("[DEBUG_APP] Machine type Setting same setting. Do not save in external flash.\r\n");
  #endif
		  return 0;
	  }
  }
  */
INT08U Set_Machine_Parameter(SRM_Machine_STR* pSet)
{
	INT16U crc = 0x0000;

	ExtFlash_ReadData(EXT_DEVICE_SET_ADDR_START, (INT08U*)&m_ExtSEnv, sizeof(ExtFlashSEnv));

	if (memcmp((INT08U*)&m_ExtSEnv.Machine.mType, pSet, sizeof(SRM_Machine_STR)))
	{
		memcpy(m_ExtSEnv.InitMachineCode, MACHINE_TYPE_INIT_CODE, 4);

		memcpy((INT08U*)&m_ExtSEnv.Machine.mType, (INT08U*)pSet, sizeof(SRM_Machine_STR));

		m_ExtSEnv.CheckCRC_MachineType = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv.Machine, sizeof(SRM_Machine_Type));

		ExtFlash_WriteData(EXT_DEVICE_SET_ADDR_START, (INT08U*)&m_ExtSEnv, sizeof(ExtFlashSEnv));

#if DEBUG_MSG
		printf("[DEBUG_APP] Machine type save to external flash. DataCRC: 0x%04x\r\n", m_ExtSEnv.CheckCRC_MachineType);
#endif
		return 1;
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Machine type Setting same thing. Do not save in external flash.\r\n");
#endif
		return 0;
	}
}

INT08U Set_DSP_Parameter(MX_DSP_Setting* pSet)
{
	INT16U crc = 0x0000;

	ExtFlash_ReadData(EXT_DEVICE_SET_ADDR_START, (INT08U*)&m_ExtSEnv, sizeof(ExtFlashSEnv));

	//pSet->NetIf[0].RemotePort = DEF_DSP_REMOTE_PORT;	// 고정값
	//pSet->NetIf[1].RemotePort = DEF_DSP_REMOTE_PORT;	// 고정값

	if (memcmp((INT08U*)&m_ExtSEnv.Machine.DSP_Set, pSet, sizeof(MX_DSP_Setting)))
	{
		memcpy(m_ExtSEnv.InitMachineCode, MACHINE_TYPE_INIT_CODE, 4);

		memcpy((INT08U*)&m_ExtSEnv.Machine.DSP_Set, (INT08U*)pSet, sizeof(MX_DSP_Setting));

		m_ExtSEnv.CheckCRC_MachineType = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv.Machine, sizeof(SRM_Machine_Type));

		ExtFlash_WriteData(EXT_DEVICE_SET_ADDR_START, (INT08U*)&m_ExtSEnv, sizeof(ExtFlashSEnv));

#if DEBUG_MSG
		printf("[DEBUG_APP] DSP Setting save to external flash. DataCRC: 0x%04x\r\n", m_ExtSEnv.CheckCRC_MachineType);
#endif
		return 1;
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] DSP Setting same thing. Do not save in external flash.\r\n");
#endif
		return 0;
	}
}

/**
  * @brief
  * @param None
  * @retval None
  */
void Machine_Type_Setting_Init()
{
	INT16U crc = 0x0000;

	ExtFlash_ReadData(EXT_DEVICE_SET_ADDR_START, (INT08U*)&m_ExtSEnv, sizeof(ExtFlashSEnv));

	if (checkFusingString((INT08U*)m_ExtSEnv.InitMachineCode, (INT08U*)MACHINE_TYPE_INIT_CODE, 4))
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Machine_Type Setting Empty. Write Default Setup.\n\r");
#endif
		Default_MachineType_Setting();

		save_error_code(ERROR1_MCU_PARAM_DATA, 2, 1);
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Checked Machine_Type Setting.\n\r");
#endif

		crc = 0x0000;
		crc = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv.Machine, sizeof(SRM_Machine_Type));
		if (m_ExtSEnv.CheckCRC_MachineType != crc)
		{
#if DEBUG_MSG
			printf("[DEBUG_APP] Not equal CRC Machine config. DataCrc: 0x%04x CalcCRC: 0x%04x\n\r",
				m_ExtSEnv.CheckCRC_MachineType, crc);
#endif
			save_error_code(ERROR1_MCU_PARAM_DATA, 2, 0);
		}
		else
		{
#if DEBUG_MSG
			printf("[DEBUG_APP] Equal CRC Machine config. DataCrc: 0x%04x CalcCRC: 0x%04x\n\r",
				m_ExtSEnv.CheckCRC_MachineType, crc);
#endif
		}
	}
}

/**
  * @brief
  * @param None
  * @retval None
  */
void Default_DIO_Setting_Init()
{
	INT08U i = 0;

	DIO_SetSTR nSetting;

	memset((INT08U*)&nSetting, 0, sizeof(DIO_SetSTR));

	for (i = 0; i < MAX_DI_CNT; i++)
	{
		nSetting.DI_Set[i].Type = 255;		// Not Use
	}

	for (i = 0; i < MAX_DO_CNT; i++)
	{
		nSetting.DO_Set[i].Type = 255;		// Not Use
	}

	Set_DIO_Parameter(&nSetting);
}

/**
  * @brief
  * @param None
  * @retval None
  */
INT08U Check_DIO_SetParameter()
{
	if (checkFusingString((INT08U*)m_ExtSEnv.InitDIOCode, (INT08U*)DIO_INIT_CODE, 4))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/**
  * @brief
  * @param None
  * @retval None
  */
void Set_DIO_Parameter(DIO_SetSTR* pDIO_Set)
{
	INT16U crc = 0x0000;

	ExtFlash_ReadData(EXT_DEVICE_SET_ADDR_START, (INT08U*)&m_ExtSEnv, sizeof(ExtFlashSEnv));

	if (memcmp((INT08U*)&m_ExtSEnv.DIO_Set, (INT08U*)pDIO_Set, sizeof(DIO_SetSTR)))
	{
		memcpy(m_ExtSEnv.InitDIOCode, DIO_INIT_CODE, 4);

		memcpy((INT08U*)&m_ExtSEnv.DIO_Set, (INT08U*)pDIO_Set, sizeof(DIO_SetSTR));
		memcpy((INT08U*)&m_DIO_SetInfo.Set, (INT08U*)&m_ExtSEnv.DIO_Set, sizeof(DIO_SetComSTR));

		m_ExtSEnv.CheckCRC_DIO_Set = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv.DIO_Set, sizeof(DIO_SetSTR));
		ExtFlash_WriteData(EXT_DEVICE_SET_ADDR_START, (INT08U*)&m_ExtSEnv, sizeof(ExtFlashSEnv));

#if DEBUG_MSG
		printf("[DEBUG_APP] DIO Setting save to external flash. DataCRC: 0x%04x\r\n", m_ExtSEnv.CheckCRC_DIO_Set);
#endif
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] DIO Setting same setting. Do not save in external flash.\r\n");
#endif
	}
}

/**
  * @brief Initialize Default Digital In/Out Setting
  * @param None
  * @retval None
  */
void DIO_Setting_Init()
{
	INT16U crc = 0x0000;

	ExtFlash_ReadData(EXT_DEVICE_SET_ADDR_START, (INT08U*)&m_ExtSEnv, sizeof(ExtFlashSEnv));

	if (checkFusingString((INT08U*)m_ExtSEnv.InitDIOCode, (INT08U*)DIO_INIT_CODE, 4))
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] DIO Setting Empty. Save default Setting.\n\r");
#endif
		Default_DIO_Setting_Init();

		//save_error_code(ERROR_MCU_PARAM_DATA, 4, 1);
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Checked DIO Setting.\n\r");
#endif
		crc = 0x0000;
		crc = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv.DIO_Set, sizeof(DIO_SetSTR));
		if (crc != m_ExtSEnv.CheckCRC_DIO_Set)
		{
#if DEBUG_MSG
			printf("[DEBUG_APP] Not equal CRC DIO config. DataCrc: 0x%04x CalcCRC: 0x%04x\n\r",
				m_ExtSEnv.CheckCRC_DIO_Set, crc);
#endif
			save_error_code(ERROR1_MCU_PARAM_DATA, 3, 0);
		}
		else
		{
#if DEBUG_MSG
			printf("[DEBUG_APP] Equal CRC DIO config. DataCrc: 0x%04x CalcCRC: 0x%04x\n\r",
				m_ExtSEnv.CheckCRC_DIO_Set, crc);
#endif
			memcpy((INT08U*)&m_DIO_SetInfo.Set, (INT08U*)&m_ExtSEnv.DIO_Set, sizeof(DIO_SetComSTR));
		}
	}

	//memcpy((INT08U*)&m_DIO_SetInfo.Set, (INT08U*)&m_ExtSEnv.DIO_Set, sizeof(DIO_SetSTR));
}

/**
  * @brief
  * @param None
  * @retval None
  */
INT08U Check_RackEnv_Config()
{
	INT08U nResult = 0;

	if (checkFusingString((INT08U*)m_ExtSEnv0.InitRackCode, (INT08U*)RACK_INIT_CODE, 4))
	{
		asm volatile("NOP");
	}
	else
	{
		if ((m_ExtSEnv0.RackConfig.BayCount) \
			&& (m_ExtSEnv0.RackConfig.LvCount))
		{
			nResult = 1;
		}
		/*
		if ((m_ExtSEnv0.RackConfig.BayCount) \
			&& (m_ExtSEnv0.RackConfig.LvCount) \
			&& (m_ExtSEnv0.RackConfig.RowDepth[0] != 0) \
			&& (m_ExtSEnv0.RackConfig.RowDepth[1] != 0) \
			&& (m_ExtSEnv0.RackConfig.RowDepth[1] != 0) \
			&& (m_ExtSEnv0.RackConfig.RowDepth[2] != 0))
		{
			nResult = 1;
		}
		*/
	}

	return nResult;
}

/**
  * @brief	Set_Rack_Config_1
  * @param  RackConfigSTR_1* pSetting
  * @retval void
  */
void Set_Rack_Config(RackConfigSTR* pSetting)
{
	INT16U crc = 0x0000;

	ExtFlash_ReadData(EXT_RACK_ENV0_ADDR_START, (INT08U*)&m_ExtSEnv0, sizeof(ExtFlashSEnv0));

	if (memcmp((INT08U*)&m_ExtSEnv0.RackConfig, (INT08U*)pSetting, sizeof(RackConfigSTR)))
	{
		memcpy(m_ExtSEnv0.InitRackCode, RACK_INIT_CODE, 4);

		memcpy((INT08U*)&m_ExtSEnv0.RackConfig, (INT08U*)pSetting, sizeof(RackConfigSTR));
		m_ExtSEnv0.CheckCRC_RackConfig = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv0.RackConfig, sizeof(RackConfigSTR));

		ExtFlash_WriteData(EXT_RACK_ENV0_ADDR_START, (INT08U*)&m_ExtSEnv0, sizeof(ExtFlashSEnv0));

#if DEBUG_MSG
		printf("[DEBUG_APP] RackConfig save to external flash. DataCRC: 0x%04x\r\n", m_ExtSEnv0.CheckCRC_RackConfig);
#endif
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] RackConfig same setting. Do not save in external flash.\r\n");
#endif
	}
}

void Clear_Rack_Config(void)
{
	INT16U crc = 0x0000;

	ExtFlash_ReadData(EXT_RACK_ENV0_ADDR_START, (INT08U*)&m_ExtSEnv0, sizeof(ExtFlashSEnv0));

	memcpy(m_ExtSEnv0.InitRackCode, RACK_INIT_CODE, 4);

	memset((INT08U*)&m_ExtSEnv0.RackConfig, 0, sizeof(RackConfigSTR));
	m_ExtSEnv0.CheckCRC_RackConfig = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv0.RackConfig, sizeof(RackConfigSTR));

	//m_ExtSEnv0.CheckCRC_RackConfig = 0;

	ExtFlash_WriteData(EXT_RACK_ENV0_ADDR_START, (INT08U*)&m_ExtSEnv0, sizeof(ExtFlashSEnv0));
}

/**
  * @brief
  * @param None
  * @retval None
  */
void Rack_Config_Init()
{
	INT16U crc = 0x0000;

	ExtFlash_ReadData(EXT_RACK_ENV0_ADDR_START, (INT08U*)&m_ExtSEnv0, sizeof(ExtFlashSEnv0));

	if (checkFusingString((INT08U*)m_ExtSEnv0.InitRackCode, (INT08U*)RACK_INIT_CODE, 4))
	{
#if DEBUG_MSG
		//printf("[DEBUG_APP] Rack config Empty. Write Default Setup.\n\r");
		printf("[DEBUG_APP] Rack config Empty.\n\r");
#endif
		Clear_Rack_Config();

		//save_error_code(ERROR_MCU_PARAM_DATA, 3, 1);
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Checked Rack config.\n\r");
#endif

		crc = 0x0000;
		crc = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv0.RackConfig, sizeof(RackConfigSTR));
		if (crc != m_ExtSEnv0.CheckCRC_RackConfig)
		{
#if DEBUG_MSG
			printf("[DEBUG_APP] Not equal Rack config. DataCrc: 0x%04x CalcCRC: 0x%04x\n\r",
				m_ExtSEnv0.CheckCRC_RackConfig, crc);
#endif
			save_error_code(ERROR1_MCU_PARAM_DATA, 4, 0);
		}
		else
		{
#if DEBUG_MSG
			printf("[DEBUG_APP] Equal Rack config. DataCrc: 0x%04x CalcCRC: 0x%04x\n\r",
				m_ExtSEnv0.CheckCRC_RackConfig, crc);
#endif
		}
	}
}

/**
  * @brief
  * @param None
  * @retval None
  */
void Default_Cell_Config_Init(CellConfigSTR* pSetting)
{
	int i = 0;

	for (i = 0; i < m_ExtSEnv0.RackConfig.BayCount; i++)
	{
		pSetting->BayPos[i] = 1000 + (i * 500);
	}

	for (i = 0; i < m_ExtSEnv0.RackConfig.LvCount; i++)
	{
		pSetting->LvPos[i] = 1000 + (i * 500);
	}
}

/**
  * @brief
  * @param None
  * @retval None
  */
INT08U Check_CellEnv_Config()
{
	INT08U nResult = 0;

	if (checkFusingString((INT08U*)m_ExtSEnv0.InitCellCode, (INT08U*)CELL_INIT_CODE, 4))
	{
		asm volatile ("NOP");
	}
	else
	{
		//Cell 위치 값 저장 확인.
		//Cell 위치 값 내림차순 확인.
		if (m_ExtSEnv0.RackConfig.BayCount && m_ExtSEnv0.RackConfig.LvCount)
		{
			nResult = 1;
		}
	}

	return nResult;
}

/**
  * @brief
  * @param None
  * @retval None
  */
void Set_Cell_Config(CellConfigSTR* pSetting)
{
	INT16U crc = 0x0000;

	ExtFlash_ReadData(EXT_RACK_ENV0_ADDR_START, (INT08U*)&m_ExtSEnv0, sizeof(ExtFlashSEnv0));

	if (memcmp((INT08U*)&m_ExtSEnv0.CellConfig_Left, (INT08U*)pSetting, sizeof(CellConfigSTR)))
	{
		memcpy(m_ExtSEnv0.InitCellCode, CELL_INIT_CODE, 4);

		memcpy((INT08U*)&m_ExtSEnv0.CellConfig_Left, (INT08U*)pSetting, sizeof(CellConfigSTR));
		m_ExtSEnv0.CheckCRC_CellData = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv0.CellConfig_Left, sizeof(CellConfigSTR));

		ExtFlash_WriteData(EXT_RACK_ENV0_ADDR_START, (INT08U*)&m_ExtSEnv0, sizeof(ExtFlashSEnv0));

#if DEBUG_MSG
		printf("[DEBUG_APP] Cell Config save to external flash. DataCRC: 0x%04x\r\n", m_ExtSEnv0.CheckCRC_CellData);
#endif
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Cell Config same setting. Do not save in external flash.\r\n");
#endif
	}
}

/**
  * @brief
  * @param None
  * @retval None
  */
void Set_Cell_Config_1(CellConfigSTR* pSetting, INT08U nDir)
{
	INT16U crc = 0x0000;
	INT16U crc1 = 0x0000;

	ExtFlash_ReadData(EXT_RACK_ENV0_ADDR_START, (INT08U*)&m_ExtSEnv0, sizeof(ExtFlashSEnv0));

	if (nDir == 0)
	{
		if (memcmp((INT08U*)&m_ExtSEnv0.CellConfig_Left, (INT08U*)pSetting, sizeof(CellConfigSTR)))
		{
			memcpy(m_ExtSEnv0.InitCellCode, CELL_INIT_CODE, 4);

			memcpy((INT08U*)&m_ExtSEnv0.CellConfig_Left, (INT08U*)pSetting, sizeof(CellConfigSTR));
			crc1 = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv0.CellConfig_Left, sizeof(CellConfigSTR));
			m_ExtSEnv0.CheckCRC_CellData = crcInitStrCalc(crc1, (INT08U*)&m_ExtSEnv0.CellConfig_Right, sizeof(CellConfigSTR));

			ExtFlash_WriteData(EXT_RACK_ENV0_ADDR_START, (INT08U*)&m_ExtSEnv0, sizeof(ExtFlashSEnv0));

#if DEBUG_MSG
			printf("[DEBUG_APP] Left Cell Config save to external flash. DataCRC: 0x%04x\r\n", m_ExtSEnv0.CheckCRC_CellData);
#endif
		}
		else
		{
#if DEBUG_MSG
			printf("[DEBUG_APP] Left  Cell Config same setting. Do not save in external flash.\r\n");
#endif
		}
	}
	else if (nDir == 1)
	{
		if (memcmp((INT08U*)&m_ExtSEnv0.CellConfig_Right, (INT08U*)pSetting, sizeof(CellConfigSTR)))
		{
			memcpy(m_ExtSEnv0.InitCellCode, CELL_INIT_CODE, 4);

			memcpy((INT08U*)&m_ExtSEnv0.CellConfig_Right, (INT08U*)pSetting, sizeof(CellConfigSTR));
			crc1 = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv0.CellConfig_Left, sizeof(CellConfigSTR));
			m_ExtSEnv0.CheckCRC_CellData = crcInitStrCalc(crc1, (INT08U*)&m_ExtSEnv0.CellConfig_Right, sizeof(CellConfigSTR));

			ExtFlash_WriteData(EXT_RACK_ENV0_ADDR_START, (INT08U*)&m_ExtSEnv0, sizeof(ExtFlashSEnv0));

#if DEBUG_MSG
			printf("[DEBUG_APP] Right Cell Config save to external flash. DataCRC: 0x%04x\r\n", m_ExtSEnv0.CheckCRC_CellData);
#endif
		}
		else
		{
#if DEBUG_MSG
			printf("[DEBUG_APP] Right  Cell Config same setting. Do not save in external flash.\r\n");
#endif
		}
	}

	
}

void Clear_Cell_Config()
{
	INT16U crc = 0x0000;
	INT16U crc1 = 0x0000;

	ExtFlash_ReadData(EXT_RACK_ENV0_ADDR_START, (INT08U*)&m_ExtSEnv0, sizeof(ExtFlashSEnv0));

	memcpy(m_ExtSEnv0.InitCellCode, CELL_INIT_CODE, 4);

	memset((INT08U*)&m_ExtSEnv0.CellConfig_Left, 0, sizeof(CellConfigSTR));
	memset((INT08U*)&m_ExtSEnv0.CellConfig_Right, 0, sizeof(CellConfigSTR));

	crc1 = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv0.CellConfig_Left, sizeof(CellConfigSTR));
	m_ExtSEnv0.CheckCRC_CellData = crcInitStrCalc(crc1, (INT08U*)&m_ExtSEnv0.CellConfig_Left, sizeof(CellConfigSTR));

	ExtFlash_WriteData(EXT_RACK_ENV0_ADDR_START, (INT08U*)&m_ExtSEnv0, sizeof(ExtFlashSEnv0));
}

/**
  * @brief
  * @param None
  * @retval None
  */
void Cell_Config_Init()
{
	INT16U crc = 0x0000, crc1 = 0x0000;

	ExtFlash_ReadData(EXT_RACK_ENV0_ADDR_START, (INT08U*)&m_ExtSEnv0, sizeof(ExtFlashSEnv0));

	if (checkFusingString((INT08U*)m_ExtSEnv0.InitCellCode, (INT08U*)CELL_INIT_CODE, 4))
	{
#if DEBUG_MSG
		//printf("[DEBUG_APP] Cell config Empty. Write Default Setup.\n\r");
		printf("[DEBUG_APP] Cell config Empty. Clear Cell Config.\n\r");
#endif
		Clear_Cell_Config();
	}
	else
	{  
#if DEBUG_MSG
		printf("[DEBUG_APP] Checked Cell config.\n\r");
#endif
		crc = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv0.CellConfig_Left, sizeof(CellConfigSTR));
		crc1 = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv0.CellConfig_Right, sizeof(CellConfigSTR));

		if (crc1 != m_ExtSEnv0.CheckCRC_CellData)
		{
#if DEBUG_MSG
			printf("[DEBUG_APP] Not equal CRC Cell config. DataCrc: 0x%04x CalcCRC: 0x%04x\n\r",
				m_ExtSEnv0.CheckCRC_CellData, crc1);
#endif
			save_error_code(ERROR1_MCU_PARAM_DATA, 4, 0);
		}
		else
		{
#if DEBUG_MSG
			printf("[DEBUG_APP] Equal CRC Cell config. DataCrc: 0x%04x CalcCRC: 0x%04x\n\r",
				m_ExtSEnv0.CheckCRC_CellData, crc1);
#endif
		}
	}
}

/**
  * @brief
  * @param None
  * @retval None
  */
INT08U Check_StationEnv_Config()
{
	INT08U nResult = 0;

	if (checkFusingString((INT08U*)m_ExtSEnv1.InitStationCode, (INT08U*)STATION_INIT_CODE, 4))
	{
		asm volatile("NOP");
	}
	else
	{
		//if (m_ExtSEnv1.StationEnv.TotalUseCnt)
		if (m_ExtSEnv1.StationEnv.TotalUseCnt > 0)
		{
			nResult = 1;
		}
	}

	return nResult;
}

/**
  * @brief
  * @param None
  * @retval None
  */
void Clear_Station_Config()
{
	INT16U crc = 0x0000;

	memcpy(m_ExtSEnv1.InitStationCode, STATION_INIT_CODE, 4);

	memset((INT08U*)&m_ExtSEnv1.StationEnv, 0, sizeof(StationSetupSTR));
	m_ExtSEnv1.CRC_StationSet = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv1.StationEnv, sizeof(StationSetupSTR));

	ExtFlash_WriteData(EXT_RACK_ENV1_ADDR_START, (INT08U*)&m_ExtSEnv1, sizeof(ExtFlashSEnv1));
}

/**
  * @brief
  * @param None
  * @retval None
  */
void Set_Station_Config(StationSetupSTR* pSetting)
{
	INT16U crc = 0x0000;

	ExtFlash_ReadData(EXT_RACK_ENV1_ADDR_START, (INT08U*)&m_ExtSEnv1, sizeof(ExtFlashSEnv1));

	if (memcmp((INT08U*)&m_ExtSEnv1.StationEnv, (INT08U*)pSetting, sizeof(StationSetupSTR)))
	{
		memcpy(m_ExtSEnv1.InitStationCode, STATION_INIT_CODE, 4);

		memcpy((INT08U*)&m_ExtSEnv1.StationEnv, (INT08U*)pSetting, sizeof(StationSetupSTR));
		m_ExtSEnv1.CRC_StationSet = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv1.StationEnv, sizeof(StationSetupSTR));

		ExtFlash_WriteData(EXT_RACK_ENV1_ADDR_START, (INT08U*)&m_ExtSEnv1, sizeof(ExtFlashSEnv1));

#if DEBUG_MSG
		printf("[DEBUG_APP] Station Config save to external flash. DataCRC: 0x%04x\r\n", \
			m_ExtSEnv1.CRC_StationSet);
#endif
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Station Config same setting. Do not save in external flash.\r\n");
#endif
	}
}

/**
  * @brief
  * @param None
  * @retval None
  */
void Station_Config_Init()
{
	INT16U crc = 0x0000;

	ExtFlash_ReadData(EXT_RACK_ENV1_ADDR_START, (INT08U*)&m_ExtSEnv1, sizeof(ExtFlashSEnv1));

	if (checkFusingString((INT08U*)m_ExtSEnv1.InitStationCode, (INT08U*)STATION_INIT_CODE, 4))
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Station config Empty. \n\r");
#endif
		Clear_Station_Config();
		//save_error_code(ERROR_MCU_PARAM_DATA, 9, 1);
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Checked Station config.\n\r");
#endif
		crc = 0x0000;
		crc = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv1.StationEnv, sizeof(StationSetupSTR));
		if (crc != m_ExtSEnv1.CRC_StationSet)
		{
#if DEBUG_MSG
			printf("[DEBUG_APP] Not equal CRC Station config. DataCrc: 0x%04x ClacCRC: 0x%04x\n\r",
				m_ExtSEnv1.CRC_StationSet, crc);
#endif
			save_error_code(ERROR1_MCU_PARAM_DATA, 6, 0);
		}
		else
		{
#if DEBUG_MSG
			printf("[DEBUG_APP] Equal CRC Station config. DataCrc: 0x%04x ClacCRC: 0x%04x\n\r",
				m_ExtSEnv1.CRC_StationSet, crc);
#endif
		}
	}
}

/**
  * @brief
  * @param CellConfigSTR
  * @retval None
  */
void Test_Prohibit_Rack_Config_Init(ProhibitRackSTR* pSetting)
{
	int i = 0;

	pSetting->Count = 100;

	for (i = 0; i < pSetting->Count; i++)
	{
		pSetting->SetData[i].Row_Apply = 1;
		pSetting->SetData[i].Bay_No = i;
		pSetting->SetData[i].Lv_No = pSetting->Count - i;
	}
}

/**
  * @brief
  * @param
  * @retval None
  */
void Clear_Prohibit_RackCfg(ProhibitRackSTR* pSetting)
{
	memset((INT08U*)pSetting, 0, sizeof(ProhibitRackSTR));
}

/**
  * @brief
  * @param None
  * @retval None
  */
INT08U Check_ProhibitRack_Config()
{
	if (checkFusingString((INT08U*)m_ExtSEnv1.InitProhibitCode, (INT08U*)PROHIBIT_RACK_INIT_CODE, 4))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/**
  * @brief
  * @param None
  * @retval None
  */
void Clear_ProhibitRack_Config()
{
	INT16U crc = 0x0000;

	ExtFlash_ReadData(EXT_RACK_ENV1_ADDR_START, (INT08U*)&m_ExtSEnv1, sizeof(ExtFlashSEnv1));

	memcpy(m_ExtSEnv1.InitProhibitCode, PROHIBIT_RACK_INIT_CODE, 4);

	memset((INT08U*)&m_ExtSEnv1.ProhibitRack, 0, sizeof(ProhibitRackSTR));

	m_ExtSEnv1.CRC_ProhibitRack = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv1.ProhibitRack, sizeof(ProhibitRackSTR));

	ExtFlash_WriteData(EXT_RACK_ENV1_ADDR_START, (INT08U*)&m_ExtSEnv1, sizeof(ExtFlashSEnv1));
}

/**
  * @brief
  * @param None
  * @retval None
  */
INT08U Check_InhibitRack_Data(InhibitRackSet_t* nData)
{
	if ((nData->Row_Apply == 0) && (nData->Bay_No == 0) && (nData->Lv_No == 0))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
  * @brief
  * @param None
  * @retval None
  */
void Set_ProhibitRack_Config(ProhibitRackSTR* pSetting)
{
	INT16U crc = 0x0000;

	ExtFlash_ReadData(EXT_RACK_ENV1_ADDR_START, (INT08U*)&m_ExtSEnv1, sizeof(ExtFlashSEnv1));

	if (memcmp((INT08U*)&m_ExtSEnv1.ProhibitRack, (INT08U*)pSetting, sizeof(ProhibitRackSTR)))
	{
		memcpy(m_ExtSEnv1.InitProhibitCode, PROHIBIT_RACK_INIT_CODE, 4);

		memcpy((INT08U*)&m_ExtSEnv1.ProhibitRack, (INT08U*)pSetting, sizeof(ProhibitRackSTR));

		m_ExtSEnv1.CRC_ProhibitRack = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv1.ProhibitRack, sizeof(ProhibitRackSTR));

		ExtFlash_WriteData(EXT_RACK_ENV1_ADDR_START, (INT08U*)&m_ExtSEnv1, sizeof(ExtFlashSEnv1));

#if DEBUG_MSG
		printf("[DEBUG_APP] Inhibit Rack Config save to external flash. DataCRC: 0x%04x\r\n", \
			m_ExtSEnv1.CRC_ProhibitRack);
#endif
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Inhibit Rack Config same setting. Do not save in external flash.\r\n");
#endif
	}
}

/**
  * @brief
  * @param None
  * @retval None
  */
void ProhibitRack_Config_Init()
{
	INT16U crc = 0x0000;

	ExtFlash_ReadData(EXT_RACK_ENV1_ADDR_START, (INT08U*)&m_ExtSEnv1, sizeof(ExtFlashSEnv1));

	if (checkFusingString((INT08U*)m_ExtSEnv1.InitProhibitCode, (INT08U*)PROHIBIT_RACK_INIT_CODE, 4))
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Inhibit Rack config Empty.\n\r");
#endif
		Clear_ProhibitRack_Config();
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Checked Inhibit Rack config.\n\r");
#endif
		crc = 0x0000;
		crc = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv1.ProhibitRack, sizeof(ProhibitRackSTR));
		if (m_ExtSEnv1.CRC_ProhibitRack != crc)
		{
#if DEBUG_MSG
			printf("[DEBUG_APP] Not equal CRC Inhibit Rack config. DataCrc: 0x%04x CalcCRC: 0x%04x\n\r",
				m_ExtSEnv1.CRC_ProhibitRack, crc);
#endif
			save_error_code(ERROR1_MCU_PARAM_DATA, 7, 0);
		}
		else
		{
#if DEBUG_MSG
			printf("[DEBUG_APP] Equal CRC Inhibit Rack config. DataCrc: 0x%04x CalcCRC: 0x%04x\n\r",
				m_ExtSEnv1.CRC_ProhibitRack, crc);
#endif
		}
	}
}

/**
  * @brief
  * @param
  * @retval None
  */
void Test_Special_Rack_Config_Init(SpecialRackSTR* pSetting)
{
	int i = 0;

	pSetting->Count = 100;

	for (i = 0; i < pSetting->Count; i++)
	{
		pSetting->SetData[i].Goods_Type = 0xFF;
		//pSetting->Cell[i].Postion_Type = 1;
		pSetting->SetData[i].Row_No = 1;
		pSetting->SetData[i].Bay_No = i;
		pSetting->SetData[i].Lv_No = pSetting->Count - i;
	}
}

/**
  * @brief
  * @param
  * @retval None
  */
void Clear_Special_RackCfg(SpecialRackSTR* pSetting)
{
	memset((INT08U*)pSetting, 0, sizeof(SpecialRackSTR));
}

/**
  * @brief
  * @param None
  * @retval None
  */
INT08U Check_SpecialRack_Config()
{
	if (checkFusingString((INT08U*)m_ExtSEnv1.InitSpecialCode, (INT08U*)SPECIAL_RACK_INIT_CODE, 4))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/**
  * @brief
  * @param None
  * @retval None
  */
void Clear_SpecialRack_Config()
{
	INT16U crc = 0x0000;

	ExtFlash_ReadData(EXT_RACK_ENV1_ADDR_START, (INT08U*)&m_ExtSEnv1, sizeof(ExtFlashSEnv1));

	memcpy(m_ExtSEnv1.InitSpecialCode, SPECIAL_RACK_INIT_CODE, 4);
	memset((INT08U*)&m_ExtSEnv1.SpecialRack, 0, sizeof(SpecialRackSTR));
	m_ExtSEnv1.CRC_SpecialRack = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv1.SpecialRack, sizeof(SpecialRackSTR));

	ExtFlash_WriteData(EXT_RACK_ENV1_ADDR_START, (INT08U*)&m_ExtSEnv1, sizeof(ExtFlashSEnv1));
}

/**
  * @brief
  * @param None
  * @retval None
  */
INT08U Check_SpecialRack_Data(SpecialRackSet_t* nData)
{
	if ((nData->Row_No == 0) && (nData->Bay_No == 0) && (nData->Lv_No == 0) && (nData->Goods_Type == 0))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
  * @brief
  * @param None
  * @retval None
  */
void Set_SpecialRack_Config(SpecialRackSTR* pSetting)
{
	INT16U crc = 0x0000;

	ExtFlash_ReadData(EXT_RACK_ENV1_ADDR_START, (INT08U*)&m_ExtSEnv1, sizeof(ExtFlashSEnv1));

	if (memcmp((INT08U*)&m_ExtSEnv1.SpecialRack, (INT08U*)pSetting, sizeof(SpecialRackSTR)))
	{
		memcpy(m_ExtSEnv1.InitSpecialCode, SPECIAL_RACK_INIT_CODE, 4);

		memcpy((INT08U*)&m_ExtSEnv1.SpecialRack, (INT08U*)pSetting, sizeof(SpecialRackSTR));

		m_ExtSEnv1.CRC_SpecialRack = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv1.SpecialRack, sizeof(SpecialRackSTR));

		ExtFlash_WriteData(EXT_RACK_ENV1_ADDR_START, (INT08U*)&m_ExtSEnv1, sizeof(ExtFlashSEnv1));

#if DEBUG_MSG
		printf("[DEBUG_APP] Special Rack Config save to external flash. DataCRC: 0x%04x\r\n", \
			m_ExtSEnv1.CRC_SpecialRack);
#endif
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Special Rack Config same setting. Do not save in external flash.\r\n");
#endif
	}
}

/**
  * @brief
  * @param None
  * @retval None
  */
void SpecialRack_Config_Init()
{
	INT16U crc = 0x0000;

	ExtFlash_ReadData(EXT_RACK_ENV1_ADDR_START, (INT08U*)&m_ExtSEnv1, sizeof(ExtFlashSEnv1));

	if (checkFusingString((INT08U*)m_ExtSEnv1.InitSpecialCode, (INT08U*)SPECIAL_RACK_INIT_CODE, 4))
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Special Rack config Empty.\n\r");
#endif
		Clear_SpecialRack_Config();
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Checked Special Rack config.\n\r");
#endif
		crc = 0x0000;
		crc = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv1.SpecialRack, sizeof(SpecialRackSTR));

		if (m_ExtSEnv1.CRC_SpecialRack != crc)
		{
#if DEBUG_MSG
			printf("[DEBUG_APP] Not equal CRC Special Rack config. DataCrc: 0x%04x CalcCRC: 0x%04x\n\r",
				m_ExtSEnv1.CRC_SpecialRack, crc);
#endif
			save_error_code(ERROR1_MCU_PARAM_DATA, 8, 0);
		}
		else
		{
#if DEBUG_MSG
			printf("[DEBUG_APP] Equal CRC Special Rack config. DataCrc: 0x%04x CalcCRC: 0x%04x\n\r",
				m_ExtSEnv1.CRC_SpecialRack, crc);
#endif
		}
	}
}

/**
  * @brief
  * @param
  * @retval None
  */
INT16U CalcCRC_Cell_Offset_All()
{
	INT32U addr_now = EXT_CELL_OFFSET_ADDR_START;
	INT32U addr_end = EXT_CELL_OFFSET_ADDR_END;

	INT08U nReadData[4096] = { 0, };

	INT16U crcValue = 0;

	while (addr_now < addr_end)
	{
		ExtFlash_ReadData(addr_now, nReadData, 4096);

		crcValue = crcInitStrCalc(crcValue, nReadData, 4096);

		addr_now += 4096;
	}

	return crcValue;
}

/**
  * @brief
  * @param
  * @retval None
  */
void Make_Test_CellOffset_Data()
{
	INT16U i = 0;
	CellOffsetSTR nWriteBuf[512];	// 4K
	INT08U nBayIdx = 0, nLvIdx = 0;
	INT32U addr_now = EXT_CELL_OFFSET_ADDR_START;
	INT32U addr_end = EXT_CELL_OFFSET_ADDR_END;

#if DEBUG_CELL_OFFSET
	INT32U nEraseSize = 0;
	INT32U nProcessTime = 0;
	INT16U nEraseBlockCount = 0;

	nEraseSize = EXT_CELL_OFFSET_ADDR_END - EXT_CELL_OFFSET_ADDR_START + 1;
	nEraseBlockCount = nEraseSize / EXT_MEMORY_BLOCK;

	printf("[CELL OFFSET] StartAddr: 0x%08x, EndAddr: 0x%08x, Size: %ld Kbytes, Erase4K: %d\r\n",
		EXT_CELL_OFFSET_ADDR_START, EXT_CELL_OFFSET_ADDR_END, nEraseSize / 1024, nEraseBlockCount);

	nProcessTime = m_pgmEnv.timer1ms;
#endif

	while (addr_now < addr_end)
	{
		for (i = 0; i < 512; i++)
		{
			memset((INT08U*)&nWriteBuf[i], 0, sizeof(CellOffsetSTR));

			nWriteBuf[i].Bay_No = nBayIdx;
			nWriteBuf[i].Lv_No = nLvIdx;

			nWriteBuf[i].Trav_Left = 1;
			nWriteBuf[i].Lift_Left = (-1);
			nWriteBuf[i].Fork_Left = 2;
			nWriteBuf[i].Trav_Right = 1;
			nWriteBuf[i].Lift_Right = (-1);
			nWriteBuf[i].Fork_Right = 2;

			++nLvIdx;
			if (nLvIdx >= MAX_LEVEL_COUNT)
			{
#if DEBUG_CELL_OFFSET
				printf("[CELL OFFSET] Cell Offset Write Bay_Id: %d, Lv_Id: %d\r\n", nBayIdx, nLvIdx);
#endif
				nLvIdx = 0;
				++nBayIdx;
			}
		}

		ExtFlash_WriteData(addr_now, (INT08U*)nWriteBuf, sizeof(CellOffsetSTR) * 512);

#if DEBUG_CELL_OFFSET
		printf("[CELL OFFSET] Cell Offset Ext Flash Write Addr: 0x%08lx\r\n", addr_now);
#endif
		addr_now += sizeof(CellOffsetSTR) * 512;
	}

#if DEBUG_CELL_OFFSET
	printf("[CELL OFFSET] Initialization Cell Offset End Bay_Id: %d, End Lv_Id: %d, Process Time: %ld ms\r\n",
		nBayIdx, nLvIdx, getCalcTimer1ms(nProcessTime));
#endif
}

/**
  * @brief
  * @param None
  * @retval None
  */
INT08U Check_Cell_Offset_Config()
{
	if (checkFusingString((INT08U*)m_ExtSEnv0.InitCellOffsetCode, (INT08U*)CELL_OFFSET_INIT_CODE, 4))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
  * @brief
  * @param
  * @retval None
  */
void Clear_CellOffset_All()
{
	INT16U i = 0;
	CellOffsetSTR nWriteBuf[512];	// 4K
	INT08U nBayIdx = 0, nLvIdx = 0;
	INT32U addr_now = EXT_CELL_OFFSET_ADDR_START;
	INT32U addr_end = EXT_CELL_OFFSET_ADDR_END;
	INT32U nTotalSize = 0;
	INT16U nBlockNo = 0;

	//INT16U CalcCrc = 0;

	nTotalSize = addr_end - addr_now + 1;

#if DEBUG_CELL_OFFSET
	INT32U nEraseSize = 0;
	INT32U nProcessTime = 0;
	INT16U nEraseBlockCount = 0;

	nEraseBlockCount = nEraseSize / EXT_MEMORY_BLOCK;
	nEraseSize = EXT_CELL_OFFSET_ADDR_END - EXT_CELL_OFFSET_ADDR_START + 1;
	/*
	printf("[CELL OFFSET] StartAddr: 0x%08x, EndAddr: 0x%08x, Size: %ld Kbytes, Block Count(4K): %d\r\n",
		EXT_CELL_OFFSET_ADDR_START, EXT_CELL_OFFSET_ADDR_END, nEraseSize / 1024, nEraseBlockCount);
	*/
	nProcessTime = m_pgmEnv.timer1ms;
#endif

	while (addr_now < addr_end)
	{
		for (i = 0; i < 512; i++)
		{
			memset((INT08U*)&nWriteBuf[i], 0, sizeof(CellOffsetSTR));

			nWriteBuf[i].Bay_No = nBayIdx;
			nWriteBuf[i].Lv_No = nLvIdx;

			++nLvIdx;
			if (nLvIdx >= MAX_LEVEL_COUNT)
			{
#if DEBUG_CELL_OFFSET
				//printf("[CELL OFFSET] CellOffset Write Bay_Id: %d, Lv_Id: %d\r\n", nBayIdx + 1, nLvIdx);
#endif
				nLvIdx = 0;
				++nBayIdx;
			}
		}

		ExtFlash_WriteData(addr_now, (INT08U*)nWriteBuf, sizeof(CellOffsetSTR) * 512);

#if DEBUG_CELL_OFFSET
		//printf("[CELL OFFSET] CellOffset ExtFlash Write Addr: 0x%08lx, BlockNo: %d\r\n", addr_now, nBlockNo);
#endif
		addr_now += sizeof(CellOffsetSTR) * 512;
		++nBlockNo;
	}

	Write_CellOffset_InitCode();

#if DEBUG_CELL_OFFSET
	printf("[CELL OFFSET] Complete Initialization. ProcessTime: %ldms, CalcCRC: 0x%04x.\r\n", \
		getCalcTimer1ms(nProcessTime), m_ExtSEnv0.CheckCRC_CellOffset);
#endif
}

void Write_CellOffset_InitCode()
{
	ExtFlash_ReadData(EXT_RACK_ENV0_ADDR_START, (INT08U*)&m_ExtSEnv0, sizeof(ExtFlashSEnv0));

	memcpy(m_ExtSEnv0.InitCellOffsetCode, CELL_OFFSET_INIT_CODE, 4);

	m_ExtSEnv0.CheckCRC_CellOffset = CalcCRC_Cell_Offset_All();

	ExtFlash_WriteData(EXT_RACK_ENV0_ADDR_START, (INT08U*)&m_ExtSEnv0, sizeof(ExtFlashSEnv0));
}

void Clear_Cell_Offset_UseFlag(INT16U nStart)
{
	INT16U i = 0;
	INT16U nByte_Idx = 0;
	INT08U nBit_Idx = 0;

	if (nStart >= 32768)	return;

	ExtFlash_ReadData(EXT_CELL_OFFSET_USEFLAG_ADDR_START, (INT08U*)&m_pgmEnv.CellOffsetUseFlag, 4096);

	for (i = nStart; i < 32768; i++)
	{
		nByte_Idx = nStart / 8;
		nByte_Idx = nStart % 8;

		m_pgmEnv.CellOffsetUseFlag[nByte_Idx] |= cbits[nBit_Idx];
	}

	ExtFlash_WriteData(EXT_CELL_OFFSET_USEFLAG_ADDR_START, (INT08U*)m_pgmEnv.CellOffsetUseFlag, 4096);

	m_pgmEnv.CellOffsetUseCount = 0;
}

void Clear_Cell_Offset_UseFlagAll()
{
	memset((INT08U*)m_pgmEnv.CellOffsetUseFlag, 0xFF, 4096);

	ExtFlash_WriteData(EXT_CELL_OFFSET_USEFLAG_ADDR_START, (INT08U*)m_pgmEnv.CellOffsetUseFlag, 4096);

	m_pgmEnv.CellOffsetUseCount = 0;
}

void Clear_CellOffset_Config()
{
	Clear_CellOffset_All();

	Clear_Cell_Offset_UseFlagAll();
}

/**
  * @brief
  * @param None
  * @retval None
  */
void CellOffset_Config_Init()
{
	INT16U crc = 0x0000;

	ExtFlash_ReadData(EXT_RACK_ENV0_ADDR_START, (INT08U*)&m_ExtSEnv0, sizeof(ExtFlashSEnv0));

	if (checkFusingString((INT08U*)m_ExtSEnv0.InitCellOffsetCode, (INT08U*)CELL_OFFSET_INIT_CODE, 4))
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Cell Offset config Empty. Clear Data. \n\r");
#endif
		Clear_CellOffset_Config();
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Checked Cell Offset config.\n\r");
#endif
		crc = 0x0000;
		crc = CalcCRC_Cell_Offset_All();
		if (m_ExtSEnv0.CheckCRC_CellOffset != crc)
		{
#if DEBUG_MSG
			printf("[DEBUG_APP] Not equal CRC CellOffset config. DataCrc: 0x%04x CalcCRC: 0x%04x\n\r",
				m_ExtSEnv0.CheckCRC_CellOffset, crc);
#endif
			save_error_code(ERROR1_MCU_PARAM_DATA, 5, 0);
			m_pgmEnv.CellOffsetUseCount = 0;
		}
		else
		{
#if DEBUG_MSG
			printf("[DEBUG_APP] Equal CRC CellOffset config. DataCrc: 0x%04x CalcCRC: 0x%04x\n\r",
				m_ExtSEnv0.CheckCRC_CellOffset, crc);
#endif
			m_pgmEnv.CellOffsetUseCount = Scan_CellOffset_UseCount();
		}
	}
}

/**
  * @brief
  * @param nBay
  * @param nLv
  * @param pReadBuf
  * @retval
  */
INT08U Read_CellOffset_Bay_Lv(INT08U nBay, INT08U nLv, CellOffsetSTR* pReadBuf)
{
	INT32U nBay_Addr_offset = 1024;

	INT32U nReadOffset = 0;
	INT32U nReadAddr = 0;

#if DEBUG_MSG
	INT32U nProcessTime = 0;

	nProcessTime = m_pgmEnv.timer100us;
#endif

	if ((nBay < 1) || (nBay > m_ExtSEnv0.RackConfig.BayCount))
	{
		return 0;
	}

	if ((nLv < 1) || (nLv > m_ExtSEnv0.RackConfig.LvCount))
	{
		return 0;
	}

	nReadOffset = (nBay_Addr_offset * (nBay - 1)) + (sizeof(CellOffsetSTR) * (nLv - 1));
	nReadAddr = EXT_CELL_OFFSET_ADDR_START + nReadOffset;

	readData(nReadAddr, (INT08U*)pReadBuf, sizeof(CellOffsetSTR));

#if DEBUG_MSG
	/*
	printf("[DEBUG_APP] Read CellOffset Addr_Offset: 0x%08lx ReadAddr: 0x%08lx ReadTime: %ld\r\n", \
		nReadOffset, nReadAddr, getCalcTimer100us(nProcessTime));

	printf("[DEBUG_APP] Read CellOffset Bay: %d, Lv: %d TL(%d) LL(%d) FL(%d) TR(%d) LR(%d) FL(%d)\r\n",
		pReadBuf->Bay_No, pReadBuf->Lv_No, pReadBuf->Trav_Left, pReadBuf->Lift_Left, pReadBuf->Fork_Left, \
		pReadBuf->Trav_Right, pReadBuf->Lift_Right, pReadBuf->Fork_Right);
		*/
#endif // DEBUG_MSG

	return 1;
}

/**
  * @brief
  * @param nIndex
  * @param pReadBuf
  * @retval
  */
void Read_CellOffset_Addr(INT16U nIndex, CellOffsetSTR* pReadBuf)
{
	INT32U nReadOffset = 0;
	INT32U nReadAddr = 0;

	if (nIndex >= MAX_CELL_OFFSET_COUNT) {
		nIndex = MAX_CELL_OFFSET_COUNT - 1;
	}

	nReadOffset = sizeof(CellOffsetSTR) * nIndex;
	nReadAddr = EXT_CELL_OFFSET_ADDR_START + nReadOffset;

	readData(nReadAddr, (INT08U*)pReadBuf, sizeof(CellOffsetSTR));

#if DEBUG_CELL_OFFSET
	/*
	printf("[DEBUG_APP] Read CellOffset Index: %d ReadAddress: 0x%06lx\n\r",
		nIndex,nReadAddr);
	*/
#endif

#if ENABLE_WATCHDOG
	WatchDog();
#endif
}

/**
  * @brief
  * @param CellOffsetSTR
  * @retval INT08U
  */
INT08U Write_CellOffset(CellOffsetSTR* pBuf)
{
	INT32U nWriteBlkOffset = 4096;		// 4K
	INT32U nBayoffset = 1024;
	INT08U nWriteBuf[4096] = { 0, };	// 4K
	INT32U nWriteOffset = 0;
	INT32U nWriteAddr = 0;
	INT16U nWriteBitOffset = 0;
	INT16U nWriteUseFlag_ByteIdx = 0;
	INT08U nWriteUseFlag_BitIdx = 0;
	CellOffsetSTR* pTemp;

	if (pBuf->Bay_No >= MAX_BAY_COUNT) 		return 0;
	if (pBuf->Lv_No >= MAX_LEVEL_COUNT) 	return 0;

	nWriteAddr = EXT_CELL_OFFSET_ADDR_START + (nWriteBlkOffset * pBuf->Bay_No);
#if DEBUG_CELL_OFFSET
	INT32U nProcessTime = 0;

	printf("[DEBUG_APP] Read Cell Offset Bay: %d ReadAddress: 0x%06lx\n\r", \
		(INT16U)pBuf->Bay_No + 1, nWriteAddr);

	nProcessTime = m_pgmEnv.timer1ms;
#endif
	ExtFlash_ReadData(nWriteAddr, (INT08U*)nWriteBuf, sizeof(INT08U) * 4096);

	nWriteOffset = (nBayoffset * pBuf->Bay_No) + (sizeof(CellOffsetSTR) * pBuf->Lv_No);

	pTemp = (CellOffsetSTR*)&nWriteBuf[nWriteOffset];
	if ((pTemp->Bay_No == pBuf->Bay_No) && (pTemp->Lv_No == pBuf->Lv_No))
	{
#if DEBUG_CELL_OFFSET
		printf("[DEBUG_APP] Write Cell Offset Bay: %d Lv: %d WriteOffset: 0x%06lx\n\r", \
			(INT16U)pTemp->Bay_No + 1, (INT16U)pTemp->Lv_No + 1, nWriteOffset);
#endif
		memcpy((INT08U*)&nWriteBuf[nWriteOffset], (INT08U*)pBuf, sizeof(CellOffsetSTR));

		ExtFlash_WriteData(nWriteAddr, (INT08U*)nWriteBuf, sizeof(INT08U) * 4096);
	}
	else
	{
#if DEBUG_CELL_OFFSET
		printf("[CELL OFFSET] Cell Index not equal Bay: %d Lv: %d \n\r", \
			(INT16U)pTemp->Bay_No + 1, (INT16U)pTemp->Lv_No + 1);
#endif
		return 0;
	}

	// Total BitCount : 32768(256*128)
	nWriteBitOffset = (nBayoffset * pBuf->Bay_No) + (pBuf->Lv_No);
	nWriteUseFlag_ByteIdx = nWriteBitOffset / 8;
	nWriteUseFlag_BitIdx = nWriteBitOffset % 8;

#if DEBUG_CELL_OFFSET
	printf("[CELL OFFSET] Write Cell UseFlag BitOffset: %d ByteIdx: %d BitIdx: %d\n\r", \
		nWriteBitOffset, nWriteUseFlag_ByteIdx, nWriteUseFlag_BitIdx);
#endif

	if (pBuf->Trav_Left || pBuf->Trav_Right || pBuf->Lift_Left || pBuf->Lift_Right
		|| pBuf->Fork_Left || pBuf->Fork_Right)
	{
		// Use Flag : Set
		m_pgmEnv.CellOffsetUseFlag[nWriteUseFlag_ByteIdx] &= nbits[nWriteUseFlag_BitIdx];
	}
	else
	{
		// Use Flag : Reset
		m_pgmEnv.CellOffsetUseFlag[nWriteUseFlag_ByteIdx] |= cbits[nWriteUseFlag_BitIdx];
	}

	ExtFlash_WriteData(EXT_CELL_OFFSET_USEFLAG_ADDR_START, (INT08U*)m_pgmEnv.CellOffsetUseFlag, sizeof(INT08U) * 4096);

#if DEBUG_CELL_OFFSET
	printf("[CELL OFFSET] Write Cell Bay: %d Lv: %d Time: %ldms\n\r", \
		(INT16U)pBuf->Bay_No + 1, (INT16U)pBuf->Lv_No + 1, getCalcTimer1ms(nProcessTime));
#endif

	return 1;
}

/**
  * @brief
  * @param CellOffsetSTR
  * @retval INT08U
  */
INT08U Read_CellOffset_Block(INT16U nBlockNo, INT08U* pBuf)
{
	INT32U nReadBlkOffset = 4096;		// 4K

	INT32U nAddress = 0;
	INT32U nReadAddr = 0;

	if (nBlockNo >= 64) return 0;

	nAddress = nBlockNo * nReadBlkOffset;
	nReadAddr = EXT_CELL_OFFSET_ADDR_START + nAddress;
#if DEBUG_CELL_OFFSET
	/*
	printf("[CELL_OFFSET] Read Cell BlkNo: %d ReadAddress: 0x%06lx\n\r", \
		(INT16U)nBlockNo, nReadAddr);
	*/
#endif
	ExtFlash_ReadData(nReadAddr, (INT08U*)pBuf, sizeof(INT08U) * nReadBlkOffset);


	return 1;
}

/**
  * @brief
  * @param CellOffsetSTR
  * @retval INT08U
  */
INT08U Write_CellOffset_Block(INT16U nBlockNo, INT08U* pBuf)
{
	INT32U nWriteBlkOffset = 4096;		// 4K
	INT32U nAddress = 0;
	INT08U nReadBuf[4096] = { 0, };	// 4K
	INT32U nWriteAddr = 0;

	if (nBlockNo >= 64) return 0;

	nAddress = nBlockNo * nWriteBlkOffset;
	nWriteAddr = EXT_CELL_OFFSET_ADDR_START + nAddress;

#if DEBUG_CELL_OFFSET
	INT32U nProcessTime = 0;
	printf("[CELL_OFFSET] Read Cell BlkNo: %d ReadAddress: 0x%06lx\n\r", \
		(INT16U)nBlockNo, nWriteAddr);

	nProcessTime = m_pgmEnv.timer1ms;
#endif

	ExtFlash_ReadData(nWriteAddr, (INT08U*)nReadBuf, sizeof(INT08U) * nWriteBlkOffset);

	if (memcmp((INT08U*)&nReadBuf, (INT08U*)pBuf, sizeof(INT08U) * nWriteBlkOffset))
	{
		ExtFlash_WriteData(nWriteAddr, (INT08U*)pBuf, sizeof(INT08U) * nWriteBlkOffset);

#if DEBUG_CELL_OFFSET
		printf("[CELL_OFFSET] Write Cell BlkNo: %d, Address: 0x%06lx, Time: %ldms\n\r", \
			nBlockNo, nWriteAddr, getCalcTimer1ms(nProcessTime));
#endif
	}
	else
	{
#if DEBUG_CELL_OFFSET
		printf("[CELL_OFFSET] same setting. Do not save in external flash.\n\r");
#endif
	}

	return 1;
}

INT08U Check_CellOffset_BlockNo(CellOffsetSTR* pBuf)
{
	INT08U nBlockNo = 0;

	// Block No: 0 - Bay00 ~ Bay03	(4K)
	// Block No: 1 - Bay05 ~ Bay08	(4K)
	// Block No: 2 - Bay09 ~ Bay12	(4K)
	// ...
	// Block No: 64 - Bay243 ~ Bay256

	nBlockNo = pBuf->Bay_No / 4;

	if (nBlockNo >= 64)
	{
		nBlockNo = 64;
	}

	return nBlockNo;
}

void Check_CellOffset_UseFlag(CellOffsetSTR* pBuf, INT08U* pUseFlag)
{
	//INT32U nBayoffset = 1024;
	INT32U nBayoffset = 128;
	INT16U nWriteBitOffset = 0;
	INT16U nWriteUseFlag_ByteIdx = 0;
	INT08U nWriteUseFlag_BitIdx = 0;

	// Total BitCount : 32768(256*128)
	nWriteBitOffset = (nBayoffset * pBuf->Bay_No) + (pBuf->Lv_No);
	nWriteUseFlag_ByteIdx = nWriteBitOffset / 8;
	nWriteUseFlag_BitIdx = nWriteBitOffset % 8;

	if (pBuf->Trav_Left || pBuf->Trav_Right
		|| pBuf->Lift_Left || pBuf->Lift_Right
		|| pBuf->Fork_Left || pBuf->Fork_Right)
	{
		// Use Flag : Set
		*(pUseFlag + nWriteUseFlag_ByteIdx) &= nbits[nWriteUseFlag_BitIdx];
	}
	else
	{
		// Use Flag : Reset
		*(pUseFlag + nWriteUseFlag_ByteIdx) |= cbits[nWriteUseFlag_BitIdx];
	}
}

/**
  * @brief
  * @param
  * @retval INT08U
  */
INT16U Scan_CellOffset_UseCount()
{
	INT16U i = 0, j = 0;

	INT16U UseCount = 0;
	INT16U NotUseCount = 0;

#if DEBUG_MSG
	INT32U nProcessTime = 0;
	nProcessTime = m_pgmEnv.timer1ms;
#endif

	ExtFlash_ReadData(EXT_CELL_OFFSET_USEFLAG_ADDR_START, (INT08U*)&m_pgmEnv.CellOffsetUseFlag, 4096);

	for (i = 0; i < 4096; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (m_pgmEnv.CellOffsetUseFlag[i] & cbits[j])
			{
				++NotUseCount;
			}
			else
			{
				++UseCount;
			}
		}
	}

#if DEBUG_MSG
	printf("[DEBUG_APP] Cell Offset UseFlag Use: %d, NotUse: %d, Time: %ldms\n\r", \
		UseCount, NotUseCount, getCalcTimer1ms(nProcessTime));
#endif

	return UseCount;
}

/**
  * @brief
  * @param
  * @retval INT08U
  */
void Read_CellOffset_Data(INT16U nPage)
{
	INT32U nProcessTime = 0;

	INT16U i = 0;
	INT08U nReadBuffer[SIZE_PAGE] = { 0, };

	INT32U nAddress = 0;

	nProcessTime = m_pgmEnv.timer100us;

	nAddress = EXT_CELL_OFFSET_ADDR_START + (nPage * SIZE_PAGE);
	sst26_read(nAddress, SIZE_PAGE, nReadBuffer);

	printf("\r\n");
	printf("[EXT_SFLASH] Page: %d, Read Address: 0x%06lx,  Process Time: %ld00us\r\n", \
		nPage, nAddress, getCalcTimer100us(nProcessTime));

	for (i = 0; i < SIZE_PAGE; i++)
	{
		//if ((i % 20) == 0) printf("\r\n");
		if ((i % 24) == 0) printf("\r\n");

		printf(" %02x", nReadBuffer[i]);
	}
	printf("\r\n");

	asm volatile ("NOP");
}

/**
  * @brief
  * @param
  * @retval
  */
void Read_CellOffset_Data_1(INT16U nReadPage)
{
	INT32U nProcessTime = 0;

	INT16U i = 0;
	INT08U nReadBuffer[SIZE_PAGE] = { 0, };

	INT32U nAddress = 0;
	INT32U nStartAddress = 0;

	INT16U j = 0;

	nStartAddress = EXT_CELL_OFFSET_ADDR_START + (nReadPage * 1024);

	for (j = 0; j < 4; j++)
	{
		nProcessTime = m_pgmEnv.timer100us;

		nAddress = nStartAddress + (j * SIZE_PAGE);
		sst26_read(nAddress, SIZE_PAGE, nReadBuffer);

		printf("\r\n");
		printf("[EXT_SFLASH] Page: %d, Read Address: 0x%06lx,  Process Time: %ld00us\r\n", \
			nReadPage, nAddress, getCalcTimer100us(nProcessTime));

		for (i = 0; i < SIZE_PAGE; i++)
		{
			//if ((i % 20) == 0) printf("\r\n");
			if ((i % 24) == 0) printf("\r\n");

			printf(" %02x", nReadBuffer[i]);
		}
		printf("\r\n");
		asm volatile ("NOP");
	}
}

/**
  * @brief
  * @param
  * @retval
  */
INT08U Set_SafetyPlug_Type(ParamControlSTR* pSetting)
{
	if (pSetting->SafetyPlug_Type < 2)
	{
		// 0 : Start Off
		// 1 : Emergency Stop
		return 1;
	}
	else
	{
		return 0;
	}
}


/**
  * @brief
  * @param
  * @retval
  */
INT08U Set_DoorSensor_UseFlag(ParamControlSTR* pSetting)
{
	if (pSetting->DoorSensor_UseFlag < 2)
	{
		// 0 : not use, 1 : use
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
  * @brief
  * @param
  * @retval
  */
INT08U Set_DoorSensor_AlarmFlag(ParamControlSTR* pSetting)
{
	if (pSetting->DoorSensor_AlarmFlag < 2)
	{
		// 0 : not use, 1 : use
		return 1;
	}
	else
	{
		return 0;
	}
}


/**
  * @brief
  * @param
  * @retval
  */
INT08U Set_LaserModem_AlarmFlag(ParamControlSTR* pSetting)
{
	if (pSetting->LaserModem_AlarmFlag < 2)
	{
		// 0 : not use, 1 : use
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
  * @brief
  * @param
  * @retval
  */
INT08U Set_AutoChange_Mode(ParamControlSTR* pSetting)
{
	if (pSetting->AutoChange_Mode < 2)
	{
		// 0 : not use, 1 : use
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
  * @brief
  * @param
  * @retval
  */
INT08U Set_TravLift_OperTime_SyncFlag(ParamControlSTR* pSetting)
{
	if (pSetting->TravLift_OperTime_SyncFlag < 3)
	{
		// 0 : 주행, 승강 동시 출발
		// 1 : 승강 하강 시 동시 출발, 상승 시 동시 도착
		// 2 : 주행, 승강 동시 출발, 동시 도착
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
  * @brief
  * @param
  * @retval
  */
INT08U Set_Cargo_Adnormal_HomeReturn_UseFlag(ParamControlSTR* pSetting)
{
	if (pSetting->HomeReturn_Fault_UseFlag < 2)
	{
		// 0 : not use, 1 : use
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
  * @brief
  * @param
  * @retval
  */
INT08U Set_Forking_Sensor_AlarmFlag(ParamControlSTR* pSetting)
{
	if (pSetting->ForkOut_cargo_misalignment_alarm < 2)
	{
		// 0 : not use, 1 : use
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
  * @brief
  * @param
  * @retval
  */
INT08U Set_OutputStation_DoubleEntry_AlarmFlag(ParamControlSTR* pSetting)
{
	if (pSetting->Station_DSTLR_Fault_Flag < 2)
	{
		// 0 : not use, 1 : use
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
  * @brief
  * @param
  * @retval
  */
INT08U Set_Forking_Interlock_AlarmFlag(ParamControlSTR* pSetting)
{
	if (pSetting->Auto_ForkOut_Interlock_Fault < 2)
	{
		// 0 : not use, 1 : use
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
  * @brief
  * @param
  * @retval
  */
INT08U Set_Forking_Interlock_CheckFlag(ParamControlSTR* pSetting)
{
	if (pSetting->Man_ForkOut_Interlock_Fault < 2)
	{
		// 0 : not use, 1 : use
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
  * @brief
  * @param
  * @retval
  */
INT08U Set_Forking_lift_BrakeOn_UseFlag(ParamControlSTR* pSetting)
{
	if (pSetting->ForkOut_LT_BrakeOn_Flag < 2)
	{
		// 0 : not use, 1 : use
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
  * @brief
  * @param
  * @retval
  */
void Set_Forking_Origin_OperCount(ParamControlSTR* pSetting)
{
	if (pSetting->Fork_Auto_Home_Count > MAX_FORK_AUTO_HOME_CNT)
	{
		pSetting->Fork_Auto_Home_Count = MAX_FORK_AUTO_HOME_CNT;
	}
}

/**
  * @brief
  * @param
  * @retval
  */
void Set_RetryInPositon(ParamControlSTR* pSetting)
{
	INT08U i = 0;

	for (i = 0; i < INVERTOR_INSTALL_COUNT; i++)
	{
		if (pSetting->InPositon[i].RetryCount > MAX_POSI_LAG_RETRY_CNT)
			pSetting->InPositon[i].RetryCount = MAX_POSI_LAG_RETRY_CNT;

		if (pSetting->InPositon[i].RetryOffset > MAX_POSI_LAG_RETRY_MM)
			pSetting->InPositon[i].RetryOffset = MAX_POSI_LAG_RETRY_MM;
	}
}

/**
  * @brief
  * @param
  * @retval
  */
void Set_Loading_DelayTime(ParamControlSTR* pSetting)
{
	INT08U i = 0;

	for (i = 0; i <= DELAY_AFTER_FORK_CENTER; i++)
	{
		if (pSetting->Loading_Delay.mSetValue[i] > MAX_DELAY_TIME)
			pSetting->Loading_Delay.mSetValue[i] = MAX_DELAY_TIME;
	}
}

/**
  * @brief
  * @param
  * @retval
  */
void Set_Unloading_DelayTime(ParamControlSTR* pSetting)
{
	INT08U i = 0;

	for (i = 0; i <= DELAY_AFTER_FORK_CENTER; i++)
	{
		if (pSetting->Unloading_Delay.mSetValue[i] > MAX_DELAY_TIME)
			pSetting->Unloading_Delay.mSetValue[i] = MAX_DELAY_TIME;
	}
}

/**
  * @brief
  * @param
  * @retval
  */
void Set_Fork_Origin_DelayTime(ParamControlSTR* pSetting)
{
	if (pSetting->Fork_Origin_DelayTime > MAX_DELAY_TIME)
		pSetting->Fork_Origin_DelayTime = MAX_DELAY_TIME;
}

/**
  * @brief
  * @param
  * @retval
  */
void Set_Setup_TimeOut(ParamControlSTR* pSetting)
{
	INT08U i = 0;

	for (i = 0; i <= SETUP_TIMEOUT_FORK_ORIGIN; i++)
	{
		if (pSetting->SetupTimeOut.mSetValue[i] > 60000)
			pSetting->SetupTimeOut.mSetValue[i] = 60000;
	}
}

/**
  * @brief
  * @param
  * @retval
  */
void Set_Drive_Timeout(ParamControlSTR* pSetting)
{
	INT08U i = 0;

	for (i = 0; i <= DRIVE_TIMEOUT_HOME_RETURN; i++)
	{
		if (pSetting->DrvTimeout.SetValue[i] > 60000)
			pSetting->DrvTimeout.SetValue[i] = 60000;
	}
}

/**
  * @brief
  * @param
  * @retval
  */
void Set_Auto_Timeout(ParamControlSTR* pSetting)
{
	INT08U i = 0;

	for (i = 0; i <= AUTO_TIMEOUT_WAIT_INTERLOCK; i++)
	{
		if (pSetting->AutoTimeout.mSetValue[i] > 60000)
			pSetting->AutoTimeout.mSetValue[i] = 60000;
	}
}

/**
  * @brief
  * @param
  * @retval
  */
void Set_ForceMode_ReleaseTime(ParamControlSTR* pSetting)
{
	if (pSetting->ForceMode_ReleaseTime > MAX_FORCE_MODE_RELEASE_TIME)
		pSetting->ForceMode_ReleaseTime = MAX_FORCE_MODE_RELEASE_TIME;
}

/**
  * @brief
  * @param
  * @retval
  */
INT08U Set_Fan_Control(ParamControlSTR* pSetting)
{
	if (pSetting->FanControl.OperTime > 1000)
		pSetting->FanControl.OperTime = 1000;

	if (pSetting->FanControl.TempSensor_Install < 2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
  * @brief
  * @param
  * @retval
  */
void Set_Buzzer_Control(ParamControlSTR* pSetting)
{
	if (pSetting->BuzzerCtr.Fault_OnTime > MAX_BZ_FAULT_ON_TIME)
		pSetting->BuzzerCtr.Fault_OnTime = MAX_BZ_FAULT_ON_TIME;

	if (pSetting->BuzzerCtr.Warning_OnTime > MAX_BZ_WARNING_ON_TIME)
		pSetting->BuzzerCtr.Warning_OnTime = MAX_BZ_WARNING_ON_TIME;

	if (pSetting->BuzzerCtr.AutoChange_OnTime > MAX_BZ_AUTO_MODE_TIME)
		pSetting->BuzzerCtr.AutoChange_OnTime = MAX_BZ_AUTO_MODE_TIME;

	if (pSetting->BuzzerCtr.AutoChange_OffTime > MAX_BZ_AUTO_MODE_TIME)
		pSetting->BuzzerCtr.AutoChange_OffTime = MAX_BZ_AUTO_MODE_TIME;

	if (pSetting->BuzzerCtr.AutoChange_Toggle_Cnt > MAX_BZ_AUTO_MODE_CNT)
		pSetting->BuzzerCtr.AutoChange_Toggle_Cnt = MAX_BZ_AUTO_MODE_CNT;
}

/**
  * @brief
  * @param
  * @retval
  */
void Set_UpperBrakeSetup(ParamControlSTR* pSetting)
{
	if (pSetting->UpperBrake.Operation_Count > 100)
		pSetting->UpperBrake.Operation_Count = 100;

	if (pSetting->UpperBrake.ON_Time > 60000)
		pSetting->UpperBrake.ON_Time = 60000;

	if (pSetting->UpperBrake.OFF_Time > 60000)
		pSetting->UpperBrake.OFF_Time = 60000;
}

/**
  * @brief
  * @param
  * @retval
  */
INT08U Set_AutoFork_PositionSensor_Alarm(ParamControlSTR* pSetting)
{
	if (pSetting->Auto_Fork_Pos_Sensor_Fault < 2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
  * @brief
  * @param
  * @retval
  */
INT08U Set_Carriage_Stabilzation_Time(ParamControlSTR* pSetting)
{
	INT08U nResult = 0;

	INT08U i = 0, nCount;

	if (pSetting->Stabilzation_TimeSet.CaseCount <= 10)
	{
		nResult = 1;
	}

	return nResult;
}


/**
  * @brief
  * @param None
  * @retval None
  */
void Default_ControlParam_Init(void)
{
	INT08U i = 0;
	INT16U crc = 0x0000;

	ParamControlSTR nInitParam;

	memset((INT08U*)&nInitParam, 0, sizeof(ParamControlSTR));

	nInitParam.SafetyPlug_Type = 0;
	nInitParam.DoorSensor_UseFlag = 0;
	nInitParam.DoorSensor_AlarmFlag = 0;
	nInitParam.LaserModem_AlarmFlag = 1;
	nInitParam.AutoChange_Mode = 1;
	nInitParam.TravLift_OperTime_SyncFlag = 0;
	nInitParam.HomeReturn_Fault_UseFlag = 1;
	nInitParam.ForkOut_cargo_misalignment_alarm = 1;
	nInitParam.Station_DSTLR_Fault_Flag = 0;
	nInitParam.Auto_ForkOut_Interlock_Fault = 0;
	nInitParam.Man_ForkOut_Interlock_Fault = 0;
	nInitParam.ForkOut_LT_BrakeOn_Flag = 0;
	nInitParam.Fork_Auto_Home_Count = 0;

	nInitParam.InPositon[INV_TRAVEL].RetryCount = 0;
	nInitParam.InPositon[INV_TRAVEL].RetryOffset = 100;
	nInitParam.InPositon[INV_HOIST].RetryCount = 0;
	nInitParam.InPositon[INV_HOIST].RetryOffset = 100;
	nInitParam.InPositon[INV_FORK_1].RetryCount = 0;
	nInitParam.InPositon[INV_FORK_1].RetryOffset = 100;

	for (i = 0; i <= DELAY_AFTER_FORK_CENTER; i++)
	{
		nInitParam.Loading_Delay.mSetValue[i] = 50;		// 0.5s, Unit 0.01 sec
		nInitParam.Unloading_Delay.mSetValue[i] = 50;	// 0.5s, Unit 0.01 sec
	}

	nInitParam.Loading_Delay.mSetValue[DELAY_AFTER_FORK_OUT] = 10;		// 0.1s, Unit 0.01 sec
	nInitParam.Unloading_Delay.mSetValue[DELAY_AFTER_FORK_OUT] = 10;	// 0.1s, Unit 0.01 sec

	nInitParam.Loading_Delay.mSetValue[DELAY_AFTER_FORK_CENTER] = 10;		// 0.1s, Unit 0.01 sec
	nInitParam.Unloading_Delay.mSetValue[DELAY_AFTER_FORK_CENTER] = 10;	// 0.1s, Unit 0.01 sec

	/*
	for (i = 0; i <= SETUP_TIMEOUT_FORK_ORIGIN; i++)
	{
		nInitParam.SetupTimeOut.mSetValue[i] = 60000;		// 600.00s, Unit 0.01 sec
	}
	*/

	nInitParam.SetupTimeOut.mSetValue[SETUP_TIMEOUT_TRAVEL_ORIGIN] = 60000;		// 600.00s, Unit 0.01 sec
	nInitParam.SetupTimeOut.mSetValue[SETUP_TIMEOUT_LIFT_ORIGIN] = 30000;		// 300.00s, Unit 0.01 sec
	nInitParam.SetupTimeOut.mSetValue[SETUP_TIMEOUT_FORK_ORIGIN] = 3000;		// 30.00s, Unit 0.01 sec

	nInitParam.DrvTimeout.SetValue[DRIVE_TIMEOUT_MANUAL_RXCOM] = 150;	// 1.5s, Unit 0.01 sec
	nInitParam.DrvTimeout.SetValue[DRIVE_TIMEOUT_HOME_RETURN] = 60000;	// 1.5s, Unit 0.01 sec

	nInitParam.AutoTimeout.mSetValue[AUTO_TIMEOUT_MOVE_TRAV_LIFT] = 60000;			// 600.00s, Unit 0.01 sec
	nInitParam.AutoTimeout.mSetValue[AUTO_TIMEOUT_MOVE_FORK_OUT] = 6000;				// 60.00s, Unit 0.01 sec
	nInitParam.AutoTimeout.mSetValue[AUTO_TIMEOUT_MOVE_FORK_OUT_LIFT] = 6000;		// 60.00s, Unit 0.01 sec
	nInitParam.AutoTimeout.mSetValue[AUTO_TIMEOUT_MOVE_FORK_CENTER] = 6000;			// 600.00s, Unit 0.01 sec
	nInitParam.AutoTimeout.mSetValue[AUTO_TIMEOUT_WAIT_INTERLOCK] = 60000;	// 600.00s, Unit 0.01 sec

	nInitParam.ForceMode_ReleaseTime = 120;	// Unit : sec,

	nInitParam.FanControl.OperTime = 0;
	nInitParam.FanControl.TempSensor_Install = 0;

	nInitParam.BuzzerCtr.Fault_OnTime = 3000;			// 1.00s, Unit 0.01 sec
	nInitParam.BuzzerCtr.Warning_OnTime = 1000;			// 1.00s, Unit 0.01 sec
	nInitParam.BuzzerCtr.AutoChange_OnTime = 100;		// 1.00s, Unit 0.01 sec
	nInitParam.BuzzerCtr.AutoChange_OffTime = 100;		// 1.00s, Unit 0.01 sec
	nInitParam.BuzzerCtr.AutoChange_Toggle_Cnt = 3;

	nInitParam.UpperBrake.ON_Time = 0;	// 600.00s, Unit 0.01 sec
	nInitParam.UpperBrake.OFF_Time = 0;	// 600.00s, Unit 0.01 sec
	nInitParam.UpperBrake.Operation_Count = 0;

	ExtFlash_ReadData(EXT_PARAMETER_SET_ADDR_START, (INT08U*)&m_ExtSEnv2, sizeof(ExtFlashSEnv2));

	memcpy((INT08U*)m_ExtSEnv2.InitControlCode, CONTROL_PARAM_INIT_CODE, sizeof(INT08U) * 4);
	memcpy((INT08U*)&m_ExtSEnv2.CtrParam, (INT08U*)&nInitParam, sizeof(ParamControlSTR));

	m_ExtSEnv2.CRC_Control = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv2.CtrParam, sizeof(ParamControlSTR));

	ExtFlash_WriteData(EXT_PARAMETER_SET_ADDR_START, (INT08U*)&m_ExtSEnv2, sizeof(ExtFlashSEnv2));
}

/**
  * @brief
  * @param None
  * @retval None
  */
void Save_Control_Param(ParamControlSTR* pSetting)
{
	INT16U crc = 0;

	ExtFlash_ReadData(EXT_PARAMETER_SET_ADDR_START, (INT08U*)&m_ExtSEnv2, sizeof(ExtFlashSEnv2));

	if (memcmp((INT08U*)&m_ExtSEnv2.CtrParam, (INT08U*)pSetting, sizeof(ParamControlSTR)))
	{
		memcpy((INT08U*)m_ExtSEnv2.InitControlCode, CONTROL_PARAM_INIT_CODE, sizeof(INT08U) * 4);
		memcpy((INT08U*)&m_ExtSEnv2.CtrParam, (INT08U*)pSetting, sizeof(ParamControlSTR));

		m_ExtSEnv2.CRC_Control = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv2.CtrParam, sizeof(ParamControlSTR));

		ExtFlash_WriteData(EXT_PARAMETER_SET_ADDR_START, (INT08U*)&m_ExtSEnv2, sizeof(ExtFlashSEnv2));
#if DEBUG_MSG
		printf("[DEBUG_APP] Control Parameter save to external flash. DataCRC: 0x%04x\r\n", m_ExtSEnv2.CRC_Control);
#endif
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Control Parameter same setting. Do not save in external flash.\r\n");
#endif
	}

}

/**
  * @brief
  * @param None
  * @retval None
  */
void Control_Param_Init()
{
	INT16U crc = 0x0000;

	ExtFlash_ReadData(EXT_PARAMETER_SET_ADDR_START, (INT08U*)&m_ExtSEnv2, sizeof(ExtFlashSEnv2));

	if (checkFusingString((INT08U*)m_ExtSEnv2.InitControlCode, (INT08U*)CONTROL_PARAM_INIT_CODE, 4))
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Control Parameter Empty. Initialize Default Value.\n\r");
#endif
		//Default_ControlParam_Init();

		save_error_code(ERROR1_MCU_PARAM_DATA, 9, 1);
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Checked Control Parameter.\n\r");
#endif
		crc = 0x0000;
		crc = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv2.CtrParam, sizeof(ParamControlSTR));

		if (m_ExtSEnv2.CRC_Control != crc)
		{
#if DEBUG_MSG
			printf("[DEBUG_APP] Not equal CRC Control Parameter. DataCRC: 0x%04x, CalcCRC: 0x%04x\n\r",
				m_ExtSEnv2.CRC_Control, crc);
#endif
			save_error_code(ERROR1_MCU_PARAM_DATA, 9, 0);
		}
		else
		{
#if DEBUG_MSG
			printf("[DEBUG_APP] Equal CRC Control Parameter.DataCRC: 0x%04x, CalcCRC: 0x%04x\n\r",
				m_ExtSEnv2.CRC_Control, crc);
#endif
		}
	}
}

/**
  * @brief Write Travel velocity
  * @param nType
  * @param pVelocity
  * @retval None
  */
void Set_Trav_Velocity(INT08U nType, UnitVelocitySTR* pVelocity)
{
	switch (nType)
	{
	case TRAV_VEL_AUTO_H:
	case TRAV_VEL_AUTO_M:
	case TRAV_VEL_AUTO_L:
		if (pVelocity->Spd > MAX_TRAVEL_VEL_AUTO)  pVelocity->Spd = MAX_TRAVEL_VEL_AUTO;
		if (pVelocity->Spd < 1)  pVelocity->Spd = 1;

		if (pVelocity->Acc > MAX_TRAVEL_ACC)  pVelocity->Acc = MAX_TRAVEL_ACC;
		if (pVelocity->Acc < 1)  pVelocity->Acc = 1;

		if (pVelocity->Dec > MAX_TRAVEL_DEC)  pVelocity->Dec = MAX_TRAVEL_DEC;
		if (pVelocity->Dec < 1)  pVelocity->Dec = 1;

		if (pVelocity->Jerk > MAX_TRAVEL_JERK)  pVelocity->Jerk = MAX_TRAVEL_JERK;  // 1.00 ~ 2.00s => 0 ~ 500,	Unit: 0.01      
		if (pVelocity->Jerk < MIN_TRAVEL_JERK)  pVelocity->Jerk = MIN_TRAVEL_JERK;  // 1.00 ~ 2.00s => 0 ~ 500,	Unit: 0.01
		break;

	case TRAV_VEL_AUTO_DEC_1:
	case TRAV_VEL_AUTO_DEC_2:
		if (pVelocity->Spd > MAX_TRAVEL_VEL_AUTO)  pVelocity->Spd = MAX_TRAVEL_VEL_AUTO;
		if (pVelocity->Spd < 1)  pVelocity->Spd = 1;


		break;

	case TRAV_VEL_MAN_M:
		if (pVelocity->Spd > MAX_TRAVEL_VEL_MAN_M)  pVelocity->Spd = MAX_TRAVEL_VEL_MAN_M;
		if (pVelocity->Spd < 1)  pVelocity->Spd = 1;

		if (pVelocity->Acc > MAX_TRAVEL_ACC)  pVelocity->Acc = MAX_TRAVEL_ACC;
		if (pVelocity->Acc < 1)  pVelocity->Acc = 1;

		if (pVelocity->Dec > MAX_TRAVEL_DEC)  pVelocity->Dec = MAX_TRAVEL_DEC;
		if (pVelocity->Dec < 1)  pVelocity->Dec = 1;

		if (pVelocity->Jerk > MAX_TRAVEL_JERK)  pVelocity->Jerk = MAX_TRAVEL_JERK;  // 1.00 ~ 2.00s => 0 ~ 500,	Unit: 0.01      
		if (pVelocity->Jerk < MIN_TRAVEL_JERK)  pVelocity->Jerk = MIN_TRAVEL_JERK;  // 1.00 ~ 2.00s => 0 ~ 500,	Unit: 0.01
		break;

	case TRAV_VEL_MAN_L:
		if (pVelocity->Spd > MAX_TRAVEL_VEL_MAN_L)  pVelocity->Spd = MAX_TRAVEL_VEL_MAN_L;
		if (pVelocity->Spd < 1)  pVelocity->Spd = 1;

		if (pVelocity->Acc > MAX_TRAVEL_ACC)  pVelocity->Acc = MAX_TRAVEL_ACC;
		if (pVelocity->Acc < 1)  pVelocity->Acc = 1;

		if (pVelocity->Dec > MAX_TRAVEL_DEC)  pVelocity->Dec = MAX_TRAVEL_DEC;
		if (pVelocity->Dec < 1)  pVelocity->Dec = 1;

		if (pVelocity->Jerk > MAX_TRAVEL_JERK)  pVelocity->Jerk = MAX_TRAVEL_JERK;  // 1.00 ~ 2.00s => 0 ~ 500,	Unit: 0.01      
		if (pVelocity->Jerk < MIN_TRAVEL_JERK)  pVelocity->Jerk = MIN_TRAVEL_JERK;  // 1.00 ~ 2.00s => 0 ~ 500,	Unit: 0.01
		break;

	case TRAV_VEL_FORCE:
		if (m_pgmEnv.Trial_Run_Mode)
		{
			//if (pVelocity->Spd > MAX_TRAVEL_VEL_AUTO)  pVelocity->Spd = MAX_TRAVEL_VEL_AUTO;
			if (pVelocity->Spd > MAX_TRAVEL_VEL_FORCE)  pVelocity->Spd = MAX_TRAVEL_VEL_FORCE;
			if (pVelocity->Spd < 1)  pVelocity->Spd = 1;
		}
		else
		{
			if (pVelocity->Spd > MAX_TRAVEL_VEL_FORCE)  pVelocity->Spd = MAX_TRAVEL_VEL_FORCE;
			if (pVelocity->Spd < 1)  pVelocity->Spd = 1;
		}

		if (pVelocity->Acc > MAX_TRAVEL_ACC)  pVelocity->Acc = MAX_TRAVEL_ACC;
		if (pVelocity->Acc < 1)  pVelocity->Acc = 1;

		if (pVelocity->Dec > MAX_TRAVEL_DEC)  pVelocity->Dec = MAX_TRAVEL_DEC;
		if (pVelocity->Dec < 1)  pVelocity->Dec = 1;

		if (pVelocity->Jerk > MAX_TRAVEL_JERK)  pVelocity->Jerk = MAX_TRAVEL_JERK;  // 1.00 ~ 2.00s => 0 ~ 500,	Unit: 0.01      
		if (pVelocity->Jerk < MIN_TRAVEL_JERK)  pVelocity->Jerk = MIN_TRAVEL_JERK;  // 1.00 ~ 2.00s => 0 ~ 500,	Unit: 0.01
		break;

	case TRAV_VEL_ORIGIN:
		if (pVelocity->Spd > MAX_TRAVEL_VEL_CREEP)  pVelocity->Spd = MAX_TRAVEL_VEL_CREEP;
		if (pVelocity->Spd < 1)  pVelocity->Spd = 1;

		if (pVelocity->Acc > MAX_TRAVEL_ACC)  pVelocity->Acc = MAX_TRAVEL_ACC;
		if (pVelocity->Acc < 1)  pVelocity->Acc = 1;

		if (pVelocity->Dec > MAX_TRAVEL_DEC)  pVelocity->Dec = MAX_TRAVEL_DEC;
		if (pVelocity->Dec < 1)  pVelocity->Dec = 1;

		if (pVelocity->Jerk > MAX_TRAVEL_JERK)  pVelocity->Jerk = MAX_TRAVEL_JERK;  // 1.00 ~ 2.00s => 0 ~ 500,	Unit: 0.01      
		if (pVelocity->Jerk < MIN_TRAVEL_JERK)  pVelocity->Jerk = MIN_TRAVEL_JERK;  // 1.00 ~ 2.00s => 0 ~ 500,	Unit: 0.01
		break;

	case TRAV_VEL_CREEP:
		if (pVelocity->Spd > MAX_TRAVEL_VEL_CREEP)  pVelocity->Spd = MAX_TRAVEL_VEL_CREEP;
		if (pVelocity->Spd < 1)  pVelocity->Spd = 1;

		if (pVelocity->Dec > MAX_TRAVEL_DEC)  pVelocity->Dec = MAX_TRAVEL_DEC;
		if (pVelocity->Dec < 1)  pVelocity->Dec = 1;

		pVelocity->Acc = pVelocity->Dec;

		if (pVelocity->Jerk > MAX_TRAVEL_JERK)  pVelocity->Jerk = MAX_TRAVEL_JERK;  // 1.00 ~ 2.00s => 0 ~ 500,	Unit: 0.01      
		if (pVelocity->Jerk < MIN_TRAVEL_JERK)  pVelocity->Jerk = MIN_TRAVEL_JERK;  // 1.00 ~ 2.00s => 0 ~ 500,	Unit: 0.01

		//pVelocity->Acc = 0;
		break;

	case TRAV_VEL_EMG:
		if (pVelocity->Dec > MAX_TRAVEL_DEC)  pVelocity->Dec = MAX_TRAVEL_DEC;
		if (pVelocity->Dec < 1)  pVelocity->Dec = 1;

		if (pVelocity->Jerk > MAX_TRAVEL_JERK)  pVelocity->Jerk = MAX_TRAVEL_JERK;  // 1.00 ~ 2.00s => 0 ~ 500,	Unit: 0.01      
		if (pVelocity->Jerk < MIN_TRAVEL_JERK)  pVelocity->Jerk = MIN_TRAVEL_JERK;  // 1.00 ~ 2.00s => 0 ~ 500,	Unit: 0.01
		break;

		/*
	default:
		if (pVelocity->Spd > MAX_TRAVEL_VEL_MAN)  pVelocity->Spd = MAX_TRAVEL_VEL_MAN;
		if (pVelocity->Spd < 1)  pVelocity->Spd = 1;
		break;
		*/
	}
}

/**
  * @brief Write Travel velocity
  * @param nType
  * @param pVelocity
  * @retval None
  */
void Set_Trav_Velocity_1(INT08U nType, UnitVelocitySTR* pSrcVel, UnitVelocitySTR* pWrVel)
{
	switch (nType)
	{
	case TRAV_VEL_AUTO_H:
	case TRAV_VEL_AUTO_M:
	case TRAV_VEL_AUTO_L:
		if (pSrcVel->Spd > MAX_TRAVEL_VEL_AUTO)  pSrcVel->Spd = MAX_TRAVEL_VEL_AUTO;
		if (pSrcVel->Spd < 1)  pSrcVel->Spd = 1;

		if (pSrcVel->Acc > MAX_TRAVEL_ACC)  pSrcVel->Acc = MAX_TRAVEL_ACC;
		if (pSrcVel->Acc < 1)  pSrcVel->Acc = 1;

		if (pSrcVel->Dec > MAX_TRAVEL_DEC)  pSrcVel->Dec = MAX_TRAVEL_DEC;
		if (pSrcVel->Dec < 1)  pSrcVel->Dec = 1;

		if (pSrcVel->Jerk > MAX_TRAVEL_JERK)  pSrcVel->Jerk = MAX_TRAVEL_JERK;  // 1.00 ~ 2.00s => 0 ~ 500,	Unit: 0.01      
		if (pSrcVel->Jerk < MIN_TRAVEL_JERK)  pSrcVel->Jerk = MIN_TRAVEL_JERK;  // 1.00 ~ 2.00s => 0 ~ 500,	Unit: 0.01
		break;

	case TRAV_VEL_AUTO_DEC_1:
	case TRAV_VEL_AUTO_DEC_2:
		if (pSrcVel->Spd > MAX_TRAVEL_VEL_AUTO)  pSrcVel->Spd = MAX_TRAVEL_VEL_AUTO;
		if (pSrcVel->Spd < 1)  pSrcVel->Spd = 1;
		break;

	case TRAV_VEL_MAN_M:
	case TRAV_VEL_MAN_L:
		if (pSrcVel->Spd > MAX_TRAVEL_VEL_MAN_M)  pSrcVel->Spd = MAX_TRAVEL_VEL_MAN_M;
		if (pSrcVel->Spd < 1)  pSrcVel->Spd = 1;

		if (pSrcVel->Acc > MAX_TRAVEL_ACC)  pSrcVel->Acc = MAX_TRAVEL_ACC;
		if (pSrcVel->Acc < 1)  pSrcVel->Acc = 1;

		if (pSrcVel->Dec > MAX_TRAVEL_DEC)  pSrcVel->Dec = MAX_TRAVEL_DEC;
		if (pSrcVel->Dec < 1)  pSrcVel->Dec = 1;

		if (pSrcVel->Jerk > MAX_TRAVEL_JERK)  pSrcVel->Jerk = MAX_TRAVEL_JERK;  // 1.00 ~ 2.00s => 0 ~ 500,	Unit: 0.01      
		if (pSrcVel->Jerk < MIN_TRAVEL_JERK)  pSrcVel->Jerk = MIN_TRAVEL_JERK;  // 1.00 ~ 2.00s => 0 ~ 500,	Unit: 0.01
		break;

	case TRAV_VEL_FORCE:
		if (m_pgmEnv.Trial_Run_Mode)
		{
			if (pSrcVel->Spd > MAX_TRAVEL_VEL_AUTO)  pSrcVel->Spd = MAX_TRAVEL_VEL_AUTO;
			if (pSrcVel->Spd < 1)  pSrcVel->Spd = 1;
		}
		else
		{
			if (pSrcVel->Spd > MAX_TRAVEL_VEL_MAN_M)  pSrcVel->Spd = MAX_TRAVEL_VEL_MAN_M;
			if (pSrcVel->Spd < 1)  pSrcVel->Spd = 1;
		}

		if (pSrcVel->Acc > MAX_TRAVEL_ACC)  pSrcVel->Acc = MAX_TRAVEL_ACC;
		if (pSrcVel->Acc < 1)  pSrcVel->Acc = 1;

		if (pSrcVel->Dec > MAX_TRAVEL_DEC)  pSrcVel->Dec = MAX_TRAVEL_DEC;
		if (pSrcVel->Dec < 1)  pSrcVel->Dec = 1;

		if (pSrcVel->Jerk > MAX_TRAVEL_JERK)  pSrcVel->Jerk = MAX_TRAVEL_JERK;  // 1.00 ~ 2.00s => 0 ~ 500,	Unit: 0.01      
		if (pSrcVel->Jerk < MIN_TRAVEL_JERK)  pSrcVel->Jerk = MIN_TRAVEL_JERK;  // 1.00 ~ 2.00s => 0 ~ 500,	Unit: 0.01
		break;

	case TRAV_VEL_ORIGIN:
		if (pSrcVel->Spd > MAX_TRAVEL_VEL_MAN_M)  pSrcVel->Spd = MAX_TRAVEL_VEL_MAN_M;
		if (pSrcVel->Spd < 1)  pSrcVel->Spd = 1;

		if (pSrcVel->Acc > MAX_TRAVEL_ACC)  pSrcVel->Acc = MAX_TRAVEL_ACC;
		if (pSrcVel->Acc < 1)  pSrcVel->Acc = 1;

		if (pSrcVel->Dec > MAX_TRAVEL_DEC)  pSrcVel->Dec = MAX_TRAVEL_DEC;
		if (pSrcVel->Dec < 1)  pSrcVel->Dec = 1;

		if (pSrcVel->Jerk > MAX_TRAVEL_JERK)  pSrcVel->Jerk = MAX_TRAVEL_JERK;  // 1.00 ~ 2.00s => 0 ~ 500,	Unit: 0.01      
		if (pSrcVel->Jerk < MIN_TRAVEL_JERK)  pSrcVel->Jerk = MIN_TRAVEL_JERK;  // 1.00 ~ 2.00s => 0 ~ 500,	Unit: 0.01
		break;

	case TRAV_VEL_CREEP:
		if (pSrcVel->Spd > MAX_TRAVEL_VEL_MAN_M)  pSrcVel->Spd = MAX_TRAVEL_VEL_MAN_M;
		if (pSrcVel->Spd < 1)  pSrcVel->Spd = 1;

		if (pSrcVel->Dec > MAX_TRAVEL_DEC)  pSrcVel->Dec = MAX_TRAVEL_DEC;
		if (pSrcVel->Dec < 1)  pSrcVel->Dec = 1;

		if (pSrcVel->Jerk > MAX_TRAVEL_JERK)  pSrcVel->Jerk = MAX_TRAVEL_JERK;  // 1.00 ~ 2.00s => 0 ~ 500,	Unit: 0.01      
		if (pSrcVel->Jerk < MIN_TRAVEL_JERK)  pSrcVel->Jerk = MIN_TRAVEL_JERK;  // 1.00 ~ 2.00s => 0 ~ 500,	Unit: 0.01

		//pVelocity->Acc = 0;
		break;

	case TRAV_VEL_EMG:
		if (pSrcVel->Dec > MAX_TRAVEL_DEC)  pSrcVel->Dec = MAX_TRAVEL_DEC;
		if (pSrcVel->Dec < 1)  pSrcVel->Dec = 1;

		if (pSrcVel->Jerk > MAX_TRAVEL_JERK)  pSrcVel->Jerk = MAX_TRAVEL_JERK;  // 1.00 ~ 2.00s => 0 ~ 500,	Unit: 0.01      
		if (pSrcVel->Jerk < MIN_TRAVEL_JERK)  pSrcVel->Jerk = MIN_TRAVEL_JERK;  // 1.00 ~ 2.00s => 0 ~ 500,	Unit: 0.01
		break;

		/*
	default:
		if (pVelocity->Spd > MAX_TRAVEL_VEL_MAN)  pVelocity->Spd = MAX_TRAVEL_VEL_MAN;
		if (pVelocity->Spd < 1)  pVelocity->Spd = 1;
		break;
		*/
	}

	memcpy((INT08U*)pWrVel, (INT08U*)pSrcVel, sizeof(UnitVelocitySTR));
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Trav_InPostion_Tolerance(ParamTravelDriveSTR* pSetting)
{
	if (pSetting->InPos_Tolerance < MIN_TRAV_IN_POS)
		pSetting->InPos_Tolerance = MIN_TRAV_IN_POS;

	if (pSetting->InPos_Tolerance > MAX_TRAV_IN_POS)
		pSetting->InPos_Tolerance = MAX_TRAV_IN_POS;
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Trav_InPostion_Tolerance_1(ParamTravelDriveSTR* pSetting, ParamTravelDriveSTR* pWrBuf)
{
	if (pSetting->InPos_Tolerance < MIN_TRAV_IN_POS)
		pSetting->InPos_Tolerance = MIN_TRAV_IN_POS;

	if (pSetting->InPos_Tolerance > MAX_TRAV_IN_POS)
		pSetting->InPos_Tolerance = MAX_TRAV_IN_POS;

	pWrBuf->InPos_Tolerance = pSetting->InPos_Tolerance;
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Trav_InPostion_Hysteresis(ParamTravelDriveSTR* pSetting)
{
	if (pSetting->InPos_Hysteresis < MIN_TRAV_HYSTERESIS)
		pSetting->InPos_Hysteresis = MIN_TRAV_HYSTERESIS;

	if (pSetting->InPos_Hysteresis > MAX_TRAV_HYSTERESIS)
		pSetting->InPos_Hysteresis = MAX_TRAV_HYSTERESIS;
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Trav_InPostion_Hysteresis_1(ParamTravelDriveSTR* pSetting, ParamTravelDriveSTR* pWrBuf)
{
	if (pSetting->InPos_Hysteresis < MIN_TRAV_HYSTERESIS)
		pSetting->InPos_Hysteresis = MIN_TRAV_HYSTERESIS;

	if (pSetting->InPos_Hysteresis > MAX_TRAV_HYSTERESIS)
		pSetting->InPos_Hysteresis = MAX_TRAV_HYSTERESIS;

	pWrBuf->InPos_Hysteresis = pSetting->InPos_Hysteresis;
}


/**
  * @brief
  * @param
  * @retval None
  */
void Set_Trav_Manual_Drive(ParamTravelDriveSTR* pSetting)
{
	if (pSetting->ManualDrive.Torque_Alarm < MIN_TRAV_OVERTORQUE)
		pSetting->ManualDrive.Torque_Alarm = MIN_TRAV_OVERTORQUE;	// 10.0%

	if (pSetting->ManualDrive.Torque_Alarm > MAX_TRAV_OVERTORQUE)
		pSetting->ManualDrive.Torque_Alarm = MAX_TRAV_OVERTORQUE;	// 200.0%

	if (pSetting->ManualDrive.StartPos >= pSetting->ManualDrive.EndPos)
	{
		pSetting->ManualDrive.StartPos = 0;
		pSetting->ManualDrive.EndPos = 0;
	}
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Trav_Manual_Drive_1(ParamTravelDriveSTR* pSetting, ParamTravelDriveSTR* pWrBuf)
{
	if (pSetting->ManualDrive.Torque_Alarm < MIN_TRAV_OVERTORQUE)
		pSetting->ManualDrive.Torque_Alarm = MIN_TRAV_OVERTORQUE;	// 10.0%

	if (pSetting->ManualDrive.Torque_Alarm > MAX_TRAV_OVERTORQUE)
		pSetting->ManualDrive.Torque_Alarm = MAX_TRAV_OVERTORQUE;	// 200.0%

	pWrBuf->ManualDrive.Torque_Alarm = pSetting->ManualDrive.Torque_Alarm;

	if (pSetting->ManualDrive.StartPos < pSetting->ManualDrive.EndPos)
	{
		pWrBuf->ManualDrive.StartPos = pSetting->ManualDrive.StartPos;
		pWrBuf->ManualDrive.EndPos = pSetting->ManualDrive.EndPos;
	}
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Trav_BrakeOn_DelayTime(ParamTravelDriveSTR* pSetting)
{
	/*
	if (pSetting->BrakeOnDelayTime < MIN_BRAKE_ON_TIME)
		pSetting->BrakeOnDelayTime = MIN_BRAKE_ON_TIME;
*/
	if (pSetting->BrakeOnDelayTime > MAX_BRAKE_ON_TIME)
		pSetting->BrakeOnDelayTime = MAX_BRAKE_ON_TIME;		// 600.00s
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Trav_BrakeOn_DelayTime_1(ParamTravelDriveSTR* pSetting, ParamTravelDriveSTR* pWrBuf)
{
	/*
	if (pSetting->BrakeOnDelayTime < MIN_BRAKE_ON_TIME)
		pSetting->BrakeOnDelayTime = MIN_BRAKE_ON_TIME;
		*/
	if (pSetting->BrakeOnDelayTime > MAX_BRAKE_ON_TIME)
		pSetting->BrakeOnDelayTime = MAX_BRAKE_ON_TIME;		// 600.00s

	pWrBuf->BrakeOnDelayTime = pSetting->BrakeOnDelayTime;
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Trav_Origin_Position(ParamTravelDriveSTR* pSetting)
{

}


INT08U Set_Trav_Home_Speed_Mode(INT08U nSetValue)
{
	if (nSetValue > 6)
	{
		nSetValue = m_ExtSEnv2.TravDrive.Home_Spd_Mode;
	}

	return nSetValue;
}

INT32S Set_Trav_Home_StationNo(INT32S nSetValue)
{
	INT08U nStationNo = 0;

	nStationNo = (INT08U)nSetValue;

	if (nStationNo > (INT32S)m_ExtSEnv1.StationEnv.TotalUseCnt)
	{
		nStationNo = 0;
	}

	return nStationNo;
}

INT32S Set_Trav_Home_BayNo(INT32S nSetValue)
{
	INT08U nBayNo = 0;

	nBayNo = (INT08U)nSetValue;

	if (nBayNo > (INT32S)m_ExtSEnv0.RackConfig.BayCount)
	{
		nBayNo = 0;
	}

	return nBayNo;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Trav_Home_Position(ParamTravelDriveSTR* pSetting)
{
	pSetting->Home_Spd_Mode = Set_Trav_Home_Speed_Mode(pSetting->Home_Spd_Mode);
	pSetting->Home_Pos_StationNo = Set_Trav_Home_StationNo(pSetting->Home_Pos_StationNo);
	pSetting->Home_Pos_BayNo = Set_Trav_Home_BayNo(pSetting->Home_Pos_BayNo);

	return 1;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Trav_Home_Position_1(ParamTravelDriveSTR* pSetting, ParamTravelDriveSTR* pWrBuf)
{
	pSetting->Home_Spd_Mode = Set_Trav_Home_Speed_Mode(pSetting->Home_Spd_Mode);
	pSetting->Home_Pos_StationNo = Set_Trav_Home_StationNo(pSetting->Home_Pos_StationNo);
	pSetting->Home_Pos_BayNo = Set_Trav_Home_BayNo(pSetting->Home_Pos_BayNo);

	pWrBuf->Home_Spd_Mode = pSetting->Home_Spd_Mode;
	pWrBuf->Home_Pos_StationNo = pSetting->Home_Pos_StationNo;
	pWrBuf->Home_Pos_BayNo = pSetting->Home_Pos_BayNo;

	return 1;
}

INT08U Set_Trav_Maintenance_Speed_Mode(INT08U nSetValue)
{
	if (nSetValue > 6)
	{
		nSetValue = m_ExtSEnv2.TravDrive.Maintenance_Spd_Mode;
	}

	return nSetValue;
}

INT32S Set_Trav_Maintenance_mm(INT32S nSetValue)
{
	if (nSetValue == 0)
	{
		nSetValue = m_ExtSEnv2.TravDrive.ManualDrive.StartPos;
	}
	else
	{
		//수동운전 시작~끝위치 이내인지 확인필요.
		if (m_ExtSEnv2.TravDrive.ManualDrive.StartPos)
		{
			if (nSetValue < m_ExtSEnv2.TravDrive.ManualDrive.StartPos)
			{
				nSetValue = m_ExtSEnv2.TravDrive.ManualDrive.StartPos;
			}
		}
		else
		{
			if (m_ExtSEnv2.TravDrive.Maintenance_Pos)
			{
				nSetValue = m_ExtSEnv2.TravDrive.Maintenance_Pos;
			}
		}

		if (m_ExtSEnv2.TravDrive.ManualDrive.EndPos)
		{
			if (nSetValue > m_ExtSEnv2.TravDrive.ManualDrive.EndPos)
			{
				nSetValue = m_ExtSEnv2.TravDrive.ManualDrive.EndPos;
			}
		}
		else
		{
			if (m_ExtSEnv2.TravDrive.Maintenance_Pos)
			{
				nSetValue = m_ExtSEnv2.TravDrive.Maintenance_Pos;
			}
		}
	}

	return nSetValue;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Trav_Maintenance_Position(ParamTravelDriveSTR* pSetting)
{
	//INT08U nSaveFlag = 0;
	//INT32S nTmpPostion = 0;

	pSetting->Maintenance_Spd_Mode = Set_Trav_Maintenance_Speed_Mode(pSetting->Maintenance_Spd_Mode);
	pSetting->Maintenance_Pos = Set_Trav_Maintenance_mm(pSetting->Maintenance_Pos);

	return 1;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Trav_Maintenance_Position_1(ParamTravelDriveSTR* pSetting, ParamTravelDriveSTR* pWrBuf)
{
	//INT08U nSaveFlag = 0;
	//INT32S nTmpPostion = 0;

	pSetting->Maintenance_Spd_Mode = Set_Trav_Home_Speed_Mode(pSetting->Maintenance_Spd_Mode);
	pSetting->Maintenance_Pos = Set_Trav_Maintenance_mm(pSetting->Maintenance_Pos);

	pWrBuf->Maintenance_Spd_Mode = pSetting->Maintenance_Spd_Mode;
	pWrBuf->Maintenance_Pos = pSetting->Maintenance_Pos;

	return 1;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Trav_DecelationRange_Mode(ParamTravelDriveSTR* pSetting)
{
	INT08U nSaveFlag = 1;

	/*
	if (pSetting->DecelRange1_Mode <= 4)
	{
		nSaveFlag = 1;
	}

	if (pSetting->DecelRange2_Mode <= 4)
	{
		nSaveFlag = 1;
	}
	*/
	if (pSetting->DecelRange1_Mode > 4)
	{
		//pSetting->DecelRange1_Mode = 0;
		pSetting->DecelRange1_Mode = m_ExtSEnv2.TravDrive.DecelRange1_Mode;
	}

	if (pSetting->DecelRange2_Mode > 4)
	{
		//pSetting->DecelRange2_Mode = 0;
		pSetting->DecelRange2_Mode = m_ExtSEnv2.TravDrive.DecelRange2_Mode;
	}

	return nSaveFlag;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Trav_DecelationRange_Mode_1(ParamTravelDriveSTR* pSetting, ParamTravelDriveSTR* pWrBuf)
{
	INT08U nSaveFlag = 1;

	/*
	if (pSetting->DecelRange1_Mode <= 4)
	{
		pWrBuf->DecelRange1_Mode = pSetting->DecelRange1_Mode;
		nSaveFlag = 1;
	}

	if (pSetting->DecelRange2_Mode <= 4)
	{
		pWrBuf->DecelRange2_Mode = pSetting->DecelRange2_Mode;
		nSaveFlag = 1;
	}
	*/

	if (pSetting->DecelRange1_Mode > 4)
	{
		pSetting->DecelRange1_Mode = m_ExtSEnv2.TravDrive.DecelRange1_Mode;
	}

	if (pSetting->DecelRange2_Mode > 4)
	{
		pSetting->DecelRange2_Mode = m_ExtSEnv2.TravDrive.DecelRange2_Mode;
	}

	pWrBuf->DecelRange1_Mode = pSetting->DecelRange1_Mode;
	pWrBuf->DecelRange2_Mode = pSetting->DecelRange2_Mode;

	return nSaveFlag;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Trav_SoftLimit_Error(ParamTravelDriveSTR* pSetting)
{
	INT08U nSaveFlag = 1;

	/*
	if (pSetting->SoftLimitErr.CheckFlag <= 3)
	{
		nSaveFlag = 1;
	}
	*/
	if (pSetting->SoftLimitErr.CheckFlag > 3)
	{
		//nSaveFlag = 1;
		//pSetting->SoftLimitErr.CheckFlag = 0;
		pSetting->SoftLimitErr.CheckFlag = m_ExtSEnv2.TravDrive.SoftLimitErr.CheckFlag;
	}

	if (pSetting->SoftLimitErr.HomePos == 0)
	{
		pSetting->SoftLimitErr.HomePos = m_ExtSEnv2.TravDrive.ManualDrive.StartPos;
	}

	if (pSetting->SoftLimitErr.EndPos == 0)
	{
		pSetting->SoftLimitErr.EndPos = m_ExtSEnv2.TravDrive.ManualDrive.EndPos;
	}

	return nSaveFlag;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Trav_SoftLimit_Error_1(ParamTravelDriveSTR* pSetting, ParamTravelDriveSTR* pWrBuf)
{
	INT08U nSaveFlag = 1;

	/*
	if (pSetting->SoftLimitErr.CheckFlag <= 3)
	{
		nSaveFlag = 1;
	}
	*/
	if (pSetting->SoftLimitErr.CheckFlag > 3)
	{
		//nSaveFlag = 1;
		pSetting->SoftLimitErr.CheckFlag = m_ExtSEnv2.TravDrive.SoftLimitErr.CheckFlag;
	}

	if (pSetting->SoftLimitErr.HomePos == 0)
	{
		pSetting->SoftLimitErr.HomePos = m_ExtSEnv2.TravDrive.ManualDrive.StartPos;
	}

	pWrBuf->SoftLimitErr.HomePos = pSetting->SoftLimitErr.HomePos;

	if (pSetting->SoftLimitErr.EndPos == 0)
	{
		pSetting->SoftLimitErr.EndPos = m_ExtSEnv2.TravDrive.ManualDrive.EndPos;
	}

	pWrBuf->SoftLimitErr.CheckFlag = pSetting->SoftLimitErr.CheckFlag;
	pWrBuf->SoftLimitErr.EndPos = pSetting->SoftLimitErr.EndPos;

	return nSaveFlag;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Trav_SoftDecelation_Error(ParamTravelDriveSTR* pSetting)
{
	INT08U nSaveFlag = 1;

	/*
	if (pSetting->SoftDecelErr.CheckFlag < 2)
	{
		nSaveFlag = 1;
	}
	*/
	if (pSetting->SoftDecelErr.CheckFlag > 2)
	{
		//nSaveFlag = 1;
		pSetting->SoftDecelErr.CheckFlag = m_ExtSEnv2.TravDrive.SoftDecelErr.CheckFlag;
	}

	if (pSetting->SoftDecelErr.ErrorOffset > 1000)
	{
		pSetting->SoftDecelErr.ErrorOffset = 1000;
	}

	return nSaveFlag;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Trav_SoftDecelation_Error_1(ParamTravelDriveSTR* pSetting, ParamTravelDriveSTR* pWrBuf)
{
	INT08U nSaveFlag = 1;

	/*
	if (pSetting->SoftDecelErr.CheckFlag < 2)
	{
		nSaveFlag = 1;

	}
	*/

	if (pSetting->SoftDecelErr.CheckFlag > 2)
	{
		pSetting->SoftDecelErr.CheckFlag = m_ExtSEnv2.TravDrive.SoftDecelErr.CheckFlag;
	}

	if (pSetting->SoftDecelErr.ErrorOffset > 1000)
	{
		pSetting->SoftDecelErr.ErrorOffset = 1000;
	}

	memcpy((INT08U*)&pWrBuf->SoftDecelErr, (INT08U*)&pSetting->SoftDecelErr, sizeof(SoftDecelErrorSTR));

	/*
	pWrBuf->SoftDecelErr.CheckFlag = pSetting->SoftDecelErr.CheckFlag;
	pWrBuf->SoftDecelErr.ErrorOffset = pSetting->SoftDecelErr.ErrorOffset;
	pWrBuf->SoftDecelErr.Braking_Distance_Auto_H_Decel = pSetting->SoftDecelErr.Braking_Distance_Auto_H_Decel;
	pWrBuf->SoftDecelErr.Braking_Distance_Auto_M_Decel = pSetting->SoftDecelErr.Braking_Distance_Auto_M_Decel;
	pWrBuf->SoftDecelErr.Braking_Distance_Auto_H_Emg = pSetting->SoftDecelErr.Braking_Distance_Auto_H_Emg;
	pWrBuf->SoftDecelErr.Braking_Distance_Auto_M_Emg = pSetting->SoftDecelErr.Braking_Distance_Auto_M_Emg;
	*/

	return nSaveFlag;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Trav_OriginDog_Postion_Error(ParamTravelDriveSTR* pSetting)
{
	INT08U nSaveFlag = 1;

	/*
	if (pSetting->OriginDogErr.CheckFlag <= 3)
	{
		nSaveFlag = 1;
	}
	*/

	if (pSetting->OriginDogErr.CheckFlag > 3)
	{
		pSetting->OriginDogErr.CheckFlag = m_ExtSEnv2.TravDrive.OriginDogErr.CheckFlag;
	}

	if (pSetting->OriginDogErr.ErrorOffset > 1000)
	{
		pSetting->OriginDogErr.ErrorOffset = 1000;
	}

	return nSaveFlag;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Trav_OriginDog_Postion_Error_1(ParamTravelDriveSTR* pSetting, ParamTravelDriveSTR* pWrBuf)
{
	INT08U nSaveFlag = 1;

	/*
	if (pSetting->OriginDogErr.CheckFlag <= 3)
	{
		pWrBuf->OriginDogErr.CheckFlag = pSetting->OriginDogErr.CheckFlag;
		nSaveFlag = 1;
	}
	*/
	if (pSetting->OriginDogErr.CheckFlag > 3)
	{
		pSetting->OriginDogErr.CheckFlag = m_ExtSEnv2.TravDrive.OriginDogErr.CheckFlag;
	}

	if (pSetting->OriginDogErr.ErrorOffset > 1000)
	{
		pSetting->OriginDogErr.ErrorOffset = 1000;
	}

	pWrBuf->OriginDogErr.CheckFlag = pSetting->OriginDogErr.CheckFlag;
	pWrBuf->OriginDogErr.ErrorOffset = pSetting->OriginDogErr.ErrorOffset;
	pWrBuf->OriginDogErr.HomePos1 = pSetting->OriginDogErr.HomePos1;
	//pWrBuf->OriginDogErr.HomePos2 = pSetting->OriginDogErr.HomePos2;
	pWrBuf->OriginDogErr.EndPos1 = pSetting->OriginDogErr.EndPos1;
	//pWrBuf->OriginDogErr.EndPos2 = pSetting->OriginDogErr.EndPos2;

	return nSaveFlag;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Trav_DecelDog_Position_Error(ParamTravelDriveSTR* pSetting)
{
	INT08U nSaveFlag = 1;

	/*
	if (pSetting->DecelDogErr.CheckFlag <= 3)
	{
		nSaveFlag = 1;
	}
	*/

	if (pSetting->DecelDogErr.CheckFlag > 3)
	{
		pSetting->DecelDogErr.CheckFlag = m_ExtSEnv2.TravDrive.DecelDogErr.CheckFlag;
	}

	if (pSetting->DecelDogErr.Offset > 1000)
	{
		pSetting->DecelDogErr.Offset = 1000;
	}

	return nSaveFlag;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Trav_DecelDog_Postion_Error_1(ParamTravelDriveSTR* pSetting, ParamTravelDriveSTR* pWrBuf)
{
	INT08U nSaveFlag = 1;

	/*
	if (pSetting->DecelDogErr.CheckFlag <= 3)
	{
		pWrBuf->DecelDogErr.CheckFlag = pSetting->DecelDogErr.CheckFlag;
		nSaveFlag = 1;
	}
	*/
	if (pSetting->DecelDogErr.CheckFlag > 3)
	{
		pSetting->DecelDogErr.CheckFlag = m_ExtSEnv2.TravDrive.DecelDogErr.CheckFlag;
	}

	if (pSetting->DecelDogErr.Offset > 1000)
	{
		pSetting->DecelDogErr.Offset = 1000;
	}

	pWrBuf->DecelDogErr.CheckFlag = pSetting->DecelDogErr.CheckFlag;
	pWrBuf->DecelDogErr.Offset = pSetting->DecelDogErr.Offset;
	pWrBuf->DecelDogErr.Fwd1_Pos1 = pSetting->DecelDogErr.Fwd1_Pos1;
	pWrBuf->DecelDogErr.Fwd1_Pos2 = pSetting->DecelDogErr.Fwd1_Pos2;
	pWrBuf->DecelDogErr.Fwd2_Pos1 = pSetting->DecelDogErr.Fwd2_Pos1;
	pWrBuf->DecelDogErr.Rvr1_Pos1 = pSetting->DecelDogErr.Rvr1_Pos1;
	pWrBuf->DecelDogErr.Rvr1_Pos2 = pSetting->DecelDogErr.Rvr1_Pos2;
	pWrBuf->DecelDogErr.Rvr2_Pos1 = pSetting->DecelDogErr.Rvr2_Pos1;

	return nSaveFlag;
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Trav_Invertor_Param(ParamTravelDriveSTR* pSetting)
{
	if (pSetting->InvParam.RefOffset < (-999999))
	{
		pSetting->InvParam.RefOffset = (-999999);
	}

	if (pSetting->InvParam.RefOffset > (999999))
	{
		pSetting->InvParam.RefOffset = (999999);
	}

	if (pSetting->InvParam.PosGain > (10000000))		// Position gain 0.000 ~ 10000.000
	{
		pSetting->InvParam.PosGain = (10000000);
	}

	if (pSetting->InvParam.PosWindow > (200))			// Position Offset 0 ~ 200
	{
		pSetting->InvParam.PosWindow = (200);
	}
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Trav_Invertor_Param_1(ParamTravelDriveSTR* pSetting, ParamTravelDriveSTR* pWrBuf)
{
	if (pSetting->InvParam.RefOffset < (-999999))
	{
		pSetting->InvParam.RefOffset = (-999999);
	}

	if (pSetting->InvParam.RefOffset > (999999))
	{
		pSetting->InvParam.RefOffset = (999999);
	}

	if (pSetting->InvParam.PosGain > (10000000))		// Position gain 0.000 ~ 10000.000
	{
		pSetting->InvParam.PosGain = (10000000);
	}

	if (pSetting->InvParam.PosWindow > (200))			// Position Offset 0 ~ 200
	{
		pSetting->InvParam.PosWindow = (200);
	}

	memcpy((INT08U*)&pWrBuf->InvParam, (INT08U*)&pSetting->InvParam, sizeof(InvertorParam));
}

void Save_Travel_Drive_Param(ParamTravelDriveSTR* pSetting)
{
	INT16U crc = 0;

	ExtFlash_ReadData(EXT_PARAMETER_SET_ADDR_START, (INT08U*)&m_ExtSEnv2, sizeof(ExtFlashSEnv2));

	if (memcmp((INT08U*)&m_ExtSEnv2.TravDrive, (INT08U*)pSetting, sizeof(ParamTravelDriveSTR)))
	{
		memcpy((INT08U*)m_ExtSEnv2.InitTravelDriveCode, TRAVEL_DRIVE_PARAM_INIT_CODE, sizeof(INT08U) * 4);
		memcpy((INT08U*)&m_ExtSEnv2.TravDrive, (INT08U*)pSetting, sizeof(ParamTravelDriveSTR));

		m_ExtSEnv2.CRC_TravelDrive = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv2.TravDrive, sizeof(ParamTravelDriveSTR));

		ExtFlash_WriteData(EXT_PARAMETER_SET_ADDR_START, (INT08U*)&m_ExtSEnv2, sizeof(ExtFlashSEnv2));

#if DEBUG_MSG
		printf("[DEBUG_APP] Travel Drive Parameter save to external flash. DataCRC: 0x%04x\r\n", m_ExtSEnv2.CRC_TravelDrive);
#endif
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Travel Drive Parameter same setting. Do not save in external flash.\r\n");
#endif
	}
}

/**
  * @brief
  * @param None
  * @retval None
  */
void Default_Travel_Drive_Param_Init(void)
{
	INT08U i = 0;
	INT16U crc = 0x0000;

	ParamTravelDriveSTR nInitParam;

	memset((INT08U*)&nInitParam, 0, sizeof(ParamTravelDriveSTR));

	for (i = 0; i < MAX_TRAV_VELOCITY_CNT; i++)
	{
		/*
		nInitParam.Vel[i].Spd = 1;
		nInitParam.Vel[i].Acc = MAX_TRAVEL_ACC;
		nInitParam.Vel[i].Dec = MAX_TRAVEL_DEC;
		nInitParam.Vel[i].Jerk = MIN_TRAVEL_JERK;
		*/
		nInitParam.Vel[i].Spd = 0;
	}

	nInitParam.InPos_Tolerance = DEF_TRAV_IN_POS_OFFSET;
	nInitParam.InPos_Hysteresis = DEF_TRAV_POS_HYSTERESIS;

	nInitParam.ManualDrive.Torque_Alarm = 500;	// 50.0%
	nInitParam.ManualDrive.StartPos = 0;
	nInitParam.ManualDrive.EndPos = 0;

	nInitParam.BrakeOnDelayTime = 1000;		// 10.00s

	nInitParam.Home_Spd_Mode = DRIVE_VELOCITY_AUTO_L;
	nInitParam.Home_Pos_StationNo = 0;

	nInitParam.Maintenance_Spd_Mode = DRIVE_VELOCITY_AUTO_L;
	nInitParam.Maintenance_Pos = 0;

	nInitParam.DecelRange1_Mode = DECEL_MODE_NOT_USE;
	nInitParam.DecelRange2_Mode = DECEL_MODE_NOT_USE;

	nInitParam.SoftLimitErr.CheckFlag = SOFT_ERROR_MODE_NOT_USE;
	nInitParam.SoftLimitErr.HomePos = 0;
	nInitParam.SoftLimitErr.EndPos = 0;

	nInitParam.SoftDecelErr.CheckFlag = 0;
	nInitParam.SoftDecelErr.ErrorOffset = 0;
	nInitParam.SoftDecelErr.Braking_Distance_Auto_H_Decel = 0;
	nInitParam.SoftDecelErr.Braking_Distance_Auto_M_Decel = 0;
	nInitParam.SoftDecelErr.Braking_Distance_Auto_H_Emg = 0;
	nInitParam.SoftDecelErr.Braking_Distance_Auto_M_Emg = 0;

	nInitParam.OriginDogErr.CheckFlag = SOFT_ERROR_MODE_NOT_USE;
	nInitParam.OriginDogErr.ErrorOffset = 0;
	nInitParam.OriginDogErr.HomePos1 = 0;
	nInitParam.OriginDogErr.Reseved0 = 0;
	nInitParam.OriginDogErr.EndPos1 = 0;
	nInitParam.OriginDogErr.Reseved1 = 0;

	nInitParam.DecelDogErr.CheckFlag = SOFT_ERROR_MODE_NOT_USE;
	nInitParam.DecelDogErr.Offset = 0;
	nInitParam.DecelDogErr.Fwd1_Pos1 = 0;
	nInitParam.DecelDogErr.Fwd1_Pos2 = 0;
	nInitParam.DecelDogErr.Fwd2_Pos1 = 0;
	nInitParam.DecelDogErr.Reseved0 = 0;
	nInitParam.DecelDogErr.Rvr1_Pos1 = 0;
	nInitParam.DecelDogErr.Rvr1_Pos2 = 0;
	nInitParam.DecelDogErr.Rvr2_Pos1 = 0;
	nInitParam.DecelDogErr.Reseved1 = 0;

	nInitParam.InvParam.RefOffset = 1000;
	//nInitParam.InvParam.RefOffset = 41;		// TestBed Reference 값
	nInitParam.InvParam.PosGain = 331;			// KCTC SRM 기본값 0.331
	nInitParam.InvParam.PosWindow = 3;

	ExtFlash_ReadData(EXT_PARAMETER_SET_ADDR_START, (INT08U*)&m_ExtSEnv2, sizeof(ExtFlashSEnv2));

	memcpy((INT08U*)m_ExtSEnv2.InitTravelDriveCode, TRAVEL_DRIVE_PARAM_INIT_CODE, sizeof(INT08U) * 4);
	memcpy((INT08U*)&m_ExtSEnv2.TravDrive, (INT08U*)&nInitParam, sizeof(ParamTravelDriveSTR));

	m_ExtSEnv2.CRC_TravelDrive = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv2.TravDrive, sizeof(ParamTravelDriveSTR));

	ExtFlash_WriteData(EXT_PARAMETER_SET_ADDR_START, (INT08U*)&m_ExtSEnv2, sizeof(ExtFlashSEnv2));
}

/**
  * @brief
  * @param None
  * @retval None
  */
void Travel_Drive_Param_Init()
{
	INT16U crc = 0x0000;
	INT16U nSaveFlag = 0;

	ExtFlash_ReadData(EXT_PARAMETER_SET_ADDR_START, (INT08U*)&m_ExtSEnv2, sizeof(ExtFlashSEnv2));

	if (checkFusingString((INT08U*)m_ExtSEnv2.InitTravelDriveCode, (INT08U*)TRAVEL_DRIVE_PARAM_INIT_CODE, 4))
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Travel Drive Parameter Empty. Initialize Default Value.\n\r");
#endif
		Default_Travel_Drive_Param_Init();

		save_error_code(ERROR1_MCU_PARAM_DATA, 10, 1);
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Checked Travel Drive Parameter.\n\r");
#endif
		// 시운전모드(셋업+강제모드) 에서는 최대설정값이 고속으로 설정될수 있음.
		// 시스템 리셋시 저속으로 재조정.
		if (m_ExtSEnv2.TravDrive.Vel[TRAV_VEL_FORCE].Spd > MAX_TRAVEL_VEL_MAN_M)
		{
			m_ExtSEnv2.TravDrive.Vel[TRAV_VEL_FORCE].Spd = MAX_TRAVEL_VEL_MAN_M;
			nSaveFlag = 1;
		}

		if (nSaveFlag)
		{
			m_ExtSEnv2.CRC_TravelDrive = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv2.TravDrive, sizeof(ParamTravelDriveSTR));
			ExtFlash_WriteData(EXT_PARAMETER_SET_ADDR_START, (INT08U*)&m_ExtSEnv2, sizeof(ExtFlashSEnv2));
			ExtFlash_ReadData(EXT_PARAMETER_SET_ADDR_START, (INT08U*)&m_ExtSEnv2, sizeof(ExtFlashSEnv2));
		}

		crc = 0x0000;
		crc = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv2.TravDrive, sizeof(ParamTravelDriveSTR));

		if (m_ExtSEnv2.CRC_TravelDrive != crc)
		{
#if DEBUG_MSG
			printf("[DEBUG_APP] Not equal CRC Travel Drive Parameter. DataCRC: 0x%04x, CalcCRC: 0x%04x\n\r",
				m_ExtSEnv2.CRC_TravelDrive, crc);
#endif
			save_error_code(ERROR1_MCU_PARAM_DATA, 10, 0);
		}
		else
		{
#if DEBUG_MSG
			printf("[DEBUG_APP] Equal CRC Travel Drive Parameter.DataCRC: 0x%04x, CalcCRC: 0x%04x\n\r",
				m_ExtSEnv2.CRC_TravelDrive, crc);
#endif

		}
	}
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Check_Available_Trav_InPostion_Tolerance()
{
	if ((m_ExtSEnv2.TravDrive.InPos_Tolerance < MIN_TRAV_IN_POS)
		|| (m_ExtSEnv2.TravDrive.InPos_Tolerance > MAX_TRAV_IN_POS))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Check_Available_Trav_InPostion_Hysteresis()
{
	if ((m_ExtSEnv2.TravDrive.InPos_Hysteresis < MIN_TRAV_HYSTERESIS)
		|| (m_ExtSEnv2.TravDrive.InPos_Hysteresis > MAX_TRAV_HYSTERESIS))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/**
  * @brief Write Lift velocity
  * @param nType
  * @param pVelocity
  * @retval None
  */
void Set_Lift_Velocity(INT08U nType, UnitVelocitySTR* pVelocity)
{
	switch (nType)
	{
	case LIFT_VEL_AUTO_H:
		if (pVelocity->Spd > MAX_LIFT_VEL_AUTO_H)  pVelocity->Spd = MAX_LIFT_VEL_AUTO_H;
		if (pVelocity->Spd < 1)  pVelocity->Spd = 1;

		if (pVelocity->Acc > MAX_LIFT_ACC)  pVelocity->Acc = MAX_LIFT_ACC;
		if (pVelocity->Acc < 1)  pVelocity->Acc = 1;

		if (pVelocity->Dec > MAX_LIFT_DEC)	pVelocity->Dec = MAX_LIFT_DEC;
		if (pVelocity->Dec < 1)  pVelocity->Dec = 1;

		if (pVelocity->Jerk > MAX_LIFT_JERK)  pVelocity->Jerk = MAX_LIFT_JERK;
		if (pVelocity->Jerk < MIN_LIFT_JERK)  pVelocity->Jerk = MIN_LIFT_JERK;
		break;

	case LIFT_VEL_AUTO_M:
	case LIFT_VEL_AUTO_L:
		if (pVelocity->Spd > MAX_LIFT_VEL_AUTO_M)  pVelocity->Spd = MAX_LIFT_VEL_AUTO_M;
		if (pVelocity->Spd < 1)  pVelocity->Spd = 1;

		if (pVelocity->Acc > MAX_LIFT_ACC)  pVelocity->Acc = MAX_LIFT_ACC;
		if (pVelocity->Acc < 1)  pVelocity->Acc = 1;

		if (pVelocity->Dec > MAX_LIFT_DEC)	pVelocity->Dec = MAX_LIFT_DEC;
		if (pVelocity->Dec < 1)  pVelocity->Dec = 1;

		if (pVelocity->Jerk > MAX_LIFT_JERK)  pVelocity->Jerk = MAX_LIFT_JERK;
		if (pVelocity->Jerk < MIN_LIFT_JERK)  pVelocity->Jerk = MIN_LIFT_JERK;
		break;

	case LIFT_VEL_AUTO_DEC_1:
	case LIFT_VEL_AUTO_DEC_2:
		if (pVelocity->Spd > MAX_LIFT_VEL_AUTO_H)  pVelocity->Spd = MAX_LIFT_VEL_AUTO_H;
		if (pVelocity->Spd < 1)  pVelocity->Spd = 1;
		break;


	case LIFT_VEL_MAN_M:
		if (pVelocity->Spd > MAX_LIFT_VEL_MAN_M)  pVelocity->Spd = MAX_LIFT_VEL_MAN_M;
		if (pVelocity->Spd < 1)  pVelocity->Spd = 1;

		if (pVelocity->Acc > MAX_LIFT_ACC)  pVelocity->Acc = MAX_LIFT_ACC;
		if (pVelocity->Acc < 1)  pVelocity->Acc = 1;

		if (pVelocity->Dec > MAX_LIFT_DEC)	pVelocity->Dec = MAX_LIFT_DEC;
		if (pVelocity->Dec < 1)  pVelocity->Dec = 1;

		if (pVelocity->Jerk > MAX_LIFT_JERK)  pVelocity->Jerk = MAX_LIFT_JERK;
		if (pVelocity->Jerk < MIN_LIFT_JERK)  pVelocity->Jerk = MIN_LIFT_JERK;
		break;

	case LIFT_VEL_MAN_L:
		if (pVelocity->Spd > MAX_LIFT_VEL_MAN_L)  pVelocity->Spd = MAX_LIFT_VEL_MAN_L;
		if (pVelocity->Spd < 1)  pVelocity->Spd = 1;

		if (pVelocity->Acc > MAX_LIFT_ACC)  pVelocity->Acc = MAX_LIFT_ACC;
		if (pVelocity->Acc < 1)  pVelocity->Acc = 1;

		if (pVelocity->Dec > MAX_LIFT_DEC)	pVelocity->Dec = MAX_LIFT_DEC;
		if (pVelocity->Dec < 1)  pVelocity->Dec = 1;

		if (pVelocity->Jerk > MAX_LIFT_JERK)  pVelocity->Jerk = MAX_LIFT_JERK;
		if (pVelocity->Jerk < MIN_LIFT_JERK)  pVelocity->Jerk = MIN_LIFT_JERK;
		break;

	case LIFT_VEL_FORCE:
		if (m_pgmEnv.Trial_Run_Mode)
		{
			if (pVelocity->Spd > MAX_LIFT_VEL_AUTO_H)  pVelocity->Spd = MAX_LIFT_VEL_AUTO_H;
			if (pVelocity->Spd < 1)  pVelocity->Spd = 1;
		}
		else
		{
			if (pVelocity->Spd > MAX_LIFT_VEL_MAN_L)  pVelocity->Spd = MAX_LIFT_VEL_MAN_L;
			if (pVelocity->Spd < 1)  pVelocity->Spd = 1;
		}

		if (pVelocity->Acc > MAX_LIFT_ACC)  pVelocity->Acc = MAX_LIFT_ACC;
		if (pVelocity->Acc < 1)  pVelocity->Acc = 1;

		if (pVelocity->Dec > MAX_LIFT_DEC)	pVelocity->Dec = MAX_LIFT_DEC;
		if (pVelocity->Dec < 1)  pVelocity->Dec = 1;

		if (pVelocity->Jerk > MAX_LIFT_JERK)  pVelocity->Jerk = MAX_LIFT_JERK;
		if (pVelocity->Jerk < MIN_LIFT_JERK)  pVelocity->Jerk = MIN_LIFT_JERK;
		break;

	case LIFT_VEL_LIFT_AUTO_FORKOUT:
	case LIFT_VEL_LIFT_MAN_FORKOUT:
	case LIFT_VEL_ORIGIN:
	case LIFT_VEL_LIFT_STICKY:
		if (pVelocity->Spd > MAX_LIFT_VEL_MAN_M)  pVelocity->Spd = MAX_LIFT_VEL_MAN_M;
		if (pVelocity->Spd < 1)  pVelocity->Spd = 1;

		if (pVelocity->Acc > MAX_LIFT_ACC)  pVelocity->Acc = MAX_LIFT_ACC;
		if (pVelocity->Acc < 1)  pVelocity->Acc = 1;

		if (pVelocity->Dec > MAX_LIFT_DEC)	pVelocity->Dec = MAX_LIFT_DEC;
		if (pVelocity->Dec < 1)  pVelocity->Dec = 1;

		if (pVelocity->Jerk > MAX_LIFT_JERK)  pVelocity->Jerk = MAX_LIFT_JERK;
		if (pVelocity->Jerk < MIN_LIFT_JERK)  pVelocity->Jerk = MIN_LIFT_JERK;
		break;

	case LIFT_VEL_CREEP:
		if (pVelocity->Spd > MAX_LIFT_VEL_MAN_M)  pVelocity->Spd = MAX_LIFT_VEL_MAN_M;
		if (pVelocity->Spd < 1)  pVelocity->Spd = 1;

		if (pVelocity->Dec > MAX_LIFT_DEC)	pVelocity->Dec = MAX_LIFT_DEC;
		if (pVelocity->Dec < 1)  pVelocity->Dec = 1;

		if (pVelocity->Jerk > MAX_LIFT_JERK)  pVelocity->Jerk = MAX_LIFT_JERK;
		if (pVelocity->Jerk < MIN_LIFT_JERK)  pVelocity->Jerk = MIN_LIFT_JERK;
		break;

	case LIFT_VEL_EMG:
		if (pVelocity->Dec > MAX_LIFT_DEC)	pVelocity->Dec = MAX_LIFT_DEC;
		if (pVelocity->Dec < 1)  pVelocity->Dec = 1;

		if (pVelocity->Jerk > MAX_LIFT_JERK)  pVelocity->Jerk = MAX_LIFT_JERK;
		if (pVelocity->Jerk < MIN_LIFT_JERK)  pVelocity->Jerk = MIN_LIFT_JERK;
		break;
	}
}

/**
  * @brief Write Lift velocity
  * @param nType
  * @param pVelocity
  * @retval None
  */
void Set_Lift_Velocity_1(INT08U nType, UnitVelocitySTR* pSrcVel, UnitVelocitySTR* pWrVel)
{
	switch (nType)
	{
	case LIFT_VEL_AUTO_H:
	case LIFT_VEL_AUTO_M:
	case LIFT_VEL_AUTO_L:
		if (pSrcVel->Spd > MAX_LIFT_VEL_AUTO_H)  pSrcVel->Spd = MAX_LIFT_VEL_AUTO_H;
		if (pSrcVel->Spd < 1)  pSrcVel->Spd = 1;

		if (pSrcVel->Acc > MAX_LIFT_ACC)  pSrcVel->Acc = MAX_LIFT_ACC;
		if (pSrcVel->Acc < 1)  pSrcVel->Acc = 1;

		if (pSrcVel->Dec > MAX_LIFT_DEC)	pSrcVel->Dec = MAX_LIFT_DEC;
		if (pSrcVel->Dec < 1)  pSrcVel->Dec = 1;

		if (pSrcVel->Jerk > MAX_LIFT_JERK)  pSrcVel->Jerk = MAX_LIFT_JERK;
		if (pSrcVel->Jerk < MIN_LIFT_JERK)  pSrcVel->Jerk = MIN_LIFT_JERK;
		break;

	case LIFT_VEL_AUTO_DEC_1:
	case LIFT_VEL_AUTO_DEC_2:
		if (pSrcVel->Spd > MAX_LIFT_VEL_AUTO_H)  pSrcVel->Spd = MAX_LIFT_VEL_AUTO_H;
		if (pSrcVel->Spd < 1)  pSrcVel->Spd = 1;
		break;

	case LIFT_VEL_MAN_M:
	case LIFT_VEL_MAN_L:
		if (pSrcVel->Spd > MAX_LIFT_VEL_MAN_M)  pSrcVel->Spd = MAX_LIFT_VEL_MAN_M;
		if (pSrcVel->Spd < 1)  pSrcVel->Spd = 1;

		if (pSrcVel->Acc > MAX_LIFT_ACC)  pSrcVel->Acc = MAX_LIFT_ACC;
		if (pSrcVel->Acc < 1)  pSrcVel->Acc = 1;

		if (pSrcVel->Dec > MAX_LIFT_DEC)	pSrcVel->Dec = MAX_LIFT_DEC;
		if (pSrcVel->Dec < 1)  pSrcVel->Dec = 1;

		if (pSrcVel->Jerk > MAX_LIFT_JERK)  pSrcVel->Jerk = MAX_LIFT_JERK;
		if (pSrcVel->Jerk < MIN_LIFT_JERK)  pSrcVel->Jerk = MIN_LIFT_JERK;
		break;

	case LIFT_VEL_FORCE:
		if (m_pgmEnv.Trial_Run_Mode)
		{
			if (pSrcVel->Spd > MAX_LIFT_VEL_AUTO_H)  pSrcVel->Spd = MAX_LIFT_VEL_AUTO_H;
			if (pSrcVel->Spd < 1)  pSrcVel->Spd = 1;
		}
		else
		{
			if (pSrcVel->Spd > MAX_LIFT_VEL_MAN_M)  pSrcVel->Spd = MAX_LIFT_VEL_MAN_M;
			if (pSrcVel->Spd < 1)  pSrcVel->Spd = 1;
		}

		if (pSrcVel->Acc > MAX_LIFT_ACC)  pSrcVel->Acc = MAX_LIFT_ACC;
		if (pSrcVel->Acc < 1)  pSrcVel->Acc = 1;

		if (pSrcVel->Dec > MAX_LIFT_DEC)	pSrcVel->Dec = MAX_LIFT_DEC;
		if (pSrcVel->Dec < 1)  pSrcVel->Dec = 1;

		if (pSrcVel->Jerk > MAX_LIFT_JERK)  pSrcVel->Jerk = MAX_LIFT_JERK;
		if (pSrcVel->Jerk < MIN_LIFT_JERK)  pSrcVel->Jerk = MIN_LIFT_JERK;
		break;

	case LIFT_VEL_LIFT_AUTO_FORKOUT:
	case LIFT_VEL_LIFT_MAN_FORKOUT:
	case LIFT_VEL_ORIGIN:
		if (pSrcVel->Spd > MAX_LIFT_VEL_MAN_M)  pSrcVel->Spd = MAX_LIFT_VEL_MAN_M;
		if (pSrcVel->Spd < 1)  pSrcVel->Spd = 1;

		if (pSrcVel->Acc > MAX_LIFT_ACC)  pSrcVel->Acc = MAX_LIFT_ACC;
		if (pSrcVel->Acc < 1)  pSrcVel->Acc = 1;

		if (pSrcVel->Dec > MAX_LIFT_DEC)	pSrcVel->Dec = MAX_LIFT_DEC;
		if (pSrcVel->Dec < 1)  pSrcVel->Dec = 1;

		if (pSrcVel->Jerk > MAX_LIFT_JERK)  pSrcVel->Jerk = MAX_LIFT_JERK;
		if (pSrcVel->Jerk < MIN_LIFT_JERK)  pSrcVel->Jerk = MIN_LIFT_JERK;
		break;

	case LIFT_VEL_CREEP:
		if (pSrcVel->Spd > MAX_LIFT_VEL_MAN_M)  pSrcVel->Spd = MAX_LIFT_VEL_MAN_M;
		if (pSrcVel->Spd < 1)  pSrcVel->Spd = 1;

		if (pSrcVel->Dec > MAX_LIFT_DEC)	pSrcVel->Dec = MAX_LIFT_DEC;
		if (pSrcVel->Dec < 1)  pSrcVel->Dec = 1;

		if (pSrcVel->Jerk > MAX_LIFT_JERK)  pSrcVel->Jerk = MAX_LIFT_JERK;
		if (pSrcVel->Jerk < MIN_LIFT_JERK)  pSrcVel->Jerk = MIN_LIFT_JERK;
		break;


	case LIFT_VEL_EMG:
		if (pSrcVel->Dec > MAX_LIFT_DEC)	pSrcVel->Dec = MAX_LIFT_DEC;
		if (pSrcVel->Dec < 1)  pSrcVel->Dec = 1;

		if (pSrcVel->Jerk > MAX_LIFT_JERK)  pSrcVel->Jerk = MAX_LIFT_JERK;
		if (pSrcVel->Jerk < MIN_LIFT_JERK)  pSrcVel->Jerk = MIN_LIFT_JERK;
		break;
	}

	memcpy((INT08U*)pWrVel, (INT08U*)pSrcVel, sizeof(UnitVelocitySTR));
}


/**
  * @brief
  * @param
  * @retval None
  */
void Set_Lift_InPostion_Tolerance(ParamLiftDriveSTR* pSetting)
{
	if (pSetting->InPos_Tolerance < MIN_LIFT_IN_POS)
		pSetting->InPos_Tolerance = MIN_LIFT_IN_POS;

	if (pSetting->InPos_Tolerance > MAX_LIFT_IN_POS)
		pSetting->InPos_Tolerance = MAX_LIFT_IN_POS;
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Lift_InPostion_Tolerance_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf)
{
	if (pSetting->InPos_Tolerance < MIN_LIFT_IN_POS)
		pSetting->InPos_Tolerance = MIN_LIFT_IN_POS;

	if (pSetting->InPos_Tolerance > MAX_LIFT_IN_POS)
		pSetting->InPos_Tolerance = MAX_LIFT_IN_POS;

	pWrBuf->InPos_Tolerance = pSetting->InPos_Tolerance;
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Lift_InPostion_Hysteresis(ParamLiftDriveSTR* pSetting)
{
	if (pSetting->InPos_Hysteresis < MIN_LIFT_HYSTERESIS)
		pSetting->InPos_Hysteresis = MIN_LIFT_HYSTERESIS;

	if (pSetting->InPos_Hysteresis > MAX_LIFT_HYSTERESIS)
		pSetting->InPos_Hysteresis = MAX_LIFT_HYSTERESIS;
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Lift_InPostion_Hysteresis_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf)
{
	if (pSetting->InPos_Hysteresis < MIN_LIFT_HYSTERESIS)
		pSetting->InPos_Hysteresis = MIN_LIFT_HYSTERESIS;

	if (pSetting->InPos_Hysteresis > MAX_LIFT_HYSTERESIS)
		pSetting->InPos_Hysteresis = MAX_LIFT_HYSTERESIS;

	pWrBuf->InPos_Hysteresis = pSetting->InPos_Hysteresis;
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Lift_Manual_Drive(ParamLiftDriveSTR* pSetting)
{
	if (pSetting->ManualDrive.Torque_Alarm < MIN_LIFT_OVERTORQUE)
		pSetting->ManualDrive.Torque_Alarm = MIN_LIFT_OVERTORQUE;	// 10.0%

	if (pSetting->ManualDrive.Torque_Alarm > MAX_LIFT_OVERTORQUE)
		pSetting->ManualDrive.Torque_Alarm = MAX_LIFT_OVERTORQUE;	// 200.0%

	if (pSetting->ManualDrive.StartPos >= pSetting->ManualDrive.EndPos)
	{
		pSetting->ManualDrive.StartPos = 0;
		pSetting->ManualDrive.EndPos = 0;
	}
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Lift_Manual_Drive_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf)
{
	if (pSetting->ManualDrive.Torque_Alarm < MIN_LIFT_OVERTORQUE)
		pSetting->ManualDrive.Torque_Alarm = MIN_LIFT_OVERTORQUE;	// 10.0%

	if (pSetting->ManualDrive.Torque_Alarm > MAX_LIFT_OVERTORQUE)
		pSetting->ManualDrive.Torque_Alarm = MAX_LIFT_OVERTORQUE;	// 200.0%

	pWrBuf->ManualDrive.Torque_Alarm = pSetting->ManualDrive.Torque_Alarm;

	if (pSetting->ManualDrive.StartPos < pSetting->ManualDrive.EndPos)
	{
		pWrBuf->ManualDrive.StartPos = pSetting->ManualDrive.StartPos;
		pWrBuf->ManualDrive.EndPos = pSetting->ManualDrive.EndPos;
	}
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Lift_BrakeOn_DelayTime(ParamLiftDriveSTR* pSetting)
{
	//if (pSetting->BrakeOnDelayTime < 1)			pSetting->BrakeOnDelayTime = 1;
	if (pSetting->BrakeOnDelayTime > 60000)		pSetting->BrakeOnDelayTime = 60000;		// 600.00s
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Lift_BrakeOn_DelayTime_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf)
{
	//if (pSetting->BrakeOnDelayTime < 1)			pSetting->BrakeOnDelayTime = 1;
	if (pSetting->BrakeOnDelayTime > 60000)		pSetting->BrakeOnDelayTime = 60000;		// 600.00s

	pWrBuf->BrakeOnDelayTime = pSetting->BrakeOnDelayTime;
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Lift_Origin_Position(ParamLiftDriveSTR* pSetting)
{

}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Lift_Origin_Position_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf)
{
	pWrBuf->Origin_Pos = pSetting->Origin_Pos;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Lift_Home_Position(ParamLiftDriveSTR* pSetting)
{
	INT08U nSaveFlag = 1;
	INT32S nTmpPostion = 0;

	/*
	if (pSetting->Home_Drv_Vel <= 6)
	{
		nSaveFlag = 1;
	}
	*/

	if (pSetting->Home_Spd_Mode > DRIVE_VELOCITY_ORIGIN)
	{
		pSetting->Home_Spd_Mode = m_ExtSEnv2.LiftDrive.Home_Spd_Mode;
	}

	if (pSetting->Home_Pos == 0)
	{
		if (Check_CellEnv_Config())
		{
			nTmpPostion = m_ExtSEnv0.CellConfig_Left.LvPos[0];
		}

		if (Check_StationEnv_Config())
		{
			if (nTmpPostion > m_ExtSEnv1.StationEnv.StationSet[0].InPosition.LiftPos)
			{
				nTmpPostion = m_ExtSEnv1.StationEnv.StationSet[0].InPosition.LiftPos;
			}
		}
	}
	else
	{
		//수동운전 시작~끝위치 이내인지 확인필요.
		if (pSetting->ManualDrive.StartPos)
		{
			if (pSetting->Home_Pos < pSetting->ManualDrive.StartPos)
			{
				pSetting->Home_Pos = pSetting->ManualDrive.StartPos;
			}
		}
		else
		{
			//pSetting->ManualDrive.StartPos == 0
			if (m_ExtSEnv2.LiftDrive.Home_Pos)
			{
				pSetting->Home_Pos = m_ExtSEnv2.LiftDrive.Home_Pos;
			}
		}

		if (pSetting->ManualDrive.EndPos)
		{
			if (pSetting->Home_Pos > pSetting->ManualDrive.EndPos)
			{
				pSetting->Home_Pos = pSetting->ManualDrive.EndPos;
			}
		}
		else
		{
			//pSetting->ManualDrive.EndPos == 0
			if (m_ExtSEnv2.LiftDrive.Home_Pos)
			{
				pSetting->Home_Pos = m_ExtSEnv2.LiftDrive.Home_Pos;
			}
		}
	}

	return nSaveFlag;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Lift_Home_Position_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf)
{
	INT08U nSaveFlag = 1;
	INT32S nTmpPostion = 0;

	/*
	if (pSetting->Home_Drv_Vel <= 6)
	{
		nSaveFlag = 1;
	}
	*/

	if (pSetting->Home_Spd_Mode > DRIVE_VELOCITY_ORIGIN)
	{
		pSetting->Home_Spd_Mode = m_ExtSEnv2.LiftDrive.Home_Spd_Mode;
	}

	if (pSetting->Home_Pos == 0)
	{
		if (Check_CellEnv_Config())
		{
			nTmpPostion = m_ExtSEnv0.CellConfig_Left.LvPos[0];
		}

		if (Check_StationEnv_Config())
		{
			if (nTmpPostion > m_ExtSEnv1.StationEnv.StationSet[0].InPosition.LiftPos)
			{
				nTmpPostion = m_ExtSEnv1.StationEnv.StationSet[0].InPosition.LiftPos;
			}
		}
	}
	else
	{
		//수동운전 시작~끝위치 이내인지 확인필요.
		if (pSetting->ManualDrive.StartPos)
		{
			if (pSetting->Home_Pos < pSetting->ManualDrive.StartPos)
			{
				pSetting->Home_Pos = pSetting->ManualDrive.StartPos;
			}
		}
		else
		{
			//pSetting->ManualDrive.StartPos == 0
			if (m_ExtSEnv2.LiftDrive.Home_Pos)
			{
				pSetting->Home_Pos = m_ExtSEnv2.LiftDrive.Home_Pos;
			}
		}

		if (pSetting->ManualDrive.EndPos)
		{
			if (pSetting->Home_Pos > pSetting->ManualDrive.EndPos)
			{
				pSetting->Home_Pos = pSetting->ManualDrive.EndPos;
			}
		}
		else
		{
			//pSetting->ManualDrive.EndPos == 0
			if (m_ExtSEnv2.LiftDrive.Home_Pos)
			{
				pSetting->Home_Pos = m_ExtSEnv2.LiftDrive.Home_Pos;
			}
		}
	}

	pWrBuf->Home_Spd_Mode = pSetting->Home_Spd_Mode;
	pWrBuf->Home_Pos = pSetting->Home_Pos;

	return nSaveFlag;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Lift_Maintanance_Position(ParamLiftDriveSTR* pSetting)
{
	INT08U nSaveFlag = 1;
	//INT32S nTmpPostion = 0;

	/*
	if (pSetting->Maintanance_Spd_Mode <= 6)
	{
		nSaveFlag = 1;
	}
	*/

	if (pSetting->Maintenance_Spd_Mode > DRIVE_VELOCITY_ORIGIN)
	{
		//pSetting->Maintanance_Pos = 6;
		pSetting->Maintenance_Spd_Mode = m_ExtSEnv2.LiftDrive.Maintenance_Spd_Mode;
	}

	if (pSetting->Maintenance_Pos == 0)
	{
		pSetting->Maintenance_Pos = m_ExtSEnv2.LiftDrive.Home_Pos;
	}
	else
	{
		//수동운전 시작~끝위치 이내인지 확인필요.
		if (m_ExtSEnv2.LiftDrive.ManualDrive.StartPos)
		{
			if (pSetting->Maintenance_Pos < m_ExtSEnv2.LiftDrive.ManualDrive.StartPos)
			{
				pSetting->Maintenance_Pos = m_ExtSEnv2.LiftDrive.ManualDrive.StartPos;
			}
		}
		else
		{
			if (m_ExtSEnv2.LiftDrive.Maintenance_Pos)
			{
				pSetting->Maintenance_Pos = m_ExtSEnv2.LiftDrive.Maintenance_Pos;
			}
		}

		if (m_ExtSEnv2.LiftDrive.ManualDrive.EndPos)
		{
			if (pSetting->Maintenance_Pos > m_ExtSEnv2.LiftDrive.ManualDrive.EndPos)
			{
				pSetting->Maintenance_Pos = m_ExtSEnv2.LiftDrive.ManualDrive.EndPos;
			}
		}
		else
		{
			if (m_ExtSEnv2.LiftDrive.Maintenance_Pos)
			{
				pSetting->Maintenance_Pos = m_ExtSEnv2.LiftDrive.Maintenance_Pos;
			}
		}
	}

	return nSaveFlag;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Lift_Maintanance_Position_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf)
{
	INT08U nSaveFlag = 1;
	//INT32S nTmpPostion = 0;

	/*
	if (pSetting->Maintanance_Spd_Mode <= 6)
	{
		nSaveFlag = 1;
	}
	*/

	if (pSetting->Maintenance_Spd_Mode > DRIVE_VELOCITY_ORIGIN)
	{
		pSetting->Maintenance_Spd_Mode = m_ExtSEnv2.LiftDrive.Maintenance_Spd_Mode;
	}

	if (pSetting->Maintenance_Pos == 0)
	{
		pSetting->Maintenance_Pos = m_ExtSEnv2.LiftDrive.Home_Pos;
	}
	else
	{
		//수동운전 시작~끝위치 이내인지 확인필요.
		if (m_ExtSEnv2.LiftDrive.ManualDrive.StartPos)
		{
			if (pSetting->Maintenance_Pos < m_ExtSEnv2.LiftDrive.ManualDrive.StartPos)
			{
				pSetting->Maintenance_Pos = m_ExtSEnv2.LiftDrive.ManualDrive.StartPos;
			}
		}
		else
		{
			if (m_ExtSEnv2.LiftDrive.Maintenance_Pos)
			{
				pSetting->Maintenance_Pos = m_ExtSEnv2.LiftDrive.Maintenance_Pos;
			}
		}

		if (m_ExtSEnv2.LiftDrive.ManualDrive.EndPos)
		{
			if (pSetting->Maintenance_Pos > m_ExtSEnv2.LiftDrive.ManualDrive.EndPos)
			{
				pSetting->Maintenance_Pos = m_ExtSEnv2.LiftDrive.ManualDrive.EndPos;
			}
		}
		else
		{
			if (m_ExtSEnv2.LiftDrive.Maintenance_Pos)
			{
				pSetting->Maintenance_Pos = m_ExtSEnv2.LiftDrive.Maintenance_Pos;
			}
		}
	}

	pWrBuf->Maintenance_Spd_Mode = pSetting->Maintenance_Spd_Mode;
	pWrBuf->Maintenance_Pos = pSetting->Maintenance_Pos;

	return nSaveFlag;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Lift_DecelationRange_Mode(ParamLiftDriveSTR* pSetting)
{
	INT08U nSaveFlag = 1;

	/*
	if (pSetting->DecelRange1_Mode <= 4)
	{
		nSaveFlag = 1;
	}

	if (pSetting->DecelRange2_Mode <= 4)
	{
		nSaveFlag = 1;
	}
	*/

	if (pSetting->DecelRange1_Mode > DECEL_VELOCITY2_OVERSPEED)
	{
		pSetting->DecelRange1_Mode = m_ExtSEnv2.LiftDrive.DecelRange1_Mode;
	}

	if (pSetting->DecelRange2_Mode > DECEL_VELOCITY2_OVERSPEED)
	{
		pSetting->DecelRange2_Mode = m_ExtSEnv2.LiftDrive.DecelRange2_Mode;
	}

	return nSaveFlag;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Lift_DecelationRange_Mode_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf)
{
	INT08U nSaveFlag = 1;

	if (pSetting->DecelRange1_Mode > DECEL_VELOCITY2_OVERSPEED)
	{
		pSetting->DecelRange1_Mode = m_ExtSEnv2.LiftDrive.DecelRange1_Mode;
	}

	if (pSetting->DecelRange2_Mode > DECEL_VELOCITY2_OVERSPEED)
	{
		pSetting->DecelRange2_Mode = m_ExtSEnv2.LiftDrive.DecelRange2_Mode;
	}

	pWrBuf->DecelRange1_Mode = pSetting->DecelRange1_Mode;
	pWrBuf->DecelRange2_Mode = pSetting->DecelRange2_Mode;

	return nSaveFlag;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Lift_SoftLimit_Error(ParamLiftDriveSTR* pSetting)
{
	INT08U nSaveFlag = 1;

	/*
	if (pSetting->SoftLimitErr.CheckFlag <= 3)
	{
		nSaveFlag = 1;
	}
	*/
	if (pSetting->SoftLimitErr.CheckFlag > SOFT_ERROR_MODE_3)
	{
		//nSaveFlag = 1;
		pSetting->SoftLimitErr.CheckFlag = m_ExtSEnv2.LiftDrive.SoftLimitErr.CheckFlag;
	}

	if (pSetting->SoftLimitErr.HomePos == 0)
	{
		pSetting->SoftLimitErr.HomePos = m_ExtSEnv2.LiftDrive.ManualDrive.StartPos;
	}

	if (pSetting->SoftLimitErr.EndPos == 0)
	{
		pSetting->SoftLimitErr.EndPos = m_ExtSEnv2.LiftDrive.ManualDrive.EndPos;
	}

	return nSaveFlag;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Lift_SoftLimit_Error_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf)
{
	INT08U nSaveFlag = 1;

	/*
	if (pSetting->SoftLimitErr.CheckFlag <= 3)
	{
		nSaveFlag = 1;
	}
	*/
	if (pSetting->SoftLimitErr.CheckFlag > SOFT_ERROR_MODE_3)
	{
		//nSaveFlag = 1;
		pSetting->SoftLimitErr.CheckFlag = m_ExtSEnv2.LiftDrive.SoftLimitErr.CheckFlag;
	}

	if (pSetting->SoftLimitErr.HomePos == 0)
	{
		pSetting->SoftLimitErr.HomePos = m_ExtSEnv2.LiftDrive.ManualDrive.StartPos;
	}

	if (pSetting->SoftLimitErr.EndPos == 0)
	{
		pSetting->SoftLimitErr.EndPos = m_ExtSEnv2.LiftDrive.ManualDrive.EndPos;
	}

	memcpy((INT08U*)&pWrBuf->SoftLimitErr, (INT08U*)&pSetting->SoftLimitErr, sizeof(SoftLimitErrorSTR));



	return nSaveFlag;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Lift_SoftDecelation_Error(ParamLiftDriveSTR* pSetting)
{
	INT08U nSaveFlag = 1;

	/*
	if (pSetting->SoftDecelErr.CheckFlag < 2)
	{
		nSaveFlag = 1;
	}
	*/
	if (pSetting->SoftDecelErr.CheckFlag > 2)
	{
		pSetting->SoftDecelErr.CheckFlag = m_ExtSEnv2.LiftDrive.SoftDecelErr.CheckFlag;
	}

	if (pSetting->SoftDecelErr.ErrorOffset > 1000)
	{
		pSetting->SoftDecelErr.ErrorOffset = 1000;
	}

	return nSaveFlag;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Lift_SoftDecelation_Error_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf)
{
	INT08U nSaveFlag = 1;

	if (pSetting->SoftDecelErr.CheckFlag > 2)
	{
		pSetting->SoftDecelErr.CheckFlag = m_ExtSEnv2.LiftDrive.SoftDecelErr.CheckFlag;
	}

	if (pSetting->SoftDecelErr.ErrorOffset > 1000)
	{
		pSetting->SoftDecelErr.ErrorOffset = 1000;
	}

	memcpy((INT08U*)&pWrBuf->SoftDecelErr, (INT08U*)&pSetting->SoftDecelErr, sizeof(SoftDecelErrorSTR));

	return nSaveFlag;
}


/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Lift_OriginDog_Postion_Error(ParamLiftDriveSTR* pSetting)
{
	INT08U nSaveFlag = 1;

	if (pSetting->OriginDogErr.CheckFlag > 3)
	{
		pSetting->OriginDogErr.CheckFlag = m_ExtSEnv2.LiftDrive.OriginDogErr.CheckFlag;
	}

	if (pSetting->OriginDogErr.ErrorOffset > 1000)
	{
		pSetting->OriginDogErr.ErrorOffset = 1000;
	}

	return nSaveFlag;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Lift_OriginDog_Postion_Error_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf)
{
	INT08U nSaveFlag = 1;

	if (pSetting->OriginDogErr.CheckFlag > 3)
	{
		//nSaveFlag = 1;
		pSetting->OriginDogErr.CheckFlag = m_ExtSEnv2.LiftDrive.OriginDogErr.CheckFlag;
	}

	if (pSetting->OriginDogErr.ErrorOffset > 1000)
	{
		pSetting->OriginDogErr.ErrorOffset = 1000;
	}

	pWrBuf->OriginDogErr.CheckFlag = pSetting->OriginDogErr.CheckFlag;
	pWrBuf->OriginDogErr.ErrorOffset = pSetting->OriginDogErr.ErrorOffset;
	pWrBuf->OriginDogErr.HomePos1 = pSetting->OriginDogErr.HomePos1;
	pWrBuf->OriginDogErr.EndPos1 = pSetting->OriginDogErr.EndPos1;

	return nSaveFlag;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Lift_DecelDog_Postion_Error(ParamLiftDriveSTR* pSetting)
{
	INT08U nSaveFlag = 1;

	if (pSetting->DecelDogErr.CheckFlag > 3)
	{
		pSetting->DecelDogErr.CheckFlag = m_ExtSEnv2.LiftDrive.DecelDogErr.CheckFlag;
	}

	if (pSetting->DecelDogErr.Offset > 1000)
	{
		pSetting->DecelDogErr.Offset = 1000;
	}

	return nSaveFlag;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Lift_DecelDog_Postion_Error_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf)
{
	INT08U nSaveFlag = 0;

	if (pSetting->DecelDogErr.CheckFlag > 3)
	{
		pSetting->DecelDogErr.CheckFlag = m_ExtSEnv2.LiftDrive.DecelDogErr.CheckFlag;
	}

	if (pSetting->DecelDogErr.Offset > 1000)
	{
		pSetting->DecelDogErr.Offset = 1000;
	}

	pWrBuf->DecelDogErr.CheckFlag = pSetting->DecelDogErr.CheckFlag;
	pWrBuf->DecelDogErr.Fwd1_Pos1 = pSetting->DecelDogErr.Fwd1_Pos1;
	pWrBuf->DecelDogErr.Fwd1_Pos2 = pSetting->DecelDogErr.Fwd1_Pos2;
	pWrBuf->DecelDogErr.Fwd2_Pos1 = pSetting->DecelDogErr.Fwd2_Pos1;
	pWrBuf->DecelDogErr.Rvr1_Pos1 = pSetting->DecelDogErr.Rvr1_Pos1;
	pWrBuf->DecelDogErr.Rvr1_Pos2 = pSetting->DecelDogErr.Rvr1_Pos2;
	pWrBuf->DecelDogErr.Rvr2_Pos1 = pSetting->DecelDogErr.Rvr2_Pos1;

	return nSaveFlag;
}


/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Lift_ForkOut_Jerk_Set(ParamLiftDriveSTR* pSetting)
{
	INT08U nSaveFlag = 1;

	/*
	if (pSetting->ForkOut_LiftJerkSet.Jerk_Mode <= 2)
	{
		nSaveFlag = 1;
	}
	*/
	if (pSetting->ForkOut_LiftJerkSet.Jerk_Mode > 2)
	{
		pSetting->ForkOut_LiftJerkSet.Jerk_Mode = m_ExtSEnv2.LiftDrive.ForkOut_LiftJerkSet.Jerk_Mode;
	}

	return nSaveFlag;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Lift_ForkOut_Jerk_Set_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrbuf)
{
	INT08U nSaveFlag = 1;

	/*
	if (pSetting->ForkOut_LiftJerkSet.Jerk_Mode <= 2)
	{
		nSaveFlag = 1;
	}
	*/
	if (pSetting->ForkOut_LiftJerkSet.Jerk_Mode > 2)
	{
		pSetting->ForkOut_LiftJerkSet.Jerk_Mode = m_ExtSEnv2.LiftDrive.ForkOut_LiftJerkSet.Jerk_Mode;
	}

	pWrbuf->ForkOut_LiftJerkSet.Jerk_Mode = pSetting->ForkOut_LiftJerkSet.Jerk_Mode;
	pWrbuf->ForkOut_LiftJerkSet.Normal_Jerk = pSetting->ForkOut_LiftJerkSet.Normal_Jerk;
	pWrbuf->ForkOut_LiftJerkSet.Setup_Jerk = pSetting->ForkOut_LiftJerkSet.Setup_Jerk;
	pWrbuf->ForkOut_LiftJerkSet.Turning_Jerk = pSetting->ForkOut_LiftJerkSet.Turning_Jerk;

	return nSaveFlag;
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Lift_Invertor_Param(ParamLiftDriveSTR* pSetting)
{
	if (pSetting->InvParam.RefOffset < (-999999))
	{
		pSetting->InvParam.RefOffset = (-999999);
	}

	if (pSetting->InvParam.RefOffset > (999999))
	{
		pSetting->InvParam.RefOffset = (999999);
	}

	if (pSetting->InvParam.PosGain > (10000000))		// Position gain 0.000 ~ 10000.000
	{
		pSetting->InvParam.PosGain = (10000000);
	}

	if (pSetting->InvParam.PosWindow > (200))			// Position Offset 0 ~ 200
	{
		pSetting->InvParam.PosWindow = (200);
	}
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Lift_Invertor_Param_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf)
{
	if (pSetting->InvParam.RefOffset < (-999999))
	{
		pSetting->InvParam.RefOffset = (-999999);
	}

	if (pSetting->InvParam.RefOffset > (999999))
	{
		pSetting->InvParam.RefOffset = (999999);
	}

	if (pSetting->InvParam.PosGain > (10000000))		// Position gain 0.000 ~ 10000.000
	{
		pSetting->InvParam.PosGain = (10000000);
	}

	if (pSetting->InvParam.PosWindow > (200))			// Position Offset 0 ~ 200
	{
		pSetting->InvParam.PosWindow = (200);
	}

	memcpy((INT08U*)&pWrBuf->InvParam, (INT08U*)&pSetting->InvParam, sizeof(InvertorParam));
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Lift_LevelUpOffset(ParamLiftDriveSTR* pSetting)
{
	if (pSetting->LevelUpOffset > (RACK_SET_LEVEL_UP_OFFSET_MAX))
	{
		pSetting->LevelUpOffset = RACK_SET_LEVEL_UP_OFFSET_MAX;
	}
	else if (pSetting->LevelUpOffset <= RACK_SET_LEVEL_UP_OFFSET_MIN)
	{
		pSetting->LevelUpOffset = RACK_SET_LEVEL_UP_OFFSET_MIN;
	}
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Lift_LevelUpOffset_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf)
{
	if (pSetting->LevelUpOffset > (RACK_SET_LEVEL_UP_OFFSET_MAX))
	{
		pSetting->LevelUpOffset = RACK_SET_LEVEL_UP_OFFSET_MAX;
	}
	else if (pSetting->LevelUpOffset <= RACK_SET_LEVEL_UP_OFFSET_MIN)
	{
		pSetting->LevelUpOffset = RACK_SET_LEVEL_UP_OFFSET_MIN;
	}
	
	pWrBuf->LevelUpOffset = pSetting->LevelUpOffset;
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Lift_LevelDnOffset(ParamLiftDriveSTR* pSetting)
{
	if (pSetting->LevelDnOffset > (RACK_SET_LEVEL_DN_OFFSET_MAX))
	{
		pSetting->LevelDnOffset = RACK_SET_LEVEL_DN_OFFSET_MAX;
	}
	else if (pSetting->LevelDnOffset < RACK_SET_LEVEL_DN_OFFSET_MIN)
	{
		pSetting->LevelDnOffset = RACK_SET_LEVEL_DN_OFFSET_MIN;
	}
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Lift_LevelDnOffset_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf)
{
	if (pSetting->LevelDnOffset > RACK_SET_LEVEL_DN_OFFSET_MAX)
	{
		pSetting->LevelDnOffset = RACK_SET_LEVEL_DN_OFFSET_MAX;
	}
	else if (pSetting->LevelDnOffset < RACK_SET_LEVEL_DN_OFFSET_MIN)
	{
		pSetting->LevelDnOffset = RACK_SET_LEVEL_DN_OFFSET_MIN;
	}

	pWrBuf->LevelDnOffset = pSetting->LevelDnOffset;
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Lift_Veriant_LT_Offset(ParamLiftDriveSTR* pSetting)
{
	asm volatile("NOP");
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Lift_Veriant_LT_Offset_1(ParamLiftDriveSTR* pSetting, ParamLiftDriveSTR* pWrBuf)
{
	pWrBuf->Veriant_LT_Offset = pSetting->Veriant_LT_Offset;
}

void Save_Lift_Drive_Param(ParamLiftDriveSTR* pSetting)
{
	INT16U crc = 0;

	ExtFlash_ReadData(EXT_PARAMETER_SET_ADDR_START, (INT08U*)&m_ExtSEnv2, sizeof(ExtFlashSEnv2));

	if (memcmp((INT08U*)&m_ExtSEnv2.LiftDrive, (INT08U*)pSetting, sizeof(ParamLiftDriveSTR)))
	{
		memcpy((INT08U*)m_ExtSEnv2.InitLiftDriveCode, LIFT_DRIVE_PARAM_INIT_CODE, sizeof(INT08U) * 4);
		memcpy((INT08U*)&m_ExtSEnv2.LiftDrive, (INT08U*)pSetting, sizeof(ParamLiftDriveSTR));

		m_ExtSEnv2.CRC_LiftDrive = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv2.LiftDrive, sizeof(ParamLiftDriveSTR));

		ExtFlash_WriteData(EXT_PARAMETER_SET_ADDR_START, (INT08U*)&m_ExtSEnv2, sizeof(ExtFlashSEnv2));

#if DEBUG_MSG
		printf("[DEBUG_APP] Lift Drive Parameter save to external flash. DataCRC: 0x%04x\r\n", m_ExtSEnv2.CRC_LiftDrive);
#endif
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Lift Drive Parameter same setting. Do not save in external flash.\r\n");
#endif
	}
}

/**
  * @brief
  * @param None
  * @retval None
  */
void Default_Lift_Drive_Param_Init(void)
{
	INT08U i = 0;
	INT16U crc = 0x0000;

	ParamLiftDriveSTR nInitParam;

	memset((INT08U*)&nInitParam, 0, sizeof(ParamLiftDriveSTR));

	for (i = 0; i < MAX_LIFT_VELOCITY_CNT; i++)
	{
		nInitParam.Vel[i].Spd = 1;
		nInitParam.Vel[i].Acc = MAX_LIFT_ACC;
		nInitParam.Vel[i].Dec = MAX_LIFT_DEC;
		nInitParam.Vel[i].Jerk = MIN_LIFT_JERK;
	}

	nInitParam.InPos_Tolerance = DEF_LIFT_IN_POS_OFFSET;
	nInitParam.InPos_Hysteresis = DEF_LIFT_POS_HYSTERESIS;

	nInitParam.ManualDrive.Torque_Alarm = 500;	// 50.0%
	nInitParam.ManualDrive.StartPos = 0;
	nInitParam.ManualDrive.EndPos = 0;

	nInitParam.BrakeOnDelayTime = 1000;		// 10.00s

	nInitParam.Origin_Pos = 0;

	nInitParam.Home_Spd_Mode = DRIVE_VELOCITY_AUTO_L;
	nInitParam.Home_Pos = 0;

	nInitParam.Maintenance_Spd_Mode = DRIVE_VELOCITY_AUTO_L;
	nInitParam.Maintenance_Pos = 0;

	nInitParam.DecelRange1_Mode = DECEL_MODE_NOT_USE;
	nInitParam.DecelRange2_Mode = DECEL_MODE_NOT_USE;

	nInitParam.SoftLimitErr.CheckFlag = SOFT_ERROR_MODE_NOT_USE;
	nInitParam.SoftLimitErr.HomePos = 0;
	nInitParam.SoftLimitErr.EndPos = 0;

	nInitParam.SoftDecelErr.CheckFlag = 0;
	nInitParam.SoftDecelErr.ErrorOffset = 0;
	nInitParam.SoftDecelErr.Braking_Distance_Auto_H_Decel = 0;
	nInitParam.SoftDecelErr.Braking_Distance_Auto_M_Decel = 0;
	nInitParam.SoftDecelErr.Braking_Distance_Auto_H_Emg = 0;
	nInitParam.SoftDecelErr.Braking_Distance_Auto_M_Emg = 0;

	nInitParam.OriginDogErr.CheckFlag = SOFT_ERROR_MODE_NOT_USE;
	nInitParam.OriginDogErr.ErrorOffset = 0;
	nInitParam.OriginDogErr.HomePos1 = 0;
	nInitParam.OriginDogErr.Reseved0 = 0;
	nInitParam.OriginDogErr.EndPos1 = 0;
	nInitParam.OriginDogErr.Reseved1 = 0;

	nInitParam.DecelDogErr.CheckFlag = SOFT_ERROR_MODE_NOT_USE;
	nInitParam.DecelDogErr.Offset = 0;
	nInitParam.DecelDogErr.Fwd1_Pos1 = 0;
	nInitParam.DecelDogErr.Fwd1_Pos2 = 0;
	nInitParam.DecelDogErr.Fwd2_Pos1 = 0;
	nInitParam.DecelDogErr.Reseved0 = 0;
	nInitParam.DecelDogErr.Rvr1_Pos1 = 0;
	nInitParam.DecelDogErr.Rvr1_Pos2 = 0;
	nInitParam.DecelDogErr.Rvr2_Pos1 = 0;
	nInitParam.DecelDogErr.Reseved1 = 0;

	nInitParam.ForkOut_LiftJerkSet.Jerk_Mode = 0;
	nInitParam.ForkOut_LiftJerkSet.Normal_Jerk = 0;
	nInitParam.ForkOut_LiftJerkSet.Setup_Jerk = 0;
	nInitParam.ForkOut_LiftJerkSet.Turning_Jerk = 0;

	nInitParam.InvParam.RefOffset = 1000;
	//nInitParam.InvParam.RefOffset = 71;		// 청라 TestBed 설정값
	nInitParam.InvParam.PosGain = 12416;		// KCTC SRM 기본값 12.416
	nInitParam.InvParam.PosWindow = 3;			// KCTC SRM 기본값

	nInitParam.LevelUpOffset = DEF_LT_LEVEL_UP_MM;
	nInitParam.LevelDnOffset = DEF_LT_LEVEL_DOWN_MM;
	nInitParam.Veriant_LT_Offset = 0;

	ExtFlash_ReadData(EXT_PARAMETER_SET_ADDR_START, (INT08U*)&m_ExtSEnv2, sizeof(ExtFlashSEnv2));

	memcpy((INT08U*)m_ExtSEnv2.InitLiftDriveCode, LIFT_DRIVE_PARAM_INIT_CODE, sizeof(INT08U) * 4);
	memcpy((INT08U*)&m_ExtSEnv2.LiftDrive, (INT08U*)&nInitParam, sizeof(ParamLiftDriveSTR));

	m_ExtSEnv2.CRC_LiftDrive = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv2.LiftDrive, sizeof(ParamLiftDriveSTR));

	ExtFlash_WriteData(EXT_PARAMETER_SET_ADDR_START, (INT08U*)&m_ExtSEnv2, sizeof(ExtFlashSEnv2));
}

void Lift_Drive_Param_Init()
{
	INT16U crc = 0x0000;
	INT08U nSaveFlag = 0;

	ExtFlash_ReadData(EXT_PARAMETER_SET_ADDR_START, (INT08U*)&m_ExtSEnv2, sizeof(ExtFlashSEnv2));

	if (checkFusingString((INT08U*)m_ExtSEnv2.InitLiftDriveCode, (INT08U*)LIFT_DRIVE_PARAM_INIT_CODE, 4))
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Lift Drive Parameter Empty. Initialize Default Value.\n\r");
#endif
		Default_Lift_Drive_Param_Init();

		save_error_code(ERROR1_MCU_PARAM_DATA, 11, 1);
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Checked Lift Drive Parameter.\n\r");
#endif
		// 시운전모드(셋업+강제모드) 에서는 최대설정값이 고속으로 설정될수 있음.
			// 시스템 리셋시 저속으로 재조정.
		if (m_ExtSEnv2.LiftDrive.Vel[LIFT_VEL_FORCE].Spd > MAX_LIFT_VEL_MAN_M)
		{
			m_ExtSEnv2.LiftDrive.Vel[LIFT_VEL_FORCE].Spd = MAX_LIFT_VEL_MAN_M;
			nSaveFlag = 1;
		}

		if (nSaveFlag)
		{
			m_ExtSEnv2.CRC_LiftDrive = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv2.LiftDrive, sizeof(ParamLiftDriveSTR));

			ExtFlash_WriteData(EXT_PARAMETER_SET_ADDR_START, (INT08U*)&m_ExtSEnv2, sizeof(ExtFlashSEnv2));
			ExtFlash_ReadData(EXT_PARAMETER_SET_ADDR_START, (INT08U*)&m_ExtSEnv2, sizeof(ExtFlashSEnv2));
		}

		crc = 0x0000;
		crc = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv2.LiftDrive, sizeof(ParamLiftDriveSTR));

		if (m_ExtSEnv2.CRC_LiftDrive != crc)
		{
#if DEBUG_MSG
			printf("[DEBUG_APP] Not equal CRC Lift Drive Parameter. DataCRC: 0x%04x, CalcCRC: 0x%04x\n\r",
				m_ExtSEnv2.CRC_LiftDrive, crc);
#endif
			save_error_code(ERROR1_MCU_PARAM_DATA, 11, 0);
		}
		else
		{
#if DEBUG_MSG
			printf("[DEBUG_APP] Equal CRC Lift Drive Parameter.DataCRC: 0x%04x, CalcCRC: 0x%04x\n\r",
				m_ExtSEnv2.CRC_LiftDrive, crc);
#endif

		}
	}
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Check_Available_Lift_InPostion_Tolerance()
{
	if ((m_ExtSEnv2.LiftDrive.InPos_Tolerance < MIN_LIFT_IN_POS)
		|| (m_ExtSEnv2.LiftDrive.InPos_Tolerance > MAX_LIFT_IN_POS))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Check_Available_Lift_InPostion_Hysteresis()
{
	if ((m_ExtSEnv2.LiftDrive.InPos_Hysteresis < MIN_TRAV_HYSTERESIS)
		|| (m_ExtSEnv2.LiftDrive.InPos_Hysteresis > MAX_TRAV_HYSTERESIS))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/**
  * @brief Write Fork velocity
  * @param nType
  * @param pVelocity
  * @retval None
  */
void Set_Fork_Velocity(INT08U nType, UnitVelocitySTR* pVelocity)
{
	switch (nType)
	{
	case FORK_VEL_AUTO_H:
	case FORK_VEL_AUTO_M:
	case FORK_VEL_AUTO_L:
		if (pVelocity->Spd > MAX_FORK_VEL_AUTO)  pVelocity->Spd = MAX_FORK_VEL_AUTO;
		if (pVelocity->Spd < 1)  pVelocity->Spd = 1;

		if (pVelocity->Acc > MAX_FORK_ACC)  pVelocity->Acc = MAX_FORK_ACC;
		if (pVelocity->Acc < 1)  pVelocity->Acc = 1;

		if (pVelocity->Dec > MAX_FORK_DEC)  pVelocity->Dec = MAX_FORK_DEC;
		if (pVelocity->Dec < 1)  pVelocity->Dec = 1;

		if (pVelocity->Jerk > MAX_FORK_JERK)  pVelocity->Jerk = MAX_FORK_JERK;  // Unit: ms     
		if (pVelocity->Jerk < MIN_FORK_JERK)  pVelocity->Jerk = MIN_FORK_JERK;  // Unit: ms
		break;

	case FORK_VEL_AUTO_DEC_1:
	case FORK_VEL_AUTO_DEC_2:
		if (pVelocity->Spd > MAX_FORK_VEL_AUTO)  pVelocity->Spd = MAX_FORK_VEL_AUTO;
		if (pVelocity->Spd < 1)  pVelocity->Spd = 1;
		break;

	case FORK_VEL_FORCE:
		if (m_pgmEnv.Trial_Run_Mode)
		{
			if (pVelocity->Spd > MAX_FORK_VEL_AUTO)  pVelocity->Spd = MAX_FORK_VEL_AUTO;
			if (pVelocity->Spd < 1)  pVelocity->Spd = 1;
		}
		else
		{
			if (pVelocity->Spd > MAX_FORK_VEL_MAN)  pVelocity->Spd = MAX_FORK_VEL_MAN;
			if (pVelocity->Spd < 1)  pVelocity->Spd = 1;
		}

		if (pVelocity->Acc > MAX_FORK_ACC)  pVelocity->Acc = MAX_FORK_ACC;
		if (pVelocity->Acc < 1)  pVelocity->Acc = 1;

		if (pVelocity->Dec > MAX_FORK_DEC)  pVelocity->Dec = MAX_FORK_DEC;
		if (pVelocity->Dec < 1)  pVelocity->Dec = 1;

		if (pVelocity->Jerk > MAX_FORK_JERK)  pVelocity->Jerk = MAX_FORK_JERK;  // Unit: ms     
		if (pVelocity->Jerk < MIN_FORK_JERK)  pVelocity->Jerk = MIN_FORK_JERK;  // Unit: ms
		break;

	case FORK_VEL_MAN_L:
	case FORK_VEL_MAN_M:
	case FORK_VEL_ORIGIN:
		if (pVelocity->Spd > MAX_FORK_VEL_MAN)  pVelocity->Spd = MAX_FORK_VEL_MAN;
		if (pVelocity->Spd < 1)  pVelocity->Spd = 1;

		if (pVelocity->Acc > MAX_FORK_ACC)  pVelocity->Acc = MAX_FORK_ACC;
		if (pVelocity->Acc < 1)  pVelocity->Acc = 1;

		if (pVelocity->Dec > MAX_FORK_DEC)  pVelocity->Dec = MAX_FORK_DEC;
		if (pVelocity->Dec < 1)  pVelocity->Dec = 1;

		if (pVelocity->Jerk > MAX_FORK_JERK)  pVelocity->Jerk = MAX_FORK_JERK;  // Unit: ms     
		if (pVelocity->Jerk < MIN_FORK_JERK)  pVelocity->Jerk = MIN_FORK_JERK;  // Unit: ms
		break;

	case FORK_VEL_CREEP:
		if (pVelocity->Spd > MAX_LIFT_VEL_MAN_M)  pVelocity->Spd = MAX_LIFT_VEL_MAN_M;
		if (pVelocity->Spd < 1)  pVelocity->Spd = 1;

		if (pVelocity->Dec > MAX_FORK_DEC)  pVelocity->Dec = MAX_FORK_DEC;
		if (pVelocity->Dec < 1)  pVelocity->Dec = 1;

		if (pVelocity->Jerk > MAX_FORK_JERK)  pVelocity->Jerk = MAX_FORK_JERK;  // Unit: ms     
		if (pVelocity->Jerk < MIN_FORK_JERK)  pVelocity->Jerk = MIN_FORK_JERK;  // Unit: ms
		break;

	case FORK_VEL_EMG:
		if (pVelocity->Dec > MAX_FORK_DEC)  pVelocity->Dec = MAX_FORK_DEC;
		if (pVelocity->Dec < 1)  pVelocity->Dec = 1;

		if (pVelocity->Jerk > MAX_FORK_JERK)  pVelocity->Jerk = MAX_FORK_JERK;  // Unit: ms     
		if (pVelocity->Jerk < MIN_FORK_JERK)  pVelocity->Jerk = MIN_FORK_JERK;  // Unit: ms
		// 		pVelocity->Spd = 0;
		// 		pVelocity->Acc = pVelocity->Dec;
		break;

	default:
		if (pVelocity->Spd > MAX_FORK_VEL_MAN)  pVelocity->Spd = MAX_FORK_VEL_MAN;
		if (pVelocity->Spd < 1)  pVelocity->Spd = 1;

		if (pVelocity->Acc > MAX_FORK_ACC)  pVelocity->Acc = MAX_FORK_ACC;
		if (pVelocity->Acc < 1)  pVelocity->Acc = 1;

		if (pVelocity->Dec > MAX_FORK_DEC)  pVelocity->Dec = MAX_FORK_DEC;
		if (pVelocity->Dec < 1)  pVelocity->Dec = 1;

		if (pVelocity->Jerk > MAX_FORK_JERK)  pVelocity->Jerk = MAX_FORK_JERK;  // Unit: ms     
		if (pVelocity->Jerk < MIN_FORK_JERK)  pVelocity->Jerk = MIN_FORK_JERK;  // Unit: ms
		break;
		/*
	default:
		if (pVelocity->Spd > MAX_FORK_VEL_MAN)  pVelocity->Spd = MAX_FORK_VEL_MAN;
		if (pVelocity->Spd < 1)  pVelocity->Spd = 1;
		break;
		*/
	}
}

/**
  * @brief Write Fork velocity
  * @param nType
  * @param pVelocity
  * @retval None
  */
void Set_Fork_Velocity_1(INT08U nType, UnitVelocitySTR* pVelocity, UnitVelocitySTR* pWrbuf)
{
	switch (nType)
	{
	case FORK_VEL_AUTO_H:
	case FORK_VEL_AUTO_M:
	case FORK_VEL_AUTO_L:
		if (pVelocity->Spd > MAX_FORK_VEL_AUTO)  pVelocity->Spd = MAX_FORK_VEL_AUTO;
		if (pVelocity->Spd < 1)  pVelocity->Spd = 1;

		if (pVelocity->Acc > MAX_FORK_ACC)  pVelocity->Acc = MAX_FORK_ACC;
		if (pVelocity->Acc < 1)  pVelocity->Acc = 1;

		if (pVelocity->Dec > MAX_FORK_DEC)  pVelocity->Dec = MAX_FORK_DEC;
		if (pVelocity->Dec < 1)  pVelocity->Dec = 1;

		if (pVelocity->Jerk > MAX_FORK_JERK)  pVelocity->Jerk = MAX_FORK_JERK;  // Unit: ms     
		if (pVelocity->Jerk < MIN_FORK_JERK)  pVelocity->Jerk = MIN_FORK_JERK;  // Unit: ms
		break;

	case FORK_VEL_AUTO_DEC_1:
	case FORK_VEL_AUTO_DEC_2:
		if (pVelocity->Spd > MAX_FORK_VEL_AUTO)  pVelocity->Spd = MAX_FORK_VEL_AUTO;
		if (pVelocity->Spd < 1)  pVelocity->Spd = 1;
		break;

	case FORK_VEL_MAN_L:
		if (m_pgmEnv.Trial_Run_Mode)
		{
			if (pVelocity->Spd > MAX_FORK_VEL_AUTO)  pVelocity->Spd = MAX_FORK_VEL_AUTO;
			if (pVelocity->Spd < 1)  pVelocity->Spd = 1;
		}
		else
		{
			if (pVelocity->Spd > MAX_FORK_VEL_MAN)  pVelocity->Spd = MAX_FORK_VEL_MAN;
			if (pVelocity->Spd < 1)  pVelocity->Spd = 1;
		}

		if (pVelocity->Acc > MAX_FORK_ACC)  pVelocity->Acc = MAX_FORK_ACC;
		if (pVelocity->Acc < 1)  pVelocity->Acc = 1;

		if (pVelocity->Dec > MAX_FORK_DEC)  pVelocity->Dec = MAX_FORK_DEC;
		if (pVelocity->Dec < 1)  pVelocity->Dec = 1;

		if (pVelocity->Jerk > MAX_FORK_JERK)  pVelocity->Jerk = MAX_FORK_JERK;  // Unit: ms     
		if (pVelocity->Jerk < MIN_FORK_JERK)  pVelocity->Jerk = MIN_FORK_JERK;  // Unit: ms
		break;

	case FORK_VEL_MAN_M:
	case FORK_VEL_FORCE:
	case FORK_VEL_ORIGIN:
		if (pVelocity->Spd > MAX_FORK_VEL_MAN)  pVelocity->Spd = MAX_FORK_VEL_MAN;
		if (pVelocity->Spd < 1)  pVelocity->Spd = 1;

		if (pVelocity->Acc > MAX_FORK_ACC)  pVelocity->Acc = MAX_FORK_ACC;
		if (pVelocity->Acc < 1)  pVelocity->Acc = 1;

		if (pVelocity->Dec > MAX_FORK_DEC)  pVelocity->Dec = MAX_FORK_DEC;
		if (pVelocity->Dec < 1)  pVelocity->Dec = 1;

		if (pVelocity->Jerk > MAX_FORK_JERK)  pVelocity->Jerk = MAX_FORK_JERK;  // Unit: ms     
		if (pVelocity->Jerk < MIN_FORK_JERK)  pVelocity->Jerk = MIN_FORK_JERK;  // Unit: ms
		break;

	case FORK_VEL_CREEP:
		if (pVelocity->Spd > MAX_LIFT_VEL_MAN_M)  pVelocity->Spd = MAX_LIFT_VEL_MAN_M;
		if (pVelocity->Spd < 1)  pVelocity->Spd = 1;

		if (pVelocity->Dec > MAX_FORK_DEC)  pVelocity->Dec = MAX_FORK_DEC;
		if (pVelocity->Dec < 1)  pVelocity->Dec = 1;

		if (pVelocity->Jerk > MAX_FORK_JERK)  pVelocity->Jerk = MAX_FORK_JERK;  // Unit: ms     
		if (pVelocity->Jerk < MIN_FORK_JERK)  pVelocity->Jerk = MIN_FORK_JERK;  // Unit: ms
		break;

	case FORK_VEL_EMG:
		if (pVelocity->Dec > MAX_FORK_DEC)  pVelocity->Dec = MAX_FORK_DEC;
		if (pVelocity->Dec < 1)  pVelocity->Dec = 1;

		if (pVelocity->Jerk > MAX_FORK_JERK)  pVelocity->Jerk = MAX_FORK_JERK;  // Unit: ms     
		if (pVelocity->Jerk < MIN_FORK_JERK)  pVelocity->Jerk = MIN_FORK_JERK;  // Unit: ms
		// 		pVelocity->Spd = 0;
		// 		pVelocity->Acc = pVelocity->Dec;
		break;

	default:
		if (pVelocity->Spd > MAX_FORK_VEL_MAN)  pVelocity->Spd = MAX_FORK_VEL_MAN;
		if (pVelocity->Spd < 1)  pVelocity->Spd = 1;

		if (pVelocity->Acc > MAX_FORK_ACC)  pVelocity->Acc = MAX_FORK_ACC;
		if (pVelocity->Acc < 1)  pVelocity->Acc = 1;

		if (pVelocity->Dec > MAX_FORK_DEC)  pVelocity->Dec = MAX_FORK_DEC;
		if (pVelocity->Dec < 1)  pVelocity->Dec = 1;

		if (pVelocity->Jerk > MAX_FORK_JERK)  pVelocity->Jerk = MAX_FORK_JERK;  // Unit: ms     
		if (pVelocity->Jerk < MIN_FORK_JERK)  pVelocity->Jerk = MIN_FORK_JERK;  // Unit: ms
		break;
	}

	memcpy((INT08U*)pWrbuf, (INT08U*)pVelocity, sizeof(UnitVelocitySTR));
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Fork_InPostion_Tolerance(ParamForkDriveSTR* pSetting)
{
	if (pSetting->InPos_Tolerance < MIN_FORK_IN_POS)
		pSetting->InPos_Tolerance = MIN_FORK_IN_POS;

	if (pSetting->InPos_Tolerance > MAX_FORK_IN_POS)
		pSetting->InPos_Tolerance = MAX_FORK_IN_POS;
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Fork_InPostion_Tolerance_1(ParamForkDriveSTR* pSetting, ParamForkDriveSTR* pWrBuf)
{
	if (pSetting->InPos_Tolerance < MIN_FORK_IN_POS)
		pSetting->InPos_Tolerance = MIN_FORK_IN_POS;

	if (pSetting->InPos_Tolerance > MAX_FORK_IN_POS)
		pSetting->InPos_Tolerance = MAX_FORK_IN_POS;

	pWrBuf->InPos_Tolerance = pSetting->InPos_Tolerance;
}


/**
  * @brief
  * @param
  * @retval None
  */
void Set_Fork_InPostion_Hysteresis(ParamForkDriveSTR* pSetting)
{
	if (pSetting->InPos_Hysteresis < MIN_FORK_HYSTERESIS)
		pSetting->InPos_Hysteresis = MIN_FORK_HYSTERESIS;

	if (pSetting->InPos_Hysteresis > MAX_FORK_HYSTERESIS)
		pSetting->InPos_Hysteresis = MAX_FORK_HYSTERESIS;
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Fork_InPostion_Hysteresis_1(ParamForkDriveSTR* pSetting, ParamForkDriveSTR* pWrBuf)
{
	if (pSetting->InPos_Hysteresis < MIN_FORK_HYSTERESIS)
		pSetting->InPos_Hysteresis = MIN_FORK_HYSTERESIS;

	if (pSetting->InPos_Hysteresis > MAX_FORK_HYSTERESIS)
		pSetting->InPos_Hysteresis = MAX_FORK_HYSTERESIS;

	pWrBuf->InPos_Hysteresis = pSetting->InPos_Hysteresis;
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Fork_Manual_Drive(ParamForkDriveSTR* pSetting)
{
	if (pSetting->ManualDrive.Torque_Alarm < MIN_FORK_OVERTORQUE)
		pSetting->ManualDrive.Torque_Alarm = MIN_FORK_OVERTORQUE;	// 10.0%

	if (pSetting->ManualDrive.Torque_Alarm > MAX_FORK_OVERTORQUE)
		pSetting->ManualDrive.Torque_Alarm = MAX_FORK_OVERTORQUE;	// 200.0%

	if (pSetting->ManualDrive.Creep_Offset > DEF_FORK_MANUAL_LOW_SPEED_AREA)	
		pSetting->ManualDrive.Creep_Offset = DEF_FORK_MANUAL_LOW_SPEED_AREA;	// mm

	if (pSetting->ManualDrive.LeftPos >= pSetting->ManualDrive.RightPos)
	{
		pSetting->ManualDrive.LeftPos = 0;
		pSetting->ManualDrive.RightPos = 0;
	}
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Fork_Manual_Drive_1(ParamForkDriveSTR* pSetting, ParamForkDriveSTR* pWrBuf)
{
	if (pSetting->ManualDrive.Torque_Alarm < MIN_FORK_OVERTORQUE)
		pSetting->ManualDrive.Torque_Alarm = MIN_FORK_OVERTORQUE;	// 10.0%

	if (pSetting->ManualDrive.Torque_Alarm > MAX_FORK_OVERTORQUE)
		pSetting->ManualDrive.Torque_Alarm = MAX_FORK_OVERTORQUE;	// 200.0%

	if (pSetting->ManualDrive.Creep_Offset > DEF_FORK_MANUAL_LOW_SPEED_AREA)	
		pSetting->ManualDrive.Creep_Offset = DEF_FORK_MANUAL_LOW_SPEED_AREA;	// mm

	if (pSetting->ManualDrive.LeftPos < pSetting->ManualDrive.RightPos)
	{
		pWrBuf->ManualDrive.LeftPos = pSetting->ManualDrive.LeftPos;
		pWrBuf->ManualDrive.RightPos = pSetting->ManualDrive.RightPos;
	}

	memcpy((INT08U*)&pWrBuf->ManualDrive, (INT08U*)&pSetting->ManualDrive, sizeof(ForkManualDriveSTR));
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Fork_Encoder_Setup(ParamForkDriveSTR* pSetting)
{
	INT08U nSaveFlag = 1;

	/*
	if (pSetting->EncoderSetup.Dir < 2)
	{
		nSaveFlag = 1;
	}

	if (pSetting->EncoderSetup.Input_Pulse < 3)
	{
		nSaveFlag = 1;
	}
	*/
	// 0: CW, 1: CCW
	if (pSetting->EncoderSetup.Dir > 1)
	{
		pSetting->EncoderSetup.Dir = m_ExtSEnv2.ForkDrive.EncoderSetup.Dir;
	}

	// 0 : Multiplication × 1 cycle
	// 1 : Multiplication × 2 cycle
	// 2 : Multiplication × 4 cycle
	if (pSetting->EncoderSetup.Input_Pulse > 2)
	{
		pSetting->EncoderSetup.Input_Pulse = m_ExtSEnv2.ForkDrive.EncoderSetup.Input_Pulse;
	}

	if (pSetting->EncoderSetup.Pulse_Distance > 10000000)
	{
		pSetting->EncoderSetup.Pulse_Distance = m_ExtSEnv2.ForkDrive.EncoderSetup.Pulse_Distance;
	}

	return nSaveFlag;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Fork_Encoder_Setup_1(ParamForkDriveSTR* pSetting, ParamForkDriveSTR* pWrBuf)
{
	INT08U nSaveFlag = 1;

	// 0: CW, 1: CCW
	if (pSetting->EncoderSetup.Dir > 1)
	{
		pSetting->EncoderSetup.Dir = m_ExtSEnv2.ForkDrive.EncoderSetup.Dir;
	}

	// 0 : Multiplication × 1 cycle
	// 1 : Multiplication × 2 cycle
	// 2 : Multiplication × 4 cycle
	if (pSetting->EncoderSetup.Input_Pulse > 2)
	{
		pSetting->EncoderSetup.Input_Pulse = m_ExtSEnv2.ForkDrive.EncoderSetup.Input_Pulse;
	}

	if (pSetting->EncoderSetup.Pulse_Distance > 10000000)
	{
		pSetting->EncoderSetup.Pulse_Distance = m_ExtSEnv2.ForkDrive.EncoderSetup.Pulse_Distance;
	}

	memcpy((INT08U*)&pWrBuf->EncoderSetup, (INT08U*)&pSetting->EncoderSetup, sizeof(ForkEncoderSetupSTR));

	return nSaveFlag;
}


/**
  * @brief
  * @param
  * @retval None
  */
void Set_Fork_Origin_Offset(ParamForkDriveSTR* pSetting)
{
	if (pSetting->OriginOffset_FCL > 0)
	{
		if (pSetting->OriginOffset_FCL > MAX_FORK_ORIGIN_OFFSET)
		{
			pSetting->OriginOffset_FCL = MAX_FORK_ORIGIN_OFFSET;	// mm
		}
	}
	else
	{
		if (pSetting->OriginOffset_FCL < MIN_FORK_ORIGIN_OFFSET)
		{
			pSetting->OriginOffset_FCL = MIN_FORK_ORIGIN_OFFSET;	// mm
		}
	}

	if (pSetting->OriginOffset_FCR > 0)
	{
		if (pSetting->OriginOffset_FCR > MAX_FORK_ORIGIN_OFFSET)
		{
			pSetting->OriginOffset_FCR = MAX_FORK_ORIGIN_OFFSET;	// mm
		}
	}
	else
	{
		if (pSetting->OriginOffset_FCR < MIN_FORK_ORIGIN_OFFSET)
		{
			pSetting->OriginOffset_FCR = MIN_FORK_ORIGIN_OFFSET;	// mm
		}
	}
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Fork_Origin_Offset_1(ParamForkDriveSTR* pSetting, ParamForkDriveSTR* pWrBuf)
{
	if (pSetting->OriginOffset_FCL > 0)
	{
		if (pSetting->OriginOffset_FCL > MAX_FORK_ORIGIN_OFFSET)
		{
			pSetting->OriginOffset_FCL = MAX_FORK_ORIGIN_OFFSET;	// mm
		}
	}
	else
	{
		if (pSetting->OriginOffset_FCL < MIN_FORK_ORIGIN_OFFSET)
		{
			pSetting->OriginOffset_FCL = MIN_FORK_ORIGIN_OFFSET;	// mm
		}
	}

	if (pSetting->OriginOffset_FCR > 0)
	{
		if (pSetting->OriginOffset_FCR > MAX_FORK_ORIGIN_OFFSET)
		{
			pSetting->OriginOffset_FCR = MAX_FORK_ORIGIN_OFFSET;	// mm
		}
	}
	else
	{
		if (pSetting->OriginOffset_FCR < MIN_FORK_ORIGIN_OFFSET)
		{
			pSetting->OriginOffset_FCR = MIN_FORK_ORIGIN_OFFSET;	// mm
		}
	}

	pWrBuf->OriginOffset_FCL = pSetting->OriginOffset_FCL;
	pWrBuf->OriginOffset_FCR = pSetting->OriginOffset_FCR;
	pWrBuf->OriginSensor = pSetting->OriginSensor;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Fork_Decelation_Control(ParamForkDriveSTR* pSetting)
{
	INT08U nSaveFlag = 1;
	INT08U i = 0;

	// 0: Not use, 1: Use
	if (pSetting->ForkDecelCtr.UseFlag > 1)
	{
		pSetting->ForkDecelCtr.UseFlag = m_ExtSEnv2.ForkDrive.ForkDecelCtr.UseFlag;
	}

	for (i = 0; i < MAX_FORK_DECELATION_SETUP; i++)
	{
		if ((i == NO_LOADED_MOVE_CENTER_TO_FEL) \
			|| (i == NO_LOADED_MOVE_CENTER_TO_FML) \
			|| (i == NO_LOADED_MOVE_CENTER_TO_FHL) \
			|| (i == NO_LOADED_MOVE_FEL_TO_CENTER) \
			|| (i == NO_LOADED_MOVE_FML_TO_CENTER) \
			|| (i == NO_LOADED_MOVE_FHL_TO_CENTER) \
			|| (i == LOADED_MOVE_CENTER_TO_FEL) \
			|| (i == LOADED_MOVE_CENTER_TO_FML) \
			|| (i == LOADED_MOVE_CENTER_TO_FHL) \
			|| (i == LOADED_MOVE_FEL_TO_CENTER) \
			|| (i == LOADED_MOVE_FML_TO_CENTER) \
			|| (i == LOADED_MOVE_FHL_TO_CENTER))
		{
			if (m_ExtSEnv2.ForkDrive.ManualDrive.LeftPos < 0)
			{
				if ((pSetting->ForkDecelCtr.Position[i] > 0) \
					|| (pSetting->ForkDecelCtr.Position[i] < m_ExtSEnv2.ForkDrive.ManualDrive.LeftPos))
				{
					pSetting->ForkDecelCtr.Position[i] = m_ExtSEnv2.ForkDrive.ForkDecelCtr.Position[i];
				}
			}
			else
			{
				pSetting->ForkDecelCtr.Position[i] = 0;
			}
		}
		else
		{
			if (m_ExtSEnv2.ForkDrive.ManualDrive.RightPos > 0)
			{
				if ((pSetting->ForkDecelCtr.Position[i] < 0) \
					|| (pSetting->ForkDecelCtr.Position[i] > m_ExtSEnv2.ForkDrive.ManualDrive.RightPos))
				{
					pSetting->ForkDecelCtr.Position[i] = m_ExtSEnv2.ForkDrive.ForkDecelCtr.Position[i];
				}
			}
			else
			{
				pSetting->ForkDecelCtr.Position[i] = 0;
			}
		}
	}

	return nSaveFlag;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Fork_Decelation_Control_1(ParamForkDriveSTR* pSetting, ParamForkDriveSTR* pWrBuf)
{
	INT08U nSaveFlag = 1;
	INT08U i = 0;

	// 0: Not use, 1: Use
	if (pSetting->ForkDecelCtr.UseFlag > 1)
	{
		pWrBuf->ForkDecelCtr.UseFlag = m_ExtSEnv2.ForkDrive.ForkDecelCtr.UseFlag;
	}
	else
	{
		pWrBuf->ForkDecelCtr.UseFlag = pSetting->ForkDecelCtr.UseFlag;
	}

	for (i = 0; i < MAX_FORK_DECELATION_SETUP; i++)
	{
		if ((i == NO_LOADED_MOVE_CENTER_TO_FEL) \
			|| (i == NO_LOADED_MOVE_CENTER_TO_FML) \
			|| (i == NO_LOADED_MOVE_CENTER_TO_FHL) \
			|| (i == NO_LOADED_MOVE_FEL_TO_CENTER) \
			|| (i == NO_LOADED_MOVE_FML_TO_CENTER) \
			|| (i == NO_LOADED_MOVE_FHL_TO_CENTER) \
			|| (i == LOADED_MOVE_CENTER_TO_FEL) \
			|| (i == LOADED_MOVE_CENTER_TO_FML) \
			|| (i == LOADED_MOVE_CENTER_TO_FHL) \
			|| (i == LOADED_MOVE_FEL_TO_CENTER) \
			|| (i == LOADED_MOVE_FML_TO_CENTER) \
			|| (i == LOADED_MOVE_FHL_TO_CENTER))
		{
			if (m_ExtSEnv2.ForkDrive.ManualDrive.LeftPos < 0)
			{
				if ((pSetting->ForkDecelCtr.Position[i] <= 0) \
					&& (pSetting->ForkDecelCtr.Position[i] >= m_ExtSEnv2.ForkDrive.ManualDrive.LeftPos))
				{
					pWrBuf->ForkDecelCtr.Position[i] = pSetting->ForkDecelCtr.Position[i];
				}
			}
			else
			{
				pWrBuf->ForkDecelCtr.Position[i] = 0;
			}
		}
		else
		{
			if (m_ExtSEnv2.ForkDrive.ManualDrive.RightPos > 0)
			{
				if ((pSetting->ForkDecelCtr.Position[i] >= 0) \
					&& (pSetting->ForkDecelCtr.Position[i] <= m_ExtSEnv2.ForkDrive.ManualDrive.RightPos))
				{
					pWrBuf->ForkDecelCtr.Position[i] = pSetting->ForkDecelCtr.Position[i];
				}
			}
			else
			{
				pWrBuf->ForkDecelCtr.Position[i] = 0;
			}
		}
	}

	//memcpy((INT08U*)&pWrBuf->ForkDecelCtr, (INT08U*)&pSetting->ForkDecelCtr, sizeof(AutoForkDecelCtrSetupSTR));

	return nSaveFlag;
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Fork_TwinFork_Setup(ParamForkDriveSTR* pSetting)
{

}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Fork_TwinFork_Setup_1(ParamForkDriveSTR* pSetting, ParamForkDriveSTR* pWrBuf)
{
	pWrBuf->TwinForkSetup.Between_Distance = pSetting->TwinForkSetup.Between_Distance;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Fork_Position_UseFlag(ParamForkDriveSTR* pSetting)
{
	INT08U nSaveFlag = 1;

	/*
	// 0: Not use, 1: Use
	if (pSetting->PosSensorUse.mHalf > 1)
	{
		pSetting->PosSensorUse.mHalf = m_ExtSEnv2.ForkDrive.PosSensorUse.mHalf;
	}

	if (pSetting->PosSensorUse.mMiddle > 1)
	{
		pSetting->PosSensorUse.mMiddle = m_ExtSEnv2.ForkDrive.PosSensorUse.mMiddle;
	}

	if (pSetting->PosSensorUse.mEnd > 1)
	{
		pSetting->PosSensorUse.mEnd = m_ExtSEnv2.ForkDrive.PosSensorUse.mEnd;
	}
	*/

	return nSaveFlag;
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Set_Fork_Position_UseFlag_1(ParamForkDriveSTR* pSetting, ParamForkDriveSTR* pWrBuf)
{
	INT08U nSaveFlag = 1;

	// 0: Not use, 1: Use
	/*
	if (pSetting->PosSensorUse.mHalf > 1)
	{
		pSetting->PosSensorUse.mHalf = m_ExtSEnv2.ForkDrive.PosSensorUse.mHalf;
	}

	if (pSetting->PosSensorUse.mMiddle > 1)
	{
		pSetting->PosSensorUse.mMiddle = m_ExtSEnv2.ForkDrive.PosSensorUse.mMiddle;
	}

	if (pSetting->PosSensorUse.mEnd > 1)
	{
		pSetting->PosSensorUse.mEnd = m_ExtSEnv2.ForkDrive.PosSensorUse.mEnd;
	}

	pWrBuf->PosSensorUse.mHalf = pSetting->PosSensorUse.mHalf;
	pWrBuf->PosSensorUse.mMiddle = pSetting->PosSensorUse.mMiddle;
	pWrBuf->PosSensorUse.mEnd = pSetting->PosSensorUse.mEnd;
	*/
	pWrBuf->PosSensorUse.Setting.D = pSetting->PosSensorUse.Setting.D;

	return nSaveFlag;
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Fork_Position_Depth(ParamForkDriveSTR* pSetting)
{
	if (m_ExtSEnv.Machine.mType.Fork_Type == FORK_TYPE_SINGLE_DEEP)
	{
		//if (m_ExtSEnv2.ForkDrive.ManualDrive.LeftPos > pSetting->ForkPosDepth.mFEL)
		if (pSetting->ManualDrive.LeftPos > pSetting->ForkPosDepth.mFEL)
		{
			pSetting->ForkPosDepth.mFEL = pSetting->ManualDrive.LeftPos;
		}

		//if (m_ExtSEnv2.ForkDrive.ManualDrive.RightPos < pSetting->ForkPosDepth.mFER)
		if (pSetting->ManualDrive.RightPos < pSetting->ForkPosDepth.mFER)
		{
			pSetting->ForkPosDepth.mFER = pSetting->ManualDrive.RightPos;
		}
	}
	else if (m_ExtSEnv.Machine.mType.Fork_Type == FORK_TYPE_DOUBLE_DEEP_2POS)
	{
		if (m_ExtSEnv2.ForkDrive.ManualDrive.LeftPos > pSetting->ForkPosDepth.mFEL)
		{
			pSetting->ForkPosDepth.mFEL = m_ExtSEnv2.ForkDrive.ManualDrive.LeftPos;
		}

		if (m_ExtSEnv2.ForkDrive.ManualDrive.RightPos < pSetting->ForkPosDepth.mFER)
		{
			pSetting->ForkPosDepth.mFER = m_ExtSEnv2.ForkDrive.ManualDrive.RightPos;
		}

		if (pSetting->ForkPosDepth.mFER < pSetting->ForkPosDepth.mFHR)
		{
			pSetting->ForkPosDepth.mFHR = 0;
		}

		if (pSetting->ForkPosDepth.mFEL > pSetting->ForkPosDepth.mFHL)
		{
			pSetting->ForkPosDepth.mFHL = 0;
		}
	}
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Fork_Position_Depth_1(ParamForkDriveSTR* pSetting, ParamForkDriveSTR* pWrBuf)
{
	if (m_ExtSEnv.Machine.mType.Fork_Type == FORK_TYPE_SINGLE_DEEP)
	{
		if (m_ExtSEnv2.ForkDrive.ManualDrive.LeftPos > pSetting->ForkPosDepth.mFEL)
		{
			pSetting->ForkPosDepth.mFEL = m_ExtSEnv2.ForkDrive.ManualDrive.LeftPos;
		}

		if (m_ExtSEnv2.ForkDrive.ManualDrive.RightPos < pSetting->ForkPosDepth.mFER)
		{
			pSetting->ForkPosDepth.mFER = m_ExtSEnv2.ForkDrive.ManualDrive.RightPos;
		}

		pSetting->ForkPosDepth.mFML = 0;
		pSetting->ForkPosDepth.mFMR = 0;
		pSetting->ForkPosDepth.mFHL = 0;
		pSetting->ForkPosDepth.mFHR = 0;

		memcpy((INT08U*)&pWrBuf->ForkPosDepth, (INT08U*)&pSetting->ForkPosDepth, sizeof(ForkPosDepthSTR));
	}
	else if (m_ExtSEnv.Machine.mType.Fork_Type == FORK_TYPE_DOUBLE_DEEP_2POS)
	{
		if (pSetting->ForkPosDepth.mFEL < 0)
		{
			if (m_ExtSEnv2.ForkDrive.ManualDrive.LeftPos > pSetting->ForkPosDepth.mFEL)
			{
				pSetting->ForkPosDepth.mFEL = m_ExtSEnv2.ForkDrive.ManualDrive.LeftPos;
			}

			if (pSetting->ForkPosDepth.mFEL > pSetting->ForkPosDepth.mFHL)
			{
				pSetting->ForkPosDepth.mFHL = 0;
			}
		}
		else
		{
			// 0 인 경우, 더블딥 포크인데 랙은 싱글딥
		}

		if (pSetting->ForkPosDepth.mFER > 0)
		{
			if (m_ExtSEnv2.ForkDrive.ManualDrive.RightPos < pSetting->ForkPosDepth.mFER)
			{
				pSetting->ForkPosDepth.mFER = m_ExtSEnv2.ForkDrive.ManualDrive.RightPos;
			}

			if (pSetting->ForkPosDepth.mFER < pSetting->ForkPosDepth.mFHR)
			{
				pSetting->ForkPosDepth.mFHR = 0;
			}
		}
		else
		{
			// 0 인 경우, 더블딥 포크인데 랙은 싱글딥
		}
		
		pSetting->ForkPosDepth.mFML = 0;
		pSetting->ForkPosDepth.mFMR = 0;
		
		memcpy((INT08U*)&pWrBuf->ForkPosDepth, (INT08U*)&pSetting->ForkPosDepth, sizeof(ForkPosDepthSTR));
	}
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Fork_Invertor_Param(ParamForkDriveSTR* pSetting)
{
	pSetting->InvParam.RefOffset = 0;		// Fork Ref Offset 값은 0 고정
	/*
	if (pSetting->InvParam.RefOffset < (-999999))
	{
		pSetting->InvParam.RefOffset = (-999999);
	}

	if (pSetting->InvParam.RefOffset > (999999))
	{
		pSetting->InvParam.RefOffset = (999999);
	}
	*/

	if (pSetting->InvParam.PosGain > (10000000))		// Position gain 0.000 ~ 10000.000
	{
		pSetting->InvParam.PosGain = (10000000);
	}

	if (pSetting->InvParam.PosWindow > (200))			// Position Offset 0 ~ 200
	{
		pSetting->InvParam.PosWindow = (200);
	}
}

/**
  * @brief
  * @param
  * @retval None
  */
void Set_Fork_Invertor_Param_1(ParamForkDriveSTR* pSetting, ParamForkDriveSTR* pWrBuf)
{
	if (pSetting->InvParam.RefOffset < (-999999))
	{
		pSetting->InvParam.RefOffset = (-999999);
	}

	if (pSetting->InvParam.RefOffset > (999999))
	{
		pSetting->InvParam.RefOffset = (999999);
	}

	if (pSetting->InvParam.PosGain > (10000000))		// Position gain 0.000 ~ 10000.000
	{
		pSetting->InvParam.PosGain = (10000000);
	}

	if (pSetting->InvParam.PosWindow > (200))			// Position Offset 0 ~ 200
	{
		pSetting->InvParam.PosWindow = (200);
	}

	memcpy((INT08U*)&pWrBuf->InvParam, (INT08U*)&pSetting->InvParam, sizeof(InvertorParam));
}


void Save_Fork_Drive_Param(ParamForkDriveSTR* pSetting)
{
	INT16U crc = 0;

	ExtFlash_ReadData(EXT_PARAMETER_SET_ADDR_START, (INT08U*)&m_ExtSEnv2, sizeof(ExtFlashSEnv2));

	if (memcmp((INT08U*)&m_ExtSEnv2.ForkDrive, (INT08U*)pSetting, sizeof(ParamForkDriveSTR)))
	{
		memcpy((INT08U*)m_ExtSEnv2.InitForkDriveCode, FORK_DRIVE_PARAM_INIT_CODE, sizeof(INT08U) * 4);
		memcpy((INT08U*)&m_ExtSEnv2.ForkDrive, (INT08U*)pSetting, sizeof(ParamForkDriveSTR));

		m_ExtSEnv2.CRC_ForkDrive = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv2.ForkDrive, sizeof(ParamForkDriveSTR));

		ExtFlash_WriteData(EXT_PARAMETER_SET_ADDR_START, (INT08U*)&m_ExtSEnv2, sizeof(ExtFlashSEnv2));

#if DEBUG_MSG
		printf("[DEBUG_APP] Fork Drive Parameter save to external flash. DataCRC: 0x%04x\r\n", m_ExtSEnv2.CRC_ForkDrive);
#endif
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Fork Drive Parameter same setting. Do not save in external flash.\r\n");
#endif
	}
}

/**
  * @brief
  * @param None
  * @retval None
  */
void Default_Fork_Drive_Param_Init(void)
{
	INT08U i = 0;
	INT16U crc = 0x0000;

	ParamForkDriveSTR nInitParam;

	memset((INT08U*)&nInitParam, 0, sizeof(ParamForkDriveSTR));

	for (i = 0; i < MAX_LIFT_VELOCITY_CNT; i++)
	{
		nInitParam.Vel[i].Spd = 1;
		nInitParam.Vel[i].Acc = MAX_FORK_ACC;
		nInitParam.Vel[i].Dec = MAX_FORK_DEC;
		nInitParam.Vel[i].Jerk = MIN_FORK_JERK;
	}

	nInitParam.InPos_Tolerance = DEF_FORK_IN_POS_OFFSET;
	nInitParam.InPos_Hysteresis = DEF_FORK_POS_HYSTERESIS;

	nInitParam.ManualDrive.Torque_Alarm = 500;	// 50.0%
	nInitParam.ManualDrive.LeftPos = 0;
	nInitParam.ManualDrive.RightPos = 0;
	nInitParam.ManualDrive.Creep_Offset = DEF_FORK_MANUAL_LOW_SPEED_AREA;

	nInitParam.EncoderSetup.Dir = 0;
	nInitParam.EncoderSetup.Input_Pulse = 2;
	nInitParam.EncoderSetup.Preset_Count = 50000;
	nInitParam.EncoderSetup.Pulse_Distance = 124;	// 0.124

	nInitParam.OriginOffset_FCL = DEF_FORK_ORIGIN_OFFSET;
	nInitParam.OriginOffset_FCR = DEF_FORK_ORIGIN_OFFSET;
	nInitParam.OriginSensor = FORK_ORIGIN_FCL;
	
	nInitParam.InvParam.RefOffset = 0;
	nInitParam.InvParam.PosGain = 3417;		// KCTC SRM 기본값 : 3.417
	nInitParam.InvParam.PosWindow = 5;		// KCTC SRM 기본값 : 5

	ExtFlash_ReadData(EXT_PARAMETER_SET_ADDR_START, (INT08U*)&m_ExtSEnv2, sizeof(ExtFlashSEnv2));

	memcpy((INT08U*)m_ExtSEnv2.InitForkDriveCode, FORK_DRIVE_PARAM_INIT_CODE, sizeof(INT08U) * 4);
	memcpy((INT08U*)&m_ExtSEnv2.ForkDrive, (INT08U*)&nInitParam, sizeof(ParamForkDriveSTR));

	m_ExtSEnv2.CRC_ForkDrive = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv2.ForkDrive, sizeof(ParamForkDriveSTR));

	ExtFlash_WriteData(EXT_PARAMETER_SET_ADDR_START, (INT08U*)&m_ExtSEnv2, sizeof(ExtFlashSEnv2));
}

void Fork_Drive_Param_Init()
{
	INT16U crc = 0x0000;
	INT08U nSaveFlag = 0;

	ExtFlash_ReadData(EXT_PARAMETER_SET_ADDR_START, (INT08U*)&m_ExtSEnv2, sizeof(ExtFlashSEnv2));

	if (checkFusingString((INT08U*)m_ExtSEnv2.InitForkDriveCode, (INT08U*)FORK_DRIVE_PARAM_INIT_CODE, 4))
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Fork Drive Parameter Empty. Initialize Default Value.\n\r");
#endif
		Default_Fork_Drive_Param_Init();

		save_error_code(ERROR1_MCU_PARAM_DATA, 12, 1);
	}
	else
	{
#if DEBUG_MSG
		printf("[DEBUG_APP] Checked Fork Drive Parameter.\n\r");
#endif
		// 시운전모드(셋업+강제모드) 에서는 최대설정값이 고속으로 설정될수 있음.
			// 시스템 리셋시 저속으로 재조정.
		if (m_ExtSEnv2.ForkDrive.Vel[FORK_VEL_FORCE].Spd > MAX_FORK_VEL_MAN)
		{
			m_ExtSEnv2.ForkDrive.Vel[FORK_VEL_FORCE].Spd = MAX_FORK_VEL_MAN;
			nSaveFlag = 1;
		}

		if (nSaveFlag)
		{
			m_ExtSEnv2.CRC_ForkDrive = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv2.ForkDrive, sizeof(ParamForkDriveSTR));
			ExtFlash_WriteData(EXT_PARAMETER_SET_ADDR_START, (INT08U*)&m_ExtSEnv2, sizeof(ExtFlashSEnv2));
			ExtFlash_ReadData(EXT_PARAMETER_SET_ADDR_START, (INT08U*)&m_ExtSEnv2, sizeof(ExtFlashSEnv2));
		}

		crc = 0x0000;
		crc = crcInitStrCalc(crc, (INT08U*)&m_ExtSEnv2.ForkDrive, sizeof(ParamForkDriveSTR));

		if (m_ExtSEnv2.CRC_ForkDrive != crc)
		{
#if DEBUG_MSG
			printf("[DEBUG_APP] Not equal CRC Fork Drive Parameter. DataCRC: 0x%04x, CalcCRC: 0x%04x\n\r",
				m_ExtSEnv2.CRC_ForkDrive, crc);
#endif
			save_error_code(ERROR1_MCU_PARAM_DATA, 12, 0);
		}
		else
		{
#if DEBUG_MSG
			printf("[DEBUG_APP] Equal CRC Fork Drive Parameter.DataCRC: 0x%04x, CalcCRC: 0x%04x\n\r",
				m_ExtSEnv2.CRC_ForkDrive, crc);
#endif	
		}
	}
}


/**
  * @brief
  * @param
  * @retval None
  */
INT08U Check_Available_Fork_InPostion_Tolerance()
{
	if ((m_ExtSEnv2.ForkDrive.InPos_Tolerance < MIN_FORK_IN_POS)
		|| (m_ExtSEnv2.ForkDrive.InPos_Tolerance > MAX_FORK_IN_POS))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Check_Available_Fork_InPostion_Hysteresis()
{
	if ((m_ExtSEnv2.ForkDrive.InPos_Hysteresis < MIN_FORK_HYSTERESIS)
		|| (m_ExtSEnv2.ForkDrive.InPos_Hysteresis > MAX_FORK_HYSTERESIS))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/**
  * @brief
  * @param
  * @retval None
  */
INT08U Check_Available_Fork_Origin_Offset()
{
	if ((m_ExtSEnv2.ForkDrive.OriginOffset_FCL >= MIN_FORK_ORIGIN_OFFSET)
		&& (m_ExtSEnv2.ForkDrive.OriginOffset_FCL <= MAX_FORK_ORIGIN_OFFSET))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}



