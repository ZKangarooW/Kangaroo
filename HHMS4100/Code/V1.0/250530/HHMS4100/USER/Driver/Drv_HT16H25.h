#ifndef __DRV_HT16H25_H__
#define __DRV_HT16H25_H__

#include "include.h"

/**********宏定义************/
#define CS_HT_L()	HAL_GPIO_WritePin(SPI_CS_GPIO_Port,SPI_CS_Pin,GPIO_PIN_RESET)//使能ICM的SPI传输
#define CS_HT_H()	HAL_GPIO_WritePin(SPI_CS_GPIO_Port,SPI_CS_Pin,GPIO_PIN_SET)//禁止ICM的SPI传输

/**********全局函数**********/
void HT16H25_Init(void);

#endif
