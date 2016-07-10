#ifndef AC_H_
#define AC_H_

#include "Types.h"

void AC_init();
void AC_enableInterrupt();
void AC_disableInterrupt();
u8 AC_readOutputBit();
u8 AC_checkFlag();

#endif /* AC_H_ */