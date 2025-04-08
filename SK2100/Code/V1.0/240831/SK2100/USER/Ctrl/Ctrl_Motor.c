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
    Speed_Arg.Kp = 40 * 0.001f;
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
    if(sys.Run_Status)//启动
    {
        if(Speed.Ctrl)
		{
            if(sys.Motor_Stop)
			{
				if(Speed_Val.Out)
					Speed_Val.Out -= (dT*4);//降速太慢*2
				if(Speed_Val.Out < 0)
					Speed_Val.Out = 0;
				PWM = Speed_Val.Out;//pid输出
			}
			else
			{
				AltPID_Calculation(dT,Speed.Ctrl,Speed.Rel,&Speed_Arg,&Speed_Val,200,200);//电机PID控制
				PWM = Speed_Val.Out;//pid输出
			}
        }
    }
    else
    {
        Speed_Val.Out = 0;
        PWM = Speed_Val.Out;//pwm不输出
    }
}

/**
 * @brief 检测电机是否停止
 *
 * @param dT 任务周期
 */
void Check_MotorStop(float dT)
{
	static float T;
	if(sys.Motor_Stop)
	{
        if(Speed.Rel <= 40)
        {
            T += dT;
            if(T > 1.0f)
            {
                SetOK_Flag = 1;//设定值
                sys.Run_Status = 0;//关闭
                sys.Motor_Stop = 0;//电机已经停止
                T = 0;
            }
        }
	}
}
