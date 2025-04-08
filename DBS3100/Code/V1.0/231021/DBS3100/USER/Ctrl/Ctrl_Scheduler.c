#include "Ctrl_Scheduler.h"

/**********局部变量声明******/
uint16_t  T_cnt_2ms=0,
          T_cnt_10ms=0,
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
    T_cnt_2ms++;
    T_cnt_10ms++;
	T_cnt_50ms++;
    T_cnt_100ms++;
    T_cnt_200ms++;
    T_cnt_500ms++;
    T_cnt_1S++;

    Sys_Loop();
}
uint8_t val,val1;
static void Loop_2ms(float dT)//2ms执行一次
{
	Read_Temp(dT);//读取温度
}

static void Loop_10ms(float dT)//10ms执行一次
{   
	Key_Scan(dT);//按键扫描
	val = HAL_GPIO_ReadPin(HALL1_GPIO_Port,HALL1_Pin);
	val1 = HAL_GPIO_ReadPin(HALL2_GPIO_Port,HALL2_Pin);
}

static void Loop_50ms(float dT)//50ms执行一次
{
    Buzzer_Status(dT);//蜂鸣器的状态检测
}

static void Loop_100ms(float dT)//100ms执行一次
{

}

static void Loop_200ms(float dT)//200ms执行一次
{

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
    if(T_cnt_200ms >= 10) {
        Loop_200ms(0.01f);
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
