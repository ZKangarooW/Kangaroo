#ifndef __DRV_IIC_H__
#define	__DRV_IIC_H__

#include "include.h"

/**********宏定义************/
//设置输出高低电平模式
#define SDA_OUT(X)   if(X) \
					HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin, GPIO_PIN_SET); \
					else  \
					HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin, GPIO_PIN_RESET);

#define SCL_OUT(X)	if(X) \
					HAL_GPIO_WritePin(SCL_GPIO_Port, SCL_Pin, GPIO_PIN_SET); \
					else  \
					HAL_GPIO_WritePin(SCL_GPIO_Port, SCL_Pin, GPIO_PIN_RESET);    

#define SDA_IN		 HAL_GPIO_ReadPin(SDA_GPIO_Port,SDA_Pin)//只有输入模式才能读取电平状态

/**********结构体************/
/**********全局变量声明******/
/**********全局函数**********/
void IIC_Start(void);
void IIC_Stop(void);
void IIC_Send_Byte(uint8_t d);
uint8_t IIC_Wait_Ack(void);
uint8_t  IIC_Read_Byte(void);
void IIC_Ack(uint8_t ack);

#endif
