#include "Ctrl_Safe_Temp.h"

/*
*****************************************************************
 * 函数原型：void Check_Safe_Temp(float dT)
 * 功    能：检测安全温度
*****************************************************************
*/
void Check_Safe_Temp(float dT)
{
	if(Safe_Rel_Temp <= Safe_Set_Temp)
	{
		Safe_Temp_Flag = 0;//清除安全温度报警
		if(Safe_Rel_Temp+50 <= Safe_Set_Temp)
		{
			COLD_OFF;//关闭风扇
			Safe_Temp_Twinkleg = 0;//安全温度图标不闪烁
		}
		else
		{
			COLD_ON;//打开风扇
		}
		return;
	}	
	if(Safe_Rel_Temp > Safe_Set_Temp && Safe_Temp_Flag == 0)//假如实际温度大于设定温度时
	{
		Safe_Temp_Flag = 1;//温度超标
		Safe_Temp_Twinkleg = 1;//安全温度图标闪烁
		Beep_Flash = 5;//蜂鸣器响5下
		Speed_ADDMode = 2;//进入减速模式下
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
		{
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
	}
	else
	{
		sys.Hardware_Damage = 0;//硬件完好
	}
}
