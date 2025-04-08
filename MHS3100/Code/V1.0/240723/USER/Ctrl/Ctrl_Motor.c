#include "Ctrl_Motor.h"

/**********结构体************/
_PID_Arg_ Speed_Arg;
_PID_Val_ Speed_Val[4];
int8_t Motor[4];//各个电机的pwm值

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
 * 函数原型：void Motor_Out(int16_t Motor_Pwm[MOTOR_NUM])
 * 功    能：电机驱动
 * 输    入：int16_t Motor_Pwm[MOTOR_NUM]
 * 参    数：Motor_Pwm[MOTOR_NUM]各个Motor的PWM占空比值
*****************************************************************
*/
void Motor_Out(int8_t Motor_Pwm[4])
{
    PWM0 = (uint8_t)Motor_Pwm[0];
    PWM1 = (uint8_t)Motor_Pwm[1];
    PWM2 = (uint8_t)Motor_Pwm[2];
    PWM3 = (uint8_t)Motor_Pwm[3];
}

/*
*****************************************************************
 * 函数原型：void Motor_Ctrl(float dT)
 * 功    能：电机控制
*****************************************************************
*/
void Motor_Ctrl(float dT)
{
    for(uint8_t i = 0;i<4;i++)
    {
        if(sys.Run_Status)//启动
        {
            HAL_GPIO_WritePin(MO_GPIO_Port, MO_Pin, GPIO_PIN_SET);//不使能电机
            if(Speed.Ctrl)
            {
                if(sys.Motor_Stop)
                {
                    if(Speed_Val[i].Out)
                        Speed_Val[i].Out -= 1;//降速太慢*2
                    if(Speed_Val[i].Out < 0)
                        Speed_Val[i].Out = 0;
                    Motor[i] = Speed_Val[i].Out;//pid输出
                }
                else
                {
                    AltPID_Calculation(dT,Speed.Ctrl,Speed.Rel[i],&Speed_Arg,&Speed_Val[i],200,200);//电机PID控制
                    if(Speed_Val[i].Out < 20)
                        Speed_Val[i].Out = 20;
                    Motor[i] = Speed_Val[i].Out;//pid输出
                }
            }
            else
            {
                if(Speed_Val[i].Out)
                    Speed_Val[i].Out -= 1;//降速太慢*2
                if(Speed_Val[i].Out < 20)
                    Speed_Val[i].Out = 0;
                Motor[i] = Speed_Val[i].Out;//pid输出
            }
        }
        else
        {
            Speed_Val[i].Integral = 20;
            Motor[i] = Speed_Val[i].Out;//pwm不输出
        }
    }
    Motor_Out(Motor);
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
        if(Speed.Display_Rel <= 300)
        {
            T += dT;
            if(T > 1.0f)
            {
                sys.Run_Status = 0;//关闭
                sys.Motor_Stop = 0;//电机已经停止
                HAL_GPIO_WritePin(MO_GPIO_Port, MO_Pin, GPIO_PIN_RESET);//不使能电机
                TimeSet_Flag=1;//设置变量
                T = 0;
            }
        }
    }
}
