#include "Param.h"

/**********�ṹ��**********/
struct _Save_Param_ Param;//ԭʼ����

/**********ȫ�ֱ�������******/
uint8_t Save_Param_En;

/*
*****************************************************************
 * ����ԭ�ͣ�void Param_Reset(void)
 * ��    �ܣ���ʼ��Ӳ���еĲ���
*****************************************************************
*/
void Param_Reset(void)
{
	Param.Flash_Check_Start = FLASH_CHECK_START;
	
	Param.Speed = 1500;//ת��
	Param.Time = 0;//ʱ��
	Param.type = 0;//0��10&15L 1��30L 2��50L
	
	Param.Flash_Check_End  = FLASH_CHECK_END;
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Param_Save(void)
 * ��    �ܣ�����Ӳ���еĲ���
*****************************************************************
*/
void Param_Save(void)
{
	Flash_Write((uint8_t *)(&Param),sizeof(Param));
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Param_Read(void)
 * ��    �ܣ���ȡӲ���еĲ������ж��Ƿ����
*****************************************************************
*/
void Param_Read(void)
{
	Flash_Read((uint8_t *)(&Param),sizeof(Param));
	
	//���Ӵ�δ��ʼ��
	if(Param.Flash_Check_Start != FLASH_CHECK_START || Param.Flash_Check_End != FLASH_CHECK_END)
	{
		Param_Reset();
		
		Speed.Set = Param.Speed;//ת��
		Time.Set = Param.Time;//ʱ��
		SpeedSet_Flag=TimeSet_Flag=1;//��������
		Save_Param_En = 1;//�������
	}
	else
	{
		Speed.Set = Param.Speed;//ת��
		Time.Set = Param.Time;//ʱ��
		SpeedSet_Flag=TimeSet_Flag=1;//��������
	}
	
	if(HAL_GPIO_ReadPin(EC11A[1].Key_GPIO,EC11A[1].Key_Pin) == KEY_DOWN)//���°���
	{
		Param.type++;
		if(Param.type > 2)
			Param.type = 0;
		Save_Param_En = 1;
		switch(Param.type)
		{
			case 0:
				Speed_MAX = 1500;
				POLE_NUMBER = 2;
				break;
			case 1:
				Speed_MAX = 1300;
				POLE_NUMBER = 5;
				break;
			case 2:
				Speed_MAX = 1100;
				POLE_NUMBER = 5;
				break;
		}
		Speed.Set = Speed_MAX;//ת��
	}
	
	switch(Param.type)
	{
		case 0:
			Speed_MAX = 1500;
			POLE_NUMBER = 2;
			break;
		case 1:
			Speed_MAX = 1300;
			POLE_NUMBER = 5;
			break;
		case 2:
			Speed_MAX = 1100;
			POLE_NUMBER = 5;
			break;
	}
	
	//�������
	if(Save_Param_En)
	{
		Save_Param_En = 0;//�����־����
		Param_Save();//����Ӳ���еĲ���
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Param_Save_Overtime(float dT)
 * ��    �ܣ������־λ��1��0.5s�󱣴�
*****************************************************************
*/
void Param_Save_Overtime(float dT)
{
	static float T;
	
	if(Save_Param_En)
	{
		T += dT;
		
		if(T >= 0.5f)//0.5s��
		{
			Param_Save();//����Ӳ���еĲ���
			Save_Param_En = 0;//�����־����
		}
	}
	else 
		T = 0;
}
