#include "Drv_Motor.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void Drv_Motor_Init(void)
 * ��    �ܣ�Motor������ʼ��
*****************************************************************
*/
void Drv_Motor_Init(void)
{
    GPIO_SET_MUX_MODE(P20CFG, GPIO_MUX_GPIO);
    GPIO_ENABLE_OUTPUT(P2TRIS, GPIO_PIN_0);
    
    Motor_OFF;//�رյ��
}
