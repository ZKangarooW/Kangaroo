#include "ZeroCross.h"
#include "Gpio.h"

void ZeroCross_Config(void)
{
	/*
	(1)����P20 IO����
	*/
	GPIO_SET_MUX_MODE(P20CFG, GPIO_MUX_GPIO);		//����P20ΪGPIOģʽ
	GPIO_ENABLE_INPUT(P2TRIS, GPIO_PIN_0);			//����Ϊ����ģʽ
	GPIO_ENABLE_RD(P2RD, GPIO_PIN_0);				//��������
	/*
	(2)�����жϷ�ʽ
	*/
	GPIO_SET_INT_MODE(P20EICFG, GPIO_INT_BOTH_EDGE);	//����Ϊ�������½����ж�ģʽ
	GPIO_EnableInt(GPIO2, GPIO_PIN_0_MSK);			//����P16�ж�
	/*
	(3)�����ж����ȼ�
	*/
	IRQ_SET_PRIORITY(IRQ_P2, IRQ_PRIORITY_LOW);
	/*
	(4)�������ж�
	*/	
	IRQ_ALL_ENABLE();	
}

