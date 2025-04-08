#include "Show.h"

/**********全局变量声明******/
float Pmode_Twinkle_Time,Speed_Twinkle_Time,Temp_Twinkle_Time,Time_Twinkle_Time;//速度闪烁时间、温度闪烁时间和时间闪烁时间
float PModeP1_Twinkle_Time, PModeP2_Twinkle_Time;

/**********局部变量声明******/
uint8_t Tab[] = {0xFA,0x0A,0xD6,0x9E,0x2E,0xBC,0xFC,0x1A,0xFE,0xBE};//0·9
uint8_t Pmode_ShowFlag,Temp_ShowFlag,Speed_ShowFlag,Time_ShowFlag;//温度、速度、时间显示的标志位 0:常亮 1：熄灭
uint8_t TempIcn_ShowFlag,TimeIcn_ShowFlag,SpeedIcn_ShowFlag,Lock_ShowFlag;//加热图标闪烁和时间图标闪烁和速度图标闪烁
uint8_t PModeP1_ShowFlag, PModeP2_ShowFlag;// P1，P2闪烁
uint8_t Setting_ShowFlag;//设定闪烁
uint8_t Hot_ShowFlag;//高温报警闪烁

/**
 * @brief 闪烁检测
 * 
 * @param dT 执行周期
 */
static void Check_ShowFlag(float dT)
{
	static float Speed_T,Temp_T,Time_T,Pmode_T,P1mode_T,P2mode_T;
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
	
	if(Temp_Twinkle_Time && !EC11A[0].EC11A_Knob)//速度闪烁和没有操作按键时
    {
		Temp_T += dT;
		if(Temp_T >= 0.5f)
		{
			Temp_Twinkle_Time -= 0.5;//闪烁计时
			Temp_ShowFlag = ~Temp_ShowFlag;//速度闪烁
			if(Temp_Twinkle_Time == 0)//如果闪烁结束
			{
				TempSet_Flag = 1;//进入速度设定
			} 
			Temp_T = 0;		
		}			
    }
	else
	{
		Temp_ShowFlag = 0;//常亮
		Temp_T = 0;
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
    
    if(PModeP1_Twinkle_Time && !EC11A[0].EC11A_Knob)//时间闪烁和没有操作按键时
    {
        if (PMode.Mode) // 如果打开梯度
        {
            P1mode_T += dT;
            if(P1mode_T >= 0.5f)
            {
                PModeP1_Twinkle_Time -= 0.5;//闪烁计时
                PModeP1_ShowFlag = ~PModeP1_ShowFlag;//时间闪烁
                P1mode_T = 0;
            }
        }
        else
        {
            P1mode_T = 0;
            PModeP1_Twinkle_Time = 0;
            PModeP1_ShowFlag = 0;//常亮
        }
    }
	else
	{
		PModeP1_ShowFlag = 0;//常亮
		P1mode_T = 0;
	}
    
    if(PModeP2_Twinkle_Time && !EC11A[1].EC11A_Knob)//时间闪烁和没有操作按键时
    {
        if (PMode.Mode) // 如果打开梯度
        {
            P2mode_T += dT;
            if(P2mode_T >= 0.5f)
            {
                PModeP2_Twinkle_Time -= 0.5;//闪烁计时
                if(PModeP2_Twinkle_Time <= 0)
                {
                    if (PMode.Status == 2)
                    {
                        PMode.Option = PMode.P1;
                        Param_Read(); // 读取参数
                    }
                }
                PModeP2_ShowFlag = ~PModeP2_ShowFlag;//时间闪烁
                P2mode_T = 0;
            }
        }
        else
        {
            P2mode_T = 0;
            PModeP2_Twinkle_Time = 0;
            PModeP2_ShowFlag = 0;//常亮
        }
    }
	else
	{
		PModeP2_ShowFlag = 0;//常亮
		P2mode_T = 0;
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
            if(Temp.Set)
				TempIcn_ShowFlag = ~TempIcn_ShowFlag;//温度图标闪烁;
			else
				TempIcn_ShowFlag = 0;
			if(Time.Rel && (!Temp.Ctrl || TempIcn_ShowFlag != TimeIcn_ShowFlag) && (Temp.Set == 0 || Temp.ADDMode == 3))
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
		
        TempIcn_ShowFlag = 0;//不显示温度图标
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

/**
 * @brief 设置检测
 *
 * @param dT 任务周期
 */
void Check_Setting(float dT)
{
    static float T,T1;
    if(sys.Setting)
    {
        T += dT;
		if (T >= 0.5f)
		{
            Setting_ShowFlag = ~Setting_ShowFlag;
            T = 0;
		}
    }
    else
    {
        T = 0;
        Setting_ShowFlag = 0;
    }
    
    if(sys.Display)
    {
        T1 += dT;
		if (T1 >= 0.5f)
		{
            Hot_ShowFlag = ~Hot_ShowFlag;
            T1 = 0;
		}
    }
    else
    {
        T1 = 0;
        Hot_ShowFlag = 0;
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
    Check_Setting(dT);
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
    uint8_t Val;// 用于百十个取出来的数字
    int16_t Temp_Rel,Temp_Set;
    Temp_Rel = celsiusToFahrenheit(Temp.Unit,Temp.Display_Rel);
    Temp_Set = celsiusToFahrenheit(Temp.Unit,Temp.Display_Set);
    if(sys.Display)
    {
        memset(seg, 0, sizeof(seg));//清空数组   
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 200);//背光pwm
        if(Temp.Rel > 500)
        {
            if(Hot_ShowFlag==0)
            {
                bit_Cal(11, 0x0F, 0x00);bit_Cal(12, 0x0E, 0x00);//H
                bit_Cal(13, 0x0F, 0x00);bit_Cal(14, 0x0E, 0x00);//o
                bit_Cal(15, 0x0F, 0x00);bit_Cal(16, 0x0E, 0x00);//t
            }
            else
            {
                bit_Cal(11, 0x0F, 0x06);bit_Cal(12, 0x0E, 0x0E);//H
                bit_Cal(13, 0x0F, 0x0C);bit_Cal(14, 0x0E, 0x0C);//o
                bit_Cal(15, 0x0F, 0x0E);bit_Cal(16, 0x0E, 0x04);//t
            }
            if (Temp_Rel >= 0)//大于等于0时
            {
                Val = Temp_Rel / 1000 % 10;
            }
            else if (Temp_Rel < 0 && Temp_Rel > -100)
            {
                Val = ABS(Temp_Rel) / 1000 % 10;//计算后是0，不大于999所以不会显示
            }
            else if (Temp_Rel <= -100 && Temp_Rel > -1000)
            {
                Val = 10;//显示“-”
            }
            switch (Val)
            {
                case 0:
                    if (Temp_Rel > 999)//显示0
                    {
                        bit_Cal(0, 0x0F, 0x0F);bit_Cal(1, 0x0E, 0x0A);
                    }
                    else//不显示
                    {
                        bit_Cal(0, 0x0F, 0x00);bit_Cal(1, 0x0E, 0x00);
                    }
                    break;
                case 1:
                    bit_Cal(0, 0x0F, 0x00);bit_Cal(1, 0x0E, 0x0A);
                    break;
                case 2:
                    bit_Cal(0, 0x0F, 0x0D);bit_Cal(1, 0x0E, 0x06);
                    break;
                case 3:
                    bit_Cal(0, 0x0F, 0x09);bit_Cal(1, 0x0E, 0x0E);
                    break;
                case 4:
                    bit_Cal(0, 0x0F, 0x02);bit_Cal(1, 0x0E, 0x0E);
                    break;
                case 5:
                    bit_Cal(0, 0x0F, 0x0B);bit_Cal(1, 0x0E, 0x0C);
                    break;
                case 6:
                    bit_Cal(0, 0x0F, 0x0F);bit_Cal(1, 0x0E, 0x0C);
                    break;
                case 7:
                    bit_Cal(0, 0x0F, 0x01);bit_Cal(1, 0x0E, 0x0A);
                    break;
                case 8:
                    bit_Cal(0, 0x0F, 0x0F);bit_Cal(1, 0x0E, 0x0E);
                    break;
                case 9:
                    bit_Cal(0, 0x0F, 0x0B);bit_Cal(1, 0x0E, 0x0E);
                    break;
                default:
                    bit_Cal(0, 0x0F, 0x00);bit_Cal(1, 0x0E, 0x04);
                    break;
            }
            if (Temp_Rel >= 0)//大于等于0时
            {
                Val = Temp_Rel / 100 % 10;
            }
            else if (Temp_Rel < 0 && Temp_Rel > -100)
            {
                Val = 10;//显示“-”
            }
            else if (Temp_Rel <= -100 && Temp_Rel > -1000)
            {
                Val = ABS(Temp_Rel)/ 100 % 10;
            }
            switch (Val)
            {
                case 0:
                    if (Temp_Rel > 99)//显示零
                    {
                        bit_Cal(2, 0x0F, 0x0F);bit_Cal(3, 0x0E, 0x0A);
                    }
                    else//不显示
                    {
                        bit_Cal(2, 0x0F, 0x00);bit_Cal(3, 0x0E, 0x00);
                    }
                    break;
                case 1:
                    bit_Cal(2, 0x0F, 0x00);bit_Cal(3, 0x0E, 0x0A);
                    break;
                case 2:
                    bit_Cal(2, 0x0F, 0x0D);bit_Cal(3, 0x0E, 0x06);
                    break;
                case 3:
                    bit_Cal(2, 0x0F, 0x09);bit_Cal(3, 0x0E, 0x0E);
                    break;
                case 4:
                    bit_Cal(2, 0x0F, 0x02);bit_Cal(3, 0x0E, 0x0E);
                    break;
                case 5:
                    bit_Cal(2, 0x0F, 0x0B);bit_Cal(3, 0x0E, 0x0C);
                    break;
                case 6:
                    bit_Cal(2, 0x0F, 0x0F);bit_Cal(3, 0x0E, 0x0C);
                    break;
                case 7:
                    bit_Cal(2, 0x0F, 0x01);bit_Cal(3, 0x0E, 0x0A);
                    break;
                case 8:
                    bit_Cal(2, 0x0F, 0x0F);bit_Cal(3, 0x0E, 0x0E);
                    break;
                case 9:
                    bit_Cal(2, 0x0F, 0x0B);bit_Cal(3, 0x0E, 0x0E);
                    break;
                default:
                    bit_Cal(2, 0x0F, 0x00);bit_Cal(3, 0x0E, 0x04);
                    break;
            }
            if (Temp_Rel >= 0)//大于等于0时
            {
                Val = Temp_Rel / 10 % 10;
            }
            else if (Temp_Rel < 0 && Temp_Rel > -100)
            {
                Val = ABS(Temp_Rel) / 10 % 10;
            }
            else if (Temp_Rel <= -100 && Temp_Rel > -1000)
            {
                Val = ABS(Temp_Rel) / 10 % 10;
            }
            switch (Val)
            {
                case 0:
                    bit_Cal(4, 0x0F, 0x0F);bit_Cal(5, 0x0E, 0x0A);
                    break;
                case 1:
                    bit_Cal(4, 0x0F, 0x00);bit_Cal(5, 0x0E, 0x0A);
                    break;
                case 2:
                    bit_Cal(4, 0x0F, 0x0D);bit_Cal(5, 0x0E, 0x06);
                    break;
                case 3:
                    bit_Cal(4, 0x0F, 0x09);bit_Cal(5, 0x0E, 0x0E);
                    break;
                case 4:
                    bit_Cal(4, 0x0F, 0x02);bit_Cal(5, 0x0E, 0x0E);
                    break;
                case 5:
                    bit_Cal(4, 0x0F, 0x0B);bit_Cal(5, 0x0E, 0x0C);
                    break;
                case 6:
                    bit_Cal(4, 0x0F, 0x0F);bit_Cal(5, 0x0E, 0x0C);
                    break;
                case 7:
                    bit_Cal(4, 0x0F, 0x01);bit_Cal(5, 0x0E, 0x0A);
                    break;
                case 8:
                    bit_Cal(4, 0x0F, 0x0F);bit_Cal(5, 0x0E, 0x0E);
                    break;
                case 9:
                    bit_Cal(4, 0x0F, 0x0B);bit_Cal(5, 0x0E, 0x0E);
                    break;
                default:
                    bit_Cal(4, 0x0F, 0x00);bit_Cal(5, 0x0E, 0x04);
                    break;
            }
            
            if (Temp_Rel >= 0)//大于等于0时
            {
                Val = Temp_Rel % 10;
            }
            else if (Temp_Rel < 0 && Temp_Rel > -100)
            {
                Val = ABS(Temp_Rel) % 10;
            }
            else if (Temp_Rel <= -100 && Temp_Rel > -1000)
            {
                Val = ABS(Temp_Rel) % 10;
            }
            switch (Val)
            {
                case 0:
                    bit_Cal(6, 0x0F, 0x0F);bit_Cal(7, 0x0E, 0x0A);
                    break;
                case 1:
                    bit_Cal(6, 0x0F, 0x00);bit_Cal(7, 0x0E, 0x0A);
                    break;
                case 2:
                    bit_Cal(6, 0x0F, 0x0D);bit_Cal(7, 0x0E, 0x06);
                    break;
                case 3:
                    bit_Cal(6, 0x0F, 0x09);bit_Cal(7, 0x0E, 0x0E);
                    break;
                case 4:
                    bit_Cal(6, 0x0F, 0x02);bit_Cal(7, 0x0E, 0x0E);
                    break;
                case 5:
                    bit_Cal(6, 0x0F, 0x0B);bit_Cal(7, 0x0E, 0x0C);
                    break;
                case 6:
                    bit_Cal(6, 0x0F, 0x0F);bit_Cal(7, 0x0E, 0x0C);
                    break;
                case 7:
                    bit_Cal(6, 0x0F, 0x01);bit_Cal(7, 0x0E, 0x0A);
                    break;
                case 8:
                    bit_Cal(6, 0x0F, 0x0F);bit_Cal(7, 0x0E, 0x0E);
                    break;
                case 9:
                    bit_Cal(6, 0x0F, 0x0B);bit_Cal(7, 0x0E, 0x0E);
                    break;
                default:
                    bit_Cal(6, 0x0F, 0x00);bit_Cal(7, 0x0E, 0x04);
                    break;
            }
            if(Temp.Unit==0)
            {
                /**********‘℃’图标**********/
                bit_Cal(7, 0x80, 0x80);
            }
            else
            {
                /**********华氏度℉**********/
                bit_Cal(8, 0x08, 0x00);
            }
        }
        else
        {
            HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 399);//背光pwm
        }
        /**********数据发送**********/
        for(uint8_t i=0;i<27;i++)
        {
            Write_Addr_Dat_N(i*2, seg[i], 1);
        }
    }
    else if(sys.Setting) 
    {
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 200);//背光pwm
        memset(seg, 0, sizeof(seg));//清空数组     
        
        if(Temp.Up_Speed == 0)
        {
            if(Setting_ShowFlag && sys.Setting_Option == 0)
            {
                /**********加热图标**********/
                bit_Cal(8, 0x02, 0x00);
                bit_Cal(3, 0x01, 0x00);//加热图标下面的横杠
            }
            else
            {
                /**********加热图标**********/
                bit_Cal(8, 0x02, 0x02);
                bit_Cal(3, 0x01, 0x01);//加热图标下面的横杠
            }
        }
        else if(Temp.Up_Speed == 1)
        {
            if(Setting_ShowFlag && sys.Setting_Option == 0)
            {
                /**********加热图标旁边的H**********/
                bit_Cal(8, 0x04, 0x00);
            }
            else
            {
                /**********加热图标旁边的H**********/
                bit_Cal(8, 0x04, 0x04);
            }
            /**********加热图标**********/
            bit_Cal(8, 0x02, 0x02);
            bit_Cal(3, 0x01, 0x01);//加热图标下面的横杠
        }
        else if(Temp.Up_Speed == 2)
        {
            if(Setting_ShowFlag && sys.Setting_Option == 0)
            {
                /**********加热图标旁边的L**********/
                bit_Cal(9, 0x02, 0x00);
            }
            else
            {
                /**********加热图标旁边的L**********/
                bit_Cal(9, 0x02, 0x02);
            }
            /**********加热图标**********/
            bit_Cal(8, 0x02, 0x02);
            bit_Cal(3, 0x01, 0x01);//加热图标下面的横杠
        }
              
        
        if(Speed.Up_Speed == 0)
        {
            if(Setting_ShowFlag && sys.Setting_Option == 1)
            {
                /**********转速图标**********/
                bit_Cal(12, 0x01, 0x00);//S5
                bit_Cal(10, 0x01, 0x00);//S4
                bit_Cal(10, 0x02, 0x00);//S3
            }
            else
            {
                /**********转速图标**********/
                bit_Cal(12, 0x01, 0x01);//S5
                bit_Cal(10, 0x01, 0x01);//S4
                bit_Cal(10, 0x02, 0x02);//S3
            }
        }
        else if(Speed.Up_Speed == 1)
        {
            if(Setting_ShowFlag && sys.Setting_Option == 1)
            {
                /**********转速图标旁边的H**********/
                bit_Cal(9, 0x08, 0x00);
            }
            else
            {
                /**********转速图标旁边的H**********/
                bit_Cal(9, 0x08, 0x08);
            }
            /**********转速图标**********/
            bit_Cal(12, 0x01, 0x01);//S5
            bit_Cal(10, 0x01, 0x01);//S4
            bit_Cal(10, 0x02, 0x02);//S3
        }
        else if(Speed.Up_Speed == 2)
        {
            if(Setting_ShowFlag && sys.Setting_Option == 1)
            {
                /**********转速图标旁边的L**********/
                bit_Cal(17, 0x01, 0x00);
            }
            else
            {
                /**********转速图标旁边的L**********/
                bit_Cal(17, 0x01, 0x01);
            }
            /**********转速图标**********/
            bit_Cal(12, 0x01, 0x01);//S5
            bit_Cal(10, 0x01, 0x01);//S4
            bit_Cal(10, 0x02, 0x02);//S3
        }
        
        if(Temp.Unit == 0)//℃
        {
            if(Setting_ShowFlag && sys.Setting_Option == 4)
            {
                /**********‘℃’图标**********/
                bit_Cal(7, 0x80, 0x00);
            }
            else
            {
                /**********‘℃’图标**********/
                bit_Cal(7, 0x80, 0x80);
            }
            /**********华氏度℉**********/
            bit_Cal(8, 0x08, 0x00);
        }
        else if(Temp.Unit == 1)//℉
        {
            if(Setting_ShowFlag && sys.Setting_Option == 4)
            {
                /**********华氏度℉**********/
                bit_Cal(8, 0x08, 0x00);
            }
            else
            {
                /**********华氏度℉**********/
                bit_Cal(8, 0x08, 0x08);
            }
            /**********‘℃’图标**********/
            bit_Cal(7, 0x80, 0x00);
        }
        
        if(Setting_ShowFlag && sys.Setting_Option == 3)
        {
            /**********'SAFE'图标**********/
            bit_Cal(1, 0x80, 0x00);
        }
        else
        {
            /**********'SAFE'图标**********/
            bit_Cal(1, 0x80, 0x80);
        }
        
        if(Setting_ShowFlag && sys.Setting_Option == 2)
        {
            bit_Cal(18, 0x0F, 0x00);bit_Cal(17, 0x0E, 0x00);//显示C
            bit_Cal(11, 0x0F, 0x00);bit_Cal(12, 0x0E, 0x00);//1
            bit_Cal(11, 0x0F, 0x00);bit_Cal(12, 0x0E, 0x00);//2
        }
        else
        {
            bit_Cal(18, 0x0F, 0x0F);bit_Cal(17, 0x0E, 0x00);//显示C
            if(sys.DownTime_Type == C1)
            {
                bit_Cal(11, 0x0F, 0x00);bit_Cal(12, 0x0E, 0x0A);//1
            }
            else
            {
                bit_Cal(11, 0x0F, 0x0D);bit_Cal(12, 0x0E, 0x06);//2
            }     
        }
        
        if (Temp.Safe_Temp >= 0)//大于等于0时
        {
            Val = Temp.Safe_Temp / 1000 % 10;
        }
        else if (Temp.Safe_Temp < 0 && Temp.Safe_Temp > -100)
        {
            Val = ABS(Temp.Safe_Temp) / 1000 % 10;//计算后是0，不大于999所以不会显示
        }
        else if (Temp.Safe_Temp <= -100 && Temp.Safe_Temp > -1000)
        {
            Val = 10;//显示“-”
        }
        switch (Val)
        {
            case 0:
                if (Temp.Safe_Temp > 999)//显示零
                {
                    bit_Cal(0, 0xF0, 0xF0);bit_Cal(1, 0x70, 0x50);
                }
                else//不显示
                {
                    bit_Cal(0, 0xF0, 0x00);bit_Cal(1, 0x70, 0x00);
                }
                break;
            case 1:
                bit_Cal(0, 0xF0, 0x00);bit_Cal(1, 0x70, 0x50);
                break;
            case 2:
                bit_Cal(0, 0xF0, 0xD0);bit_Cal(1, 0x70, 0x30);
                break;
            case 3:
                bit_Cal(0, 0xF0, 0x90);bit_Cal(1, 0x70, 0x70);
                break;
            case 4:
                bit_Cal(0, 0xF0, 0x20);bit_Cal(1, 0x70, 0x70);
                break;
            case 5:
                bit_Cal(0, 0xF0, 0xB0);bit_Cal(1, 0x70, 0x60);
                break;
            case 6:
                bit_Cal(0, 0xF0, 0xF0);bit_Cal(1, 0x70, 0x60);
                break;
            case 7:
                bit_Cal(0, 0xF0, 0x10);bit_Cal(1, 0x70, 0x50);
                break;
            case 8:
                bit_Cal(0, 0xF0, 0xF0);bit_Cal(1, 0x70, 0x70);
                break;
            case 9:
                bit_Cal(0, 0xF0, 0xB0);bit_Cal(1, 0x70, 0x70);
                break;
            default:
                bit_Cal(0, 0xF0, 0x00);bit_Cal(1, 0x70, 0x20);
                break;
        }
        
        if (Temp.Safe_Temp >= 0)//大于等于0时
        {
            Val = Temp.Safe_Temp / 100 % 10;
        }
        else if (Temp.Safe_Temp < 0 && Temp.Safe_Temp > -100)
        {
            Val = 10;//显示“-”
        }
        else if (Temp.Safe_Temp <= -100 && Temp.Safe_Temp > -1000)
        {
            Val = ABS(Temp.Safe_Temp)/ 100 % 10;
        }
        switch (Val)
        {
            case 0:
                if (Temp.Safe_Temp > 99)//显示零
                {
                    bit_Cal(2, 0xF0, 0xF0);bit_Cal(3, 0x70, 0x50);
                }
                else//不显示
                {
                    bit_Cal(2, 0xF0, 0x00);bit_Cal(3, 0x70, 0x00);
                }
                break;
            case 1:
                bit_Cal(2, 0xF0, 0x00);bit_Cal(3, 0x70, 0x50);
                break;
            case 2:
                bit_Cal(2, 0xF0, 0xD0);bit_Cal(3, 0x70, 0x30);
                break;
            case 3:
                bit_Cal(2, 0xF0, 0x90);bit_Cal(3, 0x70, 0x70);
                break;
            case 4:
                bit_Cal(2, 0xF0, 0x20);bit_Cal(3, 0x70, 0x70);
                break;
            case 5:
                bit_Cal(2, 0xF0, 0xB0);bit_Cal(3, 0x70, 0x60);
                break;
            case 6:
                bit_Cal(2, 0xF0, 0xF0);bit_Cal(3, 0x70, 0x60);
                break;
            case 7:
                bit_Cal(2, 0xF0, 0x10);bit_Cal(3, 0x70, 0x50);
                break;
            case 8:
                bit_Cal(2, 0xF0, 0xF0);bit_Cal(3, 0x70, 0x70);
                break;
            case 9:
                bit_Cal(2, 0xF0, 0xB0);bit_Cal(3, 0x70, 0x70);
                break;
            default:
                bit_Cal(2, 0xF0, 0x00);bit_Cal(3, 0x70, 0x20);
                break;
        }
        
        if (Temp.Safe_Temp >= 0)//大于等于0时
        {
            Val = Temp.Safe_Temp / 10 % 10;
        }
        else if (Temp.Safe_Temp < 0 && Temp.Safe_Temp > -100)
        {
            Val = ABS(Temp.Safe_Temp) / 10 % 10;
        }
        else if (Temp.Safe_Temp <= -100 && Temp.Safe_Temp > -1000)
        {
            Val = ABS(Temp.Safe_Temp) / 10 % 10;
        }
        switch (Val)
        {
            case 0:
                bit_Cal(4, 0xF0, 0xF0);bit_Cal(5, 0x70, 0x50);
                break;
            case 1:
                bit_Cal(4, 0xF0, 0x00);bit_Cal(5, 0x70, 0x50);
                break;
            case 2:
                bit_Cal(4, 0xF0, 0xD0);bit_Cal(5, 0x70, 0x30);
                break;
            case 3:
                bit_Cal(4, 0xF0, 0x90);bit_Cal(5, 0x70, 0x70);
                break;
            case 4:
                bit_Cal(4, 0xF0, 0x20);bit_Cal(5, 0x70, 0x70);
                break;
            case 5:
                bit_Cal(4, 0xF0, 0xB0);bit_Cal(5, 0x70, 0x60);
                break;
            case 6:
                bit_Cal(4, 0xF0, 0xF0);bit_Cal(5, 0x70, 0x60);
                break;
            case 7:
                bit_Cal(4, 0xF0, 0x10);bit_Cal(5, 0x70, 0x50);
                break;
            case 8:
                bit_Cal(4, 0xF0, 0xF0);bit_Cal(5, 0x70, 0x70);
                break;
            case 9:
                bit_Cal(4, 0xF0, 0xB0);bit_Cal(5, 0x70, 0x70);
                break;
            default:
                bit_Cal(4, 0xF0, 0x00);bit_Cal(5, 0x70, 0x20);
                break;
        }
        
        if (Temp.Safe_Temp >= 0)//大于等于0时
        {
            Val = Temp.Safe_Temp % 10;
        }
        else if (Temp.Safe_Temp < 0 && Temp.Safe_Temp > -100)
        {
            Val = ABS(Temp.Safe_Temp) % 10;
        }
        else if (Temp.Safe_Temp <= -100 && Temp.Safe_Temp > -1000)
        {
            Val = ABS(Temp.Safe_Temp) % 10;
        }
        switch (Val)
        {
            case 0:
                bit_Cal(6, 0xF0, 0xF0);bit_Cal(7, 0x70, 0x50);
                break;
            case 1:
                bit_Cal(6, 0xF0, 0x00);bit_Cal(7, 0x70, 0x50);
                break;
            case 2:
                bit_Cal(6, 0xF0, 0xD0);bit_Cal(7, 0x70, 0x30);
                break;
            case 3:
                bit_Cal(6, 0xF0, 0x90);bit_Cal(7, 0x70, 0x70);
                break;
            case 4:
                bit_Cal(6, 0xF0, 0x20);bit_Cal(7, 0x70, 0x70);
                break;
            case 5:
                bit_Cal(6, 0xF0, 0xB0);bit_Cal(7, 0x70, 0x60);
                break;
            case 6:
                bit_Cal(6, 0xF0, 0xF0);bit_Cal(7, 0x70, 0x60);
                break;
            case 7:
                bit_Cal(6, 0xF0, 0x10);bit_Cal(7, 0x70, 0x50);
                break;
            case 8:
                bit_Cal(6, 0xF0, 0xF0);bit_Cal(7, 0x70, 0x70);
                break;
            case 9:
                bit_Cal(6, 0xF0, 0xB0);bit_Cal(7, 0x70, 0x70);
                break;
            default:
                bit_Cal(6, 0xF0, 0x00);bit_Cal(7, 0x70, 0x20);
                break;
        }
        
        /**********设定温度小数点**********/
        bit_Cal(5, 0x80, 0x80);
        /**********数据发送**********/
        for(uint8_t i=0;i<27;i++)
        {
            Write_Addr_Dat_N(i*2, seg[i], 1);
        }
    }
    else
    {
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 200);//背光pwm
        memset(seg, 0, sizeof(seg));//清空数组        
        if (Temp_Rel >= 0)//大于等于0时
        {
            Val = Temp_Rel / 1000 % 10;
        }
        else if (Temp_Rel < 0 && Temp_Rel > -100)
        {
            Val = ABS(Temp_Rel) / 1000 % 10;//计算后是0，不大于999所以不会显示
        }
        else if (Temp_Rel <= -100 && Temp_Rel > -1000)
        {
            Val = 10;//显示“-”
        }
        switch (Val)
        {
            case 0:
                if (Temp_Rel > 999)//显示0
                {
                    bit_Cal(0, 0x0F, 0x0F);bit_Cal(1, 0x0E, 0x0A);
                }
                else//不显示
                {
                    bit_Cal(0, 0x0F, 0x00);bit_Cal(1, 0x0E, 0x00);
                }
                break;
            case 1:
                bit_Cal(0, 0x0F, 0x00);bit_Cal(1, 0x0E, 0x0A);
                break;
            case 2:
                bit_Cal(0, 0x0F, 0x0D);bit_Cal(1, 0x0E, 0x06);
                break;
            case 3:
                bit_Cal(0, 0x0F, 0x09);bit_Cal(1, 0x0E, 0x0E);
                break;
            case 4:
                bit_Cal(0, 0x0F, 0x02);bit_Cal(1, 0x0E, 0x0E);
                break;
            case 5:
                bit_Cal(0, 0x0F, 0x0B);bit_Cal(1, 0x0E, 0x0C);
                break;
            case 6:
                bit_Cal(0, 0x0F, 0x0F);bit_Cal(1, 0x0E, 0x0C);
                break;
            case 7:
                bit_Cal(0, 0x0F, 0x01);bit_Cal(1, 0x0E, 0x0A);
                break;
            case 8:
                bit_Cal(0, 0x0F, 0x0F);bit_Cal(1, 0x0E, 0x0E);
                break;
            case 9:
                bit_Cal(0, 0x0F, 0x0B);bit_Cal(1, 0x0E, 0x0E);
                break;
            default:
                bit_Cal(0, 0x0F, 0x00);bit_Cal(1, 0x0E, 0x04);
                break;
        }
        if (Temp_Rel >= 0)//大于等于0时
        {
            Val = Temp_Rel / 100 % 10;
        }
        else if (Temp_Rel < 0 && Temp_Rel > -100)
        {
            Val = 10;//显示“-”
        }
        else if (Temp_Rel <= -100 && Temp_Rel > -1000)
        {
            Val = ABS(Temp_Rel)/ 100 % 10;
        }
        switch (Val)
        {
            case 0:
                if (Temp_Rel > 99)//显示零
                {
                    bit_Cal(2, 0x0F, 0x0F);bit_Cal(3, 0x0E, 0x0A);
                }
                else//不显示
                {
                    bit_Cal(2, 0x0F, 0x00);bit_Cal(3, 0x0E, 0x00);
                }
                break;
            case 1:
                bit_Cal(2, 0x0F, 0x00);bit_Cal(3, 0x0E, 0x0A);
                break;
            case 2:
                bit_Cal(2, 0x0F, 0x0D);bit_Cal(3, 0x0E, 0x06);
                break;
            case 3:
                bit_Cal(2, 0x0F, 0x09);bit_Cal(3, 0x0E, 0x0E);
                break;
            case 4:
                bit_Cal(2, 0x0F, 0x02);bit_Cal(3, 0x0E, 0x0E);
                break;
            case 5:
                bit_Cal(2, 0x0F, 0x0B);bit_Cal(3, 0x0E, 0x0C);
                break;
            case 6:
                bit_Cal(2, 0x0F, 0x0F);bit_Cal(3, 0x0E, 0x0C);
                break;
            case 7:
                bit_Cal(2, 0x0F, 0x01);bit_Cal(3, 0x0E, 0x0A);
                break;
            case 8:
                bit_Cal(2, 0x0F, 0x0F);bit_Cal(3, 0x0E, 0x0E);
                break;
            case 9:
                bit_Cal(2, 0x0F, 0x0B);bit_Cal(3, 0x0E, 0x0E);
                break;
            default:
                bit_Cal(2, 0x0F, 0x00);bit_Cal(3, 0x0E, 0x04);
                break;
        }
        if (Temp_Rel >= 0)//大于等于0时
        {
            Val = Temp_Rel / 10 % 10;
        }
        else if (Temp_Rel < 0 && Temp_Rel > -100)
        {
            Val = ABS(Temp_Rel) / 10 % 10;
        }
        else if (Temp_Rel <= -100 && Temp_Rel > -1000)
        {
            Val = ABS(Temp_Rel) / 10 % 10;
        }
        switch (Val)
        {
            case 0:
                bit_Cal(4, 0x0F, 0x0F);bit_Cal(5, 0x0E, 0x0A);
                break;
            case 1:
                bit_Cal(4, 0x0F, 0x00);bit_Cal(5, 0x0E, 0x0A);
                break;
            case 2:
                bit_Cal(4, 0x0F, 0x0D);bit_Cal(5, 0x0E, 0x06);
                break;
            case 3:
                bit_Cal(4, 0x0F, 0x09);bit_Cal(5, 0x0E, 0x0E);
                break;
            case 4:
                bit_Cal(4, 0x0F, 0x02);bit_Cal(5, 0x0E, 0x0E);
                break;
            case 5:
                bit_Cal(4, 0x0F, 0x0B);bit_Cal(5, 0x0E, 0x0C);
                break;
            case 6:
                bit_Cal(4, 0x0F, 0x0F);bit_Cal(5, 0x0E, 0x0C);
                break;
            case 7:
                bit_Cal(4, 0x0F, 0x01);bit_Cal(5, 0x0E, 0x0A);
                break;
            case 8:
                bit_Cal(4, 0x0F, 0x0F);bit_Cal(5, 0x0E, 0x0E);
                break;
            case 9:
                bit_Cal(4, 0x0F, 0x0B);bit_Cal(5, 0x0E, 0x0E);
                break;
            default:
                bit_Cal(4, 0x0F, 0x00);bit_Cal(5, 0x0E, 0x04);
                break;
        }
        
        if (Temp_Rel >= 0)//大于等于0时
        {
            Val = Temp_Rel % 10;
        }
        else if (Temp_Rel < 0 && Temp_Rel > -100)
        {
            Val = ABS(Temp_Rel) % 10;
        }
        else if (Temp_Rel <= -100 && Temp_Rel > -1000)
        {
            Val = ABS(Temp_Rel) % 10;
        }
        switch (Val)
        {
            case 0:
                bit_Cal(6, 0x0F, 0x0F);bit_Cal(7, 0x0E, 0x0A);
                break;
            case 1:
                bit_Cal(6, 0x0F, 0x00);bit_Cal(7, 0x0E, 0x0A);
                break;
            case 2:
                bit_Cal(6, 0x0F, 0x0D);bit_Cal(7, 0x0E, 0x06);
                break;
            case 3:
                bit_Cal(6, 0x0F, 0x09);bit_Cal(7, 0x0E, 0x0E);
                break;
            case 4:
                bit_Cal(6, 0x0F, 0x02);bit_Cal(7, 0x0E, 0x0E);
                break;
            case 5:
                bit_Cal(6, 0x0F, 0x0B);bit_Cal(7, 0x0E, 0x0C);
                break;
            case 6:
                bit_Cal(6, 0x0F, 0x0F);bit_Cal(7, 0x0E, 0x0C);
                break;
            case 7:
                bit_Cal(6, 0x0F, 0x01);bit_Cal(7, 0x0E, 0x0A);
                break;
            case 8:
                bit_Cal(6, 0x0F, 0x0F);bit_Cal(7, 0x0E, 0x0E);
                break;
            case 9:
                bit_Cal(6, 0x0F, 0x0B);bit_Cal(7, 0x0E, 0x0E);
                break;
            default:
                bit_Cal(6, 0x0F, 0x00);bit_Cal(7, 0x0E, 0x04);
                break;
        }
        /**********设定温度**********/
        if(Temp_ShowFlag)
        {
            bit_Cal(0, 0xF0, 0x00);bit_Cal(1, 0x70, 0x00);//不显示
            bit_Cal(2, 0xF0, 0x00);bit_Cal(3, 0x70, 0x00);//不显示
            bit_Cal(4, 0xF0, 0x00);bit_Cal(5, 0x70, 0x00);//不显示
            bit_Cal(6, 0xF0, 0x00);bit_Cal(7, 0x70, 0x00);//不显示
        }
        else
        {
            if(Temp_Set == 0)
            {
                bit_Cal(0, 0xF0, 0x00);bit_Cal(1, 0x70, 0x20);//显示“-”
                bit_Cal(2, 0xF0, 0x00);bit_Cal(3, 0x70, 0x20);//显示“-”
                bit_Cal(4, 0xF0, 0x00);bit_Cal(5, 0x70, 0x20);//显示“-”
                bit_Cal(6, 0xF0, 0x00);bit_Cal(7, 0x70, 0x20);//显示“-”
            }
            else
            {
                if (Temp_Set >= 0)//大于等于0时
                {
                    Val = Temp_Set / 1000 % 10;
                }
                else if (Temp_Set < 0 && Temp_Set > -100)
                {
                    Val = ABS(Temp_Set) / 1000 % 10;//计算后是0，不大于999所以不会显示
                }
                else if (Temp_Set <= -100 && Temp_Set > -1000)
                {
                    Val = 10;//显示“-”
                }
                switch (Val)
                {
                    case 0:
                        if (Temp_Set > 999)//显示零
                        {
                            bit_Cal(0, 0xF0, 0xF0);bit_Cal(1, 0x70, 0x50);
                        }
                        else//不显示
                        {
                            bit_Cal(0, 0xF0, 0x00);bit_Cal(1, 0x70, 0x00);
                        }
                        break;
                    case 1:
                        bit_Cal(0, 0xF0, 0x00);bit_Cal(1, 0x70, 0x50);
                        break;
                    case 2:
                        bit_Cal(0, 0xF0, 0xD0);bit_Cal(1, 0x70, 0x30);
                        break;
                    case 3:
                        bit_Cal(0, 0xF0, 0x90);bit_Cal(1, 0x70, 0x70);
                        break;
                    case 4:
                        bit_Cal(0, 0xF0, 0x20);bit_Cal(1, 0x70, 0x70);
                        break;
                    case 5:
                        bit_Cal(0, 0xF0, 0xB0);bit_Cal(1, 0x70, 0x60);
                        break;
                    case 6:
                        bit_Cal(0, 0xF0, 0xF0);bit_Cal(1, 0x70, 0x60);
                        break;
                    case 7:
                        bit_Cal(0, 0xF0, 0x10);bit_Cal(1, 0x70, 0x50);
                        break;
                    case 8:
                        bit_Cal(0, 0xF0, 0xF0);bit_Cal(1, 0x70, 0x70);
                        break;
                    case 9:
                        bit_Cal(0, 0xF0, 0xB0);bit_Cal(1, 0x70, 0x70);
                        break;
                    default:
                        bit_Cal(0, 0xF0, 0x00);bit_Cal(1, 0x70, 0x20);
                        break;
                }
                
                if (Temp_Set >= 0)//大于等于0时
                {
                    Val = Temp_Set / 100 % 10;
                }
                else if (Temp_Set < 0 && Temp_Set > -100)
                {
                    Val = 10;//显示“-”
                }
                else if (Temp_Set <= -100 && Temp_Set > -1000)
                {
                    Val = ABS(Temp_Set)/ 100 % 10;
                }
                switch (Val)
                {
                    case 0:
                        if (Temp_Set > 99)//显示零
                        {
                            bit_Cal(2, 0xF0, 0xF0);bit_Cal(3, 0x70, 0x50);
                        }
                        else//不显示
                        {
                            bit_Cal(2, 0xF0, 0x00);bit_Cal(3, 0x70, 0x00);
                        }
                        break;
                    case 1:
                        bit_Cal(2, 0xF0, 0x00);bit_Cal(3, 0x70, 0x50);
                        break;
                    case 2:
                        bit_Cal(2, 0xF0, 0xD0);bit_Cal(3, 0x70, 0x30);
                        break;
                    case 3:
                        bit_Cal(2, 0xF0, 0x90);bit_Cal(3, 0x70, 0x70);
                        break;
                    case 4:
                        bit_Cal(2, 0xF0, 0x20);bit_Cal(3, 0x70, 0x70);
                        break;
                    case 5:
                        bit_Cal(2, 0xF0, 0xB0);bit_Cal(3, 0x70, 0x60);
                        break;
                    case 6:
                        bit_Cal(2, 0xF0, 0xF0);bit_Cal(3, 0x70, 0x60);
                        break;
                    case 7:
                        bit_Cal(2, 0xF0, 0x10);bit_Cal(3, 0x70, 0x50);
                        break;
                    case 8:
                        bit_Cal(2, 0xF0, 0xF0);bit_Cal(3, 0x70, 0x70);
                        break;
                    case 9:
                        bit_Cal(2, 0xF0, 0xB0);bit_Cal(3, 0x70, 0x70);
                        break;
                    default:
                        bit_Cal(2, 0xF0, 0x00);bit_Cal(3, 0x70, 0x20);
                        break;
                }
                
                if (Temp_Set >= 0)//大于等于0时
                {
                    Val = Temp_Set / 10 % 10;
                }
                else if (Temp_Set < 0 && Temp_Set > -100)
                {
                    Val = ABS(Temp_Set) / 10 % 10;
                }
                else if (Temp_Set <= -100 && Temp_Set > -1000)
                {
                    Val = ABS(Temp_Set) / 10 % 10;
                }
                switch (Val)
                {
                    case 0:
                        bit_Cal(4, 0xF0, 0xF0);bit_Cal(5, 0x70, 0x50);
                        break;
                    case 1:
                        bit_Cal(4, 0xF0, 0x00);bit_Cal(5, 0x70, 0x50);
                        break;
                    case 2:
                        bit_Cal(4, 0xF0, 0xD0);bit_Cal(5, 0x70, 0x30);
                        break;
                    case 3:
                        bit_Cal(4, 0xF0, 0x90);bit_Cal(5, 0x70, 0x70);
                        break;
                    case 4:
                        bit_Cal(4, 0xF0, 0x20);bit_Cal(5, 0x70, 0x70);
                        break;
                    case 5:
                        bit_Cal(4, 0xF0, 0xB0);bit_Cal(5, 0x70, 0x60);
                        break;
                    case 6:
                        bit_Cal(4, 0xF0, 0xF0);bit_Cal(5, 0x70, 0x60);
                        break;
                    case 7:
                        bit_Cal(4, 0xF0, 0x10);bit_Cal(5, 0x70, 0x50);
                        break;
                    case 8:
                        bit_Cal(4, 0xF0, 0xF0);bit_Cal(5, 0x70, 0x70);
                        break;
                    case 9:
                        bit_Cal(4, 0xF0, 0xB0);bit_Cal(5, 0x70, 0x70);
                        break;
                    default:
                        bit_Cal(4, 0xF0, 0x00);bit_Cal(5, 0x70, 0x20);
                        break;
                }
                
                if (Temp_Set >= 0)//大于等于0时
                {
                    Val = Temp_Set % 10;
                }
                else if (Temp_Set < 0 && Temp_Set > -100)
                {
                    Val = ABS(Temp_Set) % 10;
                }
                else if (Temp_Set <= -100 && Temp_Set > -1000)
                {
                    Val = ABS(Temp_Set) % 10;
                }
                switch (Val)
                {
                    case 0:
                        bit_Cal(6, 0xF0, 0xF0);bit_Cal(7, 0x70, 0x50);
                        break;
                    case 1:
                        bit_Cal(6, 0xF0, 0x00);bit_Cal(7, 0x70, 0x50);
                        break;
                    case 2:
                        bit_Cal(6, 0xF0, 0xD0);bit_Cal(7, 0x70, 0x30);
                        break;
                    case 3:
                        bit_Cal(6, 0xF0, 0x90);bit_Cal(7, 0x70, 0x70);
                        break;
                    case 4:
                        bit_Cal(6, 0xF0, 0x20);bit_Cal(7, 0x70, 0x70);
                        break;
                    case 5:
                        bit_Cal(6, 0xF0, 0xB0);bit_Cal(7, 0x70, 0x60);
                        break;
                    case 6:
                        bit_Cal(6, 0xF0, 0xF0);bit_Cal(7, 0x70, 0x60);
                        break;
                    case 7:
                        bit_Cal(6, 0xF0, 0x10);bit_Cal(7, 0x70, 0x50);
                        break;
                    case 8:
                        bit_Cal(6, 0xF0, 0xF0);bit_Cal(7, 0x70, 0x70);
                        break;
                    case 9:
                        bit_Cal(6, 0xF0, 0xB0);bit_Cal(7, 0x70, 0x70);
                        break;
                    default:
                        bit_Cal(6, 0xF0, 0x00);bit_Cal(7, 0x70, 0x20);
                        break;
                }
            }
        }
        
        /**********实际转速显示**********/
        if (Speed.Display_Rel > 999) // 大于999时
        {
            Val = Speed.Display_Rel / 1000 % 10;
            switch (Val)
            {
                case 0:
                    bit_Cal(18, 0x0F, 0x0F);bit_Cal(17, 0x0E, 0x0A);
                    break;
                case 1:
                    bit_Cal(18, 0x0F, 0x00);bit_Cal(17, 0x0E, 0x0A);
                    break;
                case 2:
                    bit_Cal(18, 0x0F, 0x0D);bit_Cal(17, 0x0E, 0x06);
                    break;
                case 3:
                    bit_Cal(18, 0x0F, 0x09);bit_Cal(17, 0x0E, 0x0E);
                    break;
                case 4:
                    bit_Cal(18, 0x0F, 0x02);bit_Cal(17, 0x0E, 0x0E);
                    break;
                case 5:
                    bit_Cal(18, 0x0F, 0x0B);bit_Cal(17, 0x0E, 0x0C);
                    break;
                case 6:
                    bit_Cal(18, 0x0F, 0x0F);bit_Cal(17, 0x0E, 0x0C);
                    break;
                case 7:
                    bit_Cal(18, 0x0F, 0x01);bit_Cal(17, 0x0E, 0x0A);
                    break;
                case 8:
                    bit_Cal(18, 0x0F, 0x0F);bit_Cal(17, 0x0E, 0x0E);
                    break;
                case 9:
                    bit_Cal(18, 0x0F, 0x0B);bit_Cal(17, 0x0E, 0x0E);
                    break;
                default:
                    bit_Cal(18, 0x0F, 0x00);bit_Cal(17, 0x0E, 0x04);
                    break;
            }
        }
        else
        {
            bit_Cal(18, 0x0F, 0x0F);bit_Cal(17, 0x0E, 0x0A);//显示数字0
        }
            
        if (Speed.Display_Rel > 99) // 大于99时
        {
            Val = Speed.Display_Rel / 100 % 10;
            switch (Val)
            {
                case 0:
                    bit_Cal(11, 0x0F, 0x0F);bit_Cal(12, 0x0E, 0x0A);
                    break;
                case 1:
                    bit_Cal(11, 0x0F, 0x00);bit_Cal(12, 0x0E, 0x0A);
                    break;
                case 2:
                    bit_Cal(11, 0x0F, 0x0D);bit_Cal(12, 0x0E, 0x06);
                    break;
                case 3:
                    bit_Cal(11, 0x0F, 0x09);bit_Cal(12, 0x0E, 0x0E);
                    break;
                case 4:
                    bit_Cal(11, 0x0F, 0x02);bit_Cal(12, 0x0E, 0x0E);
                    break;
                case 5:
                    bit_Cal(11, 0x0F, 0x0B);bit_Cal(12, 0x0E, 0x0C);
                    break;
                case 6:
                    bit_Cal(11, 0x0F, 0x0F);bit_Cal(12, 0x0E, 0x0C);
                    break;
                case 7:
                    bit_Cal(11, 0x0F, 0x01);bit_Cal(12, 0x0E, 0x0A);
                    break;
                case 8:
                    bit_Cal(11, 0x0F, 0x0F);bit_Cal(12, 0x0E, 0x0E);
                    break;
                case 9:
                    bit_Cal(11, 0x0F, 0x0B);bit_Cal(12, 0x0E, 0x0E);
                    break;
                default:
                    bit_Cal(11, 0x0F, 0x00);bit_Cal(12, 0x0E, 0x04);
                    break;
            }
        }
        else
        {
            bit_Cal(11, 0x0F, 0x0F);bit_Cal(12, 0x0E, 0x0A);//显示数字零
        }
        if (Speed.Display_Rel > 9) // 大于9时
        {
            Val = Speed.Display_Rel / 10 % 10;
            switch (Val)
            {
                case 0:
                    bit_Cal(13, 0x0F, 0x0F);bit_Cal(14, 0x0E, 0x0A);
                    break;
                case 1:
                    bit_Cal(13, 0x0F, 0x00);bit_Cal(14, 0x0E, 0x0A);
                    break;
                case 2:
                    bit_Cal(13, 0x0F, 0x0D);bit_Cal(14, 0x0E, 0x06);
                    break;
                case 3:
                    bit_Cal(13, 0x0F, 0x09);bit_Cal(14, 0x0E, 0x0E);
                    break;
                case 4:
                    bit_Cal(13, 0x0F, 0x02);bit_Cal(14, 0x0E, 0x0E);
                    break;
                case 5:
                    bit_Cal(13, 0x0F, 0x0B);bit_Cal(14, 0x0E, 0x0C);
                    break;
                case 6:
                    bit_Cal(13, 0x0F, 0x0F);bit_Cal(14, 0x0E, 0x0C);
                    break;
                case 7:
                    bit_Cal(13, 0x0F, 0x01);bit_Cal(14, 0x0E, 0x0A);
                    break;
                case 8:
                    bit_Cal(13, 0x0F, 0x0F);bit_Cal(14, 0x0E, 0x0E);
                    break;
                case 9:
                    bit_Cal(13, 0x0F, 0x0B);bit_Cal(14, 0x0E, 0x0E);
                    break;
                default:
                    bit_Cal(13, 0x0F, 0x00);bit_Cal(14, 0x0E, 0x04);
                    break;
            }
        }
        else
        {
            bit_Cal(13, 0x0F, 0x0F);bit_Cal(14, 0x0E, 0x0A);//显示数字零
        }
        
        Val = Speed.Display_Rel % 10;
        switch (Val)
        {
            case 0:
                bit_Cal(15, 0x0F, 0x0F);bit_Cal(16, 0x0E, 0x0A);
                break;
            case 1:
                bit_Cal(15, 0x0F, 0x00);bit_Cal(16, 0x0E, 0x0A);
                break;
            case 2:
                bit_Cal(15, 0x0F, 0x0D);bit_Cal(16, 0x0E, 0x06);
                break;
            case 3:
                bit_Cal(15, 0x0F, 0x09);bit_Cal(16, 0x0E, 0x0E);
                break;
            case 4:
                bit_Cal(15, 0x0F, 0x02);bit_Cal(16, 0x0E, 0x0E);
                break;
            case 5:
                bit_Cal(15, 0x0F, 0x0B);bit_Cal(16, 0x0E, 0x0C);
                break;
            case 6:
                bit_Cal(15, 0x0F, 0x0F);bit_Cal(16, 0x0E, 0x0C);
                break;
            case 7:
                bit_Cal(15, 0x0F, 0x01);bit_Cal(16, 0x0E, 0x0A);
                break;
            case 8:
                bit_Cal(15, 0x0F, 0x0F);bit_Cal(16, 0x0E, 0x0E);
                break;
            case 9:
                bit_Cal(15, 0x0F, 0x0B);bit_Cal(16, 0x0E, 0x0E);
                break;
            default:
                bit_Cal(15, 0x0F, 0x00);bit_Cal(16, 0x0E, 0x04);
                break;
        }
        
        /**********设定转速显示**********/
        if(Speed_ShowFlag)
        {
            bit_Cal(18, 0xF0, 0x00);bit_Cal(17, 0x70, 0x00);//不显示
            bit_Cal(11, 0xF0, 0x00);bit_Cal(12, 0x70, 0x00);//不显示
            bit_Cal(13, 0xF0, 0x00);bit_Cal(14, 0x70, 0x00);//不显示
            bit_Cal(15, 0xF0, 0x00);bit_Cal(16, 0x70, 0x00);//不显示
        }
        else
        {
            if(Speed.Display_Set == 0)
            {
                bit_Cal(18, 0xF0, 0x00);bit_Cal(17, 0x70, 0x20);//显示"-"
                bit_Cal(11, 0xF0, 0x00);bit_Cal(12, 0x70, 0x20);//显示"-"
                bit_Cal(13, 0xF0, 0x00);bit_Cal(14, 0x70, 0x20);//显示"-"
                bit_Cal(15, 0xF0, 0x00);bit_Cal(16, 0x70, 0x20);//显示"-"
            }
            else
            {
                if (Speed.Display_Set > 999) // 大于999时
                {
                    Val = Speed.Display_Set / 1000 % 10;
                    switch (Val)
                    {
                        case 0:
                            bit_Cal(18, 0xF0, 0xF0);bit_Cal(17, 0x70, 0x50);
                            break;
                        case 1:
                            bit_Cal(18, 0xF0, 0x00);bit_Cal(17, 0x70, 0x50);
                            break;
                        case 2:
                            bit_Cal(18, 0xF0, 0xD0);bit_Cal(17, 0x70, 0x30);
                            break;
                        case 3:
                            bit_Cal(18, 0xF0, 0x90);bit_Cal(17, 0x70, 0x70);
                            break;
                        case 4:
                            bit_Cal(18, 0xF0, 0x20);bit_Cal(17, 0x70, 0x70);
                            break;
                        case 5:
                            bit_Cal(18, 0xF0, 0xB0);bit_Cal(17, 0x70, 0x60);
                            break;
                        case 6:
                            bit_Cal(18, 0xF0, 0xF0);bit_Cal(17, 0x70, 0x60);
                            break;
                        case 7:
                            bit_Cal(18, 0xF0, 0x10);bit_Cal(17, 0x70, 0x50);
                            break;
                        case 8:
                            bit_Cal(18, 0xF0, 0xF0);bit_Cal(17, 0x70, 0x70);
                            break;
                        case 9:
                            bit_Cal(18, 0xF0, 0xB0);bit_Cal(17, 0x70, 0x70);
                            break;
                        default:
                            bit_Cal(18, 0xF0, 0x00);bit_Cal(17, 0x70, 0x20);
                            break;
                    }
                }
                else
                {
                    bit_Cal(18, 0xF0, 0xF0);bit_Cal(17, 0x70, 0x50);//显示数字0
                }
                    
                if (Speed.Display_Set > 99) // 大于99时
                {
                    Val = Speed.Display_Set / 100 % 10;
                    switch (Val)
                    {
                        case 0:
                            bit_Cal(11, 0xF0, 0xF0);bit_Cal(12, 0x70, 0x50);
                            break;
                        case 1:
                            bit_Cal(11, 0xF0, 0x00);bit_Cal(12, 0x70, 0x50);
                            break;
                        case 2:
                            bit_Cal(11, 0xF0, 0xD0);bit_Cal(12, 0x70, 0x30);
                            break;
                        case 3:
                            bit_Cal(11, 0xF0, 0x90);bit_Cal(12, 0x70, 0x70);
                            break;
                        case 4:
                            bit_Cal(11, 0xF0, 0x20);bit_Cal(12, 0x70, 0x70);
                            break;
                        case 5:
                            bit_Cal(11, 0xF0, 0xB0);bit_Cal(12, 0x70, 0x60);
                            break;
                        case 6:
                            bit_Cal(11, 0xF0, 0xF0);bit_Cal(12, 0x70, 0x60);
                            break;
                        case 7:
                            bit_Cal(11, 0xF0, 0x10);bit_Cal(12, 0x70, 0x50);
                            break;
                        case 8:
                            bit_Cal(11, 0xF0, 0xF0);bit_Cal(12, 0x70, 0x70);
                            break;
                        case 9:
                            bit_Cal(11, 0xF0, 0xB0);bit_Cal(12, 0x70, 0x70);
                            break;
                        default:
                            bit_Cal(11, 0xF0, 0x00);bit_Cal(12, 0x70, 0x20);
                            break;
                    }
                }
                else
                {
                    bit_Cal(11, 0xF0, 0xF0);bit_Cal(12, 0x70, 0x50);//显示数字零
                }
                if (Speed.Display_Set > 9) // 大于9时
                {
                    Val = Speed.Display_Set / 10 % 10;
                    switch (Val)
                    {
                        case 0:
                            bit_Cal(13, 0xF0, 0xF0);bit_Cal(14, 0x70, 0x50);
                            break;
                        case 1:
                            bit_Cal(13, 0xF0, 0x00);bit_Cal(14, 0x70, 0x50);
                            break;
                        case 2:
                            bit_Cal(13, 0xF0, 0xD0);bit_Cal(14, 0x70, 0x30);
                            break;
                        case 3:
                            bit_Cal(13, 0xF0, 0x90);bit_Cal(14, 0x70, 0x70);
                            break;
                        case 4:
                            bit_Cal(13, 0xF0, 0x20);bit_Cal(14, 0x70, 0x70);
                            break;
                        case 5:
                            bit_Cal(13, 0xF0, 0xB0);bit_Cal(14, 0x70, 0x60);
                            break;
                        case 6:
                            bit_Cal(13, 0xF0, 0xF0);bit_Cal(14, 0x70, 0x60);
                            break;
                        case 7:
                            bit_Cal(13, 0xF0, 0x10);bit_Cal(14, 0x70, 0x50);
                            break;
                        case 8:
                            bit_Cal(13, 0xF0, 0xF0);bit_Cal(14, 0x70, 0x70);
                            break;
                        case 9:
                            bit_Cal(13, 0xF0, 0xB0);bit_Cal(14, 0x70, 0x70);
                            break;
                        default:
                            bit_Cal(13, 0xF0, 0x00);bit_Cal(14, 0x70, 0x20);
                            break;
                    }
                }
                else
                {
                    bit_Cal(13, 0xF0, 0xF0);bit_Cal(14, 0x70, 0x50);//显示数字零
                }
                
                Val = Speed.Display_Set % 10;
                switch (Val)
                {
                    case 0:
                        bit_Cal(15, 0xF0, 0xF0);bit_Cal(16, 0x70, 0x50);
                        break;
                    case 1:
                        bit_Cal(15, 0xF0, 0x00);bit_Cal(16, 0x70, 0x50);
                        break;
                    case 2:
                        bit_Cal(15, 0xF0, 0xD0);bit_Cal(16, 0x70, 0x30);
                        break;
                    case 3:
                        bit_Cal(15, 0xF0, 0x90);bit_Cal(16, 0x70, 0x70);
                        break;
                    case 4:
                        bit_Cal(15, 0xF0, 0x20);bit_Cal(16, 0x70, 0x70);
                        break;
                    case 5:
                        bit_Cal(15, 0xF0, 0xB0);bit_Cal(16, 0x70, 0x60);
                        break;
                    case 6:
                        bit_Cal(15, 0xF0, 0xF0);bit_Cal(16, 0x70, 0x60);
                        break;
                    case 7:
                        bit_Cal(15, 0xF0, 0x10);bit_Cal(16, 0x70, 0x50);
                        break;
                    case 8:
                        bit_Cal(15, 0xF0, 0xF0);bit_Cal(16, 0x70, 0x70);
                        break;
                    case 9:
                        bit_Cal(15, 0xF0, 0xB0);bit_Cal(16, 0x70, 0x70);
                        break;
                    default:
                        bit_Cal(15, 0xF0, 0x00);bit_Cal(16, 0x70, 0x20);
                        break;
                }
            }
        }

        /**********时间显示**********/
        if(Time.Set || sys.SetMode_Option == 3)//设定时间大于0，在设定时间和闪烁下
        {
            if(!Time_ShowFlag)
            {
                if(Time.Set == 0)
                {
                    bit_Cal(26, 0x0F, 0x00);bit_Cal(25, 0x07, 0x02);//显示"-"
                    bit_Cal(24, 0x0F, 0x00);bit_Cal(23, 0x07, 0x02);//显示"-"
                    bit_Cal(22, 0x0F, 0x00);bit_Cal(21, 0x07, 0x02);//显示"-"
                    bit_Cal(20, 0x0F, 0x00);bit_Cal(19, 0x07, 0x02);//显示"-"
                }
                else
                {
                    if(Time.Display >= 3600)
                        Val = Time.Display / 3600 / 10;//计算十位为单位的小时数
                    else if(Time.Display > 59)
                        Val = Time.Display / 60 / 10;//计算十位为单位的小时数
                    else if(Time.Display > 0)
                        Val = 0;//计算十位为单位的小时数
                    else Val = 10;//显示‘-’
                    switch (Val)
                    {
                        case 0:
                            bit_Cal(26, 0x0F, 0x0F);bit_Cal(25, 0x07, 0x05);
                            break;
                        case 1:
                            bit_Cal(26, 0x0F, 0x00);bit_Cal(25, 0x07, 0x05);
                            break;
                        case 2:
                            bit_Cal(26, 0x0F, 0x0D);bit_Cal(25, 0x07, 0x03);
                            break;
                        case 3:
                            bit_Cal(26, 0x0F, 0x09);bit_Cal(25, 0x07, 0x07);
                            break;
                        case 4:
                            bit_Cal(26, 0x0F, 0x02);bit_Cal(25, 0x07, 0x07);
                            break;
                        case 5:
                            bit_Cal(26, 0x0F, 0x0B);bit_Cal(25, 0x07, 0x06);
                            break;
                        case 6:
                            bit_Cal(26, 0x0F, 0x0F);bit_Cal(25, 0x07, 0x06);
                            break;
                        case 7:
                            bit_Cal(26, 0x0F, 0x01);bit_Cal(25, 0x07, 0x05);
                            break;
                        case 8:
                            bit_Cal(26, 0x0F, 0x0F);bit_Cal(25, 0x07, 0x07);
                            break;
                        case 9:
                            bit_Cal(26, 0x0F, 0x0B);bit_Cal(25, 0x07, 0x07);
                            break;
                        default:
                            bit_Cal(26, 0x0F, 0x00);bit_Cal(25, 0x07, 0x02);
                            break;
                    }

                    if(Time.Display >= 3600)
                        Val = Time.Display / 3600 % 10;//计算十位为单位的小时数
                    else if(Time.Display > 59)
                        Val = Time.Display / 60 % 10;//计算十位为单位的小时数
                    else if(Time.Display > 0)
                        Val = 0;//计算十位为单位的小时数
                    else Val = 10;//显示‘-’
                    switch (Val)
                    {
                        case 0:
                            bit_Cal(24, 0x0F, 0x0F);bit_Cal(23, 0x07, 0x05);
                            break;
                        case 1:
                            bit_Cal(24, 0x0F, 0x00);bit_Cal(23, 0x07, 0x05);
                            break;
                        case 2:
                            bit_Cal(24, 0x0F, 0x0D);bit_Cal(23, 0x07, 0x03);
                            break;
                        case 3:
                            bit_Cal(24, 0x0F, 0x09);bit_Cal(23, 0x07, 0x07);
                            break;
                        case 4:
                            bit_Cal(24, 0x0F, 0x02);bit_Cal(23, 0x07, 0x07);
                            break;
                        case 5:
                            bit_Cal(24, 0x0F, 0x0B);bit_Cal(23, 0x07, 0x06);
                            break;
                        case 6:
                            bit_Cal(24, 0x0F, 0x0F);bit_Cal(23, 0x07, 0x06);
                            break;
                        case 7:
                            bit_Cal(24, 0x0F, 0x01);bit_Cal(23, 0x07, 0x05);
                            break;
                        case 8:
                            bit_Cal(24, 0x0F, 0x0F);bit_Cal(23, 0x07, 0x07);
                            break;
                        case 9:
                            bit_Cal(24, 0x0F, 0x0B);bit_Cal(23, 0x07, 0x07);
                            break;
                        default:
                            bit_Cal(24, 0x0F, 0x00);bit_Cal(23, 0x07, 0x02);
                            break;
                    }

                    if(Time.Display >= 3600)
                        Val = Time.Display % 3600 / 60 / 10;//计算十位为单位的小时数
                    else if(Time.Display > 59)
                        Val = Time.Display % 60 / 10;//计算十位为单位的小时数
                    else if(Time.Display > 0)
                        Val = Time.Display % 60 / 10;//计算十位为单位的小时数
                    else Val = 10;//显示‘-’
                    switch (Val)
                    {
                        case 0:
                            bit_Cal(22, 0x0F, 0x0F);bit_Cal(21, 0x07, 0x05);
                            break;
                        case 1:
                            bit_Cal(22, 0x0F, 0x00);bit_Cal(21, 0x07, 0x05);
                            break;
                        case 2:
                            bit_Cal(22, 0x0F, 0x0D);bit_Cal(21, 0x07, 0x03);
                            break;
                        case 3:
                            bit_Cal(22, 0x0F, 0x09);bit_Cal(21, 0x07, 0x07);
                            break;
                        case 4:
                            bit_Cal(22, 0x0F, 0x02);bit_Cal(21, 0x07, 0x07);
                            break;
                        case 5:
                            bit_Cal(22, 0x0F, 0x0B);bit_Cal(21, 0x07, 0x06);
                            break;
                        case 6:
                            bit_Cal(22, 0x0F, 0x0F);bit_Cal(21, 0x07, 0x06);
                            break;
                        case 7:
                            bit_Cal(22, 0x0F, 0x01);bit_Cal(21, 0x07, 0x05);
                            break;
                        case 8:
                            bit_Cal(22, 0x0F, 0x0F);bit_Cal(21, 0x07, 0x07);
                            break;
                        case 9:
                            bit_Cal(22, 0x0F, 0x0B);bit_Cal(21, 0x07, 0x07);
                            break;
                        default:
                            bit_Cal(22, 0x0F, 0x00);bit_Cal(21, 0x07, 0x02);
                            break;
                    }

                    if(Time.Display >= 3600)
                        Val = Time.Display % 3600 / 60 % 10;//计算十位为单位的小时数
                    else if(Time.Display > 59)
                        Val = Time.Display % 60 % 10;//计算十位为单位的小时数
                    else if(Time.Display > 0)
                        Val = Time.Display % 60 % 10;//计算十位为单位的小时数
                    else Val = 10;//显示‘-’
                    switch (Val)
                    {
                        case 0:
                            bit_Cal(20, 0x0F, 0x0F);bit_Cal(19, 0x07, 0x05);
                            break;
                        case 1:
                            bit_Cal(20, 0x0F, 0x00);bit_Cal(19, 0x07, 0x05);
                            break;
                        case 2:
                            bit_Cal(20, 0x0F, 0x0D);bit_Cal(19, 0x07, 0x03);
                            break;
                        case 3:
                            bit_Cal(20, 0x0F, 0x09);bit_Cal(19, 0x07, 0x07);
                            break;
                        case 4:
                            bit_Cal(20, 0x0F, 0x02);bit_Cal(19, 0x07, 0x07);
                            break;
                        case 5:
                            bit_Cal(20, 0x0F, 0x0B);bit_Cal(19, 0x07, 0x06);
                            break;
                        case 6:
                            bit_Cal(20, 0x0F, 0x0F);bit_Cal(19, 0x07, 0x06);
                            break;
                        case 7:
                            bit_Cal(20, 0x0F, 0x01);bit_Cal(19, 0x07, 0x05);
                            break;
                        case 8:
                            bit_Cal(20, 0x0F, 0x0F);bit_Cal(19, 0x07, 0x07);
                            break;
                        case 9:
                            bit_Cal(20, 0x0F, 0x0B);bit_Cal(19, 0x07, 0x07);
                            break;
                        default:
                            bit_Cal(20, 0x0F, 0x00);bit_Cal(19, 0x07, 0x02);
                            break;
                    }
                }
            }
            else//不显示时间
            {
                bit_Cal(26, 0x0F, 0x00);bit_Cal(25, 0x07, 0x00);
                bit_Cal(24, 0x0F, 0x00);bit_Cal(23, 0x07, 0x00);
                bit_Cal(22, 0x0F, 0x00);bit_Cal(21, 0x07, 0x00);
                bit_Cal(20, 0x0F, 0x00);bit_Cal(19, 0x07, 0x00);
            }
            /**********时间冒号图标**********/
            bit_Cal(8, 0x01, 0x01);

            /**********时间图标**********/
            if(TimeIcn_ShowFlag == 0)
            {
                bit_Cal(19, 0x80, 0x80);//时间图标
            }
            else
            {
                bit_Cal(19, 0x80, 0x00);//不显示时间图标

            }
            
            if(Time.Display < 3600)
            {
                /**********‘sec’图标**********/
                bit_Cal(10, 0x04, 0x04);
                /**********‘min’图标**********/
                bit_Cal(10, 0x08, 0x00);
            }
            else
            {
                /**********‘sec’图标**********/
                bit_Cal(10, 0x04, 0x00);
                /**********‘min’图标**********/
                bit_Cal(10, 0x08, 0x08);
            }
        }
        else//不显示时间
        {
            bit_Cal(26, 0x0F, 0x00);bit_Cal(25, 0x07, 0x00);
            bit_Cal(24, 0x0F, 0x00);bit_Cal(23, 0x07, 0x00);
            bit_Cal(22, 0x0F, 0x00);bit_Cal(21, 0x07, 0x00);
            bit_Cal(20, 0x0F, 0x00);bit_Cal(19, 0x07, 0x00);
            /**********时间冒号图标**********/
            bit_Cal(8, 0x01, 0x00);//不显示
            /**********时间图标**********/
            bit_Cal(19, 0x80, 0x00);//不显示
            /**********‘sec’图标**********/
            bit_Cal(10, 0x04, 0x00);//不显示
            /**********‘min’图标**********/
            bit_Cal(10, 0x08, 0x00);//不显示
        }
        
        if(Temp.Unit)
        {
            /**********华氏度℉**********/
            bit_Cal(8, 0x08, 0x08);
            /**********‘℃’图标**********/
            bit_Cal(7, 0x80, 0x00);
        }
        else
        {
            /**********华氏度℉**********/
            bit_Cal(8, 0x08, 0x00);
            /**********‘℃’图标**********/
            bit_Cal(7, 0x80, 0x80);
        }
          
        /*************加热图标***************/
        if(TempIcn_ShowFlag == 0)
        {
            /**********加热图标**********/
            bit_Cal(8, 0x02, 0x02);
            bit_Cal(3, 0x01, 0x01);//加热图标下面的横杠
        }
        else
        {
            /**********不显示加热图标**********/
            bit_Cal(8, 0x02, 0x00);
            bit_Cal(3, 0x01, 0x0);//加热图标下面的横杠
        }	      
        
        if(Temp.Up_Speed == 1)
        {
            
            /**********加热图标旁边的H**********/
            bit_Cal(8, 0x04, 0x04);
        }
        else if(Temp.Up_Speed == 2)
        {
            /**********加热图标旁边的L**********/
            bit_Cal(9, 0x02, 0x02);
        }
        
        
        /**********实际温度小数点**********/
        bit_Cal(5, 0x01, 0x01);
        
        /**********设定温度小数点**********/
        bit_Cal(5, 0x80, 0x80);
        
//        /**********'SAFE'图标**********/
//        bit_Cal(1, 0x80, 0x80);
        
        /**********外部探头图标**********/
        if(PT_VALUE_1_TEMP < 2400)
        {
            bit_Cal(7, 0x01, 0x01);
        }
        else
        {
            bit_Cal(7, 0x01, 0x00);//不显示外部探头的图标
        }
        
//        /**********转速图标搅拌子**********/
//        bit_Cal(9, 0x01, 0x01);
      
        /**********锁定图标**********/
        if(sys.Lock && !Lock_ShowFlag)
        {
            bit_Cal(9, 0x04, 0x04);//锁定
        }
        else
        {
            bit_Cal(9, 0x04, 0x00);//不显示锁定
        }
        
        /**********转速图标**********/
        switch(SpeedIcn_ShowFlag)
        {
            case 0: bit_Cal(12, 0x01, 0x01);//S5
                    bit_Cal(10, 0x01, 0x01);//S4
                    bit_Cal(10, 0x02, 0x02);//S3
                break;
            case 1: bit_Cal(12, 0x01, 0x00);//S5
                    bit_Cal(10, 0x01, 0x01);//S4
                    bit_Cal(10, 0x02, 0x02);//S3
                break;
            case 2: bit_Cal(12, 0x01, 0x01);//S5
                    bit_Cal(10, 0x01, 0x01);//S4
                    bit_Cal(10, 0x02, 0x00);//S3
                break;
            case 3: bit_Cal(12, 0x01, 0x01);//S5
                    bit_Cal(10, 0x01, 0x00);//S4
                    bit_Cal(10, 0x02, 0x02);//S3
                break;
            default:
                break;
        }
        
        /**********‘rpm’图标**********/
        bit_Cal(14, 0x80, 0x80);
        
        if(Speed.Up_Speed == 1)
        {
            /**********转速图标旁边的H**********/
            bit_Cal(9, 0x08, 0x08);
        }
        else if(Speed.Up_Speed == 2)
        {
            /**********转速图标旁边的L**********/
            bit_Cal(17, 0x01, 0x01);
        }
        
        /**********L1**********/
        if(PMode.Light_BIT & BIT0)
        {
            bit_Cal(26, 0x10, 0x10);
        }
        else
        {
            bit_Cal(26, 0x10, 0x00);
        }
        
        /**********L2**********/
        if(PMode.Light_BIT & BIT1)
        {
            bit_Cal(23, 0x08, 0x08);
        }
        else
        {
            bit_Cal(23, 0x08, 0x00);
        }
        
        /**********L3**********/
        if(PMode.Light_BIT & BIT2)
        {
            bit_Cal(19, 0x08, 0x08);
        }
        else
        {
            bit_Cal(19, 0x08, 0x00);
        }
        
        /**********L4**********/
        if(PMode.Light_BIT & BIT3)
        {
            bit_Cal(19, 0x10, 0x10);
        }
        else
        {
            bit_Cal(19, 0x10, 0x00);
        }
        
        /**********L5**********/
        if(PMode.Light_BIT & BIT4)
        {
            bit_Cal(19, 0x20, 0x20);
        }
        else
        {
            bit_Cal(19, 0x20, 0x00);
        }
        
        /**********L6**********/
        if(PMode.Light_BIT & BIT5)
        {
            bit_Cal(19, 0x40, 0x40);
        }
        else
        {
            bit_Cal(19, 0x40, 0x00);
        }
        
        /**********L7**********/
        if(PMode.Light_BIT & BIT6)
        {
            bit_Cal(20, 0x80, 0x80);
        }
        else
        {
            bit_Cal(20, 0x80, 0x00);
        }
        
        /**********L8**********/
        if(PMode.Light_BIT & BIT7)
        {
            bit_Cal(22, 0x80, 0x80);
        }
        else
        {
            bit_Cal(22, 0x80, 0x00);
        }
        
        /**********L9**********/
        if(PMode.Light_BIT & BIT8)
        {
            bit_Cal(24, 0x80, 0x80);
        }
        else
        {
            bit_Cal(24, 0x80, 0x00);
        }
        
        /**********L10**********/
        if(PMode.Light_BIT & BIT9)
        {
            bit_Cal(26, 0x80, 0x80);
        }
        else
        {
            bit_Cal(26, 0x80, 0x00);
        }
        
        /**********L11**********/
        if(PMode.Light_BIT & BIT10)
        {
            bit_Cal(26, 0x40, 0x40);
        }
        else
        {
            bit_Cal(26, 0x40, 0x00);
        }
        
        /**********L12**********/
        if(PMode.Light_BIT & BIT11)
        {
            bit_Cal(26, 0x20, 0x20);
        }
        else
        {
            bit_Cal(26, 0x20, 0x00);
        }
        
        /**********‘P’**********/
        if (PMode.Status) // 进入PMode
        {
            if (!PMode.Mode) // 在P模式下
            {
                if (!Pmode_ShowFlag)
                {
                    bit_Cal(25, 0xF0, 0x70);bit_Cal(24, 0x70, 0x30);//P
                    /**********‘-’**********/
                    bit_Cal(23, 0xF0, 0x00);bit_Cal(22, 0x70, 0x20);
                    switch (PMode.Option)
                    {
                        case 0:
                            bit_Cal(21, 0xF0, 0xF0);bit_Cal(20, 0x70, 0x50);
                            break;
                        case 1:
                            bit_Cal(21, 0xF0, 0x00);bit_Cal(20, 0x70, 0x50);
                            break;
                        case 2:
                            bit_Cal(21, 0xF0, 0xD0);bit_Cal(20, 0x70, 0x30);
                            break;
                        case 3:
                            bit_Cal(21, 0xF0, 0x90);bit_Cal(20, 0x70, 0x70);
                            break;
                        case 4:
                            bit_Cal(21, 0xF0, 0x20);bit_Cal(20, 0x70, 0x70);
                            break;
                        case 5:
                            bit_Cal(21, 0xF0, 0xB0);bit_Cal(20, 0x70, 0x60);
                            break;
                        case 6:
                            bit_Cal(21, 0xF0, 0xF0);bit_Cal(20, 0x70, 0x60);
                            break;
                        case 7:
                            bit_Cal(21, 0xF0, 0x10);bit_Cal(20, 0x70, 0x50);
                            break;
                        case 8:
                            bit_Cal(21, 0xF0, 0xF0);bit_Cal(20, 0x70, 0x70);
                            break;
                        case 9:
                            bit_Cal(21, 0xF0, 0xB0);bit_Cal(20, 0x70, 0x70);
                            break;
                        default:
                            bit_Cal(21, 0xF0, 0x00);bit_Cal(20, 0x70, 0x20);
                            break;
                    }
                }
                else
                {
                    bit_Cal(25, 0xF0, 0x00);bit_Cal(24, 0x70, 0x00);//不显示
                    bit_Cal(23, 0xF0, 0x00);bit_Cal(22, 0x70, 0x00);//不显示
                    bit_Cal(21, 0xF0, 0x00);bit_Cal(20, 0x70, 0x00);//不显示
                }
            }
            else// 梯度模式下
            {
                if (!PModeP1_ShowFlag)
                {
                    switch (PMode.P1)
                    {
                        case 0:
                            bit_Cal(25, 0xF0, 0xF0);bit_Cal(24, 0x70, 0x50);
                            break;
                        case 1:
                            bit_Cal(25, 0xF0, 0x00);bit_Cal(24, 0x70, 0x50);
                            break;
                        case 2:
                            bit_Cal(25, 0xF0, 0xD0);bit_Cal(24, 0x70, 0x30);
                            break;
                        case 3:
                            bit_Cal(25, 0xF0, 0x90);bit_Cal(24, 0x70, 0x70);
                            break;
                        case 4:
                            bit_Cal(25, 0xF0, 0x20);bit_Cal(24, 0x70, 0x70);
                            break;
                        case 5:
                            bit_Cal(25, 0xF0, 0xB0);bit_Cal(24, 0x70, 0x60);
                            break;
                        case 6:
                            bit_Cal(25, 0xF0, 0xF0);bit_Cal(24, 0x70, 0x60);
                            break;
                        case 7:
                            bit_Cal(25, 0xF0, 0x10);bit_Cal(24, 0x70, 0x50);
                            break;
                        case 8:
                            bit_Cal(25, 0xF0, 0xF0);bit_Cal(24, 0x70, 0x70);
                            break;
                        case 9:
                            bit_Cal(25, 0xF0, 0xB0);bit_Cal(24, 0x70, 0x70);
                            break;
                        default:
                            bit_Cal(25, 0xF0, 0x70);bit_Cal(24, 0x70, 0x30);//P
                            break;
                    }
                }
                else
                {
                    bit_Cal(25, 0xF0, 0x00);bit_Cal(24, 0x70, 0x00);//不显示
                }
                
                /**********‘-’**********/
                bit_Cal(23, 0xF0, 0x00);bit_Cal(22, 0x70, 0x20);
                
                if (!PModeP2_ShowFlag)
                {
                    switch (PMode.P2)
                    {
                        case 0:
                            bit_Cal(21, 0xF0, 0xF0);bit_Cal(20, 0x70, 0x50);
                            break;
                        case 1:
                            bit_Cal(21, 0xF0, 0x00);bit_Cal(20, 0x70, 0x50);
                            break;
                        case 2:
                            bit_Cal(21, 0xF0, 0xD0);bit_Cal(20, 0x70, 0x30);
                            break;
                        case 3:
                            bit_Cal(21, 0xF0, 0x90);bit_Cal(20, 0x70, 0x70);
                            break;
                        case 4:
                            bit_Cal(21, 0xF0, 0x20);bit_Cal(20, 0x70, 0x70);
                            break;
                        case 5:
                            bit_Cal(21, 0xF0, 0xB0);bit_Cal(20, 0x70, 0x60);
                            break;
                        case 6:
                            bit_Cal(21, 0xF0, 0xF0);bit_Cal(20, 0x70, 0x60);
                            break;
                        case 7:
                            bit_Cal(21, 0xF0, 0x10);bit_Cal(20, 0x70, 0x50);
                            break;
                        case 8:
                            bit_Cal(21, 0xF0, 0xF0);bit_Cal(20, 0x70, 0x70);
                            break;
                        case 9:
                            bit_Cal(21, 0xF0, 0xB0);bit_Cal(20, 0x70, 0x70);
                            break;
                        default:
                            bit_Cal(21, 0xF0, 0x00);bit_Cal(20, 0x70, 0x20);
                            break;
                    }
                }
                else
                {
                    bit_Cal(21, 0xF0, 0x00);bit_Cal(20, 0x70, 0x00);//不显示
                }
            }
        }
        else // 不进入P模式不显示
        {
            bit_Cal(25, 0xF0, 0x00);bit_Cal(24, 0x70, 0x00);//不显示
            bit_Cal(23, 0xF0, 0x00);bit_Cal(22, 0x70, 0x00);//不显示
            bit_Cal(21, 0xF0, 0x00);bit_Cal(20, 0x70, 0x00);//不显示
        }
        
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

/*
*****************************************************************
 * 函数原型：void Deal_Temp(float dT)
 * 功    能：温度显示处理
*****************************************************************
*/
void Deal_Temp(float dT)
{
    static float T;
	uint8_t val;
	
	if(sys.Run_Status == 0)//没启动的情况下
	{
		Temp.Display_Rel = Temp.Rel;//显示实际温度
		Temp.New =0;//现在的速度清零
		Temp.Last = 0;//之前的速度清零
		Temp.ADDMode = 0;//清除显示处理
        T = 0;
	}
	
	else if(sys.Run_Status== 1 && Temp.Ctrl)
	{
		if(PT_VALUE_1_TEMP < 2400)//假如插入外部探头
			val = 40;
		else//假如没有插入外部探头
		{
			if(Temp.Ctrl < 2800)
				val = 100;
			else
				val = 140;
		}
		
		if(Temp.ADDMode==0)//判断模式
		{ 
			if(Temp.Ctrl > Temp.Display_Rel)
			{
				Temp.ADDMode = 1;//进入升温模式
				Temp.Last = Temp.Display_Rel;
			}
			else if(Temp.Ctrl < Temp.Display_Rel)
			{
				Temp.ADDMode = 2;//进入降温模式
				Temp.Last = Temp.Display_Rel;//记录当前温度
			}
			else
			{
				Temp.ADDMode = 3;//进入稳定模式
			}
		}
		
		else if(Temp.ADDMode==1)//在进入升温模式下
		{ 
			Temp.New = Temp.Rel;//记录当前温度
			if(Temp.New > Temp.Last)//当前温度大于上一次温度
			{
                if(Temp.Display_Rel > 1000)
                {
                    Temp.Display_Rel += 10;//显示当前温度
                }
                else
                {
                    Temp.Display_Rel ++;//显示当前温度
                }
				Temp.Last = Temp.Display_Rel;//将当前温度保存
			}					
			else//当前温度小于上一次温度
			{	//只有在实际温度大于90℃，控制温度大于95小于100℃，插入外部探头才有作用
				if(Temp.Rel > 900 && Temp.Ctrl >= 950 && Temp.Ctrl <= 1000 && PT_VALUE_1_TEMP < 2400)
				{
					T += dT;
					if(T > 10.0f)
					{
						if(Temp.Display_Rel > 100)
                        {
                            Temp.Display_Rel += 10;//显示当前温度
                        }
                        else
                        {
                            Temp.Display_Rel ++;//显示当前温度
                        }
						Temp.Last = Temp.Display_Rel;
						T = 0;
					}
				}
                else if(Temp.Rel>=2800 && Temp.Ctrl>=2800 && PT_VALUE_1_TEMP >= 2400)
                {
                    T += dT;
					if(T > 2.0f)
					{
						Temp.Display_Rel += 10;
						Temp.Last = Temp.Display_Rel;
						T = 0;
					}
                }
				else
				{
					T = 0;
				}
			}
			if(Temp.Display_Rel >= Temp.Ctrl)//当前的温度大于等于控制温度
			{
				Temp.ADDMode = 3;//进入稳定模式
			}
			
			if((ABS(Temp.Display_Rel - Temp.Rel) > (val + 50))&&(Temp.Rel < 2800 && Temp.Ctrl<=2800))
			{
				Temp.ADDMode = 0;//进入稳定模式 
				Temp.Display_Rel = Temp.Rel;//显示实际温度
			}
		}
		
		else if(Temp.ADDMode==2)//在进入降温模式下
		{ 
            if(Temp.Display_Rel > Temp.Ctrl && Temp.Display_Rel != Temp.Rel && Temp.Display_Rel >= Temp.Rel)
            {
                if(Temp.Display_Rel > 1000)
                {
                    T += dT;
					if(T > 2.0f)
					{
						Temp.Display_Rel -= 10;
						Temp.Last = Temp.Display_Rel;
						T = 0;
					}
                }
                else
                {
                    T += dT;
					if(T > 0.8f)
					{
						Temp.Display_Rel -= 1;
						Temp.Last = Temp.Display_Rel;
						T = 0;
					}
                }
            }
            else
            {
                Temp.New = Temp.Rel;//记录当前温度
                if(Temp.New < Temp.Last)//当前温度小于上一次温度
                {
                    if(Temp.Display_Rel > 2700)
                    {
                        T += dT;
                        if(T > 2.0f)
                        {
                            Temp.Display_Rel -= 10;
                            Temp.Last = Temp.Display_Rel;
                            T = 0;
                        }
                    }
                    else
                    {
                        T = 0;
                        if(Temp.Display_Rel > 100)
                        {
                            Temp.Display_Rel -= 10;//显示当前温度
                        }
                        else
                        {
                            Temp.Display_Rel --;//显示当前温度
                        }
                        Temp.Last = Temp.Display_Rel;//将当前温度保存
                    }
                }
                else//当前温度小于上一次温度
                {	//只有在实际温度大于90℃，控制温度大于95小于100℃，插入外部探头才有作用
                    if(Temp.Rel > 900 && Temp.Ctrl >= 950 && Temp.Ctrl <= 1000 && PT_VALUE_1_TEMP < 2400)
                    {
                        T += dT;
                        if(T > 10.0f)
                        {
                            if(Temp.Display_Rel > 1000)
                            {
                                Temp.Display_Rel -= 10;//显示当前温度
                            }
                            else
                            {
                                Temp.Display_Rel --;//显示当前温度
                            }
                            Temp.Last = Temp.Display_Rel;
                            T = 0;
                        }
                    }
                    else if(Temp.Rel>=2800 && Temp.Ctrl>=2800 && PT_VALUE_1_TEMP >= 2400)
                    {
                        T += dT;
                        if(T > 2.0f)
                        {
                            Temp.Display_Rel -= 10;
                            Temp.Last = Temp.Display_Rel;
                            T = 0;
                        }
                    }
                    else
                    {
                        T = 0;
                    }
                }
                if(Temp.Display_Rel <= Temp.Ctrl)//当前的温度小于等于控制温度
                {
                    Temp.ADDMode = 3;//进入稳定模式
                }
                
                if((ABS(Temp.Display_Rel - Temp.Rel) > (val + 50))&&(Temp.Rel < 2800 && Temp.Ctrl<=2800))
                {
                    Temp.ADDMode = 0;//进入稳定模式 
                    Temp.Display_Rel = Temp.Rel;//显示实际温度
                }
            }
		}
            
		else if(Temp.ADDMode == 3)//温度稳定模式下
		{
			if((ABS(Temp.Ctrl - Temp.Rel) < val)|| Temp.Ctrl>=2800)
			{
				Temp.Display_Rel = Temp.Ctrl;//显示控制温度
			}
			else
			{
				Temp.ADDMode = 0;//进入稳定模式 
				Temp.Display_Rel = Temp.Rel;//显示实际温度
			}
		}	
	}
	
	else if(sys.Run_Status == 2)
    {
        T +=dT;
        if(T > 2.0f)
        {
            if(Temp.Rel < Temp.Display_Rel)
                Temp.Display_Rel -= 10;//显示当前温度
            else if(Temp.Rel > Temp.Display_Rel)
                Temp.Display_Rel += 10;//显示当前温度   
            else
                sys.Run_Status = 0;
            T = 0;
        }
        if((ABS(Temp.Display_Rel - Temp.Rel) > 90)&&(Temp.Rel < 2800 && Temp.Ctrl<=2800))
        {
            sys.Run_Status = 0;
        }
    }
}

/**
 * @brief 显示屏幕内容
 * 
 */
void Show_Display(void)
{
    if(sys.Run_Status == 1)
    {
        if(sys.SetMode_Option == 3)
            Time.Display = Time.Set;//显示设定时间  
        else
            Time.Display = Time.Rel + 59;//显示控制时间
    }
	else			
		Time.Display = Time.Set;//显示设定时间  
    
    Speed.Display_Set = Speed.Set;
    
    
    Temp.Display_Set = Temp.Set;
    Display();
}
