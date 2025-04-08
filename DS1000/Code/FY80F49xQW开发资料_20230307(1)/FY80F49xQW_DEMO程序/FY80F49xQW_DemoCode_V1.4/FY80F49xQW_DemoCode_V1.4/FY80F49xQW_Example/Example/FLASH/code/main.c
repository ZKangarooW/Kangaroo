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
	uint8_t Init_ok;//系统初始化是否完成，完成为1
    uint8_t Run_Status[10];//系统状态
	uint8_t SetMode_Option[10];//设置时当前设置的选项
}_sys_;
_sys_ sys;//系统初始化检测

struct _Save_Param_
{	
	uint8_t Flash_Check_Start;//检查是否已经初始化的开始位

	uint16_t Temp;//温度
	uint32_t Time;//时间
    
	uint8_t Flash_Check_End;//检查是否已经初始化的结束位
};
struct _Save_Param_ Param;
struct _Save_Param_ Param123;

/*
*****************************************************************
 * 函数原型：void Param_Reset(void)
 * 功    能：初始化硬件中的参数
*****************************************************************
*/
void Param_Reset(void)
{
	Param.Flash_Check_Start = FLASH_CHECK_START;

	Param.Temp = 200;//温度50℃
	Param.Time = 7200;//时间常动
    
	Param.Flash_Check_End  = FLASH_CHECK_END;
}
#define BYTE0(dwTemp) (*(char *)(&dwTemp))
#define BYTE1(dwTemp) (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp) (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp) (*((char *)(&dwTemp) + 3))
#define PARAMFLASH_BASE_ADDRESS	0//开始得地址值

uint8_t Flash_Write12(uint8_t *addr, uint16_t len)
{
    uint16_t i,j;
    
	FLASH_UnLock();//解锁Flash
    
	FLASH_Erase(FLASH_DATA,PARAMFLASH_BASE_ADDRESS);//调用擦除函数（擦除Flash）
    
    for(i = 0 ;i< 256 ;i++)//连续256 bytes的写等待Flash执行完成
	{   
		FLASH_Write(FLASH_DATA,0x3FF, 0xFF);//写地址使用最后的地址(任意地址都可以，建议用使用较少的地址)
	}
    
    for(j=0; j<len; j++)
	{		
        uint16_t temp;//临时存储数值   
        temp = addr[j];	
		FLASH_Write(FLASH_DATA,PARAMFLASH_BASE_ADDRESS+j, temp);			
	}
    
	FLASH_Lock();//锁住Flash
	return 1;
}


uint8_t Flash_Read12(uint8_t *addr, uint16_t len)
{
    uint16_t i;
    
    FLASH_UnLock();	//解锁Flash

	for(i=0; i<len; i++)
	{
		uint8_t temp;
        temp = FLASH_Read(FLASH_DATA,PARAMFLASH_BASE_ADDRESS+i);
        addr[i] = BYTE0(temp);
	}
    
    FLASH_Lock();//锁住Flash
	return 1;
}
uint8_t flag;
int main(void)
{		

//		
//	FLASH_UnLock();	
//	for(addr = 0x0 ;addr< 0x10 ;addr++)//0X10 大小
//	{			
//		sys.SetMode_Option[addr] = FLASH_Read(FLASH_DATA,addr);					
//	}
//	FLASH_Lock();	
	
//    Param_Reset();
//    Flash_Write12((uint8_t *)(&Param),sizeof(Param));
    Flash_Read12((uint8_t *)(&Param),sizeof(Param));

//    FLASH_UnLock();	
//	for(addr = 0x0 ;addr< 0x10 ;addr++)//0X10 大小
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

            Param.Temp = 120;//温度50℃
            Param.Time = 4200;//时间常动
            
            Param.Flash_Check_End  = 0x24;
            Flash_Write12((uint8_t *)(&Param),sizeof(Param));
            flag = 0;
        }
        Flash_Read12((uint8_t *)(&Param),sizeof(Param));
//		Param_Reset();
//        Flash_Write12((uint8_t *)(&Param),sizeof(Param));

	}		
}























