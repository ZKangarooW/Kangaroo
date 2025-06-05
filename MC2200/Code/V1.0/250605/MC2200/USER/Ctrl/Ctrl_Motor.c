#include "Ctrl_Motor.h"

/*
*****************************************************************
 * 函数原型：void Motor_Ctrl(float dT)
 * 功    能：电机控制
*****************************************************************
*/
void Motor_Ctrl(float dT)
{
    if(sys.Motor_Status == 1)
    {
        Motor_ON;//打开电机电源
    }
    else
    {
        Motor_OFF;//关闭电机电源
    }
}
