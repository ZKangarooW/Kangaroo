#ifndef __DRV_HT162x_H__
#define __DRV_HT162x_H__

#include "include.h"

/**********宏定义************/
#define  BIAS     0x52  //0b1000 0101 0010
#define  SYSDIS   0X00  //0b1000 0000 0000 
#define  SYSEN    0X02  //0b1000 0000 0010 
#define  LCDOFF   0X04  //0b1000 0000 0100  
#define  LCDON    0X06  //0b1000 0000 0110  
#define  XTAL     0x28  //0b1000 0010 1000 
#define  RC256    0X30  //0b1000 0011 0000 
#define  WDTDIS1  0X0A  //0b1000 0000 1010  

#define Clr_162x_Cs(EXP)    (EXP ? HAL_GPIO_WritePin(Ht162x_CS1_GPIO_Port, Ht162x_CS1_Pin, GPIO_PIN_RESET) : HAL_GPIO_WritePin(Ht162x_CS2_GPIO_Port, Ht162x_CS2_Pin, GPIO_PIN_RESET))
#define Set_162x_Cs(EXP)    (EXP ? HAL_GPIO_WritePin(Ht162x_CS1_GPIO_Port, Ht162x_CS1_Pin, GPIO_PIN_SET) : HAL_GPIO_WritePin(Ht162x_CS2_GPIO_Port, Ht162x_CS2_Pin, GPIO_PIN_SET))

#define Clr_162x_Wr(EXP)    (EXP ? HAL_GPIO_WritePin(Ht162x_WR1_GPIO_Port, Ht162x_WR1_Pin, GPIO_PIN_RESET) : HAL_GPIO_WritePin(Ht162x_WR2_GPIO_Port, Ht162x_WR2_Pin, GPIO_PIN_RESET))
#define Set_162x_Wr(EXP)    (EXP ? HAL_GPIO_WritePin(Ht162x_WR1_GPIO_Port, Ht162x_WR1_Pin, GPIO_PIN_SET) : HAL_GPIO_WritePin(Ht162x_WR2_GPIO_Port, Ht162x_WR2_Pin, GPIO_PIN_SET))

#define Clr_162x_Dat(EXP)    (EXP ? HAL_GPIO_WritePin(Ht162x_DAT1_GPIO_Port, Ht162x_DAT1_Pin, GPIO_PIN_RESET) : HAL_GPIO_WritePin(Ht162x_DAT2_GPIO_Port, Ht162x_DAT2_Pin, GPIO_PIN_RESET))
#define Set_162x_Dat(EXP)    (EXP ? HAL_GPIO_WritePin(Ht162x_DAT1_GPIO_Port, Ht162x_DAT1_Pin, GPIO_PIN_SET) : HAL_GPIO_WritePin(Ht162x_DAT2_GPIO_Port, Ht162x_DAT2_Pin, GPIO_PIN_SET))

#define IC1 1
#define IC2 0

/**********全局函数**********/
void Lcd_Init(void);//LCD 初始化，对lcd自身做初始化设置
void Lcd_Clr(uint8_t x);
void Lcd_All(uint8_t x);
void Write_Addr_Dat_N(uint8_t x, uint8_t _addr, uint8_t _dat, uint8_t n);

#endif
