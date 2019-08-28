#include "HT66FM5440.h"
#include "FuncTion.h"

DEFINE_ISR(ISR_PWM,0x0C);
DEFINE_ISR(ISR_Hall,0x04);
DEFINE_ISR(ISR_CAPTM,0x18);
DEFINE_ISR(ISR_ADC,0x20);
DEFINE_ISR(ISR_Protect,0x08);
DEFINE_ISR(ISR_Uart_IIC,0x3C);
//FINE_ISR(ISR_IIC,0x30);
DEFINE_ISR(ISR_PT0,0x28);
/***************************************/

u8 TakeTurnOkCnt;
u8 TakeTurnTimeCnt;

void ISR_PWM(void)
{
	_pwmpf=0;	//清除PWM週期中斷標誌

	if(MC_SpeedTime<10000)
	{
		MC_SpeedTime++;
	}

	#ifdef SOFTMODE	
	if(MC_HallDelayCnt<10000)
	{
		MC_HallDelayCnt++;
	}
	
	if(bRunFlag&&(!bTakeTurnFlag))
	{
		if(bPhaseChangFlag&&(MC_HallDelayCnt>=MC_HallDelayTime))
		{							
			bPhaseChangFlag=0;
			MC_HallDelayCnt=0;
			
			MC_NewHall=ReadHallPort();
			MC_HallPortVal=MC_NewHall;
			
			if(bReversalFlag)
			{
				MC_NewHall=Reversal_Hall[MC_NewHall];
			}
											
			ChangeDrive(MC_NewHall);
		
			
			if(MC_MotorStartCnt)
			{
				MC_MotorStartCnt--;	
			}									
		}		
	}
	#endif
			
	if(++Time1msCnt>15)	
	{
		Time1msCnt=0;
		bTime1msFlag=1;
		
		#ifdef NOHALL_MODE
		if(bRunFlag&&bTakeTurnFlag)
		{			
			if(++TakeTurnTimeCnt>=100)	//100
			{
				ChangeDrive(0);
				TakeTurnTimeCnt=0;
				_pa6=~_pa6;
				
				if(bReversalFlag)
				{
					MC_NewHall=ucPrevHall[MC_NewHall];
				}
				else
				{
					MC_NewHall=ucNextHall[MC_NewHall];
				}
				ChangeDrive(MC_NewHall);
				if(MC_NewHall==6)
				{
					bTakeTurnFlag=0;
				}				
			}
		}
		#endif
	}
}

/**************************************/
u8 temp;
void ISR_Hall(void)
{		
	_halaf=0;
	_halbf=0;
	_halcf=0;
	
	temp=ReadHallPort();
				
	if(temp!=MC_HallPortVal)
	{
		MC_HallPortVal=temp;
								
		#ifdef NOHALL_MODE					
			#ifdef SOFTMODE
			bPhaseChangFlag=1;
			MC_HallDelayCnt=0;
								
			MC_HallDelayTime=(MC_PrevSpeedTime+MC_HallDelayTime+MC_HallDelayTime)>>2;
			
//			if(MC_HallDelayTime>2)
//			{
//				MC_HallDelayTime-=2;	
//			}
//			else
//			{
//				MC_HallDelayTime=0;	
//			}
			
			MC_HallDelayTime-=(MC_HallDelayTime>>1);
							
			if(MC_HallDelayTime>1000)
			{
				MC_HallDelayTime=1000;
			}			
			#else																					
			MC_HallDelayTime=(MC_PrevSpeedTime+MC_HallDelayTime)>>1;
						
//			if(MC_HallDelayTime>4)
//			{
//				MC_HallDelayTime-=4;	
//			}
//			else
//			{
//				MC_HallDelayTime=2;	
//			}

			MC_HallDelayTime-=(MC_HallDelayTime>>1);
															
			if(MC_HallDelayTime>2000)
			{
				MC_HallDelayTime=2000;
			}
																									
		 	if(bRunFlag&&(!bTakeTurnFlag))
			{	
				if(MC_MotorStartCnt)
				{
					MC_MotorStartCnt--;	
				}
				SetDelayTime(MC_HallDelayTime);													
				MC_NewHall=MC_HallPortVal;															
				//ChangeDrive(MC_NewHall);
			}			
			#endif				
		#else			
			if((MC_HallPortVal==MC_ErrHallVal1)||(MC_HallPortVal==MC_ErrHallVal2))
		    {
		   		bStopFlag=1;
				bRunFlag=0;	
				ChangeDrive(0);
		        return;	
		    }
			else if(bRunFlag)
			{
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
				#endif
								
				MC_PrevHall=MC_NewHall;
				ChangeDrive(MC_NewHall);
			}			
		#endif
		//MC_PrevSpeedTime=MC_SpeedTime;
		MC_PrevSpeedTime=(MC_SpeedTime+MC_PrevSpeedTime)>>1;
		MC_SpeedTime=0;							
	}   
}

/*************************************/
u8 timecnt;
void ISR_ADC(void)
{	
	u16 temp;
		
	if(_isaeocf)
	{
		_isaeocf=0;
		temp=_addata;
		temp=temp>>6;
		
		AdData[ChannelCnt]=(temp+AdData[ChannelCnt])>>1;	//10位AD
		
		if(ChannelCnt==0)
		{
			timecnt++;
			switch(timecnt)
			{
				case 10:
						_adcr0 &=0xF0;
						_adcr0 |=DRIVER_CHAN;	//調速AD
						ChannelCnt=1;
						break;
				case 20:
						_adcr0 &=0xF0;
						_adcr0 |=VOLTAGE_CHAN;	//電源AD
						ChannelCnt=2;
						timecnt=0;
						break;
				default:
						break;
			}
		}
		else
		{
			_adcr0 &=0xF0;
			_adcr0 |=CURRENT_CHAN;
			ChannelCnt=0;	
		}	
	}
}

void ISR_CAPTM(void)
{						
	if(_int_pri6f)
	{
		_int_pri6f=0;				//清除比較匹配中斷標誌位
		/*堵轉保護*/
		bStallFlag=1;
		ChangeDrive(0);
		bStopFlag=1;
		bRunFlag=0;
		/*軟件復位保護模塊*/
		_pswe=1;
		_pswd=0;
		_pswe=0;
	}
}

/*****************************************/
void ISR_Protect(void)
{
	_int_pri2f = 0;
	//_c0f=0;	
	/*過流保護關PWM輸出*/
	ChangeDrive(0);
	bOverCurrentFlag=1;
	bStopFlag=1;
	bRunFlag=0;
}
/*****************************************/
void ISR_Uart_IIC(void)
{
#ifdef	UART_TEST_EN	
	//_uartf=0;		//UART中斷標誌清零
	_rxif=0;
	
	RxdBuff[RxdCnt++]=_txr_rxr;
	if(RxdCnt>4)
	{
		RxdCnt=0;	
	}
#endif	

#ifdef IIC_TEST_EN
	if(_iichaas)	//地址匹配標誌
	{
		_iichaas=0;
		if(_iicsrw)	//從機狀態標誌位
		{
			_iichtx=1;	//設成發送模式
			_iicd=Test[IIC_RxdData];	//發送數據	
		}
		else	//從機接收數據
		{
			_iichtx=0;	//設成接收模式
			_iictxak=0;	//發送應答位
			temp=_iicd;	//空讀數據---釋放SDA
		}
	}
	else if(_iichcf)	//數據傳輸完成標誌
	{
		_iichcf=0;	
		
		if(_iichtx)	//從機處於發送模式
		{
			if(_iicrxak)	//未接收到確認標誌
			{
				_iichtx=0;	//設成接收模式
				_iictxak=0;	//發送應答位
				temp=_iicd;	//空讀數據---釋放SDA	
			}
			else
			{
				_iicd=(u8)(IIC_TxdData);	//發送數據		
			}
		}
		else	//從機處於接收模式
		{
			//_iictxak=0;	//發送應答位
			IIC_RxdData=_iicd;	
		}
	}
	else if(_i2ctof)	//超時中斷
	{
		_i2ctof=0;
		
	}	
#endif	
	_int_pri15f = 0;
}
/*****************************************/
//#ifdef	UART_TEST_EN
//void ISR_Uart(void)
//{
//	//_uartf=0;		//UART中斷標誌清零
//	_rxif=0;
//	
//	RxdBuff[RxdCnt++]=_txr_rxr;
//	if(RxdCnt>4)
//	{
//		RxdCnt=0;	
//	}	
//}
//#endif

/*************************************/
//#ifdef IIC_TEST_EN
//void ISR_IIC(void)
//{
//	u8 temp;
//
//	if(_iichaas)	//地址匹配標誌
//	{
//		_iichaas=0;
//		if(_iicsrw)	//從機狀態標誌位
//		{
//			_iichtx=1;	//設成發送模式
//			_iicd=Test[IIC_RxdData];	//發送數據	
//		}
//		else	//從機接收數據
//		{
//			_iichtx=0;	//設成接收模式
//			_iictxak=0;	//發送應答位
//			temp=_iicd;	//空讀數據---釋放SDA
//		}
//	}
//	else if(_iichcf)	//數據傳輸完成標誌
//	{
//		_iichcf=0;	
//		
//		if(_iichtx)	//從機處於發送模式
//		{
//			if(_iicrxak)	//未接收到確認標誌
//			{
//				_iichtx=0;	//設成接收模式
//				_iictxak=0;	//發送應答位
//				temp=_iicd;	//空讀數據---釋放SDA	
//			}
//			else
//			{
//				_iicd=(u8)(IIC_TxdData);	//發送數據		
//			}
//		}
//		else	//從機處於接收模式
//		{
//			//_iictxak=0;	//發送應答位
//			IIC_RxdData=_iicd;	
//		}
//	}
//	else if(_i2ctof)	//超時中斷
//	{
//		_i2ctof=0;
//		
//	}	
//}
//#endif



void ISR_PT0(void)
{
	_tm0af=0;
	_pt0on=0;
	ChangeDrive(MC_NewHall);
}	