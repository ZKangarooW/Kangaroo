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
    #if(Integration_TYPE == 0)//设置成四联时
		if(Param.type == 0 || Param.type == 2)//四联
		{
			if(DownTime_Over.L1==1&&DownTime_Over.L2==1&&DownTime_Over.L5==1&&DownTime_Over.L6==1)//四联上的工位倒计时结束
			{    
				SetALL_int8(0,&DownTime_Over);//将倒计时结束的标志位清零
				SetALL_TimeOver(&Ctrl_Time,&Set_Time);//将设置时间重新赋值给控制时间  
				Beep_Flash = 5;//蜂鸣器响5下
				Run_Status = 0;//关闭
			}
		}
		else if(Param.type == 1 || Param.type == 3)//六联
		{
			if(DownTime_Over.L1==1&&DownTime_Over.L2==1&&DownTime_Over.L3==1&&DownTime_Over.L4==1&&DownTime_Over.L5==1&&DownTime_Over.L6==1)//六联上的工位倒计时结束
			{    
				SetALL_int8(0,&DownTime_Over);//将倒计时结束的标志位清零
				SetALL_TimeOver(&Ctrl_Time,&Set_Time);//将设置时间重新赋值给控制时间
				Beep_Flash = 5;//蜂鸣器响5下
				Run_Status = 0;//关闭
			}
		}
    #elif(Integration_TYPE == 1)//设置成九联时
        if(DownTime_Over.L1==1&&DownTime_Over.L2==1&&DownTime_Over.L3==1&&DownTime_Over.L4==1&&DownTime_Over.L5==1&&DownTime_Over.L6==1&&DownTime_Over.L7==1&&DownTime_Over.L8==1&&DownTime_Over.L9==1)//八联上的工位倒计时结束
        {    
            SetALL_int8(0,&DownTime_Over);//将倒计时结束的标志位清零
            SetALL_TimeOver(&Ctrl_Time,&Set_Time);//将设置时间重新赋值给控制时间
            Beep_Flash = 5;//蜂鸣器响5下
            Run_Status = 0;//关闭
        }
    #endif
    if(Run_Status)//启动系统
    {
        T += dT;
        if(T == 1000)//1S
        {
            if(RelTime_State.L1 && DownTime_Over.L1 == 0 && Rel_Speed.L1)//如果实际时间显示和倒计时没有结束的标志还在
            {
                if(Ctrl_Time.L1)
                    Ctrl_Time.L1--;//控制时间--
                else
                {
					Speed_ADDMode.L1 = 4;//将速度清零
                    DownTime_Over.L1= 1;//time1倒计时结束
                }
            }
            if(RelTime_State.L2 && DownTime_Over.L2 == 0 && Rel_Speed.L2)//如果实际时间显示和倒计时没有结束的标志还在
            {
                if(Ctrl_Time.L2)
                    Ctrl_Time.L2--;//控制时间--
                else
                {
					Speed_ADDMode.L2 = 4;//将速度清零
                    DownTime_Over.L2= 1;//time1倒计时结束
                }
            }
            if(RelTime_State.L3 && DownTime_Over.L3 == 0 && Rel_Speed.L3)//如果实际时间显示和倒计时没有结束的标志还在
            {
                if(Ctrl_Time.L3)
                    Ctrl_Time.L3--;//控制时间--
                else
                {
					Speed_ADDMode.L3 = 4;//将速度清零
                    DownTime_Over.L3= 1;//time1倒计时结束
                }
            }
            if(RelTime_State.L4 && DownTime_Over.L4 == 0 && Rel_Speed.L4)//如果实际时间显示和倒计时没有结束的标志还在
            {
                if(Ctrl_Time.L4)
                    Ctrl_Time.L4--;//控制时间--
                else
                {
					Speed_ADDMode.L4 = 4;//将速度清零
                    DownTime_Over.L4= 1;//time1倒计时结束
                }
            }
            if(RelTime_State.L5 && DownTime_Over.L5 == 0 && Rel_Speed.L5)//如果实际时间显示和倒计时没有结束的标志还在
            {
                if(Ctrl_Time.L5)
                    Ctrl_Time.L5--;//控制时间--
                else
                {
					Speed_ADDMode.L5 = 4;//将速度清零
                    DownTime_Over.L5= 1;//time1倒计时结束
                }
            }
            if(RelTime_State.L6 && DownTime_Over.L6 == 0 && Rel_Speed.L6)//如果实际时间显示和倒计时没有结束的标志还在
            {
                if(Ctrl_Time.L6)
                    Ctrl_Time.L6--;//控制时间--
                else
                {
					Speed_ADDMode.L6 = 4;//将速度清零
                    DownTime_Over.L6= 1;//time1倒计时结束
                }
            }
            if(RelTime_State.L7 && DownTime_Over.L7 == 0 && Rel_Speed.L7)//如果实际时间显示和倒计时没有结束的标志还在
            {
                if(Ctrl_Time.L7)
                    Ctrl_Time.L7--;//控制时间--
                else
                {
					Speed_ADDMode.L7 = 4;//将速度清零
                    DownTime_Over.L7= 1;//time1倒计时结束
                }
            }
            if(RelTime_State.L8 && DownTime_Over.L8 == 0 && Rel_Speed.L8)//如果实际时间显示和倒计时没有结束的标志还在
            {
                if(Ctrl_Time.L8)
                    Ctrl_Time.L8--;//控制时间--
                else
                {
					Speed_ADDMode.L8 = 4;//将速度清零
                    DownTime_Over.L8= 1;//time1倒计时结束
                }
            }
			if(RelTime_State.L9 && DownTime_Over.L9 == 0 && Rel_Speed.L9)//如果实际时间显示和倒计时没有结束的标志还在
            {
                if(Ctrl_Time.L9)
                    Ctrl_Time.L9--;//控制时间--
                else
                {
					Speed_ADDMode.L9 = 4;//将速度清零
                    DownTime_Over.L9= 1;//time1倒计时结束
                }
            }
            T = 0;//周期清零
        }    
    }
    else
    {
        SetALL_int8(0,&DownTime_Over);//将时间标志清零
        SetALL_TimeOver(&Ctrl_Time,&Set_Time);//将设定时间赋值给控制时间用来再次倒计时
    }
}
