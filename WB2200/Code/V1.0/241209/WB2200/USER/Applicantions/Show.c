#include "Show.h"

/**********全局变量声明******/
float Twinkle_Time;//闪烁时间

/**********局部变量声明******/
uint8_t Temp_ShowFlag,Time_ShowFlag;//温度、时间显示的标志位 0:常亮 1：熄灭
uint8_t cnt=0;
uint8_t seg[16] = {0};

/**
 * @brief 闪烁检测
 *
 * @param dT 任务周期
 */
static void Check_ShowFlag(float dT)
{
    static float T;
    if (!sys.SetMode_Option) // 如果没有在设置选项中，则都点亮，不闪烁
    {
        Temp_ShowFlag = 0;    // 常亮
        Time_ShowFlag = 0;    // 常亮
        Twinkle_Time = 0;     // 闪烁计时清零
        return;
    }
    if (Twinkle_Time && !Key_Status) // 闪烁和没有操作按键时
    {
        if (T == 0)
        {
            if (Twinkle_Time == 0)
            {
                sys.SetMode_Option = 0; // 模式选择清零
                Temp_ShowFlag = 0;      // 常亮
                Time_ShowFlag = 0;      // 常亮
            }
            else if (sys.SetMode_Option == 1)
            {
                Temp_ShowFlag = ~Temp_ShowFlag; // 温度闪烁
                Time_ShowFlag = 0;              // 常亮
            }
            else if (sys.SetMode_Option == 2)
            {
                Temp_ShowFlag = 0;              // 常亮
                Time_ShowFlag = ~Time_ShowFlag; // 时间闪烁
            }
        }
        T += dT;
        if (T >= 0.5f)
        {
            Twinkle_Time -= 0.5f;
            if (Twinkle_Time <= 0)
            {
                sys.SetMode_Option = 0;
            }
            T = 0;
        }
    }
    else
    {
        Temp_ShowFlag = 0;    // 常亮
        Time_ShowFlag = 0;    // 常亮
        T = 0;
    }
}

/**
 * @brief 闪烁函数
 *
 * @param dT 任务周期
 */
void Twinkle(float dT)
{
    Check_ShowFlag(dT);
}

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
 * 函数原型：void Display_Screen(int16_t dis_temp,int32_t dis_time)
 * 功    能：显示屏幕内容
 * 输    入: dis_temp：显示温度，dis_time：显示时间
 * 参    数：int16_t dis_temp,int32_t dis_time
*****************************************************************
*/
void Display_Screen(int16_t dis_temp,int32_t dis_time)
{   
    uint16_t Val;//用于百十个取出来的数字
    uint8_t SH,H,SM,M;//时间的单位取值
    if (!Temp_ShowFlag)
    {
        if(Temp.Set <= Temp_MIN)
        {
            Val = 11;//显示‘-’
        }
        else if(dis_temp > 999)//大于999时
        {
            Val=dis_temp/1000;//取出千位
            if(dis_temp > 9999)//大于9999时
                Val=Val%10;//取出千位
        }
        else if (dis_temp > -100) // 大于-100时
        {
            Val = 10;//不显示
        }
        else if (dis_temp > -1000) // 大于-1000时
        {
            Val = 11;//显示‘-’
        }
        switch(Val)
        {
            case 0:bit_Cal(0,0x01,0x01);
                    bit_Cal(1,0x01,0x01);
                    bit_Cal(3,0x01,0x01);
                    bit_Cal(4,0x01,0x00);
                    bit_Cal(5,0x01,0x01);
                    bit_Cal(6,0x01,0x01);
                    bit_Cal(7,0x01,0x01);//数字0
                break;
            case 1:bit_Cal(0,0x01,0x00);
                    bit_Cal(1,0x01,0x00);
                    bit_Cal(3,0x01,0x01);
                    bit_Cal(4,0x01,0x00);
                    bit_Cal(5,0x01,0x01);
                    bit_Cal(6,0x01,0x00);
                    bit_Cal(7,0x01,0x00);//数字1
                break;
            case 2:bit_Cal(0,0x01,0x01);
                    bit_Cal(1,0x01,0x01);
                    bit_Cal(3,0x01,0x00);
                    bit_Cal(4,0x01,0x01);
                    bit_Cal(5,0x01,0x01);
                    bit_Cal(6,0x01,0x00);
                    bit_Cal(7,0x01,0x01);//数字2
                break;
            case 3:bit_Cal(0,0x01,0x00);
                    bit_Cal(1,0x01,0x01);
                    bit_Cal(3,0x01,0x01);
                    bit_Cal(4,0x01,0x01);
                    bit_Cal(5,0x01,0x01);
                    bit_Cal(6,0x01,0x00);
                    bit_Cal(7,0x01,0x01);//数字3
                break;	
            case 4:bit_Cal(0,0x01,0x00);
                    bit_Cal(1,0x01,0x00);
                    bit_Cal(3,0x01,0x01);
                    bit_Cal(4,0x01,0x01);
                    bit_Cal(5,0x01,0x01);
                    bit_Cal(6,0x01,0x01);
                    bit_Cal(7,0x01,0x00);//数字4
                break;	
            case 5:bit_Cal(0,0x01,0x00);
                    bit_Cal(1,0x01,0x01);
                    bit_Cal(3,0x01,0x01);
                    bit_Cal(4,0x01,0x01);
                    bit_Cal(5,0x01,0x00);
                    bit_Cal(6,0x01,0x01);
                    bit_Cal(7,0x01,0x01);//数字5
                break;	
            case 6:bit_Cal(0,0x01,0x01);
                    bit_Cal(1,0x01,0x01);
                    bit_Cal(3,0x01,0x01);
                    bit_Cal(4,0x01,0x01);
                    bit_Cal(5,0x01,0x00);
                    bit_Cal(6,0x01,0x01);
                    bit_Cal(7,0x01,0x01);//数字6
                break;	
            case 7:bit_Cal(0,0x01,0x00);
                    bit_Cal(1,0x01,0x00);
                    bit_Cal(3,0x01,0x01);
                    bit_Cal(4,0x01,0x00);
                    bit_Cal(5,0x01,0x01);
                    bit_Cal(6,0x01,0x00);
                    bit_Cal(7,0x01,0x01);//数字7
                break;	
            case 8:bit_Cal(0,0x01,0x01);
                    bit_Cal(1,0x01,0x01);
                    bit_Cal(3,0x01,0x01);
                    bit_Cal(4,0x01,0x01);
                    bit_Cal(5,0x01,0x01);
                    bit_Cal(6,0x01,0x01);
                    bit_Cal(7,0x01,0x01);//数字8
                break;	
            case 9:bit_Cal(0,0x01,0x00);
                    bit_Cal(1,0x01,0x01);
                    bit_Cal(3,0x01,0x01);
                    bit_Cal(4,0x01,0x01);
                    bit_Cal(5,0x01,0x01);
                    bit_Cal(6,0x01,0x01);
                    bit_Cal(7,0x01,0x01);//数字9
                break;
            case 10:  
                bit_Cal(0,0x01,0x00);
                bit_Cal(1,0x01,0x00);
                bit_Cal(3,0x01,0x00);
                bit_Cal(4,0x01,0x00);
                bit_Cal(5,0x01,0x00);
                bit_Cal(6,0x01,0x00);
                bit_Cal(7,0x01,0x00);//不显示
                break;
            case 11:  
                bit_Cal(0,0x01,0x00);
                bit_Cal(1,0x01,0x00);
                bit_Cal(3,0x01,0x00);
                bit_Cal(4,0x01,0x01);
                bit_Cal(5,0x01,0x00);
                bit_Cal(6,0x01,0x00);
                bit_Cal(7,0x01,0x00);//显示‘-’
                break;
            default:
                break;
        }			
        
        if(Temp.Set <= Temp_MIN)
        {
            Val = 11;//显示‘-’
        }
        else if(dis_temp > 99)//大于99时
        {
            Val=dis_temp/ 100 % 10;//取出百位
        }
        else if (dis_temp >= 0) // 大于等于0时
        {
            Val = 10;//不显示
        }
        else if (dis_temp > -100) // 大于-100时
        {
            Val = 11;//显示‘-’
        }
        else if (dis_temp > -1000) // 大于-1000时
        {
            Val=ABS(dis_temp)/ 100 % 10;//取出百位
        }
        switch(Val)
        {
            case 0:bit_Cal(0,0x02,0x02);
                    bit_Cal(1,0x02,0x02);
                    bit_Cal(3,0x02,0x02);
                    bit_Cal(4,0x02,0x00);
                    bit_Cal(5,0x02,0x02);
                    bit_Cal(6,0x02,0x02);
                    bit_Cal(7,0x02,0x02);//数字0
                break;
            case 1:bit_Cal(0,0x02,0x00);
                    bit_Cal(1,0x02,0x00);
                    bit_Cal(3,0x02,0x02);
                    bit_Cal(4,0x02,0x00);
                    bit_Cal(5,0x02,0x02);
                    bit_Cal(6,0x02,0x00);
                    bit_Cal(7,0x02,0x00);//数字1
                break;
            case 2:bit_Cal(0,0x02,0x02);
                    bit_Cal(1,0x02,0x02);
                    bit_Cal(3,0x02,0x00);
                    bit_Cal(4,0x02,0x02);
                    bit_Cal(5,0x02,0x02);
                    bit_Cal(6,0x02,0x00);
                    bit_Cal(7,0x02,0x02);//数字2
                break;
            case 3:bit_Cal(0,0x02,0x00);
                    bit_Cal(1,0x02,0x02);
                    bit_Cal(3,0x02,0x02);
                    bit_Cal(4,0x02,0x02);
                    bit_Cal(5,0x02,0x02);
                    bit_Cal(6,0x02,0x00);
                    bit_Cal(7,0x02,0x02);//数字3
                break;	
            case 4:bit_Cal(0,0x02,0x00);
                    bit_Cal(1,0x02,0x00);
                    bit_Cal(3,0x02,0x02);
                    bit_Cal(4,0x02,0x02);
                    bit_Cal(5,0x02,0x02);
                    bit_Cal(6,0x02,0x02);
                    bit_Cal(7,0x02,0x00);//数字4
                break;	
            case 5:bit_Cal(0,0x02,0x00);
                    bit_Cal(1,0x02,0x02);
                    bit_Cal(3,0x02,0x02);
                    bit_Cal(4,0x02,0x02);
                    bit_Cal(5,0x02,0x00);
                    bit_Cal(6,0x02,0x02);
                    bit_Cal(7,0x02,0x02);//数字5
                break;	
            case 6:bit_Cal(0,0x02,0x02);
                    bit_Cal(1,0x02,0x02);
                    bit_Cal(3,0x02,0x02);
                    bit_Cal(4,0x02,0x02);
                    bit_Cal(5,0x02,0x00);
                    bit_Cal(6,0x02,0x02);
                    bit_Cal(7,0x02,0x02);//数字6
                break;	
            case 7:bit_Cal(0,0x02,0x00);
                    bit_Cal(1,0x02,0x00);
                    bit_Cal(3,0x02,0x02);
                    bit_Cal(4,0x02,0x00);
                    bit_Cal(5,0x02,0x02);
                    bit_Cal(6,0x02,0x00);
                    bit_Cal(7,0x02,0x02);//数字7
                break;	
            case 8:bit_Cal(0,0x02,0x02);
                    bit_Cal(1,0x02,0x02);
                    bit_Cal(3,0x02,0x02);
                    bit_Cal(4,0x02,0x02);
                    bit_Cal(5,0x02,0x02);
                    bit_Cal(6,0x02,0x02);
                    bit_Cal(7,0x02,0x02);//数字8
                break;	
            case 9:bit_Cal(0,0x02,0x00);
                    bit_Cal(1,0x02,0x02);
                    bit_Cal(3,0x02,0x02);
                    bit_Cal(4,0x02,0x02);
                    bit_Cal(5,0x02,0x02);
                    bit_Cal(6,0x02,0x02);
                    bit_Cal(7,0x02,0x02);//数字9
                break;
                
            case 10:bit_Cal(0,0x02,0x00);
                    bit_Cal(1,0x02,0x00);
                    bit_Cal(3,0x02,0x00);
                    bit_Cal(4,0x02,0x00);
                    bit_Cal(5,0x02,0x00);
                    bit_Cal(6,0x02,0x00);
                    bit_Cal(7,0x02,0x00);//不显示
                   break; 
            case 11:bit_Cal(0,0x02,0x00);
                    bit_Cal(1,0x02,0x00);
                    bit_Cal(3,0x02,0x00);
                    bit_Cal(4,0x02,0x02);
                    bit_Cal(5,0x02,0x00);
                    bit_Cal(6,0x02,0x00);
                    bit_Cal(7,0x02,0x00);//显示‘-’
                   break; 
            default:
                break;
        }


        Val=ABS(dis_temp) / 10 % 10;//取出十位
        if(Temp.Set <= Temp_MIN)
        {
            Val = 11;//显示‘-’
        }
        switch(Val)
        {
            case 0:bit_Cal(0,0x04,0x04);
                    bit_Cal(1,0x04,0x04);
                    bit_Cal(3,0x04,0x04);
                    bit_Cal(4,0x04,0x00);
                    bit_Cal(5,0x04,0x04);
                    bit_Cal(6,0x04,0x04);
                    bit_Cal(7,0x04,0x04);//数字0
                break;
            case 1:bit_Cal(0,0x04,0x00);
                    bit_Cal(1,0x04,0x00);
                    bit_Cal(3,0x04,0x04);
                    bit_Cal(4,0x04,0x00);
                    bit_Cal(5,0x04,0x04);
                    bit_Cal(6,0x04,0x00);
                    bit_Cal(7,0x04,0x00);//数字1
                break;
            case 2:bit_Cal(0,0x04,0x04);
                    bit_Cal(1,0x04,0x04);
                    bit_Cal(3,0x04,0x00);
                    bit_Cal(4,0x04,0x04);
                    bit_Cal(5,0x04,0x04);
                    bit_Cal(6,0x04,0x00);
                    bit_Cal(7,0x04,0x04);//数字2
                break;
            case 3:bit_Cal(0,0x04,0x00);
                    bit_Cal(1,0x04,0x04);
                    bit_Cal(3,0x04,0x04);
                    bit_Cal(4,0x04,0x04);
                    bit_Cal(5,0x04,0x04);
                    bit_Cal(6,0x04,0x00);
                    bit_Cal(7,0x04,0x04);//数字3
                break;	
            case 4:bit_Cal(0,0x04,0x00);
                    bit_Cal(1,0x04,0x00);
                    bit_Cal(3,0x04,0x04);
                    bit_Cal(4,0x04,0x04);
                    bit_Cal(5,0x04,0x04);
                    bit_Cal(6,0x04,0x04);
                    bit_Cal(7,0x04,0x00);//数字4
                break;	
            case 5:bit_Cal(0,0x04,0x00);
                    bit_Cal(1,0x04,0x04);
                    bit_Cal(3,0x04,0x04);
                    bit_Cal(4,0x04,0x04);
                    bit_Cal(5,0x04,0x00);
                    bit_Cal(6,0x04,0x04);
                    bit_Cal(7,0x04,0x04);//数字5
                break;	
            case 6:bit_Cal(0,0x04,0x04);
                    bit_Cal(1,0x04,0x04);
                    bit_Cal(3,0x04,0x04);
                    bit_Cal(4,0x04,0x04);
                    bit_Cal(5,0x04,0x00);
                    bit_Cal(6,0x04,0x04);
                    bit_Cal(7,0x04,0x04);//数字6
                break;	
            case 7:bit_Cal(0,0x04,0x00);
                    bit_Cal(1,0x04,0x00);
                    bit_Cal(3,0x04,0x04);
                    bit_Cal(4,0x04,0x00);
                    bit_Cal(5,0x04,0x04);
                    bit_Cal(6,0x04,0x00);
                    bit_Cal(7,0x04,0x04);//数字7
                break;	
            case 8:bit_Cal(0,0x04,0x04);
                    bit_Cal(1,0x04,0x04);
                    bit_Cal(3,0x04,0x04);
                    bit_Cal(4,0x04,0x04);
                    bit_Cal(5,0x04,0x04);
                    bit_Cal(6,0x04,0x04);
                    bit_Cal(7,0x04,0x04);//数字8
                break;	
            case 9:bit_Cal(0,0x04,0x00);
                    bit_Cal(1,0x04,0x04);
                    bit_Cal(3,0x04,0x04);
                    bit_Cal(4,0x04,0x04);
                    bit_Cal(5,0x04,0x04);
                    bit_Cal(6,0x04,0x04);
                    bit_Cal(7,0x04,0x04);//数字9
                break;
            case 10:bit_Cal(0,0x04,0x00);
                    bit_Cal(1,0x04,0x00);
                    bit_Cal(3,0x04,0x00);
                    bit_Cal(4,0x04,0x00);
                    bit_Cal(5,0x04,0x00);
                    bit_Cal(6,0x04,0x00);
                    bit_Cal(7,0x04,0x00);//不显示
                   break; 
            case 11:bit_Cal(0,0x04,0x00);
                    bit_Cal(1,0x04,0x00);
                    bit_Cal(3,0x04,0x00);
                    bit_Cal(4,0x04,0x04);
                    bit_Cal(5,0x04,0x00);
                    bit_Cal(6,0x04,0x00);
                    bit_Cal(7,0x04,0x00);//显示‘-’
                   break; 
            default:
                break;
        }			
        
        /***********dis_speed个位***********/
        Val=ABS(dis_temp) % 10;//取出个位
        if(Temp.Set <= Temp_MIN)
        {
            Val = 11;//显示‘-’
        }
        switch(Val)
        {
            case 0:bit_Cal(0,0x08,0x08);
                    bit_Cal(1,0x08,0x08);
                    bit_Cal(3,0x08,0x08);
                    bit_Cal(4,0x08,0x00);
                    bit_Cal(5,0x08,0x08);
                    bit_Cal(6,0x08,0x08);
                    bit_Cal(7,0x08,0x08);//数字0
                break;
            case 1:bit_Cal(0,0x08,0x00);
                    bit_Cal(1,0x08,0x00);
                    bit_Cal(3,0x08,0x08);
                    bit_Cal(4,0x08,0x00);
                    bit_Cal(5,0x08,0x08);
                    bit_Cal(6,0x08,0x00);
                    bit_Cal(7,0x08,0x00);//数字1
                break;
            case 2:bit_Cal(0,0x08,0x08);
                    bit_Cal(1,0x08,0x08);
                    bit_Cal(3,0x08,0x00);
                    bit_Cal(4,0x08,0x08);
                    bit_Cal(5,0x08,0x08);
                    bit_Cal(6,0x08,0x00);
                    bit_Cal(7,0x08,0x08);//数字2
                break;
            case 3:bit_Cal(0,0x08,0x00);
                    bit_Cal(1,0x08,0x08);
                    bit_Cal(3,0x08,0x08);
                    bit_Cal(4,0x08,0x08);
                    bit_Cal(5,0x08,0x08);
                    bit_Cal(6,0x08,0x00);
                    bit_Cal(7,0x08,0x08);//数字3
                break;	
            case 4:bit_Cal(0,0x08,0x00);
                    bit_Cal(1,0x08,0x00);
                    bit_Cal(3,0x08,0x08);
                    bit_Cal(4,0x08,0x08);
                    bit_Cal(5,0x08,0x08);
                    bit_Cal(6,0x08,0x08);
                    bit_Cal(7,0x08,0x00);//数字4
                break;	
            case 5:bit_Cal(0,0x08,0x00);
                    bit_Cal(1,0x08,0x08);
                    bit_Cal(3,0x08,0x08);
                    bit_Cal(4,0x08,0x08);
                    bit_Cal(5,0x08,0x00);
                    bit_Cal(6,0x08,0x08);
                    bit_Cal(7,0x08,0x08);//数字5
                break;	
            case 6:bit_Cal(0,0x08,0x08);
                    bit_Cal(1,0x08,0x08);
                    bit_Cal(3,0x08,0x08);
                    bit_Cal(4,0x08,0x08);
                    bit_Cal(5,0x08,0x00);
                    bit_Cal(6,0x08,0x08);
                    bit_Cal(7,0x08,0x08);//数字6
                break;	
            case 7:bit_Cal(0,0x08,0x00);
                    bit_Cal(1,0x08,0x00);
                    bit_Cal(3,0x08,0x08);
                    bit_Cal(4,0x08,0x00);
                    bit_Cal(5,0x08,0x08);
                    bit_Cal(6,0x08,0x00);
                    bit_Cal(7,0x08,0x08);//数字7
                break;	
            case 8:bit_Cal(0,0x08,0x08);
                    bit_Cal(1,0x08,0x08);
                    bit_Cal(3,0x08,0x08);
                    bit_Cal(4,0x08,0x08);
                    bit_Cal(5,0x08,0x08);
                    bit_Cal(6,0x08,0x08);
                    bit_Cal(7,0x08,0x08);//数字8
                break;	
            case 9:bit_Cal(0,0x08,0x00);
                    bit_Cal(1,0x08,0x08);
                    bit_Cal(3,0x08,0x08);
                    bit_Cal(4,0x08,0x08);
                    bit_Cal(5,0x08,0x08);
                    bit_Cal(6,0x08,0x08);
                    bit_Cal(7,0x08,0x08);//数字9
                break;
            case 10:bit_Cal(0,0x08,0x00);
                    bit_Cal(1,0x08,0x00);
                    bit_Cal(3,0x08,0x00);
                    bit_Cal(4,0x08,0x00);
                    bit_Cal(5,0x08,0x00);
                    bit_Cal(6,0x08,0x00);
                    bit_Cal(7,0x08,0x00);//不显示
                break;
            case 11:bit_Cal(0,0x08,0x00);
                    bit_Cal(1,0x08,0x00);
                    bit_Cal(3,0x08,0x00);
                    bit_Cal(4,0x08,0x08);
                    bit_Cal(5,0x08,0x00);
                    bit_Cal(6,0x08,0x00);
                    bit_Cal(7,0x08,0x00);//显示‘-’
                break;
            default:
                break;
        }	
    }
    else
    {
        bit_Cal(0,0x0f,0x00);
        bit_Cal(1,0x0f,0x00);
        bit_Cal(3,0x0f,0x00);
        bit_Cal(4,0x0f,0x00);
        bit_Cal(5,0x0f,0x00);
        bit_Cal(6,0x0f,0x00);
        bit_Cal(7,0x0f,0x00);//4位不显示
    }
    
    if(Temp.Set <= Temp_MIN)
    {
        bit_Cal(2,0x04,0x00);//不显示
    }
    else
    {
        bit_Cal(2,0x04,0x04);//温度小数点
    }
    SH=dis_time/3600/10;//计算十位单位的小时数
    H=dis_time/3600%10;//计算个位单位的小时数
    SM=dis_time%3600/60/10;//计算十分位单位的分钟数
    M=dis_time%3600/60%10;//计算个分位单位的分钟数
    if(Time.Set <= 0)
    {
        SH = 10;
        H = 10;
        SM = 10;
        M = 10;
    }
    if (!Time_ShowFlag)
    {
        switch(SH)
        {
            case 0:bit_Cal(8,0x10,0x10);
                    bit_Cal(9,0x10,0x10);
                    bit_Cal(11,0x10,0x10);
                    bit_Cal(12,0x10,0x00);
                    bit_Cal(13,0x10,0x10);
                    bit_Cal(14,0x10,0x10);
                    bit_Cal(15,0x10,0x10);//数字0
                break;
            case 1:bit_Cal(8,0x10,0x00);
                    bit_Cal(9,0x10,0x00);
                    bit_Cal(11,0x10,0x10);
                    bit_Cal(12,0x10,0x00);
                    bit_Cal(13,0x10,0x10);
                    bit_Cal(14,0x10,0x00);
                    bit_Cal(15,0x10,0x00);//数字1
                break;
            case 2:bit_Cal(8,0x10,0x10);
                    bit_Cal(9,0x10,0x10);
                    bit_Cal(11,0x10,0x00);
                    bit_Cal(12,0x10,0x10);
                    bit_Cal(13,0x10,0x10);
                    bit_Cal(14,0x10,0x00);
                    bit_Cal(15,0x10,0x10);//数字2
                break;
            case 3:bit_Cal(8,0x10,0x00);
                    bit_Cal(9,0x10,0x10);
                    bit_Cal(11,0x10,0x10);
                    bit_Cal(12,0x10,0x10);
                    bit_Cal(13,0x10,0x10);
                    bit_Cal(14,0x10,0x00);
                    bit_Cal(15,0x10,0x10);//数字3
                break;	
            case 4:bit_Cal(8,0x10,0x00);
                    bit_Cal(9,0x10,0x00);
                    bit_Cal(11,0x10,0x10);
                    bit_Cal(12,0x10,0x10);
                    bit_Cal(13,0x10,0x10);
                    bit_Cal(14,0x10,0x10);
                    bit_Cal(15,0x10,0x00);//数字4
                break;	
            case 5:bit_Cal(8,0x10,0x00);
                    bit_Cal(9,0x10,0x10);
                    bit_Cal(11,0x10,0x10);
                    bit_Cal(12,0x10,0x10);
                    bit_Cal(13,0x10,0x00);
                    bit_Cal(14,0x10,0x10);
                    bit_Cal(15,0x10,0x10);//数字5
                break;	
            case 6:bit_Cal(8,0x10,0x10);
                    bit_Cal(9,0x10,0x10);
                    bit_Cal(11,0x10,0x10);
                    bit_Cal(12,0x10,0x10);
                    bit_Cal(13,0x10,0x00);
                    bit_Cal(14,0x10,0x10);
                    bit_Cal(15,0x10,0x10);//数字6
                break;	
            case 7:bit_Cal(8,0x10,0x00);
                    bit_Cal(9,0x10,0x00);
                    bit_Cal(11,0x10,0x10);
                    bit_Cal(12,0x10,0x00);
                    bit_Cal(13,0x10,0x10);
                    bit_Cal(14,0x10,0x00);
                    bit_Cal(15,0x10,0x10);//数字7
                break;	
            case 8:bit_Cal(8,0x10,0x10);
                    bit_Cal(9,0x10,0x10);
                    bit_Cal(11,0x10,0x10);
                    bit_Cal(12,0x10,0x10);
                    bit_Cal(13,0x10,0x10);
                    bit_Cal(14,0x10,0x10);
                    bit_Cal(15,0x10,0x10);//数字8
                break;	
            case 9:bit_Cal(8,0x10,0x00);
                    bit_Cal(9,0x10,0x10);
                    bit_Cal(11,0x10,0x10);
                    bit_Cal(12,0x10,0x10);
                    bit_Cal(13,0x10,0x10);
                    bit_Cal(14,0x10,0x10);
                    bit_Cal(15,0x10,0x10);//数字9
                break;
            case 10:bit_Cal(8,0x10,0x00);
                    bit_Cal(9,0x10,0x00);
                    bit_Cal(11,0x10,0x00);
                    bit_Cal(12,0x10,0x10);
                    bit_Cal(13,0x10,0x00);
                    bit_Cal(14,0x10,0x00);
                    bit_Cal(15,0x10,0x00);//显示‘-’
                break;
            default:
                break;
        }			
    
    
        switch(H)
        {
            case 0:bit_Cal(8,0x20,0x20);
                    bit_Cal(9,0x20,0x20);
                    bit_Cal(11,0x20,0x20);
                    bit_Cal(12,0x20,0x00);
                    bit_Cal(13,0x20,0x20);
                    bit_Cal(14,0x20,0x20);
                    bit_Cal(15,0x20,0x20);//数字0
                break;
            case 1:bit_Cal(8,0x20,0x00);
                    bit_Cal(9,0x20,0x00);
                    bit_Cal(11,0x20,0x20);
                    bit_Cal(12,0x20,0x00);
                    bit_Cal(13,0x20,0x20);
                    bit_Cal(14,0x20,0x00);
                    bit_Cal(15,0x20,0x00);//数字1
                break;
            case 2:bit_Cal(8,0x20,0x20);
                    bit_Cal(9,0x20,0x20);
                    bit_Cal(11,0x20,0x00);
                    bit_Cal(12,0x20,0x20);
                    bit_Cal(13,0x20,0x20);
                    bit_Cal(14,0x20,0x00);
                    bit_Cal(15,0x20,0x20);//数字2
                break;
            case 3:bit_Cal(8,0x20,0x00);
                    bit_Cal(9,0x20,0x20);
                    bit_Cal(11,0x20,0x20);
                    bit_Cal(12,0x20,0x20);
                    bit_Cal(13,0x20,0x20);
                    bit_Cal(14,0x20,0x00);
                    bit_Cal(15,0x20,0x20);//数字3
                break;	
            case 4:bit_Cal(8,0x20,0x00);
                    bit_Cal(9,0x20,0x00);
                    bit_Cal(11,0x20,0x20);
                    bit_Cal(12,0x20,0x20);
                    bit_Cal(13,0x20,0x20);
                    bit_Cal(14,0x20,0x20);
                    bit_Cal(15,0x20,0x00);//数字4
                break;	
            case 5:bit_Cal(8,0x20,0x00);
                    bit_Cal(9,0x20,0x20);
                    bit_Cal(11,0x20,0x20);
                    bit_Cal(12,0x20,0x20);
                    bit_Cal(13,0x20,0x00);
                    bit_Cal(14,0x20,0x20);
                    bit_Cal(15,0x20,0x20);//数字5
                break;	
            case 6:bit_Cal(8,0x20,0x20);
                    bit_Cal(9,0x20,0x20);
                    bit_Cal(11,0x20,0x20);
                    bit_Cal(12,0x20,0x20);
                    bit_Cal(13,0x20,0x00);
                    bit_Cal(14,0x20,0x20);
                    bit_Cal(15,0x20,0x20);//数字6
                break;	
            case 7:bit_Cal(8,0x20,0x00);
                    bit_Cal(9,0x20,0x00);
                    bit_Cal(11,0x20,0x20);
                    bit_Cal(12,0x20,0x00);
                    bit_Cal(13,0x20,0x20);
                    bit_Cal(14,0x20,0x00);
                    bit_Cal(15,0x20,0x20);//数字7
                break;	
            case 8:bit_Cal(8,0x20,0x20);
                    bit_Cal(9,0x20,0x20);
                    bit_Cal(11,0x20,0x20);
                    bit_Cal(12,0x20,0x20);
                    bit_Cal(13,0x20,0x20);
                    bit_Cal(14,0x20,0x20);
                    bit_Cal(15,0x20,0x20);//数字8
                break;	
            case 9:bit_Cal(8,0x20,0x00);
                    bit_Cal(9,0x20,0x20);
                    bit_Cal(11,0x20,0x20);
                    bit_Cal(12,0x20,0x20);
                    bit_Cal(13,0x20,0x20);
                    bit_Cal(14,0x20,0x20);
                    bit_Cal(15,0x20,0x20);//数字9
                break;
            case 10:bit_Cal(8,0x20,0x00);
                    bit_Cal(9,0x20,0x00);
                    bit_Cal(11,0x20,0x00);
                    bit_Cal(12,0x20,0x20);
                    bit_Cal(13,0x20,0x00);
                    bit_Cal(14,0x20,0x00);
                    bit_Cal(15,0x20,0x00);//显示‘-’
                break;
            default:
                break;
        }			
    
        switch(SM)
        {
            case 0:bit_Cal(8,0x40,0x40);
                    bit_Cal(9,0x40,0x40);
                    bit_Cal(11,0x40,0x40);
                    bit_Cal(12,0x40,0x00);
                    bit_Cal(13,0x40,0x40);
                    bit_Cal(14,0x40,0x40);
                    bit_Cal(15,0x40,0x40);//数字0
                break;
            case 1:bit_Cal(8,0x40,0x00);
                    bit_Cal(9,0x40,0x00);
                    bit_Cal(11,0x40,0x40);
                    bit_Cal(12,0x40,0x00);
                    bit_Cal(13,0x40,0x40);
                    bit_Cal(14,0x40,0x00);
                    bit_Cal(15,0x40,0x00);//数字1
                break;
            case 2:bit_Cal(8,0x40,0x40);
                    bit_Cal(9,0x40,0x40);
                    bit_Cal(11,0x40,0x00);
                    bit_Cal(12,0x40,0x40);
                    bit_Cal(13,0x40,0x40);
                    bit_Cal(14,0x40,0x00);
                    bit_Cal(15,0x40,0x40);//数字2
                break;
            case 3:bit_Cal(8,0x40,0x00);
                    bit_Cal(9,0x40,0x40);
                    bit_Cal(11,0x40,0x40);
                    bit_Cal(12,0x40,0x40);
                    bit_Cal(13,0x40,0x40);
                    bit_Cal(14,0x40,0x00);
                    bit_Cal(15,0x40,0x40);//数字3
                break;	
            case 4:bit_Cal(8,0x40,0x00);
                    bit_Cal(9,0x40,0x00);
                    bit_Cal(11,0x40,0x40);
                    bit_Cal(12,0x40,0x40);
                    bit_Cal(13,0x40,0x40);
                    bit_Cal(14,0x40,0x40);
                    bit_Cal(15,0x40,0x00);//数字4
                break;	
            case 5:bit_Cal(8,0x40,0x00);
                    bit_Cal(9,0x40,0x40);
                    bit_Cal(11,0x40,0x40);
                    bit_Cal(12,0x40,0x40);
                    bit_Cal(13,0x40,0x00);
                    bit_Cal(14,0x40,0x40);
                    bit_Cal(15,0x40,0x40);//数字5
                break;	
            case 6:bit_Cal(8,0x40,0x40);
                    bit_Cal(9,0x40,0x40);
                    bit_Cal(11,0x40,0x40);
                    bit_Cal(12,0x40,0x40);
                    bit_Cal(13,0x40,0x00);
                    bit_Cal(14,0x40,0x40);
                    bit_Cal(15,0x40,0x40);//数字6
                break;	
            case 7:bit_Cal(8,0x40,0x00);
                    bit_Cal(9,0x40,0x00);
                    bit_Cal(11,0x40,0x40);
                    bit_Cal(12,0x40,0x00);
                    bit_Cal(13,0x40,0x40);
                    bit_Cal(14,0x40,0x00);
                    bit_Cal(15,0x40,0x40);//数字7
                break;	
            case 8:bit_Cal(8,0x40,0x40);
                    bit_Cal(9,0x40,0x40);
                    bit_Cal(11,0x40,0x40);
                    bit_Cal(12,0x40,0x40);
                    bit_Cal(13,0x40,0x40);
                    bit_Cal(14,0x40,0x40);
                    bit_Cal(15,0x40,0x40);//数字8
                break;	
            case 9:bit_Cal(8,0x40,0x00);
                    bit_Cal(9,0x40,0x40);
                    bit_Cal(11,0x40,0x40);
                    bit_Cal(12,0x40,0x40);
                    bit_Cal(13,0x40,0x40);
                    bit_Cal(14,0x40,0x40);
                    bit_Cal(15,0x40,0x40);//数字9
                break;
            case 10:bit_Cal(8,0x40,0x00);
                    bit_Cal(9,0x40,0x00);
                    bit_Cal(11,0x40,0x00);
                    bit_Cal(12,0x40,0x40);
                    bit_Cal(13,0x40,0x00);
                    bit_Cal(14,0x40,0x00);
                    bit_Cal(15,0x40,0x00);//显示‘-’
                break;
            default:
                break;
        }			
        switch(M)
        {
            case 0:bit_Cal(8,0x80,0x80);
                    bit_Cal(9,0x80,0x80);
                    bit_Cal(11,0x80,0x80);
                    bit_Cal(12,0x80,0x00);
                    bit_Cal(13,0x80,0x80);
                    bit_Cal(14,0x80,0x80);
                    bit_Cal(15,0x80,0x80);//数字0
                break;
            case 1:bit_Cal(8,0x80,0x00);
                    bit_Cal(9,0x80,0x00);
                    bit_Cal(11,0x80,0x80);
                    bit_Cal(12,0x80,0x00);
                    bit_Cal(13,0x80,0x80);
                    bit_Cal(14,0x80,0x00);
                    bit_Cal(15,0x80,0x00);//数字1
                break;
            case 2:bit_Cal(8,0x80,0x80);
                    bit_Cal(9,0x80,0x80);
                    bit_Cal(11,0x80,0x00);
                    bit_Cal(12,0x80,0x80);
                    bit_Cal(13,0x80,0x80);
                    bit_Cal(14,0x80,0x00);
                    bit_Cal(15,0x80,0x80);//数字2
                break;
            case 3:bit_Cal(8,0x80,0x00);
                    bit_Cal(9,0x80,0x80);
                    bit_Cal(11,0x80,0x80);
                    bit_Cal(12,0x80,0x80);
                    bit_Cal(13,0x80,0x80);
                    bit_Cal(14,0x80,0x00);
                    bit_Cal(15,0x80,0x80);//数字3
                break;	
            case 4:bit_Cal(8,0x80,0x00);
                    bit_Cal(9,0x80,0x00);
                    bit_Cal(11,0x80,0x80);
                    bit_Cal(12,0x80,0x80);
                    bit_Cal(13,0x80,0x80);
                    bit_Cal(14,0x80,0x80);
                    bit_Cal(15,0x80,0x00);//数字4
                break;	
            case 5:bit_Cal(8,0x80,0x00);
                    bit_Cal(9,0x80,0x80);
                    bit_Cal(11,0x80,0x80);
                    bit_Cal(12,0x80,0x80);
                    bit_Cal(13,0x80,0x00);
                    bit_Cal(14,0x80,0x80);
                    bit_Cal(15,0x80,0x80);//数字5
                break;	
            case 6:bit_Cal(8,0x80,0x80);
                    bit_Cal(9,0x80,0x80);
                    bit_Cal(11,0x80,0x80);
                    bit_Cal(12,0x80,0x80);
                    bit_Cal(13,0x80,0x00);
                    bit_Cal(14,0x80,0x80);
                    bit_Cal(15,0x80,0x80);//数字6
                break;	
            case 7:bit_Cal(8,0x80,0x00);
                    bit_Cal(9,0x80,0x00);
                    bit_Cal(11,0x80,0x80);
                    bit_Cal(12,0x80,0x00);
                    bit_Cal(13,0x80,0x80);
                    bit_Cal(14,0x80,0x00);
                    bit_Cal(15,0x80,0x80);//数字7
                break;	
            case 8:bit_Cal(8,0x80,0x80);
                    bit_Cal(9,0x80,0x80);
                    bit_Cal(11,0x80,0x80);
                    bit_Cal(12,0x80,0x80);
                    bit_Cal(13,0x80,0x80);
                    bit_Cal(14,0x80,0x80);
                    bit_Cal(15,0x80,0x80);//数字8
                break;	
            case 9:bit_Cal(8,0x80,0x00);
                    bit_Cal(9,0x80,0x80);
                    bit_Cal(11,0x80,0x80);
                    bit_Cal(12,0x80,0x80);
                    bit_Cal(13,0x80,0x80);
                    bit_Cal(14,0x80,0x80);
                    bit_Cal(15,0x80,0x80);//数字9
                break;
            case 10:bit_Cal(8,0x80,0x00);
                    bit_Cal(9,0x80,0x00);
                    bit_Cal(11,0x80,0x00);
                    bit_Cal(12,0x80,0x80);
                    bit_Cal(13,0x80,0x00);
                    bit_Cal(14,0x80,0x00);
                    bit_Cal(15,0x80,0x00);//显示‘-’
                break;
            default:
                break;
        }
    }
    else
    {
        bit_Cal(8,0xf0,0x00);
        bit_Cal(9,0xf0,0x00);
        bit_Cal(11,0xf0,0x00);
        bit_Cal(12,0xf0,0x00);
        bit_Cal(13,0xf0,0x00);
        bit_Cal(14,0xf0,0x00);
        bit_Cal(15,0xf0,0x00);//不显示
    }
	TM1640_Write_DATA(cnt, seg[cnt]);
	cnt ++;
	if(cnt >= 16)
		cnt= 0;
}

/*
*****************************************************************
 * 函数原型：void Show_Display(void)
 * 功    能：显示屏幕内容
*****************************************************************
*/
void Show_Display(void)
{	
    if(sys.Run_Status)
    {
        
    }
    else
    {
        Temp.Display = Temp.Rel;
        Time.Display = Time.Set;
    }
    Display_Screen(Temp.Display,Time.Display);
}
