#include "Drv_HEAT.h"

Heater_t Heater;//控功率

/*
*****************************************************************
 * 函数原型：void ZeroCross_Config(void)
 * 功    能：交流电过零检测的中断配置
*****************************************************************
*/
void ZeroCross_Config(void)
{
	/*
	(1)设置P17 IO功能
	*/
	GPIO_SET_MUX_MODE(P17CFG, GPIO_MUX_GPIO);		//设置P17为GPIO模式
	GPIO_ENABLE_INPUT(P1TRIS, GPIO_PIN_7);			//设置为输入模式
	GPIO_ENABLE_RD(P1RD, GPIO_PIN_7);				//开启下拉
	/*
	(2)设置中断方式
	*/
	GPIO_SET_INT_MODE(P17EICFG, GPIO_INT_BOTH_EDGE);	//设置为上升、下降沿中断模式
	GPIO_EnableInt(GPIO1, GPIO_PIN_7_MSK);			//开启P17中断
	/*
	(3)设置中断优先级
	*/
	IRQ_SET_PRIORITY(IRQ_P1, IRQ_PRIORITY_LOW);
	/*
	(4)开启总中断
	*/	
	IRQ_ALL_ENABLE();	
}

/*
*****************************************************************
 * 函数原型：void TMR1_Config(void)
 * 功    能：定时器1配置
*****************************************************************
*/
void TMR1_Config(void)
{
    /*
	(1)设置Timer的运行模式
	*/
	TMR_ConfigRunMode(TMR1, TMR_MODE_TIMING,TMR_TIM_AUTO_8BIT);	
    
	/*
	(2)设置Timer 运行时钟
	*/
	TMR_ConfigTimerClk(TMR1, TMR_CLK_DIV_12);/*Fsys = 48Mhz，Ftimer = 4Mhz,Ttmr=0.25us*/
    
	/*
	(3)设置Timer周期
	*/	
	TMR_ConfigTimerPeriod(TMR1, 256-200, 256-200);// 200*0.25us = 50us,递增计数

	/*
	(4)开启中断
	*/
	TMR_EnableOverflowInt(TMR1);

	/*
	(5)设置Timer中断优先级
	*/	
	IRQ_SET_PRIORITY(IRQ_TMR1,IRQ_PRIORITY_LOW);
	IRQ_ALL_ENABLE();	

	/*
	(6)开启Timer
	*/
    TMR_Stop(TMR1);
}


/*
*****************************************************************
 * 函数原型：void CtrlHeater_SCR(void)
 * 功    能：控制加热功率
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
	
	/*SCR动作*/
	if(1 == Heater.SCROn)
	{
        Heater_SCR_IO = On;
	}
}

/*
*****************************************************************
 * 函数原型：void GPIO_Interrupt(void)
 * 功    能：交流电过零检测的中断任务函数
*****************************************************************
*/
void GPIO_Interrupt(void)
{
    if(GPIO_GetIntFlag(GPIO1,GPIO_PIN_7))
	{
		GPIO_ClearIntFlag(GPIO1,GPIO_PIN_7);
		//市电50Hz， 10ms进入一次中断
		CtrlHeater_SCR();
        TMR_Start(TMR1);//检测到零点后开启定时器1
	}
}

/*
*****************************************************************
 * 函数原型：void Timer1_IRQ(void)
 * 功    能：定时器1中断任务函数
*****************************************************************
*/
void Timer1_IRQ(void)
{
    static uint8_t T;
    T++;
    if(T >= 200)//50us*200 = 10ms
    {
        T = 0;
        TMR_Stop(TMR1);//停止定时器1
        Heater_SCR_IO = Off;//关闭功率
    }
}

/*
*****************************************************************
 * 函数原型：void HEAT_Init(void)
 * 功    能：初始化加热
*****************************************************************
*/
void HEAT_Init(void)
{
    ZeroCross_Config();
    TMR1_Config();
    
    GPIO_SET_MUX_MODE(P20CFG, GPIO_MUX_GPIO);
    GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_0);
}
