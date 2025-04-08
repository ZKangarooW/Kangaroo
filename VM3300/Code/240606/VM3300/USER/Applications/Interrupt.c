#include "Interrupt.h"

/**
 * @brief 定时器计数回调函数
 *
 * @param htim
 */
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//	Infrared_TIM_Interrupt(htim);//红外发送定时计数中断函数
//}

///**
// * @brief 定时器捕获回调函数
// *
// * @param htim
// */
//void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
//{
//Infrared_IC_CaptureCallback(htim);
//	Speed_IC_CaptureCallback(htim);
//}

/**
 * @brief PWM信号传输完成回调函数，该函数非常之重要
 *
 * @param htim
 */
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	WS2812B_PulseFinishedCallback(htim);
}
