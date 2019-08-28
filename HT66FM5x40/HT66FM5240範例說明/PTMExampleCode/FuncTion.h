#ifndef _FUNCTION_H
#define _FUNCTION_H


//#define PWM_Mode			//PWM�Ҧ�
//#define MONOPULSE_Mode 		//��߽Ŀ�X�Ҧ�
#define COMPARE_Mode		//�����X�Ҧ�
//#define CATCH_Mode		//������J�Ҧ�
//#define EVENTCOUNT_Mode	//�w��/�ƥ�p�ƼҦ�


#define DI()   (_emi=0)
#define EI()   (_emi=1)
#define FeedWatchDog()		asm("clr wdt")

#define u8  unsigned char
#define s8  char
#define u16 unsigned int //long
#define s16 int	//long
#define u32 unsigned long
#define s32 long

#define PWMPERIOD 	640		//64us
#define TIMER1_PWMPERIOD 	1280	//64us

/**********************************/
extern u16 Duty;
extern u16 Period;
extern u16 CatchCnt;
extern u16 PrevCatchCnt;
extern u16 TimeCnt;


/**********����n��**************/
void SystemInit(void);
void ClockInit(void);
void GPIOInit(void);
void WatchDogInit(void);
void PwmInit(void);
void SetDuty(u16 duty);
		
void Timer1Init(void);
void Timer1_SetDuty(u16 duty,u16 period);
#endif

