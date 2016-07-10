#include "USART.h"

// Double Transmission Speed
void USART_setTransmissionSpeedDoubled(enum boolean doubled) {
	if (doubled) {
		UCSRA |= (1 << U2X);
		return;
	}
	UCSRA &= ~(1 << U2X);
}

// Set Receiver Interrupt Enabled
void USART_setReceiverInterruptEnabled(enum boolean enabled) {
	if (enabled) {
		UCSRB |= (1 << RXCIE);
		return;
	}
	UCSRB &= ~(1 << RXCIE);
}

// Set Transmitter Interrupt Enabled
void USART_setTransmitterInterruptEnabled(enum boolean enabled) {
	if (enabled) {
		UCSRB |= (1 << TXCIE);
		return;
	}
	UCSRB &= ~(1 << TXCIE);
}

// Set Transmitter Buffer Empty Interrupt Enable
void USART_setTransmitterBufferEmptyInterruptEnabled(enum boolean enabled) {
	if (enabled) {
		UCSRB |= (1 << UDRIE);
		return;
	}
	UCSRB &= ~(1 << UDRIE);
}

// Set Receiver Enabled
void USART_setReceiverEnabled(enum boolean enabled) {
	if (enabled) {
		UCSRB |= (1 << RXEN);
		return;
	}
	UCSRB &= ~(1 << RXEN);
}

// Set Transmitter Enabled
void USART_setTransmitterEnabled(enum boolean enabled) {
	if (enabled) {
		UCSRB |= (1 << TXEN);
		return;
	}
	UCSRB &= ~(1 << TXEN);
}

// Get Ninth Receive Bit
u8 USART_getNinthReceiveBit() {
	return ((UCSRB >> RXB8) & 0x01);
}

// Set Ninth Transmit Bit
void USART_setNinthTransmitBit(u8 ninthBit) {
	UCSRB &= ~(1 << TXB8);
	UCSRB |= ((ninthBit & 0x01) << TXB8);
}

// Set Mode
void USART_setMode(u8 mode) {
	u8 ucsrc = UBRRH;
	ucsrc = UCSRC;
	ucsrc &= ~(1 << UMSEL);
	ucsrc |= ((mode << UMSEL) | (1 << URSEL));
	UCSRC = ucsrc;
}

// Set Parity
void USART_setParity(u8 parity) {
	u8 ucsrc = UBRRH;
	ucsrc = UCSRC;
	ucsrc &= ~(0x03 << UPM0);
	ucsrc |= ((parity << UPM0) | (1 << URSEL));
	UCSRC = ucsrc;
}

// Set Stop Bits Number
void USART_setStopBitsNumber(u8 bitsNumber) {
	bitsNumber -= 1;
	u8 ucsrc = UBRRH;
	ucsrc = UCSRC;
	ucsrc &= ~(1 << USBS);
	ucsrc |= ((bitsNumber << USBS) | (1 << URSEL));
	UCSRC = ucsrc;
}

// Set Character Size
void USART_setCharacterSize(u8 size) {
	if (size == 9) {
		size -= 2;
	} else {
		size -= 5;
	}
	u8 ucsrc = UBRRH;
	ucsrc = UCSRC;
	UCSRB &= ~(1 << UCSZ2);
	UCSRB |= ((size >> 2) << UCSZ2);
	ucsrc &= ~(0x03 << UCSZ0);
	ucsrc |= (((size & 0x03) << UCSZ0) | (1 << URSEL));
	UCSRC = ucsrc;
}

// Set Clock Polarity
void USART_setClockPolarity(u8 clockPolarity) {
	u8 ucsrc = UBRRH;
	ucsrc = UCSRC;
	ucsrc &= ~(1 << UCPOL);
	ucsrc |= ((clockPolarity << UCPOL) | (1 << URSEL));
	UCSRC = ucsrc;
}

// Set Baud Rate
void USART_setBaudRate(u8 frequency_MHz, u32 baudRate) {
	u8 ucsrc = UBRRH;
	ucsrc = UCSRC;
	u16 ubrr = (u16)((u32)frequency_MHz * 1000000 / baudRate / 2);
	if (!(ucsrc & (1 << UMSEL))) {
		ubrr /= 4;
		if (!(UCSRA & (1 << U2X))) {
			ubrr /= 2;
		}
	}
	ubrr -= 1;
	ubrr &= 0x0FFF;
	UBRRH = (u8)(ubrr >> 8);
	UBRRL = (u8)ubrr;
}

// Write
void USART_write(u8 data) {
	UDR = data;
}

// Read
u8 USART_read() {
	return UDR;
}

// Is Receive Complete
enum boolean USART_isReceiveComplete() {
	if (UCSRA & (1 << RXC)) {
		return true;
	}
	return false;
}

// Is Transmit Complete
enum boolean USART_isTransmitComplete() {
	if (UCSRA & (1 << TXC)) {
		UCSRA |= (1 << TXC);
		return true;
	}
	return false;
}

// Is Transmit Buffer Empty
enum boolean USART_isTransmitBufferEmpty() {
	if (UCSRA & (1 << UDRE)) {
		return true;
	}
	return false;
}