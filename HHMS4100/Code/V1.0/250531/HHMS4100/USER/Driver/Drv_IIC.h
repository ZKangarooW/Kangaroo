#ifndef __DRV_IIC_H__
#define	__DRV_IIC_H__

#include "include.h"

/**********宏定义************/
// 设备地址
#define IIC_ADDR_MASTERWR	0x78

// 函数声明
void IIC_Start(void);
void IIC_Stop(void);
void IIC_Send_Byte(uint8_t d);
uint8_t IIC_Wait_Ack(void);
uint8_t  IIC_Read_Byte(void);
void IIC_Ack(uint8_t ack);
/**********结构体************/
/**********全局变量声明******/
/**********全局函数**********/


#endif
