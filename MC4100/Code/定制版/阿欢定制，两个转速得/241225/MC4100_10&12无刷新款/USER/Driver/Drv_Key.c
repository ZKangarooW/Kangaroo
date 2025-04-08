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
	/**************************************vial键**************************************/
	if(Key3 == 0)//按下按键
	{
		Key_Cnt1 += dT;//按下时间++
		Key_Flag1 = 1;//按键按下标志置一
	}
	if(Key_Flag1 == 1)//按键被按下
	{
		if(Key3 == 1)//抬起按键
		{   
			if(Key_Cnt1 < 1.5)//小于1.5S是单击
			{
				if(HAL_GPIO_ReadPin(BREAKEZ_GPIO_Port,BREAKEZ_Pin)== 1)//电磁锁闭合时
				{
                    if(sys.Run_Status == 0)
					{
                        Set_Speed = 2000;
                        Set_Time = 10;
                        Speed_Val.SumError = 0x186A0;//启动电 机系数
                        SetOK_Flag = 1;//设定值
                        sys.Run_Status = 1;
                        sys.SetMode_Option = 0;
                        Speed_ADDMode = 0;
                        if(sys.Motor_Stop)//如果在降速的情况下
                            sys.Motor_Stop = 0;
                        Beep_Time = 0.1;//蜂鸣器响0.1S
                    }
                    else
                    {
                        Set_Time = 10;
                        SetOK_Flag = 1;//设定值
                        sys.SetMode_Option = 0;
                        Speed_ADDMode = 0;
                        if(sys.Motor_Stop)//如果在降速的情况下
                            sys.Motor_Stop = 0;
                        Beep_Time = 0.1;//蜂鸣器响0.1S
                    }
				}
                else
				{
					Beep_Flash = 7;
					sys.Lock_On = 1;
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

	/**************************************STOP键**************************************/
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
				if(sys.Run_Status == 1)
                {
                    sys.Motor_Stop = 1;//检测电机
                    Speed_ADDMode = 2;//进入减速模式下
                    Beep_Time = 0.1;//蜂鸣器响0.1S
                }
                else
                {
                    Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
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
				Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
				LongPress3 = 1;//长按标志置一
			}
		}
	}
	/**************************************bubble键**************************************/
	if(Key4 == 0)//按下按键
	{
		if(LongPress4 == 0)//没有长按过
		{
			Key_Cnt4 += dT;//按下时间++
			Key_Flag4 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag4 == 1)//按键被按下
	{
		if(Key4 == 1)//抬起按键
		{   
			if(Key_Cnt4 < 1.5)//小于1.5S是单击
			{
				if(HAL_GPIO_ReadPin(BREAKEZ_GPIO_Port,BREAKEZ_Pin)== 1)//电磁锁闭合时
				{
					if(sys.Run_Status == 0)
					{
                        Set_Speed = 2000;
                        Set_Time = 30;
						Speed_Val.SumError = 0x186A0;//启动电 机系数
						SetOK_Flag = 1;//设定值
						sys.Run_Status = 1;
						sys.SetMode_Option = 0;
						Speed_ADDMode = 0;
						if(sys.Motor_Stop)//如果在降速的情况下
							sys.Motor_Stop = 0;
                        Beep_Time = 0.1;//蜂鸣器响0.1S
					}
                    else
                    {
                        Set_Time = 30;
						SetOK_Flag = 1;//设定值
						sys.SetMode_Option = 0;
						Speed_ADDMode = 0;
						if(sys.Motor_Stop)//如果在降速的情况下
							sys.Motor_Stop = 0;
                        Beep_Time = 0.1;//蜂鸣器响0.1S
                    }
				}
				else
				{
					Beep_Flash = 7;
					sys.Lock_On = 1;
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
    
    /**************************************OPEN键**************************************/
	if(Key5 == 0)//按下按键
	{
		Key_Cnt2 += dT;//按下时间++
		Key_Flag2 = 1;//按键按下标志置一
	}
	if(Key_Flag2 == 1)//按键被按下
	{
		if(Key5 == 1)//抬起按键
		{   
			if(Key_Cnt2 < 1.5)//小于1.5S是单击
			{
                if(sys.Run_Status && sys.Motor_Stop==0)
                {
                    Beep_Flash = 2;
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
}
