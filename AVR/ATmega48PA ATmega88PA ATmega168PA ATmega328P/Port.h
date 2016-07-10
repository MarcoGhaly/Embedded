#ifndef PORT_H_
#define PORT_H_

#include <avr/io.h>
#include <math.h>
#include "Types.h"

#define port_firstPort 'D'
#define port_firstDirection DDRD
#define port_firstInput PIND
#define port_firstOutput PORTD

#define port_input 0
#define port_output 1

void port_setPortDirection(u8 port, u8 direction);
void port_setPinDirection(u8 port, u8 pinNumber, u8 direction);
void port_writePort(u8 port, u8 data);
void port_writePin(u8 port, u8 pinNumber, u8 value);
void port_togglePort(u8 port);
void port_togglePin(u8 port, u8 pinNumber);
u8 port_readPort(u8 port);
u8 port_readPin(u8 port, u8 pinNumber);

#endif /* PORT_H_ */