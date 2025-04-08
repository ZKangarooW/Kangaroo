#ifndef __DRV_INFRARED_H__
#define __DRV_INFRARED_H__

#include "include.h"

/**********�궨��************/
#define IR1_IN HAL_GPIO_ReadPin(IR1_GPIO_Port, IR1_Pin)
#define IR2_IN HAL_GPIO_ReadPin(IR2_GPIO_Port, IR2_Pin)

#define Infrared_Send1 htim3.Instance->CCR1
#define Infrared_Send2 htim3.Instance->CCR2

#define CARRIER_38KHz(N) __HAL_TIM_SET_COMPARE(&htim3, N == 1 ? TIM_CHANNEL_1 : TIM_CHANNEL_2, 52)//����PWMռ�ձ�����֮һ
#define NO_CARRIER(N)    __HAL_TIM_SET_COMPARE(&htim3, N == 1 ? TIM_CHANNEL_1 : TIM_CHANNEL_2, 0)
#define NEC_HEAD		(uint16_t)(4500) //������
#define NEC_ZERO 		(uint16_t)(560)  //����0
#define NEC_ONE			(uint16_t)(1680) //����1
#define NEC_CONTINUE 	(uint16_t)(2100) //������������
 
#define NEC_HEAD_MIN (uint16_t)(NEC_HEAD*1.0f) //4500
#define NEC_HEAD_MAX (uint16_t)(NEC_HEAD*1.4f) //6300
 
#define NEC_ZERO_MIN (uint16_t)(NEC_ZERO*0.7f)
#define NEC_ZERO_MAX (uint16_t)(NEC_ZERO*1.5f)
 
#define NEC_ONE_MIN (uint16_t)(NEC_ONE*0.7f)
#define NEC_ONE_MAX (uint16_t)(NEC_ONE*1.3f)

#define NEC_CONTINUE_MIN (uint16_t)(NEC_CONTINUE*1.0f)
#define NEC_CONTINUE_MAX (uint16_t)(NEC_CONTINUE*1.3f)

#define REMOTE_ID 0x00//����ң��ʶ����(ID)

/**********�ṹ��************/
typedef struct
{
    int Edge;//0Ϊ���������أ�1Ϊ�����½���
    int Cnt;//����˼������
    uint32_t  t1,t2,T;
    float Distance;
    
	uint8_t Someone;//�ж��Ƿ������ڣ�1������ 0��û��
	float Someone_Time;//��һ��ʱ������û�˼���
    float SSI_CNT;
    float SSI;
} _Infrared_;
extern _Infrared_ Infrared[2];

/**********ȫ�ֱ�������*******/
/**********ȫ�ֺ���**********/

void Drv_Infrared_Init(void);
void Infrared_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void Infrared_IC_CaptureCallback(TIM_HandleTypeDef *htim);
void NEC_Send(uint8_t val);
void Check_Infrared(float dT);
void Check_Infrared_Rec(float dT);

#endif
