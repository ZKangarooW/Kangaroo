#include "Ctrl_DownTime.h"

/*
*****************************************************************
 * 函数原型：void Cheak_TimeDown(float dT)
 * 功    能：时间计时检测
 * 输    入: dT:执行周期
 * 参    数：float dT
*****************************************************************
*/
void Cheak_TimeDown(float dT)
{
    static float T,T1;
    if(Time.CountDown_Start)//启动倒计时
    {
        T += dT;
        if(T >= 1)//1S
        {
			if(Time.Rel_Time)
				Time.Rel_Time--;//控制时间--
			else
			{
				Time.CountDown_Start= 0;//倒计时结束
				Time.Rel_Time = Time.Set_Time;
				Beep_Flash = 5;//蜂鸣器响5下
			}
            T = 0;//周期清零
        }    
    }
    else
    {
		T = 0;//周期清零
    }
	
	if(Time.Count_Start)//启动正计时
    {
        T1 += dT;
        if(T1 >= 1)//1S
        {
			Time.Count_Time++;//正计时++
			if(Time.Count_Time >= 5999)
			{
				Time.Count_Start = 0;//关闭正计时
				Time.TimeDisplay_Flag = 0;//切换到倒计时
				Time.Count_Time = 0;//正计时清零
				Beep_Flash = 5;//蜂鸣器响5下
			}
            T1 = 0;//周期清零
        }    
    }
    else
    {
		T1 = 0;//周期清零
    }
}
