#ifndef __DRV_HEAT_H__
#define __DRV_HEAT_H__

#include "include.h"

/**********�궨��************/
#define HEAT htim14.Instance->CCR1//����ģ��PWM

/**********�ṹ��************/
/**********ȫ�ֱ�������******/
/**********ȫ�ֺ���**********/

void HEAT_Init(void);

#endif
