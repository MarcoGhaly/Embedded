#include "Compass.h"

// Initialize
void compass_init() {
	masterI2C_activate(0);
	masterI2C_transmitByte(0x00);	// Set pointer to CRA
	while(!masterI2C_isTransmissionComplete());
	masterI2C_transmitByte(0x70);
	while(!masterI2C_isTransmissionComplete());
	masterI2C_deactivate(0);
	
	masterI2C_activate(0);
	masterI2C_transmitByte(0x01);	// Set pointer to CRB
	while(!masterI2C_isTransmissionComplete());
	masterI2C_transmitByte(0xA0);
	while(!masterI2C_isTransmissionComplete());
	masterI2C_deactivate(0);
	
	masterI2C_activate(0);
	masterI2C_transmitByte(0x02);	// Set pointer to measurement mode
	while(!masterI2C_isTransmissionComplete());
	masterI2C_transmitByte(0x00);	// Continuous measurement
	while(!masterI2C_isTransmissionComplete());
	masterI2C_deactivate(0);
}

// Get Angle
u16 compass_getAngle() {
	masterI2C_activate(0);
	masterI2C_transmitByte(0x03);	// Set pointer to X-axis MSB
	while(!masterI2C_isTransmissionComplete());
	masterI2C_deactivate(0);
	
	masterI2C_activate(0);
	
	masterI2C_receiveByte(true);
	while(!masterI2C_isTransmissionComplete());
	u16 x = (u16)masterI2C_readByte() << 8;
	masterI2C_receiveByte(true);
	while(!masterI2C_isTransmissionComplete());
	x |= masterI2C_readByte();
	
	masterI2C_receiveByte(true);
	while(!masterI2C_isTransmissionComplete());
	u16 z = (u16)masterI2C_readByte() << 8;
	masterI2C_receiveByte(true);
	while(!masterI2C_isTransmissionComplete());
	z |= masterI2C_readByte();
	
	masterI2C_receiveByte(true);
	while(!masterI2C_isTransmissionComplete());
	u16 y = (u16)masterI2C_readByte() << 8;
	masterI2C_receiveByte(false);
	while(!masterI2C_isTransmissionComplete());
	y |= masterI2C_readByte();
	
	masterI2C_deactivate(0);
	
	double angle = atan2((double)y, (double)x) * (double)180 / (double)M_PI;
	if (angle < 0) {
		angle += 360;
	}
	return (u16)angle;
}