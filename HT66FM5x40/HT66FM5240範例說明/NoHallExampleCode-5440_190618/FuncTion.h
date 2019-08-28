#ifndef _FUNCTION_H
#define _FUNCTION_H

typedef unsigned int __sfr_word;	//2014-07-16
#define DEFINE_SFR(sfr_type, sfr, addr) static volatile sfr_type sfr __attribute__ ((at(addr)))
DEFINE_SFR(__sfr_word, _addata, 0x36);	//ADCRL + ADCRH
#define NOHALL_MODE
//#define UART_TEST_EN
//#define IIC_TEST_EN
//#define SOFTMODE



#define DI()   (_emi=0)
#define EI()   (_emi=1)
#define FeedWatchDog()		asm("clr wdt")
#define NOP					asm("nop")
#define GetTimerCnt()		((_captmch<<8)|_captmcl)	//獲取捕捉定時器的捕捉值
#define GetHallPort()		((_pa&0x38)>>3)

#define StarCAPTM()			{_captmdl=0;_captmdh=0;_captc0|=0x08;}
#define StopCAPTM()			(_captc0&=0xF7)

#define u8   unsigned char
#define s8   char
#define u16  unsigned int //long
#define s16  int	//long
#define u32  unsigned long
#define s32  long

typedef struct {
	u8  bit0 : 1;
	u8  bit1 : 1;
	u8  bit2 : 1;
	u8  bit3 : 1;
	u8  bit4 : 1;
	u8  bit5 : 1;
	u8  bit6 : 1;
	u8  bit7 : 1;
	}Byte;




typedef union{
	struct {
	u16  DL : 8;
	u16  DH : 8;
	}Byte;
	u16  Word; 
} WORD;



/**********************************/
#ifdef SOFTMODE
extern const unsigned char PWMME[8];
extern const unsigned char PWMMD[8];
#endif

extern const unsigned char Degree60to120[8];
extern const unsigned char Reversal_Hall[8];
extern const unsigned char ucNextHall[8];
extern const unsigned char ucPrevHall[8];

extern u8 ChannelCnt;
extern u8 MC_HallPortVal;
extern u8 MC_PrevHallPortVal;
extern u8 MC_NewHall;
extern u8 MC_PrevHall;
extern u8 MC_ErrHallVal1;
extern u8 MC_ErrHallVal2;
extern u8 Time1msCnt;
extern u8 MC_MotorStartCnt;
extern u8 TakeTurnOkCnt;
extern u8 TakeTurnTimeCnt;

extern u8 Test[8];


extern u16 TimeCnt;
extern u16 AdData[4];
extern u16 MC_ActPWM;
extern u16 MC_DecPWM;
extern u16 MC_SpeedTime;
extern u16 MC_PrevSpeedTime;
extern u16 MC_HallDelayTime;
extern u16 MC_HallDelayCnt;
extern u16 LastDuty;

extern u16 MC_HanderBarAD;

extern Byte Flag01;
#define bOverCurrentFlag   			Flag01.bit0
#define bStopFlag   			 	Flag01.bit1
#define bRunFlag   				 	Flag01.bit2
#define bDegree_60Flag   		    Flag01.bit3
#define bTime1msFlag   				Flag01.bit4
#define bReversalFlag   			Flag01.bit5
#define bStallFlag   				Flag01.bit6
#define bPhaseChangFlag   			Flag01.bit7

extern Byte Flag02;
#define bTakeTurnFlag   			Flag02.bit0
//#define bStopFlag   			 	Flag02.bit1
//#define bRunFlag   				 	Flag02.bit2
//#define bDegree_60Flag   		    Flag02.bit3
//#define bTime1msFlag   				Flag02.bit4
//#define bReversalFlag   			Flag02.bit5
//#define bStallFlag   				Flag02.bit6
//#define bPhaseChangFlag   			Flag02.bit7

/**********函數聲明**************/
void SystemInit(void);
void ClockInit(void);
void GPIOInit(void);
void WatchDogInit(void);
void PwmInit(void);
void SetDuty(u16 duty);
void HallInit(void);
void ADInit(void);
u16 AdSample_1(u8 channel);
void ProtectInit(void);
void CaptmInit(void);

#ifdef UART_TEST_EN
void UartInit(void);
void UartHand(void);
void UartPutChar(u8 value);

extern u8 TxdBuff[5];
extern u8 RxdBuff[5];
extern u8 TxdPoint;
extern u8 TxdPoint2;
extern u8 TxdCnt;
extern u8 RxdCnt;
#endif

#ifdef IIC_TEST_EN
void IICInit(void);
extern u16 IIC_TxdData;
extern u8 IIC_RxdData;
#endif

void Delay_2us(u16 t);
void Delay_1ms(u16 t);
void HandleSpeed(void);
u8 MotorLocation(void);
void TakeTurn(void);

/*****************************/
#define PWMPERIOD 	640		//64us
#define MAX_PWM     642		//PWMPERIOD

#define ZERO_DRIVER_AD		60		//300mv(1=4.8mv)
#define START_DRIVER_AD		125		//600mv(1=4.8mv)
#define MAX_DRIVER_AD		680		//4.0v(1=4.8mv)
#define ZERO_CURRENT_AD		70

#define CURRENT_CHAN	(0)	//AN0
#define VOLTAGE_CHAN	(1)	//AN1
#define DRIVER_CHAN		(7)	//AN6

#define CURRENT_AD  AdData[0]
#define DRIVER_AD   AdData[1]
#define VOLTAGE_AD  AdData[2]


#ifdef SOFTMODE
#define ChangeDrive(value)	{_pwmme=PWMME[value];_pwmmd=PWMMD[value];}
#else
#define ChangeDrive(value)	(_hdcd=value)
#endif

#define ReadHallPort()		(_mcd&0x07)
//#define SetDelayTime(value)	{_ptm0ah=(u8)(value>>8);_ptm0al=(u8)(value);}	//設置比較器A的值（設置延遲時間）			
#define SetDelayTime(value)	{_ptm0ah=(u8)(value>>8);_ptm0al=(u8)(value);_pt0on=1;}	//設置比較器A的值（設置延遲時間）
#endif

