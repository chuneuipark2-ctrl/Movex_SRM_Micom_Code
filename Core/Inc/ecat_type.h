
#ifndef _EC_TYPE_H
#define _EC_TYPE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

#include "type.h"

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

#define EC_NO_FRAME					(-1)
#define EC_OTHER_FRAME				(-2)
#define EC_ERROR					(-3)
#define EC_SLAVE_COUNT_EXCEEDED		(-4)
#define EC_TIMEOUT					(-5)
#define EC_MAX_ECAT_FRAME			(1518)

// Ethernet header - length - datagram header - WCK - FCS
#define EC_MAX_LRWDATA      (EC_MAX_ECAT_FRAME - 14 - 2 - 10 - 2 - 4)

// size of DC datagram used in first LRW frame
#define EC_FIRSTDCDATAGRAM (20)

//#define EC_BUFSIZE         EC_MAX_ECAT_FRAME
//#define EC_ECATTYPE        0x1000
#define EC_MAXBUF          16

#define EC_TIMEOUT_RETRY		(2000)
#define EC_TIMEOUT_RETRY3		(EC_TIMEOUT_RETRY * 3)
#define EC_TIMEOUT_SAFE			(20000)
#define EC_TIMEOUT_EEPROM		(20000)
//#define EC_TIMEOUT_EEPROM     (20)

#define EC_TIMEOUT_TXM			(20000)
#define EC_TIMEOUT_RXM			(700000)
#define EC_TIMEOUT_STATE		(2000000)
//#define EC_TIMEOUT_STATE		(200000)

#define EC_MAX_EEPROM_BITMAP    (128)

#define EC_MAX_EEPROM_BUF		(EC_MAX_EEPROM_BITMAP << 5)

#define EC_DEFAULT_RETRIES  3

#define EC_LOG_GROUP_OFFSET 16

/*
struct __attribute__((__packed__)) Tag_ec_comt
{
	uint16  elength;
	uint8   command;
	uint8   index;
	uint16  ADP;
	uint16  ADO;
	uint16  dlength;
	uint16  irpt;
};
typedef struct Tag_ec_comt  ec_comt;
*/

typedef enum
{
   EC_STATE_INIT           = 0x01,  
   EC_STATE_PRE_OP         = 0x02,  
   EC_STATE_BOOT           = 0x03,  
   EC_STATE_SAFE_OP        = 0x04,  
   EC_STATE_OPERATIONAL    = 0x08,  
   EC_STATE_ACK            = 0x10,  
   EC_STATE_ERROR          = 0x10
} EC_state;

typedef enum
{
   ECT_BOOLEAN         = 0x0001,
   ECT_INTEGER8        = 0x0002,
   ECT_INTEGER16       = 0x0003,
   ECT_INTEGER32       = 0x0004,
   ECT_UNSIGNED8       = 0x0005,
   ECT_UNSIGNED16      = 0x0006,
   ECT_UNSIGNED32      = 0x0007,
   ECT_REAL32          = 0x0008,
   ECT_VISIBLE_STRING  = 0x0009,
   ECT_OCTET_STRING    = 0x000A,
   ECT_UNICODE_STRING  = 0x000B,
   ECT_TIME_OF_DAY     = 0x000C,
   ECT_TIME_DIFFERENCE = 0x000D,
   ECT_DOMAIN          = 0x000F,
   ECT_INTEGER24       = 0x0010,
   ECT_REAL64          = 0x0011,
   ECT_INTEGER64       = 0x0015,
   ECT_UNSIGNED24      = 0x0016,
   ECT_UNSIGNED64      = 0x001B,
   ECT_BIT1            = 0x0030,
   ECT_BIT2            = 0x0031,
   ECT_BIT3            = 0x0032,
   ECT_BIT4            = 0x0033,
   ECT_BIT5            = 0x0034,
   ECT_BIT6            = 0x0035,
   ECT_BIT7            = 0x0036,
   ECT_BIT8            = 0x0037
} EC_Data_type;

typedef enum 
{
   EC_CMD_NOP = 0x00,  // No operation 
   EC_CMD_APRD,        // Auto Increment Read 
   EC_CMD_APWR,        // Auto Increment Write 
   EC_CMD_APRW,        // Auto Increment Read Write  
   EC_CMD_FPRD,        // Configured Address Read    
   EC_CMD_FPWR,        // Configured Address Write   
   EC_CMD_FPRW,        // Configured Address Read Write 
   EC_CMD_BRD,         // Broadcast Read   
   EC_CMD_BWR,         // Broadcast Write 
   EC_CMD_BRW,         // Broadcast Read Write 
   EC_CMD_LRD,         // Logical Memory Read 
   EC_CMD_LWR,         // Logical Memory Write 
   EC_CMD_LRW,         // Logical Memory Read Write 
   EC_CMD_ARMW,        // Auto Increment Read Multiple Write 
   EC_CMD_FRMW         // Configured Read Multiple Write 
} EC_cmd_type;


typedef enum 
{
   EC_ECMD_NOP         = 0x0000,  // No operation 
   EC_ECMD_READ        = 0x0100,  // Read 
   EC_ECMD_WRITE       = 0x0201,  // Write 
   EC_ECMD_RELOAD      = 0x0300   // Reload 
} EC_ecmd_type;

#define EC_ESTAT_R64    0x0040    // EEprom state machine read size 
#define EC_ESTAT_BUSY   0x8000    // EEprom state machine busy flag 
#define EC_ESTAT_EMASK  0x7800    // EEprom state machine error flag mask 
#define EC_ESTAT_NACK   0x2000    // EEprom state machine error acknowledge 

// Start address SII sections in Eeprom 
#define ECT_SII_START   0x0040

enum
{
   ECT_SII_STRING      = 10,  // SII category strings 
   ECT_SII_GENERAL     = 30,  // SII category general
   ECT_SII_FMMU        = 40,  // SII category FMMU 
   ECT_SII_SM          = 41,  // SII category SM 
   ECT_SII_PDO         = 50   // SII category PDO 
};

// Item offsets in SII general section
enum
{
   ECT_SII_MANUF       = 0x0008,
   ECT_SII_ID          = 0x000a,
   ECT_SII_REV         = 0x000c,
   ECT_SII_BOOTRXMBX   = 0x0014,
   ECT_SII_BOOTTXMBX   = 0x0016,
   ECT_SII_MBXSIZE     = 0x0019,
   ECT_SII_TXMBXADR    = 0x001a,
   ECT_SII_RXMBXADR    = 0x0018,
   ECT_SII_MBXPROTO    = 0x001c
};

enum
{
   ECT_MBXT_ERR = 0x00,  // Error mailbox type  
   ECT_MBXT_AOE,         // ADS over EtherCAT mailbox type      
   ECT_MBXT_EOE,         // Ethernet over EtherCAT mailbox type   
   ECT_MBXT_COE,         // CANopen over EtherCAT mailbox type    
   ECT_MBXT_FOE,         // File over EtherCAT mailbox type    
   ECT_MBXT_SOE,         // Servo over EtherCAT mailbox type     
   ECT_MBXT_VOE = 0x0f   // Vendor over EtherCAT mailbox type          
};

enum
{
   ECT_COES_EMERGENCY = 0x01,
   ECT_COES_SDOREQ,
   ECT_COES_SDORES,
   ECT_COES_TXPDO,
   ECT_COES_RXPDO,
   ECT_COES_TXPDO_RR,
   ECT_COES_RXPDO_RR,
   ECT_COES_SDOINFO
};

enum
{
   ECT_SDO_DOWN_INIT    = 0x21,
   ECT_SDO_DOWN_EXP     = 0x23,
   ECT_SDO_DOWN_INIT_CA = 0x31,
   ECT_SDO_UP_REQ       = 0x40,
   ECT_SDO_UP_REQ_CA    = 0x50,
   ECT_SDO_SEG_UP_REQ   = 0x60,
   ECT_SDO_ABORT        = 0x80
};

enum
{
   ECT_GET_ODLIST_REQ  = 0x01,
   ECT_GET_ODLIST_RES  = 0x02,
   ECT_GET_OD_REQ      = 0x03,
   ECT_GET_OD_RES      = 0x04,
   ECT_GET_OE_REQ      = 0x05,
   ECT_GET_OE_RES      = 0x06,
   ECT_SDOINFO_ERROR   = 0x07
};

enum
{
   ECT_FOE_READ        = 0x01,
   ECT_FOE_WRITE,
   ECT_FOE_DATA,
   ECT_FOE_ACK,
   ECT_FOE_ERROR,
   ECT_FOE_BUSY
};

enum
{
   ECT_SOE_READREQ     = 0x01,
   ECT_SOE_READRES,
   ECT_SOE_WRITEREQ,
   ECT_SOE_WRITERES,
   ECT_SOE_NOTIFICATION,
   ECT_SOE_EMERGENCY
};

enum 
{
   ECT_REG_TYPE        = 0x0000,
   ECT_REG_REVISION    = 0x0001,
   ECT_REG_BUILD       = 0x0002,
   ECT_REG_FMMU_COUNT  = 0x0004,
   ECT_REG_SM_COUNT    = 0x0005,
   ECT_REG_DPRAM       = 0x0006,
   ECT_REG_PORTDES     = 0x0007,
   ECT_REG_ESCSUP      = 0x0008,
   ECT_REG_STADR       = 0x0010,
   ECT_REG_ALIAS       = 0x0012,
   ECT_REG_RESET_ECAT  = 0x0040,
   ECT_REG_RESET_PDI   = 0x0041,
   ECT_REG_DLCTL       = 0x0100,
   ECT_REG_DLPORT      = 0x0101,
   ECT_REG_DLALIAS     = 0x0103,
   ECT_REG_DLSTAT      = 0x0110,
   ECT_REG_ALCTL       = 0x0120,
   ECT_REG_ALSTAT      = 0x0130,
   ECT_REG_ALSTATCODE  = 0x0134,
   ECT_REG_PDICTL      = 0x0140,
   ECT_REG_IRQMASK     = 0x0200,
   ECT_REG_RXERR       = 0x0300,
   ECT_REG_FRXERR      = 0x0308,
   ECT_REG_EPUECNT     = 0x030C,
   ECT_REG_PECNT       = 0x030D,
   ECT_REG_PECODE      = 0x030E,
   ECT_REG_LLCNT       = 0x0310,
   ECT_REG_WD_DIVIDER  = 0x0400,
   ECT_REG_WD_PDI      = 0x0410,
   ECT_REG_WD_PD       = 0x0420,
   ECT_REG_WD_SPD      = 0x0440,
   ECT_REG_WDCNT       = 0x0442,
   ECT_REG_EEPCFG      = 0x0500,
   ECT_REG_EEPSTATE    = 0x0501,
   ECT_REG_EEPCTL      = 0x0502,
   ECT_REG_EEPSTAT     = 0x0502,
   ECT_REG_EEPADR      = 0x0504,
   ECT_REG_EEPDAT      = 0x0508,
   ECT_REG_FMMU0       = 0x0600,
   ECT_REG_FMMU1       = ECT_REG_FMMU0 + 0x10,
   ECT_REG_FMMU2       = ECT_REG_FMMU1 + 0x10,
   ECT_REG_FMMU3       = ECT_REG_FMMU2 + 0x10,
   ECT_REG_SM0         = 0x0800,
   ECT_REG_SM1         = ECT_REG_SM0 + 0x08,
   ECT_REG_SM2         = ECT_REG_SM1 + 0x08,
   ECT_REG_SM3         = ECT_REG_SM2 + 0x08,
   ECT_REG_SM0STAT     = ECT_REG_SM0 + 0x05,
   ECT_REG_SM1STAT     = ECT_REG_SM1 + 0x05,
   ECT_REG_SM1ACT      = ECT_REG_SM1 + 0x06,
   ECT_REG_SM1CONTR    = ECT_REG_SM1 + 0x07,
   ECT_REG_DCTIME0     = 0x0900,
   ECT_REG_DCTIME1     = 0x0904,
   ECT_REG_DCTIME2     = 0x0908,
   ECT_REG_DCTIME3     = 0x090C,
   ECT_REG_DCSYSTIME   = 0x0910,
   ECT_REG_DCSOF       = 0x0918,
   ECT_REG_DCSYSOFFSET = 0x0920,
   ECT_REG_DCSYSDELAY  = 0x0928,
   ECT_REG_DCSYSDIFF   = 0x092C,
   ECT_REG_DCSPEEDCNT  = 0x0930,
   ECT_REG_DCTIMEFILT  = 0x0934,
   ECT_REG_DCTIMEFILT2 = 0x0935,
   ECT_REG_DCCUC       = 0x0980,
   ECT_REG_DCSYNCACT   = 0x0981,
   ECT_REG_DCSTART0    = 0x0990,
   ECT_REG_DCCYCLE0    = 0x09A0,
   ECT_REG_DCCYCLE1    = 0x09A4
};

#define ECT_SDO_SM_COMM_TYPE        (0x1c00)
#define ECT_SDO_PDO_ASSIGN          (0x1c10)  
#define ECT_SDO_RXPDO_ASSIGN        (0x1c12)  
#define ECT_SDO_TXPDO_ASSIGN        (0x1c13)


#define ETH_P_ECAT                  (0x88A4)

#define EC_DATAGRAM_FOLLOWS         (0x8000)

typedef enum
{
   EC_ERR_TYPE_SDO_ERROR        = 0,
   EC_ERR_TYPE_EMERGENCY        = 1,
   EC_ERR_TYPE_PACKET_ERROR     = 3,
   EC_ERR_TYPE_SDOINFO_ERROR    = 4,
   EC_ERR_TYPE_FOE_ERROR        = 5,
   EC_ERR_TYPE_FOE_BUF2SMALL    = 6,
   EC_ERR_TYPE_FOE_PACKETNUMBER = 7,
   EC_ERR_TYPE_SOE_ERROR        = 8,
   EC_ERR_TYPE_MBX_ERROR        = 9
} ec_err_type;


typedef uint8_t             boolean;

typedef struct
{
    uint32 sec;
    uint32 usec;
} EC_time_t;

typedef struct
{
   EC_time_t    Time;   
   boolean     Signal;
   uint16      Slave;
   uint16      Index;
   uint8       SubIdx;
   ec_err_type Etype;
   union
   {
      int32   AbortCode;
      struct
      {
         uint16  ErrorCode;
         uint8   ErrorReg;
         uint8   b1;
         uint16  w1;
         uint16  w2;
      };
   };
} EC_Error_t;

// Helper macros
#define HI_BYTE(w)         ((w)>>8)                                // Macro to get hi byte of a word    
#define LO_BYTE(w)         ((w)&0x00ff)                            // Macro to get low byte of a word  
#define SWAP(w)            ((((w)&0xff00)>>8) | (((w)&0x00ff)<<8)) // Macro to swap hi and low byte of a word
#define LO_WORD(l)         ((l) & 0xffff)                          // Macro to get hi word of a dword    
#define HI_WORD(l)         ((l) >> 16)                             // Macro to get hi word of a dword  

/*
#define get_unaligned(ptr) \
	({ __typeof__(*(ptr)) __tmp; memcpy(&__tmp, (ptr), sizeof(*(ptr))); __tmp; })
*/

#define put_unaligned32(val, ptr)        \
	(memcpy((ptr), &(val), 4))

#define put_unaligned64(val, ptr)        \
	(memcpy((ptr), &(val), 8))


// EC_LITTLE_ENDIAN
#define htoes(A) (A)
#define htoel(A) (A)
#define htoell(A) (A)
#define etohs(A) (A)
#define etohl(A) (A)
#define etohll(A) (A)

#endif /* _EC_TYPE_H */
