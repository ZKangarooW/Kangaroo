#include "Param.h"

/**********�ṹ��**********/
struct _Save_Param_ Param;//ԭʼ����

/**********ȫ�ֱ�������******/
uint8_t Save_Param_En;//�����־λ

/*
*****************************************************************
 * ����ԭ�ͣ�void Param_Reset(void)
 * ��    �ܣ���ʼ��Ӳ���еĲ���
*****************************************************************
*/
void Param_Reset(void)
{
	Param.Flash_Check_Start = FLASH_CHECK_START;
	
	Param.P_Param[0] = 370;//�¶�
	Param.P_Param[1] = 100;//ת��
	Param.P_Param[2] = 0;//ʱ��
	
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
		Temp.Set_Temp = Param.P_Param[0];//�¶�
		Speed.Set_Speed = Param.P_Param[1];//ת��
		Time.Set_Time = Param.P_Param[2];//ʱ��
		SetOK_Flag = 1;
		Save_Param_En = 1;
	}
	else
	{
		Temp.Set_Temp = Param.P_Param[0];//�¶�
		Speed.Set_Speed = Param.P_Param[1];//ת��
		Time.Set_Time = Param.P_Param[2];//ʱ��
		SetOK_Flag = 1;
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
			Param_Save();//����Ӳ���еĲ���
			Save_Param_En = 0;//�رձ����־λ
		}
	}
	else 
		time = 0;
}
