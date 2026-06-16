
#ifndef _ethercatcoe_
#define _ethercatcoe_

#include <stdio.h>
#include <string.h>
#include <inttypes.h>


#define EC_MAX_OD_LIST   1024
#define EC_MAX_OE_LIST   256

struct __attribute__((__packed__)) Tag_ec_SDOt
{
	EC_mbxheader_t   MbxHeader;
	uint16          CANOpen;
	uint8           Command;
	uint16          Index;
	uint8           SubIndex;
	union
	{
		uint8   bdata[0x200];
		uint16  wdata[0x100];
		uint32  ldata[0x80];
	};
};
typedef struct Tag_ec_SDOt  EC_SDO_t;


struct __attribute__((__packed__)) Tag_ec_SDOservicet
{
	EC_mbxheader_t   MbxHeader;
	uint16          CANOpen;
	uint8           Opcode;
	uint8           Reserved;
	uint16          Fragments;
	union
	{
		uint8   bdata[0x200];
		uint16  wdata[0x100];
		uint32  ldata[0x80];
	};
};
typedef struct Tag_ec_SDOservicet  EC_SDOservice_t;

typedef struct
{
	uint16  Slave;
	uint16  Entries;
	uint16  Index[EC_MAX_OD_LIST];
	uint16  DataType[EC_MAX_OD_LIST];
	uint8   ObjectCode[EC_MAX_OD_LIST];
	uint8   MaxSub[EC_MAX_OD_LIST];
	char    Name[EC_MAX_OD_LIST][EC_MAX_NAME + 1];
} EC_ODlist_t;

typedef struct
{
	uint16 Entries;
	uint8  ValueInfo[EC_MAX_OE_LIST];
	uint16 DataType[EC_MAX_OE_LIST];
	uint16 BitLength[EC_MAX_OE_LIST];
	uint16 ObjAccess[EC_MAX_OE_LIST];
	char   Name[EC_MAX_OE_LIST][EC_MAX_NAME + 1];
} EC_OElist_t;

void EC_SDO_error(EC_Main_t *pEC_Main, uint16 slave, uint16 Index, uint8 SubIdx, int32 AbortCode);
int EC_SDO_Read(EC_Main_t *pEC_Main, uint16 slave, uint16 index, uint8 subindex, boolean CA, int *psize, void *p, int timeout);
int EC_SDO_Write(EC_Main_t *pEC_Main, uint16 slave, uint16 Index, uint8 SubIndex, boolean CA, int psize, void *p, int Timeout);

int EC_Read_PDOmap(EC_Main_t *pEC_Main, uint16 slave, int *Osize, int *Isize);
int EC_Read_PDOmap_CA(EC_Main_t *pEC_Main, uint16 slave, int Thread_n, int *Osize, int *Isize);
int EC_Read_ODlist(EC_Main_t *pEC_Main, uint16 slave, EC_ODlist_t *pODlist);
int EC_Read_ODdescription(EC_Main_t *pEC_Main, uint16 Item, EC_ODlist_t *pODlist);
int EC_Read_OEsingle(EC_Main_t *pEC_Main, uint16 Item, uint8 SubI, EC_ODlist_t *pODlist, EC_OElist_t *pOElist);

int EC_SDOread(uint16 slave, uint16 index, uint8 subindex, boolean CA, int* psize, void* p, int timeout);
int EC_SDOwrite(uint16 slave, uint16 Index, uint8 SubIndex, boolean CA, int psize, void* p, int Timeout);
int EC_ReadODlist(uint16 slave, EC_ODlist_t* pODlist);
int EC_ReadODdescription(uint16 Item, EC_ODlist_t* pODlist);
int EC_ReadOEsingle(uint16 Item, uint8 SubI, EC_ODlist_t* pODlist, EC_OElist_t* pOElist);
int EC_ReadOE(uint16 Item, EC_ODlist_t* pODlist, EC_OElist_t* pOElist);

#endif
