#include "DCMotors2.h"

static struct Motor DCMotors_motors[DCMotors_motorsNumber];
static u16 DCMotors_totalCounts;

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
	DCMotors_totalCounts = (u8)(frequency_MHz * 1000 / DCMotors_timer0Dividers[i - 1]);	// Frequency (Cycle / 1ms)
	// Output Frequency is 1 KHz
	timer1_setMode(timer1_mode_PWM_fast_ICR1);
	timer1_setDivider(i);
	timer1_setCaptureValue(DCMotors_totalCounts);
	timer1_setCaptureInterruptEnabled(true);
	timer1_start();
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
	timer1_setCompareInterruptEnabled(motorNumber, false);
	port_writePin(&DCMotors_motors[motorNumber].pins[DCMotors_motors[motorNumber].selectedPin], low);
	DCMotors_motors[motorNumber].selectedPin = direction;
	timer1_setCompareInterruptEnabled(motorNumber, true);
}

// Change Direction
void DCMotors_changeDirection(u8 motorNumber) {
	DCMotors_setDirection(motorNumber, (DCMotors_motors[motorNumber].selectedPin + 1) % 2);
}

// Set Ratio
void DCMotors_setRatio(u8 motorNumber, u8 ratio) {
	u16 counts = DCMotors_totalCounts * ratio / 100;
	if (ratio % 100 == 0) {
		timer1_setCompareInterruptEnabled(motorNumber, false);
		port_writePin(&DCMotors_motors[motorNumber].pins[DCMotors_motors[motorNumber].selectedPin], ratio / 100);
	} else {
		timer1_setCompareValue(motorNumber, counts);
		timer1_setCompareInterruptEnabled(motorNumber, true);
	}
}

// Timer Compare Interrupt A
ISR(TIMER1_COMPA_vect) {
	sei();
	port_writePin(&DCMotors_motors[0].pins[DCMotors_motors[0].selectedPin], low);
}

// Timer Compare Interrupt B
ISR(TIMER1_COMPB_vect) {
	sei();
	port_writePin(&DCMotors_motors[1].pins[DCMotors_motors[1].selectedPin], low);
}

// Timer Compare Interrupt A
ISR(TIMER1_CAPT_vect) {
	sei();
	u8 i;
	for (i = 0; i < DCMotors_motorsNumber; i++) {
		port_writePin(&DCMotors_motors[i].pins[DCMotors_motors[i].selectedPin], high);
	}
}