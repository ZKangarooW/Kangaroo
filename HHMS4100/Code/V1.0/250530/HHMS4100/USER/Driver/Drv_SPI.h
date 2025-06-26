#ifndef __DRV_SPI_H__
#define	__DRV_SPI_H__

#include "include.h"

/**********宏定义************/
extern SPI_HandleTypeDef hspi2;

/**********结构体************/
/**********全局变量声明******/
/**********全局函数**********/
void Drv_SPI_Init(void);//PSI初始化，启动SPI，否则开机第一次传输失败
uint8_t SPI2_ReadWriteByte(uint8_t txdata);//读写一个字节
void SPI2_Transmit(uint8_t *ucp_Data, uint16_t us_Size);//发送数据
void SPI2_Receive(uint8_t *ucp_Data, uint16_t us_Size);//接受数据

#endif
