#include "HT66FM5440.h"
#include "FuncTion.h"


void SystemInit(void)
{
	ClockInit();
	GPIOInit();
	PwmInit();
	CaptmInit();
	ProtectInit();
	HallInit();
	ADInit();
	#ifdef	UART_TEST_EN
	UartInit();
	#endif
	#ifdef	IIC_TEST_EN	 
	IICInit();
	#endif
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
	_pa6=0;		//端口輸出高電平
	
	#ifndef NOHALL_MODE
	_papu3=1;	//上拉
	_papu4=1;	//上拉
	_papu5=1;	//上拉
	#endif		
}

void WatchDogInit(void)
{
	_wdtc=0x57;	//IDLE模式時維持Fsys時鐘、看門狗時間=2^18/Fs	(Fs=Fsub、Fs=Fsys/4)
}


/****************PWM初始化************************/
void PwmInit(void)
{
	_pcps0=0xAA;	//C引腳共用功能設置	PC0-PC5設為PWM口
	_pcps1=0x0A;
			
	_pwmc=0x81;		//中心對齊模式1、 Fpwm=20MHZ、禁止占空比中斷、允許更新 	
			
	_prdrh=(u8)(PWMPERIOD>>8);	//設置週期寄存器
	_prdrl=(u8)(PWMPERIOD);
	
	_dutr0h=0x00;	//占空比寄存器
	_dutr0l=0x00;
	_dutr1h=0x00;
	_dutr1l=0x00;	
	_dutr2h=0x00;
	_dutr2l=0x00;
	
	_pwmme=0x3F;	//禁止PWM輸出
	_pwmmd=0x00;	//強制輸出電平寄存器 強制輸出低電平
	
	#ifdef SOFTMODE
	_mcf=0x8D;		//S/W Mask 模式、非互補輸出、PWM輸出使能、頂端PWM輸出、保護時輸出為0
	#else
	//_mcf=0x0D;		//H/W Mask 模式、非互補輸出、PWM輸出使能、頂端PWM輸出、保護時輸出為0
	_mcf=0x0C;		//H/W Mask 模式、非互補輸出、PWM輸出使能、底端PWM輸出、保護時輸出為0
	#endif
	
	//_dts=0xA4;		//使能死區、死區時間為1us
	_plc=0x00;		//極性為正相輸出

	
	_pwmpf=0;	//清除PWM週期中斷標誌
	_pwmpe=1;	//允許PWM週期中斷
//**	_mf2f=0;	//清除多功能2中斷標誌
//**	_mf2e=1;	//允許多功能2中斷
	_int_pri3f = 0;
	_int_pri3e = 1;
	
	
	_pwmc|=0x08;	//開啟PWM計數器	
}

void SetDuty(u16 duty)
{	
	u8 dutyH,dutyL;
	 		
	if(duty>MAX_PWM)	//PWMPERIOD
	{
		duty=MAX_PWM;	
	}
	
	dutyH=(u8)(duty>>8);
	dutyL=(u8)(duty);
		
	_dutr0h=dutyH;	//設置占空比寄存器
	_dutr0l=dutyL;
	_dutr1h=dutyH;
	_dutr1l=dutyL;
	_dutr2h=dutyH;
	_dutr2l=dutyL;	
}

/*****霍爾初始化*****/
void HallInit(void)
{		
	#ifndef NOHALL_MODE	//有霍爾
    _integ0=0x3f;   //Hall中斷源選擇H1、H2、H3、雙邊沿中斷
    _hdcr = 0xD1; 	//Hall信號無延遲、Bit4:120°、Bit3:S/W模式、正轉、Hall傳感器解碼使能	                   					

    #else	//無霍爾
   	_pa3s1=0;	//A引腳共用功能設置	PA3設為C1P口
	_pa3s0=1;	
	_pa4s1=1;	//A引腳共用功能設置	PA4設為C2P口
	_pa4s0=0;
	_pa5s1=1;	//A引腳共用功能設置	PA5設為C3P口
	_pa5s0=0;	
	_pb3s1=1;	//B引腳共用功能設置	PB3設為CPN口
	_pb3s0=0;
	
	_cmpc|=0xEE;		//開啟比較器1、2、3，允許比較器1、2、3遲滯功能
	_integ0=0x7F;	//Hall中斷源選擇比較器輸出、雙邊沿中斷
		
	#ifdef SOFTMODE	
	_hdcr = 0xD1; 	//Hall信號無延遲、Bit4:120°、Bit3:S/W模式、正轉、Hall傳感器解碼使能
	#else
//	_hdcr = 0x31; 	//Hall信號使能延遲選PTM0做延遲時間計數、120°、S/W模式、正轉、Hall傳感器解碼使能		 	
//	/*霍爾延遲PTM0設置*/
//	_ptm0c0=0x40;			//計數時鐘選為系統時鐘=Ftbc=32K(單位時間為31.25us)
//    _ptm0c1=0x01;			//比較匹配模式、比較器A匹配時清零計數器    
//    SetDelayTime(0);		//設置比較器A的值（設置延遲時間）

	_hdcr = 0xD1; 	//Hall信號無延遲、Bit4:120°、Bit3:S/W模式、正轉、Hall傳感器解碼使能	 	
	/*霍爾延遲PTM0設置*/
	_ptm0c0=0x40;			//計數時鐘選為系統時鐘=Ftbc=32K(單位時間為31.25us)
    _ptm0c1=0xC1;			//定時/計數模式、比較器A匹配時清零計數器  
//5240    _mf4f=0;				//清除多功能4中斷標誌位
//5240	_mf4e=1;				//允許多功能4中斷 
	_int_pri10f = 0;
	_int_pri10e = 1;
	_tm0af=0;
	_tm0ae=1; 
	#endif
    #endif
    
    _hchk_num = 0x05;     // Hall噪聲濾波次數為5（0-32）
	_hnf_msel = 0x09;	  //使能噪聲濾波器、濾波器時鐘=fsys/4 
    
    
	_hdcd = 0x00; 	//Hall譯碼器輸入數據寄存器清零
	//AH、AL、BH、BL、CH、CL
			
	_hdct0 = 0B00001001;	//CH->BL		1
	_hdct1 = 0B00011000;	//AH->BL		3
	_hdct2 = 0B00010010;	//AH->CL		2
	_hdct3 = 0B00000110;	//BH->CL		6
	_hdct4 = 0B00100100;	//BH->AL     	4
	_hdct5 = 0B00100001;	//CH->AL		5
			
//	_hdct0 = 0B00011000;	//BH->AL     	1
//	_hdct1 = 0B00010010;	//CH->AL		3	
//	_hdct2 = 0B00000110;	//CH->BL		2
//	_hdct3 = 0B00100100;	//AH->BL		6
//	_hdct4 = 0B00100001;	//AH->CL		4
//	_hdct5 = 0B00001001;	//BH->CL		5
	
	
	_hdct6 = 0B00100001;	//CH->AL		1
	_hdct7 = 0B00001001;	//CH->BL		3
	_hdct8 = 0B00011000;	//AH->BL		2
	_hdct9 = 0B00010010;	//AH->CL		6
	_hdct10 = 0B00000110;	//BH->CL		4
	_hdct11 = 0B00100100;	//BH->AL     	5
	
//	_hdct6 =  0B00100100;	//AH->BL		1
//	_hdct7 =  0B00100001;	//AH->CL		3
//	_hdct8 =  0B00001001;	//BH->CL		2
//	_hdct9 =  0B00011000;	//BH->AL     	6
//	_hdct10 = 0B00010010;	//CH->AL		4	
//	_hdct11 = 0B00000110;	//CH->BL		5
		
	_frs=0;
//5240	_hallf_mf0f=0;	//清除Hall總中斷標誌
//5240	_halle_mf0e=1;	//允許Hall總中斷
	_int_pri1f = 0;
	_int_pri1e = 1;
	
	//_mfi0=0x07;		//允許HA、HB、HC中斷
	_halaf=0;		//清除HA中斷標誌
	_halbf=0;		//清除HB中斷標誌
	_halcf=0;		//清除HC中斷標誌	
	_halae=1;		//使能HA中斷
	_halbe=1;		//使能HB中斷
	_halce=1;		//使能HC中斷	
}

/****************保護初始化（過流、限流、堵轉）********************/
void ProtectInit(void)
{
	_pa1s0=1;		//引腳共用功能設置 （設置成AP功能）PA1--AP
	_pa1s1=0;
	
	_opoms = 0b01000010;	//比較器上升沿有效、內部運放放大10倍, 1A=33
	_opcm=255;		//DA比較寄存器值過流電壓為 255 => 7.7A
	_opa0cal = 0b01110000;
	
	_mptc1=0x1C;	//禁止軟件關斷功能、使能過流保護、使能限流保護、使能堵轉保護
	_mptc2=0x1F;	//軟件保護、過流保護、限流保護、堵轉保護都選擇Pause模式
	
//5240	_c0f=0;		//清除比較中斷標誌位
//5240_c0e=1;		//允許比較中斷
	_int_pri2f = 0;
	_int_pri2e = 1;
	_cmpc|=0x11;	//開啟比較器0、使能遲滯功能
}

/***************捕捉定時器初始化************************/
void CaptmInit(void)
{
	_captc0=0x00;		///計數時鐘選為PWM週期時間（64us）、捕捉通道選為H1	
	_captc1=0xF7;		//選擇雙邊沿捕捉、使能捕捉、噪聲濾波採樣四次、CAPTM 噪聲濾波器時鐘選為系統時鐘fSYS、濾波使能、CAPTM 計數器捕捉自動復位使能、CAPTM  計數器 比較匹配自動復位使能
	
	_captmal=0xFF;		//設置比較器的比較值	//堵轉時間設定
	_captmah=0xFF;
	
//	_capcf=0;				//清除比較匹配中斷標誌位
//	_capce=1;				//允許比較匹配中斷
//	_capof=0;				//清除捕捉中斷標誌位
//	_capoe=1;				//允許捕捉中斷
//5240	_mf1f=0;				//清除多功能1中斷標誌位
//5240_mf1e=1;				//允許多功能1中斷
	_int_pri6f = 0;
	_int_pri6e = 1;

	//_captc0|=0x08;		//啟動計數器	
}

/*****************AD初始化**********************/
void ADInit(void)
{	
	_pa7s0=1;		//引腳共用功能設置 （設置AD通道）PA7--AN6, speed control
	_pa7s1=0;
	
	_pd0s0=1;		//引腳共用功能設置 （設置AD通道）PD0--AN0 , Iavg
	_pd0s1=0;
	
	_pd1s0 = 1;		//引腳共用功能設置 （設置AD通道）PD1--AN1 , Input Voltage
	_pd1s1 = 0;
		
	_adcr1 = 0b00011100;	//選擇觸發電路、禁止延遲功能、PWM週期觸發AD、AD時鐘=Fsys/16、
	_adcr0 = 0b00000000;	//開啟AD電源、數據左對齊、初始通道選為AN0（內部通道）
	_adcr2 = 0b00000000;	//12 bits, 1 ch
	_adcr3 = 0x00;
	_addl=0x00;		//AD觸發延遲
	_adbyps = 0x80; //unity gain buffer on

	_adlvdl=0x00;	//設置AD值窗口限制值(初始限流值)
	_adlvdh=0x00;

	_adhvdl=0xFF;	//設置AD值窗口限制值(初始限流值)
	_adhvdh=0xFF;
		
	_isaeocf=0;	//清除AD轉換結束標誌
	_isaeoce=1;	//允許AD轉換結束中斷
		
//5240	_mf1f=0;	//清除多功能1中斷標誌
//5240	_mf1e=1;	//允許多功能1中斷
	_int_pri8f = 0;
	_int_pri8e = 1;
		
}

u16 AdSample_1(u8 channel)
{
	u16 temp;
		
	_aeoce=0;	//禁止AD轉換結束中斷
	_dlstr = 0;	//禁止觸發電路	
	_adcr0 &=0xF0;
	_adcr0 |=channel;
	
	_adstr=0;
	_adstr=1;
	_adstr=0;	
	while(_eocb);	//等待轉換結束
		
	temp=(_addata >> 6);	//10位AD
	_dlstr = 1;	//選擇觸發電路	
	_adcr0 &=0xF0;
	_adcr0 |=CURRENT_CHAN;
	ChannelCnt=0;
	_aeocf=0;	//清除AD轉換結束標誌
	_aeoce=1;	//允許AD轉換結束中斷
	
	return temp;	
}

/*****************UART初始化********************/
#ifdef	UART_TEST_EN
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
	_int_pri15f = 0;
	_int_pri15e = 1;
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
#endif

/************IIC初始化*******************/
#ifdef IIC_TEST_EN
void IICInit(void)
{
//	_sclps=1;		//引腳重置功能設置	SCL重置到PB1
//	_sdaps=1;		//引腳重置功能設置	SDA重置到PB2
//		
//	_pb1s0=1;		//引腳共用功能設置 （設置SCL）PB1--SCL
//	_pb1s1=1;	
//	_pb2s0=0;		//引腳共用功能設置 （設置SDA）PB2--SDA
//	_pb2s1=0;
//	_pb2s2=1;	

	_pa0s0=1;		//引腳共用功能設置 （設置SCL）PA0--SDA
	_pa0s1=0;
	
	_pa2s0=1;		//引腳共用功能設置 （設置SCL）PA2--SCL
	_pa2s1=0;
	
	_papu0=1;	//上拉
	_papu2=1;	//上拉
	
	
	_iicc0=0x0A;	//使能IIC、抖動時間設為4個系統時鐘
	_iica=0xA0;		//設置本機的從機地址
	_i2ctoc=0xBF;	//使能超時控制、超時時間設為最長
	
	_iicf=0;		//IIC中斷標誌清零
	_iice=1;		//使能IIC中斷
	
	_int_pri15f = 0;
	_int_pri15e = 1;	
}
#endif