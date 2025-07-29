#include "Ctrl_DownTime.h"

/*
*****************************************************************
 * 函数原型：void Cheak_TimeDown(float dT)
 * 功    能：时间倒计时检测
 * 输    入: dT:执行周期
 * 参    数：float dT
*****************************************************************
*/
void Cheak_TimeDown(float dT)
{
    static float T[4];
    for(uint8_t i = 0;i<4;i++)
    {
        if(Work_Num[i].Run_Status)//启动系统
        {
            if(Work_Num[i].Temp.Ctrl)
            {
                if(Work_Num[i].Time.Rel > 0 && Work_Num[i].Temp.ADDMode == 3)
                {
                    T[i] += dT;
                    if(T[i] >= 1.0f)//1S
                    {			
                        if(Work_Num[i].Time.Rel)
                            Work_Num[i].Time.Rel--;//控制时间--
                        if(Work_Num[i].Time.Rel == 0)
                        {
                            Work_Num[i].Speed.ADDMode = 2;
                            Work_Num[i].Motor_Stop = 1;//电机停止
                            Beep_Flash = 5;//响5下
                        }
                        T[i] = 0;//周期清零
                    }
                }
            }
            else
            {
                if(Work_Num[i].Time.Rel > 0)
                {
                    T[i] += dT;
                    if(T[i] >= 1.0f)//1S
                    {			
                        if(Work_Num[i].Time.Rel)
                            Work_Num[i].Time.Rel--;//控制时间--
                        if(Work_Num[i].Time.Rel == 0)
                        {
                            Work_Num[i].Speed.ADDMode = 2;
                            Work_Num[i].Motor_Stop = 1;//电机停止
                            Beep_Flash = 5;//响5下
                        }
                        T[i] = 0;//周期清零
                    }
                }
            }
        }
    }
}

/**
 * @brief 定时任务
 * 
 */
void Time_Task(void *p)
{
    TickType_t xLastWakeTime;//刚开始唤醒的时间
    xLastWakeTime = xTaskGetTickCount ();
    
    while(1)
    {
        Cheak_TimeDown(0.1f);
        vTaskDelayUntil(&xLastWakeTime, 100);
    }
}

