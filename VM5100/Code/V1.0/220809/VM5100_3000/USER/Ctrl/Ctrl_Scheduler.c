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
    EC11A_FlagCheak(2);//旋钮检测延时
}

static void Loop_10ms(void)//10ms执行一次
{   
    Check_KeyState();//按键检测 
}

static void Loop_50ms(void)//50ms执行一次
{
	Check_Set();//检测设置
    Motor_Ctrl();//电机控制
}

static void Loop_100ms(void)//100ms执行一次
{
    Cheak_TimeDown(100);//时间倒计时检测
	Buzzer_Status(0.1f);//蜂鸣器检测
	Param_Save_Overtime(0.1f);//保存标志位置1，0.5s后保存
	Check_MotorStop(0.1f);//检测电机是否停止
}

static void Loop_500ms(void)//500ms执行一次
{
    Check_ShowFlag(500);//屏幕闪烁检测 
	Check_Knob();//旋钮旋动检测
}

static void Loop_1S(void)//1S执行一次
{
    Check_Speed();//检测速度是否停止
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
