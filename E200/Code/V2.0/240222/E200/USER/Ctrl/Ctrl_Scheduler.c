#include "Ctrl_Scheduler.h"

uint16_t T_cnt_1ms=0,
		 T_cnt_2ms=0,
		 T_cnt_4ms=0,
		 T_cnt_6ms=0,
         T_cnt_10ms=0,
		 T_cnt_12ms=0,
		 T_cnt_20ms=0,
         T_cnt_50ms=0,
         T_cnt_100ms=0,
         T_cnt_200ms=0,
         T_cnt_500ms=0,
         T_cnt_1S=0;

void Loop_Check(void)
{
	T_cnt_1ms++;
	T_cnt_2ms++;
	T_cnt_4ms++;
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

static void Loop_1ms(float dT)
{

}

static void Loop_2ms(float dT)
{
	
}

static void Loop_4ms(float dT)
{
	
}

static void Loop_6ms(float dT)
{
	
}

static void Loop_10ms(float dT)
{   
	Key_Scan(dT);//�������
	Read_Temp(dT);//��ȡ�¶�
	Check_Set(dT);//�������
}

static void Loop_12ms(float dT)
{   
	
}

static void Loop_20ms(float dT)
{
	Deal_Temp(dT);//�¶ȴ���
}

static void Loop_50ms(float dT)
{
	Temp_Control(dT);//�¶ȼ��ȿ���
}

static void Loop_100ms(float dT)
{
	Buzzer_Status(dT);//��������״̬���
	Cheak_TimeDown(dT);//ʱ�䵹��ʱ���
	Twinkle(dT);//��˸����
	Param_Save_Overtime(dT);//�����־λ��
}

static void Loop_200ms(float dT)
{

}

static void Loop_500ms(float dT)
{
	Check_Press(dT);//��ⰴ������״̬
	
}

static void Loop_1S(float dT)
{
	
}

void Sys_Loop(void)
{
	if(T_cnt_1ms >= 1) {
        Loop_1ms(0.001f);
        T_cnt_1ms = 0;
    }
	if(T_cnt_2ms >= 2) {
        Loop_2ms(0.002f);
        T_cnt_2ms = 0;
    }
	if(T_cnt_4ms >= 4) {
        Loop_4ms(0.004f);
        T_cnt_4ms = 0;
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
