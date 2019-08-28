#include "HT66FM5240.h"
#include "FuncTion.h"

//#pragma	vector ISR_TIMER1	@0x2C

DEFINE_ISR(ISR_TIMER1,0x2C);

/**************************************/
void ISR_TIMER1(void)
{
	u16 temph,templ;
	_tm1af=0;				//清除比較A匹配中斷標誌位
	_tm1pf=0;				//清除比較P匹配中斷標誌位
	
	_pa6=~_pa6;
	
	temph=_ptm1ah;
	templ=_ptm1al;

	
	CatchCnt=(temph<<8)|templ;
	if(CatchCnt>PrevCatchCnt)
	{
		TimeCnt=CatchCnt-PrevCatchCnt;
	}
	else
	{
		TimeCnt=65536-PrevCatchCnt+CatchCnt;
	}
	PrevCatchCnt=CatchCnt;	
}	