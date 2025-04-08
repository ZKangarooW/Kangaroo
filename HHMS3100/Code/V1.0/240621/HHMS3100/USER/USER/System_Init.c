#include "System_Init.h"

#define Start_Stack_Depth 128//任务堆栈的堆栈
#define Start_Task_Priority 1//任务执行的优先级
TaskHandle_t Start_Task_Handler;//函数句柄

/**
 * @brief 系统驱动初始化
 *
 */
void System_Init(void)
{
    /**********创建启动任务******/
    SEGGER_SYSVIEW_Conf();
    
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 1); // 背光电压，2.86V
    
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);//加热盘3工位
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, 0);//加热盘1工位
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 0); //加热盘4工位
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 0); //加热盘2工位

    xTaskCreate((TaskFunction_t) Start_Task,
                (char *) "Start_Task",
                (configSTACK_DEPTH_TYPE) Start_Stack_Depth,
                (void *) NULL,
                (UBaseType_t) Start_Task_Priority,
                (TaskHandle_t *)&Start_Task_Handler);

    /**********启动调度器********/
    vTaskStartScheduler();
}
