#include "Drv_KEY.h"

/**********局部变量声明******/
float Key_Cnt1;//按下时间
uint8_t Key_Flag1;//按键按下标志
uint8_t LongPress1;//按键长按标志

/*
*****************************************************************
 * 函数原型：void Drv_LED_Init(void)
 * 功    能：LED驱动初始化
*****************************************************************
*/
void Drv_Key_Init(void)
{
    GPIO_SET_MUX_MODE(P21CFG, GPIO_MUX_GPIO);
    GPIO_ENABLE_INPUT(P2TRIS, GPIO_PIN_1);
}
/*
*****************************************************************
 * 函数原型：void Key_Scan(float dT)
 * 功    能：矩阵按键扫描
*****************************************************************
*/
void Key_Scan(float dT)
{
	/************************************船型开关按键**************************************/
	if(KEY1 == 1)//按下按键
	{
		if(sys.Run_Status == 0)//没有长按过
        {
            sys.Run_Status = 1;//启动系统
            sys.Motor_Status = 1;//启动电机
            Time.Rel = 60;//1分钟
		}
	}
    else
    {
        sys.Run_Status = 0;//关闭系统
        sys.Motor_Status = 0;//关闭电机电源
    }
}
