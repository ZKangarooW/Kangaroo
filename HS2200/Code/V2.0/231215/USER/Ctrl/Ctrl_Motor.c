#include "Ctrl_Motor.h"

/**********结构体************/
_PID_Arg_ Speed_Arg;
_PID_Val_ Speed_Val;

/*
*****************************************************************
 * 函数原型：void Motor_PID(void)
 * 功    能：电机控制PID系数
*****************************************************************
*/
void Motor_PID(void)
{
    Speed_Arg.Kp = 40 * 0.001f;
    Speed_Arg.Ki = 60 * 0.001f;
    Speed_Arg.Kd = 0 * 0.001f;
}

/*
*****************************************************************
 * 函数原型：void Motor_Ctrl(float dT)
 * 功    能：电机控制
*****************************************************************
*/
void Motor_Ctrl(float dT)
{
    if(sys.Run_Status)//启动
    {
        /**********Speed_L1**********/
        if(Speed.Ctrl)//速度大于0和定时器没有结束
        {
			AltPID_Calculation(dT,Speed.Ctrl,Speed.Rel,&Speed_Arg,&Speed_Val,350,400);//电机PID控制
            if(Speed_Val.Out<0)
                Speed_Val.Out = 0;
			PWM = Speed_Val.Out;//pid输出
        }
        else
        {
			if(Speed_Val.Out)
				Speed_Val.Out -= 1;
			if(Speed_Val.Out<0)
				Speed_Val.Out = 0;
			PWM = Speed_Val.Out;//pwm不输出
        }
    }
    else
    { 
        if(Speed_Val.Out)
		    Speed_Val.Out -= 1;
        if(Speed_Val.Out<0)
            Speed_Val.Out = 0;
        PWM = Speed_Val.Out;//pwm不输出
    }
}
