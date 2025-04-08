#ifndef __DRV_TM1650_H__
#define __DRV_TM1650_H__

#include "include.h"

/**********宏定义************/
#define TM1650_SCL_H    HAL_GPIO_WritePin(TM1650_SCL_GPIO_Port, TM1650_SCL_Pin, GPIO_PIN_SET)
#define TM1650_SCL_L    HAL_GPIO_WritePin(TM1650_SCL_GPIO_Port, TM1650_SCL_Pin, GPIO_PIN_RESET)
#define TM1650_SDA_H    HAL_GPIO_WritePin(TM1650_SDA_GPIO_Port, TM1650_SDA_Pin, GPIO_PIN_SET)
#define TM1650_SDA_L    HAL_GPIO_WritePin(TM1650_SDA_GPIO_Port, TM1650_SDA_Pin, GPIO_PIN_RESET)

/**********结构体************/
/**********全局变量声明******/
/**********全局函数**********/
void TM1650_Clr(void);//TM1650清屏函数
void TM1650_All(void);//TM165全显示函数
void TM1650_Init(void);//TM1650初始化
void TM1650_Write_DATA(uint8_t add,uint8_t DATA);//指定地址写入数据

#endif
