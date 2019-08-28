/*
	change PWM duty switches between two duty cycles for motor speed test
	modified from hall emulator code
*/
#include "HT66FM5440.h"

/* Macro */
#define FEED_WATCHDOG() GCC_CLRWDT()

/* hall emulator constants */
#define TM1_PERIOD 10 //us

/* Other Constants */

/* IO definition */
#define PWMO _pb0 // PWM output
#define TO0 _pb1
#define TO1 _pb2
#define ENAB _pa3 // enable
#define SPD_SEL _pa5 // speed selection


/* Variables */
volatile unsigned int cnt_pwm_period = 0;
volatile unsigned int pwm_period;
volatile unsigned int pwm_dly0 , pwm_dly1;
volatile unsigned char key_old = 0, key_new = 0;
volatile unsigned int cnt_debounce = 0;
volatile bit bkey_change = 0;

/* functions */
void PWM_PD_Init(unsigned int period, unsigned int duty);
void IO_Init(void);
void TM1_Init(void);
void TimeBase_Init(void);

void main()
{

	PWM_PD_Init(100, 0);
	IO_Init();
	//Comparator_Init();
	TM1_Init();
	TimeBase_Init();
		
	_emi = 1;
	
	bkey_change = 1; // force checking keys	
	while (1)
	{				
		if (bkey_change == 1)
		{
			if (ENAB == 0)
			{
				bkey_change = 0;
				if (SPD_SEL == 1)
					PWM_PD_Init(100, 40);
				else
					PWM_PD_Init(100, 20);
			}
			else
				PWM_PD_Init(100, 0);
		}
					
		FEED_WATCHDOG();
	}
}

/*  output period =  period x10us */
void PWM_PD_Init(unsigned int period, unsigned int duty)
{
	pwm_period = period; 
	pwm_dly0 = 0; 				pwm_dly1 = duty;
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

	_pa3 = 1; _pa4 = 1; _pa5 = 1;// set 1
	_papu3 = 1; _papu4 = 1; _papu5 = 1; // pull up
	_pac3 = 1; _pac4 = 1; _pac5 = 1; // input
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
	if (++cnt_pwm_period >= pwm_period)
		cnt_pwm_period = 0;
	
	if ((cnt_pwm_period >= pwm_dly0) && (cnt_pwm_period < pwm_dly1))
		PWMO = 1;
	else
		PWMO = 0;
	
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
	if (++cnt_debounce >=50)
	{
		cnt_debounce = 0;
		key_old = key_new; 
		key_new = (SPD_SEL << 1) | ENAB;
		if (key_old != key_new)
			bkey_change = 1;
	}
	
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

