#include "Drv_KEY.h"

/**********全局变量**********/
float Key_Status;//在操作按键时

/**********局部变量声明******/
float Key_Cnt1,Key_Cnt2,Key_Cnt3,Key_Cnt4,Key_Cnt5;//按下时间
uint8_t Key_Flag1,Key_Flag2,Key_Flag3,Key_Flag4,Key_Flag5;//按键按下标志
uint8_t LongPress1,LongPress2,LongPress3,LongPress4,LongPress5;//按键长按标志

/*
*****************************************************************
 * 函数原型：void Check_Press(float dT)
 * 功    能：检测按键状态
*****************************************************************
*/
void Check_Press(float dT)
{
    if(Key_Status)
        Key_Status -= dT;
}

/*
*****************************************************************
 * 函数原型：void Key_Scan(float dT)
 * 功    能：按键扫描
*****************************************************************
*/
void Key_Scan(float dT)
{
	/**************************************P键******************************************/
	if(Key1 == Key_Down)//按下按键
	{
		if(LongPress1 == 0)//没有长按过
		{
			Key_Cnt1 += dT;//按下时间++
			Key_Flag1 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag1)//按键被按下
	{
		if(Key1 == Key_Up)//抬起按键
		{   
			if(Key_Cnt1 > 0.05f && Key_Cnt1 < 1.5)//按键时间大于0.05S小于1.5S是单击
			{
				Beep_Time = 0.1;//蜂鸣器响0.1S
			}
			Key_Flag1 = 0;//按键事件结束，等待下一次按下
			LongPress1 = 0;//长按标志清零
			Key_Cnt1 = 0;//按钮计数清零
		}
		if(Key_Cnt1 > 1.5 && Key_Cnt1 < 3.0)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress1 == 0)//如果没有一直一直长按着
			{
				
				LongPress1 = 1;//长按标志置一
			}
		}
	}

	/**************************************MENU键**************************************/
	if(Key2 == Key_Down)//按下按键
	{
		if(LongPress2 == 0)//没有长按过
		{
			Key_Cnt2 += dT;//按下时间++
			Key_Flag2 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag2)//按键被按下
	{
		if(Key2 == Key_Up)//抬起按键
		{   
			if(Key_Cnt2 > 0.05f && Key_Cnt2 < 1.5)//按键时间大于0.05S小于1.5S是单击
			{
				
			}
			Key_Flag2 = 0;//按键事件结束，等待下一次按下
			LongPress2 = 0;//长按标志清零
			Key_Cnt2 = 0;//按钮计数清零
		}
		if(Key_Cnt2 > 1.5 && Key_Cnt2 < 3.0)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress2 == 0)//如果没有一直一直长按着
			{
				
				LongPress2 = 1;//长按标志置一
			}
		}
	}
	
	/**************************************加键**************************************/
	if(Key3 == Key_Down)//按下按键
	{
		Key_Cnt3 += dT;//按下时间++
		Key_Flag3 = 1;//按键按下标志置一
	}
	if(Key_Flag3 == 1)//按键被按下
	{
		if(Key3 == Key_Up)//抬起按键
		{   
			if(Key_Cnt3 < 1.5)//按键时间大于0.05S小于1.5S是单击
			{
				
			}
			Key_Flag3 = 0;//按键事件结束，等待下一次按下
			Key_Cnt3 = 0;//按钮计数清零		
		}
		else if(Key_Cnt3 > 1.9 && Key_Cnt3 < 2.1)//按键时间大于1.9S小于2.1S表示长按
		{
			
			Key_Cnt3 = 1.88f;//按钮计数清零
			Key_Flag3 = 0;//按键事件结束，等待下一次按下
		}
	} 
	else
		Key_Cnt3 = 0;//按钮计数清零
	
	/**************************************减键**************************************/
	if(Key4 == Key_Down)//按下按键
	{
		Key_Cnt4 += dT;//按下时间++
		Key_Flag4 = 1;//按键按下标志置一
	}
	if(Key_Flag4 == 1)//按键被按下
	{
		if(Key4 == Key_Up)//抬起按键
		{   
			if(Key_Cnt4 < 1.5)//按键时间大于0.05S小于1.5S是单击
			{
				
			}
			Key_Flag4 = 0;//按键事件结束，等待下一次按下
			Key_Cnt4 = 0;//按钮计数清零		
		}
		else if(Key_Cnt4 > 1.9 && Key_Cnt4 < 2.1)//按键时间大于1.9S小于2.1S表示长按
		{
			
			Key_Cnt4 = 1.88f;//按钮计数清零
			Key_Flag4 = 0;//按键事件结束，等待下一次按下
		}
	} 
	else
		Key_Cnt4 = 0;//按钮计数清零
	
	/**************************************Start键***********************************/
	if(Key5 == Key_Down)//按下按键
	{
		if(LongPress5 == 0)//没有长按过
		{
			Key_Cnt5 += dT;//按下时间++
			Key_Flag5 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag5)//按键被按下
	{
		if(Key5 == Key_Up)//抬起按键
		{   
			if(Key_Cnt5 > 0.05f && Key_Cnt5 < 1.5)//按键时间大于0.05S小于1.5S是单击
			{
				
				
			}
			Key_Flag5 = 0;//按键事件结束，等待下一次按下
			LongPress5 = 0;//长按标志清零
			Key_Cnt5 = 0;//按钮计数清零
		}
		if(Key_Cnt5 > 1.5 && Key_Cnt5 < 3.0)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress5 == 0)//如果没有一直一直长按着
			{
				
				LongPress5 = 1;//长按标志置一
			}
		}
	}
}
