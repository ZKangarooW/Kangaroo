#ifndef __DRV_TM1650_H__
#define __DRV_TM1650_H__

#include "include.h"

/**********�궨��************/
#define TM1650_SCL_H    HAL_GPIO_WritePin(TM1650_SCL_GPIO_Port, TM1650_SCL_Pin, GPIO_PIN_SET)
#define TM1650_SCL_L    HAL_GPIO_WritePin(TM1650_SCL_GPIO_Port, TM1650_SCL_Pin, GPIO_PIN_RESET)
#define TM1650_SDA_H    HAL_GPIO_WritePin(TM1650_SDA_GPIO_Port, TM1650_SDA_Pin, GPIO_PIN_SET)
#define TM1650_SDA_L    HAL_GPIO_WritePin(TM1650_SDA_GPIO_Port, TM1650_SDA_Pin, GPIO_PIN_RESET)

/**********�ṹ��************/
/**********ȫ�ֱ�������******/
/**********ȫ�ֺ���**********/
void TM1650_Clr(void);//TM1650��������
void TM1650_All(void);//TM165ȫ��ʾ����
void TM1650_Init(void);//TM1650��ʼ��
void TM1650_Write_DATA(uint8_t add,uint8_t DATA);//ָ����ַд������

#endif
