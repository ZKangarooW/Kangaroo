#ifndef __SPEED_H__
#define __SPEED_H__

#include "include.h"

/**********全局变量声明******/
extern uint8_t CAPTURE_Status;//捕获状态
extern uint16_t TIM1CH1_CAPTURE_STA;//捕获周期数

/**********全局函数**********/
void Encoder_Init(void);//编码器初始化 
void Check_Speed(float dT);//检测速度是否停止
void Check_Status(void);//检测状态
void Speed_TIM_Interrupt(TIM_HandleTypeDef *htim);//速度定时计数中断函数
void Speed_Capture_Interrupt(TIM_HandleTypeDef *htim);//速度捕获中断函数

#endif
