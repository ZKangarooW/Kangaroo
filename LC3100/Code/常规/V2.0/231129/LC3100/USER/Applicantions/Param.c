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
	for(uint8_t i=0;i <= 9;i++)
	{
		Param.P_Param[i][0] = 300;//ʱ��
		Param.P_Param[i][1] = 2000;//ת��
		Param.P_Param[i][2] = 500;//��ȫ�¶�
		Param.P_Param[i][3] = 100;//������
		Param.P_Param[0][4] = 6;//������ģʽ  1������  6��96�װ�
	}
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
		Set_Time = Param.P_Param[PMode_Option][0];//ʱ��
		if(Speed_Unit)
			Set_Speed = Param.P_Param[PMode_Option][3];//������
		else
			Set_Speed = Param.P_Param[PMode_Option][1];//ת��
		Safe_Set_Temp = Param.P_Param[PMode_Option][2];//��ȫ�¶�
		Speed_Mode = Param.P_Param[0][4];//������ģʽ
		SetOK_Flag = 1;
		Save_Param_En = 1;
	}
	else
	{
		Set_Time = Param.P_Param[PMode_Option][0];//ʱ��
		if(Speed_Unit)
			Set_Speed = Param.P_Param[PMode_Option][3];//������
		else
			Set_Speed = Param.P_Param[PMode_Option][1];//ת��
		Safe_Set_Temp = Param.P_Param[PMode_Option][2];//��ȫ�¶�
		Speed_Mode = Param.P_Param[0][4];//������ģʽ
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
			Param_Save();
			Save_Param_En = 0;
		}
	}
	else 
		time = 0;
}
