#include "Param.h"

/**********结构体**********/
struct _Save_Param_ Param;//原始数据

/**********全局变量声明******/
uint8_t Save_Param_En;

/*
*****************************************************************
 * 函数原型：void Param_Reset(void)
 * 功    能：初始化硬件中的参数
*****************************************************************
*/
void Param_Reset(void)
{
	Param.Flash_Check_Start = FLASH_CHECK_START;
	
	Param.Heat_Temp = 450;//初始温度45℃
	Param.Cool_Temp = 260;//初始温度26℃
	Param.CountDown_Time = 1200;//20分钟
	
	Param.Calibration_Temp = 1.0;//温度校准系数
	
	Param.Flash_Check_End  = FLASH_CHECK_END;
}

/*
*****************************************************************
 * 函数原型： void Param_Save(void)
 * 功    能： 保存硬件中的参数
*****************************************************************
*/
void Param_Save(void)
{
	Flash_Write((uint8_t *)(&Param),sizeof(Param));
}

/*
*****************************************************************
 * 函数原型：void Param_Read(void)
 * 功    能：读取硬件中的参数，判断是否更新
*****************************************************************
*/
void Param_Read(void)
{
	Flash_Read((uint8_t *)(&Param),sizeof(Param));
	
	//板子从未初始化
	if(Param.Flash_Check_Start != FLASH_CHECK_START || Param.Flash_Check_End != FLASH_CHECK_END)
	{
		Param_Reset();
		Heat_Temp.Set_Temp = Param.Heat_Temp;//加热区域温度
		Cool_Temp.Set_Temp = Param.Cool_Temp;//制冷区域温度
		Time.Set_Time = Param.CountDown_Time;//倒计时时间
		Calibration_Temp = Param.Calibration_Temp;//温度校准系数
		SetOK_Flag = 1;
		Save_Param_En = 1;
	}
	else
	{
		Heat_Temp.Set_Temp = Param.Heat_Temp;//加热区域温度
		Cool_Temp.Set_Temp = Param.Cool_Temp;//制冷区域温度
		Time.Set_Time = Param.CountDown_Time;//倒计时时间
		Calibration_Temp = Param.Calibration_Temp;//温度校准系数
		SetOK_Flag = 1;
	}
	
	//保存参数
	if(Save_Param_En)
	{
		Save_Param_En = 0;
		Param_Save();
	}
}

/*
*****************************************************************
 * 函数原型：void Param_Save_Overtime(float dT)
 * 功    能：保存标志位置1，0.5s后保存
*****************************************************************
*/
void Param_Save_Overtime(float dT)
{
	static float time;
	
	if(Save_Param_En)
	{
		time += dT;
		
		if(time >= 0.5f)
		{
			Param_Save();
			Save_Param_En = 0;
		}
	}
	else 
		time = 0;
}
