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
	_pwmpf=0;	//�M��PWM�g�����_�лx

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
		
		AdData[ChannelCnt]=(temp+AdData[ChannelCnt])>>1;	//10��AD
		
		if(ChannelCnt==0)
		{
			timecnt++;
			switch(timecnt)
			{
				case 10:
						_adcr0 &=0xF0;
						_adcr0 |=DRIVER_CHAN;	//�ճtAD
						ChannelCnt=1;
						break;
				case 20:
						_adcr0 &=0xF0;
						_adcr0 |=VOLTAGE_CHAN;	//�q��AD
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
		_int_pri6f=0;				//�M������ǰt���_�лx��
		/*����O�@*/
		bStallFlag=1;
		ChangeDrive(0);
		bStopFlag=1;
		bRunFlag=0;
		/*�n��_��O�@�Ҷ�*/
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
	/*�L�y�O�@��PWM��X*/
	ChangeDrive(0);
	bOverCurrentFlag=1;
	bStopFlag=1;
	bRunFlag=0;
}
/*****************************************/
void ISR_Uart_IIC(void)
{
#ifdef	UART_TEST_EN	
	//_uartf=0;		//UART���_�лx�M�s
	_rxif=0;
	
	RxdBuff[RxdCnt++]=_txr_rxr;
	if(RxdCnt>4)
	{
		RxdCnt=0;	
	}
#endif	

#ifdef IIC_TEST_EN
	if(_iichaas)	//�a�}�ǰt�лx
	{
		_iichaas=0;
		if(_iicsrw)	//�q�����A�лx��
		{
			_iichtx=1;	//�]���o�e�Ҧ�
			_iicd=Test[IIC_RxdData];	//�o�e�ƾ�	
		}
		else	//�q�������ƾ�
		{
			_iichtx=0;	//�]�������Ҧ�
			_iictxak=0;	//�o�e������
			temp=_iicd;	//��Ū�ƾ�---����SDA
		}
	}
	else if(_iichcf)	//�ƾڶǿ駹���лx
	{
		_iichcf=0;	
		
		if(_iichtx)	//�q���B��o�e�Ҧ�
		{
			if(_iicrxak)	//��������T�{�лx
			{
				_iichtx=0;	//�]�������Ҧ�
				_iictxak=0;	//�o�e������
				temp=_iicd;	//��Ū�ƾ�---����SDA	
			}
			else
			{
				_iicd=(u8)(IIC_TxdData);	//�o�e�ƾ�		
			}
		}
		else	//�q���B�󱵦��Ҧ�
		{
			//_iictxak=0;	//�o�e������
			IIC_RxdData=_iicd;	
		}
	}
	else if(_i2ctof)	//�W�ɤ��_
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
//	//_uartf=0;		//UART���_�лx�M�s
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
//	if(_iichaas)	//�a�}�ǰt�лx
//	{
//		_iichaas=0;
//		if(_iicsrw)	//�q�����A�лx��
//		{
//			_iichtx=1;	//�]���o�e�Ҧ�
//			_iicd=Test[IIC_RxdData];	//�o�e�ƾ�	
//		}
//		else	//�q�������ƾ�
//		{
//			_iichtx=0;	//�]�������Ҧ�
//			_iictxak=0;	//�o�e������
//			temp=_iicd;	//��Ū�ƾ�---����SDA
//		}
//	}
//	else if(_iichcf)	//�ƾڶǿ駹���лx
//	{
//		_iichcf=0;	
//		
//		if(_iichtx)	//�q���B��o�e�Ҧ�
//		{
//			if(_iicrxak)	//��������T�{�лx
//			{
//				_iichtx=0;	//�]�������Ҧ�
//				_iictxak=0;	//�o�e������
//				temp=_iicd;	//��Ū�ƾ�---����SDA	
//			}
//			else
//			{
//				_iicd=(u8)(IIC_TxdData);	//�o�e�ƾ�		
//			}
//		}
//		else	//�q���B�󱵦��Ҧ�
//		{
//			//_iictxak=0;	//�o�e������
//			IIC_RxdData=_iicd;	
//		}
//	}
//	else if(_i2ctof)	//�W�ɤ��_
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