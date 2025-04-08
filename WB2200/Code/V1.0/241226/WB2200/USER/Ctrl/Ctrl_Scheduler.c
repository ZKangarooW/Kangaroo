#include "Ctrl_Scheduler.h"

uint16_t    T_cnt_1ms=0,
            T_cnt_10ms=0,
            T_cnt_50ms=0,
            T_cnt_100ms=0,
            T_cnt_500ms=0,
            T_cnt_5000ms=0;
            
static void Loop_1ms(float dT)//1msִ��һ��
{   
    Show_Display();
}

static void Loop_10ms(float dT)//10msִ��һ��
{   
    Read_Temp(dT);//��ȡ�¶�
    Key_Scan(dT);//����ɨ��
    Check_Set(dT);//�������
}

static void Loop_50ms(float dT)//50msִ��һ��
{
    Buzzer_Status(dT);//��������״̬���
}

static void Loop_100ms(float dT)//100msִ��һ��
{
    
    Twinkle(dT);//��˸����
//    Cheak_TimeDown(dT);//ʱ�䵹��ʱ���
    Param_Save_Overtime(dT);//�����־λ��1��0.5s�󱣴�
}

static void Loop_500ms(float dT)//500msִ��һ��
{
    Temp_Control(dT);//�¶ȼ��ȿ��� 
    Check_Press(dT);//��ⰴ������״̬
//    Deal_Temp(dT);//�¶���ʾ����
//printf("RTT print\r\n");
}

static void Loop_5000ms(float dT)//5sִ��һ��
{
//    Temp_Control(dT);
}


void Sys_Loop(void)
{
    if(T_cnt_1ms >= 1) {
        Loop_1ms(0.001f);
        T_cnt_1ms = 0;
    }
    if(T_cnt_10ms >= 10) {
        Loop_10ms(0.01f);
        T_cnt_10ms = 0;
    }
    if(T_cnt_50ms >= 50) {
        Loop_50ms(0.05f);
        T_cnt_50ms = 0;
    }
    if(T_cnt_100ms >= 100) {
        Loop_100ms(0.1f);
        T_cnt_100ms = 0;
    }
    if(T_cnt_500ms >= 500) {
        Loop_500ms(0.5f);
        T_cnt_500ms = 0;
    }
    if(T_cnt_5000ms >= 3000) {
        Loop_5000ms(3.0f);
        T_cnt_5000ms = 0;
    }
}

void Loop_Check(void)
{
    T_cnt_1ms++;
    T_cnt_10ms++;
    T_cnt_50ms++;
    T_cnt_100ms++;
    T_cnt_500ms++;
    T_cnt_5000ms++;
    Sys_Loop();
}
