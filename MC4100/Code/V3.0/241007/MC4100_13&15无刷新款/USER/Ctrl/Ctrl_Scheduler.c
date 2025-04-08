#include "Ctrl_Scheduler.h"

uint16_t  T_cnt_1ms=0,
          T_cnt_10ms=0,
		  T_cnt_20ms=0,
          T_cnt_50ms=0,
          T_cnt_100ms=0,
          T_cnt_200ms=0,
          T_cnt_500ms=0;

void Loop_Check(void)
{
    T_cnt_1ms++;
    T_cnt_10ms++;
	T_cnt_20ms++;
    T_cnt_50ms++;
    T_cnt_100ms++;
    T_cnt_200ms++;
    T_cnt_500ms++;

    Sys_Loop();
}

static void Loop_1ms(void)//1ms执行一次
{   
	Deal_Speed();
}

static void Loop_10ms(void)//10ms执行一次
{   
	Key_Scan(0.01f);//矩阵按键扫描
	Read_Temp(0.01f);//读取温度
	Check_Set(0.01f);//检测设置
}

static void Loop_20ms(void)//20ms执行一次
{
	Ctrl_Lock(0.02f);//电磁铁控制
}

static void Loop_50ms(void)//50ms执行一次
{
	Motor_Ctrl(0.05f);//控制速度
	Check_Speed(0.05f);//速度静止检测
}

static void Loop_100ms(void)//100ms执行一次
{
	Buzzer_Status(0.1f);//蜂鸣器的状态检测
	Cheak_TimeDown(0.1f);//时间倒计时检测
	Twinkle(0.1f);//闪烁函数
	Param_Save_Overtime(0.1f);//保存标志位置
}

static void Loop_200ms(void)//200ms执行一次
{
	Check_MotorStop(0.2f);//检测电机是否停止，停止后开盖
	Check_Safe_Temp(0.2f);//检测安全温度
}

static void Loop_500ms(void)//500ms执行一次
{
	Check_Press(0.5f);//检测按键按下状态
}

void Sys_Loop(void)
{
    if(T_cnt_1ms >= 1) {
        Loop_1ms();
        T_cnt_1ms = 0;
    }
    if(T_cnt_10ms >= 10) {
        Loop_10ms();
        T_cnt_10ms = 0;
    }
	if(T_cnt_20ms >= 20) {
        Loop_20ms();
        T_cnt_20ms = 0;
    }
    if(T_cnt_50ms >= 50) {
        Loop_50ms();
        T_cnt_50ms = 0;
    }
    if(T_cnt_100ms >= 100) {
        Loop_100ms();
        T_cnt_100ms = 0;
    }
    if(T_cnt_200ms >= 200) {
        Loop_200ms();
        T_cnt_200ms = 0;
    }
    if(T_cnt_500ms >= 500) {
        Loop_500ms();
        T_cnt_500ms = 0;
    }
}
