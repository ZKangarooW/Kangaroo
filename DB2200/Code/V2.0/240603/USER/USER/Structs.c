#include "Structs.h"

_sys_ sys;//ϵͳ��ʼ�����

int32_t Ctrl_Time;//����ʱ�䣨����ֵ��
int32_t Set_Time;//����ʱ��
int32_t Display_CtrlTime;//��ʾ����ʱ��
int32_t Display_SetTime;//��ʾ����ʱ��
int32_t Time;//��ʱ�洢ֵ
uint8_t Time_Unit;//ʱ�䵥λ
uint8_t Time_State;//ʱ���״̬
uint8_t DownTime_Over;//ʱ�䵹��ʱ����

int Set_Temp;//�����¶�
int Ctrl_Temp;//�����¶ȣ�����ֵ��
int Ture_Temp;//����¶�
int Rel_Temp;//ʵ���¶�
int Display_RelTemp;//��ʾʵ���¶�
int Display_CtrlTemp;//��ʾ�����¶�
int Temp;//��ʱ�洢�¶�
uint8_t Temp_ADDMode;//�¶���ʾģʽ
int Temp_New,Temp_Last;//�����¶ȡ�֮ǰ�¶�
uint8_t HEAT_ICO;//����ͼ��
int ADD_Wait_Count;//���½��µ�ʱ��

uint8_t Display_Circle;//Pģʽ��Ȧ
uint8_t Circle_Run;//��Ȧ�ı�־λ
uint8_t Show_Circle;//Pģʽ��Ȧ��ʾ
uint8_t PMode_Status;//Pģʽ״̬
uint8_t PMode_Mode;//Pģʽ���ݶȺͼ����л�
uint8_t PMode_Option;//Pģʽѡ��
uint8_t PMode_P1;//PģʽP1ֵ
uint8_t PMode_P2;//PģʽP2ֵ
