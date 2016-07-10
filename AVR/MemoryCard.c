#include "MemoryCard.h"

static u32 memoryCard_currentAddress;

// Initialize
void memoryCard_init(u8 frequency_MHz, struct Pin* slavePin) {
	u8 i;
	for(i = 0; i < 10; i++) {
		masterSPI_transmitByte(0xFF);	// Apply 80 clock pulses
		while(!masterSPI_isTransmissionComplete());
	}
	masterSPI_activate(0);
	
	// Initialize Card
	memoryCard_sendCommand(memoryCard_command_resetCard, 0);
	memoryCard_sendCommand(memoryCard_command_initialize, 0);
}

// Send Command
u8 memoryCard_sendCommand(u8 cmd, u32 argument) {
	masterSPI_transmitByte(0xFF);	// Dummy Byte
	while(!masterSPI_isTransmissionComplete());
	masterSPI_transmitByte(cmd | 0x40);
	while(!masterSPI_isTransmissionComplete());
	masterSPI_transmitByte((u8)(argument >> 24));
	while(!masterSPI_isTransmissionComplete());
	masterSPI_transmitByte((u8)(argument >> 16));
	while(!masterSPI_isTransmissionComplete());
	masterSPI_transmitByte((u8)(argument >> 8));
	while(!masterSPI_isTransmissionComplete());
	masterSPI_transmitByte((u8)argument);
	while(!masterSPI_isTransmissionComplete());
	masterSPI_transmitByte(0x95);	// Correct CRC for Reset Command
	while(!masterSPI_isTransmissionComplete());
	while (1) {
		masterSPI_transmitByte(0xFF);	// Response Time (NCR)
		while(!masterSPI_isTransmissionComplete());
		u8 response = SPI_readByte();	
		if (response != 0xFF) {
			return response;	// Data Response
		}
	}
}

// Set Read Mode
void memoryCard_setReadMode(u32 address) {
	memoryCard_sendCommand(memoryCard_command_readSingleBlock, address);
	memoryCard_currentAddress = address;
	do {
		masterSPI_transmitByte(0xFF);	// Response Time (NCR)
		while(!masterSPI_isTransmissionComplete());
	} while(SPI_readByte() != 0xFE);
}

// Read Next Byte
u8 memoryCard_readNextByte() {
	masterSPI_transmitByte(0xFF);
	while(!masterSPI_isTransmissionComplete());
	u8 data = SPI_readByte();
	memoryCard_currentAddress++;
	if (memoryCard_currentAddress % memoryCard_blockSize_bytes == 0) {
		// Receive 2 CRC bytes
		masterSPI_transmitByte(0xFF);
		while(!masterSPI_isTransmissionComplete());
		masterSPI_transmitByte(0xFF);
		while(!masterSPI_isTransmissionComplete());
		
		memoryCard_setReadMode(memoryCard_currentAddress);
	}
	return data;
}