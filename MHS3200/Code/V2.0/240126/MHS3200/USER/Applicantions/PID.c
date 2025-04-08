#include "PID.h"

/**********结构体************/
PID_val_t Speed_Val_L1;//pid数据结构
PID_val_t Speed_Val_L2;//pid数据结构
PID_val_t Speed_Val_L3;//pid数据结构
PID_val_t Speed_Val_L4;//pid数据结构
PID_val_t Speed_Val_L5;//pid数据结构
PID_val_t Speed_Val_L6;//pid数据结构
PID_val_t Speed_Val_L7;//pid数据结构
PID_val_t Speed_Val_L8;//pid数据结构
PID_val_t Speed_Val_L9;//pid数据结构
PID_arg_t Speed_Arg;//pid数据系数
PID_val_t Temp_Val;//pid数据结构
PID_arg_t Temp_Arg;//pid数据系数

/*
*****************************************************************
 * 函数原型： void PID_Init(void)
 * 功    能： pid系数初始化
*****************************************************************
*/
void PID_Init(void)
{
	Speed_Arg.Kp=0.035;
	Speed_Arg.Ki=0.00051;
	Speed_Arg.Kd=0.0009;
    Temp_Arg.Kp = 1.4;//比例系数
    Temp_Arg.Ki = 0.02;//积分系数
    Temp_Arg.Kd = 0.04; //微分系数
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
	if(pid_val->Error > 200)
	{
		pid_val->Error = 200;
	}
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
 * 函数原型： void PID_Calc(float NextPoint ,float SetPoint)
 * 功    能： PID算法
 * 输    入:  NextPoint；实际温度 , SetPoint：设定温度
 * 参    数： float NextPoint ,float SetPoint
*****************************************************************
*/
void PID_Calc(float NextPoint ,float SetPoint)
{
	Temp_Val.Error = SetPoint-NextPoint;//计算误差
	Temp_Val.SumError+=Temp_Val.Error;//计算误差和
	Temp_Val.D_Error =Temp_Val.LastError-Temp_Val.PrevError;//计算微分误差
	Temp_Val.PrevError =  Temp_Val.LastError;//保存这次误差
	Temp_Val.LastError =  Temp_Val.Error;//保存上一次误差
	Temp_Val.Integral = Temp_Arg.Ki*Temp_Val.SumError;//计算积分值
	if(Temp_Val.Integral>1000)//积分限幅
	{
		Temp_Val.Integral=1000;	
	}
	Temp_Val.Out = Temp_Arg.Kp*Temp_Val.Error+Temp_Val.Integral+Temp_Arg.Kd*Temp_Val.D_Error;//输出PID的值
	if(Temp_Val.Out>100)
		Temp_Val.Out=100;//PWM占空比宽带/
	if(Temp_Val.Out<0)
		Temp_Val.Out=0;// PWM占空比宽带              
}
