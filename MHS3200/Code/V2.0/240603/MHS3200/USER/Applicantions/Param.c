#include "Param.h"

/**********结构体**********/
struct _Save_Param_ Param; // 原始数据

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
	SetALL_int(100, &Param.Speed); // 初始化设置速度
	SetALL_int32(0, &Param.Time);  // 初始化设置时间
	Param.Temp = 370;				   
#if (Integration_TYPE == 0)
	Param.type = 3;// 0：四联，1：六联，2：加热四联，3：加热六联
#endif
	Param.Flash_Check_End = FLASH_CHECK_END;
}

/*
*****************************************************************
* 函数原型： void Param_Save(void)
* 功    能： 保存硬件中的参数
*****************************************************************
*/
void Param_Save(void)
{
	Flash_Write((uint8_t *)(&Param), sizeof(Param));
}

/*
*****************************************************************
* 函数原型：void Param_Read(void)
* 功    能：读取硬件中的参数，判断是否更新
*****************************************************************
*/
void Param_Read(void)
{
	Flash_Read((uint8_t *)(&Param), sizeof(Param));

	// 板子从未初始化
	if (Param.Flash_Check_Start != FLASH_CHECK_START || Param.Flash_Check_End != FLASH_CHECK_END)
	{
		Param_Reset();
		SetALL_SpeedOver(&Set_Speed, &Param.Speed);
		SetALL_TimeOver(&Set_Time, &Param.Time);
		Set_Temp = Param.Temp;
		SetOK_Flag = 1;
		Save_Param_En = 1;
	}
	else
	{
		SetALL_SpeedOver(&Set_Speed, &Param.Speed);
		SetALL_TimeOver(&Set_Time, &Param.Time);
		Set_Temp = Param.Temp;
		SetOK_Flag = 1;
	}

#if (Integration_TYPE == 0)												   // 四六联
	if (HAL_GPIO_ReadPin(EC11A[1].Key_GPIO, EC11A[1].Key_Pin) == KEY_DOWN) // 按下按键
	{
		Param.type++;
		if (Param.type > 3)
			Param.type = 0;
		Save_Param_En = 1;
		if (Param.type <= 1)
		{
			MAX_Speed = 1500;
		}
		else
		{
			MAX_Speed = 1200;
		}
		SetALL_int(100, &Param.Speed); // 初始化设置速度
		SetALL_SpeedOver(&Set_Speed, &Param.Speed);
		SetALL_int32(0, &Param.Time); // 初始化设置时间
		Param.Temp = 0;
		SetALL_TimeOver(&Set_Time, &Param.Time);
		Set_Temp = Param.Temp;
	}

	if (Param.type <= 1)
		MAX_Speed = 1500;
	else
		MAX_Speed = 1200;
#elif (Integration_TYPE == 1) // 九联
	MAX_Speed = 1500;
#endif

	// 保存参数
	if (Save_Param_En)
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

	if (Save_Param_En)
	{
		time += dT;

		if (time >= 0.5f)
		{
			Param_Save();
			Save_Param_En = 0;
		}
	}
	else
		time = 0;
}
