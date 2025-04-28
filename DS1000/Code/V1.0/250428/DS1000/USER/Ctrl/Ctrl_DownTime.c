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
    if(sys.Run_Status==1)//启动系统
    {
        if(Time.Rel)
        {
            T += dT;
            if(T >= 1.0f)//1S
            {			
                if(Time.Rel)
                    Time.Rel--;//控制时间--
                if(Time.Rel == 0)
                {
                    sys.Run_Status = 0;//关闭系统
                    Time.Rel = Time.Set;//不加的话，倒计时结束，不会复原，后面就变成常动的了
                    Beep_Flash = 5;//响5下
                }
                T = 0;//周期清零
            }
        }
    }
}
