#include "Ctrl_Motor.h"

/**********结构体************/
_PID_Arg_ Speed_Arg;
_PID_Val_ Speed_Val;

/**
 * @brief 电机控制PID系数
 *
 */
void Motor_PID(void)
{
    Speed_Arg.Kp = 4 * 0.001f;
    Speed_Arg.Ki = 60 * 0.001f;
    Speed_Arg.Kd = 0 * 0.001f;
}

/**
 * @brief 电机控制
 *
 * @param dT 任务周期
 */
void Motor_Ctrl(float dT)
{
    if (sys.Run_Status == 1) // 启动
    {
        if (Speed.Ctrl) // 速度大于0和定时器没有结束
        {
            if(sys.Motor_Stop)//在停止减速模式下
			{			
				if (Speed_Val.Out)
                    Speed_Val.Out -= 1;
                if (Speed_Val.Out < 0)
                    Speed_Val.Out = 0;
                PWM = Speed_Val.Out; // PWM输出
			}
			else
			{	
                AltPID_Calculation(dT, Speed.Ctrl, Speed.Rel, &Speed_Arg, &Speed_Val, 150, 999); // 电机PID控制
                if (Speed_Val.Out < 0)
                    Speed_Val.Out = 0;
                PWM = Speed_Val.Out; // PID输出
			}
        }
        else
        {
            sys.Motor_Stop = 1;//检测电机
			if(sys.Motor_Stop)//在停止减速模式下
			{
                if (Speed_Val.Out)
                    Speed_Val.Out -= 1;
                if (Speed_Val.Out < 0)
                    Speed_Val.Out = 0;
                PWM = Speed_Val.Out; // PWM输出
            }
        }
    }
    else
    {
        Speed_Val.Out = 0;
        PWM = Speed_Val.Out; // PWM输出
    }
}

/*
*****************************************************************
 * 函数原型：void Check_MotorStop(float dT)
 * 功    能：检测电机是否停止
*****************************************************************
*/
void Check_MotorStop(float dT)
{
	static float T;
	if(sys.Motor_Stop)//在停止减速模式下
	{
		if(Speed.Rel < 180)
		{
			T += dT;//时间加dT
			if(T>1.0f)//速度为零时间持续1S时
			{
				SetOK_Flag = 1;//设置参数置一
				sys.Run_Status = 0;//关闭
				sys.Motor_Stop = 0;//电机已经停止
				T = 0;//时间清零
			}
		}
	}
	else
	{
		T = 0;//时间清零
	}
}
