#include "main.h"

#include "mcu_util.h"

// 0x410 : stm32f1xx medium-density' 
// 0x411 : stm32f2xx' 
// 0x412 : stm32f1xx low-density' 
// 0x413 : stm32f405/407xx and stm32f415/417xx' 
// 0x414 : stm32f1xx high-density' 
// 0x415 : stm32l4xx' 
// 0x416 : stm32l1xx medium-density' 
// 0x417 : stm32l0xx' 
// 0x418 : stm32f1xx connectivity line' 
// 0x419 : stm32f4xx high-density' 
// 0x420 : stm32f1xx value line' 
// 0x421 : stm32f446xx' 
// 0x422 : stm32f3xx' 
// 0x423 : stm32f4xx low power' 
// 0x425 : stm32l0xx cat. 2' 
// 0x427 : stm32l1xx medium-density/plus' 
// 0x428 : stm32f1xx value line high-density' 
// 0x429 : stm32l1xx cat. 2' 
// 0x430 : stm32f1xx xl-density' 
// 0x431 : stm32f411re' 
// 0x432 : stm32f37x' 
// 0x433 : stm32f4xx de' 
// 0x434 : stm32f4xx dsi' 
// 0x435 : stm32l43x' 
// 0x436 : stm32l1xx high-density' 
// 0x437 : stm32l152re' 
// 0x438 : stm32f334' 
// 0x439 : stm32f3xx small' 
// 0x440 : stm32f0xx' 
// 0x441 : stm32f412' 
// 0x442 : stm32f09x' 
// 0x444 : stm32f0xx small' 
// 0x445 : stm32f04x' 
// 0x446 : stm32f303 high-density' 
// 0x447 : stm32l0xx cat. 5' 
// 0x448 : stm32f0xx can' 
// 0x449 : stm32f74xxx/stm32f75xxx' 
// 0x450 : stm32h7xxx' 
// 0x451 : stm32f76xxx/stm32f77xxx' 
// 0x452 : stm32f72xxx/stm32f73xxx' 
// 0x457 : stm32l011' 
// 0x458 : stm32f410' 
// 0x463 : stm32f413' 
/**
  * @brief Read STM32 MCU Device ID
  * @param inx
  * @retval Rev_ID
  */
INT32U Get_STM32_Dev_ID(void)
{
	INT32U ID_Code;

	ID_Code = DBGMCU->IDCODE & 0xFFF;
	ID_Code = (DBGMCU->IDCODE & DBGMCU_IDCODE_DEV_ID_Msk) >> DBGMCU_IDCODE_DEV_ID_Pos;

	return ID_Code;
}

// 0x1000 : Revision A
// 0x1001 : Revision Z
// 0x1003 : Revision Y
// 0x1007 : Revision 1
// 0x2001 : Revision 3
/**
  * @brief Read STM32 MCU Reversion ID
  * @param inx
  * @retval Rev_ID
  */
INT32U Get_STM32_Rev_ID(void)
{
	INT32U revCode;

	revCode = (DBGMCU->IDCODE & DBGMCU_IDCODE_REV_ID_Msk) >> DBGMCU_IDCODE_REV_ID_Pos;

	return revCode;
}

#define STM32F0_UNIQUE_ID_ADDR    0x1FFFF7AC   //STM32F0 
#define STM32F1_UNIQUE_ID_ADDR    0x1FFFF7E8   //STM32F1 
#define STM32F2_UNIQUE_ID_ADDR    0x1FFF7A10   //STM32F2 
#define STM32F3_UNIQUE_ID_ADDR    0x1FFFF7AC   //STM32F3 
#define STM32F4_UNIQUE_ID_ADDR    0x1FFF7A10   //STM32F4 
#define STM32F7_UNIQUE_ID_ADDR    0x1FF0F420   //STM32F7 
#define STM32L0_UNIQUE_ID_ADDR    0x1FF80050   //STM32L0 
#define STM32L1_UNIQUE_ID_ADDR    0x1FF80050   //STM32L1 
#define STM32L4_UNIQUE_ID_ADDR    0x1FFF7590   //STM32L4 
#define STM32H7_UNIQUE_ID_ADDR    0x1FF0F420   //STM32H7 
/**
  * @brief Read STM32 MCU UniqueID
  * @param inx
  * @retval UniqueID
  */
INT32U Get_STM32_UniqueID(INT08U inx)
{
	INT32U Addr;
	INT16U FlashSize = 0;

	Addr = STM32F7_UNIQUE_ID_ADDR + inx * 4;

	//Read the corresponding chip flash memory capacity register to get the Flash size
	FlashSize = *(INT16U*)(Addr);

	return FlashSize;
}

#define STM32F0_FLASH_SIZE_ADDR   0x1FFFF7CC   //STM32F0 
#define STM32F1_FLASH_SIZE_ADDR   0x1FFFF7E0   //STM32F1 
#define STM32F2_FLASH_SIZE_ADDR   0x1FFF7A22   //STM32F2 
#define STM32F3_FLASH_SIZE_ADDR   0x1FFFF7CC   //STM32F3 
#define STM32F4_FLASH_SIZE_ADDR   0x1FFF7A22   //STM32F4 
#define STM32F7_FLASH_SIZE_ADDR   0x1FF0F442   //STM32F7 
#define STM32L0_FLASH_SIZE_ADDR   0x1FF8007C   //STM32L0 
#define STM32L1_FLASH_SIZE_ADDR   0x1FF8004C   //STM32L1 
#define STM32L4_FLASH_SIZE_ADDR   0x1FFF75E0   //STM32L4 
#define STM32H7_FLASH_SIZE_ADDR   0x1FF0F442   //STM32H7 

/**
  * @brief Read STM32 MCU Flash size 
  * @param none
  * @retval Flash Size (Unit : KBytes) 
  */
INT16U Get_STM32_FlashSize(void)
{
	INT16U FlashSize = 0;
	INT32U Addr;

	Addr = STM32F7_FLASH_SIZE_ADDR;

	//Read the corresponding chip flash memory capacity register to get the Flash size
	FlashSize = *(INT16U*)(Addr);

	return FlashSize;
}
