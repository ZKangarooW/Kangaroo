#ifndef __DRV_TM1640_H__
#define __DRV_TM1640_H__

#include "include.h"

/**********�궨��************/
#define TM1640_SCL_H    HAL_GPIO_WritePin(TM1640_SCL_GPIO_Port, TM1640_SCL_Pin, GPIO_PIN_SET)
#define TM1640_SCL_L    HAL_GPIO_WritePin(TM1640_SCL_GPIO_Port, TM1640_SCL_Pin, GPIO_PIN_RESET)
#define TM1640_SDA_H    HAL_GPIO_WritePin(TM1640_SDA_GPIO_Port, TM1640_SDA_Pin, GPIO_PIN_SET)
#define TM1640_SDA_L    HAL_GPIO_WritePin(TM1640_SDA_GPIO_Port, TM1640_SDA_Pin, GPIO_PIN_RESET)

/**********�ṹ��************/
/**********ȫ�ֱ�������******/
/**********ȫ�ֺ���**********/
void TM1640_Clr(void);//TM1640��������
void TM1640_All(void);//TM1640ȫ��ʾ����
void TM1640_Init(void);//TM1640��ʼ��
void TM1640_Write_DATA(uint8_t add,uint8_t DATA);//ָ����ַд������

#endif
