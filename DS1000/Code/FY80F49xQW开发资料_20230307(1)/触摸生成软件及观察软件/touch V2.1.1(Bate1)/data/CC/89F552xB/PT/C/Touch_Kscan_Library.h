
#ifndef	_CHECKTOUCHKEY_H_
#define	_CHECKTOUCHKEY_H_
#include "TouchKeyConst.h"

#pragma warning disable 752,759

//接口函数声明
extern void __CMS_CheckTouchKey(void);		//按键扫描主过程函数,建议在2.5ms~5ms内调用
extern volatile bit _CMS_b_kerr;				//复位按键标志

//每个按键对应于寄存器的1个位,由高至低一一对应
//_CMS_KeyFlag[0]对应于Key7,...,Key1,Key0
//_CMS_KeyFlag[1]对应于Key15,...,Key9,Key8
//按键有效时相应位为1,无效时为0
extern volatile unsigned char _CMS_KeyFlag[2];

//防水模式选择,不定义则为组合键模式
//#define 	WaterMode

//同时最大允许有效按键数,超过该值将认为是干扰
#define		C_VALID_KEY		4//1~16

//按键最大允许生效时间,以4ms为基准换算,为0时将忽略
#define		C_VALID_TIME	(1000/4)*60 //0~65535

//按键消抖次数
#define		C_KEY_SHAKE		2 //0~7

//待检测按键总数,常量
#define 	C_KEY_TOTAL		4 //1~16

//内部比较器参考电压设定,在下列值中选取
//_CMS_KVREF_04	=>	0.4VDD
//_CMS_KVREF_05	=>	0.5VDD
//_CMS_KVREF_06	=>	0.6VDD
//_CMS_KVREF_07	=>	0.7VDD
#define		C_KVREF			C_KVREF_05

//转换时钟设定,在下列值中选取
//C_KCLK_SYS2	=>	系统时钟的2分频
//C_KCLK_SYS4	=>	系统时钟的4分频
//C_KCLK_SYS8	=>	系统时钟的8分频
//注意：1、5V供电时，若INTRC_SEL主频选择16M，建议触摸转换时钟选择8分频，不能选择2分频
//		2、5V供电时，若INTRC_SEL主频选择8M，建议触摸转换时钟选择4分频/8分频
//		3、3V及以下供电时，触摸转换时钟需选择8分频
#define		C_KCLK			C_KCLK_SYS8


//使用时根据实际硬件连接修改下面这三个数组的内容
//注意数组的大小不能小于检测的按键总数

//检测通道设定,为_CMS_KCHS0至_CMS_KCHS15其中之一
const unsigned char _CMS_Table_KeyChannel[] = {

};

//内部并联电容选择，用来调整长短线，以最长的线为0，适当调大短线的值，范围:C_KCAP0至C_KCAP7
const unsigned char _CMS_Table_KeyCap[] = {

};

//下降有效幅度选择,调整长短线后再用这个修正灵敏度差异
//低灵敏度时设定值不可低于6
//高灵敏度时设定值不可低于20
const unsigned char _CMS_Table_KeyDown[] = {

};

//高灵敏触摸使能
//1:使能
//0:不使能
#define		HIGHSENSITIVE		0





/***********************************************************
下面的内容一般不用修改
***********************************************************/
//触摸结束滤波次数
#define		CM_LVBO			0 //0~7

/***********************************************************
下面的内容请勿修改
***********************************************************/
unsigned int  _CMS_KeyResSum[C_KEY_TOTAL];
unsigned int  _CMS_KeyOldValue0[C_KEY_TOTAL];
unsigned int  _CMS_KeyOldValue1[C_KEY_TOTAL];
unsigned int  _CMS_KeyOldValue2[C_KEY_TOTAL];
unsigned int  _CMS_KeyReference[C_KEY_TOTAL];
unsigned char _CMS_KeyUpShake[C_KEY_TOTAL];

const unsigned int  _CMS_KeyValidT = C_VALID_TIME;
const unsigned char _CMS_KeyTNumber = C_KEY_TOTAL;
const unsigned char _CMS_KeyShakeC = C_KEY_SHAKE;
const unsigned char _CMS_KeyCLK = C_KCLK;
const unsigned char _CMS_KeyValidC = C_VALID_KEY;
const unsigned char _CMS_HSens = HIGHSENSITIVE;
const unsigned char _CMS_Lb = CM_LVBO;

#ifdef	WaterMode
const unsigned char _CMS_WModeSel = 1;
#else
const unsigned char _CMS_WModeSel = 0;
#endif
#endif





