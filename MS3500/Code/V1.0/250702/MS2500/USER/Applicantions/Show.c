#include "Show.h"

/**********全局变量声明******/
float Pmode_Twinkle_Time,Speed_Twinkle_Time,Time_Twinkle_Time;//速度闪烁时间和时间闪烁时间

/**********局部变量声明******/
uint8_t Pmode_ShowFlag,Speed_ShowFlag,Time_ShowFlag;//温度、速度、时间显示的标志位 0:常亮 1：熄灭
uint8_t TimeIcn_ShowFlag,SpeedIcn_ShowFlag,Lock_ShowFlag;//加热图标闪烁和时间图标闪烁和速度图标闪烁

/**
 * @brief 闪烁检测
 * 
 * @param dT 执行周期
 */
static void Check_ShowFlag(float dT)
{
	static float Speed_T,Time_T,Pmode_T;
	if(Speed_Twinkle_Time && !EC11A[1].EC11A_Knob)//速度闪烁和没有操作按键时
    {
		Speed_T += dT;
		if(Speed_T >= 0.5f)
		{
			Speed_Twinkle_Time -= 0.5;//闪烁计时
			Speed_ShowFlag = ~Speed_ShowFlag;//速度闪烁
			if(Speed_Twinkle_Time == 0)//如果闪烁结束
			{
				SpeedSet_Flag = 1;//进入速度设定
			} 
			Speed_T = 0;		
		}			
    }
	else
	{
		Speed_ShowFlag = 0;//常亮
		Speed_T = 0;
	}
	
	if(Time_Twinkle_Time && (!EC11A[0].EC11A_Knob))//时间闪烁和没有操作按键时
    {
		Time_T += dT;
		if(Time_T >= 0.5f)
		{
			Time_Twinkle_Time -= 0.5;//闪烁计时
			Time_ShowFlag = ~Time_ShowFlag;//时间闪烁
			if(Time_Twinkle_Time == 0)//如果闪烁结束
			{
				TimeSet_Flag = 1;//进入时间设定
			} 
			Time_T = 0;			
		}			
    }
	else
	{
		Time_ShowFlag = 0;//常亮
		Time_T = 0;
	}
    
    if(Pmode_Twinkle_Time && (!EC11A[1].EC11A_Knob && !EC11A[0].EC11A_Knob))//时间闪烁和没有操作按键时
    {
		Pmode_T += dT;
		if(Pmode_T >= 0.5f)
		{
			Pmode_Twinkle_Time -= 0.5;//闪烁计时
			Pmode_ShowFlag = ~Pmode_ShowFlag;//时间闪烁
			if(Pmode_Twinkle_Time == 0)//如果闪烁结束
			{
                SpeedSet_Flag = TimeSet_Flag=1;//进入设置
			} 
			Pmode_T = 0;
		}			
    }
	else
	{
		Pmode_ShowFlag = 0;//常亮
		Pmode_T = 0;
	}
}

/**
 * @brief 外框动画
 *
 * @param dT 任务周期
 */
void Circle_Duty(float dT)
{
    static float T;
    if (PMode.Status)
    {
        if ((sys.Run_Status == 1) && PMode.Status == 2) // 启动，并且在梯度模式下
        {
            if (T == 0)
            {
                PMode.Circle_Step++;
                if (PMode.Circle_Step > 17)
                    PMode.Circle_Step = 6;
                switch (PMode.Circle_Step)
                {
                case 0:
                    PMode.Light_BIT = 0x0FFF; // 全部点亮
                    break;
                case 1:
                    PMode.Light_BIT = 0x0001; // L1点亮
                    break;
                case 2:
                    PMode.Light_BIT = 0x0003; // L1，2点亮
                    break;
                case 3:
                    PMode.Light_BIT = 0x0007; // L1，2，3点亮
                    break;
                case 4:
                    PMode.Light_BIT = 0x000F; // L1，2，3，4点亮
                    break;
                case 5:
                    PMode.Light_BIT = 0x001F; // L1，2，3，4，5，点亮
                    break;
                case 6:
                    PMode.Light_BIT = 0x003F; // L1，2，3，4，5，6点亮
                    break;
                case 7:
                    PMode.Light_BIT = 0x007E; // L2,3,4,5,6,7点亮
                    break;
                case 8:
                    PMode.Light_BIT = 0x00FC; // L3,4,5,6,7,8点亮
                    break;
                case 9:
                    PMode.Light_BIT = 0x01F8; // L4,5,6,7,8,9点亮
                    break;
                case 10:
                    PMode.Light_BIT = 0x03F0; // L5,6,7,8,9,10点亮
                    break;
                case 11:
                    PMode.Light_BIT = 0x07E0; // L6,7,8,9,10,11,点亮
                    break;
                case 12:
                    PMode.Light_BIT = 0x0FC0; // L7,8,9,10,11,12点亮
                    break;
                case 13:
                    PMode.Light_BIT = 0x0F81; // L8,9,10,11,12,1点亮
                    break;
                case 14:
                    PMode.Light_BIT = 0x0F03; // L9,10,11,12,1,2点亮
                    break;
                case 15:
                    PMode.Light_BIT = 0x0E07; // L10,11,12,1，2，3点亮
                    break;
                case 16:
                    PMode.Light_BIT = 0x0C0F; // L11，12，1，2，3，4点亮
                    break;
                case 17:
                    PMode.Light_BIT = 0x081F; // L12，1，2，3，4，5点亮
                    break;
                default:
                    break;
                }
            }
            T += dT;
            if (T >= 0.5f)
            {
                T = 0;
            }
        }
        else
        {
            PMode.Light_BIT = 0x0FFF; // 全部点亮
            T = 0;
        }
    }
    else
    {
        PMode.Light_BIT = 0x0000; // 全部熄灭
        T = 0;
    }
}

/*
*****************************************************************
 * 函数原型：static void Icn_Twinkle(float dT)
 * 功    能：图标闪烁
 * 调    用：内部调用
*****************************************************************
*/
static void Icn_Twinkle(float dT)
{
	static float T;
	if(sys.Run_Status == 1)		
	{
		T += dT;
		if(T >= 0.5f)
		{
			if(Speed.Set)
			{
				if(Speed.CwIcn)
				{
					if(SpeedIcn_ShowFlag > 0)
						SpeedIcn_ShowFlag --;//速度图标闪烁;
					if(SpeedIcn_ShowFlag < 1)
						SpeedIcn_ShowFlag = 3;
				}
				else
				{
					SpeedIcn_ShowFlag ++;//速度图标闪烁;
					if(SpeedIcn_ShowFlag > 3)
						SpeedIcn_ShowFlag = 1;
				}
			}
			else
				SpeedIcn_ShowFlag = 0;
            
			if(Time.Rel)
				TimeIcn_ShowFlag = ~TimeIcn_ShowFlag;//定时图标闪烁;
            else
            {
                TimeIcn_ShowFlag = 0;
            }
			T = 0;
		}
	}
	else
	{
		if(Speed.CwShow)
		{
			T += dT;
			if(T >= 0.5f)
			{
				if(Speed.CwIcn)
				{
					if(SpeedIcn_ShowFlag ==0)
						SpeedIcn_ShowFlag = 3;
					else
					{
						SpeedIcn_ShowFlag --;//速度图标闪烁;
					
						if(SpeedIcn_ShowFlag ==0)
							Speed.CwShow = 0;
					}
				}
				else
				{
					SpeedIcn_ShowFlag ++;//速度图标闪烁;
					if(SpeedIcn_ShowFlag > 3)
					{
						SpeedIcn_ShowFlag = 0;
						Speed.CwShow = 0;
					}
				}
				T = 0;
			}
		}
		else
			SpeedIcn_ShowFlag = 0;//显示时间图标
		
		TimeIcn_ShowFlag = 0;//显示时间图标
	}
}

/**
 * @brief 锁定误触图标闪烁检测
 *
 * @param dT 任务周期
 */
void Check_Lock(float dT)
{
    static float T;
	if (sys.Lock_Alarm)
	{
		T += dT;
		if (T >= 0.5f)
		{
			Lock_ShowFlag = ~Lock_ShowFlag;//安全温度图标闪烁
            sys.Lock_Alarm -= 0.5f;
			T = 0;
		}
	}
    else
    {
        Lock_ShowFlag = 0;
    }
}

/*
*****************************************************************
 * 函数原型：void Twinkle(float dT)
 * 功    能：闪烁函数
*****************************************************************
*/
void Twinkle(float dT)
{
	Check_ShowFlag(dT);//闪烁检测
    Circle_Duty(dT);
    Check_Lock(dT);//锁定误触图标闪烁检测
	Icn_Twinkle(dT);//图标闪烁
}

/*
*****************************************************************
 * 函数原型：void Display_Temp(int16_t dis_set_temp,int16_t dis_rel_temp)
 * 功    能：显示温度
 * 输    入: dis_set_temp 设定温度  dis_rel_temp 实际温度
 * 参    数：int16_t dis_set_temp,int16_t dis_rel_temp
*****************************************************************
*/
void Display(void)
{
    uint8_t Val = 0;// 用于百十个取出来的数字
  
    if(sys.Display)
    {
		HAL_TIM_PWM_Stop(&htim16, TIM_CHANNEL_1);
		__HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, 399);//背光pwm
		memset(seg, 0, sizeof(seg));//清空数组
	}
    else
    {
        HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
        __HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, 200);//背光pwm
        memset(seg, 0, sizeof(seg));//清空数组
		
		/**********实际转速显示**********/
        if (Speed.Display_Rel > 999) // 大于999时
        {
            Val = Speed.Display_Rel / 1000 % 10;
            ShowDigit(RelSpeed_1,Val);
        }
        else
        {
             ShowDigit(RelSpeed_1,Dispaly_0);//显示数字0
        }
            
        if (Speed.Display_Rel > 99) // 大于99时
        {
            Val = Speed.Display_Rel / 100 % 10;
            ShowDigit(RelSpeed_2,Val);
        }
        else
        {
            ShowDigit(RelSpeed_2,Dispaly_0);//显示数字零
        }
        if (Speed.Display_Rel > 9) // 大于9时
        {
            Val = Speed.Display_Rel / 10 % 10;
            ShowDigit(RelSpeed_3,Val);
        }
        else
        {
            ShowDigit(RelSpeed_3,Dispaly_0);//显示数字零
        }
        
        Val = Speed.Display_Rel % 10;
       ShowDigit(RelSpeed_4,Val);
        
        /**********设定转速显示**********/
        if(Speed_ShowFlag)
        {
            ShowDigit(SetSpeed_1,Dispaly_OFF);//不显示
			ShowDigit(SetSpeed_2,Dispaly_OFF);//不显示
			ShowDigit(SetSpeed_3,Dispaly_OFF);//不显示
			ShowDigit(SetSpeed_4,Dispaly_OFF);//不显示
        }
        else
        {
			if (Speed.Display_Set > 999) // 大于999时
			{
				Val = Speed.Display_Set / 1000 % 10;
				ShowDigit(SetSpeed_1,Val);
			}
			else
			{
				ShowDigit(SetSpeed_1,Dispaly_0);//显示数字0
			}
				
			if (Speed.Display_Set > 99) // 大于99时
			{
				Val = Speed.Display_Set / 100 % 10;
				ShowDigit(SetSpeed_2,Val);
			}
			else
			{
				ShowDigit(SetSpeed_2,Dispaly_0);//显示数字零
			}
			if (Speed.Display_Set > 9) // 大于9时
			{
				Val = Speed.Display_Set / 10 % 10;
				ShowDigit(SetSpeed_3,Val);
			}
			else
			{
				ShowDigit(SetSpeed_3,Dispaly_0);//显示数字零
			}
			Val = Speed.Display_Set % 10;
			ShowDigit(SetSpeed_4,Val);
		}
		
		 /**********实际时间显示**********/
		if(Time.Display_Set > 3599)
			Time.Unit = 1;//min
		else
			Time.Unit = 0;//sec
		
		if(Time.Display_Rel == 0)
		{
			ShowDigit(RelTime_1,Dispaly__);//显示"-"
			ShowDigit(RelTime_2,Dispaly__);//显示"-"
			ShowDigit(RelTime_3,Dispaly__);//显示"-"
			ShowDigit(RelTime_4,Dispaly__);//显示"-"
		}
		else
		{
			if(Time.Unit == 1)
				Val = Time.Display_Rel / 3600 / 10;//计算十位为单位的小时数
			else if(Time.Unit == 0)
				Val = Time.Display_Rel / 60 / 10;//计算十位为单位的小时数
			else if(Time.Display_Rel > 0)
				Val = 0;//计算十位为单位的小时数
			else Val = Dispaly__;//显示‘-’
			ShowDigit(RelTime_1,Val);
                   
			if(Time.Unit == 1)
				Val = Time.Display_Rel / 3600 % 10;//计算十位为单位的小时数
			else if(Time.Unit == 0)
				Val = Time.Display_Rel / 60 % 10;//计算十位为单位的小时数
			else if(Time.Display_Rel > 0)
				Val = 0;//计算十位为单位的小时数
			else Val = Dispaly__;//显示‘-’
			ShowDigit(RelTime_2,Val);       

			if(Time.Unit == 1)
				Val = Time.Display_Rel % 3600 / 60 / 10;//计算十位为单位的小时数
			else if(Time.Unit == 0)
				Val = Time.Display_Rel % 60 / 10;//计算十位为单位的小时数
			else if(Time.Display_Rel > 0)
				Val = Time.Display_Rel % 60 / 10;//计算十位为单位的小时数
			else Val = Dispaly__;//显示‘-’
			ShowDigit(RelTime_3,Val);       

			if(Time.Unit == 1)
				Val = Time.Display_Rel % 3600 / 60 % 10;//计算十位为单位的小时数
			else if(Time.Unit == 0)
				Val = Time.Display_Rel % 60 % 10;//计算十位为单位的小时数
			else if(Time.Display_Rel > 0)
				Val = Time.Display_Rel % 60 % 10;//计算十位为单位的小时数
			else Val = Dispaly__;//显示‘-’
			ShowDigit(RelTime_4,Val);
		}
		
		 /**********设置时间显示**********/
		if(!Time_ShowFlag)//显示时间表示为0
		{
			if(Time.Display_Set == 0)
			{
				ShowDigit(SetTime_1,Dispaly__);//显示"-"
				ShowDigit(SetTime_2,Dispaly__);//显示"-"
				ShowDigit(SetTime_3,Dispaly__);//显示"-"
				ShowDigit(SetTime_4,Dispaly__);//显示"-"
			}
			else
			{
				if(Time.Unit == 1)
					Val = Time.Display_Set / 3600 / 10;//计算十位为单位的小时数
				else if(Time.Unit == 0)
					Val = Time.Display_Set / 60 / 10;//计算十位为单位的小时数
				else if(Time.Display_Set > 0)
					Val = 0;//计算十位为单位的小时数
				else Val = Dispaly__;//显示‘-’
				ShowDigit(SetTime_1,Val);
					   

				if(Time.Unit == 1)
					Val = Time.Display_Set / 3600 % 10;//计算十位为单位的小时数
				else if(Time.Unit == 0)
					Val = Time.Display_Set / 60 % 10;//计算十位为单位的小时数
				else if(Time.Display_Set > 0)
					Val = 0;//计算十位为单位的小时数
				else Val = Dispaly__;//显示‘-’
				ShowDigit(SetTime_2,Val);       

				if(Time.Unit == 1)
					Val = Time.Display_Set % 3600 / 60 / 10;//计算十位为单位的小时数
				else if(Time.Unit == 0)
					Val = Time.Display_Set % 60 / 10;//计算十位为单位的小时数
				else if(Time.Display_Set > 0)
					Val = Time.Display_Set % 60 / 10;//计算十位为单位的小时数
				else Val = Dispaly__;//显示‘-’
				ShowDigit(SetTime_3,Val);       

				if(Time.Unit == 1)
					Val = Time.Display_Set % 3600 / 60 % 10;//计算十位为单位的小时数
				else if(Time.Unit == 0)
					Val = Time.Display_Set % 60 % 10;//计算十位为单位的小时数
				else if(Time.Display_Set > 0)
					Val = Time.Display_Set % 60 % 10;//计算十位为单位的小时数
				else Val = Dispaly__;//显示‘-’
				ShowDigit(SetTime_4,Val);       
			}
		} 
		else
		{
			ShowDigit(SetTime_1,Dispaly_OFF);//不显示
			ShowDigit(SetTime_2,Dispaly_OFF);//不显示
			ShowDigit(SetTime_3,Dispaly_OFF);//不显示
			ShowDigit(SetTime_4,Dispaly_OFF);//不显示
		}
	
		/* 设置时间冒号 */
		bit_Cal(25, 0x01, 0x01);
		/* 实际时间冒号 */
		bit_Cal(2, 0x08, 0x08);
		
		if(Time.Unit == 0)
		{
			/**********‘sec’图标**********/
			bit_Cal(23, 0x01, 0x01);
			/**********‘min’图标**********/
			bit_Cal(24, 0x01, 0x00);
		}
		else
		{
			/**********‘sec’图标**********/
			bit_Cal(23, 0x01, 0x00);
			/**********‘min’图标**********/
			bit_Cal(24, 0x01, 0x01);
		}
		/* 时间图标 */
		bit_Cal(6, 0x08, 0x08);
		if(sys.Run_Status && TimeIcn_ShowFlag)//运行时
		{
			bit_Cal(2, 0x08, 0x0);//实际时间冒号（上面）消失
			bit_Cal(6, 0x08, 0x00);//时间图标（上面）消失
		}
		/* rpm */
		bit_Cal(17, 0x01, 0x01);
		
		/**********转速图标**********/
        switch(SpeedIcn_ShowFlag)
        {
            case 0: bit_Cal(22, 0x01, 0x01);//S5
                    bit_Cal(21, 0x01, 0x01);//S4
                    bit_Cal(8 ,0x01, 0x01);//S3
                break;
            case 1: bit_Cal(22, 0x01, 0x00);//S5
                    bit_Cal(21, 0x01, 0x01);//S4
                    bit_Cal(8, 0x01, 0x01);//S3
                break;
            case 2: bit_Cal(22, 0x01, 0x01);//S5
                    bit_Cal(21, 0x01, 0x01);//S4
                    bit_Cal(8, 0x01, 0x00);//S3
                break;
            case 3: bit_Cal(22, 0x01, 0x01);//S5
                    bit_Cal(21, 0x01, 0x00);//S4
                    bit_Cal(8, 0x01, 0x01);//S3
                break;
            default:
                break;
        }
		/**********锁定图标**********/
		if(sys.Lock && !Lock_ShowFlag)
		{
			bit_Cal(7, 0x01, 0x01);//锁定
		}
		else
		{
			bit_Cal(7, 0x01, 0x00);//不显示锁定
		}
		
		/**********L1**********/
        if(PMode.Light_BIT & BIT0)
        {
            bit_Cal(28, 0x10, 0x10);
        }
        else
        {
            bit_Cal(28, 0x10, 0x00);
        }
        
        /**********L2**********/
        if(PMode.Light_BIT & BIT1)
        {
            bit_Cal(0, 0x08, 0x08);
        }
        else
        {
            bit_Cal(0, 0x08, 0x00);
        }
        
        /**********L3**********/
        if(PMode.Light_BIT & BIT2)
        {
            bit_Cal(2, 0x10, 0x10);
        }
        else
        {
            bit_Cal(2, 0x10, 0x00);
        }
        
        /**********L4**********/
        if(PMode.Light_BIT & BIT3)
        {
            bit_Cal(4, 0x08, 0x08);
        }
        else
        {
            bit_Cal(4, 0x08, 0x00);
        }
        
        /**********L5**********/
        if(PMode.Light_BIT & BIT4)
        {
            bit_Cal(6, 0x10, 0x10);
        }
        else
        {
            bit_Cal(6, 0x10, 0x00);
        }
        
        /**********L6**********/
        if(PMode.Light_BIT & BIT5)
        {
            bit_Cal(6, 0x20, 0x20);
        }
        else
        {
            bit_Cal(6, 0x20, 0x00);
        }
        
        /**********L7**********/
        if(PMode.Light_BIT & BIT6)
        {
            bit_Cal(6, 0x40, 0x40);
        }
        else
        {
            bit_Cal(6, 0x40, 0x00);
        }
        
        /**********L8**********/
        if(PMode.Light_BIT & BIT7)
        {
            bit_Cal(4, 0x80, 0x80);
        }
        else
        {
            bit_Cal(4, 0x80, 0x00);
        }
        
        /**********L9**********/
        if(PMode.Light_BIT & BIT8)
        {
            bit_Cal(0, 0x80, 0x80);
        }
        else
        {
            bit_Cal(0, 0x80, 0x00);
        }
        
        /**********L10**********/
        if(PMode.Light_BIT & BIT9)
        {
            bit_Cal(28, 0x80, 0x80);
        }
        else
        {
            bit_Cal(28, 0x80, 0x00);
        }
        
        /**********L11**********/
        if(PMode.Light_BIT & BIT10)
        {
            bit_Cal(28, 0x40, 0x40);
        }
        else
        {
            bit_Cal(28, 0x40, 0x00);
        }
        
        /**********L12**********/
        if(PMode.Light_BIT & BIT11)
        {
            bit_Cal(28, 0x20, 0x20);
        }
        else
        {
            bit_Cal(28, 0x20, 0x00);
        }
		
		if (PMode.Status) // 进入PMode
		{
			if (!Pmode_ShowFlag)
			{
				ShowDigit(P_1,Dispaly_P);//P
				ShowDigit(P_2,Dispaly__);//-
				ShowDigit(P_3,PMode.Option);//显示
			}
			else
			{
				ShowDigit(P_1,Dispaly_OFF);//不显示
				ShowDigit(P_2,Dispaly_OFF);//不显示
				ShowDigit(P_3,Dispaly_OFF);//不显示
			}
		}
		else // 不进入P模式不显示
		{
			ShowDigit(P_1,Dispaly_OFF);//不显示
			ShowDigit(P_2,Dispaly_OFF);//不显示
			ShowDigit(P_3,Dispaly_OFF);//不显示
		}
	}
	/**********数据发送**********/
	for(uint8_t i=0;i<31;i++)
	{
		Write_Addr_Dat_N(i*2, seg[i], 1);
	}
}

/**
 * @brief 速度显示处理
 * 
 */
void Deal_Speed(float dT)
{
	if(sys.Run_Status == 1)
	{
		if(Speed.Ctrl)
		{
			if(Speed.ADDMode==0)//在电机控制中，速度未处理
			{ 
				if(Speed.Ctrl >= Speed.Display_Rel)//控制速度大于实际速度
				{
					Speed.ADDMode = 1;//进入加速模式下
				}
				else if(Speed.Ctrl < Speed.Display_Rel)//控制速度小于实际速度
				{
					Speed.ADDMode = 2;//进入减速模式下
				}
			}
			if(Speed.ADDMode==1)//在进入加速模式下
			{
				Speed.New = Speed.Rel;//记录当前速度
				if(Speed.New > Speed.Display_Rel)//当前速度大于显示速度
				{
					if(Speed.Display_Rel < Speed.New)
						Speed.Display_Rel = Speed.New;//显示当前速度
				}
				else//当前速度小于上一次速度
				{
					Speed.Display_Rel = Speed.Display_Rel;//显示上一次速度，不让速度小于当前速度。呈现攀升速度的现象
				}  
				if(sys.Motor_Stop == 0)
				{
					if(Speed.Display_Rel >= Speed.Ctrl)//实际速度大于等于控制速度
					{
						Speed.ADDMode = 3;//进入稳定模式
						return;
					}
				}
			}
			if(Speed.ADDMode == 2)//速度下降模式下
			{
				Speed.New = Speed.Rel;//记录当前速度
				
				if(Speed.New < Speed.Display_Rel)//当前速度小于上一次速度
				{
					if(Speed.Display_Rel > Speed.New)
						Speed.Display_Rel = Speed.New;//显示当前速度
				}
				else//当前速度大于上一次速度
				{
					Speed.Display_Rel = Speed.Display_Rel;//显示上一次速度，不让速度大于当前速度。呈现下降速度的现象
				}
				if(sys.Motor_Stop == 0)
				{
					if(Speed.Display_Rel <= Speed.Ctrl)//实际速度小于等于控制速度
					{
						Speed.ADDMode = 3;//进入稳定模式
						return;
					}
				}
			}
			else if(Speed.ADDMode == 3)//速度稳定模式下
			{
				Speed.Display_Rel = Speed.Ctrl;//显示控制速度
			}
		}
		else
		{
			if(Speed.Display_Rel)
				Speed.Display_Rel = Speed.Rel;//显示当前速度
			else
				Speed.Display_Rel =0;//显示当前速度为0
		}
	}
	else
	{
		Speed.Display_Rel = 0;//实际速度显示为零
		Speed.New =0;//现在的速度清零
		Speed.ADDMode = 0;//清除显示处理
	}
}

/**
 * @brief 显示屏幕内容
 * 
 */
void Show_Display(void)
{
	Time.Display_Rel = Time.Rel;//显示控制时间		
	Time.Display_Set = Time.Set;//显示设定时间  
    
    Speed.Display_Set = Speed.Set;
    Display();
}
