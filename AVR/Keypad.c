#include "Keypad.h"

static struct Keypad_Button keypad_buttons[keypad_rowsNumber][keypad_columnsNumber];
static u8 keypad_rowsCounter = 0;
static u16 keypad_holdDelay_ms = 500;
static u16 keypad_typeDelay_ms = 100;

// Initialize Timer
static void keypad_initTimer(u8 frequency_MHz) {
	u16 keypad_timer0Dividers[keypad_frequnciesNumber] = {1, 8, 64, 256, 1024};
	u16 divider = (u16)(frequency_MHz * 1000 / keypad_intermediateFrequency_KHz);
	u8 i;
	for (i = 0; i < keypad_frequnciesNumber; i++) {
		if (divider / keypad_timer0Dividers[i] == 0) {
			divider = keypad_timer0Dividers[i];
			break;
		}
	}
	u8 compare = (u8)(frequency_MHz * 1000 / divider);	// Frequency in KHz (Cycle / ms)
	// Sampling each 1 ms
	timer0_setMode(timer0_CTC);
	timer0_setDivider(i + 1);
	timer0_setCompareValue(compare);
	timer0_setCompareInterruptEnabled(true);
	timer0_start();
}

// Initialize Pins
static void keypad_initPins(struct Pin* writePins, struct Pin* readPins) {
	u8 i, j;
	for (i = 0; i < keypad_rowsNumber; i++) {
		for (j = 0; j < keypad_columnsNumber; j++) {
			keypad_buttons[i][j].writePin.port = writePins[i].port;
			keypad_buttons[i][j].writePin.pinNumber = writePins[i].pinNumber;
			keypad_buttons[i][j].readPin.port = readPins[j].port;
			keypad_buttons[i][j].readPin.pinNumber = readPins[j].pinNumber;
			keypad_buttons[i][j].samplesCounter = 0;
			keypad_buttons[i][j].pressed = false;
			keypad_buttons[i][j].hold = false;
			keypad_buttons[i][j].delayCounter = 0;
			keypad_buttons[i][j].typed = false;
		}
	}
	// Input & Pull-ups
	for (i = 0; i < keypad_columnsNumber; i++) {
		port_setPinDirection(&readPins[i], port_direction_input);
		port_writePin(&readPins[i], high);	// Pull-up resistor
	}
}

// Initialize
void keypad_init(u8 frequency_MHz, struct Pin* writePins, struct Pin* readPins) {
	keypad_initPins(writePins, readPins);
	keypad_initTimer(frequency_MHz);
}

// Set Delays
void keypad_setDelays(u16 holdDelay_ms, u16 typeDelay_ms) {
	keypad_holdDelay_ms = holdDelay_ms;
	keypad_typeDelay_ms = typeDelay_ms;
}

// Is Pressed
enum boolean keypad_isPressed(u8 rowNumber, u8 columnNumber) {
	return (keypad_buttons[rowNumber][columnNumber].pressed);
}

// Is Typed
enum boolean keypad_isTyped(u8 rowNumber, u8 columnNumber) {
	enum boolean typed = keypad_buttons[rowNumber][columnNumber].typed;
	keypad_buttons[rowNumber][columnNumber].typed = false;
	return typed;
}

// Timer Interrupt
ISR (TIMER0_COMP_vect) {
	u8 keypad_columnsCounter;
	for (keypad_columnsCounter = 0; keypad_columnsCounter < keypad_columnsNumber; keypad_columnsCounter++) {
		port_setPinDirection(&keypad_buttons[keypad_rowsCounter][keypad_columnsCounter].writePin, port_direction_output);
		port_writePin(&keypad_buttons[keypad_rowsCounter][keypad_columnsCounter].writePin, low);
		
		if (port_readPin(&keypad_buttons[keypad_rowsCounter][keypad_columnsCounter].readPin) == keypad_activeLogic) {
			if (!keypad_buttons[keypad_rowsCounter][keypad_columnsCounter].pressed) {
				keypad_buttons[keypad_rowsCounter][keypad_columnsCounter].samplesCounter = (keypad_buttons[keypad_rowsCounter][keypad_columnsCounter].samplesCounter + 1) % (keypad_samplesNumber / keypad_rowsNumber);
				if (!keypad_buttons[keypad_rowsCounter][keypad_columnsCounter].samplesCounter) {
					keypad_buttons[keypad_rowsCounter][keypad_columnsCounter].pressed = true;
					keypad_buttons[keypad_rowsCounter][keypad_columnsCounter].typed = true;
				}
			} else {
				keypad_buttons[keypad_rowsCounter][keypad_columnsCounter].samplesCounter = 0;	// Debounce
				if (keypad_buttons[keypad_rowsCounter][keypad_columnsCounter].hold) {
					keypad_buttons[keypad_rowsCounter][keypad_columnsCounter].delayCounter = (keypad_buttons[keypad_rowsCounter][keypad_columnsCounter].delayCounter + 1) % (keypad_typeDelay_ms / keypad_rowsNumber);
					if (!keypad_buttons[keypad_rowsCounter][keypad_columnsCounter].delayCounter) {
						keypad_buttons[keypad_rowsCounter][keypad_columnsCounter].typed = true;
					}
				} else {
					keypad_buttons[keypad_rowsCounter][keypad_columnsCounter].delayCounter = (keypad_buttons[keypad_rowsCounter][keypad_columnsCounter].delayCounter + 1) % (keypad_holdDelay_ms / keypad_rowsNumber);
					if (!keypad_buttons[keypad_rowsCounter][keypad_columnsCounter].delayCounter) {
						keypad_buttons[keypad_rowsCounter][keypad_columnsCounter].hold = true;
					}
				}
			}
		} else {
			if (keypad_buttons[keypad_rowsCounter][keypad_columnsCounter].pressed) {
				keypad_buttons[keypad_rowsCounter][keypad_columnsCounter].samplesCounter--;
				if ( keypad_buttons[keypad_rowsCounter][keypad_columnsCounter].samplesCounter * -1 == (keypad_samplesNumber / keypad_rowsNumber) ) {
					keypad_buttons[keypad_rowsCounter][keypad_columnsCounter].samplesCounter = 0;
					keypad_buttons[keypad_rowsCounter][keypad_columnsCounter].pressed = false;
					keypad_buttons[keypad_rowsCounter][keypad_columnsCounter].hold = false;
					keypad_buttons[keypad_rowsCounter][keypad_columnsCounter].delayCounter = 0;
					keypad_buttons[keypad_rowsCounter][keypad_columnsCounter].typed = false;
				}
			} else {
				keypad_buttons[keypad_rowsCounter][keypad_columnsCounter].samplesCounter = 0;	// Debounce
			}
		}
		port_setPinDirection(&keypad_buttons[keypad_rowsCounter][keypad_columnsCounter].writePin, port_direction_input);
	}
	keypad_rowsCounter = (keypad_rowsCounter + 1) % keypad_rowsNumber;
}