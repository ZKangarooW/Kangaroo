#include "PID.h"

/**********结构体************/
PID_val_t Speed_Val;//pid数据结构
PID_arg_t Speed_Arg;//pid数据系数

/*
*****************************************************************
 * 函数原型： void PID_Init(void)
 * 功    能： pid系数初始化
*****************************************************************
*/
void PID_Init(void)
{
	Speed_Arg.Kp=0.018;
	Speed_Arg.Ki=0.027;
	Speed_Arg.Kd=0.002;
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
            PID_arg_t *pid_arg,//PID参数结构体
            PID_val_t *pid_val)//PID数据结构体
{  
    pid_val->Error = Expect - Feedback;//当前误差
	if(pid_val->Error > 140)//限幅误差值，这样可以降低上升速度
	{
		pid_val->Error = 140;
	}
	if(pid_val->Error < -90)//限幅误差值，这样可以降低下降速度
	{
		pid_val->Error = -90;
	}
    pid_val->SumError = pid_val->Error + pid_val->SumError;//误差和
    pid_val->D_Error = pid_val->Error - pid_val->LastError;//误差偏差  
    pid_val->LastError = pid_val->Error;//保存上一次误差
    pid_val->Out = pid_arg->Kp*pid_val->Error+pid_arg->Ki*pid_val->SumError+pid_arg->Kd*pid_val->D_Error;
    if(pid_val->Out<1) 
        pid_val->Out=1;
    if(pid_val->Out>1&&pid_val->Out<200)
        pid_val->Out=pid_val->Out;
}
