#ifndef __CTRL_CONTROTEMP_H__
#define __CTRL_CONTROTEMP_H__

#include "include.h"

/**********�궨��************/

/**********ȫ�ֱ�������******/
extern uint8_t Protect;//������

/**********ȫ�ֺ���**********/
void Temp_PID(void);//�¶ȿ���PIDϵ��
void Temp_Control(float dT);//�¶ȼ��ȿ���

#endif
