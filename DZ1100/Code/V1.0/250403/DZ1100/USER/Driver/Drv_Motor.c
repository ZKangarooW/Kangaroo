#include "Drv_Motor.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void Drv_Motor_Init(void)
 * ��    �ܣ�Motor������ʼ��
*****************************************************************
*/
void Drv_Motor_Init(void)
{
    GPIO_SET_MUX_MODE(P12CFG, GPIO_MUX_GPIO);
    GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_2);
    
    Motor_OFF;//�رյ��
}
