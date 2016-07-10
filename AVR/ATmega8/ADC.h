#ifndef ADC_H_
#define ADC_H_

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

void ADC_setReference(byte reference);
void ADC_setAdjustment(byte adjustment);
void ADC_setPrescaler(byte prescaler);
void ADC_enable();
void ADC_disable();
void ADC_start();
void ADC_enableInterrupt();
void ADC_disableInterrupt();
void ADC_setChannel(byte channelNumber);
word ADC_read();
byte ADC_checkFlag();

#endif /* ADC_H_ */