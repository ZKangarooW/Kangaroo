#include "Drv_Sleep.h"

/**********ȫ�ֱ���**********/

/*
*****************************************************************
 * ����ԭ�ͣ�void Drv_Sleep_Init(void)
 * ��    �ܣ�Sleep������ʼ��
*****************************************************************
*/
void Drv_Sleep_Init(void)
{
    /*
	(1)����EXTINT����
	*/
	EXTINT_ConfigInt(EXTINT1, EXTINT_TRIG_FALLING);		//INT1 �½��ش����ж�
	/*
	(2)����EXTINT IO��
	*/	
    GPIO_SET_MUX_MODE(P07CFG, GPIO_MUX_GPIO);
    GPIO_ENABLE_INPUT(P0TRIS, GPIO_PIN_7);
	GPIO_ENABLE_UP(P0UP, GPIO_PIN_7);				//����P07����
	GPIO_SET_PS_MODE(PS_INT1, GPIO_P07_MUX_INT1);			//����ΪINT1 ���빦��
	/*
	(3)����EXTINT�ж�
	*/		
	EXTINT_EnableInt(EXTINT1);
	IRQ_SET_PRIORITY(IRQ_INT1, IRQ_PRIORITY_HIGH);
	IRQ_ALL_ENABLE();							 //�������ж�
    SYS_EnableWakeUp();//congfig�����������߻��ѵȴ�ʱ��(WAKEUP_WAITTIME)
}


/*
*****************************************************************
 * ����ԭ�ͣ�void Check_Sleep(float dT)
 * ��    �ܣ����ʱ�䣬��������ģʽ
*****************************************************************
*/
void Check_Sleep(float dT)
{
    static float T;
    if(sys.Run_Status)
    {
        T = 0;
    }
    else
    {
        T += dT;
        if(T>10.0f)
        {
            T = 0;
            LED1_OFF;//�رյ�
            LED2_OFF;//�رյ�
            SYS_EnterStop();
        }
    }
}
