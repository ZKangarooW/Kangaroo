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
extern PID_val_t Speed_Val;//pid���ݽṹ

typedef struct
{
	float Kp;			 //����ϵ��
	float Ki;			 //����ϵ��
	float Kd;		 	 //΢��ϵ��
}__attribute__((packed)) PID_arg_t;
extern PID_arg_t Speed_Arg;//pid����ϵ��

/**********ȫ�ֺ���**********/
void PID_Init(void);//pidϵ����ʼ��
void PID_Speed(
            uint16_t Expect,   //����ֵ���趨ֵ��
            uint16_t Feedback, //����ֵ��ʵ��ֵ��
            PID_arg_t *pid_arg,//PID�����ṹ��
            PID_val_t *pid_val);//PID���ݽṹ��

#endif
