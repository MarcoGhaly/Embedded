#ifndef DCMOTORS_2_H_
#define DCMOTORS_2_H_

#include "Types.h"

#define DCMotors_forward 0
#define DCMotors_backward 1

#define DCMotors_left 0
#define DCMotors_right 1

#define DCMotors_number 2

#define DCMotors_totalCounts 8000

void DCMotors_init();
void DCMotors_setDirection(u8 motor, u8 direction);
void DCMotors_changeDirection(u8 motor);
void DCMotors_setRatio(u8 motor, u8 ratio);

#endif /* DCMOTORS_2_H_ */