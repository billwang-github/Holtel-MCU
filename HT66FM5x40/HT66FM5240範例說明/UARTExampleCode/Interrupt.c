#include "HT66FM5240.h"
#include "FuncTion.h"

DEFINE_ISR(ISR_Uart,0x34);

/*****************************************/
void ISR_Uart(void)
{
	//_uartf=0;		//UART¤¤Â_¼Ð»x²M¹s
	_rxif=0;
	
	RxdData=_txr_rxr;
	
//	RxdBuff[RxdCnt++]=_txr_rxr;
//	if(RxdCnt>4)
//	{
//		RxdCnt=0;	
//	}	
}

	