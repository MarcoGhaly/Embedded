#include <avr/io.h>
#include "Types.h"
#include "ADC.h"

void ADC_setReference(byte reference) {
	ADMUX &= ~(0x03 << REFS0);
	ADMUX |= (reference << REFS0);
}

void ADC_setAdjustment(byte adjustment) {
	ADMUX &= ~(1 << ADLAR);
	ADMUX |= (adjustment << ADLAR);
}

void ADC_setPrescaler(byte prescaler) {
	ADCSRA &= ~(0x07);
	ADCSRA |= prescaler;
}

void ADC_enable() {
	ADCSRA |= (1 << ADEN);
}

void ADC_disable() {
	ADCSRA &= ~(1 << ADEN);
}

void ADC_start() {
	ADCSRA |= (1 << ADSC);
}

void ADC_enableInterrupt() {
	ADCSRA |= (1 << ADIE);
}

void ADC_disableInterrupt() {
	ADCSRA &= ~(1 << ADIE);
}

void ADC_setChannel(byte channelNumber) {
	ADMUX &= 0xE0;
	ADMUX |= channelNumber;
}

word ADC_read() {
	word digitalValue = ADCL;
	word highValue = ADCH;
	digitalValue |= (highValue << 8);
	return digitalValue;
}

byte ADC_checkFlag() {
	if (ADCSRA & (1 << ADIF)) {
		ADCSRA |= (1 << ADIF);
		return 1;
	}
	return 0;
}