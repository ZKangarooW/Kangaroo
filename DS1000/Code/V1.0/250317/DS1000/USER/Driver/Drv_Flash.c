#include "Drv_Flash.h"

///********************用法********************/
////Flash_Write((uint8_t *)(&Param),sizeof(Param));
////Flash_Read((uint8_t *)(&Param),sizeof(Param));
///*
//*****************************************************************
// * 函数原型：uint8_t DataFlash_Write(uint8_t *addr, uint16_t len)
// * 功    能：写入Flash
// * 输    入：addr需要写入结构体的地址，len结构体长度
// * 输    出：写入是否成功
// * 参    数：uint8_t *addr, uint16_t len
//*****************************************************************
//*/volatile uint16_t Dtemp=0;volatile uint16_t addr2=0;
//uint8_t DataFlash_Write(uint8_t *addr, uint16_t len)
//{
//    uint16_t i,j;
//    Dtemp=0;
//	FLASH_UnLock();//解锁Flash
//    addr2=0xFF00;
//	FLASH_Erase(FLASH_CODE,addr2);//调用擦除函数（擦除Flash）
//    
//    for(i = 0 ;i< 256 ;i++)//连续256 bytes的写等待Flash执行完成
//	{   
//		FLASH_Write(FLASH_CODE,0xFFFF, 0xFF);//写地址使用最后的地址(任意地址都可以，建议用使用较少的地址)
//	}
//    
//    for(addr2 = 0xFF00 ;addr2< 0xFF10 ;addr2++)
//	{			
//		FLASH_Write(FLASH_CODE,addr2, Dtemp++);					
//	}
//    
//	FLASH_Lock();//锁住Flash
//	return 1;
//}

///*
//*****************************************************************
// * 函数原型：uint8_t DataFlash_Read(uint8_t *addr, uint16_t len)
// * 功    能：读取Flash
// * 输    入：addr需要写入结构体的地址，len结构体长度
// * 输    出：读取是否成功
// * 参    数：uint8_t *addr, uint16_t len
//*****************************************************************
//*/
//uint8_t DataFlash_Read(uint8_t *addr, uint16_t len)
//{
//    uint16_t i;
//    
//    FLASH_UnLock();	//解锁Flash

////	for(i=0; i<len; i++)
////	{
////		uint8_t temp;
////        temp = FLASH_Read(FLASH_CODE,PARAMFLASH_BASE_ADDRESS+i);
////        addr[i] = BYTE0(temp);
////	}
//    for(addr2 = 0xFF00 ;addr2< 0xFF10 ;addr2++)
//	{			
//		sys.dataa[addr2] = FLASH_Read(FLASH_CODE,addr2);					
//	}
//    FLASH_Lock();//锁住Flash
//	return 1;
//}
