#ifndef LCD_H_
#define LCD_H_

#include "Types.h"
#include "Port.h"

#define LCD_mode_4bit 0
#define LCD_mode_8bit 1

#define LCD_write 0
#define LCD_read 1

#define LCD_command 0
#define LCD_data 1

#define LCD_firstAddress 0x80
#define LCD_rowShift 6

#define LCD_command_4bitMode 0x02
#define LCD_command_functionSet 0x2C
#define LCD_command_displayControl 0x0C
#define LCD_command_entrySetMode 0x06
#define LCD_command_clearDisplay 0x01

void LCD_init(u8 rows, u8 columns, struct Pin* RS, struct Pin* RW, struct Pin* EN, struct Pin* dataStart, struct Pin* dataEnd);
static void LCD_setDataPortDirection(u8 direction);
static void LCD_writeDataPort(u8 value);
static void LCD_sendChar(u8 value, u8 type);
u8 LCD_readChar();
void LCD_checkBusyFlag();
void LCD_setCursor(u8 row, u8 column);
void LCD_jump();
void LCD_jumpNewLine();
void LCD_displayChar(u8 value);
void LCD_displayCharAt(u8 value, u8 row, u8 column);
void LCD_displayChars(u8* ptr, u8 length);
void LCD_eraseChar();
void LCD_displayNumber(double number, u8 approximation);
static void LCD_displayInteger(u32 number);
void LCD_clearScreen();

#endif /* LCD_H_ */