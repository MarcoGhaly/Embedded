#include "Timer0.h"

u8 timer0_divider = 0;

void timer0_setMode(u8 mode) {
	TCCR0 &= ~( (1 << WGM00) | (1 << WGM01) );
	TCCR0 |= ( ( (mode & 0x01) << WGM00 ) | ( (mode >> 1) << WGM01 ) );
}

void timer0_setDivider(u8 divider) {
	timer0_divider = (divider & 0x07);
}

void timer0_setCompareValue(u8 value) {
	OCR0 = value;
}

void timer0_setCounterValue(u8 value) {
	TCNT0 = value;
}

u8 timer0_getCounterValue() {
	return TCNT0;
}

void timer0_start() {
	TCCR0 &= ~(0x07 << CS00);
	TCCR0 |= (timer0_divider << CS00);
}

void timer0_stop() {
	TCCR0 &= ~(0x07 << CS00);
	TIFR = (0x03 << TOV0);
}

void timer0_setCompareInterruptEnabled(enum boolean enabled) {
	if (enabled) {
		TIMSK |= (1 << OCIE0);
	} else {
		TIMSK &= ~(1 << OCIE0);
	}
}

void timer0_setOverflowInterruptEnabled(enum boolean enabled) {
	if (enabled) {
		TIMSK |= (1 << TOIE0);
	} else {
		TIMSK &= ~(1 << TOIE0);
	}
}

enum boolean timer0_checkCompareFlag() {
	if (TIFR & (1 << OCF0)) {
		TIFR = (1 << OCF0);
		return true;
	}
	return false;
}

enum boolean timer0_checkOverFlowFlag() {
	if (TIFR & (1 << TOV0)) {
		TIFR = (1 << TOV0);
		return true;
	}
	return false;
}