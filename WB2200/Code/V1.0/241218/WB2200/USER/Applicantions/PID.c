#include "PID.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void AltPID_Calculation(float dT, float Expect, float Freedback, _PID_Arg_ * PID_Arg, _PID_Val_ * PID_Val, float Error_Lim, float Integral_Lim)
 * ��    �ܣ�΢������PID����
 * ��    �룺dT�����ڣ���λ���룩
			 Expect������ֵ���趨ֵ��
			 Freedback������ֵ
			 _PID_Arg_ * PID_Arg��PID�����ṹ��
			 _PID_Val_ * PID_Val��PID���ݽṹ��
			 Error_Lim������޷�
			 Integral_Lim����������޷�
 * ��    ����float dT, float Expect, float Freedback, _PID_Arg_ * PID_Arg, _PID_Val_ * PID_Val, float Error_Lim, float Integral_Lim
*****************************************************************
*/
void AltPID_Calculation(float dT, float Expect, float Freedback, _PID_Arg_ * PID_Arg, _PID_Val_ * PID_Val, float Error_Lim, float Integral_Lim)
{
    PID_Val->Error = Expect - Freedback;//��� = ����ֵ-����ֵ

    PID_Val->Proportion   = PID_Arg->Kp * PID_Val->Error;//���� = ����ϵ��*���
    PID_Val->Fb_Differential = -PID_Arg->Kd * ((Freedback - PID_Val->Freedback_Old) * safe_div(1.0f, dT, 0));//΢�� = -��΢��ϵ���� * ����ǰ����ֵ-��һ�η���ֵ�� *Ƶ��
    PID_Val->Integral += PID_Arg->Ki * LIMIT(PID_Val->Error, -Error_Lim, Error_Lim) * dT;//���� = ����ϵ��*���*����
    PID_Val->Integral = LIMIT(PID_Val->Integral, 0, Integral_Lim);//�����޷�

    PID_Val->Out = PID_Val->Proportion + PID_Val->Integral + PID_Val->Fb_Differential;//PID���

    PID_Val->Freedback_Old = Freedback;//����ǰ����ֵ��ֵ����һ�η���ֵ
}

/*
*****************************************************************
 * ����ԭ�ͣ�void IncPID_Calculation(float dT,float Expect,float Freedback,_PID_Arg_ * PID_Arg,_PID_Val_ * PID_Val,float Integral_Lim)
 * ��    �ܣ�����ʽPID����
 * ��    �룺dT�����ڣ���λ���룩
			Expect������ֵ���趨ֵ��
			Freedback������ֵ
			_PID_Arg_ * PID_Arg��PID�����ṹ��
			_PID_Val_ * PID_Val��PID���ݽṹ��
 * ��    ����float dT,float Expect,float Freedback,_PID_Arg_ * PID_Arg,_PID_Val_ * PID_Val
*****************************************************************
*/
void IncPID_Calculation(float dT,float Expect,float Freedback,_PID_Arg_ * PID_Arg,_PID_Val_ * PID_Val,float Integral_Lim)
{
	PID_Val->Error = Expect - Freedback;//��� = ����ֵ-����ֵ
    
	PID_Val->Proportion   = PID_Arg->Kp * (PID_Val->Error - PID_Val->Error_Last);//���� = ����ϵ��*����ǰ���-��һ����
    
    if(PID_Val->Proportion > 5)
        PID_Val->Proportion = 5;
    if(PID_Val->Proportion < -50)
        PID_Val->Proportion = -50;
    
	PID_Val->Integral     = PID_Arg->Ki * PID_Val->Error* dT;//���� = ����ϵ��*���*����
	PID_Val->Integral     = LIMIT(PID_Val->Integral,-Integral_Lim,Integral_Lim);//�����޷�
	PID_Val->Differential = PID_Arg->Kd * (PID_Val->Error - 2.0f*PID_Val->Error_Last + PID_Val->Error_Previous) * safe_div(1.0f,dT,0);//΢�� = ΢��ϵ�� * ����ǰ���-2*��һ�����+���ϴ���*Ƶ��
	
	PID_Val->Out += PID_Val->Proportion + PID_Val->Integral + PID_Val->Differential;//PID���
	
    if(PID_Val->Out > 100)
        PID_Val->Out = 100;
    if(PID_Val->Out < 5)
        PID_Val->Out = 5;
    
    if(PID_Val->Error<0)
        PID_Val->Out = 0;
    
	PID_Val->Error_Previous = PID_Val->Error_Last;//����һ����ֵ�����ϴ����
	PID_Val->Error_Last = PID_Val->Error;//����ǰ��ֵ����һ�����
}
