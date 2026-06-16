/**
  ******************************************************************************
  * @file           : fpga.h
  * @brief          : Header for user_define.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

#ifndef INC_FPGA_H_
#define INC_FPGA_H_

#include "main.h"
#include "type.h"
#include "User_Define.h"
#include "alarm.h"
#include "type.h"


extern INT08U get_FPGA_ID(void);
extern INT08U get_FPGA_Version(void);

extern void   set_FPGA_SSI_Send_Cmd(INT08U mode);
extern INT08U get_FPGA_SSI_Status(void);
extern INT08U get_FPGA_SSI_Send_Bit(void);
extern void   set_FPGA_SSI_Send_Bit(INT08U bit_cnt);
extern INT16U get_FPGA_SSI_Clk(void);
extern void set_FPGA_SSI_Clk(INT16U nClk);
extern INT32U get_FPGA_SSI_Read_Data(void);

extern INT32U get_FPGA_PTO_Pulse_Low_Count(void);
extern INT32U get_FPGA_PTO_Pulse_High_Count(void);
extern void   set_FPGA_PTO_Pulse_Low_Count(INT32U cnt);
extern void   set_FPGA_PTO_Pulse_High_Count(INT32U cnt);
//extern void   set_FPGA_PTO_Pulse_Count_Apply(void);
extern void   set_FPGA_PTO_Pulse_Count_Apply(INT08U);
extern void   set_FPGA_PTO_Pulse_Freq(INT32U freq);

extern void   set_FPGA_EthNet_MAC_Address(INT08U* addr);
extern void   set_FPGA_EthNet_IP_Address(INT08U* addr);
extern INT08U get_FPGA_EthNet_Recv_Buff_Sel(void);
extern void   set_FPGA_EthNet_Read_Buff_Sel(INT08U buff_sel);
extern void   set_FPGA_EthNet_Send_Buff_Sel(INT08U buff_sel);
extern INT08U get_FPGA_EthNet_RxBuff(INT16U addr);
extern void   get_FPGA_EthNet_RxBuff_Len(INT16U addr, INT08U* buff, INT16U len);
extern void   set_FPGA_EthNet_TxBuff(INT16U addr, INT08U data);
extern void   set_FPGA_EthNet_TxBuff_Len(INT16U addr, INT08U* buff, INT16U len);
extern void   set_FPGA_EthNet_Send_Size(INT16U len);
extern void   set_FPGA_EthNet_Send_Cmd(INT08U mode);
extern INT16U getFPGAEthernet(INT08U* buff, INT16U buff_size);
extern void   putFPGAEthernet(INT08U* buff, INT16U buff_size);

extern INT08U get_FPGA_EthCat_Status(void);
extern void   set_FPGA_EthCat_MAC_Address(INT08U* addr);
extern void   set_FPGA_EthCat_IP_Address(INT08U* addr);
extern INT08U get_FPGA_EthCat_Recv_Buff_Sel(void);
extern void   set_FPGA_EthCat_Read_Buff_Sel(INT08U buff_sel);
extern void   set_FPGA_EthCat_Send_Buff_Sel(INT08U buff_sel);
extern INT08U get_FPGA_EthCat_RxBuff(INT16U addr);
extern void   get_FPGA_EthCat_RxBuff_Len(INT16U addr, INT08U* buff, INT16U len);
extern void   set_FPGA_EthCat_TxBuff(INT16U addr, INT08U data);
extern void   set_FPGA_EthCat_TxBuff_Len(INT16U addr, INT08U* buff, INT16U len);
extern void   set_FPGA_EthCat_Send_Size(INT16U len);
extern void   set_FPGA_EthCat_Send_Cmd(INT08U mode);
extern INT16U getFPGAEthercat(INT08U* buff, INT16U buff_size);
extern void   putFPGAEthercat(INT08U* buff, INT16U buff_size);


extern void   FpgaManager(void);

#endif /* INC_FPGA_H_ */
