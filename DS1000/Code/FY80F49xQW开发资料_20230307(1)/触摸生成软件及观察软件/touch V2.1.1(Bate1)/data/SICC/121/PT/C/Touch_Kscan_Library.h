#ifndef	_TOUCH_KSCAN_LIBRARY_H_
#define	_TOUCH_KSCAN_LIBRARY_H_


#pragma warning disable 752,759

//接口函数声明
extern void CheckTouchKey(void);	//按键扫描主过程函数,建议在2.5ms~5ms内调用
extern volatile bit b_kerr;			//复位按键标志,将其置1可以重置全部按键

//每个按键对应于寄存器的1个位,由高至低一一对应
//KeyFlag[0]对应于Key7,...,Key1,Key0
//KeyFlag[1]对应于Key15,...,Key9,Key8
//按键有效时相应位为1,无效时为0
extern volatile unsigned char KeyFlag[2];

//防水模式选择,不定义则为组合键模式
#define		WaterMode

//同时最大允许有效按键数,超过该值将认为是干扰
#define		C_VALID_KEY		1

//按键最大允许生效时间(单位：ms),以4ms调用基准换算,为0时将忽略
#define		C_VALID_TIME	60*(1000/4)

//按键消抖次数
#define		C_KEY_SHAKE		2

//待检测按键总数
#define		C_KEY_TOTAL		1

//使能的按键通道
#define		C_KEY_CHANNEL	0x00

//各触摸检测通道对应的按键序号,未使用的通道设置为0x80
const unsigned char Table_KeyEnable[3][4] = {
	0x80,			//触摸通道1不检测按键
	0x80,			//触摸通道2不检测按键
	0x80,			//触摸通道3不检测按键
	0x80,			//触摸通道4不检测按键
	0x80,			//触摸通道5不检测按键
	0x80,			//触摸通道6不检测按键
	0x80,			//触摸通道7不检测按键
	0x80,			//触摸通道8不检测按键
	0x80,			//触摸通道9不检测按键
	0x80,			//触摸通道10不检测按键
	0x80,			//触摸通道11不检测按键
	0x80			//触摸通道12不检测按键
};

//灵敏度选择,调整长短线后再用这个修正灵敏度差异,设定值不可低于5
const unsigned char Table_KeyDown[] = {

};






/***********************************************************
下面的内容请勿修改
***********************************************************/
unsigned int KeyResSum[C_KEY_TOTAL];
unsigned int KeyOldValue0[C_KEY_TOTAL];
unsigned int KeyOldValue1[C_KEY_TOTAL];
unsigned int KeyOldValue2[C_KEY_TOTAL];
unsigned int KeyReference[C_KEY_TOTAL];
unsigned char KeyUpShake[C_KEY_TOTAL];

const unsigned char KeyTimerWidth = 230;
const unsigned int KeyChannelSel = C_KEY_CHANNEL;
const unsigned int KeyValidTime = C_VALID_TIME;
const unsigned char KeyTotalNumber = C_KEY_TOTAL;
const unsigned char KeyShakeCounter = C_KEY_SHAKE;
const unsigned char KeyValidNumber = C_VALID_KEY;

#ifdef WaterMode
const unsigned char WaterModeSel = 1;
#else
const unsigned char WaterModeSel = 0;
#endif

#endif
