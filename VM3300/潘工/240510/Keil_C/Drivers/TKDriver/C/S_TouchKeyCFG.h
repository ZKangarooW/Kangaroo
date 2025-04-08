//*************************************************************************************************
//Copyright (c) 深圳市赛元微电子有限公司
//文件名称:  S_TouchKeyCFG.h
//作者: 
//模块功能:  触控键配置文件
//版本:  V0.2
//更改记录:
//************************************************************************************************
#ifndef __S_TOUCHKEYCFG_H__
#define __S_TOUCHKEYCFG_H__
#define		    SOCAPI_SET_TOUCHKEY_TOTAL					  3
#define			SOCAPI_SET_TOUCHKEY_CHANNEL					  0x0000000E
#define			SOCAPI_SET_TOUCHKEY_CHANNEL2			      0x00000000
unsigned int  code TKCFG[17] = {0,0,0,5,10,3000,200,100,2,0,0,4,0,1,65535,65535,41}; 
unsigned char code TKChannelCfg[3][8]={
0x05,0x6c,0x04,0x08,0x0f,0x05,0x02,0xdf,
0x05,0x6c,0x04,0x08,0x15,0x05,0x03,0x73,
0x05,0x6c,0x04,0x08,0x20,0x05,0x02,0x98,
};
#endif
