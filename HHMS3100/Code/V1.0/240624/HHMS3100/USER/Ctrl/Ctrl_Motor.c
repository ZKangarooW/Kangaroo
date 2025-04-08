#include "Ctrl_Motor.h"

/**
 * @brief 电机任务
 * 
 */
void Motor_Task(void *p)
{
    TickType_t xLastWakeTime;//刚开始唤醒的时间
    xLastWakeTime = xTaskGetTickCount ();

    while(1)
    {
//        PWM0 = 0;
//        PWM1 = 0;
//        PWM2 = 0;
//        PWM3 = 0;
        vTaskDelayUntil(&xLastWakeTime, 50);
    }
}
