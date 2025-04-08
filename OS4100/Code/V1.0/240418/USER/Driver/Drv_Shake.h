#ifndef __DRV_SHAKE_H__
#define __DRV_SHAKE_H__

#include "include.h"

/**********宏定义************/
#define G1 HAL_GPIO_ReadPin(G1_GPIO_Port, G1_Pin) // 读KEY2的电平

/**********结构体************/
/**********全局变量声明*******/
extern uint8_t Shake_Alarm; // 倾倒报警

/**********全局函数**********/

void Cheack_Shake(float dT);

#endif
