#ifndef __SHOW_H__
#define __SHOW_H__

#include "main.h"

/**********ȫ�ֱ���**********/
extern uint32_t rel_time;//ʵʱʱ��
extern uint32_t set_time;//�趨ʱ��
extern uint8_t time_status;//ʱ����ʾģʽ
extern uint8_t Set_Mode_Enable;//P����������ģʽ 0��ģʽ���ò�����ʾ 1��ģʽ������ʾ
extern uint8_t run_mode_flag;//����Pʱ��ʾ
extern uint8_t Select_Option;//����ʱ��ǰ���õ�ѡ��
extern uint16_t Twinkle_Time;//��˸��ʱ��
extern uint16_t Twinkle_On;//��˸����ʱ
extern uint8_t temp_flag;//ѡ�������¶�ʱ��˸
extern uint8_t time_flag;//ѡ������ʱ��ʱ��˸
extern uint8_t mode_flag;//ѡ������ģʽʱ��˸
extern uint8_t circle_dis;//�ݶ�ģʽ����Ȧת����ʾ�������벻�����˼Ĵ����������ȣ�
extern uint8_t circle_dis_flag;//��Ȧ��ʼת���������벻�����˼Ĵ����������ȣ�
extern uint8_t mode_flag_p1;//�ݶ�ģʽ��P1����˸�������벻�����˼Ĵ����������ȣ�
extern uint8_t mode_flag_p2;//�ݶ�ģʽ��P1����˸�������벻�����˼Ĵ����������ȣ�
extern uint8_t mode_run_p1;//�ݶ�ģʽ��P1��ֵ�������벻�����˼Ĵ����������ȣ�
extern uint8_t mode_run_p2;//�ݶ�ģʽ��P1��ֵ�������벻�����˼Ĵ����������ȣ�
extern uint8_t set_mode_p;//Pģʽ���л��ݶ�ģʽ���Ǿͼ���ģʽ 1���ݶ�ģʽ 0��pģʽ�������벻�����˼Ĵ����������ȣ�
extern uint8_t ADD_Wait_Count;//������ʾ��������
extern int Dis_Rel_Temp;//ʵʱʱ��
extern uint8_t SetTime_State;//δ�趨ʱ����ʾ��----��

/**********ȫ�ֺ���**********/
void LCD_Display(void);//��Ļ��ʾ
void Circle_Go(void);//��Ȧת��
void Cheak_ShowFlag(uint16_t dT);//��˸���
void Dis_RelTemp(int dis_rel_temp);//��ʾʵ���¶�
void time_icn(float dT);//����ʱʱ��ͼ����˸ 
void ADD_Show(uint16_t dT);//��ʾ����ʱ��

#endif
