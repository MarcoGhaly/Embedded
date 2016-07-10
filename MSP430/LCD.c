#include "LCD.h"

static u8 lcd_mode = lcd_4_bit;
static u8 lcd_adjustment = lcd_higherNibble;

static u8 lcd_currentRow = 0;
static u8 lcd_currentColumn = 0;

static u8 lcd_firstBit;
static u8 lcd_lastBit;

static u8 lcd_busyFlagBit = 7;

static void lcd_sendChar(u8 value, u8 type) {
	lcd_checkBusyFlag();
	lcd_setOutputPortDirection(port_direction_output);
	port_writePin(lcd_controlPort, lcd_RW, lcd_write);
	port_writePin(lcd_controlPort, lcd_RS, type);
	port_writePin(lcd_controlPort, lcd_EN, high);
	lcd_writeOutputPort(value);
	port_writePin(lcd_controlPort, lcd_EN, low);
}

static void lcd_setOutputPortDirection(u8 direction) {
	if (lcd_mode == lcd_4_bit) {
		u8 i;
		for (i = lcd_firstBit; i <= lcd_lastBit; i++) {
			port_setPinDirection(lcd_dataPort, i, direction);
		}
		return;
	}
	port_setPortDirection(lcd_dataPort, port_direction_output);
}

static void lcd_writeOutputPort(u8 value) {
	if (lcd_mode == lcd_4_bit) {
		u8 i, j;
		for (j = 0; j < 2; j++) {
			for (i = lcd_lastBit; i >= lcd_firstBit; i--) {
				port_writePin(lcd_dataPort, i, (value) & 0x80);
				value = value << 1;
			}
			if (j == 1) {
				return;
			}
			port_writePin(lcd_controlPort, lcd_EN, low);
			port_writePin(lcd_controlPort, lcd_EN, high);
		}
	}
	port_writePort(lcd_dataPort, value);
}

void lcd_init() {
	port_setPinDirection(lcd_controlPort, lcd_RS, port_direction_output);
	port_setPinDirection(lcd_controlPort, lcd_RW, port_direction_output);
	port_setPinDirection(lcd_controlPort, lcd_EN, port_direction_output);
	if (lcd_mode == lcd_4_bit) {
		lcd_firstBit = lcd_adjustment * 4;
		lcd_lastBit = lcd_firstBit + 3;
		lcd_sendChar(0x02, lcd_command);
		lcd_busyFlagBit = lcd_adjustment * 4 + 3;
	}
	u8 functionSet = lcd_command_functionSet | (lcd_mode << 4);
	lcd_sendChar(functionSet, lcd_command);			//	Function Set
	lcd_sendChar(lcd_command_displayControl, lcd_command);	//	Display On/Off Control
	lcd_sendChar(lcd_command_clearDisplay, lcd_command);	//	Clear Display
	lcd_sendChar(lcd_command_entrySetMode, lcd_command);	//	Entry Mode Set
}

void lcd_setCursor(u8 row, u8 column) {
	u8 dd_ram_value = ( (lcd_firstAddress | ( (row % 2) << lcd_rowShift)) | column );
	if (row > 1) {
		dd_ram_value += lcd_columns;
	}
	lcd_sendChar(dd_ram_value, lcd_command);
	lcd_currentRow = row;
	lcd_currentColumn = column;
}

void lcd_jump() {
	lcd_currentRow = (lcd_currentRow + 1) % lcd_rows;
	lcd_setCursor(lcd_currentRow, lcd_currentColumn);
}

void lcd_jumpNewLine() {
	lcd_currentRow = (lcd_currentRow + 1) % lcd_rows;
	lcd_setCursor(lcd_currentRow, 0);
}

void lcd_displayChars(u8* ptr, u8 length) {
	u8 i;
	for (i = 0; i < length; i++) {
		lcd_displayChar(ptr[i]);
	}
}

void lcd_displayChar(u8 value) {
	lcd_sendChar(value, lcd_data);
	lcd_currentColumn = (lcd_currentColumn + 1) % lcd_columns;
	if (!lcd_currentColumn) {
		lcd_jumpNewLine();
	}
}

void lcd_eraseChar() {
	if (!lcd_currentColumn) {
		if (!lcd_currentRow) {
			lcd_currentRow = lcd_rows - 1;
		} else {
			lcd_currentRow--;
		}
		lcd_currentColumn = lcd_columns - 1;
	} else {
		lcd_currentColumn--;
	}
	lcd_setCursor(lcd_currentRow, lcd_currentColumn);
	lcd_sendChar(' ', lcd_data);
	lcd_setCursor(lcd_currentRow, lcd_currentColumn);
}

void lcd_displayNumber(double number, u8 approximation) {
	if (number < 0) {
		lcd_displayChar('-');
		number *= -1;
	}
	if (number < 1) {
		lcd_displayChar('0');
	}
	lcd_displayInteger((u32)number);
	
	enum boolean first = true;
	u8 i;
	for (i = 0; i < approximation; i++) {
		number *= 10;
		u32 integer = (u32)number;
		if ( (number == (double)integer) && (integer % 10 == 0) ) {
			break;
		}
		if (first) {
			lcd_displayChar('.');
		}
		first = false;
		lcd_displayChar('0' + integer % 10);
	}
}

static void lcd_displayInteger(u32 number) {
	if (number == 0) {
		return;
	}
	lcd_displayInteger(number / 10);
	lcd_displayChar('0' + number % 10);
}

u8 lcd_readChar() {
	lcd_checkBusyFlag();
	port_setPortDirection(lcd_dataPort, port_direction_input);
	port_writePin(lcd_controlPort, lcd_RW, lcd_read);
	port_writePin(lcd_controlPort, lcd_RS, lcd_data);
	port_writePin(lcd_controlPort, lcd_EN, high);
	u8 value = port_readPort(lcd_dataPort);
	port_writePin(lcd_controlPort, lcd_EN, low);
	return value;
}

void lcd_clearScreen() {
	lcd_sendChar(lcd_command_clearDisplay, lcd_command);
}

void lcd_checkBusyFlag() {
	lcd_setOutputPortDirection(port_direction_input);
	port_writePin(lcd_controlPort, lcd_RW, lcd_read);
	port_writePin(lcd_controlPort, lcd_RS, lcd_command);
	u8 flag;
	do {
		port_writePin(lcd_controlPort, lcd_EN, low);
		port_writePin(lcd_controlPort, lcd_EN, high);
		flag = port_readPin(lcd_dataPort, lcd_busyFlagBit);
		if (lcd_mode == lcd_4_bit) {
			port_writePin(lcd_controlPort, lcd_EN, low);
			port_writePin(lcd_controlPort, lcd_EN, high);
		}
	} while(flag);
	port_writePin(lcd_controlPort, lcd_EN, low);
}
