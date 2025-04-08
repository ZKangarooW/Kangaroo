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
	for(uint8_t i=0;i <= 9;i++)
	{
		Param.P_Param[i][0] = 300;//时间
		Param.P_Param[i][2] = 500;//安全温度
		Param.P_Param[i][3] = 0;//离心率
		Param.type = 1;//0：12Pro  1：10Pro
		Param.P_Param[i][1] = 110;//转速
	}
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
		Set_Time = Param.P_Param[PMode_Option][0];//时间
		Val_xg = Param.P_Param[PMode_Option][3];//离心力
		Val_Speed = Param.P_Param[PMode_Option][1];//速度数组
		Set_Speed =  Speed_Val[Val_Speed];
		Safe_Set_Temp = Param.P_Param[PMode_Option][2];//安全温度
		SetOK_Flag = 1;
		Save_Param_En = 1;
	}
	else
	{
		Set_Time = Param.P_Param[PMode_Option][0];//时间
		if(Speed_Mode)
		{
			Val_xg = Param.P_Param[PMode_Option][3];//离心力数组
			Set_Speed = xg_Val[Val_xg];
		}	
		else
		{
			Val_Speed = Param.P_Param[PMode_Option][1];//速度数组
			Set_Speed =  Speed_Val[Val_Speed];
		}
		
		Safe_Set_Temp = Param.P_Param[PMode_Option][2];//安全温度
		SetOK_Flag = 1;
	}
	
	ROW1_H;
	ROW2_H;
	ROW3_L;
	if(HAL_GPIO_ReadPin(COL1_GPIO_Port,COL1_Pin) == 0 && HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_Pin )== 0)
	{
		Param.type++;
		if(Param.type > 1)
			Param.type = 0;
		Save_Param_En = 1;
		switch(Param.type)
		{
			case 0:
				Speed_MAX = 110;
				break;
			case 1:
				Speed_MAX = 90;
				break;
		}
		for(uint8_t i=0;i <= 9;i++)
		{
			Param.P_Param[i][0] = 300;//时间
			Param.P_Param[i][2] = 500;//安全温度
			Param.P_Param[i][3] = 0;//离心率
			Param.P_Param[i][1] = Speed_MAX;//转速
		}
		Set_Speed =  Speed_Val[Speed_MAX];
	}
	
	switch(Param.type)
	{
		case 0:
			Speed_MAX = 110;
			break;
		case 1:
			Speed_MAX = 90;
			break;
	}
	
	//保存参数
	if(Save_Param_En == 1)
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
