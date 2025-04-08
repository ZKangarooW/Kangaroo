#include "Interrupt.h"

/**
 * @brief 定时器更新（溢出）中断回调函数
 *
 * @param htim
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	Infrared_TIM_PeriodElapsedCallback(htim);
}

/**
 * @brief 定时器捕获回调函数
 *
 * @param htim
 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	Speed_IC_CaptureCallback(htim);
    Infrared_IC_CaptureCallback(htim);
}

/**
 * @brief PWM信号传输完成回调函数，该函数非常之重要
 *
 * @param htim
 */
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	WS2812B_PulseFinishedCallback(htim);
}
