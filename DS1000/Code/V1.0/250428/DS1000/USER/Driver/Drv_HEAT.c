#include "Drv_HEAT.h"

Heater_t Heater;//�ع���

/*
*****************************************************************
 * ����ԭ�ͣ�void ZeroCross_Config(void)
 * ��    �ܣ��������������ж�����
*****************************************************************
*/
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

/*
*****************************************************************
 * ����ԭ�ͣ�void TMR1_Config(void)
 * ��    �ܣ���ʱ��1����
*****************************************************************
*/
void TMR1_Config(void)
{
    /*
	(1)����Timer������ģʽ
	*/
	TMR_ConfigRunMode(TMR1, TMR_MODE_TIMING,TMR_TIM_AUTO_8BIT);	
    
	/*
	(2)����Timer ����ʱ��
	*/
	TMR_ConfigTimerClk(TMR1, TMR_CLK_DIV_12);/*Fsys = 48Mhz��Ftimer = 4Mhz,Ttmr=0.25us*/
    
	/*
	(3)����Timer����
	*/	
	TMR_ConfigTimerPeriod(TMR1, 256-200, 256-200);// 200*0.25us = 50us,��������

	/*
	(4)�����ж�
	*/
	TMR_EnableOverflowInt(TMR1);

	/*
	(5)����Timer�ж����ȼ�
	*/	
	IRQ_SET_PRIORITY(IRQ_TMR1,IRQ_PRIORITY_LOW);
	IRQ_ALL_ENABLE();	

	/*
	(6)����Timer
	*/
    TMR_Stop(TMR1);
}


/*
*****************************************************************
 * ����ԭ�ͣ�void CtrlHeater_SCR(void)
 * ��    �ܣ����Ƽ��ȹ���
*****************************************************************
*/
void CtrlHeater_SCR(void)
{
    Heater.SCRCnt =(Heater.SCRCnt < U8_MAX)?Heater.SCRCnt+1:0;	
    Heater.SCRFullTimeSet = 100;
    if(Heater.SCRCnt == Heater.SCRFullTimeSet)
    {
        Heater.SCRCnt = 0;
        Heater.SCROnTimeSet = Heater.PWM;
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
        Heater_SCR_IO = On;
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ�void GPIO_Interrupt(void)
 * ��    �ܣ��������������ж�������
*****************************************************************
*/
void GPIO_Interrupt(void)
{
    if(GPIO_GetIntFlag(GPIO1,GPIO_PIN_7))
	{
		GPIO_ClearIntFlag(GPIO1,GPIO_PIN_7);
		//�е�50Hz�� 10ms����һ���ж�
		CtrlHeater_SCR();
        TMR_Start(TMR1);//��⵽��������ʱ��1
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Timer1_IRQ(void)
 * ��    �ܣ���ʱ��1�ж�������
*****************************************************************
*/
void Timer1_IRQ(void)
{
    static uint8_t T;
    T++;
    if(T >= 200)//50us*200 = 10ms
    {
        T = 0;
        TMR_Stop(TMR1);//ֹͣ��ʱ��1
        Heater_SCR_IO = Off;//�رչ���
    }
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
