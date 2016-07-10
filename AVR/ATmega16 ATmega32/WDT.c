#include <avr/io.h>
#include "WDT.h"

void WDT_enable() {
	WDTCR |= ( (1 << WDP0) | (1 << WDP1) | (1 << WDP2) );	//	Timeout period 2.1 sec
	WDTCR |= (1 << WDE);
}

void WDT_reset() {
	WDT_disable();
	WDT_enable();
}

void WDT_disable() {
	WDTCR |= ( (1 << WDTOE) | (1 << WDE) );
	WDTCR &= ~(1 << WDE);
}

u8 WDT_checkFlag() {
	if (MCUCSR & (1 << WDRF)) {
		MCUCSR |= (1 << WDRF);
		return 1;
	}
	return 0;
}