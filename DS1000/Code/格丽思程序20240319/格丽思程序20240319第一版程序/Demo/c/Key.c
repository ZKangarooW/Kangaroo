#include "Key.h"
#include "Led.h"
#include "CheckTouchKey_80F73xx.h"
#include "Buzzer.h"
#include "time.h"
#include "Temp.h"

unsigned char xdata KeyProcessFlag;	//����������λ

KeyValue_t KeyValueScan;

SystemState_t State;
SystemState_t Pre_State; //���ǰ��״̬

int SelfTest_Valid = 1; //�Ƿ���Խ����Լ�״̬


/*****************************************************************************
 ** \brief	 Kscan
 **
 ** \param [in]  none   
 **
 ** \return 0
 *****************************************************************************/
void Kscan(void)
{
	static unsigned long int xdata KeyOldFlag = 0;
	unsigned long int xdata KeyOnOutput = KeyFlag;
	if(KeyOnOutput)
	{
		if(KeyOnOutput != KeyOldFlag)
		{
			KeyOldFlag = KeyOnOutput;			//�м�⵽����
			if(0x1 == KeyOnOutput)				//����
			{
				KeyValueScan = On_Off;
			}
			else if(0x2 == KeyOnOutput)		//����
			{
				KeyValueScan = Function;
			}
			else if(0x4 == KeyOnOutput)		//���
			{
				KeyValueScan = Boil;
			}
			else if(0x8 == KeyOnOutput)		// +
			{
				KeyValueScan = Add;
			}
			else if(0x10 == KeyOnOutput)	// -
			{
				KeyValueScan = Sub;
			}
		}
	}
	else
	{
		KeyOldFlag = 0;
		KeyValueScan = Free;
		KeyProcessFlag = 1;		//���������󣬲������´�����ֵ
	}
}


/**********************************************************
�������ƣ� KeyProcess(void)
�������ܣ� ��������
���������
���������
***********************************************************/
void KeyProcess(void)
{
	static int count = 0;
	static int PowerOnCount = 0;
	int DisplayNow = 0;
	DisplayNow = GetData1();
	count++;
	
	if(PowerOnCount < 30)
	{
		PowerOnCount++; //������ʱ3s�������Լ�����ж�
	}
	
	if(PowerOnCount < 5 ){
		//0.5s���ٽ��밴�����״̬
		return;
	}else if(PowerOnCount == 5)
	{ 
		//0.5s�������ʾ,���밴�����״̬
		DisplayNum[0] = 11;
  	DisplayNum[1] = 11;
		DisplayNum[2] = 11;
		DisplayNum[3] = 11;
		SetSpecialData1(0);
		SetSpecialData2(0);
		SetLed(6);
	}else if(PowerOnCount == 30)
	{
		//�ϵ�3s���޷������Լ�״̬
		SelfTest_Valid = 0;
	}
	
	if((State == SelfTest) && (Err == 1))
	{
			//�Լ�״̬��δ��⵽ntc�������ʾ88 88 
			SetData1(88);
			SetData2(88);
	}
	
	if(Cnt.TimeTo3s > 30) //3s��˸���趨ֵ��Ч
	{
		Num1Valid = 1; //�趨ֵ�޸ĺ���ȴ�3s����Ч
	}

	if((Cnt.TimeTo3s < 30) && (Err == 1) && (DisplayNow == 0) && (State != PowerOn) && (State != SelfTest)) //��˸���ʱ����ˮ������ʾ�趨ֵ
	{
		if(State == Temp100)
		{
			SetData1(100); //��г�����ʾ100��
		}
		else
		{
			SetData1(DisplayNum1); //���๦����ʾԭ���趨ֵ
		}
		
	}
	
	//NTC���ϣ�����δ����ʱ�����в���
	if((0 == KeyProcessFlag) || (Err == 1))   
	{
		return;
	}
	KeyProcessFlag = 0;
	
	
	switch(State)
	{
		//�ϵ���ʾ��-- -- ledȫ���ر�
		case PowerOn:
		{
			DisplayNum[0] = 11;
			DisplayNum[1] = 11;
			DisplayNum[2] = 11;
			DisplayNum[3] = 11;
			SetSpecialData1(0);
			SetSpecialData2(0);
			SetLed(6);
			led1sValid = 0;
			
			DisplayNum1 = 0;
			
			if(KeyValueScan == On_Off)
			{
				BeepSet(80, 1);
				State = Temp45;
				Pre_State = Temp45;
				DisplayNum1 = 45;
				SetData1(DisplayNum1);
				Num1Valid = 0;		//�趨ֵ��˸3s����Ч
				Cnt.TimeTo3s = 0;
				count = 0;
				SelfTest_Valid = 0; //����������������ʱ�����޷������Լ�״̬
			}
			
			break;
		}
		case Temp45:			//45��״̬
		{
			SetLed(0);	//��һ��led����

			if(Cnt.TimeTo3s < 30 && Cnt.TimeTo3s > 3) //500ms��3000ms�ڿ�����˸
			{
				if(count> 4) // 500ms������˸
				{
					count=0;
					if(DisplayNow == 0)
					{
						SetData1(DisplayNum1);
					}else{
						DisplayNum[0] = 12;
						DisplayNum[1] = 12;
						SetSpecialData1(1);
					}
				}
			}else if(DisplayNow == 0){
				SetData1(DisplayNum1);
			}
			
			
			
			if(KeyValueScan == On_Off)
			{
				BeepSet(80, 1);
				State = PowerOn;
				count = 0;
			}else if(KeyValueScan == Function)
			{
				BeepSet(80, 1);
				State = Temp55;
				DisplayNum1 = 55;
				SetData1(DisplayNum1);
				Num1Valid = 0;		//�趨ֵ��˸3s����Ч
				Cnt.TimeTo3s = 0;
				count = 0;
			}else if(KeyValueScan == Boil)
			{
				BeepSet(80, 1);
				State = Temp100;
				SetData1(100);
				Num1Valid = 0;		//�趨ֵ��˸3s����Ч
				Pre_State = Temp45;
				Cnt.TimeTo3s = 30;
				count = 0;
			}else if(KeyValueScan == Add)
			{
				BeepSet(80, 1);
				AddProcess();
				Num1Valid = 0;		//�趨ֵ��˸3s����Ч
				Cnt.TimeTo3s = 0;
				count = 0;
			}else if(KeyValueScan == Sub)
			{
				BeepSet(80, 1);
				Num1Valid = 0;		//�趨ֵ��˸3s����Ч
				SubProcess();
				Cnt.TimeTo3s = 0;
				count = 0;
			}
			
			break;
		}
		case Temp55:			//����״̬
		{
			
			SetLed(1);	//��2��led����

			if(Cnt.TimeTo3s < 30 && Cnt.TimeTo3s > 3)
			{
				if(count> 4)
				{
					count=0;
					if(DisplayNow == 0)
					{
						SetData1(DisplayNum1);
					}else{
						DisplayNum[0] = 12;
						DisplayNum[1] = 12;
						SetSpecialData1(1);
					}
				}
			}else if(DisplayNow == 0){
				SetData1(DisplayNum1);
			}
			
			
			
			if(KeyValueScan == On_Off)
			{
				BeepSet(80, 1);
				State = PowerOn;
				count = 0;
			}else if(KeyValueScan == Function)
			{
				BeepSet(80, 1);
				State = Temp60;
				DisplayNum1 = 60;
				SetData1(DisplayNum1);
				Num1Valid = 0;		//�趨ֵ��˸3s����Ч
				Cnt.TimeTo3s = 0;
				count = 0;
			}else if(KeyValueScan == Boil)
			{
				BeepSet(80, 1);
				State = Temp100;
				SetData1(100);
				Num1Valid = 0;		//�趨ֵ��˸3s����Ч
				Cnt.TimeTo3s = 30;
				Pre_State = Temp55;
				count = 0;
			}else if(KeyValueScan == Add)
			{
				BeepSet(80, 1);
				AddProcess();
				Num1Valid = 0;		//�趨ֵ��˸3s����Ч
				Cnt.TimeTo3s = 0;
				count = 0;
			}else if(KeyValueScan == Sub)
			{
				BeepSet(80, 1);
				SubProcess();
				Num1Valid = 0;		//�趨ֵ��˸3s����Ч
				Cnt.TimeTo3s = 0;
				count = 0;
			}
			
			break;
		}
    case Temp60:			//�¶�ѡ��״̬
		{
			SetLed(2);	//��3��led����

			if(Cnt.TimeTo3s < 30 && Cnt.TimeTo3s > 3)
			{
				if(count> 4)
				{
					count=0;
					if(DisplayNow == 0)
					{
						SetData1(DisplayNum1);
					}else{
						DisplayNum[0] = 12;
						DisplayNum[1] = 12;
						SetSpecialData1(1);
					}
				}
			}else if(DisplayNow == 0){
				SetData1(DisplayNum1);
				//��������
			}
			
			
			
			if(KeyValueScan == On_Off)
			{
				BeepSet(80, 1);
				State = PowerOn;
				count = 0;
			}else if(KeyValueScan == Function)
			{
				BeepSet(80, 1);
				State = Temp85;
				DisplayNum1 = 85;
				SetData1(DisplayNum1);
				Num1Valid = 0;		//�趨ֵ��˸3s����Ч
				Cnt.TimeTo3s = 0;
				count = 0;
			}else if(KeyValueScan == Boil)
			{
				BeepSet(80, 1);
				State = Temp100;
				SetData1(100);
				Pre_State = Temp60;
				Num1Valid = 0;		//�趨ֵ��˸3s����Ч
				Cnt.TimeTo3s = 30;
				count = 0;
			}else if(KeyValueScan == Add)
			{
				BeepSet(80, 1);
				AddProcess();
				Num1Valid = 0;		//�趨ֵ��˸3s����Ч
				Cnt.TimeTo3s = 0;
				count = 0;
			}else if(KeyValueScan == Sub)
			{
				BeepSet(80, 1);
				SubProcess();
				Num1Valid = 0;		//�趨ֵ��˸3s����Ч
				Cnt.TimeTo3s = 0;
				count = 0;
			}
			break;
		}
    case Temp85:			//���ڼ���״̬
		{
			SetLed(3);	//��4��led����

			if(Cnt.TimeTo3s < 30 && Cnt.TimeTo3s > 3)
			{
				if(count> 4)
				{
					count=0;
					if(DisplayNow == 0)
					{
						SetData1(DisplayNum1);
					}else{
						DisplayNum[0] = 12;
						DisplayNum[1] = 12;
						SetSpecialData1(1);
					}
				}
			}else if(DisplayNow == 0){
				SetData1(DisplayNum1);
				//��������
			}
			
			
			
			if(KeyValueScan == On_Off)
			{
				BeepSet(80, 1);
				State = PowerOn;
				count = 0;
			}else if(KeyValueScan == Function)
			{
				BeepSet(80, 1);
				State = Temp90;
				DisplayNum1 = 90;
				SetData1(DisplayNum1);
				Num1Valid = 0;		//�趨ֵ��˸3s����Ч
				Cnt.TimeTo3s = 0;
				count = 0;
			}else if(KeyValueScan == Boil)
			{
				BeepSet(80, 1);
				State = Temp100;
				SetData1(100);
				Pre_State = Temp85;
				Num1Valid = 0;		//�趨ֵ��˸3s����Ч
				Cnt.TimeTo3s = 30;
				count = 0;
			}else if(KeyValueScan == Add)
			{
				BeepSet(80, 1);
				AddProcess();
				Num1Valid = 0;		//�趨ֵ��˸3s����Ч
				Cnt.TimeTo3s = 0;
				count = 0;
			}else if(KeyValueScan == Sub)
			{
				BeepSet(80, 1);
				SubProcess();
				Num1Valid = 0;		//�趨ֵ��˸3s����Ч
				Cnt.TimeTo3s = 0;
				count = 0;
			}
			break;
		}
    case Temp90: 			
		{
			SetLed(4);	//��5��led����

			if(Cnt.TimeTo3s < 30 && Cnt.TimeTo3s > 3)
			{
				if(count> 4)
				{
					count=0;
					if(DisplayNow == 0)
					{
						SetData1(DisplayNum1);
					}else{
						DisplayNum[0] = 12;
						DisplayNum[1] = 12;
						SetSpecialData1(1);
					}
				}
			}else if(DisplayNow == 0){
				SetData1(DisplayNum1);
				//��������
			}
			
			
			
			if(KeyValueScan == On_Off)
			{
				BeepSet(80, 1);
				State = PowerOn;
				count = 0;
			}else if(KeyValueScan == Function)
			{
				BeepSet(80, 1);
				State = Temp100;
				Pre_State = Temp45;
				SetData1(100);
				DisplayNum1 = 45; //�����ʾΪ100�棬�趨ֵ��Сδ�趨ʱΪ45��,100���տ�����ת45��
				Num1Valid = 0;		//�趨ֵ��˸3s����Ч
				Cnt.TimeTo3s = 0;
				count = 0;
			}else if(KeyValueScan == Boil)
			{
				BeepSet(80, 1);
				State = Temp100;
				SetData1(100);
				Pre_State = Temp90;
				DisplayNum1 = 90;
				Num1Valid = 0;		//�趨ֵ��˸3s����Ч
				Cnt.TimeTo3s = 30;
				count = 0;
			}else if(KeyValueScan == Add)
			{
				BeepSet(80, 1);
				AddProcess();
				Num1Valid = 0;		//�趨ֵ��˸3s����Ч
				Cnt.TimeTo3s = 0;
				count = 0;
			}else if(KeyValueScan == Sub)
			{
				BeepSet(80, 1);
				SubProcess();
				Num1Valid = 0;		//�趨ֵ��˸3s����Ч
				Cnt.TimeTo3s = 0;
				count = 0;
			}
			break;
		}
    case Temp100:
		{
			SetLed(5);	//��6��led����

			if(Cnt.TimeTo3s < 30 && Cnt.TimeTo3s > 3)
			{
				if(count> 4)
				{
					count=0;
					if(DisplayNow == 0)
					{
						SetData1(100); //������֮ǰ״̬���趨ֵ����ʾΪ100���϶�
					}else{
						DisplayNum[0] = 12;
						DisplayNum[1] = 12;
						SetSpecialData1(1);
					}
				}
			}else if(DisplayNow == 0){
				SetData1(100);
				//��������
			}
			
			
			
			if(KeyValueScan == On_Off)
			{
				BeepSet(80, 1);
				State = PowerOn;
				count = 0;
			}else if(KeyValueScan == Function)
			{
				BeepSet(80, 1);
				State = Temp45;
				Pre_State = Temp45;
				DisplayNum1 = 45;
				SetData1(DisplayNum1);
				Num1Valid = 0;		//�趨ֵ��˸3s����Ч
				Cnt.TimeTo3s = 0;
				count = 0;
			}else if(KeyValueScan == Boil)
			{
				BeepSet(80, 1);
				State = Temp100;
				SetData1(100);
				Num1Valid = 0;		//�趨ֵ��˸3s����Ч
				Cnt.TimeTo3s = 30;
				count = 0;
			}else if(KeyValueScan == Add)
			{
				BeepSet(80, 1);
				AddProcess();
				Num1Valid = 0;		//�趨ֵ��˸3s����Ч
				Cnt.TimeTo3s = 0;
				count = 0;
			}else if(KeyValueScan == Sub)
			{
				BeepSet(80, 1);
				SubProcess();
				Num1Valid = 0;		//�趨ֵ��˸3s����Ч
				Cnt.TimeTo3s = 0;
				count = 0;
			}
			break;
		}
	
		case SelfTest:
		{			
			//�������ʾ12 34
			SetData1(12);
			SetData2(34);
			
			if(KeyValueScan == On_Off)
			{
				State = PowerOn;
				count = 0;
			}else if(KeyValueScan == Function)
			{
				SetData1(55);
				SetData2(55);
			}else if(KeyValueScan == Boil)
			{
				SetData1(66);
				SetData2(66);
			}else if(KeyValueScan == Add)
			{
				SetData1(77);
				SetData2(77);
			}
			break;
		}
		
	}
	
	
}

/**********************************************************
�������ƣ� AddProcess(void)
�������ܣ� �趨�¶���������
���������
���������
***********************************************************/
void AddProcess(void)
{
	if(DisplayNum1 < 95)
	{
		DisplayNum1++;
	}
	Num1Valid = 0;
	Cnt.TimeTo3s = 0;
	SetData1(DisplayNum1);
}

/**********************************************************
�������ƣ� SubProcess(void)
�������ܣ� �趨�¶ȼ�������
���������
���������
***********************************************************/
void SubProcess(void)
{
	if(DisplayNum1 > 37)
	{
		DisplayNum1--;
	}
	Num1Valid = 0;
	Cnt.TimeTo3s = 0;
	SetData1(DisplayNum1);
}

/**********************************************************
�������ƣ� LongPress(void)
�������ܣ� ���������趨�¶�����
���������
���������
***********************************************************/
void LongPress(void)
{
	static int count = 0; //1s�������ʾ��ֵ
	static int longend_flag = 0; //����������־
	
	if((Err == 0) && (State != PowerOn) && (State != SelfTest))
	{

		if(count== 5) // 500ms��ʱ����һ�ε�
		{
			DisplayNum[0] = 12;
			DisplayNum[1] = 12;
			SetSpecialData1(1);
		}
	
		if( KeyValueScan == Add )
		{
			count++;
			if(count > 10) //1s������趨ֵ
			{
				AddProcess();
				longend_flag = 1;
			}
		}else if(KeyValueScan == Sub){
			count++;
			if(count > 10 ) //1s������趨ֵ
			{
				SubProcess();
				longend_flag = 1;
			}
		}else{
			count = 0;
			if(longend_flag)
			{
				longend_flag = 0;
				Num1Valid = 0;		//�趨ֵ��˸3s����Ч
				Cnt.TimeTo3s = 0;
			}
		}
	}
}

/**********************************************************
�������ƣ� SelfTestProcess(void)
�������ܣ� �Լ����
���������
���������
***********************************************************/
void SelfTestProcess(void)
{
	static int selftest_count = 0; //�Լ�״̬����
	//NTC���� �ϵ�δ���� ��������Լ�״̬
	if((State == PowerOn) && (SelfTest_Valid == 1))
	{
		if(KeyValueScan == Sub)
		{
			selftest_count++;
		}else
		{
			selftest_count = 0;
		}
		
		if(selftest_count > 10)
		{
			State = SelfTest;
			SelfTest_Valid = 0; //�������Լ�״̬�����ٴν���
			SetLed(7);	//led��ȫ��
			
		}
	}
	
}