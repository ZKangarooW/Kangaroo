#include "Interrupt.h"

/**
 * @brief ��ʱ�����£�������жϻص�����
 *
 * @param htim
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	Infrared_TIM_PeriodElapsedCallback(htim);
}

/**
 * @brief ��ʱ������ص�����
 *
 * @param htim
 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	Speed_IC_CaptureCallback(htim);
    Infrared_IC_CaptureCallback(htim);
}

/**
 * @brief PWM�źŴ�����ɻص��������ú����ǳ�֮��Ҫ
 *
 * @param htim
 */
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	WS2812B_PulseFinishedCallback(htim);
}
