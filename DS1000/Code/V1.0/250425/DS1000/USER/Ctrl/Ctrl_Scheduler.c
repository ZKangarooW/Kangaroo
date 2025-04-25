#include "Ctrl_Scheduler.h"

uint16_t  T_cnt_2ms=0,
          T_cnt_10ms=0,
		  T_cnt_50ms=0,
//          T_cnt_100ms=0,
          T_cnt_500ms=0,
          T_cnt_1S=0;
          
float time_50us;
void Loop_Check(void)
{
    time_50us += 0.05f;
    if(time_50us >= 0.95f)//1ms
    {
        time_50us = 0;
        T_cnt_2ms++;
        T_cnt_10ms++;
        T_cnt_50ms++;
//        T_cnt_100ms++;
        T_cnt_500ms++;
        T_cnt_1S++;

        Sys_Loop();
    }
}

/*
*****************************************************************
 * 函数原型：void TMR0_Config(void)
 * 功    能：定时器0配置
*****************************************************************
*/
void TMR0_Config(void)
{
	/*
	(1)设置Timer的运行模式
	*/
	TMR_ConfigRunMode(TMR0, TMR_MODE_TIMING,TMR_TIM_AUTO_8BIT);	
    
	/*
	(2)设置Timer 运行时钟
	*/
	TMR_ConfigTimerClk(TMR0, TMR_CLK_DIV_12);/*Fsys = 48Mhz，Ftimer = 4Mhz,Ttmr=0.25us*/
    
	/*
	(3)设置Timer周期
	*/	
	TMR_ConfigTimerPeriod(TMR0, 256-200, 256-200);// 200*0.25us = 50us,递增计数

	/* 
	(4)开启中断
	*/
	TMR_EnableOverflowInt(TMR0);

	/*
	(5)设置Timer中断优先级
	*/	
	IRQ_SET_PRIORITY(IRQ_TMR0,IRQ_PRIORITY_HIGH);
	IRQ_ALL_ENABLE();	

	/*
	(6)开启Timer
	*/
	TMR_Start(TMR0);
}

static void Loop_2ms(float dT)//2ms执行一次
{
    __CMS_CheckTouchKey();//触摸的函数
}

static void Loop_10ms(float dT)//10ms执行一次
{   
    Key_Scan(dT);//矩阵按键扫描
    Twinkle(dT);//闪烁函数
    Show_Display(dT);//显示屏幕内容
    
}

static void Loop_50ms(float dT)//50ms执行一次
{
    Check_Set(dT);//检测设置
    Buzzer_Status(dT);//蜂鸣器的状态检测
}

//static void Loop_100ms(float dT)//100ms执行一次
//{
//    
//}

static void Loop_500ms(float dT)//500ms执行一次
{
    Cheak_TimeDown(dT);//时间倒计时检测
    Param_Save_Overtime(dT);//保存标志位置1，0.5s后保存
	Check_Press(dT);//检测按键按下状态
}

static void Loop_1S(float dT)//1S执行一次
{
	Temp_Control(dT);//温度加热控制
}

void Sys_Loop(void)
{
    if(T_cnt_2ms >= 2) {
        Loop_2ms(0.002f);
        T_cnt_2ms = 0;
    }
    if(T_cnt_10ms >= 10) {
        Loop_10ms(0.01f);
        T_cnt_10ms = 0;
    }
	if(T_cnt_50ms >= 50) {
        Loop_50ms(0.05f);
        T_cnt_50ms = 0;
    }
//    if(T_cnt_100ms >= 100) {
//        Loop_100ms(0.1f);
//        T_cnt_100ms = 0;
//    }
    if(T_cnt_500ms >= 500) {
        Loop_500ms(0.5f);
        T_cnt_500ms = 0;
    }
    if(T_cnt_1S >= 1000) {
        Loop_1S(1.0f);
        T_cnt_1S = 0;
    }
}
