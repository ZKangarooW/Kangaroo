#include "Show.h"

/**********全局变量**********/
float Twinkle_Time; // 闪烁时间

/**********局部变量声明*******/
uint8_t Speed_ShowFlag, Time_ShowFlag, Sync_ShowFlag;//速度、温度、时间显示的标志位，0：常亮，1：熄灭

/*
*****************************************************************
 * 函数原型：static void Icn_Twinkle(float dT)
 * 功    能：图标闪烁
 * 调    用：内部调用
*****************************************************************
*/
static void Icn_Twinkle(float dT)
{
	static float T[4];
    for(uint8_t i = 0;i<4;i++)
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
            else if(sys.SetMode_Option == 2)//设置时间
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

/**
 * @brief 闪烁函数
 *
 * @param dT 任务周期
 */
void Twinkle(float dT)
{
    Icn_Twinkle(dT);
    Check_ShowFlag(dT);
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
    if(Speed_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 3)//不显示设定转速
    {
        bit_Cal(6, 0x70, 0x00);bit_Cal(7, 0xF0, 0x00);//第一位不显示
        bit_Cal(4, 0x70, 0x00);bit_Cal(5, 0xF0, 0x00);//第二位不显示
        bit_Cal(2, 0x70, 0x00);bit_Cal(3, 0xF0, 0x00);//第三位不显示
        bit_Cal(0, 0x70, 0x00);bit_Cal(1, 0xF0, 0x00);//第四位不显示
    }
    else
    {
        if(work_num[3].Speed.Display_Set == 0)//显示“ -- ”
        {
            bit_Cal(6, 0x70, 0x20);bit_Cal(7, 0xF0, 0x00);//显示“-”
            bit_Cal(4, 0x70, 0x20);bit_Cal(5, 0xF0, 0x00);//显示“-”
            bit_Cal(2, 0x70, 0x20);bit_Cal(3, 0xF0, 0x00);//显示“-”
            bit_Cal(0, 0x70, 0x20);bit_Cal(1, 0xF0, 0x00);//显示“-”
        }
        else
        {
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
        }
    }

     /**********工位4的实际时间显示**********/
    if(work_num[3].Time.Rel == 0)
    {
        bit_Cal(14, 0x0E, 0x04);bit_Cal(15, 0x0F, 0x00);//显示“-”
        bit_Cal(12, 0x0E, 0x04);bit_Cal(13, 0x0F, 0x00);//显示“-”
        bit_Cal(10, 0x0E, 0x04);bit_Cal(11, 0x0F, 0x00);//显示“-”
        bit_Cal(8, 0x0E, 0x04);bit_Cal(9, 0x0F, 0x00);//显示“-”
    }
    else
    {
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
    }

     /**********工位4的设定时间显示**********/
    if(Time_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 3)//不显示设定转速
    {
        bit_Cal(6, 0x0E, 0x00);bit_Cal(7, 0x0F, 0x00);//第一位不显示
        bit_Cal(4, 0x0E, 0x00);bit_Cal(5, 0x0F, 0x00);//第二位不显示
        bit_Cal(2, 0x0E, 0x00);bit_Cal(3, 0x0F, 0x00);//第三位不显示
        bit_Cal(0, 0x0E, 0x00);bit_Cal(1, 0x0F, 0x00);//第四位不显示
    }
    else
    {
        if(work_num[3].Time.Set == 0)
        {
            bit_Cal(6, 0x0E, 0x04);bit_Cal(7, 0x0F, 0x00);//显示“-”
            bit_Cal(4, 0x0E, 0x04);bit_Cal(5, 0x0F, 0x00);//显示“-”
            bit_Cal(2, 0x0E, 0x04);bit_Cal(3, 0x0F, 0x00);//显示“-”
            bit_Cal(0, 0x0E, 0x04);bit_Cal(1, 0x0F, 0x00);//显示“-”
        }
        else
        {
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
         }
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
    if(Speed_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 2)//不显示设定转速
    {
        bit_Cal(29, 0x70, 0x00);bit_Cal(21, 0xF0, 0x00);//第一位不显示
        bit_Cal(19, 0x70, 0x00);bit_Cal(20, 0xF0, 0x00);//第二位不显示
        bit_Cal(30, 0x70, 0x00);bit_Cal(18, 0xF0, 0x00);//第三位不显示
        bit_Cal(16, 0x70, 0x00);bit_Cal(17, 0xF0, 0x00);//第四位不显示
    }
    else
    {
        if(work_num[2].Speed.Display_Set == 0)//显示“ -- ”
        {
            bit_Cal(29, 0x70, 0x20);bit_Cal(21, 0xF0, 0x00);//显示“-”
            bit_Cal(19, 0x70, 0x20);bit_Cal(20, 0xF0, 0x00);//显示“-”
            bit_Cal(30, 0x70, 0x20);bit_Cal(18, 0xF0, 0x00);//显示“-”
            bit_Cal(16, 0x70, 0x20);bit_Cal(17, 0xF0, 0x00);//显示“-”
        }
        else
        {
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
        }
    }

    /**********工位3的实际时间显示**********/
    if(work_num[2].Time.Rel == 0)
    {
        bit_Cal(27, 0x7F, 0x08);//显示“-”
        bit_Cal(28, 0x0E, 0x04);bit_Cal(26, 0x0F, 0x00);//显示“-”
        bit_Cal(24, 0x0E, 0x04);bit_Cal(25, 0x0F, 0x00);//显示“-”
        bit_Cal(22, 0x0E, 0x04);bit_Cal(23, 0x0F, 0x00);//显示“-”
    }
    else
    {
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
    }

     /**********工位3的设定时间显示**********/
    if(Time_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 2)//不显示设定转速
    {
        bit_Cal(29, 0x0E, 0x00);bit_Cal(21, 0x0F, 0x00);//第一位不显示
        bit_Cal(19, 0x0E, 0x00);bit_Cal(20, 0x0F, 0x00);//第二位不显示
        bit_Cal(30, 0x0E, 0x00);bit_Cal(18, 0x0F, 0x00);//第三位不显示
        bit_Cal(16, 0x0E, 0x00);bit_Cal(17, 0x0F, 0x00);//第四位不显示
    }
    else
    {
        if(work_num[2].Time.Set == 0)
        {
            bit_Cal(29, 0x0E, 0x04);bit_Cal(21, 0x0F, 0x00);//显示“-”
            bit_Cal(19, 0x0E, 0x04);bit_Cal(20, 0x0F, 0x00);//显示“-”
            bit_Cal(30, 0x0E, 0x04);bit_Cal(18, 0x0F, 0x00);//显示“-”
            bit_Cal(16, 0x0E, 0x04);bit_Cal(17, 0x0F, 0x00);//显示“-”
        }
        else
        {
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
         }
     }

     /**********工位4'RPM'显示**********/
     bit_Cal(0, 0x80, 0x80);

     /**********工位4'min'显示**********/
     bit_Cal(0, 0x01, 0x01);

     /**********工位4设定时间'：'显示**********/
     bit_Cal(4, 0x01, 0x01);
     
    /* 2号工位4号工位之间横线 */
    if(sys.New_Work == 1 || sys.New_Work == 3)//如果当前工位在2或者4号工位
    {
        /**********右边横杠显示**********/
        bit_Cal(6, 0x80, 0x80);
    }
    else
    {
        bit_Cal(6, 0x80, 0x00);
    }

     /**********中间锁图标显示**********/
    if(Lock_Switch)
        bit_Cal(6, 0x01, 0x01);
    else
        bit_Cal(6, 0x01, 0x00);
     
    /* 4号工位转速图标 */
    switch(Work_Num[3].Speed.IconStep)
	{
		case 0: bit_Cal(10, 0x80, 0x80);
                bit_Cal(8, 0x80, 0x80);
                bit_Cal(8, 0x01, 0x01);
			break;
		case 1: bit_Cal(10, 0x80, 0x00);
                bit_Cal(8, 0x80, 0x80);
                bit_Cal(8, 0x01, 0x01);
			break;
		case 2: bit_Cal(10, 0x80, 0x80);
                bit_Cal(8, 0x80, 0x00);
                bit_Cal(8, 0x01, 0x01);
			break;
		case 3: bit_Cal(10, 0x80, 0x80);
                bit_Cal(8, 0x80, 0x80);
                bit_Cal(8, 0x01, 0x00);
			break;
		default:
			break;
	}
    /* 1号工位3号工位之间横线 */
    if(sys.New_Work == 0 || sys.New_Work == 2)//如果当前工位在1或者3号工位
    {
        /**********左边横杠显示**********/
        bit_Cal(10, 0x01, 0x01);
    }
    else
    {
        bit_Cal(10, 0x01, 0x00);
    }

    /* 3号工位4号工位之间竖线 */
    if(sys.New_Work == 2 || sys.New_Work == 3)//如果当前工位在3或者4号工位
    {
        /**********下面竖线显示**********/
        bit_Cal(12, 0x80, 0x80);
    }
    else
    {
        bit_Cal(12, 0x80, 0x00);
    }

     /**********工位4实际时间'：'显示**********/
     bit_Cal(12, 0x01, 0x01);

    /* 4号工位时间图标 */
    if(Work_Num[3].Time.Icon == 0)
    {
        bit_Cal(14, 0x80, 0x80);
    }
    else
    {
        bit_Cal(14, 0x80, 0x00);
    }

     /**********工位3'RPM'显示**********/
     bit_Cal(16, 0x80, 0x80);

     /**********工位3'min'显示**********/
     bit_Cal(16, 0x01, 0x01); 

    /* 3号工位转速图标 */
    switch(Work_Num[2].Speed.IconStep)
	{
		case 0: bit_Cal(30, 0x80, 0x80);
                bit_Cal(30, 0x01, 0x01);
                bit_Cal(19, 0x80, 0x80);
			break;
		case 1: bit_Cal(30, 0x80, 0x00);
                bit_Cal(30, 0x01, 0x01);
                bit_Cal(19, 0x80, 0x80);
			break;
		case 2: bit_Cal(30, 0x80, 0x80);
                bit_Cal(30, 0x01, 0x00);
                bit_Cal(19, 0x80, 0x80);
			break;
		case 3: bit_Cal(30, 0x80, 0x80);
                bit_Cal(30, 0x01, 0x01);
                bit_Cal(19, 0x80, 0x00);
			break;
		default:
			break;
	}
   
     /**********工位4设定时间'：'显示**********/
     bit_Cal(19, 0x01, 0x01);

    /*3号工位时间图标 */
    if(Work_Num[2].Time.Icon == 0)
    {
        bit_Cal(27, 0x80, 0x80);
    }
    else
    {   
        bit_Cal(27, 0x80, 0x00);
    }

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
    if(Speed_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 1)//不显示设定转速
    {
        bit_Cal(37, 0x0E, 0x00);bit_Cal(38, 0x0F, 0x00);//第一位不显示
        bit_Cal(35, 0x0E, 0x00);bit_Cal(36, 0x0F, 0x00);//第二位不显示
        bit_Cal(33, 0x0E, 0x00);bit_Cal(34, 0x0F, 0x00);//第三位不显示
        bit_Cal(31, 0x0E, 0x00);bit_Cal(32, 0x0F, 0x00);//第四位不显示
    }
    else
    {
        if(work_num[1].Speed.Display_Set == 0)//显示“ -- ”
        {
            bit_Cal(37, 0x0E, 0x04);bit_Cal(38, 0x0F, 0x00);//显示“-”
            bit_Cal(35, 0x0E, 0x04);bit_Cal(36, 0x0F, 0x00);//显示“-”
            bit_Cal(33, 0x0E, 0x04);bit_Cal(34, 0x0F, 0x00);//显示“-”
            bit_Cal(31, 0x0E, 0x04);bit_Cal(32, 0x0F, 0x00);//显示“-”
        }
        else
        {
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
         }
     }

     /**********工位2的实际时间显示**********/
    if(work_num[1].Time.Rel == 0)
    {
        bit_Cal(45, 0x70, 0x20);bit_Cal(46, 0xF0, 0x00);//显示“-”
        bit_Cal(43, 0x70, 0x20);bit_Cal(44, 0xF0, 0x00);//显示“-”
        bit_Cal(41, 0x70, 0x20);bit_Cal(42, 0xF0, 0x00);//显示“-”
        bit_Cal(39, 0x70, 0x20);bit_Cal(40, 0xF0, 0x00);//显示“-”
    }
    else
    {
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
    }

     /**********工位2的设定时间显示**********/
    if(Time_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 1)//不显示设定转速
    {
        bit_Cal(37, 0x70, 0x00);bit_Cal(38, 0xF0, 0x00);//第一位不显示
        bit_Cal(35, 0x70, 0x00);bit_Cal(36, 0xF0, 0x00);//第二位不显示
        bit_Cal(33, 0x70, 0x00);bit_Cal(34, 0xF0, 0x00);//第三位不显示
        bit_Cal(31, 0x70, 0x00);bit_Cal(32, 0xF0, 0x00);//第四位不显示
    }
    else
    {
        if(work_num[1].Time.Set == 0)
        {
            bit_Cal(37, 0x70, 0x20);bit_Cal(38, 0xF0, 0x00);//显示“-”
            bit_Cal(35, 0x70, 0x20);bit_Cal(36, 0xF0, 0x00);//显示“-”
            bit_Cal(33, 0x70, 0x20);bit_Cal(34, 0xF0, 0x00);//显示“-”
            bit_Cal(31, 0x70, 0x20);bit_Cal(32, 0xF0, 0x00);//显示“-”
        }
        else
        {
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
        }
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
    if(Speed_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 0)//不显示设定转速
    {
        bit_Cal(53, 0x0E, 0x00);bit_Cal(54, 0x0F, 0x00);//第一位不显示
        bit_Cal(51, 0x0E, 0x00);bit_Cal(52, 0x0F, 0x00);//第二位不显示
        bit_Cal(49, 0x0E, 0x00);bit_Cal(50, 0x0F, 0x00);//第三位不显示
        bit_Cal(47, 0x0E, 0x00);bit_Cal(48, 0x0F, 0x00);//第四位不显示
    }
    else
    {
        if(work_num[0].Speed.Display_Set == 0)//显示“ -- ”
        {
            bit_Cal(53, 0x0E, 0x04);bit_Cal(54, 0x0F, 0x00);//显示“-”
            bit_Cal(51, 0x0E, 0x04);bit_Cal(52, 0x0F, 0x00);//显示“-”
            bit_Cal(49, 0x0E, 0x04);bit_Cal(50, 0x0F, 0x00);//显示“-”
            bit_Cal(47, 0x0E, 0x04);bit_Cal(48, 0x0F, 0x00);//显示“-”
        }
        else
        {
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
         }
     }

     /**********工位2的实际时间显示**********/
    if(work_num[0].Time.Rel == 0)
    {
        bit_Cal(53, 0x81, 0x00);bit_Cal(55, 0x81, 0x01);bit_Cal(57, 0x81, 0x00);bit_Cal(59, 0x01, 0x00);//显示“-”
        bit_Cal(59, 0x70, 0x20);bit_Cal(60, 0xF0, 0x00);//显示“-”
        bit_Cal(57, 0x70, 0x20);bit_Cal(58, 0xF0, 0x00);//显示“-”
        bit_Cal(55, 0x70, 0x20);bit_Cal(56, 0xF0, 0x00);//显示“-”
    }
    else
    {
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
    }

     /**********工位1的设定时间显示**********/
    if(Time_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 0)//不显示设定转速
    {
        bit_Cal(53, 0x70, 0x00);bit_Cal(54, 0xF0, 0x00);//第一位不显示
        bit_Cal(51, 0x70, 0x00);bit_Cal(52, 0xF0, 0x00);//第二位不显示
        bit_Cal(49, 0x70, 0x00);bit_Cal(50, 0xF0, 0x00);//第三位不显示
        bit_Cal(47, 0x70, 0x00);bit_Cal(48, 0xF0, 0x00);//第四位不显示
    }
    else
    {
        if(work_num[0].Time.Set == 0)
        {
            bit_Cal(53, 0x70, 0x20);bit_Cal(54, 0xF0, 0x00);//显示“-”
            bit_Cal(51, 0x70, 0x20);bit_Cal(52, 0xF0, 0x00);//显示“-”
            bit_Cal(49, 0x70, 0x20);bit_Cal(50, 0xF0, 0x00);//显示“-”
            bit_Cal(47, 0x70, 0x20);bit_Cal(48, 0xF0, 0x00);//显示“-”
        }
        else
        {
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
         }
     }

     /*2号工位时间图标 */
    if(Work_Num[1].Time.Icon == 0)
    {
        bit_Cal(41, 0x80, 0x80);
    }
    else
    {
        bit_Cal(41, 0x80, 0x00);
    }

    /* 2号工位转速图标 */
    switch(Work_Num[1].Speed.IconStep)
	{
		case 0: bit_Cal(43, 0x01, 0x01);
                 bit_Cal(45, 0x01, 0x01);
                 bit_Cal(45, 0x80, 0x80);
			break;
		case 1: bit_Cal(43, 0x01, 0x00);
                 bit_Cal(45, 0x01, 0x01);
                 bit_Cal(45, 0x80, 0x80);
			break;
		case 2: bit_Cal(43, 0x01, 0x01);
                 bit_Cal(45, 0x01, 0x01);
                 bit_Cal(45, 0x80, 0x00);
			break;
		case 3: bit_Cal(43, 0x01, 0x01);
                 bit_Cal(45, 0x01, 0x00);
                 bit_Cal(45, 0x80, 0x80);
			break;
		default:
			break;
	}

     /*1号工位时间图标 */
    if(Work_Num[0].Time.Icon == 0)
    {
        bit_Cal(51, 0x01, 0x01);
    }
    else
    {
        bit_Cal(51, 0x01, 0x00);
    }

    /* 1号工位转速图标 */
    switch(Work_Num[0].Speed.IconStep)
	{
		case 0: bit_Cal(49, 0x01, 0x01);
                 bit_Cal(61, 0x80, 0x80);
                 bit_Cal(49, 0x80, 0x80);
			break;
		case 1: bit_Cal(49, 0x01, 0x00);
                 bit_Cal(61, 0x80, 0x80);
                 bit_Cal(49, 0x80, 0x80);
			break;
		case 2: bit_Cal(49, 0x01, 0x01);
                 bit_Cal(61, 0x80, 0x00);
                 bit_Cal(49, 0x80, 0x80);
			break;
		case 3: bit_Cal(49, 0x01, 0x01);
                 bit_Cal(61, 0x80, 0x80);
                 bit_Cal(49, 0x80, 0x00);
			break;
		default:
			break;
	}
    
    /* 1号工位2号工位之间竖线 */
    if(sys.New_Work == 0 || sys.New_Work == 1)//如果当前工位在1或者2号工位
    {
        /**********上面竖线显示**********/
        bit_Cal(41, 0x01, 0x01);
    }
    else
    {
        bit_Cal(41, 0x01, 0x00);
    }
    
     /**********工位2'RPM'显示**********/
     bit_Cal(31, 0x01, 0x01);

     /**********工位2'min'显示**********/
     bit_Cal(31, 0x80, 0x80);

     /**********工位2设定时间'：'显示**********/
     bit_Cal(35, 0x80, 0x80);
    
     /**********工位2实际时间'：'显示**********/
     bit_Cal(43, 0x80, 0x80);

     /**********工位1'RPM'显示**********/
     bit_Cal(47, 0x01, 0x01);

     /**********工位1'min'显示**********/
     bit_Cal(47, 0x80, 0x80);

     /**********工位1设定时间'：'显示**********/
     bit_Cal(51, 0x80, 0x80);
     
     /**********工位1实际时间'：'显示**********/
     bit_Cal(59, 0x80, 0x80);

     

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
    for(uint8_t i = 0;i<4;i++)
    {
        Work_Num[i].Speed.Display_Set = Work_Num[i].Speed.Set;
        Deal_Speed(i);
        Work_Num[i].Time.Display_Set = Work_Num[i].Time.Set;
        Work_Num[i].Time.Display_Rel = Work_Num[i].Time.Rel;
    }
     Display_IC(Work_Num);
}
