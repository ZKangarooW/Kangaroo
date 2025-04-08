#include "PID.h"

/*
*****************************************************************
 * 函数原型：void AltPID_Calculation(float dT, float Expect, float Freedback, _PID_Arg_ * PID_Arg, _PID_Val_ * PID_Val, float Error_Lim, float Integral_Lim)
 * 功    能：微分先行PID计算
 * 输    入：dT：周期（单位：秒）
			 Expect：期望值（设定值）
			 Freedback：反馈值
			 _PID_Arg_ * PID_Arg：PID参数结构体
			 _PID_Val_ * PID_Val：PID数据结构体
			 Error_Lim：误差限幅
			 Integral_Lim：积分误差限幅
 * 参    数：float dT, float Expect, float Freedback, _PID_Arg_ * PID_Arg, _PID_Val_ * PID_Val, float Error_Lim, float Integral_Lim
*****************************************************************
*/
void AltPID_Calculation(float dT, float Expect, float Freedback, _PID_Arg_ * PID_Arg, _PID_Val_ * PID_Val, float Error_Lim, float Integral_Lim)
{
    PID_Val->Error = Expect - Freedback;//误差 = 期望值-反馈值

    PID_Val->Proportion   = PID_Arg->Kp * PID_Val->Error;//比例 = 比例系数*误差
    PID_Val->Fb_Differential = -PID_Arg->Kd * ((Freedback - PID_Val->Freedback_Old) * safe_div(1.0f, dT, 0));//微分 = -（微分系数） * （当前反馈值-上一次反馈值） *频率
    PID_Val->Integral += PID_Arg->Ki * LIMIT(PID_Val->Error, -Error_Lim, Error_Lim) * dT;//积分 = 积分系数*误差*周期
    PID_Val->Integral = LIMIT(PID_Val->Integral, 0, Integral_Lim);//积分限幅

    PID_Val->Out = PID_Val->Proportion + PID_Val->Integral + PID_Val->Fb_Differential;//PID输出

    PID_Val->Freedback_Old = Freedback;//将当前反馈值赋值给上一次反馈值
}

/*
*****************************************************************
 * 函数原型：void IncPID_Calculation(float dT,float Expect,float Freedback,_PID_Arg_ * PID_Arg,_PID_Val_ * PID_Val,float Integral_Lim)
 * 功    能：增量式PID计算
 * 输    入：dT：周期（单位：秒）
			Expect：期望值（设定值）
			Freedback：反馈值
			_PID_Arg_ * PID_Arg：PID参数结构体
			_PID_Val_ * PID_Val：PID数据结构体
 * 参    数：float dT,float Expect,float Freedback,_PID_Arg_ * PID_Arg,_PID_Val_ * PID_Val
*****************************************************************
*/
void IncPID_Calculation(float dT,float Expect,float Freedback,_PID_Arg_ * PID_Arg,_PID_Val_ * PID_Val,float Integral_Lim)
{
	PID_Val->Error = Expect - Freedback;//误差 = 期望值-反馈值
    
	PID_Val->Proportion   = PID_Arg->Kp * (PID_Val->Error - PID_Val->Error_Last);//比例 = 比例系数*（当前误差-上一次误差）
    
    if(PID_Val->Proportion > 5)
        PID_Val->Proportion = 5;
    if(PID_Val->Proportion < -50)
        PID_Val->Proportion = -50;
    
	PID_Val->Integral     = PID_Arg->Ki * PID_Val->Error* dT;//积分 = 积分系数*误差*周期
	PID_Val->Integral     = LIMIT(PID_Val->Integral,-Integral_Lim,Integral_Lim);//积分限幅
	PID_Val->Differential = PID_Arg->Kd * (PID_Val->Error - 2.0f*PID_Val->Error_Last + PID_Val->Error_Previous) * safe_div(1.0f,dT,0);//微分 = 微分系数 * （当前误差-2*上一次误差+上上次误差）*频率
	
	PID_Val->Out += PID_Val->Proportion + PID_Val->Integral + PID_Val->Differential;//PID输出
	
    if(PID_Val->Out > 100)
        PID_Val->Out = 100;
    if(PID_Val->Out < 5)
        PID_Val->Out = 5;
    
    if(PID_Val->Error<0)
        PID_Val->Out = 0;
    
	PID_Val->Error_Previous = PID_Val->Error_Last;//将上一次误差赋值给上上次误差
	PID_Val->Error_Last = PID_Val->Error;//将当前误差赋值给上一次误差
}
