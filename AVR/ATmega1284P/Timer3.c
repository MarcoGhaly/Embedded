#include <avr/io.h>
#include "Timer3.h"

u8 timer3_prescaler = 0;

void timer3_setMode(u8 mode) {
	TCCR3A &= ~( (1 << WGM30) | (1 << WGM31) );
	TCCR3B &= ~( (1 << WGM32) | (1 << WGM33) );
	TCCR3A |= (mode & 0x03);
	TCCR3B |= ( (mode >> 2) << WGM32 );
}

void timer3_setPrescaler(u8 prescaler) {
	timer3_prescaler = (prescaler & 0x07);
}

void timer3_setCompareValue(u8 compareNumber, u16 value) {
	u8* compare_ptr = (u8*)((u8)&OCR3AH - 2 * (compareNumber - 1));
	*compare_ptr = (u8) (value >> 8);
	*(--compare_ptr) = (u8) (value);
}

void timer3_setCaptureValue(u16 value) {
	ICR3H = (u8) (value >> 8);
	ICR3L = (u8) (value);
}

u16 timer3_getCaptureValue() {
	u16 lowByte = ICR3L;
	u16 highByte = ICR3H;
	return (lowByte | (highByte << 8));
}

void timer3_setCounterValue(u16 value) {
	TCNT3H = (u8) (value >> 8);
	TCNT3L = (u8) (value);
}

u16 timer3_getCounterValue() {
	u16 lowByte = TCNT3L;
	u16 highByte = TCNT3H;
	return (lowByte | (highByte << 8));
}

void timer3_start() {
	TCCR3B &= ~(0x07 << CS30);
	TCCR3B |= timer3_prescaler;
}

void timer3_stop() {
	TCCR3B &= ~(0x07 << CS30);
	TIFR3 = (0x07 << TOV3) | (1 << ICF3);
}

void timer3_setCompareInterruptEnabled(u8 compareNumber, enum boolean enabled) {
	u8 shift = OCIE3A - (compareNumber - 1);
	if (enabled) {
		TIMSK3 |= (1 << shift);
	} else {
		TIMSK3 &= ~(1 << shift);
	}
}

void timer3_setCaptureInterruptEnabled(enum boolean enabled) {
	if (enabled) {
		TIMSK3 |= (1 << ICIE3);
	} else {
		TIMSK3 &= ~(1 << ICIE3);
	}
}

void timer3_setOverflowInterruptEnabled(enum boolean enabled) {
	if (enabled) {
		TIMSK3 |= (1 << TOIE3);
	} else {
		TIMSK3 &= ~(1 << TOIE3);
	}
}

u8 timer3_checkCompareFlag(u8 compareNumber) {
	u8 shift = OCF3A - (compareNumber - 1);
	if (TIFR3 & (1 << shift)) {
		TIFR3 = (1 << shift);
		return 1;
	}
	return 0;
}

u8 timer3_checkCaptureFlag() {
	if (TIFR3 & (1 << ICF3)) {
		TIFR3 = (1 << ICF3);
		return 1;
	}
	return 0;
}

u8 timer3_checkOverFlowFlag() {
	if (TIFR3 & (1 << TOV3)) {
		TIFR3 = (1 << TOV3);
		return 1;
	}
	return 0;
}