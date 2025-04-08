#include "Param.h"

/**********�ṹ��**********/
struct _Save_Param_ Param; // ԭʼ����

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
	SetALL_int(100, &Param.Speed); // ��ʼ�������ٶ�
	SetALL_int32(0, &Param.Time);  // ��ʼ������ʱ��
	Param.Temp = 370;				   
#if (Integration_TYPE == 0)
	Param.type = 3;// 0��������1��������2������������3����������
#endif
	Param.Flash_Check_End = FLASH_CHECK_END;
}

/*
*****************************************************************
* ����ԭ�ͣ� void Param_Save(void)
* ��    �ܣ� ����Ӳ���еĲ���
*****************************************************************
*/
void Param_Save(void)
{
	Flash_Write((uint8_t *)(&Param), sizeof(Param));
}

/*
*****************************************************************
* ����ԭ�ͣ�void Param_Read(void)
* ��    �ܣ���ȡӲ���еĲ������ж��Ƿ����
*****************************************************************
*/
void Param_Read(void)
{
	Flash_Read((uint8_t *)(&Param), sizeof(Param));

	// ���Ӵ�δ��ʼ��
	if (Param.Flash_Check_Start != FLASH_CHECK_START || Param.Flash_Check_End != FLASH_CHECK_END)
	{
		Param_Reset();
		SetALL_SpeedOver(&Set_Speed, &Param.Speed);
		SetALL_TimeOver(&Set_Time, &Param.Time);
		Set_Temp = Param.Temp;
		SetOK_Flag = 1;
		Save_Param_En = 1;
	}
	else
	{
		SetALL_SpeedOver(&Set_Speed, &Param.Speed);
		SetALL_TimeOver(&Set_Time, &Param.Time);
		Set_Temp = Param.Temp;
		SetOK_Flag = 1;
	}

#if (Integration_TYPE == 0)												   // ������
	if (HAL_GPIO_ReadPin(EC11A[1].Key_GPIO, EC11A[1].Key_Pin) == KEY_DOWN) // ���°���
	{
		Param.type++;
		if (Param.type > 3)
			Param.type = 0;
		Save_Param_En = 1;
		if (Param.type <= 1)
		{
			MAX_Speed = 1500;
		}
		else
		{
			MAX_Speed = 1200;
		}
		SetALL_int(100, &Param.Speed); // ��ʼ�������ٶ�
		SetALL_SpeedOver(&Set_Speed, &Param.Speed);
		SetALL_int32(0, &Param.Time); // ��ʼ������ʱ��
		Param.Temp = 0;
		SetALL_TimeOver(&Set_Time, &Param.Time);
		Set_Temp = Param.Temp;
	}

	if (Param.type <= 1)
		MAX_Speed = 1500;
	else
		MAX_Speed = 1200;
#elif (Integration_TYPE == 1) // ����
	MAX_Speed = 1500;
#endif

	// �������
	if (Save_Param_En)
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

	if (Save_Param_En)
	{
		time += dT;

		if (time >= 0.5f)
		{
			Param_Save();
			Save_Param_En = 0;
		}
	}
	else
		time = 0;
}
