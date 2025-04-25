#include "Ctrl_Scheduler.h"

uint16_t  T_cnt_2ms=0,
          T_cnt_10ms=0,
		  T_cnt_50ms=0,
//          T_cnt_100ms=0,
          T_cnt_500ms=0,
          T_cnt_1S=0;
          
float time_50us;
void Loop_Check(void)
{
    time_50us += 0.05f;
    if(time_50us >= 0.95f)//1ms
    {
        time_50us = 0;
        T_cnt_2ms++;
        T_cnt_10ms++;
        T_cnt_50ms++;
//        T_cnt_100ms++;
        T_cnt_500ms++;
        T_cnt_1S++;

        Sys_Loop();
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ�void TMR0_Config(void)
 * ��    �ܣ���ʱ��0����
*****************************************************************
*/
void TMR0_Config(void)
{
	/*
	(1)����Timer������ģʽ
	*/
	TMR_ConfigRunMode(TMR0, TMR_MODE_TIMING,TMR_TIM_AUTO_8BIT);	
    
	/*
	(2)����Timer ����ʱ��
	*/
	TMR_ConfigTimerClk(TMR0, TMR_CLK_DIV_12);/*Fsys = 48Mhz��Ftimer = 4Mhz,Ttmr=0.25us*/
    
	/*
	(3)����Timer����
	*/	
	TMR_ConfigTimerPeriod(TMR0, 256-200, 256-200);// 200*0.25us = 50us,��������

	/* 
	(4)�����ж�
	*/
	TMR_EnableOverflowInt(TMR0);

	/*
	(5)����Timer�ж����ȼ�
	*/	
	IRQ_SET_PRIORITY(IRQ_TMR0,IRQ_PRIORITY_HIGH);
	IRQ_ALL_ENABLE();	

	/*
	(6)����Timer
	*/
	TMR_Start(TMR0);
}

static void Loop_2ms(float dT)//2msִ��һ��
{
    __CMS_CheckTouchKey();//�����ĺ���
}

static void Loop_10ms(float dT)//10msִ��һ��
{   
    Key_Scan(dT);//���󰴼�ɨ��
    Twinkle(dT);//��˸����
    Show_Display(dT);//��ʾ��Ļ����
    
}

static void Loop_50ms(float dT)//50msִ��һ��
{
    Check_Set(dT);//�������
    Buzzer_Status(dT);//��������״̬���
}

//static void Loop_100ms(float dT)//100msִ��һ��
//{
//    
//}

static void Loop_500ms(float dT)//500msִ��һ��
{
    Cheak_TimeDown(dT);//ʱ�䵹��ʱ���
    Param_Save_Overtime(dT);//�����־λ��1��0.5s�󱣴�
	Check_Press(dT);//��ⰴ������״̬
}

static void Loop_1S(float dT)//1Sִ��һ��
{
	Temp_Control(dT);//�¶ȼ��ȿ���
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
//    if(T_cnt_100ms >= 100) {
//        Loop_100ms(0.1f);
//        T_cnt_100ms = 0;
//    }
    if(T_cnt_500ms >= 500) {
        Loop_500ms(0.5f);
        T_cnt_500ms = 0;
    }
    if(T_cnt_1S >= 1000) {
        Loop_1S(1.0f);
        T_cnt_1S = 0;
    }
}
