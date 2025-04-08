#include "Param.h"

/**********�ṹ��**********/
struct _Save_Param_ Param;//ԭʼ����

uint8_t Save_Param_En = 0;

void Param_Reset()
{
	Param.Flash_Check_Start = FLASH_CHECK_START;
	for(uint8_t i=0;i <= 9;i++)
	{
		Param.P_Param[i][0] = 0;
		Param.P_Param[i][1] = 0;
	}
	Param.Flash_Check_End  = FLASH_CHECK_END;
}

/*
*****************************************************************
 * ����ԭ�ͣ� void JD_Param_Save(void)
 * ��    �ܣ� ����Ӳ���еĲ���
*****************************************************************
*/
void Param_Save(void)
{
	Flash_Write((uint8_t *)(&Param),sizeof(Param));
}

void Param_Read(void)
{
	Flash_Read((uint8_t *)(&Param),sizeof(Param));
	
	//���Ӵ�δ��ʼ��
	if(Param.Flash_Check_Start!=FLASH_CHECK_START || Param.Flash_Check_End!=FLASH_CHECK_END)
	{
		Param_Reset();
//		set_time=Param.P_Param[run_mode][1];//���������趨ʱ��Ϊ20min
		set_temp=Param.P_Param[run_mode][0];//���������趨�¶�37��
		SetOK_Flag = 1;
		Save_Param_En = 1;
	}
	else
	{
//		set_time=Param.P_Param[run_mode][1];//���������趨ʱ��Ϊ20min
		set_temp=Param.P_Param[run_mode][0];//���������趨�¶�37��
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

