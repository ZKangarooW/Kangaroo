#include "PID.h"

/**********�ṹ��************/
PID_val_t Speed_Val_L1;//pid���ݽṹ
PID_val_t Speed_Val_L2;//pid���ݽṹ
PID_val_t Speed_Val_L3;//pid���ݽṹ
PID_val_t Speed_Val_L4;//pid���ݽṹ
PID_val_t Speed_Val_L5;//pid���ݽṹ
PID_val_t Speed_Val_L6;//pid���ݽṹ
PID_val_t Speed_Val_L7;//pid���ݽṹ
PID_val_t Speed_Val_L8;//pid���ݽṹ
PID_val_t Speed_Val_L9;//pid���ݽṹ
PID_arg_t Speed_Arg;//pid����ϵ��
PID_val_t Temp_Val;//pid���ݽṹ
PID_arg_t Temp_Arg;//pid����ϵ��

/*
*****************************************************************
 * ����ԭ�ͣ� void PID_Init(void)
 * ��    �ܣ� pidϵ����ʼ��
*****************************************************************
*/
void PID_Init(void)
{
	Speed_Arg.Kp=0.035;
	Speed_Arg.Ki=0.00051;
	Speed_Arg.Kd=0.0009;
    Temp_Arg.Kp = 1.4;//����ϵ��
    Temp_Arg.Ki = 0.02;//����ϵ��
    Temp_Arg.Kd = 0.04; //΢��ϵ��
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
            PID_arg_t *pid_arg,//PID�����ṹ��
            PID_val_t *pid_val)//PID���ݽṹ��
            
{  
    pid_val->Error = Expect - Feedback;//��ǰ���
	if(pid_val->Error > 200)
	{
		pid_val->Error = 200;
	}
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
 * ����ԭ�ͣ� void PID_Calc(float NextPoint ,float SetPoint)
 * ��    �ܣ� PID�㷨
 * ��    ��:  NextPoint��ʵ���¶� , SetPoint���趨�¶�
 * ��    ���� float NextPoint ,float SetPoint
*****************************************************************
*/
void PID_Calc(float NextPoint ,float SetPoint)
{
	Temp_Val.Error = SetPoint-NextPoint;//�������
	Temp_Val.SumError+=Temp_Val.Error;//��������
	Temp_Val.D_Error =Temp_Val.LastError-Temp_Val.PrevError;//����΢�����
	Temp_Val.PrevError =  Temp_Val.LastError;//����������
	Temp_Val.LastError =  Temp_Val.Error;//������һ�����
	Temp_Val.Integral = Temp_Arg.Ki*Temp_Val.SumError;//�������ֵ
	if(Temp_Val.Integral>1000)//�����޷�
	{
		Temp_Val.Integral=1000;	
	}
	Temp_Val.Out = Temp_Arg.Kp*Temp_Val.Error+Temp_Val.Integral+Temp_Arg.Kd*Temp_Val.D_Error;//���PID��ֵ
	if(Temp_Val.Out>100)
		Temp_Val.Out=100;//PWMռ�ձȿ��/
	if(Temp_Val.Out<0)
		Temp_Val.Out=0;// PWMռ�ձȿ��              
}
