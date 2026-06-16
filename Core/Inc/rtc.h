/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RTC_H
#define __RTC_H

#include "type.h"

void setTimeDate_Rev2(INT32U nUtcTime);
INT32U getTimeDate_Rev2(void);

void loadBKSramSTR(void);
void saveBKSramSTR(void);
INT16U loadBKSramBlock(INT08U* ptr, INT16U len);
INT16U saveBKSramBlock(INT08U* ptr, INT16U len);

#endif /* __RTC_H */
