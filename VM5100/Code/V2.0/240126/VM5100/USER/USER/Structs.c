#include "Structs.h"

uint16_t Speed_MAX;//���ת��
uint16_t Speed_MIN;//��Сת��

_sys_ sys;//ϵͳ��ʼ�����

int Ctrl_Speed;//�����ٶȣ�����ֵ��
int Set_Speed;//�����ٶ�
int Rel_Speed;//ʵ���ٶ�
int Display_SetSpeed;//������ʾ�����ٶ�
int Display_RelSpeed;//������ʾʵ���ٶ�
int Speed;//��ʱ�洢�ٶ�
uint8_t Speed_Cnt;//���벶�����Ĵ���
int Speed_New;//�����ٶ���ʾ�������
int Speed_Last;//�����ٶ���ʾ����洢
int Speed_ADDMode;//�����ж��ٶ�ʱ���������½�
uint8_t pwm_start = 8;

int32_t Ctrl_Time;//����ʱ�䣨����ֵ��
int32_t Set_Time;//����ʱ��
int32_t Display_SetTime;//��ʾʱ��
int32_t Display_CtrlTime;//��ʾʱ��
int32_t Time;//��ʱ�洢ֵ
uint8_t Time_State;//ʱ���״̬
uint8_t DownTime_Over;//ʱ�䵹��ʱ����


