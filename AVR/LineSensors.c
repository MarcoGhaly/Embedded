#include "LineSensors.h"

static u8 lineSensors_channelOffset;
static u8 lineSensors_sensorsNumber;

// Initialize
void lineSensors_init(u8 channelOffset, u8 sensorsNumber) {
	lineSensors_channelOffset = channelOffset;
	lineSensors_sensorsNumber = sensorsNumber;
}

// Read Color
u8 lineSensors_readColor(u8 sensorNumber) {
	if (analog_readChannel(sensorNumber + lineSensors_channelOffset) > lineSensors_colorThreshold) {
		return lineSensors_black;
	}
	return lineSensors_white;
}