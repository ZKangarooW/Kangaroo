#ifndef __TEMPCONTROL_H__
#define __TEMPCONTROL_H__

#include "main.h"

/**********�궨��************/
#define HEAT htim3.Instance->CCR2//����ģ��PWM
#define safe_div(numerator,denominator,safe_value) ( (denominator == 0) ? (safe_value) : ((numerator)/(denominator)) )
#define LIMIT( x,min,max ) ( (x) < (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) )

/**********�ṹ��************/
typedef struct
{
	float Kp;//����ϵ��
	float Ki;//����ϵ��
	float Kd;//΢��ϵ��
	float Kf;//ǰ��ϵ��
}_PID_Arg_;

typedef struct
{
	float Proportion;//����
	float Integral;//����
	float Differential;//΢��
	
	float Fb_Differential;//΢������
		
	float Error;//���
	float Proportion_Last;//��һ�α���
	float Freedback_Old;//��һ������ֵ
	
	float Out;//���
}_PID_Val_;
extern _PID_Val_ Temp_Val;//pid���ݽṹ
extern _PID_Arg_ Temp_Arg;//pid����ϵ��

/**********ȫ�ֱ���**********/
extern uint8_t ADD_Mode;//�¶ȼ���״̬

/**********ȫ�ֺ���**********/
void PID_Init(void);//PIDϵ����ʼ��
void temp_control(void);//�¶ȼ��ȿ���

#endif
