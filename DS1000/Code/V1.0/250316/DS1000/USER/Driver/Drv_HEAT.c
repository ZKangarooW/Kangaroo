#include "Drv_HEAT.h"

Heater_t Heater;

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
函数名称：void Timer1TriggerDelay(unsigned int us)
函数功能：重新设定定时器1的定时时长
输入参数：us:所需设定的时长单位us
输出参数：
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
    TCON &= ~0x40;	//关闭定时器1
	TH1 = 0xfe;
	TL1 += 0x0b;
	P05 = ~P05;
	Heater_SCR_IO = Off;
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
	
	/*SCR动作*/
	if(1 == Heater.SCROn)
	{
//        P05 = 1;
        Heater_SCR_IO = On;
	}
}
