#include "Ctrl_Motor.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void Motor_Ctrl(float dT)
 * ��    �ܣ��������
*****************************************************************
*/
void Motor_Ctrl(float dT)
{   
	static uint8_t Convert_Set,Ctrl_Val;//pwm��ֵ
    if(sys.Run_Status == 1)//����
    {
		if((HAL_GPIO_ReadPin(KEY_UP_GPIO_Port,KEY_UP_Pin)== 1))//���ӱպ�ʱ
		{
			if(Speed.Ctrl_Speed && ((Time.DownTime_Over == 0)||(Time.Ctrl_Time)))//�ٶȴ���0�Ͷ�ʱ��û�н���
			{
				switch(Speed.Ctrl_Speed)//��������ٶȵ�PWMֵ
				{
					case 1000: Convert_Set = 4;//1018
						break;
					case 1500: Convert_Set = 6;//1510
						break;
					case 2000: Convert_Set = 9;//2014
						break;
					case 2500: Convert_Set = 16;//2500
						break;
					case 3000: Convert_Set = 26;//3010
						break;
					case 3500: Convert_Set = 40;//3514
						break;
					case 4000: Convert_Set = 59;//3984
						break;
					case 4500: Convert_Set = 78;//4498
						break;
					case 5000: Convert_Set = 106;//5010
						break;
					case 5500: Convert_Set = 145;//5507
						break;
					case 6000: Convert_Set = 162;//6010
						break;
					case 6500: Convert_Set = 180;//6477
						break;
					case 7000: Convert_Set = 180;//6477
						break;
					default: Convert_Set=0;//ֹͣ
						break;
				}
				if(Ctrl_Val < Convert_Set)//�������ֵС��Ҫ�ﵽ��ֵ
				{
					Ctrl_Val++;//����ֵ++
					if(Speed.Speed_Mode==0)//�ٶ�	
					{
						Speed.Rel_Speed = ((float)Ctrl_Val/(float)Convert_Set)*Speed.Ctrl_Speed;//�������������ֵ�µ��ٶ�
					}
					else//������
					{
						Speed.Rel_Speed = ((float)Ctrl_Val/(float)Convert_Set)*Speed.Ctrl_Speed;//�������������ֵ�µ��ٶ�
						Speed.Rel_Speed = 11.18*(Speed.Rel_Speed/1000)*(Speed.Rel_Speed/1000)*6;//���ٶȼ���������
					}
				}
				PWM = Ctrl_Val;//PWM��ֵ
			}
			else
			{
				if(Ctrl_Val)
				{
					Ctrl_Val--;
					if(Speed.Speed_Mode==0)//�ٶ�	
					{
						Speed.Rel_Speed = ((float)Ctrl_Val/(float)Convert_Set)*Speed.Ctrl_Speed;//�������������ֵ�µ��ٶ�
					}
					else//������
					{
						Speed.Rel_Speed = ((float)Ctrl_Val/(float)Convert_Set)*Speed.Ctrl_Speed;//�������������ֵ�µ��ٶ�
						Speed.Rel_Speed = 11.18*(Speed.Rel_Speed/1000)*(Speed.Rel_Speed/1000)*6;//���ٶȼ���������
					}
				}
				else//�ٶ�Ϊ��ʱ
				{
					sys.Run_Status = 0;//�ر�ϵͳ
				}
				PWM = Ctrl_Val;//PWM��ֵ
			}
		}
		else//���Ӵ�
		{
			sys.Run_Status = 0;//�ر�ϵͳ
			Speed.Rel_Speed = 0;//��������ʾһֱʱʵ��ת��
			Ctrl_Val = 0;//����ֵ����
			PWM = Ctrl_Val;//PWM��ֵ
		}
    }
    else//ϵͳ�ر�
    {
		if(Ctrl_Val)//����ֵδ����
		{
			Ctrl_Val--;//����ֵ--
			if(Speed.Speed_Mode==0)//�ٶ�	
			{
				Speed.Rel_Speed = ((float)Ctrl_Val/(float)Convert_Set)*Speed.Ctrl_Speed;//�������������ֵ�µ��ٶ�
			}
			else//������
			{
				Speed.Rel_Speed = ((float)Ctrl_Val/(float)Convert_Set)*Speed.Ctrl_Speed;//�������������ֵ�µ��ٶ�
				Speed.Rel_Speed = 11.18*(Speed.Rel_Speed/1000)*(Speed.Rel_Speed/1000)*6;//���ٶȼ���������
			}
		}
		PWM = Ctrl_Val;//PWM��ֵ
    }      
}
