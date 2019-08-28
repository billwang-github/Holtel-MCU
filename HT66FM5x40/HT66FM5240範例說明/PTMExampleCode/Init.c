#include "HT66FM5240.h"
#include "FuncTion.h"


void SystemInit(void)
{
	ClockInit();
	GPIOInit();
	PwmInit();
	Timer1Init();
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
}

void WatchDogInit(void)
{
	_wdtc=0x57;	//IDLE模式時維持Fsys時鐘、看門狗時間=2^18/Fs	(Fs=Fsub、Fs=Fsys/4)
}


/****************************************/
void PwmInit(void)
{
	_pcps0=0xAA;	//C引腳共用功能設置	PC0-PC5設為PWM口
	_pcps1=0x0A;
	
		
	_pwmc=0x81;		//中心對齊模式1、 Fpwm=20MHZ、禁止占空比中斷、允許更新 	
	
	_prdrh=(u8)(PWMPERIOD>>8);	//設置週期寄出去
	_prdrl=(u8)(PWMPERIOD);
	
	_dutr0h=0x00;	//占空比寄存器
	_dutr0l=0x00;
	_dutr1h=0x00;
	_dutr1l=0x00;	
	_dutr2h=0x00;
	_dutr2l=0x00;
	
	_pwmme=0x00;	//禁止強制輸出功能
	_pwmmd=0x00;	//強制輸出電平寄存器
	
	_mcf=0x85;		//S/W Mask 模式、互補輸出、PWM輸出使能、頂端PWM輸出
	_dts=0xA4;		//使能死區、死區時間為1us
	_plc=0x00;		//極性為正相輸出
	
	_pwmc|=0x08;	//開啟PWM計數器	
}


void SetDuty(u16 duty)
{
	if(duty>PWMPERIOD)
	{
		duty=PWMPERIOD;	
	}
	_dutr0h=(u8)(duty>>8);	//設置占空比寄存器
	_dutr0l=(u8)(duty);
	_dutr1h=(u8)(duty>>8);
	_dutr1l=(u8)(duty);	
	_dutr2h=(u8)(duty>>8);
	_dutr2l=(u8)(duty);	
}


/*****************************************/
void Timer1Init(void)
{
	#ifdef PWM_Mode
	_pdps0|=0x50;			//PD2、PD3設為TP1_0、TP1_1	
	_ptm1c0=0x10;			//計數時鐘選為系統時鐘=20MHZ
	_ptm1c1=0xA8;			//PWM或單脈衝模式、PWM輸出、高有效、同相		
	_ptm1rpl=(u8)(TIMER1_PWMPERIOD);	//設置週期值為1280（PWM週期為64us）
	_ptm1rph=(u8)(TIMER1_PWMPERIOD>>8);	
	_ptm1al=0x00;			//設置初始占空比為0
	_ptm1ah=0x00;	
	_ptm1c0|=0x08;			//啟動計數器
	
	#elif defined MONOPULSE_Mode
	_pdps0|=0x50;			//PD2、PD3設為TP1_0、TP1_1	
	_ptm1c0=0x10;			//計數時鐘選為系統時鐘=20MHZ
	_ptm1c1=0xB8;			//PWM或單脈衝模式、單脈衝輸出、高有效、同相		
	_ptm1al=(u8)(Duty);		//設置單脈衝的寬度
	_ptm1ah=(u8)(Duty>>8);	
	_ptm1c0|=0x08;			//啟動計數器
	
	#elif defined COMPARE_Mode
	_pdps0|=0x50;			//PD2、PD3設為TP1_0、TP1_1	
	_ptm1c0=0x10;			//計數時鐘選為系統時鐘=20MHZ
	_ptm1c1=0x34;			//比較匹配輸出模式、輸出翻轉、初始為低、反相、P比較器比較匹配時清零計數器	
	_ptm1rpl=(u8)(TIMER1_PWMPERIOD);	//設置比較器P的值
	_ptm1rph=(u8)(TIMER1_PWMPERIOD>>8);	
	_ptm1al=(u8)(Duty);					//設置比較器A的值
	_ptm1ah=(u8)(Duty>>8);	
	
	//_tm1af=0;				//清除比較A匹配中斷標誌位
	//_tm1ae=1;				//允許比較A匹配中斷
	_tm1pf=0;				//清除比較P匹配中斷標誌位
	_tm1pe=1;				//允許比較P匹配中斷
	_mf5f=0;				//清除多功能5中斷標誌位
	_mf5e=1;				//允許多功能5中斷
	_ptm1c0|=0x08;			//啟動計數器
	
	#elif defined EVENTCOUNT_Mode
	//_pdps0|=0x50;			//PD2、PD3設為TP1_0、TP1_1	
	_ptm1c0=0x10;			//計數時鐘選為系統時鐘=20MHZ
	_ptm1c1=0xC0;			//定時\計數器模式、P比較器比較匹配時清零計數器		
	_ptm1rpl=(u8)(TIMER1_PWMPERIOD);		//設置定時時間
	_ptm1rph=(u8)(TIMER1_PWMPERIOD>>8);
		
	//_tm1af=0;				//清除比較A匹配中斷標誌位
	//_tm1ae=1;				//允許比較A匹配中斷
	_tm1pf=0;				//清除比較P匹配中斷標誌位
	_tm1pe=1;				//允許比較P匹配中斷
	_mf5f=0;				//清除多功能5中斷標誌位
	_mf5e=1;				//允許多功能5中斷		
	_ptm1c0|=0x08;			//啟動計數器
	#elif defined CATCH_Mode
	//_pdps0|=0x50;			//PD2、PD3設為TP1_0、TP1_1	
	_ptm1c0=0x10;			//計數時鐘選為系統時鐘=20MHZ
	_ptm1c1=0x62;			//捕捉輸入模式、雙沿輸入捕捉、捕捉信號來自TCKn腳		
	_ptm1rpl=0x00;			//設置最長捕捉時間(65536*0.05us=3276us)
	_ptm1rph=0x00;
		
	_tm1af=0;				//清除比較A匹配中斷標誌位
	_tm1ae=1;				//允許比較A匹配中斷
	//_tm1pf=0;				//清除比較P匹配中斷標誌位
	//_tm1pe=1;				//允許比較P匹配中斷
	_mf5f=0;				//清除多功能5中斷標誌位
	_mf5e=1;				//允許多功能5中斷		
	_ptm1c0|=0x08;			//啟動計數器	
	#endif	
}

void Timer1_SetDuty(u16 duty,u16 period)
{
	#ifdef PWM_Mode
	if(duty>TIMER1_PWMPERIOD)
	{
		duty=TIMER1_PWMPERIOD;	
	}		
	_ptm1al=(u8)(duty);		//設置占空比寄存器
	_ptm1ah=(u8)(duty>>8);
	#elif defined MONOPULSE_Mode
	_ptm1al=(u8)(duty);		//設置脈衝寬度
	_ptm1ah=(u8)(duty>>8);
	#elif defined COMPARE_Mode
	_ptm1al=(u8)(duty);		//設置比較寄存器A
	_ptm1ah=(u8)(duty>>8);
	_ptm1rpl=(u8)(period);	//設置比較寄存器P
	_ptm1rph=(u8)(period>>8);	
	#elif defined EVENTCOUNT_Mode
	_ptm1rpl=(u8)(period);	//設置比較寄存器P
	_ptm1rph=(u8)(period>>8);
	#endif
}
