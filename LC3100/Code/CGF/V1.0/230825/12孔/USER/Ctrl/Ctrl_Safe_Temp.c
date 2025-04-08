#include "Ctrl_Safe_Temp.h"

/*
*****************************************************************
 * 函数原型：void Check_Safe_Temp(float dT)
 * 功    能：检测安全温度
*****************************************************************
*/
void Check_Safe_Temp(float dT)
{
	if(SafeTemp.Rel <= SafeTemp.Set)
	{
		SafeTemp.Flag = 0;//清除安全温度报警
		if(SafeTemp.Rel+50 <= SafeTemp.Set)
		{
			COLD_OFF;//关闭风扇
			SafeTemp.Twinkleg = 0;//安全温度图标不闪烁
		}
		else
		{
			COLD_ON;//打开风扇
		}
		return;
	}	
    if(sys.Run_Status && sys.Motor_Stop == 0)
    {
        if(SafeTemp.Rel > SafeTemp.Set && SafeTemp.Flag == 0)//假如实际温度大于设定温度时
        {
            SafeTemp.Flag = 1;//温度超标
            SafeTemp.Twinkleg = 1;//安全温度图标闪烁
            sys.Motor_Stop = 1;//进入减速模式
            Beep_Flash = 5;//蜂鸣器响5下
            Speed.ADDMode = 2;//进入减速模式下
        }
    }        
}

/*
*****************************************************************
 * 函数原型：void Check_Shock(float dT)
 * 功    能：检测震动
*****************************************************************
*/
void Check_Shock(float dT)
{
	static float T;
	if(HAL_GPIO_ReadPin(UC_IN3_GPIO_Port,UC_IN3_Pin)== 0)//震动开关放开
	{
		sys.Hardware_Damage = 1;//硬件损坏
        while(1)
        {
            T += dT;
            if(T <= 1)//1S
            {
                Lcd_All();
                
            }
            else if(T > 1 && T <= 2)
            {
                Lcd_Clr();
            }
            else if(T > 2)
            {
                T = 0;
            }
            PWM = 0;	
            HAL_GPIO_WritePin(BREAKEZ_GPIO_Port,BREAKEZ_Pin,GPIO_PIN_RESET);//高电平不刹车，低电平刹车
        }
	}
	else
	{
		sys.Hardware_Damage = 0;//硬件完好
	}
}
