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
    Speed_Arg.Kp = 16 * 0.001f;
    Speed_Arg.Ki = 24 * 0.001f;
    Speed_Arg.Kd = 0 * 0.001f;
}

/*
*****************************************************************
 * 函数原型： void Motor_Ctrl(float dT)
 * 功    能： 电机控制
*****************************************************************
*/
void Motor_Ctrl(float dT)
{   
    if(sys.Run_Status == 1)//启动
    {
		if((HAL_GPIO_ReadPin(UC_IN1_GPIO_Port,UC_IN1_Pin)== 1)&&(HAL_GPIO_ReadPin(UC_IN2_GPIO_Port,UC_IN2_Pin)== 1))//电磁锁1和2闭合时
		{
			if(Speed.Ctrl)//速度大于0
			{
				if(sys.Motor_Stop)
				{
					HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_SET);//高电平不刹车，低电平刹车
					if(Speed_Val.Out)
                        Speed_Val.Out -= (dT*10);//降速太慢*2
                    if(Speed_Val.Out < 0)
                        Speed_Val.Out = 0;
                    PWM = Speed_Val.Out;//pid输出
				}
				else
				{
					HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_SET);//高电平不刹车，低电平刹车
					if(Speed.Unit)	
						AltPID_Calculation(dT,1000 * My_Sqrt(Speed.Ctrl/(11.18*Mode_R)),Speed.Rel,&Speed_Arg,&Speed_Val,400,400);//电机PID控制离心率
					else
						AltPID_Calculation(dT,Speed.Ctrl,Speed.Rel,&Speed_Arg,&Speed_Val,400,400);//电机PID控制
					PWM = Speed_Val.Out;//pid输出
				}
			}
		}
		else
		{
			sys.Run_Status = 0;//不启动
            HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_RESET);//高电平不刹车，低电平刹车
			SetOK_Flag = 1;//设置变量
		}
    }
    else
    {
        PWM = 0;//pwm不输出
		sys.Motor_Stop = 0;//电机已经停止
		HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_RESET);//高电平不刹车，低电平刹车
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
	static float T;
	if(sys.Motor_Stop)
	{
		if(Speed.Rel <= 150)
		{
			T += dT;
			if(T> 1.0f)
			{
				PWM = 0;
				HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_RESET);//高电平不刹车，低电平刹车
				Lock1_Status = 1;//电磁锁1打开
				Lock2_Status = 1;//电磁锁2打开
				SetOK_Flag = 1;//设置变量
				sys.Run_Status = 0;//关闭
				sys.Motor_Stop = 0;//电机已经停止
                if(sys.Run_Mode == 1)//在CGF模式下
                {
                    PMode.Option = 1;//记忆程序为1
                    sys.CGF_Step = 0;//步骤为0
                    Speed.Set = Param.P_Param[PMode.Option][1];//读取记忆中第四段的转速
                    Speed.Ctrl = Speed.Set;//把设定速度赋值给控制速度
                }
				T = 0;
			}
		}
		else
		{
			T = 0;
		}
	}
	else
	{
		T = 0;
	}
}
