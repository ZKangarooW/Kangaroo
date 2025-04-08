#ifndef __DRV_UART_H__
#define	__DRV_UART_H__

#include "include.h"

/**********�궨��************/
#define RXBUFFERSIZE 256//�����������ֽ���
#define TXBUFFERSIZE 256//�����������ֽ���

/**********�ṹ��************/
/**********ȫ�ֱ�������******/
extern char RxBuffer1[RXBUFFERSIZE];//��������
extern uint8_t aRxBuffer1;//�����жϻ���
extern uint8_t Uart1_Rx_Cnt;//���ջ������

/**********ȫ�ֺ���**********/

void Drv_Uart_Init(void);
void Uart_Put_Char(UART_HandleTypeDef *huart, uint8_t DataToSend);
void Uart_Put_String(UART_HandleTypeDef *huart, uint8_t *Str);
void Uart_Put_Buf(UART_HandleTypeDef *huart, uint8_t *DataToSend , uint8_t data_num);

#endif
