#include "Structs.h"

_sys_ sys;//ϵͳ��ʼ�����

uint8_t Speed_Unit;//�ٶȵ�λ
uint8_t Speed_Mode;//�ٶ�ģʽ
uint8_t SpeedIcon_Step;//ת��ͼ��ת������
uint32_t Ctrl_Speed;//�����ٶȣ�����ֵ��
int32_t Set_Speed;//�����ٶ�
int8_t  Val_Speed;//�ٶ�����
int8_t  Val_xg;//����������
uint32_t Rel_Speed;//ʵ���ٶ�
uint32_t Speed_Cnt;//���ת��
uint32_t Speed;//��ʱ�洢�ٶ�
uint32_t Speed_New;//�����ٶ���ʾ�������
uint32_t Speed_Last;//�����ٶ���ʾ����洢
uint32_t Display_RelSpeed;//������ʾ�ٶ�
uint32_t Display_SetSpeed;//��ʾ�ٶ�
uint16_t Speed_MAX;//����ٶ�

int32_t Ctrl_Time;//����ʱ�䣨����ֵ��
int32_t Set_Time;//����ʱ��
int32_t Display_CtrlTime;//��ʾ����ʱ��
int32_t Display_SetTime;//��ʾ����ʱ��
int32_t Time;//��ʱ�洢ֵ
uint8_t Time_Unit;//ʱ�䵥λ
uint8_t DownTime_Over;//ʱ�䵹��ʱ����

uint8_t PModeIcon_Step;//����ģʽͼ��ת������
uint8_t PMode_Option;//Pģʽѡ��
uint8_t Circle_Run;//��Ȧ�ı�־λ
uint8_t Show_Circle;//Pģʽ��Ȧ��ʾ

uint8_t Safe_Mode;//��ȫģʽ
uint8_t Safe_Temp_Flag;//��ȫ�¶ȳ���
uint8_t Safe_Temp_Twinkleg;//��ȫ�¶�ͼ����˸
int16_t Safe_Set_Temp;//��ȫ�趨�¶�
int16_t Safe_Rel_Temp;//��ȫʵ���¶�
int16_t Display_SafeTemp;//��ʾ��ȫ�¶�
uint8_t Lid_State;//����״̬
