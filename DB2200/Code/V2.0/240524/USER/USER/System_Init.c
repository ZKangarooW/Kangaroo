#include "System_Init.h"

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
    
    /**********LCD初始化**********/  
	Lcd_Init();
	Lcd_All();
	HAL_Delay(1000);
	Lcd_Clr();
	
    /**********PID初始化**********/     
    PID_Init();
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);//开启tim3通道2的pwm
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);//开启tim3通道2的pwm

	Param_Read();
    /**********数值初始化**********/  
	HAL_ADC_Start(&hadc);//开始读取adc的值
    HAL_Delay(10);//没有延时开机读不出温度
    NTC_Res = Get_Ntc_Temp(HAL_ADC_GetValue(&hadc));//将adc的值储存
	Rel_Temp = Ture_Temp;
	Display_RelTemp = Rel_Temp;
	
	Beep_Time = 0.1;//蜂鸣器响0.1S
	
	Display_Circle = 13;//梯度模式下外圈转动显示
	
	/***************系统初始化成功**********/
	sys.Init_ok = 1;
}
