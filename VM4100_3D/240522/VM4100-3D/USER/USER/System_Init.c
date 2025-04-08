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
    
    /**********背光源亮度控制**********/  
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,30);//Set_Speed);//pwm 0—400
    
    /**********LCD初始化**********/  
	Lcd_Init();
    Lcd_Clr();
    
    /**********PID初始化**********/  
    PID_Init();
    
    /**********电机初始化**********/  
    Motor_Init();
    
    /**********电调初始化**********/  
    Encoder_Init();
    
    /**********数值初始化**********/  
	Param_Read();
    Beep_Time = 0.1;//蜂鸣器响0.1S
	
	/***************系统初始化成功**********/
	sys.Init_ok = 1;
}
