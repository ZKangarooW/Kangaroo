#include "Show.h"

/**********全局变量**********/
float Twinkle_Time; // 闪烁时间
float WorkTwinkle_Time; //工位闪烁时间

/**********局部变量声明*******/
uint8_t Speed_ShowFlag, Temp_ShowFlag, Time_ShowFlag;//速度、温度、时间显示的标志位，0：常亮，1：熄灭
uint8_t WorkLine_Flag;

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
            bit_Cal(56, 0x04, 0x04);//显示数字1
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

    /* 1号工位与3号工位之间横线 */
    if(sys.New_Work == 0)//如果当前工位在1
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
    
    // if(PT_VALUE_1_TEMP[0] < 2200)//外部探头
    // {
        bit_Cal(58, 0x08, 0x08);//1号工位温度探头图标
    // }
    // else
    // {
    //     bit_Cal(58, 0x08, 0x00);//不显示1号工位温度探头图标
    // }
    
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
            bit_Cal(36, 0x04, 0x04);//显示数字1
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
    if(Speed_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 0)//不显示设定转速
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
    if(Temp_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 0)//不显示设定转速
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
    if(Time_ShowFlag && EC11A[1].EC11A_Knob <= 0 && sys.New_Work == 0)//不显示设定转速
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

    /* 2号工位与3号工位之间横线 */
    if(sys.New_Work == 0)//如果当前工位在1
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
    
    // if(PT_VALUE_1_TEMP[1] < 2200)//外部探头
    // {
        bit_Cal(38, 0x08, 0x08);//2号工位温度探头图标
    // }
    // else
    // {
    //     bit_Cal(38, 0x08, 0x00);//不显示2号工位温度探头图标
    // }
    
    /* 2号工位时间图标 */
    if(Work_Num[1].Time.Icon == 0)
    {
        bit_Cal(39, 0x80, 0x80);//2号工位时间图标
    }
    else
    {
        bit_Cal(39, 0x80, 0x00);//2号工位时间图标
    }
    HT16H25_RamUpdata(seg);
}

void Show_Display(void)
{
    while(1)
    {
        // for(uint8_t i = 0;i<4;i++)
        // {
        //     Work_Num[i].Speed.Display_Set = Work_Num[i].Speed.Set;
        //     Deal_Speed(i);
        //     Work_Num[i].Temp.Display_Set = Work_Num[i].Temp.Set;
        //     Deal_Temp(0.1f,i);
        //     Work_Num[i].Time.Display_Set = Work_Num[i].Time.Set;
        //     Work_Num[i].Time.Display_Rel = Work_Num[i].Time.Rel + 59;
        // }
        // Twinkle(0.1f);
        Display(Work_Num);
        vTaskDelay(100);
    }
}
