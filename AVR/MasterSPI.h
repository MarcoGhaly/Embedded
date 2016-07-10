#ifndef MASTERSPI_H_
#define MASTERSPI_H_

#include <avr/interrupt.h>
#include "Types.h"
#include "SPI.h"
#include "Port.h"

struct Slave {
	struct Pin pin;
	u8 activeLevel;
};

#define masterSPI_slavesNumber 1
#define masterSPI_dividersNumber 8

static void masterSPI_initFrequency(u8 mainFrequency_MHz, u16 SPIFrequency_KHz);
void masterSPI_init(u8 mainFrequency_MHz, u16 SPIFrequency_KHz, struct Pin* SS, struct Pin* MOSI, struct Pin* MISO, struct Pin* SCLK, struct Pin* slavesPins, u8* activeLevels);
enum boolean masterSPI_activate(u8 slaveNumber);
enum boolean masterSPI_deactivate(u8 slaveNumber);
enum boolean masterSPI_isTransmissionComplete();
void masterSPI_transmitByte(u8 data);
u8 masterSPI_readByte();

#endif /* MASTERSPI_H_ */