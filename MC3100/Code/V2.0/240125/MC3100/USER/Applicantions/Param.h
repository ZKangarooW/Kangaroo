#ifndef __PARAM_H__
#define	__PARAM_H__

#include "include.h"

/**********�궨��************/
/**********�ṹ��************/
struct _Save_Param_
{	
	uint8_t Flash_Check_Start;//����Ƿ��Ѿ���ʼ���Ŀ�ʼλ
	uint8_t Flash_Check_End;//����Ƿ��Ѿ���ʼ���Ľ���λ
	uint8_t type;//����
	int Speed;//�ٶ�
	int32_t Time;//ʱ��
	uint8_t Speed_Rcf;//������
};
extern struct _Save_Param_ Param;

/**********ȫ�ֱ�������******/
extern uint8_t Save_Param_En;//���浽Flash�ı�־λ

/**********�ֲ���������******/
/**********ȫ�ֺ���**********/
void Param_Read(void);//��ȡӲ���еĲ������ж��Ƿ����
void Param_Save_Overtime(float dT);//�����־λ��1��0.5s�󱣴�

#endif
