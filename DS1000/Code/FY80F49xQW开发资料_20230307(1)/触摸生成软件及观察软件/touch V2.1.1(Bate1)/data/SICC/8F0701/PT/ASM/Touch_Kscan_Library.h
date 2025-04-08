;**********************************************************
;触摸主函数和触摸中断函数有操作FSR以及TABLE_SPL、TABLE_SPH、TABLE_DATAH，如果其它程序有用到，需要在中断里进行保存备份
;触摸函数用到触摸中断，外部不需要操作触摸中断使能位，注意需要清PIR2第6位，注意中断优先级开启
;**********************************************************
;文 件 名:Touch_Kscan_Const.H
;触摸定义文件，包括按键消抖次数设置、每个按键灵敏度设置、按键通道设置
;**********************************************************
;**********************************************************
#INCLUDE	"Touch_Kscan_Const.h"

;调试模式使能
;1:使能
;0:不使能
#define		CMS_DEBUG_MODE	0


;将 B_KERR=1 可以重置全部按键(SETB		B_KERR)

#define		C_KCOUNT		4		;按键个数1~16,最多支持16个按键

#define		C_KEYC			3		;2~6 按键按下消抖次数

;噪声阈值
#define		VOL_VALUE		50		;无干扰下的最大触摸波动值*2,范围25~127

;迟滞值
#define		SLU_VALUE		10		;手指按下和放开切换的消抖值,此值需小于等于VOL_VALUE/2,范围1~63

;触摸基准值更新消抖次数
#define		CM_BASE			6		;消抖时间约为(主程序调用时间4ms + 按键个数*1.5) * CM_BASE * CM_TIME,范围4~127

;触摸基准值更新间隔时间
#define		CM_TIME			3		;1~127

#define		C_VALID_KEY		2		;允许最大有效按键数,范围1~16

#define		C_VALID_TIME	(1000/4)*20	;允许最长响应时间,范围0~65535

;----------------------------------------------------------
;----------------------------------------------------------
;触摸检测通道设置C_KCHS0~C_KCHS25
C_KEY1_CH		DEF		C_KCHS20	;KEY1通道
C_KEY2_CH		DEF		C_KCHS21	;KEY2通道
C_KEY3_CH		DEF		C_KCHS22	;KEY3通道
C_KEY4_CH		DEF		C_KCHS19	;KEY4通道
C_KEY5_CH		DEF		C_KCHS4		;KEY5通道
C_KEY6_CH		DEF		C_KCHS5		;KEY6通道
C_KEY7_CH		DEF		C_KCHS6		;KEY7通道
C_KEY8_CH		DEF		C_KCHS7		;KEY8通道
C_KEY9_CH		DEF		C_KCHS8		;KEY9通道
C_KEY10_CH		DEF		C_KCHS9		;KEY10通道
C_KEY11_CH		DEF		C_KCHS10	;KEY11通道
C_KEY12_CH		DEF		C_KCHS11	;KEY12通道
C_KEY13_CH		DEF		C_KCHS12	;KEY13通道
C_KEY14_CH		DEF		C_KCHS13	;KEY14通道
C_KEY15_CH		DEF		C_KCHS14	;KEY15通道
C_KEY16_CH		DEF		C_KCHS16	;KEY16通道
;----------------------------------------------------------
;灵敏度阈值1,设定值不低于VOL_VALUE,不能大于1023
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
;噪声滤波系数
;越小，则高频噪声滤除越好、响应越慢,摸键总数超过8时,建议大于4
;为0则无滤波功能
#define 	KEY_VOLLV		4;0~8

;灵敏度档位
;越大越灵敏,为2时注意噪声值以及触摸基准值
#define 	LMDVALUE		1;1~2

;CS使能，默认即可
;0：不使能
;1:提高动态性能，但静态性能可能会降低
#define 	CS_FUN			0

;检测电压
#define		KEY_LDOSEL		3;0~7

;检测频率
;0:检测频率高，外部串电阻建议不超过1k
;1:检测频率低，外部串电阻建议不超过2k
#define 	KEY_FRESEL		1;0~1

;消顶噪声滤波系数，0为不使能滤除噪声
#define 	NOI_VALUE		2;0~2
;----------------------------------------------------------
;----------------------------------------------------------
;----------------------------------------------------------