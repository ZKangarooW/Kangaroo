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
		Param.Time = 0;//时间
		Param.Speed = 3000;//转速
	Param.type = 0;//0：3000 1:1200
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
		Set_Time = Param.Time;//时间
		Set_Speed = Param.Speed;//转速
		SpeedSet_Flag=TimeSet_Flag=1;//进入设置
		Save_Param_En = 1;
	}
	else
	{
		Set_Time = Param.Time;//时间
		Set_Speed = Param.Speed;//转速
		SpeedSet_Flag=TimeSet_Flag=1;//进入设置
	}
	
	if(HAL_GPIO_ReadPin(EC11A[1].Key_GPIO,EC11A[1].Key_Pin) == KEY_DOWN)//按下按键
	{
		Param.type++;
		if(Param.type > 1)
			Param.type = 0;
		Save_Param_En = 1;
		switch(Param.type)
		{
			case 0:
				Speed_MAX = 3000;
				Speed_MIN = 1500;
				Param.Time = 0;//时间
				Set_Time = Param.Time;//时间
				break;
			case 1:
				Speed_MAX = 1200;
				Speed_MIN = 500;
				Param.Time = 0;//时间
				Set_Time = Param.Time;//时间
				break;
		}
		Set_Speed = Speed_MAX;//转速
	}
	
	switch(Param.type)
	{
		case 0:
			Speed_MAX = 3000;
			Speed_MIN = 1500;
			break;
		case 1:
			Speed_MAX = 1200;
			Speed_MIN = 500;
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
