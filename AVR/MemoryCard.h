#ifndef MEMORYCARD_H_
#define MEMORYCARD_H_

#include "Types.h"
#include "MasterSPI.h"

#define memoryCard_activeLevel 0
#define memoryCard_frequency_KHz 400
#define memoryCard_blockSize_bytes 512

#define memoryCard_command_resetCard 0
#define memoryCard_command_initialize 1
#define memoryCard_command_readSingleBlock 17

void memoryCard_init(u8 frequency_MHz, struct Pin* slavePin);
u8 memoryCard_sendCommand(u8 cmd, u32 argument);
void memoryCard_setReadMode(u32 address);
u8 memoryCard_readNextByte();

#endif /* MEMORYCARD_H_ */