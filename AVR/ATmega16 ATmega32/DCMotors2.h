#ifndef DCMOTORS2_H_
#define DCMOTORS2_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Types.h"
#include "Timer1.h"
#include "Port.h"

struct Motor {
	struct Pin pins[2];
	u8 selectedPin;
};

// Intermediate Frequency 100 KHz (100 Cycle / 1ms)
#define DCMotors_intermediateFrequency_KHz 100
#define DCMotors_frequnciesNumber 5

#define DCMotors_motorsNumber 2

#define DCMotors_forward 0
#define DCMotors_backward 1

static void DCMotors_initTimer(u8 frequency_MHz);
static void DCMotors_initPins(struct Pin (*pins)[2]);
void DCMotors_init(u8 frequency_MHz, struct Pin (*pins)[2]);
void DCMotors_setDirection(u8 motorNumber, u8 direction);
void DCMotors_changeDirection(u8 motorNumber);
void DCMotors_setRatio(u8 motorNumber, u8 ratio);

#endif /* DCMOTORS2_H_ */