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
	/**************************************L键**************************************/
	if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin) == 0)//按下按键
	{
		if(sys.Run_Status)
			return;
		Key_Cnt1 += dT;//按下时间++
		Key_Flag1 = 1;//按键按下标志置一
	}
	if(Key_Flag1 == 1)//按键被按下
	{
		if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin) == 1)//抬起按键
		{   
			if(Key_Cnt1 < 1.5)//小于1.5S是单击
			{
				if(sys.SetMode_Option)
				{
					if(sys.SetMode_Option == 1 || sys.SetMode_Option == 3)
					{
						Set_Speed -= 100;//速度-100
						if(Set_Speed < 100)//速度小于100
							Set_Speed = 100;//速度最小为100就下不去了
					}
					else if(sys.SetMode_Option == 2 || sys.SetMode_Option == 4)
					{
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
					}
				}
				else
				{
					Speed_Mode = 1;//L模式
					SetOK_Flag = 1;//进入设置
					Beep_Time = 0.1;
				}
			}
			Key_Flag1 = 0;//按键事件结束，等待下一次按下
			Key_Cnt1 = 0;//按钮计数清零
		}
		if(Key_Cnt1 > 5.0 && Key_Cnt1 < 5.2)//按键时间大于1.5S小于3S表示长按
		{
			if(sys.SetMode_Option)
			{
				Key_Flag1 = 0;//按键事件结束，等待下一次按下
				Key_Cnt1 = 1.5;//按钮计数
				return;
			}
			
			Speed_Mode = 1;//L模式
			SetOK_Flag = 1;//进入设置
			sys.SetMode_Option = 1;//进入设定模式
			Beep_Time = 0.1;
			Key_Flag1 = 0;//按键事件结束，等待下一次按下
			Key_Cnt1 = 1.5;//按钮计数
		}
	}
	/**************************************S键**************************************/
	if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)== 0)//按下按键
	{
		if(sys.Run_Status)
			return;
		Key_Cnt2 += dT;//按下时间++
		Key_Flag2 = 1;//按键按下标志置一
	}
	if(Key_Flag2 == 1)//按键被按下
	{
		if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) == 1)//抬起按键
		{   
			if(Key_Cnt2 < 1.5)//小于1.5S是单击
			{
				if(sys.SetMode_Option)
				{
					if(sys.SetMode_Option == 1 || sys.SetMode_Option == 3)
					{
						Set_Speed +=100;//速度+100
						if(Set_Speed > 2000)//速度大于2000时
							Set_Speed = 2000;//速度最大为2000就上不去了
					}
					else if(sys.SetMode_Option == 2 || sys.SetMode_Option == 4)
					{
						if(Time_Unit)//小时为单位时
							Set_Time += 3600;//设置时间加1小时
						else//在分钟为单位时
							Set_Time += 60;//设置时间加1分钟
						if(Set_Time>28800)//时间大于8小时
							Set_Time = 28800;//时间最大为8小时
					}
				}
				else
				{
					Speed_Mode = 0;//S模式
					SetOK_Flag = 1;//进入设置
					Beep_Time = 0.1;
				}
			}
			Key_Flag2 = 0;//按键事件结束，等待下一次按下
			Key_Cnt2 = 0;//按钮计数清零		
		}
		if(Key_Cnt2 > 5.0 && Key_Cnt2 < 5.2)//按键时间大于1.9S小于2.1S表示长按
		{
			if(sys.SetMode_Option)
			{
				Key_Flag2 = 0;//按键事件结束，等待下一次按下
				Key_Cnt2 = 1.5;//按钮计数
				return;
			}
			Speed_Mode = 0;//S模式
			SetOK_Flag = 1;//进入设置
			sys.SetMode_Option = 1;//进入设定模式
			Beep_Time = 0.1;
			Key_Flag2 = 0;//按键事件结束，等待下一次按下
			Key_Cnt2 = 1.5;//按钮计数
		}
	}
	/**************************************Stop键**************************************/
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
				if(sys.SetMode_Option)
				{
					sys.SetMode_Option++;
					SetOK_Flag = 1;//进入设置
				}
				else
				{
					if(sys.Run_Status == 1)//系统启动
					{
						sys.Motor_Stop = 1;//检测电机
						Speed_ADDMode = 4;//进入减速模式下
						sys.Run_Step = 0;
						Set_Speed = Param.Speed[Speed_Mode][sys.Run_Step];
						Set_Time = Param.Speed[Speed_Mode][sys.Run_Step];
					}
				}
				Beep_Time = 0.1;
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
	/**************************************Start键**************************************/
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
				if(sys.SetMode_Option)
				{
					Beep_Flash = 5;//蜂鸣器响5下
				}
				else
				{
					if(sys.Run_Status == 0)//系统没有启动
					{
						Speed_Val.SumError = 0xDD7D;//启动电机系数
						SetOK_Flag = 1;//设定数值标志
						Ctrl_Speed = Set_Speed;//把设定速度赋值给控制速度
						Ctrl_Time = Set_Time;//把设定时间赋值给控制时间
						sys.Run_Status = 1;//启动系统
						sys.SetMode_Option = 0;//设置选项清零
						Speed_ADDMode = 0;//数据处理重新开始
					}	
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
				
				LongPress4 = 1;//长按标志置一
			}
		}
	}
}

