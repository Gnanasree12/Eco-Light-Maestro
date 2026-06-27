//LCD.h
#include "types.h"
void writeLCD(unsigned char data);
void cmdLCD(unsigned char cmd);
void charLCD(unsigned char ascii);
void InitLCD(void);
void strLCD(char* str);
void U32LCD(u32 n);
void S32LCD(s32 n);
void F32LCD(f32 f,u32 nDP);
void HexLCD(u32 n);
void BinLCD(u32 n,u32 nBD);
void BuildCGRAM(u8 *p,u32 nBytes);








