#ifndef ADC10_H_
#define ADC10_H_

#include <msp430.h>
#include "Types.h"
#include "Port.h"

#define adc10_samplingTime_4CLKs 0
#define adc10_samplingTime_8CLKs 1
#define adc10_samplingTime_16CLKs 2
#define adc10_samplingTime_64CLKs 3

#define adc10_samplingRate_200KSPS 0
#define adc10_samplingRate_50KSPS 1

#define adc10_referenceBurst_continuous 0
#define adc10_referenceBurst_duringConversion 1

#define adc10_referenceVoltage_1_5V 0
#define adc10_referenceVoltage_2_5V 1

#define adc10_SamplingTriggerSource_ADC10SC 0
#define adc10_SamplingTriggerSource_TimerA_OUT1 1
#define adc10_SamplingTriggerSource_TimerA_OUT0 2
#define adc10_SamplingTriggerSource_TimerA_OUT2 3

#define adc10_dataFormat_StraightBinary 0
#define adc10_dataFormat_2sComplement 1

#define adc10_clockSource_ADC10OSC 0
#define adc10_clockSource_ACLK 1
#define adc10_clockSource_MCLK 2
#define adc10_clockSource_SMCLK 3

#define adc10_conversionMode_Single 0
#define adc10_conversionMode_Sequence 1
#define adc10_conversionMode_RepeatedSingle 2
#define adc10_conversionMode_RepeatedSequence 3

void adc10_setSampleTime(u8 samplingTime);
void adc10_setMaximumSamplingRate(u8 samplingRate);
void adc10_setReferenceOutputEnabled(enum boolean enabled);
void adc10_setReferenceBurst(u8 referenceBurst);
void adc10_setMultipleconversionEnabled(enum boolean enabled);
void adc10_setReferenceVoltage(u8 referenceVoltage);
void adc10_setReferenceGeneratorEnabled(enum boolean enabled);
void adc10_setEnabled(enum boolean enabled);
void adc10_setInterruptEnabled(enum boolean enabled);
enum boolean adc10_isConversionFinished();
void adc10_setConversionEnabled(enum boolean enabled);
void adc10_startConversion();
void adc10_setInputChannel(u8 channelNumber);
void adc10_setSamplingTriggerSource(u8 triggerSource);
void adc10_setDataFormat(u8 dataFormat);
void adc10_setSampleSignalInverted(enum boolean enable);
void adc10_setClockDivider(u8 clockDivider);
void adc10_setClockSource(u8 clockSource);
void adc10_setConversionMode(u8 conversionMode);
enum boolean adc10_isBusy();
u16 adc10_getConversionResult();

#endif /* ADC10_H_ */
