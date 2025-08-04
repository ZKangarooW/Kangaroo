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

static void Loop_10ms(float dT)//10ms执行一次
{   
	Key_Scan(dT);//按键扫描
	Check_Set(dT);//检测设置
	Ctrl_Lock(dT);//关开盖检测
}

static void Loop_100ms(float dT)//100ms执行一次
{
	Buzzer_Status(dT);//蜂鸣器的状态检测
	Cheak_TimeDown(dT);//时间倒计时检测
	Twinkle(dT);//闪烁函数
	Param_Save_Overtime(dT);//保存标志位置
	Motor_Ctrl(dT);//控制速度
}

static void Loop_500ms(float dT)//500ms执行一次
{
	Check_Press(dT);//检测按键按下状态
	
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
