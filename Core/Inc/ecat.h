
#ifndef _EC_ETHERCAT_H
#define _EC_ETHERCAT_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "ecat_type.h"
#include "ecat_combase.h"
#include "ecat_main.h"

#include "ecat_dc.h"
#include "ecat_coe.h"
#include "ecat_config.h"

#include "fpga.h"

#define GetEthercatRxData_Func    getFPGAEthercat
#define PutEthercatTxData_Func    putFPGAEthercat
#define SetEthercatMacAddr_Func   set_FPGA_EthCat_MAC_Address
#define SetEthercatIpAddr_Func    set_FPGA_EthCat_IP_Address


#endif /* _EC_ETHERCAT_H */
