#ifndef __PARAM_H__
#define	__PARAM_H__

#include "include.h"

/**********�궨��************/
/**********�ṹ��************/
struct _Save_Param_
{	
	uint8_t Flash_Check_Start;//����Ƿ��Ѿ���ʼ���Ŀ�ʼλ
	uint8_t Flash_Check_End;//����Ƿ��Ѿ���ʼ���Ľ���λ
	uint32_t P_Param[3];
};
extern struct _Save_Param_ Param;

/**********ȫ�ֱ�������******/
extern uint8_t Save_Param_En;

/**********ȫ�ֺ���**********/
void Param_Read(void);//��ȡӲ���еĲ������ж��Ƿ����
void Param_Save_Overtime(float dT);//�����־λ��1��0.5s�󱣴�

#endif
