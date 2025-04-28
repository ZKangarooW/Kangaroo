#include "Drv_Flash.h"

/********************�÷�********************/
//Flash_Write((uint8_t *)(&Param),sizeof(Param));
//Flash_Read((uint8_t *)(&Param),sizeof(Param));
/*
*****************************************************************
 * ����ԭ�ͣ�void Drv_DataFlash_Write(uint8_t *addr, uint16_t len)
 * ��    �ܣ�д��Flash
 * ��    �룺addr��Ҫд��ṹ��ĵ�ַ��len�ṹ�峤��
 * ��    ����uint8_t *addr, uint16_t len
*****************************************************************
*/
void Drv_DataFlash_Write(uint8_t *addr, uint16_t len)
{
    uint16_t i,j;
    
    IRQ_ALL_DISABLE();//�ر������жϣ���Ȼ�޷�д��Ͷ�ȡ
	FLASH_UnLock();//����Flash
    
	FLASH_Erase(FLASH_DATA,PARAMFLASH_BASE_ADDRESS);//���ò�������������Flash��
    
    for(i = 0 ;i< 256 ;i++)//����256 bytes��д�ȴ�Flashִ�����
	{   
		FLASH_Write(FLASH_DATA,0x3FF, 0xFF);//д��ַʹ�����ĵ�ַ(�����ַ�����ԣ�������ʹ�ý��ٵĵ�ַ)
	}
    
    for(j=0; j<len; j++)
	{		
		FLASH_Write(FLASH_DATA,PARAMFLASH_BASE_ADDRESS+j, addr[j]);			
	}
    
	FLASH_Lock();//��סFlash
    IRQ_ALL_ENABLE();//�������ж�
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Drv_DataFlash_Read(uint8_t *addr, uint16_t len)
 * ��    �ܣ���ȡFlash
 * ��    �룺addr��Ҫд��ṹ��ĵ�ַ��len�ṹ�峤��
 * ��    ����uint8_t *addr, uint16_t len
*****************************************************************
*/
void Drv_DataFlash_Read(uint8_t *addr, uint16_t len)
{
    uint16_t i;
    
    IRQ_ALL_DISABLE();//�ر������жϣ���Ȼ�޷�д��Ͷ�ȡ
    FLASH_UnLock();	//����Flash

	for(i=0; i<len; i++)
	{
        addr[i] = FLASH_Read(FLASH_DATA,PARAMFLASH_BASE_ADDRESS+i);
	}
    
    FLASH_Lock();//��סFlash
    IRQ_ALL_ENABLE();//�������ж�
}
