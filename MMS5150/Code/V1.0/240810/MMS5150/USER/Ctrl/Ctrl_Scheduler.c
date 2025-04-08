#include "Ctrl_Scheduler.h"

/**********�ֲ���������*******/
uint16_t T_cnt_2ms = 0,
         T_cnt_10ms = 0,
         T_cnt_50ms = 0,
         T_cnt_100ms = 0,
         T_cnt_200ms = 0,
         T_cnt_500ms = 0,
         T_cnt_1S = 0;

/**
 * @brief ʱ����
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
 * @brief 2msִ��һ��
 *
 * @param dT ��������
 */
static void Loop_2ms(float dT)
{
    
}

/**
 * @brief 10msִ��һ��
 *
 * @param dT ��������
 */
static void Loop_10ms(float dT)
{
    
}

/**
 * @brief 50msִ��һ��
 *
 * @param dT ��������
 */
static void Loop_50ms(float dT)
{
    Buzzer_Status(dT);
}

/**
 * @brief 100msִ��һ��
 *
 * @param dT ��������
 */
static void Loop_100ms(float dT)
{
    
}

/**
 * @brief 200msִ��һ��
 *
 * @param dT ��������
 */
static void Loop_200ms(float dT)
{
 
}

/**
 * @brief 500msִ��һ��
 *
 * @param dT ��������
 */
static void Loop_500ms(float dT)
{
    
}

/**
 * @brief 1Sִ��һ��
 *
 * @param dT ��������
 */
static void Loop_1S(float dT)
{
	
}

/**
 * @brief �������
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
