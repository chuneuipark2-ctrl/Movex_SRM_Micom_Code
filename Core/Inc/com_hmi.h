/*
 * com_hmi.h
 *
 *  Created on: Jun 15, 2022
 *      Author: ARTWARE
 */

#ifndef INC_COM_HMI_H_
#define INC_COM_HMI_H_

enum enumRS485_MODE {
	RS485_RX_MODE = 0,
	RS485_TX_MODE,
};

void RS485_Mode_Control(INT08U nFlag);
void RS422_Mode_Enable(void);

void rsComHandler_485(INT08U rsData);

void HMI_Com_Receive_Proc();
void HMI_Com_Transmit_Proc();

void Set_RS485_422_Mode(INT08U nMode);
void HMI_Com_Manager(void);

void HMI_DownLink_ModbusTCP_Manager();
#endif /* INC_COM_HMI_H_ */
