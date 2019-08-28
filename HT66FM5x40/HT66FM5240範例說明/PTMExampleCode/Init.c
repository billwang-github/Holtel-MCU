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
	_smod=0x01;	//�T��ֳt����\��B�T��IDLE�Ҧ�	Fsys=Fh=20MHZ
	while((_smod&0x04)==0);	//���ݮ���í�w
}

void GPIOInit(void)
{
	_papu6=0;	//���W��
    _pac6=0;	//�ݤf�]����X�Ҧ�
	_pa6=1;		//�ݤf��X���q��	
}

void WatchDogInit(void)
{
	_wdtc=0x57;	//IDLE�Ҧ��ɺ���Fsys�����B�ݪ����ɶ�=2^18/Fs	(Fs=Fsub�BFs=Fsys/4)
}


/****************************************/
void PwmInit(void)
{
	_pcps0=0xAA;	//C�޸}�@�Υ\��]�m	PC0-PC5�]��PWM�f
	_pcps1=0x0A;
	
		
	_pwmc=0x81;		//���߹���Ҧ�1�B Fpwm=20MHZ�B�T��e�Ť��_�B���\��s 	
	
	_prdrh=(u8)(PWMPERIOD>>8);	//�]�m�g���H�X�h
	_prdrl=(u8)(PWMPERIOD);
	
	_dutr0h=0x00;	//�e�Ť�H�s��
	_dutr0l=0x00;
	_dutr1h=0x00;
	_dutr1l=0x00;	
	_dutr2h=0x00;
	_dutr2l=0x00;
	
	_pwmme=0x00;	//�T��j���X�\��
	_pwmmd=0x00;	//�j���X�q���H�s��
	
	_mcf=0x85;		//S/W Mask �Ҧ��B���ɿ�X�BPWM��X�ϯ�B����PWM��X
	_dts=0xA4;		//�ϯ঺�ϡB���Ϯɶ���1us
	_plc=0x00;		//���ʬ����ۿ�X
	
	_pwmc|=0x08;	//�}��PWM�p�ƾ�	
}


void SetDuty(u16 duty)
{
	if(duty>PWMPERIOD)
	{
		duty=PWMPERIOD;	
	}
	_dutr0h=(u8)(duty>>8);	//�]�m�e�Ť�H�s��
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
	_pdps0|=0x50;			//PD2�BPD3�]��TP1_0�BTP1_1	
	_ptm1c0=0x10;			//�p�Ʈ����אּ�t�ή���=20MHZ
	_ptm1c1=0xA8;			//PWM�γ�߽ļҦ��BPWM��X�B�����ġB�P��		
	_ptm1rpl=(u8)(TIMER1_PWMPERIOD);	//�]�m�g���Ȭ�1280�]PWM�g����64us�^
	_ptm1rph=(u8)(TIMER1_PWMPERIOD>>8);	
	_ptm1al=0x00;			//�]�m��l�e�Ť�0
	_ptm1ah=0x00;	
	_ptm1c0|=0x08;			//�Ұʭp�ƾ�
	
	#elif defined MONOPULSE_Mode
	_pdps0|=0x50;			//PD2�BPD3�]��TP1_0�BTP1_1	
	_ptm1c0=0x10;			//�p�Ʈ����אּ�t�ή���=20MHZ
	_ptm1c1=0xB8;			//PWM�γ�߽ļҦ��B��߽Ŀ�X�B�����ġB�P��		
	_ptm1al=(u8)(Duty);		//�]�m��߽Ī��e��
	_ptm1ah=(u8)(Duty>>8);	
	_ptm1c0|=0x08;			//�Ұʭp�ƾ�
	
	#elif defined COMPARE_Mode
	_pdps0|=0x50;			//PD2�BPD3�]��TP1_0�BTP1_1	
	_ptm1c0=0x10;			//�p�Ʈ����אּ�t�ή���=20MHZ
	_ptm1c1=0x34;			//����ǰt��X�Ҧ��B��X½��B��l���C�B�ϬۡBP���������ǰt�ɲM�s�p�ƾ�	
	_ptm1rpl=(u8)(TIMER1_PWMPERIOD);	//�]�m�����P����
	_ptm1rph=(u8)(TIMER1_PWMPERIOD>>8);	
	_ptm1al=(u8)(Duty);					//�]�m�����A����
	_ptm1ah=(u8)(Duty>>8);	
	
	//_tm1af=0;				//�M�����A�ǰt���_�лx��
	//_tm1ae=1;				//���\���A�ǰt���_
	_tm1pf=0;				//�M�����P�ǰt���_�лx��
	_tm1pe=1;				//���\���P�ǰt���_
	_mf5f=0;				//�M���h�\��5���_�лx��
	_mf5e=1;				//���\�h�\��5���_
	_ptm1c0|=0x08;			//�Ұʭp�ƾ�
	
	#elif defined EVENTCOUNT_Mode
	//_pdps0|=0x50;			//PD2�BPD3�]��TP1_0�BTP1_1	
	_ptm1c0=0x10;			//�p�Ʈ����אּ�t�ή���=20MHZ
	_ptm1c1=0xC0;			//�w��\�p�ƾ��Ҧ��BP���������ǰt�ɲM�s�p�ƾ�		
	_ptm1rpl=(u8)(TIMER1_PWMPERIOD);		//�]�m�w�ɮɶ�
	_ptm1rph=(u8)(TIMER1_PWMPERIOD>>8);
		
	//_tm1af=0;				//�M�����A�ǰt���_�лx��
	//_tm1ae=1;				//���\���A�ǰt���_
	_tm1pf=0;				//�M�����P�ǰt���_�лx��
	_tm1pe=1;				//���\���P�ǰt���_
	_mf5f=0;				//�M���h�\��5���_�лx��
	_mf5e=1;				//���\�h�\��5���_		
	_ptm1c0|=0x08;			//�Ұʭp�ƾ�
	#elif defined CATCH_Mode
	//_pdps0|=0x50;			//PD2�BPD3�]��TP1_0�BTP1_1	
	_ptm1c0=0x10;			//�p�Ʈ����אּ�t�ή���=20MHZ
	_ptm1c1=0x62;			//������J�Ҧ��B���u��J�����B�����H���Ӧ�TCKn�}		
	_ptm1rpl=0x00;			//�]�m�̪������ɶ�(65536*0.05us=3276us)
	_ptm1rph=0x00;
		
	_tm1af=0;				//�M�����A�ǰt���_�лx��
	_tm1ae=1;				//���\���A�ǰt���_
	//_tm1pf=0;				//�M�����P�ǰt���_�лx��
	//_tm1pe=1;				//���\���P�ǰt���_
	_mf5f=0;				//�M���h�\��5���_�лx��
	_mf5e=1;				//���\�h�\��5���_		
	_ptm1c0|=0x08;			//�Ұʭp�ƾ�	
	#endif	
}

void Timer1_SetDuty(u16 duty,u16 period)
{
	#ifdef PWM_Mode
	if(duty>TIMER1_PWMPERIOD)
	{
		duty=TIMER1_PWMPERIOD;	
	}		
	_ptm1al=(u8)(duty);		//�]�m�e�Ť�H�s��
	_ptm1ah=(u8)(duty>>8);
	#elif defined MONOPULSE_Mode
	_ptm1al=(u8)(duty);		//�]�m�߽ļe��
	_ptm1ah=(u8)(duty>>8);
	#elif defined COMPARE_Mode
	_ptm1al=(u8)(duty);		//�]�m����H�s��A
	_ptm1ah=(u8)(duty>>8);
	_ptm1rpl=(u8)(period);	//�]�m����H�s��P
	_ptm1rph=(u8)(period>>8);	
	#elif defined EVENTCOUNT_Mode
	_ptm1rpl=(u8)(period);	//�]�m����H�s��P
	_ptm1rph=(u8)(period>>8);
	#endif
}
