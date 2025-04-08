#ifndef __DRV_INFRARED_H__
#define __DRV_INFRARED_H__

#include "include.h"

/**********�궨��************/
#define IR1_IN HAL_GPIO_ReadPin(IR1_GPIO_Port, IR1_Pin)
#define IR2_IN HAL_GPIO_ReadPin(IR2_GPIO_Port, IR2_Pin)

#define Infrared_Send1 htim3.Instance->CCR1
#define Infrared_Send2 htim3.Instance->CCR2

/**********�ṹ��************/
typedef struct
{
	uint8_t IRSta;//����״̬��[0:3]�����������[4]����������Ƿ��Ѿ�������,[5]������[6]�õ���һ��������ȫ����Ϣ,[7]�յ����������־
	uint16_t Dval;//�ߵ�ƽ��������ֵ�����ݴ��жϸߵ͵�ƽ��ʱ��
	uint8_t Someone;//�ж��Ƿ������ڣ�1������ 0��û��
	float Someone_Time;//��һ��ʱ������û�˼���
} _Infrared_;
extern _Infrared_ Infrared[2];

/**********ȫ�ֱ�������*******/
/**********ȫ�ֺ���**********/

void Drv_Infrared_Init(void);
void Check_Infrared(float dT);
void Infrared_TIM_Interrupt(TIM_HandleTypeDef *htim);
void Infrared_IC_CaptureCallback(TIM_HandleTypeDef *htim);

#endif
