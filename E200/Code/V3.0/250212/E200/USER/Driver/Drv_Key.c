#include "Drv_Key.h"

/**********全局变量声明******/
uint8_t Key_Status;//按键按下标志
uint8_t LongPress;//检测上下长按

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
	/**************************************Temp_Set键**************************************/
	if(KEY1 == 0)//按下按键
	{
		if(LongPress1 == 0)//没有长按过
		{
			Key_Cnt1 += dT;//按下时间++
			Key_Flag1 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag1 == 1)//按键被按下
	{
		if(KEY1 == 1)//抬起按键
		{   
			if(Key_Cnt1 < 1.5)//小于1.5S是单击
			{
				if(sys.Calibration)//如果在校准界面时
				{
					if(Cool_Temp.ADDMode)
					{
						sys.Calibration_Step++;//校准步骤加加
						if(sys.Calibration_Step>1)//如果校准不走大于1
						{
							sys.Calibration = 0;//关闭校准
							sys.Calibration_Step = 0;//步骤清零
							sys.TempOption_Mun = 0;//设置是位数清零
							Calibration(sys.Calibration_Temp1,sys.Calibration_Temp2);//温度校准计算
							sys.Calibration_Temp1 = 260;
							sys.Calibration_Temp2 = 400;
							sys.SetMode_Option = 0;
						}
						Cool_Temp.ADDMode = 0;//温度显示处理为0
					}
				}
				else
				{
					sys.SetMode_Option++;
					if(sys.SetMode_Option > 2)
						sys.SetMode_Option = 1;
					sys.TempOption_Mun = 0;
                    Heat_Temp.ADDMode = 0;//温度处理清零
                    Cool_Temp.ADDMode = 0;//温度处理清零
                    if(Time.Count_Start)//如果正在计时
                    {
                        Time.Count_Start = 0;//关闭正计时
                        Time.Count_Time = 0;//清除正计时时间
                        Time.TimeDisplay_Flag = 0;//显示倒计时
                    }
                    else if(Time.CountDown_Start)//如果正在倒计时
                    {
                        Time.TimeDisplay_Flag = 0;//显示倒计时
                        Time.CountDown_Start = 0;//关闭倒计时
                        Time.Rel_Time = Time.Set_Time;//赋值
                    }
                    else
                    {
                        Time.TimeDisplay_Flag = 0;//显示倒计时
                        Time.CountDown_Start = 0;
                        Time.Count_Time = 0;//清除正计时时间
                        Time.Rel_Time = Time.Set_Time;//赋值
                    }
					Twinkle_Time = 5;//闪烁5S
				}
			}
			Key_Flag1 = 0;//按键事件结束，等待下一次按下
			LongPress1 = 0;//长按标志清零
			Key_Cnt1 = 0;//按钮计数清零
		}
		if(Key_Cnt1 > 1.5 && Key_Cnt1 < 3.1)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress1 == 0)//如果没有一直一直长按着
			{
				/*校准温度*/
				if(sys.Calibration == 0)//没有在校准界面时
				{
					sys.Calibration = 1;//进入校准界面
					sys.Calibration_Step = 0;//校准步骤清零
					sys.Calibration_Temp1 = 260;//设置温度一为26度
					sys.Calibration_Temp2 = 400;//设置温度二为40度
					sys.SetMode_Option = 4;//设置模式为四
					sys.TempOption_Mun = 2;//温度位数为最后一位
					Heat_Temp.ADDMode = 0;//温度显示处理为0
					Cool_Temp.ADDMode = 0;//温度显示处理为0
				}
				LongPress1 = 1;//长按标志置一
			}
		}
	}
	/**************************************Time_Set键**************************************/
	if(KEY2 == 0)//按下按键
	{
		if(sys.Calibration)
			return;
		if(LongPress2 == 0)//没有长按过
		{
			Key_Cnt2 += dT;//按下时间++
			Key_Flag2 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag2 == 1)//按键被按下
	{
		if(KEY2 == 1)//抬起按键
		{   
			if(Key_Cnt2 < 1.5)//小于1.5S是单击
			{
				if(sys.SetMode_Option == 0)
				{
					sys.SetMode_Option = 3;//设置时间
					Twinkle_Time = 5;//闪烁5S
				}
			}
			Key_Flag2 = 0;//按键事件结束，等待下一次按下
			LongPress2 = 0;//长按标志清零
			Key_Cnt2 = 0;//按钮计数清零
		}
		if(Key_Cnt2 > 1.5 && Key_Cnt2 < 3.1)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress2 == 0)//如果没有一直一直长按着
			{

				LongPress2 = 1;//长按标志置一
			}
		}
	}
	
	/**************************************加键**************************************/
	if(KEY3 == 0)//按下按键
	{
		if(!sys.SetMode_Option)
			return;
		Key_Cnt3 += dT;//按下时间++
		Key_Flag3 = 1;//按键按下标志置一
	}
	if(Key_Flag3 == 1)//按键被按下
	{
		if(KEY3 == 1)//抬起按键
		{   
			if(Key_Cnt3 < 1.5)//小于1.5S是单击
			{
				if(sys.SetMode_Option == 1)//设置加热区域时
				{
					if(sys.TempOption_Mun == 0)
						Heat_Temp.Set_Temp += 10;
					else if(sys.TempOption_Mun == 1)
						Heat_Temp.Set_Temp += 100;
					else if(sys.TempOption_Mun == 2)
						Heat_Temp.Set_Temp += 1;
					if(Heat_Temp.Set_Temp > 600)
						Heat_Temp.Set_Temp = 600;
					Twinkle_Time = 5;//闪烁5S
					Key_Status = 2.0f;//操作时常亮1S
				}
				else if(sys.SetMode_Option == 2)//设置制冷区域时
				{
					if(sys.TempOption_Mun == 0)
						Cool_Temp.Set_Temp += 10;
					else if(sys.TempOption_Mun == 1)
						Cool_Temp.Set_Temp += 100;
					else if(sys.TempOption_Mun == 2)
						Cool_Temp.Set_Temp += 1;
					if(Cool_Temp.Set_Temp > 500)
						Cool_Temp.Set_Temp = 500;
					Twinkle_Time = 5;//闪烁5S
					Key_Status = 2.0f;//操作时常亮1S
				}
				else if(sys.SetMode_Option == 3)//设置时间时
				{
					if(sys.TimeOption_Mun == 0)
						Time.Set_Time += 60;
					else if(sys.TimeOption_Mun == 1)
						Time.Set_Time += 600;
					else if(sys.TimeOption_Mun == 2)
						Time.Set_Time += 1;
					else if(sys.TimeOption_Mun == 3)
						Time.Set_Time += 10;
					if(Time.Set_Time > 5999)//如果大于99分59秒
						Time.Set_Time = 5999;
					Twinkle_Time = 5;//闪烁5S
					Key_Status = 2.0f;//操作时常亮1S
				}
				else if(sys.SetMode_Option == 4)//设置校准温度
				{
					if(sys.Calibration_Step == 0)
					{
						if(sys.TempOption_Mun == 2)
							sys.Calibration_Temp1 += 1;
						if(sys.Calibration_Temp1 > 800)
							sys.Calibration_Temp1 = 800;
					}
					if(sys.Calibration_Step == 1)
					{
						if(sys.TempOption_Mun == 2)
							sys.Calibration_Temp2 += 1;
						if(sys.Calibration_Temp2 > 800)
							sys.Calibration_Temp2 = 800;
					}
					Key_Status = 2.0f;//操作时常亮1S
				}
			}
			Key_Flag3 = 0;//按键事件结束，等待下一次按下
			Key_Cnt3 = 0;//按钮计数清零		
			LongPress = 0;//长按清零
		}
		if(Key_Cnt3 > 2.0 && Key_Cnt3 < 2.5)//按键时间大于2.0小于2.5表示长按
		{	
			if(sys.SetMode_Option > 0 && sys.SetMode_Option <= 2)//设置温度时
			{
				sys.TempOption_Mun++;//温度位数++
				if(sys.TempOption_Mun > 2)
					sys.TempOption_Mun = 0;
				LongPress = 1;//表示长按加减
				Twinkle_Time = 5;//闪烁5S
			}
			if(sys.SetMode_Option == 3)//设置时间时
			{
				sys.TimeOption_Mun++;//时间位数++
				if(sys.TimeOption_Mun > 3)
					sys.TimeOption_Mun = 0;
				LongPress = 1;//表示长按加减
				Twinkle_Time = 5;//闪烁5S
			}
			Key_Flag3 = 0;//按键事件结束，等待下一次按下
			Key_Cnt3 = 1.5;//按钮计数清零
		}
	}
	
	/**************************************减键**************************************/
	if(KEY4 == 0)//按下按键
	{
		if(!sys.SetMode_Option)
			return;
		Key_Cnt4 += dT;//按下时间++
		Key_Flag4 = 1;//按键按下标志置一
	}
	if(Key_Flag4 == 1)//按键被按下
	{
		if(KEY4 == 1)//抬起按键
		{   
			if(Key_Cnt4 < 1.5)//小于1.5S是单击
			{
				if(sys.SetMode_Option == 1)//设置加热区域时
				{
					if(sys.TempOption_Mun == 0)
						Heat_Temp.Set_Temp -= 10;
					else if(sys.TempOption_Mun == 1)
						Heat_Temp.Set_Temp -= 100;
					else if(sys.TempOption_Mun == 2)
						Heat_Temp.Set_Temp -= 1;
					if(Heat_Temp.Set_Temp < 300)
						Heat_Temp.Set_Temp = 300;
					Twinkle_Time = 5;//闪烁5S
					Key_Status = 2.0f;//操作时常亮1S
				}
				else if(sys.SetMode_Option == 2)//设置制冷区域时
				{
					if(sys.TempOption_Mun == 0)
						Cool_Temp.Set_Temp -= 10;
					else if(sys.TempOption_Mun == 1)
						Cool_Temp.Set_Temp -= 100;
					else if(sys.TempOption_Mun == 2)
						Cool_Temp.Set_Temp -= 1;
					if(Cool_Temp.Set_Temp < 200)
						Cool_Temp.Set_Temp = 200;
					Twinkle_Time = 5;//闪烁5S
					Key_Status = 2.0f;//操作时常亮1S
				}
				else if(sys.SetMode_Option == 3)//设置时间时
				{
					if(sys.TimeOption_Mun == 0)
						Time.Set_Time -= 60;
					else if(sys.TimeOption_Mun == 1)
						Time.Set_Time -= 600;
					else if(sys.TimeOption_Mun == 2)
						Time.Set_Time -= 1;
					else if(sys.TimeOption_Mun == 3)
						Time.Set_Time -= 10;
					if(Time.Set_Time < 1)//如果小于1秒
						Time.Set_Time = 1;
					Twinkle_Time = 5;//闪烁5S
					Key_Status = 2.0f;//操作时常亮1S
				}
				else if(sys.SetMode_Option == 4)//设置校准温度
				{
					if(sys.Calibration_Step == 0)
					{
						if(sys.TempOption_Mun == 2)
							sys.Calibration_Temp1 -= 1;
						if(sys.Calibration_Temp1 < 200)
							sys.Calibration_Temp1 = 200;
					}
					if(sys.Calibration_Step == 1)
					{
						if(sys.TempOption_Mun == 2)
							sys.Calibration_Temp2 -= 1;
						if(sys.Calibration_Temp2 < 200)
							sys.Calibration_Temp2 = 200;
					}
					Key_Status = 2.0f;//操作时常亮1S
				}
			}
			Key_Flag4 = 0;//按键事件结束，等待下一次按下
			Key_Cnt4 = 0;//按钮计数清零		
			LongPress = 0;//长按清零
		}
		if(Key_Cnt4 > 2.0 && Key_Cnt4 < 2.5)//按键时间大于2.0S小于2.5表示长按
		{	
			if(sys.SetMode_Option > 0 && sys.SetMode_Option <= 2)//设置温度时
			{
				if(sys.TempOption_Mun)
					sys.TempOption_Mun--;//温度位数--
				else
					sys.TempOption_Mun = 2;
				LongPress = 1;//表示长按加减
				Twinkle_Time = 5;//闪烁5S
			}
			if(sys.SetMode_Option == 3)//设置时间时
			{
				if(sys.TimeOption_Mun)
					sys.TimeOption_Mun--;//温度位数--
				else
					sys.TimeOption_Mun = 3;
				LongPress = 1;//表示长按加减
				Twinkle_Time = 5;//闪烁5S
			}
			Key_Flag4 = 0;//按键事件结束，等待下一次按下
			Key_Cnt4 = 1.5;//按钮计数清零
		}
	}
	
	/**************************************Count键**************************************/
	if(KEY5 == 0)//按下按键
	{
		if(Heat_Temp.ADDMode == 0 || Cool_Temp.ADDMode == 0 || sys.Calibration == 1 || sys.SetMode_Option)
			return;
		if(LongPress5 == 0)//没有长按过
		{
			Key_Cnt5 += dT;//按下时间++
			Key_Flag5 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag5 == 1)//按键被按下
	{
		if(KEY5 == 1)//抬起按键
		{   
			if(Key_Cnt5 < 1.5)/*单击*///小于1.5S是单击
			{
				if(Time.CountDown_Start)//如果倒计时也在启动
				{
					Time.CountDown_Start = 0;//关闭倒计时
					Time.Rel_Time = Time.Set_Time;//赋值
					Time.TimeDisplay_Flag = 0;//显示正计时
				}
				else if(Time.Count_Start)//如果正计时启动
				{
					Time.Count_Start = 0;//关闭正计时
					Time.Count_Time = 0;//清除正计时时间
					Time.TimeDisplay_Flag = 0;//显示倒计时
				}
				else//如果正计时没有启动
				{
					Time.TimeDisplay_Flag = 1;//显示正计时
					Time.Count_Start = 1;//打开正计时
					Beep_Time = 0.2;//蜂鸣器响0.2S
				}
				Twinkle_Time = 0;//闪烁5S
                Key_Status = 0.0f;//操作时常亮1S
                SetOK_Flag = 1;
			}
			Key_Flag5 = 0;//按键事件结束，等待下一次按下
			LongPress5 = 0;//长按标志清零
			Key_Cnt5 = 0;//按钮计数清零		
		}
		if(Key_Cnt5 > 1.5 && Key_Cnt5 < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress5 == 0)/*长按*///如果没有一直一直长按着
			{
				Beep_Time = 0.1;//蜂鸣器响0.1S
				LongPress5 = 1;//长按标志置一
			}
		}
	}
	
	/**************************************CountDown键**************************************/
	if(KEY6 == 0)//按下按键
	{
		if(Heat_Temp.ADDMode == 0 || Cool_Temp.ADDMode == 0 || sys.Calibration == 1 || sys.SetMode_Option)
			return;
		if(LongPress6 == 0)//没有长按过
		{
			Key_Cnt6 += dT;//按下时间++
			Key_Flag6 = 1;//按键按下标志置一
		}
	}
	if(Key_Flag6 == 1)//按键被按下
	{
		if(KEY6 == 1)//抬起按键
		{   
			if(Key_Cnt6 < 1.5)/*单击*///小于1.5S是单击
			{
				if(Time.Count_Start)//如果正在计时
				{
					Time.Count_Start = 0;//关闭正计时
					Time.Count_Time = 0;//清除正计时时间
					Time.TimeDisplay_Flag = 0;//显示倒计时
				}
				else if(Time.CountDown_Start)//如果正在倒计时
				{
					Time.TimeDisplay_Flag = 0;//显示倒计时
					Time.CountDown_Start = 0;//关闭倒计时
					Time.Rel_Time = Time.Set_Time;//赋值
				}
				else
				{
					Time.TimeDisplay_Flag = 0;//显示倒计时
					Time.CountDown_Start = 1;
					Beep_Time = 0.2;//蜂鸣器响0.2S
				}
                Twinkle_Time = 0;//闪烁5S
                Key_Status = 0.0f;//操作时常亮1S
                SetOK_Flag = 1;
                sys.SetMode_Option = 0;//模式选择清零
			}
			Key_Flag6 = 0;//按键事件结束，等待下一次按下
			LongPress6 = 0;//长按标志清零
			Key_Cnt6 = 0;//按钮计数清零				
		}
		if(Key_Cnt6 > 1.5 && Key_Cnt6 < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress6 == 0)/*长按*///如果没有一直一直长按着
			{
				Beep_Time = 0.1;//蜂鸣器响0.1S
				LongPress6 = 1;//长按标志置一
			}
		}
	}
}
