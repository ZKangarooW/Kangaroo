#include "Scheduler.h"

uint16_t  T_cnt_2ms=0,
          T_cnt_10ms=0,
          T_cnt_50ms=0,
          T_cnt_100ms=0,
          T_cnt_200ms=0,
          T_cnt_500ms=0,
          T_cnt_1S=0;

void Loop_Check(void)
{
    T_cnt_2ms++;
    T_cnt_10ms++;
    T_cnt_50ms++;
    T_cnt_100ms++;
    T_cnt_200ms++;
    T_cnt_500ms++;
    T_cnt_1S++;

    Sys_Loop();
}

static void Loop_2ms(void)//2msִ��һ��
{

}

static void Loop_10ms(void)//10msִ��һ��
{
    Read_Temp();//��ȡ�¶�
    Key_Handle(0.01f);//�������
	Check_Set();//�������
}

static void Loop_50ms(void)//50msִ��һ��
{
	temp_control();//�¶ȿ���
    Buzzer_Status(0.05);
}

static void Loop_100ms(void)//100msִ��һ��
{
    Cheak_ShowFlag(100);//��˸���
    Cheak_TimeDown(100);//����ʱ
	time_icn(0.1f);//����ʱʱ��ͼ����˸ 
	ADD_Show(100);//��ʾ����ʱ��
	Param_Save_Overtime(0.1f);//�����־λ��
}

static void Loop_200ms(void)//200msִ��һ��
{
    check_set(0.2f);
}

static void Loop_500ms(void)//500msִ��һ��
{
    
}

static void Loop_1S(void)//1Sִ��һ��
{
    Check_Key();
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
    if(T_cnt_200ms >= 200) {
        Loop_200ms();
        T_cnt_200ms = 0;
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
