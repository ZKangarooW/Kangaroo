#include "Ctrl_Safe_Temp.h"

/*
*****************************************************************
 * 函数原型：void Check_Safe_Temp(float dT)
 * 功    能：检测安全温度
*****************************************************************
*/
void Check_Safe_Temp(float dT)
{
	if(Safe_Rel_Temp < Safe_Set_Temp)
	{
		Safe_Temp_Flag = 0;//清除安全温度报警
		if(Safe_Rel_Temp+50 < Safe_Set_Temp)
		{
			Safe_Temp_Twinkleg = 0;//安全温度图标不闪烁
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
