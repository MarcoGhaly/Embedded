#ifndef LCD_H_
#define LCD_H_

#include "Types.h"
#include "Port.h"

#define lcd_rows 2
#define lcd_columns 16

#define lcd_controlPort 2
#define lcd_dataPort 2

#define lcd_RS 1
#define lcd_RW 2
#define lcd_EN 3

#define lcd_4_bit 0
#define lcd_8_bit 1

#define lcd_lowerNibble 0
#define lcd_higherNibble 1

#define lcd_write 0
#define lcd_read 1

#define lcd_command 0
#define lcd_data 1

#define lcd_firstAddress 0x80
#define lcd_rowShift 6

#define lcd_command_functionSet 0x2C
#define lcd_command_displayControl 0x0C
#define lcd_command_entrySetMode 0x06
#define lcd_command_clearDisplay 0x01

static void lcd_sendChar(u8 value, u8 type);
static void lcd_setOutputPortDirection(u8 direction);
static void lcd_writeOutputPort(u8 value);
void lcd_init();
void lcd_setCursor(u8 row, u8 column);
void lcd_jump();
void lcd_jumpNewLine();
void lcd_displayChars(u8* ptr, u8 length);
void lcd_displayChar(u8 value);
void lcd_eraseChar();
void lcd_displayNumber(double number, u8 approximation);
static void lcd_displayInteger(u32 number);
u8 lcd_readChar();
void lcd_clearScreen();
void lcd_checkBusyFlag();

#endif /* LCD_H_ */
