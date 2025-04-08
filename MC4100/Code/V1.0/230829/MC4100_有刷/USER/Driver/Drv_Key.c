#include "Drv_Key.h"

/**********全局变量声明******/
uint8_t Key_Status;//按键按下标志

/**********局部变量声明******/
float Key_Cnt1,Key_Cnt2,Key_Cnt3,Key_Cnt4,Key_Cnt5,Key_Cnt6;//按下时间
uint8_t Key_Flag1,Key_Flag2,Key_Flag3,Key_Flag4,Key_Flag5,Key_Flag6;//按键按下标志
uint8_t LongPress1,LongPress2,LongPress3,LongPress4,LongPress5,LongPress6;//按键长按标志

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
	ROW1_L;
	ROW2_H;
	ROW3_H;
	/**************************************P键**************************************/
	if(HAL_GPIO_ReadPin(COL1_GPIO_Port,COL1_Pin) == 0)//按下按键
	{
		if(sys.Run_Status)//如果在显示离心力的模式下都不能操作
			return;
		if(LongPress1 == 0)//没有长按过
		{
			Key_Cnt1 += dT;//按下时间++
			Key_Flag1 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag1 == 1)//按键被按下
	{
		if(HAL_GPIO_ReadPin(COL1_GPIO_Port,COL1_Pin) == 1)//抬起按键
		{   
			if(Key_Cnt1 < 1.5)//小于1.5S是单击
			{
				if(Show_Circle == 0)
				{
					Show_Circle = 1;//显示外框和P-几模式
					PMode_Option = 1;//记忆模式1
					Param_Read();//读取参数
					SetOK_Flag = 1;//设置参数
					sys.SetMode_Option = 1;//进入设置P值模式
					Twinkle_Time = 6;//闪烁时间6S
				}
				else
				{
					Show_Circle = 0;//不显示外框和P-几模式
					PMode_Option = 0;//记忆模式0
					Param_Read();//读取参数
					sys.SetMode_Option = 0;//模式清零
					SetOK_Flag = 1;//设置参数
				}
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
				LongPress1 = 1;//长按标志置一
			}
		}
	}
	/**************************************OPEN键**************************************/
	if(HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_Pin )== 0)//按下按键
	{
		if(sys.Run_Status || sys.Motor_Stop)//如果在显示离心力的模式下都不能操作
			return;
		Key_Cnt2 += dT;//按下时间++
		Key_Flag2 = 1;//按键按下标志置一
	}
	if(Key_Flag2 == 1)//按键被按下
	{
		if(HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_Pin) == 1)//抬起按键
		{   
			if(Key_Cnt2 < 1.5)//小于1.5S是单击
			{
				if(HAL_GPIO_ReadPin(BREAKEZ_GPIO_Port,BREAKEZ_Pin)== 1)//电磁锁闭合时
					Lock_Status = 1;//打开电磁锁
				sys.Run_Status = 0;
				sys.Motor_Stop = 0;
				Beep_Time = 0.1;//蜂鸣器响0.1S
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
	ROW1_H;
	ROW2_L;
	ROW3_H;
	/**************************************MENU键**************************************/
	if(HAL_GPIO_ReadPin(COL1_GPIO_Port,COL1_Pin) == 0)//按下按键
	{
		if(sys.Run_Status == 1)
			return;
		if(LongPress3 == 0)//没有长按过
		{
			Key_Cnt3 += dT;//按下时间++
			Key_Flag3 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag3 == 1)//按键被按下
	{
		if(HAL_GPIO_ReadPin(COL1_GPIO_Port,COL1_Pin) == 1)//抬起按键
		{   
			if(Key_Cnt3 < 1.5)/*单击*///小于1.5S是单击
			{
				if(Show_Circle == 0)
				{
					sys.SetMode_Option++;//设置模式++
					if(sys.SetMode_Option > 4)//退出设置
						sys.SetMode_Option = 0;//清零
					if(sys.SetMode_Option == 1)
						sys.SetMode_Option = 2;
				}
				else
				{
					sys.SetMode_Option++;//设置模式++
					if(sys.SetMode_Option > 4)//退出设置
						sys.SetMode_Option = 0;//清零
					
				}
				Beep_Time = 0.1;//蜂鸣器响0.1S
				Twinkle_Time = 6;//闪烁时间6S
			}
			Key_Flag3 = 0;//按键事件结束，等待下一次按下
			LongPress3 = 0;//长按标志清零
			Key_Cnt3 = 0;//按钮计数清零		
		}
		if(Key_Cnt3 > 1.5 && Key_Cnt3 < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress3 == 0)/*长按*///如果没有一直一直长按着
			{
				if(Speed_Mode)//假如在离心力的模式下
				{
					Speed_Mode = 0;//长按后推出
					Speed_Unit = 0;//显示速度单位
					Param_Read();
				}	
				else
				{
					Speed_Mode = 1;//进入离心力显示模式
					Speed_Unit = 1;//显示离心力单位
					Param_Read();
				}
				Beep_Time = 0.1;//蜂鸣器响0.1S
				Twinkle_Time = 6;//闪烁时间6S
				LongPress3 = 1;//长按标志置一
			}
		}
	}
	/**************************************Start键**************************************/
	if(HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_Pin )== 0)//按下按键
	{
		if(sys.Run_Status == 0)
		{
			if(Safe_Rel_Temp + 50 >= Safe_Set_Temp)
			{
				Safe_Temp_Twinkleg = 1;//安全温度图标闪烁
				Beep_Flash = 5;//蜂鸣器响5下
				return;
			}
		}
		if(LongPress4 == 0)//没有长按过
		{
			Key_Cnt4 += dT;//按下时间++
			Key_Flag4 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag4 == 1)//按键被按下
	{
		if(HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_Pin) == 1)//抬起按键
		{   
			if(Key_Cnt4 < 1.5)//小于1.5S是单击
			{
				if(HAL_GPIO_ReadPin(BREAKEZ_GPIO_Port,BREAKEZ_Pin)== 1)//电磁锁闭合时
				{
					if(sys.Run_Status == 0)
					{
						if(Show_Circle == 1)
							Circle_Run = 1;
						SetOK_Flag = 1;//设定值
						sys.Run_Status = 1;
						sys.SetMode_Option = 0;
						if(sys.Motor_Stop)//如果在降速的情况下
							sys.Motor_Stop = 0;
					}
					else
					{
						sys.Run_Status = 0;//检测电机
						sys.Motor_Stop = 1;//检测电机停止开盖
					}
				}
				else
				{
					Beep_Flash = 7;
					sys.Lock_On = 1;
				}
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
				Beep_Time = 0.1;//蜂鸣器响0.1S
				LongPress4 = 1;//长按标志置一
			}
		}
	}
	ROW1_H;
	ROW2_H;
	ROW3_L;
	/**************************************加键**************************************/
	if(HAL_GPIO_ReadPin(COL1_GPIO_Port,COL1_Pin) == 0)//按下按键
	{
		if(sys.Run_Status)
			return;
		Key_Cnt5 += dT;//按下时间++
		Key_Flag5 = 1;//按键按下标志置一
	}
	if(Key_Flag5 == 1)//按键被按下
	{
		if(HAL_GPIO_ReadPin(COL1_GPIO_Port,COL1_Pin) == 1)//抬起按键
		{   
			if(Key_Cnt5 < 1.5)//小于1.5S是单击
			{
				if(sys.SetMode_Option == 2)//设置时间
				{
					if(Time_Unit == 0)
						Set_Time += 10;//时间加10S
					else
						Set_Time += 60;//时间加60S
					if(Set_Time > 3590)//设置时间大于59分50秒时
						Set_Time = 3590;//设置时间等于59分50秒时
				}
				else if(sys.SetMode_Option == 3)//设置速度
				{
					#if(Type == 0)//10PRo
					if(Speed_Mode)
					{
						Val_xg += 1;//速度数组加1
						if(Val_xg > 90)//速度数组大于90
							Val_xg = 90;//速度数组等于90
						Set_Speed = xg_Val[Val_xg];
					}
					else
					{
						Val_Speed += 1;//速度加1个数组
						if(Val_Speed > 90)//速度数组大于90时
							Val_Speed = 90;//速度数组等于90
						Set_Speed =  Speed_Val[Val_Speed];
					}
					#elif(Type == 1)//12PRO
					if(Speed_Mode)
					{
						Val_xg += 1;//速度数组加1
						if(Val_xg > 110)//速度数组大于110
							Val_xg = 110;//速度数组等于110
						Set_Speed = xg_Val[Val_xg];
					}
					else
					{
						Val_Speed += 1;//速度加1个数组
						if(Val_Speed > 110)//速度数组大于110时
							Val_Speed = 110;//速度数组等于110
						Set_Speed = Speed_Val[Val_Speed];
					}
					#endif
				}
				else if(sys.SetMode_Option == 4)//设置温度
				{
					Safe_Set_Temp += 10;//温度加1度
					if(Safe_Set_Temp > 500)//设定安全温度大于50度时
						Safe_Set_Temp = 500;//设定安全温度等于50度
				}
				if(Show_Circle == 1 && sys.SetMode_Option == 1)
				{
					PMode_Option++;
					if(PMode_Option > 9)
					{
						PMode_Option = 9;
					}
					Param_Read();
				}
				Key_Status = 2;//设置时2S不闪烁
//				Beep_Time = 0.1;//蜂鸣器响0.1S
				Twinkle_Time = 6;//闪烁时间6S
			}
			Key_Flag5 = 0;//按键事件结束，等待下一次按下
			Key_Cnt5 = 0;//按钮计数清零		
		}
		if(Key_Cnt5 > 1.9 && Key_Cnt5 < 2.1)//按键时间大于1.9S小于2.1S表示长按
		{
			if(sys.SetMode_Option == 2)//设置时间
			{
				if(Time_Unit == 0)
						Set_Time += 60;//时间加60S
					else
						Set_Time += 600;//时间加600S
				if(Set_Time > 3590)//设置时间大于59分50秒时
					Set_Time = 3590;//设置时间等于59分50秒时
			}
			else if(sys.SetMode_Option == 3)//设置速度
			{
				#if(Type == 0)//10PRo
				if(Speed_Mode)
				{
					Val_xg += 10;//速度数组加10
					if(Val_xg > 90)//速度数组大于90
						Val_xg = 90;//速度数组等于90
					Set_Speed = xg_Val[Val_xg];
				}
				else
				{
					Val_Speed += 10;//速度加10个数组
					if(Val_Speed > 90)//速度数组大于90时
						Val_Speed = 90;//速度数组等于90
					Set_Speed =  Speed_Val[Val_Speed];
				}
				#elif(Type == 1)//12PRO
				if(Speed_Mode)
				{
					Val_xg += 10;//速度数组加10
					if(Val_xg > 110)//速度数组大于110
						Val_xg = 110;//速度数组等于110
					Set_Speed = xg_Val[Val_xg];
				}
				else
				{
					Val_Speed += 10;//速度加10个数组
					if(Val_Speed > 110)//速度数组大于110时
						Val_Speed = 110;//速度数组等于110
					Set_Speed =  Speed_Val[Val_Speed];
				}
				#endif
			}
			else if(sys.SetMode_Option == 4)//设置温度
			{
				Safe_Set_Temp += 100;//温度加1度
				if(Safe_Set_Temp > 500)//设定安全温度大于50度时
					Safe_Set_Temp = 500;//设定安全温度等于50度
			}
			Key_Status = 2;//设置时2S不闪烁
			Key_Flag5 = 0;//按键事件结束，等待下一次按下
			Key_Cnt5 = 1.5;//按钮计数清零
//			Beep_Time = 0.1;//蜂鸣器响0.1S
			Twinkle_Time = 6;//闪烁时间6S
		}
	}
	/**************************************减键**************************************/
	if(HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_Pin )== 0)//按下按键
	{
		if(sys.Run_Status)
			return;
		if(LongPress6 == 0)//没有长按过
		{
			Key_Cnt6 += dT;//按下时间++
			Key_Flag6 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag6 == 1)//按键被按下
	{
		if(HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_Pin) == 1)//抬起按键
		{   
			if(Key_Cnt6 < 1.5)//小于1.5S是单击
			{
				if(sys.SetMode_Option == 2)//设置时间
				{
					if(Time_Unit == 0)//时间状态是秒为单位时
						Set_Time -= 10;//时间减10S
					else
						Set_Time -= 60;//时间减60S
					if(Set_Time < 30)//设置时间小于30S时
						Set_Time = 30;//设置时间等于30S
				}
				else if(sys.SetMode_Option == 3)//设置速度
				{
					if(Speed_Mode)
					{
						Val_xg -= 1;//速度数组减1
						if(Val_xg < 0)//速度数组小于0
							Val_xg = 0;//速度数组等于0
						Set_Speed = xg_Val[Val_xg];
					}
					else
					{
						Val_Speed -= 1;//速度数组减1
						if(Val_Speed < 0)//速度数组小于0
							Val_Speed = 0;//速度数组等于0
						Set_Speed =  Speed_Val[Val_Speed];
					}
				}
				else if(sys.SetMode_Option == 4)//设置温度
				{
					Safe_Set_Temp -= 10;//温度减1度
					if(Safe_Set_Temp < (Safe_Rel_Temp+50))//设定安全温度大于实际安全温度+5度时
						Safe_Set_Temp = Safe_Rel_Temp+50;//设定安全温度等于实际安全温度+5度
				}
				if(Show_Circle == 1 && sys.SetMode_Option == 1)
				{
					PMode_Option--;
					if(PMode_Option < 1)
					{
						PMode_Option = 1;
					}
					Param_Read();
				}
				Key_Status = 2;//设置时2S不闪烁
//				Beep_Time = 0.1;//蜂鸣器响0.1S
				Twinkle_Time = 6;//闪烁时间6S
			}
			Key_Flag6 = 0;//按键事件结束，等待下一次按下
			Key_Cnt6 = 0;//按钮计数清零
		}
		if(Key_Cnt6 > 1.9 && Key_Cnt6 < 2.1)//按键时间大于1.9S小于2.1S表示长按
		{
			if(sys.SetMode_Option == 2)//设置时间
			{
				if(Time_Unit == 0)//时间状态是秒为单位时
						Set_Time -= 60;//时间减60S
					else
						Set_Time -= 600;//时间减600S
				if(Set_Time < 30)//设置时间小于30S时
					Set_Time = 30;//设置时间等于30S
			}
			else if(sys.SetMode_Option == 3)//设置速度
			{
				if(Speed_Mode)
				{
					Val_xg -= 10;//速度数组减1
					if(Val_xg < 0)//速度数组小于0
						Val_xg = 0;//速度数组等于0
					Set_Speed = xg_Val[Val_xg];
				}
				else
				{
					Val_Speed -= 10;//速度数组减10
					if(Val_Speed < 0)//速度数组小于0
						Val_Speed = 0;//速度数组等于0
					Set_Speed =  Speed_Val[Val_Speed];
				}
			}
			else if(sys.SetMode_Option == 4)//设置温度
			{
				Safe_Set_Temp -= 100;//温度加10度
				if(Safe_Set_Temp < (Safe_Rel_Temp+50))//设定安全温度大于实际安全温度+5度时
						Safe_Set_Temp = Safe_Rel_Temp+50;//设定安全温度等于实际安全温度+5度
			}
			Key_Status = 2;//设置时2S不闪烁
			Key_Flag6 = 0;//按键事件结束，等待下一次按下
			Key_Cnt6 = 1.5;//按钮计数清零
//			Beep_Time = 0.1;//蜂鸣器响0.1S
			Twinkle_Time = 6;//闪烁时间6S
		}
	}
}

