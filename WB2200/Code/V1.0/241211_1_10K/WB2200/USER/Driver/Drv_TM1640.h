#ifndef __DRV_TM1640_H__
#define __DRV_TM1640_H__

#include "include.h"

/**********宏定义************/
#define TM1640_SCL_H    HAL_GPIO_WritePin(TM1640_SCL_GPIO_Port, TM1640_SCL_Pin, GPIO_PIN_SET)
#define TM1640_SCL_L    HAL_GPIO_WritePin(TM1640_SCL_GPIO_Port, TM1640_SCL_Pin, GPIO_PIN_RESET)
#define TM1640_SDA_H    HAL_GPIO_WritePin(TM1640_SDA_GPIO_Port, TM1640_SDA_Pin, GPIO_PIN_SET)
#define TM1640_SDA_L    HAL_GPIO_WritePin(TM1640_SDA_GPIO_Port, TM1640_SDA_Pin, GPIO_PIN_RESET)

/**********结构体************/
/**********全局变量声明******/
/**********全局函数**********/
void TM1640_Clr(void);//TM1640清屏函数
void TM1640_All(void);//TM1640全显示函数
void TM1640_Init(void);//TM1640初始化
void TM1640_Write_DATA(uint8_t add,uint8_t DATA);//指定地址写入数据

#endif
