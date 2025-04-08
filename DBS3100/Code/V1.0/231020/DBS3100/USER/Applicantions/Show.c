#include "Show.h"

/**********全局变量声明******/
float Twinkle_Time;//闪烁时间

/**********局部变量声明******/
uint8_t Tab[] = {0xF5,0x05,0xD3,0x97,0x27,0xB6,0xF6,0x15,0xF7,0xB7};//0·9
uint8_t Tab1[] = {0x5F,0x06,0x6B,0x2F,0x36,0x3D,0x7D,0x07,0x7F,0x3F};//0·9
uint8_t Time_ShowFlag,Speed_ShowFlag,Temp_ShowFlag;//时间、速度、温度显示的标志位 0:常亮 1：熄灭

/*
*****************************************************************
 * 函数原型：void Display_Temp(int16_t dis_set_temp,int16_t dis_rel_temp)
 * 功    能：显示温度
 * 输    入: dis_set_temp 设定温度  dis_rel_temp 实际温度
 * 参    数：int16_t dis_set_temp,int16_t dis_rel_temp
*****************************************************************
*/
void Display_Temp(int16_t dis_set_temp,int16_t dis_rel_temp)
{
	uint8_t seg1,seg2,seg3,seg4,seg5,seg6,seg7,seg8;
	seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;seg7=0;seg8=0;
	uint8_t Temp_QU,Temp_BU,Temp_SU,Temp_GU;//实际温度的计算位数取值
	uint8_t Temp_QD,Temp_BD,Temp_SD,Temp_GD;//设定温度的计算位数取值
	uint16_t Val;//用于百十个取出来的数字
	
	if(dis_set_temp > 0)
	{
		if(dis_set_temp > 999)//大于999时
		{
			Val=dis_set_temp/1000;//取出千位
			Temp_QD = Tab1[Val];
		}
		else
		{
			Temp_QD = 0x00;//不显示
		}
		if(dis_set_temp > 99)//大于99时
		{
			Val=dis_set_temp/100;//取出百位
			if(dis_set_temp > 999)//大于999时
				Val=Val%10;//取出百位
			Temp_BD = Tab1[Val];
		}
		else
		{
			Temp_BD = 0x00;//不显示
		}
		if(dis_set_temp > 9)//大于9时
		{
			Val=dis_set_temp/10;//取出十位
			if(dis_set_temp > 99)//大于99时
				Val=Val%10;//取出十位
			Temp_SD = Tab1[Val];
		}
		else
		{
			Temp_SD = Tab1[0];//不显示0
		}
		Val=dis_set_temp%10;//取出个位
		Temp_GD = Tab1[Val];
	}
	else
	{
		Temp_QD = 0x20;//显示"-"
		Temp_BD = 0x20;//显示"-"
		Temp_SD = 0x20;//显示"-"
		Temp_GD = 0x20;//显示"-"
	}
	
	Temp_QU = Tab[0];
	Temp_BU = Tab[0];
	Temp_SU = Tab[0];
	Temp_GU = Tab[0];
//	Temp_QD = Tab1[7];
//	Temp_BD = Tab1[7];
//	Temp_SD = Tab1[7];
//	Temp_GD = Tab1[7];
	/*************数据拆分***************/	
	seg2 &= 0xF8;seg2 |= (Temp_QU & 0x07);
	seg1 &= 0xF0;seg1 |= (Temp_QU >>4) & 0x0F;
	seg2 &= 0x87;seg2 |= ((Temp_QD<<3)&0x70)|((Temp_QD<<3)&0x08);
	seg1 &= 0x8F;seg1 |= (Temp_QD&0x70);
	
	seg4 &= 0xF8;seg4 |= (Temp_BU & 0x07);
	seg3 &= 0xF0;seg3 |= (Temp_BU >>4) & 0x0F;
	seg4 &= 0x87;seg4 |= ((Temp_BD<<3)&0x70)|((Temp_BD<<3)&0x08);
	seg3 &= 0x8F;seg3 |= (Temp_BD&0x70);
	
	seg6 &= 0xF8;seg6 |= (Temp_SU & 0x07);
	seg5 &= 0xF0;seg5 |= (Temp_SU >>4) & 0x0F;
	seg6 &= 0x0F;seg6 |= Temp_SD<<4;
	seg5 &= 0x8F;seg5 |= (Temp_SD&0x70);
	
	seg8 &= 0xF8;seg8 |= (Temp_GU & 0x07);
	seg7 &= 0xF0;seg7 |= (Temp_GU >>4) & 0x0F;
	seg8 &= 0x87;seg8 |= ((Temp_GD<<3)&0x70)|((Temp_GD<<3)&0x08);
	seg7 &= 0x8F;seg7 |= (Temp_GD&0x70);
	
	/*************发送数据***************/	
	Write_Addr_Dat_N(0, seg1,1);//SEG27
	Write_Addr_Dat_N(2, seg2,1);//SEG26
	Write_Addr_Dat_N(4, seg3,1);//SEG25
	Write_Addr_Dat_N(6, seg4,1);//SEG24
	Write_Addr_Dat_N(8, seg5,1);//SEG23
	Write_Addr_Dat_N(10, seg6,1);//SEG22
	Write_Addr_Dat_N(12, seg7,1);//SEG21
	Write_Addr_Dat_N(14, seg8,1);//SEG20
}

/*
*****************************************************************
 * 函数原型：void Show_Display(void)
 * 功    能：显示屏幕内容
*****************************************************************
*/
void Show_Display(void)
{
    Display_Temp(12,654);
}
