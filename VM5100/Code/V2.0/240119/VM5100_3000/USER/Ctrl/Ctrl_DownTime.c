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
	if(DownTime_Over==1)//倒计时结束
	{    
		DownTime_Over=0;//将时间标志清零
		Speed_ADDMode = 2;//进入减速模式下
		Beep_Flash = 5;//蜂鸣器响5下
	}
    if(sys.Run_Status && sys.Motor_Stop == 0)//启动系统
    {
        T += dT;
        if(T == 1000)//1S
        {
            if(Time_State && DownTime_Over == 0 && Rel_Speed)//如果实际时间显示和倒计时没有结束的标志还在
            {
				Ctrl_Time--;//控制时间--
                if(Ctrl_Time ==0)
                    DownTime_Over= 1;//time1倒计时结束
				
            }
            T = 0;//周期清零
        }    
    }
    else
    {
        DownTime_Over=0;//将时间标志清零    
    }
}
