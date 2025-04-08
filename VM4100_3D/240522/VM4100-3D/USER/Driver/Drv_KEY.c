#include "Drv_KEY.h"

#include "Drv_Key.h"

/**********全局变量声明******/
uint8_t Key_Status;//按键按下标志
uint8_t SetMode_Option;//选择设置模式

/**********局部变量声明******/
float Key_Cnt1,Key_Cnt2,Key_Cnt3,Key_Cnt4;//按下时间
uint8_t Key_Flag1,Key_Flag2,Key_Flag3,Key_Flag4;//按键按下标志
uint8_t LongPress1,LongPress2,LongPress3,LongPress4;//按键长按标志

/*
*****************************************************************
 * 函数原型：void Check_Press(float dT)
 * 功    能：检测按键按下状态-500ms
*****************************************************************
*/
void Check_Press(float dT)
{
    if(Key_Status)//按键按下
        Key_Status -= dT;//倒计时
}

/*
*****************************************************************
 * 函数原型：void Key_Scan(float dT)
 * 功    能：矩阵按键扫描
*****************************************************************
*/
uint8_t Beep_Flag;//点动蜂鸣器flag
void Key_Scan(float dT)
{
	/**************************************减键**************************************/
	if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin) == 0)//按下按键
	{
		Key_Cnt1 += dT;//按下时间++
		Key_Flag1 = 1;//按键按下标志置一
	}
	if(Key_Flag1 == 1)//按键被按下
	{
		if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin) == 1)//抬起按键
		{   
			if(Key_Cnt1 < 1.5)//小于1.5S是单击
			{
				if(SetMode_Option == 1)//在设置速度时
				{
					Set_Speed -= 1;//速度-1
					if(Set_Speed < 10)//速度小于10
						Set_Speed = 10;//速度最小为10就下不去了
                    Key_Status = 1;//按键一秒，表示按下时有1s的等待，不闪烁
                    Twinkle_Time = 6;//一共闪烁6S
				}
				else if(SetMode_Option == 2)//在设置时间时
				{
					#if(Type == 1)
					if(Time_Unit)//在小时为单位时
					{
						if(Set_Time == 3600)
							Set_Time -= 60;
						else
							Set_Time -= 3600;//时间减一小时
					}
					else//分钟为单位时
						Set_Time -= 60;//每次时间减一分钟
					if(Set_Time < 60)//时间小于一分钟
						Set_Time = 0;//设置时间为0
					#elif(Type == 0)
					if(Set_Time <= 60)//在秒为单位时
						Set_Time -= 1;//时间--
					else//分钟为单位时
						Set_Time -= 60;//每次时间减一分钟
					if(Set_Time < 1)//时间小于一秒时
						Set_Time = 0;//设置时间为0
					#endif
                    Key_Status = 1;//按键一秒，表示按下时有1s的等待，不闪烁
                    Twinkle_Time = 6;//一共闪烁6S
				}
                else
				{
					Beep_Flash = 2;
				}
			}
			Key_Flag1 = 0;//按键事件结束，等待下一次按下
			Key_Cnt1 = 0;//按钮计数清零
		}
		if(Key_Cnt1 > 1.9 && Key_Cnt1 < 2.1)//按键时间大于1.5S小于3S表示长按
		{
			if(SetMode_Option == 1)//在设置速度时
			{
				Set_Speed -=10;//速度减10
				if(Set_Speed < 10)//速度小于10
					Set_Speed = 10;//速度最小为10就下不去了
                Key_Status = 1;//按键一秒，表示按下时有1s的等待，不闪烁
                Twinkle_Time = 6;//一共闪烁6S
			}
			else if(SetMode_Option == 2)//在设置时间时
			{
				#if(Type == 1)
				if(Time_Unit)//在小时为单位时
				{
					if(Set_Time == 3600)
						Set_Time -= 60;
					else
						Set_Time -= 3600;//时间减一小时
				}
				else//小时为单位时
					Set_Time -= 600;//每次时间减十分钟
				if(Set_Time < 60)//时间小于一秒时
					Set_Time = 0;//设置时间为0
				#elif(Type == 0)
				if(Time_Unit == 0)//在秒为单位时
					Set_Time -= 10;//时间减10S
				else//分钟为单位时
					Set_Time -= 600;//每次时间减十分钟
				if(Set_Time < 1)//时间小于一秒时
					Set_Time = 0;//设置时间为0
				#endif
                Key_Status = 1;//按键一秒，表示按下时有1s的等待，不闪烁
                Twinkle_Time = 6;//一共闪烁6S
			}
            else
			{
				Beep_Flash = 2;
			}
			Key_Flag1 = 0;//按键事件结束，等待下一次按下
			Key_Cnt1 = 1.5;//按钮计数
		}
	}
	/**************************************加键**************************************/
	if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)== 0)//按下按键
	{
		Key_Cnt2 += dT;//按下时间++
		Key_Flag2 = 1;//按键按下标志置一
	}
	if(Key_Flag2 == 1)//按键被按下
	{
		if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) == 1)//抬起按键
		{   
			if(Key_Cnt2 < 1.5)//小于1.5S是单击
			{
				if(SetMode_Option == 1)//在设置速度时
				{
					Set_Speed +=1;//速度+1
					if(Set_Speed > 80)//速度大于80时
						Set_Speed = 80;//速度最大为80就上不去了
                    Key_Status = 1;//按键一秒，表示按下时有1s的等待，不闪烁
                    Twinkle_Time = 6;//一共闪烁6S
				}
				else if(SetMode_Option == 2)//在设置时间时
				{
					#if(Type == 1)
					if(Time_Unit)//小时为单位时
						Set_Time += 3600;//设置时间加1小时
					else//在分钟为单位时
						Set_Time += 60;//设置时间加1分钟
					if(Set_Time>28800)//时间大于8小时
						Set_Time = 28800;//时间最大为8小时
					#elif(Type == 0)
					if(Set_Time == 0)//设置时间为0时
						Set_Time += 59;//从一秒开始加
					if(Time_Unit == 0)//在秒为单位时
						Set_Time += 1;//设置时间加1秒
					else//分钟为单位时
						Set_Time += 60;//设置时间加1分钟
					if(Set_Time>5940)//时间大于5940秒时（99分钟）
						Set_Time = 5940;//时间最大为99分钟
					#endif
                    Key_Status = 1;//按键一秒，表示按下时有1s的等待，不闪烁
                    Twinkle_Time = 6;//一共闪烁6S
				}
                else
                {
                    Beep_Flash = 2;
                }
			}
			Key_Flag2 = 0;//按键事件结束，等待下一次按下
			Key_Cnt2 = 0;//按钮计数清零		
		}
		if(Key_Cnt2 > 1.9 && Key_Cnt2 < 2.1)//按键时间大于1.9S小于2.1S表示长按
		{
			if(SetMode_Option == 1)//在设置速度时
			{
				Set_Speed +=10;//速度加10
				if(Set_Speed > 80)//速度大于80时
					Set_Speed = 80;//速度最大为80就上不去了
                Key_Status = 1;//按键一秒，表示按下时有1s的等待，不闪烁
                Twinkle_Time = 6;//一共闪烁6S
			}
			else if(SetMode_Option == 2)//在设置时间时
			{
				#if(Type == 1)
				if(Time_Unit)//小时为单位时
					Set_Time += 3600;//设置时间加1小时
				else//在分钟为单位时
				{
					Set_Time += 600;//设置时间加1分钟
					if(Set_Time > 3600)//大于1小时
						Set_Time = 3600;
				}
				if(Set_Time>28800)//时间大于8小时
					Set_Time = 28800;//时间最大为8小时
				#elif(Type == 0)
				if(Set_Time == 0)//设置时间为0时
					Set_Time += 60;//从一秒开始加
				if(Time_Unit == 0)//在秒为单位时
				{
					Set_Time += 10;//设置时间加1分钟
					if(Set_Time > 60)
						Set_Time = 60;
				}
				else//分钟为单位时
					Set_Time += 600;//设置时间加10分钟
				if(Set_Time>5940)//时间大于5940秒时（99分钟）
					Set_Time = 5940;//时间最大为99分钟
				#endif
                Key_Status = 1;//按键一秒，表示按下时有1s的等待，不闪烁
                Twinkle_Time = 6;//一共闪烁6S
			}
            else
			{
				Beep_Flash = 2;
			}
			Key_Flag2 = 0;//按键事件结束，等待下一次按下
			Key_Cnt2 = 1.5;//按钮计数
		}
	}
	/**************************************Start键**************************************/
	if(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin) == 0)//按下按键
	{
		if(LongPress3 == 0)//没有长按过
		{
			Key_Cnt3 += dT;//按下时间++
			Key_Flag3 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag3 == 1)//按键被按下
	{
		if(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin) == 1)//抬起按键
		{   
			if(Key_Cnt3 < 1.5)/*单击*///小于1.5S是单击
			{
				if(sys.Run_Status ==0)
				{
					sys.Run_Status = 1;
					Speed_ADDMode = 0;//屏幕显示模式
					Speed_Val.SumError = 0x5800;//启动的脉冲，能到10rpm
					Speed_New=0;//现在的速度清零
					Speed_Last = 0;//之前的速度等于当前显示速度
				}
				else
				{
					sys.Run_Status = 0;
				}
				SetMode_Option = 0;
				Beep_Time = 0.1;//蜂鸣器响0.1S
			}
			Key_Flag3 = 0;//按键事件结束，等待下一次按下
			LongPress3 = 0;//长按标志清零
			Key_Cnt3 = 0;//按钮计数清零		
		}
		if(Key_Cnt3 > 1.5 && Key_Cnt3 < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress3 == 0)/*长按*///如果没有一直一直长按着
			{
				Beep_Flash = 2;
				LongPress3 = 1;//长按标志置一
			}
		}
	}
	/**************************************MENU键**************************************/
	if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin )== 0)//按下按键
	{
		if(LongPress4 == 0)//没有长按过
		{
			Key_Cnt4 += dT;//按下时间++
			Key_Flag4 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag4 == 1)//按键被按下
	{
		if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin) == 1)//抬起按键
		{   
			if(Key_Cnt4 < 1.5)//小于1.5S是单击
			{
				SetMode_Option++;
				if(SetMode_Option > 2)
				{
					SetMode_Option = 0;
					
				}
				Twinkle_Time = 6000;
				Beep_Time = 0.1;//蜂鸣器响0.1S
			}
			Key_Flag4 = 0;//按键事件结束，等待下一次按下
			LongPress4 = 0;//长按标志清零
			Key_Cnt4 = 0;//按钮计数清零		
		}
		if(Key_Cnt4 > 1.5 && Key_Cnt4 < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress4 == 0)//如果没有一直一直长按着
			{
                Beep_Flash = 2;
				LongPress4 = 1;//长按标志置一
			}
		}
	}
}

/*
*****************************************************************
 * 函数原型：void Check_Key(void)
 * 功    能：检测按键状态-1s
*****************************************************************
*/
void Check_Key(void)
{
    if(Key_Status)
        Key_Status--;
}
