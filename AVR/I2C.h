#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>
#include "Types.h"

#define I2C_divider_1 0
#define I2C_divider_4 1
#define I2C_divider_16 2
#define I2C_divider_64 3

#define I2C_status_master_startBitTransmitted 0x08
#define I2C_status_master_acknowledgeToWriteReceived 0x18
#define I2C_status_master_acknowledgeToWriteNotReceived 0x20

void I2C_setBitRate(u8 bitRate);
static void I2C_startOperation();
void I2C_setAcknowledgeBitEnabled(enum boolean enabled);
void I2C_sendStartBit();
void I2C_sendStopBit();
void I2C_setEnabled(enum boolean enabled);
void I2C_setInterruptEnabled(enum boolean enabled);
void I2C_setDivider(u8 divider);
void I2C_writeByte(u8 data);
void I2C_receiveByte();
u8 I2C_readByte();
enum boolean I2C_checkFlag();
u8 I2C_getStatus();
void I2C_setSlaveAddress(u8 address);

#endif /* I2C_H_ */