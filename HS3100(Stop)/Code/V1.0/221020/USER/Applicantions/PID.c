#include "PID.h"

/**********结构体************/
PID_val_t Speed_Val;//pid数据结构
PID_arg_t Speed_Arg;//pid数据系数
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;


/*
*****************************************************************
 * 函数原型： void PID_Init(void)
 * 功    能： pid系数初始化
*****************************************************************
*/
void PID_Init(void)
{
	Speed_Arg.Kp=0.08;
	Speed_Arg.Ki=0.000646;
	Speed_Arg.Kd=0.00043;

	Temp_Arg.Kp = 1000*0.001f;
	Temp_Arg.Ki = 20*0.001f;
	Temp_Arg.Kd = 8000*0.001f;//控台面
}

/*
*****************************************************************
 * 函数原型： void PID_Speed(
            uint16_t Expect,   //期望值（设定值）
            uint16_t Feedback, //反馈值（实际值）
            PID_arg_t *pid_arg,//PID参数结构体
            PID_val_t *pid_val)//PID数据结构体
 * 功    能： PID控制
 * 输    入:  Expect,   //期望值（设定值） 
              Feedback, //反馈值（实际值）
              PID_arg_t *pid_arg,//PID参数结构体
              PID_arg_t *pid_arg,//PID参数结构体
*****************************************************************
*/
void PID_Speed(
            uint16_t Expect,   //期望值（设定值）
            uint16_t Feedback, //反馈值（实际值）
            PID_arg_t *pid_arg,//PID参数结构
            PID_val_t *pid_val)//PID数据结构体
            
{  
    pid_val->Error = Expect - Feedback;//当前误差
	if(pid_val->Error > 100)
		pid_val->Error = 100;
    pid_val->SumError = pid_val->Error + pid_val->SumError;//误差和
    pid_val->D_Error = pid_val->Error - pid_val->LastError;//误差偏差  
    pid_val->LastError = pid_val->Error;//保存上一次误差
    pid_val->Out = pid_arg->Kp*pid_val->Error+pid_arg->Ki*pid_val->SumError+pid_arg->Kd*pid_val->D_Error;
    if(pid_val->Out<0) 
        pid_val->Out=0;
    if(pid_val->Out>0&&pid_val->Out<2500)
        pid_val->Out=pid_val->Out;
}


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
    PID_Val->Integral = LIMIT(PID_Val->Integral, -Integral_Lim, Integral_Lim);//积分限幅

    PID_Val->Out = PID_Val->Proportion + PID_Val->Integral + PID_Val->Fb_Differential;//PID输出

    PID_Val->Freedback_Old = Freedback;//将当前反馈值赋值给上一次反馈值
}
