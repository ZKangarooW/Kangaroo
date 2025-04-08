#include "PID.h"

/**********�ṹ��************/
PID_val_t HeatTemp_Val;//pid���ݽṹ
PID_arg_t HeatTemp_Arg;//pid����ϵ��
PID_val_t CoolTemp_Val;//pid���ݽṹ
PID_arg_t CoolTemp_Arg;//pid����ϵ��

/*
*****************************************************************
 * ����ԭ�ͣ� void PID_Init(void)
 * ��    �ܣ� pidϵ����ʼ��
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
 * ����ԭ�ͣ�void PID_Temp(
            int16_t Expect,   //����ֵ���趨ֵ��
            int16_t Feedback, //����ֵ��ʵ��ֵ��
            PID_arg_t *pid_arg,//PID�����ṹ��
            PID_val_t *pid_val)//PID���ݽṹ��
 * ��    �ܣ� PID����
 * ��    ��:  Expect,   //����ֵ���趨ֵ�� 
              Feedback, //����ֵ��ʵ��ֵ��
              PID_arg_t *pid_arg,//PID�����ṹ��
              PID_arg_t *pid_arg,//PID�����ṹ��
*****************************************************************
*/
void PID_Temp(
            int16_t Expect,   //����ֵ���趨ֵ��
            int16_t Feedback, //����ֵ��ʵ��ֵ��
            PID_arg_t *pid_arg,//PID�����ṹ��
            PID_val_t *pid_val)//PID���ݽṹ��       
{  
    pid_val->Error = Expect - Feedback;//��ǰ���
	if(pid_val->Error > - 100 &&  pid_val->Error < 100)
		pid_val->SumError += pid_val->Error;
	else
		pid_val->SumError = 0;
	
	if(HeatTemp_Val.Error< 0 && HeatTemp_Val.SumError <0)
		HeatTemp_Val.SumError = 0;
    pid_val->D_Error = pid_val->LastError - pid_val->PrevError;//���ƫ��  
	pid_val->PrevError = pid_val->LastError;//������һ�����
    pid_val->LastError = pid_val->Error;//�������
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
