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
    #if(Integration_TYPE <= 1)//设置成四联和六联时
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
    #elif(Integration_TYPE == 2)//设置成九联时
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
    #endif
    
    /**********加热模块pem控制**********/
    #if(Temp_TYPE == 1)//设置成加热款
        #if(Integration_TYPE <= 1)//设置成四联和六联时
        HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
        #elif(Integration_TYPE == 2)//设置成九联时
        HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
        #endif
    #endif
    
    /**********电机初始化**********/
    Motor_Init();
    
    /**********编码器初始化**********/
    Encoder_Init();
    
    /**********EC11A初始化定时器*******/
	EC11A_Init();
    
    /**********初始化lcd屏幕**********/
	Lcd_Init();//初始化
    LCD_Light(LCD_ON);//打卡背光 
    Lcd_All();//显示全部内容
    HAL_Delay(1000);//延时1S
	Lcd_Clr();//清屏

    /**********系统参数初始化**********/
    Work_Option = 1;//工位号1
	Param_Read();//读取参数
    SetOK_Flag = 1;
    PID_Init();//pid系数初始化
    Beep_Time = 0.1;//蜂鸣器响0.1S

	/***************系统初始化成功**********/
	sys.Init_ok = 1;
}
