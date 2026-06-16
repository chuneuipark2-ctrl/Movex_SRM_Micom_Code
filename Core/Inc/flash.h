#ifndef __FLASH_H
#define __FLASH_H

#include "main.h"
#include "type.h"

// 1 Mbyte Flash memory single bank organization (256 bits read width)
#define ADDR_FLASH_SECTOR_0     ((INT32U)0x08000000) // Base @ of Sector 0,   32 Kbyte 
#define ADDR_FLASH_SECTOR_1     ((INT32U)0x08008000) // Base @ of Sector 1,   32 Kbyte 
#define ADDR_FLASH_SECTOR_2     ((INT32U)0x08010000) // Base @ of Sector 2,   32 Kbyte 
#define ADDR_FLASH_SECTOR_3     ((INT32U)0x08018000) // Base @ of Sector 3,   32 Kbyte 
#define ADDR_FLASH_SECTOR_4     ((INT32U)0x08020000) // Base @ of Sector 4,  128 Kbyte 
#define ADDR_FLASH_SECTOR_5     ((INT32U)0x08040000) // Base @ of Sector 5,  256 Kbyte 
#define ADDR_FLASH_SECTOR_6     ((INT32U)0x08080000) // Base @ of Sector 6,  256 Kbyte 
#define ADDR_FLASH_SECTOR_7     ((INT32U)0x080C0000) // Base @ of Sector 7,  256 Kbyte 

#define BOOT_PGM_IN_FLASH_START_SECTOR_ADDR     ADDR_FLASH_SECTOR_0			// Sector 0~3,  64 Kbyte 
#define BOOT_PGM_IN_FLASH_END_SECTOR_ADDR       (ADDR_FLASH_SECTOR_2 - 1)	// 

#define DOWN_PGM_IN_FLASH_START_SECTOR_ADDR     ADDR_FLASH_SECTOR_2			// Sector 5 ~ 7,   960 Kbyte 
#define DOWN_PGM_IN_FLASH_END_SECTOR_ADDR       (ADDR_FLASH_SECTOR_7 - 1)	//

extern uint32_t GetSector(uint32_t Address);

HAL_StatusTypeDef FLASH_User_EraseSector(INT32U start_address, INT32U end_address);

INT08U FLASH_User_WriteData(INT32U addr, INT08U* buff, INT32U size);

INT08U FLASH_User_WriteData_1(INT32U Flash_Addr, INT32U buf_Addr, INT32U Total_Size);
#endif
