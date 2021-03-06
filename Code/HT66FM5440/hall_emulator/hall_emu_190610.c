#include "HT66FM5440.h"

/* Macro */
#define FEED_WATCHDOG() GCC_CLRWDT()

/* hall emulator constants */
#define TM1_PERIOD 10 //us
//#define HALL_PERIOD 498 // x10us, ��6������, 489=>200Hz, 996 => 100Hz
//#define HALL_60D (HALL_PERIOD / 6)
//#define HALL_120D (HALL_PERIOD / 3)
//#define HALL_180D	(HALL_PERIOD >> 1)
//#define HA_DLY0 0
//#define HA_DLY1 HALL_180D //180 degree
//#define HB_DLY0 HALL_120D // 120 degree
//#define HB_DLY1 HB_DLY0 + HALL_180D
//#define HC_DLY0 HALL_60D
//#define HC_DLY1 HALL_120D + HALL_120D // 240 degree

/* Other Constants */

/* IO definition */
#define TO0 _pb0
#define TO1 _pb1
#define TO2 _pb2
#define ENAB _pa3
#define REVB _pa4

/* Variables */
volatile unsigned int cnt_hall_period = 0;
volatile unsigned int cnt_1ms = 0;
volatile unsigned int hall_period , hall_60d  , hall_120d , hall_180d;
volatile unsigned int ha_dly0 , ha_dly1, hb_dly0, hb_dly1, hc_dly0, hc_dly1;

/* functions */
void TimeBase_Init(void);
void Hall_Period_Init(unsigned int period);
void IO_Init(void);
void TM1_Init(void);

void main()
{

	Hall_Period_Init(498);
	IO_Init();
	//Comparator_Init();

	TimeBase_Init();
	_emi = 1;
	cnt_1ms = 100;
	while (cnt_1ms > 0)
	{
		FEED_WATCHDOG();
	}
	TM1_Init();

		
	while (1)
	{																
		FEED_WATCHDOG();
	}
}

void Hall_Period_Init(unsigned int period)
{
	hall_period = period; hall_60d = hall_period / 6; hall_120d = hall_period / 3; hall_180d = hall_period / 2;
	ha_dly0 = 0; 				ha_dly1 = hall_180d;
	hb_dly0 = hall_120d; 		hb_dly1 = hall_120d + hall_180d;
	hc_dly0 = hall_60d;			hc_dly1 = hall_120d + hall_120d;
}

/* I/O Setting */
void IO_Init(void)
{
	/* Hall emulator output */
	_pb0 = 0;
	_pbc0 = 0;	
	_pb1 = 0;
	_pbc1 = 0;	
	_pb2 = 0;
	_pbc2 = 0;		
	
	/* control pins */
	_pdps0 &= 0b11000000; // pin share 

	_pa3 = 1; _pa4 = 0; // set 1
	_papu3 = 1; _papu4 = 1; // pull up
	_pac3 = 1; _pac4 = 1; // input
}

void TM1_Init(void) // 16 bits counter
{
    _ptm1c0=0b00100000;   // tm1 clock = 1MHz
	_ptm1c1=0b11000001;	// timer/counter mode, comp A match clear
	
	_ptm1al= TM1_PERIOD & 0xff; // low byte first
	_ptm1ah=TM1_PERIOD >> 8;

	_int_pri11f = 0;
	_tm1af = 0;		
	_tm1ae = 1;
	_int_pri11e = 1;
	
	_pt1on = 0;
	_pt1on = 1;
}

void __attribute ((interrupt(0x2c))) ISR_TM1()
{  
	FEED_WATCHDOG();
	if (++cnt_hall_period >= hall_period)
		cnt_hall_period = 0;
	
//	if (ENAB == 0)
	if (1)
	{	
		if (REVB == 1)
		{
			if ((cnt_hall_period >= ha_dly0) && (cnt_hall_period < ha_dly1))
				TO0 = 1;
			else
				TO0 = 0;
				
			if ((cnt_hall_period >= hb_dly0) && (cnt_hall_period < hb_dly1))
				TO1 = 1;
			else
				TO1 = 0;
				
			if ((cnt_hall_period >= hc_dly0) || (cnt_hall_period < hc_dly1))
				TO2 = 1;
			else
				TO2 = 0;
		}
		else
		{
			if ((cnt_hall_period >= ha_dly0) && (cnt_hall_period < ha_dly1))
				TO2 = 1;
			else
				TO2 = 0;
				
			if ((cnt_hall_period >= hb_dly0) && (cnt_hall_period < hb_dly1))
				TO1 = 1;
			else
				TO1 = 0;
				
			if ((cnt_hall_period >= hc_dly0) || (cnt_hall_period < hc_dly1))
				TO0 = 1;
			else
				TO0 = 0;
		}						
	}
	else
	{
		TO0 = 0;
		TO1	= 0;
		TO2 = 0;
	}
	
	_int_pri11f = 0;
	_tm1af = 0;	
}

void TimeBase_Init(void)
{
    _tbc = 0xc0; // 1.024ms
    _tbe = 1;
    _tbf = 0;
    _int_pri15e = 1;
    _int_pri15f = 0;
}

void __attribute ((interrupt(0x3c))) ISR_TimeBase(void) 
{
	FEED_WATCHDOG();
	if (cnt_1ms > 0)
		cnt_1ms--;
	_int_pri15f = 0;
    _tbf = 0;
}

/*===============================================
1A=>10.2 @10mOhm	// OCPM setting
1A -> 10mV * 20
     ---------- * 255 = 10.2
        5V
===============================================*/
void Comparator_Init(void)
{
	_opoms = 0b01000011;	// Rising edge trigger, AV=20
	_opa0cal = 0b00110000; // offset cal off, normal mode

	_opcm = 30; // 10mOhm, 3A
	_c0en = 1; // enable OCP comparator
	_ishe = 1; // enable OCP hw protection
	_ocpse = 0; // reset PROCTECTOC			
	_ocpse = 1;			
	_ocps = 0b00101010; // low side MOS turn on if OCP
	_int_pri2e = 1;
	_int_pri2f = 0;
}


//===============================================
//
//===============================================
void __attribute ((interrupt(0x08))) ISR_OCP(void)
{
	_int_pri2f = 0;
}

