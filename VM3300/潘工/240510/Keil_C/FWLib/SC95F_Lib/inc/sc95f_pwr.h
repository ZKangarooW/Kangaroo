//************************************************************
//  Copyright (c) 深圳市赛元微电子股份有限公司
//	文件名称: 		sc95f_pwr.h
//	作者		:
//	模块功能: 		PWR固件库函数头文件
// 	最后更正日期:	2024年1月18日
// 	版本:				V1.0002
//  说明:该文件仅适用于SC95F系列芯片
//*************************************************************

#ifndef _sc95f_PWR_H_
#define _sc95f_PWR_H_

#include "sc95f.h"
#include <intrins.h>

void PWR_DeInit(void);
void PWR_EnterSTOPMode(void);
void PWR_EnterIDLEMode(void);
void PWR_SoftwareReset(void);

#endif

/******************* (C) COPYRIGHT 2018 SinOne Microelectronics *****END OF FILE****/