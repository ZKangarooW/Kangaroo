//************************************************************
//  Copyright (c) 深圳市赛元微电子股份有限公司
//	文件名称: 		sc95f_CRC.c
//	作者		:
//	模块功能: 		CRC固件库函数C文件
// 	最后更正日期:	2024年1月18日
// 	版本:				V1.0002
//  说明:该文件仅适用于SC95F系列芯片
//*************************************************************

#include "sc95f_CRC.h"
#include "intrins.H"

#if defined (SC95F8x6x) || defined (SC95F7x6x) || defined (SC95F8x1xB) || defined (SC95F7x1xB) || defined (SC95R751)\
		|| defined (SC95F7610B) || defined (SC95F7619B) || defined (SC95R602)  || defined (SC95R605) || defined (SC95F7x7x)\
		|| defined (SC95F8x7x)  || defined (SC95R503)
/* CRC固件库函数头文件 */
#include "CRC_Option_EW.h"

/**************************************************
*函数名称:unsigned long CRC_All()
*函数功能:求本工程HEX的CRC32校验值，该计算结果会根据OPTION的IAR Range不同而变化
*入口参数:void
*出口参数:
uint32_t:返回CRC计算结果
**************************************************/
uint32_t CRC_All()
{
 return CRC_CodeAllOption();
}

/**************************************************
*函数名称:uint32_t CRC_Frame(uint8_t* buff,uint8_t Length)
*函数功能:求输入帧的CRC校验值
*入口参数:
uint8_t*:buff:传入需要进行CRC计算的数组
uint8_t:Length:传入需要计算的数组长度
*出口参数:
uint32_t:CRC计算结果
**************************************************/
uint32_t CRC_Frame(uint8_t* buff, uint8_t Length)
{
	uint8_t i;
  uint32_t CRC_Input ,CRC_Result;
	
	CRC_ResetDROption();
  for(i = 0; i < Length; i++)
  {
    CRC_Input = *(buff + i);
		CRC_CalcOption(CRC_Input);
  }
  CRC_Result = CRC_GetOption();
  return CRC_Result;
}
#else
/**************************************************
*函数名称:unsigned long CRC_All()
*函数功能:求本工程HEX的CRC32校验值，该计算结果会根据OPTION的IAR Range不同而变化
*入口参数:void
*出口参数:
uint32_t:返回CRC计算结果
**************************************************/
uint32_t CRC_All()
{
  uint32_t CRC_Result;
  OPERCON |= 0x01;
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
	
  CRCINX = 0x00;
  CRC_Result = CRCREG;
  CRC_Result = CRCREG * 256 + CRC_Result;
  CRC_Result = CRCREG * 65536 + CRC_Result;
  CRC_Result = CRCREG * 16777216 + CRC_Result;
  return CRC_Result;
}

/**************************************************
*函数名称:uint32_t CRC_Frame(uint8_t* buff,uint8_t Length)
*函数功能:求输入帧的CRC校验值
*入口参数:
uint8_t*:buff:传入需要进行CRC计算的数组
uint8_t:Length:传入需要计算的数组长度
*出口参数:
uint32_t:CRC计算结果
**************************************************/
uint32_t CRC_Frame(uint8_t* buff, uint8_t Length)
{
  uint8_t i;
  uint32_t CRC_Result = 0;

  EA = 0;
  OPERCON |= 0x02;
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

  for(i = 0; i < Length; i++)
  {
    CRC_Result = *(buff + i);
    CRCREG = CRC_Result;
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

  CRCINX = 0x00;
  CRC_Result = CRCREG;
  CRC_Result = CRCREG * 256 + CRC_Result;
  CRC_Result = CRCREG * 65536 + CRC_Result;
  CRC_Result = CRCREG * 16777216 + CRC_Result;
  EA = 1;

  return CRC_Result;
}
#endif
/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/