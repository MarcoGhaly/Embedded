#include "SPI.h"

// Set Interrupt Enabled
void SPI_setInterruptEnabled(enum boolean enabled) {
	if (enabled) {
		SPCR |= (1 << SPIE);
		return;
	}
	SPCR &= ~(1 << SPIE);
}

// Set SPI Enabled
void SPI_setEnabled(enum boolean enabled) {
	if (enabled) {
		SPCR |= (1 << SPE);
		return;
	}
	SPCR &= ~(1 << SPE);
}

// Set Data Order
void SPI_setDataOrder(u8 dataOrder) {
	SPCR &= ~(1 << DORD);
	SPCR |= (dataOrder << DORD);
}

// Set Mode
void SPI_setMode(u8 mode) {
	SPCR &= ~(1 << MSTR);
	SPCR |= (mode << MSTR);
}

// Set Polarity
void SPI_setPolarity(u8 polarity) {
	SPCR &= ~(1 << CPOL);
	SPCR |= (polarity << CPOL);
}

// Set Phase
void SPI_setPhase(u8 phase) {
	SPCR &= ~(1 << CPHA);
	SPCR |= (phase << CPHA);
}

// Set Divider
void SPI_setDivider(u8 divider) {
	SPCR &= ~(0x03 << SPR0);
	SPSR &= ~(1 << SPI2X);
	SPCR |= ((divider & 0x03) << SPR0);
	SPSR |= ((divider >> 2) << SPI2X);
}

// Write Byte
void SPI_writeByte(u8 data) {
    SPDR = data;
}

// Read Byte
u8 SPI_readByte() {
	return SPDR;
}

// Check Flag
u8 SPI_checkFlag() {
	if (SPSR & (1 << SPIF)) {
		return 1;
	}
	return 0;
}