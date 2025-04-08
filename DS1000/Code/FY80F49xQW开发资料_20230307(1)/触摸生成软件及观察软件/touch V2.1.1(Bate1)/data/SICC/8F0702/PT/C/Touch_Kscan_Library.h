/*

*/
#ifndef	_CHECKTOUCHKEY_H_
#define	_CHECKTOUCHKEY_H_

#include "TouchKeyConst.h"
#pragma warning disable 752,759
//接口函数声明，按键扫描主过程函数,建议在2.5ms~5ms内调用,调用间隔不能小于1ms
extern void __CMS_CheckTouchKey(void);

//此函数用到触摸中断，外部不需要操作触摸中断使能位，注意需要清PIR2第6位，注意中断优先级开启
extern void __CMS_TouchKeyValue(void);

extern volatile bit gf_kerr;				//复位按键标志
//每个按键对应于寄存器的1个位,由高至低一一对应
//g_KeyFlag[0]对应于Key8,...,Key2,Key1
//g_KeyFlag[1]对应于Key16,...,Key10,Key9
//按键有效时相应位为1,无效时为0
extern volatile unsigned char g_KeyFlag[2];
//-------------------------------------------------------
//使用时根据实际硬件连接修改下面这三个数组的内容
//注意数组的大小不能小于检测的按键总数

//检测通道设定,为C_KCHS0至C_KCHS25其中之一
const unsigned char gc_Table_KeyChannel[] = {
	C_KCHS20,
	C_KCHS21,
	C_KCHS22,
	C_KCHS19,
};

//灵敏度阈值,设定值不低于VOL_VALUE值,不能大于1023
//触摸响应的条件，为当前值与基准值的差值大于gc_Table_KeyDown值
const unsigned int gc_Table_KeyDown[] = 
{
	200,
	200,
	200,
	200,
};


//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
/*
常规触摸效果参数设置
*/
//待检测按键总数,常量
#define 	C_KEY_TOTAL		4//1~16

//按键按下消抖次数
#define		C_KEY_SHAKE		3//2~6

//按键放开消抖次数
#define		C_KEY_OFFSHAKE	3//2~6

//噪声阈值
//至少大于最大触摸波动值*2
#define		VOL_VALUE		50//25~127

//迟滞值
//手指按下和放开切换的消抖值,此值需小于等于VOL_VALUE/2
#define		SLU_VALUE		10//1~63

//触摸基准值更新消抖次数
//消抖时间约为(主程序调用时间4ms + 按键个数*1.5) * CM_BASE * CM_TIME
#define		CM_BASE			6//4~127

//触摸基准值更新间隔时间
#define		CM_TIME			3//1~127

//同时最大允许有效按键数,超过该值将认为是干扰
#define		C_VALID_KEY		2//1~16

//按键最大允许生效时间,以扫描时间（例如4ms）为基准换算,为0时将忽略,(1000/4)*20=20S
#define		C_VALID_TIME	(1000/4)*20//0~65535



/*-------------------------------------------------------
以下数据通常情况下不用修改
-------------------------------------------------------*/
//噪声滤波系数
//越小，则高频噪声滤除越好、响应越慢,摸键总数超过8时,建议大于4
//为0则无滤波功能
#define 	KEY_VOLLV		4//0~8

//灵敏度档位
//越大越灵敏,为2时注意噪声值以及触摸基准值
#define 	LMDVALUE		1//1~2

//CS使能，默认即可
//0：不使能
//1:提高动态性能，但静态性能可能会降低
#define 	CS_FUN			0

//检测电压
#define 	KEY_LDOSEL		3//0~7

//检测频率
//0:检测频率高，外部串电阻建议不超过1k
//1:检测频率低，外部串电阻建议不超过2k
#define 	KEY_FRESEL		1//0~1

//消顶噪声滤波系数，0为不使能滤除噪声
#define 	NOI_VALUE		2//0~2
/***********************************************************
下面的内容请勿修改
***********************************************************/
const unsigned char gc_KeyTNumber = C_KEY_TOTAL;
const unsigned char gc_KeyShakeC = C_KEY_SHAKE;
const unsigned char gc_KeyOffC = C_KEY_OFFSHAKE;
const unsigned char gc_VolValue = VOL_VALUE;
const unsigned char gc_SluValue = SLU_VALUE;
const unsigned char gc_CmBase = CM_BASE;
const unsigned char gc_CmTime = CM_TIME;
const unsigned char gc_KeyValidC = C_VALID_KEY;
const unsigned int  gc_KeyValidT = C_VALID_TIME;
//-------------------------------------------------------
const unsigned char gc_Key_VolLV = KEY_VOLLV;
const unsigned char gc_LMDValue = LMDVALUE;
const unsigned char gc_CSFun = CS_FUN;
const unsigned char gc_KeyLDOSel = KEY_LDOSEL;
const unsigned char gc_KeyFreSel = KEY_FRESEL;
const unsigned char gc_NoiValue = NOI_VALUE;

unsigned int g_DispKeyDown[C_KEY_TOTAL];
unsigned int g_NoiseDat[C_KEY_TOTAL];
unsigned int g_FactorRawDat[C_KEY_TOTAL];
//--------------------------------------------------
#endif





