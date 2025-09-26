#ifndef __DRV_EC11A_H__
#define __DRV_EC11A_H__

#include "include.h"

/**********宏定义************/
#define EC11A_Tim_1 htim16 // 旋钮1的定时器

#define EC11A_FastSpeed 40 // 旋钮快转的值

// 用于识别按键按下的状态识别
#define EC11A_PRESS RESET // 低电平识别

#define EC11A_DOWN EC11A_PRESS /*键按下*/
#define EC11A_UP !EC11A_PRESS  /*键弹起*/

/**********结构体************/
typedef struct
{
	uint16_t EXTI_Pin;		  // EC11A旋钮中断引脚
	uint16_t EC11A_Pin;		  // EC11A旋钮输入引脚
	GPIO_TypeDef *EC11A_GPIO; // EC11A旋钮输入GPIO端口
	uint16_t Key_Pin;		  // EC11A按键输入引脚
	GPIO_TypeDef *Key_GPIO;	  // EC11A按键输入GPIO端口
	TIM_HandleTypeDef *Tim;	  // 选用的定时器
	uint8_t EC11A_Fast;		  ////旋钮快转的值

	float EC11A_Speed;	// 旋转旋钮时的速度
	uint16_t EC11A_Cnt; // 旋动时的，一圈是20个
	uint8_t EC11A_Knob; // 在旋动旋钮时
	uint8_t TIM_Cnt;	// 定时器计数

	float Key_Cnt;	   // 按下时间
	uint8_t Key_Flag;  // 按键按下标志
	uint8_t LongPress; // 按键长按标志

} _EC11A_;
extern _EC11A_ EC11A[1]; // 旋钮参数

/**********全局变量声明******/
/**********全局函数**********/

void EC11A_Init(void);		  // EC11A初始化定时器
void EC11A_Speed(float dT);	  // EC11A旋钮速度计算
void EC11AKey_Scan(float dT); // EC11A按键扫描
void Check_Press(float dT);	  // 检测按键按下状态-500ms

#endif
