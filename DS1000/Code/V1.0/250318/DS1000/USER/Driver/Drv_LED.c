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
    GPIO_SET_MUX_MODE(P05CFG, GPIO_MUX_GPIO);
    GPIO_ENABLE_OUTPUT(P0TRIS, GPIO_PIN_5);
    LED_ON;//�򿪵�
}
