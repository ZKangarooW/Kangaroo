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
	
	Param.Heat_Temp = 450;//��ʼ�¶�45��
	Param.Cool_Temp = 260;//��ʼ�¶�26��
	Param.CountDown_Time = 1200;//20����
	
	Param.Calibration_Temp = 1.0;//�¶�У׼ϵ��
	
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
		Heat_Temp.Set_Temp = Param.Heat_Temp;//���������¶�
		Cool_Temp.Set_Temp = Param.Cool_Temp;//���������¶�
		Time.Set_Time = Param.CountDown_Time;//����ʱʱ��
		Calibration_Temp = Param.Calibration_Temp;//�¶�У׼ϵ��
		SetOK_Flag = 1;
		Save_Param_En = 1;
	}
	else
	{
		Heat_Temp.Set_Temp = Param.Heat_Temp;//���������¶�
		Cool_Temp.Set_Temp = Param.Cool_Temp;//���������¶�
		Time.Set_Time = Param.CountDown_Time;//����ʱʱ��
		Calibration_Temp = Param.Calibration_Temp;//�¶�У׼ϵ��
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
