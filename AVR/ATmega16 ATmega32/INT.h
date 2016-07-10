#ifndef INT_H_
#define INT_H_

#include "Types.h"

#define INT_lowLevel 0
#define INT_logicalChange 1
#define INT_fallingEdge 2
#define INT_risingEdge 3

void INT_setMode(u8 interruptNumber, u8 mode);
void INT_enable(u8 interrupt);
void INT_disable(u8 interrupt);

#endif /* INT_H_ */