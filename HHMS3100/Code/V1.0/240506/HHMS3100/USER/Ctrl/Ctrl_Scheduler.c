#include "Ctrl_Scheduler.h"

/**********�궨��************/
#define Buzzer_Stack_Depth 128//�����ջ�Ķ�ջ
#define Buzzer_Task_Priority 1//����ִ�е����ȼ�

#define Show_Stack_Depth 256//�����ջ�Ķ�ջ
#define Show_Task_Priority 2//����ִ�е����ȼ�

#define Time_Stack_Depth 128//�����ջ�Ķ�ջ
#define Time_Task_Priority 3//����ִ�е����ȼ�

#define EC11A_Stack_Depth 128//�����ջ�Ķ�ջ
#define EC11A_Task_Priority 4//����ִ�е����ȼ�

/**********�ṹ��************/
TaskHandle_t Buzzer_Task_Handler;//�������
TaskHandle_t Show_Task_Handler;//�������
TaskHandle_t Time_Task_Handler;//�������
TaskHandle_t EC11A_Task_Handler;//�������

/**
 * @brief ��ʱ
 * 
 */
void Time_Task(void *p)
{
   TickType_t xLastWakeTime;//�տ�ʼ���ѵ�ʱ��f
   xLastWakeTime = xTaskGetTickCount ();
    while(1)
    {
        Time[0].Display_Rel += 1;
        printf("New Time:%d S\r\n",Time[0].Display_Rel);
       vTaskDelayUntil(&xLastWakeTime, 1000);
    }
}

/**
 * @brief ��ʼִ��������
 * 
 */
void Start_Task(void *p)
{
    /* �����ٽ��� */
    taskENTER_CRITICAL();
    
    /* ������ʾ���� */
    xTaskCreate((TaskFunction_t) Show_Display,
                (char *) "Show_Display",
                (configSTACK_DEPTH_TYPE) EC11A_Stack_Depth,
                (void *) NULL,
                (UBaseType_t) EC11A_Task_Priority,
                (TaskHandle_t *)&EC11A_Task_Handler);

     /* ������ť���� */
    xTaskCreate((TaskFunction_t) EC11A_Task,
                (char *) "EC11A_Task",
                (configSTACK_DEPTH_TYPE) Show_Stack_Depth,
                (void *) NULL,
                (UBaseType_t) Show_Task_Priority,
                (TaskHandle_t *)&Buzzer_Task_Handler);

    /* �������������� */
    xTaskCreate((TaskFunction_t) Buzzer_Task,
                (char *) "Buzzer_Task",
                (configSTACK_DEPTH_TYPE) Buzzer_Stack_Depth,
                (void *) NULL,
                (UBaseType_t) Buzzer_Task_Priority,
                (TaskHandle_t *)&Buzzer_Task_Handler);

    xTaskCreate((TaskFunction_t) Time_Task,
                (char *) "Time_Task",
                (configSTACK_DEPTH_TYPE) Time_Stack_Depth,
                (void *) NULL,
                (UBaseType_t) Time_Task_Priority,
                (TaskHandle_t *)&Time_Task_Handler);
             
    /* ��������ֻ��Ҫִ��һ�Σ������ɾ */
    vTaskDelete(NULL);
                
    /* �˳��ٽ��� */
    taskEXIT_CRITICAL();
}
