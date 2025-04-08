#include "Show.h"

/**********全局变量声明******/
uint16_t Twinkle_Time;//闪烁时间

/**********局部变量声明******/
uint8_t seg15_Flag;//用于显示屏实际速度最后一位中间的斜杠个其他的相差太远
uint8_t Speed_ShowFlag,Temp_ShowFlag,Time_ShowFlag;//速度、温度、时间显示的标志位 0:常亮 1：熄灭
uint8_t Work_All_Time;//全部工位设置时闪烁的工位时间
uint8_t Run_Flag;//运行闪烁图标
uint8_t Data[10]  = {0x77,0x12,0x6B,0x5B,0x1E,0x5D,0x7D,0x13,0x7F,0x5F};
uint8_t Data1[10] = {0xEE,0x48,0xD6,0xDA,0x78,0xBA,0xBE,0xC8,0xFE,0xFA};

/*
*****************************************************************
 * 函数原型：void Start_SpeedRun(float dT)
 * 功    能：转速动画
*****************************************************************
*/
void Start_SpeedRun(float dT)
{
	static float T;
	if(Run_Status==1 && Set_Speed.L0 > 0 && Rel_Speed.L0)//运行时
	{
		T += dT;
		if(T >= 0.5f)
		{
			SpeedIcon_Step++;
			if(SpeedIcon_Step > 3)
				SpeedIcon_Step = 1;
			T = 0;
		}
	}
	else
	{
		SpeedIcon_Step = 0;
		T = 0;
	}
}

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
        Run_Flag = ~Run_Flag;//运行时闪烁
    if(SetMode_Option == 0 && Twinkle_Time==0)//如果没在设置选项中，则都点亮，不闪烁
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
        if(SetMode_Option == 0)//设置速度
        {
            Speed_ShowFlag = ~Speed_ShowFlag;//速度闪烁
            Temp_ShowFlag = 0;//温度常亮
            Time_ShowFlag = 0;//时间常亮
        }
        else if(SetMode_Option == 1)//设置温度
        {
            Speed_ShowFlag = 0;//速度常亮
            Temp_ShowFlag = ~Temp_ShowFlag;//温度闪烁
            Time_ShowFlag = 0;//时间常亮
        }
        else if(SetMode_Option == 2)//设置时间
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
        case 0 :
            HAL_GPIO_WritePin(LED_KEY_GPIO_Port, LED_KEY_Pin, GPIO_PIN_SET);//拉高背光电平信号
			if(Param.type == 0 || Param.type == 2)//四联
			{
				__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 0);//不输出pwm
			}
			else if(Param.type == 1 || Param.type == 3)//六联
			{
				__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 0);//不输出pwm
			}
            break ;
        case 1 :
            HAL_GPIO_WritePin(LED_KEY_GPIO_Port, LED_KEY_Pin, GPIO_PIN_RESET);//拉低背光电平信号
			if(Param.type == 0 || Param.type == 2)//四联
			{
				__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 15);//不输出pwm
			}
			else if(Param.type == 1 || Param.type == 3)//六联
			{
				__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 15);//不输出pwm
			}
            break ;
    }
}

/*
*****************************************************************
 * 函数原型：void Display_WorkSpeed(uint16_t Speed_L1,uint16_t Speed_L2,uint16_t Speed_L3,uint16_t Speed_L4,uint16_t Speed_L5,uint16_t Speed_L6)
 * 功    能：显示工位速度
 * 输    入: Speed_L1工位一的速度, Speed_L2工位二的速度, Speed_L3工位三的速度, Speed_L4工位四的速度, Speed_L5工位五的速度, Speed_L6工位六的速度
 * 参    数：uint16_t Speed_L1,uint16_t Speed_L2,uint16_t Speed_L3,uint16_t Speed_L4,uint16_t Speed_L5,uint16_t Speed_L6
*****************************************************************
*/
void Display_WorkSpeed(uint16_t Speed_L1,uint16_t Speed_L2,uint16_t Speed_L3,uint16_t Speed_L4,uint16_t Speed_L5,uint16_t Speed_L6,uint16_t dis_rel_rpm,uint16_t dis_set_rpm,int dis_rel_temp,int dis_set_temp,uint32_t dis_rel_time,uint32_t dis_set_time)
{
	uint8_t seg1,seg2,seg3,seg4,seg5,seg6,seg7,seg8,seg9,seg10,
	seg11,seg12,seg13,seg14,seg15,seg16,seg17,seg18,seg19,seg20,
	seg21,seg22,seg23,seg24,seg25,seg26,seg27,seg28,seg29,seg30,
	seg31,seg32;
	seg1=0;seg2=0;seg3=0;seg4=0;seg5=0;seg6=0;seg7=0;seg8=0;seg9=0;seg10=0;
	seg11=0;seg12=0;seg13=0;seg14=0;seg15=0;seg16=0;seg17=0;seg18=0;seg19=0;seg20=0;
	seg21=0;seg22=0;seg23=0;seg24=0;seg25=0;seg26=0;seg27=0;seg28=0;seg29=0;seg30=0;
	seg31=0;seg32=0;
    uint8_t Val;//用于百十个取出来的数字
	uint8_t SH,H,SM,M;//时间的单位取值
	
	/*********************Speed_L1*********************/
	/***********L1千位***********/
	if(Speed_L1 > 999)//大于999时
	{		
		seg21&=0xFE;seg21|=0x01;//显示1
		seg1&=0xFD;seg1|=0x00;//显示1
	}
	else//小于999时
    {
        seg21&=0xFE;seg21|=0x01;//显示0
		seg1&=0xFD;seg1|=0x02;//显示0
    }
	
	/***********L1百位***********/
	if(Speed_L1 > 99)//大于99时
	{
		Val=Speed_L1/100;//取出百位的数字
		if(Speed_L1 > 999)//加入大于999时
            Val=Val%10;//取出百位的数字
		seg21&=0x01;seg21|=Data1[Val];//显示百位
	}
	else
	{
		seg21&=0x01;seg21|=Data1[0];//显示百位
	}
	
	/***********L1十位***********/
	if(Speed_L1 > 9)//大于9时
	{
		Val=Speed_L1/10;//取出十位的数字
		if(Speed_L1 > 99)//大于99时
            Val=Val%10;//取出十位的数字
		seg22&=0x01;seg22|=Data1[Val];//显示十位
	}
	else
	{
		seg22&=0x01;seg22|=Data1[0];//显示百位
	}
	
	/***********L1个位***********/
    seg22&=0xFE;seg22|=0x01;//显示1
	
	/*********************Speed_L2*********************/
	/***********L2千位***********/
	if(Speed_L2 > 999)//大于999时
	{		
		seg23&=0xFE;seg23|=0x01;//显示1
		seg1&=0xFE;seg1|=0x00;//显示1
	}
	else//小于999时
    {
        seg23&=0xFE;seg23|=0x01;//显示0
		seg1&=0xFE;seg1|=0x01;//显示0
    }
	
	/***********L2百位***********/
	if(Speed_L2 > 99)//大于99时
	{
		Val=Speed_L2/100;//取出百位的数字
		if(Speed_L2 > 999)//加入大于999时
            Val=Val%10;//取出百位的数字
		seg23&=0x01;seg23|=Data1[Val];//显示百位
	}
	else
	{
		seg23&=0x01;seg23|=Data1[0];//显示百位
	}
	
	/***********L2十位***********/
	if(Speed_L2 > 9)//大于9时
	{
		Val=Speed_L2/10;//取出十位的数字
		if(Speed_L2> 99)//大于99时
            Val=Val%10;//取出十位的数字
		seg24&=0x01;seg24|=Data1[Val];//显示十位
	}
	else
	{
		seg24&=0x01;seg24|=Data1[0];//显示百位
	}
	
	/***********L2个位***********/
    seg24&=0xFE;seg24|=0x01;//显示1
	
	/*********************Speed_L3*********************/
	/***********L3千位***********/
	if(Speed_L3 > 999)//大于999时
	{		
		seg11&=0x7F;seg11|=0x80;//显示1
		seg2&=0xBF;seg2|=0x00;//显示1
	}
	else//小于999时
    {
        seg11&=0x7F;seg11|=0x80;//显示0
		seg2&=0xBF;seg2|=0x40;//显示0
    }
	
	/***********L3百位***********/
	if(Speed_L3 > 99)//大于99时
	{
		Val=Speed_L3/100;//取出百位的数字
		if(Speed_L3 > 999)//加入大于999时
            Val=Val%10;//取出百位的数字
		seg11&=0x80;seg11|=Data[Val];//显示百位
	}
	else
	{
		seg11&=0x80;seg11|=Data[0];//显示百位
	}
	
	/***********L3十位***********/
	if(Speed_L3 > 9)//大于9时
	{
		Val=Speed_L3/10;//取出十位的数字
		if(Speed_L3 > 99)//大于99时
            Val=Val%10;//取出十位的数字
		seg10&=0x80;seg10|=Data[Val];//显示十位
	}
	else
	{
		seg10&=0x80;seg10|=Data[0];//显示百位
	}
	
	/***********L3个位***********/
    seg10&=0x7F;seg10|=0x80;//显示十位
	
	/*********************Speed_L4*********************/
	/***********L4千位***********/
	if(Speed_L4 > 999)//大于999时
	{		
		seg9&=0x7F;seg9|=0x80;//显示1
		seg2&=0x7F;seg2|=0x00;//显示1
	}
	else//小于999时
    {
        seg9&=0x7F;seg9|=0x80;//显示0
		seg2&=0x7F;seg2|=0x80;//显示0
    }
	
	/***********L4百位***********/
	if(Speed_L4 > 99)//大于99时
	{
		Val=Speed_L4/100;//取出百位的数字
		if(Speed_L4 > 999)//加入大于999时
            Val=Val%10;//取出百位的数字
		seg9&=0x80;seg9|=Data[Val];//显示百位
	}
	else
	{
		seg9&=0x80;seg9|=Data[0];//显示百位
	}
	
	/***********L4十位***********/
	if(Speed_L4 > 9)//大于9时
	{
		Val=Speed_L4/10;//取出十位的数字
		if(Speed_L4 > 99)//大于99时
            Val=Val%10;//取出十位的数字
		seg8&=0x80;seg8|=Data[Val];//显示十位
	}
	else
	{
		seg8&=0x80;seg8|=Data[0];//显示百位
	}
	
	/***********L4个位***********/
    seg8&=0x7F;seg8|=0x80;//显示十位
	
	/*********************Speed_L5*********************/
	/***********L5千位***********/
	if(Speed_L5 > 999)//大于999时
	{		
		seg7&=0x7F;seg7|=0x80;//显示1
		seg3&=0xBF;seg3|=0x00;//显示1
	}
	else//小于999时
    {
        seg7&=0x7F;seg7|=0x80;//显示0
		seg3&=0xBF;seg3|=0x40;//显示0
    }
	
	/***********L5百位***********/
	if(Speed_L5 > 99)//大于99时
	{
		Val=Speed_L5/100;//取出百位的数字
		if(Speed_L5 > 999)//加入大于999时
            Val=Val%10;//取出百位的数字
		seg7&=0x80;seg7|=Data[Val];//显示百位
	}
	else
	{
		seg7&=0x80;seg7|=Data[0];//显示百位
	}
	
	/***********L5十位***********/
	if(Speed_L5 > 9)//大于9时
	{
		Val=Speed_L5/10;//取出十位的数字
		if(Speed_L5 > 99)//大于99时
            Val=Val%10;//取出十位的数字
		seg6&=0x80;seg6|=Data[Val];//显示十位
	}
	else
	{
		seg6&=0x80;seg6|=Data[0];//显示百位
	}
	
	/***********L5个位***********/
    seg6&=0x7F;seg6|=0x80;//显示十位
	
	/*********************Speed_L6*********************/
	/***********L6千位***********/
	if(Speed_L6 > 999)//大于999时
	{		
		seg5&=0x7F;seg5|=0x80;//显示1
		seg3&=0x7F;seg3|=0x00;//显示1
	}
	else//小于999时
    {
        seg5&=0x7F;seg5|=0x80;//显示0
		seg3&=0x7F;seg3|=0x80;//显示0
    }
	
	/***********L6百位***********/
	if(Speed_L6 > 99)//大于99时
	{
		Val=Speed_L6/100;//取出百位的数字
		if(Speed_L6 > 999)//加入大于999时
            Val=Val%10;//取出百位的数字
		seg5&=0x80;seg5|=Data[Val];//显示百位
	}
	else
	{
		seg5&=0x80;seg5|=Data[0];//显示百位
	}
	
	/***********L6十位***********/
	if(Speed_L6 > 9)//大于9时
	{
		Val=Speed_L6/10;//取出十位的数字
		if(Speed_L6 > 99)//大于99时
            Val=Val%10;//取出十位的数字
		seg4&=0x80;seg4|=Data[Val];//显示十位
	}
	else
	{
		seg4&=0x80;seg4|=Data[0];//显示百位
	}
	
	/***********L6个位***********/
    seg4&=0x7F;seg4|=0x80;//显示十位
	
	/*********************中间图标*******************/
	/***********转速图标***********/
	/*****************转速图标******************/
	switch(SpeedIcon_Step)
	{
		case 0:seg25&=0xC7;seg25|=0x38;//常亮
			break;
		case 1:seg25&=0xC7;seg25|=0x18;//转速S37
			break;
		case 2:seg25&=0xC7;seg25|=0x28;//转速S38
			break;
		case 3:seg25&=0xC7;seg25|=0x30;//转速S39
			break;
		default:
			break;
	}
	
	/***********温度图标***********/
	seg25&=0xF9;seg25|=0x06;//温度图标
	if(Run_Status == 1 && Temp_State == 1 && Run_Flag > 1)//运行时
    {
		seg25&=0xF9;seg25|=0x00;//温度图标
    }
	
	/***********时间图标***********/
	seg25&=0xFE;seg25|=0x01;//时间图标
	if(Run_Status == 1 && Run_Flag > 1 && DownTime_Over.L0 == 0 && RelTime_State.L0 == 1)//运行时
    {
        seg25&=0xFE;seg25|=0x00;//时间图标消失
    }
	
	/*********************Rel_Speed*********************/
	/***********Rel_Speed千位***********/
	if(dis_rel_rpm > 999)//大于999时
	{		
		seg25&=0x3F;seg25|=0x40;//显示1
	}
	else//小于999时
	{
		seg25&=0x3F;seg25|=0xC0;//显示0
	}
	
	/***********Rel_Speed百位***********/
	if(dis_rel_rpm > 99)//大于99时
	{
		Val=dis_rel_rpm/100;//取出百位的数字
		if(dis_rel_rpm > 999)//加入大于999时
			Val=Val%10;//取出百位的数字
		seg26&=0x01;seg26|=Data1[Val];//显示百位
	}
	else
	{
		seg26&=0x01;seg26|=Data1[0];//显示0
	}
	
	/***********Rel_Speed十位***********/
	if(dis_rel_rpm > 9)//大于9时
	{
		Val=dis_rel_rpm/10;//取出十位的数字
		if(dis_rel_rpm > 99)//大于99时
			Val=Val%10;//取出十位的数字
		seg27&=0x01;seg27|=Data1[Val];//显示十位
	}
	else
	{
		seg27&=0x01;seg27|=Data1[0];//显示0
	}
	
	/***********Rel_Speed个位***********/
	seg26&=0xFE;seg26|=0x01;//显示十位
	
	/*********************Set_Speed*********************/
	/***********Set_Speed千位***********/
	if(dis_set_rpm > 999)//大于999时
	{		
		seg27&=0xFE;seg27|=0x00;//显示1
		seg28&=0xFE;seg28|=0x01;//显示1
	}
	else//小于999时
	{
		seg27&=0xFE;seg27|=0x01;//显示1
		seg28&=0xFE;seg28|=0x01;//显示0
	}
	
	/***********Set_Speed百位***********/
	if(dis_set_rpm > 99)//大于99时
	{
		Val=dis_set_rpm/100;//取出百位的数字
		if(dis_set_rpm > 999)//加入大于999时
			Val=Val%10;//取出百位的数字
		seg28&=0x01;seg28|=Data1[Val];//显示百位
	}
	else
	{
		seg28&=0x01;seg28|=Data1[0];//显示0
	}
	
	/***********Set_Speed十位***********/
	if(dis_set_rpm > 9)//大于9时
	{
		Val=dis_set_rpm/10;//取出十位的数字
		if(dis_set_rpm > 99)//大于99时
			Val=Val%10;//取出十位的数字
		seg29&=0x01;seg29|=Data1[Val];//显示十位
	}
	else
	{
		seg29&=0x01;seg29|=Data1[0];//显示0
	}
	
	/***********Set_Speed个位***********/
	seg29&=0xFE;seg29|=0x01;//显示十位
	/*闪烁*/
	if(Speed_ShowFlag && EC11A_Knob == 0)//时间到和旋钮无操作时
	{
		seg27&=0xFE;seg27|=0x00;//不显示显示
		seg28&=0x00;//不显示显示
		seg29&=0x00;//不显示显示
	}
    seg3&=0xFC;seg3|=0x04;//显示“rpm”
	
	/*********************Rel_Temp*********************/
	/***********Rel_Temp千位***********/
    if(dis_rel_temp > 999)//大于999时
    {
		seg3&=0xFD;seg3|=0x00;//显示1
		seg30&=0xFE;seg30|=0x01;//显示1
    }
    else//小于999时
    {
		seg3&=0xFD;seg3|=0x02;//显示0
		seg30&=0xFE;seg30|=0x01;//显示0
    }
	
	/***********Rel_Temp百位***********/
	if(dis_rel_temp > 99)//大于99时
	{
		Val=dis_rel_temp/100;//取出百位的数字
		if(dis_rel_temp > 999)//加入大于999时
			Val=Val%10;//取出百位的数字
		seg30&=0x01;seg30|=Data1[Val];//显示百位
	}
	else
	{
		seg30&=0x01;seg30|=Data1[0];//显示0
	}
	
	/***********Rel_Temp十位***********/
	if(dis_rel_temp > 9)//大于9时
	{
		Val=dis_rel_temp/10;//取出十位的数字
		if(dis_rel_temp > 99)//大于99时
			Val=Val%10;//取出十位的数字
		seg31&=0x01;seg31|=Data1[Val];//显示十位
	}
	else
	{
		seg31&=0x01;seg31|=Data1[0];//显示0
	}
	
	/***********Rel_Temp个位***********/
	Val = dis_rel_temp % 10;//取出个位
	if(Val > 4)//大于4时
    {
		seg32&=0x01;seg32|=Data1[5];//显示5
    }
    else//小于4时
    {
		seg32&=0x01;seg32|=Data1[0];//显示0
	}	
	/***********温度小数点**************/
	seg31&=0xFE;seg31|=0x01;//显示实际温度小数点
	
	/*********************Set_Temp*********************/
	/***********Set_Temp千位***********/
    if(dis_set_temp > 999)//大于999时
    {
		seg32&=0xFE;seg32|=0x00;//显示1
		seg12&=0xFE;seg12|=0x01;//显示1
    }
    else//小于999时
    {
		seg32&=0xFE;seg32|=0x01;//显示0
		seg12&=0xFE;seg12|=0x01;//显示0
    }
	
	/***********Set_Temp百位***********/
	if(dis_set_temp > 99)//大于99时
	{
		Val=dis_set_temp/100;//取出百位的数字
		if(dis_set_temp > 999)//加入大于999时
			Val=Val%10;//取出百位的数字
		seg12&=0x01;seg12|=Data1[Val];//显示百位
	}
	else
	{
		seg12&=0x01;seg12|=Data1[0];//显示0
	}
	
	/***********Set_Temp十位***********/
	if(dis_set_temp > 9)//大于9时
	{
		Val=dis_set_temp/10;//取出十位的数字
		if(dis_set_temp > 99)//大于99时
			Val=Val%10;//取出十位的数字
		seg13&=0x01;seg13|=Data1[Val];//显示十位
	}
	else
	{
		seg13&=0x01;seg13|=Data1[0];//显示0
	}
	
	/***********Set_Temp个位***********/
	Val = dis_set_temp % 10;//取出个位
	if(Val > 4)//大于4时
    {
		seg14&=0x01;seg14|=Data1[5];//显示5
    }
    else//小于4时
    {
		seg14&=0x01;seg14|=Data1[0];//显示0
	}
	if(Temp_State == 0)//温度设置大于0时
    {
		seg32&=0xFE;seg32|=0x00;//不显示
		seg12&=0xFE;seg12|=0x00;//不显示
		seg12&=0x01;seg12|=0x10;//显示‘-’
		seg13&=0x01;seg13|=0x10;//显示‘-’
		seg14&=0x01;seg14|=0x10;//显示‘-’
	}
	if(Temp_ShowFlag && EC11A_Knob == 0)//时间到和旋钮无操作时
    {
		seg32&=0xFE;seg32|=0x00;//不显示
		seg12&=0xFE;seg12|=0x00;//不显示
		seg12&=0x01;seg12|=0x00;//显示‘-’
		seg13&=0x01;seg13|=0x00;//显示‘-’
		seg14&=0x01;seg14|=0x00;//显示‘-’
	}
	/***********温度小数点**************/
	seg13&=0xFE;seg13|=0x01;//显示设定温度小数点
	/***********温度单位图标************/
	seg14&=0xFE;seg14|=0x01;//显示温度单位图标
	
	/*********************Rel_Time*********************/
	SH=dis_rel_time/3600/10;//计算十位单位的小时数
	H=dis_rel_time/3600%10;//计算个位单位的小时数
	SM=dis_rel_time%3600/60/10;//计算十分位单位的分钟数
	M=dis_rel_time%3600/60%10;//计算个分位单位的分钟数
       
	/***********Rel_Time第一位***********/
	if(SH == 0)
	{
		seg3&=0xFE;seg3|=0x01;//显示实际时间第一位
		seg15&=0xFE;seg15|=0x01;//显示实际时间第一位
	}
	else
	{
		seg3&=0xFE;seg3|=0x00;//显示实际时间第一位
		seg15&=0xFE;seg15|=0x01;//显示实际时间第一位
	}
	
	/***********Rel_Time第二位***********/
	seg15&=0x01;seg15|=Data1[H];//显示实际时间第二位
	/***********Rel_Time第三位***********/
	seg16&=0x01;seg16|=Data1[SM];//显示实际时间第三位
	/***********Rel_Time第四位***********/
	seg17&=0x01;seg17|=Data1[M];//显示实际时间第四位
	/***********Rel_Time冒号图标*********/
	seg16&=0xFE;seg16|=0x01;//显示实际时间冒号
	if(RelTime_State.L0 == 0)//没有设置时间
    {
		seg3&=0xFE;seg3|=0x00;//不显示实际时间第一位
		seg15&=0xFE;seg15|=0x00;//不显示实际时间第一位
		seg15&=0x01;seg15|=0x10;//显示实际时间第二位
		seg16&=0x01;seg16|=0x10;//显示实际时间第三位
		seg17&=0x01;seg17|=0x10;//显示实际时间第四位
	}
	if(Run_Status == 1 && Run_Flag > 1 && DownTime_Over.L0 == 0 && RelTime_State.L0 == 1)//运行时
    {
        seg16&=0xFE;seg16|=0x00;//时间冒号消失
    }
	
	/*********************Set_Time*********************/
	/***********Set_Time千位***********/
	SH=dis_set_time/3600/10;//计算十位单位的小时数
	H=dis_set_time/3600%10;//计算个位单位的小时数
	SM=dis_set_time%3600/60/10;//计算十分位单位的分钟数
	M=dis_set_time%3600/60%10;//计算个分位单位的分钟数

	/***********Set_Time第一位***********/
	if(SH == 0)
	{
		seg17&=0xFE;seg17|=0x01;//显示实际时间第一位
		seg18&=0xFE;seg18|=0x01;//显示实际时间第一位
	}
	else
	{
		seg17&=0xFE;seg17|=0x00;//显示实际时间第一位
		seg18&=0xFE;seg18|=0x01;//显示实际时间第一位
	}
	/***********Set_Time第二位***********/
	seg18&=0x01;seg18|=Data1[H%10];//显示设定时间第二位
	/***********Set_Time第三位***********/
	seg19&=0x01;seg19|=Data1[SM%10];//显示设定时间第三位
	/***********Set_Time第四位***********/
	seg20&=0x01;seg20|=Data1[M%10];//显示设定时间第四位
	/***********Set_Time冒号图标*********/
	seg19&=0xFE;seg19|=0x01;//显示设定时间冒号
	/***********Set_Time单位图标*********/
	seg20&=0xFE;seg20|=0x01;//显示时间单位图标
	
	if(SetTime_State.L0 == 0)//没有设置时间
    {
		seg17&=0xFE;seg17|=0x00;//显示设定时间第一位‘-’
		seg18&=0x00;seg18|=0x10;//显示设定时间第二位‘-’
		seg19&=0x01;seg19|=0x10;//显示设定时间第三位‘-’
		seg20&=0x01;seg20|=0x10;//显示设定时间第四位‘-’
	}
	if(Time_ShowFlag && EC11A_Knob == 0)//时间到和旋钮无操作时
    {
		seg17&=0xFE;seg17|=0x00;//不显示设定时间第一位
		seg18&=0x00;seg18|=0x00;//不显示设定时间第二位
		seg19&=0x01;seg19|=0x00;//不显示设定时间第三位
		seg20&=0x01;seg20|=0x00;//不显示设定时间第四位
	}
	
	/*********************下划线*********************/
	if(Work_All)//在全局设置时
    {
        seg1&=0x03;seg1|=0xFC;//L5和L6下面的下划线  
        if(Work_All_Time)//选中工位1和熄灭下划线时
        {        
            switch(Work_Option)
            {
				case 1:seg1&=0x03;seg1|=0xF4;//L5下划线熄灭
                    break;
                case 2:seg1&=0x03;seg1|=0xF8;//L6下划线熄灭
                    break;
				case 3:seg1&=0x03;seg1|=0xEC;//L4下划线熄灭
                    break;
                case 4:seg1&=0x03;seg1|=0xDC;//L3下划线熄灭
                    break;
                case 5:seg1&=0x03;seg1|=0x7C;//L1下划线熄灭
                    break;
                case 6:seg1&=0x03;seg1|=0xBC;//L2下划线熄灭
                    break;
                default:
                    break;      
            }
        }
    }
    else
    {		 		 
        switch(Work_Option)//工位号选择
        {
			case 1:seg1&=0x03;seg1|=0x08;//显示L5下面的下划线
                    break;
            case 2:seg1&=0x03;seg1|=0x04;//显示L6下面的下划线
                    break;
			case 3:seg1&=0x03;seg1|=0x10;//显示L4下面的下划线
                    break;
			case 4:seg1&=0x03;seg1|=0x20;//显示L3下面的下划线
                    break;
            case 5:seg1&=0x03;seg1|=0x80;//显示L1下面的下划线
                    break;
            case 6:seg1&=0x03;seg1|=0x40;//显示L2下面的下划线
                    break;
            default:     
                break;
        }
    }
	
	if(Param.type == 0 || Param.type == 2)//设置为四联时L3和L4不显示
	{
		seg1&=0xCF;
		seg2&=0x3F;
		seg8&=0x00;
		seg9&=0x00;
		seg10&=0x00;
		seg11&=0x00;
	}
	
	if(Param.type <= 1)//设置成加热款
	{
		seg3&=0xFD;seg3|=0x00;
		seg30&=0x00;
		seg31&=0x00;
		seg32&=0x00;
		seg12&=0x00;
		seg13&=0x00;
		seg14&=0x00;
		seg25&=0xF9;seg25|=0x00;
    }
	
	Write_Addr_Dat_N(0, seg1,1);
	Write_Addr_Dat_N(2, seg2,1);
	Write_Addr_Dat_N(4, seg3,1);
	Write_Addr_Dat_N(6, seg4,1);
	Write_Addr_Dat_N(8, seg5,1);
	Write_Addr_Dat_N(10, seg6,1);
	Write_Addr_Dat_N(12, seg7,1);
	Write_Addr_Dat_N(14, seg8,1);
	Write_Addr_Dat_N(16, seg9,1);
	Write_Addr_Dat_N(18, seg10,1);
	Write_Addr_Dat_N(20, seg11,1);
	Write_Addr_Dat_N(22, seg12,1);
	Write_Addr_Dat_N(24, seg13,1);
	Write_Addr_Dat_N(26, seg14,1);
	Write_Addr_Dat_N(28, seg15,1);
	Write_Addr_Dat_N(30, seg16,1);
	Write_Addr_Dat_N(32, seg17,1);
	Write_Addr_Dat_N(34, seg18,1);
	Write_Addr_Dat_N(36, seg19,1);
	Write_Addr_Dat_N(38, seg20,1);
	Write_Addr_Dat_N(40, seg21,1);
	Write_Addr_Dat_N(42, seg22,1);
	Write_Addr_Dat_N(44, seg23,1);
	Write_Addr_Dat_N(46, seg24,1);
	Write_Addr_Dat_N(48, seg25,1);
	Write_Addr_Dat_N(50, seg26,1);
	Write_Addr_Dat_N(52, seg27,1);
	Write_Addr_Dat_N(54, seg28,1);
	Write_Addr_Dat_N(56, seg29,1);
	Write_Addr_Dat_N(58, seg30,1);
	Write_Addr_Dat_N(60, seg31,1);
	Write_Addr_Dat_N(62, seg32,1);
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
        else if(Speed_ADDMode.L1 == 4)//速度显示清零
		{
			Display_RelSpeed.L1 = 0;
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
		else if(Speed_ADDMode.L2 == 4)//速度显示清零
		{
			Display_RelSpeed.L2 = 0;
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
		else if(Speed_ADDMode.L3 == 4)//速度显示清零
		{
			Display_RelSpeed.L3 = 0;
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
		else if(Speed_ADDMode.L4 == 4)//速度显示清零
		{
			Display_RelSpeed.L4 = 0;
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
		else if(Speed_ADDMode.L5 == 4)//速度显示清零
		{
			Display_RelSpeed.L5 = 0;
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
		else if(Speed_ADDMode.L6 == 4)//速度显示清零
		{
			Display_RelSpeed.L6 = 0;
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
		else if(Speed_ADDMode.L7 == 4)//速度显示清零
		{
			Display_RelSpeed.L7 = 0;
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
		else if(Speed_ADDMode.L8 == 4)//速度显示清零
		{
			Display_RelSpeed.L8 = 0;
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
 * 函数原型：void ADD_Show(float dT)
 * 功    能：显示上升时间
 * 输    入: dT:执行周期
 * 参    数：float dT
*****************************************************************
*/
void ADD_Show(float dT)
{
    static float T;
	if(Run_Status == 0)
		return;
    if(ADD_Wait_Count)//加入慢速上升标志位大于一并且升温状态在慢速上升时
    {
        T += dT;
        if(T >= 0.2f)//1S
        {
            ADD_Wait_Count--;//慢速上声标志位--
            if(ADD_Wait_Count == 0)//慢速上升标志位等于0时
                Temp_ADDMode = 4;//进入稳定温度模式
            T = 0;
        }
    }
}

/*
*****************************************************************
 * 函数原型：void Deal_Temp(void)
 * 功    能：温度显示处理
*****************************************************************
*/
void Deal_Temp(void)
{
    if(Run_Status == 0 || (Run_Status == 1 && Temp_State == 0))//没启动和没设置的情况下
    {
		Rel_Temp = Ture_Temp;//显示实际测得温度
		Temp_New = 0;
		Temp_Last = 0;
    }
    else
    {
        if(Temp_ADDMode == 0)//判断数据处理显示
        {
			if(Rel_Temp < Ctrl_Temp)//实际温度大于控制温度
			{	
				Temp_ADDMode = 1;//升温
				Temp_New = 0;
				Temp_Last = Rel_Temp;
			}
			else
			{
				Temp_ADDMode = 2;//保温
				Temp_New = 0;
				Temp_Last = Rel_Temp;
			}
		}
        else if(Temp_ADDMode == 1)//在加热模式下
        {
			if(Rel_Temp < Ture_Temp)
				Temp_New = Ture_Temp;//记录当前温度
            if(Temp_New > Temp_Last)//当前温度大于上一次温度
                Rel_Temp = Temp_New;//显示当前温度
            else//当前温度小于等于上一次温度
            {
                Rel_Temp = Temp_Last;//显示上一次温度，不让温度小于当前温度。呈现攀升温度的现象
                Temp_New = Temp_Last;//将上一次温度赋值给当前温度
            }
            Temp_Last = Temp_New;//将当前温度保存
			if(Rel_Temp >= Ctrl_Temp - 20)//假如显示值大于等于设定值
            {
				ADD_Wait_Count = (-(Temp_New-Ctrl_Temp)*10);//200S的缓慢升温显示  
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
                Temp_ADDMode = 4;//进入稳定模式
            }
        }
        else if(Temp_ADDMode == 3)//缓慢
        {
            if(Rel_Temp < Ctrl_Temp)
				Rel_Temp=(Ctrl_Temp-20)+(20-(ADD_Wait_Count)*2/20);//缓慢显示数值
        }
		else if(Temp_ADDMode == 4)//稳定模式下
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
        default:
            break;
    }
	Display_WorkSpeed(Display_Speed.L1,Display_Speed.L2,
					  Display_Speed.L3,Display_Speed.L4,
					  Display_Speed.L5,Display_Speed.L6,
				      Rel_Speed.L0,Set_Speed.L0,Rel_Temp,Set_Temp,Rel_Time.L0+59,Set_Time.L0);
}
