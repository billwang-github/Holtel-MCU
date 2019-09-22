/*  =============================================================================
   馬達紅線接V     
	DWN(PB0): GB PWM 
	UP(PB1) : GC PWM	 
	TEST(PB2)
===================================================================================*/
#include "HT66FM5440.h"
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;


/* Macro */
#define FEED_WATCHDOG() GCC_CLRWDT()
	

/* IO definition */
#define PIN_DWN _pb0
#define PIN_UP _pb1
#define PIN_TESTIB _pb2
#define PIN_TESTO0 _pa3
#define PIN_TESTO1 _pa4
#define PIN_TESTO2 _pa5

// timer
#define TIME_TEST_UP_ON 2000
#define TIME_TEST_UP_OFF 3000
#define TIME_TEST_DWN_ON 2000
#define TIME_TEST_DWM_OFF 3000
volatile uint16 cnt_ms =0;
volatile uint8 cnt_10ms = 0, cnt_200ms = 0;
volatile bit f_ms = 0, f_10ms = 0, f_200ms = 0;

// Motor var 
#define ST_COAST 0 // all MOSFETs off
#define ST_STOP 1 // motor stopped
#define ST_BRAKE 2 // motor is braking
#define ST_UP 3 // motor runs in forward direction
#define ST_DOWN 4 // motor runs in reverse direction
#define ST_T_DIRSW 5
#define ST_T_UP 6
#define ST_T_DOWN 7
enum DIR {UP, DWN, STP} direction, direction_test;
volatile uint16 motor_current = 0;
volatile uint8 motor_state;

//PWM
#define SET_PWM_DUTY(x)({\
	_dutr0h = (x >> 8) & 0xff;\
	_dutr0l = (x) & 0xff;\
	_pwmsuf = 1;\
	})
// All off
#define DRV_COAST() ({\
	_pc     = 0b00000000;\
	_pcps0  = 0b00000000;\
	_pcps1  = 0b00000000;\
	})
// BB,CB ON
#define DRV_BRAKE() ({\
	_pc     = 0b00101000;\
	_pcps0  = 0b00000000;\
	_pcps1  = 0b00000000;\
	})
// BB,CB bottom PWM, BT, CT OFF
#define DRV_BRAKE_PWM() ({\
	_pc     = 0b00000000;\
	_pcps0  = 0b10000000;\
	_pcps1  = 0b00001000;\
	})	
// B PWM, CB ON
#define DRV_DWN() ({\
	_pc     = 0b00100000;\
	_pcps0  = 0b10100000;\
	_pcps1  = 0b00000000;\
	})
// C PWM, CB ON	
#define DRV_UP() ({\
	_pc     = 0b00001000;\
	_pcps0  = 0b00000000;\
	_pcps1  = 0b00001010;\
	})	
#define PWM_PERIOD 800
#define PWM_DUTY_MAX 750

volatile uint16 pwmduty_now = 0;
uint16 pwmduty_temp;

//ADC
#define CH_IAVG 7
#define CH_VDET 8
#define MAX_Im 0
#define B12 0
#define B10 1
volatile bit f_adc_ch = 0;
volatile uint16 iavg = 0, vdc[4], vdet;
volatile uint8 vdc_index = 0;
volatile uint16 vdc_sum = 0;

//UART
uint8 txbuff[6];
volatile uint8 rxbuff[6];
volatile uint8 rxcnt = 0, txcnt = 0;
const char ascii[] = "0123456789ABCDEF";

//others
bit f_testmode = 0;

// functions
void gpio_init(void);
void pwm_init(void);
void adc_init(uint8 res);
void uart_init(void);
void timeBase_init(void);
void handle_key(void);
uint16 adc_sample(uint8 ch);
uint8 ua_outchar(char c);
void print_byte(unsigned char b);
void print_string(const char *s);


int main(void)
{
	pwmduty_now = 0;
	motor_state = ST_BRAKE;
	direction_test = UP;

	gpio_init();
	adc_init(B12); // 12 
	uart_init();
	timeBase_init();
	pwm_init();
	_pwmon = 1;	
	_emi = 1;
	
	
	cnt_ms = 500;
	f_ms = 0; 
	
	while (f_ms == 0) // delay 500ms
	{
		FEED_WATCHDOG();
	}
	
						
	while(1)
	{						
		FEED_WATCHDOG();
					
		if (vdet >= 3470) // check VM OVP
			PIN_TESTO2 = 1;
		else if (vdet <= 3465)
			PIN_TESTO2 = 0;
			
		if (motor_current > MAX_Im) // Check motor current
			motor_state = ST_COAST;
					
		
		if (f_10ms) // every 10 mseconds
		{
			f_10ms = 0; // reset flag
			handle_key(); // ckeck key status	
							
									
			switch (motor_state)  // handle motor state
			{
				case ST_COAST: // wait for a system reset			
					pwmduty_now = 0;	
					break;

				case ST_BRAKE:			
					pwmduty_temp = 5; // break pwm delta
					if (pwmduty_now < pwmduty_temp)
					{
						pwmduty_now = 0;
						motor_state = ST_STOP;
					}						
					else
						pwmduty_now -= pwmduty_temp;				
					break;
									
				case ST_STOP:
					if (f_testmode == 0)
						direction_test = UP;
					if ((f_testmode == 1) && (f_ms == 1))
					{
						motor_state = ST_T_DIRSW;
					}
					else
					{						
						if (direction == DWN) // reverse ?
							motor_state = ST_DOWN;
						else if (direction == UP) // Forward ?
							motor_state = ST_UP;
					}
					break;
				case ST_T_DIRSW:					
					if (direction_test == UP)
					{
						cnt_ms = TIME_TEST_DWN_ON; // down on time 
						direction_test = DWN;
						motor_state = ST_T_DOWN;						
					}
					else if (direction_test == DWN)
					{
						cnt_ms = TIME_TEST_UP_ON; // up on time
						direction_test = UP;
						motor_state = ST_T_UP;						
					}
					else
						motor_state = ST_BRAKE;	
					f_ms = 0;							
					break;
				case ST_T_UP:
					if ((f_testmode == 0) || (f_ms == 1))
					{
						cnt_ms = TIME_TEST_UP_OFF; // up off time
						f_ms = 0;
						pwmduty_now = 400;		//越小剎車越快	
						motor_state = ST_BRAKE; // then brake !
					}
					else
					{
						pwmduty_temp = pwmduty_now + 10;  // ramp up pwm duty and check over max
						if (pwmduty_temp > PWM_DUTY_MAX)
							pwmduty_now = PWM_DUTY_MAX;
						else						
							pwmduty_now = pwmduty_temp;
					}						
					break;
				case ST_T_DOWN:
					if ((f_testmode == 0) || (f_ms == 1))
					{
						cnt_ms = TIME_TEST_DWM_OFF; // down off time
						f_ms = 0;
						pwmduty_now = 400;		//越小剎車越快	
						motor_state = ST_BRAKE; // then brake !
					}
					else
					{
						pwmduty_temp = pwmduty_now + 10;  // ramp up pwm duty and check over max
						if (pwmduty_temp > PWM_DUTY_MAX)
							pwmduty_now = PWM_DUTY_MAX;
						else						
							pwmduty_now = pwmduty_temp;
					}						
					break;		
				
				case ST_UP:							
					if (direction != UP) // not forward ?
					{					
						pwmduty_now = 400;		//越小剎車越快	
						motor_state = ST_BRAKE; // then brake !
					}
					else
					{
						pwmduty_temp = pwmduty_now + 10;  // ramp up pwm duty and check over max
						if (pwmduty_temp > PWM_DUTY_MAX)
							pwmduty_now = PWM_DUTY_MAX;
						else						
							pwmduty_now = pwmduty_temp;
					}
					break;
				
				case ST_DOWN:				
					if (direction != DWN) // not forward ?
					{					
						pwmduty_now = 400;		//越小剎車越快	
						motor_state = ST_BRAKE; // then brake !
					}
					else
					{
						pwmduty_temp = pwmduty_now + 10;  // ramp up pwm duty and check over max
						if (pwmduty_temp > PWM_DUTY_MAX)
							pwmduty_now = PWM_DUTY_MAX;
						else						
							pwmduty_now = pwmduty_temp;
					}
					break;
				
				default:
					motor_state = ST_COAST;
					break;
			}
		}
		
		if (f_200ms) // every 200 mseconds
		{
			f_200ms = 0; // reset flag
//			if (motor_state == ST_UP)
//				motor_state = ST_DOWN;
//			else
//				motor_state = ST_UP;
		}
	}		
}

void handle_key(void)
{	
	uint8 key_now;
	
	key_now = ~(PIN_TESTIB << 2| PIN_UP << 1 | PIN_DWN); // sample key status

	if ((key_now & 0x07) == 0x01 )
	{
		direction = DWN;
	}
	else if ((key_now & 0x07) == 0x02 )
	{
		direction = UP;			
	}
	else
		direction = STP;
		
	if ((key_now & 0x04) == 0x04 )
	{
		f_testmode = 1;		
	}			
	else
		f_testmode = 0;
}



/* I/O Setting */
void gpio_init(void)
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

	// TEST OUT	
	_pa3 = 0;
	_pa4 = 0;
	_pac3 = 0;
	_pac4 = 0;
	_pa5 = 0;
	_pac5 = 0;
				
}

void pwm_init(void)
{
	/* PWM output */
	_pc = 0x00;
	_pcc = 0x00;
//	_pcps0 = 0b10101010; // Set GxT, GxB I/O enabled
//	_pcps1 = 0b00001010;
		
	// PWMC
	_pwmms1 			= 0;						//0x:Edge-aligned mode				
	_pwmms0 			= 0;						//10: Center-aligned mode 1 11: Center-aligned mode 2

	_pwmon				= 0;						// pwm on	
	_pcks0				= 0;						// fpwm = 16MHz
	_pcks1				= 0;
	_pwmld				= 1;						// update prdr

	// PWMCS
	_pwmsuf 			= 1;						// dutr synchronous update request
	_pwmsu				= 1;						//	dutr synchronous update enable
	_pwmsv				= 1;						// duty written to dutr0 also written to dutr1~2	

	// DUTR0~2, PRDR
	_dutr0h 			= 0x00; 					// duty
	_dutr0l 			= 0x00;
	_pwmsuf 			= 1; 						// update duty
	_prdrh				= PWM_PERIOD >> 8; 			// 20kHz, 800	
	_prdrl				= PWM_PERIOD & 0xFF;




	// MCF
	_mskms				= 1;						// mask 0:hardware 1:software Note: pwmon must be enabled

	_mpwms				= 0;						// 1: non-complementary
	_mpwe				= 1;						// 0:pwm output disable
	_fmos				= 0;						// free run at PROTECTOC
	_pwms				= 1;						// top pwm output

	// PWMME
	_pwmme				= 0x00;						// 0: pwm 1:masked

	//PWMMD	
	_pwmmd				= 0x00;						// all off
	
	
	//DTS
//	_dts = 0b11100110;
	_dtcks1 			= 1;						// fsys/8 = 2MHz, 0.5us
	_dtcks0 			= 1;
	_dte 				= 1;						// enable dead time
	_dts 				= (_dts &= 0xe0);			// dead time 0.5us

	// PLC, Polarity Control
	_plc 				= 0;
	
	//====	Motor protection	====
	// MPTC1
	_pswd				= 0;						//software protection
	_pswps				= 0;						//
	_ahlps				= 0;	
	_isps				= 0;
	_capcps				= 0;
	_capops				= 0;		
	
	_pswe				= 0;						// disable SW protect	
	_ahlhe				= 0;	
	_ishe				= 0;
	_capche				= 0;	
	_capohe				= 0;	
	_ocpse				= 0;

	// MPTC2
	_isps				= 0;
	
	// OCPS
	_ocps 				= 0;						// output 0 when protectoc	
	
	_pwmpf = 0;
	_int_pri3f = 0;	
	_pwmpe = 1;
	_int_pri3e = 1;	

}


void __attribute ((interrupt(0x0c))) ISR_PWM(void) 
{
	FEED_WATCHDOG();
	_pwmpf = 0;
	_int_pri3f = 0;
	
	//SET_PWM_DUTY(pwmduty_now);			
	switch (motor_state)
	{
		case ST_COAST: // all off	
			SET_PWM_DUTY(pwmduty_now);			
			DRV_COAST();
			break;
		case ST_STOP: // low side on	
			SET_PWM_DUTY(pwmduty_now);						
			DRV_BRAKE();		
			break;
		case ST_BRAKE: 	
			SET_PWM_DUTY(pwmduty_now);					
			DRV_BRAKE_PWM();		
			break;
		case ST_UP: // BT,BB pwm, CB on, CT off
			SET_PWM_DUTY(pwmduty_now);					
			DRV_UP();
			break;
		case ST_DOWN: // CT,CB pwm, BB on, BT off
			SET_PWM_DUTY(pwmduty_now);					
			DRV_DWN();	
			break;
		case ST_T_UP: // BT,BB pwm, CB on, CT off
			SET_PWM_DUTY(pwmduty_now);					
			DRV_UP();
			break;
		case ST_T_DOWN: // CT,CB pwm, BB on, BT off
			SET_PWM_DUTY(pwmduty_now);					
			DRV_DWN();	
			break;	
		case ST_T_DIRSW:
			break;		
		default:
			break;
	}
}

void adc_init(uint8 res) //resolution 0: 12 1: 10
{

	
	//ADSTR Triggered A/D Conversion		
	//	Step 1
	//	Select the required A/D conversion clock by correctly programming bits ADCK2~ADCK0 in the
	//	ADCR1 register
	//	000: fSYS
	//	001: fSYS/2
	//	010: fSYS/4
	//	011: fSYS/8
	//	100: fSYS/16
	//	101: fSYS/32
	//	110: fSYS/64		
	_adck2				= 1;					
	_adck1				= 0;
	_adck0				= 0;
	//	Step 2
	//	Enable the A/D converter by clearing the ADOFF bit in the ADCR0 register to zero.	
	_adoff 				= 0; 						// ADC on	
	//	Step 3
	//	Select which signal is to be connected to the internal A/D converter by correctly configuring the
	//	ACS3~ACS0 bits in the ADCR0 register.
	_adcr0 &= 0xF0;
	_adcr0 |= 8; // select channel	
//	_acs3				= 0;
//	_acs2				= 0;
//	_acs1				= 0;
//	_acs0				= 0;	
	//	Step 4
	//	Select which pin is to be used as A/D input and configure it by correctly programming the
	//	corresponding bit in the pin-shared control register	
	_pa7s1 = 0; 	// AN6, IAVG
	_pa7s0 = 1;	
	_pa6s1 = 1;		// AN7, VDET
	_pa6s0 = 0;	
	//	Step 5
	//	Select A/D converter resolution and data format by setting the ADCRL_SEL bit in the ADCR2
	//	register and the ADRFS bit in the ADCR0 register.
	_adcrl_sel			= res;						// resolution 0: 12 1: 10
	_adrfs				= 1;						//12-bit data format (ADCRL_SEL=0):
													//0: High Byte=D[11:4]; Low Byte=D[3:0]
													//1: High Byte=D[11:8]; Low Byte=D[7:0]
													//10-bit data format (ADCRL_SEL=1):
													//0: High Byte=D[9:2]; Low Byte=D[1:0]
													//1: High Byte=D[9:8]; Low Byte=D[7:0]	
	//	Step 6
	//	If A/D conversion interrupt is used, the interrupt control registers must be correctly configured	
	_aeocf = 0;
	_aeoce = 1;
	_int_pri8f = 0;
	_int_pri8e = 1;
	
	//Others
	_ugb_on = 1; //unit gain buffer on
}

void __attribute ((interrupt(0x20))) ISR_Adc(void) 
{
	uint16 vdc_temp;
	FEED_WATCHDOG();	
	if (f_adc_ch == 1)
	{
		vdc_temp= (_adrh << 8) | _adrl;
		vdc_temp &= 0x0fff;
		vdc_sum -= vdc[vdc_index];
		vdc_sum += vdc_temp;
		vdc[vdc_index] = vdc_temp;
		vdc_index ++;
		vdc_index &= 3;
		vdet = (vdc_sum >> 2);
	}
	else
		iavg = (_adrh << 8) | _adrl;
	_aeocf = 0;
	_int_pri8f = 0;
} 

//0000: AN0
//0001: AN1
//0010: AN2
//0011: AN3
//0100: OPA2 output
//0101: OPA1 output
//0110: OPA0 output
//0111: AN6
//1000: AN7
uint16 adc_sample(uint8 ch)
{
//	uint16 result;
	_adcr0 &= 0xF0;
	_adcr0 |= ch; // select channel
	_adstr = 0; // start conversion
	_adstr = 1;
	_adstr = 0;
//	while (_eocb == 1)
//	{
//		FEED_WATCHDOG();
//	}
//	result = (_adrh << 8) | _adrl ;
	return 1;
}

void uart_init(void)
{
	uint8 i;
		
	_pb6s0=1;		//引腳共用功能設置 （設置RX）PB6--RX
	_pb6s1=0;
	_pb7s0=1;		//引腳共用功能設置 （設置TX）PB7--TX
	_pb7s1=0;
	
	_ucr1=0x80;		//使能UART、8位數據傳輸、奇偶校驗、一位停止位、無暫停字
	_ucr2=0xE4; 	//發送、接收使能、選擇高速波特率、無地址檢測功能、無喚醒功能、禁止發送空閒中斷、禁止發送寄存器空中斷
	_brg=103;       //_brg=16000000/(9600*16)-1=129  (高速波特率：波特率=fSYS/[16×(N+1)]、低速波特率：波特率=fSYS/[64×(N+1)])
	
	_uartf=0;		//UART中斷標誌清零
	_uarte=1;		//使能UART中斷
	
	_int_pri15f = 0;
	_int_pri15e = 1;
	
	rxcnt = 0;
	for (i = 0; i < 6; i++)
	{
		rxbuff[i] = 0;
	}	
}

void timeBase_init(void)
{
    _tbc = 0xc0; // 1.024ms
    _tbe = 1;
    _tbf = 0;
    _int_pri15e = 1;
    _int_pri15f = 0;
}

void __attribute ((interrupt(0x3c))) ISR_TimeBase_Uart(void) 
{
//	static uint16 cnt_ms =0;
//	static uint8 cnt_10ms = 0, cnt_200ms = 0;
	uint8 i;
		
	FEED_WATCHDOG();

	_int_pri15f = 0;
	
	if (_uartf == 1)
	{
		_uartf=0;		
	
		if (_rxif)
		{
			if (_txr_rxr == '#') // if '#' received, reset buffer
			{
				rxcnt = 0;
				for (i = 0; i < 6; i++)
				{
					rxbuff[i] = 0;
				}
			}		
			else if(rxcnt < 6) // if buff full, don't save
			{
				rxbuff[rxcnt]=_txr_rxr;		
				rxcnt++;	
			}	
		}
	}	
	
	if (_tbf)
	{
		if (f_adc_ch == 0) // adc sample voltage and current
		{	
			f_adc_ch = 1;
			adc_sample(CH_VDET);	
		}
		else
		{
			f_adc_ch = 0;
			adc_sample(CH_IAVG);		
		}	
				
		if (--cnt_ms == 0)
		{
			f_ms = 1; // toggles every 200 mseconds
		}
				
		if (++cnt_10ms > 10)
		{
			cnt_10ms = 0;
			f_10ms = 1; // toggles every 200 mseconds
		}
				
		if (++cnt_200ms > 200)
		{
			cnt_200ms = 0;
			f_200ms = 1; // toggles every 200 mseconds
		}
			
		_tbf = 0;
	}	

}


/*
	baud rate:9600
	==============
	command:
	#HHXXXX : XXXX => hall period in HEX
	#DDXXXX : XXXX => phase delay in HEX
*/
//void uart_handle(void)
//{
//	uint8 i;
//	
//	if (rxcnt >=6)
//	{
//		if ((rxbuff[0] == 'D') && (rxbuff[1] == 'D')) // change delay
//		{
//			phase_dly = hexstr2int(rxbuff + 2); 
//		}
//		
//		rxcnt = 0;
//		for (i = 0; i < 6; i++)
//		{
//			rxbuff[i] = 0;
//		}		
//	}	
//}


uint8 ua_outchar(char c)
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

	_txr_rxr			= c;
	return 0;	
}

void print_byte(unsigned char b)
{
	ua_outchar(ascii[b >> 4]);
	ua_outchar(ascii[b & 0x0f]);
}

void print_string(const char *s)
{
	while (*s)
	{
		if (*s == '\n')
			ua_outchar('\r'); // output a '\r' first
		ua_outchar(*s);
		s++;
	}
}