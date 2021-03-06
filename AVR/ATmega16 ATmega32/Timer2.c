#include "Timer2.h"

u8 timer2_divider = 0;

void timer2_setMode(u8 mode) {
	TCCR2 &= ~( (1 << WGM20) | (1 << WGM21) );
	TCCR2 |= ( ( (mode & 0x01) << WGM20 ) | ( (mode >> 1) << WGM21 ) );
}

void timer2_setDivider(u8 divider) {
	timer2_divider = (divider & 0x07);
}

void timer2_setCompareValue(u8 value) {
	OCR2 = value;
}

void timer2_setCounterValue(u8 value) {
	TCNT2 = value;
}

u8 timer2_getCounterValue() {
	return TCNT2;
}

void timer2_start() {
	TCCR2 &= ~(0x07 << CS20);
	TCCR2 |= (timer2_divider << CS20);
}

void timer2_stop() {
	TCCR2 &= ~(0x07 << CS20);
	TIFR = (0x03 << TOV2);
}

void timer2_setCompareInterruptEnabled(enum boolean enabled) {
	if (enabled) {
		TIMSK |= (1 << OCIE2);
	} else {
		TIMSK &= ~(1 << OCIE2);
	}
}

void timer2_setOverflowInterruptEnabled(enum boolean enabled) {
	if (enabled) {
		TIMSK |= (1 << TOIE2);
	} else {
		TIMSK &= ~(1 << TOIE2);
	}
}

enum boolean timer2_checkCompareFlag() {
	if (TIFR & (1 << OCF2)) {
		TIFR = (1 << OCF2);
		return true;
	}
	return false;
}

enum boolean timer2_checkOverFlowFlag() {
	if (TIFR & (1 << TOV2)) {
		TIFR = (1 << TOV2);
		return true;
	}
	return false;
}