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
    if(sys.Run_Status && sys.Motor_Stop == 0)//启动系统
    {
        if(Time.Rel > 0)
        {
            T += dT;
            if(T >= 1.0f)//1S
            {			
                if(Time.Rel)
                    Time.Rel--;//控制时间--
                if(Time.Rel == 0)
                {
                    Speed.ADDMode = 2;//进入降速显示
					Speed.Cw = 0;//转向清零
					sys.Motor_Stop = 1;//检测电机
					SpeedSet_Flag=TimeSet_Flag=1;//进入设置
					Speed_Twinkle_Time = Time_Twinkle_Time = 0;//关闭闪烁
                    Beep_Flash = 5;//响5下
                }
                 T = 0;//周期清零
            }
        }
    }
}
