#include "Ctrl_Scheduler.h"

uint16_t  T_cnt_2ms=0,
          T_cnt_10ms=0,
		  T_cnt_50ms=0,
          T_cnt_100ms=0,
          T_cnt_200ms=0,
          T_cnt_500ms=0,
          T_cnt_1S=0;
          
uint8_t time_50us;
void Loop_Check(void)
{
    time_50us++;
    if(time_50us > 20)//1ms
    {
        time_50us = 0;
        T_cnt_2ms++;
        T_cnt_10ms++;
        T_cnt_50ms++;
        T_cnt_100ms++;
        T_cnt_200ms++;
        T_cnt_500ms++;
        T_cnt_1S++;

        Sys_Loop();
    }
}

void TMR0_Config(void)
{
	/*
	(1)����Timer������ģʽ
	*/
	TMR_ConfigRunMode(TMR0, TMR_MODE_TIMING,TMR_TIM_AUTO_8BIT);	
	/*
	(2)����Timer ����ʱ��
	*/
	TMR_ConfigTimerClk(TMR0, TMR_CLK_DIV_12);						/*Fsys = 48Mhz��Ftimer = 4Mhz,Ttmr=0.25us*/
	/*
	(3)����Timer����
	*/	
	TMR_ConfigTimerPeriod(TMR0, 256-200, 256-200); 				// 200*0.25us = 50us,��������
		
	/*
	(4)�����ж�
	*/
	TMR_EnableOverflowInt(TMR0);

	/*
	(5)����Timer�ж����ȼ�
	*/	
	IRQ_SET_PRIORITY(IRQ_TMR0,IRQ_PRIORITY_LOW);
	IRQ_ALL_ENABLE();	

	/*
	(6)����Timer
	*/
	TMR_Start(TMR0);
}

static void Loop_2ms(float dT)//2msִ��һ��
{

}

static void Loop_10ms(float dT)//10msִ��һ��
{   
//	#if (Key_Type == 0)
//		Key_Scan(dT);//���󰴼�ɨ��
//	#else
//		EC11AKey_Scan(dT);//EC11A����ɨ��
//	#endif
//	Read_Temp(dT);//��ȡ�¶�
//	Check_Set(dT);//�������
}

static void Loop_50ms(float dT)//50msִ��һ��
{
//	Motor_Ctrl(dT);//�������
//	Check_Speed(dT);//����ٶ��Ƿ�ֹͣ
    Buzzer_Status(dT);//��������״̬���
}

static void Loop_100ms(float dT)//100msִ��һ��
{
//    Cheak_TimeDown(dT);//ʱ�䵹��ʱ���
//    Check_MotorStop(dT);//������Ƿ�ֹͣ
//	Twinkle(dT);//��˸����
}

static void Loop_200ms(float dT)//200msִ��һ��
{
//	Deal_Speed(dT);//�ٶ���ʾ����
//  Deal_Temp(dT);//�¶���ʾ����
}

static void Loop_500ms(float dT)//500msִ��һ��
{
//	Check_Press(dT);//��ⰴ������״̬
//	Param_Save_Overtime(dT);//�����־λ��1��0.5s�󱣴�
}

static void Loop_1S(float dT)//1Sִ��һ��
{
    P05 = ~P05;
//	Temp_Control(dT);//�¶ȼ��ȿ���
//	#if (Key_Type == 1)
//		EC11A_Speed(dT);//EC11A��ť�ٶȼ���
//	#endif
}

void Sys_Loop(void)
{
    if(T_cnt_2ms >= 2) {
        Loop_2ms(0.002f);
        T_cnt_2ms = 0;
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
