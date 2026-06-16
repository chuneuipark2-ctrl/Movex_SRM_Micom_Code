/**
  ******************************************************************************
  * @file            : uart.c
  * @version         :
  * @author          :
  * @brief           : This file implements usart function.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

// #include <stdlib.h>
// #include <stdarg.h>

#include "uart.h"

extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart6;

extern DMA_HandleTypeDef hdma_usart3_rx;
extern DMA_HandleTypeDef hdma_usart3_tx;

#define MAX_COM_PORT            20
#define CRCCCITT                0x1021

static volatile INT16U  crcPortTbl[MAX_COM_PORT] = { 0, };

//INT16U CrcTable[256] =
const INT16U CrcTable[256] =
{ 0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
  0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
  0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
  0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
  0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
  0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
  0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
  0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
  0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
  0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
  0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
  0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
  0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
  0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
  0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
  0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
  0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
  0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
  0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
  0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
  0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
  0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
  0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
  0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
  0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
  0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
  0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
  0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
  0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
  0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
  0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
  0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
};

INT16U CRCWhere(INT16U data, INT16U poly, INT16U accum)
{
	INT16U i;

	data <<= 8;
	for (i = 8; i > 0; i--)
	{
		if ((data ^ accum) & 0x8000) accum = (accum << 1) ^ poly;
		else                          accum <<= 1;
		data <<= 1;
	}

	return(accum);
}

/*
void makeCRCTable(void)
{
	INT16U i;

	for (i = 0; i < 256; i++)
	{
		CrcTable[i] = CRCWhere(i, CRCCCITT, 0);
	}
}
*/

/*******************************************************************************/
/* CRC-CCITT ��� : ����ڰ� ������ ����Ʈ ���                                  */
/*******************************************************************************/
INT16U crcByteCalc(INT16U crcValue, INT08U crcCh)
{
	INT08U crcpo;

	crcpo = (crcValue >> 8) ^ crcCh;
	crcValue = (crcValue << 8) ^ CrcTable[crcpo];

	return(crcValue);
}

INT16U crcInitStrCalc(INT16U crcValue, INT08U* crcptr, INT32U len)
{
	INT32U i  = 0;
	INT08U crcpo = 0;

	for (i = 0; i < len; i++)
	{
		crcpo = (crcValue >> 8) ^ crcptr[i];
		crcValue = (crcValue << 8) ^ CrcTable[crcpo];
	}

	return crcValue;
}

//////////////////////////////////////////////////////////////////////////////////////
//extern UART_HandleTypeDef huart3;

UartQSTR	m_RxUartQ[MAX_UART_PORT];
UartQSTR	m_TxUartQ[MAX_UART_PORT];

UartTxBuffSTR  m_TxUartBuff[MAX_UART_PORT];

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
	if (huart->Instance == USART3)
	{
		++m_RxUartQ[rsTMLPort].TC_Count;
		rsComHandlerDMA();
	}
}

void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef* huart)
{
	if (huart->Instance == USART3)
	{
		++m_RxUartQ[rsTMLPort].HT_Count;
		rsComHandlerDMA();
	}
}


void UART_IDLECallback(UART_HandleTypeDef* huart)
{

	if (huart->Instance == USART3)
	{
		++m_RxUartQ[rsTMLPort].IDEL_Count;
		rsComHandlerDMA();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

INT08U getUartRxData(INT08U port, INT08U* rxData)
{
	if (port < MAX_UART_PORT)
	{
		if (m_RxUartQ[port].Front != m_RxUartQ[port].Rear)
		{
			*rxData = m_RxUartQ[port].Data[m_RxUartQ[port].Rear];
			if (++m_RxUartQ[port].Rear >= FRAME_MAX_DATA_LEN) m_RxUartQ[port].Rear = 0;
			return 1;
		}
	}

	return 0;
}

void clsUartRxData(INT08U port)
{
	if (port < MAX_UART_PORT)
	{
		m_RxUartQ[port].Front = 0;
		m_RxUartQ[port].Rear = 0;
	}
}

void Send_Uart_Polling(INT08U port)
{
	if (port < MAX_UART_PORT)
	{
		if (port == rsTMLPort)
		{
#if DEBUG_TML_MSG
			printf("[TML] Transmit Data");

			for (INT16U i = 0; i < m_TxUartQ[port].Len; i++) 
			{
				if ((i % 20) == 0) printf("\r\n");
				printf(" [%02x]", m_TxUartQ[port].Data[i]);
			}

			printf("\r\n");
#endif

			HAL_UART_Transmit(&huart3, m_TxUartQ[port].Data, m_TxUartQ[port].Len, 1000);
		}
		else if (port == rsRS485_422_Port)
		{
#if DEBUG_TML_MSG
			printf("[HMI] Transmit Data");

			for (INT16U i = 0; i < m_TxUartQ[port].Len; i++)
			{
				if ((i % 20) == 0) printf("\r\n");
				printf(" [%02x]", m_TxUartQ[port].Data[i]);
			}

			printf("\r\n");
#endif
			HAL_UART_Transmit(&huart6, m_TxUartQ[port].Data, m_TxUartQ[port].Len, 1000);
		}
		else if (port == rsMCU_DEBUG_Port)
		{
			HAL_UART_Transmit(&huart4, m_TxUartQ[port].Data, m_TxUartQ[port].Len, 1000);
		}
	
		m_TxUartQ[port].Len = 0;
	}
}

void Send_Uart_DMA(INT08U port)
{
	if (port < MAX_UART_PORT)
	{
		if (port == rsTMLPort)
		{
			HAL_UART_Transmit_DMA(&huart3, m_TxUartQ[rsTMLPort].Data, m_TxUartQ[rsTMLPort].Len);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////
void rsPutcPort(INT08U port, INT08U data)
{
	switch (port)
	{
	case UART_1:
	case UART_2:
	case UART_3:
	case UART_4:
	case UART_5:
	case UART_6:
		m_TxUartQ[port].Data[m_TxUartQ[port].Len] = data;
		if (++m_TxUartQ[port].Len >= FRAME_MAX_DATA_LEN) m_TxUartQ[port].Len = FRAME_MAX_DATA_LEN - 1;
		break;
		/*
	case rsUSBPort:
		m_pgmEnv.txUsbComBuffer[m_pgmEnv.txUsbComLen] = data;
		if (++m_pgmEnv.txUsbComLen >= FRAME_MAX_DATA_LEN) m_pgmEnv.txUsbComLen = FRAME_MAX_DATA_LEN - 1;
		break;
		*/
	case rsETHUDPPort_Uplink:
		m_pgmEnv.txEthUdpComBuffer[m_pgmEnv.txEthUdpComLen] = data;
		if (++m_pgmEnv.txEthUdpComLen >= FRAME_ETH_MAX_DATA_LEN) m_pgmEnv.txEthUdpComLen = FRAME_MAX_DATA_LEN - 1;
		break;

	case rsETHTCPPort:
// 		m_pgmEnv.txEthTcpComBuffer[m_pgmEnv.txEthTcpComLen] = data;
// 		if (++m_pgmEnv.txEthTcpComLen >= FRAME_ETH_MAX_DATA_LEN) m_pgmEnv.txEthTcpComLen = FRAME_MAX_DATA_LEN - 1;
		break;

	case rsETHUDPPort_DwLink:
		m_pgmEnv.txInvUdpComBuffer[m_pgmEnv.txInvUdpComLen] = data;
		if (++m_pgmEnv.txInvUdpComLen >= FRAME_ETH_MAX_DATA_LEN) m_pgmEnv.txInvUdpComLen = FRAME_MAX_DATA_LEN - 1;
		break;

	case rsINVTCPPort:
// 		m_pgmEnv.txInvTcpComBuffer[m_pgmEnv.txInvTcpComLen] = data;
// 		if (++m_pgmEnv.txInvTcpComLen >= FRAME_ETH_MAX_DATA_LEN) m_pgmEnv.txInvTcpComLen = FRAME_MAX_DATA_LEN - 1;
		break;

	case rsDSP_UDP_Port:
 		m_pgmEnv.txDSPComBuffer[m_pgmEnv.txDSPComLen] = data;
 		if (++m_pgmEnv.txDSPComLen >= FRAME_DSP_DATA_LEN) m_pgmEnv.txDSPComLen = FRAME_DSP_DATA_LEN - 1;
		break;
	}
}


void rsPutsPort(INT08U port, INT08U* txStr)
{
	while (*txStr) rsPutcPort(port, *txStr++);
}

void rsPutnPort(INT08U port, INT08U* txStr, INT16U txLen)
{
	while (txLen--) rsPutcPort(port, *txStr++);
}

void rsPutmPort(INT08U port, INT08U txData, INT16U txLen)
{
	while (txLen--) rsPutcPort(port, txData);
}

void rsPutwPort(INT08U port, INT16U Value)   // Int
{
	rsPutcPort(port, (Value) & 0xFF);
	rsPutcPort(port, (Value >> 8) & 0xFF);
}

void rsPutiPort(INT08U port, INT16U Value)   // Int
{
	rsPutcPort(port, (Value >> 8) & 0xFF);
	rsPutcPort(port, (Value) & 0xFF);
}

void rsPutdPort(INT08U port, INT32U Value)   // Long
{
	rsPutcPort(port, (Value >> 24) & 0xFF);
	rsPutcPort(port, (Value >> 16) & 0xFF);
	rsPutcPort(port, (Value >> 8) & 0xFF);
	rsPutcPort(port, (Value) & 0xFF);
}

void rsPutfPort(INT08U port, float val)
{
	INT08U chr[4];

	memcpy((INT08U*)chr, (INT08U*)&val, 4);
	rsPutcPort(port, chr[3]);
	rsPutcPort(port, chr[2]);
	rsPutcPort(port, chr[1]);
	rsPutcPort(port, chr[0]);
}

void crcClear(INT08U port)
{
	crcPortTbl[port] = 0;
}

void calcCrc(INT08U port, INT08U crcData)
{
	crcPortTbl[port] = crcByteCalc(crcPortTbl[port], crcData);
}

void txPutcPort(INT08U port, INT08U txData)
{
	calcCrc(port, txData);
	rsPutcPort(port, txData);
}

void txPutwPort(INT08U port, INT16U Value)   // Word
{
	txPutcPort(port, (Value) & 0xFF);
	txPutcPort(port, (Value >> 8) & 0xFF);
}

void txPutlPort(INT08U port, INT32U Value)   // Full Word
{
	txPutcPort(port, (Value) & 0xFF);
	txPutcPort(port, (Value >> 8) & 0xFF);
	txPutcPort(port, (Value >> 16) & 0xFF);
	txPutcPort(port, (Value >> 24) & 0xFF);
}

void txPutiPort(INT08U port, INT16U Value)   // Int
{
	txPutcPort(port, (Value >> 8) & 0xFF);
	txPutcPort(port, (Value) & 0xFF);
}

void txPutfPort(INT08U port, INT32U Value)   // Long
{
	txPutcPort(port, (Value >> 24) & 0xFF);
	txPutcPort(port, (Value >> 16) & 0xFF);
	txPutcPort(port, (Value >> 8) & 0xFF);
	txPutcPort(port, (Value) & 0xFF);
}

void txPutsPort(INT08U port, INT08U* txStr)
{
	while (*txStr) txPutcPort(port, *txStr++);
}

void txPutnPort(INT08U port, INT08U* txStr, INT16U txLen)
{
	while (txLen--) txPutcPort(port, *txStr++);
}

void txCRCPort(INT08U port)
{
	INT16U crcValue;

	crcValue = crcPortTbl[port];
	rsPutcPort(port, (crcValue >> 8) & 0xFF);
	rsPutcPort(port, (crcValue & 0xFF));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ��ȯ���ڿ�  �ǹ� 
// %o          8�� ���� �������� ���  
// %d          10�� ���� �������� ���  
// %ld         long�� 10�� ���� �������� ���  
// %x          16�� ���� �������� ���  
// %u          ��ȣ ���� 10�� ���� �������� ���  
// %f          �Ҽ��� �������� ���  
// %e          %E  ���� �������� ���  
// %g          %G  %e�� %f �� ª�� ��, �Ҽ����� �̾����� 0�� ����  
// %c          ���� �������� ���  
// %s          ���ڿ� �������� ���  

// ��ȯ���ڿ�                              ���                          �ǹ� 
// printf("%d", 123)                       123                           ǥ�� �����ġ�� ���  
// printf("%5d", 123)                      ___123                        10������ 5�ڸ��� ���߾� ���, 123�տ� ���� 2�� �߰�  
// printf("%-5d", 123)                     123__                         10������ 5�ڸ��� ���߾� ���, ���� ����, �����ʿ� ���� �߰�  
// printf("%f", 1.234567)                  1.234567                      16�� ���� �������� ���  
// printf("%4f", 1.234567)                 1.2346                        �ҚY ���� 4�ڸ� ���, �ݿø�  
// printf("%7.2f", 1.234567)               ___1.23                       �Ҽ��� �����ؼ� ��ü 7�ڸ�, �Ҽ��� ���� 2�ڸ�. ���� 3���� �� �κп� �߰��˴ϴ�.  
// printf("%s", "forum.falinux.com")       forum.falinux.com             ���� �������� ���  
// printf("%20s", "forum.falinux.com")     __________forum.falinux.com   �ڸ����� ���߱� ���� ���ʿ� ������ �־� ���ڿ� ���  
// printf("%10s", "forum.falinux.com")     forum.falinux.com             ���ڿ��� �� ��� �״�� ���  
// printf("%.10s", "forum.falinux.com")    forum.fali                    ���ڿ��� �� ��� �߶� ���  
// printf("%-20s", "forum.falinux.com")    forum.falinux.com________     ���ڿ��� ���� �������� �Ͽ� �����ʿ� ���ڸ��� �ڸ��� �������� �޲�  
// printf("%12.10s", "forum.falinux.com")  __forum.fali                  ��ü 12�ڸ��� 10�ڸ��� ���, ���ڸ� �κ��� ���ʿ� ���� �߰��Ͽ� ���  
/*
void printfPort(INT08U port, char* format, ...)
{
	char      buf[256];
	va_list   arg;

	clearTxBuf(port);
	va_start(arg, format);
	vsprintf(buf, format, arg);
	rsPutsPort(port, (INT08U*)buf);
	va_end(arg);
	sendTxBuf(port);
}
*/

/*
void printfPort2(INT08U port, char* format, ...)
{
	char      buf[256];
	va_list   arg;

	va_start(arg, format);
	vsprintf(buf, format, arg);
	rsPutsPort(port, (INT08U*)buf);
	va_end(arg);
}
*/

/*
void printfPort_Data(INT08U port, INT08U* str, INT08U* data, INT16U len)
{
	INT16U i, p = 0;

	clearTxBuf(port);
	printfPort(port, "%s(%d.%03d)\n\r", str, m_pgmEnv.timer1ms / 1000, m_pgmEnv.timer1ms % 1000);
	for (i = 0; i < len; i++)
	{
		printfPort(port, "%02X", data[i]);
		if (++p >= 20)
		{
			printfPort(port, "\n\r");
			p = 0;
		}
		else
		{
			printfPort(port, " ");
		}
	}

	if (p)  printfPort(port, "\n\r");
	printfPort(port, "\n\r");
	sendTxBuf(port);
}
*/

/*
void printfPort_Data2(INT08U port, INT08U* str, INT08U* data, INT16U len)
{
	INT16U i;

	clearTxBuf(port);
	printfPort(port, "%4d.%03dms  %-12s : ", m_pgmEnv.timer1ms / 1000, m_pgmEnv.timer1ms % 1000, str);
	for (i = 0; i < len; i++) printfPort(port, "%02x ", data[i]);
	printfPort(port, "\n\r");
	sendTxBuf(port);
}
*/

/*
void printfPort_Time(INT08U port, INT08U* str)
{
	clearTxBuf(port);
	printfPort(port, "(%4d.%03d)%s", m_pgmEnv.timer1ms / 1000, m_pgmEnv.timer1ms % 1000, str);
	sendTxBuf(port);
}
*/


