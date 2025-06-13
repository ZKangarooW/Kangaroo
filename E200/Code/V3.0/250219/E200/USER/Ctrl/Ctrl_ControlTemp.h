#ifndef __CTRL_CONTROTEMP_H__
#define __CTRL_CONTROTEMP_H__

#include "include.h"

/**********宏定义************/
#define UC_HEAT htim1.Instance->CCR2//单加热模块PWM
#define COLD htim3.Instance->CCR2//制冷模块PWM
#define HEAT htim3.Instance->CCR1//加热模块PWM

#define WIND_ON		HAL_GPIO_WritePin(WIND_GPIO_Port, WIND_Pin, GPIO_PIN_SET)
#define WIND_OFF	HAL_GPIO_WritePin(WIND_GPIO_Port, WIND_Pin, GPIO_PIN_RESET)

/**********全局变量**********/

/**********全局函数**********/
void Temp_Iint(void);//温度初始化
void Temp_Control(float dT);//温度加热控制
void PID_Init(void);
void Cool_Temp_Control(float dT);
#endif
