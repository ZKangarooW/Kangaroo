;库程序用户接口:
;按键扫描结果存放于寄存器KEYF及KEYF1中
;每个按键对应于寄存器的1个位,由高至低一一对应
;KEYF对应于Key8,...,Key2,Key1
;KEYF1对应于Key16,...,Key10,Key9
;按键有效时相应位为1,无效时为0

;将TK_FLAG,B_KERR=1 可以重置全部按键

;按键对应关系表:
;		BIT7	BIT6	BIT5	BIT4	BIT3	BIT2	BIT1	BIT0
;KEYF	KEY8	KEY7	KEY6	KEY5	KEY4	KEY3	KEY2	KEY1
;KEYF1	----	KEY15	KEY14	KEY13	KEY12	KEY11	KEY10	KEY9
;********************************************************************
;********************************************************************
#ifndef	_TOUCH_KSCAN_LIBRARY_H_
#define	_TOUCH_KSCAN_LIBRARY_H_

;--------------------------------------------------------------------
#define		C_KEY_CHANNEL	0x00	;使能的按键通道
#define		C_KTMR			230		;按键周期，值越小检测时间越长，按键越灵敏
;--------------------------------------------------------------------
;防水模式选择,不定义则为组合键模式
#define		C_KWATER
#define		C_KCOUNT	1			;按键个数
#define		C_KEYC		2			;按键消抖次数
#define		C_VALID_KEY	1			;同时最大允许有效按键数,超过该值将认为是干扰
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
;各触摸检测通道对应的按键序号
;未使用的通道设置为0x80
C_KEY1_CH		DEF		0x80		;触摸通道1不检测按键
C_KEY2_CH		DEF		0x80		;触摸通道2不检测按键
C_KEY3_CH		DEF		0x80		;触摸通道3不检测按键
C_KEY4_CH		DEF		0x80		;触摸通道4不检测按键
C_KEY5_CH		DEF		0x80		;触摸通道5不检测按键
C_KEY6_CH		DEF		0x80		;触摸通道6不检测按键
C_KEY7_CH		DEF		0x80		;触摸通道7不检测按键
C_KEY8_CH		DEF		0x80		;触摸通道8不检测按键
C_KEY9_CH		DEF		0x80		;触摸通道9不检测按键
C_KEY10_CH		DEF		0x80		;触摸通道10不检测按键
C_KEY11_CH		DEF		0x80		;触摸通道11不检测按键
C_KEY12_CH		DEF		0x80		;触摸通道12不检测按键
;--------------------------------------------------------------------
#define		C_VALID_TIME	60*(1000/4)			;按键最大允许生效时间(单位：ms),以4ms调用基准换算,为0时将忽略
;--------------------------------------------------------------------
#endif
