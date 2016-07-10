#include "Analog.h"

static u16 analog_values[analog_channelsNumber];
static u8 analog_channelCounter = 0;

// Initialize
void analog_init(u8 frequency_MHz) {
	u16 analog_timer0Dividers[analog_dividersNumber] = {2, 4, 8, 16, 32, 64, 128};
	u16 divider = (u16)(frequency_MHz * 1000 / analog_intermediateFrequency_KHz);
	u8 i;
	for (i = 0; i < analog_dividersNumber; i++) {
		if (divider / analog_timer0Dividers[i] == 0) {
			break;
		}
	}
	ADC_setReference(ADC_AREF);
	ADC_setAdjustment(ADC_leftAdjusted);
	ADC_setDivider(i - 1);
	ADC_enableInterrupt();
	ADC_enable();
	ADC_start();
}

// Read Channel
u16 analog_readChannel(u8 channelNumber) {
	return analog_values[channelNumber];
}

// Update
static void analog_update() {
	ADC_start();
	analog_values[analog_channelCounter] = ADC_read();
	analog_channelCounter = (analog_channelCounter + 1) % analog_channelsNumber;
	ADC_setChannel((analog_channelCounter + 1) % analog_channelsNumber);
}

// Check Flag
u8 analog_checkFlag() {
	if (ADC_checkFlag()) {
		analog_update();
	}
}

// ADC Interrupt
ISR(ADC_vect) {
	analog_update();
}