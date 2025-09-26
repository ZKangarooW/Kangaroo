#ifndef __DRV_KEY_H__
#define __DRV_KEY_H__

#include "include.h"

/**********宏定义************/
#define KEY1 HAL_GPIO_ReadPin(OUT1_GPIO_Port, OUT1_Pin) // 读KEY1的电平
#define KEY2 HAL_GPIO_ReadPin(OUT2_GPIO_Port, OUT2_Pin) // 读KEY2的电平

// 用于识别按键按下的状态识别
#define KEY_PRESS RESET // 低电平识别

#define KEY_DOWN KEY_PRESS /*键按下*/
#define KEY_UP !KEY_PRESS  /*键弹起*/

/**********结构体************/
/**********全局变量声明*******/
extern uint8_t Lock_Switch, Shake_Switch; // 锁定和抖动开关
extern float Lock_Alarm;//锁定报警
   
/**********全局函数**********/

void Key_Scan(float dT);
void Check_Press(float dT);

#endif
