#ifndef ULTRASONICSENSORS_H_
#define ULTRASONICSENSORS_H_

#include <avr/interrupt.h>
#include <math.h>
#include "Types.h"
#include "WDT.h"
#include "Port.h"
#include "Timer1.h"
#include "INT.h"

// Intermediate Frequency 1 MHz (1 Cycle / us)
#define ultraSonicSensors_intermediateFrequency_KHz 1000
#define ultraSonicSensors_dividersNumber 5

#define ultraSonicSensors_sensorsNumber 4
#define ultraSonicSensors_selectPinsNumber 2

#define ultraSonicSensors_triggerDelay_us 15
#define ultraSonicSensors_soundSpeed_Cm_us 0.034

static void ultraSonicSensors_initTimer(u8 frequency_MHz);
void ultraSonicSensors_initPins(struct Pin* selectPins, struct Pin* echoPin, struct Pin* triggerPins);
void ultraSonicSensors_init(u8 frequency_MHz, u16 maxDistance, struct Pin* selectPins, struct Pin* echoPin, struct Pin* triggerPins);
static void ultraSonicSensors_start();
u16 ultraSonicSensors_getValue_cm(u8 SensorNumber);
static void ultraSonicSensors_selectSensor(u8 SensorNumber);

#endif /* ULTRASONICSENSORS_H_ */