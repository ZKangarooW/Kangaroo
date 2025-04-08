#include "Drv_KEY.h"

/**********全局变量**********/
float Key_Status;//在操作按键时

/**********局部变量声明******/
float Key_Cnt1,Key_Cnt2,Key_Cnt3,Key_Cnt4,Key_Cnt5;//按下时间
uint8_t Key_Flag1,Key_Flag2,Key_Flag3,Key_Flag4,Key_Flag5;//按键按下标志
uint8_t LongPress1,LongPress2,LongPress3,LongPress4,LongPress5;//按键长按标志

/*
*****************************************************************
 * 函数原型：void Check_Press(float dT)
 * 功    能：检测按键状态-1s
*****************************************************************
*/
void Check_Press(float dT)
{
    if(Key_Status)
        Key_Status -= dT;
}

/*
*****************************************************************
 * 函数原型：void Key_Scan(float dT)
 * 功    能：按键扫描
*****************************************************************
*/
void Key_Scan(float dT)
{
	/**************************************MENU键**************************************/
	if(!Key1)//按下按键
	{
		if(sys.Run_Status == 1)
			return;
		if(LongPress1 == 0)//没有长按过
		{
			Key_Cnt1 += dT;//按下时间++
			Key_Flag1 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag1)//按键被按下
	{
		if(Key1)//抬起按键
		{   
			if(Key_Cnt1 > 0.05f && Key_Cnt1 < 1.5)//按键时间大于0.05S小于1.5S是单击
			{
				sys.SetMode_Option++;
                if(PMode.Show_Circle)
                {
                    if(sys.SetMode_Option > 3)
                    {
                        sys.SetMode_Option = 0;
                    }
                    Twinkle_Time = 6.0f;
                    Key_Status = 0;
                    Beep_Time = 0.1;
                }
                else
                {
                    if(sys.SetMode_Option > 2)
                    {
                        sys.SetMode_Option = 0;
                    }
                    Twinkle_Time = 6.0f;
                    Key_Status = 0;
                    Beep_Time = 0.1;
                }
			}
			Key_Flag1 = 0;//按键事件结束，等待下一次按下
			LongPress1 = 0;//长按标志清零
			Key_Cnt1 = 0;//按钮计数清零
		}
		if(Key_Cnt1 > 1.5 && Key_Cnt1 < 3.0)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress1 == 0)//如果没有一直一直长按着
			{
				
				LongPress1 = 1;//长按标志置一
			}
		}
	}

	/**************************************加键**************************************/
	if(!Key2)//按下按键
	{
		if(sys.Run_Status == 1)
			return;
		Key_Cnt2 += dT;//按下时间++
		Key_Flag2 = 1;//按键按下标志置一
	}
	if(Key_Flag2 == 1)//按键被按下
	{
		if(Key2)//抬起按键
		{   
			if(Key_Cnt2 < 1.5)//小于1.5S是单击
			{
				if(sys.SetMode_Option == 1)
                {
                    Temp.Set++;
                    if(Temp.Set > Temp_MAX)
                    {
                        Temp.Set = Temp_MAX;
                    }
                }
                else if(sys.SetMode_Option == 2)
                {
                    if(Time.Set < 3600)
                        Time.Set += 5;
                    else
                        Time.Set += 60;
                    if(Time.Set > Time_MAX)
                    {
                        Time.Set = Time_MAX;
                    }
                }
                else if(sys.SetMode_Option == 3)
                {
                    PMode.Option ++;
                    if(PMode.Option > 9)
                    {
                        PMode.Option = 1;
                    }
                    Param_Read();
                }
                Key_Status = 2.0f;
                Twinkle_Time = 6.0f;
			}
			Key_Flag2 = 0;//按键事件结束，等待下一次按下
			Key_Cnt2 = 0;//按钮计数清零		
		}
		if(Key_Cnt2 > 1.9 && Key_Cnt2 < 2.1)//按键时间大于1.9S小于2.1S表示长按
		{
			if(sys.SetMode_Option == 1)
            {
                Temp.Set += 1;
                if(Temp.Set > Temp_MAX)
                {
                    Temp.Set = Temp_MAX;
                }
				if(Temp.Set % 10 == 0)
				{
					Key_Cnt2 = 1.8;//按钮计数清零
				}
				else
				{
					Key_Cnt2 = 1.88f;//按钮计数清零
				}
            }
            else if(sys.SetMode_Option == 2)
            {
                if(Time.Set < 3600)
                {
                    Time.Set += 5;
                    if(Time.Set>3600)
                        Time.Set = 3600;
					if(Time.Set % 60 == 0)
					{
						Key_Cnt2 = 1.84f;//按钮计数清零
					}
					else
					{
						Key_Cnt2 = 1.88f;//按钮计数清零
					}
                }
                else
				{
                    Time.Set += 300;
					if(Time.Set % 600 == 0)
					{
						Key_Cnt2 = 1.84f;//按钮计数清零
					}
					else
					{
						Key_Cnt2 = 1.88f;//按钮计数清零
					}
				}
                if(Time.Set > Time_MAX)
                {
                    Time.Set = Time_MAX;
                }
            }
            else if(sys.SetMode_Option == 3)
            {
                PMode.Option ++;
                if(PMode.Option > 9)
                {
                    PMode.Option = 1;
                }
				Key_Cnt2 = 1.66;//按钮计数清零
            }
            Key_Status = 2.0f;
            Twinkle_Time = 6.0f;
			Key_Flag2 = 0;//按键事件结束，等待下一次按下
		}
	}
	else
		Key_Cnt2 = 0;//按钮计数清零

	/**************************************减键**************************************/
	if(!Key3)//按下按键
	{
		if(sys.Run_Status == 1)
			return;
		Key_Cnt3 += dT;//按下时间++
		Key_Flag3 = 1;//按键按下标志置一
	}
	if(Key_Flag3 == 1)//按键被按下
	{
		if(Key3)//抬起按键
		{   
			if(Key_Cnt3 < 1.5)//按键时间大于0.05S小于1.5S是单击
			{
				if(sys.SetMode_Option == 1)
                {
                    Temp.Set--;
                    if(Temp.Set < Temp_MIN)
                    {
                        Temp.Set = Temp_MIN;
                    }
                }
                else if(sys.SetMode_Option == 2)
                {
                    if(Time.Set < 3600)
                        Time.Set -= 5;
                    else
                    {
                        Time.Set -= 60;
                        if(Time.Set < 3600)
                            Time.Set = 3595;
                    }
                    if(Time.Set < Time_MIN)
                    {
                        Time.Set = Time_MIN;
                    }
                }
                else if(sys.SetMode_Option == 3)
                {
                    PMode.Option --;
                    if(PMode.Option < 1)
                    {
                        PMode.Option = 9;
                    }
                    Param_Read();
                }
                Key_Status = 2.0f;
                Twinkle_Time = 6.0f;
			}
			Key_Flag3 = 0;//按键事件结束，等待下一次按下
			Key_Cnt3 = 0;//按钮计数清零		
		}
		else if(Key_Cnt3 > 1.9 && Key_Cnt3 < 2.1)//按键时间大于1.9S小于2.1S表示长按
		{
			if(sys.SetMode_Option == 1)
            {
                Temp.Set -= 1;
                if(Temp.Set < Temp_MIN)
                {
                    Temp.Set = Temp_MIN;
                }
				if(Temp.Set % 10 == 0)
				{
					Key_Cnt3 = 1.8;//按钮计数清零
				}
				else
				{
					Key_Cnt3 = 1.88f;//按钮计数清零
				}
            }
            else if(sys.SetMode_Option == 2)
            {
                if(Time.Set < 3600)
                {
                    Time.Set -= 5;
					if(Time.Set % 60 == 0)
					{
						Key_Cnt3 = 1.84f;//按钮计数清零
					}
					else
					{
						Key_Cnt3 = 1.88f;//按钮计数清零
					}
                }
                else
                {
                    Time.Set -= 300;
                    if(Time.Set < 3600)
                        Time.Set = 3540;
					if(Time.Set % 600 == 0)
					{
						Key_Cnt3 = 1.84f;//按钮计数清零
					}
					else
					{
						Key_Cnt3 = 1.88f;//按钮计数清零
					}
                }
                if(Time.Set < Time_MIN)
                {
                    Time.Set = Time_MIN;
                }
            }
            else if(sys.SetMode_Option == 3)
            {
                PMode.Option --;
                if(PMode.Option < 1)
                {
                    PMode.Option = 9;
                }
				Key_Cnt3 = 1.66;//按钮计数清零
            }
            Key_Status = 2.0f;
            Twinkle_Time = 6.0f;
			Key_Flag3 = 0;//按键事件结束，等待下一次按下
		}
	} 
	else
		Key_Cnt3 = 0;//按钮计数清零

	/**************************************Start键**************************************/
	if(!Key4)//按下按键
	{
		if(LongPress4 == 0)//没有长按过
		{
			Key_Cnt4 += dT;//按下时间++
			Key_Flag4 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag4)//按键被按下
	{
		if(Key4)//抬起按键
		{   
			if(Key_Cnt4 > 0.05f && Key_Cnt4 < 1.5)//按键时间大于0.05S小于1.5S是单击
			{
				if(sys.Run_Status != 1)
                {
                    sys.Run_Status = 1;//系统启动
					sys.SetMode_Option = 0;//清除设置
                    Temp_Val.Integral = 40;//开始就5分之一功率加热
                    SetOK_Flag = 1;//速度设置，时间设置
                    Twinkle_Time = Key_Status =0;//闪烁时间清零
					Temp.Last_Set = Temp.Set;//记录设定值
					Temp.Last_Mode = 0;//记录关闭时的显示模式
                    Beep_Time = 0.1;//蜂鸣器响0.1S
                }
                else
                {
                    sys.Run_Status = 2;//系统关闭
					Temp.Last_Mode = Temp.ADDMode;//记录关闭时的显示模式
					Temp.ADD_Wait_Count = 0;//清楚缓慢计时数
					SetOK_Flag = 1;//速度设置，时间设置
                    Beep_Time = 0.1;//蜂鸣器响0.1S
                    Temp.ADDMode = 0;//加热显示模式清零
                }
			}
			Key_Flag4 = 0;//按键事件结束，等待下一次按下
			LongPress4 = 0;//长按标志清零
			Key_Cnt4 = 0;//按钮计数清零
		}
		if(Key_Cnt4 > 1.5 && Key_Cnt4 < 3.0)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress4 == 0)//如果没有一直一直长按着
			{

				LongPress4 = 1;//长按标志置一
			}
		}
	}
	/**************************************P键******************************************/
	if(!Key5)//按下按键
	{
		if(sys.Run_Status == 1)
			return;
		if(LongPress5 == 0)//没有长按过
		{
			Key_Cnt5 += dT;//按下时间++
			Key_Flag5 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag5)//按键被按下
	{
		if(Key5)//抬起按键
		{   
			if(Key_Cnt5 > 0.05f && Key_Cnt5 < 1.5)//按键时间大于0.05S小于1.5S是单击
			{
				if(PMode.Show_Circle == 0)
				{
					PMode.Show_Circle = 1;//显示外框和P-几模式
					PMode.Option = 1;//记忆模式1
					Param_Read();//读取参数
					SetOK_Flag = 1;//设置参数
					sys.SetMode_Option = 3;//进入设置P值模式
					Twinkle_Time = 6;//闪烁时间6S
				}
				else
				{
					PMode.Show_Circle = 0;//不显示外框和P-几模式
					PMode.Option = 0;//记忆模式0
					Param_Read();//读取参数
					sys.SetMode_Option = 0;//模式清零
					SetOK_Flag = 1;//设置参数
				}
				Beep_Time = 0.1;//蜂鸣器响0.1S
            }
			Key_Flag5 = 0;//按键事件结束，等待下一次按下
			LongPress5 = 0;//长按标志清零
			Key_Cnt5 = 0;//按钮计数清零
		}
		if(Key_Cnt5 > 1.5 && Key_Cnt5 < 3.0)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress5 == 0)//如果没有一直一直长按着
			{
				
				LongPress5 = 1;//长按标志置一
			}
		}
	}
}
