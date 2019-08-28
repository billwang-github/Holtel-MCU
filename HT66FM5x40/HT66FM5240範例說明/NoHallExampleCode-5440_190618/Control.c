#include "HT66FM5440.h"
#include "FuncTion.h"


u8 MC_HallPortVal;
u8 MC_PrevHallPortVal;
u8 MC_NewHall;
u8 MC_PrevHall;
u8 MC_ErrHallVal1;
u8 MC_ErrHallVal2;
u8 MC_MotorStartCnt;

u16 MC_ActPWM;
u16 MC_DecPWM;
u16 MC_HanderBarAD;
u16 MC_SpeedTime;
u16 MC_PrevSpeedTime;
u16 MC_HallDelayTime;
u16 MC_HallDelayCnt;

u8 Test[8];


#ifdef SOFTMODE
//const unsigned char PWMME[8]={0x3F,0x2F,0x3E,0x3E,0x3B,0x2F,0x3B,0x3F};	//正常驅動上管PWM
//const unsigned char PWMMD[8]={0x00,0x08,0x20,0x08,0x02,0x02,0x20,0x00};



const unsigned char PWMME[8]={0x3F,0x1F,0x3D,0x3D,0x37,0x1F,0x37,0x3F};	//上下管對調驅動
const unsigned char PWMMD[8]={0x00,0x04,0x10,0x04,0x01,0x01,0x10,0x00};

//const unsigned char PWMME[8]={0x3F,0x3B,0x2F,0x3B,0x3E,0x3E,0x2F,0x3F};	//上下管對調驅動下管PWM
//const unsigned char PWMMD[8]={0x00,0x20,0x02,0x02,0x08,0x20,0x08,0x00};
#endif

const unsigned char Degree60to120[8]={2,6,0,4,3,0,1,5};
const unsigned char ucNextHall[8]={0,3,6,2,5,1,4,0};
const unsigned char ucPrevHall[8]={0,5,3,1,6,4,2,0};
const unsigned char Reversal_Hall[8]={0,5,3,1,6,4,2,0};//{0,2,4,6,1,3,5,0};



void HandleSpeed(void)
{	
	MC_HanderBarAD=(MC_HanderBarAD+DRIVER_AD)>>1;
	
	if(bStopFlag)
	{
		MC_DecPWM=0;
		MC_ActPWM=0;
		
		if(MC_HanderBarAD<=ZERO_DRIVER_AD)	//300mv
		{
			bStopFlag=0;
		}
	}
	else if(MC_HanderBarAD>START_DRIVER_AD)	//600mv
	{			
		if(!bRunFlag)
		{	
			DI();														
			if(bOverCurrentFlag)
			{	
				/*復位保護模塊*/
				if(CURRENT_AD<ZERO_CURRENT_AD)
				{
					_pswe=1;
					_pswd=0;
					_pswe=0;
				}
										
				/*MOS自檢*/			
				bOverCurrentFlag=0;
				if(bOverCurrentFlag)
				{
					bStopFlag=1;	
				}							
			}
			else
			{				
				MC_HallPortVal=ReadHallPort();
								
				#ifndef NOHALL_MODE
				if((MC_HallPortVal==MC_ErrHallVal1)||(MC_HallPortVal==MC_ErrHallVal2))
				{
					bStopFlag=1;	
				}
				else
				#endif
				{	
					MC_PrevSpeedTime=MC_SpeedTime;
					//bReversalFlag=~bReversalFlag;																		
					#ifdef NOHALL_MODE
						if((MC_SpeedTime>500)||(MC_HallPortVal==MC_ErrHallVal1)||(MC_HallPortVal==MC_ErrHallVal2))
						{
							#if 0
							MC_HallPortVal=MotorLocation();
							bTakeTurnFlag=0;
							#else
//							SetDuty(20);
//							ChangeDrive(3);	
//							Delay_1ms(700);
//							ChangeDrive(0);	
//							SetDuty(0);										
//							MC_HallPortVal=6;
							
							bTakeTurnFlag=1;
							TakeTurnOkCnt=0;
							MC_HallPortVal=6;
							#endif						
						}
						else
						{
							bTakeTurnFlag=0;
						}
						
						MC_NewHall=MC_HallPortVal;
						MC_MotorStartCnt=200;
						if(MC_PrevSpeedTime>100)//50
						{
							MC_PrevSpeedTime=100;
						}
																				
						#ifdef SOFTMODE						
						MC_HallDelayTime=(MC_PrevSpeedTime>>1);												
						MC_HallDelayCnt=0;
						bPhaseChangFlag=0;
						if(bReversalFlag)
						{
							MC_NewHall=Reversal_Hall[MC_NewHall];
						}
						#else
						MC_HallDelayTime=MC_PrevSpeedTime;
						_frs=bReversalFlag;
						//SetDelayTime(MC_HallDelayTime);
						#endif					
					#else
						MC_NewHall=MC_HallPortVal;
						#ifdef SOFTMODE
						if(bDegree_60Flag)
						{
							MC_NewHall=Degree60to120[MC_NewHall];	
						}
						
						if(bReversalFlag)
						{
							MC_NewHall=Reversal_Hall[MC_NewHall];
						}
						#else
						_frs=bReversalFlag;
						#endif
					#endif
					MC_SpeedTime=0;																																																				
					bRunFlag=1;
					MC_ActPWM=20;
					SetDuty(MC_ActPWM);
					Delay_2us(2);	
					ChangeDrive(MC_NewHall);																																
					StarCAPTM();				
				}			
			}
			EI();									
		}
		#ifdef NOHALL_MODE
		if(bTakeTurnFlag)
		{
			MC_DecPWM=20;
		}
		else
		#endif
		{
			MC_DecPWM=(MC_HanderBarAD-START_DRIVER_AD);
		}
		
		if(MC_DecPWM<20)
		{
			MC_DecPWM=20;	
		}
		
		if(MC_DecPWM>MAX_PWM)
		{
			MC_DecPWM=MAX_PWM;
		}			
	}
	else
	{
		MC_DecPWM=0;
	}
	
	if(MC_DecPWM>MC_ActPWM)
	{
		if(MC_DecPWM>(MC_ActPWM+20))
		{
			MC_ActPWM+=3;	//5
		}
		else if(MC_ActPWM<MAX_PWM)
		{
			MC_ActPWM++;
		}
	}
	else
	{
		if(MC_ActPWM>(MC_DecPWM+20))
		{
			MC_ActPWM-=3;	//5
		}
		else if(MC_ActPWM>0)
		{
			MC_ActPWM--;
		}
		else
		{
			bRunFlag=0;
			StopCAPTM();
			ChangeDrive(0);
		}
	}
	
	SetDuty(MC_ActPWM);
}


//const unsigned char LOCATION_PWMMD[8]={0x00,0x25,0x16,0x26,0x19,0x29,0x1A,0x00};
const unsigned char LOCATION_PWMMD[8]={0x00,0x1A,0x29,0x19,0x26,0x16,0x25,0x00};

u8 MotorLocation(void)
{
	u8 i,temp;
	u16 ch[7];
	
	#ifndef SOFTMODE
	//_mcf=0x8D;	//S/W模式
	_mcf=0x8C;	//S/W模式
	#endif
	
	_pwmme=0x3F;	//禁止PWM輸出
	_pwmmd=0x00;	//強制輸出電平寄存器 強制輸出低電平
	
	for(i=1;i<7;i++)
	{		
		_pwmmd=LOCATION_PWMMD[i];
		//_pa6=1;
		Delay_2us(25);	//200
		ch[i]=AdSample_1(CURRENT_CHAN);
		//_pa6=0;	
		_pwmmd=0x00;	//200
		Delay_2us(50);		
	}
	
	_pwmmd=0x00;
		
	temp=1;
	for(i=1;i<7;i++) //取最大值
	{
		if(ch[i]>ch[temp])
		{
			temp=i;	
		}
	}
	
	#ifndef SOFTMODE	
	//_mcf=0x0D;	//H/W模式
	_mcf=0x0C;	//H/W模式
	#endif
	
	return temp;
}


//const unsigned char TAKETURNSTEP[8]={6,4,5,1,3,2};
//u8 TakeTurnTime;
//u8 TakeTurnStep;
//u8 TakeTurnOkCnt;
//u8 TakeTurnTimeCnt;

//void TakeTurn(void)
//{
//	if(++TakeTurnTimeCnt>TakeTurnTime)
//	{
//		TakeTurnTimeCnt=0;
//		if(TakeTurnTime>9)
//		{
//			TakeTurnTime-=1;		
//		}
//		
//		TakeTurnStep++;		
//		if(TakeTurnStep>5)
//		{
//			TakeTurnStep=0;
//		}
//
//		MC_NewHall=TAKETURNSTEP[TakeTurnStep];
//		ChangeDrive(MC_NewHall);
//	}
//}

