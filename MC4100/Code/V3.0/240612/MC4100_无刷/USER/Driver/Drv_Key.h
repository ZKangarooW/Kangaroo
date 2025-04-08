#ifndef __DRV_KEY_H__
#define	__DRV_KEY_H__

#include "include.h"

/**********宏定义************/
#define ROW1_H HAL_GPIO_WritePin(ROW1_GPIO_Port,ROW1_Pin,GPIO_PIN_SET)//ROW1拉高
#define ROW1_L HAL_GPIO_WritePin(ROW1_GPIO_Port,ROW1_Pin,GPIO_PIN_RESET)//ROW1拉低
#define ROW2_H HAL_GPIO_WritePin(ROW2_GPIO_Port,ROW2_Pin,GPIO_PIN_SET)//ROW2拉高
#define ROW2_L HAL_GPIO_WritePin(ROW2_GPIO_Port,ROW2_Pin,GPIO_PIN_RESET)//ROW2拉低
#define ROW3_H HAL_GPIO_WritePin(ROW3_GPIO_Port,ROW3_Pin,GPIO_PIN_SET)//ROW3拉高
#define ROW3_L HAL_GPIO_WritePin(ROW3_GPIO_Port,ROW3_Pin,GPIO_PIN_RESET)//ROW3拉低

/**********结构体************/
/**********全局变量声明******/
extern uint8_t Key_Status;//按键按下标志

/**********局部变量声明******/
/**********全局函数**********/
void Key_Scan(float dT);//矩阵按键扫描
void Check_Press(float dT);//检测按键按下状态

#endif
