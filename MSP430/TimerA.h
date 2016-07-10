#ifndef TIMERA_H_
#define TIMERA_H_

#include <msp430.h>
#include "Types.h"

#define timerA_clockSource_TACLK 0
#define timerA_clockSource_ACLK 1
#define timerA_clockSource_SMCLK 2
#define timerA_clockSource_INCLK 3

#define timerA_mode_stop 0
#define timerA_mode_up 1
#define timerA_mode_continuous 2
#define timerA_mode_upDown 3

#define timerA_clockDivider_1 0
#define timerA_clockDivider_2 1
#define timerA_clockDivider_4 2
#define timerA_clockDivider_8 3

void timerA_start(u8 timerNumber);
void timerA_stop(u8 timerNumber);
void timerA_setClockSource(u8 timerNumber, u8 clockSource);
void timerA_setMode(u8 timerNumber, u8 mode);
void timerA_setDivider(u8 timerNumber, u8 prescaler);
void timerA_setCounterValue(u8 timerNumber, u16 value);
u16 timerA_getCounterValue(u8 timerNumber);
void timerA_setCompareValue(u8 timerNumber, u8 compareNumber, u16 value);
void timerA_setCompareInterruptEnabled(u8 timerNumber, u8 compareNumber, enum boolean enable);
void timerA_setInterruptEnabled(u8 timerNumber, enum boolean enable);
u8 timerA_checkCompareFlag(u8 timerNumber, u8 compareNumber);
u8 timerA_checkFlag(u8 timerNumber);

#endif /* TIMERA_H_ */
