/**
  ******************************************************************************
  * @file            : fpga.c
  * @version         :
  * @author          :
  * @brief           : This file implements FPGA
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

#include "fpga.h"

__packed struct tagFpgaEthReg
{
    INT08U  MacAddr[6];        // 0x0 ~ 0x5
    INT08U  IpAddr[4];         // 0x6 ~ 0x9
    INT08U  Status;            // 0xA
    INT08U  Read_Buff_Num;     // 0xB
    INT08U  Recv_Buff_Num;     // 0xC
    INT08U  Send_Cmd;          // 0xD
    INT16U  Send_Size;         // 0xE ~ 0xF
    //INT08U  LinkStatus;        // 0x10
};
typedef struct tagFpgaEthReg  FpgaEthRegSTR;

__packed struct tagFpgaEthCatReg
{
    INT08U  MacAddr[6];        // 0x0 ~ 0x5
    INT08U  IpAddr[4];         // 0x6 ~ 0x9
    INT08U  Status;            // 0xA
    INT08U  Read_Buff_Num;     // 0xB
    INT08U  Recv_Buff_Num;     // 0xC
    INT08U  Send_Cmd;          // 0xD
    INT16U  Send_Size;         // 0xE ~ 0xF
    //INT08U  LinkStatus;
    //INT08U  SwitchControl;
};
typedef struct tagFpgaEthCatReg  FpgaEthCatRegSTR;

__packed struct tagFpgaSsiReg
{
    INT08U  Status;          // 0x0
    INT08U  Send_Cmd;        // 0x1
    //INT16U  Clk_Divider;     // 0x2 ~ 0x3
    INT08U  Clk_Divider[2];     // 0x2 ~ 0x3
    INT08U  Send_bit;        // 0x4 
    //INT32U  Read_Data;       // 0x5 ~ 0x8
    INT08U  Read_Data[4];    // 0x34 ~ 0x36
    INT08U  Reserved[7];     // 0x9 ~ 0xF
};
typedef struct tagFpgaSsiReg  FpgaSsiRegSTR;

__packed struct tagFpgaPtoReg
{
    //INT32U  Pulse_Low_Cnt;     // 0x0 ~ 0x03
    INT08U  Pulse_Low_Cnt[4];     // 0x0 ~ 0x03
    //INT32U  Pulse_High_Cnt;    // 0x4 ~ 0x07 
    INT08U  Pulse_High_Cnt[4];    // 0x4 ~ 0x07 
    INT08U  Cnt_Apply;         // 0x8
    INT08U  Reserved2[7];      // 0x9 ~ 0xF
};
typedef struct tagFpgaPtoReg  FpgaPtoRegSTR;

/*
__packed struct tagFpgaReg
{
    INT08U  Reserved1[2];         // 0x00 ~ 0x01
    INT08U  ID;                   // 0x02
    INT08U  Version;              // 0x03
    INT08U  Reserved2[4];         // 0x04 ~ 0x07
    INT08U  FpgaTest[4];          // 0x08 ~ 0x0B
    INT08U  Reserved3[4];         // 0x0C ~ 0x0F
    INT08U  Reserved4[0x10];      // 0x10 ~ 0x1F

    FpgaEthRegSTR EthNet;         // 0x20 ~ 0x2F
    INT08U  Reserved5[0x10];      // 0x30 ~ 0x3F

    FpgaEthRegSTR EthCat;         // 0x40 ~ 0x4F
    INT08U  Reserved6[0x10];      // 0x50 ~ 0x5F

    FpgaSsiRegSTR SSI;            // 0x60 ~ 0x6F
    INT08U  Reserved7[0x10];      // 0x70 ~ 0x7F

    FpgaPtoRegSTR PTO;            // 0x80 ~ 0x8F
    INT08U  Reserved8[0x10];      // 0x90 ~ 0x9F
};
typedef struct tagFpgaReg  FpgaRegSTR;
*/

__packed struct tagFpgaReg
{
    INT08U  Reserved1[2];         // 0x00 ~ 0x01
    INT08U  ID;                   // 0x02
    INT08U  Version;              // 0x03
    INT08U  Reserved2[4];         // 0x04 ~ 0x07
    INT08U  FpgaTest[4];          // 0x08 ~ 0x0B
    INT08U  Reserved3[4];         // 0x0C ~ 0x0F
    INT08U  Reserved4[0x10];      // 0x10 ~ 0x1F

    union
    {
        FpgaEthRegSTR EthNet;     // 0x20 ~ 0x30
        INT08U  EthNetReg[0x10];
    };
    INT08U  Reserved5[0x10];      // 0x31 ~ 0x3F

    union
    {
        FpgaEthRegSTR EthCat;         // 0x40 ~ 0x4F
        //FpgaEthCatRegSTR EthCat;         // 0x40 ~ 0x51
        INT08U  EthCatReg[0x10];
    };
    INT08U  Reserved6[0x10];      // 0x50 ~ 0x5F

    union
    {
        FpgaSsiRegSTR SSI;            // 0x60 ~ 0x6F
        INT08U  SsiReg[0x10];
    };
    INT08U  Reserved7[0x10];      // 0x70 ~ 0x7F

    union
    {
        FpgaPtoRegSTR PTO;            // 0x80 ~ 0x8F
        INT08U  PtoReg[0x10];
    };
    INT08U  Reserved8[0x10];      // 0x90 ~ 0x9F
};
typedef struct tagFpgaReg  FpgaRegSTR;

__packed struct tagFpgaMem
{
    INT08U  Data[0x800];
};
typedef struct tagFpgaMem  FpgaMemSTR;

/*
volatile FpgaRegSTR *m_FpgaReg   = (volatile FpgaRegSTR *)(ADDR_FSMC_FPGA_REG);
volatile FpgaMemSTR *m_FpgaNetTx = (volatile FpgaMemSTR *)(ADDR_FSMC_ETHERNET_TX_MEM);
volatile FpgaMemSTR *m_FpgaNetRx = (volatile FpgaMemSTR *)(ADDR_FSMC_ETHERNET_RX_MEM);
volatile FpgaMemSTR *m_FpgaCatTx = (volatile FpgaMemSTR *)(ADDR_FSMC_ETHERCAT_TX_MEM);
volatile FpgaMemSTR *m_FpgaCatRx = (volatile FpgaMemSTR *)(ADDR_FSMC_ETHERCAT_RX_MEM);
*/

FpgaRegSTR* m_FpgaReg = (FpgaRegSTR*)(ADDR_FSMC_FPGA_REG);
FpgaMemSTR* m_FpgaNetTx = (FpgaMemSTR*)(ADDR_FSMC_ETHERNET_TX_MEM);
FpgaMemSTR* m_FpgaNetRx = (FpgaMemSTR*)(ADDR_FSMC_ETHERNET_RX_MEM);
FpgaMemSTR* m_FpgaCatTx = (FpgaMemSTR*)(ADDR_FSMC_ETHERCAT_TX_MEM);
FpgaMemSTR* m_FpgaCatRx = (FpgaMemSTR*)(ADDR_FSMC_ETHERCAT_RX_MEM);

/*
static INT32U byte2word(INT08U* buff)
{
    return ((INT32U)buff[0] << 24) | ((INT32U)buff[1] << 16) | ((INT32U)buff[2] << 8) | ((INT32U)buff[3] << 0);
}
*/

/*
static INT16U byte2hword(INT08U* buff)
{
    return ((INT32U)buff[0] << 8) | ((INT32U)buff[1] << 0);
}
*/

INT08U get_FPGA_ID(void)
{
    return m_FpgaReg->ID;
}

INT08U get_FPGA_Version(void)
{
    return m_FpgaReg->Version;
}

//////////////////////////////////////////////////////////////////////////////////////
// SSI Function
//////////////////////////////////////////////////////////////////////////////////////

INT08U get_FPGA_SSI_Status(void)
{
    return m_FpgaReg->SSI.Status;
}

void set_FPGA_SSI_Send_Cmd(INT08U mode)
{
    m_FpgaReg->SSI.Send_Cmd = mode;
}

INT08U get_FPGA_SSI_Send_Bit(void)
{
    return m_FpgaReg->SSI.Send_bit;
}

void set_FPGA_SSI_Send_Bit(INT08U bit_cnt)
{
    if (bit_cnt > 31) bit_cnt = 31;
    if (bit_cnt < 8) bit_cnt = 8;

    m_FpgaReg->SSI.Send_bit = bit_cnt;
}

INT16U get_FPGA_SSI_Clk(void)
{
    INT32U value = 0;
    INT08U ssi_data[4] = { 0, };

    ssi_data[0] = m_FpgaReg->SSI.Clk_Divider[0];
    ssi_data[1] = m_FpgaReg->SSI.Clk_Divider[1];
 
    value = ((INT32U)ssi_data[1] << 8) | ((INT32U)ssi_data[0]);

    return value;
}

void set_FPGA_SSI_Clk(INT16U nClk)
{
	m_FpgaReg->SSI.Clk_Divider[0] = (INT08U)nClk;
	m_FpgaReg->SSI.Clk_Divider[1] = (INT08U)(nClk >> 8);
}

INT32U get_FPGA_SSI_Read_Data(void)
{
    INT32U value = 0;
    ///*
    INT08U ssi_data[4] = { 0, };

	ssi_data[0] = m_FpgaReg->SSI.Read_Data[0];
	ssi_data[1] = m_FpgaReg->SSI.Read_Data[1];
	ssi_data[2] = m_FpgaReg->SSI.Read_Data[2];
	//ssi_data[3] = m_FpgaReg->SSI.Read_Data[3];

	value = ((INT32U)ssi_data[2] << 16) | ((INT32U)ssi_data[1] << 8) | ((INT32U)ssi_data[0]);
	//*/
     
    //value = m_FpgaReg->SSI.Read_Data;
   
    return value;
}

//////////////////////////////////////////////////////////////////////////////////////
// Inverter Function
//////////////////////////////////////////////////////////////////////////////////////

INT32U get_FPGA_PTO_Pulse_Low_Count(void)
{
	INT32U value = 0;
	///*
    INT08U inv_data[3] = { 0, };

	inv_data[0] = m_FpgaReg->PTO.Pulse_Low_Cnt[0];
	inv_data[1] = m_FpgaReg->PTO.Pulse_Low_Cnt[1];
	inv_data[2] = m_FpgaReg->PTO.Pulse_Low_Cnt[2];
	inv_data[3] = m_FpgaReg->PTO.Pulse_Low_Cnt[3];

    value = ((INT32U)inv_data[3] << 24) | ((INT32U)inv_data[2] << 16) | ((INT32U)inv_data[1] << 8) | ((INT32U)inv_data[0]);
	//*/

	//value = m_FpgaReg->PTO.Pulse_Low_Cnt;

	return value;
}

INT32U get_FPGA_PTO_Pulse_High_Count(void)
{
    INT32U value = 0;
    ///*
	INT08U inv_data[4];

	inv_data[0] = m_FpgaReg->PTO.Pulse_High_Cnt[0];
	inv_data[1] = m_FpgaReg->PTO.Pulse_High_Cnt[1];
	inv_data[2] = m_FpgaReg->PTO.Pulse_High_Cnt[2];
	inv_data[3] = m_FpgaReg->PTO.Pulse_High_Cnt[3];

	value = ((INT32U)inv_data[3] << 24) | ((INT32U)inv_data[2] << 16) | ((INT32U)inv_data[1] << 8) | ((INT32U)inv_data[0]);
	//*/

   //value = m_FpgaReg->PTO.Pulse_High_Cnt;

    return value;
}

void set_FPGA_PTO_Pulse_Low_Count(INT32U cnt)
{
    //m_FpgaReg->PTO.Pulse_Low_Cnt = cnt;
    ///*
	m_FpgaReg->PTO.Pulse_Low_Cnt[3] = (INT08U)(cnt >> 24) & 0xFF;
	m_FpgaReg->PTO.Pulse_Low_Cnt[2] = (INT08U)(cnt >> 16) & 0xFF;
	m_FpgaReg->PTO.Pulse_Low_Cnt[1] = (INT08U)(cnt >> 8) & 0xFF;
	m_FpgaReg->PTO.Pulse_Low_Cnt[0] = (INT08U)(cnt >> 0) & 0xFF;
	//*/
}

void set_FPGA_PTO_Pulse_High_Count(INT32U cnt)
{
    //m_FpgaReg->PTO.Pulse_High_Cnt = cnt;
    ///*
    m_FpgaReg->PTO.Pulse_High_Cnt[3] = (cnt >> 24) & 0xFF;
    m_FpgaReg->PTO.Pulse_High_Cnt[2] = (cnt >> 16) & 0xFF;
    m_FpgaReg->PTO.Pulse_High_Cnt[1] = (cnt >> 8) & 0xFF;
    m_FpgaReg->PTO.Pulse_High_Cnt[0] = (cnt >> 0) & 0xFF;
    //*/
}

void set_FPGA_PTO_Pulse_Count_Apply(INT08U nFlag)
{
    (nFlag) ? (m_FpgaReg->PTO.Cnt_Apply = 1) : (m_FpgaReg->PTO.Cnt_Apply = 0);
}

/*
void set_FPGA_PTO_Pulse_Count_Apply(void)
{
    m_FpgaReg->PTO.Cnt_Apply = 1;
}
*/

void set_FPGA_PTO_Pulse_Freq(INT32U freq)
{
    INT32U cnt = 0;

    //if (freq > 1000000)  freq = 10000000;
    if (freq > 1000000)  freq = 1000000;
    if (freq < 5)  freq = 0;

    if (freq != 0)
    {
        cnt = 50000000 / (freq * 2);
    }
    /*
        m_FpgaReg->INV.Pulse_Low_Cnt[1]  = (cnt>>16)&0xFF;
        m_FpgaReg->INV.Pulse_Low_Cnt[2]  = (cnt>> 8)&0xFF;
        m_FpgaReg->INV.Pulse_Low_Cnt[3]  = (cnt>> 0)&0xFF;
        m_FpgaReg->INV.Pulse_High_Cnt[1] = (cnt>>16)&0xFF;
        m_FpgaReg->INV.Pulse_High_Cnt[2] = (cnt>> 8)&0xFF;
        m_FpgaReg->INV.Pulse_High_Cnt[3] = (cnt>> 0)&0xFF;
    */

    set_FPGA_PTO_Pulse_Count_Apply(0);

    set_FPGA_PTO_Pulse_High_Count(cnt);
    set_FPGA_PTO_Pulse_Low_Count(cnt);
    //m_FpgaReg->PTO.Pulse_Low_Cnt = cnt;
    //m_FpgaReg->PTO.Pulse_High_Cnt = cnt;
    //m_FpgaReg->PTO.Cnt_Apply = 1;

    set_FPGA_PTO_Pulse_Count_Apply(1);
}

//////////////////////////////////////////////////////////////////////////////////////
// EtherNet Function
//////////////////////////////////////////////////////////////////////////////////////

void set_FPGA_EthNet_MAC_Address(INT08U* addr)
{
    m_FpgaReg->EthNet.MacAddr[0] = addr[0];
    m_FpgaReg->EthNet.MacAddr[1] = addr[1];
    m_FpgaReg->EthNet.MacAddr[2] = addr[2];
    m_FpgaReg->EthNet.MacAddr[3] = addr[3];
    m_FpgaReg->EthNet.MacAddr[4] = addr[4];
    m_FpgaReg->EthNet.MacAddr[5] = addr[5];
}

void set_FPGA_EthNet_IP_Address(INT08U* addr)
{
    m_FpgaReg->EthNet.IpAddr[0] = addr[0];
    m_FpgaReg->EthNet.IpAddr[1] = addr[1];
    m_FpgaReg->EthNet.IpAddr[2] = addr[2];
    m_FpgaReg->EthNet.IpAddr[3] = addr[3];
}

INT08U get_FPGA_EthNet_Read_Buff_Num(void)
{
    return m_FpgaReg->EthNet.Read_Buff_Num;
}

INT08U get_FPGA_EthNet_Recv_Buff_Num(void)
{
    return m_FpgaReg->EthNet.Recv_Buff_Num;
}

void set_FPGA_EthNet_Read_Buff_Num(INT08U num)
{
    m_FpgaReg->EthNet.Read_Buff_Num = num;
}

INT08U get_FPGA_EthNet_RxBuff(INT16U addr)
{
    return m_FpgaNetRx->Data[addr];
}

void get_FPGA_EthNet_RxBuff_Len(INT16U addr, INT08U* buff, INT16U len)
{
    memcpy((INT08U*)&buff[0], (INT08U*)&m_FpgaNetRx->Data[addr], len);
}

void set_FPGA_EthNet_TxBuff(INT16U addr, INT08U data)
{
    m_FpgaNetTx->Data[addr] = data;
}

void set_FPGA_EthNet_TxBuff_Len(INT16U addr, INT08U* buff, INT16U len)
{
    memcpy((INT08U*)&m_FpgaNetTx->Data[addr], (INT08U*)&buff[0], len);
}

void set_FPGA_EthNet_Send_Size(INT16U len)
{
    m_FpgaReg->EthNet.Send_Size = len;
}

void set_FPGA_EthNet_Send_Cmd(INT08U mode)
{
    m_FpgaReg->EthNet.Send_Cmd = mode;
}

INT16U getFPGAEthernet(INT08U* buff, INT16U buff_size)
{
    //INT08U i;
    //INT32U dst_mac;
    //INT32U src_mac;
    //INT32U eth_type;
    INT16U ret = 0;
    INT16U len;
    INT08U recv_buff_num1;
    INT08U recv_buff_num2;
    INT08U read_buff_num1;
    INT08U read_buff_num2;

    recv_buff_num1 = get_FPGA_EthNet_Recv_Buff_Num();
    read_buff_num1 = get_FPGA_EthNet_Read_Buff_Num();
    recv_buff_num2 = get_FPGA_EthNet_Recv_Buff_Num();
    read_buff_num2 = get_FPGA_EthNet_Read_Buff_Num();

    if ((recv_buff_num1 == recv_buff_num2) && (read_buff_num1 == read_buff_num2))
    {
        if (recv_buff_num1 != read_buff_num1)
        {
            len = ((INT16U)get_FPGA_EthNet_RxBuff(2000));
            len |= ((INT16U)get_FPGA_EthNet_RxBuff(2001) << 8);

            if ((len > 14) && (len < 1600) && (len <= buff_size))
            {
                get_FPGA_EthNet_RxBuff_Len(0, (INT08U*)&buff[0], len);
                ret = len;
            }

            if (++read_buff_num1 >= 8)  read_buff_num1 = 0;
            set_FPGA_EthNet_Read_Buff_Num(read_buff_num1);
        }

        m_pgmEnv.FpgaNetReadInx = read_buff_num1;
        m_pgmEnv.FpgaNetRecvInx = recv_buff_num1;
    }

    return ret;
}

void putFPGAEthernet(INT08U* buff, INT16U buff_size)
{
    if (buff_size <= 1492)
    {
        set_FPGA_EthNet_TxBuff_Len(0, (INT08U*)&buff[0], buff_size);
        set_FPGA_EthNet_Send_Size(buff_size);
        set_FPGA_EthNet_Send_Cmd(1);
    }
}


//////////////////////////////////////////////////////////////////////////////////////
// EtherCat Function
//////////////////////////////////////////////////////////////////////////////////////

//************************************
// Method:    get_FPGA_EthCat_Status
// FullName:  get_FPGA_EthCat_Status
// Access:    public 
// Returns:   extern INT08U
// Qualifier:
// Parameter: void
//************************************
INT08U get_FPGA_EthCat_Status(void)
{
    return m_FpgaReg->EthCat.Status;
}

void set_FPGA_EthCat_MAC_Address(INT08U* addr)
{
    m_FpgaReg->EthCat.MacAddr[0] = addr[0];
    m_FpgaReg->EthCat.MacAddr[1] = addr[1];
    m_FpgaReg->EthCat.MacAddr[2] = addr[2];
    m_FpgaReg->EthCat.MacAddr[3] = addr[3];
    m_FpgaReg->EthCat.MacAddr[4] = addr[4];
    m_FpgaReg->EthCat.MacAddr[5] = addr[5];
}

void set_FPGA_EthCat_IP_Address(INT08U* addr)
{
    m_FpgaReg->EthCat.IpAddr[0] = addr[0];
    m_FpgaReg->EthCat.IpAddr[1] = addr[1];
    m_FpgaReg->EthCat.IpAddr[2] = addr[2];
    m_FpgaReg->EthCat.IpAddr[3] = addr[3];
}

INT08U get_FPGA_EthCat_Read_Buff_Num(void)
{
    return m_FpgaReg->EthCat.Read_Buff_Num;
}

INT08U get_FPGA_EthCat_Recv_Buff_Num(void)
{
    return m_FpgaReg->EthCat.Recv_Buff_Num;
}

void set_FPGA_EthCat_Read_Buff_Num(INT08U num)
{
    m_FpgaReg->EthCat.Read_Buff_Num = num;
}

INT08U get_FPGA_EthCat_RxBuff(INT16U addr)
{
    return m_FpgaCatRx->Data[addr];
}

void get_FPGA_EthCat_RxBuff_Len(INT16U addr, INT08U* buff, INT16U len)
{
    memcpy((INT08U*)&buff[0], (INT08U*)&m_FpgaCatRx->Data[addr], len);
}

void set_FPGA_EthCat_TxBuff(INT16U addr, INT08U data)
{
    m_FpgaCatTx->Data[addr] = data;
}

void set_FPGA_EthCat_TxBuff_Len(INT16U addr, INT08U* buff, INT16U len)
{
    memcpy((INT08U*)&m_FpgaCatTx->Data[addr], (INT08U*)&buff[0], len);
}

void set_FPGA_EthCat_Send_Size(INT16U len)
{
    m_FpgaReg->EthCat.Send_Size = len;
}

void set_FPGA_EthCat_Send_Cmd(INT08U mode)
{
    m_FpgaReg->EthCat.Send_Cmd = mode;
}

INT16U getFPGAEthercat(INT08U* buff, INT16U buff_size)
{
    //INT08U i = 0;
    //INT32U dst_mac = 0;
    //INT32U src_mac = 0;
    //INT32U eth_type = 0;
    INT16U ret = 0;
    INT16U len = 0;
    INT08U recv_buff_num1 = 0;
    INT08U read_buff_num1 = 0;

    //INT08U recv_buff_num2 = 0;
    //INT08U read_buff_num2 = 0;

    recv_buff_num1 = get_FPGA_EthCat_Recv_Buff_Num();
    read_buff_num1 = get_FPGA_EthCat_Read_Buff_Num();
//     recv_buff_num2 = get_FPGA_EthCat_Recv_Buff_Num();
//     read_buff_num2 = get_FPGA_EthCat_Read_Buff_Num();
    
	if (recv_buff_num1 != read_buff_num1)
	{
		len = ((INT16U)get_FPGA_EthCat_RxBuff(2000));
		len |= ((INT16U)get_FPGA_EthCat_RxBuff(2001) << 8);

		if ((len > 14) && (len < 1492) && (len <= buff_size))
		{
			get_FPGA_EthCat_RxBuff_Len(0, (INT08U*)&buff[0], len);
			ret = len;
			//++m_TestStatus.St[DEBUG_STR_2];
		}
		else
		{
            //++m_TestStatus.St[DEBUG_STR_3];
		}

		if (++read_buff_num1 >= 8)  read_buff_num1 = 0;
		set_FPGA_EthCat_Read_Buff_Num(read_buff_num1);

		recv_buff_num1 = get_FPGA_EthCat_Recv_Buff_Num();
		read_buff_num1 = get_FPGA_EthCat_Read_Buff_Num();

        if (recv_buff_num1 != read_buff_num1)
        {
            //++m_TestStatus.St[DEBUG_STR_4];
			set_FPGA_EthCat_Read_Buff_Num(recv_buff_num1);
        }
	}

	m_pgmEnv.FpgaCatReadInx = read_buff_num1;
	m_pgmEnv.FpgaCatRecvInx = recv_buff_num1;

	//m_TestStatus.St[DEBUG_STR_5] = m_pgmEnv.FpgaCatReadInx;
	//m_TestStatus.St[DEBUG_STR_6] = m_pgmEnv.FpgaCatRecvInx;


    /*
    if ((recv_buff_num1 == recv_buff_num2) && (read_buff_num1 == read_buff_num2))
    {
        if (recv_buff_num1 != read_buff_num1)
        {
            len = ((INT16U)get_FPGA_EthCat_RxBuff(2000));
            len |= ((INT16U)get_FPGA_EthCat_RxBuff(2001) << 8);

            if ((len > 14) && (len < 1492) && (len <= buff_size))
            {
                get_FPGA_EthCat_RxBuff_Len(0, (INT08U*)&buff[0], len);
                ret = len;
                m_TestStatus.St[DEBUG_STR_2]++;
            }
            else
            {
                m_TestStatus.St[DEBUG_STR_3]++;
            }

            if (++read_buff_num1 >= 8)  read_buff_num1 = 0;
            set_FPGA_EthCat_Read_Buff_Num(read_buff_num1);
        }

        m_pgmEnv.FpgaCatReadInx = read_buff_num1;
        m_pgmEnv.FpgaCatRecvInx = recv_buff_num1;

		m_TestStatus.St[DEBUG_STR_4] = m_pgmEnv.FpgaCatReadInx;
		m_TestStatus.St[DEBUG_STR_5] = m_pgmEnv.FpgaCatRecvInx;
    }
    */

    return ret;
}

void putFPGAEthercat(INT08U* buff, INT16U buff_size)
{
    if (buff_size <= 1492)
    {
        set_FPGA_EthCat_TxBuff_Len(0, (INT08U*)&buff[0], buff_size);
        set_FPGA_EthCat_Send_Size(buff_size);
        set_FPGA_EthCat_Send_Cmd(1);
        //m_TestStatus.St[DEBUG_STR_1]++;
    }
}

////////////////////////////////////////////////////////////////////////////////////

void testFpgaReadWrite(void)
{
    //	  INT16U i;
    //	  
    //	  m_TestStatus.St[0]++;
    //    m_TestStatus.St[1] = m_FpgaReg->ID;
    //    m_TestStatus.St[2] = m_FpgaReg->Version;
    //    
    //    m_FpgaReg->FpgaTest[0] = 0x12;
    //    m_FpgaReg->FpgaTest[1] = 0x34;
    //    m_FpgaReg->FpgaTest[2] = 0x56;
    //    m_FpgaReg->FpgaTest[3] = 0x78;
    //
    //    m_TestStatus.St[3] = m_FpgaReg->FpgaTest[0];
    //    m_TestStatus.St[4] = m_FpgaReg->FpgaTest[1];
    //    m_TestStatus.St[5] = m_FpgaReg->FpgaTest[2];
    //    m_TestStatus.St[6] = m_FpgaReg->FpgaTest[3];
    //
    //    m_TestStatus.St[7] = m_FpgaReg->EthNet.MacAddr[0];
    //    m_TestStatus.St[8] = m_FpgaReg->EthNet.MacAddr[1];
    //    m_TestStatus.St[9] = m_FpgaReg->EthNet.MacAddr[2];
    //    m_TestStatus.St[10] = m_FpgaReg->EthNet.MacAddr[3];
    //    m_TestStatus.St[11] = m_FpgaReg->EthNet.MacAddr[4];
    //    m_TestStatus.St[12] = m_FpgaReg->EthNet.MacAddr[5];
    //    m_TestStatus.St[13] = m_FpgaReg->EthNet.IpAddr[0];
    //    m_TestStatus.St[14] = m_FpgaReg->EthNet.IpAddr[1];
    //    m_TestStatus.St[15] = m_FpgaReg->EthNet.IpAddr[2];
    //    m_TestStatus.St[16] = m_FpgaReg->EthNet.IpAddr[3];
    //
    //    m_FpgaReg->EthNet.Send_Size = 0xABCD;
    //    m_TestStatus.St[17] = m_FpgaReg->EthNetReg[0xE];
    //    m_TestStatus.St[18] = m_FpgaReg->EthNetReg[0xF];
    //
    //    m_FpgaReg->PTO.Pulse_Low_Cnt  = 0x13579BDF;
    //
    //    m_TestStatus.St[19] = m_FpgaReg->PtoReg[0x0];
    //    m_TestStatus.St[20] = m_FpgaReg->PtoReg[0x1];
    //    m_TestStatus.St[21] = m_FpgaReg->PtoReg[0x2];
    //    m_TestStatus.St[22] = m_FpgaReg->PtoReg[0x3];
    //
    //    m_TestStatus.St[23] = m_FpgaReg->EthNet.Read_Buff_Num;
    //    m_TestStatus.St[24] = m_FpgaReg->EthNet.Recv_Buff_Num;

    //    m_FpgaNetTx->Data[0] = 0x01;
    //    m_FpgaNetTx->Data[1] = 0x02;
    //    m_FpgaNetTx->Data[2] = 0x03;
    //    m_FpgaNetTx->Data[3] = 0x04;
    // 
    //    m_FpgaCatTx->Data[0] = 0x05;
    //    m_FpgaCatTx->Data[1] = 0x06;
    //    m_FpgaCatTx->Data[2] = 0x07;
    //    m_FpgaCatTx->Data[3] = 0x08;
    // 
    //    m_TestStatus.St[23] = m_FpgaNetTx->Data[0];
    //    m_TestStatus.St[24] = m_FpgaNetTx->Data[1];
    //    m_TestStatus.St[25] = m_FpgaNetTx->Data[2];
    //    m_TestStatus.St[26] = m_FpgaNetTx->Data[3];
    //    m_TestStatus.St[27] = m_FpgaCatTx->Data[0];
    //    m_TestStatus.St[28] = m_FpgaCatTx->Data[1];
    //    m_TestStatus.St[29] = m_FpgaCatTx->Data[2];
    //    m_TestStatus.St[30] = m_FpgaCatTx->Data[3];
}


void EthPacketTestProcess(void)
{
    static INT32U chkTimer = 0;
    static INT08U mode = 0;

    switch (mode)
    {
    case  0:
        //      	        sendTestEthPacket();
        testFpgaReadWrite();
        //             	  m_TestStatus.St[10]++;
        chkTimer = m_pgmEnv.timer100us;
        mode = 1;
        break;
    case  1:
        if (m_TestStatus.Ctrl[0] < 1) m_TestStatus.Ctrl[0] = 1;

        if (getCalcTimer100us(chkTimer) >= m_TestStatus.Ctrl[0])  // 100 )   
        {
            chkTimer = m_pgmEnv.timer100us;
            mode = 0;
        }
        break;
    }
}

void FpgaManager(void)
{
    static INT32U s_chkTimer = 0;
    //static INT32U runTimer = 0;
    static INT08U s_mode = 0;
    INT08U fpga_id;
    INT08U fpga_ver;
    INT08U test_val = 1;
    INT08U test_val_w[4];
    INT08U test_val_r[4];
    INT08U i;

    switch (s_mode)
    {
    case  0:
        m_pgmEnv.FPGA_Reset_Flag = 0;

        s_chkTimer = m_pgmEnv.timer1ms;
        s_mode = 1;
        break;

    case  1:
        if (getCalcTimer1ms(s_chkTimer) >= 1000)
        {
			HAL_GPIO_WritePin(FPGA_RESET_GPIO_Port, FPGA_RESET_Pin, GPIO_PIN_RESET);
			s_chkTimer = m_pgmEnv.timer1ms;
			s_mode = 2;
        }
        break;
    case  2:
        if (getCalcTimer1ms(s_chkTimer) >= 3000)
        {
            HAL_GPIO_WritePin(FPGA_RESET_GPIO_Port, FPGA_RESET_Pin, GPIO_PIN_SET);

#if DEBUG_FPGA_MSG
            printf("[FPGA] Reset Release.\r\n");
#endif
            s_chkTimer = m_pgmEnv.timer1ms;
            s_mode = 3;
        }
        break;
    case  3:
        if (getCalcTimer1ms(s_chkTimer) >= 10)
        {
            fpga_id = m_FpgaReg->ID;
            fpga_ver = m_FpgaReg->Version;
#if DEBUG_FPGA_MSG
			printf("[FPGA] ID: %x Version: %x\r\n", fpga_id, fpga_ver);
#endif

            if ((fpga_id != 0xFF) && (fpga_ver != 0xFF))
            {
//                 m_TestStatus.St[DEBUG_STR_1] = fpga_id;
//                 m_TestStatus.St[DEBUG_STR_2] = fpga_ver;
//                 m_TestStatus.St[DEBUG_STR_3] = getCalcTimer1ms(runTimer);
                s_mode = 4;
            }
            s_chkTimer = m_pgmEnv.timer1ms;
        }
        break;
    case  4:
        if (getCalcTimer1ms(s_chkTimer) >= 10)
        {
            test_val += 4;
            for (i = 0; i < 4; i++)  test_val_w[i] = test_val + i;
            for (i = 0; i < 4; i++)  m_FpgaReg->FpgaTest[i] = test_val_w[i];
            for (i = 0; i < 4; i++)  test_val_r[i] = m_FpgaReg->FpgaTest[i];

            if ((test_val_w[0] == test_val_r[0])
                && (test_val_w[1] == test_val_r[1])
                && (test_val_w[2] == test_val_r[2])
                && (test_val_w[3] == test_val_r[3]))
            {
                m_pgmEnv.isFpgaRun = 1;

                m_pgmEnv.DownLinkInitFlag = 1;

                s_mode = 10;
            }
        }
        break;

    case 10:
        if (m_pgmEnv.FPGA_Reset_Flag == 1)
        {
            s_mode = 0;
        }
		//m_TestStatus.St[DEBUG_STR_5] = m_FpgaReg->EthCat.Status;
        break;
    }

    //m_TestStatus.St[DEBUG_STR_32] = mode;
}