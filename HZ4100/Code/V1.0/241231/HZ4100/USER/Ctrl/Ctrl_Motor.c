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
    static float T;
    static uint8_t step;
    if (sys.Run_Status == 1) // 启动
    {
        if (Speed.Ctrl) // 速度大于0和定时器没有结束
        {
            if(step == 0)
            {
                PWM = 20;
                T += dT;
                if(T> 2.0f)
                {
                    step = 1;
                    T = 0;
                }
            }
            else
            {
                AltPID_Calculation(dT, Speed.Ctrl, Speed.Rel, &Speed_Arg, &Speed_Val, 400, 400); // 电机PID控制
                if (Speed_Val.Out < 20)
                    Speed_Val.Out = 20;
                PWM = Speed_Val.Out; // PID输出
            }
        }
        else
        {
            PWM = 0; // PID输出
        }
    }
    else
    {
        step = 0;
        if (Speed_Val.Out)
            Speed_Val.Out -= 1;
        if (Speed_Val.Out < 0)
            Speed_Val.Out = 0;
        PWM = Speed_Val.Out; // PWM输出
    }
}
