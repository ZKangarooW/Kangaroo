#include "Drv_Touch.h"

/**********ȫ�ֱ�������*******/
float Key_Status = 0;//�ڲ���������ʱ��

/**********�ֲ���������*******/
float Key_Cnt1, Key_Cnt2, Key_Cnt3 = 0;//����ʱ��
bit Key_Flag1, Key_Flag2, Key_Flag3 = 0;//�������±�־
bit LongPress1, LongPress2, LongPress3 = 0;//����������־
float UPPress_Time, DownPress_Time = 0;      
uint32_t exKeyValueFlag = 0;//��ֵTK0��Ӧ0x00000001��TK1��Ӧ0x00000002���������ơ�

/**
 * @brief ������ʼ��
 *
 */
void Drv_Touch_Init(void)
{
	TouchKeyInit();//���ÿ⺯������ʼ��TouchKey
}

/**
 * @brief ��ֵ����
 *
 * @param dT ��������
 */
void ChangeTouchKeyvalue(float dT)
{
    /******************************Start��******************************/
	if (exKeyValueFlag == Key1)//���°���
	{
		if (LongPress1 == 0)//û�г�����
		{
			Key_Cnt1 += dT;//����ʱ��++
			Key_Flag1 = 1;//�������±�־��һ
		}
	}
	else if (Key_Flag1)//����������
	{
		if (exKeyValueFlag != Key1)//̧�𰴼�
		{
			if (Key_Cnt1 > 0.05f && Key_Cnt1 < 1.5f)//����ʱ�����0.05SС��1.5S�ǵ���
			{
				if(sys.Run_Status)
				{
					sys.Run_Status = 0;
				}
				else
				{
					sys.Run_Status = 1;
					Speed_Val.Integral = 100;
				}
				Beep_Time = 0.1f;//��������0.1S
				
			}
		}
		Key_Flag1 = 0;//�����¼��������ȴ���һ�ΰ���
		LongPress1 = 0;//������־λ����
		Key_Cnt1 = 0;//��ť��������
	}
	if (Key_Cnt1 > 1.5f && Key_Cnt1 < 3.0f)//����ʱ�����1.5SС��3S��ʾ����
	{
		if (LongPress1 == 0)//���û��һֱ������
		{
			
			LongPress1 = 1;//������־��һ
		}
	}
	
	/******************************�Ӽ�******************************/
    if(exKeyValueFlag == Key2)//���°���
    {
        UPPress_Time += dT;//����ʱ��Ӽ�
        Key_Cnt2 += dT;//����ʱ��++
        Key_Flag2 = 1;//�������±�־��һ
    }
    if(Key_Flag2)//����������
    {
        if(exKeyValueFlag != Key2)//̧�𰴼�
        {
            if(Key_Cnt2 < 1.5f)//����ʱ��С��1.5S�ǵ���
            {

//                Beep_Time = 0.1f;//��������0.1S
            }
            Key_Flag2 = 0;//�����¼��������ȴ���һ�ΰ���
            Key_Cnt2 = 0;//��ť��������
        }
        else if (Key_Cnt2 > 1.9f && Key_Cnt2 < 2.1f)//����ʱ�����1.9SС��2.1S��ʾ����
        {
			if (UPPress_Time > 5.0f)
			{
				//+10
			}
			else
			{
				//++ 
			}
            if (UPPress_Time > 5.0f)
            {
                Key_Cnt2 = 1.82f;//��������ʱ�临λ
            }
            else
            {
                Key_Cnt2 = 1.88f;
            }
            Key_Flag2 = 0;//�����¼��������ȴ���һ�ΰ���
        }
    }
    else
    {
        UPPress_Time = 0;
        Key_Cnt2 = 0; // ������������
    }
	
	/******************************����******************************/
    if(exKeyValueFlag == Key3)//���°���
    {
        DownPress_Time += dT;//����ʱ��Ӽ�
        Key_Cnt3 += dT;//����ʱ��++
        Key_Flag3 = 1;//�������±�־��һ
    }
    if(Key_Flag3)//����������
    {
        if(exKeyValueFlag != Key3)//̧�𰴼�
        {
            if(Key_Cnt3 < 1.5f)//����ʱ��С��1.5S�ǵ���
            {

//                Beep_Time = 0.1f;//��������0.1S
            }
            Key_Flag3 = 0;//�����¼��������ȴ���һ�ΰ���
            Key_Cnt3 = 0;//��ť��������
        }
        else if (Key_Cnt3 > 1.9f && Key_Cnt3 < 2.1f)//����ʱ�����1.9SС��2.1S��ʾ����
        {
			if (DownPress_Time > 5.0f)
			{
				//+10
			}
			else
			{
				//++ 
			}
            if (DownPress_Time > 5.0f)
            {
                Key_Cnt3 = 1.82f;//��������ʱ�临λ
            }
            else
            {
                Key_Cnt3 = 1.88f;
            }
            Key_Flag3 = 0;//�����¼��������ȴ���һ�ΰ���
        }
    }
    else
    {
        DownPress_Time = 0;
        Key_Cnt3 = 0; // ������������
    }
}

/**
 * @brief ����ɨ��
 *
 * @param dT ��������
 */
void Touch_Scan(float dT)
{
	if(SOCAPI_TouchKeyStatus&0x80)//��Ҫ����2:  ������ɨ��һ�ֱ�־���Ƿ����TouchKeyScan()һ��Ҫ���ݴ˱�־λ�����
	{	   																	
		SOCAPI_TouchKeyStatus &=0x7f;//��Ҫ����3: �����־λ�� ��Ҫ�ⲿ�����													    
		exKeyValueFlag = TouchKeyScan();//ɨ��õ���ֵ
		ChangeTouchKeyvalue(dT);//��ֵ����
		TouchKeyRestart();//������һ��ת�� 																 			
	}			
}

/**
 * @brief ��ⰴ��״̬
 *
 * @param dT ��������
 */
void Check_Press(float dT)
{
    if (Key_Status)
        Key_Status -= dT;
}

 