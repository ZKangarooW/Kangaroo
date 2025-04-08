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
    if (sys.Run_Status == 1)//启动
    {
        if (Speed.Ctrl)//速度大于0和定时器没有结束
        {
            if(Speed.Rel< 300)
            {
                Speed_Arg.Kp = 8 * 0.001f;
                Speed_Arg.Ki = 22 * 0.001f;
            }
            else
            {
                Speed_Arg.Kp = 80 * 0.001f;
                Speed_Arg.Ki = 60 * 0.001f;
            }
            AltPID_Calculation(dT, Speed.Ctrl, Speed.Rel, &Speed_Arg, &Speed_Val, 999, 999);//电机PID控制
            if (Speed_Val.Out < 0)
                Speed_Val.Out = 0;
            PWM = Speed_Val.Out;//PID输出
        }
        else
        {
            SetOK_Flag = 1;//设置参数置一
            sys.Run_Status = 0;//关闭
            PWM = 0;
        }
    }
	else if(Infrared[0].Someone || Infrared[1].Someone)
	{
        if(Infrared[0].Someone==3 || Infrared[1].Someone==3)
        {    
            if (Speed.Ctrl)//速度大于0和定时器没有结束
            {
                if(Speed.Rel< 300)
                {
                    Speed_Arg.Kp = 8 * 0.001f;
                    Speed_Arg.Ki = 22 * 0.001f;
                }
                else
                {
                    Speed_Arg.Kp = 80 * 0.001f;
                    Speed_Arg.Ki = 60 * 0.001f;
                }
                AltPID_Calculation(dT, Speed.Ctrl, Speed.Rel, &Speed_Arg, &Speed_Val, 200, 200);//电机PID控制
                if (Speed_Val.Out < 0)
                    Speed_Val.Out = 0;
                PWM = Speed_Val.Out;//PID输出
            }
            else
            {
                SetOK_Flag = 1;//设置参数置一
                sys.Run_Status = 0;//关闭
                PWM = 0;
            }
        }
        else
        {
            if (Speed.Ctrl)//速度大于0和定时器没有结束
            {
                Speed_Arg.Kp = 8 * 0.001f;
                Speed_Arg.Ki = 22 * 0.001f;
                AltPID_Calculation(dT, 200, Speed.Rel, &Speed_Arg, &Speed_Val, 200, 200);//电机PID控制
                if (Speed_Val.Out < 0)
                    Speed_Val.Out = 0;
                PWM = Speed_Val.Out;//PID输出
            }
            else
            {
                SetOK_Flag = 1;//设置参数置一
                sys.Run_Status = 0;//关闭
                PWM = 0;
            }
        }
	}
    else
    {
        Speed_Val.Out = 0;
        PWM = Speed_Val.Out;//PWM输出
		Speed_Val.Integral = 21;
        SetOK_Flag = 1;//设置参数置一
        sys.Run_Status = 0;//关闭
    }
}
