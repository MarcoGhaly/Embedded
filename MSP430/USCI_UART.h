#ifndef USCI_UART_H_
#define USCI_UART_H_

#include <msp430.h>
#include <math.h>
#include "Types.h"
#include "Port.h"

#define usci_uart_clockFrequency 1048576

#define usci_uart_parity_odd 0
#define usci_uart_parity_even 1

#define usci_uart_firstBit_LSB 0
#define usci_uart_firstBit_MSB 1

#define usci_uart_dataBits_8 0
#define usci_uart_dataBits_7 1

#define usci_uart_stopBits_0 0
#define usci_uart_stopBits_1 1

#define usci_uart_mode_UART 0
#define usci_uart_mode_idleLineMultiprocessor 1
#define usci_uart_mode_addressBitMultiprocessor 2
#define usci_uart_mode_automaticBaudRateDetection 3

#define usci_uart_clockSource_UCLK 0
#define usci_uart_clockSource_ACLK 1
#define usci_uart_clockSource_SMCLK 2

void usci_uart_init();
void usci_uart_setParityEnabled(u8 UART_number, enum boolean enabled);
void usci_uart_setParity(u8 UART_number, u8 parity);
void usci_uart_setFirstBit(u8 UART_number, u8 firstBit);
void usci_uart_setDataLength(u8 UART_number, u8 dataLength);
void usci_uart_setStopBits(u8 UART_number, u8 stopBits);
void usci_uart_setMode(u8 UART_number, u8 mode);
void usci_uart_setSynchronousModeEnabled(u8 UART_number, enum boolean enabled);
void usci_uart_setClockSource(u8 UART_number, u8 clockSource);
void usci_uart_setSoftwareResetEnabled(u8 UART_number, enum boolean enabled);
void usci_uart_setOversamplingModeEnabled(u8 UART_number, enum boolean enabled);
u8 usci_uart_receiveByte(u8 UART_number);
void usci_uart_transmitByte(u8 UART_number, u8 data);
void usci_uart_setBaudRate(u8 UART_number, u32 baudRate);
u8 usci_uart_checkReceiveFlag(u8 UART_number);
u8 usci_uart_checkTransmitFlag(u8 UART_number);
void usci_uart_setReceiveInterruptEnabled(u8 UART_number, enum boolean enabled);
void usci_uart_setTransmitInterruptEnabled(u8 UART_number, enum boolean enabled);

#endif /* USCI_UART_H_ */
