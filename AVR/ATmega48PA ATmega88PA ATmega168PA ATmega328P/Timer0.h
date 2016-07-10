#ifndef TIMER0_H_
#define TIMER0_H_

#include "Types.h"

#define timer0_normal 0
#define timer0_PWM_phaseCorrect 1
#define timer0_CTC 2
#define timer0_PWM_fast 3

#define timer0_clock_1 1
#define timer0_clock_8 2
#define timer0_clock_64 3
#define timer0_clock_256 4
#define timer0_clock_1024 5
#define timer0_clock_ext_falling_T0 6
#define timer0_clock_ext_rising_T0 7

void timer0_setMode(u8 mode);
void timer0_setPrescaler(u8 prescaler);
void timer0_start();
void timer0_stop();

void timer0_setCompareValue(u8 compareNumber, u16 value);
void timer0_setCounterValue(u8 value);

void timer0_setCompareInterruptEnabled(u8 compareNumber, enum boolean enabled);
void timer0_setOverflowInterruptEnabled(enum boolean enabled);

u8 timer0_checkCompareFlag(u8 compareNumber);
u8 timer0_checkOverFlowFlag();

#endif /* TIMER0_H_ */