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
    if(sys.Run_Status == 1 && sys.Display == 0)//启动
    {
        if(Speed.Ctrl)
		{
            if(Speed.Up_Speed == 1)//快速
            {
                Speed_Arg.Kp = 20 * 0.001f;
                Speed_Arg.Ki = 120 * 0.001f;
                Speed_Arg.Kd = 0 * 0.001f;
            }
            else if(Speed.Up_Speed == 2)//慢速
            {
                Speed_Arg.Kp = 20 * 0.001f;
                Speed_Arg.Ki = 30 * 0.001f;
                Speed_Arg.Kd = 0 * 0.001f;
            }
            else//正常
            {
                Speed_Arg.Kp = 20 * 0.001f;
                Speed_Arg.Ki = 60 * 0.001f;
                Speed_Arg.Kd = 0 * 0.001f;
            }
            
            if(sys.Motor_Stop)
			{
				if(Speed_Val.Out)
					Speed_Val.Out -= 1;//降速太慢*2
				if(Speed_Val.Out < 0)
					Speed_Val.Out = 0;
				PWM = Speed_Val.Out;//pid输出
			}
			else
			{
				AltPID_Calculation(dT,Speed.Ctrl,Speed.Rel,&Speed_Arg,&Speed_Val,400,400);//电机PID控制
				PWM = Speed_Val.Out;//pid输出
			}
        }
		else
		{
			if(Speed_Val.Out)
				Speed_Val.Out -= 1;//降速太慢*2
			if(Speed_Val.Out < 40)
				Speed_Val.Out = 0;
			PWM = Speed_Val.Out;//pid输出
		}
    }
    else
    {
        Speed_Val.Out = 0;
        PWM = Speed_Val.Out;//pwm不输出
    }
}

/*
*****************************************************************
 * 函数原型：void Check_MotorStop(float dT)
 * 功    能：检测电机是否停止，停止后开盖
*****************************************************************
*/
float CW_Time;
void Check_MotorStop(float dT)
{
	static float T;
	if(sys.Motor_Stop)
	{
		if(Speed.Cw)//进入改变转向
		{
			if(sys.Run_Status == 1)
			{
				if(Speed.Rel <= 100)
				{
					T += dT;
					CW_Time = 2.0f;
					if(T > CW_Time)
					{
						if(Speed.CwIcn) 
						{
                            HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_RESET);//逆时针
							Speed.ADDMode = 0;
							Speed.CwIcn = 0;
						}
						else 
						{
                            HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_SET);//顺时针
							Speed.ADDMode = 0;
							Speed.CwIcn = 1;
						}
						Beep_Time = 0.1f;
						sys.Motor_Stop = 0;//电机停止清零
						Speed.Cw = 0;//改变转向清零
						Speed_Val.Integral = 27;//电机起步的PWM
						T = 0;
					}
				}
			}
			else
			{
				if(Speed.CwIcn) 
				{
                    HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_RESET);//逆时针
					Speed.ADDMode = 0;
					Speed.CwIcn = 0;
				}
				else 
				{
                    HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_SET);//顺时针
					Speed.ADDMode = 0;
					Speed.CwIcn = 1;
				}
				sys.Motor_Stop = 0;//电机停止清零
				Speed.Cw = 0;//改变转向清零
			}
		}
		else
		{
			if(Speed.Rel <= 100)
			{
				T += dT;
				if(T > 1.0f)
				{
					sys.Run_Status = 2;//关闭
					sys.Motor_Stop = 0;//电机已经停止
					SpeedSet_Flag = TempSet_Flag = TimeSet_Flag=1;//进入设置
					T = 0;
				}
			}
		}
	}
}
