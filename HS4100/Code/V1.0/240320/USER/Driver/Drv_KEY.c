#include "Drv_KEY.h"

/**********局部变量声明******/
float Key_Cnt1,Key_Cnt2,Key_Cnt3;//按下时间
uint8_t Key_Flag1,Key_Flag2,Key_Flag3;//按键按下标志
uint8_t LongPress1,LongPress2,LongPress3;//按键长按标志

/*
*****************************************************************
 * 函数原型：void Key_Scan(float dT)
 * 功    能：按键扫描
*****************************************************************
*/
void Key_Scan(float dT)
{
	/************************************锁定键**************************************/
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
				if(sys.Lock)
					sys.Lock = 0;
				else
					sys.Lock = 1;
				Beep_Time = 0.1;//蜂鸣器响0.1S
			}
			Key_Flag1 = 0;//按键事件结束，等待下一次按下
			LongPress1 = 0;//长按标志清零
			Key_Cnt1 = 0;//按钮计数清零
		}
		if(Key_Cnt1 > 1.5 && Key_Cnt1 < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress1 == 0)//如果没有一直一直长按着
			{
				Beep_Flash = 2;//“滴滴”两下用于误触
				LongPress1 = 1;//长按标志置一
			}
		}
	}
    
	/**************************************定时键**************************************/
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
				if(sys.Lock)
				{
					Beep_Flash = 2;//“滴滴”两下用于误触
				}
				else
				{
					if(sys.SetMode_Option != 3)
					{
						sys.SetMode_Option = 3;
						Time_Twinkle_Time = 6;//闪烁时间6S
					}
					else
					{
						sys.SetMode_Option = 0;
						EC11A[1].EC11A_Knob = EC11A[0].EC11A_Knob = 0;
						Time_Twinkle_Time = 0;
						TimeSet_Flag = 1;//进入时间设定
					}
					Beep_Time = 0.1;//蜂鸣器响0.1S
				}
			}
			Key_Flag2 = 0;//按键事件结束，等待下一次按下
			LongPress2 = 0;//长按标志清零
			Key_Cnt2 = 0;//按钮计数清零		
		}
		if(Key_Cnt2 > 1.5 && Key_Cnt2 < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress2 == 0)//如果没有一直一直长按着
			{
				Beep_Flash = 2;//“滴滴”两下用于误触
				LongPress2 = 1;//长按标志置一
			}
		}
	}
	/**************************************正反转键**************************************/
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
				if(sys.Lock)
				{
					Beep_Flash = 2;//“滴滴”两下用于误触
				}
				else
				{
					if(!Speed.Cw)//改变转向的话
					{
						Speed.ADDMode = 2;//进去减速显示
						sys.Motor_Stop = 1;//电机停止
						Speed.Cw = 1;//进入改变转向
						Speed.CwShow = 1;//转向图标改变，动画开始
						SpeedSet_Flag = TempSet_Flag = TimeSet_Flag=1;//进入设置
					}
					Beep_Time = 0.1;//蜂鸣器响0.1S
				}
			}
			Key_Flag3 = 0;//按键事件结束，等待下一次按下
			LongPress3 = 0;//长按标志清零
			Key_Cnt3 = 0;//按钮计数清零		
		}
		if(Key_Cnt3 > 1.5 && Key_Cnt3 < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress3 == 0)//如果没有一直一直长按着
			{
				Beep_Flash = 2;//“滴滴”两下用于误触
				LongPress3 = 1;//长按标志置一
			}
		}
	}
}
