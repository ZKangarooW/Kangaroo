#ifndef __PID_H__
#define __PID_H__

#include "include.h"

/**********�ṹ��************/
typedef struct
{
	float Error;//���ֵ
    float D_Error;//΢�����
	float LastError;//��һ�����
	float PrevError;//���ϸ����
	float SumError;//����
	float Integral;//����
	float Out;//PID���
}__attribute__((packed)) PID_val_t;
extern PID_val_t HeatTemp_Val;//pid���ݽṹ
extern PID_val_t CoolTemp_Val;//pid���ݽṹ

typedef struct
{
	float Kp;			 //����ϵ��
	float Ki;			 //����ϵ��
	float Kd;		 	 //΢��ϵ��
}__attribute__((packed)) PID_arg_t;
extern PID_arg_t HeatTemp_Arg;//pid����ϵ��
extern PID_arg_t CoolTemp_Arg;//pid����ϵ��

/**********ȫ�ֺ���**********/
void PID_Init(void);//pidϵ����ʼ��
void PID_Temp(
            int16_t Expect,   //����ֵ���趨ֵ��
            int16_t Feedback, //����ֵ��ʵ��ֵ��
            PID_arg_t *pid_arg,//PID�����ṹ��
            PID_val_t *pid_val);//PID���ݽṹ��

#endif
