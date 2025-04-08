#include "Drv_Uart.h"

#if 1
/*
*****************************************************************
 * 函数原型：int fputc(int ch, FILE *f)
 * 功    能：重定向c库函数printf到DEBUG_USARTx
 * 输    入：int ch, FILE *f
 * 输    出：ch
 * 参    数：int ch, FILE *f
*****************************************************************
*/
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
    return ch;
}

/*
*****************************************************************
 * 函数原型：int fgetc(FILE *f)
 * 功    能：重定向c库函数getchar,scanf到DEBUG_USARTx
 * 输    入：FILE *f
 * 输    出：ch
 * 参    数：FILE *f
*****************************************************************
*/
int fgetc(FILE *f)
{
    uint8_t ch = 0;
    HAL_UART_Receive(&huart1, &ch, 1, 0xffff);
    return ch;
}
#endif

/*
*****************************************************************
 * 函数原型：void Drv_Uart_Init(void)
 * 功    能：串口初始化
*****************************************************************
*/
void Drv_Uart_Init(void)
{
    HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer1, 1);
}

/*
*****************************************************************
 * 函数原型：void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
 * 功    能：串口1中断回调函数，要在mian中先调用一次接收中断函数
			 HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer1, 1);
*****************************************************************
*/
char RxBuffer1[RXBUFFERSIZE];//接收数据
uint8_t aRxBuffer1;//接收中断缓冲
uint8_t Uart1_Rx_Cnt = 0;//接收缓冲计数
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    UNUSED(huart);
    /*********USART1**********/
    if(huart->Instance == USART1)//判断是由哪个串口触发的中断
    {
        Speed_Receive(aRxBuffer1);
        HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer1, 1);//重新使能串口1接收中断
    }
}

/*
*****************************************************************
 * 函数原型：void Uart_Put_Char(UART_HandleTypeDef *huart, uint8_t DataToSend)
 * 功    能：打印一个字节
 * 输    入: *huart：串口号 DataToSend：一个字节
 * 参    数：UART_HandleTypeDef *huart, uint8_t DataToSend
*****************************************************************
*/
void Uart_Put_Char(UART_HandleTypeDef *huart, uint8_t DataToSend)
{
    HAL_UART_Transmit(huart, &DataToSend, 1, 0xFFFF);
}

/*
*****************************************************************
 * 函数原型：void Uart_Put_String(UART_HandleTypeDef *huart, uint8_t *Str)
 * 功    能：打印一串字符串
 * 输    入: *huart：串口号 *Str：一串字符串
 * 参    数：UART_HandleTypeDef *huart, uint8_t *Str
*****************************************************************
*/
void Uart_Put_String(UART_HandleTypeDef *huart, uint8_t *Str)
{
    uint8_t *p;
    p = Str;
    while(*p != '\0')
    {
        Uart_Put_Char(huart, *p);
        p++;
    }
}

/*
*****************************************************************
 * 函数原型：void Uart_Put_Buf(UART_HandleTypeDef *huart, uint8_t *DataToSend, uint8_t data_num)
 * 功    能：打印一个数组
 * 输    入: *huart：串口号 *DataToSend：数组 data_num：数组长度
 * 参    数：UART_HandleTypeDef *huart, uint8_t *DataToSend, uint8_t data_num
*****************************************************************
*/
void Uart_Put_Buf(UART_HandleTypeDef *huart, uint8_t *DataToSend, uint8_t data_num)
{
    while(data_num)
    {
        Uart_Put_Char(huart, *DataToSend);
        DataToSend++;
        data_num--;
    }
}
