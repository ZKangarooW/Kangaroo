#ifndef __CTRL_CONTROTEMP_H__
#define __CTRL_CONTROTEMP_H__

#include "include.h"

/**********�궨��************/
#define ABS(x) ((x)>0?(x):-(x))

/**********ȫ�ֱ���**********/
extern uint8_t Protect,Display_Res;//�����ձ����ͼ�ˮ����ʾ

/**********ȫ�ֺ���**********/
void Temp_PID(void);//�¶ȿ���PIDϵ��
void Temp_Control(float dT);//�¶ȼ��ȿ���
void Check_FGS(float dT);//��������
void Check_AddWater(float dT);//����ˮ
void Check_TempStop(float dT);//����¶��Ƿ�ֹͣ����
#endif
