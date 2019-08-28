#include "HT66FM5240.h"
#include "FuncTion.h"

u16 Duty;
u16 Period;
u16 CatchCnt;
u16 PrevCatchCnt;
u16 TimeCnt;

void main(void)
{
	u16 i;
	
	DI();
	Duty=200;
	Period=1280;	
	SystemInit();
	EI();

	CatchCnt=0;
	PrevCatchCnt=0;
	Duty=200;
			
	while(1)
	{
		for(i=0;i<3000;i++)
		{
			FeedWatchDog();	//Áýª¯
		}
		SetDuty(256);
		Timer1_SetDuty(Duty,Period);//³]¸m¥eªÅ¤ñ				
	}
}















