#include "Drv_KEY.h"

/**********局部变量声明******/
float Key_Cnt1,Key_Cnt2,Key_Cnt3;//按下时间
uint8_t Key_Flag1,Key_Flag2,Key_Flag3;//按键按下标志
uint8_t LongPress1,LongPress2,LongPress3;//按键长按标志

uint8_t Lock_Switch; // 锁定开关

/**
 * @brief 按键扫描
 * 
 * @param dT 执行周期
 */
void Key_Scan(float dT)
{
	/************************************SYNC键**************************************/
	if(KEY1 == KEY_DOWN)//按下按键
	{
		if(LongPress1 == 0)//没有长按过
		{
			Key_Cnt1 += dT;//按下时间++
			Key_Flag1 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag1 == 1)//按键被按下
	{
		if(KEY1 == KEY_UP)//抬起按键
		{   
			if(Key_Cnt1 > 0.1 && Key_Cnt1 < 1.5)//小于1.5S是单击
			{
                if(Lock_Switch)
                {
                    Beep_Flash = 2;//“滴滴”两下用于误触
                }
                else
                {
                    for(uint8_t i = 0;i<4;i++)
                    {
                        Work_Num[i].Speed.Set= Param.Speed[i]= Work_Num[i].Speed.Ctrl= Work_Num[sys.New_Work].Speed.Set;
                        Work_Num[i].Time.Rel = Work_Num[i].Time.Set = Param.Time[i] = Work_Num[i].Time.Ctrl = Work_Num[sys.New_Work].Time.Set;
                        
                        if(Work_Num[i].Speed.ADDMode != 0)
                            Work_Num[i].Speed.ADDMode = 0;
                        
                        if(Work_Num[sys.New_Work].Run_Status)
                        {
                            Work_Num[i].Run_Status = 1;
                        }
                    }
                    sys.Sync = 1;
                    sys.SetMode_Option = 0;//退出设置模式
                    Twinkle_Time = 0;
                    Save_Param_En = 1;//保存
                    Beep_Time = 0.1f; // 蜂鸣器响0.1S
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
                Beep_Flash = 2;//“滴滴”两下用于误触
				LongPress1 = 1;//长按标志置一
			}
		}
	}
    
	/**************************************锁定键**************************************/
	if(KEY2 == KEY_DOWN)//按下按键
	{	
		if(LongPress2 == 0)//没有长按过
		{
			Key_Cnt2 += dT;//按下时间++
			Key_Flag2 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag2 == 1)//按键被按下
	{
		if(KEY2 == KEY_UP)//抬起按键
		{   
			if(Key_Cnt2 > 0.1 && Key_Cnt2 < 1.5)//小于1.5S是单击
			{
				if (Lock_Switch)
				{
					Lock_Switch = 0;
				}
				else
				{
					Lock_Switch = 1;
				}
				Beep_Time = 0.1f; // 蜂鸣器响0.1S
			}
			Key_Flag2 = 0;//按键事件结束，等待下一次按下
			LongPress2 = 0;//长按标志清零
			Key_Cnt2 = 0;//按钮计数清零		
		}
		if(Key_Cnt2 > 1.5 && Key_Cnt2 < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress2 == 0)//如果没有一直一直长按着
			{
				Beep_Flash = 2;//“滴滴”两下用于误触
				LongPress2 = 1;//长按标志置一
			}
		}
	}
	/**************************************start键**************************************/
	if(KEY3 == KEY_DOWN)//按下按键
	{	
		if(LongPress3 == 0)//没有长按过
		{
			Key_Cnt3 += dT;//按下时间++
			Key_Flag3 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag3 == 1)//按键被按下
	{
		if(KEY3 == KEY_UP)//抬起按键
		{   
			if(Key_Cnt3 > 0.1 && Key_Cnt3 < 1.5)//小于1.5S是单击
			{
                if(Lock_Switch)
                {
                    Beep_Flash = 2;//“滴滴”两下用于误触
                }
                else
                {
                    if(Work_Num[0].Run_Status != 1 && Work_Num[1].Run_Status != 1 
                    && Work_Num[2].Run_Status != 1 && Work_Num[3].Run_Status != 1
                        )//系统没启动的话
                    {
                        for(uint8_t i = 0;i<4;i++)
                        {
                            Work_Num[i].Run_Status = 1;//启动系统
                        }
                    }
                    else//系统启动的话
                    {
                        for(uint8_t i = 0;i<4;i++)
                        {
                            Work_Num[i].Speed.ADDMode = 2;
                            Work_Num[i].Motor_Stop = 1;//电机停止
                        }
                    }
                    Beep_Time = 0.1f;
                }
			}
			Key_Flag3 = 0;//按键事件结束，等待下一次按下
			LongPress3 = 0;//长按标志清零
			Key_Cnt3 = 0;//按钮计数清零		
		}
		if(Key_Cnt3 > 1.5 && Key_Cnt3 < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress3 == 0)//如果没有一直一直长按着
			{
                Beep_Flash = 2;//“滴滴”两下用于误触
				LongPress3 = 1;//长按标志置一
			}
		}
	}
}
