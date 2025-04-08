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

/****************************************************************************/
/** \file main.c
**
** 
**
**	History:
**	
*****************************************************************************/
/****************************************************************************/
/*	include files
*****************************************************************************/
#include "cms80f731xx.h"

/****************************************************************************/
/*	Local pre-processor symbols('#define')
*****************************************************************************/

/****************************************************************************/
/*	Global variable definitions(declared in header file with 'extern')
*****************************************************************************/


/****************************************************************************/
/*	Local type definitions('typedef')
*****************************************************************************/

/****************************************************************************/
/*	Local variable  definitions('static')
*****************************************************************************/


/****************************************************************************/
/*	Local function prototypes('static')
*****************************************************************************/


/****************************************************************************/
/*	Function implementation - global ('extern') and local('static')
*****************************************************************************/

/*****************************************************************************
 ** \brief	 main
 **
 ** \param [in]  none   
 **
 ** \return 0
 *****************************************************************************/

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xA4

volatile uint8_t temp=0;
volatile uint16_t addr=0;
volatile uint16_t Dtemp=0;

typedef struct
{
	uint8_t Init_ok;//ϵͳ��ʼ���Ƿ���ɣ����Ϊ1
    uint8_t Run_Status[10];//ϵͳ״̬
	uint8_t SetMode_Option[10];//����ʱ��ǰ���õ�ѡ��
}_sys_;
_sys_ sys;//ϵͳ��ʼ�����

struct _Save_Param_
{	
	uint8_t Flash_Check_Start;//����Ƿ��Ѿ���ʼ���Ŀ�ʼλ

	uint16_t Temp;//�¶�
	uint32_t Time;//ʱ��
    
	uint8_t Flash_Check_End;//����Ƿ��Ѿ���ʼ���Ľ���λ
};
struct _Save_Param_ Param;
struct _Save_Param_ Param123;

/*
*****************************************************************
 * ����ԭ�ͣ�void Param_Reset(void)
 * ��    �ܣ���ʼ��Ӳ���еĲ���
*****************************************************************
*/
void Param_Reset(void)
{
	Param.Flash_Check_Start = FLASH_CHECK_START;

	Param.Temp = 200;//�¶�50��
	Param.Time = 7200;//ʱ�䳣��
    
	Param.Flash_Check_End  = FLASH_CHECK_END;
}
#define BYTE0(dwTemp) (*(char *)(&dwTemp))
#define BYTE1(dwTemp) (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp) (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp) (*((char *)(&dwTemp) + 3))
#define PARAMFLASH_BASE_ADDRESS	0//��ʼ�õ�ֵַ

uint8_t Flash_Write12(uint8_t *addr, uint16_t len)
{
    uint16_t i,j;
    
	FLASH_UnLock();//����Flash
    
	FLASH_Erase(FLASH_DATA,PARAMFLASH_BASE_ADDRESS);//���ò�������������Flash��
    
    for(i = 0 ;i< 256 ;i++)//����256 bytes��д�ȴ�Flashִ�����
	{   
		FLASH_Write(FLASH_DATA,0x3FF, 0xFF);//д��ַʹ�����ĵ�ַ(�����ַ�����ԣ�������ʹ�ý��ٵĵ�ַ)
	}
    
    for(j=0; j<len; j++)
	{		
        uint16_t temp;//��ʱ�洢��ֵ   
        temp = addr[j];	
		FLASH_Write(FLASH_DATA,PARAMFLASH_BASE_ADDRESS+j, temp);			
	}
    
	FLASH_Lock();//��סFlash
	return 1;
}


uint8_t Flash_Read12(uint8_t *addr, uint16_t len)
{
    uint16_t i;
    
    FLASH_UnLock();	//����Flash

	for(i=0; i<len; i++)
	{
		uint8_t temp;
        temp = FLASH_Read(FLASH_DATA,PARAMFLASH_BASE_ADDRESS+i);
        addr[i] = BYTE0(temp);
	}
    
    FLASH_Lock();//��סFlash
	return 1;
}
uint8_t flag;
int main(void)
{		

//		
//	FLASH_UnLock();	
//	for(addr = 0x0 ;addr< 0x10 ;addr++)//0X10 ��С
//	{			
//		sys.SetMode_Option[addr] = FLASH_Read(FLASH_DATA,addr);					
//	}
//	FLASH_Lock();	
	
//    Param_Reset();
//    Flash_Write12((uint8_t *)(&Param),sizeof(Param));
    Flash_Read12((uint8_t *)(&Param),sizeof(Param));

//    FLASH_UnLock();	
//	for(addr = 0x0 ;addr< 0x10 ;addr++)//0X10 ��С
//	{			
//		sys.SetMode_Option[addr] = FLASH_Read(FLASH_DATA,addr);					
//	}
//	FLASH_Lock();	
//    Flash_Read12((uint8_t *)(&Param),sizeof(Param));
    
	while(1)
	{	
        if(flag == 1)
        {
            Param.Flash_Check_Start = 0x13;

            Param.Temp = 120;//�¶�50��
            Param.Time = 4200;//ʱ�䳣��
            
            Param.Flash_Check_End  = 0x24;
            Flash_Write12((uint8_t *)(&Param),sizeof(Param));
            flag = 0;
        }
        Flash_Read12((uint8_t *)(&Param),sizeof(Param));
//		Param_Reset();
//        Flash_Write12((uint8_t *)(&Param),sizeof(Param));

	}		
}























