#include "Ctrl_Scheduler.h"

uint16_t  T_cnt_2ms=0,
          T_cnt_10ms=0,
          T_cnt_50ms=0,
          T_cnt_100ms=0,
          T_cnt_500ms=0,
          T_cnt_1S=0;

void Loop_Check(void)
{
    T_cnt_2ms++;
    T_cnt_10ms++;
    T_cnt_50ms++;
    T_cnt_100ms++;
    T_cnt_500ms++;
    T_cnt_1S++;

    Sys_Loop();
}

static void Loop_2ms(void)//2msִ��һ��
{

}

static void Loop_10ms(void)//10msִ��һ��
{   
    EC11AKey_Scan(0.01f);//EC11A����ɨ��
}

static void Loop_50ms(void)//50msִ��һ��
{
	Check_Set();//�������
    Motor_Ctrl();//�������
    Check_Speed(0.05f);
}

static void Loop_100ms(void)//100msִ��һ��
{
    Cheak_TimeDown(100);//ʱ�䵹��ʱ���
	Buzzer_Status(0.1f);//���������
	Param_Save_Overtime(0.1f);//�����־λ��1��0.5s�󱣴�
	Check_MotorStop(0.1f);//������Ƿ�ֹͣ
}

static void Loop_500ms(void)//500msִ��һ��
{
    Check_ShowFlag(0.5f);//��Ļ��˸��� 
	Check_Knob(0.5f);//�����ť��״̬
}

static void Loop_1S(void)//1Sִ��һ��
{
    EC11A_Speed(1.0);//EC11A��ť�ٶȼ���
}

void Sys_Loop(void)
{
    if(T_cnt_2ms >= 2) {
        Loop_2ms();
        T_cnt_2ms = 0;
    }
    if(T_cnt_10ms >= 10) {
        Loop_10ms();
        T_cnt_10ms = 0;
    }
    if(T_cnt_50ms >= 50) {
        Loop_50ms();
        T_cnt_50ms = 0;
    }
    if(T_cnt_100ms >= 100) {
        Loop_100ms();
        T_cnt_100ms = 0;
    }
    if(T_cnt_500ms >= 500) {
        Loop_500ms();
        T_cnt_500ms = 0;
    }
    if(T_cnt_1S >= 1000) {
        Loop_1S();
        T_cnt_1S = 0;
    }
}
