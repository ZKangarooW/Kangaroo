#include "Show.h"

/**********全局变量**********/
float Twinkle_Time; // 闪烁时间

/**********局部变量声明*******/
uint8_t Speed_ShowFlag, Temp_ShowFlag, Time_ShowFlag;//速度、温度、时间显示的标志位，0：常亮，1：熄灭

/*
*****************************************************************
 * 函数原型：static void Icn_Twinkle(float dT)
 * 功    能：图标闪烁
 * 调    用：内部调用
*****************************************************************
*/
static void Icn_Twinkle(float dT)
{
	static float T[Motor_Num];
    for(uint8_t i = 0; i<Motor_Num; i++)
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
                
                if(Work_Num[i].Temp.Set)
                    Work_Num[i].Temp.Icon = ~Work_Num[i].Temp.Icon;//温度图标闪烁;
                else
                    Work_Num[i].Temp.Icon = 0;
                
                if(Work_Num[i].Time.Rel && (!Work_Num[i].Temp.Ctrl || Work_Num[i].Temp.Icon != Work_Num[i].Time.Icon) && (Work_Num[i].Temp.Set == 0 || Work_Num[i].Temp.ADDMode == 3))
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
            Work_Num[i].Temp.Icon = 0;//不显示温度图标
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
        Temp_ShowFlag = 0;//常亮
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
                Temp_ShowFlag = 0;//温度常亮
                Time_ShowFlag = 0;//时间常亮
            }
            else if(sys.SetMode_Option == 1)//设置速度
            {
                Speed_ShowFlag = ~Speed_ShowFlag;//速度闪烁
                Temp_ShowFlag = 0;//温度常亮
                Time_ShowFlag = 0;//时间常亮
            }
            else if(sys.SetMode_Option == 2)//设置温度
            {
                Speed_ShowFlag = 0;//速度常亮
                Temp_ShowFlag = ~Temp_ShowFlag;//温度闪烁
                Time_ShowFlag = 0;//时间常亮
            }
            else if(sys.SetMode_Option == 3)//设置时间
            {
                Speed_ShowFlag = 0;//速度常亮
                Temp_ShowFlag = 0;//温度常亮
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

/**
 * @brief 显示函数
 *
 * @param work_num[] 工位结构体
 */
void Display(_Work_Num_ work_num[])
{
    uint8_t Val;// 用于百十个取出来的数字
    /*******************************1号工位*******************************/
    /**********工位1的实际转速显示**********/
    if (work_num[0].Speed.Display_Rel > 999) // 大于999时
    {
        Val = work_num[0].Speed.Display_Rel / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(56, 0x06, 0x04);//显示数字1
        }
        else
        {
            bit_Cal(56, 0x06, 0x06);//显示数字0
        }
    }
    else
    {
        bit_Cal(56, 0x06, 0x06);//显示数字0
    }
	
	if (work_num[0].Speed.Display_Rel > 99) // 大于99时
	{
		Val = work_num[0].Speed.Display_Rel / 100 % 10;
		ShowDigit(Work_1_RelSpeed_2,Val);
	}
	else
	{
		ShowDigit(Work_1_RelSpeed_2,Dispaly_0);
	}
	
	if (work_num[0].Speed.Display_Rel > 9) // 大于9时
	{
		Val = work_num[0].Speed.Display_Rel / 10 % 10;
		ShowDigit(Work_1_RelSpeed_3,Val);
	}
	else
	{
		ShowDigit(Work_1_RelSpeed_3,Dispaly_0);
	}
    bit_Cal(48, 0x01, 0x01);//实际转速个位只能显示零

    /**********工位1的设定转速显示**********/
    if(Speed_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 0)//不显示设定转速
    {
        bit_Cal(46, 0x01, 0x00);bit_Cal(48, 0x02, 0x00);//第一位不显示
        ShowDigit(Work_1_SetSpeed_2,Dispaly_OFF);//第二位不显示
        ShowDigit(Work_1_SetSpeed_3,Dispaly_OFF);//第三位不显示
        bit_Cal(42, 0x01, 0x00);//第四位不显示
    }
    else
    {
        if(work_num[0].Speed.Display_Set == 0)//显示“ -- ”
        {
            bit_Cal(46, 0x01, 0x00);bit_Cal(48, 0x02, 0x00);//不显示
            ShowDigit(Work_1_SetSpeed_2,Dispaly__);//显示“-”
            ShowDigit(Work_1_SetSpeed_3,Dispaly__);//显示“-”
            bit_Cal(42, 0x01, 0x00);//不显示
        }
        else
        {
            if(work_num[0].Speed.Display_Set > 999) // 大于999时
            {
                Val = work_num[0].Speed.Display_Set / 1000 % 10;
                if(Val > 0)
                {
                    bit_Cal(46, 0x01, 0x01);bit_Cal(48, 0x02, 0x00);//显示数字1
                }
                else
                {
                    bit_Cal(46, 0x01, 0x01);bit_Cal(48, 0x02, 0x02);//显示数字0
                }
            }
            else
            {
                bit_Cal(46, 0x01, 0x01);bit_Cal(48, 0x02, 0x02);//显示数字0
            }
            
           if (work_num[0].Speed.Display_Set > 99) // 大于99时
            {
                Val = work_num[0].Speed.Display_Set / 100 % 10;
                ShowDigit(Work_1_SetSpeed_2,Val);
            }
            else
            {
                ShowDigit(Work_1_SetSpeed_2,Dispaly_0);//显示数字零
            }

           if (work_num[0].Speed.Display_Set > 9) // 大于9时
            {
                Val = work_num[0].Speed.Display_Set / 10 % 10;
                ShowDigit(Work_1_SetSpeed_3,Val);
            }
            else
            {
                ShowDigit(Work_1_SetSpeed_3,Dispaly_0);//显示数字零
            }
            bit_Cal(42, 0x01, 0x01);//实际转速个位只能显示零
        }
    }

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
        Val = Dispaly__;//显示“-”
    }
    ShowDigit(Work_1_RelTemp_1,Val);

    if (work_num[0].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[0].Temp.Display_Rel / 100 % 10;
    }
    else if (work_num[0].Temp.Display_Rel < 0 && work_num[0].Temp.Display_Rel > -100)
    {
        Val = Dispaly__;//显示“-”
    }
    else if (work_num[0].Temp.Display_Rel <= -100 && work_num[0].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[0].Temp.Display_Rel)/ 100 % 10;
    }
    ShowDigit(Work_1_RelTemp_2,Val);

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
    ShowDigit(Work_1_RelTemp_3,Val);

    if (work_num[0].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[0].Temp.Display_Rel % 10;
    }
    else if (work_num[0].Temp.Display_Rel < 0 && work_num[0].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[0].Temp.Display_Rel) % 10;
    }
    else if (work_num[0].Temp.Display_Rel <= -100 && work_num[0].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[0].Temp.Display_Rel) % 10;
    }
    ShowDigit(Work_1_RelTemp_4,Val);

    /* 1号工位实际温度小数点 */
    bit_Cal(53, 0x01, 0x01);

    /**********工位1的设定温度显示**********/
    if(Temp_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 0)//不显示设定转速
    {
        ShowDigit(Work_1_SetTemp_1,Dispaly_OFF);//第一位不显示
        ShowDigit(Work_1_SetTemp_2,Dispaly_OFF);//第二位不显示
        ShowDigit(Work_1_SetTemp_3,Dispaly_OFF);//第三位不显示
        ShowDigit(Work_1_SetTemp_4,Dispaly_OFF);//第四位不显示
    }
    else
    {
        if (work_num[0].Temp.Display_Set > 0)//大于0时
        {
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
                Val = Dispaly__;//显示“-”
            }
            ShowDigit(Work_1_SetTemp_1,Val);

            if (work_num[0].Temp.Display_Set >= 0)//大于等于0时
            {
                Val = work_num[0].Temp.Display_Set / 100 % 10;
            }
            else if (work_num[0].Temp.Display_Set < 0 && work_num[0].Temp.Display_Set > -100)
            {
                Val = Dispaly__;//显示“-”
            }
            else if (work_num[0].Temp.Display_Set <= -100 && work_num[0].Temp.Display_Set > -1000)
            {
                Val = ABS(work_num[0].Temp.Display_Set)/ 100 % 10;
            }
            ShowDigit(Work_1_SetTemp_2,Val);

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
            ShowDigit(Work_1_SetTemp_3,Val);

            if (work_num[0].Temp.Display_Set >= 0)//大于等于0时
            {
                Val = work_num[0].Temp.Display_Set % 10;
            }
            else if (work_num[0].Temp.Display_Set < 0 && work_num[0].Temp.Display_Set > -100)
            {
                Val = ABS(work_num[0].Temp.Display_Set) % 10;
            }
            else if (work_num[0].Temp.Display_Set <= -100 && work_num[0].Temp.Display_Set > -1000)
            {
                Val = ABS(work_num[0].Temp.Display_Set) % 10;
            }
            ShowDigit(Work_1_SetTemp_4,Val);
        }
        else
        {
            ShowDigit(Work_1_SetTemp_1,Dispaly__);//显示“-”
            ShowDigit(Work_1_SetTemp_2,Dispaly__);//显示“-”
            ShowDigit(Work_1_SetTemp_3,Dispaly__);//显示“-”
            ShowDigit(Work_1_SetTemp_4,Dispaly__);//显示“-”
        }
    }
    /* 1号工位设定温度小数点 */
    bit_Cal(43, 0x04, 0x04);

    /**********工位1的实际时间显示**********/
    if(work_num[0].Time.Ctrl == 0)
    {
        ShowDigit(Work_1_RelTime_1,Dispaly__);//显示“-”
        ShowDigit(Work_1_RelTime_2,Dispaly__);//显示“-”
        ShowDigit(Work_1_RelTime_3,Dispaly__);//显示“-”
        ShowDigit(Work_1_RelTime_4,Dispaly__);//显示“-”
    }
    else
    {
        Val = work_num[0].Time.Display_Rel / 3600 / 10;//计算十位为单位的小时数
        ShowDigit(Work_1_RelTime_1,Val);

        Val = work_num[0].Time.Display_Rel / 3600 % 10;// 计算个位为单位的小时数
        ShowDigit(Work_1_RelTime_2,Val);

        Val = work_num[0].Time.Display_Rel % 3600 / 60 / 10; // 计算十分位为单位的分钟数
        ShowDigit(Work_1_RelTime_3,Val);

        Val = work_num[0].Time.Display_Rel % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
        ShowDigit(Work_1_RelTime_4,Val);
    }
    /* 1号工位实际时间冒号 */
    bit_Cal(55, 0x04, 0x04);

    /**********工位1的设定时间显示**********/
    if(Time_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 0)//不显示设定转速
    {
        ShowDigit(Work_1_SetTime_1,Dispaly_OFF);//第一位不显示
        ShowDigit(Work_1_SetTime_2,Dispaly_OFF);//第二位不显示
        ShowDigit(Work_1_SetTime_3,Dispaly_OFF);//第三位不显示
        ShowDigit(Work_1_SetTime_4,Dispaly_OFF);//第四位不显示
    }
    else
    {
        if(work_num[0].Time.Set == 0)
        {
            ShowDigit(Work_1_SetTime_1,Dispaly__);//显示“-”
            ShowDigit(Work_1_SetTime_2,Dispaly__);//显示“-”
            ShowDigit(Work_1_SetTime_3,Dispaly__);//显示“-”
            ShowDigit(Work_1_SetTime_4,Dispaly__);//显示“-”
        }
        else
        {
            Val = work_num[0].Time.Display_Set / 3600 / 10;//计算十位为单位的小时数
            ShowDigit(Work_1_SetTime_1,Val);

            Val = work_num[0].Time.Display_Set / 3600 % 10;// 计算个位为单位的小时数
            ShowDigit(Work_1_SetTime_2,Val);

            Val = work_num[0].Time.Display_Set % 3600 / 60 / 10; // 计算十分位为单位的分钟数
            ShowDigit(Work_1_SetTime_3,Val);

            Val = work_num[0].Time.Display_Set % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
            ShowDigit(Work_1_SetTime_4,Val);
        }
    }
    /* 1号工位设定时间冒号 */
    bit_Cal(45, 0x20, 0x20);

    /* 1号工位“rpm”图标 */
    bit_Cal(40, 0x01, 0x01);
    
    /* 1号工位“℃”图标 */
    bit_Cal(40, 0x02, 0x02);

    /* 1号工位“min”图标 */
    bit_Cal(41, 0x40, 0x40);

    /* 1号工位的横线 */
    if(sys.New_Work == 0)
    {
        bit_Cal(41, 0x80, 0x80);
    }
    else//不在当前工位常量
        bit_Cal(41, 0x80, 0x00);

    /* 1号工位转速图标 */
    switch(Work_Num[0].Speed.IconStep)
	{
		case 0: bit_Cal(58, 0x01, 0x01);//1号工位转速图标S1
                bit_Cal(58, 0x02, 0x02);//1号工位转速图标S2
                bit_Cal(56, 0x01, 0x01);//1号工位转速图标S3
			break;
		case 1: bit_Cal(58, 0x01, 0x00);//1号工位转速图标1
                bit_Cal(58, 0x02, 0x02);//1号工位转速图标2
                bit_Cal(56, 0x01, 0x01);//1号工位转速图标3
			break;
		case 2: bit_Cal(58, 0x01, 0x01);//1号工位转速图标1
                bit_Cal(58, 0x02, 0x00);//1号工位转速图标2
                bit_Cal(56, 0x01, 0x01);//1号工位转速图标3
			break;
		case 3: bit_Cal(58, 0x01, 0x01);//1号工位转速图标1
                bit_Cal(58, 0x02, 0x02);//1号工位转速图标2
                bit_Cal(56, 0x01, 0x00);//1号工位转速图标3
			break;
		default:
			break;
	}
    
    /* 1号工位加热图标 */
    if(Work_Num[0].Temp.Icon == 0)
    {
        bit_Cal(58, 0x04, 0x04);//1号工位加热图标
    }
    else
    {
        bit_Cal(58, 0x04, 0x00);//1号工位加热图标
    }
    
    if(PT_VALUE_1_TEMP[0] < 2200)//外部探头
    {
        bit_Cal(58, 0x08, 0x08);//1号工位温度探头图标
    }
    else
    {
        bit_Cal(58, 0x08, 0x00);//不显示1号工位温度探头图标
    }
    
    /* 1号工位时间图标 */
    if(Work_Num[0].Time.Icon == 0)
    {
        bit_Cal(59, 0x80, 0x80);//1号工位时间图标
    }
    else
    {
        bit_Cal(59, 0x80, 0x00);//1号工位时间图标
    }

    /*******************************2号工位*******************************/
    /**********工位2的实际转速显示**********/
    if (work_num[1].Speed.Display_Rel > 999) // 大于999时
    {
        Val = work_num[1].Speed.Display_Rel / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(36, 0x06, 0x04);//显示数字1
        }
        else
        {
            bit_Cal(36, 0x06, 0x06);//显示数字0
        }
    }
    else
    {
        bit_Cal(36, 0x06, 0x06);//显示数字0
    }
	
	if (work_num[1].Speed.Display_Rel > 99) // 大于99时
	{
		Val = work_num[1].Speed.Display_Rel / 100 % 10;
		ShowDigit(Work_2_RelSpeed_2,Val);
	}
	else
	{
		ShowDigit(Work_2_RelSpeed_2,Dispaly_0);
	}
	
	if (work_num[1].Speed.Display_Rel > 9) // 大于9时
	{
		Val = work_num[1].Speed.Display_Rel / 10 % 10;
		ShowDigit(Work_2_RelSpeed_3,Val);
	}
	else
	{
		ShowDigit(Work_2_RelSpeed_3,Dispaly_0);
	}
    bit_Cal(28, 0x01, 0x01);//实际转速个位只能显示零

    /**********工位2的设定转速显示**********/
    if(Speed_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 1)//不显示设定转速
    {
        bit_Cal(26, 0x01, 0x00);bit_Cal(28, 0x02, 0x00);//第一位不显示
        ShowDigit(Work_2_SetSpeed_2,Dispaly_OFF);//第二位不显示
        ShowDigit(Work_2_SetSpeed_3,Dispaly_OFF);//第三位不显示
        bit_Cal(22, 0x01, 0x00);//第四位不显示
    }
    else
    {
        if(work_num[1].Speed.Display_Set == 0)//显示“ -- ”
        {
            bit_Cal(26, 0x01, 0x00);bit_Cal(28, 0x02, 0x00);//不显示
            ShowDigit(Work_2_SetSpeed_2,Dispaly__);//显示“-”
            ShowDigit(Work_2_SetSpeed_3,Dispaly__);//显示“-”
            bit_Cal(22, 0x01, 0x00);//不显示
        }
        else
        {
            if(work_num[1].Speed.Display_Set > 999) // 大于999时
            {
                Val = work_num[1].Speed.Display_Set / 1000 % 10;
                if(Val > 0)
                {
                    bit_Cal(26, 0x01, 0x01);bit_Cal(28, 0x02, 0x00);//显示数字1
                }
                else
                {
                    bit_Cal(26, 0x01, 0x01);bit_Cal(28, 0x02, 0x02);//显示数字0
                }
            }
            else
            {
                bit_Cal(26, 0x01, 0x01);bit_Cal(28, 0x02, 0x02);//显示数字0
            }
            
           if (work_num[1].Speed.Display_Set > 99) // 大于99时
            {
                Val = work_num[1].Speed.Display_Set / 100 % 10;
                ShowDigit(Work_2_SetSpeed_2,Val);
            }
            else
            {
                ShowDigit(Work_2_SetSpeed_2,Dispaly_0);//显示数字零
            }

           if (work_num[1].Speed.Display_Set > 9) // 大于9时
            {
                Val = work_num[1].Speed.Display_Set / 10 % 10;
                ShowDigit(Work_2_SetSpeed_3,Val);
            }
            else
            {
                ShowDigit(Work_2_SetSpeed_3,Dispaly_0);//显示数字零
            }
            bit_Cal(22, 0x01, 0x01);//实际转速个位只能显示零
        }
    }

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
        Val = Dispaly__;//显示“-”
    }
    ShowDigit(Work_2_RelTemp_1,Val);

    if (work_num[1].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[1].Temp.Display_Rel / 100 % 10;
    }
    else if (work_num[1].Temp.Display_Rel < 0 && work_num[1].Temp.Display_Rel > -100)
    {
        Val = Dispaly__;//显示“-”
    }
    else if (work_num[1].Temp.Display_Rel <= -100 && work_num[1].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[1].Temp.Display_Rel)/ 100 % 10;
    }
    ShowDigit(Work_2_RelTemp_2,Val);

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
    ShowDigit(Work_2_RelTemp_3,Val);

    if (work_num[1].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[1].Temp.Display_Rel % 10;
    }
    else if (work_num[1].Temp.Display_Rel < 0 && work_num[1].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[1].Temp.Display_Rel) % 10;
    }
    else if (work_num[1].Temp.Display_Rel <= -100 && work_num[1].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[1].Temp.Display_Rel) % 10;
    }
    ShowDigit(Work_2_RelTemp_4,Val);

    /* 2号工位实际温度小数点 */
    bit_Cal(33, 0x01, 0x01);

    /**********工位2的设定温度显示**********/
    if(Temp_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 1)//不显示设定转速
    {
        ShowDigit(Work_2_SetTemp_1,Dispaly_OFF);//第一位不显示
        ShowDigit(Work_2_SetTemp_2,Dispaly_OFF);//第二位不显示
        ShowDigit(Work_2_SetTemp_3,Dispaly_OFF);//第三位不显示
        ShowDigit(Work_2_SetTemp_4,Dispaly_OFF);//第四位不显示
    }
    else
    {
        if (work_num[1].Temp.Display_Set > 0)//大于0时
        {
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
                Val = Dispaly__;//显示“-”
            }
            ShowDigit(Work_2_SetTemp_1,Val);

            if (work_num[1].Temp.Display_Set >= 0)//大于等于0时
            {
                Val = work_num[1].Temp.Display_Set / 100 % 10;
            }
            else if (work_num[1].Temp.Display_Set < 0 && work_num[1].Temp.Display_Set > -100)
            {
                Val = Dispaly__;//显示“-”
            }
            else if (work_num[1].Temp.Display_Set <= -100 && work_num[1].Temp.Display_Set > -1000)
            {
                Val = ABS(work_num[1].Temp.Display_Set)/ 100 % 10;
            }
            ShowDigit(Work_2_SetTemp_2,Val);

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
            ShowDigit(Work_2_SetTemp_3,Val);

            if (work_num[1].Temp.Display_Set >= 0)//大于等于0时
            {
                Val = work_num[1].Temp.Display_Set % 10;
            }
            else if (work_num[1].Temp.Display_Set < 0 && work_num[1].Temp.Display_Set > -100)
            {
                Val = ABS(work_num[1].Temp.Display_Set) % 10;
            }
            else if (work_num[1].Temp.Display_Set <= -100 && work_num[1].Temp.Display_Set > -1000)
            {
                Val = ABS(work_num[1].Temp.Display_Set) % 10;
            }
            ShowDigit(Work_2_SetTemp_4,Val);
        }
        else
        {
            ShowDigit(Work_2_SetTemp_1,Dispaly__);//显示“-”
            ShowDigit(Work_2_SetTemp_2,Dispaly__);//显示“-”
            ShowDigit(Work_2_SetTemp_3,Dispaly__);//显示“-”
            ShowDigit(Work_2_SetTemp_4,Dispaly__);//显示“-”
        }
    }
    /* 2号工位设定温度小数点 */
    bit_Cal(23, 0x04, 0x04);

    /**********工位2的实际时间显示**********/
    if(work_num[1].Time.Ctrl == 0)
    {
        ShowDigit(Work_2_RelTime_1,Dispaly__);//显示“-”
        ShowDigit(Work_2_RelTime_2,Dispaly__);//显示“-”
        ShowDigit(Work_2_RelTime_3,Dispaly__);//显示“-”
        ShowDigit(Work_2_RelTime_4,Dispaly__);//显示“-”
    }
    else
    {
        Val = work_num[1].Time.Display_Rel / 3600 / 10;//计算十位为单位的小时数
        ShowDigit(Work_2_RelTime_1,Val);

        Val = work_num[1].Time.Display_Rel / 3600 % 10;// 计算个位为单位的小时数
        ShowDigit(Work_2_RelTime_2,Val);

        Val = work_num[1].Time.Display_Rel % 3600 / 60 / 10; // 计算十分位为单位的分钟数
        ShowDigit(Work_2_RelTime_3,Val);

        Val = work_num[1].Time.Display_Rel % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
        ShowDigit(Work_2_RelTime_4,Val);
    }
    /* 2号工位实际时间冒号 */
    bit_Cal(35, 0x04, 0x04);

    /**********工位2的设定时间显示**********/
    if(Time_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 1)//不显示设定转速
    {
        ShowDigit(Work_2_SetTime_1,Dispaly_OFF);//第一位不显示
        ShowDigit(Work_2_SetTime_2,Dispaly_OFF);//第二位不显示
        ShowDigit(Work_2_SetTime_3,Dispaly_OFF);//第三位不显示
        ShowDigit(Work_2_SetTime_4,Dispaly_OFF);//第四位不显示
    }
    else
    {
        if(work_num[1].Time.Set == 0)
        {
            ShowDigit(Work_2_SetTime_1,Dispaly__);//显示“-”
            ShowDigit(Work_2_SetTime_2,Dispaly__);//显示“-”
            ShowDigit(Work_2_SetTime_3,Dispaly__);//显示“-”
            ShowDigit(Work_2_SetTime_4,Dispaly__);//显示“-”
        }
        else
        {
            Val = work_num[1].Time.Display_Set / 3600 / 10;//计算十位为单位的小时数
            ShowDigit(Work_2_SetTime_1,Val);

            Val = work_num[1].Time.Display_Set / 3600 % 10;// 计算个位为单位的小时数
            ShowDigit(Work_2_SetTime_2,Val);

            Val = work_num[1].Time.Display_Set % 3600 / 60 / 10; // 计算十分位为单位的分钟数
            ShowDigit(Work_2_SetTime_3,Val);

            Val = work_num[1].Time.Display_Set % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
            ShowDigit(Work_2_SetTime_4,Val);
        }
    }
    /* 2号工位设定时间冒号 */
    bit_Cal(25, 0x20, 0x20);

    /* 2号工位“rpm”图标 */
    bit_Cal(20, 0x01, 0x01);
    
    /* 2号工位“℃”图标 */
    bit_Cal(20, 0x02, 0x02);

    /* 2号工位“min”图标 */
    bit_Cal(21, 0x40, 0x40);

    /* 2号工位的横线 */
    if(sys.New_Work == 1)
    {
        bit_Cal(21, 0x80, 0x80);
    }
    else//不在当前工位常量
        bit_Cal(21, 0x80, 0x00);

    /* 2号工位转速图标 */
    switch(Work_Num[1].Speed.IconStep)
	{
		case 0: bit_Cal(38, 0x01, 0x01);//2号工位转速图标S1
                bit_Cal(38, 0x02, 0x02);//2号工位转速图标S2
                bit_Cal(36, 0x01, 0x01);//2号工位转速图标S3
			break;
		case 1: bit_Cal(38, 0x01, 0x00);//2号工位转速图标1
                bit_Cal(38, 0x02, 0x02);//2号工位转速图标2
                bit_Cal(36, 0x01, 0x01);//2号工位转速图标3
			break;
		case 2: bit_Cal(38, 0x01, 0x01);//2号工位转速图标1
                bit_Cal(38, 0x02, 0x00);//2号工位转速图标2
                bit_Cal(36, 0x01, 0x01);//2号工位转速图标3
			break;
		case 3: bit_Cal(38, 0x01, 0x01);//2号工位转速图标1
                bit_Cal(38, 0x02, 0x02);//2号工位转速图标2
                bit_Cal(36, 0x01, 0x00);//2号工位转速图标3
			break;
		default:
			break;
	}
    
    /* 2号工位加热图标 */
    if(Work_Num[1].Temp.Icon == 0)
    {
        bit_Cal(38, 0x04, 0x04);//2号工位加热图标
    }
    else
    {
        bit_Cal(38, 0x04, 0x00);//2号工位加热图标
    }
    
    if(PT_VALUE_1_TEMP[1] < 2200)//外部探头
    {
        bit_Cal(38, 0x08, 0x08);//2号工位温度探头图标
    }
    else
    {
        bit_Cal(38, 0x08, 0x00);//不显示2号工位温度探头图标
    }
    
    /* 2号工位时间图标 */
    if(Work_Num[1].Time.Icon == 0)
    {
        bit_Cal(39, 0x80, 0x80);//2号工位时间图标
    }
    else
    {
        bit_Cal(39, 0x80, 0x00);//2号工位时间图标
    }

    /*******************************3号工位*******************************/
    /**********工位3的实际转速显示**********/
    if (work_num[2].Speed.Display_Rel > 999) // 大于999时
    {
        Val = work_num[2].Speed.Display_Rel / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(77, 0x60, 0x20);//显示数字1
        }
        else
        {
            bit_Cal(77, 0x60, 0x60);//显示数字0
        }
    }
    else
    {
        bit_Cal(77, 0x60, 0x60);//显示数字0
    }
	
	if (work_num[2].Speed.Display_Rel > 99) // 大于99时
	{
		Val = work_num[2].Speed.Display_Rel / 100 % 10;
		ShowDigit(Work_3_RelSpeed_2,Val);
	}
	else
	{
		ShowDigit(Work_3_RelSpeed_2,Dispaly_0);
	}
	
	if (work_num[2].Speed.Display_Rel > 9) // 大于9时
	{
		Val = work_num[2].Speed.Display_Rel / 10 % 10;
		ShowDigit(Work_3_RelSpeed_3,Val);
	}
	else
	{
		ShowDigit(Work_3_RelSpeed_3,Dispaly_0);
	}
    bit_Cal(69, 0x80, 0x80);//实际转速个位只能显示零

    /**********工位3的设定转速显示**********/
    if(Speed_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 2)//不显示设定转速
    {
        bit_Cal(67, 0x80, 0x00);bit_Cal(69, 0x40, 0x00);//第一位不显示
        ShowDigit(Work_3_SetSpeed_2,Dispaly_OFF);//第二位不显示
        ShowDigit(Work_3_SetSpeed_3,Dispaly_OFF);//第三位不显示
        bit_Cal(63, 0x80, 0x00);//第四位不显示
    }
    else
    {
        if(work_num[2].Speed.Display_Set == 0)//显示“ -- ”
        {
            bit_Cal(67, 0x80, 0x00);bit_Cal(69, 0x40, 0x00);//不显示
            ShowDigit(Work_3_SetSpeed_2,Dispaly__);//显示“-”
            ShowDigit(Work_3_SetSpeed_3,Dispaly__);//显示“-”
            bit_Cal(63, 0x80, 0x00);//不显示
        }
        else
        {
            if(work_num[2].Speed.Display_Set > 999) // 大于999时
            {
                Val = work_num[2].Speed.Display_Set / 1000 % 10;
                if(Val > 0)
                {
                    bit_Cal(67, 0x80, 0x80);bit_Cal(69, 0x40, 0x00);//显示数字1
                }
                else
                {
                    bit_Cal(67, 0x80, 0x80);bit_Cal(69, 0x40, 0x40);//显示数字0
                }
            }
            else
            {
                bit_Cal(67, 0x80, 0x80);bit_Cal(69, 0x40, 0x40);//显示数字0
            }
            
           if (work_num[2].Speed.Display_Set > 99) // 大于99时
            {
                Val = work_num[2].Speed.Display_Set / 100 % 10;
                ShowDigit(Work_3_SetSpeed_2,Val);
            }
            else
            {
                ShowDigit(Work_3_SetSpeed_2,Dispaly_0);//显示数字零
            }

           if (work_num[2].Speed.Display_Set > 9) // 大于9时
            {
                Val = work_num[2].Speed.Display_Set / 10 % 10;
                ShowDigit(Work_3_SetSpeed_3,Val);
            }
            else
            {
                ShowDigit(Work_3_SetSpeed_3,Dispaly_0);//显示数字零
            }
            bit_Cal(63, 0x80, 0x80);//实际转速个位只能显示零
        }
    }

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
        Val = Dispaly__;//显示“-”
    }
    ShowDigit(Work_3_RelTemp_1,Val);

    if (work_num[2].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[2].Temp.Display_Rel / 100 % 10;
    }
    else if (work_num[2].Temp.Display_Rel < 0 && work_num[2].Temp.Display_Rel > -100)
    {
        Val = Dispaly__;//显示“-”
    }
    else if (work_num[2].Temp.Display_Rel <= -100 && work_num[2].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[2].Temp.Display_Rel)/ 100 % 10;
    }
    ShowDigit(Work_3_RelTemp_2,Val);

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
    ShowDigit(Work_3_RelTemp_3,Val);

    if (work_num[2].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[2].Temp.Display_Rel % 10;
    }
    else if (work_num[2].Temp.Display_Rel < 0 && work_num[2].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[2].Temp.Display_Rel) % 10;
    }
    else if (work_num[2].Temp.Display_Rel <= -100 && work_num[2].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[2].Temp.Display_Rel) % 10;
    }
    ShowDigit(Work_3_RelTemp_4,Val);

    /* 3号工位实际温度小数点 */
    bit_Cal(72, 0x80, 0x80);

    /**********工位3的设定温度显示**********/
    if(Temp_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 2)//不显示设定转速
    {
        ShowDigit(Work_3_SetTemp_1,Dispaly_OFF);//第一位不显示
        ShowDigit(Work_3_SetTemp_2,Dispaly_OFF);//第二位不显示
        ShowDigit(Work_3_SetTemp_3,Dispaly_OFF);//第三位不显示
        ShowDigit(Work_3_SetTemp_4,Dispaly_OFF);//第四位不显示
    }
    else
    {
        if (work_num[2].Temp.Display_Set > 0)//大于0时
        {
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
                Val = Dispaly__;//显示“-”
            }
            ShowDigit(Work_3_SetTemp_1,Val);

            if (work_num[2].Temp.Display_Set >= 0)//大于等于0时
            {
                Val = work_num[2].Temp.Display_Set / 100 % 10;
            }
            else if (work_num[2].Temp.Display_Set < 0 && work_num[2].Temp.Display_Set > -100)
            {
                Val = Dispaly__;//显示“-”
            }
            else if (work_num[2].Temp.Display_Set <= -100 && work_num[2].Temp.Display_Set > -1000)
            {
                Val = ABS(work_num[2].Temp.Display_Set)/ 100 % 10;
            }
            ShowDigit(Work_3_SetTemp_2,Val);

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
            ShowDigit(Work_3_SetTemp_3,Val);

            if (work_num[2].Temp.Display_Set >= 0)//大于等于0时
            {
                Val = work_num[2].Temp.Display_Set % 10;
            }
            else if (work_num[2].Temp.Display_Set < 0 && work_num[2].Temp.Display_Set > -100)
            {
                Val = ABS(work_num[2].Temp.Display_Set) % 10;
            }
            else if (work_num[2].Temp.Display_Set <= -100 && work_num[2].Temp.Display_Set > -1000)
            {
                Val = ABS(work_num[2].Temp.Display_Set) % 10;
            }
            ShowDigit(Work_3_SetTemp_4,Val);
        }
        else
        {
            ShowDigit(Work_3_SetTemp_1,Dispaly__);//显示“-”
            ShowDigit(Work_3_SetTemp_2,Dispaly__);//显示“-”
            ShowDigit(Work_3_SetTemp_3,Dispaly__);//显示“-”
            ShowDigit(Work_3_SetTemp_4,Dispaly__);//显示“-”
        }
    }
    /* 3号工位设定温度小数点 */
    bit_Cal(62, 0x20, 0x20);

    /**********工位3的实际时间显示**********/
    if(work_num[2].Time.Ctrl == 0)
    {
        ShowDigit(Work_3_RelTime_1,Dispaly__);//显示“-”
        ShowDigit(Work_3_RelTime_2,Dispaly__);//显示“-”
        ShowDigit(Work_3_RelTime_3,Dispaly__);//显示“-”
        ShowDigit(Work_3_RelTime_4,Dispaly__);//显示“-”
    }
    else
    {
        Val = work_num[2].Time.Display_Rel / 3600 / 10;//计算十位为单位的小时数
        ShowDigit(Work_3_RelTime_1,Val);

        Val = work_num[2].Time.Display_Rel / 3600 % 10;// 计算个位为单位的小时数
        ShowDigit(Work_3_RelTime_2,Val);

        Val = work_num[2].Time.Display_Rel % 3600 / 60 / 10; // 计算十分位为单位的分钟数
        ShowDigit(Work_3_RelTime_3,Val);

        Val = work_num[2].Time.Display_Rel % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
        ShowDigit(Work_3_RelTime_4,Val);
    }
    /* 3号工位实际时间冒号 */
    bit_Cal(74, 0x20, 0x20);

    /**********工位3的设定时间显示**********/
    if(Time_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 2)//不显示设定转速
    {
        ShowDigit(Work_3_SetTime_1,Dispaly_OFF);//第一位不显示
        ShowDigit(Work_3_SetTime_2,Dispaly_OFF);//第二位不显示
        ShowDigit(Work_3_SetTime_3,Dispaly_OFF);//第三位不显示
        ShowDigit(Work_3_SetTime_4,Dispaly_OFF);//第四位不显示
    }
    else
    {
        if(work_num[2].Time.Set == 0)
        {
            ShowDigit(Work_3_SetTime_1,Dispaly__);//显示“-”
            ShowDigit(Work_3_SetTime_2,Dispaly__);//显示“-”
            ShowDigit(Work_3_SetTime_3,Dispaly__);//显示“-”
            ShowDigit(Work_3_SetTime_4,Dispaly__);//显示“-”
        }
        else
        {
            Val = work_num[2].Time.Display_Set / 3600 / 10;//计算十位为单位的小时数
            ShowDigit(Work_3_SetTime_1,Val);

            Val = work_num[2].Time.Display_Set / 3600 % 10;// 计算个位为单位的小时数
            ShowDigit(Work_3_SetTime_2,Val);

            Val = work_num[2].Time.Display_Set % 3600 / 60 / 10; // 计算十分位为单位的分钟数
            ShowDigit(Work_3_SetTime_3,Val);

            Val = work_num[2].Time.Display_Set % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
            ShowDigit(Work_3_SetTime_4,Val);
        }
    }
    /* 3号工位设定时间冒号 */
    bit_Cal(64, 0x04, 0x04);

    /* 3号工位“rpm”图标 */
    bit_Cal(61, 0x80, 0x80);
    
    /* 3号工位“℃”图标 */
    bit_Cal(61, 0x40, 0x40);

    /* 3号工位“min”图标 */
    bit_Cal(60, 0x02, 0x02);

    /* 3号工位的横线 */
    if(sys.New_Work == 2)
    {
        bit_Cal(60, 0x01, 0x01);
    }
    else//不在当前工位常量
        bit_Cal(60, 0x01, 0x00);

    /* 3号工位转速图标 */
    switch(work_num[2].Speed.IconStep)
	{
		case 0: bit_Cal(79, 0x80, 0x80);//3号工位转速图标S1
                bit_Cal(79, 0x40, 0x40);//3号工位转速图标S2
                bit_Cal(77, 0x80, 0x80);//3号工位转速图标S3
			break;
		case 1: bit_Cal(79, 0x80, 0x00);//3号工位转速图标1
                bit_Cal(79, 0x40, 0x40);//3号工位转速图标2
                bit_Cal(77, 0x80, 0x80);//3号工位转速图标3
			break;
		case 2: bit_Cal(79, 0x80, 0x80);//3号工位转速图标1
                bit_Cal(79, 0x40, 0x00);//3号工位转速图标2
                bit_Cal(77, 0x80, 0x80);//3号工位转速图标3
			break;
		case 3: bit_Cal(79, 0x80, 0x80);//3号工位转速图标1
                bit_Cal(79, 0x40, 0x40);//3号工位转速图标2
                bit_Cal(77, 0x80, 0x00);//3号工位转速图标3
			break;
		default:
			break;
	}
    
    /* 3号工位加热图标 */
    if(work_num[2].Temp.Icon == 0)
    {
        bit_Cal(79, 0x20, 0x20);//3号工位加热图标
    }
    else
    {
        bit_Cal(79, 0x20, 0x00);//3号工位加热图标
    }
    
    if(PT_VALUE_1_TEMP[2] < 2200)//外部探头
    {
        bit_Cal(79, 0x10, 0x10);//3号工位温度探头图标
    }
    else
    {
        bit_Cal(79, 0x10, 0x00);//不显示3号工位温度探头图标
    }
    
    /* 3号工位时间图标 */
    if(work_num[2].Time.Icon == 0)
    {
        bit_Cal(78, 0x01, 0x01);//3号工位时间图标
    }
    else
    {
        bit_Cal(78, 0x01, 0x00);//3号工位时间图标
    }

    /*******************************4号工位*******************************/
    /**********工位4的实际转速显示**********/
    if (work_num[3].Speed.Display_Rel > 999) // 大于999时
    {
        Val = work_num[3].Speed.Display_Rel / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(3, 0x60, 0x20);//显示数字1
        }
        else
        {
            bit_Cal(3, 0x60, 0x60);//显示数字0
        }
    }
    else
    {
        bit_Cal(3, 0x60, 0x60);//显示数字0
    }
	
	if (work_num[3].Speed.Display_Rel > 99) // 大于99时
	{
		Val = work_num[3].Speed.Display_Rel / 100 % 10;
		ShowDigit(Work_4_RelSpeed_2,Val);
	}
	else
	{
		ShowDigit(Work_4_RelSpeed_2,Dispaly_0);
	}
	
	if (work_num[3].Speed.Display_Rel > 9) // 大于9时
	{
		Val = work_num[3].Speed.Display_Rel / 10 % 10;
		ShowDigit(Work_4_RelSpeed_3,Val);
	}
	else
	{
		ShowDigit(Work_4_RelSpeed_3,Dispaly_0);
	}
    bit_Cal(11, 0x80, 0x80);//实际转速个位只能显示零

    /**********工位4的设定转速显示**********/
    if(Speed_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 3)//不显示设定转速
    {
        bit_Cal(13, 0x80, 0x00);bit_Cal(11, 0x40, 0x00);//第一位不显示
        ShowDigit(Work_4_SetSpeed_2,Dispaly_OFF);//第二位不显示
        ShowDigit(Work_4_SetSpeed_3,Dispaly_OFF);//第三位不显示
        bit_Cal(17, 0x80, 0x00);//第四位不显示
    }
    else
    {
        if(work_num[3].Speed.Display_Set == 0)//显示“ -- ”
        {
            bit_Cal(13, 0x80, 0x00);bit_Cal(11, 0x40, 0x00);//不显示
            ShowDigit(Work_4_SetSpeed_2,Dispaly__);//显示“-”
            ShowDigit(Work_4_SetSpeed_3,Dispaly__);//显示“-”
            bit_Cal(17, 0x80, 0x00);//不显示
        }
        else
        {
            if(work_num[3].Speed.Display_Set > 999) // 大于999时
            {
                Val = work_num[3].Speed.Display_Set / 1000 % 10;
                if(Val > 0)
                {
                    bit_Cal(13, 0x80, 0x80);bit_Cal(11, 0x40, 0x00);//显示数字1
                }
                else
                {
                    bit_Cal(13, 0x80, 0x80);bit_Cal(11, 0x40, 0x40);//显示数字0
                }
            }
            else
            {
                bit_Cal(13, 0x80, 0x80);bit_Cal(11, 0x40, 0x40);//显示数字0
            }
            
           if (work_num[3].Speed.Display_Set > 99) // 大于99时
            {
                Val = work_num[3].Speed.Display_Set / 100 % 10;
                ShowDigit(Work_4_SetSpeed_2,Val);
            }
            else
            {
                ShowDigit(Work_4_SetSpeed_2,Dispaly_0);//显示数字零
            }

           if (work_num[3].Speed.Display_Set > 9) // 大于9时
            {
                Val = work_num[3].Speed.Display_Set / 10 % 10;
                ShowDigit(Work_4_SetSpeed_3,Val);
            }
            else
            {
                ShowDigit(Work_4_SetSpeed_3,Dispaly_0);//显示数字零
            }
            bit_Cal(17, 0x80, 0x80);//实际转速个位只能显示零
        }
    }

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
        Val = Dispaly__;//显示“-”
    }
    ShowDigit(Work_4_RelTemp_1,Val);

    if (work_num[3].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[3].Temp.Display_Rel / 100 % 10;
    }
    else if (work_num[3].Temp.Display_Rel < 0 && work_num[3].Temp.Display_Rel > -100)
    {
        Val = Dispaly__;//显示“-”
    }
    else if (work_num[3].Temp.Display_Rel <= -100 && work_num[3].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[3].Temp.Display_Rel)/ 100 % 10;
    }
    ShowDigit(Work_4_RelTemp_2,Val);

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
    ShowDigit(Work_4_RelTemp_3,Val);

    if (work_num[3].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[3].Temp.Display_Rel % 10;
    }
    else if (work_num[3].Temp.Display_Rel < 0 && work_num[3].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[3].Temp.Display_Rel) % 10;
    }
    else if (work_num[3].Temp.Display_Rel <= -100 && work_num[3].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[3].Temp.Display_Rel) % 10;
    }
    ShowDigit(Work_4_RelTemp_4,Val);

    /* 4号工位实际温度小数点 */
    bit_Cal(6, 0x80, 0x80);

    /**********工位4的设定温度显示**********/
    if(Temp_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 3)//不显示设定转速
    {
        ShowDigit(Work_4_SetTemp_1,Dispaly_OFF);//第一位不显示
        ShowDigit(Work_4_SetTemp_2,Dispaly_OFF);//第二位不显示
        ShowDigit(Work_4_SetTemp_3,Dispaly_OFF);//第三位不显示
        ShowDigit(Work_4_SetTemp_4,Dispaly_OFF);//第四位不显示
    }
    else
    {
        if (work_num[3].Temp.Display_Set > 0)//大于0时
        {
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
                Val = Dispaly__;//显示“-”
            }
            ShowDigit(Work_4_SetTemp_1,Val);

            if (work_num[3].Temp.Display_Set >= 0)//大于等于0时
            {
                Val = work_num[3].Temp.Display_Set / 100 % 10;
            }
            else if (work_num[3].Temp.Display_Set < 0 && work_num[3].Temp.Display_Set > -100)
            {
                Val = Dispaly__;//显示“-”
            }
            else if (work_num[3].Temp.Display_Set <= -100 && work_num[3].Temp.Display_Set > -1000)
            {
                Val = ABS(work_num[3].Temp.Display_Set)/ 100 % 10;
            }
            ShowDigit(Work_4_SetTemp_2,Val);

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
            ShowDigit(Work_4_SetTemp_3,Val);

            if (work_num[3].Temp.Display_Set >= 0)//大于等于0时
            {
                Val = work_num[3].Temp.Display_Set % 10;
            }
            else if (work_num[3].Temp.Display_Set < 0 && work_num[3].Temp.Display_Set > -100)
            {
                Val = ABS(work_num[3].Temp.Display_Set) % 10;
            }
            else if (work_num[3].Temp.Display_Set <= -100 && work_num[3].Temp.Display_Set > -1000)
            {
                Val = ABS(work_num[3].Temp.Display_Set) % 10;
            }
            ShowDigit(Work_4_SetTemp_4,Val);
        }
        else
        {
            ShowDigit(Work_4_SetTemp_1,Dispaly__);//显示“-”
            ShowDigit(Work_4_SetTemp_2,Dispaly__);//显示“-”
            ShowDigit(Work_4_SetTemp_3,Dispaly__);//显示“-”
            ShowDigit(Work_4_SetTemp_4,Dispaly__);//显示“-”
        }
    }
    /* 4号工位设定温度小数点 */
    bit_Cal(16, 0x20, 0x20);

    /**********工位4的实际时间显示**********/
    if(work_num[3].Time.Ctrl == 0)
    {
        ShowDigit(Work_4_RelTime_1,Dispaly__);//显示“-”
        ShowDigit(Work_4_RelTime_2,Dispaly__);//显示“-”
        ShowDigit(Work_4_RelTime_3,Dispaly__);//显示“-”
        ShowDigit(Work_4_RelTime_4,Dispaly__);//显示“-”
    }
    else
    {
        Val = work_num[3].Time.Display_Rel / 3600 / 10;//计算十位为单位的小时数
        ShowDigit(Work_4_RelTime_1,Val);

        Val = work_num[3].Time.Display_Rel / 3600 % 10;// 计算个位为单位的小时数
        ShowDigit(Work_4_RelTime_2,Val);

        Val = work_num[3].Time.Display_Rel % 3600 / 60 / 10; // 计算十分位为单位的分钟数
        ShowDigit(Work_4_RelTime_3,Val);

        Val = work_num[3].Time.Display_Rel % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
        ShowDigit(Work_4_RelTime_4,Val);
    }
    /* 4号工位实际时间冒号 */
    bit_Cal(4, 0x20, 0x20);

    /**********工位4的设定时间显示**********/
    if(Time_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 3)//不显示设定转速
    {
        ShowDigit(Work_4_SetTime_1,Dispaly_OFF);//第一位不显示
        ShowDigit(Work_4_SetTime_2,Dispaly_OFF);//第二位不显示
        ShowDigit(Work_4_SetTime_3,Dispaly_OFF);//第三位不显示
        ShowDigit(Work_4_SetTime_4,Dispaly_OFF);//第四位不显示
    }
    else
    {
        if(work_num[3].Time.Set == 0)
        {
            ShowDigit(Work_4_SetTime_1,Dispaly__);//显示“-”
            ShowDigit(Work_4_SetTime_2,Dispaly__);//显示“-”
            ShowDigit(Work_4_SetTime_3,Dispaly__);//显示“-”
            ShowDigit(Work_4_SetTime_4,Dispaly__);//显示“-”
        }
        else
        {
            Val = work_num[3].Time.Display_Set / 3600 / 10;//计算十位为单位的小时数
            ShowDigit(Work_4_SetTime_1,Val);

            Val = work_num[3].Time.Display_Set / 3600 % 10;// 计算个位为单位的小时数
            ShowDigit(Work_4_SetTime_2,Val);

            Val = work_num[3].Time.Display_Set % 3600 / 60 / 10; // 计算十分位为单位的分钟数
            ShowDigit(Work_4_SetTime_3,Val);

            Val = work_num[3].Time.Display_Set % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
            ShowDigit(Work_4_SetTime_4,Val);
        }
    }
    /* 4号工位设定时间冒号 */
    bit_Cal(14, 0x04, 0x04);

    /* 4号工位“rpm”图标 */
    bit_Cal(19, 0x80, 0x80);
    
    /* 4号工位“℃”图标 */
    bit_Cal(19, 0x40, 0x40);

    /* 4号工位“min”图标 */
    bit_Cal(18, 0x02, 0x02);

    /* 4号工位的横线 */
    if(sys.New_Work == 3)
    {
        bit_Cal(18, 0x01, 0x01);
    }
    else//不在当前工位常量
        bit_Cal(18, 0x01, 0x00);

    /* 4号工位转速图标 */
    switch(work_num[3].Speed.IconStep)
	{
		case 0: bit_Cal(1, 0x80, 0x80);//4号工位转速图标S1
                bit_Cal(1, 0x40, 0x40);//4号工位转速图标S2
                bit_Cal(3, 0x80, 0x80);//4号工位转速图标S3
			break;
		case 1: bit_Cal(1, 0x80, 0x00);//4号工位转速图标1
                bit_Cal(1, 0x40, 0x40);//4号工位转速图标2
                bit_Cal(3, 0x80, 0x80);//4号工位转速图标3
			break;
		case 2: bit_Cal(1, 0x80, 0x80);//4号工位转速图标1
                bit_Cal(1, 0x40, 0x00);//4号工位转速图标2
                bit_Cal(3, 0x80, 0x80);//4号工位转速图标3
			break;
		case 3: bit_Cal(1, 0x80, 0x80);//4号工位转速图标1
                bit_Cal(1, 0x40, 0x40);//4号工位转速图标2
                bit_Cal(3, 0x80, 0x00);//4号工位转速图标3
			break;
		default:
			break;
	}
    
    /* 4号工位加热图标 */
    if(work_num[3].Temp.Icon == 0)
    {
        bit_Cal(1, 0x20, 0x20);//4号工位加热图标
    }
    else
    {
        bit_Cal(1, 0x20, 0x00);//4号工位加热图标
    }
    
    if(PT_VALUE_1_TEMP[3] < 2200)//外部探头
    {
        bit_Cal(1, 0x10, 0x10);//4号工位温度探头图标
    }
    else
    {
        bit_Cal(1, 0x10, 0x00);//不显示4号工位温度探头图标
    }
    
    /* 4号工位时间图标 */
    if(work_num[3].Time.Icon == 0)
    {
        bit_Cal(0, 0x01, 0x01);//4号工位时间图标
    }
    else
    {
        bit_Cal(0, 0x01, 0x00);//4号工位时间图标
    }

    /*******************************5号工位*******************************/
    /**********工位5的实际转速显示**********/
    if (work_num[4].Speed.Display_Rel > 999) // 大于999时
    {
        Val = work_num[4].Speed.Display_Rel / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(82, 0x06, 0x04);//显示数字1
        }
        else
        {
            bit_Cal(82, 0x06, 0x06);//显示数字0
        }
    }
    else
    {
        bit_Cal(82, 0x06, 0x06);//显示数字0
    }
	
	if (work_num[4].Speed.Display_Rel > 99) // 大于99时
	{
		Val = work_num[4].Speed.Display_Rel / 100 % 10;
		ShowDigit(Work_5_RelSpeed_2,Val);
	}
	else
	{
		ShowDigit(Work_5_RelSpeed_2,Dispaly_0);
	}
	
	if (work_num[4].Speed.Display_Rel > 9) // 大于9时
	{
		Val = work_num[4].Speed.Display_Rel / 10 % 10;
		ShowDigit(Work_5_RelSpeed_3,Val);
	}
	else
	{
		ShowDigit(Work_5_RelSpeed_3,Dispaly_0);
	}
    bit_Cal(90, 0x01, 0x01);//实际转速个位只能显示零

    /**********工位5的设定转速显示**********/
    if(Speed_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 4)//不显示设定转速
    {
        bit_Cal(90, 0x02, 0x00);bit_Cal(92, 0x01, 0x00);//第一位不显示
        ShowDigit(Work_5_SetSpeed_2,Dispaly_OFF);//第二位不显示
        ShowDigit(Work_5_SetSpeed_3,Dispaly_OFF);//第三位不显示
        bit_Cal(96, 0x01, 0x00);//第四位不显示
    }
    else
    {
        if(work_num[4].Speed.Display_Set == 0)//显示“ -- ”
        {
            bit_Cal(90, 0x02, 0x00);bit_Cal(92, 0x01, 0x00);//不显示
            ShowDigit(Work_5_SetSpeed_2,Dispaly__);//显示“-”
            ShowDigit(Work_5_SetSpeed_3,Dispaly__);//显示“-”
            bit_Cal(96, 0x01, 0x00);//不显示
        }
        else
        {
            if(work_num[4].Speed.Display_Set > 999) // 大于999时
            {
                Val = work_num[4].Speed.Display_Set / 1000 % 10;
                if(Val > 0)
                {
                    bit_Cal(90, 0x02, 0x00);bit_Cal(92, 0x01, 0x01);//显示数字1
                }
                else
                {
                    bit_Cal(90, 0x02, 0x02);bit_Cal(92, 0x01, 0x01);//显示数字0
                }
            }
            else
            {
                bit_Cal(90, 0x02, 0x02);bit_Cal(92, 0x01, 0x01);//显示数字0
            }
            
           if(work_num[4].Speed.Display_Set > 99) // 大于99时
            {
                Val = work_num[4].Speed.Display_Set / 100 % 10;
                ShowDigit(Work_5_SetSpeed_2,Val);
            }
            else
            {
                ShowDigit(Work_5_SetSpeed_2,Dispaly_0);//显示数字零
            }

           if (work_num[4].Speed.Display_Set > 9) // 大于9时
            {
                Val = work_num[4].Speed.Display_Set / 10 % 10;
                ShowDigit(Work_5_SetSpeed_3,Val);
            }
            else
            {
                ShowDigit(Work_5_SetSpeed_3,Dispaly_0);//显示数字零
            }
            bit_Cal(96, 0x01, 0x01);//实际转速个位只能显示零
        }
    }

    /**********工位5的实际温度显示**********/
    if (work_num[4].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[4].Temp.Display_Rel / 1000 % 10;
    }
    else if (work_num[4].Temp.Display_Rel < 0 && work_num[4].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[4].Temp.Display_Rel) / 1000 % 10;//计算后是0，不大于999所以不会显示
    }
    else if (work_num[4].Temp.Display_Rel <= -100 && work_num[4].Temp.Display_Rel > -1000)
    {
        Val = Dispaly__;//显示“-”
    }
    ShowDigit(Work_5_RelTemp_1,Val);

    if (work_num[4].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[4].Temp.Display_Rel / 100 % 10;
    }
    else if (work_num[4].Temp.Display_Rel < 0 && work_num[4].Temp.Display_Rel > -100)
    {
        Val = Dispaly__;//显示“-”
    }
    else if (work_num[4].Temp.Display_Rel <= -100 && work_num[4].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[4].Temp.Display_Rel)/ 100 % 10;
    }
    ShowDigit(Work_5_RelTemp_2,Val);

    if (work_num[4].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[4].Temp.Display_Rel / 10 % 10;
    }
    else if (work_num[4].Temp.Display_Rel < 0 && work_num[4].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[4].Temp.Display_Rel) / 10 % 10;
    }
    else if (work_num[4].Temp.Display_Rel <= -100 && work_num[4].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[4].Temp.Display_Rel) / 10 % 10;
    }
    ShowDigit(Work_5_RelTemp_3,Val);

    if (work_num[4].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[4].Temp.Display_Rel % 10;
    }
    else if (work_num[4].Temp.Display_Rel < 0 && work_num[4].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[4].Temp.Display_Rel) % 10;
    }
    else if (work_num[4].Temp.Display_Rel <= -100 && work_num[4].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[4].Temp.Display_Rel) % 10;
    }
    ShowDigit(Work_5_RelTemp_4,Val);

    /* 5号工位实际温度小数点 */
    bit_Cal(87, 0x01, 0x01);

    /**********工位5的设定温度显示**********/
    if(Temp_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 4)//不显示设定转速
    {
        ShowDigit(Work_5_SetTemp_1,Dispaly_OFF);//第一位不显示
        ShowDigit(Work_5_SetTemp_2,Dispaly_OFF);//第二位不显示
        ShowDigit(Work_5_SetTemp_3,Dispaly_OFF);//第三位不显示
        ShowDigit(Work_5_SetTemp_4,Dispaly_OFF);//第四位不显示
    }
    else
    {
        if (work_num[4].Temp.Display_Set > 0)//大于0时
        {
            if (work_num[4].Temp.Display_Set >= 0)//大于等于0时
            {
                Val = work_num[4].Temp.Display_Set / 1000 % 10;
            }
            else if (work_num[4].Temp.Display_Set < 0 && work_num[4].Temp.Display_Set > -100)
            {
                Val = ABS(work_num[4].Temp.Display_Set) / 1000 % 10;//计算后是0，不大于999所以不会显示
            }
            else if (work_num[4].Temp.Display_Set <= -100 && work_num[4].Temp.Display_Set > -1000)
            {
                Val = Dispaly__;//显示“-”
            }
            ShowDigit(Work_5_SetTemp_1,Val);

            if (work_num[4].Temp.Display_Set >= 0)//大于等于0时
            {
                Val = work_num[4].Temp.Display_Set / 100 % 10;
            }
            else if (work_num[4].Temp.Display_Set < 0 && work_num[4].Temp.Display_Set > -100)
            {
                Val = Dispaly__;//显示“-”
            }
            else if (work_num[4].Temp.Display_Set <= -100 && work_num[4].Temp.Display_Set > -1000)
            {
                Val = ABS(work_num[4].Temp.Display_Set)/ 100 % 10;
            }
            ShowDigit(Work_5_SetTemp_2,Val);

            if (work_num[4].Temp.Display_Set >= 0)//大于等于0时
            {
                Val = work_num[4].Temp.Display_Set / 10 % 10;
            }
            else if (work_num[4].Temp.Display_Set < 0 && work_num[4].Temp.Display_Set > -100)
            {
                Val = ABS(work_num[4].Temp.Display_Set) / 10 % 10;
            }
            else if (work_num[4].Temp.Display_Set <= -100 && work_num[4].Temp.Display_Set > -1000)
            {
                Val = ABS(work_num[4].Temp.Display_Set) / 10 % 10;
            }
            ShowDigit(Work_5_SetTemp_3,Val);

            if (work_num[4].Temp.Display_Set >= 0)//大于等于0时
            {
                Val = work_num[4].Temp.Display_Set % 10;
            }
            else if (work_num[4].Temp.Display_Set < 0 && work_num[4].Temp.Display_Set > -100)
            {
                Val = ABS(work_num[4].Temp.Display_Set) % 10;
            }
            else if (work_num[4].Temp.Display_Set <= -100 && work_num[4].Temp.Display_Set > -1000)
            {
                Val = ABS(work_num[4].Temp.Display_Set) % 10;
            }
            ShowDigit(Work_5_SetTemp_4,Val);
        }
        else
        {
            ShowDigit(Work_5_SetTemp_1,Dispaly__);//显示“-”
            ShowDigit(Work_5_SetTemp_2,Dispaly__);//显示“-”
            ShowDigit(Work_5_SetTemp_3,Dispaly__);//显示“-”
            ShowDigit(Work_5_SetTemp_4,Dispaly__);//显示“-”
        }
    }
    /* 5号工位设定温度小数点 */
    bit_Cal(97, 0x04, 0x04);

    /**********工位5的实际时间显示**********/
    if(work_num[4].Time.Ctrl == 0)
    {
        ShowDigit(Work_5_RelTime_1,Dispaly__);//显示“-”
        ShowDigit(Work_5_RelTime_2,Dispaly__);//显示“-”
        ShowDigit(Work_5_RelTime_3,Dispaly__);//显示“-”
        ShowDigit(Work_5_RelTime_4,Dispaly__);//显示“-”
    }
    else
    {
        Val = work_num[4].Time.Display_Rel / 3600 / 10;//计算十位为单位的小时数
        ShowDigit(Work_5_RelTime_1,Val);

        Val = work_num[4].Time.Display_Rel / 3600 % 10;// 计算个位为单位的小时数
        ShowDigit(Work_5_RelTime_2,Val);

        Val = work_num[4].Time.Display_Rel % 3600 / 60 / 10; // 计算十分位为单位的分钟数
        ShowDigit(Work_5_RelTime_3,Val);

        Val = work_num[4].Time.Display_Rel % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
        ShowDigit(Work_5_RelTime_4,Val);
    }
    /* 5号工位实际时间冒号 */
    bit_Cal(85, 0x04, 0x04);

    /**********工位5的设定时间显示**********/
    if(Time_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 4)//不显示设定转速
    {
        ShowDigit(Work_5_SetTime_1,Dispaly_OFF);//第一位不显示
        ShowDigit(Work_5_SetTime_2,Dispaly_OFF);//第二位不显示
        ShowDigit(Work_5_SetTime_3,Dispaly_OFF);//第三位不显示
        ShowDigit(Work_5_SetTime_4,Dispaly_OFF);//第四位不显示
    }
    else
    {
        if(work_num[4].Time.Set == 0)
        {
            ShowDigit(Work_5_SetTime_1,Dispaly__);//显示“-”
            ShowDigit(Work_5_SetTime_2,Dispaly__);//显示“-”
            ShowDigit(Work_5_SetTime_3,Dispaly__);//显示“-”
            ShowDigit(Work_5_SetTime_4,Dispaly__);//显示“-”
        }
        else
        {
            Val = work_num[4].Time.Display_Set / 3600 / 10;//计算十位为单位的小时数
            ShowDigit(Work_5_SetTime_1,Val);

            Val = work_num[4].Time.Display_Set / 3600 % 10;// 计算个位为单位的小时数
            ShowDigit(Work_5_SetTime_2,Val);

            Val = work_num[4].Time.Display_Set % 3600 / 60 / 10; // 计算十分位为单位的分钟数
            ShowDigit(Work_5_SetTime_3,Val);

            Val = work_num[4].Time.Display_Set % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
            ShowDigit(Work_5_SetTime_4,Val);
        }
    }
    /* 5号工位设定时间冒号 */
    bit_Cal(95, 0x20, 0x20);

    /* 5号工位“rpm”图标 */
    bit_Cal(98, 0x01, 0x01);
    
    /* 5号工位“℃”图标 */
    bit_Cal(98, 0x02, 0x02);

    /* 5号工位“min”图标 */
    bit_Cal(99, 0x40, 0x40);

    /* 5号工位的横线 */
    if(sys.New_Work == 4)
    {
        bit_Cal(99, 0x80, 0x80);
    }
    else//不在当前工位常量
        bit_Cal(99, 0x80, 0x00);

    /* 5号工位转速图标 */
    switch(work_num[4].Speed.IconStep)
	{
		case 0: bit_Cal(80, 0x01, 0x01);//5号工位转速图标S1
                bit_Cal(80, 0x02, 0x02);//5号工位转速图标S2
                bit_Cal(82, 0x01, 0x01);//5号工位转速图标S3
			break;
		case 1: bit_Cal(80, 0x01, 0x00);//5号工位转速图标1
                bit_Cal(80, 0x02, 0x02);//5号工位转速图标2
                bit_Cal(82, 0x01, 0x01);//5号工位转速图标3
			break;
		case 2: bit_Cal(80, 0x01, 0x01);//5号工位转速图标1
                bit_Cal(80, 0x02, 0x00);//5号工位转速图标2
                bit_Cal(82, 0x01, 0x01);//5号工位转速图标3
			break;
		case 3: bit_Cal(80, 0x01, 0x01);//5号工位转速图标1
                bit_Cal(80, 0x02, 0x02);//5号工位转速图标2
                bit_Cal(82, 0x01, 0x00);//5号工位转速图标3
			break;
		default:
			break;
	}
    
    /* 5号工位加热图标 */
    if(work_num[4].Temp.Icon == 0)
    {
        bit_Cal(80, 0x04, 0x04);//5号工位加热图标
    }
    else
    {
        bit_Cal(80, 0x04, 0x00);//5号工位加热图标
    }
    
    if(PT_VALUE_1_TEMP[4] < 2200)//外部探头
    {
        bit_Cal(80, 0x08, 0x08);//5号工位温度探头图标
    }
    else
    {
        bit_Cal(80, 0x08, 0x00);//不显示5号工位温度探头图标
    }
    
    /* 5号工位时间图标 */
    if(work_num[4].Time.Icon == 0)
    {
        bit_Cal(81, 0x80, 0x80);//5号工位时间图标
    }
    else
    {
        bit_Cal(81, 0x80, 0x00);//5号工位时间图标
    }

    /*******************************6号工位*******************************/
    /**********工位6的实际转速显示**********/
    if (work_num[5].Speed.Display_Rel > 999) // 大于999时
    {
        Val = work_num[5].Speed.Display_Rel / 1000 % 10;
        if(Val > 0)
        {
            bit_Cal(102, 0x06, 0x04);//显示数字1
        }
        else
        {
            bit_Cal(102, 0x06, 0x06);//显示数字0
        }
    }
    else
    {
        bit_Cal(102, 0x06, 0x06);//显示数字0
    }
	
	if (work_num[5].Speed.Display_Rel > 99) // 大于99时
	{
		Val = work_num[5].Speed.Display_Rel / 100 % 10;
		ShowDigit(Work_6_RelSpeed_2,Val);
	}
	else
	{
		ShowDigit(Work_6_RelSpeed_2,Dispaly_0);
	}
	
	if (work_num[5].Speed.Display_Rel > 9) // 大于9时
	{
		Val = work_num[5].Speed.Display_Rel / 10 % 10;
		ShowDigit(Work_6_RelSpeed_3,Val);
	}
	else
	{
		ShowDigit(Work_6_RelSpeed_3,Dispaly_0);
	}
    bit_Cal(110, 0x01, 0x01);//实际转速个位只能显示零

    /**********工位6的设定转速显示**********/
    if(Speed_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 5)//不显示设定转速
    {
        bit_Cal(110, 0x02, 0x00);bit_Cal(112, 0x01, 0x00);//第一位不显示
        ShowDigit(Work_6_SetSpeed_2,Dispaly_OFF);//第二位不显示
        ShowDigit(Work_6_SetSpeed_3,Dispaly_OFF);//第三位不显示
        bit_Cal(116, 0x01, 0x00);//第四位不显示
    }
    else
    {
        if(work_num[5].Speed.Display_Set == 0)//显示“ -- ”
        {
            bit_Cal(110, 0x02, 0x00);bit_Cal(112, 0x01, 0x00);//不显示
            ShowDigit(Work_6_SetSpeed_2,Dispaly__);//显示“-”
            ShowDigit(Work_6_SetSpeed_3,Dispaly__);//显示“-”
            bit_Cal(116, 0x01, 0x00);//不显示
        }
        else
        {
            if(work_num[5].Speed.Display_Set > 999) // 大于999时
            {
                Val = work_num[5].Speed.Display_Set / 1000 % 10;
                if(Val > 0)
                {
                    bit_Cal(110, 0x02, 0x00);bit_Cal(112, 0x01, 0x01);//显示数字1
                }
                else
                {
                    bit_Cal(110, 0x02, 0x02);bit_Cal(112, 0x01, 0x01);//显示数字0
                }
            }
            else
            {
                bit_Cal(110, 0x02, 0x02);bit_Cal(112, 0x01, 0x01);//显示数字0
            }
            
           if(work_num[5].Speed.Display_Set > 99) // 大于99时
            {
                Val = work_num[5].Speed.Display_Set / 100 % 10;
                ShowDigit(Work_6_SetSpeed_2,Val);
            }
            else
            {
                ShowDigit(Work_6_SetSpeed_2,Dispaly_0);//显示数字零
            }

           if (work_num[5].Speed.Display_Set > 9) // 大于9时
            {
                Val = work_num[5].Speed.Display_Set / 10 % 10;
                ShowDigit(Work_6_SetSpeed_3,Val);
            }
            else
            {
                ShowDigit(Work_6_SetSpeed_3,Dispaly_0);//显示数字零
            }
            bit_Cal(116, 0x01, 0x01);//实际转速个位只能显示零
        }
    }

    /**********工位6的实际温度显示**********/
    if (work_num[5].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[5].Temp.Display_Rel / 1000 % 10;
    }
    else if (work_num[5].Temp.Display_Rel < 0 && work_num[5].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[5].Temp.Display_Rel) / 1000 % 10;//计算后是0，不大于999所以不会显示
    }
    else if (work_num[5].Temp.Display_Rel <= -100 && work_num[5].Temp.Display_Rel > -1000)
    {
        Val = Dispaly__;//显示“-”
    }
    ShowDigit(Work_6_RelTemp_1,Val);

    if (work_num[5].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[5].Temp.Display_Rel / 100 % 10;
    }
    else if (work_num[5].Temp.Display_Rel < 0 && work_num[5].Temp.Display_Rel > -100)
    {
        Val = Dispaly__;//显示“-”
    }
    else if (work_num[5].Temp.Display_Rel <= -100 && work_num[5].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[5].Temp.Display_Rel)/ 100 % 10;
    }
    ShowDigit(Work_6_RelTemp_2,Val);

    if (work_num[5].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[5].Temp.Display_Rel / 10 % 10;
    }
    else if (work_num[5].Temp.Display_Rel < 0 && work_num[5].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[5].Temp.Display_Rel) / 10 % 10;
    }
    else if (work_num[5].Temp.Display_Rel <= -100 && work_num[5].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[5].Temp.Display_Rel) / 10 % 10;
    }
    ShowDigit(Work_6_RelTemp_3,Val);

    if (work_num[5].Temp.Display_Rel >= 0)//大于等于0时
    {
        Val = work_num[5].Temp.Display_Rel % 10;
    }
    else if (work_num[5].Temp.Display_Rel < 0 && work_num[5].Temp.Display_Rel > -100)
    {
        Val = ABS(work_num[5].Temp.Display_Rel) % 10;
    }
    else if (work_num[5].Temp.Display_Rel <= -100 && work_num[5].Temp.Display_Rel > -1000)
    {
        Val = ABS(work_num[5].Temp.Display_Rel) % 10;
    }
    ShowDigit(Work_6_RelTemp_4,Val);

    /* 6号工位实际温度小数点 */
    bit_Cal(107, 0x01, 0x01);

    /**********工位6的设定温度显示**********/
    if(Temp_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 5)//不显示设定转速
    {
        ShowDigit(Work_6_SetTemp_1,Dispaly_OFF);//第一位不显示
        ShowDigit(Work_6_SetTemp_2,Dispaly_OFF);//第二位不显示
        ShowDigit(Work_6_SetTemp_3,Dispaly_OFF);//第三位不显示
        ShowDigit(Work_6_SetTemp_4,Dispaly_OFF);//第四位不显示
    }
    else
    {
        if (work_num[5].Temp.Display_Set > 0)//大于0时
        {
            if (work_num[5].Temp.Display_Set >= 0)//大于等于0时
            {
                Val = work_num[5].Temp.Display_Set / 1000 % 10;
            }
            else if (work_num[5].Temp.Display_Set < 0 && work_num[5].Temp.Display_Set > -100)
            {
                Val = ABS(work_num[5].Temp.Display_Set) / 1000 % 10;//计算后是0，不大于999所以不会显示
            }
            else if (work_num[5].Temp.Display_Set <= -100 && work_num[5].Temp.Display_Set > -1000)
            {
                Val = Dispaly__;//显示“-”
            }
            ShowDigit(Work_6_SetTemp_1,Val);

            if (work_num[5].Temp.Display_Set >= 0)//大于等于0时
            {
                Val = work_num[5].Temp.Display_Set / 100 % 10;
            }
            else if (work_num[5].Temp.Display_Set < 0 && work_num[5].Temp.Display_Set > -100)
            {
                Val = Dispaly__;//显示“-”
            }
            else if (work_num[5].Temp.Display_Set <= -100 && work_num[5].Temp.Display_Set > -1000)
            {
                Val = ABS(work_num[5].Temp.Display_Set)/ 100 % 10;
            }
            ShowDigit(Work_6_SetTemp_2,Val);

            if (work_num[5].Temp.Display_Set >= 0)//大于等于0时
            {
                Val = work_num[5].Temp.Display_Set / 10 % 10;
            }
            else if (work_num[5].Temp.Display_Set < 0 && work_num[5].Temp.Display_Set > -100)
            {
                Val = ABS(work_num[5].Temp.Display_Set) / 10 % 10;
            }
            else if (work_num[5].Temp.Display_Set <= -100 && work_num[5].Temp.Display_Set > -1000)
            {
                Val = ABS(work_num[5].Temp.Display_Set) / 10 % 10;
            }
            ShowDigit(Work_6_SetTemp_3,Val);

            if (work_num[5].Temp.Display_Set >= 0)//大于等于0时
            {
                Val = work_num[5].Temp.Display_Set % 10;
            }
            else if (work_num[5].Temp.Display_Set < 0 && work_num[5].Temp.Display_Set > -100)
            {
                Val = ABS(work_num[5].Temp.Display_Set) % 10;
            }
            else if (work_num[5].Temp.Display_Set <= -100 && work_num[5].Temp.Display_Set > -1000)
            {
                Val = ABS(work_num[5].Temp.Display_Set) % 10;
            }
            ShowDigit(Work_6_SetTemp_4,Val);
        }
        else
        {
            ShowDigit(Work_6_SetTemp_1,Dispaly__);//显示“-”
            ShowDigit(Work_6_SetTemp_2,Dispaly__);//显示“-”
            ShowDigit(Work_6_SetTemp_3,Dispaly__);//显示“-”
            ShowDigit(Work_6_SetTemp_4,Dispaly__);//显示“-”
        }
    }
    /* 6号工位设定温度小数点 */
    bit_Cal(117, 0x04, 0x04);

    /**********工位6的实际时间显示**********/
    if(work_num[5].Time.Ctrl == 0)
    {
        ShowDigit(Work_6_RelTime_1,Dispaly__);//显示“-”
        ShowDigit(Work_6_RelTime_2,Dispaly__);//显示“-”
        ShowDigit(Work_6_RelTime_3,Dispaly__);//显示“-”
        ShowDigit(Work_6_RelTime_4,Dispaly__);//显示“-”
    }
    else
    {
        Val = work_num[5].Time.Display_Rel / 3600 / 10;//计算十位为单位的小时数
        ShowDigit(Work_6_RelTime_1,Val);

        Val = work_num[5].Time.Display_Rel / 3600 % 10;// 计算个位为单位的小时数
        ShowDigit(Work_6_RelTime_2,Val);

        Val = work_num[5].Time.Display_Rel % 3600 / 60 / 10; // 计算十分位为单位的分钟数
        ShowDigit(Work_6_RelTime_3,Val);

        Val = work_num[5].Time.Display_Rel % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
        ShowDigit(Work_6_RelTime_4,Val);
    }
    /* 6号工位实际时间冒号 */
    bit_Cal(105, 0x04, 0x04);

    /**********工位6的设定时间显示**********/
    if(Time_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 5)//不显示设定转速
    {
        ShowDigit(Work_6_SetTime_1,Dispaly_OFF);//第一位不显示
        ShowDigit(Work_6_SetTime_2,Dispaly_OFF);//第二位不显示
        ShowDigit(Work_6_SetTime_3,Dispaly_OFF);//第三位不显示
        ShowDigit(Work_6_SetTime_4,Dispaly_OFF);//第四位不显示
    }
    else
    {
        if(work_num[5].Time.Set == 0)
        {
            ShowDigit(Work_6_SetTime_1,Dispaly__);//显示“-”
            ShowDigit(Work_6_SetTime_2,Dispaly__);//显示“-”
            ShowDigit(Work_6_SetTime_3,Dispaly__);//显示“-”
            ShowDigit(Work_6_SetTime_4,Dispaly__);//显示“-”
        }
        else
        {
            Val = work_num[5].Time.Display_Set / 3600 / 10;//计算十位为单位的小时数
            ShowDigit(Work_6_SetTime_1,Val);

            Val = work_num[5].Time.Display_Set / 3600 % 10;// 计算个位为单位的小时数
            ShowDigit(Work_6_SetTime_2,Val);

            Val = work_num[5].Time.Display_Set % 3600 / 60 / 10; // 计算十分位为单位的分钟数
            ShowDigit(Work_6_SetTime_3,Val);

            Val = work_num[5].Time.Display_Set % 3600 / 60 % 10;	// 计算个分位为单位的分钟数
            ShowDigit(Work_6_SetTime_4,Val);
        }
    }
    /* 6号工位设定时间冒号 */
    bit_Cal(115, 0x20, 0x20);

    /* 6号工位“rpm”图标 */
    bit_Cal(118, 0x01, 0x01);
    
    /* 6号工位“℃”图标 */
    bit_Cal(118, 0x02, 0x02);

    /* 6号工位“min”图标 */
    bit_Cal(119, 0x40, 0x40);

    /* 6号工位的横线 */
    if(sys.New_Work == 5)
        bit_Cal(119, 0x80, 0x80);
    else//不在当前工位常量
        bit_Cal(119, 0x80, 0x00);

    /* 6号工位转速图标 */
    switch(work_num[5].Speed.IconStep)
	{
		case 0: bit_Cal(100, 0x01, 0x01);//6号工位转速图标S1
                bit_Cal(100, 0x02, 0x02);//6号工位转速图标S2
                bit_Cal(102, 0x01, 0x01);//6号工位转速图标S3
			break;
		case 1: bit_Cal(100, 0x01, 0x00);//6号工位转速图标1
                bit_Cal(100, 0x02, 0x02);//6号工位转速图标2
                bit_Cal(102, 0x01, 0x01);//6号工位转速图标3
			break;
		case 2: bit_Cal(100, 0x01, 0x01);//6号工位转速图标1
                bit_Cal(100, 0x02, 0x00);//6号工位转速图标2
                bit_Cal(102, 0x01, 0x01);//6号工位转速图标3
			break;
		case 3: bit_Cal(100, 0x01, 0x01);//6号工位转速图标1
                bit_Cal(100, 0x02, 0x02);//6号工位转速图标2
                bit_Cal(102, 0x01, 0x00);//6号工位转速图标3
			break;
		default:
			break;
	}
    
    /* 6号工位加热图标 */
    if(work_num[5].Temp.Icon == 0)
    {
        bit_Cal(100, 0x04, 0x04);//6号工位加热图标
    }
    else
    {
        bit_Cal(100, 0x04, 0x00);//6号工位加热图标
    }
    
    if(PT_VALUE_1_TEMP[5] < 2200)//外部探头
    {
        bit_Cal(100, 0x08, 0x08);//6号工位温度探头图标
    }
    else
    {
        bit_Cal(100, 0x08, 0x00);//不显示6号工位温度探头图标
    }
    
    /* 6号工位时间图标 */
    if(work_num[5].Time.Icon == 0)
    {
        bit_Cal(101, 0x80, 0x80);//6号工位时间图标
    }
    else
    {
        bit_Cal(101, 0x80, 0x00);//6号工位时间图标
    }
    HT16H25_RamUpdata(seg);
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

/*
*****************************************************************
 * 函数原型：void Deal_Temp(float dT)
 * 功    能：温度显示处理
*****************************************************************
*/
void Deal_Temp(float dT,uint8_t i)
{
    static float T[Motor_Num];
	uint8_t val;
	if(Work_Num[i].Run_Status && Work_Num[i].Temp.Ctrl)
	{
		if(PT_VALUE_1_TEMP[i] < 2200)//假如插入外部探头
			val = 40;
		else//假如没有插入外部探头
		{
			if(Work_Num[i].Temp.Ctrl < 2800)
				val = 100;
			else
				val = 140;
		}
		
		if(ABS(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Rel) < val)
		{
			if(Work_Num[i].Temp.ADDMode==0)//判断模式
			{ 
				if(Work_Num[i].Temp.Ctrl > Work_Num[i].Temp.Rel)
				{
					Work_Num[i].Temp.ADDMode = 1;//进入升温模式
					Work_Num[i].Temp.Last = Work_Num[i].Temp.Rel;
				}
				else if(Work_Num[i].Temp.Ctrl < Work_Num[i].Temp.Rel)
				{
					Work_Num[i].Temp.ADDMode = 2;//进入降温模式
					Work_Num[i].Temp.Last = Work_Num[i].Temp.Rel;//记录当前温度
				}
				else
				{
					Work_Num[i].Temp.ADDMode = 3;//进入稳定模式
				}
			}
			else if(Work_Num[i].Temp.ADDMode==1)//在进入升温模式下
			{ 
				Work_Num[i].Temp.New = Work_Num[i].Temp.Rel;//记录当前温度
				if(Work_Num[i].Temp.New > Work_Num[i].Temp.Last)//当前温度大于上一次温度
					Work_Num[i].Temp.Display_Rel = Work_Num[i].Temp.New;//显示当前温度
				else//当前温度小于上一次温度
				{
                    if(Work_Num[i].Temp.Ctrl == 1000)
                    {
                        if(Work_Num[i].Temp.Display_Rel == Work_Num[i].Temp.Last)
                        {
                            T[i] += dT;
                            if(T[i] > 10)
                            {
                                Work_Num[i].Temp.Display_Rel += 1;
                                Work_Num[i].Temp.Last = Work_Num[i].Temp.Display_Rel;
                                T[i] = 0;
                            }
                        }
                        else
                        {
                            T[i] = 0;
                        }
                    }
                    if(Work_Num[i].Temp.Ctrl - Work_Num[i].Temp.Display_Rel <= 20)//如果控制温度减去显示温度小于1摄氏度
                    {
                        T[i] += dT;
                        if(T[i] > 2.0f)
                        {
                            Work_Num[i].Temp.Display_Rel += 1;
                            Work_Num[i].Temp.Last = Work_Num[i].Temp.Display_Rel;
                            T[i] = 0;
                        }
                    }
					Work_Num[i].Temp.Display_Rel = Work_Num[i].Temp.Last;//显示上一次温度，不让温度小于当前温度。呈现攀升速度的现象
					Work_Num[i].Temp.New = Work_Num[i].Temp.Last;//将上一次温度赋值给当前温度
				}
                Work_Num[i].Temp.Last = Work_Num[i].Temp.New;//将当前温度保存                
				if(Work_Num[i].Temp.Display_Rel >= Work_Num[i].Temp.Ctrl)//当前的温度大于等于控制温度
				{
					Work_Num[i].Temp.ADDMode = 3;//进入稳定模式
				}
			}
            
			else if(Work_Num[i].Temp.ADDMode==2)//在进入降温模式下
			{ 
				Work_Num[i].Temp.New = Work_Num[i].Temp.Rel;//记录当前温度
				if(Work_Num[i].Temp.New < Work_Num[i].Temp.Last)//当前温度小于上一次温度
					Work_Num[i].Temp.Display_Rel = Work_Num[i].Temp.New;//显示当前温度
				else//当前温度大于上一次温度
				{
					Work_Num[i].Temp.Display_Rel = Work_Num[i].Temp.Last;//显示上一次温度，不让温度小于当前温度。呈现攀升速度的现象
					Work_Num[i].Temp.New = Work_Num[i].Temp.Last;//将上一次温度赋值给当前温度
				}
				Work_Num[i].Temp.Last = Work_Num[i].Temp.New;//将当前温度保存
				if(Work_Num[i].Temp.Display_Rel <= Work_Num[i].Temp.Ctrl)//当前的温度小于等于控制温度
				{
					Work_Num[i].Temp.ADDMode = 3;//进入稳定模式
				}
			}
            
			else if(Work_Num[i].Temp.ADDMode == 3)//温度稳定模式下
			{
				Work_Num[i].Temp.Display_Rel = Work_Num[i].Temp.Ctrl;//显示控制温度
			}
            
		}
		else
		{
			Work_Num[i].Temp.ADDMode = 0;//进入稳定模式 
			Work_Num[i].Temp.Display_Rel = Work_Num[i].Temp.Rel;//显示实际温度
		}
	}
	else
	{
		Work_Num[i].Temp.Display_Rel = Work_Num[i].Temp.Rel;//显示实际温度
		Work_Num[i].Temp.New =0;//现在的速度清零
		Work_Num[i].Temp.Last = 0;//之前的速度清零
		Work_Num[i].Temp.ADDMode = 0;//清除显示处理
        T[i] = 0;
	}
}

/**
 * @brief 显示屏幕内容
 *
 */
void Show_Display(void)
{
    while(1)
    {
		for(uint8_t i = 0;i<Motor_Num;i++)
		{
			Work_Num[i].Speed.Display_Set = Work_Num[i].Speed.Set;
			Deal_Speed(i);
			Work_Num[i].Temp.Display_Set = Work_Num[i].Temp.Set;
			Deal_Temp(0.1f,i);
			Work_Num[i].Time.Display_Set = Work_Num[i].Time.Set;
			Work_Num[i].Time.Display_Rel = Work_Num[i].Time.Rel + 59;
		}
		Twinkle(0.1f);
		Display(Work_Num);
        vTaskDelay(100);
    }
}
