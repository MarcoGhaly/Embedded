#include "ServoMotors.h"

static struct ServoMotor servoMotors_motors[servoMotors_motorsNumber];
static float servoMotors_cycleTime_us;

// Initialize Timer
static void servoMotors_initTimer(u8 frequency_MHz) {
	u16 servoMotors_timer1Dividers[servoMotors_frequnciesNumber] = {1, 8, 64, 256, 1024};
	u16 divider = (u16)(frequency_MHz * 1000 / servoMotors_intermediateFrequency_KHz);
	u8 i;
	for (i = 0; i < servoMotors_frequnciesNumber; i++) {
		if (divider / servoMotors_timer1Dividers[i] == 0) {
			servoMotors_cycleTime_us = (float)servoMotors_timer1Dividers[i - 1] / divider;
			break;
		}
	}
	// Output Frequency is 50 Hz
	timer1_setMode(timer1_PWM_fast_ICR1);
	timer1_setDivider(i);
	timer1_setCaptureValue(servoMotors_totalTime_us / servoMotors_cycleTime_us);
	timer1_setCompareInterruptEnabled(1, true);
	//timer1_setCompareInterruptEnabled(2, true);
	timer1_setCaptureInterruptEnabled(true);
	timer1_start();
}

// Initialize Pins
static void servoMotors_initPins(struct Pin* pins) {
	u8 i;
	for (i = 0; i < servoMotors_motorsNumber; i++) {
		servoMotors_motors[i].pin.port = pins[i].port;
		servoMotors_motors[i].pin.pinNumber = pins[i].pinNumber;
		servoMotors_motors[i].minimumAngle = 0;
		servoMotors_motors[i].maximumAngle = 180;
		servoMotors_motors[i].centerAngle = 90;
		port_setPinDirection(&servoMotors_motors[i].pin, port_direction_output);
		servoMotors_setAngle(i, servoMotors_motors[i].centerAngle);
	}
}

// Initialize
void servoMotors_init(u8 frequency_MHz, struct Pin* pins) {
	servoMotors_initPins(pins);
	servoMotors_initTimer(frequency_MHz);
}

// Set Angle Range
void servoMotors_setAngleRange(u8 servoNumber, u8 minimumAngle, u8 maximumAngle) {
	if (minimumAngle > 180) {
		minimumAngle = 0;
	}
	if (maximumAngle > 180) {
		maximumAngle = 180;
	}
	servoMotors_motors[servoNumber].minimumAngle = minimumAngle;
	servoMotors_motors[servoNumber].maximumAngle = maximumAngle;
	servoMotors_motors[servoNumber].centerAngle = (minimumAngle + maximumAngle) / 2;
}

// Set Angle
void servoMotors_setAngle(u8 servoNumber, u8 angle) {
	float servoMotors_counts = (servoMotors_zeroTime_us + (float)angle * servoMotors_degreeTime_us) / servoMotors_cycleTime_us;
	timer1_setCompareValue(servoNumber + 1, (u16)servoMotors_counts);
	servoMotors_motors[servoNumber].currentAngle = angle;
}

// Move
void servoMotors_move(u8 servoNumber, u8 angle, u8 direction) {
	u8 newAngle;
	if (direction == servoMotors_direction_clockWise) {
		newAngle = servoMotors_motors[servoNumber].currentAngle - angle;
		if ((angle > servoMotors_motors[servoNumber].currentAngle) || (newAngle <= servoMotors_motors[servoNumber].minimumAngle)) {
			return;
		}
	} else if ((angle > _8bit_max - servoMotors_motors[servoNumber].currentAngle) || (direction == servoMotors_direction_counterClockWise)) {
		newAngle = servoMotors_motors[servoNumber].currentAngle + angle;
		if (newAngle >= servoMotors_motors[servoNumber].maximumAngle) {
			return;
		}
	}
	servoMotors_setAngle(servoNumber, newAngle);
}

// Flip
void servoMotors_flip(u8 servoNumber) {
	if (servoMotors_motors[servoNumber].currentAngle < servoMotors_motors[servoNumber].centerAngle) {
		servoMotors_setAngle(servoNumber, servoMotors_motors[servoNumber].minimumAngle);
	} else {
		servoMotors_setAngle(servoNumber, servoMotors_motors[servoNumber].maximumAngle);
	}
}

// Check Flags
void servoMotors_checkFlags() {
	u8 i;
	for (i = 0; i < servoMotors_motorsNumber; i++) {
		if (timer1_checkCompareFlag(i + 1)) {
			port_writePin(&servoMotors_motors[i].pin, low);
		}
	}
	if (timer1_checkCaptureFlag()) {
		for (i = 0; i < servoMotors_motorsNumber; i++) {
			port_writePin(&servoMotors_motors[i].pin, high);
		}
	}
}

// Timer Compare A Interrupt
ISR (TIMER1_COMPA_vect) {
	port_writePin(&servoMotors_motors[0].pin, low);
}

// Timer Compare B Interrupt
ISR (TIMER1_COMPB_vect) {
	port_writePin(&servoMotors_motors[1].pin, low);
}

// Timer Capture Interrupt
ISR (TIMER1_CAPT_vect) {
	port_writePin(&servoMotors_motors[0].pin, high);
	port_writePin(&servoMotors_motors[1].pin, high);
}