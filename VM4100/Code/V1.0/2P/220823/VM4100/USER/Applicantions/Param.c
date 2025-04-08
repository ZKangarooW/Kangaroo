#include "Param.h"

/**********结构体**********/
struct _Save_Param_ Param;//原始数据

/**********全局变量声明******/
uint8_t Save_Param_En;//保存到Flash的标志位

/*
*****************************************************************
 * 函数原型：void Param_Reset(void)
 * 功    能：初始化硬件中的参数
*****************************************************************
*/
void Param_Reset(void)
{
	Param.Flash_Check_Start = FLASH_CHECK_START;
	Param.Time = 120;//时间
	Param.Speed = 1200;//转速
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
		Param_Reset();//初始化硬件中的参数
		Set_Time = Param.Time;//时间
		Set_Speed = Param.Speed;//转速
		Save_Param_En = 1;//保存标志位置一
		SetOK_Flag = 1;//设置标志位置一
	}
	else
	{
		Set_Time = Param.Time;//时间
		Set_Speed = Param.Speed;//转速
		SetOK_Flag = 1;//设置标志位置一
	}
	
	//保存参数
	if(Save_Param_En)
	{
		Param_Save();//保存到Flash
		Save_Param_En = 0;//保存标志位置零
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
	static float T;
	
	if(Save_Param_En)//加入保存标志位置一
	{
		T += dT;//时间加上dT
		
		if(T >= 0.5f)//大于0.5S时
		{
			Param_Save();//保存到Flash
			Save_Param_En = 0;//保存标志位置零
		}
	}
	else 
		T = 0;//时间清零
}
