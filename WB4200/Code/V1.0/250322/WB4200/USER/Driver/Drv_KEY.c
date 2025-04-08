#include "Drv_KEY.h"

/**********�ֲ���������******/
float Key_Cnt1,Key_Cnt2,Key_Cnt3,Key_Cnt4,Key_Cnt5,Key_Cnt6;//����ʱ��
uint8_t Key_Flag1,Key_Flag2,Key_Flag3,Key_Flag4,Key_Flag5,Key_Flag6;//�������±�־
uint8_t LongPress1,LongPress2,LongPress3,LongPress4,LongPress5,LongPress6;//����������־

/**
 * @brief ����ɨ��
 * 
 * @param dT ִ������
 */
void Key_Scan(float dT)
{
	/************************************MUNE��**************************************/
	if(KEY1 == KEY_DOWN)//���°���
	{
		if(LongPress1 == 0)//û�г�����
		{
			Key_Cnt1 += dT;//����ʱ��++
			Key_Flag1 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag1 == 1)//����������
	{
		if(KEY1 == KEY_UP)//̧�𰴼�
		{   
			if(Key_Cnt1 > 0.1 && Key_Cnt1 < 1.5)//С��1.5S�ǵ���
			{
                HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);//�ر�LED
			}
			Key_Flag1 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress1 = 0;//������־����
			Key_Cnt1 = 0;//��ť��������
		}
		if(Key_Cnt1 > 1.5 && Key_Cnt1 < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress1 == 0)//���û��һֱһֱ������
			{
                
				LongPress1 = 1;//������־��һ
			}
		}
	}
    
	/**************************************P��**************************************/
	if(KEY2 == KEY_DOWN)//���°���
	{	
		if(LongPress2 == 0)//û�г�����
		{
			Key_Cnt2 += dT;//����ʱ��++
			Key_Flag2 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag2 == 1)//����������
	{
		if(KEY2 == KEY_UP)//̧�𰴼�
		{   
			if(Key_Cnt2 > 0.1 && Key_Cnt2 < 1.5)//С��1.5S�ǵ���
			{
                HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET);//�ر�LED
			}
			Key_Flag2 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress2 = 0;//������־����
			Key_Cnt2 = 0;//��ť��������		
		}
		if(Key_Cnt2 > 1.5 && Key_Cnt2 < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress2 == 0)//���û��һֱһֱ������
			{
				
				LongPress2 = 1;//������־��һ
			}
		}
	}
	/**************************************�Ӽ�**************************************/
	if(KEY3 == KEY_DOWN)//���°���
	{	
		if(LongPress3 == 0)//û�г�����
		{
			Key_Cnt3 += dT;//����ʱ��++
			Key_Flag3 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag3 == 1)//����������
	{
		if(KEY3 == KEY_UP)//̧�𰴼�
		{   
			if(Key_Cnt3 > 0.1 && Key_Cnt3 < 1.5)//С��1.5S�ǵ���
			{
                HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_RESET);//�ر�LED
			}
			Key_Flag3 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress3 = 0;//������־����
			Key_Cnt3 = 0;//��ť��������		
		}
		if(Key_Cnt3 > 1.5 && Key_Cnt3 < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress3 == 0)//���û��һֱһֱ������
			{
                
				LongPress3 = 1;//������־��һ
			}
		}
	}
    
    /**************************************����**************************************/
	if(KEY4 == KEY_DOWN)//���°���
	{	
		if(LongPress4 == 0)//û�г�����
		{
			Key_Cnt4 += dT;//����ʱ��++
			Key_Flag4 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag4 == 1)//����������
	{
		if(KEY4 == KEY_UP)//̧�𰴼�
		{   
			if(Key_Cnt4 > 0.1 && Key_Cnt4 < 1.5)//С��1.5S�ǵ���
			{
                HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,GPIO_PIN_RESET);//�ر�LED
			}
			Key_Flag4 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress4 = 0;//������־����
			Key_Cnt4 = 0;//��ť��������		
		}
		if(Key_Cnt4 > 1.5 && Key_Cnt4 < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress4 == 0)//���û��һֱһֱ������
			{
                
				LongPress4 = 1;//������־��һ
			}
		}
	}
    
    /**************************************Boil��**************************************/
	if(KEY5 == KEY_DOWN)//���°���
	{	
		if(LongPress5 == 0)//û�г�����
		{
			Key_Cnt5 += dT;//����ʱ��++
			Key_Flag5 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag5 == 1)//����������
	{
		if(KEY5 == KEY_UP)//̧�𰴼�
		{   
			if(Key_Cnt5 > 0.1 && Key_Cnt5 < 1.5)//С��1.5S�ǵ���
			{
                HAL_GPIO_WritePin(LED5_GPIO_Port,LED5_Pin,GPIO_PIN_RESET);//�ر�LED
			}
			Key_Flag5 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress5 = 0;//������־����
			Key_Cnt5 = 0;//��ť��������		
		}
		if(Key_Cnt5 > 1.5 && Key_Cnt5 < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress5 == 0)//���û��һֱһֱ������
			{
                
				LongPress5 = 1;//������־��һ
			}
		}
	}
    
    /**************************************Start��**************************************/
	if(KEY6 == KEY_DOWN)//���°���
	{	
		if(LongPress6 == 0)//û�г�����
		{
			Key_Cnt6 += dT;//����ʱ��++
			Key_Flag6 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag6 == 1)//����������
	{
		if(KEY6 == KEY_UP)//̧�𰴼�
		{   
			if(Key_Cnt6 > 0.1 && Key_Cnt6 < 1.5)//С��1.5S�ǵ���
			{
                HAL_GPIO_WritePin(LED6_GPIO_Port,LED6_Pin,GPIO_PIN_RESET);//�ر�LED
			}
			Key_Flag6 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress6 = 0;//������־����
			Key_Cnt6 = 0;//��ť��������		
		}
		if(Key_Cnt6 > 1.5 && Key_Cnt6 < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress6 == 0)//���û��һֱһֱ������
			{
                
				LongPress6 = 1;//������־��һ
			}
		}
	}
}
