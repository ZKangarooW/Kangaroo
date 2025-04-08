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
uint8_t Beep_Flag;//点动蜂鸣器flag
void Key_Scan(float dT)
{
	static float T;
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
				if(sys.SetMode_Option == 1)//在设置速度时
				{
					Set_Speed -= 100;//速度-100
					if(Set_Speed < 100)//速度小于100
						Set_Speed = 100;//速度最小为100就下不去了
					Beep_Time = 0.1;//蜂鸣器响0.1S
				}
				if(sys.SetMode_Option == 2)//在设置时间时
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
					Beep_Time = 0.1;//蜂鸣器响0.1S
				}
				Key_Status = 1;//按键一秒，表示按下时有1s的等待，不闪烁
				Twinkle_Time = 6;//一共闪烁6S
			}
			Key_Flag1 = 0;//按键事件结束，等待下一次按下
			Key_Cnt1 = 0;//按钮计数清零
		}
		if(Key_Cnt1 > 1.9 && Key_Cnt1 < 2.1)//按键时间大于1.5S小于3S表示长按
		{
			if(sys.SetMode_Option == 1)//在设置速度时
			{
				Set_Speed -=500;//速度减500
				if(Set_Speed < 100)//速度小于100
					Set_Speed = 100;//速度最小为100就下不去了
				Beep_Time = 0.1;//蜂鸣器响0.1S
			}
			if(sys.SetMode_Option == 2)//在设置时间时
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
				Beep_Time = 0.1;//蜂鸣器响0.1S
			}
			Key_Flag1 = 0;//按键事件结束，等待下一次按下
			Key_Cnt1 = 1.5;//按钮计数
			Key_Status = 1;//按键一秒，表示按下时有1s的等待，不闪烁
			Twinkle_Time = 6;//一共闪烁6S
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
				if(sys.SetMode_Option == 1)//在设置速度时
				{
					Set_Speed +=100;//速度+100
					if(Set_Speed > 3000)//速度大于3000时
						Set_Speed = 3000;//速度最大为3000就上不去了
					Beep_Time = 0.1;//蜂鸣器响0.1S
				}
				if(sys.SetMode_Option == 2)//在设置时间时
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
					Beep_Time = 0.1;//蜂鸣器响0.1S
				}
				Key_Status = 1;//按键一秒，表示按下时有1s的等待，不闪烁
				Twinkle_Time = 6;//一共闪烁6S
			}
			Key_Flag2 = 0;//按键事件结束，等待下一次按下
			Key_Cnt2 = 0;//按钮计数清零		
		}
		if(Key_Cnt2 > 1.9 && Key_Cnt2 < 2.1)//按键时间大于1.9S小于2.1S表示长按
		{
			if(sys.SetMode_Option == 1)//在设置速度时
			{
				Set_Speed +=500;//速度加500
				if(Set_Speed > 3000)//速度大于3000时
					Set_Speed = 3000;//速度最大为3000就上不去了
				Beep_Time = 0.1;//蜂鸣器响0.1S
			}
			if(sys.SetMode_Option == 2)//在设置时间时
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
				Beep_Time = 0.1;//蜂鸣器响0.1S
			}
			Key_Status = 1;//按键一秒，表示按下时有1s的等待，不闪烁
			Twinkle_Time = 6;//一共闪烁6S
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
				if(sys.Run_Status == 1 && Start_Flag == 1)//系统启动并且按过start键的话
				{
					sys.Motor_Stop = 1;//检测电机
					Speed_ADDMode = 4;//进入减速模式下
					Start_Flag = 0;//清除按下了开始按键
					Beep_Time = 0.1;//蜂鸣器响0.1S
				}
				if(sys.Run_Status == 0 && Start_Flag == 0)//系统没有启动和没按过start键的话
				{
					Speed_Val.SumError = 0xDD7D;//启动电机系数
					SetOK_Flag = 1;//设定数值标志
					Ctrl_Time = Set_Time;//把设定时间赋值给控制时间
					Param.Time = Set_Time;//时间
					sys.Run_Status = 1;//启动系统
					sys.SetMode_Option = 0;//设置选项清零
					Speed_ADDMode = 0;//数据处理重新开始
					Start_Flag = 1;//按下了开始按键
//					HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//开启tim1通道一
					Beep_Time = 0.1;//蜂鸣器响0.1S
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
				
				LongPress3 = 1;//长按标志置一
			}
		}
	}
	/**************************************MENU键**************************************/
	if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin )== 0)//按下按键
	{
		if(sys.Motor_Stop)
			return;
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
			Key_Flag4 = 0;//按键事件结束，等待下一次按下
			LongPress4 = 0;//长按标志清零
			Key_Cnt4 = 0;//按钮计数清零		
		}
		if(Key_Cnt4 > 1.5 && Key_Cnt4 < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress4 == 0)//如果没有一直一直长按着
			{
				if(sys.Run_Status == 0)
				{
					if(Speed_Mode == 0)//在点动模式下
					{
						Speed_Mode = 1;//打开常动模式
					}
					else//在点动模式下
					{
						Speed_Mode = 0;//打开点动模式
					}
				}
				Beep_Time = 0.1;//蜂鸣器响0.1S
				LongPress4 = 1;//长按标志置一
			}
		}
	}
	
	/**************************************T键**************************************/
	if(HAL_GPIO_ReadPin(KEY_T_GPIO_Port,KEY_T_Pin )== 0)//按下按键
	{
		if(Speed_Mode == 1 || Start_Flag == 1 || DownTime_Over == 1)//如果在常动模式下并且按下了start键，倒计时结束按着T键时可能会误触发蜂鸣器
			return;//跳出
		if(sys.Run_Status == 0)
		{
			Speed_Val.SumError = 0xDD7D;//启动电机系数
			SetOK_Flag = 1;//设定数值标志
			sys.Run_Status = 1;//启动系统
			sys.SetMode_Option = 0;//设置选项清零
			Speed_ADDMode = 0;//数据处理重新开始
			Time_State = 1;//时间显示“--”
			Beep_Flag = 1;//表示可以进入蜂鸣器响
		}
		else
		{
			if(Beep_Flag == 1)//为了运行时响一次
			{
				Beep_Time = 0.1f;
				Beep_Flag = 0;
			}				
			if(sys.Motor_Stop == 1)
			{
				T = 0;//周期清零
				Time_State = 1;//时间显示“--”
				sys.Motor_Stop = 0;//电机已经停止
				Speed_ADDMode = 1;//数据处理重新开始
			}
		}
	}
	if(HAL_GPIO_ReadPin(KEY_T_GPIO_Port,KEY_T_Pin )== 1)//放开按键
	{
		if(sys.Run_Status == 0)
			return;
		if((Speed_Mode == 1|| Start_Flag == 1) && Time_State == 0)
			return;
		T += dT;//看是不是误放开，然后计时
		if(T > 0.5f)
		{
			sys.Motor_Stop = 1;//电机已经停止
			Start_Flag = 0;//按下开始按键清零
			Speed_ADDMode = 4;//降速处理
			Beep_Flag = 1;//表示可以进入蜂鸣器响
			T = 0;//周期清零
		}
	}
}

