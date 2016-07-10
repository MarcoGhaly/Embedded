#include "Port.h"

void port_setPortDirection(u8 port, u8 direction) {
	u8* ptr = &port_firstDirection - 3 * (u8) fabs(port_firstPort - port);
    *ptr = _8bit_max * direction;
}

void port_setPinDirection(u8 port, u8 pinNumber, u8 direction) {
	u8* ptr = &port_firstDirection - 3 * (u8) fabs(port_firstPort - port);
	if (direction) {
		*ptr |= (1 << pinNumber);
	} else {
		*ptr &= ~(1 << pinNumber);
	}
}

void port_writePort(u8 port, u8 data) {
	u8* ptr = &port_firstOutput - 3 * (u8) fabs(port_firstPort - port);
	*ptr = data;
}

void port_writePin(u8 port, u8 pinNumber, u8 value) {
	u8* ptr = &port_firstOutput - 3 * (u8) fabs(port_firstPort - port);
	if (value) {
		*ptr |= (1 << pinNumber);
	} else {
		*ptr &= ~(1 << pinNumber);
	}
}

void port_togglePort(u8 port) {
	u8* ptr = &port_firstOutput - 3 * (u8) fabs(port_firstPort - port);
	*ptr = ~(*ptr);
}

void port_togglePin(u8 port, u8 pinNumber) {
	u8* ptr = &port_firstOutput - 3 * (u8) fabs(port_firstPort - port);
	*ptr ^= (1 << pinNumber);
}

u8 port_readPort(u8 port) {
	u8* ptr = &port_firstInput - 3 * (u8) fabs(port_firstPort - port);
	return (*ptr);
}

u8 port_readPin(u8 port, u8 pinNumber) {
	u8* ptr = &port_firstInput - 3 * (u8) fabs(port_firstPort - port);
    if (*ptr & (1 << pinNumber)) {
        return 1;
    }
	return 0;
}