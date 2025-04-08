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
    
    /**********������ʼ��**************/
    Param_Read();//��ȡ����
    
    /**********EC11A��ʼ��***********/
    EC11A_Init();
    
    /**********��������ʼ��***********/
    Encoder_Init();
    
    /**********���ȳ�ʼ��**************/
	HEAT_Init();
    
    /**********�����ʼ��***********/
    Drv_Motor_Init();
    
    /**********LCD��ʼ��*************/
    Lcd_Init();
    
    /**********��ʼ��ADC_DMA***********/
    ADCDMA_Init();
    
    /**********������������***********/
    Beep_Time = 0.1f;

    /**********�¶�У׼��ʼ��*************/
    Calibration_Init();
    
    xTaskCreate((TaskFunction_t) Start_Task,
                (char *) "Start_Task",
                (configSTACK_DEPTH_TYPE) Start_Stack_Depth,
                (void *) NULL,
                (UBaseType_t) Start_Task_Priority,
                (TaskHandle_t *)&Start_Task_Handler);

    /**********����������********/
    vTaskStartScheduler();
}
