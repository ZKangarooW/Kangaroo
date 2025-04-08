#include "System_Init.h"

/**
 * @brief ϵͳ������ʼ��
 *
 */
void System_Init(void)
{
    /**********ϵͳ��ʼ����ʼ**********/
	sys.Init_ok = 0;
	
	/**********������ʼ��***************/
	Drv_Touch_Init();
	
	/**********�����ʼ��***************/
	Drv_Motor_Init();
	
	/**********���PID��ʼ��***********/
	Motor_PID();
	
//	Speed.Ctrl = 200;
//	SCD_IR_Decode_Init();
	
	/**********������������************/
	Beep_Time = 0.1f;
	
	/**********ϵͳ��ʼ���ɹ�**********/
	sys.Init_ok = 1;
}
