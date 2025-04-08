#include "Show.h"

/**********全局变量**********/
float Twinkle_Time; // 闪烁时间

/**********局部变量声明*******/
uint8_t Temp_ShowFlag, Speed_ShowFlag, Time_ShowFlag ,Lock_ShowFlag; // 时间、速度、温度显示的标志位，0：常亮，1：熄灭
uint8_t Shake_Flag;

/**
 * @brief 闪烁检测
 *
 * @param dT 任务周期
 */
static void Check_ShowFlag(float dT)
{
	static float T;
	if (Twinkle_Time && !EC11A[0].EC11A_Knob) // 闪烁和没有操作按键时
	{
		if (T == 0)
		{
            if (sys.SetMode_Option == 0)
			{
				Temp_ShowFlag = 0;				  // 常亮
				Speed_ShowFlag = ~Speed_ShowFlag; // 速度闪烁
				Time_ShowFlag = 0;				  // 常亮
			}
			else if (sys.SetMode_Option == 1)
			{
				Temp_ShowFlag = 0;				  // 常亮
				Speed_ShowFlag = ~Speed_ShowFlag; // 速度闪烁
				Time_ShowFlag = 0;				  // 常亮
			}
			else if (sys.SetMode_Option == 2)
			{
				Temp.Safe_Mode = 1;				// 点亮"SAFE"图标
				Temp_ShowFlag = ~Temp_ShowFlag; // 温度闪烁
				Speed_ShowFlag = 0;				// 常亮
				Time_ShowFlag = 0;				// 常亮
			}
			else if (sys.SetMode_Option == 3)
			{
				Temp_ShowFlag = 0;				// 常亮
				Speed_ShowFlag = 0;				// 常亮
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
                SetOK_Flag = 1; // 检测到设置，等待退出设置模式
			}
			T = 0;
		}
	}
	else
	{
		Temp_ShowFlag = 0;	// 常亮
		Speed_ShowFlag = 0; // 常亮
		Time_ShowFlag = 0;	// 常亮
		T = 0;
	}
}

/**
 * @brief 图标闪烁
 *
 * @param dT 任务周期
 */
static void Icn_Twinkle(float dT)
{
	static float T;

	if (sys.Run_Status == 1)
	{
		T += dT;
		if (T >= 0.5f)
		{
			Time.Icn = ~Time.Icn;
			T = 0;
		}
	}
	else
	{
		Time.Icn = 0;
	}
}

/**
 * @brief 锁定误触图标闪烁检测
 *
 * @param dT 任务周期
 */
void Check_Lock(float dT)
{
    static float T;
	if (Lock_Alarm)
	{
		T += dT;
		if (T >= 0.5f)
		{
			Lock_ShowFlag = ~Lock_ShowFlag;//安全温度图标闪烁
            Lock_Alarm -= 0.5f;
			T = 0;
		}
	}
    else
    {
        Lock_ShowFlag = 0;
    }
}

/**
 * @brief 倾倒检测
 *
 * @param dT 任务周期
 */
static void Check_ShakeCartoon(float dT)
{
    static float T;

	if (Shake_Alarm)
	{
		T += dT;
		if (T >= 0.5f)
		{
			Shake_Flag = ~Shake_Flag;//安全温度图标闪烁
			T = 0;
		}
	}
	else
	{
		Shake_Flag = 0;
	}
}

/**
 * @brief 转速图标转动任务
 *
 * @param dT 任务周期
 */
void SpeedIcn_Duty(float dT)
{
	static float T;
	if ((sys.Run_Status == 1) && Speed.Ctrl) // 启动，并且在设定了转速的情况下
	{
		if (T == 0)
		{
			Speed.IcnStep++;
			if (Speed.IcnStep > 3)
				Speed.IcnStep = 1;
		}
		T += dT;
		if (T >= 0.5f)
		{
			T = 0;
		}
	}
	else
	{
		Speed.IcnStep = 0;
		T = 0;
	}
}

/**
 * @brief 安全温度图标闪烁检测
 *
 * @param dT 任务周期
 */
static void Check_Safe_Mode(float dT)
{
	static float T;
	if (Temp.Icn)
	{
		T += dT;
		if (T >= 0.5f)
		{
			Temp.Safe_Mode = ~Temp.Safe_Mode; // 安全温度图标闪烁
			T = 0;
		}
	}
	else
	{
		if (sys.SetMode_Option == 2)
			Temp.Safe_Mode = 1;
		else
			Temp.Safe_Mode = 0;
	}
}

/**
 * @brief 闪烁函数
 *
 * @param dT 任务周期
 */
void Twinkle(float dT)
{
	Check_Safe_Mode(dT);
	Check_ShowFlag(dT);
	Check_ShakeCartoon(dT);
	SpeedIcn_Duty(dT);
    Check_Lock(dT);
	Icn_Twinkle(dT);
}

uint8_t seg[18] = {0};

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
 * @brief 显示屏幕函数
 *
 * @param dis_rel_speed 实际转速
 * @param dis_set_speed 设定转速
 * @param dis_temp 显示温度
 * @param dis_time 显示时间
 */
void Display_Show(uint16_t dis_rel_speed, uint16_t dis_set_speed, uint32_t dis_time, int16_t dis_temp)
{
    uint8_t Val;// 用于百十个取出来的数字
    if (!Shake_Alarm)
    {
        /**********显示实际转速**********/
        if (dis_rel_speed > 9999) // 大于9999时
        {
            Val = dis_rel_speed / 10000 % 10;
           switch (Val)
           {
           case 0:
                bit_Cal(8,0xE0,0xA0);bit_Cal(9,0xF0,0xF0);
                break;
           case 1:
                bit_Cal(8,0xE0,0x00);bit_Cal(9,0xF0,0x60);
                break;
           case 2:
                bit_Cal(8,0xE0,0x60);bit_Cal(9,0xF0,0xD0);
                break;
           case 3:
                bit_Cal(8,0xE0,0x40);bit_Cal(9,0xF0,0xF0);
                break;
           case 4:
                bit_Cal(8,0xE0,0xC0);bit_Cal(9,0xF0,0x60);
                break;
           case 5:
                bit_Cal(8,0xE0,0xC0);bit_Cal(9,0xF0,0xB0);
                break;
           case 6:
                bit_Cal(8,0xE0,0xE0);bit_Cal(9,0xF0,0xB0);
                break;
           case 7:
                bit_Cal(8,0xE0,0x00);bit_Cal(9,0xF0,0xE0);
                break;
           case 8:
                bit_Cal(8,0xE0,0xE0);bit_Cal(9,0xF0,0xF0);
                break;
           case 9:
                bit_Cal(8,0xE0,0xC0);bit_Cal(9,0xF0,0xF0);
                break;
           default:
               break;
           }
        }
        else
        {
            bit_Cal(8,0xE0,0x00);bit_Cal(9,0xF0,0x00);
        }
        
         if (dis_rel_speed > 999) // 大于999时
         {
              Val = dis_rel_speed / 1000 % 10;
              switch (Val)
              {
              case 0:
                   bit_Cal(10,0xE0,0xA0);bit_Cal(11,0xF0,0xF0);
                   break;
              case 1:
                   bit_Cal(10,0xE0,0x00);bit_Cal(11,0xF0,0x60);
                   break;
              case 2:
                   bit_Cal(10,0xE0,0x60);bit_Cal(11,0xF0,0xD0);
                   break;
              case 3:
                   bit_Cal(10,0xE0,0x40);bit_Cal(11,0xF0,0xF0);
                   break;
              case 4:
                   bit_Cal(10,0xE0,0xC0);bit_Cal(11,0xF0,0x60);
                   break;
              case 5:
                   bit_Cal(10,0xE0,0xC0);bit_Cal(11,0xF0,0xB0);
                   break;
              case 6:
                   bit_Cal(10,0xE0,0xE0);bit_Cal(11,0xF0,0xB0);
                   break;
              case 7:
                   bit_Cal(10,0xE0,0x00);bit_Cal(11,0xF0,0xE0);
                   break;
              case 8:
                   bit_Cal(10,0xE0,0xE0);bit_Cal(11,0xF0,0xF0);
                   break;
              case 9:
                   bit_Cal(10,0xE0,0xC0);bit_Cal(11,0xF0,0xF0);
                   break;
              default:
                   break;
              }
         }
         else
         {
              bit_Cal(10,0xE0,0x00);bit_Cal(11,0xF0,0x00);
         }
        
         if (dis_rel_speed > 99) // 大于99时
         {
              Val = dis_rel_speed / 100 % 10;
              switch (Val)
              {
              case 0:
                   bit_Cal(12,0xE0,0xA0);bit_Cal(13,0xF0,0xF0);
                   break;
              case 1:
                   bit_Cal(12,0xE0,0x00);bit_Cal(13,0xF0,0x60);
                   break;
              case 2:
                   bit_Cal(12,0xE0,0x60);bit_Cal(13,0xF0,0xD0);
                   break;
              case 3:
                   bit_Cal(12,0xE0,0x40);bit_Cal(13,0xF0,0xF0);
                   break;
              case 4:
                   bit_Cal(12,0xE0,0xC0);bit_Cal(13,0xF0,0x60);
                   break;
              case 5:
                   bit_Cal(12,0xE0,0xC0);bit_Cal(13,0xF0,0xB0);
                   break;
              case 6:
                   bit_Cal(12,0xE0,0xE0);bit_Cal(13,0xF0,0xB0);
                   break;
              case 7:
                   bit_Cal(12,0xE0,0x00);bit_Cal(13,0xF0,0xE0);
                   break;
              case 8:
                   bit_Cal(12,0xE0,0xE0);bit_Cal(13,0xF0,0xF0);
                   break;
              case 9:
                   bit_Cal(12,0xE0,0xC0);bit_Cal(13,0xF0,0xF0);
                   break;
              default:
                   break;
              }
         }
         else
         {
              bit_Cal(12,0xE0,0x00);bit_Cal(13,0xF0,0x00);
         }

         if (dis_rel_speed > 9) // 大于9时
         {
              Val = dis_rel_speed / 10 % 10;
              switch (Val)
              {
              case 0:
                   bit_Cal(14,0xE0,0xA0);bit_Cal(15,0xF0,0xF0);
                   break;
              case 1:
                   bit_Cal(14,0xE0,0x00);bit_Cal(15,0xF0,0x60);
                   break;
              case 2:
                   bit_Cal(14,0xE0,0x60);bit_Cal(15,0xF0,0xD0);
                   break;
              case 3:
                   bit_Cal(14,0xE0,0x40);bit_Cal(15,0xF0,0xF0);
                   break;
              case 4:
                   bit_Cal(14,0xE0,0xC0);bit_Cal(15,0xF0,0x60);
                   break;
              case 5:
                   bit_Cal(14,0xE0,0xC0);bit_Cal(15,0xF0,0xB0);
                   break;
              case 6:
                   bit_Cal(14,0xE0,0xE0);bit_Cal(15,0xF0,0xB0);
                   break;
              case 7:
                   bit_Cal(14,0xE0,0x00);bit_Cal(15,0xF0,0xE0);
                   break;
              case 8:
                   bit_Cal(14,0xE0,0xE0);bit_Cal(15,0xF0,0xF0);
                   break;
              case 9:
                   bit_Cal(14,0xE0,0xC0);bit_Cal(15,0xF0,0xF0);
                   break;
              default:
                   break;
              }
         }
         else
         {
              bit_Cal(14,0xE0,0x00);bit_Cal(15,0xF0,0x00);
         }

         if (dis_rel_speed > 0) // 大于等于0时
         {
              Val = dis_rel_speed % 10;
              switch (Val)
              {
              case 0:
                   bit_Cal(16,0xE0,0xA0);bit_Cal(17,0xF0,0xF0);
                   break;
              case 1:
                   bit_Cal(16,0xE0,0x00);bit_Cal(17,0xF0,0x60);
                   break;
              case 2:
                   bit_Cal(16,0xE0,0x60);bit_Cal(17,0xF0,0xD0);
                   break;
              case 3:
                   bit_Cal(16,0xE0,0x40);bit_Cal(17,0xF0,0xF0);
                   break;
              case 4:
                   bit_Cal(16,0xE0,0xC0);bit_Cal(17,0xF0,0x60);
                   break;
              case 5:
                   bit_Cal(16,0xE0,0xC0);bit_Cal(17,0xF0,0xB0);
                   break;
              case 6:
                   bit_Cal(16,0xE0,0xE0);bit_Cal(17,0xF0,0xB0);
                   break;
              case 7:
                   bit_Cal(16,0xE0,0x00);bit_Cal(17,0xF0,0xE0);
                   break;
              case 8:
                   bit_Cal(16,0xE0,0xE0);bit_Cal(17,0xF0,0xF0);
                   break;
              case 9:
                   bit_Cal(16,0xE0,0xC0);bit_Cal(17,0xF0,0xF0);
                   break;
              default:
                   break;
              }
         }
         else
         {
              bit_Cal(16,0xE0,0xA0);bit_Cal(17,0xF0,0xF0);
         }
         
        /**********显示设定转速**********/
        if (!Speed_ShowFlag)
        {
             if (dis_set_speed > 9999) // 大于9999时
             {
                  Val = dis_set_speed / 10000 % 10;
               switch (Val)
               {
               case 0:
                    bit_Cal(8,0x1E,0x1E);bit_Cal(9,0x0E,0x0A);
                    break;
               case 1:
                    bit_Cal(8,0x1E,0x00);bit_Cal(9,0x0E,0x0A);
                    break;
               case 2:
                    bit_Cal(8,0x1E,0x16);bit_Cal(9,0x0E,0x0C);
                    break;
               case 3:
                    bit_Cal(8,0x1E,0X12);bit_Cal(9,0x0E,0x0E);
                    break;
               case 4:
                    bit_Cal(8,0x1E,0x08);bit_Cal(9,0x0E,0x0E);
                    break;
               case 5:
                    bit_Cal(8,0x1E,0X1A);bit_Cal(9,0x0E,0x06);
                    break;
               case 6:
                    bit_Cal(8,0x1E,0x1E);bit_Cal(9,0x0E,0x06);
                    break;
               case 7:
                    bit_Cal(8,0x1E,0x10);bit_Cal(9,0x0E,0x0A);
                    break;
               case 8:
                    bit_Cal(8,0x1E,0x1E);bit_Cal(9,0x0E,0x0E);
                    break;
               case 9:
                    bit_Cal(8,0x1E,0x1A);bit_Cal(9,0x0E,0x0E);
                    break;
               default:
                   break;
               }
             }
             else
             {
                  bit_Cal(8,0x1E,0x00);bit_Cal(9,0x0E,0x00);
             }
            
             if (dis_set_speed > 999) // 大于999时
             {
                  Val = dis_set_speed / 1000 % 10;
                  switch (Val)
               {
               case 0:
                    bit_Cal(10,0x1E,0x1E);bit_Cal(11,0x0E,0x0A);
                    break;
               case 1:
                    bit_Cal(10,0x1E,0x00);bit_Cal(11,0x0E,0x0A);
                    break;
               case 2:
                    bit_Cal(10,0x1E,0x16);bit_Cal(11,0x0E,0x0C);
                    break;
               case 3:
                    bit_Cal(10,0x1E,0X12);bit_Cal(11,0x0E,0x0E);
                    break;
               case 4:
                    bit_Cal(10,0x1E,0x08);bit_Cal(11,0x0E,0x0E);
                    break;
               case 5:
                    bit_Cal(10,0x1E,0X1A);bit_Cal(11,0x0E,0x06);
                    break;
               case 6:
                    bit_Cal(10,0x1E,0x1E);bit_Cal(11,0x0E,0x06);
                    break;
               case 7:
                    bit_Cal(10,0x1E,0x10);bit_Cal(11,0x0E,0x0A);
                    break;
               case 8:
                    bit_Cal(10,0x1E,0x1E);bit_Cal(11,0x0E,0x0E);
                    break;
               case 9:
                    bit_Cal(10,0x1E,0x1A);bit_Cal(11,0x0E,0x0E);
                    break;
               default:
                   bit_Cal(10,0x1E,0x00);bit_Cal(11,0x0E,0x04);//-
                   break;
               }
             }
             else
             {
                  bit_Cal(10,0x1E,0x00);bit_Cal(11,0x0E,0x00);
             }
            
             if (dis_set_speed > 99) // 大于99时
             {
                  Val = dis_set_speed / 100 % 10;
                  switch (Val)
               {
               case 0:
                    bit_Cal(12,0x1E,0x1E);bit_Cal(13,0x0E,0x0A);
                    break;
               case 1:
                    bit_Cal(12,0x1E,0x00);bit_Cal(13,0x0E,0x0A);
                    break;
               case 2:
                    bit_Cal(12,0x1E,0x16);bit_Cal(13,0x0E,0x0C);
                    break;
               case 3:
                    bit_Cal(12,0x1E,0X12);bit_Cal(13,0x0E,0x0E);
                    break;
               case 4:
                    bit_Cal(12,0x1E,0x08);bit_Cal(13,0x0E,0x0E);
                    break;
               case 5:
                    bit_Cal(12,0x1E,0X1A);bit_Cal(13,0x0E,0x06);
                    break;
               case 6:
                    bit_Cal(12,0x1E,0x1E);bit_Cal(13,0x0E,0x06);
                    break;
               case 7:
                    bit_Cal(12,0x1E,0x10);bit_Cal(13,0x0E,0x0A);
                    break;
               case 8:
                    bit_Cal(12,0x1E,0x1E);bit_Cal(13,0x0E,0x0E);
                    break;
               case 9:
                    bit_Cal(12,0x1E,0x1A);bit_Cal(13,0x0E,0x0E);
                    break;
               default:
                   bit_Cal(12,0x1E,0x00);bit_Cal(13,0x0E,0x04);//-
                   break;
               }
             }
             else
             {
                  bit_Cal(12,0x1E,0x00);bit_Cal(13,0x0E,0x00);
             }

             if (dis_set_speed > 9) // 大于9时
             {
                  Val = dis_set_speed / 10 % 10;
                  switch (Val)
               {
               case 0:
                    bit_Cal(14,0x1E,0x1E);bit_Cal(15,0x0E,0x0A);
                    break;
               case 1:
                    bit_Cal(14,0x1E,0x00);bit_Cal(15,0x0E,0x0A);
                    break;
               case 2:
                    bit_Cal(14,0x1E,0x16);bit_Cal(15,0x0E,0x0C);
                    break;
               case 3:
                    bit_Cal(14,0x1E,0X12);bit_Cal(15,0x0E,0x0E);
                    break;
               case 4:
                    bit_Cal(14,0x1E,0x08);bit_Cal(15,0x0E,0x0E);
                    break;
               case 5:
                    bit_Cal(14,0x1E,0X1A);bit_Cal(15,0x0E,0x06);
                    break;
               case 6:
                    bit_Cal(14,0x1E,0x1E);bit_Cal(15,0x0E,0x06);
                    break;
               case 7:
                    bit_Cal(14,0x1E,0x10);bit_Cal(15,0x0E,0x0A);
                    break;
               case 8:
                    bit_Cal(14,0x1E,0x1E);bit_Cal(15,0x0E,0x0E);
                    break;
               case 9:
                    bit_Cal(14,0x1E,0x1A);bit_Cal(15,0x0E,0x0E);
                    break;
               default:
                   bit_Cal(14,0x1E,0x00);bit_Cal(15,0x0E,0x04);//-
                   break;
               }
             }
             else
             {
                  bit_Cal(14,0x1E,0x00);bit_Cal(15,0x0E,0x00);
             }

             if (dis_set_speed > 0) // 大于等于0时
             {
                  Val = dis_set_speed % 10;
                  switch (Val)
               {
               case 0:
                    bit_Cal(16,0x1E,0x1E);bit_Cal(17,0x0E,0x0A);
                    break;
               case 1:
                    bit_Cal(16,0x1E,0x00);bit_Cal(17,0x0E,0x0A);
                    break;
               case 2:
                    bit_Cal(16,0x1E,0x16);bit_Cal(17,0x0E,0x0C);
                    break;
               case 3:
                    bit_Cal(16,0x1E,0X12);bit_Cal(17,0x0E,0x0E);
                    break;
               case 4:
                    bit_Cal(16,0x1E,0x08);bit_Cal(17,0x0E,0x0E);
                    break;
               case 5:
                    bit_Cal(16,0x1E,0X1A);bit_Cal(17,0x0E,0x06);
                    break;
               case 6:
                    bit_Cal(16,0x1E,0x1E);bit_Cal(17,0x0E,0x06);
                    break;
               case 7:
                    bit_Cal(16,0x1E,0x10);bit_Cal(17,0x0E,0x0A);
                    break;
               case 8:
                    bit_Cal(16,0x1E,0x1E);bit_Cal(17,0x0E,0x0E);
                    break;
               case 9:
                    bit_Cal(16,0x1E,0x1A);bit_Cal(17,0x0E,0x0E);
                    break;
               default:
                   bit_Cal(16,0x1E,0x00);bit_Cal(17,0x0E,0x04);//-
                   break;
               }
             }
             else
             {
                  bit_Cal(16,0x1E,0x00);bit_Cal(17,0x0E,0x00);
             }
         }
        else
        {
            bit_Cal(8,0x1E,0x00);bit_Cal(9,0x0E,0x00);
            bit_Cal(10,0x1E,0x00);bit_Cal(11,0x0E,0x00);
            bit_Cal(12,0x1E,0x00);bit_Cal(13,0x0E,0x00);
            bit_Cal(14,0x1E,0x00);bit_Cal(15,0x0E,0x00);
            bit_Cal(16,0x1E,0x00);bit_Cal(17,0x0E,0x00);
        }
        /**********时间**********/
         /**********工位3的实际时间显示**********/
        if (!Time_ShowFlag)
        {
            if(dis_time == 0)
            {
                bit_Cal(6, 0x07, 0x02);bit_Cal(7, 0x0F, 0x00);//显示“-”
                bit_Cal(2, 0x0E, 0x04);bit_Cal(3, 0x1E, 0x00);//显示“-”
                bit_Cal(2, 0x0E, 0x04);bit_Cal(3, 0x1E, 0x00);//显示“-”
                bit_Cal(0, 0x07, 0x02);bit_Cal(1, 0x0F, 0x00);//显示“-”
                /**********时间冒号图标**********/
                bit_Cal(4, 0x01, 0x00);
            }
            else
            {
                /**********时间计算**********/
                if (Time.Display < 3600)
                {
                    Val = dis_time % 3600 / 60 / 10; // 计算十位为单位的分钟数
                }
                else
                {
                    Val = dis_time / 3600 / 10;//计算十位为单位的小时数
                }
                switch (Val)
                {
                    case 0:
                            bit_Cal(6, 0x07, 0x05);bit_Cal(7, 0x0F, 0x0F);
                        break;
                    case 1:
                            bit_Cal(6, 0x07, 0x05);bit_Cal(7, 0x0F, 0x00);
                        break;
                    case 2:
                            bit_Cal(6, 0x07, 0x03);bit_Cal(7, 0x0F, 0x0D);
                        break;
                    case 3:
                            bit_Cal(6, 0x07, 0x07);bit_Cal(7, 0x0F, 0x09);
                        break;
                    case 4:
                            bit_Cal(6, 0x07, 0x07);bit_Cal(7, 0x0F, 0x02);
                        break;
                    case 5:
                            bit_Cal(6, 0x07, 0x06);bit_Cal(7, 0x0F, 0x0B);
                        break;
                    case 6:
                            bit_Cal(6, 0x07, 0x06);bit_Cal(7, 0x0F, 0x0F);
                        break;
                    case 7:
                            bit_Cal(6, 0x07, 0x05);bit_Cal(7, 0x0F, 0x01);
                        break;
                    case 8:
                            bit_Cal(6, 0x07, 0x07);bit_Cal(7, 0x0F, 0x0F);
                        break;
                    case 9:
                            bit_Cal(6, 0x07, 0x07);bit_Cal(7, 0x0F, 0x0B);
                        break;
                    default:
                            bit_Cal(6, 0x07, 0x02);bit_Cal(7, 0x0F, 0x00);//显示“-”
                        break;
                }
                if (Time.Display < 3600)
                {
                    Val = dis_time % 3600 / 60 % 10;	// 计算个位为单位的分钟数
                }
                else
                {
                    Val = dis_time / 3600 % 10;// 计算个位为单位的小时数
                }
                switch (Val)
                {
                    case 0:
                            bit_Cal(4, 0x0E, 0x0A);bit_Cal(5, 0x1E, 0x1E);
                        break;
                    case 1:
                            bit_Cal(4, 0x0E, 0x0A);bit_Cal(5, 0x1E, 0x00);
                        break;
                    case 2:
                            bit_Cal(4, 0x0E, 0x06);bit_Cal(5, 0x1E, 0x1A);
                        break;
                    case 3:
                            bit_Cal(4, 0x0E, 0x0E);bit_Cal(5, 0x1E, 0x12);
                        break;
                    case 4:
                            bit_Cal(4, 0x0E, 0x0E);bit_Cal(5, 0x1E, 0x04);
                        break;
                    case 5:
                            bit_Cal(4, 0x0E, 0x0C);bit_Cal(5, 0x1E, 0x16);
                        break;
                    case 6:
                            bit_Cal(4, 0x0E, 0x0C);bit_Cal(5, 0x1E, 0x1E);
                        break;
                    case 7:
                            bit_Cal(4, 0x0E, 0x0A);bit_Cal(5, 0x1E, 0x02);
                        break;
                    case 8:
                            bit_Cal(4, 0x0E, 0x0E);bit_Cal(5, 0x1E, 0x1E);
                        break;
                    case 9:
                            bit_Cal(4, 0x0E, 0x0E);bit_Cal(5, 0x1E, 0x16);
                        break;
                    default:
                            bit_Cal(4, 0x0E, 0x04);bit_Cal(5, 0x1E, 0x00);//显示“-”
                        break;
                }

                if (Time.Display < 3600)
                {
                    Val = dis_time % 60 / 10;// 计算个位为单位的分钟数
                }
                else
                {
                    Val = dis_time % 3600 / 60 / 10; // 计算十分位为单位的分钟数
                }
                switch (Val)
                {
                    case 0:
                            bit_Cal(2, 0x0E, 0x0A);bit_Cal(3, 0x1E, 0x1E);
                        break;
                    case 1:
                            bit_Cal(2, 0x0E, 0x0A);bit_Cal(3, 0x1E, 0x00);
                        break;
                    case 2:
                            bit_Cal(2, 0x0E, 0x06);bit_Cal(3, 0x1E, 0x1A);
                        break;
                    case 3:
                            bit_Cal(2, 0x0E, 0x0E);bit_Cal(3, 0x1E, 0x12);
                        break;
                    case 4:
                            bit_Cal(2, 0x0E, 0x0E);bit_Cal(3, 0x1E, 0x04);
                        break;
                    case 5:
                            bit_Cal(2, 0x0E, 0x0C);bit_Cal(3, 0x1E, 0x16);
                        break;
                    case 6:
                            bit_Cal(2, 0x0E, 0x0C);bit_Cal(3, 0x1E, 0x1E);
                        break;
                    case 7:
                            bit_Cal(2, 0x0E, 0x0A);bit_Cal(3, 0x1E, 0x02);
                        break;
                    case 8:
                            bit_Cal(2, 0x0E, 0x0E);bit_Cal(3, 0x1E, 0x1E);
                        break;
                    case 9:
                            bit_Cal(2, 0x0E, 0x0E);bit_Cal(3, 0x1E, 0x16);
                        break;
                    default:
                            bit_Cal(2, 0x0E, 0x04);bit_Cal(3, 0x1E, 0x00);//显示“-”
                        break;
                }

                if (Time.Display < 3600)
                {
                    Val = dis_time % 60 % 10;// 计算个位为单位的分钟数
                }
                else
                {
                    Val = dis_time % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
                }
                switch (Val)
                {
                    case 0:
                            bit_Cal(0, 0x07, 0x05);bit_Cal(1, 0x0F, 0x0F);
                        break;
                    case 1:
                            bit_Cal(0, 0x07, 0x05);bit_Cal(1, 0x0F, 0x00);
                        break;
                    case 2:
                            bit_Cal(0, 0x07, 0x03);bit_Cal(1, 0x0F, 0x0D);
                        break;
                    case 3:
                            bit_Cal(0, 0x07, 0x07);bit_Cal(1, 0x0F, 0x09);
                        break;
                    case 4:
                            bit_Cal(0, 0x07, 0x07);bit_Cal(1, 0x0F, 0x02);
                        break;
                    case 5:
                            bit_Cal(0, 0x07, 0x06);bit_Cal(1, 0x0F, 0x0B);
                        break;
                    case 6:
                            bit_Cal(0, 0x07, 0x06);bit_Cal(1, 0x0F, 0x0F);
                        break;
                    case 7:
                            bit_Cal(0, 0x07, 0x05);bit_Cal(1, 0x0F, 0x01);
                        break;
                    case 8:
                            bit_Cal(0, 0x07, 0x07);bit_Cal(1, 0x0F, 0x0F);
                        break;
                    case 9:
                            bit_Cal(0, 0x07, 0x07);bit_Cal(1, 0x0F, 0x0B);
                        break;
                    default:
                            bit_Cal(0, 0x07, 0x02);bit_Cal(1, 0x0F, 0x00);//显示“-”
                        break;
                }
                /**********时间冒号图标**********/
                bit_Cal(4, 0x01, 0x01);
            }
        }
        else
        {
            bit_Cal(6, 0x07, 0x00);bit_Cal(7, 0x0F, 0x00);//显示“-”
            bit_Cal(4, 0x0E, 0x00);bit_Cal(5, 0x1E, 0x00);//显示“-”
            bit_Cal(2, 0x0E, 0x00);bit_Cal(3, 0x1E, 0x00);//显示“-”
            bit_Cal(0, 0x07, 0x00);bit_Cal(1, 0x0F, 0x00);//显示“-”
            /**********时间冒号图标**********/
            bit_Cal(4, 0x01, 0x00);
        }
        /**********温度显示**********/
        /**********工位3的设定温度显示**********/
        if (!Temp_ShowFlag)
        {
            if (dis_temp > 0)//大于0时
            {
                if (dis_temp >= 0)//大于等于0时
                {
                    Val = dis_temp / 1000 % 10;
                }
                else if (dis_temp < 0 && dis_temp > -100)
                {
                    Val = ABS(dis_temp) / 1000 % 10;//计算后是0，不大于999所以不会显示
                }
                else if (dis_temp <= -100 && dis_temp > -1000)
                {
                    Val = 10;//显示“-”
                }
                switch (Val)
                {
                    case 0:
                        if (dis_temp > 999)//显示0
                        {
                            bit_Cal(6, 0x78, 0x78);bit_Cal(7, 0x70, 0x50);
                        }
                        else//不显示这位
                        {
                            bit_Cal(6, 0x78, 0x00);bit_Cal(7, 0x70, 0x00);
                        }
                        break;
                    case 1:
                        bit_Cal(6, 0x78, 0x30);bit_Cal(7, 0x70, 0x00);
                        break;
                    case 2:
                        bit_Cal(6, 0x78, 0x58);bit_Cal(7, 0x70, 0x60);
                        break;
                    case 3:
                        bit_Cal(6, 0x78, 0x78);bit_Cal(7, 0x70, 0x20);
                        break;
                    case 4:
                        bit_Cal(6, 0x78, 0x30);bit_Cal(7, 0x70, 0x30);
                        break;
                    case 5:
                        bit_Cal(6, 0x78, 0x68);bit_Cal(7, 0x70, 0x30);
                        break;
                    case 6:
                        bit_Cal(6, 0x78, 0x68);bit_Cal(7, 0x70, 0x70);
                        break;
                    case 7:
                        bit_Cal(6, 0x78, 0x38);bit_Cal(7, 0x70, 0x00);
                        break;
                    case 8:
                        bit_Cal(6, 0x78, 0x78);bit_Cal(7, 0x70, 0x70);
                        break;
                    case 9:
                        bit_Cal(6, 0x78, 0x78);bit_Cal(7, 0x70, 0x30);
                        break;
                    default:
                        bit_Cal(6, 0x78, 0x00);bit_Cal(7, 0x70, 0x20);//显示“-”
                        break;
                }

                if (dis_temp >= 0)//大于等于0时
                {
                    Val = dis_temp / 100 % 10;
                }
                else if (dis_temp < 0 && dis_temp > -100)
                {
                    Val = 10;//显示“-”
                }
                else if (dis_temp <= -100 && dis_temp > -1000)
                {
                    Val = ABS(dis_temp)/ 100 % 10;
                }
                switch (Val)
                {
                    case 0:
                        if (dis_temp > 999)//显示0
                        {
                            bit_Cal(4, 0xF0, 0xF0);bit_Cal(5, 0xE0, 0xA0);
                        }
                        else//不显示这位
                        {
                            bit_Cal(4, 0xF0, 0x00);bit_Cal(5, 0xE0, 0x00);
                        }
                        break;
                    case 1:
                        bit_Cal(4, 0xF0, 0x60);bit_Cal(5, 0xE0, 0x00);
                        break;
                    case 2:
                        bit_Cal(4, 0xF0, 0xB0);bit_Cal(5, 0xE0, 0xC0);
                        break;
                    case 3:
                        bit_Cal(4, 0xF0, 0xF0);bit_Cal(5, 0xE0, 0x40);
                        break;
                    case 4:
                        bit_Cal(4, 0xF0, 0x60);bit_Cal(5, 0xE0, 0x60);
                        break;
                    case 5:
                        bit_Cal(4, 0xF0, 0XD0);bit_Cal(5, 0xE0, 0x60);
                        break;
                    case 6:
                        bit_Cal(4, 0xF0, 0XD0);bit_Cal(5, 0xE0, 0xE0);
                        break;
                    case 7:
                        bit_Cal(4, 0xF0, 0x70);bit_Cal(5, 0xE0, 0x00);
                        break;
                    case 8:
                        bit_Cal(4, 0xF0, 0xF0);bit_Cal(5, 0xE0, 0xE0);
                        break;
                    case 9:
                        bit_Cal(4, 0xF0, 0xF0);bit_Cal(5, 0xE0, 0x60);
                        break;
                    default:
                        bit_Cal(4, 0xF0, 0x00);bit_Cal(5, 0xE0, 0x40);//显示“-”
                        break;
                }

                if (dis_temp >= 0)//大于等于0时
                {
                    Val = dis_temp / 10 % 10;
                }
                else if (dis_temp < 0 && dis_temp > -100)
                {
                    Val = ABS(dis_temp) / 10 % 10;
                }
                else if (dis_temp <= -100 && dis_temp > -1000)
                {
                    Val = ABS(dis_temp) / 10 % 10;
                }
                switch (Val)
                {
                    case 0:
                        bit_Cal(2, 0xF0, 0xF0);bit_Cal(3, 0xE0, 0xA0);
                        break;
                    case 1:
                        bit_Cal(2, 0xF0, 0x60);bit_Cal(3, 0xE0, 0x00);
                        break;
                    case 2:
                        bit_Cal(2, 0xF0, 0xB0);bit_Cal(3, 0xE0, 0xC0);
                        break;
                    case 3:
                        bit_Cal(2, 0xF0, 0xF0);bit_Cal(3, 0xE0, 0x40);
                        break;
                    case 4:
                        bit_Cal(2, 0xF0, 0x60);bit_Cal(3, 0xE0, 0x60);
                        break;
                    case 5:
                        bit_Cal(2, 0xF0, 0XD0);bit_Cal(3, 0xE0, 0x60);
                        break;
                    case 6:
                        bit_Cal(2, 0xF0, 0XD0);bit_Cal(3, 0xE0, 0xE0);
                        break;
                    case 7:
                        bit_Cal(2, 0xF0, 0x70);bit_Cal(3, 0xE0, 0x00);
                        break;
                    case 8:
                        bit_Cal(2, 0xF0, 0xF0);bit_Cal(3, 0xE0, 0xE0);
                        break;
                    case 9:
                        bit_Cal(2, 0xF0, 0xF0);bit_Cal(3, 0xE0, 0x60);
                        break;
                    default:
                        bit_Cal(2, 0xF0, 0x00);bit_Cal(3, 0xE0, 0x40);//显示“-”
                        break;
                }

                if (dis_temp >= 0)//大于等于0时
                {
                    Val = dis_temp % 10;
                }
                else if (dis_temp < 0 && dis_temp > -100)
                {
                    Val = ABS(dis_temp) % 10;
                }
                else if (dis_temp <= -100 && dis_temp > -1000)
                {
                    Val = ABS(dis_temp) % 10;
                }
                switch (Val)
                {
                    case 0:
                        bit_Cal(0, 0x78, 0x78);bit_Cal(1, 0x70, 0x50);
                        break;
                    case 1:
                        bit_Cal(0, 0x78, 0x30);bit_Cal(1, 0x70, 0x00);
                        break;
                    case 2:
                        bit_Cal(0, 0x78, 0x58);bit_Cal(1, 0x70, 0x60);
                        break;
                    case 3:
                        bit_Cal(0, 0x78, 0x78);bit_Cal(1, 0x70, 0x20);
                        break;
                    case 4:
                        bit_Cal(0, 0x78, 0x30);bit_Cal(1, 0x70, 0x30);
                        break;
                    case 5:
                        bit_Cal(0, 0x78, 0x68);bit_Cal(1, 0x70, 0x30);
                        break;
                    case 6:
                        bit_Cal(0, 0x78, 0x68);bit_Cal(1, 0x70, 0x70);
                        break;
                    case 7:
                        bit_Cal(0, 0x78, 0x38);bit_Cal(1, 0x70, 0x00);
                        break;
                    case 8:
                        bit_Cal(0, 0x78, 0x78);bit_Cal(1, 0x70, 0x70);
                        break;
                    case 9:
                        bit_Cal(0, 0x78, 0x78);bit_Cal(1, 0x70, 0x30);
                        break;
                    default:
                        bit_Cal(0, 0x78, 0x00);bit_Cal(1, 0x70, 0x20);//显示“-”
                        break;
                }
                /**********温度小数点图标**********/
                bit_Cal(1, 0x80, 0x80);
            }
            else
            {
                bit_Cal(6, 0x78, 0x00);bit_Cal(7, 0x70, 0x20);//显示“-”
                bit_Cal(4, 0xF0, 0x00);bit_Cal(5, 0xE0, 0x40);//显示“-”
                bit_Cal(2, 0xF0, 0x00);bit_Cal(3, 0xE0, 0x40);//显示“-”
                bit_Cal(0, 0x78, 0x00);bit_Cal(1, 0x70, 0x20);//显示“-”
                /**********温度小数点图标**********/
                bit_Cal(1, 0x80, 0x00);
            }
        }
        else
        {
            bit_Cal(6, 0x78, 0x00);bit_Cal(7, 0x70, 0x00);//不显示
            bit_Cal(4, 0xF0, 0x00);bit_Cal(5, 0xE0, 0x00);//不显示
            bit_Cal(2, 0xF0, 0x00);bit_Cal(3, 0xE0, 0x00);//不显示
            bit_Cal(0, 0x78, 0x00);bit_Cal(1, 0x70, 0x00);//不显示
            /**********温度小数点图标**********/
            bit_Cal(1, 0x80, 0x00);
        }
        /**********抖动图标**********/
        if (Shake_Switch)
        {
            bit_Cal(0, 0x80, 0x80);
        }
        else
        {
            bit_Cal(0, 0x80, 0x00);
        }

        /**********锁定图标**********/
        if (Lock_Switch && !Lock_ShowFlag)
        {
            bit_Cal(6, 0x80, 0x80);
        }
        else
        {
            bit_Cal(6, 0x80, 0x00);
        }
        
        /**********安全温度图标**********/
        if (Temp.Safe_Mode)
        {
            bit_Cal(7, 0x80, 0x80);
        }
        else
        {
            bit_Cal(7, 0x80, 0x00);
        }
        
        /**********转速图标**********/
        switch (Speed.IcnStep)
        {
        case 0:
            bit_Cal(8, 0x01, 0x01);//S11
            bit_Cal(9, 0x01, 0x01);//S12
            bit_Cal(10, 0x01, 0x01);//S13
            break;

        case 1:
            bit_Cal(8, 0x01, 0x00);//S11
            bit_Cal(9, 0x01, 0x01);//S12
            bit_Cal(10, 0x01, 0x01);//S13
            break;

        case 2:
            bit_Cal(8, 0x01, 0x01);//S11
            bit_Cal(9, 0x01, 0x00);//S12
            bit_Cal(10, 0x01, 0x01);//S13
            break;

        case 3:
            bit_Cal(8, 0x01, 0x01);//S11
            bit_Cal(9, 0x01, 0x01);//S12
            bit_Cal(10, 0x01, 0x00);//S13
            break;
        default:
            break;
        }

        /**********时间图标**********/
        if (Time.Icn)
        {
            bit_Cal(11, 0x01, 0x00);
        }
        else
        {
            bit_Cal(11, 0x01, 0x01);
        }

        /*********时间单位图标**********/
        if (Time.Display < 3600)
        {
            bit_Cal(14, 0x01, 0x01);//sec图标
            bit_Cal(15, 0x01, 0x00);//min图标
        }
        else
        {
            bit_Cal(14, 0x01, 0x00);//sec图标
            bit_Cal(15, 0x01, 0x01);//min图标
        }
        
        /**********℃图标**********/
        bit_Cal(16, 0x01, 0x01);
        
        /**********rpm图标**********/
        bit_Cal(17, 0x01, 0x01);
    }
    else
	{
		for (uint8_t i = 0; i < 18; i++)
		{
			seg[i] = 0x00;
		}
        if (Shake_Flag)
        {
            bit_Cal(0, 0x80, 0x80);
        }
        else
        {
            bit_Cal(0, 0x80, 0x00);
        }
    }
    
    /**********数据发送**********/
    for(uint8_t i=0;i<18;i++)
    {
        Write_Addr_Dat_N(i*2, seg[i], 1);
    }
}

/**
 * @brief 速度显示处理
 *
 * @param dT 任务周期
 */
void Deal_Speed(float dT)
{
	if (sys.Run_Status == 1)
	{
		if (Speed.ADDMode == 0) // 在电机控制中，速度未处理
		{
			if (Speed.Ctrl >= Speed.Display_Rel) // 控制速度大于实际速度
			{
				Speed.ADDMode = 1; // 进入加速模式下
			}
			else if (Speed.Ctrl < Speed.Display_Rel) // 控制速度小于实际速度
			{
				Speed.ADDMode = 2; // 进入减速模式下
			}
		}
		if (Speed.ADDMode == 1) // 在进入加速模式下
		{
			if (Speed.Rel > Speed.Display_Rel) // 当前速度大于显示速度
			{
				if (Speed.Display_Rel < Speed.Rel)
					Speed.Display_Rel = Speed.Rel; // 显示当前速度
			}
			else // 当前速度小于上一次速度
			{
				Speed.Display_Rel = Speed.Display_Rel; // 显示上一次速度，不让速度小于当前速度。呈现攀升速度的现象
			}
			if (Speed.Display_Rel >= Speed.Ctrl) // 实际速度大于等于控制速度
			{
				Speed.ADDMode = 3; // 进入稳定模式
				return;
			}
		}
		if (Speed.ADDMode == 2) // 速度下降模式下
		{
			if (Speed.Rel < Speed.Display_Rel) // 当前速度小于上一次速度
			{
				if (Speed.Display_Rel > Speed.Rel)
					Speed.Display_Rel = Speed.Rel; // 显示当前速度
			}
			else // 当前速度大于上一次速度
			{
				Speed.Display_Rel = Speed.Display_Rel; // 显示上一次速度，不让速度大于当前速度。呈现下降速度的现象
			}

			if (Speed.Display_Rel <= Speed.Ctrl) // 实际速度小于等于控制速度
			{
				Speed.ADDMode = 3; // 进入稳定模式
				return;
			}
		}
		else if (Speed.ADDMode == 3) // 速度稳定模式下
		{
			Speed.Display_Rel = Speed.Ctrl; // 显示控制速度
		}
	}
	else
	{
		if (Speed.Display_Rel && Speed.Display_Rel > Speed.Rel)
			Speed.Display_Rel = Speed.Rel; // 显示当前速度
	}
}

/**
 * @brief 显示屏幕内容
 *
 */
void Show_Display(void)
{
    Speed.Display_Set = Speed.Set;
    
    if (sys.SetMode_Option == 2)
	{
		Temp.Display = Temp.Set;
	}
	else
	{
        if(Receive_ok ==1 && Temp.Rel < 1200)//接收到串口温度数据
        {
            Temp.Display = Temp.Rel;
        }
        else
        {
            Temp.Display = 0;
        }
	}
    
    if (sys.Run_Status)
	{
		Time.Display = Time.Rel;
	}
	else
	{
		Time.Display = Time.Set;
	}
    
    Display_Show(Speed.Display_Rel, Speed.Display_Set,Time.Display,Temp.Display);
}
