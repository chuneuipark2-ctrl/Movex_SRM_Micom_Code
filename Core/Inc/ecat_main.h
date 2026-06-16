
#ifndef _ETHERCAT_MAIN_
#define _ETHERCAT_MAIN_

#include "type.h"
#include "ecat_type.h"

#define EC_MAX_ERR_LIST			(64)
#define EC_MAX_NAME				(40)
//#define EC_MAX_SLAVE			(200)
#define EC_MAX_SLAVE			(20)
#define EC_MAX_GROUP			(2)
#define EC_MAX_IO_SEGMENTS		(64)
#define EC_MAX_MBX				(1486)
#define EC_MAX_EEP_DO			(0x200)
#define EC_MAX_SM				(8)
#define EC_MAX_FMMU				(4)
//#define EC_MAXLEN_ADAPTERNAME	(128)
#define EC_MAX_MAPT				(1)


struct __attribute__((__packed__)) EC_fmmu
{
	uint32  LogStart;
	uint16  LogLength;
	uint8   LogStartbit;
	uint8   LogEndbit;
	uint16  PhysStart;
	uint8   PhysStartBit;
	uint8   FMMUtype;
	uint8   FMMUactive;
	uint8   unused1;
	uint16  unused2;
};
typedef struct EC_fmmu  ec_fmmu_t;


struct __attribute__((__packed__)) ec_sm
{
	uint16  StartAddr;
	uint16  SMlength;
	uint32  SMflags;
};
typedef struct ec_sm  ec_smt;

/*
struct __attribute__((__packed__)) ec_state_status
{
	uint16  State;
	uint16  Unused;
	uint16  ALstatuscode;
};
typedef struct ec_state_status  ec_state_status;
*/

//#define ECT_MBXPROT_AOE      0x0001
//#define ECT_MBXPROT_EOE      0x0002
//#define ECT_MBXPROT_FOE      0x0008
//#define ECT_MBXPROT_SOE      0x0010
//#define ECT_MBXPROT_VOE      0x0020

#define ECT_MBXPROT_COE      0x0004

//#define ECT_COEDET_SDO       0x01
//#define ECT_COEDET_SDOINFO   0x02
//#define ECT_COEDET_PDOASSIGN 0x04
//#define ECT_COEDET_PDOCONFIG 0x08
//#define ECT_COEDET_UPLOAD    0x10

#define ECT_COEDET_SDOCA     0x20

#define EC_SMENABLEMASK      0xfffeffff

typedef struct ECx_Main EC_Main_t;


typedef struct tag_ec_slave
{
	uint16           state;
	uint16           ALstatuscode;
	uint16           configadr;
	uint16           aliasadr;
	uint32           eep_man;
	uint32           eep_id;
	uint32           eep_rev;
	uint16           Itype;
	uint16           Dtype;
	uint16           Obits;
	uint32           Obytes;
	uint8            *outputs;
	uint8            Ostartbit;
	uint16           Ibits;
	uint32           Ibytes;
	uint8            *inputs;
	uint8            Istartbit;
	ec_smt           SM[EC_MAX_SM];
	uint8            SMtype[EC_MAX_SM];
	ec_fmmu_t         FMMU[EC_MAX_FMMU];
	uint8            FMMU0func;
	uint8            FMMU1func;
	uint8            FMMU2func;
	uint8            FMMU3func;
	uint16           mbx_l;
	uint16           mbx_wo;
	uint16           mbx_rl;
	uint16           mbx_ro;
	uint16           mbx_proto;
	uint8            mbx_cnt;
	boolean          hasdc;
	uint8            ptype;
	uint8            topology;
	uint8            activeports;
	uint8            consumedports;
	uint16           parent;
	uint8            parentport;
	uint8            entryport;
	int32            DCrtA;
	int32            DCrtB;
	int32            DCrtC;
	int32            DCrtD;
	int32            pdelay;
	uint16           DCnext;
	uint16           DCprevious;
	int32            DCcycle;
	int32            DCshift;
	uint8            DCactive;
	uint16           configindex;
	uint16           SIIindex;
	uint8            eep_8byte;
	uint8            eep_pdi;
	uint8            CoEdetails;
	uint8            FoEdetails;
	uint8            EoEdetails;
	uint8            SoEdetails;
	int16            Ebuscurrent;
	uint8            blockLRW;
	uint8            group;
	uint8            FMMUunused;
	boolean          islost;
	int(*PO2SOconfig)(uint16 slave);
	int(*PO2SOconfigx)(EC_Main_t * pEC_Main, uint16 slave);
	char             name[EC_MAX_NAME + 1];
} EC_Slave_t;

typedef struct tag_ec_group
{
	uint32           logstartaddr;
	uint32           Obytes;
	uint8            *outputs;
	uint32           Ibytes;
	uint8            *inputs;
	boolean          hasdc;
	uint16           DCnext;
	int16            Ebuscurrent;
	uint8            blockLRW;
	uint16           nsegments;
	uint16           Isegment;
	uint16           Ioffset;
	uint16           outputsWKC;
	uint16           inputsWKC;
	boolean          docheckstate;
	uint32           IOsegment[EC_MAX_IO_SEGMENTS];
} EC_group_t;

typedef struct tag_ec_eepromFMMU
{
	uint16  Startpos;
	uint8   nFMMU;
	uint8   FMMU0;
	uint8   FMMU1;
	uint8   FMMU2;
	uint8   FMMU3;
} EC_eepromFMMU_t;

typedef struct tag_ec_eepromSM
{
	uint16  Startpos;
	uint8   nSM;
	uint16  PhStart;
	uint16  Plength;
	uint8   Creg;
	uint8   Sreg;  
	uint8   Activate;
	uint8   PDIctrl;
} EC_eepromSM_t;


typedef struct ec_eepromPDO
{
	uint16  Startpos;
	uint16  Length;
	uint16  nPDO;
	uint16  Index[EC_MAX_EEP_DO];
	uint16  SyncM[EC_MAX_EEP_DO];
	uint16  BitSize[EC_MAX_EEP_DO];
	uint16  SMbitsize[EC_MAX_SM];
} EC_eepromPDO_t;

typedef uint8 EC_Mbx_buffer_t[EC_MAX_MBX + 1];

struct __attribute__((__packed__)) Tag_ec_mbxheader
{
	uint16  length;
	uint16  address;
	uint8   priority;
	uint8   mbxtype;
};
typedef struct Tag_ec_mbxheader  EC_mbxheader_t;


struct __attribute__((__packed__)) ec_alstatus
{
	uint16  alstatus;
	uint16  unused;
	uint16  alstatuscode;
};
typedef struct ec_alstatus  EC_Alstatus_t;

/*
struct __attribute__((__packed__)) tag_ec_idxstack
{
	uint8   pushed;
	uint8   pulled;
	uint8   idx[EC_MAXBUF];
	void    *data[EC_MAXBUF];
	uint16  length[EC_MAXBUF];
};
typedef struct tag_ec_idxstack  ec_idxstackT;
*/

struct __attribute__((__packed__)) tag_ec_ering
{
	int16     head;
	int16     tail;
	EC_Error_t Error[EC_MAX_ERR_LIST + 1];
};
typedef struct tag_ec_ering  EC_ering_t;

struct __attribute__((__packed__)) tag_ec_SMcommtype
{
	uint8   n;
	uint8   nu1;
	uint8   SMtype[EC_MAX_SM];
};
typedef struct tag_ec_SMcommtype  EC_SMcommtype_t;

struct __attribute__((__packed__)) tag_ec_PDOassign
{
	uint8   n;
	uint8   nu1;
	uint16  index[256];
};
typedef struct tag_ec_PDOassign  EC_PDOassign_t;

struct __attribute__((__packed__)) tag_ec_PDOdesc
{
	uint8   n;
	uint8   nu1;
	uint32  PDO[256];
};
typedef struct tag_ec_PDOdesc  EC_PDOdesc_t;

struct ECx_Main
{
	EC_Slave_t      *slave_list;
	int            *slavecount;
	int            maxslave;
	EC_group_t      *group_list;
	int            maxgroup;
	uint8          *esibuf;
	uint32         *esimap;
	uint16         esislave;
	EC_ering_t      *elist;
	boolean        *ecaterror;
	uint16         DCtO;
	uint16         DCl;
	int64          *DCtime;
	EC_SMcommtype_t *SMcommtype;
	EC_PDOassign_t  *PDOassign;
	EC_PDOdesc_t    *PDOdesc;
	EC_eepromSM_t   *eepSM;
	EC_eepromFMMU_t *eepFMMU;
	int(*FOEhook)(uint16 slave, int packetnumber, int datasize);
	int(*EOEhook)(EC_Main_t * pEC_Main, uint16 slave, void * eoembx);
	int            manualstatechange;

	uint8			DisconnectFlag;		//
	uint16			DisconnectCount;	//
};

/** delay in us for eeprom ready loop */
#define EC_LOCALDELAY  200

struct __attribute__((__packed__)) Tag_ec_eepromt
{
	uint16    comm;
	uint16    addr;
	uint16    d2;
};
typedef struct Tag_ec_eepromt  EC_eeprom_t;

struct __attribute__((__packed__)) Tag_ec_mbxerrort
{
	EC_mbxheader_t   MbxHeader;
	uint16          Type;
	uint16          Detail;
};
typedef struct Tag_ec_mbxerrort  EC_mbxerror_t;

struct __attribute__((__packed__)) Tag_ec_emcyt
{
	EC_mbxheader_t   MbxHeader;
	uint16          CANOpen;
	uint16          ErrorCode;
	uint8           ErrorReg;
	uint8           bData;
	uint16          w1, w2;
};
typedef struct Tag_ec_emcyt  ec_emcyt;

extern EC_Main_t     m_EC_Main;

#define EC_MAX_ERROR_NAME 127

typedef struct
{
	uint32        errorcode;
	char          errordescription[EC_MAX_ERROR_NAME + 1];
} ec_sdoerrorlist_t;

typedef struct
{
	uint16        ALstatuscode;
	char          ALstatuscodedescription[EC_MAX_ERROR_NAME + 1];
} ec_ALstatuscodelist_t;

typedef struct
{
	uint16        errorcode;
	char          errordescription[EC_MAX_ERROR_NAME + 1];
} ec_soeerrorlist_t;

typedef struct
{
	uint16              errorcode;
	char                errordescription[EC_MAX_ERROR_NAME + 1];
} ec_mbxerrorlist_t;



uint8	EC_Next_MailBox_Cnt(uint8 cnt);
void	EC_Clear_MailBox(EC_Mbx_buffer_t *Mbx);
void	EC_Push_Error(EC_Main_t* pEC_Main, const EC_Error_t *Ec);
boolean EC_Pop_Error(EC_Main_t* pEC_Main, EC_Error_t *Ec);
//boolean EC_Is_Error(EC_pEC_Main_t *pEC_Main);
void	EC_Packet_Error(EC_Main_t* pEC_Main, uint16 Slave, uint16 Index, uint8 SubIdx, uint16 ErrorCode);
uint8	EC_SII_Read(EC_Main_t* pEC_Main, uint16 slave, uint16 address);
int16	EC_SII_Find(EC_Main_t* pEC_Main, uint16 slave, uint16 cat);
void	EC_SII_String(EC_Main_t* pEC_Main, char *str, uint16 slave, uint16 Sn);
uint16	EC_SII_FMMU(EC_Main_t* pEC_Main, uint16 slave, EC_eepromFMMU_t* FMMU);
uint16	EC_SII_SM(EC_Main_t* pEC_Main, uint16 slave, EC_eepromSM_t* SM);
uint16	EC_SII_SM_Next(EC_Main_t* pEC_Main, uint16 slave, EC_eepromSM_t* SM, uint16 n);
int		EC_SII_PDO(EC_Main_t* pEC_Main, uint16 slave, EC_eepromPDO_t* PDO, uint8 t);
int		EC_Read_State_1(EC_Main_t* pEC_Main);

uint16	EC_State_Check_1(EC_Main_t* pEC_Main, uint16 slave, uint16 reqstate, uint32 timeout);
int		EC_MailBox_Empty(EC_Main_t* pEC_Main, uint16 slave, int timeout);
int		EC_MailBox_Send(EC_Main_t* pEC_Main, uint16 slave, EC_Mbx_buffer_t *mbx, int timeout);
int		EC_MailBox_Receive(EC_Main_t* pEC_Main, uint16 slave, EC_Mbx_buffer_t *mbx, int timeout);
void	EC_Esi_dump(EC_Main_t* pEC_Main, uint16 slave, uint8 *esibuf);
uint32	EC_Read_EEprom(EC_Main_t* pEC_Main, uint16 slave, uint16 eeproma, int timeout);
int		EC_EEpromToMaster(EC_Main_t* pEC_Main, uint16 slave);
int		EC_EEpromToPDI(EC_Main_t* pEC_Main, uint16 slave);
uint64	EC_Read_EEpromFP(EC_Main_t* pEC_Main, uint16 configadr, uint16 eeproma, int timeout);
void	EC_Read_EEprom1(EC_Main_t* pEC_Main, uint16 slave, uint16 eeproma);
uint32	EC_Read_EEprom2(EC_Main_t* pEC_Main, uint16 slave, int timeout);

const char* ec_sdoerror2string(uint32 sdoerrorcode);
char* ec_ALstatuscode2string(uint16 ALstatuscode);
char* ec_soeerror2string(uint16 errorcode);
char* ec_mbxerror2string(uint16 errorcode);
char* ecx_err2string(const EC_Error_t Ec);
char* ecx_elist2string(EC_Main_t* pEC_Main);

char* ec_elist2string(void);

void ECAT_Com_Process();
void ECAT_Manager(void);

void ECAT_TestManager(INT08U nRunFlag, INT08U* pTestSeq, INT08U* pResult);
void ECAT_TestManager_1();

#endif /* _EC_MAIN_H */
