#ifndef __PARAM_H__
#define	__PARAM_H__

#include "include.h"

/**********�궨��************/
#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xCC

/**********�ṹ��************/
struct _Save_Param_
{	
	uint8_t Flash_Check_Start;//���ɿ��Ƿ��Ѿ���ʼ���Ŀ�ʼλ
	uint8_t Flash_Check_End;//���ɿ��Ƿ��Ѿ���ʼ���Ľ���λ
	int P_Param[10][2];
};

extern struct _Save_Param_ Param;

/**********ȫ�ֱ�������******/
extern uint8_t Save_Param_En;

/**********�ֲ���������******/
/**********ȫ�ֺ���**********/
void Param_Read(void);
void Sensor_Reset(void);
void Param_Save(void);

#endif
