#include "Beep.h"

/**********ȫ�ֱ���**********/
float Beep_Time;//���������ʱ��

/*
*****************************************************************
 * ����ԭ�ͣ� void Buzzer_Status(float dT)
 * ��    �ܣ� ��������״̬���
 * ��    ��:  dT:ִ������
 * ��    ���� uint16_t dT
*****************************************************************
*/
void Buzzer_Status(float dT)
{
    if(Beep_Time <= 0)
    { 
        Beep_OFF; 
        return;
    } 
    Beep_ON;
    Beep_Time -= dT;
}
