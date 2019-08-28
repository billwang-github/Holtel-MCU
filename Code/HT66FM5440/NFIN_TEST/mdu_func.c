#include "HT66FM5440.h"
#include "mdu_func.h"

uint16 mul8x8(uint8 a, uint8 b)
{	
	uint16 u16tmp= 0;

	_mdu0r0 = a;
	_mdu0r1 = b;
	_md0s = 1;
	
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	
	u16tmp = (uint16)_mdu0r0;
	u16tmp |= ((uint16)_mdu0r1 << 8);

	return u16tmp;
}

void div8_8(uint8 *quo, uint8 *rem, uint8 a, uint8 b)
{		
	_mdu0r0 = a;
	_mdu0r1 = b;
	_md0s = 0;	

	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");	
	asm("nop");

	
	*quo = _mdu0r0;
	*rem = _mdu0r1;
}

uint32 mul16x16(uint16 a, uint16 b)
{	
	uint32 u32temp0 = 0;
	_mdu1r0 = (uint8)a;
	_mdu1r4 = (uint8)b;
	_mdu1r1	= (uint8)(a >> 8);
	_mdu1r5	= (uint8)(b >> 8);

	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");

	u32temp0 = (uint32)_mdu1r0;
	u32temp0 |= ((uint32)_mdu1r1 << 8);
	u32temp0 |= ((uint32)_mdu1r2 << 16);
	u32temp0 |= ((uint32)_mdu1r3 << 24);
	
	return u32temp0;
}

// a/b
void div16_16(uint16 *quo, uint16 *rem, uint16 a, uint16 b)
{	
	uint16 u16temp0 = 0;
//	asm("local u32temp1 db 4 dup (?)");

	_mdu1r0 = (uint8)a;
	_mdu1r1 = (uint8)(a >> 8);
	_mdu1r4	= (uint8)b;
	_mdu1r5	= (uint8)(b >> 8);

	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");

	u16temp0 = (uint16)_mdu1r0;
	u16temp0 |= ((uint16)_mdu1r1 << 8);
	*quo = u16temp0;
	u16temp0 = (uint16)_mdu1r4;
	u16temp0 |= ((uint16)_mdu1r5 << 8);
	*rem = u16temp0;	
}

// a/b
void div32_16(uint32 *quo, uint16 *rem, uint32 a, uint16 b)
{	
	uint16 u16tmp = 0;
	uint32 u32tmp = 0;
//	asm("local u32temp1 db 4 dup (?)");

	_mdu1r0 = (uint8)a;
	_mdu1r1 = (uint8)(a >> 8);
	_mdu1r2 = (uint8)(a >> 16);
	_mdu1r3 = (uint8)(a >> 24);	
	_mdu1r4	= (uint8)b;
	_mdu1r5	= (uint8)(b >> 8);

	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");	
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");		

	u32tmp = (uint32)_mdu1r0;
	u32tmp |= ((uint32)_mdu1r1 << 8);
	u32tmp |= ((uint32)_mdu1r2 << 16);
	u32tmp |= ((uint32)_mdu1r3 << 24);		
	*quo = u32tmp;
	
	u16tmp = (uint16)_mdu1r4;
	u16tmp |= ((uint16)_mdu1r5 << 8);
	*rem = u16tmp;	
}