#ifndef __DRV_EC11A_H__
#define __DRV_EC11A_H__

#include "include.h"

/**********宏定义************/
#define EC11A_FastSpeed 20//旋钮快转的值

//用于识别按键按下的状态识别 
#define PRESS RESET//低电平识别

#define KEY_DOWN PRESS/*键按下*/
#define KEY_UP  !PRESS/*键弹起*/

/**********结构体************/
typedef struct
{
	uint16_t EXTI_Pin;//EC11A旋钮中断引脚
	uint16_t EC11A_Pin;//EC11A旋钮输入引脚
	GPIO_TypeDef* EC11A_GPIO;//EC11A旋钮输入GPIO端口
	uint16_t Key_Pin;//EC11A按键输入引脚
	GPIO_TypeDef* Key_GPIO;//EC11A按键输入GPIO端口
	uint8_t EC11A_Fast;////旋钮快转的值
	
	float EC11A_Speed;//旋转旋钮时的速度
	float EC11A_Cnt;//旋动时的，一圈是20个
	float EC11A_Knob;//在旋动旋钮时
	
	float Key_Cnt;//按下时间
	uint8_t Key_Flag;//按键按下标志
	uint8_t LongPress;//按键长按标志
	
}_EC11A_;
extern _EC11A_ EC11A[2];//旋钮参数

/**********全局变量声明******/
/**********全局函数**********/

void EC11A_Init(void);
void EC11AKey_Scan(float dT);
void Check_Press(float dT);
void EC11A_Speed(float dT);

#endif
