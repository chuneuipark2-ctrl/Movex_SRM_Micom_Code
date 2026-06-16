/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MCU_UTIL_H
#define __MCU_UTIL_H

#include "type.h"

INT32U Get_STM32_Dev_ID(void);
INT32U Get_STM32_Rev_ID(void);
INT32U Get_STM32_UniqueID(INT08U inx);
INT16U Get_STM32_FlashSize(void);

#endif
