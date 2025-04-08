#ifndef __DRV_EC11A_H__
#define __DRV_EC11A_H__

#include "include.h"

/**********宏定义************/
#define EC11A_FastSpeed 40//旋钮快转的值
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
	TIM_HandleTypeDef *Tim;//选用的定时器
	uint8_t EC11A_Fast;//旋钮快转的值
	uint8_t FlagTim;//计时标志
    
	float EC11A_Speed;//旋转旋钮时的速度
	uint16_t EC11A_Cnt;//旋动时的，一圈是20个
	uint8_t EC11A_Knob;//在旋动旋钮时
	uint8_t TIM_Cnt;//定时器计数
	
	float Key_Cnt;//按下时间
	uint8_t Key_Flag;//按键按下标志
	uint8_t LongPress;//按键长按标志
	
}_EC11A_;
extern _EC11A_ EC11A[2];//旋钮参数

/**********全局变量声明******/
extern uint8_t Work_Option;//工位号
extern uint8_t SetMode_Option;//选择设置模式
extern uint8_t EC11A_Knob;//在旋动旋钮时
extern uint8_t Run_Status;//系统状态
extern uint8_t Work_All;//工位设置相同

/**********全局函数**********/
void Check_Knob(void);//检测旋钮状态
void EC11A_Init(void);//EC11A初始化定时器
void TimCnt_Check(float dT);//定时器计数检测
void EC11AKey_Scan(float dT);//EC11A按键扫描
void EC11A_Speed(float dT);//EC11A旋钮速度计算

#endif
