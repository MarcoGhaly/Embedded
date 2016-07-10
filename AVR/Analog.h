#ifndef ANALOG_H_
#define ANALOG_H_

#include <avr/interrupt.h>
#include "Types.h"
#include "ADC.h"

// Intermediate Frequency 125 KHz (50 KHz ~ 200 KHz)
#define analog_intermediateFrequency_KHz 125
#define analog_dividersNumber 7

#define analog_channelsNumber 8

void analog_init(u8 frequency_MHz);
u16 analog_readChannel(u8 channelNumber);
static void analog_update();
u8 analog_checkFlag();

#endif /* ANALOG_H_ */