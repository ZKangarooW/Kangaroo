#ifndef __CTRL_PROTOCOL_H__
#define	__CTRL_PROTOCOL_H__

#include "include.h"

/**********�궨��************/
/**********�ṹ��************/
typedef struct
{
	uint8_t Send_Check;//У���־λ
	uint8_t Send_Flag;//���ͱ�־λ
}Data_Flag_;
extern Data_Flag_ Data_Flag;//���ͱ�־�ṹ��

/**********ȫ�ֱ�������******/
extern uint8_t Data_To_Send[50];//�������ݻ���

/**********ȫ�ֺ���**********/
void Rc_SendData_Fly(uint8_t *dataToSend, uint8_t length);//ң�����������ݵ��ɻ�
void Rc_SendData_PC(uint8_t *dataToSend, uint8_t length);//ң�����������ݵ�PC
void Rc_Data_Exchange(float dT);//Data_Exchange��������������ݷ�������
void Data_Receive_Anl(uint8_t *data_buf,uint8_t num);//���ݽ��ܷ���

#endif
