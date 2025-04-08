#include "Ctrl_Protocol.h"

/**********�ṹ��************/
_Data_Flag_ Data_Flag;//���ͱ�־�ṹ��

/**********ȫ�ֱ�������******/
uint8_t Data_To_Send[10];//�������ݻ���

uint8_t app_CalcCRC8(uint8_t *ptr, uint8_t len) {
    static uint8_t crc;
    static uint8_t i;
    crc = 0;
    while (len--) {
        crc ^= *ptr++;
        for (i = 0; i < 8; i++) {
            if (crc & 0x01)
                crc = (crc >> 1) ^ 0x8C;
            else
                crc >>= 1;
    }
  }
  return crc;
}

// ���Ƶ��״̬�ĺ���
void setMotorStatus(uint8_t *byte1, uint8_t motorStatus, uint8_t direction) 
{
    // ���õ������״̬ (bit 0)
    if (motorStatus == 1) {
        *byte1 |= 0x01;  // �� bit 0 ��Ϊ 1
    } else {
        *byte1 &= ~0x01; // �� bit 0 ��Ϊ 0
    }

    // ������ת���� (bit 1)
    if (direction == 1) {
        *byte1 |= 0x02;  // �� bit 1 ��Ϊ 1
    } else {
        *byte1 &= ~0x02; // �� bit 1 ��Ϊ 0
    }
}

uint8_t motor_status;
/*
*****************************************************************
 * ����ԭ�ͣ�void Send_StartMotor(uint8_t Type, uint8_t SSI, uint16_t Sensor_Status, uint16_t Settings)
 * ��    �ܣ����͵������������
 * ��    ��: Status:0ֹͣ��1����,CW:0:��ת��1����ת�� speed��ת��
 * ��    ����uint8_t Status,uint8_t CW, uint16_t speed
*****************************************************************
*/
void Send_StartMotor(uint8_t Status,uint8_t CW, uint16_t speed)
{
    uint8_t _cnt = 0;
    uint8_t crc;

    Data_To_Send[_cnt++] = 0xA5;
    Data_To_Send[_cnt++] = 0;

    Data_To_Send[_cnt++] = 0xF2;
    
    setMotorStatus(&motor_status,Status,CW);
    
    Data_To_Send[_cnt++] = BYTE0(motor_status);

    Data_To_Send[_cnt++] = BYTE1(speed);
    Data_To_Send[_cnt++] = BYTE0(speed);
    
    Data_To_Send[1] = _cnt - 3;//�������ݳ���
    
    crc = app_CalcCRC8(Data_To_Send,_cnt);//crcУ��
    
    Data_To_Send[_cnt++] = BYTE0(crc);
    
    Uart_Put_Buf(&huart1,Data_To_Send,_cnt);
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Data_Exchange(float dT)
 * ��    �ܣ�Data_Exchange��������������ݷ�������
 * ��    �룺dT����������
 * ��    ����float dT
*****************************************************************
*/
void Data_Exchange(float dT)
{
    if(Data_Flag.Send_Data)//���Ϳ�ʼ����
    {
        Send_StartMotor(Speed.Status,Speed.CW,Speed.Ctrl);
        Data_Flag.Send_Data = 0;//����У��λʱ��ȷ�����ᷢ��������
    }

}
