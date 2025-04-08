#include "PID.h"

/**********�ṹ��************/
_PID_Val_ Temp_Val;//pid���ݽṹ
_PID_Arg_ Temp_Arg;//pid����ϵ��

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
    PID_Val->Integral = LIMIT(PID_Val->Integral, -Integral_Lim, Integral_Lim);//�����޷�

    PID_Val->Out = PID_Val->Proportion + PID_Val->Integral + PID_Val->Fb_Differential;//PID���

    PID_Val->Freedback_Old = Freedback;//����ǰ����ֵ��ֵ����һ�η���ֵ
}
