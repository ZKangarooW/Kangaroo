#include "Drv_Motor.h"

/**
 * @brief 电机初始化
 *
 */
void Drv_Motor_Init(void)
{
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1); // 开启tim5通道四 26值起来 63转
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2); // 开启tim5通道四 26值起来
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_3); // 开启tim5通道四 26值起来
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_4); // 开启tim5通道四 26值起来
    Motor_Switch(0,0);
    Motor_Switch(1,0);
    Motor_Switch(2,0);
    Motor_Switch(3,0);
}

void Motor_Switch(uint8_t i,uint8_t val)
{
    switch(i)
    {
        case 0:
            if(val)
               MO0_ON;
            else
               MO0_OFF; 
            break;
        case 1:
            if(val)
               MO1_ON;
            else
               MO1_OFF; 
            break;
        case 2:
            if(val)
               MO2_ON;
            else
               MO2_OFF; 
            break;
        case 3:
            if(val)
               MO3_ON;
            else
               MO3_OFF; 
            break;
    }
}
