#ifndef __PID_H__
#define __PID_H__

#include "include.h"

/**********结构体************/
typedef struct
{
	float Error;//误差值
    float D_Error;//微分误差
	float LastError;//上一个误差
	float PrevError;//上上个误差
	float SumError;//误差和
	float Integral;//积分
	float Out;//PID输出
}__attribute__((packed)) PID_val_t;
extern PID_val_t Speed_Val;//pid数据结构


typedef struct
{
	float Kp;			 //比例系数
	float Ki;			 //积分系数
	float Kd;		 	 //微分系数
}__attribute__((packed)) PID_arg_t;
extern PID_arg_t Speed_Arg;//pid数据系数


typedef struct
{
	float Kp;//比例系数
	float Ki;//积分系数
	float Kd;//微分系数
	float Kf;//前馈系数
}_PID_Arg_;
extern _PID_Arg_ Temp_Arg;
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
extern _PID_Val_ Temp_Val;

#define safe_div(numerator,denominator,safe_value) ( (denominator == 0) ? (safe_value) : ((numerator)/(denominator)))
#define LIMIT( x,min,max ) ( (x) < (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) )

/**********全局函数**********/
void PID_Init(void);//pid系数初始化
void PID_Speed(
            uint16_t Expect,   //期望值（设定值）
            uint16_t Feedback, //反馈值（实际值）
            PID_arg_t *pid_arg,//PID参数结构体
            PID_val_t *pid_val);//PID数据结构体
void AltPID_Calculation(float dT, float Expect, float Freedback, _PID_Arg_ * PID_Arg, _PID_Val_ * PID_Val, float Error_Lim, float Integral_Lim);//微分先行PID计算

#endif
