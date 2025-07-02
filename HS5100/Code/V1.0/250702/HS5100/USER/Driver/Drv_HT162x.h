#ifndef __DRV_HT162x_H__
#define __DRV_HT162x_H__

#include "include.h"

/**********宏定义************/
#define  BIAS     0x52//0b1000 0101 0010
#define  SYSDIS   0X00//0b1000 0000 0000 
#define  SYSEN    0X02//0b1000 0000 0010 
#define  LCDOFF   0X04//0b1000 0000 0100  
#define  LCDON    0X06//0b1000 0000 0110  
#define  XTAL     0x28//0b1000 0010 1000 
#define  RC256    0X30//0b1000 0011 0000 
#define  WDTDIS1  0X0A//0b1000 0000 1010  

#define Clr_162x_Cs  HAL_GPIO_WritePin(Ht162x_CS_GPIO_Port, Ht162x_CS_Pin, GPIO_PIN_RESET)
#define Set_162x_Cs  HAL_GPIO_WritePin(Ht162x_CS_GPIO_Port, Ht162x_CS_Pin, GPIO_PIN_SET)

#define Clr_162x_Wr  HAL_GPIO_WritePin(Ht162x_WR_GPIO_Port, Ht162x_WR_Pin, GPIO_PIN_RESET)
#define Set_162x_Wr  HAL_GPIO_WritePin(Ht162x_WR_GPIO_Port, Ht162x_WR_Pin, GPIO_PIN_SET)

#define Clr_162x_Dat HAL_GPIO_WritePin(Ht162x_DAT_GPIO_Port, Ht162x_DAT_Pin, GPIO_PIN_RESET)
#define Set_162x_Dat HAL_GPIO_WritePin(Ht162x_DAT_GPIO_Port, Ht162x_DAT_Pin, GPIO_PIN_SET)

/**********结构体************/
/**********全局变量声明******/
/**********全局函数**********/

void Lcd_Init(void);
void Lcd_Clr(void);
void Lcd_All(void);
void Write_Addr_Dat_N(unsigned char _addr, unsigned char _dat, unsigned char n);

#endif
