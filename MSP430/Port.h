#ifndef PORT_H_
#define PORT_H_

#include <msp430.h>
#include "Types.h"

#define port_portsNumber 4
#define port_interruptsNumber 2

#define port_direction_input 0
#define port_direction_output 1

#define port_function_IO 0
#define port_function_primaryPeripheral 1
#define port_function_secondaryPeripheral 3

#define port_edge_rising 0
#define port_edge_falling 1

void port_setPortDirection(u8 portNumber, u8 direction);
void port_setPinDirection(u8 portNumber, u8 pinNumber, u8 direction);
void port_writePort(u8 portNumber, u8 data);
void port_writePin(u8 portNumber, u8 pinNumber, u8 value);
void port_togglePort(u8 portNumber);
void port_togglePin(u8 portNumber, u8 pinNumber);
u8 port_readPort(u8 portNumber);
u8 port_readPin(u8 portNumber, u8 pinNumber);
void port_setPinFunction(u8 portNumber, u8 pinNumber, u8 function);
void port_setPortResistorEnabled(u8 portNumber, enum boolean enabled);
void port_setPinResistorEnabled(u8 portNumber, u8 pinNumber, enum boolean enabled);
void port_setPortInterruptEnabled(u8 portNumber, enum boolean enabled);
void port_setPinInterruptEnabled(u8 portNumber, u8 pinNumber, enum boolean enabled);
void port_setPortInterruptEdge(u8 portNumber, u8 edge);
void port_setPinInterruptEdge(u8 portNumber, u8 pinNumber, u8 edge);

#endif /* PORT_H_ */
