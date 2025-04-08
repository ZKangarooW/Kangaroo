#ifndef __PID_H__
#define	__PID_H__

#include "include.h"

/**********�궨��************/
#define LIMIT( x,min,max ) ( (x) < (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) )
#define safe_div(numerator,denominator,safe_value) ( (denominator == 0) ? (safe_value) : ((numerator)/(denominator)) )
#define ABS(x) ((x)>0?(x):-(x))

/**********�ṹ��************/
typedef struct
{
	float Kp;//����ϵ��
	float Ki;//����ϵ��
	float Kd;//΢��ϵ��
}_PID_Arg_;
extern _PID_Arg_ Speed_Arg;

typedef struct
{
	float Proportion;//����
	float Integral;//����
	float Differential;//΢��
	
	float Error;//���
	float Error_Last;//��һ�����
	float Error_Previous;//���ϴ����
	
		
	float Fb_Differential;//΢������
	float Proportion_Last;//��һ�α���
	float Freedback_Old;//��һ������ֵ
	
	float Out;//���
}_PID_Val_;
extern _PID_Val_ Speed_Val;;

/**********ȫ�ֱ�������******/
/**********ȫ�ֺ���**********/
void AltPID_Calculation(float dT, float Expect, float Freedback, _PID_Arg_ * PID_Arg, _PID_Val_ * PID_Val, float Error_Lim, float Integral_Lim);//λ��ʽPID����
void IncPID_Calculation(float dT,float Expect,float Freedback,_PID_Arg_ * PID_Arg,_PID_Val_ * PID_Val,float Integral_Lim);//����ʽPID����

#endif
