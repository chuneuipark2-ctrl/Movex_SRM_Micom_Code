
#ifndef _ECAT_COM_BASE_
#define _ECAT_COM_BASE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "type.h"

INT08U ecx_setupdatagram(INT08U com, INT16U ADP, INT16U ADO, INT16U length, INT08U* data);
//void ecx_adddatagram(INT08U Inx, INT08U Cmd, INT16U Adp, INT16U Ado, INT16U Len, INT08U* Data);
void ecx_adddatagram(INT08U Cmd, INT16U Adp, INT16U Ado, INT16U Len, INT08U* Data);

INT16U EC_MultiData_Process(int n, INT08U* pReadData, INT16U nDataSize, int timeout);

int ecx_NOP(uint16 ADP, uint16 ADO, uint16 length, void* data);
int ecx_BWR(uint16 ADP, uint16 ADO, uint16 length, void *data);
int ecx_BRD(uint16 ADP, uint16 ADO, uint16 length, void *data);
int ecx_APRD(uint16 ADP, uint16 ADO, uint16 length, void *data);
int ecx_ARMW(uint16 ADP, uint16 ADO, uint16 length, void *data);
int ecx_FRMW(uint16 ADP, uint16 ADO, uint16 length, void *data);
uint16 ecx_APRDw(uint16 ADP, uint16 ADO);
int ecx_FPRD(uint16 ADP, uint16 ADO, uint16 length, void *data);
uint16 ecx_FPRDw(uint16 ADP, uint16 ADO);
int ecx_APWRw(uint16 ADP, uint16 ADO, uint16 data);
int ecx_APWR(uint16 ADP, uint16 ADO, uint16 length, void *data);
int ecx_FPWRw(uint16 ADP, uint16 ADO, uint16 data);
int ecx_FPWR(uint16 ADP, uint16 ADO, uint16 length, void *data);
int ecx_LRW(uint32 LogAdr, uint16 length, void *data);
int ecx_LRW_OverLoad(uint32 LogAdr, uint16 length, void* DataOut, void* DataIn);
int ecx_LRD(uint32 LogAdr, uint16 length, void* data);
int ecx_LWR(uint32 LogAdr, uint16 length, void *data);
int ecx_LRWDC(uint32 LogAdr, uint16 length, void *data, uint16 DCrs, int64 *DCtime);

#endif
