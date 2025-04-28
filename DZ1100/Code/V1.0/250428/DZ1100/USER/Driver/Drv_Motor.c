#include "Drv_Motor.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void Drv_Motor_Init(void)
 * ��    �ܣ�Motor������ʼ��
*****************************************************************
*/
void Drv_Motor_Init(void)
{
    GPIO_SET_MUX_MODE(P11CFG, GPIO_MUX_GPIO);
    GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_1);
    GPIO_SET_MUX_MODE(P12CFG, GPIO_MUX_GPIO);
    GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_2);
    GPIO_SET_MUX_MODE(P13CFG, GPIO_MUX_GPIO);
    GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_3);
    
    Motor_Vcc_ON;//�رյ��
    Motor_Gnd_OFF;//�رյ��
    Motor_En_OFF;//�رյ��
}


void Motor_BrakeCheck(float dT)
{
    static float T;
    float T1;
    if(sys.Motor_Brake)
    {
        T += dT;
        if(sys.sys_time< 5.0f)
        {
            T1 = 1.0f;
        }
        else if(sys.sys_time< 9.0f)
        {
            T1 = 1.5f;
        }
        else
        {
            T1 = 2.1f;
        }
        
        if(T <=T1)
        {
            Motor_Vcc_OFF;//�رյ��
            Motor_Gnd_ON;//�رյ��
            Motor_En_ON;//�رյ��
        }
        else
        {
            sys.Run_Status = 0;//����ϵͳ
            sys.Motor_Brake = 0;
            Motor_Vcc_ON;//�رյ��
            Motor_Gnd_ON;//�رյ��
            Motor_En_ON;//�رյ��
            T = 0;
        }
    }
}
