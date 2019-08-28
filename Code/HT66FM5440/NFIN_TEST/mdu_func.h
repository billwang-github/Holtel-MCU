#ifndef _MDU_FUNC
#define _MDU_DUNC

//asm(" include HT66FM5440.inc ");

#define uint8 unsigned char
#define uint16 unsigned int
#define uint32 unsigned long

uint16 mul8x8(uint8 a, uint8 b);
void div8_8(uint8 *quo, uint8 *rem, uint8 a, uint8 b);
uint32 mul16x16(uint16 a, uint16 b);
void div16_16(uint16 *quo, uint16 *rem, uint16 a, uint16 b);
void div32_16(uint32 *quo, uint16 *rem, uint32 a, uint16 b);

#endif