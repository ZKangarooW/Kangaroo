#include "Drv_Flash.h"

/********************用法********************/
//Flash_Write((uint8_t *)(&Param),sizeof(Param));
//Flash_Read((uint8_t *)(&Param),sizeof(Param));
/*
*****************************************************************
 * 函数原型：void Drv_DataFlash_Write(uint8_t *addr, uint16_t len)
 * 功    能：写入Flash
 * 输    入：addr需要写入结构体的地址，len结构体长度
 * 参    数：uint8_t *addr, uint16_t len
*****************************************************************
*/
void Drv_DataFlash_Write(uint8_t *addr, uint16_t len)
{
    uint16_t i,j;
    
    IRQ_ALL_DISABLE();//关闭所有中断，不然无法写入和读取
	FLASH_UnLock();//解锁Flash
    
	FLASH_Erase(FLASH_DATA,PARAMFLASH_BASE_ADDRESS);//调用擦除函数（擦除Flash）
    
    for(i = 0 ;i< 256 ;i++)//连续256 bytes的写等待Flash执行完成
	{   
		FLASH_Write(FLASH_DATA,0x3FF, 0xFF);//写地址使用最后的地址(任意地址都可以，建议用使用较少的地址)
	}
    
    for(j=0; j<len; j++)
	{		
		FLASH_Write(FLASH_DATA,PARAMFLASH_BASE_ADDRESS+j, addr[j]);			
	}
    
	FLASH_Lock();//锁住Flash
    IRQ_ALL_ENABLE();//打开所有中断
}

/*
*****************************************************************
 * 函数原型：void Drv_DataFlash_Read(uint8_t *addr, uint16_t len)
 * 功    能：读取Flash
 * 输    入：addr需要写入结构体的地址，len结构体长度
 * 参    数：uint8_t *addr, uint16_t len
*****************************************************************
*/
void Drv_DataFlash_Read(uint8_t *addr, uint16_t len)
{
    uint16_t i;
    
    IRQ_ALL_DISABLE();//关闭所有中断，不然无法写入和读取
    FLASH_UnLock();	//解锁Flash

	for(i=0; i<len; i++)
	{
        addr[i] = FLASH_Read(FLASH_DATA,PARAMFLASH_BASE_ADDRESS+i);
	}
    
    FLASH_Lock();//锁住Flash
    IRQ_ALL_ENABLE();//打开所有中断
}
