#include "Show.h"

/**********全局变量声明******/
float Speed_Twinkle_Time,Time_Twinkle_Time;//速度闪烁时间和时间闪烁时间

/**********局部变量声明******/
uint8_t Speed_ShowFlag,Time_ShowFlag;//速度、时间显示的标志位 0:常亮 1：熄灭
uint8_t cnt;

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
	static float Speed_T,Time_T;
	if(Speed_Twinkle_Time && !EC11A[0].EC11A_Knob)//速度闪烁和没有操作按键时
    {
		Speed_T += dT;
		if(Speed_T >= 0.5f)
		{
			Speed_Twinkle_Time -= 0.5;//闪烁计时
			Speed_ShowFlag = ~Speed_ShowFlag;//速度闪烁
			if(Speed_Twinkle_Time == 0)//如果闪烁结束
			{
				SpeedSet_Flag = 1;//进入速度设定
				Beep_Time = 0.1;//蜂鸣器响0.1S
			} 
			Speed_T = 0;		
		}			
    }
	else
	{
		Speed_ShowFlag = 0;//常亮
		Speed_T = 0;
	}
	
	if(Time_Twinkle_Time && !EC11A[1].EC11A_Knob)//时间闪烁和没有操作按键时
    {
		Time_T += dT;
		if(Time_T >= 0.5f)
		{
			Time_Twinkle_Time -= 0.5;//闪烁计时
			Time_ShowFlag = ~Time_ShowFlag;//时间闪烁
			if(Time_Twinkle_Time == 0)//如果闪烁结束
			{
				TimeSet_Flag = 1;//进入时间设定
				Beep_Time = 0.1;//蜂鸣器响0.1S
			} 
			Time_T = 0;			
		}			
    }
	else
	{
		Time_ShowFlag = 0;//常亮
		Time_T = 0;
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
}

/*
*****************************************************************
 * 函数原型：void Display_Screen(int16_t dis_set_speed,int16_t dis_rel_speed,int32_t dis_set_time,int32_t dis_rel_time)
 * 功    能：显示屏幕内容
 * 输    入: dis_set_speed：设定转速，dis_rel_speed：实际转速，dis_set_time：设定时间，dis_rel_time：实际时间
 * 参    数：int16_t dis_set_speed,int16_t dis_rel_speed,int32_t dis_set_time,int32_t dis_rel_time
*****************************************************************
*/
void Display_Screen(int16_t dis_set_speed,int16_t dis_rel_speed,int32_t dis_set_time,int32_t dis_rel_time)
{
	uint8_t seg[16] = {0};
//	uint8_t seg0,seg1,seg2,seg3,seg4,seg5,seg6,seg7,seg8,seg9,seg10,seg11,seg12,seg13,seg14,seg15;
//	seg0=0;seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;seg7=0;seg8=0;seg9=0;seg10=0;seg11=0;seg12=0;seg13=0;seg14=0;;seg15=0;
	uint16_t Val;//用于百十个取出来的数字
	uint8_t SH,H,SM,M;//时间的单位取值
    
    /***********dis_set_speed千位***********/
    if(!Speed_ShowFlag)//闪烁显示
    {
        if(dis_set_speed > 999)//大于999时
        {
            Val=dis_set_speed/1000;//取出千位
            if(dis_set_speed > 9999)//大于9999时
                Val=Val%10;//取出千位
            switch(Val)
            {
                case 0:seg[0]&=0xFE;seg[1]&=0xFE;seg[3]&=0xFE;seg[5]&=0xFE;seg[6]&=0xFE;seg[7]&=0xFE;
                        seg[0]|=0x01;seg[1]|=0x01;seg[3]|=0x01;seg[5]|=0x01;seg[6]|=0x01;seg[7]|=0x01;//数字0
                    break;
                case 1:seg[3]&=0xFE;seg[5]&=0xFE;
                        seg[3]|=0x01;seg[5]|=0x01;//数字1
                    break;
                case 2:seg[0]&=0xFE;seg[1]&=0xFE;seg[4]&=0xFE;seg[5]&=0xFE;seg[7]&=0xFE;
                        seg[0]|=0x01;seg[1]|=0x01;seg[4]|=0x01;seg[5]|=0x01;seg[7]|=0x01;//数字2
                    break;
                case 3:seg[1]&=0xFE;seg[3]&=0xFE;seg[4]&=0xFE;seg[5]&=0xFE;seg[7]&=0xFE;
                        seg[1]|=0x01;seg[3]|=0x01;seg[4]|=0x01;seg[5]|=0x01;seg[7]|=0x01;//数字3
                    break;	
                case 4:seg[3]&=0xFE;seg[4]&=0xFE;seg[5]&=0xFE;seg[6]&=0xFE;
                        seg[3]|=0x01;seg[4]|=0x01;seg[5]|=0x01;seg[6]|=0x01;//数字4
                    break;	
                case 5:seg[1]&=0xFE;seg[3]&=0xFE;seg[4]&=0xFE;seg[6]&=0xFE;seg[7]&=0xFE;
                        seg[1]|=0x01;seg[3]|=0x01;seg[4]|=0x01;seg[6]|=0x01;seg[7]|=0x01;//数字5
                    break;	
                case 6:seg[0]&=0xFE;seg[1]&=0xFE;seg[3]&=0xFE;seg[4]&=0xFE;seg[6]&=0xFE;seg[7]&=0xFE;
                        seg[0]|=0x01;seg[1]|=0x01;seg[3]|=0x01;seg[4]|=0x01;seg[6]|=0x01;seg[7]|=0x01;//数字6
                    break;	
                case 7:seg[3]&=0xFE;seg[5]&=0xFE;seg[7]&=0xFE;
                        seg[3]|=0x01;seg[5]|=0x01;seg[7]|=0x01;//数字7
                    break;	
                case 8:seg[0]&=0xFE;seg[1]&=0xFE;seg[3]&=0xFE;seg[4]&=0xFE;seg[5]&=0xFE;seg[6]&=0xFE;seg[7]&=0xFE;
                        seg[0]|=0x01;seg[1]|=0x01;seg[3]|=0x01;seg[4]|=0x01;seg[5]|=0x01;seg[6]|=0x01;seg[7]|=0x01;//数字8
                    break;	
                case 9:seg[1]&=0xFE;seg[3]&=0xFE;seg[4]&=0xFE;seg[5]&=0xFE;seg[6]&=0xFE;seg[7]&=0xFE;
                        seg[1]|=0x01;seg[3]|=0x01;seg[4]|=0x01;seg[5]|=0x01;seg[6]|=0x01;seg[7]|=0x01;//数字9
                    break;
                default:
                    break;
            }			
        }
        else
        {
            seg[0]&=0xFE;seg[1]&=0xFE;seg[3]&=0xFE;seg[4]&=0xFE;seg[5]&=0xFE;seg[6]&=0xFE;seg[7]&=0xFE;
            seg[0]|=0x00;seg[1]|=0x00;seg[3]|=0x00;seg[4]|=0x00;seg[5]|=0x00;seg[6]|=0x00;seg[7]|=0x00;//不显示
        }

        /***********dis_set_speed百位***********/
        if(dis_set_speed > 99)//大于99时
        {
            Val=dis_set_speed/100;//取出百位
            if(dis_set_speed > 999)//大于999时
                Val=Val%10;//取出百位
            switch(Val)
            {
                case 0:seg[0]&=0xFD;seg[1]&=0xFD;seg[3]&=0xFD;seg[5]&=0xFD;seg[6]&=0xFD;seg[7]&=0xFD;
                        seg[0]|=0x02;seg[1]|=0x02;seg[3]|=0x02;seg[5]|=0x02;seg[6]|=0x02;seg[7]|=0x02;//数字0
                    break;
                case 1:seg[3]&=0xFD;seg[5]&=0xFD;
                        seg[3]|=0x02;seg[5]|=0x02;//数字1
                    break;
                case 2:seg[0]&=0xFD;seg[1]&=0xFD;seg[4]&=0xFD;seg[5]&=0xFD;seg[7]&=0xFD;
                        seg[0]|=0x02;seg[1]|=0x02;seg[4]|=0x02;seg[5]|=0x02;seg[7]|=0x02;//数字2
                    break;
                case 3:seg[1]&=0xFD;seg[3]&=0xFD;seg[4]&=0xFD;seg[5]&=0xFD;seg[7]&=0xFD;
                        seg[1]|=0x02;seg[3]|=0x02;seg[4]|=0x02;seg[5]|=0x02;seg[7]|=0x02;//数字3
                    break;	
                case 4:seg[3]&=0xFD;seg[4]&=0xFD;seg[5]&=0xFD;seg[6]&=0xFD;
                        seg[3]|=0x02;seg[4]|=0x02;seg[5]|=0x02;seg[6]|=0x02;//数字4
                    break;	
                case 5:seg[1]&=0xFD;seg[3]&=0xFD;seg[4]&=0xFD;seg[6]&=0xFD;seg[7]&=0xFD;
                        seg[1]|=0x02;seg[3]|=0x02;seg[4]|=0x02;seg[6]|=0x02;seg[7]|=0x02;//数字5
                    break;	
                case 6:seg[0]&=0xFD;seg[1]&=0xFD;seg[3]&=0xFD;seg[4]&=0xFD;seg[6]&=0xFD;seg[7]&=0xFD;
                        seg[0]|=0x02;seg[1]|=0x02;seg[3]|=0x02;seg[4]|=0x02;seg[6]|=0x02;seg[7]|=0x02;//数字6
                    break;	
                case 7:seg[3]&=0xFD;seg[5]&=0xFD;seg[7]&=0xFD;
                        seg[3]|=0x02;seg[5]|=0x02;seg[7]|=0x02;//数字7
                    break;	
                case 8:seg[0]&=0xFD;seg[1]&=0xFD;seg[3]&=0xFD;seg[4]&=0xFD;seg[5]&=0xFD;seg[6]&=0xFD;seg[7]&=0xFD;
                        seg[0]|=0x02;seg[1]|=0x02;seg[3]|=0x02;seg[4]|=0x02;seg[5]|=0x02;seg[6]|=0x02;seg[7]|=0x02;//数字8
                    break;	
                case 9:seg[1]&=0xFD;seg[3]&=0xFD;seg[4]&=0xFD;seg[5]&=0xFD;seg[6]&=0xFD;seg[7]&=0xFD;
                        seg[1]|=0x02;seg[3]|=0x02;seg[4]|=0x02;seg[5]|=0x02;seg[6]|=0x02;seg[7]|=0x02;//数字9
                    break;
                default:
                    break;
            }			
        }
        else
        {
            seg[0]&=0xFD;seg[1]&=0xFD;seg[3]&=0xFD;seg[4]&=0xFD;seg[5]&=0xFD;seg[6]&=0xFD;seg[7]&=0xFD;
            seg[0]|=0x00;seg[1]|=0x00;seg[3]|=0x00;seg[4]|=0x00;seg[5]|=0x00;seg[6]|=0x00;seg[7]|=0x00;//不显示
        }
        
        /***********dis_set_speed十位***********/
        if(dis_set_speed > 9)//大于9时
        {
            Val=dis_set_speed/10;//取出十位
            if(dis_set_speed > 99)//大于99时
                Val=Val%10;//取出十位
            switch(Val)
            {
                case 0:seg[0]&=0xFB;seg[1]&=0xFB;seg[3]&=0xFB;seg[5]&=0xFB;seg[6]&=0xFB;seg[7]&=0xFB;
                        seg[0]|=0x04;seg[1]|=0x04;seg[3]|=0x04;seg[5]|=0x04;seg[6]|=0x04;seg[7]|=0x04;//数字0
                    break;
                case 1:seg[3]&=0xFB;seg[5]&=0xFB;
                        seg[3]|=0x04;seg[5]|=0x04;//数字1
                    break;
                case 2:seg[0]&=0xFB;seg[1]&=0xFB;seg[4]&=0xFB;seg[5]&=0xFB;seg[7]&=0xFB;
                        seg[0]|=0x04;seg[1]|=0x04;seg[4]|=0x04;seg[5]|=0x04;seg[7]|=0x04;//数字2
                    break;
                case 3:seg[1]&=0xFB;seg[3]&=0xFB;seg[4]&=0xFB;seg[5]&=0xFB;seg[7]&=0xFB;
                        seg[1]|=0x04;seg[3]|=0x04;seg[4]|=0x04;seg[5]|=0x04;seg[7]|=0x04;//数字3
                    break;	
                case 4:seg[3]&=0xFB;seg[4]&=0xFB;seg[5]&=0xFB;seg[6]&=0xFB;
                        seg[3]|=0x04;seg[4]|=0x04;seg[5]|=0x04;seg[6]|=0x04;//数字4
                    break;	
                case 5:seg[1]&=0xFB;seg[3]&=0xFB;seg[4]&=0xFB;seg[6]&=0xFB;seg[7]&=0xFB;
                        seg[1]|=0x04;seg[3]|=0x04;seg[4]|=0x04;seg[6]|=0x04;seg[7]|=0x04;//数字5
                    break;	
                case 6:seg[0]&=0xFB;seg[1]&=0xFB;seg[3]&=0xFB;seg[4]&=0xFB;seg[6]&=0xFB;seg[7]&=0xFB;
                        seg[0]|=0x04;seg[1]|=0x04;seg[3]|=0x04;seg[4]|=0x04;seg[6]|=0x04;seg[7]|=0x04;//数字6
                    break;	
                case 7:seg[3]&=0xFB;seg[5]&=0xFB;seg[7]&=0xFB;
                        seg[3]|=0x04;seg[5]|=0x04;seg[7]|=0x04;//数字7
                    break;	
                case 8:seg[0]&=0xFB;seg[1]&=0xFB;seg[3]&=0xFB;seg[4]&=0xFB;seg[5]&=0xFB;seg[6]&=0xFB;seg[7]&=0xFB;
                        seg[0]|=0x04;seg[1]|=0x04;seg[3]|=0x04;seg[4]|=0x04;seg[5]|=0x04;seg[6]|=0x04;seg[7]|=0x04;//数字8
                    break;	
                case 9:seg[1]&=0xFB;seg[3]&=0xFB;seg[4]&=0xFB;seg[5]&=0xFB;seg[6]&=0xFB;seg[7]&=0xFB;
                        seg[1]|=0x04;seg[3]|=0x04;seg[4]|=0x04;seg[5]|=0x04;seg[6]|=0x04;seg[7]|=0x04;//数字9
                    break;
                default:
                    break;
            }			
        }
        else
        {
            seg[0]&=0xFB;seg[1]&=0xFB;seg[3]&=0xFB;seg[4]&=0xFB;seg[5]&=0xFB;seg[6]&=0xFB;seg[7]&=0xFB;
            seg[0]|=0x00;seg[1]|=0x00;seg[3]|=0x00;seg[4]|=0x00;seg[5]|=0x00;seg[6]|=0x00;seg[7]|=0x00;//不显示
        }
        
        /***********dis_set_speed个位***********/
        Val=dis_set_speed%10;//取出个位
        switch(Val)
        {
            case 0:seg[0]&=0xF7;seg[1]&=0xF7;seg[3]&=0xF7;seg[5]&=0xF7;seg[6]&=0xF7;seg[7]&=0xF7;
                    seg[0]|=0x08;seg[1]|=0x08;seg[3]|=0x08;seg[5]|=0x08;seg[6]|=0x08;seg[7]|=0x08;//数字0
                break;
            case 1:seg[3]&=0xF7;seg[5]&=0xF7;
                    seg[3]|=0x08;seg[5]|=0x08;//数字1
                break;
            case 2:seg[0]&=0xF7;seg[1]&=0xF7;seg[4]&=0xF7;seg[5]&=0xF7;seg[7]&=0xF7;
                    seg[0]|=0x08;seg[1]|=0x08;seg[4]|=0x08;seg[5]|=0x08;seg[7]|=0x08;//数字2
                break;
            case 3:seg[1]&=0xF7;seg[3]&=0xF7;seg[4]&=0xF7;seg[5]&=0xF7;seg[7]&=0xF7;
                    seg[1]|=0x08;seg[3]|=0x08;seg[4]|=0x08;seg[5]|=0x08;seg[7]|=0x08;//数字3
                break;	
            case 4:seg[3]&=0xF7;seg[4]&=0xF7;seg[5]&=0xF7;seg[6]&=0xF7;
                    seg[3]|=0x08;seg[4]|=0x08;seg[5]|=0x08;seg[6]|=0x08;//数字4
                break;	
            case 5:seg[1]&=0xF7;seg[3]&=0xF7;seg[4]&=0xF7;seg[6]&=0xF7;seg[7]&=0xF7;
                    seg[1]|=0x08;seg[3]|=0x08;seg[4]|=0x08;seg[6]|=0x08;seg[7]|=0x08;//数字5
                break;	
            case 6:seg[0]&=0xF7;seg[1]&=0xF7;seg[3]&=0xF7;seg[4]&=0xF7;seg[6]&=0xF7;seg[7]&=0xF7;
                    seg[0]|=0x08;seg[1]|=0x08;seg[3]|=0x08;seg[4]|=0x08;seg[6]|=0x08;seg[7]|=0x08;//数字6
                break;	
            case 7:seg[3]&=0xF7;seg[5]&=0xF7;seg[7]&=0xF7;
                    seg[3]|=0x08;seg[5]|=0x08;seg[7]|=0x08;//数字7
                break;	
            case 8:seg[0]&=0xF7;seg[1]&=0xF7;seg[3]&=0xF7;seg[4]&=0xF7;seg[5]&=0xF7;seg[6]&=0xF7;seg[7]&=0xF7;
                    seg[0]|=0x08;seg[1]|=0x08;seg[3]|=0x08;seg[4]|=0x08;seg[5]|=0x08;seg[6]|=0x08;seg[7]|=0x08;//数字8
                break;	
            case 9:seg[1]&=0xF7;seg[3]&=0xF7;seg[4]&=0xF7;seg[5]&=0xF7;seg[6]&=0xF7;seg[7]&=0xF7;
                    seg[1]|=0x08;seg[3]|=0x08;seg[4]|=0x08;seg[5]|=0x08;seg[6]|=0x08;seg[7]|=0x08;//数字9
                break;
            default:
                break;
        }	
    }
    else
    {		
        seg[0]&=0xF0;seg[1]&=0xF0;seg[3]&=0xF0;seg[4]&=0xF0;seg[5]&=0xF0;seg[6]&=0xF0;seg[7]&=0xF0;
        seg[0]|=0x00;seg[1]|=0x00;seg[3]|=0x00;seg[4]|=0x00;seg[5]|=0x00;seg[6]|=0x00;seg[7]|=0x00;//不显示
    }
    
    /***********dis_rel_speed千位***********/
    if(dis_rel_speed > 999)//大于999时
    {
        Val=dis_rel_speed/1000;//取出千位
        if(dis_rel_speed > 9999)//大于9999时
            Val=Val%10;//取出千位
        switch(Val)
        {
            case 0:seg[0]&=0xEF;seg[1]&=0xEF;seg[3]&=0xEF;seg[5]&=0xEF;seg[6]&=0xEF;seg[7]&=0xEF;
                    seg[0]|=0x10;seg[1]|=0x10;seg[3]|=0x10;seg[5]|=0x10;seg[6]|=0x10;seg[7]|=0x10;//数字0
                break;
            case 1:seg[3]&=0xEF;seg[5]&=0xEF;
                    seg[3]|=0x10;seg[5]|=0x10;//数字1
                break;
            case 2:seg[0]&=0xEF;seg[1]&=0xEF;seg[4]&=0xEF;seg[5]&=0xEF;seg[7]&=0xEF;
                    seg[0]|=0x10;seg[1]|=0x10;seg[4]|=0x10;seg[5]|=0x10;seg[7]|=0x10;//数字2
                break;
            case 3:seg[1]&=0xEF;seg[3]&=0xEF;seg[4]&=0xEF;seg[5]&=0xEF;seg[7]&=0xEF;
                    seg[1]|=0x10;seg[3]|=0x10;seg[4]|=0x10;seg[5]|=0x10;seg[7]|=0x10;//数字3
                break;	
            case 4:seg[3]&=0xEF;seg[4]&=0xEF;seg[5]&=0xEF;seg[6]&=0xEF;
                    seg[3]|=0x10;seg[4]|=0x10;seg[5]|=0x10;seg[6]|=0x10;//数字4
                break;	
            case 5:seg[1]&=0xEF;seg[3]&=0xEF;seg[4]&=0xEF;seg[6]&=0xEF;seg[7]&=0xEF;
                    seg[1]|=0x10;seg[3]|=0x10;seg[4]|=0x10;seg[6]|=0x10;seg[7]|=0x10;//数字5
                break;	
            case 6:seg[0]&=0xEF;seg[1]&=0xEF;seg[3]&=0xEF;seg[4]&=0xEF;seg[6]&=0xEF;seg[7]&=0xEF;
                    seg[0]|=0x10;seg[1]|=0x10;seg[3]|=0x10;seg[4]|=0x10;seg[6]|=0x10;seg[7]|=0x10;//数字6
                break;	
            case 7:seg[3]&=0xEF;seg[5]&=0xEF;seg[7]&=0xEF;
                    seg[3]|=0x10;seg[5]|=0x10;seg[7]|=0x10;//数字7
                break;	
            case 8:seg[0]&=0xEF;seg[1]&=0xEF;seg[3]&=0xEF;seg[4]&=0xEF;seg[5]&=0xEF;seg[6]&=0xEF;seg[7]&=0xEF;
                    seg[0]|=0x10;seg[1]|=0x10;seg[3]|=0x10;seg[4]|=0x10;seg[5]|=0x10;seg[6]|=0x10;seg[7]|=0x10;//数字8
                break;	
            case 9:seg[1]&=0xEF;seg[3]&=0xEF;seg[4]&=0xEF;seg[5]&=0xEF;seg[6]&=0xEF;seg[7]&=0xEF;
                    seg[1]|=0x10;seg[3]|=0x10;seg[4]|=0x10;seg[5]|=0x10;seg[6]|=0x10;seg[7]|=0x10;//数字9
                break;
            default:
                break;
        }			
    }
    else
    {
        seg[0]&=0xEF;seg[1]&=0xEF;seg[3]&=0xEF;seg[4]&=0xEF;seg[5]&=0xEF;seg[6]&=0xEF;seg[7]&=0xEF;
        seg[0]|=0x00;seg[1]|=0x00;seg[3]|=0x00;seg[4]|=0x00;seg[5]|=0x00;seg[6]|=0x00;seg[7]|=0x00;//不显示
    }

    /***********dis_rel_speed百位***********/
    if(dis_rel_speed > 99)//大于99时
    {
        Val=dis_rel_speed/100;//取出百位
        if(dis_rel_speed > 999)//大于999时
            Val=Val%10;//取出百位
        switch(Val)
        {
            case 0:seg[0]&=0xDF;seg[1]&=0xDF;seg[3]&=0xDF;seg[5]&=0xDF;seg[6]&=0xDF;seg[7]&=0xDF;
                    seg[0]|=0x20;seg[1]|=0x20;seg[3]|=0x20;seg[5]|=0x20;seg[6]|=0x20;seg[7]|=0x20;//数字0
                break;
            case 1:seg[3]&=0xDF;seg[5]&=0xDF;
                    seg[3]|=0x20;seg[5]|=0x20;//数字1
                break;
            case 2:seg[0]&=0xDF;seg[1]&=0xDF;seg[4]&=0xDF;seg[5]&=0xDF;seg[7]&=0xDF;
                    seg[0]|=0x20;seg[1]|=0x20;seg[4]|=0x20;seg[5]|=0x20;seg[7]|=0x20;//数字2
                break;
            case 3:seg[1]&=0xDF;seg[3]&=0xDF;seg[4]&=0xDF;seg[5]&=0xDF;seg[7]&=0xDF;
                    seg[1]|=0x20;seg[3]|=0x20;seg[4]|=0x20;seg[5]|=0x20;seg[7]|=0x20;//数字3
                break;	
            case 4:seg[3]&=0xDF;seg[4]&=0xDF;seg[5]&=0xDF;seg[6]&=0xDF;
                    seg[3]|=0x20;seg[4]|=0x20;seg[5]|=0x20;seg[6]|=0x20;//数字4
                break;	
            case 5:seg[1]&=0xDF;seg[3]&=0xDF;seg[4]&=0xDF;seg[6]&=0xDF;seg[7]&=0xDF;
                    seg[1]|=0x20;seg[3]|=0x20;seg[4]|=0x20;seg[6]|=0x20;seg[7]|=0x20;//数字5
                break;	
            case 6:seg[0]&=0xDF;seg[1]&=0xDF;seg[3]&=0xDF;seg[4]&=0xDF;seg[6]&=0xDF;seg[7]&=0xDF;
                    seg[0]|=0x20;seg[1]|=0x20;seg[3]|=0x20;seg[4]|=0x20;seg[6]|=0x20;seg[7]|=0x20;//数字6
                break;	
            case 7:seg[3]&=0xDF;seg[5]&=0xDF;seg[7]&=0xDF;
                    seg[3]|=0x20;seg[5]|=0x20;seg[7]|=0x20;//数字7
                break;	
            case 8:seg[0]&=0xDF;seg[1]&=0xDF;seg[3]&=0xDF;seg[4]&=0xDF;seg[5]&=0xDF;seg[6]&=0xDF;seg[7]&=0xDF;
                    seg[0]|=0x20;seg[1]|=0x20;seg[3]|=0x20;seg[4]|=0x20;seg[5]|=0x20;seg[6]|=0x20;seg[7]|=0x20;//数字8
                break;	
            case 9:seg[1]&=0xDF;seg[3]&=0xDF;seg[4]&=0xDF;seg[5]&=0xDF;seg[6]&=0xDF;seg[7]&=0xDF;
                    seg[1]|=0x20;seg[3]|=0x20;seg[4]|=0x20;seg[5]|=0x20;seg[6]|=0x20;seg[7]|=0x20;//数字9
                break;
            default:
                break;
        }			
    }
    else
    {
        seg[0]&=0xDF;seg[1]&=0xDF;seg[3]&=0xDF;seg[4]&=0xDF;seg[5]&=0xDF;seg[6]&=0xDF;seg[7]&=0xDF;
        seg[0]|=0x00;seg[1]|=0x00;seg[3]|=0x00;seg[4]|=0x00;seg[5]|=0x00;seg[6]|=0x00;seg[7]|=0x00;//不显示
    }
    /***********dis_rel_speed十位***********/
    if(dis_rel_speed > 9)//大于9时
    {
        Val=dis_rel_speed/10;//取出十位
        if(dis_rel_speed > 99)//大于99时
            Val=Val%10;//取出十位
        switch(Val)
        {
            case 0:seg[0]&=0xBF;seg[1]&=0xBF;seg[3]&=0xBF;seg[5]&=0xBF;seg[6]&=0xBF;seg[7]&=0xBF;
                    seg[0]|=0x40;seg[1]|=0x40;seg[3]|=0x40;seg[5]|=0x40;seg[6]|=0x40;seg[7]|=0x40;//数字0
                break;
            case 1:seg[3]&=0xBF;seg[5]&=0xBF;
                    seg[3]|=0x40;seg[5]|=0x40;//数字1
                break;
            case 2:seg[0]&=0xBF;seg[1]&=0xBF;seg[4]&=0xBF;seg[5]&=0xBF;seg[7]&=0xBF;
                    seg[0]|=0x40;seg[1]|=0x40;seg[4]|=0x40;seg[5]|=0x40;seg[7]|=0x40;//数字2
                break;
            case 3:seg[1]&=0xBF;seg[3]&=0xBF;seg[4]&=0xBF;seg[5]&=0xBF;seg[7]&=0xBF;
                    seg[1]|=0x40;seg[3]|=0x40;seg[4]|=0x40;seg[5]|=0x40;seg[7]|=0x40;//数字3
                break;	
            case 4:seg[3]&=0xBF;seg[4]&=0xBF;seg[5]&=0xBF;seg[6]&=0xBF;
                    seg[3]|=0x40;seg[4]|=0x40;seg[5]|=0x40;seg[6]|=0x40;//数字4
                break;	
            case 5:seg[1]&=0xBF;seg[3]&=0xBF;seg[4]&=0xBF;seg[6]&=0xBF;seg[7]&=0xBF;
                    seg[1]|=0x40;seg[3]|=0x40;seg[4]|=0x40;seg[6]|=0x40;seg[7]|=0x40;//数字5
                break;	
            case 6:seg[0]&=0xBF;seg[1]&=0xBF;seg[3]&=0xBF;seg[4]&=0xBF;seg[6]&=0xBF;seg[7]&=0xBF;
                    seg[0]|=0x40;seg[1]|=0x40;seg[3]|=0x40;seg[4]|=0x40;seg[6]|=0x40;seg[7]|=0x40;//数字6
                break;	
            case 7:seg[3]&=0xBF;seg[5]&=0xBF;seg[7]&=0xBF;
                    seg[3]|=0x40;seg[5]|=0x40;seg[7]|=0x40;//数字7
                break;	
            case 8:seg[0]&=0xBF;seg[1]&=0xBF;seg[3]&=0xBF;seg[4]&=0xBF;seg[5]&=0xBF;seg[6]&=0xBF;seg[7]&=0xBF;
                    seg[0]|=0x40;seg[1]|=0x40;seg[3]|=0x40;seg[4]|=0x40;seg[5]|=0x40;seg[6]|=0x40;seg[7]|=0x40;//数字8
                break;	
            case 9:seg[1]&=0xBF;seg[3]&=0xBF;seg[4]&=0xBF;seg[5]&=0xBF;seg[6]&=0xBF;seg[7]&=0xBF;
                    seg[1]|=0x40;seg[3]|=0x40;seg[4]|=0x40;seg[5]|=0x40;seg[6]|=0x40;seg[7]|=0x40;//数字9
                break;
            default:
                break;
        }			
    }
    else
    {
        seg[0]&=0xBF;seg[1]&=0xBF;seg[3]&=0xBF;seg[4]&=0xBF;seg[5]&=0xBF;seg[6]&=0xBF;seg[7]&=0xBF;
        seg[0]|=0x00;seg[1]|=0x00;seg[3]|=0x00;seg[4]|=0x00;seg[5]|=0x00;seg[6]|=0x00;seg[7]|=0x00;//不显示
    }
    /***********dis_rel_speed个位***********/
    Val=dis_rel_speed%10;//取出个位
    switch(Val)
    {
        case 0:seg[0]&=0x7F;seg[1]&=0x7F;seg[3]&=0x7F;seg[5]&=0x7F;seg[6]&=0x7F;seg[7]&=0x7F;
                seg[0]|=0x80;seg[1]|=0x80;seg[3]|=0x80;seg[5]|=0x80;seg[6]|=0x80;seg[7]|=0x80;//数字0
            break;
        case 1:seg[3]&=0x7F;seg[5]&=0x7F;
                seg[3]|=0x80;seg[5]|=0x80;//数字1
            break;
        case 2:seg[0]&=0x7F;seg[1]&=0x7F;seg[4]&=0x7F;seg[5]&=0x7F;seg[7]&=0x7F;
                seg[0]|=0x80;seg[1]|=0x80;seg[4]|=0x80;seg[5]|=0x80;seg[7]|=0x80;//数字2
            break;
        case 3:seg[1]&=0x7F;seg[3]&=0x7F;seg[4]&=0x7F;seg[5]&=0x7F;seg[7]&=0x7F;
                seg[1]|=0x80;seg[3]|=0x80;seg[4]|=0x80;seg[5]|=0x80;seg[7]|=0x80;//数字3
            break;	
        case 4:seg[3]&=0x7F;seg[4]&=0x7F;seg[5]&=0x7F;seg[6]&=0x7F;
                seg[3]|=0x80;seg[4]|=0x80;seg[5]|=0x80;seg[6]|=0x80;//数字4
            break;	
        case 5:seg[1]&=0x7F;seg[3]&=0x7F;seg[4]&=0x7F;seg[6]&=0x7F;seg[7]&=0x7F;
                seg[1]|=0x80;seg[3]|=0x80;seg[4]|=0x80;seg[6]|=0x80;seg[7]|=0x80;//数字5
            break;	
        case 6:seg[0]&=0x7F;seg[1]&=0x7F;seg[3]&=0x7F;seg[4]&=0x7F;seg[6]&=0x7F;seg[7]&=0x7F;
                seg[0]|=0x80;seg[1]|=0x80;seg[3]|=0x80;seg[4]|=0x80;seg[6]|=0x80;seg[7]|=0x80;//数字6
            break;	
        case 7:seg[3]&=0x7F;seg[5]&=0x7F;seg[7]&=0x7F;
                seg[3]|=0x80;seg[5]|=0x80;seg[7]|=0x80;//数字7
            break;	
        case 8:seg[0]&=0x7F;seg[1]&=0x7F;seg[3]&=0x7F;seg[4]&=0x7F;seg[5]&=0x7F;seg[6]&=0x7F;seg[7]&=0x7F;
                seg[0]|=0x80;seg[1]|=0x80;seg[3]|=0x80;seg[4]|=0x80;seg[5]|=0x80;seg[6]|=0x80;seg[7]|=0x80;//数字8
            break;	
        case 9:seg[1]&=0x7F;seg[3]&=0x7F;seg[4]&=0x7F;seg[5]&=0x7F;seg[6]&=0x7F;seg[7]&=0x7F;
                seg[1]|=0x80;seg[3]|=0x80;seg[4]|=0x80;seg[5]|=0x80;seg[6]|=0x80;seg[7]|=0x80;//数字9
            break;
        default:
            break;
    }	
    
    if(!Time_ShowFlag)//设定时间闪烁
    {
        if(dis_set_time)//设定时间大于0
        {
            /***********dis_set_time**********/
            SH=dis_set_time/3600/10;//计算十位单位的小时数
            H=dis_set_time/3600%10;//计算个位单位的小时数
            SM=dis_set_time%3600/60/10;//计算十分位单位的分钟数
            M=dis_set_time%3600/60%10;//计算个分位单位的分钟数
            
            switch(SH)
            {
                case 0:seg[8]&=0xFE;seg[9]&=0xFE;seg[11]&=0xFE;seg[13]&=0xFE;seg[14]&=0xFE;seg[15]&=0xFE;
                        seg[8]|=0x01;seg[9]|=0x01;seg[11]|=0x01;seg[13]|=0x01;seg[14]|=0x01;seg[15]|=0x01;//数字0
                    break;
                case 1:seg[11]&=0xFE;seg[13]&=0xFE;
                        seg[11]|=0x01;seg[13]|=0x01;//数字1
                    break;
                case 2:seg[8]&=0xFE;seg[9]&=0xFE;seg[12]&=0xFE;seg[13]&=0xFE;seg[15]&=0xFE;
                        seg[8]|=0x01;seg[9]|=0x01;seg[12]|=0x01;seg[13]|=0x01;seg[15]|=0x01;//数字2
                    break;
                case 3:seg[9]&=0xFE;seg[11]&=0xFE;seg[12]&=0xFE;seg[13]&=0xFE;seg[15]&=0xFE;
                        seg[9]|=0x01;seg[11]|=0x01;seg[12]|=0x01;seg[13]|=0x01;seg[15]|=0x01;//数字3
                    break;	
                case 4:seg[11]&=0xFE;seg[12]&=0xFE;seg[13]&=0xFE;seg[14]&=0xFE;
                        seg[11]|=0x01;seg[12]|=0x01;seg[13]|=0x01;seg[14]|=0x01;//数字4
                    break;	
                case 5:seg[9]&=0xFE;seg[11]&=0xFE;seg[12]&=0xFE;seg[14]&=0xFE;seg[15]&=0xFE;
                        seg[9]|=0x01;seg[11]|=0x01;seg[12]|=0x01;seg[14]|=0x01;seg[15]|=0x01;//数字5
                    break;	
                case 6:seg[8]&=0xFE;seg[9]&=0xFE;seg[11]&=0xFE;seg[12]&=0xFE;seg[14]&=0xFE;seg[15]&=0xFE;
                        seg[8]|=0x01;seg[9]|=0x01;seg[11]|=0x01;seg[12]|=0x01;seg[14]|=0x01;seg[15]|=0x01;//数字6
                    break;	
                case 7:seg[11]&=0xFE;seg[13]&=0xFE;seg[15]&=0xFE;
                        seg[11]|=0x01;seg[13]|=0x01;seg[15]|=0x01;//数字7
                    break;	
                case 8:seg[8]&=0xFE;seg[9]&=0xFE;seg[11]&=0xFE;seg[12]&=0xFE;seg[13]&=0xFE;seg[14]&=0xFE;seg[15]&=0xFE;
                        seg[8]|=0x01;seg[9]|=0x01;seg[11]|=0x01;seg[12]|=0x01;seg[13]|=0x01;seg[14]|=0x01;seg[15]|=0x01;//数字8
                    break;	
                case 9:seg[9]&=0xFE;seg[11]&=0xFE;seg[12]&=0xFE;seg[13]&=0xFE;seg[14]&=0xFE;seg[15]&=0xFE;
                        seg[9]|=0x01;seg[11]|=0x01;seg[12]|=0x01;seg[13]|=0x01;seg[14]|=0x01;seg[15]|=0x01;//数字9
                    break;
                default:
                    break;
            }		
            switch(H)
            {
                case 0:seg[8]&=0xFD;seg[9]&=0xFD;seg[11]&=0xFD;seg[13]&=0xFD;seg[14]&=0xFD;seg[15]&=0xFD;
                        seg[8]|=0x02;seg[9]|=0x02;seg[11]|=0x02;seg[13]|=0x02;seg[14]|=0x02;seg[15]|=0x02;//数字0
                    break;
                case 1:seg[11]&=0xFD;seg[13]&=0xFD;
                        seg[11]|=0x02;seg[13]|=0x02;//数字1
                    break;
                case 2:seg[8]&=0xFD;seg[9]&=0xFD;seg[12]&=0xFD;seg[13]&=0xFD;seg[15]&=0xFD;
                        seg[8]|=0x02;seg[9]|=0x02;seg[12]|=0x02;seg[13]|=0x02;seg[15]|=0x02;//数字2
                    break;
                case 3:seg[9]&=0xFD;seg[11]&=0xFD;seg[12]&=0xFD;seg[13]&=0xFD;seg[15]&=0xFD;
                        seg[9]|=0x02;seg[11]|=0x02;seg[12]|=0x02;seg[13]|=0x02;seg[15]|=0x02;//数字3
                    break;	
                case 4:seg[11]&=0xFD;seg[12]&=0xFD;seg[13]&=0xFD;seg[14]&=0xFD;
                        seg[11]|=0x02;seg[12]|=0x02;seg[13]|=0x02;seg[14]|=0x02;//数字4
                    break;	
                case 5:seg[9]&=0xFD;seg[11]&=0xFD;seg[12]&=0xFD;seg[14]&=0xFD;seg[15]&=0xFD;
                        seg[9]|=0x02;seg[11]|=0x02;seg[12]|=0x02;seg[14]|=0x02;seg[15]|=0x02;//数字5
                    break;	
                case 6:seg[8]&=0xFD;seg[9]&=0xFD;seg[11]&=0xFD;seg[12]&=0xFD;seg[14]&=0xFD;seg[15]&=0xFD;
                        seg[8]|=0x02;seg[9]|=0x02;seg[11]|=0x02;seg[12]|=0x02;seg[14]|=0x02;seg[15]|=0x02;//数字6
                    break;	
                case 7:seg[11]&=0xFD;seg[13]&=0xFD;seg[15]&=0xFD;
                        seg[11]|=0x02;seg[13]|=0x02;seg[15]|=0x02;//数字7
                    break;	
                case 8:seg[8]&=0xFD;seg[9]&=0xFD;seg[11]&=0xFD;seg[12]&=0xFD;seg[13]&=0xFD;seg[14]&=0xFD;seg[15]&=0xFD;
                        seg[8]|=0x02;seg[9]|=0x02;seg[11]|=0x02;seg[12]|=0x02;seg[13]|=0x02;seg[14]|=0x02;seg[15]|=0x02;//数字8
                    break;	
                case 9:seg[9]&=0xFD;seg[11]&=0xFD;seg[12]&=0xFD;seg[13]&=0xFD;seg[14]&=0xFD;seg[15]&=0xFD;
                        seg[9]|=0x02;seg[11]|=0x02;seg[12]|=0x02;seg[13]|=0x02;seg[14]|=0x02;seg[15]|=0x02;//数字9
                    break;
                default:
                    break;
            }		
            switch(SM)
            {
                case 0:seg[8]&=0xFB;seg[9]&=0xFB;seg[11]&=0xFB;seg[13]&=0xFB;seg[14]&=0xFB;seg[15]&=0xFB;
                        seg[8]|=0x04;seg[9]|=0x04;seg[11]|=0x04;seg[13]|=0x04;seg[14]|=0x04;seg[15]|=0x04;//数字0
                    break;
                case 1:seg[11]&=0xFB;seg[13]&=0xFB;
                        seg[11]|=0x04;seg[13]|=0x04;//数字1
                    break;
                case 2:seg[8]&=0xFB;seg[9]&=0xFB;seg[12]&=0xFB;seg[13]&=0xFB;seg[15]&=0xFB;
                        seg[8]|=0x04;seg[9]|=0x04;seg[12]|=0x04;seg[13]|=0x04;seg[15]|=0x04;//数字2
                    break;
                case 3:seg[9]&=0xFB;seg[11]&=0xFB;seg[12]&=0xFB;seg[13]&=0xFB;seg[15]&=0xFB;
                        seg[9]|=0x04;seg[11]|=0x04;seg[12]|=0x04;seg[13]|=0x04;seg[15]|=0x04;//数字3
                    break;	
                case 4:seg[11]&=0xFB;seg[12]&=0xFB;seg[13]&=0xFB;seg[14]&=0xFB;
                        seg[11]|=0x04;seg[12]|=0x04;seg[13]|=0x04;seg[14]|=0x04;//数字4
                    break;	
                case 5:seg[9]&=0xFB;seg[11]&=0xFB;seg[12]&=0xFB;seg[14]&=0xFB;seg[15]&=0xFB;
                        seg[9]|=0x04;seg[11]|=0x04;seg[12]|=0x04;seg[14]|=0x04;seg[15]|=0x04;//数字5
                    break;	
                case 6:seg[8]&=0xFB;seg[9]&=0xFB;seg[11]&=0xFB;seg[12]&=0xFB;seg[14]&=0xFB;seg[15]&=0xFB;
                        seg[8]|=0x04;seg[9]|=0x04;seg[11]|=0x04;seg[12]|=0x04;seg[14]|=0x04;seg[15]|=0x04;//数字6
                    break;	
                case 7:seg[11]&=0xFB;seg[13]&=0xFB;seg[15]&=0xFB;
                        seg[11]|=0x04;seg[13]|=0x04;seg[15]|=0x04;//数字7
                    break;	
                case 8:seg[8]&=0xFB;seg[9]&=0xFB;seg[11]&=0xFB;seg[12]&=0xFB;seg[13]&=0xFB;seg[14]&=0xFB;seg[15]&=0xFB;
                        seg[8]|=0x04;seg[9]|=0x04;seg[11]|=0x04;seg[12]|=0x04;seg[13]|=0x04;seg[14]|=0x04;seg[15]|=0x04;//数字8
                    break;	
                case 9:seg[9]&=0xFB;seg[11]&=0xFB;seg[12]&=0xFB;seg[13]&=0xFB;seg[14]&=0xFB;seg[15]&=0xFB;
                        seg[9]|=0x04;seg[11]|=0x04;seg[12]|=0x04;seg[13]|=0x04;seg[14]|=0x04;seg[15]|=0x04;//数字9
                    break;
                default:
                    break;
            }		
            switch(M)
            {
                case 0:seg[8]&=0xF7;seg[9]&=0xF7;seg[11]&=0xF7;seg[13]&=0xF7;seg[14]&=0xF7;seg[15]&=0xF7;
                        seg[8]|=0x08;seg[9]|=0x08;seg[11]|=0x08;seg[13]|=0x08;seg[14]|=0x08;seg[15]|=0x08;//数字0
                    break;
                case 1:seg[11]&=0xF7;seg[13]&=0xF7;
                        seg[11]|=0x08;seg[13]|=0x08;//数字1
                    break;
                case 2:seg[8]&=0xF7;seg[9]&=0xF7;seg[12]&=0xF7;seg[13]&=0xF7;seg[15]&=0xF7;
                        seg[8]|=0x08;seg[9]|=0x08;seg[12]|=0x08;seg[13]|=0x08;seg[15]|=0x08;//数字2
                    break;
                case 3:seg[9]&=0xF7;seg[11]&=0xF7;seg[12]&=0xF7;seg[13]&=0xF7;seg[15]&=0xF7;
                        seg[9]|=0x08;seg[11]|=0x08;seg[12]|=0x08;seg[13]|=0x08;seg[15]|=0x08;//数字3
                    break;	
                case 4:seg[11]&=0xF7;seg[12]&=0xF7;seg[13]&=0xF7;seg[14]&=0xF7;
                        seg[11]|=0x08;seg[12]|=0x08;seg[13]|=0x08;seg[14]|=0x08;//数字4
                    break;	
                case 5:seg[9]&=0xF7;seg[11]&=0xF7;seg[12]&=0xF7;seg[14]&=0xF7;seg[15]&=0xF7;
                        seg[9]|=0x08;seg[11]|=0x08;seg[12]|=0x08;seg[14]|=0x08;seg[15]|=0x08;//数字5
                    break;	
                case 6:seg[8]&=0xF7;seg[9]&=0xF7;seg[11]&=0xF7;seg[12]&=0xF7;seg[14]&=0xF7;seg[15]&=0xF7;
                        seg[8]|=0x08;seg[9]|=0x08;seg[11]|=0x08;seg[12]|=0x08;seg[14]|=0x08;seg[15]|=0x08;//数字6
                    break;	
                case 7:seg[11]&=0xF7;seg[13]&=0xF7;seg[15]&=0xF7;
                        seg[11]|=0x08;seg[13]|=0x08;seg[15]|=0x08;//数字7
                    break;	
                case 8:seg[8]&=0xF7;seg[9]&=0xF7;seg[11]&=0xF7;seg[12]&=0xF7;seg[13]&=0xF7;seg[14]&=0xF7;seg[15]&=0xF7;
                        seg[8]|=0x08;seg[9]|=0x08;seg[11]|=0x08;seg[12]|=0x08;seg[13]|=0x08;seg[14]|=0x08;seg[15]|=0x08;//数字8
                    break;	
                case 9:seg[9]&=0xF7;seg[11]&=0xF7;seg[12]&=0xF7;seg[13]&=0xF7;seg[14]&=0xF7;seg[15]&=0xF7;
                        seg[9]|=0x08;seg[11]|=0x08;seg[12]|=0x08;seg[13]|=0x08;seg[14]|=0x08;seg[15]|=0x08;//数字9
                    break;
                default:
                    break;
            }
        }
        else
        {
            seg[8]&=0xF0;seg[9]&=0xF0;seg[11]&=0xF0;seg[12]&=0xF0;seg[13]&=0xF0;seg[14]&=0xF0;seg[15]&=0xF0;
            seg[8]|=0x00;seg[9]|=0x00;seg[11]|=0x00;seg[12]|=0x0F;seg[13]|=0x00;seg[14]|=0x00;seg[15]|=0x00;//显示“-- --”
        }
    }
    else
    {
        seg[8]&=0xF0;seg[9]&=0xF0;seg[11]&=0xF0;seg[12]&=0xF0;seg[13]&=0xF0;seg[14]&=0xF0;seg[15]&=0xF0;
        seg[8]|=0x00;seg[9]|=0x00;seg[11]|=0x00;seg[12]|=0x00;seg[13]|=0x00;seg[14]|=0x00;seg[15]|=0x00;
    }
	
    /***********dis_rel_time**********/
    if(Time.Rel || dis_set_time)//显示时间表示为0
	{
        SH=dis_rel_time/3600/10;//计算十位单位的小时数
        H=dis_rel_time/3600%10;//计算个位单位的小时数
        SM=dis_rel_time%3600/60/10;//计算十分位单位的分钟数
        M=dis_rel_time%3600/60%10;//计算个分位单位的分钟数
        
        switch(SH)
        {
            case 0:seg[8]&=0xEF;seg[9]&=0xEF;seg[11]&=0xEF;seg[13]&=0xEF;seg[14]&=0xEF;seg[15]&=0xEF;
                    seg[8]|=0x10;seg[9]|=0x10;seg[11]|=0x10;seg[13]|=0x10;seg[14]|=0x10;seg[15]|=0x10;//数字0
                break;
            case 1:seg[11]&=0xEF;seg[13]&=0xEF;
                    seg[11]|=0x10;seg[13]|=0x10;//数字1
                break;
            case 2:seg[8]&=0xEF;seg[9]&=0xEF;seg[12]&=0xEF;seg[13]&=0xEF;seg[15]&=0xEF;
                    seg[8]|=0x10;seg[9]|=0x10;seg[12]|=0x10;seg[13]|=0x10;seg[15]|=0x10;//数字2
                break;
            case 3:seg[9]&=0xEF;seg[11]&=0xEF;seg[12]&=0xEF;seg[13]&=0xEF;seg[15]&=0xEF;
                    seg[9]|=0x10;seg[11]|=0x10;seg[12]|=0x10;seg[13]|=0x10;seg[15]|=0x10;//数字3
                break;	
            case 4:seg[11]&=0xEF;seg[12]&=0xEF;seg[13]&=0xEF;seg[14]&=0xEF;
                    seg[11]|=0x10;seg[12]|=0x10;seg[13]|=0x10;seg[14]|=0x10;//数字4
                break;	
            case 5:seg[9]&=0xEF;seg[11]&=0xEF;seg[12]&=0xEF;seg[14]&=0xEF;seg[15]&=0xEF;
                    seg[9]|=0x10;seg[11]|=0x10;seg[12]|=0x10;seg[14]|=0x10;seg[15]|=0x10;//数字5
                break;	
            case 6:seg[8]&=0xEF;seg[9]&=0xEF;seg[11]&=0xEF;seg[12]&=0xEF;seg[14]&=0xEF;seg[15]&=0xEF;
                    seg[8]|=0x10;seg[9]|=0x10;seg[11]|=0x10;seg[12]|=0x10;seg[14]|=0x10;seg[15]|=0x10;//数字6
                break;	
            case 7:seg[11]&=0xEF;seg[13]&=0xEF;seg[15]&=0xEF;
                    seg[11]|=0x10;seg[13]|=0x10;seg[15]|=0x10;//数字7
                break;	
            case 8:seg[8]&=0xEF;seg[9]&=0xEF;seg[11]&=0xEF;seg[12]&=0xEF;seg[13]&=0xEF;seg[14]&=0xEF;seg[15]&=0xEF;
                    seg[8]|=0x10;seg[9]|=0x10;seg[11]|=0x10;seg[12]|=0x10;seg[13]|=0x10;seg[14]|=0x10;seg[15]|=0x10;//数字8
                break;	
            case 9:seg[9]&=0xEF;seg[11]&=0xEF;seg[12]&=0xEF;seg[13]&=0xEF;seg[14]&=0xEF;seg[15]&=0xEF;
                    seg[9]|=0x10;seg[11]|=0x10;seg[12]|=0x10;seg[13]|=0x10;seg[14]|=0x10;seg[15]|=0x10;//数字9
                break;
            default:
                break;
        }		
        switch(H)
        {
            case 0:seg[8]&=0xDF;seg[9]&=0xDF;seg[11]&=0xDF;seg[13]&=0xDF;seg[14]&=0xDF;seg[15]&=0xDF;
                    seg[8]|=0x20;seg[9]|=0x20;seg[11]|=0x20;seg[13]|=0x20;seg[14]|=0x20;seg[15]|=0x20;//数字0
                break;
            case 1:seg[11]&=0xDF;seg[13]&=0xDF;
                    seg[11]|=0x20;seg[13]|=0x20;//数字1
                break;
            case 2:seg[8]&=0xDF;seg[9]&=0xDF;seg[12]&=0xDF;seg[13]&=0xDF;seg[15]&=0xDF;
                    seg[8]|=0x20;seg[9]|=0x20;seg[12]|=0x20;seg[13]|=0x20;seg[15]|=0x20;//数字2
                break;
            case 3:seg[9]&=0xDF;seg[11]&=0xDF;seg[12]&=0xDF;seg[13]&=0xDF;seg[15]&=0xDF;
                    seg[9]|=0x20;seg[11]|=0x20;seg[12]|=0x20;seg[13]|=0x20;seg[15]|=0x20;//数字3
                break;	
            case 4:seg[11]&=0xDF;seg[12]&=0xDF;seg[13]&=0xDF;seg[14]&=0xDF;
                    seg[11]|=0x20;seg[12]|=0x20;seg[13]|=0x20;seg[14]|=0x20;//数字4
                break;	
            case 5:seg[9]&=0xDF;seg[11]&=0xDF;seg[12]&=0xDF;seg[14]&=0xDF;seg[15]&=0xDF;
                    seg[9]|=0x20;seg[11]|=0x20;seg[12]|=0x20;seg[14]|=0x20;seg[15]|=0x20;//数字5
                break;	
            case 6:seg[8]&=0xDF;seg[9]&=0xDF;seg[11]&=0xDF;seg[12]&=0xDF;seg[14]&=0xDF;seg[15]&=0xDF;
                    seg[8]|=0x20;seg[9]|=0x20;seg[11]|=0x20;seg[12]|=0x20;seg[14]|=0x20;seg[15]|=0x20;//数字6
                break;	
            case 7:seg[11]&=0xDF;seg[13]&=0xDF;seg[15]&=0xDF;
                    seg[11]|=0x20;seg[13]|=0x20;seg[15]|=0x20;//数字7
                break;	
            case 8:seg[8]&=0xDF;seg[9]&=0xDF;seg[11]&=0xDF;seg[12]&=0xDF;seg[13]&=0xDF;seg[14]&=0xDF;seg[15]&=0xDF;
                    seg[8]|=0x20;seg[9]|=0x20;seg[11]|=0x20;seg[12]|=0x20;seg[13]|=0x20;seg[14]|=0x20;seg[15]|=0x20;//数字8
                break;	
            case 9:seg[9]&=0xDF;seg[11]&=0xDF;seg[12]&=0xDF;seg[13]&=0xDF;seg[14]&=0xDF;seg[15]&=0xDF;
                    seg[9]|=0x20;seg[11]|=0x20;seg[12]|=0x20;seg[13]|=0x20;seg[14]|=0x20;seg[15]|=0x20;//数字9
                break;
            default:
                break;
        }		
        switch(SM)
        {
            case 0:seg[8]&=0xBF;seg[9]&=0xBF;seg[11]&=0xBF;seg[13]&=0xBF;seg[14]&=0xBF;seg[15]&=0xBF;
                    seg[8]|=0x40;seg[9]|=0x40;seg[11]|=0x40;seg[13]|=0x40;seg[14]|=0x40;seg[15]|=0x40;//数字0
                break;
            case 1:seg[11]&=0xBF;seg[13]&=0xBF;
                    seg[11]|=0x40;seg[13]|=0x40;//数字1
                break;
            case 2:seg[8]&=0xBF;seg[9]&=0xBF;seg[12]&=0xBF;seg[13]&=0xBF;seg[15]&=0xBF;
                    seg[8]|=0x40;seg[9]|=0x40;seg[12]|=0x40;seg[13]|=0x40;seg[15]|=0x40;//数字2
                break;
            case 3:seg[9]&=0xBF;seg[11]&=0xBF;seg[12]&=0xBF;seg[13]&=0xBF;seg[15]&=0xBF;
                    seg[9]|=0x40;seg[11]|=0x40;seg[12]|=0x40;seg[13]|=0x40;seg[15]|=0x40;//数字3
                break;	
            case 4:seg[11]&=0xBF;seg[12]&=0xBF;seg[13]&=0xBF;seg[14]&=0xBF;
                    seg[11]|=0x40;seg[12]|=0x40;seg[13]|=0x40;seg[14]|=0x40;//数字4
                break;	
            case 5:seg[9]&=0xBF;seg[11]&=0xBF;seg[12]&=0xBF;seg[14]&=0xBF;seg[15]&=0xBF;
                    seg[9]|=0x40;seg[11]|=0x40;seg[12]|=0x40;seg[14]|=0x40;seg[15]|=0x40;//数字5
                break;	
            case 6:seg[8]&=0xBF;seg[9]&=0xBF;seg[11]&=0xBF;seg[12]&=0xBF;seg[14]&=0xBF;seg[15]&=0xBF;
                    seg[8]|=0x40;seg[9]|=0x40;seg[11]|=0x40;seg[12]|=0x40;seg[14]|=0x40;seg[15]|=0x40;//数字6
                break;	
            case 7:seg[11]&=0xBF;seg[13]&=0xBF;seg[15]&=0xBF;
                    seg[11]|=0x40;seg[13]|=0x40;seg[15]|=0x40;//数字7
                break;	
            case 8:seg[8]&=0xBF;seg[9]&=0xBF;seg[11]&=0xBF;seg[12]&=0xBF;seg[13]&=0xBF;seg[14]&=0xBF;seg[15]&=0xBF;
                    seg[8]|=0x40;seg[9]|=0x40;seg[11]|=0x40;seg[12]|=0x40;seg[13]|=0x40;seg[14]|=0x40;seg[15]|=0x40;//数字8
                break;	
            case 9:seg[9]&=0xBF;seg[11]&=0xBF;seg[12]&=0xBF;seg[13]&=0xBF;seg[14]&=0xBF;seg[15]&=0xBF;
                    seg[9]|=0x40;seg[11]|=0x40;seg[12]|=0x40;seg[13]|=0x40;seg[14]|=0x40;seg[15]|=0x40;//数字9
                break;
            default:
                break;
        }		
        switch(M)
        {
            case 0:seg[8]&=0x7F;seg[9]&=0x7F;seg[11]&=0x7F;seg[13]&=0x7F;seg[14]&=0x7F;seg[15]&=0x7F;
                    seg[8]|=0x80;seg[9]|=0x80;seg[11]|=0x80;seg[13]|=0x80;seg[14]|=0x80;seg[15]|=0x80;//数字0
                break;
            case 1:seg[11]&=0x7F;seg[13]&=0x7F;
                    seg[11]|=0x80;seg[13]|=0x80;//数字1
                break;
            case 2:seg[8]&=0x7F;seg[9]&=0x7F;seg[12]&=0x7F;seg[13]&=0x7F;seg[15]&=0x7F;
                    seg[8]|=0x80;seg[9]|=0x80;seg[12]|=0x80;seg[13]|=0x80;seg[15]|=0x80;//数字2
                break;
            case 3:seg[9]&=0x7F;seg[11]&=0x7F;seg[12]&=0x7F;seg[13]&=0x7F;seg[15]&=0x7F;
                    seg[9]|=0x80;seg[11]|=0x80;seg[12]|=0x80;seg[13]|=0x80;seg[15]|=0x80;//数字3
                break;	
            case 4:seg[11]&=0x7F;seg[12]&=0x7F;seg[13]&=0x7F;seg[14]&=0x7F;
                    seg[11]|=0x80;seg[12]|=0x80;seg[13]|=0x80;seg[14]|=0x80;//数字4
                break;	
            case 5:seg[9]&=0x7F;seg[11]&=0x7F;seg[12]&=0x7F;seg[14]&=0x7F;seg[15]&=0x7F;
                    seg[9]|=0x80;seg[11]|=0x80;seg[12]|=0x80;seg[14]|=0x80;seg[15]|=0x80;//数字5
                break;	
            case 6:seg[8]&=0x7F;seg[9]&=0x7F;seg[11]&=0x7F;seg[12]&=0x7F;seg[14]&=0x7F;seg[15]&=0x7F;
                    seg[8]|=0x80;seg[9]|=0x80;seg[11]|=0x80;seg[12]|=0x80;seg[14]|=0x80;seg[15]|=0x80;//数字6
                break;	
            case 7:seg[11]&=0x7F;seg[13]&=0x7F;seg[15]&=0x7F;
                    seg[11]|=0x80;seg[13]|=0x80;seg[15]|=0x80;//数字7
                break;	
            case 8:seg[8]&=0x7F;seg[9]&=0x7F;seg[11]&=0x7F;seg[12]&=0x7F;seg[13]&=0x7F;seg[14]&=0x7F;seg[15]&=0x7F;
                    seg[8]|=0x80;seg[9]|=0x80;seg[11]|=0x80;seg[12]|=0x80;seg[13]|=0x80;seg[14]|=0x80;seg[15]|=0x80;//数字8
                break;	
            case 9:seg[9]&=0x7F;seg[11]&=0x7F;seg[12]&=0x7F;seg[13]&=0x7F;seg[14]&=0x7F;seg[15]&=0x7F;
                    seg[9]|=0x80;seg[11]|=0x80;seg[12]|=0x80;seg[13]|=0x80;seg[14]|=0x80;seg[15]|=0x80;//数字9
                break;
            default:
                break;
        }	
    }
    else
    {
        seg[8]&=0x0F;seg[9]&=0x0F;seg[11]&=0x0F;seg[12]&=0x0F;seg[13]&=0x0F;seg[14]&=0x0F;seg[15]&=0x0F;
        seg[8]|=0x00;seg[9]|=0x00;seg[11]|=0x00;seg[12]|=0xF0;seg[13]|=0x00;seg[14]|=0x00;seg[15]|=0x00;//显示“-- --”
    }    
    
    /**********设定时间冒号**********/
    seg[10]&=0xDF;seg[10]|=0x20;
    /**********实际时间冒号**********/
    seg[10]&=0xFD;seg[10]|=0x02;
    
	
	
	TM1640_Write_DATA(cnt, seg[cnt]);
	cnt ++;
	if(cnt >= 16)
		cnt= 0;
//	TM1640_Write_DATA(1, seg[1]);
//	TM1640_Write_DATA(2, seg[2]);
//	TM1640_Write_DATA(3, seg[3]);
//	TM1640_Write_DATA(4, seg[4]);
//	TM1640_Write_DATA(5, seg[5]);
//	TM1640_Write_DATA(6, seg[6]);
//	TM1640_Write_DATA(7, seg[7]);
//	TM1640_Write_DATA(8, seg[8]);
//	TM1640_Write_DATA(9, seg[9]);
//    TM1640_Write_DATA(10, seg[10]);
//	TM1640_Write_DATA(11, seg[11]);
//	TM1640_Write_DATA(12, seg[12]);
//	TM1640_Write_DATA(13, seg[13]);
//	TM1640_Write_DATA(14, seg[14]);
//    TM1640_Write_DATA(15, seg[15]);
}

/*
*****************************************************************
 * 函数原型：void Deal_Speed(float dT)
 * 功    能：速度显示处理
*****************************************************************
*/
int16_t Speed_CalVal;//计算后的速度
void Deal_Speed(float dT)
{
    if(sys.Run_Status)//启动的情况下
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
			Speed_Arg.Kp = 20 * 0.001f;
			Speed_Arg.Ki = 44 * 0.001f;
		}
		if(Speed.ADDMode==1)//在进入加速模式下
		{
			Speed_Arg.Kp = 20 * 0.001f;
			Speed_Arg.Ki = 44 * 0.001f;
            if(Speed.Rel > 2000)
                Speed_CalVal = 2000 + ((Speed.Rel - 2000) * 2);
            else
                Speed_CalVal = Speed.Rel;
			Speed.New = Speed_CalVal;//记录当前速度
            
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
            if(Speed.Rel > 2000)
                Speed_CalVal = 2000 + ((Speed.Rel - 2000) * 2);
            else
                Speed_CalVal = Speed.Rel;
            Speed.New = Speed_CalVal;//记录当前速度
            
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
			Speed_Arg.Kp = 5 * 0.001f;
			Speed_Arg.Ki = 10 * 0.001f;
        }
	}
	else
	{
		Speed.Display_Rel = 0;//实际速度显示为零
		Speed.New =0;//现在的速度清零
		Speed.ADDMode = 0;//清除显示处理
	}
}

/*
*****************************************************************
 * 函数原型：void Show_Display(void)
 * 功    能：显示屏幕内容
*****************************************************************
*/
void Show_Display(void)
{	
    Speed.Display_Set = Speed.Set;//显示设定速度
	Time.Display_Set = Time.Set;//显示设定时间
	Time.Display_Rel = Time.Rel + 59;//显示实际时间+59s
    Display_Screen(Speed.Display_Set,Speed.Display_Rel,Time.Display_Set,Time.Display_Rel);
}
