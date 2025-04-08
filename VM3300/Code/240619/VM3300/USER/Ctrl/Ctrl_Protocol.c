#include "Ctrl_Protocol.h"

/**********�ṹ��************/
Data_Flag_ Data_Flag;//���ͱ�־�ṹ��

/**********ȫ�ֱ�������******/
uint8_t Data_To_Send[50];//�������ݻ���

/*
*****************************************************************
 * ����ԭ�ͣ�void Rc_SendData_PC(uint8_t *dataToSend, uint8_t length)
 * ��    �ܣ�ң�����������ݵ�PC
 * ��    �룺dataToSend ���͵�����  length ���ݳ���
 * ��    ����uint8_t *dataToSend, uint8_t length
*****************************************************************
*/
void Rc_SendData_PC(uint8_t *dataToSend, uint8_t length)
{
    Uart_Put_Buf(&huart1, dataToSend, length);
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Fly_Send_Senser(int16_t ACC_X, int16_t ACC_Y, int16_t ACC_Z,
								  int16_t GYRO_X, int16_t GYRO_Y, int16_t GYRO_Z,
								  int16_t MAG_X, int16_t MAG_Y, int16_t MAG_Z)
 * ��    �ܣ����ͷɻ�����������
 * ��    �룺ACC_X�����ٶȵ�Xֵ -->ʵ���ٶ�
			 ACC_Y�����ٶȵ�Yֵ -->ʵ���¶�
			 ACC_Z�����ٶȵ�Zֵ -->ʵ��ʱ��
			 GYRO_X���Ǽ��ٶȵ�Xֵ -->�趨�ٶ�
			 GYRO_Y���Ǽ��ٶȵ�Yֵ -->�趨�¶�
			 GYRO_Z���Ǽ��ٶȵ�Zֵ -->�趨ʱ��
			 MAG_X�������Ƶ�Xֵ
			 MAG_Y�������Ƶ�Yֵ
			 MAG_Z�������Ƶ�Zֵ
 * ��	����int16_t ACC_X, int16_t ACC_Y, int16_t ACC_Z,
            int16_t GYRO_X, int16_t GYRO_Y, int16_t GYRO_Z,
            int16_t MAG_X, int16_t MAG_Y, int16_t MAG_Z
*****************************************************************
*/
void Fly_Send_Senser(int16_t ACC_X, int16_t ACC_Y, int16_t ACC_Z,
                     int16_t GYRO_X, int16_t GYRO_Y, int16_t GYRO_Z,
                     int16_t MAG_X, int16_t MAG_Y, int16_t MAG_Z)
{
    uint8_t _cnt = 0;

    Data_To_Send[_cnt++] = 0xAA;
    Data_To_Send[_cnt++] = 0xAA;
    Data_To_Send[_cnt++] = 0x02;
    Data_To_Send[_cnt++] = 0;

    Data_To_Send[_cnt++] = BYTE1(ACC_X);
    Data_To_Send[_cnt++] = BYTE0(ACC_X);

    Data_To_Send[_cnt++] = BYTE1(ACC_Y);
    Data_To_Send[_cnt++] = BYTE0(ACC_Y);

    Data_To_Send[_cnt++] = BYTE1(ACC_Z);
    Data_To_Send[_cnt++] = BYTE0(ACC_Z);

    Data_To_Send[_cnt++] = BYTE1(GYRO_X);
    Data_To_Send[_cnt++] = BYTE0(GYRO_X);

    Data_To_Send[_cnt++] = BYTE1(GYRO_Y);
    Data_To_Send[_cnt++] = BYTE0(GYRO_Y);

    Data_To_Send[_cnt++] = BYTE1(GYRO_Z);
    Data_To_Send[_cnt++] = BYTE0(GYRO_Z);

    Data_To_Send[_cnt++] = BYTE1(MAG_X);
    Data_To_Send[_cnt++] = BYTE0(MAG_X);

    Data_To_Send[_cnt++] = BYTE1(MAG_Y);
    Data_To_Send[_cnt++] = BYTE0(MAG_Y);

    Data_To_Send[_cnt++] = BYTE1(MAG_Z);
    Data_To_Send[_cnt++] = BYTE0(MAG_Z);

    Data_To_Send[3] = _cnt - 4;

    uint8_t sum = 0;
    for(uint8_t i = 0; i < _cnt; i++)
        sum += Data_To_Send[i];
    Data_To_Send[_cnt++] = sum;

    Rc_SendData_PC(Data_To_Send, _cnt);
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Rc_Data_Exchange(float dT)
 * ��    �ܣ�Data_Exchange��������������ݷ�������
 * ��    �룺dT����������
 * ��    ����float dT
*****************************************************************
*/
void Rc_Data_Exchange(float dT)
{
   Fly_Send_Senser(Speed.Rel,0,0,
					Speed.Ctrl,0,0,
					0,0,0);
}
