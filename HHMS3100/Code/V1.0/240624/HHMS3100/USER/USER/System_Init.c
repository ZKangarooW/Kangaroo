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
    
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);//加热盘3工位
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, 0);//加热盘1工位
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 0); //加热盘4工位
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 0); //加热盘2工位
  
    
    /**********参数初始化**************/
    Param_Read();//读取参数
    
    /**********EC11A初始化***********/
    EC11A_Init();
    
    /**********编码器初始化***********/
    Encoder_Init();
    
    /**********电机初始化***********/
    Drv_Motor_Init();
    
    /**********LCD初始化*************/
    Lcd_Init();
    
    /**********初始化ADC_DMA***********/
    ADCDMA_Init();
    
    /**********开机蜂鸣器响***********/
    Beep_Time = 0.1f;
    
    xTaskCreate((TaskFunction_t) Start_Task,
                (char *) "Start_Task",
                (configSTACK_DEPTH_TYPE) Start_Stack_Depth,
                (void *) NULL,
                (UBaseType_t) Start_Task_Priority,
                (TaskHandle_t *)&Start_Task_Handler);

    /**********启动调度器********/
    vTaskStartScheduler();
}
