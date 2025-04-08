#include "Ctrl_Safe_Temp.h"

/**
 * @brief 检测安全温度
 *
 * @param dT 任务周期
 */
void Check_Safe_Temp(float dT)
{
	static float T;
	if (PT_VALUE_1_TEMP >= 2000)
	{
		T = 0;
		return;
	}
	else
	{
		T += dT;
		if (T > 2.0f)
			T = 2.0f;
	}

	if (T >= 2.0f)
	{
		if (Temp.Rel <= Temp.Set)
		{
			Temp.Safe_Temp_Flag = 0; // 清除安全温度报警
			if (Temp.Rel + 50 <= Temp.Set)
			{
				Temp.Icn = 0; // 安全温度图标不闪烁
			}

			return;
		}
		if (Temp.Rel > Temp.Set && Temp.Safe_Temp_Flag == 0) // 假如实际温度大于设定温度时
		{
			Temp.Safe_Temp_Flag = 1; // 温度超标
			Temp.Icn = 1;			 // 安全温度图标闪烁
			Beep_Flash = 5;			 // 蜂鸣器响5下
			sys.Run_Status = 0;
			sys.SetMode_Option = 0;
			Speed.ADDMode = 2;
			SetOK_Flag = 1;
		}
	}
}
