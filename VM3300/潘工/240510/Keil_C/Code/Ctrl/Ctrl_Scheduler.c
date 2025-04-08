#include "Ctrl_Scheduler.h"

/**********局部变量声明*******/
uint16_t T_cnt_1ms = 0,
         T_cnt_10ms = 0,
		 T_cnt_20ms = 0,
         T_cnt_50ms = 0,
         T_cnt_100ms = 0,
         T_cnt_500ms = 0;

/**
 * @brief 时间检测
 *
 */
void Loop_Check(void)
{
    T_cnt_1ms++;
    T_cnt_10ms++;
	T_cnt_20ms++;
    T_cnt_50ms++;
    T_cnt_100ms++;
    T_cnt_500ms++;

    Sys_Loop();
}

/**
 * @brief 1ms执行一次
 *
 * @param dT 任务周期
 */
static void Loop_1ms(float dT)
{
	SCD_NT_Scan();
}

/**
 * @brief 10ms执行一次
 *
 * @param dT 任务周期
 */
static void Loop_10ms(float dT)
{
	Touch_Scan(dT);
}

/**
 * @brief 20ms执行一次
 *
 * @param dT 任务周期
 */
static void Loop_20ms(float dT)
{
	Show_Display();
	WS2812_Duty(dT);
}

/**
 * @brief 50ms执行一次
 *
 * @param dT 任务周期
 */
static void Loop_50ms(float dT)
{
	Motor_Ctrl(dT);
    Buzzer_Status(dT);
}

/**
 * @brief 100ms执行一次
 *
 * @param dT 任务周期
 */
static void Loop_100ms(float dT)
{
    
}

/**
 * @brief 500ms执行一次
 *
 * @param dT 任务周期
 */
static void Loop_500ms(float dT)
{
	Check_Speed(dT);
}

/**
 * @brief 任务调度
 *
 */
void Sys_Loop(void)
{
    if (T_cnt_1ms >= 1)
    {
        Loop_1ms(0.001f);
        T_cnt_1ms = 0;
    }
    if (T_cnt_10ms >= 10)
    {
        Loop_10ms(0.01f);
        T_cnt_10ms = 0;
    }
	if (T_cnt_20ms >= 20)
    {
        Loop_20ms(0.02f);
        T_cnt_20ms = 0;
    }
    if (T_cnt_50ms >= 50)
    {
        Loop_50ms(0.05f);
        T_cnt_50ms = 0;
    }
    if (T_cnt_100ms >= 100)
    {
        Loop_100ms(0.1f);
        T_cnt_100ms = 0;
    }
    if (T_cnt_500ms >= 500)
    {
        Loop_500ms(0.5f);
        T_cnt_500ms = 0;
    }
}
