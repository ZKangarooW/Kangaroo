#include "Drv_Flash.h"

///********************�÷�********************/
////Flash_Write((uint8_t *)(&Param),sizeof(Param));
////Flash_Read((uint8_t *)(&Param),sizeof(Param));
///*
//*****************************************************************
// * ����ԭ�ͣ�uint8_t DataFlash_Write(uint8_t *addr, uint16_t len)
// * ��    �ܣ�д��Flash
// * ��    �룺addr��Ҫд��ṹ��ĵ�ַ��len�ṹ�峤��
// * ��    ����д���Ƿ�ɹ�
// * ��    ����uint8_t *addr, uint16_t len
//*****************************************************************
//*/volatile uint16_t Dtemp=0;volatile uint16_t addr2=0;
//uint8_t DataFlash_Write(uint8_t *addr, uint16_t len)
//{
//    uint16_t i,j;
//    Dtemp=0;
//	FLASH_UnLock();//����Flash
//    addr2=0xFF00;
//	FLASH_Erase(FLASH_CODE,addr2);//���ò�������������Flash��
//    
//    for(i = 0 ;i< 256 ;i++)//����256 bytes��д�ȴ�Flashִ�����
//	{   
//		FLASH_Write(FLASH_CODE,0xFFFF, 0xFF);//д��ַʹ�����ĵ�ַ(�����ַ�����ԣ�������ʹ�ý��ٵĵ�ַ)
//	}
//    
//    for(addr2 = 0xFF00 ;addr2< 0xFF10 ;addr2++)
//	{			
//		FLASH_Write(FLASH_CODE,addr2, Dtemp++);					
//	}
//    
//	FLASH_Lock();//��סFlash
//	return 1;
//}

///*
//*****************************************************************
// * ����ԭ�ͣ�uint8_t DataFlash_Read(uint8_t *addr, uint16_t len)
// * ��    �ܣ���ȡFlash
// * ��    �룺addr��Ҫд��ṹ��ĵ�ַ��len�ṹ�峤��
// * ��    ������ȡ�Ƿ�ɹ�
// * ��    ����uint8_t *addr, uint16_t len
//*****************************************************************
//*/
//uint8_t DataFlash_Read(uint8_t *addr, uint16_t len)
//{
//    uint16_t i;
//    
//    FLASH_UnLock();	//����Flash

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
//    FLASH_Lock();//��סFlash
//	return 1;
//}
