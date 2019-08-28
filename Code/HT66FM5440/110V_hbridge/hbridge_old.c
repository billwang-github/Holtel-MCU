#include "HT66FM5440.h"
#define LFQ

/* Macro */
#define FEED_WATCHDOG() GCC_CLRWDT()
#define MOTOR_BRAKE() (_brke = 1)
#define SPEED_UP() (bDutyDir = 1)
#define SPEED_DOWN() (bDutyDir = 0)
#define SET_PWM_DUTY(duty)({\
	duty_now = duty;\
	_dutr0h = (duty >> 8) & 0xff;\
	_dutr0l = (duty) & 0xff;\
	_pwmsuf = 1;\
	})

/* PWM constants */
#ifndef LFQ
	#define PWM_PERIOD 100 // * 0.5us
	#define PWM_DUTY_MAX 90 // x 0.5us full PWM_PERIOD 
	#define PWM_DUTY_MIN 0 // x 0.5us full PWM_PERIOD 
	#define PWM_STEP_TIME 1 // (n+1)x 1ms 
	#define PWM_STEP_DUTY 1
#else
	#define PWM_PERIOD 200 // * 0.5us
	#define PWM_DUTY_MAX 190 // x 0.5us full PWM_PERIOD 
	#define PWM_DUTY_MIN 0 // x 0.5us full PWM_PERIOD 
	#define PWM_STEP_TIME 1 // (n+1)x 1ms 
	#define PWM_STEP_DUTY 2
#endif
	
#define DEAD_TIME 1 // (dead time + 1)x0.5us
/* key state */
#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_TEST 3
#define KEY_BREAK 4
#define KEY_NONE 0

#define UP 1
#define DOWN 0

/* others */
#define DEBOUNCE_TIME 100 // x1ms

/* hall emulator constants */
#define TM1_PERIOD 10 //us
#define HALL_PERIOD 996 // x10us
#define HALL_60D (HALL_PERIOD / 6)
#define HALL_120D (HALL_PERIOD / 3)
#define HALL_180D	(HALL_PERIOD >> 1)
#define HA_DLY0 0
#define HA_DLY1 HALL_180D //180 degree
#define HB_DLY0 HALL_120D // 120 degree
#define HB_DLY1 HB_DLY0 + HALL_180D
#define HC_DLY0 HALL_60D
#define HC_DLY1 HALL_120D + HALL_120D // 240 degree

/* Other Constants */

/* IO definition */
#define CTRL_DOWN _pb0
#define CTRL_UP _pb2
#define CTRL_TEST _pb1
//#define TO0 _pb0
//#define TO1 _pb1
//#define TO2 _pb2


/* Variables */
volatile unsigned int cnt_hall_period = 0;
volatile unsigned int duty_now = 0;
volatile unsigned int cnt_pwm_inc = 0, cnt_debounce  = 0, cnt_1ms = 0;
volatile unsigned char status_ctrl_old = 0xff, status_ctrl_now = 0x00, stat_key = KEY_BREAK ;
volatile unsigned char key_pressed = 0;
volatile bit bOCP =0, bPauseDutyCnt = 1, bDutyDir = 0, bTestStart = 0;

/* functions */
void Motor_Init(void);
void Motor_Up(void);
void Motor_Down(void);
void Motor_FreeRun(void);
void Motor_Break(void);

void IO_Init(void);
void Comparator_Init(void);
void TM1_Init(void);
void TimeBase_Init(void);

void main()
{
	IO_Init();
	//Comparator_Init();
	TM1_Init();
	TimeBase_Init();
		
	_emi = 1;
	

	Motor_Init();
	Motor_Break();
	cnt_1ms = 2000;
	while (cnt_1ms > 0) {FEED_WATCHDOG();}		
		
	while (1)
	{			
		if (stat_key == KEY_UP)	
		{
			Motor_Break();
			SET_PWM_DUTY(0);
			cnt_1ms = 100;
			while (cnt_1ms > 0) {FEED_WATCHDOG();}		
			Motor_Up();
			stat_key = KEY_NONE;
			bTestStart = 0;
		}
		else if (stat_key == KEY_DOWN)	
		{
			Motor_Break();
			SET_PWM_DUTY(0);
			cnt_1ms = 100;
			while (cnt_1ms > 0) {FEED_WATCHDOG();}	
			Motor_Down();
			stat_key = KEY_NONE;
		} 
		else if (stat_key == KEY_TEST)
		{
			if (bTestStart == 0 ) 
			{
				Motor_Break();
				SET_PWM_DUTY(0);
				cnt_1ms = 1000;
				while (cnt_1ms > 0) {FEED_WATCHDOG();}				
				bTestStart = 1;
				Motor_Up();
			}
			else
			{
				if (duty_now == PWM_DUTY_MAX)
				{
					cnt_1ms = 5000;
					while (cnt_1ms > 0) 
					{
						if (stat_key != KEY_TEST) break;
						FEED_WATCHDOG();
					}					
					Motor_Break();
					SET_PWM_DUTY(0);
					cnt_1ms = 2000;
					while (cnt_1ms > 0) 
					{
						if (stat_key != KEY_TEST) break;
						FEED_WATCHDOG();
					}	
					if (_frs == UP)
						Motor_Down();
					else
						Motor_Up();
				}
			}		
		}
		else if (stat_key == KEY_NONE)
		{			
			bTestStart = 0;
		}
		else
		{
			bTestStart = 0;
			Motor_Break();
			SET_PWM_DUTY(0);
			//stat_key = KEY_NONE;		
		}
															
		FEED_WATCHDOG();
	}
}

void Motor_Init(void)
{	
	/* PWM Setting */
	_pwmc = 0b00110001;	//edge aligned, fpwm/8 = 2MHz, PDDR reload	, fh=16MHz
//    #ifdef LFQ
//    _pwmms1 = 1; _pwmms0 = 0; // Center-aligned mode 1
//    #endif
	_pwmcs  = 0b00000111; //dutr update request, synchronous update, write to dutr0~2  
	_prdrh  = PWM_PERIOD >> 8; // 2MHz/1023=20KHz, high byte first
	_prdrl  = PWM_PERIOD & 0xFF;		
	_dutr3h = 0; // no pwm3 output, only for sine wave calculation
	_dutr3l = 0;
	_dutr0h = 0; // duty, high byte first
	_dutr0l = 0;
	_pwmsuf = 1; //if update the pwm duty, this bit must be set 
	
	/* Mask Setting */
	_mcf = 0b00000111;	// hw mask, complement output, pwm output enable, break at protection, top pwm
	_pwmmd = 0b00101010; // set low side mos on to break
	_pwmme = 0xff; // pwm mask is enabled

	
	/* Others */
	_dts = 0b11100000 | DEAD_TIME;   // dead time enabled, clock=fsys/8 = 0.5us
	_plc = 0x00; // non-inverting output
	
	/* hall sensor decoder */
	_integ0 = 0x00; // disable hall interrupt
	_hdcr = 0b11010101; // hall delay ckt disabled, 120 degree, software mode, break mode, hall decoder enabled
	_hdcd = 0; // sw hall signal
	_hdct0 = 0b00001001; // HBT on, HCB on, FRS=0
	_hdct1 = 0b00001001;
	_hdct2 = 0b00001001;
	_hdct3 = 0b00001001;
	_hdct4 = 0b00001001;
	_hdct5 = 0b00001001;
	_hdct6 = 0b00000110; // HCT on, HBB on, FRS=1
	_hdct7 = 0b00000110;
	_hdct8 = 0b00000110;
	_hdct9 = 0b00000110;
	_hdct10 = 0b00000110;
	_hdct11 = 0b00000110;
		
	MOTOR_BRAKE();
}

void Motor_Up(void)
{
//	_brke = 1;
//	_pwmon = 0;	
//	_hdcen = 1;
//	_hdcd = 1;			
//	_frs = 0;	
//	_brke =0;	
//	_pwmon = 1;	

	_hdcen = 1;
	_hdcd = 1;			
	_frs = UP;	
	_brke =0;	
	_pwmon = 1;	
	bPauseDutyCnt = 0;
	SPEED_UP();
}

void Motor_Down(void)
{		
//	_brke = 1;
//	_pwmon = 0;	
//	_hdcen = 1;	
//	_hdcd = 1;			
//	_frs = 1;	
//	_brke =0;	
//	_pwmon = 1;	
	_hdcen = 1;
	_hdcd = 1;			
	_frs = DOWN;	
	_brke =0;	
	_pwmon = 1;	
	bPauseDutyCnt = 0;
	SPEED_UP();
}

void Motor_Break(void)
{
//	SPEED_DOWN();
//	bPauseDutyCnt = 0;
//	while (duty_now > 0) {FEED_WATCHDOG();}
	
	_pwmon = 0;
	bPauseDutyCnt = 1;
	MOTOR_BRAKE();	
}

void Motor_FreeRun(void)
{
	_hdcen = 0;
	_brke = 0;
}


/* ===========================
	PWM period = 0x3FF(20KHz)
==============================*/
//void Set_PWM_Duty(unsigned int duty) 
//{
//	duty_now = duty;
//	_dutr0h = (duty >> 8) & 0xff; // high byte first
//	_dutr0l = (duty) & 0xff;
//	_pwmsuf = 1; // update duty
//}


/* I/O Setting */
void IO_Init(void)
{
	
	/* current sensing pin AP */
	_pa1s1 = 1;
	_pa1s0 = 0;
	
	/* control pins */
	_pdps0 &= 0b11000000; // pin share 

	_pb0 = 1; // set 1
	_pb1 = 1;
	_pb2 = 1;
	_pbpu0 = 1; // pull up
	_pbpu1 = 1;
	_pbpu2 = 1;
	_pbc0 = 1; // input
	_pbc1 = 1;
	_pbc2 = 1;
	
	/* PWM output */
	_pc = 0x00;
	_pcc = 0x00;
	_pcps0 = 0b10101010; // Set GxT, GxB I/O enabled
	_pcps1 = 0b00001010;			
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
	if (cnt_hall_period >= HALL_PERIOD)
		cnt_hall_period = 0;
	else
		cnt_hall_period++;
		
//	if ((cnt_hall_period >= HA_DLY0) && (cnt_hall_period < HA_DLY1))
//		TO0 = 1;
//	else
//		TO0 = 0;
//		
//	if ((cnt_hall_period >= HB_DLY0) && (cnt_hall_period < HB_DLY1))
//		TO1 = 1;
//	else
//		TO1 = 0;
//		
//	if ((cnt_hall_period >= HC_DLY1) || (cnt_hall_period < HC_DLY0))
//		TO2 = 1;
//	else
//		TO2 = 0;				
		
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
	unsigned int duty = 0;
	
	FEED_WATCHDOG();
	
	if (cnt_1ms > 0)
		cnt_1ms--;
	
	
	if (cnt_debounce > 0) 
		cnt_debounce--;	
	else
	{
		status_ctrl_old = status_ctrl_now ;
		status_ctrl_now = ~(CTRL_TEST << 2| CTRL_DOWN << 1 | CTRL_UP); // sample key status
		if (status_ctrl_now != status_ctrl_old)
		{		
			GCC_CLRWDT();
			if ((status_ctrl_now & 0x07) == 0x02 )
			{
				stat_key = KEY_UP;
			}
			else if ((status_ctrl_now & 0x07) == 0x01 )
			{
				stat_key = KEY_DOWN;			
			}
			else if ((status_ctrl_now & 0x07) == 0x04 ) // self-test mode
			{
				stat_key = KEY_TEST;
			}	
			else
				stat_key = KEY_BREAK;
		}	
		cnt_debounce = DEBOUNCE_TIME; 
	}
		
	
	if (cnt_pwm_inc < PWM_STEP_TIME) // increase duty every PWM_STEP_TIME 
		cnt_pwm_inc ++;
	else
	{
		cnt_pwm_inc = 0;
	
		if (bPauseDutyCnt == 0)		 
		{
			if (bDutyDir ==1)
			{
				duty = duty_now;
				if ( duty <= (PWM_DUTY_MAX - PWM_STEP_DUTY))
				{
					duty += PWM_STEP_DUTY;
				}
				else
					duty = PWM_DUTY_MAX;
			}
			else
			{
				if (duty  >= (PWM_DUTY_MIN + PWM_STEP_DUTY))
				{
					duty -=PWM_STEP_DUTY;
				}
				else
					duty = PWM_DUTY_MIN;
			}				
			SET_PWM_DUTY(duty);
		}		
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
	bOCP = 1;
}

