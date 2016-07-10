#include "USCI_SPI_B.h"

static const struct Pin usci_spi_pins[3] = { {1, 5}, {1, 6}, {1, 7} };

void usci_spi_init() {
	port_setPinFunction(usci_spi_pins[0].portNumber, usci_spi_pins[0].pinNumber, port_function_secondaryPeripheral);
	port_setPinFunction(usci_spi_pins[1].portNumber, usci_spi_pins[1].pinNumber, port_function_secondaryPeripheral);
	port_setPinFunction(usci_spi_pins[2].portNumber, usci_spi_pins[2].pinNumber, port_function_secondaryPeripheral);
}

void usci_spi_setFirstEdgePhase(u8 spi_number, u8 phase) {
	u8* usci_spi_control = (u8*)((u16)&UCB0CTL0 + spi_number * 0x70);
	*usci_spi_control &= ~(1 << 7);
	*usci_spi_control |= (phase << 7);
}

void usci_spi_setInactivePolarity(u8 spi_number, u8 polarity) {
	u8* usci_spi_control = (u8*)((u16)&UCB0CTL0 + spi_number * 0x70);
	*usci_spi_control &= ~(1 << 6);
	*usci_spi_control |= (polarity << 6);
}

void usci_spi_setDataDirection(u8 spi_number, u8 dataDirection) {
	u8* usci_spi_control = (u8*)((u16)&UCB0CTL0 + spi_number * 0x70);
	*usci_spi_control &= ~(1 << 5);
	*usci_spi_control |= (dataDirection << 5);
}

void usci_spi_setDataLength(u8 spi_number, u8 dataLength) {
	u8* usci_spi_control = (u8*)((u16)&UCB0CTL0 + spi_number * 0x70);
	*usci_spi_control &= ~(1 << 4);
	*usci_spi_control |= (dataLength << 4);
}

void usci_spi_setMode(u8 spi_number, u8 mode) {
	u8* usci_spi_control = (u8*)((u16)&UCB0CTL0 + spi_number * 0x70);
	*usci_spi_control &= ~(1 << 3);
	*usci_spi_control |= (mode << 3);
}

void usci_spi_setSynchronousMode(u8 spi_number, u8 synchronousMode) {
	u8* usci_spi_control = (u8*)((u16)&UCB0CTL0 + spi_number * 0x70);
	*usci_spi_control &= ~(0x03 << 1);
	*usci_spi_control |= (synchronousMode << 1);
}

void usci_spi_setSynchronousModeEnabled(u8 spi_number, enum boolean enabled) {
	u8* usci_spi_control = (u8*)((u16)&UCB0CTL0 + spi_number * 0x70);
	if (enabled) {
		*usci_spi_control |= (1 << 0);
	} else {
		*usci_spi_control &= ~(1 << 0);
	}
}

void usci_spi_setClockSource(u8 spi_number, u8 clockSource) {
	u8* usci_spi_control = (u8*)((u16)&UCB0CTL1 + spi_number * 0x70);
	*usci_spi_control &= ~(0x03 << 6);
	*usci_spi_control |= (clockSource << 6);
}

void usci_spi_setSoftwareResetEnabled(u8 spi_number, enum boolean enabled) {
	u8* usci_spi_control = (u8*)((u16)&UCB0CTL1 + spi_number * 0x70);
	if (enabled) {
		*usci_spi_control |= (1 << 0);
	} else {
		*usci_spi_control &= ~(1 << 0);
	}
}

u8 usci_spi_isBusy(u8 spi_number) {
	u8* usci_spi_status = (u8*)((u16)&UCB0STAT + spi_number * 0x70);
	if (*usci_spi_status & (1 << 0)) {
		return 1;
	}
	return 0;
}

void usci_spi_setBitRate(u8 spi_number, u32 bitRate) {
	u16* usci_spi_bitRate = (u16*)((u16)&UCB0BR0 + spi_number * 0x70);
	*usci_spi_bitRate = usci_spi_clockFrequency / bitRate;
}

void usci_spi_setTransmitInterruptEnabled(u8 spi_number, enum boolean enabled) {
	u8* usci_spi_interrupts = (u8*)((u16)&IE2 + spi_number * 0x05);
	if (enabled) {
		*usci_spi_interrupts |= (1 << 3);
	} else {
		*usci_spi_interrupts &= ~(1 << 3);
	}
}

void usci_spi_setReceiveInterruptEnabled(u8 spi_number, enum boolean enabled) {
	u8* usci_spi_interrupts = (u8*)((u16)&IE2 + spi_number * 0x05);
	if (enabled) {
		*usci_spi_interrupts |= (1 << 2);
	} else {
		*usci_spi_interrupts &= ~(1 << 2);
	}
}

u8 usci_spi_checkTransmitFlag(u8 spi_number) {
	u8* usci_spi_flags = (u8*)((u16)&IFG2 + spi_number * 0x04);
	if (*usci_spi_flags & (1 << 3)) {
		return 1;
	}
	return 0;
}

u8 usci_spi_checkReceiveFlag(u8 spi_number) {
	u8* usci_spi_flags = (u8*)((u16)&IFG2 + spi_number * 0x04);
	if (*usci_spi_flags & (1 << 2)) {
		return 1;
	}
	return 0;
}

u8 usci_spi_readByte(u8 spi_number) {
	u8* usci_spi_receive = (u8*)((u16)&UCB0RXBUF + spi_number * 0x70);
	return (*usci_spi_receive);
}

void usci_spi_writeByte(u8 spi_number, u8 value) {
	u8* usci_spi_transmit = (u8*)((u16)&UCB0TXBUF + spi_number * 0x70);
	*usci_spi_transmit = value;
}
