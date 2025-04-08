#include "Show.h"

/**********全局变量声明******/
float Pmode_Twinkle_Time,Speed_Twinkle_Time,Temp_Twinkle_Time,Time_Twinkle_Time;//速度闪烁时间、温度闪烁时间和时间闪烁时间

/**********局部变量声明******/
uint8_t Pmode_ShowFlag,Temp_ShowFlag,Speed_ShowFlag,Time_ShowFlag;//温度、速度、时间显示的标志位 0:常亮 1：熄灭
uint8_t TempIcn_ShowFlag,TimeIcn_ShowFlag,SpeedIcn_ShowFlag;//加热图标闪烁和时间图标闪烁和速度图标闪烁


/*
*****************************************************************
 * 函数原型：void Twinkle(float dT)
 * 功    能：闪烁函数
*****************************************************************
*/
void Twinkle(float dT)
{
	
}

uint8_t seg[21] = {0};

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
void Display(int16_t dis_rel_temp,int16_t dis_set_temp,uint16_t dis_speed,uint32_t dis_time)
{
    uint8_t Val;// 用于百十个取出来的数字
    
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
            bit_Cal(4, 0x0F, 0x0F);bit_Cal(5, 0x07, 0x05);
            break;
        case 1:
            bit_Cal(4, 0x0F, 0x00);bit_Cal(5, 0x07, 0x05);
            break;
        case 2:
            bit_Cal(4, 0x0F, 0x0D);bit_Cal(5, 0x07, 0x03);
            break;
        case 3:
            bit_Cal(4, 0x0F, 0x09);bit_Cal(5, 0x07, 0x07);
            break;
        case 4:
            bit_Cal(4, 0x0F, 0x02);bit_Cal(5, 0x07, 0x07);
            break;
        case 5:
            bit_Cal(4, 0x0F, 0x0B);bit_Cal(5, 0x07, 0x06);
            break;
        case 6:
            bit_Cal(4, 0x0F, 0x0F);bit_Cal(5, 0x07, 0x06);
            break;
        case 7:
            bit_Cal(4, 0x0F, 0x01);bit_Cal(5, 0x07, 0x05);
            break;
        case 8:
            bit_Cal(4, 0x0F, 0x0F);bit_Cal(5, 0x07, 0x07);
            break;
        case 9:
            bit_Cal(4, 0x0F, 0x0B);bit_Cal(5, 0x07, 0x07);
            break;
        default:
            bit_Cal(4, 0x0F, 0x00);bit_Cal(5, 0x0E, 0x02);
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
            bit_Cal(6, 0x0F, 0x0F);bit_Cal(7, 0x07, 0x05);
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
            bit_Cal(6, 0x0F, 0x00);bit_Cal(7, 0x0E, 0x02);
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
        if(dis_set_temp == 0)
        {
            bit_Cal(0, 0xF0, 0x00);bit_Cal(1, 0x70, 0x20);//显示“-”
            bit_Cal(2, 0xF0, 0x00);bit_Cal(3, 0x70, 0x20);//显示“-”
            bit_Cal(4, 0xF0, 0x00);bit_Cal(5, 0x70, 0x20);//显示“-”
            bit_Cal(6, 0xF0, 0x00);bit_Cal(7, 0x70, 0x40);//显示“-”
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
                    bit_Cal(6, 0xF0, 0xF0);bit_Cal(7, 0xE0, 0xA0);
                    break;
                case 1:
                    bit_Cal(6, 0xF0, 0x00);bit_Cal(7, 0xE0, 0xA0);
                    break;
                case 2:
                    bit_Cal(6, 0xF0, 0xD0);bit_Cal(7, 0xE0, 0x60);
                    break;
                case 3:
                    bit_Cal(6, 0xF0, 0x90);bit_Cal(7, 0xE0, 0xE0);
                    break;
                case 4:
                    bit_Cal(6, 0xF0, 0x20);bit_Cal(7, 0xE0, 0xE0);
                    break;
                case 5:
                    bit_Cal(6, 0xF0, 0xB0);bit_Cal(7, 0xE0, 0xC0);
                    break;
                case 6:
                    bit_Cal(6, 0xF0, 0xF0);bit_Cal(7, 0xE0, 0xC0);
                    break;
                case 7:
                    bit_Cal(6, 0xF0, 0x10);bit_Cal(7, 0xE0, 0xA0);
                    break;
                case 8:
                    bit_Cal(6, 0xF0, 0xF0);bit_Cal(7, 0xE0, 0xE0);
                    break;
                case 9:
                    bit_Cal(6, 0xF0, 0xB0);bit_Cal(7, 0xE0, 0xE0);
                    break;
                default:
                    bit_Cal(6, 0xF0, 0x00);bit_Cal(7, 0xE0, 0x40);
                    break;
            }
        }
    }
    
    /**********转速显示**********/
    if(Speed_ShowFlag)
    {
        bit_Cal(15, 0xF0, 0x00);bit_Cal(14, 0x70, 0x00);//不显示
        bit_Cal(13, 0xF0, 0x00);bit_Cal(12, 0x70, 0x00);//不显示
        bit_Cal(11, 0xF0, 0x00);bit_Cal(10, 0x70, 0x00);//不显示
        bit_Cal(9, 0xF0, 0x00);bit_Cal(8, 0xE0, 0x00);//不显示
    }
    else
    {
        if(Speed.Set == 0)//不用那个是因为实际转速如果为0也会显示----
        {
            bit_Cal(15, 0xF0, 0x00);bit_Cal(14, 0x70, 0x20);//显示"-"
            bit_Cal(13, 0xF0, 0x00);bit_Cal(12, 0x70, 0x20);//显示"-"
            bit_Cal(11, 0xF0, 0x00);bit_Cal(10, 0x70, 0x20);//显示"-"
            bit_Cal(9, 0xF0, 0x00);bit_Cal(8, 0xE0, 0x40);//显示"-"
        }
        else
        {
            if (dis_speed > 999) // 大于999时
            {
                Val = dis_speed / 1000 % 10;
                switch (Val)
                {
                    case 0:
                        bit_Cal(15, 0xF0, 0xF0);bit_Cal(14, 0x70, 0x50);
                        break;
                    case 1:
                        bit_Cal(15, 0xF0, 0x00);bit_Cal(14, 0x70, 0x50);
                        break;
                    case 2:
                        bit_Cal(15, 0xF0, 0xB0);bit_Cal(14, 0x70, 0x60);
                        break;
                    case 3:
                        bit_Cal(15, 0xF0, 0x90);bit_Cal(14, 0x70, 0x70);
                        break;
                    case 4:
                        bit_Cal(15, 0xF0, 0x40);bit_Cal(14, 0x70, 0x70);
                        break;
                    case 5:
                        bit_Cal(15, 0xF0, 0xD0);bit_Cal(14, 0x70, 0x30);
                        break;
                    case 6:
                        bit_Cal(15, 0xF0, 0xF0);bit_Cal(14, 0x70, 0x30);
                        break;
                    case 7:
                        bit_Cal(15, 0xF0, 0x80);bit_Cal(14, 0x70, 0x50);
                        break;
                    case 8:
                        bit_Cal(15, 0xF0, 0xF0);bit_Cal(14, 0x70, 0x70);
                        break;
                    case 9:
                        bit_Cal(15, 0xF0, 0xD0);bit_Cal(14, 0x70, 0x70);
                        break;
                    default:
                        bit_Cal(15, 0xF0, 0x00);bit_Cal(14, 0x70, 0x20);
                        break;
                }
            }
            else
            {
                bit_Cal(15, 0xF0, 0xF0);bit_Cal(14, 0x70, 0x50);//显示数字0
            }
                
            if (dis_speed > 99) // 大于99时
            {
                Val = dis_speed / 100 % 10;
                switch (Val)
                {
                    case 0:
                        bit_Cal(13, 0xF0, 0xF0);bit_Cal(12, 0x70, 0x50);
                        break;
                    case 1:
                        bit_Cal(13, 0xF0, 0x00);bit_Cal(12, 0x70, 0x50);
                        break;
                    case 2:
                        bit_Cal(13, 0xF0, 0xB0);bit_Cal(12, 0x70, 0x60);
                        break;
                    case 3:
                        bit_Cal(13, 0xF0, 0x90);bit_Cal(12, 0x70, 0x70);
                        break;
                    case 4:
                        bit_Cal(13, 0xF0, 0x40);bit_Cal(12, 0x70, 0x70);
                        break;
                    case 5:
                        bit_Cal(13, 0xF0, 0xD0);bit_Cal(12, 0x70, 0x30);
                        break;
                    case 6:
                        bit_Cal(13, 0xF0, 0xF0);bit_Cal(12, 0x70, 0x30);
                        break;
                    case 7:
                        bit_Cal(13, 0xF0, 0x80);bit_Cal(12, 0x70, 0x50);
                        break;
                    case 8:
                        bit_Cal(13, 0xF0, 0xF0);bit_Cal(12, 0x70, 0x70);
                        break;
                    case 9:
                        bit_Cal(13, 0xF0, 0xD0);bit_Cal(12, 0x70, 0x70);
                        break;
                    default:
                        bit_Cal(13, 0xF0, 0x00);bit_Cal(12, 0x70, 0x20);
                        break;
                }
            }
            else
            {
                bit_Cal(13, 0xF0, 0xF0);bit_Cal(12, 0x70, 0x50);//显示数字零
            }
            
            if (dis_speed > 9) // 大于9时
            {
                Val = dis_speed / 10 % 10;
                switch (Val)
                {
                    case 0:
                        bit_Cal(11, 0xF0, 0xF0);bit_Cal(10, 0x70, 0x50);
                        break;
                    case 1:
                        bit_Cal(11, 0xF0, 0x00);bit_Cal(10, 0x70, 0x50);
                        break;
                    case 2:
                        bit_Cal(11, 0xF0, 0xB0);bit_Cal(10, 0x70, 0x60);
                        break;
                    case 3:
                        bit_Cal(11, 0xF0, 0x90);bit_Cal(10, 0x70, 0x70);
                        break;
                    case 4:
                        bit_Cal(11, 0xF0, 0x40);bit_Cal(10, 0x70, 0x70);
                        break;
                    case 5:
                        bit_Cal(11, 0xF0, 0xD0);bit_Cal(10, 0x70, 0x30);
                        break;
                    case 6:
                        bit_Cal(11, 0xF0, 0xF0);bit_Cal(10, 0x70, 0x30);
                        break;
                    case 7:
                        bit_Cal(11, 0xF0, 0x80);bit_Cal(10, 0x70, 0x50);
                        break;
                    case 8:
                        bit_Cal(11, 0xF0, 0xF0);bit_Cal(10, 0x70, 0x70);
                        break;
                    case 9:
                        bit_Cal(11, 0xF0, 0xD0);bit_Cal(10, 0x70, 0x70);
                        break;
                    default:
                        bit_Cal(11, 0xF0, 0x00);bit_Cal(10, 0x70, 0x20);
                        break;
                }
            }
            else
            {
                bit_Cal(11, 0xF0, 0xF0);bit_Cal(10, 0x70, 0x50);//显示数字零
            }
            
            Val = dis_speed % 10;
            switch (Val)
            {
                 case 0:
                    bit_Cal(9, 0xF0, 0xF0);bit_Cal(8, 0xE0, 0xA0);
                    break;
                case 1:
                    bit_Cal(9, 0xF0, 0x00);bit_Cal(8, 0xE0, 0xA0);
                    break;
                case 2:
                    bit_Cal(9, 0xF0, 0xB0);bit_Cal(8, 0xE0, 0xC0);
                    break;
                case 3:
                    bit_Cal(9, 0xF0, 0x90);bit_Cal(8, 0xE0, 0xE0);
                    break;
                case 4:
                    bit_Cal(9, 0xF0, 0x40);bit_Cal(8, 0xE0, 0xE0);
                    break;
                case 5:
                    bit_Cal(9, 0xF0, 0xD0);bit_Cal(8, 0xE0, 0x60);
                    break;
                case 6:
                    bit_Cal(9, 0xF0, 0xF0);bit_Cal(8, 0xE0, 0x60);
                    break;
                case 7:
                    bit_Cal(9, 0xF0, 0x80);bit_Cal(8, 0xE0, 0xA0);
                    break;
                case 8:
                    bit_Cal(9, 0xF0, 0xF0);bit_Cal(8, 0xE0, 0xE0);
                    break;
                case 9:
                    bit_Cal(9, 0xF0, 0xD0);bit_Cal(8, 0xE0, 0xE0);
                    break;
                default:
                    bit_Cal(9, 0xF0, 0x00);bit_Cal(8, 0xE0, 0x40);
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
                bit_Cal(15, 0x0F, 0x00);bit_Cal(14, 0x0E, 0x04);//显示"-"
                bit_Cal(13, 0x0F, 0x00);bit_Cal(12, 0x0E, 0x04);//显示"-"
                bit_Cal(11, 0x0F, 0x00);bit_Cal(10, 0x0E, 0x04);//显示"-"
                bit_Cal(9, 0x0F, 0x00);bit_Cal(8, 0x0E, 0x04);//显示"-"
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
                        bit_Cal(15, 0x0F, 0x0F);bit_Cal(14, 0x0E, 0x0A);
                        break;
                    case 1:
                        bit_Cal(15, 0x0F, 0x00);bit_Cal(14, 0x0E, 0x0A);
                        break;
                    case 2:
                        bit_Cal(15, 0x0F, 0x0B);bit_Cal(14, 0x0E, 0x0C);
                        break;
                    case 3:
                        bit_Cal(15, 0x0F, 0x09);bit_Cal(14, 0x0E, 0x0E);
                        break;
                    case 4:
                        bit_Cal(15, 0x0F, 0x04);bit_Cal(14, 0x0E, 0x0E);
                        break;
                    case 5:
                        bit_Cal(15, 0x0F, 0x0D);bit_Cal(14, 0x0E, 0x06);
                        break;
                    case 6:
                        bit_Cal(15, 0x0F, 0x0F);bit_Cal(14, 0x0E, 0x06);
                        break;
                    case 7:
                        bit_Cal(15, 0x0F, 0x08);bit_Cal(14, 0x0E, 0x0A);
                        break;
                    case 8:
                        bit_Cal(15, 0x0F, 0x0F);bit_Cal(14, 0x0E, 0x0E);
                        break;
                    case 9:
                        bit_Cal(15, 0x0F, 0x0D);bit_Cal(14, 0x0E, 0x0E);
                        break;
                    default:
                        bit_Cal(15, 0x0F, 0x00);bit_Cal(14, 0x0E, 0x04);
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
                        bit_Cal(13, 0x0F, 0x0F);bit_Cal(12, 0x0E, 0x0A);
                        break;
                    case 1:
                        bit_Cal(13, 0x0F, 0x00);bit_Cal(12, 0x0E, 0x0A);
                        break;
                    case 2:
                        bit_Cal(13, 0x0F, 0x0B);bit_Cal(12, 0x0E, 0x0C);
                        break;
                    case 3:
                        bit_Cal(13, 0x0F, 0x09);bit_Cal(12, 0x0E, 0x0E);
                        break;
                    case 4:
                        bit_Cal(13, 0x0F, 0x04);bit_Cal(12, 0x0E, 0x0E);
                        break;
                    case 5:
                        bit_Cal(13, 0x0F, 0x0D);bit_Cal(12, 0x0E, 0x06);
                        break;
                    case 6:
                        bit_Cal(13, 0x0F, 0x0F);bit_Cal(12, 0x0E, 0x06);
                        break;
                    case 7:
                        bit_Cal(13, 0x0F, 0x08);bit_Cal(12, 0x0E, 0x0A);
                        break;
                    case 8:
                        bit_Cal(13, 0x0F, 0x0F);bit_Cal(12, 0x0E, 0x0E);
                        break;
                    case 9:
                        bit_Cal(13, 0x0F, 0x0D);bit_Cal(12, 0x0E, 0x0E);
                        break;
                    default:
                        bit_Cal(13, 0x0F, 0x00);bit_Cal(12, 0x0E, 0x04);
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
                        bit_Cal(11, 0x0F, 0x0F);bit_Cal(10, 0x0E, 0x0A);
                        break;
                    case 1:
                        bit_Cal(11, 0x0F, 0x00);bit_Cal(10, 0x0E, 0x0A);
                        break;
                    case 2:
                        bit_Cal(11, 0x0F, 0x0B);bit_Cal(10, 0x0E, 0x0C);
                        break;
                    case 3:
                        bit_Cal(11, 0x0F, 0x09);bit_Cal(10, 0x0E, 0x0E);
                        break;
                    case 4:
                        bit_Cal(11, 0x0F, 0x04);bit_Cal(10, 0x0E, 0x0E);
                        break;
                    case 5:
                        bit_Cal(11, 0x0F, 0x0D);bit_Cal(10, 0x0E, 0x06);
                        break;
                    case 6:
                        bit_Cal(11, 0x0F, 0x0F);bit_Cal(10, 0x0E, 0x06);
                        break;
                    case 7:
                        bit_Cal(11, 0x0F, 0x08);bit_Cal(10, 0x0E, 0x0A);
                        break;
                    case 8:
                        bit_Cal(11, 0x0F, 0x0F);bit_Cal(10, 0x0E, 0x0E);
                        break;
                    case 9:
                        bit_Cal(11, 0x0F, 0x0D);bit_Cal(10, 0x0E, 0x0E);
                        break;
                    default:
                        bit_Cal(11, 0x0F, 0x00);bit_Cal(10, 0x0E, 0x04);
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
                        bit_Cal(9, 0x0F, 0x0F);bit_Cal(8, 0x0E, 0x0A);
                        break;
                    case 1:
                        bit_Cal(9, 0x0F, 0x00);bit_Cal(8, 0x0E, 0x0A);
                        break;
                    case 2:
                        bit_Cal(9, 0x0F, 0x0B);bit_Cal(8, 0x0E, 0x0C);
                        break;
                    case 3:
                        bit_Cal(9, 0x0F, 0x09);bit_Cal(8, 0x0E, 0x0E);
                        break;
                    case 4:
                        bit_Cal(9, 0x0F, 0x04);bit_Cal(8, 0x0E, 0x0E);
                        break;
                    case 5:
                        bit_Cal(9, 0x0F, 0x0D);bit_Cal(8, 0x0E, 0x06);
                        break;
                    case 6:
                        bit_Cal(9, 0x0F, 0x0F);bit_Cal(8, 0x0E, 0x06);
                        break;
                    case 7:
                        bit_Cal(9, 0x0F, 0x08);bit_Cal(8, 0x0E, 0x0A);
                        break;
                    case 8:
                        bit_Cal(9, 0x0F, 0x0F);bit_Cal(8, 0x0E, 0x0E);
                        break;
                    case 9:
                        bit_Cal(9, 0x0F, 0x0D);bit_Cal(8, 0x0E, 0x0E);
                        break;
                    default:
                        bit_Cal(9, 0x0F, 0x00);bit_Cal(8, 0x0E, 0x04);
                        break;
                }
            }
        }
        else//不显示时间
        {
            bit_Cal(15, 0x0F, 0x00);bit_Cal(14, 0x0E, 0x00);
            bit_Cal(13, 0x0F, 0x00);bit_Cal(12, 0x0E, 0x00);
            bit_Cal(11, 0x0F, 0x00);bit_Cal(10, 0x0E, 0x00);
            bit_Cal(9, 0x0F, 0x00);bit_Cal(8, 0x0E, 0x00);
        }
        
        /**********时间冒号图标**********/
        bit_Cal(12, 0x01, 0x01);

        /**********时间图标**********/
        if(TimeIcn_ShowFlag == 0)
        {
            bit_Cal(16, 0x80, 0x80);//时间图标
        }
        else
        {
            bit_Cal(16, 0x80, 0x00);//不显示时间图标
        }
        
        if(dis_time < 3600)
        {
            /**********‘sec’图标**********/
            bit_Cal(8, 0x10, 0x10);
            /**********‘min’图标**********/
            bit_Cal(8, 0x01, 0x00);
        }
        else
        {
            /**********‘sec’图标**********/
            bit_Cal(8, 0x10, 0x00);
            /**********‘min’图标**********/
            bit_Cal(8, 0x01, 0x01);
        }
    }
    else//不显示时间
    {
        bit_Cal(15, 0x0F, 0x00);bit_Cal(14, 0x0E, 0x00);
        bit_Cal(13, 0x0F, 0x00);bit_Cal(12, 0x0E, 0x00);
        bit_Cal(11, 0x0F, 0x00);bit_Cal(10, 0x0E, 0x00);
        bit_Cal(9, 0x0F, 0x00);bit_Cal(8, 0x0E, 0x00);
        /**********时间冒号图标**********/
        bit_Cal(12, 0x01, 0x00);//不显示
        /**********时间图标**********/
        bit_Cal(16, 0x80, 0x00);//不显示
        /**********‘sec’图标**********/
        bit_Cal(8, 0x10, 0x00);//不显示
        /**********‘min’图标**********/
        bit_Cal(8, 0x01, 0x00);//不显示
    }
    
    /**********实际温度小数点**********/
    bit_Cal(5, 0x08, 0x08);
    
    /**********设定温度小数点**********/
    bit_Cal(5, 0x80, 0x80);
    
    /*************加热图标***************/
    if(TempIcn_ShowFlag == 0)
    {
        /**********加热图标**********/
        bit_Cal(1, 0x80, 0x80);
        bit_Cal(1, 0x01, 0x01);//加热图标下面的横杠
    }
    else
    {
        /**********不显示加热图标**********/
        bit_Cal(1, 0x80, 0x00);
        bit_Cal(1, 0x01, 0x00);//加热图标下面的横杠
    }	  
        
    if(Temp.Unit)
    {
        /**********实际温度华氏度℉**********/
        bit_Cal(7, 0x08, 0x08);
        /**********设定温度华氏度℉**********/
        bit_Cal(3, 0x80, 0x80);
        /**********实际温度‘℃’图标**********/
        bit_Cal(3, 0x01, 0x00);
        /**********设定温度‘℃’图标**********/
        bit_Cal(7, 0x10, 0x00);
    }
    else
    {
        /**********实际温度华氏度℉**********/
        bit_Cal(7, 0x08, 0x00);
        /**********设定温度华氏度℉**********/
        bit_Cal(3, 0x80, 0x00);
        /**********实际温度‘℃’图标**********/
        bit_Cal(3, 0x01, 0x01);
        /**********设定温度‘℃’图标**********/
        bit_Cal(7, 0x10, 0x10);
    }
    
    /**********“SAFE“图标**********/
    bit_Cal(20, 0x01, 0x01);
    
    /**********转速图标**********/
    switch(SpeedIcn_ShowFlag)
    {
        case 0: bit_Cal(12, 0x80, 0x80);//S16
                bit_Cal(14, 0x80, 0x80);//S15
                bit_Cal(14, 0x01, 0x01);//S14
            break;
        case 1: bit_Cal(12, 0x80, 0x00);//S16
                bit_Cal(14, 0x80, 0x80);//S15
                bit_Cal(14, 0x01, 0x01);//S14
            break;
        case 2: bit_Cal(12, 0x80, 0x80);//S16
                bit_Cal(14, 0x80, 0x00);//S15
                bit_Cal(14, 0x01, 0x01);//S14
            break;
        case 3: bit_Cal(12, 0x80, 0x80);//S16
                bit_Cal(14, 0x80, 0x80);//S15
                bit_Cal(14, 0x01, 0x00);//S14
            break;
        default:
            break;
    }
    
    /**********‘rpm’图标**********/
    bit_Cal(10, 0x80, 0x80);
        
    /**********一键煮沸图标**********/
    bit_Cal(10, 0x01, 0x01);
    
    /**********L1**********/
    if(PMode.Light_BIT & BIT0)
    {
        bit_Cal(16, 0x20, 0x20);
    }
    else
    {
        bit_Cal(16, 0x20, 0x00);
    }
    
    /**********L2**********/
    if(PMode.Light_BIT & BIT1)
    {
        bit_Cal(16, 0x10, 0x10);
    }
    else
    {
        bit_Cal(16, 0x10, 0x00);
    }
    
    /**********L3**********/
    if(PMode.Light_BIT & BIT2)
    {
        bit_Cal(18, 0x10, 0x10);
    }
    else
    {
        bit_Cal(18, 0x10, 0x00);
    }
    
    /**********L4**********/
    if(PMode.Light_BIT & BIT3)
    {
        bit_Cal(16, 0x08, 0x08);
    }
    else
    {
        bit_Cal(16, 0x08, 0x00);
    }
    
    /**********L5**********/
    if(PMode.Light_BIT & BIT4)
    {
        bit_Cal(16, 0x04, 0x04);
    }
    else
    {
        bit_Cal(16, 0x04, 0x00);
    }
    
    /**********L6**********/
    if(PMode.Light_BIT & BIT5)
    {
        bit_Cal(16, 0x02, 0x02);
    }
    else
    {
        bit_Cal(16, 0x02, 0x00);
    }
    
    /**********L7**********/
    if(PMode.Light_BIT & BIT6)
    {
        bit_Cal(16, 0x01, 0x01);
    }
    else
    {
        bit_Cal(16, 0x01, 0x00);
    }
    
    /**********L8**********/
    if(PMode.Light_BIT & BIT7)
    {
        bit_Cal(17, 0x01, 0x01);
    }
    else
    {
        bit_Cal(17, 0x01, 0x00);
    }
    
    /**********L9**********/
    if(PMode.Light_BIT & BIT8)
    {
        bit_Cal(19, 0x01, 0x01);
    }
    else
    {
        bit_Cal(19, 0x01, 0x00);
    }
    
    /**********L10**********/
    if(PMode.Light_BIT & BIT9)
    {
        bit_Cal(20, 0x80, 0x80);
    }
    else
    {
        bit_Cal(20, 0x80, 0x00);
    }
    
    /**********L11**********/
    if(PMode.Light_BIT & BIT10)
    {
        bit_Cal(20, 0x40, 0x40);
    }
    else
    {
        bit_Cal(20, 0x40, 0x00);
    }
    
    /**********L12**********/
    if(PMode.Light_BIT & BIT11)
    {
        bit_Cal(16, 0x40, 0x40);
    }
    else
    {
        bit_Cal(16, 0x40, 0x00);
    }
    
    /**********‘P’**********/
    if (PMode.Status) // 进入PMode
    {
        if (!PMode.Mode) // 在P模式下
        {
            if (!Pmode_ShowFlag)
            {
                bit_Cal(17, 0xF0, 0x70);bit_Cal(18, 0xE0, 0x60);//P
                /**********‘-’**********/
                bit_Cal(19, 0xFE, 0x04);
                switch (PMode.Option)
                {
                    case 0:
                        bit_Cal(18, 0x0F, 0x0F);bit_Cal(17, 0x0E, 0x0A);
                        break;
                    case 1:
                        bit_Cal(18, 0x0F, 0x00);bit_Cal(17, 0x0E, 0x0A);
                        break;
                    case 2:
                        bit_Cal(18, 0x0F, 0x0B);bit_Cal(17, 0x0E, 0x0C);
                        break;
                    case 3:
                        bit_Cal(18, 0x0F, 0x09);bit_Cal(17, 0x0E, 0x0E);
                        break;
                    case 4:
                        bit_Cal(18, 0x0F, 0x04);bit_Cal(17, 0x0E, 0x0E);
                        break;
                    case 5:
                        bit_Cal(18, 0x0F, 0x0D);bit_Cal(17, 0x0E, 0x06);
                        break;
                    case 6:
                        bit_Cal(18, 0x0F, 0x0F);bit_Cal(17, 0x0E, 0x06);
                        break;
                    case 7:
                        bit_Cal(18, 0x0F, 0x08);bit_Cal(17, 0x0E, 0x0A);
                        break;
                    case 8:
                        bit_Cal(18, 0x0F, 0x0F);bit_Cal(17, 0x0E, 0x0E);
                        break;
                    case 9:
                        bit_Cal(18, 0x0F, 0x0D);bit_Cal(17, 0x0E, 0x0E);
                        break;
                    default:
                        bit_Cal(18, 0x0F, 0x00);bit_Cal(17, 0x0E, 0x04);
                        break;
                }
            }
            else
            {
                bit_Cal(17, 0xF0, 0x00);bit_Cal(18, 0xE0, 0x00);//不显示
                bit_Cal(19, 0xFE, 0x00);//不显示
                bit_Cal(18, 0x0F, 0x00);bit_Cal(17, 0x0E, 0x00);//不显示
            }
        }
    }
    else // 不进入P模式不显示
    {
        bit_Cal(17, 0xF0, 0x00);bit_Cal(18, 0xE0, 0x00);//不显示
        bit_Cal(19, 0xFE, 0x00);//不显示
        bit_Cal(18, 0x0F, 0x00);bit_Cal(17, 0x0E, 0x00);//不显示
    }
        
    /**********数据发送**********/
    for(uint8_t i=0;i<27;i++)
    {
        Write_Addr_Dat_N(i*2, seg[i], 1);
    } 
}

/**
 * @brief 显示屏幕内容
 * 
 */
void Show_Display(void)
{
    Display(1234,5678,3456,3660);
}
