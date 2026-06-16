/**
  ******************************************************************************
  * @file           : upgrade.h
  * @brief          : Header for8 user_define.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

#ifndef __UPGRADE_H
#define __UPGRADE_H

#include "type.h"
#include "User_Define.h"
#include "com_tml.h"

INT08U				checkFusingString(INT08U* s, INT08U* d, INT08U len);
extern INT16U         getStr2ShortValue(INT08U* str);
extern INT32U         getStr2LongValue(INT08U* str);
//extern void           getFlashSectorAddressSize(INT08U start_sector, INT08U sector_count, INT32U* sAddr, INT32U* mSize);

extern void			initProgram(void);
//extern void           initDownload(void);
extern void           checkDownload(void);

extern void           rxDownloadStart(INT08U port, TMLComPTR pCom);
extern void           rxDownloadData(INT08U port, TMLComPTR pCom);
extern void           rxDownloadFinish(INT08U port, TMLComPTR pCom);


extern void				rxDownloadStart(INT08U port, TMLComPTR pCom);
extern void				rxDownloadData(INT08U port, TMLComPTR pCom);
extern void				rxDownloadFinish(INT08U port, TMLComPTR pCom);
//extern INT16U         calcFileCrc(INT16U totalSize);

#endif
