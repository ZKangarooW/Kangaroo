/*

*/
#ifndef	_CHECKTOUCHKEY_H_
#define	_CHECKTOUCHKEY_H_

#pragma warning disable 752,759
//接口函数声明
extern void __CMS_CheckTouchKey(void);//按键扫描主过程函数,建议在2.5ms~5ms内调用

extern volatile bit b_kerr;//复位按键标志
extern volatile bit KeyOnceOver,KeyOnceHave,KeySleepStr;//休眠唤醒用
//KeyOnceHave = 1说明有按键，芯片唤醒
//当休眠时KeySleepStr = 1，唤醒后KeySleepStr = 0;为1时执行__CMS_CheckTouchKey将减少芯片执行触摸检测时间

//每个按键对应于寄存器的1个位,由高至低一一对应
//KeyFlag[0]对应于Key8,...,Key2,Key1
//KeyFlag[1]对应于Key12,Key11,Key2,Key1
//按键有效时相应位为1,无效时为0
extern volatile unsigned char KeyFlag[2];
//-------------------------------------------------------
//使用时根据实际硬件连接修改下面这两个数组的内容

//各触摸检测通道对应的按键序号(0x00~0x0B)，未使用的通道设置为0x80
const unsigned char Table_KeyEnable[3][4] = {
	0x80,		//触摸通道TK0,未使用
	0x80,		//触摸通道TK1,未使用
	0x80,		//触摸通道TK2,未使用
	0x80,		//触摸通道TK3,未使用
	0x80,		//触摸通道TK4,未使用
	0x80,		//触摸通道TK5,未使用
	0x80,		//触摸通道TK6,未使用
	0x80,		//触摸通道TK7,未使用
	0x80,		//触摸通道TK8,未使用
	0x80,		//触摸通道TK9,未使用
	0x80,		//触摸通道TK10,未使用
	0x80,		//触摸通道TK11,未使用
};//此数组长度不能改

//每个按键下降有效幅度选择,调整长短线后再用这个修正灵敏度差异,设定值不可低于10,范围10~255
const unsigned char Table_KeyDown[] = {

};//此数组长度需大于等于C_KEY_TOTAL按键总数
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
/*
常规触摸效果参数设置
*/
//待检测按键总数,常量
#define 	C_KEY_TOTAL		4//最多12个按键，1~12

//使能的按键通道
#define 	C_KEY_CHANNEL	0x0F00//通道使能,根据实际应用必须设置,芯片管脚上的TK0~TK11分别对应bit0~bit11

//防水模式选择,不定义则为组合键模式
#define 	WaterMode

//同时最大允许有效按键数,超过该值将认为是干扰
#define		C_VALID_KEY		2//1~255

//按键最大允许生效时间,以4ms为基准换算,为0时将忽略
#define		C_VALID_TIME	(1000/4)*60//1~65535

//按键消抖次数
#define		C_KEY_SHAKE		2//1~8



/***********************************************************
下面的内容一般情况不用修改
***********************************************************/
//各触摸检测通道检测时间选择 160~240，值最大，检测时间越短，触摸变化量越小
const unsigned char Table_KeyTime[3][4] = {
	{215,215,215,215},
	{215,215,215,215},
	{215,215,215,215},
	//触摸通道Key1检测时间选择215
	//触摸通道Key2检测时间选择215
	//触摸通道Key3检测时间选择215
	//触摸通道Key4检测时间选择215
};//此数组长度不能改


//按键检测频率选择0~2,越小检测时间越长，响应速度越慢，对外骚扰越小
//建议选择1或者2
#define		KEY_FRESET		2//0~2

//按键检测频率模式选择0~3
//默认3
#define		KEY_FREMODE		3//0~3

//倍频
//0：不使能
//1：使能
#define		KEY_FREDFEN		1//0~1
/***********************************************************
下面的内容请勿修改
***********************************************************/
unsigned int  KeyResSum[C_KEY_TOTAL];
unsigned int  KeyOldValue0[C_KEY_TOTAL];
unsigned int  KeyOldValue1[C_KEY_TOTAL];
unsigned int  KeyOldValue2[C_KEY_TOTAL];
unsigned int  KeyReference[C_KEY_TOTAL];
unsigned char KeyUpShake[C_KEY_TOTAL];

const unsigned int KeyChannelSel = C_KEY_CHANNEL;
const unsigned int KeyValidTime = C_VALID_TIME;
const unsigned char KeyTotalNumber = C_KEY_TOTAL;
const unsigned char KeyShakeCounter = C_KEY_SHAKE;
const unsigned char KeyValidNumber = C_VALID_KEY;
const unsigned char KeyFreSet = KEY_FRESET;
const unsigned char KeyFreMode = KEY_FREMODE;
const unsigned char KeyFreDFEN = KEY_FREDFEN;
#ifdef	WaterMode
const unsigned char WaterModeSel = 1;
#else
const unsigned char WaterModeSel = 0;
#endif


unsigned int Disp_KeyDown[C_KEY_TOTAL];
unsigned int NoiseDat[C_KEY_TOTAL];
unsigned int FactorRawDat[C_KEY_TOTAL];


//--------------------------------------------------
//--------------------------------------------------
//--------------------------------------------------
#endif





