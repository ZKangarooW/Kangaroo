#include "Param.h"

/**********�ṹ��**********/
struct _Save_Param_ Param;//ԭʼ����

/**********ȫ�ֱ�������******/
uint8_t Save_Param_En;//���浽Flash�ı�־λ

/*
*****************************************************************
 * ����ԭ�ͣ�void Param_Reset(void)
 * ��    �ܣ���ʼ��Ӳ���еĲ���
*****************************************************************
*/
void Param_Reset(void)
{
	Param.Flash_Check_Start = FLASH_CHECK_START;
	Param.Time = 120;//ʱ��
	Param.Mode = 0;//�ٶ�ģʽ
	Param.type = 2;//0������� 1��2P 2��3D 3������ƿ

	if(Param.type==0)
		Param.Speed = 3000;//ת��
	else if(Param.type==1)
		Param.Speed = 1200;//ת��
	else if(Param.type==2)
		Param.Speed = 80;//ת��
	else if(Param.type==3)
		Param.Speed = 2000;//ת��
	
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
		Param_Reset();//��ʼ��Ӳ���еĲ���
		Set_Time = Param.Time;//ʱ��
		Set_Speed = Param.Speed;//ת��
		Speed_Mode = Param.Mode;//�ٶ�ģʽ
		Save_Param_En = 1;//�����־λ��һ
		SetOK_Flag = 1;//���ñ�־λ��һ
	}
	else
	{
		Set_Time = Param.Time;//ʱ��
		Set_Speed = Param.Speed;//ת��
		Speed_Mode = Param.Mode;//�ٶ�ģʽ
		SetOK_Flag = 1;//���ñ�־λ��һ
	}
	
	if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin) == 0 && HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)== 0)//���°���
	{
		Param.type++;
		if(Param.type > 3)
			Param.type = 0;
		Save_Param_En = 1;
		switch(Param.type)
		{
			case 0://����
				Speed_MAX = 3000;
				Set_Speed = Speed_MAX;//ת��
				Param.Time = 120;//ʱ��
				Speed_Mode = Param.Mode = 0;
				break;
			case 1://2P
				Speed_MAX = 1200;
				Set_Speed = Speed_MAX;//ת��
				Param.Time = 120;//ʱ��
				Speed_Mode = Param.Mode = 1;
				break;
			case 2://3D
				Speed_MAX = 80;
				Set_Speed = Speed_MAX;//ת��
				Param.Time = 120;//ʱ��
				Speed_Mode = Param.Mode = 1;
				break;
			case 3://����ƿ
				Speed_MAX = 2000;
				Set_Speed = Speed_MAX;//ת��
				Param.Time = 120;//ʱ��
				Speed_Mode = Param.Mode = 1;
				break;
		}
		Param.Speed = Speed_MAX;
	}
	switch(Param.type)
	{
		case 0://����
			Speed_MAX = 3000;
			break;
		case 1://1P 2P
			Speed_MAX = 1200;
			break;
		case 2://3D
			Speed_MAX = 80;
            break;
		case 3://����ƿ
			Speed_MAX = 2000;
			break;
	}
	
	//�������
	if(Save_Param_En)
	{
		Save_Param_En = 0;//�����־λ����
		Param_Save();//���浽Flash
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
	
	if(Save_Param_En)//���뱣���־λ��һ
	{
		T += dT;//ʱ�����dT
		
		if(T >= 0.5f)//����0.5Sʱ
		{
			Param_Save();//���浽Flash
			Save_Param_En = 0;//�����־λ����
		}
	}
	else 
		T = 0;//ʱ������
}
