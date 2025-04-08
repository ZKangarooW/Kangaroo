#include "Param.h"

/**********结构体**********/
struct _Save_Param_ Param;//原始数据

/**********全局变量声明******/
uint8_t Save_Param_En;

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xC2

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
		Param.P_Param[i][3] = 100;//离心率
		Param.type = 2;//0：15Pro  1：13Pro 2：12Pro
        if(Param.type==0)
            Param.P_Param[i][1] = 14500;//转速
        else if(Param.type==1)
            Param.P_Param[i][1] = 13000;//转速
        else if(Param.type==2)
            Param.P_Param[i][1] = 12000;//转速
        
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
		Set_Speed = Param.P_Param[PMode_Option][1];//转速
		Safe_Set_Temp = Param.P_Param[PMode_Option][2];//安全温度
		SetOK_Flag = 1;
		Save_Param_En = 1;
	}
	else
	{
		Set_Time = Param.P_Param[PMode_Option][0];//时间
		if(Speed_Mode)
			Set_Speed = Param.P_Param[PMode_Option][3];//离心率
		else
			Set_Speed = Param.P_Param[PMode_Option][1];//转速
		Safe_Set_Temp = Param.P_Param[PMode_Option][2];//安全温度
		SetOK_Flag = 1;
	}
	
	ROW1_H;
	ROW2_H;
	ROW3_L;
	if(HAL_GPIO_ReadPin(COL1_GPIO_Port,COL1_Pin) == 0 && HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_Pin )== 0)
	{
		Param.type++;
		if(Param.type > 2)
			Param.type = 0;
		Save_Param_En = 1;
		switch(Param.type)
		{
			case 0:
				Speed_MAX = 14500;
				Xg_MAX = 14100;
				break;
			case 1:
				Speed_MAX = 13000;
				Xg_MAX = 11300;
				break;
			case 2:
				Speed_MAX = 12000;
				Xg_MAX = 10000;
				break;
		}
		for(uint8_t i=0;i <= 9;i++)
		{
			Param.P_Param[i][0] = 300;//时间
			Param.P_Param[i][1] = Speed_MAX;//转速
			Param.P_Param[i][2] = 500;//安全温度
			Param.P_Param[i][3] = 100;//离心率
		}
		Set_Speed =  Param.P_Param[0][1];
	}
		
	switch(Param.type)
	{
		case 0:
			Speed_MAX = 14500;
			Xg_MAX = 14100;
			break;
		case 1:
			Speed_MAX = 13000;
			Xg_MAX = 11300;
			break;
		case 2:
			Speed_MAX = 12000;
			Xg_MAX = 10000;
			break;
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
