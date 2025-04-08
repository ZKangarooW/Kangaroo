#include "PID.h"

/**********结构体************/
PID_val_t HeatTemp_Val;//pid数据结构
PID_arg_t HeatTemp_Arg;//pid数据系数
PID_val_t CoolTemp_Val;//pid数据结构
PID_arg_t CoolTemp_Arg;//pid数据系数

/*
*****************************************************************
 * 函数原型： void PID_Init(void)
 * 功    能： pid系数初始化
*****************************************************************
*/
void PID_Init(void)
{
	HeatTemp_Arg.Kp=2.6;
	HeatTemp_Arg.Ki=25;
	HeatTemp_Arg.Kd=0;
	
	CoolTemp_Arg.Kp=45;
	CoolTemp_Arg.Ki=25;//25
	CoolTemp_Arg.Kd=0;
}

/*
*****************************************************************
 * 函数原型：void PID_Temp(
            int16_t Expect,   //期望值（设定值）
            int16_t Feedback, //反馈值（实际值）
            PID_arg_t *pid_arg,//PID参数结构体
            PID_val_t *pid_val)//PID数据结构体
 * 功    能： PID控制
 * 输    入:  Expect,   //期望值（设定值） 
              Feedback, //反馈值（实际值）
              PID_arg_t *pid_arg,//PID参数结构体
              PID_arg_t *pid_arg,//PID参数结构体
*****************************************************************
*/
void PID_Temp(
            int16_t Expect,   //期望值（设定值）
            int16_t Feedback, //反馈值（实际值）
            PID_arg_t *pid_arg,//PID参数结构体
            PID_val_t *pid_val)//PID数据结构体       
{  
    pid_val->Error = Expect - Feedback;//当前误差
	if(pid_val->Error > - 100 &&  pid_val->Error < 100)
		pid_val->SumError += pid_val->Error;
	else
		pid_val->SumError = 0;
	
	if(HeatTemp_Val.Error< 0 && HeatTemp_Val.SumError <0)
		HeatTemp_Val.SumError = 0;
    pid_val->D_Error = pid_val->LastError - pid_val->PrevError;//误差偏差  
	pid_val->PrevError = pid_val->LastError;//保存上一次误差
    pid_val->LastError = pid_val->Error;//保存误差
	pid_val->Integral = pid_arg->Ki*pid_val->SumError/10000.0;
	
	if(pid_val->Integral >400)
	{
		pid_val->Integral = 400;
	}
    pid_val->Out = pid_arg->Kp*pid_val->Error+pid_val->Integral+pid_arg->Kd*pid_val->D_Error;
    if(pid_val->Out> 999)
        pid_val->Out= 999;
	if(pid_val->Out< -999)
        pid_val->Out= -999;
}
