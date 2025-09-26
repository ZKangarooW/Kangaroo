#ifndef __DRV_UART_H__
#define	__DRV_UART_H__

#include "include.h"

/**********宏定义************/
#define RXBUFFERSIZE 256//串口最大接收字节数
#define TXBUFFERSIZE 256//串口最大接收字节数

/**********结构体************/
/**********全局变量声明******/
extern char RxBuffer1[RXBUFFERSIZE];//接收数据
extern uint8_t aRxBuffer1;//接收中断缓冲
extern uint8_t Uart1_Rx_Cnt;//接收缓冲计数

/**********全局函数**********/
void Drv_Uart_Init(void);//串口初始化
void Uart_Put_Char(UART_HandleTypeDef *huart, uint8_t DataToSend);//打印一个字节
void Uart_Put_String(UART_HandleTypeDef *huart, uint8_t *Str);//打印一串字符串
void Uart_Put_Buf(UART_HandleTypeDef *huart, uint8_t *DataToSend, uint8_t data_num);//打印一个数组

#endif
