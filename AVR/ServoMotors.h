#ifndef SERVOMOTORS_H_
#define SERVOMOTORS_H_

#include <avr/interrupt.h>
#include "Types.h"
#include "Port.h"
#include "Timer1.h"

struct ServoMotor {
	struct Pin pin;
	u8 minimumAngle;
	u8 maximumAngle;
	u8 centerAngle;
	u8 currentAngle;
};

// Intermediate Frequency 1 MHz (1 Cycle / us)
#define servoMotors_intermediateFrequency_KHz 1000
#define servoMotors_frequnciesNumber 5

#define servoMotors_motorsNumber 2

#define servoMotors_degreeTime_us 5.56f
#define servoMotors_zeroTime_us 1000.0f
#define servoMotors_totalTime_us 20000.0f

#define servoMotors_direction_clockWise 0
#define servoMotors_direction_counterClockWise 1

static void servoMotors_initTimer(u8 frequency_MHz);
static void servoMotors_initPins(struct Pin* pins);
void servoMotors_init(u8 frequency_MHz, struct Pin* pins);
void servoMotors_setAngleRange(u8 servoNumber, u8 minimumAngle, u8 maximumAngle);
void servoMotors_setAngle(u8 servoNumber, u8 angle);
void servoMotors_move(u8 servoNumber, u8 angle, u8 direction);
void servoMotors_flip(u8 servoNumber);
void servoMotors_checkFlags();


#endif /* SERVOMOTORS_H_ */