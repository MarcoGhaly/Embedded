#include "LCD.h"

static struct Pin LCD_RS;
static struct Pin LCD_RW;
static struct Pin LCD_EN;
static struct Pin LCD_dataStart;
static struct Pin LCD_dataEnd;

static u8 LCD_mode = LCD_mode_4bit;

static u8 LCD_rows;
static u8 LCD_columns;

static u8 LCD_currentRow = 0;
static u8 LCD_currentColumn = 0;

// Initialize
void LCD_init(u8 rows, u8 columns, struct Pin* RS, struct Pin* RW, struct Pin* EN, struct Pin* dataStart, struct Pin* dataEnd) {
	LCD_rows = rows;
	LCD_columns = columns;
	
	LCD_RS.port = RS->port;
	LCD_RS.pinNumber = RS->pinNumber;
	LCD_RW.port = RW->port;
	LCD_RW.pinNumber = RW->pinNumber;
	LCD_EN.port = EN->port;
	LCD_EN.pinNumber = EN->pinNumber;
	LCD_dataStart.port = dataStart->port;
	LCD_dataStart.pinNumber = dataStart->pinNumber;
	LCD_dataEnd.port = dataEnd->port;
	LCD_dataEnd.pinNumber = dataEnd->pinNumber;
	
	port_setPinDirection(&LCD_RS, port_direction_output);
	port_setPinDirection(&LCD_RW, port_direction_output);
	port_setPinDirection(&LCD_EN, port_direction_output);
	
	if (dataEnd->pinNumber - dataStart->pinNumber == 3) {
		LCD_mode = LCD_mode_4bit;
		LCD_sendChar(LCD_command_4bitMode, LCD_command);
	}
	u8 functionSet = LCD_command_functionSet | (LCD_mode << 4);
	
	LCD_sendChar(functionSet, LCD_command);					//	Function Set
	LCD_sendChar(LCD_command_displayControl, LCD_command);	//	Display On/Off Control
	LCD_sendChar(LCD_command_clearDisplay, LCD_command);	//	Clear Display
	LCD_sendChar(LCD_command_entrySetMode, LCD_command);	//	Entry Mode Set
}

// Set Data Port Direction
static void LCD_setDataPortDirection(u8 direction) {
	if (LCD_mode == LCD_mode_4bit) {
		u8 i;
		for (i = LCD_dataStart.pinNumber; i <= LCD_dataEnd.pinNumber; i++) {
			struct Pin pin = {LCD_dataStart.port, i};
			port_setPinDirection(&pin, direction);
		}
		return;
	}
	port_setPortDirection(LCD_dataStart.port, direction);
}

// Write Data Port
static void LCD_writeDataPort(u8 value) {
	if (LCD_mode == LCD_mode_4bit) {
		s8 i, j;
		for (j = 0; j < 2; j++) {
			for (i = LCD_dataEnd.pinNumber; i >= LCD_dataStart.pinNumber; i--) {
				struct Pin pin = {LCD_dataStart.port, i};
				port_writePin(&pin, (value) & 0x80);
				value = value << 1;
			}
			if (j == 1) {
				return;
			}
			port_writePin(&LCD_EN, low);
			port_writePin(&LCD_EN, high);
		}
	}
	port_writePort(LCD_dataStart.port, value);
}

// Send Character
static void LCD_sendChar(u8 value, u8 type) {
	LCD_checkBusyFlag();
	port_writePin(&LCD_EN, low);
	port_writePin(&LCD_RW, LCD_write);
	port_writePin(&LCD_RS, type);
	port_writePin(&LCD_EN, high);
	LCD_setDataPortDirection(port_direction_output);
	LCD_writeDataPort(value);
	port_writePin(&LCD_EN, low);
}

// Read Character
u8 LCD_readChar() {
	port_setPortDirection(LCD_dataStart.port, port_direction_input);
	LCD_checkBusyFlag();
	port_writePin(&LCD_EN, low);
	port_writePin(&LCD_RW, LCD_read);
	port_writePin(&LCD_RS, LCD_data);
	port_writePin(&LCD_EN, high);
	port_writePin(&LCD_EN, low);
	port_writePin(&LCD_EN, high);
	u8 value = port_readPort(LCD_dataStart.port);
	return value;
}

// Check Busy Flag
void LCD_checkBusyFlag() {
	LCD_setDataPortDirection(port_direction_input);
	port_writePin(&LCD_EN, low);
	port_writePin(&LCD_RW, LCD_read);
	port_writePin(&LCD_RS, LCD_command);
	u8 flag;
	do {
		port_writePin(&LCD_EN, low);
		port_writePin(&LCD_EN, high);
		flag = port_readPin(&LCD_dataEnd);
		if (LCD_mode == LCD_mode_4bit) {
			port_writePin(&LCD_EN, low);
			port_writePin(&LCD_EN, high);
		}
	} while(flag);
}

// Set Cursor
void LCD_setCursor(u8 row, u8 column) {
	u8 dd_ram_value = ( (LCD_firstAddress | ( (row % 2) << LCD_rowShift)) | column );
	if (row > 1) {
		dd_ram_value += LCD_columns;
	}
	LCD_sendChar(dd_ram_value, LCD_command);
	LCD_currentRow = row;
	LCD_currentColumn = column;
}

// Jump
void LCD_jump() {
	LCD_currentRow = (LCD_currentRow + 1) % LCD_rows;
	LCD_setCursor(LCD_currentRow, LCD_currentColumn);
}

// Jump New Line
void LCD_jumpNewLine() {
	LCD_currentRow = (LCD_currentRow + 1) % LCD_rows;
	LCD_setCursor(LCD_currentRow, 0);
}

// Display Character
void LCD_displayChar(u8 value) {
	LCD_sendChar(value, LCD_data);
	LCD_currentColumn = (LCD_currentColumn + 1) % LCD_columns;
	if (!LCD_currentColumn) {
		LCD_jumpNewLine();
	}
}

// Display Character At
void LCD_displayCharAt(u8 value, u8 row, u8 column) {
	LCD_setCursor(row, column);
	LCD_displayChar(value);
}

// Display Characters
void LCD_displayChars(u8* ptr, u8 length) {
	u8 i;
	for (i = 0; i < length; i++) {
		LCD_displayChar(ptr[i]);
	}
}

// Erase Character
void LCD_eraseChar() {
	if (!LCD_currentColumn) {
		if (!LCD_currentRow) {
			LCD_currentRow = LCD_rows - 1;
		} else {
			LCD_currentRow--;
		}
		LCD_currentColumn = LCD_columns - 1;
	} else {
		LCD_currentColumn--;
	}
	LCD_setCursor(LCD_currentRow, LCD_currentColumn);
	LCD_sendChar(' ', LCD_data);
	LCD_setCursor(LCD_currentRow, LCD_currentColumn);
}

// Display Number
void LCD_displayNumber(double number, u8 approximation) {
	if (number < 0) {
		LCD_displayChar('-');
		number *= -1;
	}
	if (number < 1) {
		LCD_displayChar('0');
	}
	LCD_displayInteger((u32)number);
	
	enum boolean first = true;
	u8 i;
	for (i = 0; i < approximation; i++) {
		number *= 10;
		u32 integer = (u32)number;
		if ( (number == (double)integer) && (integer % 10 == 0) ) {
			break;
		}
		if (first) {
			LCD_displayChar('.');
		}
		first = false;
		LCD_displayChar('0' + integer % 10);
	}
}

// Display Integer
static void LCD_displayInteger(u32 number) {
	if (number == 0) {
		return;
	}
	LCD_displayInteger(number / 10);
	LCD_displayChar('0' + number % 10);
}

// Clear Screen
void LCD_clearScreen() {
	LCD_sendChar(LCD_command_clearDisplay, LCD_command);
}