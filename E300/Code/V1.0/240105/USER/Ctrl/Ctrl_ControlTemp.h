#ifndef __CTRL_CONTROTEMP_H__
#define __CTRL_CONTROTEMP_H__

#include "include.h"

/**********�궨��************/
/**********�ṹ��************/
/**********ȫ�ֱ�������******/
/**********ȫ�ֺ���**********/
void Temp_PID(void);//�¶ȿ���PIDϵ��
void Temp_Control(float dT);//�¶ȼ��ȿ���
void Check_Temp_Time(float dT);//��̨�����ȵ�ʱ��

#endif
