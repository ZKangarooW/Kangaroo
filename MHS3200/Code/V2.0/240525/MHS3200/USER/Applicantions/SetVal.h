#ifndef __SETVAL_H__
#define __SETVAL_H__

#include "include.h"

/**********ȫ�ֱ�������******/
extern uint8_t SetOK_Flag;//����Ƿ񲨶���ť�����ñ�־λ

/**********ȫ�ֺ���**********/
void Set_Val(uint8_t flag,uint8_t Work_Option,uint8_t SetMode_Option);//������ֵ
void Check_Set(void);//�������
void SetALL_int(int Val,_Work_Num_ *Work_Num);//
void SetALL_int8(uint8_t Val,_Work_Num_Flag *Work_Num);//���ṹͼ�еĲ�����ֵ-uint8_t��
void SetALL_int32(uint32_t Val,_Work_Num_long *Work_Num);//���ṹͼ�еĲ�����ֵ-uint32_t��
void SetALL_TimeOver(_Work_Num_long *Work_Num1,_Work_Num_long *Work_Num);//�������ṹ������Ĳ�����Ӧ��ֵ�����ڽ���ʱ�临ԭ
void SetALL_SpeedOver(_Work_Num_ *Work_Num1,_Work_Num_ *Work_Num);////�������ṹ������Ĳ�����Ӧ��ֵ�����ڽ����ٶȸ�ԭ
void Speed_ALL(uint8_t work,_Work_Num_ *Work_Num,_Work_Num_ *Work_Num1);//ͬ�����ܣ������й�λ���ٶ�ͬ��
void Time_ALL(uint8_t work,_Work_Num_long *Work_Num,_Work_Num_long *Work_Num1);//ͬ�����ܣ������й�λ��ʱ��ͬ��
void Flag_ALL(uint8_t work,_Work_Num_Flag *Work_Num,_Work_Num_Flag *Work_Num1);//ͬ�����ܣ������й�λ��flagͬ��
void Set_Speeds(_Work_Num_ *Work_Num,_Work_Num_ *Work_Num1,_Work_Num_ *Work_Num2,_Work_Num_ *Work_Num3,_Work_Num_ *Work_Num4,_Work_Num_ *Work_Num5);//�ж������ٶ���ֵ�Ƿ�ı�
void Set_Times(_Work_Num_long *Work_Num,_Work_Num_long *Work_Num1,_Work_Num_long *Work_Num2,_Work_Num_long *Work_Num3,_Work_Num_long *Work_Num4,_Work_Num_long *Work_Num5);//�ж�����ʱ����ֵ�Ƿ�ı�
void Check_Time_State(_Work_Num_Flag *Work_Num,_Work_Num_long *Work_Num1);//�ж�ʱ��״̬

#endif
