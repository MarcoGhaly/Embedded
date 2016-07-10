#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include "Types.h"
#include "Port.h"

#define SPI_dataOrder_MSBFirst 0
#define SPI_dataOrder_LSBFirst 1

#define SPI_mode_slave 0
#define SPI_mode_master 1

#define SPI_polarity_idle_low 0
#define SPI_polarity_idle_high 1

#define SPI_phase_leadingEdge_sample 0
#define SPI_phase_leadingEdge_setup 1

#define SPI_divider_4 0
#define SPI_divider_16 1
#define SPI_divider_64 2
#define SPI_divider_128 3
#define SPI_divider_2 4
#define SPI_divider_8 5
#define SPI_divider_32 6
#define SPI_divider_64 7

void SPI_setInterruptEnabled(enum boolean enabled);
void SPI_setEnabled(enum boolean enabled);
void SPI_setDataOrder(u8 dataOrder);
void SPI_setMode(u8 mode);
void SPI_setPolarity(u8 polarity);
void SPI_setPhase(u8 phase);
void SPI_setDivider(u8 divider);
void SPI_writeByte(u8 data);
u8 SPI_readByte();
u8 SPI_checkFlag();

#endif /* SPI_H_ */