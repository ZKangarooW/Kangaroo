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
	Param.Mode = 0;//速度模式
	Param.type = 2;//0：常规款 1：2P 2：3D 3：西林瓶

	if(Param.type==0)
		Param.Speed = 3000;//转速
	else if(Param.type==1)
		Param.Speed = 1200;//转速
	else if(Param.type==2)
		Param.Speed = 80;//转速
	else if(Param.type==3)
		Param.Speed = 2000;//转速
	
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
		Speed_Mode = Param.Mode;//速度模式
		Save_Param_En = 1;//保存标志位置一
		SetOK_Flag = 1;//设置标志位置一
	}
	else
	{
		Set_Time = Param.Time;//时间
		Set_Speed = Param.Speed;//转速
		Speed_Mode = Param.Mode;//速度模式
		SetOK_Flag = 1;//设置标志位置一
	}
	
	if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin) == 0 && HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)== 0)//按下按键
	{
		Param.type++;
		if(Param.type > 3)
			Param.type = 0;
		Save_Param_En = 1;
		switch(Param.type)
		{
			case 0://常规
				Speed_MAX = 3000;
				Set_Speed = Speed_MAX;//转速
				Param.Time = 120;//时间
				Speed_Mode = Param.Mode = 0;
				break;
			case 1://2P
				Speed_MAX = 1200;
				Set_Speed = Speed_MAX;//转速
				Param.Time = 120;//时间
				Speed_Mode = Param.Mode = 1;
				break;
			case 2://3D
				Speed_MAX = 80;
				Set_Speed = Speed_MAX;//转速
				Param.Time = 120;//时间
				Speed_Mode = Param.Mode = 1;
				break;
			case 3://西林瓶
				Speed_MAX = 2000;
				Set_Speed = Speed_MAX;//转速
				Param.Time = 120;//时间
				Speed_Mode = Param.Mode = 1;
				break;
		}
		Param.Speed = Speed_MAX;
	}
	switch(Param.type)
	{
		case 0://常规
			Speed_MAX = 3000;
			break;
		case 1://1P 2P
			Speed_MAX = 1200;
			break;
		case 2://3D
			Speed_MAX = 80;
            break;
		case 3://西林瓶
			Speed_MAX = 2000;
			break;
	}
	
	//保存参数
	if(Save_Param_En)
	{
		Save_Param_En = 0;//保存标志位置零
		Param_Save();//保存到Flash
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
