#include "Drv_Lock.h"

/**********全局变量声明******/
uint8_t Lock1_Status,Lock2_Status;//电磁铁的状态

/*
*****************************************************************
 * 函数原型：void Ctrl_Lock(float dT)
 * 功    能：电磁铁控制
*****************************************************************
*/
void Ctrl_Lock(float dT)
{
	if(Lock1_Status == 1)
	{
		Lock1_ON;//打开电磁锁1
		Lock1_Status = 0;
	}
	else
	{
		Lock1_OFF;//关闭电磁锁1
	}
	if(Lock2_Status == 1)
	{
		Lock2_ON;//打开电磁锁2
		Lock2_Status = 0;
	}
	else
	{
		Lock2_OFF;//关闭电磁锁2
	}
	if((HAL_GPIO_ReadPin(UC_IN1_GPIO_Port,UC_IN1_Pin)== 1)&&(HAL_GPIO_ReadPin(UC_IN2_GPIO_Port,UC_IN2_Pin)== 1))//电磁锁1和电磁锁2都闭合时
	{
		Lid_State = 0;//关闭盖子，显示图标
	}
	else
	{
		Lid_State = 1;//打开盖子，显示图标
	}
	
}
