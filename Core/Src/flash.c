/**
 ******************************************************************************
 * @file      flash.c
 * @author
 * @brief     Flash read, wirte function
 *
 *
 *
 *
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */

 /* Includes */
#include "flash.h"
#include "FlashSST26.h"

/* Functions */
/**
  * @brief  Gets the sector of a given address
  * @param  Address
  * @retval The sector of a given address
  */
uint32_t GetSector(uint32_t Address)
{
	uint32_t sector = 0;

	if ((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
	{
		sector = FLASH_SECTOR_0;
	}
	else if ((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
	{
		sector = FLASH_SECTOR_1;
	}
	else if ((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
	{
		sector = FLASH_SECTOR_2;
	}
	else if ((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
	{
		sector = FLASH_SECTOR_3;
	}
	else if ((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
	{
		sector = FLASH_SECTOR_4;
	}
	else if ((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
	{
		sector = FLASH_SECTOR_5;
	}
	else if ((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
	{
		sector = FLASH_SECTOR_6;
	}
	else
	{
		sector = FLASH_SECTOR_7;
	}

	return sector;
}

HAL_StatusTypeDef FLASH_User_EraseSector(INT32U start_address, INT32U end_address)
{
	HAL_StatusTypeDef status = HAL_OK;

	FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t FirstSector = 0, NbOfSectors = 0;
	uint32_t SECTORError = 0;

	FirstSector = GetSector(start_address);
	NbOfSectors = GetSector(end_address) - FirstSector + 1;

#if DEBUG_FLASH_MSG
	printf("[FLASH] Erase FirstSector : %ld, NbOfSectors:%ld\n\r", FirstSector, NbOfSectors);
#endif

	HAL_FLASH_Unlock();

	EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
	EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
	EraseInitStruct.Sector = FirstSector;
	EraseInitStruct.NbSectors = NbOfSectors;

	//HAL_GPIO_WritePin(CPU_RUN_LED_GPIO_Port, CPU_RUN_LED_Pin, GPIO_PIN_SET);
	if (HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK)
	{
		Error_Handler();
		status = HAL_ERROR;
	}
	//HAL_GPIO_WritePin(CPU_RUN_LED_GPIO_Port, CPU_RUN_LED_Pin, GPIO_PIN_RESET);

	HAL_FLASH_Lock();

#if DEBUG_FLASH_MSG
	if (status == HAL_OK)
	{
		printf("[FLASH] Erase Success.\n\r");
	}
	else
	{
		printf("[FLASH] Erase Fail!!!\n\r");
	}
#endif

	return status;
}


INT08U FLASH_User_WriteData(INT32U addr, INT08U* buff, INT32U size)
{
	HAL_StatusTypeDef status = HAL_OK;

	INT32U addr_now = addr;
	INT32U addr_end = addr + size;
	INT32U* dataPtr = (INT32U*)buff;
	INT08U nReturn = 1;

#if DEBUG_FLASH_MSG
	//printf("[FLASH] Start Write addr_now:%lx, addr_end:%lx\n\r", addr_now, addr_end);
#endif

	HAL_FLASH_Unlock();

	while ((addr_now < addr_end))
	{
		status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr_now, *(uint32_t*)dataPtr);
		if (status != HAL_OK)
		{
			//Error_Handler();
#if DEBUG_FLASH_MSG
			printf("[FLASH] Write Error : %d, Addr_now:%lx\n\r", status, addr_now);
#endif
			break;
		}

		addr_now += 4;
		dataPtr++;
	}

	HAL_FLASH_Lock();

	if (status != HAL_OK)
	{
		nReturn = 0;
	}
	else
	{
		addr_now = addr;
		dataPtr = (INT32U*)buff;
		while (addr_now < addr_end)
		{
			if ((*(__IO uint32_t*)addr_now) != *(uint32_t*)dataPtr)
			{
#if DEBUG_FLASH_MSG
				printf("[FLASH] Copy Error Addr_now:%lx, Data:%lx\n\r", addr_now, *(uint32_t*)dataPtr);
#endif
				nReturn = 0;
				break;
			}

			addr_now += 4;
			dataPtr++;
		}
	}

	if (nReturn)
	{
#if DEBUG_FLASH_MSG
		printf("[FLASH] Write Success. addr_now:%lx, addr_end:%lx\n\r", addr_now, addr_end);
#endif
	}

	return nReturn;
}


INT08U FLASH_User_WriteData_1(INT32U Flash_Addr, INT32U buf_Addr, INT32U Total_Size)
{
	HAL_StatusTypeDef status = HAL_OK;

	INT32U Flash_addr_now = Flash_Addr;
	INT32U Flash_addr_end = Flash_Addr + Total_Size;

	INT32U SFlash_addr_now = buf_Addr;
	INT32U SFlash_addr_end = buf_Addr + Total_Size;

	INT08U ReadBuf[SIZE_PAGE] = { 0, };
	INT32U nProcessSize = 0;
	INT32U nReadSize = 0;

	INT32U nWrite_Now = 0;
	INT32U nData = 0;

	INT08U nReturn = 1;

#if DEBUG_FLASH_MSG
	printf("[FLASH] Start Write. addr_now:%lx, addr_end:%lx\n\r", Flash_addr_now, Flash_addr_end);
#endif

	HAL_FLASH_Unlock();

	while ((Flash_addr_now < Flash_addr_end))
	{
		nProcessSize = SFlash_addr_now + SIZE_PAGE;
		if (nProcessSize > SFlash_addr_end)
		{
			nReadSize = SFlash_addr_end - SFlash_addr_now;
		}
		else
		{
			nReadSize = SIZE_PAGE;
		}

		memset((INT08U*)ReadBuf, 0, sizeof(INT08U) * SIZE_PAGE);
		sst26_read(SFlash_addr_now, nReadSize, ReadBuf);
		nWrite_Now = 0;

		while (nWrite_Now < nReadSize)
		{
			memcpy((INT08U*)&nData, (INT08U*)&ReadBuf[nWrite_Now], sizeof(INT08U) * 4);
			status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Flash_addr_now, nData);
			if (status != HAL_OK)
			{
				//Error_Handler();
#if DEBUG_FLASH_MSG
				printf("[FLASH] Write Error : %d, Addr_now:%lx\n\r", status, Flash_addr_now);
#endif
				break;
			}
			nWrite_Now += 4;
			Flash_addr_now += 4;
		}

		SFlash_addr_now += nReadSize;
	}

	HAL_FLASH_Lock();

	if (status != HAL_OK)
	{
		nReturn = 0;
	}
	else
	{
		Flash_addr_now = Flash_Addr;
		SFlash_addr_now = buf_Addr;

		while (Flash_addr_now < Flash_addr_end)
		{
			nProcessSize = SFlash_addr_now + SIZE_PAGE;
			if (nProcessSize > SFlash_addr_end)
			{
				nReadSize = SFlash_addr_end - SFlash_addr_now;
			}
			else
			{
				nReadSize = SIZE_PAGE;
			}

			memset((INT08U*)ReadBuf, 0, sizeof(INT08U) * SIZE_PAGE);
			sst26_read(SFlash_addr_now, nReadSize, ReadBuf);
			nWrite_Now = 0;

			while (nWrite_Now < nReadSize)
			{
				memcpy((INT08U*)&nData, (INT08U*)&ReadBuf[nWrite_Now], sizeof(INT08U) * 4);
				if ((*(__IO uint32_t*)Flash_addr_now) != (uint32_t)nData)
				{
#if DEBUG_FLASH_MSG
					printf("[FLASH] Copy Error Addr_now: 0x%08lx, Data:0x%08lx, nWrite_Now: %ld\n\r", \
						Flash_addr_now, nData, nWrite_Now);
#endif
					nReturn = 0;
					break;
				}


				nWrite_Now += 4;
				Flash_addr_now += 4;
			}

			SFlash_addr_now += nReadSize;
		}
	}

	if (nReturn)
	{
#if DEBUG_FLASH_MSG
		printf("[FLASH] Write Success. addr_now:%lx, addr_end:%lx\n\r", Flash_addr_now, Flash_addr_end);
#endif
	}

	return nReturn;
}
