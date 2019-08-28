/* 
	Sweep PWM duty from low to high and high to low , pwm frequency = 1KHz
	FOr LED dimming test
*/
#include "HT66FM5440.h"
/* Macro */
#define FEED_WATCHDOG() GCC_CLRWDT()
#define MOTOR_BRAKE() (_brke = 1)
#define SPEED_UP() (bDutyDir = 1)
#define SPEED_DOWN() (bDutyDir = 0)

/* PWM constants */
#define PWM_PERIOD 100 // * 0.5us
#define PWM_DUTY_MAX 100 // x 0.5us full PWM_PERIOD 
#define PWM_DUTY_MIN 90 // x 0.5us full PWM_PERIOD 
#define PWM_STEP_TIME 15 // x 1ms 
#define PWM_STEP_DUTY 1
#define DEAD_TIME 0 // (dead time + 1)x0.5us

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
#define CTRL_DOWN _pd1
#define CTRL_UP _pd0
#define TO0 _pb0
#define TO1 _pb1
#define TO2 _pb2


/* Variables */
volatile unsigned int cnt_hall_period = 0;
volatile unsigned int duty_now = 0;
volatile unsigned int cnt_pwm_inc = 0, cnt_debounce  = 0;
volatile unsigned char status_ctrl_old = 0xff, status_ctrl_now = 0x00;
volatile unsigned char key_pressed = 0;
volatile bit bOCP =0, bPauseDutyCnt = 1, bDutyDir = 0;
volatile unsigned int cnt_1ms = 0;

/* functions */
void Motor_Init(void);
void Motor_Up(void);
void Motor_Down(void);
void Motor_FreeRun(void);
void Motor_Break(void);
void Set_PWM_Duty(unsigned int duty);

void IO_Init(void);
void Comparator_Init(void);
void TM1_Init(void);
void TimeBase_Init(void);

void main()
{
	unsigned long int i = 0;

	IO_Init();
	//Comparator_Init();
	TM1_Init();
	TimeBase_Init();
		
	_emi = 1;
	

	Motor_Init();
	Motor_Break();
	_dte = 0; // dead time disabled
	Set_PWM_Duty(900);
	//while (1) {FEED_WATCHDOG();}
	Motor_Down();
			
	while (1)
	{			
		SPEED_UP();
		while (duty_now < PWM_DUTY_MAX) { FEED_WATCHDOG();}	
		cnt_1ms = 500;
		while (cnt_1ms > 0) FEED_WATCHDOG();
		SPEED_DOWN();
		while (duty_now > PWM_DUTY_MIN) {FEED_WATCHDOG();}
		cnt_1ms = 500;
		while (cnt_1ms > 0) FEED_WATCHDOG();		
	}
}

void Motor_Init(void)
{	
	/* PWM Setting */
    _pwmc = 0b00110001;	//edge aligned, fpwm/8 = 2MHz, PDDR reload	, fh=16MHz
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
	_frs = 1;	
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
	_frs = 0;	
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
	duty_now = 0;
	Set_PWM_Duty(duty_now);
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
void Set_PWM_Duty(unsigned int duty) 
{
	duty_now = duty;
	_dutr0h = (duty >> 8) & 0xff; // high byte first
	_dutr0l = (duty) & 0xff;
	_pwmsuf = 1; // update duty
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
	
	/* current sensing pin AP */
	_pa1s1 = 1;
	_pa1s0 = 0;
	
	/* control pins */
	_pdps0 &= 0b11000000; // pin share 

	_pd0 = 1; // set 1
	_pd1 = 1;
	_pd2 = 1;
	_pdpu0 = 1; // pull up
	_pdpu1 = 1;
	_pdpu2 = 1;
	_pdc0 = 1; // input
	_pdc1 = 1;
	_pdc2 = 1;
	
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
		
	if ((cnt_hall_period >= HA_DLY0) && (cnt_hall_period < HA_DLY1))
		TO0 = 1;
	else
		TO0 = 0;
		
	if ((cnt_hall_period >= HB_DLY0) && (cnt_hall_period < HB_DLY1))
		TO1 = 1;
	else
		TO1 = 0;
		
	if ((cnt_hall_period >= HC_DLY1) || (cnt_hall_period < HC_DLY0))
		TO2 = 1;
	else
		TO2 = 0;				
		
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
	
	if (cnt_debounce > 0) 
		cnt_debounce--;	
	else
	{
		status_ctrl_old = status_ctrl_now ;
		status_ctrl_now = (CTRL_DOWN << 1 | CTRL_UP); // sample key status
		cnt_debounce = 100; // every 10ms
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
				if (duty_now <= (PWM_DUTY_MAX - PWM_STEP_DUTY))
				{
					duty_now += PWM_STEP_DUTY;
				}
				else
					duty_now = PWM_DUTY_MAX;
			}
			else
			{
				if (duty_now  >= (PWM_DUTY_MIN + PWM_STEP_DUTY))
				{
					duty_now -=PWM_STEP_DUTY;
				}
				else
					duty_now = PWM_DUTY_MIN;
			}				
			Set_PWM_Duty(duty_now);
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

