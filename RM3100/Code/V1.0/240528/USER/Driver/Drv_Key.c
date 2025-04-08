#include "Drv_Key.h"

/**********全局变量声明******/
uint8_t Key_Status;//按键按下标志

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
void Key_Scan(float dT)
{
	/**************************************Start键**************************************/
	if(KEY3 == 0)//按下按键
	{
		if(LongPress1 == 0)//没有长按过
		{
			Key_Cnt1 += dT;//按下时间++
			Key_Flag1 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag1 == 1)//按键被按下
	{
		if(KEY3 == 1)//抬起按键
		{   
			if(Key_Cnt1 < 1.5)//小于1.5S是单击
			{
				if(sys.Run_Status == 0)//系统没有启动的话
				{
					Speed_Val.SumError = 0x06B2;//启动电机系数
					SetOK_Flag = 1;//设定数值标志
					Ctrl_Time = Set_Time;//把设定时间赋值给控制时间
					Param.Time = Set_Time;//时间
					sys.Run_Status = 1;//启动系统
					sys.SetMode_Option = 0;//设置选项清零
					Speed_ADDMode = 0;//数据处理重新开始
				}
				else//系统启动的话
				{
					sys.Motor_Stop = 1;//检测电机
					Speed_ADDMode = 4;//进入减速模式下
				}
				Beep_Time = 0.1;//蜂鸣器响0.1S
			}
			Key_Flag1 = 0;//按键事件结束，等待下一次按下
			LongPress1 = 0;//长按标志清零
			Key_Cnt1 = 0;//按钮计数清零
		}
		if(Key_Cnt1 > 1.5 && Key_Cnt1 < 3.0)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress1 == 0)/*长按*///如果没有一直一直长按着
			{
				Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
				LongPress1 = 1;//长按标志置一
			}			
		}
	}
	/**************************************加键**************************************/
	if(KEY2== 0)//按下按键
	{
		Key_Cnt2 += dT;//按下时间++
		Key_Flag2 = 1;//按键按下标志置一
	}
	if(Key_Flag2 == 1)//按键被按下
	{
		if(KEY2 == 1)//抬起按键
		{   
			if(Key_Cnt2 < 1.5)//小于1.5S是单击
			{
				if(sys.SetMode_Option == 1)//在设置速度时
				{
					Set_Speed +=1;//速度++
					if(Set_Speed > 80)//速度大于80时
						Set_Speed = 80;//速度最大为80就上不去了
					Key_Status = 1;//按键一秒，表示按下时有1s的等待，不闪烁
					Twinkle_Time = 6;//一共闪烁6S
				}
				else if(sys.SetMode_Option == 2)//在设置时间时
				{
					Set_Time += 60;//设置时间加1分钟
					if(Set_Time>86399)//时间大于23小时59分
						Set_Time = 86399;//时间最大为23小时59分
					Key_Status = 1;//按键一秒，表示按下时有1s的等待，不闪烁
					Twinkle_Time = 6;//一共闪烁6S
				}
				else
				{
					Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
				}
			}
			Key_Flag2 = 0;//按键事件结束，等待下一次按下
			Key_Cnt2 = 0;//按钮计数清零		
		}
		if(Key_Cnt2 > 1.9 && Key_Cnt2 < 2.1)//按键时间大于1.9S小于2.1S表示长按
		{
			if(sys.SetMode_Option == 1)//在设置速度时
			{
				Set_Speed +=10;//速度加10
				if(Set_Speed > 80)//速度大于80时
					Set_Speed = 80;//速度最大为80就上不去了
				Key_Status = 1;//按键一秒，表示按下时有1s的等待，不闪烁
				Twinkle_Time = 6;//一共闪烁6S
			}
			else if(sys.SetMode_Option == 2)//在设置时间时
			{
				Set_Time += 600;//设置时间加10分钟
				if(Set_Time>86399)//时间大于23小时59分
					Set_Time = 86399;//时间最大为23小时59分
				Key_Status = 1;//按键一秒，表示按下时有1s的等待，不闪烁
				Twinkle_Time = 6;//一共闪烁6S
			}
			else
			{
				Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
			}
			Key_Flag2 = 0;//按键事件结束，等待下一次按下
			Key_Cnt2 = 1.5;//按钮计数
		}
	}

	/**************************************减键**************************************/
	if(KEY4 == 0)//按下按键
	{
		Key_Cnt3 += dT;//按下时间++
		Key_Flag3 = 1;//按键按下标志置一
	}
	if(Key_Flag3 == 1)//按键被按下
	{
		if(KEY4 == 1)//抬起按键
		{   
			if(Key_Cnt3 < 1.5)/*单击*///小于1.5S是单击
			{
				if(sys.SetMode_Option == 1)//在设置速度时
				{
					Set_Speed -=1;//速度--
					if(Set_Speed < 20)//速度小于20
						Set_Speed = 20;//速度最小为20就下不去了
					Key_Status = 1;//按键一秒，表示按下时有1s的等待，不闪烁
					Twinkle_Time = 6;//一共闪烁6S
				}
				else if(sys.SetMode_Option == 2)//在设置时间时
				{
					Set_Time -= 60;//每次时间减一分钟
					if(Set_Time < 60)//时间小于一秒时
						Set_Time = 0;//设置时间为0
					Key_Status = 1;//按键一秒，表示按下时有1s的等待，不闪烁
					Twinkle_Time = 6;//一共闪烁6S
				}
				else
				{
					Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
				}	
			}
			Key_Flag3 = 0;//按键事件结束，等待下一次按下
			Key_Cnt3 = 0;//按钮计数清零		
		}
		if(Key_Cnt3 > 1.9 && Key_Cnt3 < 2.1)//按键时间大于1.5S小于3S表示长按
		{
			if(sys.SetMode_Option == 1)//在设置速度时
			{
				Set_Speed -=10;//速度减10
				if(Set_Speed < 20)//速度小于20
					Set_Speed = 20;//速度最小为20就下不去了
				Key_Status = 1;//按键一秒，表示按下时有1s的等待，不闪烁
				Twinkle_Time = 6;//一共闪烁6S
			}
			else if(sys.SetMode_Option == 2)//在设置时间时
			{
				Set_Time -= 600;//每次时间减十分钟
				if(Set_Time < 60)//时间小于一秒时
					Set_Time = 0;//设置时间为0
				Key_Status = 1;//按键一秒，表示按下时有1s的等待，不闪烁
				Twinkle_Time = 6;//一共闪烁6S
			}
			else
			{
				Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
			}
			Key_Flag3 = 0;//按键事件结束，等待下一次按下
			Key_Cnt3 = 1.5;//按钮计数
		}
	}
	/**************************************MENU键**************************************/
	if(KEY1 == 0)//按下按键
	{
		if(LongPress4 == 0)//没有长按过
		{
			Key_Cnt4 += dT;//按下时间++
			Key_Flag4 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag4 == 1)//按键被按下
	{
		if(KEY1 == 1)//抬起按键
		{   
			if(Key_Cnt4 < 1.5)//小于1.5S是单击
			{
				if(sys.Motor_Stop)
				{
					Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
				}
				else
				{
					sys.SetMode_Option++;//设置选项++
                    if(sys.SetMode_Option > 2)//设置选项大于2
                    {
                        sys.SetMode_Option = 0;//设置选项清零
                        SetOK_Flag = 1;
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
				Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
				LongPress4 = 1;//长按标志置一
			}
		}
	}
}
