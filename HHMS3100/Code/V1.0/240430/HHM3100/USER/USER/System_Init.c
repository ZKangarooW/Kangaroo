#include "System_Init.h"

/**
 * @brief 系统驱动初始化
 *
 */
void System_Init(void)
{
    /**********系统初始化开始**********/
    sys.Init_ok = 0;
    
    /**********LCD初始化*************/
    Lcd_Init();
    
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 1); // 背光电压，2.86V
    
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0); //加热盘
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, 0); //加热盘
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 0); //加热盘
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 0); //加热盘
    
    /**********开机蜂鸣器响***********/
    Beep_Time = 0.1f;
    
    /**********系统初始化成功**********/
    sys.Init_ok = 1;
}
