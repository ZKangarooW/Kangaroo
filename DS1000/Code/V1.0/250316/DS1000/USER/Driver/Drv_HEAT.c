#include "Drv_HEAT.h"

Heater_t Heater;

void ZeroCross_Config(void)
{
	/*
	(1)����P17 IO����
	*/
	GPIO_SET_MUX_MODE(P17CFG, GPIO_MUX_GPIO);		//����P17ΪGPIOģʽ
	GPIO_ENABLE_INPUT(P1TRIS, GPIO_PIN_7);			//����Ϊ����ģʽ
	GPIO_ENABLE_RD(P1RD, GPIO_PIN_7);				//��������
	/*
	(2)�����жϷ�ʽ
	*/
	GPIO_SET_INT_MODE(P17EICFG, GPIO_INT_BOTH_EDGE);	//����Ϊ�������½����ж�ģʽ
	GPIO_EnableInt(GPIO1, GPIO_PIN_7_MSK);			//����P17�ж�
	/*
	(3)�����ж����ȼ�
	*/
	IRQ_SET_PRIORITY(IRQ_P1, IRQ_PRIORITY_LOW);
	/*
	(4)�������ж�
	*/	
	IRQ_ALL_ENABLE();	
}

void TMR1_Config(void)
{
	PT1 = 1;
	TMOD |= 0x10;//16bit
	CKCON |= 0x00;//TMR_CLK_DIV_12
	//	TH1 = 0xfe;	//0xFFFF-0xFE0B = 500;  1/(48MHz/12)*500= 125us
	//	TL1 = 0x0b;   
	IP |= 0x08;
	IE |= 0x88;
	//	TCON |= 0x40;
	TCON |=0x80;
}

/*****************************************************************************
�������ƣ�void Timer1TriggerDelay(unsigned int us)
�������ܣ������趨��ʱ��1�Ķ�ʱʱ��
���������us:�����趨��ʱ����λus
���������
******************************************************************************/
void Timer1TriggerDelay(unsigned int us)
{
	unsigned int TimeBuf;
	TimeBuf = 0xFFFF-(us<<2);
	
	TH1 = (TimeBuf>>8)&0xFF;	//0xFFFF-0xFE0B = 500;  1/(48MHz/12)*500= 125us
	TL1 = TimeBuf&0xFF;  
	TCON |= 0x40;
}

void Timer1_IRQ(void)
{
    TCON &= ~0x40;	//�رն�ʱ��1
	TH1 = 0xfe;
	TL1 += 0x0b;
	P05 = ~P05;
	Heater_SCR_IO = Off;
}

/*
*****************************************************************
 * ����ԭ�ͣ�void HEAT_Init(void)
 * ��    �ܣ���ʼ������
*****************************************************************
*/
void HEAT_Init(void)
{
    ZeroCross_Config();
    TMR1_Config();
    
    GPIO_SET_MUX_MODE(P20CFG, GPIO_MUX_GPIO);
    GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_0);
}

void CtrlHeater_SCR(void)
{
    Heater.SCRCnt =(Heater.SCRCnt < U8_MAX)?Heater.SCRCnt+1:0;	
    Heater.SCRFullTimeSet = 100;
    if(Heater.SCRCnt == Heater.SCRFullTimeSet)
    {
        Heater.SCRCnt = 0;
        Heater.SCROnTimeSet = 10;
    }
    
    if(Heater.SCRCnt < Heater.SCROnTimeSet)
    {
        Heater.SCROn = 1;
    }
    else
    {
        Heater.SCROn = 0;
    }
	
	/*SCR����*/
	if(1 == Heater.SCROn)
	{
//        P05 = 1;
        Heater_SCR_IO = On;
	}
}
