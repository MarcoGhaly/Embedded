#ifndef CURRENTSENSORS_H_
#define CURRENTSENSORS_H_

#include "Types.h"
#include "Analog.h"

void currentSensors_init(u8 channelOffset, u8 sensorsNumber);
float currentSensors_readCurrent_A(u8 sensorNumber);

#endif /* CURRENTSENSORS_H_ */