#include "Interrupt.h"

/**
 * @brief ��ʱ�������ص�����
 *
 * @param htim
 */
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//	Infrared_TIM_Interrupt(htim);//���ⷢ�Ͷ�ʱ�����жϺ���
//}

///**
// * @brief ��ʱ������ص�����
// *
// * @param htim
// */
//void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
//{
//Infrared_IC_CaptureCallback(htim);
//	Speed_IC_CaptureCallback(htim);
//}

/**
 * @brief PWM�źŴ�����ɻص��������ú����ǳ�֮��Ҫ
 *
 * @param htim
 */
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	WS2812B_PulseFinishedCallback(htim);
}
