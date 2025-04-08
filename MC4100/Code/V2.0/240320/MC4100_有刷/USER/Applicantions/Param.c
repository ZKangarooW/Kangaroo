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
		Param.P_Param[i][2] = 500;//��ȫ�¶�
		Param.P_Param[i][3] = 0;//������
		Param.type = 1;//0��12Pro  1��10Pro
		Param.P_Param[i][1] = 110;//ת��
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
		Val_xg = Param.P_Param[PMode_Option][3];//������
		Val_Speed = Param.P_Param[PMode_Option][1];//�ٶ�����
		Set_Speed =  Speed_Val[Val_Speed];
		Safe_Set_Temp = Param.P_Param[PMode_Option][2];//��ȫ�¶�
		SetOK_Flag = 1;
		Save_Param_En = 1;
	}
	else
	{
		Set_Time = Param.P_Param[PMode_Option][0];//ʱ��
		if(Speed_Mode)
		{
			Val_xg = Param.P_Param[PMode_Option][3];//����������
			Set_Speed = xg_Val[Val_xg];
		}	
		else
		{
			Val_Speed = Param.P_Param[PMode_Option][1];//�ٶ�����
			Set_Speed =  Speed_Val[Val_Speed];
		}
		
		Safe_Set_Temp = Param.P_Param[PMode_Option][2];//��ȫ�¶�
		SetOK_Flag = 1;
	}
	
	ROW1_H;
	ROW2_H;
	ROW3_L;
	if(HAL_GPIO_ReadPin(COL1_GPIO_Port,COL1_Pin) == 0 && HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_Pin )== 0)
	{
		Param.type++;
		if(Param.type > 1)
			Param.type = 0;
		Save_Param_En = 1;
		switch(Param.type)
		{
			case 0:
				Speed_MAX = 110;
				break;
			case 1:
				Speed_MAX = 90;
				break;
		}
		for(uint8_t i=0;i <= 9;i++)
		{
			Param.P_Param[i][0] = 300;//ʱ��
			Param.P_Param[i][2] = 500;//��ȫ�¶�
			Param.P_Param[i][3] = 0;//������
			Param.P_Param[i][1] = Speed_MAX;//ת��
		}
		Set_Speed =  Speed_Val[Speed_MAX];
	}
	
	switch(Param.type)
	{
		case 0:
			Speed_MAX = 110;
			break;
		case 1:
			Speed_MAX = 90;
			break;
	}
	
	//�������
	if(Save_Param_En == 1)
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
