#include "Drv_LED.h"

/**********ȫ�ֱ���**********/

/*
*****************************************************************
 * ����ԭ�ͣ�void Drv_LED_Init(void)
 * ��    �ܣ�LED������ʼ��
*****************************************************************
*/
void Drv_LED_Init(void)
{
    GPIO_SET_MUX_MODE(P00CFG, GPIO_MUX_GPIO);
    GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_0);
    
    GPIO_SET_MUX_MODE(P02CFG, GPIO_MUX_GPIO);
    GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_2);
    
    LED1_OFF;//�رյ�
    LED2_OFF;//�رյ�
}
