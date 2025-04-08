#include "Drv_EC11A.h"

/**********结构体************/
_EC11A_ EC11A[2];//旋钮参数

/**********全局变量声明******/
uint8_t Work_Option = 1;//选择工位号
uint8_t SetMode_Option;//选择设置模式
uint8_t EC11A_Knob;//在旋动旋钮时
uint8_t Run_Status;//系统状态
uint8_t Work_All;//工位设置相同

/**********局部变量声明******/
uint8_t EC11A_Flag,Key1_Flag;//进入中断延时标志
uint8_t Key1_Press,Key2_Press;//按下按钮
uint16_t KEY1_Count,KEY2_Count;//记录KEY1,KEY2按下的时间

/*
*****************************************************************
 * 函数原型：void Check_Knob(void)
 * 功    能：检测旋钮状态-500ms
*****************************************************************
*/
void Check_Knob(void)
{
    if(EC11A_Knob)//旋钮被转动
        EC11A_Knob--;//1S倒计时
}

/*
*****************************************************************
 * 函数原型：void EC11A_Init(void)
 * 功    能：EC11A初始化定时器
*****************************************************************
*/
void EC11A_Init(void)
{
	/**********EC11A_1**********/
	EC11A[0].EXTI_Pin = KEY1A_Pin;//EC11A旋钮中断引脚
	EC11A[0].EC11A_Pin = KEY1B_Pin;//EC11A旋钮输入引脚
	EC11A[0].EC11A_GPIO = KEY1B_GPIO_Port;//EC11A旋钮输入GPIO端口
	
	EC11A[0].Key_Pin = KEY1_Pin;//EC11A按键输入引脚
	EC11A[0].Key_GPIO = KEY1_GPIO_Port;//EC11A按键输入GPIO端口
	
	EC11A[0].EC11A_Fast = EC11A_FastSpeed;//判断旋转速度阈值
	
	/**********EC11A_2**********/
	EC11A[1].EXTI_Pin = KEY2A_Pin;//EC11A旋钮中断引脚
	EC11A[1].EC11A_Pin = KEY2B_Pin;//EC11A旋钮输入引脚
	EC11A[1].EC11A_GPIO = KEY2B_GPIO_Port;//EC11A旋钮输入GPIO端口
	
	EC11A[1].Key_Pin = KEY2_Pin;//EC11A按键输入引脚
	EC11A[1].Key_GPIO = KEY2_GPIO_Port;//EC11A按键输入GPIO端口
	
	EC11A[1].EC11A_Fast = EC11A_FastSpeed;//判断旋转速度阈值
}

/*
*****************************************************************
 * 函数原型：void EC11A_Speed(float dT)
 * 功    能：EC11A旋钮速度计算
*****************************************************************
*/
void EC11A_Speed(float dT)
{
	/**********EC11A_1**********/
	EC11A[0].EC11A_Speed = EC11A[0].EC11A_Cnt*60/20;//一秒检测一次。转一圈20个反馈，一分钟的速度
	EC11A[0].EC11A_Cnt = 0;//将检测到的计数清零
	
	/**********EC11A_2**********/
	EC11A[1].EC11A_Speed = EC11A[1].EC11A_Cnt*60/20;//一秒检测一次。转一圈20个反馈，一分钟的速度
	EC11A[1].EC11A_Cnt = 0;//将检测到的计数清零
}

/*
*****************************************************************
 * 函数原型：void EC11AKey_Scan(float dT)
 * 功    能：EC11A按键扫描
*****************************************************************
*/
void EC11AKey_Scan(float dT)
{
	/**********EC11A_1**********/
	if(HAL_GPIO_ReadPin(EC11A[0].Key_GPIO,EC11A[0].Key_Pin) == KEY_DOWN)//按下按键
	{
		if(EC11A[0].LongPress == 0)//没有长按过
		{
			EC11A[0].Key_Cnt += dT;//按下时间++
			EC11A[0].Key_Flag = 1;//按键按下标志置一
		}
	}
	if(EC11A[0].Key_Flag == 1)//按键被按下
	{
		if(HAL_GPIO_ReadPin(EC11A[0].Key_GPIO,EC11A[0].Key_Pin) == KEY_UP)//抬起按键
		{   
			if(EC11A[0].Key_Cnt > 0.1 && EC11A[0].Key_Cnt < 1.5)//小于1.5S是单击
			{
				Work_Option++;//工号位++
                #if(Integration_TYPE == 0)//设置成四联六联时
					if(Param.type == 0 || Param.type == 2)
					{
						if(Work_Option > 2 && Work_Option < 5)//如果工号位大于2，工号位为5
							Work_Option = 5;//工号位为7号
						if(Work_Option > 6)//如果工号位大于8，工号位为1
							Work_Option = 1;//工号位为1号
					}
					else if(Param.type == 1 || Param.type == 3)
					{
						if(Work_Option > 6)//如果工号位大于6，工号位为1
							Work_Option = 1;//工号位为1号
					}
                #elif(Integration_TYPE == 1)//设置成九联时
                    if(Work_Option > 9)//如果工号位大于9，工号位为1
                        Work_Option = 1;//工号位为1号   
                #endif
                Beep_Time = 0.1;//蜂鸣器响0.1S
                SetMode_Option = 0;//每次切换工位，设置模式置0
                Twinkle_Time = 0;
			}
			EC11A[0].Key_Flag = 0;//按键事件结束，等待下一次按下
			EC11A[0].LongPress = 0;//长按标志清零
			EC11A[0].Key_Cnt = 0;//按钮计数清零
		}
		if(EC11A[0].Key_Cnt > 1.5 && EC11A[0].Key_Cnt < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(EC11A[0].LongPress == 0)//如果没有一直一直长按着
			{
                Work_All = 1;//进入全局设置模式
                SetMode_Option = 0;//退出设置模式
                Twinkle_Time = 0;
                SetALL_int(0,&Speed_ADDMode);//速度显示模式清零
                /**********同步的数据赋值*********/
                switch(Work_Option)
                {
                    case 1: 
                            Speed_ALL(1,&Set_Speed,&Set_Speed);//同步设置速度
                            Time_ALL(1,&Set_Time,&Set_Time);//同步设置时间
                            break;
                    case 2: 
                            Speed_ALL(2,&Set_Speed,&Set_Speed);//同步设置速度
                            Time_ALL(2,&Set_Time,&Set_Time);//同步设置时间
                            break;
                    case 3: 
                            
                            Speed_ALL(3,&Set_Speed,&Set_Speed);//同步设置速度
                            Time_ALL(3,&Set_Time,&Set_Time);//同步设置时间
                            break;
                    case 4: 
                            Speed_ALL(4,&Set_Speed,&Set_Speed);//同步设置速度
                            
                            Time_ALL(4,&Set_Time,&Set_Time);//同步设置时间
                            
                            break;
                    case 5: 
                            Speed_ALL(5,&Set_Speed,&Set_Speed);//同步设置速度
                           
                            Time_ALL(5,&Set_Time,&Set_Time);//同步设置时间
                            
                            break;
                    case 6: 
                            Speed_ALL(6,&Set_Speed,&Set_Speed);//同步设置速度
                            Time_ALL(6,&Set_Time,&Set_Time);//同步设置时间
                           
                            break;
                    case 7: 
                            Speed_ALL(7,&Set_Speed,&Set_Speed);//同步设置速度
                           
                            Time_ALL(7,&Set_Time,&Set_Time);//同步设置时间
                            
                            break;
                    case 8: 
                            Speed_ALL(8,&Set_Speed,&Set_Speed);//同步设置速度
                           
                            Time_ALL(8,&Set_Time,&Set_Time);//同步设置时间
                            
                            break;
                    case 9: 
                            Speed_ALL(9,&Set_Speed,&Set_Speed);//同步设置速度
                           
                            Time_ALL(9,&Set_Time,&Set_Time);//同步设置时间
                            
                            break;
                }
                SetOK_Flag = 1;
                Beep_Time = 0.1;//蜂鸣器响0.1S
				EC11A[0].LongPress = 1;//长按标志置一
			}
		}
	}
	
	/**********EC11A_2**********/
	if(HAL_GPIO_ReadPin(EC11A[1].Key_GPIO,EC11A[1].Key_Pin) == KEY_DOWN)//按下按键
	{
		if(EC11A[1].LongPress == 0)//没有长按过
		{
			EC11A[1].Key_Cnt += dT;//按下时间++
			EC11A[1].Key_Flag = 1;//按键按下标志置一
		}
	}
	if(EC11A[1].Key_Flag == 1)//按键被按下
	{
		if(HAL_GPIO_ReadPin(EC11A[1].Key_GPIO,EC11A[1].Key_Pin) == KEY_UP)//抬起按键
		{   
			if(EC11A[1].Key_Cnt > 0.1 && EC11A[1].Key_Cnt < 1.5)//小于1.5S是单击
			{
                SetMode_Option++;//设置模式切换
				#if(Integration_TYPE == 0)//设置成四联六联时
                if(Param.type <= 1)//设置成普通款
				{
                    if(SetMode_Option == 1)
                        SetMode_Option = 2;//直接跳过温度
                    if(SetMode_Option == 3)//设置模式只有2种，等于4时
                    {
                        SetMode_Option = 0;//清零
                        Twinkle_Time = 0;//闪烁显示6S
                    }
				}
                else if(Param.type >= 1)//设置成加热款时
				{
                    if(SetMode_Option == 3)//设置模式只有3种，等于4时
                    {
                        SetMode_Option = 0;//清零
                        Twinkle_Time = 0;//闪烁显示6S
                    }
				}
				#elif(Integration_TYPE == 1)//设置成九联时
					if(SetMode_Option == 1)
                        SetMode_Option = 2;//直接跳过温度
                    if(SetMode_Option == 3)//设置模式只有2种，等于4时
                    {
                        SetMode_Option = 0;//清零
                        Twinkle_Time = 0;//闪烁显示6S
                    }
				#endif
                Beep_Time = 0.1;//蜂鸣器响0.1S
                if(SetMode_Option != 0)
                {
                    Twinkle_Time = 6000;//闪烁显示6S
                }
			}
			EC11A[1].Key_Flag = 0;//按键事件结束，等待下一次按下
			EC11A[1].LongPress = 0;//长按标志清零
			EC11A[1].Key_Cnt = 0;//按钮计数清零
		}
		if(EC11A[1].Key_Cnt > 1.5 && EC11A[1].Key_Cnt < 3)//按键时间大于1.5S小于3S表示长按
		{
			if(EC11A[1].LongPress == 0)//如果没有一直一直长按着
			{
                if(Run_Status == 1)
                {
                    Run_Status = 0;//关闭系统
                }
                else
                {
                    Run_Status = 1;//打开系统
                    Speed_Val_L1.SumError=0x12000;//启动电机系数
                    Speed_Val_L2.SumError=0x12000;//启动电机系数
                    Speed_Val_L3.SumError=0x12000;//启动电机系数
                    Speed_Val_L4.SumError=0x12000;//启动电机系数
                    Speed_Val_L5.SumError=0x12000;//启动电机系数
                    Speed_Val_L6.SumError=0x12000;//启动电机系数
                    Speed_Val_L7.SumError=0x12000;//启动电机系数
                    Speed_Val_L8.SumError=0x12000;//启动电机系数
                    Speed_Val_L9.SumError=0x12000;//启动电机系数
                    ADD_Wait_Count = 0;
                    SetMode_Option = 0;//退出设置模式
                }
                Beep_Time = 0.1;//蜂鸣器响0.1S
				EC11A[1].LongPress = 1;//长按标志置一
			}
		}
	}
}


/*
*****************************************************************
 * 函数原型：void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
 * 功    能：外部中断
*****************************************************************
*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	UNUSED(GPIO_Pin);
	
	/**********EC11A_1**********/
	if(GPIO_Pin == EC11A[0].EXTI_Pin)//A上升沿触发外部中断
	{
		EC11A[0].FlagTim = 1;//开始计时
		while(EC11A[0].TIM_Cnt <= 2)//定时器一个周期1ms，计时2ms内看看A有没有电跳变
		{
			if(GPIO_Pin == EC11A[0].EXTI_Pin)//在2ms内，检测到电平变化
			{ 
				EC11A[0].FlagTim = 0;//停止计时
				EC11A[0].TIM_Cnt = 0;//清除TIM计数
				EC11A[0].EC11A_Cnt++;//旋钮计数
                Beep_Time = 0.1;//蜂鸣器响0.1S
                SetMode_Option = 0;//每次切换工位，设置模式置0
                Twinkle_Time = 0;
				EC11A[0].EC11A_Knob = 2;//在旋转旋钮时
				if(HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO,EC11A[0].EC11A_Pin) == 0)//加
				{
					Work_Option++;//工号位++
                    #if(Integration_TYPE == 0)//设置成四联六联时
						if(Param.type == 0 || Param.type == 2)
						{
							if(Work_Option > 2 && Work_Option < 5)//如果工号位大于2，工号位为5
								Work_Option = 5;//工号位为7号
							if(Work_Option > 6)//如果工号位大于8，工号位为1
								Work_Option = 1;//工号位为1号
						}
						else if(Param.type == 1 || Param.type == 3)
						{
							if(Work_Option > 6)//如果工号位大于6，工号位为1
								Work_Option = 1;//工号位为1号
						}
                    #elif(Integration_TYPE == 1) //设置成九联时
                        if(Work_Option > 9)//如果工号位大于9，工号位为1
                            Work_Option = 1;//工号位为1号   
                    #endif
					break;
				}
				else if(HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO,EC11A[0].EC11A_Pin) == 1)//减
				{
					Work_Option--;//工号位减1
                    #if(Integration_TYPE == 0)//设置成四联六联时 
						if(Param.type == 0 || Param.type == 2)//四联
						{
							if(Work_Option > 2 && Work_Option < 5)//如果工号位小于5，工号位为2
								Work_Option = 2;//工号位为2号
							if(Work_Option < 1)//如果工号位小于1，工号位为6
								Work_Option = 6;//工号位为6号    
						}
						else if(Param.type == 1 || Param.type == 3)//六联
						{
							if(Work_Option < 1)//如果工号位小于1，工号位为6
								Work_Option = 6;//工号位为6号
						}					
                    #elif(Integration_TYPE == 1)//设置成九联时
                        if(Work_Option < 1)//如果工号位小于1，工号位为9
                            Work_Option = 9;//工号位为9号   
                    #endif
					break;
				}
				break;
			}
		}
		EC11A[0].FlagTim = 0;//停止计时
		EC11A[0].TIM_Cnt = 0;//清除TIM计数
	}
	
	/**********EC11A_2**********/
	if(GPIO_Pin == EC11A[1].EXTI_Pin)//A上升沿触发外部中断
	{
		EC11A[1].FlagTim = 1;//开始计时
		while(EC11A[1].TIM_Cnt <= 2)//定时器一个周期1ms，计时2ms内看看A有没有电跳变
		{
			if(GPIO_Pin == EC11A[1].EXTI_Pin)//在2ms内，检测到电平变化
			{ 
				EC11A[1].FlagTim = 0;//停止计时
				EC11A[1].TIM_Cnt = 0;//清除TIM计数
				EC11A[1].EC11A_Cnt++;//旋钮计数
				EC11A[1].EC11A_Knob = 2;//在旋转旋钮时
				if(HAL_GPIO_ReadPin(EC11A[1].EC11A_GPIO,EC11A[1].EC11A_Pin) == 0)//加
				{
                    /*加*/
                    Set_Val(0,Work_Option,SetMode_Option);//设置数值
					break;
				}
				else if(HAL_GPIO_ReadPin(EC11A[1].EC11A_GPIO,EC11A[1].EC11A_Pin) == 1)//减
				{
                    /*减*/
                    Set_Val(1,Work_Option,SetMode_Option);//设置数值
					break;
				}
				break;
			}
		}
		EC11A[1].FlagTim = 0;//停止计时
		EC11A[1].TIM_Cnt = 0;//清除TIM计数
	}
}

/*
*****************************************************************
 * 函数原型：void TimCnt_Check(float dT)
 * 功    能：定时器计数检测
*****************************************************************
*/
void TimCnt_Check(float dT)
{
    if(EC11A[0].FlagTim)
        EC11A[0].TIM_Cnt++;
    if(EC11A[1].FlagTim)
        EC11A[1].TIM_Cnt++;
    
}
