#ifndef __DRV_TM1650_H__
#define __DRV_TM1650_H__

#include "include.h"

/**********宏定义************/
#define TM1650_SCL_H    HAL_GPIO_WritePin(TM1650_SCL_GPIO_Port, TM1650_SCL_Pin, GPIO_PIN_SET)
#define TM1650_SCL_L    HAL_GPIO_WritePin(TM1650_SCL_GPIO_Port, TM1650_SCL_Pin, GPIO_PIN_RESET)
#define TM1650_SDA_H    HAL_GPIO_WritePin(TM1650_SDA_GPIO_Port, TM1650_SDA_Pin, GPIO_PIN_SET)
#define TM1650_SDA_L    HAL_GPIO_WritePin(TM1650_SDA_GPIO_Port, TM1650_SDA_Pin, GPIO_PIN_RESET)
#define TM1650_SDA_RD() HAL_GPIO_ReadPin(TM1650_SDA_GPIO_Port, TM1650_SDA_Pin)

//#define SDA_IN()  {GPIOA->MODER &= ~(3UL << 10);}
//#define SDA_OUT() {GPIOA->MODER &= ~(3UL << 10); GPIOA->MODER |= (1UL << 10);}


#define SDA_IN()   {\
					GPIO_InitTypeDef  GPIO_Initstructure; \
					GPIO_Initstructure.Pin = TM1650_SDA_Pin;\
					GPIO_Initstructure.Mode = GPIO_MODE_INPUT; \
					HAL_GPIO_Init(TM1650_SDA_GPIO_Port, &GPIO_Initstructure); }   
#define SDA_OUT()    {\
					GPIO_InitTypeDef  GPIO_Initstructure; \
					GPIO_Initstructure.Pin = TM1650_SDA_Pin;\
					GPIO_Initstructure.Mode = GPIO_MODE_OUTPUT_PP;\
					GPIO_Initstructure.Pull = GPIO_NOPULL; \
					GPIO_Initstructure.Speed = GPIO_SPEED_FREQ_HIGH;\
					HAL_GPIO_Init(TM1650_SDA_GPIO_Port, &GPIO_Initstructure); } 	

#define	brighting_8			0x00
#define	brighting_7			0x07
#define	brighting_6			0x06
#define	brighting_5			0x05
#define	brighting_4			0x04
#define	brighting_3			0x03
#define	brighting_2			0x02
#define	brighting_1			0x01

															
/**********结构体************/
/**********全局变量声明******/
/**********全局函数**********/
					
void DisplayNumber_4BitDig(uint16_t Num);
void DrvTM1650_Init(void);

#endif
