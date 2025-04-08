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
	
	Param.P_Param[0] = 300;//ʱ��
	Param.P_Param[2] = 1700;//������
	Param.type = 1;
	
	if(Param.type==0)
		Param.P_Param[1] = 5000;//ת��
	else if(Param.type==1)
		Param.P_Param[1] = 4000;//ת��
	else if(Param.type==2)
		Param.P_Param[1] = 4500;//ת��
		
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
		Time.Set = Param.P_Param[0];//ʱ��
		if(Speed.Unit)
			Speed.Set = Param.P_Param[2];//������
		else
			Speed.Set = Param.P_Param[1];//ת��
		SetOK_Flag = 1;//����
		Save_Param_En = 1;//����
	}
	else
	{
		Time.Set = Param.P_Param[0];//ʱ��
		if(Speed.Unit)
			Speed.Set = Param.P_Param[2];//������
		else
			Speed.Set = Param.P_Param[1];//ת��
		SetOK_Flag = 1;//����
	}
	
	if(!KEY2 && !KEY3)
	{
		Param.type++;
		if(Param.type > 2)
			Param.type = 0;
		Save_Param_En = 1;
		switch(Param.type)
		{
			case 0:
				Speed_MAX = 5000;
				Xg_MAX = 2600;
				if(Speed.Unit)
					Speed.Set = Xg_MAX;//������
				else
					Speed.Set = Speed_MAX;//ת��
				break;
			case 1:
				Speed_MAX = 4000;
				Xg_MAX = 1700;
				if(Speed.Unit)
					Speed.Set = Xg_MAX;//������
				else
					Speed.Set = Speed_MAX;//ת��
				break;
			case 2:
				Speed_MAX = 4500;
				Xg_MAX = 2150;
				if(Speed.Unit)
					Speed.Set = Xg_MAX;//������
				else
					Speed.Set = Speed_MAX;//ת��
				break;
		}
		Param.P_Param[1] = Speed_MAX;
		Param.P_Param[2] = Xg_MAX;
	}
	switch(Param.type)
	{
		case 0:
			Speed_MAX = 5000;
			Xg_MAX = 2600;
			break;
		case 1:
			Speed_MAX = 4000;
			Xg_MAX = 1700;
			break;
		case 2:
			Speed_MAX = 4500;
			Xg_MAX = 2150;
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
