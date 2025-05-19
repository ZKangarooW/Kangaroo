#ifndef __TEMPCONTROL_H__
#define __TEMPCONTROL_H__

#include "main.h"

/**********宏定义************/
#define HEAT htim3.Instance->CCR2//加热模块PWM
#define safe_div(numerator,denominator,safe_value) ( (denominator == 0) ? (safe_value) : ((numerator)/(denominator)) )
#define LIMIT( x,min,max ) ( (x) < (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) )

/**********结构体************/
typedef struct
{
	float Kp;//比例系数
	float Ki;//积分系数
	float Kd;//微分系数
	float Kf;//前馈系数
}_PID_Arg_;

typedef struct
{
	float Proportion;//比例
	float Integral;//积分
	float Differential;//微分
	
	float Fb_Differential;//微分先行
		
	float Error;//误差
	float Proportion_Last;//上一次比例
	float Freedback_Old;//上一个反馈值
	
	float Out;//输出
}_PID_Val_;
extern _PID_Val_ Temp_Val;//pid数据结构
extern _PID_Arg_ Temp_Arg;//pid数据系数

/**********全局变量**********/
extern uint8_t ADD_Mode;//温度加热状态

/**********全局函数**********/
void PID_Init(void);//PID系数初始化
void temp_control(void);//温度加热控制

#endif
