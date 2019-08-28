//======================================================
// File  : Leafblower.C
// 
// MCU setting:
// 
// PWM 16K use Centre-aligned mode 1.
//
// Auther : Chuansheng Pei/13312975887
// Date   : 2016/08/08
// version: 1.0
// history: 
//======================================================
#include "HT66FM5440.h"
asm(" include HT66FM5440.inc ");

//===============================================
#define DRAG_TIME 			20 //45	
#define DRAG_TEMP_TIME 		1	
#define DRAG_MIN_TIME 		10 //20	

#define DRAG_PWM_Min		790	
#define DRAG_PWM_MAX		DRAG_PWM_Min + 5
#define DRAG_PWM_BaseInc	6	

#define	PWM_MAX				800
#define	PWM_MAX_Gear3		800 
#define	PWM_MAX_Gear2		648	
#define	PWM_MAX_Gear1		400	
#define	PWM_MAX_Gear4		125		//1A
#define PWM_MAX_LowVoltage	160

//===============================================
const unsigned char ucDealDragHall[6]={5,1,3,2,6,4};

typedef struct{
	unsigned char	b0 : 1;
	unsigned char	b1 : 1;
	unsigned char	b2 : 1;
	unsigned char	b3 : 1;
	unsigned char	b4 : 1;
	unsigned char	b5 : 1;
	unsigned char	b6 : 1;
	unsigned char	b7 : 1;
}_bits;

static volatile	_bits bit_var_0	__attribute__	((at(0x80)));
static volatile	_bits bit_var_1	__attribute__	((at(0x81)));
static volatile	_bits bit_var_2	__attribute__	((at(0x82)));

#define bDragFlag			bit_var_0.b0
#define bStallFlag			bit_var_0.b1
#define bFirstRunFlag		bit_var_0.b2
#define bRestart			bit_var_0.b3
#define bHadRun				bit_var_0.b4
#define bStopMotor			bit_var_0.b5
#define bPermitStart		bit_var_0.b6
#define bAlarmFlag			bit_var_0.b7

#define bVoiceFlag			bit_var_1.b0
//#define bPermitStart		bit_var_1.b1
#define bNmsFlag			bit_var_1.b2
#define bOCP				bit_var_1.b3
#define bVoltageUnder		bit_var_1.b4
#define bCurrentLimit		bit_var_1.b5
#define bVoltageOver		bit_var_1.b6
#define bVRRefresh			bit_var_1.b7

#define bVoltageErrorVoice	bit_var_2.b0
#define bVoltageErrorFlag	bit_var_2.b1
#define bVDC_WorkOK			bit_var_2.b2
#define bKey_Press 			bit_var_2.b3
#define bKey_Bounce			bit_var_2.b4
#define bKey_NO				bit_var_2.b5
#define bPWMUpdate			bit_var_2.b6
#define bcaputre_speed			bit_var_2.b7

volatile unsigned int	uiDragPWM_Max;
volatile unsigned char	ucDragPWM_BaseInc;
volatile unsigned char	ucHallCycle;
volatile unsigned char	ucDragDelayTime;
volatile unsigned char	ucTempDragDelayTime;
volatile unsigned char	ucMinDragDelayTime;
volatile unsigned int	uiDragPWM;
volatile unsigned char	uiCount1ms;
volatile unsigned char	ucHallCnt;
volatile unsigned int	uiLastHallTime;
volatile unsigned int	uiVR_Value;
volatile unsigned int	uiTempPWM;
volatile unsigned char	ValueTemp;
volatile unsigned char	ucHallStep;
volatile unsigned int	uiHallTimeCnt;
volatile unsigned char	ucVoiceStep;
volatile unsigned int	uiVoiceTimeCnt;
volatile unsigned char	ucDragCnt;

volatile unsigned char	ucReadADCNT;
volatile unsigned int	uiADC_ValueTemp;
volatile unsigned int	uiADCSum;
volatile unsigned char	ucVRIndex;
volatile unsigned int	uiVRValue_Final;
volatile unsigned int	uiVRValue[4];
volatile unsigned char	ucVDC_Temp;
volatile unsigned int	uiVDCADCSum;
volatile unsigned char	ucVDCIndex;
volatile unsigned int	uiVDCValue_Final;
volatile unsigned int	uiVDCValue[4];
volatile unsigned int	uiCurrentADCSum;
volatile unsigned char	ucCurrentIndex;
volatile unsigned int	uiCurrentValue_Final;
volatile unsigned int	uiCurrentValue[4];
volatile unsigned int	uiVoltageCheckCnt;
volatile unsigned char	ucMTR_State;
volatile unsigned int	uiReleaseKey_CNT;
volatile unsigned char	ucPWMUpdateCNT;

static volatile unsigned int	uiVoiceTime	__attribute__ ((at(0x180)));
static volatile unsigned char	ucLostCommandVoice __attribute__ ((at(0x182)));
static volatile unsigned char	ucVoiceCnt __attribute__ ((at(0x194)));


//===============================================
void 	IO_Init(void);
void 	PWM_Init(void);
void 	ADC_Init(void);
void 	TM1_Init(void);
void	PWMInit(void);
void 	Hall_Init(void);
void 	INT_Init(void);
void 	System_Init(void);
void 	Varitate_Init(void);
void 	Drag_Motor(void);
void 	delay(unsigned int);
void 	Comparator_Init(void);
void 	CAPTM_Init(void);
void 	Motor_Stop(void);
void 	VoiceSpeakInit(void);
void 	Init_TM3(void);
void 	AD_Init(void);
void 	CommandOK(void);
void 	commutation(void);
void 	TimeBaseInit(void);
void 	delay1(unsigned char x);
void	ReadVR(void);
void	ReadMTRState(void);
void	ReadVDC(void);
void	ReadCurrent(void);
void	ReadVDC_PowerON(void);
void	KeyCheck(void);
void	get_drag_pwm(void);

//===============================================
//
//===============================================
void main()
{
	asm("NOP");
	asm("NOP");
	asm("NOP");
	_emi = 0;
	IO_Init();
	System_Init();
	TM1_Init();
	PWMInit();
	Hall_Init();
	ADC_Init();
	Comparator_Init();
	CAPTM_Init();
	Init_TM3();
	TimeBaseInit();
	INT_Init();
	Varitate_Init();
	_lvden=1;
	_lve=1;
	_lvf=0;
	_emi = 1;
	delay(1000);
	uiReleaseKey_CNT = 10001;
	ucMTR_State = 0;
	ReadVDC_PowerON();
	delay(2000);			//開機後先DELAY一段時間
	
//	VoiceSpeakInit();
//	ucVoiceStep = 0;
	CommandOK();
//***********************************************
//main loop
//***********************************************
	while(1)
	{
		if(ucReadADCNT > 20)
		{
			ucReadADCNT = 0;
			KeyCheck();
			ReadMTRState();
			ReadVDC();		
			ReadCurrent();	
		}
		
		if(bPermitStart)
		{
			if(bStopMotor || bVoltageOver || bVoltageUnder || bOCP)
			{
			    Motor_Stop();
			}
			
			if(bHadRun)
		    {
			    if(uiVR_Value < 50)   
			    {
			        if((uiTempPWM < 50) && (uiHallTimeCnt > 5))
			        {
			            bRestart=1;
				        Motor_Stop();
						Varitate_Init();
			        }
			    }
		    }
	    }
	    
		if(bNmsFlag)
		{
			bNmsFlag = 0;
			
		    if(bPermitStart && (!bVoltageOver) && (!bVoltageUnder))
		    {
				if(uiVRValue_Final > 120)
				{
					bVRRefresh = 1;	
					
				}
				else if(uiVRValue_Final < 70)
				{
					bVRRefresh = 0;
					bOCP = 0;
					_ocpse = 1;
					_ocpse = 0;
					_ocpse = 1;	
				}
				
				if(bVRRefresh)
		        {
					uiVR_Value = uiVRValue_Final;
					if(bVDC_WorkOK)
					{
						if(uiVR_Value > PWM_MAX)
						{
							uiVR_Value = PWM_MAX;	
						}
					}
					else
					{
						if(uiVR_Value > PWM_MAX_LowVoltage)
						{
							uiVR_Value = PWM_MAX_LowVoltage;
						}
					}
		        }
		        else
		        {
					uiVR_Value = 0;
		        }
				
		        
				if(uiVR_Value > 120)
				{
					
					if((bHadRun&&(uiHallTimeCnt > 100)) || bStallFlag)
					{
						if(bStopMotor == 0)
						{
							bStallFlag = 0;
							Motor_Stop();
							Varitate_Init(); 
						}
					}
				    
				    if(bRestart && (!bOCP))
					{
					    bRestart = 0;
					    if(bFirstRunFlag == 0)
					    {
							get_drag_pwm();
							uiDragPWM_Max = uiDragPWM + 5;
							bDragFlag = 1;
					    }
					    bFirstRunFlag = 1;
					}
				}
				else if(bDragFlag)
				{
				    bRestart = 1;
					Motor_Stop();
					Varitate_Init();
				}
				
				if(bHadRun)
				{
					if(!bCurrentLimit)
					{
						if(uiTempPWM < uiVR_Value)
						{
							uiTempPWM += 5;
						}
						else 
						{
							if(uiVR_Value >= 150)
							{
								uiTempPWM --;
							}
							else
							{
								uiTempPWM = uiVR_Value;	
							}
						}
					}
					else if(uiTempPWM > uiVR_Value)
					{
						uiTempPWM = uiVR_Value;
					}
					
				    ValueTemp = (unsigned char)(uiTempPWM >> 8);
				    _dutr0h = ValueTemp;
				    ValueTemp = (unsigned char)uiTempPWM;
					_dutr0l = ValueTemp;
					_pwmsuf = 1;
				}
			}
			
			if(bVoltageErrorVoice)
			{
				VoiceSpeakInit();
				ucVoiceStep = 6;
				bAlarmFlag = 1;
				bVoltageErrorVoice = 0;
			}
		}
		asm("CLR	WDT");
	}
}



//===============================================
//
//===============================================
void System_Init(void)
{
	_smod = 0b00000001;
	for(_mp0 = 0x80;_mp0 != 0x00;_mp0 ++)_iar0 = 0x00;		//clear RAM  
	_mp1h = 1;
	for(_mp1l = 0x80;_mp1l != 0x00;_mp1l++)_iar1 = 0x00;	//clear RAM  
	_mp2h = 2;
	for(_mp2l = 0x80;_mp2l != 0x00;_mp2l++)_iar1 = 0x00;	//clear RAM  
	_mp1h = 0;
	_mp2h = 0;
	asm("CLR	WDT");

}


//===============================================
//
//===============================================
void IO_Init(void)
{
	_pc   = 0x00;	
	_pcc  = 0x00;		
	
	_pac = 0B11111010;	
	_pa  = 0x00;
	
	_pbc = 0B11001000;		
	_pb  = 0x00;			
	_pbpu = 0B11000000;
	
	_paps0 = 0x44;		
	_paps1 = 0x2a;		
	_pbps0 = 0b10010000;
	
	_pbps1 = 0x00;
	_pcps0 = 0x00;
	_pcps1 = 0x00;

}



//===============================================
//
//===============================================
void ADC_Init(void)
{
	_adcr0 = 0b00010000;
	_adcr1 = 0b00000100;		
	_adcr2 = 0b01010011;	
	_adcr3 = 0b00000001;	
	_adisg1 = 0b10000110;	
	_adisg2 = 0b11111111;	
	_adbyps = 0x80;		
	_addl   = 20;		
	
	_dlstr  = 1;		
	_adoff  = 0;		
	asm("CLR	WDT");
}



//===============================================
//
//===============================================
void Comparator_Init(void)
{
	_opoms = 0b01000011;	
	_opa0cal = 0b00010000;
	_opcm = 165;			
	_cmpc = 0xff;
	_ishe = 1;			
	_ocpse = 1;			
	_ocps = 0;			
	_int_pri2e = 1;
	_int_pri2f = 0;
}


//===============================================
//
//===============================================
void __attribute ((interrupt(0x08))) ISR_OCP(void)
{
	_int_pri2f = 0;
	bOCP = 1;
}


//===============================================
//
//===============================================
void	PWMInit(void)
{
    _pwmc = 0b00110001;		
	_pwmcs  = 0b00000111;	
	_prdrh  = 0x03;
	_prdrl  = 0xff;		
	_dutr3h = 1;
	_dutr3l = 0xff;
	_dutr0h = 0;
	_dutr0l = 0x27;
	_pwmsuf = 1;
	
	_mcf = 0b00001101;	
	_dts = 0B11100110;   
	_hdcr = 0b11010001; 
	_integ0 = 0x00;
	_hdcd = 0;
	_pwmme = 0xff;
	_pwmmd = 0x00;
	_pwmon = 1;
}



//===============================================
//
//===============================================
void Hall_Init(void)
{
    _hdcr = 0b11010001;
	_hdcd = 0b00000000;
	_hnf_msel = 0b00001011;	
	_hchk_num = 15; //12;
	
	_hdct0 = 0B00100101;	//SC SB SA(001) CT BB     	1
	_hdct1 = 0B00000000;	//SC SB SA(011) AT BB		3
		
	_hdct2 = 0B00010010;	//SC SB SA(010) AT CB		2
	_hdct3 = 0B00000110;	//SC SB SA(110) BT CB		6
	_hdct4 = 0B00100100;	//SC SB SA(100) BT AB		4
	_hdct5 = 0B00100001;	//SC SB SA(101) CT AB		5	
	
	_hdct6 = 0B00011000;	//SC SB SA(001) CT AB 
	_hdct7 = 0B00010010;	//SC SB SA(011) CT BB 
	_hdct8 = 0B00000110;	//SC SB SA(010) AT BB
	_hdct9 = 0B00100100;	//SC SB SA(110) AT CB
	_hdct10 =0B00100001;	//SC SB SA(100) BT CB
	_hdct11 =0B00001001;	//SC SB SA(101) BT AB
	
	_hdms = 0;
	asm("CLR	WDT");
}



//===============================================
//
//===============================================
void CAPTM_Init(void)
{
    _captc0 = 0b01100000;	
	_captc1 = 0b11101111;	
	
	_captmal = 0x00;
	_captmah = 0xff;
    _capton = 1;
}



//===============================================
//
//===============================================
void INT_Init(void)
{
	_int_pri3e = 1;		
	_int_pri3f = 0;	
}


//===============================================
//
//===============================================
void Varitate_Init(void)
{
	ucDragDelayTime     = DRAG_TIME;
	ucTempDragDelayTime = DRAG_TEMP_TIME;
	ucMinDragDelayTime  = DRAG_MIN_TIME;
	ucDragPWM_BaseInc	= DRAG_PWM_BaseInc;
	uiDragPWM_Max		= DRAG_PWM_MAX;
	
	_hchk_num = 12;
	uiDragPWM = 0;
	bHadRun = 0;
	ucHallCnt = 0;
	bFirstRunFlag = 0;
	bDragFlag = 0;
	ucHallCycle = 0;
	bStopMotor = 0;
	bStallFlag = 0;
	bRestart = 1;
	uiLastHallTime = 800;
	_ptm3al = 250;
	_ptm3ah = 0x00;	
    
	_halae = 0;	
	_halbe = 0;	
	_halce = 0;	
	_int_pri1e = 1;	
	_halaf = 0;
	_halbf = 0;
	_halcf = 0;	
	_int_pri1f = 0;
}


//===============================================
//
//===============================================
void delay1(unsigned char n)
{
    unsigned char j;
    for(j=0;j<n;j++)
    asm("CLR	WDT");		
}


//===============================================
//
//===============================================
void delay(unsigned int x)
{
    unsigned int i;
    unsigned char j;  
    unsigned char k;  
    for(i=0;i<x;i++)
    for(j=0;j<11;j++)
    for(k=0;k<30;k++)
   	asm("CLR	WDT");	
	
}


//===============================================
//
//===============================================
void Drag_Motor(void)
{
	unsigned char temp;
	if(uiDragPWM < uiVR_Value)
	{
		uiDragPWM = uiVR_Value;
	}
	uiDragPWM += DRAG_PWM_BaseInc;	
	if(uiDragPWM > uiDragPWM_Max)	
	{
		uiDragPWM = uiDragPWM_Max;
	}
	temp=(unsigned char)(uiDragPWM >> 8);
	_dutr0h = temp;
	
	temp = (unsigned char)uiDragPWM;
	_dutr0l = temp;
	_pwmsuf = 1;
	_halae = 1;	
	_halbe = 1;	
	_halce = 1;	
	
	commutation();
	_pt3on=1;
	
	if(ucDragDelayTime > ucMinDragDelayTime)
	{
		ucDragDelayTime -= ucTempDragDelayTime;
		if(ucTempDragDelayTime < 4)
		{
			ucTempDragDelayTime ++;
		}
	}
}


//===============================================
//
//===============================================
volatile unsigned int uiHallTimeNew = 0;	
void __attribute ((interrupt(0x04))) ISR_HALL(void)
{
	unsigned char ucHallTimeTemp;
	unsigned int uiHallTimeNewTemp; 
	unsigned int uiHallCheckDelay; 
	_int_pri1f = 0;
	
    _mfi0 = 0x07;
    _pt1on = 0;
    
    uiHallTimeNewTemp = _ptm1dh;    
    ucHallTimeTemp = _ptm1dl;
    
    uiHallTimeNewTemp = uiHallTimeNewTemp << 8;
    uiHallTimeNewTemp = uiHallTimeNewTemp | ucHallTimeTemp;
    uiHallTimeNew = uiHallTimeNewTemp;
     _pt1on = 1;      
     
    if(bHadRun)
    {
    	if(ucHallCnt > 50)
	    if(uiLastHallTime > (uiHallTimeNew << 2)/*(uiHallTimeNew+uiHallTimeNew+uiHallTimeNew)*/)
	    {
	        bStallFlag = 1;	
	    }
	    uiHallCheckDelay = uiLastHallTime >> 3;
    	_ptm3al = /*(unsigned char)*/uiHallCheckDelay;
		_ptm3ah = /*(unsigned char)*/(uiHallCheckDelay >> 8);
		
		if(ucHallCnt < 200)
		ucHallCnt ++;
    }
    
	uiLastHallTime = uiHallTimeNew;
	uiHallTimeCnt = 0;
	commutation(); 
	
	if(bHadRun == 0)
	{
		if(ucHallCycle > 1)    
		{
			ucHallCycle = 0;
			bDragFlag = 0;  
			uiTempPWM = uiDragPWM;
			bHadRun = 1;
			_hchk_num = 8;
			
		}
    }
    
	_pt3on = 0;
	_pt3on = 1;
	
	_int_pri14f = 0;
	_tm3af = 0;
    
	_int_pri1f = 0;
	_mfi0 = 0x07;
}


//===============================================
//
//===============================================
void commutation(void)
{
	_int_pri1e = 0;	

_pb0 = 1;

	switch (ucHallStep)
	{
	 case 0:	//CT,AB	
		delay1(100);
		_pc     = 0b00000010;	
		_pcps0  = 0x00;
		_pcps1  = 0b00000010;	
	//	delay1(50);
	//	_pb ^= 2;
	    _integ0 = 0b00100000;	//PHASE B DOWN = C3P DOWN
	 break;
	
	 case 1:	//CT,BB
		delay1(100);
		_pc     = 0b00001000;
	//	delay1(50);
	//	_pb ^= 2;
	    _integ0 = 0b00000100;	//PHASE A UP = C2P UP	
	 break;
	 
	 case 2:	//AT,BB
		delay1(100);
		_pcps1  = 0b00000000;
		_pcps0  = 0b00000010;
	//	delay1(50);
	//	_pb ^= 2;
	    _integ0 = 0b00000010;	//PHASE C DOWN = C1P DOWN
	 break;
	 
	 case 3:	//AT,CB
		delay1(100);
		_pc     = 0b00100000;
	//	delay1(50);
	//	_pb ^= 2;
	    _integ0 = 0b00010000;	//PHASE B UP = C3P UP	
	 break;
	 
	 case 4:	//BT,CB
		delay1(100);
		_pcps0  = 0b00100000;
	//	delay1(50);
	//	_pb ^= 2;
	    _integ0 = 0b00001000;	//PHASE A DOWN = C2P DOWN
	 break;
	 
	 case 5:	//BT,AB
		delay1(100);
		_pc     = 0b00000010;
	//	delay1(50);
	//	_pb ^= 2;
	    _integ0 = 0b00000001;	//PHASE C UP = C1P UP	
	 break;
	 
	 default:
	 break;
	}

	if(ucHallStep >= 5)
	{
		ucHallStep = 0;
		if(ucHallCycle < 250)
		    ucHallCycle ++;
	}
	else
	{
	    ucHallStep ++;
	}
	ucDragCnt = 0;
}






//===============================================
//
//===============================================
void Motor_Stop(void)
{
	uiTempPWM=0;
	_dutr0h = 0;
	_dutr0l = 0;
	_pwmsuf = 1;
	_hdcd = 0;
	_pwmme = 0x00;
	_pwmmd = 0xff;
	
	_pc = 0;
	_pcps0 = 0x00;
	_pcps1 = 0x00;
}



//===============================================
//
//===============================================
void CommandOK(void)
{
	ucVoiceStep=1;
	_ptm2c0=0b10100000; 
	_tm2pf=0;
	_tm2pe=0;
	_tm2af=0;
	_tm2ae=0;
	_int_pri9e = 0;
	_int_pri9f = 0;
	
	_pwmc = 0b00000001;		
	_prdrh = 0x03;							
	_prdrl = 0x20;	
	_dutr0h = 0;
	_dutr0l = 0x27;
	_pwmsuf = 1;
	
	_mcf=0b10001101; 
	_dts=0B11000110;
	_hdcd=0;
	bPermitStart = 1;
	_pwmon = 1;
	
	_pwmme = 0x00;
	_pwmmd = 0xFF;	
	_pc = 0x00;
	_pcps0 = 0x00;
	_pcps1 = 0x00;
}




//===============================================
//
//===============================================
void VoiceSpeakInit(void)
{
	_ptm2c0 = 0b10100000;
	_ptm2c1 = 0b11000000;
	_ptm2al = 0x10;
	_ptm2ah = 0x00;
	_ptm2rpl = 0xe8;
	_ptm2rph = 0x01;	
	_ptm2c0 = 0b00101000; 
	_tm2pf = 0;
	_tm2pe = 1;
	_tm2af=0;
	_int_pri9e = 1;
	_int_pri9f = 0;
	
	_pwmc = 0b00110001;
	_pwmcs  = 0b00000111;
	_prdrh  = 0x03;
	_prdrl  = 0xff;
	_dutr3h = 1;
	_dutr3l = 0xff;
	_dutr0h = 0;
	_dutr0l = 0x20;
	_pwmsuf = 1;
	
	_mcf = 0b00001101;
	_dts = 0B11100110;
	_hdcr = 0b11010001; 
	_integ0 = 0x00;
	_hdcd = 0;
	_pwmme = 0xff;
	_pwmmd = 0x00;
	_pwmon = 1;
	_plc = 0x00;	
	_pcps0 = 0xaa;
	_pcps1 = 0x0a; 	
	
	_halae = 0;
	_halbe = 0;
	_halce = 0;
	_int_pri1e = 0;
	
	_halaf = 0;
	_halbf = 0;
	_halcf = 0;
	_int_pri1f = 0;
	
	ucVoiceStep = 6;
	bAlarmFlag = 0;
	uiVoiceTime = 556;
}



//===============================================
//
//===============================================
void __attribute ((interrupt(0x24))) ISR_TM2(void)
{
    _int_pri9f = 0;
    _tm2pf = 0;
	
   if(bAlarmFlag == 0)
    {
        _hdcd = 1;
    }
    else
    {
        _hdcd = 3;
    }
    
    
	if(ucVoiceStep == 6)
	{
		if(uiVoiceTimeCnt++ > uiVoiceTime)//
		{
			uiVoiceTimeCnt = 0;
			uiVoiceTime = 300;
			if(bAlarmFlag)
			{
			    bVoiceFlag = 1;	
			}
			else
			{
			    bVoiceFlag = 0;
			}
			bAlarmFlag = 1;
		}
		else
		{
			if(bVoltageErrorFlag)
			{
				ucVoiceCnt = 0;
				if(bVoiceFlag)
				{
					bAlarmFlag = 0;
					ucLostCommandVoice ++;
				}
				else if(ucLostCommandVoice >= 2)
				{
					ucLostCommandVoice = 0;
					uiVoiceTime = 5000;
				}
			}
			
			else if(!bVoltageErrorFlag)
			{
				{
					ucVoiceCnt=0;
					bAlarmFlag=1;
					CommandOK();
				}
			}
		}
	}
	else
	{
		if(uiVoiceTimeCnt ++> 460)
	    {
	    	uiVoiceTimeCnt = 0;
	    	ucVoiceStep ++;
	    	if((ucVoiceStep == 1) || (ucVoiceStep == 3))
	    	{
	    		bAlarmFlag = 1;	
	    	}
	    	if((ucVoiceStep == 2) || (ucVoiceStep == 4))
	    	{
	    		bAlarmFlag = 0;	
	    	}
	    	if(ucVoiceStep == 5)
	    	{
	    		bAlarmFlag = 1;	
				ucVoiceCnt = 0;
				CommandOK();
				uiVoiceTimeCnt = 0;
	    	}
		}
	}
//	CommandOK();
	
}



//===============================================
//
//===============================================
void TM1_Init(void)
{
    _ptm1c0=0b00100000;  
	_ptm1c1=0b11000001;	
	
	_ptm1al=0xf0;
	_ptm1ah=0xff;
	
}

//===============================================
//
//===============================================
void __attribute ((interrupt(0x2c))) ISR_TM1()
{
	_int_pri11f = 0;
	_tm1af = 0;	
    
    _pt1on = 0;
	_int_pri11f = 0;
	_tm1af = 0;	
}





//===============================================
//
//===============================================
void Init_TM3(void)
{
    _ptm3c0 = 0b00100000;   
	_ptm3c1 = 0b11000001;	
	
	_ptm3al = 250;
	_ptm3ah = 0x00;
	
	_tm3af = 0;
    _tm3ae = 1;
	
	_int_pri14f = 0;
	_int_pri14e = 1;
}


//===============================================
//
//===============================================
void __attribute ((interrupt(0x38))) ISR_TM3(void)
{
    _int_pri14f = 0;
	_tm3af = 0;
	_pt3on = 0;
	_int_pri1f = 0;
	_mfi0 = 0x07;	
	_int_pri1e = 1;
	
_pb0 = 0;

	_integ0 |= 0x40;
	if(uiLastHallTime < 140)
    if(_int_pri1f == 1)
    {
        if((_mcd & 0x07) == ucDealDragHall[ucHallStep])
        {
    		delay1(80);	//70
			_int_pri14f = 0;
			_tm3af = 0;
    		return;
        }
    }
    
	_int_pri1f = 0;
	_mfi0 = 0x07;
	_int_pri14f = 0;
    _tm3af = 0;
    
    
}




//===============================================
//
//===============================================
void TimeBaseInit(void)
{
    _tbc = 0xc0;
    _tbe = 1;
    _tbf = 0;
    _int_pri15e = 1;
    _int_pri15f = 0;
}

void __attribute ((interrupt(0x3c))) ISR_TimeBase(void)
{
	_int_pri15f = 0;
    _tbf = 0;
	if(bPermitStart)
	{
		if(bDragFlag && (bStopMotor == 0) && (bVoltageOver == 0))
		{
			if(ucDragCnt++ > ucDragDelayTime)
			{
		    	Drag_Motor();
			}
		}
	}
	
	
	if(uiVoltageCheckCnt++ > 4000)
	{
		uiVoltageCheckCnt = 4001;
		if(!bVoltageErrorFlag)
		{
			bVoltageErrorFlag = 1;
			bVoltageErrorVoice = 1;
			bPermitStart = 0;		
	    }
	}
	
	if(uiHallTimeCnt++ > 1000)
	{
		uiHallTimeCnt = 1001;
	}
	
	uiCount1ms ++;
    if(uiCount1ms >= 1)	
	{
	    uiCount1ms = 0;
	    bNmsFlag = 1;
	}
	
	if(ucReadADCNT < 200)
	{
		ucReadADCNT ++;
	}
	
	if(uiReleaseKey_CNT < 20000)
	{
		uiReleaseKey_CNT ++;
	}
	
	asm("CLR	WDT");	
}



//===============================================
//
//===============================================
void	KeyCheck(void)
{
	if(!_pb7)
	{
		bKey_NO = 0;
		uiReleaseKey_CNT = 0;
		if(bKey_Press)
		{
/*			if(bKey_Bounce)
			{
				bKey_Bounce = 0;
				if(ucMTR_State == 0)
				{
					ucMTR_State = 1;
				}
				else if(ucMTR_State == 1)
				{
					ucMTR_State = 2;
				}
				else if(ucMTR_State == 2)
				{
					ucMTR_State = 3;
				}
				else if(ucMTR_State == 4)
				{
					ucMTR_State = 1;
				}
			}*/
			ucMTR_State = 3;
		}
		else
		{
			bKey_Press = 1;
		}
	}
	else
	{
		if(bKey_NO)
		{
			bKey_Bounce = 1;
			bKey_Press  = 0;
		}
		else
		{
			bKey_NO = 1;
		}
		
		if((uiReleaseKey_CNT > 2000) && (uiReleaseKey_CNT < 3000))
		{
			ucMTR_State = 4;
		}
		else if(uiReleaseKey_CNT > 10000)
		{
			ucMTR_State = 0;
		}
	}
}



//===============================================
//
//===============================================
void	ReadMTRState(void)
{
	switch(ucMTR_State)
	{
		case 0:
			uiADC_ValueTemp = 0;
		break;
		
		case 1:
			uiADC_ValueTemp = PWM_MAX_Gear1;
		break;
		
		case 2:
			uiADC_ValueTemp = PWM_MAX_Gear2;
		break;
		
		case 3:
			uiADC_ValueTemp = PWM_MAX_Gear3;
		break;
		
		case 4:
			uiADC_ValueTemp = PWM_MAX_Gear4;
		break;
		
		default:
			uiADC_ValueTemp = 0;
		break;
	}
	
	uiADCSum -= uiVRValue[ucVRIndex];
	uiADCSum += uiADC_ValueTemp;
	uiVRValue[ucVRIndex] = uiADC_ValueTemp;
	ucVRIndex ++;
	ucVRIndex = ucVRIndex & 3;
	uiVRValue_Final = uiADCSum >> 2;
	
	asm("clr	wdt");
}






//===============================================
//
//===============================================
void	ReadVDC_PowerON(void)
{
	uiADC_ValueTemp = _isrl1;
	uiADC_ValueTemp += _isrh1 << 8;
	_iseocb = 0;
	uiVDCValue_Final = uiADC_ValueTemp;
	if(uiVDCValue_Final > 0x237)
	{
		bVDC_WorkOK = 1;
	}
	else
	{
		bVDC_WorkOK = 0;
	}
	bVDC_WorkOK = 1;  //HZS
}


//===============================================
//
//
//===============================================
void	ReadVDC(void)
{
	uiADC_ValueTemp = _isrl1;
	uiADC_ValueTemp += _isrh1 << 8;
	_iseocb = 0;
	
	uiVDCADCSum -= uiVDCValue[ucVDCIndex];
	uiVDCADCSum += uiADC_ValueTemp;
	uiVDCValue[ucVDCIndex] = uiADC_ValueTemp;
	ucVDCIndex ++;
	ucVDCIndex = ucVDCIndex & 3;
	uiVDCValue_Final = uiVDCADCSum >> 2;
	
	if(bVDC_WorkOK)	
	{
		if(uiVDCValue_Final > 0x326)		
		{
			bVoltageOver = 1;
			
		}
		else if((uiVDCValue_Final < 0x30d) && (!bVoltageUnder))	
		{
			bVoltageOver = 0;
			bVoltageErrorFlag = 0;
			uiVoltageCheckCnt = 0;
		}
		
		if(uiVDCValue_Final < 0x22a)	
		{
			bVoltageUnder = 1;
			
		}
		else if((uiVDCValue_Final > 0x237) && (!bVoltageOver))
		{
			bVoltageUnder = 0;
			bVoltageErrorFlag = 0;
			uiVoltageCheckCnt = 0;
		}
	}
	else			
	{
		if(uiVDCValue_Final > 0x2c0)	
		{
			bVoltageOver = 1;
			
		}
		else if((uiVDCValue_Final < 0x2b3) && (!bVoltageUnder))
		{
			bVoltageOver = 0;
			bVoltageErrorFlag = 0;
			uiVoltageCheckCnt = 0;
		}
		
		if(uiVDCValue_Final < 0x16D)
		{
			bVoltageUnder = 1;
			
		}
		else if((uiVDCValue_Final > 0x17D) && (!bVoltageOver))
		{
			bVoltageUnder = 0;
			bVoltageErrorFlag = 0;
			uiVoltageCheckCnt = 0;
		}
	}
			
			bVoltageUnder = 0;			//HZS
			bVoltageErrorFlag = 0;		//HZS
			uiVoltageCheckCnt = 0;		//HZS
	asm("clr	wdt");
	
}



//===============================================
//
//===============================================
void	ReadCurrent(void)
{
	uiADC_ValueTemp = _isrl0;
	uiADC_ValueTemp += _isrh0 << 8;
	_iseocb = 0;
	
	uiCurrentADCSum -= uiCurrentValue[ucCurrentIndex];
	uiCurrentADCSum += uiADC_ValueTemp;
	uiCurrentValue[ucCurrentIndex] = uiADC_ValueTemp;
	ucCurrentIndex ++;
	ucCurrentIndex = ucCurrentIndex & 3;
	uiCurrentValue_Final = uiCurrentADCSum >> 2;
	
	if((uiCurrentValue_Final > 500) && bPermitStart)
	{
		bCurrentLimit = 1;
		if(uiTempPWM > 80)
		{
			uiTempPWM --;
			ValueTemp = (unsigned char)(uiTempPWM >> 8);
		    _dutr0h = ValueTemp;
		    ValueTemp = (unsigned char)uiTempPWM;
			_dutr0l = ValueTemp;
			_pwmsuf = 1;
		}
		
	}
	else
	{
		bCurrentLimit = 0;
	}
	
	asm("clr	wdt");
}




//===============================================
//
//===============================================
void	get_drag_pwm(void)
{
	asm("MOV	A,80H");		//5c
	asm("MOV	MDU1R0,A");
	asm("MOV	A,0EEH");		//ee
	asm("MOV	MDU1R1,A");
	asm("MOV	A,0H");			//0
	asm("MOV	MDU1R2,A");

	asm("MOV	A,0");
	asm("MOV	MDU1R3,A");
	asm("MOV	A,_uiVDCValue_Final[0]");
	asm("MOV	MDU1R4,A");
	asm("MOV	A,_uiVDCValue_Final[1]");
	asm("MOV	MDU1R5,A");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("MOV	A,MDU1R0");
	asm("MOV	_uiDragPWM[0],A");
	asm("MOV	A,MDU1R1");
	asm("MOV	_uiDragPWM[1],A");
	
	
	if(uiDragPWM > 700)
	{
		uiDragPWM = 700;		//HZS
	}
	else if(uiDragPWM < 50)
	{
		uiDragPWM = 50;
	}
	
	//uiDragPWM = 450;	//for test
}

