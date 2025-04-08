#include "Drv_KEY.h"

/**********局部变量声明******/
float Key_Cnt1,Key_Cnt2,Key_Cnt3,Key_Cnt4,Key_Cnt5,Key_Cnt6;//按下时间
uint8_t Key_Flag1,Key_Flag2,Key_Flag3,Key_Flag4,Key_Flag5,Key_Flag6;//按键按下标志
uint8_t LongPress1,LongPress2,LongPress3,LongPress4,LongPress5,LongPress6;//按键长按标志

/**
 * @brief 按键扫描
 * 
 * @param dT 执行周期
 */
void Key_Scan(float dT)
{
	/************************************MUNE键**************************************/
	if(KEY1 == KEY_DOWN)//按下按键
	{
		if(LongPress1 == 0)//没有长按过
		{
			Key_Cnt1 += dT;//按下时间++
			Key_Flag1 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag1 == 1)//按键被按下
	{
		if(KEY1 == KEY_UP)//抬起按键
		{   
			if(Key_Cnt1 > 0.1 && Key_Cnt1 < 1.5)//小于1.5S是单击
			{
                HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);//关闭LED
			}
			Key_Flag1 = 0;//按键事件结束，等待下一次按下
			LongPress1 = 0;//长按标志清零
			Key_Cnt1 = 0;//按钮计数清零
		}
		if(Key_Cnt1 > 1.5 && Key_Cnt1 < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress1 == 0)//如果没有一直一直长按着
			{
                
				LongPress1 = 1;//长按标志置一
			}
		}
	}
    
	/**************************************P键**************************************/
	if(KEY2 == KEY_DOWN)//按下按键
	{	
		if(LongPress2 == 0)//没有长按过
		{
			Key_Cnt2 += dT;//按下时间++
			Key_Flag2 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag2 == 1)//按键被按下
	{
		if(KEY2 == KEY_UP)//抬起按键
		{   
			if(Key_Cnt2 > 0.1 && Key_Cnt2 < 1.5)//小于1.5S是单击
			{
                HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET);//关闭LED
			}
			Key_Flag2 = 0;//按键事件结束，等待下一次按下
			LongPress2 = 0;//长按标志清零
			Key_Cnt2 = 0;//按钮计数清零		
		}
		if(Key_Cnt2 > 1.5 && Key_Cnt2 < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress2 == 0)//如果没有一直一直长按着
			{
				
				LongPress2 = 1;//长按标志置一
			}
		}
	}
	/**************************************加键**************************************/
	if(KEY3 == KEY_DOWN)//按下按键
	{	
		if(LongPress3 == 0)//没有长按过
		{
			Key_Cnt3 += dT;//按下时间++
			Key_Flag3 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag3 == 1)//按键被按下
	{
		if(KEY3 == KEY_UP)//抬起按键
		{   
			if(Key_Cnt3 > 0.1 && Key_Cnt3 < 1.5)//小于1.5S是单击
			{
                HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_RESET);//关闭LED
			}
			Key_Flag3 = 0;//按键事件结束，等待下一次按下
			LongPress3 = 0;//长按标志清零
			Key_Cnt3 = 0;//按钮计数清零		
		}
		if(Key_Cnt3 > 1.5 && Key_Cnt3 < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress3 == 0)//如果没有一直一直长按着
			{
                
				LongPress3 = 1;//长按标志置一
			}
		}
	}
    
    /**************************************减键**************************************/
	if(KEY4 == KEY_DOWN)//按下按键
	{	
		if(LongPress4 == 0)//没有长按过
		{
			Key_Cnt4 += dT;//按下时间++
			Key_Flag4 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag4 == 1)//按键被按下
	{
		if(KEY4 == KEY_UP)//抬起按键
		{   
			if(Key_Cnt4 > 0.1 && Key_Cnt4 < 1.5)//小于1.5S是单击
			{
                HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,GPIO_PIN_RESET);//关闭LED
			}
			Key_Flag4 = 0;//按键事件结束，等待下一次按下
			LongPress4 = 0;//长按标志清零
			Key_Cnt4 = 0;//按钮计数清零		
		}
		if(Key_Cnt4 > 1.5 && Key_Cnt4 < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress4 == 0)//如果没有一直一直长按着
			{
                
				LongPress4 = 1;//长按标志置一
			}
		}
	}
    
    /**************************************Boil键**************************************/
	if(KEY5 == KEY_DOWN)//按下按键
	{	
		if(LongPress5 == 0)//没有长按过
		{
			Key_Cnt5 += dT;//按下时间++
			Key_Flag5 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag5 == 1)//按键被按下
	{
		if(KEY5 == KEY_UP)//抬起按键
		{   
			if(Key_Cnt5 > 0.1 && Key_Cnt5 < 1.5)//小于1.5S是单击
			{
                HAL_GPIO_WritePin(LED5_GPIO_Port,LED5_Pin,GPIO_PIN_RESET);//关闭LED
			}
			Key_Flag5 = 0;//按键事件结束，等待下一次按下
			LongPress5 = 0;//长按标志清零
			Key_Cnt5 = 0;//按钮计数清零		
		}
		if(Key_Cnt5 > 1.5 && Key_Cnt5 < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress5 == 0)//如果没有一直一直长按着
			{
                
				LongPress5 = 1;//长按标志置一
			}
		}
	}
    
    /**************************************Start键**************************************/
	if(KEY6 == KEY_DOWN)//按下按键
	{	
		if(LongPress6 == 0)//没有长按过
		{
			Key_Cnt6 += dT;//按下时间++
			Key_Flag6 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag6 == 1)//按键被按下
	{
		if(KEY6 == KEY_UP)//抬起按键
		{   
			if(Key_Cnt6 > 0.1 && Key_Cnt6 < 1.5)//小于1.5S是单击
			{
                HAL_GPIO_WritePin(LED6_GPIO_Port,LED6_Pin,GPIO_PIN_RESET);//关闭LED
			}
			Key_Flag6 = 0;//按键事件结束，等待下一次按下
			LongPress6 = 0;//长按标志清零
			Key_Cnt6 = 0;//按钮计数清零		
		}
		if(Key_Cnt6 > 1.5 && Key_Cnt6 < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress6 == 0)//如果没有一直一直长按着
			{
                
				LongPress6 = 1;//长按标志置一
			}
		}
	}
}
