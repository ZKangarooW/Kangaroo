//************************************************************
//  Copyright (c) 深圳市赛元微电子股份有限公司
//	文件名称: 		sc95f_USCI4.h
//	作者:
//	模块功能: 		USCI4固件库函数头文件
// 	最后更正日期:	2024年1月18日
// 	版本:				V1.0002
// 说明:				该文件仅适用于SC95F系列芯片
//*************************************************************

#ifndef _sc95f_USCI4_H_
#define _sc95f_USCI4_H_

#include "sc95f.h"

#define USCI4_UART_BaudRate_FsysDIV12 0X00 //仅模式0可用，串行端口在系统时钟的1/12下运行
#define USCI4_UART_BaudRate_FsysDIV4 0X01  //仅模式0可用，串行端口在系统时钟的1/4下运行

typedef enum
{
  USCI4_Mode_SPI = (uint8_t)0x01, //SPI
  USCI4_Mode_TWI = (uint8_t)0x02, //TWI
  USCI4_Mode_UART = (uint8_t)0x03 //UART
} USCI4_CommunicationMode_TypeDef;

typedef enum
{
  USCI4_SPI_FIRSTBIT_MSB = (uint8_t)0x00, //MSB优先发送
  USCI4_SPI_FIRSTBIT_LSB = (uint8_t)0x04  //LSB优先发送
} USCI4_SPI_FirstBit_TypeDef;

typedef enum
{
  USCI4_SPI_BAUDRATEPRESCALER_1 = (uint8_t)0x00,  //SPI时钟速率为系统时钟除以1
  USCI4_SPI_BAUDRATEPRESCALER_2 = (uint8_t)0x01,  //SPI时钟速率为系统时钟除以2
  USCI4_SPI_BAUDRATEPRESCALER_4 = (uint8_t)0x02,  //SPI时钟速率为系统时钟除以4
  USCI4_SPI_BAUDRATEPRESCALER_8 = (uint8_t)0x03,  //SPI时钟速率为系统时钟除以8
  USCI4_SPI_BAUDRATEPRESCALER_16 = (uint8_t)0x04, //SPI时钟速率为系统时钟除以16
  USCI4_SPI_BAUDRATEPRESCALER_32 = (uint8_t)0x05, //SPI时钟速率为系统时钟除以32
  USCI4_SPI_BAUDRATEPRESCALER_64 = (uint8_t)0x06, //SPI时钟速率为系统时钟除以64
  USCI4_SPI_BAUDRATEPRESCALER_128 = (uint8_t)0x07 //SPI时钟速率为系统时钟除以128
} USCI4_SPI_BaudRatePrescaler_TypeDef;

typedef enum
{
  USCI4_SPI_MODE_MASTER = (uint8_t)0x20, //SPI为主设备
  USCI4_SPI_MODE_SLAVE = (uint8_t)0x00   //SPI为从设备
} USCI4_SPI_Mode_TypeDef;

typedef enum
{
  USCI4_SPI_CLOCKPOLARITY_LOW = (uint8_t)0x00, //SCK在空闲状态下为低电平
  USCI4_SPI_CLOCKPOLARITY_HIGH = (uint8_t)0x10 //SCK在空闲状态下为高电平
} USCI4_SPI_ClockPolarity_TypeDef;

typedef enum
{
  USCI4_SPI_CLOCKPHASE_1EDGE = (uint8_t)0x00, //SCK的第一沿采集数据
  USCI4_SPI_CLOCKPHASE_2EDGE = (uint8_t)0x08  //SCK的第二沿采集数据
} USCI4_SPI_ClockPhase_TypeDef;

typedef enum
{
  USCI4_SPI_TXE_DISINT = (uint8_t)0x00, //TBIE为0时不允许发送中断
  USCI4_SPI_TXE_ENINT = (uint8_t)0x01   //TBIE为1时允许发送中断
} USCI4_SPI_TXE_INT_TypeDef;

typedef enum
{
  USCI4_SPI_DATA8 = (uint8_t)0x00, //SPI 8位传输模式
  USCI4_SPI_DATA16 = (uint8_t)0x01 //SPI 16位传输模式
} USCI4_TransmissionMode_TypeDef;

typedef enum
{
  USCI4_TWI_1024 = (uint8_t)0x00, //TWI通信速率 Fhrc/1024
  USCI4_TWI_512 = (uint8_t)0x01,  //TWI通信速率 Fhrc/512
  USCI4_TWI_256 = (uint8_t)0x02,  //TWI通信速率 Fhrc/256
  USCI4_TWI_128 = (uint8_t)0x03,  //TWI通信速率 Fhrc/128
  USCI4_TWI_64 = (uint8_t)0x04,   //TWI通信速率 Fhrc/64
  USCI4_TWI_32 = (uint8_t)0x05,   //TWI通信速率 Fhrc/32
  USCI4_TWI_16 = (uint8_t)0x06,   //TWI通信速率 Fhrc/16
} USCI4_TWI_MasterCommunicationRate_TypeDef;

typedef enum
{
  USCI4_TWI_SlaveIdle = 0x00,
  USCI4_TWI_SlaveReceivedaAddress = 0x01,
  USCI4_TWI_SlaveReceivedaData = 0x02,
  USCI4_TWI_SlaveSendData = 0x03,
  USCI4_TWI_SlaveReceivedaUACK = 0x04,
  USCI4_TWI_SlaveDisableACK = 0x05,
  USCI4_TWI_SlaveAddressError = 0x06,
  USCI4_TWI_MasterIdle = 0x00,
  USCI4_TWI_MasterSendAddress = 0x01,
  USCI4_TWI_MasterSendData = 0x02,
  USCI4_TWI_MasterReceivedaData = 0x03,
  USCI4_TWI_MasterReceivedaUACK = 0x04,
} USCI4_TWIState_TypeDef;

typedef enum
{
  USCI4_UART_Mode_8B = 0X00,  //UART设置为8位模式
  USCI4_UART_Mode_10B = 0X40, //UART设置为10位模式
  USCI4_UART_Mode_11B = 0X80  //UART设置为11位模式
} USCI4_UART_Mode_TypeDef;

typedef enum
{
  USCI4_UART_RX_ENABLE = 0X10, //UART允许接收
  USCI4_UART_RX_DISABLE = 0X00 //UART禁止接收
} USCI4_UART_RX_TypeDef;

typedef enum
{
  USCI4_SPI_FLAG_SPIF = (uint8_t)0x80, //SPI数据传送标志位SPIF
  USCI4_SPI_FLAG_WCOL = (uint8_t)0x40, //SPI写入冲突标志位WCOL
  USCI4_SPI_FLAG_TXE = (uint8_t)0x08,  //SPI发送缓存器空标志TXE
  USCI4_TWI_FLAG_TWIF = (uint8_t)0x40, //TWI中断标志位TWIF
  USCI4_TWI_FLAG_GCA = (uint8_t)0x10,  //TWI通用地址响应标志位GCA
  USCI4_TWI_FLAG_MSTR = (uint8_t)0x20, //TWI主从标志位MSTR
  USCI4_TWI_FLAG_TXRXnE = (uint8_t)0x80,
  USCI4_UART_FLAG_RI = (uint8_t)0x01, //UART接收中断标志位RI
  USCI4_UART_FLAG_TI = (uint8_t)0x02, //UART发送中断标志位TI
} USCI4_Flag_TypeDef;

typedef enum
{
  USCI4_STATE_READY = 0x00,   //准备标志
  USCI4_STATE_BUSY = 0x01,    //忙碌标志
  USCI4_STATE_ERROR = 0x02,   //错误标志
  USCI4_STATE_TIMEOUT = 0x03,  //超时标志
  USCI4_STATE_WAIT = 0x04,   //等待标志：TWI从机等待地址响应
} USCI4_StatusTypeDef;

typedef struct __USCI4_HandleInfoDef
{
  union
  {
    uint8_t* Size_u8;              //8位数据发送缓存区
    uint16_t* Size_u16;           //16位数据发送缓存区
  } pTxBuffPtr;
  uint8_t TxXferSize;              //数据发送量
  uint8_t TxXferCount;            //数据发送计数器
  union
  {
    uint8_t* Size_u8;              //8位数据接收缓存区
    uint16_t* Size_u16;           //16位数据接收缓存区
  } pRxBuffPtr;
  uint8_t RxXferSize;              //数据接收量
  uint8_t RxXferCount;              //数据接收计数器大小
  USCI4_StatusTypeDef TxState;      //发送状态
  USCI4_StatusTypeDef RxState;      //接收状态
} USCI4_HandleInfoDef;

typedef enum
{
  USCI4_TWI_Write = 0x00, //写操作
  USCI4_TWI_Read = 0x01,  //读操作
} USCI4_TWI_RWType;

void USCI4_DeInit(void);
/********************************* SPI **************************************************/
void USCI4_SPI_Init(USCI4_SPI_FirstBit_TypeDef FirstBit,
                    USCI4_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler, USCI4_SPI_Mode_TypeDef Mode,
                    USCI4_SPI_ClockPolarity_TypeDef ClockPolarity, USCI4_SPI_ClockPhase_TypeDef ClockPhase,
                    USCI4_SPI_TXE_INT_TypeDef SPI_TXE_INT, USCI4_TransmissionMode_TypeDef TransmissionMode);
void USCI4_TransmissionMode(USCI4_TransmissionMode_TypeDef TransmissionMode);
void USCI4_SPI_Cmd(FunctionalState NewState);
void USCI4_SPI_SendData_8(uint8_t Data);
uint8_t USCI4_SPI_ReceiveData_8(void);
void USCI4_SPI_SendData_16(uint16_t Data);
uint16_t USCI4_SPI_ReceiveData_16(void);

StatusTypeDef USCI4_SPI_Receive(USCI4_HandleInfoDef* USCI4_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout);
StatusTypeDef USCI4_SPI_Transmit(USCI4_HandleInfoDef* USCI4_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout);
StatusTypeDef USCI4_SPI_TransmitReceive(USCI4_HandleInfoDef* USCI4_HANDLE, uint8_t* pTxData, uint8_t* pRxData, uint8_t Size, uint32_t Timeout);

StatusTypeDef USCI4_SPI_IRQHandler(USCI4_HandleInfoDef* USCI4_HANDLE);
StatusTypeDef USCI4_SPI_Receive_IT(USCI4_HandleInfoDef* USCI4_HANDLE, uint8_t* pData, uint8_t Size);
StatusTypeDef USCI4_SPI_Transmit_IT(USCI4_HandleInfoDef* USCI4_HANDLE, uint8_t* pData, uint8_t Size);
StatusTypeDef USCI4_SPI_TransmitReceive_IT(USCI4_HandleInfoDef* USCI4_HANDLE, uint8_t* pTxData, uint8_t* pRxData, uint8_t Size);

/********************************* TWI **************************************************/
void USCI4_TWI_Slave_Init(uint8_t TWI_Address);
void USCI4_TWI_MasterCommunicationRate(USCI4_TWI_MasterCommunicationRate_TypeDef
                                       TWI_MasterCommunicationRate);
void USCI4_TWI_Start(void);
void USCI4_TWI_MasterModeStop(void);
void USCI4_TWI_SlaveClockExtension(FunctionalState NewState);
void USCI4_TWI_AcknowledgeConfig(FunctionalState NewState);
void USCI4_TWI_GeneralCallCmd(FunctionalState NewState);
FlagStatus USCI4_GetTWIStatus(USCI4_TWIState_TypeDef USCI4_TWIState);
void USCI4_TWI_Cmd(FunctionalState NewState);
void USCI4_TWI_SendAddr(uint8_t Addr, USCI4_TWI_RWType RW);
void USCI4_TWI_SendData(uint8_t Data);
uint8_t USCI4_TWI_ReceiveData(void);

StatusTypeDef USCI4_TWI_Master_Transmit(USCI4_HandleInfoDef* USCI4_HANDLE, uint8_t slaveAddr, uint8_t* pData, uint8_t Size, uint32_t Timeout);
StatusTypeDef USCI4_TWI_Slave_Transmit(USCI4_HandleInfoDef* USCI4_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout);

StatusTypeDef USCI4_TWI_Master_Transmit_IT(USCI4_HandleInfoDef* USCI4_HANDLE, uint8_t slaveAddr, uint8_t* pData, uint8_t Size);
StatusTypeDef USCI4_TWI_Master_Transmit_IRQHandler(USCI4_HandleInfoDef* USCI4_HANDLE);

StatusTypeDef USCI4_TWI_Slave_Transmit_IT(USCI4_HandleInfoDef* USCI4_HANDLE, uint8_t* pData, uint8_t Size);
StatusTypeDef USCI4_TWI_Slave_Transmit_IRQHandler(USCI4_HandleInfoDef* USCI4_HANDLE);

StatusTypeDef USCI4_TWI_Master_Receive(USCI4_HandleInfoDef* USCI4_HANDLE, uint8_t slaveAddr, uint8_t* pData, uint8_t Size, uint32_t Timeout);
StatusTypeDef USCI4_TWI_Slave_Receive(USCI4_HandleInfoDef* USCI4_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout);

StatusTypeDef USCI4_TWI_Master_Receive_IT(USCI4_HandleInfoDef* USCI4_HANDLE, uint8_t slaveAddr, uint8_t* pData, uint8_t Size);
StatusTypeDef USCI4_TWI_Master_Receive_IRQHandler(USCI4_HandleInfoDef* USCI4_HANDLE);

StatusTypeDef USCI4_TWI_Slave_Receive_IT(USCI4_HandleInfoDef* USCI4_HANDLE, uint8_t* pData, uint8_t Size);
StatusTypeDef USCI4_TWI_Slave_Receive_IRQHandler(USCI4_HandleInfoDef* USCI4_HANDLE);

/********************************* UART **************************************************/
void USCI4_UART_Init(uint32_t UART1Fsys, uint32_t BaudRate, USCI4_UART_Mode_TypeDef Mode,
                     USCI4_UART_RX_TypeDef RxMode);
void USCI4_UART_SendData8(uint8_t Data);
uint8_t USCI4_UART_ReceiveData8(void);
void USCI4_UART_SendData9(uint16_t Data);
uint16_t USCI4_UART_ReceiveData9(void);
uint16_t USCI4_UART_ReceiveData9(void);

StatusTypeDef USCI4_UART_Transmit(USCI4_HandleInfoDef* USCI4_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout);
StatusTypeDef USCI4_UART_Transmit_IT(USCI4_HandleInfoDef* USCI4_HANDLE, uint8_t* pData, uint8_t Size);
StatusTypeDef USCI4_UART_Transmit_IRQHandler(USCI4_HandleInfoDef* USCI4_HANDLE);
StatusTypeDef USCI4_UART_Receive(USCI4_HandleInfoDef* USCI4_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout);
StatusTypeDef USCI4_UART_Receive_IT(USCI4_HandleInfoDef* USCI4_HANDLE, uint8_t* pData, uint8_t Size);
StatusTypeDef USCI4_UART_Receive_IRQHandler(USCI4_HandleInfoDef* USCI4_HANDLE);

/********************************* 中断和标志位 **************************************************/
void USCI4_ITConfig(FunctionalState NewState, PriorityStatus Priority);
FlagStatus USCI4_GetFlagStatus(USCI4_Flag_TypeDef USCI4_FLAG);
void USCI4_ClearFlag(USCI4_Flag_TypeDef USCI4_FLAG);

#endif

/******************* (C) COPYRIGHT 2022 SinOne Microelectronics *****END OF FILE****/