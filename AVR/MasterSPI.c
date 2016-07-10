#include "MasterSPI.h"

static struct Slave masterSPI_slaves[masterSPI_slavesNumber];
static u8 masterSPI_currentSlave = 0;
static enum boolean masterSPI_slaveActive = false;
static enum boolean masterSPI_transmissionComplete = true;
static u8 masterSPI_data;

// Initialize Frequency
static void masterSPI_initFrequency(u8 mainFrequency_MHz, u16 SPIFrequency_KHz) {
	u16 masterSPI_SPIDividers[masterSPI_dividersNumber] = {4, 16, 64, 128, 2, 8, 32, 64};
	u16 divider = (u16)(mainFrequency_MHz * 1000 / SPIFrequency_KHz);
	u8 minimum;
	u8 index = 0;
	u8 i;
	for (i = 0; i < masterSPI_dividersNumber; i++) {
		if (divider / masterSPI_SPIDividers[i] > 0) {
			if ((i == 0) || (divider - masterSPI_SPIDividers[i] < minimum)) {
				minimum = divider - masterSPI_SPIDividers[i];
				index = i;
			}
		} else if ((i == 0) || (masterSPI_SPIDividers[i] - divider < minimum)) {
			minimum = masterSPI_SPIDividers[i] - divider;
			index = i;
		}
	}
	SPI_setDivider(index);
}

// Initialize
void masterSPI_init(u8 mainFrequency_MHz, u16 SPIFrequency_KHz, struct Pin* SS, struct Pin* MOSI, struct Pin* MISO, struct Pin* SCLK, struct Pin* slavesPins, u8* activeLevels) {
	port_setPinDirection(SS, port_direction_output);
	port_setPinDirection(MOSI, port_direction_output);
	port_setPinDirection(MISO, port_direction_input);
	port_setPinDirection(SCLK, port_direction_output);
	
	u8 i;
	for (i = 0; i < masterSPI_slavesNumber; i++) {
		masterSPI_slaves[i].pin.port = slavesPins[i].port;
		masterSPI_slaves[i].pin.pinNumber = slavesPins[i].pinNumber;
		masterSPI_slaves[i].activeLevel = activeLevels[i];
		port_setPinDirection(&slavesPins[i], port_direction_output);
		port_writePin(&slavesPins[i], (activeLevels[i] + 1) % 2);
	}
	
	masterSPI_initFrequency(mainFrequency_MHz, SPIFrequency_KHz);
	
	SPI_setInterruptEnabled(true);
	SPI_setMode(SPI_mode_master);
	SPI_setDataOrder(SPI_dataOrder_MSBFirst);
	SPI_setPolarity(SPI_polarity_idle_low);
	SPI_setPhase(SPI_phase_leadingEdge_sample);
	SPI_setEnabled(true);
}

// Activate
enum boolean masterSPI_activate(u8 slaveNumber) {
	if (masterSPI_slaveActive) {
		return false;
	}
	masterSPI_currentSlave = slaveNumber;
	masterSPI_slaveActive = true;
	port_writePin(&masterSPI_slaves[slaveNumber].pin, masterSPI_slaves[slaveNumber].activeLevel);
	return true;
}

// Deactivate
enum boolean masterSPI_deactivate(u8 slaveNumber) {
	if (!masterSPI_slaveActive || (masterSPI_currentSlave != slaveNumber)) {
		return false;
	}
	masterSPI_slaveActive = false;
	port_writePin(&masterSPI_slaves[slaveNumber].pin, (masterSPI_slaves[slaveNumber].activeLevel + 1) % 2);
	return true;
}

// Is Transmission Complete
enum boolean masterSPI_isTransmissionComplete() {
	return masterSPI_transmissionComplete;
}

// Transmit Byte
void masterSPI_transmitByte(u8 data) {
	SPI_writeByte(data);
	masterSPI_transmissionComplete = false;
}

// Read Byte
u8 masterSPI_readByte() {
	return masterSPI_data;
}

// SPI Interrupt
ISR (SPI_STC_vect) {
	masterSPI_data = SPI_readByte();
	masterSPI_transmissionComplete = true;
}