#include <avr/io.h>
#include "ADC.h"

void ADC_setReference(u8 reference) {
	ADMUX &= ~(0x03 << REFS0);
	ADMUX |= (reference << REFS0);
}

void ADC_setAdjustment(u8 adjustment) {
	ADMUX &= ~(1 << ADLAR);
	ADMUX |= (adjustment << ADLAR);
}

void ADC_setDivider(u8 prescaler) {
	ADCSRA &= ~(0x07);
	ADCSRA |= prescaler;
}

void ADC_enableAutoTrigger() {
	ADCSRA |= (1 << ADATE);
}

void ADC_disableAutoTrigger() {
	ADCSRA &= ~(1 << ADATE);
}

void ADC_setMode(u8 mode) {
	SFIOR &= ~(0x07 << ADTS0);
	SFIOR |= (mode << ADTS0);
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

void ADC_setChannel(u8 channelNumber) {
	ADMUX &= 0xE0;
	ADMUX |= channelNumber;
}

u16 ADC_read() {
	u16 digitalValue = ADCL;
	u16 highValue = ADCH;
	digitalValue |= (highValue << 8);
	return digitalValue;
}

u8 ADC_checkFlag() {
	if (ADCSRA & (1 << ADIF)) {
		ADCSRA |= (1 << ADIF);
		return 1;
	}
	return 0;
}