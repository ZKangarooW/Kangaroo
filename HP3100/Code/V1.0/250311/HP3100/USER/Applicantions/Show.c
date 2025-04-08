#include "Show.h"

/**********全局变量声明******/
float Twinkle_Time;//闪烁时间

/**********局部变量声明******/
uint8_t Temp_ShowFlag,Time_ShowFlag,Pmode_ShowFlag;//温度、时间、P模式显示的标志位 0:常亮 1：熄灭
uint8_t TempIcn_ShowFlag,TimeIcn_ShowFlag,Lock_ShowFlag;//加热图标闪烁和时间图标、锁定图标闪烁

/*
*****************************************************************
 * 函数原型：static void Icn_Twinkle(float dT)
 * 功    能：图标闪烁
 * 调    用：内部调用
*****************************************************************
*/
static void Icn_Twinkle(float dT)
{
	
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
	
}

/*
*****************************************************************
 * 函数原型：void Twinkle(float dT)
 * 功    能：闪烁函数
*****************************************************************
*/
void Twinkle(float dT)
{
	
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
    if(sys.Lock && !Lock_ShowFlag)
    {
        bit_Cal(18, 0x80, 0x80);//锁定
    }
    else
    {
        bit_Cal(18, 0x80, 0x00);//不显示锁定
    }
    
    /**********‘HOT’图标**********/
    bit_Cal(5, 0x80, 0x80);//HOT
    bit_Cal(4, 0x80, 0x80);//！
    
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
    
    /**********数据发送**********/
    for(uint8_t i=0;i<20;i++)
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
//    Temp.Display_Rel = CelsiusToFahrenheit(Temp.Unit,Temp_Rel);
//    Temp.Display_Set = CelsiusToFahrenheit(Temp.Unit,Temp_Set);
    Temp.Display_Rel = Temp.Rel;
    Temp.Display_Set = Temp.Set;
    Time.Display_Rel = Time.Rel;
    Time.Display_Set = Time.Set;
    Display(Temp.Display_Set,Temp.Display_Rel,Time.Display_Set,Time.Display_Rel,PMode.Option);
}
