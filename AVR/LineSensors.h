#ifndef LINESENSORS_H_
#define LINESENSORS_H_

#include "Types.h"
#include "Analog.h"

#define lineSensors_black 0
#define lineSensors_white 1

#define lineSensors_colorThreshold 350

void lineSensors_init(u8 channelOffset, u8 sensorsNumber);
u8 lineSensors_readColor(u8 sensorNumber);

#endif /* LINESENSORS_H_ */