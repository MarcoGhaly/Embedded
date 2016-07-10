#ifndef TIMER2_H_
#define TIMER2_H_

#include <avr/io.h>
#include "Types.h"

#define timer2_mode_normal 0
#define timer2_mode_PWM_phaseCorrect 1
#define timer2_mode_CTC 2
#define timer2_mode_PWM_fast 3

#define timer2_divider_1 1
#define timer2_divider_8 2
#define timer2_divider_32 3
#define timer2_divider_64 4
#define timer2_divider_128 5
#define timer2_divider_256 6
#define timer2_divider_1024 7

void timer2_setMode(u8 mode);
void timer2_setDivider(u8 divider);
void timer2_start();
void timer2_stop();

void timer2_setCompareValue(u8 value);
void timer2_setCounterValue(u8 value);
u8 timer2_getCounterValue();


void timer2_setCompareInterruptEnabled(enum boolean enabled);
void timer2_setOverflowInterruptEnabled(enum boolean enabled);

enum boolean timer2_checkCompareFlag();
enum boolean timer2_checkOverFlowFlag();

#endif /* TIMER2_H_ */