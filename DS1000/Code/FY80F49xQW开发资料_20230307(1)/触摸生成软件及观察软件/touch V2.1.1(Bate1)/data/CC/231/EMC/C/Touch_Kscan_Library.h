/*
触摸函数已用TMR0计数器，OPTION_REG分配给TMR0
*/
#ifndef	_CHECKTOUCHKEY_H_
#define	_CHECKTOUCHKEY_H_

#include "TouchKeyConst.h"
#pragma warning disable 752,759
//接口函数声明
extern void CheckTouchKey(void);		//按键扫描主过程函数,建议在2.5ms~5ms内调用
extern volatile bit b_kerr;				//复位按键标志
extern volatile bit KeyOnceHave,KeyOnceOver;//休眠唤醒用
//每个按键对应于寄存器的1个位,由高至低一一对应
//KeyFlag[0]对应于Key7,...,Key1,Key0
//KeyFlag[1]对应于Key15,...,Key9,Key8
//按键有效时相应位为1,无效时为0
extern volatile unsigned char KeyFlag[2];

//同时最大允许有效按键数,超过该值将认为是干扰
#define		C_VALID_KEY		2

//按键最大允许生效时间,以扫描时间（例如5ms）为基准换算,为0时将忽略
#define		C_VALID_TIME	(1000/5)*20

//按键按下消抖次数C_KEY_SHAKE
#define		C_KEY_SHAKE		2

//待检测按键总数,常量
#define 	C_KEY_TOTAL		1

//跳频使能
//0：关闭
//1：开启
#define		C_TP_EN			1

//内部比较器参考电压设定,在下列值中选取
//C_KVREF_04	=>	0.4VDD
//C_KVREF_05	=>	0.5VDD
//C_KVREF_06	=>	0.6VDD
//C_KVREF_07	=>	0.7VDD
#define		C_KVREF			C_KVREF_04

//使用时根据实际硬件连接修改下面这三个数组的内容
//注意数组的大小不能小于检测的按键总数

//检测通道设定,为C_KCHS0至C_KCHS15其中之一
const unsigned char Table_KeyChannel[] = {

};

//内部并联电容选择，用来调整长短线，以最长的线为0，适当调大短线的值，范围:C_KCAP0至C_KCAP7
const unsigned char Table_KeyCap[] = {

};

//下降有效幅度选择,调整长短线后再用这个修正灵敏度差异,设定值不可低于6
const unsigned char Table_KeyDown[] = {

};

//噪声阈值
#define		VOL_VALUE		5			//无干扰下的最大触摸波动值*2,取值范围5~128

//迟滞值
#define		SLU_VALUE		1			//手指按下和放开切换的消抖值,此值需小于VOL_VALUE



//触摸基准值更新消抖次数
#define		CM_BASE			6			//消抖时间约为调用周期4ms（主程序时间例如4ms）*按键个数*CM_BASE
/***********************************************************
下面的内容请勿修改
***********************************************************/
//
#define		C_OFF_SHAKE		2

unsigned int  KeySum0[C_KEY_TOTAL];
unsigned int  KeySum1[C_KEY_TOTAL];

//unsigned int  KeyOldValue0[C_KEY_TOTAL];
//unsigned int  KeyOldValue1[C_KEY_TOTAL];
unsigned int  KeyOldValue[C_KEY_TOTAL];
unsigned int  KeyReference[C_KEY_TOTAL];
unsigned char KeyUpShake[C_KEY_TOTAL];
unsigned char KeyBaseCnt[C_KEY_TOTAL];
unsigned char KeyHaveCnt[C_KEY_TOTAL];

const unsigned int  KeyValidTime = C_VALID_TIME;
const unsigned char KeyTotalNumber = C_KEY_TOTAL;
const unsigned char KeyShakeCounter = C_KEY_SHAKE;
const unsigned char OffShakeCounter = C_OFF_SHAKE;
const unsigned char KeyValidNumber = C_VALID_KEY;

const unsigned char VolValue = VOL_VALUE;
const unsigned char SluValue = SLU_VALUE;
const unsigned char CmBase = CM_BASE;
const unsigned char C_Tp_En = C_TP_EN;

#endif





