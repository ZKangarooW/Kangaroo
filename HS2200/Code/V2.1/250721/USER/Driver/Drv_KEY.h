#ifndef __DRV_KEY_H__
#define __DRV_KEY_H__

#include "include.h"
#if (Key_Type == 0)
/**********宏定义************/
#define KEY1 HAL_GPIO_ReadPin(K1_GPIO_Port,K1_Pin)
#define KEY2 HAL_GPIO_ReadPin(K2_GPIO_Port,K2_Pin)
#define KEY3 HAL_GPIO_ReadPin(K3_GPIO_Port,K3_Pin)
#define KEY4 HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)

//用于识别按键按下的状态识别 
#define PRESS RESET//低电平识别

#define KEY_DOWN PRESS/*键按下*/
#define KEY_UP !PRESS/*键弹起*/


/**********全局变量声明******/
extern float Key_Status;//按键按下标志

/**********局部变量声明******/
/**********全局函数**********/
void Key_Scan(float dT);//矩阵按键扫描
void Check_Press(float dT);//检测按键按下状态

#endif
#endif
