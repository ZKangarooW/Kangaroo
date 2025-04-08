#include "Ctrl_DownTime.h"

/*
*****************************************************************
 * 函数原型： void Cheak_TimeDown(uint16_t dT)
 * 功    能： 时间倒计时检测
 * 输    入:  dT:执行周期
 * 参    数： uint16_t dT
*****************************************************************
*/
void Cheak_TimeDown(uint16_t dT)
{
    static uint16_t T;
    if(DownTime_Over==1)//工位倒计时结束
    {    
        DownTime_Over = 0;//将倒计时结束的标志位清零
        Ctrl_Time = Set_Time;//将设置时间重新赋值给控制时间  
        Beep_Flash = 5;//蜂鸣器响5下
		sys.Motor_Stop  = 1;
		Speed_ADDMode = 2;//进入减速模式下
    }
    if(sys.Run_Status && sys.Motor_Stop == 0)//启动系统和不在停止状态下
    {
        T += dT;
        if(T == 1000)//1S
        {
            if(Time_State == 0 && DownTime_Over == 0 && Ctrl_Speed)//如果实际时间显示和倒计时没有结束的标志还在
            { 
                if(Ctrl_Time)
                    Ctrl_Time--;//控制时间--
                else
                {
                    DownTime_Over= 1;//time1倒计时结束
                }
            }
            T = 0;//周期清零
        }    
    }
    else
    {
        DownTime_Over = 0;//将倒计时结束的标志位清零
    }
}
