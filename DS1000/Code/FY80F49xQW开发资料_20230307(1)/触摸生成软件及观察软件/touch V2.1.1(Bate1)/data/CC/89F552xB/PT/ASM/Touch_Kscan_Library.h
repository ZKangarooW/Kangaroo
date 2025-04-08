;**********************************************************
;**********************************************************
;文 件 名:Touch_Kscan_Library.H
;触摸定义文件，包括按键消抖次数设置、每个按键灵敏度设置、每个按键内部并联电容设置、按键通道设置
;将 TK_FLAG,B_KERR=1 可以重置全部按键
;**********************************************************
;**********************************************************
#INCLUDE	"Touch_Kscan_Const.h"

;#define		C_KWATER		1		;防水/组合键模式选择,不定义为组合键模式
#define		C_KCOUNT		4		;1~16按键个数

#define		C_VALID_KEY		2		;1~16
#define		C_VALID_TIME	(1000/4)*60 ;0~65535
;----------------------------------------------------------
C_KEYC			DEF			2		;2~16按键消抖次数
;----------------------------------------------------------
;----------------------------------------------------------
;#define		C_HSENSITIVE		1		;高灵敏触摸使能,不定义为普通灵敏度
;----------------------------------------------------------
;内部比较器参考电压设定,在下列值中选取
;C_KVREF_04	=>	0.4VDD
;C_KVREF_05	=>	0.5VDD
;C_KVREF_06	=>	0.6VDD
;C_KVREF_07	=>	0.7VDD
C_KVREF			DEF		C_KVREF_05

;----------------------------------------------------------
;触摸按键时钟设定,在下列值中选取
;注意：	1、5V供电时，若INTRC_SEL主频选择16M，建议触摸转换时钟选择8分频，不能选择2分频
;		2、5V供电时，若INTRC_SEL主频选择8M，建议触摸转换时钟选择4分频/8分频
;		3、3V及以下供电时，触摸转换时钟需选择8分频
;C_KCLK_SYS2	=>	系统时钟的2分频
;C_KCLK_SYS4	=>	系统时钟的4分频
;C_KCLK_SYS8	=>	系统时钟的8分频
C_KCLK			DEF		C_KCLK_SYS8

;----------------------------------------------------------
;下降有效幅度选择,调整长短线后再用这个修正灵敏度差异
;低灵敏度时设定值不可低于6
;高灵敏度时设定值不可低于20

C_KEY1_LMD		DEF		.20		;KEY1灵敏度
C_KEY2_LMD		DEF		.20		;KEY2灵敏度
C_KEY3_LMD		DEF		.20		;KEY3灵敏度
C_KEY4_LMD		DEF		.20		;KEY4灵敏度
C_KEY5_LMD		DEF		.20		;KEY5灵敏度
C_KEY6_LMD		DEF		.20		;KEY6灵敏度
C_KEY7_LMD		DEF		.20		;KEY7灵敏度
C_KEY8_LMD		DEF		.20		;KEY8灵敏度
C_KEY9_LMD		DEF		.20		;KEY9灵敏度
C_KEY10_LMD		DEF		.20		;KEY10灵敏度
C_KEY11_LMD		DEF		.20		;KEY11灵敏度
C_KEY12_LMD		DEF		.20		;KEY12灵敏度
C_KEY13_LMD		DEF		.20		;KEY13灵敏度
C_KEY14_LMD		DEF		.20		;KEY14灵敏度
C_KEY15_LMD		DEF		.20		;KEY15灵敏度
C_KEY16_LMD		DEF		.20		;KEY16灵敏度
;----------------------------------------------------------
;触摸通道口电容
C_KEY1_ADJ		DEF		C_KCAP_0		;KEY1口线电容
C_KEY2_ADJ		DEF		C_KCAP_0		;KEY2口线电容
C_KEY3_ADJ		DEF		C_KCAP_0		;KEY3口线电容
C_KEY4_ADJ		DEF		C_KCAP_0		;KEY4口线电容
C_KEY5_ADJ		DEF		C_KCAP_0		;KEY5口线电容
C_KEY6_ADJ		DEF		C_KCAP_0		;KEY6口线电容
C_KEY7_ADJ		DEF		C_KCAP_0		;KEY7口线电容
C_KEY8_ADJ		DEF		C_KCAP_0		;KEY8口线电容
C_KEY9_ADJ		DEF		C_KCAP_0		;KEY9口线电容
C_KEY10_ADJ		DEF		C_KCAP_0		;KEY10口线电容
C_KEY11_ADJ		DEF		C_KCAP_0		;KEY11口线电容
C_KEY12_ADJ		DEF		C_KCAP_0		;KEY12口线电容
C_KEY13_ADJ		DEF		C_KCAP_0		;KEY13口线电容
C_KEY14_ADJ		DEF		C_KCAP_0		;KEY14口线电容
C_KEY15_ADJ		DEF		C_KCAP_0		;KEY15口线电容
C_KEY16_ADJ		DEF		C_KCAP_0		;KEY16口线电容
;----------------------------------------------------------
;触摸检测通道设置
;不用的按键与未设置的按键默认设置为KCHS0
C_KEY1_CH		DEF		C_KCHS0		;KEY1通道
C_KEY2_CH		DEF		C_KCHS0		;KEY2通道
C_KEY3_CH		DEF		C_KCHS0		;KEY3通道
C_KEY4_CH		DEF		C_KCHS0		;KEY4通道
C_KEY5_CH		DEF		C_KCHS0		;KEY5通道
C_KEY6_CH		DEF		C_KCHS0		;KEY6通道
C_KEY7_CH		DEF		C_KCHS0		;KEY7通道
C_KEY8_CH		DEF		C_KCHS0		;KEY8通道
C_KEY9_CH		DEF		C_KCHS0		;KEY9通道
C_KEY10_CH		DEF		C_KCHS0		;KEY10通道
C_KEY11_CH		DEF		C_KCHS0		;KEY11通道
C_KEY12_CH		DEF		C_KCHS0		;KEY12通道
C_KEY13_CH		DEF		C_KCHS0		;KEY13通道
C_KEY14_CH		DEF		C_KCHS0		;KEY14通道
C_KEY15_CH		DEF		C_KCHS0		;KEY15通道
C_KEY16_CH		DEF		C_KCHS0		;KEY16通道
;----------------------------------------------------------
