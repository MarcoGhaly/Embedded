#ifndef SPEEDOMETER_H_
#define SPEEDOMETER_H_

#include <avr/interrupt.h>
#include "Types.h"
#include "Timer0.h"
#include "Analog.h"

// Intermediate Frequency 1 MHz (1 Cycle / us)
#define speedoMeter_intermediateFrequency_KHz 1000
#define speedoMeter_dividersNumber 5

#define speedoMeter_state_blocked 0
#define speedoMeter_state_free 1

#define speedoMeter_threshold_blocked 200
#define speedoMeter_threshold_free 700

#define speedoMeter_maxPendingTime_s 1

static void speedoMeter_initTimer(u8 frequency_MHz);
void speedoMeter_init(u8 frequency_MHz, u8 channelNumber, u8 unitDistance_cm);
u16 speedoMeter_getDistance();
u16 speedoMeter_getSpeed();
void speedoMeter_reset();
void speedoMeter_read();

#endif /* SPEEDOMETER_H_ */