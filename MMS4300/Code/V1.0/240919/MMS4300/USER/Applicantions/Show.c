#include "Show.h"

/**********全局变量**********/
float Twinkle_Time; // 闪烁时间

/**********局部变量声明*******/
uint8_t Speed_ShowFlag, Time_ShowFlag, Sync_ShowFlag;//速度、温度、时间显示的标志位，0：常亮，1：熄灭

/**
 * @brief 闪烁函数
 *
 * @param dT 任务周期
 */
void Twinkle(float dT)
{

}

uint8_t seg[62] = {0};
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

void Display_IC(_Work_Num_ work_num[])
{
    uint8_t Val;// 用于百十个取出来的数字
    
    /**********工位4的实际转速显示**********/
    if (work_num[3].Speed.Display_Rel > 999) // 大于999时
    {
        Val = work_num[3].Speed.Display_Rel / 1000 % 10;
        switch (Val)
        {
        case 0:
               bit_Cal(14, 0x70, 0x50);bit_Cal(15, 0xF0, 0xF0);
            break;
        case 1:
               bit_Cal(14, 0x70, 0x50);bit_Cal(15, 0xF0, 0x00);
            break;
        case 2:
               bit_Cal(14, 0x70, 0x60);bit_Cal(15, 0xF0, 0xB0);
            break;
        case 3:
               bit_Cal(14, 0x70, 0x70);bit_Cal(15, 0xF0, 0x90);
            break;
        case 4:
               bit_Cal(14, 0x70, 0x70);bit_Cal(15, 0xF0, 0x40);
            break;
        case 5:
               bit_Cal(14, 0x70, 0x30);bit_Cal(15, 0xF0, 0xD0);
            break;
        case 6:
               bit_Cal(14, 0x70, 0x30);bit_Cal(15, 0xF0, 0xF0);
            break;
        case 7:
               bit_Cal(14, 0x70, 0x50);bit_Cal(15, 0xF0, 0x80);
            break;
        case 8:
               bit_Cal(14, 0x70, 0x70);bit_Cal(15, 0xF0, 0xF0);
            break;
        case 9:
               bit_Cal(14, 0x70, 0x70);bit_Cal(15, 0xF0, 0xD0);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(14, 0x70, 0x50);bit_Cal(15, 0xF0, 0xF0);
    }
    
   if (work_num[3].Speed.Display_Rel > 99) // 大于99时
   {
       Val = work_num[3].Speed.Display_Rel / 100 % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(12, 0x70, 0x50);bit_Cal(13, 0xF0, 0xF0);
            break;
        case 1:
               bit_Cal(12, 0x70, 0x50);bit_Cal(13, 0xF0, 0x00);
            break;
        case 2:
               bit_Cal(12, 0x70, 0x60);bit_Cal(13, 0xF0, 0xB0);
            break;
        case 3:
               bit_Cal(12, 0x70, 0x70);bit_Cal(13, 0xF0, 0x90);
            break;
        case 4:
               bit_Cal(12, 0x70, 0x70);bit_Cal(13, 0xF0, 0x40);
            break;
        case 5:
               bit_Cal(12, 0x70, 0x30);bit_Cal(13, 0xF0, 0xD0);
            break;
        case 6:
               bit_Cal(12, 0x70, 0x30);bit_Cal(13, 0xF0, 0xF0);
            break;
        case 7:
               bit_Cal(12, 0x70, 0x50);bit_Cal(13, 0xF0, 0x80);
            break;
        case 8:
               bit_Cal(12, 0x70, 0x70);bit_Cal(13, 0xF0, 0xF0);
            break;
        case 9:
               bit_Cal(12, 0x70, 0x70);bit_Cal(13, 0xF0, 0xD0);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(12, 0x70, 0x50);bit_Cal(13, 0xF0, 0xF0);
    }

   if (work_num[3].Speed.Display_Rel > 9) // 大于9时
   {
       Val = work_num[3].Speed.Display_Rel / 10 % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(10, 0x70, 0x50);bit_Cal(11, 0xF0, 0xF0);
            break;
        case 1:
               bit_Cal(10, 0x70, 0x50);bit_Cal(11, 0xF0, 0x00);
            break;
        case 2:
               bit_Cal(10, 0x70, 0x60);bit_Cal(11, 0xF0, 0xB0);
            break;
        case 3:
               bit_Cal(10, 0x70, 0x70);bit_Cal(11, 0xF0, 0x90);
            break;
        case 4:
               bit_Cal(10, 0x70, 0x70);bit_Cal(11, 0xF0, 0x40);
            break;
        case 5:
               bit_Cal(10, 0x70, 0x30);bit_Cal(11, 0xF0, 0xD0);
            break;
        case 6:
               bit_Cal(10, 0x70, 0x30);bit_Cal(11, 0xF0, 0xF0);
            break;
        case 7:
               bit_Cal(10, 0x70, 0x50);bit_Cal(11, 0xF0, 0x80);
            break;
        case 8:
               bit_Cal(10, 0x70, 0x70);bit_Cal(11, 0xF0, 0xF0);
            break;
        case 9:
               bit_Cal(10, 0x70, 0x70);bit_Cal(11, 0xF0, 0xD0);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(10, 0x70, 0x50);bit_Cal(11, 0xF0, 0xF0);
    }
   
   if (work_num[3].Speed.Display_Rel>= 0) // 大于等于0时
   {
       Val = work_num[3].Speed.Display_Rel % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(8, 0x70, 0x50);bit_Cal(9, 0xF0, 0xF0);
            break;
        case 1:
               bit_Cal(8, 0x70, 0x50);bit_Cal(9, 0xF0, 0x00);
            break;
        case 2:
               bit_Cal(8, 0x70, 0x60);bit_Cal(9, 0xF0, 0xB0);
            break;
        case 3:
               bit_Cal(8, 0x70, 0x70);bit_Cal(9, 0xF0, 0x90);
            break;
        case 4:
               bit_Cal(8, 0x70, 0x70);bit_Cal(9, 0xF0, 0x40);
            break;
        case 5:
               bit_Cal(8, 0x70, 0x30);bit_Cal(9, 0xF0, 0xD0);
            break;
        case 6:
               bit_Cal(8, 0x70, 0x30);bit_Cal(9, 0xF0, 0xF0);
            break;
        case 7:
               bit_Cal(8, 0x70, 0x50);bit_Cal(9, 0xF0, 0x80);
            break;
        case 8:
               bit_Cal(8, 0x70, 0x70);bit_Cal(9, 0xF0, 0xF0);
            break;
        case 9:
               bit_Cal(8, 0x70, 0x70);bit_Cal(9, 0xF0, 0xD0);
            break;
        default:
           break;
        }
    }

    /**********工位4的设定转速显示**********/
    if (work_num[3].Speed.Display_Set > 999) // 大于999时
    {
        Val = work_num[3].Speed.Display_Set / 1000 % 10;
        switch (Val)
        {
        case 0:
               bit_Cal(6, 0x70, 0x50);bit_Cal(7, 0xF0, 0xF0);
            break;
        case 1:
               bit_Cal(6, 0x70, 0x50);bit_Cal(7, 0xF0, 0x00);
            break;
        case 2:
               bit_Cal(6, 0x70, 0x60);bit_Cal(7, 0xF0, 0xB0);
            break;
        case 3:
               bit_Cal(6, 0x70, 0x70);bit_Cal(7, 0xF0, 0x90);
            break;
        case 4:
               bit_Cal(6, 0x70, 0x70);bit_Cal(7, 0xF0, 0x40);
            break;
        case 5:
               bit_Cal(6, 0x70, 0x30);bit_Cal(7, 0xF0, 0xD0);
            break;
        case 6:
               bit_Cal(6, 0x70, 0x30);bit_Cal(7, 0xF0, 0xF0);
            break;
        case 7:
               bit_Cal(6, 0x70, 0x50);bit_Cal(7, 0xF0, 0x80);
            break;
        case 8:
               bit_Cal(6, 0x70, 0x70);bit_Cal(7, 0xF0, 0xF0);
            break;
        case 9:
               bit_Cal(6, 0x70, 0x70);bit_Cal(7, 0xF0, 0xD0);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(6, 0x70, 0x50);bit_Cal(7, 0xF0, 0xF0);
    }
    
   if (work_num[3].Speed.Display_Set > 99) // 大于99时
   {
       Val = work_num[3].Speed.Display_Set / 100 % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(4, 0x70, 0x50);bit_Cal(5, 0xF0, 0xF0);
            break;
        case 1:
               bit_Cal(4, 0x70, 0x50);bit_Cal(5, 0xF0, 0x00);
            break;
        case 2:
               bit_Cal(4, 0x70, 0x60);bit_Cal(5, 0xF0, 0xB0);
            break;
        case 3:
               bit_Cal(4, 0x70, 0x70);bit_Cal(5, 0xF0, 0x90);
            break;
        case 4:
               bit_Cal(4, 0x70, 0x70);bit_Cal(5, 0xF0, 0x40);
            break;
        case 5:
               bit_Cal(4, 0x70, 0x30);bit_Cal(5, 0xF0, 0xD0);
            break;
        case 6:
               bit_Cal(4, 0x70, 0x30);bit_Cal(5, 0xF0, 0xF0);
            break;
        case 7:
               bit_Cal(4, 0x70, 0x50);bit_Cal(5, 0xF0, 0x80);
            break;
        case 8:
               bit_Cal(4, 0x70, 0x70);bit_Cal(5, 0xF0, 0xF0);
            break;
        case 9:
               bit_Cal(4, 0x70, 0x70);bit_Cal(5, 0xF0, 0xD0);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(4, 0x70, 0x50);bit_Cal(5, 0xF0, 0xF0);
    }

   if (work_num[3].Speed.Display_Set > 9) // 大于9时
   {
       Val = work_num[3].Speed.Display_Set / 10 % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(2, 0x70, 0x50);bit_Cal(3, 0xF0, 0xF0);
            break;
        case 1:
               bit_Cal(2, 0x70, 0x50);bit_Cal(3, 0xF0, 0x00);
            break;
        case 2:
               bit_Cal(2, 0x70, 0x60);bit_Cal(3, 0xF0, 0xB0);
            break;
        case 3:
               bit_Cal(2, 0x70, 0x70);bit_Cal(3, 0xF0, 0x90);
            break;
        case 4:
               bit_Cal(2, 0x70, 0x70);bit_Cal(3, 0xF0, 0x40);
            break;
        case 5:
               bit_Cal(2, 0x70, 0x30);bit_Cal(3, 0xF0, 0xD0);
            break;
        case 6:
               bit_Cal(2, 0x70, 0x30);bit_Cal(3, 0xF0, 0xF0);
            break;
        case 7:
               bit_Cal(2, 0x70, 0x50);bit_Cal(3, 0xF0, 0x80);
            break;
        case 8:
               bit_Cal(2, 0x70, 0x70);bit_Cal(3, 0xF0, 0xF0);
            break;
        case 9:
               bit_Cal(2, 0x70, 0x70);bit_Cal(3, 0xF0, 0xD0);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(2, 0x70, 0x50);bit_Cal(3, 0xF0, 0xF0);
    }
   
   if (work_num[3].Speed.Display_Set>= 0) // 大于等于0时
   {
       Val = work_num[3].Speed.Display_Set % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(0, 0x70, 0x50);bit_Cal(1, 0xF0, 0xF0);
            break;
        case 1:
               bit_Cal(0, 0x70, 0x50);bit_Cal(1, 0xF0, 0x00);
            break;
        case 2:
               bit_Cal(0, 0x70, 0x60);bit_Cal(1, 0xF0, 0xB0);
            break;
        case 3:
               bit_Cal(0, 0x70, 0x70);bit_Cal(1, 0xF0, 0x90);
            break;
        case 4:
               bit_Cal(0, 0x70, 0x70);bit_Cal(1, 0xF0, 0x40);
            break;
        case 5:
               bit_Cal(0, 0x70, 0x30);bit_Cal(1, 0xF0, 0xD0);
            break;
        case 6:
               bit_Cal(0, 0x70, 0x30);bit_Cal(1, 0xF0, 0xF0);
            break;
        case 7:
               bit_Cal(0, 0x70, 0x50);bit_Cal(1, 0xF0, 0x80);
            break;
        case 8:
               bit_Cal(0, 0x70, 0x70);bit_Cal(1, 0xF0, 0xF0);
            break;
        case 9:
               bit_Cal(0, 0x70, 0x70);bit_Cal(1, 0xF0, 0xD0);
            break;
        default:
           break;
        }
    }

     /**********工位4的实际时间显示**********/
     Val = work_num[3].Time.Display_Rel / 3600 / 10;//计算十位为单位的小时数
     switch (Val)
     {
     case 0:
          bit_Cal(14, 0x0E, 0x0A);bit_Cal(15, 0x0F, 0x0F);
          break;
     case 1:
          bit_Cal(14, 0x0E, 0x0A);bit_Cal(15, 0x0F, 0x00);
          break;
     case 2:
          bit_Cal(14, 0x0E, 0x0C);bit_Cal(15, 0x0F, 0x0B);
          break;
     case 3:
          bit_Cal(14, 0x0E, 0x0E);bit_Cal(15, 0x0F, 0x09);
          break;
     case 4:
          bit_Cal(14, 0x0E, 0x0E);bit_Cal(15, 0x0F, 0x04);
          break;
     case 5:
          bit_Cal(14, 0x0E, 0x06);bit_Cal(15, 0x0F, 0x0D);
          break;
     case 6:
          bit_Cal(14, 0x0E, 0x06);bit_Cal(15, 0x0F, 0x0F);
          break;
     case 7:
          bit_Cal(14, 0x0E, 0x0A);bit_Cal(15, 0x0F, 0x08);
          break;
     case 8:
          bit_Cal(14, 0x0E, 0x0E);bit_Cal(15, 0x0F, 0x0F);
          break;
     case 9:
          bit_Cal(14, 0x0E, 0x0E);bit_Cal(15, 0x0F, 0x0D);
          break;
     default:
          break;
     }

     Val = work_num[3].Time.Display_Rel / 3600 % 10;// 计算个位为单位的小时数
     switch (Val)
     {
     case 0:
          bit_Cal(12, 0x0E, 0x0A);bit_Cal(13, 0x0F, 0x0F);
          break;
     case 1:
          bit_Cal(12, 0x0E, 0x0A);bit_Cal(13, 0x0F, 0x00);
          break;
     case 2:
          bit_Cal(12, 0x0E, 0x0C);bit_Cal(13, 0x0F, 0x0B);
          break;
     case 3:
          bit_Cal(12, 0x0E, 0x0E);bit_Cal(13, 0x0F, 0x09);
          break;
     case 4:
          bit_Cal(12, 0x0E, 0x0E);bit_Cal(13, 0x0F, 0x04);
          break;
     case 5:
          bit_Cal(12, 0x0E, 0x06);bit_Cal(13, 0x0F, 0x0D);
          break;
     case 6:
          bit_Cal(12, 0x0E, 0x06);bit_Cal(13, 0x0F, 0x0F);
          break;
     case 7:
          bit_Cal(12, 0x0E, 0x0A);bit_Cal(13, 0x0F, 0x08);
          break;
     case 8:
          bit_Cal(12, 0x0E, 0x0E);bit_Cal(13, 0x0F, 0x0F);
          break;
     case 9:
          bit_Cal(12, 0x0E, 0x0E);bit_Cal(13, 0x0F, 0x0D);
          break;
     default:
          break;
     }

     Val = work_num[3].Time.Display_Rel % 3600 / 60 / 10; // 计算十分位为单位的分钟数
     switch (Val)
     {
     case 0:
          bit_Cal(10, 0x0E, 0x0A);bit_Cal(11, 0x0F, 0x0F);
          break;
     case 1:
          bit_Cal(10, 0x0E, 0x0A);bit_Cal(11, 0x0F, 0x00);
          break;
     case 2:
          bit_Cal(10, 0x0E, 0x0C);bit_Cal(11, 0x0F, 0x0B);
          break;
     case 3:
          bit_Cal(10, 0x0E, 0x0E);bit_Cal(11, 0x0F, 0x09);
          break;
     case 4:
          bit_Cal(10, 0x0E, 0x0E);bit_Cal(11, 0x0F, 0x04);
          break;
     case 5:
          bit_Cal(10, 0x0E, 0x06);bit_Cal(11, 0x0F, 0x0D);
          break;
     case 6:
          bit_Cal(10, 0x0E, 0x06);bit_Cal(11, 0x0F, 0x0F);
          break;
     case 7:
          bit_Cal(10, 0x0E, 0x0A);bit_Cal(11, 0x0F, 0x08);
          break;
     case 8:
          bit_Cal(10, 0x0E, 0x0E);bit_Cal(11, 0x0F, 0x0F);
          break;
     case 9:
          bit_Cal(10, 0x0E, 0x0E);bit_Cal(11, 0x0F, 0x0D);
          break;
     default:
          break;
     }

     Val = work_num[3].Time.Display_Rel % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
     switch (Val)
     {
     case 0:
          bit_Cal(8, 0x0E, 0x0A);bit_Cal(9, 0x0F, 0x0F);
          break;
     case 1:
          bit_Cal(8, 0x0E, 0x0A);bit_Cal(9, 0x0F, 0x00);
          break;
     case 2:
          bit_Cal(8, 0x0E, 0x0C);bit_Cal(9, 0x0F, 0x0B);
          break;
     case 3:
          bit_Cal(8, 0x0E, 0x0E);bit_Cal(9, 0x0F, 0x09);
          break;
     case 4:
          bit_Cal(8, 0x0E, 0x0E);bit_Cal(9, 0x0F, 0x04);
          break;
     case 5:
          bit_Cal(8, 0x0E, 0x06);bit_Cal(9, 0x0F, 0x0D);
          break;
     case 6:
          bit_Cal(8, 0x0E, 0x06);bit_Cal(9, 0x0F, 0x0F);
          break;
     case 7:
          bit_Cal(8, 0x0E, 0x0A);bit_Cal(9, 0x0F, 0x08);
          break;
     case 8:
          bit_Cal(8, 0x0E, 0x0E);bit_Cal(9, 0x0F, 0x0F);
          break;
     case 9:
          bit_Cal(8, 0x0E, 0x0E);bit_Cal(9, 0x0F, 0x0D);
          break;
     default:
          break;
     }

     /**********工位4的设定时间显示**********/
     Val = work_num[3].Time.Display_Set / 3600 / 10;//计算十位为单位的小时数
     switch (Val)
     {
     case 0:
          bit_Cal(6, 0x0E, 0x0A);bit_Cal(7, 0x0F, 0x0F);
          break;
     case 1:
          bit_Cal(6, 0x0E, 0x0A);bit_Cal(7, 0x0F, 0x00);
          break;
     case 2:
          bit_Cal(6, 0x0E, 0x0C);bit_Cal(7, 0x0F, 0x0B);
          break;
     case 3:
          bit_Cal(6, 0x0E, 0x0E);bit_Cal(7, 0x0F, 0x09);
          break;
     case 4:
          bit_Cal(6, 0x0E, 0x0E);bit_Cal(7, 0x0F, 0x04);
          break;
     case 5:
          bit_Cal(6, 0x0E, 0x06);bit_Cal(7, 0x0F, 0x0D);
          break;
     case 6:
          bit_Cal(6, 0x0E, 0x06);bit_Cal(7, 0x0F, 0x0F);
          break;
     case 7:
          bit_Cal(6, 0x0E, 0x0A);bit_Cal(7, 0x0F, 0x08);
          break;
     case 8:
          bit_Cal(6, 0x0E, 0x0E);bit_Cal(7, 0x0F, 0x0F);
          break;
     case 9:
          bit_Cal(6, 0x0E, 0x0E);bit_Cal(7, 0x0F, 0x0D);
          break;
     default:
          break;
     }

     Val = work_num[3].Time.Display_Set / 3600 % 10;// 计算个位为单位的小时数
     switch (Val)
     {
     case 0:
          bit_Cal(4, 0x0E, 0x0A);bit_Cal(5, 0x0F, 0x0F);
          break;
     case 1:
          bit_Cal(4, 0x0E, 0x0A);bit_Cal(5, 0x0F, 0x00);
          break;
     case 2:
          bit_Cal(4, 0x0E, 0x0C);bit_Cal(5, 0x0F, 0x0B);
          break;
     case 3:
          bit_Cal(4, 0x0E, 0x0E);bit_Cal(5, 0x0F, 0x09);
          break;
     case 4:
          bit_Cal(4, 0x0E, 0x0E);bit_Cal(5, 0x0F, 0x04);
          break;
     case 5:
          bit_Cal(4, 0x0E, 0x06);bit_Cal(5, 0x0F, 0x0D);
          break;
     case 6:
          bit_Cal(4, 0x0E, 0x06);bit_Cal(5, 0x0F, 0x0F);
          break;
     case 7:
          bit_Cal(4, 0x0E, 0x0A);bit_Cal(5, 0x0F, 0x08);
          break;
     case 8:
          bit_Cal(4, 0x0E, 0x0E);bit_Cal(5, 0x0F, 0x0F);
          break;
     case 9:
          bit_Cal(4, 0x0E, 0x0E);bit_Cal(5, 0x0F, 0x0D);
          break;
     default:
          break;
     }

     Val = work_num[3].Time.Display_Set % 3600 / 60 / 10; // 计算十分位为单位的分钟数
     switch (Val)
     {
     case 0:
          bit_Cal(2, 0x0E, 0x0A);bit_Cal(3, 0x0F, 0x0F);
          break;
     case 1:
          bit_Cal(2, 0x0E, 0x0A);bit_Cal(3, 0x0F, 0x00);
          break;
     case 2:
          bit_Cal(2, 0x0E, 0x0C);bit_Cal(3, 0x0F, 0x0B);
          break;
     case 3:
          bit_Cal(2, 0x0E, 0x0E);bit_Cal(3, 0x0F, 0x09);
          break;
     case 4:
          bit_Cal(2, 0x0E, 0x0E);bit_Cal(3, 0x0F, 0x04);
          break;
     case 5:
          bit_Cal(2, 0x0E, 0x06);bit_Cal(3, 0x0F, 0x0D);
          break;
     case 6:
          bit_Cal(2, 0x0E, 0x06);bit_Cal(3, 0x0F, 0x0F);
          break;
     case 7:
          bit_Cal(2, 0x0E, 0x0A);bit_Cal(3, 0x0F, 0x08);
          break;
     case 8:
          bit_Cal(2, 0x0E, 0x0E);bit_Cal(3, 0x0F, 0x0F);
          break;
     case 9:
          bit_Cal(2, 0x0E, 0x0E);bit_Cal(3, 0x0F, 0x0D);
          break;
     default:
          break;
     }

     Val = work_num[3].Time.Display_Set % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
     switch (Val)
     {
     case 0:
          bit_Cal(0, 0x0E, 0x0A);bit_Cal(1, 0x0F, 0x0F);
          break;
     case 1:
          bit_Cal(0, 0x0E, 0x0A);bit_Cal(1, 0x0F, 0x00);
          break;
     case 2:
          bit_Cal(0, 0x0E, 0x0C);bit_Cal(1, 0x0F, 0x0B);
          break;
     case 3:
          bit_Cal(0, 0x0E, 0x0E);bit_Cal(1, 0x0F, 0x09);
          break;
     case 4:
          bit_Cal(0, 0x0E, 0x0E);bit_Cal(1, 0x0F, 0x04);
          break;
     case 5:
          bit_Cal(0, 0x0E, 0x06);bit_Cal(1, 0x0F, 0x0D);
          break;
     case 6:
          bit_Cal(0, 0x0E, 0x06);bit_Cal(1, 0x0F, 0x0F);
          break;
     case 7:
          bit_Cal(0, 0x0E, 0x0A);bit_Cal(1, 0x0F, 0x08);
          break;
     case 8:
          bit_Cal(0, 0x0E, 0x0E);bit_Cal(1, 0x0F, 0x0F);
          break;
     case 9:
          bit_Cal(0, 0x0E, 0x0E);bit_Cal(1, 0x0F, 0x0D);
          break;
     default:
          break;
     }

     /**********工位3的实际转速显示**********/
    if (work_num[2].Speed.Display_Rel > 999) // 大于999时
    {
        Val = work_num[2].Speed.Display_Rel / 1000 % 10;
        switch (Val)
        {
        case 0:
               bit_Cal(22, 0x81, 0x80);bit_Cal(24, 0x81, 0x81);bit_Cal(28, 0x80, 0x80);bit_Cal(29, 0x81, 0x81);
            break;
        case 1:
               bit_Cal(22, 0x81, 0x00);bit_Cal(24, 0x81, 0x81);bit_Cal(28, 0x80, 0x00);bit_Cal(29, 0x81, 0x00);
            break;
        case 2:
               bit_Cal(22, 0x81, 0x81);bit_Cal(24, 0x81, 0x80);bit_Cal(28, 0x80, 0x80);bit_Cal(29, 0x81, 0x01);
            break;
        case 3:
               bit_Cal(22, 0x81, 0x81);bit_Cal(24, 0x81, 0x81);bit_Cal(28, 0x80, 0x80);bit_Cal(29, 0x81, 0x00);
            break;
        case 4:
               bit_Cal(22, 0x81, 0x01);bit_Cal(24, 0x81, 0x81);bit_Cal(28, 0x80, 0x00);bit_Cal(29, 0x81, 0x80);
            break;
        case 5:
               bit_Cal(22, 0x81, 0x81);bit_Cal(24, 0x81, 0x01);bit_Cal(28, 0x80, 0x80);bit_Cal(29, 0x81, 0x80);
            break;
        case 6:
               bit_Cal(22, 0x81, 0x81);bit_Cal(24, 0x81, 0x01);bit_Cal(28, 0x80, 0x80);bit_Cal(29, 0x81, 0x81);
            break;
        case 7:
               bit_Cal(22, 0x81, 0x80);bit_Cal(24, 0x81, 0x81);bit_Cal(28, 0x80, 0x00);bit_Cal(29, 0x81, 0x00);
            break;
        case 8:
               bit_Cal(22, 0x81, 0x81);bit_Cal(24, 0x81, 0x81);bit_Cal(28, 0x80, 0x80);bit_Cal(29, 0x81, 0x81);
            break;
        case 9:
               bit_Cal(22, 0x81, 0x81);bit_Cal(24, 0x81, 0x81);bit_Cal(28, 0x80, 0x80);bit_Cal(29, 0x81, 0x80);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(22, 0x81, 0x80);bit_Cal(24, 0x81, 0x81);bit_Cal(28, 0x80, 0x80);bit_Cal(29, 0x81, 0x81);
    }
    
   if (work_num[2].Speed.Display_Rel > 99) // 大于99时
   {
       Val = work_num[2].Speed.Display_Rel / 100 % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(28, 0x70, 0x50);bit_Cal(26, 0xF0, 0xF0);
            break;
        case 1:
               bit_Cal(28, 0x70, 0x50);bit_Cal(26, 0xF0, 0x00);
            break;
        case 2:
               bit_Cal(28, 0x70, 0x60);bit_Cal(26, 0xF0, 0xB0);
            break;
        case 3:
               bit_Cal(28, 0x70, 0x70);bit_Cal(26, 0xF0, 0x90);
            break;
        case 4:
               bit_Cal(28, 0x70, 0x70);bit_Cal(26, 0xF0, 0x40);
            break;
        case 5:
               bit_Cal(28, 0x70, 0x30);bit_Cal(26, 0xF0, 0xD0);
            break;
        case 6:
               bit_Cal(28, 0x70, 0x30);bit_Cal(26, 0xF0, 0xF0);
            break;
        case 7:
               bit_Cal(28, 0x70, 0x50);bit_Cal(26, 0xF0, 0x80);
            break;
        case 8:
               bit_Cal(28, 0x70, 0x70);bit_Cal(26, 0xF0, 0xF0);
            break;
        case 9:
               bit_Cal(28, 0x70, 0x70);bit_Cal(26, 0xF0, 0xD0);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(28, 0x70, 0x50);bit_Cal(26, 0xF0, 0xF0);
    }

   if (work_num[2].Speed.Display_Rel > 9) // 大于9时
   {
       Val = work_num[2].Speed.Display_Rel / 10 % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(24, 0x70, 0x50);bit_Cal(25, 0xF0, 0xF0);
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
    }
    else
    {
        bit_Cal(24, 0x70, 0x50);bit_Cal(25, 0xF0, 0xF0);
    }
   
   if (work_num[2].Speed.Display_Rel >= 0) // 大于等于0时
   {
       Val = work_num[2].Speed.Display_Rel % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(22, 0x70, 0x50);bit_Cal(23, 0xF0, 0xF0);
            break;
        case 1:
               bit_Cal(22, 0x70, 0x50);bit_Cal(23, 0xF0, 0x00);
            break;
        case 2:
               bit_Cal(22, 0x70, 0x60);bit_Cal(23, 0xF0, 0xB0);
            break;
        case 3:
               bit_Cal(22, 0x70, 0x70);bit_Cal(23, 0xF0, 0x90);
            break;
        case 4:
               bit_Cal(22, 0x70, 0x70);bit_Cal(23, 0xF0, 0x40);
            break;
        case 5:
               bit_Cal(22, 0x70, 0x30);bit_Cal(23, 0xF0, 0xD0);
            break;
        case 6:
               bit_Cal(22, 0x70, 0x30);bit_Cal(23, 0xF0, 0xF0);
            break;
        case 7:
               bit_Cal(22, 0x70, 0x50);bit_Cal(23, 0xF0, 0x80);
            break;
        case 8:
               bit_Cal(22, 0x70, 0x70);bit_Cal(23, 0xF0, 0xF0);
            break;
        case 9:
               bit_Cal(22, 0x70, 0x70);bit_Cal(23, 0xF0, 0xD0);
            break;
        default:
           break;
        }
    }

    /**********工位3的设定转速显示**********/
    if (work_num[2].Speed.Display_Set > 999) // 大于999时
    {
        Val = work_num[2].Speed.Display_Set / 1000 % 10;
        switch (Val)
        {
        case 0:
               bit_Cal(29, 0x70, 0x50);bit_Cal(21, 0xF0, 0xF0);
            break;
        case 1:
               bit_Cal(29, 0x70, 0x50);bit_Cal(21, 0xF0, 0x00);
            break;
        case 2:
               bit_Cal(29, 0x70, 0x60);bit_Cal(21, 0xF0, 0xB0);
            break;
        case 3:
               bit_Cal(29, 0x70, 0x70);bit_Cal(21, 0xF0, 0x90);
            break;
        case 4:
               bit_Cal(29, 0x70, 0x70);bit_Cal(21, 0xF0, 0x40);
            break;
        case 5:
               bit_Cal(29, 0x70, 0x30);bit_Cal(21, 0xF0, 0xD0);
            break;
        case 6:
               bit_Cal(29, 0x70, 0x30);bit_Cal(21, 0xF0, 0xF0);
            break;
        case 7:
               bit_Cal(29, 0x70, 0x50);bit_Cal(21, 0xF0, 0x80);
            break;
        case 8:
               bit_Cal(29, 0x70, 0x70);bit_Cal(21, 0xF0, 0xF0);
            break;
        case 9:
               bit_Cal(29, 0x70, 0x70);bit_Cal(21, 0xF0, 0xD0);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(29, 0x70, 0x50);bit_Cal(21, 0xF0, 0xF0);
    }
    
   if (work_num[2].Speed.Display_Set > 99) // 大于99时
   {
       Val = work_num[2].Speed.Display_Set / 100 % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(19, 0x70, 0x50);bit_Cal(20, 0xF0, 0xF0);
            break;
        case 1:
               bit_Cal(19, 0x70, 0x50);bit_Cal(20, 0xF0, 0x00);
            break;
        case 2:
               bit_Cal(19, 0x70, 0x60);bit_Cal(20, 0xF0, 0xB0);
            break;
        case 3:
               bit_Cal(19, 0x70, 0x70);bit_Cal(20, 0xF0, 0x90);
            break;
        case 4:
               bit_Cal(19, 0x70, 0x70);bit_Cal(20, 0xF0, 0x40);
            break;
        case 5:
               bit_Cal(19, 0x70, 0x30);bit_Cal(20, 0xF0, 0xD0);
            break;
        case 6:
               bit_Cal(19, 0x70, 0x30);bit_Cal(20, 0xF0, 0xF0);
            break;
        case 7:
               bit_Cal(19, 0x70, 0x50);bit_Cal(20, 0xF0, 0x80);
            break;
        case 8:
               bit_Cal(19, 0x70, 0x70);bit_Cal(20, 0xF0, 0xF0);
            break;
        case 9:
               bit_Cal(19, 0x70, 0x70);bit_Cal(20, 0xF0, 0xD0);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(19, 0x70, 0x50);bit_Cal(20, 0xF0, 0xF0);
    }

   if (work_num[2].Speed.Display_Set > 9) // 大于9时
   {
       Val = work_num[2].Speed.Display_Set / 10 % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(30, 0x70, 0x50);bit_Cal(18, 0xF0, 0xF0);
            break;
        case 1:
               bit_Cal(30, 0x70, 0x50);bit_Cal(18, 0xF0, 0x00);
            break;
        case 2:
               bit_Cal(30, 0x70, 0x60);bit_Cal(18, 0xF0, 0xB0);
            break;
        case 3:
               bit_Cal(30, 0x70, 0x70);bit_Cal(18, 0xF0, 0x90);
            break;
        case 4:
               bit_Cal(30, 0x70, 0x70);bit_Cal(18, 0xF0, 0x40);
            break;
        case 5:
               bit_Cal(30, 0x70, 0x30);bit_Cal(18, 0xF0, 0xD0);
            break;
        case 6:
               bit_Cal(30, 0x70, 0x30);bit_Cal(18, 0xF0, 0xF0);
            break;
        case 7:
               bit_Cal(30, 0x70, 0x50);bit_Cal(18, 0xF0, 0x80);
            break;
        case 8:
               bit_Cal(30, 0x70, 0x70);bit_Cal(18, 0xF0, 0xF0);
            break;
        case 9:
               bit_Cal(30, 0x70, 0x70);bit_Cal(18, 0xF0, 0xD0);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(30, 0x70, 0x50);bit_Cal(18, 0xF0, 0xF0);
    }
   
   if (work_num[2].Speed.Display_Set>= 0) // 大于等于0时
   {
       Val = work_num[2].Speed.Display_Set % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(16, 0x70, 0x50);bit_Cal(17, 0xF0, 0xF0);
            break;
        case 1:
               bit_Cal(16, 0x70, 0x50);bit_Cal(17, 0xF0, 0x00);
            break;
        case 2:
               bit_Cal(16, 0x70, 0x60);bit_Cal(17, 0xF0, 0xB0);
            break;
        case 3:
               bit_Cal(16, 0x70, 0x70);bit_Cal(17, 0xF0, 0x90);
            break;
        case 4:
               bit_Cal(16, 0x70, 0x70);bit_Cal(17, 0xF0, 0x40);
            break;
        case 5:
               bit_Cal(16, 0x70, 0x30);bit_Cal(17, 0xF0, 0xD0);
            break;
        case 6:
               bit_Cal(16, 0x70, 0x30);bit_Cal(17, 0xF0, 0xF0);
            break;
        case 7:
               bit_Cal(16, 0x70, 0x50);bit_Cal(17, 0xF0, 0x80);
            break;
        case 8:
               bit_Cal(16, 0x70, 0x70);bit_Cal(17, 0xF0, 0xF0);
            break;
        case 9:
               bit_Cal(16, 0x70, 0x70);bit_Cal(17, 0xF0, 0xD0);
            break;
        default:
           break;
        }
    }

    /**********工位3的实际时间显示**********/
     Val = work_num[2].Time.Display_Rel / 3600 / 10;//计算十位为单位的小时数
     switch (Val)
     {
     case 0:
          bit_Cal(27, 0x7F, 0x77);
          break;
     case 1:
          bit_Cal(27, 0x7F, 0x12);
          break;
     case 2:
          bit_Cal(27, 0x7F, 0x5D);
          break;
     case 3:
          bit_Cal(27, 0x7F, 0x5B);
          break;
     case 4:
          bit_Cal(27, 0x7F, 0x3A);
          break;
     case 5:
          bit_Cal(27, 0x7F, 0x6B);
          break;
     case 6:
          bit_Cal(27, 0x7F, 0x6F);
          break;
     case 7:
          bit_Cal(27, 0x7F, 0x52);
          break;
     case 8:
          bit_Cal(27, 0x7F, 0x7F);
          break;
     case 9:
          bit_Cal(27, 0x7F, 0x7B);
          break;
     default:
          break;
     }

     Val = work_num[2].Time.Display_Rel / 3600 % 10;// 计算个位为单位的小时数
     switch (Val)
     {
     case 0:
          bit_Cal(28, 0x0E, 0x0A);bit_Cal(26, 0x0F, 0x0F);
          break;
     case 1:
          bit_Cal(28, 0x0E, 0x0A);bit_Cal(26, 0x0F, 0x00);
          break;
     case 2:
          bit_Cal(28, 0x0E, 0x0C);bit_Cal(26, 0x0F, 0x0B);
          break;
     case 3:
          bit_Cal(28, 0x0E, 0x0E);bit_Cal(26, 0x0F, 0x09);
          break;
     case 4:
          bit_Cal(28, 0x0E, 0x0E);bit_Cal(26, 0x0F, 0x04);
          break;
     case 5:
          bit_Cal(28, 0x0E, 0x06);bit_Cal(26, 0x0F, 0x0D);
          break;
     case 6:
          bit_Cal(28, 0x0E, 0x06);bit_Cal(26, 0x0F, 0x0F);
          break;
     case 7:
          bit_Cal(28, 0x0E, 0x0A);bit_Cal(26, 0x0F, 0x08);
          break;
     case 8:
          bit_Cal(28, 0x0E, 0x0E);bit_Cal(26, 0x0F, 0x0F);
          break;
     case 9:
          bit_Cal(28, 0x0E, 0x0E);bit_Cal(26, 0x0F, 0x0D);
          break;
     default:
          break;
     }

     Val = work_num[2].Time.Display_Rel % 3600 / 60 / 10; // 计算十分位为单位的分钟数
     switch (Val)
     {
     case 0:
          bit_Cal(24, 0x0E, 0x0A);bit_Cal(25, 0x0F, 0x0F);
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

     Val = work_num[2].Time.Display_Rel % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
     switch (Val)
     {
     case 0:
          bit_Cal(22, 0x0E, 0x0A);bit_Cal(23, 0x0F, 0x0F);
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
          bit_Cal(22, 0x0E, 0x06);bit_Cal(23, 0x0F, 0x0F);
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

     /**********工位3的设定时间显示**********/
     Val = work_num[2].Time.Display_Set / 3600 / 10;//计算十位为单位的小时数
     switch (Val)
     {
     case 0:
          bit_Cal(29, 0x0E, 0x0A);bit_Cal(21, 0x0F, 0x0F);
          break;
     case 1:
          bit_Cal(29, 0x0E, 0x0A);bit_Cal(21, 0x0F, 0x00);
          break;
     case 2:
          bit_Cal(29, 0x0E, 0x0C);bit_Cal(21, 0x0F, 0x0B);
          break;
     case 3:
          bit_Cal(29, 0x0E, 0x0E);bit_Cal(21, 0x0F, 0x09);
          break;
     case 4:
          bit_Cal(29, 0x0E, 0x0E);bit_Cal(21, 0x0F, 0x04);
          break;
     case 5:
          bit_Cal(29, 0x0E, 0x06);bit_Cal(21, 0x0F, 0x0D);
          break;
     case 6:
          bit_Cal(29, 0x0E, 0x06);bit_Cal(21, 0x0F, 0x0F);
          break;
     case 7:
          bit_Cal(29, 0x0E, 0x0A);bit_Cal(21, 0x0F, 0x08);
          break;
     case 8:
          bit_Cal(29, 0x0E, 0x0E);bit_Cal(21, 0x0F, 0x0F);
          break;
     case 9:
          bit_Cal(29, 0x0E, 0x0E);bit_Cal(21, 0x0F, 0x0D);
          break;
     default:
          break;
     }

     Val = work_num[2].Time.Display_Set / 3600 % 10;// 计算个位为单位的小时数
     switch (Val)
     {
     case 0:
          bit_Cal(19, 0x0E, 0x0A);bit_Cal(20, 0x0F, 0x0F);
          break;
     case 1:
          bit_Cal(19, 0x0E, 0x0A);bit_Cal(20, 0x0F, 0x00);
          break;
     case 2:
          bit_Cal(19, 0x0E, 0x0C);bit_Cal(20, 0x0F, 0x0B);
          break;
     case 3:
          bit_Cal(19, 0x0E, 0x0E);bit_Cal(20, 0x0F, 0x09);
          break;
     case 4:
          bit_Cal(19, 0x0E, 0x0E);bit_Cal(20, 0x0F, 0x04);
          break;
     case 5:
          bit_Cal(19, 0x0E, 0x06);bit_Cal(20, 0x0F, 0x0D);
          break;
     case 6:
          bit_Cal(19, 0x0E, 0x06);bit_Cal(20, 0x0F, 0x0F);
          break;
     case 7:
          bit_Cal(19, 0x0E, 0x0A);bit_Cal(20, 0x0F, 0x08);
          break;
     case 8:
          bit_Cal(19, 0x0E, 0x0E);bit_Cal(20, 0x0F, 0x0F);
          break;
     case 9:
          bit_Cal(19, 0x0E, 0x0E);bit_Cal(20, 0x0F, 0x0D);
          break;
     default:
          break;
     }

     Val = work_num[2].Time.Display_Set % 3600 / 60 / 10; // 计算十分位为单位的分钟数
     switch (Val)
     {
     case 0:
          bit_Cal(30, 0x0E, 0x0A);bit_Cal(18, 0x0F, 0x0F);
          break;
     case 1:
          bit_Cal(30, 0x0E, 0x0A);bit_Cal(18, 0x0F, 0x00);
          break;
     case 2:
          bit_Cal(30, 0x0E, 0x0C);bit_Cal(18, 0x0F, 0x0B);
          break;
     case 3:
          bit_Cal(30, 0x0E, 0x0E);bit_Cal(18, 0x0F, 0x09);
          break;
     case 4:
          bit_Cal(30, 0x0E, 0x0E);bit_Cal(18, 0x0F, 0x04);
          break;
     case 5:
          bit_Cal(30, 0x0E, 0x06);bit_Cal(18, 0x0F, 0x0D);
          break;
     case 6:
          bit_Cal(30, 0x0E, 0x06);bit_Cal(18, 0x0F, 0x0F);
          break;
     case 7:
          bit_Cal(30, 0x0E, 0x0A);bit_Cal(18, 0x0F, 0x08);
          break;
     case 8:
          bit_Cal(30, 0x0E, 0x0E);bit_Cal(18, 0x0F, 0x0F);
          break;
     case 9:
          bit_Cal(30, 0x0E, 0x0E);bit_Cal(18, 0x0F, 0x0D);
          break;
     default:
          break;
     }

     Val = work_num[2].Time.Display_Set % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
     switch (Val)
     {
     case 0:
          bit_Cal(16, 0x0E, 0x0A);bit_Cal(17, 0x0F, 0x0F);
          break;
     case 1:
          bit_Cal(16, 0x0E, 0x0A);bit_Cal(17, 0x0F, 0x00);
          break;
     case 2:
          bit_Cal(16, 0x0E, 0x0C);bit_Cal(17, 0x0F, 0x0B);
          break;
     case 3:
          bit_Cal(16, 0x0E, 0x0E);bit_Cal(17, 0x0F, 0x09);
          break;
     case 4:
          bit_Cal(16, 0x0E, 0x0E);bit_Cal(17, 0x0F, 0x04);
          break;
     case 5:
          bit_Cal(16, 0x0E, 0x06);bit_Cal(17, 0x0F, 0x0D);
          break;
     case 6:
          bit_Cal(16, 0x0E, 0x06);bit_Cal(17, 0x0F, 0x0F);
          break;
     case 7:
          bit_Cal(16, 0x0E, 0x0A);bit_Cal(17, 0x0F, 0x08);
          break;
     case 8:
          bit_Cal(16, 0x0E, 0x0E);bit_Cal(17, 0x0F, 0x0F);
          break;
     case 9:
          bit_Cal(16, 0x0E, 0x0E);bit_Cal(17, 0x0F, 0x0D);
          break;
     default:
          break;
     }

     /**********工位4'RPM'显示**********/
     bit_Cal(0, 0x80, 0x80);

     /**********工位4'min'显示**********/
     bit_Cal(0, 0x01, 0x01);

     /**********工位4设定时间'：'显示**********/
     bit_Cal(4, 0x01, 0x01);

     /**********右边横杠显示**********/
     bit_Cal(6, 0x80, 0x80);

     /**********中间锁图标显示**********/
     bit_Cal(6, 0x01, 0x01);

     /**********工位4转速图标S19显示**********/
     bit_Cal(10, 0x80, 0x80);

     /**********工位4转速图标S20显示**********/
     bit_Cal(8, 0x80, 0x80);

     /**********工位4转速图标S21显示**********/
     bit_Cal(8, 0x01, 0x01);

     /**********左边横杠显示**********/
     bit_Cal(10, 0x01, 0x01);

     /**********下面竖线显示**********/
     bit_Cal(12, 0x80, 0x80);

     /**********工位4实际时间'：'显示**********/
     bit_Cal(12, 0x01, 0x01);

     /**********时间图标显示**********/
     bit_Cal(14, 0x80, 0x80);

     /**********工位3'RPM'显示**********/
     bit_Cal(16, 0x80, 0x80);

     /**********工位3'min'显示**********/
     bit_Cal(16, 0x01, 0x01); 

     /**********工位3转速图标S12显示**********/
     bit_Cal(19, 0x80, 0x80);

     /**********工位3转速图标S10显示**********/
     bit_Cal(30, 0x80, 0x80);

     /**********工位3转速图标S0显示**********/
     bit_Cal(30, 0x01, 0x01);

     /**********工位4设定时间'：'显示**********/
     bit_Cal(19, 0x01, 0x01);

     /**********时间图标显示**********/
     bit_Cal(27, 0x80, 0x80);

     /**********工位3实际时间'：'显示**********/
     bit_Cal(28, 0x01, 0x01);


     /******************** IC2 ********************/
     /**********工位2的实际转速显示**********/
     if (work_num[1].Speed.Display_Rel > 999) // 大于999时
     {
        Val = work_num[1].Speed.Display_Rel / 1000 % 10;
        switch (Val)
        {
        case 0:
               bit_Cal(45, 0x0E, 0x0A);bit_Cal(46, 0x0F, 0x0F);
            break;
        case 1:
               bit_Cal(45, 0x0E, 0x0A);bit_Cal(46, 0x0F, 0x00);
            break;
        case 2:
               bit_Cal(45, 0x0E, 0x06);bit_Cal(46, 0x0F, 0x0D);
            break;
        case 3:
               bit_Cal(45, 0x0E, 0x0E);bit_Cal(46, 0x0F, 0x09);
            break;
        case 4:
               bit_Cal(45, 0x0E, 0x0E);bit_Cal(46, 0x0F, 0x02);
            break;
        case 5:
               bit_Cal(45, 0x0E, 0x0C);bit_Cal(46, 0x0F, 0x0B);
            break;
        case 6:
               bit_Cal(45, 0x0E, 0x0C);bit_Cal(46, 0x0F, 0x0F);
            break;
        case 7:
               bit_Cal(45, 0x0E, 0x0A);bit_Cal(46, 0x0F, 0x01);
            break;
        case 8:
               bit_Cal(45, 0x0E, 0x0E);bit_Cal(46, 0x0F, 0x0F);
            break;
        case 9:
               bit_Cal(45, 0x0E, 0x0E);bit_Cal(46, 0x0F, 0x0B);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(45, 0x0E, 0x0A);bit_Cal(46, 0x0F, 0x0F);
    }
    
   if (work_num[1].Speed.Display_Rel > 99) // 大于99时
   {
       Val = work_num[1].Speed.Display_Rel / 100 % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(43, 0x0E, 0x0A);bit_Cal(44, 0x0F, 0x0F);
            break;
        case 1:
               bit_Cal(43, 0x0E, 0x0A);bit_Cal(44, 0x0F, 0x00);
            break;
        case 2:
               bit_Cal(43, 0x0E, 0x06);bit_Cal(44, 0x0F, 0x0D);
            break;
        case 3:
               bit_Cal(43, 0x0E, 0x0E);bit_Cal(44, 0x0F, 0x09);
            break;
        case 4:
               bit_Cal(43, 0x0E, 0x0E);bit_Cal(44, 0x0F, 0x02);
            break;
        case 5:
               bit_Cal(43, 0x0E, 0x0C);bit_Cal(44, 0x0F, 0x0B);
            break;
        case 6:
               bit_Cal(43, 0x0E, 0x0C);bit_Cal(44, 0x0F, 0x0F);
            break;
        case 7:
               bit_Cal(43, 0x0E, 0x0A);bit_Cal(44, 0x0F, 0x01);
            break;
        case 8:
               bit_Cal(43, 0x0E, 0x0E);bit_Cal(44, 0x0F, 0x0F);
            break;
        case 9:
               bit_Cal(43, 0x0E, 0x0E);bit_Cal(44, 0x0F, 0x0B);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(43, 0x0E, 0x0A);bit_Cal(44, 0x0F, 0x0F);
    }

   if (work_num[1].Speed.Display_Rel > 9) // 大于9时
   {
       Val = work_num[1].Speed.Display_Rel / 10 % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(41, 0x0E, 0x0A);bit_Cal(42, 0x0F, 0x0F);
            break;
        case 1:
               bit_Cal(41, 0x0E, 0x0A);bit_Cal(42, 0x0F, 0x00);
            break;
        case 2:
               bit_Cal(41, 0x0E, 0x06);bit_Cal(42, 0x0F, 0x0D);
            break;
        case 3:
               bit_Cal(41, 0x0E, 0x0E);bit_Cal(42, 0x0F, 0x09);
            break;
        case 4:
               bit_Cal(41, 0x0E, 0x0E);bit_Cal(42, 0x0F, 0x02);
            break;
        case 5:
               bit_Cal(41, 0x0E, 0x0C);bit_Cal(42, 0x0F, 0x0B);
            break;
        case 6:
               bit_Cal(41, 0x0E, 0x0C);bit_Cal(42, 0x0F, 0x0F);
            break;
        case 7:
               bit_Cal(41, 0x0E, 0x0A);bit_Cal(42, 0x0F, 0x01);
            break;
        case 8:
               bit_Cal(41, 0x0E, 0x0E);bit_Cal(42, 0x0F, 0x0F);
            break;
        case 9:
               bit_Cal(41, 0x0E, 0x0E);bit_Cal(42, 0x0F, 0x0B);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(41, 0x0E, 0x0A);bit_Cal(42, 0x0F, 0x0F);
    }
   
   if (work_num[1].Speed.Display_Rel>= 0) // 大于等于0时
   {
       Val = work_num[1].Speed.Display_Rel % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(39, 0x0E, 0x0A);bit_Cal(40, 0x0F, 0x0F);
            break;
        case 1:
               bit_Cal(39, 0x0E, 0x0A);bit_Cal(40, 0x0F, 0x00);
            break;
        case 2:
               bit_Cal(39, 0x0E, 0x06);bit_Cal(40, 0x0F, 0x0D);
            break;
        case 3:
               bit_Cal(39, 0x0E, 0x0E);bit_Cal(40, 0x0F, 0x09);
            break;
        case 4:
               bit_Cal(39, 0x0E, 0x0E);bit_Cal(40, 0x0F, 0x02);
            break;
        case 5:
               bit_Cal(39, 0x0E, 0x0C);bit_Cal(40, 0x0F, 0x0B);
            break;
        case 6:
               bit_Cal(39, 0x0E, 0x0C);bit_Cal(40, 0x0F, 0x0F);
            break;
        case 7:
               bit_Cal(39, 0x0E, 0x0A);bit_Cal(40, 0x0F, 0x01);
            break;
        case 8:
               bit_Cal(39, 0x0E, 0x0E);bit_Cal(40, 0x0F, 0x0F);
            break;
        case 9:
               bit_Cal(39, 0x0E, 0x0E);bit_Cal(40, 0x0F, 0x0B);
            break;
        default:
           break;
        }
    }
    /**********工位2的设定转速显示**********/
     if (work_num[1].Speed.Display_Set > 999) // 大于999时
     {
        Val = work_num[1].Speed.Display_Set / 1000 % 10;
        switch (Val)
        {
        case 0:
               bit_Cal(37, 0x0E, 0x0A);bit_Cal(38, 0x0F, 0x0F);
            break;
        case 1:
               bit_Cal(37, 0x0E, 0x0A);bit_Cal(38, 0x0F, 0x00);
            break;
        case 2:
               bit_Cal(37, 0x0E, 0x06);bit_Cal(38, 0x0F, 0x0D);
            break;
        case 3:
               bit_Cal(37, 0x0E, 0x0E);bit_Cal(38, 0x0F, 0x09);
            break;
        case 4:
               bit_Cal(37, 0x0E, 0x0E);bit_Cal(38, 0x0F, 0x02);
            break;
        case 5:
               bit_Cal(37, 0x0E, 0x0C);bit_Cal(38, 0x0F, 0x0B);
            break;
        case 6:
               bit_Cal(37, 0x0E, 0x0C);bit_Cal(38, 0x0F, 0x0F);
            break;
        case 7:
               bit_Cal(37, 0x0E, 0x0A);bit_Cal(38, 0x0F, 0x01);
            break;
        case 8:
               bit_Cal(37, 0x0E, 0x0E);bit_Cal(38, 0x0F, 0x0F);
            break;
        case 9:
               bit_Cal(37, 0x0E, 0x0E);bit_Cal(38, 0x0F, 0x0B);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(37, 0x0E, 0x0A);bit_Cal(38, 0x0F, 0x0F);
    }
    
   if (work_num[1].Speed.Display_Set > 99) // 大于99时
   {
       Val = work_num[1].Speed.Display_Set / 100 % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(35, 0x0E, 0x0A);bit_Cal(36, 0x0F, 0x0F);
            break;
        case 1:
               bit_Cal(35, 0x0E, 0x0A);bit_Cal(36, 0x0F, 0x00);
            break;
        case 2:
               bit_Cal(35, 0x0E, 0x06);bit_Cal(36, 0x0F, 0x0D);
            break;
        case 3:
               bit_Cal(35, 0x0E, 0x0E);bit_Cal(36, 0x0F, 0x09);
            break;
        case 4:
               bit_Cal(35, 0x0E, 0x0E);bit_Cal(36, 0x0F, 0x02);
            break;
        case 5:
               bit_Cal(35, 0x0E, 0x0C);bit_Cal(36, 0x0F, 0x0B);
            break;
        case 6:
               bit_Cal(35, 0x0E, 0x0C);bit_Cal(36, 0x0F, 0x0F);
            break;
        case 7:
               bit_Cal(35, 0x0E, 0x0A);bit_Cal(36, 0x0F, 0x01);
            break;
        case 8:
               bit_Cal(35, 0x0E, 0x0E);bit_Cal(36, 0x0F, 0x0F);
            break;
        case 9:
               bit_Cal(35, 0x0E, 0x0E);bit_Cal(36, 0x0F, 0x0B);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(35, 0x0E, 0x0A);bit_Cal(36, 0x0F, 0x0F);
    }

   if (work_num[1].Speed.Display_Set > 9) // 大于9时
   {
       Val = work_num[1].Speed.Display_Set / 10 % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(33, 0x0E, 0x0A);bit_Cal(34, 0x0F, 0x0F);
            break;
        case 1:
               bit_Cal(33, 0x0E, 0x0A);bit_Cal(34, 0x0F, 0x00);
            break;
        case 2:
               bit_Cal(33, 0x0E, 0x06);bit_Cal(34, 0x0F, 0x0D);
            break;
        case 3:
               bit_Cal(33, 0x0E, 0x0E);bit_Cal(34, 0x0F, 0x09);
            break;
        case 4:
               bit_Cal(33, 0x0E, 0x0E);bit_Cal(34, 0x0F, 0x02);
            break;
        case 5:
               bit_Cal(33, 0x0E, 0x0C);bit_Cal(34, 0x0F, 0x0B);
            break;
        case 6:
               bit_Cal(33, 0x0E, 0x0C);bit_Cal(34, 0x0F, 0x0F);
            break;
        case 7:
               bit_Cal(33, 0x0E, 0x0A);bit_Cal(34, 0x0F, 0x01);
            break;
        case 8:
               bit_Cal(33, 0x0E, 0x0E);bit_Cal(34, 0x0F, 0x0F);
            break;
        case 9:
               bit_Cal(33, 0x0E, 0x0E);bit_Cal(34, 0x0F, 0x0B);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(33, 0x0E, 0x0A);bit_Cal(34, 0x0F, 0x0F);
    }
   
   if (work_num[1].Speed.Display_Set>= 0) // 大于等于0时
   {
       Val = work_num[1].Speed.Display_Set % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(31, 0x0E, 0x0A);bit_Cal(32, 0x0F, 0x0F);
            break;
        case 1:
               bit_Cal(31, 0x0E, 0x0A);bit_Cal(32, 0x0F, 0x00);
            break;
        case 2:
               bit_Cal(31, 0x0E, 0x06);bit_Cal(32, 0x0F, 0x0D);
            break;
        case 3:
               bit_Cal(31, 0x0E, 0x0E);bit_Cal(32, 0x0F, 0x09);
            break;
        case 4:
               bit_Cal(31, 0x0E, 0x0E);bit_Cal(32, 0x0F, 0x02);
            break;
        case 5:
               bit_Cal(31, 0x0E, 0x0C);bit_Cal(32, 0x0F, 0x0B);
            break;
        case 6:
               bit_Cal(31, 0x0E, 0x0C);bit_Cal(32, 0x0F, 0x0F);
            break;
        case 7:
               bit_Cal(31, 0x0E, 0x0A);bit_Cal(32, 0x0F, 0x01);
            break;
        case 8:
               bit_Cal(31, 0x0E, 0x0E);bit_Cal(32, 0x0F, 0x0F);
            break;
        case 9:
               bit_Cal(31, 0x0E, 0x0E);bit_Cal(32, 0x0F, 0x0B);
            break;
        default:
           break;
        }
     }

     /**********工位2的实际时间显示**********/
     Val = work_num[1].Time.Display_Rel / 3600 / 10;//计算十位为单位的小时数
     switch (Val)
     {
     case 0:
          bit_Cal(45, 0x70, 0x50);bit_Cal(46, 0xF0, 0xF0);
          break;
     case 1:
          bit_Cal(45, 0x70, 0x50);bit_Cal(46, 0xF0, 0x00);
          break;
     case 2:
          bit_Cal(45, 0x70, 0x30);bit_Cal(46, 0xF0, 0xD0);
          break;
     case 3:
          bit_Cal(45, 0x70, 0x70);bit_Cal(46, 0xF0, 0x90);
          break;
     case 4:
          bit_Cal(45, 0x70, 0x70);bit_Cal(46, 0xF0, 0x20);
          break;
     case 5:
          bit_Cal(45, 0x70, 0x60);bit_Cal(46, 0xF0, 0xB0);
          break;
     case 6:
          bit_Cal(45, 0x70, 0x60);bit_Cal(46, 0xF0, 0xF0);
          break;
     case 7:
          bit_Cal(45, 0x70, 0x50);bit_Cal(46, 0xF0, 0x10);
          break;
     case 8:
          bit_Cal(45, 0x70, 0x70);bit_Cal(46, 0xF0, 0xF0);
          break;
     case 9:
          bit_Cal(45, 0x70, 0x70);bit_Cal(46, 0xF0, 0xB0);
          break;
     default:
          break;
     }

     Val = work_num[1].Time.Display_Rel / 3600 % 10;// 计算个位为单位的小时数
     switch (Val)
     {
     case 0:
          bit_Cal(43, 0x70, 0x50);bit_Cal(44, 0xF0, 0xF0);
          break;
     case 1:
          bit_Cal(43, 0x70, 0x50);bit_Cal(44, 0xF0, 0x00);
          break;
     case 2:
          bit_Cal(43, 0x70, 0x30);bit_Cal(44, 0xF0, 0xD0);
          break;
     case 3:
          bit_Cal(43, 0x70, 0x70);bit_Cal(44, 0xF0, 0x90);
          break;
     case 4:
          bit_Cal(43, 0x70, 0x70);bit_Cal(44, 0xF0, 0x20);
          break;
     case 5:
          bit_Cal(43, 0x70, 0x60);bit_Cal(44, 0xF0, 0xB0);
          break;
     case 6:
          bit_Cal(43, 0x70, 0x60);bit_Cal(44, 0xF0, 0xF0);
          break;
     case 7:
          bit_Cal(43, 0x70, 0x50);bit_Cal(44, 0xF0, 0x10);
          break;
     case 8:
          bit_Cal(43, 0x70, 0x70);bit_Cal(44, 0xF0, 0xF0);
          break;
     case 9:
          bit_Cal(43, 0x70, 0x70);bit_Cal(44, 0xF0, 0xB0);
          break;
     default:
          break;
     }

     Val = work_num[1].Time.Display_Rel % 3600 / 60 / 10; // 计算十分位为单位的分钟数
     switch (Val)
     {
     case 0:
          bit_Cal(41, 0x70, 0x50);bit_Cal(42, 0xF0, 0xF0);
          break;
     case 1:
          bit_Cal(41, 0x70, 0x50);bit_Cal(42, 0xF0, 0x00);
          break;
     case 2:
          bit_Cal(41, 0x70, 0x30);bit_Cal(42, 0xF0, 0xD0);
          break;
     case 3:
          bit_Cal(41, 0x70, 0x70);bit_Cal(42, 0xF0, 0x90);
          break;
     case 4:
          bit_Cal(41, 0x70, 0x70);bit_Cal(42, 0xF0, 0x20);
          break;
     case 5:
          bit_Cal(41, 0x70, 0x60);bit_Cal(42, 0xF0, 0xB0);
          break;
     case 6:
          bit_Cal(41, 0x70, 0x60);bit_Cal(42, 0xF0, 0xF0);
          break;
     case 7:
          bit_Cal(41, 0x70, 0x50);bit_Cal(42, 0xF0, 0x10);
          break;
     case 8:
          bit_Cal(41, 0x70, 0x70);bit_Cal(42, 0xF0, 0xF0);
          break;
     case 9:
          bit_Cal(41, 0x70, 0x70);bit_Cal(42, 0xF0, 0xB0);
          break;
     default:
          break;
     }

     Val = work_num[1].Time.Display_Rel % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
     switch (Val)
     {
     case 0:
          bit_Cal(39, 0x70, 0x50);bit_Cal(40, 0xF0, 0xF0);
          break;
     case 1:
          bit_Cal(39, 0x70, 0x50);bit_Cal(40, 0xF0, 0x00);
          break;
     case 2:
          bit_Cal(39, 0x70, 0x30);bit_Cal(40, 0xF0, 0xD0);
          break;
     case 3:
          bit_Cal(39, 0x70, 0x70);bit_Cal(40, 0xF0, 0x90);
          break;
     case 4:
          bit_Cal(39, 0x70, 0x70);bit_Cal(40, 0xF0, 0x20);
          break;
     case 5:
          bit_Cal(39, 0x70, 0x60);bit_Cal(40, 0xF0, 0xB0);
          break;
     case 6:
          bit_Cal(39, 0x70, 0x60);bit_Cal(40, 0xF0, 0xF0);
          break;
     case 7:
          bit_Cal(39, 0x70, 0x50);bit_Cal(40, 0xF0, 0x10);
          break;
     case 8:
          bit_Cal(39, 0x70, 0x70);bit_Cal(40, 0xF0, 0xF0);
          break;
     case 9:
          bit_Cal(39, 0x70, 0x70);bit_Cal(40, 0xF0, 0xB0);
          break;
     default:
          break;
     }

     /**********工位2的设定时间显示**********/
     Val = work_num[1].Time.Display_Set / 3600 / 10;//计算十位为单位的小时数
     switch (Val)
     {
     case 0:
          bit_Cal(37, 0x70, 0x50);bit_Cal(38, 0xF0, 0xF0);
          break;
     case 1:
          bit_Cal(37, 0x70, 0x50);bit_Cal(38, 0xF0, 0x00);
          break;
     case 2:
          bit_Cal(37, 0x70, 0x30);bit_Cal(38, 0xF0, 0xD0);
          break;
     case 3:
          bit_Cal(37, 0x70, 0x70);bit_Cal(38, 0xF0, 0x90);
          break;
     case 4:
          bit_Cal(37, 0x70, 0x70);bit_Cal(38, 0xF0, 0x20);
          break;
     case 5:
          bit_Cal(37, 0x70, 0x60);bit_Cal(38, 0xF0, 0xB0);
          break;
     case 6:
          bit_Cal(37, 0x70, 0x60);bit_Cal(38, 0xF0, 0xF0);
          break;
     case 7:
          bit_Cal(37, 0x70, 0x50);bit_Cal(38, 0xF0, 0x10);
          break;
     case 8:
          bit_Cal(37, 0x70, 0x70);bit_Cal(38, 0xF0, 0xF0);
          break;
     case 9:
          bit_Cal(37, 0x70, 0x70);bit_Cal(38, 0xF0, 0xB0);
          break;
     default:
          break;
     }

     Val = work_num[1].Time.Display_Set / 3600 % 10;// 计算个位为单位的小时数
     switch (Val)
     {
     case 0:
          bit_Cal(35, 0x70, 0x50);bit_Cal(36, 0xF0, 0xF0);
          break;
     case 1:
          bit_Cal(35, 0x70, 0x50);bit_Cal(36, 0xF0, 0x00);
          break;
     case 2:
          bit_Cal(35, 0x70, 0x30);bit_Cal(36, 0xF0, 0xD0);
          break;
     case 3:
          bit_Cal(35, 0x70, 0x70);bit_Cal(36, 0xF0, 0x90);
          break;
     case 4:
          bit_Cal(35, 0x70, 0x70);bit_Cal(36, 0xF0, 0x20);
          break;
     case 5:
          bit_Cal(35, 0x70, 0x60);bit_Cal(36, 0xF0, 0xB0);
          break;
     case 6:
          bit_Cal(35, 0x70, 0x60);bit_Cal(36, 0xF0, 0xF0);
          break;
     case 7:
          bit_Cal(35, 0x70, 0x50);bit_Cal(36, 0xF0, 0x10);
          break;
     case 8:
          bit_Cal(35, 0x70, 0x70);bit_Cal(36, 0xF0, 0xF0);
          break;
     case 9:
          bit_Cal(35, 0x70, 0x70);bit_Cal(36, 0xF0, 0xB0);
          break;
     default:
          break;
     }

     Val = work_num[1].Time.Display_Set % 3600 / 60 / 10; // 计算十分位为单位的分钟数
     switch (Val)
     {
     case 0:
          bit_Cal(33, 0x70, 0x50);bit_Cal(34, 0xF0, 0xF0);
          break;
     case 1:
          bit_Cal(33, 0x70, 0x50);bit_Cal(34, 0xF0, 0x00);
          break;
     case 2:
          bit_Cal(33, 0x70, 0x30);bit_Cal(34, 0xF0, 0xD0);
          break;
     case 3:
          bit_Cal(33, 0x70, 0x70);bit_Cal(34, 0xF0, 0x90);
          break;
     case 4:
          bit_Cal(33, 0x70, 0x70);bit_Cal(34, 0xF0, 0x20);
          break;
     case 5:
          bit_Cal(33, 0x70, 0x60);bit_Cal(34, 0xF0, 0xB0);
          break;
     case 6:
          bit_Cal(33, 0x70, 0x60);bit_Cal(34, 0xF0, 0xF0);
          break;
     case 7:
          bit_Cal(33, 0x70, 0x50);bit_Cal(34, 0xF0, 0x10);
          break;
     case 8:
          bit_Cal(33, 0x70, 0x70);bit_Cal(34, 0xF0, 0xF0);
          break;
     case 9:
          bit_Cal(33, 0x70, 0x70);bit_Cal(34, 0xF0, 0xB0);
          break;
     default:
          break;
     }

     Val = work_num[1].Time.Display_Set % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
     switch (Val)
     {
     case 0:
          bit_Cal(31, 0x70, 0x50);bit_Cal(32, 0xF0, 0xF0);
          break;
     case 1:
          bit_Cal(31, 0x70, 0x50);bit_Cal(32, 0xF0, 0x00);
          break;
     case 2:
          bit_Cal(31, 0x70, 0x30);bit_Cal(32, 0xF0, 0xD0);
          break;
     case 3:
          bit_Cal(31, 0x70, 0x70);bit_Cal(32, 0xF0, 0x90);
          break;
     case 4:
          bit_Cal(31, 0x70, 0x70);bit_Cal(32, 0xF0, 0x20);
          break;
     case 5:
          bit_Cal(31, 0x70, 0x60);bit_Cal(32, 0xF0, 0xB0);
          break;
     case 6:
          bit_Cal(31, 0x70, 0x60);bit_Cal(32, 0xF0, 0xF0);
          break;
     case 7:
          bit_Cal(31, 0x70, 0x50);bit_Cal(32, 0xF0, 0x10);
          break;
     case 8:
          bit_Cal(31, 0x70, 0x70);bit_Cal(32, 0xF0, 0xF0);
          break;
     case 9:
          bit_Cal(31, 0x70, 0x70);bit_Cal(32, 0xF0, 0xB0);
          break;
     default:
          break;
     }

     /**********工位1的实际转速显示**********/
     if (work_num[0].Speed.Display_Rel > 999) // 大于999时
     {
        Val = work_num[0].Speed.Display_Rel / 1000 % 10;
        switch (Val)
        {
        case 0:
               bit_Cal(61, 0x7F, 0x77);
            break;
        case 1:
               bit_Cal(61, 0x7F, 0x24);
            break;
        case 2:
               bit_Cal(61, 0x7F, 0x5D);
            break;
        case 3:
               bit_Cal(61, 0x7F, 0x6D);
            break;
        case 4:
               bit_Cal(61, 0x7F, 0x2E);
            break;
        case 5:
               bit_Cal(61, 0x7F, 0x6B);
            break;
        case 6:
               bit_Cal(61, 0x7F, 0x7B);
            break;
        case 7:
               bit_Cal(61, 0x7F, 0x25);
            break;
        case 8:
               bit_Cal(61, 0x7F, 0x7F);
            break;
        case 9:
               bit_Cal(61, 0x7F, 0x6F);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(61, 0x7F, 0x77);
    }
    
   if (work_num[0].Speed.Display_Rel > 99) // 大于99时
   {
       Val = work_num[0].Speed.Display_Rel / 100 % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(59, 0x0E, 0x0A);bit_Cal(60, 0x0F, 0x0F);
            break;
        case 1:
               bit_Cal(59, 0x0E, 0x0A);bit_Cal(60, 0x0F, 0x00);
            break;
        case 2:
               bit_Cal(59, 0x0E, 0x06);bit_Cal(60, 0x0F, 0x0D);
            break;
        case 3:
               bit_Cal(59, 0x0E, 0x0E);bit_Cal(60, 0x0F, 0x09);
            break;
        case 4:
               bit_Cal(59, 0x0E, 0x0E);bit_Cal(60, 0x0F, 0x02);
            break;
        case 5:
               bit_Cal(59, 0x0E, 0x0C);bit_Cal(60, 0x0F, 0x0B);
            break;
        case 6:
               bit_Cal(59, 0x0E, 0x0C);bit_Cal(60, 0x0F, 0x0F);
            break;
        case 7:
               bit_Cal(59, 0x0E, 0x0A);bit_Cal(60, 0x0F, 0x01);
            break;
        case 8:
               bit_Cal(59, 0x0E, 0x0E);bit_Cal(60, 0x0F, 0x0F);
            break;
        case 9:
               bit_Cal(59, 0x0E, 0x0E);bit_Cal(60, 0x0F, 0x0B);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(59, 0x0E, 0x0A);bit_Cal(60, 0x0F, 0x0F);
    }

   if (work_num[0].Speed.Display_Rel > 9) // 大于9时
   {
       Val = work_num[0].Speed.Display_Rel / 10 % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(57, 0x0E, 0x0A);bit_Cal(58, 0x0F, 0x0F);
            break;
        case 1:
               bit_Cal(57, 0x0E, 0x0A);bit_Cal(58, 0x0F, 0x00);
            break;
        case 2:
               bit_Cal(57, 0x0E, 0x06);bit_Cal(58, 0x0F, 0x0D);
            break;
        case 3:
               bit_Cal(57, 0x0E, 0x0E);bit_Cal(58, 0x0F, 0x09);
            break;
        case 4:
               bit_Cal(57, 0x0E, 0x0E);bit_Cal(58, 0x0F, 0x02);
            break;
        case 5:
               bit_Cal(57, 0x0E, 0x0C);bit_Cal(58, 0x0F, 0x0B);
            break;
        case 6:
               bit_Cal(57, 0x0E, 0x0C);bit_Cal(58, 0x0F, 0x0F);
            break;
        case 7:
               bit_Cal(57, 0x0E, 0x0A);bit_Cal(58, 0x0F, 0x01);
            break;
        case 8:
               bit_Cal(57, 0x0E, 0x0E);bit_Cal(58, 0x0F, 0x0F);
            break;
        case 9:
               bit_Cal(57, 0x0E, 0x0E);bit_Cal(58, 0x0F, 0x0B);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(57, 0x0E, 0x0A);bit_Cal(58, 0x0F, 0x0F);
    }
   
   if (work_num[0].Speed.Display_Rel>= 0) // 大于等于0时
   {
       Val = work_num[0].Speed.Display_Rel % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(55, 0x0E, 0x0A);bit_Cal(56, 0x0F, 0x0F);
            break;
        case 1:
               bit_Cal(55, 0x0E, 0x0A);bit_Cal(56, 0x0F, 0x00);
            break;
        case 2:
               bit_Cal(55, 0x0E, 0x06);bit_Cal(56, 0x0F, 0x0D);
            break;
        case 3:
               bit_Cal(55, 0x0E, 0x0E);bit_Cal(56, 0x0F, 0x09);
            break;
        case 4:
               bit_Cal(55, 0x0E, 0x0E);bit_Cal(56, 0x0F, 0x02);
            break;
        case 5:
               bit_Cal(55, 0x0E, 0x0C);bit_Cal(56, 0x0F, 0x0B);
            break;
        case 6:
               bit_Cal(55, 0x0E, 0x0C);bit_Cal(56, 0x0F, 0x0F);
            break;
        case 7:
               bit_Cal(55, 0x0E, 0x0A);bit_Cal(56, 0x0F, 0x01);
            break;
        case 8:
               bit_Cal(55, 0x0E, 0x0E);bit_Cal(56, 0x0F, 0x0F);
            break;
        case 9:
               bit_Cal(55, 0x0E, 0x0E);bit_Cal(56, 0x0F, 0x0B);
            break;
        default:
           break;
        }
    }
    /**********工位2的设定转速显示**********/
     if (work_num[0].Speed.Display_Set > 999) // 大于999时
     {
        Val = work_num[0].Speed.Display_Set / 1000 % 10;
        switch (Val)
        {
        case 0:
               bit_Cal(53, 0x0E, 0x0A);bit_Cal(54, 0x0F, 0x0F);
            break;
        case 1:
               bit_Cal(53, 0x0E, 0x0A);bit_Cal(54, 0x0F, 0x00);
            break;
        case 2:
               bit_Cal(53, 0x0E, 0x06);bit_Cal(54, 0x0F, 0x0D);
            break;
        case 3:
               bit_Cal(53, 0x0E, 0x0E);bit_Cal(54, 0x0F, 0x09);
            break;
        case 4:
               bit_Cal(53, 0x0E, 0x0E);bit_Cal(54, 0x0F, 0x02);
            break;
        case 5:
               bit_Cal(53, 0x0E, 0x0C);bit_Cal(54, 0x0F, 0x0B);
            break;
        case 6:
               bit_Cal(53, 0x0E, 0x0C);bit_Cal(54, 0x0F, 0x0F);
            break;
        case 7:
               bit_Cal(53, 0x0E, 0x0A);bit_Cal(54, 0x0F, 0x01);
            break;
        case 8:
               bit_Cal(53, 0x0E, 0x0E);bit_Cal(54, 0x0F, 0x0F);
            break;
        case 9:
               bit_Cal(53, 0x0E, 0x0E);bit_Cal(54, 0x0F, 0x0B);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(53, 0x0E, 0x0A);bit_Cal(54, 0x0F, 0x0F);
    }
    
   if (work_num[0].Speed.Display_Set > 99) // 大于99时
   {
       Val = work_num[0].Speed.Display_Set / 100 % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(51, 0x0E, 0x0A);bit_Cal(52, 0x0F, 0x0F);
            break;
        case 1:
               bit_Cal(51, 0x0E, 0x0A);bit_Cal(52, 0x0F, 0x00);
            break;
        case 2:
               bit_Cal(51, 0x0E, 0x06);bit_Cal(52, 0x0F, 0x0D);
            break;
        case 3:
               bit_Cal(51, 0x0E, 0x0E);bit_Cal(52, 0x0F, 0x09);
            break;
        case 4:
               bit_Cal(51, 0x0E, 0x0E);bit_Cal(52, 0x0F, 0x02);
            break;
        case 5:
               bit_Cal(51, 0x0E, 0x0C);bit_Cal(52, 0x0F, 0x0B);
            break;
        case 6:
               bit_Cal(51, 0x0E, 0x0C);bit_Cal(52, 0x0F, 0x0F);
            break;
        case 7:
               bit_Cal(51, 0x0E, 0x0A);bit_Cal(52, 0x0F, 0x01);
            break;
        case 8:
               bit_Cal(51, 0x0E, 0x0E);bit_Cal(52, 0x0F, 0x0F);
            break;
        case 9:
               bit_Cal(51, 0x0E, 0x0E);bit_Cal(52, 0x0F, 0x0B);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(51, 0x0E, 0x0A);bit_Cal(52, 0x0F, 0x0F);
    }

   if (work_num[0].Speed.Display_Set > 9) // 大于9时
   {
       Val = work_num[0].Speed.Display_Set / 10 % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(49, 0x0E, 0x0A);bit_Cal(50, 0x0F, 0x0F);
            break;
        case 1:
               bit_Cal(49, 0x0E, 0x0A);bit_Cal(50, 0x0F, 0x00);
            break;
        case 2:
               bit_Cal(49, 0x0E, 0x06);bit_Cal(50, 0x0F, 0x0D);
            break;
        case 3:
               bit_Cal(49, 0x0E, 0x0E);bit_Cal(50, 0x0F, 0x09);
            break;
        case 4:
               bit_Cal(49, 0x0E, 0x0E);bit_Cal(50, 0x0F, 0x02);
            break;
        case 5:
               bit_Cal(49, 0x0E, 0x0C);bit_Cal(50, 0x0F, 0x0B);
            break;
        case 6:
               bit_Cal(49, 0x0E, 0x0C);bit_Cal(50, 0x0F, 0x0F);
            break;
        case 7:
               bit_Cal(49, 0x0E, 0x0A);bit_Cal(50, 0x0F, 0x01);
            break;
        case 8:
               bit_Cal(49, 0x0E, 0x0E);bit_Cal(50, 0x0F, 0x0F);
            break;
        case 9:
               bit_Cal(49, 0x0E, 0x0E);bit_Cal(50, 0x0F, 0x0B);
            break;
        default:
           break;
        }
    }
    else
    {
        bit_Cal(49, 0x0E, 0x0A);bit_Cal(50, 0x0F, 0x0F);
    }
   
   if (work_num[0].Speed.Display_Set>= 0) // 大于等于0时
   {
       Val = work_num[0].Speed.Display_Set % 10;
       switch (Val)
        {
        case 0:
               bit_Cal(47, 0x0E, 0x0A);bit_Cal(48, 0x0F, 0x0F);
            break;
        case 1:
               bit_Cal(47, 0x0E, 0x0A);bit_Cal(48, 0x0F, 0x00);
            break;
        case 2:
               bit_Cal(47, 0x0E, 0x06);bit_Cal(48, 0x0F, 0x0D);
            break;
        case 3:
               bit_Cal(47, 0x0E, 0x0E);bit_Cal(48, 0x0F, 0x09);
            break;
        case 4:
               bit_Cal(47, 0x0E, 0x0E);bit_Cal(48, 0x0F, 0x02);
            break;
        case 5:
               bit_Cal(47, 0x0E, 0x0C);bit_Cal(48, 0x0F, 0x0B);
            break;
        case 6:
               bit_Cal(47, 0x0E, 0x0C);bit_Cal(48, 0x0F, 0x0F);
            break;
        case 7:
               bit_Cal(47, 0x0E, 0x0A);bit_Cal(48, 0x0F, 0x01);
            break;
        case 8:
               bit_Cal(47, 0x0E, 0x0E);bit_Cal(48, 0x0F, 0x0F);
            break;
        case 9:
               bit_Cal(47, 0x0E, 0x0E);bit_Cal(48, 0x0F, 0x0B);
            break;
        default:
           break;
        }
     }

     /**********工位2的实际时间显示**********/
     Val = work_num[0].Time.Display_Rel / 3600 / 10;//计算十位为单位的小时数
     switch (Val)
     {
     case 0:
          bit_Cal(53, 0x81, 0x81);bit_Cal(55, 0x81, 0x80);bit_Cal(57, 0x81, 0x81);bit_Cal(59, 0x01, 0x01);
          break;
     case 1:
          bit_Cal(53, 0x81, 0x00);bit_Cal(55, 0x81, 0x00);bit_Cal(57, 0x81, 0x81);bit_Cal(59, 0x01, 0x00);
          break;
     case 2:
          bit_Cal(53, 0x81, 0x80);bit_Cal(55, 0x81, 0x81);bit_Cal(57, 0x81, 0x01);bit_Cal(59, 0x01, 0x01);
          break;
     case 3:
          bit_Cal(53, 0x81, 0x00);bit_Cal(55, 0x81, 0x81);bit_Cal(57, 0x81, 0x81);bit_Cal(59, 0x01, 0x01);
          break;
     case 4:
          bit_Cal(53, 0x81, 0x01);bit_Cal(55, 0x81, 0x01);bit_Cal(57, 0x81, 0x81);bit_Cal(59, 0x01, 0x00);
          break;
     case 5:
          bit_Cal(53, 0x81, 0x01);bit_Cal(55, 0x81, 0x81);bit_Cal(57, 0x81, 0x80);bit_Cal(59, 0x01, 0x01);
          break;
     case 6:
          bit_Cal(53, 0x81, 0x81);bit_Cal(55, 0x81, 0x81);bit_Cal(57, 0x81, 0x80);bit_Cal(59, 0x01, 0x01);
          break;
     case 7:
          bit_Cal(53, 0x81, 0x00);bit_Cal(55, 0x81, 0x00);bit_Cal(57, 0x81, 0x81);bit_Cal(59, 0x01, 0x01);
          break;
     case 8:
          bit_Cal(53, 0x81, 0x81);bit_Cal(55, 0x81, 0x80);bit_Cal(57, 0x81, 0x81);bit_Cal(59, 0x01, 0x01);
          break;
     case 9:
          bit_Cal(53, 0x81, 0x01);bit_Cal(55, 0x81, 0x81);bit_Cal(57, 0x81, 0x81);bit_Cal(59, 0x01, 0x01);
          break;
     default:
          break;
     }

     Val = work_num[0].Time.Display_Rel / 3600 % 10;// 计算个位为单位的小时数
     switch (Val)
     {
     case 0:
          bit_Cal(59, 0x70, 0x50);bit_Cal(60, 0xF0, 0xF0);
          break;
     case 1:
          bit_Cal(59, 0x70, 0x50);bit_Cal(60, 0xF0, 0x00);
          break;
     case 2:
          bit_Cal(59, 0x70, 0x30);bit_Cal(60, 0xF0, 0xD0);
          break;
     case 3:
          bit_Cal(59, 0x70, 0x70);bit_Cal(60, 0xF0, 0x90);
          break;
     case 4:
          bit_Cal(59, 0x70, 0x70);bit_Cal(60, 0xF0, 0x20);
          break;
     case 5:
          bit_Cal(59, 0x70, 0x60);bit_Cal(60, 0xF0, 0xB0);
          break;
     case 6:
          bit_Cal(59, 0x70, 0x60);bit_Cal(60, 0xF0, 0xF0);
          break;
     case 7:
          bit_Cal(59, 0x70, 0x50);bit_Cal(60, 0xF0, 0x10);
          break;
     case 8:
          bit_Cal(59, 0x70, 0x70);bit_Cal(60, 0xF0, 0xF0);
          break;
     case 9:
          bit_Cal(59, 0x70, 0x70);bit_Cal(60, 0xF0, 0xB0);
          break;
     default:
          break;
     }

     Val = work_num[0].Time.Display_Rel % 3600 / 60 / 10; // 计算十分位为单位的分钟数
     switch (Val)
     {
     case 0:
          bit_Cal(57, 0x70, 0x50);bit_Cal(58, 0xF0, 0xF0);
          break;
     case 1:
          bit_Cal(57, 0x70, 0x50);bit_Cal(58, 0xF0, 0x00);
          break;
     case 2:
          bit_Cal(57, 0x70, 0x30);bit_Cal(58, 0xF0, 0xD0);
          break;
     case 3:
          bit_Cal(57, 0x70, 0x70);bit_Cal(58, 0xF0, 0x90);
          break;
     case 4:
          bit_Cal(57, 0x70, 0x70);bit_Cal(58, 0xF0, 0x20);
          break;
     case 5:
          bit_Cal(57, 0x70, 0x60);bit_Cal(58, 0xF0, 0xB0);
          break;
     case 6:
          bit_Cal(57, 0x70, 0x60);bit_Cal(58, 0xF0, 0xF0);
          break;
     case 7:
          bit_Cal(57, 0x70, 0x50);bit_Cal(58, 0xF0, 0x10);
          break;
     case 8:
          bit_Cal(57, 0x70, 0x70);bit_Cal(58, 0xF0, 0xF0);
          break;
     case 9:
          bit_Cal(57, 0x70, 0x70);bit_Cal(58, 0xF0, 0xB0);
          break;
     default:
          break;
     }

     Val = work_num[0].Time.Display_Rel % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
     switch (Val)
     {
     case 0:
          bit_Cal(55, 0x70, 0x50);bit_Cal(56, 0xF0, 0xF0);
          break;
     case 1:
          bit_Cal(55, 0x70, 0x50);bit_Cal(56, 0xF0, 0x00);
          break;
     case 2:
          bit_Cal(55, 0x70, 0x30);bit_Cal(56, 0xF0, 0xD0);
          break;
     case 3:
          bit_Cal(55, 0x70, 0x70);bit_Cal(56, 0xF0, 0x90);
          break;
     case 4:
          bit_Cal(55, 0x70, 0x70);bit_Cal(56, 0xF0, 0x20);
          break;
     case 5:
          bit_Cal(55, 0x70, 0x60);bit_Cal(56, 0xF0, 0xB0);
          break;
     case 6:
          bit_Cal(55, 0x70, 0x60);bit_Cal(56, 0xF0, 0xF0);
          break;
     case 7:
          bit_Cal(55, 0x70, 0x50);bit_Cal(56, 0xF0, 0x10);
          break;
     case 8:
          bit_Cal(55, 0x70, 0x70);bit_Cal(56, 0xF0, 0xF0);
          break;
     case 9:
          bit_Cal(55, 0x70, 0x70);bit_Cal(56, 0xF0, 0xB0);
          break;
     default:
          break;
     }

     /**********工位2的设定时间显示**********/
     Val = work_num[0].Time.Display_Set / 3600 / 10;//计算十位为单位的小时数
     switch (Val)
     {
     case 0:
          bit_Cal(53, 0x70, 0x50);bit_Cal(54, 0xF0, 0xF0);
          break;
     case 1:
          bit_Cal(53, 0x70, 0x50);bit_Cal(54, 0xF0, 0x00);
          break;
     case 2:
          bit_Cal(53, 0x70, 0x30);bit_Cal(54, 0xF0, 0xD0);
          break;
     case 3:
          bit_Cal(53, 0x70, 0x70);bit_Cal(54, 0xF0, 0x90);
          break;
     case 4:
          bit_Cal(53, 0x70, 0x70);bit_Cal(54, 0xF0, 0x20);
          break;
     case 5:
          bit_Cal(53, 0x70, 0x60);bit_Cal(54, 0xF0, 0xB0);
          break;
     case 6:
          bit_Cal(53, 0x70, 0x60);bit_Cal(54, 0xF0, 0xF0);
          break;
     case 7:
          bit_Cal(53, 0x70, 0x50);bit_Cal(54, 0xF0, 0x10);
          break;
     case 8:
          bit_Cal(53, 0x70, 0x70);bit_Cal(54, 0xF0, 0xF0);
          break;
     case 9:
          bit_Cal(53, 0x70, 0x70);bit_Cal(54, 0xF0, 0xB0);
          break;
     default:
          break;
     }

     Val = work_num[0].Time.Display_Set / 3600 % 10;// 计算个位为单位的小时数
     switch (Val)
     {
     case 0:
          bit_Cal(51, 0x70, 0x50);bit_Cal(52, 0xF0, 0xF0);
          break;
     case 1:
          bit_Cal(51, 0x70, 0x50);bit_Cal(52, 0xF0, 0x00);
          break;
     case 2:
          bit_Cal(51, 0x70, 0x30);bit_Cal(52, 0xF0, 0xD0);
          break;
     case 3:
          bit_Cal(51, 0x70, 0x70);bit_Cal(52, 0xF0, 0x90);
          break;
     case 4:
          bit_Cal(51, 0x70, 0x70);bit_Cal(52, 0xF0, 0x20);
          break;
     case 5:
          bit_Cal(51, 0x70, 0x60);bit_Cal(52, 0xF0, 0xB0);
          break;
     case 6:
          bit_Cal(51, 0x70, 0x60);bit_Cal(52, 0xF0, 0xF0);
          break;
     case 7:
          bit_Cal(51, 0x70, 0x50);bit_Cal(52, 0xF0, 0x10);
          break;
     case 8:
          bit_Cal(51, 0x70, 0x70);bit_Cal(52, 0xF0, 0xF0);
          break;
     case 9:
          bit_Cal(51, 0x70, 0x70);bit_Cal(52, 0xF0, 0xB0);
          break;
     default:
          break;
     }

     Val = work_num[0].Time.Display_Set % 3600 / 60 / 10; // 计算十分位为单位的分钟数
     switch (Val)
     {
     case 0:
          bit_Cal(49, 0x70, 0x50);bit_Cal(50, 0xF0, 0xF0);
          break;
     case 1:
          bit_Cal(49, 0x70, 0x50);bit_Cal(50, 0xF0, 0x00);
          break;
     case 2:
          bit_Cal(49, 0x70, 0x30);bit_Cal(50, 0xF0, 0xD0);
          break;
     case 3:
          bit_Cal(49, 0x70, 0x70);bit_Cal(50, 0xF0, 0x90);
          break;
     case 4:
          bit_Cal(49, 0x70, 0x70);bit_Cal(50, 0xF0, 0x20);
          break;
     case 5:
          bit_Cal(49, 0x70, 0x60);bit_Cal(50, 0xF0, 0xB0);
          break;
     case 6:
          bit_Cal(49, 0x70, 0x60);bit_Cal(50, 0xF0, 0xF0);
          break;
     case 7:
          bit_Cal(49, 0x70, 0x50);bit_Cal(50, 0xF0, 0x10);
          break;
     case 8:
          bit_Cal(49, 0x70, 0x70);bit_Cal(50, 0xF0, 0xF0);
          break;
     case 9:
          bit_Cal(49, 0x70, 0x70);bit_Cal(50, 0xF0, 0xB0);
          break;
     default:
          break;
     }

     Val = work_num[0].Time.Display_Set % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
     switch (Val)
     {
     case 0:
          bit_Cal(47, 0x70, 0x50);bit_Cal(48, 0xF0, 0xF0);
          break;
     case 1:
          bit_Cal(47, 0x70, 0x50);bit_Cal(48, 0xF0, 0x00);
          break;
     case 2:
          bit_Cal(47, 0x70, 0x30);bit_Cal(48, 0xF0, 0xD0);
          break;
     case 3:
          bit_Cal(47, 0x70, 0x70);bit_Cal(48, 0xF0, 0x90);
          break;
     case 4:
          bit_Cal(47, 0x70, 0x70);bit_Cal(48, 0xF0, 0x20);
          break;
     case 5:
          bit_Cal(47, 0x70, 0x60);bit_Cal(48, 0xF0, 0xB0);
          break;
     case 6:
          bit_Cal(47, 0x70, 0x60);bit_Cal(48, 0xF0, 0xF0);
          break;
     case 7:
          bit_Cal(47, 0x70, 0x50);bit_Cal(48, 0xF0, 0x10);
          break;
     case 8:
          bit_Cal(47, 0x70, 0x70);bit_Cal(48, 0xF0, 0xF0);
          break;
     case 9:
          bit_Cal(47, 0x70, 0x70);bit_Cal(48, 0xF0, 0xB0);
          break;
     default:
          break;
     }

     /**********工位2'RPM'显示**********/
     bit_Cal(31, 0x01, 0x01);

     /**********工位2'min'显示**********/
     bit_Cal(31, 0x80, 0x80);

     /**********工位2设定时间'：'显示**********/
     bit_Cal(35, 0x80, 0x80);

     /**********时间图标显示**********/
     bit_Cal(41, 0x80, 0x80);

     /**********工位2转速图标S28显示**********/
     bit_Cal(43, 0x01, 0x01);

     /**********工位2转速图标S30显示**********/
     bit_Cal(45, 0x01, 0x01);

     /**********工位2转速图标S29显示**********/
     bit_Cal(45, 0x80, 0x80);

     /**********工位2实际时间'：'显示**********/
     bit_Cal(43, 0x80, 0x80);


     /**********工位1'RPM'显示**********/
     bit_Cal(47, 0x01, 0x01);

     /**********工位1'min'显示**********/
     bit_Cal(47, 0x80, 0x80);

     /**********工位1设定时间'：'显示**********/
     bit_Cal(51, 0x80, 0x80);

     /**********时间图标显示**********/
     bit_Cal(51, 0x01, 0x01);

     /**********工位1转速图标S1显示**********/
     bit_Cal(49, 0x01, 0x01);

     /**********工位1转速图标S2显示**********/
     bit_Cal(61, 0x80, 0x80);

     /**********工位1转速图标3显示**********/
     bit_Cal(49, 0x80, 0x80);

     /**********工位1实际时间'：'显示**********/
     bit_Cal(59, 0x80, 0x80);


     /**********上面竖线显示**********/
     bit_Cal(41, 0x01, 0x01);

     /**********数据发送**********/
     for(uint8_t i=0;i<31;i++)
     {
          Write_Addr_Dat_N(IC1, i*2, seg[i], 1);
     }
     for(uint8_t i=0;i<31;i++)
     {
          Write_Addr_Dat_N(IC2, i*2, seg[i+31], 1);
     }
}

/**
 * @brief 显示屏幕内容
 *
 */
void Show_Display(void)
{
     Work_Num[3].Speed.Display_Rel = sys.val;
     Work_Num[3].Speed.Display_Set = sys.val;
     Work_Num[3].Time.Display_Rel = sys.val1;
     Work_Num[3].Time.Display_Set = sys.val1;
     Work_Num[2].Speed.Display_Rel = sys.val;
     Work_Num[2].Speed.Display_Set = sys.val;
     Work_Num[2].Time.Display_Rel = sys.val1;
     Work_Num[2].Time.Display_Set = sys.val1;
     Work_Num[1].Speed.Display_Rel = sys.val;
     Work_Num[1].Speed.Display_Set = sys.val;
     Work_Num[1].Time.Display_Rel = sys.val1;
     Work_Num[1].Time.Display_Set = sys.val1;
      Work_Num[0].Speed.Display_Rel = sys.val;
     Work_Num[0].Speed.Display_Set = sys.val;
     Work_Num[0].Time.Display_Rel = sys.val1;
     Work_Num[0].Time.Display_Set = sys.val1;
     Display_IC(Work_Num);
}
