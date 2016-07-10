#ifndef PUSHBUTTONS_H_
#define PUSHBUTTONS_H_

#include <avr/interrupt.h>
#include "Types.h"
#include "Port.h"
#include "Timer0.h"

struct Button {
	struct Pin pin;
	s8 samplesCounter;
	enum boolean pressed;
	enum boolean hold;
	u16 delayCounter;
	enum boolean typed;
};

// Intermediate Frequency 128 KHz (Cycle / ms)
#define pushButtons_intermediateFrequency_KHz 128
#define pushButtons_frequnciesNumber 5

#define pushButtons_buttonsNumber 8
#define pushButtons_activeLogic 0

#define pushButtons_samples 20

static void pushButtons_initTimer(u8 frequency_MHz);
static void pushButtons_initPins(struct Pin* pins);
void pushButtons_init(u8 frequency_MHz, struct Pin* pins);
void keypad_setDelays(u16 holdDelay_ms, u16 typeDelay_ms);
enum boolean pushButtons_isPressed(u8 buttonNumber);
enum boolean pushButtons_isTyped(u8 buttonNumber);

#endif /* PUSHBUTTONS_H_ */