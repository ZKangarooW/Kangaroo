#include "Drv_KEY.h"

/**********全局变量**********/
uint8_t Key_Status;//在操作按键时

/**********局部变量声明******/
float Key_Cnt1,Key_Cnt2,Key_Cnt3,Key_Cnt4,Key_Cnt5;//按下时间
uint8_t Key_Flag1,Key_Flag2,Key_Flag3,Key_Flag4,Key_Flag5;//按键按下标志
uint8_t LongPress1,LongPress2,LongPress3,LongPress4,LongPress5;//按键长按标志

/*
*****************************************************************
 * 函数原型：void Check_Key(void)
 * 功    能：检测按键状态-1s
*****************************************************************
*/
void Check_Key(void)
{
    if(Key_Status)
        Key_Status--;
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
				if(sys.Run_Status)
				{
					Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
				}
				else
				{
					if(PMode_Mode == 0)
					{
						if(PMode_Status == 1)
						{
							sys.SetMode_Option++;//设置选项切换
							if(sys.SetMode_Option > 3)//在温度和时间来换选择
							{
								sys.SetMode_Option = 0;//不进行设置    
							}
						}
						else
						{
							sys.SetMode_Option++;//设置选项切换
							if(sys.SetMode_Option == 1)//在温度和时间来换选择
							{
								sys.SetMode_Option = 2;//不进行设置    
							}
							if(sys.SetMode_Option > 3)//在温度和时间来换选择
							{
								sys.SetMode_Option = 0;//不进行设置    
							}
						}
                        Twinkle_Time = 6000;//闪烁时间6S
                        Beep_Time = 0.1;//蜂鸣器响0.1S
					}
					else
					{
						sys.SetP_Mode_Option++;
						if(sys.SetP_Mode_Option > 2)//在P1和P1来切换选择
						{
							sys.SetP_Mode_Option = 0;//不进行设置   
							PMode_Option = PMode_P1;
							Flash_Read((uint8_t *)(&Param),sizeof(Param));
							Set_Time=Param.P_Param[PMode_Option][1];//开机设置设定时间为20min
							Ctrl_Time=Param.P_Param[PMode_Option][1];//开机设置实际时间为20min
							Set_Temp=Param.P_Param[PMode_Option][0];//开机设置设定温度37℃
							Ctrl_Temp = Set_Temp;		
							if(Set_Time > 0)
								Time_State = 0;
							else
								Time_State = 1;				
						}
						if(sys.SetP_Mode_Option == 1)//设置P1
						{
							PMode_Option = PMode_P1;
							Flash_Read((uint8_t *)(&Param),sizeof(Param));
							Set_Time=Param.P_Param[PMode_Option][1];//开机设置设定时间为20min
							Ctrl_Time=Param.P_Param[PMode_Option][1];//开机设置实际时间为20min
							Set_Temp=Param.P_Param[PMode_Option][0];//开机设置设定温度37℃
							Ctrl_Temp = Set_Temp;
							if(Set_Time > 0)
								Time_State = 0;
							else
								Time_State = 1;
						}
						else if(sys.SetP_Mode_Option == 2)//设置P2
						{
							PMode_Option = PMode_P2;
							Flash_Read((uint8_t *)(&Param),sizeof(Param));
							Set_Time=Param.P_Param[PMode_Option][1];//开机设置设定时间为20min
							Ctrl_Time=Param.P_Param[PMode_Option][1];//开机设置实际时间为20min
							Set_Temp=Param.P_Param[PMode_Option][0];//开机设置设定温度37℃
							Ctrl_Temp = Set_Temp;
							if(Set_Time > 0)
								Time_State = 0;
							else
								Time_State = 1;
						}
                        Twinkle_Time = 6000;//闪烁时间6S
                        Beep_Time = 0.1;//蜂鸣器响0.1S
					}
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
				Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
				LongPress1 = 1;//长按标志置一
			}
		}
	}

	/**************************************加键**************************************/
	if(!Key2)//按下按键
	{
		Key_Cnt2 += dT;//按下时间++
		Key_Flag2 = 1;//按键按下标志置一
	}
	if(Key_Flag2 == 1)//按键被按下
	{
		if(Key2)//抬起按键
		{   
			if(Key_Cnt2 > 0.05f && Key_Cnt2 < 1.5)//按键时间大于0.05S小于1.5S是单击
			{
				if(sys.Run_Status)
				{
					Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
				}
				else
				{
					if(sys.SetMode_Option == 2)//在设置温度选项
					{
						Set_Temp++;//温度++；
						if(Set_Temp > 1000)//最高设定温度在100℃
							Set_Temp = 1000;
                        Key_Status = 1;//按键操作时不闪烁，2s后闪烁
                        Twinkle_Time = 6000;//闪烁时间6S
					}
					else if(sys.SetMode_Option == 3)//在设置时间选项
					{
						if(Time_Unit == 0)//在秒单位模式下
						{
							Set_Time += 5;//时间加5s
							Time_State = 0;//时间退出显示“----”
						}
						else//在分单位模式下
							Set_Time += 60;//时间加60s
						if(Set_Time > 86399)//最高可定时23.99小时
							Set_Time = 86399;
                        Key_Status = 1;//按键操作时不闪烁，2s后闪烁
                        Twinkle_Time = 6000;//闪烁时间6S
					}
					else if(sys.SetMode_Option == 1)
					{
						PMode_Option++;
						if(PMode_Option > 9)
							PMode_Option = 9;
						Flash_Read((uint8_t *)(&Param),sizeof(Param));
						Set_Temp=Param.P_Param[PMode_Option][0];//开机设置设定温度37℃
						Ctrl_Temp = Set_Temp;
						Set_Time=Param.P_Param[PMode_Option][1];//开机设置设定时间为20min
						Ctrl_Time=Param.P_Param[PMode_Option][1];//开机设置实际时间为20min
						if(Set_Time > 0)
							Time_State = 0;
						else
							Time_State = 1;
                        Key_Status = 1;//按键操作时不闪烁，2s后闪烁
                        Twinkle_Time = 6000;//闪烁时间6S
					}
					else if(sys.SetP_Mode_Option == 1)//设置P1
					{
						PMode_P1++;
						if(PMode_P1 > 9)
							PMode_P1 = 9;
						PMode_Option = PMode_P1;
						Flash_Read((uint8_t *)(&Param),sizeof(Param));
						Set_Time=Param.P_Param[PMode_Option][1];//开机设置设定时间为20min
						Ctrl_Time=Param.P_Param[PMode_Option][1];//开机设置实际时间为20min
						Set_Temp=Param.P_Param[PMode_Option][0];//开机设置设定温度37℃
						Ctrl_Temp = Set_Temp;
						if(Set_Time > 0)
							Time_State = 0;
						else
							Time_State = 1;
                        Key_Status = 1;//按键操作时不闪烁，2s后闪烁
                        Twinkle_Time = 6000;//闪烁时间6S
					}
					else if(sys.SetP_Mode_Option == 2)//设置P2
					{
						PMode_P2++;
						if(PMode_P2 > 9)
							PMode_P2 = 9;
						PMode_Option = PMode_P2;
						Flash_Read((uint8_t *)(&Param),sizeof(Param));
						Set_Time=Param.P_Param[PMode_Option][1];//开机设置设定时间为20min
						Ctrl_Time=Param.P_Param[PMode_Option][1];//开机设置实际时间为20min
						Set_Temp=Param.P_Param[PMode_Option][0];//开机设置设定温度37℃
						Ctrl_Temp = Set_Temp;
						if(Set_Time > 0)
							Time_State = 0;
						else
							Time_State = 1;
                        Key_Status = 1;//按键操作时不闪烁，2s后闪烁
                        Twinkle_Time = 6000;//闪烁时间6S
					}
					else
					{
						Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
					}
                }
			}
			Key_Flag2 = 0;//按键事件结束，等待下一次按下
			Key_Cnt2 = 0;//按钮计数清零		
		}
		if(Key_Cnt2 > 1.9 && Key_Cnt2 < 2.1)//按键时间大于1.9S小于2.1S表示长按
		{
			if(sys.Run_Status)
			{
				Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
			}
			else
			{
				if(sys.SetMode_Option == 2)//在设置温度选项
				{
					Set_Temp++;//温度++；
					if(Set_Temp > 1000)//最高设定温度在100℃
						Set_Temp = 1000;
                    Key_Status = 1;//按键操作时不闪烁，2s后闪烁
                    Twinkle_Time = 6000;//闪烁时间6S
				}
				else if(sys.SetMode_Option == 3)//在设置时间选项
				{
					if(Time_Unit == 0)//在秒单位模式下
					{
						Set_Time += 5;//时间加5s
						Time_State = 0;//时间退出显示“----”
					}
					else//在分单位模式下
						Set_Time += 60;//时间加60s
					if(Set_Time > 86399)//最高可定时23.99小时
						Set_Time = 86399;
                    Key_Status = 1;//按键操作时不闪烁，2s后闪烁
                    Twinkle_Time = 6000;//闪烁时间6S
				}
				else if(sys.SetMode_Option == 1)
				{
					PMode_Option++;
					if(PMode_Option > 9)
						PMode_Option = 9;
					Flash_Read((uint8_t *)(&Param),sizeof(Param));
					Set_Temp=Param.P_Param[PMode_Option][0];//开机设置设定温度37℃
					Ctrl_Temp = Set_Temp;
					Set_Time=Param.P_Param[PMode_Option][1];//开机设置设定时间为20min
					Ctrl_Time=Param.P_Param[PMode_Option][1];//开机设置实际时间为20min
					if(Set_Time > 0)
						Time_State = 0;
					else
						Time_State = 1;
                    Key_Status = 1;//按键操作时不闪烁，2s后闪烁
                    Twinkle_Time = 6000;//闪烁时间6S
				}
				else if(sys.SetP_Mode_Option == 1)//设置P1
				{
					PMode_P1++;
					if(PMode_P1 > 9)
						PMode_P1 = 9;
					PMode_Option = PMode_P1;
					Flash_Read((uint8_t *)(&Param),sizeof(Param));
					Set_Time=Param.P_Param[PMode_Option][1];//开机设置设定时间为20min
					Ctrl_Time=Param.P_Param[PMode_Option][1];//开机设置实际时间为20min
					Set_Temp=Param.P_Param[PMode_Option][0];//开机设置设定温度37℃
					Ctrl_Temp = Set_Temp;
					if(Set_Time > 0)
						Time_State = 0;
					else
						Time_State = 1;
                    Key_Status = 1;//按键操作时不闪烁，2s后闪烁
                    Twinkle_Time = 6000;//闪烁时间6S
				}
				else if(sys.SetP_Mode_Option == 2)//设置P2
				{
					PMode_P2++;
					if(PMode_P2 > 9)
						PMode_P2 = 9;
					PMode_Option = PMode_P2;
					Flash_Read((uint8_t *)(&Param),sizeof(Param));
					Set_Time=Param.P_Param[PMode_Option][1];//开机设置设定时间为20min
					Ctrl_Time=Param.P_Param[PMode_Option][1];//开机设置实际时间为20min
					Set_Temp=Param.P_Param[PMode_Option][0];//开机设置设定温度37℃
					Ctrl_Temp = Set_Temp;
					if(Set_Time > 0)
						Time_State = 0;
					else
						Time_State = 1;
                    Key_Status = 1;//按键操作时不闪烁，2s后闪烁
                    Twinkle_Time = 6000;//闪烁时间6S
				}
				else
				{
					Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
				}
			}
			Key_Flag2 = 0;//按键事件结束，等待下一次按下
			Key_Cnt2 = 1.88f;//按钮计数清零
		}
	}

	/**************************************减键**************************************/
	if(!Key3)//按下按键
	{
		Key_Cnt3 += dT;//按下时间++
		Key_Flag3 = 1;//按键按下标志置一
	}
	if(Key_Flag3 == 1)//按键被按下
	{
		if(Key3)//抬起按键
		{   
			if(Key_Cnt3 > 0.05f && Key_Cnt3 < 1.5)//按键时间大于0.05S小于1.5S是单击
			{
				if(sys.Run_Status)
				{
					Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
				}
				else
				{
					if(sys.SetMode_Option == 2)//在设置温度选项
					{
						Set_Temp--;//温度--；
						if(Set_Temp < -50)//如果设定温度小于0时（单加热只能自动降温）
						{
							Set_Temp = -50;//将设定温度保持在0
						}
                        Key_Status = 1;//按键操作时不闪烁，2s后闪烁
                        Twinkle_Time = 6000;//闪烁时间6S
					}
					else if(sys.SetMode_Option == 3)//在设置时间选项
					{
						if(Time_Unit == 0)//在秒单位模式下
						{
							if(Set_Time)
								Set_Time -= 5;//时间减5s
							if(Set_Time < 5)//小于5s的设定值时
							{
								Set_Time = 0;
								Time_State = 1;//时间显示“----”
							}   
						}
						else//在分为单位的模式下
							Set_Time -= 60;//时间减1分钟
                        Key_Status = 1;//按键操作时不闪烁，2s后闪烁
                        Twinkle_Time = 6000;//闪烁时间6S
					}
					else if(sys.SetMode_Option == 1)
					{
						PMode_Option--;
						if(PMode_Option < 1)
							PMode_Option = 1;
						Flash_Read((uint8_t *)(&Param),sizeof(Param));
						Set_Time=Param.P_Param[PMode_Option][1];//开机设置设定时间为20min
						Ctrl_Time=Param.P_Param[PMode_Option][1];//开机设置实际时间为20min
						Set_Temp=Param.P_Param[PMode_Option][0];//开机设置设定温度37℃
						Ctrl_Temp = Set_Temp;
						if(Set_Time > 0)
							Time_State = 0;
						else
							Time_State = 1;
                        Key_Status = 1;//按键操作时不闪烁，2s后闪烁
                        Twinkle_Time = 6000;//闪烁时间6S
					}
					else if(sys.SetP_Mode_Option == 1)//设置P1
					{
						PMode_P1--;
						if(PMode_P1 < 1)
							PMode_P1 = 1;
						PMode_Option = PMode_P1;
						Flash_Read((uint8_t *)(&Param),sizeof(Param));
						Set_Time=Param.P_Param[PMode_Option][1];//开机设置设定时间为20min
						Ctrl_Time=Param.P_Param[PMode_Option][1];//开机设置实际时间为20min
						Set_Temp=Param.P_Param[PMode_Option][0];//开机设置设定温度37℃
						Ctrl_Temp = Set_Temp;
						if(Set_Time > 0)
							Time_State = 0;
						else
							Time_State = 1;
                        Key_Status = 1;//按键操作时不闪烁，2s后闪烁
                        Twinkle_Time = 6000;//闪烁时间6S
					}
					else if(sys.SetP_Mode_Option == 2)//设置P2
					{
						PMode_P2--;
						if(PMode_P2 < 1)
							PMode_P2 = 1;
						PMode_Option = PMode_P2;
						Flash_Read((uint8_t *)(&Param),sizeof(Param));
						Set_Time=Param.P_Param[PMode_Option][1];//开机设置设定时间为20min
						Ctrl_Time=Param.P_Param[PMode_Option][1];//开机设置实际时间为20min
						Set_Temp=Param.P_Param[PMode_Option][0];//开机设置设定温度37℃
						Ctrl_Temp = Set_Temp;
						if(Set_Time > 0)
							Time_State = 0;
						else
							Time_State = 1;
                        Key_Status = 1;//按键操作时不闪烁，2s后闪烁
                        Twinkle_Time = 6000;//闪烁时间6S
					}
					else
					{
						Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
					}
				}
			}
			Key_Flag3 = 0;//按键事件结束，等待下一次按下
			Key_Cnt3 = 0;//按钮计数清零		
		}
		if(Key_Cnt3 > 1.9 && Key_Cnt3 < 2.1)//按键时间大于1.9S小于2.1S表示长按
		{
			if(sys.Run_Status)
			{
				Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
			}
			else
			{
				if(sys.SetMode_Option == 2)//在设置温度选项
				{
					Set_Temp--;//温度--；
					if(Set_Temp < -50)//如果设定温度小于0时（单加热只能自动降温）
					{
						Set_Temp = -50;//将设定温度保持在0
					}
                    Key_Status = 1;//按键操作时不闪烁，2s后闪烁
                    Twinkle_Time = 6000;//闪烁时间6S
				}
				else if(sys.SetMode_Option == 3)//在设置时间选项
				{
					if(Time_Unit == 0)//在秒单位模式下
					{
						if(Set_Time)
							Set_Time -= 5;//时间减5s
						if(Set_Time < 5)//小于5s的设定值时
						{
							Set_Time = 0;
							Time_State = 1;//时间显示“----”
						}   
					}
					else//在分为单位的模式下
						Set_Time -= 60;//时间减1分钟
                    Key_Status = 1;//按键操作时不闪烁，2s后闪烁
                    Twinkle_Time = 6000;//闪烁时间6S
				}
				else if(sys.SetMode_Option == 1)
				{
					PMode_Option--;
					if(PMode_Option < 1)
						PMode_Option = 1;
					Flash_Read((uint8_t *)(&Param),sizeof(Param));
					Set_Time=Param.P_Param[PMode_Option][1];//开机设置设定时间为20min
					Ctrl_Time=Param.P_Param[PMode_Option][1];//开机设置实际时间为20min
					Set_Temp=Param.P_Param[PMode_Option][0];//开机设置设定温度37℃
					Ctrl_Temp = Set_Temp;
					if(Set_Time > 0)
						Time_State = 0;
					else
						Time_State = 1;
                    Key_Status = 1;//按键操作时不闪烁，2s后闪烁
                    Twinkle_Time = 6000;//闪烁时间6S
				}
				else if(sys.SetP_Mode_Option == 1)//设置P1
				{
					PMode_P1--;
					if(PMode_P1 < 1)
						PMode_P1 = 1;
					PMode_Option = PMode_P1;
					Flash_Read((uint8_t *)(&Param),sizeof(Param));
					Set_Time=Param.P_Param[PMode_Option][1];//开机设置设定时间为20min
					Ctrl_Time=Param.P_Param[PMode_Option][1];//开机设置实际时间为20min
					Set_Temp=Param.P_Param[PMode_Option][0];//开机设置设定温度37℃
					Ctrl_Temp = Set_Temp;
					if(Set_Time > 0)
						Time_State = 0;
					else
						Time_State = 1;
                    Key_Status = 1;//按键操作时不闪烁，2s后闪烁
                    Twinkle_Time = 6000;//闪烁时间6S
				}
				else if(sys.SetP_Mode_Option == 2)//设置P2
				{
					PMode_P2--;
					if(PMode_P2 < 1)
						PMode_P2 = 1;
					PMode_Option = PMode_P2;
					Flash_Read((uint8_t *)(&Param),sizeof(Param));
					Set_Time=Param.P_Param[PMode_Option][1];//开机设置设定时间为20min
					Ctrl_Time=Param.P_Param[PMode_Option][1];//开机设置实际时间为20min
					Set_Temp=Param.P_Param[PMode_Option][0];//开机设置设定温度37℃
					Ctrl_Temp = Set_Temp;
					if(Set_Time > 0)
						Time_State = 0;
					else
						Time_State = 1;
                    Key_Status = 1;//按键操作时不闪烁，2s后闪烁
                    Twinkle_Time = 6000;//闪烁时间6S
				}
				else
				{
					Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
				}
			}
			Key_Flag3 = 0;//按键事件结束，等待下一次按下
			Key_Cnt3 = 1.88f;//按钮计数清零
		}
	} 

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
				if(sys.Run_Status == 1)
				{
					sys.Run_Status = 0;
					Ctrl_Time = Time;
					if(PMode_Status == 2)
					{
						PMode_Mode = 1;//梯度模式
						PMode_Option = PMode_P1;
						Flash_Read((uint8_t *)(&Param),sizeof(Param));
						Set_Time=Param.P_Param[PMode_Option][1];//开机设置设定时间为20min
						Ctrl_Time=Param.P_Param[PMode_Option][1];//开机设置实际时间为20min
						Set_Temp=Param.P_Param[PMode_Option][0];//开机设置设定温度37℃
						Ctrl_Temp = Set_Temp;
						if(Set_Time > 0)
							Time_State = 0;
						else
							Time_State = 1;
						SetOK_Flag = 1;
					}
					SetOK_Flag = 1;
				}
				else
				{
					sys.Run_Status = 1;
					sys.SetMode_Option = 0;
					sys.SetP_Mode_Option = 0;
					Temp_ADDMode= 0;
					CtrlMode = 1;
					Time = Set_Time;
					if(PMode_Status == 2)
					{
						PMode_Option = PMode_P1;
						Flash_Read((uint8_t *)(&Param),sizeof(Param));
						Set_Time=Param.P_Param[PMode_Option][1];//开机设置设定时间为20min
						Ctrl_Time=Param.P_Param[PMode_Option][1];//开机设置实际时间为20min
						Set_Temp=Param.P_Param[PMode_Option][0];//开机设置设定温度37℃
						Ctrl_Temp = Set_Temp;
						if(Set_Time > 0)
							Time_State = 0;
						else
							Time_State = 1;
					}
					SetOK_Flag = 1;
					if(PMode_P1 > PMode_P2)
					{
						sys.Run_Status = 0;
						if(Beep_Flash == 0)
							Beep_Flash = 5;
					}
				}
				Beep_Time = 0.1;//蜂鸣器响0.1S
			}
			Key_Flag4 = 0;//按键事件结束，等待下一次按下
			LongPress4 = 0;//长按标志清零
			Key_Cnt4 = 0;//按钮计数清零
		}
		if(Key_Cnt4 > 1.5 && Key_Cnt4 < 3.0)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress4 == 0)//如果没有一直一直长按着
			{
                Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
				LongPress4 = 1;//长按标志置一
			}
		}
	}
	/**************************************P键******************************************/
	if(!Key5)//按下按键
	{
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
				if(sys.Run_Status)
				{
					Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
				}
				else
				{
					if(PMode_Status == 0)
					{
						if(PMode_Mode == 0)
						{
							PMode_Status = 1;
							PMode_Option = 1;
							sys.SetMode_Option = 1;
							Flash_Read((uint8_t *)(&Param),sizeof(Param));
							Set_Time=Param.P_Param[PMode_Option][1];//开机设置设定时间为20min
							Ctrl_Time=Param.P_Param[PMode_Option][1];//开机设置实际时间为20min
							Set_Temp=Param.P_Param[PMode_Option][0];//开机设置设定温度37℃
							Ctrl_Temp = Set_Temp;
							if(Set_Time > 0)
								Time_State = 0;
							else
								Time_State = 1;
							Twinkle_Time = 6000;//闪烁时间6S
						}
					}
					else
					{
						if(PMode_Mode == 0)
						{
							PMode_Status = 0;
							PMode_Option = 0;
							sys.SetMode_Option = 0;
							Flash_Read((uint8_t *)(&Param),sizeof(Param));
							Set_Time=Param.P_Param[PMode_Option][1];//开机设置设定时间为20min
							Ctrl_Time=Param.P_Param[PMode_Option][1];//开机设置实际时间为20min
							Set_Temp=Param.P_Param[PMode_Option][0];//开机设置设定温度37℃
							Ctrl_Temp = Set_Temp;
							if(Set_Time > 0)
								Time_State = 0;
							else
								Time_State = 1;
							
						}
					}
					Beep_Time = 0.1;//蜂鸣器响0.1S
				}
			}
			Key_Flag5 = 0;//按键事件结束，等待下一次按下
			LongPress5 = 0;//长按标志清零
			Key_Cnt5 = 0;//按钮计数清零
		}
		if(Key_Cnt5 > 1.5 && Key_Cnt5 < 3.0)//按键时间大于1.5S小于3S表示长按
		{
			if(LongPress5 == 0)//如果没有一直一直长按着
			{
				if(sys.Run_Status)
				{
					Beep_Flash = 2;//无效按键时蜂鸣器“滴滴”
				}
				else
				{
					if(PMode_Mode == 0)
					{
						PMode_Mode = 1;//梯度模式
						PMode_Status = 2;//梯度模式
						PMode_P1 = 1;
						PMode_P2 = 1;
						PMode_Option = PMode_P1;
						Circle_Run = 1;
						sys.SetMode_Option = 0;
						sys.SetP_Mode_Option = 1;
						Flash_Read((uint8_t *)(&Param),sizeof(Param));
						Set_Time=Param.P_Param[PMode_Option][1];//开机设置设定时间为20min
						Ctrl_Time=Param.P_Param[PMode_Option][1];//开机设置实际时间为20min
						Set_Temp=Param.P_Param[PMode_Option][0];//开机设置设定温度37℃
						Ctrl_Temp = Set_Temp;
						if(Set_Time > 0)
								Time_State = 0;
							else
								Time_State = 1;
						Twinkle_Time = 6000;//闪烁时间6S
					}
					else
					{
						PMode_Mode = 0;//梯度模式
						PMode_Status = 1;//记忆模式
						PMode_Option = 1;
						Circle_Run = 0;
						sys.SetMode_Option = 1;
						sys.SetP_Mode_Option = 0;
						Flash_Read((uint8_t *)(&Param),sizeof(Param));
						Set_Time=Param.P_Param[PMode_Option][1];//开机设置设定时间为20min
						Ctrl_Time=Param.P_Param[PMode_Option][1];//开机设置实际时间为20min
						Set_Temp=Param.P_Param[PMode_Option][0];//开机设置设定温度37℃
						Ctrl_Temp = Set_Temp;
						if(Set_Time > 0)
							Time_State = 0;
						else
							Time_State = 1;
						Twinkle_Time = 6000;//闪烁时间6S
					}
					Beep_Time = 0.1;//蜂鸣器响0.1S
				}
				LongPress5 = 1;//长按标志置一
			}
		}
	}
}
