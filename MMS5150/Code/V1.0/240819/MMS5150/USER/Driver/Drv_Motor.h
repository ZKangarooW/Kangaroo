#ifndef __DRV_MOTOR_H__
#define __DRV_MOTOR_H__

#include "include.h"

/**********宏定义************/
#define MO1_ON HAL_GPIO_WritePin(MO1_GPIO_Port, MO1_Pin, GPIO_PIN_SET)//打开电机电压
#define MO2_ON HAL_GPIO_WritePin(MO2_GPIO_Port, MO2_Pin, GPIO_PIN_SET)//打开电机电压
#define MO3_ON HAL_GPIO_WritePin(MO3_GPIO_Port, MO3_Pin, GPIO_PIN_SET)//打开电机电压
#define MO4_ON HAL_GPIO_WritePin(MO4_GPIO_Port, MO4_Pin, GPIO_PIN_SET)//打开电机电压
#define MO5_ON HAL_GPIO_WritePin(MO5_GPIO_Port, MO5_Pin, GPIO_PIN_SET)//打开电机电压
#define MO6_ON HAL_GPIO_WritePin(MO6_GPIO_Port, MO6_Pin, GPIO_PIN_SET)//打开电机电压
#define MO7_ON HAL_GPIO_WritePin(MO7_GPIO_Port, MO7_Pin, GPIO_PIN_SET)//打开电机电压
#define MO8_ON HAL_GPIO_WritePin(MO8_GPIO_Port, MO8_Pin, GPIO_PIN_SET)//打开电机电压
#define MO9_ON HAL_GPIO_WritePin(MO9_GPIO_Port, MO9_Pin, GPIO_PIN_SET)//打开电机电压
#define MO10_ON HAL_GPIO_WritePin(MO10_GPIO_Port, MO10_Pin, GPIO_PIN_SET)//打开电机电压
#define MO11_ON HAL_GPIO_WritePin(MO11_GPIO_Port, MO11_Pin, GPIO_PIN_SET)//打开电机电压
#define MO12_ON HAL_GPIO_WritePin(MO12_GPIO_Port, MO12_Pin, GPIO_PIN_SET)//打开电机电压
#define MO13_ON HAL_GPIO_WritePin(MO13_GPIO_Port, MO13_Pin, GPIO_PIN_SET)//打开电机电压
#define MO14_ON HAL_GPIO_WritePin(MO14_GPIO_Port, MO14_Pin, GPIO_PIN_SET)//打开电机电压
#define MO15_ON HAL_GPIO_WritePin(MO15_GPIO_Port, MO15_Pin, GPIO_PIN_SET)//打开电机电压

#define MO1_OFF HAL_GPIO_WritePin(MO1_GPIO_Port, MO1_Pin, GPIO_PIN_RESET)//关闭电机电压
#define MO2_OFF HAL_GPIO_WritePin(MO2_GPIO_Port, MO2_Pin, GPIO_PIN_RESET)//关闭电机电压
#define MO3_OFF HAL_GPIO_WritePin(MO3_GPIO_Port, MO3_Pin, GPIO_PIN_RESET)//关闭电机电压
#define MO4_OFF HAL_GPIO_WritePin(MO4_GPIO_Port, MO4_Pin, GPIO_PIN_RESET)//关闭电机电压
#define MO5_OFF HAL_GPIO_WritePin(MO5_GPIO_Port, MO5_Pin, GPIO_PIN_RESET)//关闭电机电压
#define MO6_OFF HAL_GPIO_WritePin(MO6_GPIO_Port, MO6_Pin, GPIO_PIN_RESET)//关闭电机电压
#define MO7_OFF HAL_GPIO_WritePin(MO7_GPIO_Port, MO7_Pin, GPIO_PIN_RESET)//关闭电机电压
#define MO8_OFF HAL_GPIO_WritePin(MO8_GPIO_Port, MO8_Pin, GPIO_PIN_RESET)//关闭电机电压
#define MO9_OFF HAL_GPIO_WritePin(MO9_GPIO_Port, MO9_Pin, GPIO_PIN_RESET)//关闭电机电压
#define MO10_OFF HAL_GPIO_WritePin(MO10_GPIO_Port, MO10_Pin, GPIO_PIN_RESET)//关闭电机电压
#define MO11_OFF HAL_GPIO_WritePin(MO11_GPIO_Port, MO11_Pin, GPIO_PIN_RESET)//关闭电机电压
#define MO12_OFF HAL_GPIO_WritePin(MO12_GPIO_Port, MO12_Pin, GPIO_PIN_RESET)//关闭电机电压
#define MO13_OFF HAL_GPIO_WritePin(MO13_GPIO_Port, MO13_Pin, GPIO_PIN_RESET)//关闭电机电压
#define MO14_OFF HAL_GPIO_WritePin(MO14_GPIO_Port, MO14_Pin, GPIO_PIN_RESET)//关闭电机电压
#define MO15_OFF HAL_GPIO_WritePin(MO15_GPIO_Port, MO15_Pin, GPIO_PIN_RESET)//关闭电机电压

/**********结构体************/
/**********全局变量声明*******/
extern uint16_t Motor_PWM[15];
extern uint16_t Time_Val;
/**********全局函数**********/

void Drv_Motor_Init(void);
void PWM_ValSet(uint8_t i);

#endif
