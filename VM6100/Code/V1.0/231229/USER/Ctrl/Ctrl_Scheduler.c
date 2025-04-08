#include "Ctrl_Scheduler.h"

/**********�ֲ���������******/
uint16_t  T_cnt_1ms=0,
		  T_cnt_6ms=0,
          T_cnt_10ms=0,
		  T_cnt_12ms=0,
		  T_cnt_20ms=0,
          T_cnt_50ms=0,
          T_cnt_100ms=0,
          T_cnt_200ms=0,
          T_cnt_500ms=0,
          T_cnt_1S=0;

/*
*****************************************************************
 * ����ԭ�ͣ�void Loop_Check(void)
 * ��    �ܣ�ʱ����
*****************************************************************
*/
void Loop_Check(void)
{
	T_cnt_1ms++;
    T_cnt_6ms++;
    T_cnt_10ms++;
	T_cnt_12ms++;
	T_cnt_20ms++;
    T_cnt_50ms++;
    T_cnt_100ms++;
    T_cnt_200ms++;
    T_cnt_500ms++;
    T_cnt_1S++;

    Sys_Loop();
}

static void Loop_1ms(float dT)//1msִ��һ��
{
	Deal_Speed(dT);//�ٶ���ʾ����
	Show_Display();//��ʾ��Ļ����
}

static void Loop_6ms(float dT)//6msִ��һ��
{
	
}

static void Loop_10ms(float dT)//10msִ��һ��
{   
    EC11AKey_Scan(dT);//EC11A����ɨ��
	Check_Set(dT);//�������
}

static void Loop_12ms(float dT)//12msִ��һ��
{   
    
}

static void Loop_20ms(float dT)//20msִ��һ��
{
    
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
	Check_MotorStop(dT);//������Ƿ�ֹͣ
}

static void Loop_200ms(float dT)//200msִ��һ��
{
	
}

static void Loop_500ms(float dT)//500msִ��һ��
{
    Param_Save_Overtime(dT);//�����־λ��
	Check_Press(dT);//��ⰴ������״̬
}

static void Loop_1S(float dT)//1Sִ��һ��
{
	EC11A_Speed(dT);//EC11A��ť�ٶȼ���
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Sys_Loop(void)
 * ��    �ܣ��������
*****************************************************************
*/
void Sys_Loop(void)
{
	if(T_cnt_1ms >= 1) {
        Loop_1ms(0.001f);
        T_cnt_1ms = 0;
    }
    if(T_cnt_6ms >= 6) {
        Loop_6ms(0.006f);
        T_cnt_6ms = 0;
    }
    if(T_cnt_10ms >= 10) {
        Loop_10ms(0.01f);
        T_cnt_10ms = 0;
    }
	if(T_cnt_12ms >= 12) {
        Loop_12ms(0.012f);
        T_cnt_12ms = 0;
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
    if(T_cnt_1S >= 1000) {
        Loop_1S(1.0f);
        T_cnt_1S = 0;
    }
}
