#include "Show.h"

/**********全局变量声明******/
uint8_t Display_Flag;//用于显示刷新
uint8_t Display_OFF;//不显示屏幕

/**********局部变量声明******/
uint8_t Speed_ShowFlag;//速度显示的标志位 0:常亮 1：熄灭
uint8_t DIG;//DIG的数据
uint8_t SPEED_Tab[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6};//显示0-9
uint8_t Cnt;//显示位数，用于刷新

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
    static float T;
    if(sys.Run_Status && !EC11A[0].EC11A_Knob)//运行时
    {
        T += dT;
        if(T <= 0.8f)
        {
            Speed_ShowFlag = 0;
        }
        else if(T > 0.8f && T <= 1.0f)
        {
            Speed_ShowFlag = 1;//熄灭
        }
        else
        {
            T = 0;
        }
    }
    else
    {
        T = 0;
        Speed_ShowFlag = 0;
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
 * 函数原型：void Check_Display(float dT)
 * 功    能：检测不操作时熄屏
*****************************************************************
*/
void Check_Display(float dT)
{
	static float T;
	if(EC11A[0].EC11A_Knob || sys.Run_Status)//在旋旋钮时或者在运行时或者按下按钮时
	{
		T = 0;//计时清零
		Display_OFF = 0;//打开屏幕
	}
	else
	{
		T +=dT;
		if(T > 300)
		{
			Display_OFF = 1;//关闭屏幕
			T = 300;
		}
	}
}

/*
*****************************************************************
 * 函数原型：void Display_SpeedShow(int16_t speed)
 * 功    能：显示速度
 * 输    入: speed：要显示的速度
 * 参    数：int16_t speed
*****************************************************************
*/
void Display_Speed(int16_t speed)
{
	uint8_t Val;//用于百十个取出来的数字

    if(Cnt == 1)
    {
        /***********L1千位***********/
        if(speed > 999)//大于999时
        {	
            Val=speed/1000;//取出千位的数字			
            UCdata_Display(SPEED_Tab[Val]);
                DIGdata_Display(0x80);
        }
        else//小于999时
        {
            DIGdata_Display(0x00);
        }  
        if(Display_OFF || Speed_ShowFlag)
        {
            DIGdata_Display(0x00);
        }
    }
    else if(Cnt == 2)
    {
        /***********L1百位***********/
        if(speed > 99)//大于99时
        {
            Val=speed/100;//取出百位的数字
            if(speed > 999)//加入大于999时
                Val=Val%10;//取出百位的数字
            UCdata_Display(SPEED_Tab[Val]); 
                DIGdata_Display(0x40);
        }
        else
        {
            DIGdata_Display(0x00);//不显示
        }
        if(Display_OFF || Speed_ShowFlag)
        {
            DIGdata_Display(0x00);
        }
        
    }
    else if(Cnt == 3)
    {
        /***********L1十位***********/
        if(speed > 9)//大于9时
        {
            Val=speed/10;//取出十位的数字
            if(speed > 99)//大于99时
                Val=Val%10;//取出十位的数字
            UCdata_Display(SPEED_Tab[Val]);  
                DIGdata_Display(0x20);         
        }
        else
        {
            DIGdata_Display(0x00);//不显示
        }
        if(Display_OFF || Speed_ShowFlag)
        {
            DIGdata_Display(0x00);
        }
    }
    else if(Cnt == 4)
    {
        /***********L1个位***********/
        Val=speed%10;//取出个位
        UCdata_Display(SPEED_Tab[Val]);
            DIGdata_Display(0x10);
        if(Display_OFF || Speed_ShowFlag)
        {
            DIGdata_Display(0x00);
        }
    }
    else if(Cnt == 5)//刷新
    {
        DIGdata_Set();
        Cnt = 0;
    }
}

/*
*****************************************************************
 * 函数原型：void Deal_Speed(void)
 * 功    能：速度显示处理
*****************************************************************
*/
void Deal_Speed(void)
{
    /**********SpeedL1_ADD_Mode**********/
	if(sys.Motor_Stop)
	{
		if(Speed.Display > Speed.Rel && Speed.Display > 0)
		{
			Speed.Display--;//显示控制速度
		}
		if(Speed.Display <= 0)
		{
			Speed.Display = 0;
		}
	}
	else
	{
		if(Speed.ADDMode == 0)//在电机控制中，速度未处理
		{
			if(Speed.Rel < Speed.Ctrl)
			{
				Speed.ADDMode = 1;//进入加速模式下
				Speed.Display = Speed.Rel;
			}
			else if(Speed.Rel > Speed.Ctrl)
			{
				Speed.ADDMode = 2;//进入减速模式下
				Speed.Display = Speed.Rel;
			}
		}
		if(Speed.ADDMode==1)//在进入加速模式下
		{	
			if(Speed.Display < Speed.Rel && Speed.Display < Speed.Ctrl)
			{
				Speed.Display++;//显示控制速度
			}
			if(Speed.Display >= Speed.Ctrl)
			{
				Speed.ADDMode = 3;
			}
		}
		else if(Speed.ADDMode == 2)//速度下降模式下
		{
			if(Speed.Display > Speed.Rel && Speed.Display > Speed.Ctrl)
			{
				Speed.Display--;//显示控制速度
			}
			else if(Speed.Display <= Speed.Ctrl)
			{
				Speed.ADDMode = 3;
			}
		}
		else if(Speed.ADDMode == 3)//速度稳定模式下
		{
			Speed.Display = Speed.Ctrl;//显示控制速度
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
	if(Display_Flag == 1)
	{
		Cnt++;
		if(!sys.Run_Status)
		{
			Speed.Display = Speed.Set;
		}
		else
		{
			if(EC11A[0].EC11A_Knob > 0)
			{
				Speed.Display = Speed.Set;
			}
			else
			{
				Deal_Speed();
			}
		}
		Display_Speed(Speed.Display);
		Display_Flag = 0;
	}
}
