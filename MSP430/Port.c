#include "Port.h"

static const u8 in_addresses[port_portsNumber] = {0x20, 0x28, 0x18, 0x1C};
static const u8 out_addresses[port_portsNumber] = {0x21, 0x29, 0x19, 0x1D};
static const u8 dir_addresses[port_portsNumber] = {0x22, 0x2A, 0x1A, 0x1E};
static const u8 sel_addresses[port_portsNumber] = {0x26, 0x2E, 0x1B, 0x1F};
static const u8 sel2_addresses[port_portsNumber] = {0x41, 0x42, 0x43, 0x44};
static const u8 res_addresses[port_portsNumber] = {0x27, 0x2F, 0x10, 0x11};
static const u8 int_enable_addresses[port_interruptsNumber] = {0x25, 0x2D};
static const u8 int_edge_addresses[port_interruptsNumber] = {0x24, 0x2C};

void port_setPortDirection(u8 portNumber, u8 direction) {
	u8* dir_ptr = (u8*) dir_addresses[portNumber - 1];
	*dir_ptr = direction * _8bit_max;
}

void port_setPinDirection(u8 portNumber, u8 pinNumber, u8 direction) {
	u8* dir_ptr = (u8*) dir_addresses[portNumber - 1];
	if (direction) {
		*dir_ptr |= (1 << pinNumber);
	} else {
		*dir_ptr &= ~(1 << pinNumber);
	}
}

void port_writePort(u8 portNumber, u8 data) {
	u8* out_ptr = (u8*) out_addresses[portNumber - 1];
	*out_ptr = data;
}

void port_writePin(u8 portNumber, u8 pinNumber, u8 value) {
	u8* out_ptr = (u8*) out_addresses[portNumber - 1];
	if (value) {
		*out_ptr |= (1 << pinNumber);
	} else {
		*out_ptr &= ~(1 << pinNumber);
	}
}

void port_togglePort(u8 portNumber) {
	u8* out_ptr = (u8*) out_addresses[portNumber - 1];
	*out_ptr = ~(*out_ptr);
}

void port_togglePin(u8 portNumber, u8 pinNumber) {
	u8* out_ptr = (u8*) out_addresses[portNumber - 1];
	*out_ptr ^= (1 << pinNumber);
}

u8 port_readPort(u8 portNumber) {
	u8* in_ptr = (u8*) in_addresses[portNumber - 1];
	return *in_ptr;
}

u8 port_readPin(u8 portNumber, u8 pinNumber) {
	u8* in_ptr = (u8*) in_addresses[portNumber - 1];
	if (*in_ptr & (1 << pinNumber)) {
		return 1;
	}
	return 0;
}

void port_setPinFunction(u8 portNumber, u8 pinNumber, u8 function) {
	u8* sel_ptr = (u8*) sel_addresses[portNumber - 1];
	u8* sel2_ptr = (u8*) sel2_addresses[portNumber - 1];
	*sel_ptr &= ~(1 << pinNumber);
	*sel2_ptr &= ~(1 << pinNumber);
	*sel_ptr |= ((function & 0x01) << pinNumber);
	function = function >> 1;
	*sel2_ptr |= ((function & 0x01) << pinNumber);
}

void port_setPortResistorEnabled(u8 portNumber, enum boolean enabled) {
	u8* res_ptr = (u8*) res_addresses[portNumber - 1];
	if (enabled) {
		*res_ptr = _8bit_max;
	} else {
		*res_ptr = 0;
	}

}

void port_setPinResistorEnabled(u8 portNumber, u8 pinNumber, enum boolean enabled) {
	u8* res_ptr = (u8*) res_addresses[portNumber - 1];
	if (enabled) {
		*res_ptr |= (1 << pinNumber);
	} else {
		*res_ptr &= ~(1 << pinNumber);
	}
}

void port_setPortInterruptEnabled(u8 portNumber, enum boolean enabled) {
	u8* int_enable_ptr = (u8*) int_enable_addresses[portNumber - 1];
	if (enabled) {
		*int_enable_ptr = _8bit_max;
	} else {
		*int_enable_ptr = 0;
	}
}

void port_setPinInterruptEnabled(u8 portNumber, u8 pinNumber, enum boolean enabled) {
	u8* int_enable_ptr = (u8*) int_enable_addresses[portNumber - 1];
	if (enabled) {
		*int_enable_ptr |= (1 << pinNumber);
	} else {
		*int_enable_ptr &= ~(1 << pinNumber);
	}
}

void port_setPortInterruptEdge(u8 portNumber, u8 edge) {
	u8* int_edge_ptr = (u8*) int_edge_addresses[portNumber - 1];
	*int_edge_ptr = edge * _8bit_max;
}

void port_setPinInterruptEdge(u8 portNumber, u8 pinNumber, u8 edge) {
	u8* int_edge_ptr = (u8*) int_edge_addresses[portNumber - 1];
	if (edge) {
		*int_edge_ptr |= (1 << pinNumber);
	} else {
		*int_edge_ptr &= ~(1 << pinNumber);
	}
}
