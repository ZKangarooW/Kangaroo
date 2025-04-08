#include "Show.h"

/**********全局变量声明******/
float Temp_Twinkle_Time,Time_Twinkle_Time;//温度闪烁时间和时间闪烁时间

/**********局部变量声明******/
uint8_t Temp_ShowFlag,Time_ShowFlag,Pmode_ShowFlag;//温度、时间、P模式显示的标志位 0:常亮 1：熄灭
uint8_t TempIcn_ShowFlag,TimeIcn_ShowFlag,Hot_ShowFlag;//加热图标闪烁和时间图标、高温图标闪烁

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
            if(Temp.Ctrl)
				TempIcn_ShowFlag = ~TempIcn_ShowFlag;//温度图标闪烁;
			else
				TempIcn_ShowFlag = 0;
            
			if(Time.Rel && (!Temp.Ctrl || TempIcn_ShowFlag != TimeIcn_ShowFlag))
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
        T = 0;
        TempIcn_ShowFlag = 0;
        TimeIcn_ShowFlag = 0;
    }
}

/*
*****************************************************************
 * 函数原型：static void Check_ShowFlag(float dT)
 * 功    能：闪烁检测
 * 输    入: dT:执行周期
 * 参    数：float dT
 * 调    用：内部调用
*****************************************************************
*/
static void Check_ShowFlag(float dT)
{
	static float Temp_T,Time_T,Hot_T;
    
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
    
    if(sys.Display)
    {
        Hot_T += dT;
		if (Hot_T >= 0.5f)
		{
            Hot_ShowFlag = ~Hot_ShowFlag;
            Hot_T = 0;
		}
    }
    else
    {
        Hot_T = 0;
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
	Check_ShowFlag(dT);
    Icn_Twinkle(dT);
}

uint8_t seg[20] = {0};
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
 * 函数原型：void Display(int16_t dis_set_temp,int16_t dis_rel_temp,int32_t dis_set_time,int32_t dis_rel_time,uint8_t PMode_Option)
 * 功    能：显示函数
*****************************************************************
*/
void Display(int16_t dis_set_temp,int16_t dis_rel_temp,int32_t dis_set_time,int32_t dis_rel_time,uint8_t PMode_Option)
{
    uint8_t Val;// 用于百十个取出来的数字
    
    
    if(sys.Display)
    {
        memset(seg, 0, sizeof(seg));//清空数组   
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 200);//背光pwm
        if(Temp.Mesa > 500)
        {
            if(Hot_ShowFlag==0)
            {
                bit_Cal(5, 0x80, 0x00);//HOT
                bit_Cal(4, 0x80, 0x00);//！
            }
            else
            {
                bit_Cal(5, 0x80, 0x80);//HOT
                bit_Cal(4, 0x80, 0x80);//！
            }
            /**********设定温度**********/
            if (Temp.Mesa >= 0)//大于等于0时
            {
                Val = Temp.Mesa / 1000 % 10;
            }
            else if (Temp.Mesa < 0 && Temp.Mesa > -100)
            {
                Val = ABS(Temp.Mesa) / 1000 % 10;//计算后是0，不大于999所以不会显示
            }
            else if (Temp.Mesa <= -100 && Temp.Mesa > -1000)
            {
                Val = 10;//显示“-”
            }
            switch (Val)
            {
                case 0:
                    if (Temp.Mesa > 999)//显示零
                    {
                        bit_Cal(13, 0xFE, 0xEE);
                    }
                    else//不显示
                    {
                        bit_Cal(13, 0xFE, 0x00);
                    }
                    break;
                case 1:
                    bit_Cal(13, 0xFE, 0x48);
                    break;
                case 2:
                    bit_Cal(13, 0xFE, 0xBA);
                    break;
                case 3:
                    bit_Cal(13, 0xFE, 0xDA);
                    break;
                case 4:
                    bit_Cal(13, 0xFE, 0x5C);
                    break;
                case 5:
                    bit_Cal(13, 0xFE, 0xD6);
                    break;
                case 6:
                    bit_Cal(13, 0xFE, 0xF6);
                    break;
                case 7:
                    bit_Cal(13, 0xFE, 0x4A);
                    break;
                case 8:
                    bit_Cal(13, 0xFE, 0xFE);
                    break;
                case 9:
                    bit_Cal(13, 0xFE, 0xDE);
                    break;
                default:
                    bit_Cal(13, 0xFE, 0x10);
                    break;
            }
            
            if (Temp.Mesa >= 0)//大于等于0时
            {
                Val = Temp.Mesa / 100 % 10;
            }
            else if (Temp.Mesa < 0 && Temp.Mesa > -100)
            {
                Val = 10;//显示“-”
            }
            else if (Temp.Mesa <= -100 && Temp.Mesa > -1000)
            {
                Val = ABS(Temp.Mesa)/ 100 % 10;
            }
            switch (Val)
            {
                case 0:
                    if (Temp.Mesa > 99)//显示零
                    {
                        bit_Cal(12, 0xFE, 0xEE);
                    }
                    else//不显示
                    {
                        bit_Cal(12, 0xFE, 0x00);
                    }
                    break;
                case 1:
                    bit_Cal(12, 0xFE, 0x48);
                    break;
                case 2:
                    bit_Cal(12, 0xFE, 0xBA);
                    break;
                case 3:
                    bit_Cal(12, 0xFE, 0xDA);
                    break;
                case 4:
                    bit_Cal(12, 0xFE, 0x5C);
                    break;
                case 5:
                    bit_Cal(12, 0xFE, 0xD6);
                    break;
                case 6:
                    bit_Cal(12, 0xFE, 0xF6);
                    break;
                case 7:
                    bit_Cal(12, 0xFE, 0x4A);
                    break;
                case 8:
                    bit_Cal(12, 0xFE, 0xFE);
                    break;
                case 9:
                    bit_Cal(12, 0xFE, 0xDE);
                    break;
                default:
                    bit_Cal(12, 0xFE, 0x10);
                    break;
            }
            
            if (Temp.Mesa >= 0)//大于等于0时
            {
                Val = Temp.Mesa / 10 % 10;
            }
            else if (Temp.Mesa < 0 && Temp.Mesa > -100)
            {
                Val = ABS(Temp.Mesa) / 10 % 10;
            }
            else if (Temp.Mesa <= -100 && Temp.Mesa > -1000)
            {
                Val = ABS(Temp.Mesa) / 10 % 10;
            }
            switch (Val)
            {
                case 0:
                    bit_Cal(11, 0xFE, 0xEE);
                    break;
                case 1:
                    bit_Cal(11, 0xFE, 0x48);
                    break;
                case 2:
                    bit_Cal(11, 0xFE, 0xBA);
                    break;
                case 3:
                    bit_Cal(11, 0xFE, 0xDA);
                    break;
                case 4:
                    bit_Cal(11, 0xFE, 0x5C);
                    break;
                case 5:
                    bit_Cal(11, 0xFE, 0xD6);
                    break;
                case 6:
                    bit_Cal(11, 0xFE, 0xF6);
                    break;
                case 7:
                    bit_Cal(11, 0xFE, 0x4A);
                    break;
                case 8:
                    bit_Cal(11, 0xFE, 0xFE);
                    break;
                case 9:
                    bit_Cal(11, 0xFE, 0xDE);
                    break;
                default:
                    bit_Cal(11, 0xFE, 0x10);
                    break;
            }
            
            if (Temp.Mesa >= 0)//大于等于0时
            {
                Val = Temp.Mesa % 10;
            }
            else if (Temp.Mesa < 0 && Temp.Mesa > -100)
            {
                Val = ABS(Temp.Mesa) % 10;
            }
            else if (Temp.Mesa <= -100 && Temp.Mesa > -1000)
            {
                Val = ABS(Temp.Mesa) % 10;
            }
            switch (Val)
            {
                case 0:
                    bit_Cal(10, 0x7F, 0x77);
                    break;
                case 1:
                    bit_Cal(10, 0x7F, 0x24);
                    break;
                case 2:
                    bit_Cal(10, 0x7F, 0x5D);
                    break;
                case 3:
                    bit_Cal(10, 0x7F, 0x6D);
                    break;
                case 4:
                    bit_Cal(10, 0x7F, 0x2E);
                    break;
                case 5:
                    bit_Cal(10, 0x7F, 0x6B);
                    break;
                case 6:
                    bit_Cal(10, 0x7F, 0x7B);
                    break;
                case 7:
                    bit_Cal(10, 0x7F, 0x25);
                    break;
                case 8:
                    bit_Cal(10, 0x7F, 0x7F);
                    break;
                case 9:
                    bit_Cal(10, 0x7F, 0x6F);
                    break;
                default:
                    bit_Cal(10, 0x7F, 0x08);
                    break;
            }
            
            if(Temp.Unit)
            {
                /**********华氏度℉**********/
                bit_Cal(12, 0x01, 0x01);
                /**********‘℃’图标**********/
                bit_Cal(11, 0x01, 0x00);
            }
            else
            {
                /**********华氏度℉**********/
                bit_Cal(12, 0x01, 0x00);
                /**********‘℃’图标**********/
                bit_Cal(11, 0x01, 0x01);
            }
            
            /**********实际温度小数点**********/
//            bit_Cal(16, 0x01, 0x01);
            
            /**********设定温度小数点**********/
            bit_Cal(10, 0x80, 0x80);
        }
        else
        {
            HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
            __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 399);//背光pwm
        }
    }
    else
    {
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 200);//背光pwm
        memset(seg, 0, sizeof(seg));//清空数组  
        
        /**********实际温度**********/
        if (dis_rel_temp >= 0)//大于等于0时
        {
            Val = dis_rel_temp / 1000 % 10;
        }
        else if (dis_rel_temp < 0 && dis_rel_temp > -100)
        {
            Val = ABS(dis_rel_temp) / 1000 % 10;//计算后是0，不大于999所以不会显示
        }
        else if (dis_rel_temp <= -100 && dis_rel_temp > -1000)
        {
            Val = 10;//显示“-”
        }
        switch (Val)
        {
            case 0:
                if (dis_rel_temp > 999)//显示0
                {
                    bit_Cal(14, 0xFE, 0xEE);
                }
                else//不显示
                {
                    bit_Cal(14, 0xFE, 0x00);
                }
                break;
            case 1:
                bit_Cal(14, 0xFE, 0x24);
                break;
            case 2:
                bit_Cal(14, 0xFE, 0xBA);
                break;
            case 3:
                bit_Cal(14, 0xFE, 0xB6);
                break;
            case 4:
                bit_Cal(14, 0xFE, 0x74);
                break;
            case 5:
                bit_Cal(14, 0xFE, 0xD6);
                break;
            case 6:
                bit_Cal(14, 0xFE, 0xDE);
                break;
            case 7:
                bit_Cal(14, 0xFE, 0xA4);
                break;
            case 8:
                bit_Cal(14, 0xFE, 0xFE);
                break;
            case 9:
                bit_Cal(14, 0xFE, 0xF6);
                break;
            default:
                bit_Cal(14, 0xFE, 0x10);
                break;
        }
        if (dis_rel_temp >= 0)//大于等于0时
        {
            Val = dis_rel_temp / 100 % 10;
        }
        else if (dis_rel_temp < 0 && dis_rel_temp > -100)
        {
            Val = 10;//显示“-”
        }
        else if (dis_rel_temp <= -100 && dis_rel_temp > -1000)
        {
            Val = ABS(dis_rel_temp)/ 100 % 10;
        }
        switch (Val)
        {
            case 0:
                if (dis_rel_temp > 99)//显示0
                {
                    bit_Cal(15, 0xFE, 0xEE);
                }
                else//不显示
                {
                    bit_Cal(15, 0xFE, 0x00);
                }
                break;
            case 1:
                bit_Cal(15, 0xFE, 0x24);
                break;
            case 2:
                bit_Cal(15, 0xFE, 0xBA);
                break;
            case 3:
                bit_Cal(15, 0xFE, 0xB6);
                break;
            case 4:
                bit_Cal(15, 0xFE, 0x74);
                break;
            case 5:
                bit_Cal(15, 0xFE, 0xD6);
                break;
            case 6:
                bit_Cal(15, 0xFE, 0xDE);
                break;
            case 7:
                bit_Cal(15, 0xFE, 0xA4);
                break;
            case 8:
                bit_Cal(15, 0xFE, 0xFE);
                break;
            case 9:
                bit_Cal(15, 0xFE, 0xF6);
                break;
            default:
                bit_Cal(15, 0xFE, 0x10);
                break;
        }
        if (dis_rel_temp >= 0)//大于等于0时
        {
            Val = dis_rel_temp / 10 % 10;
        }
        else if (dis_rel_temp < 0 && dis_rel_temp > -100)
        {
            Val = ABS(dis_rel_temp) / 10 % 10;
        }
        else if (dis_rel_temp <= -100 && dis_rel_temp > -1000)
        {
            Val = ABS(dis_rel_temp) / 10 % 10;
        }
        switch (Val)
        {
            case 0:
                bit_Cal(16, 0xFE, 0xEE);
                break;
            case 1:
                bit_Cal(16, 0xFE, 0x24);
                break;
            case 2:
                bit_Cal(16, 0xFE, 0xBA);
                break;
            case 3:
                bit_Cal(16, 0xFE, 0xB6);
                break;
            case 4:
                bit_Cal(16, 0xFE, 0x74);
                break;
            case 5:
                bit_Cal(16, 0xFE, 0xD6);
                break;
            case 6:
                bit_Cal(16, 0xFE, 0xDE);
                break;
            case 7:
                bit_Cal(16, 0xFE, 0xA4);
                break;
            case 8:
                bit_Cal(16, 0xFE, 0xFE);
                break;
            case 9:
                bit_Cal(16, 0xFE, 0xF6);
                break;
            default:
                bit_Cal(16, 0xFE, 0x10);
                break;
        }
        
        if (dis_rel_temp >= 0)//大于等于0时
        {
            Val = dis_rel_temp % 10;
        }
        else if (dis_rel_temp < 0 && dis_rel_temp > -100)
        {
            Val = ABS(dis_rel_temp) % 10;
        }
        else if (dis_rel_temp <= -100 && dis_rel_temp > -1000)
        {
            Val = ABS(dis_rel_temp) % 10;
        }
        switch (Val)
        {
            case 0:
                bit_Cal(17, 0xFE, 0xEE);
                break;
            case 1:
                bit_Cal(17, 0xFE, 0x24);
                break;
            case 2:
                bit_Cal(17, 0xFE, 0xBA);
                break;
            case 3:
                bit_Cal(17, 0xFE, 0xB6);
                break;
            case 4:
                bit_Cal(17, 0xFE, 0x74);
                break;
            case 5:
                bit_Cal(17, 0xFE, 0xD6);
                break;
            case 6:
                bit_Cal(17, 0xFE, 0xDE);
                break;
            case 7:
                bit_Cal(17, 0xFE, 0xA4);
                break;
            case 8:
                bit_Cal(17, 0xFE, 0xFE);
                break;
            case 9:
                bit_Cal(17, 0xFE, 0xF6);
                break;
            default:
                bit_Cal(17, 0xFE, 0x10);
                break;
        }
        /**********设定温度**********/
        if(Temp_ShowFlag)
        {
            bit_Cal(13, 0xFE, 0x00);//不显示
            bit_Cal(12, 0xFE, 0x00);//不显示
            bit_Cal(11, 0xFE, 0x00);//不显示
            bit_Cal(10, 0x7F, 0x00);//不显示
        }
        else
        {
            if(dis_set_temp == 0)
            {
                bit_Cal(13, 0xFE, 0x10);//显示“-”
                bit_Cal(12, 0xFE, 0x10);//显示“-”
                bit_Cal(11, 0xFE, 0x10);//显示“-”
                bit_Cal(10, 0x7F, 0x08);//显示“-”
            }
            else
            {
                if (dis_set_temp >= 0)//大于等于0时
                {
                    Val = dis_set_temp / 1000 % 10;
                }
                else if (dis_set_temp < 0 && dis_set_temp > -100)
                {
                    Val = ABS(dis_set_temp) / 1000 % 10;//计算后是0，不大于999所以不会显示
                }
                else if (dis_set_temp <= -100 && dis_set_temp > -1000)
                {
                    Val = 10;//显示“-”
                }
                switch (Val)
                {
                    case 0:
                        if (dis_set_temp > 999)//显示零
                        {
                            bit_Cal(13, 0xFE, 0xEE);
                        }
                        else//不显示
                        {
                            bit_Cal(13, 0xFE, 0x00);
                        }
                        break;
                    case 1:
                        bit_Cal(13, 0xFE, 0x48);
                        break;
                    case 2:
                        bit_Cal(13, 0xFE, 0xBA);
                        break;
                    case 3:
                        bit_Cal(13, 0xFE, 0xDA);
                        break;
                    case 4:
                        bit_Cal(13, 0xFE, 0x5C);
                        break;
                    case 5:
                        bit_Cal(13, 0xFE, 0xD6);
                        break;
                    case 6:
                        bit_Cal(13, 0xFE, 0xF6);
                        break;
                    case 7:
                        bit_Cal(13, 0xFE, 0x4A);
                        break;
                    case 8:
                        bit_Cal(13, 0xFE, 0xFE);
                        break;
                    case 9:
                        bit_Cal(13, 0xFE, 0xDE);
                        break;
                    default:
                        bit_Cal(13, 0xFE, 0x10);
                        break;
                }
                
                if (dis_set_temp >= 0)//大于等于0时
                {
                    Val = dis_set_temp / 100 % 10;
                }
                else if (dis_set_temp < 0 && dis_set_temp > -100)
                {
                    Val = 10;//显示“-”
                }
                else if (dis_set_temp <= -100 && dis_set_temp > -1000)
                {
                    Val = ABS(dis_set_temp)/ 100 % 10;
                }
                switch (Val)
                {
                    case 0:
                        if (dis_set_temp > 99)//显示零
                        {
                            bit_Cal(12, 0xFE, 0xEE);
                        }
                        else//不显示
                        {
                            bit_Cal(12, 0xFE, 0x00);
                        }
                        break;
                    case 1:
                        bit_Cal(12, 0xFE, 0x48);
                        break;
                    case 2:
                        bit_Cal(12, 0xFE, 0xBA);
                        break;
                    case 3:
                        bit_Cal(12, 0xFE, 0xDA);
                        break;
                    case 4:
                        bit_Cal(12, 0xFE, 0x5C);
                        break;
                    case 5:
                        bit_Cal(12, 0xFE, 0xD6);
                        break;
                    case 6:
                        bit_Cal(12, 0xFE, 0xF6);
                        break;
                    case 7:
                        bit_Cal(12, 0xFE, 0x4A);
                        break;
                    case 8:
                        bit_Cal(12, 0xFE, 0xFE);
                        break;
                    case 9:
                        bit_Cal(12, 0xFE, 0xDE);
                        break;
                    default:
                        bit_Cal(12, 0xFE, 0x10);
                        break;
                }
                
                if (dis_set_temp >= 0)//大于等于0时
                {
                    Val = dis_set_temp / 10 % 10;
                }
                else if (dis_set_temp < 0 && dis_set_temp > -100)
                {
                    Val = ABS(dis_set_temp) / 10 % 10;
                }
                else if (dis_set_temp <= -100 && dis_set_temp > -1000)
                {
                    Val = ABS(dis_set_temp) / 10 % 10;
                }
                switch (Val)
                {
                    case 0:
                        bit_Cal(11, 0xFE, 0xEE);
                        break;
                    case 1:
                        bit_Cal(11, 0xFE, 0x48);
                        break;
                    case 2:
                        bit_Cal(11, 0xFE, 0xBA);
                        break;
                    case 3:
                        bit_Cal(11, 0xFE, 0xDA);
                        break;
                    case 4:
                        bit_Cal(11, 0xFE, 0x5C);
                        break;
                    case 5:
                        bit_Cal(11, 0xFE, 0xD6);
                        break;
                    case 6:
                        bit_Cal(11, 0xFE, 0xF6);
                        break;
                    case 7:
                        bit_Cal(11, 0xFE, 0x4A);
                        break;
                    case 8:
                        bit_Cal(11, 0xFE, 0xFE);
                        break;
                    case 9:
                        bit_Cal(11, 0xFE, 0xDE);
                        break;
                    default:
                        bit_Cal(11, 0xFE, 0x10);
                        break;
                }
                
                if (dis_set_temp >= 0)//大于等于0时
                {
                    Val = dis_set_temp % 10;
                }
                else if (dis_set_temp < 0 && dis_set_temp > -100)
                {
                    Val = ABS(dis_set_temp) % 10;
                }
                else if (dis_set_temp <= -100 && dis_set_temp > -1000)
                {
                    Val = ABS(dis_set_temp) % 10;
                }
                switch (Val)
                {
                    case 0:
                        bit_Cal(10, 0x7F, 0x77);
                        break;
                    case 1:
                        bit_Cal(10, 0x7F, 0x24);
                        break;
                    case 2:
                        bit_Cal(10, 0x7F, 0x5D);
                        break;
                    case 3:
                        bit_Cal(10, 0x7F, 0x6D);
                        break;
                    case 4:
                        bit_Cal(10, 0x7F, 0x2E);
                        break;
                    case 5:
                        bit_Cal(10, 0x7F, 0x6B);
                        break;
                    case 6:
                        bit_Cal(10, 0x7F, 0x7B);
                        break;
                    case 7:
                        bit_Cal(10, 0x7F, 0x25);
                        break;
                    case 8:
                        bit_Cal(10, 0x7F, 0x7F);
                        break;
                    case 9:
                        bit_Cal(10, 0x7F, 0x6F);
                        break;
                    default:
                        bit_Cal(10, 0x7F, 0x08);
                        break;
                }
            }
        }
        
        /**********实际时间**********/
        if(dis_rel_time == 0)
        {
            bit_Cal(18, 0x7F, 0x08);//显示"-"
            bit_Cal(19, 0xFE, 0x10);//显示"-"
            bit_Cal(1, 0xFE, 0x10);//显示"-"
            bit_Cal(0, 0xFE, 0x10);//显示"-"
        }
        else
        {
            if(dis_rel_time >= 3600)
                Val = dis_rel_time / 3600 / 10;//计算十位为单位的小时数
            else if(dis_rel_time > 59)
                Val = dis_rel_time / 60 / 10;//计算十位为单位的小时数
            else if(dis_rel_time > 0)
                Val = 0;//计算十位为单位的小时数
            else Val = 10;//显示‘-’
            switch (Val)
            {
                case 0:
                    bit_Cal(18, 0x7F, 0x77);
                    break;
                case 1:
                    bit_Cal(18, 0x7F, 0x12);
                    break;
                case 2:
                    bit_Cal(18, 0x7F, 0x5D);
                    break;
                case 3:
                    bit_Cal(18, 0x7F, 0x5B);
                    break;
                case 4:
                    bit_Cal(18, 0x7F, 0x3A);
                    break;
                case 5:
                    bit_Cal(18, 0x7F, 0x6B);
                    break;
                case 6:
                    bit_Cal(18, 0x7F, 0x6F);
                    break;
                case 7:
                    bit_Cal(18, 0x7F, 0x52);
                    break;
                case 8:
                    bit_Cal(18, 0x7F, 0x7F);
                    break;
                case 9:
                    bit_Cal(18, 0x7F, 0x7B);
                    break;
                default:
                    bit_Cal(18, 0x7F, 0x08);
                    break;
            }

            if(dis_rel_time >= 3600)
                Val = dis_rel_time / 3600 % 10;//计算十位为单位的小时数
            else if(dis_rel_time > 59)
                Val = dis_rel_time / 60 % 10;//计算十位为单位的小时数
            else if(dis_rel_time > 0)
                Val = 0;//计算十位为单位的小时数
            else Val = 10;//显示‘-’
            switch (Val)
            {
                case 0:
                    bit_Cal(19, 0xFE, 0xEE);
                    break;
                case 1:
                    bit_Cal(19, 0xFE, 0x24);
                    break;
                case 2:
                    bit_Cal(19, 0xFE, 0xBA);
                    break;
                case 3:
                    bit_Cal(19, 0xFE, 0xB6);
                    break;
                case 4:
                    bit_Cal(19, 0xFE, 0x74);
                    break;
                case 5:
                    bit_Cal(19, 0xFE, 0xD6);
                    break;
                case 6:
                    bit_Cal(19, 0xFE, 0xDE);
                    break;
                case 7:
                    bit_Cal(19, 0xFE, 0xA4);
                    break;
                case 8:
                    bit_Cal(19, 0xFE, 0xFE);
                    break;
                case 9:
                    bit_Cal(19, 0xFE, 0xF6);
                    break;
                default:
                    bit_Cal(19, 0xFE, 0x10);
                    break;
            }

            if(dis_rel_time >= 3600)
                Val = dis_rel_time % 3600 / 60 / 10;//计算十位为单位的小时数
            else if(dis_rel_time > 59)
                Val = dis_rel_time % 60 / 10;//计算十位为单位的小时数
            else if(dis_rel_time > 0)
                Val = dis_rel_time % 60 / 10;//计算十位为单位的小时数
            else Val = 10;//显示‘-’
            switch (Val)
            {
                case 0:
                    bit_Cal(1, 0xFE, 0xEE);
                    break;
                case 1:
                    bit_Cal(1, 0xFE, 0x24);
                    break;
                case 2:
                    bit_Cal(1, 0xFE, 0xBA);
                    break;
                case 3:
                    bit_Cal(1, 0xFE, 0xB6);
                    break;
                case 4:
                    bit_Cal(1, 0xFE, 0x74);
                    break;
                case 5:
                    bit_Cal(1, 0xFE, 0xD6);
                    break;
                case 6:
                    bit_Cal(1, 0xFE, 0xDE);
                    break;
                case 7:
                    bit_Cal(1, 0xFE, 0xA4);
                    break;
                case 8:
                    bit_Cal(1, 0xFE, 0xFE);
                    break;
                case 9:
                    bit_Cal(1, 0xFE, 0xF6);
                    break;
                default:
                    bit_Cal(1, 0xFE, 0x10);
                    break;
            }

            if(dis_rel_time >= 3600)
                Val = dis_rel_time % 3600 / 60 % 10;//计算十位为单位的小时数
            else if(dis_rel_time > 59)
                Val = dis_rel_time % 60 % 10;//计算十位为单位的小时数
            else if(dis_rel_time > 0)
                Val = dis_rel_time % 60 % 10;//计算十位为单位的小时数
            else Val = 10;//显示‘-’
            switch (Val)
            {
                case 0:
                    bit_Cal(0, 0xFE, 0xEE);
                    break;
                case 1:
                    bit_Cal(0, 0xFE, 0x24);
                    break;
                case 2:
                    bit_Cal(0, 0xFE, 0xBA);
                    break;
                case 3:
                    bit_Cal(0, 0xFE, 0xB6);
                    break;
                case 4:
                    bit_Cal(0, 0xFE, 0x74);
                    break;
                case 5:
                    bit_Cal(0, 0xFE, 0xD6);
                    break;
                case 6:
                    bit_Cal(0, 0xFE, 0xDE);
                    break;
                case 7:
                    bit_Cal(0, 0xFE, 0xA4);
                    break;
                case 8:
                    bit_Cal(0, 0xFE, 0xFE);
                    break;
                case 9:
                    bit_Cal(0, 0xFE, 0xF6);
                    break;
                default:
                    bit_Cal(0, 0xFE, 0x10);
                    break;
            }
        }
        
        /**********设定时间**********/
        if(!Time_ShowFlag)
        {
            if(dis_set_time == 0)
            {
                bit_Cal(2, 0x7F, 0x08);//显示"-"
                bit_Cal(3, 0x7F, 0x08);//显示"-"
                bit_Cal(4, 0x7F, 0x08);//显示"-"
                bit_Cal(5, 0x7F, 0x08);//显示"-"
            }
            else
            {
                if(dis_set_time >= 3600)
                    Val = dis_set_time / 3600 / 10;//计算十位为单位的小时数
                else if(dis_set_time > 59)
                    Val = dis_set_time / 60 / 10;//计算十位为单位的小时数
                else if(dis_set_time > 0)
                    Val = 0;//计算十位为单位的小时数
                else Val = 10;//显示‘-’
                switch (Val)
                {
                    case 0:
                        bit_Cal(5, 0x7F, 0x77);
                        break;
                    case 1:
                        bit_Cal(5, 0x7F, 0x12);
                        break;
                    case 2:
                        bit_Cal(5, 0x7F, 0x5D);
                        break;
                    case 3:
                        bit_Cal(5, 0x7F, 0x5B);
                        break;
                    case 4:
                        bit_Cal(5, 0x7F, 0x3A);
                        break;
                    case 5:
                        bit_Cal(5, 0x7F, 0x6B);
                        break;
                    case 6:
                        bit_Cal(5, 0x7F, 0x6F);
                        break;
                    case 7:
                        bit_Cal(5, 0x7F, 0x52);
                        break;
                    case 8:
                        bit_Cal(5, 0x7F, 0x7F);
                        break;
                    case 9:
                        bit_Cal(5, 0x7F, 0x7B);
                        break;
                    default:
                        bit_Cal(5, 0x7F, 0x08);
                        break;
                }

                if(dis_set_time >= 3600)
                    Val = dis_set_time / 3600 % 10;//计算十位为单位的小时数
                else if(dis_set_time > 59)
                    Val = dis_set_time / 60 % 10;//计算十位为单位的小时数
                else if(dis_set_time > 0)
                    Val = 0;//计算十位为单位的小时数
                else Val = 10;//显示‘-’
                switch (Val)
                {
                    case 0:
                        bit_Cal(4, 0x7F, 0x77);
                        break;
                    case 1:
                        bit_Cal(4, 0x7F, 0x12);
                        break;
                    case 2:
                        bit_Cal(4, 0x7F, 0x5D);
                        break;
                    case 3:
                        bit_Cal(4, 0x7F, 0x5B);
                        break;
                    case 4:
                        bit_Cal(4, 0x7F, 0x3A);
                        break;
                    case 5:
                        bit_Cal(4, 0x7F, 0x6B);
                        break;
                    case 6:
                        bit_Cal(4, 0x7F, 0x6F);
                        break;
                    case 7:
                        bit_Cal(4, 0x7F, 0x52);
                        break;
                    case 8:
                        bit_Cal(4, 0x7F, 0x7F);
                        break;
                    case 9:
                        bit_Cal(4, 0x7F, 0x7B);
                        break;
                    default:
                        bit_Cal(4, 0x7F, 0x08);
                        break;
                }

                if(dis_set_time >= 3600)
                    Val = dis_set_time % 3600 / 60 / 10;//计算十位为单位的小时数
                else if(dis_set_time > 59)
                    Val = dis_set_time % 60 / 10;//计算十位为单位的小时数
                else if(dis_set_time > 0)
                    Val = dis_set_time % 60 / 10;//计算十位为单位的小时数
                else Val = 10;//显示‘-’
                switch (Val)
                {
                    case 0:
                        bit_Cal(3, 0x7F, 0x77);
                        break;
                    case 1:
                        bit_Cal(3, 0x7F, 0x12);
                        break;
                    case 2:
                        bit_Cal(3, 0x7F, 0x5D);
                        break;
                    case 3:
                        bit_Cal(3, 0x7F, 0x5B);
                        break;
                    case 4:
                        bit_Cal(3, 0x7F, 0x3A);
                        break;
                    case 5:
                        bit_Cal(3, 0x7F, 0x6B);
                        break;
                    case 6:
                        bit_Cal(3, 0x7F, 0x6F);
                        break;
                    case 7:
                        bit_Cal(3, 0x7F, 0x52);
                        break;
                    case 8:
                        bit_Cal(3, 0x7F, 0x7F);
                        break;
                    case 9:
                        bit_Cal(3, 0x7F, 0x7B);
                        break;
                    default:
                        bit_Cal(3, 0x7F, 0x08);
                        break;
                }

                if(dis_set_time >= 3600)
                    Val = dis_set_time % 3600 / 60 % 10;//计算十位为单位的小时数
                else if(dis_set_time > 59)
                    Val = dis_set_time % 60 % 10;//计算十位为单位的小时数
                else if(dis_set_time > 0)
                    Val = dis_set_time % 60 % 10;//计算十位为单位的小时数
                else Val = 10;//显示‘-’
                switch (Val)
                {
                    case 0:
                        bit_Cal(2, 0x7F, 0x77);
                        break;
                    case 1:
                        bit_Cal(2, 0x7F, 0x12);
                        break;
                    case 2:
                        bit_Cal(2, 0x7F, 0x5D);
                        break;
                    case 3:
                        bit_Cal(2, 0x7F, 0x5B);
                        break;
                    case 4:
                        bit_Cal(2, 0x7F, 0x3A);
                        break;
                    case 5:
                        bit_Cal(2, 0x7F, 0x6B);
                        break;
                    case 6:
                        bit_Cal(2, 0x7F, 0x6F);
                        break;
                    case 7:
                        bit_Cal(2, 0x7F, 0x52);
                        break;
                    case 8:
                        bit_Cal(2, 0x7F, 0x7F);
                        break;
                    case 9:
                        bit_Cal(2, 0x7F, 0x7B);
                        break;
                    default:
                        bit_Cal(2, 0x7F, 0x08);
                        break;
                }
            }
        }
        else//不显示时间
        {
            bit_Cal(2, 0x7F, 0x00);
            bit_Cal(3, 0x7F, 0x00);
            bit_Cal(4, 0x7F, 0x00);
            bit_Cal(5, 0x7F, 0x00);
        }
        
        /**********P模式**********/
        if(PMode.Status)
        {
            PMode.Light_BIT = 0x0FFF; // 全部点亮
        }
        else
        {
            PMode.Light_BIT = 0x0000; // 全部熄灭
        }
        
        /**********L1**********/
        if(PMode.Light_BIT & BIT0)
        {
            bit_Cal(9, 0x10, 0x10);
        }
        else
        {
            bit_Cal(9, 0x10, 0x00);
        }
        
        /**********L2**********/
        if(PMode.Light_BIT & BIT1)
        {
            bit_Cal(9, 0x08, 0x08);
        }
        else
        {
            bit_Cal(9, 0x08, 0x00);
        }
        
        /**********L3**********/
        if(PMode.Light_BIT & BIT2)
        {
            bit_Cal(9, 0x04, 0x04);
        }
        else
        {
            bit_Cal(9, 0x04, 0x00);
        }
        
        /**********L4**********/
        if(PMode.Light_BIT & BIT3)
        {
            bit_Cal(9, 0x02, 0x02);
        }
        else
        {
            bit_Cal(9, 0x02, 0x00);
        }
        
        /**********L5**********/
        if(PMode.Light_BIT & BIT4)
        {
            bit_Cal(9, 0x01, 0x01);
        }
        else
        {
            bit_Cal(9, 0x01, 0x00);
        }
        
        /**********L6**********/
        if(PMode.Light_BIT & BIT5)
        {
            bit_Cal(13, 0x01, 0x01);
        }
        else
        {
            bit_Cal(13, 0x01, 0x00);
        }
        
        /**********L7**********/
        if(PMode.Light_BIT & BIT6)
        {
            bit_Cal(6, 0x80, 0x80);
        }
        else
        {
            bit_Cal(6, 0x80, 0x00);
        }
        
        /**********L8**********/
        if(PMode.Light_BIT & BIT7)
        {
            bit_Cal(7, 0x80, 0x80);
        }
        else
        {
            bit_Cal(7, 0x80, 0x00);
        }
        
        /**********L9**********/
        if(PMode.Light_BIT & BIT8)
        {
            bit_Cal(8, 0x80, 0x80);
        }
        else
        {
            bit_Cal(8, 0x80, 0x00);
        }
        
        /**********L10**********/
        if(PMode.Light_BIT & BIT9)
        {
            bit_Cal(9, 0x80, 0x80);
        }
        else
        {
            bit_Cal(9, 0x80, 0x00);
        }
        
        /**********L11**********/
        if(PMode.Light_BIT & BIT10)
        {
            bit_Cal(9, 0x40, 0x40);
        }
        else
        {
            bit_Cal(9, 0x40, 0x00);
        }
        
        /**********L12**********/
        if(PMode.Light_BIT & BIT11)
        {
            bit_Cal(9, 0x20, 0x20);
        }
        else
        {
            bit_Cal(9, 0x20, 0x00);
        }
        
        if (PMode.Status) // 在P模式下
        {
            if (!Pmode_ShowFlag)
            {
                bit_Cal(8, 0x7F, 0x1F);//P
                /**********‘-’**********/
                bit_Cal(7, 0x7F, 0x08);//-
                switch (PMode_Option)
                {
                    case 0:
                        bit_Cal(6, 0x7F, 0x77);
                        break;
                    case 1:
                        bit_Cal(6, 0x7F, 0x24);
                        break;
                    case 2:
                        bit_Cal(6, 0x7F, 0x5D);
                        break;
                    case 3:
                        bit_Cal(6, 0x7F, 0x6D);
                        break;
                    case 4:
                        bit_Cal(6, 0x7F, 0x2E);
                        break;
                    case 5:
                        bit_Cal(6, 0x7F, 0x6B);
                        break;
                    case 6:
                        bit_Cal(6, 0x7F, 0x7B);
                        break;
                    case 7:
                        bit_Cal(6, 0x7F, 0x25);
                        break;
                    case 8:
                        bit_Cal(6, 0x7F, 0x7F);
                        break;
                    case 9:
                        bit_Cal(6, 0x7F, 0x6F);
                        break;
                    default:
                        bit_Cal(6, 0x7F, 0x08);
                        break;
                }
            }
            else
            {
                bit_Cal(6, 0x7F, 0x00);//不显示
                bit_Cal(7, 0x7F, 0x00);//不显示
                bit_Cal(8, 0x7F, 0x00);//不显示
            }
        }
        else
        {
            bit_Cal(6, 0x7F, 0x00);//不显示
            bit_Cal(7, 0x7F, 0x00);//不显示
            bit_Cal(8, 0x7F, 0x00);//不显示
        }
        
        
        /*************图标***************/
        /**********温度单位图标**********/
        if(Temp.Unit)
        {
            /**********华氏度℉**********/
            bit_Cal(12, 0x01, 0x01);
            /**********‘℃’图标**********/
            bit_Cal(11, 0x01, 0x00);
        }
        else
        {
            /**********华氏度℉**********/
            bit_Cal(12, 0x01, 0x00);
            /**********‘℃’图标**********/
            bit_Cal(11, 0x01, 0x01);
        }
        
        /**********实际温度小数点**********/
        bit_Cal(16, 0x01, 0x01);
        
        /**********设定温度小数点**********/
        bit_Cal(10, 0x80, 0x80);
        
        /*************加热图标***************/
        if(TempIcn_ShowFlag == 0)
        {
            /**********加热图标**********/
            bit_Cal(17, 0x01, 0x01);
            bit_Cal(15, 0x01, 0x01);//加热图标下面的横杠
        }
        else
        {
            /**********不显示加热图标**********/
            bit_Cal(17, 0x01, 0x00);
            bit_Cal(15, 0x01, 0x00);//加热图标下面的横杠
        }
        
        /**********锁定图标**********/
//        if(sys.Lock && !Lock_ShowFlag)
//        {
//            bit_Cal(18, 0x80, 0x80);//锁定
//        }
//        else
//        {
//            bit_Cal(18, 0x80, 0x00);//不显示锁定
//        }
        
        /**********‘HOT’图标**********/
        bit_Cal(5, 0x80, 0x00);//HOT
        bit_Cal(4, 0x80, 0x00);//！
        
        /**********时间单位图标**********/
        if(dis_set_time < 3600)
        {
            /**********‘sec’图标**********/
            bit_Cal(0, 0x01, 0x01);
            /**********‘min’图标**********/
            bit_Cal(1, 0x01, 0x00);
        }
        else
        {
            /**********‘sec’图标**********/
            bit_Cal(0, 0x01, 0x00);
            /**********‘min’图标**********/
            bit_Cal(1, 0x01, 0x01);
        }
        
        /**********实际时间冒号图标**********/
        bit_Cal(19, 0x01, 0x01);
        
        /**********设定时间冒号图标**********/
        bit_Cal(3, 0x80, 0x80);
        
        /**********时间图标**********/
        if(TimeIcn_ShowFlag == 0)
        {
            bit_Cal(2, 0x80, 0x80);//时间图标
        }
        else
        {
            bit_Cal(2, 0x80, 0x00);//不显示时间图标
        }
    }
    /**********数据发送**********/
    for(uint8_t i=0;i<20;i++)
    {
        Write_Addr_Dat_N(i*2, seg[i], 1);
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

/*
*****************************************************************
 * 函数原型： void Show_Display(void)
 * 功    能： 显示屏幕内容
*****************************************************************
*/
void Show_Display(void)
{
//    Temp.Display_Rel = CelsiusToFahrenheit(Temp.Unit,Temp_Rel);
//    Temp.Display_Set = CelsiusToFahrenheit(Temp.Unit,Temp_Set);
    Temp.Display_Rel = Temp.Rel;//后期处理
    Temp.Display_Set = Temp.Set;
    Time.Display_Rel = Time.Rel;
    Time.Display_Set = Time.Set;
    Display(Temp.Display_Set,Temp.Display_Rel,Time.Display_Set,Time.Display_Rel,PMode.Option);
}
