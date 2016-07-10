#ifndef WDT_H_
#define WDT_H_

#define WDT_16K 0
#define WDT_32K 1
#define WDT_64K 2
#define WDT_128K 3
#define WDT_256K 4
#define WDT_512K 5
#define WDT_1024K 6
#define WDT_2048K 7

void WDT_setCountsNumber(byte countsNumber);
void WDT_enable();
void WDT_reset();
void WDT_disable();
byte WDT_checkFlag();

#endif /* WDT_H_ */