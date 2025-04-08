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
	for(uint8_t i=0;i <= 8;i++)
	{
		Param.P_Param[i][0] = 300;//ʱ��
		Param.P_Param[i][1] = 2300;//ת��
		Param.P_Param[i][2] = 500;//��ȫ�¶�
		Param.P_Param[i][3] = 100;//������
	}
    /***************CGF*******************/
    Param.P_Param[1][0] = 840;//ʱ��
    Param.P_Param[1][1] = 2450;//ת��
    Param.P_Param[2][1] = 2150;//ת��
    Param.P_Param[3][1] = 2450;//ת��
    Param.P_Param[4][1] = 2690;//ת��
    /***************PrP*******************/
    Param.P_Param[5][0] = 300;//ʱ��
    Param.P_Param[5][1] = 3930;//ת��
    /***************APrF******************/
    Param.P_Param[6][0] = 720;//ʱ��
    Param.P_Param[6][1] = 1300;//ת��
    /***************IPrF******************/
    Param.P_Param[7][0] = 300;//ʱ��
    Param.P_Param[7][1] = 680;//ת��
    
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
		Time.Set = Param.P_Param[PMode.Option][0];//ʱ��
		SafeTemp.Set = Param.P_Param[PMode.Option][2];//��ȫ�¶�
        if(Speed.Unit)
			Speed.Set = Param.P_Param[PMode.Option][3];//������
		else
			Speed.Set = Param.P_Param[PMode.Option][1];//ת��
		SetOK_Flag = 1;
		Save_Param_En = 1;
	}
	else
	{
		Time.Set = Param.P_Param[PMode.Option][0];//ʱ��
		SafeTemp.Set = Param.P_Param[PMode.Option][2];//��ȫ�¶�
        if(Speed.Unit)
			Speed.Set = Param.P_Param[PMode.Option][3];//������
		else
			Speed.Set = Param.P_Param[PMode.Option][1];//ת��
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
