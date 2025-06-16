#ifndef __DRV_KEY_H__
#define __DRV_KEY_H__

#include "include.h"

/**********宏定义************/
#define KEY1 HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)
#define KEY2 HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin)
#define KEY3 HAL_GPIO_ReadPin(KEY5_GPIO_Port,KEY5_Pin)

/**********局部变量声明******/

void Key_Scan(float dT);

#endif
