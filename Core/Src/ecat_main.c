


#include "main.h"
#include "type.h"
#include "User_Define.h"
#include "fpga.h"
#include "alarm.h"
#include "dev_SRM.h"
#include "SRM_Parameter.h"

#include "ecat.h"

extern TIM_HandleTypeDef htim4;

static INT08U m_ProcessData_Flag = 0;

EncoderTxPDO m_Enx_TxPDO;
EncoderRxPDO m_Enx_RxPDO;

EncoderTxPDO_1 m_Enx_TxPDO_1;
EncoderRxPDO_1 m_Enx_RxPDO_1;

MX_EXT_TxPDO m_MX_EXT_TxPDO;
MX_EXT_RxPDO m_MX_EXT_RxPDO;

__attribute__((section(".dtcm_bss"))) EC_Slave_t					m_EC_Slave[EC_MAX_SLAVE];
int							m_EC_SlaveCount;
EC_group_t					m_EC_Group[EC_MAX_GROUP];
static uint8				m_EC_esibuf[EC_MAX_EEPROM_BUF];
static uint32				m_EC_esimap[EC_MAX_EEPROM_BITMAP];
static EC_ering_t			m_EC_Err_list;
static EC_SMcommtype_t		m_EC_SMcomm_type[EC_MAX_MAPT];
static EC_PDOassign_t		m_EC_PDOassign[EC_MAX_MAPT];
static EC_PDOdesc_t			m_EC_PDOdesc[EC_MAX_MAPT];
static EC_eepromSM_t		m_EC_SM;
static EC_eepromFMMU_t		m_EC_FMMU;
boolean						m_EcatError = FALSE;
int64						m_EC_DCtime;

EC_Main_t  m_EC_Main = {
	&m_EC_Slave[0],
	&m_EC_SlaveCount,
	EC_MAX_SLAVE,
	&m_EC_Group[0],
	EC_MAX_GROUP,
	&m_EC_esibuf[0],
	&m_EC_esimap[0],
	0,
	&m_EC_Err_list,
	&m_EcatError,
	0,
	0,
	&m_EC_DCtime,
	&m_EC_SMcomm_type[0],
	&m_EC_PDOassign[0],
	&m_EC_PDOdesc[0],
	&m_EC_SM,
	&m_EC_FMMU,
	NULL,
	NULL,
	0
};

//char IOmap[256];
char m_IOmap[1024];

EC_ODlist_t m_ODlist;
EC_OElist_t m_OElist;

// boolean printSDO = FALSE;
// boolean printMAP = FALSE;

boolean m_printSDO = FALSE;
boolean m_printMAP = FALSE;

char m_usdo[128];
char m_hstr[1024];

const ec_sdoerrorlist_t ec_sdoerrorlist[] = {
   {0x00000000, "No error" },
   {0x05030000, "Toggle bit not changed" },
   {0x05040000, "SDO protocol timeout" },
   {0x05040001, "Client/Server command specifier not valid or unknown" },
   {0x05040005, "Out of memory" },
   {0x06010000, "Unsupported access to an object" },
   {0x06010001, "Attempt to read to a write only object" },
   {0x06010002, "Attempt to write to a read only object" },
   {0x06010003, "Subindex can not be written, SI0 must be 0 for write access" },
   {0x06010004, "SDO Complete access not supported for variable length objects" },
   {0x06010005, "Object length exceeds mailbox size" },
   {0x06010006, "Object mapped to RxPDO, SDO download blocked" },
   {0x06020000, "The object does not exist in the object directory" },
   {0x06040041, "The object can not be mapped into the PDO" },
   {0x06040042, "The number and length of the objects to be mapped would exceed the PDO length" },
   {0x06040043, "General parameter incompatibility reason" },
   {0x06040047, "General internal incompatibility in the device" },
   {0x06060000, "Access failed due to a hardware error" },
   {0x06070010, "Data type does not match, length of service parameter does not match" },
   {0x06070012, "Data type does not match, length of service parameter too high" },
   {0x06070013, "Data type does not match, length of service parameter too low" },
   {0x06090011, "Subindex does not exist" },
   {0x06090030, "Value range of parameter exceeded (only for write access)" },
   {0x06090031, "Value of parameter written too high" },
   {0x06090032, "Value of parameter written too low" },
   {0x06090036, "Maximum value is less than minimum value" },
   {0x08000000, "General error" },
   {0x08000020, "Data cannot be transferred or stored to the application" },
   {0x08000021, "Data cannot be transferred or stored to the application because of local control" },
   {0x08000022, "Data cannot be transferred or stored to the application because of the present device state" },
   {0x08000023, "Object dictionary dynamic generation fails or no object dictionary is present" },
   {0xffffffff, "Unknown" }
};

const ec_ALstatuscodelist_t ec_ALstatuscodelist[] = {
   {0x0000 , "No error" },
   {0x0001 , "Unspecified error" },
   {0x0002 , "No memory" },
   {0x0011 , "Invalid requested state change" },
   {0x0012 , "Unknown requested state" },
   {0x0013 , "Bootstrap not supported" },
   {0x0014 , "No valid firmware" },
   {0x0015 , "Invalid mailbox configuration" },
   {0x0016 , "Invalid mailbox configuration" },
   {0x0017 , "Invalid sync manager configuration" },
   {0x0018 , "No valid inputs available" },
   {0x0019 , "No valid outputs" },
   {0x001A , "Synchronization error" },
   {0x001B , "Sync manager watchdog" },
   {0x001C , "Invalid sync Manager types" },
   {0x001D , "Invalid output configuration" },
   {0x001E , "Invalid input configuration" },
   {0x001F , "Invalid watchdog configuration" },
   {0x0020 , "Slave needs cold start" },
   {0x0021 , "Slave needs INIT" },
   {0x0022 , "Slave needs PREOP" },
   {0x0023 , "Slave needs SAFEOP" },
   {0x0024 , "Invalid input mapping" },
   {0x0025 , "Invalid output mapping" },
   {0x0026 , "Inconsistent settings" },
   {0x0027 , "Freerun not supported" },
   {0x0028 , "Synchronisation not supported" },
   {0x0029 , "Freerun needs 3buffer mode" },
   {0x002A , "Background watchdog" },
   {0x002B , "No valid Inputs and Outputs" },
   {0x002C , "Fatal sync error" },
   {0x002D , "No sync error" }, // was "Invalid Output FMMU Configuration"
   {0x002E , "Invalid input FMMU configuration" },
   {0x0030 , "Invalid DC SYNC configuration" },
   {0x0031 , "Invalid DC latch configuration" },
   {0x0032 , "PLL error" },
   {0x0033 , "DC sync IO error" },
   {0x0034 , "DC sync timeout error" },
   {0x0035 , "DC invalid sync cycle time" },
   {0x0036 , "DC invalid sync0 cycle time" },
   {0x0037 , "DC invalid sync1 cycle time" },
   {0x0041 , "MBX_AOE" },
   {0x0042 , "MBX_EOE" },
   {0x0043 , "MBX_COE" },
   {0x0044 , "MBX_FOE" },
   {0x0045 , "MBX_SOE" },
   {0x004F , "MBX_VOE" },
   {0x0050 , "EEPROM no access" },
   {0x0051 , "EEPROM error" },
   {0x0060 , "Slave restarted locally" },
   {0x0061 , "Device identification value updated" },
   {0x00f0 , "Application controller available" },
   {0xffff , "Unknown" }
};

const ec_soeerrorlist_t ec_soeerrorlist[] = {
   {0x0000, "No error" },
   {0x1001, "No IDN" },
   {0x1009, "Invalid access to element 1" },
   {0x2001, "No Name" },
   {0x2002, "Name transmission too short" },
   {0x2003, "Name transmission too long" },
   {0x2004, "Name cannot be changed (read only)" },
   {0x2005, "Name is write-protected at this time" },
   {0x3002, "Attribute transmission too short" },
   {0x3003, "Attribute transmission too long" },
   {0x3004, "Attribute cannot be changed (read only)" },
   {0x3005, "Attribute is write-protected at this time" },
   {0x4001, "No units" },
   {0x4002, "Unit transmission too short" },
   {0x4003, "Unit transmission too long" },
   {0x4004, "Unit cannot be changed (read only)" },
   {0x4005, "Unit is write-protected at this time" },
   {0x5001, "No minimum input value" },
   {0x5002, "Minimum input value transmission too short" },
   {0x5003, "Minimum input value transmission too long" },
   {0x5004, "Minimum input value cannot be changed (read only)" },
   {0x5005, "Minimum input value is write-protected at this time" },
   {0x6001, "No maximum input value" },
   {0x6002, "Maximum input value transmission too short" },
   {0x6003, "Maximum input value transmission too long" },
   {0x6004, "Maximum input value cannot be changed (read only)" },
   {0x6005, "Maximum input value is write-protected at this time" },
   {0x7002, "Operation data transmission too short" },
   {0x7003, "Operation data transmission too long" },
   {0x7004, "Operation data cannot be changed (read only)" },
   {0x7005, "Operation data is write-protected at this time (state)" },
   {0x7006, "Operation data is smaller than the minimum input value" },
   {0x7007, "Operation data is smaller than the maximum input value" },
   {0x7008, "Invalid operation data:Configured IDN will not be supported" },
   {0x7009, "Operation data write protected by a password" },
   {0x700A, "Operation data is write protected, it is configured cyclically" },
   {0x700B, "Invalid indirect addressing: (e.g., data container, list handling)" },
   {0x700C, "Operation data is write protected, due to other settings" },
   {0x700D, "Reserved" },
   {0x7010, "Procedure command already active" },
   {0x7011, "Procedure command not interruptible" },
   {0x7012, "Procedure command at this time not executable (state)" },
   {0x7013, "Procedure command not executable (invalid or false parameters)" },
   {0x7014, "No data state" },
   {0x8001, "No default value" },
   {0x8002, "Default value transmission too long" },
   {0x8004, "Default value cannot be changed, read only" },
   {0x800A, "Invalid drive number" },
   {0x800A, "General error" },
   {0x800A, "No element addressed" },
   {0xffff, "Unknown" }
};

const ec_mbxerrorlist_t ec_mbxerrorlist[] = {
   {0x0000, "No error" },
   {0x0001, "Syntax of 6 octet Mailbox Header is wrong" },
   {0x0002, "The mailbox protocol is not supported" },
   {0x0003, "Channel Field contains wrong value"},
   {0x0004, "The service is no supported"},
   {0x0005, "Invalid mailbox header"},
   {0x0006, "Length of received mailbox data is too short"},
   {0x0007, "No more memory in slave"},
   {0x0008, "The length of data is inconsistent"},
   {0xffff, "Unknown"}
};

char estring[EC_MAX_ERROR_NAME];

static void InitFPGAEtherCat_1(void)
{
	static INT08U MacAddr[6] = { 0x00, 0x0A, 0x1F, 0x00, 0x12, 0x76 };
	static INT08U IpAddr[4] = { 192, 168, 100, 17 };

	SetEthercatMacAddr_Func((INT08U*)&MacAddr[0]);
	SetEthercatIpAddr_Func((INT08U*)&IpAddr[0]);
}


void EC_Push_Error(EC_Main_t* pEC_Main, const EC_Error_t* Ec)
{
	pEC_Main->elist->Error[pEC_Main->elist->head] = *Ec;
	pEC_Main->elist->Error[pEC_Main->elist->head].Signal = TRUE;
	pEC_Main->elist->head++;
	if (pEC_Main->elist->head > EC_MAX_ERR_LIST)
	{
		pEC_Main->elist->head = 0;
	}
	if (pEC_Main->elist->head == pEC_Main->elist->tail)
	{
		pEC_Main->elist->tail++;
	}
	if (pEC_Main->elist->tail > EC_MAX_ERR_LIST)
	{
		pEC_Main->elist->tail = 0;
	}
	*(pEC_Main->ecaterror) = TRUE;
}

boolean EC_Pop_Error(EC_Main_t* pEC_Main, EC_Error_t* Ec)
{
	boolean notEmpty = (pEC_Main->elist->head != pEC_Main->elist->tail);

	*Ec = pEC_Main->elist->Error[pEC_Main->elist->tail];
	pEC_Main->elist->Error[pEC_Main->elist->tail].Signal = FALSE;
	if (notEmpty)
	{
		pEC_Main->elist->tail++;
		if (pEC_Main->elist->tail > EC_MAX_ERR_LIST)
		{
			pEC_Main->elist->tail = 0;
		}
	}
	else
	{
		*(pEC_Main->ecaterror) = FALSE;
	}
	return notEmpty;
}


/*
boolean EC_Is_Error(EC_pEC_Main_t* pEC_Main)
{
	return (pEC_Main->elist->head != pEC_Main->elist->tail);
}
*/


void EC_Packet_Error(EC_Main_t* pEC_Main, uint16 Slave, uint16 Index, uint8 SubIdx, uint16 ErrorCode)
{
	EC_Error_t nEc_Error;
	EC_time_t nTime;

	memset(&nEc_Error, 0, sizeof(nEc_Error));

	nTime.sec = 0;
	nTime.usec = 0;

	nEc_Error.Time = nTime;
	nEc_Error.Slave = Slave;
	nEc_Error.Index = Index;
	nEc_Error.SubIdx = SubIdx;
	*(pEC_Main->ecaterror) = TRUE;
	nEc_Error.Etype = EC_ERR_TYPE_PACKET_ERROR;
	nEc_Error.ErrorCode = ErrorCode;
	EC_Push_Error(pEC_Main, &nEc_Error);
}

static void EC_mbx_Error(EC_Main_t* pEC_Main, uint16 Slave, uint16 Detail)
{
	EC_Error_t nEc_Error;
	EC_time_t nTime;

	memset(&nEc_Error, 0, sizeof(nEc_Error));

	/*
	nTime.sec = m_pgmEnv.timer1ms / 1000;
	nTime.usec = m_pgmEnv.timer1ms % 1000;
	m_pgmEnv.SysTime_1ms = m_pgmEnv.timer1ms;
	*/
	nTime.sec = 0;
	nTime.usec = 0;

	nEc_Error.Time = nTime;
	nEc_Error.Slave = Slave;
	nEc_Error.Index = 0;
	nEc_Error.SubIdx = 0;
	nEc_Error.Etype = EC_ERR_TYPE_MBX_ERROR;
	nEc_Error.ErrorCode = Detail;
	EC_Push_Error(pEC_Main, &nEc_Error);
}


static void EC_mbx_emergency_error(EC_Main_t* pEC_Main, uint16 Slave, uint16 ErrorCode, uint16 ErrorReg, uint8 b1, uint16 w1, uint16 w2)
{
	EC_Error_t nEc_Error;
	EC_time_t nTime;

	memset(&nEc_Error, 0, sizeof(nEc_Error));

	/*
	Time.sec = m_pgmEnv.timer1ms / 1000;
	Time.usec = m_pgmEnv.timer1ms % 1000;
	m_pgmEnv.SysTime_1ms = m_pgmEnv.timer1ms;
	*/
	nTime.sec = 0;
	nTime.usec = 0;

	nEc_Error.Time = nTime;
	nEc_Error.Slave = Slave;
	nEc_Error.Index = 0;
	nEc_Error.SubIdx = 0;
	nEc_Error.Etype = EC_ERR_TYPE_EMERGENCY;
	nEc_Error.ErrorCode = ErrorCode;
	nEc_Error.ErrorReg = (uint8)ErrorReg;
	nEc_Error.b1 = b1;
	nEc_Error.w1 = w1;
	nEc_Error.w2 = w2;
	EC_Push_Error(pEC_Main, &nEc_Error);
}

uint8 EC_SII_Read(EC_Main_t* pEC_Main, uint16 slave, uint16 address)
{
	uint16 configadr, eadr;
	uint64 edat64;
	uint32 edat32;
	uint16 mapw, mapb;
	int lp, cnt;
	uint8 retval;

	retval = 0xff;
	if (slave != pEC_Main->esislave)
	{
		memset(pEC_Main->esimap, 0x00, EC_MAX_EEPROM_BITMAP * sizeof(uint32));
		pEC_Main->esislave = slave;
	}

	if (address < EC_MAX_EEPROM_BUF)
	{
		mapw = address >> 5;
		mapb = address - (mapw << 5);
		if (pEC_Main->esimap[mapw] & (uint32)(1 << mapb))
		{
			retval = pEC_Main->esibuf[address];
		}
		else
		{
			configadr = pEC_Main->slave_list[slave].configadr;
			EC_EEpromToMaster(pEC_Main, slave);
			eadr = address >> 1;
			edat64 = EC_Read_EEpromFP(pEC_Main, configadr, eadr, EC_TIMEOUT_EEPROM);

			if (pEC_Main->slave_list[slave].eep_8byte)
			{
				put_unaligned64(edat64, &(pEC_Main->esibuf[eadr << 1]));
				cnt = 8;
			}
			else
			{
				edat32 = (uint32)edat64;
				put_unaligned32(edat32, &(pEC_Main->esibuf[eadr << 1]));
				cnt = 4;
			}

			mapw = eadr >> 4;
			mapb = (eadr << 1) - (mapw << 5);
			for (lp = 0; lp < cnt; lp++)
			{
				pEC_Main->esimap[mapw] |= (1 << mapb);
				mapb++;
				if (mapb > 31)
				{
					mapb = 0;
					mapw++;
				}
			}
			retval = pEC_Main->esibuf[address];
		}
	}

	return retval;
}

int16 EC_SII_Find(EC_Main_t* pEC_Main, uint16 slave, uint16 cat)
{
	int16 nAddr;
	uint16 rVal;
	uint8 eectl = pEC_Main->slave_list[slave].eep_pdi;

	nAddr = ECT_SII_START << 1;
	rVal = EC_SII_Read(pEC_Main, slave, nAddr++);
	rVal += (EC_SII_Read(pEC_Main, slave, nAddr++) << 8);

	while ((rVal != cat) && (rVal != 0xffff))
	{
		rVal = EC_SII_Read(pEC_Main, slave, nAddr++);
		rVal += (EC_SII_Read(pEC_Main, slave, nAddr++) << 8);
		nAddr += rVal << 1;
		rVal = EC_SII_Read(pEC_Main, slave, nAddr++);
		rVal += (EC_SII_Read(pEC_Main, slave, nAddr++) << 8);
	}
	if (rVal != cat)
	{
		nAddr = 0;
	}
	if (eectl)
	{
		EC_EEpromToPDI(pEC_Main, slave);
	}

	return nAddr;
}

void EC_SII_String(EC_Main_t* pEC_Main, char* str, uint16 slave, uint16 Sn)
{
	uint16 a, i, j, l, n, ba;
	char* ptr;
	uint8 eectl = pEC_Main->slave_list[slave].eep_pdi;

	ptr = str;
	a = EC_SII_Find(pEC_Main, slave, ECT_SII_STRING);
	if (a > 0)
	{
		ba = a + 2;
		n = EC_SII_Read(pEC_Main, slave, ba++);
		if (Sn <= n)
		{
			for (i = 1; i <= Sn; i++)
			{
				l = EC_SII_Read(pEC_Main, slave, ba++);
				if (i < Sn)
				{
					ba += l;
				}
				else
				{
					ptr = str;
					for (j = 1; j <= l; j++)
					{
						if (j <= EC_MAX_NAME)
						{
							*ptr = (char)EC_SII_Read(pEC_Main, slave, ba++);
							ptr++;
						}
						else
						{
							ba++;
						}
					}
				}
			}
			*ptr = 0;
		}
		else
		{
			ptr = str;
			*ptr = 0;
		}
	}

	if (eectl)
	{
		EC_EEpromToPDI(pEC_Main, slave);
	}
}

uint16 EC_SII_FMMU(EC_Main_t* pEC_Main, uint16 slave, EC_eepromFMMU_t* FMMU)
{
	uint16  a;
	uint8 eectl = pEC_Main->slave_list[slave].eep_pdi;

	FMMU->nFMMU = 0;
	FMMU->FMMU0 = 0;
	FMMU->FMMU1 = 0;
	FMMU->FMMU2 = 0;
	FMMU->FMMU3 = 0;
	FMMU->Startpos = EC_SII_Find(pEC_Main, slave, ECT_SII_FMMU);

	if (FMMU->Startpos > 0)
	{
		a = FMMU->Startpos;
		FMMU->nFMMU = EC_SII_Read(pEC_Main, slave, a++);
		FMMU->nFMMU += (EC_SII_Read(pEC_Main, slave, a++) << 8);
		FMMU->nFMMU *= 2;
		FMMU->FMMU0 = EC_SII_Read(pEC_Main, slave, a++);
		FMMU->FMMU1 = EC_SII_Read(pEC_Main, slave, a++);
		if (FMMU->nFMMU > 2)
		{
			FMMU->FMMU2 = EC_SII_Read(pEC_Main, slave, a++);
			FMMU->FMMU3 = EC_SII_Read(pEC_Main, slave, a++);
		}
	}

	if (eectl)
	{
		EC_EEpromToPDI(pEC_Main, slave);
	}

	return FMMU->nFMMU;
}

uint16 EC_SII_SM(EC_Main_t* pEC_Main, uint16 slave, EC_eepromSM_t* SM)
{
	uint16 a, w;
	uint8 eectl = pEC_Main->slave_list[slave].eep_pdi;

	SM->nSM = 0;
	SM->Startpos = EC_SII_Find(pEC_Main, slave, ECT_SII_SM);
	if (SM->Startpos > 0)
	{
		a = SM->Startpos;
		w = EC_SII_Read(pEC_Main, slave, a++);
		w += (EC_SII_Read(pEC_Main, slave, a++) << 8);
		SM->nSM = (w / 4);
		SM->PhStart = EC_SII_Read(pEC_Main, slave, a++);
		SM->PhStart += (EC_SII_Read(pEC_Main, slave, a++) << 8);
		SM->Plength = EC_SII_Read(pEC_Main, slave, a++);
		SM->Plength += (EC_SII_Read(pEC_Main, slave, a++) << 8);
		SM->Creg = EC_SII_Read(pEC_Main, slave, a++);
		SM->Sreg = EC_SII_Read(pEC_Main, slave, a++);
		SM->Activate = EC_SII_Read(pEC_Main, slave, a++);
		SM->PDIctrl = EC_SII_Read(pEC_Main, slave, a++);
	}

	if (eectl)
	{
		EC_EEpromToPDI(pEC_Main, slave);
	}

	return SM->nSM;
}

uint16 EC_SII_SM_Next(EC_Main_t* pEC_Main, uint16 slave, EC_eepromSM_t* SM, uint16 n)
{
	uint16 a;
	uint16 retVal = 0;
	uint8 eectl = pEC_Main->slave_list[slave].eep_pdi;

	if (n < SM->nSM)
	{
		a = SM->Startpos + 2 + (n * 8);
		SM->PhStart = EC_SII_Read(pEC_Main, slave, a++);
		SM->PhStart += (EC_SII_Read(pEC_Main, slave, a++) << 8);
		SM->Plength = EC_SII_Read(pEC_Main, slave, a++);
		SM->Plength += (EC_SII_Read(pEC_Main, slave, a++) << 8);
		SM->Creg = EC_SII_Read(pEC_Main, slave, a++);
		SM->Sreg = EC_SII_Read(pEC_Main, slave, a++);
		SM->Activate = EC_SII_Read(pEC_Main, slave, a++);
		SM->PDIctrl = EC_SII_Read(pEC_Main, slave, a++);
		retVal = 1;
	}

	if (eectl)
	{
		EC_EEpromToPDI(pEC_Main, slave);
	}

	return retVal;
}

int EC_SII_PDO(EC_Main_t* pEC_Main, uint16 slave, EC_eepromPDO_t* PDO, uint8 t)
{
	uint16 a, w, c, e, er, Size;
	uint8 eectl = pEC_Main->slave_list[slave].eep_pdi;

	Size = 0;
	PDO->nPDO = 0;
	PDO->Length = 0;
	PDO->Index[1] = 0;
	for (c = 0; c < EC_MAX_SM; c++) PDO->SMbitsize[c] = 0;

	if (t > 1)	t = 1;

	PDO->Startpos = EC_SII_Find(pEC_Main, slave, ECT_SII_PDO + t);
	if (PDO->Startpos > 0)
	{
		a = PDO->Startpos;
		w = EC_SII_Read(pEC_Main, slave, a++);
		w += (EC_SII_Read(pEC_Main, slave, a++) << 8);
		PDO->Length = w;
		c = 1;
		do
		{
			PDO->nPDO++;
			PDO->Index[PDO->nPDO] = EC_SII_Read(pEC_Main, slave, a++);
			PDO->Index[PDO->nPDO] += (EC_SII_Read(pEC_Main, slave, a++) << 8);
			PDO->BitSize[PDO->nPDO] = 0;
			c++;
			e = EC_SII_Read(pEC_Main, slave, a++);
			PDO->SyncM[PDO->nPDO] = EC_SII_Read(pEC_Main, slave, a++);
			a += 4;
			c += 2;
			if (PDO->SyncM[PDO->nPDO] < EC_MAX_SM)
			{
				for (er = 1; er <= e; er++)
				{
					c += 4;
					a += 5;
					PDO->BitSize[PDO->nPDO] += EC_SII_Read(pEC_Main, slave, a++);
					a += 2;
				}
				PDO->SMbitsize[PDO->SyncM[PDO->nPDO]] += PDO->BitSize[PDO->nPDO];
				Size += PDO->BitSize[PDO->nPDO];
				c++;
			}
			else
			{
				c += 4 * e;
				a += 8 * e;
				c++;
			}

			if (PDO->nPDO >= (EC_MAX_EEP_DO - 1))
			{
				c = PDO->Length;
			}
		} while (c < PDO->Length);
	}

	if (eectl)
	{
		EC_EEpromToPDI(pEC_Main, slave);
	}

	return (Size);
}

#define MAX_FPRD_MULTI 50

int EC_FPRD_multi(int n, uint16* configlst, EC_Alstatus_t* slstatlst, int timeout)
{
	int wkc = 0;
	int slcnt = 0;

	ecx_setupdatagram(EC_CMD_FPRD, *(configlst + slcnt), ECT_REG_ALSTAT,
		sizeof(EC_Alstatus_t), (INT08U*)(slstatlst + slcnt));

	for (slcnt = 1; slcnt < n; slcnt++)
	{
		ecx_adddatagram(EC_CMD_FPRD, *(configlst + slcnt), ECT_REG_ALSTAT,
			sizeof(EC_Alstatus_t), (INT08U*)(slstatlst + slcnt));
	}

	wkc = EC_MultiData_Process(n, (INT08U*)slstatlst, sizeof(EC_Alstatus_t), timeout);
	asm volatile("NOP");

	return wkc;
}

/*
int EC_Write_State(EC_pEC_Main_t* pEC_Main, uint16 slave)
{
	int ret;
	uint16 configadr, slstate;

	if (slave == 0)
	{
		slstate = htoes(pEC_Main->slavelist[slave].state);
		ret = ecx_BWR(0, ECT_REG_ALCTL, sizeof(slstate), &slstate);
	}
	else
	{
		configadr = pEC_Main->slavelist[slave].configadr;

		ret = ecx_FPWRw(configadr, ECT_REG_ALCTL, htoes(pEC_Main->slavelist[slave].state));
	}
	return ret;
}
*/

int EC_Read_State_1(EC_Main_t* pEC_Main)
{
	uint16 slave, fslave, lslave, configadr, lowest, rval, bitwisestate;
	EC_Alstatus_t sl[MAX_FPRD_MULTI];
	uint16 slca[MAX_FPRD_MULTI];
	boolean noerrorflag, allslavessamestate;
	boolean allslavespresent = FALSE;
	int wkc;

	rval = 0;
	wkc = ecx_BRD(0, ECT_REG_ALSTAT, sizeof(rval), &rval);

	if (wkc >= *(pEC_Main->slavecount))
	{
		allslavespresent = TRUE;
	}

	rval = etohs(rval);
	bitwisestate = (rval & 0x0f);

	if ((rval & EC_STATE_ERROR) == 0)
	{
		noerrorflag = TRUE;
		pEC_Main->slave_list[0].ALstatuscode = 0;
	}
	else
	{
		//++m_TestStatus.St[DEBUG_STR_10];
		noerrorflag = FALSE;
	}

	switch (bitwisestate)
	{
	case EC_STATE_INIT:
	case EC_STATE_PRE_OP:
	case EC_STATE_BOOT:
	case EC_STATE_SAFE_OP:
	case EC_STATE_OPERATIONAL:
		allslavessamestate = TRUE;
		pEC_Main->slave_list[0].state = bitwisestate;
		break;
	default:
		allslavessamestate = FALSE;
		//++m_TestStatus.St[DEBUG_STR_11];
		break;
	}

	if (noerrorflag && allslavessamestate && allslavespresent)
	{
		for (slave = 1; slave <= *(pEC_Main->slavecount); slave++)
		{
			pEC_Main->slave_list[slave].ALstatuscode = 0x0000;
			pEC_Main->slave_list[slave].state = bitwisestate;
		}

		//++m_TestStatus.St[DEBUG_STR_9];
		lowest = bitwisestate;
	}
	else
	{
		pEC_Main->slave_list[0].ALstatuscode = 0;
		lowest = 0xff;
		fslave = 1;

		do
		{
			lslave = *(pEC_Main->slavecount);
			if ((lslave - fslave) >= MAX_FPRD_MULTI)
			{
				lslave = fslave + MAX_FPRD_MULTI - 1;
			}

			for (slave = fslave; slave <= lslave; slave++)
			{
				const EC_Alstatus_t zero = { 0, 0, 0 };

				configadr = pEC_Main->slave_list[slave].configadr;
				slca[slave - fslave] = configadr;
				sl[slave - fslave] = zero;
			}

			wkc = EC_FPRD_multi((lslave - fslave) + 1, &(slca[0]), &(sl[0]), EC_TIMEOUT_RETRY3);

#if DEBUG_ETHERCAT_MSG
			/*
			printf("[ETHERCAT] %d FPRD Slave:%d, configadr:0x%04x wkc:%d\r\n",
				s_TestCount, (lslave - fslave) + 1, slca[0], wkc);
				*/
#endif
			if (wkc > 0)
			{
				for (slave = fslave; slave <= lslave; slave++)
				{
					configadr = pEC_Main->slave_list[slave].configadr;
					rval = etohs(sl[slave - fslave].alstatus);
					pEC_Main->slave_list[slave].ALstatuscode = etohs(sl[slave - fslave].alstatuscode);
					if ((rval & 0xf) < lowest)
					{
						lowest = (rval & 0xf);
					}
					pEC_Main->slave_list[slave].state = rval;
					pEC_Main->slave_list[0].ALstatuscode |= pEC_Main->slave_list[slave].ALstatuscode;

#if DEBUG_ETHERCAT_MSG
					/*
					printf("[ETHERCAT] Slave:%d, configadr:0x%04x rval:0x%x, ALstatuscode:%x lowest:%x\r\n",
						slave, configadr, rval, pEC_Main->slavelist[slave].ALstatuscode, lowest);
						*/
#endif
				}
			}
			else
			{
				//++m_TestStatus.St[DEBUG_STR_14];
			}

			fslave = lslave + 1;
		} while (lslave < *(pEC_Main->slavecount));

		pEC_Main->slave_list[0].state = lowest;

		//++m_TestStatus.St[DEBUG_STR_13];
	}

	return lowest;
}


uint16 EC_State_Check_1(EC_Main_t* pEC_Main, uint16 slave, uint16 reqstate, uint32 timeout)
{
	uint16 nConfigadr = 0, nState = 0, nRval = 0;
	EC_Alstatus_t slstat;
	static INT32U s_Timer = 0;

	if (slave > *(pEC_Main->slavecount))
	{
		return 0;
	}

	//s_Timer = m_pgmEnv.timer1ms;
	s_Timer = m_pgmEnv.timer100us;

	nConfigadr = pEC_Main->slave_list[slave].configadr;
	do
	{
		if (slave < 1)
		{
			nRval = 0;
			ecx_BRD(0, ECT_REG_ALSTAT, sizeof(nRval), &nRval);
			nRval = etohs(nRval);
		}
		else
		{
			slstat.alstatus = 0;
			slstat.alstatuscode = 0;
			ecx_FPRD(nConfigadr, ECT_REG_ALSTAT, sizeof(slstat), &slstat);
			nRval = etohs(slstat.alstatus);
			pEC_Main->slave_list[slave].ALstatuscode = etohs(slstat.alstatuscode);
		}

		nState = nRval & 0x000f;
		if (nState != reqstate)
		{
			uSleep_ms(1000);
		}
	} while ((nState != reqstate) && (!((getCalcTimer100us(s_Timer) > timeout))));

	pEC_Main->slave_list[slave].state = nRval;

	return nState;
}

uint8 EC_Next_MailBox_Cnt(uint8 cnt)
{
	cnt++;
	if (cnt > 7)
	{
		cnt = 1;
	}

	return cnt;
}

void EC_Clear_MailBox(EC_Mbx_buffer_t* Mbx)
{
	memset(Mbx, 0x00, EC_MAX_MBX);
}


int EC_MailBox_Empty(EC_Main_t* pEC_Main, uint16 slave, int timeout)
{
	uint16 configadr;
	uint8 SMstat;
	int wkc;
	static INT32U s_Timer = 0;

	s_Timer = m_pgmEnv.timer100us;
	configadr = pEC_Main->slave_list[slave].configadr;
	do
	{
		SMstat = 0;
		wkc = ecx_FPRD(configadr, ECT_REG_SM0STAT, sizeof(SMstat), &SMstat);
		SMstat = etohs(SMstat);
		if (((SMstat & 0x08) != 0) && (timeout > EC_LOCALDELAY))
		{
			uSleep_ms(EC_LOCALDELAY);
		}
	} while (((wkc <= 0) || ((SMstat & 0x08) != 0)) && (!((getCalcTimer100us(s_Timer) > timeout))));

	if ((wkc > 0) && ((SMstat & 0x08) == 0))
	{
		return 1;
	}

	return 0;
}

int EC_MailBox_Send(EC_Main_t* pEC_Main, uint16 slave, EC_Mbx_buffer_t* mbx, int timeout)
{
	uint16 mbxwo, mbxl, configadr;
	int wkc;

	wkc = 0;
	configadr = pEC_Main->slave_list[slave].configadr;
	mbxl = pEC_Main->slave_list[slave].mbx_l;
	if ((mbxl > 0) && (mbxl <= EC_MAX_MBX))
	{
		if (EC_MailBox_Empty(pEC_Main, slave, timeout))
		{
			mbxwo = pEC_Main->slave_list[slave].mbx_wo;
			wkc = ecx_FPWR(configadr, mbxwo, mbxl, mbx);
		}
		else
		{
			wkc = 0;
		}
	}

	return wkc;
}

int EC_MailBox_Receive(EC_Main_t* pEC_Main, uint16 slave, EC_Mbx_buffer_t* mbx, int timeout)
{
	uint16 mbxro, mbxl, configadr;
	int wkc = 0;
	int wkc2;
	uint16 SMstat;
	uint8 SMcontr;
	EC_mbxheader_t* mbxh;
	ec_emcyt* EMp;
	EC_mbxerror_t* MBXEp;
	static INT32U s_Timer = 0;

	configadr = pEC_Main->slave_list[slave].configadr;
	mbxl = pEC_Main->slave_list[slave].mbx_rl;
	if ((mbxl > 0) && (mbxl <= EC_MAX_MBX))
	{
		s_Timer = m_pgmEnv.timer100us;
		wkc = 0;
		do
		{
			SMstat = 0;
			wkc = ecx_FPRD(configadr, ECT_REG_SM1STAT, sizeof(SMstat), &SMstat);
			SMstat = etohs(SMstat);
			if (((SMstat & 0x08) == 0) && (timeout > EC_LOCALDELAY))
			{
				uSleep_ms(EC_LOCALDELAY);
			}
		} while (((wkc <= 0) || ((SMstat & 0x08) == 0)) && (!((getCalcTimer100us(s_Timer) > timeout))));

		if ((wkc > 0) && ((SMstat & 0x08) > 0))
		{
			mbxro = pEC_Main->slave_list[slave].mbx_ro;
			do
			{
				mbxh = (EC_mbxheader_t*)mbx;

				wkc = ecx_FPRD(configadr, mbxro, mbxl, mbx);
				if ((wkc > 0) && ((mbxh->mbxtype & 0x0f) == 0x00))
				{
					MBXEp = (EC_mbxerror_t*)mbx;
					EC_mbx_Error(pEC_Main, slave, etohs(MBXEp->Detail));
					wkc = 0;
				}
				else if ((wkc > 0)\
					&& ((mbxh->mbxtype & 0x0f) == ECT_MBXT_COE))
				{
					EMp = (ec_emcyt*)mbx;
					if ((etohs(EMp->CANOpen) >> 12) == 0x01)
					{
						EC_mbx_emergency_error(pEC_Main, slave, etohs(EMp->ErrorCode), EMp->ErrorReg,
							EMp->bData, etohs(EMp->w1), etohs(EMp->w2));
						wkc = 0;
					}
				}
				else
				{
					if (wkc <= 0)
					{
						SMstat ^= 0x0200;
						SMstat = htoes(SMstat);
						wkc2 = ecx_FPWR(configadr, ECT_REG_SM1STAT, sizeof(SMstat), &SMstat);
						SMstat = etohs(SMstat);
						do
						{
							wkc2 = ecx_FPRD(configadr, ECT_REG_SM1CONTR, sizeof(SMcontr), &SMcontr);
						} while (((wkc2 <= 0) \
							|| ((SMcontr & 0x02) != (HI_BYTE(SMstat) & 0x02))) \
							&& (!((getCalcTimer100us(s_Timer) > timeout))));
						do
						{
							wkc2 = ecx_FPRD(configadr, ECT_REG_SM1STAT, sizeof(SMstat), &SMstat);
							SMstat = etohs(SMstat);
							if (((SMstat & 0x08) == 0) && (timeout > EC_LOCALDELAY))
							{
								uSleep_ms(EC_LOCALDELAY);
							}
						} while (((wkc2 <= 0) \
							|| ((SMstat & 0x08) == 0)) \
							&& (!((getCalcTimer100us(s_Timer) > timeout))));
					}
				}
			} while ((wkc <= 0) && (!((getCalcTimer100us(s_Timer) > timeout))));
		}
		else
		{
			if (wkc > 0)
				wkc = EC_TIMEOUT;
		}
	}

	return wkc;
}


void EC_Esi_dump(EC_Main_t* pEC_Main, uint16 slave, uint8* esibuf)
{
	int address, incr;
	uint16 configadr;
	uint64* p64;
	uint16* p16;
	uint64 edat;
	uint8 eectl = pEC_Main->slave_list[slave].eep_pdi;

	EC_EEpromToMaster(pEC_Main, slave);
	configadr = pEC_Main->slave_list[slave].configadr;
	address = ECT_SII_START;
	p16 = (uint16*)esibuf;
	if (pEC_Main->slave_list[slave].eep_8byte)
	{
		incr = 4;
	}
	else
	{
		incr = 2;
	}
	do
	{
		edat = EC_Read_EEpromFP(pEC_Main, configadr, address, EC_TIMEOUT_EEPROM);
		p64 = (uint64*)p16;
		*p64 = edat;
		p16 += incr;
		address += incr;
	} while ((address <= (EC_MAX_EEPROM_BUF >> 1)) && ((uint32)edat != 0xffffffff));

	if (eectl)
	{
		EC_EEpromToPDI(pEC_Main, slave);
	}
}

uint32 EC_Read_EEprom(EC_Main_t* pEC_Main, uint16 slave, uint16 eeproma, int timeout)
{
	uint16 configadr;

	EC_EEpromToMaster(pEC_Main, slave);
	configadr = pEC_Main->slave_list[slave].configadr;

	return ((uint32)EC_Read_EEpromFP(pEC_Main, configadr, eeproma, timeout));
}

int EC_EEpromToMaster(EC_Main_t* pEC_Main, uint16 slave)
{
	int wkc = 1, cnt = 0;
	uint16 configadr;
	uint8 eepctl;

	if (pEC_Main->slave_list[slave].eep_pdi)
	{
		configadr = pEC_Main->slave_list[slave].configadr;
		eepctl = 2;
		do
		{
			wkc = ecx_FPWR(configadr, ECT_REG_EEPCFG, sizeof(eepctl), &eepctl);
		} while ((wkc <= 0) && (cnt++ < EC_DEFAULT_RETRIES));

		eepctl = 0;
		cnt = 0;
		do
		{
			wkc = ecx_FPWR(configadr, ECT_REG_EEPCFG, sizeof(eepctl), &eepctl);
		} while ((wkc <= 0) && (cnt++ < EC_DEFAULT_RETRIES));
		pEC_Main->slave_list[slave].eep_pdi = 0;
	}

	return wkc;
}

int EC_EEpromToPDI(EC_Main_t* pEC_Main, uint16 slave)
{
	int wkc = 1, cnt = 0;
	uint16 configadr;
	uint8 eepctl;

	if (!pEC_Main->slave_list[slave].eep_pdi)
	{
		configadr = pEC_Main->slave_list[slave].configadr;
		eepctl = 1;
		do
		{
			wkc = ecx_FPWR(configadr, ECT_REG_EEPCFG, sizeof(eepctl), &eepctl);
		} while ((wkc <= 0) && (cnt++ < EC_DEFAULT_RETRIES));
		pEC_Main->slave_list[slave].eep_pdi = 1;
	}

	return wkc;
}


uint16 ecx_eeprom_waitnotbusyFP(EC_Main_t* pEC_Main, uint16 configadr, uint16* estat, int timeout)
{
	static INT32U Timer = 0;
	int wkc, retval = 0;

	Timer = m_pgmEnv.timer1ms;
	do
	{
		*estat = 0;
		wkc = ecx_FPRD(configadr, ECT_REG_EEPSTAT, sizeof(*estat), estat);
		*estat = etohs(*estat);
	} while (((wkc <= 0) || ((*estat & EC_ESTAT_BUSY) > 0)) && (!((getCalcTimer1ms(Timer) > timeout)))); /* wait for eeprom ready */

	if ((*estat & EC_ESTAT_BUSY) == 0)
	{
		retval = 1;
	}

	return retval;
}

uint64 EC_Read_EEpromFP(EC_Main_t* pEC_Main, uint16 configadr, uint16 eeproma, int timeout)
{
	uint16 estat;
	uint32 edat32;
	uint64 edat64;
	EC_eeprom_t ed;
	int wkc, cnt, nackcnt = 0;

	edat64 = 0;
	edat32 = 0;
	if (ecx_eeprom_waitnotbusyFP(pEC_Main, configadr, &estat, timeout))
	{
		if (estat & EC_ESTAT_EMASK)
		{
			estat = htoes(EC_ECMD_NOP);
			wkc = ecx_FPWR(configadr, ECT_REG_EEPCTL, sizeof(estat), &estat);
		}

		do
		{
			ed.comm = htoes(EC_ECMD_READ);
			ed.addr = htoes(eeproma);
			ed.d2 = 0x0000;
			cnt = 0;
			do
			{
				wkc = ecx_FPWR(configadr, ECT_REG_EEPCTL, sizeof(ed), &ed);
			} while ((wkc <= 0) && (cnt++ < EC_DEFAULT_RETRIES));
			if (wkc)
			{
				uSleep_ms(EC_LOCALDELAY);
				estat = 0x0000;
				if (ecx_eeprom_waitnotbusyFP(pEC_Main, configadr, &estat, timeout))
				{
					if (estat & EC_ESTAT_NACK)
					{
						nackcnt++;
						uSleep_ms(EC_LOCALDELAY * 5);
					}
					else
					{
						nackcnt = 0;
						if (estat & EC_ESTAT_R64)
						{
							cnt = 0;
							do
							{
								wkc = ecx_FPRD(configadr, ECT_REG_EEPDAT, sizeof(edat64), &edat64);
							} while ((wkc <= 0) && (cnt++ < EC_DEFAULT_RETRIES));
						}
						else
						{
							cnt = 0;
							do
							{
								wkc = ecx_FPRD(configadr, ECT_REG_EEPDAT, sizeof(edat32), &edat32);
							} while ((wkc <= 0) && (cnt++ < EC_DEFAULT_RETRIES));
							edat64 = (uint64)edat32;
						}
					}
				}
			}
		} while ((nackcnt > 0) && (nackcnt < 3));
	}

	return edat64;
}

void EC_Read_EEprom1(EC_Main_t* pEC_Main, uint16 slave, uint16 eeproma)
{
	uint16 configadr, estat;
	EC_eeprom_t ed;
	int wkc, cnt = 0;

	EC_EEpromToMaster(pEC_Main, slave);
	configadr = pEC_Main->slave_list[slave].configadr;
	if (ecx_eeprom_waitnotbusyFP(pEC_Main, configadr, &estat, EC_TIMEOUT_EEPROM))
	{
		if (estat & EC_ESTAT_EMASK)
		{
			estat = htoes(EC_ECMD_NOP);
			wkc = ecx_FPWR(configadr, ECT_REG_EEPCTL, sizeof(estat), &estat);
		}

		ed.comm = htoes(EC_ECMD_READ);
		ed.addr = htoes(eeproma);
		ed.d2 = 0x0000;
		do
		{
			wkc = ecx_FPWR(configadr, ECT_REG_EEPCTL, sizeof(ed), &ed);
		} while ((wkc <= 0) && (cnt++ < EC_DEFAULT_RETRIES));
	}
}

uint32 EC_Read_EEprom2(EC_Main_t* pEC_Main, uint16 slave, int timeout)
{
	uint16 estat, configadr;
	uint32 edat;
	int wkc, cnt = 0;

	configadr = pEC_Main->slave_list[slave].configadr;
	edat = 0;
	estat = 0x0000;

	if (ecx_eeprom_waitnotbusyFP(pEC_Main, configadr, &estat, timeout))
	{
		do
		{
			wkc = ecx_FPRD(configadr, ECT_REG_EEPDAT, sizeof(edat), &edat);
		} while ((wkc <= 0) && (cnt++ < EC_DEFAULT_RETRIES));
	}

	return edat;
}

/*
void ec_pusherror(const ec_errort* Ec)
{
	EC_Push_Error(&m_EC_pEC_Main, Ec);
}
*/

/*
boolean ec_poperror(ec_errort* Ec)
{
	return EC_Pop_Error(&m_EC_pEC_Main, Ec);
}
*/

/*
boolean ec_iserror(void)
{
	return EC_Is_Error(&m_EC_pEC_Main);
}
*/

/*
void ec_packeterror(uint16 Slave, uint16 Index, uint8 SubIdx, uint16 ErrorCode)
{
	EC_Packet_Error(&m_EC_pEC_Main, Slave, Index, SubIdx, ErrorCode);
}
*/

uint8 EC_Sii_Get_Byte(uint16 slave, uint16 address)
{
	return EC_SII_Read(&m_EC_Main, slave, address);
}


int16 eC_Sii_Find(uint16 slave, uint16 cat)
{
	return EC_SII_Find(&m_EC_Main, slave, cat);
}

void EC_Sii_string(char* str, uint16 slave, uint16 Sn)
{
	EC_SII_String(&m_EC_Main, str, slave, Sn);
}

/*
uint16 ec_siiFMMU(uint16 slave, ec_eepromFMMUt* FMMU)
{
	return EC_SII_FMMU(&m_EC_pEC_Main, slave, FMMU);
}
*/

/*
uint16 ec_siiSM(uint16 slave, ec_eepromSMt* SM)
{
	return EC_SII_SM(&m_EC_pEC_Main, slave, SM);
}
*/

/*
uint16 ec_siiSMnext(uint16 slave, ec_eepromSMt* SM, uint16 n)
{
	return EC_SII_SM_Next(&m_EC_pEC_Main, slave, SM, n);
}
*/

/*
int ec_siiPDO(uint16 slave, ec_eepromPDOt* PDO, uint8 t)
{
	return EC_SII_PDO(&m_EC_pEC_Main, slave, PDO, t);
}
*/

int EC_Read_State(void)
{
	int nReturn = 0;

	// Normal Process Timer : 62us
	// Event Error Process Timer : us
	__HAL_TIM_DISABLE(&htim4);
	__HAL_TIM_DISABLE_IT(&htim4, TIM_IT_UPDATE);

	nReturn = EC_Read_State_1(&m_EC_Main);

	__HAL_TIM_SET_COUNTER(&htim4, ETHERCAT_UPDATE_TIME);
	__HAL_TIM_ENABLE(&htim4);
	__HAL_TIM_ENABLE_IT(&htim4, TIM_IT_UPDATE);

	return nReturn;
}

/*
int ec_writestate(uint16 slave)
{
	return EC_Write_State(&m_EC_pEC_Main, slave);
}
*/

uint16 EC_State_Check(uint16 slave, uint16 reqstate, int timeout)
{
	return EC_State_Check_1(&m_EC_Main, slave, reqstate, timeout);
}


/*
int EC_Mbx_Empty(uint16 slave, int timeout)
{
	return EC_MailBox_Empty(&m_EC_pEC_Main, slave, timeout);
}
*/

/*
int ec_mbxsend(uint16 slave, EC_Mbx_buffer_t* mbx, int timeout)
{
	return EC_MailBox_Send(&m_EC_pEC_Main, slave, mbx, timeout);
}
*/

/*
int ec_mbxreceive(uint16 slave, EC_Mbx_buffer_t* mbx, int timeout)
{
	return EC_MailBox_Receive(&m_EC_pEC_Main, slave, mbx, timeout);
}
*/

/*
void ec_esidump(uint16 slave, uint8* esibuf)
{
	EC_Esi_dump(&m_EC_pEC_Main, slave, esibuf);
}
*/

/*
uint32 ec_readeeprom(uint16 slave, uint16 eeproma, int timeout)
{
	return EC_Read_EEprom(&m_EC_pEC_Main, slave, eeproma, timeout);
}
*/

/*
int ec_eeprom2master(uint16 slave)
{
	return EC_EEpromToMaster(&m_EC_pEC_Main, slave);
}
*/

int ec_eeprom2pdi(uint16 slave)
{
	return EC_EEpromToPDI(&m_EC_Main, slave);
}

/*
uint16 ec_eeprom_waitnotbusyFP(uint16 configadr, uint16* estat, int timeout)
{
	return ecx_eeprom_waitnotbusyFP(&m_EC_pEC_Main, configadr, estat, timeout);
}
*/

/*
uint64 ec_readeepromFP(uint16 configadr, uint16 eeproma, int timeout)
{
	return EC_Read_EEpromFP(&m_EC_pEC_Main, configadr, eeproma, timeout);
}
*/

/*
void ec_readeeprom1(uint16 slave, uint16 eeproma)
{
	EC_Read_EEprom1(&m_EC_pEC_Main, slave, eeproma);
}
*/

/*
uint32 ec_readeeprom2(uint16 slave, int timeout)
{
	return EC_Read_EEprom2(&m_EC_pEC_Main, slave, timeout);
}
*/


int EC_Send_ProcessData(uint8 group)
{
	/*
	ecx_LRW(ec_group[group].logstartaddr, ec_group[group].IOsegment[0], IOmap);

	ecx_FRMW(m_ecx_pEC_Main.slavelist[m_ecx_pEC_Main.grouplist[group].DCnext].configadr,
		ECT_REG_DCSYSTIME, sizeof(int64), (void*)&ec_DCtime);
		*/

	ecx_LRWDC(m_EC_Group[group].logstartaddr, m_EC_Group[group].IOsegment[0], m_IOmap, \
		m_EC_Main.slave_list[m_EC_Main.group_list[group].DCnext].configadr, \
		& m_EC_DCtime);

	return 0;
}

int ec_send_processdata_group_1(uint8 group)
{
	ecx_LRW(m_EC_Group[group].logstartaddr, m_EC_Group[group].IOsegment[0], m_IOmap);
	//ecx_LRW(m_EC_Group[group].logstartaddr, 1, m_IOmap);

	return 0;
}

char* dtype2string(uint16 dtype)
{
	switch (dtype)
	{
	case ECT_BOOLEAN:
		sprintf(m_hstr, "BOOLEAN");
		break;
	case ECT_INTEGER8:
		sprintf(m_hstr, "INTEGER8");
		break;
	case ECT_INTEGER16:
		sprintf(m_hstr, "INTEGER16");
		break;
	case ECT_INTEGER32:
		sprintf(m_hstr, "INTEGER32");
		break;
	case ECT_INTEGER24:
		sprintf(m_hstr, "INTEGER24");
		break;
	case ECT_INTEGER64:
		sprintf(m_hstr, "INTEGER64");
		break;
	case ECT_UNSIGNED8:
		sprintf(m_hstr, "UNSIGNED8");
		break;
	case ECT_UNSIGNED16:
		sprintf(m_hstr, "UNSIGNED16");
		break;
	case ECT_UNSIGNED32:
		sprintf(m_hstr, "UNSIGNED32");
		break;
	case ECT_UNSIGNED24:
		sprintf(m_hstr, "UNSIGNED24");
		break;
	case ECT_UNSIGNED64:
		sprintf(m_hstr, "UNSIGNED64");
		break;
	case ECT_REAL32:
		sprintf(m_hstr, "REAL32");
		break;
	case ECT_REAL64:
		sprintf(m_hstr, "REAL64");
		break;
	case ECT_BIT1:
		sprintf(m_hstr, "BIT1");
		break;
	case ECT_BIT2:
		sprintf(m_hstr, "BIT2");
		break;
	case ECT_BIT3:
		sprintf(m_hstr, "BIT3");
		break;
	case ECT_BIT4:
		sprintf(m_hstr, "BIT4");
		break;
	case ECT_BIT5:
		sprintf(m_hstr, "BIT5");
		break;
	case ECT_BIT6:
		sprintf(m_hstr, "BIT6");
		break;
	case ECT_BIT7:
		sprintf(m_hstr, "BIT7");
		break;
	case ECT_BIT8:
		sprintf(m_hstr, "BIT8");
		break;
	case ECT_VISIBLE_STRING:
		sprintf(m_hstr, "VISIBLE_STRING");
		break;
	case ECT_OCTET_STRING:
		sprintf(m_hstr, "OCTET_STRING");
		break;
	default:
		sprintf(m_hstr, "Type 0x%4.4X", dtype);
	}
	return m_hstr;
}

char* SDO2string(uint16 slave, uint16 index, uint8 subidx, uint16 dtype)
{
	int l = sizeof(m_usdo) - 1, i;
	uint8* u8;
	int8* i8;
	uint16* u16;
	int16* i16;
	uint32* u32;
	int32* i32;
	uint64* u64;
	int64* i64;
	float* sr;
	double* dr;
	char es[32];

	memset(&m_usdo, 0, 128);
	EC_SDOread(slave, index, subidx, FALSE, &l, &m_usdo, EC_TIMEOUT_RXM);
	if (m_EcatError)
	{
		return ec_elist2string();
	}
	else
	{
		switch (dtype)
		{
		case ECT_BOOLEAN:
			u8 = (uint8*)&m_usdo[0];
			if (*u8) sprintf(m_hstr, "TRUE");
			else sprintf(m_hstr, "FALSE");
			break;
		case ECT_INTEGER8:
			i8 = (int8*)&m_usdo[0];
			sprintf(m_hstr, "0x%2.2x %d", *i8, *i8);
			break;
		case ECT_INTEGER16:
			i16 = (int16*)&m_usdo[0];
			sprintf(m_hstr, "0x%4.4x %d", *i16, *i16);
			break;
		case ECT_INTEGER32:
		case ECT_INTEGER24:
			i32 = (int32*)&m_usdo[0];
			sprintf(m_hstr, "0x%8.8ld %ld", *i32, *i32);
			break;
		case ECT_INTEGER64:
			i64 = (int64*)&m_usdo[0];
			sprintf(m_hstr, "0x%16.16"PRIx64" %"PRId64, *i64, *i64);
			break;
		case ECT_UNSIGNED8:
			u8 = (uint8*)&m_usdo[0];
			sprintf(m_hstr, "0x%2.2x %u", *u8, *u8);
			break;
		case ECT_UNSIGNED16:
			u16 = (uint16*)&m_usdo[0];
			sprintf(m_hstr, "0x%4.4x %u", *u16, *u16);
			break;
		case ECT_UNSIGNED32:
		case ECT_UNSIGNED24:
			u32 = (uint32*)&m_usdo[0];
			sprintf(m_hstr, "0x%8.8lx %ld", *u32, *u32);
			break;
		case ECT_UNSIGNED64:
			u64 = (uint64*)&m_usdo[0];
			sprintf(m_hstr, "0x%16.16"PRIx64" %"PRIu64, *u64, *u64);
			break;
		case ECT_REAL32:
			sr = (float*)&m_usdo[0];
			sprintf(m_hstr, "%lf", *sr);
			break;
		case ECT_REAL64:
			dr = (double*)&m_usdo[0];
			sprintf(m_hstr, "%lf", *dr);
			break;
		case ECT_BIT1:
		case ECT_BIT2:
		case ECT_BIT3:
		case ECT_BIT4:
		case ECT_BIT5:
		case ECT_BIT6:
		case ECT_BIT7:
		case ECT_BIT8:
			u8 = (uint8*)&m_usdo[0];
			sprintf(m_hstr, "0x%x", *u8);
			break;
		case ECT_VISIBLE_STRING:
			strcpy(m_hstr, m_usdo);
			break;
		case ECT_OCTET_STRING:
			m_hstr[0] = 0x00;
			for (i = 0; i < l; i++)
			{
				sprintf(es, "0x%2.2x ", m_usdo[i]);
				strcat(m_hstr, es);
			}
			break;
		default:
			sprintf(m_hstr, "Unknown type");
		}
		return m_hstr;
	}
}

int si_PDOassign(uint16 slave, uint16 PDOassign, int mapoffset, int bitoffset)
{
	uint16 idxloop, nidx, subidxloop, rdat, idx, subidx;
	uint8 subcnt;
	int wkc, bsize = 0, rdl;
	int32 rdat2;
	uint8 bitlen, obj_subidx;
	uint16 obj_idx;
	int abs_offset, abs_bit;

	rdl = sizeof(rdat); rdat = 0;
	wkc = EC_SDOread(slave, PDOassign, 0x00, FALSE, &rdl, &rdat, EC_TIMEOUT_RXM);
	rdat = etohs(rdat);

	if ((wkc > 0) && (rdat > 0))
	{
		nidx = rdat;
		bsize = 0;

		for (idxloop = 1; idxloop <= nidx; idxloop++)
		{
			rdl = sizeof(rdat); rdat = 0;
			wkc = EC_SDOread(slave, PDOassign, (uint8)idxloop, FALSE, &rdl, &rdat, EC_TIMEOUT_RXM);
			idx = etohl(rdat);
			if (idx > 0)
			{
				rdl = sizeof(subcnt); subcnt = 0;
				wkc = EC_SDOread(slave, idx, 0x00, FALSE, &rdl, &subcnt, EC_TIMEOUT_RXM);
				subidx = subcnt;
				for (subidxloop = 1; subidxloop <= subidx; subidxloop++)
				{
					rdl = sizeof(rdat2); rdat2 = 0;
					wkc = EC_SDOread(slave, idx, (uint8)subidxloop, FALSE, &rdl, &rdat2, EC_TIMEOUT_RXM);
					rdat2 = etohl(rdat2);
					bitlen = LO_BYTE(rdat2);
					bsize += bitlen;
					obj_idx = (uint16)(rdat2 >> 16);
					obj_subidx = (uint8)((rdat2 >> 8) & 0x000000ff);
					abs_offset = mapoffset + (bitoffset / 8);
					abs_bit = bitoffset % 8;
					m_ODlist.Slave = slave;
					m_ODlist.Index[0] = obj_idx;
					m_OElist.Entries = 0;
					wkc = 0;
					if (obj_idx || obj_subidx)
						wkc = EC_ReadOEsingle(0, obj_subidx, &m_ODlist, &m_OElist);
					printf("  [0x%4.4X.%1d] 0x%4.4X:0x%2.2X 0x%2.2X", abs_offset, abs_bit, obj_idx, obj_subidx, bitlen);
					if ((wkc > 0) && m_OElist.Entries)
					{
						printf(" %-12s %s\r\n", dtype2string(m_OElist.DataType[obj_subidx]), m_OElist.Name[obj_subidx]);
					}
					else
						printf("\r\n");
					bitoffset += bitlen;
				};
			};
		};
	};
	/* return total found bitlength (PDO) */
	return bsize;
}

int si_map_sdo(int slave)
{
	int wkc, rdl;
	int retVal = 0;
	uint8 nSM, iSM, tSM;
	int Tsize, outputs_bo, inputs_bo;
	uint8 SMt_bug_add;

	printf("PDO mapping according to CoE :\r\n");
	SMt_bug_add = 0;
	outputs_bo = 0;
	inputs_bo = 0;
	rdl = sizeof(nSM); nSM = 0;
	wkc = EC_SDOread(slave, ECT_SDO_SM_COMM_TYPE, 0x00, FALSE, &rdl, &nSM, EC_TIMEOUT_RXM);
	if ((wkc > 0) && (nSM > 2))
	{
		nSM--;
		if (nSM > EC_MAX_SM)
			nSM = EC_MAX_SM;
		for (iSM = 2; iSM <= nSM; iSM++)
		{
			rdl = sizeof(tSM); tSM = 0;
			wkc = EC_SDOread(slave, ECT_SDO_SM_COMM_TYPE, iSM + 1, FALSE, &rdl, &tSM, EC_TIMEOUT_RXM);
			if (wkc > 0)
			{
				if ((iSM == 2) && (tSM == 2))
				{
					SMt_bug_add = 1;
					printf("Activated SM type workaround, possible incorrect mapping.\r\n");
				}
				if (tSM)
					tSM += SMt_bug_add;

				if (tSM == 3)
				{
					printf("  SM%1d outputs\r\n     addr b   index: sub bitl data_type    name\r\n", iSM);
					Tsize = si_PDOassign(slave, ECT_SDO_PDO_ASSIGN + iSM, (int)(m_EC_Slave[slave].outputs - (uint8*)&m_IOmap[0]), outputs_bo);
					outputs_bo += Tsize;
				}
				if (tSM == 4)
				{
					printf("  SM%1d inputs\r\n     addr b   index: sub bitl data_type    name\r\n", iSM);
					Tsize = si_PDOassign(slave, ECT_SDO_PDO_ASSIGN + iSM, (int)(m_EC_Slave[slave].inputs - (uint8*)&m_IOmap[0]), inputs_bo);
					inputs_bo += Tsize;
				}
			}
		}
	}

	if ((outputs_bo > 0) || (inputs_bo > 0))
		retVal = 1;

	return retVal;
}

int si_siiPDO(uint16 slave, uint8 t, int mapoffset, int bitoffset)
{
	uint16 a, w, c, e, er, Size;
	uint8 eectl;
	uint16 obj_idx;
	uint8 obj_subidx;
	uint8 obj_name;
	uint8 obj_datatype;
	uint8 bitlen;
	int totalsize;
	EC_eepromPDO_t eepPDO;
	EC_eepromPDO_t* PDO;
	int abs_offset, abs_bit;
	char str_name[EC_MAX_NAME + 1];

	eectl = m_EC_Slave[slave].eep_pdi;
	Size = 0;
	totalsize = 0;
	PDO = &eepPDO;
	PDO->nPDO = 0;
	PDO->Length = 0;
	PDO->Index[1] = 0;
	for (c = 0; c < EC_MAX_SM; c++) PDO->SMbitsize[c] = 0;
	if (t > 1)
		t = 1;
	PDO->Startpos = eC_Sii_Find(slave, ECT_SII_PDO + t);
	if (PDO->Startpos > 0)
	{
		a = PDO->Startpos;
		w = EC_Sii_Get_Byte(slave, a++);
		w += (EC_Sii_Get_Byte(slave, a++) << 8);
		PDO->Length = w;
		c = 1;
		do
		{
			PDO->nPDO++;
			PDO->Index[PDO->nPDO] = EC_Sii_Get_Byte(slave, a++);
			PDO->Index[PDO->nPDO] += (EC_Sii_Get_Byte(slave, a++) << 8);
			PDO->BitSize[PDO->nPDO] = 0;
			c++;
			e = EC_Sii_Get_Byte(slave, a++);
			PDO->SyncM[PDO->nPDO] = EC_Sii_Get_Byte(slave, a++);
			a++;
			obj_name = EC_Sii_Get_Byte(slave, a++);
			a += 2;
			c += 2;
			if (PDO->SyncM[PDO->nPDO] < EC_MAX_SM)
			{
				str_name[0] = 0;
				if (obj_name)
					EC_Sii_string(str_name, slave, obj_name);
				if (t)
					printf("  SM%1d RXPDO 0x%4.4X %s\r\n", PDO->SyncM[PDO->nPDO], PDO->Index[PDO->nPDO], str_name);
				else
					printf("  SM%1d TXPDO 0x%4.4X %s\r\n", PDO->SyncM[PDO->nPDO], PDO->Index[PDO->nPDO], str_name);
				printf("     addr b   index: sub bitl data_type    name\r\n");

				for (er = 1; er <= e; er++)
				{
					c += 4;
					obj_idx = EC_Sii_Get_Byte(slave, a++);
					obj_idx += (EC_Sii_Get_Byte(slave, a++) << 8);
					obj_subidx = EC_Sii_Get_Byte(slave, a++);
					obj_name = EC_Sii_Get_Byte(slave, a++);
					obj_datatype = EC_Sii_Get_Byte(slave, a++);
					bitlen = EC_Sii_Get_Byte(slave, a++);
					abs_offset = mapoffset + (bitoffset / 8);
					abs_bit = bitoffset % 8;

					PDO->BitSize[PDO->nPDO] += bitlen;
					a += 2;

					str_name[0] = 0;
					if (obj_name)
						EC_Sii_string(str_name, slave, obj_name);

					printf("  [0x%4.4X.%1d] 0x%4.4X:0x%2.2X 0x%2.2X", abs_offset, abs_bit, obj_idx, obj_subidx, bitlen);
					printf(" %-12s %s\r\n", dtype2string(obj_datatype), str_name);
					bitoffset += bitlen;
					totalsize += bitlen;
				}
				PDO->SMbitsize[PDO->SyncM[PDO->nPDO]] += PDO->BitSize[PDO->nPDO];
				Size += PDO->BitSize[PDO->nPDO];
				c++;
			}
			else
			{
				c += 4 * e;
				a += 8 * e;
				c++;
			}

			if (PDO->nPDO >= (EC_MAX_EEP_DO - 1)) c = PDO->Length;
		} while (c < PDO->Length);
	}

	if (eectl) ec_eeprom2pdi(slave);

	return totalsize;
}


int si_map_sii(int slave)
{
	int retVal = 0;
	int Tsize, outputs_bo, inputs_bo;

	printf("PDO mapping according to SII :\r\n");

	outputs_bo = 0;
	inputs_bo = 0;
	Tsize = si_siiPDO(slave, 1, (int)(m_EC_Slave[slave].outputs - (uint8*)&m_IOmap), outputs_bo);
	outputs_bo += Tsize;
	Tsize = si_siiPDO(slave, 0, (int)(m_EC_Slave[slave].inputs - (uint8*)&m_IOmap), inputs_bo);
	inputs_bo += Tsize;

	if ((outputs_bo > 0) || (inputs_bo > 0))
		retVal = 1;

	return retVal;
}

void si_sdo(int cnt)
{
	int i, j;

	m_ODlist.Entries = 0;
	memset(&m_ODlist, 0, sizeof(m_ODlist));
	if (EC_ReadODlist(cnt, &m_ODlist))
	{
		printf(" CoE Object Description found, %d entries.\r\n", m_ODlist.Entries);
		for (i = 0; i < m_ODlist.Entries; i++)
		{
			EC_ReadODdescription(i, &m_ODlist);
			while (m_EcatError) printf("%s", ec_elist2string());
			printf(" Index: %4.4x Datatype: %4.4x Objectcode: %2.2x Name: %s\r\n",
				m_ODlist.Index[i], m_ODlist.DataType[i], m_ODlist.ObjectCode[i], m_ODlist.Name[i]);
			memset(&m_OElist, 0, sizeof(m_OElist));
			EC_ReadOE(i, &m_ODlist, &m_OElist);
			while (m_EcatError) printf("%s", ec_elist2string());
			for (j = 0; j < m_ODlist.MaxSub[i] + 1; j++)
			{
				if ((m_OElist.DataType[j] > 0) && (m_OElist.BitLength[j] > 0))
				{
					printf("  Sub: %2.2x Datatype: %4.4x Bitlength: %4.4x Obj.access: %4.4x Name: %s\r\n",
						j, m_OElist.DataType[j], m_OElist.BitLength[j], m_OElist.ObjAccess[j], m_OElist.Name[j]);
					if ((m_OElist.ObjAccess[j] & 0x0007))
					{
						printf("          Value :%s\r\n", SDO2string(cnt, m_ODlist.Index[i], j, m_OElist.DataType[j]));
					}
				}
			}
		}
	}
	else
	{
		while (m_EcatError) printf("%s", ec_elist2string());
	}
}

void slaveinfo()
{
	int cnt, j, nSM;
	uint16 ssigen;

	/* find and auto-config slaves */

	printf("%d slaves found and configured.\r\n", m_EC_SlaveCount);

	EC_Read_State();

	for (cnt = 1; cnt <= m_EC_SlaveCount; cnt++)
	{
		printf("\r\nSlave:%d\r\n Name:%s\r\n Output size: %dbits\r\n Input size: %dbits\r\n State: %d\r\n Delay: %ld[ns]\r\n Has DC: %d\r\n",
			cnt, m_EC_Slave[cnt].name, m_EC_Slave[cnt].Obits, m_EC_Slave[cnt].Ibits,
			m_EC_Slave[cnt].state, m_EC_Slave[cnt].pdelay, m_EC_Slave[cnt].hasdc);
		if (m_EC_Slave[cnt].hasdc) printf(" DCParentport:%d\r\n", m_EC_Slave[cnt].parentport);
		printf(" Activeports:%d.%d.%d.%d\r\n", (m_EC_Slave[cnt].activeports & 0x01) > 0,
			(m_EC_Slave[cnt].activeports & 0x02) > 0,
			(m_EC_Slave[cnt].activeports & 0x04) > 0,
			(m_EC_Slave[cnt].activeports & 0x08) > 0);
		printf(" Configured address: %4.4x\r\n", m_EC_Slave[cnt].configadr);
		printf(" Alias address: 0x%4.4x\r\n", m_EC_Slave[cnt].aliasadr);
		printf(" Man: 0x%8.8x ID: 0x%8.8x Rev: 0x%8.8x\r\n", (int)m_EC_Slave[cnt].eep_man, (int)m_EC_Slave[cnt].eep_id, (int)m_EC_Slave[cnt].eep_rev);
		for (nSM = 0; nSM < EC_MAX_SM; nSM++)
		{
			if (m_EC_Slave[cnt].SM[nSM].StartAddr > 0)
				printf(" SM%1d A:0x%4.4x L:%4d F:0x%8.8x Type:%d\r\n", nSM, m_EC_Slave[cnt].SM[nSM].StartAddr, m_EC_Slave[cnt].SM[nSM].SMlength,
					(int)m_EC_Slave[cnt].SM[nSM].SMflags, m_EC_Slave[cnt].SMtype[nSM]);
		}
		for (j = 0; j < m_EC_Slave[cnt].FMMUunused; j++)
		{
			printf(" FMMU%1d Ls:0x%8.8x Ll:%4d Lsb:%d Leb:%d Ps:0x%4.4x Psb:%d Ty:0x%2.2x Act:0x%2.2x\r\n", j,
				(int)m_EC_Slave[cnt].FMMU[j].LogStart, m_EC_Slave[cnt].FMMU[j].LogLength, m_EC_Slave[cnt].FMMU[j].LogStartbit,
				m_EC_Slave[cnt].FMMU[j].LogEndbit, m_EC_Slave[cnt].FMMU[j].PhysStart, m_EC_Slave[cnt].FMMU[j].PhysStartBit,
				m_EC_Slave[cnt].FMMU[j].FMMUtype, m_EC_Slave[cnt].FMMU[j].FMMUactive);
		}
		printf(" FMMUfunc 0:%d 1:%d 2:%d 3:%d\r\n",
			m_EC_Slave[cnt].FMMU0func, m_EC_Slave[cnt].FMMU1func, m_EC_Slave[cnt].FMMU2func, m_EC_Slave[cnt].FMMU3func);
		printf(" MBX length wr: %d rd: %d MBX protocols : 0x%2.2x\r\n", m_EC_Slave[cnt].mbx_l, m_EC_Slave[cnt].mbx_rl, m_EC_Slave[cnt].mbx_proto);
		ssigen = eC_Sii_Find(cnt, ECT_SII_GENERAL);

		if (ssigen)
		{
			m_EC_Slave[cnt].CoEdetails = EC_Sii_Get_Byte(cnt, ssigen + 0x07);
			m_EC_Slave[cnt].FoEdetails = EC_Sii_Get_Byte(cnt, ssigen + 0x08);
			m_EC_Slave[cnt].EoEdetails = EC_Sii_Get_Byte(cnt, ssigen + 0x09);
			m_EC_Slave[cnt].SoEdetails = EC_Sii_Get_Byte(cnt, ssigen + 0x0a);
			if ((EC_Sii_Get_Byte(cnt, ssigen + 0x0d) & 0x02) > 0)
			{
				m_EC_Slave[cnt].blockLRW = 1;
				m_EC_Slave[0].blockLRW++;
			}
			m_EC_Slave[cnt].Ebuscurrent = EC_Sii_Get_Byte(cnt, ssigen + 0x0e);
			m_EC_Slave[cnt].Ebuscurrent += EC_Sii_Get_Byte(cnt, ssigen + 0x0f) << 8;
			m_EC_Slave[0].Ebuscurrent += m_EC_Slave[cnt].Ebuscurrent;
		}
		printf(" CoE details: 0x%2.2x FoE details: 0x%2.2x EoE details: 0x%2.2x SoE details: 0x%2.2x\r\n",
			m_EC_Slave[cnt].CoEdetails, m_EC_Slave[cnt].FoEdetails, m_EC_Slave[cnt].EoEdetails, m_EC_Slave[cnt].SoEdetails);
		printf(" Ebus current: %d[mA]\r\n only LRD/LWR:%d\r\n",
			m_EC_Slave[cnt].Ebuscurrent, m_EC_Slave[cnt].blockLRW);

		if ((m_EC_Slave[cnt].mbx_proto & ECT_MBXPROT_COE) && m_printSDO)
			si_sdo(cnt);

		if (m_printMAP)
		{
			if (m_EC_Slave[cnt].mbx_proto & ECT_MBXPROT_COE)
				si_map_sdo(cnt);
			else
				si_map_sii(cnt);
		}
	}
}

const char* ec_sdoerror2string(uint32 sdoerrorcode)
{
	int i = 0;

	while ((ec_sdoerrorlist[i].errorcode != 0xffffffffUL) &&
		(ec_sdoerrorlist[i].errorcode != sdoerrorcode))
	{
		i++;
	}

	return ec_sdoerrorlist[i].errordescription;
}

char* ec_ALstatuscode2string(uint16 ALstatuscode)
{
	int i = 0;

	while ((ec_ALstatuscodelist[i].ALstatuscode != 0xffff) &&
		(ec_ALstatuscodelist[i].ALstatuscode != ALstatuscode))
	{
		i++;
	}

	return (char*)ec_ALstatuscodelist[i].ALstatuscodedescription;
}

char* ec_soeerror2string(uint16 errorcode)
{
	int i = 0;

	while ((ec_soeerrorlist[i].errorcode != 0xffff) &&
		(ec_soeerrorlist[i].errorcode != errorcode))
	{
		i++;
	}

	return (char*)ec_soeerrorlist[i].errordescription;
}

char* ec_mbxerror2string(uint16 errorcode)
{
	int i = 0;

	while ((ec_mbxerrorlist[i].errorcode != 0xffff) &&
		(ec_mbxerrorlist[i].errorcode != errorcode))
	{
		i++;
	}

	return (char*)ec_mbxerrorlist[i].errordescription;
}

char* ecx_err2string(const EC_Error_t Ec)
{
	char timestr[20];
	sprintf(timestr, "Time:%12.3f", Ec.Time.sec + (Ec.Time.usec / 1000000.0));

	switch (Ec.Etype)
	{
	case EC_ERR_TYPE_SDO_ERROR:
	{
		sprintf(estring, "%s SDO slave:%d index:%4.4x.%2.2x error:%8.8x %s\r\n",
			timestr, Ec.Slave, Ec.Index, Ec.SubIdx, (unsigned)Ec.AbortCode, ec_sdoerror2string(Ec.AbortCode));
		break;
	}
	case EC_ERR_TYPE_EMERGENCY:
	{
		sprintf(estring, "%s EMERGENCY slave:%d error:%4.4x\r\n",
			timestr, Ec.Slave, Ec.ErrorCode);
		break;
	}
	case EC_ERR_TYPE_PACKET_ERROR:
	{
		sprintf(estring, "%s PACKET slave:%d index:%4.4x.%2.2x error:%d\r\n",
			timestr, Ec.Slave, Ec.Index, Ec.SubIdx, Ec.ErrorCode);
		break;
	}
	case EC_ERR_TYPE_SDOINFO_ERROR:
	{
		sprintf(estring, "%s SDO slave:%d index:%4.4x.%2.2x error:%8.8x %s\r\n",
			timestr, Ec.Slave, Ec.Index, Ec.SubIdx, (unsigned)Ec.AbortCode, ec_sdoerror2string(Ec.AbortCode));
		break;
	}
	case EC_ERR_TYPE_SOE_ERROR:
	{
		sprintf(estring, "%s SoE slave:%d IDN:%4.4x error:%4.4x %s\r\n",
			timestr, Ec.Slave, Ec.Index, (unsigned)Ec.AbortCode, ec_soeerror2string(Ec.ErrorCode));
		break;
	}
	case EC_ERR_TYPE_MBX_ERROR:
	{
		sprintf(estring, "%s MBX slave:%d error:%4.4x %s\r\n",
			timestr, Ec.Slave, Ec.ErrorCode, ec_mbxerror2string(Ec.ErrorCode));
		break;
	}
	default:
	{
		sprintf(estring, "%s error:%8.8x\r\n",
			timestr, (unsigned)Ec.AbortCode);
		break;
	}
	}
	return (char*)estring;
}

char* ecx_elist2string(EC_Main_t* nEC_Main)
{
	EC_Error_t Ec;

	if (EC_Pop_Error(nEC_Main, &Ec))
	{
		return ecx_err2string(Ec);
	}
	else
	{
		return "";
	}
}

char* ec_elist2string(void)
{
	return ecx_elist2string(&m_EC_Main);
}


INT08U Check_SlaveState(uint16 reqstate)
{
	INT08U nReturn = 0;

	EC_State_Check(0, reqstate, EC_TIMEOUT_STATE * 3);

	if (m_EC_Slave[0].state != reqstate)
	{
#if DEBUG_ETHERCAT_MSG
		if (reqstate == EC_STATE_OPERATIONAL)
		{
			printf("Not all slaves reached OP state.\r\n");
		}
		else if (reqstate == EC_STATE_SAFE_OP)
		{
			printf("Not all slaves reached SAFE OP state.\r\n");
		}
		else if (reqstate == EC_STATE_PRE_OP)
		{
			printf("Not all slaves reached PRE OP state.\r\n");
		}
		else
		{
			printf("Not all slaves reached Init state.\r\n");
		}
#endif
		EC_Read_State();
		for (INT16U i = 1; i <= m_EC_SlaveCount; i++)
		{
			if (m_EC_Slave[i].state != reqstate)
			{
#if DEBUG_ETHERCAT_MSG
				printf("Slave %d State=%2x StatusCode=%4x : %s\r\n",
					i, m_EC_Slave[i].state, m_EC_Slave[i].ALstatuscode, ec_ALstatuscode2string(m_EC_Slave[i].ALstatuscode));
#endif

				// Retry AL Control....
				nReturn = 0;
			}
		}
	}
	else
	{
		nReturn = 1;
	}

	return nReturn;
}

void EC_FPWR_SM_Set(INT08U nSM_No)
{
	INT16U Def_SM_Reg[4] = { ECT_REG_SM0 , ECT_REG_SM1, ECT_REG_SM2, ECT_REG_SM3 };
	INT16U i = 0;

	for (i = 1; i <= m_EC_SlaveCount; i++)
	{
		if (nSM_No == 3)
		{
			m_EC_Slave[i].SM[nSM_No].SMflags = htoel(0x00010020);	//  0x0020:OpMode: 3 buffer, Access: Read, PDI IRQ, 
		}

		ecx_FPWR(m_EC_Slave[i].configadr, Def_SM_Reg[nSM_No],
			sizeof(m_EC_Slave[i].SM[nSM_No]), &m_EC_Slave[i].SM[nSM_No]);
	}
}

int ABB_ACS380_setup(uint16 slave)
{
	// RxPDO Map
	// Index,	Name,						Type
	// 6040		Controlword					U16
	// 6060		Modes of operation			I8	
	// 6042		vl target velocity			I16
	uint32 RxPDOmap_1600[3] = { 0x60400010, 0x60600008, 0x60420010 };
	uint8 nRxPDO_Count = 3;

	// TxPDO Map
	// Index,	Name,							Type
	// 6041		Statusword						U16	
	// 6043		vl velocity demand				I16
	// 6044		vl velocity actual value		I16	
	// 606B		velocity demand value			I32
	// 606C		velocity actual value			I32
	// 603F		Error Code						U16
	uint32 TxPDOmap_1A00[6] = { 0x60410010, 0x60430010, 0x60440010, 0x606B0020, 0x606C0020, 0x603F0010 };
	uint8 nTxPDO_Count = 6;

	// map velocity
	uint16 map_1c12[2] = { 0x0001, 0x1600 };
	uint16 map_1c13[2] = { 0x0001, 0x1a00 };

	//uint8 rdat8;
	uint8 wdat8;
	//uint16 rdat16;
	//uint16 wdat16;
	//uint32 wdat32;
	//uint32 rdat32;

	void* pRdat;
	int rdl;

	int retval = 0, i = 0;
	//uint16 u16val;

	wdat8 = 0x00;
	rdl = sizeof(wdat8); pRdat = (void*)&wdat8;
	retval += EC_SDOwrite(1, 0x1C12, 0, FALSE, rdl, pRdat, EC_TIMEOUT_TXM);

	wdat8 = 0x00;
	rdl = sizeof(wdat8); pRdat = (void*)&wdat8;
	retval += EC_SDOwrite(1, 0x1C13, 0, FALSE, rdl, pRdat, EC_TIMEOUT_TXM);

	wdat8 = 0x00;
	rdl = sizeof(wdat8); pRdat = (void*)&wdat8;
	retval += EC_SDOwrite(1, 0x1600, 0, FALSE, rdl, pRdat, EC_TIMEOUT_TXM);

	for (i = 1; i < (nRxPDO_Count + 1); i++)
	{
		retval += EC_SDOwrite(slave, 0x1600, i, FALSE, sizeof(INT32U), &RxPDOmap_1600[i - 1], EC_TIMEOUT_RXM);
	}

	wdat8 = nRxPDO_Count;
	rdl = sizeof(wdat8); pRdat = (void*)&wdat8;
	retval += EC_SDOwrite(1, 0x1600, 0, FALSE, rdl, pRdat, EC_TIMEOUT_TXM);

	wdat8 = 0x00;
	rdl = sizeof(wdat8); pRdat = (void*)&wdat8;
	retval += EC_SDOwrite(1, 0x1A00, 0, FALSE, rdl, pRdat, EC_TIMEOUT_TXM);

	for (i = 1; i < (nTxPDO_Count + 1); i++)
	{
		retval += EC_SDOwrite(slave, 0x1A00, i, FALSE, sizeof(INT32U), &TxPDOmap_1A00[i - 1], EC_TIMEOUT_RXM);
	}

	wdat8 = nTxPDO_Count;
	rdl = sizeof(wdat8); pRdat = (void*)&wdat8;
	retval += EC_SDOwrite(1, 0x1A00, 0, FALSE, rdl, pRdat, EC_TIMEOUT_TXM);

	retval += EC_SDOwrite(slave, 0x1c12, 1, FALSE, sizeof(INT16U), &map_1c12[1], EC_TIMEOUT_RXM);
	retval += EC_SDOwrite(slave, 0x1c12, 0, FALSE, sizeof(INT08U), &map_1c12[0], EC_TIMEOUT_RXM);

	retval += EC_SDOwrite(slave, 0x1c13, 1, FALSE, sizeof(INT16U), &map_1c13[1], EC_TIMEOUT_RXM);
	retval += EC_SDOwrite(slave, 0x1c13, 0, FALSE, sizeof(INT08U), &map_1c13[0], EC_TIMEOUT_RXM);

	// bug in EL7031 old firmware, CompleteAccess for reading is not supported even if the slave says it is.
	//ec_slave[slave].CoEdetails &= ~ECT_COEDET_SDOCA;

	/*
	wdat32 = 0;
	rdl = sizeof(wdat32); pRdat = (void*)&wdat32;
	ec_SDOwrite(1, 0x6046, 0x01, FALSE, rdl, pRdat, EC_TIMEOUTSTATE);

	wdat32 = 1500;
	rdl = sizeof(wdat32); pRdat = (void*)&wdat32;
	ec_SDOwrite(1, 0x6046, 0x02, FALSE, rdl, pRdat, EC_TIMEOUTSTATE);

	wdat32 = 100;
	rdl = sizeof(wdat32); pRdat = (void*)&wdat32;
	ec_SDOwrite(1, 0x6048, 0x01, FALSE, rdl, pRdat, EC_TIMEOUTSTATE);

	wdat16 = 1;
	rdl = sizeof(wdat16); pRdat = (void*)&wdat16;
	ec_SDOwrite(1, 0x6048, 0x02, FALSE, rdl, pRdat, EC_TIMEOUTSTATE);

	wdat32 = 100;
	rdl = sizeof(wdat32); pRdat = (void*)&wdat32;
	ec_SDOwrite(1, 0x6049, 0x01, FALSE, rdl, pRdat, EC_TIMEOUTSTATE);

	wdat16 = 1;
	rdl = sizeof(wdat16); pRdat = (void*)&wdat16;
	ec_SDOwrite(1, 0x6049, 0x02, FALSE, rdl, pRdat, EC_TIMEOUTSTATE);
	*/

	// set some motor parameters, just as example
// 	wdat8 = 0x02;	// opereation velocity mode
// 	rdl = sizeof(wdat8); pRdat = (void*)&wdat8;
// 	retval += ec_SDOwrite(slave, 0x6060, 0x00, FALSE, rdl, pRdat, EC_TIMEOUTSAFE);

	//wdat16 = 150; // motor coil resistance in 0.01ohm
//    retval += ec_SDOwrite(slave, 0x8010, 0x04, FALSE, sizeof(u16val), &u16val, EC_TIMEOUTSAFE);

	// set other nescessary parameters as needed
	// .....

	while (m_EcatError) printf("%s", ec_elist2string());

#if DEBUG_ETHERCAT_MSG
	printf("ACS380 slave %d set, retval = %d\r\n", slave, retval);
#endif

	return 1;
}

int GX_EC0211_setup(uint16 slave)
{
	uint8 rdat8;
	uint8 wdat8;
	uint16 rdat16;
	uint16 wdat16;
	//uint32 wdat32;
	//uint32 rdat32;

	void* pData;
	int DLen;

	int retval = 0;
	//uint16 u16val;

	// set other nescessary parameters as needed
	// .....
	// 0x2200 Communication Error Setting
	// Set value 
	// 00 hex to 0F hex
	wdat8 = 0x0F;
	//wdat8 = 0;
	DLen = sizeof(wdat8); pData = (void*)&wdat8;
	retval += EC_SDOwrite(slave, 0x2200, 0x00, FALSE, DLen, pData, EC_TIMEOUT_STATE);

	DLen = sizeof(rdat8); pData = (void*)&rdat8;
	retval += EC_SDOread(slave, 0x2200, 0x00, FALSE, &DLen, pData, EC_TIMEOUT_STATE);

	wdat16 = 0x0258;
	//wdat16 = 0;
	DLen = sizeof(wdat16); pData = (void*)&wdat16;
	retval += EC_SDOwrite(slave, 0x2201, 0x00, FALSE, DLen, pData, EC_TIMEOUT_STATE);

	DLen = sizeof(rdat16); pData = (void*)&rdat16;
	retval += EC_SDOread(slave, 0x2201, 0x00, FALSE, &DLen, pData, EC_TIMEOUT_STATE);

	// 0x4001 Encoder Direction
	// Set value 
	// 0 - Forward direction at CW, 1 - Forward direction at CCW
	//wdat8 = 0;
	wdat8 = m_ExtSEnv2.ForkDrive.EncoderSetup.Dir;
	DLen = sizeof(wdat8); pData = (void*)&wdat8;
	retval += EC_SDOwrite(slave, 0x4001, 0x01, FALSE, DLen, pData, EC_TIMEOUT_STATE);

	/*
	DLen = sizeof(rdat8); pData = (void*)&rdat8;
	retval += ec_SDOread(slave, 0x4001, 0x01, FALSE, &DLen, pData, EC_TIMEOUTSTATE);
	*/

	// 0x4001 Encoder Input Setting
	// Set value 
	// 00 - Phase A/B pulse (Multiplication �� 1 cycle)
	// 01 - Phase A/B pulse (Multiplication �� 2 cycle)
	// 02 - Phase A/B pulse (Multiplication �� 4 cycle)
	// 03 - Code + pulse (Multiplication �� 1 cycle)
	// 04 - Incremental/decremental pulse
	//wdat8 = 2;
	wdat8 = m_ExtSEnv2.ForkDrive.EncoderSetup.Input_Pulse;
	DLen = sizeof(wdat8); pData = (void*)&wdat8;
	retval += EC_SDOwrite(slave, 0x4002, 0x01, FALSE, DLen, pData, EC_TIMEOUT_STATE);

	/*
	DLen = sizeof(rdat8); pData = (void*)&rdat8;
	retval += ec_SDOread(slave, 0x4002, 0x01, FALSE, &DLen, pData, EC_TIMEOUTSTATE);
	*/

	while (m_EcatError) printf("%s", ec_elist2string());

#if DEBUG_ETHERCAT_MSG
	printf("slave %d set, retval = %d\r\n", slave, retval);
#endif

	return 1;
}

int MX_DIO_10x_setup(uint16 slave)
{
	uint8 rdat8;
	uint8 wdat8;
	uint16 rdat16;
	uint16 wdat16;
	//uint32 wdat32;
	//uint32 rdat32;

	void* pData;
	int DLen;

	int retval = 0;
	//uint16 u16val;

	// 0x4001 Encoder Direction
	// Set value 
	// 0 - Forward direction at CW, 1 - Forward direction at CCW
	//wdat8 = 0;
	wdat8 = m_ExtSEnv2.ForkDrive.EncoderSetup.Dir;
	DLen = sizeof(wdat8); pData = (void*)&wdat8;
	retval += EC_SDOwrite(slave, 0x3001, 0x01, FALSE, DLen, pData, EC_TIMEOUT_STATE);

	// 0x4001 Encoder Input Setting
	// Set value 
	// 00 - Phase A/B pulse (Multiplication �� 1 cycle)
	// 01 - Phase A/B pulse (Multiplication �� 2 cycle)
	// 02 - Phase A/B pulse (Multiplication �� 4 cycle)
	// 03 - Code + pulse (Multiplication �� 1 cycle)
	// 04 - Incremental/decremental pulse
	//wdat8 = 2;
	wdat8 = m_ExtSEnv2.ForkDrive.EncoderSetup.Input_Pulse;
	DLen = sizeof(wdat8); pData = (void*)&wdat8;
	retval += EC_SDOwrite(slave, 0x3002, 0x01, FALSE, DLen, pData, EC_TIMEOUT_STATE);

	while (m_EcatError) printf("%s", ec_elist2string());

#if DEBUG_ETHERCAT_MSG
	printf("slave %d set, retval = %d\r\n", slave, retval);
#endif

	return 1;
}

int MX_DIO_20x_setup(uint16 slave)
{
	uint8 rdat8;
	uint8 wdat8;
	uint16 rdat16;
	uint16 wdat16;
	//uint32 wdat32;
	//uint32 rdat32;

	void* pData;
	int DLen;

	int retval = 0;
	//uint16 u16val;

	// 0x4001 Encoder Direction
	// Set value 
	// 0 - Forward direction at CW, 1 - Forward direction at CCW
	//wdat8 = 0;
	wdat8 = m_ExtSEnv2.ForkDrive.EncoderSetup.Dir;
	DLen = sizeof(wdat8); pData = (void*)&wdat8;
	retval += EC_SDOwrite(slave, 0x3001, 0x01, FALSE, DLen, pData, EC_TIMEOUT_STATE);

	// 0x4001 Encoder Input Setting
	// Set value 
	// 00 - Phase A/B pulse (Multiplication �� 1 cycle)
	// 01 - Phase A/B pulse (Multiplication �� 2 cycle)
	// 02 - Phase A/B pulse (Multiplication �� 4 cycle)
	// 03 - Code + pulse (Multiplication �� 1 cycle)
	// 04 - Incremental/decremental pulse
	//wdat8 = 2;
	wdat8 = m_ExtSEnv2.ForkDrive.EncoderSetup.Input_Pulse;
	DLen = sizeof(wdat8); pData = (void*)&wdat8;
	retval += EC_SDOwrite(slave, 0x3002, 0x01, FALSE, DLen, pData, EC_TIMEOUT_STATE);

	while (m_EcatError) printf("%s", ec_elist2string());

#if DEBUG_ETHERCAT_MSG
	printf("slave %d set, retval = %d\r\n", slave, retval);
#endif

	return 1;
}

int MX_EXT_setup(uint16 slave)
{
	uint8 rdat8;
	uint8 wdat8;
	uint16 rdat16;
	uint16 wdat16;
	//uint32 wdat32;
	//uint32 rdat32;

	void* pData;
	int DLen;

	int retval = 0;
	//uint16 u16val;

	// 0x4001 Encoder Direction
	// Set value 
	// 0 - Forward direction at CW, 1 - Forward direction at CCW
	//wdat8 = 0;
	wdat8 = m_ExtSEnv2.ForkDrive.EncoderSetup.Dir;
	DLen = sizeof(wdat8); pData = (void*)&wdat8;
	retval += EC_SDOwrite(slave, 0x3001, 0x01, FALSE, DLen, pData, EC_TIMEOUT_STATE);

	// 0x4001 Encoder Input Setting
	// Set value 
	// 00 - Phase A/B pulse (Multiplication �� 1 cycle)
	// 01 - Phase A/B pulse (Multiplication �� 2 cycle)
	// 02 - Phase A/B pulse (Multiplication �� 4 cycle)
	// 03 - Code + pulse (Multiplication �� 1 cycle)
	// 04 - Incremental/decremental pulse
	//wdat8 = 2;
	wdat8 = m_ExtSEnv2.ForkDrive.EncoderSetup.Input_Pulse;
	DLen = sizeof(wdat8); pData = (void*)&wdat8;
	retval += EC_SDOwrite(slave, 0x3002, 0x01, FALSE, DLen, pData, EC_TIMEOUT_STATE);

	while (m_EcatError) printf("%s", ec_elist2string());

#if DEBUG_ETHERCAT_MSG
	printf("slave %d set, retval = %d\r\n", slave, retval);
#endif

	return 1;
}

int MX_EXT_setup_1(uint16 slave)
{
	// RxPDO Map
	// Index,		Name,						Type
	// 6200.02		Output 1st byte				U8
	// 3020.00		Encoder Instruction Bits	U8	
	// 3011.00		Encoder Preset Valu			U32
	uint32 RxPDOmap_1701[3] = { 0x62000208, 0x30200008, 0x30110020 };
	uint8 nRxPDO_Count = 3;

	// TxPDO Map
	// Index,	Name,							Type
	// 6000.02	Input 1st byte					U8	
	// 3030.00	Encoder Status Bits				U8
	// 3010.00	Encoder Position Value			U32	
	uint32 TxPDOmap_1B01[3] = { 0x60000208, 0x30300008, 0x30100020 };
	uint8 nTxPDO_Count = 3;

	// map velocity
	uint16 map_1c12[2] = { 0x0001, 0x1701 };
	uint16 map_1c13[2] = { 0x0001, 0x1B01 };

	uint8 i = 0;

	uint8 rdat8 = 0;
	uint8 wdat8 = 0;
	uint16 rdat16 = 0;
	uint16 wdat16 = 0;
	//uint32 wdat32;
	//uint32 rdat32;

	void* pRdat;
	int rdl;

	void* pData;
	int DLen = 0;

	int retval = 0;
	//uint16 u16val;

	/*
	// 0x3001.00 Encoder Direction
	// Set value
	// 0 - Forward direction at CW, 1 - Forward direction at CCW
	//wdat8 = 0;
	//wdat8 = m_ExtSEnv2.ForkDrive.EncoderSetup.Dir;
	wdat8 = 1;
	DLen = sizeof(wdat8); pData = (void*)&wdat8;
	//retval += EC_SDOwrite(slave, 0x3001, 0x01, FALSE, DLen, pData, EC_TIMEOUT_STATE);
	retval += EC_SDOwrite(slave, 0x3001, 0x00, FALSE, DLen, pData, EC_TIMEOUT_STATE);

	// 0x3002.00 Encoder Input Setting
	// Set value
	// 00 - Phase A/B pulse (Multiplication �� 1 cycle)
	// 01 - Phase A/B pulse (Multiplication �� 2 cycle)
	// 02 - Phase A/B pulse (Multiplication �� 4 cycle)
	// 03 - Code + pulse (Multiplication �� 1 cycle)
	// 04 - Incremental/decremental pulse
	//wdat8 = 2;
	//wdat8 = m_ExtSEnv2.ForkDrive.EncoderSetup.Input_Pulse;
	wdat8 = 4;
	DLen = sizeof(wdat8); pData = (void*)&wdat8;
	//retval += EC_SDOwrite(slave, 0x3002, 0x01, FALSE, DLen, pData, EC_TIMEOUT_STATE);
	retval += EC_SDOwrite(slave, 0x3002, 0x00, FALSE, DLen, pData, EC_TIMEOUT_STATE);
	*/

	///*
	wdat8 = 0x00;
	rdl = sizeof(wdat8); pRdat = (void*)&wdat8;
	retval += EC_SDOwrite(1, 0x1C12, 0, FALSE, rdl, pRdat, EC_TIMEOUT_TXM);

	wdat8 = 0x00;
	rdl = sizeof(wdat8); pRdat = (void*)&wdat8;
	retval += EC_SDOwrite(1, 0x1C13, 0, FALSE, rdl, pRdat, EC_TIMEOUT_TXM);
	//*/

	wdat8 = 0x00;
	rdl = sizeof(wdat8); pRdat = (void*)&wdat8;
	retval += EC_SDOwrite(1, 0x1701, 0, FALSE, rdl, pRdat, EC_TIMEOUT_TXM);

	for (i = 1; i < (nRxPDO_Count + 1); i++)
	{
		retval += EC_SDOwrite(slave, 0x1701, i, FALSE, sizeof(INT32U), &RxPDOmap_1701[i - 1], EC_TIMEOUT_RXM);
	}

	wdat8 = nRxPDO_Count;
	rdl = sizeof(wdat8); pRdat = (void*)&wdat8;
	retval += EC_SDOwrite(1, 0x1701, 0, FALSE, rdl, pRdat, EC_TIMEOUT_TXM);

	wdat8 = 0x00;
	rdl = sizeof(wdat8); pRdat = (void*)&wdat8;
	retval += EC_SDOwrite(1, 0x1B01, 0, FALSE, rdl, pRdat, EC_TIMEOUT_TXM);

	for (i = 1; i < (nTxPDO_Count + 1); i++)
	{
		retval += EC_SDOwrite(slave, 0x1B01, i, FALSE, sizeof(INT32U), &TxPDOmap_1B01[i - 1], EC_TIMEOUT_RXM);
	}

	wdat8 = nTxPDO_Count;
	rdl = sizeof(wdat8); pRdat = (void*)&wdat8;
	retval += EC_SDOwrite(1, 0x1B01, 0, FALSE, rdl, pRdat, EC_TIMEOUT_TXM);

	retval += EC_SDOwrite(slave, 0x1c12, 1, FALSE, sizeof(INT16U), &map_1c12[1], EC_TIMEOUT_RXM);
	retval += EC_SDOwrite(slave, 0x1c12, 0, FALSE, sizeof(INT08U), &map_1c12[0], EC_TIMEOUT_RXM);

	retval += EC_SDOwrite(slave, 0x1c13, 1, FALSE, sizeof(INT16U), &map_1c13[1], EC_TIMEOUT_RXM);
	retval += EC_SDOwrite(slave, 0x1c13, 0, FALSE, sizeof(INT08U), &map_1c13[0], EC_TIMEOUT_RXM);

	///*
	// 0x3001.00 Encoder Direction
	// Set value 
	// 0 - Forward direction at CW, 1 - Forward direction at CCW
	wdat8 = 1;
	//wdat8 = m_ExtSEnv2.ForkDrive.EncoderSetup.Dir;
	DLen = sizeof(wdat8); pData = (void*)&wdat8;
	//retval += EC_SDOwrite(slave, 0x3001, 0x01, FALSE, DLen, pData, EC_TIMEOUT_STATE);
	retval += EC_SDOwrite(slave, 0x3001, 0x00, FALSE, DLen, pData, EC_TIMEOUT_STATE);

	// 0x3002.00 Encoder Input Setting
	// Set value 
	// 00 - Phase A/B pulse (Multiplication �� 1 cycle)
	// 01 - Phase A/B pulse (Multiplication �� 2 cycle)
	// 02 - Phase A/B pulse (Multiplication �� 4 cycle)
	// 03 - Code + pulse (Multiplication �� 1 cycle)
	// 04 - Incremental/decremental pulse
	wdat8 = 2;
	//wdat8 = m_ExtSEnv2.ForkDrive.EncoderSetup.Input_Pulse;
	DLen = sizeof(wdat8); pData = (void*)&wdat8;
	//retval += EC_SDOwrite(slave, 0x3002, 0x01, FALSE, DLen, pData, EC_TIMEOUT_STATE);
	retval += EC_SDOwrite(slave, 0x3002, 0x00, FALSE, DLen, pData, EC_TIMEOUT_STATE);
	//*/

	while (m_EcatError) printf("%s", ec_elist2string());

#if DEBUG_ETHERCAT_MSG
	printf("slave %d set, retval = %d\r\n", slave, retval);
#endif

	return 1;
}

int MX_Slave_setup(uint16 slave)
{
	uint8 rdat8;
	//uint8 wdat8;

	//uint16 rdat16;
	//uint16 wdat16;

	void* pData;
	int DLen;

	int retval = 0;

	if (slave > 10)	return 0;

	// Read Board Type
	DLen = sizeof(rdat8); pData = (void*)&rdat8;
	retval += EC_SDOread(slave, 0x2000, 0x00, FALSE, &DLen, pData, EC_TIMEOUT_STATE);

	//m_DIO_SetInfo.Scan[slave - 1].SlaveID = rdat8;

	while (m_EcatError) printf("%s", ec_elist2string());

#if DEBUG_ETHERCAT_MSG
	printf("slave %d set, retval = %d\r\n", slave, retval);
#endif

	return 1;
}

int GX_EX_GetErrorCode(uint16 slave)
{
	uint8 rdat8;
	//uint8 wdat8;
	//uint16 rdat16;
	//uint16 wdat16;
	//uint32 wdat32;
	//uint32 rdat32;

	void* pRdat;
	int rdl;

	//int retval = 0, i = 0;
	//uint16 u16val;

	rdat8 = 0;
	rdl = sizeof(rdat8); pRdat = (void*)&rdat8;
	EC_SDOread(slave, 0x2002, 0x01, FALSE, &rdl, pRdat, EC_TIMEOUT_STATE);

#if DEBUG_ETHERCAT_MSG
	printf("[EtherCAT] Sysmac error status : 0x%02x\r\n", rdat8);
#endif

	return 1;
}

INT08U ec_init()
{
	int wkc = 0, i;

	//wkc = ECAT_Config(FALSE, &IOmap);
	wkc = ECAT_Config();

	if (m_EC_SlaveCount >= 1)
	{
		for (i = 1; i <= m_EC_SlaveCount; i++)
		{
			if ((m_EC_Slave[i].eep_man == 0x000000b7) && (m_EC_Slave[i].eep_id == 0x00000264))
			{
#if DEBUG_ETHERCAT_MSG
				printf("Found Name : %s at position : %d\r\n", m_EC_Slave[i].name, i);
#endif
				// link slave specific setup to preop->safeop hook
				m_EC_Slave[i].PO2SOconfig = &ABB_ACS380_setup;
			}
			else if ((m_EC_Slave[i].eep_man == 0x00000083) && (m_EC_Slave[i].eep_id == 0x00000051))
			{
#if DEBUG_ETHERCAT_MSG
				printf("Found Name : %s at position : %d\r\n", m_EC_Slave[i].name, i);
#endif
				m_EC_Slave[i].PO2SOconfig = &GX_EC0211_setup;
			}
			else if ((m_EC_Slave[i].eep_man == 0x00000AB0) && (m_EC_Slave[i].eep_id == 0x00030101))
			{
#if DEBUG_ETHERCAT_MSG
				printf("Found Name : %s at position : %d\r\n", m_EC_Slave[i].name, i);
#endif
				m_EC_Slave[i].PO2SOconfig = &MX_EXT_setup;
				//m_EC_Slave[i].PO2SOconfig = &MX_EXT_setup_1;
				asm volatile("NOP");
			}
			else if ((m_EC_Slave[i].eep_man == 0x00000AB0) && (m_EC_Slave[i].eep_id == 0x00010101))
			{
#if DEBUG_ETHERCAT_MSG
				printf("Found Name : %s at position : %d\r\n", m_EC_Slave[i].name, i);
#endif
				//ec_slave[slc].PO2SOconfig = &MX_Slave_setup;
			}
		}

		asm volatile("NOP");
	}

	if (wkc)
	{
		ECAT_Config_Map(&m_IOmap);

		ECAT_ConfigDC();
	}

	return wkc;
}


int64 m_Diff_DCTime = 0;
int64 m_Max_DCtime = 0;

INT08U m_Update_TxPDO;

void ECAT_Com_Process()
{
	static INT32U s_IntervalTimer = 0;
	static int64 s_Pre_DCtime;

	if (m_ProcessData_Flag)
	{
		// Process Time : 140.7us
		//HAL_GPIO_WritePin(CPU_RUN_LED_GPIO_Port, CPU_RUN_LED_Pin, GPIO_PIN_RESET);

		//m_TestStatus.St[DEBUG_STR_30] = getCalcTimer100us(s_IntervalTimer);

		s_Pre_DCtime = m_EC_DCtime;

		EC_Send_ProcessData(0);

		if (m_EC_Main.DisconnectFlag)
		{
#if DEBUG_ETHERCAT_MSG
			printf("[EtherCAT] Disconnect EtherCAT cable.\r\n");
#endif
			m_ProcessData_Flag = 0;

			__HAL_TIM_DISABLE(&htim4);
			__HAL_TIM_DISABLE_IT(&htim4, TIM_IT_UPDATE);
		}
		else
		{
			m_Diff_DCTime = m_EC_DCtime - s_Pre_DCtime;

			s_IntervalTimer = m_pgmEnv.timer100us;

			m_Update_TxPDO = 1;
		}

		//HAL_GPIO_WritePin(CPU_RUN_LED_GPIO_Port, CPU_RUN_LED_Pin, GPIO_PIN_SET);
	}
}

/*
void EtherCAT_Input_Test()
{
	INT08U i = 0;

	m_TestStatus.St[DEBUG_STR_19] = ec_slavecount;

	for (i = 1; i <= ec_slavecount; i++)
	{
		if (((ec_slave[i].eep_man == 0x00000083) && (ec_slave[i].eep_id == 0x0000003A))
			|| ((ec_slave[i].eep_man == 0x00000083) && (ec_slave[i].eep_id == 0x00000032))
			|| ((ec_slave[i].eep_man == 0x00000083) && (ec_slave[i].eep_id == 0x00000040)))
		{
			memcpy((INT08U*)&m_TestStatus.St[DEBUG_STR_19 + i], (INT08U*)ec_slave[i].inputs,
				sizeof(INT08U) * ec_slave[i].Ibytes);
		}
		else if ((ec_slave[i].eep_man == 0x00000959) && (ec_slave[i].eep_id == 0x01001201))
		{
			memcpy((INT08U*)&m_TestStatus.St[DEBUG_STR_19 + i], (INT08U*)ec_slave[i].inputs,
				sizeof(INT08U) * 4);
		}
	}
}
*/

void EtherCAT_Output_Test()
{
	static INT08U s_Init;
	static INT32U s_Timer;

	if (!s_Init)
	{
		s_Init = 1;
		s_Timer = m_pgmEnv.timer100us;
	}
	else
	{
		if (getCalcTimer100us(s_Timer) >= 20)	// 5ms
		{
			*((INT16U*)m_EC_Slave[1].outputs) ^= cbits16[0];

			s_Timer = m_pgmEnv.timer100us;
		}
	}
}

void External_Encoder_Proc()
{
	static INT32U s_chkTimer = 0;
	static INT08U s_Step = 0;

	static INT32U s_ReadFail = 0, s_MaxReadFail_Continue = 0;
	static INT08U s_Slave_Idx = 0;

	INT08U i = 0;

	INT32S nReadEncoder = 0;
	double nClacPosition = 0;
	double nPulseDistance = 0;

	if (s_Step >= 2)
	{
		memcpy((INT08U*)&m_Enx_TxPDO, (INT08U*)m_EC_Slave[s_Slave_Idx].inputs, sizeof(EncoderTxPDO));
	}

	switch (s_Step)
	{
	case 0:
		if (m_pgmEnv.EtherCAT_Connection)
		{
			// Scan GX-EX2011 Slave Index
			s_Slave_Idx = 0;
			for (i = 1; i <= m_EC_SlaveCount; i++)
			{
				if ((m_EC_Slave[i].eep_man == 0x00000083)
					&& (m_EC_Slave[i].eep_id == 0x00000051))
				{
					s_Slave_Idx = i;
					break;
				}
			}

			if (s_Slave_Idx == 0)
			{
#if DEBUG_ETHERCAT_EC_MODULE
				printf("[EtherCAT] GX-EC0211 not found!\r\n");
#endif
				s_Step = 1;
			}
			else
			{
#if DEBUG_ETHERCAT_EC_MODULE
				printf("[EtherCAT] GX-EC0211 Slave No:%d, eep_man:0x%08lx, eep_id:0x0x%08lx Alias_adr:0x%02x\r\n",
					s_Slave_Idx, m_EC_Slave[s_Slave_Idx].eep_man, m_EC_Slave[s_Slave_Idx].eep_id, m_EC_Slave[s_Slave_Idx].aliasadr);
#endif
				memset((INT08U*)&m_Enx_RxPDO, 0, sizeof(EncoderRxPDO));

				if (m_ExtSEnv.Machine.mType.Fork_Sensor_Type & cbits[0])
				{
					// 포크위치센서 구성 - 로터리 엔코더 적용
					s_Step = 2;
				}
				else
				{
					// 포크위치센서 구성 - 로터리 엔코더 미적용
					s_Step = 1;
				}
			}
		}
		break;

	case 1:
		// EC Module not found.
		break;

	case 2:
		m_Enx_RxPDO.Ch1_Preset_Value = 50000;
#if DEBUG_ETHERCAT_EC_MODULE
		printf("[EtherCAT] GX-EC0211 Set Ch1_Preset_Value : %ld \r\n", m_Enx_RxPDO.Ch1_Preset_Value);
#endif
		s_chkTimer = m_pgmEnv.timer1ms;
		s_Step = 3;
		break;

	case 3:
		if (getCalcTimer1ms(s_chkTimer) > 50)
		{
			m_Enx_RxPDO.Ch1_Switch0 |= cbits[1];	// PSET1
#if DEBUG_ETHERCAT_EC_MODULE
			printf("[EtherCAT] GX-EC0211 Present value preset execution : 0x%02x \r\n",
				m_Enx_RxPDO.Ch1_Switch0);
#endif
			s_chkTimer = m_pgmEnv.timer1ms;
			s_Step = 4;
		}
		break;

	case 4:
		if (getCalcTimer1ms(s_chkTimer) > 100)
		{
			if (m_Enx_TxPDO.Ch1_Counter_Status & cbits[0])
			{
				if (m_Enx_TxPDO.Ch1_Present_Value == m_Enx_RxPDO.Ch1_Preset_Value)
				{
					m_Enx_RxPDO.Ch1_Switch0 &= nbits[1];	// PSET1 Clear
#if DEBUG_ETHERCAT_EC_MODULE
					printf("[EtherCAT] GX-EC0211 Present value : %ld \r\n",
						m_Enx_TxPDO.Ch1_Present_Value);
#endif
					s_Step = 5;
				}
			}
			else
			{
				m_Enx_RxPDO.Ch1_Switch0 &= nbits[1];	// PSET1 Clear

				s_Step = 3;
			}

			s_chkTimer = m_pgmEnv.timer1ms;
		}
		break;

	case 5:
		if (getCalcTimer1ms(s_chkTimer) > 100)
		{
			m_Enx_RxPDO.Ch1_Switch0 |= cbits[0];	// CENB1 Set
#if DEBUG_ETHERCAT_EC_MODULE
			printf("[EtherCAT] GX-EC0211 Counter operation enable : 0x%02x \r\n",
				m_Enx_RxPDO.Ch1_Switch0);
#endif

			s_chkTimer = m_pgmEnv.timer1ms;

			s_Step = 6;
		}
		break;

	case 6:
		if (getCalcTimer1ms(s_chkTimer) > 100)
		{
			if (m_Enx_TxPDO.Ch1_Counter_Status | 0x80)
			{
#if DEBUG_ETHERCAT_EC_MODULE
				printf("[EtherCAT] GX-EC0211 Counter operation status : 0x%02x \r\n",
					m_Enx_TxPDO.Ch1_Counter_Status);
#endif
				s_Step = 7;
			}
			else
			{
				s_Step = 5;
			}
		}
		break;

	case 7:
		if (!m_pgmEnv.EtherCAT_Connection)
		{
			s_Step = 0;
			break;
		}

		if (m_Update_TxPDO)
		{
			m_Update_TxPDO = 0;
			//++m_TestStatus.Ctrl[DEBUG_CTR_1];

			if (m_Enx_TxPDO.Ch1_Counter_Status & 0x80)
			{
				INT32U nSetPreset = 0;

				if (m_ExtSEnv2.ForkDrive.EncoderSetup.Preset_Count)
				{
					nSetPreset = m_ExtSEnv2.ForkDrive.EncoderSetup.Preset_Count;
				}
				else
				{
					nSetPreset = 50000;
				}
				nReadEncoder = (INT32S)m_Enx_TxPDO.Ch1_Present_Value - nSetPreset;
				//m_TestStatus.Ctrl[DEBUG_CTR_6] = nReadEncoder;

				//double nPulseDistance = 0.124243;

				///*
				if (m_ExtSEnv2.ForkDrive.EncoderSetup.Pulse_Distance)
				{
					nPulseDistance = m_ExtSEnv2.ForkDrive.EncoderSetup.Pulse_Distance * 0.000001;
				}
				else
				{
					nPulseDistance = 0.124243;
				}
				//*/
				nClacPosition = (double)nReadEncoder * nPulseDistance;	// pulse 1 : 0.124243
				//nClacPosition = (double)nReadEncoder * 0.1242431640625;	// pulse 1 : 0.124243

				m_St.Inv_St[INV_FORK_1].Current_Pos = (INT32S)nClacPosition;

				s_ReadFail = 0;
			}
			else
			{
				/*
				if (m_Enx_RxPDO.Ch1_Switch0 & cbits[0])
				{
					++s_ReadFail;
					if (s_MaxReadFail_Continue < s_ReadFail)
					{
						s_MaxReadFail_Continue = s_ReadFail;
						m_TestStatus.Ctrl[DEBUG_CTR_2] = s_MaxReadFail_Continue;
					}

					if (s_ReadFail == 2)
					{
						++m_TestStatus.Ctrl[DEBUG_CTR_3];
					}
					else if (s_ReadFail == 3)
					{
						++m_TestStatus.Ctrl[DEBUG_CTR_4];
					}
					else if (s_ReadFail >= 4)
					{
						++m_TestStatus.Ctrl[DEBUG_CTR_5];
					}
				}
				*/
			}
		}
		break;

	default:
		break;
	}

	//m_TestStatus.Ctrl[DEBUG_CTR_4] = s_Step;
	//m_TestStatus.Ctrl[DEBUG_CTR_5] = s_Slave_Idx;

	if (s_Step >= 2)
	{
		memcpy((INT08U*)m_EC_Slave[s_Slave_Idx].outputs, (INT08U*)&m_Enx_RxPDO, sizeof(EncoderRxPDO));
	}
}

void MX_Ext_Encoder_Proc_1()
{
	static INT32U s_chkTimer = 0;
	static INT08U s_Step = 0;

	static INT32U s_ReadFail = 0, s_MaxReadFail_Continue = 0;
	static INT08U s_Slave_Idx = 0;

	INT08U i = 0;

	INT32S nReadEncoder = 0;
	double nClacPosition = 0;
	double nPulseDistance = 0;

	if (s_Step >= 2)
	{
		memcpy((INT08U*)&m_Enx_TxPDO_1, (INT08U*)m_EC_Slave[s_Slave_Idx].inputs, sizeof(EncoderTxPDO_1));
	}

	switch (s_Step)
	{
	case 0:
		if (m_pgmEnv.EtherCAT_Connection)
		{
			// Scan MX_EXT Slave Index
			s_Slave_Idx = 0;
			for (i = 1; i <= m_EC_SlaveCount; i++)
			{
				if ((m_EC_Slave[i].eep_man == 0x00000AB0)
					&& (m_EC_Slave[i].eep_id == 0x00030101)
					/* && (ec_slave[i].aliasadr == 15)*/)
				{
					s_Slave_Idx = i;
					break;
				}
			}

			if (s_Slave_Idx == 0)
			{
#if DEBUG_ETHERCAT_EC_MODULE
				printf("[EtherCAT] MX_EXT not found!\r\n");
#endif
				s_Step = 1;
			}
			else
			{
#if DEBUG_ETHERCAT_EC_MODULE
				printf("[EtherCAT] MX_EXT Slave No:%d, eep_man:0x%08lx, eep_id:0x0x%08lx Alias_adr:0x%02x\r\n",
					s_Slave_Idx, m_EC_Slave[s_Slave_Idx].eep_man, m_EC_Slave[s_Slave_Idx].eep_id, m_EC_Slave[s_Slave_Idx].aliasadr);
#endif
				memset((INT08U*)&m_Enx_RxPDO_1, 0, sizeof(EncoderRxPDO_1));
				s_Step = 2;
			}
		}
		break;

	case 1:
		// MX_EXT Module not found.
		break;

	case 2:
		m_Enx_RxPDO_1.Preset_Value = 50000;
#if DEBUG_ETHERCAT_EC_MODULE
		printf("[EtherCAT] MX_EXT Set Preset_Value : %ld \r\n", m_Enx_RxPDO_1.Preset_Value);
#endif
		s_chkTimer = m_pgmEnv.timer1ms;
		s_Step = 3;
		break;

	case 3:
		if (getCalcTimer1ms(s_chkTimer) > 50)
		{
			m_Enx_RxPDO_1.Switch |= cbits[1];	// PSET1
#if DEBUG_ETHERCAT_EC_MODULE
			printf("[EtherCAT] MX_EXT Present value preset execution : 0x%02x \r\n",
				m_Enx_RxPDO_1.Switch);
#endif
			s_chkTimer = m_pgmEnv.timer1ms;
			s_Step = 4;
		}
		break;

	case 4:
		if (getCalcTimer1ms(s_chkTimer) > 100)
		{
			if (m_Enx_TxPDO_1.Counter_Status & cbits[1])
			{
				if (m_Enx_TxPDO_1.Present_Value == m_Enx_RxPDO_1.Preset_Value)
				{
					m_Enx_RxPDO_1.Switch &= nbits[1];	// PSET1 Clear
#if DEBUG_ETHERCAT_EC_MODULE
					printf("[EtherCAT] MX_EXT Present value : %ld \r\n",
						m_Enx_TxPDO_1.Present_Value);
#endif
					s_Step = 5;
				}
			}
			else
			{
				m_Enx_RxPDO_1.Switch &= nbits[1];	// PSET1 Clear

				s_Step = 3;
			}

			s_chkTimer = m_pgmEnv.timer1ms;
		}
		break;

	case 5:
		if (getCalcTimer1ms(s_chkTimer) > 100)
		{
			m_Enx_RxPDO_1.Switch |= cbits[0];	// CENB1 Set
#if DEBUG_ETHERCAT_EC_MODULE
			printf("[EtherCAT] MX_EXT Counter operation enable : 0x%02x \r\n",
				m_Enx_RxPDO_1.Switch);
#endif
			s_chkTimer = m_pgmEnv.timer1ms;
			s_Step = 6;
		}
		break;

	case 6:
		if (getCalcTimer1ms(s_chkTimer) > 100)
		{
			if (m_Enx_TxPDO_1.Counter_Status | 0x01)
			{
#if DEBUG_ETHERCAT_EC_MODULE
				printf("[EtherCAT] MX_EXT Counter operation status : 0x%02x \r\n",
					m_Enx_TxPDO_1.Counter_Status);
#endif
				s_Step = 7;
			}
			else
			{
				s_Step = 5;
			}
		}
		break;

	case 7:
		if (!m_pgmEnv.EtherCAT_Connection)
		{
			s_Step = 0;
			break;
		}

		if (m_Update_TxPDO)
		{
			m_Update_TxPDO = 0;
			//++m_TestStatus.Ctrl[DEBUG_CTR_1];

			if (m_Enx_TxPDO_1.Counter_Status & 0x01)
			{
				INT32U nSetPreset = 0;

				if (m_ExtSEnv2.ForkDrive.EncoderSetup.Preset_Count)
				{
					nSetPreset = m_ExtSEnv2.ForkDrive.EncoderSetup.Preset_Count;
				}
				else
				{
					nSetPreset = 50000;
				}
				nReadEncoder = (INT32S)m_Enx_TxPDO_1.Present_Value - nSetPreset;
				//m_TestStatus.Ctrl[DEBUG_CTR_6] = nReadEncoder;

				if (m_ExtSEnv2.ForkDrive.EncoderSetup.Pulse_Distance)
				{
					nPulseDistance = m_ExtSEnv2.ForkDrive.EncoderSetup.Pulse_Distance * 0.000001;
				}
				else
				{
					nPulseDistance = 0.124243;
				}

				nClacPosition = (double)nReadEncoder * nPulseDistance;	// pulse 1 : 0.124243

				m_St.Inv_St[INV_FORK_1].Current_Pos = (INT32S)nClacPosition;

				s_ReadFail = 0;
			}
			else
			{
				/*
				if (m_Enx_RxPDO_1.Switch & cbits[0])
				{
					++s_ReadFail;
					if (s_MaxReadFail_Continue < s_ReadFail)
					{
						s_MaxReadFail_Continue = s_ReadFail;
						m_TestStatus.Ctrl[DEBUG_CTR_2] = s_MaxReadFail_Continue;
					}

					if (s_ReadFail == 2)
					{
						++m_TestStatus.Ctrl[DEBUG_CTR_3];
					}
					else if (s_ReadFail == 3)
					{
						++m_TestStatus.Ctrl[DEBUG_CTR_4];
					}
					else if (s_ReadFail >= 4)
					{
						++m_TestStatus.Ctrl[DEBUG_CTR_5];
					}
				}
				*/
			}
		}
		break;

	default:
		break;
	}

	//m_TestStatus.Ctrl[DEBUG_CTR_4] = s_Step;
	//m_TestStatus.Ctrl[DEBUG_CTR_5] = s_Slave_Idx;

	if (s_Step >= 2)
	{
		memcpy((INT08U*)m_EC_Slave[s_Slave_Idx].outputs, (INT08U*)&m_Enx_RxPDO_1, sizeof(EncoderRxPDO_1));
	}

	/*
	m_TestStatus.St[DEBUG_STR_1] = s_Step;
	m_TestStatus.St[DEBUG_STR_2] = s_Slave_Idx;

	m_TestStatus.St[DEBUG_STR_3] = m_Enx_RxPDO_1.Switch;
	m_TestStatus.St[DEBUG_STR_4] = m_Enx_RxPDO_1.Preset_Value;

	m_TestStatus.St[DEBUG_STR_5] = m_Enx_TxPDO_1.DI;
	m_TestStatus.St[DEBUG_STR_6] = m_Enx_TxPDO_1.Counter_Status;
	m_TestStatus.St[DEBUG_STR_7] = m_Enx_TxPDO_1.Present_Value;
	*/
}

void MX_EXT_Proc()
{
	static INT32U s_chkTimer = 0;
	static INT08U s_Step = 0;

	static INT32U s_ReadFail = 0, s_MaxReadFail_Continue = 0;
	static INT08U s_Slave_Idx = 0;

	INT08U i = 0;

	INT32S nReadEncoder = 0;
	double nClacPosition = 0;
	double nPulseDistance = 0;

	//if (s_Step >= 2)
	if (s_Step >= 1)
	{
		memcpy((INT08U*)&m_MX_EXT_TxPDO, (INT08U*)m_EC_Slave[s_Slave_Idx].inputs, sizeof(MX_EXT_TxPDO));
	}

	switch (s_Step)
	{
	case 0:
		if (m_pgmEnv.EtherCAT_Connection)
		{
			// Scan MX_EXT Slave Index
			s_Slave_Idx = 0;
			for (i = 1; i <= m_EC_SlaveCount; i++)
			{
				if ((m_EC_Slave[i].eep_man == 0x00000AB0)
					&& (m_EC_Slave[i].eep_id == 0x00030101))
				{
					s_Slave_Idx = i;
					break;
				}
			}

			if (s_Slave_Idx == 0)
			{
#if DEBUG_ETHERCAT_EC_MODULE
				printf("[EtherCAT] MX_EXT not found!\r\n");
#endif
				s_Step = 1;
			}
			else
			{
#if DEBUG_ETHERCAT_EC_MODULE
				printf("[EtherCAT] MX_EXT Slave No:%d, eep_man:0x%08lx, eep_id:0x0x%08lx Alias_adr:0x%02x\r\n",
					s_Slave_Idx, m_EC_Slave[s_Slave_Idx].eep_man, m_EC_Slave[s_Slave_Idx].eep_id, m_EC_Slave[s_Slave_Idx].aliasadr);
#endif
				memset((INT08U*)&m_MX_EXT_RxPDO, 0, sizeof(MX_EXT_RxPDO));

				if (m_ExtSEnv.Machine.mType.Fork_Sensor_Type & cbits[0])
				{
					// 포크위치센서 구성 - 로터리 엔코더 적용
					s_Step = 2;
				}
				else
				{
					// 포크위치센서 구성 - 로터리 엔코더 미적용
					s_Step = 1;
				}
			}
		}
		break;

	case 1:
		// MX_EXT Module not found.
		break;

	case 2:
		m_MX_EXT_RxPDO.ENC_Preset_Value = 50000;
#if DEBUG_ETHERCAT_EC_MODULE
		printf("[EtherCAT] MX_EXT Set Preset_Value : %ld \r\n", m_MX_EXT_RxPDO.ENC_Preset_Value);
#endif
		s_chkTimer = m_pgmEnv.timer1ms;
		s_Step = 3;
		break;

	case 3:
		if (getCalcTimer1ms(s_chkTimer) > 50)
		{
			m_MX_EXT_RxPDO.ENC_Switch |= cbits[1];	// PSET1
#if DEBUG_ETHERCAT_EC_MODULE
			printf("[EtherCAT] MX_EXT Present value preset execution : 0x%02x \r\n",
				m_MX_EXT_RxPDO.ENC_Switch);
#endif


			s_chkTimer = m_pgmEnv.timer1ms;
			s_Step = 4;
		}
		break;

	case 4:
		if (getCalcTimer1ms(s_chkTimer) > 100)
		{
			if (m_MX_EXT_TxPDO.ENC_Status & cbits[1])
			{
				if (m_MX_EXT_TxPDO.ENC_Postion == m_MX_EXT_RxPDO.ENC_Preset_Value)
				{
					m_MX_EXT_RxPDO.ENC_Switch &= nbits[1];	// PSET1 Clear
#if DEBUG_ETHERCAT_EC_MODULE
					printf("[EtherCAT] MX_EXT Present value : %ld \r\n", \
						m_MX_EXT_TxPDO.ENC_Postion);
#endif
					s_Step = 5;
				}
			}
			else
			{
				m_MX_EXT_RxPDO.ENC_Switch &= nbits[1];	// PSET1 Clear

				s_Step = 3;
			}

			s_chkTimer = m_pgmEnv.timer1ms;
		}
		break;

	case 5:
		if (getCalcTimer1ms(s_chkTimer) > 100)
		{
			m_MX_EXT_RxPDO.ENC_Switch |= cbits[0];	// CENB1 Set
			m_MX_EXT_RxPDO.SSI_Switch |= cbits[0];	//
#if DEBUG_ETHERCAT_EC_MODULE
			printf("[EtherCAT] MX_EXT Counter operation enable : 0x%02x \r\n",
				m_MX_EXT_RxPDO.ENC_Switch);
#endif
			s_chkTimer = m_pgmEnv.timer1ms;
			s_Step = 6;
		}
		break;

	case 6:
		if (getCalcTimer1ms(s_chkTimer) > 100)
		{
			if (m_MX_EXT_TxPDO.ENC_Status | 0x01)
			{
#if DEBUG_ETHERCAT_EC_MODULE
				printf("[EtherCAT] MX_EXT Counter operation status : 0x%02x \r\n",
					m_MX_EXT_TxPDO.ENC_Status);
#endif
				s_Step = 7;
			}
			else
			{
				s_Step = 5;
			}
		}
		break;

	case 7:
		if (!m_pgmEnv.EtherCAT_Connection)
		{
			s_Step = 0;
			break;
		}

		if (m_Update_TxPDO)
		{
			m_Update_TxPDO = 0;

			if (m_MX_EXT_TxPDO.ENC_Status & 0x01)
			{
				INT32U nSetPreset = 0;

				if (m_ExtSEnv2.ForkDrive.EncoderSetup.Preset_Count)
				{
					nSetPreset = m_ExtSEnv2.ForkDrive.EncoderSetup.Preset_Count;
				}
				else
				{
					nSetPreset = 50000;
				}
				nReadEncoder = (INT32S)m_Enx_TxPDO_1.Present_Value - nSetPreset;

				if (m_ExtSEnv2.ForkDrive.EncoderSetup.Pulse_Distance)
				{
					nPulseDistance = m_ExtSEnv2.ForkDrive.EncoderSetup.Pulse_Distance * 0.000001;
				}
				else
				{
					nPulseDistance = 0.124243;
				}

				nClacPosition = (double)nReadEncoder * nPulseDistance;	// pulse 1 : 0.124243

				m_St.Inv_St[INV_FORK_1].Current_Pos = (INT32S)nClacPosition;

				s_ReadFail = 0;
			}
			else
			{

			}
		}
		break;

	default:
		break;
	}

	//m_TestStatus.Ctrl[DEBUG_CTR_4] = s_Step;
	//m_TestStatus.Ctrl[DEBUG_CTR_5] = s_Slave_Idx;

	if (s_Step >= 2)
	{
		memcpy((INT08U*)m_EC_Slave[s_Slave_Idx].outputs, (INT08U*)&m_MX_EXT_RxPDO, sizeof(MX_EXT_RxPDO));
	}

	/*
	m_TestStatus.St[DEBUG_STR_1] = s_Step;
	m_TestStatus.St[DEBUG_STR_2] = s_Slave_Idx;

	m_TestStatus.St[DEBUG_STR_3] = m_MX_EXT_TxPDO.DI;
	m_TestStatus.St[DEBUG_STR_4] = m_MX_EXT_TxPDO.ENC_Status;
	m_TestStatus.St[DEBUG_STR_5] = m_MX_EXT_TxPDO.ENC_Postion;
	m_TestStatus.St[DEBUG_STR_6] = m_MX_EXT_TxPDO.SSI_Postion;

	m_TestStatus.St[DEBUG_STR_7] = m_MX_EXT_RxPDO.DO;
	m_TestStatus.St[DEBUG_STR_8] = m_MX_EXT_RxPDO.ENC_Switch;
	m_TestStatus.St[DEBUG_STR_9] = m_MX_EXT_RxPDO.ENC_Preset_Value;
	m_TestStatus.St[DEBUG_STR_10] = m_MX_EXT_RxPDO.SSI_Switch;
	m_TestStatus.St[DEBUG_STR_11] = m_MX_EXT_RxPDO.PTO_Freq;
	*/
}

/**
  * @brief  이더켓 슬레이브 연결상태 확인
  * @retval None
  */
void Check_EtherCAT_Slave_Connection()
{
	static INT32U s_ChkTime;
	INT08U i = 0;

	if (getCalcTimer1ms(s_ChkTime) > 100)
	{
		for (i = 1; i <= m_EC_SlaveCount; i++)
		{
			if ((m_EC_Slave[i].state != 0) && (m_EC_Slave[i].state != EC_STATE_INIT))
			{
				m_DevStatus.mLinkStatus.EtherCAT_Slave |= cbits16[i - 1];
			}
			else
			{
				m_DevStatus.mLinkStatus.EtherCAT_Slave &= ~cbits16[i - 1];
			}
		}

		s_ChkTime = m_pgmEnv.timer1ms;
	}
}

/**
  * @brief
  * @retval None
  */
void Check_ECAT_Slave_Name()
{
	for (INT08U i = 1; i < (m_EC_SlaveCount + 1); i++)
	{
		m_DIO_SetInfo.Scan[i - 1].Alias_Addr = m_EC_Slave[i].aliasadr;

#if DEBUG_ETHERCAT_MSG
		printf("[EtherCAT] Slave No:%d, eep_man:0x%08lx, eep_id:0x%08lx\r\n",
			i, m_EC_Slave[i].eep_man, m_EC_Slave[i].eep_id);
#endif
		if ((m_EC_Slave[i].eep_man == 0x00000083) && (m_EC_Slave[i].eep_id == 0x00000051))
		{
			m_DIO_SetInfo.Scan[i - 1].SlaveID = GX_EC0211;

			// Omron Encoder Unit
			ECAT_Dcsync0(i, TRUE, SYNC0TIME, 0); // SYNC0 on slave
		}
		else if ((m_EC_Slave[i].eep_man == 0x00000083) && (m_EC_Slave[i].eep_id == 0x0000003A))
		{
			m_DIO_SetInfo.Scan[i - 1].SlaveID = GX_ID1618;
		}
		else if ((m_EC_Slave[i].eep_man == 0x00000083) && (m_EC_Slave[i].eep_id == 0x00000032))
		{
			m_DIO_SetInfo.Scan[i - 1].SlaveID = GX_MD1611;
		}
		else if ((m_EC_Slave[i].eep_man == 0x00000083) && (m_EC_Slave[i].eep_id == 0x00000033))
		{
			m_DIO_SetInfo.Scan[i - 1].SlaveID = GX_MD1621;
		}
		else if ((m_EC_Slave[i].eep_man == 0x00000083) && (m_EC_Slave[i].eep_id == 0x00000040))
		{
			m_DIO_SetInfo.Scan[i - 1].SlaveID = GX_ID3218;
		}
		else if ((m_EC_Slave[i].eep_man == 0x00000AB0) && (m_EC_Slave[i].eep_id == 0x00010101))
		{
			m_DIO_SetInfo.Scan[i - 1].SlaveID = MX_DIO_101;
		}
		else if ((m_EC_Slave[i].eep_man == 0x00000AB0) && (m_EC_Slave[i].eep_id == 0x00010201))
		{
			m_DIO_SetInfo.Scan[i - 1].SlaveID = MX_DIO_201;
		}
		else if ((m_EC_Slave[i].eep_man == 0x00000AB0) && (m_EC_Slave[i].eep_id == 0x00010301))
		{
			m_DIO_SetInfo.Scan[i - 1].SlaveID = MX_DIO_301;
		}
		else if ((m_EC_Slave[i].eep_man == 0x00000AB0) && (m_EC_Slave[i].eep_id == 0x00020101))
		{
			m_DIO_SetInfo.Scan[i - 1].SlaveID = MX_RLY_101;
		}
		else if ((m_EC_Slave[i].eep_man == 0x00000AB0) && (m_EC_Slave[i].eep_id == 0x00030101))
		{
			m_DIO_SetInfo.Scan[i - 1].SlaveID = MX_EXT_101;
		}
		else
		{
			m_DIO_SetInfo.Scan[i - 1].SlaveID = NOT_DEFINE;
		}
	}
}

/**
	@brief
	@details
	@date		2023/07/15
	@param
	@return		INT08U		이더켓 슬레이브 설정 확인
	@remarks
*/
INT08U Check_ECAT_Slave_Name_1()
{
	INT08U i;
	INT08U nErrorResult = 0;
	INT08U nSlaveCount = 0;

	for (INT08U i = 0; i < MAX_DIO_MODULE_CNT; i++)
	{
		if (m_DIO_SetInfo.Set.SlaveID[i])
		{
			++nSlaveCount;
		}
	}

	for (i = 1; i < (m_EC_SlaveCount + 1); i++)
	{
		m_DIO_SetInfo.Scan[i - 1].Alias_Addr = m_EC_Slave[i].aliasadr;

#if DEBUG_ETHERCAT_MSG
		printf("[EtherCAT] Slave No:%d, eep_man:0x%08lx, eep_id:0x%08lx\r\n",
			i, m_EC_Slave[i].eep_man, m_EC_Slave[i].eep_id);
#endif
		if ((m_EC_Slave[i].eep_man == 0x00000083) && (m_EC_Slave[i].eep_id == 0x00000051))
		{
			m_DIO_SetInfo.Scan[i - 1].SlaveID = GX_EC0211;

			// Omron Encoder Unit
			ECAT_Dcsync0(i, TRUE, SYNC0TIME, 0); // SYNC0 on slave
		}
		else if ((m_EC_Slave[i].eep_man == 0x00000083) && (m_EC_Slave[i].eep_id == 0x0000003A))
		{
			m_DIO_SetInfo.Scan[i - 1].SlaveID = GX_ID1618;
		}
		else if ((m_EC_Slave[i].eep_man == 0x00000083) && (m_EC_Slave[i].eep_id == 0x00000032))
		{
			m_DIO_SetInfo.Scan[i - 1].SlaveID = GX_MD1611;
		}
		else if ((m_EC_Slave[i].eep_man == 0x00000083) && (m_EC_Slave[i].eep_id == 0x00000033))
		{
			m_DIO_SetInfo.Scan[i - 1].SlaveID = GX_MD1621;
		}
		else if ((m_EC_Slave[i].eep_man == 0x00000083) && (m_EC_Slave[i].eep_id == 0x00000040))
		{
			m_DIO_SetInfo.Scan[i - 1].SlaveID = GX_ID3218;
		}
		else if ((m_EC_Slave[i].eep_man == 0x00000AB0) && (m_EC_Slave[i].eep_id == 0x00010101))
		{
			m_DIO_SetInfo.Scan[i - 1].SlaveID = MX_DIO_101;
		}
		else if ((m_EC_Slave[i].eep_man == 0x00000AB0) && (m_EC_Slave[i].eep_id == 0x00010201))
		{
			m_DIO_SetInfo.Scan[i - 1].SlaveID = MX_DIO_201;
		}
		else if ((m_EC_Slave[i].eep_man == 0x00000AB0) && (m_EC_Slave[i].eep_id == 0x00010301))
		{
			m_DIO_SetInfo.Scan[i - 1].SlaveID = MX_DIO_301;
		}
		else if ((m_EC_Slave[i].eep_man == 0x00000AB0) && (m_EC_Slave[i].eep_id == 0x00020101))
		{
			m_DIO_SetInfo.Scan[i - 1].SlaveID = MX_RLY_101;
		}
		else if ((m_EC_Slave[i].eep_man == 0x00000AB0) && (m_EC_Slave[i].eep_id == 0x00030101))
		{
			m_DIO_SetInfo.Scan[i - 1].SlaveID = MX_EXT_101;
		}
		else
		{
			m_DIO_SetInfo.Scan[i - 1].SlaveID = NOT_DEFINE;
		}
	}

	if (m_EC_SlaveCount == nSlaveCount)
	{
		for (i = 1; i < (m_EC_SlaveCount + 1); i++)
		{
			if (m_DIO_SetInfo.Scan[i - 1].SlaveID != m_DIO_SetInfo.Set.SlaveID[i - 1])
			{
				// Type 이상
				nErrorResult = 1;
				break;
			}

			if (m_DIO_SetInfo.Scan[i - 1].Alias_Addr != 0)
			{
				if (m_DIO_SetInfo.Scan[i - 1].Alias_Addr != i)
				{
					// Alias Address 이상
					nErrorResult = 2;
					break;
				}
			}
		}
	}
	else
	{
		nErrorResult = 3;
	}


	return nErrorResult;
}

/**
  * @brief
  * @param None
  * @retval None
  */
void EtherCAT_Output_Control_All_Off(void)
{
	INT08U nMaxSlaveCount = 0;
	INT08U i;

	if (*m_EC_Main.slavecount > 10)
	{
		nMaxSlaveCount = 10;
	}
	else
	{
		nMaxSlaveCount = *(INT08U*)m_EC_Main.slavecount;
	}

	memset((INT16U*)m_pgmEnv.EtherCAT_DO, 0, sizeof(INT16U) * 10);

	for (i = 1; i <= nMaxSlaveCount; i++)
	{
		if ((m_EC_Slave[i].eep_man == 0x00000083) && (m_EC_Slave[i].eep_id == 0x00000032))
		{
			// GX-MD1611
			*(INT16U*)m_EC_Slave[i].outputs = m_pgmEnv.EtherCAT_DO[i - 1];
		}
		else if ((m_EC_Slave[i].eep_man == 0x00000083) && (m_EC_Slave[i].eep_id == 0x00000033))
		{
			// GX-MD1611
			*(INT16U*)m_EC_Slave[i].outputs = m_pgmEnv.EtherCAT_DO[i - 1];
		}
		else if ((m_EC_Slave[i].eep_man == 0x00000AB0) && (m_EC_Slave[i].eep_id == 0x00010201))
		{
			//MX-DIO-20x
			*(INT16U*)m_EC_Slave[i].outputs = m_pgmEnv.EtherCAT_DO[i - 1];
		}
		else if ((m_EC_Slave[i].eep_man == 0x00000AB0) && (m_EC_Slave[i].eep_id == 0x00010301))
		{
			//MX-DIO-30x
			*(INT16U*)m_EC_Slave[i].outputs = m_pgmEnv.EtherCAT_DO[i - 1];
		}
		else if ((m_EC_Slave[i].eep_man == 0x00000AB0) && (m_EC_Slave[i].eep_id == 0x00020101))
		{
			//MX-RLY
			*(INT16U*)m_EC_Slave[i].outputs = m_pgmEnv.EtherCAT_DO[i - 1];
		}
		else if ((m_EC_Slave[i].eep_man == 0x00000AB0) && (m_EC_Slave[i].eep_id == 0x00030101))
		{
			//MX-EXT Output 4
			*(INT08U*)m_EC_Slave[i].outputs = (INT08U)m_pgmEnv.EtherCAT_DO[i - 1];
		}
	}
}

/**
  * @brief
  * @param None
  * @retval None
  */
void EtherCAT_Output_Control(void)
{
	INT08U nMaxSlaveCount = 0;
	INT08U i;

	if (!m_pgmEnv.EtherCAT_Connection)	return;

	if (*m_EC_Main.slavecount > 10)
	{
		nMaxSlaveCount = 10;
	}
	else
	{
		nMaxSlaveCount = *(INT08U*)m_EC_Main.slavecount;
	}

	for (i = 1; i <= nMaxSlaveCount; i++)
	{
		if ((m_EC_Slave[i].eep_man == 0x00000083) && (m_EC_Slave[i].eep_id == 0x00000032))
		{
			*(INT16U*)m_EC_Slave[i].outputs = m_pgmEnv.EtherCAT_DO[i - 1];
		}
		else if ((m_EC_Slave[i].eep_man == 0x00000083) && (m_EC_Slave[i].eep_id == 0x00000033))
		{
			*(INT16U*)m_EC_Slave[i].outputs = m_pgmEnv.EtherCAT_DO[i - 1];
		}
		else if ((m_EC_Slave[i].eep_man == 0x00000AB0) && (m_EC_Slave[i].eep_id == 0x00010201))
		{
			*(INT16U*)m_EC_Slave[i].outputs = m_pgmEnv.EtherCAT_DO[i - 1];
		}
		else if ((m_EC_Slave[i].eep_man == 0x00000AB0) && (m_EC_Slave[i].eep_id == 0x00010301))
		{
			*(INT16U*)m_EC_Slave[i].outputs = m_pgmEnv.EtherCAT_DO[i - 1];
		}
		else if ((m_EC_Slave[i].eep_man == 0x00000AB0) && (m_EC_Slave[i].eep_id == 0x00020101))
		{
			*(INT16U*)m_EC_Slave[i].outputs = m_pgmEnv.EtherCAT_DO[i - 1];
		}
		/*
		else if ((m_EC_Slave[i].eep_man == 0x00000AB0) && (m_EC_Slave[i].eep_id == 0x00030101))
		{
			*(INT08U*)m_EC_Slave[i].outputs = (INT08U)m_pgmEnv.EtherCAT_DO[i - 1];
		}
		*/
	}
}

//INT08U s_ec_mode = 0;

/**
  * @brief
  * @param None
  * @retval None
  */
void ECAT_Manager(void)
{
	//INT08U nDEF_Error_Count = 10;
	INT08U nDEF_Error_Count = 3;

	static INT08U s_Retry_Start = 0;

	static INT08U s_ec_mode = 0;

	static INT32U s_chkTimer = 0;

	static INT08U s_Retry = 0;

	static INT08U s_Retry_Init = 0;

	INT08U nCheckFlag = 0;
	INT16U nCheckCnt = 0;
	INT16U nErrorEventFlag = 0;

	static INT08U s_ErrorCnt[16] = { 0, };

	static INT16U s_Slave_Connect_State = 0;
	INT16U nSlave_DisConnect_State = 0;

	int expectedWKC = 0;

#if DISABLE_ECAT_PROC
	return;
#endif

	Check_EtherCAT_Slave_Connection();

	switch (s_ec_mode)
	{
	case 0:
		if (m_pgmEnv.isFpgaRun)
		{
			InitFPGAEtherCat_1();

			s_Retry_Init = 0;

			s_chkTimer = m_pgmEnv.timer1ms;

			if (m_pgmEnv.UPLink)
			{
				s_ec_mode = 1;
			}
			else
			{
				s_ec_mode = 2;
			}
		}
		break;

	case 1:
		if (getCalcTimer1ms(s_chkTimer) >= 10000)
		{
			if (m_pgmEnv.UPLinkInitFlag)
			{
				s_Retry = 0;
				s_ec_mode = 2;
			}
		}
		break;

	case 2:
		if (getCalcTimer1ms(s_chkTimer) >= 1000)
		{
			s_chkTimer = m_pgmEnv.timer1ms;

			INT08U nSlaveCount = 0;
			for (INT08U i = 0; i < MAX_DIO_MODULE_CNT; i++)
			{
				if (m_DIO_SetInfo.Set.SlaveID[i])
				{
					++nSlaveCount;
				}
			}

			expectedWKC = EC_Detect_Slaves(&m_EC_Main);
			if (expectedWKC)
			{
				s_ec_mode = 3;
			}
			else
			{
				++s_Retry;
				if (s_Retry > 10)
				{
					if (nSlaveCount)
					{
						save_error_code(ERROR1_ETHERCAT, 1, 1);
					}
				}
			}

			/*
			INT08U nSlaveCount = 0;
			for (INT08U i = 0; i < MAX_DIO_MODULE_CNT; i++)
			{
				if (m_DIO_SetInfo.Set.SlaveID[i])
				{
					++nSlaveCount;
				}
			}

			expectedWKC = EC_Detect_Slaves(&m_EC_Main);
			if (expectedWKC)
			{
				if (expectedWKC == nSlaveCount)
				{
					s_ec_mode = 3;
				}
				else
				{
					++s_Retry;
					if (s_Retry > 10)
					{
						save_error_code(ERROR_ECAT_SETTING, 0, 0);
					}
				}
			}
			else
			{
				++s_Retry;
				if (s_Retry > 10)
				{
					save_error_code(ERROR_ECAT_SETTING, 0, 0);
				}
			}

			//m_TestStatus.St[DEBUG_STR_20] = nSlaveCount;
			//m_TestStatus.St[DEBUG_STR_21] = s_Retry;

			s_chkTimer = m_pgmEnv.timer1ms;
			*/
		}
		break;

	case 3:
		if (getCalcTimer1ms(s_chkTimer) >= 1000)
		{

#if DEBUG_ETHERCAT_MSG
			printf("[EtherCAT] Start EtherCAT initialization.\r\n");
#endif
			m_pgmEnv.SysTime_1ms = m_pgmEnv.timer1ms;

			if (ec_init())
			{
				// INIT -> PREOP
#if DEBUG_ETHERCAT_MSG
				printf("[EtherCAT] %d slaves found and configured.\r\n", m_EC_SlaveCount);

				expectedWKC = (m_EC_Group[0].outputsWKC * 2) + m_EC_Group[0].inputsWKC;
				printf("[EtherCAT] Calculated workcounter %d\r\n", expectedWKC);

				slaveinfo();
#endif
				m_DevStatus.mLinkStatus.EtherCAT_Slave = 0;

				// Check All Slave EC_STATE - PRE_OP
				nCheckFlag = Check_SlaveState(EC_STATE_PRE_OP);
				if (nCheckFlag)
				{
#if DEBUG_ETHERCAT_MSG
					printf("[EtherCAT] Step:%d All Slave State Pre Operational\r\n", s_ec_mode);
#endif
					//s_Retry = 0;
					s_chkTimer = m_pgmEnv.timer1ms;
					s_ec_mode = 4;
					break;
				}
			}

			s_chkTimer = m_pgmEnv.timer1ms;
			if (s_ec_mode != 4)
			{
#if DEBUG_ETHERCAT_MSG
				printf("[EtherCAT] No slaves found!\r\n");
#endif
				s_ec_mode = 100;
			}
		}
		break;

	case 4:
		if (getCalcTimer1ms(s_chkTimer) >= 1000)
		{
			nErrorEventFlag = Check_ECAT_Slave_Name_1();
			if (nErrorEventFlag == 0)
			{
				m_ProcessData_Flag = 1;

				__HAL_TIM_SET_COUNTER(&htim4, ETHERCAT_UPDATE_TIME);
				__HAL_TIM_ENABLE(&htim4);
				__HAL_TIM_ENABLE_IT(&htim4, TIM_IT_UPDATE);

				s_chkTimer = m_pgmEnv.timer1ms;
				s_ec_mode = 5;
			}
			else
			{
				++s_Retry;
				if (s_Retry < 10)
				{
					s_ec_mode = 3;
				}
				else
				{
					s_Retry = 0;
					if (nErrorEventFlag == 1)
					{
						for (INT08U i = 1; i < (m_EC_SlaveCount + 1); i++)
						{
							if (m_DIO_SetInfo.Scan[i - 1].SlaveID != m_DIO_SetInfo.Set.SlaveID[i - 1])
							{
								// Type 이상
								save_error_code(ERROR1_ETHERCAT, 4, i);
							}

							if (m_DIO_SetInfo.Scan[i - 1].Alias_Addr != 0)
							{
								if (m_DIO_SetInfo.Scan[i - 1].Alias_Addr != i)
								{
									// Alias Address 이상
									save_error_code(ERROR1_ETHERCAT, 3, i);
								}
							}
						}
					}
					else if (nErrorEventFlag == 2)
					{
						for (INT08U i = 1; i < (m_EC_SlaveCount + 1); i++)
						{
							if (m_DIO_SetInfo.Scan[i - 1].Alias_Addr != 0)
							{
								if (m_DIO_SetInfo.Scan[i - 1].Alias_Addr != i)
								{
									// Alias Address 이상
									save_error_code(ERROR1_ETHERCAT, 3, i);
								}
							}
						}
					}
					else if (nErrorEventFlag == 3)
					{
						save_error_code(ERROR1_ETHERCAT, 2, 1);
					}

					s_ec_mode = 100;
				}
			}
		}
		break;

	case 5:
		EtherCAT_Output_Control_All_Off();

		if (getCalcTimer1ms(s_chkTimer) >= 100)
		{
			// PREOP -> SAFEOP
			for (INT16U i = 1; i <= m_EC_SlaveCount; i++)
			{
				ecx_FPWRw(m_EC_Slave[i].configadr, ECT_REG_ALCTL, htoes(EC_STATE_SAFE_OP | EC_STATE_ACK)); // set op status 
			}

			s_chkTimer = m_pgmEnv.timer1ms;
			s_ec_mode = 6;
		}
		break;

	case 6:
		EtherCAT_Output_Control_All_Off();

		if (getCalcTimer1ms(s_chkTimer) >= 100)	// 1ms
		{
			EC_Read_State();

			for (INT16U i = 1; i <= m_EC_SlaveCount; i++)
			{
				if (m_EC_Slave[i].state == EC_STATE_SAFE_OP)
				{
#if DEBUG_ETHERCAT_MSG
					printf("[EtherCAT] Slave:%d Name:%s Output size:%3dbits Input size:%3dbits State:%2d delay:%d.%d\r\n",
						i, m_EC_Slave[i].name, m_EC_Slave[i].Obits, m_EC_Slave[i].Ibits,
						m_EC_Slave[i].state, (int)m_EC_Slave[i].pdelay, m_EC_Slave[i].hasdc);
#endif

					++nCheckCnt;
					s_ErrorCnt[i] = 0;
				}
				else
				{

					++s_ErrorCnt[i];
					if (s_ErrorCnt[i] > nDEF_Error_Count)
					{
						s_ErrorCnt[i] = 0;
#if DEBUG_ETHERCAT_MSG
						printf("[EtherCAT] Step:%d Slave %d State=%2x StatusCode=%04x : %s\r\n",
							s_ec_mode, i, m_EC_Slave[i].state, m_EC_Slave[i].ALstatuscode, ec_ALstatuscode2string(m_EC_Slave[i].ALstatuscode));
#endif

						m_pgmEnv.EtherCAT_Connection = 0;
						m_ProcessData_Flag = 0;

						__HAL_TIM_DISABLE(&htim4);
						__HAL_TIM_DISABLE_IT(&htim4, TIM_IT_UPDATE);

						s_ec_mode = 100;
						break;
					}
				}

			}

			if (nCheckCnt == m_EC_SlaveCount)
			{
#if DEBUG_ETHERCAT_MSG
				printf("[EtherCAT] Change Safe operational state for all slaves. Step : %d\r\n", s_ec_mode);
#endif
				s_ec_mode = 7;
			}
			else
			{
				if (s_ec_mode != 100)
				{
					s_ec_mode = 5;
				}
			}

			s_chkTimer = m_pgmEnv.timer1ms;
		}
		break;

	case 7:
		EtherCAT_Output_Control_All_Off();

		if (getCalcTimer1ms(s_chkTimer) >= 100)
		{
			for (INT16U i = 1; i <= m_EC_SlaveCount; i++)
			{
				ecx_FPWRw(m_EC_Slave[i].configadr, ECT_REG_ALCTL, htoes(EC_STATE_OPERATIONAL | EC_STATE_ACK)); // set op status 
			}

			s_ec_mode = 8;
			s_chkTimer = m_pgmEnv.timer1ms;
		}
		break;

	case 8:
		EtherCAT_Output_Control_All_Off();

		if (getCalcTimer1ms(s_chkTimer) >= 100)	// 1ms
		{
			EC_Read_State();

			for (INT16U i = 1; i <= m_EC_SlaveCount; i++)
			{
				if (m_EC_Slave[i].state == EC_STATE_OPERATIONAL)
				{
					++nCheckCnt;
					s_ErrorCnt[i] = 0;
				}
				else
				{
					++s_ErrorCnt[i];

					if (s_ErrorCnt[i] > nDEF_Error_Count)
					{
						s_ErrorCnt[i] = 0;
#if DEBUG_ETHERCAT_MSG
						printf("[EtherCAT] Step:%d Slave %d State=%2x StatusCode=%04x : %s\r\n",
							s_ec_mode, i, m_EC_Slave[i].state, m_EC_Slave[i].ALstatuscode, ec_ALstatuscode2string(m_EC_Slave[i].ALstatuscode));
#endif

						m_pgmEnv.EtherCAT_Connection = 0;
						m_ProcessData_Flag = 0;

						__HAL_TIM_DISABLE(&htim4);
						__HAL_TIM_DISABLE_IT(&htim4, TIM_IT_UPDATE);

						s_ec_mode = 100;
						break;
					}
				}

			}

			if (nCheckCnt == m_EC_SlaveCount)
			{
#if DEBUG_ETHERCAT_MSG
				printf("[EtherCAT] Request operational state for all slaves. Step : %d\r\n", s_ec_mode);
#endif
				DO_Control_Init();

				s_ec_mode = 9;
			}
			else
			{
				m_pgmEnv.EtherCAT_Connection = 0;
				m_ProcessData_Flag = 0;

				__HAL_TIM_DISABLE(&htim4);
				__HAL_TIM_DISABLE_IT(&htim4, TIM_IT_UPDATE);

				s_ec_mode = 10;
			}

			s_chkTimer = m_pgmEnv.timer1ms;
		}
		break;

	case 9:
		if (m_EC_Main.DisconnectFlag)
		{
#if DEBUG_ETHERCAT_MSG
			printf("[EtherCAT] Disconnect EtherCAT cable.\r\n");
#endif
			m_ProcessData_Flag = 0;

			__HAL_TIM_DISABLE(&htim4);
			__HAL_TIM_DISABLE_IT(&htim4, TIM_IT_UPDATE);

			s_ec_mode = 102;
		}
		else
		{
			m_pgmEnv.EtherCAT_Connection = 1;

			if (m_Max_DCtime < m_Diff_DCTime)
			{
				m_Max_DCtime = m_Diff_DCTime;
			}
			//m_TestStatus.St[DEBUG_STR_28] = (INT32U)m_Max_DCtime;
			//m_TestStatus.St[DEBUG_STR_29] = (INT32U)m_Diff_DCTime;

			//if (getCalcTimer1ms(s_chkTimer) >= 100)
			if (getCalcTimer1ms(s_chkTimer) >= 10)
			{
				EC_Read_State();

				for (INT16U i = 1; i <= m_EC_SlaveCount; i++)
				{
					if (m_EC_Slave[i].state != EC_STATE_OPERATIONAL)
					{
						++s_ErrorCnt[i];
						if (s_ErrorCnt[i] > nDEF_Error_Count)
						{
#if DEBUG_ETHERCAT_MSG
							printf("[EtherCAT] Step:%d Slave %d State=%2x StatusCode=%4x : %s\r\n",
								s_ec_mode, i, m_EC_Slave[i].state, m_EC_Slave[i].ALstatuscode,
								ec_ALstatuscode2string(m_EC_Slave[i].ALstatuscode));
#endif
							nErrorEventFlag = 1;
							
							s_Slave_Connect_State &= nbits16[i];
						}
					}
					else
					{
						s_Slave_Connect_State |= cbits16[i];

						s_ErrorCnt[i] = 0;
					}
				}

				s_chkTimer = m_pgmEnv.timer1ms;

				if (nErrorEventFlag)
				{
#if DEBUG_ETHERCAT_MSG
					printf("[EtherCAT] Stop.\r\n");
#endif
					m_pgmEnv.EtherCAT_Connection = 0;
					m_ProcessData_Flag = 0;

					__HAL_TIM_DISABLE(&htim4);
					__HAL_TIM_DISABLE_IT(&htim4, TIM_IT_UPDATE);

					if (m_St.SRM_Mode.Bit.Auto == 1)
					{
						nSlave_DisConnect_State = ~s_Slave_Connect_State;

						for (INT16U i = 1; i <= m_EC_SlaveCount; i++)
						{
							if (nSlave_DisConnect_State & cbits16[i])
							{
								save_error_code(ERROR1_ETHERCAT, 10 + (i - 1), m_pgmEnv.SRM_RunMode);
							}
						}

						s_ec_mode = 100;
					}
					else
					{
						s_ec_mode = 10;
					}
				}
			}
		}
		break;

	case 10:
		if (getCalcTimer1ms(s_chkTimer) >= 1000)
		{
			EC_Read_State();

			for (INT16U i = 1; i <= m_EC_SlaveCount; i++)
			{
				if (m_EC_Slave[i].state != EC_STATE_OPERATIONAL)
				{
#if DEBUG_ETHERCAT_MSG
					printf("[EtherCAT] Step:%d Slave %d State=%2x StatusCode=%4x : %s\r\n",
						s_ec_mode, i, m_EC_Slave[i].state, m_EC_Slave[i].ALstatuscode, ec_ALstatuscode2string(m_EC_Slave[i].ALstatuscode));
#endif
				}
			}

			// EhterCAT 연결 이상
			// Slave 중 OP Mode가 아닌게 있음.
			++s_Retry_Init;
			if (s_Retry_Init > 20)
			{
				s_Retry_Init = 0;
				save_error_code(ERROR1_ETHERCAT, 10, 0);
			}

			s_chkTimer = m_pgmEnv.timer1ms;
			s_ec_mode = 100;
		}
		break;

	case 11:
		if (m_pgmEnv.downloadMode)
		{
			asm volatile("NOP");
		}
		else
		{
			if (!m_pgmEnv.MCU_Test_Mode)
			{
				// 테스트 모드 해제 시, EtherCAT 초기화 재시작
				s_ec_mode = 0;
			}
		}
		break;

	case 100:
		m_pgmEnv.EtherCAT_Connection = 0;
		m_DevStatus.mLinkStatus.EtherCAT_Slave = 0;

		if (getCalcTimer1ms(s_chkTimer) >= 1000)
		{
			//save_error_code(ERROR1_ETHERCAT, 10, 2);

			s_chkTimer = m_pgmEnv.timer1ms;

			s_ec_mode = 3;
		}
		break;

	case 101:
		if (getCalcTimer1ms(s_chkTimer) >= 500)
		{
			EC_Read_State();

			for (INT16U i = 1; i <= m_EC_SlaveCount; i++)
			{
				if (m_EC_Slave[i].state != EC_STATE_SAFE_OP)
				{
#if DEBUG_ETHERCAT_MSG
					printf("[EtherCAT] Step:%d Slave %d State=%2x StatusCode=%4x : %s\r\n",
						s_ec_mode, i, m_EC_Slave[i].state, m_EC_Slave[i].ALstatuscode, ec_ALstatuscode2string(m_EC_Slave[i].ALstatuscode));
#endif
					//m_TestStatus.St[i] = ec_slave[i].ALstatuscode;

					m_ProcessData_Flag = 0;
				}
			}

			s_ec_mode = 102;
		}
		break;

	case 102:
		m_pgmEnv.EtherCAT_Connection = 0;
		m_DevStatus.mLinkStatus.EtherCAT_Slave = 0;

		if (getCalcTimer1ms(s_chkTimer) >= 1000)
		{
			++s_Retry_Start;
			if (s_Retry_Start >= 3)
			{
				s_Retry_Start = 0;
				save_error_code(ERROR1_ETHERCAT, 10, 2);
			}
			
			s_chkTimer = m_pgmEnv.timer1ms;

			s_ec_mode = 3;
		}
		break;

	case 110:
		if (getCalcTimer1ms(s_chkTimer) >= 10000)
		{
			s_chkTimer = m_pgmEnv.timer1ms;

			s_ec_mode = 3;
		}
		break;

	case 200:
		break;
	}


	EtherCAT_Output_Control();

	External_Encoder_Proc();		// GX_EC0211

	MX_EXT_Proc();

	if (m_pgmEnv.downloadMode || m_pgmEnv.MCU_Test_Mode)
	{
		if (s_ec_mode != 11)
		{
#if DEBUG_ETHERCAT_MSG
			printf("[EtherCAT] EtherCAT Stop. All Slave Init State.\r\n");
#endif
			for (INT16U i = 1; i <= m_EC_SlaveCount; i++)
			{
				ecx_FPWRw(m_EC_Slave[i].configadr, ECT_REG_ALCTL, htoes(EC_STATE_INIT | EC_STATE_ACK)); // set op status 
			}

			__HAL_TIM_DISABLE(&htim4);
			__HAL_TIM_DISABLE_IT(&htim4, TIM_IT_UPDATE);

			m_ProcessData_Flag = 0;
			s_ec_mode = 11;
		}
	}
	else
	{
		//EtherCAT_ComProcess();
	}

	//Set_TestStatus(DEBUG_STR_60, s_ec_mode);
	//m_TestStatus.St[DEBUG_STR_10] = m_ecx_pEC_Main.DisconnectCount;
	/*
	m_TestStatus.St[DEBUG_STR_10] = m_pgmEnv.EtherCAT_DO[0];
	m_TestStatus.St[DEBUG_STR_11] = m_pgmEnv.EtherCAT_DO[1];
	m_TestStatus.St[DEBUG_STR_12] = m_pgmEnv.EtherCAT_DO[2];

	m_TestStatus.St[DEBUG_STR_13] = *(INT16U*)ec_slave[1].inputs;
	m_TestStatus.St[DEBUG_STR_14] = *(INT16U*)ec_slave[2].inputs;
	m_TestStatus.St[DEBUG_STR_15] = *(INT16U*)ec_slave[3].inputs;
	m_TestStatus.St[DEBUG_STR_16] = *(INT32U*)ec_slave[4].inputs;
	*/
	//m_TestStatus.St[DEBUG_STR_31] = s_ec_mode;
}


/**
  * @brief
  * @param None
  * @retval None
  */
void ECAT_TestManager(INT08U nRunFlag, INT08U* pTestSeq, INT08U* pResult)
{
	static INT08U s_ec_mode;
	static INT32U s_chkTimer = 0;

	INT08U nDEF_Check_Count = 5;
	static INT08U s_CheckCnt;

	INT08U nDEF_Retry_Count = 5;
	static INT08U s_RetryCnt;

	INT08U nCheckFlag = 0;

	if (nRunFlag)
	{
		if (s_ec_mode == 0)
		{
			s_ec_mode = 1;
		}
	}
	else
	{
		s_ec_mode = 0;
	}

	Check_EtherCAT_Slave_Connection();

	switch (s_ec_mode)
	{
	case 0:
		s_CheckCnt = 0;
		s_RetryCnt = 0;
		break;

	case 1:
		if (m_pgmEnv.isFpgaRun)
		{
			InitFPGAEtherCat_1();

			s_chkTimer = m_pgmEnv.timer1ms;

			if (m_pgmEnv.UPLink)
			{
				s_ec_mode = 2;
			}
			else
			{
				s_ec_mode = 3;
			}
		}
		break;

	case 2:
		if (getCalcTimer1ms(s_chkTimer) >= 100)
		{
			if (m_pgmEnv.UPLinkInitFlag)
			{
				s_ec_mode = 3;
			}
		}
		break;

	case 3:
		if (getCalcTimer1ms(s_chkTimer) >= 100)
		{

#if DEBUG_ETHERCAT_MSG
			printf("[EtherCAT TEST] Start EtherCAT initialization.\r\n");
#endif
			m_pgmEnv.SysTime_1ms = m_pgmEnv.timer1ms;

			if (ec_init())
			{
				// INIT -> PREOP
#if DEBUG_ETHERCAT_MSG
				int expectedWKC = 0;

				printf("[EtherCAT TEST] %d slaves found and configured.\r\n", m_EC_SlaveCount);

				expectedWKC = (m_EC_Group[0].outputsWKC * 2) + m_EC_Group[0].inputsWKC;
				printf("[EtherCAT TEST] Calculated work counter %d\r\n", expectedWKC);
#endif	
				// Check All Slave EC_STATE - PRE_OP
				nCheckFlag = Check_SlaveState(EC_STATE_PRE_OP);
				if (nCheckFlag)
				{
#if DEBUG_ETHERCAT_MSG
					printf("[EtherCAT] All Slave State Pre Operational. CheckFlag : %d\r\n", nCheckFlag);
#endif
				}
			}

			s_chkTimer = m_pgmEnv.timer1ms;
			if (m_EC_SlaveCount == 2)
			{
				s_ec_mode = 4;
			}
			else
			{
				s_ec_mode = 100;
			}
		}
		break;

	case 4:
		//if (getCalcTimer1ms(s_chkTimer) > 1000)
		if (getCalcTimer1ms(s_chkTimer) > 100)
		{
			for (INT16U i = 1; i <= m_EC_SlaveCount; i++)
			{
				ecx_FPWRw(m_EC_Slave[i].configadr, ECT_REG_ALCTL, htoes(EC_STATE_INIT | EC_STATE_ACK)); // set op status 
			}

			s_chkTimer = m_pgmEnv.timer1ms;

			++s_CheckCnt;
			if (s_CheckCnt > nDEF_Check_Count)
			{
#if DEBUG_ETHERCAT_MSG
				printf("[EtherCAT TEST] Test OK.\r\n");
#endif
				s_ec_mode = 5;
			}
			else
			{
#if DEBUG_ETHERCAT_MSG
				printf("[EtherCAT TEST] Test OK. Restart Scan Slave. Check Count : %d\r\n", s_CheckCnt);
#endif
				//s_ec_mode = 1;
				s_ec_mode = 3;
			}
		}
		break;

	case 5:
		break;

	case 100:
		//if (getCalcTimer1ms(s_chkTimer) > 1000)
		if (getCalcTimer1ms(s_chkTimer) > 100)
		{
			for (INT16U i = 1; i <= m_EC_SlaveCount; i++)
			{
				ecx_FPWRw(m_EC_Slave[i].configadr, ECT_REG_ALCTL, htoes(EC_STATE_INIT | EC_STATE_ACK)); // set op status 
			}

			s_chkTimer = m_pgmEnv.timer1ms;

			++s_RetryCnt;
			if (s_RetryCnt > nDEF_Retry_Count)
			{
#if DEBUG_ETHERCAT_MSG
				printf("[EtherCAT TEST] Test Fail...\r\n");
#endif
				s_ec_mode = 101;
			}
			else
			{
#if DEBUG_ETHERCAT_MSG
				printf("[EtherCAT TEST] Test NG. Restart Scan Slave. Retry : %d\r\n", s_RetryCnt);
#endif
				//s_ec_mode = 1;
				s_ec_mode = 3;
			}
		}
		break;

	case 101:
		break;

	}

	if (s_ec_mode == 5)
	{
		// Complete Test. Result : OK
		*pTestSeq = 2;
		*pResult = m_EC_SlaveCount;
	}
	else if (s_ec_mode == 101)
	{
		// Complete Test. Result : NG
		*pTestSeq = 3;
		*pResult = m_EC_SlaveCount;
	}
	else if (s_ec_mode != 0)
	{
		// Testing....
		*pTestSeq = 1;
		*pResult = 0;
	}
}

/**
  * @brief
  * @param None
  * @retval None
  */
void ECAT_TestManager_1()
{
	INT08U nDEF_Error_Count = 3;

	static INT08U s_ec_mode = 0;
	static INT32U s_chkTimer = 0;

	INT08U nDEF_Check_Count = 5;
	static INT08U s_CheckCnt;

	INT08U nDEF_Retry_Count = 5;
	static INT08U s_RetryCnt;

	INT08U nCheckFlag = 0;
	INT16U nCheckCnt = 0;
	INT16U nErrorEventFlag = 0;

	static INT08U s_ErrorCnt[16] = { 0, };

	static INT32U s_IntervalTimer = 0;

	static INT32U s_Test_Flag = 0;
	static INT32U s_Test_Timer = 0;

	static INT32U s_ClearTimer = 0;
	INT32U s_ClearData = 0;

	Check_EtherCAT_Slave_Connection();

	switch (s_ec_mode)
	{
	case 0:
		s_CheckCnt = 0;
		s_RetryCnt = 0;

		s_ec_mode = 1;
		break;

	case 1:
		if (m_pgmEnv.isFpgaRun)
		{
			InitFPGAEtherCat_1();

			s_chkTimer = m_pgmEnv.timer1ms;

			if (m_pgmEnv.UPLink)
			{
				s_ec_mode = 2;
			}
			else
			{
				s_ec_mode = 3;
			}
		}
		break;

	case 2:
		if (getCalcTimer1ms(s_chkTimer) >= 100)
		{
			if (m_pgmEnv.UPLinkInitFlag)
			{
				s_ec_mode = 3;
			}
		}
		break;

	case 3:
		if (getCalcTimer1ms(s_chkTimer) >= 100)
		{

#if DEBUG_ETHERCAT_MSG
			printf("[EtherCAT TEST] Start EtherCAT initialization.\r\n");
#endif
			m_pgmEnv.SysTime_1ms = m_pgmEnv.timer1ms;

			if (ec_init())
			{
				// INIT -> PREOP
#if DEBUG_ETHERCAT_MSG
				int expectedWKC;

				printf("[EtherCAT TEST]] %d slaves found and configured.\r\n", m_EC_SlaveCount);

				expectedWKC = (m_EC_Group[0].outputsWKC * 2) + m_EC_Group[0].inputsWKC;
				printf("[EtherCAT TEST]] Calculated workcounter %d\r\n", expectedWKC);

				slaveinfo();
#endif
				// Check All Slave EC_STATE - PRE_OP
				nCheckFlag = Check_SlaveState(EC_STATE_PRE_OP);
				if (nCheckFlag)
				{
#if DEBUG_ETHERCAT_MSG
					printf("[EtherCAT TEST]] Step:%d All Slave State Pre Operational\r\n", s_ec_mode);
#endif
					s_chkTimer = m_pgmEnv.timer1ms;
					s_ec_mode = 4;
					break;
				}
			}

			s_chkTimer = m_pgmEnv.timer1ms;
		}
		break;

	case 4:
		//if (getCalcTimer1ms(s_chkTimer) >= 100)
		if (getCalcTimer1ms(s_chkTimer) >= 100)
		{
			Check_ECAT_Slave_Name();

			s_chkTimer = m_pgmEnv.timer1ms;
			s_ec_mode = 5;
		}
		break;

	case 5:
		EtherCAT_Output_Control_All_Off();

		if (getCalcTimer1ms(s_chkTimer) >= 100)
		{
			// PREOP -> SAFEOP
			for (INT16U i = 1; i <= m_EC_SlaveCount; i++)
			{
				ecx_FPWRw(m_EC_Slave[i].configadr, ECT_REG_ALCTL, htoes(EC_STATE_SAFE_OP | EC_STATE_ACK)); // set op status 
			}

			s_chkTimer = m_pgmEnv.timer1ms;
			s_ec_mode = 6;
		}
		break;

	case 6:
		EtherCAT_Output_Control_All_Off();

		if (getCalcTimer1ms(s_chkTimer) >= 100)	// 1ms
		{
			s_ec_mode = 7;
			///*
			EC_Read_State();

			for (INT16U i = 1; i <= m_EC_SlaveCount; i++)
			{
				if (m_EC_Slave[i].state == EC_STATE_SAFE_OP)
				{
#if DEBUG_ETHERCAT_MSG
					printf("[EtherCAT TEST] Slave:%d Name:%s Output size:%3dbits Input size:%3dbits State:%2d delay:%d.%d\r\n",
						i, m_EC_Slave[i].name, m_EC_Slave[i].Obits, m_EC_Slave[i].Ibits,
						m_EC_Slave[i].state, (int)m_EC_Slave[i].pdelay, m_EC_Slave[i].hasdc);
#endif

					++nCheckCnt;
					s_ErrorCnt[i] = 0;
				}
				else
				{
					if (m_EC_Slave[i].ALstatuscode == 0x0000)
					{
						++nCheckCnt;
						s_ErrorCnt[i] = 0;
					}
					else
					{
						++s_ErrorCnt[i];
						if (s_ErrorCnt[i] > nDEF_Error_Count)
						{
							s_ErrorCnt[i] = 0;
#if DEBUG_ETHERCAT_MSG
							printf("[EtherCAT TEST] Step:%d Slave %d State=%2x StatusCode=%04x : %s\r\n",
								s_ec_mode, i, m_EC_Slave[i].state, m_EC_Slave[i].ALstatuscode, ec_ALstatuscode2string(m_EC_Slave[i].ALstatuscode));
#endif

							m_pgmEnv.EtherCAT_Connection = 0;
							nErrorEventFlag = 1;
							break;
						}
					}
				}

			}

			if (nCheckCnt == m_EC_SlaveCount)
			{
#if DEBUG_ETHERCAT_MSG
				printf("[EtherCAT TEST] Change Safe operational state for all slaves. Step : %d\r\n", s_ec_mode);
#endif
				s_ec_mode = 7;
			}
			else
			{
				if (nErrorEventFlag)
				{
					s_ec_mode = 5;
				}
				else
				{
					s_ec_mode = 100;
				}
			}

			s_chkTimer = m_pgmEnv.timer1ms;
			//*/
		}
		break;

	case 7:
		EtherCAT_Output_Control_All_Off();

		if (getCalcTimer1ms(s_chkTimer) >= 100)
		{
			for (INT16U i = 1; i <= m_EC_SlaveCount; i++)
			{
				ecx_FPWRw(m_EC_Slave[i].configadr, ECT_REG_ALCTL, htoes(EC_STATE_OPERATIONAL | EC_STATE_ACK)); // set op status 
			}

			s_ec_mode = 8;
			s_chkTimer = m_pgmEnv.timer1ms;
		}
		break;

	case 8:
		EtherCAT_Output_Control_All_Off();

		if (getCalcTimer1ms(s_chkTimer) >= 100)	// 1ms
		{
			s_ec_mode = 9;
			///*
			EC_Read_State();

			for (INT16U i = 1; i <= m_EC_SlaveCount; i++)
			{
				if (m_EC_Slave[i].state == EC_STATE_OPERATIONAL)
				{
					++nCheckCnt;
					s_ErrorCnt[i] = 0;
				}
				else
				{
					if (m_EC_Slave[i].ALstatuscode == 0x0000)
					{
						++nCheckCnt;
						s_ErrorCnt[i] = 0;
					}
					else
					{
						++s_ErrorCnt[i];

						if (s_ErrorCnt[i] > nDEF_Error_Count)
						{
							s_ErrorCnt[i] = 0;
#if DEBUG_ETHERCAT_MSG
							printf("[EtherCAT TEST] Step:%d Slave %d State=%2x StatusCode=%04x : %s\r\n",
								s_ec_mode, i, m_EC_Slave[i].state, m_EC_Slave[i].ALstatuscode, ec_ALstatuscode2string(m_EC_Slave[i].ALstatuscode));
#endif

							m_pgmEnv.EtherCAT_Connection = 0;

							s_ec_mode = 100;
							break;
						}
					}
				}

			}

			if (nCheckCnt == m_EC_SlaveCount)
			{
#if DEBUG_ETHERCAT_MSG
				printf("[EtherCAT TEST] Request operational state for all slaves. Step : %d\r\n", s_ec_mode);
#endif
				s_ec_mode = 9;
			}
			else
			{
				m_pgmEnv.EtherCAT_Connection = 0;

				s_ec_mode = 100;
			}

			s_chkTimer = m_pgmEnv.timer1ms;
			//*/
		}
		break;

	case 9:
		m_pgmEnv.EtherCAT_Connection = 1;

		EtherCAT_Output_Control();

		if (getCalcTimer1ms(s_Test_Timer) >= 100)
		{
			DO_Control(OUT_IINH, s_Test_Flag);

			s_Test_Flag ^= 0x01;

			s_Test_Timer = m_pgmEnv.timer1ms;
		}

		///*
		if (getCalcTimer1ms(s_chkTimer) >= 10)
		{
			EC_Read_State();

			for (INT16U i = 1; i <= m_EC_SlaveCount; i++)
			{
				if (m_EC_Slave[i].state != EC_STATE_OPERATIONAL)
				{
					if (m_EC_Slave[i].ALstatuscode)
					{
						++s_ErrorCnt[i];
						if (s_ErrorCnt[i] > nDEF_Error_Count)
						{
#if DEBUG_ETHERCAT_MSG
							printf("[EtherCAT] Step:%d Slave %d State=%2x StatusCode=%4x : %s\r\n",
								s_ec_mode, i, m_EC_Slave[i].state, m_EC_Slave[i].ALstatuscode,
								ec_ALstatuscode2string(m_EC_Slave[i].ALstatuscode));
#endif
							nErrorEventFlag = 1;
						}
					}
				}
				else
				{
					s_ErrorCnt[i] = 0;
				}
			}

			if (nErrorEventFlag)
			{
#if DEBUG_ETHERCAT_MSG
				printf("[EtherCAT] Stop.\r\n");
#endif
				m_pgmEnv.EtherCAT_Connection = 0;
				s_ec_mode = 100;
				break;
			}

			s_chkTimer = m_pgmEnv.timer1ms;
		}
		//*/
		break;

	case 100:
		asm volatile("NOP");
		break;

	case 101:
		break;

	}

	if (s_ec_mode == 9)
	{
		if (getCalcTimer100us(s_IntervalTimer) >= 10)
		{
			// Process Time : 140.7us
			ec_send_processdata_group_1(0);
			s_IntervalTimer = m_pgmEnv.timer100us;
		}
	}

	if (getCalcTimer1ms(s_ClearTimer) > 100)
	{
		ecx_BWR(0x0000, ECT_REG_RXERR, 8, &s_ClearData);
		s_ClearTimer = m_pgmEnv.timer1ms;
	}
}



