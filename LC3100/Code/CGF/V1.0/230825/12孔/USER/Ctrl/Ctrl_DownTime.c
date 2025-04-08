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
        if(sys.Run_Mode != 1)
        {
            T += dT;
            if(T >= 1)//1S
            {
                if(Speed.Ctrl)//如果实际时间显示和倒计时没有结束的标志还在
                {
                    if(Time.Rel)
                        Time.Rel--;//控制时间--
                    else
                    {
                        Speed.ADDMode = 2;//进入减速模式下
                        sys.Motor_Stop = 1;//进入减速模式
                        Beep_Flash = 3;//蜂鸣器响3下
                    }
                }
                T = 0;//周期清零
            }
        }
        else
        {
            if(Speed.ADDMode == 3)
            {
                T += dT;
                if(T >= 1)//1S
                {
                    if(Speed.Ctrl)//如果实际时间显示和倒计时没有结束的标志还在
                    {
                        if(Time.Rel)
                            Time.Rel--;//控制时间--
                        switch(sys.CGF_Step)
                        {
                            case 0:if(Time.Rel ==  720)//12分钟
                                    {
                                        Speed.ADDMode = 0;//进入降速不倒计时
                                        PMode.Option = 2;//进入第二段
                                        Speed.Set = Param.P_Param[PMode.Option][1];//读取记忆中第二段的转速
                                        Speed.Ctrl = Speed.Set;//把设定速度赋值给控制速度
                                        sys.CGF_Step = 1;//进入下一步
                                    }
                                break;
                            case 1:if(Time.Rel ==  420)//7分钟
                                    {
                                        Speed.ADDMode = 0;//进入降速不倒计时
                                        PMode.Option = 3;//进入第三段
                                        Speed.Set = Param.P_Param[PMode.Option][1];//读取记忆中第三段的转速
                                        Speed.Ctrl = Speed.Set;//把设定速度赋值给控制速度
                                        sys.CGF_Step = 2;//进入下一步
                                    }
                                break;
                            case 2:if(Time.Rel ==  180)//3分钟
                                    {
                                        Speed.ADDMode = 0;//进入降速不倒计时
                                        PMode.Option = 4;//进入第四段
                                        Speed.Set = Param.P_Param[PMode.Option][1];//读取记忆中第四段的转速
                                        Speed.Ctrl = Speed.Set;//把设定速度赋值给控制速度
                                        sys.CGF_Step = 3;//进入下一步
                                    }
                                break;
                            case 3:if(Time.Rel == 0)//0分钟
                                    {
                                        Speed.ADDMode = 2;//进入减速模式下
                                        Speed.Set = Param.P_Param[PMode.Option][1];//读取记忆中第四段的转速
                                        Speed.Ctrl = Speed.Set;//把设定速度赋值给控制速度
                                        sys.Motor_Stop = 1;//进入减速模式
                                        Beep_Flash = 3;//蜂鸣器响3下
                                    }
                                break;
                            default:
                                break;
                        }
                    }
                    T = 0;//周期清零
                }
            }
        }
    }
    else
    {
		T = 0;//周期清零
    }
}
