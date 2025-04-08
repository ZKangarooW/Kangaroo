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
	
    /**********电机初始化**********/
    Motor_Init();
    PID_Init();
    /**********编码器初始化**********/
    Encoder_Init();
   
    /**********初始化lcd屏幕**********/
	Lcd_Init();//初始化
    LCD_Light(LCD_ON);//打卡背光
    Lcd_All();//显示全部内容
    HAL_Delay(1000);//延时1S
    Lcd_Clr();//清屏
	
    /**********系统参数初始化**********/
	Param_Read();
	Speed = Ctrl_Speed = Set_Speed;
	Time = Ctrl_Time = Set_Time;
	Time_State  = (Set_Time < 60) ? 0 : 1;//判断是否设置了时间
	Beep_Time = 0.1;
	
	/***************系统初始化成功**********/
	sys.Init_ok = 1;
}
