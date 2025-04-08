#include "System_Init.h"

/**
 * @brief 系统驱动初始化
 *
 */
void System_Init(void)
{
    /**********系统初始化开始**********/
    sys.Init_ok = 0;
	
	/**********参数初始化**************/
	Param_Read();
	
	/**********电机初始化**************/
	Drv_Motor_Init();
	
	/**********编码器初始化************/
	Encoder_Init();
	
	/**********红外初始化**************/
	Drv_Infrared_Init();
	
	/**********WS2812初始化**********/
    WS2812_Init();
	Motor_PID();
    /**********开机蜂鸣器响***********/
	Beep_Time = 0.1f;
	TM1650_Init();
    /**********系统初始化成功**********/
    sys.Init_ok = 1;
	
}
