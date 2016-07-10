#ifndef COMPASS_H_
#define COMPASS_H_

#include <math.h>
#include "Types.h"
#include "MasterI2C.h"

#define compass_address 0x3C
#define compass_frequency_KHz 100

void compass_init();
u16 compass_getAngle();

#endif /* COMPASS_H_ */