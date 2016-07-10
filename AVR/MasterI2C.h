#ifndef MASTERI2C_H_
#define MASTERI2C_H_

#include <avr/interrupt.h>
#include "Types.h"
#include "I2C.h"

#define masterI2C_state_startSent 0
#define masterI2C_state_addressSent 1
#define masterI2C_state_dataSent 2

#define masterI2C_mode_write 0
#define masterI2C_mode_read 1

#define masterI2C_slavesNumber 1
#define masterI2C_dividersNumber 4

void masterI2C_init(u8 frequency_MHz, u16 I2CFrequency_KHz, u8* addresses);
enum boolean masterI2C_activate(u8 slaveNumber);
enum boolean masterI2C_deactivate(u8 slaveNumber);
enum boolean masterI2C_isTransmissionComplete();
void masterI2C_transmitByte(u8 data);
void masterI2C_receiveByte(enum boolean acknowledge);
u8 masterI2C_readByte();

#endif /* MASTERI2C_H_ */