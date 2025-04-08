#include "Param.h"

/**********�ṹ��**********/
struct _Save_Param_ Param;//ԭʼ����

uint8_t Save_Param_En = 0;

void Param_Reset()
{
	Param.Flash_Check_Start = FLASH_CHECK_START;
	for(uint8_t i=0;i <= 9;i++)
	{
		Param.P_Param[i][0] = 370;
		Param.P_Param[i][1] = 1200;
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
		Set_Time=Param.P_Param[PMode_Option][1];//���������趨ʱ��Ϊ20min
		Set_Temp=Param.P_Param[PMode_Option][0];//���������趨�¶�37��
		SetOK_Flag = 1;
		Save_Param_En = 1;
	}
	else
	{
		Set_Time=Param.P_Param[PMode_Option][1];//���������趨ʱ��Ϊ20min
		Set_Temp=Param.P_Param[PMode_Option][0];//���������趨�¶�37��
		SetOK_Flag = 1;
	}
	
	//�������
	if(Save_Param_En)
	{
		Save_Param_En = 0;
		Param_Save();
	}
}

