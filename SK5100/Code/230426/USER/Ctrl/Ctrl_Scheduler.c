#include "Ctrl_Scheduler.h"

/**********局部变量声明******/
uint16_t  T_cnt_2ms=0,
          T_cnt_10ms=0,
		  T_cnt_50ms=0,
          T_cnt_100ms=0,
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
	EC11AKey_Scan(dT);//EC11A按键扫描
	Check_Set(dT);//检测设置
}

static void Loop_50ms(float dT)//50ms执行一次
{
	Motor_Ctrl(dT);//电机控制
	Check_Speed(dT);//检测速度是否停止
	Buzzer_Status(dT);//蜂鸣器的状态检测
	
}

static void Loop_100ms(float dT)//100ms执行一次
{
	Deal_Speed(dT);//速度显示处理
	Cheak_TimeDown(dT);//时间倒计时检测
	Twinkle(dT);//闪烁函数
	Check_MotorStop(dT);//检测电机是否停止
}

static void Loop_500ms(float dT)//500ms执行一次
{
	Check_Knob(dT);//检测旋钮的状态
	Param_Save_Overtime(dT);//保存标志位置1，0.5s后保存
}

static void Loop_1S(float dT)//1S执行一次
{
	EC11A_Speed(dT);//EC11A旋钮速度计算
}

/*
*****************************************************************
 * 函数原型：void Sys_Loop(void)
 * 功    能：任务调度
*****************************************************************
*/
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
