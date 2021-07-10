/*! 
 *  Common_Macros.h
 *  \brief		Commonly used macros for AVR
 *  \details	Some commonly used macros that can be used with AVR uC.
 *	they contain mostly some macros for manipulating registers, I/O operations,...
 *  \author		Meena Bassem - mpdotf@gmail.com
 *  \date		25-2-2015 
 *	\warning	Must use CAPITAL LETTERS with some of the macros.
 */

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_
#define _CONCAT(a,b) a##b
//concat	PORT(A)	->	PORTA
#define PORT(X) _CONCAT(PORT,X)
#define PIN(X) _CONCAT(PIN,X)
#define DDR(X) _CONCAT(DDR,X)

#define SET_HIGH(REG,NUM)		REG |= (1 << NUM)
#define SET_LOW(REG,NUM)		REG &= ~(1 << NUM)
#define TOGGLE(REG,NUM)			REG ^= (1 << NUM)
#define CHECK_HIGH(REG,NUM)		REG & (1 << NUM)
#define CHECK_LOW(REG,NUM)		(!(REG & (1 << NUM)))
/*WARNING : USE CAPITAL LETTERS WITH ALL THESE MACROS*/
#define TOGGLE_PORT(LETTER,NUM)			TOGGLE(PORT(LETTER),NUM)
#define BUTTON_PRESSED(LETTER,NUM)		CHECK_LOW(PIN(LETTER),NUM)
#define SET_INPUT(LETTER,NUM)			SET_LOW(DDR(LETTER),NUM)
#define SET_OUTPUT(LETTER,NUM)			SET_HIGH(DDR(LETTER),NUM)
#define SET_PORT_HIGH(LETTER,NUM)		SET_HIGH(PORT(LETTER),NUM)
#define SET_PORT_LOW(LETTER,NUM)		SET_LOW(PORT(LETTER),NUM)
#define CHECK_PIN_HIGH(LETTER,NUM)		CHECK_HIGH(PIN(LETTER),NUM)
#define CHECK_PIN_LOW(LETTER,NUM)		CHECK_LOW(PIN(LETTER),NUM)
#define PULLUP_ENABLE(LETTER,NUM)		SET_LOW(DDR(LETTER),NUM); SET_HIGH(PORT(LETTER),NUM)
#endif