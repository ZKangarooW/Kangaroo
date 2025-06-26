#include "Drv_SPI.h"

/*
*****************************************************************
 * 函数原型：void Drv_SPI_Init(void)
 * 功    能：PSI初始化，启动SPI，否则开机第一次传输失败
*****************************************************************
*/
void Drv_SPI_Init(void)
{
    SPI2->CR1 |=  SPI_CR1_SPE;
}

/*
*****************************************************************
 * 函数原型：uint8_t SPI2_ReadWriteByte(uint8_t txdata)
 * 功    能：读写一个字节
 * 输    入：txdata：要写入的字节
 * 输    出：读取到的字节
 * 参    数：uint8_t txdata
*****************************************************************
*/
uint8_t SPI2_ReadWriteByte(uint8_t txdata)
{
    uint8_t rxdata;
    HAL_SPI_TransmitReceive(&hspi2, &txdata, &rxdata, 1, 55);
    return rxdata;
}

/*
*****************************************************************
 * 函数原型：void SPI2_Transmit(uint8_t *ucp_Data, uint16_t us_Size)
 * 功    能：发送数据
 * 输    入：*ucp_Data：数据数组 us_Size：长度
 * 参    数：uint8_t *ucp_Data, uint16_t us_Size
*****************************************************************
*/
void SPI2_Transmit(uint8_t *ucp_Data, uint16_t us_Size)
{
    HAL_SPI_Transmit(&hspi2, ucp_Data, us_Size, 55);
}

/*
*****************************************************************
 * 函数原型：void SPI2_Receive(uint8_t *ucp_Data, uint16_t us_Size)
 * 功    能：接收数据
 * 输    入：*ucp_Data：数据数组 us_Size：长度
 * 参    数：uint8_t *ucp_Data, uint16_t us_Size
*****************************************************************
*/
void SPI2_Receive(uint8_t *ucp_Data, uint16_t us_Size)
{
    HAL_SPI_Receive(&hspi2, ucp_Data, us_Size, 55);
}
