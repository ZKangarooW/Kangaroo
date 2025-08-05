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

static void Loop_2ms(float dT)//2ms执行一次
{
    
}

static void Loop_10ms(float dT)//10ms执行一次
{   
	Key_Scan(dT);//按键扫描
	Check_Set(dT);//检测设置
	Motor_Ctrl(dT);//电机控制
	Read_Temp(dT);//读取温度-10ms
}

static void Loop_50ms(float dT)//50ms执行一次
{
    
}

static void Loop_100ms(float dT)//100ms执行一次
{
	Buzzer_Status(dT);//蜂鸣器的状态检测
	Param_Save_Overtime(dT);//保存标志位置
	Twinkle(dT);//闪烁函数
	Cheak_TimeDown(dT);//时间倒计时检测
}

static void Loop_500ms(float dT)//500ms执行一次
{
	Check_Press(dT);//检测按键按下状态
	
}

static void Loop_1S(float dT)//1S执行一次
{
	Temp_Control(dT);//温度加热控制
	Check_Speed(dT);//检测速度是否停止
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
    if(T_cnt_500ms >= 500) {
        Loop_500ms(0.5f);
        T_cnt_500ms = 0;
    }
    if(T_cnt_1S >= 1000) {
        Loop_1S(1.0f);
        T_cnt_1S = 0;
    }
}
