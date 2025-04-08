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
    WS2812_Init();
	
	/**********编码器初始化************/
//	Encoder_Init();
	
	HAL_TIM_Base_Start_IT(&htim6);//开始定时器
    /**********开机蜂鸣器响***********/
//	HAL_GPIO_WritePin(CW_GPIO_Port, CW_Pin, GPIO_PIN_RESET);
//	PWM = 0;

	Drv_Infrared_Init();
	Beep_Time = 0.1f;
    /**********系统初始化成功**********/
    sys.Init_ok = 1;
}
