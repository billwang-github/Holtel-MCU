#include "HT66FM5440.h"

/*
	baud rate:9600
	==============
	command:
	#HHXXXX : XXXX => hall period in HEX
	#DDXXXX : XXXX => phase delay in HEX
*/

#define uint8 unsigned char
#define uint16 unsigned int
#define FEEDWATCHDOG() GCC_CLRWDT()

const uint8 txbuff[6] = { 'H' , 'e', 'l' , 'l', 'o', '!' };
uint8 rxbuff[6];
uint8 rxcnt = 0, txcnt = 0;
bit bRxfull = 0;

void UartInit(void);
void print_string_const(const uint8 txdata[]);

void main()
{
	uint8 i;
	
	rxcnt = 0;
	for (i = 0; i < 6; i++)
	{
		rxbuff[i] = 0;
	}					
			
	UartInit();
	_emi = 1;
	
	while (1)
	{
		FEEDWATCHDOG();
		
		if (rxcnt >=6)
		{
			if ((rxbuff[0] == 'H') && (rxbuff[1] == 'H'))
			{
				print_string_const(txbuff);
					
				rxcnt = 0;
				for (i = 0; i < 6; i++)
				{
					rxbuff[i] = 0;
				}				
			}
		}
	}
}

void UartInit(void)
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

DEFINE_ISR(ISR_Uart,0x3c);
/*****************************************/
void ISR_Uart(void)
{
	uint8 i;
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
}

void print_string_const(const uint8 txdata[])
{
	uint8 i;	
	for (i = 0; i < 6; i++)
	{
		while (_txif == 0) 
			FEEDWATCHDOG();	
		_txr_rxr = txdata[i];
	}
}