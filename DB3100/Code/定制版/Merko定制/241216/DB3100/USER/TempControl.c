#include "TempControl.h"

/**********全局变量**********/
uint8_t ADD_Mode;//温度加热状态

/**********结构体************/
_PID_Val_ Temp_Val;//pid数据结构
_PID_Arg_ Temp_Arg;//pid数据系数

/*
*****************************************************************
 * 函数原型： void PID_Init(void)
 * 功    能： pid系数初始化
*****************************************************************
*/
void PID_Init(void)
{
	Temp_Arg.Kp=10;
	Temp_Arg.Ki=0.14;
	Temp_Arg.Kd=0.4;
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

/*
*****************************************************************
 * 函数原型：void temp_control(void)
 * 功    能：温度加热控制
*****************************************************************
*/
uint16_t adc_val;
uint8_t Out_Enable;
void temp_control(void)
{ 
    int Temp_Out;
	if(Run_Status == 0)
	{
		HEAT = 0;
		return;
	}
	adc_val = Get_ADCVal(ctrl_temp);
	
	if((adc_val - val > -40 && adc_val - val < 40))
		Out_Enable = 1;
	else
		Out_Enable = 0;
	AltPID_Calculation(0.05f, adc_val, val, &Temp_Arg, &Temp_Val, 100, Out_Enable * 1000);
    Temp_Out = (int)Temp_Val.Out;//pid值赋值
	if(Temp_Out<= 0)
		Temp_Out = 0;
    HEAT = Temp_Out;//控制加热模块
}
