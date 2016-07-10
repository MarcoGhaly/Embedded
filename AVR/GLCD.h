#ifndef Gglcd_H_
#define Gglcd_H_

#include "Types.h"
#include "Port.h"

#define glcd_write 0
#define glcd_read 1

#define glcd_command 0
#define glcd_data 1

#define glcd_firstPageAddress 0xB8
#define glcd_firstColumnAddress 0x40

#define glcd_command_displayControl 0x3E
#define glcd_busyFlagBit 7

#define glcd_side_side_left 0
#define glcd_side_right 1

#define glcd_state_off 0
#define glcd_state_on 1

void glcd_init(u8 rows, u8 columns, struct Pin* RS, struct Pin* RW, struct Pin* EN, struct Pin* CS1, struct Pin* CS2, u8 dataPort);
static void glcd_sendChar(u8 value, u8 type);
static u8 glcd_readChar();
void glcd_checkBusyFlag();
static void glcd_setPosition(u8 page, u8 column);
void glcd_setDot(u8 row, u8 column, enum boolean illuminated);
enum boolean glcd_isIlluminated(u8 row, u8 column);

#endif /* Gglcd_H_ */