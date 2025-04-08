#include "Ctrl_Scheduler.h"

/**********�ֲ���������******/
uint16_t  T_cnt_10ms=0,
		  T_cnt_20ms=0,
          T_cnt_50ms=0,
          T_cnt_100ms=0,
          T_cnt_200ms=0,
          T_cnt_500ms=0;
          
/*
*****************************************************************
 * ����ԭ�ͣ�void Loop_Check(void)
 * ��    �ܣ�ʱ����
*****************************************************************
*/
void Loop_Check(void)
{
    T_cnt_10ms++;
	T_cnt_20ms++;
    T_cnt_50ms++;
    T_cnt_100ms++;
    T_cnt_200ms++;
    T_cnt_500ms++;

    Sys_Loop();
}

static void Loop_10ms(float dT)//10msִ��һ��
{   
    Deal_Speed(dT);//�ٶ���ʾ����
	Key_Scan(dT);//���󰴼�ɨ��
	Check_Set(dT);//�������
}

static void Loop_20ms(float dT)//20msִ��һ��
{
	Ctrl_Lock(dT);//���������
}

static void Loop_50ms(float dT)//50msִ��һ��
{
	Motor_Ctrl(dT);//�����ٶ�
	Check_Speed(dT);//�ٶȾ�ֹ���
    Buzzer_Status(dT);//��������״̬���
}

static void Loop_100ms(float dT)//100msִ��һ��
{
	Cheak_TimeDown(dT);//ʱ�䵹��ʱ���
	Twinkle(dT);//��˸����
	Param_Save_Overtime(dT);//�����־λ��
}

static void Loop_200ms(float dT)//200msִ��һ��
{
	Check_MotorStop(dT);//������Ƿ�ֹͣ��ֹͣ�󿪸�
}

static void Loop_500ms(float dT)//500msִ��һ��
{
	Check_Press(dT);//��ⰴ������״̬
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Sys_Loop(void)
 * ��    �ܣ��������
*****************************************************************
*/
void Sys_Loop(void)
{
    if(T_cnt_10ms >= 10) {
        Loop_10ms(0.01f);
        T_cnt_10ms = 0;
    }
	if(T_cnt_20ms >= 20) {
        Loop_20ms(0.02f);
        T_cnt_20ms = 0;
    }
    if(T_cnt_50ms >= 50) {
        Loop_50ms(0.05f);
        T_cnt_50ms = 0;
    }
    if(T_cnt_100ms >= 100) {
        Loop_100ms(0.1f);
        T_cnt_100ms = 0;
    }
    if(T_cnt_200ms >= 200) {
        Loop_200ms(0.2f);
        T_cnt_200ms = 0;
    }
    if(T_cnt_500ms >= 500) {
        Loop_500ms(0.5f);
        T_cnt_500ms = 0;
    }
}
