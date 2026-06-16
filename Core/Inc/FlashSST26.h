/**
  ******************************************************************************
  * @file           : FlashSST25.h
  * @brief          : Header for FlashSST26.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef FLASH_SST26_H
#define FLASH_SST26_H

#include "type.h"

#define SPIx	SPI2

/*
to do:
New: overflow if addressStart+lenData >= sizeflash return
New: return int errorCode for all functions
New: printErrorCode
Changed: writeData, readData accepts big array and chrashes

Tested circuits: SST26WF016B

Pining:

PIN 1 CE#   Chip Enable
PIN 2 SO    Serial Data Output To transfer data serially out of the device.
PIN 3 WP#   Write Protect The Write Protect (WP#) pin is used to enable/disable BPL bit in the status register.
PIN 4 VSS   Ground
PIN 5 SI    Serial Data Input  To transfer commands, addresses, or data serially into the device.
PIN 6 SCK   Serial Clock    To provide the timing of the serial interface.
PIN 7 HOLD# Hold To temporarily stop serial communication with SPI flash memory without resetting the device.
PIN 8 VDD   Power Supply

SPI Mode: 0 (0,0), 3 (1,1)

Read Speed: 40MHz
Read High Speed: 104MHz

Supply Voltage: 1.65V - 1.95V

Address: 0x000000 - 0x1FFFFF
4 KByte erasable sectors
*/

/* SST26 Registers *******************************************************************/
/* Indentification register values */
#ifndef CONFIG_SST26_MANUFACTURER
#define CONFIG_SST26_MANUFACTURER 0xBF
#endif

#ifndef CONFIG_SST26_MEMORY_TYPE
#define CONFIG_SST26_MEMORY_TYPE  0x26
#endif

#define SST26_MANUFACTURER         CONFIG_SST26_MANUFACTURER
#define SST26_MEMORY_TYPE          CONFIG_SST26_MEMORY_TYPE

#define SST26_SST26VF016_CAPACITY    0x41 /* 16 M-bit */
#define SST26_SST26VF032_CAPACITY    0x42 /* 32 M-bit */
#define SST26_SST26VF064_CAPACITY    0x43 /* 64 M-bit */

/* SST26VF016 capacity is 2,097,152 bytes:
 * (512 sectors) * (4,096 bytes per sector)
 * (8192 pages) * (256 bytes per page)
 */

#define SST26_SST26VF016_SECTOR_SHIFT  12    /* Sector size 1 << 15 = 65,536 */
#define SST26_SST26VF016_NSECTORS      512
#define SST26_SST26VF016_PAGE_SHIFT    8     /* Page size 1 << 8 = 256 */
#define SST26_SST26VF016_NPAGES        8192

 /* SST26VF032 capacity is 4,194,304 bytes:
  * (1,024 sectors) * (4,096 bytes per sector)
  * (16,384 pages) * (256 bytes per page)
  */

#define SST26_SST26VF032_SECTOR_SHIFT  12    /* Sector size 1 << 15 = 65,536 */
#define SST26_SST26VF032_NSECTORS      1024
#define SST26_SST26VF032_PAGE_SHIFT    8     /* Page size 1 << 8 = 256 */
#define SST26_SST26VF032_NPAGES        16384

  /* SST26VF064 capacity is 8,388,608 bytes:
   * (2,048 sectors) * (4,096 bytes per sector)
   * (32,768 pages) * (256 bytes per page)
   */

#define SST26_SST26VF064_SECTOR_SHIFT  12    /* Sector size 1 << 15 = 65,536 */
#define SST26_SST26VF064_NSECTORS      2048
#define SST26_SST26VF064_PAGE_SHIFT    8     /* Page size 1 << 8 = 256 */
#define SST26_SST26VF064_NPAGES        32768

   /* Instructions */
	/*      Command         Value      NN Description                  Addr Dummy  Data */
#define SST26_NOP       0x00    /* 14 No Operation                    0   0   0     */
#define SST26_RSTEN     0x66    /* 14 Reset Enable                    0   0   0     */
#define SST26_RST       0x99    /* 14 Reset Memory                    0   0   0     */
#define SST26_EQIO      0x38    /* 1  Enable Quad I/O                 0   0   0     */
#define SST26_RSTQIO    0xFF    /*  4 Reset Quad I/O                  0   0   0     */
#define SST26_RDSR      0x05    /* 1  Read Status Register            0   0   >=1   */
								/*  4 Read Status Register            0   1   >=1   */
#define SST26_WRSR      0x01    /* 14 Write Status Register           0   0   2     */
#define SST26_RDCR      0x35    /* 1  Read Config Register            0   0   >=1   */
								/*  4 Read Config Register            0   1   >=1   */

#define SST26_READ      0x03    /* 1  Read Data Bytes                 3   0   >=1   */
#define SST26_FAST_READ 0x0b    /* 1  Higher speed read               3   1   >=1   */
								/*  4 Higher speed read               3   3   >=1   */
#define SST26_SQOR      0x6b    /* 1  SQI Output Read                 3   1   >=1   */
#define SST26_SQIOR     0xeb    /* 1  SQI I/O Read                    3   3   >=1   */
#define SST26_SDOR      0x3b    /* 1  SDI Output Read                 3   1   >=1   */
#define SST26_SDIOR     0xbb    /* 1  SDI I/O Read                    3   1   >=1   */
#define SST26_SB        0xc0    /* 14 Set Burst Length                0   0   1     */
#define SST26_RBSQI     0x0c    /*  4 SQI Read Burst w/ Wrap          3   3   >=1   */
#define SST26_RBSPI     0xec    /* 1  SPI Read Burst w/ Wrap          3   3   >=1   */

#define SST26_RDID      0x9f    /* 1  Read Identification             0   0   >=3   */
#define SST26_QRDID     0xaf    /*  4 Quad Read Identification        0   1   >=3   */
#define SST26_SFDP      0x5a    /* 1  Serial Flash Discoverable Para  3   1   >=1   */

#define SST26_WREN      0x06    /* 14 Write Enable                    0   0   0     */
#define SST26_WRDI      0x04    /* 14 Write Disable                   0   0   0     */
#define SST26_SE        0x20    /* 14 Sector Erase                    3   0   0     */
#define SST26_BE        0xd8    /* 14 8/32/64K Block Erase            3   0   0     */
#define SST26_CE        0xc7    /* 14 Chip Erase                      0   0   0     */
#define SST26_PP        0x02    /* 1  Page Program                    3   0   1-256 */
#define SST26_QPP       0x32    /* 1  Quad Page Program               3   0   1-256 */
#define SST26_WRSU      0xb0    /* 14 Suspend Program/Erase           0   0   0     */
#define SST26_WRRE      0x30    /* 14 Resume Program/Erase            0   0   0     */

#define SST26_RBPR      0x72    /* 1  Read Block-Protection reg       0   0   1-18  */
								/*  4 Read Block-Protection reg       0   1   1-18  */
#define SST26_WBPR      0x42    /* 14 Write Block-Protection reg      0   0   1-18  */
#define SST26_LBPR      0x8d    /* 14 Lock down Block-Prot. reg       0   0   0     */
#define SST26_NVWLDR    0xe8    /* 14 non-Volatile Write L-D reg      0   0   1-18  */
#define SST26_ULBPR     0x98    /* 14 Global Block Protection unlock  0   0   0     */
#define SST26_RSID      0x88    /* 14 Read Security ID                2   1   1-2048*/
								/*  4 Read Security ID                2   3   1-2048*/
#define SST26_PSID      0xa5    /* 14 Program User Security ID area   2   0   1-256 */
#define SST26_LSID      0x85    /* 14 Lockout Security ID programming 0   0   0     */
/* Status register bit definitions */
#define SST26_SR_WIP              (1 << 0)                /* Bit 0: Write in progress */
#define SST26_SR_WEL              (1 << 1)                /* Bit 1: Write enable latch */
#define SST26_SR_WSE              (1 << 2)                /* Bit 2: Write Suspend-Erase Status */
#define SST26_SR_WSP              (1 << 3)                /* Bit 3: Write Suspend-Program Status */
#define SST26_SR_WPLD             (1 << 4)                /* Bit 4: Write Protection Lock-Down Status */
#define SST26_SR_SEC              (1 << 5)                /* Bit 5: Security ID status */
#define SST26_SR_RES              (1 << 6)                /* Bit 6: RFU */
#define SST26_SR_WIP2             (1 << 7)                /* Bit 7: Write in progress */
#define SST26_DUMMY               0xa5

//Size of buffer we are working on
enum SIZE_PAGE { SIZE_PAGE = 0x100 };

//Max numbers of retry when chip is busy
enum MAX_RETRY { MAX_RETRY = 10 };

//Durations in ms
enum DURATIONS
{
	//DURATION_1_MILLIS = 1,//Write page, write sec. id
	//DURATION_1_MILLIS = 3,//Write page, write sec. id
	DURATION_1_MILLIS = 6,//Write page, write sec. id
	DURATION_25_MILLIS = 25,//Erase sector, enable write protection
	DURATION_50_MILLIS = 50,//Erase all

	//TR(o) Reset to Read (non-data operation) 20 ns
	//TR(p) Reset Recovery from Program or Suspend 100 ��s
	//TR(e) Reset Recovery from Erase 1 ms
	//TPD   Power-down Duration 100 ms

	//TSE Sector-Erase 25 ms
	//TBE Block-Erase 25 ms
	//TSCE Chip-Erase 50 ms
	//TPP Page-Program 1.5 ms
	//TPSID Program Security-ID 1.5 ms
	//TWS Write-Suspend Latency 25 ��s
	//TWpen Write-Protection Enable Bit Latency 25 ms
};

/*type id_t*/
struct __attribute__((__packed__)) Tag_id_t
{
	INT32U jedecId;      /*0xBF2651*/
	INT08U manufacturerId;/*0xBF*/
	INT08U MemType;   /*0x26*/
	INT08U deviceId;     /*0x51*/
};
typedef struct Tag_id_t ID_t;

/*type uniqueId_t*/
struct __attribute__((__packed__)) Tag_uniqueId_t
{
	INT32U uniqueIdUpper;//upper 64 bit
	INT32U uniqueIdLower;//lower 64 bit
};
typedef struct Tag_uniqueId_t  uniqueId_t;

/*type registerStatus_t*/
struct __attribute__((__packed__)) Tag_registerStatus_t
{
	INT08U busy1 : 1; /*read only*/
	INT08U writeEnableLatch : 1; /*read only*/
	INT08U suspendErase : 1; /*read only*/
	INT08U suspendProgram : 1; /*read only*/
	INT08U writeProtection : 1; /*read only*/
	INT08U securityId : 1; /*read only*/
	INT08U reserved1 : 1; /*read only*/
	INT08U busy2 : 1; /*read only*/
};
typedef struct Tag_registerStatus_t  registerStatus_t;

/*type registerConfiguration_t*/
struct __attribute__((__packed__)) Tag_registerConfiguration_t
{
	INT08U reserved1 : 1;/*read only*/
	INT08U ioConfiguration : 1;/*R/W*/
	INT08U reserved2 : 1;/*read only*/
	INT08U blockProtectionVolatility : 1;/*read only*/ /*Default at power up 1*/
	INT08U reserved3 : 1;/*read only*/
	INT08U reserved4 : 1;/*read only*/
	INT08U reserved5 : 1;/*read only*/
	INT08U writeProtectionPin : 1;/*R/W non-volatile*/
};
typedef struct Tag_registerConfiguration_t  registerConfiguration_t;

//The default state after a power-on reset is write-protected BPR[47:0] = 5555 FFFF FFFF
struct __attribute__((__packed__)) Tag_registerBlockProtection_t
{
	INT08U adressRange0;/*8 bit 0x010000 - 0x08FFFF*/
	INT08U adressRange1;/*8 bit 0x090000 -*/
	INT08U adressRange2;/*8 bit*/
	INT08U adressRange3;/*8 bit*/
	INT08U adressRange4;/*8 bit*/
	INT08U adressRange5;/*8 bit*/
};
typedef struct Tag_registerBlockProtection_t  registerBlockProtection_t;

struct __attribute__((__packed__)) Tag_FlashSst26
{
	INT16U sectorshift;
	INT16U nsectors;
	INT16U pageshift;
	INT16U npages;

	//address we are working on
	INT32U _address;

	//ids
	ID_t                      _id;
	uniqueId_t                _uniqueId;

	//registers
	registerStatus_t          _registerStatus;
	registerConfiguration_t   _registerConfiguration;
	registerBlockProtection_t _registerBlockProtection;
};
typedef struct Tag_FlashSst26  FlashSst26;


//Enable write
void enableWrite(void);
//Disable write
void disableWrite(void);
//Read id
ID_t readId();
//Read unique id
uniqueId_t readUniqueId();
//Read register status
registerStatus_t readRegisterStatus();
//Read register configuration
registerConfiguration_t readRegisterConfiguration();
//Read register block protection
registerBlockProtection_t readRegisterBlockProtection();

//Write register configuration
INT08U writeRegisterConfiguration(registerConfiguration_t registerConfiguration);
//Write register block protection
INT08U writeRegisterBlockProtection(registerBlockProtection_t registerBlockProtection);
//Disable Global Block Protection
INT08U disableGlobalBlockProtection(void);

//Erase 4kBytes = 0x1000
INT08U erase4kByte(INT32U addressStart);
/*
	Sector 4kByte
	Address bits
	[AMS:A12] determine the sector address (SAX)
	(AMS = Most Significant Address)
	Blocks are 64 KByte, 32 KByte, or 8KByte, depending on location
	AMS - A13 for 8 KByte
	AMS - A15 for 32 KByte
	AMS - A16 for 64 KByte
	Remaining addresses are dont care, but must be set to VIL or VIH
*/
//Erase 8kBytes = 0x2000, 32kBytes = 0x8000, 64kBytes = 0xFFFF
INT08U eraseBlock(INT32U addressStart);

//Erase all
INT08U eraseAll(void);

//Write
// INT08U writeByte(INT32U addressStart, INT08U data[]);
// INT08U writePage(INT32U addressStart, INT08U page[]);
//Write data pagewise
INT08U writeData_Page(INT32U addressStart, INT08U data[], INT32U lenData);


//Read data
void readData(INT32U addressStart, INT08U data[], INT32U lenData);
void readPage(INT32U addressStart, INT08U page[]);
void readBytes(INT32U addressStart, INT08U bytes[], INT16U numBytes);

//Read data pagewise from flash and calculate its Crc32
INT32U readCrc32(INT32U address, INT32U lenData);

//Test if device is busy
INT08U isBusy(void);

INT32U calculateCrc32(INT08U data[], INT32U lenData, INT32U previousCrc32);

uint32_t sst26_write(uint32_t offset, uint16_t nbytes, const uint8_t* buffer);
unsigned int sst26_read(uint32_t offset, uint16_t nbytes, uint8_t* buffer);

extern int sst26_chiperase();
extern void sst_init();
extern void	init_FlashSst26(void);

#define TEST_PAGE_ADDRESS (0x1FF000)	// Last 4K Block Start Address. 2,093,056

// void Test_SFlash_Page_WriteRead();
// void Test_SFlash_Page_WriteRead_1();
// 
// void Test_SFlash_Page_Read();
// void Test_SFlash_Page_Erase();

void SFlash_Page_Read(INT32U nReadAddress);

#define EXT_MEMORY_BLOCK		(0x1000)		// 4KBytes(4096), 

#define EXT_MEMORY_4K		(0x1000)		// 4KBytes(4096),
#define EXT_MEMORY_8K		(0x2000)		// 8KBytes,
#define EXT_MEMORY_32K		(0x8000)		// 32KBytes,
#define EXT_MEMORY_64K		(0x10000)		// 64KBytes,

#define EXT_FLASH_MEMORY_ADDRESS_END	(0x200000)		// 2 MBbytes

// Parameter Use Memory : 272 KBytes, Not Use : 752 KBytes

#define EXT_PARAMETER_ADDR_START				(0x000000)		//
#define EXT_PARAMETER_ADDR_END					(0x100000)		// 1 MBbytes

#define EXT_DEVICE_SET_ADDR_START				(0)		// 4 KBytes
#define EXT_DEVICE_SET_ADDR_END					(EXT_DEVICE_SET_ADDR_START + EXT_MEMORY_BLOCK - 1)

#define EXT_RACK_ENV0_ADDR_START				(EXT_DEVICE_SET_ADDR_END + 1)	// 4 KBytes
#define EXT_RACK_ENV0_ADDR_END					(EXT_RACK_ENV0_ADDR_START + EXT_MEMORY_BLOCK - 1)	

#define EXT_RACK_ENV1_ADDR_START				(EXT_RACK_ENV0_ADDR_END + 1)	// 4 KBytes
#define EXT_RACK_ENV1_ADDR_END					(EXT_RACK_ENV1_ADDR_START + EXT_MEMORY_BLOCK - 1)

#define EXT_PARAMETER_SET_ADDR_START			(EXT_RACK_ENV1_ADDR_END + 1)	// 4 KBytes
#define EXT_PARAMETER_SET_ADDR_END				(EXT_PARAMETER_SET_ADDR_START + EXT_MEMORY_BLOCK - 1)

#define EXT_CELL_OFFSET_USEFLAG_ADDR_START		(EXT_PARAMETER_SET_ADDR_END + 1)	// 4 KBytes
#define EXT_CELL_OFFSET_USEFLAG_ADDR_END		(EXT_CELL_OFFSET_USEFLAG_ADDR_START + EXT_MEMORY_BLOCK - 1)

#define EXT_CELL_OFFSET_ADDR_START				(EXT_CELL_OFFSET_USEFLAG_ADDR_END + 1)	// 256 KBytes
#define EXT_CELL_OFFSET_ADDR_END				((EXT_CELL_OFFSET_ADDR_START + (EXT_MEMORY_BLOCK * 64)) - 1)	



//#define EXT_FW_PROGRAM_ADDR_START				(0x100000)		//
#define EXT_FW_PROGRAM_ADDR_START				(0x100000)		//
#define EXT_FW_PROGRAM_ADDR_END					(0x200000)		// 1 MBbytes

#define EXT_FW_BOOT_ADDR_START					(EXT_FW_PROGRAM_ADDR_START)			// 64 KBytes
#define EXT_FW_BOOT_ADDR_END					((EXT_FW_BOOT_ADDR_START + (EXT_MEMORY_BLOCK * 16)) - 1)

#define EXT_FW_APP_ADDR_START					(EXT_FW_BOOT_ADDR_END + 1)			// 960 KBytes
#define EXT_FW_APP_ADDR_END						((EXT_FW_APP_ADDR_START + (EXT_MEMORY_BLOCK * 240)) - 1)	

INT08U ExtFlash_WriteData(INT32U nAddress, INT08U* buff, INT32U size);
void ExtFlash_ReadData(INT32U nAddress, INT08U* buff, INT32U size);

INT08U ExtFlash_EraseData(INT32U nStartAddress, INT32U size);
//INT08U ExtFlash_WriteFW(INT32U nAddress, INT08U* buff, INT32U size);
//INT08U ExtFlash_WriteFW(INT32U nAddress, INT08U* buff, INT32U size, INT16U Crc);
INT08U ExtFlash_WriteFW(INT32U nAddress, INT08U* buff, INT32U size, INT16U* pCrc);
INT16U Calc_CRC_FlahsData(INT32U nAddress, INT32U nTotalSize);
#endif
