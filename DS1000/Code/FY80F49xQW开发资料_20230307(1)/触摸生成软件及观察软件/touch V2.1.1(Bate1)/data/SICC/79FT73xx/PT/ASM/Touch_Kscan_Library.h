;**********************************************************
;触摸主函数和触摸中断函数有操作FSR以及TABLE_SPL、TABLE_SPH、TABLE_DATAH，如果其它程序有用到，需要在中断里进行保存备份
;**********************************************************
;文 件 名:Touch_Kscan_Const.H
;触摸定义文件，包括按键消抖次数设置、每个按键灵敏度设置、按键通道设置
;**********************************************************
;**********************************************************
#INCLUDE	"Touch_Kscan_Const.h"

;调试模式使能
#define		CMS_DEBUG_MODE	0

;将 B_KERR=1 可以重置全部按键

#define		C_KCOUNT		4		;按键个数,最多支持16个按键

#define		C_KEYC			2		;2~8 按键按下消抖次数

;噪声阈值
#define		VOL_VALUE		25		;无干扰下的最大触摸波动值*2,范围20~127

;迟滞值
#define		SLU_VALUE		12		;手指按下和放开切换的消抖值,此值需小于等于VOL_VALUE/2,范围1~127

;触摸基准值更新消抖次数
#define		CM_BASE			10		;消抖时间约为(主程序调用时间4ms + 按键个数*1.5) * CM_BASE,范围6~127

#define		C_VALID_KEY		2		;允许最大有效按键数,范围1~16

#define		C_VALID_TIME	(1000/4)*20	;允许最长响应时间,范围0~65535

;灵敏度档位
#define 	LMDVALUE		1;0~1,越大约灵敏,为1时注意噪声值以及触摸基准值

;内部串电阻
#define		KEY_EN1KRES		0; 0:不串; 1:串电阻1K
;----------------------------------------------------------
;----------------------------------------------------------
;触摸检测通道设置C_KCHS0~C_KCHS25
;不用的按键与未设置的按键默认设置为KCHS0
C_KEY1_CH		DEF		C_KCHS0	;KEY1通道
C_KEY2_CH		DEF		C_KCHS0	;KEY2通道
C_KEY3_CH		DEF		C_KCHS0	;KEY3通道
C_KEY4_CH		DEF		C_KCHS0	;KEY4通道
C_KEY5_CH		DEF		C_KCHS0	;KEY5通道
C_KEY6_CH		DEF		C_KCHS0	;KEY6通道
C_KEY7_CH		DEF		C_KCHS0	;KEY7通道
C_KEY8_CH		DEF		C_KCHS0	;KEY8通道
C_KEY9_CH		DEF		C_KCHS0	;KEY9通道
C_KEY10_CH		DEF		C_KCHS0	;KEY10通道
C_KEY11_CH		DEF		C_KCHS0	;KEY11通道
C_KEY12_CH		DEF		C_KCHS0	;KEY12通道
C_KEY13_CH		DEF		C_KCHS0	;KEY13通道
C_KEY14_CH		DEF		C_KCHS0	;KEY14通道
C_KEY15_CH		DEF		C_KCHS0	;KEY15通道
C_KEY16_CH		DEF		C_KCHS0	;KEY16通道
;----------------------------------------------------------
;灵敏度阈值1,设定值不可低于20,不能大于1023
C_KEY1_LMD		DEF		.150		;KEY1灵敏度
C_KEY2_LMD		DEF		.150		;KEY2灵敏度
C_KEY3_LMD		DEF		.150		;KEY3灵敏度
C_KEY4_LMD		DEF		.150		;KEY4灵敏度
C_KEY5_LMD		DEF		.150		;KEY5灵敏度
C_KEY6_LMD		DEF		.150		;KEY6灵敏度
C_KEY7_LMD		DEF		.150		;KEY7灵敏度
C_KEY8_LMD		DEF		.150		;KEY8灵敏度
C_KEY9_LMD		DEF		.150		;KEY9灵敏度
C_KEY10_LMD		DEF		.150		;KEY10灵敏度
C_KEY11_LMD		DEF		.150		;KEY11灵敏度
C_KEY12_LMD		DEF		.150		;KEY12灵敏度
C_KEY13_LMD		DEF		.150		;KEY13灵敏度
C_KEY14_LMD		DEF		.150		;KEY14灵敏度
C_KEY15_LMD		DEF		.150		;KEY15灵敏度
C_KEY16_LMD		DEF		.150		;KEY16灵敏度
;----------------------------------------------------------
;----------------------------------------------------------
;以下数据通常情况下不用修改
;----------------------------------------------------------
;----------------------------------------------------------
;异常判断使能，当TK值异常重新进行自适应
#define		UNNOL_CHECK		1;0~1

;异常判断自恢复次数，超过则不再进行自恢复，为255则恢复次数为无限次
#define		UNNOL_TIMES		100;1~250

;检测电压
#define		KEY_LDOSEL		4;0~7
;----------------------------------------------------------
;----------------------------------------------------------
;----------------------------------------------------------