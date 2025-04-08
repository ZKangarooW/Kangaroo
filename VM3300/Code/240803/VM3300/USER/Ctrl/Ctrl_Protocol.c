#include "Ctrl_Protocol.h"

/**********结构体************/
Data_Flag_ Data_Flag;//发送标志结构体

/**********全局变量声明******/
uint8_t Data_To_Send[50];//发送数据缓存

/*
*****************************************************************
 * 函数原型：void Rc_SendData_PC(uint8_t *dataToSend, uint8_t length)
 * 功    能：遥控器发送数据到PC
 * 输    入：dataToSend 发送的数据  length 数据长度
 * 参    数：uint8_t *dataToSend, uint8_t length
*****************************************************************
*/
void Rc_SendData_PC(uint8_t *dataToSend, uint8_t length)
{
    Uart_Put_Buf(&huart1, dataToSend, length);
}

/*
*****************************************************************
 * 函数原型：void Fly_Send_Senser(int16_t ACC_X, int16_t ACC_Y, int16_t ACC_Z,
								  int16_t GYRO_X, int16_t GYRO_Y, int16_t GYRO_Z,
								  int16_t MAG_X, int16_t MAG_Y, int16_t MAG_Z)
 * 功    能：发送飞机传感器数据
 * 输    入：ACC_X：加速度的X值 -->实际速度
			 ACC_Y：加速度的Y值 -->实际温度
			 ACC_Z：加速度的Z值 -->实际时间
			 GYRO_X：角加速度的X值 -->设定速度
			 GYRO_Y：角加速度的Y值 -->设定温度
			 GYRO_Z：角加速度的Z值 -->设定时间
			 MAG_X：磁力计的X值
			 MAG_Y：磁力计的Y值
			 MAG_Z：磁力计的Z值
 * 参	数：int16_t ACC_X, int16_t ACC_Y, int16_t ACC_Z,
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
 * 函数原型：void Rc_Data_Exchange(float dT)
 * 功    能：Data_Exchange函数处理各种数据发送请求
 * 输    入：dT：运行周期
 * 参    数：float dT
*****************************************************************
*/
void Rc_Data_Exchange(float dT)
{
   Fly_Send_Senser(Speed.Rel,0,0,
					Speed.Ctrl,0,0,
					0,0,0);
}
