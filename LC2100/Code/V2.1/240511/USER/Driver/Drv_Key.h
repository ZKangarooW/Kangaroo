#ifndef __DRV_KEY_H__
#define	__DRV_KEY_H__

#include "include.h"

/**********宏定义************/
#define KEY1 HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)
#define KEY2 HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)
#define KEY3 HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)
#define KEY4 HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)
#define KEY5 HAL_GPIO_ReadPin(KEY5_GPIO_Port,KEY5_Pin)

/**********结构体************/
/**********全局变量声明******/
extern uint8_t Key_Status;//按键按下标志

/**********全局函数**********/
void Key_Scan(float dT);//矩阵按键扫描
void Check_Press(float dT);//检测按键按下状态

#endif
