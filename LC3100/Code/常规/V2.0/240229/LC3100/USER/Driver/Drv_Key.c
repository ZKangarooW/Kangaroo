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
			if(Key_Cnt1 < 5)//小于1.5S是单击
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
		if(Key_Cnt1 > 5 && Key_Cnt1 < 6)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress1 == 0)//如果没有一直一直长按着
			{
				if(Speed_ModeFlag)//假如在离心力的模式下
				{
					Speed_ModeFlag = 0;//长按后推出
					sys.SetMode_Option = 0;
				}	
				else
				{
					Speed_ModeFlag = 1;//显示P-几的离心率模块
					Param_Read();
					sys.SetMode_Option = 5;
				}
				Beep_Time = 0.1;//蜂鸣器响0.1S
				Twinkle_Time = 6;//闪烁时间6S
				LongPress1 = 1;//长按标志置一
			}
		}
	}
	/**************************************减键**************************************/
	if(HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_Pin )== 0)//按下按键
	{
		if(sys.Run_Status)
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
					if(Speed_Unit)
					{
						Set_Speed -= 100;//离心率加100
						if(Set_Speed < 100)//速度小于100时
							Set_Speed = 100;//速度小于100时
					}
					else
					{
						Set_Speed -= 100;//速度减100
						if(Set_Speed < 500)//速度小于500时
							Set_Speed = 500;//速度等于500
					}
				}
				else if(sys.SetMode_Option == 4)//设置温度
				{
					Safe_Set_Temp -= 10;//温度减1度
					if(Safe_Set_Temp < (Safe_Rel_Temp+50))//设定安全温度大于实际安全温度+5度时
						Safe_Set_Temp = Safe_Rel_Temp+50;//设定安全温度等于实际安全温度+5度
				}
				else if(sys.SetMode_Option == 5)//设置离心率模块
				{
					Speed_Mode -= 1;//模块类型减一
					if(Speed_Mode < 1)//模块类型小于一
						Speed_Mode = 1;//模块类型等于一
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
				Beep_Time = 0.1;//蜂鸣器响0.1S
				Twinkle_Time = 6;//闪烁时间6S
			}
			Key_Flag2 = 0;//按键事件结束，等待下一次按下
			Key_Cnt2 = 0;//按钮计数清零		
		}
		if(Key_Cnt2 > 1.9 && Key_Cnt2 < 2.1)//按键时间大于1.9S小于2.1S表示长按
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
				if(Speed_Unit)
				{
					Set_Speed -= 1000;//离心率加1000
					if(Set_Speed < 100)//速度小于100时
						Set_Speed = 100;//速度小于100时
				}
				else
				{
					Set_Speed -= 1000;//速度减1000
					if(Set_Speed < 500)//速度小于500时
						Set_Speed = 500;//速度等于500
				}
			}
			else if(sys.SetMode_Option == 4)//设置温度
			{
				Safe_Set_Temp -= 100;//温度加10度
				if(Safe_Set_Temp < (Safe_Rel_Temp+50))//设定安全温度大于实际安全温度+5度时
						Safe_Set_Temp = Safe_Rel_Temp+50;//设定安全温度等于实际安全温度+5度
			}
			else if(sys.SetMode_Option == 5)//设置离心率模块
			{
				Speed_Mode -= 1;//模块类型减一
				if(Speed_Mode < 1)//模块类型小于一
					Speed_Mode = 1;//模块类型等于一
			}	
			Key_Status = 2;//设置时2S不闪烁
			Key_Flag2 = 0;//按键事件结束，等待下一次按下
			Key_Cnt2 = 1.5;//按钮计数清零
			Beep_Time = 0.1;//蜂鸣器响0.1S
			Twinkle_Time = 6;//闪烁时间6S
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
				if(Speed_Unit)//假如在离心力的模式下
				{
					Speed_Unit = 0;//显示速度单位
					Param_Read();
				}	
				else
				{
					Speed_Unit = 1;//显示离心力单位
					Param_Read();
				}
				sys.SetMode_Option = 0;
				Beep_Time = 0.1;//蜂鸣器响0.1S
				Twinkle_Time = 6;//闪烁时间6S
				LongPress3 = 1;//长按标志置一
			}
		}
	}
	/**************************************Start键**************************************/
	if(HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_Pin )== 0)//按下按键
	{
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
				if((HAL_GPIO_ReadPin(UC_IN1_GPIO_Port,UC_IN1_Pin)== 1)&&(HAL_GPIO_ReadPin(UC_IN2_GPIO_Port,UC_IN2_Pin)== 1))//电磁锁1和2闭合时
				{
					if(sys.Run_Status == 0)
					{
						if(Show_Circle == 1)
							Circle_Run = 1;
						Speed_Val.SumError = 0x1200;//启动电 机系数
						SetOK_Flag = 1;//设定值
						sys.Run_Status = 1;
						sys.SetMode_Option = 0;
						Speed_ADDMode = 0;
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
		if(sys.Run_Status == 1)
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
					if(Speed_Unit)
					{
						Set_Speed += 100;//离心率加100
						if(Set_Speed > Xg_MAX)//离心率大于2100时
							Set_Speed = Xg_MAX;//离心率等于2100
					}
					else
					{
						Set_Speed += 100;//速度加100
						if(Set_Speed > Speed_MAX)//速度大于2500时
							Set_Speed = Speed_MAX;//速度等于2500
					}
				}
				else if(sys.SetMode_Option == 4)//设置温度
				{
					Safe_Set_Temp += 10;//温度加1度
					if(Safe_Set_Temp > 500)//设定安全温度大于50度时
						Safe_Set_Temp = 500;//设定安全温度等于50度
				}
				else if(sys.SetMode_Option == 5)//设置离心率模块
				{
					Speed_Mode += 1;//模块类型加一
					if(Speed_Mode > 6)//模块类型大于六
						Speed_Mode = 6;//模块类型等于六
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
				Beep_Time = 0.1;//蜂鸣器响0.1S
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
					Set_Time += 60;//时间加10S
				else
					Set_Time += 600;//时间加60S
				if(Set_Time > 3590)//设置时间大于59分50秒时
					Set_Time = 3590;//设置时间等于59分50秒时
			}
			else if(sys.SetMode_Option == 3)//设置速度
			{
				if(Speed_Unit)
				{
					Set_Speed += 1000;//离心率加1000
					if(Set_Speed > Xg_MAX)//离心率大于2100时
						Set_Speed = Xg_MAX;//离心率等于2100
				}
				else
				{
					Set_Speed += 1000;//速度加1000
					if(Set_Speed > Speed_MAX)//速度大于2500时
						Set_Speed = Speed_MAX;//速度等于2500
				}
			}
			else if(sys.SetMode_Option == 4)//设置温度
			{
				Safe_Set_Temp += 100;//温度加1度
				if(Safe_Set_Temp > 500)//设定安全温度大于50度时
					Safe_Set_Temp = 500;//设定安全温度等于50度
			}
			else if(sys.SetMode_Option == 5)//设置离心率模块
			{
				Speed_Mode += 1;//模块类型加一
				if(Speed_Mode > 6)//模块类型大于六
					Speed_Mode = 6;//模块类型等于六
			}
			Key_Status = 2;//设置时2S不闪烁
			Key_Flag5 = 0;//按键事件结束，等待下一次按下
			Key_Cnt5 = 1.5;//按钮计数清零
			Beep_Time = 0.1;//蜂鸣器响0.1S
			Twinkle_Time = 6;//闪烁时间6S
		}
	}
	/**************************************OPEN键**************************************/
	if(HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_Pin )== 0)//按下按键
	{
		if(sys.Run_Status)//如果在显示离心力的模式下都不能操作
			return;
		Key_Cnt6 += dT;//按下时间++
		Key_Flag6 = 1;//按键按下标志置一
	}
	if(Key_Flag6 == 1)//按键被按下
	{
		if(HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_Pin) == 1)//抬起按键
		{   
			if(Key_Cnt6 < 1.5)//小于1.5S是单击
			{
				if(HAL_GPIO_ReadPin(UC_IN1_GPIO_Port,UC_IN1_Pin)== 1)//电磁锁1闭合时
					Lock1_Status = 1;//打开电磁锁1
				if(HAL_GPIO_ReadPin(UC_IN2_GPIO_Port,UC_IN2_Pin)== 1)//电磁锁2闭合时
					Lock2_Status = 1;//打开电磁锁2
				sys.Run_Status = 0;
				Beep_Time = 0.1;//蜂鸣器响0.1S
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

