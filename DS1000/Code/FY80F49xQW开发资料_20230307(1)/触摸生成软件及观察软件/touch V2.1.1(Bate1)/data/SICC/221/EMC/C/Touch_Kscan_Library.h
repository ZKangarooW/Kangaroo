/*

*/
#ifndef	_CHECKTOUCHKEY_H_
#define	_CHECKTOUCHKEY_H_

#include "TouchKeyConst.h"
#pragma warning disable 752,759
//接口函数声明
extern void __CMS_CheckTouchKey(void);		//按键扫描主过程函数,建议在2.5ms~5ms内调用
extern void __CMS_GetTouchKeyValue(void);//此函数放在中断，建议中断扫描时间125us
extern volatile bit b_kerr;				//复位按键标志
//每个按键对应于寄存器的1个位,由高至低一一对应
//KeyFlag[0]对应于Key8,...,Key2,Key1
//KeyFlag[1]对应于Key16,...,Key10,Key9
//按键有效时相应位为1,无效时为0
extern volatile unsigned char KeyFlag[2];
//-------------------------------------------------------
//使用时根据实际硬件连接修改下面这三个数组的内容
//注意数组的大小不能小于检测的按键总数

//检测通道设定,为C_KCHS0至C_KCHS15其中之一
const unsigned char Table_KeyChannel[] = {

};

//灵敏度阈值1,,设定值不可低于20,不能大于1023
const unsigned int Table_KeyDown[] = {

};

//灵敏度阈值2,一般情况下与阈值1差别不大,,设定值不可低于20,不能大于1023
const unsigned int Table_KeyDown_Pro[] = {

};
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
/*
常规触摸效果参数设置
*/
//待检测按键总数,常量
#define 	C_KEY_TOTAL		4//最多支持16通道

//按键按下消抖次数C_KEY_SHAKE
#define		C_KEY_SHAKE		2//1~8

//噪声阈值
#define		VOL_VALUE		10			//无干扰下的最大触摸波动值*2,取值范围10~128

//迟滞值
#define		SLU_VALUE		10			//手指按下和放开切换的消抖值,此值需小于等于VOL_VALUE

//触摸基准值更新消抖次数
#define		CM_BASE			10			//消抖时间约为(主程序调用时间4ms*2 + 按键个数*1.5) * CM_BASE

//同时最大允许有效按键数,超过该值将认为是干扰
#define		C_VALID_KEY		2

//按键最大允许生效时间,以扫描时间（例如5ms）为基准换算,为0时将忽略
#define		C_VALID_TIME	(1000/5)*20//20S

/*-------------------------------------------------------
以下数据通常情况下不用修改
-------------------------------------------------------*/
//异常判断使能，当TK值异常重新进行自适应
#define		UNNOL_CHECK		1
//异常判断自恢复次数，超过则不再进行自恢复
#define		UNNOL_TIMES		100

//跳频使能
//0：关闭
//1：开启，降低对外骚扰
#define		C_TP_EN			1

//计数器位数
#define 	TK_TIME			TK_TIME3//0~7 (TK_TIME+8)位

//检测电压
#define 	KEY_LDOSEL		11//0~15
/***********************************************************
下面的内容请勿修改
***********************************************************/
unsigned char __CMS_CurStep[C_KEY_TOTAL];

const unsigned char KeyTotalNumber = C_KEY_TOTAL;
const unsigned char KeyShakeCounter = C_KEY_SHAKE;
const unsigned char VolValue = VOL_VALUE;
const unsigned char SluValue = SLU_VALUE;
const unsigned char CmBase = CM_BASE;
const unsigned char KeyValidNumber = C_VALID_KEY;
const unsigned int  KeyValidTime = C_VALID_TIME;
//-------------------------------------------------------
const unsigned char UnNol_Check = UNNOL_CHECK;
const unsigned char UnNol_Times = UNNOL_TIMES;
const unsigned char C_Tp_En = C_TP_EN;
const unsigned char TK_Time = TK_TIME;
const unsigned char Key_LDOSel = KEY_LDOSEL;

unsigned int Disp_KeyDown[C_KEY_TOTAL];//仅供调试用
unsigned int Disp_KeyDownPro[C_KEY_TOTAL];//仅供调试用
unsigned int NoiseDat[C_KEY_TOTAL];//仅供调试用
unsigned int FactorRawDat[C_KEY_TOTAL];//仅供调试用
//--------------------------------------------------
#endif





