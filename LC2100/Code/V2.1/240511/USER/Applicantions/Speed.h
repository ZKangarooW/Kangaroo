#ifndef __SPEED_H__
#define __SPEED_H__

#include "include.h"

/**********宏定义************/
/**********结构体************/
/**********全局变量声明******/
/**********全局函数**********/
void Encoder_Init(void);//编码器初始化 
void TIM1_Poll(void);//TIM1轮训状态切换
void Check_Speed(float dT);//检测速度是否停止

#endif
