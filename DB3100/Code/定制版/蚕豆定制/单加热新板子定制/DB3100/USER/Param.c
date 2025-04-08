#include "Param.h"

/**********结构体**********/
struct _Save_Param_ Param;//原始数据

uint8_t Save_Param_En = 0;

void Param_Reset()
{
	Param.Flash_Check_Start = FLASH_CHECK_START;
	for(uint8_t i=0;i <= 9;i++)
	{
		Param.P_Param[i][0] = 0;
		Param.P_Param[i][1] = 0;
	}
	Param.Flash_Check_End  = FLASH_CHECK_END;
}

/*
*****************************************************************
 * 函数原型： void JD_Param_Save(void)
 * 功    能： 保存硬件中的参数
*****************************************************************
*/
void Param_Save(void)
{
	Flash_Write((uint8_t *)(&Param),sizeof(Param));
}

void Param_Read(void)
{
	Flash_Read((uint8_t *)(&Param),sizeof(Param));
	
	//板子从未初始化
	if(Param.Flash_Check_Start!=FLASH_CHECK_START || Param.Flash_Check_End!=FLASH_CHECK_END)
	{
		Param_Reset();
//		set_time=Param.P_Param[run_mode][1];//开机设置设定时间为20min
		set_temp=Param.P_Param[run_mode][0];//开机设置设定温度37℃
		SetOK_Flag = 1;
		Save_Param_En = 1;
	}
	else
	{
//		set_time=Param.P_Param[run_mode][1];//开机设置设定时间为20min
		set_temp=Param.P_Param[run_mode][0];//开机设置设定温度37℃
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

