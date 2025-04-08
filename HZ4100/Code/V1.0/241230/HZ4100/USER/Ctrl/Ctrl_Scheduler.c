#include "Ctrl_Scheduler.h"

/**********局部变量声明*******/
uint16_t T_cnt_2ms = 0,
         T_cnt_10ms = 0,
         T_cnt_20ms = 0,
         T_cnt_50ms = 0,
         T_cnt_100ms = 0,
         T_cnt_200ms = 0,
         T_cnt_500ms = 0,
         T_cnt_1S = 0;

/**
 * @brief 时间检测
 *
 */
void Loop_Check(void)
{
    T_cnt_2ms++;
    T_cnt_10ms++;
    T_cnt_20ms++;
    T_cnt_50ms++;
    T_cnt_100ms++;
    T_cnt_200ms++;
    T_cnt_500ms++;
    T_cnt_1S++;

    Sys_Loop();
}

/**
 * @brief 2ms执行一次
 *
 * @param dT 任务周期
 */
static void Loop_2ms(float dT)
{
    Deal_Speed(dT);
}

/**
 * @brief 10ms执行一次
 *
 * @param dT 任务周期
 */
static void Loop_10ms(float dT)
{
//    Cheack_Shake(dT);
    Key_Scan(dT);
    EC11AKey_Scan(dT);
//    Data_Exchange(dT);
}

/**
 * @brief 20ms执行一次
 *
 * @param dT 任务周期
 */
static void Loop_20ms(float dT)
{
    WS2812_Duty(dT);
}

/**
 * @brief 50ms执行一次
 *
 * @param dT 任务周期
 */
static void Loop_50ms(float dT)
{
    Buzzer_Status(dT);
    Check_Speed(dT);
}

/**
 * @brief 100ms执行一次
 *
 * @param dT 任务周期
 */
static void Loop_100ms(float dT)
{
    Twinkle(dT);
    Param_Save_Overtime(dT);
}

/**
 * @brief 200ms执行一次
 *
 * @param dT 任务周期
 */
static void Loop_200ms(float dT)
{
    Check_Set(dT);
    Cheak_TimeDown(dT);
//    Check_Safe_Temp(dT);
}

/**
 * @brief 500ms执行一次
 *
 * @param dT 任务周期
 */
static void Loop_500ms(float dT)
{
    Check_Press(dT);  
}

/**
 * @brief 1S执行一次
 *
 * @param dT 任务周期
 */
static void Loop_1S(float dT)
{
    EC11A_Speed(dT);
}

/**
 * @brief 任务调度
 *
 */
void Sys_Loop(void)
{
    if (T_cnt_2ms >= 2)
    {
        Loop_2ms(0.002f);
        T_cnt_2ms = 0;
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
    if (T_cnt_200ms >= 200)
    {
        Loop_200ms(0.2f);
        T_cnt_200ms = 0;
    }
    if (T_cnt_500ms >= 500)
    {
        Loop_500ms(0.5f);
        T_cnt_500ms = 0;
    }
    if (T_cnt_1S >= 1000)
    {
        Loop_1S(1.0f);
        T_cnt_1S = 0;
    }
}
