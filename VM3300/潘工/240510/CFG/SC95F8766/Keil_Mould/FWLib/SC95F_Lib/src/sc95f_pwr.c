//************************************************************
//  Copyright (c) 深圳市赛元微电子股份有限公司
//	文件名称: 		sc95f_pwr.c
//	作者		:
//	模块功能: 		PWR固件库函数C文件
// 	最后更正日期:	2024年1月18日
// 	版本:				V1.0002
//  说明    :该文件仅适用于SC95F系列芯片
//*************************************************************
#include "sc95f_pwr.h"

/**************************************************
*函数名称:void PWR_DeInit(void)
*函数功能:PWR相关寄存器复位至缺省值
*入口参数:void
*出口参数:void
**************************************************/
void PWR_DeInit(void)
{
  PCON &= 0XFC;
}

/**************************************************
*函数名称:void PWR_EnterSTOPMode(void)
*函数功能:MCU进入STOP模式
*入口参数:void
*出口参数:void
**************************************************/
void PWR_EnterSTOPMode(void)
{
  PCON |= 0X02; //进入Stop
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
	_nop_();
  _nop_();
}
/**************************************************
*函数名称:void PWR_EnterIDLEMode(void)
*函数功能:MCU进入IDLE模式
*入口参数:void
*出口参数:void
**************************************************/
void PWR_EnterIDLEMode(void)
{
  PCON |= 0X01;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
	_nop_();
  _nop_();
}
/**************************************************
*函数名称:void PWR_SoftwareReset(void)
*函数功能:MCU进入软件复位
*入口参数:void
*出口参数:void
**************************************************/
void PWR_SoftwareReset(void)
{
	PCON |= 0X08;	//软件复位
	_nop_();		
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
  _nop_();
  _nop_();
	_nop_();
}
/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/