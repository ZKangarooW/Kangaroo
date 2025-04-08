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
    if(sys.Run_Status)//启动系统
    {
        if(CGF.Mode == 0)
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
        else if(CGF.Mode == 1)
        {
            if(Speed.ADDMode == 3)
            {
                T += dT;
                if(T >= 1)//1S
                {
                    if(Param.C_Param[1][0])//如果实际时间显示和倒计时没有结束的标志还在
                    {
                        if(Param.C_Param[1][0])
                            Param.C_Param[1][0]--;//控制时间--
                        if(Param.C_Param[1][0] ==  720)//12分钟
                        {
                            Speed.ADDMode = 0;//进入降速不倒计时
                            CGF.Option = 2;//进入第二段
                        }
                        else if(Param.C_Param[1][0] ==  420)//7分钟
                        {
                            Speed.ADDMode = 0;//进入降速不倒计时
                            CGF.Option = 3;//进入第三段
                        }
                        else if(Param.C_Param[1][0] ==  180)//3分钟
                        {
                            Speed.ADDMode = 0;//进入降速不倒计时
                            CGF.Option = 4;//进入第四段
                        }
                        else if(Param.C_Param[1][0] ==  0)//0分钟
                        {
                            Speed.ADDMode = 2;//进入降速不倒计时
                            sys.Motor_Stop = 1;//电机降速停止
                            Beep_Flash = 3;//蜂鸣器响5下
                        }
                    }
                    T = 0;//周期清零
                }
            }
        }
        else
        {
            if(Speed.ADDMode == 3)
            {
                T += dT;
                if(T >= 1)//1S
                {
                    if(Param.C_Param[CGF.Option][0])//如果实际时间显示和倒计时没有结束的标志还在
                    {
                        if(Param.C_Param[CGF.Option][0])
                            Param.C_Param[CGF.Option][0]--;//控制时间--
                        else 
                        {
                            Speed.ADDMode = 2;//进入降速不倒计时
                            sys.Motor_Stop = 1;//电机降速停止
                            Beep_Flash = 3;//蜂鸣器响5下
                        }
                    }
                    T = 0;//周期清零
                }
            }
        }
    }
}
