#include "Ctrl_Motor.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void Motor_Ctrl(float dT)
 * ��    �ܣ��������
*****************************************************************
*/
void Motor_Ctrl(float dT)
{
    if(sys.Motor_Status == 1)
    {
        Motor_ON;//�򿪵����Դ
    }
    else
    {
        Motor_OFF;//�رյ����Դ
    }
}
