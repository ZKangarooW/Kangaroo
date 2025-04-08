#include "Drv_Key.h"

/**********ȫ�ֱ�������******/
uint8_t Key_Status;//�������±�־

/**********�ֲ���������******/
float Key_Cnt1,Key_Cnt2,Key_Cnt3,Key_Cnt4,Key_Cnt5,Key_Cnt6;//����ʱ��
uint8_t Key_Flag1,Key_Flag2,Key_Flag3,Key_Flag4,Key_Flag5,Key_Flag6;//�������±�־
uint8_t LongPress1,LongPress2,LongPress3,LongPress4,LongPress5,LongPress6;//����������־

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_Press(float dT)
 * ��    �ܣ���ⰴ������״̬-500ms
*****************************************************************
*/
void Check_Press(float dT)
{
    if(Key_Status)//��������
        Key_Status -= dT;//����ʱ
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Key_Scan(float dT)
 * ��    �ܣ����󰴼�ɨ��
*****************************************************************
*/
void Key_Scan(float dT)
{
	ROW1_H;
	ROW2_L;
	ROW3_H;
	/**************************************START��**************************************/
	if(HAL_GPIO_ReadPin(COL1_GPIO_Port,COL1_Pin) == 0)//���°���
	{
		if(LongPress3 == 0)//û�г�����
		{
			Key_Cnt3 += dT;//����ʱ��++
			Key_Flag3 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag3 == 1)//����������
	{
		if(HAL_GPIO_ReadPin(COL1_GPIO_Port,COL1_Pin) == 1)//̧�𰴼�
		{   
			if(Key_Cnt3 < 1.5)/*����*///С��1.5S�ǵ���
			{
				if(HAL_GPIO_ReadPin(BREAKEZ_GPIO_Port,BREAKEZ_Pin)== 1)//������պ�ʱ
				{
                    if(Show_Circle == 1)
                        Circle_Run = 1;
                    Speed_Val.SumError = 0x186A0;//������ ��ϵ��
                    SetOK_Flag = 1;//�趨ֵ
                    sys.Run_Status = 1;
                    sys.SetMode_Option = 0;
                    Speed_ADDMode = 0;
                    if(sys.Motor_Stop)//����ڽ��ٵ������
                        sys.Motor_Stop = 0;
				}
				else
				{
					Beep_Flash = 7;
					sys.Lock_On = 1;
				}
				Beep_Time = 0.1;//��������0.1S
			}
			Key_Flag3 = 0;//�����¼��������ȴ���һ�ΰ���
			LongPress3 = 0;//������־����
			Key_Cnt3 = 0;//��ť��������		
		}
		if(Key_Cnt3 > 1.5 && Key_Cnt3 < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(LongPress3 == 0)/*����*///���û��һֱһֱ������
			{
				LongPress3 = 1;//������־��һ
			}
		}
	}
	ROW1_H;
	ROW2_H;
	ROW3_L;
	/**************************************Stop��**************************************/
	if(HAL_GPIO_ReadPin(COL1_GPIO_Port,COL1_Pin) == 0)//���°���
	{
		Key_Cnt5 += dT;//����ʱ��++
		Key_Flag5 = 1;//�������±�־��һ
	}
	if(Key_Flag5 == 1)//����������
	{
		if(HAL_GPIO_ReadPin(COL1_GPIO_Port,COL1_Pin) == 1)//̧�𰴼�
		{   
			if(Key_Cnt5 < 1.5)//С��1.5S�ǵ���
			{
                if(sys.Run_Status == 1)
                {
                    sys.Motor_Stop = 1;//�����
                    Speed_ADDMode = 2;//�������ģʽ��
                }
                Beep_Time = 0.1;//��������0.1S
			}
			Key_Flag5 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt5 = 0;//��ť��������		
		}
		if(Key_Cnt5 > 1.9 && Key_Cnt5 < 2.1)//����ʱ�����1.9SС��2.1S��ʾ����
		{
			Key_Flag5 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt5 = 1.5;//��ť��������
		}
	}
	/**************************************OPEN��**************************************/
	if(HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_Pin )== 0)//���°���
	{
        if(sys.Motor_Stop == 0 && sys.Run_Status == 1)//�������ʾ��������ģʽ�¶����ܲ���
			return;
		if(LongPress6 == 0)//û�г�����
		{
			Key_Cnt6 += dT;//����ʱ��++
			Key_Flag6 = 1;//�������±�־��һ
		}
	}
	if(Key_Flag6 == 1)//����������
	{
		if(HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_Pin) == 1)//̧�𰴼�
		{   
			if(Key_Cnt6 < 1.5)//С��1.5S�ǵ���
			{
				if(HAL_GPIO_ReadPin(BREAKEZ_GPIO_Port,BREAKEZ_Pin)== 1)//������պ�ʱ
					Lock_Status = 1;//�򿪵����
				sys.Run_Status = 0;
				sys.Motor_Stop = 0;
				Beep_Time = 0.1;//��������0.1S
			}
			Key_Flag6 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt6 = 0;//��ť��������		
		}
		if(Key_Cnt6 > 1.9 && Key_Cnt6 < 2.1)//����ʱ�����1.9SС��2.1S��ʾ����
		{	
			Key_Flag6 = 0;//�����¼��������ȴ���һ�ΰ���
			Key_Cnt6 = 1.5;//��ť��������
		}
	}
}

