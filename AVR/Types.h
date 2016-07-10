#ifndef TYPES_H_
#define TYPES_H_

#include <avr/io.h>

typedef int8_t s8;
typedef uint8_t u8;
typedef int16_t s16;
typedef uint16_t u16;
typedef int32_t s32;
typedef uint32_t u32;
typedef int64_t s64;
typedef uint64_t u64;

enum boolean {false, true};

struct Pin {u8 port; u8 pinNumber;};

#define low 0
#define high 1

#define _8bit_max 0xFF
#define _16bit_max 0xFFFF
#define _32bit_max 0xFFFFFFFF
#define _64bit_max 0xFFFFFFFFFFFFFFFF

#endif /* TYPES_H_ */