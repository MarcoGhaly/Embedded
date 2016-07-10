#ifndef timer1_H_
#define timer1_H_

#include <avr/io.h>
#include "Types.h"

#define timer1_mode_normal 0
#define timer1_mode_PWM_phaseCorrect_8 1
#define timer1_mode_PWM_phaseCorrect_9 2
#define timer1_mode_PWM_phaseCorrect_10 3
#define timer1_mode_CTC_OCR1A 4
#define timer1_mode_PWM_fast_8 5
#define timer1_mode_PWM_fast_9 6
#define timer1_mode_PWM_fast_10 7
#define timer1_mode_PWM_phaseFrequencyCorrect_ICR1 8
#define timer1_mode_PWM_phaseFrequencyCorrect_OCR1A 9
#define timer1_mode_PWM_phaseCorrect_ICR1 10
#define timer1_mode_PWM_phaseCorrect_OCR1A 11
#define timer1_mode_CTC_ICR1 12
#define timer1_mode_PWM_fast_ICR1 14
#define timer1_mode_PWM_fast_OCR1A 15

#define timer1_divider_1 1
#define timer1_divider_8 2
#define timer1_divider_64 3
#define timer1_divider_256 4
#define timer1_divider_1024 5
#define timer1_divider_ext_falling_T1 6
#define timer1_divider_ext_rising_T1 7

void timer1_setMode(u8 mode);
void timer1_setDivider(u8 divider);
void timer1_start();
void timer1_stop();

void timer1_setCompareValue(u8 compareNumber, u16 value);
void timer1_setCaptureValue(u16 value);
u16 timer1_getCaptureValue();
void timer1_setCounterValue(u16 value);
u16 timer1_getCounterValue();

void timer1_setCompareInterruptEnabled(u8 compareNumber, enum boolean enabled);
void timer1_setCaptureInterruptEnabled(enum boolean enabled);
void timer1_setOverflowInterruptEnabled(enum boolean enabled);

enum boolean timer1_checkCompareFlag(u8 compareNumber);
enum boolean timer1_checkCaptureFlag();
enum boolean timer1_checkOverFlowFlag();

#endif /* timer1_H_ */