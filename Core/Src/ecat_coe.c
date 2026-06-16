

#include <stdio.h>
#include <string.h>

#include "User_Define.h"
#include "ecat_type.h"
#include "ecat_combase.h"
#include "ecat_main.h"
#include "ecat_coe.h"


void EC_SDO_error(EC_Main_t* pEC_Main, uint16 Slave, uint16 Index, uint8 SubIdx, int32 AbortCode)
{
	EC_Error_t Ec;
	EC_time_t Time;

	Time.sec = 0;
	Time.usec = 0;

	memset(&Ec, 0, sizeof(Ec));
	
	Ec.Time = Time;
	Ec.Slave = Slave;
	Ec.Index = Index;
	Ec.SubIdx = SubIdx;
	*(pEC_Main->ecaterror) = TRUE;
	Ec.Etype = EC_ERR_TYPE_SDO_ERROR;
	Ec.AbortCode = AbortCode;
	EC_Push_Error(pEC_Main, &Ec);
}

static void EC_SDO_info_error(EC_Main_t* pEC_Main, uint16 Slave, uint16 Index, uint8 SubIdx, int32 AbortCode)
{
	EC_Error_t Ec_Err;

	memset(&Ec_Err, 0, sizeof(Ec_Err));
	Ec_Err.Slave = Slave;
	Ec_Err.Index = Index;
	Ec_Err.SubIdx = SubIdx;
	*(pEC_Main->ecaterror) = TRUE;
	Ec_Err.Etype = EC_ERR_TYPE_SDOINFO_ERROR;
	Ec_Err.AbortCode = AbortCode;
	EC_Push_Error(pEC_Main, &Ec_Err);
}

int EC_SDO_Read(EC_Main_t* pEC_Main, uint16 slave, uint16 index, uint8 subindex, boolean CA, int* psize, void* p, int timeout)
{
	EC_SDO_t* pSDO, * pSDOa;
	uint16 bytesize, Framedatasize;
	int wkc;
	int32 SDOlen;
	uint8* bp;
	uint8* hp;
	EC_Mbx_buffer_t MbxIn, MbxOut;
	uint8 cnt, toggle;
	boolean NotLast;
	
	EC_Clear_MailBox(&MbxIn);
	
	//wkc = ecx_mbxreceive(pEC_Main, slave, (ec_mbxbuft *)&MbxIn, 0);
	wkc = EC_MailBox_Receive(pEC_Main, slave, (EC_Mbx_buffer_t*)&MbxIn, 10);
	
	EC_Clear_MailBox(&MbxOut);
	pSDOa = (EC_SDO_t*)&MbxIn;
	pSDO = (EC_SDO_t*)&MbxOut;
	pSDO->MbxHeader.length = htoes(0x000a);
	pSDO->MbxHeader.address = htoes(0x0000);
	pSDO->MbxHeader.priority = 0x00;
	
	cnt = EC_Next_MailBox_Cnt(pEC_Main->slave_list[slave].mbx_cnt);
	pEC_Main->slave_list[slave].mbx_cnt = cnt;
	pSDO->MbxHeader.mbxtype = ECT_MBXT_COE + (cnt << 4); 
	pSDO->CANOpen = htoes(0x000 + (ECT_COES_SDOREQ << 12));
	if (CA)
	{
		pSDO->Command = ECT_SDO_UP_REQ_CA;
	}
	else
	{
		pSDO->Command = ECT_SDO_UP_REQ;
	}
	pSDO->Index = htoes(index);
	if (CA && (subindex > 1))
	{
		subindex = 1;
	}
	pSDO->SubIndex = subindex;
	pSDO->ldata[0] = 0;

	wkc = EC_MailBox_Send(pEC_Main, slave, (EC_Mbx_buffer_t*)&MbxOut, EC_TIMEOUT_TXM);
	if (wkc > 0)
	{
		EC_Clear_MailBox(&MbxIn);
		
		wkc = EC_MailBox_Receive(pEC_Main, slave, (EC_Mbx_buffer_t*)&MbxIn, timeout);
		if (wkc > 0)
		{
			if (((pSDOa->MbxHeader.mbxtype & 0x0f) == ECT_MBXT_COE) &&
				((etohs(pSDOa->CANOpen) >> 12) == ECT_COES_SDORES) &&
				(pSDOa->Index == pSDO->Index))
			{
				if ((pSDOa->Command & 0x02) > 0)
				{
					bytesize = 4 - ((pSDOa->Command >> 2) & 0x03);
					if (*psize >= bytesize)
					{
						memcpy(p, &pSDOa->ldata[0], bytesize);
						*psize = bytesize;
					}
					else
					{
						wkc = 0;
						EC_Packet_Error(pEC_Main, slave, index, subindex, 3);
					}
				}
				else
				{ 
					SDOlen = etohl(pSDOa->ldata[0]);
					if (SDOlen <= *psize)
					{
						bp = p;
						hp = p;
					
						Framedatasize = (etohs(pSDOa->MbxHeader.length) - 10);
						if (Framedatasize < SDOlen)
						{
							memcpy(hp, &pSDOa->ldata[1], Framedatasize);
						
							hp += Framedatasize;
							*psize = Framedatasize;
							NotLast = TRUE;
							toggle = 0x00;
							while (NotLast)
							{
								pSDO = (EC_SDO_t*)&MbxOut;
								pSDO->MbxHeader.length = htoes(0x000a);
								pSDO->MbxHeader.address = htoes(0x0000);
								pSDO->MbxHeader.priority = 0x00;
								cnt = EC_Next_MailBox_Cnt(pEC_Main->slave_list[slave].mbx_cnt);
								pEC_Main->slave_list[slave].mbx_cnt = cnt;
								pSDO->MbxHeader.mbxtype = ECT_MBXT_COE + (cnt << 4);
								pSDO->CANOpen = htoes(0x000 + (ECT_COES_SDOREQ << 12));
								pSDO->Command = ECT_SDO_SEG_UP_REQ + toggle;
								pSDO->Index = htoes(index);
								pSDO->SubIndex = subindex;
								pSDO->ldata[0] = 0;
								
								wkc = EC_MailBox_Send(pEC_Main, slave, (EC_Mbx_buffer_t*)&MbxOut, EC_TIMEOUT_TXM);
								if (wkc > 0)
								{
									EC_Clear_MailBox(&MbxIn);
									
									wkc = EC_MailBox_Receive(pEC_Main, slave, (EC_Mbx_buffer_t*)&MbxIn, timeout);
									if (wkc > 0)
									{
										if ((((pSDOa->MbxHeader.mbxtype & 0x0f) == ECT_MBXT_COE) &&
											((etohs(pSDOa->CANOpen) >> 12) == ECT_COES_SDORES) &&
											((pSDOa->Command & 0xe0) == 0x00)))
										{
											Framedatasize = etohs(pSDOa->MbxHeader.length) - 3;
											if ((pSDOa->Command & 0x01) > 0)
											{ 
												NotLast = FALSE;
												if (Framedatasize == 7)
													Framedatasize = Framedatasize - ((pSDOa->Command & 0x0e) >> 1);

												memcpy(hp, &(pSDOa->Index), Framedatasize);
											}
											else
											{
												memcpy(hp, &(pSDOa->Index), Framedatasize);
												hp += Framedatasize;
											}
											*psize += Framedatasize;
										}
										else
										{
											NotLast = FALSE;
											if ((pSDOa->Command) == ECT_SDO_ABORT)
												EC_SDO_error(pEC_Main, slave, index, subindex, etohl(pSDOa->ldata[0]));
											else
												EC_Packet_Error(pEC_Main, slave, index, subindex, 1);
											wkc = 0;
										}
									}
								}
								toggle = toggle ^ 0x10;
							}
						}					
						else
						{
	
							memcpy(bp, &pSDOa->ldata[1], SDOlen);
							*psize = SDOlen;
						}
					}
					else
					{
						wkc = 0;
						EC_Packet_Error(pEC_Main, slave, index, subindex, 3);
					}
				}
			}
			else
			{
				if ((pSDOa->Command) == ECT_SDO_ABORT)
				{
					EC_SDO_error(pEC_Main, slave, index, subindex, etohl(pSDOa->ldata[0]));
				}
				else
				{
					EC_Packet_Error(pEC_Main, slave, index, subindex, 1);
				}
				wkc = 0;
			}
		}
	}
	return wkc;
}

int EC_SDO_Write(EC_Main_t* pEC_Main, uint16 Slave, uint16 Index, uint8 SubIndex, boolean CA, int psize, void* p, int Timeout)
{
	EC_SDO_t* SDOp, * aSDOp;
	int wkc, maxdata;
	EC_Mbx_buffer_t MbxIn, MbxOut;
	uint8 cnt, toggle;
	uint16 framedatasize;
	boolean  NotLast;
	uint8* hp;

	EC_Clear_MailBox(&MbxIn);

	/* Empty slave out mailbox if something is in. Timeout set to 0 */
	wkc = EC_MailBox_Receive(pEC_Main, Slave, (EC_Mbx_buffer_t*)&MbxIn, 10);
	EC_Clear_MailBox(&MbxOut);
	aSDOp = (EC_SDO_t*)&MbxIn;
	SDOp = (EC_SDO_t*)&MbxOut;
	maxdata = pEC_Main->slave_list[Slave].mbx_l - 0x10;

	if ((psize <= 4) && !CA)
	{
		SDOp->MbxHeader.length = htoes(0x000a);
		SDOp->MbxHeader.address = htoes(0x0000);
		SDOp->MbxHeader.priority = 0x00;
		cnt = EC_Next_MailBox_Cnt(pEC_Main->slave_list[Slave].mbx_cnt);
		pEC_Main->slave_list[Slave].mbx_cnt = cnt;
		SDOp->MbxHeader.mbxtype = ECT_MBXT_COE + (cnt << 4);
		SDOp->CANOpen = htoes(0x000 + (ECT_COES_SDOREQ << 12)); 
		SDOp->Command = ECT_SDO_DOWN_EXP | (((4 - psize) << 2) & 0x0c);
		SDOp->Index = htoes(Index);
		SDOp->SubIndex = SubIndex;
		//hp = p;
		hp = (uint8*)p;
		//memcpy(&SDOp->ldata[0], hp, sizeof(uint8) * psize);
		memcpy(&SDOp->bdata[0], hp, sizeof(uint8) * psize);

		wkc = EC_MailBox_Send(pEC_Main, Slave, (EC_Mbx_buffer_t*)&MbxOut, EC_TIMEOUT_TXM);
		if (wkc > 0)
		{
			EC_Clear_MailBox(&MbxIn);
			wkc = EC_MailBox_Receive(pEC_Main, Slave, (EC_Mbx_buffer_t*)&MbxIn, Timeout);
			if (wkc > 0)
			{
				if (((aSDOp->MbxHeader.mbxtype & 0x0f) == ECT_MBXT_COE) &&
					((etohs(aSDOp->CANOpen) >> 12) == ECT_COES_SDORES) &&
					(aSDOp->Index == SDOp->Index) &&
					(aSDOp->SubIndex == SDOp->SubIndex))
				{
					/* all OK */
				}
				else
				{
					if (aSDOp->Command == ECT_SDO_ABORT)
					{
						EC_SDO_error(pEC_Main, Slave, Index, SubIndex, etohl(aSDOp->ldata[0]));
					}
					else
					{
						EC_Packet_Error(pEC_Main, Slave, Index, SubIndex, 1);
					}
					wkc = 0;
				}
			}
		}
	}
	else
	{
		framedatasize = psize;
		NotLast = FALSE;
		if (framedatasize > maxdata)
		{
			framedatasize = maxdata;
			NotLast = TRUE;
		}

		SDOp->MbxHeader.length = htoes(0x0a + framedatasize);
		SDOp->MbxHeader.address = htoes(0x0000);
		SDOp->MbxHeader.priority = 0x00;

		cnt = EC_Next_MailBox_Cnt(pEC_Main->slave_list[Slave].mbx_cnt);
		pEC_Main->slave_list[Slave].mbx_cnt = cnt;
		SDOp->MbxHeader.mbxtype = ECT_MBXT_COE + (cnt << 4);
		SDOp->CANOpen = htoes(0x000 + (ECT_COES_SDOREQ << 12));
		if (CA)
		{
			SDOp->Command = ECT_SDO_DOWN_INIT_CA;
		}
		else
		{
			SDOp->Command = ECT_SDO_DOWN_INIT;
		}
		SDOp->Index = htoes(Index);
		SDOp->SubIndex = SubIndex;
		if (CA && (SubIndex > 1))
		{
			SDOp->SubIndex = 1;
		}
		SDOp->ldata[0] = htoel(psize);
		hp = p;
		memcpy(&SDOp->ldata[1], hp, framedatasize);
		hp += framedatasize;
		psize -= framedatasize;
		wkc = EC_MailBox_Send(pEC_Main, Slave, (EC_Mbx_buffer_t*)&MbxOut, EC_TIMEOUT_TXM);
		if (wkc > 0)
		{
			EC_Clear_MailBox(&MbxIn);
			wkc = EC_MailBox_Receive(pEC_Main, Slave, (EC_Mbx_buffer_t*)&MbxIn, Timeout);
			if (wkc > 0)
			{
				if (((aSDOp->MbxHeader.mbxtype & 0x0f) == ECT_MBXT_COE) &&
					((etohs(aSDOp->CANOpen) >> 12) == ECT_COES_SDORES) &&
					(aSDOp->Index == SDOp->Index) &&
					(aSDOp->SubIndex == SDOp->SubIndex))
				{
					/* all ok */
					maxdata += 7;
					toggle = 0;
					while (NotLast)
					{
						SDOp = (EC_SDO_t*)&MbxOut;
						framedatasize = psize;
						NotLast = FALSE;
						SDOp->Command = 0x01;
						if (framedatasize > maxdata)
						{
							framedatasize = maxdata; 
							NotLast = TRUE;
							SDOp->Command = 0x00;
						}

						if (!NotLast && (framedatasize < 7))
						{
							SDOp->MbxHeader.length = htoes(0x0a);
							SDOp->Command = 0x01 + ((7 - framedatasize) << 1);
						}
						else
						{
							SDOp->MbxHeader.length = htoes(framedatasize + 3); /* data + 2 CoE + 1 SDO */
						}
						SDOp->MbxHeader.address = htoes(0x0000);
						SDOp->MbxHeader.priority = 0x00;
						
						cnt = EC_Next_MailBox_Cnt(pEC_Main->slave_list[Slave].mbx_cnt);
						pEC_Main->slave_list[Slave].mbx_cnt = cnt;
						SDOp->MbxHeader.mbxtype = ECT_MBXT_COE + (cnt << 4);
						SDOp->CANOpen = htoes(0x000 + (ECT_COES_SDOREQ << 12));
						SDOp->Command = SDOp->Command + toggle;
						
						memcpy(&SDOp->Index, hp, framedatasize);
						
						hp += framedatasize;
						psize -= framedatasize;
						
						wkc = EC_MailBox_Send(pEC_Main, Slave, (EC_Mbx_buffer_t*)&MbxOut, EC_TIMEOUT_TXM);
						if (wkc > 0)
						{
							EC_Clear_MailBox(&MbxIn);
							wkc = EC_MailBox_Receive(pEC_Main, Slave, (EC_Mbx_buffer_t*)&MbxIn, Timeout);
							if (wkc > 0)
							{
								if (((aSDOp->MbxHeader.mbxtype & 0x0f) == ECT_MBXT_COE) &&
									((etohs(aSDOp->CANOpen) >> 12) == ECT_COES_SDORES) &&
									((aSDOp->Command & 0xe0) == 0x20))
								{
									/* all OK, nothing to do */
								}
								else
								{
									if (aSDOp->Command == ECT_SDO_ABORT)
									{
										EC_SDO_error(pEC_Main, Slave, Index, SubIndex, etohl(aSDOp->ldata[0]));
									}
									else
									{
										EC_Packet_Error(pEC_Main, Slave, Index, SubIndex, 1);
									}
									wkc = 0;
									NotLast = FALSE;
								}
							}
						}
						toggle = toggle ^ 0x10;
					}
				}
				else
				{
					if (aSDOp->Command == ECT_SDO_ABORT)
					{
						EC_SDO_error(pEC_Main, Slave, Index, SubIndex, etohl(aSDOp->ldata[0]));
					}
					else
					{
						EC_Packet_Error(pEC_Main, Slave, Index, SubIndex, 1);
					}
					wkc = 0;
				}
			}
		}
	}

	return wkc;
}

/*
int ecx_RxPDO(EC_pEC_Main_t* pEC_Main, uint16 Slave, uint16 RxPDOnumber, int psize, void* p)
{
	ec_SDOt* SDOp;
	int wkc, maxdata;
	EC_Mbx_buffer_t MbxIn, MbxOut;
	uint8 cnt;
	uint16 framedatasize;

	EC_Clear_MailBox(&MbxIn);
	wkc = EC_MailBox_Receive(pEC_Main, Slave, (EC_Mbx_buffer_t*)&MbxIn, 0);
	EC_Clear_MailBox(&MbxOut);
	SDOp = (ec_SDOt*)&MbxOut;
	maxdata = pEC_Main->slavelist[Slave].mbx_l - 0x08;
	framedatasize = psize;
	if (framedatasize > maxdata)
	{
		framedatasize = maxdata;
	}
	SDOp->MbxHeader.length = htoes(0x02 + framedatasize);
	SDOp->MbxHeader.address = htoes(0x0000);
	SDOp->MbxHeader.priority = 0x00;
	cnt = EC_Next_MailBox_Cnt(pEC_Main->slavelist[Slave].mbx_cnt);
	pEC_Main->slavelist[Slave].mbx_cnt = cnt;
	SDOp->MbxHeader.mbxtype = ECT_MBXT_COE + (cnt << 4);
	SDOp->CANOpen = htoes((RxPDOnumber & 0x01ff) + (ECT_COES_RXPDO << 12));

	memcpy(&SDOp->Command, p, framedatasize);

	wkc = EC_MailBox_Send(pEC_Main, Slave, (EC_Mbx_buffer_t*)&MbxOut, EC_TIMEOUT_TXM);

	return wkc;
}
*/

/*
int ecx_TxPDO(EC_pEC_Main_t* pEC_Main, uint16 slave, uint16 TxPDOnumber, int* psize, void* p, int timeout)
{
	ec_SDOt* SDOp, * aSDOp;
	int wkc;
	EC_Mbx_buffer_t MbxIn, MbxOut;
	uint8 cnt;
	uint16 framedatasize;

	EC_Clear_MailBox(&MbxIn);
	wkc = EC_MailBox_Receive(pEC_Main, slave, (EC_Mbx_buffer_t*)&MbxIn, 0);
	EC_Clear_MailBox(&MbxOut);
	aSDOp = (ec_SDOt*)&MbxIn;
	SDOp = (ec_SDOt*)&MbxOut;
	SDOp->MbxHeader.length = htoes(0x02);
	SDOp->MbxHeader.address = htoes(0x0000);
	SDOp->MbxHeader.priority = 0x00;
	cnt = EC_Next_MailBox_Cnt(pEC_Main->slavelist[slave].mbx_cnt);
	pEC_Main->slavelist[slave].mbx_cnt = cnt;
	SDOp->MbxHeader.mbxtype = ECT_MBXT_COE + (cnt << 4);
	SDOp->CANOpen = htoes((TxPDOnumber & 0x01ff) + (ECT_COES_TXPDO_RR << 12));
	wkc = EC_MailBox_Send(pEC_Main, slave, (EC_Mbx_buffer_t*)&MbxOut, EC_TIMEOUT_TXM);
	if (wkc > 0)
	{
		EC_Clear_MailBox(&MbxIn);
		wkc = EC_MailBox_Receive(pEC_Main, slave, (EC_Mbx_buffer_t*)&MbxIn, timeout);
		if (wkc > 0)
		{
			if (((aSDOp->MbxHeader.mbxtype & 0x0f) == ECT_MBXT_COE) &&
				((etohs(aSDOp->CANOpen) >> 12) == ECT_COES_TXPDO))
			{
				framedatasize = (aSDOp->MbxHeader.length - 2);
				if (*psize >= framedatasize)
				{
					memcpy(p, &aSDOp->Command, framedatasize);
					*psize = framedatasize;
				}
				else
				{
					wkc = 0;
					EC_Packet_Error(pEC_Main, slave, 0, 0, 3);
				}
			}
			else
			{
				if ((aSDOp->Command) == ECT_SDO_ABORT)
				{
					ecx_SDOerror(pEC_Main, slave, 0, 0, etohl(aSDOp->ldata[0]));
				}
				else
				{
					EC_Packet_Error(pEC_Main, slave, 0, 0, 1);
				}
				wkc = 0;
			}
		}
	}

	return wkc;
}
*/

int EC_Read_PDOassign(EC_Main_t* pEC_Main, uint16 Slave, uint16 PDOassign)
{
	uint16 idxloop, nidx, subidxloop, rdat, idx, subidx;
	uint8 subcnt;
	int wkc, bsize = 0, rdl;
	int32 rdat2;

	rdl = sizeof(rdat); rdat = 0;
	wkc = EC_SDO_Read(pEC_Main, Slave, PDOassign, 0x00, FALSE, &rdl, &rdat, EC_TIMEOUT_RXM);
	rdat = etohs(rdat);

	if ((wkc > 0) && (rdat > 0))
	{
		nidx = rdat;
		bsize = 0;
		for (idxloop = 1; idxloop <= nidx; idxloop++)
		{
			rdl = sizeof(rdat); rdat = 0;
			wkc = EC_SDO_Read(pEC_Main, Slave, PDOassign, (uint8)idxloop, FALSE, &rdl, &rdat, EC_TIMEOUT_RXM);
			idx = etohs(rdat);
			if (idx > 0)
			{
				rdl = sizeof(subcnt); subcnt = 0;
				wkc = EC_SDO_Read(pEC_Main, Slave, idx, 0x00, FALSE, &rdl, &subcnt, EC_TIMEOUT_RXM);
				subidx = subcnt;
				for (subidxloop = 1; subidxloop <= subidx; subidxloop++)
				{
					rdl = sizeof(rdat2); rdat2 = 0;
					wkc = EC_SDO_Read(pEC_Main, Slave, idx, (uint8)subidxloop, FALSE, &rdl, &rdat2, EC_TIMEOUT_RXM);
					rdat2 = etohl(rdat2);
					if (LO_BYTE(rdat2) < 0xff)
					{
						bsize += LO_BYTE(rdat2);
					}
					else
					{
						rdl = sizeof(rdat); rdat = htoes(0xff);

						//wkc = ec_readOEsingle(idx, (uint8)SubCount, pODlist, pOElist);
						bsize += etohs(rdat);
					}
				}
			}
		}
	}
	
	return bsize;
}


int EC_Read_PDOassignCA(EC_Main_t* pEC_Main, uint16 Slave, int Thread_n, uint16 PDOassign)
{
	uint16 idxloop, nidx, subidxloop, idx, subidx;
	int wkc, bsize = 0, rdl;

	rdl = sizeof(EC_PDOassign_t);
	pEC_Main->PDOassign[Thread_n].n = 0;
	wkc = EC_SDO_Read(pEC_Main, Slave, PDOassign, 0x00, TRUE, &rdl,
		&(pEC_Main->PDOassign[Thread_n]), EC_TIMEOUT_RXM);

	if ((wkc > 0) && (pEC_Main->PDOassign[Thread_n].n > 0))
	{
		nidx = pEC_Main->PDOassign[Thread_n].n;

		bsize = 0;
		for (idxloop = 1; idxloop <= nidx; idxloop++)
		{
			idx = etohs(pEC_Main->PDOassign[Thread_n].index[idxloop - 1]);
			if (idx > 0)
			{
				rdl = sizeof(EC_PDOdesc_t); pEC_Main->PDOdesc[Thread_n].n = 0;

				wkc = EC_SDO_Read(pEC_Main, Slave, idx, 0x00, TRUE, &rdl,
					&(pEC_Main->PDOdesc[Thread_n]), EC_TIMEOUT_RXM);
				subidx = pEC_Main->PDOdesc[Thread_n].n;

				for (subidxloop = 1; subidxloop <= subidx; subidxloop++)
				{
					bsize += LO_BYTE(etohl(pEC_Main->PDOdesc[Thread_n].PDO[subidxloop - 1]));
				}
			}
		}
	}

	return bsize;
}

int EC_Read_PDOassignCA_1(EC_Main_t* pEC_Main, uint16 Slave, int Thread_n, uint16 PDOassign, uint8 iSm)
{
	uint16 idxloop, nidx, subidxloop, idx, subidx;
	int wkc, bsize = 0, rdl;

	rdl = sizeof(EC_PDOassign_t);
	pEC_Main->PDOassign[Thread_n].n = 0;
	wkc = EC_SDO_Read(pEC_Main, Slave, PDOassign, 0x00, TRUE, &rdl,
		&(pEC_Main->PDOassign[Thread_n]), EC_TIMEOUT_RXM);

	if ((wkc > 0) && (pEC_Main->PDOassign[Thread_n].n > 0))
	{
		nidx = pEC_Main->PDOassign[Thread_n].n;

		bsize = 0;
		for (idxloop = 1; idxloop <= nidx; idxloop++)
		{
			idx = etohs(pEC_Main->PDOassign[Thread_n].index[idxloop - 1]);
			if (idx > 0)
			{
				if (idxloop == 1)
				{
					pEC_Main->slave_list[Slave].SM[iSm].StartAddr = idx;
					asm volatile("NOP");
				}

				rdl = sizeof(EC_PDOdesc_t); pEC_Main->PDOdesc[Thread_n].n = 0;

				wkc = EC_SDO_Read(pEC_Main, Slave, idx, 0x00, TRUE, &rdl,
					&(pEC_Main->PDOdesc[Thread_n]), EC_TIMEOUT_RXM);
				subidx = pEC_Main->PDOdesc[Thread_n].n;

				for (subidxloop = 1; subidxloop <= subidx; subidxloop++)
				{
					bsize += LO_BYTE(etohl(pEC_Main->PDOdesc[Thread_n].PDO[subidxloop - 1]));
				}
			}
		}
	}

	return bsize;
}

int EC_Read_PDOmap(EC_Main_t* pEC_Main, uint16 Slave, int* Osize, int* Isize)
{
	int wkc, rdl;
	int retVal = 0;
	uint8 nSM, iSM, tSM;
	int Tsize;
	uint8 SMt_bug_add;

	*Isize = 0;
	*Osize = 0;
	SMt_bug_add = 0;
	rdl = sizeof(nSM); nSM = 0;
	wkc = EC_SDO_Read(pEC_Main, Slave, ECT_SDO_SM_COMM_TYPE, 0x00, FALSE, &rdl, &nSM, EC_TIMEOUT_RXM);

	if ((wkc > 0) && (nSM > 2))
	{
		if (nSM > EC_MAX_SM)
			nSM = EC_MAX_SM;

		for (iSM = 2; iSM < nSM; iSM++)
		{
			rdl = sizeof(tSM); tSM = 0;
			wkc = EC_SDO_Read(pEC_Main, Slave, ECT_SDO_SM_COMM_TYPE, iSM + 1, FALSE, &rdl, &tSM, EC_TIMEOUT_RXM);
			if (wkc > 0)
			{
				if ((iSM == 2) && (tSM == 2))
				{
					SMt_bug_add = 1;
				}
				if (tSM)
				{
					tSM += SMt_bug_add;
				}
				if ((iSM == 2) && (tSM == 0))
				{
					tSM = 3;
				}
				if ((iSM == 3) && (tSM == 0))
				{
					tSM = 4;
				}

				pEC_Main->slave_list[Slave].SMtype[iSM] = tSM;
				if (tSM == 0)
				{
					pEC_Main->slave_list[Slave].SM[iSM].SMflags =
						htoel(etohl(pEC_Main->slave_list[Slave].SM[iSM].SMflags) & EC_SMENABLEMASK);
				}
				if ((tSM == 3) || (tSM == 4))
				{
					Tsize = EC_Read_PDOassign(pEC_Main, Slave, ECT_SDO_PDO_ASSIGN + iSM);
					if (Tsize)
					{
						pEC_Main->slave_list[Slave].SM[iSM].SMlength = htoes((Tsize + 7) / 8);
						if (tSM == 3)
						{
							*Osize += Tsize;
						}
						else
						{
							*Isize += Tsize;
						}
					}
				}
			}
		}
	}

	if ((*Isize > 0) || (*Osize > 0))
	{
		retVal = 1;
	}

	return retVal;
}

int EC_Read_PDOmap_CA(EC_Main_t* pEC_Main, uint16 Slave, int Thread_n, int* Osize, int* Isize)
{
	int wkc, rdl;
	int retVal = 0;
	uint8 nSM, iSM, tSM;
	int Tsize;
	uint8 SMt_bug_add;

	*Isize = 0;
	*Osize = 0;
	SMt_bug_add = 0;
	rdl = sizeof(EC_SMcommtype_t);
	pEC_Main->SMcommtype[Thread_n].n = 0;

	wkc = EC_SDO_Read(pEC_Main, Slave, ECT_SDO_SM_COMM_TYPE, 0x00, TRUE, &rdl,
		&(pEC_Main->SMcommtype[Thread_n]), EC_TIMEOUT_RXM);

	if ((wkc > 0) && (pEC_Main->SMcommtype[Thread_n].n > 2))
	{
		nSM = pEC_Main->SMcommtype[Thread_n].n;
		if (nSM > EC_MAX_SM)
		{
			nSM = EC_MAX_SM;
			EC_Packet_Error(pEC_Main, Slave, 0, 0, 10);
		}

		for (iSM = 2; iSM < nSM; iSM++)
		{
			tSM = pEC_Main->SMcommtype[Thread_n].SMtype[iSM];

			if ((iSM == 2) && (tSM == 2))
			{
				SMt_bug_add = 1;
			}
			if (tSM)
			{
				tSM += SMt_bug_add;
			}

			pEC_Main->slave_list[Slave].SMtype[iSM] = tSM;
			if (tSM == 0)
			{
				pEC_Main->slave_list[Slave].SM[iSM].SMflags =
					htoel(etohl(pEC_Main->slave_list[Slave].SM[iSM].SMflags) & EC_SMENABLEMASK);
			}
			if ((tSM == 3) || (tSM == 4))
			{
				///*
				Tsize = EC_Read_PDOassignCA(pEC_Main, Slave, Thread_n,
					ECT_SDO_PDO_ASSIGN + iSM);
				//*/

				/*
				Tsize = EC_Read_PDOassignCA_1(pEC_Main, Slave, Thread_n,
					ECT_SDO_PDO_ASSIGN + iSM, iSM);
				*/
				if (Tsize)
				{
					pEC_Main->slave_list[Slave].SM[iSM].SMlength = htoes((Tsize + 7) / 8);
					if (tSM == 3)
					{
						*Osize += Tsize;
					}
					else
					{
						*Isize += Tsize;
					}
				}
			}
		}
	}

	if ((*Isize > 0) || (*Osize > 0))
	{
		retVal = 1;
	}
	return retVal;
}

int EC_Read_ODlist(EC_Main_t* pEC_Main, uint16 Slave, EC_ODlist_t* pODlist)
{
	EC_SDOservice_t* SDOp, * aSDOp;
	EC_Mbx_buffer_t MbxIn, MbxOut;
	int wkc;
	uint16 x, n, i, sp, offset;
	boolean stop;
	uint8 cnt;
	boolean First;

	pODlist->Slave = Slave;
	pODlist->Entries = 0;
	EC_Clear_MailBox(&MbxIn);

	//wkc = ecx_mbxreceive(pEC_Main, Slave, &MbxIn, 0);
	wkc = EC_MailBox_Receive(pEC_Main, Slave, &MbxIn, 10);
	EC_Clear_MailBox(&MbxOut);
	aSDOp = (EC_SDOservice_t*)&MbxIn;
	SDOp = (EC_SDOservice_t*)&MbxOut;
	SDOp->MbxHeader.length = htoes(0x0008);
	SDOp->MbxHeader.address = htoes(0x0000);
	SDOp->MbxHeader.priority = 0x00;

	cnt = EC_Next_MailBox_Cnt(pEC_Main->slave_list[Slave].mbx_cnt);
	pEC_Main->slave_list[Slave].mbx_cnt = cnt;
	SDOp->MbxHeader.mbxtype = ECT_MBXT_COE + (cnt << 4); 
	SDOp->CANOpen = htoes(0x000 + (ECT_COES_SDOINFO << 12)); 
	SDOp->Opcode = ECT_GET_ODLIST_REQ; 
	SDOp->Reserved = 0;
	SDOp->Fragments = 0;
	SDOp->wdata[0] = htoes(0x01);
	
	wkc = EC_MailBox_Send(pEC_Main, Slave, &MbxOut, EC_TIMEOUT_TXM);
	if (wkc > 0)
	{
		x = 0;
		sp = 0;
		First = TRUE;
		offset = 1;
		do
		{
			stop = TRUE;
			EC_Clear_MailBox(&MbxIn);
			wkc = EC_MailBox_Receive(pEC_Main, Slave, &MbxIn, EC_TIMEOUT_RXM);
			if (wkc > 0)
			{
				if (((aSDOp->MbxHeader.mbxtype & 0x0f) == ECT_MBXT_COE) &&
					((aSDOp->Opcode & 0x7f) == ECT_GET_ODLIST_RES))
				{
					if (First)
					{
						n = (etohs(aSDOp->MbxHeader.length) - (6 + 2)) / 2;
					}
					else
					{
						n = (etohs(aSDOp->MbxHeader.length) - 6) / 2;
					}

					if ((sp + n) > EC_MAX_OD_LIST)
					{
						n = EC_MAX_OD_LIST + 1 - sp;
						EC_SDO_info_error(pEC_Main, Slave, 0, 0, 0xf000000);
						stop = TRUE;
					}

					if ((pODlist->Entries + n) > EC_MAX_OD_LIST)
					{
						n = EC_MAX_OD_LIST - pODlist->Entries;
					}

					pODlist->Entries += n;
					for (i = 0; i < n; i++)
					{
						pODlist->Index[sp + i] = etohs(aSDOp->wdata[i + offset]);
					}

					sp += n;
					if (aSDOp->Fragments > 0)
					{
						stop = FALSE;
					}
					First = FALSE;
					offset = 0;
				}
				else
				{
					if ((aSDOp->Opcode & 0x7f) == ECT_SDOINFO_ERROR)
					{
						EC_SDO_info_error(pEC_Main, Slave, 0, 0, etohl(aSDOp->ldata[0]));
						stop = TRUE;
					}
					else
					{
						EC_Packet_Error(pEC_Main, Slave, 0, 0, 1);
					}
					wkc = 0;
					x += 20;
				}
			}
			x++;
		} while ((x <= 128) && !stop);
	}
	return wkc;
}


int EC_Read_ODdescription(EC_Main_t* pEC_Main, uint16 Item, EC_ODlist_t* pODlist)
{
	EC_SDOservice_t* SDOp, * aSDOp;
	int wkc;
	uint16  n, Slave;
	EC_Mbx_buffer_t MbxIn, MbxOut;
	uint8 cnt;

	Slave = pODlist->Slave;
	pODlist->DataType[Item] = 0;
	pODlist->ObjectCode[Item] = 0;
	pODlist->MaxSub[Item] = 0;
	pODlist->Name[Item][0] = 0;
	EC_Clear_MailBox(&MbxIn);

	wkc = EC_MailBox_Receive(pEC_Main, Slave, &MbxIn, 0);
	EC_Clear_MailBox(&MbxOut);
	aSDOp = (EC_SDOservice_t*)&MbxIn;
	SDOp = (EC_SDOservice_t*)&MbxOut;
	SDOp->MbxHeader.length = htoes(0x0008);
	SDOp->MbxHeader.address = htoes(0x0000);
	SDOp->MbxHeader.priority = 0x00;

	cnt = EC_Next_MailBox_Cnt(pEC_Main->slave_list[Slave].mbx_cnt);
	pEC_Main->slave_list[Slave].mbx_cnt = cnt;
	SDOp->MbxHeader.mbxtype = ECT_MBXT_COE + (cnt << 4); 
	SDOp->CANOpen = htoes(0x000 + (ECT_COES_SDOINFO << 12));
	SDOp->Opcode = ECT_GET_OD_REQ;
	SDOp->Reserved = 0;
	SDOp->Fragments = 0;
	SDOp->wdata[0] = htoes(pODlist->Index[Item]);
	
	wkc = EC_MailBox_Send(pEC_Main, Slave, &MbxOut, EC_TIMEOUT_TXM);
	if (wkc > 0)
	{
		EC_Clear_MailBox(&MbxIn);
		wkc = EC_MailBox_Receive(pEC_Main, Slave, &MbxIn, EC_TIMEOUT_RXM);
		if (wkc > 0)
		{
			if (((aSDOp->MbxHeader.mbxtype & 0x0f) == ECT_MBXT_COE) &&
				((aSDOp->Opcode & 0x7f) == ECT_GET_OD_RES))
			{
				n = (etohs(aSDOp->MbxHeader.length) - 12);
				if (n > EC_MAX_NAME)
				{
					n = EC_MAX_NAME; 
				}
				pODlist->DataType[Item] = etohs(aSDOp->wdata[1]);
				pODlist->ObjectCode[Item] = aSDOp->bdata[5];
				pODlist->MaxSub[Item] = aSDOp->bdata[4];

				strncpy(pODlist->Name[Item], (char*)&aSDOp->bdata[6], n);
				pODlist->Name[Item][n] = 0x00; 
			}
			else
			{
				if (((aSDOp->Opcode & 0x7f) == ECT_SDOINFO_ERROR))
				{
					EC_SDO_info_error(pEC_Main, Slave, pODlist->Index[Item], 0, etohl(aSDOp->ldata[0]));
				}
				else
				{
					EC_Packet_Error(pEC_Main, Slave, pODlist->Index[Item], 0, 1);
				}
				wkc = 0;
			}
		}
	}

	return wkc;
}


int EC_Read_OEsingle(EC_Main_t* pEC_Main, uint16 Item, uint8 SubI, EC_ODlist_t* pODlist, EC_OElist_t* pOElist)
{
	EC_SDOservice_t* SDOp, * aSDOp;
	int wkc;
	uint16 Index, Slave;
	int16 n;
	EC_Mbx_buffer_t MbxIn, MbxOut;
	uint8 cnt;

	wkc = 0;
	Slave = pODlist->Slave;
	Index = pODlist->Index[Item];
	EC_Clear_MailBox(&MbxIn);
	wkc = EC_MailBox_Receive(pEC_Main, Slave, &MbxIn, 0);
	EC_Clear_MailBox(&MbxOut);
	aSDOp = (EC_SDOservice_t*)&MbxIn;
	SDOp = (EC_SDOservice_t*)&MbxOut;
	SDOp->MbxHeader.length = htoes(0x000a);
	SDOp->MbxHeader.address = htoes(0x0000);
	SDOp->MbxHeader.priority = 0x00;
	cnt = EC_Next_MailBox_Cnt(pEC_Main->slave_list[Slave].mbx_cnt);
	pEC_Main->slave_list[Slave].mbx_cnt = cnt;
	SDOp->MbxHeader.mbxtype = ECT_MBXT_COE + (cnt << 4);
	SDOp->CANOpen = htoes(0x000 + (ECT_COES_SDOINFO << 12));
	SDOp->Opcode = ECT_GET_OE_REQ;
	SDOp->Reserved = 0;
	SDOp->Fragments = 0;  
	SDOp->wdata[0] = htoes(Index);
	SDOp->bdata[2] = SubI;      
	SDOp->bdata[3] = 1 + 2 + 4; 
	
	wkc = EC_MailBox_Send(pEC_Main, Slave, &MbxOut, EC_TIMEOUT_TXM);
	if (wkc > 0)
	{
		EC_Clear_MailBox(&MbxIn);
		wkc = EC_MailBox_Receive(pEC_Main, Slave, &MbxIn, EC_TIMEOUT_RXM);
		if (wkc > 0)
		{
			if (((aSDOp->MbxHeader.mbxtype & 0x0f) == ECT_MBXT_COE) &&
				((aSDOp->Opcode & 0x7f) == ECT_GET_OE_RES))
			{
				pOElist->Entries++;
				n = (etohs(aSDOp->MbxHeader.length) - 16);
				if (n > EC_MAX_NAME)
				{
					n = EC_MAX_NAME;
				}
				if (n < 0)
				{
					n = 0;
				}
				pOElist->ValueInfo[SubI] = aSDOp->bdata[3];
				pOElist->DataType[SubI] = etohs(aSDOp->wdata[2]);
				pOElist->BitLength[SubI] = etohs(aSDOp->wdata[3]);
				pOElist->ObjAccess[SubI] = etohs(aSDOp->wdata[4]);

				strncpy(pOElist->Name[SubI], (char*)&aSDOp->wdata[5], n);
				pOElist->Name[SubI][n] = 0x00;
			}
			else
			{
				if (((aSDOp->Opcode & 0x7f) == ECT_SDOINFO_ERROR))
				{
					EC_SDO_info_error(pEC_Main, Slave, Index, SubI, etohl(aSDOp->ldata[0]));
				}
				else
				{
					EC_Packet_Error(pEC_Main, Slave, Index, SubI, 1);
				}
				wkc = 0;
			}
		}
	}

	return wkc;
}

int EC_ReadOE_1(EC_Main_t* pEC_Main, uint16 Item, EC_ODlist_t* pODlist, EC_OElist_t* pOElist)
{
	uint16 SubCount;
	int wkc;
	uint8 SubI;

	wkc = 0;
	pOElist->Entries = 0;
	SubI = pODlist->MaxSub[Item];
	
	for (SubCount = 0; SubCount <= SubI; SubCount++)
	{
		wkc = EC_Read_OEsingle(pEC_Main, Item, (uint8)SubCount, pODlist, pOElist);
	}

	return wkc;
}

int EC_SDOread(uint16 slave, uint16 index, uint8 subindex,
	boolean CA, int* psize, void* p, int timeout)
{
	return EC_SDO_Read(&m_EC_Main, slave, index, subindex, CA, psize, p, timeout);
}

int EC_SDOwrite(uint16 Slave, uint16 Index, uint8 SubIndex, boolean CA, int psize, void* p, int Timeout)
{
#if DEBUG_ETHERCAT_MSG
	/*
	int i = 0;

	printf("(ec_SDOwrite) Slave:%d Index:%x SubIndex:%x CA:%d psize:%d Data:", Slave, Index, SubIndex, CA, psize);
	for (i = 0; i < psize; i++)
	{
		printf(" %x", *(INT08U*)(p + i));
	}

	printf("\r\n");
	*/
#endif

	return EC_SDO_Write(&m_EC_Main, Slave, Index, SubIndex, CA, psize, p, Timeout);
}

int EC_ReadODlist(uint16 Slave, EC_ODlist_t* pODlist)
{
	return EC_Read_ODlist(&m_EC_Main, Slave, pODlist);
}

int EC_ReadODdescription(uint16 Item, EC_ODlist_t* pODlist)
{
	return EC_Read_ODdescription(&m_EC_Main, Item, pODlist);
}

int EC_ReadOEsingle(uint16 Item, uint8 SubI, EC_ODlist_t* pODlist, EC_OElist_t* pOElist)
{
	return EC_Read_OEsingle(&m_EC_Main, Item, SubI, pODlist, pOElist);
}

int EC_ReadOE(uint16 Item, EC_ODlist_t* pODlist, EC_OElist_t* pOElist)
{
	return EC_ReadOE_1(&m_EC_Main, Item, pODlist, pOElist);
}
