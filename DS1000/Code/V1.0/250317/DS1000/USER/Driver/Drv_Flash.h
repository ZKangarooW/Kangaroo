#ifndef __DRV_FLASH_H__
#define __DRV_FLASH_H__

#include "include.h"

/**********�궨��************/
#define BYTE0(dwTemp) (*(char *)(&dwTemp))
#define BYTE1(dwTemp) (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp) (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp) (*((char *)(&dwTemp) + 3))

#define PARAMFLASH_BASE_ADDRESS	0x1000//��ʼ�õ�ֵַ�õ�ֵַ

/**********�ṹ��************/
/**********ȫ�ֱ�������******/
/**********ȫ�ֺ���**********/
uint8_t DataFlash_Write(uint8_t *addr, uint16_t len);//д��Flash
uint8_t DataFlash_Read(uint8_t *addr, uint16_t len);//��ȡFlash

#endif
