#include "Structs.h"

uint16_t MAX_Speed;

_sys_ sys;//ϵͳ��ʼ�����

_Work_Num_ Ctrl_Speed;//�����ٶȣ�����ֵ��
_Work_Num_ Set_Speed;//�����ٶ�
_Work_Num_ Display_Speed;//��ʾ�ٶ�
_Work_Num_ Rel_Speed;//ʵ���ٶ�
_Work_Num_ Speed;//��ʱ�洢�ٶ�
_Work_Num_ Speed_New;//�����ٶ���ʾ�������
_Work_Num_ Speed_Last;//�����ٶ���ʾ����洢
_Work_Num_ Speed_ADDMode;//�����ж��ٶ�ʱ���������½�
_Work_Num_ Display_RelSpeed;//������ʾʵ���ٶ�

_Work_Num_long Ctrl_Time;//����ʱ�䣨����ֵ��
_Work_Num_long Set_Time;//����ʱ��
_Work_Num_long Display_Time;//��ʾʱ��
_Work_Num_long Rel_Time;//ʵ��ʱ��
_Work_Num_long Time;//��ʱ�洢ֵ
_Work_Num_Flag SetTime_State;//����ʱ���״̬
_Work_Num_Flag RelTime_State;//ʵ��ʱ���״̬
_Work_Num_Flag DownTime_Over;//ʱ�䵹��ʱ����
uint8_t Time_unit;//ʱ�䵥λ
_Work_Num_Flag Speed_Cnt;//���벶�����Ĵ���
uint8_t SpeedIcon_Step;//ת��ͼ��ת������

int Set_Temp;//�����¶�
int Ctrl_Temp;//�����¶ȣ�����ֵ��
int Ture_Temp;//����¶�
int Rel_Temp;//ʵ���¶�
int Temp;//��ʱ�洢�¶�
uint8_t Temp_ADDMode;//�¶���ʾģʽ
uint8_t Temp_State;//�¶ȵ�״̬
int Temp_New,Temp_Last;//�����¶ȡ�֮ǰ�¶�
uint8_t ADD_Wait_Count;//������ʾ��������
