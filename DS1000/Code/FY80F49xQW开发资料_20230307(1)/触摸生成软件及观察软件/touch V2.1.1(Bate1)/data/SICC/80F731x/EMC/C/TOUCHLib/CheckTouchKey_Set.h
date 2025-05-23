#ifndef	_CHECKTOUCHKEY_SET_H_
#define	_CHECKTOUCHKEY_SET_H_
/****************************************************************************/
/** \file CheckTouchKey_Set.h
**	History:
*****************************************************************************/
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "CheckTouchKeyConst_80F73xx.h"
/****************************************************************************
*****************************************************************************/
//debug相关，不用debug需要注释掉，Lib文件换成CheckTouchKey_80F73xx,省空间
//#define CMS_TOUCH_DEBUG


//使用时根据实际硬件连接修改下面这两个数组的内容
//触摸检测通道设置,其值为C_KCHS0至C_KCHS19,C_KCHS39至C_KCHS44
//只选前C_KEY_TOTAL个触摸通道
#define C_KEY1_CH		C_KCHS16
#define C_KEY2_CH		C_KCHS15
#define C_KEY3_CH		C_KCHS18
#define C_KEY4_CH		C_KCHS17
#define C_KEY5_CH		C_KCHS4
#define C_KEY6_CH		C_KCHS5
#define C_KEY7_CH		C_KCHS6
#define C_KEY8_CH		C_KCHS7
#define C_KEY9_CH		C_KCHS8
#define C_KEY10_CH	C_KCHS9
#define C_KEY11_CH	C_KCHS10
#define C_KEY12_CH	C_KCHS11
#define C_KEY13_CH	C_KCHS12
#define C_KEY14_CH	C_KCHS13
#define C_KEY15_CH	C_KCHS14
#define C_KEY16_CH	C_KCHS15
#define C_KEY17_CH	C_KCHS16
#define C_KEY18_CH	C_KCHS17
#define C_KEY19_CH	C_KCHS18
#define C_KEY20_CH	C_KCHS19
#define C_KEY21_CH	C_KCHS39
#define C_KEY22_CH	C_KCHS40
#define C_KEY23_CH	C_KCHS41
#define C_KEY24_CH	C_KCHS42
#define C_KEY25_CH	C_KCHS43
#define C_KEY26_CH	C_KCHS44

//按键灵敏度设置常量20~2047
#define	C_KEY1_THRESHOLD	100
#define	C_KEY2_THRESHOLD	100
#define	C_KEY3_THRESHOLD	100
#define	C_KEY4_THRESHOLD	100
#define	C_KEY5_THRESHOLD	100
#define	C_KEY6_THRESHOLD	100
#define	C_KEY7_THRESHOLD	100
#define	C_KEY8_THRESHOLD	100
#define	C_KEY9_THRESHOLD	100
#define	C_KEY10_THRESHOLD	100
#define	C_KEY11_THRESHOLD	100
#define	C_KEY12_THRESHOLD	100
#define	C_KEY13_THRESHOLD	100
#define	C_KEY14_THRESHOLD	100
#define	C_KEY15_THRESHOLD	100
#define	C_KEY16_THRESHOLD	100
#define	C_KEY17_THRESHOLD	100
#define	C_KEY18_THRESHOLD	100
#define	C_KEY19_THRESHOLD	100
#define	C_KEY20_THRESHOLD	100
#define	C_KEY21_THRESHOLD	100
#define	C_KEY22_THRESHOLD	100
#define	C_KEY23_THRESHOLD	100
#define	C_KEY24_THRESHOLD	100
#define	C_KEY25_THRESHOLD	100
#define	C_KEY26_THRESHOLD	100

//内部并联电容选择，用来调整长短线，以最长的线为0，适当调大短线的值，范围:C_KCAP0至C_KCAP7
#define	C_KEY1_CAP	C_KCAP0
#define	C_KEY2_CAP	C_KCAP0
#define	C_KEY3_CAP	C_KCAP0
#define	C_KEY4_CAP	C_KCAP0
#define	C_KEY5_CAP	C_KCAP0
#define	C_KEY6_CAP	C_KCAP0
#define	C_KEY7_CAP	C_KCAP0
#define	C_KEY8_CAP	C_KCAP0
#define	C_KEY9_CAP	C_KCAP0
#define	C_KEY10_CAP	C_KCAP0
#define	C_KEY11_CAP	C_KCAP0
#define	C_KEY12_CAP	C_KCAP0
#define	C_KEY13_CAP	C_KCAP0
#define	C_KEY14_CAP	C_KCAP0
#define	C_KEY15_CAP	C_KCAP0
#define	C_KEY16_CAP	C_KCAP0
#define	C_KEY17_CAP	C_KCAP0
#define	C_KEY18_CAP	C_KCAP0
#define	C_KEY19_CAP	C_KCAP0
#define	C_KEY20_CAP	C_KCAP0
#define	C_KEY21_CAP	C_KCAP0
#define	C_KEY22_CAP	C_KCAP0
#define	C_KEY23_CAP	C_KCAP0
#define	C_KEY24_CAP	C_KCAP0
#define	C_KEY25_CAP	C_KCAP0
#define	C_KEY26_CAP	C_KCAP0

/*
常规触摸效果参数设置
*/
//待检测按键总数,常量
#define 	C_KEY_TOTAL			4//范围1~26

//按键按下消抖次数
#define		C_KEY_SHAKE			2//2~7

//噪声阈值
#define		VOL_VALUE				30			//无干扰下的最大触摸波动值*2,范围30~127

//迟滞值
#define		SLU_VALUE				15			//手指按下和放开切换的消抖值,此值需小于等于VOL_VALUE/2,范围1~127

//触摸基准值更新消抖次数
#define		CM_BASE					10			//消抖时间约为(主程序调用时间2.5ms*2 + 按键个数*1.5) * CM_BASE,范围6~127

//同时最大允许有效按键数,超过该值将认为是干扰
#define		C_VALID_KEY			2//范围1~25

//按键最大允许生效时间,以扫描时间（例如5ms）为基准换算,为0时将忽略,0~65535
#define		C_VALID_TIME		(1000/5)*20//20S

//触摸按键中断异常限制时间,以扫描时间（例如5ms）为基准换算,为0时将忽略,20~255
#define		C_UN_TIME				200/5		//200ms(以触摸扫描周期5ms来计算)

//灵敏度档位
#define 	LMDVALUE				1//1~2,越大越灵敏,为2时注意噪声值设置是否合理

//防水模式开关
//0:不使能，组合键模式
//1:使能，防水模式
#define		WATER_MODE			0



/*-------------------------------------------------------
以下数据通常情况下不用修改
-------------------------------------------------------*/
//异常判断使能，当TK值异常重新进行自适应
#define		UNNOL_CHECK		1//0~1
//异常判断自恢复次数，超过则不再进行自恢复，设置成255则为无限次
#define		UNNOL_TIMES		100//1~100

//检测电压
#define 	KEY_LDOSEL		3//0~7

//内部串电阻
#define		KEY_EN1KRES		0//0~1

//频率键值
#define 	CMS_KEY_DISP	0//0~1

//Debug相关
#ifdef	CMS_TOUCH_DEBUG
extern unsigned int xdata g_FactorRawDat[];
extern unsigned int xdata g_Disp_KeyDown[];
extern unsigned int xdata g_Disp_KeyDown_Pro[];
extern unsigned int xdata g_NoiseDat[];
#endif
/*-------------------------------------------------------
-------------------------------------------------------*/
extern unsigned char code Table_KeyChannel[];
extern unsigned int code Table_KeyDown[];
extern unsigned char code Table_KeyCap[];
//若startup.a51里没有对xdata进行上电清0的配置，则此部分xdata需要上电程序清0
extern unsigned int xdata g_CMS_RAM0[];
extern unsigned int xdata g_CMS_RAM1[];
extern unsigned int xdata g_CMS_RAM2[];
extern unsigned int xdata g_CMS_RAM3[];
extern unsigned int xdata g_CMS_RAM4[];
extern unsigned int xdata g_CMS_RAM5[];
extern unsigned int xdata g_CMS_RAM6[];
extern unsigned char xdata g_CMS_RAM7[];
extern unsigned char xdata g_CMS_RAM8[];
extern unsigned char xdata g_CMS_RAM9[];
extern unsigned char xdata g_CMS_RAM10[];
extern unsigned char xdata g_CMS_RAM11[];
extern unsigned char xdata g_CMS_RAM12[];
extern unsigned char xdata g_CMS_RAM13[];
extern unsigned char xdata g_CMS_RAM14[];
extern unsigned char xdata g_CMS_RAM15[];

extern unsigned char code g__KeyTotalNumber;
extern unsigned char code g__KeyShakeCounter;
extern unsigned char code g__VolValue;
extern unsigned char code g__SluValue;
extern unsigned char code g__CmBase;
extern unsigned char code g__KeyValidNumber;
extern unsigned long int  code g__KeyValidTime;
extern unsigned char code g__KeyUNTime;
extern unsigned char code g__UnNol_Check;
extern unsigned char code g__UnNol_Times;
extern unsigned char code g__LMDValue;
extern unsigned char code g__Key_LDOSel;
extern unsigned char code g__Key_En1kres;
extern unsigned char code g__WaterMode;
extern unsigned char code g__CMS_Key_Disp;





#endif//_CHECKTOUCHKEY_SET_H_





