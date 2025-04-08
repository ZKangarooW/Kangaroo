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
    if(sys.Run_Status == 1 && Temp.ADDMode == 4)//启动系统
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
                    sys.Run_Status = 2;//系统关闭
					SetOK_Flag = 1;//速度设置，时间设置
					Temp.Last_Mode = Temp.ADDMode;//记录关闭时的显示模式
					Temp.ADD_Wait_Count = 0;//清楚缓慢计时数
                    Temp.ADDMode = 0;//加热显示模式清零
					Beep_Flash = 5;//响5下
                }
				T = 0;//周期清零
            }
        }
    }
}
