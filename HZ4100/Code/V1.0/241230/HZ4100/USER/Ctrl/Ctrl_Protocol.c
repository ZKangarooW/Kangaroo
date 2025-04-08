#include "Ctrl_Protocol.h"

/**********结构体************/
_Data_Flag_ Data_Flag;//发送标志结构体

/**********全局变量声明******/
uint8_t Data_To_Send[10];//发送数据缓存

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

// 控制电机状态的函数
void setMotorStatus(uint8_t *byte1, uint8_t motorStatus, uint8_t direction) 
{
    // 设置电机开关状态 (bit 0)
    if (motorStatus == 1) {
        *byte1 |= 0x01;  // 将 bit 0 置为 1
    } else {
        *byte1 &= ~0x01; // 将 bit 0 置为 0
    }

    // 设置旋转方向 (bit 1)
    if (direction == 1) {
        *byte1 |= 0x02;  // 将 bit 1 置为 1
    } else {
        *byte1 &= ~0x02; // 将 bit 1 置为 0
    }
}

uint8_t motor_status;
/*
*****************************************************************
 * 函数原型：void Send_StartMotor(uint8_t Type, uint8_t SSI, uint16_t Sensor_Status, uint16_t Settings)
 * 功    能：发送电机的启动数据
 * 输    入: Status:0停止，1启动,CW:0:反转，1：正转， speed：转速
 * 参    数：uint8_t Status,uint8_t CW, uint16_t speed
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
    
    Data_To_Send[1] = _cnt - 3;//计算数据长度
    
    crc = app_CalcCRC8(Data_To_Send,_cnt);//crc校验
    
    Data_To_Send[_cnt++] = BYTE0(crc);
    
    Uart_Put_Buf(&huart1,Data_To_Send,_cnt);
}

/*
*****************************************************************
 * 函数原型：void Data_Exchange(float dT)
 * 功    能：Data_Exchange函数处理各种数据发送请求
 * 输    入：dT：运行周期
 * 参    数：float dT
*****************************************************************
*/
void Data_Exchange(float dT)
{
    if(Data_Flag.Send_Data)//发送开始数据
    {
        Send_StartMotor(Speed.Status,Speed.CW,Speed.Ctrl);
        Data_Flag.Send_Data = 0;//发送校验位时，确保不会发送其他的
    }

}
