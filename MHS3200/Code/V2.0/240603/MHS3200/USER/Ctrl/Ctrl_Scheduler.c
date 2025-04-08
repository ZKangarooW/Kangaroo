#include "Ctrl_Scheduler.h"

uint16_t  T_cnt_1ms=0,
          T_cnt_2ms=0,
          T_cnt_10ms=0,
          T_cnt_50ms=0,
          T_cnt_100ms=0,
          T_cnt_200ms=0,
          T_cnt_500ms=0,
          T_cnt_1S=0;

void Loop_Check(void)
{
    T_cnt_1ms++;
    T_cnt_2ms++;
    T_cnt_10ms++;
    T_cnt_50ms++;
    T_cnt_100ms++;
    T_cnt_200ms++;
    T_cnt_500ms++;
    T_cnt_1S++;

    Sys_Loop();
}

static void Loop_1ms(void)//1ms执行一次
{
    TimCnt_Check(0.001f);//定时器计数检测
}

static void Loop_2ms(void)//2ms执行一次
{
    Check_Set();//检测设置
}

static void Loop_10ms(void)//10ms执行一次
{   
    EC11AKey_Scan(0.01f);//EC11A按键扫描
	#if(Integration_TYPE == 0)
		if(Param.type >= 2)//设置成加热款
		{
			temp_Control(0.01f);//温度控制
			Read_Temp();//读取温度
		}
		else
		{
			HEAT = 0;
		}
	#endif
}

static void Loop_50ms(void)//50ms执行一次
{
    Check_Speed();//检测速度是否停止
    Motor_Ctrl();//电机控制
	#if(Integration_TYPE == 0)//四六联时
		ADD_Show(0.05f);
		Start_SpeedRun(0.05f);//转速动画
	#endif
    Buzzer_Status(0.05);//蜂鸣器检测
}

static void Loop_100ms(void)//100ms执行一次
{
    Cheak_TimeDown(100);//时间倒计时检测
	Param_Save_Overtime(0.1f);//保存标志位置1，0.5s后保存
}

static void Loop_200ms(void)//200ms执行一次
{
   
}

static void Loop_500ms(void)//500ms执行一次
{
    Check_ShowFlag(500);//屏幕闪烁检测
    Check_Knob();//旋钮旋动检测
}

static void Loop_1S(void)//1S执行一次
{
    EC11A_Speed(1.0f);//EC11A旋钮速度计算
	#if(Integration_TYPE == 0)//四六联时
		if(Param.type >= 2)//设置成加热款
		{
			PID_Cap(1.0f);
		}
	#endif
}

void Sys_Loop(void)
{
    if(T_cnt_1ms >= 1) {
        Loop_1ms();
        T_cnt_1ms = 0;
    }
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
