#include "Show.h"

/**********全局变量声明******/
float Twinkle_Time;//闪烁时间

/**********局部变量声明******/
uint8_t Temp_ShowFlag,Time_ShowFlag;//温度、时间显示的标志位 0:常亮 1：熄灭
uint8_t TempIcn_ShowFlag,TimeIcn_ShowFlag;//加热图标闪烁和时间图标闪烁

/*
*****************************************************************
 * 函数原型：static void Icn_Twinkle(float dT)
 * 功    能：图标闪烁
 * 调    用：内部调用
*****************************************************************
*/
static void Icn_Twinkle(float dT)
{
	static float T,T1;
	if(sys.Run_Status == 1)		
	{
		T += dT;
		if(T >= 0.08f)
		{
            TempIcn_ShowFlag ++;//速度图标闪烁;
            if(TempIcn_ShowFlag > 2)
                TempIcn_ShowFlag = 0;
            T = 0;
		}
        
        T1 += dT;
		if(T1 >= 0.5f)
		{
			if(Time.Rel)
				TimeIcn_ShowFlag = ~TimeIcn_ShowFlag;//时间图标闪烁;
            else
            {
                TimeIcn_ShowFlag = 0;
            }
            T1 = 0;
        }
	}
	else
	{
		TempIcn_ShowFlag = 0;//不显示温度图标
		TimeIcn_ShowFlag = 0;//不显示时间图标
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
	static float T;
    if(sys.SetMode_Option == 0)//如果没在设置选项中，则都点亮，不闪烁
    {
        Temp_ShowFlag = 0;//常亮
        Time_ShowFlag = 0;//常亮
        Twinkle_Time = 0;//闪烁计时清零
        return;
    }
    if(Twinkle_Time && Key_Status==0)//闪烁和没有操作按键时
    {
		T += dT;
		if(T >= 0.5f)
		{
			Twinkle_Time -= 0.5;//闪烁计时
			if(sys.SetMode_Option == 1)//设置温度
			{
				Temp_ShowFlag = ~Temp_ShowFlag;//温度闪烁
				Time_ShowFlag = 0;//时间常亮
			}
			else if(sys.SetMode_Option == 2)//设置时间
			{
				Temp_ShowFlag = 0;//温度常亮
				Time_ShowFlag = ~Time_ShowFlag;//时间闪烁		
			}
			if(Twinkle_Time == 0)//如果闪烁结束
			{
				sys.SetMode_Option = 0;//模式选择清零
			} 
			T = 0;			
		}			
    }
	else
	{
        Temp_ShowFlag = 0;//常亮
        Time_ShowFlag = 0;//常亮
		T = 0;
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
	Icn_Twinkle(dT);//图标闪烁
}

uint8_t seg[10] = {0};

/**
 * @brief 位数计算
 *
 * @param *bit1 输入的位数
 * @param num 与等于的数
 * @param num1 或等于的数
 */
void bit_Cal(uint8_t bit1,uint8_t num,uint8_t num1)
{
    seg[bit1] &= (0xFF-num);seg[bit1] |= num1;
}

/*
*****************************************************************
 * 函数原型：void Display_Time(int16_t dis_time)
 * 功    能：显示时间
 * 输    入: dis_time 时间
 * 参    数：int32_t dis_time
*****************************************************************
*/
void Display_Time(int16_t dis_time)
{
    uint8_t Val;// 用于百十个取出来的数字
    
    if(sys.Run_Status == 1)
    {
        if(sys.SetMode_Option == 1)
        {
            if(!Temp_ShowFlag)
            {
                if(Temp.Set == 1)//高温
                {
                    /**********加热图标中间火**********/
                    bit_Cal(0, 0x80, 0x80);bit_Cal(1, 0x01, 0x01);
                    
                    /**********加热图标两边火**********/
                    bit_Cal(0, 0x60, 0x60);bit_Cal(1, 0x06, 0x06);
                    
                    /**********加热图标底部杠**********/
                    bit_Cal(0, 0x18, 0x18);
                }
                else
                {
                    /**********加热图标中间火**********/
                    bit_Cal(0, 0x80, 0x80);bit_Cal(1, 0x01, 0x01);
                    
                    /**********加热图标两边火**********/
                    bit_Cal(0, 0x60, 0x00);bit_Cal(1, 0x06, 0x00);
                    
                    /**********加热图标底部杠**********/
                    bit_Cal(0, 0x18, 0x18);
                }
            }
            else
            {
                /**********加热图标中间火**********/
                bit_Cal(0, 0x80, 0x00);bit_Cal(1, 0x01, 0x00);
                
                /**********加热图标两边火**********/
                bit_Cal(0, 0x60, 0x00);bit_Cal(1, 0x06, 0x00);
                
                /**********加热图标底部杠**********/
                bit_Cal(0, 0x18, 0x00);
            }
        }
        else
        {
            if(Temp.Set == 1)//高温
            {
                if(TempIcn_ShowFlag == 0)
                {
                    /**********加热图标中间火**********/
                    bit_Cal(0, 0x80, 0x00);bit_Cal(1, 0x01, 0x01);//D1
                    
                    /**********加热图标两边火**********/
                    bit_Cal(0, 0x60, 0x40);bit_Cal(1, 0x06, 0x04);//B F
                    
                    /**********加热图标底部杠**********/
                    bit_Cal(0, 0x18, 0x18);
                }
                else if(TempIcn_ShowFlag == 1)
                {
                    /**********加热图标中间火**********/
                    bit_Cal(0, 0x80, 0x80);bit_Cal(1, 0x01, 0x00);//C1
                    
                    /**********加热图标两边火**********/
                    bit_Cal(0, 0x60, 0x20);bit_Cal(1, 0x06, 0x02);//A E
                    
                    /**********加热图标底部杠**********/
                    bit_Cal(0, 0x18, 0x18);
                }
                else
                {
                    /**********加热图标中间火**********/
                    bit_Cal(0, 0x80, 0x80);bit_Cal(1, 0x01, 0x01);
                    
                    /**********加热图标两边火**********/
                    bit_Cal(0, 0x60, 0x60);bit_Cal(1, 0x06, 0x06);
                    
                    /**********加热图标底部杠**********/
                    bit_Cal(0, 0x18, 0x18);
                }
            }
            else
            {
                if(TempIcn_ShowFlag == 0)
                {
                    /**********加热图标中间火**********/
                    bit_Cal(0, 0x80, 0x00);bit_Cal(1, 0x01, 0x01);//D1
                    
                    /**********加热图标两边火**********/
                    bit_Cal(0, 0x60, 0x00);bit_Cal(1, 0x06, 0x00);//B F
                    
                    /**********加热图标底部杠**********/
                    bit_Cal(0, 0x18, 0x18);
                }
                else if(TempIcn_ShowFlag == 1)
                {
                    /**********加热图标中间火**********/
                    bit_Cal(0, 0x80, 0x80);bit_Cal(1, 0x01, 0x00);//C1
                    
                    /**********加热图标两边火**********/
                    bit_Cal(0, 0x60, 0x00);bit_Cal(1, 0x06, 0x00);//A E
                    
                    /**********加热图标底部杠**********/
                    bit_Cal(0, 0x18, 0x18);
                }
                else
                {
                    /**********加热图标中间火**********/
                    bit_Cal(0, 0x80, 0x80);bit_Cal(1, 0x01, 0x01);
                    
                    /**********加热图标两边火**********/
                    bit_Cal(0, 0x60, 0x00);bit_Cal(1, 0x06, 0x00);
                    
                    /**********加热图标底部杠**********/
                    bit_Cal(0, 0x18, 0x18);
                }
            }
        }
    }
    else
    {
        if(!Temp_ShowFlag)
        {
            if(Temp.Set == 1)//高温
            {
                /**********加热图标中间火**********/
                bit_Cal(0, 0x80, 0x80);bit_Cal(1, 0x01, 0x01);
                
                /**********加热图标两边火**********/
                bit_Cal(0, 0x60, 0x60);bit_Cal(1, 0x06, 0x06);
                
                /**********加热图标底部杠**********/
                bit_Cal(0, 0x18, 0x18);
            }
            else
            {
                /**********加热图标中间火**********/
                bit_Cal(0, 0x80, 0x80);bit_Cal(1, 0x01, 0x01);
                
                /**********加热图标两边火**********/
                bit_Cal(0, 0x60, 0x00);bit_Cal(1, 0x06, 0x00);
                
                /**********加热图标底部杠**********/
                bit_Cal(0, 0x18, 0x18);
            }
        }
        else
        {
            /**********加热图标中间火**********/
            bit_Cal(0, 0x80, 0x00);bit_Cal(1, 0x01, 0x00);
            
            /**********加热图标两边火**********/
            bit_Cal(0, 0x60, 0x00);bit_Cal(1, 0x06, 0x00);
            
            /**********加热图标底部杠**********/
            bit_Cal(0, 0x18, 0x00);
        }
    }
    
    if(sys.Run_Status == 1)
    {
        if(sys.SetMode_Option == 2)
        {
            /**********时间冒号**********/
            bit_Cal(2, 0x08, 0x08);
            bit_Cal(4, 0x08, 0x08);
        }
        else
        {
            if(TimeIcn_ShowFlag)
            {
                /**********时间冒号**********/
                bit_Cal(2, 0x08, 0x00);
                bit_Cal(4, 0x08, 0x00);
            }
            else
            {
                /**********时间冒号**********/
                bit_Cal(2, 0x08, 0x08);
                bit_Cal(4, 0x08, 0x08);
            }
        }
    }
    else
    {
        bit_Cal(2, 0x08, 0x08);
        bit_Cal(4, 0x08, 0x08);
    }
    
    /**********min**********/
    bit_Cal(6, 0x08, 0x08);
    bit_Cal(8, 0x08, 0x08);
    
    if(!Time_ShowFlag)
    {
        if(Time.Set == 0)
        {
            bit_Cal(2, 0xF0, 0x10);bit_Cal(3, 0x07, 0x00);//显示"-"
            bit_Cal(4, 0xF0, 0x10);bit_Cal(5, 0x07, 0x00);//显示"-"
            bit_Cal(6, 0xF0, 0x10);bit_Cal(7, 0x07, 0x00);//显示"-"
            bit_Cal(8, 0xF0, 0x10);bit_Cal(9, 0x07, 0x00);//显示"-"
        }
        else
        {
            if(dis_time >= 3600)
                Val = dis_time / 3600 / 10;//计算十位为单位的小时数
            else if(dis_time > 59)
                Val = dis_time / 60 / 10;//计算十位为单位的小时数
            else if(dis_time > 0)
                Val = 0;//计算十位为单位的小时数
            else Val = 10;//显示‘-’
            switch (Val)
            {
                case 0:
                    bit_Cal(2, 0xF0, 0xE0);bit_Cal(3, 0x07, 0x07);
                    break;
                case 1:
                    bit_Cal(2, 0xF0, 0xC0);bit_Cal(3, 0x07, 0x00);
                    break;
                case 2:
                    bit_Cal(2, 0xF0, 0x70);bit_Cal(3, 0x07, 0x03);
                    break;
                case 3:
                    bit_Cal(2, 0xF0, 0xF0);bit_Cal(3, 0x07, 0x01);
                    break;
                case 4:
                    bit_Cal(2, 0xF0, 0xD0);bit_Cal(3, 0x07, 0x04);
                    break;
                case 5:
                    bit_Cal(2, 0xF0, 0xB0);bit_Cal(3, 0x07, 0x05);
                    break;
                case 6:
                    bit_Cal(2, 0xF0, 0xB0);bit_Cal(3, 0x07, 0x07);
                    break;
                case 7:
                    bit_Cal(2, 0xF0, 0xE0);bit_Cal(3, 0x07, 0x00);
                    break;
                case 8:
                    bit_Cal(2, 0xF0, 0xF0);bit_Cal(3, 0x07, 0x07);
                    break;
                case 9:
                    bit_Cal(2, 0xF0, 0xF0);bit_Cal(3, 0x07, 0x05);
                    break;
                default:
                    bit_Cal(2, 0xF0, 0x10);bit_Cal(3, 0x07, 0x00);
                    break;
            }

            if(dis_time >= 3600)
                Val = dis_time / 3600 % 10;//计算十位为单位的小时数
            else if(dis_time > 59)
                Val = dis_time / 60 % 10;//计算十位为单位的小时数
            else if(dis_time > 0)
                Val = 0;//计算十位为单位的小时数
            else Val = 10;//显示‘-’
            switch (Val)
            {
                case 0:
                    bit_Cal(4, 0xF0, 0xE0);bit_Cal(5, 0x07, 0x07);
                    break;
                case 1:
                    bit_Cal(4, 0xF0, 0xC0);bit_Cal(5, 0x07, 0x00);
                    break;
                case 2:
                    bit_Cal(4, 0xF0, 0x70);bit_Cal(5, 0x07, 0x03);
                    break;
                case 3:
                    bit_Cal(4, 0xF0, 0xF0);bit_Cal(5, 0x07, 0x01);
                    break;
                case 4:
                    bit_Cal(4, 0xF0, 0xD0);bit_Cal(5, 0x07, 0x04);
                    break;
                case 5:
                    bit_Cal(4, 0xF0, 0xB0);bit_Cal(5, 0x07, 0x05);
                    break;
                case 6:
                    bit_Cal(4, 0xF0, 0xB0);bit_Cal(5, 0x07, 0x07);
                    break;
                case 7:
                    bit_Cal(4, 0xF0, 0xE0);bit_Cal(5, 0x07, 0x00);
                    break;
                case 8:
                    bit_Cal(4, 0xF0, 0xF0);bit_Cal(5, 0x07, 0x07);
                    break;
                case 9:
                    bit_Cal(4, 0xF0, 0xF0);bit_Cal(5, 0x07, 0x05);
                    break;
                default:
                    bit_Cal(4, 0xF0, 0x10);bit_Cal(5, 0x07, 0x00);
                    break;
            }

            if(dis_time >= 3600)
                Val = dis_time % 3600 / 60 / 10;//计算十位为单位的小时数
            else if(dis_time > 59)
                Val = dis_time % 60 / 10;//计算十位为单位的小时数
            else if(dis_time > 0)
                Val = dis_time % 60 / 10;//计算十位为单位的小时数
            else Val = 10;//显示‘-’
            switch (Val)
            {
                case 0:
                    bit_Cal(6, 0xF0, 0xE0);bit_Cal(7, 0x07, 0x07);
                    break;
                case 1:
                    bit_Cal(6, 0xF0, 0xC0);bit_Cal(7, 0x07, 0x00);
                    break;
                case 2:
                    bit_Cal(6, 0xF0, 0x70);bit_Cal(7, 0x07, 0x03);
                    break;
                case 3:
                    bit_Cal(6, 0xF0, 0xF0);bit_Cal(7, 0x07, 0x01);
                    break;
                case 4:
                    bit_Cal(6, 0xF0, 0xD0);bit_Cal(7, 0x07, 0x04);
                    break;
                case 5:
                    bit_Cal(6, 0xF0, 0xB0);bit_Cal(7, 0x07, 0x05);
                    break;
                case 6:
                    bit_Cal(6, 0xF0, 0xB0);bit_Cal(7, 0x07, 0x07);
                    break;
                case 7:
                    bit_Cal(6, 0xF0, 0xE0);bit_Cal(7, 0x07, 0x00);
                    break;
                case 8:
                    bit_Cal(6, 0xF0, 0xF0);bit_Cal(7, 0x07, 0x07);
                    break;
                case 9:
                    bit_Cal(6, 0xF0, 0xF0);bit_Cal(7, 0x07, 0x05);
                    break;
                default:
                    bit_Cal(6, 0xF0, 0x10);bit_Cal(7, 0x07, 0x00);
                    break;
            }

            if(dis_time >= 3600)
                Val = dis_time % 3600 / 60 % 10;//计算十位为单位的小时数
            else if(dis_time > 59)
                Val = dis_time % 60 % 10;//计算十位为单位的小时数
            else if(dis_time > 0)
                Val = dis_time % 60 % 10;//计算十位为单位的小时数
            else Val = 10;//显示‘-’
            switch (Val)
            {
                case 0:
                    bit_Cal(8, 0xF0, 0xE0);bit_Cal(9, 0x07, 0x07);
                    break;
                case 1:
                    bit_Cal(8, 0xF0, 0xC0);bit_Cal(9, 0x07, 0x00);
                    break;
                case 2:
                    bit_Cal(8, 0xF0, 0x70);bit_Cal(9, 0x07, 0x03);
                    break;
                case 3:
                    bit_Cal(8, 0xF0, 0xF0);bit_Cal(9, 0x07, 0x01);
                    break;
                case 4:
                    bit_Cal(8, 0xF0, 0xD0);bit_Cal(9, 0x07, 0x04);
                    break;
                case 5:
                    bit_Cal(8, 0xF0, 0xB0);bit_Cal(9, 0x07, 0x05);
                    break;
                case 6:
                    bit_Cal(8, 0xF0, 0xB0);bit_Cal(9, 0x07, 0x07);
                    break;
                case 7:
                    bit_Cal(8, 0xF0, 0xE0);bit_Cal(9, 0x07, 0x00);
                    break;
                case 8:
                    bit_Cal(8, 0xF0, 0xF0);bit_Cal(9, 0x07, 0x07);
                    break;
                case 9:
                    bit_Cal(8, 0xF0, 0xF0);bit_Cal(9, 0x07, 0x05);
                    break;
                default:
                    bit_Cal(8, 0xF0, 0x10);bit_Cal(9, 0x07, 0x00);
                    break;
            }
        }
    }
    else
    {
        bit_Cal(2, 0xF0, 0x00);bit_Cal(3, 0x07, 0x00);//不显示
        bit_Cal(4, 0xF0, 0x00);bit_Cal(5, 0x07, 0x00);//不显示
        bit_Cal(6, 0xF0, 0x00);bit_Cal(7, 0x07, 0x00);//不显示
        bit_Cal(8, 0xF0, 0x00);bit_Cal(9, 0x07, 0x00);//不显示
    }
    
    LEDC0DATA0 = seg[0];			/*1*/
    LEDC0DATA1 = seg[1];			/*1*/
    LEDC1DATA0 = seg[2];			/*2*/
    LEDC1DATA1 = seg[3];			/*2*/
	LEDC2DATA0 = seg[4];			/*3*/
    LEDC2DATA1 = seg[5];			/*3*/
	LEDC3DATA0 = seg[6];			/*4*/
    LEDC3DATA1 = seg[7];			/*4*/
    LEDC4DATA0 = seg[8];            /*5*/
    LEDC4DATA1 = seg[9];			/*5*/
}

/*
*****************************************************************
 * 函数原型： void Show_Display(float dT)
 * 功    能： 显示屏幕内容
*****************************************************************
*/
void Show_Display(float dT)
{
	if(sys.Run_Status == 1)
    {
        if(sys.SetMode_Option == 2)
            Time.Display = Time.Set;//显示设定时间  
        else
            Time.Display = Time.Rel + 59;//显示控制时间
    }
	else			
		Time.Display = Time.Set;//显示设定时间  

    Display_Time(Time.Display);//显示时间
}
