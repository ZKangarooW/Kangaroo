#include "Ctrl_Scheduler.h"

/**********�궨��************/
#define Buzzer_Stack_Depth 128//�����ջ�Ķ�ջ
#define Buzzer_Task_Priority 9//����ִ�е����ȼ�

#define Show_Stack_Depth 256//�����ջ�Ķ�ջ
#define Show_Task_Priority 8//����ִ�е����ȼ�

#define EC11A_Stack_Depth 128//�����ջ�Ķ�ջ
#define EC11A_Task_Priority 3//����ִ�е����ȼ�

#define PT1000_Stack_Depth 128//�����ջ�Ķ�ջ
#define PT1000_Task_Priority 4//����ִ�е����ȼ�

#define Motor_Stack_Depth 128//�����ջ�Ķ�ջ
#define Motor_Task_Priority 7//����ִ�е����ȼ�

#define Speed_Stack_Depth 128//�����ջ�Ķ�ջ
#define Speed_Task_Priority 6//����ִ�е����ȼ�

/**********�ṹ��************/
TaskHandle_t Buzzer_Task_Handler;//�������
TaskHandle_t Show_Task_Handler;//�������
TaskHandle_t EC11A_Task_Handler;//�������
TaskHandle_t PT1000_Task_Handler;//�������
TaskHandle_t Motor_Task_Handler;//�������
TaskHandle_t Speed_Task_Handler;//�������

/**
 * @brief ��ʼִ��������
 * 
 */
void Start_Task(void *p)
{
    /* �����ٽ��� */
    taskENTER_CRITICAL();
    
    /* ������������ */
    xTaskCreate((TaskFunction_t) Speed_Task,
                (char *) "Speed_Task",
                (configSTACK_DEPTH_TYPE) Speed_Stack_Depth,
                (void *) NULL,
                (UBaseType_t) Speed_Task_Priority,
                (TaskHandle_t *)&Speed_Task_Handler);
                
    /* ����������� */
    xTaskCreate((TaskFunction_t) Motor_Task,
                (char *) "Motor_Task",
                (configSTACK_DEPTH_TYPE) Motor_Stack_Depth,
                (void *) NULL,
                (UBaseType_t) Motor_Task_Priority,
                (TaskHandle_t *)&Motor_Task_Handler);
                
    /* ������ʾ���� */
    xTaskCreate((TaskFunction_t) Show_Display,
                (char *) "Show_Display",
                (configSTACK_DEPTH_TYPE) Show_Stack_Depth,
                (void *) NULL,
                (UBaseType_t) Show_Task_Priority,
                (TaskHandle_t *)&Show_Task_Handler);
                
     /* ������ť���� */
    xTaskCreate((TaskFunction_t) EC11A_Task,
                (char *) "EC11A_Task",
                (configSTACK_DEPTH_TYPE) EC11A_Stack_Depth,
                (void *) NULL,
                (UBaseType_t) EC11A_Task_Priority,
                (TaskHandle_t *)&EC11A_Task_Handler);

    /* �������������� */
    xTaskCreate((TaskFunction_t) Buzzer_Task,
                (char *) "Buzzer_Task",
                (configSTACK_DEPTH_TYPE) Buzzer_Stack_Depth,
                (void *) NULL,
                (UBaseType_t) Buzzer_Task_Priority,
                (TaskHandle_t *)&Buzzer_Task_Handler);

    /* ����PT1000���� */
    xTaskCreate((TaskFunction_t) PT1000_Task,
                (char *) "PT1000_Task",
                (configSTACK_DEPTH_TYPE) PT1000_Stack_Depth,
                (void *) NULL,
                (UBaseType_t) PT1000_Task_Priority,
                (TaskHandle_t *)&PT1000_Task_Handler);

    /* ��������ֻ��Ҫִ��һ�Σ������ɾ */
    vTaskDelete(NULL);
                
    /* �˳��ٽ��� */
    taskEXIT_CRITICAL();
}
