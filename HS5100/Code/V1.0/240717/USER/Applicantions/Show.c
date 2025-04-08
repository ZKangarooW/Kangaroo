#include "Show.h"

/**********全局变量声明******/
float Speed_Twinkle_Time,Temp_Twinkle_Time,Time_Twinkle_Time;//速度闪烁时间、温度闪烁时间和时间闪烁时间

/**********局部变量声明******/
uint8_t Tab[] = {0xFA,0x0A,0xD6,0x9E,0x2E,0xBC,0xFC,0x1A,0xFE,0xBE};//0·9
uint8_t Temp_ShowFlag,Speed_ShowFlag,Time_ShowFlag;//温度、速度、时间显示的标志位 0:常亮 1：熄灭
uint8_t TempIcn_ShowFlag,TimeIcn_ShowFlag,SpeedIcn_ShowFlag,Lock_ShowFlag;//加热图标闪烁和时间图标闪烁和速度图标闪烁

/*
*****************************************************************
 * 函数原型：void Twinkle(float dT)
 * 功    能：闪烁函数
*****************************************************************
*/
void Twinkle(float dT)
{
//	Check_ShowFlag(dT);//闪烁检测
//    Check_Lock(dT);//锁定误触图标闪烁检测
//	Icn_Twinkle(dT);//图标闪烁
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
    if (Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = Temp.Display_Rel / 1000 % 10;
    }
    else if (Temp.Display_Rel < 0 && Temp.Display_Rel > -100)
    {
        Val = ABS(Temp.Display_Rel) / 1000 % 10;//计算后是0，不大于999所以不会显示
    }
    else if (Temp.Display_Rel <= -100 && Temp.Display_Rel > -1000)
    {
        Val = 10;//显示“-”
    }
    switch (Val)
    {
        case 0:
            if (Temp.Display_Rel > 999)//显示0
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
    if (Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = Temp.Display_Rel / 100 % 10;
    }
    else if (Temp.Display_Rel < 0 && Temp.Display_Rel > -100)
    {
        Val = 10;//显示“-”
    }
    else if (Temp.Display_Rel <= -100 && Temp.Display_Rel > -1000)
    {
        Val = ABS(Temp.Display_Rel)/ 100 % 10;
    }
    switch (Val)
    {
        case 0:
            if (Temp.Display_Rel > 99)//显示零
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
    if (Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = Temp.Display_Rel / 10 % 10;
    }
    else if (Temp.Display_Rel < 0 && Temp.Display_Rel > -100)
    {
        Val = ABS(Temp.Display_Rel) / 10 % 10;
    }
    else if (Temp.Display_Rel <= -100 && Temp.Display_Rel > -1000)
    {
        Val = ABS(Temp.Display_Rel) / 10 % 10;
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
    
    if (Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = Temp.Display_Rel % 10;
    }
    else if (Temp.Display_Rel < 0 && Temp.Display_Rel > -100)
    {
        Val = ABS(Temp.Display_Rel) % 10;
    }
    else if (Temp.Display_Rel <= -100 && Temp.Display_Rel > -1000)
    {
        Val = ABS(Temp.Display_Rel) % 10;
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
     if (Temp.Display_Set >= 0)//大于等于0时
    {
        Val = Temp.Display_Set / 1000 % 10;
    }
    else if (Temp.Display_Set < 0 && Temp.Display_Set > -100)
    {
        Val = ABS(Temp.Display_Set) / 1000 % 10;//计算后是0，不大于999所以不会显示
    }
    else if (Temp.Display_Set <= -100 && Temp.Display_Set > -1000)
    {
        Val = 10;//显示“-”
    }
    switch (Val)
    {
        case 0:
            if (Temp.Display_Set > 999)//显示零
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
    
    if (Temp.Display_Set >= 0)//大于等于0时
    {
        Val = Temp.Display_Set / 100 % 10;
    }
    else if (Temp.Display_Set < 0 && Temp.Display_Set > -100)
    {
        Val = 10;//显示“-”
    }
    else if (Temp.Display_Set <= -100 && Temp.Display_Set > -1000)
    {
        Val = ABS(Temp.Display_Set)/ 100 % 10;
    }
    switch (Val)
    {
        case 0:
            if (Temp.Display_Set > 99)//显示零
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
    
    if (Temp.Display_Set >= 0)//大于等于0时
    {
        Val = Temp.Display_Set / 10 % 10;
    }
    else if (Temp.Display_Set < 0 && Temp.Display_Set > -100)
    {
        Val = ABS(Temp.Display_Set) / 10 % 10;
    }
    else if (Temp.Display_Set <= -100 && Temp.Display_Set > -1000)
    {
        Val = ABS(Temp.Display_Set) / 10 % 10;
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
    
    if (Temp.Display_Set >= 0)//大于等于0时
    {
        Val = Temp.Display_Set % 10;
    }
    else if (Temp.Display_Set < 0 && Temp.Display_Set > -100)
    {
        Val = ABS(Temp.Display_Set) % 10;
    }
    else if (Temp.Display_Set <= -100 && Temp.Display_Set > -1000)
    {
        Val = ABS(Temp.Display_Set) % 10;
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
    
    /**********时间显示**********/
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
    
    /**********实际温度小数点**********/
    bit_Cal(5, 0x01, 0x01);
    
    /**********设定温度小数点**********/
    bit_Cal(5, 0x80, 0x80);
    
    /**********'SAFE'图标**********/
    bit_Cal(1, 0x80, 0x80);
    
    /**********外部探头图标**********/
    bit_Cal(7, 0x01, 0x01);
    
    /**********‘℃’图标**********/
    bit_Cal(7, 0x80, 0x80);
    
    /**********时间冒号图标**********/
    bit_Cal(8, 0x01, 0x01);
    
    /**********加热图标**********/
    bit_Cal(8, 0x02, 0x02);
    bit_Cal(3, 0x01, 0x01);//加热图标下面的横杠
    
    /**********加热图标旁边的H**********/
    bit_Cal(8, 0x04, 0x04);
    
    /**********华氏度℉**********/
    bit_Cal(8, 0x08, 0x08);
    
    /**********转速图标搅拌子**********/
    bit_Cal(9, 0x01, 0x01);
    
    /**********加热图标旁边的L**********/
    bit_Cal(9, 0x02, 0x02);
    
    /**********锁定图标**********/
    bit_Cal(9, 0x04, 0x04);
    
    /**********转速图标旁边的H**********/
    bit_Cal(9, 0x08, 0x08);
    
    /**********转速图标S4**********/
    bit_Cal(10, 0x01, 0x01);
    
    /**********转速图标S3**********/
    bit_Cal(10, 0x02, 0x02);
    
    /**********转速图标S5**********/
    bit_Cal(12, 0x01, 0x01);
    
    /**********‘sec’图标**********/
    bit_Cal(10, 0x04, 0x04);
    
    /**********‘min’图标**********/
    bit_Cal(10, 0x08, 0x08);
    
    /**********‘rpm’图标**********/
    bit_Cal(14, 0x80, 0x80);
    
    /**********转速图标旁边的L**********/
    bit_Cal(17, 0x01, 0x01);
    
    /**********时间图标**********/
    bit_Cal(19, 0x80, 0x80);
    
    /**********L1**********/
    bit_Cal(26, 0x10, 0x10);
    
    /**********L2**********/
    bit_Cal(23, 0x08, 0x08);
    
    /**********L3**********/
    bit_Cal(19, 0x08, 0x08);
    
    /**********L4**********/
    bit_Cal(19, 0x10, 0x10);
    
    /**********L5**********/
    bit_Cal(19, 0x20, 0x20);
    
    /**********L6**********/
    bit_Cal(19, 0x40, 0x40);
    
    /**********L7**********/
    bit_Cal(20, 0x80, 0x80);
    
    /**********L8**********/
    bit_Cal(22, 0x80, 0x80);
    
    /**********L9**********/
    bit_Cal(24, 0x80, 0x80);
    
    /**********L10**********/
    bit_Cal(26, 0x80, 0x80);
    
    /**********L11**********/
    bit_Cal(26, 0x40, 0x40);
    
    /**********L12**********/
    bit_Cal(26, 0x20, 0x20);
    
    /**********‘P’**********/
    bit_Cal(25, 0xF0, 0x70);bit_Cal(24, 0x70, 0x30);
    /**********‘-’**********/
    bit_Cal(23, 0xF0, 0x00);bit_Cal(22, 0x70, 0x20);
    
    switch (Val)
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
    
	/**********数据发送**********/
    for(uint8_t i=0;i<27;i++)
    {
        Write_Addr_Dat_N(i*2, seg[i], 1);
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
    Time.Display = 60;
    Speed.Display_Set = 8888;
    Speed.Display_Rel = 50;
    Temp.Display_Rel = 8888;
    Temp.Display_Set = 8888;
    Display();
}
