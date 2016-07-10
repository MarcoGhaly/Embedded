#ifndef TIMER0_H_
#define TIMER0_H_

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

void timer0_setPrescaler(byte prescaler);
void timer0_setCounterValue(byte value);
byte timer0_getCounterValue();
void timer0_start();
void timer0_stop();
void timer0_enableOverFlowInterrupt();
void timer0_disableOverFlowInterrupt();
byte timer0_checkOverFlowFlag();

#endif /* TIMER0_H_ */