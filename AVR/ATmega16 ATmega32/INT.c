#include <avr/io.h>
#include "INT.h"

void INT_setMode(u8 interruptNumber, u8 mode) {
	if (interruptNumber == 2) {
		MCUCSR &= ~(1 << ISC2);
		MCUCSR |= ((mode & 0x01) << ISC2);
	} else {
		MCUCR &= ~(0x03 << (interruptNumber * 2));
		MCUCR |= (mode << (interruptNumber * 2));
	}
	
}

void INT_enable(u8 interruptNumber) {
	if (interruptNumber == 2) {
		GICR |= (1 << INT2);
	} else {
		GICR |= (1 << (interruptNumber + INT0));
	}
}

void INT_disable(u8 interruptNumber) {
	if (interruptNumber == 2) {
		GICR &= ~(1 << INT2);
	} else {
		GICR &= ~(1 << (interruptNumber + INT0));
	}
}