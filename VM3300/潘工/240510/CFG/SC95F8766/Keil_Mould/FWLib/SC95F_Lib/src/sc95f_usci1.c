//************************************************************
//  Copyright (c) 深圳市赛元微电子股份有限公司
//	文件名称: 		sc95f_USCI1.c
//	作者		:
//	模块功能: 		USCI1固件库函数C文件
// 	最后更正日期:	2024年1月18日
// 	版本:				V1.0002
//  说明:该文件仅适用于SC95F系列芯片
//*************************************************************

#include "sc95f_usci1.h"

/**************************************************
*函数名称:void USCI1_DeInit(void)
*函数功能:USCI1相关寄存器复位至缺省值
*入口参数:void
*出口参数:void
**************************************************/
void USCI1_DeInit(void)
{
  OTCON &= 0X3F;
  US1CON0 = 0X00;
  US1CON1 = 0X00;
  US1CON2 = 0X00;
  US1CON3 = 0X00;
  IE2 &= (~0X01);
  IP2 &= (~0X01);
}

/**************************************************
*函数名称:void USCI1_SPI_Init(USCI1_SPI_FirstBit_TypeDef FirstBit, USCI1_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler,USCI1_SPI_Mode_TypeDef Mode,
							 USCI1_SPI_ClockPolarity_TypeDef ClockPolarity, USCI1_SPI_ClockPhase_TypeDef ClockPhase,USCI1_SPI_TXE_INT_TypeDef SPI_TXE_INT,USCI1_TransmissionMode_TypeDef TransmissionMode)
*函数功能:SPI初始化配置函数
*入口参数:
USCI1_SPI_FirstBit_TypeDef:FirstBit:优先传送位选择（MSB/LSB）
USCI1_SPI_BaudRatePrescaler_TypeDef:BaudRatePrescaler:SPI时钟频率选择
USCI1_SPI_Mode_TypeDef:Mode:SPI工作模式选择
USCI1_SPI_ClockPolarity_TypeDef:ClockPolarity:SPI时钟极性选择
USCI1_SPI_ClockPhase_TypeDef:ClockPhase:SPI时钟相位选择
USCI1_SPI_TXE_INT_TypeDef:SPI_TXE_INT:发送缓存器中断允许选择,该功能在RD8XX1X芯片上无效
USCI1_TransmissionMode_TypeDef:TransmissionMode:SPI传输模式选择 8/16位
*出口参数:void
**************************************************/
void USCI1_SPI_Init(USCI1_SPI_FirstBit_TypeDef FirstBit,
                    USCI1_SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler, USCI1_SPI_Mode_TypeDef Mode,
                    USCI1_SPI_ClockPolarity_TypeDef ClockPolarity, USCI1_SPI_ClockPhase_TypeDef ClockPhase,
                    USCI1_SPI_TXE_INT_TypeDef SPI_TXE_INT, USCI1_TransmissionMode_TypeDef TransmissionMode)
{

  OTCON = (OTCON & 0X3F) | 0X40;
  US1CON1 = US1CON1 & (~0X05) | FirstBit | SPI_TXE_INT | TransmissionMode;
  US1CON0 = US1CON0 & 0X80 | BaudRatePrescaler | Mode | ClockPolarity | ClockPhase;
}

/**************************************************
*函数名称:void USCI1_TransmissionMode(USCI1_TransmissionMode_TypeDef TransmissionMode)
*函数功能:SPI 传输模式配置函数
*入口参数:
USCI1_TransmissionMode_TypeDef:TransmissionMode:SPI传输模式选择 8/16e位
*出口参数:void
**************************************************/
void USCI1_TransmissionMode(USCI1_TransmissionMode_TypeDef TransmissionMode)
{
  if(TransmissionMode == USCI1_SPI_DATA8)
  {
    US1CON1 &= 0xFD;
  }
  else
  {
    US1CON1 |= 0x02;
  }
}

/*****************************************************
*函数名称:void USCI1_SPI_Cmd(FunctionalState NewState)
*函数功能:SPI功能开关函数
*入口参数:
FunctionalState:NewState:功能启动/关闭选择
*出口参数:void
*****************************************************/
void USCI1_SPI_Cmd(FunctionalState NewState)
{
  OTCON = (OTCON & 0X3F) | 0X40;

  if(NewState != DISABLE)
  {
    US1CON0 |= 0X80;
  }
  else
  {
    US1CON0 &= (~0X80);
  }
}
/*****************************************************
*函数名称:void USCI1_SPI_SendData_8(uint8_t Data)
*函数功能:USCI1 SPI发送数据
*入口参数:
uint8_t:Data:发送的数据
*出口参数:void
*****************************************************/
void USCI1_SPI_SendData_8(uint8_t Data)
{
  US1CON2 = Data;
}

/*****************************************************
*函数名称:uint8_t USCI1_SPI_ReceiveData_8(void)
*函数功能:获得US1CON2中的值
*入口参数:void
*出口参数:
uint8_t:接收的数据
*****************************************************/
uint8_t USCI1_SPI_ReceiveData_8(void)
{
  return US1CON2;
}

/*****************************************************
*函数名称:void USCI1_SPI_SendData_16(uint16_t Data)
*函数功能:US1CON2 SPI发送数据
*入口参数:
uint16_t:Data:发送的数据
*出口参数:void
*****************************************************/
void USCI1_SPI_SendData_16(uint16_t Data)
{
  US1CON3 = (uint8_t)(Data >> 8);
  US1CON2 = (uint8_t)Data;
}

/*****************************************************
*函数名称:uint16_t USCI1_SPI_ReceiveData_16(void)
*函数功能:获得US1CON2中的值
*入口参数:void
*出口参数:
uint16_t:接收的数据
*****************************************************/
uint16_t USCI1_SPI_ReceiveData_16(void)
{
  uint16_t SPI_data;
  SPI_data = (uint16_t)((US1CON3 << 8) | US1CON2);
  return SPI_data;
}

/**********************************************************************************************************
*函数名称:StatusTypeDef USCI1_SPI_IRQHandler(USCI1_HandleInfoDef* USCI1_HANDLE)
*函数功能:SPI0 中断处理
*入口参数:
USCI1_HandleInfoDef*:USCI1_HANDLE:指向包含 SPI0 信息的 USCI1_HandleInfoDef 结构体的指针。
*出口参数:
void
**********************************************************************************************************/
StatusTypeDef USCI1_SPI_IRQHandler(USCI1_HandleInfoDef* USCI1_HANDLE)
{
  StatusTypeDef TempStatus = Status_ERROR;

  if(USCI1_HANDLE->RxState == USCI1_STATE_BUSY)
  {
    /* 当数据没有接收完成 */
    if(USCI1_HANDLE->RxXferCount < USCI1_HANDLE->RxXferSize)
    {
      /* SPI处于16位通信模式 */
      if((US1CON1 & USCI1_SPI_DATA16) != 0)
      {
        *(USCI1_HANDLE->pRxBuffPtr.Size_u16 + USCI1_HANDLE->RxXferCount) = USCI1_SPI_ReceiveData_16();			//读取16位数据
      }
      /* SPI处于8位通信模式 */
      else
      {
        *(USCI1_HANDLE->pRxBuffPtr.Size_u8 + USCI1_HANDLE->RxXferCount) = USCI1_SPI_ReceiveData_8();			//读取16位数据
      }

      TempStatus = Status_BUSY;
      USCI1_HANDLE->RxXferCount++;			//接收到数据，计数值加1

      /* 数据接收完成，状态位进行修改 */
      if(USCI1_HANDLE->RxXferCount == USCI1_HANDLE->RxXferSize)
      {
        USCI1_HANDLE->RxState = USCI1_STATE_READY;
        TempStatus =  Status_OK;
      }
    }

    if(USCI1_HANDLE->TxState == USCI1_STATE_BUSY)
    {

      USCI1_HANDLE->TxXferCount++;			//数据发送完成，计数值加1
      /* 当数据没有发送完成 */
      if(USCI1_HANDLE->TxXferCount < USCI1_HANDLE->TxXferSize)
      {
        /* SPI处于16位通信模式 */
        if((US1CON1 & USCI1_SPI_DATA16) != 0)
        {
          USCI1_SPI_SendData_16(*(USCI1_HANDLE->pTxBuffPtr.Size_u16 + USCI1_HANDLE->TxXferCount));			//发送16位数据
        }
        /* SPI处于8位通信模式 */
        else
        {
          USCI1_SPI_SendData_8(*(USCI1_HANDLE->pTxBuffPtr.Size_u8 + USCI1_HANDLE->TxXferCount));			//发送16位数据
        }
        TempStatus = Status_BUSY;
      }
      /* 数据发送完成，状态位进行修改  */
      else if(USCI1_HANDLE->TxXferCount == USCI1_HANDLE->TxXferSize)
      {
        USCI1_HANDLE->TxState = USCI1_STATE_READY;
        TempStatus = Status_OK;
      }
    }
    /* 当SPI处于主机时，SPI需要发送数据，才能同步接收到数据 */
    else if(USCI1_HANDLE->RxXferSize)
    {
      USCI1_SPI_SendData_8(0x00);
    }
  }
  return TempStatus;
}


/**********************************************************************************************************
*函数名称:StatusTypeDef USCI1_SPI_Receive(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t *pData, uint8_t Size, uint32_t Timeout)
*函数功能:SPI在轮询模式下接收大量数据
*入口参数:
USCI1_HandleInfoDef*:USCI1_HANDLE:指向包含指定SPI模块的配置信息结构体的指针
uint8_t *:pData:接收数据的存放区
uint16_t:Size:待接收的数据量
uint32_t:Timeout:超时时间
*出口参数:
StatusTypeDef:USCI1 状态
**********************************************************************************************************/
StatusTypeDef USCI1_SPI_Receive(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout)
{
  uint32_t TimeoutCnt = 0;

  if(USCI1_HANDLE->RxState == USCI1_STATE_READY)
  {
    /* 待发送数据长度必须大于0，否则返回错误状态 */
    if(((IE2 & 0x01) != 0) || (Size == 0U))
    {
      return USCI1_STATE_ERROR;
    }

    /* SPI作为主机时，接收数据必定跟随发送数据 */
    if((US1CON0 & USCI1_SPI_MODE_MASTER) != 0)
    {
      return USCI1_SPI_TransmitReceive(USCI1_HANDLE, pData, pData, Size, Timeout);			//跳转到阻塞模式数据收发函数
    }

    USCI1_HANDLE->RxState = USCI1_STATE_BUSY;			//发送进程忙碌中
    USCI1_ClearFlag(USCI1_SPI_FLAG_SPIF);			 //接收前清除接收中断标志
    USCI1_HANDLE->pRxBuffPtr.Size_u8 = pData;			//指向待发送数据的地址
    USCI1_HANDLE->RxXferSize = Size;			//更新待发送的数据量
    USCI1_HANDLE->RxXferCount = 0;			//发送计数器清零

    while(USCI1_HANDLE->RxXferCount < USCI1_HANDLE->RxXferSize)
    {
      /* 等待SPI中断标志位置起 */
      if(USCI1_GetFlagStatus(USCI1_SPI_FLAG_SPIF))
      {
        /* SPI处于16位通信模式 */
        if((US1CON1 & USCI1_SPI_DATA16) != 0)
        {
          *(USCI1_HANDLE->pRxBuffPtr.Size_u16 + USCI1_HANDLE->RxXferCount) = USCI1_SPI_ReceiveData_16();			//读取16位数据,并且地址自增
        }
        /* SPI处于8位通信模式 */
        else
        {
          *(USCI1_HANDLE->pRxBuffPtr.Size_u8 + USCI1_HANDLE->RxXferCount) = USCI1_SPI_ReceiveData_8();			//读取16位数据,并且地址自增
        }
        USCI1_ClearFlag(USCI1_SPI_FLAG_SPIF);				//清除标志位
        USCI1_HANDLE->RxXferCount++;	//接收数据量计数加1
        TimeoutCnt = 0;			//超时计数值清零
      }
      else
      {
        /* 超时计数器不断累加，直到超出设定的超时时间 */
        if((TimeoutCnt++) > Timeout)
        {
          if(Timeout == 0)
            return USCI1_STATE_TIMEOUT;				//返回超时错误
        }
        WDTCON |= 0x10;          //喂狗函数，防止看门狗复位
      }
    }

    if(USCI1_HANDLE->RxXferCount == USCI1_HANDLE->RxXferSize)
    {
      USCI1_HANDLE->RxState = USCI1_STATE_READY;	//接收完成
      return Status_OK;
    }
    else
    {
      USCI1_HANDLE->RxState = USCI1_STATE_ERROR;//接收错误
      return Status_ERROR;
    }
  }
  else
  {
    return Status_BUSY;//返回忙碌状态
  }
}

/**********************************************************************************************************
*函数名称:StatusTypeDef USCI1_SPI_Receive_IT(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t *pData, uint8_t Size)
*函数功能:中断模式接收一定量数据
*入口参数:
USCI1_HandleInfoDef*:USCI1_HANDLE:指向包含指定SPI模块的配置信息结构体的指针
uint8_t *:pData:接收数据的存放
uint16_t:Size:待接收的数据量
*出口参数:
StatusTypeDef:USCI1 状态
**********************************************************************************************************/
StatusTypeDef USCI1_SPI_Receive_IT(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pData, uint8_t Size)
{
  /* 检查一个接收进程是否正在进行 */
  if(USCI1_HANDLE->RxState == USCI1_STATE_READY)
  {
    /* 待发送数据长度必须大于0，否则返回错误状态 */
    if(((IE2 & 0x01) == 0) || (Size == 0U))
    {
      return USCI1_STATE_ERROR;
    }

    /* SPI作为主机时，接收数据必定跟随发送数据 */
    if((US1CON0 & USCI1_SPI_MODE_MASTER) != 0)
    {
      return USCI1_SPI_TransmitReceive_IT(USCI1_HANDLE, pData, pData, Size);			//跳转到中断模式数据收发函数
    }

    USCI1_HANDLE->RxState = USCI1_STATE_BUSY;			//状态更新为接收忙碌中
    USCI1_ClearFlag(USCI1_SPI_FLAG_SPIF);			//清除中断标志位
    USCI1_HANDLE->pRxBuffPtr.Size_u8 = pData;			//指向待发送数据的地址
    USCI1_HANDLE->RxXferSize = Size;			//更新待发送的数据量
    USCI1_HANDLE->RxXferCount = 0;			//发送计数器清零

    return Status_OK;
  }
  else
  {
    return Status_BUSY;//返回标志位
  }
}

/**********************************************************************************************************
*函数名称:StatusTypeDef USCI1_SPI_Transmit(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout)
*函数功能:SPI在轮询模式下发送大量数据
*入口参数:
USCI1_HandleInfoDef*:USCI1_HANDLE:指向包含指定SPI模块的配置信息结构体的指针
uint8_t *pData:指向数据缓存的指针。
uint16_t Size:发送数据的大小
uint32_t Timeout:超时时间
*出口参数:
StatusTypeDef:USCI1 状态
**********************************************************************************************************/
StatusTypeDef USCI1_SPI_Transmit(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout)
{
  uint32_t TimeoutCnt = 0;
  /* 检查一个发送进程是否正在进行 */
  if(USCI1_HANDLE->TxState == USCI1_STATE_READY)
  {
    /* 待发送数据长度必须大于0，否则返回错误状态 */
    if(((IE2 & 0x01) != 0) || (Size == 0U))
    {
      return Status_ERROR;
    }

    USCI1_HANDLE->TxState = USCI1_STATE_BUSY;			//发送进程忙碌中
    USCI1_ClearFlag(USCI1_SPI_FLAG_SPIF);			 //发送前清除标志位
    USCI1_HANDLE->pTxBuffPtr.Size_u8 = pData;			//指向待发送数据的地址
    USCI1_HANDLE->TxXferSize = Size;			//更新待发送的数据量
    USCI1_HANDLE->TxXferCount = 0;			//发送计数器清零

    while(USCI1_HANDLE->TxXferCount < USCI1_HANDLE->TxXferSize)//判断是否接收所有数据
    {
      if((US1CON1 & USCI1_SPI_DATA16) != 0)/* SPI处于16位通信模式 */
      {
        USCI1_SPI_SendData_16(*(USCI1_HANDLE->pTxBuffPtr.Size_u16 + USCI1_HANDLE->TxXferCount));			//发送16位数据并且数据地址增加
      }
      else/* SPI处于8位通信模式 */
      {
        USCI1_SPI_SendData_8(*(USCI1_HANDLE->pTxBuffPtr.Size_u8 + USCI1_HANDLE->TxXferCount));			//发送8位数据并且数据地址增加
      }

      while(!USCI1_GetFlagStatus(USCI1_SPI_FLAG_SPIF))			//等待发送完成
      {
        /* 超时计数器不断累加，直到超出设定的超时时间 */
        if(TimeoutCnt++ > Timeout)
        {
          USCI1_HANDLE->TxState = USCI1_STATE_TIMEOUT;//发送超时
          return Status_TIMEOUT;
        }
        WDTCON |= 0x10;			//喂狗，防止等待时间过长，导致WDT复位
      }

      USCI1_ClearFlag(USCI1_SPI_FLAG_SPIF);				//发送前先清除标志位
      TimeoutCnt = 0;			//超时计数器清零
      USCI1_HANDLE->TxXferCount ++;	//发送数据量计数
    }
    if(USCI1_HANDLE->TxXferCount == USCI1_HANDLE->TxXferSize)
    {
      USCI1_HANDLE->TxState = USCI1_STATE_READY;	//发送完成
      return Status_OK;
    }
    else
    {
      USCI1_HANDLE->TxState = USCI1_STATE_ERROR;//发生发送错误
      return Status_ERROR;
    }
  }
  else
  {
    return Status_BUSY;//返回忙碌状态
  }
}
/**********************************************************************************************************
*函数名称:StatusTypeDef USCI1_SPI_Transmit_IT(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pData, uint8_t Size)
*函数功能:中断模式发送一定量数据
*入口参数:
USCI1_HandleInfoDef *USCI1_HANDLE:指向包含 SPI0 信息的 USCI1_HandleInfoDef 结构体的指针。
uint8_t *pData:指向数据缓存的指针。
uint16_t Size:发送数据的大小
*出口参数:
StatusTypeDef:USCI1 状态
**********************************************************************************************************/
StatusTypeDef USCI1_SPI_Transmit_IT(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pData, uint8_t Size)
{
  /* 检查一个发送进程是否正在进行 */
  if(USCI1_HANDLE->TxState == USCI1_STATE_READY)
  {
    /* 没有开启USCI1中断或发送数据量大小为0，返回错误 */
    if(((IE2 & 0x01) == 0) || (Size == 0U))
    {
      return Status_ERROR;
    }

    USCI1_HANDLE->TxState = USCI1_STATE_BUSY;			//发送进程忙碌中
    USCI1_ClearFlag(USCI1_SPI_FLAG_SPIF);			//清除中断标志位
    USCI1_HANDLE->pTxBuffPtr.Size_u8 = pData;			//指向待发送数据的地址
    USCI1_HANDLE->TxXferSize = Size;			//更新待发送的数据量
    USCI1_HANDLE->TxXferCount = 0;			//发送计数器置0

    /* 发送第1byte数据 */
    /* SPI处于16位通信模式 */
    if((US1CON1 & USCI1_SPI_DATA16) != 0)
    {
      USCI1_SPI_SendData_16(*(USCI1_HANDLE->pTxBuffPtr.Size_u16));
    }
    /* SPI处于8位通信模式 */
    else
    {
      USCI1_SPI_SendData_8(*(USCI1_HANDLE->pTxBuffPtr.Size_u8));
    }

    return Status_OK;
  }
  else
  {
    return  Status_BUSY;			//状态位修改为忙碌状态
  }
}
/**********************************************************************************************************
*函数名称:StatusTypeDef USCI1_SPI_TransmitReceive(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pTxData, uint8_t* pRxData, uint8_t Size, uint32_t Timeout)
*函数功能:阻塞模式收发一定量数据
*入口参数:
USCI1_HandleInfoDef*:USCI1_HANDLE:指向包含 SPI0 信息的 USCI1_HandleInfoDef 结构体的指针。
*出口参数:
StatusTypeDef:USCI1 状态
**********************************************************************************************************/
StatusTypeDef USCI1_SPI_TransmitReceive(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pTxData, uint8_t* pRxData, uint8_t Size, uint32_t Timeout)
{
  uint32_t TimeoutCnt = 0;
  /* 检查一个发送进程是否正在进行 */
  if((USCI1_HANDLE->TxState == USCI1_STATE_READY) && (USCI1_HANDLE->RxState == USCI1_STATE_READY))
  {

    /* 待发送和接收数据长度必须大于0，否则返回错误状态 */
    if(((IE2 & 0x01) != 0) || (Size == 0U))
    {
      return  Status_ERROR;
    }

    USCI1_HANDLE->TxState = USCI1_HANDLE->RxState = USCI1_STATE_BUSY;			//发送进程忙碌中
    USCI1_ClearFlag(USCI1_SPI_FLAG_SPIF);			//清除中断标志位
    USCI1_HANDLE->pTxBuffPtr.Size_u8 = pTxData;       //指向待发送数据的地址
    USCI1_HANDLE->pRxBuffPtr.Size_u8 = pRxData;
    USCI1_HANDLE->TxXferSize = USCI1_HANDLE->RxXferSize = Size;			//更新待发送的数据量
    USCI1_HANDLE->TxXferCount = USCI1_HANDLE->RxXferCount = 0;			//发送计数器清零

    while(USCI1_HANDLE->TxXferCount < USCI1_HANDLE->TxXferSize);
    {

      if((US1CON1 & USCI1_SPI_DATA16) != 0)
      {
        USCI1_SPI_SendData_16(*(USCI1_HANDLE->pTxBuffPtr.Size_u16 + USCI1_HANDLE->TxXferCount));			//发送16位数据并且地址增加
        while(!USCI1_GetFlagStatus(USCI1_SPI_FLAG_SPIF))			//等待发送完成
        {
          /* 等待时间是否发生了超时 */
          if(TimeoutCnt++ > Timeout)
          {
            return USCI1_STATE_TIMEOUT;				//返回超时错误
          }
          WDTCON |= 0x10;			//喂狗，防止等待时间过长，导致WDT复位
        }
        USCI1_ClearFlag(USCI1_SPI_FLAG_SPIF);				//发送前先清除标志位
        *(USCI1_HANDLE->pTxBuffPtr.Size_u16 + USCI1_HANDLE->TxXferCount) = USCI1_SPI_ReceiveData_16();
      }
      else
      {
        USCI1_SPI_SendData_8(*(USCI1_HANDLE->pTxBuffPtr.Size_u8 + USCI1_HANDLE->TxXferCount));			//发送16位数据并且地址增加
        while(!USCI1_GetFlagStatus(USCI1_SPI_FLAG_SPIF))			//等待发送完成
        {
          /* 等待时间是否发生了超时 */
          if(TimeoutCnt++ > Timeout)
          {
            return USCI1_STATE_TIMEOUT;				//返回超时错误
          }
          WDTCON |= 0x10;			//喂狗，防止等待时间过长，导致WDT复位
        }
        USCI1_ClearFlag(USCI1_SPI_FLAG_SPIF);				//发送前先清除标志位
        *(USCI1_HANDLE->pTxBuffPtr.Size_u8 + USCI1_HANDLE->TxXferCount) = USCI1_SPI_ReceiveData_8();
      }
      TimeoutCnt = 0;			//超时计数值清零
      USCI1_HANDLE->TxXferCount++;			//数据量计数值加1
      USCI1_HANDLE->TxXferCount++;			//数据量计数值加1
    }
    if(USCI1_HANDLE->TxXferCount == USCI1_HANDLE->TxXferSize)
    {
      USCI1_HANDLE->TxState = USCI1_HANDLE->RxState = USCI1_STATE_READY;	//发送完成
      return Status_OK;
    }
    else
    {
      USCI1_HANDLE->TxState = USCI1_STATE_ERROR;//发生发送错误
      return Status_ERROR;
    }
  }
  else
  {
    return Status_ERROR;
  }

}
/**********************************************************************************************************
*函数名称:StatusTypeDef USCI1_SPI_TransmitReceive_IT(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pTxData, uint8_t* pRxData, uint8_t Size)
*函数功能:SPI在中断模式下发送和接收大量数据时，先在main函数中调用此函数
*入口参数:
USCI1_HandleInfoDef *USCI1_HANDLE:指向包含指定SPI模块的配置信息结构体的指针
uint8_t *:pData:发送和接收数据的存放区
uint16_t:Size:待发送和接收的数据量
*出口参数:
StatusTypeDef:USCI1 状态
**********************************************************************************************************/
StatusTypeDef USCI1_SPI_TransmitReceive_IT(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pTxData, uint8_t* pRxData, uint8_t Size)
{
  /* 待发送数据长度必须大于0，否则返回错误状态 */
  if((USCI1_HANDLE->TxState == USCI1_STATE_READY) && (USCI1_HANDLE->RxState == USCI1_STATE_READY))
  {

    /* 待发送和接收数据长度必须大于0，否则返回错误状态 */
    if(((IE2 & 0x01) == 0) || (Size == 0U))
    {
      return  Status_ERROR;
    }
    USCI1_SPI_Cmd(DISABLE);
    USCI1_HANDLE->TxState = USCI1_HANDLE->RxState = USCI1_STATE_BUSY;			//发送进程忙碌中
    USCI1_ClearFlag(USCI1_SPI_FLAG_SPIF);			//清除中断标志位
    USCI1_HANDLE->pTxBuffPtr.Size_u8 = pTxData;
    USCI1_HANDLE->pRxBuffPtr.Size_u8 = pRxData;			//指向待发送数据的地址
    USCI1_HANDLE->TxXferSize = USCI1_HANDLE->RxXferSize = Size;			//更新待发送的数据量
    USCI1_HANDLE->TxXferCount = USCI1_HANDLE->RxXferCount = 0;			//发送计数器清零
    USCI1_SPI_Cmd(ENABLE);

    /* 发送第1byte数据 */
    /* SPI处于16位通信模式 */
    if((US1CON1 & USCI1_SPI_DATA16) != 0)
    {
      USCI1_SPI_SendData_16(*(USCI1_HANDLE->pTxBuffPtr.Size_u16));			//发送16位数据
    }
    /* SPI处于8位通信模式 */
    else
    {
      USCI1_SPI_SendData_8(*(USCI1_HANDLE->pTxBuffPtr.Size_u8));			//发送8位数据
    }
    /* 状态处于忙碌的状态 */

    return  Status_OK;
  }
  else
  {
    return Status_ERROR;
  }
}

/**************************************************
*函数名称:void USCI1_TWI_Slave_Init(uint8_t TWI_Address)
*函数功能:USCI1 TWI从机初始化配置函数
*入口参数:
uint8_t:TWI_Address:TWI作为从机时的7位从机地址
*出口参数:void
**************************************************/
void USCI1_TWI_Slave_Init(uint8_t TWI_Address)
{
  OTCON = OTCON & 0X3F | 0X80;
  US1CON2 = TWI_Address << 1;
}

/**************************************************
*函数名称:void USCI1_TWI_MasterCommunicationRate(USCI1_TWI_MasterCommunicationRate_TypeDef TWI_MasterCommunicationRate)
*函数功能:USCI1 TWI主机模式下通讯速率设定
*入口参数:
USCI1_TWI_MasterCommunicationRate_TypeDef:TWI_MasterCommunicationRate:TWI主机模式下通讯速率
*出口参数:void
**************************************************/
void USCI1_TWI_MasterCommunicationRate(USCI1_TWI_MasterCommunicationRate_TypeDef
                                       TWI_MasterCommunicationRate)
{
  OTCON = OTCON & 0X3F | 0X80;
  US1CON1 |= TWI_MasterCommunicationRate;
}

/**************************************************
*函数名称:void USCI1_TWI_Start(void)
*函数功能:USCI1 TWI 起始位
*入口参数:void
*出口参数:void
**************************************************/
void USCI1_TWI_Start(void)
{
  US1CON1 |= 0x20;
}

/**************************************************
*函数名称:void USCI1_TWI_MasterModeStop(void)
*函数功能:USCI1 TWI主机模式停止位
*入口参数:void
*出口参数:void
**************************************************/
void USCI1_TWI_MasterModeStop(void)
{
  US1CON1 |= 0x10;
}

/**************************************************
*函数名称:void USCI1_TWI_SlaveClockExtension(FunctionalState NewState)
*函数功能:USCI1 TWI从机模式时钟延长功能位
*入口参数:
FunctionalState:NewState:使能/失能选择
*出口参数:void
**************************************************/
void USCI1_TWI_SlaveClockExtension(FunctionalState NewState)
{
  OTCON = OTCON & 0X3F | 0X80;

  if(NewState != DISABLE)
  {
    US1CON1 |= 0x40;
  }
  else
  {
    US1CON1 &= 0XBF;
  }
}

/**************************************************
*函数名称:void USCI1_TWI_AcknowledgeConfig(FunctionalState NewState)
*函数功能:TWI接收应答使能函数
*入口参数:
FunctionalState:NewState:接收应答使能/失能选择
*出口参数:void
**************************************************/
void USCI1_TWI_AcknowledgeConfig(FunctionalState NewState)
{
  OTCON = OTCON & 0X3F | 0X80;

  if(NewState != DISABLE)
  {
    US1CON0 |= 0X08;
  }
  else
  {
    US1CON0 &= 0XF7;
  }
}

/**************************************************
*函数名称:void USCI1_TWI_GeneralCallCmd(FunctionalState NewState)
*函数功能:TWI通用地址响应使能函数
*入口参数:
FunctionalState:NewState:接收应答使能/失能选择
*出口参数:void
**************************************************/
void USCI1_TWI_GeneralCallCmd(FunctionalState NewState)
{
  OTCON = OTCON & 0X3F | 0X80;

  if(NewState != DISABLE)
  {
    US1CON2 |= 0X01;
  }
  else
  {
    US1CON2 &= 0XFE;
  }
}

/*****************************************************
*函数名称:FlagStatus USCI1_GetTWIStatus(USCI1_TWIState_TypeDef USCI1_TWIState)
*函数功能:读取TWI状态
*入口参数:
USCI1_TWIState_TypeDef:USCI1_TWIState:TWI状态类型
*出口参数:
FlagStatus:USCI1_TWI标志状态
*****************************************************/
FlagStatus USCI1_GetTWIStatus(USCI1_TWIState_TypeDef USCI1_TWIState)
{
  if((US1CON0 & 0x07) == USCI1_TWIState)
    return SET;
  else
    return RESET;
}

/*****************************************************
*函数名称:void USCI1_TWI_Cmd(FunctionalState NewState)
*函数功能:TWI功能开关函数
*入口参数:
FunctionalState:NewState:功能启动/关闭选择
*出口参数:void
*****************************************************/
void USCI1_TWI_Cmd(FunctionalState NewState)
{
  OTCON = OTCON & 0X3F | 0X80;

  if(NewState != DISABLE)
  {
    US1CON0 |= 0X80;
  }
  else
  {
    US1CON0 &= (~0X80);
  }
}

/*****************************************************
*函数名称:void USCI1_TWI_SendAddr(uint8_t Addr,USCI1_TWI_RWType RW)
*函数功能:TWI发送地址，读写类型
*入口参数:
uint8_t:Addr:发送的地址 0~127
USCI1_TWI_RWType:RW:读写类型
*出口参数:void
*****************************************************/
void USCI1_TWI_SendAddr(uint8_t Addr, USCI1_TWI_RWType RW)
{
  US1CON3 = (Addr << 1) | RW;
}

/*****************************************************
*函数名称:void USCI1_TWI_SendData(uint8_t Data)
*函数功能:TWI发送数据
*入口参数:
uint8_t:Data:发送的数据
*出口参数:void
*****************************************************/
void USCI1_TWI_SendData(uint8_t Data)
{
  US1CON3 = Data;
}

/*****************************************************
*函数名称:uint8_t USCI1_TWI_SendData(void)
*函数功能:获得US1CON3中的值
*入口参数:void
*出口参数:
uint8_t:接收的数据
*****************************************************/
uint8_t USCI1_TWI_ReceiveData(void)
{
  return US1CON3;
}

/*****************************************************
*函数名称：StatusTypeDef USCI1_TWI_Wait_TWIF(USCI1_HandleInfoDef* USCI1_HANDLE,uint32_t Timeout)
*函数功能：等待TWIF置起
*入口参数：
USCI1_HandleInfoDef*:USCI1_HANDLE:指针指向USCI1数据信息存放区
uint32_t:Timeout:超时时间设置
*出口参数：StatusTypeDef状态枚举
*****************************************************/
StatusTypeDef USCI1_TWI_Wait_TWIF(USCI1_HandleInfoDef* USCI1_HANDLE, uint32_t Timeout)
{
  uint32_t TimeoutCnt = 0;
  while(!(USCI1_GetFlagStatus(USCI1_TWI_FLAG_TWIF)))			//等待启动信号发送完毕
  {
    TimeoutCnt++;
    if(TimeoutCnt > Timeout)
    {
      /* 超时更新状态 */
      if(USCI1_HANDLE->TxState == USCI1_STATE_BUSY)
        USCI1_HANDLE->TxState = USCI1_STATE_TIMEOUT;
      if(USCI1_HANDLE->RxState == USCI1_STATE_BUSY)
        USCI1_HANDLE->RxState = USCI1_STATE_TIMEOUT;
      return Status_TIMEOUT;
    }
  }
  USCI1_ClearFlag(USCI1_TWI_FLAG_TWIF);			//清除标志位
  return Status_OK;
}

/*****************************************************
*函数名称：StatusTypeDef USCI1_TWI_Master_Transmit(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t slaveAddr, uint8_t* pData, uint8_t Size, uint32_t Timeout)
*函数功能：发送8位数据时，主机轮询模式下发送大量数据
*入口参数：
USCI1_HandleInfoDef*:USCI1_HANDLE:指针指向USCI1数据信息存放区
uint8_t:slaveAddr:从机地址
uint8_t*：pData	指针指向存储区
uint32_t:Size:存储数据长度
uint32_t:Timeout:超时时间设置
*出口参数：StatusTypeDef状态枚举
*****************************************************/
StatusTypeDef USCI1_TWI_Master_Transmit(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t slaveAddr, uint8_t* pData, uint8_t Size, uint32_t Timeout)
{
  /* 检查一个发送进程是否正在进行 */
  if(USCI1_HANDLE->TxState == USCI1_STATE_READY)
  {
    /* 待发送数据长度必须大于0，否则返回错误状态 */
    if((IE2 & 0x01 != 0) || (Size == 0U))
    {
      return Status_ERROR;
    }

    USCI1_HANDLE->TxState = USCI1_STATE_BUSY;			//发送进程忙碌中
    USCI1_ClearFlag(USCI1_TWI_FLAG_TWIF);			 //发送前清除标志位
    USCI1_HANDLE->pTxBuffPtr.Size_u8 = pData;			//指向待发送数据的地址
    USCI1_HANDLE->TxXferSize = Size;			//更新待发送的数据量
    USCI1_HANDLE->TxXferCount = 0;			//发送计数器清零

    USCI1_TWI_Start();			//发送启动信号
    if(USCI1_TWI_Wait_TWIF(USCI1_HANDLE, Timeout) == Status_TIMEOUT)           //等待启动信号发送完毕
    {
      /* 无论是否发送完成，都需要发送结束信号，防止主机占用总线 */
      USCI1_TWI_MasterModeStop();
      return Status_TIMEOUT;
    }

    if(USCI1_GetTWIStatus(USCI1_TWI_MasterSendAddress) == RESET)          //检测状态机状态
    {
      USCI1_HANDLE->TxState = USCI1_STATE_ERROR;
      /* 无论是否发送完成，都需要发送结束信号，防止主机占用总线 */
      USCI1_TWI_MasterModeStop();
      return Status_ERROR;
    }

    US1CON3 = (slaveAddr << 1) & 0xFE;			//发送地址和读写位
    if(USCI1_TWI_Wait_TWIF(USCI1_HANDLE, Timeout) == Status_TIMEOUT)           //等待信号发送完毕
    {
      /* 无论是否发送完成，都需要发送结束信号，防止主机占用总线 */
      USCI1_TWI_MasterModeStop();
      return Status_TIMEOUT;
    }

    do
    {
      if(USCI1_GetTWIStatus(USCI1_TWI_MasterSendData) == RESET)          //检测状态机状态
      {
        USCI1_HANDLE->TxState = USCI1_STATE_ERROR;
        /* 无论是否发送完成，都需要发送结束信号，防止主机占用总线 */
        USCI1_TWI_MasterModeStop();
        return Status_ERROR;
      }
      US1CON3 = *(USCI1_HANDLE->pTxBuffPtr.Size_u8  + USCI1_HANDLE->TxXferCount);             //TWI发送数据
      if(USCI1_TWI_Wait_TWIF(USCI1_HANDLE, Timeout) == Status_TIMEOUT)           //等待信号发送完毕
      {
        /* 无论是否发送完成，都需要发送结束信号，防止主机占用总线 */
        USCI1_TWI_MasterModeStop();
        return Status_TIMEOUT;
      }
      USCI1_HANDLE->TxXferCount++;
    }
    while(USCI1_HANDLE->TxXferCount < USCI1_HANDLE->TxXferSize);

    /* 无论是否发送完成，都需要发送结束信号，防止主机占用总线 */
    USCI1_TWI_MasterModeStop();

    if(USCI1_HANDLE->TxXferCount == USCI1_HANDLE->TxXferSize)
    {
      USCI1_HANDLE->TxState = USCI1_STATE_READY;	//发送完成
      return Status_OK;
    }
    else
    {
      USCI1_HANDLE->TxState = USCI1_STATE_ERROR;//发生发送错误
      return Status_ERROR;
    }

  }
  else
  {
    return Status_BUSY;
  }
}

/*****************************************************
*函数名称:StatusTypeDef USCI1_TWI_Slave_Transmit(USCI1_HandleInfoDef* USCI1_HANDLE, uint32_t Timeout)
*函数功能:发送8位数据时，从机轮询模式下发送大量数据
* 注：默认开启时钟延长模式
*入口参数:
USCI1_HandleInfoDef*:USCI1_HANDLE:指针指向USCI1数据信息存放区
uint32_t:Timeout:超时时间设置
*出口参数:StatusTypeDef状态枚举
*****************************************************/
StatusTypeDef USCI1_TWI_Slave_Transmit(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout)
{
  /* 检查一个发送进程是否正在进行 */
  if(USCI1_HANDLE->TxState == USCI1_STATE_READY)
  {
    /* 待发送数据长度必须大于0，否则返回错误状态 */
    if((IE2 & 0x01 != 0) || (Size == 0U))
    {
      return Status_ERROR;
    }
    else
    {
      USCI1_HANDLE->TxState = USCI1_STATE_BUSY;			//发送进程忙碌中
      USCI1_ClearFlag(USCI1_TWI_FLAG_TWIF);			 //发送前清除标志位
      USCI1_HANDLE->pTxBuffPtr.Size_u8 = pData;			//指向待发送数据的地址
      USCI1_HANDLE->TxXferSize = Size;			//更新待发送的数据量
      USCI1_HANDLE->TxXferCount = 0;			//发送计数器清零

      USCI1_TWI_SlaveClockExtension(ENABLE);            //开启时钟延长
      USCI1_TWI_AcknowledgeConfig(ENABLE);         //开启AA使能位
      if(USCI1_TWI_Wait_TWIF(USCI1_HANDLE, Timeout) == Status_TIMEOUT)            //等待地址匹配
      {
        USCI1_TWI_AcknowledgeConfig(DISABLE);            //关闭AA使能
        return Status_TIMEOUT;
      }

      do
      {
        if(USCI1_GetTWIStatus(USCI1_TWI_SlaveSendData) == SET)           //检测状态机状态
        {

          US1CON3 = *(USCI1_HANDLE->pTxBuffPtr.Size_u8 + USCI1_HANDLE->TxXferCount);             //TWI发送数据

          if(USCI1_TWI_Wait_TWIF(USCI1_HANDLE, Timeout) == Status_TIMEOUT)             //等待启动信号发送完毕
          {
            USCI1_TWI_AcknowledgeConfig(DISABLE);            //关闭AA使能
            return Status_TIMEOUT;
          }
          USCI1_HANDLE->TxXferCount++;

          if(USCI1_HANDLE->TxXferCount == USCI1_HANDLE->TxXferSize - 1)

            USCI1_TWI_AcknowledgeConfig(DISABLE);            //关闭AA使能

        }
        else if(USCI1_GetTWIStatus(USCI1_TWI_SlaveDisableACK) == SET)
        {

          USCI1_HANDLE->TxXferCount++;
        }
        else
        {
          USCI1_HANDLE->TxState = USCI1_STATE_ERROR;
          return Status_ERROR;
        }
      }
      while(USCI1_HANDLE->TxXferCount < USCI1_HANDLE->TxXferSize);

      if(USCI1_GetTWIStatus(USCI1_TWI_SlaveDisableACK) == RESET)           //检测状态机状态
      {
        USCI1_HANDLE->TxState = USCI1_STATE_ERROR;
        return Status_ERROR;
      }

      if(USCI1_HANDLE->TxXferCount == USCI1_HANDLE->TxXferSize)
      {
        USCI1_HANDLE->TxState = USCI1_STATE_READY;	//发送完成
        return Status_OK;
      }
      else
      {
        USCI1_HANDLE->TxState = USCI1_STATE_ERROR;//发生发送错误
        return Status_ERROR;
      }
    }
  }
  else
  {
    return Status_BUSY;
  }
}

/*****************************************************
*函数名称:StatusTypeDef USCI1_TWI_Master_Transmit_IT(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t slaveAddr, uint8_t* pData, uint8_t Size)
*函数功能:主机使用中断模式下发送大量数据时，先在main函数中调用此函数
*入口参数:
USCI1_HandleInfoDef*:USCI1_HANDLE:指针指向USCI1数据信息存放区
*出口参数:
StatusTypeDef状态枚举
*****************************************************/
StatusTypeDef USCI1_TWI_Master_Transmit_IT(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t slaveAddr, uint8_t* pData, uint8_t Size)
{
  if(USCI1_HANDLE->TxState == USCI1_STATE_READY)
  {
    /* 待发送数据长度必须大于0，否则返回错误状态 */
    if(((IE2 & 0x01) == 0) || (Size == 0U))
    {
      return Status_ERROR;
    }
    else
    {
      
      IE2 &= ~0x01;			//关闭中断

      USCI1_HANDLE->TxState = USCI1_STATE_WAIT;			//发送进程忙碌中
      USCI1_ClearFlag(USCI1_TWI_FLAG_TWIF);			 //发送前清除标志位
      USCI1_HANDLE->pTxBuffPtr.Size_u8 = pData;			//指向待发送数据的地址
      USCI1_HANDLE->TxXferSize = Size;			//更新待发送的数据量
      USCI1_HANDLE->TxXferCount = 0;			//发送计数器清零

      USCI1_TWI_Start();			//发送启动信号

      if(USCI1_TWI_Wait_TWIF(USCI1_HANDLE, 0xFFFFFFFF) == Status_TIMEOUT)            //等待启动信号发送完毕
      {
        /* 无论是否发送完成，都需要发送结束信号，防止主机占用总线 */
        USCI1_TWI_MasterModeStop();
        IE2 |= 0x01;	//开启中断
        return Status_TIMEOUT;
      }

      if(USCI1_GetTWIStatus(USCI1_TWI_MasterSendAddress) == RESET)           //检测状态机状态
      {
        USCI1_HANDLE->TxState = USCI1_STATE_ERROR;
        /* 无论是否发送完成，都需要发送结束信号，防止主机占用总线 */
        USCI1_TWI_MasterModeStop();
        IE2 |= 0x01;	//开启中断
        return Status_ERROR;
      }

      IE2 |= 0x01;						//开启中断
      US1CON3 = (slaveAddr << 1) & 0xFE;//发送地址和读写位

      return Status_OK;
    }
  }
  else
  {
    return Status_BUSY;
  }
}

/*****************************************************
*函数名称:StatusTypeDef USCI1_TWI_Master_Transmit_IRQHandler(USCI1_HandleInfoDef *USCI1_HANDLE)
*函数功能:发送8位数据时，主机中断模式下发送大量数据
*入口参数:
USCI1_HandleInfoDef*:USCI1_HANDLE:指针指向USCI1数据信息存放区
*出口参数:StatusTypeDef状态枚举
*****************************************************/
StatusTypeDef USCI1_TWI_Master_Transmit_IRQHandler(USCI1_HandleInfoDef* USCI1_HANDLE)
{
  if(USCI1_HANDLE->TxState == USCI1_STATE_BUSY)
  {
    if(USCI1_GetTWIStatus(USCI1_TWI_MasterSendData) == SET)
    {
      if(USCI1_HANDLE->TxXferCount < USCI1_HANDLE->TxXferSize)
      {
        USCI1_HANDLE->TxXferCount++;			//地址帧也作为数据计数
        US1CON3 = *(USCI1_HANDLE->pTxBuffPtr.Size_u8 + USCI1_HANDLE->TxXferCount);             //TWI发送数据
        return Status_BUSY;
      }
      else if(USCI1_HANDLE->RxXferCount == USCI1_HANDLE->RxXferSize)
      {
        /* 无论是否发送完成，都需要发送结束信号，防止主机占用总线 */
        USCI1_TWI_MasterModeStop();
        USCI1_HANDLE->TxState = USCI1_STATE_READY;
        return Status_OK;
      }
      else
      {
        /* 无论是否发送完成，都需要发送结束信号，防止主机占用总线 */
        USCI1_TWI_MasterModeStop();
        USCI1_HANDLE->TxState = USCI1_STATE_ERROR;
        return Status_OK;
      }
    }
    else if(USCI1_GetTWIStatus(USCI1_TWI_MasterReceivedaUACK) == SET)
    {
      /* 无论是否发送完成，都需要发送结束信号，防止主机占用总线 */
      USCI1_HANDLE->TxXferCount++;
      USCI1_TWI_MasterModeStop();
      if(USCI1_HANDLE->TxXferCount == USCI1_HANDLE->TxXferSize)
      {
        USCI1_HANDLE->TxState = USCI1_STATE_READY;
        return Status_OK;
      }
      else
      {
        USCI1_HANDLE->TxState = USCI1_STATE_ERROR;
        return Status_ERROR;
      }
    }
    else
    {
      USCI1_TWI_MasterModeStop();
      USCI1_HANDLE->TxState = USCI1_STATE_ERROR;
      return Status_ERROR;
    }
  }
  else if(USCI1_HANDLE->TxState == USCI1_STATE_WAIT)
  {
    //地址成功响应
    USCI1_HANDLE->TxState = USCI1_STATE_BUSY;
    US1CON3 = *(USCI1_HANDLE->pTxBuffPtr.Size_u8 + USCI1_HANDLE->TxXferCount);
    return Status_BUSY;
  }
  else
  {
    return Status_ERROR;//返回标志位
  }
}

/*****************************************************
*函数名称:StatusTypeDef USCI1_TWI_Slave_Transmit_IT(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pData, uint8_t Size)
*函数功能:从机使用中断模式下发送大量数据时，先在main函数中调用此函数
* 注
*入口参数:*USCI1_HANDLE 指针指向USCI1数据信息存放区
*出口参数:void
*****************************************************/
StatusTypeDef USCI1_TWI_Slave_Transmit_IT(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pData, uint8_t Size)
{
  /* 检查一个发送进程是否正在进行 */
  if(USCI1_HANDLE->TxState == USCI1_STATE_READY)
  {
    /* 待发送数据长度必须大于0，否则返回错误状态 */
    if(((IE2 & 0x01) == 0) || (Size == 0U))
    {
      return Status_ERROR;
    }
    else
    {
      

      USCI1_TWI_AcknowledgeConfig(DISABLE);         //开启AA
      USCI1_ClearFlag(USCI1_TWI_FLAG_TWIF);			 //发送前清除标志位
      USCI1_TWI_SlaveClockExtension(ENABLE);            //开启时钟延长
      USCI1_HANDLE->TxState = USCI1_STATE_WAIT;			//发送进程忙碌中
      USCI1_HANDLE->pTxBuffPtr.Size_u8 = pData;			//指向待发送数据的地址
      USCI1_HANDLE->TxXferSize = Size;			//更新待发送的数据量
      USCI1_HANDLE->TxXferCount = 0;			//发送计数器清零

      USCI1_TWI_AcknowledgeConfig(ENABLE);         //开启AA

      return Status_OK;;
    }
  }
  else
  {
    return Status_ERROR;
  }
}

/*****************************************************
*函数名称:StatusTypeDef USCI1_TWI_Slave_Transmit_IRQHandler(USCI1_HandleInfoDef *USCI1_HANDLE)
*函数功能:发送8位数据时，从机中断模式下发送大量数据
*入口参数:*USCI1_HANDLE 指针指向USCI1数据信息存放区
*出口参数:StatusTypeDef状态枚举
*****************************************************/
StatusTypeDef USCI1_TWI_Slave_Transmit_IRQHandler(USCI1_HandleInfoDef* USCI1_HANDLE)
{
  if(USCI1_HANDLE->TxState == USCI1_STATE_BUSY)
  {

    if(USCI1_GetTWIStatus(USCI1_TWI_SlaveSendData) == SET)
    {
      if(USCI1_HANDLE->TxXferCount < USCI1_HANDLE->TxXferSize)
      {
        USCI1_HANDLE->TxXferCount++;			//第一次中断是接受到地址了
        US1CON3 = *(USCI1_HANDLE->pTxBuffPtr.Size_u8 + USCI1_HANDLE->TxXferCount);
        if(USCI1_HANDLE->TxXferCount == USCI1_HANDLE->TxXferSize - 1)
        {
          USCI1_TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
        }
        return Status_BUSY;
      }
      else
      {
        USCI1_TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
        USCI1_HANDLE->TxState = USCI1_STATE_ERROR;
        return Status_ERROR;
      }
    }
    /*
    1.但数据传输过程中，其他程序修改了AA控制位
    2.接收到主机回来的UACK */
    else if((USCI1_GetTWIStatus(USCI1_TWI_SlaveDisableACK) == SET) || (USCI1_GetTWIStatus(USCI1_TWI_SlaveReceivedaUACK) == SET))
    {
      USCI1_TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
		 USCI1_HANDLE->TxXferCount++;
      if(USCI1_HANDLE->TxXferCount == USCI1_HANDLE->TxXferSize)			//所有数据已发送
      {
        USCI1_HANDLE->TxState = USCI1_STATE_READY;
        return Status_OK;
      }
      else
      {
        USCI1_HANDLE->TxState = USCI1_STATE_ERROR;
        return Status_ERROR;
      }
    }
    else
    {
      USCI1_TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
      /* 以下情况未发送过程出错
      1.数据发送后接受到UACK
      2.TWI不是工作在从机发送状态 */
      USCI1_HANDLE->TxState = USCI1_STATE_ERROR;
      return Status_ERROR;
    }
  }
  else if(USCI1_HANDLE->TxState == USCI1_STATE_WAIT)
  {
    if(USCI1_GetTWIStatus(USCI1_TWI_SlaveSendData) == SET)
    {
      US1CON3 = *(USCI1_HANDLE->pTxBuffPtr.Size_u8 + USCI1_HANDLE->TxXferCount);
      USCI1_HANDLE->TxState = USCI1_STATE_BUSY;
    }
    return Status_BUSY;
  }
  else
  {
    return Status_ERROR;//返回标志位
  }
}

/*****************************************************
*函数名称:StatusTypeDef USCI1_TWI_Master_Receive(USCI1_HandleInfoDef* USCI1_HANDLE,uint8_t slaveAddr, uint8_t* pData, uint8_t Size,uint32_t Timeout)
*函数功能:接收8位数据时，主机轮询模式下接收大量数据
*入口参数:*USCI1_HANDLE 指针指向USCI1数据信息存放区
					 Timeout    超时时间设置
*出口参数:StatusTypeDef状态枚举
*****************************************************/
StatusTypeDef USCI1_TWI_Master_Receive(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t slaveAddr, uint8_t* pData, uint8_t Size, uint32_t Timeout)
{
  /* 检查一个接收进程是否正在进行 */
  if(USCI1_HANDLE->RxState == USCI1_STATE_READY)
  {
    /* 待接收数据长度必须大于0，否则返回错误状态 */
    if((IE2 & 0x01 != 0) || (Size == 0U))
    {
      return Status_ERROR;
    }

    USCI1_HANDLE->RxState = USCI1_STATE_BUSY;			//发送进程忙碌中
    USCI1_ClearFlag(USCI1_TWI_FLAG_TWIF);			 //发送前清除标志位
    USCI1_TWI_AcknowledgeConfig(ENABLE);         //开启AA使能位
    USCI1_HANDLE->pRxBuffPtr.Size_u8 = pData;			//指向待发送数据的地址
    USCI1_HANDLE->RxXferSize = Size;			//更新待发送的数据量
    USCI1_HANDLE->RxXferCount = 0;			//发送计数器清零

    USCI1_TWI_Start();			//发送启动信号
    if(USCI1_TWI_Wait_TWIF(USCI1_HANDLE, Timeout) == Status_TIMEOUT)            //等待启动信号发送完毕
    {
      USCI1_TWI_AcknowledgeConfig(DISABLE);
      return Status_TIMEOUT;
    }

    if(USCI1_GetTWIStatus(USCI1_TWI_MasterSendAddress) == RESET)           //检测状态机状态
    {
      USCI1_HANDLE->RxState = USCI1_STATE_ERROR;
      USCI1_TWI_AcknowledgeConfig(DISABLE);
      return Status_ERROR;
    }

    /* 发送地址帧过程 */
    US1CON3 = (slaveAddr << 1) | 0x01;//发送地址和读写位
    if(USCI1_TWI_Wait_TWIF(USCI1_HANDLE, Timeout) == Status_TIMEOUT)            //等待信号发送完毕
    {
      /* 无论是否发送完成，都需要发送结束信号，防止主机占用总线 */
		 USCI1_TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
      USCI1_TWI_MasterModeStop();
      return Status_TIMEOUT;
    }

    if(USCI1_GetTWIStatus(USCI1_TWI_MasterReceivedaData) == RESET)           //检测状态机状态
    {
      USCI1_HANDLE->RxState = USCI1_STATE_ERROR;
      /* 无论是否发送完成，都需要发送结束信号，防止主机占用总线 */
		 USCI1_TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
      USCI1_TWI_MasterModeStop();
      return Status_ERROR;
    }

    /* 数据接收过程 */
    do
    {
      if(USCI1_TWI_Wait_TWIF(USCI1_HANDLE, Timeout) == Status_TIMEOUT)            //等待信号发送完毕
      {
        /* 无论是否发送完成，都需要发送结束信号，防止主机占用总线 */
			USCI1_TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
        USCI1_TWI_MasterModeStop();
        return Status_TIMEOUT;
      }

      if(USCI1_GetTWIStatus(USCI1_TWI_MasterReceivedaData) == RESET)           //检测状态机状态
      {
        USCI1_HANDLE->RxState = USCI1_STATE_ERROR;
        /* 无论是否发送完成，都需要发送结束信号，防止主机占用总线 */
			USCI1_TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
        USCI1_TWI_MasterModeStop();
        return Status_ERROR;
      }

      *(USCI1_HANDLE->pRxBuffPtr.Size_u8 + USCI1_HANDLE->RxXferCount) = US1CON3;             //TWI接收数据
      USCI1_HANDLE->RxXferCount++;
      if(USCI1_HANDLE->RxXferCount == USCI1_HANDLE->RxXferSize - 1)
      {
        USCI1_TWI_AcknowledgeConfig(DISABLE);                                     //关闭AA
        if(USCI1_TWI_Wait_TWIF(USCI1_HANDLE, Timeout) == Status_TIMEOUT)            //等待信号发送完毕
        {
          /* 无论是否发送完成，都需要发送结束信号，防止主机占用总线 */
			  USCI1_TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
          USCI1_TWI_MasterModeStop();
          return Status_TIMEOUT;
        }
        if(USCI1_GetTWIStatus(USCI1_TWI_MasterReceivedaUACK) == RESET)           //检测状态机状态
        {
          USCI1_HANDLE->RxState = USCI1_STATE_ERROR;
          /* 无论是否发送完成，都需要发送结束信号，防止主机占用总线 */
			  USCI1_TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
          USCI1_TWI_MasterModeStop();
          return Status_ERROR;
        }

        *(USCI1_HANDLE->pRxBuffPtr.Size_u8 + USCI1_HANDLE->RxXferCount) = US1CON3;             //TWI接收数据
        USCI1_HANDLE->RxXferCount++;
      }
    }
    while(USCI1_HANDLE->RxXferCount < USCI1_HANDLE->RxXferSize);
    /* 无论是否发送完成，都需要发送结束信号，防止主机占用总线 */
	 USCI1_TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
    USCI1_TWI_MasterModeStop();

    if(USCI1_HANDLE->RxXferCount == USCI1_HANDLE->RxXferSize)
    {
      USCI1_HANDLE->RxState = USCI1_STATE_READY;	//发送完成
      return Status_OK;
    }
    else
    {
      USCI1_HANDLE->RxState = USCI1_STATE_ERROR;//发生发送错误
      return Status_ERROR;
    }
  }
  else
  {
    return Status_BUSY;
  }
}


/*****************************************************
*函数名称:StatusTypeDef USCI1_TWI_Slave_Receive(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout)
*函数功能:接收8位数据时，从机轮询模式下接收大量数据
*入口参数:
USCI1_HandleInfoDef:*USCI1_HANDLE:指针指向USCI1数据信息存放区
uint32_t:Timeout:超时时间设置
*出口参数:StatusTypeDef状态枚举
*****************************************************/
StatusTypeDef USCI1_TWI_Slave_Receive(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout)
{
  if(USCI1_HANDLE->RxState == USCI1_STATE_READY)
  {
    /* 待发送数据长度必须大于0，否则返回错误状态 */
    if((IE2 & 0x01 != 0) || (Size == 0U))
    {
      return Status_ERROR;
    }

    USCI1_HANDLE->RxState = USCI1_STATE_BUSY;			//发送进程忙碌中
    USCI1_ClearFlag(USCI1_TWI_FLAG_TWIF);			 //发送前清除标志位
    USCI1_TWI_AcknowledgeConfig(ENABLE);         //开启AA使能位
    USCI1_HANDLE->pRxBuffPtr.Size_u8 = pData;			//指向待发送数据的地址
    USCI1_HANDLE->RxXferSize = Size;			//更新待发送的数据量
    USCI1_HANDLE->RxXferCount = 0;			//发送计数器清零

    /* 接收地址工程 */
    if(USCI1_TWI_Wait_TWIF(USCI1_HANDLE, Timeout) == Status_TIMEOUT)            //等待信号发送完毕
    {
      /* 无论是否发送完成，都需要发送结束信号，防止主机占用总线 */
      USCI1_TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
      return Status_TIMEOUT;
    }

    if(USCI1_GetTWIStatus(USCI1_TWI_SlaveReceivedaData) == RESET)           //检测状态机状态
    {
      USCI1_HANDLE->RxState = USCI1_STATE_ERROR;
      /* 无论是否发送完成，都需要发送结束信号，防止主机占用总线 */
      USCI1_TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
      return Status_ERROR;
    }

    /* 接收数据过程 */
    do
    {
      if(USCI1_TWI_Wait_TWIF(USCI1_HANDLE, Timeout) == Status_TIMEOUT)            //等待启动信号发送完毕
      {
        return Status_TIMEOUT;
      }

      if(USCI1_GetTWIStatus(USCI1_TWI_SlaveReceivedaData) == SET)           //检测状态机状态
      {
        *(USCI1_HANDLE->pRxBuffPtr.Size_u8 + USCI1_HANDLE->RxXferCount) = US1CON3;             //TWI接收数据
        USCI1_HANDLE->RxXferCount++;
        if(USCI1_HANDLE->RxXferCount == USCI1_HANDLE->RxXferSize - 1)
          USCI1_TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位,回主机UAC
      }
      else if(USCI1_GetTWIStatus(USCI1_TWI_SlaveIdle) == SET)
      {
        if(USCI1_HANDLE->RxXferCount == USCI1_HANDLE->RxXferSize - 1)
        {
          *(USCI1_HANDLE->pRxBuffPtr.Size_u8 + USCI1_HANDLE->RxXferCount) = US1CON3;
          USCI1_HANDLE->RxXferCount++;
        }
        else
        {
          USCI1_HANDLE->RxState = USCI1_STATE_ERROR;
          USCI1_TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
          return Status_ERROR;
        }
      }
      else
      {
        USCI1_HANDLE->RxState = USCI1_STATE_ERROR;
        USCI1_TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
        return Status_ERROR;
      }

    }
    while(USCI1_HANDLE->RxXferCount < USCI1_HANDLE->RxXferSize);

    if(USCI1_HANDLE->RxXferCount == USCI1_HANDLE->RxXferSize)
    {
      USCI1_HANDLE->RxState = USCI1_STATE_READY;	//发送完成
      return Status_OK;
    }
    else
    {
      USCI1_HANDLE->RxState = USCI1_STATE_ERROR;//发生发送错误
      return Status_ERROR;
    }
  }
  else
  {
    return Status_BUSY;
  }
}

/*****************************************************
*函数名称:StatusTypeDef USCI1_TWI_Master_Receive_IT(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t slaveAddr, uint8_t* pData, uint8_t Size)
*函数功能:主机使用中断模式下接收大量数据时，先在main函数中调用此函数
*入口参数:*USCI1_HANDLE 指针指向USCI1数据信息存放区
		   Size        存储数据长度
*出口参数:void
*****************************************************/
StatusTypeDef USCI1_TWI_Master_Receive_IT(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t slaveAddr, uint8_t* pData, uint8_t Size)
{
  /* 检查一个接收进程是否正在进行 */
  if(USCI1_HANDLE->RxState == USCI1_STATE_READY)
  {
    /* 待接收数据长度必须大于0，否则返回错误状态 */
    if(((IE2 & 0x01) == 0) || (Size == 0U))
    {
      return Status_ERROR;
    }
    
    IE2 &= ~0x01;	//关闭中断
    USCI1_HANDLE->RxState = USCI1_STATE_WAIT;			//发送进程忙碌中
    USCI1_ClearFlag(USCI1_TWI_FLAG_TWIF);			 //发送前清除标志位
    USCI1_HANDLE->pRxBuffPtr.Size_u8 = pData;			//指向待发送数据的地址
    USCI1_HANDLE->RxXferSize = Size;			//更新待发送的数据量
    USCI1_HANDLE->RxXferCount = 0;			//发送计数器清零
    USCI1_TWI_AcknowledgeConfig(ENABLE);         //开启AA
    USCI1_TWI_Start();			//发送启动信号

    if(USCI1_TWI_Wait_TWIF(USCI1_HANDLE, 0xFFFF) == Status_TIMEOUT)            //等待启动信号发送完毕
    {
      /* 无论是否发送完成，都需要发送结束信号，防止主机占用总线 */
		 USCI1_TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
      USCI1_TWI_MasterModeStop();
      IE2 |= 0x01;	//开启中断
      return Status_TIMEOUT;
    }

    if(USCI1_GetTWIStatus(USCI1_TWI_MasterSendAddress) == RESET)           //检测状态机状态
    {
      USCI1_HANDLE->TxState = USCI1_STATE_ERROR;
      /* 无论是否发送完成，都需要发送结束信号，防止主机占用总线 */
		 USCI1_TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
      USCI1_TWI_MasterModeStop();
      IE2 |= 0x01;	//开启中断
      return Status_ERROR;
    }

    /* 发送地址帧过程 */
    IE2 |= 0x01;	//开启中断
    US1CON3 = (slaveAddr << 1) | 0x01;//发送地址和读写位

    return Status_OK;
  }
  else
  {
    return Status_BUSY;
  }
}

/*****************************************************
*函数名称:StatusTypeDef USCI1_TWI_Master_Receive_IRQHandler(USCI1_HandleInfoDef *USCI1_HANDLE)
*函数功能:接收8位数据时，主机中断模式下接收大量数据
*入口参数:*USCI1_HANDLE 指针指向USCI1数据信息存放区
*出口参数:StatusTypeDef状态枚举
*****************************************************/
StatusTypeDef USCI1_TWI_Master_Receive_IRQHandler(USCI1_HandleInfoDef* USCI1_HANDLE)
{
  if(USCI1_HANDLE->RxState == USCI1_STATE_BUSY)
  {
    if(USCI1_GetTWIStatus(USCI1_TWI_MasterReceivedaData) == SET)           //检测状态机状态
    {
      if(USCI1_HANDLE->RxXferCount < USCI1_HANDLE->RxXferSize)
      {
        *(USCI1_HANDLE->pRxBuffPtr.Size_u8 + USCI1_HANDLE->RxXferCount) = US1CON3;             //TWI接收数据
        USCI1_HANDLE->RxXferCount++;
        if(USCI1_HANDLE->RxXferCount == USCI1_HANDLE->RxXferSize)
        {
          /* 无论是否发送完成，都需要发送结束信号，防止主机占用总线 */
			  USCI1_TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
          USCI1_TWI_MasterModeStop();
          USCI1_HANDLE->RxState = USCI1_STATE_READY;	//发送完成
          return Status_OK;
        }
        return Status_BUSY;
      }
      else
      {
			USCI1_TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
        USCI1_TWI_MasterModeStop();
        USCI1_HANDLE->RxState = USCI1_STATE_ERROR;//发生发送错误
        return Status_ERROR;
      }
    }
  }
  else if(USCI1_HANDLE->RxState == USCI1_STATE_WAIT)
  {
    if(USCI1_GetTWIStatus(USCI1_TWI_MasterReceivedaData) == SET)
    {
      USCI1_HANDLE->RxState = USCI1_STATE_BUSY;
    }
    return Status_BUSY;
  }
  return Status_ERROR;
}


/*****************************************************
*函数名称:void USCI1_TWI_Slave_Receive_IT(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pData, uint8_t Size))
*函数功能:从机使用中断模式下接收大量数据时，先在main函数中调用此函数
*入口参数:
*USCI1_HANDLE 指针指向USCI1数据信息存放区
		   *pData	指针指向存储区
		   Size        存储数据长度
*出口参数:void
*****************************************************/
StatusTypeDef USCI1_TWI_Slave_Receive_IT(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pData, uint8_t Size)
{
  if(USCI1_HANDLE->RxState == USCI1_STATE_READY)
  {
    /* 待发送数据长度必须大于0，否则返回错误状态 */
    if(((IE2 & 0x01) == 0) || (Size == 0U))
    {
      return Status_ERROR;
    }
    
    USCI1_TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
    USCI1_ClearFlag(USCI1_TWI_FLAG_TWIF);			 //发送前清除标志位
    USCI1_HANDLE->RxState = USCI1_STATE_WAIT;			//发送进程忙碌中
    USCI1_HANDLE->pRxBuffPtr.Size_u8 = pData;			//指向待发送数据的地址
    USCI1_HANDLE->RxXferSize = Size;			//更新待发送的数据量
    USCI1_HANDLE->RxXferCount = 0;			//发送计数器清零
    USCI1_TWI_AcknowledgeConfig(ENABLE);         //开启AA使能位

    return Status_OK;
  }
  else
  {
    return Status_BUSY;
  }
}

/*****************************************************
*函数名称:StatusTypeDef USCI1_TWI_Slave_Receive_IRQHandler(USCI1_HandleInfoDef* USCI1_HANDLE)
*函数功能:接收8位数据时，从机中断模式下接收大量数据
*入口参数:
USCI1_HandleInfoDef:*USCI1_HANDLE 指针指向USCI1数据信息存放区
*出口参数:StatusTypeDef状态枚举
*****************************************************/
StatusTypeDef USCI1_TWI_Slave_Receive_IRQHandler(USCI1_HandleInfoDef* USCI1_HANDLE)
{
  if(USCI1_HANDLE->RxState == USCI1_STATE_BUSY)
  {
    if(USCI1_GetTWIStatus(USCI1_TWI_SlaveReceivedaData) == SET)           //检测状态机状态
    {
      if(USCI1_HANDLE->RxXferCount < USCI1_HANDLE->RxXferSize)
      {
        *(USCI1_HANDLE->pRxBuffPtr.Size_u8 + USCI1_HANDLE->RxXferCount) = US1CON3;             //TWI发送数据
        USCI1_HANDLE->RxXferCount++;
        if(USCI1_HANDLE->RxXferCount == USCI1_HANDLE->RxXferSize - 1)
        {
          USCI1_TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位,回主机UACK
        }
      }
      else
      {
        USCI1_TWI_AcknowledgeConfig(DISABLE);
        return Status_ERROR;
      }
      return Status_BUSY;
    }
    else if(USCI1_GetTWIStatus(USCI1_TWI_SlaveIdle) == SET)
    {
      if(USCI1_HANDLE->RxXferCount == USCI1_HANDLE->RxXferSize - 1)
      {
        *(USCI1_HANDLE->pRxBuffPtr.Size_u8 + USCI1_HANDLE->RxXferCount) = US1CON3;
        USCI1_HANDLE->RxXferCount++;
        USCI1_TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位,回主机UACK
        USCI1_HANDLE->RxState = USCI1_STATE_READY;
        return Status_OK;
      }
      else
      {
        USCI1_TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
        USCI1_HANDLE->RxState = USCI1_STATE_ERROR;
        return Status_ERROR;
      }
    }
    else
    {
      USCI1_HANDLE->RxState = USCI1_STATE_ERROR;
      USCI1_TWI_AcknowledgeConfig(DISABLE);         //关闭AA使能位
      return Status_ERROR;
    }
  }
  else if(USCI1_HANDLE->RxState == USCI1_STATE_WAIT)
  {
    USCI1_HANDLE->RxState = USCI1_STATE_BUSY;
    return Status_BUSY;
  }
  else
  {
    return Status_ERROR;
  }
}

/**************************************************
*函数名称:void USCI1_UART_Init(uint32_t UARTFsys, uint32_t BaudRate, USCI1_UART_Mode_TypeDef Mode, USCI1_UART_RX_TypeDef RxMode)
*函数功能:UART初始化配置函数
*入口参数:
uint32_t:UARTFsys:系统时钟频率
uint32_t:BaudRate:波特率
USCI1_UART_Mode_TypeDef:Mode:UART1工作模式
USCI1_UART_RX_TypeDef:RxMode:接收允许选择
*出口参数:void
**************************************************/
void USCI1_UART_Init(uint32_t UARTFsys, uint32_t BaudRate, USCI1_UART_Mode_TypeDef Mode,
                     USCI1_UART_RX_TypeDef RxMode)
{
  OTCON |= 0xC0;
  US1CON0 = US1CON0 & 0X0F | Mode | RxMode;

  if(Mode == USCI1_UART_Mode_8B)
  {
    if(BaudRate == USCI1_UART_BaudRate_FsysDIV12)
    {
      US1CON0 &= 0XDF;
    }
    else if(BaudRate == USCI1_UART_BaudRate_FsysDIV4)
    {
      US1CON0 |= 0X20;
    }
  }
  else
  {
    US1CON2 = UARTFsys / BaudRate / 256;
    US1CON1 = UARTFsys / BaudRate % 256;
  }
}

/*****************************************************
*函数名称:void USCI1_UART_SendData8(uint8_t Data)
*函数功能:USCI1 UART1发送8位数据
*入口参数:
uint8_t:Data:发送的数据
*出口参数:void
*****************************************************/
void USCI1_UART_SendData8(uint8_t Data)
{
  US1CON3 = Data;
}

/*****************************************************
*函数名称:uint8_t USCI1_UART_ReceiveData8(void)
*函数功能:获得US1CON3中的值
*入口参数:void
*出口参数:
uint8_t:接收的数据
*****************************************************/
uint8_t USCI1_UART_ReceiveData8(void)
{
  return US1CON3;
}

/*****************************************************
*函数名称:void USCI1_UART_SendData9(uint16_t Data)
*函数功能:UART1发送9位数据
*入口参数:
uint16_t:Data:发送的数据
*出口参数:void
*****************************************************/
void USCI1_UART_SendData9(uint16_t Data)
{
  uint8_t Data_9Bit;
  Data_9Bit = (Data >> 8);

  if(Data_9Bit)
  {
    US1CON0 |= 0x08;
  }
  else
  {
    US1CON0 &= 0xf7;
  }

  US1CON3 = (uint8_t)Data;
}

/*****************************************************
*函数名称:uint16_t USCI1_UART_ReceiveData9(void)
*函数功能:获得US1CON3中的值及第九位的值
*入口参数:void
*出口参数:
uint16_t:接收的数据
*****************************************************/
uint16_t USCI1_UART_ReceiveData9(void)
{
  uint16_t Data9;
  Data9 = US1CON3 + ((uint16_t)(US1CON0 & 0X04) << 6);
  return Data9;
}

/*****************************************************
*函数名称:StatusTypeDef  USCI1_UART_Transmit(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t *pData, uint8_t Size, uint32_t Timeout)
*函数功能:UART在轮询模式下发送大量数据
*入口参数:
USCI1_HandleInfoDef*:USCI1_HANDLE:指针指向UART数据信息存放区
uint8_t *:pData:待发送数据
uint16_t:Size:待发送的数据量
uint32_t:Timeout:超时时间设置
*出口参数:
StatusTypeDef:函数执行状态
*****************************************************/
StatusTypeDef USCI1_UART_Transmit(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout)
{
  uint32_t delaytime = 0;
  /* 检查一个发送进程是否正在进行 */
  if(USCI1_HANDLE->TxState == USCI1_STATE_READY)
  {
    /* 检查发送数据量是否为0 */
    if(((IE2 & 0x01) != 0) || (Size == 0U))
    {
      return  Status_ERROR;
    }

    USCI1_HANDLE->TxState = USCI1_STATE_BUSY;			//发送进程忙碌中
    USCI1_ClearFlag(USCI1_UART_FLAG_TI); //发送前清除发送中断标志，写1/写0清零
    USCI1_HANDLE->pTxBuffPtr.Size_u8 = pData;			//指向待发送数据的地址
    USCI1_HANDLE->TxXferSize = Size;			//更新待发送的数据量
    USCI1_HANDLE->TxXferCount = 0;			//发送计数器清零

    while(USCI1_HANDLE->TxXferCount < USCI1_HANDLE->TxXferSize)//判断是否接收所有数据
    {
      if((US1CON0 & 0xC0) == USCI1_UART_Mode_11B)
      {
        /* 发送9位数据 */
        USCI1_UART_SendData9(*(USCI1_HANDLE->pTxBuffPtr.Size_u16 + USCI1_HANDLE->TxXferCount));
      }
      else
      {
        /* 发送8位数据 */
        USCI1_UART_SendData8(*(USCI1_HANDLE->pTxBuffPtr.Size_u8 + USCI1_HANDLE->TxXferCount));
      }

      /* 等待发送完成 */
      delaytime = 0;
      while(!(US1CON0 & 0x02))
      {
        if(delaytime++ > Timeout)
        {
          USCI1_HANDLE->TxState = USCI1_STATE_TIMEOUT;//发送超时
          return Status_TIMEOUT;
        }
      }

      USCI1_ClearFlag(USCI1_UART_FLAG_TI); //发送中断标志清除，写1/写0清零
      USCI1_HANDLE->TxXferCount ++;	//发送数据量计数
    }

    if(USCI1_HANDLE->TxXferCount == USCI1_HANDLE->TxXferSize)
    {
      USCI1_HANDLE->TxState = USCI1_STATE_READY;	//发送完成
      return Status_OK;
    }
    else
    {
      USCI1_HANDLE->TxState = USCI1_STATE_ERROR;//发生发送错误
      return Status_ERROR;
    }
  }
  else
  {
    return Status_BUSY;//返回标志位
  }
}


/*****************************************************
*函数名称:StatusTypeDef USCI1_UART_Transmit_IT(USCI1_HandleInfoDef *USCI1_HANDLE, uint8_t *pData, uint8_t Size)
*函数功能:UART在中断模式下发送大量数据时，先在main函数中调用此函数
*入口参数:
USCI1_HandleInfoDef*:USCI1_HANDLE:指针指向UART数据信息存放区
uint8_t *:pData:待发送数据
uint16_t:Size:待发送的数据量
*出口参数:
StatusTypeDef:函数执行状态
*****************************************************/
StatusTypeDef USCI1_UART_Transmit_IT(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pData, uint8_t Size)
{
  /* 检查一个发送进程是否正在进行 */
  if(USCI1_HANDLE->TxState == USCI1_STATE_READY)
  {
    /* 没有开启USCI1中断或发送数据量大小为0，返回错误 */
    if(((IE2 & 0x01) == 0) || (Size == 0U))
    {
      return Status_ERROR;
    }

    USCI1_HANDLE->TxState = USCI1_STATE_BUSY;
    USCI1_HANDLE->pTxBuffPtr.Size_u8 = pData;			//指向待发送数据的地址
    USCI1_HANDLE->TxXferSize = Size;			//更新待发送的数据量
    USCI1_HANDLE->TxXferCount = 0;			//发送计数器清零

    /* 发送第1帧数据 */
    if((US1CON0 & 0xC0) == USCI1_UART_Mode_11B)
    {
      /* 发送9位数据 */
      USCI1_UART_SendData9(*(USCI1_HANDLE->pTxBuffPtr.Size_u16 + USCI1_HANDLE->TxXferCount));
    }
    else
    {
      /* 发送8位数据 */
      USCI1_UART_SendData8(*(USCI1_HANDLE->pTxBuffPtr.Size_u8 + USCI1_HANDLE->TxXferCount));
    }
    return Status_OK;
  }
  else
  {
    return Status_BUSY;//返回标志位
  }
}

/*****************************************************
*函数名称:StatusTypeDef  USCI1_UART_Transmit_IRQHandler(USCI1_HandleInfoDef *USCI1_HANDLE)
*函数功能:UART在中断模式下发送大量数据时，在中断服务函数中调用
*	注：该函数调用需要判断中断标志位是否置起
*入口参数:*USCI1_HANDLE 指针指向UART数据信息存放区
*出口参数:
StatusTypeDef:函数执行状态
*****************************************************/
StatusTypeDef USCI1_UART_Transmit_IRQHandler(USCI1_HandleInfoDef* USCI1_HANDLE)
{
  /* 处于发送线程 */
  if(USCI1_HANDLE->TxState == USCI1_STATE_BUSY)
  {
    USCI1_HANDLE->TxXferCount++;
    /* 判断上一次发送是否是最后一次 */
    if(USCI1_HANDLE->TxXferCount < USCI1_HANDLE->TxXferSize)
    {
      /* 待发送数据量未为0，继续发送 */
      if((US1CON0 & 0xC0) == USCI1_UART_Mode_11B)
      {
        /* 发送9位数据 */
        USCI1_UART_SendData9(*(USCI1_HANDLE->pTxBuffPtr.Size_u16 + USCI1_HANDLE->TxXferCount));
      }
      else
      {
        /* 发送8位数据 */
        USCI1_UART_SendData8(*(USCI1_HANDLE->pTxBuffPtr.Size_u8 + USCI1_HANDLE->TxXferCount));
      }
      return Status_BUSY;
    }
    else if(USCI1_HANDLE->TxXferCount == USCI1_HANDLE->TxXferSize)
    {
      /* 发送完成 */
      USCI1_HANDLE->TxState = USCI1_STATE_READY;
      return Status_OK;
    }
    else
    {
      /* 发送数据量为0时还发送数据，返回错误 */
      USCI1_HANDLE->TxState = USCI1_STATE_ERROR;
      return Status_ERROR;
    }
  }
  else
  {
    return Status_BUSY;
  }
}

/*****************************************************
*函数名称:StatusTypeDef USCI1_UART_Receive(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t *pData, uint8_t Size, uint32_t Timeout)
*函数功能:UART在轮询模式下接收大量数据
*入口参数:
USCI1_USCI1_HANDLEInfoDef*:USCI1_HANDLE:指针指向USCI1_UART数据信息存放区
uint8_t *:pData:接收数据的存放区
uint16_t:Size:待接收的数据量
uint32_t:Timeout:超时时间设置
*出口参数:
StatusTypeDef:函数执行状态
*****************************************************/
StatusTypeDef USCI1_UART_Receive(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pData, uint8_t Size, uint32_t Timeout)
{
  uint32_t delaytime = 0;
  /* 检查接收进程正在运行 */
  if(USCI1_HANDLE->RxState == USCI1_STATE_READY)
  {
    /* 检查接收数据量大小和是否开启接收使能 */
    if(((IE2 & 0x01) != 0) || (Size == 0U) || ((US1CON0 & 0x10) != USCI1_UART_RX_ENABLE))
    {
      return  Status_ERROR;
    }

    USCI1_HANDLE->RxState = USCI1_STATE_BUSY;			//发送进程忙碌中
    USCI1_ClearFlag(USCI1_UART_FLAG_RI);			 //接收前清除接收中断标志
    USCI1_HANDLE->pRxBuffPtr.Size_u8 = pData;			//指向待发送数据的地址
    USCI1_HANDLE->RxXferSize = Size;			//更新待发送的数据量
    USCI1_HANDLE->RxXferCount = 0;			//发送计数器清零

    while(USCI1_HANDLE->RxXferCount < USCI1_HANDLE->RxXferSize) //判断是否接收所有数据
    {
      if(USCI1_GetFlagStatus(USCI1_UART_FLAG_RI)) //判断接收标志位
      {
        USCI1_ClearFlag(USCI1_UART_FLAG_RI);			//接收标志位清零

        /* 待接收数据量未为0，继续发送 */
        if((US1CON0 & 0xC0) == USCI1_UART_Mode_11B)
        {
          /* 接收9位数据 */
          *(USCI1_HANDLE->pRxBuffPtr.Size_u16 + USCI1_HANDLE->RxXferCount) = USCI1_UART_ReceiveData9();
        }
        else
        {
          /* 接收8位数据 */
          *(USCI1_HANDLE->pRxBuffPtr.Size_u8 + USCI1_HANDLE->RxXferCount) = USCI1_UART_ReceiveData8();
        }

        USCI1_HANDLE->RxXferCount++;	//接收数据量计数
        delaytime = 0;//收到数据，超时计数清零
      }
      if(delaytime++ > Timeout)//计时溢出
      {
        USCI1_HANDLE->RxState = USCI1_STATE_TIMEOUT;//发送超时
        return Status_TIMEOUT;
      }
    }

    if(USCI1_HANDLE->RxXferCount == USCI1_HANDLE->RxXferSize)
    {
      USCI1_HANDLE->RxState = USCI1_STATE_READY;	//发送完成
      return Status_OK;
    }
    else
    {
      USCI1_HANDLE->RxState = USCI1_STATE_ERROR;//发生发送错误
      return Status_ERROR;
    }
  }
  else
  {
    return Status_BUSY;//返回标志位
  }
}

/*****************************************************
*函数名称:StatusTypeDef USCI1_UART_Receive_IT(USCI1_HandleInfoDef *USCI1_HANDLE, uint8_t *pData, uint8_t Size)
*函数功能:UART在中断模式下接收大量数据时，先在main函数中调用此函数
*入口参数:
USCI1_USCI1_HANDLEInfoDef*:USCI1_HANDLE:指针指向UART数据信息存放区
uint8_t *:pData:接收数据的存放区
uint16_t:Size:待接收的数据量
*出口参数:
StatusTypeDef:函数执行状态
*****************************************************/
StatusTypeDef USCI1_UART_Receive_IT(USCI1_HandleInfoDef* USCI1_HANDLE, uint8_t* pData, uint8_t Size)
{
  /* 检查一个接收进程是否正在进行 */
  if(USCI1_HANDLE->RxState == USCI1_STATE_READY)
  {
    /* 检查是否开启USCI1_UART中断或发送数据量大小为0或是否开启接收使能，返回错误 */
    if(((IE2 & 0x01) == 0) || (Size == 0U) || ((US1CON0 & 0x10) != USCI1_UART_RX_ENABLE))
    {
      return Status_ERROR;
    }

    USCI1_HANDLE->RxState = USCI1_STATE_BUSY;
    USCI1_HANDLE->pRxBuffPtr.Size_u8 = pData;			//指向接收数据的存放地址
    USCI1_HANDLE->RxXferSize = Size;			//更新待接收的数据量
    USCI1_HANDLE->RxXferCount = 0;			//发送计数器清零

    return Status_OK;
  }
  else
  {
    return Status_BUSY;//返回标志位
  }
}

/*****************************************************
*函数名称:StatusTypeDef USCI1_UART_Receive_IRQHandler(USCI1_HandleInfoDef* USCI1_HANDLE)
*函数功能:UART在中断模式下接收大量数据时，在中断服务函数中调用
*	注：该函数调用需要判断中断标志位是否置起
*入口参数:
USCI1_HandleInfoDef*:USCI1_HANDLE:指针指向USCI1数据信息存放区
*出口参数:
StatusTypeDef:函数执行状态
*****************************************************/
StatusTypeDef USCI1_UART_Receive_IRQHandler(USCI1_HandleInfoDef* USCI1_HANDLE)
{
  /* 检查一个接收进程是否正在进行 */
  if(USCI1_HANDLE->RxState == USCI1_STATE_BUSY)
  {
    /* 处于接收线程，检查待接收数据量是否为0 */
    if(USCI1_HANDLE->RxXferCount < USCI1_HANDLE->RxXferSize)
    {
      /* 待接收数据量未为0，继续接收 */
      if((US1CON0 & 0xC0) == USCI1_UART_Mode_11B)
      {
        /* 接收9位数据 */
        *(USCI1_HANDLE->pRxBuffPtr.Size_u16 + USCI1_HANDLE->RxXferCount) = USCI1_UART_ReceiveData9();
      }
      else
      {
        /* 接收8位数据 */
        *(USCI1_HANDLE->pRxBuffPtr.Size_u8 + USCI1_HANDLE->RxXferCount) = USCI1_UART_ReceiveData8();
      }
      USCI1_HANDLE->RxXferCount ++;
      /* 判断上一次发送是否是最后一次 */
      if(USCI1_HANDLE->RxXferCount == USCI1_HANDLE->RxXferSize)
      {
        /* 接收完成 */
        USCI1_HANDLE->RxState = USCI1_STATE_READY;
				return Status_OK;
      }
       return Status_ERROR;
    }
    else
    {
      /* 接收数据量为0时还接收数据，返回错误 */
      USCI1_HANDLE->RxState = USCI1_STATE_ERROR;
      return Status_ERROR;
    }
  }
  else
  {
    return Status_BUSY;
  }
}

/********************************* 中断相关 **************************************************/
/*****************************************************
*函数名称:void USCI1_ITConfig(FunctionalState NewState, PriorityStatus Priority)
*函数功能:USCI1中断初始化
*入口参数:
FunctionalState:NewState:中断使能/关闭选择
PriorityStatus:Priority:中断优先级选择
*出口参数:void
*****************************************************/
void USCI1_ITConfig(FunctionalState NewState, PriorityStatus Priority)
{
  if(NewState != DISABLE)
  {
    IE2 |= 0x01;
  }
  else
  {
    IE2 &= 0xFE;
  }

  /************************************************************/
  if(Priority != LOW)
  {
    IP2 |= 0x01;
  }
  else
  {
    IP2 &= 0xFE;
  }
}

/*****************************************************
*函数名称:FlagStatus USCI1_GetFlagStatus(USCI1_Flag_TypeDef USCI1_FLAG)
*函数功能:获得USCI1标志状态
*入口参数:
USCI1_Flag_Typedef:USCI1_Flag:中断标志位选择
*出口参数:
FlagStatus:USCI1标志状态
*****************************************************/
FlagStatus USCI1_GetFlagStatus(USCI1_Flag_TypeDef USCI1_FLAG)
{
  FlagStatus bitstatus = RESET;
	if((OTCON & 0xC0)==0x40)      //SPI模式
	{
#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx)		
		
		if((USCI1_FLAG == USCI1_SPI_FLAG_SPIF) || (USCI1_FLAG == USCI1_SPI_FLAG_WCOL))
			
#elif	defined(SC95F8x2x) || defined(SC95F7x2x) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)\
	|| defined (SC95F8x1xB) || defined (SC95F7x1xB)	|| defined (SC95F7619B) || defined(SC95FS52x) || defined (SC95R602)  || defined (SC95R605) \
	|| defined	(SC95F8x7x) || defined(SC95F7x7x)|| defined(SC95R503)
		
		if((USCI1_FLAG == USCI1_SPI_FLAG_SPIF) || (USCI1_FLAG == USCI1_SPI_FLAG_WCOL) || (USCI1_FLAG == USCI1_SPI_FLAG_TXE))
#endif		
		{
			if((USCI1_FLAG & US1CON1) != (uint8_t)RESET)
      {
        bitstatus = SET;
      }
      else
      {
        bitstatus = RESET;
      }		
		}	
	}else if((OTCON & 0xC0)==0x80)  //TWI模式
  {
		if(USCI1_FLAG == USCI1_TWI_FLAG_TXRXnE)
		{
			if((USCI1_FLAG & US1CON1) != (uint8_t)RESET)
      {
        bitstatus = SET;
      }
      else
      {
        bitstatus = RESET;
      }
		}
		else
    {
			if((USCI1_FLAG & US1CON0) != (uint8_t)RESET)
      {
        bitstatus = SET;
      }
      else
      {
        bitstatus = RESET;
      }
    }
	}else if((OTCON & 0xC0)==0xC0)  //UART模式
  {
    if((USCI1_FLAG & US1CON0) != (uint8_t)RESET)
    {
      bitstatus = SET;
    }
    else
    {
      bitstatus = RESET;
    }
  }
  return bitstatus;
}

/*****************************************************
*函数名称:void USCI1_ClearFlag(USCI1_Flag_TypeDef USCI1_FLAG)
*函数功能:清除USCI1标志状态
*入口参数:
USCI1_Flag_TypeDef:USCI1_FLAG:所需清除的标志位
*出口参数:void
*****************************************************/
void USCI1_ClearFlag(USCI1_Flag_TypeDef USCI1_FLAG)
{
	if((OTCON & 0xC0)==0x40)      //SPI模式
	{
#if defined(SC95F8x1x) || defined(SC95F7x1x) || defined(SC95FWxx)
		
		if((USCI1_FLAG == USCI1_SPI_FLAG_SPIF) || (USCI1_FLAG == USCI1_SPI_FLAG_WCOL))

#elif	defined(SC95F8x2x) || defined(SC95F7x2x) || defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)\
	|| defined (SC95F8x1xB) || defined (SC95F7x1xB)	|| defined (SC95F7619B) || defined(SC95FS52x) || defined (SC95R602)  || defined (SC95R605) \
	|| defined	(SC95F8x7x) || defined(SC95F7x7x)|| defined(SC95R503)
		
		if((USCI1_FLAG == USCI1_SPI_FLAG_SPIF) || (USCI1_FLAG == USCI1_SPI_FLAG_WCOL) || (USCI1_FLAG == USCI1_SPI_FLAG_TXE))
#endif
    {
		  US1CON1 &= (~USCI1_FLAG); //操作寄存器US1CON1	
		}		
	}else if((OTCON & 0xC0)==0x80)  //TWI模式
	{
		if(USCI1_FLAG == USCI1_TWI_FLAG_TXRXnE)
	  {
       US1CON1 &= (~USCI1_FLAG); //操作寄存器US1CON1
    }
		else
    {
       US1CON0 &= (~USCI1_FLAG); //操作寄存器US1CON0
    }	
	}else if((OTCON & 0xC0)==0xC0)  //UART模式
	{
	 if((USCI1_FLAG == USCI1_UART_FLAG_TI) || (USCI1_FLAG == USCI1_UART_FLAG_RI))
   {
#if defined(SC95F8x3x) || defined(SC95F7x3x) || defined (SC95F8x6x) || defined (SC95F7x6x)  || defined (SC95F8x1xB) || defined (SC95F7x1xB)\
		|| defined (SC95R602)  || defined (SC95R605) || defined (SC95F8x7x) || defined (SC95F7x7x)|| defined(SC95R503)
     US1CON0 = US1CON0  & 0xFC | USCI1_FLAG; //写1清零
#else
     US1CON0 &= (~USCI1_FLAG); //写0清零
#endif
   }
	}
}


/******************* (C) COPYRIGHT 2020 SinOne Microelectronics *****END OF FILE****/
