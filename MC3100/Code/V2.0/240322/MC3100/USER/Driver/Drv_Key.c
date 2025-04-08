#include "Drv_Key.h"

/**********全局变量声明******/
uint8_t Key_Status;//按键按下标志

/**********局部变量声明******/
float Key_Cnt1,Key_Cnt2,Key_Cnt3,Key_Cnt4;//按下时间
uint8_t Key_Flag1,Key_Flag2,Key_Flag3,Key_Flag4;//按键按下标志
uint8_t LongPress1,LongPress2,LongPress3,LongPress4;//按键长按标志
uint16_t Rcf[13] = {67,151,268,419,604,822,1073,1358,1677,2029,2415,2834,3286};

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
				if(sys.Run_Status == 1|| Speed.Rel_Speed > 0)
				{
					Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
				}
				else
				{
					if(sys.SetMode_Option == 1)//在设置速度时
					{
						if(Speed.Speed_Mode==0)//速度
						{
							Speed.Set_Speed -= 500;//速度-500
							if(Speed.Set_Speed < Speed_MIN)//速度小于Speed_MIN
								Speed.Set_Speed = Speed_MIN;//速度最小为Speed_MIN就下不去了
						}
						else//离心力
						{
							if(Speed.Speed_Rcf)
								Speed.Speed_Rcf--;
							Speed.Set_Speed = Rcf[Speed.Speed_Rcf];//离心力
						}
					}
					else if(sys.SetMode_Option == 2)//在设置时间时
					{
						if(Time.Set_Time <= 60)//在秒为单位时
							Time.Set_Time -= 1;//时间--
						else//分钟为单位时
							Time.Set_Time -= 60;//每次时间减一分钟
						if(Time.Set_Time < Time_MIN)//时间小于Time_MIN秒时
							Time.Set_Time = Time_MIN;//设置时间为Time_MIN
					}
					else 
					{
						Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
					}
					Key_Status = 1;//按键一秒，表示按下时有1s的等待，不闪烁
					Twinkle_Time = 6;//一共闪烁6S
				}
			}
			Key_Flag1 = 0;//按键事件结束，等待下一次按下
			Key_Cnt1 = 0;//按钮计数清零
		}
		if(Key_Cnt1 > 1.9 && Key_Cnt1 < 2.1)//按键时间大于1.5S小于3S表示长按
		{
			if(sys.Run_Status == 1|| Speed.Rel_Speed > 0)
			{
				Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
			}
			else
			{
				if(sys.SetMode_Option == 1)//在设置速度时
				{
					if(Speed.Speed_Mode==0)//速度
					{
						Speed.Set_Speed -= 1000;//速度-1000
						if(Speed.Set_Speed < Speed_MIN)//速度小于Speed_MIN
							Speed.Set_Speed = Speed_MIN;//速度最小为Speed_MIN就下不去了
					}
					else//离心力
					{
						if(Speed.Speed_Rcf)
							Speed.Speed_Rcf--;
						Speed.Set_Speed = Rcf[Speed.Speed_Rcf];
					}
				}
				else if(sys.SetMode_Option == 2)//在设置时间时
				{
					if(Time.Time_Unit == 0)//在秒为单位时
						Time.Set_Time -= 10;//时间减10S
					else//分钟为单位时
					{
						Time.Set_Time -= 600;//每次时间减一分钟
						if(Time.Set_Time<60)
							Time.Set_Time = 59;
					}
					if(Time.Set_Time < Time_MIN)//时间小于Time_MIN秒时
						Time.Set_Time = Time_MIN;//设置时间为Time_MIN
				}
				else 
				{
					Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
				}
				Key_Status = 1;//按键一秒，表示按下时有1s的等待，不闪烁
				Twinkle_Time = 6;//一共闪烁6S
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
				if(sys.Run_Status == 1|| Speed.Rel_Speed > 0)
				{
					Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
				}
				else
				{
					if(sys.SetMode_Option == 1)//在设置速度时
					{
						if(Speed.Speed_Mode==0)//速度
						{
							Speed.Set_Speed +=500;//速度+500
							if(Speed.Set_Speed > Speed_MAX)//速度大于Speed_MAX时
								Speed.Set_Speed = Speed_MAX;//速度最大为Speed_MAX就上不去了
						}
						else//离心力
						{
							Speed.Speed_Rcf++;
							if(Speed.Speed_Rcf>Rcf_MAX)
								Speed.Speed_Rcf = Rcf_MAX;
							Speed.Set_Speed = Rcf[Speed.Speed_Rcf];
						}
					}
					else if(sys.SetMode_Option == 2)//在设置时间时
					{
						if(Time.Set_Time == 0)//设置时间为0时
							Time.Set_Time += 59;//从一秒开始加
						if(Time.Time_Unit == 0)//在秒为单位时
							Time.Set_Time += 1;//设置时间加1秒
						else//分钟为单位时
							Time.Set_Time += 60;//设置时间加1分钟
						if(Time.Set_Time>Time_MAX)//时间大于Time_MAX秒时（99分钟）
							Time.Set_Time = Time_MAX;//时间最大为99分钟
					}
					else 
					{
						Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
					}
					Key_Status = 1;//按键一秒，表示按下时有1s的等待，不闪烁
					Twinkle_Time = 6;//一共闪烁6S
				}
			}
			Key_Flag2 = 0;//按键事件结束，等待下一次按下
			Key_Cnt2 = 0;//按钮计数清零		
		}
		if(Key_Cnt2 > 1.9 && Key_Cnt2 < 2.1)//按键时间大于1.9S小于2.1S表示长按
		{
			if(sys.Run_Status == 1|| Speed.Rel_Speed > 0)
			{
				Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
			}
			else
			{
				if(sys.SetMode_Option == 1)//在设置速度时
				{
					if(Speed.Speed_Mode==0)//速度
					{
						Speed.Set_Speed += 1000;//速度加1000
						if(Speed.Set_Speed > Speed_MAX)//速度大于Speed_MAX时
							Speed.Set_Speed = Speed_MAX;//速度最大为Speed_MAX就上不去了
					}
					else//离心力
					{
						Speed.Speed_Rcf++;
						if(Speed.Speed_Rcf>Rcf_MAX)
							Speed.Speed_Rcf = Rcf_MAX;
						Speed.Set_Speed = Rcf[Speed.Speed_Rcf];
					}
				}
				else if(sys.SetMode_Option == 2)//在设置时间时
				{
					if(Time.Set_Time == 0)//设置时间为0时
						Time.Set_Time += 60;//从一秒开始加
					if(Time.Time_Unit == 0)//在秒为单位时
					{
						Time.Set_Time += 10;//设置时间加1分钟
						if(Time.Set_Time > 60)
							Time.Set_Time = 60;
					}
					else//分钟为单位时
						Time.Set_Time += 600;//设置时间加10分钟
					if(Time.Set_Time>Time_MAX)//时间大于Time_MAX秒时（99分钟）
						Time.Set_Time = Time_MAX;//时间最大为99分钟
				}
				else 
				{
					Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
				}
				Key_Status = 1;//按键一秒，表示按下时有1s的等待，不闪烁
				Twinkle_Time = 6;//一共闪烁6S
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
				if(HAL_GPIO_ReadPin(KEY_UP_GPIO_Port,KEY_UP_Pin)== 1)//电磁锁闭合时
				{
					if(sys.Run_Status)//系统启动
					{
						sys.Run_Status = 0;//系统关闭
						Beep_Time = 0.1;//蜂鸣器响0.1S
					}
					else//系统没有启动
					{
						SetOK_Flag = 1;//设定数值标志
						sys.Run_Status = 1;//启动系统
						sys.SetMode_Option = 0;//设置选项清零
						Beep_Time = 0.1;//蜂鸣器响0.1S
					}	
				}
				else
				{
					Beep_Flash = 7;
					sys.Lock_On = 1;
				}
			}
			Key_Flag3 = 0;//按键事件结束，等待下一次按下
			LongPress3 = 0;//长按标志清零
			Key_Cnt3 = 0;//按钮计数清零		
		}
		if(Key_Cnt3 > 1.5 && Key_Cnt3 < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress3 == 0)/*长按*///如果没有一直一直长按着
			{
				Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
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
				if(sys.Run_Status == 1|| Speed.Rel_Speed > 0)
				{
					Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
				}
				else
				{
					sys.SetMode_Option++;//设置选项++
					if(sys.Run_Status == 0)//没启动的情况下
					{
						if(sys.SetMode_Option > 2)//设置选项大于2
						{
							sys.SetMode_Option = 0;//设置选项清零
						}
					}
					else//启动的情况下
					{
						if(sys.SetMode_Option > 1)//设置选项大于1
						{
							sys.SetMode_Option = 0;//设置选项清零
						}
					}
					Twinkle_Time = 6;//一共闪烁6S
					Beep_Time = 0.1;//蜂鸣器响0.1S
				}
			}
			Key_Flag4 = 0;//按键事件结束，等待下一次按下
			LongPress4 = 0;//长按标志清零
			Key_Cnt4 = 0;//按钮计数清零		
		}
		if(Key_Cnt4 > 1.5 && Key_Cnt4 < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress4 == 0)//如果没有一直一直长按着
			{
				if(sys.Run_Status == 1|| Speed.Rel_Speed > 0)
				{
					Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
				}
				else
				{
					if(Speed.Speed_Mode)//假如在离心力的模式下
					{
						Speed.Speed_Mode = 0;//进入离心力显示模式
						Speed.Speed_Unit = 0;//显示离心力单位
						Param_Read();
					}	
					else
					{
						Speed.Speed_Mode = 1;//进入速度显示模式
						Speed.Speed_Unit = 1;//显示速度的单位
						Param_Read();
					}
					Beep_Time = 0.1;//蜂鸣器响0.1S
				}
				LongPress4 = 1;//长按标志置一
			}
		}
	}
}

