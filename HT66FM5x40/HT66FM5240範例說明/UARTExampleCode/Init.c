#include "HT66FM5240.h"
#include "FuncTion.h"


void SystemInit(void)
{
	ClockInit();
	GPIOInit();
	UartInit();
	WatchDogInit();	
}


void ClockInit(void)
{
	_smod=0x01;	//禁止快速喚醒功能、禁止IDLE模式	Fsys=Fh=20MHZ
	while((_smod&0x04)==0);	//等待時鐘穩定
}

void GPIOInit(void)
{
	_papu6=0;	//未上拉
    _pac6=0;	//端口設為輸出模式
	_pa6=1;		//端口輸出高電平
	
	_papu3=1;	//上拉
	_papu4=1;	//上拉
	_papu5=1;	//上拉
		
}

void WatchDogInit(void)
{
	_wdtc=0x57;	//IDLE模式時維持Fsys時鐘、看門狗時間=2^18/Fs	(Fs=Fsub、Fs=Fsys/4)
}

/*************************************/
void UartInit(void)
{
	_pb6s0=1;		//引腳共用功能設置 （設置RX）PB6--RX
	_pb6s1=0;
	_pb7s0=1;		//引腳共用功能設置 （設置TX）PB7--TX
	_pb7s1=0;
	
	_ucr1=0x80;		//使能UART、8位數據傳輸、奇偶校驗、一位停止位、無暫停字
	_ucr2=0xE4; 	//發送、接收使能、選擇高速波特率、無地址檢測功能、無喚醒功能、禁止發送空閒中斷、禁止發送寄存器空中斷
	_brg=129;       //_brg=20000000/(9600*16)-1=129  (高速波特率：波特率=fSYS/[16×(N+1)]、低速波特率：波特率=fSYS/[64×(N+1)])
	
	_uartf=0;		//UART中斷標誌清零
	_uarte=1;		//使能UART中斷
}

void UartHand(void)
{
	if(_txif)
	{
		_txif=0;
		if(TxdPoint2)	
		{
			TxdPoint2--;
			_txr_rxr=TxdBuff[TxdPoint++];	
			if(TxdPoint>4)
			{
				TxdPoint=0;
			}
		}
	}
}

void UartPutChar(u8 value)
{
	if(TxdPoint2<5)
	{
		TxdPoint2++;
		TxdBuff[TxdCnt++]=value;		
		if(TxdCnt>4)
		{
			TxdCnt=0;
		}
	}
}