#include <stdio.h>
#include <string.h>

#include "User_Define.h"

/*
#include "ecat_type.h"
#include "ecat_combase.h"
#include "ecat_main.h"
#include "ecat_coe.h"
#include "ecat_config.h"
*/

#include "ecat.h"

static int EC_Map_COE_SOE(EC_Main_t* EC_Main, uint16 slave, int thread_n)
{
	int Isize, Osize;
	int nReturn_val;

	EC_State_Check_1(EC_Main, slave, EC_STATE_PRE_OP, EC_TIMEOUT_STATE); 

#if DEBUG_ETHERCAT_MSG
	printf(" >Slave %d, configadr %x, state %2.2x\r\n",
		slave, EC_Main->slave_list[slave].configadr, EC_Main->slave_list[slave].state);
#endif

	if (EC_Main->slave_list[slave].PO2SOconfig)
	{
		EC_Main->slave_list[slave].PO2SOconfig(slave);
	}

	if (EC_Main->slave_list[slave].PO2SOconfigx)
	{
		EC_Main->slave_list[slave].PO2SOconfigx(EC_Main, slave);
	}

	if (!EC_Main->slave_list[slave].configindex)
	{
		Isize = 0;
		Osize = 0;
		if (EC_Main->slave_list[slave].mbx_proto & ECT_MBXPROT_COE)
		{
			nReturn_val = 0;
			if (EC_Main->slave_list[slave].CoEdetails & ECT_COEDET_SDOCA)
			{
				nReturn_val = EC_Read_PDOmap_CA(EC_Main, slave, thread_n, &Osize, &Isize);
			}

			if (!nReturn_val)
			{
				nReturn_val = EC_Read_PDOmap(EC_Main, slave, &Osize, &Isize);
			}

#if DEBUG_ETHERCAT_MSG
			printf("  CoE Osize:%d Isize:%d\r\n", Osize, Isize);
#endif
		}
		
		EC_Main->slave_list[slave].Obits = Osize;
		EC_Main->slave_list[slave].Ibits = Isize;
	}

	return 1;
}

static int EC_lookup_mapping(EC_Main_t* pEC_Main, uint16 slave, int* Osize, int* Isize)
{
	int i, nSM;
	if ((slave > 1) && (*(pEC_Main->slavecount) > 0))
	{
		i = 1;
		while (((pEC_Main->slave_list[i].eep_man != pEC_Main->slave_list[slave].eep_man) ||
			(pEC_Main->slave_list[i].eep_id != pEC_Main->slave_list[slave].eep_id) ||
			(pEC_Main->slave_list[i].eep_rev != pEC_Main->slave_list[slave].eep_rev)) &&
			(i < slave))
		{
			i++;
		}
		if (i < slave)
		{
			for (nSM = 0; nSM < EC_MAX_SM; nSM++)
			{
				pEC_Main->slave_list[slave].SM[nSM].SMlength = pEC_Main->slave_list[i].SM[nSM].SMlength;
				pEC_Main->slave_list[slave].SMtype[nSM] = pEC_Main->slave_list[i].SMtype[nSM];
			}
			*Osize = pEC_Main->slave_list[i].Obits;
			*Isize = pEC_Main->slave_list[i].Ibits;
			pEC_Main->slave_list[slave].Obits = *Osize;
			pEC_Main->slave_list[slave].Ibits = *Isize;

#if DEBUG_ETHERCAT_MSG
			printf("Copy mapping slave %d from %d.\r\n", slave, i);
#endif

			return 1;
		}
	}
	return 0;
}

static int EC_lookup_prev_sii(EC_Main_t* EC_Main, uint16 slave)
{
	int i, nSM;

	if ((slave > 1) && (*(EC_Main->slavecount) > 0))
	{
		i = 1;
		while (((EC_Main->slave_list[i].eep_man != EC_Main->slave_list[slave].eep_man) ||
			(EC_Main->slave_list[i].eep_id != EC_Main->slave_list[slave].eep_id) ||
			(EC_Main->slave_list[i].eep_rev != EC_Main->slave_list[slave].eep_rev)) &&
			(i < slave))
		{
			i++;
		}

		if (i < slave)
		{
			EC_Main->slave_list[slave].CoEdetails = EC_Main->slave_list[i].CoEdetails;
			EC_Main->slave_list[slave].FoEdetails = EC_Main->slave_list[i].FoEdetails;
			EC_Main->slave_list[slave].EoEdetails = EC_Main->slave_list[i].EoEdetails;
			EC_Main->slave_list[slave].SoEdetails = EC_Main->slave_list[i].SoEdetails;
			if (EC_Main->slave_list[i].blockLRW > 0)
			{
				EC_Main->slave_list[slave].blockLRW = 1;
				EC_Main->slave_list[0].blockLRW++;
			}
			EC_Main->slave_list[slave].Ebuscurrent = EC_Main->slave_list[i].Ebuscurrent;
			EC_Main->slave_list[0].Ebuscurrent += EC_Main->slave_list[slave].Ebuscurrent;
			memcpy(EC_Main->slave_list[slave].name, EC_Main->slave_list[i].name, EC_MAX_NAME + 1);
			for (nSM = 0; nSM < EC_MAX_SM; nSM++)
			{
				EC_Main->slave_list[slave].SM[nSM].StartAddr = EC_Main->slave_list[i].SM[nSM].StartAddr;
				EC_Main->slave_list[slave].SM[nSM].SMlength = EC_Main->slave_list[i].SM[nSM].SMlength;
				EC_Main->slave_list[slave].SM[nSM].SMflags = EC_Main->slave_list[i].SM[nSM].SMflags;
			}
			EC_Main->slave_list[slave].FMMU0func = EC_Main->slave_list[i].FMMU0func;
			EC_Main->slave_list[slave].FMMU1func = EC_Main->slave_list[i].FMMU1func;
			EC_Main->slave_list[slave].FMMU2func = EC_Main->slave_list[i].FMMU2func;
			EC_Main->slave_list[slave].FMMU3func = EC_Main->slave_list[i].FMMU3func;

#if DEBUG_ETHERCAT_MSG
			printf("Copy SII slave %d from %d.\r\n", slave, i);
#endif // DEBUG_ETHERCAT_MSG

			return 1;
		}
	}
	return 0;
}

static void EC_Config_Create_Input_Mappings(EC_Main_t* pEC_Main, void* pIOmap, uint8 group, int16 slave, uint32* LogAddr, uint8* BitPos)
{
	int BitCount = 0;
	int ByteCount = 0;
	int FMMUsize = 0;
	int FMMUdone = 0;
	uint8 SMc = 0;
	uint16 EndAddr;
	uint16 SMlength;
	uint16 configadr;
	uint8 FMMUc;

#if DEBUG_ETHERCAT_MSG
	printf(" =Slave %d, INPUT MAPPING\r\n", slave);
#endif

	configadr = pEC_Main->slave_list[slave].configadr;
	FMMUc = pEC_Main->slave_list[slave].FMMUunused;
	if (pEC_Main->slave_list[slave].Obits)
	{
		while (pEC_Main->slave_list[slave].FMMU[FMMUc].LogStart)
		{
			FMMUc++;
		}
	}
	
	while ((SMc < (EC_MAX_SM - 1)) && (FMMUdone < ((pEC_Main->slave_list[slave].Ibits + 7) / 8)))
	{
#if DEBUG_ETHERCAT_MSG
		printf("    FMMU %d\r\n", FMMUc);
#endif
		while ((SMc < (EC_MAX_SM - 1)) && (pEC_Main->slave_list[slave].SMtype[SMc] != 4))
		{
			SMc++;
		}
#if DEBUG_ETHERCAT_MSG
		printf("      SM%d\r\n", SMc);
#endif

		pEC_Main->slave_list[slave].FMMU[FMMUc].PhysStart =
			pEC_Main->slave_list[slave].SM[SMc].StartAddr;
		SMlength = etohs(pEC_Main->slave_list[slave].SM[SMc].SMlength);
		ByteCount += SMlength;
		BitCount += SMlength * 8;
		EndAddr = etohs(pEC_Main->slave_list[slave].SM[SMc].StartAddr) + SMlength;
		while ((BitCount < pEC_Main->slave_list[slave].Ibits) && (SMc < (EC_MAX_SM - 1)))
		{
			SMc++;
			while ((SMc < (EC_MAX_SM - 1)) && (pEC_Main->slave_list[slave].SMtype[SMc] != 4))
			{
				SMc++;
			}
			
			if (etohs(pEC_Main->slave_list[slave].SM[SMc].StartAddr) > EndAddr)
			{
				break;
			}
#if DEBUG_ETHERCAT_MSG
			printf("      SM%d\r\n", SMc);
#endif

			SMlength = etohs(pEC_Main->slave_list[slave].SM[SMc].SMlength);
			ByteCount += SMlength;
			BitCount += SMlength * 8;
			EndAddr = etohs(pEC_Main->slave_list[slave].SM[SMc].StartAddr) + SMlength;
		}

		if (!pEC_Main->slave_list[slave].Ibytes)
		{
			pEC_Main->slave_list[slave].FMMU[FMMUc].LogStart = htoel(*LogAddr);
			pEC_Main->slave_list[slave].FMMU[FMMUc].LogStartbit = *BitPos;
			*BitPos += pEC_Main->slave_list[slave].Ibits - 1;
			if (*BitPos > 7)
			{
				*LogAddr += 1;
				*BitPos -= 8;
			}
			FMMUsize = *LogAddr - etohl(pEC_Main->slave_list[slave].FMMU[FMMUc].LogStart) + 1;
			pEC_Main->slave_list[slave].FMMU[FMMUc].LogLength = htoes(FMMUsize);
			pEC_Main->slave_list[slave].FMMU[FMMUc].LogEndbit = *BitPos;
			*BitPos += 1;
			if (*BitPos > 7)
			{
				*LogAddr += 1;
				*BitPos -= 8;
			}
		}
		else
		{
			if (*BitPos)
			{
				*LogAddr += 1;
				*BitPos = 0;
			}
			pEC_Main->slave_list[slave].FMMU[FMMUc].LogStart = htoel(*LogAddr);
			pEC_Main->slave_list[slave].FMMU[FMMUc].LogStartbit = *BitPos;
			*BitPos = 7;
			FMMUsize = ByteCount;
			if ((FMMUsize + FMMUdone) > (int)pEC_Main->slave_list[slave].Ibytes)
			{
				FMMUsize = pEC_Main->slave_list[slave].Ibytes - FMMUdone;
			}
			*LogAddr += FMMUsize;
			pEC_Main->slave_list[slave].FMMU[FMMUc].LogLength = htoes(FMMUsize);
			pEC_Main->slave_list[slave].FMMU[FMMUc].LogEndbit = *BitPos;
			*BitPos = 0;
		}
		FMMUdone += FMMUsize;
		if (pEC_Main->slave_list[slave].FMMU[FMMUc].LogLength)
		{
			pEC_Main->slave_list[slave].FMMU[FMMUc].PhysStartBit = 0;
			pEC_Main->slave_list[slave].FMMU[FMMUc].FMMUtype = 1;
			pEC_Main->slave_list[slave].FMMU[FMMUc].FMMUactive = 1;
			
			ecx_FPWR(configadr, ECT_REG_FMMU0 + (sizeof(ec_fmmu_t) * FMMUc),
				sizeof(ec_fmmu_t), &(pEC_Main->slave_list[slave].FMMU[FMMUc]));
			
			pEC_Main->group_list[group].inputsWKC++;
		}
		if (!pEC_Main->slave_list[slave].inputs)
		{
			if (group)
			{
				pEC_Main->slave_list[slave].inputs =
					(uint8*)(pIOmap)+
					etohl(pEC_Main->slave_list[slave].FMMU[FMMUc].LogStart) -
					pEC_Main->group_list[group].logstartaddr;
			}
			else
			{
				pEC_Main->slave_list[slave].inputs =
					(uint8*)(pIOmap)+
					etohl(pEC_Main->slave_list[slave].FMMU[FMMUc].LogStart);
			}
			pEC_Main->slave_list[slave].Istartbit =
				pEC_Main->slave_list[slave].FMMU[FMMUc].LogStartbit;

#if DEBUG_ETHERCAT_MSG
			printf("    Inputs %p startbit %d\r\n", \
				pEC_Main->slave_list[slave].inputs,	\
				pEC_Main->slave_list[slave].Istartbit);
#endif

		}
		FMMUc++;
	}
	pEC_Main->slave_list[slave].FMMUunused = FMMUc;
}

static int EC_Map_SM(EC_Main_t* pEC_Main, uint16 slave)
{
	uint16 configadr;
	int nSM;
	int nWkc = 0;

	configadr = pEC_Main->slave_list[slave].configadr;

#if DEBUG_ETHERCAT_MSG
	printf("  Slave :%d, SM programming\r\n", slave);
#endif
	if (!pEC_Main->slave_list[slave].mbx_l && pEC_Main->slave_list[slave].SM[0].StartAddr)
	{
		ecx_FPWR(configadr, ECT_REG_SM0,
			sizeof(ec_smt), &(pEC_Main->slave_list[slave].SM[0]));

#if DEBUG_ETHERCAT_MSG
		printf("    SM0 Type:%d StartAddr:%4.4x Flags:%8.8lx\r\n",
		 			pEC_Main->slave_list[slave].SMtype[0],
		 			etohs(pEC_Main->slave_list[slave].SM[0].StartAddr),
		 			etohl(pEC_Main->slave_list[slave].SM[0].SMflags));
#endif
	}
	if (!pEC_Main->slave_list[slave].mbx_l && pEC_Main->slave_list[slave].SM[1].StartAddr)
	{
		ecx_FPWR(configadr, ECT_REG_SM1,
			sizeof(ec_smt), &pEC_Main->slave_list[slave].SM[1]);

#if DEBUG_ETHERCAT_MSG
		printf("    SM1 Type:%d StartAddr:%4.4x Flags:%8.8lx\r\n",
			pEC_Main->slave_list[slave].SMtype[1],
			etohs(pEC_Main->slave_list[slave].SM[1].StartAddr),
			etohl(pEC_Main->slave_list[slave].SM[1].SMflags));
#endif
	}

	for (nSM = 2; nSM < EC_MAX_SM; nSM++)
	{
		if (pEC_Main->slave_list[slave].SM[nSM].StartAddr)
		{
			if (pEC_Main->slave_list[slave].SM[nSM].SMlength == 0)
			{
				pEC_Main->slave_list[slave].SM[nSM].SMflags =
					htoel(etohl(pEC_Main->slave_list[slave].SM[nSM].SMflags) & EC_SMENABLEMASK);
			}
			else
			{
				pEC_Main->slave_list[slave].SM[nSM].SMflags =
					htoel(etohl(pEC_Main->slave_list[slave].SM[nSM].SMflags) | ~EC_SMENABLEMASK);
			}
			nWkc = ecx_FPWR(configadr, (uint16)(ECT_REG_SM0 + (nSM * sizeof(ec_smt))),
				sizeof(ec_smt), &pEC_Main->slave_list[slave].SM[nSM]);

#if DEBUG_ETHERCAT_MSG
			printf("    SM%d Type:%d StartAddr:%4.4x Flags:%8.8lx nWkc: %d\r\n", nSM,
				pEC_Main->slave_list[slave].SMtype[nSM],
				etohs(pEC_Main->slave_list[slave].SM[nSM].StartAddr),
				etohl(pEC_Main->slave_list[slave].SM[nSM].SMflags), nWkc);
#endif
			asm volatile("NOP");
		}
	}
	if (pEC_Main->slave_list[slave].Ibits > 7)
	{
		pEC_Main->slave_list[slave].Ibytes = (pEC_Main->slave_list[slave].Ibits + 7) / 8;
	}
	if (pEC_Main->slave_list[slave].Obits > 7)
	{
		pEC_Main->slave_list[slave].Obytes = (pEC_Main->slave_list[slave].Obits + 7) / 8;
	}

	return 1;
}

static int EC_Map_Sii(EC_Main_t* pEC_Main, uint16 slave)
{
	int Isize, Osize;
	int nSM;
	EC_eepromPDO_t eepPDO;

	Osize = pEC_Main->slave_list[slave].Obits;
	Isize = pEC_Main->slave_list[slave].Ibits;

	if (!Isize && !Osize)
	{
		(void)EC_lookup_mapping(pEC_Main, slave, &Osize, &Isize);
	}
	if (!Isize && !Osize)
	{
		memset(&eepPDO, 0, sizeof(eepPDO));
		Isize = (int)EC_SII_PDO(pEC_Main, slave, &eepPDO, 0);
#if DEBUG_ETHERCAT_MSG
		printf("  SII Isize:%d\r\n", Isize);
#endif
		for (nSM = 0; nSM < EC_MAX_SM; nSM++)
		{
			if (eepPDO.SMbitsize[nSM] > 0)
			{
				pEC_Main->slave_list[slave].SM[nSM].SMlength = htoes((eepPDO.SMbitsize[nSM] + 7) / 8);
				pEC_Main->slave_list[slave].SMtype[nSM] = 4;
#if DEBUG_ETHERCAT_MSG
				printf("    SM%d length %d\r\n", nSM, eepPDO.SMbitsize[nSM]);
#endif
			}
		}
		Osize = (int)EC_SII_PDO(pEC_Main, slave, &eepPDO, 1);
#if DEBUG_ETHERCAT_MSG
		printf("  SII Osize:%d\r\n", Osize);
#endif

		for (nSM = 0; nSM < EC_MAX_SM; nSM++)
		{
			if (eepPDO.SMbitsize[nSM] > 0)
			{
				pEC_Main->slave_list[slave].SM[nSM].SMlength = htoes((eepPDO.SMbitsize[nSM] + 7) / 8);
				pEC_Main->slave_list[slave].SMtype[nSM] = 3;

#if DEBUG_ETHERCAT_MSG
				printf("    SM%d length %d\r\n", nSM, eepPDO.SMbitsize[nSM]);
#endif
			}
		}
	}
	pEC_Main->slave_list[slave].Obits = Osize;
	pEC_Main->slave_list[slave].Ibits = Isize;
#if DEBUG_ETHERCAT_MSG
	printf("     ISIZE:%d %d OSIZE:%d\r\n",
	 		pEC_Main->slave_list[slave].Ibits, Isize, pEC_Main->slave_list[slave].Obits);
#endif
	return 1;
}

static void EC_Config_Find_Map(EC_Main_t* nEC_Main, uint8 group)
{
	uint16 slave;

	for (slave = 1; slave <= *(nEC_Main->slavecount); slave++)
	{
		if (!group || (group == nEC_Main->slave_list[slave].group))
		{
			EC_Map_COE_SOE(nEC_Main, slave, 0);
		}
	}

	for (slave = 1; slave <= *(nEC_Main->slavecount); slave++)
	{
		if (!group || (group == nEC_Main->slave_list[slave].group))
		{
			EC_Map_Sii(nEC_Main, slave);
			EC_Map_SM(nEC_Main, slave);
		}
	}
}

static void EC_Config_Create_Output_Mappings(EC_Main_t* pEC_Main, void* pIOmap, uint8 group, int16 slave, uint32* LogAddr, uint8* BitPos)
{
	int BitCount = 0;
	int ByteCount = 0;
	int FMMUsize = 0;
	int FMMUdone = 0;
	uint8 SMc = 0;
	uint16 EndAddr;
	uint16 SMlength;
	uint16 configadr;
	uint8 FMMUc;

#if DEBUG_ETHERCAT_MSG
	printf("  OUTPUT MAPPING\r\n");
#endif

	FMMUc = pEC_Main->slave_list[slave].FMMUunused;
	configadr = pEC_Main->slave_list[slave].configadr;

	while ((SMc < (EC_MAX_SM - 1)) && (FMMUdone < ((pEC_Main->slave_list[slave].Obits + 7) / 8)))
	{
#if DEBUG_ETHERCAT_MSG
		printf("    FMMU %d\r\n", FMMUc);
#endif
		while ((SMc < (EC_MAX_SM - 1)) && (pEC_Main->slave_list[slave].SMtype[SMc] != 3))
		{
			SMc++;
		}
#if DEBUG_ETHERCAT_MSG
		printf("      SM%d\r\n", SMc);
#endif
		pEC_Main->slave_list[slave].FMMU[FMMUc].PhysStart =
			pEC_Main->slave_list[slave].SM[SMc].StartAddr;
		SMlength = etohs(pEC_Main->slave_list[slave].SM[SMc].SMlength);
		ByteCount += SMlength;
		BitCount += SMlength * 8;
		EndAddr = etohs(pEC_Main->slave_list[slave].SM[SMc].StartAddr) + SMlength;
		while ((BitCount < pEC_Main->slave_list[slave].Obits) && (SMc < (EC_MAX_SM - 1)))
		{
			SMc++;
			while ((SMc < (EC_MAX_SM - 1)) && (pEC_Main->slave_list[slave].SMtype[SMc] != 3))
			{
				SMc++;
			}
			if (etohs(pEC_Main->slave_list[slave].SM[SMc].StartAddr) > EndAddr)
			{
				break;
			}
#if DEBUG_ETHERCAT_MSG
			printf("      SM%d\r\n", SMc);
#endif
			SMlength = etohs(pEC_Main->slave_list[slave].SM[SMc].SMlength);
			ByteCount += SMlength;
			BitCount += SMlength * 8;
			EndAddr = etohs(pEC_Main->slave_list[slave].SM[SMc].StartAddr) + SMlength;
		}

		if (!pEC_Main->slave_list[slave].Obytes)
		{
			pEC_Main->slave_list[slave].FMMU[FMMUc].LogStart = htoel(*LogAddr);
			pEC_Main->slave_list[slave].FMMU[FMMUc].LogStartbit = *BitPos;
			*BitPos += pEC_Main->slave_list[slave].Obits - 1;
			if (*BitPos > 7)
			{
				*LogAddr += 1;
				*BitPos -= 8;
			}
			FMMUsize = *LogAddr - etohl(pEC_Main->slave_list[slave].FMMU[FMMUc].LogStart) + 1;
			pEC_Main->slave_list[slave].FMMU[FMMUc].LogLength = htoes(FMMUsize);
			pEC_Main->slave_list[slave].FMMU[FMMUc].LogEndbit = *BitPos;
			*BitPos += 1;
			if (*BitPos > 7)
			{
				*LogAddr += 1;
				*BitPos -= 8;
			}
		}
		else
		{
			if (*BitPos)
			{
				*LogAddr += 1;
				*BitPos = 0;
			}
			pEC_Main->slave_list[slave].FMMU[FMMUc].LogStart = htoel(*LogAddr);
			pEC_Main->slave_list[slave].FMMU[FMMUc].LogStartbit = *BitPos;
			*BitPos = 7;
			FMMUsize = ByteCount;
			if ((FMMUsize + FMMUdone) > (int)pEC_Main->slave_list[slave].Obytes)
			{
				FMMUsize = pEC_Main->slave_list[slave].Obytes - FMMUdone;
			}
			*LogAddr += FMMUsize;
			pEC_Main->slave_list[slave].FMMU[FMMUc].LogLength = htoes(FMMUsize);
			pEC_Main->slave_list[slave].FMMU[FMMUc].LogEndbit = *BitPos;
			*BitPos = 0;
		}
		FMMUdone += FMMUsize;
		pEC_Main->slave_list[slave].FMMU[FMMUc].PhysStartBit = 0;
		pEC_Main->slave_list[slave].FMMU[FMMUc].FMMUtype = 2;
		pEC_Main->slave_list[slave].FMMU[FMMUc].FMMUactive = 1;
		
		ecx_FPWR(configadr, ECT_REG_FMMU0 + (sizeof(ec_fmmu_t) * FMMUc),
			sizeof(ec_fmmu_t), &(pEC_Main->slave_list[slave].FMMU[FMMUc]));
		pEC_Main->group_list[group].outputsWKC++;
		if (!pEC_Main->slave_list[slave].outputs)
		{
			if (group)
			{
				pEC_Main->slave_list[slave].outputs =
					(uint8*)(pIOmap)+
					etohl(pEC_Main->slave_list[slave].FMMU[FMMUc].LogStart) -
					pEC_Main->group_list[group].logstartaddr;
			}
			else
			{
				pEC_Main->slave_list[slave].outputs =
					(uint8*)(pIOmap)+
					etohl(pEC_Main->slave_list[slave].FMMU[FMMUc].LogStart);
			}
			pEC_Main->slave_list[slave].Ostartbit =
				pEC_Main->slave_list[slave].FMMU[FMMUc].LogStartbit;

#if DEBUG_ETHERCAT_MSG
			printf("    slave %d Outputs %p startbit %d\r\n", \
				slave, pEC_Main->slave_list[slave].outputs, pEC_Main->slave_list[slave].Ostartbit);
#endif
		}
		FMMUc++;
	}
	pEC_Main->slave_list[slave].FMMUunused = FMMUc;
}

int EC_Config_Map_Group(EC_Main_t* pEC_Main, void* pIOmap, uint8 group)
{
	uint16 nSlave, nConfigadr;
	uint8 nBitPos;
	uint32 nLogAddr = 0;
	uint32 nLogAddr_1 = 0;
	uint32 nDiff;
	uint16 nCurrent_Segment = 0;
	uint32 Segment_Size = 0;

	if ((*(pEC_Main->slavecount) > 0) && (group < pEC_Main->maxgroup))
	{
#if DEBUG_ETHERCAT_MSG
		printf("ec_config_map_group IOmap:%p group:%d\r\n", pIOmap, group);
#endif
		nLogAddr = pEC_Main->group_list[group].logstartaddr;
		nLogAddr_1 = nLogAddr;
		nBitPos = 0;
		pEC_Main->group_list[group].nsegments = 0;
		pEC_Main->group_list[group].outputsWKC = 0;
		pEC_Main->group_list[group].inputsWKC = 0;

		EC_Config_Find_Map(pEC_Main, group);

		for (nSlave = 1; nSlave <= *(pEC_Main->slavecount); nSlave++)
		{
			nConfigadr = pEC_Main->slave_list[nSlave].configadr;

			if (!group || (group == pEC_Main->slave_list[nSlave].group))
			{
				if (pEC_Main->slave_list[nSlave].Obits)
				{
					EC_Config_Create_Output_Mappings(pEC_Main, pIOmap, group, nSlave, &nLogAddr, &nBitPos);
					nDiff = nLogAddr - nLogAddr_1;
					nLogAddr_1 = nLogAddr;
					if ((Segment_Size + nDiff) > (EC_MAX_LRWDATA - EC_FIRSTDCDATAGRAM))
					{
						pEC_Main->group_list[group].IOsegment[nCurrent_Segment] = Segment_Size;
						if (nCurrent_Segment < (EC_MAX_IO_SEGMENTS - 1))
						{
							nCurrent_Segment++;
							Segment_Size = nDiff;
						}
					}
					else
					{
						Segment_Size += nDiff;
					}
				}
			}
		}
		if (nBitPos)
		{
			nLogAddr++;
			nLogAddr_1 = nLogAddr;
			nBitPos = 0;
			if ((Segment_Size + 1) > (EC_MAX_LRWDATA - EC_FIRSTDCDATAGRAM))
			{
				pEC_Main->group_list[group].IOsegment[nCurrent_Segment] = Segment_Size;
				if (nCurrent_Segment < (EC_MAX_IO_SEGMENTS - 1))
				{
					nCurrent_Segment++;
					Segment_Size = 1;
				}
			}
			else
			{
				Segment_Size += 1;
			}
		}
		pEC_Main->group_list[group].outputs = pIOmap;
		pEC_Main->group_list[group].Obytes = nLogAddr - pEC_Main->group_list[group].logstartaddr;
		pEC_Main->group_list[group].nsegments = nCurrent_Segment + 1;
		pEC_Main->group_list[group].Isegment = nCurrent_Segment;
		pEC_Main->group_list[group].Ioffset = Segment_Size;
		if (!group)
		{
			pEC_Main->slave_list[0].outputs = pIOmap;
			pEC_Main->slave_list[0].Obytes = nLogAddr -
				pEC_Main->group_list[group].logstartaddr;
		}

		for (nSlave = 1; nSlave <= *(pEC_Main->slavecount); nSlave++)
		{
			nConfigadr = pEC_Main->slave_list[nSlave].configadr;
			if (!group || (group == pEC_Main->slave_list[nSlave].group))
			{
				if (pEC_Main->slave_list[nSlave].Ibits)
				{
					EC_Config_Create_Input_Mappings(pEC_Main, pIOmap, group, nSlave, &nLogAddr, &nBitPos);
					nDiff = nLogAddr - nLogAddr_1;
					nLogAddr_1 = nLogAddr;
					if ((Segment_Size + nDiff) > (EC_MAX_LRWDATA - EC_FIRSTDCDATAGRAM))
					{
						pEC_Main->group_list[group].IOsegment[nCurrent_Segment] = Segment_Size;
						if (nCurrent_Segment < (EC_MAX_IO_SEGMENTS - 1))
						{
							nCurrent_Segment++;
							Segment_Size = nDiff;
						}
					}
					else
					{
						Segment_Size += nDiff;
					}
				}

				EC_EEpromToPDI(pEC_Main, nSlave);
				if (pEC_Main->manualstatechange == 0)
				{
					ecx_FPWRw(nConfigadr, ECT_REG_ALCTL, htoes(EC_STATE_PRE_OP));
				}
				if (pEC_Main->slave_list[nSlave].blockLRW)
				{
					pEC_Main->group_list[group].blockLRW++;
				}
				pEC_Main->group_list[group].Ebuscurrent += pEC_Main->slave_list[nSlave].Ebuscurrent;
			}
		}
		if (nBitPos)
		{
			nLogAddr++;
			nLogAddr_1 = nLogAddr;
			nBitPos = 0;
			if ((Segment_Size + 1) > (EC_MAX_LRWDATA - EC_FIRSTDCDATAGRAM))
			{
				pEC_Main->group_list[group].IOsegment[nCurrent_Segment] = Segment_Size;
				if (nCurrent_Segment < (EC_MAX_IO_SEGMENTS - 1))
				{
					nCurrent_Segment++;
					Segment_Size = 1;
				}
			}
			else
			{
				Segment_Size += 1;
			}
		}
		pEC_Main->group_list[group].IOsegment[nCurrent_Segment] = Segment_Size;
		pEC_Main->group_list[group].nsegments = nCurrent_Segment + 1;
		pEC_Main->group_list[group].inputs = (uint8*)(pIOmap)+pEC_Main->group_list[group].Obytes;
		pEC_Main->group_list[group].Ibytes = nLogAddr -
			pEC_Main->group_list[group].logstartaddr -
			pEC_Main->group_list[group].Obytes;
		if (!group)
		{
			pEC_Main->slave_list[0].inputs = (uint8*)(pIOmap)+pEC_Main->slave_list[0].Obytes;
			pEC_Main->slave_list[0].Ibytes = nLogAddr -
				pEC_Main->group_list[group].logstartaddr -
				pEC_Main->slave_list[0].Obytes;
		}

#if DEBUG_ETHERCAT_MSG
		printf("IOmapSize = %ld\r\n", nLogAddr - pEC_Main->group_list[group].logstartaddr);
#endif

		return (nLogAddr - pEC_Main->group_list[group].logstartaddr);
	}

	return 0;
}

void EC_init_pEC_Main(EC_Main_t* pEC_Main)
{
	int lp;

	*(pEC_Main->slavecount) = 0;
	
	memset(pEC_Main->slave_list, 0x00, sizeof(EC_Slave_t) * pEC_Main->maxslave);
	memset(pEC_Main->group_list, 0x00, sizeof(EC_group_t) * pEC_Main->maxgroup);
	
	EC_SII_Read(pEC_Main, 0, EC_MAX_EEPROM_BUF);

	///*
	for (lp = 0; lp < pEC_Main->maxgroup; lp++)
	{
		pEC_Main->group_list[lp].logstartaddr = lp << EC_LOG_GROUP_OFFSET;
	}
	//*/

	//pEC_Main->group_list[0].logstartaddr = 0x01000000;
}

int EC_Detect_Slaves(EC_Main_t* pEC_Main)
{
	uint8  b;
	uint16 w = 0;
	int    wkc = 0;

	b = 0x00;
	ecx_BWR(0x0000, ECT_REG_DLALIAS, sizeof(b), &b);    
	b = EC_STATE_INIT | EC_STATE_ACK;
	ecx_BWR(0x0000, ECT_REG_ALCTL, sizeof(b), &b);       
	
	ecx_BWR(0x0000, ECT_REG_ALCTL, sizeof(b), &b);       
	wkc = ecx_BRD(0x0000, ECT_REG_TYPE, sizeof(w), &w);  
	if (wkc > 0)
	{
		if (wkc < EC_MAX_SLAVE)
		{
			*(pEC_Main->slavecount) = wkc;
		}
		else
		{
			return EC_SLAVE_COUNT_EXCEEDED;
		}
	}
	return wkc;
}

static void EC_set_slaves_to_default(EC_Main_t* pEC_Main)
{
	uint8 nBuf;
	uint16 nWord;
	uint8 nBufArr[256];

	memset(&nBufArr, 0x00, sizeof(nBufArr));

	nBuf = 0x52;
	ecx_BWR(0x0000, ECT_REG_RESET_ECAT, sizeof(nBuf), &nBuf);     // EtherCAT Reset 'R'
	ecx_BRD(0x0000, ECT_REG_RESET_ECAT, sizeof(nBuf), &nBuf);

	nBuf = 0x45;
	ecx_BWR(0x0000, ECT_REG_RESET_ECAT, sizeof(nBuf), &nBuf);     // EtherCAT Reset 'E'
	ecx_BRD(0x0000, ECT_REG_RESET_ECAT, sizeof(nBuf), &nBuf);

	nBuf = 0x53;
	ecx_BWR(0x0000, ECT_REG_RESET_ECAT, sizeof(nBuf), &nBuf);     // EtherCAT Reset 'S'
	ecx_BRD(0x0000, ECT_REG_RESET_ECAT, sizeof(nBuf), &nBuf);

	nBuf = 0x00;
	ecx_BWR(0x0000, ECT_REG_DLPORT, sizeof(nBuf), &nBuf);    
	nWord = htoes(0x0004);
	ecx_BWR(0x0000, ECT_REG_IRQMASK, sizeof(nWord), &nWord); 
	ecx_BWR(0x0000, ECT_REG_RXERR, 8, &nBufArr);  

	nWord = 0;
	ecx_BWR(0x0000, ECT_REG_STADR, sizeof(nWord), &nWord);  

// 	ecx_BWR(0x0000, ECT_REG_FMMU0, 16 * 3, &zbuf);  
// 	ecx_BWR(0x0000, ECT_REG_SM0, 8 * 4, &zbuf);  

	ecx_BWR(0x0000, ECT_REG_FMMU0, 16 * 16, &nBufArr); 
	ecx_BWR(0x0000, ECT_REG_SM0, 16 * 16, &nBufArr);  

	nBuf = 0x00;
	ecx_BWR(0x0000, ECT_REG_DCSYNCACT, sizeof(nBuf), &nBuf);   

	//ecx_BWR(0x0000, ECT_REG_DCSYSTIME, 4, &zbuf);  
	ecx_BWR(0x0000, ECT_REG_DCSYSTIME, 32, &nBufArr); 

	nWord = htoes(0x1000);
	ecx_BWR(0x0000, ECT_REG_DCSPEEDCNT, sizeof(nWord), &nWord);  
	nWord = htoes(0x0c00);
	ecx_BWR(0x0000, ECT_REG_DCTIMEFILT, sizeof(nWord), &nWord);  

	nBuf = 0x09;
	ecx_BWR(0x0000, ECT_REG_DCTIMEFILT2, sizeof(nBuf), &nBuf);   

	nBuf = 0x00;
	ecx_BWR(0x0000, ECT_REG_DLALIAS, sizeof(nBuf), &nBuf); 

	nBuf = EC_STATE_INIT | EC_STATE_ACK;
	ecx_BWR(0x0000, ECT_REG_ALCTL, sizeof(nBuf), &nBuf);

	nBuf = 2;
	ecx_BWR(0x0000, ECT_REG_EEPCFG, sizeof(nBuf), &nBuf);   

	nBuf = 0;
	ecx_BWR(0x0000, ECT_REG_EEPCFG, sizeof(nBuf), &nBuf); 
}


int EC_Config_Init(EC_Main_t* pEC_Main)
{
	uint16 slave, ADPh, configadr, ssigen;
	uint16 topology, estat;
	int16 topoc, slavec, aliasadr;
	uint8 b, h;
	uint8 SMc;
	uint32 eedat;
	int wkc, cindex, nSM;
	uint16 val16;

	EC_init_pEC_Main(pEC_Main);
	wkc = EC_Detect_Slaves(pEC_Main);
	if (wkc > 0)
	{
		EC_set_slaves_to_default(pEC_Main);
		for (slave = 1; slave <= *(pEC_Main->slavecount); slave++)
		{
			ADPh = (uint16)(1 - slave);
			val16 = ecx_APRDw(ADPh, ECT_REG_PDICTL);
			pEC_Main->slave_list[slave].Itype = etohs(val16);

			ecx_APWRw(ADPh, ECT_REG_STADR, htoes(slave + EC_NODEOFFSET));
			if (slave == 1)
			{
				b = 1;
			}
			else
			{
				b = 0;
			}
			ecx_APWRw(ADPh, ECT_REG_DLCTL, htoes(b));
			configadr = ecx_APRDw(ADPh, ECT_REG_STADR);
			configadr = etohs(configadr);
			pEC_Main->slave_list[slave].configadr = configadr;
			ecx_FPRD(configadr, ECT_REG_ALIAS, sizeof(aliasadr), &aliasadr);
			pEC_Main->slave_list[slave].aliasadr = etohs(aliasadr);
			ecx_FPRD(configadr, ECT_REG_EEPSTAT, sizeof(estat), &estat);
			estat = etohs(estat);
			if (estat & EC_ESTAT_R64)
			{
				pEC_Main->slave_list[slave].eep_8byte = 1;
			}

			val16 = etohs(2498);
			ecx_FPWRw(configadr, ECT_REG_WD_DIVIDER, val16);

			val16 = etohs(1500);
			ecx_FPWRw(configadr, ECT_REG_WD_PDI, val16);

			val16 = etohs(1500);
			ecx_FPWRw(configadr, ECT_REG_WD_PD, val16);

			EC_Read_EEprom1(pEC_Main, slave, ECT_SII_MANUF);	
		}

		for (slave = 1; slave <= *(pEC_Main->slavecount); slave++)
		{
			eedat = EC_Read_EEprom2(pEC_Main, slave, EC_TIMEOUT_EEPROM);
			pEC_Main->slave_list[slave].eep_man = etohl(eedat);
			EC_Read_EEprom1(pEC_Main, slave, ECT_SII_ID);
		}
		for (slave = 1; slave <= *(pEC_Main->slavecount); slave++)
		{
			eedat = EC_Read_EEprom2(pEC_Main, slave, EC_TIMEOUT_EEPROM);
			pEC_Main->slave_list[slave].eep_id = etohl(eedat);
			EC_Read_EEprom1(pEC_Main, slave, ECT_SII_REV);
		}
		for (slave = 1; slave <= *(pEC_Main->slavecount); slave++)
		{
			eedat = EC_Read_EEprom2(pEC_Main, slave, EC_TIMEOUT_EEPROM);
			pEC_Main->slave_list[slave].eep_rev = etohl(eedat);
			EC_Read_EEprom1(pEC_Main, slave, ECT_SII_RXMBXADR);
		}
		for (slave = 1; slave <= *(pEC_Main->slavecount); slave++)
		{
			eedat = EC_Read_EEprom2(pEC_Main, slave, EC_TIMEOUT_EEPROM);
			pEC_Main->slave_list[slave].mbx_wo = (uint16)LO_WORD(etohl(eedat));
			pEC_Main->slave_list[slave].mbx_l = (uint16)HI_WORD(etohl(eedat));
			if (pEC_Main->slave_list[slave].mbx_l > 0)
			{
				EC_Read_EEprom1(pEC_Main, slave, ECT_SII_TXMBXADR);
			}
		}
		for (slave = 1; slave <= *(pEC_Main->slavecount); slave++)
		{
			if (pEC_Main->slave_list[slave].mbx_l > 0)
			{
				eedat = EC_Read_EEprom2(pEC_Main, slave, EC_TIMEOUT_EEPROM);
				pEC_Main->slave_list[slave].mbx_ro = (uint16)LO_WORD(etohl(eedat));
				pEC_Main->slave_list[slave].mbx_rl = (uint16)HI_WORD(etohl(eedat));
				if (pEC_Main->slave_list[slave].mbx_rl == 0)
				{
					pEC_Main->slave_list[slave].mbx_rl = pEC_Main->slave_list[slave].mbx_l;
				}
				EC_Read_EEprom1(pEC_Main, slave, ECT_SII_MBXPROTO);
			}
			configadr = pEC_Main->slave_list[slave].configadr;
			val16 = ecx_FPRDw(configadr, ECT_REG_ESCSUP);
			if ((etohs(val16) & 0x04) > 0)
			{
				pEC_Main->slave_list[slave].hasdc = TRUE;
			}
			else
			{
				pEC_Main->slave_list[slave].hasdc = FALSE;
			}
			topology = ecx_FPRDw(configadr, ECT_REG_DLSTAT);
			topology = etohs(topology);
			h = 0;
			b = 0;
			if ((topology & 0x0300) == 0x0200)
			{
				h++;
				b |= 0x01;
			}
			if ((topology & 0x0c00) == 0x0800)
			{
				h++;
				b |= 0x02;
			}
			if ((topology & 0x3000) == 0x2000)
			{
				h++;
				b |= 0x04;
			}
			if ((topology & 0xc000) == 0x8000)
			{
				h++;
				b |= 0x08;
			}
			
			val16 = ecx_FPRDw(configadr, ECT_REG_PORTDES);
			pEC_Main->slave_list[slave].ptype = LO_BYTE(etohs(val16));
			pEC_Main->slave_list[slave].topology = h;
			pEC_Main->slave_list[slave].activeports = b;
			/* 0=no links, not possible             */
			/* 1=1 link  , end of line              */
			/* 2=2 links , one before and one after */
			/* 3=3 links , split point              */
			/* 4=4 links , cross point              */
			/* search for parent */
			pEC_Main->slave_list[slave].parent = 0;
			if (slave > 1)
			{
				topoc = 0;
				slavec = slave - 1;
				do
				{
					topology = pEC_Main->slave_list[slavec].topology;
					if (topology == 1)
					{
						topoc--; 
					}
					if (topology == 3)
					{
						topoc++; 
					}
					if (topology == 4)
					{
						topoc += 2;
					}
					if (((topoc >= 0) && (topology > 1)) ||
						(slavec == 1)) 
					{
						pEC_Main->slave_list[slave].parent = slavec;
						slavec = 1;
					}
					slavec--;
				} while (slavec > 0);
			}

			(void)EC_State_Check_1(pEC_Main, slave, EC_STATE_INIT, EC_TIMEOUT_STATE);

			if (pEC_Main->slave_list[slave].mbx_l > 0)
			{
				pEC_Main->slave_list[slave].SMtype[0] = 1;
				pEC_Main->slave_list[slave].SMtype[1] = 2;
				pEC_Main->slave_list[slave].SMtype[2] = 3;
				pEC_Main->slave_list[slave].SMtype[3] = 4;
				pEC_Main->slave_list[slave].SM[0].StartAddr = htoes(pEC_Main->slave_list[slave].mbx_wo);
				pEC_Main->slave_list[slave].SM[0].SMlength = htoes(pEC_Main->slave_list[slave].mbx_l);
				pEC_Main->slave_list[slave].SM[0].SMflags = htoel(EC_DEFAULT_MBX_SM0);
				pEC_Main->slave_list[slave].SM[1].StartAddr = htoes(pEC_Main->slave_list[slave].mbx_ro);
				pEC_Main->slave_list[slave].SM[1].SMlength = htoes(pEC_Main->slave_list[slave].mbx_rl);
				pEC_Main->slave_list[slave].SM[1].SMflags = htoel(EC_DEFAULT_MBX_SM1);
				eedat = EC_Read_EEprom2(pEC_Main, slave, EC_TIMEOUT_EEPROM);
				pEC_Main->slave_list[slave].mbx_proto = etohl(eedat);
			}
			cindex = 0;

			if (!cindex && !EC_lookup_prev_sii(pEC_Main, slave))
			{
				ssigen = EC_SII_Find(pEC_Main, slave, ECT_SII_GENERAL);
				if (ssigen)
				{
					pEC_Main->slave_list[slave].CoEdetails = EC_SII_Read(pEC_Main, slave, ssigen + 0x07);
					pEC_Main->slave_list[slave].FoEdetails = EC_SII_Read(pEC_Main, slave, ssigen + 0x08);
					pEC_Main->slave_list[slave].EoEdetails = EC_SII_Read(pEC_Main, slave, ssigen + 0x09);
					pEC_Main->slave_list[slave].SoEdetails = EC_SII_Read(pEC_Main, slave, ssigen + 0x0a);
					if ((EC_SII_Read(pEC_Main, slave, ssigen + 0x0d) & 0x02) > 0)
					{
						pEC_Main->slave_list[slave].blockLRW = 1;
						pEC_Main->slave_list[0].blockLRW++;
					}
					pEC_Main->slave_list[slave].Ebuscurrent = EC_SII_Read(pEC_Main, slave, ssigen + 0x0e);
					pEC_Main->slave_list[slave].Ebuscurrent += EC_SII_Read(pEC_Main, slave, ssigen + 0x0f) << 8;
					pEC_Main->slave_list[0].Ebuscurrent += pEC_Main->slave_list[slave].Ebuscurrent;
				}

				if (EC_SII_Find(pEC_Main, slave, ECT_SII_STRING) > 0)
				{
					EC_SII_String(pEC_Main, pEC_Main->slave_list[slave].name, slave, 1);
				}
				else
				{
#if DEBUG_ETHERCAT_MSG
					sprintf(pEC_Main->slave_list[slave].name, "? M:%8.8x I:%8.8x",
						(unsigned int)pEC_Main->slave_list[slave].eep_man,
						(unsigned int)pEC_Main->slave_list[slave].eep_id);
#endif
				}

				nSM = EC_SII_SM(pEC_Main, slave, pEC_Main->eepSM);
				if (nSM > 0)
				{
					pEC_Main->slave_list[slave].SM[0].StartAddr = htoes(pEC_Main->eepSM->PhStart);
					pEC_Main->slave_list[slave].SM[0].SMlength = htoes(pEC_Main->eepSM->Plength);
					pEC_Main->slave_list[slave].SM[0].SMflags =
						htoel((pEC_Main->eepSM->Creg) + (pEC_Main->eepSM->Activate << 16));
					SMc = 1;
					while ((SMc < EC_MAX_SM) && EC_SII_SM_Next(pEC_Main, slave, pEC_Main->eepSM, SMc))
					{
						pEC_Main->slave_list[slave].SM[SMc].StartAddr = htoes(pEC_Main->eepSM->PhStart);
						pEC_Main->slave_list[slave].SM[SMc].SMlength = htoes(pEC_Main->eepSM->Plength);
						pEC_Main->slave_list[slave].SM[SMc].SMflags =
							htoel((pEC_Main->eepSM->Creg) + (pEC_Main->eepSM->Activate << 16));
						SMc++;
					}
				}

				if (EC_SII_FMMU(pEC_Main, slave, pEC_Main->eepFMMU))
				{
					if (pEC_Main->eepFMMU->FMMU0 != 0xff)
					{
						pEC_Main->slave_list[slave].FMMU0func = pEC_Main->eepFMMU->FMMU0;
					}
					if (pEC_Main->eepFMMU->FMMU1 != 0xff)
					{
						pEC_Main->slave_list[slave].FMMU1func = pEC_Main->eepFMMU->FMMU1;
					}
					if (pEC_Main->eepFMMU->FMMU2 != 0xff)
					{
						pEC_Main->slave_list[slave].FMMU2func = pEC_Main->eepFMMU->FMMU2;
					}
					if (pEC_Main->eepFMMU->FMMU3 != 0xff)
					{
						pEC_Main->slave_list[slave].FMMU3func = pEC_Main->eepFMMU->FMMU3;
					}
				}
			}

			if (pEC_Main->slave_list[slave].mbx_l > 0)
			{
				if (pEC_Main->slave_list[slave].SM[0].StartAddr == 0x0000) 
				{
#if DEBUG_ETHERCAT_MSG
					printf("Slave %d has no proper mailbox in configuration, try default.\r\n", slave);
#endif
					pEC_Main->slave_list[slave].SM[0].StartAddr = htoes(0x1000);
					pEC_Main->slave_list[slave].SM[0].SMlength = htoes(0x0080);
					pEC_Main->slave_list[slave].SM[0].SMflags = htoel(EC_DEFAULT_MBX_SM0);
					pEC_Main->slave_list[slave].SMtype[0] = 1;
				}

				if (pEC_Main->slave_list[slave].SM[1].StartAddr == 0x0000)
				{
#if DEBUG_ETHERCAT_MSG
					printf("Slave %d has no proper mailbox out configuration, try default.\r\n", slave);
#endif
					pEC_Main->slave_list[slave].SM[1].StartAddr = htoes(0x1080);
					pEC_Main->slave_list[slave].SM[1].SMlength = htoes(0x0080);
					pEC_Main->slave_list[slave].SM[1].SMflags = htoel(EC_DEFAULT_MBX_SM1);
					pEC_Main->slave_list[slave].SMtype[1] = 2;
				}

				ecx_FPWR(configadr, ECT_REG_SM0, sizeof(ec_smt) * 2,
					&(pEC_Main->slave_list[slave].SM[0]));
			}

			EC_EEpromToPDI(pEC_Main, slave);
			if (pEC_Main->manualstatechange == 0)
			{
				ecx_FPWRw(configadr, ECT_REG_ALCTL, htoes(EC_STATE_PRE_OP | EC_STATE_ACK));
			}
		}
	}

	return wkc;
}

int ECAT_Config_Map(void* pIOmap)
{
	return EC_Config_Map_Group(&m_EC_Main, pIOmap, 0);
	//return EC_Config_Map_Group_1(&m_EC_Main, pIOmap, 0);
}

int ECAT_Config()
{
	int wkc = 0;

	wkc = EC_Config_Init(&m_EC_Main);

	return wkc;
}
