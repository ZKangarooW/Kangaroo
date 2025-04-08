#ifndef __CTRL_PROTOCOL_H__
#define	__CTRL_PROTOCOL_H__

#include "include.h"

/**********�궨��************/
#define BYTE0(dwTemp) (*(char *)(&dwTemp))
#define BYTE1(dwTemp) (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp) (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp) (*((char *)(&dwTemp) + 3))

/**********�ṹ��************/
typedef struct
{
	uint8_t Send_Data;//��������
}_Data_Flag_;
extern _Data_Flag_ Data_Flag;//���ͱ�־�ṹ��

/**********ȫ�ֱ�������******/
extern uint8_t Data_To_Send[10];//�������ݻ���

/**********ȫ�ֺ���**********/
void Data_Exchange(float dT);
uint8_t app_CalcCRC8(uint8_t *ptr, uint8_t len);

#endif
