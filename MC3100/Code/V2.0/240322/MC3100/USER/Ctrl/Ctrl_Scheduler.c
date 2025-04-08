#include "Ctrl_Scheduler.h"

uint16_t  T_cnt_10ms=0,
          T_cnt_100ms=0,
          T_cnt_500ms=0;

void Loop_Check(void)
{
    T_cnt_10ms++;
    T_cnt_100ms++;
    T_cnt_500ms++;

    Sys_Loop();
}

static void Loop_10ms(float dT)//10msִ��һ��
{   
	Key_Scan(dT);//����ɨ��
	Check_Set(dT);//�������
	Ctrl_Lock(dT);//�ؿ��Ǽ��
}

static void Loop_100ms(float dT)//100msִ��һ��
{
	Buzzer_Status(dT);//��������״̬���
	Cheak_TimeDown(dT);//ʱ�䵹��ʱ���
	Twinkle(dT);//��˸����
	Param_Save_Overtime(dT);//�����־λ��
	Motor_Ctrl(dT);//�����ٶ�
}

static void Loop_500ms(float dT)//500msִ��һ��
{
	Check_Press(dT);//��ⰴ������״̬
	
}

void Sys_Loop(void)
{
    if(T_cnt_10ms >= 10) {
        Loop_10ms(0.01f);
        T_cnt_10ms = 0;
    }
    if(T_cnt_100ms >= 100) {
        Loop_100ms(0.1f);
        T_cnt_100ms = 0;
    }
    if(T_cnt_500ms >= 500) {
        Loop_500ms(0.5f);
        T_cnt_500ms = 0;
    }
}
