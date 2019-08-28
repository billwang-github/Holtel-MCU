/*  last modified by Bill Wang: 2019/08/16
	test NFIN noise filter, PTM0 capture , MDU, UART
	1. PA6 is pulse output , PA7 is pulse input, PA5 is filtered pulse output
		connect PA6 to PA7, watch the PA5
	2. delay time is (NF_VIH[4:0] - NF_VIL[4:0]) x 5us	
	3. iph: pulse high time, ipl: pulse low time unit:4us	
	4. use MDU to calculate duty cycle = iph * 100 / (iph + ipl)
	5. print duty to UART , baud rate:9600
*/
#include "HT66FM5440.h"
//asm(" include HT66FM5440.inc ");
#include <string.h>
#include "mdu_func.h"

#define uint8 unsigned char
#define uint16 unsigned int
#define uint32 unsigned long
#define FEEDWATCHDOG() GCC_CLRWDT()

#define PULSE_OUT _pa6
#define FILT_OUT _pa5

/* captm */
volatile uint8 cnt_ov = 255; // ptm0 overflow counter
volatile uint16 iph = 0, ipl = 0; // pulse width

/* time base */
volatile uint16 cnt1_1ms = 0, cnt2_1ms = 0;
volatile bit bTimeup1 = 0, bTimeup2 = 0;

/* UART*/
char txbuff[32];
volatile char rxbuff[6];
volatile uint8 rxcnt = 0, txcnt = 0;

uint32 u32temp;
uint16 u16temp0, u16temp1;
uint32 u32temp0;
uint8 duty = 0;

void Init_GPIO(void);
void Init_NFIN(void);
void Init_PTM0(void);
void Init_TimeBase(void);
void Init_Uart(void);

void print_string(char txdata[], uint8 cnt);
void byte2str10(char *str, uint8 num);
void int2str10(char *str, uint16 num);

void main()
{		
	uint8 i;
	
	Init_GPIO();
	Init_NFIN();
	Init_PTM0();
	Init_TimeBase();
	Init_Uart();
	
	strncpy(txbuff, "Hello World!!\r\n", 15);
	print_string(txbuff, 15);
	_emi = 1;
	
	while (1)
	{
		FEEDWATCHDOG();
/* test PTM0 capture and print to uart */		
		_nf_byps = 1; // bypass noise filter
		if (bTimeup1 == 1)
		{
			bTimeup1 = 0;
			cnt1_1ms = 1000;	// 1秒測一次
			for (i = 0; i < 2; i++){
				GCC_DELAY(3200); //200u
				PULSE_OUT = 0;
				GCC_DELAY(16000); // 1000u
				PULSE_OUT = 1;	
			}
			
			u32temp0 = mul16x16(iph, 100);
			div32_16(&u32temp, &u16temp0, u32temp0, (iph + ipl));
			duty = (uint8)u32temp;	
			byte2str10(txbuff, duty);
			txbuff[3] = ':';
			int2str10(txbuff + 4, iph);
			txbuff[9] = ':';
			int2str10(txbuff + 10, ipl );			
			txbuff[15] = '\r';	// add new line char
			txbuff[16] = '\n';
			print_string(txbuff, 17); //print duty:iph:ipl to uart		

			for (i = 0; i < 2; i++){
				GCC_DELAY(4800); //300u
				PULSE_OUT = 0;
				GCC_DELAY(16000); // 1000u
				PULSE_OUT = 1;	
			}
			
			u32temp0 = mul16x16(iph, 100);
			div32_16(&u32temp, &u16temp0, u32temp0, (iph + ipl));
			duty = (uint8)u32temp;	
			byte2str10(txbuff, duty);
			txbuff[3] = ':';
			int2str10(txbuff + 4, iph);
			txbuff[9] = ':';
			int2str10(txbuff + 10, ipl );			
			txbuff[15] = '\r';	// add new line char
			txbuff[16] = '\n';
			print_string(txbuff, 17); //print duty:iph:ipl to uart				
		}		
							
		
/* test noise filter  , reset _nf_byps to 0 to enable noise filter */		
//		_nf_byps = 0; // enable noise filter
//		GCC_DELAY(40); //2.5u
//		PULSE_OUT = 0;
//		GCC_DELAY(240);
//		PULSE_OUT = 1;		
//		GCC_DELAY(100); //6.25u
//		PULSE_OUT = 0;
//		GCC_DELAY(240);
//		PULSE_OUT = 1;
//		GCC_DELAY(160); //10u
//		PULSE_OUT = 0;
//		GCC_DELAY(240);
//		PULSE_OUT = 1;				
//		GCC_DELAY(240); //15u
//		PULSE_OUT = 0;
//		GCC_DELAY(240);
//		PULSE_OUT = 1;				
	}
}

void Init_GPIO(void)
{
	_pa6 = 0;
	_pac6 = 0; // pa6 as pulse output	
	
	_pa5 = 0; // pa5 as filter output
	_pac5 = 0;
}

void Init_NFIN(void)
{
	_pa7 = 1;
	_pac7 = 1; // NFIN as input

	/* noise filter  (NF_VIH[4:0] - NF_VIL[4:0]) x 5us */	
	_nf_vih &= 0xE0; 
	_nf_vil &= 0xE0;
	_nf_vih |= 1; // 5us sample rate
	_nf_vil |= 0;
	_nf_byps = 1; // 1:bypass noise filter
	_cins = 1; //1:data_out to ptm0

	_nfis1 = 1; //00: Disable
	_nfis0 = 1;	//01: Rising edge trigger		
				//10: Falling edge trigger
				//11: Dual edge trigger	
	
	_int_pri13f = 0;	
	_int_pri13e = 1;	
}

void Init_PTM0(void)
{	
	/* PTM0 setup */
	_ptm0c0 = 0b00110000; //fh/64 = 4us
	_ptm0c1 = 0b01100010; //capture mode, latched into CCRA at falling edge and into CCRB at rising edge
						  //from tck0
	_ptm0c2 = 0b00000110; //TPn_0/TCKn dual edge clear, tm0af will be triggered
	_pt0on = 1; 
	// interrupts
	_tm0pf = 0;
	_tm0af = 0;
	_tm0pe = 1;
	_tm0ae = 1;
	_int_pri10f = 0;
	_int_pri10e = 1;	
}

void Init_TimeBase(void)
{
    _tbc = 0xc0; // 1.024ms
    _tbe = 1;
    _tbf = 0;
    _int_pri15e = 1;
    _int_pri15f = 0;
}

void Init_Uart(void)
{
	uint8 i;
		
	_pb6s0=1;		//引腳共用功能設置 （設置RX）PB6--RX
	_pb6s1=0;
	_pb7s0=1;		//引腳共用功能設置 （設置TX）PB7--TX
	_pb7s1=0;
	
	_ucr1=0x80;		//使能UART、8位數據傳輸、奇偶校驗、一位停止位、無暫停字
	_ucr2=0xE4; 	//發送、接收使能、選擇高速波特率、無地址檢測功能、無喚醒功能、禁止發送空閒中斷、禁止發送寄存器空中斷
	_brg=103;       //_brg=16000000/(9600*16)-1=103  (高速波特率：波特率=fSYS/[16×(N+1)]、低速波特率：波特率=fSYS/[64×(N+1)])
	
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

DEFINE_ISR(ISR_NFIN,0x34);
/*****************************************/
void ISR_NFIN(void)
{
	_int_pri13f = 0;
	if (PULSE_OUT == 0)
		FILT_OUT = 0;
	else
		FILT_OUT = 1;
}

DEFINE_ISR(ISR_PTM0,0x28);
/*****************************************/
void ISR_PTM0(void)
{
	uint8 u8tmph, u8tmpl;
	
	if (_tm0pf)
	{
		if (cnt_ov < 0xff)
			cnt_ov++;
		_tm0pf = 0;
	}
	
	if (_tm0af)
	{
		cnt_ov = 0; // if edge trigger appears reset overflow counter
		if (_pt0vlf) //rising edge, save CCRB to ipl
		{
			u8tmph = _ptm0bh;
			u8tmpl = _ptm0bl;	
			ipl = (u8tmph << 8) | u8tmpl;
		}
		else //falling edge, save CCRA to iph
		{
			u8tmph = _ptm0ah;
			u8tmpl = _ptm0al;	
			iph = (u8tmph << 8) | u8tmpl;
		}
		_tm0af = 0;		
	}
	_int_pri10f = 0;	
}

void __attribute ((interrupt(0x3c))) ISR_TimeBase_Uart(void) 
{
	uint8 i;
		
	FEEDWATCHDOG();

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
		if (cnt1_1ms > 0)
			cnt1_1ms--;	
		else
			bTimeup1 = 1;	

		if (cnt2_1ms > 0)
			cnt2_1ms--;	
		else
			bTimeup2 = 1;
			
		_tbf = 0;
	}	

}

/* chars in buffer are sent to UART */
void print_string(char txdata[], uint8 cnt)
{
	uint8 i;	
	for (i = 0; i < cnt; i++)
	{
	while (_txif == 0) 
		FEEDWATCHDOG();	
	_txr_rxr = txdata[i];
	}
}

/* convert byte to 3 digits decimal string */
void byte2str10(char *str, uint8 num)
{
	uint8 quo, rem, u8tmp;
	
	div8_8(&quo, &rem, num, 10); 
	str[2] = rem + '0';//個位
	u8tmp = quo;
	div8_8(&quo, &rem, u8tmp, 10);
	str[1] = rem + '0';//十位 
	str[0] = quo + '0';//百位
}

/* convert uint16 to 5 digits decimal string */
void int2str10(char *str, uint16 num)
{
	uint16 quo, rem, u16tmp;
	
	div16_16(&quo, &rem, num, 10); 
	str[4] = rem + '0';//個位
	u16tmp = quo;
	div16_16(&quo, &rem, u16tmp, 10);
	str[3] = rem + '0';//十位 
	u16tmp = quo;
	div16_16(&quo, &rem, u16tmp, 10);
	str[2] = rem + '0';//百位	
	u16tmp = quo;
	div16_16(&quo, &rem, u16tmp, 10);
	str[1] = rem + '0';//千位
	str[0] = quo + '0';//萬位	
}

