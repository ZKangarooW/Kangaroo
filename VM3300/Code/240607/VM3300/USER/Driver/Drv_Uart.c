#include "Drv_Uart.h"

#if 1

/**
 * @brief �ض���c�⺯��printf��DEBUG_USARTx
 * 
 */
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
    return ch;
}

/**
 * @brief �ض���c�⺯��getchar,scanf��DEBUG_USARTx
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
 * @brief ���ڳ�ʼ��
 * 
 */
void Drv_Uart_Init(void)
{
    HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer1, 1);
}

char RxBuffer1[RXBUFFERSIZE];//��������
uint8_t aRxBuffer1;//�����жϻ���
uint8_t Uart1_Rx_Cnt = 0;//���ջ������
/**
 * @brief ����1�жϻص�������Ҫ��mian���ȵ���һ�ν����жϺ���
 * 
 * @param huart ���ں�
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    UNUSED(huart);
    /*********USART1**********/
    if(huart->Instance == USART1)//�ж������ĸ����ڴ������ж�
    {
        HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer1, 1);//����ʹ�ܴ���1�����ж�
    }
}

/**
 * @brief ��ӡһ���ֽ�
 * 
 * @param huart ���ں�
 * @param DataToSend һ���ֽ�
 */
void Uart_Put_Char(UART_HandleTypeDef *huart, uint8_t DataToSend)
{
    HAL_UART_Transmit(huart, &DataToSend, 1, 0xFFFF);
}

/**
 * @brief ��ӡһ���ַ���
 * 
 * @param huart ���ں�
 * @param Str һ���ַ���
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
 * @brief ��ӡһ������
 * 
 * @param huart ���ں�
 * @param DataToSend ����
 * @param data_num ���鳤��
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
