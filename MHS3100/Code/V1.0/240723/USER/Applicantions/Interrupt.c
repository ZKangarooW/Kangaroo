#include "Interrupt.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
 * ��    �ܣ��ⲿ�ж�
*****************************************************************
*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	UNUSED(GPIO_Pin);
	
	EC11A_EXTI_Interrupt(GPIO_Pin);//EC11A��ť�жϺ���
}

/*
*****************************************************************
 * ����ԭ�ͣ�void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
 * ��    �ܣ����벶��ص�����
*****************************************************************
*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	Speed_Capture_Interrupt(htim);//�ٶȲ����жϺ���
}
