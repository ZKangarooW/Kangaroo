#ifndef __DRV_KEY_H__
#define __DRV_KEY_H__

#include "include.h"

/**********宏定义************/
#define Key1 HAL_GPIO_ReadPin(KEY5_GPIO_Port,KEY5_Pin)//读KEY1的电平
#define Key2 HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)//读KEY2的电平
#define Key3 HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)//读KEY3的电平
#define Key4 HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)//读KEY4的电平
#define Key5 HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)//读KEY5的电平

/**********全局变量**********/
extern float Key_Status;//在操作按键时

/**********全局函数**********/
void Key_Scan(float dT);//按键扫描
void Check_Press(float dT);//检测按键状态-1s

#endif
