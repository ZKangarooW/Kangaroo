#include "Interrupt.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 * ��    �ܣ���ʱ�������ص�����
*****************************************************************
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	Infrared_TIM_Interrupt(htim);//���ⷢ�Ͷ�ʱ�����жϺ���
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	Infrared_IC_CaptureCallback(htim);
}
