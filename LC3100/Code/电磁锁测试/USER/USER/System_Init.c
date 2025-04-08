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
	
	/**********LCD初始化***************/
	Lcd_Init();
	
	/**********电机初始化**************/
	Motor_Init();
	
	/**********编码器初始化************/
	Encoder_Init();
	
	/**********PID初始化***************/
	PID_Init();

	/**********参数初始化**************/
	Param_Read();
	Ctrl_Speed = Speed=Set_Speed;//速度初始化
	Ctrl_Time = Time = Set_Time;//时间初始化
	Beep_Time = 0.1;//蜂鸣器响0.1S  
    for(uint8_t i =0;i<=100;i++)
    {
        ADC_Val = Filter_ADC();//滤波获取adc的滑动平均值
        if(i == 100)//1S
        {
            NTC_Res = Get_Ntc_Temp(ADC_Val);//计算温度
        }
        HAL_Delay(10);//没有延时开机读不出温度
    }
	Display_SafeTemp = Safe_Rel_Temp;
	Speed_Mode = 6;//96孔板
	
	/**********系统初始化成功**********/
	sys.Init_ok = 1;
}
