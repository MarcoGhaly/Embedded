#include "Port.h"

// Set Port Direction
void port_setPortDirection(u8 port, u8 direction) {
	u8* ptr = &port_firstDirection + 3 * (u8) fabs(port_firstPort - toUpperCase(port));
    *ptr = _8bit_max * direction;
}

// Set Pin Direction
void port_setPinDirection(struct Pin* pin, u8 direction) {
	u8* ptr = &port_firstDirection + 3 * (u8) fabs(port_firstPort - toUpperCase(pin->port));
	if (direction) {
		*ptr |= (1 << pin->pinNumber);
	} else {
		*ptr &= ~(1 << pin->pinNumber);
	}
}

// Write Port
void port_writePort(u8 port, u8 data) {
	u8* ptr = &port_firstOutput + 3 * (u8) fabs(port_firstPort - toUpperCase(port));
	*ptr = data;
}

// Write Pin
void port_writePin(struct Pin* pin, u8 value) {
	u8* ptr = &port_firstOutput + 3 * (u8) fabs(port_firstPort - toUpperCase(pin->port));
	if (value) {
		*ptr |= (1 << pin->pinNumber);
	} else {
		*ptr &= ~(1 << pin->pinNumber);
	}
}

// Toggle Port
void port_togglePort(u8 port) {
	u8* ptr = &port_firstOutput + 3 * (u8) fabs(port_firstPort - toUpperCase(port));
	*ptr = ~(*ptr);
}

// Toggle Pin
void port_togglePin(struct Pin* pin) {
	u8* ptr = &port_firstOutput + 3 * (u8) fabs(port_firstPort - toUpperCase(pin->port));
	*ptr ^= (1 << pin->pinNumber);
}

// Read Port
u8 port_readPort(u8 port) {
	u8* ptr = &port_firstInput + 3 * (u8) fabs(port_firstPort - toUpperCase(port));
	return (*ptr);
}

// Read Pin
u8 port_readPin(struct Pin* pin) {
	u8* ptr = &port_firstInput + 3 * (u8) fabs(port_firstPort - toUpperCase(pin->port));
    if (*ptr & (1 << pin->pinNumber)) {
        return 1;
    }
	return 0;
}

// To Upper Case
u8 toUpperCase(u8 letter) {
	if (letter > 'Z') {
		letter -= 'a' - 'A';
	}
	return letter;
}