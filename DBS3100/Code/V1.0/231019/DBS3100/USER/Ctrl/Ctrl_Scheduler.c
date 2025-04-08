#include "Ctrl_Scheduler.h"

uint16_t    T_cnt_10ms=0,
            T_cnt_50ms=0,
            T_cnt_100ms=0,
            T_cnt_500ms=0;

static void Loop_10ms(float dT)//10msִ��һ��
{   
    Key_Scan(dT);//����ɨ��
    Read_Temp(dT);//��ȡ�¶�
    Check_Set(dT);//�������
    Deal_Speed(dT);//�ٶ���ʾ����
}

static void Loop_50ms(float dT)//50msִ��һ��
{
	Motor_Ctrl(dT);//�������
    Check_Speed(dT);//����ٶ��Ƿ�ֹͣ
}

static void Loop_100ms(float dT)//100msִ��һ��
{
    Twinkle(dT);//��˸����
    Buzzer_Status(dT);//��������״̬���
    Cheak_TimeDown(dT);//ʱ�䵹��ʱ���
	Check_AddWater(dT);//����ˮ
	Check_FGS(dT);//��������
	Check_TempStop(dT);//����¶��Ƿ�ֹͣ����
}

static void Loop_500ms(float dT)//500msִ��һ��
{
	Deal_Temp(dT);//�¶���ʾ����
	Temp_Control(dT);//�¶ȼ��ȿ���
    Check_Press(dT);//��ⰴ������״̬
    Param_Save_Overtime(dT);//�����־λ��1��0.5s�󱣴�
}

void Sys_Loop(void)
{
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
}

void Loop_Check(void)
{
    T_cnt_10ms++;
    T_cnt_50ms++;
    T_cnt_100ms++;
    T_cnt_500ms++;

    Sys_Loop();
}
