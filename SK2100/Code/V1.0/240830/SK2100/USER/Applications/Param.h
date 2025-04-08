#ifndef __PARAM_H__
#define __PARAM_H__

#include "include.h"

/**********�궨��************/
/**********�ṹ��************/
struct _Save_Param_
{
    uint8_t Flash_Check_Start; //����Ƿ��Ѿ���ʼ���Ŀ�ʼλ

    int16_t Speed;
    int32_t Time;
    
    uint8_t Flash_Check_End; //����Ƿ��Ѿ���ʼ���Ľ���λ
};
extern struct _Save_Param_ Param;

/**********ȫ�ֱ�������*******/
extern uint8_t Save_Param_En;

/**********ȫ�ֺ���**********/

void Param_Read(void);
void Param_Save_Overtime(float dT);

#endif
