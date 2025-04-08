#ifndef __DRV_GN1640_H__
#define	__DRV_GN1640_H__

#include "include.h"

/**********�궨��************/
#define GN1640_CLK_H	HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET)
#define GN1640_CLK_L	HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET)
#define GN1640_DATA_H	HAL_GPIO_WritePin(DATA_GPIO_Port, DATA_Pin, GPIO_PIN_SET)
#define GN1640_DATA_L	HAL_GPIO_WritePin(DATA_GPIO_Port, DATA_Pin, GPIO_PIN_RESET)

/**********�ṹ��************/
/**********ȫ�ֱ�������******/
/**********�ֲ���������******/
/**********ȫ�ֺ���**********/
void GN1640_CLS(void);//��������
void GN1640_Init(void);//GN1640��ʼ��
void GN1640_Write_DATA(uint8_t add,uint8_t DATA);//ָ����ַд������
void GN1640_ALL(void);//ȫ������

#endif
