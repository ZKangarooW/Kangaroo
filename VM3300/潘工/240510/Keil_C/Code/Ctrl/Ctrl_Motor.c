#include "Ctrl_Motor.h"

/**********结构体************/
_PID_Arg_ Speed_Arg = {0,0,0};
_PID_Val_ Speed_Val = {0,0,0,0,0,0,0,0,0,0};

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
    if (sys.Run_Status == 1) // 启动
    {
        if (Speed.Ctrl) // 速度大于0和定时器没有结束
        {
            AltPID_Calculation(dT, Speed.Ctrl, Speed.Rel, &Speed_Arg, &Speed_Val, 999, 999); // 电机PID控制
            if (Speed_Val.Out < 0)
                Speed_Val.Out = 0;
			if(Speed_Val.Out>1050)
				Speed_Val.Out = 1050;
			PWM_IndependentModeConfig(PWM20,Speed_Val.Out);//1050电压3.2V
        }
        else
        {
            PWM_IndependentModeConfig(PWM20,0);//1050电压3.2V
        }
    }
    else
    {
        if (Speed_Val.Out)
            Speed_Val.Out -= 1;
        if (Speed_Val.Out < 0)
            Speed_Val.Out = 0;
        PWM_IndependentModeConfig(PWM20,Speed_Val.Out);//1050电压3.2V
    }
}
