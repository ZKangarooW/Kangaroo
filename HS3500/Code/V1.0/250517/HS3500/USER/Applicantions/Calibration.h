#ifndef __CALIBRATION_H__
#define __CALIBRATION_H__

#include "include.h"

/**********�궨��************/
/**********�ṹ��************/
typedef struct
{
    uint8_t Switch;//����
    int16_t Deviation;//У׼���¶�ƫ��
    float Val;
} _Calibration_;
extern _Calibration_ Calibration;//У׼����

/**********ȫ�ֱ�������*******/
/**********ȫ�ֺ���**********/

void Calibration_Temp(float dT);

#endif
