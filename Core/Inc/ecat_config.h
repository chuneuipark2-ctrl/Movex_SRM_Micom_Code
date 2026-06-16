
#ifndef _ETHERCAT_CONFIG_
#define _ETHERCAT_CONFIG_

#define EC_NODEOFFSET      0x1000
#define EC_TEMPNODE        0xffff

typedef const struct
{
	uint32           man;
	uint32           id;
	char             name[EC_MAX_NAME + 1];
	uint8            Dtype;
	uint16            Ibits;
	uint16           Obits;
	uint16           SM2a;
	uint32           SM2f;
	uint16           SM3a;
	uint32           SM3f;
	uint8            FM0ac;
	uint8            FM1ac;
} ec_configlist_t;

#define EC_DEFAULT_MBX_SM0  0x00010026
#define EC_DEFAULT_MBX_SM1  0x00010022
#define EC_DEFAULT_DO_SM0   0x00010044

int EC_Detect_Slaves(EC_Main_t* pEC_Main);
int ECAT_Config_Map(void* pIOmap);
int ECAT_Config();
#endif