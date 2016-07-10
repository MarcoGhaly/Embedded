#ifndef TIMER0_H_
#define TIMER0_H_

#include <avr/io.h>
#include "Types.h"

#define timer0_mode_normal 0
#define timer0_mode_PWM_phaseCorrect 1
#define timer0_mode_CTC 2
#define timer0_mode_PWM_fast 3

#define timer0_divider_1 1
#define timer0_divider_8 2
#define timer0_divider_64 3
#define timer0_divider_256 4
#define timer0_divider_1024 5
#define timer0_divider_ext_falling_T0 6
#define timer0_divider_ext_rising_T0 7

void timer0_setMode(u8 mode);
void timer0_setDivider(u8 divider);
void timer0_start();
void timer0_stop();

void timer0_setCompareValue(u8 value);
void timer0_setCounterValue(u8 value);
u8 timer0_getCounterValue();

void timer0_setCompareInterruptEnabled(enum boolean enabled);
void timer0_setOverflowInterruptEnabled(enum boolean enabled);

enum boolean timer0_checkCompareFlag();
enum boolean timer0_checkOverFlowFlag();

#endif /* TIMER0_H_ */