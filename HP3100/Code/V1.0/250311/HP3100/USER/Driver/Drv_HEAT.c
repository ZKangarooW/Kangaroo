#include "Drv_HEAT.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void HEAT_Init(void)
 * ��    �ܣ���ʼ������
*****************************************************************
*/
void HEAT_Init(void)
{
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);//����tim3ͨ����
    HEAT_OFF;
}
