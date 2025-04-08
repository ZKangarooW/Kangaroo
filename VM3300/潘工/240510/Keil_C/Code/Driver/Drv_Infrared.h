#ifndef __DRV_INFRARED_H__
#define __DRV_INFRARED_H__

#include "include.h"

/**********�궨��************/

#define CARRIER_38KHz() PWM_IndependentModeConfig(PWM06,280);//����PWMռ�ձ�.��ʼ������27us��
#define NO_CARRIER()	PWM_IndependentModeConfig(PWM06,0);//1050��ѹ3.2V

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
void Check_Infrared(float dT);
void Infrared_TIM_Interrupt(void);
void NEC_Send(uint8_t addr, uint8_t value, uint8_t cnt);

#endif
