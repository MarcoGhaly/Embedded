#include <avr/io.h>
#include "AC.h"

void AC_init() {
	SFIOR &= ~(1 << ACME);	//	Negative input is applied at pin AIN1
	ACSR &= ~(1 << ACBG);	//	AIN0 is applied to the positive input
	ACSR &= ~( (1 << ACIS0) | (1 << ACIS1) );	//	Comparator Interrupt on Output Toggle
}

void AC_enableInterrupt() {
	ACSR |= (1 << ACIE);
}

void AC_disableInterrupt() {
	ACSR &= ~(1 << ACIE);
}

u8 AC_readOutputBit() {
	if (ACSR & (1 << ACO)) {
		return 1;
	}
	return 0;
}

u8 AC_checkFlag() {
	if (ACSR & (1 << ACI)) {
		ACSR |= (1 << ACI);
		return 1;
	}
	return 0;
}