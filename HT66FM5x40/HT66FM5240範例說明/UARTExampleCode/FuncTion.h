#ifndef _FUNCTION_H
#define _FUNCTION_H


#define DI()   (_emi=0)
#define EI()   (_emi=1)
#define FeedWatchDog()		asm("clr wdt")

#define GetTimerCnt()		((_captmch<<8)|_captmcl)	//獲取捕捉定時器的捕捉值
#define GetHallPort()		((_pa&0x38)>>3)

#define u8  unsigned char
#define s8  char
#define u16 unsigned int //long
#define s16 int	//long
#define u32 unsigned long
#define s32 long

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
extern const u8 PWMME[8];
extern const u8 PWMMD[8];
extern const u8 Degree60to120[8];
extern const u8 Reversal_Hall[8];


extern u8 ChannelCnt;
extern u8 MC_HallPortVal;
extern u8 MC_PrevHallPortVal;
extern u8 MC_NewHall;
extern u8 MC_PrevHall;
extern u8 MC_ErrHallVal1;
extern u8 MC_ErrHallVal2;

extern u8  Time1msCnt;
extern u8 TxdBuff[5];
extern u8 RxdBuff[5];
extern u8 TxdPoint;
extern u8 TxdPoint2;
extern u8 TxdCnt;
extern u8 RxdCnt;
extern u8  RxdData;
extern u8  TxdData;

extern u16 TimeCnt;
extern u16 AdData[4];
extern u16 MC_ActPWM;
extern u16 MC_DecPWM;
extern u16 MC_SpeedTime;
extern u16 MC_PrevSpeedTime;



extern Byte Flag01;
#define bOverCurrentFlag   			Flag01.bit0
#define bStopFlag   			 	Flag01.bit1
#define bRunFlag   				 	Flag01.bit2
#define bDegree_60Flag   		    Flag01.bit3
#define bTime1msFlag   				Flag01.bit4
#define bReversalFlag   			Flag01.bit5

//#define bOverCurrentFlag   Flag01.bit6
//#define bOverCurrentFlag   Flag01.bit7


/**********函數聲明**************/
void SystemInit(void);
void ClockInit(void);
void GPIOInit(void);
void WatchDogInit(void);
void UartInit(void);
void UartHand(void);
void UartPutChar(u8 value);

/*****************************/
#define PWMPERIOD 	640		//64us
#define MAX_PWM     PWMPERIOD
#define START_DRIVER_AD		500		//600mv(1=1.2mv)
#define MAX_DRIVER_AD		  3400	//4.0v(1=1.2mv)


#define CURRENT_CHAN	(6)	//AP
#define VOLTAGE_CHAN	(5)	//AD5
#define DRIVER_CHAN		(4)	//AD4

#define CURRENT_AD  AdData[0]
#define DRIVER_AD   AdData[1]
#define VOLTAGE_AD  AdData[2]

#endif

