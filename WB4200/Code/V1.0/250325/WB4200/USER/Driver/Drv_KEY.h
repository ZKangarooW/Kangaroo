#ifndef __DRV_KEY_H__
#define __DRV_KEY_H__

#include "include.h"

/**********宏定义************/
#define KEY1 HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)
#define KEY2 HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)
#define KEY3 HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)
#define KEY4 HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)
#define KEY5 HAL_GPIO_ReadPin(KEY5_GPIO_Port,KEY5_Pin)
#define KEY6 HAL_GPIO_ReadPin(KEY6_GPIO_Port,KEY6_Pin)

//用于识别按键按下的状态识别 
#define PRESS RESET//低电平识别

#define KEY_DOWN PRESS/*键按下*/
#define KEY_UP !PRESS/*键弹起*/

/**********局部变量声明******/

void Key_Scan(float dT);

#endif
