#include "HT66FM5440.h"
#include "FuncTion.h"

u16 TimeCnt;
u16 AdData[4];
u8  ChannelCnt;
u8  Time1msCnt;

#ifdef	UART_TEST_EN
u8 TxdBuff[5];
u8 RxdBuff[5];
u8 TxdPoint;
u8 TxdPoint2;
u8 TxdCnt;
u8 RxdCnt;
#endif

Byte Flag01;
Byte Flag02;

#ifdef	IIC_TEST_EN 
u16 IIC_TxdData; 
u8 IIC_RxdData;
#endif


void main(void)
{		
	DI();		
	SystemInit();
	//DRIVER_AD=AdSample_1(DRIVER_CHAN);	
	DRIVER_AD = 0;
	if(DRIVER_AD>START_DRIVER_AD)	//600mv(1-4.8mv)
	{
		bStopFlag=1;
	}
	bDegree_60Flag=0;
	bReversalFlag=0;
	bOverCurrentFlag=0;
	bRunFlag=0;	
	bPhaseChangFlag=0;
	bTakeTurnFlag=0;
	MC_HanderBarAD=0;
	Time1msCnt=0;
	
	if(bDegree_60Flag)
	{
		MC_ErrHallVal1=2;
		MC_ErrHallVal2=5;
	}
	else
	{
		MC_ErrHallVal1=0;
		MC_ErrHallVal2=7;
	}
	ChannelCnt=0;
	EI();
			
	while(1)
	{	
		#ifdef	UART_TEST_EN	
		UartHand();	
		#endif
		
//		#ifdef IIC_TEST_EN
//		switch(IIC_RxdData)
//		{
//			case 0:
//					IIC_TxdData=MC_HallPortVal;//VOLTAGE_AD;
//					break;
//			case 1:
//					IIC_TxdData=VOLTAGE_AD;
//					break;
//			case 2:
//					IIC_TxdData=VOLTAGE_AD;
//					break;
//			case 3:
//					IIC_TxdData=CURRENT_AD;
//					break;
//			case 5:
//					IIC_TxdData=VOLTAGE_AD;
//					break;
//			case 6:
//					IIC_TxdData=DRIVER_AD;
//					break;
//			case 7:
//					IIC_TxdData=VOLTAGE_AD;
//					break;
//			default:
//					break;		
//		}
//		#endif
		
		if(bTime1msFlag)
		{
			bTime1msFlag=0;
			HandleSpeed();	
		}
		
		FeedWatchDog();				
	}
}


void Delay_2us(u16 t)
{
	while(t)
	{
		t--;
		FeedWatchDog();	
	}	
}


void Delay_1ms(u16 t)
{
	u16 i;
	while(t)
	{				
		i=400;
		while(i)
		{
			i--;
			FeedWatchDog();	
		}
		t--;
	}	
}









