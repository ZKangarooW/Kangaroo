#ifndef __PID_H__
#define __PID_H__

#include "include.h"

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

/**********ȫ�ֱ�������******/
/**********ȫ�ֺ���**********/
void AltPID_Calculation(float dT, float Expect, float Freedback, _PID_Arg_ * PID_Arg, _PID_Val_ * PID_Val, float Error_Lim, float Integral_Lim);//΢������PID����

#endif
