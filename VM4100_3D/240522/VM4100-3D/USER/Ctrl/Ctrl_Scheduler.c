#include "Ctrl_Scheduler.h"

uint16_t  T_cnt_2ms=0,
          T_cnt_10ms=0,
          T_cnt_100ms=0,
          T_cnt_500ms=0,
          T_cnt_1S=0;

void Loop_Check(void)
{
    T_cnt_2ms++;
    T_cnt_10ms++;
    T_cnt_100ms++;
    T_cnt_500ms++;
    T_cnt_1S++;

    Sys_Loop();
}

static void Loop_2ms(void)//2ms执行一次
{
    Check_Set();//检测设置
}

static void Loop_10ms(void)//10ms执行一次
{   
    Key_Scan(0.01f);//矩阵按键扫描
    Motor_Ctrl();//电机控制
}

static void Loop_100ms(void)//100ms执行一次
{
    Cheak_TimeDown(100);//时间倒计时检测
	Buzzer_Status(0.1f);
	Param_Save_Overtime(0.1f);//保存标志位置1，0.5s后保存
}

static void Loop_500ms(void)//500ms执行一次
{
    Check_ShowFlag(0.5f);//屏幕闪烁检测
}

static void Loop_1S(void)//1S执行一次
{
    Check_Key();//检测按键是否还在按
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
