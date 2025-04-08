#include "Ctrl_Scheduler.h"

uint16_t  T_cnt_2ms=0,
          T_cnt_10ms=0,
          T_cnt_50ms=0,
          T_cnt_100ms=0,
          T_cnt_200ms=0,
          T_cnt_500ms=0,
          T_cnt_1S=0;

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

static void Loop_2ms(void)//2ms执行一次
{
    
}

static void Loop_10ms(void)//10ms执行一次
{   
	Read_Temp();//读取温度
	Key_Scan(0.01f);//按键扫描
	Check_Set();//检测设置
//	CtrlTemp_Error(0.01f);
}

static void Loop_50ms(void)//50ms执行一次
{  
	Temp_Control(0.05);//温度加热控制
	Check_CtrlTemp_Mode();
}

static void Loop_100ms(void)//100ms执行一次
{
	Buzzer_Status(0.1);//蜂鸣器检测
	Cheak_TimeDown(100);//倒计时检测
	ADD_Show(100);//显示上升时
	time_icn(0.1f);//启动时时间图标闪烁
}

static void Loop_200ms(void)//200ms执行一次
{

}

static void Loop_500ms(void)//500ms执行一次
{
	Check_ShowFlag(500);//屏幕闪烁检测
	Check_Show_PModeFlag(0.5);
	Circle_Go();
}

static void Loop_1S(void)//1S执行一次
{
	Check_Key();//检测按键是否按下
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
    if(T_cnt_200ms >= 200) {
        Loop_200ms();
        T_cnt_200ms = 0;
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
