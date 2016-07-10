#include "USCI_UART.h"

static const struct Pin usci_uart_pins[2] = { {1, 1}, {1, 2} };

static enum boolean usci_uart_oversamplingModeEnabled = false;

void usci_uart_init() {
	port_setPinFunction(usci_uart_pins[0].portNumber, usci_uart_pins[0].pinNumber, port_function_secondaryPeripheral);
	port_setPinFunction(usci_uart_pins[1].portNumber, usci_uart_pins[1].pinNumber, port_function_secondaryPeripheral);
}

void usci_uart_setParityEnabled(u8 UART_number, enum boolean enabled) {
	u8* usci_control_0_ptr = (u8*)((u16)&UCA0CTL0 + 0x70 * UART_number);
	if (enabled) {
		*usci_control_0_ptr |= (1 << 7);
		return;
	}
	*usci_control_0_ptr &= ~(1 << 7);
}

void usci_uart_setParity(u8 UART_number, u8 parity) {
	u8* usci_control_0_ptr = (u8*)((u16)&UCA0CTL0 + 0x70 * UART_number);
	*usci_control_0_ptr &= ~(1 << 6);
	*usci_control_0_ptr |= (parity << 6);
}

void usci_uart_setFirstBit(u8 UART_number, u8 firstBit) {
	u8* usci_control_0_ptr = (u8*)((u16)&UCA0CTL0 + 0x70 * UART_number);
	*usci_control_0_ptr &= ~(1 << 5);
	*usci_control_0_ptr |= (firstBit << 5);
}

void usci_uart_setDataLength(u8 UART_number, u8 dataLength) {
	u8* usci_control_0_ptr = (u8*)((u16)&UCA0CTL0 + 0x70 * UART_number);
	*usci_control_0_ptr &= ~(1 << 4);
	*usci_control_0_ptr |= (dataLength << 4);
}

void usci_uart_setStopBits(u8 UART_number, u8 stopBits) {
	u8* usci_control_0_ptr = (u8*)((u16)&UCA0CTL0 + 0x70 * UART_number);
	*usci_control_0_ptr &= ~(1 << 3);
	*usci_control_0_ptr |= (stopBits << 3);
}

void usci_uart_setMode(u8 UART_number, u8 mode) {
	u8* usci_control_0_ptr = (u8*)((u16)&UCA0CTL0 + 0x70 * UART_number);
	*usci_control_0_ptr &= ~(0x03 << 1);
	*usci_control_0_ptr |= (mode << 1);
}

void usci_uart_setSynchronousModeEnabled(u8 UART_number, enum boolean enabled) {
	u8* usci_control_0_ptr = (u8*)((u16)&UCA0CTL0 + 0x70 * UART_number);
	if (enabled) {
		*usci_control_0_ptr |= (1 << 0);
		return;
	}
	*usci_control_0_ptr &= ~(1 << 0);
}

void usci_uart_setClockSource(u8 UART_number, u8 clockSource) {
	u8* usci_control_1_ptr = (u8*)((u16)&UCA0CTL1 + 0x70 * UART_number);
	*usci_control_1_ptr &= ~(0x03 << 6);
	*usci_control_1_ptr |= (clockSource << 6);
}

void usci_uart_setSoftwareResetEnabled(u8 UART_number, enum boolean enabled) {
	u8* usci_control_1_ptr = (u8*)((u16)&UCA0CTL1 + 0x70 * UART_number);
	if (enabled) {
		*usci_control_1_ptr |= (1 << 0);
		return;
	}
	*usci_control_1_ptr &= ~(1 << 0);
}

void usci_uart_setOversamplingModeEnabled(u8 UART_number, enum boolean enabled) {
	usci_uart_oversamplingModeEnabled = enabled;
	u8* usci_modulationControl_ptr = (u8*)((u16)&UCA0MCTL + 0x70 * UART_number);
	if (enabled) {
		*usci_modulationControl_ptr |= (1 << 0);
		return;
	}
	*usci_modulationControl_ptr &= ~(1 << 0);
}

u8 usci_uart_receiveByte(u8 UART_number) {
	u8* usci_receiveBuffer_ptr = (u8*)((u16)&UCA0RXBUF + 0x70 * UART_number);
	return (*usci_receiveBuffer_ptr);
}

void usci_uart_transmitByte(u8 UART_number, u8 data) {
	u8* usci_transmitBuffer_ptr = (u8*)((u16)&UCA0TXBUF + 0x70 * UART_number);
	*usci_transmitBuffer_ptr = data;
}

void usci_uart_setBaudRate(u8 UART_number, u32 baudRate) {
	u16* usci_baudRate_ptr = (u16*)((u16)&UCA0BR0 + 0x70 * UART_number);
	u8* usci_modulationControl_ptr = (u8*)((u16)&UCA0MCTL + 0x70 * UART_number);

	float UCBRx = (float)(usci_uart_clockFrequency) / baudRate;
	u8 UCBRSx = (u8) roundf((UCBRx - (u16)UCBRx) * 8);
	*usci_modulationControl_ptr &= ~(0x07 << 1);
	*usci_modulationControl_ptr |= (UCBRSx << 1);
	if (usci_uart_oversamplingModeEnabled) {
		UCBRx /= 16;
		u8 UCBRFx = (u8) roundf((UCBRx - (u16)UCBRx) * 16);
		*usci_modulationControl_ptr &= ~(0x0F << 4);
		*usci_modulationControl_ptr |= (UCBRFx << 4);
	}
	*usci_baudRate_ptr = (u16)UCBRx;
}

u8 usci_uart_checkReceiveFlag(u8 UART_number) {
	u8* usci_flags_ptr = (u8*)((u16)&IFG2 + 0x04 * UART_number);
	if (*usci_flags_ptr & (1 << 0)) {
		*usci_flags_ptr &= ~(1 << 0);
		return 1;
	}
	return 0;
}

u8 usci_uart_checkTransmitFlag(u8 UART_number) {
	u8* usci_flags_ptr = (u8*)((u16)&IFG2 + 0x04 * UART_number);
	if (*usci_flags_ptr & (1 << 1)) {
		*usci_flags_ptr &= ~(1 << 1);
		return 1;
	}
	return 0;
}

void usci_uart_setReceiveInterruptEnabled(u8 UART_number, enum boolean enabled) {
	u8* usci_interrupts_ptr = (u8*)((u16)&IE2 + 0x05 * UART_number);
	if (enabled) {
		*usci_interrupts_ptr |= (1 << 0);
		return;
	}
	*usci_interrupts_ptr &= ~(1 << 0);
}

void usci_uart_setTransmitInterruptEnabled(u8 UART_number, enum boolean enabled) {
	u8* usci_interrupts_ptr = (u8*)((u16)&IE2 + 0x05 * UART_number);
	if (enabled) {
		*usci_interrupts_ptr |= (1 << 1);
		return;
	}
	*usci_interrupts_ptr &= ~(1 << 1);
}
