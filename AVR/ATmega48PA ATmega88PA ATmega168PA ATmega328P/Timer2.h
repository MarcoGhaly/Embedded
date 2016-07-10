#ifndef TIMER2_H_
#define TIMER2_H_

#include "Types.h"

#define timer2_normal 0
#define timer2_PWM_phaseCorrect 1
#define timer2_CTC 2
#define timer2_PWM_fast 3

#define timer2_clock_1 1
#define timer2_clock_8 2
#define timer2_clock_32 3
#define timer2_clock_64 4
#define timer2_clock_128 5
#define timer2_clock_256 6
#define timer2_clock_1024 7

void timer2_setMode(u8 mode);
void timer2_setPrescaler(u8 prescaler);
void timer2_start();
void timer2_stop();

void timer2_setCompareValue(u8 compareNumber, u16 value);
void timer2_setCounterValue(u8 value);

void timer2_setCompareInterruptEnabled(u8 compareNumber, enum boolean enabled);
void timer2_setOverflowInterruptEnabled(enum boolean enabled);

u8 timer2_checkCompareFlag(u8 compareNumber);
u8 timer2_checkOverFlowFlag();

#endif /* TIMER2_H_ */