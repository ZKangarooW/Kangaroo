#include "Flash.h"

/*
*****************************************************************
 * 函数原型：uint8_t Flash_Write(uint8_t *addr, uint16_t len)
 * 功    能：写入Flash
 * 输    入：addr需要写入结构体的地址，len结构体长度
 * 输    出：写入是否成功
 * 参    数：uint8_t *addr, uint16_t len
*****************************************************************
*/
uint8_t Flash_Write(uint8_t *addr, uint16_t len)
{
	uint16_t  FlashStatus;//定义写入Flash状态
	FLASH_EraseInitTypeDef My_Flash;//声明 FLASH_EraseInitTypeDef 结构体为 My_Flash

	HAL_FLASH_Unlock();//解锁Flash
	
	My_Flash.TypeErase = FLASH_TYPEERASE_PAGES;//标明Flash执行页面只做擦除操作
    My_Flash.PageAddress = PARAMFLASH_BASE_ADDRESS;//声明要擦除的地址
    My_Flash.NbPages = 1;//说明要擦除的页数，此参数必须是Min_Data = 1和Max_Data =(最大页数-初始页的值)之间的值
	
	uint32_t PageError = 0;//设置PageError,如果出现错误这个变量会被设置为出错的FLASH地址
	
	FlashStatus = HAL_FLASHEx_Erase(&My_Flash, &PageError);//调用擦除函数（擦除Flash）
	if(FlashStatus != HAL_OK)
		return 0;
	
	for(uint16_t i=0; i<len; i=i+2)
	{
		uint16_t temp;//临时存储数值
		if(i+1 <= len-1)
			temp = (uint16_t)(addr[i+1]<<8) + addr[i];
		else
			temp = 0xff00 + addr[i];	
		//对Flash进行烧写，FLASH_TYPEPROGRAM_HALFWORD 声明操作的Flash地址的16位的，此外还有32位跟64位的操作，自行翻查HAL库的定义即可	
		FlashStatus = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, PARAMFLASH_BASE_ADDRESS+i, temp); 
		if (FlashStatus != HAL_OK)
			return 0;
	}
	HAL_FLASH_Lock();//锁住Flash
	return 1;
}

/*
*****************************************************************
 * 函数原型：uint8_t Flash_Read(uint8_t *addr, uint16_t len)
 * 功    能：读取Flash
 * 输    入：addr需要写入结构体的地址，len结构体长度
 * 输    出：读取是否成功
 * 参    数：uint8_t *addr, uint16_t len
*****************************************************************
*/
uint8_t Flash_Read(uint8_t *addr, uint16_t len)
{
	for(uint16_t i=0; i<len; i=i+2)
	{
		uint16_t temp;
		if(i+1 <= len-1)
		{
			temp = (*(__IO uint16_t*)(PARAMFLASH_BASE_ADDRESS+i));//*(__IO uint16_t *)是读取该地址的参数值,其值为16位数据,一次读取两个字节
			addr[i] = BYTE0(temp);
			addr[i+1] = BYTE1(temp);
		}
		else
		{
			temp = (*(__IO uint16_t*)(PARAMFLASH_BASE_ADDRESS+i));
			addr[i] = BYTE0(temp);
		}
	}
	return 1;
}
