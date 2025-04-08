#include "System_Init.h"

/**
 * @brief 系统功能初始化
 * 
 */
void System_Init(void)
{
    HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);//关闭LED
    HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);//关闭LED
    HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_SET);//关闭LED
    HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,GPIO_PIN_SET);//关闭LED
    HAL_GPIO_WritePin(LED5_GPIO_Port,LED5_Pin,GPIO_PIN_SET);//关闭LED
    HAL_GPIO_WritePin(LED6_GPIO_Port,LED6_Pin,GPIO_PIN_SET);//关闭LED
	/**********系统初始化成功**********/
	sys.Init_ok = 0;
    
	/**********参数初始化**************/
	Param_Read();
	
	/**********LCD初始化***************/
	Lcd_Init();
	
//	/**********编码器初始化************/
//	Encoder_Init();
//	
//	/**********电机初始化**************/
//	Motor_Init();
//	
//	/**********加热初始化**************/
//	HEAT_Init();
//    
//	/**********电机PID系数*************/
//	Motor_PID();
//    
//	/**********温度PID系数*************/
//	Temp_PID();
//	
//	/**********EC11A初始化定时器*******/
//	EC11A_Init();
//	
//	/**********ADC&DMA初始化***********/  
//	ADCDMA_Init();
	
	/**********蜂鸣器响0.1S************/  
    Beep_Time = 0.1;
    
	/**********系统初始化成功**********/
	sys.Init_ok = 1;
}
