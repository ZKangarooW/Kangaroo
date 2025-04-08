;********************************************************************
;*********************触摸按键检测库程序配置文件*********************
;********************************************************************
;此文件由CTouch V1.06创建
;文 件 名:Touch_Kscan_Library.H
;创建时间:2017年10月12日 13:27:58
;--------------------------------------------------------------------
;库程序用户接口:
;按键扫描结果存放于寄存器KEYF及KEYF1中
;每个按键对应于寄存器的1个位,由高至低一一对应
;KEYF对应于Key8,...,Key2,Key1
;KEYF1对应于Key12,...,Key10,Key9
;按键有效时相应位为1,无效时为0

;B_KEY_EN=1		表示有按键按下
;B_KEY_LONG=1	表示有长按键
;B_KEY_UP=0		表示按键放开

;按键对应关系表:
;		BIT7	BIT6	BIT5	BIT4	BIT3	BIT2	BIT1	BIT0
;KEYF	KEY8	KEY7	KEY6	KEY5	KEY4	KEY3	KEY2	KEY1
;KEYF1	----	----	----	----	KEY12	KEY11	KEY10	KEY9
;********************************************************************
;********************************************************************
#ifndef	_TOUCH_KSCAN_LIBRARY_H_
#define	_TOUCH_KSCAN_LIBRARY_H_

#INCLUDE	"Touch_Kscan_Const.h"

;--------------------------------------------------------------------
#define		C_KWATER	1			;按键检测模式(0为组合键模式,1为防水模式)
#define		C_KCOUNT	12			;按键个数;1~12
#define		C_KEYC		2			;按键消抖次数
#define		C_VALID_KEY	2			;同时最大允许有效按键数,超过该值将认为是干扰
;--------------------------------------------------------------------
;按键灵敏度设置常量
C_KEY1_LMD		DEF		10			;KEY1灵敏度
C_KEY2_LMD		DEF		10			;KEY2灵敏度
C_KEY3_LMD		DEF		10			;KEY3灵敏度
C_KEY4_LMD		DEF		10			;KEY4灵敏度
C_KEY5_LMD		DEF		10			;KEY5灵敏度
C_KEY6_LMD		DEF		10			;KEY6灵敏度
C_KEY7_LMD		DEF		10			;KEY7灵敏度
C_KEY8_LMD		DEF		10			;KEY8灵敏度
C_KEY9_LMD		DEF		10			;KEY9灵敏度
C_KEY10_LMD		DEF		10			;KEY10灵敏度
C_KEY11_LMD		DEF		10			;KEY11灵敏度
C_KEY12_LMD		DEF		10			;KEY12灵敏度
;--------------------------------------------------------------------
;触摸通道口电容,其值为C_KCAP_0至C_KCAP_7之一
C_KEY1_ADJ		DEF		C_KCAP_0	;KEY1口线电容
C_KEY2_ADJ		DEF		C_KCAP_0	;KEY2口线电容
C_KEY3_ADJ		DEF		C_KCAP_0	;KEY3口线电容
C_KEY4_ADJ		DEF		C_KCAP_0	;KEY4口线电容
C_KEY5_ADJ		DEF		C_KCAP_0	;KEY5口线电容
C_KEY6_ADJ		DEF		C_KCAP_0	;KEY6口线电容
C_KEY7_ADJ		DEF		C_KCAP_0	;KEY7口线电容  
C_KEY8_ADJ		DEF		C_KCAP_0	;KEY8口线电容
C_KEY9_ADJ		DEF		C_KCAP_0	;KEY9口线电容
C_KEY10_ADJ		DEF		C_KCAP_0	;KEY10口线电容
C_KEY11_ADJ		DEF		C_KCAP_0	;KEY11口线电容
C_KEY12_ADJ		DEF		C_KCAP_0	;KEY12口线电容
;--------------------------------------------------------------------
;触摸检测通道设置,其值为C_KCHS0至C_KCHS15之一
;未使用到的按键默认设置为C_KCHS0
C_KEY1_CH		DEF		C_KCHS0		;KEY1扫描通道
C_KEY2_CH		DEF		C_KCHS0		;KEY2扫描通道
C_KEY3_CH		DEF		C_KCHS0		;KEY3扫描通道
C_KEY4_CH		DEF		C_KCHS0		;KEY4扫描通道
C_KEY5_CH		DEF		C_KCHS0		;KEY5扫描通道
C_KEY6_CH		DEF		C_KCHS0		;KEY6扫描通道
C_KEY7_CH		DEF		C_KCHS0		;KEY7扫描通道
C_KEY8_CH		DEF		C_KCHS0		;KEY8扫描通道
C_KEY9_CH		DEF		C_KCHS0		;KEY9扫描通道
C_KEY10_CH		DEF		C_KCHS0		;KEY10扫描通道
C_KEY11_CH		DEF		C_KCHS0		;KEY11扫描通道
C_KEY12_CH		DEF		C_KCHS0		;KEY12扫描通道
;--------------------------------------------------------------------
C_FRIST_TIME	DEF		80			;初次长按确认时间=程序调用周期*8*C_FRIST_TIME (ms)
C_LONG_TIME		DEF		5			;每次长按键响应时间=程序调用周期*8*C_LONG_TIME (ms)
;--------------------------------------------------------------------
#endif
