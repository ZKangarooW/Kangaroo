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
		Param.Time = 0;//ʱ��
		Param.Speed = 3000;//ת��
	Param.type = 0;//0��3000 1:1200
	Param.Flash_Check_End  = FLASH_CHECK_END;
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Param_Save(void)
 * ��    �ܣ� ����Ӳ���еĲ���
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
		Set_Time = Param.Time;//ʱ��
		Set_Speed = Param.Speed;//ת��
		SpeedSet_Flag=TimeSet_Flag=1;//��������
		Save_Param_En = 1;
	}
	else
	{
		Set_Time = Param.Time;//ʱ��
		Set_Speed = Param.Speed;//ת��
		SpeedSet_Flag=TimeSet_Flag=1;//��������
	}
	
	if(HAL_GPIO_ReadPin(EC11A[1].Key_GPIO,EC11A[1].Key_Pin) == KEY_DOWN)//���°���
	{
		Param.type++;
		if(Param.type > 1)
			Param.type = 0;
		Save_Param_En = 1;
		switch(Param.type)
		{
			case 0:
				Speed_MAX = 3000;
				Speed_MIN = 1500;
				Param.Time = 0;//ʱ��
				Set_Time = Param.Time;//ʱ��
				break;
			case 1:
				Speed_MAX = 1200;
				Speed_MIN = 500;
				Param.Time = 0;//ʱ��
				Set_Time = Param.Time;//ʱ��
				break;
		}
		Set_Speed = Speed_MAX;//ת��
	}
	
	switch(Param.type)
	{
		case 0:
			Speed_MAX = 3000;
			Speed_MIN = 1500;
			break;
		case 1:
			Speed_MAX = 1200;
			Speed_MIN = 500;
			break;
	}
	
	//�������
	if(Save_Param_En)
	{
		Save_Param_En = 0;
		Param_Save();
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
	static float time;
	
	if(Save_Param_En)
	{
		time += dT;
		
		if(time >= 0.5f)
		{
			Param_Save();
			Save_Param_En = 0;
		}
	}
	else 
		time = 0;
}
