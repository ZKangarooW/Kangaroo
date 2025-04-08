#include "Ctrl_DownTime.h"

/*
*****************************************************************
 * 函数原型： void Cheak_TimeDown(float dT)
 * 功    能： 时间倒计时检测
 * 输    入:  dT:执行周期
 * 参    数： float dT
*****************************************************************
*/
void Cheak_TimeDown(float dT)
{
    static float T;
    if(sys.Run_Status && sys.Motor_Stop == 0)//启动系统
    {
        T += dT;
        if(T >= 1)//1S
        {
            if(Ctrl_Speed)//如果实际时间显示和倒计时没有结束的标志还在
            {
                if(Ctrl_Time)
                    Ctrl_Time--;//控制时间--
                else
                {
                    sys.Motor_Stop= 1;//time1倒计时结束
					Speed_ADDMode = 2;//进入减速模式下
					Beep_Flash = 3;//蜂鸣器响3下
                }
            }
            T = 0;//周期清零
        }    
    }
    else
    {
		T = 0;//周期清零
    }
}
