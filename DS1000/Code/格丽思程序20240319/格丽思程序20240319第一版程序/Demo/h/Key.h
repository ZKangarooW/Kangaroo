#ifndef _KEY_H_
#define _KEY_H_

#define U8_MAX 0xFF
#define U16_MAX 0xFFFF

#define On 0
#define Off 1


typedef enum
{
		Free = 0,				//未按下
		On_Off,					//开关
		Function,				//功能
		Boil,		//沸腾/取消，长按除氯
		Add,						//+
		Sub,						//-
}KeyValue_t;

extern KeyValue_t KeyValueScan;



typedef enum
{
	PowerOn,								//开机状态
	Temp45,									//45℃状态
	Temp55,									//休眠状态
	Temp60,									//温度选择状态
	Temp85,									//沸腾加热状态
	Temp90, 								//沸腾除氯加热状态
	Temp100,								//保温加热状态
	SelfTest,								//自检状态
}SystemState_t;

extern SystemState_t State;
extern SystemState_t Pre_State; //煮沸前的状态
extern unsigned char xdata KeyProcessFlag;	//按键处理标记位

void Kscan(void);
void KeyProcess(void);
void AddProcess(void);
void SubProcess(void);
void LongPress(void);
void SelfTestProcess(void);

#endif