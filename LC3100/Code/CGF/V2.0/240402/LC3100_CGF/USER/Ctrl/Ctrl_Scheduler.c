#include "Ctrl_Scheduler.h"

/**********局部变量声明******/
uint16_t  T_cnt_1ms=0,
		  T_cnt_6ms=0,
          T_cnt_10ms=0,
		  T_cnt_12ms=0,
		  T_cnt_20ms=0,
          T_cnt_50ms=0,
          T_cnt_100ms=0,
          T_cnt_200ms=0,
          T_cnt_500ms=0,
          T_cnt_1S=0;

/*
*****************************************************************
 * 函数原型：void Loop_Check(void)
 * 功    能：时间检测
*****************************************************************
*/
void Loop_Check(void)
{
	T_cnt_1ms++;
    T_cnt_6ms++;
    T_cnt_10ms++;
	T_cnt_12ms++;
	T_cnt_20ms++;
    T_cnt_50ms++;
    T_cnt_100ms++;
    T_cnt_200ms++;
    T_cnt_500ms++;
    T_cnt_1S++;

    Sys_Loop();
}

static void Loop_1ms(float dT)//1ms执行一次
{
	Deal_Speed(dT);//速度显示处理
}

static void Loop_6ms(float dT)//6ms执行一次
{
	
}

static void Loop_10ms(float dT)//10ms执行一次
{   
	Key_Scan(dT);//矩阵按键扫描
	Read_Temp(dT);//读取温度
	Check_Set(dT);//检测设置
}

static void Loop_12ms(float dT)//12ms执行一次
{   
    
}

static void Loop_20ms(float dT)//20ms执行一次
{
	Ctrl_Lock(dT);//电磁铁控制
}

static void Loop_50ms(float dT)//50ms执行一次
{
    Motor_Ctrl(dT);//控制速度
	Check_Speed(dT);//速度静止检测
	Check_Shock(dT);//检测震动
}

static void Loop_100ms(float dT)//100ms执行一次
{
    Buzzer_Status(dT);//蜂鸣器的状态检测
	Cheak_TimeDown(dT);//时间倒计时检测
	Twinkle(dT);//闪烁函数
	Param_Save_Overtime(dT);//保存标志位置
}

static void Loop_200ms(float dT)//200ms执行一次
{
	Check_MotorStop(dT);//检测电机是否停止，停止后开盖
	Check_Safe_Temp(dT);//检测安全温度
}

static void Loop_500ms(float dT)//500ms执行一次
{
	Check_Press(dT);//检测按键按下状态
}

static void Loop_1S(float dT)//1S执行一次
{
	
}

/*
*****************************************************************
 * 函数原型：void Sys_Loop(void)
 * 功    能：任务调度
*****************************************************************
*/
void Sys_Loop(void)
{
	if(T_cnt_1ms >= 1) {
        Loop_1ms(0.001f);
        T_cnt_1ms = 0;
    }
    if(T_cnt_6ms >= 6) {
        Loop_6ms(0.006f);
        T_cnt_6ms = 0;
    }
    if(T_cnt_10ms >= 10) {
        Loop_10ms(0.01f);
        T_cnt_10ms = 0;
    }
	if(T_cnt_12ms >= 12) {
        Loop_12ms(0.012f);
        T_cnt_12ms = 0;
    }
	if(T_cnt_20ms >= 20) {
        Loop_20ms(0.02f);
        T_cnt_20ms = 0;
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
