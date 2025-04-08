#include "Flash.h"

/*
*****************************************************************
 * ����ԭ�ͣ�uint8_t Flash_Write(uint8_t *addr, uint16_t len)
 * ��    �ܣ�д��Flash
 * ��    �룺addr��Ҫд��ṹ��ĵ�ַ��len�ṹ�峤��
 * ��    ����д���Ƿ�ɹ�
 * ��    ����uint8_t *addr, uint16_t len
*****************************************************************
*/
uint8_t Flash_Write(uint8_t *addr, uint16_t len)
{
	uint16_t  FlashStatus;//����д��Flash״̬
	FLASH_EraseInitTypeDef My_Flash;//���� FLASH_EraseInitTypeDef �ṹ��Ϊ My_Flash

	HAL_FLASH_Unlock();//����Flash
	
	My_Flash.TypeErase = FLASH_TYPEERASE_PAGES;//����Flashִ��ҳ��ֻ����������
    My_Flash.PageAddress = PARAMFLASH_BASE_ADDRESS;//����Ҫ�����ĵ�ַ
    My_Flash.NbPages = 1;//˵��Ҫ������ҳ�����˲���������Min_Data = 1��Max_Data =(���ҳ��-��ʼҳ��ֵ)֮���ֵ
	
	uint32_t PageError = 0;//����PageError,������ִ�����������ᱻ����Ϊ�����FLASH��ַ
	
	FlashStatus = HAL_FLASHEx_Erase(&My_Flash, &PageError);//���ò�������������Flash��
	if(FlashStatus != HAL_OK)
		return 0;
	
	for(uint16_t i=0; i<len; i=i+2)
	{
		uint16_t temp;//��ʱ�洢��ֵ
		if(i+1 <= len-1)
			temp = (uint16_t)(addr[i+1]<<8) + addr[i];
		else
			temp = 0xff00 + addr[i];	
		//��Flash������д��FLASH_TYPEPROGRAM_HALFWORD ����������Flash��ַ��16λ�ģ����⻹��32λ��64λ�Ĳ��������з���HAL��Ķ��弴��	
		FlashStatus = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, PARAMFLASH_BASE_ADDRESS+i, temp); 
		if (FlashStatus != HAL_OK)
			return 0;
	}
	HAL_FLASH_Lock();//��סFlash
	return 1;
}

/*
*****************************************************************
 * ����ԭ�ͣ�uint8_t Flash_Read(uint8_t *addr, uint16_t len)
 * ��    �ܣ���ȡFlash
 * ��    �룺addr��Ҫд��ṹ��ĵ�ַ��len�ṹ�峤��
 * ��    ������ȡ�Ƿ�ɹ�
 * ��    ����uint8_t *addr, uint16_t len
*****************************************************************
*/
uint8_t Flash_Read(uint8_t *addr, uint16_t len)
{
	for(uint16_t i=0; i<len; i=i+2)
	{
		uint16_t temp;
		if(i+1 <= len-1)
		{
			temp = (*(__IO uint16_t*)(PARAMFLASH_BASE_ADDRESS+i));//*(__IO uint16_t *)�Ƕ�ȡ�õ�ַ�Ĳ���ֵ,��ֵΪ16λ����,һ�ζ�ȡ�����ֽ�
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
