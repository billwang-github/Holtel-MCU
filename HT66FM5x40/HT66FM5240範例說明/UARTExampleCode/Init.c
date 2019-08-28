#include "HT66FM5240.h"
#include "FuncTion.h"


void SystemInit(void)
{
	ClockInit();
	GPIOInit();
	UartInit();
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
	
	_papu3=1;	//�W��
	_papu4=1;	//�W��
	_papu5=1;	//�W��
		
}

void WatchDogInit(void)
{
	_wdtc=0x57;	//IDLE�Ҧ��ɺ���Fsys�����B�ݪ����ɶ�=2^18/Fs	(Fs=Fsub�BFs=Fsys/4)
}

/*************************************/
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