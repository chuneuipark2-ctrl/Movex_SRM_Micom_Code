
#ifndef _EC_ECATDC_H
#define _EC_ECATDC_H

boolean ECAT_ConfigDC();
void ECAT_Dcsync0(uint16 slave, boolean act, uint32 CyclTime, int32 CyclShift);
void ECAT_Dcsync01(uint16 slave, boolean act, uint32 CyclTime0, uint32 CyclTime1, int32 CyclShift);

boolean EC_ConfigDC(EC_Main_t *context);
void EC_DC_Sync0(EC_Main_t *context, uint16 slave, boolean act, uint32 CyclTime, int32 CyclShift);
void EC_DC_Sync01(EC_Main_t *context, uint16 slave, boolean act, uint32 CyclTime0, uint32 CyclTime1, int32 CyclShift);

#endif /* _EC_ECATDC_H */
