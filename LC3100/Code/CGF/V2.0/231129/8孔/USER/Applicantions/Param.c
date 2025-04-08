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
	for(uint8_t i=0;i <= 8;i++)
	{
		Param.P_Param[i][0] = 300;//时间
		Param.P_Param[i][1] = 2300;//转速
		Param.P_Param[i][2] = 500;//安全温度
		Param.P_Param[i][3] = 100;//离心率
	}
    /***************CGF*******************/
    Param.P_Param[1][0] = 840;//时间
    Param.P_Param[1][1] = 2450;//转速
    Param.P_Param[2][1] = 2150;//转速
    Param.P_Param[3][1] = 2450;//转速
    Param.P_Param[4][1] = 2690;//转速
    /***************PrP*******************/
    Param.P_Param[5][0] = 300;//时间
    Param.P_Param[5][1] = 3930;//转速
    /***************APrF******************/
    Param.P_Param[6][0] = 720;//时间
    Param.P_Param[6][1] = 1300;//转速
    /***************IPrF******************/
    Param.P_Param[7][0] = 300;//时间
    Param.P_Param[7][1] = 680;//转速
    
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
		Time.Set = Param.P_Param[PMode.Option][0];//时间
		SafeTemp.Set = Param.P_Param[PMode.Option][2];//安全温度
        if(Speed.Unit)
			Speed.Set = Param.P_Param[PMode.Option][3];//离心率
		else
			Speed.Set = Param.P_Param[PMode.Option][1];//转速
		SetOK_Flag = 1;
		Save_Param_En = 1;
	}
	else
	{
		Time.Set = Param.P_Param[PMode.Option][0];//时间
		SafeTemp.Set = Param.P_Param[PMode.Option][2];//安全温度
        if(Speed.Unit)
			Speed.Set = Param.P_Param[PMode.Option][3];//离心率
		else
			Speed.Set = Param.P_Param[PMode.Option][1];//转速
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
