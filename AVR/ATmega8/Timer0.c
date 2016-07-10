#include <avr/io.h>
#include "Types.h"
#include "Timer0.h"

byte timer0_prescaler = 0;

void timer0_setPrescaler(byte prescaler) {
	timer0_prescaler = prescaler;
}

void timer0_setCounterValue(byte value) {
	TCNT0 = value;
}

byte timer0_getCounterValue() {
	return TCNT0;
}

void timer0_start() {
	TCCR0 &= ~( (1 << CS00) | (1 << CS01) | (1 << CS02) );
	timer0_setCounterValue(0);
	TCCR0 |= timer0_prescaler;
}

void timer0_stop() {
	TCCR0 &= ~( (1 << CS00) | (1 << CS01) | (1 << CS02) );
	TIFR = (1 << TOV0);
}

void timer0_enableOverFlowInterrupt() {
	TIMSK |= (1 << TOIE0);
}

void timer0_disableOverFlowInterrupt() {
	TIMSK &= ~(1 << TOIE0);
}

byte timer0_checkOverFlowFlag() {
	if (TIFR & (1 << TOV0)) {
		TIFR = (1 << TOV0);
		return 1;
	}
	return 0;
}