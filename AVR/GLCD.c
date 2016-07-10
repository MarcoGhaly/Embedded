#include "GLCD.h"

static struct Pin glcd_RS;
static struct Pin glcd_RW;
static struct Pin glcd_EN;
static struct Pin glcd_CS1;
static struct Pin glcd_CS2;
static u8 glcd_dataPort;

static u8 glcd_rows;
static u8 glcd_columns;

static u8 glcd_currentRow = 0;
static u8 glcd_currentColumn = 0;

// Initialize
void glcd_init(u8 rows, u8 columns, struct Pin* RS, struct Pin* RW, struct Pin* EN, struct Pin* CS1, struct Pin* CS2, u8 dataPort) {
	glcd_rows = rows;
	glcd_columns = columns;
	
	glcd_RS.port = RS->port;
	glcd_RS.pinNumber = RS->pinNumber;
	glcd_RW.port = RW->port;
	glcd_RW.pinNumber = RW->pinNumber;
	glcd_EN.port = EN->port;
	glcd_EN.pinNumber = EN->pinNumber;
	glcd_CS1.port = CS1->port;
	glcd_CS1.pinNumber = CS1->pinNumber;
	glcd_CS2.port = CS2->port;
	glcd_CS2.pinNumber = CS2->pinNumber;
	glcd_dataPort = dataPort;
	
	port_setPinDirection(&glcd_RS, port_direction_output);
	port_setPinDirection(&glcd_RW, port_direction_output);
	port_setPinDirection(&glcd_EN, port_direction_output);
	port_setPinDirection(&glcd_CS1, port_direction_output);
	port_setPinDirection(&glcd_CS2, port_direction_output);
	
	glcd_sendChar(glcd_command_displayControl | high, glcd_command);	//	Display On
}

// Send Character
static void glcd_sendChar(u8 value, u8 type) {
	glcd_checkBusyFlag();
	port_setPortDirection(glcd_dataPort, port_direction_output);
	port_writePin(&glcd_EN, low);
	port_writePin(&glcd_RW, glcd_write);
	port_writePin(&glcd_RS, type);
	port_writePin(&glcd_EN, high);
	port_writePort(glcd_dataPort, value);
	port_writePin(&glcd_EN, low);
}

// Read Character
static u8 glcd_readChar() {
	glcd_checkBusyFlag();
	port_setPortDirection(glcd_dataPort, port_direction_input);
	port_writePin(&glcd_EN, low);
	port_writePin(&glcd_RW, glcd_read);
	port_writePin(&glcd_RS, glcd_data);
	port_writePin(&glcd_EN, high);
	port_writePin(&glcd_EN, low);
	port_writePin(&glcd_EN, high);
	u8 value = port_readPort(glcd_dataPort);
	return value;
}

// Check Busy Flag
void glcd_checkBusyFlag() {
	struct Pin glcd_busyFlag = {glcd_dataPort, glcd_busyFlagBit};
	port_setPortDirection(glcd_dataPort, port_direction_input);
	port_writePin(&glcd_EN, low);
	port_writePin(&glcd_RW, glcd_read);
	port_writePin(&glcd_RS, glcd_command);
	//port_writePin(&glcd_EN, high);
	do {
		port_writePin(&glcd_EN, low);
		port_writePin(&glcd_EN, high);
	} while(port_readPin(&glcd_busyFlag));
}

// Set Position
static void glcd_setPosition(u8 page, u8 column) {
	u8 side = column / glcd_columns;
	column -= glcd_columns * side;
	
	port_writePin(&glcd_CS1, low);
	port_writePin(&glcd_CS2, low);
	glcd_sendChar(glcd_firstPageAddress | page, glcd_command);
	
	port_writePin(&glcd_CS1, glcd_side_right - side);
	port_writePin(&glcd_CS2, side);
	glcd_sendChar(glcd_firstColumnAddress | column, glcd_command);
}

// Set Dot
void glcd_setDot(u8 row, u8 column, enum boolean illuminated) {
	glcd_setPosition(row / 8, column);
	u8 value = glcd_readChar();
	glcd_setPosition(row / 8, column);
	if (illuminated) {
		value &= ~(1 << (row % 8));
	} else {
		value |= 1 << (row % 8);
	}
	glcd_sendChar(value, glcd_data);
	glcd_currentRow = row;
	glcd_currentColumn = column;
}

// Is Illuminated
enum boolean glcd_isIlluminated(u8 row, u8 column) {
	glcd_setPosition(row / 8, column);
	u8 value = glcd_readChar();
	if (value & (1 << (row % 8))) {
		return false;
	}
	return true;
}

/*
// Display Character
void glcd_displayChar(u8 value) {
	glcd_sendChar(value, glcd_data);
	glcd_currentColumn = (glcd_currentColumn + 1) % glcd_columns;
	if (!glcd_currentColumn) {
		glcd_currentRow = (glcd_currentRow + 1) % glcd_rows;
	}
}

// Display Characters
void glcd_displayChars(u8* ptr, u8 length) {
	u8 i;
	for (i = 0; i < length; i++) {
		glcd_displayChar(ptr[i]);
	}
}

// Erase Character
void glcd_eraseChar() {
	if (!glcd_currentColumn) {
		if (!glcd_currentRow) {
			glcd_currentRow = glcd_rows - 1;
		} else {
			glcd_currentRow--;
		}
		glcd_currentColumn = glcd_columns - 1;
	} else {
		glcd_currentColumn--;
	}
	glcd_setPosition(glcd_currentRow, glcd_currentColumn);
	glcd_sendChar(' ', glcd_data);
	glcd_setPosition(glcd_currentRow, glcd_currentColumn);
}

// Display Number
void glcd_displayNumber(double number, u8 approximation) {
	if (number < 0) {
		glcd_displayChar('-');
		number *= -1;
	}
	if (number < 1) {
		glcd_displayChar('0');
	}
	glcd_displayInteger((u32)number);
	
	enum boolean first = true;
	u8 i;
	for (i = 0; i < approximation; i++) {
		number *= 10;
		u32 integer = (u32)number;
		if ( (number == (double)integer) && (integer % 10 == 0) ) {
			break;
		}
		if (first) {
			glcd_displayChar('.');
		}
		first = false;
		glcd_displayChar('0' + integer % 10);
	}
}

// Display Integer
static void glcd_displayInteger(u32 number) {
	if (number == 0) {
		return;
	}
	glcd_displayInteger(number / 10);
	glcd_displayChar('0' + number % 10);
}
*/