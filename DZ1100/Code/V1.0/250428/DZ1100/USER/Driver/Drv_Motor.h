#ifndef __DRV_MOTOR_H__
#define __DRV_MOTOR_H__

#include "include.h"

/**********宏定义************/
#define Motor_Vcc_ON  P12 = 1//打开电机电源
#define Motor_Vcc_OFF P12 = 0//关闭电机电源
#define Motor_Gnd_ON  P11 = 1//打开电机电源
#define Motor_Gnd_OFF P11 = 0//关闭电机电源
#define Motor_En_ON  P13 = 1//打开电机电源
#define Motor_En_OFF P13 = 0//关闭电机电源

/**********全局变量**********/

/**********全局函数**********/
void Drv_Motor_Init(void);//Motor驱动初始化
void Motor_BrakeCheck(float dT);

#endif
