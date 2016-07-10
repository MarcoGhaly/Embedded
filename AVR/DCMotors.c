#include "DCMotors.h"

static struct Motor DCMotors_motors[DCMotors_motorsNumber];
static u8 DCMotors_counter = 0;

// Initialize Timer
static void DCMotors_initTimer(u8 frequency_MHz) {
	u16 DCMotors_timer0Dividers[DCMotors_frequnciesNumber] = {1, 8, 64, 256, 1024};
	u16 divider = (u16)(frequency_MHz * 1000 / DCMotors_intermediateFrequency_KHz);
	u8 i;
	for (i = 0; i < DCMotors_frequnciesNumber; i++) {
		if (divider / DCMotors_timer0Dividers[i] == 0) {
			divider = DCMotors_timer0Dividers[i];
			break;
		}
	}
	u8 compare = (u8)(frequency_MHz * 100 / divider);	// Frequency (Cycle / 100uS)
	// Output Frequency is 1 KHz
	timer0_setMode(timer0_CTC);
	timer0_setDivider(i + 1);
	timer0_setCompareValue(compare);
	timer0_setCompareInterruptEnabled(true);
	timer0_start();
}

// Set Pins
static void DCMotors_initPins(struct Pin (*pins)[2]) {
	u8 i;
	for (i = 0; i < DCMotors_motorsNumber; i++) {
		DCMotors_motors[i].pins[0].port = pins[i][0].port;
		DCMotors_motors[i].pins[0].pinNumber = pins[i][0].pinNumber;
		DCMotors_motors[i].pins[1].port = pins[i][1].port;
		DCMotors_motors[i].pins[1].pinNumber = pins[i][1].pinNumber;
		port_setPinDirection(&DCMotors_motors[i].pins[0], port_direction_output);
		port_setPinDirection(&DCMotors_motors[i].pins[1], port_direction_output);
	}
}

// Initialize
void DCMotors_init(u8 frequency_MHz, struct Pin (*pins)[2]) {
	DCMotors_initPins(pins);
	DCMotors_initTimer(frequency_MHz);
}

// Set Direction
void DCMotors_setDirection(u8 motorNumber, u8 direction) {
	DCMotors_motors[motorNumber].enable = false;
	port_writePin(&DCMotors_motors[motorNumber].pins[DCMotors_motors[motorNumber].selectedPin], low);
	DCMotors_motors[motorNumber].selectedPin = direction;
	DCMotors_motors[motorNumber].enable = true;
}

// Change Direction
void DCMotors_changeDirection(u8 motorNumber) {
	DCMotors_setDirection(motorNumber, (DCMotors_motors[motorNumber].selectedPin + 1) % 2);
}

// Set Ratio
void DCMotors_setRatio(u8 motorNumber, u8 ratio) {
	u8 counts = ratio * DCMotors_totalCounts / 100;
	if ( (ratio == 0) || (ratio == 100) ) {
		DCMotors_motors[motorNumber].enable = false;
		port_writePin(&DCMotors_motors[motorNumber].pins[DCMotors_motors[motorNumber].selectedPin], ratio / 100);
	} else {
		DCMotors_motors[motorNumber].counts = counts;
		DCMotors_motors[motorNumber].enable = true;
	}
}

// Toggle
static void DCMotors_toggle() {
	DCMotors_counter = (++DCMotors_counter) % DCMotors_totalCounts;
	u8 i;
	if (DCMotors_counter == 0) {
		for (i = 0; i < DCMotors_motorsNumber; i++) {
			if (DCMotors_motors[i].enable) {
				port_writePin(&DCMotors_motors[i].pins[DCMotors_motors[i].selectedPin], high);
			}
		}
		return;
	}
	for (i = 0; i < DCMotors_motorsNumber; i++) {
		if ( (DCMotors_motors[i].enable) && (DCMotors_counter == DCMotors_motors[i].counts) ) {
			port_writePin(&DCMotors_motors[i].pins[DCMotors_motors[i].selectedPin], low);
		}
	}
}

// Check Flags
void DCMotors_checkFlags() {
	if (timer0_checkCompareFlag()) {
		DCMotors_toggle();
	}
}

// Timer Interrupt
ISR(TIMER0_COMP_vect) {
	sei();
	DCMotors_toggle();
}