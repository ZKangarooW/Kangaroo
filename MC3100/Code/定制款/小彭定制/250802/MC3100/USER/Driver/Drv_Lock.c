#include "Drv_Lock.h"

/**********全局变量声明******/
uint8_t Lock_Status;//盖子的状态

/*
*****************************************************************
 * 函数原型：void Ctrl_Lock(float dT)
 * 功    能：关开盖检测
*****************************************************************
*/
void Ctrl_Lock(float dT)
{
	if((HAL_GPIO_ReadPin(KEY_UP_GPIO_Port,KEY_UP_Pin)== 1))//盖子闭合时
	{
		Lock_Status = 0;//关闭盖子，显示图标
	}
	else
	{
		Lock_Status = 1;//打开盖子，显示图标
	}
}
