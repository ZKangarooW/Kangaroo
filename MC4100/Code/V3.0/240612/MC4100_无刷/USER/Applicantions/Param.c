#include "Param.h"

/**********�ṹ��**********/
struct _Save_Param_ Param;//ԭʼ����

/**********ȫ�ֱ�������******/
uint8_t Save_Param_En;

#define FLASH_CHECK_START 0xAA
#define FLASH_CHECK_END 0xC2

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
		Param.P_Param[i][3] = 100;//������
		Param.type = 2;//0��15Pro  1��13Pro 2��12Pro
        if(Param.type==0)
            Param.P_Param[i][1] = 14500;//ת��
        else if(Param.type==1)
            Param.P_Param[i][1] = 13000;//ת��
        else if(Param.type==2)
            Param.P_Param[i][1] = 12000;//ת��
        
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
		Set_Speed = Param.P_Param[PMode_Option][1];//ת��
		Safe_Set_Temp = Param.P_Param[PMode_Option][2];//��ȫ�¶�
		SetOK_Flag = 1;
		Save_Param_En = 1;
	}
	else
	{
		Set_Time = Param.P_Param[PMode_Option][0];//ʱ��
		if(Speed_Mode)
			Set_Speed = Param.P_Param[PMode_Option][3];//������
		else
			Set_Speed = Param.P_Param[PMode_Option][1];//ת��
		Safe_Set_Temp = Param.P_Param[PMode_Option][2];//��ȫ�¶�
		SetOK_Flag = 1;
	}
	
	ROW1_H;
	ROW2_H;
	ROW3_L;
	if(HAL_GPIO_ReadPin(COL1_GPIO_Port,COL1_Pin) == 0 && HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_Pin )== 0)
	{
		Param.type++;
		if(Param.type > 2)
			Param.type = 0;
		Save_Param_En = 1;
		switch(Param.type)
		{
			case 0:
				Speed_MAX = 14500;
				Xg_MAX = 14100;
				break;
			case 1:
				Speed_MAX = 13000;
				Xg_MAX = 11300;
				break;
			case 2:
				Speed_MAX = 12000;
				Xg_MAX = 10000;
				break;
		}
		for(uint8_t i=0;i <= 9;i++)
		{
			Param.P_Param[i][0] = 300;//ʱ��
			Param.P_Param[i][1] = Speed_MAX;//ת��
			Param.P_Param[i][2] = 500;//��ȫ�¶�
			Param.P_Param[i][3] = 100;//������
		}
		Set_Speed =  Param.P_Param[0][1];
	}
		
	switch(Param.type)
	{
		case 0:
			Speed_MAX = 14500;
			Xg_MAX = 14100;
			break;
		case 1:
			Speed_MAX = 13000;
			Xg_MAX = 11300;
			break;
		case 2:
			Speed_MAX = 12000;
			Xg_MAX = 10000;
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
