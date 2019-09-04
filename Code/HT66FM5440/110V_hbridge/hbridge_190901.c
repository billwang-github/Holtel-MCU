#include "HT66FM5440.h"

typedef unsigned char boolean; /* Boolean value type. */
typedef unsigned long int uint32; /* Unsigned 32 bit value */
typedef unsigned short uint16; /* Unsigned 16 bit value */
typedef unsigned char uint8; /* Unsigned 8 bit value */
typedef signed long int int32; /* Signed 32 bit value */
typedef signed short int16; /* Signed 16 bit value */
typedef signed char int8; /* Signed 8 bit value */

#define LFQ  // PWM @ low frequency

/* Macro */
#define FEED_WATCHDOG() GCC_CLRWDT()
#define SET_PWM_DUTY(x)({\
	duty_now = x;\
	_dutr0h = (x >> 8) & 0xff;\
	_dutr0l = (x) & 0xff;\
	_pwmsuf = 1;\
	})

// 加減速時間
#define SPEED_TIME 2000 //ms
#define BRAKE_TIME 1000 //ms
/* PWM constants */
#ifndef LFQ
	#define PWM_PERIOD 100 // * 0.5us
	#define PWM_DUTY_MAX 98 // x 0.5us full PWM_PERIOD 
	#define PWM_DUTY_MIN 0 // x 0.5us full PWM_PERIOD 
	//#define PWM_STEPUP_DT 10 // (n+1)x 1ms 
	#define PWM_STEPUP_DUTY 1
	//#define PWM_STEPDOWN_DT 10 // (n+1)x 1ms 
	#define PWM_STEPDOWN_DUTY 1
#else
	#define PWM_PERIOD 200 // * 0.5us
	#define PWM_DUTY_MAX 196 // x 0.5us full PWM_PERIOD 
	#define PWM_DUTY_MIN 0 // x 0.5us full PWM_PERIOD 
	//#define PWM_STEPUP_DT SPEED_TIME/PWM_DUTY_MAX // (n+1)x 1ms 
	#define PWM_STEPUP_DUTY 1
	//#define PWM_STEPDOWN_DT BRAKE_TIME/PW_DUTY_MAX // (n+1)x 1ms 
	#define PWM_STEPDOWN_DUTY 1	
#endif
	
#define PWM_DEAD_TIME 0 // (dead time + 1)x0.5us

#define FWD 1
#define REV 0

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
#define PIN_FWD _pb0
#define PIN_REV _pb1
#define PIN_TEST _pb2
#define SP0 _pa3
#define SP1 _pa4
#define TESTO _pa5
//#define TO2 _pb2

// Define states
enum FSMSTATE {MOTOR_BRAKE, MOTOR_FWD, MOTOR_REV, MOTOR_SPEEDUP, MOTOR_SPEEDDOWN, STAT_MOTOR_TEST} curr_state;
enum KEYSTATE {KEY_FWD, KEY_REV, KEY_BRAKE} key;
 
/* Variables */
volatile unsigned int cnt_hall_period = 0;
volatile unsigned int duty_now = 0;
volatile unsigned int cnt_pwm_inc = 0, cnt_debounce  = 0, cnt_1ms = 0;
volatile unsigned char status_key_old = 0xff, status_key_now = 0x00;
volatile unsigned char ucRxData = 0;
volatile bit bOCP =0, bOVP = 0, bPauseDutyCnt = 1, bDIR = 0, bTestStart = 0, bKeyChange = 0, bRxData = 0;
const uint8 max_duty[] = { PWM_DUTY_MAX * 0.25, PWM_DUTY_MAX * 0.5, PWM_DUTY_MAX * 0.75, PWM_DUTY_MAX  };
volatile unsigned int pwm_duty_max =0;
volatile unsigned char pwm_stepup_dt = 0, pwm_stepdown_dt = 0;

/* functions */
void Motor_Init(void);
void Set_Motor_Fwd(void);
void Set_Motor_Rev(void);
void Set_Motor_FreeRun(void);
void Set_Motor_Brake(void);

void IO_Init(void);
void Comparator_Init(void);
void TM1_Init(void);
void TimeBase_Init(void);
void Uart_Init(void);
boolean Uart_Tx(uint8 txdata);

void main()
{

	IO_Init();
	//Comparator_Init();
	//TM1_Init();
	TimeBase_Init();
	//Uart_Init();
				
	Motor_Init();
	curr_state = MOTOR_BRAKE;
	Set_Motor_Brake();
	SET_PWM_DUTY(0);

	bOCP = 0;
	bOVP = 0;

	_emi = 1;
	cnt_1ms = 2000;
	while (cnt_1ms > 0) 
	{
		FEED_WATCHDOG();
	}	//delay 2 second
	
	if ((SP1 == 0) && (SP0 == 0))	
	{
		pwm_duty_max = max_duty[0];
	}
	else if ((SP1 == 0) && (SP0 == 1))
	{
		pwm_duty_max = max_duty[1];
	}		
	else if ((SP1 == 1) && (SP0 == 0))
	{
		pwm_duty_max = max_duty[2];
	}
	else 
	{
		pwm_duty_max = max_duty[3];
	}
	
	pwm_stepup_dt = SPEED_TIME/pwm_duty_max;
	pwm_stepdown_dt = BRAKE_TIME/pwm_duty_max;
			
	while (1)
	{	
		// check OVP
		GCC_CLRWDT();
		switch(curr_state){			
			case (MOTOR_REV) :
				Set_Motor_Rev();
				SET_PWM_DUTY(0);
				bDIR = REV;
				cnt_1ms = pwm_stepup_dt;
				if ((key == KEY_BRAKE) || (bOVP == 1) || (bOCP == 1))
					curr_state = MOTOR_BRAKE;
				else
					curr_state = MOTOR_SPEEDUP;
				break;
				
			case (MOTOR_FWD) :
				Set_Motor_Fwd();
				SET_PWM_DUTY(0);
				bDIR = FWD;
				cnt_1ms = pwm_stepup_dt;
				if ((key == KEY_BRAKE) || (bOVP == 1) || (bOCP == 1))
					curr_state = MOTOR_BRAKE;
				else
					curr_state = MOTOR_SPEEDUP;
				break;	
									
			case (MOTOR_SPEEDUP) :	
				if (cnt_1ms == 0)
				{
					cnt_1ms = pwm_stepup_dt;
					if ( duty_now <= (pwm_duty_max - PWM_STEPUP_DUTY))
					{
						duty_now += PWM_STEPUP_DUTY;
					}
					else
					{
						duty_now = pwm_duty_max;
					}
					SET_PWM_DUTY(duty_now);
				}
				if ((key == KEY_BRAKE) || ((key == KEY_FWD) && (bDIR == REV)) || ((key == KEY_REV) && (bDIR == FWD)))
				{
					cnt_1ms = pwm_stepdown_dt;
					curr_state = MOTOR_SPEEDDOWN;
				}
				if ((bOCP == 1) || (bOVP == 1))
					curr_state = MOTOR_BRAKE;
				break;
				
			case (MOTOR_SPEEDDOWN) :
				if (cnt_1ms == 0)
				{
					cnt_1ms = pwm_stepdown_dt;
					if (duty_now  >= (PWM_DUTY_MIN + PWM_STEPDOWN_DUTY))
					{
						duty_now -=PWM_STEPDOWN_DUTY;
					}
					else
						duty_now = PWM_DUTY_MIN;
					SET_PWM_DUTY(duty_now);
				}
				if ((duty_now == PWM_DUTY_MIN) || (bOCP == 1) || (bOVP == 1))
					curr_state = MOTOR_BRAKE;		
				break;
				
			case (MOTOR_BRAKE) :
				Set_Motor_Brake();
				bOCP = 0;
				bOVP = 0;	
				if (key == KEY_REV)
					curr_state = MOTOR_REV;
				else if (key == KEY_FWD)
					curr_state = MOTOR_FWD;	
				else
					curr_state = MOTOR_BRAKE;
				break;
				
			default :
				Set_Motor_Brake();
				curr_state = MOTOR_BRAKE;
				break;
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
	_dts = 0b11100000 | PWM_DEAD_TIME;   // dead time enabled, clock=fsys/8 = 0.5us
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
		
	Set_Motor_Brake();
}

void Set_Motor_Fwd(void)
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
	_frs = FWD;	
	_brke =0;	
	SET_PWM_DUTY(0);	
	_pwmon = 1;	
}

void Set_Motor_Rev(void)
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
	_frs = REV;	
	_brke =0;	
	SET_PWM_DUTY(0);	
	_pwmon = 1;	
}

void Set_Motor_Brake(void)
{
//	SPEED_DOWN();
//	bPauseDutyCnt = 0;
//	while (duty_now > 0) {FEED_WATCHDOG();}
	SET_PWM_DUTY(0);	
	_pwmon = 0;
	bPauseDutyCnt = 1;
	_brke = 1;	
}

void Set_Motor_FreeRun(void)
{
	_hdcen = 0;
	_brke = 0;
}

boolean Uart_Tx(uint8 txdata)
{
	uint8			errcnt = 0;

	while (1)
	{
		if (errcnt++ == 255)
			return 1;

		if (_txif)
			break;

		FEED_WATCHDOG();
	}

	_txr_rxr			= txdata;
	return 0;
}



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
	
	_pa3 = 1;
	_pa4 = 1;
	_papu3 = 1;
	_papu4 = 1;
	_pac3 = 1;
	_pac4 = 1;
	
	// TEST OUT
	_pa5 = 0;
	_pac5 = 0;
	
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

void Uart_Init(void)
{
	//baud rate	BRG(calculated)	BRG 	actural	baud rate	error(%)
	//==================================================================
	//9600		103.1666667 	103 	9615.384615 		0.16025641
	//14400		68.44444444 	68		4492.75362 		0.644122383
	//19200		51.08333333 	51		19230.76923 		0.16025641
	//38400		25.04166667 	25		38461.53846 		0.16025641
	//57600		16.36111111 	16		58823.52941 		2.124183007
	//76800		12.02083333 	12		76923.07692 		0.16025641
	//115200	7.680555556 	8		111111.1111 		-3.549382716
	//128000	6.8125			7		125000				-2.34375
	//256000	2.90625			3		250000				-2.34375


	_uarten = 1;	// enable uart pins	
	_adden = 0;		// address detect disabled
	_wake = 0;
	_rie = 1;		// RX interrupt enabled
	_tiie = 0;		// TX interrupt disabled
	_teie = 0;		// Transmitter empty interrupt is disabled	
	
	_bno = 0;		// 8b
	_pren = 0;		// parity none
	_stops = 0; 	// 1 stop bit
	_txbrk = 0; 	// no break

	_brgh = 1;		// high speed
	_brg = 8;		// 115200
	
	_txen = 1;
	_rxen = 1;	
	
	_uartf 				= 0;				
	_uarte				= 1; 	
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
	//unsigned int duty = 0;
	
	FEED_WATCHDOG();
	
	
	if (_tbf)
	{
		if (cnt_1ms > 0)
			cnt_1ms--;		
			
		if (cnt_debounce > 0) 
			cnt_debounce--;	
		else
		{
			cnt_debounce = DEBOUNCE_TIME;		
			status_key_old = status_key_now ;
			status_key_now = ~(PIN_TEST << 2| PIN_FWD << 1 | PIN_REV); // sample key status
			if (status_key_now != status_key_old) 
				bKeyChange = 1;
	
			if ((status_key_now & 0x07) == 0x02 )
			{
				key = KEY_FWD;
			}
			else if ((status_key_now & 0x07) == 0x01 )
			{
				key = KEY_REV;			
			}
	//		else if ((status_key_now & 0x07) == 0x04 ) // self-test mode
	//		{
	//			state_motor = STAT_MOTOR_TEST;
	//		}	
			else
				key = KEY_BRAKE; 
			
		}
		_tbf = 0;
	}
	
	if (_uartf)
	{
		if (_rxif)
		{
			_rxif				= 0;
			ucRxData 			= _txr_rxr;
			_uartf				= 0;
			bRxData 			= 1;
		}
	}	
	_int_pri15f = 0;

}

/*===============================================
1A => 51 @10mOhm	// OCPM setting
1A -> 50mV * 20
     ---------- * 255 = 51
        5V
===============================================*/
void Comparator_Init(void)
{
	_opoms = 0b01000011;	// Rising edge trigger, AV=20
	_opa0cal = 0b00010000; // offset cal off, normal mode

	_opcm = 200; //50mOhm, 4A
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
	//Set_Motor_Brake();
}

