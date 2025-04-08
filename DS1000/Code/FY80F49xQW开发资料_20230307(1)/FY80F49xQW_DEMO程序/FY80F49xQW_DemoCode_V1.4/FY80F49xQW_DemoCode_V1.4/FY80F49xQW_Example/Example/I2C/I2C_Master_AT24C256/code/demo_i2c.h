/*******************************************************************************
* Copyright (C) 2019 China Micro Semiconductor Limited Company. All Rights Reserved.
*
* This software is owned and published by:
* CMS LLC, No 2609-10, Taurus Plaza, TaoyuanRoad, NanshanDistrict, Shenzhen, China.
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with CMS
* components. This software is licensed by CMS to be adapted only
* for use in systems utilizing CMS components. CMS shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. CMS is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/

/*****************************************************************************/
/** \file demo_i2c.h
**
**
**
** History:
** - 
*****************************************************************************/
#ifndef __DEMO_I2C_H__
#define __DEMO_I2C_H__
/*****************************************************************************/
/* Include files */
/*****************************************************************************/
#include "cms80f731xx.h"

/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define') */
/*****************************************************************************/


/*****************************************************************************/
/* Global type definitions ('typedef') */
/*****************************************************************************/



/*****************************************************************************/
/* Global variable declarations ('extern', definition in C source) */
/*****************************************************************************/


/*****************************************************************************/
/* Global function prototypes ('extern', definition in C source) */
/*****************************************************************************/
/******************************************************************************
 ** \brief	 I2C_Config
 ** \param [in] 
 **            	
 ** \return  none
 ** \note  
 ******************************************************************************/
void I2C_Config(void);

/*****************************************************************************
 ** \brief	 At24c256_read_str
 **			 ������ȡAt24c256����
 ** \param [in] addr ����ʼ��ַ
 **            	ch	 : ���ݱ��������(����)  
**				sizevalue: ��ȡ�����ݵĸ���
 ** \return  0/1
 ** \note  	 ����  unsigned char  array[10];			//����һ��10�ֽڵ�����
 **	  At24c256_read_str(0x0010, Buffer, 5); //�ӵ�ַ0x0010��ʼ��ȡ5���ֽڵ����ݷŵ�����array��
 *****************************************************************************/
uint16_t At24c256_read_str(uint16_t addr,  uint8_t *ch, uint16_t sizevalue);
 
/*****************************************************************************
 ** \brief	 At24c256_read_byte
 **			 ��At24C256�ж�����
 ** \param [in]  addr : ��ַ
 **            	
 ** \return  ����8λ����
 ** \note   
 ****************************************************************************/
uint8_t  At24c256_read_byte(uint16_t addr);
/*****************************************************************************
 ** \brief	 At24c256_write_byte
 **			 д���ݵ�At24C256
 ** \param [in] addr ����ַ
**				ch   : ����
 **            	
 ** \return  -1��������ַ��Χ 0��д���
 ** \note  
 *****************************************************************************/ 
int16_t  At24c256_write_byte(uint16_t addr , uint8_t ch);

#endif /* __DEMO_I2C_H__ */






