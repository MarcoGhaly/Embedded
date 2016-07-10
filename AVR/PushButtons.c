#include "PushButtons.h"

static struct Button pushButtons_buttons[pushButtons_buttonsNumber];
static u16 pushButtons_holdDelay_ms = 500;
static u16 pushButtons_typeDelay_ms = 100;

// Initialize Timer
static void pushButtons_initTimer(u8 frequency_MHz) {
	u16 pushButtons_timer0Dividers[pushButtons_frequnciesNumber] = {1, 8, 64, 256, 1024};
	u16 divider = (u16)(frequency_MHz * 1000 / pushButtons_intermediateFrequency_KHz);
	u8 i;
	for (i = 0; i < pushButtons_frequnciesNumber; i++) {
		if (divider / pushButtons_timer0Dividers[i] == 0) {
			divider = pushButtons_timer0Dividers[i];
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
static void pushButtons_initPins(struct Pin* pins) {
	u8 i;
	for (i = 0; i < pushButtons_buttonsNumber; i++) {
		pushButtons_buttons[i].pin.port = pins[i].port;
		pushButtons_buttons[i].pin.pinNumber = pins[i].pinNumber;
		pushButtons_buttons[i].samplesCounter = 0;
		pushButtons_buttons[i].pressed = false;
		pushButtons_buttons[i].hold = false;
		pushButtons_buttons[i].delayCounter = 0;
		pushButtons_buttons[i].typed = false;
		// Input & Pull-ups
		port_setPinDirection(&pins[i], port_direction_input);
		port_writePin(&pins[i], high);	// Pull-up resistor
	}
}

// Initialize
void pushButtons_init(u8 frequency_MHz, struct Pin* pins) {
	pushButtons_initPins(pins);
	pushButtons_initTimer(frequency_MHz);
}

// Set Delays
void keypad_setDelays(u16 holdDelay_ms, u16 typeDelay_ms) {
	pushButtons_holdDelay_ms = holdDelay_ms;
	pushButtons_typeDelay_ms = typeDelay_ms;
}

// Is Pressed
enum boolean pushButtons_isPressed(u8 buttonNumber) {
	return (pushButtons_buttons[buttonNumber].pressed);
}

// Is Typed
enum boolean pushButtons_isTyped(u8 buttonNumber) {
	enum boolean typed = pushButtons_buttons[buttonNumber].typed;
	pushButtons_buttons[buttonNumber].typed = false;
	return typed;
}

// Timer Interrupt
ISR (TIMER0_COMP_vect) {
	u8 pushButtons_counter;
	for (pushButtons_counter = 0; pushButtons_counter < pushButtons_buttonsNumber; pushButtons_counter++) {
		if (port_readPin(&pushButtons_buttons[pushButtons_counter].pin) == pushButtons_activeLogic) {
			if (!pushButtons_buttons[pushButtons_counter].pressed) {
				pushButtons_buttons[pushButtons_counter].samplesCounter = (pushButtons_buttons[pushButtons_counter].samplesCounter + 1) % pushButtons_samples;
				if (!pushButtons_buttons[pushButtons_counter].samplesCounter) {
					pushButtons_buttons[pushButtons_counter].pressed = true;
					pushButtons_buttons[pushButtons_counter].typed = true;
				}
			} else {
				pushButtons_buttons[pushButtons_counter].samplesCounter = 0;
				if (pushButtons_buttons[pushButtons_counter].hold) {
					pushButtons_buttons[pushButtons_counter].delayCounter = (pushButtons_buttons[pushButtons_counter].delayCounter + 1) % pushButtons_typeDelay_ms;
					if (!pushButtons_buttons[pushButtons_counter].delayCounter) {
						pushButtons_buttons[pushButtons_counter].typed = true;
					}
				} else {
					pushButtons_buttons[pushButtons_counter].delayCounter = (pushButtons_buttons[pushButtons_counter].delayCounter + 1) % pushButtons_holdDelay_ms;
					if (!pushButtons_buttons[pushButtons_counter].delayCounter) {
						pushButtons_buttons[pushButtons_counter].hold = true;
					}
				}
			}
		} else {
			if (pushButtons_buttons[pushButtons_counter].pressed) {
				pushButtons_buttons[pushButtons_counter].samplesCounter--;
				if (pushButtons_buttons[pushButtons_counter].samplesCounter * -1 == pushButtons_samples) {
					pushButtons_buttons[pushButtons_counter].samplesCounter = 0;
					pushButtons_buttons[pushButtons_counter].pressed = false;
					pushButtons_buttons[pushButtons_counter].hold = false;
					pushButtons_buttons[pushButtons_counter].delayCounter = 0;
					pushButtons_buttons[pushButtons_counter].typed = false;
				}
			} else {
				pushButtons_buttons[pushButtons_counter].samplesCounter = 0;
			}
		}
	}
}