#include "Show.h"

/**********全局变量声明******/
float Pmode_Twinkle_Time,Speed_Twinkle_Time,Temp_Twinkle_Time,Time_Twinkle_Time;//速度闪烁时间、温度闪烁时间和时间闪烁时间
float PModeP1_Twinkle_Time, PModeP2_Twinkle_Time;

/**********局部变量声明******/
uint8_t Tab[] = {0xFA,0x0A,0xD6,0x9E,0x2E,0xBC,0xFC,0x1A,0xFE,0xBE};//0·9
uint8_t Pmode_ShowFlag,Temp_ShowFlag,Speed_ShowFlag,Time_ShowFlag;//温度、速度、时间显示的标志位 0:常亮 1：熄灭
uint8_t TempIcn_ShowFlag,TimeIcn_ShowFlag,SpeedIcn_ShowFlag,Lock_ShowFlag;//加热图标闪烁和时间图标闪烁和速度图标闪烁
uint8_t PModeP1_ShowFlag, PModeP2_ShowFlag;// P1，P2闪烁

/**
 * @brief 闪烁检测
 * 
 * @param dT 执行周期
 */
static void Check_ShowFlag(float dT)
{
	static float Speed_T,Temp_T,Time_T,Pmode_T,P1mode_T,P2mode_T;
	if(Speed_Twinkle_Time && !EC11A[1].EC11A_Knob)//速度闪烁和没有操作按键时
    {
		Speed_T += dT;
		if(Speed_T >= 0.5f)
		{
			Speed_Twinkle_Time -= 0.5;//闪烁计时
			Speed_ShowFlag = ~Speed_ShowFlag;//速度闪烁
			if(Speed_Twinkle_Time == 0)//如果闪烁结束
			{
				SpeedSet_Flag = 1;//进入速度设定
			} 
			Speed_T = 0;		
		}			
    }
	else
	{
		Speed_ShowFlag = 0;//常亮
		Speed_T = 0;
	}
	
	if(Temp_Twinkle_Time && !EC11A[0].EC11A_Knob)//速度闪烁和没有操作按键时
    {
		Temp_T += dT;
		if(Temp_T >= 0.5f)
		{
			Temp_Twinkle_Time -= 0.5;//闪烁计时
			Temp_ShowFlag = ~Temp_ShowFlag;//速度闪烁
			if(Temp_Twinkle_Time == 0)//如果闪烁结束
			{
				TempSet_Flag = 1;//进入速度设定
			} 
			Temp_T = 0;		
		}			
    }
	else
	{
		Temp_ShowFlag = 0;//常亮
		Temp_T = 0;
	}
	
	if(Time_Twinkle_Time && (!EC11A[1].EC11A_Knob && !EC11A[0].EC11A_Knob))//时间闪烁和没有操作按键时
    {
		Time_T += dT;
		if(Time_T >= 0.5f)
		{
			Time_Twinkle_Time -= 0.5;//闪烁计时
			Time_ShowFlag = ~Time_ShowFlag;//时间闪烁
			if(Time_Twinkle_Time == 0)//如果闪烁结束
			{
				TimeSet_Flag = 1;//进入时间设定
			} 
			Time_T = 0;			
		}			
    }
	else
	{
		Time_ShowFlag = 0;//常亮
		Time_T = 0;
	}
    
    if(Pmode_Twinkle_Time && (!EC11A[1].EC11A_Knob && !EC11A[0].EC11A_Knob))//时间闪烁和没有操作按键时
    {
		Pmode_T += dT;
		if(Pmode_T >= 0.5f)
		{
			Pmode_Twinkle_Time -= 0.5;//闪烁计时
			Pmode_ShowFlag = ~Pmode_ShowFlag;//时间闪烁
			if(Pmode_Twinkle_Time == 0)//如果闪烁结束
			{
                SpeedSet_Flag = TempSet_Flag = TimeSet_Flag=1;//进入设置
			} 
			Pmode_T = 0;
		}			
    }
	else
	{
		Pmode_ShowFlag = 0;//常亮
		Pmode_T = 0;
	}
    
    if(PModeP1_Twinkle_Time)//时间闪烁和没有操作按键时
    {
        if (PMode.Mode) // 如果打开梯度
        {
            P1mode_T += dT;
            if(P1mode_T >= 0.5f)
            {
                PModeP1_Twinkle_Time -= 0.5;//闪烁计时
                PModeP1_ShowFlag = ~PModeP1_ShowFlag;//时间闪烁
                P1mode_T = 0;
            }
        }
        else
        {
            P1mode_T = 0;
            PModeP1_Twinkle_Time = 0;
            PModeP1_ShowFlag = 0;//常亮
        }
    }
	else
	{
		PModeP1_ShowFlag = 0;//常亮
		P1mode_T = 0;
	}
    
    if(PModeP2_Twinkle_Time)//时间闪烁和没有操作按键时
    {
        if (PMode.Mode) // 如果打开梯度
        {
            P2mode_T += dT;
            if(P2mode_T >= 0.5f)
            {
                PModeP2_Twinkle_Time -= 0.5;//闪烁计时
                PModeP2_ShowFlag = ~PModeP2_ShowFlag;//时间闪烁
                P2mode_T = 0;
            }
        }
        else
        {
            P2mode_T = 0;
            PModeP2_Twinkle_Time = 0;
            PModeP2_ShowFlag = 0;//常亮
        }
    }
	else
	{
		PModeP2_ShowFlag = 0;//常亮
		P2mode_T = 0;
	}
}

/**
 * @brief 外框动画
 *
 * @param dT 任务周期
 */
void Circle_Duty(float dT)
{
    static float T;
    if (PMode.Status)
    {
        if ((sys.Run_Status == 1) && PMode.Status == 2) // 启动，并且在梯度模式下
        {
            if (T == 0)
            {
                PMode.Circle_Step++;
                if (PMode.Circle_Step > 17)
                    PMode.Circle_Step = 6;
                switch (PMode.Circle_Step)
                {
                case 0:
                    PMode.Light_BIT = 0x0FFF; // 全部点亮
                    break;
                case 1:
                    PMode.Light_BIT = 0x0001; // L1点亮
                    break;
                case 2:
                    PMode.Light_BIT = 0x0003; // L1，2点亮
                    break;
                case 3:
                    PMode.Light_BIT = 0x0007; // L1，2，3点亮
                    break;
                case 4:
                    PMode.Light_BIT = 0x000F; // L1，2，3，4点亮
                    break;
                case 5:
                    PMode.Light_BIT = 0x001F; // L1，2，3，4，5，点亮
                    break;
                case 6:
                    PMode.Light_BIT = 0x003F; // L1，2，3，4，5，6点亮
                    break;
                case 7:
                    PMode.Light_BIT = 0x007E; // L2,3,4,5,6,7点亮
                    break;
                case 8:
                    PMode.Light_BIT = 0x00FC; // L3,4,5,6,7,8点亮
                    break;
                case 9:
                    PMode.Light_BIT = 0x01F8; // L4,5,6,7,8,9点亮
                    break;
                case 10:
                    PMode.Light_BIT = 0x03F0; // L5,6,7,8,9,10点亮
                    break;
                case 11:
                    PMode.Light_BIT = 0x07E0; // L6,7,8,9,10,11,点亮
                    break;
                case 12:
                    PMode.Light_BIT = 0x0FC0; // L7,8,9,10,11,12点亮
                    break;
                case 13:
                    PMode.Light_BIT = 0x0F81; // L8,9,10,11,12,1点亮
                    break;
                case 14:
                    PMode.Light_BIT = 0x0F03; // L9,10,11,12,1,2点亮
                    break;
                case 15:
                    PMode.Light_BIT = 0x0E07; // L10,11,12,1，2，3点亮
                    break;
                case 16:
                    PMode.Light_BIT = 0x0C0F; // L11，12，1，2，3，4点亮
                    break;
                case 17:
                    PMode.Light_BIT = 0x081F; // L12，1，2，3，4，5点亮
                    break;
                default:
                    break;
                }
            }
            T += dT;
            if (T >= 0.5f)
            {
                T = 0;
            }
        }
        else
        {
            PMode.Light_BIT = 0x0FFF; // 全部点亮
            T = 0;
        }
    }
    else
    {
        PMode.Light_BIT = 0x0000; // 全部熄灭
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
    Circle_Duty(dT);
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
    if(Temp_ShowFlag)
	{
        bit_Cal(0, 0xF0, 0x00);bit_Cal(1, 0x70, 0x00);//不显示
        bit_Cal(2, 0xF0, 0x00);bit_Cal(3, 0x70, 0x00);//不显示
        bit_Cal(4, 0xF0, 0x00);bit_Cal(5, 0x70, 0x00);//不显示
        bit_Cal(6, 0xF0, 0x00);bit_Cal(7, 0x70, 0x00);//不显示
    }
    else
    {
        if(Temp.Display_Set == 0)
        {
            bit_Cal(0, 0xF0, 0x00);bit_Cal(1, 0x70, 0x20);//显示“-”
            bit_Cal(2, 0xF0, 0x00);bit_Cal(3, 0x70, 0x20);//显示“-”
            bit_Cal(4, 0xF0, 0x00);bit_Cal(5, 0x70, 0x20);//显示“-”
            bit_Cal(6, 0xF0, 0x00);bit_Cal(7, 0x70, 0x20);//显示“-”
        }
        else
        {
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
        }
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
    if(Speed_ShowFlag)
	{
        bit_Cal(18, 0xF0, 0x00);bit_Cal(17, 0x70, 0x00);//不显示
        bit_Cal(11, 0xF0, 0x00);bit_Cal(12, 0x70, 0x00);//不显示
        bit_Cal(13, 0xF0, 0x00);bit_Cal(14, 0x70, 0x00);//不显示
        bit_Cal(15, 0xF0, 0x00);bit_Cal(16, 0x70, 0x00);//不显示
    }
    else
    {
        if(Speed.Display_Set == 0)
        {
            bit_Cal(18, 0xF0, 0x00);bit_Cal(17, 0x70, 0x20);//显示"-"
            bit_Cal(11, 0xF0, 0x00);bit_Cal(12, 0x70, 0x20);//显示"-"
            bit_Cal(13, 0xF0, 0x00);bit_Cal(14, 0x70, 0x20);//显示"-"
            bit_Cal(15, 0xF0, 0x00);bit_Cal(16, 0x70, 0x20);//显示"-"
        }
        else
        {
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
        }
    }

    /**********时间显示**********/
    if(Time.Set || sys.SetMode_Option == 3)//设定时间大于0，在设定时间和闪烁下
	{
		if(!Time_ShowFlag)
        {
            if(Time.Set == 0)
            {
                bit_Cal(26, 0x0F, 0x00);bit_Cal(25, 0x07, 0x02);//显示"-"
                bit_Cal(24, 0x0F, 0x00);bit_Cal(23, 0x07, 0x02);//显示"-"
                bit_Cal(22, 0x0F, 0x00);bit_Cal(21, 0x07, 0x02);//显示"-"
                bit_Cal(20, 0x0F, 0x00);bit_Cal(19, 0x07, 0x02);//显示"-"
            }
            else
            {
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
            }
        }
        else//不显示时间
        {
            bit_Cal(26, 0x0F, 0x00);bit_Cal(25, 0x07, 0x00);
            bit_Cal(24, 0x0F, 0x00);bit_Cal(23, 0x07, 0x00);
            bit_Cal(22, 0x0F, 0x00);bit_Cal(21, 0x07, 0x00);
            bit_Cal(20, 0x0F, 0x00);bit_Cal(19, 0x07, 0x00);
        }
        /**********时间冒号图标**********/
        bit_Cal(8, 0x01, 0x01);

        /**********时间图标**********/
        bit_Cal(19, 0x80, 0x80);

        if(Time.Display < 3600)
        {
            /**********‘sec’图标**********/
            bit_Cal(10, 0x04, 0x04);
            /**********‘min’图标**********/
            bit_Cal(10, 0x08, 0x00);
        }
        else
        {
            /**********‘sec’图标**********/
            bit_Cal(10, 0x04, 0x00);
            /**********‘min’图标**********/
            bit_Cal(10, 0x08, 0x08);
        }
    }
    else//不显示时间
    {
        bit_Cal(26, 0x0F, 0x00);bit_Cal(25, 0x07, 0x00);
        bit_Cal(24, 0x0F, 0x00);bit_Cal(23, 0x07, 0x00);
        bit_Cal(22, 0x0F, 0x00);bit_Cal(21, 0x07, 0x00);
        bit_Cal(20, 0x0F, 0x00);bit_Cal(19, 0x07, 0x00);
        /**********时间冒号图标**********/
        bit_Cal(8, 0x01, 0x00);//不显示
        /**********时间图标**********/
        bit_Cal(19, 0x80, 0x00);//不显示
        /**********‘sec’图标**********/
        bit_Cal(10, 0x04, 0x00);//不显示
        /**********‘min’图标**********/
        bit_Cal(10, 0x08, 0x00);//不显示
    }
    
    if(Temp.Unit)
    {
        /**********华氏度℉**********/
        bit_Cal(8, 0x08, 0x08);
        /**********‘℃’图标**********/
        bit_Cal(7, 0x80, 0x00);
    }
    else
    {
        /**********华氏度℉**********/
        bit_Cal(8, 0x08, 0x00);
        /**********‘℃’图标**********/
        bit_Cal(7, 0x80, 0x80);
    }
        
    /**********实际温度小数点**********/
    bit_Cal(5, 0x01, 0x01);
    
    /**********设定温度小数点**********/
    bit_Cal(5, 0x80, 0x80);
    
//    /**********'SAFE'图标**********/
//    bit_Cal(1, 0x80, 0x80);
    
    /**********外部探头图标**********/
    if(PT_VALUE_1_TEMP < 2000)//假如插入外部探头
	{
        bit_Cal(7, 0x01, 0x01);
    }
	else
	{
		bit_Cal(7, 0x01, 0x00);//不显示外部探头的图标
	}
    
    /**********加热图标**********/
    bit_Cal(8, 0x02, 0x02);
    bit_Cal(3, 0x01, 0x01);//加热图标下面的横杠
    
//    /**********转速图标搅拌子**********/
//    bit_Cal(9, 0x01, 0x01);
    
//    /**********加热图标旁边的H**********/
//    bit_Cal(8, 0x04, 0x04);
    
//    /**********加热图标旁边的L**********/
//    bit_Cal(9, 0x02, 0x02);
    
//    /**********锁定图标**********/
//    bit_Cal(9, 0x04, 0x04);
    
    /**********转速图标S4**********/
    bit_Cal(10, 0x01, 0x01);
    
    /**********转速图标S3**********/
    bit_Cal(10, 0x02, 0x02);
    
    /**********转速图标S5**********/
    bit_Cal(12, 0x01, 0x01);
    
    /**********‘rpm’图标**********/
    bit_Cal(14, 0x80, 0x80);
    
//    /**********转速图标旁边的H**********/
//    bit_Cal(9, 0x08, 0x08);
    
//    /**********转速图标旁边的L**********/
//    bit_Cal(17, 0x01, 0x01);
    
    /**********L1**********/
    if(PMode.Light_BIT & BIT0)
    {
        bit_Cal(26, 0x10, 0x10);
    }
    else
    {
        bit_Cal(26, 0x10, 0x00);
    }
    
    /**********L2**********/
    if(PMode.Light_BIT & BIT1)
    {
        bit_Cal(23, 0x08, 0x08);
    }
    else
    {
        bit_Cal(23, 0x08, 0x00);
    }
    
    /**********L3**********/
    if(PMode.Light_BIT & BIT2)
    {
        bit_Cal(19, 0x08, 0x08);
    }
    else
    {
        bit_Cal(19, 0x08, 0x00);
    }
    
    /**********L4**********/
    if(PMode.Light_BIT & BIT3)
    {
        bit_Cal(19, 0x10, 0x10);
    }
    else
    {
        bit_Cal(19, 0x10, 0x00);
    }
    
    /**********L5**********/
    if(PMode.Light_BIT & BIT4)
    {
        bit_Cal(19, 0x20, 0x20);
    }
    else
    {
        bit_Cal(19, 0x20, 0x00);
    }
    
    /**********L6**********/
    if(PMode.Light_BIT & BIT5)
    {
        bit_Cal(19, 0x40, 0x40);
    }
    else
    {
        bit_Cal(19, 0x40, 0x00);
    }
    
    /**********L7**********/
    if(PMode.Light_BIT & BIT6)
    {
        bit_Cal(20, 0x80, 0x80);
    }
    else
    {
        bit_Cal(20, 0x80, 0x00);
    }
    
    /**********L8**********/
    if(PMode.Light_BIT & BIT7)
    {
        bit_Cal(22, 0x80, 0x80);
    }
    else
    {
        bit_Cal(22, 0x80, 0x00);
    }
    
    /**********L9**********/
    if(PMode.Light_BIT & BIT8)
    {
        bit_Cal(24, 0x80, 0x80);
    }
    else
    {
        bit_Cal(24, 0x80, 0x00);
    }
    
    /**********L10**********/
    if(PMode.Light_BIT & BIT9)
    {
        bit_Cal(26, 0x80, 0x80);
    }
    else
    {
        bit_Cal(26, 0x80, 0x00);
    }
    
    /**********L11**********/
    if(PMode.Light_BIT & BIT10)
    {
        bit_Cal(26, 0x40, 0x40);
    }
    else
    {
        bit_Cal(26, 0x40, 0x00);
    }
    
    /**********L12**********/
    if(PMode.Light_BIT & BIT11)
    {
        bit_Cal(26, 0x20, 0x20);
    }
    else
    {
        bit_Cal(26, 0x20, 0x00);
    }
    
    /**********‘P’**********/
    if (PMode.Status) // 进入PMode
    {
        if (!PMode.Mode) // 在P模式下
        {
            if (!Pmode_ShowFlag)
            {
                bit_Cal(25, 0xF0, 0x70);bit_Cal(24, 0x70, 0x30);//P
                /**********‘-’**********/
                bit_Cal(23, 0xF0, 0x00);bit_Cal(22, 0x70, 0x20);
                switch (PMode.Option)
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
            }
            else
            {
                bit_Cal(25, 0xF0, 0x00);bit_Cal(24, 0x70, 0x00);//不显示
                bit_Cal(23, 0xF0, 0x00);bit_Cal(22, 0x70, 0x00);//不显示
                bit_Cal(21, 0xF0, 0x00);bit_Cal(20, 0x70, 0x00);//不显示
            }
        }
        else// 梯度模式下
        {
            if (!PModeP1_ShowFlag)
            {
                switch (PMode.P1)
                {
                    case 0:
                        bit_Cal(25, 0xF0, 0xF0);bit_Cal(24, 0x70, 0x50);
                        break;
                    case 1:
                        bit_Cal(25, 0xF0, 0x00);bit_Cal(24, 0x70, 0x50);
                        break;
                    case 2:
                        bit_Cal(25, 0xF0, 0xD0);bit_Cal(24, 0x70, 0x30);
                        break;
                    case 3:
                        bit_Cal(25, 0xF0, 0x90);bit_Cal(24, 0x70, 0x70);
                        break;
                    case 4:
                        bit_Cal(25, 0xF0, 0x20);bit_Cal(24, 0x70, 0x70);
                        break;
                    case 5:
                        bit_Cal(25, 0xF0, 0xB0);bit_Cal(24, 0x70, 0x60);
                        break;
                    case 6:
                        bit_Cal(25, 0xF0, 0xF0);bit_Cal(24, 0x70, 0x60);
                        break;
                    case 7:
                        bit_Cal(25, 0xF0, 0x10);bit_Cal(24, 0x70, 0x50);
                        break;
                    case 8:
                        bit_Cal(25, 0xF0, 0xF0);bit_Cal(24, 0x70, 0x70);
                        break;
                    case 9:
                        bit_Cal(25, 0xF0, 0xB0);bit_Cal(24, 0x70, 0x70);
                        break;
                    default:
                        bit_Cal(25, 0xF0, 0x70);bit_Cal(24, 0x70, 0x30);//P
                        break;
                }
            }
            else
            {
                bit_Cal(25, 0xF0, 0x00);bit_Cal(24, 0x70, 0x00);//不显示
            }
            
            /**********‘-’**********/
            bit_Cal(23, 0xF0, 0x00);bit_Cal(22, 0x70, 0x20);
            
            if (!PModeP2_ShowFlag)
            {
                switch (PMode.P2)
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
            }
            else
            {
                bit_Cal(21, 0xF0, 0x00);bit_Cal(20, 0x70, 0x00);//不显示
            }
        }
    }
    else // 不进入P模式不显示
    {
        bit_Cal(25, 0xF0, 0x00);bit_Cal(24, 0x70, 0x00);//不显示
        bit_Cal(23, 0xF0, 0x00);bit_Cal(22, 0x70, 0x00);//不显示
        bit_Cal(21, 0xF0, 0x00);bit_Cal(20, 0x70, 0x00);//不显示
    }
    
	/**********数据发送**********/
    for(uint8_t i=0;i<27;i++)
    {
        Write_Addr_Dat_N(i*2, seg[i], 1);
    }
}

/**
 * @brief 速度显示处理
 * 
 */
void Deal_Speed(float dT)
{
	if(sys.Run_Status)
	{
		if(Speed.Ctrl)
		{
			if(Speed.ADDMode==0)//在电机控制中，速度未处理
			{ 
				if(Speed.Ctrl >= Speed.Display_Rel)//控制速度大于实际速度
				{
					Speed.ADDMode = 1;//进入加速模式下
				}
				else if(Speed.Ctrl < Speed.Display_Rel)//控制速度小于实际速度
				{
					Speed.ADDMode = 2;//进入减速模式下
				}
			}
			if(Speed.ADDMode==1)//在进入加速模式下
			{
				Speed.New = Speed.Rel;//记录当前速度
				if(Speed.New > Speed.Display_Rel)//当前速度大于显示速度
				{
					if(Speed.Display_Rel < Speed.New)
						Speed.Display_Rel+=1;//显示当前速度
				}
				else//当前速度小于上一次速度
				{
					Speed.Display_Rel = Speed.Display_Rel;//显示上一次速度，不让速度小于当前速度。呈现攀升速度的现象
				}  
				if(sys.Motor_Stop == 0)
				{
					if(Speed.Display_Rel >= Speed.Ctrl)//实际速度大于等于控制速度
					{
						Speed.ADDMode = 3;//进入稳定模式
						return;
					}
				}
			}
			if(Speed.ADDMode == 2)//速度下降模式下
			{
				Speed.New = Speed.Rel;//记录当前速度
				
				if(Speed.New < Speed.Display_Rel)//当前速度小于上一次速度
				{
					if(Speed.Display_Rel > Speed.New)
						Speed.Display_Rel -=1;//显示当前速度
				}
				else//当前速度大于上一次速度
				{
					Speed.Display_Rel = Speed.Display_Rel;//显示上一次速度，不让速度大于当前速度。呈现下降速度的现象
				}
				if(sys.Motor_Stop == 0)
				{
					if(Speed.Display_Rel <= Speed.Ctrl)//实际速度小于等于控制速度
					{
						Speed.ADDMode = 3;//进入稳定模式
						return;
					}
				}
			}
			else if(Speed.ADDMode == 3)//速度稳定模式下
			{
				Speed.Display_Rel = Speed.Ctrl;//显示控制速度
			}
		}
		else
		{
			if(Speed.Display_Rel)
				Speed.Display_Rel -=1;//显示当前速度
			else
				Speed.Display_Rel =0;//显示当前速度为0
		}
	}
	else
	{
		Speed.Display_Rel = 0;//实际速度显示为零
		Speed.New =0;//现在的速度清零
		Speed.ADDMode = 0;//清除显示处理
	}
}

/**
 * @brief 显示屏幕内容
 * 
 */
void Show_Display(void)
{
    Time.Display = Time.Set;
    Speed.Display_Set = Speed.Set;
    Temp.Display_Rel = Temp.Rel;
    Temp.Display_Set = Temp.Set;
    Display();
}
