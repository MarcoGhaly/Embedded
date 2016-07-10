#ifndef USART_H_
#define USART_H_

#include <avr/io.h>
#include "Types.h"

#define USART_mode_asynchronous 0
#define USART_mode_synchronous 1

#define USART_parity_disabled 0
#define USART_parity_even 2
#define USART_parity_odd 3

#define USART_clockPolarity_sample_fallingEdge 0
#define USART_clockPolarity_sample_risingEdge 1

void USART_setTransmissionSpeedDoubled(enum boolean doubled);
void USART_setReceiverInterruptEnabled(enum boolean enabled);
void USART_setTransmitterInterruptEnabled(enum boolean enabled);
void USART_setTransmitterBufferEmptyInterruptEnabled(enum boolean enabled);
void USART_setReceiverEnabled(enum boolean enabled);
void USART_setTransmitterEnabled(enum boolean enabled);
u8 USART_getNinthReceiveBit();
void USART_setNinthTransmitBit(u8 ninthBit);
void USART_setMode(u8 mode);
void USART_setParity(u8 parity);
void USART_setStopBitsNumber(u8 bitsNumber);
void USART_setCharacterSize(u8 size);
void USART_setClockPolarity(u8 clockPolarity);
void USART_setBaudRate(u8 frequency_MHz, u32 baudRate);
void USART_write(u8 data);
u8 USART_read();
enum boolean USART_isReceiveComplete();
enum boolean USART_isTransmitComplete();
enum boolean USART_isTransmitBufferEmpty();

#endif /* USART_H_ */