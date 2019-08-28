#include "HT66FM5240.h"
#include "FuncTion.h"

u16 TimeCnt;
u16 AdData[4];
u8  ChannelCnt;
u8  Time1msCnt;

u8 TxdBuff[5];
u8 RxdBuff[5];
u8 TxdPoint;
u8 TxdPoint2;
u8 TxdCnt;
u8 RxdCnt;
Byte Flag01;


u8 TxdData;
u8 RxdData;

void main(void)
{	
	u16 i;	
	DI();		
	SystemInit();	
	EI();
	
	TxdData=0xAA;		
	while(1)
	{
		for(i=0;i<3000;i++)
		{
			FeedWatchDog();	
			UartHand();	
		}
		UartPutChar(TxdData);					
	}
}















