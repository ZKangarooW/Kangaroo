#include "Show.h"

/**********全局变量**********/
float Twinkle_Time; // 闪烁时间

/**********局部变量声明*******/
uint8_t Speed_ShowFlag, Time_ShowFlag, Sync_ShowFlag;//速度、温度、时间显示的标志位，0：常亮，1：熄灭

static void Check_Sync(float dT)
{
    static float T;
    T += dT;
    if(T >= 0.5f)
    {
        if(sys.Sync)//进入全家设置
            Sync_ShowFlag = ~Sync_ShowFlag;//选中工位下闪烁
        T = 0;
    } 
}

static void Check_ShowFlag(float dT)
{
    static float T;
    
    if(sys.SetMode_Option == 0 && Twinkle_Time==0)//如果没在设置选项中，则都点亮，不闪烁
    {
        Speed_ShowFlag = 0;//常亮
        Time_ShowFlag = 0;//常亮
        T = 0;
        return;
    }
    if(Twinkle_Time && EC11A[1].EC11A_Knob<=0)//闪烁和没有操作旋钮时
    {
        if(T == 0)
        {
            Twinkle_Time -= 0.5f;//闪烁计时
            if(sys.SetMode_Option == 0)//设置速度
            {
                Speed_ShowFlag = ~Speed_ShowFlag;//速度闪烁
                Time_ShowFlag = 0;//时间常亮
            }
            else if(sys.SetMode_Option == 1)//设置速度
            {
                Speed_ShowFlag = ~Speed_ShowFlag;//速度闪烁
                Time_ShowFlag = 0;//时间常亮
            }
            if(sys.SetMode_Option == 2)//设置时间
            {
                Speed_ShowFlag = 0;//速度常亮
                Time_ShowFlag = ~Time_ShowFlag;//时间闪烁
            }
            if(Twinkle_Time == 0)//如果闪烁结束
            {
                sys.SetMode_Option = 0;//模式选择清零
            }
        }
        T += dT;
        if(T >= 0.5f)
        {
            T = 0;
        }            
    }
    else
        T = 0;
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
	static float T[15];
    for(uint8_t i = 0;i<15;i++)
    {
        if(Work_Num[i].Run_Status)		
        {
            T[i] += dT;
            if(T[i] >= 0.5f)
            {
                if(Work_Num[i].Speed.Set)
                {
                    Work_Num[i].Speed.IconStep ++;//速度图标闪烁;
                    if(Work_Num[i].Speed.IconStep > 3)
                        Work_Num[i].Speed.IconStep = 1;
                }
                else
                   Work_Num[i].Speed.IconStep = 0;
                
                
                if(Work_Num[i].Time.Rel)
                    Work_Num[i].Time.Icon = ~Work_Num[i].Time.Icon;//定时图标闪烁;
                else
                {
                    Work_Num[i].Time.Icon = 0;
                }
                T[i] = 0;
            }
		}
        else
        {
            Work_Num[i].Speed.IconStep = 0;//显示时间图标
            Work_Num[i].Time.Icon = 0;//显示时间图标
            T[i] = 0;
        }
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
    Icn_Twinkle(dT);
    Check_Sync(dT);
}

uint8_t seg[46] = {0};
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

void Display(_Work_Num_ work_num[])
{
    uint8_t Val;// 用于百十个取出来的数字
    
    /***********工位1**********/
    if (work_num[0].Speed.Display_Set > 999) // 大于999时
    {
        Val = work_num[0].Speed.Display_Set / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(0, 0x0C, 0x04);//显示数字1
        }
        else
        {
            bit_Cal(0, 0x0C, 0x0C);//显示数字0
        }
    }
    else
    {
         bit_Cal(0, 0x0C, 0x0C);//显示数字0
    }
    
    if (work_num[0].Speed.Display_Set > 99) // 大于99时
    {
        Val = work_num[0].Speed.Display_Set / 100 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(1, 0x0F, 0x0F);bit_Cal(2, 0x07, 0x05);//显示数字0
            break;
        case 1:
            bit_Cal(1, 0x0F, 0x00);bit_Cal(2, 0x07, 0x05);
            break;
        case 2:
            bit_Cal(1, 0x0F, 0x0D);bit_Cal(2, 0x07, 0x03);
            break;
        case 3:
            bit_Cal(1, 0x0F, 0x09);bit_Cal(2, 0x07, 0x07);
            break;
        case 4:
            bit_Cal(1, 0x0F, 0x02);bit_Cal(2, 0x07, 0x07);
            break;
        case 5:
            bit_Cal(1, 0x0F, 0x0B);bit_Cal(2, 0x07, 0x06);
            break;
        case 6:
            bit_Cal(1, 0x0F, 0x0F);bit_Cal(2, 0x07, 0x06);
            break;
        case 7:
            bit_Cal(1, 0x0F, 0x01);bit_Cal(2, 0x07, 0x05);
            break;
        case 8:
            bit_Cal(1, 0x0F, 0x0F);bit_Cal(2, 0x07, 0x07);
            break;
        case 9:
            bit_Cal(1, 0x0F, 0x0B);bit_Cal(2, 0x07, 0x07);
            break;
        default:
            break;
        }
    }
    else
    {
         bit_Cal(1, 0x0F, 0x0F);bit_Cal(2, 0x07, 0x05);//显示数字0
    }

    if (work_num[0].Speed.Display_Set > 9) // 大于9时
    {
        Val = work_num[0].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(3, 0x0F, 0x0F);bit_Cal(4, 0x07, 0x05);//显示数字0
            break;
        case 1:
            bit_Cal(3, 0x0F, 0x00);bit_Cal(4, 0x07, 0x05);
            break;
        case 2:
            bit_Cal(3, 0x0F, 0x0D);bit_Cal(4, 0x07, 0x03);
            break;
        case 3:
            bit_Cal(3, 0x0F, 0x09);bit_Cal(4, 0x07, 0x07);
            break;
        case 4:
            bit_Cal(3, 0x0F, 0x02);bit_Cal(4, 0x07, 0x07);
            break;
        case 5:
            bit_Cal(3, 0x0F, 0x0B);bit_Cal(4, 0x07, 0x06);
            break;
        case 6:
            bit_Cal(3, 0x0F, 0x0F);bit_Cal(4, 0x07, 0x06);
            break;
        case 7:
            bit_Cal(3, 0x0F, 0x01);bit_Cal(4, 0x07, 0x05);
            break;
        case 8:
            bit_Cal(3, 0x0F, 0x0F);bit_Cal(4, 0x07, 0x07);
            break;
        case 9:
            bit_Cal(3, 0x0F, 0x0B);bit_Cal(4, 0x07, 0x07);
            break;
        default:
            break;
        }
    }
    else
    {
         bit_Cal(3, 0x0F, 0x0F);bit_Cal(4, 0x07, 0x05);//显示数字0
    }

    //实际转速个位只能显示零
    bit_Cal(4, 0x08, 0x08);//显示数字0

    /***********工位2**********/
    if (work_num[1].Speed.Display_Set > 999) // 大于999时
    {
        Val = work_num[1].Speed.Display_Set / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(5, 0x0C, 0x04);//显示数字1
        }
        else
        {
            bit_Cal(5, 0x0C, 0x0C);//显示数字0
        }
    }
    else
    {
         bit_Cal(5, 0x0C, 0x0C);//显示数字0
    }
    
    if (work_num[1].Speed.Display_Set > 99) // 大于99时
    {
        Val = work_num[1].Speed.Display_Set / 100 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(6, 0x0F, 0x0F);bit_Cal(7, 0x07, 0x05);//显示数字0
            break;
        case 1:
            bit_Cal(6, 0x0F, 0x00);bit_Cal(7, 0x07, 0x05);
            break;
        case 2:
            bit_Cal(6, 0x0F, 0x0D);bit_Cal(7, 0x07, 0x03);
            break;
        case 3:
            bit_Cal(6, 0x0F, 0x09);bit_Cal(7, 0x07, 0x07);
            break;
        case 4:
            bit_Cal(6, 0x0F, 0x02);bit_Cal(7, 0x07, 0x07);
            break;
        case 5:
            bit_Cal(6, 0x0F, 0x0B);bit_Cal(7, 0x07, 0x06);
            break;
        case 6:
            bit_Cal(6, 0x0F, 0x0F);bit_Cal(7, 0x07, 0x06);
            break;
        case 7:
            bit_Cal(6, 0x0F, 0x01);bit_Cal(7, 0x07, 0x05);
            break;
        case 8:
            bit_Cal(6, 0x0F, 0x0F);bit_Cal(7, 0x07, 0x07);
            break;
        case 9:
            bit_Cal(6, 0x0F, 0x0B);bit_Cal(7, 0x07, 0x07);
            break;
        default:
            break;
        }
    }
    else
    {
         bit_Cal(6, 0x0F, 0x0F);bit_Cal(7, 0x07, 0x05);//显示数字0
    }

    if (work_num[1].Speed.Display_Set > 9) // 大于9时
    {
        Val = work_num[1].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(8, 0x0F, 0x0F);bit_Cal(9, 0x07, 0x05);//显示数字0
            break;
        case 1:
            bit_Cal(8, 0x0F, 0x00);bit_Cal(9, 0x07, 0x05);
            break;
        case 2:
            bit_Cal(8, 0x0F, 0x0D);bit_Cal(9, 0x07, 0x03);
            break;
        case 3:
            bit_Cal(8, 0x0F, 0x09);bit_Cal(9, 0x07, 0x07);
            break;
        case 4:
            bit_Cal(8, 0x0F, 0x02);bit_Cal(9, 0x07, 0x07);
            break;
        case 5:
            bit_Cal(8, 0x0F, 0x0B);bit_Cal(9, 0x07, 0x06);
            break;
        case 6:
            bit_Cal(8, 0x0F, 0x0F);bit_Cal(9, 0x07, 0x06);
            break;
        case 7:
            bit_Cal(8, 0x0F, 0x01);bit_Cal(9, 0x07, 0x05);
            break;
        case 8:
            bit_Cal(8, 0x0F, 0x0F);bit_Cal(9, 0x07, 0x07);
            break;
        case 9:
            bit_Cal(8, 0x0F, 0x0B);bit_Cal(9, 0x07, 0x07);
            break;
        default:
            break;
        }
    }
    else
    {
         bit_Cal(8, 0x0F, 0x0F);bit_Cal(9, 0x07, 0x05);//显示数字0
    }
    //实际转速个位只能显示零
    bit_Cal(9, 0x08, 0x08);//显示数字0

    /***********工位3**********/
    if (work_num[2].Speed.Display_Set > 999) // 大于999时
    {
        Val = work_num[2].Speed.Display_Set / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(10, 0x0C, 0x04);//显示数字1
        }
        else
        {
            bit_Cal(10, 0x0C, 0x0C);//显示数字0
        }
    }
    else
    {
         bit_Cal(10, 0x0C, 0x0C);//显示数字0
    }
    
    if (work_num[2].Speed.Display_Set > 99) // 大于99时
    {
        Val = work_num[2].Speed.Display_Set / 100 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(11, 0x0F, 0x0F);bit_Cal(12, 0x07, 0x05);//显示数字0
            break;
        case 1:
            bit_Cal(11, 0x0F, 0x00);bit_Cal(12, 0x07, 0x05);
            break;
        case 2:
            bit_Cal(11, 0x0F, 0x0D);bit_Cal(12, 0x07, 0x03);
            break;
        case 3:
            bit_Cal(11, 0x0F, 0x09);bit_Cal(12, 0x07, 0x07);
            break;
        case 4:
            bit_Cal(11, 0x0F, 0x02);bit_Cal(12, 0x07, 0x07);
            break;
        case 5:
            bit_Cal(11, 0x0F, 0x0B);bit_Cal(12, 0x07, 0x06);
            break;
        case 6:
            bit_Cal(11, 0x0F, 0x0F);bit_Cal(12, 0x07, 0x06);
            break;
        case 7:
            bit_Cal(11, 0x0F, 0x01);bit_Cal(12, 0x07, 0x05);
            break;
        case 8:
            bit_Cal(11, 0x0F, 0x0F);bit_Cal(12, 0x07, 0x07);
            break;
        case 9:
            bit_Cal(11, 0x0F, 0x0B);bit_Cal(12, 0x07, 0x07);
            break;
        default:
            break;
        }
    }
    else
    {
         bit_Cal(11, 0x0F, 0x0F);bit_Cal(12, 0x07, 0x05);//显示数字0
    }

    if (work_num[2].Speed.Display_Set > 9) // 大于9时
    {
        Val = work_num[2].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(13, 0x0F, 0x0F);bit_Cal(14, 0x07, 0x05);//显示数字0
            break;
        case 1:
            bit_Cal(13, 0x0F, 0x00);bit_Cal(14, 0x07, 0x05);
            break;
        case 2:
            bit_Cal(13, 0x0F, 0x0D);bit_Cal(14, 0x07, 0x03);
            break;
        case 3:
            bit_Cal(13, 0x0F, 0x09);bit_Cal(14, 0x07, 0x07);
            break;
        case 4:
            bit_Cal(13, 0x0F, 0x02);bit_Cal(14, 0x07, 0x07);
            break;
        case 5:
            bit_Cal(13, 0x0F, 0x0B);bit_Cal(14, 0x07, 0x06);
            break;
        case 6:
            bit_Cal(13, 0x0F, 0x0F);bit_Cal(14, 0x07, 0x06);
            break;
        case 7:
            bit_Cal(13, 0x0F, 0x01);bit_Cal(14, 0x07, 0x05);
            break;
        case 8:
            bit_Cal(13, 0x0F, 0x0F);bit_Cal(14, 0x07, 0x07);
            break;
        case 9:
            bit_Cal(13, 0x0F, 0x0B);bit_Cal(14, 0x07, 0x07);
            break;
        default:
            break;
        }
    }
    else
    {
         bit_Cal(13, 0x0F, 0x0F);bit_Cal(14, 0x07, 0x05);//显示数字0
    }
    //实际转速个位只能显示零
    bit_Cal(14, 0x08, 0x08);//显示数字0

    /***********工位4**********/
    if (work_num[3].Speed.Display_Set > 999)//大于999时
    {
        Val = work_num[3].Speed.Display_Set / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(0, 0x30, 0x20);//显示数字1
        }
        else
        {
            bit_Cal(0, 0x30, 0x30);//显示数字0
        }
    }
    else
    {
        bit_Cal(0, 0x30, 0x30);//显示数字0
    }

    if (work_num[3].Speed.Display_Set > 99)//大于99时
    {
        Val = work_num[3].Speed.Display_Set / 100 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(1, 0xF0, 0xF0);bit_Cal(2, 0x70, 0x50);//显示数字0
            break;
        case 1:
            bit_Cal(1, 0xF0, 0x00);bit_Cal(2, 0x70, 0x50);
            break;
        case 2:
            bit_Cal(1, 0xF0, 0xD0);bit_Cal(2, 0x70, 0x30);
            break;
        case 3:
            bit_Cal(1, 0xF0, 0x90);bit_Cal(2, 0x70, 0x70);
            break;
        case 4:
            bit_Cal(1, 0xF0, 0x20);bit_Cal(2, 0x70, 0x70);
            break;
        case 5:
            bit_Cal(1, 0xF0, 0xB0);bit_Cal(2, 0x70, 0x60);
            break;
        case 6:
            bit_Cal(1, 0xF0, 0xF0);bit_Cal(2, 0x70, 0x60);
            break;
        case 7:
            bit_Cal(1, 0xF0, 0x10);bit_Cal(2, 0x70, 0x50);
            break;
        case 8:
            bit_Cal(1, 0xF0, 0xF0);bit_Cal(2, 0x70, 0x70);
            break;
        case 9:
            bit_Cal(1, 0xF0, 0xB0);bit_Cal(2, 0x70, 0x70);
            break;
        default:
            break;
        }
    }
    else
    {
         bit_Cal(1, 0xF0, 0xF0);bit_Cal(2, 0x70, 0x50);//显示数字0
    }

    if (work_num[3].Speed.Display_Set > 9) // 大于9时
    {
        Val = work_num[3].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(3, 0xF0, 0xF0);bit_Cal(4, 0x70, 0x50);//显示数字0
            break;
        case 1:
            bit_Cal(3, 0xF0, 0x00);bit_Cal(4, 0x70, 0x50);
            break;
        case 2:
            bit_Cal(3, 0xF0, 0xD0);bit_Cal(4, 0x70, 0x30);
            break;
        case 3:
            bit_Cal(3, 0xF0, 0x90);bit_Cal(4, 0x70, 0x70);
            break;
        case 4:
            bit_Cal(3, 0xF0, 0x20);bit_Cal(4, 0x70, 0x70);
            break;
        case 5:
            bit_Cal(3, 0xF0, 0xB0);bit_Cal(4, 0x70, 0x60);
            break;
        case 6:
            bit_Cal(3, 0xF0, 0xF0);bit_Cal(4, 0x70, 0x60);
            break;
        case 7:
            bit_Cal(3, 0xF0, 0x10);bit_Cal(4, 0x70, 0x50);
            break;
        case 8:
            bit_Cal(3, 0xF0, 0xF0);bit_Cal(4, 0x70, 0x70);
            break;
        case 9:
            bit_Cal(3, 0xF0, 0xB0);bit_Cal(4, 0x70, 0x70);
            break;
        default:
            break;
        }
    }
    else
    {
         bit_Cal(3, 0xF0, 0xF0);bit_Cal(4, 0x70, 0x50);//显示数字0
    }

    //实际转速个位只能显示零
    bit_Cal(5, 0x40, 0x40);//显示数字0

    /***********工位5**********/
    if (work_num[4].Speed.Display_Set > 999)//大于999时
    {
        Val = work_num[4].Speed.Display_Set / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(5, 0x30, 0x10);//显示数字1
        }
        else
        {
            bit_Cal(5, 0x30, 0x30);//显示数字0
        }
    }
    else
    {
        bit_Cal(5, 0x30, 0x30);//显示数字0
    }

    if (work_num[4].Speed.Display_Set > 99)//大于99时
    {
        Val = work_num[4].Speed.Display_Set / 100 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(6, 0xF0, 0xF0);bit_Cal(7, 0x70, 0x50);//显示数字0
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
            break;
        }
    }
    else
    {
         bit_Cal(6, 0xF0, 0xF0);bit_Cal(7, 0x70, 0x50);//显示数字0
    }

    if (work_num[4].Speed.Display_Set > 9) // 大于9时
    {
        Val = work_num[4].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(8, 0xF0, 0xF0);bit_Cal(9, 0x70, 0x50);//显示数字0
            break;
        case 1:
            bit_Cal(8, 0xF0, 0x00);bit_Cal(9, 0x70, 0x50);
            break;
        case 2:
            bit_Cal(8, 0xF0, 0xD0);bit_Cal(9, 0x70, 0x30);
            break;
        case 3:
            bit_Cal(8, 0xF0, 0x90);bit_Cal(9, 0x70, 0x70);
            break;
        case 4:
            bit_Cal(8, 0xF0, 0x20);bit_Cal(9, 0x70, 0x70);
            break;
        case 5:
            bit_Cal(8, 0xF0, 0xB0);bit_Cal(9, 0x70, 0x60);
            break;
        case 6:
            bit_Cal(8, 0xF0, 0xF0);bit_Cal(9, 0x70, 0x60);
            break;
        case 7:
            bit_Cal(8, 0xF0, 0x10);bit_Cal(9, 0x70, 0x50);
            break;
        case 8:
            bit_Cal(8, 0xF0, 0xF0);bit_Cal(9, 0x70, 0x70);
            break;
        case 9:
            bit_Cal(8, 0xF0, 0xB0);bit_Cal(9, 0x70, 0x70);
            break;
        default:
            break;
        }
    }
    else
    {
         bit_Cal(8, 0xF0, 0xF0);bit_Cal(9, 0x70, 0x50);//显示数字0
    }

    //实际转速个位只能显示零
    bit_Cal(9, 0x80, 0x80);//显示数字0

    /***********工位6**********/
    if (work_num[5].Speed.Display_Set > 999)//大于999时
    {
        Val = work_num[5].Speed.Display_Set / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(10, 0x30, 0x10);//显示数字1
        }
        else
        {
            bit_Cal(10, 0x30, 0x30);//显示数字0
        }
    }
    else
    {
        bit_Cal(10, 0x30, 0x30);//显示数字0
    }

    if (work_num[5].Speed.Display_Set > 99)//大于99时
    {
        Val = work_num[5].Speed.Display_Set / 100 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(11, 0xF0, 0xF0);bit_Cal(12, 0x70, 0x50);//显示数字0
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
            break;
        }
    }
    else
    {
         bit_Cal(11, 0xF0, 0xF0);bit_Cal(12, 0x70, 0x50);//显示数字0
    }

    if (work_num[5].Speed.Display_Set > 9) // 大于9时
    {
        Val = work_num[5].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(13, 0xF0, 0xF0);bit_Cal(14, 0x70, 0x50);//显示数字0
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
            break;
        }
    }
    else
    {
         bit_Cal(13, 0xF0, 0xF0);bit_Cal(14, 0x70, 0x50);//显示数字0
    }

    //转速个位只能显示零
    bit_Cal(15, 0x40, 0x40);//显示数字0

    /***********工位7**********/
    if (work_num[6].Speed.Display_Set > 999)//大于999时
    {
        Val = work_num[6].Speed.Display_Set / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(45, 0xC0, 0x80);//显示数字1
        }
        else
        {
            bit_Cal(45, 0xC0, 0xC0);//显示数字0
        }
    }
    else
    {
         bit_Cal(45, 0xC0, 0xC0);//显示数字0
    }

    if (work_num[6].Speed.Display_Set > 99)//大于99时
    {
        Val = work_num[6].Speed.Display_Set / 100 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(0, 0x83, 0x81);bit_Cal(2, 0x80, 0x80);bit_Cal(26, 0x01, 0x01);bit_Cal(30, 0x80, 0x80);bit_Cal(36, 0x01, 0x01);
            break;
        case 1:
            bit_Cal(0, 0x83, 0x01);bit_Cal(2, 0x80, 0x80);bit_Cal(26, 0x01, 0x00);bit_Cal(30, 0x80, 0x00);bit_Cal(36, 0x01, 0x00);
            break;
        case 2:
            bit_Cal(0, 0x83, 0x82);bit_Cal(2, 0x80, 0x80);bit_Cal(26, 0x01, 0x01);bit_Cal(30, 0x80, 0x80);bit_Cal(36, 0x01, 0x00);
            break;
        case 3:
            bit_Cal(0, 0x83, 0x83);bit_Cal(2, 0x80, 0x80);bit_Cal(26, 0x01, 0x01);bit_Cal(30, 0x80, 0x00);bit_Cal(36, 0x01, 0x00);
            break;
        case 4:
            bit_Cal(0, 0x83, 0x03);bit_Cal(2, 0x80, 0x80);bit_Cal(26, 0x01, 0x00);bit_Cal(30, 0x80, 0x00);bit_Cal(36, 0x01, 0x01);
            break;
        case 5:
            bit_Cal(0, 0x83, 0x83);bit_Cal(2, 0x80, 0x00);bit_Cal(26, 0x01, 0x01);bit_Cal(30, 0x80, 0x00);bit_Cal(36, 0x01, 0x01);
            break;
        case 6:
            bit_Cal(0, 0x83, 0x83);bit_Cal(2, 0x80, 0x00);bit_Cal(26, 0x01, 0x01);bit_Cal(30, 0x80, 0x80);bit_Cal(36, 0x01, 0x01);
            break;
        case 7:
            bit_Cal(0, 0x83, 0x81);bit_Cal(2, 0x80, 0x80);bit_Cal(26, 0x01, 0x00);bit_Cal(30, 0x80, 0x00);bit_Cal(36, 0x01, 0x00);
            break;
        case 8:
            bit_Cal(0, 0x83, 0x83);bit_Cal(2, 0x80, 0x80);bit_Cal(26, 0x01, 0x01);bit_Cal(30, 0x80, 0x80);bit_Cal(36, 0x01, 0x01);
            break;
        case 9:
            bit_Cal(0, 0x83, 0x83);bit_Cal(2, 0x80, 0x80);bit_Cal(26, 0x01, 0x01);bit_Cal(30, 0x80, 0x00);bit_Cal(36, 0x01, 0x01);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(0, 0x83, 0x81);bit_Cal(2, 0x80, 0x80);bit_Cal(26, 0x01, 0x01);bit_Cal(30, 0x80, 0x80);bit_Cal(36, 0x01, 0x01);//显示数字0
    }

     if (work_num[6].Speed.Display_Set > 9) // 大于9时
    {
        Val = work_num[6].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(4, 0x80, 0x80);bit_Cal(5, 0x83, 0x81);bit_Cal(10, 0x83, 0x83);
            break;
        case 1:
            bit_Cal(4, 0x80, 0x00);bit_Cal(5, 0x83, 0x00);bit_Cal(10, 0x83, 0x82);
            break;
        case 2:
            bit_Cal(4, 0x80, 0x00);bit_Cal(5, 0x83, 0x83);bit_Cal(10, 0x83, 0x81);
            break;
        case 3:
            bit_Cal(4, 0x80, 0x00);bit_Cal(5, 0x83, 0x82);bit_Cal(10, 0x83, 0x83);
            break;
        case 4:
           bit_Cal(4, 0x80, 0x80);bit_Cal(5, 0x83, 0x02);bit_Cal(10, 0x83, 0x82);
            break;
        case 5:
            bit_Cal(4, 0x80, 0x80);bit_Cal(5, 0x83, 0x82);bit_Cal(10, 0x83, 0x03);
            break;
        case 6:
            bit_Cal(4, 0x80, 0x80);bit_Cal(5, 0x83, 0x83);bit_Cal(10, 0x83, 0x03);
            break;
        case 7:
            bit_Cal(4, 0x80, 0x00);bit_Cal(5, 0x83, 0x80);bit_Cal(10, 0x83, 0x82);
            break;
        case 8:
            bit_Cal(4, 0x80, 0x80);bit_Cal(5, 0x83, 0x83);bit_Cal(10, 0x83, 0x83);
            break;
        case 9:
            bit_Cal(4, 0x80, 0x80);bit_Cal(5, 0x83, 0x82);bit_Cal(10, 0x83, 0x83);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(4, 0x80, 0x80);bit_Cal(5, 0x83, 0x81);bit_Cal(10, 0x83, 0x83);//显示数字0
    }

    //转速个位只能显示零
    bit_Cal(12, 0x80, 0x80);//显示数字0

    /***********工位8**********/
    if (work_num[7].Speed.Display_Set > 999)//大于999时
    {
        Val = work_num[7].Speed.Display_Set / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(14, 0x80, 0x00);bit_Cal(15, 0x80, 0x80);//显示数字1
        }
        else
        {
            bit_Cal(14, 0x80, 0x80);bit_Cal(15, 0x80, 0x80);//显示数字0
        }
    }
    else
    {
        bit_Cal(14, 0x80, 0x80);bit_Cal(15, 0x80, 0x80);//显示数字0
    }

    if (work_num[7].Speed.Display_Set > 99)//大于99时
    {
        Val = work_num[7].Speed.Display_Set / 100 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(20, 0xF0, 0xF0);bit_Cal(21, 0x70, 0x50);//显示数字0
            break;
        case 1:
            bit_Cal(20, 0xF0, 0x00);bit_Cal(21, 0x70, 0x50);
            break;
        case 2:
            bit_Cal(20, 0xF0, 0xD0);bit_Cal(21, 0x70, 0x30);
            break;
        case 3:
            bit_Cal(20, 0xF0, 0x90);bit_Cal(21, 0x70, 0x70);
            break;
        case 4:
            bit_Cal(20, 0xF0, 0x20);bit_Cal(21, 0x70, 0x70);
            break;
        case 5:
            bit_Cal(20, 0xF0, 0xB0);bit_Cal(21, 0x70, 0x60);
            break;
        case 6:
            bit_Cal(20, 0xF0, 0xF0);bit_Cal(21, 0x70, 0x60);
            break;
        case 7:
            bit_Cal(20, 0xF0, 0x10);bit_Cal(21, 0x70, 0x50);
            break;
        case 8:
            bit_Cal(20, 0xF0, 0xF0);bit_Cal(21, 0x70, 0x70);
            break;
        case 9:
            bit_Cal(20, 0xF0, 0xB0);bit_Cal(21, 0x70, 0x70);
            break;
        default:
            break;
        }
    }
    else
    {
         bit_Cal(20, 0xF0, 0xF0);bit_Cal(21, 0x70, 0x50);//显示数字0
    }

    if (work_num[7].Speed.Display_Set > 9) // 大于9时
    {
        Val = work_num[7].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(22, 0xF0, 0xF0);bit_Cal(23, 0x70, 0x50);//显示数字0
            break;
        case 1:
            bit_Cal(22, 0xF0, 0x00);bit_Cal(23, 0x70, 0x50);
            break;
        case 2:
            bit_Cal(22, 0xF0, 0xD0);bit_Cal(23, 0x70, 0x30);
            break;
        case 3:
            bit_Cal(22, 0xF0, 0x90);bit_Cal(23, 0x70, 0x70);
            break;
        case 4:
            bit_Cal(22, 0xF0, 0x20);bit_Cal(23, 0x70, 0x70);
            break;
        case 5:
            bit_Cal(22, 0xF0, 0xB0);bit_Cal(23, 0x70, 0x60);
            break;
        case 6:
            bit_Cal(22, 0xF0, 0xF0);bit_Cal(23, 0x70, 0x60);
            break;
        case 7:
            bit_Cal(22, 0xF0, 0x10);bit_Cal(23, 0x70, 0x50);
            break;
        case 8:
            bit_Cal(22, 0xF0, 0xF0);bit_Cal(23, 0x70, 0x70);
            break;
        case 9:
            bit_Cal(22, 0xF0, 0xB0);bit_Cal(23, 0x70, 0x70);
            break;
        default:
            break;
        }
    }
    else
    {
         bit_Cal(22, 0xF0, 0xF0);bit_Cal(23, 0x70, 0x50);//显示数字0
    }

    //转速个位只能显示零
    bit_Cal(23, 0x80, 0x80);//显示数字0

    /***********工位9**********/
    if (work_num[8].Speed.Display_Set > 999)//大于999时
    {
        Val = work_num[8].Speed.Display_Set / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(24, 0x80, 0x80);bit_Cal(26, 0x80, 0x00);//显示数字1
        }
        else
        {
            bit_Cal(24, 0x80, 0x80);bit_Cal(26, 0x80, 0x80);//显示数字0
        }
    }
    else
    {
        bit_Cal(24, 0x80, 0x80);bit_Cal(26, 0x80, 0x80);//显示数字0
    }

    if (work_num[8].Speed.Display_Set > 99)//大于99时
    {
        Val = work_num[8].Speed.Display_Set / 100 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(22, 0x0E, 0x0A);bit_Cal(23, 0x0F, 0x0F);//显示数字0
            break;
        case 1:
            bit_Cal(22, 0x0E, 0x0A);bit_Cal(23, 0x0F, 0x00);
            break;
        case 2:
            bit_Cal(22, 0x0E, 0x0C);bit_Cal(23, 0x0F, 0x0B);
            break;
        case 3:
            bit_Cal(22, 0x0E, 0x0E);bit_Cal(23, 0x0F, 0x09);
            break;
        case 4:
            bit_Cal(22, 0x0E, 0x0E);bit_Cal(23, 0x0F, 0x04);
            break;
        case 5:
            bit_Cal(22, 0x0E, 0x06);bit_Cal(23, 0x0F, 0x0D);
            break;
        case 6:
            bit_Cal(22, 0x0E, 0x0E);bit_Cal(23, 0x0F, 0x0D);
            break;
        case 7:
            bit_Cal(22, 0x0E, 0x0A);bit_Cal(23, 0x0F, 0x08);
            break;
        case 8:
            bit_Cal(22, 0x0E, 0x0E);bit_Cal(23, 0x0F, 0x0F);
            break;
        case 9:
            bit_Cal(22, 0x0E, 0x0E);bit_Cal(23, 0x0F, 0x0D);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(22, 0x0E, 0x0A);bit_Cal(23, 0x0F, 0x0F);//显示数字0
    }

    if (work_num[8].Speed.Display_Set > 9) // 大于9时
    {
        Val = work_num[8].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(20, 0x0E, 0x0A);bit_Cal(21, 0x0F, 0x0F);//显示数字0
            break;
        case 1:
            bit_Cal(20, 0x0E, 0x0A);bit_Cal(21, 0x0F, 0x00);
            break;
        case 2:
            bit_Cal(20, 0x0E, 0x0C);bit_Cal(21, 0x0F, 0x0B);
            break;
        case 3:
            bit_Cal(20, 0x0E, 0x0E);bit_Cal(21, 0x0F, 0x09);
            break;
        case 4:
            bit_Cal(20, 0x0E, 0x0E);bit_Cal(21, 0x0F, 0x04);
            break;
        case 5:
            bit_Cal(20, 0x0E, 0x06);bit_Cal(21, 0x0F, 0x0D);
            break;
        case 6:
            bit_Cal(20, 0x0E, 0x0E);bit_Cal(21, 0x0F, 0x0D);
            break;
        case 7:
            bit_Cal(20, 0x0E, 0x0A);bit_Cal(21, 0x0F, 0x08);
            break;
        case 8:
            bit_Cal(20, 0x0E, 0x0E);bit_Cal(21, 0x0F, 0x0F);
            break;
        case 9:
            bit_Cal(20, 0x0E, 0x0E);bit_Cal(21, 0x0F, 0x0D);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(20, 0x0E, 0x0A);bit_Cal(21, 0x0F, 0x0F);//显示数字0
    }

    //转速个位只能显示零
    bit_Cal(20, 0x01, 0x01);//显示数字0

    /***********工位10**********/
    if (work_num[9].Speed.Display_Set > 999)//大于999时
    {
        Val = work_num[9].Speed.Display_Set / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(45, 0x30, 0x20);//显示数字1
        }
        else
        {
            bit_Cal(45, 0x30, 0x30);//显示数字0
        }
    }
    else
    {
        bit_Cal(45, 0x30, 0x30);//显示数字0
    }

    if (work_num[9].Speed.Display_Set > 99)//大于99时
    {
        Val = work_num[9].Speed.Display_Set / 100 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(43, 0xE0, 0xA0);bit_Cal(44, 0xF0, 0xF0);//显示数字0
            break;
        case 1:
            bit_Cal(43, 0xE0, 0xA0);bit_Cal(44, 0xF0, 0x00);
            break;
        case 2:
            bit_Cal(43, 0xE0, 0xC0);bit_Cal(44, 0xF0, 0xB0);
            break;
        case 3:
            bit_Cal(43, 0xE0, 0xE0);bit_Cal(44, 0xF0, 0x90);
            break;
        case 4:
            bit_Cal(43, 0xE0, 0xE0);bit_Cal(44, 0xF0, 0x40);
            break;
        case 5:
            bit_Cal(43, 0xE0, 0x60);bit_Cal(44, 0xF0, 0xD0);
            break;
        case 6:
            bit_Cal(43, 0xE0, 0x60);bit_Cal(44, 0xF0, 0xF0);
            break;
        case 7:
            bit_Cal(43, 0xE0, 0xA0);bit_Cal(44, 0xF0, 0x80);
            break;
        case 8:
            bit_Cal(43, 0xE0, 0xE0);bit_Cal(44, 0xF0, 0xF0);
            break;
        case 9:
            bit_Cal(43, 0xE0, 0xE0);bit_Cal(44, 0xF0, 0xD0);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(43, 0xE0, 0xA0);bit_Cal(44, 0xF0, 0xF0);//显示数字0
    }

    if (work_num[9].Speed.Display_Set > 9) // 大于9时
    {
        Val = work_num[9].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(41, 0xE0, 0xA0);bit_Cal(42, 0xF0, 0xF0);//显示数字0
            break;
        case 1:
            bit_Cal(41, 0xE0, 0xA0);bit_Cal(42, 0xF0, 0x00);
            break;
        case 2:
            bit_Cal(41, 0xE0, 0xC0);bit_Cal(42, 0xF0, 0xB0);
            break;
        case 3:
            bit_Cal(41, 0xE0, 0xE0);bit_Cal(42, 0xF0, 0x90);
            break;
        case 4:
            bit_Cal(41, 0xE0, 0xE0);bit_Cal(42, 0xF0, 0x40);
            break;
        case 5:
            bit_Cal(41, 0xE0, 0x60);bit_Cal(42, 0xF0, 0xD0);
            break;
        case 6:
            bit_Cal(41, 0xE0, 0x60);bit_Cal(42, 0xF0, 0xF0);
            break;
        case 7:
            bit_Cal(41, 0xE0, 0xA0);bit_Cal(42, 0xF0, 0x80);
            break;
        case 8:
            bit_Cal(41, 0xE0, 0xE0);bit_Cal(42, 0xF0, 0xF0);
            break;
        case 9:
            bit_Cal(41, 0xE0, 0xE0);bit_Cal(42, 0xF0, 0xD0);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(41, 0xE0, 0xA0);bit_Cal(42, 0xF0, 0xF0);//显示数字0
    }

    //转速个位只能显示零
    bit_Cal(41, 0x10, 0x10);//显示数字0

    /***********工位11**********/
    if (work_num[10].Speed.Display_Set > 999)//大于999时
    {
        Val = work_num[10].Speed.Display_Set / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(37, 0x80, 0x00);bit_Cal(39, 0x80, 0x80);//显示数字1
        }
        else
        {
            bit_Cal(37, 0x80, 0x80);bit_Cal(39, 0x80, 0x80);//显示数字0
        }
    }
    else
    {
        bit_Cal(37, 0x80, 0x80);bit_Cal(39, 0x80, 0x80);//显示数字0
    }

    if (work_num[10].Speed.Display_Set > 99)//大于99时
    {
        Val = work_num[10].Speed.Display_Set / 100 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(39, 0x70, 0x50);bit_Cal(40, 0xF0, 0xF0);//显示数字0
            break;
        case 1:
            bit_Cal(39, 0x70, 0x50);bit_Cal(40, 0xF0, 0x00);
            break;
        case 2:
            bit_Cal(39, 0x70, 0x60);bit_Cal(40, 0xF0, 0xB0);
            break;
        case 3:
            bit_Cal(39, 0x70, 0x70);bit_Cal(40, 0xF0, 0x90);
            break;
        case 4:
            bit_Cal(39, 0x70, 0x70);bit_Cal(40, 0xF0, 0x40);
            break;
        case 5:
            bit_Cal(39, 0x70, 0x30);bit_Cal(40, 0xF0, 0xD0);
            break;
        case 6:
            bit_Cal(39, 0x70, 0x30);bit_Cal(40, 0xF0, 0xF0);
            break;
        case 7:
            bit_Cal(39, 0x70, 0x50);bit_Cal(40, 0xF0, 0x80);
            break;
        case 8:
            bit_Cal(39, 0x70, 0x70);bit_Cal(40, 0xF0, 0xF0);
            break;
        case 9:
            bit_Cal(39, 0x70, 0x70);bit_Cal(40, 0xF0, 0xD0);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(39, 0x70, 0x50);bit_Cal(40, 0xF0, 0xF0);//显示数字0
    }

    if (work_num[10].Speed.Display_Set > 9) // 大于9时
    {
        Val = work_num[10].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(37, 0x70, 0x50);bit_Cal(38, 0xF0, 0xF0);//显示数字0
            break;
        case 1:
            bit_Cal(37, 0x70, 0x50);bit_Cal(38, 0xF0, 0x00);
            break;
        case 2:
            bit_Cal(37, 0x70, 0x60);bit_Cal(38, 0xF0, 0xB0);
            break;
        case 3:
            bit_Cal(37, 0x70, 0x70);bit_Cal(38, 0xF0, 0x90);
            break;
        case 4:
            bit_Cal(37, 0x70, 0x70);bit_Cal(38, 0xF0, 0x40);
            break;
        case 5:
            bit_Cal(37, 0x70, 0x30);bit_Cal(38, 0xF0, 0xD0);
            break;
        case 6:
            bit_Cal(37, 0x70, 0x30);bit_Cal(38, 0xF0, 0xF0);
            break;
        case 7:
            bit_Cal(37, 0x70, 0x50);bit_Cal(38, 0xF0, 0x80);
            break;
        case 8:
            bit_Cal(37, 0x70, 0x70);bit_Cal(38, 0xF0, 0xF0);
            break;
        case 9:
            bit_Cal(37, 0x70, 0x70);bit_Cal(38, 0xF0, 0xD0);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(37, 0x70, 0x50);bit_Cal(38, 0xF0, 0xF0);//显示数字0
    }

    //转速个位只能显示零
    bit_Cal(36, 0x10, 0x10);//显示数字0

    /***********工位12**********/
    if (work_num[11].Speed.Display_Set > 999)//大于999时
    {
        Val = work_num[11].Speed.Display_Set / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(36, 0x60, 0x40);//显示数字1
        }
        else
        {
            bit_Cal(36, 0x60, 0x60);//显示数字0
        }
    }
    else
    {
        bit_Cal(36, 0x60, 0x60);//显示数字0
    }

    if (work_num[11].Speed.Display_Set > 99)//大于99时
    {
        Val = work_num[11].Speed.Display_Set / 100 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(34, 0xE0, 0xA0);bit_Cal(35, 0xF0, 0xF0);//显示数字0
            break;
        case 1:
            bit_Cal(34, 0xE0, 0xA0);bit_Cal(35, 0xF0, 0x00);
            break;
        case 2:
            bit_Cal(34, 0xE0, 0xC0);bit_Cal(35, 0xF0, 0xB0);
            break;
        case 3:
            bit_Cal(34, 0xE0, 0xE0);bit_Cal(35, 0xF0, 0x90);
            break;
        case 4:
            bit_Cal(34, 0xE0, 0xE0);bit_Cal(35, 0xF0, 0x40);
            break;
        case 5:
            bit_Cal(34, 0xE0, 0x60);bit_Cal(35, 0xF0, 0xD0);
            break;
        case 6:
            bit_Cal(34, 0xE0, 0x60);bit_Cal(35, 0xF0, 0xF0);
            break;
        case 7:
            bit_Cal(34, 0xE0, 0xA0);bit_Cal(35, 0xF0, 0x80);
            break;
        case 8:
            bit_Cal(34, 0xE0, 0xE0);bit_Cal(35, 0xF0, 0xF0);
            break;
        case 9:
            bit_Cal(34, 0xE0, 0xE0);bit_Cal(35, 0xF0, 0xD0);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(34, 0xE0, 0xA0);bit_Cal(35, 0xF0, 0xF0);//显示数字0
    }

    if (work_num[11].Speed.Display_Set > 9) // 大于9时
    {
        Val = work_num[11].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(32, 0xE0, 0xA0);bit_Cal(33, 0xF0, 0xF0);//显示数字0
            break;
        case 1:
            bit_Cal(32, 0xE0, 0xA0);bit_Cal(33, 0xF0, 0x00);
            break;
        case 2:
            bit_Cal(32, 0xE0, 0xC0);bit_Cal(33, 0xF0, 0xB0);
            break;
        case 3:
            bit_Cal(32, 0xE0, 0xE0);bit_Cal(33, 0xF0, 0x90);
            break;
        case 4:
            bit_Cal(32, 0xE0, 0xE0);bit_Cal(33, 0xF0, 0x40);
            break;
        case 5:
            bit_Cal(32, 0xE0, 0x60);bit_Cal(33, 0xF0, 0xD0);
            break;
        case 6:
            bit_Cal(32, 0xE0, 0x60);bit_Cal(33, 0xF0, 0xF0);
            break;
        case 7:
            bit_Cal(32, 0xE0, 0xA0);bit_Cal(33, 0xF0, 0x80);
            break;
        case 8:
            bit_Cal(32, 0xE0, 0xE0);bit_Cal(33, 0xF0, 0xF0);
            break;
        case 9:
            bit_Cal(32, 0xE0, 0xE0);bit_Cal(33, 0xF0, 0xD0);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(32, 0xE0, 0xA0);bit_Cal(33, 0xF0, 0xF0);//显示数字0
    }

    //转速个位只能显示零
    bit_Cal(32, 0x10, 0x10);//显示数字0

    /***********工位13**********/
    if (work_num[12].Speed.Display_Set > 999)//大于999时
    {
        Val = work_num[12].Speed.Display_Set / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(45, 0x0C, 0x08);//显示数字1
        }
        else
        {
            bit_Cal(45, 0x0C, 0x0C);//显示数字0
        }
    }
    else
    {
        bit_Cal(45, 0x0C, 0x0C);//显示数字0
    }

    if (work_num[12].Speed.Display_Set > 99)//大于99时
    {
        Val = work_num[12].Speed.Display_Set / 100 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(43, 0x0E, 0x0A);bit_Cal(44, 0x0F, 0x0F);//显示数字0
            break;
        case 1:
            bit_Cal(43, 0x0E, 0x0A);bit_Cal(44, 0x0F, 0x00);
            break;
        case 2:
            bit_Cal(43, 0x0E, 0x0C);bit_Cal(44, 0x0F, 0x0B);
            break;
        case 3:
            bit_Cal(43, 0x0E, 0x0E);bit_Cal(44, 0x0F, 0x09);
            break;
        case 4:
            bit_Cal(43, 0x0E, 0x0E);bit_Cal(44, 0x0F, 0x04);
            break;
        case 5:
            bit_Cal(43, 0x0E, 0x06);bit_Cal(44, 0x0F, 0x0D);
            break;
        case 6:
            bit_Cal(43, 0x0E, 0x0E);bit_Cal(44, 0x0F, 0x0D);
            break;
        case 7:
            bit_Cal(43, 0x0E, 0x0A);bit_Cal(44, 0x0F, 0x08);
            break;
        case 8:
            bit_Cal(43, 0x0E, 0x0E);bit_Cal(44, 0x0F, 0x0F);
            break;
        case 9:
            bit_Cal(43, 0x0E, 0x0E);bit_Cal(44, 0x0F, 0x0D);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(43, 0x0E, 0x0A);bit_Cal(44, 0x0F, 0x0F);//显示数字0
    }

    if (work_num[12].Speed.Display_Set > 9) // 大于9时
    {
        Val = work_num[12].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(41, 0x0E, 0x0A);bit_Cal(42, 0x0F, 0x0F);//显示数字0
            break;
        case 1:
            bit_Cal(41, 0x0E, 0x0A);bit_Cal(42, 0x0F, 0x00);
            break;
        case 2:
            bit_Cal(41, 0x0E, 0x0C);bit_Cal(42, 0x0F, 0x0B);
            break;
        case 3:
            bit_Cal(41, 0x0E, 0x0E);bit_Cal(42, 0x0F, 0x09);
            break;
        case 4:
            bit_Cal(41, 0x0E, 0x0E);bit_Cal(42, 0x0F, 0x04);
            break;
        case 5:
            bit_Cal(41, 0x0E, 0x06);bit_Cal(42, 0x0F, 0x0D);
            break;
        case 6:
            bit_Cal(41, 0x0E, 0x0E);bit_Cal(42, 0x0F, 0x0D);
            break;
        case 7:
            bit_Cal(41, 0x0E, 0x0A);bit_Cal(42, 0x0F, 0x08);
            break;
        case 8:
            bit_Cal(41, 0x0E, 0x0E);bit_Cal(42, 0x0F, 0x0F);
            break;
        case 9:
            bit_Cal(41, 0x0E, 0x0E);bit_Cal(42, 0x0F, 0x0D);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(41, 0x0E, 0x0A);bit_Cal(42, 0x0F, 0x0F);//显示数字0
    }

    //转速个位只能显示零
    bit_Cal(41, 0x01, 0x01);//显示数字0

    /***********工位14**********/
    if (work_num[13].Speed.Display_Set > 999)//大于999时
    {
        Val = work_num[13].Speed.Display_Set / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(45, 0x03, 0x02);//显示数字1
        }
        else
        {
            bit_Cal(45, 0x03, 0x03);//显示数字0
        }
    }
    else
    {
        bit_Cal(45, 0x03, 0x03);//显示数字0
    }

    if (work_num[13].Speed.Display_Set > 99)//大于99时
    {
        Val = work_num[13].Speed.Display_Set / 100 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(39, 0x07, 0x05);bit_Cal(40, 0x0F, 0x0F);//显示数字0
            break;
        case 1:
            bit_Cal(39, 0x07, 0x05);bit_Cal(40, 0x0F, 0x00);
            break;
        case 2:
            bit_Cal(39, 0x07, 0x06);bit_Cal(40, 0x0F, 0x0B);
            break;
        case 3:
            bit_Cal(39, 0x07, 0x07);bit_Cal(40, 0x0F, 0x09);
            break;
        case 4:
            bit_Cal(39, 0x07, 0x07);bit_Cal(40, 0x0F, 0x04);
            break;
        case 5:
            bit_Cal(39, 0x07, 0x03);bit_Cal(40, 0x0F, 0x0D);
            break;
        case 6:
            bit_Cal(39, 0x07, 0x03);bit_Cal(40, 0x0F, 0x0F);
            break;
        case 7:
            bit_Cal(39, 0x07, 0x05);bit_Cal(40, 0x0F, 0x08);
            break;
        case 8:
            bit_Cal(39, 0x07, 0x07);bit_Cal(40, 0x0F, 0x0F);
            break;
        case 9:
            bit_Cal(39, 0x07, 0x07);bit_Cal(40, 0x0F, 0x0D);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(39, 0x07, 0x05);bit_Cal(40, 0x0F, 0x0F);//显示数字0
    }

    if (work_num[13].Speed.Display_Set > 9) // 大于9时
    {
        Val = work_num[13].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(37, 0x0E, 0x0A);bit_Cal(38, 0x0F, 0x0F);//显示数字0
            break;
        case 1:
            bit_Cal(37, 0x0E, 0x0A);bit_Cal(38, 0x0F, 0x00);
            break;
        case 2:
            bit_Cal(37, 0x0E, 0x0C);bit_Cal(38, 0x0F, 0x0B);
            break;
        case 3:
            bit_Cal(37, 0x0E, 0x0E);bit_Cal(38, 0x0F, 0x09);
            break;
        case 4:
            bit_Cal(37, 0x0E, 0x0E);bit_Cal(38, 0x0F, 0x04);
            break;
        case 5:
            bit_Cal(37, 0x0E, 0x06);bit_Cal(38, 0x0F, 0x0D);
            break;
        case 6:
            bit_Cal(37, 0x0E, 0x06);bit_Cal(38, 0x0F, 0x0F);
            break;
        case 7:
            bit_Cal(37, 0x0E, 0x0A);bit_Cal(38, 0x0F, 0x08);
            break;
        case 8:
            bit_Cal(37, 0x0E, 0x0E);bit_Cal(38, 0x0F, 0x0F);
            break;
        case 9:
            bit_Cal(37, 0x0E, 0x0E);bit_Cal(38, 0x0F, 0x0D);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(37, 0x0E, 0x0A);bit_Cal(38, 0x0F, 0x0F);//显示数字0
    }

    //转速个位只能显示零
    bit_Cal(36, 0x02, 0x02);//显示数字0

    /***********工位15**********/
    if (work_num[14].Speed.Display_Set > 999)//大于999时
    {
        Val = work_num[14].Speed.Display_Set / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(36, 0x0C, 0x08);//显示数字1
        }
        else
        {
            bit_Cal(36, 0x0C, 0x0C);//显示数字0
        }
    }
    else
    {
        bit_Cal(36, 0x0C, 0x0C);//显示数字0
    }

    if (work_num[14].Speed.Display_Set > 99)//大于99时
    {
        Val = work_num[14].Speed.Display_Set / 100 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(34, 0x0E, 0x0A);bit_Cal(35, 0x0F, 0x0F);//显示数字0
            break;
        case 1:
            bit_Cal(34, 0x0E, 0x0A);bit_Cal(35, 0x0F, 0x00);
            break;
        case 2:
            bit_Cal(34, 0x0E, 0x0C);bit_Cal(35, 0x0F, 0x0B);
            break;
        case 3:
            bit_Cal(34, 0x0E, 0x0E);bit_Cal(35, 0x0F, 0x09);
            break;
        case 4:
            bit_Cal(34, 0x0E, 0x0E);bit_Cal(35, 0x0F, 0x04);
            break;
        case 5:
            bit_Cal(34, 0x0E, 0x06);bit_Cal(35, 0x0F, 0x0D);
            break;
        case 6:
            bit_Cal(34, 0x0E, 0x06);bit_Cal(35, 0x0F, 0x0F);
            break;
        case 7:
            bit_Cal(34, 0x0E, 0x0A);bit_Cal(35, 0x0F, 0x08);
            break;
        case 8:
            bit_Cal(34, 0x0E, 0x0E);bit_Cal(35, 0x0F, 0x0F);
            break;
        case 9:
            bit_Cal(34, 0x0E, 0x0E);bit_Cal(35, 0x0F, 0x0D);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(34, 0x0E, 0x0A);bit_Cal(35, 0x0F, 0x0F);//显示数字0
    }

    if (work_num[14].Speed.Display_Set > 9) // 大于9时
    {
        Val = work_num[14].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(32, 0x0E, 0x0A);bit_Cal(33, 0x0F, 0x0F);//显示数字0
            break;
        case 1:
            bit_Cal(32, 0x0E, 0x0A);bit_Cal(33, 0x0F, 0x00);
            break;
        case 2:
            bit_Cal(32, 0x0E, 0x0C);bit_Cal(33, 0x0F, 0x0B);
            break;
        case 3:
            bit_Cal(32, 0x0E, 0x0E);bit_Cal(33, 0x0F, 0x09);
            break;
        case 4:
            bit_Cal(32, 0x0E, 0x0E);bit_Cal(33, 0x0F, 0x04);
            break;
        case 5:
            bit_Cal(32, 0x0E, 0x06);bit_Cal(33, 0x0F, 0x0D);
            break;
        case 6:
            bit_Cal(32, 0x0E, 0x06);bit_Cal(33, 0x0F, 0x0F);
            break;
        case 7:
            bit_Cal(32, 0x0E, 0x0A);bit_Cal(33, 0x0F, 0x08);
            break;
        case 8:
            bit_Cal(32, 0x0E, 0x0E);bit_Cal(33, 0x0F, 0x0F);
            break;
        case 9:
            bit_Cal(32, 0x0E, 0x0E);bit_Cal(33, 0x0F, 0x0D);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(32, 0x0E, 0x0A);bit_Cal(33, 0x0F, 0x0F);//显示数字0
    }

    //转速个位只能显示零
    bit_Cal(32, 0x01, 0x01);//显示数字0

    /****************************************设定区域****************************************/
    /***********实际转速**********/
    if (work_num[sys.New_Work].Speed.Display_Rel > 999)//大于999时
    {
        Val = work_num[sys.New_Work].Speed.Display_Rel / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(15, 0x03, 0x01);//显示数字1
        }
        else
        {
            bit_Cal(15, 0x03, 0x03);//显示数字0
        }
    }
    else
    {
        bit_Cal(15, 0x03, 0x03);//显示数字0
    }

    if (work_num[sys.New_Work].Speed.Display_Rel > 99)//大于99时
    {
        Val = work_num[sys.New_Work].Speed.Display_Rel / 100 % 10;
         switch (Val)
        {
        case 0:
            bit_Cal(16, 0x07, 0x05);bit_Cal(17, 0x0F, 0x0F);//显示数字0
            break;
        case 1:
            bit_Cal(16, 0x07, 0x00);bit_Cal(17, 0x0F, 0x06);
            break;
        case 2:
            bit_Cal(16, 0x07, 0x06);bit_Cal(17, 0x0F, 0x0B);
            break;
        case 3:
            bit_Cal(16, 0x07, 0x02);bit_Cal(17, 0x0F, 0x0F);
            break;
        case 4:
            bit_Cal(16, 0x07, 0x03);bit_Cal(17, 0x0F, 0x06);
            break;
        case 5:
            bit_Cal(16, 0x07, 0x03);bit_Cal(17, 0x0F, 0x0D);
            break;
        case 6:
            bit_Cal(16, 0x07, 0x07);bit_Cal(17, 0x0F, 0x0D);
            break;
        case 7:
            bit_Cal(16, 0x07, 0x00);bit_Cal(17, 0x0F, 0x07);
            break;
        case 8:
            bit_Cal(16, 0x07, 0x07);bit_Cal(17, 0x0F, 0x0F);
            break;
        case 9:
            bit_Cal(16, 0x07, 0x03);bit_Cal(17, 0x0F, 0x0F);
            break;
        default:
            break;
        }
    }
    else
    {
        bit_Cal(16, 0x07, 0x05);bit_Cal(17, 0x0F, 0x0F);//显示数字0
    }

    if (work_num[sys.New_Work].Speed.Display_Rel > 9) // 大于9时
    {
        Val = work_num[sys.New_Work].Speed.Display_Rel / 10 % 10;
        switch (Val)
        {
        case 0:
            bit_Cal(18, 0x0F, 0x0F);bit_Cal(19, 0x07, 0x05);//显示数字0
            break;
        case 1:
            bit_Cal(18, 0x0F, 0x00);bit_Cal(19, 0x07, 0x05);
            break;
        case 2:
            bit_Cal(18, 0x0F, 0x0D);bit_Cal(19, 0x07, 0x03);
            break;
        case 3:
            bit_Cal(18, 0x0F, 0x09);bit_Cal(19, 0x07, 0x07);
            break;
        case 4:
            bit_Cal(18, 0x0F, 0x02);bit_Cal(19, 0x07, 0x07);
            break;
        case 5:
            bit_Cal(18, 0x0F, 0x0B);bit_Cal(19, 0x07, 0x06);
            break;
        case 6:
            bit_Cal(18, 0x0F, 0x0F);bit_Cal(19, 0x07, 0x06);
            break;
        case 7:
            bit_Cal(18, 0x0F, 0x01);bit_Cal(19, 0x07, 0x05);
            break;
        case 8:
            bit_Cal(18, 0x0F, 0x0F);bit_Cal(19, 0x07, 0x07);
            break;
        case 9:
            bit_Cal(18, 0x0F, 0x0B);bit_Cal(19, 0x07, 0x07);
            break;
        default:
            break;
        }
    }
    else
    {
         bit_Cal(18, 0x0F, 0x0F);bit_Cal(19, 0x07, 0x05);//显示数字0
    }
    //实际转速个位只能显示零
    bit_Cal(19, 0x08, 0x08);//显示数字0

    /***********设定转速**********/
    if(Speed_ShowFlag && EC11A[1].EC11A_Knob <= 0)
    {
        bit_Cal(15, 0x30, 0x00);//不显示
        bit_Cal(16, 0xF0, 0x00);bit_Cal(17, 0x70, 0x00);//不显示
        bit_Cal(18, 0xF0, 0x00);bit_Cal(19, 0x70, 0x00);//不显示
        bit_Cal(19, 0x80, 0x00);//不显示
    }
    else
    {
        if(work_num[sys.New_Work].Speed.Display_Set == 0)//显示“ -- ”
        {
            bit_Cal(15, 0x30, 0x00);//不显示
            bit_Cal(16, 0xF0, 0x00);bit_Cal(17, 0x70, 0x20);//显示“-”
            bit_Cal(18, 0xF0, 0x00);bit_Cal(19, 0x70, 0x20);//显示“-”
            bit_Cal(19, 0x80, 0x00);//不显示
        }
        else
        {
            if (work_num[sys.New_Work].Speed.Display_Set > 999)//大于999时
            {
                Val = work_num[sys.New_Work].Speed.Display_Set / 1000 % 10;
                if(Val > 0)
                {
                    bit_Cal(15, 0x30, 0x10);//显示数字1
                }
                else
                {
                    bit_Cal(15, 0x30, 0x30);//显示数字0
                }
            }
            else
            {
                bit_Cal(15, 0x30, 0x30);//显示数字0
            }

            if (work_num[sys.New_Work].Speed.Display_Set > 99)//大于99时
            {
                Val = work_num[sys.New_Work].Speed.Display_Set / 100 % 10;
                switch (Val)
                {
                case 0:
                    bit_Cal(16, 0xF0, 0xF0);bit_Cal(17, 0x70, 0x50);//显示数字0
                    break;
                case 1:
                    bit_Cal(16, 0xF0, 0x00);bit_Cal(17, 0x70, 0x50);
                    break;
                case 2:
                    bit_Cal(16, 0xF0, 0xD0);bit_Cal(17, 0x70, 0x30);
                    break;
                case 3:
                    bit_Cal(16, 0xF0, 0x90);bit_Cal(17, 0x70, 0x70);
                    break;
                case 4:
                    bit_Cal(16, 0xF0, 0x20);bit_Cal(17, 0x70, 0x70);
                    break;
                case 5:
                    bit_Cal(16, 0xF0, 0xB0);bit_Cal(17, 0x70, 0x60);
                    break;
                case 6:
                    bit_Cal(16, 0xF0, 0xF0);bit_Cal(17, 0x70, 0x60);
                    break;
                case 7:
                    bit_Cal(16, 0xF0, 0x10);bit_Cal(17, 0x70, 0x50);
                    break;
                case 8:
                    bit_Cal(16, 0xF0, 0xF0);bit_Cal(17, 0x70, 0x70);
                    break;
                case 9:
                    bit_Cal(16, 0xF0, 0xB0);bit_Cal(17, 0x70, 0x70);
                    break;
                default:
                    break;
                }
            }
            else
            {
                 bit_Cal(16, 0xF0, 0xF0);bit_Cal(17, 0x70, 0x50);//显示数字0
            }

            if (work_num[sys.New_Work].Speed.Display_Set > 9) // 大于9时
            {
                Val = work_num[sys.New_Work].Speed.Display_Set / 10 % 10;
                switch (Val)
                {
                case 0:
                    bit_Cal(18, 0xF0, 0xF0);bit_Cal(19, 0x70, 0x50);//显示数字0
                    break;
                case 1:
                    bit_Cal(18, 0xF0, 0x00);bit_Cal(19, 0x70, 0x50);
                    break;
                case 2:
                    bit_Cal(18, 0xF0, 0xD0);bit_Cal(19, 0x70, 0x30);
                    break;
                case 3:
                    bit_Cal(18, 0xF0, 0x90);bit_Cal(19, 0x70, 0x70);
                    break;
                case 4:
                    bit_Cal(18, 0xF0, 0x20);bit_Cal(19, 0x70, 0x70);
                    break;
                case 5:
                    bit_Cal(18, 0xF0, 0xB0);bit_Cal(19, 0x70, 0x60);
                    break;
                case 6:
                    bit_Cal(18, 0xF0, 0xF0);bit_Cal(19, 0x70, 0x60);
                    break;
                case 7:
                    bit_Cal(18, 0xF0, 0x10);bit_Cal(19, 0x70, 0x50);
                    break;
                case 8:
                    bit_Cal(18, 0xF0, 0xF0);bit_Cal(19, 0x70, 0x70);
                    break;
                case 9:
                    bit_Cal(18, 0xF0, 0xB0);bit_Cal(19, 0x70, 0x70);
                    break;
                default:
                    break;
                }
            }
            else
            {
                 bit_Cal(18, 0xF0, 0xF0);bit_Cal(19, 0x70, 0x50);//显示数字0
            }

            bit_Cal(19, 0x80, 0x80);//显示数字0
        }
    }

    /***********实际时间**********/
    Val = work_num[sys.New_Work].Time.Display_Rel / 3600 / 10;//计算十位为单位的小时数
    switch (Val)
    {
    case 0:
        bit_Cal(30, 0x70, 0x50);bit_Cal(31, 0xF0, 0xF0);//显示数字0
        break;
    case 1:
        bit_Cal(30, 0x70, 0x50);bit_Cal(31, 0xF0, 0x00);
        break;
    case 2:
        bit_Cal(30, 0x70, 0x60);bit_Cal(31, 0xF0, 0xB0);
        break;
    case 3:
        bit_Cal(30, 0x70, 0x70);bit_Cal(31, 0xF0, 0x90);
        break;
    case 4:
        bit_Cal(30, 0x70, 0x70);bit_Cal(31, 0xF0, 0x40);
        break;
    case 5:
        bit_Cal(30, 0x70, 0x30);bit_Cal(31, 0xF0, 0xD0);
        break;
    case 6:
        bit_Cal(30, 0x70, 0x30);bit_Cal(31, 0xF0, 0xF0);
        break;
    case 7:
        bit_Cal(30, 0x70, 0x50);bit_Cal(31, 0xF0, 0x80);
        break;
    case 8:
        bit_Cal(30, 0x70, 0x70);bit_Cal(31, 0xF0, 0xF0);
        break;
    case 9:
        bit_Cal(30, 0x70, 0x70);bit_Cal(31, 0xF0, 0xD0);
        break;
    default:
        break;
    }


    Val = work_num[sys.New_Work].Time.Display_Rel / 3600 % 10;// 计算个位为单位的小时数
    switch (Val)
    {
    case 0:
        bit_Cal(28, 0x70, 0x50);bit_Cal(29, 0xF0, 0xF0);//显示数字0
        break;
    case 1:
        bit_Cal(28, 0x70, 0x50);bit_Cal(29, 0xF0, 0x00);
        break;
    case 2:
        bit_Cal(28, 0x70, 0x60);bit_Cal(29, 0xF0, 0xB0);
        break;
    case 3:
        bit_Cal(28, 0x70, 0x70);bit_Cal(29, 0xF0, 0x90);
        break;
    case 4:
        bit_Cal(28, 0x70, 0x70);bit_Cal(29, 0xF0, 0x40);
        break;
    case 5:
        bit_Cal(28, 0x70, 0x30);bit_Cal(29, 0xF0, 0xD0);
        break;
    case 6:
        bit_Cal(28, 0x70, 0x30);bit_Cal(29, 0xF0, 0xF0);
        break;
    case 7:
        bit_Cal(28, 0x70, 0x50);bit_Cal(29, 0xF0, 0x80);
        break;
    case 8:
        bit_Cal(28, 0x70, 0x70);bit_Cal(29, 0xF0, 0xF0);
        break;
    case 9:
        bit_Cal(28, 0x70, 0x70);bit_Cal(29, 0xF0, 0xD0);
        break;
    default:
        break;
    }

    Val = work_num[sys.New_Work].Time.Display_Rel % 3600 / 60 / 10; // 计算十分位为单位的分钟数
    switch (Val)
    {
    case 0:
        bit_Cal(26, 0x70, 0x50);bit_Cal(27, 0xF0, 0xF0);//显示数字0
        break;
    case 1:
        bit_Cal(26, 0x70, 0x50);bit_Cal(27, 0xF0, 0x00);
        break;
    case 2:
        bit_Cal(26, 0x70, 0x60);bit_Cal(27, 0xF0, 0xB0);
        break;
    case 3:
        bit_Cal(26, 0x70, 0x70);bit_Cal(27, 0xF0, 0x90);
        break;
    case 4:
        bit_Cal(26, 0x70, 0x70);bit_Cal(27, 0xF0, 0x40);
        break;
    case 5:
        bit_Cal(26, 0x70, 0x30);bit_Cal(27, 0xF0, 0xD0);
        break;
    case 6:
        bit_Cal(26, 0x70, 0x30);bit_Cal(27, 0xF0, 0xF0);
        break;
    case 7:
        bit_Cal(26, 0x70, 0x50);bit_Cal(27, 0xF0, 0x80);
        break;
    case 8:
        bit_Cal(26, 0x70, 0x70);bit_Cal(27, 0xF0, 0xF0);
        break;
    case 9:
        bit_Cal(26, 0x70, 0x70);bit_Cal(27, 0xF0, 0xD0);
        break;
    default:
        break;
    } 

    Val = work_num[sys.New_Work].Time.Display_Rel % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
     switch (Val)
    {
    case 0:
        bit_Cal(24, 0x70, 0x50);bit_Cal(25, 0xF0, 0xF0);//显示数字0
        break;
    case 1:
        bit_Cal(24, 0x70, 0x50);bit_Cal(25, 0xF0, 0x00);
        break;
    case 2:
        bit_Cal(24, 0x70, 0x60);bit_Cal(25, 0xF0, 0xB0);
        break;
    case 3:
        bit_Cal(24, 0x70, 0x70);bit_Cal(25, 0xF0, 0x90);
        break;
    case 4:
        bit_Cal(24, 0x70, 0x70);bit_Cal(25, 0xF0, 0x40);
        break;
    case 5:
        bit_Cal(24, 0x70, 0x30);bit_Cal(25, 0xF0, 0xD0);
        break;
    case 6:
        bit_Cal(24, 0x70, 0x30);bit_Cal(25, 0xF0, 0xF0);
        break;
    case 7:
        bit_Cal(24, 0x70, 0x50);bit_Cal(25, 0xF0, 0x80);
        break;
    case 8:
        bit_Cal(24, 0x70, 0x70);bit_Cal(25, 0xF0, 0xF0);
        break;
    case 9:
        bit_Cal(24, 0x70, 0x70);bit_Cal(25, 0xF0, 0xD0);
        break;
    default:
        break;
    }

    /***********设定时间**********/
    if(Time_ShowFlag && EC11A[1].EC11A_Knob <= 0)//不显示设定转速
    {
        bit_Cal(30, 0x07, 0x00);bit_Cal(31, 0x0F, 0x00);//不显示
        bit_Cal(28, 0x0E, 0x00);bit_Cal(29, 0x0F, 0x00);//不显示
        bit_Cal(26, 0x0E, 0x00);bit_Cal(27, 0x0F, 0x00);//不显示
        bit_Cal(24, 0x0E, 0x00);bit_Cal(25, 0x0F, 0x00);//不显示
    }
    else
    {
        if(work_num[sys.New_Work].Time.Display_Set == 0)
        {
            bit_Cal(30, 0x07, 0x02);bit_Cal(31, 0x0F, 0x00);//显示“-”
            bit_Cal(28, 0x0E, 0x04);bit_Cal(29, 0x0F, 0x00);//显示“-”
            bit_Cal(26, 0x0E, 0x04);bit_Cal(27, 0x0F, 0x00);//显示“-”
            bit_Cal(24, 0x0E, 0x04);bit_Cal(25, 0x0F, 0x00);//显示“-”
        }
        else
        {
            Val = work_num[sys.New_Work].Time.Display_Set / 3600 / 10;//计算十位为单位的小时数
            switch (Val)
            {
            case 0:
                bit_Cal(30, 0x07, 0x05);bit_Cal(31, 0x0F, 0x0F);//显示数字0
                break;
            case 1:
                bit_Cal(30, 0x07, 0x05);bit_Cal(31, 0x0F, 0x00);
                break;
            case 2:
                bit_Cal(30, 0x07, 0x06);bit_Cal(31, 0x0F, 0x0B);
                break;
            case 3:
                bit_Cal(30, 0x07, 0x07);bit_Cal(31, 0x0F, 0x09);
                break;
            case 4:
                bit_Cal(30, 0x07, 0x07);bit_Cal(31, 0x0F, 0x04);
                break;
            case 5:
                bit_Cal(30, 0x07, 0x03);bit_Cal(31, 0x0F, 0x0D);
                break;
            case 6:
                bit_Cal(30, 0x07, 0x03);bit_Cal(31, 0x0F, 0x0F);
                break;
            case 7:
                bit_Cal(30, 0x07, 0x05);bit_Cal(31, 0x0F, 0x08);
                break;
            case 8:
                bit_Cal(30, 0x07, 0x07);bit_Cal(31, 0x0F, 0x0F);
                break;
            case 9:
                bit_Cal(30, 0x07, 0x07);bit_Cal(31, 0x0F, 0x0D);
                break;
            default:
                break;
            }


            Val = work_num[sys.New_Work].Time.Display_Set / 3600 % 10;// 计算个位为单位的小时数
            switch (Val)
            {
            case 0:
                bit_Cal(28, 0x0E, 0x0A);bit_Cal(29, 0x0F, 0x0F);//显示数字0
                break;
            case 1:
                bit_Cal(28, 0x0E, 0x0A);bit_Cal(29, 0x0F, 0x00);
                break;
            case 2:
                bit_Cal(28, 0x0E, 0x0C);bit_Cal(29, 0x0F, 0x0B);
                break;
            case 3:
                bit_Cal(28, 0x0E, 0x0E);bit_Cal(29, 0x0F, 0x09);
                break;
            case 4:
                bit_Cal(28, 0x0E, 0x0E);bit_Cal(29, 0x0F, 0x04);
                break;
            case 5:
                bit_Cal(28, 0x0E, 0x06);bit_Cal(29, 0x0F, 0x0D);
                break;
            case 6:
                bit_Cal(28, 0x0E, 0x06);bit_Cal(29, 0x0F, 0x0F);
                break;
            case 7:
                bit_Cal(28, 0x0E, 0x0A);bit_Cal(29, 0x0F, 0x08);
                break;
            case 8:
                bit_Cal(28, 0x0E, 0x0E);bit_Cal(29, 0x0F, 0x0F);
                break;
            case 9:
                bit_Cal(28, 0x0E, 0x0E);bit_Cal(29, 0x0F, 0x0D);
                break;
            default:
                break;
            }

            Val = work_num[sys.New_Work].Time.Display_Set % 3600 / 60 / 10; // 计算十分位为单位的分钟数
            switch (Val)
            {
            case 0:
                bit_Cal(26, 0x0E, 0x0A);bit_Cal(27, 0x0F, 0x0F);//显示数字0
                break;
            case 1:
                bit_Cal(26, 0x0E, 0x0A);bit_Cal(27, 0x0F, 0x00);
                break;
            case 2:
                bit_Cal(26, 0x0E, 0x0C);bit_Cal(27, 0x0F, 0x0B);
                break;
            case 3:
                bit_Cal(26, 0x0E, 0x0E);bit_Cal(27, 0x0F, 0x09);
                break;
            case 4:
                bit_Cal(26, 0x0E, 0x0E);bit_Cal(27, 0x0F, 0x04);
                break;
            case 5:
                bit_Cal(26, 0x0E, 0x06);bit_Cal(27, 0x0F, 0x0D);
                break;
            case 6:
                bit_Cal(26, 0x0E, 0x06);bit_Cal(27, 0x0F, 0x0F);
                break;
            case 7:
                bit_Cal(26, 0x0E, 0x0A);bit_Cal(27, 0x0F, 0x08);
                break;
            case 8:
                bit_Cal(26, 0x0E, 0x0E);bit_Cal(27, 0x0F, 0x0F);
                break;
            case 9:
                bit_Cal(26, 0x0E, 0x0E);bit_Cal(27, 0x0F, 0x0D);
                break;
            default:
                break;
            }

            Val = work_num[sys.New_Work].Time.Display_Set % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
            switch (Val)
            {
            case 0:
                bit_Cal(24, 0x0E, 0x0A);bit_Cal(25, 0x0F, 0x0F);//显示数字0
                break;
            case 1:
                bit_Cal(24, 0x0E, 0x0A);bit_Cal(25, 0x0F, 0x00);
                break;
            case 2:
                bit_Cal(24, 0x0E, 0x0C);bit_Cal(25, 0x0F, 0x0B);
                break;
            case 3:
                bit_Cal(24, 0x0E, 0x0E);bit_Cal(25, 0x0F, 0x09);
                break;
            case 4:
                bit_Cal(24, 0x0E, 0x0E);bit_Cal(25, 0x0F, 0x04);
                break;
            case 5:
                bit_Cal(24, 0x0E, 0x06);bit_Cal(25, 0x0F, 0x0D);
                break;
            case 6:
                bit_Cal(24, 0x0E, 0x06);bit_Cal(25, 0x0F, 0x0F);
                break;
            case 7:
                bit_Cal(24, 0x0E, 0x0A);bit_Cal(25, 0x0F, 0x08);
                break;
            case 8:
                bit_Cal(24, 0x0E, 0x0E);bit_Cal(25, 0x0F, 0x0F);
                break;
            case 9:
                bit_Cal(24, 0x0E, 0x0E);bit_Cal(25, 0x0F, 0x0D);
                break;
            default:
                break;
            }
        }
    }

    bit_Cal(2, 0x08, 0x00);//显示工位1得下划线
    bit_Cal(7, 0x08, 0x00);//显示工位2得下划线
    bit_Cal(12, 0x08, 0x00);//显示工位3得下划线
    bit_Cal(0, 0x40, 0x00);//显示工位4得下划线
    bit_Cal(7, 0x80, 0x00);//显示工位5得下划线
    bit_Cal(10, 0x40, 0x00);//显示工位6得下划线
    bit_Cal(36, 0x80, 0x00);//显示工位7得下划线
    bit_Cal(21, 0x80, 0x00);//显示工位8得下划线
    bit_Cal(22, 0x01, 0x00);//显示工位9得下划线
    bit_Cal(43, 0x10, 0x00);//显示工位10得下划线
    bit_Cal(39, 0x08, 0x00);//显示工位11得下划线
    bit_Cal(34, 0x10, 0x00);//显示工位12得下划线
    bit_Cal(43, 0x01, 0x00);//显示工位13得下划线
    bit_Cal(37, 0x01, 0x00);//显示工位14得下划线
    bit_Cal(34, 0x01, 0x00);//显示工位14得下划线
    
    switch(sys.New_Work)
    {
        case 0:bit_Cal(2, 0x08, 0x08);//显示工位1得下划线
            break;
        case 1:bit_Cal(7, 0x08, 0x08);//显示工位2得下划线
            break;
        case 2:bit_Cal(12, 0x08, 0x08);//显示工位3得下划线
            break;
        case 3:bit_Cal(0, 0x40, 0x40);//显示工位4得下划线
            break;
        case 4:bit_Cal(7, 0x80, 0x80);//显示工位5得下划线
            break;
        case 5:bit_Cal(10, 0x40, 0x40);//显示工位6得下划线
            break;
        case 6:bit_Cal(36, 0x80, 0x80);//显示工位7得下划线
            break;
        case 7:bit_Cal(21, 0x80, 0x80);//显示工位8得下划线
            break;
        case 8:bit_Cal(22, 0x01, 0x01);//显示工位9得下划线
            break;
        case 9:bit_Cal(43, 0x10, 0x10);//显示工位10得下划线
            break;
        case 10:bit_Cal(39, 0x08, 0x08);//显示工位11得下划线
            break;
        case 11:bit_Cal(34, 0x10, 0x10);//显示工位12得下划线
            break;
        case 12:bit_Cal(43, 0x01, 0x01);//显示工位13得下划线
            break;
        case 13:bit_Cal(37, 0x01, 0x01);//显示工位14得下划线
            break;
        case 14:bit_Cal(34, 0x01, 0x01);//显示工位15得下划线
            break;
    }
    
    if(sys.Sync == 1)   
    {
        bit_Cal(2, 0x08, 0x08);//显示工位1得下划线
        bit_Cal(7, 0x08, 0x08);//显示工位2得下划线
        bit_Cal(12, 0x08, 0x08);//显示工位3得下划线
        bit_Cal(0, 0x40, 0x40);//显示工位4得下划线
        bit_Cal(7, 0x80, 0x80);//显示工位5得下划线
        bit_Cal(10, 0x40, 0x40);//显示工位6得下划线
        bit_Cal(36, 0x80, 0x80);//显示工位7得下划线
        bit_Cal(21, 0x80, 0x80);//显示工位8得下划线
        bit_Cal(22, 0x01, 0x01);//显示工位9得下划线
        bit_Cal(43, 0x10, 0x10);//显示工位10得下划线
        bit_Cal(39, 0x08, 0x08);//显示工位11得下划线
        bit_Cal(34, 0x10, 0x10);//显示工位12得下划线
        bit_Cal(43, 0x01, 0x01);//显示工位13得下划线
        bit_Cal(37, 0x01, 0x01);//显示工位14得下划线
        bit_Cal(34, 0x01, 0x01);//显示工位14得下划线
        if(Sync_ShowFlag)
        {
            switch(sys.New_Work)
            {
                case 0:bit_Cal(2, 0x08, 0x00);//显示工位1得下划线
                    break;
                case 1:bit_Cal(7, 0x08, 0x00);//显示工位2得下划线
                    break;
                case 2:bit_Cal(12, 0x08, 0x00);//显示工位3得下划线
                    break;
                case 3:bit_Cal(0, 0x40, 0x00);//显示工位4得下划线
                    break;
                case 4:bit_Cal(7, 0x80, 0x00);//显示工位5得下划线
                    break;
                case 5:bit_Cal(10, 0x40, 0x00);//显示工位6得下划线
                    break;
                case 6:bit_Cal(36, 0x80, 0x00);//显示工位7得下划线
                    break;
                case 7:bit_Cal(21, 0x80, 0x00);//显示工位8得下划线
                    break;
                case 8:bit_Cal(22, 0x01, 0x00);//显示工位9得下划线
                    break;
                case 9:bit_Cal(43, 0x10, 0x00);//显示工位10得下划线
                    break;
                case 10:bit_Cal(39, 0x08, 0x00);//显示工位11得下划线
                    break;
                case 11:bit_Cal(34, 0x10, 0x00);//显示工位12得下划线
                    break;
                case 12:bit_Cal(43, 0x01, 0x00);//显示工位13得下划线
                    break;
                case 13:bit_Cal(37, 0x01, 0x00);//显示工位14得下划线
                    break;
                case 14:bit_Cal(34, 0x01, 0x00);//显示工位15得下划线
                    break;
            }
        }
    }
    
    /* 1号工位转速图标 */
    if(work_num[sys.New_Work].Speed.Display_Rel)
    {
        switch(Work_Num[0].Speed.IconStep)
        {
            case 0: bit_Cal(15, 0x04, 0x04);//工位转速图标S48
                    bit_Cal(15, 0x08, 0x08);//工位转速图标S49
                    bit_Cal(16, 0x08, 0x08);//工位转速图标S50
                break;
            case 1: bit_Cal(15, 0x04, 0x00);//工位转速图标S48
                    bit_Cal(15, 0x08, 0x08);//工位转速图标S49
                    bit_Cal(16, 0x08, 0x08);//工位转速图标S50
                break;
            case 2: bit_Cal(15, 0x04, 0x04);//工位转速图标S48
                    bit_Cal(15, 0x08, 0x00);//工位转速图标S49
                    bit_Cal(16, 0x08, 0x08);//工位转速图标S50
                break;
            case 3: bit_Cal(15, 0x04, 0x04);//工位转速图标S48
                    bit_Cal(15, 0x08, 0x08);//工位转速图标S49
                    bit_Cal(16, 0x08, 0x00);//工位转速图标S50
                break;
            default:
                break;
        }
    }
    else
    {
        bit_Cal(15, 0x04, 0x04);//工位转速图标S48
        bit_Cal(15, 0x08, 0x08);//工位转速图标S49
        bit_Cal(16, 0x08, 0x08);//工位转速图标S50
    }
    
    /**********rpm图标**********/
    bit_Cal(17, 0x80, 0x80);

    
    /* 1号工位时间图标 */
    if(Work_Num[sys.New_Work].Time.Icon == 0)
    {
        bit_Cal(30, 0x08, 0x08);//工位时间图标
    }
    else
    {
        bit_Cal(30, 0x08, 0x00);//工位时间图标
    }
    
    /**********min图标**********/
    bit_Cal(24, 0x01, 0x01);

    /**********设定时间冒号图标**********/
    bit_Cal(28, 0x01, 0x01);

    /**********实际时间冒号图标**********/
    bit_Cal(28, 0x80, 0x80);

    /**********数据发送**********/
   
    for(uint8_t i=0;i<46;i++)
    {
        Write_Addr_Dat_N(2+i, seg[i], 1);
    }
}

/*
*****************************************************************
 * 函数原型：void Deal_Speed(float dT)
 * 功    能：速度显示处理
*****************************************************************
*/
void Deal_Speed(uint8_t i)
{
    if(Work_Num[i].Run_Status)
    {
        if(Work_Num[i].Speed.Ctrl)
        {
            if(Work_Num[i].Speed.ADDMode==0)//在电机控制中，速度未处理
            { 
                if(Work_Num[i].Speed.Ctrl >= Work_Num[i].Speed.Display_Rel)//控制速度大于实际速度
                {
                    Work_Num[i].Speed.ADDMode = 1;//进入加速模式下
                }
                else if(Work_Num[i].Speed.Ctrl < Work_Num[i].Speed.Display_Rel)//控制速度小于实际速度
                {
                    Work_Num[i].Speed.ADDMode = 2;//进入减速模式下
                }
            }
            if(Work_Num[i].Speed.ADDMode==1)//在进入加速模式下
            {
                if(Work_Num[i].Speed.Rel > Work_Num[i].Speed.Display_Rel)//当前速度大于显示速度
                {
                        Work_Num[i].Speed.Display_Rel = Work_Num[i].Speed.Rel;//显示当前速度
                }
                else//当前速度小于上一次速度
                {
                    Work_Num[i].Speed.Display_Rel = Work_Num[i].Speed.Display_Rel;//显示上一次速度，不让速度小于当前速度。呈现攀升速度的现象
                }  
                if(Work_Num[i].Motor_Stop == 0)
                {
                    if(Work_Num[i].Speed.Display_Rel >= Work_Num[i].Speed.Ctrl)//实际速度大于等于控制速度
                    {
                        Work_Num[i].Speed.ADDMode = 3;//进入稳定模式
                        return;
                    }
                }
            }
            if(Work_Num[i].Speed.ADDMode == 2)//速度下降模式下
            {
                if(Work_Num[i].Speed.Rel < Work_Num[i].Speed.Display_Rel)//当前速度小于上一次速度
                {
                        Work_Num[i].Speed.Display_Rel = Work_Num[i].Speed.Rel;//显示当前速度
                }
                else//当前速度大于上一次速度
                {
                    Work_Num[i].Speed.Display_Rel = Work_Num[i].Speed.Display_Rel;//显示上一次速度，不让速度大于当前速度。呈现下降速度的现象
                }
                if(Work_Num[i].Motor_Stop == 0)
                {
                    if(Work_Num[i].Speed.Display_Rel <= Work_Num[i].Speed.Ctrl)//实际速度小于等于控制速度
                    {
                        Work_Num[i].Speed.ADDMode = 3;//进入稳定模式
                        return;
                    }
                }
            }
            else if(Work_Num[i].Speed.ADDMode == 3)//速度稳定模式下
            {
                Work_Num[i].Speed.Display_Rel = Work_Num[i].Speed.Ctrl;//显示控制速度
            }
        }
        else
        {
            if(Work_Num[i].Speed.Rel < Work_Num[i].Speed.Display_Rel)//当前速度小于上一次速度
            {
                    Work_Num[i].Speed.Display_Rel = Work_Num[i].Speed.Rel;//显示当前速度
            }
            else//当前速度大于上一次速度
            {
                Work_Num[i].Speed.Display_Rel = Work_Num[i].Speed.Display_Rel;//显示上一次速度，不让速度大于当前速度。呈现下降速度的现象
            }
        }
    }
    else
    {
        Work_Num[i].Speed.Display_Rel = 0;//实际速度显示为零
        Work_Num[i].Speed.ADDMode = 0;//清除显示处理
    }
}

/**
 * @brief 显示屏幕内容
 *
 */
void Show_Display(void)
{
    for(uint8_t i = 0;i<15;i++)
    {
        Work_Num[i].Speed.Display_Set = Work_Num[i].Speed.Set;
        Deal_Speed(i);
        Work_Num[i].Time.Display_Set = Work_Num[i].Time.Set;
        Work_Num[i].Time.Display_Rel = Work_Num[i].Time.Rel + 59;
    }
    Display(Work_Num);
}
