#include <avr/interrupt.h>
#include "Port.h"
#include "Timer1.h"
#include "DCMotors_2.h"

static const u8 DCMotors_ports[DCMotors_number][2] = { {'B', 'B'}, {'C', 'C'} };
static const u8 DCMotors_pins[DCMotors_number][2] = { {0, 1}, {0, 1} };
static u8 DCMotors_selectedPins[DCMotors_number] = {0, 0};
static enum boolean DCMotors_enable[DCMotors_number] = {false, false};

void DCMotors_init() {
	u8 i, j;
	for (i = 0; i < DCMotors_number; i++) {
		for (j = 0; j < DCMotors_number; j++) {
			port_setPinDirection(DCMotors_ports[i][j], DCMotors_pins[i][j], port_output);
		}
	}
	timer1_setMode(timer1_PWM_fast_ICR1);
	timer1_setPrescaler(timer1_clock_1);
	timer1_enableCompareInterruptA();
	timer1_enableCompareInterruptB();
	timer1_enableCaptureInterrupt();
	timer1_setCaptureValue(DCMotors_totalCounts);
	timer1_start();
}

void DCMotors_setDirection(u8 motor, u8 direction) {
	cli();
	port_writePin(DCMotors_ports[motor][DCMotors_selectedPins[motor]], DCMotors_pins[motor][DCMotors_selectedPins[motor]], low);
	DCMotors_selectedPins[motor] = direction;
	sei();
}

void DCMotors_changeDirection(u8 motor) {
	DCMotors_setDirection(motor, (DCMotors_selectedPins[motor] + 1) % DCMotors_number);
}

void DCMotors_setRatio(u8 motor, u8 ratio) {
	if ( (ratio == 0) || (ratio == 100) ) {
		DCMotors_enable[motor] = false;
		port_writePin(DCMotors_ports[motor][DCMotors_selectedPins[motor]], DCMotors_pins[motor][DCMotors_selectedPins[motor]], ratio / 100);
	} else {
		DCMotors_enable[motor] = true;
		u16 temp = (u16)((u32)DCMotors_totalCounts * ratio / 100);
		if (motor == DCMotors_left) {
			timer1_setCompareValueA(temp);
		} else {
			timer1_setCompareValueB(temp);
		}
	}
}

void DCMotors_checkFlags() {
	if ( (timer1_checkCompareFlagA()) && (DCMotors_enable[DCMotors_left]) ) {
		port_writePin(DCMotors_ports[DCMotors_left][DCMotors_selectedPins[DCMotors_left]], DCMotors_pins[DCMotors_left][DCMotors_selectedPins[DCMotors_left]], low);
	}
	if ( (timer1_checkCompareFlagB()) && (DCMotors_enable[DCMotors_right]) ) {
		port_writePin(DCMotors_ports[DCMotors_right][DCMotors_selectedPins[DCMotors_right]], DCMotors_pins[DCMotors_right][DCMotors_selectedPins[DCMotors_right]], low);
	}
	if (timer1_checkCaptureFlag()) {
		if (DCMotors_enable[DCMotors_left]) {
			port_writePin(DCMotors_ports[DCMotors_left][DCMotors_selectedPins[DCMotors_left]], DCMotors_pins[DCMotors_left][DCMotors_selectedPins[DCMotors_left]], high);
		}
		if (DCMotors_enable[DCMotors_right]) {
			port_writePin(DCMotors_ports[DCMotors_right][DCMotors_selectedPins[DCMotors_right]], DCMotors_pins[DCMotors_right][DCMotors_selectedPins[DCMotors_right]], high);
		}
	}
}

ISR (TIMER1_COMPA_vect) {
	//sei();
	if (DCMotors_enable[DCMotors_left]) {
		port_writePin(DCMotors_ports[DCMotors_left][DCMotors_selectedPins[DCMotors_left]], DCMotors_pins[DCMotors_left][DCMotors_selectedPins[DCMotors_left]], low);
	}
}

ISR (TIMER1_COMPB_vect) {
	//sei();
	if (DCMotors_enable[DCMotors_right]) {
		port_writePin(DCMotors_ports[DCMotors_right][DCMotors_selectedPins[DCMotors_right]], DCMotors_pins[DCMotors_right][DCMotors_selectedPins[DCMotors_right]], low);
	}
}

ISR (TIMER1_CAPT_vect) {
	//sei();
	if (DCMotors_enable[DCMotors_left]) {
		port_writePin(DCMotors_ports[DCMotors_left][DCMotors_selectedPins[DCMotors_left]], DCMotors_pins[DCMotors_left][DCMotors_selectedPins[DCMotors_left]], high);
	}
	if (DCMotors_enable[DCMotors_right]) {
		port_writePin(DCMotors_ports[DCMotors_right][DCMotors_selectedPins[DCMotors_right]], DCMotors_pins[DCMotors_right][DCMotors_selectedPins[DCMotors_right]], high);
	}
}