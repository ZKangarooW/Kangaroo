#ifndef __DRV_WIND_H__
#define __DRV_WIND_H__

#include "include.h"

/**********宏定义************/
#define WIND_ON HAL_GPIO_WritePin(WIND_GPIO_Port, WIND_Pin, GPIO_PIN_SET)    // 打开风扇
#define WIND_OFF HAL_GPIO_WritePin(WIND_GPIO_Port, WIND_Pin, GPIO_PIN_RESET) // 关闭风扇

/**********结构体************/
/**********全局变量声明*******/
/**********全局函数**********/

#endif
