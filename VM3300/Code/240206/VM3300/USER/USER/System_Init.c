#include "System_Init.h"

/**
 * @brief 系统驱动初始化
 *
 */
void System_Init(void)
{
    /**********系统初始化开始**********/
    sys.Init_ok = 0;
	/**********电机初始化**************/
	Drv_Motor_Init();
	/**********WS2812初始化**********/
//    WS2812_Init();
	
	HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, GPIO_PIN_RESET);
	/**********编码器初始化************/
	Encoder_Init();
	
	HAL_TIM_Base_Start_IT(&htim6);//开始定时器
    /**********开机蜂鸣器响***********/
    Beep_Time = 0.1f;
//	HAL_GPIO_WritePin(MO_GPIO_Port, MO_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_RESET);
//	PWM = 0;
	
    /**********系统初始化成功**********/
    sys.Init_ok = 1;
}
