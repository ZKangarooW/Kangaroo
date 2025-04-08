#include "ZeroCross.h"
#include "Gpio.h"

void ZeroCross_Config(void)
{
	/*
	(1)设置P20 IO功能
	*/
	GPIO_SET_MUX_MODE(P20CFG, GPIO_MUX_GPIO);		//设置P20为GPIO模式
	GPIO_ENABLE_INPUT(P2TRIS, GPIO_PIN_0);			//设置为输入模式
	GPIO_ENABLE_RD(P2RD, GPIO_PIN_0);				//开启下拉
	/*
	(2)设置中断方式
	*/
	GPIO_SET_INT_MODE(P20EICFG, GPIO_INT_BOTH_EDGE);	//设置为上升、下降沿中断模式
	GPIO_EnableInt(GPIO2, GPIO_PIN_0_MSK);			//开启P16中断
	/*
	(3)设置中断优先级
	*/
	IRQ_SET_PRIORITY(IRQ_P2, IRQ_PRIORITY_LOW);
	/*
	(4)开启总中断
	*/	
	IRQ_ALL_ENABLE();	
}

