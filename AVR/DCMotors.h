#ifndef DCMOTORS_H_
#define DCMOTORS_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Types.h"
#include "Timer0.h"
#include "Port.h"

struct Motor {
	struct Pin pins[2];
	u8 selectedPin;
	enum boolean enable;
	u8 counts;
};

// Intermediate Frequency 1280 KHz (128 Cycle / 100us)
#define DCMotors_intermediateFrequency_KHz 1280
#define DCMotors_frequnciesNumber 5
#define DCMotors_totalCounts 10

#define DCMotors_motorsNumber 2

#define DCMotors_forward 0
#define DCMotors_backward 1

static void DCMotors_initTimer(u8 frequency_MHz);
static void DCMotors_initPins(struct Pin (*pins)[2]);
void DCMotors_init(u8 frequency_MHz, struct Pin (*pins)[2]);
void DCMotors_setDirection(u8 motorNumber, u8 direction);
void DCMotors_changeDirection(u8 motorNumber);
void DCMotors_setRatio(u8 motorNumber, u8 ratio);
static void DCMotors_toggle();
void DCMotors_checkFlags();

#endif /* DCMOTORS_H_ */