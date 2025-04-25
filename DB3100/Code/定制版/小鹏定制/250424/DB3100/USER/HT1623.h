#ifndef __HT1623_H__
#define __HT1623_H__

#include "main.h"

/**********宏定义************/
#define  BIAS     0x52  //0b1000 0101 0010  1/3duty 4com 
#define  SYSDIS   0X00  //0b1000 0000 0000  ???????LCD????? 
#define  SYSEN    0X02  //0b1000 0000 0010 ??????? 
#define  LCDOFF   0X04  //0b1000 0000 0100  ?LCD?? 
#define  LCDON    0X06  //0b1000 0000 0110  ??LCD?? 
#define  XTAL     0x28  //0b1000 0010 1000 ????? 
#define  RC256    0X30  //0b1000 0011 0000  ???? 
#define  WDTDIS1  0X0A  //0b1000 0000 1010  ????? 

#define Clr_1625_Cs  HAL_GPIO_WritePin(GPIOA, Ht1621_CS_Pin, GPIO_PIN_RESET)
#define Set_1625_Cs  HAL_GPIO_WritePin(GPIOA, Ht1621_CS_Pin, GPIO_PIN_SET)

#define Clr_1625_Wr  HAL_GPIO_WritePin(GPIOA, Ht1621_WR_Pin, GPIO_PIN_RESET)
#define Set_1625_Wr  HAL_GPIO_WritePin(GPIOA, Ht1621_WR_Pin, GPIO_PIN_SET)

#define Clr_1625_Dat HAL_GPIO_WritePin(GPIOA, Ht1621_DAT_Pin, GPIO_PIN_RESET)
#define Set_1625_Dat HAL_GPIO_WritePin(GPIOA, Ht1621_DAT_Pin, GPIO_PIN_SET)

#define VLED htim1.Instance->CCR2//LCD背光

/**********全局函数**********/
void lcd_init(void);//LCD 初始化，对lcd自身做初始化设置
void lcd_clr(void);//LCD 清屏函数
void lcd_all(void);//LCD 全显示函数
void write_addr_dat_n(unsigned char _addr, unsigned char _dat, unsigned char n);//屏幕显示

#endif
