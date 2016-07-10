#ifndef TIMER3_H_
#define TIMER3_H_

#include "Types.h"

#define timer3_normal 0
#define timer3_PWM_phaseCorrect_8 1
#define timer3_PWM_phaseCorrect_9 2
#define timer3_PWM_phaseCorrect_10 3
#define timer3_CTC_OCR1A 4
#define timer3_PWM_fast_8 5
#define timer3_PWM_fast_9 6
#define timer3_PWM_fast_10 7
#define timer3_PWM_phaseFrequencyCorrect_ICR1 8
#define timer3_PWM_phaseFrequencyCorrect_OCR1A 9
#define timer3_PWM_phaseCorrect_ICR1 10
#define timer3_PWM_phaseCorrect_OCR1A 11
#define timer3_CTC_ICR1 12
#define timer3_PWM_fast_ICR1 14
#define timer3_PWM_fast_OCR1A 15

#define timer3_clock_1 1
#define timer3_clock_8 2
#define timer3_clock_64 3
#define timer3_clock_256 4
#define timer3_clock_1024 5
#define timer3_clock_ext_falling_T1 6
#define timer3_clock_ext_rising_T1 7

void timer3_setMode(u8 mode);
void timer3_setPrescaler(u8 prescaler);
void timer3_start();
void timer3_stop();

void timer3_setCompareValue(u8 compareNumber, u16 value);
void timer3_setCaptureValue(u16 value);
u16 timer3_getCaptureValue();
void timer3_setCounterValue(u16 value);
u16 timer3_getCounterValue();

void timer3_setCompareInterruptEnabled(u8 compareNumber, enum boolean enabled);
void timer3_setCaptureInterruptEnabled(enum boolean enabled);
void timer3_setOverflowInterruptEnabled(enum boolean enabled);

u8 timer3_checkCompareFlag(u8 compareNumber);
u8 timer3_checkCaptureFlag();
u8 timer3_checkOverFlowFlag();

#endif /* TIMER3_H_ */