#include "System_Init.h"
//#define COLD htim3.Instance->CCR1//制冷模块PWM
//#define HEAT htim3.Instance->CCR2//加热模块PWM
/*
*****************************************************************
 * 函数原型： void System_Init(void)
 * 功    能： 系统功能初始化
*****************************************************************
*/
void System_Init(void)
{	
	/**********系统初始化成功**********/
	sys.Init_ok = 0;
	
	/**********LCD初始化***************/
	Lcd_Init();
	
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);//开启tim3通道2的pwm
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);//开启tim3通道2的pwm
	
	/**********开机蜂鸣器响************/
	Beep_Time = 0.1;

	HAL_GPIO_WritePin(WIND_GPIO_Port,WIND_Pin,GPIO_PIN_RESET);//打开蜂鸣器
//	COLD = 0;
//	HEAT = 0;
	
	/**********系统初始化成功**********/
	sys.Init_ok = 1;
}
