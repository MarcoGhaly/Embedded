#ifndef TYPES_H_
#define TYPES_H_

typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed long s32;
typedef unsigned long u32;
typedef signed long long s64;
typedef unsigned long long u64;

enum boolean {false, true};

struct Pin {u8 portNumber; u8 pinNumber;};

#define low 0
#define high 1

#define _8bit_max 0xFF
#define _16bit_max 0xFFFF
#define _32bit_max 0xFFFFFFFF

#endif /* TYPES_H_ */
