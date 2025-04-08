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
	
	/***********设定温度计算**********/
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
	
	/***********实际温度计算**********/
	if(dis_rel_temp > 999)//大于999时
	{
		Val=dis_rel_temp/1000;//取出千位
		Temp_QU = Tab[Val];
	}
	else
	{
		Temp_QU = 0x00;//不显示
	}
	if(dis_rel_temp > 99)//大于99时
	{
		Val=dis_rel_temp/100;//取出百位
		if(dis_rel_temp > 999)//大于999时
			Val=Val%10;//取出百位
		Temp_BU = Tab[Val];
	}
	else
	{
		Temp_BU = 0x00;//不显示
	}
	if(dis_rel_temp > 9)//大于9时
	{
		Val=dis_rel_temp/10;//取出十位
		if(dis_rel_temp > 99)//大于99时
			Val=Val%10;//取出十位
		Temp_SU = Tab[Val];
	}
	else
	{
		Temp_SU = Tab[0];//不显示0
	}
	Val=dis_rel_temp%10;//取出个位
	Temp_GU = Tab[Val];
	
	/*************外框的图标*************/
	seg1 &= 0x7f;seg1 |= 0x80;//L6
	seg2 &= 0x7f;seg2 |= 0x80;//L7
	seg3 &= 0x7f;seg3 |= 0x80;//L8
	seg4 &= 0x7f;seg4 |= 0x80;//L9
	seg5 &= 0x7f;seg5 |= 0x80;//L10
	
	/*************温度小数点的图标*******/
	seg6 &= 0xf7;seg6 |= 0x08;//实际温度小数点
	seg7 &= 0x7f;seg7 |= 0x80;//设定温度小数点
	
	/****************℃******************/
	seg8 &= 0x7F;seg8 |= 0x80;//℃
	
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
	Write_Addr_Dat_N(0, seg1,1);
	Write_Addr_Dat_N(2, seg2,1);
	Write_Addr_Dat_N(4, seg3,1);
	Write_Addr_Dat_N(6, seg4,1);
	Write_Addr_Dat_N(8, seg5,1);
	Write_Addr_Dat_N(10, seg6,1);
	Write_Addr_Dat_N(12, seg7,1);
	Write_Addr_Dat_N(14, seg8,1);
}
/*
*****************************************************************
 * 函数原型：void Display_Speed(int16_t dis_set_speed,int16_t dis_rel_speed)
 * 功    能：显示转速
 * 输    入: dis_set_speed 设定转速  dis_rel_speed 实际转速
 * 参    数：int16_t dis_set_speed,int16_t dis_rel_speed
*****************************************************************
*/
void Display_Speed(int16_t dis_set_speed,int16_t dis_rel_speed)
{
	uint8_t seg9,seg10,seg11,seg12,seg13,seg14,seg15,seg16,seg17;
	seg9=0;seg10=0;seg11=0;seg12=0;seg13=0;seg14=0;seg15=0;seg16=0;seg17=0;
	uint8_t Speed_QU,Speed_BU,Speed_SU,Speed_GU;//实际速度的计算位数取值
	uint8_t Speed_QD,Speed_BD,Speed_SD,Speed_GD;//设定速度的计算位数取值
	uint16_t Val;//用于百十个取出来的数字
	
	if(Speed_ShowFlag == 0)
	{
		/***********设定转速计算**********/
		if(dis_set_speed > 999)//大于999时
		{
			Val=dis_set_speed/1000;//取出千位
			Speed_QD = Tab1[Val];
		}
		else
		{
			Speed_QD = Tab1[0];//显示0
		}
		if(dis_set_speed > 99)//大于99时
		{
			Val=dis_set_speed/100;//取出百位
			if(dis_set_speed > 999)//大于999时
				Val=Val%10;//取出百位
			Speed_BD = Tab1[Val];
		}
		else
		{
			Speed_BD = Tab1[0];//显示0
		}
		if(dis_set_speed > 9)//大于9时
		{
			Val=dis_set_speed/10;//取出十位
			if(dis_set_speed > 99)//大于99时
				Val=Val%10;//取出十位
			Speed_SD = Tab1[Val];
		}
		else
		{
			Speed_SD = Tab1[0];//显示0
		}
		Val=dis_set_speed%10;//取出个位
		Speed_GD = Tab1[Val];
	}
	else
	{
		Speed_QD = 0x00;//不显示设定速度
		Speed_BD = 0x00;//不显示设定速度
		Speed_SD = 0x00;//不显示设定速度
		Speed_GD = 0x00;//不显示设定速度
	}
	
	/***********实际转速计算**********/
	if(dis_rel_speed > 999)//大于999时
	{
		Val=dis_rel_speed/1000;//取出千位
		Speed_QU = Tab[Val];
	}
	else
	{
		Speed_QU = Tab[0];//显示0
	}
	if(dis_rel_speed > 99)//大于99时
	{
		Val=dis_rel_speed/100;//取出百位
		if(dis_rel_speed > 999)//大于999时
			Val=Val%10;//取出百位
		Speed_BU = Tab[Val];
	}
	else
	{
		Speed_BU = Tab[0];//显示0
	}
	if(dis_rel_speed > 9)//大于9时
	{
		Val=dis_rel_speed/10;//取出十位
		if(dis_rel_speed > 99)//大于99时
			Val=Val%10;//取出十位
		Speed_SU = Tab[Val];
	}
	else
	{
		Speed_SU = Tab[0];//显示0
	}
	Val=dis_rel_speed%10;//取出个位
	Speed_GU = Tab[Val];
	
	/*************加热的图标*************/
	seg9 &= 0xFE;seg9 |= 0x01;//加热图标
	
	/*************制冷的图标*************/
	seg9 &= 0xFD;seg9 |= 0x02;//制冷图标
	
	/*************时间的图标*************/
	seg9 &= 0xFB;seg9 |= 0x04;//时间图标
	
	/*************上盖的图标*************/
	seg9 &= 0xF7;seg9 |= 0x08;//上盖图标
	
	/*************上模块的图标***********/
	seg9 &= 0xEF;seg9 |= 0x10;//上模块图标
	
	/*************下模块的图标***********/
	seg9 &= 0xDF;seg9 |= 0x20;//下模块图标
	
	/*************底部模块的图标*********/
	seg9 &= 0xBF;seg9 |= 0x40;//底部模块图标
	
	/*************L11的图标**************/
	seg9 &= 0x7F;seg9 |= 0x80;//L11图标
	
	/*************转速的图标*************/
	seg10 &= 0x7F;seg10 |= 0x80;//S5图标
	seg11 &= 0x7F;seg11 |= 0x80;//S3图标
	
	/*************时间单位的图标*********/
	seg12 &= 0x7F;seg12 |= 0x80;//sec图标
	
	/*************时间单位的图标*********/
	seg15 &= 0x7F;seg15 |= 0x80;//min图标
	
	/*************时间冒号的图标*********/
	seg13 &= 0xFE;seg13 |= 0x01;//设定转速上的冒号
	seg14 &= 0x7F;seg14 |= 0x80;//设定转速上的冒号
	
	/*************时间单位的图标*********/
	seg16 &= 0x7F;seg16 |= 0x80;//设定转速min图标
	
	/*************转速单位的图标*********/
	seg17 &= 0x7F;seg17 |= 0x80;//设定转速rpm图标
	
	/*************数据拆分***************/
	seg11 &= 0xF8;seg11 |= (Speed_QU & 0x07);
	seg10 &= 0xF0;seg10 |= (Speed_QU >>4) & 0x0F;
	seg11 &= 0x87;seg11 |= ((Speed_QD<<3)&0x70)|((Speed_QD<<3)&0x08);
	seg10 &= 0x8F;seg10 |= (Speed_QD&0x70);
	
	seg13 &= 0x1F;seg13 |= ((Speed_BU<<1) & 0x0E);
	seg12 &= 0xF0;seg12 |= (Speed_BU >>4) & 0x0F;
	seg13 &= 0x0F;seg13 |= Speed_BD<<4;
	seg12 &= 0x8F;seg12 |= (Speed_BD&0x70);
	
	seg15 &= 0xF8;seg15 |= (Speed_SU & 0x07);
	seg14 &= 0xF0;seg14 |= (Speed_SU >>4) & 0x0F;
	seg15 &= 0x87;seg15 |= ((Speed_SD<<3)&0x70)|((Speed_SD<<3)&0x08);
	seg14 &= 0x8F;seg14 |= (Speed_SD&0x70);
	
	seg17 &= 0xF8;seg17 |= (Speed_GU & 0x07);
	seg16 &= 0xF0;seg16 |= (Speed_GU >>4) & 0x0F;
	seg17 &= 0x87;seg17 |= ((Speed_GD<<3)&0x70)|((Speed_GD<<3)&0x08);
	seg16 &= 0x8F;seg16 |= (Speed_GD&0x70);
	
	/*************发送数据***************/	
	Write_Addr_Dat_N(16, seg9,1);
	Write_Addr_Dat_N(18, seg10,1);
	Write_Addr_Dat_N(20, seg11,1);
	Write_Addr_Dat_N(22, seg12,1);
	Write_Addr_Dat_N(24, seg13,1);
	Write_Addr_Dat_N(26, seg14,1);
	Write_Addr_Dat_N(28, seg15,1);
	Write_Addr_Dat_N(30, seg16,1);	
	Write_Addr_Dat_N(32, seg17,1);	
}

/*
*****************************************************************
 * 函数原型：void Display_Time(int32_t dis_time)
 * 功    能：显示时间
 * 输    入: dis_time 时间
 * 参    数：int32_t dis_time
*****************************************************************
*/
void Display_Time(int32_t dis_time)
{
	uint8_t seg18,seg19,seg20,seg21,seg22,seg23,seg24,seg25;
	seg18=0;seg19=0;seg20=0;seg21=0;seg22=0;seg23=0;seg24=0;seg25=0;
	uint8_t Time_Q,Time_B,Time_S,Time_G;//时间的计算位数取值
	uint8_t SH,H,SM,M;//时间的单位取值
	
	/*************发送数据***************/	
	Write_Addr_Dat_N(34, seg18,1);
	Write_Addr_Dat_N(36, seg19,1);
	Write_Addr_Dat_N(38, seg20,1);
	Write_Addr_Dat_N(40, seg21,1);
	Write_Addr_Dat_N(42, seg22,1);
	Write_Addr_Dat_N(44, seg23,1);
	Write_Addr_Dat_N(46, seg24,1);
	Write_Addr_Dat_N(48, seg25,1);	
}

/*
*****************************************************************
 * 函数原型：void Show_Display(void)
 * 功    能：显示屏幕内容
*****************************************************************
*/
void Show_Display(void)
{
    Display_Temp(3462,5449);
	Display_Speed(1245,6789);
}
