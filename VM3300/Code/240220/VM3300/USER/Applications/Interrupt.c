#include "Interrupt.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
 * ��    �ܣ���ʱ�������ص�����
*****************************************************************
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	Motor_TIM_Interrupt(htim);//EC11A��ť��ʱ�����жϺ���
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	Remote_IC_CaptureCallback(htim);
}
