#include "Ctrl_Motor.h"

/**
 * @brief 电机任务
 * 
 */
void Motor_Task(void *p)
{
    TickType_t xLastWakeTime;//刚开始唤醒的时间
    xLastWakeTime = xTaskGetTickCount ();

    /**********电机初始化***********/
    Drv_Motor_Init();
    PWM0 = 80;
    PWM1 = 80;
    PWM2 = 80;
    PWM3 = 80;
    
    while(1)
    {

        vTaskDelayUntil(&xLastWakeTime, 50);
    }
}
