#include "Drv_Motor.h"

/**
 * @brief 电机初始化
 *
 */
void Drv_Motor_Init(void)
{
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1); // 开启tim2通道四 26值起来 63转
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2); // 开启tim2通道四 26值起来
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3); // 开启tim2通道四 26值起来
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4); // 开启tim2通道四 26值起来
    HAL_GPIO_WritePin(CW1_GPIO_Port, CW1_Pin, GPIO_PIN_SET);//
    HAL_GPIO_WritePin(CW2_GPIO_Port, CW2_Pin, GPIO_PIN_SET);//
    HAL_GPIO_WritePin(CW3_GPIO_Port, CW3_Pin, GPIO_PIN_SET);//
    HAL_GPIO_WritePin(CW4_GPIO_Port, CW4_Pin, GPIO_PIN_SET);//
}
