#include "System_Init.h"

/*
*****************************************************************
 * 函数原型：void System_Init(void)
 * 功    能：系统功能初始化
*****************************************************************
*/
void System_Init(void)
{
	/**********系统初始化开始**********/
	sys.Init_ok = 0;
	
	/**********参数初始化**************/
	Param_Read();
	
	/*********ADC&DMA初始化********/  
	ADCDMA_Init();
	
	/**********GN1640初始化************/
	GN1640_Init();
	
	/**********温度初始化**************/
	Temp_Iint();
	
	/**********PID初始化**********/     
    PID_Init();
	
	/**********蜂鸣器响一下************/
	Beep_Time = 0.2;//蜂鸣器响0.1S

	/**********系统初始化成功**********/
	sys.Init_ok = 1;
}
