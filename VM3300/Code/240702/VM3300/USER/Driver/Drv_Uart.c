#include "Drv_Uart.h"

#if 1

/**
 * @brief 重定向c库函数printf到DEBUG_USARTx
 * 
 */
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
    return ch;
}

/**
 * @brief 重定向c库函数getchar,scanf到DEBUG_USARTx
 * 
 */
int fgetc(FILE *f)
{
    uint8_t ch = 0;
    HAL_UART_Receive(&huart1, &ch, 1, 0xffff);
    return ch;
}
#endif

/**
 * @brief 串口初始化
 * 
 */
void Drv_Uart_Init(void)
{
    HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer1, 1);
}

char RxBuffer1[RXBUFFERSIZE];//接收数据
uint8_t aRxBuffer1;//接收中断缓冲
uint8_t Uart1_Rx_Cnt = 0;//接收缓冲计数
/**
 * @brief 串口1中断回调函数，要在mian中先调用一次接收中断函数
 * 
 * @param huart 串口号
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    UNUSED(huart);
    /*********USART1**********/
    if(huart->Instance == USART1)//判断是由哪个串口触发的中断
    {
        HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer1, 1);//重新使能串口1接收中断
    }
}

/**
 * @brief 打印一个字节
 * 
 * @param huart 串口号
 * @param DataToSend 一个字节
 */
void Uart_Put_Char(UART_HandleTypeDef *huart, uint8_t DataToSend)
{
    HAL_UART_Transmit(huart, &DataToSend, 1, 0xFFFF);
}

/**
 * @brief 打印一串字符串
 * 
 * @param huart 串口号
 * @param Str 一串字符串
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

/**
 * @brief 打印一个数组
 * 
 * @param huart 串口号
 * @param DataToSend 数组
 * @param data_num 数组长度
 */
void Uart_Put_Buf(UART_HandleTypeDef *huart, uint8_t *DataToSend , uint8_t data_num)
{
    while(data_num)
    {
        Uart_Put_Char(huart, *DataToSend);
        DataToSend++;
        data_num--;
    }
}
