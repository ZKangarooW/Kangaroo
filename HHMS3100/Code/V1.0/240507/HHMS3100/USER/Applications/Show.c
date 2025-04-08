#include "Show.h"

/**********全局变量**********/
float Twinkle_Time; // 闪烁时间

/**********局部变量声明*******/
uint8_t Pmode_ShowFlag, Temp_ShowFlag, Speed_ShowFlag, Time_ShowFlag;                      // P模式、时间、速度、温度显示的标志位，0：常亮，1：熄灭
uint8_t PModeP1_ShowFlag, PModeP2_ShowFlag;                                                // P1，P2闪烁
uint8_t Icn_Falg, TimeIcn_Flag, BaseIcn_Flag;                                          // 温度、时间、底座图标显示的标志位

/**
 * @brief 闪烁函数
 *
 * @param dT 任务周期
 */
void Twinkle(float dT)
{
    
}

uint8_t seg[80] = {0};

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

/**
 * @brief 显示温度
 *
 * @param dis_set_temp 设定温度
 * @param dis_rel_temp 实际温度
 */
void Display_IC2( _Work_Num_ work_num[])
{
    uint8_t Val;// 用于百十个取出来的数字

    /*******************************1号工位*******************************/
    /**********工位1的实际转速显示**********/
    if (work_num[0].Speed.Display_Rel > 999) // 大于999时
    {
        Val = work_num[0].Speed.Display_Rel / 1000 % 10;
       if(Val > 0)
        {
            bit_Cal(2, 0x01, 0x00);bit_Cal(3, 0x01, 0x01);//显示数字1
        }
       else
       {
            bit_Cal(2, 0x01, 0x01);bit_Cal(3, 0x01, 0x01);//显示数字0
       }
    }
    else
    {
        bit_Cal(2, 0x01, 0x01);bit_Cal(3, 0x01, 0x01);//显示数字0
    }
    
   if (work_num[0].Speed.Display_Rel > 99) // 大于99时
   {
       Val = work_num[0].Speed.Display_Rel / 100 % 10;
       switch (Val)
       {
       case 0:
            bit_Cal(4, 0x03, 0x03);bit_Cal(5, 0x07, 0x05);bit_Cal(6, 0x03, 0x03);
            break;
       case 1:
            bit_Cal(4, 0x03, 0x00);bit_Cal(5, 0x07, 0x00);bit_Cal(6, 0x03, 0x03);
            break;
       case 2:
            bit_Cal(4, 0x03, 0x02);bit_Cal(5, 0x07, 0x07);bit_Cal(6, 0x03, 0x01);
            break;
       case 3:
            bit_Cal(4, 0x03, 0x00);bit_Cal(5, 0x07, 0x07);bit_Cal(6, 0x03, 0x03);
            break;
       case 4:
            bit_Cal(4, 0x03, 0x01);bit_Cal(5, 0x07, 0x02);bit_Cal(6, 0x03, 0x03);
            break;
       case 5:
            bit_Cal(4, 0x03, 0x01);bit_Cal(5, 0x07, 0x07);bit_Cal(6, 0x03, 0x02);
            break;
       case 6:
            bit_Cal(4, 0x03, 0x03);bit_Cal(5, 0x07, 0x07);bit_Cal(6, 0x03, 0x02);
            break;
       case 7:
            bit_Cal(4, 0x03, 0x00);bit_Cal(5, 0x07, 0x01);bit_Cal(6, 0x03, 0x03);
            break;
       case 8:
            bit_Cal(4, 0x03, 0x03);bit_Cal(5, 0x07, 0x07);bit_Cal(6, 0x03, 0x03);
            break;
       case 9:
            bit_Cal(4, 0x03, 0x01);bit_Cal(5, 0x07, 0x07);bit_Cal(6, 0x03, 0x03);
            break;
       default:
           break;
       }
   }
   else
   {
        bit_Cal(4, 0x03, 0x03);bit_Cal(5, 0x07, 0x05);bit_Cal(6, 0x03, 0x03);//显示数字零
   }

   if (work_num[0].Speed.Display_Rel > 9) // 大于9时
   {
       Val = work_num[0].Speed.Display_Rel / 10 % 10;
       switch (Val)
       {
       case 0:
            bit_Cal(7, 0x03, 0x03);bit_Cal(8, 0x07, 0x05);bit_Cal(9, 0x03, 0x03);
            break;
       case 1:
            bit_Cal(7, 0x03, 0x00);bit_Cal(8, 0x07, 0x00);bit_Cal(9, 0x03, 0x03);
            break;
       case 2:
            bit_Cal(7, 0x03, 0x02);bit_Cal(8, 0x07, 0x07);bit_Cal(9, 0x03, 0x01);
            break;
       case 3:
            bit_Cal(7, 0x03, 0x00);bit_Cal(8, 0x07, 0x07);bit_Cal(9, 0x03, 0x03);
            break;
       case 4:
            bit_Cal(7, 0x03, 0x01);bit_Cal(8, 0x07, 0x02);bit_Cal(9, 0x03, 0x03);
            break;
       case 5:
            bit_Cal(7, 0x03, 0x01);bit_Cal(8, 0x07, 0x07);bit_Cal(9, 0x03, 0x02);
            break;
       case 6:
            bit_Cal(7, 0x03, 0x03);bit_Cal(8, 0x07, 0x07);bit_Cal(9, 0x03, 0x02);
            break;
       case 7:
            bit_Cal(7, 0x03, 0x00);bit_Cal(8, 0x07, 0x01);bit_Cal(9, 0x03, 0x03);
            break;
       case 8:
            bit_Cal(7, 0x03, 0x03);bit_Cal(8, 0x07, 0x07);bit_Cal(9, 0x03, 0x03);
            break;
       case 9:
            bit_Cal(7, 0x03, 0x01);bit_Cal(8, 0x07, 0x07);bit_Cal(9, 0x03, 0x03);
            break;
       default:
           break;
       }
   }
   else
   {
        bit_Cal(7, 0x03, 0x03);bit_Cal(8, 0x07, 0x05);bit_Cal(9, 0x03, 0x03);//显示数字零
   }
    bit_Cal(10, 0x01, 0x01);//实际转速个位只能显示零

    /**********工位1的设定转速显示**********/
    if (work_num[0].Speed.Display_Set > 999) // 大于999时
    {
        Val = work_num[0].Speed.Display_Set / 1000 % 10;
       if(Val > 0)
        {
            bit_Cal(11, 0x01, 0x00);bit_Cal(12, 0x01, 0x01);//显示数字1
        }
       else
       {
            bit_Cal(11, 0x01, 0x01);bit_Cal(12, 0x01, 0x01);//显示数字0
       }
    }
    else
    {
        bit_Cal(11, 0x01, 0x01);bit_Cal(12, 0x01, 0x01);//显示数字0
    }
    
   if (work_num[0].Speed.Display_Set > 99) // 大于99时
   {
       Val = work_num[0].Speed.Display_Set / 100 % 10;
       switch (Val)
       {
       case 0:
            bit_Cal(13, 0x03, 0x03);bit_Cal(14, 0x07, 0x05);bit_Cal(15, 0x03, 0x03);
            break;
       case 1:
            bit_Cal(13, 0x03, 0x00);bit_Cal(14, 0x07, 0x00);bit_Cal(15, 0x03, 0x03);
            break;
       case 2:
            bit_Cal(13, 0x03, 0x02);bit_Cal(14, 0x07, 0x07);bit_Cal(15, 0x03, 0x01);
            break;
       case 3:
            bit_Cal(13, 0x03, 0x00);bit_Cal(14, 0x07, 0x07);bit_Cal(15, 0x03, 0x03);
            break;
       case 4:
            bit_Cal(13, 0x03, 0x01);bit_Cal(14, 0x07, 0x02);bit_Cal(15, 0x03, 0x03);
            break;
       case 5:
            bit_Cal(13, 0x03, 0x01);bit_Cal(14, 0x07, 0x07);bit_Cal(15, 0x03, 0x02);
            break;
       case 6:
            bit_Cal(13, 0x03, 0x03);bit_Cal(14, 0x07, 0x07);bit_Cal(15, 0x03, 0x02);
            break;
       case 7:
            bit_Cal(13, 0x03, 0x00);bit_Cal(14, 0x07, 0x01);bit_Cal(15, 0x03, 0x03);
            break;
       case 8:
            bit_Cal(13, 0x03, 0x03);bit_Cal(14, 0x07, 0x07);bit_Cal(15, 0x03, 0x03);
            break;
       case 9:
            bit_Cal(13, 0x03, 0x01);bit_Cal(14, 0x07, 0x07);bit_Cal(15, 0x03, 0x03);
            break;
       default:
           break;
       }
   }
   else
   {
        bit_Cal(13, 0x03, 0x03);bit_Cal(14, 0x07, 0x05);bit_Cal(15, 0x03, 0x03);//显示数字零
   }

   if (work_num[0].Speed.Display_Set > 9) // 大于9时
   {
       Val = work_num[0].Speed.Display_Set / 10 % 10;
       switch (Val)
       {
       case 0:
            bit_Cal(16, 0x03, 0x03);bit_Cal(17, 0x07, 0x05);bit_Cal(18, 0x03, 0x03);
            break;
       case 1:
            bit_Cal(16, 0x03, 0x00);bit_Cal(17, 0x07, 0x00);bit_Cal(18, 0x03, 0x03);
            break;
       case 2:
            bit_Cal(16, 0x03, 0x02);bit_Cal(17, 0x07, 0x07);bit_Cal(18, 0x03, 0x01);
            break;
       case 3:
            bit_Cal(16, 0x03, 0x00);bit_Cal(17, 0x07, 0x07);bit_Cal(18, 0x03, 0x03);
            break;
       case 4:
            bit_Cal(16, 0x03, 0x01);bit_Cal(17, 0x07, 0x02);bit_Cal(18, 0x03, 0x03);
            break;
       case 5:
            bit_Cal(16, 0x03, 0x01);bit_Cal(17, 0x07, 0x07);bit_Cal(18, 0x03, 0x02);
            break;
       case 6:
            bit_Cal(16, 0x03, 0x03);bit_Cal(17, 0x07, 0x07);bit_Cal(18, 0x03, 0x02);
            break;
       case 7:
            bit_Cal(16, 0x03, 0x00);bit_Cal(17, 0x07, 0x01);bit_Cal(18, 0x03, 0x03);
            break;
       case 8:
            bit_Cal(16, 0x03, 0x03);bit_Cal(17, 0x07, 0x07);bit_Cal(18, 0x03, 0x03);
            break;
       case 9:
            bit_Cal(16, 0x03, 0x01);bit_Cal(17, 0x07, 0x07);bit_Cal(18, 0x03, 0x03);
            break;
       default:
           break;
       }
   }
   else
   {
        bit_Cal(16, 0x03, 0x03);bit_Cal(17, 0x07, 0x05);bit_Cal(18, 0x03, 0x03);//显示数字零
   }
    bit_Cal(19, 0x01, 0x01);//实际转速个位只能显示零

    /**********工位1的实际温度显示**********/
    if (work_num[0].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[0].Temp.Display_Rel / 1000 % 10;
    }
    else if (work_num[0].Temp.Display_Rel < 0 && work_num[0].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[0].Temp.Display_Rel) / 1000 % 10;//计算后是0，不大于999所以不会显示
    }
    else if (work_num[0].Temp.Display_Rel <= -100 && work_num[0].Temp.Display_Rel > -1000)
    {
        Val = 10;//显示“-”
    }
    switch (Val)
    {
        case 0:
            if (work_num[0].Temp.Display_Rel > 999)//显示0
            {
                bit_Cal(0, 0x30, 0x30);bit_Cal(1, 0x1C, 0x14);bit_Cal(2, 0x0C, 0x0C);
            }
            else//不显示这位
            {
                bit_Cal(0, 0x30, 0x00);bit_Cal(1, 0x1C, 0x00);bit_Cal(2, 0x0C, 0x00);
            }
            break;
        case 1:
            bit_Cal(0, 0x30, 0x00);bit_Cal(1, 0x1C, 0x00);bit_Cal(2, 0x0C, 0x0C);
            break;
        case 2:
            bit_Cal(0, 0x30, 0x20);bit_Cal(1, 0x1C, 0x1C);bit_Cal(2, 0x0C, 0x04);
            break;
        case 3:
            bit_Cal(0, 0x30, 0x00);bit_Cal(1, 0x1C, 0x1C);bit_Cal(2, 0x0C, 0x0C);
            break;
        case 4:
            bit_Cal(0, 0x30, 0x10);bit_Cal(1, 0x1C, 0x08);bit_Cal(2, 0x0C, 0x0C);
            break;
        case 5:
            bit_Cal(0, 0x30, 0x10);bit_Cal(1, 0x1C, 0x1C);bit_Cal(2, 0x0C, 0x08);
            break;
        case 6:
            bit_Cal(0, 0x30, 0x30);bit_Cal(1, 0x1C, 0x1C);bit_Cal(2, 0x0C, 0x08);
            break;
        case 7:
            bit_Cal(0, 0x30, 0x00);bit_Cal(1, 0x1C, 0x04);bit_Cal(2, 0x0C, 0x0C);
            break;
        case 8:
            bit_Cal(0, 0x30, 0x30);bit_Cal(1, 0x1C, 0x1C);bit_Cal(2, 0x0C, 0x0C);
            break;
        case 9:
            bit_Cal(0, 0x30, 0x10);bit_Cal(1, 0x1C, 0x1C);bit_Cal(2, 0x0C, 0x0C);
            break;
        default:
            bit_Cal(0, 0x30, 0x00);bit_Cal(1, 0x1C, 0x08);bit_Cal(2, 0x0C, 0x00);//显示“-”
            break;
    }

    if (work_num[0].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[0].Temp.Display_Rel / 100 % 10;
    }
    else if (work_num[0].Temp.Display_Rel < 0 && work_num[0].Temp.Display_Rel > -100)
    {
        Val = 10;//显示“-”
    }
    else if (work_num[0].Temp.Display_Rel <= -100 && work_num[0].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[0].Temp.Display_Rel)/ 100 % 10;
    }
    switch (Val)
    {
        case 0:
            if (work_num[0].Temp.Display_Rel > 99)//显示零
            {
                bit_Cal(2, 0x02, 0x02);bit_Cal(3, 0x0E, 0x0A);bit_Cal(4, 0x1C, 0x1C);
            }
            else//不显示
            {
                bit_Cal(2, 0x02, 0x00);bit_Cal(3, 0x0E, 0x00);bit_Cal(4, 0x1C, 0x00);
            }
            break;
        case 1:
            bit_Cal(2, 0x02, 0x00);bit_Cal(3, 0x0E, 0x00);bit_Cal(4, 0x1C, 0x0C);
            break;
        case 2:
            bit_Cal(2, 0x02, 0x00);bit_Cal(3, 0x0E, 0x0E);bit_Cal(4, 0x1C, 0x14);
            break;
        case 3:
            bit_Cal(2, 0x02, 0x00);bit_Cal(3, 0x0E, 0x06);bit_Cal(4, 0x1C, 0x1C);
            break;
        case 4:
            bit_Cal(2, 0x02, 0x02);bit_Cal(3, 0x0E, 0x04);bit_Cal(4, 0x1C, 0x0C);
            break;
        case 5:
            bit_Cal(2, 0x02, 0x02);bit_Cal(3, 0x0E, 0x06);bit_Cal(4, 0x1C, 0x18);
            break;
        case 6:
            bit_Cal(2, 0x02, 0x02);bit_Cal(3, 0x0E, 0x0E);bit_Cal(4, 0x1C, 0x18);
            break;
        case 7:
            bit_Cal(2, 0x02, 0x00);bit_Cal(3, 0x0E, 0x02);bit_Cal(4, 0x1C, 0x0C);
            break;
        case 8:
            bit_Cal(2, 0x02, 0x02);bit_Cal(3, 0x0E, 0x0E);bit_Cal(4, 0x1C, 0x1C);
            break;
        case 9:
            bit_Cal(2, 0x02, 0x02);bit_Cal(3, 0x0E, 0x06);bit_Cal(4, 0x1C, 0x1C);
            break;
        default:
            bit_Cal(2, 0x02, 0x00);bit_Cal(3, 0x0E, 0x04);bit_Cal(4, 0x1C, 0x00);//显示“-”
            break;
    }

    if (work_num[0].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[0].Temp.Display_Rel / 10 % 10;
    }
    else if (work_num[0].Temp.Display_Rel < 0 && work_num[0].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[0].Temp.Display_Rel) / 10 % 10;
    }
    else if (work_num[0].Temp.Display_Rel <= -100 && work_num[0].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[0].Temp.Display_Rel) / 10 % 10;
    }
    switch (Val)
    {
    case 0:
        bit_Cal(5, 0x18, 0x18);bit_Cal(6, 0x1C, 0x14);bit_Cal(7, 0x0C, 0x0C);
        break;
    case 1:
        bit_Cal(5, 0x18, 0x00);bit_Cal(6, 0x1C, 0x00);bit_Cal(7, 0x0C, 0x0C);
        break;
    case 2:
        bit_Cal(5, 0x18, 0x10);bit_Cal(6, 0x1C, 0x1C);bit_Cal(7, 0x0C, 0x04);
        break;
    case 3:
        bit_Cal(5, 0x18, 0x00);bit_Cal(6, 0x1C, 0x1C);bit_Cal(7, 0x0C, 0x0C);
        break;
    case 4:
        bit_Cal(5, 0x18, 0x08);bit_Cal(6, 0x1C, 0x08);bit_Cal(7, 0x0C, 0x0C);
        break;
    case 5:
        bit_Cal(5, 0x18, 0x08);bit_Cal(6, 0x1C, 0x1C);bit_Cal(7, 0x0C, 0x08);
        break;
    case 6:
        bit_Cal(5, 0x18, 0x18);bit_Cal(6, 0x1C, 0x1C);bit_Cal(7, 0x0C, 0x08);
        break;
    case 7:
        bit_Cal(5, 0x18, 0x00);bit_Cal(6, 0x1C, 0x04);bit_Cal(7, 0x0C, 0x0C);
        break;
    case 8:
        bit_Cal(5, 0x18, 0x18);bit_Cal(6, 0x1C, 0x1C);bit_Cal(7, 0x0C, 0x0C);
        break;
    case 9:
        bit_Cal(5, 0x18, 0x08);bit_Cal(6, 0x1C, 0x1C);bit_Cal(7, 0x0C, 0x0C);
        break;
    default:
        bit_Cal(5, 0x18, 0x00);bit_Cal(6, 0x1C, 0x08);bit_Cal(7, 0x0C, 0x00);//显示“-”
        break;
    }

    if (work_num[0].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[0].Temp.Display_Rel / 10 % 10;
    }
    else if (work_num[0].Temp.Display_Rel < 0 && work_num[0].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[0].Temp.Display_Rel) % 10;
    }
    else if (work_num[0].Temp.Display_Rel <= -100 && work_num[0].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[0].Temp.Display_Rel) % 10;
    }
    switch (Val)
    {
        case 0:
            bit_Cal(8, 0x38, 0x38);bit_Cal(9, 0x1C, 0x14);bit_Cal(10, 0x04, 0x04);
            break;
        case 1:
            bit_Cal(8, 0x38, 0x00);bit_Cal(9, 0x1C, 0x10);bit_Cal(10, 0x04, 0x04);
            break;
        case 2:
            bit_Cal(8, 0x38, 0x30);bit_Cal(9, 0x1C, 0x0C);bit_Cal(10, 0x04, 0x04);
            break;
        case 3:
            bit_Cal(8, 0x38, 0x20);bit_Cal(9, 0x1C, 0x1C);bit_Cal(10, 0x04, 0x04);
            break;
        case 4:
            bit_Cal(8, 0x38, 0x08);bit_Cal(9, 0x1C, 0x18);bit_Cal(10, 0x04, 0x04);
            break;
        case 5:
            bit_Cal(8, 0x38, 0x28);bit_Cal(9, 0x1C, 0x1C);bit_Cal(10, 0x04, 0x00);
            break;
        case 6:
            bit_Cal(8, 0x38, 0x38);bit_Cal(9, 0x1C, 0x1C);bit_Cal(10, 0x04, 0x00);
            break;
        case 7:
            bit_Cal(8, 0x38, 0x00);bit_Cal(9, 0x1C, 0x14);bit_Cal(10, 0x04, 0x04);
            break;
        case 8:
            bit_Cal(8, 0x38, 0x38);bit_Cal(9, 0x1C, 0x1C);bit_Cal(10, 0x04, 0x04);
            break;
        case 9:
            bit_Cal(8, 0x38, 0x28);bit_Cal(9, 0x1C, 0x1C);bit_Cal(10, 0x04, 0x04);
            break;
        default:
            bit_Cal(8, 0x38, 0x00);bit_Cal(9, 0x1C, 0x08);bit_Cal(10, 0x04, 0x00);//显示“-”
            break;
    }

    /* 1号工位实际温度小数点 */
    bit_Cal(7, 0x10, 0x10);

    /**********工位1的设定温度显示**********/
    if (work_num[0].Temp.Display_Set >= 0)//大于等于0时
    {
        Val = work_num[0].Temp.Display_Set / 1000 % 10;
    }
    else if (work_num[0].Temp.Display_Set < 0 && work_num[0].Temp.Display_Set > -100)
    {
        Val = ABS(work_num[0].Temp.Display_Set) / 1000 % 10;//计算后是0，不大于999所以不会显示
    }
    else if (work_num[0].Temp.Display_Set <= -100 && work_num[0].Temp.Display_Set > -1000)
    {
        Val = 10;//显示“-”
    }
    switch (Val)
    {
        case 0:
            if (work_num[0].Temp.Display_Set > 999)//显示0
            {
                bit_Cal(10, 0x0A, 0x0A);bit_Cal(11, 0x0E, 0x0A);bit_Cal(12, 0x06, 0x06);
            }
            else//不显示这位
            {
                bit_Cal(10, 0x0A, 0x00);bit_Cal(11, 0x0E, 0x00);bit_Cal(12, 0x06, 0x00);
            }
            break;
        case 1:
            bit_Cal(10, 0x0A, 0x00);bit_Cal(11, 0x0E, 0x00);bit_Cal(12, 0x06, 0x06);
            break;
        case 2:
            bit_Cal(10, 0x0A, 0x08);bit_Cal(11, 0x0E, 0x0E);bit_Cal(12, 0x06, 0x02);
            break;
        case 3:
            bit_Cal(10, 0x0A, 0x00);bit_Cal(11, 0x0E, 0x0E);bit_Cal(12, 0x06, 0x06);
            break;
        case 4:
            bit_Cal(10, 0x0A, 0x02);bit_Cal(11, 0x0E, 0x04);bit_Cal(12, 0x06, 0x06);
            break;
        case 5:
            bit_Cal(10, 0x0A, 0x02);bit_Cal(11, 0x0E, 0x0E);bit_Cal(12, 0x06, 0x04);
            break;
        case 6:
            bit_Cal(10, 0x0A, 0x0A);bit_Cal(11, 0x0E, 0x0E);bit_Cal(12, 0x06, 0x04);
            break;
        case 7:
            bit_Cal(10, 0x0A, 0x00);bit_Cal(11, 0x0E, 0x02);bit_Cal(12, 0x06, 0x06);
            break;
        case 8:
            bit_Cal(10, 0x0A, 0x0A);bit_Cal(11, 0x0E, 0x0E);bit_Cal(12, 0x06, 0x06);
            break;
        case 9:
            bit_Cal(10, 0x0A, 0x02);bit_Cal(11, 0x0E, 0x0E);bit_Cal(12, 0x06, 0x06);
            break;
        default:
            bit_Cal(10, 0x0A, 0x00);bit_Cal(11, 0x0E, 0x04);bit_Cal(12, 0x06, 0x00);//显示“-”
            break;
    }

    if (work_num[0].Temp.Display_Set >= 0)//大于等于0时
    {
        Val = work_num[0].Temp.Display_Set / 100 % 10;
    }
    else if (work_num[0].Temp.Display_Set < 0 && work_num[0].Temp.Display_Set > -100)
    {
        Val = 10;//显示“-”
    }
    else if (work_num[0].Temp.Display_Set <= -100 && work_num[0].Temp.Display_Set > -1000)
    {
        Val = ABS(work_num[0].Temp.Display_Set)/ 100 % 10;
    }
    switch (Val)
    {
        case 0:
            if (work_num[0].Temp.Display_Set > 99)//显示零
            {
                bit_Cal(12, 0x08, 0x08);bit_Cal(13, 0x1C, 0x14);bit_Cal(14, 0x38, 0x38);
            }
            else//不显示
            {
                bit_Cal(12, 0x08, 0x00);bit_Cal(13, 0x1C, 0x00);bit_Cal(14, 0x38, 0x00);
            }
            break;
        case 1:
            bit_Cal(12, 0x08, 0x00);bit_Cal(13, 0x1C, 0x00);bit_Cal(14, 0x38, 0x30);
            break;
        case 2:
            bit_Cal(12, 0x08, 0x08);bit_Cal(13, 0x1C, 0x18);bit_Cal(14, 0x38, 0x18);
            break;
        case 3:
            bit_Cal(12, 0x08, 0x00);bit_Cal(13, 0x1C, 0x18);bit_Cal(14, 0x38, 0x38);
            break;
        case 4:
            bit_Cal(12, 0x08, 0x00);bit_Cal(13, 0x1C, 0x0C);bit_Cal(14, 0x38, 0x30);
            break;
        case 5:
            bit_Cal(12, 0x08, 0x00);bit_Cal(13, 0x1C, 0x1C);bit_Cal(14, 0x38, 0x28);
            break;
        case 6:
            bit_Cal(12, 0x08, 0x08);bit_Cal(13, 0x1C, 0x1C);bit_Cal(14, 0x38, 0x28);
            break;
        case 7:
            bit_Cal(12, 0x08, 0x00);bit_Cal(13, 0x1C, 0x00);bit_Cal(14, 0x38, 0x38);
            break;
        case 8:
            bit_Cal(12, 0x08, 0x08);bit_Cal(13, 0x1C, 0x1C);bit_Cal(14, 0x38, 0x38);
            break;
        case 9:
            bit_Cal(12, 0x08, 0x00);bit_Cal(13, 0x1C, 0x1C);bit_Cal(14, 0x38, 0x38);
            break;
        default:
            bit_Cal(12, 0x08, 0x00);bit_Cal(13, 0x1C, 0x08);bit_Cal(14, 0x38, 0x00);//显示“-”
            break;
    }

    if (work_num[0].Temp.Display_Set >= 0)//大于等于0时
    {
        Val = work_num[0].Temp.Display_Set / 10 % 10;
    }
    else if (work_num[0].Temp.Display_Set < 0 && work_num[0].Temp.Display_Set > -100)
    {
        Val = ABS(work_num[0].Temp.Display_Set) / 10 % 10;
    }
    else if (work_num[0].Temp.Display_Set <= -100 && work_num[0].Temp.Display_Set > -1000)
    {
        Val = ABS(work_num[0].Temp.Display_Set) / 10 % 10;
    }
    switch (Val)
    {
        case 0:
            bit_Cal(15, 0x1C, 0x1C);bit_Cal(16, 0x1C, 0x14);bit_Cal(17, 0x08, 0x08);
            break;
        case 1:
            bit_Cal(15, 0x1C, 0x00);bit_Cal(16, 0x1C, 0x10);bit_Cal(17, 0x08, 0x08);
            break;
        case 2:
            bit_Cal(15, 0x1C, 0x18);bit_Cal(16, 0x1C, 0x0C);bit_Cal(17, 0x08, 0x08);
            break;
        case 3:
            bit_Cal(15, 0x1C, 0x10);bit_Cal(16, 0x1C, 0x1C);bit_Cal(17, 0x08, 0x08);
            break;
        case 4:
            bit_Cal(15, 0x1C, 0x04);bit_Cal(16, 0x1C, 0x18);bit_Cal(17, 0x08, 0x08);
            break;
        case 5:
            bit_Cal(15, 0x1C, 0x14);bit_Cal(16, 0x1C, 0x1C);bit_Cal(17, 0x08, 0x00);
            break;
        case 6:
            bit_Cal(15, 0x1C, 0x1C);bit_Cal(16, 0x1C, 0x1C);bit_Cal(17, 0x08, 0x00);
            break;
        case 7:
            bit_Cal(15, 0x1C, 0x00);bit_Cal(16, 0x1C, 0x14);bit_Cal(17, 0x08, 0x08);
            break;
        case 8:
            bit_Cal(15, 0x1C, 0x1C);bit_Cal(16, 0x1C, 0x1C);bit_Cal(17, 0x08, 0x08);
            break;
        case 9:
            bit_Cal(15, 0x1C, 0x14);bit_Cal(16, 0x1C, 0x1C);bit_Cal(17, 0x08, 0x08);
            break;
        default:
            bit_Cal(15, 0x1C, 0x00);bit_Cal(16, 0x1C, 0x08);bit_Cal(17, 0x08, 0x00);//显示“-”
            break;
    }

    if (work_num[0].Temp.Display_Set >= 0)//大于等于0时
    {
        Val = work_num[0].Temp.Display_Set / 10 % 10;
    }
    else if (work_num[0].Temp.Display_Set < 0 && work_num[0].Temp.Display_Set > -100)
    {
        Val = ABS(work_num[0].Temp.Display_Set) % 10;
    }
    else if (work_num[0].Temp.Display_Set <= -100 && work_num[0].Temp.Display_Set > -1000)
    {
        Val = ABS(work_num[0].Temp.Display_Set) % 10;
    }
    switch (Val)
    {
        case 0:
            bit_Cal(18, 0x3C, 0x3C);bit_Cal(19, 0x38, 0x28);
            break;
        case 1:
            bit_Cal(18, 0x3C, 0x00);bit_Cal(19, 0x38, 0x28);
            break;
        case 2:
            bit_Cal(18, 0x3C, 0x34);bit_Cal(19, 0x38, 0x18);
            break;
        case 3:
            bit_Cal(18, 0x3C, 0x24);bit_Cal(19, 0x38, 0x38);
            break;
        case 4:
            bit_Cal(18, 0x3C, 0x08);bit_Cal(19, 0x38, 0x38);
            break;
        case 5:
            bit_Cal(18, 0x3C, 0x2C);bit_Cal(19, 0x38, 0x30);
            break;
        case 6:
            bit_Cal(18, 0x3C, 0x3C);bit_Cal(19, 0x38, 0x30);
            break;
        case 7:
            bit_Cal(18, 0x3C, 0x04);bit_Cal(19, 0x38, 0x28);
            break;
        case 8:
            bit_Cal(18, 0x3C, 0x3C);bit_Cal(19, 0x38, 0x38);
            break;
        case 9:
            bit_Cal(18, 0x3C, 0x2C);bit_Cal(19, 0x38, 0x38);
            break;
        default:
            bit_Cal(18, 0x3C, 0x00);bit_Cal(19, 0x38, 0x10);//显示“-”
            break;
    }
    /* 1号工位设定温度小数点 */
    bit_Cal(17, 0x10, 0x10);

    /**********工位1的实际时间显示**********/
    Val = work_num[0].Time.Display_Rel / 3600 / 10;//计算十位为单位的小时数
    switch (Val)
    {
        case 0:
            bit_Cal(1, 0xE0, 0x60);bit_Cal(2, 0xE0, 0xE0);
            break;
        case 1:
            bit_Cal(1, 0xE0, 0x00);bit_Cal(2, 0xE0, 0x60);
            break;
        case 2:
            bit_Cal(1, 0xE0, 0xA0);bit_Cal(2, 0xE0, 0xA0);
            break;
        default:
            bit_Cal(1, 0xE0, 0x80);bit_Cal(2, 0xE0, 0x00);//显示“-”
            break;
    }

    Val = work_num[0].Time.Display_Rel / 3600 % 10;// 计算个位为单位的小时数
    switch (Val)
    {
        case 0:
            bit_Cal(2, 0x10, 0x10);bit_Cal(3, 0xF0, 0xD0);bit_Cal(4, 0x60, 0x60);
            break;
        case 1:
            bit_Cal(2, 0x10, 0x00);bit_Cal(3, 0xF0, 0x00);bit_Cal(4, 0x60, 0x60);
            break;
        case 2:
            bit_Cal(2, 0x10, 0x00);bit_Cal(3, 0xF0, 0xF0);bit_Cal(4, 0x60, 0x20);
            break;
        case 3:
            bit_Cal(2, 0x10, 0x00);bit_Cal(3, 0xF0, 0xB0);bit_Cal(4, 0x60, 0x60);
            break;
        case 4:
            bit_Cal(2, 0x10, 0x10);bit_Cal(3, 0xF0, 0x20);bit_Cal(4, 0x60, 0x60);
            break;
        case 5:
            bit_Cal(2, 0x10, 0x10);bit_Cal(3, 0xF0, 0xB0);bit_Cal(4, 0x60, 0x40);
            break;
        case 6:
            bit_Cal(2, 0x10, 0x10);bit_Cal(3, 0xF0, 0xF0);bit_Cal(4, 0x60, 0x40);
            break;
        case 7:
            bit_Cal(2, 0x10, 0x00);bit_Cal(3, 0xF0, 0x10);bit_Cal(4, 0x60, 0x60);
            break;
        case 8:
            bit_Cal(2, 0x10, 0x10);bit_Cal(3, 0xF0, 0xF0);bit_Cal(4, 0x60, 0x60);
            break;
        case 9:
            bit_Cal(2, 0x10, 0x10);bit_Cal(3, 0xF0, 0xB0);bit_Cal(4, 0x60, 0x60);
            break;
        default:
            bit_Cal(2, 0x10, 0x00);bit_Cal(3, 0xF0, 0x20);bit_Cal(4, 0x60, 0x00);//显示“-”
            break;
    }

    Val = work_num[0].Time.Display_Rel % 3600 / 60 / 10; // 计算十分位为单位的分钟数
    switch (Val)
    {
        case 0:
            bit_Cal(5, 0xE0, 0xA0);bit_Cal(6, 0xE0, 0xE0);bit_Cal(19, 0x80, 0x80);
            break;
        case 1:
            bit_Cal(5, 0xE0, 0x00);bit_Cal(6, 0xE0, 0xC0);bit_Cal(19, 0x80, 0x00);
            break;
        case 2:
            bit_Cal(5, 0xE0, 0xC0);bit_Cal(6, 0xE0, 0x60);bit_Cal(19, 0x80, 0x80);
            break;
        case 3:
            bit_Cal(5, 0xE0, 0x40);bit_Cal(6, 0xE0, 0xE0);bit_Cal(19, 0x80, 0x80);
            break;
        case 4:
            bit_Cal(5, 0xE0, 0x60);bit_Cal(6, 0xE0, 0xC0);bit_Cal(19, 0x80, 0x00);
            break;
        case 5:
            bit_Cal(5, 0xE0, 0x60);bit_Cal(6, 0xE0, 0xA0);bit_Cal(19, 0x80, 0x80);
            break;
        case 6:
            bit_Cal(5, 0xE0, 0xE0);bit_Cal(6, 0xE0, 0xA0);bit_Cal(19, 0x80, 0x80);
            break;
        case 7:
            bit_Cal(5, 0xE0, 0x00);bit_Cal(6, 0xE0, 0xE0);bit_Cal(19, 0x80, 0x00);
            break;
        case 8:
            bit_Cal(5, 0xE0, 0xE0);bit_Cal(6, 0xE0, 0xE0);bit_Cal(19, 0x80, 0x80);
            break;
        case 9:
            bit_Cal(5, 0xE0, 0x60);bit_Cal(6, 0xE0, 0xE0);bit_Cal(19, 0x80, 0x80);
            break;
        default:
            bit_Cal(5, 0xE0, 0x40);bit_Cal(6, 0xE0, 0x00);bit_Cal(19, 0x80, 0x00);//显示“-”
            break;
    }

    Val = work_num[0].Time.Display_Rel % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
    switch (Val)
    {
        case 0:
            bit_Cal(7, 0xE0, 0xA0);bit_Cal(8, 0xC0, 0xC0);bit_Cal(9, 0x80, 0x80);bit_Cal(10, 0x80, 0x80);
            break;
        case 1:
            bit_Cal(7, 0xE0, 0x00);bit_Cal(8, 0xC0, 0x80);bit_Cal(9, 0x80, 0x80);bit_Cal(10, 0x80, 0x00);
            break;
        case 2:
            bit_Cal(7, 0xE0, 0xC0);bit_Cal(8, 0xC0, 0xC0);bit_Cal(9, 0x80, 0x00);bit_Cal(10, 0x80, 0x80);
            break;
        case 3:
            bit_Cal(7, 0xE0, 0x40);bit_Cal(8, 0xC0, 0xC0);bit_Cal(9, 0x80, 0x80);bit_Cal(10, 0x80, 0x80);
            break;
        case 4:
            bit_Cal(7, 0xE0, 0x60);bit_Cal(8, 0xC0, 0x90);bit_Cal(9, 0x80, 0x80);bit_Cal(10, 0x80, 0x00);
            break;
        case 5:
            bit_Cal(7, 0xE0, 0x60);bit_Cal(8, 0xC0, 0x40);bit_Cal(9, 0x80, 0x80);bit_Cal(10, 0x80, 0x80);
            break;
        case 6:
            bit_Cal(7, 0xE0, 0xE0);bit_Cal(8, 0xC0, 0x40);bit_Cal(9, 0x80, 0x80);bit_Cal(10, 0x80, 0x80);
            break;
        case 7:
            bit_Cal(7, 0xE0, 0x00);bit_Cal(8, 0xC0, 0xC0);bit_Cal(9, 0x80, 0x80);bit_Cal(10, 0x80, 0x00);
            break;
        case 8:
            bit_Cal(7, 0xE0, 0xE0);bit_Cal(8, 0xC0, 0xC0);bit_Cal(9, 0x80, 0x80);bit_Cal(10, 0x80, 0x80);
            break;
        case 9:
            bit_Cal(7, 0xE0, 0x60);bit_Cal(8, 0xC0, 0xC0);bit_Cal(9, 0x80, 0x80);bit_Cal(10, 0x80, 0x80);
            break;
        default:
            bit_Cal(7, 0xE0, 0x40);bit_Cal(8, 0xC0, 0x00);bit_Cal(9, 0x80, 0x00);bit_Cal(10, 0x80, 0x00);//显示“-”
            break;
    }
    /* 1号工位实际时间冒号 */
    bit_Cal(4, 0x80, 0x80);

    /**********工位1的设定时间显示**********/
    Val = work_num[0].Time.Display_Set / 3600 / 10;//计算十位为单位的小时数
    switch (Val)
    {
        case 0:
            bit_Cal(9, 0x60, 0x60);bit_Cal(10, 0x70, 0x50);bit_Cal(11, 0x50, 0x50);
            break;
        case 1:
            bit_Cal(9, 0x60, 0x00);bit_Cal(10, 0x70, 0x00);bit_Cal(11, 0x50, 0x50);
            break;
        case 2:
            bit_Cal(9, 0x60, 0x40);bit_Cal(10, 0x70, 0x70);bit_Cal(11, 0x50, 0x10);
            break;
        default:
            bit_Cal(9, 0x60, 0x00);bit_Cal(10, 0x70, 0x20);bit_Cal(11, 0x50, 0x00);//显示“-”
            break;
    }

    Val = work_num[0].Time.Display_Set / 3600 % 10;// 计算个位为单位的小时数
    switch (Val)
    {
        case 0:
            bit_Cal(11, 0x20, 0x20);bit_Cal(12, 0xF0, 0xD0);bit_Cal(13, 0x60, 0x60);
            break;
        case 1:
            bit_Cal(11, 0x20, 0x00);bit_Cal(12, 0xF0, 0x00);bit_Cal(13, 0x60, 0x60);
            break;
        case 2:
            bit_Cal(11, 0x20, 0x00);bit_Cal(12, 0xF0, 0xF0);bit_Cal(13, 0x60, 0x20);
            break;
        case 3:
            bit_Cal(11, 0x20, 0x00);bit_Cal(12, 0xF0, 0xB0);bit_Cal(13, 0x60, 0x60);
            break;
        case 4:
            bit_Cal(11, 0x20, 0x20);bit_Cal(12, 0xF0, 0x20);bit_Cal(13, 0x60, 0x60);
            break;
        case 5:
            bit_Cal(11, 0x20, 0x20);bit_Cal(12, 0xF0, 0xB0);bit_Cal(13, 0x60, 0x40);
            break;
        case 6:
            bit_Cal(11, 0x20, 0x20);bit_Cal(12, 0xF0, 0xF0);bit_Cal(13, 0x60, 0x40);
            break;
        case 7:
            bit_Cal(11, 0x20, 0x00);bit_Cal(12, 0xF0, 0x10);bit_Cal(13, 0x60, 0x60);
            break;
        case 8:
            bit_Cal(11, 0x20, 0x20);bit_Cal(12, 0xF0, 0xF0);bit_Cal(13, 0x60, 0x60);
            break;
        case 9:
            bit_Cal(11, 0x20, 0x20);bit_Cal(12, 0xF0, 0xB0);bit_Cal(13, 0x60, 0x60);
            break;
        default:
            bit_Cal(11, 0x20, 0x00);bit_Cal(12, 0xF0, 0x20);bit_Cal(13, 0x60, 0x00);//显示“-”
            break;
    }

    Val = work_num[0].Time.Display_Set % 3600 / 60 / 10; // 计算十分位为单位的分钟数
    switch (Val)
    {
        case 0:
            bit_Cal(11, 0x80, 0x80);bit_Cal(14, 0xC0, 0x40);bit_Cal(15, 0xE0, 0xE0);bit_Cal(16, 0x80, 0x80);
            break;
        case 1:
            bit_Cal(11, 0x80, 0x00);bit_Cal(14, 0xC0, 0x00);bit_Cal(15, 0xE0, 0xC0);bit_Cal(16, 0x80, 0x00);
            break;
        case 2:
            bit_Cal(11, 0x80, 0x80);bit_Cal(14, 0xC0, 0x80);bit_Cal(15, 0xE0, 0x60);bit_Cal(16, 0x80, 0x80);
            break;
        case 3:
            bit_Cal(11, 0x80, 0x00);bit_Cal(14, 0xC0, 0x80);bit_Cal(15, 0xE0, 0xE0);bit_Cal(16, 0x80, 0x80);
            break;
        case 4:
            bit_Cal(11, 0x80, 0x00);bit_Cal(14, 0xC0, 0xC0);bit_Cal(15, 0xE0, 0xC0);bit_Cal(16, 0x80, 0x00);
            break;
        case 5:
            bit_Cal(11, 0x80, 0x00);bit_Cal(14, 0xC0, 0xC0);bit_Cal(15, 0xE0, 0xA0);bit_Cal(16, 0x80, 0x80);
            break;
        case 6:
            bit_Cal(11, 0x80, 0x80);bit_Cal(14, 0xC0, 0xC0);bit_Cal(15, 0xE0, 0xA0);bit_Cal(16, 0x80, 0x80);
            break;
        case 7:
            bit_Cal(11, 0x80, 0x00);bit_Cal(14, 0xC0, 0x00);bit_Cal(15, 0xE0, 0xE0);bit_Cal(16, 0x80, 0x00);
            break;
        case 8:
            bit_Cal(11, 0x80, 0x80);bit_Cal(14, 0xC0, 0xC0);bit_Cal(15, 0xE0, 0xE0);bit_Cal(16, 0x80, 0x80);
            break;
        case 9:
            bit_Cal(11, 0x80, 0x00);bit_Cal(14, 0xC0, 0xC0);bit_Cal(15, 0xE0, 0xE0);bit_Cal(16, 0x80, 0x80);
            break;
        default:
            bit_Cal(11, 0x80, 0x00);bit_Cal(14, 0xC0, 0x80);bit_Cal(15, 0xE0, 0x00);bit_Cal(16, 0x80, 0x00);//显示“-”
            break;
    }

    Val = work_num[0].Time.Display_Set % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
    switch (Val)
    {
        case 0:
            bit_Cal(16, 0x60, 0x60);bit_Cal(17, 0xE0, 0xA0);bit_Cal(18, 0xC0, 0xC0);
            break;
        case 1:
            bit_Cal(16, 0x60, 0x00);bit_Cal(17, 0xE0, 0x00);bit_Cal(18, 0xC0, 0xC0);
            break;
        case 2:
            bit_Cal(16, 0x60, 0x40);bit_Cal(17, 0xE0, 0xE0);bit_Cal(18, 0xC0, 0x40);
            break;
        case 3:
            bit_Cal(16, 0x60, 0x00);bit_Cal(17, 0xE0, 0xE0);bit_Cal(18, 0xC0, 0xC0);
            break;
        case 4:
            bit_Cal(16, 0x60, 0x20);bit_Cal(17, 0xE0, 0x40);bit_Cal(18, 0xC0, 0xC0);
            break;
        case 5:
            bit_Cal(16, 0x60, 0x20);bit_Cal(17, 0xE0, 0xE0);bit_Cal(18, 0xC0, 0x80);
            break;
        case 6:
            bit_Cal(16, 0x60, 0x60);bit_Cal(17, 0xE0, 0xE0);bit_Cal(18, 0xC0, 0x80);
            break;
        case 7:
            bit_Cal(16, 0x60, 0x00);bit_Cal(17, 0xE0, 0x20);bit_Cal(18, 0xC0, 0xC0);
            break;
        case 8:
            bit_Cal(16, 0x60, 0x60);bit_Cal(17, 0xE0, 0xE0);bit_Cal(18, 0xC0, 0xC0);
            break;
        case 9:
            bit_Cal(16, 0x60, 0x20);bit_Cal(17, 0xE0, 0xE0);bit_Cal(18, 0xC0, 0xC0);
            break;
        default:
            bit_Cal(16, 0x60, 0x00);bit_Cal(17, 0xE0, 0x40);bit_Cal(18, 0xC0, 0x00);//显示“-”
            break;
    }
    /* 1号工位设定时间冒号 */
    bit_Cal(13, 0x80, 0x80);
    /* 1号工位“rpm”图标 */
    bit_Cal(19, 0x02, 0x02);
    
    /* 1号工位“℃”图标 */
    bit_Cal(19, 0x04, 0x04);

    /* 1号工位“min”图标 */
    bit_Cal(19, 0x40, 0x40);

    /* 1号工位与3号工位之间横线 */
    bit_Cal(0, 0x80, 0x80);

    /* 1号工位转速图标 */
    bit_Cal(0, 0x01, 0x01);//1号工位转速图标S70
    bit_Cal(1, 0x01, 0x01);//1号工位转速图标S71
    bit_Cal(1, 0x02, 0x02);//1号工位转速图标S72
    
    /* 1号工位加热图标 */
    bit_Cal(0, 0x02, 0x02);//1号工位加热图标S73
    bit_Cal(0, 0x04, 0x04);//1号工位加热图标S74
    bit_Cal(0, 0x08, 0x08);//1号工位温度探头图标
    
    /* 1号工位时间图标 */
    bit_Cal(0, 0x40, 0x40);//1号工位时间图标

    /*******************************2号工位*******************************/
    /**********工位2的实际转速显示**********/
    if (work_num[1].Speed.Display_Rel > 999) // 大于999时
    {
        Val = work_num[1].Speed.Display_Rel / 1000 % 10;
       if(Val > 0)
        {
            bit_Cal(22, 0x01, 0x00);bit_Cal(23, 0x01, 0x01);//显示数字1
        }
       else
       {
            bit_Cal(22, 0x01, 0x01);bit_Cal(23, 0x01, 0x01);//显示数字0
       }
    }
    else
    {
        bit_Cal(22, 0x01, 0x01);bit_Cal(23, 0x01, 0x01);//显示数字0
    }
    
   if (work_num[1].Speed.Display_Rel > 99) // 大于99时
   {
       Val = work_num[1].Speed.Display_Rel / 100 % 10;
       switch (Val)
       {
       case 0:
            bit_Cal(24, 0x03, 0x03);bit_Cal(25, 0x07, 0x05);bit_Cal(26, 0x03, 0x03);
            break;
       case 1:
            bit_Cal(24, 0x03, 0x00);bit_Cal(25, 0x07, 0x00);bit_Cal(26, 0x03, 0x03);
            break;
       case 2:
            bit_Cal(24, 0x03, 0x02);bit_Cal(25, 0x07, 0x07);bit_Cal(26, 0x03, 0x01);
            break;
       case 3:
            bit_Cal(24, 0x03, 0x00);bit_Cal(25, 0x07, 0x07);bit_Cal(26, 0x03, 0x03);
            break;
       case 4:
            bit_Cal(24, 0x03, 0x01);bit_Cal(25, 0x07, 0x02);bit_Cal(26, 0x03, 0x03);
            break;
       case 5:
            bit_Cal(24, 0x03, 0x01);bit_Cal(25, 0x07, 0x07);bit_Cal(26, 0x03, 0x02);
            break;
       case 6:
            bit_Cal(24, 0x03, 0x03);bit_Cal(25, 0x07, 0x07);bit_Cal(26, 0x03, 0x02);
            break;
       case 7:
            bit_Cal(24, 0x03, 0x00);bit_Cal(25, 0x07, 0x01);bit_Cal(26, 0x03, 0x03);
            break;
       case 8:
            bit_Cal(24, 0x03, 0x03);bit_Cal(25, 0x07, 0x07);bit_Cal(26, 0x03, 0x03);
            break;
       case 9:
            bit_Cal(24, 0x03, 0x01);bit_Cal(25, 0x07, 0x07);bit_Cal(26, 0x03, 0x03);
            break;
       default:
           break;
       }
   }
   else
   {
        bit_Cal(24, 0x03, 0x03);bit_Cal(25, 0x07, 0x05);bit_Cal(26, 0x03, 0x03);//显示数字零
   }

   if (work_num[1].Speed.Display_Rel > 9) // 大于9时
   {
       Val = work_num[1].Speed.Display_Rel / 10 % 10;
       switch (Val)
       {
       case 0:
            bit_Cal(27, 0x03, 0x03);bit_Cal(28, 0x07, 0x05);bit_Cal(29, 0x03, 0x03);
            break;
       case 1:
            bit_Cal(27, 0x03, 0x00);bit_Cal(28, 0x07, 0x00);bit_Cal(29, 0x03, 0x03);
            break;
       case 2:
            bit_Cal(27, 0x03, 0x02);bit_Cal(28, 0x07, 0x07);bit_Cal(29, 0x03, 0x01);
            break;
       case 3:
            bit_Cal(27, 0x03, 0x00);bit_Cal(28, 0x07, 0x07);bit_Cal(29, 0x03, 0x03);
            break;
       case 4:
            bit_Cal(27, 0x03, 0x01);bit_Cal(28, 0x07, 0x02);bit_Cal(29, 0x03, 0x03);
            break;
       case 5:
            bit_Cal(27, 0x03, 0x01);bit_Cal(28, 0x07, 0x07);bit_Cal(29, 0x03, 0x02);
            break;
       case 6:
            bit_Cal(27, 0x03, 0x03);bit_Cal(28, 0x07, 0x07);bit_Cal(29, 0x03, 0x02);
            break;
       case 7:
            bit_Cal(27, 0x03, 0x00);bit_Cal(28, 0x07, 0x01);bit_Cal(29, 0x03, 0x03);
            break;
       case 8:
            bit_Cal(27, 0x03, 0x03);bit_Cal(28, 0x07, 0x07);bit_Cal(29, 0x03, 0x03);
            break;
       case 9:
            bit_Cal(27, 0x03, 0x01);bit_Cal(28, 0x07, 0x07);bit_Cal(29, 0x03, 0x03);
            break;
       default:
           break;
       }
   }
   else
   {
        bit_Cal(27, 0x03, 0x03);bit_Cal(28, 0x07, 0x05);bit_Cal(29, 0x03, 0x03);//显示数字零
   }
    bit_Cal(30, 0x01, 0x01);//实际转速个位只能显示零

    /**********工位2的设定转速显示**********/
    if (work_num[1].Speed.Display_Set > 999) // 大于999时
    {
        Val = work_num[1].Speed.Display_Set / 1000 % 10;
       if(Val > 0)
        {
            bit_Cal(31, 0x01, 0x00);bit_Cal(32, 0x01, 0x01);//显示数字1
        }
       else
       {
            bit_Cal(31, 0x01, 0x01);bit_Cal(32, 0x01, 0x01);//显示数字0
       }
    }
    else
    {
        bit_Cal(31, 0x01, 0x01);bit_Cal(32, 0x01, 0x01);//显示数字0
    }
    
   if (work_num[1].Speed.Display_Set > 99) // 大于99时
   {
       Val = work_num[1].Speed.Display_Set / 100 % 10;
       switch (Val)
       {
       case 0:
            bit_Cal(33, 0x03, 0x03);bit_Cal(34, 0x07, 0x05);bit_Cal(35, 0x03, 0x03);
            break;
       case 1:
            bit_Cal(33, 0x03, 0x00);bit_Cal(34, 0x07, 0x00);bit_Cal(35, 0x03, 0x03);
            break;
       case 2:
            bit_Cal(33, 0x03, 0x02);bit_Cal(34, 0x07, 0x07);bit_Cal(35, 0x03, 0x01);
            break;
       case 3:
            bit_Cal(33, 0x03, 0x00);bit_Cal(34, 0x07, 0x07);bit_Cal(35, 0x03, 0x03);
            break;
       case 4:
            bit_Cal(33, 0x03, 0x01);bit_Cal(34, 0x07, 0x02);bit_Cal(35, 0x03, 0x03);
            break;
       case 5:
            bit_Cal(33, 0x03, 0x01);bit_Cal(34, 0x07, 0x07);bit_Cal(35, 0x03, 0x02);
            break;
       case 6:
            bit_Cal(33, 0x03, 0x03);bit_Cal(34, 0x07, 0x07);bit_Cal(35, 0x03, 0x02);
            break;
       case 7:
            bit_Cal(33, 0x03, 0x00);bit_Cal(34, 0x07, 0x01);bit_Cal(35, 0x03, 0x03);
            break;
       case 8:
            bit_Cal(33, 0x03, 0x03);bit_Cal(34, 0x07, 0x07);bit_Cal(35, 0x03, 0x03);
            break;
       case 9:
            bit_Cal(33, 0x03, 0x01);bit_Cal(34, 0x07, 0x07);bit_Cal(35, 0x03, 0x03);
            break;
       default:
           break;
       }
   }
   else
   {
        bit_Cal(33, 0x03, 0x03);bit_Cal(34, 0x07, 0x05);bit_Cal(35, 0x03, 0x03);//显示数字零
   }

   if (work_num[1].Speed.Display_Set > 9) // 大于9时
   {
       Val = work_num[1].Speed.Display_Set / 10 % 10;
       switch (Val)
       {
       case 0:
            bit_Cal(36, 0x03, 0x03);bit_Cal(37, 0x07, 0x05);bit_Cal(38, 0x03, 0x03);
            break;
       case 1:
            bit_Cal(36, 0x03, 0x00);bit_Cal(37, 0x07, 0x00);bit_Cal(38, 0x03, 0x03);
            break;
       case 2:
            bit_Cal(36, 0x03, 0x02);bit_Cal(37, 0x07, 0x07);bit_Cal(38, 0x03, 0x01);
            break;
       case 3:
            bit_Cal(36, 0x03, 0x00);bit_Cal(37, 0x07, 0x07);bit_Cal(38, 0x03, 0x03);
            break;
       case 4:
            bit_Cal(36, 0x03, 0x01);bit_Cal(37, 0x07, 0x02);bit_Cal(38, 0x03, 0x03);
            break;
       case 5:
            bit_Cal(36, 0x03, 0x01);bit_Cal(37, 0x07, 0x07);bit_Cal(38, 0x03, 0x02);
            break;
       case 6:
            bit_Cal(36, 0x03, 0x03);bit_Cal(37, 0x07, 0x07);bit_Cal(38, 0x03, 0x02);
            break;
       case 7:
            bit_Cal(36, 0x03, 0x00);bit_Cal(37, 0x07, 0x01);bit_Cal(38, 0x03, 0x03);
            break;
       case 8:
            bit_Cal(36, 0x03, 0x03);bit_Cal(37, 0x07, 0x07);bit_Cal(38, 0x03, 0x03);
            break;
       case 9:
            bit_Cal(36, 0x03, 0x01);bit_Cal(37, 0x07, 0x07);bit_Cal(38, 0x03, 0x03);
            break;
       default:
           break;
       }
   }
   else
   {
        bit_Cal(36, 0x03, 0x03);bit_Cal(37, 0x07, 0x05);bit_Cal(38, 0x03, 0x03);//显示数字零
   }
    bit_Cal(39, 0x01, 0x01);//实际转速个位只能显示零

    /**********工位2的实际温度显示**********/
    if (work_num[1].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[1].Temp.Display_Rel / 1000 % 10;
    }
    else if (work_num[1].Temp.Display_Rel < 0 && work_num[1].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[1].Temp.Display_Rel) / 1000 % 10;//计算后是0，不大于999所以不会显示
    }
    else if (work_num[1].Temp.Display_Rel <= -100 && work_num[1].Temp.Display_Rel > -1000)
    {
        Val = 10;//显示“-”
    }
    switch (Val)
    {
        case 0:
            if (work_num[1].Temp.Display_Rel > 999)//显示0
            {
                bit_Cal(20, 0x30, 0x30);bit_Cal(21, 0x1C, 0x14);bit_Cal(22, 0x0C, 0x0C);
            }
            else//不显示这位
            {
                bit_Cal(20, 0x30, 0x00);bit_Cal(21, 0x1C, 0x00);bit_Cal(22, 0x0C, 0x00);
            }
            break;
        case 1:
            bit_Cal(20, 0x30, 0x00);bit_Cal(21, 0x1C, 0x00);bit_Cal(22, 0x0C, 0x0C);
            break;
        case 2:
            bit_Cal(20, 0x30, 0x20);bit_Cal(21, 0x1C, 0x1C);bit_Cal(22, 0x0C, 0x04);
            break;
        case 3:
            bit_Cal(20, 0x30, 0x00);bit_Cal(21, 0x1C, 0x1C);bit_Cal(22, 0x0C, 0x0C);
            break;
        case 4:
            bit_Cal(20, 0x30, 0x10);bit_Cal(21, 0x1C, 0x08);bit_Cal(22, 0x0C, 0x0C);
            break;
        case 5:
            bit_Cal(20, 0x30, 0x10);bit_Cal(21, 0x1C, 0x1C);bit_Cal(22, 0x0C, 0x08);
            break;
        case 6:
            bit_Cal(20, 0x30, 0x30);bit_Cal(21, 0x1C, 0x1C);bit_Cal(22, 0x0C, 0x08);
            break;
        case 7:
            bit_Cal(20, 0x30, 0x00);bit_Cal(21, 0x1C, 0x04);bit_Cal(22, 0x0C, 0x0C);
            break;
        case 8:
            bit_Cal(20, 0x30, 0x30);bit_Cal(21, 0x1C, 0x1C);bit_Cal(22, 0x0C, 0x0C);
            break;
        case 9:
            bit_Cal(20, 0x30, 0x10);bit_Cal(21, 0x1C, 0x1C);bit_Cal(22, 0x0C, 0x0C);
            break;
        default:
            bit_Cal(20, 0x30, 0x00);bit_Cal(21, 0x1C, 0x08);bit_Cal(22, 0x0C, 0x00);//显示“-”
            break;
    }

    if (work_num[1].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[1].Temp.Display_Rel / 100 % 10;
    }
    else if (work_num[1].Temp.Display_Rel < 0 && work_num[1].Temp.Display_Rel > -100)
    {
        Val = 10;//显示“-”
    }
    else if (work_num[1].Temp.Display_Rel <= -100 && work_num[1].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[1].Temp.Display_Rel)/ 100 % 10;
    }
    switch (Val)
    {
        case 0:
            if (work_num[1].Temp.Display_Rel > 99)//显示零
            {
                bit_Cal(22, 0x02, 0x02);bit_Cal(23, 0x0E, 0x0A);bit_Cal(24, 0x1C, 0x1C);
            }
            else//不显示
            {
                bit_Cal(22, 0x02, 0x00);bit_Cal(23, 0x0E, 0x00);bit_Cal(24, 0x1C, 0x00);
            }
            break;
        case 1:
            bit_Cal(22, 0x02, 0x00);bit_Cal(23, 0x0E, 0x00);bit_Cal(24, 0x1C, 0x0C);
            break;
        case 2:
            bit_Cal(22, 0x02, 0x00);bit_Cal(23, 0x0E, 0x0E);bit_Cal(24, 0x1C, 0x14);
            break;
        case 3:
            bit_Cal(22, 0x02, 0x00);bit_Cal(23, 0x0E, 0x06);bit_Cal(24, 0x1C, 0x1C);
            break;
        case 4:
            bit_Cal(22, 0x02, 0x02);bit_Cal(23, 0x0E, 0x04);bit_Cal(24, 0x1C, 0x0C);
            break;
        case 5:
            bit_Cal(22, 0x02, 0x02);bit_Cal(23, 0x0E, 0x06);bit_Cal(24, 0x1C, 0x18);
            break;
        case 6:
            bit_Cal(22, 0x02, 0x02);bit_Cal(23, 0x0E, 0x0E);bit_Cal(24, 0x1C, 0x18);
            break;
        case 7:
            bit_Cal(22, 0x02, 0x00);bit_Cal(23, 0x0E, 0x02);bit_Cal(24, 0x1C, 0x0C);
            break;
        case 8:
            bit_Cal(22, 0x02, 0x02);bit_Cal(23, 0x0E, 0x0E);bit_Cal(24, 0x1C, 0x1C);
            break;
        case 9:
            bit_Cal(22, 0x02, 0x02);bit_Cal(23, 0x0E, 0x06);bit_Cal(24, 0x1C, 0x1C);
            break;
        default:
            bit_Cal(22, 0x02, 0x00);bit_Cal(23, 0x0E, 0x04);bit_Cal(24, 0x1C, 0x00);//显示“-”
            break;
    }

    if (work_num[1].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[1].Temp.Display_Rel / 10 % 10;
    }
    else if (work_num[1].Temp.Display_Rel < 0 && work_num[1].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[1].Temp.Display_Rel) / 10 % 10;
    }
    else if (work_num[1].Temp.Display_Rel <= -100 && work_num[1].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[1].Temp.Display_Rel) / 10 % 10;
    }
    switch (Val)
    {
    case 0:
        bit_Cal(25, 0x18, 0x18);bit_Cal(26, 0x1C, 0x14);bit_Cal(27, 0x0C, 0x0C);
        break;
    case 1:
        bit_Cal(25, 0x18, 0x00);bit_Cal(26, 0x1C, 0x00);bit_Cal(27, 0x0C, 0x0C);
        break;
    case 2:
        bit_Cal(25, 0x18, 0x10);bit_Cal(26, 0x1C, 0x1C);bit_Cal(27, 0x0C, 0x04);
        break;
    case 3:
        bit_Cal(25, 0x18, 0x00);bit_Cal(26, 0x1C, 0x1C);bit_Cal(27, 0x0C, 0x0C);
        break;
    case 4:
        bit_Cal(25, 0x18, 0x08);bit_Cal(26, 0x1C, 0x08);bit_Cal(27, 0x0C, 0x0C);
        break;
    case 5:
        bit_Cal(25, 0x18, 0x08);bit_Cal(26, 0x1C, 0x1C);bit_Cal(27, 0x0C, 0x08);
        break;
    case 6:
        bit_Cal(25, 0x18, 0x18);bit_Cal(26, 0x1C, 0x1C);bit_Cal(27, 0x0C, 0x08);
        break;
    case 7:
        bit_Cal(25, 0x18, 0x00);bit_Cal(26, 0x1C, 0x04);bit_Cal(27, 0x0C, 0x0C);
        break;
    case 8:
        bit_Cal(25, 0x18, 0x18);bit_Cal(26, 0x1C, 0x1C);bit_Cal(27, 0x0C, 0x0C);
        break;
    case 9:
        bit_Cal(25, 0x18, 0x08);bit_Cal(26, 0x1C, 0x1C);bit_Cal(27, 0x0C, 0x0C);
        break;
    default:
        bit_Cal(25, 0x18, 0x00);bit_Cal(26, 0x1C, 0x08);bit_Cal(27, 0x0C, 0x00);//显示“-”
        break;
    }

    if (work_num[1].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[1].Temp.Display_Rel / 10 % 10;
    }
    else if (work_num[1].Temp.Display_Rel < 0 && work_num[1].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[1].Temp.Display_Rel) % 10;
    }
    else if (work_num[1].Temp.Display_Rel <= -100 && work_num[1].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[1].Temp.Display_Rel) % 10;
    }
    switch (Val)
    {
        case 0:
            bit_Cal(28, 0x38, 0x38);bit_Cal(29, 0x1C, 0x14);bit_Cal(30, 0x04, 0x04);
            break;
        case 1:
            bit_Cal(28, 0x38, 0x00);bit_Cal(29, 0x1C, 0x10);bit_Cal(30, 0x04, 0x04);
            break;
        case 2:
            bit_Cal(28, 0x38, 0x30);bit_Cal(29, 0x1C, 0x0C);bit_Cal(30, 0x04, 0x04);
            break;
        case 3:
            bit_Cal(28, 0x38, 0x20);bit_Cal(29, 0x1C, 0x1C);bit_Cal(30, 0x04, 0x04);
            break;
        case 4:
            bit_Cal(28, 0x38, 0x08);bit_Cal(29, 0x1C, 0x18);bit_Cal(30, 0x04, 0x04);
            break;
        case 5:
            bit_Cal(28, 0x38, 0x28);bit_Cal(29, 0x1C, 0x1C);bit_Cal(30, 0x04, 0x00);
            break;
        case 6:
            bit_Cal(28, 0x38, 0x38);bit_Cal(29, 0x1C, 0x1C);bit_Cal(30, 0x04, 0x00);
            break;
        case 7:
            bit_Cal(28, 0x38, 0x00);bit_Cal(29, 0x1C, 0x14);bit_Cal(30, 0x04, 0x04);
            break;
        case 8:
            bit_Cal(28, 0x38, 0x38);bit_Cal(29, 0x1C, 0x1C);bit_Cal(30, 0x04, 0x04);
            break;
        case 9:
            bit_Cal(28, 0x38, 0x28);bit_Cal(29, 0x1C, 0x1C);bit_Cal(30, 0x04, 0x04);
            break;
        default:
            bit_Cal(28, 0x38, 0x00);bit_Cal(29, 0x1C, 0x08);bit_Cal(30, 0x04, 0x00);//显示“-”
            break;
    }

    /* 2号工位实际温度小数点 */
    bit_Cal(27, 0x10, 0x10);

    /**********工位2的设定温度显示**********/
    if (work_num[1].Temp.Display_Set >= 0)//大于等于0时
    {
        Val = work_num[1].Temp.Display_Set / 1000 % 10;
    }
    else if (work_num[1].Temp.Display_Set < 0 && work_num[1].Temp.Display_Set > -100)
    {
        Val = ABS(work_num[1].Temp.Display_Set) / 1000 % 10;//计算后是0，不大于999所以不会显示
    }
    else if (work_num[1].Temp.Display_Set <= -100 && work_num[1].Temp.Display_Set > -1000)
    {
        Val = 10;//显示“-”
    }
    switch (Val)
    {
        case 0:
            if (work_num[1].Temp.Display_Set > 999)//显示0
            {
                bit_Cal(30, 0x0A, 0x0A);bit_Cal(31, 0x0E, 0x0A);bit_Cal(32, 0x06, 0x06);
            }
            else//不显示这位
            {
                bit_Cal(30, 0x0A, 0x00);bit_Cal(31, 0x0E, 0x00);bit_Cal(32, 0x06, 0x00);
            }
            break;
        case 1:
            bit_Cal(30, 0x0A, 0x00);bit_Cal(31, 0x0E, 0x00);bit_Cal(32, 0x06, 0x06);
            break;
        case 2:
            bit_Cal(30, 0x0A, 0x08);bit_Cal(31, 0x0E, 0x0E);bit_Cal(32, 0x06, 0x02);
            break;
        case 3:
            bit_Cal(30, 0x0A, 0x00);bit_Cal(31, 0x0E, 0x0E);bit_Cal(32, 0x06, 0x06);
            break;
        case 4:
            bit_Cal(30, 0x0A, 0x02);bit_Cal(31, 0x0E, 0x04);bit_Cal(32, 0x06, 0x06);
            break;
        case 5:
            bit_Cal(30, 0x0A, 0x02);bit_Cal(31, 0x0E, 0x0E);bit_Cal(32, 0x06, 0x04);
            break;
        case 6:
            bit_Cal(30, 0x0A, 0x0A);bit_Cal(31, 0x0E, 0x0E);bit_Cal(32, 0x06, 0x04);
            break;
        case 7:
            bit_Cal(30, 0x0A, 0x00);bit_Cal(31, 0x0E, 0x02);bit_Cal(32, 0x06, 0x06);
            break;
        case 8:
            bit_Cal(30, 0x0A, 0x0A);bit_Cal(31, 0x0E, 0x0E);bit_Cal(32, 0x06, 0x06);
            break;
        case 9:
            bit_Cal(30, 0x0A, 0x02);bit_Cal(31, 0x0E, 0x0E);bit_Cal(32, 0x06, 0x06);
            break;
        default:
            bit_Cal(30, 0x0A, 0x00);bit_Cal(31, 0x0E, 0x04);bit_Cal(32, 0x06, 0x00);//显示“-”
            break;
    }

    if (work_num[1].Temp.Display_Set >= 0)//大于等于0时
    {
        Val = work_num[1].Temp.Display_Set / 100 % 10;
    }
    else if (work_num[1].Temp.Display_Set < 0 && work_num[1].Temp.Display_Set > -100)
    {
        Val = 10;//显示“-”
    }
    else if (work_num[1].Temp.Display_Set <= -100 && work_num[1].Temp.Display_Set > -1000)
    {
        Val = ABS(work_num[1].Temp.Display_Set)/ 100 % 10;
    }
    switch (Val)
    {
        case 0:
            if (work_num[1].Temp.Display_Set > 99)//显示零
            {
                bit_Cal(32, 0x08, 0x08);bit_Cal(33, 0x1C, 0x14);bit_Cal(34, 0x38, 0x38);
            }
            else//不显示
            {
                bit_Cal(32, 0x08, 0x00);bit_Cal(33, 0x1C, 0x00);bit_Cal(34, 0x38, 0x00);
            }
            break;
        case 1:
            bit_Cal(32, 0x08, 0x00);bit_Cal(33, 0x1C, 0x00);bit_Cal(34, 0x38, 0x30);
            break;
        case 2:
            bit_Cal(32, 0x08, 0x08);bit_Cal(33, 0x1C, 0x18);bit_Cal(34, 0x38, 0x18);
            break;
        case 3:
            bit_Cal(32, 0x08, 0x00);bit_Cal(33, 0x1C, 0x18);bit_Cal(34, 0x38, 0x38);
            break;
        case 4:
            bit_Cal(32, 0x08, 0x00);bit_Cal(33, 0x1C, 0x0C);bit_Cal(34, 0x38, 0x30);
            break;
        case 5:
            bit_Cal(32, 0x08, 0x00);bit_Cal(33, 0x1C, 0x1C);bit_Cal(34, 0x38, 0x28);
            break;
        case 6:
            bit_Cal(32, 0x08, 0x08);bit_Cal(33, 0x1C, 0x1C);bit_Cal(34, 0x38, 0x28);
            break;
        case 7:
            bit_Cal(32, 0x08, 0x00);bit_Cal(33, 0x1C, 0x00);bit_Cal(34, 0x38, 0x38);
            break;
        case 8:
            bit_Cal(32, 0x08, 0x08);bit_Cal(33, 0x1C, 0x1C);bit_Cal(34, 0x38, 0x38);
            break;
        case 9:
            bit_Cal(32, 0x08, 0x00);bit_Cal(33, 0x1C, 0x1C);bit_Cal(34, 0x38, 0x38);
            break;
        default:
            bit_Cal(32, 0x08, 0x00);bit_Cal(33, 0x1C, 0x08);bit_Cal(34, 0x38, 0x00);//显示“-”
            break;
    }

    if (work_num[1].Temp.Display_Set >= 0)//大于等于0时
    {
        Val = work_num[1].Temp.Display_Set / 10 % 10;
    }
    else if (work_num[1].Temp.Display_Set < 0 && work_num[1].Temp.Display_Set > -100)
    {
        Val = ABS(work_num[1].Temp.Display_Set) / 10 % 10;
    }
    else if (work_num[1].Temp.Display_Set <= -100 && work_num[1].Temp.Display_Set > -1000)
    {
        Val = ABS(work_num[1].Temp.Display_Set) / 10 % 10;
    }
    switch (Val)
    {
        case 0:
            bit_Cal(35, 0x1C, 0x1C);bit_Cal(36, 0x1C, 0x14);bit_Cal(37, 0x08, 0x08);
            break;
        case 1:
            bit_Cal(35, 0x1C, 0x00);bit_Cal(36, 0x1C, 0x10);bit_Cal(37, 0x08, 0x08);
            break;
        case 2:
            bit_Cal(35, 0x1C, 0x18);bit_Cal(36, 0x1C, 0x0C);bit_Cal(37, 0x08, 0x08);
            break;
        case 3:
            bit_Cal(35, 0x1C, 0x10);bit_Cal(36, 0x1C, 0x1C);bit_Cal(37, 0x08, 0x08);
            break;
        case 4:
            bit_Cal(35, 0x1C, 0x04);bit_Cal(36, 0x1C, 0x18);bit_Cal(37, 0x08, 0x08);
            break;
        case 5:
            bit_Cal(35, 0x1C, 0x14);bit_Cal(36, 0x1C, 0x1C);bit_Cal(37, 0x08, 0x00);
            break;
        case 6:
            bit_Cal(35, 0x1C, 0x1C);bit_Cal(36, 0x1C, 0x1C);bit_Cal(37, 0x08, 0x00);
            break;
        case 7:
            bit_Cal(35, 0x1C, 0x00);bit_Cal(36, 0x1C, 0x14);bit_Cal(37, 0x08, 0x08);
            break;
        case 8:
            bit_Cal(35, 0x1C, 0x1C);bit_Cal(36, 0x1C, 0x1C);bit_Cal(37, 0x08, 0x08);
            break;
        case 9:
            bit_Cal(35, 0x1C, 0x14);bit_Cal(36, 0x1C, 0x1C);bit_Cal(37, 0x08, 0x08);
            break;
        default:
            bit_Cal(35, 0x1C, 0x00);bit_Cal(36, 0x1C, 0x08);bit_Cal(37, 0x08, 0x00);//显示“-”
            break;
    }

    if (work_num[1].Temp.Display_Set >= 0)//大于等于0时
    {
        Val = work_num[1].Temp.Display_Set / 10 % 10;
    }
    else if (work_num[1].Temp.Display_Set < 0 && work_num[1].Temp.Display_Set > -100)
    {
        Val = ABS(work_num[1].Temp.Display_Set) % 10;
    }
    else if (work_num[1].Temp.Display_Set <= -100 && work_num[1].Temp.Display_Set > -1000)
    {
        Val = ABS(work_num[1].Temp.Display_Set) % 10;
    }
    switch (Val)
    {
        case 0:
            bit_Cal(38, 0x3C, 0x3C);bit_Cal(39, 0x38, 0x28);
            break;
        case 1:
            bit_Cal(38, 0x3C, 0x00);bit_Cal(39, 0x38, 0x28);
            break;
        case 2:
            bit_Cal(38, 0x3C, 0x34);bit_Cal(39, 0x38, 0x18);
            break;
        case 3:
            bit_Cal(38, 0x3C, 0x24);bit_Cal(39, 0x38, 0x38);
            break;
        case 4:
            bit_Cal(38, 0x3C, 0x08);bit_Cal(39, 0x38, 0x38);
            break;
        case 5:
            bit_Cal(38, 0x3C, 0x2C);bit_Cal(39, 0x38, 0x30);
            break;
        case 6:
            bit_Cal(38, 0x3C, 0x3C);bit_Cal(39, 0x38, 0x30);
            break;
        case 7:
            bit_Cal(38, 0x3C, 0x04);bit_Cal(39, 0x38, 0x28);
            break;
        case 8:
            bit_Cal(38, 0x3C, 0x3C);bit_Cal(39, 0x38, 0x38);
            break;
        case 9:
            bit_Cal(38, 0x3C, 0x2C);bit_Cal(39, 0x38, 0x38);
            break;
        default:
            bit_Cal(38, 0x3C, 0x00);bit_Cal(39, 0x38, 0x10);//显示“-”
            break;
    }
    /* 2号工位设定温度小数点 */
    bit_Cal(37, 0x10, 0x10);

    /**********工位2的实际时间显示**********/
    Val = work_num[1].Time.Display_Rel / 3600 / 10;//计算十位为单位的小时数
    switch (Val)
    {
        case 0:
            bit_Cal(21, 0xE0, 0x60);bit_Cal(22, 0xE0, 0xE0);
            break;
        case 1:
            bit_Cal(21, 0xE0, 0x00);bit_Cal(22, 0xE0, 0x60);
            break;
        case 2:
            bit_Cal(21, 0xE0, 0xA0);bit_Cal(22, 0xE0, 0xA0);
            break;
        default:
            bit_Cal(21, 0xE0, 0x80);bit_Cal(22, 0xE0, 0x00);//显示“-”
            break;
    }

    Val = work_num[1].Time.Display_Rel / 3600 % 10;// 计算个位为单位的小时数
    switch (Val)
    {
        case 0:
            bit_Cal(22, 0x10, 0x10);bit_Cal(23, 0xF0, 0xD0);bit_Cal(24, 0x60, 0x60);
            break;
        case 1:
            bit_Cal(22, 0x10, 0x00);bit_Cal(23, 0xF0, 0x00);bit_Cal(24, 0x60, 0x60);
            break;
        case 2:
            bit_Cal(22, 0x10, 0x00);bit_Cal(23, 0xF0, 0xF0);bit_Cal(24, 0x60, 0x20);
            break;
        case 3:
            bit_Cal(22, 0x10, 0x00);bit_Cal(23, 0xF0, 0xB0);bit_Cal(24, 0x60, 0x60);
            break;
        case 4:
            bit_Cal(22, 0x10, 0x10);bit_Cal(23, 0xF0, 0x20);bit_Cal(24, 0x60, 0x60);
            break;
        case 5:
            bit_Cal(22, 0x10, 0x10);bit_Cal(23, 0xF0, 0xB0);bit_Cal(24, 0x60, 0x40);
            break;
        case 6:
            bit_Cal(22, 0x10, 0x10);bit_Cal(23, 0xF0, 0xF0);bit_Cal(24, 0x60, 0x40);
            break;
        case 7:
            bit_Cal(22, 0x10, 0x00);bit_Cal(23, 0xF0, 0x10);bit_Cal(24, 0x60, 0x60);
            break;
        case 8:
            bit_Cal(22, 0x10, 0x10);bit_Cal(23, 0xF0, 0xF0);bit_Cal(24, 0x60, 0x60);
            break;
        case 9:
            bit_Cal(22, 0x10, 0x10);bit_Cal(23, 0xF0, 0xB0);bit_Cal(24, 0x60, 0x60);
            break;
        default:
            bit_Cal(22, 0x10, 0x00);bit_Cal(23, 0xF0, 0x20);bit_Cal(24, 0x60, 0x00);//显示“-”
            break;
    }

    Val = work_num[1].Time.Display_Rel % 3600 / 60 / 10; // 计算十分位为单位的分钟数
    switch (Val)
    {
        case 0:
            bit_Cal(25, 0xE0, 0xA0);bit_Cal(26, 0xE0, 0xE0);bit_Cal(39, 0x80, 0x80);
            break;
        case 1:
            bit_Cal(25, 0xE0, 0x00);bit_Cal(26, 0xE0, 0xC0);bit_Cal(39, 0x80, 0x00);
            break;
        case 2:
            bit_Cal(25, 0xE0, 0xC0);bit_Cal(26, 0xE0, 0x60);bit_Cal(39, 0x80, 0x80);
            break;
        case 3:
            bit_Cal(25, 0xE0, 0x40);bit_Cal(26, 0xE0, 0xE0);bit_Cal(39, 0x80, 0x80);
            break;
        case 4:
            bit_Cal(25, 0xE0, 0x60);bit_Cal(26, 0xE0, 0xC0);bit_Cal(39, 0x80, 0x00);
            break;
        case 5:
            bit_Cal(25, 0xE0, 0x60);bit_Cal(26, 0xE0, 0xA0);bit_Cal(39, 0x80, 0x80);
            break;
        case 6:
            bit_Cal(25, 0xE0, 0xE0);bit_Cal(26, 0xE0, 0xA0);bit_Cal(39, 0x80, 0x80);
            break;
        case 7:
            bit_Cal(25, 0xE0, 0x00);bit_Cal(26, 0xE0, 0xE0);bit_Cal(39, 0x80, 0x00);
            break;
        case 8:
            bit_Cal(25, 0xE0, 0xE0);bit_Cal(26, 0xE0, 0xE0);bit_Cal(39, 0x80, 0x80);
            break;
        case 9:
            bit_Cal(25, 0xE0, 0x60);bit_Cal(26, 0xE0, 0xE0);bit_Cal(39, 0x80, 0x80);
            break;
        default:
            bit_Cal(25, 0xE0, 0x40);bit_Cal(26, 0xE0, 0x00);bit_Cal(39, 0x80, 0x00);//显示“-”
            break;
    }

    Val = work_num[1].Time.Display_Rel % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
    switch (Val)
    {
        case 0:
            bit_Cal(27, 0xE0, 0xA0);bit_Cal(28, 0xC0, 0xC0);bit_Cal(29, 0x80, 0x80);bit_Cal(30, 0x80, 0x80);
            break;
        case 1:
            bit_Cal(27, 0xE0, 0x00);bit_Cal(28, 0xC0, 0x80);bit_Cal(29, 0x80, 0x80);bit_Cal(30, 0x80, 0x00);
            break;
        case 2:
            bit_Cal(27, 0xE0, 0xC0);bit_Cal(28, 0xC0, 0xC0);bit_Cal(29, 0x80, 0x00);bit_Cal(30, 0x80, 0x80);
            break;
        case 3:
            bit_Cal(27, 0xE0, 0x40);bit_Cal(28, 0xC0, 0xC0);bit_Cal(29, 0x80, 0x80);bit_Cal(30, 0x80, 0x80);
            break;
        case 4:
            bit_Cal(27, 0xE0, 0x60);bit_Cal(28, 0xC0, 0x90);bit_Cal(29, 0x80, 0x80);bit_Cal(30, 0x80, 0x00);
            break;
        case 5:
            bit_Cal(27, 0xE0, 0x60);bit_Cal(28, 0xC0, 0x40);bit_Cal(29, 0x80, 0x80);bit_Cal(30, 0x80, 0x80);
            break;
        case 6:
            bit_Cal(27, 0xE0, 0xE0);bit_Cal(28, 0xC0, 0x40);bit_Cal(29, 0x80, 0x80);bit_Cal(30, 0x80, 0x80);
            break;
        case 7:
            bit_Cal(27, 0xE0, 0x00);bit_Cal(28, 0xC0, 0xC0);bit_Cal(29, 0x80, 0x80);bit_Cal(30, 0x80, 0x00);
            break;
        case 8:
            bit_Cal(27, 0xE0, 0xE0);bit_Cal(28, 0xC0, 0xC0);bit_Cal(29, 0x80, 0x80);bit_Cal(30, 0x80, 0x80);
            break;
        case 9:
            bit_Cal(27, 0xE0, 0x60);bit_Cal(28, 0xC0, 0xC0);bit_Cal(29, 0x80, 0x80);bit_Cal(30, 0x80, 0x80);
            break;
        default:
            bit_Cal(27, 0xE0, 0x40);bit_Cal(28, 0xC0, 0x00);bit_Cal(29, 0x80, 0x00);bit_Cal(30, 0x80, 0x00);//显示“-”
            break;
    }
    /* 2号工位实际时间冒号 */
    bit_Cal(24, 0x80, 0x80);

    /**********工位2的设定时间显示**********/
    Val = work_num[1].Time.Display_Set / 3600 / 10;//计算十位为单位的小时数
    switch (Val)
    {
        case 0:
            bit_Cal(29, 0x60, 0x60);bit_Cal(30, 0x70, 0x50);bit_Cal(31, 0x50, 0x50);
            break;
        case 1:
            bit_Cal(29, 0x60, 0x00);bit_Cal(30, 0x70, 0x00);bit_Cal(31, 0x50, 0x50);
            break;
        case 2:
            bit_Cal(29, 0x60, 0x40);bit_Cal(30, 0x70, 0x70);bit_Cal(31, 0x50, 0x10);
            break;
        default:
            bit_Cal(29, 0x60, 0x00);bit_Cal(30, 0x70, 0x20);bit_Cal(31, 0x50, 0x00);//显示“-”
            break;
    }

    Val = work_num[1].Time.Display_Set / 3600 % 10;// 计算个位为单位的小时数
    switch (Val)
    {
        case 0:
            bit_Cal(31, 0x20, 0x20);bit_Cal(32, 0xF0, 0xD0);bit_Cal(33, 0x60, 0x60);
            break;
        case 1:
            bit_Cal(31, 0x20, 0x00);bit_Cal(32, 0xF0, 0x00);bit_Cal(33, 0x60, 0x60);
            break;
        case 2:
            bit_Cal(31, 0x20, 0x00);bit_Cal(32, 0xF0, 0xF0);bit_Cal(33, 0x60, 0x20);
            break;
        case 3:
            bit_Cal(31, 0x20, 0x00);bit_Cal(32, 0xF0, 0xB0);bit_Cal(33, 0x60, 0x60);
            break;
        case 4:
            bit_Cal(31, 0x20, 0x20);bit_Cal(32, 0xF0, 0x20);bit_Cal(33, 0x60, 0x60);
            break;
        case 5:
            bit_Cal(31, 0x20, 0x20);bit_Cal(32, 0xF0, 0xB0);bit_Cal(33, 0x60, 0x40);
            break;
        case 6:
            bit_Cal(31, 0x20, 0x20);bit_Cal(32, 0xF0, 0xF0);bit_Cal(33, 0x60, 0x40);
            break;
        case 7:
            bit_Cal(31, 0x20, 0x00);bit_Cal(32, 0xF0, 0x10);bit_Cal(33, 0x60, 0x60);
            break;
        case 8:
            bit_Cal(31, 0x20, 0x20);bit_Cal(32, 0xF0, 0xF0);bit_Cal(33, 0x60, 0x60);
            break;
        case 9:
            bit_Cal(31, 0x20, 0x20);bit_Cal(32, 0xF0, 0xB0);bit_Cal(33, 0x60, 0x60);
            break;
        default:
            bit_Cal(31, 0x20, 0x00);bit_Cal(32, 0xF0, 0x20);bit_Cal(33, 0x60, 0x00);//显示“-”
            break;
    }

    Val = work_num[1].Time.Display_Set % 3600 / 60 / 10; // 计算十分位为单位的分钟数
    switch (Val)
    {
        case 0:
            bit_Cal(31, 0x80, 0x80);bit_Cal(34, 0xC0, 0x40);bit_Cal(35, 0xE0, 0xE0);bit_Cal(36, 0x80, 0x80);
            break;
        case 1:
            bit_Cal(31, 0x80, 0x00);bit_Cal(34, 0xC0, 0x00);bit_Cal(35, 0xE0, 0xC0);bit_Cal(36, 0x80, 0x00);
            break;
        case 2:
            bit_Cal(31, 0x80, 0x80);bit_Cal(34, 0xC0, 0x80);bit_Cal(35, 0xE0, 0x60);bit_Cal(36, 0x80, 0x80);
            break;
        case 3:
            bit_Cal(31, 0x80, 0x00);bit_Cal(34, 0xC0, 0x80);bit_Cal(35, 0xE0, 0xE0);bit_Cal(36, 0x80, 0x80);
            break;
        case 4:
            bit_Cal(31, 0x80, 0x00);bit_Cal(34, 0xC0, 0xC0);bit_Cal(35, 0xE0, 0xC0);bit_Cal(36, 0x80, 0x00);
            break;
        case 5:
            bit_Cal(31, 0x80, 0x00);bit_Cal(34, 0xC0, 0xC0);bit_Cal(35, 0xE0, 0xA0);bit_Cal(36, 0x80, 0x80);
            break;
        case 6:
            bit_Cal(31, 0x80, 0x80);bit_Cal(34, 0xC0, 0xC0);bit_Cal(35, 0xE0, 0xA0);bit_Cal(36, 0x80, 0x80);
            break;
        case 7:
            bit_Cal(31, 0x80, 0x00);bit_Cal(34, 0xC0, 0x00);bit_Cal(35, 0xE0, 0xE0);bit_Cal(36, 0x80, 0x00);
            break;
        case 8:
            bit_Cal(31, 0x80, 0x80);bit_Cal(34, 0xC0, 0xC0);bit_Cal(35, 0xE0, 0xE0);bit_Cal(36, 0x80, 0x80);
            break;
        case 9:
            bit_Cal(31, 0x80, 0x00);bit_Cal(34, 0xC0, 0xC0);bit_Cal(35, 0xE0, 0xE0);bit_Cal(36, 0x80, 0x80);
            break;
        default:
            bit_Cal(31, 0x80, 0x00);bit_Cal(34, 0xC0, 0x80);bit_Cal(35, 0xE0, 0x00);bit_Cal(36, 0x80, 0x00);//显示“-”
            break;
    }

    Val = work_num[1].Time.Display_Set % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
    switch (Val)
    {
        case 0:
            bit_Cal(36, 0x60, 0x60);bit_Cal(37, 0xE0, 0xA0);bit_Cal(38, 0xC0, 0xC0);
            break;
        case 1:
            bit_Cal(36, 0x60, 0x00);bit_Cal(37, 0xE0, 0x00);bit_Cal(38, 0xC0, 0xC0);
            break;
        case 2:
            bit_Cal(36, 0x60, 0x40);bit_Cal(37, 0xE0, 0xE0);bit_Cal(38, 0xC0, 0x40);
            break;
        case 3:
            bit_Cal(36, 0x60, 0x00);bit_Cal(37, 0xE0, 0xE0);bit_Cal(38, 0xC0, 0xC0);
            break;
        case 4:
            bit_Cal(36, 0x60, 0x20);bit_Cal(37, 0xE0, 0x40);bit_Cal(38, 0xC0, 0xC0);
            break;
        case 5:
            bit_Cal(36, 0x60, 0x20);bit_Cal(37, 0xE0, 0xE0);bit_Cal(38, 0xC0, 0x80);
            break;
        case 6:
            bit_Cal(36, 0x60, 0x60);bit_Cal(37, 0xE0, 0xE0);bit_Cal(38, 0xC0, 0x80);
            break;
        case 7:
            bit_Cal(36, 0x60, 0x00);bit_Cal(37, 0xE0, 0x20);bit_Cal(38, 0xC0, 0xC0);
            break;
        case 8:
            bit_Cal(36, 0x60, 0x60);bit_Cal(37, 0xE0, 0xE0);bit_Cal(38, 0xC0, 0xC0);
            break;
        case 9:
            bit_Cal(36, 0x60, 0x20);bit_Cal(37, 0xE0, 0xE0);bit_Cal(38, 0xC0, 0xC0);
            break;
        default:
            bit_Cal(36, 0x60, 0x00);bit_Cal(37, 0xE0, 0x40);bit_Cal(38, 0xC0, 0x00);//显示“-”
            break;
    }
    /* 2号工位设定时间冒号 */
    bit_Cal(33, 0x80, 0x80);
    /* 2号工位“rpm”图标 */
    bit_Cal(39, 0x02, 0x02);
    
    /* 2号工位“℃”图标 */
    bit_Cal(39, 0x04, 0x04);

    /* 2号工位“min”图标 */
    bit_Cal(39, 0x40, 0x40);

    /* 2号工位与3号工位之间横线 */
    bit_Cal(20, 0x80, 0x80);

    /* 2号工位转速图标 */
    bit_Cal(20, 0x01, 0x01);//2号工位转速图标S70
    bit_Cal(21, 0x01, 0x01);//2号工位转速图标S71
    bit_Cal(21, 0x02, 0x02);//2号工位转速图标S72
    
    /* 2号工位加热图标 */
    bit_Cal(20, 0x02, 0x02);//2号工位加热图标S73
    bit_Cal(20, 0x04, 0x04);//2号工位加热图标S74
    bit_Cal(20, 0x08, 0x08);//2号工位温度探头图标
    
    /* 2号工位时间图标 */
    bit_Cal(20, 0x40, 0x40);//2号工位时间图标
    
    /**********数据发送**********/
    for(uint8_t i=0;i<40;i++)/* 1号工位与3号工位之间横线 */
    {
        Write_Addr_Dat_N(IC2, i, seg[i], 1);
    }
}

void Display_IC1(_Work_Num_ work_num[])
{
    uint8_t Val;// 用于百十个取出来的数字

    /*******************************3号工位*******************************/
    /**********工位3的实际转速显示**********/
    if (work_num[2].Speed.Display_Rel > 999) // 大于999时
    {
        Val = work_num[2].Speed.Display_Rel / 1000 % 10;
       if(Val > 0)
        {
            bit_Cal(78, 0x02, 0x00);bit_Cal(77, 0x02, 0x02);//显示数字1
        }
       else
       {
            bit_Cal(78, 0x02, 0x02);bit_Cal(77, 0x02, 0x02);//显示数字0
       }
    }
    else
    {
        bit_Cal(78, 0x02, 0x02);bit_Cal(77, 0x02, 0x02);//显示数字0
    }
    
   if (work_num[2].Speed.Display_Rel > 99) // 大于99时
   {
       Val = work_num[2].Speed.Display_Rel / 100 % 10;
       switch (Val)
       {
       case 0:
            bit_Cal(77, 0x01, 0x01);bit_Cal(76, 0x07, 0x07);bit_Cal(75, 0x03, 0x02);bit_Cal(74, 0x02, 0x02);
            break;
       case 1:
            bit_Cal(77, 0x01, 0x00);bit_Cal(76, 0x07, 0x01);bit_Cal(75, 0x03, 0x00);bit_Cal(74, 0x02, 0x02);
            break;
       case 2:
            bit_Cal(77, 0x01, 0x01);bit_Cal(76, 0x07, 0x05);bit_Cal(75, 0x03, 0x03);bit_Cal(74, 0x02, 0x00);
            break;
       case 3:
            bit_Cal(77, 0x01, 0x01);bit_Cal(76, 0x07, 0x01);bit_Cal(75, 0x03, 0x03);bit_Cal(74, 0x02, 0x02);
            break;
       case 4:
            bit_Cal(77, 0x01, 0x00);bit_Cal(76, 0x07, 0x03);bit_Cal(75, 0x03, 0x01);bit_Cal(74, 0x02, 0x02);
            break;
       case 5:
            bit_Cal(77, 0x01, 0x01);bit_Cal(76, 0x07, 0x02);bit_Cal(75, 0x03, 0x03);bit_Cal(74, 0x02, 0x02);
            break;
       case 6:
            bit_Cal(77, 0x01, 0x01);bit_Cal(76, 0x07, 0x06);bit_Cal(75, 0x03, 0x03);bit_Cal(74, 0x02, 0x02);
            break;
       case 7:
            bit_Cal(77, 0x01, 0x01);bit_Cal(76, 0x07, 0x01);bit_Cal(75, 0x03, 0x00);bit_Cal(74, 0x02, 0x02);
            break;
       case 8:
            bit_Cal(77, 0x01, 0x01);bit_Cal(76, 0x07, 0x07);bit_Cal(75, 0x03, 0x03);bit_Cal(74, 0x02, 0x02);
            break;
       case 9:
            bit_Cal(77, 0x01, 0x01);bit_Cal(76, 0x07, 0x03);bit_Cal(75, 0x03, 0x03);bit_Cal(74, 0x02, 0x02);
            break;
       default:
           break;
       }
   }
   else
   {
        bit_Cal(77, 0x01, 0x01);bit_Cal(76, 0x07, 0x07);bit_Cal(75, 0x02, 0x02);bit_Cal(74, 0x02, 0x02);;//显示数字零
   }

   if (work_num[2].Speed.Display_Rel > 9) // 大于9时
   {
       Val = work_num[2].Speed.Display_Rel / 10 % 10;
       switch (Val)
       {
       case 0:
            bit_Cal(74, 0x01, 0x01);bit_Cal(73, 0x03, 0x03);bit_Cal(72, 0x03, 0x02);bit_Cal(71, 0x03, 0x03);
            break;
       case 1:
            bit_Cal(74, 0x01, 0x00);bit_Cal(73, 0x03, 0x00);bit_Cal(72, 0x03, 0x00);bit_Cal(71, 0x03, 0x03);
            break;
       case 2:
            bit_Cal(74, 0x01, 0x01);bit_Cal(73, 0x03, 0x02);bit_Cal(72, 0x03, 0x03);bit_Cal(71, 0x03, 0x01);
            break;
       case 3:
            bit_Cal(74, 0x01, 0x01);bit_Cal(73, 0x03, 0x00);bit_Cal(72, 0x03, 0x03);bit_Cal(71, 0x03, 0x03);
            break;
       case 4:
            bit_Cal(74, 0x01, 0x00);bit_Cal(73, 0x03, 0x01);bit_Cal(72, 0x03, 0x01);bit_Cal(71, 0x03, 0x03);
            break;
       case 5:
            bit_Cal(74, 0x01, 0x01);bit_Cal(73, 0x03, 0x01);bit_Cal(72, 0x03, 0x03);bit_Cal(71, 0x03, 0x02);
            break;
       case 6:
            bit_Cal(74, 0x01, 0x01);bit_Cal(73, 0x03, 0x03);bit_Cal(72, 0x03, 0x03);bit_Cal(71, 0x03, 0x02);
            break;
       case 7:
            bit_Cal(74, 0x01, 0x01);bit_Cal(73, 0x03, 0x00);bit_Cal(72, 0x03, 0x00);bit_Cal(71, 0x03, 0x03);
            break;
       case 8:
            bit_Cal(74, 0x01, 0x01);bit_Cal(73, 0x03, 0x03);bit_Cal(72, 0x03, 0x03);bit_Cal(71, 0x03, 0x03);
            break;
       case 9:
            bit_Cal(74, 0x01, 0x01);bit_Cal(73, 0x03, 0x01);bit_Cal(72, 0x03, 0x03);bit_Cal(71, 0x03, 0x03);
            break;
       default:
           break;
       }
   }
   else
   {
       bit_Cal(74, 0x01, 0x01);bit_Cal(73, 0x03, 0x03);bit_Cal(72, 0x03, 0x02);bit_Cal(71, 0x03, 0x03);//显示数字零
   }
    bit_Cal(70, 0x01, 0x01);//实际转速个位只能显示零

    /**********工位3的设定转速显示**********/
    if (work_num[2].Speed.Display_Set > 999) // 大于999时
    {
        Val = work_num[2].Speed.Display_Set / 1000 % 10;
       if(Val > 0)
        {
            bit_Cal(69, 0x01, 0x00);bit_Cal(68, 0x01, 0x01);//显示数字1
        }
       else
       {
            bit_Cal(69, 0x01, 0x01);bit_Cal(68, 0x01, 0x01);//显示数字0
       }
    }
    else
    {
        bit_Cal(69, 0x01, 0x01);bit_Cal(68, 0x01, 0x01);//显示数字0
    }
    
   if (work_num[2].Speed.Display_Set > 99) // 大于99时
   {
       Val = work_num[2].Speed.Display_Set / 100 % 10;
       switch (Val)
       {
       case 0:
            bit_Cal(67, 0x01, 0x01);bit_Cal(66, 0x01, 0x01);bit_Cal(65, 0x03, 0x02);bit_Cal(64, 0x03, 0x03);bit_Cal(63, 0x01, 0x01);
            break;
       case 1:
            bit_Cal(67, 0x01, 0x00);bit_Cal(66, 0x01, 0x00);bit_Cal(65, 0x03, 0x00);bit_Cal(64, 0x03, 0x01);bit_Cal(63, 0x01, 0x01);
            break;
       case 2:
            bit_Cal(67, 0x01, 0x01);bit_Cal(66, 0x01, 0x00);bit_Cal(65, 0x03, 0x03);bit_Cal(64, 0x03, 0x02);bit_Cal(63, 0x01, 0x01);
            break;
       case 3:
            bit_Cal(67, 0x01, 0x01);bit_Cal(66, 0x01, 0x00);bit_Cal(65, 0x03, 0x01);bit_Cal(64, 0x03, 0x03);bit_Cal(63, 0x01, 0x01);
            break;
       case 4:
            bit_Cal(67, 0x01, 0x00);bit_Cal(66, 0x01, 0x01);bit_Cal(65, 0x03, 0x01);bit_Cal(64, 0x03, 0x01);bit_Cal(63, 0x01, 0x01);
            break;
       case 5:
            bit_Cal(67, 0x01, 0x01);bit_Cal(66, 0x01, 0x01);bit_Cal(65, 0x03, 0x01);bit_Cal(64, 0x03, 0x03);bit_Cal(63, 0x01, 0x00);
            break;
       case 6:
            bit_Cal(67, 0x01, 0x01);bit_Cal(66, 0x01, 0x01);bit_Cal(65, 0x03, 0x03);bit_Cal(64, 0x03, 0x03);bit_Cal(63, 0x01, 0x00);
            break;
       case 7:
            bit_Cal(67, 0x01, 0x01);bit_Cal(66, 0x01, 0x00);bit_Cal(65, 0x03, 0x00);bit_Cal(64, 0x03, 0x01);bit_Cal(63, 0x01, 0x01);
            break;
       case 8:
            bit_Cal(67, 0x01, 0x01);bit_Cal(66, 0x01, 0x01);bit_Cal(65, 0x03, 0x03);bit_Cal(64, 0x03, 0x03);bit_Cal(63, 0x01, 0x01);
            break;
       case 9:
            bit_Cal(67, 0x01, 0x01);bit_Cal(66, 0x01, 0x01);bit_Cal(65, 0x03, 0x01);bit_Cal(64, 0x03, 0x03);bit_Cal(63, 0x01, 0x01);
            break;
       default:
           break;
       }
   }
   else
   {
        bit_Cal(67, 0x01, 0x01);bit_Cal(66, 0x01, 0x01);bit_Cal(65, 0x03, 0x02);bit_Cal(64, 0x03, 0x03);bit_Cal(63, 0x01, 0x01);//显示数字零
   }

   if (work_num[2].Speed.Display_Set > 9) // 大于9时
   {
        Val = work_num[2].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
            case 0:
                bit_Cal(63, 0x06, 0x06);bit_Cal(62, 0x07, 0x05);bit_Cal(61, 0x03, 0x03);
                break;
            case 1:
                bit_Cal(63, 0x06, 0x00);bit_Cal(62, 0x07, 0x04);bit_Cal(61, 0x03, 0x02);
                break;
            case 2:
                bit_Cal(63, 0x06, 0x06);bit_Cal(62, 0x07, 0x02);bit_Cal(61, 0x03, 0x03);
                break;
            case 3:
                bit_Cal(63, 0x06, 0x04);bit_Cal(62, 0x07, 0x06);bit_Cal(61, 0x03, 0x03);
                break;
            case 4:
                bit_Cal(63, 0x06, 0x00);bit_Cal(62, 0x07, 0x07);bit_Cal(61, 0x03, 0x02);
                break;
            case 5:
                bit_Cal(63, 0x06, 0x04);bit_Cal(62, 0x07, 0x07);bit_Cal(61, 0x03, 0x01);
                break;
            case 6:
                bit_Cal(63, 0x06, 0x06);bit_Cal(62, 0x07, 0x07);bit_Cal(61, 0x03, 0x01);
                break;
            case 7:
                bit_Cal(63, 0x06, 0x00);bit_Cal(62, 0x07, 0x04);bit_Cal(61, 0x03, 0x03);
                break;
            case 8:
                bit_Cal(63, 0x06, 0x06);bit_Cal(62, 0x07, 0x07);bit_Cal(61, 0x03, 0x03);
                break;
            case 9:
                bit_Cal(63, 0x06, 0x04);bit_Cal(62, 0x07, 0x07);bit_Cal(61, 0x03, 0x03);
                break;
            default:
                break;
        }
    }
    else
    {
        bit_Cal(63, 0x06, 0x06);bit_Cal(62, 0x07, 0x05);bit_Cal(61, 0x03, 0x03);//显示数字零
    }
    bit_Cal(60, 0x02, 0x02);//实际转速个位只能显示零

    /**********工位3的实际温度显示**********/
    if (work_num[2].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[2].Temp.Display_Rel / 1000 % 10;
    }
    else if (work_num[2].Temp.Display_Rel < 0 && work_num[2].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[2].Temp.Display_Rel) / 1000 % 10;//计算后是0，不大于999所以不会显示
    }
    else if (work_num[2].Temp.Display_Rel <= -100 && work_num[2].Temp.Display_Rel > -1000)
    {
        Val = 10;//显示“-”
    }
    switch (Val)
    {
        case 0:
            if (work_num[2].Temp.Display_Rel > 999)//显示0
            {
                bit_Cal(78, 0x0C, 0x0C);bit_Cal(77, 0x1C, 0x14);bit_Cal(76, 0x18, 0x18);
            }
            else//不显示这位
            {
                bit_Cal(78, 0x0C, 0x00);bit_Cal(77, 0x1C, 0x00);bit_Cal(76, 0x18, 0x00);
            }
            break;
        case 1:
            bit_Cal(78, 0x0C, 0x00);bit_Cal(77, 0x1C, 0x00);bit_Cal(76, 0x18, 0x18);
            break;
        case 2:
            bit_Cal(78, 0x0C, 0x08);bit_Cal(77, 0x1C, 0x1C);bit_Cal(76, 0x18, 0x08);
            break;
        case 3:
            bit_Cal(78, 0x0C, 0x00);bit_Cal(77, 0x1C, 0x1C);bit_Cal(76, 0x18, 0x18);
            break;
        case 4:
            bit_Cal(78, 0x0C, 0x04);bit_Cal(77, 0x1C, 0x08);bit_Cal(76, 0x18, 0x18);
            break;
        case 5:
            bit_Cal(78, 0x0C, 0x04);bit_Cal(77, 0x1C, 0x1C);bit_Cal(76, 0x18, 0x10);
            break;
        case 6:
            bit_Cal(78, 0x0C, 0x0C);bit_Cal(77, 0x1C, 0x1C);bit_Cal(76, 0x18, 0x10);
            break;
        case 7:
            bit_Cal(78, 0x0C, 0x00);bit_Cal(77, 0x1C, 0x04);bit_Cal(76, 0x18, 0x18);
            break;
        case 8:
            bit_Cal(78, 0x0C, 0x0C);bit_Cal(77, 0x1C, 0x1C);bit_Cal(76, 0x18, 0x18);
            break;
        case 9:
            bit_Cal(78, 0x0C, 0x04);bit_Cal(77, 0x1C, 0x1C);bit_Cal(76, 0x18, 0x18);
            break;
        default:
            bit_Cal(78, 0x0C, 0x00);bit_Cal(77, 0x1C, 0x08);bit_Cal(76, 0x18, 0x00);//显示“-”
            break;
    }

    if (work_num[2].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[2].Temp.Display_Rel / 100 % 10;
    }
    else if (work_num[2].Temp.Display_Rel < 0 && work_num[2].Temp.Display_Rel > -100)
    {
        Val = 10;//显示“-”
    }
    else if (work_num[2].Temp.Display_Rel <= -100 && work_num[2].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[2].Temp.Display_Rel)/ 100 % 10;
    }
    switch (Val)
    {
        case 0:
            if (work_num[2].Temp.Display_Rel > 99)//显示零
            {
                bit_Cal(75, 0x3C, 0x3C);bit_Cal(74, 0x38, 0x2C);
            }
            else//不显示
            {
                bit_Cal(75, 0x3C, 0x00);bit_Cal(74, 0x38, 0x00);
            }
            break;
        case 1:
            bit_Cal(75, 0x3C, 0x00);bit_Cal(74, 0x38, 0x28);
            break;
        case 2:
            bit_Cal(75, 0x3C, 0x34);bit_Cal(74, 0x38, 0x18);
            break;
        case 3:
            bit_Cal(75, 0x3C, 0x24);bit_Cal(74, 0x38, 0x3C);
            break;
        case 4:
            bit_Cal(75, 0x3C, 0x08);bit_Cal(74, 0x38, 0x3C);
            break;
        case 5:
            bit_Cal(75, 0x3C, 0x2C);bit_Cal(74, 0x38, 0x30);
            break;
        case 6:
            bit_Cal(75, 0x3C, 0x3C);bit_Cal(74, 0x38, 0x30);
            break;
        case 7:
            bit_Cal(75, 0x3C, 0x04);bit_Cal(74, 0x38, 0x28);
            break;
        case 8:
            bit_Cal(75, 0x3C, 0x3C);bit_Cal(74, 0x38, 0x3C);
            break;
        case 9:
            bit_Cal(75, 0x3C, 0x2C);bit_Cal(74, 0x38, 0x3C);
            break;
        default:
            bit_Cal(75, 0x3C, 0x00);bit_Cal(74, 0x38, 0x10);
            break;
    }

    if (work_num[2].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[2].Temp.Display_Rel / 10 % 10;
    }
    else if (work_num[2].Temp.Display_Rel < 0 && work_num[2].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[2].Temp.Display_Rel) / 10 % 10;
    }
    else if (work_num[2].Temp.Display_Rel <= -100 && work_num[2].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[2].Temp.Display_Rel) / 10 % 10;
    }
    switch (Val)
    {
        case 0:
            bit_Cal(74, 0x04, 0x04);bit_Cal(73, 0x1C, 0x14);bit_Cal(72, 0x1C, 0x1C);
            break;
        case 1:
            bit_Cal(74, 0x04, 0x00);bit_Cal(73, 0x1C, 0x00);bit_Cal(72, 0x1C, 0x0C);
            break;
        case 2:
            bit_Cal(74, 0x04, 0x00);bit_Cal(73, 0x1C, 0x1C);bit_Cal(72, 0x1C, 0x14);
            break;
        case 3:
            bit_Cal(74, 0x04, 0x00);bit_Cal(73, 0x1C, 0x0C);bit_Cal(72, 0x1C, 0x1C);
            break;
        case 4:
            bit_Cal(74, 0x04, 0x04);bit_Cal(73, 0x1C, 0x08);bit_Cal(72, 0x1C, 0x0C);
            break;
        case 5:
            bit_Cal(74, 0x04, 0x04);bit_Cal(73, 0x1C, 0x0C);bit_Cal(72, 0x1C, 0x18);
            break;
        case 6:
            bit_Cal(74, 0x04, 0x04);bit_Cal(73, 0x1C, 0x1C);bit_Cal(72, 0x1C, 0x18);
            break;
        case 7:
            bit_Cal(74, 0x04, 0x00);bit_Cal(73, 0x1C, 0x04);bit_Cal(72, 0x1C, 0x0C);
            break;
        case 8:
            bit_Cal(74, 0x04, 0x04);bit_Cal(73, 0x1C, 0x1C);bit_Cal(72, 0x1C, 0x1C);
            break;
        case 9:
            bit_Cal(74, 0x04, 0x04);bit_Cal(73, 0x1C, 0x0C);bit_Cal(72, 0x1C, 0x1C);
            break;
        default:
            bit_Cal(74, 0x04, 0x00);bit_Cal(73, 0x1C, 0x08);bit_Cal(72, 0x1C, 0x00);//显示“-”
            break;
    }

    if (work_num[2].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[2].Temp.Display_Rel / 10 % 10;
    }
    else if (work_num[2].Temp.Display_Rel < 0 && work_num[2].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[2].Temp.Display_Rel) % 10;
    }
    else if (work_num[2].Temp.Display_Rel <= -100 && work_num[2].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[2].Temp.Display_Rel) % 10;
    }
    switch (Val)
    {
        case 0:
            bit_Cal(71, 0x1C, 0x1C);bit_Cal(70, 0x0E, 0x0A);bit_Cal(69, 0x02, 0x02);
            break;
        case 1:
            bit_Cal(71, 0x1C, 0x00);bit_Cal(70, 0x0E, 0x08);bit_Cal(69, 0x02, 0x02);
            break;
        case 2:
            bit_Cal(71, 0x1C, 0x18);bit_Cal(70, 0x0E, 0x06);bit_Cal(69, 0x02, 0x02);
            break;
        case 3:
            bit_Cal(71, 0x1C, 0x10);bit_Cal(70, 0x0E, 0x0E);bit_Cal(69, 0x02, 0x02);
            break;
        case 4:
            bit_Cal(71, 0x1C, 0x04);bit_Cal(70, 0x0E, 0x0C);bit_Cal(69, 0x02, 0x02);
            break;
        case 5:
            bit_Cal(71, 0x1C, 0x14);bit_Cal(70, 0x0E, 0x0E);bit_Cal(69, 0x02, 0x00);
            break;
        case 6:
            bit_Cal(71, 0x1C, 0x1C);bit_Cal(70, 0x0E, 0x0E);bit_Cal(69, 0x02, 0x00);
            break;
        case 7:
            bit_Cal(71, 0x1C, 0x00);bit_Cal(70, 0x0E, 0x0A);bit_Cal(69, 0x02, 0x02);
            break;
        case 8:
            bit_Cal(71, 0x1C, 0x1C);bit_Cal(70, 0x0E, 0x0E);bit_Cal(69, 0x02, 0x02);
            break;
        case 9:
            bit_Cal(71, 0x1C, 0x14);bit_Cal(70, 0x0E, 0x0E);bit_Cal(69, 0x02, 0x02);
            break;
        default:
            bit_Cal(71, 0x1C, 0x00);bit_Cal(70, 0x0E, 0x04);bit_Cal(69, 0x02, 0x00);//显示“-”
            break;
    }

    /* 3号工位实际温度小数点 */
    bit_Cal(72, 0x20, 0x20);

    /**********工位3的设定温度显示**********/
    if (work_num[2].Temp.Display_Set >= 0)//大于等于0时
    {
        Val = work_num[2].Temp.Display_Set / 1000 % 10;
    }
    else if (work_num[2].Temp.Display_Set < 0 && work_num[2].Temp.Display_Set > -100)
    {
        Val = ABS(work_num[2].Temp.Display_Set) / 1000 % 10;//计算后是0，不大于999所以不会显示
    }
    else if (work_num[2].Temp.Display_Set <= -100 && work_num[2].Temp.Display_Set > -1000)
    {
        Val = 10;//显示“-”
    }
    switch (Val)
    {
        case 0:
            if (work_num[2].Temp.Display_Set > 999)//显示0
            {
                bit_Cal(69, 0x1C, 0x1C);bit_Cal(68, 0x0E, 0x0A);bit_Cal(67, 0x02, 0x02);
            }
            else//不显示这位
            {
                bit_Cal(69, 0x1C, 0x00);bit_Cal(68, 0x0E, 0x00);bit_Cal(67, 0x02, 0x00);
            }
            break;
        case 1:
            bit_Cal(69, 0x1C, 0x00);bit_Cal(68, 0x0E, 0x08);bit_Cal(67, 0x02, 0x02);
            break;
        case 2:
            bit_Cal(69, 0x1C, 0x18);bit_Cal(68, 0x0E, 0x06);bit_Cal(67, 0x02, 0x02);
            break;
        case 3:
            bit_Cal(69, 0x1C, 0x10);bit_Cal(68, 0x0E, 0x0E);bit_Cal(67, 0x02, 0x02);
            break;
        case 4:
            bit_Cal(69, 0x1C, 0x04);bit_Cal(68, 0x0E, 0x0C);bit_Cal(67, 0x02, 0x02);
            break;
        case 5:
            bit_Cal(69, 0x1C, 0x14);bit_Cal(68, 0x0E, 0x0E);bit_Cal(67, 0x02, 0x00);
            break;
        case 6:
            bit_Cal(69, 0x1C, 0x1C);bit_Cal(68, 0x0E, 0x0E);bit_Cal(67, 0x02, 0x00);
            break;
        case 7:
            bit_Cal(69, 0x1C, 0x00);bit_Cal(68, 0x0E, 0x0A);bit_Cal(67, 0x02, 0x02);
            break;
        case 8:
            bit_Cal(69, 0x1C, 0x1C);bit_Cal(68, 0x0E, 0x0E);bit_Cal(67, 0x02, 0x02);
            break;
        case 9:
            bit_Cal(69, 0x1C, 0x14);bit_Cal(68, 0x0E, 0x0E);bit_Cal(67, 0x02, 0x02);
            break;
        default:
            bit_Cal(69, 0x1C, 0x00);bit_Cal(68, 0x0E, 0x04);bit_Cal(67, 0x02, 0x00);//显示“-”
            break;
    }

    if (work_num[2].Temp.Display_Set >= 0)//大于等于0时
    {
        Val = work_num[2].Temp.Display_Set / 100 % 10;
    }
    else if (work_num[2].Temp.Display_Set < 0 && work_num[2].Temp.Display_Set > -100)
    {
        Val = 10;//显示“-”
    }
    else if (work_num[2].Temp.Display_Set <= -100 && work_num[2].Temp.Display_Set > -1000)
    {
        Val = ABS(work_num[2].Temp.Display_Set)/ 100 % 10;
    }
    switch (Val)
    {
        case 0:
            if (work_num[2].Temp.Display_Set > 999)//显示0
            {
                bit_Cal(67, 0x1C, 0x1C);bit_Cal(66, 0x0E, 0x0A);bit_Cal(65, 0x04, 0x04);
            }
            else//不显示这位
            {
                bit_Cal(67, 0x1C, 0x00);bit_Cal(66, 0x0E, 0x00);bit_Cal(65, 0x04, 0x00);
            }
            break;
        case 1:
            bit_Cal(67, 0x1C, 0x00);bit_Cal(66, 0x0E, 0x08);bit_Cal(65, 0x04, 0x04);
            break;
        case 2:
            bit_Cal(67, 0x1C, 0x18);bit_Cal(66, 0x0E, 0x06);bit_Cal(65, 0x04, 0x04);
            break;
        case 3:
            bit_Cal(67, 0x1C, 0x10);bit_Cal(66, 0x0E, 0x0E);bit_Cal(65, 0x04, 0x04);
            break;
        case 4:
            bit_Cal(67, 0x1C, 0x04);bit_Cal(66, 0x0E, 0x0C);bit_Cal(65, 0x04, 0x04);
            break;
        case 5:
            bit_Cal(67, 0x1C, 0x14);bit_Cal(66, 0x0E, 0x0E);bit_Cal(65, 0x04, 0x00);
            break;
        case 6:
            bit_Cal(67, 0x1C, 0x1C);bit_Cal(66, 0x0E, 0x0E);bit_Cal(65, 0x04, 0x00);
            break;
        case 7:
            bit_Cal(67, 0x1C, 0x00);bit_Cal(66, 0x0E, 0x0A);bit_Cal(65, 0x04, 0x04);
            break;
        case 8:
            bit_Cal(67, 0x1C, 0x1C);bit_Cal(66, 0x0E, 0x0E);bit_Cal(65, 0x04, 0x04);
            break;
        case 9:
            bit_Cal(67, 0x1C, 0x14);bit_Cal(66, 0x0E, 0x0E);bit_Cal(65, 0x04, 0x04);
            break;
        default:
            bit_Cal(67, 0x1C, 0x00);bit_Cal(66, 0x0E, 0x04);bit_Cal(65, 0x04, 0x00);//显示“-”
            break;
    }

    if (work_num[2].Temp.Display_Set >= 0)//大于等于0时
    {
        Val = work_num[2].Temp.Display_Set / 10 % 10;
    }
    else if (work_num[2].Temp.Display_Set < 0 && work_num[2].Temp.Display_Set > -100)
    {
        Val = ABS(work_num[2].Temp.Display_Set) / 10 % 10;
    }
    else if (work_num[2].Temp.Display_Set <= -100 && work_num[2].Temp.Display_Set > -1000)
    {
        Val = ABS(work_num[2].Temp.Display_Set) / 10 % 10;
    }
    switch (Val)
    {
        case 0:
            bit_Cal(65, 0x18, 0x18);bit_Cal(64, 0x1C, 0x14);bit_Cal(63, 0x18, 0x18);
            break;
        case 1:
            bit_Cal(65, 0x18, 0x00);bit_Cal(64, 0x1C, 0x00);bit_Cal(63, 0x18, 0x18);
            break;
        case 2:
            bit_Cal(65, 0x18, 0x10);bit_Cal(64, 0x1C, 0x1C);bit_Cal(63, 0x18, 0x08);
            break;
        case 3:
            bit_Cal(65, 0x18, 0x00);bit_Cal(64, 0x1C, 0x1C);bit_Cal(63, 0x18, 0x18);
            break;
        case 4:
            bit_Cal(65, 0x18, 0x08);bit_Cal(64, 0x1C, 0x08);bit_Cal(63, 0x18, 0x18);
            break;
        case 5:
            bit_Cal(65, 0x18, 0x08);bit_Cal(64, 0x1C, 0x1C);bit_Cal(63, 0x18, 0x10);
            break;
        case 6:
            bit_Cal(65, 0x18, 0x18);bit_Cal(64, 0x1C, 0x1C);bit_Cal(63, 0x18, 0x10);
            break;
        case 7:
            bit_Cal(65, 0x18, 0x00);bit_Cal(64, 0x1C, 0x04);bit_Cal(63, 0x18, 0x18);
            break;
        case 8:
            bit_Cal(65, 0x18, 0x18);bit_Cal(64, 0x1C, 0x1C);bit_Cal(63, 0x18, 0x18);
            break;
        case 9:
            bit_Cal(65, 0x18, 0x08);bit_Cal(64, 0x1C, 0x1C);bit_Cal(63, 0x18, 0x18);
            break;
        default:
            bit_Cal(65, 0x18, 0x00);bit_Cal(64, 0x1C, 0x08);bit_Cal(63, 0x18, 0x00);//显示“-”
            break;
    }

    if (work_num[2].Temp.Display_Set >= 0)//大于等于0时
    {
        Val = work_num[2].Temp.Display_Set / 10 % 10;
    }
    else if (work_num[2].Temp.Display_Set < 0 && work_num[2].Temp.Display_Set > -100)
    {
        Val = ABS(work_num[2].Temp.Display_Set) % 10;
    }
    else if (work_num[2].Temp.Display_Set <= -100 && work_num[2].Temp.Display_Set > -1000)
    {
        Val = ABS(work_num[2].Temp.Display_Set) % 10;
    }
    switch (Val)
    {
        case 0:
            bit_Cal(62, 0x38, 0x38);bit_Cal(61, 0x1C, 0x14);bit_Cal(60, 0x08, 0x08);
            break;
        case 1:
            bit_Cal(62, 0x38, 0x00);bit_Cal(61, 0x1C, 0x10);bit_Cal(60, 0x08, 0x08);
            break;
        case 2:
            bit_Cal(62, 0x38, 0x30);bit_Cal(61, 0x1C, 0x0C);bit_Cal(60, 0x08, 0x08);
            break;
        case 3:
            bit_Cal(62, 0x38, 0x20);bit_Cal(61, 0x1C, 0x1C);bit_Cal(60, 0x08, 0x08);
            break;
        case 4:
            bit_Cal(62, 0x38, 0x08);bit_Cal(61, 0x1C, 0x18);bit_Cal(60, 0x08, 0x08);
            break;
        case 5:
            bit_Cal(62, 0x38, 0x28);bit_Cal(61, 0x1C, 0x1C);bit_Cal(60, 0x08, 0x00);
            break;
        case 6:
            bit_Cal(62, 0x38, 0x38);bit_Cal(61, 0x1C, 0x1C);bit_Cal(60, 0x08, 0x00);
            break;
        case 7:
            bit_Cal(62, 0x38, 0x00);bit_Cal(61, 0x1C, 0x14);bit_Cal(60, 0x08, 0x08);
            break;
        case 8:
            bit_Cal(62, 0x38, 0x38);bit_Cal(61, 0x1C, 0x1C);bit_Cal(60, 0x08, 0x08);
            break;
        case 9:
            bit_Cal(62, 0x38, 0x28);bit_Cal(61, 0x1C, 0x1C);bit_Cal(60, 0x08, 0x08);
            break;
        default:
            bit_Cal(62, 0x38, 0x00);bit_Cal(61, 0x1C, 0x08);bit_Cal(60, 0x08, 0x00);//显示“-”
            break;
    }
    /* 3号工位设定温度小数点 */
    bit_Cal(63, 0x20, 0x20);

     /**********工位3的实际时间显示**********/
    Val = work_num[2].Time.Display_Rel / 3600 / 10;//计算十位为单位的小时数
    switch (Val)
    {
        case 0:
            bit_Cal(79, 0xC0, 0xC0);bit_Cal(78, 0xF0, 0xB0);
            break;
        case 1:
            bit_Cal(79, 0xC0, 0x00);bit_Cal(78, 0xF0, 0xA0);
            break;
        case 2:
            bit_Cal(79, 0xC0, 0x80);bit_Cal(78, 0xF0, 0x70);
            break;
        default:
            bit_Cal(79, 0xC0, 0x00);bit_Cal(78, 0xF0, 0x40);//显示“-”
            break;
    }

    Val = work_num[2].Time.Display_Rel / 3600 % 10;// 计算个位为单位的小时数
    switch (Val)
    {
        case 0:
            bit_Cal(77, 0xE0, 0xE0);bit_Cal(76, 0xE0, 0xA0);bit_Cal(75, 0x80, 0x80);
            break;
        case 1:
            bit_Cal(77, 0xE0, 0x00);bit_Cal(76, 0xE0, 0x20);bit_Cal(75, 0x80, 0x80);
            break;
        case 2:
            bit_Cal(77, 0xE0, 0xA0);bit_Cal(76, 0xE0, 0xE0);bit_Cal(75, 0x80, 0x00);
            break;
        case 3:
            bit_Cal(77, 0xE0, 0x20);bit_Cal(76, 0xE0, 0xE0);bit_Cal(75, 0x80, 0x80);
            break;
        case 4:
            bit_Cal(77, 0xE0, 0x40);bit_Cal(76, 0xE0, 0x60);bit_Cal(75, 0x80, 0x80);
            break;
        case 5:
            bit_Cal(77, 0xE0, 0x60);bit_Cal(76, 0xE0, 0xC0);bit_Cal(75, 0x80, 0x80);
            break;
        case 6:
            bit_Cal(77, 0xE0, 0xE0);bit_Cal(76, 0xE0, 0xC0);bit_Cal(75, 0x80, 0x80);
            break;
        case 7:
            bit_Cal(77, 0xE0, 0x20);bit_Cal(76, 0xE0, 0x20);bit_Cal(75, 0x80, 0x80);
            break;
        case 8:
            bit_Cal(77, 0xE0, 0xE0);bit_Cal(76, 0xE0, 0xE0);bit_Cal(75, 0x80, 0x80);
            break;
        case 9:
            bit_Cal(77, 0xE0, 0x60);bit_Cal(76, 0xE0, 0xE0);bit_Cal(75, 0x80, 0x80);
            break;
        default:
            bit_Cal(77, 0xE0, 0x00);bit_Cal(76, 0xE0, 0x40);bit_Cal(75, 0x80, 0x00);//显示“-”
            break;
    }

    Val = work_num[2].Time.Display_Rel % 3600 / 60 / 10; // 计算十分位为单位的分钟数
    switch (Val)
    {
        case 0:
            bit_Cal(74, 0xC0, 0xC0);bit_Cal(73, 0xE0, 0xA0);bit_Cal(72, 0xC0, 0xC0);
            break;
        case 1:
            bit_Cal(74, 0xC0, 0x00);bit_Cal(73, 0xE0, 0x00);bit_Cal(72, 0xC0, 0xC0);
            break;
        case 2:
            bit_Cal(74, 0xC0, 0x80);bit_Cal(73, 0xE0, 0xE0);bit_Cal(72, 0xC0, 0x40);
            break;
        case 3:
            bit_Cal(74, 0xC0, 0x00);bit_Cal(73, 0xE0, 0xE0);bit_Cal(72, 0xC0, 0xC0);
            break;
        case 4:
            bit_Cal(74, 0xC0, 0x40);bit_Cal(73, 0xE0, 0x40);bit_Cal(72, 0xC0, 0xC0);
            break;
        case 5:
            bit_Cal(74, 0xC0, 0x40);bit_Cal(73, 0xE0, 0xE0);bit_Cal(72, 0xC0, 0x80);
            break;
        case 6:
            bit_Cal(74, 0xC0, 0xC0);bit_Cal(73, 0xE0, 0xE0);bit_Cal(72, 0xC0, 0x80);
            break;
        case 7:
            bit_Cal(74, 0xC0, 0x00);bit_Cal(73, 0xE0, 0x20);bit_Cal(72, 0xC0, 0xC0);
            break;
        case 8:
            bit_Cal(74, 0xC0, 0xC0);bit_Cal(73, 0xE0, 0xE0);bit_Cal(72, 0xC0, 0xC0);
            break;
        case 9:
            bit_Cal(74, 0xC0, 0x40);bit_Cal(73, 0xE0, 0xE0);bit_Cal(72, 0xC0, 0xC0);
            break;
        default:
            bit_Cal(74, 0xC0, 0x00);bit_Cal(73, 0xE0, 0x40);bit_Cal(72, 0xC0, 0x00);//显示“-”
            break;
    }

    Val = work_num[2].Time.Display_Rel % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
    switch (Val)
    {
        case 0:
            bit_Cal(71, 0xE0, 0xA0);bit_Cal(70, 0xF0, 0xF0);
            break;
        case 1:
            bit_Cal(71, 0xE0, 0x00);bit_Cal(70, 0xF0, 0x60);
            break;
        case 2:
            bit_Cal(71, 0xE0, 0xC0);bit_Cal(70, 0xF0, 0xB0);
            break;
        case 3:
            bit_Cal(71, 0xE0, 0x40);bit_Cal(70, 0xF0, 0xF0);
            break;
        case 4:
            bit_Cal(71, 0xE0, 0x60);bit_Cal(70, 0xF0, 0x60);
            break;
        case 5:
            bit_Cal(71, 0xE0, 0x60);bit_Cal(70, 0xF0, 0xD0);
            break;
        case 6:
            bit_Cal(71, 0xE0, 0xE0);bit_Cal(70, 0xF0, 0xD0);
            break;
        case 7:
            bit_Cal(71, 0xE0, 0x00);bit_Cal(70, 0xF0, 0x70);
            break;
        case 8:
            bit_Cal(71, 0xE0, 0xE0);bit_Cal(70, 0xF0, 0xF0);
            break;
        case 9:
            bit_Cal(71, 0xE0, 0x60);bit_Cal(70, 0xF0, 0xF0);
            break;
        default:
            bit_Cal(71, 0xE0, 0x40);bit_Cal(70, 0xF0, 0x00);//显示“-”
            break;
    }
    /* 3号工位实际时间冒号 */
    bit_Cal(75, 0x40, 0x40);

    /**********工位3的设定时间显示**********/
    Val = work_num[2].Time.Display_Set / 3600 / 10;//计算十位为单位的小时数
    switch (Val)
    {
         case 0:
            bit_Cal(69, 0xE0, 0xA0);bit_Cal(68, 0xF0, 0xF0);
            break;
        case 1:
            bit_Cal(69, 0xE0, 0x00);bit_Cal(68, 0xF0, 0x60);
            break;
        case 2:
            bit_Cal(69, 0xE0, 0xC0);bit_Cal(68, 0xF0, 0xB0);
            break;
        default:
            bit_Cal(69, 0xE0, 0x40);bit_Cal(68, 0xF0, 0x00);//显示“-”
            break;
    }

    Val = work_num[2].Time.Display_Set / 3600 % 10;// 计算个位为单位的小时数
    switch (Val)
    {
        case 0:
            bit_Cal(67, 0xE0, 0xA0);bit_Cal(66, 0xF0, 0xF0);
            break;
        case 1:
            bit_Cal(67, 0xE0, 0x00);bit_Cal(66, 0xF0, 0x60);
            break;
        case 2:
            bit_Cal(67, 0xE0, 0xC0);bit_Cal(66, 0xF0, 0xB0);
            break;
        case 3:
            bit_Cal(67, 0xE0, 0x40);bit_Cal(66, 0xF0, 0xF0);
            break;
        case 4:
            bit_Cal(67, 0xE0, 0x60);bit_Cal(66, 0xF0, 0x60);
            break;
        case 5:
            bit_Cal(67, 0xE0, 0x60);bit_Cal(66, 0xF0, 0xD0);
            break;
        case 6:
            bit_Cal(67, 0xE0, 0xE0);bit_Cal(66, 0xF0, 0xD0);
            break;
        case 7:
            bit_Cal(67, 0xE0, 0x00);bit_Cal(66, 0xF0, 0x70);
            break;
        case 8:
            bit_Cal(67, 0xE0, 0xE0);bit_Cal(66, 0xF0, 0xF0);
            break;
        case 9:
            bit_Cal(67, 0xE0, 0x60);bit_Cal(66, 0xF0, 0xF0);
            break;
        default:
            bit_Cal(67, 0xE0, 0x40);bit_Cal(66, 0xF0, 0x00);//显示“-”
            break;
    }

    Val = work_num[2].Time.Display_Set % 3600 / 60 / 10; // 计算十分位为单位的分钟数
    switch (Val)
    {
        case 0:
            bit_Cal(65, 0xC0, 0xC0);bit_Cal(64, 0xE0, 0xA0);bit_Cal(63, 0xC0, 0xC0);
            break;
        case 1:
            bit_Cal(65, 0xC0, 0x00);bit_Cal(64, 0xE0, 0x00);bit_Cal(63, 0xC0, 0xC0);
            break;
        case 2:
            bit_Cal(65, 0xC0, 0x80);bit_Cal(64, 0xE0, 0xE0);bit_Cal(63, 0xC0, 0x40);
            break;
        case 3:
            bit_Cal(65, 0xC0, 0x00);bit_Cal(64, 0xE0, 0xE0);bit_Cal(63, 0xC0, 0xC0);
            break;
        case 4:
            bit_Cal(65, 0xC0, 0x40);bit_Cal(64, 0xE0, 0x40);bit_Cal(63, 0xC0, 0xC0);
            break;
        case 5:
            bit_Cal(65, 0xC0, 0x40);bit_Cal(64, 0xE0, 0xE0);bit_Cal(63, 0xC0, 0x80);
            break;
        case 6:
            bit_Cal(65, 0xC0, 0xC0);bit_Cal(64, 0xE0, 0xE0);bit_Cal(63, 0xC0, 0x80);
            break;
        case 7:
            bit_Cal(65, 0xC0, 0x00);bit_Cal(64, 0xE0, 0x20);bit_Cal(63, 0xC0, 0xC0);
            break;
        case 8:
            bit_Cal(65, 0xC0, 0xC0);bit_Cal(64, 0xE0, 0xE0);bit_Cal(63, 0xC0, 0xC0);
            break;
        case 9:
            bit_Cal(65, 0xC0, 0x40);bit_Cal(64, 0xE0, 0xE0);bit_Cal(63, 0xC0, 0xC0);
            break;
        default:
            bit_Cal(65, 0xC0, 0x00);bit_Cal(64, 0xE0, 0x40);bit_Cal(63, 0xC0, 0x00);//显示“-”
            break;
    }

    Val = work_num[2].Time.Display_Set % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
    switch (Val)
    {
        case 0:
            bit_Cal(62, 0xC0, 0xC0);bit_Cal(61, 0xE0, 0xA0);bit_Cal(60, 0x60, 0x60);
            break;
        case 1:
            bit_Cal(62, 0xC0, 0x00);bit_Cal(61, 0xE0, 0x00);bit_Cal(60, 0x60, 0x60);
            break;
        case 2:
            bit_Cal(62, 0xC0, 0x80);bit_Cal(61, 0xE0, 0xE0);bit_Cal(60, 0x60, 0x20);
            break;
        case 3:
            bit_Cal(62, 0xC0, 0x00);bit_Cal(61, 0xE0, 0xE0);bit_Cal(60, 0x60, 0x60);
            break;
        case 4:
            bit_Cal(62, 0xC0, 0x40);bit_Cal(61, 0xE0, 0x40);bit_Cal(60, 0x60, 0x60);
            break;
        case 5:
            bit_Cal(62, 0xC0, 0x40);bit_Cal(61, 0xE0, 0xE0);bit_Cal(60, 0x60, 0x40);
            break;
        case 6:
            bit_Cal(62, 0xC0, 0xC0);bit_Cal(61, 0xE0, 0xE0);bit_Cal(60, 0x60, 0x40);
            break;
        case 7:
            bit_Cal(62, 0xC0, 0x00);bit_Cal(61, 0xE0, 0x20);bit_Cal(60, 0x60, 0x60);
            break;
        case 8:
            bit_Cal(62, 0xC0, 0xC0);bit_Cal(61, 0xE0, 0xE0);bit_Cal(60, 0x60, 0x60);
            break;
        case 9:
            bit_Cal(62, 0xC0, 0x40);bit_Cal(61, 0xE0, 0xE0);bit_Cal(60, 0x60, 0x60);
            break;
        default:
            bit_Cal(62, 0xC0, 0x00);bit_Cal(61, 0xE0, 0x40);bit_Cal(60, 0x60, 0x00);//显示“-”
            break;
    }
    /* 3号工位设定时间冒号 */
    bit_Cal(65, 0x20, 0x20);
    /* 3号工位“rpm”图标 */
    bit_Cal(60, 0x04, 0x04);
    
    /* 3号工位“℃”图标 */
    bit_Cal(60, 0x10, 0x10);

    /* 3号工位“min”图标 */
    bit_Cal(60, 0x80, 0x80);

    /* 3号工位与4号工位之间横线 */
    bit_Cal(60, 0x01, 0x01);

    /* 3号工位转速图标 */
    bit_Cal(79, 0x01, 0x01);//3号工位转速图标S2
    bit_Cal(79, 0x02, 0x02);//3号工位转速图标S3
    bit_Cal(78, 0x01, 0x01);//3号工位转速图标S1
    
    /* 3号工位加热图标 */
    bit_Cal(79, 0x04, 0x04);//3号工位加热图标S4
    bit_Cal(79, 0x10, 0x10);//3号工位加热图标S5
    bit_Cal(79, 0x08, 0x08);//3号工位温度探头图标
    
    /* 3号工位时间图标 */
    bit_Cal(79, 0x20, 0x20);//3号工位时间图标

    /*******************************4号工位*******************************/
    /**********工位4的实际转速显示**********/
    if (work_num[3].Speed.Display_Rel > 999) // 大于999时
    {
        Val = work_num[3].Speed.Display_Rel / 1000 % 10;
       if(Val > 0)
        {
            bit_Cal(58, 0x02, 0x00);bit_Cal(57, 0x02, 0x02);//显示数字1
        }
       else
       {
            bit_Cal(58, 0x02, 0x02);bit_Cal(57, 0x02, 0x02);//显示数字0
       }
    }
    else
    {
        bit_Cal(58, 0x02, 0x02);bit_Cal(57, 0x02, 0x02);//显示数字0
    }
    
   if (work_num[3].Speed.Display_Rel > 99) // 大于99时
   {
       Val = work_num[3].Speed.Display_Rel / 100 % 10;
       switch (Val)
       {
       case 0:
            bit_Cal(57, 0x01, 0x01);bit_Cal(56, 0x07, 0x07);bit_Cal(55, 0x03, 0x02);bit_Cal(54, 0x02, 0x02);
            break;
       case 1:
            bit_Cal(57, 0x01, 0x00);bit_Cal(56, 0x07, 0x01);bit_Cal(55, 0x03, 0x00);bit_Cal(54, 0x02, 0x02);
            break;
       case 2:
            bit_Cal(57, 0x01, 0x01);bit_Cal(56, 0x07, 0x05);bit_Cal(55, 0x03, 0x03);bit_Cal(54, 0x02, 0x00);
            break;
       case 3:
            bit_Cal(57, 0x01, 0x01);bit_Cal(56, 0x07, 0x01);bit_Cal(55, 0x03, 0x03);bit_Cal(54, 0x02, 0x02);
            break;
       case 4:
            bit_Cal(57, 0x01, 0x00);bit_Cal(56, 0x07, 0x03);bit_Cal(55, 0x03, 0x01);bit_Cal(54, 0x02, 0x02);
            break;
       case 5:
            bit_Cal(57, 0x01, 0x01);bit_Cal(56, 0x07, 0x02);bit_Cal(55, 0x03, 0x03);bit_Cal(54, 0x02, 0x02);
            break;
       case 6:
            bit_Cal(57, 0x01, 0x01);bit_Cal(56, 0x07, 0x06);bit_Cal(55, 0x03, 0x03);bit_Cal(54, 0x02, 0x02);
            break;
       case 7:
            bit_Cal(57, 0x01, 0x01);bit_Cal(56, 0x07, 0x01);bit_Cal(55, 0x03, 0x00);bit_Cal(54, 0x02, 0x02);
            break;
       case 8:
            bit_Cal(57, 0x01, 0x01);bit_Cal(56, 0x07, 0x07);bit_Cal(55, 0x03, 0x03);bit_Cal(54, 0x02, 0x02);
            break;
       case 9:
            bit_Cal(57, 0x01, 0x01);bit_Cal(56, 0x07, 0x03);bit_Cal(55, 0x03, 0x03);bit_Cal(54, 0x02, 0x02);
            break;
       default:
           break;
       }
   }
   else
   {
        bit_Cal(57, 0x01, 0x01);bit_Cal(56, 0x07, 0x07);bit_Cal(55, 0x02, 0x02);bit_Cal(54, 0x02, 0x02);;//显示数字零
   }

   if (work_num[3].Speed.Display_Rel > 9) // 大于9时
   {
       Val = work_num[3].Speed.Display_Rel / 10 % 10;
       switch (Val)
       {
       case 0:
            bit_Cal(54, 0x01, 0x01);bit_Cal(53, 0x03, 0x03);bit_Cal(52, 0x03, 0x02);bit_Cal(51, 0x03, 0x03);
            break;
       case 1:
            bit_Cal(54, 0x01, 0x00);bit_Cal(53, 0x03, 0x00);bit_Cal(52, 0x03, 0x00);bit_Cal(51, 0x03, 0x03);
            break;
       case 2:
            bit_Cal(54, 0x01, 0x01);bit_Cal(53, 0x03, 0x02);bit_Cal(52, 0x03, 0x03);bit_Cal(51, 0x03, 0x01);
            break;
       case 3:
            bit_Cal(54, 0x01, 0x01);bit_Cal(53, 0x03, 0x00);bit_Cal(52, 0x03, 0x03);bit_Cal(51, 0x03, 0x03);
            break;
       case 4:
            bit_Cal(54, 0x01, 0x00);bit_Cal(53, 0x03, 0x01);bit_Cal(52, 0x03, 0x01);bit_Cal(51, 0x03, 0x03);
            break;
       case 5:
            bit_Cal(54, 0x01, 0x01);bit_Cal(53, 0x03, 0x01);bit_Cal(52, 0x03, 0x03);bit_Cal(51, 0x03, 0x02);
            break;
       case 6:
            bit_Cal(54, 0x01, 0x01);bit_Cal(53, 0x03, 0x03);bit_Cal(52, 0x03, 0x03);bit_Cal(51, 0x03, 0x02);
            break;
       case 7:
            bit_Cal(54, 0x01, 0x01);bit_Cal(53, 0x03, 0x00);bit_Cal(52, 0x03, 0x00);bit_Cal(51, 0x03, 0x03);
            break;
       case 8:
            bit_Cal(54, 0x01, 0x01);bit_Cal(53, 0x03, 0x03);bit_Cal(52, 0x03, 0x03);bit_Cal(51, 0x03, 0x03);
            break;
       case 9:
            bit_Cal(54, 0x01, 0x01);bit_Cal(53, 0x03, 0x01);bit_Cal(52, 0x03, 0x03);bit_Cal(51, 0x03, 0x03);
            break;
       default:
           break;
       }
   }
   else
   {
       bit_Cal(54, 0x01, 0x01);bit_Cal(53, 0x03, 0x03);bit_Cal(52, 0x03, 0x02);bit_Cal(51, 0x03, 0x03);//显示数字零
   }
    bit_Cal(50, 0x01, 0x01);//实际转速个位只能显示零

    /**********工位4的设定转速显示**********/
    if (work_num[3].Speed.Display_Set > 999) // 大于999时
    {
        Val = work_num[3].Speed.Display_Set / 1000 % 10;
       if(Val > 0)
        {
            bit_Cal(49, 0x01, 0x00);bit_Cal(48, 0x01, 0x01);//显示数字1
        }
       else
       {
            bit_Cal(49, 0x01, 0x01);bit_Cal(48, 0x01, 0x01);//显示数字0
       }
    }
    else
    {
        bit_Cal(49, 0x01, 0x01);bit_Cal(48, 0x01, 0x01);//显示数字0
    }
    
   if (work_num[3].Speed.Display_Set > 99) // 大于99时
   {
       Val = work_num[3].Speed.Display_Set / 100 % 10;
       switch (Val)
       {
       case 0:
            bit_Cal(47, 0x01, 0x01);bit_Cal(46, 0x01, 0x01);bit_Cal(45, 0x03, 0x02);bit_Cal(44, 0x03, 0x03);bit_Cal(43, 0x01, 0x01);
            break;
       case 1:
            bit_Cal(47, 0x01, 0x00);bit_Cal(46, 0x01, 0x00);bit_Cal(45, 0x03, 0x00);bit_Cal(44, 0x03, 0x01);bit_Cal(43, 0x01, 0x01);
            break;
       case 2:
            bit_Cal(47, 0x01, 0x01);bit_Cal(46, 0x01, 0x00);bit_Cal(45, 0x03, 0x03);bit_Cal(44, 0x03, 0x02);bit_Cal(43, 0x01, 0x01);
            break;
       case 3:
            bit_Cal(47, 0x01, 0x01);bit_Cal(46, 0x01, 0x00);bit_Cal(45, 0x03, 0x01);bit_Cal(44, 0x03, 0x03);bit_Cal(43, 0x01, 0x01);
            break;
       case 4:
            bit_Cal(47, 0x01, 0x00);bit_Cal(46, 0x01, 0x01);bit_Cal(45, 0x03, 0x01);bit_Cal(44, 0x03, 0x01);bit_Cal(43, 0x01, 0x01);
            break;
       case 5:
            bit_Cal(47, 0x01, 0x01);bit_Cal(46, 0x01, 0x01);bit_Cal(45, 0x03, 0x01);bit_Cal(44, 0x03, 0x03);bit_Cal(43, 0x01, 0x00);
            break;
       case 6:
            bit_Cal(47, 0x01, 0x01);bit_Cal(46, 0x01, 0x01);bit_Cal(45, 0x03, 0x03);bit_Cal(44, 0x03, 0x03);bit_Cal(43, 0x01, 0x00);
            break;
       case 7:
            bit_Cal(47, 0x01, 0x01);bit_Cal(46, 0x01, 0x00);bit_Cal(45, 0x03, 0x00);bit_Cal(44, 0x03, 0x01);bit_Cal(43, 0x01, 0x01);
            break;
       case 8:
            bit_Cal(47, 0x01, 0x01);bit_Cal(46, 0x01, 0x01);bit_Cal(45, 0x03, 0x03);bit_Cal(44, 0x03, 0x03);bit_Cal(43, 0x01, 0x01);
            break;
       case 9:
            bit_Cal(47, 0x01, 0x01);bit_Cal(46, 0x01, 0x01);bit_Cal(45, 0x03, 0x01);bit_Cal(44, 0x03, 0x03);bit_Cal(43, 0x01, 0x01);
            break;
       default:
           break;
       }
   }
   else
   {
        bit_Cal(47, 0x01, 0x01);bit_Cal(46, 0x01, 0x01);bit_Cal(45, 0x03, 0x02);bit_Cal(44, 0x03, 0x03);bit_Cal(43, 0x01, 0x01);//显示数字零
   }

   if (work_num[3].Speed.Display_Set > 9) // 大于9时
   {
        Val = work_num[3].Speed.Display_Set / 10 % 10;
        switch (Val)
        {
            case 0:
                bit_Cal(43, 0x06, 0x06);bit_Cal(42, 0x07, 0x05);bit_Cal(41, 0x03, 0x03);
                break;
            case 1:
                bit_Cal(43, 0x06, 0x00);bit_Cal(42, 0x07, 0x04);bit_Cal(41, 0x03, 0x02);
                break;
            case 2:
                bit_Cal(43, 0x06, 0x06);bit_Cal(42, 0x07, 0x02);bit_Cal(41, 0x03, 0x03);
                break;
            case 3:
                bit_Cal(43, 0x06, 0x04);bit_Cal(42, 0x07, 0x06);bit_Cal(41, 0x03, 0x03);
                break;
            case 4:
                bit_Cal(43, 0x06, 0x00);bit_Cal(42, 0x07, 0x07);bit_Cal(41, 0x03, 0x02);
                break;
            case 5:
                bit_Cal(43, 0x06, 0x04);bit_Cal(42, 0x07, 0x07);bit_Cal(41, 0x03, 0x01);
                break;
            case 6:
                bit_Cal(43, 0x06, 0x06);bit_Cal(42, 0x07, 0x07);bit_Cal(41, 0x03, 0x01);
                break;
            case 7:
                bit_Cal(43, 0x06, 0x00);bit_Cal(42, 0x07, 0x04);bit_Cal(41, 0x03, 0x03);
                break;
            case 8:
                bit_Cal(43, 0x06, 0x06);bit_Cal(42, 0x07, 0x07);bit_Cal(41, 0x03, 0x03);
                break;
            case 9:
                bit_Cal(43, 0x06, 0x04);bit_Cal(42, 0x07, 0x07);bit_Cal(41, 0x03, 0x03);
                break;
            default:
                break;
        }
    }
    else
    {
        bit_Cal(43, 0x06, 0x06);bit_Cal(42, 0x07, 0x05);bit_Cal(41, 0x03, 0x03);//显示数字零
    }
    bit_Cal(40, 0x02, 0x02);//实际转速个位只能显示零

    /**********工位4的实际温度显示**********/
    if (work_num[3].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[3].Temp.Display_Rel / 1000 % 10;
    }
    else if (work_num[3].Temp.Display_Rel < 0 && work_num[3].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[3].Temp.Display_Rel) / 1000 % 10;//计算后是0，不大于999所以不会显示
    }
    else if (work_num[3].Temp.Display_Rel <= -100 && work_num[3].Temp.Display_Rel > -1000)
    {
        Val = 10;//显示“-”
    }
    switch (Val)
    {
        case 0:
            if (work_num[3].Temp.Display_Rel > 999)//显示0
            {
                bit_Cal(58, 0x0C, 0x0C);bit_Cal(57, 0x1C, 0x14);bit_Cal(56, 0x18, 0x18);
            }
            else//不显示这位
            {
                bit_Cal(58, 0x0C, 0x00);bit_Cal(57, 0x1C, 0x00);bit_Cal(56, 0x18, 0x00);
            }
            break;
        case 1:
            bit_Cal(58, 0x0C, 0x00);bit_Cal(57, 0x1C, 0x00);bit_Cal(56, 0x18, 0x18);
            break;
        case 2:
            bit_Cal(58, 0x0C, 0x08);bit_Cal(57, 0x1C, 0x1C);bit_Cal(56, 0x18, 0x08);
            break;
        case 3:
            bit_Cal(58, 0x0C, 0x00);bit_Cal(57, 0x1C, 0x1C);bit_Cal(56, 0x18, 0x18);
            break;
        case 4:
            bit_Cal(58, 0x0C, 0x04);bit_Cal(57, 0x1C, 0x08);bit_Cal(56, 0x18, 0x18);
            break;
        case 5:
            bit_Cal(58, 0x0C, 0x04);bit_Cal(57, 0x1C, 0x1C);bit_Cal(56, 0x18, 0x10);
            break;
        case 6:
            bit_Cal(58, 0x0C, 0x0C);bit_Cal(57, 0x1C, 0x1C);bit_Cal(56, 0x18, 0x10);
            break;
        case 7:
            bit_Cal(58, 0x0C, 0x00);bit_Cal(57, 0x1C, 0x04);bit_Cal(56, 0x18, 0x18);
            break;
        case 8:
            bit_Cal(58, 0x0C, 0x0C);bit_Cal(57, 0x1C, 0x1C);bit_Cal(56, 0x18, 0x18);
            break;
        case 9:
            bit_Cal(58, 0x0C, 0x04);bit_Cal(57, 0x1C, 0x1C);bit_Cal(56, 0x18, 0x18);
            break;
        default:
            bit_Cal(58, 0x0C, 0x00);bit_Cal(57, 0x1C, 0x08);bit_Cal(56, 0x18, 0x00);//显示“-”
            break;
    }

    if (work_num[3].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[3].Temp.Display_Rel / 100 % 10;
    }
    else if (work_num[3].Temp.Display_Rel < 0 && work_num[3].Temp.Display_Rel > -100)
    {
        Val = 10;//显示“-”
    }
    else if (work_num[3].Temp.Display_Rel <= -100 && work_num[3].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[3].Temp.Display_Rel)/ 100 % 10;
    }
    switch (Val)
    {
        case 0:
            if (work_num[3].Temp.Display_Rel > 99)//显示零
            {
                bit_Cal(55, 0x3C, 0x3C);bit_Cal(54, 0x38, 0x2C);
            }
            else//不显示
            {
                bit_Cal(55, 0x3C, 0x00);bit_Cal(54, 0x38, 0x00);
            }
            break;
        case 1:
            bit_Cal(55, 0x3C, 0x00);bit_Cal(54, 0x38, 0x28);
            break;
        case 2:
            bit_Cal(55, 0x3C, 0x34);bit_Cal(54, 0x38, 0x18);
            break;
        case 3:
            bit_Cal(55, 0x3C, 0x24);bit_Cal(54, 0x38, 0x3C);
            break;
        case 4:
            bit_Cal(55, 0x3C, 0x08);bit_Cal(54, 0x38, 0x3C);
            break;
        case 5:
            bit_Cal(55, 0x3C, 0x2C);bit_Cal(54, 0x38, 0x30);
            break;
        case 6:
            bit_Cal(55, 0x3C, 0x3C);bit_Cal(54, 0x38, 0x30);
            break;
        case 7:
            bit_Cal(55, 0x3C, 0x04);bit_Cal(54, 0x38, 0x28);
            break;
        case 8:
            bit_Cal(55, 0x3C, 0x3C);bit_Cal(54, 0x38, 0x3C);
            break;
        case 9:
            bit_Cal(55, 0x3C, 0x2C);bit_Cal(54, 0x38, 0x3C);
            break;
        default:
            bit_Cal(55, 0x3C, 0x00);bit_Cal(54, 0x38, 0x10);
            break;
    }

    if (work_num[3].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[3].Temp.Display_Rel / 10 % 10;
    }
    else if (work_num[3].Temp.Display_Rel < 0 && work_num[3].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[3].Temp.Display_Rel) / 10 % 10;
    }
    else if (work_num[3].Temp.Display_Rel <= -100 && work_num[3].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[3].Temp.Display_Rel) / 10 % 10;
    }
    switch (Val)
    {
        case 0:
            bit_Cal(54, 0x04, 0x04);bit_Cal(53, 0x1C, 0x14);bit_Cal(52, 0x1C, 0x1C);
            break;
        case 1:
            bit_Cal(54, 0x04, 0x00);bit_Cal(53, 0x1C, 0x00);bit_Cal(52, 0x1C, 0x0C);
            break;
        case 2:
            bit_Cal(54, 0x04, 0x00);bit_Cal(53, 0x1C, 0x1C);bit_Cal(52, 0x1C, 0x14);
            break;
        case 3:
            bit_Cal(54, 0x04, 0x00);bit_Cal(53, 0x1C, 0x0C);bit_Cal(52, 0x1C, 0x1C);
            break;
        case 4:
            bit_Cal(54, 0x04, 0x04);bit_Cal(53, 0x1C, 0x08);bit_Cal(52, 0x1C, 0x0C);
            break;
        case 5:
            bit_Cal(54, 0x04, 0x04);bit_Cal(53, 0x1C, 0x0C);bit_Cal(52, 0x1C, 0x18);
            break;
        case 6:
            bit_Cal(54, 0x04, 0x04);bit_Cal(53, 0x1C, 0x1C);bit_Cal(52, 0x1C, 0x18);
            break;
        case 7:
            bit_Cal(54, 0x04, 0x00);bit_Cal(53, 0x1C, 0x04);bit_Cal(52, 0x1C, 0x0C);
            break;
        case 8:
            bit_Cal(54, 0x04, 0x04);bit_Cal(53, 0x1C, 0x1C);bit_Cal(52, 0x1C, 0x1C);
            break;
        case 9:
            bit_Cal(54, 0x04, 0x04);bit_Cal(53, 0x1C, 0x0C);bit_Cal(52, 0x1C, 0x1C);
            break;
        default:
            bit_Cal(54, 0x04, 0x00);bit_Cal(53, 0x1C, 0x08);bit_Cal(52, 0x1C, 0x00);//显示“-”
            break;
    }

    if (work_num[3].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[3].Temp.Display_Rel / 10 % 10;
    }
    else if (work_num[3].Temp.Display_Rel < 0 && work_num[3].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[3].Temp.Display_Rel) % 10;
    }
    else if (work_num[3].Temp.Display_Rel <= -100 && work_num[3].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[3].Temp.Display_Rel) % 10;
    }
    switch (Val)
    {
        case 0:
            bit_Cal(51, 0x1C, 0x1C);bit_Cal(50, 0x0E, 0x0A);bit_Cal(49, 0x02, 0x02);
            break;
        case 1:
            bit_Cal(51, 0x1C, 0x00);bit_Cal(50, 0x0E, 0x08);bit_Cal(49, 0x02, 0x02);
            break;
        case 2:
            bit_Cal(51, 0x1C, 0x18);bit_Cal(50, 0x0E, 0x06);bit_Cal(49, 0x02, 0x02);
            break;
        case 3:
            bit_Cal(51, 0x1C, 0x10);bit_Cal(50, 0x0E, 0x0E);bit_Cal(49, 0x02, 0x02);
            break;
        case 4:
            bit_Cal(51, 0x1C, 0x04);bit_Cal(50, 0x0E, 0x0C);bit_Cal(49, 0x02, 0x02);
            break;
        case 5:
            bit_Cal(51, 0x1C, 0x14);bit_Cal(50, 0x0E, 0x0E);bit_Cal(49, 0x02, 0x00);
            break;
        case 6:
            bit_Cal(51, 0x1C, 0x1C);bit_Cal(50, 0x0E, 0x0E);bit_Cal(49, 0x02, 0x00);
            break;
        case 7:
            bit_Cal(51, 0x1C, 0x00);bit_Cal(50, 0x0E, 0x0A);bit_Cal(49, 0x02, 0x02);
            break;
        case 8:
            bit_Cal(51, 0x1C, 0x1C);bit_Cal(50, 0x0E, 0x0E);bit_Cal(49, 0x02, 0x02);
            break;
        case 9:
            bit_Cal(51, 0x1C, 0x14);bit_Cal(50, 0x0E, 0x0E);bit_Cal(49, 0x02, 0x02);
            break;
        default:
            bit_Cal(51, 0x1C, 0x00);bit_Cal(50, 0x0E, 0x04);bit_Cal(49, 0x02, 0x00);//显示“-”
            break;
    }

    /* 4号工位实际温度小数点 */
    bit_Cal(52, 0x20, 0x20);

    /**********工位4的设定温度显示**********/
    if (work_num[3].Temp.Display_Set >= 0)//大于等于0时
    {
        Val = work_num[3].Temp.Display_Set / 1000 % 10;
    }
    else if (work_num[3].Temp.Display_Set < 0 && work_num[3].Temp.Display_Set > -100)
    {
        Val = ABS(work_num[3].Temp.Display_Set) / 1000 % 10;//计算后是0，不大于999所以不会显示
    }
    else if (work_num[3].Temp.Display_Set <= -100 && work_num[3].Temp.Display_Set > -1000)
    {
        Val = 10;//显示“-”
    }
    switch (Val)
    {
        case 0:
            if (work_num[3].Temp.Display_Set > 999)//显示0
            {
                bit_Cal(49, 0x1C, 0x1C);bit_Cal(48, 0x0E, 0x0A);bit_Cal(47, 0x02, 0x02);
            }
            else//不显示这位
            {
                bit_Cal(49, 0x1C, 0x00);bit_Cal(48, 0x0E, 0x00);bit_Cal(47, 0x02, 0x00);
            }
            break;
        case 1:
            bit_Cal(49, 0x1C, 0x00);bit_Cal(48, 0x0E, 0x08);bit_Cal(47, 0x02, 0x02);
            break;
        case 2:
            bit_Cal(49, 0x1C, 0x18);bit_Cal(48, 0x0E, 0x06);bit_Cal(47, 0x02, 0x02);
            break;
        case 3:
            bit_Cal(49, 0x1C, 0x10);bit_Cal(48, 0x0E, 0x0E);bit_Cal(47, 0x02, 0x02);
            break;
        case 4:
            bit_Cal(49, 0x1C, 0x04);bit_Cal(48, 0x0E, 0x0C);bit_Cal(47, 0x02, 0x02);
            break;
        case 5:
            bit_Cal(49, 0x1C, 0x14);bit_Cal(48, 0x0E, 0x0E);bit_Cal(47, 0x02, 0x00);
            break;
        case 6:
            bit_Cal(49, 0x1C, 0x1C);bit_Cal(48, 0x0E, 0x0E);bit_Cal(47, 0x02, 0x00);
            break;
        case 7:
            bit_Cal(49, 0x1C, 0x00);bit_Cal(48, 0x0E, 0x0A);bit_Cal(47, 0x02, 0x02);
            break;
        case 8:
            bit_Cal(49, 0x1C, 0x1C);bit_Cal(48, 0x0E, 0x0E);bit_Cal(47, 0x02, 0x02);
            break;
        case 9:
            bit_Cal(49, 0x1C, 0x14);bit_Cal(48, 0x0E, 0x0E);bit_Cal(47, 0x02, 0x02);
            break;
        default:
            bit_Cal(49, 0x1C, 0x00);bit_Cal(48, 0x0E, 0x04);bit_Cal(47, 0x02, 0x00);//显示“-”
            break;
    }

    if (work_num[3].Temp.Display_Set >= 0)//大于等于0时
    {
        Val = work_num[3].Temp.Display_Set / 100 % 10;
    }
    else if (work_num[3].Temp.Display_Set < 0 && work_num[3].Temp.Display_Set > -100)
    {
        Val = 10;//显示“-”
    }
    else if (work_num[3].Temp.Display_Set <= -100 && work_num[3].Temp.Display_Set > -1000)
    {
        Val = ABS(work_num[3].Temp.Display_Set)/ 100 % 10;
    }
    switch (Val)
    {
        case 0:
            if (work_num[3].Temp.Display_Set > 999)//显示0
            {
                bit_Cal(47, 0x1C, 0x1C);bit_Cal(46, 0x0E, 0x0A);bit_Cal(45, 0x04, 0x04);
            }
            else//不显示这位
            {
                bit_Cal(47, 0x1C, 0x00);bit_Cal(46, 0x0E, 0x00);bit_Cal(45, 0x04, 0x00);
            }
            break;
        case 1:
            bit_Cal(47, 0x1C, 0x00);bit_Cal(46, 0x0E, 0x08);bit_Cal(45, 0x04, 0x04);
            break;
        case 2:
            bit_Cal(47, 0x1C, 0x18);bit_Cal(46, 0x0E, 0x06);bit_Cal(45, 0x04, 0x04);
            break;
        case 3:
            bit_Cal(47, 0x1C, 0x10);bit_Cal(46, 0x0E, 0x0E);bit_Cal(45, 0x04, 0x04);
            break;
        case 4:
            bit_Cal(47, 0x1C, 0x04);bit_Cal(46, 0x0E, 0x0C);bit_Cal(45, 0x04, 0x04);
            break;
        case 5:
            bit_Cal(47, 0x1C, 0x14);bit_Cal(46, 0x0E, 0x0E);bit_Cal(45, 0x04, 0x00);
            break;
        case 6:
            bit_Cal(47, 0x1C, 0x1C);bit_Cal(46, 0x0E, 0x0E);bit_Cal(45, 0x04, 0x00);
            break;
        case 7:
            bit_Cal(47, 0x1C, 0x00);bit_Cal(46, 0x0E, 0x0A);bit_Cal(45, 0x04, 0x04);
            break;
        case 8:
            bit_Cal(47, 0x1C, 0x1C);bit_Cal(46, 0x0E, 0x0E);bit_Cal(45, 0x04, 0x04);
            break;
        case 9:
            bit_Cal(47, 0x1C, 0x14);bit_Cal(46, 0x0E, 0x0E);bit_Cal(45, 0x04, 0x04);
            break;
        default:
            bit_Cal(47, 0x1C, 0x00);bit_Cal(46, 0x0E, 0x04);bit_Cal(45, 0x04, 0x00);//显示“-”
            break;
    }

    if (work_num[3].Temp.Display_Set >= 0)//大于等于0时
    {
        Val = work_num[3].Temp.Display_Set / 10 % 10;
    }
    else if (work_num[3].Temp.Display_Set < 0 && work_num[3].Temp.Display_Set > -100)
    {
        Val = ABS(work_num[3].Temp.Display_Set) / 10 % 10;
    }
    else if (work_num[3].Temp.Display_Set <= -100 && work_num[3].Temp.Display_Set > -1000)
    {
        Val = ABS(work_num[3].Temp.Display_Set) / 10 % 10;
    }
    switch (Val)
    {
        case 0:
            bit_Cal(45, 0x18, 0x18);bit_Cal(44, 0x1C, 0x14);bit_Cal(43, 0x18, 0x18);
            break;
        case 1:
            bit_Cal(45, 0x18, 0x00);bit_Cal(44, 0x1C, 0x00);bit_Cal(43, 0x18, 0x18);
            break;
        case 2:
            bit_Cal(45, 0x18, 0x10);bit_Cal(44, 0x1C, 0x1C);bit_Cal(43, 0x18, 0x08);
            break;
        case 3:
            bit_Cal(45, 0x18, 0x00);bit_Cal(44, 0x1C, 0x1C);bit_Cal(43, 0x18, 0x18);
            break;
        case 4:
            bit_Cal(45, 0x18, 0x08);bit_Cal(44, 0x1C, 0x08);bit_Cal(43, 0x18, 0x18);
            break;
        case 5:
            bit_Cal(45, 0x18, 0x08);bit_Cal(44, 0x1C, 0x1C);bit_Cal(43, 0x18, 0x10);
            break;
        case 6:
            bit_Cal(45, 0x18, 0x18);bit_Cal(44, 0x1C, 0x1C);bit_Cal(43, 0x18, 0x10);
            break;
        case 7:
            bit_Cal(45, 0x18, 0x00);bit_Cal(44, 0x1C, 0x04);bit_Cal(43, 0x18, 0x18);
            break;
        case 8:
            bit_Cal(45, 0x18, 0x18);bit_Cal(44, 0x1C, 0x1C);bit_Cal(43, 0x18, 0x18);
            break;
        case 9:
            bit_Cal(45, 0x18, 0x08);bit_Cal(44, 0x1C, 0x1C);bit_Cal(43, 0x18, 0x18);
            break;
        default:
            bit_Cal(45, 0x18, 0x00);bit_Cal(44, 0x1C, 0x08);bit_Cal(43, 0x18, 0x00);//显示“-”
            break;
    }

    if (work_num[3].Temp.Display_Set >= 0)//大于等于0时
    {
        Val = work_num[3].Temp.Display_Set / 10 % 10;
    }
    else if (work_num[3].Temp.Display_Set < 0 && work_num[3].Temp.Display_Set > -100)
    {
        Val = ABS(work_num[3].Temp.Display_Set) % 10;
    }
    else if (work_num[3].Temp.Display_Set <= -100 && work_num[3].Temp.Display_Set > -1000)
    {
        Val = ABS(work_num[3].Temp.Display_Set) % 10;
    }
    switch (Val)
    {
        case 0:
            bit_Cal(42, 0x38, 0x38);bit_Cal(41, 0x1C, 0x14);bit_Cal(40, 0x08, 0x08);
            break;
        case 1:
            bit_Cal(42, 0x38, 0x00);bit_Cal(41, 0x1C, 0x10);bit_Cal(40, 0x08, 0x08);
            break;
        case 2:
            bit_Cal(42, 0x38, 0x30);bit_Cal(41, 0x1C, 0x0C);bit_Cal(40, 0x08, 0x08);
            break;
        case 3:
            bit_Cal(42, 0x38, 0x20);bit_Cal(41, 0x1C, 0x1C);bit_Cal(40, 0x08, 0x08);
            break;
        case 4:
            bit_Cal(42, 0x38, 0x08);bit_Cal(41, 0x1C, 0x18);bit_Cal(40, 0x08, 0x08);
            break;
        case 5:
            bit_Cal(42, 0x38, 0x28);bit_Cal(41, 0x1C, 0x1C);bit_Cal(40, 0x08, 0x00);
            break;
        case 6:
            bit_Cal(42, 0x38, 0x38);bit_Cal(41, 0x1C, 0x1C);bit_Cal(40, 0x08, 0x00);
            break;
        case 7:
            bit_Cal(42, 0x38, 0x00);bit_Cal(41, 0x1C, 0x14);bit_Cal(40, 0x08, 0x08);
            break;
        case 8:
            bit_Cal(42, 0x38, 0x38);bit_Cal(41, 0x1C, 0x1C);bit_Cal(40, 0x08, 0x08);
            break;
        case 9:
            bit_Cal(42, 0x38, 0x28);bit_Cal(41, 0x1C, 0x1C);bit_Cal(40, 0x08, 0x08);
            break;
        default:
            bit_Cal(42, 0x38, 0x00);bit_Cal(41, 0x1C, 0x08);bit_Cal(40, 0x08, 0x00);//显示“-”
            break;
    }
    /* 4号工位设定温度小数点 */
    bit_Cal(43, 0x20, 0x20);

     /**********工位4的实际时间显示**********/
    Val = work_num[3].Time.Display_Rel / 3600 / 10;//计算十位为单位的小时数
    switch (Val)
    {
        case 0:
            bit_Cal(59, 0xC0, 0xC0);bit_Cal(58, 0xF0, 0xB0);
            break;
        case 1:
            bit_Cal(59, 0xC0, 0x00);bit_Cal(58, 0xF0, 0xA0);
            break;
        case 2:
            bit_Cal(59, 0xC0, 0x80);bit_Cal(58, 0xF0, 0x70);
            break;
        default:
            bit_Cal(59, 0xC0, 0x00);bit_Cal(58, 0xF0, 0x40);//显示“-”
            break;
    }

    Val = work_num[3].Time.Display_Rel / 3600 % 10;// 计算个位为单位的小时数
    switch (Val)
    {
        case 0:
            bit_Cal(57, 0xE0, 0xE0);bit_Cal(56, 0xE0, 0xA0);bit_Cal(55, 0x80, 0x80);
            break;
        case 1:
            bit_Cal(57, 0xE0, 0x00);bit_Cal(56, 0xE0, 0x20);bit_Cal(55, 0x80, 0x80);
            break;
        case 2:
            bit_Cal(57, 0xE0, 0xA0);bit_Cal(56, 0xE0, 0xE0);bit_Cal(55, 0x80, 0x00);
            break;
        case 3:
            bit_Cal(57, 0xE0, 0x20);bit_Cal(56, 0xE0, 0xE0);bit_Cal(55, 0x80, 0x80);
            break;
        case 4:
            bit_Cal(57, 0xE0, 0x40);bit_Cal(56, 0xE0, 0x60);bit_Cal(55, 0x80, 0x80);
            break;
        case 5:
            bit_Cal(57, 0xE0, 0x60);bit_Cal(56, 0xE0, 0xC0);bit_Cal(55, 0x80, 0x80);
            break;
        case 6:
            bit_Cal(57, 0xE0, 0xE0);bit_Cal(56, 0xE0, 0xC0);bit_Cal(55, 0x80, 0x80);
            break;
        case 7:
            bit_Cal(57, 0xE0, 0x20);bit_Cal(56, 0xE0, 0x20);bit_Cal(55, 0x80, 0x80);
            break;
        case 8:
            bit_Cal(57, 0xE0, 0xE0);bit_Cal(56, 0xE0, 0xE0);bit_Cal(55, 0x80, 0x80);
            break;
        case 9:
            bit_Cal(57, 0xE0, 0x60);bit_Cal(56, 0xE0, 0xE0);bit_Cal(55, 0x80, 0x80);
            break;
        default:
            bit_Cal(57, 0xE0, 0x00);bit_Cal(56, 0xE0, 0x40);bit_Cal(55, 0x80, 0x00);//显示“-”
            break;
    }

    Val = work_num[3].Time.Display_Rel % 3600 / 60 / 10; // 计算十分位为单位的分钟数
    switch (Val)
    {
        case 0:
            bit_Cal(54, 0xC0, 0xC0);bit_Cal(53, 0xE0, 0xA0);bit_Cal(52, 0xC0, 0xC0);
            break;
        case 1:
            bit_Cal(54, 0xC0, 0x00);bit_Cal(53, 0xE0, 0x00);bit_Cal(52, 0xC0, 0xC0);
            break;
        case 2:
            bit_Cal(54, 0xC0, 0x80);bit_Cal(53, 0xE0, 0xE0);bit_Cal(52, 0xC0, 0x40);
            break;
        case 3:
            bit_Cal(54, 0xC0, 0x00);bit_Cal(53, 0xE0, 0xE0);bit_Cal(52, 0xC0, 0xC0);
            break;
        case 4:
            bit_Cal(54, 0xC0, 0x40);bit_Cal(53, 0xE0, 0x40);bit_Cal(52, 0xC0, 0xC0);
            break;
        case 5:
            bit_Cal(54, 0xC0, 0x40);bit_Cal(53, 0xE0, 0xE0);bit_Cal(52, 0xC0, 0x80);
            break;
        case 6:
            bit_Cal(54, 0xC0, 0xC0);bit_Cal(53, 0xE0, 0xE0);bit_Cal(52, 0xC0, 0x80);
            break;
        case 7:
            bit_Cal(54, 0xC0, 0x00);bit_Cal(53, 0xE0, 0x20);bit_Cal(52, 0xC0, 0xC0);
            break;
        case 8:
            bit_Cal(54, 0xC0, 0xC0);bit_Cal(53, 0xE0, 0xE0);bit_Cal(52, 0xC0, 0xC0);
            break;
        case 9:
            bit_Cal(54, 0xC0, 0x40);bit_Cal(53, 0xE0, 0xE0);bit_Cal(52, 0xC0, 0xC0);
            break;
        default:
            bit_Cal(54, 0xC0, 0x00);bit_Cal(53, 0xE0, 0x40);bit_Cal(52, 0xC0, 0x00);//显示“-”
            break;
    }

    Val = work_num[3].Time.Display_Rel % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
    switch (Val)
    {
        case 0:
            bit_Cal(51, 0xE0, 0xA0);bit_Cal(50, 0xF0, 0xF0);
            break;
        case 1:
            bit_Cal(51, 0xE0, 0x00);bit_Cal(50, 0xF0, 0x60);
            break;
        case 2:
            bit_Cal(51, 0xE0, 0xC0);bit_Cal(50, 0xF0, 0xB0);
            break;
        case 3:
            bit_Cal(51, 0xE0, 0x40);bit_Cal(50, 0xF0, 0xF0);
            break;
        case 4:
            bit_Cal(51, 0xE0, 0x60);bit_Cal(50, 0xF0, 0x60);
            break;
        case 5:
            bit_Cal(51, 0xE0, 0x60);bit_Cal(50, 0xF0, 0xD0);
            break;
        case 6:
            bit_Cal(51, 0xE0, 0xE0);bit_Cal(50, 0xF0, 0xD0);
            break;
        case 7:
            bit_Cal(51, 0xE0, 0x00);bit_Cal(50, 0xF0, 0x70);
            break;
        case 8:
            bit_Cal(51, 0xE0, 0xE0);bit_Cal(50, 0xF0, 0xF0);
            break;
        case 9:
            bit_Cal(51, 0xE0, 0x60);bit_Cal(50, 0xF0, 0xF0);
            break;
        default:
            bit_Cal(51, 0xE0, 0x40);bit_Cal(50, 0xF0, 0x00);//显示“-”
            break;
    }
    /* 4号工位实际时间冒号 */
    bit_Cal(55, 0x40, 0x40);

    /**********工位3的设定时间显示**********/
    Val = work_num[3].Time.Display_Set / 3600 / 10;//计算十位为单位的小时数
    switch (Val)
    {
         case 0:
            bit_Cal(49, 0xE0, 0xA0);bit_Cal(48, 0xF0, 0xF0);
            break;
        case 1:
            bit_Cal(49, 0xE0, 0x00);bit_Cal(48, 0xF0, 0x60);
            break;
        case 2:
            bit_Cal(49, 0xE0, 0xC0);bit_Cal(48, 0xF0, 0xB0);
            break;
        default:
            bit_Cal(49, 0xE0, 0x40);bit_Cal(48, 0xF0, 0x00);//显示“-”
            break;
    }

    Val = work_num[3].Time.Display_Set / 3600 % 10;// 计算个位为单位的小时数
    switch (Val)
    {
        case 0:
            bit_Cal(47, 0xE0, 0xA0);bit_Cal(46, 0xF0, 0xF0);
            break;
        case 1:
            bit_Cal(47, 0xE0, 0x00);bit_Cal(46, 0xF0, 0x60);
            break;
        case 2:
            bit_Cal(47, 0xE0, 0xC0);bit_Cal(46, 0xF0, 0xB0);
            break;
        case 3:
            bit_Cal(47, 0xE0, 0x40);bit_Cal(46, 0xF0, 0xF0);
            break;
        case 4:
            bit_Cal(47, 0xE0, 0x60);bit_Cal(46, 0xF0, 0x60);
            break;
        case 5:
            bit_Cal(47, 0xE0, 0x60);bit_Cal(46, 0xF0, 0xD0);
            break;
        case 6:
            bit_Cal(47, 0xE0, 0xE0);bit_Cal(46, 0xF0, 0xD0);
            break;
        case 7:
            bit_Cal(47, 0xE0, 0x00);bit_Cal(46, 0xF0, 0x70);
            break;
        case 8:
            bit_Cal(47, 0xE0, 0xE0);bit_Cal(46, 0xF0, 0xF0);
            break;
        case 9:
            bit_Cal(47, 0xE0, 0x60);bit_Cal(46, 0xF0, 0xF0);
            break;
        default:
            bit_Cal(47, 0xE0, 0x40);bit_Cal(46, 0xF0, 0x00);//显示“-”
            break;
    }

    Val = work_num[3].Time.Display_Set % 3600 / 60 / 10; // 计算十分位为单位的分钟数
    switch (Val)
    {
        case 0:
            bit_Cal(45, 0xC0, 0xC0);bit_Cal(44, 0xE0, 0xA0);bit_Cal(43, 0xC0, 0xC0);
            break;
        case 1:
            bit_Cal(45, 0xC0, 0x00);bit_Cal(44, 0xE0, 0x00);bit_Cal(43, 0xC0, 0xC0);
            break;
        case 2:
            bit_Cal(45, 0xC0, 0x80);bit_Cal(44, 0xE0, 0xE0);bit_Cal(43, 0xC0, 0x40);
            break;
        case 3:
            bit_Cal(45, 0xC0, 0x00);bit_Cal(44, 0xE0, 0xE0);bit_Cal(43, 0xC0, 0xC0);
            break;
        case 4:
            bit_Cal(45, 0xC0, 0x40);bit_Cal(44, 0xE0, 0x40);bit_Cal(43, 0xC0, 0xC0);
            break;
        case 5:
            bit_Cal(45, 0xC0, 0x40);bit_Cal(44, 0xE0, 0xE0);bit_Cal(43, 0xC0, 0x80);
            break;
        case 6:
            bit_Cal(45, 0xC0, 0xC0);bit_Cal(44, 0xE0, 0xE0);bit_Cal(43, 0xC0, 0x80);
            break;
        case 7:
            bit_Cal(45, 0xC0, 0x00);bit_Cal(44, 0xE0, 0x20);bit_Cal(43, 0xC0, 0xC0);
            break;
        case 8:
            bit_Cal(45, 0xC0, 0xC0);bit_Cal(44, 0xE0, 0xE0);bit_Cal(43, 0xC0, 0xC0);
            break;
        case 9:
            bit_Cal(45, 0xC0, 0x40);bit_Cal(44, 0xE0, 0xE0);bit_Cal(43, 0xC0, 0xC0);
            break;
        default:
            bit_Cal(45, 0xC0, 0x00);bit_Cal(44, 0xE0, 0x40);bit_Cal(43, 0xC0, 0x00);//显示“-”
            break;
    }

    Val = work_num[3].Time.Display_Set % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
    switch (Val)
    {
        case 0:
            bit_Cal(42, 0xC0, 0xC0);bit_Cal(41, 0xE0, 0xA0);bit_Cal(40, 0x60, 0x60);
            break;
        case 1:
            bit_Cal(42, 0xC0, 0x00);bit_Cal(41, 0xE0, 0x00);bit_Cal(40, 0x60, 0x60);
            break;
        case 2:
            bit_Cal(42, 0xC0, 0x80);bit_Cal(41, 0xE0, 0xE0);bit_Cal(40, 0x60, 0x20);
            break;
        case 3:
            bit_Cal(42, 0xC0, 0x00);bit_Cal(41, 0xE0, 0xE0);bit_Cal(40, 0x60, 0x60);
            break;
        case 4:
            bit_Cal(42, 0xC0, 0x40);bit_Cal(41, 0xE0, 0x40);bit_Cal(40, 0x60, 0x60);
            break;
        case 5:
            bit_Cal(42, 0xC0, 0x40);bit_Cal(41, 0xE0, 0xE0);bit_Cal(40, 0x60, 0x40);
            break;
        case 6:
            bit_Cal(42, 0xC0, 0xC0);bit_Cal(41, 0xE0, 0xE0);bit_Cal(40, 0x60, 0x40);
            break;
        case 7:
            bit_Cal(42, 0xC0, 0x00);bit_Cal(41, 0xE0, 0x20);bit_Cal(40, 0x60, 0x60);
            break;
        case 8:
            bit_Cal(42, 0xC0, 0xC0);bit_Cal(41, 0xE0, 0xE0);bit_Cal(40, 0x60, 0x60);
            break;
        case 9:
            bit_Cal(42, 0xC0, 0x40);bit_Cal(41, 0xE0, 0xE0);bit_Cal(40, 0x60, 0x60);
            break;
        default:
            bit_Cal(42, 0xC0, 0x00);bit_Cal(41, 0xE0, 0x40);bit_Cal(40, 0x60, 0x00);//显示“-”
            break;
    }
    /* 4号工位设定时间冒号 */
    bit_Cal(45, 0x20, 0x20);
    /* 4号工位“rpm”图标 */
    bit_Cal(40, 0x04, 0x04);
    
    /* 4号工位“℃”图标 */
    bit_Cal(40, 0x10, 0x10);

    /* 4号工位“min”图标 */
    bit_Cal(40, 0x80, 0x80);

    /* 4号工位与4号工位之间横线 */
    bit_Cal(40, 0x01, 0x01);

    /* 4号工位转速图标 */
    bit_Cal(59, 0x01, 0x01);//4号工位转速图标S2
    bit_Cal(59, 0x02, 0x02);//4号工位转速图标S3
    bit_Cal(58, 0x01, 0x01);//4号工位转速图标S1
    
    /* 4号工位加热图标 */
    bit_Cal(59, 0x04, 0x04);//4号工位加热图标S4
    bit_Cal(59, 0x10, 0x10);//4号工位加热图标S5
    bit_Cal(59, 0x08, 0x08);//4号工位温度探头图标
    
    /* 4号工位时间图标 */
    bit_Cal(59, 0x20, 0x20);//4号工位时间图标

    /**********数据发送**********/
    for(uint8_t i=0;i<40;i++)
    {
        Write_Addr_Dat_N(IC1, i, seg[i+40], 1);
    }
}

/**
 * @brief 显示屏幕内容
 *
 */
void Show_Display(void)
{
    
    /**********LCD初始化*************/
    Lcd_Init();

    while(1)
    {
        Display_IC2(Work_Num);
        Display_IC1(Work_Num);
        vTaskDelay(10);
    }
}
