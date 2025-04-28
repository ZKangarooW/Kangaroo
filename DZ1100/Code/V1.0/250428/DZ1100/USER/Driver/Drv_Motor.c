#include "Drv_Motor.h"

/*
*****************************************************************
 * 函数原型：void Drv_Motor_Init(void)
 * 功    能：Motor驱动初始化
*****************************************************************
*/
void Drv_Motor_Init(void)
{
    GPIO_SET_MUX_MODE(P11CFG, GPIO_MUX_GPIO);
    GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_1);
    GPIO_SET_MUX_MODE(P12CFG, GPIO_MUX_GPIO);
    GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_2);
    GPIO_SET_MUX_MODE(P13CFG, GPIO_MUX_GPIO);
    GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_3);
    
    Motor_Vcc_ON;//关闭电机
    Motor_Gnd_OFF;//关闭电机
    Motor_En_OFF;//关闭电机
}


void Motor_BrakeCheck(float dT)
{
    static float T;
    float T1;
    if(sys.Motor_Brake)
    {
        T += dT;
        if(sys.sys_time< 5.0f)
        {
            T1 = 1.0f;
        }
        else if(sys.sys_time< 9.0f)
        {
            T1 = 1.5f;
        }
        else
        {
            T1 = 2.1f;
        }
        
        if(T <=T1)
        {
            Motor_Vcc_OFF;//关闭电机
            Motor_Gnd_ON;//关闭电机
            Motor_En_ON;//关闭电机
        }
        else
        {
            sys.Run_Status = 0;//启动系统
            sys.Motor_Brake = 0;
            Motor_Vcc_ON;//关闭电机
            Motor_Gnd_ON;//关闭电机
            Motor_En_ON;//关闭电机
            T = 0;
        }
    }
}
