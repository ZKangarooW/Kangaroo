#ifndef __DRV_FLASH_H__
#define __DRV_FLASH_H__

#include "include.h"

/**********宏定义************/
#define BYTE0(dwTemp) (*(char *)(&dwTemp))
#define BYTE1(dwTemp) (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp) (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp) (*((char *)(&dwTemp) + 3))
#if defined(STM32F10X_LD) || defined(STM32F10X_MD) // 判断芯片内存
#define PAGE_SIZE (uint16_t)0x400                  /* Page size = 1KByte */
#elif defined(STM32F10X_HD) || defined(STM32F10X_CL)
#define PAGE_SIZE (uint16_t)0x800 /* Page size = 2KByte */
#endif

#define EEPROM_START_ADDRESS ((uint32_t)0x08009A00)                                 // 最初地址值
#define PARAMFLASH_BASE_ADDRESS ((uint32_t)(EEPROM_START_ADDRESS + 0x000))          // 开始的地址值
#define PARAMFLASH_END_ADDRESS ((uint32_t)(EEPROM_START_ADDRESS + (PAGE_SIZE - 1))) // 结束的地址值

/**********结构体************/
/**********全局变量声明*******/
/**********全局函数**********/

uint8_t Flash_Write(uint8_t *addr, uint16_t len);
uint8_t Flash_Read(uint8_t *addr, uint16_t len);

#endif
