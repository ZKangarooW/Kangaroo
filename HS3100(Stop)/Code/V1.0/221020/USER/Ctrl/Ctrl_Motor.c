#include "Ctrl_Motor.h"

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
		if(Speed.Set_Speed > 0)
		{
			MO_ON();//电机启动
			PID_Speed(Speed.Ctrl_Speed,Speed.Rel_Speed,&Speed_Arg,&Speed_Val);//电机PID控制
			PWM = Speed_Val.Out;//pid输出
		}
		else
		{
			MO_OFF();//电机关闭
			Speed_Val.SumError = 0;//清除积分合
			PWM = 0;//pwm不输出
		}
    }
    else
    {
		MO_OFF();//电机关闭
		Speed_Val.SumError = 0;//清除积分合
        PWM = 0;//pwm不输出
    }
}
