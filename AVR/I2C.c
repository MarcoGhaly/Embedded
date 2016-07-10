#include "I2C.h"

// Set Bit Rate
void I2C_setBitRate(u8 bitRate) {
	TWBR = bitRate;
}

// Set Acknowledge Bit Enabled
void I2C_setAcknowledgeBitEnabled(enum boolean enabled) {
	if (enabled) {
		TWCR |= (1 << TWEA);
		return;
	}
	TWCR &= ~((1 << TWINT) | (1 << TWEA));
}

// Send Start Bit
void I2C_sendStartBit() {
	TWCR &= ~((1 << TWINT) | (1 << TWSTA));
	TWCR |= (1 << TWSTA);
	TWCR |= (1 << TWINT);
}

// Send Stop Bit
void I2C_sendStopBit() {
	TWCR |= (1 << TWSTO);
	TWCR |= (1 << TWINT);
}

// Set Enabled
void I2C_setEnabled(enum boolean enabled) {
	if (enabled) {
		TWCR |= (1 << TWEN);
		return;
	}
	TWCR &= ~((1 << TWINT) | (1 << TWEN));
}

// Set Interrupt Enabled
void I2C_setInterruptEnabled(enum boolean enabled) {
	if (enabled) {
		TWCR |= (1 << TWIE);
		return;
	}
	TWCR &= ~((1 << TWINT) | (1 << TWIE));
}

// Set Divider
void I2C_setDivider(u8 divider) {
	TWSR &= ~(0x03 << TWPS0);
	TWSR |= (divider << TWPS0);
}

// Write Data
void I2C_writeByte(u8 data) {
	TWDR = data;
	TWCR |= (1 << TWINT);
}

// Receive Byte
void I2C_receiveByte() {
	TWCR |= (1 << TWINT);
}

// Read Byte
u8 I2C_readByte() {
	return TWDR;
}

// Check Flag
enum boolean I2C_checkFlag() {
	return (TWCR & (1 << TWINT));
}

// Check Status
u8 I2C_getStatus() {
	return (TWSR & 0xFC);
}

// Set Address
void I2C_setSlaveAddress(u8 address) {
	TWAR = address;
}