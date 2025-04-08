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
    Speed_Arg.Kp = 20 * 0.001f;
    Speed_Arg.Ki = 44 * 0.001f;
    Speed_Arg.Kd = 0 * 0.001f;
}

/*
*****************************************************************
 * 函数原型：void Motor_Ctrl(float dT)
 * 功    能：电机控制
*****************************************************************
*/
int16_t Ctrl_Val;
void Motor_Ctrl(float dT)
{ 
    if(sys.Run_Status)//启动
    {
        if(Speed.Ctrl)
		{
            HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_SET);//高电平不刹车，低电平刹车
            if(sys.Motor_Stop)
			{
				HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_RESET);//高电平不刹车，低电平刹车
			}
			else
			{
                if(Speed.Ctrl > 2000)
                    Ctrl_Val = 2000 + ((Speed.Ctrl - 2000)/2);
                else
                    Ctrl_Val = Speed.Ctrl;
				AltPID_Calculation(dT,Ctrl_Val,Speed.Rel,&Speed_Arg,&Speed_Val,400,400);//电机PID控制
				PWM = Speed_Val.Out;//pid输出
			}
        }
    }
    else
    {
        HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_RESET);//高电平不刹车，低电平刹车
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
void Check_MotorStop(float dT)
{
//	static float T;
	if(sys.Motor_Stop)
	{
//        if(Speed.Rel <= 300)
//        {
//            T += dT;
//            if(T > 1.0f)
//            {
                TimeSet_Flag=1;//设置变量
                sys.Run_Status = 0;//关闭
                sys.Motor_Stop = 0;//电机已经停止
//                T = 0;
//            }
//        }
	}
}
