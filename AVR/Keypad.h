#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <avr/interrupt.h>
#include "Types.h"
#include "Port.h"
#include "Timer0.h"

struct Keypad_Button {
	struct Pin writePin;
	struct Pin readPin;
	s8 samplesCounter;
	enum boolean pressed;
	enum boolean hold;
	u16 delayCounter;
	enum boolean typed;
};

// Intermediate Frequency 128 KHz (Cycle / ms)
#define keypad_intermediateFrequency_KHz 128
#define keypad_frequnciesNumber 5

#define keypad_rowsNumber 4
#define keypad_columnsNumber 4

#define keypad_activeLogic 0
#define keypad_samplesNumber 20

static void keypad_initTimer(u8 frequency_MHz);
static void keypad_initPins(struct Pin* writePins, struct Pin* readPins);
void keypad_init(u8 frequency_MHz, struct Pin* writePins, struct Pin* readPins);
void keypad_setDelays(u16 holdDelay_ms, u16 typeDelay_ms);
enum boolean keypad_isPressed(u8 rowNumber, u8 columnNumber);
enum boolean keypad_isTyped(u8 rowNumber, u8 columnNumber);

#endif /* KEYPAD_H_ */