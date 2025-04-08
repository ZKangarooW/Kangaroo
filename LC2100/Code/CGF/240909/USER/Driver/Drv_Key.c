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
	/**************************************减键**************************************/
	if(KEY2 == 0)//按下按键
	{
		Key_Cnt1 += dT;//按下时间++
		Key_Flag1 = 1;//按键按下标志置一
	}
	if(Key_Flag1 == 1)//按键被按下
	{
		if(KEY2 == 1)//抬起按键
		{   
			if(Key_Cnt1 < 1.5)//小于1.5S是单击
			{
				if(CGF.Mode == 0)
                {
                    if(sys.SetMode_Option == 1)//设置速度
                    {
                        if(Speed.Unit)
                        {
                            Speed.Set -= 50;//离心率减50
                            if(Speed.Set < Xg_Min)//离心率小于于Xg_Min时
                                Speed.Set = Xg_Min;//离心率等于Xg_Min
                        }
                        else
                        {
                            Speed.Set -= 100;//速度减100
                            if(Speed.Set < Speed_Min)//速度小于Speed_Min时
                                Speed.Set = Speed_Min;//速度等于Speed_Min
                        }
                        Key_Status = 2;
                        Twinkle_Time = 6;//闪烁时间6S
                    }
                    else if(sys.SetMode_Option == 2)//设置时间
                    {
                        Time.Set -= 10;//时间减10S
                        if(Time.Set < Time_Min)//设置时间小于Time_Min
                            Time.Set = Time_Min;//设置时间等于Time_Min
                        Key_Status = 2;
                        Twinkle_Time = 6;//闪烁时间6S
                    }
                    else
                    {
                        Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
                    }
                }
                else
                {
//                    CGF.Mode --;
//                    if(CGF.Mode<1)
//                        CGF.Mode = 4;
                    Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
                }
			}	
			Key_Flag1 = 0;//按键事件结束，等待下一次按下
			Key_Cnt1 = 0;//按钮计数清零
		}
		if(Key_Cnt1 > 1.9 && Key_Cnt1 < 2.1)//按键时间大于1.9S小于2.1S表示长按
		{
            if(CGF.Mode == 0)
            {
                if(sys.SetMode_Option == 1)//设置速度
                {
                    if(Speed.Unit)
                    {
                        Speed.Set -= 100;//离心率减100
                        if(Speed.Set < Xg_Min)//离心率小于于Xg_Min时
                            Speed.Set = Xg_Min;//离心率等于Xg_Min
                    }
                    else
                    {
                        Speed.Set -= 100;//速度减100
                        if(Speed.Set < Speed_Min)//速度小于Speed_Min时
                            Speed.Set = Speed_Min;//速度等于Speed_Min
                    }
                    Key_Status = 2;
                    Twinkle_Time = 6;//闪烁时间6S
                }
                else if(sys.SetMode_Option == 2)//设置时间
                {
                    Time.Set -= 60;//时间减60S
                    if(Time.Set < Time_Min)//设置时间小于Time_Min
                        Time.Set = Time_Min;//设置时间等于Time_Min
                    Key_Status = 2;
                    Twinkle_Time = 6;//闪烁时间6S
                }
                else
                {
                    Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
                }
            }
            else
            {
//                CGF.Mode --;
//                if(CGF.Mode<1)
//                    CGF.Mode = 4;
                Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
            }
			Key_Flag1 = 0;//按键事件结束，等待下一次按下
			Key_Cnt1 = 1.75;//按钮计数清零
		}
	}

	/**************************************MENU键**************************************/
	if(KEY4 == 0)//按下按键
	{
		Key_Cnt2 += dT;//按下时间++
		Key_Flag2 = 1;//按键按下标志置一
	}
	if(Key_Flag2 == 1)//按键被按下
	{
		if(KEY4 == 1)//抬起按键
		{   
			if(Key_Cnt2 < 1.5)//小于1.5S是单击
			{
                if(CGF.Mode==0)
                {
                    if(sys.Run_Status)
                    {
                        Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
                    }
                    else
                    {
                        sys.SetMode_Option++;//设置模式++
                        if(sys.SetMode_Option > 2)//退出设置
                            sys.SetMode_Option = 0;//清零
                        Beep_Time = 0.1;//蜂鸣器响0.1S
                        Twinkle_Time = 6;//闪烁时间6S
                    }
                }
                else
                {
                    CGF.Mode++;
                    if(CGF.Mode>4)
                        CGF.Mode = 1;
                    if(CGF.Mode == 1)
						CGF.Option = 1;//记忆模式1
					else if(CGF.Mode == 2)
						CGF.Option = 5;//记忆模式5
					else if(CGF.Mode == 3)
						CGF.Option = 6;//记忆模式6
					else if(CGF.Mode == 4)
						CGF.Option = 7;//记忆模式7
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
                if(CGF.Mode == 0)
                {
                    CGF.Mode = 1;
                }
                else
                {
                    CGF.Mode = 0;
                }
                CGF.Option = 1;
				LongPress2 = 1;//长按标志置一
			}
		}
	}
	
	/**************************************Start键**************************************/
	if(KEY1 == 0)//按下按键
	{
		if(LongPress3 == 0)//没有长按过
		{
			Key_Cnt3 += dT;//按下时间++
			Key_Flag3 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag3 == 1)//按键被按下
	{
		if(KEY1 == 1)//抬起按键
		{   
			if(Key_Cnt3 < 1.5)/*单击*///小于1.5S是单击
			{
				if(HAL_GPIO_ReadPin(UC_IN_GPIO_Port,UC_IN_Pin)== 1)//电磁锁1闭合时
				{
					if(sys.Run_Status == 0)
					{
						Speed_Val.Integral = 25;//启动电 机系数
						SetOK_Flag = 1;//设定值
						sys.Run_Status = 1;
						sys.SetMode_Option = 0;
						Speed.ADDMode = 0;
						Beep_Time = 0.1;//蜂鸣器响0.1S
					}
					else
					{
						sys.Motor_Stop = 1;//检测电机
						Speed.ADDMode = 2;//进入减速模式下
						Beep_Time = 0.1;//蜂鸣器响0.1S
					}
				}
				else
				{
					Beep_Flash = 7;//蜂鸣器响7下
					sys.Lock_On = 1;//开盖图标闪烁标志位
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

	/**************************************加键**************************************/
	if(KEY3 == 0)//按下按键
	{
		Key_Cnt4 += dT;//按下时间++
		Key_Flag4 = 1;//按键按下标志置一
	}
	if(Key_Flag4 == 1)//按键被按下
	{
		if(KEY3 == 1)//抬起按键
		{   
			if(Key_Cnt4 < 1.5)//小于1.5S是单击
			{
                if(CGF.Mode == 0)
                {
                    if(sys.SetMode_Option == 1)//设置速度
                    {
                        if(Speed.Unit)
                        {
                            Speed.Set += 50;//离心率加50
                            if(Speed.Set > Xg_MAX)//离心率大于2100时
                                Speed.Set = Xg_MAX;//离心率等于2100
                        }
                        else
                        {
                            Speed.Set += 100;//速度加100
                            if(Speed.Set > Speed_MAX)//速度大于2500时
                                Speed.Set = Speed_MAX;//速度等于2500
                        }
                        Key_Status = 2;
                        Twinkle_Time = 6;//闪烁时间6S
                    }
                    else if(sys.SetMode_Option == 2)//设置时间
                    {
                        Time.Set += 10;//时间加10S
                        if(Time.Set > Time_MAX)//设置时间大于59分50秒时
                            Time.Set = Time_MAX;//设置时间等于59分50秒时
                        Key_Status = 2;
                        Twinkle_Time = 6;//闪烁时间6S
                    }
                    else
                    {
                        Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
                    }
                }
                else
                {
//                    CGF.Mode ++;
//                    if(CGF.Mode>4)
//                        CGF.Mode = 1;
                    Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
                }
			}
			Key_Flag4 = 0;//按键事件结束，等待下一次按下
			Key_Cnt4 = 0;//按钮计数清零		
		}
		if(Key_Cnt4 > 1.9 && Key_Cnt4 < 2.1)//按键时间大于1.9S小于2.1S表示长按
		{
            if(CGF.Mode == 0)
            {
                if(sys.SetMode_Option == 1)//设置速度
                {
                    if(Speed.Unit)
                    {
                        Speed.Set += 100;//离心率加100
                        if(Speed.Set > Xg_MAX)//离心率大于2100时
                            Speed.Set = Xg_MAX;//离心率等于2100
                    }
                    else
                    {
                        Speed.Set += 100;//速度加100
                        if(Speed.Set > Speed_MAX)//速度大于2500时
                            Speed.Set = Speed_MAX;//速度等于2500
                    }
                    Key_Status = 2;
                    Twinkle_Time = 6;//闪烁时间6S
                }
                else if(sys.SetMode_Option == 2)//设置时间
                {
                    Time.Set += 60;//时间加10S
                    if(Time.Set > Time_MAX)//设置时间大于59分50秒时
                        Time.Set = Time_MAX;//设置时间等于59分50秒时
                    Key_Status = 2;
                    Twinkle_Time = 6;//闪烁时间6S
                }
                else
                {
                    Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
                }
            }
            else
            {
//                CGF.Mode ++;
//                if(CGF.Mode>4)
//                    CGF.Mode = 1;
                Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
            }
			Key_Flag4 = 0;//按键事件结束，等待下一次按下
			Key_Cnt4 = 1.75;//按钮计数清零
		}
	}
    
	/**************************************OPEN键**************************************/
	if(KEY5 == 0)//按下按键
	{
		Key_Cnt5 += dT;//按下时间++
		Key_Flag5 = 1;//按键按下标志置一
	}
	if(Key_Flag5 == 1)//按键被按下
	{
		if(KEY5 == 1)//抬起按键
		{   
			if(Key_Cnt5 < 1.5)//小于1.5S是单击
			{
				if(sys.Run_Status)
				{
					Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
				}
				else
				{
					if(HAL_GPIO_ReadPin(UC_IN_GPIO_Port,UC_IN_Pin)== 1)//电磁锁1闭合时
					{
						Lock_Status = 1;//打开电磁锁1
						Beep_Time = 0.1;//蜂鸣器响0.1S
						sys.Run_Status = 0;//关闭系统
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
			Beep_Flash = 2;//无效按键动作，蜂鸣器“滴滴”
			Key_Flag5 = 0;//按键事件结束，等待下一次按下
			Key_Cnt5 = 1.5;//按钮计数清零
		}
	}
}

