#include "Ctrl_DownTime.h"

/*
*****************************************************************
 * 函数原型：void Cheak_TimeDown(float dT)
 * 功    能：时间倒计时检测
 * 输    入：dT：执行周期
 * 参    数：float dT
*****************************************************************
*/
void Cheak_TimeDown(float dT)
{
    static float T;
    if(sys.Run_Status && Speed.ADDMode == 3)//启动系统
    {
        if(Time.Ctrl)
        {
            T += dT;
            if(T >= 1)//1S
            {
                if(Time.Ctrl)
                    Time.Ctrl--;//控制时间--
                if(Time.Ctrl == 0)
                {
                    Speed.ADDMode = 2;//进入减速模式下
                    sys.Motor_Stop = 1;//电机降速停止
                    Beep_Flash = 5;//蜂鸣器响5下
                }
                T = 0;//周期清零
            } 
        }            
    }
}
