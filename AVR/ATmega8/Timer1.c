#include <avr/io.h>
#include "Timer1.h"

u8 timer1_prescaler = 0;

void timer1_setMode(u8 mode) {
	TCCR1A &= ~( (1 << WGM10) | (1 << WGM11) );
	TCCR1B &= ~( (1 << WGM12) | (1 << WGM13) );
	TCCR1A |= (mode & 0x03);
	TCCR1B |= ( (mode >> 2) << WGM12 );
}

void timer1_setPrescaler(u8 prescaler) {
	timer1_prescaler = (prescaler & 0x07);
}

void timer1_setCompareValue(u8 compareNumber, u16 value) {
	u8* compare_ptr = (u8*)((u8)&OCR1AH - 2 * (compareNumber - 1));
	*compare_ptr = (u8) (value >> 8);
	*(--compare_ptr) = (u8) (value);
}

void timer1_setCaptureValue(u16 value) {
	ICR1H = (u8) (value >> 8);
	ICR1L = (u8) (value);
}

u16 timer1_getCaptureValue() {
	u16 lowByte = ICR1L;
	u16 highByte = ICR1H;
	return (lowByte | (highByte << 8));
}

void timer1_setCounterValue(u16 value) {
	TCNT1H = (u8) (value >> 8);
	TCNT1L = (u8) (value);
}

u16 timer1_getCounterValue() {
	u16 lowByte = TCNT1L;
	u16 highByte = TCNT1H;
	return (lowByte | (highByte << 8));
}

void timer1_start() {
	TCCR1B &= ~(0x07 << CS10);
	TCCR1B |= timer1_prescaler;
}

void timer1_stop() {
	TCCR1B &= ~(0x07 << CS10);
	TIFR = (0x0F << TOV1);
}

void timer1_setCompareInterruptEnabled(u8 compareNumber, enum boolean enabled) {
	u8 shift = OCIE1A - (compareNumber - 1);
	if (enabled) {
		TIMSK |= (1 << shift);
	} else {
		TIMSK &= ~(1 << shift);
	}
}

void timer1_setCaptureInterruptEnabled(enum boolean enabled) {
	if (enabled) {
		TIMSK |= (1 << TICIE1);
	} else {
		TIMSK &= ~(1 << TICIE1);
	}
}

void timer1_setOverflowInterruptEnabled(enum boolean enabled) {
	if (enabled) {
		TIMSK |= (1 << TOIE1);
	} else {
		TIMSK &= ~(1 << TOIE1);
	}
}

u8 timer1_checkCompareFlag(u8 compareNumber) {
	u8 shift = OCF1A - (compareNumber - 1);
	if (TIFR & (1 << shift)) {
		TIFR = (1 << shift);
		return 1;
	}
	return 0;
}

u8 timer1_checkCaptureFlag() {
	if (TIFR & (1 << ICF1)) {
		TIFR = (1 << ICF1);
		return 1;
	}
	return 0;
}

u8 timer1_checkOverFlowFlag() {
	if (TIFR & (1 << TOV1)) {
		TIFR = (1 << TOV1);
		return 1;
	}
	return 0;
}