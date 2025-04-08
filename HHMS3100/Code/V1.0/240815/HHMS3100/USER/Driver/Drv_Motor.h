#ifndef __DRV_MOTOR_H__
#define __DRV_MOTOR_H__

#include "include.h"

/**********宏定义************/
#define PWM2 htim5.Instance->CCR1 // motor PWM输出 （0~200）
#define PWM0 htim5.Instance->CCR2 // motor PWM输出 （0~200）
#define PWM3 htim5.Instance->CCR3 // motor PWM输出 （0~200）
#define PWM1 htim5.Instance->CCR4 // motor PWM输出 （0~200）
#define MO2_ON HAL_GPIO_WritePin(MO1_GPIO_Port, MO1_Pin, GPIO_PIN_SET)//打开电机电压
#define MO0_ON HAL_GPIO_WritePin(MO2_GPIO_Port, MO2_Pin, GPIO_PIN_SET)//打开电机电压
#define MO3_ON HAL_GPIO_WritePin(MO3_GPIO_Port, MO3_Pin, GPIO_PIN_SET)//打开电机电压
#define MO1_ON HAL_GPIO_WritePin(MO4_GPIO_Port, MO4_Pin, GPIO_PIN_SET)//打开电机电压
#define MO2_OFF HAL_GPIO_WritePin(MO1_GPIO_Port, MO1_Pin, GPIO_PIN_RESET)//打开电机电压
#define MO0_OFF HAL_GPIO_WritePin(MO2_GPIO_Port, MO2_Pin, GPIO_PIN_RESET)//打开电机电压
#define MO3_OFF HAL_GPIO_WritePin(MO3_GPIO_Port, MO3_Pin, GPIO_PIN_RESET)//打开电机电压
#define MO1_OFF HAL_GPIO_WritePin(MO4_GPIO_Port, MO4_Pin, GPIO_PIN_RESET)//打开电机电压
/**********结构体************/
/**********全局变量声明*******/
/**********全局函数**********/

void Drv_Motor_Init(void);
void Motor_Switch(uint8_t i,uint8_t val);

#endif
