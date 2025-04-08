#include "Show_9.h"

/**********全局变量声明******/
uint16_t Twinkle_Time;//闪烁时间
uint8_t Tab[] = {0x77,0x12,0x6B,0x5B,0x1E,0x5D,0x7D,0x13,0x7F,0x5F};//0·9
uint8_t Tab1[] = {0xEE,0x48,0xD6,0xDA,0x78,0xBA,0xBE,0xC8,0xFE,0xFA};//0·9

/**********局部变量声明******/
uint8_t seg15_Flag;//用于显示屏实际速度最后一位中间的斜杠个其他的相差太远
uint8_t Speed_ShowFlag,Temp_ShowFlag,Time_ShowFlag;//速度、温度、时间显示的标志位 0:常亮 1：熄灭
uint8_t Work_All_Time;//全部工位设置时闪烁的工位时间
uint8_t Speed_Icn,Run_Flag;//运行闪烁图标

/*
*****************************************************************
 * 函数原型： void Check_ShowFlag(uint16_t dT)
 * 功    能： 闪烁检测
 * 输    入:  dT:执行周期
 * 参    数： uint16_t dT
*****************************************************************
*/
void Check_ShowFlag(uint16_t dT)
{
    if(Work_All)//进入全家设置
        Work_All_Time = ~Work_All_Time;//选中工位下闪烁
    if(Run_Status)//运行时
	{
		Speed_Icn++;
		if(Speed_Icn>3)
			Speed_Icn = 1;
        Run_Flag = ~Run_Flag;//运行时闪烁
	}
	else
	{
		Run_Flag = 0;
		Speed_Icn = 0;
	}
    if(SetMode_Option == 0)//如果没在设置选项中，则都点亮，不闪烁
    {
        Speed_ShowFlag = 0;//常亮
        Temp_ShowFlag = 0;//常亮
        Time_ShowFlag = 0;//常亮
        Twinkle_Time = 0;//闪烁计时清零
        return;
    }
    if(Twinkle_Time && EC11A_Knob==0)//闪烁和没有操作旋钮时
    {
        Twinkle_Time -= dT;//闪烁计时
        if(SetMode_Option == 1)//设置速度
        {
            Speed_ShowFlag = ~Speed_ShowFlag;//速度闪烁
            Temp_ShowFlag = 0;//温度常亮
            Time_ShowFlag = 0;//时间常亮
        }
        else if(SetMode_Option == 2)//设置温度
        {
            Speed_ShowFlag = 0;//速度常亮
            Temp_ShowFlag = ~Temp_ShowFlag;//温度闪烁
            Time_ShowFlag = 0;//时间常亮
        }
        else if(SetMode_Option == 3)//设置时间
        {
            Speed_ShowFlag = 0;//速度常亮
            Temp_ShowFlag = 0;//温度常亮
            Time_ShowFlag = ~Time_ShowFlag;//时间闪烁
        }
        if(Twinkle_Time == 0)//如果闪烁结束
        {
            SetMode_Option = 0;//模式选择清零
        }        
    }
}

/*
*****************************************************************
 * 函数原型： void LCD_Light(short LCD_Status) 
 * 功    能： 打开和关闭背光显示
 * 输    入:  LCD_Status：1、打开背光 0：关闭背光
 * 参    数： short LCD_Status
*****************************************************************
*/
void LCD_Light(short LCD_Status)
{
    switch(LCD_Status)
    {
        case 0 :__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 0); break ;//不输出pwm    
        case 1 :
            HAL_GPIO_WritePin(LED_KEY_GPIO_Port, LED_KEY_Pin, GPIO_PIN_RESET);//拉低背光电平信号
            __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 105);//不输出pwm
            break ;
    }
}

/*
*****************************************************************
 * 函数原型：void Display_Speed_One(uint16_t Speed_L1,uint16_t Speed_L2,uint16_t Speed_L3)
 * 功    能：显示第一行的设定速度和下划线和中间的图标
 * 输    入: Speed_L1 L1的速度 Speed_L2 L2的速度 Speed_L3 L3的速度
 * 参    数：uint16_t Speed_L1,uint16_t Speed_L2,uint16_t Speed_L3
*****************************************************************
*/
void Display_Speed_One(uint16_t Speed_L1,uint16_t Speed_L2,uint16_t Speed_L3)
{
	uint8_t seg1,seg2,seg3,seg4,seg5,seg6,seg7,seg8,seg9,seg10;
	seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;seg7=0;seg8=0;seg9=0;seg10=0;
	uint16_t Val;//用于百十个取出来的数字
	
	/***********L1转速计算**********/
	/***********Ll千位***********/
	if(Speed_L1 > 999)//大于999时
	{		
		seg3&=0x7F;seg3|=0x80;//显示1
	}
	else//小于999时
    {
        seg3&=0x7F;seg3|=0x00;//不显示
    }
	/***********Ll百位***********/
	if(Speed_L1 > 99)//大于99时
	{
		Val=Speed_L1/100;//取出百位的数字
		if(Speed_L1 > 999)//大于999时
			Val=Val%10;//取出百位
		seg3&=0x80;seg3|=Tab[Val];//数字	
	}
	else
	{
		seg3&=0x80;seg3|=Tab[0];//数字0	
	}
	/***********Ll十位***********/
	if(Speed_L1 > 9)//大于9时
	{
		Val=Speed_L1/10;//取出十位的数字
		if(Speed_L1 > 99)//大于99时
			Val=Val%10;//取出十位
		seg4&=0x80;seg4|=Tab[Val];//数字	
	}
	else
	{
		seg4&=0x80;seg4|=Tab[0];//数字0
	}
	/***********L1个位***********/
	seg4&=0x7F;seg4|=0x80;//数字0
	
	/***********L2转速计算**********/
	/***********L2千位***********/
	if(Speed_L2 > 999)//大于999时
	{		
		seg5&=0x7F;seg5|=0x80;//显示1
	}
	else//小于999时
    {
        seg5&=0x7F;seg5|=0x00;//不显示
    }
	/***********L2百位***********/
	if(Speed_L2 > 99)//大于99时
	{
		Val=Speed_L2/100;//取出百位的数字
		if(Speed_L2 > 999)//大于999时
			Val=Val%10;//取出百位
		seg5&=0x80;seg5|=Tab[Val];//数字	
	}
	else
	{
		seg5&=0x80;seg5|=Tab[0];//数字0
	}
	/***********L2十位***********/
	if(Speed_L2 > 9)//大于9时
	{
		Val=Speed_L2/10;//取出十位的数字
		if(Speed_L2 > 99)//大于99时
			Val=Val%10;//取出十位
		seg6&=0x80;seg6|=Tab[Val];//数字	
	}
	else
	{
		seg6&=0x80;seg6|=Tab[0];//数字0
	}
	/***********L2个位***********/
	seg6&=0x7F;seg6|=0x80;//数字0
	
	/***********L3转速计算**********/
	/***********L3千位***********/
	if(Speed_L3 > 999)//大于999时
	{		
		seg7&=0x7F;seg7|=0x80;//显示1
	}
	else//小于999时
    {
        seg7&=0x7F;seg7|=0x00;//不显示
    }
	/***********L3百位***********/
	if(Speed_L3 > 99)//大于99时
	{
		Val=Speed_L3/100;//取出百位的数字
		if(Speed_L3 > 999)//大于999时
			Val=Val%10;//取出百位
		seg7&=0x80;seg7|=Tab[Val];//数字	
	}
	else
	{
		seg7&=0x80;seg7|=Tab[0];//数字0
	}
	/***********L3十位***********/
	if(Speed_L3 > 9)//大于9时
	{
		Val=Speed_L3/10;//取出十位的数字
		if(Speed_L3 > 99)//大于99时
			Val=Val%10;//取出十位
		seg8&=0x80;seg8|=Tab[Val];//数字
	}
	else
	{
		seg8&=0x80;seg8|=Tab[0];//数字0
	}
	/***********L3个位***********/
	seg8&=0x7F;seg8|=0x80;//数字0
	
	if(Work_All)//在全局设置时
    {
		seg10&=0x1F;seg10|=0xE0;//L1和L2和L3的下划线点亮
		seg2&=0xF8;seg2|=0x07;//L4和L5和L6的下划线点亮
        seg1&=0xF8;seg1|=0x07;//L7和L8和L9的下划线点亮
        if(Work_All_Time)//在全局设置下选中工位闪烁
        {        
            switch(Work_Option)
            {
                case 1:seg10&=0x1F;seg10|=0xC0;//L1下划线熄灭
                    break;
				case 2:seg10&=0x1F;seg10|=0xA0;//L2下划线熄灭
                    break;
				case 3:seg10&=0x1F;seg10|=0x60;//L3下划线熄灭
                    break;
                case 4:seg2&=0xF8;seg2|=0x06;//L4下划线熄灭
                    break;
                case 5:seg2&=0xF8;seg2|=0x05;//L5下划线熄灭
                    break;
				case 6:seg2&=0xF8;seg2|=0x03;//L6下划线熄灭
                    break;
				case 7:seg1&=0xF8;seg1|=0x06;//L7下划线熄灭
                    break;
                case 8:seg1&=0xF8;seg1|=0x05;//L8下划线熄灭
                    break;
				case 9:seg1&=0xF8;seg1|=0x03;//L9下划线熄灭
                    break;
                default:
					seg10&=0x1F;seg10|=0xE0;//L1和L2和L3的下划线点亮
					seg2&=0xF8;seg2|=0x07;//L4和L5和L6的下划线点亮
					seg1&=0xF8;seg1|=0x07;//L7和L8和L9的下划线点亮
                    break;
            }
        }
    }
    else
    {		 		 
        switch(Work_Option)//工位号选择
        {
            case 1: seg10&=0x1F;seg10|=0x20;
					seg2&=0xF8;seg2|=0x00;
					seg1&=0xF8;seg1|=0x00;//显示L1下面的下划线
                break;
            case 2: seg10&=0x1F;seg10|=0x40;
					seg2&=0xF8;seg2|=0x00;
					seg1&=0xF8;seg1|=0x00;//显示L2下面的下划线
                break;
            case 3: seg10&=0x1F;seg10|=0x80;
					seg2&=0xF8;seg2|=0x00;
					seg1&=0xF8;seg1|=0x00;//显示L3下面的下划线
					break;
			case 4: seg10&=0x1F;seg10|=0x00;
					seg2&=0xF8;seg2|=0x01;
					seg1&=0xF8;seg1|=0x00;//显示L4面的下划线
					break;
			case 5: seg10&=0x1F;seg10|=0x00;
					seg2&=0xF8;seg2|=0x02;
					seg1&=0xF8;seg1|=0x00;//显示L5面的下划线
					break;
			case 6: seg10&=0x1F;seg10|=0x00;
					seg2&=0xF8;seg2|=0x04;
					seg1&=0xF8;seg1|=0x00;//显示L6面的下划线
					break;
			case 7: seg10&=0x1F;seg10|=0x00;
					seg2&=0xF8;seg2|=0x00;
					seg1&=0xF8;seg1|=0x01;//显示L7面的下划线
					break;
			case 8: seg10&=0x1F;seg10|=0x00;
					seg2&=0xF8;seg2|=0x00;
					seg1&=0xF8;seg1|=0x02;//显示L8面的下划线
					break;
			case 9: seg10&=0x1F;seg10|=0x00;
					seg2&=0xF8;seg2|=0x00;
					seg1&=0xF8;seg1|=0x04;//显示L9面的下划线
					break;
            default:     
                break;
        }
    }	
	if(Run_Status==1 && Speed_Icn > 0 && Set_Speed.L0 > 0 && Rel_Speed.L0)  //运行时
    {
        if(Speed_Icn == 1)
		{
			seg9&=0xF8;seg9|=0x03;
		}
		else if(Speed_Icn == 2)
		{
			seg9&=0xF8;seg9|=0x06;
		}
		else if(Speed_Icn == 3)
		{
			seg9&=0xF8;seg9|=0x05;
		}  
    }
	else
	{
		seg9&=0xF8;seg9|=0x07;
	}
	#if(Temp_TYPE == 1)//设置成为加热款
	seg9&=0xE7;seg9|=0x18;//温度图标
	if(Run_Status == 1 && Temp_State == 1 && Run_Flag > 1)//运行时
    {
        seg9&=0xE7;seg9|=0x00;//温度图标消失
    }
	#endif
	seg9&=0xDF;seg9|=0x20;//时间图标
	if(Run_Status == 1 && Run_Flag > 1 && DownTime_Over.L0 == 0 && RelTime_State.L0 == 1)//运行时
    {
        seg9&=0xDF;seg9|=0x00;//时间图标消失
    }
	Write_Addr_Dat_N(0, seg1, 1);
	Write_Addr_Dat_N(1, seg2, 1);
	Write_Addr_Dat_N(2, seg3, 1);
	Write_Addr_Dat_N(3, seg4, 1);
	Write_Addr_Dat_N(4, seg5, 1);
	Write_Addr_Dat_N(5, seg6, 1);
	Write_Addr_Dat_N(6, seg7, 1);
	Write_Addr_Dat_N(7, seg8, 1);
	Write_Addr_Dat_N(8, seg9, 1);
	Write_Addr_Dat_N(25, seg10, 1);//L1\L2\L3的下划线
}

/*
*****************************************************************
 * 函数原型：void Display_Speed_Two(uint16_t Speed_L4,uint16_t Speed_L5,uint16_t Speed_L6)
 * 功    能：显示第二行的设定速度
 * 输    入: Speed_L4 L4的速度 Speed_L5 L5的速度 Speed_L6 L6的速度
 * 参    数：uint16_t Speed_L4,uint16_t Speed_L5,uint16_t Speed_L6
*****************************************************************
*/
void Display_Speed_Two(uint16_t Speed_L4,uint16_t Speed_L5,uint16_t Speed_L6)
{
	uint8_t seg1,seg2,seg3,seg4,seg5,seg6;
	seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;
	uint16_t Val;//用于百十个取出来的数字
	
	/***********L4转速计算**********/
	/***********L4千位***********/
	if(Speed_L4 > 999)//大于999时
	{		
		seg1&=0xFE;seg1|=0x01;//显示1
	}
	else//小于999时
    {
        seg1&=0xFE;seg1|=0x00;//不显示
    }
	/***********L4百位***********/
	if(Speed_L4 > 99)//大于99时
	{
		Val=Speed_L4/100;//取出百位的数字
		if(Speed_L4 > 999)//大于999时
			Val=Val%10;//取出百位
		seg1&=0x01;seg1|=Tab1[Val];//数字
	}
	else
	{
		seg1&=0x01;seg1|=Tab1[0];//数字0
	}
	/***********L4十位***********/
	if(Speed_L4 > 9)//大于9时
	{
		Val=Speed_L4/10;//取出十位的数字
		if(Speed_L4 > 99)//大于99时
			Val=Val%10;//取出十位
		seg2&=0x01;seg2|=Tab1[Val];//数字	
	}
	else
	{
		seg2&=0x01;seg2|=Tab1[0];//数字0	
	}
	/***********L4个位***********/
	seg2&=0xFE;seg2|=0x01;//数字0
	
	/***********L5转速计算**********/
	/***********L5千位***********/
	if(Speed_L5 > 999)//大于999时
	{		
		seg3&=0xFE;seg3|=0x01;//显示1
	}
	else//小于999时
    {
        seg3&=0xFE;seg3|=0x00;//不显示
    }
	/***********L5百位***********/
	if(Speed_L5 > 99)//大于99时
	{
		Val=Speed_L5/100;//取出百位的数字
		if(Speed_L5 > 999)//大于999时
			Val=Val%10;//取出百位
		seg3&=0x01;seg3|=Tab1[Val];//数字
	}
	else
	{
		seg3&=0x01;seg3|=Tab1[0];//数字0
	}
	/***********L5十位***********/
	if(Speed_L5 > 9)//大于9时
	{
		Val=Speed_L5/10;//取出十位的数字
		if(Speed_L5 > 99)//大于99时
			Val=Val%10;//取出十位
		seg4&=0x01;seg4|=Tab1[Val];//数字
	}
	else
	{
		seg4&=0x01;seg4|=Tab1[0];//数字0
	}
	/***********L5个位***********/
	seg4&=0xFE;seg4|=0x01;//数字0
	
	/***********L6转速计算**********/
	/***********L6千位***********/
	if(Speed_L6 > 999)//大于999时
	{		
		seg5&=0xFE;seg5|=0x01;//显示1
	}
	else//小于999时
    {
        seg5&=0xFE;seg5|=0x00;//不显示
    }
	/***********L6百位***********/
	if(Speed_L6 > 99)//大于99时
	{
		Val=Speed_L6/100;//取出百位的数字
		if(Speed_L6 > 999)//大于999时
			Val=Val%10;//取出百位
		seg5&=0x01;seg5|=Tab1[Val];//数字
	}
	else
	{
		seg5&=0x01;seg5|=Tab1[0];//数字0
	}
	/***********L6十位***********/
	if(Speed_L6 > 9)//大于9时
	{
		Val=Speed_L6/10;//取出十位的数字
		if(Speed_L6 > 99)//大于99时
			Val=Val%10;//取出十位
		seg6&=0x01;seg6|=Tab1[Val];//数字	
	}
	else
	{
		seg6&=0x01;seg6|=Tab1[0];//数字0
	}
	/***********L6个位***********/
	seg6&=0xFE;seg6|=0x01;//数字0
	
	Write_Addr_Dat_N(26, seg1, 1);
	Write_Addr_Dat_N(27, seg2, 1);
	Write_Addr_Dat_N(28, seg3, 1);
	Write_Addr_Dat_N(29, seg4, 1);
	Write_Addr_Dat_N(30, seg5, 1);
	Write_Addr_Dat_N(31, seg6, 1);
}

/*
*****************************************************************
 * 函数原型：void Display_Speed_Three(uint16_t Speed_L7,uint16_t Speed_L8,uint16_t Speed_L9)
 * 功    能：显示第三行的设定速度
 * 输    入: Speed_L7 L7的速度 Speed_L8 L8的速度 Speed_L9 L9的速度
 * 参    数：uint16_t Speed_L7,uint16_t Speed_L8,uint16_t Speed_L9
*****************************************************************
*/
void Display_Speed_Three(uint16_t Speed_L7,uint16_t Speed_L8,uint16_t Speed_L9)
{
	uint8_t seg1,seg2,seg3,seg4,seg5,seg6;
	seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;
	uint16_t Val;//用于百十个取出来的数字
	
	/***********L7转速计算**********/
	/***********L7千位***********/
	if(Speed_L7 > 999)//大于999时
	{		
		seg1&=0xFE;seg1|=0x01;//显示1
	}
	else//小于999时
    {
        seg1&=0xFE;seg1|=0x00;//不显示
    }
	/***********L7百位***********/
	if(Speed_L7 > 99)//大于99时
	{
		Val=Speed_L7/100;//取出百位的数字
		if(Speed_L7 > 999)//大于999时
			Val=Val%10;//取出百位
		seg1&=0x01;seg1|=Tab1[Val];//数字
	}
	else
	{
		seg1&=0x01;seg1|=Tab1[0];//数字0
	}
	/***********L7十位***********/
	if(Speed_L7 > 9)//大于9时
	{
		Val=Speed_L7/10;//取出十位的数字
		if(Speed_L7 > 99)//大于99时
			Val=Val%10;//取出十位
		seg2&=0x01;seg2|=Tab1[Val];//数字
	}
	else
	{
		seg2&=0x01;seg2|=Tab1[0];//数字0
	}	
	/***********L7个位***********/
	seg2&=0xFE;seg2|=0x01;//数字0
	
	/***********L8转速计算**********/
	/***********L8千位***********/
	if(Speed_L8 > 999)//大于999时
	{		
		seg3&=0xFE;seg3|=0x01;//显示1
	}
	else//小于999时
    {
        seg3&=0xFE;seg3|=0x00;//不显示
    }
	/***********L8百位***********/
	if(Speed_L8 > 99)//大于99时
	{
		Val=Speed_L8/100;//取出百位的数字
		if(Speed_L8 > 999)//大于999时
			Val=Val%10;//取出百位
		seg3&=0x01;seg3|=Tab1[Val];//数字
	}
	else
	{
		seg3&=0x01;seg3|=Tab1[0];//数字0
	}
	/***********L8十位***********/
	if(Speed_L8 > 9)//大于9时
	{
		Val=Speed_L8/10;//取出十位的数字
		if(Speed_L8 > 99)//大于99时
			Val=Val%10;//取出十位
		seg4&=0x01;seg4|=Tab1[Val];//数字
	}
	else
	{
		seg4&=0x01;seg4|=Tab1[0];//数字0
	}
	/***********L8个位***********/
	seg4&=0xFE;seg4|=0x01;//数字0
	
	/***********L9转速计算**********/
	/***********L9千位***********/
	if(Speed_L9 > 999)//大于999时
	{		
		seg5&=0xFE;seg5|=0x01;//显示1
	}
	else//小于999时
    {
        seg5&=0xFE;seg5|=0x00;//不显示
    }
	/***********L9百位***********/
	if(Speed_L9 > 99)//大于99时
	{
		Val=Speed_L9/100;//取出百位的数字
		if(Speed_L9 > 999)//大于999时
			Val=Val%10;//取出百位
		seg5&=0x01;seg5|=Tab1[Val];//数字
	}
	else
	{
		seg5&=0x01;seg5|=Tab1[0];//数字0
	}
	/***********L9十位***********/
	if(Speed_L9 > 9)//大于9时
	{
		Val=Speed_L9/10;//取出十位的数字
		if(Speed_L9 > 99)//大于99时
			Val=Val%10;//取出十位
		seg6&=0x01;seg6|=Tab1[Val];//数字
	}
	else
	{
		seg6&=0x01;seg6|=Tab1[0];//数字0
	}
	/***********L9个位***********/
	seg6&=0xFE;seg6|=0x01;//数字0
	
	Write_Addr_Dat_N(32, seg1, 1);
	Write_Addr_Dat_N(33, seg2, 1);
	Write_Addr_Dat_N(34, seg3, 1);
	Write_Addr_Dat_N(35, seg4, 1);
	Write_Addr_Dat_N(36, seg5, 1);
	Write_Addr_Dat_N(37, seg6, 1);
}

/*
*****************************************************************
 * 函数原型：void Display_Speed_Val(uint16_t dis_speed_rel,uint16_t dis_speed_set)
 * 功    能：显示当前工位的实际速度和设定速度
 * 输    入: dis_speed_rel 实际速度  dis_speed_set 设定速度
 * 参    数：uint16_t dis_speed_rel,uint16_t dis_speed_set
*****************************************************************
*/
void Display_Speed_Val(uint16_t dis_speed_rel,uint16_t dis_speed_set)
{
	uint8_t seg1,seg2,seg3,seg4;
	seg1=0;seg2=0;seg3=0;seg4=0;
	uint16_t Val;//用于百十个取出来的数字
	
	/***********speed_rel转速计算**********/
	/***********speed_rel千位***********/
	if(dis_speed_rel > 999)//大于999时
	{		
		seg1&=0x7F;seg1|=0x80;//显示1
	}
	else//小于999时
    {
        seg1&=0x7F;seg1|=0x00;//不显示
    }
	/***********speed_rel百位***********/
	if(dis_speed_rel > 99)//大于99时
	{
		Val=dis_speed_rel/100;//取出百位的数字
		if(dis_speed_rel > 999)//大于999时
			Val=Val%10;//取出百位
		seg1&=0x80;seg1|=Tab[Val];//数字
	}
	else
	{
		seg1&=0x80;seg1|=Tab[0];//数字0
	}
	/***********speed_rel十位***********/
	if(dis_speed_rel > 9)//大于9时
	{
		Val=dis_speed_rel/10;//取出十位的数字
		if(dis_speed_rel > 99)//大于99时
			Val=Val%10;//取出十位
		seg2&=0x80;seg2|=Tab[Val];//数字
	}
	else
	{
		seg2&=0x80;seg2|=Tab[0];//数字0
	}
	/***********speed_rel个位***********/
	seg2&=0x7F;seg2|=0x80;//数字0
	
	/***********speed_set转速计算**********/
	/***********speed_set千位***********/
	if(dis_speed_set > 999)//大于999时
	{		
		seg3&=0x7F;seg3|=0x80;//显示1
	}
	else//小于999时
    {
        seg3&=0x7F;seg3|=0x00;//不显示
    }
	/***********speed_set百位***********/
	if(dis_speed_set > 99)//大于99时
	{
		Val=dis_speed_set/100;//取出百位的数字
		if(dis_speed_set > 999)//大于999时
			Val=Val%10;//取出百位
		seg3&=0x80;seg3|=Tab[Val];//数字
	}
	else
	{
		seg3&=0x80;seg3|=Tab[0];//数字0
	}
	/***********speed_set十位***********/
	if(dis_speed_set > 9)//大于9时
	{
		Val=dis_speed_set/10;//取出十位的数字
		if(dis_speed_set > 99)//大于99时
			Val=Val%10;//取出十位
		seg4&=0x80;seg4|=Tab[Val];//数字
	}
	else
	{
		seg4&=0x80;seg4|=Tab[0];//数字0
	}
	/***********speed_set个位***********/
	seg4&=0x7F;seg4|=0x80;//数字0
	
	if(SetMode_Option == 1)
    {
        if(Speed_ShowFlag && EC11A_Knob == 0)//时间到和旋钮无操作时
        {
            seg3&=0x00;seg3|=0x00;seg4&=0x00;seg4|=0x00;
        }
    }  
	
	Write_Addr_Dat_N(9, seg1, 1);
	Write_Addr_Dat_N(10, seg2, 1);
	Write_Addr_Dat_N(11, seg3, 1);
	Write_Addr_Dat_N(12, seg4, 1);
}

/*
*****************************************************************
 * 函数原型：void Display_Temp_Val(int dis_temp_rel,int dis_temp_set)
 * 功    能：显示当前工位的实际温度和设定温度
 * 输    入: dis_temp_rel 实际温度  dis_temp_set 设定温度
 * 参    数：int dis_temp_rel,int dis_temp_set
*****************************************************************
*/
void Display_Temp_Val(int dis_temp_rel,int dis_temp_set)
{
	uint8_t seg1,seg2,seg3,seg4,seg5,seg6;
	seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;
	uint16_t Val;//用于百十个取出来的数字
	
	/***********temp_rel温度计算**********/
	/***********temp_rel千位***********/
	if(dis_temp_rel > 999)//大于999时
	{		
		seg1&=0x7F;seg1|=0x80;//显示1
	}
	else//小于999时
    {
        seg1&=0x7F;seg1|=0x00;//不显示
    }
	/***********temp_rel百位***********/
	if(dis_temp_rel > 99)//大于99时
	{
		Val=dis_temp_rel/100;//取出百位的数字
		if(dis_temp_rel > 999)//大于999时
			Val=Val%10;//取出百位
		seg1&=0x80;seg1|=Tab[Val];//数字	
	}
	else
	{
		seg1&=0x80;seg1|=0x00;//不显示
	}
	/***********temp_rel十位***********/
	if(dis_temp_rel > 9)//大于9时
	{
		Val=dis_temp_rel/10;//取出十位的数字
		if(dis_temp_rel > 99)//大于99时
			Val=Val%10;//取出十位
		seg2&=0x80;seg2|=Tab[Val];//数字	
	}
	else
	{
		seg2&=0x80;seg2|=Tab[0];//数字0
	}
	/***********temp_rel个位***********/
	if(dis_temp_rel > 9)//大于9时
	{
		Val=dis_temp_rel%10;//取出个位
		seg3&=0x80;seg3|=Tab[Val];//数字
	}
	else
	{
		seg3&=0x80;seg3|=Tab[0];//数字0
	}
	
	/***********temp_set温度计算**********/
	/***********temp_set千位***********/
	if(dis_temp_set > 999)//大于999时
	{		
		seg4&=0x7F;seg4|=0x80;//显示1
	}
	else//小于999时
    {
        seg4&=0x7F;seg4|=0x00;//不显示
    }
	/***********temp_set百位***********/
	if(dis_temp_set > 99)//大于99时
	{
		Val=dis_temp_set/100;//取出百位的数字
		if(dis_temp_set > 999)//大于999时
			Val=Val%10;//取出百位
		seg4&=0x80;seg4|=Tab[Val];//数字	
	}
	else
	{
		seg4&=0x80;seg4|=0x00;//不显示
	}
	/***********temp_set十位***********/
	if(dis_temp_set > 9)//大于9时
	{
		Val=dis_temp_set/10;//取出十位的数字
		if(dis_temp_set > 99)//大于99时
			Val=Val%10;//取出十位
		seg5&=0x80;seg5|=Tab[Val];//数字	
	}
	else
	{
		seg5&=0x80;seg5|=Tab[0];//数字0	
	}
	
	/***********temp_set个位***********/
	if(dis_temp_set > 9)//大于9时
	{
		Val=dis_temp_set%10;//取出个位
		seg6&=0x80;seg6|=Tab[Val];//数字
	}
	else
	{
		seg6&=0x80;seg6|=Tab[0];//数字0
	}
	seg2&=0x7F;seg2|=0x80;//实际温度的小数点
	seg3&=0x7F;seg3|=0x80;//显示rpm
	seg5&=0x7F;seg5|=0x80;//设定温度的小数点
	seg6&=0x7F;seg6|=0x80;//显示℃
	
	if(Temp_State == 0)//温度设置大于0时
    {
		/*温度没设置时----*/	
		seg4&=0x00;seg4|=0x08;seg5&=0x80;seg5|=0x08;seg6&=0x80;seg6|=0x08;//数字0
    }        
    if(SetMode_Option == 2)//在设定温度时
    {
        if(Temp_ShowFlag && EC11A_Knob == 0)//时间到和旋钮无操作时
        {
            seg4&=0x00;seg4|=0x00;seg5&=0x80;seg5|=0x00;seg6&=0x80;seg6|=0x00;//数字0
		}
    }
	
	#if(Temp_TYPE == 0)//设置成四联普通款时
        seg1&=0x00;seg1|=0x00;seg2&=0x00;seg2|=0x00;seg3&=0x80;seg3|=0x00;seg4&=0x00;seg4|=0x00;seg5&=0x00;seg5|=0x00;seg6&=0x00;seg6|=0x00;//隐藏温度数码管
    #endif
	
	Write_Addr_Dat_N(13, seg1, 1);
	Write_Addr_Dat_N(14, seg2, 1);
	Write_Addr_Dat_N(15, seg3, 1);
	Write_Addr_Dat_N(16, seg4, 1);
	Write_Addr_Dat_N(17, seg5, 1);
	Write_Addr_Dat_N(18, seg6, 1);
}

/*
*****************************************************************
 * 函数原型：void Display_Time_Val(uint32_t dis_time_rel,uint32_t dis_time_set)
 * 功    能：显示当前工位的实际时间和设定时间
 * 输    入: dis_time_rel 实际时间  dis_time_set 设定时间
 * 参    数：uint32_t dis_time_rel,uint32_t dis_time_set
*****************************************************************
*/
void Display_Time_Val(uint32_t dis_time_rel,uint32_t dis_time_set)
{
	uint8_t seg1,seg2,seg3,seg4,seg5,seg6;
	seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;
	uint8_t SH,H,SM,M;//时间的单位取值

	/***********time_rel时间计算**********/
	SH=dis_time_rel/3600/10;//计算十位单位的小时数
	H=dis_time_rel/3600%10;//计算个位单位的小时数
	SM=dis_time_rel%3600/60/10;//计算十分位单位的分钟数
	M=dis_time_rel%3600/60%10;//计算个分位单位的分钟数
	/***********time_rel第一位位***********/
	if(SH)//大于等于10小时时 就是9小时59分59秒
	{		
		seg1&=0x7F;seg1|=0x80;//显示1
	}
	else//小于999时
    {
        seg1&=0x7F;seg1|=0x00;//不显示
    }
	/***********time_rel第二位***********/
	seg1&=0x80;seg1|=Tab[H];//数字	
	
	/***********time_rel十位***********/
	seg2&=0x80;seg2|=Tab[SM];//数字	
	
	/***********time_rel个位***********/
	seg3&=0x80;seg3|=Tab[M];//数字	
	
	/***********time_set转速计算**********/
	SH=dis_time_set/3600/10;//计算十位单位的小时数
	H=dis_time_set/3600%10;//计算个位单位的小时数
	SM=dis_time_set%3600/60/10;//计算十分位单位的分钟数
	M=dis_time_set%3600/60%10;//计算个分位单位的分钟数
	/***********time_set千位***********/
	if(SH)//大于等于10小时时 就是9小时59分59秒
	{		
		seg4&=0x7F;seg4|=0x80;//显示1
	}
	else//小于999时
    {
        seg4&=0x7F;seg4|=0x00;//不显示
    }
	/***********time_set百位***********/
	seg4&=0x80;seg4|=Tab[H];//数字	
	
	/***********time_set十位***********/
	seg5&=0x80;seg5|=Tab[SM];//数字	
	
	/***********time_set个位***********/
	seg6&=0x80;seg6|=Tab[M];//数字	
	
	seg2&=0x7F;seg2|=0x80;//实际时间的冒号
	if(Run_Status == 1 && Run_Flag > 1 && DownTime_Over.L0 == 0 && RelTime_State.L0 == 1)//运行时
    {
        seg2&=0x7F;seg2|=0x00;//实际时间的冒号消失
    }
	seg5&=0x7F;seg5|=0x80;//设定时间的冒号
	seg6&=0x7F;seg6|=0x80;//显示min
	
	if(SetTime_State.L0 == 0)//没有设置时间
    {
        //时间显示横杠“----”
        seg1&=0x00;seg1|=0x08;seg2&=0x80;seg2|=0x08;seg3&=0x80;seg3|=0x08;
		seg4&=0x00;seg4|=0x08;seg5&=0x80;seg5|=0x08;seg6&=0x80;seg6|=0x08;
    }
    if(SetMode_Option == 3)
    {
        if(Time_ShowFlag && EC11A_Knob == 0)//时间到和旋钮无操作时
        {
            seg4&=0x00;seg4|=0x00;seg5&=0x80;seg5|=0x00;seg6&=0x80;seg6|=0x00;
        }		
    }
	Write_Addr_Dat_N(24, seg1, 1);
	Write_Addr_Dat_N(23, seg2, 1);
	Write_Addr_Dat_N(22, seg3, 1);
	Write_Addr_Dat_N(21, seg4, 1);
	Write_Addr_Dat_N(20, seg5, 1);
	Write_Addr_Dat_N(19, seg6, 1);
}

/*
*****************************************************************
 * 函数原型： void Deal_Speed(void)
 * 功    能： 速度显示处理
*****************************************************************
*/
void Deal_Speed(void)
{
    /**********SpeedL1_ADD_Mode**********/
    if(Run_Status == 1)//启动的情况下
    {
        if(Speed_ADDMode.L1 == 0)//在电机控制中，速度未处理
        {
            if(Ctrl_Speed.L1 >= Display_RelSpeed.L1)//控制速度大于实际速度
            {
                Speed_New.L1 =0;//现在的速度清零
                Speed_Last.L1 = 0;//之前的速度清零
                Speed_ADDMode.L1 = 1;//进入加速模式下
            }
            else if(Ctrl_Speed.L1 < Display_RelSpeed.L1)//控制速度小于实际速度
            {
                Speed_New.L1=0;//现在的速度清零
                Speed_Last.L1 = Display_RelSpeed.L1;//之前的速度等于当前显示速度
                Speed_ADDMode.L1 = 2;//进入减速模式下
            }
        }
        if(Speed_ADDMode.L1==1)//在进入加速模式下
        { 
            if(Rel_Speed.L1 >= Ctrl_Speed.L1)//实际速度大于等于控制速度
            {
                Speed_ADDMode.L1 = 3;//进入稳定模式
                return;
            }
            Speed_New.L1 = Rel_Speed.L1;//记录当前速度
            if(Speed_New.L1 > Speed_Last.L1)//当前速度大于上一次速度
                Display_RelSpeed.L1 = Speed_New.L1;//显示当前速度
            else//当前速度小于上一次速度
            {
                Display_RelSpeed.L1 = Speed_Last.L1;//显示上一次速度，不让速度小于当前速度。呈现攀升速度的现象
                Speed_New.L1 = Speed_Last.L1;//将上一次速度赋值给当前速度
            }
            Speed_Last.L1 = Speed_New.L1;//将当前速度保存    
        }
        else if(Speed_ADDMode.L1 == 2)//速度下降模式下
        {
            if(Rel_Speed.L1 <= Ctrl_Speed.L1)//实际速度小于等于控制速度
            {
                Speed_ADDMode.L1 = 3;//稳定模式
                return;
            }
            Speed_New.L1 = Rel_Speed.L1;//记录当前速度
            if(Speed_New.L1 < Speed_Last.L1)//当前速度小于上一次速度
                Display_RelSpeed.L1 = Speed_New.L1;//显示当前速度
            else//当前速度大于上一次速度
            {
                Display_RelSpeed.L1 = Speed_Last.L1;//显示上一次速度，不让速度大于当前速度。呈现下降速度的现象
                Speed_New.L1 = Speed_Last.L1;//将上一次速度赋值给当前速度
            }
            Speed_Last.L1 = Speed_New.L1;//将当前速度保存
            
        }
        else if(Speed_ADDMode.L1 == 3)//速度稳定模式下
        {
            Display_RelSpeed.L1 = Ctrl_Speed.L1;//显示控制速度
        }
        else if(Speed_ADDMode.L1 == 4)//倒计时结束
        {
            Display_RelSpeed.L1 = Rel_Speed.L1;//显示控制速度
        }
        /**********SpeedL2_ADD_Mode**********/
        if(Speed_ADDMode.L2 == 0)//在电机控制中，速度未处理
        {
            if(Ctrl_Speed.L2 >= Display_RelSpeed.L2)//控制速度大于实际速度
            {
                Speed_New.L2 =0;//现在的速度清零
                Speed_Last.L2 = 0;//之前的速度清零
                Speed_ADDMode.L2 = 1;//进入加速模式下
            }
            else if(Ctrl_Speed.L2 < Display_RelSpeed.L2)//控制速度小于实际速度
            {
                Speed_New.L2=0;//现在的速度清零
                Speed_Last.L2 = Display_RelSpeed.L2;//之前的速度等于当前显示速度
                Speed_ADDMode.L2 = 2;//进入减速模式下
            }
        }
        if(Speed_ADDMode.L2==1)//在进入加速模式下
        { 
            if(Rel_Speed.L2 >= Ctrl_Speed.L2)//实际速度大于等于控制速度
            {
                Speed_ADDMode.L2 = 3;//进入稳定模式
                return;
            }
            Speed_New.L2 = Rel_Speed.L2;//记录当前速度
            if(Speed_New.L2 > Speed_Last.L2)//当前速度大于上一次速度
                Display_RelSpeed.L2 = Speed_New.L2;//显示当前速度
            else//当前速度小于上一次速度
            {
                Display_RelSpeed.L2 = Speed_Last.L2;//显示上一次速度，不让速度小于当前速度。呈现攀升速度的现象
                Speed_New.L2 = Speed_Last.L2;//将上一次速度赋值给当前速度
            }
            Speed_Last.L2 = Speed_New.L2;//将当前速度保存    
        }
        else if(Speed_ADDMode.L2 == 2)//速度下降模式下
        {
            if(Rel_Speed.L2 <= Ctrl_Speed.L2)//实际速度小于等于控制速度
            {
                Speed_ADDMode.L2 = 3;//稳定模式
                return;
            }
            Speed_New.L2 = Rel_Speed.L2;//记录当前速度
            if(Speed_New.L2 < Speed_Last.L2)//当前速度小于上一次速度
                Display_RelSpeed.L2 = Speed_New.L2;//显示当前速度
            else//当前速度大于上一次速度
            {
                Display_RelSpeed.L2 = Speed_Last.L2;//显示上一次速度，不让速度大于当前速度。呈现下降速度的现象
                Speed_New.L2 = Speed_Last.L2;//将上一次速度赋值给当前速度
            }
            Speed_Last.L2 = Speed_New.L2;//将当前速度保存
            
        }
        else if(Speed_ADDMode.L2 == 3)//速度稳定模式下
        {
            Display_RelSpeed.L2 = Ctrl_Speed.L2;//显示控制速度
        }
		else if(Speed_ADDMode.L2 == 4)//倒计时结束
        {
            Display_RelSpeed.L2 = Rel_Speed.L2;//显示控制速度
        }
        /**********SpeedL3_ADD_Mode**********/
        if(Speed_ADDMode.L3 == 0)//在电机控制中，速度未处理
        {
            if(Ctrl_Speed.L3 >= Display_RelSpeed.L3)//控制速度大于实际速度
            {
                Speed_New.L3 =0;//现在的速度清零
                Speed_Last.L3 = 0;//之前的速度清零
                Speed_ADDMode.L3 = 1;//进入加速模式下
            }
            else if(Ctrl_Speed.L3 < Display_RelSpeed.L3)//控制速度小于实际速度
            {
                Speed_New.L3=0;//现在的速度清零
                Speed_Last.L3 = Display_RelSpeed.L3;//之前的速度等于当前显示速度
                Speed_ADDMode.L3 = 2;//进入减速模式下
            }
        }
        if(Speed_ADDMode.L3==1)//在进入加速模式下
        { 
            if(Rel_Speed.L3 >= Ctrl_Speed.L3)//实际速度大于等于控制速度
            {
                Speed_ADDMode.L3 = 3;//进入稳定模式
                return;
            }
            Speed_New.L3 = Rel_Speed.L3;//记录当前速度
            if(Speed_New.L3 > Speed_Last.L3)//当前速度大于上一次速度
                Display_RelSpeed.L3 = Speed_New.L3;//显示当前速度
            else//当前速度小于上一次速度
            {
                Display_RelSpeed.L3 = Speed_Last.L3;//显示上一次速度，不让速度小于当前速度。呈现攀升速度的现象
                Speed_New.L3 = Speed_Last.L3;//将上一次速度赋值给当前速度
            }
            Speed_Last.L3 = Speed_New.L3;//将当前速度保存    
        }
        else if(Speed_ADDMode.L3 == 2)//速度下降模式下
        {
            if(Rel_Speed.L3 <= Ctrl_Speed.L3)//实际速度小于等于控制速度
            {
                Speed_ADDMode.L3 = 3;//稳定模式
                return;
            }
            Speed_New.L3 = Rel_Speed.L3;//记录当前速度
            if(Speed_New.L3 < Speed_Last.L3)//当前速度小于上一次速度
                Display_RelSpeed.L3 = Speed_New.L3;//显示当前速度
            else//当前速度大于上一次速度
            {
                Display_RelSpeed.L3 = Speed_Last.L3;//显示上一次速度，不让速度大于当前速度。呈现下降速度的现象
                Speed_New.L3 = Speed_Last.L3;//将上一次速度赋值给当前速度
            }
            Speed_Last.L3 = Speed_New.L3;//将当前速度保存
            
        }
        else if(Speed_ADDMode.L3 == 3)//速度稳定模式下
        {
            Display_RelSpeed.L3 = Ctrl_Speed.L3;//显示控制速度
        }
		else if(Speed_ADDMode.L3 == 4)//倒计时结束
        {
            Display_RelSpeed.L3 = Rel_Speed.L3;//显示控制速度
        }
        /**********SpeedL4_ADD_Mode**********/
        if(Speed_ADDMode.L4 == 0)//在电机控制中，速度未处理
        {
            if(Ctrl_Speed.L4 >= Display_RelSpeed.L4)//控制速度大于实际速度
            {
                Speed_New.L4 =0;//现在的速度清零
                Speed_Last.L4 = 0;//之前的速度清零
                Speed_ADDMode.L4 = 1;//进入加速模式下
            }
            else if(Ctrl_Speed.L4 < Display_RelSpeed.L4)//控制速度小于实际速度
            {
                Speed_New.L4=0;//现在的速度清零
                Speed_Last.L4 = Display_RelSpeed.L4;//之前的速度等于当前显示速度
                Speed_ADDMode.L4 = 2;//进入减速模式下
            }
        }
        if(Speed_ADDMode.L4==1)//在进入加速模式下
        { 
            if(Rel_Speed.L4 >= Ctrl_Speed.L4)//实际速度大于等于控制速度
            {
                Speed_ADDMode.L4 = 3;//进入稳定模式
                return;
            }
            Speed_New.L4 = Rel_Speed.L4;//记录当前速度
            if(Speed_New.L4 > Speed_Last.L4)//当前速度大于上一次速度
                Display_RelSpeed.L4 = Speed_New.L4;//显示当前速度
            else//当前速度小于上一次速度
            {
                Display_RelSpeed.L4 = Speed_Last.L4;//显示上一次速度，不让速度小于当前速度。呈现攀升速度的现象
                Speed_New.L4 = Speed_Last.L4;//将上一次速度赋值给当前速度
            }
            Speed_Last.L4 = Speed_New.L4;//将当前速度保存    
        }
        else if(Speed_ADDMode.L4 == 2)//速度下降模式下
        {
            if(Rel_Speed.L4 <= Ctrl_Speed.L4)//实际速度小于等于控制速度
            {
                Speed_ADDMode.L4 = 3;//稳定模式
                return;
            }
            Speed_New.L4 = Rel_Speed.L4;//记录当前速度
            if(Speed_New.L4 < Speed_Last.L4)//当前速度小于上一次速度
                Display_RelSpeed.L4 = Speed_New.L4;//显示当前速度
            else//当前速度大于上一次速度
            {
                Display_RelSpeed.L4 = Speed_Last.L4;//显示上一次速度，不让速度大于当前速度。呈现下降速度的现象
                Speed_New.L4 = Speed_Last.L4;//将上一次速度赋值给当前速度
            }
            Speed_Last.L4 = Speed_New.L4;//将当前速度保存
            
        }
        else if(Speed_ADDMode.L4 == 3)//速度稳定模式下
        {
            Display_RelSpeed.L4 = Ctrl_Speed.L4;//显示控制速度
        }
		else if(Speed_ADDMode.L4 == 4)//倒计时结束
        {
            Display_RelSpeed.L4 = Rel_Speed.L4;//显示控制速度
        }
        /**********SpeedL5_ADD_Mode**********/
        if(Speed_ADDMode.L5 == 0)//在电机控制中，速度未处理
        {
            if(Ctrl_Speed.L5 >= Display_RelSpeed.L5)//控制速度大于实际速度
            {
                Speed_New.L5 =0;//现在的速度清零
                Speed_Last.L5 = 0;//之前的速度清零
                Speed_ADDMode.L5 = 1;//进入加速模式下
            }
            else if(Ctrl_Speed.L5 < Display_RelSpeed.L5)//控制速度小于实际速度
            {
                Speed_New.L5=0;//现在的速度清零
                Speed_Last.L5 = Display_RelSpeed.L5;//之前的速度等于当前显示速度
                Speed_ADDMode.L5 = 2;//进入减速模式下
            }
        }
        if(Speed_ADDMode.L5==1)//在进入加速模式下
        { 
            if(Rel_Speed.L5 >= Ctrl_Speed.L5)//实际速度大于等于控制速度
            {
                Speed_ADDMode.L5 = 3;//进入稳定模式
                return;
            }
            Speed_New.L5 = Rel_Speed.L5;//记录当前速度
            if(Speed_New.L5 > Speed_Last.L5)//当前速度大于上一次速度
                Display_RelSpeed.L5 = Speed_New.L5;//显示当前速度
            else//当前速度小于上一次速度
            {
                Display_RelSpeed.L5 = Speed_Last.L5;//显示上一次速度，不让速度小于当前速度。呈现攀升速度的现象
                Speed_New.L5 = Speed_Last.L5;//将上一次速度赋值给当前速度
            }
            Speed_Last.L5 = Speed_New.L5;//将当前速度保存    
        }
        else if(Speed_ADDMode.L5 == 2)//速度下降模式下
        {
            if(Rel_Speed.L5 <= Ctrl_Speed.L5)//实际速度小于等于控制速度
            {
                Speed_ADDMode.L5 = 3;//稳定模式
                return;
            }
            Speed_New.L5 = Rel_Speed.L5;//记录当前速度
            if(Speed_New.L5 < Speed_Last.L5)//当前速度小于上一次速度
                Display_RelSpeed.L5 = Speed_New.L5;//显示当前速度
            else//当前速度大于上一次速度
            {
                Display_RelSpeed.L5 = Speed_Last.L5;//显示上一次速度，不让速度大于当前速度。呈现下降速度的现象
                Speed_New.L5 = Speed_Last.L5;//将上一次速度赋值给当前速度
            }
            Speed_Last.L5 = Speed_New.L5;//将当前速度保存
            
        }
        else if(Speed_ADDMode.L5 == 3)//速度稳定模式下
        {
            Display_RelSpeed.L5 = Ctrl_Speed.L5;//显示控制速度
        }
		else if(Speed_ADDMode.L5 == 4)//倒计时结束
        {
            Display_RelSpeed.L5 = Rel_Speed.L5;//显示控制速度
        }
        /**********SpeedL6_ADD_Mode**********/
        if(Speed_ADDMode.L6 == 0)//在电机控制中，速度未处理
        {
            if(Ctrl_Speed.L6 >= Display_RelSpeed.L6)//控制速度大于实际速度
            {
                Speed_New.L6 =0;//现在的速度清零
                Speed_Last.L6 = 0;//之前的速度清零
                Speed_ADDMode.L6 = 1;//进入加速模式下
            }
            else if(Ctrl_Speed.L6 < Display_RelSpeed.L6)//控制速度小于实际速度
            {
                Speed_New.L6=0;//现在的速度清零
                Speed_Last.L6 = Display_RelSpeed.L6;//之前的速度等于当前显示速度
                Speed_ADDMode.L6 = 2;//进入减速模式下
            }
        }
        if(Speed_ADDMode.L6==1)//在进入加速模式下
        { 
            if(Rel_Speed.L6 >= Ctrl_Speed.L6)//实际速度大于等于控制速度
            {
                Speed_ADDMode.L6 = 3;//进入稳定模式
                return;
            }
            Speed_New.L6 = Rel_Speed.L6;//记录当前速度
            if(Speed_New.L6 > Speed_Last.L6)//当前速度大于上一次速度
                Display_RelSpeed.L6 = Speed_New.L6;//显示当前速度
            else//当前速度小于上一次速度
            {
                Display_RelSpeed.L6 = Speed_Last.L6;//显示上一次速度，不让速度小于当前速度。呈现攀升速度的现象
                Speed_New.L6 = Speed_Last.L6;//将上一次速度赋值给当前速度
            }
            Speed_Last.L6 = Speed_New.L6;//将当前速度保存    
        }
        else if(Speed_ADDMode.L6 == 2)//速度下降模式下
        {
            if(Rel_Speed.L6 <= Ctrl_Speed.L6)//实际速度小于等于控制速度
            {
                Speed_ADDMode.L6 = 3;//稳定模式
                return;
            }
            Speed_New.L6 = Rel_Speed.L6;//记录当前速度
            if(Speed_New.L6 < Speed_Last.L6)//当前速度小于上一次速度
                Display_RelSpeed.L6 = Speed_New.L6;//显示当前速度
            else//当前速度大于上一次速度
            {
                Display_RelSpeed.L6 = Speed_Last.L6;//显示上一次速度，不让速度大于当前速度。呈现下降速度的现象
                Speed_New.L6 = Speed_Last.L6;//将上一次速度赋值给当前速度
            }
            Speed_Last.L6 = Speed_New.L6;//将当前速度保存
            
        }
        else if(Speed_ADDMode.L6 == 3)//速度稳定模式下
        {
            Display_RelSpeed.L6 = Ctrl_Speed.L6;//显示控制速度
        }
		else if(Speed_ADDMode.L6 == 4)//倒计时结束
        {
            Display_RelSpeed.L6 = Rel_Speed.L6;//显示控制速度
        }
        /**********SpeedL7_ADD_Mode**********/
        if(Speed_ADDMode.L7 == 0)//在电机控制中，速度未处理
        {
            if(Ctrl_Speed.L7 >= Display_RelSpeed.L7)//控制速度大于实际速度
            {
                Speed_New.L7 =0;//现在的速度清零
                Speed_Last.L7 = 0;//之前的速度清零
                Speed_ADDMode.L7 = 1;//进入加速模式下
            }
            else if(Ctrl_Speed.L7 < Display_RelSpeed.L7)//控制速度小于实际速度
            {
                Speed_New.L7=0;//现在的速度清零
                Speed_Last.L7 = Display_RelSpeed.L7;//之前的速度等于当前显示速度
                Speed_ADDMode.L7 = 2;//进入减速模式下
            }
        }
        if(Speed_ADDMode.L7==1)//在进入加速模式下
        { 
            if(Rel_Speed.L7 >= Ctrl_Speed.L7)//实际速度大于等于控制速度
            {
                Speed_ADDMode.L7 = 3;//进入稳定模式
                return;
            }
            Speed_New.L7 = Rel_Speed.L7;//记录当前速度
            if(Speed_New.L7 > Speed_Last.L7)//当前速度大于上一次速度
                Display_RelSpeed.L7 = Speed_New.L7;//显示当前速度
            else//当前速度小于上一次速度
            {
                Display_RelSpeed.L7 = Speed_Last.L7;//显示上一次速度，不让速度小于当前速度。呈现攀升速度的现象
                Speed_New.L7 = Speed_Last.L7;//将上一次速度赋值给当前速度
            }
            Speed_Last.L7 = Speed_New.L7;//将当前速度保存    
        }
        else if(Speed_ADDMode.L7 == 2)//速度下降模式下
        {
            if(Rel_Speed.L7 <= Ctrl_Speed.L7)//实际速度小于等于控制速度
            {
                Speed_ADDMode.L7 = 3;//稳定模式
                return;
            }
            Speed_New.L7 = Rel_Speed.L7;//记录当前速度
            if(Speed_New.L7 < Speed_Last.L7)//当前速度小于上一次速度
                Display_RelSpeed.L7 = Speed_New.L7;//显示当前速度
            else//当前速度大于上一次速度
            {
                Display_RelSpeed.L7 = Speed_Last.L7;//显示上一次速度，不让速度大于当前速度。呈现下降速度的现象
                Speed_New.L7 = Speed_Last.L7;//将上一次速度赋值给当前速度
            }
            Speed_Last.L7 = Speed_New.L7;//将当前速度保存
            
        }
        else if(Speed_ADDMode.L7 == 3)//速度稳定模式下
        {
            Display_RelSpeed.L7 = Ctrl_Speed.L7;//显示控制速度
        }
		else if(Speed_ADDMode.L7 == 4)//倒计时结束
        {
            Display_RelSpeed.L7 = Rel_Speed.L7;//显示控制速度
        }
        /**********SpeedL8_ADD_Mode**********/
        if(Speed_ADDMode.L8 == 0)//在电机控制中，速度未处理
        {
            if(Ctrl_Speed.L8 >= Display_RelSpeed.L8)//控制速度大于实际速度
            {
                Speed_New.L8 =0;//现在的速度清零
                Speed_Last.L8 = 0;//之前的速度清零
                Speed_ADDMode.L8 = 1;//进入加速模式下
            }
            else if(Ctrl_Speed.L8 < Display_RelSpeed.L8)//控制速度小于实际速度
            {
                Speed_New.L8=0;//现在的速度清零
                Speed_Last.L8 = Display_RelSpeed.L8;//之前的速度等于当前显示速度
                Speed_ADDMode.L8 = 2;//进入减速模式下
            }
        }
        if(Speed_ADDMode.L8==1)//在进入加速模式下
        { 
            if(Rel_Speed.L8 >= Ctrl_Speed.L8)//实际速度大于等于控制速度
            {
                Speed_ADDMode.L8 = 3;//进入稳定模式
                return;
            }
            Speed_New.L8 = Rel_Speed.L8;//记录当前速度
            if(Speed_New.L8 > Speed_Last.L8)//当前速度大于上一次速度
                Display_RelSpeed.L8 = Speed_New.L8;//显示当前速度
            else//当前速度小于上一次速度
            {
                Display_RelSpeed.L8 = Speed_Last.L8;//显示上一次速度，不让速度小于当前速度。呈现攀升速度的现象
                Speed_New.L8 = Speed_Last.L8;//将上一次速度赋值给当前速度
            }
            Speed_Last.L8 = Speed_New.L8;//将当前速度保存    
        }
        else if(Speed_ADDMode.L8 == 2)//速度下降模式下
        {
            if(Rel_Speed.L8 <= Ctrl_Speed.L8)//实际速度小于等于控制速度
            {
                Speed_ADDMode.L8 = 3;//稳定模式
                return;
            }
            Speed_New.L8 = Rel_Speed.L8;//记录当前速度
            if(Speed_New.L8 < Speed_Last.L8)//当前速度小于上一次速度
                Display_RelSpeed.L8 = Speed_New.L8;//显示当前速度
            else//当前速度大于上一次速度
            {
                Display_RelSpeed.L8 = Speed_Last.L8;//显示上一次速度，不让速度大于当前速度。呈现下降速度的现象
                Speed_New.L8 = Speed_Last.L8;//将上一次速度赋值给当前速度
            }
            Speed_Last.L8 = Speed_New.L8;//将当前速度保存
            
        }
        else if(Speed_ADDMode.L8 == 3)//速度稳定模式下
        {
            Display_RelSpeed.L8 = Ctrl_Speed.L8;//显示控制速度
        }
		else if(Speed_ADDMode.L8 == 4)//倒计时结束
        {
            Display_RelSpeed.L8 = Rel_Speed.L8;//显示控制速度
        }
		/**********SpeedL9_ADD_Mode**********/
        if(Speed_ADDMode.L9 == 0)//在电机控制中，速度未处理
        {
            if(Ctrl_Speed.L9 >= Display_RelSpeed.L9)//控制速度大于实际速度
            {
                Speed_New.L9 =0;//现在的速度清零
                Speed_Last.L9 = 0;//之前的速度清零
                Speed_ADDMode.L9 = 1;//进入加速模式下
            }
            else if(Ctrl_Speed.L9 < Display_RelSpeed.L9)//控制速度小于实际速度
            {
                Speed_New.L9=0;//现在的速度清零
                Speed_Last.L9 = Display_RelSpeed.L9;//之前的速度等于当前显示速度
                Speed_ADDMode.L9 = 2;//进入减速模式下
            }
        }
        if(Speed_ADDMode.L9==1)//在进入加速模式下
        { 
            if(Rel_Speed.L9 >= Ctrl_Speed.L9)//实际速度大于等于控制速度
            {
                Speed_ADDMode.L9 = 3;//进入稳定模式
                return;
            }
            Speed_New.L9 = Rel_Speed.L9;//记录当前速度
            if(Speed_New.L9 > Speed_Last.L9)//当前速度大于上一次速度
                Display_RelSpeed.L8 = Speed_New.L9;//显示当前速度
            else//当前速度小于上一次速度
            {
                Display_RelSpeed.L9 = Speed_Last.L9;//显示上一次速度，不让速度小于当前速度。呈现攀升速度的现象
                Speed_New.L9 = Speed_Last.L9;//将上一次速度赋值给当前速度
            }
            Speed_Last.L9 = Speed_New.L9;//将当前速度保存    
        }
        else if(Speed_ADDMode.L9 == 2)//速度下降模式下
        {
            if(Rel_Speed.L9 <= Ctrl_Speed.L9)//实际速度小于等于控制速度
            {
                Speed_ADDMode.L9 = 3;//稳定模式
                return;
            }
            Speed_New.L9 = Rel_Speed.L9;//记录当前速度
            if(Speed_New.L9 < Speed_Last.L9)//当前速度小于上一次速度
                Display_RelSpeed.L9 = Speed_New.L9;//显示当前速度
            else//当前速度大于上一次速度
            {
                Display_RelSpeed.L9 = Speed_Last.L9;//显示上一次速度，不让速度大于当前速度。呈现下降速度的现象
                Speed_New.L9 = Speed_Last.L9;//将上一次速度赋值给当前速度
            }
            Speed_Last.L9 = Speed_New.L9;//将当前速度保存
            
        }
        else if(Speed_ADDMode.L9 == 3)//速度稳定模式下
        {
            Display_RelSpeed.L9 = Ctrl_Speed.L9;//显示控制速度
        }
		else if(Speed_ADDMode.L9 == 4)//倒计时结束
        {
            Display_RelSpeed.L9 = Rel_Speed.L9;//显示控制速度
        }
    }
    else
    {
        SetALL_int(0,&Speed_ADDMode);//速度显示模式清零
        SetALL_int(0,&Speed_New);//当前记录速度清零
        SetALL_int(0,&Speed_Last);//上一个速度清零
        SetALL_SpeedOver(&Display_RelSpeed,&Rel_Speed);//将实际速度显示
    }
}

/*
*****************************************************************
 * 函数原型： void Deal_Temp(void)
 * 功    能： 温度显示处理
*****************************************************************
*/
void Deal_Temp(void)
{
    if(Run_Status == 0 || Temp_State == 0)//没启动和没设置的情况下
    {
		Rel_Temp = Ture_Temp;//显示实际测得温度
    }
    else
    {
        if(Temp_ADDMode == 0)//判断数据处理显示
        {
			if(Ture_Temp < Ctrl_Temp)//实际温度大于控制温度
			{	
				Temp_ADDMode = 1;//升温
			}
			else
			{
				Temp_ADDMode = 2;//保温
			}
		}
        else if(Temp_ADDMode == 1)//在加热模式下
        {
            Temp_New = Ture_Temp;//记录当前温度
            if(Temp_New > Temp_Last)//当前温度大于上一次温度
                Rel_Temp = Temp_New;//显示当前温度
            else//当前温度小于等于上一次温度
            {
                Rel_Temp = Temp_Last;//显示上一次温度，不让温度小于当前温度。呈现攀升温度的现象
                Temp_New = Temp_Last;//将上一次温度赋值给当前温度
            }
            Temp_Last = Temp_New;//将当前温度保存
            if(Rel_Temp >= Ctrl_Temp)//假如显示值大于等于设定值
            {
                Temp_ADDMode = 3;//进入稳定模式
            }
        }
        else if(Temp_ADDMode == 2)
        {
            Temp_New = Ture_Temp;//记录当前温度
            if(Temp_New < Temp_Last)//当前温度小于上一次温度
                Rel_Temp = Temp_New;//显示当前温度
            else//当前温度大于上一次温度
            {
                Rel_Temp = Temp_Last;//显示上一次温度，不让温度大于当前温度。呈现下降温度的现象
                Temp_New = Temp_Last;//将上一次温度赋值给当前温度
            }
            Temp_Last = Temp_New;//将当前速度保存
            if(Rel_Temp <= Ctrl_Temp)//假如显示值小于等于设定值
            {
                Temp_ADDMode = 3;//进入稳定模式
            }
        }
        else if(Temp_ADDMode == 3)//稳定模式下
        {
            Rel_Temp = Ctrl_Temp;//显示控制温度
        }
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
	Deal_Speed();//速度显示处理
    Deal_Temp();//温度显示处理
	switch(Work_Option)
    {
        case 1://工位1              
            Set_Speed.L0 = Set_Speed.L1;//将工位的速度赋值给设定速度显示
            Rel_Speed.L0 = Display_RelSpeed.L1;//将获取的实际速度赋值显示
        
            Set_Time.L0 = Set_Time.L1;//将时间显示
            if(Run_Status == 0)
                Rel_Time.L0 = Rel_Time.L1;//实际时间跟随设定时间显示
            else
                Rel_Time.L0 = Ctrl_Time.L1;//实际时间跟随控制时间显示
            SetTime_State.L0 = SetTime_State.L1;//去设定显示时间
            RelTime_State.L0 = RelTime_State.L1;//去实际显示时间
            DownTime_Over.L0 = DownTime_Over.L1;//时间倒计时结束图标闪烁显示
            break;
        case 2://工位2
            Set_Speed.L0 = Set_Speed.L2;//将工位的速度赋值给设定速度显示
            Rel_Speed.L0 = Display_RelSpeed.L2;//将获取的实际速度赋值显示
        
            Set_Time.L0 = Set_Time.L2;//将时间显示
            if(Run_Status == 0)
                Rel_Time.L0 = Rel_Time.L2;//实际时间跟随设定时间显示
            else
                Rel_Time.L0 = Ctrl_Time.L2;//实际时间跟随控制时间显示
            SetTime_State.L0 = SetTime_State.L2;//去设定显示时间
            RelTime_State.L0 = RelTime_State.L2;//去实际显示时间
            DownTime_Over.L0 = DownTime_Over.L2;//时间倒计时结束图标闪烁显示
            break;
        case 3://工位3
            Set_Speed.L0 = Set_Speed.L3;//将工位的速度赋值给设定速度显示
            Rel_Speed.L0 = Display_RelSpeed.L3;//将获取的实际速度赋值显示
        
            Set_Time.L0 = Set_Time.L3;//将时间显示
            if(Run_Status == 0)
                Rel_Time.L0 = Rel_Time.L3;//实际时间跟随设定时间显示
            else
                Rel_Time.L0 = Ctrl_Time.L3;//实际时间跟随控制时间显示
            SetTime_State.L0 = SetTime_State.L3;//去设定显示时间
            RelTime_State.L0 = RelTime_State.L3;//去实际显示时间
            DownTime_Over.L0 = DownTime_Over.L3;//时间倒计时结束图标闪烁显示
            break;
        case 4://工位4
            Set_Speed.L0 = Set_Speed.L4;//将工位的速度赋值给设定速度显示
            Rel_Speed.L0 = Display_RelSpeed.L4;//将获取的实际速度赋值显示
        
            Set_Time.L0 = Set_Time.L4;//将时间显示
            if(Run_Status == 0)
                Rel_Time.L0 = Rel_Time.L4;//实际时间跟随设定时间显示
            else
                Rel_Time.L0 = Ctrl_Time.L4;//实际时间跟随控制时间显示
            SetTime_State.L0 = SetTime_State.L4;//去设定显示时间
            RelTime_State.L0 = RelTime_State.L4;//去实际显示时间
            DownTime_Over.L0 = DownTime_Over.L4;//时间倒计时结束图标闪烁显示
            break;
        case 5://工位5
            Set_Speed.L0 = Set_Speed.L5;//将工位的速度赋值给设定速度显示
            Rel_Speed.L0 = Display_RelSpeed.L5;//将获取的实际速度赋值显示
        
            Set_Time.L0 = Set_Time.L5;//将时间显示
            if(Run_Status == 0)
                Rel_Time.L0 = Rel_Time.L5;//实际时间跟随设定时间显示
            else
                Rel_Time.L0 = Ctrl_Time.L5;//实际时间跟随控制时间显示
            SetTime_State.L0 = SetTime_State.L5;//去设定显示时间
            RelTime_State.L0 = RelTime_State.L5;//去实际显示时间
            DownTime_Over.L0 = DownTime_Over.L5;//时间倒计时结束图标闪烁显示
            break;
        case 6://工位6
            Set_Speed.L0 = Set_Speed.L6;//将工位的速度赋值给设定速度显示
            Rel_Speed.L0 = Display_RelSpeed.L6;//将获取的实际速度赋值显示
        
            Set_Time.L0 = Set_Time.L6;//将时间显示
            if(Run_Status == 0)
                Rel_Time.L0 = Rel_Time.L6;//实际时间跟随设定时间显示
            else
                Rel_Time.L0 = Ctrl_Time.L6;//实际时间跟随控制时间显示
            SetTime_State.L0 = SetTime_State.L6;//去设定显示时间
            RelTime_State.L0 = RelTime_State.L6;//去实际显示时间
            DownTime_Over.L0 = DownTime_Over.L6;//时间倒计时结束图标闪烁显示
            break;
        case 7://工位7
            Set_Speed.L0 = Set_Speed.L7;//将工位的速度赋值给设定速度显示
            Rel_Speed.L0 = Display_RelSpeed.L7;//将获取的实际速度赋值显示
        
            Set_Time.L0 = Set_Time.L7;//将时间显示
            if(Run_Status == 0)
                Rel_Time.L0 = Rel_Time.L7;//实际时间跟随设定时间显示
            else
                Rel_Time.L0 = Ctrl_Time.L7;//实际时间跟随控制时间显示
            SetTime_State.L0 = SetTime_State.L7;//去设定显示时间
            RelTime_State.L0 = RelTime_State.L7;//去实际显示时间
            DownTime_Over.L0 = DownTime_Over.L7;//时间倒计时结束图标闪烁显示
            break;
        case 8://工位8
            Set_Speed.L0 = Set_Speed.L8;//将工位的速度赋值给设定速度显示
            Rel_Speed.L0 = Display_RelSpeed.L8;//将获取的实际速度赋值显示
        
            Set_Time.L0 = Set_Time.L8;//将时间显示
            if(Run_Status == 0)
                Rel_Time.L0 = Rel_Time.L8;//实际时间跟随设定时间显示
            else
                Rel_Time.L0 = Ctrl_Time.L8;//实际时间跟随控制时间显示
            SetTime_State.L0 = SetTime_State.L8;//去设定显示时间
            RelTime_State.L0 = RelTime_State.L8;//去实际显示时间
            DownTime_Over.L0 = DownTime_Over.L8;//时间倒计时结束图标闪烁显示
            break;
		case 9://工位9
            Set_Speed.L0 = Set_Speed.L9;//将工位的速度赋值给设定速度显示
            Rel_Speed.L0 = Display_RelSpeed.L9;//将获取的实际速度赋值显示
        
            Set_Time.L0 = Set_Time.L9;//将时间显示
            if(Run_Status == 0)
                Rel_Time.L0 = Rel_Time.L9;//实际时间跟随设定时间显示
            else
                Rel_Time.L0 = Ctrl_Time.L9;//实际时间跟随控制时间显示
            SetTime_State.L0 = SetTime_State.L9;//去设定显示时间
            RelTime_State.L0 = RelTime_State.L9;//去实际显示时间
            DownTime_Over.L0 = DownTime_Over.L9;//时间倒计时结束图标闪烁显示
            break;
        default:
            break;
    }
    Display_Speed_One(Display_Speed.L1,Display_Speed.L2,Display_Speed.L3);
	Display_Speed_Two(Display_Speed.L4,Display_Speed.L5,Display_Speed.L6);
	Display_Speed_Three(Display_Speed.L7,Display_Speed.L8,Display_Speed.L9);
	Display_Speed_Val(Rel_Speed.L0,Set_Speed.L0);
	Display_Temp_Val(Rel_Temp,Set_Temp);
	Display_Time_Val(Rel_Time.L0+59,Set_Time.L0);
}

