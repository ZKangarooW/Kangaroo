#ifndef __CTRL_CONTROTEMP_H__
#define __CTRL_CONTROTEMP_H__

#include "include.h"

/**********�궨��************/

/**********ȫ�ֱ�������******/
extern bool tuning_complete;//�Զ����α�־λ
extern float last_peak_time;//��һ������
extern int oscillation_count;//������

/**********ȫ�ֺ���**********/
void Temp_PID(void);//�¶ȿ���PIDϵ��
void Temp_Control(float dT);//�¶ȼ��ȿ���

#endif
