#ifndef PORT_H_
#define PORT_H_

#include <avr/io.h>
#include <math.h>
#include "Types.h"

#define port_firstPort 'D'
#define port_firstDirection DDRD
#define port_firstInput PIND
#define port_firstOutput PORTD

#define port_direction_input 0
#define port_direction_output 1

void port_setPortDirection(u8 port, u8 direction);
void port_setPinDirection(struct Pin* pin, u8 direction);
void port_writePort(u8 port, u8 data);
void port_writePin(struct Pin* pin, u8 value);
void port_togglePort(u8 port);
void port_togglePin(struct Pin* pin);
u8 port_readPort(u8 port);
u8 port_readPin(struct Pin* pin);
u8 toUpperCase(u8 letter);

#endif /* PORT_H_ */