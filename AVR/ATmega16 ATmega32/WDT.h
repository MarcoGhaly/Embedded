#ifndef WDT_H_
#define WDT_H_

#include "Types.h"

void WDT_enable();
void WDT_reset();
void WDT_disable();
u8 WDT_checkFlag();

#endif /* WDT_H_ */