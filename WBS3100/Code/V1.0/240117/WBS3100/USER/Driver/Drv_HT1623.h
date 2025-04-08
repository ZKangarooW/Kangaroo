#ifndef __DRV_HT1623_H__
#define __DRV_HT1623_H__

#include "include.h"

/**********�궨��************/
#define  BIAS     0x52  //0b1000 0101 0010 1/3duty 4com 
#define  SYSDIS   0X00  //0b1000 0000 0000
#define  SYSEN    0X02  //0b1000 0000 0010
#define  LCDOFF   0X04  //0b1000 0000 0100
#define  LCDON    0X06  //0b1000 0000 0110
#define  XTAL     0x28  //0b1000 0010 1000
#define  RC256    0X30  //0b1000 0011 0000
#define  WDTDIS1  0X0A  //0b1000 0000 1010

#define Clr_1625_Cs  HAL_GPIO_WritePin(Ht1621_CS_GPIO_Port, Ht1621_CS_Pin, GPIO_PIN_RESET)//Ht1621_CS_Pin
#define Set_1625_Cs  HAL_GPIO_WritePin(Ht1621_CS_GPIO_Port, Ht1621_CS_Pin, GPIO_PIN_SET)

#define Clr_1625_Wr  HAL_GPIO_WritePin(Ht1621_WR_GPIO_Port, Ht1621_WR_Pin, GPIO_PIN_RESET)//Ht1621_WR_Pin
#define Set_1625_Wr  HAL_GPIO_WritePin(Ht1621_WR_GPIO_Port, Ht1621_WR_Pin, GPIO_PIN_SET)

#define Clr_1625_Dat HAL_GPIO_WritePin(Ht1621_DAT_GPIO_Port, Ht1621_DAT_Pin, GPIO_PIN_RESET)//Ht1621_DAT_Pin
#define Set_1625_Dat HAL_GPIO_WritePin(Ht1621_DAT_GPIO_Port, Ht1621_DAT_Pin, GPIO_PIN_SET)

/**********�ṹ��************/
/**********ȫ�ֱ�������******/
/**********�ֲ���������******/
/**********ȫ�ֺ���**********/
void Lcd_Init(void);//LCD��ʼ������lcd��������ʼ������
void Lcd_Clr(void);//LCD��������
void Lcd_All(void);//LCDȫ��ʾ����
void Write_Addr_Dat_N(unsigned char _addr, unsigned char _dat, unsigned char n);//��Ļ��ʾ

#endif
