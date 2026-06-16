

#include <stdio.h>
#include <string.h>

#include "main.h"
#include "type.h"
#include "alarm.h"

//#include "ecat_type.h"
//#include "ecat_combase.h"
#include "ecat.h"

//#define MAX_EC_DATAGRAM_COUNT  12
#define MAX_EC_DATAGRAM_COUNT  50
//#define MAX_EC_DATAGRAM_COUNT  64		// #define MAX_FPRD_MULTI 64

#define MAX_ETHERCAT_DATA_LEN  1600

struct __attribute__((__packed__)) tagEC_Frame_STR
{
	INT08U  DstAddr[6];    // FF FF FF FF FF FF
	INT08U  SrcAddr[6];    // 00 0A 1F 00 12 34
	INT16U  EthType;       // 0x88A4  =>  88 A4

	INT16U  EC_Header;     // bit15~bit12:cmd(0x1), bit11:Reserved(0x0), bit10~bit0:Length

	INT08U  EC_Data[MAX_ETHERCAT_DATA_LEN];

	INT16U  Len;
};

typedef struct tagEC_Frame_STR  EC_Frame_STR;

struct __attribute__((__packed__)) tagEC_Datagram_STR
{
	INT08U  Cmd;          // EtherCAT command, see ec_cmdtype 
	INT08U  Index;        // index, used in SOEM for Tx to Rx recombination 
	union
	{
		struct
		{
			INT16U  Adp;          // ADP 
			INT16U  Ado;          // ADO 
		};
		INT32U LAddr;
	};
	INT16U  LengthFlag;   // length of data portion in datagram 
	INT16U  Irq;          // interrupt, currently unused 
	//INT08U  Data[0x120];
	INT08U  Data[0x200];

	INT16U  WCNT;
	INT16U  PacketLen;
};

typedef struct tagEC_Datagram_STR  EC_Datagram_STR;


static EC_Frame_STR        EC_TxFrame;
static EC_Frame_STR        EC_RxFrame;

__attribute__((section(".dtcm_bss"))) EC_Datagram_STR     m_Datagram_Tx[MAX_EC_DATAGRAM_COUNT];
__attribute__((section(".dtcm_bss"))) EC_Datagram_STR     m_Datagram_Rx[MAX_EC_DATAGRAM_COUNT];

// static EC_SyncManager_STR  EC_SyncManager;
// static EC_FMMU_STR         EC_FMMU;
// static EC_MailBox_STR      EC_TxMailBox;
// static EC_MailBox_STR      EC_RxMailBox;

INT16U m_Datagram_Tx_Cnt = 0;
INT16U m_Datagram_Rx_Cnt = 0;

INT08U m_Datagram_Idx = 0;

INT16U EC_Send_Len = 0;

//static INT08U ec_lrd_value = 0x00;

/** Generate and set EtherCAT datagram in a standard ethernet frame.
 *
 * @param[in]  com         = command
 * @param[in]  idx         = index used for TX and RX buffers
 * @param[in]  ADP         = Address Position
 * @param[in]  ADO         = Address Offset
 * @param[in]  length      = length of datagram excluding EtherCAT header
 * @param[in]  data        = databuffer to be copied in datagram
 * @return always 0
 */
INT08U ecx_setupdatagram(INT08U com, INT16U ADP, INT16U ADO, INT16U length, INT08U *data)
{
	m_Datagram_Tx_Cnt = 0;
	
	memset((INT08U *)&m_Datagram_Tx[m_Datagram_Tx_Cnt], 0x00, sizeof(EC_Datagram_STR));

	m_Datagram_Tx[m_Datagram_Tx_Cnt].Cmd = com;
	m_Datagram_Tx[m_Datagram_Tx_Cnt].Index = m_Datagram_Idx;

	m_Datagram_Tx[m_Datagram_Tx_Cnt].Adp = ADP;
	m_Datagram_Tx[m_Datagram_Tx_Cnt].Ado = ADO;
	m_Datagram_Tx[m_Datagram_Tx_Cnt].LengthFlag = (length & 0x07FF);
	m_Datagram_Tx[m_Datagram_Tx_Cnt].Irq = 0x0000;

	if (length > 0)
	{
		switch (com)
		{
		case EC_CMD_NOP:
			/* Fall-through */
		case EC_CMD_APRD:
			/* Fall-through */
		case EC_CMD_FPRD:
			/* Fall-through */
		case EC_CMD_BRD:
			/* Fall-through */
		case EC_CMD_LRD:
			/* no data to write. initialize data so frame is in a known state */
			memset((INT08U*)&m_Datagram_Tx[m_Datagram_Tx_Cnt].Data[0], 0, length);
			break;
		default:
			memcpy((INT08U*)&m_Datagram_Tx[m_Datagram_Tx_Cnt].Data[0], (INT08U*)&data[0], length);
			break;
		}
	}

	m_Datagram_Tx[m_Datagram_Tx_Cnt].PacketLen = length + 10 + 2;   // Datagram_Header(10) + Working_Count(2)
	m_Datagram_Tx[m_Datagram_Tx_Cnt].WCNT = 0;

	++m_Datagram_Tx_Cnt;
	++m_Datagram_Idx;

	return m_Datagram_Tx_Cnt;
}

//void ecx_adddatagram(INT08U Inx, INT08U Cmd, INT16U Adp, INT16U Ado, INT16U Len, INT08U* Data)
void ecx_adddatagram(INT08U Cmd, INT16U Adp, INT16U Ado, INT16U Len, INT08U* Data)
{
	if (m_Datagram_Tx_Cnt <= MAX_EC_DATAGRAM_COUNT)
	{
		memset((INT08U*)&m_Datagram_Tx[m_Datagram_Tx_Cnt], 0x00, sizeof(EC_Datagram_STR));

		m_Datagram_Tx[m_Datagram_Tx_Cnt].Cmd = Cmd;
		m_Datagram_Tx[m_Datagram_Tx_Cnt].Index = m_Datagram_Idx;
		m_Datagram_Tx[m_Datagram_Tx_Cnt].Adp = Adp;
		m_Datagram_Tx[m_Datagram_Tx_Cnt].Ado = Ado;
		m_Datagram_Tx[m_Datagram_Tx_Cnt].LengthFlag = (Len & 0x07FF) | EC_DATAGRAM_FOLLOWS;
		//m_Datagram_Tx[m_Datagram_Tx_Cnt].LengthFlag = (Len & 0x07FF);
		m_Datagram_Tx[m_Datagram_Tx_Cnt].Irq = 0x0000;

		if (Len > 0)
		{
			switch (Cmd)
			{
			case EC_CMD_NOP:
				/* Fall-through */
			case EC_CMD_APRD:
				/* Fall-through */
			case EC_CMD_FPRD:
				/* Fall-through */
			case EC_CMD_BRD:
				/* Fall-through */
			case EC_CMD_LRD:
				/* no data to write. initialize data so frame is in a known state */
				memset((INT08U*)&m_Datagram_Tx[m_Datagram_Tx_Cnt].Data[0], 0, Len);
				break;
			default:
				memcpy((INT08U*)&m_Datagram_Tx[m_Datagram_Tx_Cnt].Data[0], (INT08U*)&Data[0], Len);
				break;
			}
		}

		m_Datagram_Tx[m_Datagram_Tx_Cnt].PacketLen = Len + 10 + 2;   // Datagram_Header(10) + Working_Count(2)
		m_Datagram_Tx[m_Datagram_Tx_Cnt].WCNT = 0;

		++m_Datagram_Tx_Cnt;
		++m_Datagram_Idx;
	}
}

INT08U EC_Transmit_Data(void)
{
	INT08U ret_value = 0;
	INT16U nTxLen = 0;
	INT16U i;

	if (m_Datagram_Tx_Cnt && (m_Datagram_Tx_Cnt <= MAX_EC_DATAGRAM_COUNT))
	{
		EC_TxFrame.DstAddr[0] = 0xff;
		EC_TxFrame.DstAddr[1] = 0xff;
		EC_TxFrame.DstAddr[2] = 0xff;
		EC_TxFrame.DstAddr[3] = 0xff;
		EC_TxFrame.DstAddr[4] = 0xff;
		EC_TxFrame.DstAddr[5] = 0xff;
		EC_TxFrame.SrcAddr[0] = 0x00;
		EC_TxFrame.SrcAddr[1] = 0x0a;
		EC_TxFrame.SrcAddr[2] = 0x1f;
		EC_TxFrame.SrcAddr[3] = 0x00;
		EC_TxFrame.SrcAddr[4] = 0x12;
		EC_TxFrame.SrcAddr[5] = 0x34;
		EC_TxFrame.EthType = SWAP(ETH_P_ECAT);

		for (i = 0; i < m_Datagram_Tx_Cnt; i++)
		{
			if (i == (m_Datagram_Tx_Cnt - 1))
			{
				m_Datagram_Tx[i].LengthFlag &= (~EC_DATAGRAM_FOLLOWS);
			}
			else
			{
				m_Datagram_Tx[i].LengthFlag |= EC_DATAGRAM_FOLLOWS;
			}

			memcpy((INT08U *)&EC_TxFrame.EC_Data[nTxLen], (INT08U *)&m_Datagram_Tx[i], m_Datagram_Tx[i].PacketLen);
			nTxLen += m_Datagram_Tx[i].PacketLen;
		}

		EC_TxFrame.EC_Header = 0x1000 | (nTxLen & 0x07FF);     // bit15~bit12:cmd(0x1), bit11:Reserved(0x0), bit10~bit0:Length

		if (nTxLen < 44)
		{
			memset((INT08U *)&EC_TxFrame.EC_Data[nTxLen], 0x00, (44 - nTxLen));
			nTxLen = 44;
		}

		EC_Send_Len = nTxLen + 16;  // MAC_Header(14) + Ethercat_Header(2)

		PutEthercatTxData_Func((INT08U *)&EC_TxFrame, EC_Send_Len);
	}
	else
	{
		ret_value = 1;
	}

	m_Datagram_Tx_Cnt = 0;

	return ret_value;
}

//void EC_Receive_Data_Process(void)
INT08U EC_Receive_Data_Process(void)
{
	INT16U p = 0;
	INT16U ethcat_len;
	INT16U dg_len;

	INT08U nEC_Recieved = 0;
	//INT16U i;
	
	m_Datagram_Rx_Cnt = 0;

	if (EC_RxFrame.EthType == SWAP(ETH_P_ECAT))
	{
		nEC_Recieved = 1;

		ethcat_len = EC_RxFrame.EC_Header & 0x0FFF;
		
		if (ethcat_len)
		{
			while (p < ethcat_len)
			{
				memcpy((INT08U *)&m_Datagram_Rx[m_Datagram_Rx_Cnt], (INT08U *)&EC_RxFrame.EC_Data[p], 10);    p += 10;
				dg_len = m_Datagram_Rx[m_Datagram_Rx_Cnt].LengthFlag & 0x07FF;
				m_Datagram_Rx[m_Datagram_Rx_Cnt].PacketLen = dg_len;

				memcpy((INT08U *)&m_Datagram_Rx[m_Datagram_Rx_Cnt].Data[0], (INT08U *)&EC_RxFrame.EC_Data[p], dg_len);    p += dg_len;
				memcpy((INT08U *)&m_Datagram_Rx[m_Datagram_Rx_Cnt].WCNT, (INT08U *)&EC_RxFrame.EC_Data[p], 2);    p += 2;

				if (++m_Datagram_Rx_Cnt > MAX_EC_DATAGRAM_COUNT)
				{
					break;
				}
			}
		}
	}
	else
	{
		nEC_Recieved = 0;
		asm volatile("NOP");
	}

	return nEC_Recieved;
}

//#define ETHERCAT_RESPONSE_WAIT_TIME    120		// Max Delay Count 66 

//#define ETHERCAT_RESPONSE_WAIT_TIME    200		// Max Delay Count 77

#define ETHERCAT_RESPONSE_WAIT_TIME    500		// Max Delay Count 77

/*
INT08U EC_Data_Process(void)
{
	static INT32U s_MaxCount;
	INT32U nChk_timer = 0;
	INT08U ret_value = 0;
	INT08U ret;
	INT16U len;

	//HAL_GPIO_WritePin(CPU_RUN_LED_GPIO_Port, CPU_RUN_LED_Pin, GPIO_PIN_RESET);

	m_Datagram_Rx_Cnt = 0;
	ret = EC_Transmit_Data();
	
	if (ret == 0)
	{
		do 
		{
			len = GetEthercatRxData_Func((INT08U*)&EC_RxFrame, sizeof(EC_Frame_STR));

			if (len)
			{
				EC_RxFrame.Len = len;
				EC_Receive_Data_Process();
				ret_value = 1;
			}
			else
			{
				++nChk_timer;
				if (nChk_timer > ETHERCAT_RESPONSE_WAIT_TIME)
				{
					asm volatile("NOP");
					break;
				}
			}
#if ENABLE_WATCHDOG
			WatchDog();
#endif
		} while (!ret_value);

		m_TestStatus.St[DEBUG_STR_27] = nChk_timer;

		if (s_MaxCount < nChk_timer)
		{
			s_MaxCount = nChk_timer;
			m_TestStatus.St[DEBUG_STR_26] = s_MaxCount;
		}

	}

	//HAL_GPIO_WritePin(CPU_RUN_LED_GPIO_Port, CPU_RUN_LED_Pin, GPIO_PIN_SET);

	return ret_value;
}
*/

INT08U EC_Data_Process(INT32U nTimeOut)
{
	//static INT32U s_MaxCount;
	INT32U nChk_timer = 0;
	INT08U ret_value = 0;
	INT08U ret;
	INT16U len;

	m_Datagram_Rx_Cnt = 0;
	ret = EC_Transmit_Data();

	if (ret == 0)
	{
		do
		{
			len = GetEthercatRxData_Func((INT08U*)&EC_RxFrame, sizeof(EC_Frame_STR));

			if (len)
			{
				EC_RxFrame.Len = len;
				EC_Receive_Data_Process();
				ret_value = 1;
			}
			else
			{
				++nChk_timer;
				if (nChk_timer > nTimeOut)
				{
					//asm volatile("NOP");
					break;
				}
			}
#if ENABLE_WATCHDOG
			//WatchDog();
#endif
		} while (!ret_value);

		/*
		m_TestStatus.St[DEBUG_STR_27] = nChk_timer;

		if (s_MaxCount < nChk_timer)
		{
			s_MaxCount = nChk_timer;
			m_TestStatus.St[DEBUG_STR_26] = s_MaxCount;
		}
		*/

	}

	return ret_value;
}

INT08U EC_Data_Process_1(INT32U nTimeOut)
{
	static INT32U s_TimeOut_Count;
	static INT32U s_MaxCount;
	INT32U nChk_timer = 0;
	INT08U ret_value = 0;
	INT08U ret = 1;
	INT16U len = 0;

	m_Datagram_Rx_Cnt = 0;
	ret = EC_Transmit_Data();

	if (ret == 0)
	{
		do
		{
			len = GetEthercatRxData_Func((INT08U*)&EC_RxFrame, sizeof(EC_Frame_STR));
			if (len)
			{
				EC_RxFrame.Len = len;
				EC_Receive_Data_Process();
				ret_value = 1;
			}
			else
			{
				++nChk_timer;
				if (nChk_timer > nTimeOut)
				{
					++s_TimeOut_Count;
					break;
				}
			}
		} while (!ret_value);


		if (s_MaxCount < nChk_timer)
		{
			s_MaxCount = nChk_timer;
		}
	}

#if DEBUG_ECAT_TIMEOUT
	Set_TestStatus(DEBUG_STR_60, nChk_timer);
	Set_TestStatus(DEBUG_STR_61, s_MaxCount);
	Set_TestStatus(DEBUG_STR_62, s_TimeOut_Count);

	m_pgmEnv.EtherCAT_DelayCount = nChk_timer;
	m_pgmEnv.EtherCAT_MaxDelayCount = s_MaxCount;
	m_pgmEnv.EtherCAT_TimeOutCount = s_TimeOut_Count;
#endif

	return ret_value;
}


INT16U EC_MultiData_Process(int n, INT08U* pReadData, INT16U nDataSize, int timeout)
{
	INT16U nWkc = 0;
	INT16U i = 0;
	INT08U nEC_Recieve_Flag = 0;

	//nEC_Recieve_Flag = EC_Data_Process_1(n);
	nEC_Recieve_Flag = EC_Data_Process(1000);

	if (nEC_Recieve_Flag)
	{
		for (i = 0; i < m_Datagram_Rx_Cnt; i++)
		{
			nWkc += m_Datagram_Rx[i].WCNT;
			memcpy((void*)(pReadData + (i * nDataSize)), (void*)m_Datagram_Rx[i].Data, sizeof(INT08U) * (m_Datagram_Rx[i].PacketLen));
		}
	}
	else
	{
		nWkc = 0;
	}

	return nWkc;
}

//////////////////////////////////////////////////////////////////////////////////////////

// Auto Increment Read 
void EC_APRD_SetDatagram(INT16U Adp, INT16U Ado, INT16U Len, void *Data)
{
	//ecx_adddatagram(m_Datagram_Tx_Cnt++, EC_CMD_APRD, Adp, Ado, Len, Data);
	ecx_setupdatagram(EC_CMD_APRD, Adp, Ado, Len, Data);
}

// Auto Increment Write 
void EC_APWR_SetDatagram(INT16U Adp, INT16U Ado, INT16U Len, void *Data)
{
	//ecx_adddatagram(m_Datagram_Tx_Cnt++, EC_CMD_APWR, Adp, Ado, Len, Data);
	ecx_setupdatagram(EC_CMD_APWR, Adp, Ado, Len, Data);
}

// Auto Increment Read Write
void EC_APRW_SetDatagram(INT16U Adp, INT16U Ado, INT16U Len, void *Data)
{
	//ecx_adddatagram(m_Datagram_Tx_Cnt++, EC_CMD_APRW, Adp, Ado, Len, Data);
	ecx_setupdatagram(EC_CMD_APWR, Adp, Ado, Len, Data);
}

// Auto Increment Read Multiple Write 
void EC_ARMW_SetDatagram(INT16U Adp, INT16U Ado, INT16U Len, void *Data)
{
	//ecx_adddatagram(0, EC_CMD_ARMW, Adp, Ado, Len, Data);
	ecx_setupdatagram(EC_CMD_ARMW, Adp, Ado, Len, Data);
}

// Configured Address Read 
void EC_FPRD_SetDatagram(INT16U Adp, INT16U Ado, INT16U Len, void *Data)
{
	//ecx_adddatagram(m_Datagram_Tx_Cnt++, EC_CMD_FPRD, Adp, Ado, Len, Data);
	ecx_setupdatagram(EC_CMD_FPRD, Adp, Ado, Len, Data);
}

// Configured Address Write
void EC_FPWR_SetDatagram(INT16U Adp, INT16U Ado, INT16U Len, void *Data)
{
	//ecx_adddatagram(m_Datagram_Tx_Cnt++, EC_CMD_FPWR, Adp, Ado, Len, Data);
	ecx_setupdatagram(EC_CMD_FPWR, Adp, Ado, Len, Data);

}

// Configured Address Read Write
void EC_FPRW_SetDatagram(INT16U Adp, INT16U Ado, INT16U Len, void *Data)
{
	//ecx_adddatagram(m_Datagram_Tx_Cnt++, EC_CMD_FPRW, Adp, Ado, Len, Data);
	ecx_setupdatagram(EC_CMD_FPRW, Adp, Ado, Len, Data);
}

// Configured Read Multiple Write
void EC_FRMW_SetDatagram(INT16U Adp, INT16U Ado, INT16U Len, void *Data)
{
	//ecx_adddatagram(m_Datagram_Tx_Cnt++, EC_CMD_FRMW, Adp, Ado, Len, Data);
	ecx_setupdatagram(EC_CMD_FRMW, Adp, Ado, Len, Data);
}

// Broadcast Read 
void EC_BRD_SetDatagram(INT16U Adp, INT16U Ado, INT16U Len, void *Data)
{
	//ecx_adddatagram(m_Datagram_Tx_Cnt++, EC_CMD_BRD, Adp, Ado, Len, Data);
	ecx_setupdatagram(EC_CMD_BRD, Adp, Ado, Len, Data);
}

// Broadcast Write 
void EC_BWR_SetDatagram(INT16U Adp, INT16U Ado, INT16U Len, void *Data)
{
	//ecx_adddatagram(m_Datagram_Tx_Cnt++, EC_CMD_BWR, Adp, Ado, Len, Data);
	ecx_setupdatagram(EC_CMD_BWR, Adp, Ado, Len, Data);
}

// Broadcast Read Write
void EC_BRW_SetDatagram(INT16U Adp, INT16U Ado, INT16U Len, void *Data)
{
	//ecx_adddatagram(m_Datagram_Tx_Cnt++, EC_CMD_BRW, Adp, Ado, Len, Data);
	ecx_setupdatagram(EC_CMD_BRW, Adp, Ado, Len, Data);
}

void EC_NOP_SetDatagram(INT16U Adp, INT16U Ado, INT16U Len, void* Data)
{
	//ecx_adddatagram(m_Datagram_Tx_Cnt++, EC_CMD_BRW, Adp, Ado, Len, Data);
	ecx_setupdatagram(EC_CMD_NOP, Adp, Ado, Len, Data);
}

// Logical Memory Read 
void EC_LRD_SetDatagram(INT32U LAddr, INT16U Len, void *Data)
{
	//ecx_adddatagram(0, EC_CMD_LRD, LO_WORD(LAddr), HI_WORD(LAddr), Len, Data);
	ecx_setupdatagram(EC_CMD_LRD, LO_WORD(LAddr), HI_WORD(LAddr), Len, Data);
}

void EC_LRD_AddDatagram(INT32U LAddr, INT16U Len, void* Data)
{
	ecx_adddatagram(EC_CMD_LRD, LO_WORD(LAddr), HI_WORD(LAddr), Len, Data);
	//ecx_setupdatagram(EC_CMD_LRD, LO_WORD(LAddr), HI_WORD(LAddr), Len, Data);
}

// Logical Memory Write 
void EC_LWR_SetDatagram(INT32U LAddr, INT16U Len, void *Data)
{
	//ecx_adddatagram(0, EC_CMD_LWR, LO_WORD(LAddr), HI_WORD(LAddr), Len, Data);
	ecx_setupdatagram(EC_CMD_LWR, LO_WORD(LAddr), HI_WORD(LAddr), Len, Data);
}

// Logical Memory Read Write
void EC_LRW_SetDatagram(INT32U LAddr, INT16U Len, void *Data)
{
	ecx_setupdatagram(EC_CMD_LRW, LO_WORD(LAddr), HI_WORD(LAddr), Len, Data);
}

void EC_LRW_AddDatagram(INT32U LAddr, INT16U Len, void* Data)
{
	ecx_adddatagram(EC_CMD_LRW, LO_WORD(LAddr), HI_WORD(LAddr), Len, Data);
	//ecx_setupdatagram(EC_CMD_LRW, LO_WORD(LAddr), HI_WORD(LAddr), Len, Data);
}

//************************************
// Method:    ecx_NOP
// FullName:  ecx_NOP
// Access:    public 
// Returns:   int
// Parameter: INT16U addr
// Parameter: INT16U len
// Parameter: uint16 length
// Parameter: void * data
// purpose : 
//************************************
int ecx_NOP(INT16U ADP, INT16U ADO, uint16 length, void* data)
{
	INT08U wkc = 0;

	EC_BWR_SetDatagram(ADP, ADO, length, data);

	if (EC_Data_Process(100))
	{
		if (m_Datagram_Rx_Cnt == 1)
		{
			wkc = m_Datagram_Rx[(m_Datagram_Rx_Cnt - 1)].WCNT;
		}

		if (wkc > 0)
		{
			memcpy(data, m_Datagram_Rx[(m_Datagram_Rx_Cnt - 1)].Data, length);
		}
	}
	else
	{

	}

	return wkc;
}

//************************************
// Method:    ecx_BWR
// FullName:  ecx_BWR
// Access:    public 
// Returns:   int
// Parameter: INT16U addr
// Parameter: INT16U len
// Parameter: uint16 length
// Parameter: void * data
// purpose : 
//************************************
int ecx_BWR(INT16U ADP, INT16U ADO, uint16 length, void *data)
{
	INT08U wkc = 0;

	EC_BWR_SetDatagram(ADP, ADO, length, data);

	if (EC_Data_Process(100))
	{
		if (m_Datagram_Rx_Cnt == 1)
		{
			wkc = m_Datagram_Rx[(m_Datagram_Rx_Cnt - 1)].WCNT;
		}

		if (wkc > 0)
		{
			memcpy(data, m_Datagram_Rx[(m_Datagram_Rx_Cnt - 1)].Data, length);
		}
	}

	return wkc;
}

//************************************
// Method:    ecx_BRD
// FullName:  ecx_BRD
// Access:    public 
// Returns:   int
// Parameter: INT16U addr
// Parameter: INT16U len
// Parameter: uint16 length
// Parameter: void * data
// purpose : 
//************************************
int ecx_BRD(INT16U ADP, INT16U ADO, uint16 length, void *data)
{
	INT08U wkc = 0;

	EC_BRD_SetDatagram(ADP, ADO, length, data);

	if (EC_Data_Process(100))
	{
		if (m_Datagram_Rx_Cnt == 1)
		{
			wkc = m_Datagram_Rx[(m_Datagram_Rx_Cnt - 1)].WCNT;
		}

		if (wkc > 0)
		{
			memcpy(data, m_Datagram_Rx[(m_Datagram_Rx_Cnt - 1)].Data, length);
		}
	}

	return wkc;
}

//************************************
// Method:    ecx_APRD
// FullName:  ecx_APRD
// Access:    public 
// Returns:   int
// Parameter: uint16 ADP
// Parameter: uint16 ADO
// Parameter: uint16 length
// Parameter: void * data
// purpose : 
//************************************
int ecx_APRD(uint16 ADP, uint16 ADO, uint16 length, void *data)
{
	INT08U wkc = 0;

	EC_APRD_SetDatagram(ADP, ADO, length, data);

	if (EC_Data_Process(100))
	{
		if (m_Datagram_Rx_Cnt == 1)
		{
			wkc = m_Datagram_Rx[(m_Datagram_Rx_Cnt - 1)].WCNT;
		}

		if (wkc > 0)
		{
			memcpy(data, m_Datagram_Rx[(m_Datagram_Rx_Cnt - 1)].Data, length);
		}
	}

	return wkc;
}

//************************************
// Method:    ecx_ARMW
// FullName:  ecx_ARMW
// Access:    public 
// Returns:   int
// Parameter: uint16 ADP
// Parameter: uint16 ADO
// Parameter: uint16 length
// Parameter: void * data
// purpose : 
//************************************
int ecx_ARMW(uint16 ADP, uint16 ADO, uint16 length, void *data)
{
	INT08U wkc = 0;

	EC_ARMW_SetDatagram(ADP, ADO, length, data);

	if (EC_Data_Process(100))
	{
		if (m_Datagram_Rx_Cnt == 1)
		{
			wkc = m_Datagram_Rx[(m_Datagram_Rx_Cnt - 1)].WCNT;
		}

		if (wkc > 0)
		{
			memcpy(data, m_Datagram_Rx[(m_Datagram_Rx_Cnt - 1)].Data, length);
		}
	}

	return wkc;
}

//************************************
// Method:    ecx_FRMW
// FullName:  ecx_FRMW
// Access:    public 
// Returns:   int
// Parameter: uint16 ADP
// Parameter: uint16 ADO
// Parameter: uint16 length
// Parameter: void * data
// purpose : 
//************************************
int ecx_FRMW(uint16 ADP, uint16 ADO, uint16 length, void *data)
{
	INT08U wkc = 0;

	EC_FRMW_SetDatagram(ADP, ADO, length, data);

	if (EC_Data_Process(100))
	{
		if (m_Datagram_Rx_Cnt == 1)
		{
			wkc = m_Datagram_Rx[(m_Datagram_Rx_Cnt - 1)].WCNT;
		}

		if (wkc > 0)
		{
			memcpy(data, m_Datagram_Rx[(m_Datagram_Rx_Cnt - 1)].Data, length);
		}
	}

	return wkc;
}

//************************************
// Method:    ecx_APRDw
// FullName:  ecx_APRDw
// Access:    public 
// Returns:   uint16
// Parameter: uint16 ADP
// Parameter: uint16 ADO
// purpose : 
//************************************
uint16 ecx_APRDw(uint16 ADP, uint16 ADO)
{
	uint16 w = 0;

	ecx_APRD(ADP, ADO, sizeof(w), &w);

	return w;
}

//************************************
// Method:    ecx_FPRD
// FullName:  ecx_FPRD
// Access:    public 
// Returns:   int
// Parameter: uint16 ADP
// Parameter: uint16 ADO
// Parameter: uint16 length
// Parameter: void * data
// purpose : 
//************************************
int ecx_FPRD(uint16 ADP, uint16 ADO, uint16 length, void *data)
{
	INT08U wkc = 0;

	EC_FPRD_SetDatagram(ADP, ADO, length, data);

	if (EC_Data_Process(5000))
	{
		if (m_Datagram_Rx_Cnt >= 1)
		{
			wkc = m_Datagram_Rx[(m_Datagram_Rx_Cnt - 1)].WCNT;
		}

		if (wkc > 0)
		{
			memcpy(data, m_Datagram_Rx[(m_Datagram_Rx_Cnt - 1)].Data, length);
		}

		memset(&m_Datagram_Rx[(m_Datagram_Rx_Cnt - 1)], 0x00, sizeof(EC_Datagram_STR));
	}

	return wkc;
}

//************************************
// Method:    ecx_FPRDw
// FullName:  ecx_FPRDw
// Access:    public 
// Returns:   uint16
// Parameter: uint16 ADP
// Parameter: uint16 ADO
// purpose : 
//************************************
uint16 ecx_FPRDw(uint16 ADP, uint16 ADO)
{
	uint16 w = 0;

	ecx_FPRD(ADP, ADO, sizeof(w), &w);

	return w;
}

//************************************
// Method:    ecx_APWRw
// FullName:  ecx_APWRw
// Access:    public 
// Returns:   int
// Parameter: uint16 ADP
// Parameter: uint16 ADO
// Parameter: uint16 data
// purpose : 
//************************************
int ecx_APWRw(uint16 ADP, uint16 ADO, uint16 data)
{
	return ecx_APWR(ADP, ADO, sizeof(data), &data);
}

//************************************
// Method:    ecx_APWR
// FullName:  ecx_APWR
// Access:    public 
// Returns:   int
// Parameter: uint16 ADP
// Parameter: uint16 ADO
// Parameter: uint16 length
// Parameter: void * data
// purpose : 
//************************************
int ecx_APWR(uint16 ADP, uint16 ADO, uint16 length, void *data)
{
	INT08U wkc = 0;

	EC_APWR_SetDatagram(ADP, ADO, length, data);

	if (EC_Data_Process(100))
	{
		if (m_Datagram_Rx_Cnt == 1)
		{
			wkc = m_Datagram_Rx[(m_Datagram_Rx_Cnt - 1)].WCNT;
		}

		if (wkc > 0)
		{
			memcpy(data, m_Datagram_Rx[(m_Datagram_Rx_Cnt - 1)].Data, length);
		}
	}

	return wkc;
}

//************************************
// Method:    ecx_FPWRw
// FullName:  ecx_FPWRw
// Access:    public 
// Returns:   int
// Parameter: uint16 ADP
// Parameter: uint16 ADO
// Parameter: uint16 data
// purpose : 
//************************************
int ecx_FPWRw(uint16 ADP, uint16 ADO, uint16 data)
{
	return ecx_FPWR(ADP, ADO, sizeof(data), &data);
}

//************************************
// Method:    ecx_FPWR
// FullName:  ecx_FPWR
// Access:    public 
// Returns:   int
// Parameter: uint16 ADP
// Parameter: uint16 ADO
// Parameter: uint16 length
// Parameter: void * data
// purpose : 
//************************************
int ecx_FPWR(uint16 ADP, uint16 ADO, uint16 length, void *data)
{
	INT08U wkc = 0;

	EC_FPWR_SetDatagram(ADP, ADO, length, data);

	if (EC_Data_Process(1000))
	{
		if (m_Datagram_Rx_Cnt == 1)
		{
			wkc = m_Datagram_Rx[(m_Datagram_Rx_Cnt - 1)].WCNT;
		}

		if (wkc > 0)
		{
			memcpy(data, m_Datagram_Rx[(m_Datagram_Rx_Cnt - 1)].Data, length);
		}
	}

	return wkc;
}

//************************************
// Method:    ecx_LRW
// FullName:  ecx_LRW
// Access:    public 
// Returns:   int
// Parameter: uint32 LogAdr
// Parameter: uint16 length
// Parameter: void * data
// purpose : 
//************************************
int ecx_LRW(uint32 LogAdr, uint16 length, void *data)
{
	INT08U wkc = 0;

	EC_LRW_SetDatagram(LogAdr, length, data);

	if (EC_Data_Process_1(100))
	{
		if (m_Datagram_Rx_Cnt == 1)
		{
			wkc = m_Datagram_Rx[(m_Datagram_Rx_Cnt - 1)].WCNT;
		}

		if (wkc > 0)
		{
			memcpy(data, m_Datagram_Rx[(m_Datagram_Rx_Cnt - 1)].Data, length);

			m_EC_Main.DisconnectFlag = 0;
			m_EC_Main.DisconnectCount = 0;
		}
	}
	else
	{
		++m_EC_Main.DisconnectCount;
		if (m_EC_Main.DisconnectCount > 10)
		{
			m_EC_Main.DisconnectFlag = 1;
		}
	}

	return wkc;
}

//************************************
// Method:    ecx_LRW_OverLoad
// FullName:  ecx_LRW_OverLoad
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: uint32 LogAdr
// Parameter: uint16 length
// Parameter: void * DataOut
// Parameter: void * DataIn
//************************************
int ecx_LRW_OverLoad(uint32 LogAdr, uint16 length, void* DataOut, void* DataIn)
{
	INT08U wkc = 0;

	EC_LRW_SetDatagram(LogAdr, length, DataOut);

	if (EC_Data_Process(100))
	{
		if (m_Datagram_Rx_Cnt == 1)
		{
			wkc = m_Datagram_Rx[(m_Datagram_Rx_Cnt - 1)].WCNT;
		}

		if (wkc > 0)
		{
			memcpy(DataIn, m_Datagram_Rx[(m_Datagram_Rx_Cnt - 1)].Data, length);
		}
	}

	return wkc;
}

//************************************
// Method:    ecx_LRD
// FullName:  ecx_LRD
// Access:    public 
// Returns:   int
// Parameter: uint32 LogAdr
// Parameter: uint16 length
// Parameter: void * data
// purpose : 
//************************************
int ecx_LRD(uint32 LogAdr, uint16 length, void *data)
{
	INT08U wkc = 0;

	EC_LRD_SetDatagram(LogAdr, length, data);

	if (EC_Data_Process(100))
	{
		if (m_Datagram_Rx_Cnt == 1)
		{
			wkc = m_Datagram_Rx[(m_Datagram_Rx_Cnt - 1)].WCNT;
		}

		if (wkc > 0)
		{
			memcpy(data, m_Datagram_Rx[(m_Datagram_Rx_Cnt - 1)].Data, length);
		}
	}

	return wkc;
}

//************************************
// Method:    ecx_LWR
// FullName:  ecx_LWR
// Access:    public 
// Returns:   int
// Parameter: uint32 LogAdr
// Parameter: uint16 length
// Parameter: void * data
// purpose : 
//************************************
int ecx_LWR(uint32 LogAdr, uint16 length, void *data)
{
	INT08U wkc = 0;

	EC_LWR_SetDatagram(LogAdr, length, data);

	if (EC_Data_Process_1(500))
	{
		if (m_Datagram_Rx_Cnt == 1)
		{
			wkc = m_Datagram_Rx[(m_Datagram_Rx_Cnt - 1)].WCNT;
		}

		if (wkc > 0)
		{
			memcpy(data, m_Datagram_Rx[(m_Datagram_Rx_Cnt - 1)].Data, length);
		}

		m_EC_Main.DisconnectFlag = 0;
		m_EC_Main.DisconnectCount = 0;
	}
	else
	{
		++m_EC_Main.DisconnectCount;
		if (m_EC_Main.DisconnectCount > 10)
		{
			m_EC_Main.DisconnectFlag = 1;
		}
	}

	return wkc;
}


//************************************
// Method:    ecx_LRWDC
// FullName:  ecx_LRWDC
// Access:    public 
// Returns:   int
// Parameter: uint32 LogAdr
// Parameter: uint16 length
// Parameter: void * data
// Parameter: uint16 DCrs
// Parameter: int64 * DCtime
// purpose : 
//************************************
int ecx_LRWDC(uint32 LogAdr, uint16 length, void *data, uint16 DCrs, int64 *DCtime)
{
	INT08U i = 0;
	INT08U nTemp[100] = { 0, };
	INT08U wkc = 0;
	int64 DCtE = 0;

#if DEBUG_ETHERCAT_EC_MODULE
	static INT32U s_OperTimer;
	static INT32U s_MaxOperTimer;

	s_OperTimer = m_pgmEnv.timer100us;
#endif

	EC_LRD_SetDatagram(LogAdr, 0, nTemp);
	EC_LRW_AddDatagram(LogAdr, length, data);
	
	DCtE = htoell(*DCtime);
	ecx_adddatagram(EC_CMD_FRMW, DCrs, ECT_REG_DCSYSTIME, sizeof(DCtime), (void*)&DCtE);

	if (EC_Data_Process_1(1000))		// MX-EXT Test �� Disconnect �߻�
	//if (EC_Data_Process_1(2000))
	{
		if (m_Datagram_Rx_Cnt == 3)
		{
			for (i = 0; i < m_Datagram_Rx_Cnt; i++)
			{
				wkc += m_Datagram_Rx[i].WCNT;

				if (m_Datagram_Rx[i].Cmd == EC_CMD_LRW)
				{
					if (m_Datagram_Rx[i].PacketLen == length)
					{
						memcpy(data, m_Datagram_Rx[i].Data, length);
					}
				}
				else if (m_Datagram_Rx[i].Cmd == EC_CMD_LRD)
				{
				}
				else if (m_Datagram_Rx[i].Cmd == EC_CMD_FRMW)
				{
					memcpy((int64*)&DCtE, (int64*)&m_Datagram_Rx[i].Data, sizeof(int64));
					*DCtime = etohll(DCtE);
				}
			}

			m_EC_Main.DisconnectFlag = 0;
			m_EC_Main.DisconnectCount = 0;
		}
	}
	else
	{
		++m_EC_Main.DisconnectCount;
		if (m_EC_Main.DisconnectCount > 10)
		//if (m_ecx_context.DisconnectCount > 100)
		{
			m_EC_Main.DisconnectFlag = 1;
		}
	}

#if DEBUG_ETHERCAT_EC_MODULE
	/*
	m_TestStatus.St[DEBUG_STR_7] = getCalcTimer100us(s_OperTimer);
	if (getCalcTimer100us(s_OperTimer) > s_MaxOperTimer)
	{
		s_MaxOperTimer = getCalcTimer100us(s_OperTimer);
		m_TestStatus.St[DEBUG_STR_8] = s_MaxOperTimer;
	}
	*/
#endif

	return wkc;
}
