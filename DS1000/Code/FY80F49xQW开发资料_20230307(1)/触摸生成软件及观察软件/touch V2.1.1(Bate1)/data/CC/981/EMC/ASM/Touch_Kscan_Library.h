;**********************************************************
;**********************************************************
;文 件 名:GlobalKeySet.H
;触摸定义文件，包括按键消抖次数设置、每个按键灵敏度设置、每个按键内部并联电容设置、按键通道设置
;**********************************************************
;**********************************************************
#INCLUDE	"Touch_Kscan_Const.h"

#define		C_KCOUNT		1			;按键个数

#define		C_VALID_KEY		3			;允许最大有效按键数
#define		C_VALID_TIME	(1000/4)*60	;允许最长响应时间


;噪声阈值
#define		VOL_VALUE		5			;无干扰下的最大触摸波动值*2,取值范围5~128

;迟滞值
#define		SLU_VALUE		1			;手指按下和放开切换的消抖值

;触摸基准值更新消抖次数
#define		CM_BASE			6		;消抖时间约为调用周期4ms（主程序时间例如4ms）*按键个数*CM_BASE
;----------------------------------------------------------
C_KEYC			DEF		.2		;按键消抖次数
;----------------------------------------------------------
C_OFF_KEYC		DEF		.2		;按键放开消抖次数
;----------------------------------------------------------
;按键灵敏度设置常量
C_KEY1_LMD		DEF		.10		;KEY1灵敏度
C_KEY2_LMD		DEF		.10		;KEY2灵敏度
C_KEY3_LMD		DEF		.10		;KEY3灵敏度
C_KEY4_LMD		DEF		.10		;KEY4灵敏度
C_KEY5_LMD		DEF		.10		;KEY5灵敏度
C_KEY6_LMD		DEF		.10		;KEY6灵敏度
C_KEY7_LMD		DEF		.10		;KEY7灵敏度
C_KEY8_LMD		DEF		.10		;KEY8灵敏度
C_KEY9_LMD		DEF		.10		;KEY9灵敏度
C_KEY10_LMD		DEF		.10		;KEY10灵敏度
C_KEY11_LMD		DEF		.10		;KEY11灵敏度
C_KEY12_LMD		DEF		.10		;KEY12灵敏度
C_KEY13_LMD		DEF		.10		;KEY10灵敏度
C_KEY14_LMD		DEF		.10		;KEY11灵敏度
C_KEY15_LMD		DEF		.10		;KEY12灵敏度
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
;----------------------------------------------------------
