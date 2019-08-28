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
	_smod=0x01;	//�T��ֳt����\��B�T��IDLE�Ҧ�	Fsys=Fh=20MHZ
	while((_smod&0x04)==0);	//���ݮ���í�w
}

void GPIOInit(void)
{
	_papu6=0;	//���W��
    _pac6=0;	//�ݤf�]����X�Ҧ�
	_pa6=0;		//�ݤf��X���q��
	
	#ifndef NOHALL_MODE
	_papu3=1;	//�W��
	_papu4=1;	//�W��
	_papu5=1;	//�W��
	#endif		
}

void WatchDogInit(void)
{
	_wdtc=0x57;	//IDLE�Ҧ��ɺ���Fsys�����B�ݪ����ɶ�=2^18/Fs	(Fs=Fsub�BFs=Fsys/4)
}


/****************PWM��l��************************/
void PwmInit(void)
{
	_pcps0=0xAA;	//C�޸}�@�Υ\��]�m	PC0-PC5�]��PWM�f
	_pcps1=0x0A;
			
	_pwmc=0x81;		//���߹���Ҧ�1�B Fpwm=20MHZ�B�T��e�Ť��_�B���\��s 	
			
	_prdrh=(u8)(PWMPERIOD>>8);	//�]�m�g���H�s��
	_prdrl=(u8)(PWMPERIOD);
	
	_dutr0h=0x00;	//�e�Ť�H�s��
	_dutr0l=0x00;
	_dutr1h=0x00;
	_dutr1l=0x00;	
	_dutr2h=0x00;
	_dutr2l=0x00;
	
	_pwmme=0x3F;	//�T��PWM��X
	_pwmmd=0x00;	//�j���X�q���H�s�� �j���X�C�q��
	
	#ifdef SOFTMODE
	_mcf=0x8D;		//S/W Mask �Ҧ��B�D���ɿ�X�BPWM��X�ϯ�B����PWM��X�B�O�@�ɿ�X��0
	#else
	//_mcf=0x0D;		//H/W Mask �Ҧ��B�D���ɿ�X�BPWM��X�ϯ�B����PWM��X�B�O�@�ɿ�X��0
	_mcf=0x0C;		//H/W Mask �Ҧ��B�D���ɿ�X�BPWM��X�ϯ�B����PWM��X�B�O�@�ɿ�X��0
	#endif
	
	//_dts=0xA4;		//�ϯ঺�ϡB���Ϯɶ���1us
	_plc=0x00;		//���ʬ����ۿ�X

	
	_pwmpf=0;	//�M��PWM�g�����_�лx
	_pwmpe=1;	//���\PWM�g�����_
//**	_mf2f=0;	//�M���h�\��2���_�лx
//**	_mf2e=1;	//���\�h�\��2���_
	_int_pri3f = 0;
	_int_pri3e = 1;
	
	
	_pwmc|=0x08;	//�}��PWM�p�ƾ�	
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
		
	_dutr0h=dutyH;	//�]�m�e�Ť�H�s��
	_dutr0l=dutyL;
	_dutr1h=dutyH;
	_dutr1l=dutyL;
	_dutr2h=dutyH;
	_dutr2l=dutyL;	
}

/*****�N����l��*****/
void HallInit(void)
{		
	#ifndef NOHALL_MODE	//���N��
    _integ0=0x3f;   //Hall���_�����H1�BH2�BH3�B����u���_
    _hdcr = 0xD1; 	//Hall�H���L����BBit4:120�X�BBit3:S/W�Ҧ��B����BHall�ǷP���ѽX�ϯ�	                   					

    #else	//�L�N��
   	_pa3s1=0;	//A�޸}�@�Υ\��]�m	PA3�]��C1P�f
	_pa3s0=1;	
	_pa4s1=1;	//A�޸}�@�Υ\��]�m	PA4�]��C2P�f
	_pa4s0=0;
	_pa5s1=1;	//A�޸}�@�Υ\��]�m	PA5�]��C3P�f
	_pa5s0=0;	
	_pb3s1=1;	//B�޸}�@�Υ\��]�m	PB3�]��CPN�f
	_pb3s0=0;
	
	_cmpc|=0xEE;		//�}�Ҥ����1�B2�B3�A���\�����1�B2�B3�𺢥\��
	_integ0=0x7F;	//Hall���_����ܤ������X�B����u���_
		
	#ifdef SOFTMODE	
	_hdcr = 0xD1; 	//Hall�H���L����BBit4:120�X�BBit3:S/W�Ҧ��B����BHall�ǷP���ѽX�ϯ�
	#else
//	_hdcr = 0x31; 	//Hall�H���ϯੵ���PTM0������ɶ��p�ơB120�X�BS/W�Ҧ��B����BHall�ǷP���ѽX�ϯ�		 	
//	/*�N������PTM0�]�m*/
//	_ptm0c0=0x40;			//�p�Ʈ����אּ�t�ή���=Ftbc=32K(���ɶ���31.25us)
//    _ptm0c1=0x01;			//����ǰt�Ҧ��B�����A�ǰt�ɲM�s�p�ƾ�    
//    SetDelayTime(0);		//�]�m�����A���ȡ]�]�m����ɶ��^

	_hdcr = 0xD1; 	//Hall�H���L����BBit4:120�X�BBit3:S/W�Ҧ��B����BHall�ǷP���ѽX�ϯ�	 	
	/*�N������PTM0�]�m*/
	_ptm0c0=0x40;			//�p�Ʈ����אּ�t�ή���=Ftbc=32K(���ɶ���31.25us)
    _ptm0c1=0xC1;			//�w��/�p�ƼҦ��B�����A�ǰt�ɲM�s�p�ƾ�  
//5240    _mf4f=0;				//�M���h�\��4���_�лx��
//5240	_mf4e=1;				//���\�h�\��4���_ 
	_int_pri10f = 0;
	_int_pri10e = 1;
	_tm0af=0;
	_tm0ae=1; 
	#endif
    #endif
    
    _hchk_num = 0x05;     // Hall���n�o�i���Ƭ�5�]0-32�^
	_hnf_msel = 0x09;	  //�ϯྸ�n�o�i���B�o�i������=fsys/4 
    
    
	_hdcd = 0x00; 	//HallĶ�X����J�ƾڱH�s���M�s
	//AH�BAL�BBH�BBL�BCH�BCL
			
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
//5240	_hallf_mf0f=0;	//�M��Hall�`���_�лx
//5240	_halle_mf0e=1;	//���\Hall�`���_
	_int_pri1f = 0;
	_int_pri1e = 1;
	
	//_mfi0=0x07;		//���\HA�BHB�BHC���_
	_halaf=0;		//�M��HA���_�лx
	_halbf=0;		//�M��HB���_�лx
	_halcf=0;		//�M��HC���_�лx	
	_halae=1;		//�ϯ�HA���_
	_halbe=1;		//�ϯ�HB���_
	_halce=1;		//�ϯ�HC���_	
}

/****************�O�@��l�ơ]�L�y�B���y�B����^********************/
void ProtectInit(void)
{
	_pa1s0=1;		//�޸}�@�Υ\��]�m �]�]�m��AP�\��^PA1--AP
	_pa1s1=0;
	
	_opoms = 0b01000010;	//������W�ɪu���ġB�����B���j10��, 1A=33
	_opcm=255;		//DA����H�s���ȹL�y�q���� 255 => 7.7A
	_opa0cal = 0b01110000;
	
	_mptc1=0x1C;	//�T��n�����_�\��B�ϯ�L�y�O�@�B�ϯ୭�y�O�@�B�ϯ����O�@
	_mptc2=0x1F;	//�n��O�@�B�L�y�O�@�B���y�O�@�B����O�@�����Pause�Ҧ�
	
//5240	_c0f=0;		//�M��������_�лx��
//5240_c0e=1;		//���\������_
	_int_pri2f = 0;
	_int_pri2e = 1;
	_cmpc|=0x11;	//�}�Ҥ����0�B�ϯ�𺢥\��
}

/***************�����w�ɾ���l��************************/
void CaptmInit(void)
{
	_captc0=0x00;		///�p�Ʈ����אּPWM�g���ɶ��]64us�^�B�����q�D�אּH1	
	_captc1=0xF7;		//�������u�����B�ϯஷ���B���n�o�i�ļ˥|���BCAPTM ���n�o�i�������אּ�t�ή���fSYS�B�o�i�ϯ�BCAPTM �p�ƾ������۰ʴ_��ϯ�BCAPTM  �p�ƾ� ����ǰt�۰ʴ_��ϯ�
	
	_captmal=0xFF;		//�]�m������������	//����ɶ��]�w
	_captmah=0xFF;
	
//	_capcf=0;				//�M������ǰt���_�лx��
//	_capce=1;				//���\����ǰt���_
//	_capof=0;				//�M���������_�лx��
//	_capoe=1;				//���\�������_
//5240	_mf1f=0;				//�M���h�\��1���_�лx��
//5240_mf1e=1;				//���\�h�\��1���_
	_int_pri6f = 0;
	_int_pri6e = 1;

	//_captc0|=0x08;		//�Ұʭp�ƾ�	
}

/*****************AD��l��**********************/
void ADInit(void)
{	
	_pa7s0=1;		//�޸}�@�Υ\��]�m �]�]�mAD�q�D�^PA7--AN6, speed control
	_pa7s1=0;
	
	_pd0s0=1;		//�޸}�@�Υ\��]�m �]�]�mAD�q�D�^PD0--AN0 , Iavg
	_pd0s1=0;
	
	_pd1s0 = 1;		//�޸}�@�Υ\��]�m �]�]�mAD�q�D�^PD1--AN1 , Input Voltage
	_pd1s1 = 0;
		
	_adcr1 = 0b00011100;	//���Ĳ�o�q���B�T���\��BPWM�g��Ĳ�oAD�BAD����=Fsys/16�B
	_adcr0 = 0b00000000;	//�}��AD�q���B�ƾڥ�����B��l�q�D�אּAN0�]�����q�D�^
	_adcr2 = 0b00000000;	//12 bits, 1 ch
	_adcr3 = 0x00;
	_addl=0x00;		//ADĲ�o����
	_adbyps = 0x80; //unity gain buffer on

	_adlvdl=0x00;	//�]�mAD�ȵ��f�����(��l���y��)
	_adlvdh=0x00;

	_adhvdl=0xFF;	//�]�mAD�ȵ��f�����(��l���y��)
	_adhvdh=0xFF;
		
	_isaeocf=0;	//�M��AD�ഫ�����лx
	_isaeoce=1;	//���\AD�ഫ�������_
		
//5240	_mf1f=0;	//�M���h�\��1���_�лx
//5240	_mf1e=1;	//���\�h�\��1���_
	_int_pri8f = 0;
	_int_pri8e = 1;
		
}

u16 AdSample_1(u8 channel)
{
	u16 temp;
		
	_aeoce=0;	//�T��AD�ഫ�������_
	_dlstr = 0;	//�T��Ĳ�o�q��	
	_adcr0 &=0xF0;
	_adcr0 |=channel;
	
	_adstr=0;
	_adstr=1;
	_adstr=0;	
	while(_eocb);	//�����ഫ����
		
	temp=(_addata >> 6);	//10��AD
	_dlstr = 1;	//���Ĳ�o�q��	
	_adcr0 &=0xF0;
	_adcr0 |=CURRENT_CHAN;
	ChannelCnt=0;
	_aeocf=0;	//�M��AD�ഫ�����лx
	_aeoce=1;	//���\AD�ഫ�������_
	
	return temp;	
}

/*****************UART��l��********************/
#ifdef	UART_TEST_EN
void UartInit(void)
{
	_pb6s0=1;		//�޸}�@�Υ\��]�m �]�]�mRX�^PB6--RX
	_pb6s1=0;
	_pb7s0=1;		//�޸}�@�Υ\��]�m �]�]�mTX�^PB7--TX
	_pb7s1=0;
	
	_ucr1=0x80;		//�ϯ�UART�B8��ƾڶǿ�B�_������B�@�찱���B�L�Ȱ��r
	_ucr2=0xE4; 	//�o�e�B�����ϯ�B��ܰ��t�i�S�v�B�L�a�}�˴��\��B�L����\��B�T��o�e�Ŷ����_�B�T��o�e�H�s���Ť��_
	_brg=129;       //_brg=20000000/(9600*16)-1=129  (���t�i�S�v�G�i�S�v=fSYS/[16��(N+1)]�B�C�t�i�S�v�G�i�S�v=fSYS/[64��(N+1)])
	
	_uartf=0;		//UART���_�лx�M�s
	_uarte=1;		//�ϯ�UART���_
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

/************IIC��l��*******************/
#ifdef IIC_TEST_EN
void IICInit(void)
{
//	_sclps=1;		//�޸}���m�\��]�m	SCL���m��PB1
//	_sdaps=1;		//�޸}���m�\��]�m	SDA���m��PB2
//		
//	_pb1s0=1;		//�޸}�@�Υ\��]�m �]�]�mSCL�^PB1--SCL
//	_pb1s1=1;	
//	_pb2s0=0;		//�޸}�@�Υ\��]�m �]�]�mSDA�^PB2--SDA
//	_pb2s1=0;
//	_pb2s2=1;	

	_pa0s0=1;		//�޸}�@�Υ\��]�m �]�]�mSCL�^PA0--SDA
	_pa0s1=0;
	
	_pa2s0=1;		//�޸}�@�Υ\��]�m �]�]�mSCL�^PA2--SCL
	_pa2s1=0;
	
	_papu0=1;	//�W��
	_papu2=1;	//�W��
	
	
	_iicc0=0x0A;	//�ϯ�IIC�B�ݰʮɶ��]��4�Өt�ή���
	_iica=0xA0;		//�]�m�������q���a�}
	_i2ctoc=0xBF;	//�ϯ�W�ɱ���B�W�ɮɶ��]���̪�
	
	_iicf=0;		//IIC���_�лx�M�s
	_iice=1;		//�ϯ�IIC���_
	
	_int_pri15f = 0;
	_int_pri15e = 1;	
}
#endif