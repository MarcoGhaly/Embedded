#include "CurrentSensors.h"

static u8 currentSensors_channelOffset;
static u8 currentSensors_sensorsNumber;

// Initialize
void currentSensors_init(u8 channelOffset, u8 sensorsNumber) {
	currentSensors_channelOffset = channelOffset;
	currentSensors_sensorsNumber = sensorsNumber;
}

// Read Current
float currentSensors_readCurrent_A(u8 sensorNumber) {
	float outVolt = (float)analog_readChannel(sensorNumber + currentSensors_channelOffset) * 5 / 1024;
	return (outVolt * 5 - (float)12.5);	//	current = output_volt * 5 - 12.5;
}