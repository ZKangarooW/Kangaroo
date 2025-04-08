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
	Param.Time = 300;//ʱ��
	#if(Type==0)
	Param.Speed = 5000;//ת��
	Param.Speed_Rcf = 8;//������
	#elif(Type==1)
	Param.Speed = 7000;//ת��
	Param.Speed_Rcf = 12;//������
	#endif
	Param.type = Type;//���ͱ仯
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
	if(Param.Flash_Check_Start != FLASH_CHECK_START || Param.Flash_Check_End != FLASH_CHECK_END || Param.type != Type)
	{
		Param_Reset();//��ʼ��Ӳ���еĲ���
		Time.Set_Time = Param.Time;//ʱ��
		Speed.Speed_Rcf = Param.Speed_Rcf;//������
		Speed.Set_Speed = Param.Speed;//ת��
		Save_Param_En = 1;//�����־λ��һ
		SetOK_Flag = 1;//���ñ�־λ��һ
	}
	else
	{
		Time.Set_Time = Param.Time;//ʱ��
		Speed.Speed_Rcf = Param.Speed_Rcf;//������	
		if(Speed.Speed_Mode)//������ģʽ��
			Speed.Set_Speed = Rcf[Param.Speed_Rcf];//������
		else//ת��ģʽ��
			Speed.Set_Speed = Param.Speed;//ת��
		SetOK_Flag = 1;//���ñ�־λ��һ
	}
	
	//�������
	if(Save_Param_En)
	{
		Param_Save();//���浽Flash
		Save_Param_En = 0;//�����־λ����
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
