#include "System_Init.h"

/**
 * @brief 系统功能初始化
 * 
 */
void System_Init(void)
{
	/**********系统初始化成功**********/
	sys.Init_ok = 0;
    
    if(HAL_GPIO_ReadPin(Key_POR_GPIO_Port,Key_POR_Pin) == KEY_DOWN)//按下按键
	{	
		sys.Display = 1;
	}
    else
    {
        sys.Display = 0;
    }
    
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
	EC11A_Init();
	
	/**********ADC&DMA初始化***********/  
	ADCDMA_Init();
	
	/**********蜂鸣器响0.1S************/  
    if(sys.Display == 0)
    {
        Beep_Time = 0.1;
    }
	
	/**********系统初始化成功**********/
	sys.Init_ok = 1;
}
