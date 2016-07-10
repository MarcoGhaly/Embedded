#include "ADC10.h"

void adc10_setSampleTime(u8 samplingTime) {
	ADC10CTL0 &= ~(0x03 < 11);
	ADC10CTL0 |= (samplingTime < 11);
}

void adc10_setMaximumSamplingRate(u8 samplingRate) {
	ADC10CTL0 &= ~(1 << 10);
	ADC10CTL0 |= (samplingRate << 10);
}

void adc10_setReferenceOutputEnabled(enum boolean enabled) {
	if (enabled) {
		ADC10CTL0 |= (1 << 9);
	} else {
		ADC10CTL0 &= ~(1 << 9);
	}
}

void adc10_setReferenceBurst(u8 referenceBurst) {
	ADC10CTL0 &= ~(1 << 8);
	ADC10CTL0 |= (referenceBurst << 8);
}

void adc10_setMultipleconversionEnabled(enum boolean enabled) {
	if (enabled) {
		ADC10CTL0 |= (1 << 7);
	} else {
		ADC10CTL0 &= ~(1 << 7);
	}
}

void adc10_setReferenceVoltage(u8 referenceVoltage) {
	ADC10CTL0 &= ~(1 << 6);
	ADC10CTL0 |= (referenceVoltage << 6);
}

void adc10_setReferenceGeneratorEnabled(enum boolean enabled) {
	if (enabled) {
		ADC10CTL0 |= (1 << 5);
	} else {
		ADC10CTL0 &= ~(1 << 5);
	}
}

void adc10_setEnabled(enum boolean enabled) {
	if (enabled) {
		ADC10CTL0 |= (1 << 4);
	} else {
		ADC10CTL0 &= ~(1 << 4);
	}
}

void adc10_setInterruptEnabled(enum boolean enabled) {
	if (enabled) {
		ADC10CTL0 |= (1 << 3);
	} else {
		ADC10CTL0 &= ~(1 << 3);
	}
}

enum boolean adc10_isConversionFinished() {
	if (ADC10CTL0 & (1 << 2)) {
		ADC10CTL0 &= ~(1 << 2);
		return true;
	}
	return false;
}

void adc10_setConversionEnabled(enum boolean enabled) {
	if (enabled) {
		ADC10CTL0 |= (1 << 1);
	} else {
		ADC10CTL0 &= ~(1 << 1);
	}
}

void adc10_startConversion() {
	ADC10CTL0 |= (1 << 1) | (1 << 0);
}

void adc10_setInputChannel(u8 channelNumber) {
	ADC10CTL1 &= ~(0x0F << 12);
	ADC10CTL1 |= (channelNumber << 12);
	ADC10AE0 = (1 << channelNumber);
//	if (channelNumber > 7) {
//		ADC10AE1 = (1 << (channelNumber - 8) );
//	}
}

void adc10_setSamplingTriggerSource(u8 triggerSource) {
	ADC10CTL1 &= ~(0x03 << 10);
	ADC10CTL1 |= (triggerSource << 10);
}

void adc10_setDataFormat(u8 dataFormat) {
	ADC10CTL1 &= ~(1 << 9);
	ADC10CTL1 |= (dataFormat << 9);
}

void adc10_setSampleSignalInverted(enum boolean enable) {
	if (enable) {
		ADC10CTL1 |= (1 << 8);
	} else {
		ADC10CTL1 &= ~(1 << 8);
	}
}

void adc10_setClockDivider(u8 clockDivider) {
	ADC10CTL1 &= ~(0x07 << 5);
	ADC10CTL1 |= ((clockDivider - 1) << 5);
}

void adc10_setClockSource(u8 clockSource) {
	ADC10CTL1 &= ~(0x03 << 3);
	ADC10CTL1 |= (clockSource << 3);
}

void adc10_setConversionMode(u8 conversionMode) {
	ADC10CTL1 &= ~(0x03 << 1);
	ADC10CTL1 |= (conversionMode << 1);
}

enum boolean adc10_isBusy() {
	if (ADC10CTL1 & (1 << 0)) {
		return true;
	}
	return false;
}

u16 adc10_getConversionResult() {
	return ADC10MEM;
}
