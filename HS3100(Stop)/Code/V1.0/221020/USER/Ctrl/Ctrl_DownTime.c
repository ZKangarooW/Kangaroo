#include "Ctrl_DownTime.h"

/*
*****************************************************************
 * 函数原型：void Cheak_TimeDown(float dT)
 * 功    能：时间倒计时检测
 * 输    入: dT:执行周期
 * 参    数：float dT
*****************************************************************
*/
void Cheak_TimeDown(float dT)
{
    static float T;
    if(sys.Run_Status)//启动系统
    {
		if(Time.Ctrl_Time > 0 && Speed.Speed_ADDMode != 1)
		{
			T += dT;
			if(T >= 1.0f)//1S
			{			
				if(Time.Ctrl_Time)
					Time.Ctrl_Time--;//控制时间--
				if(Time.Ctrl_Time == 0)
				{
					Speed.Speed_ADDMode = 1;//进入减速模式
					Speed.Ctrl_Speed = 0;//将控制速度设置为0
					Beep_Flash = 5;//响5下
				}
				T = 0;//周期清零
			}    
		}
    }
}
