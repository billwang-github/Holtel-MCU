#include "HT66FM5440.h"

/* Macro */
#define FEED_WATCHDOG() GCC_CLRWDT()

/* hall emulator constants */
#define TM1_PERIOD 10 //us

/* Other Constants */

/* IO definition */
#define HA _pb0
#define HB _pb1
#define HC _pb2
#define SPEED _pa4
#define PWMO _pa5

// Define states
enum FSMSTATE {S0, S1, S2, S3, S4, S5, Sx} hall_state;

/* Variables */
volatile unsigned int cnt_hall_period = 0;
volatile unsigned int cnt_1ms = 0;
volatile unsigned int hall_period = 0 , hall_60d = 0 , hall_120d =0 , hall_180d = 0, hall_240d = 0, hall_300d = 0;
volatile unsigned int cnt_pwm_period = 0 , pwm_period = 0, pwm_duty = 0;

/* functions */
void IO_Init(void);
void Hall_Period_Init(unsigned int period);
void TimeBase_Init(void);
void TM1_Init(void);

void main()
{

	
	IO_Init();
	//Comparator_Init();

	TimeBase_Init();
	_emi = 1;
	cnt_1ms = 10;
	while (cnt_1ms > 0) // delay output
	{
		FEED_WATCHDOG();
	}
	
	pwm_period = 100; // 1KHz
	pwm_duty = 20; // 20% duty
	
	hall_state = S5;  // initial state = S5
	Hall_Period_Init(9960); // set hall at low frequency 
	TM1_Init();
			
	while (1)
	{	
		cnt_1ms = 20;
		while (cnt_1ms > 0) // 
		{
			FEED_WATCHDOG();
		}			
		
		if (hall_period > 498)
			Hall_Period_Init(hall_period -= 60);
		
		if (SPEED)
			pwm_duty = 40;
		else
			pwm_duty = 20;
				
		FEED_WATCHDOG();
	}
}


/*
	set hall_period variable
	period取6的倍數, 週期= period x 10us, 498=>200Hz, 996 => 100Hz
*/
void Hall_Period_Init(unsigned int period)
{
	if (hall_period != 0)
	{
		while (hall_state != S5 ) {FEED_WATCHDOG();}
		while (hall_state != S0 ) {FEED_WATCHDOG();}
	}
	
	hall_period = period; hall_60d = hall_period / 6 ; hall_120d = hall_period / 3 ; hall_180d = hall_period / 2;	
	hall_240d= hall_120d << 1; hall_300d = hall_180d + hall_120d; 
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
	_pa3 = 1; _pa4 = 1; // set 1
	_papu3 = 1; _papu4 = 1; // pull up
	_pac3 = 1; _pac4 = 1; // input
	
	/* PWM output */
	_pa5 = 0;
	_pac5 = 0;
}

void TM1_Init(void) // 16 bits counter
{
    _ptm1c0=0b00100000;   // tm1 clock = 1MHz
	_ptm1c1=0b11000001;	  // timer/counter mode, comp A match clear
	
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
	
	if (++cnt_pwm_period >= pwm_period)
		cnt_pwm_period = 0;
		
	if (cnt_pwm_period < pwm_duty)
		PWMO = 1;
	else
		PWMO = 0;
	
	if (++cnt_hall_period >= hall_period)
		cnt_hall_period = 0;
	
	switch (hall_state)
	{
		case S0 :
			if (cnt_hall_period == (hall_60d - 1))
			{ 
				HA = 1; HB = 0; HC = 0; 
				hall_state = S1;
			}
			break;
		case S1 :
			if (cnt_hall_period == (hall_120d - 1))
			{ 
				HA = 1; HB = 1; HC = 0; 
				hall_state = S2;
			}
			break;
		case S2 :
			if (cnt_hall_period == (hall_180d - 1))
			{ 
				HA = 0; HB = 1; HC = 0; 
				hall_state = S3;
			}
			break;
		case S3 :
			if (cnt_hall_period == (hall_240d - 1))
			{ 
				HA = 0; HB = 1; HC = 1; 
				hall_state = S4;
			}
			break;
		case S4 :
			if (cnt_hall_period == (hall_300d - 1))
			{ 
				HA = 0; HB = 0; HC = 1; 
				hall_state = S5;
			}
			break;									
		case S5 :
			if (cnt_hall_period == (hall_period - 1))
			{ 
				HA = 1; HB = 0; HC = 1; 
				hall_state = S0;
			}
			break;	
		default :
			HA = 0; HB = 0; HC = 0;
			break;
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

