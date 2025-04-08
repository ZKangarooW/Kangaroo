;**********************************************************
;**********************************************************
;文 件 名:
;触摸定义文件，包括按键消抖次数设置、每个按键灵敏度设置、每个按键内部并联电容设置、按键通道设置

;触摸函数已用TMR0计数器，OPTION_REG分配给TMR0
;汇编EMC库没有做长短线校准算法，外挂基准电容建议用精度±5%的涤纶电容
;汇编EMC库默认开启高灵敏
;**********************************************************
;**********************************************************
#INCLUDE	"Touch_Kscan_Const.h"

;将 TK_FLAG,B_KERR=1 可以重置全部按键

#define		OSC_CH			0 ;0 = 16M(主频默认); 1 = 8M

#define		C_KCOUNT		4 ;1~12按键个数

#define		C_VALID_KEY		2 ;1~12允许最大有效按键数
#define		C_VALID_TIME	(1000/4)*60	;0~65535,允许最长响应时间,为0时将忽略


;噪声阈值
#define		VOL_VALUE		15 ;15~127,无干扰下的最大触摸波动值*2

;迟滞值
#define		SLU_VALUE		5 ;手指按下和放开切换的消抖值,此值需小于等于VOL_VALUE/2,范围1~127

;触摸基准值更新消抖次数
#define		CM_BASE			10 ;5~127,消抖时间约为调用周期4ms（主程序时间例如4ms）*按键个数*CM_BASE

;硬件跳频设定
#define		C_TP_EN			1 ;0：关闭; 1：开启
;----------------------------------------------------------
C_KEYC			DEF			.2 ;2~8按键按下消抖次数
;----------------------------------------------------------
C_OFF_KEYC		DEF			.2 ;2~8按键放开消抖次数
;----------------------------------------------------------
;内部比较器参考电压设定,在下列值中选取
;C_KVREF_04	=>	0.4VDD
;C_KVREF_05	=>	0.5VDD
;C_KVREF_06	=>	0.6VDD
;C_KVREF_07	=>	0.7VDD
C_KVREF			DEF		C_KVREF_05
;----------------------------------------------------------
;按键灵敏度设置常量,响应计算值为C_KEY1_LMD + VOL_VALUE/2
;10~127
C_KEY1_LMD		DEF		.30		;KEY1灵敏度
C_KEY2_LMD		DEF		.30		;KEY2灵敏度
C_KEY3_LMD		DEF		.30		;KEY3灵敏度
C_KEY4_LMD		DEF		.30		;KEY4灵敏度
C_KEY5_LMD		DEF		.30		;KEY5灵敏度
C_KEY6_LMD		DEF		.30		;KEY6灵敏度
C_KEY7_LMD		DEF		.30		;KEY7灵敏度
C_KEY8_LMD		DEF		.30		;KEY8灵敏度
C_KEY9_LMD		DEF		.30		;KEY9灵敏度
C_KEY10_LMD		DEF		.30		;KEY10灵敏度
C_KEY11_LMD		DEF		.30		;KEY11灵敏度
C_KEY12_LMD		DEF		.30		;KEY12灵敏度
C_KEY13_LMD		DEF		.30		;KEY10灵敏度
C_KEY14_LMD		DEF		.30		;KEY11灵敏度
C_KEY15_LMD		DEF		.30		;KEY12灵敏度
;----------------------------------------------------------
;触摸通道口电容
;C_KCAP_0 ~ C_KCAP_7
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
;----------------------------------------------------------
;触摸检测通道设置
;不用的按键与未设置的按键默认设置为KCHS0
;KCHS0~KCHS12
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
;----------------------------------------------------------
