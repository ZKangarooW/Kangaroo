#include "System_Init.h"

#define Start_Stack_Depth 128//�����ջ�Ķ�ջ
#define Start_Task_Priority 1//����ִ�е����ȼ�
TaskHandle_t Start_Task_Handler;//�������

/**
 * @brief ϵͳ������ʼ��
 *
 */
void System_Init(void)
{
    /**********������������******/
    SEGGER_SYSVIEW_Conf();
    
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 1); // �����ѹ��2.86V
    
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);//������3��λ
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, 0);//������1��λ
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 0); //������4��λ
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 0); //������2��λ

    xTaskCreate((TaskFunction_t) Start_Task,
                (char *) "Start_Task",
                (configSTACK_DEPTH_TYPE) Start_Stack_Depth,
                (void *) NULL,
                (UBaseType_t) Start_Task_Priority,
                (TaskHandle_t *)&Start_Task_Handler);

    /**********����������********/
    vTaskStartScheduler();
}
