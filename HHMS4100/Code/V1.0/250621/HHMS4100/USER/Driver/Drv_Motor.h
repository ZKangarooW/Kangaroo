#ifndef __DRV_MOTOR_H__
#define __DRV_MOTOR_H__

#include "include.h"

/**********宏定义************/
#define MO1_ON HAL_GPIO_WritePin(PWM1_GPIO_Port, PWM1_Pin, GPIO_PIN_SET)//打开电机电压
#define MO2_ON HAL_GPIO_WritePin(PWM2_GPIO_Port, PWM2_Pin, GPIO_PIN_SET)//打开电机电压
#define MO3_ON HAL_GPIO_WritePin(PWM3_GPIO_Port, PWM3_Pin, GPIO_PIN_SET)//打开电机电压
#define MO4_ON HAL_GPIO_WritePin(PWM4_GPIO_Port, PWM4_Pin, GPIO_PIN_SET)//打开电机电压
#define MO5_ON HAL_GPIO_WritePin(PWM5_GPIO_Port, PWM5_Pin, GPIO_PIN_SET)//打开电机电压
#define MO6_ON HAL_GPIO_WritePin(PWM6_GPIO_Port, PWM6_Pin, GPIO_PIN_SET)//打开电机电压

#define MO1_OFF HAL_GPIO_WritePin(PWM1_GPIO_Port, PWM1_Pin, GPIO_PIN_RESET)//关闭电机电压
#define MO2_OFF HAL_GPIO_WritePin(PWM2_GPIO_Port, PWM2_Pin, GPIO_PIN_RESET)//关闭电机电压
#define MO3_OFF HAL_GPIO_WritePin(PWM3_GPIO_Port, PWM3_Pin, GPIO_PIN_RESET)//关闭电机电压
#define MO4_OFF HAL_GPIO_WritePin(PWM4_GPIO_Port, PWM4_Pin, GPIO_PIN_RESET)//关闭电机电压
#define MO5_OFF HAL_GPIO_WritePin(PWM5_GPIO_Port, PWM5_Pin, GPIO_PIN_RESET)//关闭电机电压
#define MO6_OFF HAL_GPIO_WritePin(PWM6_GPIO_Port, PWM6_Pin, GPIO_PIN_RESET)//关闭电机电压

/**********结构体************/
/**********全局变量声明*******/
extern uint16_t Motor_PWM[Motor_Num];
extern uint16_t Time_Val;
/**********全局函数**********/

void Drv_Motor_Init(void);
void Motor_AllOFF(void);
void Motor_AllON(void);


#endif
