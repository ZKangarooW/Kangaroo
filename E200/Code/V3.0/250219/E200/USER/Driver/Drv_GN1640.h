#ifndef __DRV_GN1640_H__
#define	__DRV_GN1640_H__

#include "include.h"

/**********宏定义************/
#define GN1640_CLK_H	HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET)
#define GN1640_CLK_L	HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET)
#define GN1640_DATA_H	HAL_GPIO_WritePin(DATA_GPIO_Port, DATA_Pin, GPIO_PIN_SET)
#define GN1640_DATA_L	HAL_GPIO_WritePin(DATA_GPIO_Port, DATA_Pin, GPIO_PIN_RESET)

/**********结构体************/
/**********全局变量声明******/
/**********局部变量声明******/
/**********全局函数**********/
void GN1640_CLS(void);//清屏函数
void GN1640_Init(void);//GN1640初始化
void GN1640_Write_DATA(uint8_t add,uint8_t DATA);//指定地址写入数据
void GN1640_ALL(void);//全屏函数

#endif
