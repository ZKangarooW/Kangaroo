#include "Show.h"

/**********全局变量声明******/
float Pmode_Twinkle_Time,Speed_Twinkle_Time,Time_Twinkle_Time;//速度闪烁时间、温度闪烁时间和时间闪烁时间

/**********局部变量声明******/
uint8_t Tab[] = {0xFA,0x0A,0xD6,0x9E,0x2E,0xBC,0xFC,0x1A,0xFE,0xBE};//0·9
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
	
	if(Time_Twinkle_Time && (!EC11A[1].EC11A_Knob && !EC11A[0].EC11A_Knob))//时间闪烁和没有操作按键时
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
                SpeedSet_Flag = TempSet_Flag = TimeSet_Flag=1;//进入设置
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

/**
 * @brief 梯度模式显示转换
 *
 * @param dT 任务周期
 */
static void Check_PMode_Mode(float dT)
{
    static float T;
    if (PMode.Status == 2)
    {
        if (sys.Run_Status == 1)
        {
            T += dT;
            if (T > 2.0f)
            {
                PMode.Mode = 1;
                if (T >= 4)
                    T = 0;
            }
            else
            {
                PMode.Mode = 0;
            }
        }
        else
        {
            T = 0;
            PMode.Mode = 1;
        }
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
    Check_PMode_Mode(dT);
    Check_Lock(dT);//锁定误触图标闪烁检测
	Icn_Twinkle(dT);//图标闪烁
}

uint8_t seg[27] = {0};

/**
 * @brief 位数计算
 *
 * @param *bit 输入的位数
 * @param num 与等于的数
 * @param num1 或等于的数
 */
void bit_Cal(uint8_t bit,uint8_t num,uint8_t num1)
{
    seg[bit] &= (0xFF-num);seg[bit] |= num1;
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

        /**********数据发送**********/
        for(uint8_t i=0;i<27;i++)
        {
            Write_Addr_Dat_N(i*2, seg[i], 1);
        }
    }
    else
    {
        HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
        __HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, 200);//背光pwm
        memset(seg, 0, sizeof(seg));//清空数组     

        /**********实际转速显示**********/
        bit_Cal(10, 0xFF, 0xFF);

        /**********数据发送**********/
        for(uint8_t i=0;i<27;i++)
        {
            Write_Addr_Dat_N(i*2, seg[i], 1);
        }
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
    Display();
}
