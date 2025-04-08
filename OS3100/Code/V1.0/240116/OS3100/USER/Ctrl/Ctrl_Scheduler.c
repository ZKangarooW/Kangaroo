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

static void Loop_2ms(void)//2ms执行一次
{
    Display_Show();//显示屏幕
}

static void Loop_10ms(void)//10ms执行一次
{   
    EC11AKey_Scan(0.01f);
}

static void Loop_50ms(void)//50ms执行一次
{
    Buzzer_Status(0.05);//蜂鸣器检测
	Check_Speed();//检测速度是否停止
	Motor_Ctrl();//电机控制
}

static void Loop_100ms(void)//100ms执行一次
{
    Cheak_TimeDown(100);//时间倒计时检测
	Check_MotorStop(0.1f);//检测电机是否停止
	Check_Display(0.1f);//检测不操作时熄屏
}

static void Loop_500ms(void)//500ms执行一次
{
    Check_Press(0.5f);
	Check_ShowFlag(500);//屏幕闪烁检测
}

static void Loop_1S(void)//1S执行一次
{
     EC11A_Speed(1.0f);
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
