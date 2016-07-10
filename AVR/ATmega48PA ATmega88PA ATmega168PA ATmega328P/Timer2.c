#include <avr/io.h>
#include "Timer2.h"

u8 timer2_prescaler = 0;

void timer2_setMode(u8 mode) {
	TCCR2A &= ~( (1 << WGM20) | (1 << WGM21) );
	TCCR2A |= (mode & 0x03);
}

void timer2_setPrescaler(u8 prescaler) {
	timer2_prescaler = (prescaler & 0x07);
}

void timer2_setCompareValue(u8 compareNumber, u16 value) {
	u8* compare_ptr = (u8*)((u8)&OCR2A - (compareNumber - 1));
	*compare_ptr = value;
}

void timer2_setCounterValue(u8 value) {
	TCNT2 = value;
}

void timer2_start() {
	TCCR2B &= ~(0x07 << CS20);
	TCCR2B |= timer2_prescaler;
}

void timer2_stop() {
	TCCR2B &= ~(0x07 << CS20);
	TIFR2 = (0x07 << TOV2);
}

void timer2_setCompareInterruptEnabled(u8 compareNumber, enum boolean enabled) {
	u8 shift = OCIE2A + (compareNumber - 1);
	if (enabled) {
		TIMSK2 |= (1 << shift);
	} else {
		TIMSK2 &= ~(1 << shift);
	}
}

void timer2_setOverflowInterruptEnabled(enum boolean enabled) {
	if (enabled) {
		TIMSK2 |= (1 << TOIE2);
	} else {
		TIMSK2 &= ~(1 << TOIE2);
	}
}

u8 timer2_checkCompareFlag(u8 compareNumber) {
	u8 shift = OCF2A + (compareNumber - 1);
	if (TIFR2 & (1 << shift)) {
		TIFR2 = (1 << shift);
		return 1;
	}
	return 0;
}

u8 timer2_checkOverFlowFlag() {
	if (TIFR2 & (1 << TOV2)) {
		TIFR2 = (1 << TOV2);
		return 1;
	}
	return 0;
}