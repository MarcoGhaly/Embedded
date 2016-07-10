#include <avr/io.h>
#include "Timer0.h"

u8 timer0_prescaler = 0;

void timer0_setMode(u8 mode) {
	TCCR0A &= ~( (1 << WGM00) | (1 << WGM01) );
	TCCR0A |= (mode & 0x03);
}

void timer0_setPrescaler(u8 prescaler) {
	timer0_prescaler = (prescaler & 0x07);
}

void timer0_setCompareValue(u8 compareNumber, u16 value) {
	u8* compare_ptr = (u8*)((u8)&OCR0A - (compareNumber - 1));
	*compare_ptr = value;
}

void timer0_setCounterValue(u8 value) {
	TCNT0 = value;
}

void timer0_start() {
	TCCR0B &= ~(0x07 << CS00);
	TCCR0B |= timer0_prescaler;
}

void timer0_stop() {
	TCCR0B &= ~(0x07 << CS00);
	TIFR0 = (0x07 << TOV0);
}

void timer0_setCompareInterruptEnabled(u8 compareNumber, enum boolean enabled) {
	u8 shift = OCIE0A + (compareNumber - 1);
	if (enabled) {
		TIMSK0 |= (1 << shift);
	} else {
		TIMSK0 &= ~(1 << shift);
	}
}

void timer0_setOverflowInterruptEnabled(enum boolean enabled) {
	if (enabled) {
		TIMSK0 |= (1 << TOIE0);
	} else {
		TIMSK0 &= ~(1 << TOIE0);
	}
}

u8 timer0_checkCompareFlag(u8 compareNumber) {
	u8 shift = OCF0A + (compareNumber - 1);
	if (TIFR0 & (1 << shift)) {
		TIFR0 = (1 << shift);
		return 1;
	}
	return 0;
}

u8 timer0_checkOverFlowFlag() {
	if (TIFR0 & (1 << TOV0)) {
		TIFR0 = (1 << TOV0);
		return 1;
	}
	return 0;
}