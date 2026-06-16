

#include <stdio.h>
#include <string.h>

#include "rtc.h"

#include "ecat_type.h"
#include "ecat_combase.h"
#include "ecat_main.h"
#include "ecat_dc.h"

#define PORT_M0 0x01
#define PORT_M1 0x02
#define PORT_M2 0x04
#define PORT_M3 0x08

#define SyncDelay       ((int32)100000000)		 // 1st sync pulse delay in ns here 100ms

void EC_DC_Sync0(EC_Main_t* pEC_Main, uint16 slave, boolean act, uint32 CyclTime, int32 CyclShift)
{
	uint8 h = 0, RA = 0;
	uint16 slaveh = 0;
	int64 t, t1 = 0;
	int32 tc = 0;

	slaveh = pEC_Main->slave_list[slave].configadr;
	RA = 0;

	(void)ecx_FPWR(slaveh, ECT_REG_DCSYNCACT, sizeof(RA), &RA);
	if (act)
	{
		RA = 1 + 2;
	}
	h = 0;
	(void)ecx_FPWR(slaveh, ECT_REG_DCCUC, sizeof(h), &h);
	t1 = 0;
	(void)ecx_FPRD(slaveh, ECT_REG_DCSYSTIME, sizeof(t1), &t1);
	t1 = etohll(t1);

	if (CyclTime > 0)
	{
		t = ((t1 + SyncDelay) / CyclTime) * CyclTime + CyclTime + CyclShift;
	}
	else
	{
		t = t1 + SyncDelay + CyclShift;
	}
	t = htoell(t);
	(void)ecx_FPWR(slaveh, ECT_REG_DCSTART0, sizeof(t), &t);
	tc = htoel(CyclTime);
	(void)ecx_FPWR(slaveh, ECT_REG_DCCYCLE0, sizeof(tc), &tc);
	(void)ecx_FPWR(slaveh, ECT_REG_DCSYNCACT, sizeof(RA), &RA);

	pEC_Main->slave_list[slave].DCactive = (uint8)act;
	pEC_Main->slave_list[slave].DCshift = CyclShift;
	pEC_Main->slave_list[slave].DCcycle = CyclTime;
}


void EC_DC_Sync01(EC_Main_t* pEC_Main, uint16 slave, boolean act, uint32 CyclTime0, uint32 CyclTime1, int32 CyclShift)
{
	uint8 h, RA;
	uint16 slaveh;
	int64 t, t1;
	int32 tc;
	uint32 TrueCyclTime;

	TrueCyclTime = ((CyclTime1 / CyclTime0) + 1) * CyclTime0;

	slaveh = pEC_Main->slave_list[slave].configadr;
	RA = 0;

	(void)ecx_FPWR(slaveh, ECT_REG_DCSYNCACT, sizeof(RA), &RA);
	if (act)
	{
		RA = 1 + 2 + 4;
	}
	h = 0;
	(void)ecx_FPWR(slaveh, ECT_REG_DCCUC, sizeof(h), &h);
	t1 = 0;
	(void)ecx_FPRD(slaveh, ECT_REG_DCSYSTIME, sizeof(t1), &t1);
	t1 = etohll(t1);

	if (CyclTime0 > 0)
	{
		t = ((t1 + SyncDelay) / TrueCyclTime) * TrueCyclTime + TrueCyclTime + CyclShift;
	}
	else
	{
		t = t1 + SyncDelay + CyclShift;
	}
	t = htoell(t);
	(void)ecx_FPWR(slaveh, ECT_REG_DCSTART0, sizeof(t), &t);
	tc = htoel(CyclTime0);
	(void)ecx_FPWR(slaveh, ECT_REG_DCCYCLE0, sizeof(tc), &tc);
	tc = htoel(CyclTime1);
	(void)ecx_FPWR(slaveh, ECT_REG_DCCYCLE1, sizeof(tc), &tc);
	(void)ecx_FPWR(slaveh, ECT_REG_DCSYNCACT, sizeof(RA), &RA);

	pEC_Main->slave_list[slave].DCactive = (uint8)act;
	pEC_Main->slave_list[slave].DCshift = CyclShift;
	pEC_Main->slave_list[slave].DCcycle = CyclTime0;
}

static int32 EC_Port_Time(EC_Main_t* pEC_Main, uint16 slave, uint8 port)
{
	int32 ts;
	switch (port)
	{
	case 0:
		ts = pEC_Main->slave_list[slave].DCrtA;
		break;
	case 1:
		ts = pEC_Main->slave_list[slave].DCrtB;
		break;
	case 2:
		ts = pEC_Main->slave_list[slave].DCrtC;
		break;
	case 3:
		ts = pEC_Main->slave_list[slave].DCrtD;
		break;
	default:
		ts = 0;
		break;
	}
	return ts;
}

static uint8 EC_Prev_Port(EC_Main_t* pEC_Main, uint16 slave, uint8 port)
{
	uint8 pport = port;
	uint8 aport = pEC_Main->slave_list[slave].activeports;
	switch (port)
	{
	case 0:
		if (aport & PORT_M2)
			pport = 2;
		else if (aport & PORT_M1)
			pport = 1;
		else if (aport & PORT_M3)
			pport = 3;
		break;
	case 1:
		if (aport & PORT_M3)
			pport = 3;
		else if (aport & PORT_M0)
			pport = 0;
		else if (aport & PORT_M2)
			pport = 2;
		break;
	case 2:
		if (aport & PORT_M1)
			pport = 1;
		else if (aport & PORT_M3)
			pport = 3;
		else if (aport & PORT_M0)
			pport = 0;
		break;
	case 3:
		if (aport & PORT_M0)
			pport = 0;
		else if (aport & PORT_M2)
			pport = 2;
		else if (aport & PORT_M1)
			pport = 1;
		break;
	}
	return pport;
}

static uint8 EC_Parent_Port(EC_Main_t* pEC_Main, uint16 parent)
{
	uint8 parentport = 0;
	uint8 b;

	b = pEC_Main->slave_list[parent].consumedports;
	if (b & PORT_M3)
	{
		parentport = 3;
		b &= (uint8)~PORT_M3;
	}
	else if (b & PORT_M1)
	{
		parentport = 1;
		b &= (uint8)~PORT_M1;
	}
	else if (b & PORT_M2)
	{
		parentport = 2;
		b &= (uint8)~PORT_M2;
	}
	else if (b & PORT_M0)
	{
		parentport = 0;
		b &= (uint8)~PORT_M0;
	}
	pEC_Main->slave_list[parent].consumedports = b;
	return parentport;
}

/**
 * Locate DC slaves, measure propagation delays.
 *
 * @param[in]  pEC_Main        = pEC_Main struct
 * @return boolean if slaves are found with DC
 */
boolean EC_ConfigDC(EC_Main_t* pEC_Main)
{
	uint16 i, slaveh, parent, child;
	uint16 parenthold = 0;
	uint16 prevDCslave = 0;
	int32 ht, dt1, dt2, dt3;
	int64 hrt0, hrt1;
	uint8 entryport;
	int8 nlist;
	int8 plist[4];
	int32 tlist[4];
	EC_time_t mastertime;
	uint64 mastertime64;

	pEC_Main->slave_list[0].hasdc = FALSE;
	pEC_Main->group_list[0].hasdc = FALSE;
	ht = 0;

	ecx_BWR(0, ECT_REG_DCTIME0, sizeof(ht), &ht);  /* latch DCrecvTimeA of all slaves */

	//mastertime.sec = getTimeDate();
	mastertime.sec = getTimeDate_Rev2();
	mastertime.sec -= 946684800UL;  /* EtherCAT uses 2000-01-01 as epoch start instead of 1970-01-01 */
	mastertime.usec = 0;
	mastertime64 = (((uint64)mastertime.sec * 1000000) + (uint64)mastertime.usec) * 1000;
	for (i = 1; i <= *(pEC_Main->slavecount); i++)
	{
		pEC_Main->slave_list[i].consumedports = pEC_Main->slave_list[i].activeports;
		if (pEC_Main->slave_list[i].hasdc)
		{
			if (!pEC_Main->slave_list[0].hasdc)
			{
				pEC_Main->slave_list[0].hasdc = TRUE;
				pEC_Main->slave_list[0].DCnext = i;
				pEC_Main->slave_list[i].DCprevious = 0;
				pEC_Main->group_list[pEC_Main->slave_list[i].group].hasdc = TRUE;
				pEC_Main->group_list[pEC_Main->slave_list[i].group].DCnext = i;
			}
			else
			{
				pEC_Main->slave_list[prevDCslave].DCnext = i;
				pEC_Main->slave_list[i].DCprevious = prevDCslave;
			}
			/* this branch has DC slave so remove parenthold */
			parenthold = 0;
			prevDCslave = i;
			slaveh = pEC_Main->slave_list[i].configadr;
			(void)ecx_FPRD(slaveh, ECT_REG_DCTIME0, sizeof(ht), &ht);
			pEC_Main->slave_list[i].DCrtA = etohl(ht);
			/* 64bit latched DCrecvTimeA of each specific slave */
			(void)ecx_FPRD(slaveh, ECT_REG_DCSOF, sizeof(hrt0), &hrt0);
			/* use it as offset in order to set local time around 0 + mastertime */
			hrt1 = htoell(-etohll(hrt0) + mastertime64);
			/* save it in the offset register */
			(void)ecx_FPWR(slaveh, ECT_REG_DCSYSOFFSET, sizeof(hrt1), &hrt1);
			(void)ecx_FPRD(slaveh, ECT_REG_DCTIME1, sizeof(ht), &ht);
			pEC_Main->slave_list[i].DCrtB = etohl(ht);
			(void)ecx_FPRD(slaveh, ECT_REG_DCTIME2, sizeof(ht), &ht);
			pEC_Main->slave_list[i].DCrtC = etohl(ht);
			(void)ecx_FPRD(slaveh, ECT_REG_DCTIME3, sizeof(ht), &ht);
			pEC_Main->slave_list[i].DCrtD = etohl(ht);

			/* make list of active ports and their time stamps */
			nlist = 0;
			if (pEC_Main->slave_list[i].activeports & PORT_M0)
			{
				plist[nlist] = 0;
				tlist[nlist] = pEC_Main->slave_list[i].DCrtA;
				nlist++;
			}
			if (pEC_Main->slave_list[i].activeports & PORT_M3)
			{
				plist[nlist] = 3;
				tlist[nlist] = pEC_Main->slave_list[i].DCrtD;
				nlist++;
			}
			if (pEC_Main->slave_list[i].activeports & PORT_M1)
			{
				plist[nlist] = 1;
				tlist[nlist] = pEC_Main->slave_list[i].DCrtB;
				nlist++;
			}
			if (pEC_Main->slave_list[i].activeports & PORT_M2)
			{
				plist[nlist] = 2;
				tlist[nlist] = pEC_Main->slave_list[i].DCrtC;
				nlist++;
			}
			/* entryport is port with the lowest timestamp */
			entryport = 0;
			if ((nlist > 1) && (tlist[1] < tlist[entryport]))
			{
				entryport = 1;
			}
			if ((nlist > 2) && (tlist[2] < tlist[entryport]))
			{
				entryport = 2;
			}
			if ((nlist > 3) && (tlist[3] < tlist[entryport]))
			{
				entryport = 3;
			}
			entryport = plist[entryport];
			pEC_Main->slave_list[i].entryport = entryport;
			/* consume entryport from activeports */
			pEC_Main->slave_list[i].consumedports &= (uint8)~(1 << entryport);

			/* finding DC parent of current */
			parent = i;
			do
			{
				child = parent;
				parent = pEC_Main->slave_list[parent].parent;
			} while (!((parent == 0) || (pEC_Main->slave_list[parent].hasdc)));
			/* only calculate propagation delay if slave is not the first */
			if (parent > 0)
			{
				/* find port on parent this slave is connected to */
				pEC_Main->slave_list[i].parentport = EC_Parent_Port(pEC_Main, parent);
				if (pEC_Main->slave_list[parent].topology == 1)
				{
					pEC_Main->slave_list[i].parentport = pEC_Main->slave_list[parent].entryport;
				}

				dt1 = 0;
				dt2 = 0;
				/* delta time of (parentport - 1) - parentport */
				/* note: order of ports is 0 - 3 - 1 -2 */
				/* non active ports are skipped */
				dt3 = EC_Port_Time(pEC_Main, parent, pEC_Main->slave_list[i].parentport) -
					EC_Port_Time(pEC_Main, parent,
						EC_Prev_Port(pEC_Main, parent, pEC_Main->slave_list[i].parentport));
				/* current slave has children */
				/* those children's delays need to be subtracted */
				if (pEC_Main->slave_list[i].topology > 1)
				{
					dt1 = EC_Port_Time(pEC_Main, i,
						EC_Prev_Port(pEC_Main, i, pEC_Main->slave_list[i].entryport)) -
						EC_Port_Time(pEC_Main, i, pEC_Main->slave_list[i].entryport);
				}
				/* we are only interested in positive difference */
				if (dt1 > dt3) dt1 = -dt1;
				/* current slave is not the first child of parent */
				/* previous child's delays need to be added */
				if ((child - parent) > 1)
				{
					dt2 = EC_Port_Time(pEC_Main, parent,
						EC_Prev_Port(pEC_Main, parent, pEC_Main->slave_list[i].parentport)) -
						EC_Port_Time(pEC_Main, parent, pEC_Main->slave_list[parent].entryport);
				}
				if (dt2 < 0) dt2 = -dt2;

				/* calculate current slave delay from delta times */
				/* assumption : forward delay equals return delay */
				pEC_Main->slave_list[i].pdelay = ((dt3 - dt1) / 2) + dt2 +
					pEC_Main->slave_list[parent].pdelay;
				ht = htoel(pEC_Main->slave_list[i].pdelay);
				/* write propagation delay*/
				(void)ecx_FPWR(slaveh, ECT_REG_DCSYSDELAY, sizeof(ht), &ht);
			}
		}
		else
		{
			pEC_Main->slave_list[i].DCrtA = 0;
			pEC_Main->slave_list[i].DCrtB = 0;
			pEC_Main->slave_list[i].DCrtC = 0;
			pEC_Main->slave_list[i].DCrtD = 0;
			parent = pEC_Main->slave_list[i].parent;
			/* if non DC slave found on first position on branch hold root parent */
			if ((parent > 0) && (pEC_Main->slave_list[parent].topology > 2))
				parenthold = parent;
			/* if branch has no DC slaves consume port on root parent */
			if (parenthold && (pEC_Main->slave_list[i].topology == 1))
			{
				EC_Parent_Port(pEC_Main, parenthold);
				parenthold = 0;
			}
		}

		asm volatile("NOP");
	}

	return pEC_Main->slave_list[0].hasdc;
}

void ECAT_Dcsync0(uint16 slave, boolean act, uint32 CyclTime, int32 CyclShift)
{
	EC_DC_Sync0(&m_EC_Main, slave, act, CyclTime, CyclShift);
}


void ECAT_Dcsync01(uint16 slave, boolean act, uint32 CyclTime0, uint32 CyclTime1, int32 CyclShift)
{
	EC_DC_Sync01(&m_EC_Main, slave, act, CyclTime0, CyclTime1, CyclShift);
}


boolean ECAT_ConfigDC(void)
{
	return EC_ConfigDC(&m_EC_Main);
}
