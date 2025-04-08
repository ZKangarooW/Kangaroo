#include "Ctrl_Scheduler.h"

/**********宏定义************/
#define Buzzer_Stack_Depth 128//任务堆栈的堆栈
#define Buzzer_Task_Priority 9//任务执行的优先级

#define Show_Stack_Depth 256//任务堆栈的堆栈
#define Show_Task_Priority 8//任务执行的优先级

#define EC11A_Stack_Depth 128//任务堆栈的堆栈
#define EC11A_Task_Priority 3//任务执行的优先级

#define PT1000_Stack_Depth 128//任务堆栈的堆栈
#define PT1000_Task_Priority 4//任务执行的优先级

#define Motor_Stack_Depth 128//任务堆栈的堆栈
#define Motor_Task_Priority 7//任务执行的优先级

#define Speed_Stack_Depth 128//任务堆栈的堆栈
#define Speed_Task_Priority 6//任务执行的优先级

/**********结构体************/
TaskHandle_t Buzzer_Task_Handler;//函数句柄
TaskHandle_t Show_Task_Handler;//函数句柄
TaskHandle_t EC11A_Task_Handler;//函数句柄
TaskHandle_t PT1000_Task_Handler;//函数句柄
TaskHandle_t Motor_Task_Handler;//函数句柄
TaskHandle_t Speed_Task_Handler;//函数句柄

/**
 * @brief 开始执行任务函数
 * 
 */
void Start_Task(void *p)
{
    /* 进入临界区 */
    taskENTER_CRITICAL();
    
    /* 创建测速任务 */
    xTaskCreate((TaskFunction_t) Speed_Task,
                (char *) "Speed_Task",
                (configSTACK_DEPTH_TYPE) Speed_Stack_Depth,
                (void *) NULL,
                (UBaseType_t) Speed_Task_Priority,
                (TaskHandle_t *)&Speed_Task_Handler);
                
    /* 创建电机任务 */
    xTaskCreate((TaskFunction_t) Motor_Task,
                (char *) "Motor_Task",
                (configSTACK_DEPTH_TYPE) Motor_Stack_Depth,
                (void *) NULL,
                (UBaseType_t) Motor_Task_Priority,
                (TaskHandle_t *)&Motor_Task_Handler);
                
    /* 创建显示任务 */
    xTaskCreate((TaskFunction_t) Show_Display,
                (char *) "Show_Display",
                (configSTACK_DEPTH_TYPE) Show_Stack_Depth,
                (void *) NULL,
                (UBaseType_t) Show_Task_Priority,
                (TaskHandle_t *)&Show_Task_Handler);
                
     /* 创建旋钮任务 */
    xTaskCreate((TaskFunction_t) EC11A_Task,
                (char *) "EC11A_Task",
                (configSTACK_DEPTH_TYPE) EC11A_Stack_Depth,
                (void *) NULL,
                (UBaseType_t) EC11A_Task_Priority,
                (TaskHandle_t *)&EC11A_Task_Handler);

    /* 创建蜂鸣器任务 */
    xTaskCreate((TaskFunction_t) Buzzer_Task,
                (char *) "Buzzer_Task",
                (configSTACK_DEPTH_TYPE) Buzzer_Stack_Depth,
                (void *) NULL,
                (UBaseType_t) Buzzer_Task_Priority,
                (TaskHandle_t *)&Buzzer_Task_Handler);

    /* 创建PT1000任务 */
    xTaskCreate((TaskFunction_t) PT1000_Task,
                (char *) "PT1000_Task",
                (configSTACK_DEPTH_TYPE) PT1000_Stack_Depth,
                (void *) NULL,
                (UBaseType_t) PT1000_Task_Priority,
                (TaskHandle_t *)&PT1000_Task_Handler);

    /* 启动任务只需要执行一次，用完就删 */
    vTaskDelete(NULL);
                
    /* 退出临界区 */
    taskEXIT_CRITICAL();
}
