#include "Drv_KEY.h"

/**********局部变量声明******/
float Key_Cnt1;//按下时间
uint8_t Key_Flag1;//按键按下标志
uint8_t LongPress1;//按键长按标志

/*
*****************************************************************
 * 函数原型：void Key_Scan(float dT)
 * 功    能：矩阵按键扫描
*****************************************************************
*/
void Key_Scan(float dT)
{
	/************************************Start键**************************************/
	if(KEY1 == 0)//按下按键
	{
		if(LongPress1 == 0)//没有长按过
		{
			Key_Cnt1 += dT;//按下时间++
			Key_Flag1 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag1 == 1)//按键被按下
	{
		if(KEY1 != 0)//抬起按键
		{   
			if(Key_Cnt1 > 0.1 && Key_Cnt1 < 1.5)//小于1.5S是单击
			{
                if(sys.Run_Status == 0)//系统没有启动的话
                {
                    sys.Run_Status = 1;//启动系统
                    Time.Rel = 360;//6分钟
                    LED2_ON;//打开系统运行灯
                    Motor_ON;//打开电机电源
                }
                else//系统启动的话
                {
                    sys.Run_Status = 0;//启动系统
                    LED2_OFF;//关闭系统运行灯
                    Motor_OFF;//关闭电机电源
                }
			}
			Key_Flag1 = 0;//按键事件结束，等待下一次按下
			LongPress1 = 0;//长按标志清零
			Key_Cnt1 = 0;//按钮计数清零
		}
		if(Key_Cnt1 > 1.5 && Key_Cnt1 < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress1 == 0)//如果没有一直一直长按着
			{
				LongPress1 = 1;//长按标志置一
			}
		}
	}
}
