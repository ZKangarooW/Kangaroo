#include "Ctrl_Scheduler.h"

/**********局部变量声明*******/
uint16_t T_cnt_2ms = 0,
         T_cnt_10ms = 0,
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
    Display_Show(dT);//显示屏幕
}

/**
 * @brief 10ms执行一次
 *
 * @param dT 任务周期
 */
static void Loop_10ms(float dT)
{
    Key_Scan(dT);
}

/**
 * @brief 50ms执行一次
 *
 * @param dT 任务周期
 */
static void Loop_50ms(float dT)
{
    Check_Set(dT);
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
    Check_ShowFlag(dT);//闪烁检测
}

/**
 * @brief 200ms执行一次
 *
 * @param dT 任务周期
 */
static void Loop_200ms(float dT)
{
    Check_Speed(dT);
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
    Cheak_TimeDown(dT);
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
