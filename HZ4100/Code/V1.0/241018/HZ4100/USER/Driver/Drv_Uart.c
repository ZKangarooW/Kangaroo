#include "Drv_Uart.h"

#if 1
/*
*****************************************************************
 * ����ԭ�ͣ�int fputc(int ch, FILE *f)
 * ��    �ܣ��ض���c�⺯��printf��DEBUG_USARTx
 * ��    �룺int ch, FILE *f
 * ��    ����ch
 * ��    ����int ch, FILE *f
*****************************************************************
*/
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
    return ch;
}

/*
*****************************************************************
 * ����ԭ�ͣ�int fgetc(FILE *f)
 * ��    �ܣ��ض���c�⺯��getchar,scanf��DEBUG_USARTx
 * ��    �룺FILE *f
 * ��    ����ch
 * ��    ����FILE *f
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
 * ����ԭ�ͣ�void Drv_Uart_Init(void)
 * ��    �ܣ����ڳ�ʼ��
*****************************************************************
*/
void Drv_Uart_Init(void)
{
    HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer1, 1);
}

/*
*****************************************************************
 * ����ԭ�ͣ�void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
 * ��    �ܣ�����1�жϻص�������Ҫ��mian���ȵ���һ�ν����жϺ���
			 HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer1, 1);
*****************************************************************
*/
char RxBuffer1[RXBUFFERSIZE];//��������
uint8_t aRxBuffer1;//�����жϻ���
uint8_t Uart1_Rx_Cnt = 0;//���ջ������
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    UNUSED(huart);
    /*********USART1**********/
    if(huart->Instance == USART1)//�ж������ĸ����ڴ������ж�
    {
        Speed_Receive(aRxBuffer1);
        HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer1, 1);//����ʹ�ܴ���1�����ж�
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Uart_Put_Char(UART_HandleTypeDef *huart, uint8_t DataToSend)
 * ��    �ܣ���ӡһ���ֽ�
 * ��    ��: *huart�����ں� DataToSend��һ���ֽ�
 * ��    ����UART_HandleTypeDef *huart, uint8_t DataToSend
*****************************************************************
*/
void Uart_Put_Char(UART_HandleTypeDef *huart, uint8_t DataToSend)
{
    HAL_UART_Transmit(huart, &DataToSend, 1, 0xFFFF);
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Uart_Put_String(UART_HandleTypeDef *huart, uint8_t *Str)
 * ��    �ܣ���ӡһ���ַ���
 * ��    ��: *huart�����ں� *Str��һ���ַ���
 * ��    ����UART_HandleTypeDef *huart, uint8_t *Str
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
 * ����ԭ�ͣ�void Uart_Put_Buf(UART_HandleTypeDef *huart, uint8_t *DataToSend, uint8_t data_num)
 * ��    �ܣ���ӡһ������
 * ��    ��: *huart�����ں� *DataToSend������ data_num�����鳤��
 * ��    ����UART_HandleTypeDef *huart, uint8_t *DataToSend, uint8_t data_num
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
