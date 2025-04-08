#include "Ctrl_Scheduler.h"

uint16_t  T_cnt_1ms=0,
          T_cnt_10ms=0,
		  T_cnt_20ms=0,
          T_cnt_50ms=0,
          T_cnt_100ms=0,
          T_cnt_200ms=0,
          T_cnt_500ms=0;

void Loop_Check(void)
{
    T_cnt_1ms++;
    T_cnt_10ms++;
	T_cnt_20ms++;
    T_cnt_50ms++;
    T_cnt_100ms++;
    T_cnt_200ms++;
    T_cnt_500ms++;

    Sys_Loop();
}

static void Loop_1ms(void)//1msִ��һ��
{   
	Deal_Speed();
}

static void Loop_10ms(void)//10msִ��һ��
{   
	Key_Scan(0.01f);//���󰴼�ɨ��
	Read_Temp(0.01f);//��ȡ�¶�
	Check_Set(0.01f);//�������
}

static void Loop_20ms(void)//20msִ��һ��
{
	Ctrl_Lock(0.02f);//���������
}

static void Loop_50ms(void)//50msִ��һ��
{
	Motor_Ctrl(0.05f);//�����ٶ�
	Check_Speed(0.05f);//�ٶȾ�ֹ���
}

static void Loop_100ms(void)//100msִ��һ��
{
	Buzzer_Status(0.1f);//��������״̬���
	Cheak_TimeDown(0.1f);//ʱ�䵹��ʱ���
	Twinkle(0.1f);//��˸����
	Param_Save_Overtime(0.1f);//�����־λ��
}

static void Loop_200ms(void)//200msִ��һ��
{
	Check_MotorStop(0.2f);//������Ƿ�ֹͣ��ֹͣ�󿪸�
	Check_Safe_Temp(0.2f);//��ⰲȫ�¶�
}

static void Loop_500ms(void)//500msִ��һ��
{
	Check_Press(0.5f);//��ⰴ������״̬
}

void Sys_Loop(void)
{
    if(T_cnt_1ms >= 1) {
        Loop_1ms();
        T_cnt_1ms = 0;
    }
    if(T_cnt_10ms >= 10) {
        Loop_10ms();
        T_cnt_10ms = 0;
    }
	if(T_cnt_20ms >= 20) {
        Loop_20ms();
        T_cnt_20ms = 0;
    }
    if(T_cnt_50ms >= 50) {
        Loop_50ms();
        T_cnt_50ms = 0;
    }
    if(T_cnt_100ms >= 100) {
        Loop_100ms();
        T_cnt_100ms = 0;
    }
    if(T_cnt_200ms >= 200) {
        Loop_200ms();
        T_cnt_200ms = 0;
    }
    if(T_cnt_500ms >= 500) {
        Loop_500ms();
        T_cnt_500ms = 0;
    }
}
