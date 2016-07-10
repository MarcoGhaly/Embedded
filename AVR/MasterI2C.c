#include "MasterI2C.h"

static u8 masterI2C_addresses[masterI2C_slavesNumber];
static u8 masterI2C_currentSlave = 0;
static enum boolean masterI2C_slaveActive = false;
static enum boolean masterI2C_transmissionComplete = true;
static u8 masterI2C_state;
static u8 masterI2C_mode;
static u8 masterI2C_data;

// Initialize Frequency
void masterI2C_init(u8 frequency_MHz, u16 I2CFrequency_KHz, u8* addresses) {
	u8 i;
	for (i = 0; i < masterI2C_slavesNumber; i++) {
		masterI2C_addresses[i] = addresses[i];
	}
	
	u16 masterI2C_SPIDividers[masterI2C_dividersNumber] = {1, 4, 16, 64};
	u16 divider = (u16)(frequency_MHz * 1000 / I2CFrequency_KHz);
	divider = (divider - 16) / 2;
	u8 minimum;
	u8 index = 0;
	for (i = 0; i < masterI2C_dividersNumber; i++) {
		if (divider / masterI2C_SPIDividers[i] > 0) {
			if ((i == 0) || (divider - masterI2C_SPIDividers[i] < minimum)) {
				minimum = divider - masterI2C_SPIDividers[i];
				index = i;
			}
		} else if ((i == 0) || (masterI2C_SPIDividers[i] - divider < minimum)) {
			minimum = masterI2C_SPIDividers[i] - divider;
			index = i;
		}
	}
	I2C_setDivider(index);
	I2C_setBitRate(divider / masterI2C_SPIDividers[index]);
	I2C_setInterruptEnabled(true);
	I2C_setEnabled(true);
}

// Activate
enum boolean masterI2C_activate(u8 slaveNumber) {
	if (masterI2C_slaveActive) {
		return false;
	}
	masterI2C_currentSlave = slaveNumber;
	masterI2C_slaveActive = true;
	return true;
}

// Deactivate
enum boolean masterI2C_deactivate(u8 slaveNumber) {
	if (!masterI2C_slaveActive || (masterI2C_currentSlave != slaveNumber)) {
		return false;
	}
	I2C_sendStopBit();
	masterI2C_slaveActive = false;
	return true;
}

// Is Transmission Complete
enum boolean masterI2C_isTransmissionComplete() {
	return masterI2C_transmissionComplete;
}

// Transmit Byte
void masterI2C_transmitByte(u8 data) {
	I2C_sendStartBit();
	I2C_setInterruptEnabled(true);
	masterI2C_state = masterI2C_state_startSent;
	masterI2C_mode = masterI2C_mode_write;
	masterI2C_transmissionComplete = false;
	masterI2C_data = data;
}

// Receive Byte
void masterI2C_receiveByte(enum boolean acknowledge) {
	I2C_setAcknowledgeBitEnabled(acknowledge);
	I2C_sendStartBit();
	I2C_setInterruptEnabled(true);
	masterI2C_state = masterI2C_state_startSent;
	masterI2C_mode = masterI2C_mode_read;
	masterI2C_transmissionComplete = false;
}

// Read Byte
u8 masterI2C_readByte() {
	return masterI2C_data;
}

// SPI Interrupt
ISR (TWI_vect) {
	if (masterI2C_state == masterI2C_state_startSent) {
		I2C_writeByte(masterI2C_addresses[masterI2C_currentSlave] | masterI2C_mode);
		masterI2C_state = masterI2C_state_addressSent;
	} else if (masterI2C_state == masterI2C_state_addressSent) {
		if (masterI2C_mode == masterI2C_mode_write) {
			I2C_writeByte(masterI2C_data);
		} else if (masterI2C_mode == masterI2C_mode_read) {
			I2C_receiveByte();
		}
		masterI2C_state = masterI2C_state_dataSent;
	} else {
		if (masterI2C_mode == masterI2C_mode_read) {
			masterI2C_data = I2C_readByte();
		}
		masterI2C_transmissionComplete = true;
		I2C_setInterruptEnabled(false);
	}
}