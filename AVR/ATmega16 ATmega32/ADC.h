#ifndef ADC_H_
#define ADC_H_

#include "Types.h"

#define ADC_AREF 0
#define ADC_AVCC 1
#define ADC_reversed 2
#define ADC_internal 3

#define ADC_leftAdjusted 0
#define ADC_rightAdjusted 1

#define ADC_clock_2 1
#define ADC_clock_4 2
#define ADC_clock_8 3
#define ADC_clock_16 4
#define ADC_clock_32 5
#define ADC_clock_64 6
#define ADC_clock_128 7

#define ADC_freeRunningMode 0
#define ADC_analogComparator 1
#define ADC_externalInterruptRequest0 2
#define ADC_timer0CompareMatch 3
#define ADC_timer0Overflow 4
#define ADC_timer1CompareMatchB 5
#define ADC_timer1Overflow 6
#define ADC_timer1CaptureEvent 7

void ADC_setReference(u8 reference);
void ADC_setAdjustment(u8 adjustment);
void ADC_setDivider(u8 prescaler);
void ADC_enableAutoTrigger();
void ADC_disableAutoTrigger();
void ADC_setMode(u8 mode);
void ADC_enable();
void ADC_disable();
void ADC_start();
void ADC_enableInterrupt();
void ADC_disableInterrupt();
void ADC_setChannel(u8 channelNumber);
u16 ADC_read();
u8 ADC_checkFlag();

#endif /* ADC_H_ */