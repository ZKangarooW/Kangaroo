#ifndef __CTRL_CONTROTEMP_H__
#define __CTRL_CONTROTEMP_H__

#include "include.h"

/**********�궨��************/
#define ABS(x) ((x)>0?(x):-(x))

/**********ȫ�ֱ�������******/
extern uint8_t Protect;//������
extern uint16_t LIMIT_Val;//��������

/**********ȫ�ֺ���**********/
void Temp_PID(void);//�¶ȿ���PIDϵ��
void Temp_Control(float dT);//�¶ȼ��ȿ���

#endif
