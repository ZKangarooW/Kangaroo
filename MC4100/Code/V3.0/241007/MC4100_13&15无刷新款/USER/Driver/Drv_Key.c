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
 * 功    能：按键扫描
*****************************************************************
*/
void Key_Scan(float dT)
{
	/**************************************P键**************************************/
	if(Key1 == 0)//按下按键
	{
		if(LongPress1 == 0)//没有长按过
		{
			Key_Cnt1 += dT;//按下时间++
			Key_Flag1 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag1 == 1)//按键被按下
	{
		if(Key1 == 1)//抬起按键
		{   
			if(Key_Cnt1 < 1.5)//小于1.5S是单击
			{
				if(sys.Run_Status)//如果在显示离心力的模式下都不能操作
				{
					Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
				}
				else
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
			}
			Key_Flag1 = 0;//按键事件结束，等待下一次按下
			LongPress1 = 0;//长按标志清零
			Key_Cnt1 = 0;//按钮计数清零
		}
		if(Key_Cnt1 > 1.5 && Key_Cnt1 < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress1 == 0)//如果没有一直一直长按着
			{
				Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
				LongPress1 = 1;//长按标志置一
			}
		}
	}
	/**************************************OPEN键**************************************/
	if(Key6 == 0)//按下按键
	{
		Key_Cnt2 += dT;//按下时间++
		Key_Flag2 = 1;//按键按下标志置一
	}
	if(Key_Flag2 == 1)//按键被按下
	{
		if(Key6 == 1)//抬起按键
		{   
			if(Key_Cnt2 < 1.5)//小于1.5S是单击
			{
				if(sys.Run_Status || sys.Motor_Stop)//如果在显示离心力的模式下都不能操作
				{
					Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
				}
				else
				{
					if(HAL_GPIO_ReadPin(BREAKEZ_GPIO_Port,BREAKEZ_Pin)== 1)//电磁锁闭合时
						Lock_Status = 1;//打开电磁锁
					sys.Run_Status = 0;
					sys.Motor_Stop = 0;
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
				Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
				LongPress2 = 1;//长按标志置一
			}
		}
	}

	/**************************************MENU键**************************************/
	if(Key2 == 0)//按下按键
	{
		if(LongPress3 == 0)//没有长按过
		{
			Key_Cnt3 += dT;//按下时间++
			Key_Flag3 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag3 == 1)//按键被按下
	{
		if(Key2 == 1)//抬起按键
		{   
			if(Key_Cnt3 < 1.5)/*单击*///小于1.5S是单击
			{
				if(sys.Run_Status)//如果在显示离心力的模式下都不能操作
				{
					Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
				}
				else
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
			}
			Key_Flag3 = 0;//按键事件结束，等待下一次按下
			LongPress3 = 0;//长按标志清零
			Key_Cnt3 = 0;//按钮计数清零		
		}
		if(Key_Cnt3 > 1.5 && Key_Cnt3 < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress3 == 0)/*长按*///如果没有一直一直长按着
			{
				if(sys.Run_Status)//如果在显示离心力的模式下都不能操作
				{
					Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
				}
				else
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
				}
				LongPress3 = 1;//长按标志置一
			}
		}
	}
	/**************************************Start键**************************************/
	if(Key5 == 0)//按下按键
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
		if(Key5 == 1)//抬起按键
		{   
			if(Key_Cnt4 < 1.5)//小于1.5S是单击
			{
				if(HAL_GPIO_ReadPin(BREAKEZ_GPIO_Port,BREAKEZ_Pin)== 1)//电磁锁闭合时
				{
					if(sys.Run_Status == 0)
					{
						if(Show_Circle == 1)
							Circle_Run = 1;
						Speed_Val.SumError = 0xEA60;//启动电 机系数
						SetOK_Flag = 1;//设定值
						sys.Run_Status = 1;
						sys.SetMode_Option = 0;
						Speed_ADDMode = 0;
						if(sys.Motor_Stop)//如果在降速的情况下
							sys.Motor_Stop = 0;
					}
					else
					{
						sys.Motor_Stop = 1;//检测电机
						Speed_ADDMode = 2;//进入减速模式下
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
				Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
				LongPress4 = 1;//长按标志置一
			}
		}
	}

	/**************************************加键**************************************/
	if(Key3 == 0)//按下按键
	{
		Key_Cnt5 += dT;//按下时间++
		Key_Flag5 = 1;//按键按下标志置一
	}
	if(Key_Flag5 == 1)//按键被按下
	{
		if(Key3 == 1)//抬起按键
		{   
			if(Key_Cnt5 < 1.5)//小于1.5S是单击
			{
				if(sys.Run_Status)//如果在显示离心力的模式下都不能操作
				{
					Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
				}
				else
				{
					if(sys.SetMode_Option == 2)//设置时间
					{
						if(Time_Unit == 0)
							Set_Time += 10;//时间加10S
						else
							Set_Time += 60;//时间加60S
						if(Set_Time > 3590)//设置时间大于59分50秒时
							Set_Time = 3590;//设置时间等于59分50秒时
                        Key_Status = 2;//设置时2S不闪烁
                        Twinkle_Time = 6;//闪烁时间6S
					}
					else if(sys.SetMode_Option == 3)//设置速度
					{
						if(Speed_Mode)
						{
						if(Set_Speed == 70)
							Set_Speed = 100;//离心率等于100
						else
							Set_Speed += 100;//离心率加100
						if(Set_Speed > Xg_MAX)//离心率大于14100时
							Set_Speed = Xg_MAX;//离心率等于14100
						}
						else
						{
							Set_Speed += 100;//速度加100
							if(Set_Speed > Speed_MAX)//速度大于14500时
								Set_Speed = Speed_MAX;//速度等于14500
						}
                        Key_Status = 2;//设置时2S不闪烁
                        Twinkle_Time = 6;//闪烁时间6S
					}
					else if(sys.SetMode_Option == 4)//设置温度
					{
						Safe_Set_Temp += 10;//温度加1度
						if(Safe_Set_Temp > 500)//设定安全温度大于50度时
							Safe_Set_Temp = 500;//设定安全温度等于50度
                        Key_Status = 2;//设置时2S不闪烁
                        Twinkle_Time = 6;//闪烁时间6S
					}
					else if(Show_Circle == 1 && sys.SetMode_Option == 1)
					{
						PMode_Option++;
						if(PMode_Option > 9)
						{
							PMode_Option = 9;
						}
						Param_Read();
                        Key_Status = 2;//设置时2S不闪烁
                        Twinkle_Time = 6;//闪烁时间6S
					}
					else
					{
						Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
					}
				}
			}
			Key_Flag5 = 0;//按键事件结束，等待下一次按下
			Key_Cnt5 = 0;//按钮计数清零		
		}
		if(Key_Cnt5 > 1.9 && Key_Cnt5 < 2.1)//按键时间大于1.9S小于2.1S表示长按
		{
			if(sys.Run_Status)//如果在显示离心力的模式下都不能操作
			{
				Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
			}
			else
			{
				if(sys.SetMode_Option == 2)//设置时间
				{
					if(Time_Unit == 0)
							Set_Time += 60;//时间加60S
						else
							Set_Time += 600;//时间加600S
					if(Set_Time > 3590)//设置时间大于59分50秒时
						Set_Time = 3590;//设置时间等于59分50秒时
                    Key_Status = 2;//设置时2S不闪烁
                    Twinkle_Time = 6;//闪烁时间6S
				}
				else if(sys.SetMode_Option == 3)//设置速度
				{
					if(Speed_Mode)
					{
						if(Set_Speed == 70)
							Set_Speed = 100;//离心率等于100
						else if(Set_Speed >= 1000)
							Set_Speed += 1000;//离心率加1000
						else if(Set_Speed < 1000)
							Set_Speed += 100;//离心率加1000
						if(Set_Speed > Xg_MAX)//离心率大于14100时
							Set_Speed = Xg_MAX;//离心率等于14100
					}
					else
					{
						Set_Speed += 1000;//速度加1000
						if(Set_Speed > Speed_MAX)//速度大于14500时
							Set_Speed = Speed_MAX;//速度等于14500
					}
                    Key_Status = 2;//设置时2S不闪烁
                    Twinkle_Time = 6;//闪烁时间6S
				}
				else if(sys.SetMode_Option == 4)//设置温度
				{
					Safe_Set_Temp += 100;//温度加1度
					if(Safe_Set_Temp > 500)//设定安全温度大于50度时
						Safe_Set_Temp = 500;//设定安全温度等于50度
                    Key_Status = 2;//设置时2S不闪烁
                    Twinkle_Time = 6;//闪烁时间6S
				}
				else
				{
					Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
				}
			}
			Key_Flag5 = 0;//按键事件结束，等待下一次按下
			Key_Cnt5 = 1.5;//按钮计数清零
		}
	}
	/**************************************减键**************************************/
	if(Key4 == 0)//按下按键
	{
		if(LongPress6 == 0)//没有长按过
		{
			Key_Cnt6 += dT;//按下时间++
			Key_Flag6 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag6 == 1)//按键被按下
	{
		if(Key4 == 1)//抬起按键
		{   
			if(Key_Cnt6 < 1.5)//小于1.5S是单击
			{
				if(sys.Run_Status)//如果在显示离心力的模式下都不能操作
				{
					Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
				}
				else
				{
					if(sys.SetMode_Option == 2)//设置时间
					{
						if(Time_Unit == 0)//时间状态是秒为单位时
							Set_Time -= 10;//时间减10S
						else
							Set_Time -= 60;//时间减60S
						if(Set_Time < 30)//设置时间小于30S时
							Set_Time = 30;//设置时间等于30S
                        Key_Status = 2;//设置时2S不闪烁
                        Twinkle_Time = 6;//闪烁时间6S
					}
					else if(sys.SetMode_Option == 3)//设置速度
					{
						if(Speed_Mode)
						{
							Set_Speed -= 100;//离心率加100
							if(Set_Speed < 70)//速度小于70时
								Set_Speed = 70;//速度小于70时
						}
						else
						{
							Set_Speed -= 100;//速度减100
							if(Set_Speed < 1000)//速度小于1000时
								Set_Speed = 1000;//速度等于1000
						}
                        Key_Status = 2;//设置时2S不闪烁
                        Twinkle_Time = 6;//闪烁时间6S
					}
					else if(sys.SetMode_Option == 4)//设置温度
					{
						Safe_Set_Temp -= 10;//温度减1度
						if(Safe_Set_Temp < (Safe_Rel_Temp+50))//设定安全温度大于实际安全温度+5度时
							Safe_Set_Temp = Safe_Rel_Temp+50;//设定安全温度等于实际安全温度+5度
						if(Safe_Set_Temp < 0)
						{
							Safe_Set_Temp = 0;
						}
                        Key_Status = 2;//设置时2S不闪烁
                        Twinkle_Time = 6;//闪烁时间6S
					}
					else if(Show_Circle == 1 && sys.SetMode_Option == 1)
					{
						PMode_Option--;
						if(PMode_Option < 1)
						{
							PMode_Option = 1;
						}
						Param_Read();
                        Key_Status = 2;//设置时2S不闪烁
                        Twinkle_Time = 6;//闪烁时间6S
					}
					else
					{
						Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
					}
				}
			}
			Key_Flag6 = 0;//按键事件结束，等待下一次按下
			Key_Cnt6 = 0;//按钮计数清零		
		}
		if(Key_Cnt6 > 1.9 && Key_Cnt6 < 2.1)//按键时间大于1.9S小于2.1S表示长按
		{
			if(sys.Run_Status)//如果在显示离心力的模式下都不能操作
			{
				Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
			}
			else
			{
				if(sys.SetMode_Option == 2)//设置时间
				{
					if(Time_Unit == 0)//时间状态是秒为单位时
							Set_Time -= 60;//时间减60S
						else
							Set_Time -= 600;//时间减600S
					if(Set_Time < 30)//设置时间小于30S时
						Set_Time = 30;//设置时间等于30S
                    Key_Status = 2;//设置时2S不闪烁
                    Twinkle_Time = 6;//闪烁时间6S
				}
				else if(sys.SetMode_Option == 3)//设置速度
				{
					if(Speed_Mode)
					{
						if(Set_Speed >= 1000)
							Set_Speed -= 1000;//离心率加1000
						else if(Set_Speed < 1000)
							Set_Speed -= 100;//离心率加1000
						if(Set_Speed < 70)//速度小于70时
							Set_Speed = 70;//速度小于70时
					}
					else
					{
						Set_Speed -= 1000;//速度减1000
						if(Set_Speed < 1000)//速度小于1000时
							Set_Speed = 1000;//速度等于11000
					}
                    Key_Status = 2;//设置时2S不闪烁
                    Twinkle_Time = 6;//闪烁时间6S
				}
				else if(sys.SetMode_Option == 4)//设置温度
				{
					Safe_Set_Temp -= 100;//温度加10度
					if(Safe_Set_Temp < (Safe_Rel_Temp+50))//设定安全温度大于实际安全温度+5度时
							Safe_Set_Temp = Safe_Rel_Temp+50;//设定安全温度等于实际安全温度+5度
					if(Safe_Set_Temp < 0)
					{
						Safe_Set_Temp = 0;
					}
                    Key_Status = 2;//设置时2S不闪烁
                    Twinkle_Time = 6;//闪烁时间6S
				}
				else
				{
					Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
				}
			}
			Key_Flag6 = 0;//按键事件结束，等待下一次按下
			Key_Cnt6 = 1.5;//按钮计数清零
		}
	}
}
