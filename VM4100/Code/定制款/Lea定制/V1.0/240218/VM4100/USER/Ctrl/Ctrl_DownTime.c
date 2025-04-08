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
	if(Set_Time == 0)//设置时间为0的话，不进入计时
		return;
    if(sys.Run_Status)//启动系统
    {
        T += dT;//时间加dT
        if(T >= 1)//1S
        {
            if(DownTime_Over == 0 && Ctrl_Speed && sys.Motor_Stop == 0)//如果实际时间显示和倒计时没有结束的标志还在
            {
                if(Ctrl_Time)//控制监视大于0
				{	
					if(Time_State == 0)//时间显示
						Ctrl_Time--;//控制时间--
				}
                else
                {
					if(sys.Run_Step < 1)
					{
						sys.Run_Step ++;
						Set_Speed = Param.Speed[Speed_Mode][sys.Run_Step];
						Set_Time = Param.Time[Speed_Mode][sys.Run_Step];
						Ctrl_Time = Set_Time;//把设定时间赋值给控制时间
						Ctrl_Speed = Set_Speed;//把设定速度赋值给控制速度
						if(Speed_ADDMode != 0)//假如工位只有在启动并且设置了速度的情况下不等于0，不在未处理模式下
							Speed_ADDMode = 0;//进入未处理，判断加速还是减速 
						Beep_Flash = 1;//蜂鸣器响1下
					}
					else
					{
						sys.Run_Step = 0;
						Set_Speed = Param.Speed[Speed_Mode][sys.Run_Step];
						Set_Time = Param.Speed[Speed_Mode][sys.Run_Step];
						DownTime_Over= 1;//time1倒计时结束
						Speed_ADDMode = 4;//进入减速模式下
						Beep_Flash = 3;//蜂鸣器响3下
					}
                }
            }
            T = 0;//周期清零
        }    
    }
    else
    {
		T = 0;//周期清零
        DownTime_Over = 0;//将倒计时结束的标志位清零
    }
}
