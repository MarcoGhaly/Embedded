#include <avr/io.h>
#include "Types.h"
#include "WDT.h"

void WDT_setCountsNumber(byte countsNumber) {
	WDTCR |= ( (1 << WDCE) | (1 << WDE) );
	WDTCR |= countsNumber;	//	Clear WDCE bit & Set timeout period 2.1 sec
}

void WDT_enable() {
	WDTCR |= (1 << WDE);
}

void WDT_reset() {
	WDT_disable();
	WDT_enable();
}

void WDT_disable() {
	WDTCR |= ( (1 << WDCE) | (1 << WDE) );
	WDTCR &= ~(1 << WDE);
}

byte WDT_checkFlag() {
	if (MCUCSR & (1 << WDRF)) {
		MCUCSR &= ~(1 << WDRF);
		return 1;
	}
	return 0;
}