#ifndef __DRV_LEDDISPLAY_H__
#define	__DRV_LEDDISPLAY_H__

#include "include.h"

/**********宏定义************/
#define DIG9_OFF HAL_GPIO_WritePin(DIG9_GPIO_Port, DIG9_Pin, GPIO_PIN_SET);
#define DIG9_ON HAL_GPIO_WritePin(DIG9_GPIO_Port, DIG9_Pin, GPIO_PIN_RESET);
#define DIG10_OFF HAL_GPIO_WritePin(DIG10_GPIO_Port, DIG10_Pin, GPIO_PIN_SET);
#define DIG10_ON HAL_GPIO_WritePin(DIG10_GPIO_Port, DIG10_Pin, GPIO_PIN_RESET);

/**********全局变量声明******/
extern uint16_t Twinkle_Time;//闪烁时间

/**********全局函数**********/
void Display_Show(void);//显示屏幕
void Check_ShowFlag(uint16_t dT);//闪烁检测
void Deal_Speed(void);//速度显示处理


#endif
