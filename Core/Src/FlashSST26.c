/**
  ******************************************************************************
  * @file            : FlashSST26.c
  * @author          :
  * @version         :
  * @brief           : This file implements External EEPROM
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

#include "main.h"
#include "type.h"
#include "User_Define.h"
#include "alarm.h"
#include "uart.h"
#include "FlashSST26.h"

FlashSst26 m_SFlash;

//#define SPI_TIMEOUT 10000
#define SPI_TIMEOUT 1000

#define SPI_SELECT(x) (x ? (HAL_GPIO_WritePin(SFlash_CE_GPIO_Port, SFlash_CE_Pin, GPIO_PIN_RESET)) : \
							 (HAL_GPIO_WritePin(SFlash_CE_GPIO_Port, SFlash_CE_Pin, GPIO_PIN_SET)))

void init_FlashSst26(void)
{
	HAL_GPIO_WritePin(SFlash_HOLD_GPIO_Port, SFlash_HOLD_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SFlash_WP_GPIO_Port, SFlash_WP_Pin, GPIO_PIN_SET);

	SPI_SELECT(0);
	
	m_SFlash.sectorshift = SST26_SST26VF016_SECTOR_SHIFT;
	m_SFlash.nsectors = SST26_SST26VF016_NSECTORS;
	m_SFlash.pageshift = SST26_SST26VF016_PAGE_SHIFT;
	m_SFlash.npages = SST26_SST26VF016_NPAGES;
}

INT08U SPI_SEND(INT08U cmd)
{
	INT16S nSpiTimeover = SPI_TIMEOUT;
	INT08U nRxData = 0;

	if ((SPIx->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
	{
		// If disabled, I enable it
		SET_BIT(SPIx->CR1, SPI_CR1_SPE);
	}
	
	//while (LL_I2S_IsActiveFlag_TXE(SPIx) == RESET)
	while (!(SPIx->SR & SPI_SR_TXE))
	{
		if ((--nSpiTimeover) <= 0)
		{
			asm volatile("NOP");
			break;
		}
	}
	LL_SPI_TransmitData8(SPIx, cmd);

	while (SPIx->SR & SPI_SR_BSY);

	nSpiTimeover = SPI_TIMEOUT;
	//while (LL_I2S_IsActiveFlag_RXNE(SPIx) == RESET)
	while (!(SPIx->SR & SPI_SR_RXNE))
	{
		if ((--nSpiTimeover) <= 0)
		{
 			asm volatile("NOP");
			break;
		}
	}

	nRxData = LL_SPI_ReceiveData8(SPIx);

	// Disable SPI
	CLEAR_BIT(SPIx->CR1, SPI_CR1_SPE);
	
	return nRxData;
}

INT08U SPI_SNDBLOCK(const INT08U* pWriteData, INT16U nLen)
{
	INT16U nIndex = 0;
	INT16S nSpiTimeover = SPI_TIMEOUT;
	INT08U nDummy = 0;

	if (nLen == 0)	return 0;

	if ((SPIx->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
	{
		// If disabled, I enable it
		SET_BIT(SPIx->CR1, SPI_CR1_SPE);
	}
	
	while (nLen)
	{
		nSpiTimeover = SPI_TIMEOUT;
		//while (LL_I2S_IsActiveFlag_TXE(SPIx) == RESET)
		while (!(SPIx->SR & SPI_SR_TXE))
		{
			if ((--nSpiTimeover) <= 0)
			{
				asm volatile("NOP");
				return 1;
			}
		}
		LL_SPI_TransmitData8(SPIx, pWriteData[nIndex]);	++nIndex;
		while (SPIx->SR & SPI_SR_BSY);
		
		nSpiTimeover = SPI_TIMEOUT;
		while (!(SPIx->SR & SPI_SR_RXNE))
		{
			if ((--nSpiTimeover) <= 0)
			{
				asm volatile("NOP");
				return 1;
			}
		}
		nDummy = LL_SPI_ReceiveData8(SPIx);

		--nLen;
	}

	// Disable SPI
	CLEAR_BIT(SPIx->CR1, SPI_CR1_SPE);

	return 0;
}

INT08U SPI_RECVBLOCK(INT08U* pReadData, INT16U nLen)
{
	INT16U nIndex = 0;
	INT16S nSpiTimeover = SPI_TIMEOUT;

	if (nLen == 0)	return 0;

	if ((SPIx->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
	{
		// If disabled, I enable it
		SET_BIT(SPIx->CR1, SPI_CR1_SPE);
	}

	while (nLen)
	{
		nSpiTimeover = SPI_TIMEOUT;
		while (!(SPIx->SR & SPI_SR_TXE))
		{
			if ((--nSpiTimeover) <= 0)
			{
				asm volatile("NOP");
				return 1;
			}
		}
		LL_SPI_TransmitData8(SPIx, SST26_DUMMY);
		while (SPIx->SR & SPI_SR_BSY);

		nSpiTimeover = SPI_TIMEOUT;
		while (!(SPIx->SR & SPI_SR_RXNE))
		{
			if ((--nSpiTimeover) <= 0)
			{
				asm volatile("NOP");
				return 1;
			}
		}

		pReadData[nIndex] = LL_SPI_ReceiveData8(SPIx); ++nIndex;
		--nLen;
	}

	// Disable SPI
	CLEAR_BIT(SPIx->CR1, SPI_CR1_SPE);

	return 0;
}

void disableWrite()
{
	SPI_SELECT(1);
	asm volatile("NOP");
	SPI_SEND(SST26_WRDI);
	asm volatile("NOP");
	SPI_SELECT(0);
}

void enableWrite()
{
	SPI_SELECT(1);
	asm volatile("NOP");
	SPI_SEND(SST26_WREN);
	asm volatile("NOP");
	SPI_SELECT(0);
}


ID_t readId()
{
	ID_t nReadID;
	INT08U nRead_Data[3];

	SPI_SELECT(1);
	SPI_SEND(SST26_RDID);
	SPI_RECVBLOCK(nRead_Data, sizeof(nRead_Data));
	
	nReadID.manufacturerId = nRead_Data[0];
	nReadID.MemType = nRead_Data[1];
	nReadID.deviceId = nRead_Data[2];
	SPI_SELECT(0);

	nReadID.jedecId = ((unsigned long)nReadID.manufacturerId << 16) 
		| (nReadID.MemType << 8) | nReadID.deviceId;

	if (nReadID.manufacturerId == SST26_MANUFACTURER && nReadID.MemType == SST26_MEMORY_TYPE)
	{
		if (nReadID.deviceId == SST26_SST26VF064_CAPACITY)
		{
			m_SFlash.sectorshift = SST26_SST26VF064_SECTOR_SHIFT;
			m_SFlash.nsectors = SST26_SST26VF064_NSECTORS;
			m_SFlash.pageshift = SST26_SST26VF064_PAGE_SHIFT;
			m_SFlash.npages = SST26_SST26VF064_NPAGES;
		}
		else if (nReadID.deviceId == SST26_SST26VF032_CAPACITY)
		{
			m_SFlash.sectorshift = SST26_SST26VF032_SECTOR_SHIFT;
			m_SFlash.nsectors = SST26_SST26VF032_NSECTORS;
			m_SFlash.pageshift = SST26_SST26VF032_PAGE_SHIFT;
			m_SFlash.npages = SST26_SST26VF032_NPAGES;
		}
		else if (nReadID.deviceId == SST26_SST26VF016_CAPACITY)
		{
			m_SFlash.sectorshift = SST26_SST26VF016_SECTOR_SHIFT;
			m_SFlash.nsectors = SST26_SST26VF016_NSECTORS;
			m_SFlash.pageshift = SST26_SST26VF016_PAGE_SHIFT;
			m_SFlash.npages = SST26_SST26VF016_NPAGES;
		}
	}

	return nReadID;
}



//************************************
// Method:    readUniqueId
// FullName:  readUniqueId
// Access:    public 
// Returns:   uniqueId_t
// Qualifier:
//************************************
uniqueId_t readUniqueId()
{
	uint8_t cmd[4];
	uint8_t data[8] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
	uniqueId_t nUniquedID;

	cmd[0] = SST26_RSID;
	cmd[1] = 0x00;//address
	cmd[2] = 0x00;//address
	cmd[3] = 0xff;//dummy

	SPI_SELECT(1);
	SPI_SNDBLOCK(cmd, sizeof(cmd));
	SPI_RECVBLOCK(data, sizeof(data));
	SPI_SELECT(0);

	nUniquedID.uniqueIdLower = (uint32_t) data[4] << 24
		| (uint32_t) data[5] << 16
		| (uint32_t) data[6] << 8
		| (uint32_t) data[7];

	nUniquedID.uniqueIdUpper = (uint32_t) data[0] << 24
		| (uint32_t) data[1] << 16
		| (uint32_t) data[2] << 8
		| (uint32_t) data[3];

	return nUniquedID;
}

//************************************
// Method:    readRegisterStatus
// FullName:  readRegisterStatus
// Access:    public 
// Returns:   registerStatus_t
// Qualifier:
//************************************
registerStatus_t readRegisterStatus()
{
	uint8_t cmd[1];
	uint8_t data[1] = { 0xff };
	registerStatus_t nRegisterStatus;

	cmd[0] = SST26_RDSR;

	SPI_SELECT(1);
	SPI_SNDBLOCK(cmd, sizeof(cmd));
	SPI_RECVBLOCK(data, sizeof(data));
	SPI_SELECT(0);

	nRegisterStatus.busy1 = data[0] & 1;
	nRegisterStatus.writeEnableLatch = data[0] >> 1 & 1;
	nRegisterStatus.suspendErase = data[0] >> 2 & 1;
	nRegisterStatus.suspendProgram = data[0] >> 3 & 1;
	nRegisterStatus.writeProtection = data[0] >> 4 & 1;
	nRegisterStatus.securityId = data[0] >> 5 & 1;
	nRegisterStatus.reserved1 = data[0] >> 6 & 1;
	nRegisterStatus.busy2 = data[0] >> 7 & 1;

	return nRegisterStatus;
}

//************************************
// Method:    readRegisterConfiguration
// FullName:  readRegisterConfiguration
// Access:    public 
// Returns:   registerConfiguration_t
// Qualifier:
//************************************
registerConfiguration_t readRegisterConfiguration()
{
	uint8_t cmd[1];
	uint8_t data[1] = { 0xff };
	registerConfiguration_t nRegisterConfiguration;

	cmd[0] = SST26_RDCR;

	SPI_SELECT(1);
	SPI_SNDBLOCK(cmd, sizeof(cmd));
	SPI_RECVBLOCK(data, sizeof(data));
	SPI_SELECT(0);

	nRegisterConfiguration.reserved1 = data[0] & 1;
	nRegisterConfiguration.ioConfiguration = data[0] >> 1 & 1;
	nRegisterConfiguration.reserved2 = data[0] >> 2 & 1;
	nRegisterConfiguration.blockProtectionVolatility = data[0] >> 3 & 1;
	nRegisterConfiguration.reserved3 = data[0] >> 4 & 1;
	nRegisterConfiguration.reserved4 = data[0] >> 5 & 1;
	nRegisterConfiguration.reserved5 = data[0] >> 6 & 1;
	nRegisterConfiguration.writeProtectionPin = data[0] >> 7 & 1;

	return nRegisterConfiguration;
}

//************************************
// Method:    writeRegisterConfiguration
// FullName:  writeRegisterConfiguration
// Access:    public 
// Returns:   INT08U
// Qualifier:
// Parameter: registerConfiguration_t registerConfiguration
//************************************
INT08U writeRegisterConfiguration(registerConfiguration_t registerConfiguration)
{
	uint8_t cmd[3] = { 0xff, 0xff, 0xff };

	cmd[0] = SST26_WRSR;

	cmd[1] = 0;
	/*
	  (unsigned char)_registerStatus.busy1 |
	  (unsigned char)_registerStatus.writeEnableLatch << 1 |
	  (unsigned char)_registerStatus.suspendErase << 2 |
	  (unsigned char)_registerStatus.suspendProgram << 3 |
	  (unsigned char)_registerStatus.writeProtection << 4 |
	  (unsigned char)_registerStatus.securityId << 5 |
	  (unsigned char)_registerStatus.reserved1 << 6 |
	  (unsigned char)_registerStatus.busy2 << 7;
	*/
	cmd[2] =
		(unsigned char)registerConfiguration.reserved1 |
		(unsigned char)registerConfiguration.ioConfiguration << 1 |
		(unsigned char)registerConfiguration.reserved2 << 2 |
		(unsigned char)registerConfiguration.blockProtectionVolatility << 3 |
		(unsigned char)registerConfiguration.reserved3 << 4 |
		(unsigned char)registerConfiguration.reserved4 << 5 |
		(unsigned char)registerConfiguration.reserved5 << 6 |
		(unsigned char)registerConfiguration.writeProtectionPin << 7;

	enableWrite();

	SPI_SELECT(1);
	SPI_SNDBLOCK(cmd, sizeof(cmd));
	SPI_SELECT(0);

	return 1;
}



//************************************
// Method:    writeRegisterBlockProtection
// FullName:  writeRegisterBlockProtection
// Access:    public 
// Returns:   INT08U
// Qualifier:
// Parameter: registerBlockProtection_t registerBlockProtection
//************************************
INT08U writeRegisterBlockProtection(registerBlockProtection_t registerBlockProtection)
{
	uint8_t data[7];

	data[0] = SST26_WBPR;
	data[1] = registerBlockProtection.adressRange0;
	data[2] = registerBlockProtection.adressRange1;
	data[3] = registerBlockProtection.adressRange2;
	data[4] = registerBlockProtection.adressRange3;
	data[5] = registerBlockProtection.adressRange4;
	data[6] = registerBlockProtection.adressRange5;
	
	enableWrite();
	
	SPI_SELECT(1);
	SPI_SNDBLOCK(data, sizeof(data));
	SPI_SELECT(0);

	return 1;
}

//************************************
// Method:    disableGlobalBlockProtection
// FullName:  disableGlobalBlockProtection
// Access:    public 
// Returns:   INT08U
// Qualifier:
// Parameter: void
//************************************
INT08U disableGlobalBlockProtection(void)
{
	uint8_t cmd[1];

	cmd[0] = SST26_ULBPR;

	enableWrite();

	SPI_SELECT(1);
	SPI_SNDBLOCK(cmd, sizeof(cmd));
	SPI_SELECT(0);

	return 1;
}


//************************************
// Method:    erase4kByte
// FullName:  erase4kByte
// Access:    public 
// Returns:   INT08U
// Qualifier:
// Parameter: INT32U addressStart
//************************************
INT08U erase4kByte(INT32U addressStart)
{
	//Address has to start at begin of sector
	if (addressStart % 0x1000 != 0) return 0;

	uint8_t cmd[4];

	cmd[0] = SST26_SE;
	cmd[1] = addressStart >> 16 & 0xFF;
	cmd[2] = addressStart >> 8 & 0xFF;
	cmd[3] = addressStart & 0xFF;

#if DEBUG_EXT_SFLASH_MSG
	printf("[EXT_SFLASH] erase4kByte. CMD: %x, Address: 0x%04lx\r\n", cmd[0], addressStart);
#endif

	enableWrite();

	SPI_SELECT(1);
	SPI_SNDBLOCK(cmd, sizeof(cmd));
	SPI_SELECT(0);

	//retry until device not busy anymore
	for (uint8_t retry = 0; retry < MAX_RETRY; retry++)
	{
		wait1ms(DURATION_25_MILLIS);
		if (!isBusy()) break;
		if (retry == MAX_RETRY)return 0;
	}
	return 1;
}

//************************************
// Method:    eraseBlock
// FullName:  eraseBlock
// Access:    public 
// Returns:   INT08U
// Qualifier:
// Parameter: INT32U addressStart
//************************************
INT08U eraseBlock(INT32U addressStart)
{
	//Address has to start at begin of Block
	if (addressStart % 0x2000 != 0) return 0;

	uint8_t cmd[4];

	cmd[0] = SST26_BE;
	cmd[1] = addressStart >> 16 & 0xFF;
	cmd[2] = addressStart >> 8 & 0xFF;
	cmd[3] = addressStart & 0xFF;

#if DEBUG_EXT_SFLASH_MSG
	printf("[EXT_SFLASH] eraseBlock. CMD: %x, Address: %lx\r\n", cmd[0], addressStart);
#endif

	enableWrite();

	SPI_SELECT(1);
	SPI_SNDBLOCK(cmd, sizeof(cmd));
	SPI_SELECT(0);

	//retry until device not busy anymore
	for (uint8_t retry = 0; retry < MAX_RETRY; retry++)
	{
		wait1ms(DURATION_25_MILLIS);
		if (!isBusy()) break;
		if (retry == MAX_RETRY)return 0;
	}
	return 1;
}

//************************************
// Method:    eraseBlock
// FullName:  eraseBlock
// Access:    public 
// Returns:   INT08U
// Qualifier:
// Parameter: INT32U addressStart
//************************************
INT08U eraseBlock_64K(INT32U addressStart)
{
	//Address has to start at begin of Block
	if (addressStart % 0x10000 != 0) return 0;

	uint8_t cmd[4];

	cmd[0] = SST26_BE;
	cmd[1] = addressStart >> 16 & 0xFF;
	cmd[2] = addressStart >> 8 & 0xFF;
	cmd[3] = addressStart & 0xFF;

#if DEBUG_EXT_SFLASH_MSG
	printf("[EXT_SFLASH] erase 64KB Block. CMD: %x, Address: %lx\r\n", cmd[0], addressStart);
#endif

	enableWrite();

	SPI_SELECT(1);
	SPI_SNDBLOCK(cmd, sizeof(cmd));
	SPI_SELECT(0);

	//retry until device not busy anymore
	for (uint8_t retry = 0; retry < MAX_RETRY; retry++)
	{
		wait1ms(DURATION_25_MILLIS);
		if (!isBusy()) break;
		if (retry == MAX_RETRY)return 0;
	}
	return 1;
}

//************************************
// Method:    eraseAll
// FullName:  eraseAll
// Access:    public 
// Returns:   INT08U
// Qualifier:
// Parameter: void
//************************************
INT08U eraseAll(void)
{
	uint8_t cmd[1];

	cmd[0] = SST26_CE;

#if DEBUG_EXT_SFLASH_MSG
		printf("[EXT_SFLASH] eraseAll. CMD: %x\r\n", cmd[0]);
#endif

	enableWrite();

	SPI_SELECT(1);
	SPI_SNDBLOCK(cmd, sizeof(cmd));
	SPI_SELECT(0);

	//retry until device not busy anymore
	for (uint8_t retry = 0; retry < MAX_RETRY; retry++)
	{
		wait1ms(DURATION_50_MILLIS);
		if (!isBusy()) break;
		if (retry == MAX_RETRY) return 0;
	}
	return 1;
}

//************************************
// Method:    writeByte
// FullName:  writeByte
// Access:    public 
// Returns:   INT08U
// Qualifier:
// Parameter: INT32U addressStart
// Parameter: INT08U data[]
//************************************
INT08U writeByte(INT32U addressStart, INT08U data[])
{
	//Adress has to start at begin of page
	if (addressStart % SIZE_PAGE != 0) return 0;

	uint8_t cmd[5];

	cmd[0] = SST26_PP;
	cmd[1] = addressStart >> 16 & 0xFF;
	cmd[2] = addressStart >> 8 & 0xFF;
	cmd[3] = addressStart & 0xFF;
	cmd[4] = data[0];

	enableWrite();

	SPI_SELECT(1);
	SPI_SNDBLOCK(cmd, sizeof(cmd));
	SPI_SELECT(0);

	//retry until device not busy anymore
	for (uint8_t retry = 0; retry < MAX_RETRY; retry++)
	{
		if (!isBusy()) break;
		if (retry == MAX_RETRY)return 0;
	}
	return 1;
}

//************************************
// Method:    writePage
// FullName:  writePage
// Access:    public 
// Returns:   INT08U
// Qualifier:
// Parameter: INT32U addressStart
// Parameter: INT08U page[]
//************************************
INT08U writePage(INT32U addressStart, INT08U page[])
{
	//Address has to start at begin of page
	if (addressStart % SIZE_PAGE != 0) return 0;

	uint8_t cmd[4];

	cmd[0] = SST26_PP;
	cmd[1] = addressStart >> 16 & 0xFF;
	cmd[2] = addressStart >> 8 & 0xFF;
	cmd[3] = addressStart & 0xFF;

	enableWrite();

	SPI_SELECT(1);
	SPI_SNDBLOCK(cmd, sizeof(cmd));
	SPI_SNDBLOCK(page, SIZE_PAGE);
	SPI_SELECT(0);

	//retry until device not busy anymore
	for (uint8_t retry = 0; retry < MAX_RETRY; retry++)
	{
		wait1ms(DURATION_1_MILLIS);
		if (!isBusy()) break;
		if (retry == MAX_RETRY)return 0;
	}
	return 1;
}

//************************************
// Method:    writeData
// FullName:  writeData
// Access:    public 
// Returns:   INT08U
// Qualifier:
// Parameter: INT32U addressStart
// Parameter: INT08U data[]
// Parameter: INT32U len
//************************************
INT08U writeData_Page(INT32U addressStart, INT08U data[], INT32U len)
{
	//Address has to start at begin of page
	if ((addressStart % SIZE_PAGE) != 0)
	{
#if DEBUG_EXT_SFLASH_MSG
		printf("[EXT_SFLASH] Address has to start at begin of page AddressStart: 0x%04lx\r\n", \
			addressStart);
#endif
		return 0;
	}

	//position in data[]
	uint32_t position = 0;
	//number of buffers written
	uint16_t numBuffer = 0;

	//cycle trough array data[]
	while (position < len)
	{
		//create local buffer
		uint8_t buffer[SIZE_PAGE];
		//initalize local buffer with 0xff
		//for (uint16_t i = 0; i < SIZE_PAGE; i++) buffer[i] = 0xff;
		memset(buffer, 0xFF, sizeof(buffer));

		//fill buffer
		for (uint16_t j = 0; j < SIZE_PAGE; j++)
		{
			//copy data in buffer
			buffer[j] = data[position];
			//next position in data[]
			position++;

			//end of data[] reached before buffer[] full
			if (position >= len)break;
		}
		//buffer full ..write page at right address...if not full write 0xff
		writePage(addressStart + numBuffer * SIZE_PAGE, buffer);

		//count buffers written for next page address
		numBuffer++;
	}

	return 1;
}

//************************************
// Method:    readData
// FullName:  readData
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: INT32U addressStart
// Parameter: INT08U data[]
// Parameter: INT32U lenData
//************************************
void readData(INT32U addressStart, INT08U data[], INT32U lenData)
{
	//analyze lenData
	//nothing to read
	if (lenData == 0)
	{
		return;
	}

	//overflow: if addressStart+lenData >= sizeflash return
	uint8_t cmd[4];

	cmd[0] = SST26_READ;
	cmd[1] = addressStart >> 16 & 0xFF;
	cmd[2] = addressStart >> 8 & 0xFF;
	cmd[3] = addressStart & 0xFF;

	SPI_SELECT(1);
	SPI_SNDBLOCK(cmd, sizeof(cmd));
	SPI_RECVBLOCK(data, lenData);
	SPI_SELECT(0);

	//retry until device not busy anymore
	for (uint8_t retry = 0; retry < MAX_RETRY; retry++)
	{
		if (!isBusy()) break;
		if (retry == MAX_RETRY) return;
	}
}

//************************************
// Method:    readPage
// FullName:  readPage
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: INT32U addressStart
// Parameter: INT08U page[]
//************************************
void readPage(INT32U addressStart, INT08U page[])
{
	uint8_t cmd[4];

	cmd[0] = SST26_READ;
	cmd[1] = addressStart >> 16 & 0xFF;
	cmd[2] = addressStart >> 8 & 0xFF;
	cmd[3] = addressStart & 0xFF;

	SPI_SELECT(1);
	SPI_SNDBLOCK(cmd, sizeof(cmd));
	SPI_RECVBLOCK(page, SIZE_PAGE);
	SPI_SELECT(0);

	//retry until device not busy anymore
	for (uint8_t retry = 0; retry < MAX_RETRY; retry++)
	{
		if (!isBusy()) break;
		if (retry == MAX_RETRY)return;
	}
}

//************************************
// Method:    readBytes
// FullName:  readBytes
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: INT32U addressStart
// Parameter: INT08U bytes[]
// Parameter: INT16U numBytes
//************************************
void readBytes(INT32U addressStart, INT08U bytes[], INT16U numBytes)
{
	//nothing to read
	if (numBytes == 0) return;

	//initialize
	for (uint16_t i = 0; i < numBytes; i++) 
		bytes[i] =  0xff;

	uint8_t cmd[4];

	cmd[0] = SST26_READ;
	cmd[1] = addressStart >> 16 & 0xFF;
	cmd[2] = addressStart >> 8 & 0xFF;
	cmd[3] = addressStart & 0xFF;

	SPI_SELECT(1);
	SPI_SNDBLOCK(cmd, sizeof(cmd));
	SPI_RECVBLOCK(bytes, numBytes);
	SPI_SELECT(0);

	//retry until device not busy anymore
	for (uint8_t retry = 0; retry < MAX_RETRY; retry++)
	{
		if (!isBusy()) break;
		if (retry == MAX_RETRY) return;
	}
}

//************************************
// Method:    readCrc32
// FullName:  readCrc32
// Access:    public 
// Returns:   INT32U
// Qualifier:
// Parameter: INT32U address
// Parameter: INT32U lenData
//************************************
INT32U readCrc32(INT32U address, INT32U lenData)
{
	//CRC32 value
	uint32_t crc32 = 0;
	//data buffer
	uint8_t buffer[0x100];
	//number of pages to check
	uint32_t numPages = 0;
	//calculate rest
	uint16_t modulo = lenData % 0x100;
	//subtract the rest
	numPages = (lenData - modulo) / 0x100;

	for (uint32_t page = 0; page < numPages; page++)
	{
		//initalize buffer with 0xff
		for (uint16_t i = 0; i < 0x100; i++) buffer[i] = 0xff;
		//read a page of data
		readData(address + page * 0x100, buffer, 0x100);
		//calculate crc32
		crc32 = calculateCrc32(buffer, 0x100, crc32);
	}

	//is there a modulo ?
	if (modulo)
	{
		//initalize buffer with 0xff
		for (uint16_t i = 0; i < 0x100; i++) buffer[i] = 0xff;
		//read modulo
		readData(address + numPages * 0x100, buffer, modulo);
		//calculate crc32
		crc32 = calculateCrc32(buffer, modulo, crc32);
	}
	return crc32;
}

//************************************
// Method:    reset
// FullName:  reset
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void reset(void)
{

}

//************************************
// Method:    isBusy
// FullName:  isBusy
// Access:    public 
// Returns:   INT08U
// Qualifier:
// Parameter: void
//************************************
INT08U isBusy(void)
{
	INT08U nResult = 0;

	m_SFlash._registerStatus = readRegisterStatus();

	(m_SFlash._registerStatus.busy1) ? (nResult = 1) : (nResult = 0);
	
	return nResult;
}

//************************************
// Method:    calculateCrc32
// FullName:  calculateCrc32
// Access:    public 
// Returns:   INT32U
// Qualifier:
// Parameter: INT08U data[]
// Parameter: INT32U lenData
// Parameter: INT32U previousCrc32
//************************************
INT32U calculateCrc32(INT08U data[], INT32U lenData, INT32U previousCrc32)
{
	const uint32_t polynomial = 0xEDB88320;
	uint32_t crc = ~previousCrc32;
	uint8_t* current = data;

	while (lenData--)
	{
		crc ^= *current++;
		//all bits
		for (uint8_t j = 0; j < 8; j++)
		{
			//last bit is 1
			if (crc & 1)
				//shift and ^
				crc = (crc >> 1) ^ polynomial;
			//last bit is 0
			else
				//shift
				crc = crc >> 1;
		}
	}
	return ~crc;
}

//************************************
// Method:    readRegisterBlockProtection
// FullName:  readRegisterBlockProtection
// Access:    public 
// Returns:   registerBlockProtection_t
// Qualifier:
//************************************
registerBlockProtection_t readRegisterBlockProtection()
{
	uint8_t cmd[1];
	uint8_t data[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

	registerBlockProtection_t nRegisterBlockProtection;

	cmd[0] = SST26_RBPR;

	SPI_SELECT(1);
	SPI_SNDBLOCK(cmd, sizeof(cmd));
	SPI_RECVBLOCK(data, sizeof(data));
	SPI_SELECT(0);

	nRegisterBlockProtection.adressRange0 = data[0];
	nRegisterBlockProtection.adressRange1 = data[1];
	nRegisterBlockProtection.adressRange2 = data[2];
	nRegisterBlockProtection.adressRange3 = data[3];
	nRegisterBlockProtection.adressRange4 = data[4];
	nRegisterBlockProtection.adressRange5 = data[5];

	return nRegisterBlockProtection;
}

unsigned int sst26_read(uint32_t offset, uint16_t nbytes, uint8_t* buffer)
{
	SPI_SELECT(1);
	SPI_SEND(SST26_FAST_READ);
	SPI_SEND((offset >> 16) & 0xff);
	SPI_SEND((offset >> 8) & 0xff);
	SPI_SEND(offset & 0xff);
	SPI_SEND(SST26_DUMMY);
	SPI_RECVBLOCK(buffer, nbytes);
	SPI_SELECT(0);

	return nbytes;
}

void sst26_globalunlock()
{
	SPI_SELECT(1);
	SPI_SEND(SST26_ULBPR);
	SPI_SELECT(0);
}

void sst26_waitwritecomplete()
{
	int errCount = 255;
	uint8_t status;
	do
	{
		SPI_SELECT(1);
		SPI_SEND(SST26_RDSR);
		status = SPI_SEND(SST26_DUMMY);
		SPI_SELECT(0);
		if ((status & SST26_SR_WIP) != 0)
		{
			wait1ms(DURATION_1_MILLIS);
		}
		errCount--;
		if (errCount < 0)
			break;
	} while ((status & SST26_SR_WIP) != 0);
}

static inline void sst26_bytewrite(const uint8_t* buffer, uint32_t offset, uint16_t count)
{
	enableWrite();
	SPI_SELECT(1);
	SPI_SEND(SST26_PP);
	SPI_SEND((offset >> 16) & 0xff);
	SPI_SEND((offset >> 8) & 0xff);
	SPI_SEND(offset & 0xff);
	SPI_SNDBLOCK(buffer, count);
	SPI_SELECT(0);
	sst26_waitwritecomplete();
}


uint32_t sst26_write(uint32_t offset, uint16_t nbytes, const uint8_t* buffer)
{
	int    startpage;
	int    endpage;
	int    count;
	int    index;
	int    pagesize;
	int    bytestowrite;

	startpage = offset / (1 << m_SFlash.pageshift);
	endpage = (offset + nbytes) / (1 << m_SFlash.pageshift);
	
	//printf("\n %d - %d \n", startpage, endpage);

	if (startpage == endpage)
	{
		sst26_bytewrite(buffer, offset, nbytes);
	}
	else
	{
		count = nbytes;
		pagesize = (1 << m_SFlash.pageshift);
		bytestowrite = pagesize - (offset & (pagesize - 1));
		sst26_bytewrite(buffer, offset, bytestowrite);
		offset += bytestowrite;
		count -= bytestowrite;
		index = bytestowrite;
		while (count >= pagesize)
		{
			sst26_bytewrite(&buffer[index], offset, pagesize);
			offset += pagesize;
			count -= pagesize;
			index += pagesize;
		}
		if (count > 0)
		{
			sst26_bytewrite(&buffer[index], offset, count);
		}
	}
	return nbytes;
}


static void sst26_sectorerase(uint16_t sector, uint8_t type)
{
	uint32_t offset;

	offset = sector << m_SFlash.sectorshift;
	enableWrite();
	SPI_SELECT(1);
	SPI_SEND(type);
	SPI_SEND((offset >> 16) & 0xff);
	SPI_SEND((offset >> 8) & 0xff);
	SPI_SEND(offset & 0xff);
	SPI_SELECT(0);
	sst26_waitwritecomplete();
}


int sst26_erase(uint16_t startblock, uint16_t nblocks)
{
#if DEBUG_EXT_SFLASH_MSG
	printf("[EXT_SFLASH] erese chip.\r\n");
#endif

	uint16_t blocksleft = nblocks;
	while (blocksleft > 0)
	{
		sst26_sectorerase(startblock, SST26_SE);
		startblock++;
		blocksleft--;
	}
	return (int)nblocks;
}

int sst26_chiperase()
{
#if DEBUG_EXT_SFLASH_MSG
	printf("[EXT_SFLASH] chip erase.\r\n");
#endif

	enableWrite();

	SPI_SELECT(1);
	SPI_SEND(SST26_CE);
	SPI_SELECT(0);

	sst26_waitwritecomplete();
	return 0;
}

void sst_init()
{
	m_SFlash._id = readId();

#if DEBUG_EXT_SFLASH_MSG
	printf("[EXT_SFLASH] manufacturerId: 0x%x MemType: 0x%x deviceId: 0x%x\r\n", \
		m_SFlash._id.manufacturerId, m_SFlash._id.MemType, m_SFlash._id.deviceId);
#endif

	if ((m_SFlash._id.manufacturerId == SST26_MANUFACTURER) && 
		(m_SFlash._id.MemType == SST26_MEMORY_TYPE))
	{

		m_pgmEnv.SFlash_Install = 1;

#if DEBUG_EXT_SFLASH_MSG
		printf("[EXT_SFLASH] Checked SST26VF SFlash. SFlash_Install: %d\r\n", m_pgmEnv.SFlash_Install);
#endif

		m_SFlash._uniqueId = readUniqueId();
		m_SFlash._registerStatus = readRegisterStatus();
		m_SFlash._registerConfiguration = readRegisterConfiguration();
		m_SFlash._registerBlockProtection = readRegisterBlockProtection();

		enableWrite();
		sst26_globalunlock();
		disableWrite();
	}
	else
	{
		m_pgmEnv.SFlash_Install = 0;
	}
}

/*
void Test_SFlash_Page_WriteRead()
{
	INT32U nProcessTime = 0;

	INT16U i = 0;
	INT08U nResult = 0;
	INT08U nWriteBuffer[SIZE_PAGE] = { 0, };
	INT08U nReadBuffer[SIZE_PAGE] = { 0, };

	asm volatile ("NOP");

	for (i = 0; i <= 0xFF; i++)
	{
		nWriteBuffer[i] = i;
	}
	asm volatile ("NOP");

	nProcessTime = m_pgmEnv.timer100us;
	nResult = writeData_Page(TEST_PAGE_ADDRESS, nWriteBuffer, SIZE_PAGE);

	if (nResult)
	{
#if DEBUG_EXT_SFLASH_MSG
		printf("[EXT_SFLASH] Write Page No: %d, Size: %d ProcessTime: %ld00us\r\n", \
			TEST_PAGE_ADDRESS, SIZE_PAGE, getCalcTimer100us(nProcessTime));

		wait1ms(5);
		sst26_read(TEST_PAGE_ADDRESS, SIZE_PAGE, nReadBuffer);

		for (i = 0; i < 0xFF; i++)
		{
			if ((i % 20) == 0) printf("\r\n");
			printf(" %02x", nReadBuffer[i]);
		}
		printf("\r\n");
#endif
	}
	else
	{
#if DEBUG_EXT_SFLASH_MSG
		printf("[EXT_SFLASH] Test Write Fail.\r\n");
#endif
	}

	asm volatile ("NOP");
}
*/

/*
void Test_SFlash_Page_WriteRead_1()
{
	INT32U nProcessTime = 0;

	INT16U i = 0;
	INT08U nResult = 0;
	INT08U nWriteBuffer[SIZE_PAGE] = { 0, };
	INT08U nReadBuffer[SIZE_PAGE] = { 0, };

	for (i = 0; i <= 0xFF; i++)
	{
		nWriteBuffer[i] = 0xFF - i;
	}

	nProcessTime = m_pgmEnv.timer100us;
	nResult = writeData_Page(TEST_PAGE_ADDRESS, nWriteBuffer, SIZE_PAGE);

	if (nResult)
	{
		wait1ms(5);
		sst26_read(TEST_PAGE_ADDRESS, SIZE_PAGE, nReadBuffer);

#if DEBUG_EXT_SFLASH_MSG
		printf("\r\n");
		printf("[EXT_SFLASH] Write Page No: %d, Size: %d ProcessTime: %ld00us\r\n", \
			TEST_PAGE_ADDRESS, SIZE_PAGE, getCalcTimer100us(nProcessTime));

		for (i = 0; i < SIZE_PAGE; i++)
		{
			if ((i % 20) == 0) printf("\r\n");
			printf(" %02x", nReadBuffer[i]);
		}
		printf("\r\n");
#endif
		
	}
	else
	{
#if DEBUG_EXT_SFLASH_MSG
		printf("[EXT_SFLASH] Test Write Fail.\r\n");
#endif
	}

	asm volatile ("NOP");
}
*/

/*
void Test_SFlash_Page_Read()
{
	INT32U nProcessTime = 0;

	INT16U i = 0;
	INT08U nReadBuffer[SIZE_PAGE] = { 0, };

	nProcessTime = m_pgmEnv.timer100us;
	
	sst26_read(TEST_PAGE_ADDRESS, SIZE_PAGE, nReadBuffer);
	
	printf("\r\n");
	printf("[EXT_SFLASH] Read Address: 0x%06x, Size: %d Process Time: %ld00us\r\n", \
		TEST_PAGE_ADDRESS, SIZE_PAGE, getCalcTimer100us(nProcessTime));

	for (i = 0; i < SIZE_PAGE; i++)
	{
		if ((i % 20) == 0) printf("\r\n");

		printf(" %02x", nReadBuffer[i]);
	}
	printf("\r\n");
	
	asm volatile ("NOP");
}
*/

/*
void Test_SFlash_Page_Erase()
{
	INT32U nProcessTime = 0;

	nProcessTime = m_pgmEnv.timer1ms;

	erase4kByte(TEST_PAGE_ADDRESS);

	printf("[EXT_SFLASH] Erase page. Process Time: %ldms\r\n", getCalcTimer1ms(nProcessTime));

	asm volatile ("NOP");
}
*/

void SFlash_Page_Read(INT32U nReadAddress)
{
	INT32U nProcessTime = 0;

	INT16U i = 0;
	INT08U nReadBuffer[SIZE_PAGE] = { 0, };

	nProcessTime = m_pgmEnv.timer100us;

	if (nReadAddress > TEST_PAGE_ADDRESS) return;

	sst26_read(nReadAddress, SIZE_PAGE, nReadBuffer);

	printf("\r\n");
	printf("[EXT_SFLASH] Read Address: 0x%06lx, Size: %d Process Time: %ld00us\r\n", \
		nReadAddress, SIZE_PAGE, getCalcTimer100us(nProcessTime));

	for (i = 0; i < SIZE_PAGE; i++)
	{
		if ((i % 20) == 0) printf("\r\n");
		printf(" %02x", nReadBuffer[i]);
	}
	printf("\r\n");

	asm volatile ("NOP");
}

/**
  * @brief Write to External Flash data
  * @param nAddress
  * @param buff
  * @param size
  * @retval write success, fail
  */
INT08U ExtFlash_WriteData(INT32U nAddress, INT08U* buff, INT32U size)
{
	INT08U i = 0;

	INT08U nResult = 0;
	INT08U nErase4K_Cnt = 0;

	INT32U addr_now = nAddress;
	INT32U addr_end = addr_now + size;
	INT08U* dataPtr = (INT08U*)buff;

	INT08U nReadBuffer[SIZE_PAGE] = { 0, };

	nErase4K_Cnt = size / EXT_MEMORY_BLOCK;

#if DEBUG_EXT_SFLASH_MSG
	INT32U nProcessTime = 0;
	printf("[EXT_SFLASH] Erase4K Cnt: %d\r\n", nErase4K_Cnt);
	nProcessTime = m_pgmEnv.timer1ms;
#endif
	if (nErase4K_Cnt == 0)
	{
		return 0;
	}

	for (i = 0; i < nErase4K_Cnt; i++)
	{
		erase4kByte(nAddress + (i * EXT_MEMORY_BLOCK));
		//wait1ms(DURATION_25_MILLIS);
		wait1ms(DURATION_1_MILLIS);
	}
	
#if DEBUG_EXT_SFLASH_MSG
	printf("[EXT_SFLASH] Start Write addr_now: 0x%04lx addr_end: 0x%04lx Size: %ld \r\n", \
		addr_now, addr_end, size);
#endif
	while ((addr_now < addr_end))
	{
		nResult = writeData_Page(addr_now, dataPtr, SIZE_PAGE);

		if (nResult)
		{
			wait1ms(DURATION_1_MILLIS);
			sst26_read(addr_now, SIZE_PAGE, nReadBuffer);

			if (memcmp(dataPtr, nReadBuffer, SIZE_PAGE))
			{
#if DEBUG_EXT_SFLASH_MSG
				printf("[EXT_SFLASH] Write/Read not equal. addr_now: 0x%04lx addr_end: 0x%04lx\r\n", \
					addr_now, addr_end);
#endif
				nResult = 0;
				break;
			}
			else
			{
				addr_now += SIZE_PAGE;
				dataPtr += SIZE_PAGE;

#if ENABLE_WATCHDOG
				WatchDog();
#endif
			}
		}
		else
		{
#if DEBUG_EXT_SFLASH_MSG
			printf("[EXT_SFLASH] Write Fail. Check size. \r\n");
#endif
			nResult = 0;
			break;
		}
	}

#if DEBUG_EXT_SFLASH_MSG
	if (nResult)
	{
		printf("[EXT_SFLASH] Complete Write Address: 0x%lx Size: %ld Time: %ldms\r\n", \
			nAddress, size, getCalcTimer1ms(nProcessTime));
	}
#endif

	return nResult;
}

/**
  * @brief Read from External Flash data
  * @param nAddress
  * @param buff
  * @param size
  * @retval
  */
void ExtFlash_ReadData(INT32U nAddress, INT08U* buff, INT32U size)
{
	INT32U addr_now = nAddress;
	INT32U addr_end = addr_now + size;

#if DEBUG_EXT_SFLASH_MSG
	INT32U nProcessTime = 0;
	nProcessTime = m_pgmEnv.timer1ms;

	printf("[EXT_SFLASH] Start Read addr_now: 0x%lx addr_end: 0x%lx \r\n", addr_now, addr_end);
#endif
	while ((addr_now < addr_end))
	{		
		sst26_read(addr_now, SIZE_PAGE, buff);

		addr_now += SIZE_PAGE;
		buff += SIZE_PAGE;

#if ENABLE_WATCHDOG
		WatchDog();
#endif
	}

#if DEBUG_EXT_SFLASH_MSG
	printf("[EXT_SFLASH] Read Address: 0x%lx Size: %ld Time: %ldms\r\n", \
		nAddress, size, getCalcTimer1ms(nProcessTime));
#endif
}

/**
  * @brief Write to External Flash data
  * @param nAddress
  * @param size
  * @retval write success, fail
  */
INT08U ExtFlash_EraseData(INT32U nStartAddress, INT32U size)
{
	INT08U i = 0;
	INT08U nErase_Cnt = 0;
	INT08U nResult = 1;
	//INT32U addr_now = nStartAddress;


	//nErase_Cnt = size / EXT_MEMORY_64K;
	if (size > EXT_MEMORY_64K)
	{
		nErase_Cnt = size / EXT_MEMORY_64K;
	}
	else
	{
		nErase_Cnt = 1;
	}

#if DEBUG_EXT_SFLASH_MSG
	INT32U nProcessTime = 0;
	printf("[EXT_SFLASH] Erase Cnt: %d\r\n", nErase_Cnt);
	nProcessTime = m_pgmEnv.timer1ms;
#endif
	if (nErase_Cnt == 0)
	{
		nResult = 0;
	}

	if (nResult)
	{
		for (i = 0; i < nErase_Cnt; i++)
		{
			nResult = eraseBlock_64K(nStartAddress + (i * EXT_MEMORY_64K));
			wait1ms(DURATION_25_MILLIS);
			//wait1ms(DURATION_1_MILLIS);
			//wait1ms(10);

			if (nResult == 0)
			{
				break;
			}
		}
	}


#if DEBUG_EXT_SFLASH_MSG
	if (nResult)
	{
		printf("[EXT_SFLASH] Success erase Address: 0x%lx Size: %ld Time: %ldms\r\n", \
			nStartAddress, size, getCalcTimer1ms(nProcessTime));
	}
	else
	{
		printf("[EXT_SFLASH] Fail erase Address: 0x%lx Size: %ld Time: %ldms\r\n", \
			nStartAddress, size, getCalcTimer1ms(nProcessTime));
	}
#endif

	return nResult;
}

/**
  * @brief Write to External Flash data
  * @param nAddress
  * @param buff
  * @param size
  * @retval write success, fail
  */
INT08U ExtFlash_WriteFW(INT32U nAddress, INT08U* buff, INT32U size, INT16U* pCrc)
{
	INT08U nResult = 0;

	INT32U addr_now = nAddress;
	INT32U addr_end = addr_now + size;
	INT08U* dataPtr = (INT08U*)buff;

	INT32U nProcessSize = 0;
	INT32U nWriteSize = 0;

	INT08U nReadBuffer[SIZE_PAGE] = { 0, };

#if DEBUG_UPGRADE_MSG
	INT32U nProcessTime = 0;

	nProcessTime = m_pgmEnv.timer1ms;

	printf("[EXT_SFLASH] Start Write addr_now: 0x%04lx addr_end: 0x%04lx Size: %ld \r\n", \
		addr_now, addr_end, size);
#endif
	while ((addr_now < addr_end))
	{
		nProcessSize = addr_now + SIZE_PAGE;
		if (nProcessSize > addr_end)
		{
			nWriteSize = addr_end - addr_now;
		}
		else
		{
			nWriteSize = SIZE_PAGE;
		}

#if DEBUG_EXT_SFLASH_MSG
		/*
		printf("[EXT_SFLASH] Write addr_now: 0x%04lx addr_end: 0x%04lx Size: %ld\r\n", \
			addr_now, addr_end, nWriteSize);
		*/
#endif
		nResult = writeData_Page(addr_now, dataPtr, nWriteSize);
		if (nResult)
		{
			wait1ms(DURATION_1_MILLIS);
			sst26_read(addr_now, nWriteSize, nReadBuffer);

			if (memcmp(dataPtr, nReadBuffer, nWriteSize))
			{
#if DEBUG_UPGRADE_MSG
				printf("[EXT_SFLASH] Write/Read not equal. addr_now: 0x%04lx addr_end: 0x%04lx\r\n", \
					addr_now, addr_end);
#endif
				nResult = 0;
				break;
			}
			else
			{
				addr_now += nWriteSize;
				dataPtr += nWriteSize;

				*pCrc = crcInitStrCalc(*pCrc, nReadBuffer, nWriteSize);

#if ENABLE_WATCHDOG
				WatchDog();
#endif
			}
		}
		else
		{
#if DEBUG_UPGRADE_MSG
			printf("[EXT_SFLASH] FW Write Fail. Check size. \r\n");
#endif
			nResult = 0;
			break;
		}
	}

#if DEBUG_UPGRADE_MSG
	if (nResult)
	{
		printf("[EXT_SFLASH] FW Write Address: 0x%lx Size: %ld Time: %ldms\r\n", \
			nAddress, size, getCalcTimer1ms(nProcessTime));
	}
#endif

	return nResult;
}

/**
  * @brief	Calc_CRC_FlahsData
  * @param
  * @param
  * @retval void
  */
INT16U Calc_CRC_FlahsData(INT32U nAddress, INT32U nTotalSize)
{
	INT32U addr_now = nAddress;
	INT32U addr_end = addr_now + nTotalSize;
	INT08U nReadBuf[SIZE_PAGE] = { 0, };

	INT32U nProcessSize = 0;
	INT32U nReadSize = 0;

	INT16U calc_Crc = 0;

	while ((addr_now < addr_end))
	{
		nProcessSize = addr_now + SIZE_PAGE;
		if (nProcessSize > addr_end)
		{
			nReadSize = addr_end - addr_now;
		}
		else
		{
			nReadSize = SIZE_PAGE;
		}

		sst26_read(addr_now, nReadSize, nReadBuf);
		addr_now += nReadSize;

		calc_Crc = crcInitStrCalc(calc_Crc, (INT08U*)(nReadBuf), nReadSize);
	}

	return calc_Crc;
}
