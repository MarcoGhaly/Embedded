#ifndef USCI_SPI_B_H_
#define USCI_SPI_B_H_

#include <msp430.h>
#include "Types.h"
#include "Port.h"

#define usci_spi_clockFrequency 1048576

#define usci_spi_phase_change 0
#define usci_spi_phase_capture 1

#define usci_spi_polarity_low 0
#define usci_spi_polarity_high 1

#define usci_spi_dataDirection_LSBFirst 0
#define usci_spi_dataDirection_MSBFirst 1

#define usci_spi_dataLength_8 0
#define usci_spi_dataLength_7 1

#define usci_spi_mode_slave 0
#define usci_spi_mode_master 1

#define usci_spi_synchronousMode_3Pin 0
#define usci_spi_synchronousMode_4Pin_activeHigh 1
#define usci_spi_synchronousMode_4Pin_activeLow 2

#define usci_spi_clockSource_NA 0
#define usci_spi_clockSource_ACLK 1
#define usci_spi_clockSource_SMCLK 2
//#define usci_spi_clockSource_SMCLK 3

void usci_spi_init();
void usci_spi_setFirstEdgePhase(u8 spi_number, u8 phase);
void usci_spi_setInactivePolarity(u8 spi_number, u8 polarity);
void usci_spi_setDataDirection(u8 spi_number, u8 dataDirection);
void usci_spi_setDataLength(u8 spi_number, u8 dataLength);
void usci_spi_setMode(u8 spi_number, u8 mode);
void usci_spi_setSynchronousMode(u8 spi_number, u8 synchronousMode);
void usci_spi_setSynchronousModeEnabled(u8 spi_number, enum boolean enabled);
void usci_spi_setClockSource(u8 spi_number, u8 clockSource);
void usci_spi_setSoftwareResetEnabled(u8 spi_number, enum boolean enabled);
u8 usci_spi_isBusy(u8 spi_number);
void usci_spi_setBitRate(u8 spi_number, u32 bitRate);
void usci_spi_setTransmitInterruptEnabled(u8 spi_number, enum boolean enabled);
void usci_spi_setReceiveInterruptEnabled(u8 spi_number, enum boolean enabled);
u8 usci_spi_checkTransmitFlag(u8 spi_number);
u8 usci_spi_checkReceiveFlag(u8 spi_number);
u8 usci_spi_readByte(u8 spi_number);
void usci_spi_writeByte(u8 spi_number, u8 value);

#endif /* USCI_SPI_B_H_ */
