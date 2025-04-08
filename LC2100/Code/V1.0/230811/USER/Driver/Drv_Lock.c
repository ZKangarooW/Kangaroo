#include "Drv_Lock.h"

/**********全局变量声明******/
uint8_t Lock_Status;//电磁铁的状态
uint8_t Lid_State;//显示图标

/*
*****************************************************************
 * 函数原型：void Ctrl_Lock(float dT)
 * 功    能：电磁铁控制
*****************************************************************
*/
void Ctrl_Lock(float dT)
{
	if(Lock_Status == 1)
	{
		Lock_ON;//打开电磁锁1
		Lock_Status = 0;
	}
	else
	{
		Lock_OFF;//关闭电磁锁1
	}
	if((HAL_GPIO_ReadPin(UC_IN_GPIO_Port,UC_IN_Pin)== 1))//电磁锁闭合时
	{
		Lid_State = 0;//关闭盖子，显示图标
	}
	else
	{
		Lid_State = 1;//打开盖子，显示图标
	}
}
