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
    
	/**********参数初始化**************/
	Param_Read();
	
	/**********LCD初始化***************/
	Lcd_Init();
	
	/**********编码器初始化************/
	Encoder_Init();
	
	/**********电机初始化**************/
	Motor_Init();
	
	/**********加热初始化**************/
	HEAT_Init();
	
	/**********电机PID系数*************/
	Motor_PID();
	
	/**********温度PID系数*************/
	Temp_PID();
	
	/**********EC11A初始化定时器*******/
	#if(Key_Type == 1)
		EC11A_Init();
	#endif
	
	/**********ADC&DMA初始化***********/  
	ADCDMA_Init();
	
	/**********蜂鸣器响0.1S************/  
	Beep_Time = 0.1;
    
    #if (Key_Type == 0)
    if(KEY1 == KEY_DOWN)//按下MENU键进入倒计时模式设定界面
    {
        sys.Setting = 1;
		sys.Setting_Option = 1;
    }
	#elif (Key_Type == 1)
	if(HAL_GPIO_ReadPin(EC11A[0].Key_GPIO,EC11A[0].Key_Pin) == KEY_DOWN)
	{
		sys.Setting = 1;
		sys.Setting_Option = 2;
	}
    #endif
	
	/**********系统初始化成功**********/
	sys.Init_ok = 1;
}
