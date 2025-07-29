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
    
    /**********参数初始化**************/
    Param_Read();//读取参数
    
    /**********EC11A初始化***********/
    EC11A_Init();
    
    /**********编码器初始化***********/
    Encoder_Init();
    
    /**********加热初始化**************/
	HEAT_Init();
    
    /**********电机初始化***********/
    Drv_Motor_Init();
    
    /**********LCD初始化*************/
    Lcd_Init();
    
    /**********初始化ADC_DMA***********/
    ADCDMA_Init();
    
    /**********开机蜂鸣器响***********/
    Beep_Time = 0.1f;

    /**********温度校准初始化*************/
    Calibration_Init();
    
    xTaskCreate((TaskFunction_t) Start_Task,
                (char *) "Start_Task",
                (configSTACK_DEPTH_TYPE) Start_Stack_Depth,
                (void *) NULL,
                (UBaseType_t) Start_Task_Priority,
                (TaskHandle_t *)&Start_Task_Handler);

    /**********启动调度器********/
    vTaskStartScheduler();
}
