#ifndef __DRV_TOUCH_H__
#define __DRV_TOUCH_H__

#include "include.h"

/**********�궨��************/
#define Key1 0x00000002
#define Key2 0x00000004
#define Key3 0x00000008

/**********�ṹ��************/
/**********ȫ�ֱ�������******/
extern float Key_Status;//�������±�־

/**********ȫ�ֺ���***********/

void Drv_Touch_Init(void);
void Touch_Scan(float dT);
void Check_Press(float dT);

#endif