/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_H
#define __UART_H

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <stdarg.h>
// #include <time.h>

//#include "main.h"

#include "stm32f7xx_hal.h"

#include "type.h"
#include "User_Define.h"
#include "com_tml.h"

struct __attribute__((__packed__)) tagUartQ
{
	INT16U      Len;
	INT16U      Front;
	INT16U      Rear;
	INT16U		HT_Count;
	INT16U		TC_Count;
	INT16U		IDEL_Count;
	INT08U		RecvFlag;
	INT32U		rx_com_chkTimer;
	INT08U		RS485_Mode;
	INT08U		RS485_422_Tx_Flag;
	INT08U      Data[FRAME_MAX_DATA_LEN];
};
typedef struct tagUartQ  UartQSTR;

extern UartQSTR	m_RxUartQ[MAX_UART_PORT];
extern UartQSTR	m_TxUartQ[MAX_UART_PORT];

struct __attribute__((__packed__)) tagUartTxBuff
{
	INT16U       Len;
	INT16U       Pos;
	INT08U       TxEn;
	INT08U       Delay;
	INT08U       Data[FRAME_MAX_DATA_LEN];
};
typedef struct tagUartTxBuff  UartTxBuffSTR;

extern void           makeCRCTable(void);
extern INT16U         crcByteCalc(INT16U crcValue, INT08U crcCh);
extern INT16U         crcInitStrCalc(INT16U crcValue, INT08U* crcptr, INT32U len);
extern INT08U         getUartRxData(INT08U port, INT08U* rxData);
extern void           clsUartRxData(INT08U port);

extern void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart);
extern void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef* huart);
extern void UART_IDLECallback(UART_HandleTypeDef* huart);

extern void           Send_Uart_Polling(INT08U port);
//extern void           Send_Uart_DMA(INT08U port);

extern void           rsPutcPort(INT08U port, INT08U data);
extern void           rsPutsPort(INT08U port, INT08U* txStr);
extern void           rsPutnPort(INT08U port, INT08U* txStr, INT16U txLen);
extern void           rsPutmPort(INT08U port, INT08U txData, INT16U txLen);
extern void           rsPutiPort(INT08U port, INT16U Value);   // Int
extern void           rsPutdPort(INT08U port, INT32U Value);   // Long
extern void           rsPutfPort(INT08U port, float val);
extern void           crcClear(INT08U port);
extern void           calcCrc(INT08U port, INT08U crcData);
extern void           txPutcPort(INT08U port, INT08U txData);
extern void           txPutwPort(INT08U port, INT16U Value);
extern void           txPutlPort(INT08U port, INT32U Value);
extern void           txPutiPort(INT08U port, INT16U Value);
extern void           txPutfPort(INT08U port, INT32U Value);
extern void           txPutsPort(INT08U port, INT08U* txStr);
extern void           txPutnPort(INT08U port, INT08U* txStr, INT16U txLen);
extern void           txCRCPort(INT08U port);

#endif /* __UART_H */