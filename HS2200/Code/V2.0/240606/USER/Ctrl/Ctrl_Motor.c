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
            if(sys.Motor_Stop)
			{
                if(Speed_Val.Out)
                    Speed_Val.Out -= 1;
                if(Speed_Val.Out<0)
                    Speed_Val.Out = 0;
                PWM = Speed_Val.Out;//pwm不输出
            }
            else
            {
                AltPID_Calculation(dT,Speed.Ctrl,Speed.Rel,&Speed_Arg,&Speed_Val,350,400);//电机PID控制
                if(Speed_Val.Out<0)
                    Speed_Val.Out = 0;
                PWM = Speed_Val.Out;//pid输出
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
    else
    { 
        if(Speed_Val.Out)
		    Speed_Val.Out -= 1;
        if(Speed_Val.Out<0)
            Speed_Val.Out = 0;
        PWM = Speed_Val.Out;//pwm不输出
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
	if(sys.Motor_Stop)
	{
        if(Speed.Rel <= 100)
        {
            T += dT;
            if(T > 1.0f)
            {
                sys.Run_Status = 0;//关闭系统
                SetOK_Flag = 1;//设置标志置一
                sys.Motor_Stop = 0;
                T = 0;
            }
        }
	}
}
