#ifndef __SPEED_H__
#define __SPEED_H__

#include "include.h"

/**********宏定义************/
/**********结构体************/
/**********全局变量声明******/
extern uint16_t TIM1CH3_CAPTURE_STA;//捕获周期数
extern uint32_t TIM1CH3_CAPTURE_VAL;//捕获计数值
extern uint32_t P_Status;//捕获周期计数状态  1开启 0关闭
/**********局部变量声明******/
/**********全局函数**********/
void Encoder_Init(void);//编码器初始化 
void TIM1_Poll(void);//TIM3轮训状态切换
void Check_Speed(float dT);//检测速度是否停止

#endif
