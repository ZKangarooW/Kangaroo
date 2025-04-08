#include "PID.h"

/**********�ṹ��************/
PID_val_t Speed_Val;//pid���ݽṹ
PID_arg_t Speed_Arg;//pid����ϵ��
_PID_Arg_ Temp_Arg;
_PID_Val_ Temp_Val;


/*
*****************************************************************
 * ����ԭ�ͣ� void PID_Init(void)
 * ��    �ܣ� pidϵ����ʼ��
*****************************************************************
*/
void PID_Init(void)
{
	Speed_Arg.Kp=0.08;
	Speed_Arg.Ki=0.000646;
	Speed_Arg.Kd=0.00043;

	Temp_Arg.Kp = 1000*0.001f;
	Temp_Arg.Ki = 20*0.001f;
	Temp_Arg.Kd = 8000*0.001f;//��̨��
}

/*
*****************************************************************
 * ����ԭ�ͣ� void PID_Speed(
            uint16_t Expect,   //����ֵ���趨ֵ��
            uint16_t Feedback, //����ֵ��ʵ��ֵ��
            PID_arg_t *pid_arg,//PID�����ṹ��
            PID_val_t *pid_val)//PID���ݽṹ��
 * ��    �ܣ� PID����
 * ��    ��:  Expect,   //����ֵ���趨ֵ�� 
              Feedback, //����ֵ��ʵ��ֵ��
              PID_arg_t *pid_arg,//PID�����ṹ��
              PID_arg_t *pid_arg,//PID�����ṹ��
*****************************************************************
*/
void PID_Speed(
            uint16_t Expect,   //����ֵ���趨ֵ��
            uint16_t Feedback, //����ֵ��ʵ��ֵ��
            PID_arg_t *pid_arg,//PID�����ṹ
            PID_val_t *pid_val)//PID���ݽṹ��
            
{  
    pid_val->Error = Expect - Feedback;//��ǰ���
	if(pid_val->Error > 100)
		pid_val->Error = 100;
    pid_val->SumError = pid_val->Error + pid_val->SumError;//����
    pid_val->D_Error = pid_val->Error - pid_val->LastError;//���ƫ��  
    pid_val->LastError = pid_val->Error;//������һ�����
    pid_val->Out = pid_arg->Kp*pid_val->Error+pid_arg->Ki*pid_val->SumError+pid_arg->Kd*pid_val->D_Error;
    if(pid_val->Out<0) 
        pid_val->Out=0;
    if(pid_val->Out>0&&pid_val->Out<2500)
        pid_val->Out=pid_val->Out;
}


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
