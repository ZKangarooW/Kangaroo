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
    static int16_t Speed_Num;//用来区分80转以下的转速
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
                #if(Type == 0)//10L&15L
                if(Speed.Ctrl < 80)
                    Speed_Num = 80;
                else
                    Speed_Num = Speed.Ctrl;
                #elif(Type >= 1)//30L&50L
                    Speed_Num = Speed.Ctrl;
                #endif
				AltPID_Calculation(dT,Speed_Num,Speed.Rel,&Speed_Arg,&Speed_Val,200,200);//电机PID控制
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
			if(sys.Run_Status)
			{
				if(Speed.Rel <= 100)
				{
					T += dT;
					CW_Time = 2.0f;
					if(T > CW_Time)
					{
						if(Speed.CwIcn) 
						{
                            #if(Type == 0)//10L15L
                            HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_RESET);//逆时针
                            #elif(Type >= 1)//30L50L
                            HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_SET);//逆时针
                            #endif
							Speed.ADDMode = 0;
							Speed.CwIcn = 0;
						}
						else 
						{
                            #if(Type == 0)//10L15L
                            HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_SET);//顺时针
                            #elif(Type >= 1)//30L50L
                            HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_RESET);//顺时针
                            #endif
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
					#if(Type == 0)//10L15L
                    HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_RESET);//逆时针
                    #elif(Type >= 1)//30L50L
                    HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_SET);//逆时针
                    #endif
					Speed.ADDMode = 0;
					Speed.CwIcn = 0;
				}
				else 
				{
					#if(Type == 0)//10L15L
                    HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_SET);//顺时针
                    #elif(Type >= 1)//30L50L
                    HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_RESET);//顺时针
                    #endif
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
					TimeSet_Flag=1;//设置变量
					sys.Run_Status = 0;//关闭
					sys.Motor_Stop = 0;//电机已经停止
					T = 0;
				}
			}
		}
	}
}
