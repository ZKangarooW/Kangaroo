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
        if(sys.Run_Status) return;
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
			if(Key_Cnt1 < 1.5f)//小于1.5S是单击
			{   
                sys.Run_Mode++;
                if(sys.Run_Mode>4)
                    sys.Run_Mode = 0;
                if(sys.Run_Mode == 0)
                    PMode.Option = 0;//记忆模式0
                else if(sys.Run_Mode == 1)
                    PMode.Option = 1;//记忆模式1
                else if(sys.Run_Mode == 2)
                    PMode.Option = 5;//记忆模式5
                else if(sys.Run_Mode == 3)
                    PMode.Option = 6;//记忆模式6
                else if(sys.Run_Mode == 4)
                    PMode.Option = 7;//记忆模式7
                Speed.Unit = 0;//转成速度模式
                Param_Read();//读取参数
                SetOK_Flag = 1;//设置参数
                sys.CGF_Step = 0;//CGF步骤清零
                sys.SetMode_Option = 0;//不进入设定模式
                Beep_Time = 0.1f;//蜂鸣器响0.1S
			}
			Key_Flag1 = 0;//按键事件结束，等待下一次按下
			LongPress1 = 0;//长按标志清零
			Key_Cnt1 = 0;//按钮计数清零
		}
		if(Key_Cnt1 > 1.9f && Key_Cnt1 < 2.1f)//按键时间大于1.9S小于2.1S表示长按
		{
			if(LongPress1 == 0)//如果没有一直一直长按着
			{
				
				LongPress1 = 1;//长按标志置一
			}
		}
	}
	/**************************************减键**************************************/
	if(HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_Pin )== 0)//按下按键
	{
		Key_Cnt2 += dT;//按下时间++
		Key_Flag2 = 1;//按键按下标志置一
	}
	if(Key_Flag2 == 1)//按键被按下
	{
		if(HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_Pin) == 1)//抬起按键
		{   
			if(Key_Cnt2 < 1.5f)//小于1.5S是单击
			{
				if(sys.SetMode_Option == 1)//设置时间
				{
					if(Time.Set < 3599)//如果设定时间小于59.59分钟时
						Time.Set -= 10;//时间减10S
					else
						Time.Set += 60;//时间减60S
					if(Time.Set < 30)//设置时间小于30S时
						Time.Set = 30;//设置时间等于30S
				}
				else if(sys.SetMode_Option == 2)//设置速度
				{
					if(Speed.Unit)
					{
						Speed.Set -= 100;//离心率加100
						if(Speed.Set < 100)//速度小于100时
							Speed.Set = 100;//速度小于100时
					}
					else
					{
						Speed.Set -= 100;//速度减100
						if(Speed.Set < 500)//速度小于500时
							Speed.Set = 500;//速度等于500
					}
				}
				else if(sys.SetMode_Option == 3)//设置温度
				{
					SafeTemp.Set -= 10;//温度减1度
					if(SafeTemp.Set < (SafeTemp.Rel+50))//设定安全温度大于实际安全温度+5度时
						SafeTemp.Set = SafeTemp.Rel+50;//设定安全温度等于实际安全温度+5度
                }
                Key_Status = 2.0f;//设置时2S不闪烁
                Twinkle_Time = 6.0f;//闪烁时间6S
            }
			Key_Flag2 = 0;//按键事件结束，等待下一次按下
			Key_Cnt2 = 0;//按钮计数清零		
		}
		if(Key_Cnt2 > 1.9f && Key_Cnt2 < 2.1f)//按键时间大于1.9S小于2.1S表示长按
		{
			if(sys.SetMode_Option == 1)//设置时间
            {
                if(Time.Set < 3599)//如果设定时间小于59.59分钟时
                    Time.Set -= 10;//时间减10S
                else
                    Time.Set += 60;//时间减60S
                if(Time.Set < 30)//设置时间小于30S时
                    Time.Set = 30;//设置时间等于30S
            }
            else if(sys.SetMode_Option == 2)//设置速度
            {
                if(Speed.Unit)
                {
                    Speed.Set -= 100;//离心率加100
                    if(Speed.Set < 100)//速度小于100时
                        Speed.Set = 100;//速度小于100时
                }
                else
                {
                    Speed.Set -= 100;//速度减100
                    if(Speed.Set < 500)//速度小于500时
                        Speed.Set = 500;//速度等于500
                }
            }
            else if(sys.SetMode_Option == 3)//设置温度
            {
                SafeTemp.Set -= 10;//温度减1度
                if(SafeTemp.Set < (SafeTemp.Rel+50))//设定安全温度大于实际安全温度+5度时
                    SafeTemp.Set = SafeTemp.Rel+50;//设定安全温度等于实际安全温度+5度
            }
			Key_Status = 2.0f;//设置时2S不闪烁
            Twinkle_Time = 6.0f;//闪烁时间6S
			Key_Flag2 = 0;//按键事件结束，等待下一次按下
			Key_Cnt2 = 1.85f;//按钮计数清零
		}
	}
	ROW1_H;
	ROW2_L;
	ROW3_H;
	/**************************************MENU键**************************************/
	if(HAL_GPIO_ReadPin(COL1_GPIO_Port,COL1_Pin) == 0)//按下按键
	{
        if(sys.Run_Mode || sys.Run_Status)
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
				sys.SetMode_Option++;//设置模式++
                if(sys.SetMode_Option > 3)//退出设置
                    sys.SetMode_Option = 0;//清零
                Beep_Time = 0.1;//蜂鸣器响0.1S
				Twinkle_Time = 6;//闪烁时间6S
			}
			Key_Flag3 = 0;//按键事件结束，等待下一次按下
			LongPress3 = 0;//长按标志清零
			Key_Cnt3 = 0;//按钮计数清零		
		}
		if(Key_Cnt3 > 1.9f && Key_Cnt3 < 2.1f)//按键时间大于1.9S小于2.1S表示长按
		{
			if(LongPress3 == 0)/*长按*///如果没有一直一直长按着
			{
				if(Speed.Unit)//假如在离心力的模式下
				{
					Speed.Unit = 0;//显示速度单位
					Param_Read();
				}	
				else
				{
					Speed.Unit = 1;//显示离心力单位
					Param_Read();
				}
                sys.SetMode_Option = 0;
				Beep_Time = 0.1;//蜂鸣器响0.1S
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
						Speed_Val.Integral = 15;
						SetOK_Flag = 1;//设定值
						sys.Run_Status = 1;
						sys.SetMode_Option = 0;
						Speed.ADDMode = 0;//速度显示模式清零
					}
					else
					{
						sys.Motor_Stop = 1;//检测电机
						Speed.ADDMode = 2;//进入减速模式下
					}
				}
				else
				{
					Beep_Flash = 7;//蜂鸣器响7下
					sys.Lock_On = 1;//开盖图标闪烁
				}
				Beep_Time = 0.1f;//蜂鸣器响0.1S
			}
			Key_Flag4 = 0;//按键事件结束，等待下一次按下
			LongPress4 = 0;//长按标志清零
			Key_Cnt4 = 0;//按钮计数清零		
		}
		if(Key_Cnt4 > 1.9f && Key_Cnt4 < 2.1f)//按键时间大于1.9S小于2.1S表示长按
		{
			if(LongPress4 == 0)//如果没有一直一直长按着
			{
               
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
		Key_Cnt5 += dT;//按下时间++
		Key_Flag5 = 1;//按键按下标志置一
	}
	if(Key_Flag5 == 1)//按键被按下
	{
		if(HAL_GPIO_ReadPin(COL1_GPIO_Port,COL1_Pin) == 1)//抬起按键
		{   
			if(Key_Cnt5 < 1.5)//小于1.5S是单击
			{
                if(sys.SetMode_Option == 1)//设置时间
				{
					if(Time.Set < 3599)//如果设定时间小于59.59分钟时
						Time.Set += 10;//时间加10S
					else
						Time.Set += 60;//时间加60S
					if(Time.Set > 3590)//设置时间大于59分50秒时
						Time.Set = 3590;//设置时间等于59分50秒时
				}
				else if(sys.SetMode_Option == 2)//设置速度
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
				}
				else if(sys.SetMode_Option == 3)//设置温度
				{
					SafeTemp.Set += 10;//温度加1度
					if(SafeTemp.Set > 500)//设定安全温度大于50度时
						SafeTemp.Set = 500;//设定安全温度等于50度
				}
                Key_Status = 2.0f;//设置时2S不闪烁
                Twinkle_Time = 6.0f;//闪烁时间6S
			}
			Key_Flag5 = 0;//按键事件结束，等待下一次按下
			Key_Cnt5 = 0;//按钮计数清零		
		}
		if(Key_Cnt5 > 1.9 && Key_Cnt5 < 2.1)//按键时间大于1.9S小于2.1S表示长按
		{
            if(sys.SetMode_Option == 1)//设置时间
            {
                if(Time.Set < 3599)//如果设定时间小于59.59分钟时
                    Time.Set += 10;//时间加10S
                else
                    Time.Set += 60;//时间加60S
                if(Time.Set > 3590)//设置时间大于59分50秒时
                    Time.Set = 3590;//设置时间等于59分50秒时
            }
            else if(sys.SetMode_Option == 2)//设置速度
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
            }
            else if(sys.SetMode_Option == 3)//设置温度
            {
                SafeTemp.Set += 10;//温度加1度
                if(SafeTemp.Set > 500)//设定安全温度大于50度时
                    SafeTemp.Set = 500;//设定安全温度等于50度
            }
            Key_Status = 2.0f;//设置时2S不闪烁
            Twinkle_Time = 6.0f;//闪烁时间6S    
			Key_Flag5 = 0;//按键事件结束，等待下一次按下
			Key_Cnt5 = 1.85f;//按钮计数清零
		}
	}
	/**************************************OPEN键**************************************/
	if(HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_Pin )== 0)//按下按键
	{
        if(sys.Run_Status) return;
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
                if((HAL_GPIO_ReadPin(UC_IN1_GPIO_Port,UC_IN1_Pin)== 1)||(HAL_GPIO_ReadPin(UC_IN2_GPIO_Port,UC_IN2_Pin)== 1))//电磁锁1闭合时
                    Beep_Time = 0.1;//蜂鸣器响0.1S
			}
			Key_Flag6 = 0;//按键事件结束，等待下一次按下
			LongPress6 = 0;//长按标志清零
			Key_Cnt6 = 0;//按钮计数清零		
		}
		if(Key_Cnt6 > 1.9f && Key_Cnt6 < 2.1f)//按键时间大于1.9S小于2.1S表示长按
		{
			if(LongPress6 == 0)//如果没有一直一直长按着
			{
                
				LongPress6 = 1;//长按标志置一
			}
		}
	}
}
