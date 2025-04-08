
#include "Heater.h"
#include "Gpio.h"
#include "Key.h"
#include "Temp.h"
#include "led.h"
#include "Buzzer.h"

#include <CMS\FY80F49x.H>
Heater_t Heater;


void Heater_Config(void)
{
	
//		/*�ɿع����*/
//		GPIO_SET_MUX_MODE(P15CFG, GPIO_MUX_GPIO);
		GPIO_ENABLE_OUTPUT(P1TRIS, GPIO_PIN_5);
//		P15 = 0;
	
		/*������*/
		GPIO_SET_MUX_MODE(P20CFG, GPIO_MUX_GPIO);
		GPIO_ENABLE_INPUT(P2TRIS, GPIO_PIN_0);
}


void CtrlHeater_SCR(void)
{
	signed int Delta;
	int display1 = 0;	//��ǰ��ʾ�趨�¶�
	display1 = GetData1();
	
	if(1 == Heater.UseSCR)
	{
	
		Delta = display1 - DisplayNum2; //�趨�¶ȼ�ȥ��ǰ�¶� 

		Heater.SCRCnt =(Heater.SCRCnt < U8_MAX)?Heater.SCRCnt+1:0;	
		Heater.SCRFullTimeSet = 100;
		if(Heater.SCRCnt == Heater.SCRFullTimeSet)
		{
			Heater.SCRCnt = 0;
			
			if(Delta > 5)
			{
				Heater.SCROnTimeSet = 100;
			}
			else if(Delta >= 0)
			{
				Heater.SCROnTimeSet = 70;
			}
			else
			{
				Heater.SCROnTimeSet = 0;
			}
		}
		
	#
		if(Heater.SCRCnt < Heater.SCROnTimeSet)
		{
			Heater.SCROn = 1;
		}
		else
		{
			Heater.SCROn = 0;
		}
	}else{
		if(State == SelfTest) 
		{
			//�Լ�״̬�����ɿع賩��
			Heater.SCROn = 1;
		}else
		{
			//��������رռ��ȹܽ�
			Heater.SCROn = 0;
		}
	}
	
	/*SCR����*/
	if(1 == Heater.SCROn)
	{
			Heater_SCR_IO = On ;
	}
}


/*************************************************************************************************
�������ƣ�CtrlHeater()
�������ܣ����Ƽ����Ƿ���
�������
�������
**************************************************************************************************/
void CtrlHeater(void)
{
	static int equState = 0;
	static unsigned int count = 0; //���ֵ65535
	static int s15 = 0;			//��ˮʱ��
	int display2 = 0; //��ǰ��ʾ�¶�
	int display1 = 0;	//��ǰ��ʾ�趨�¶�
	//NTC���ϡ���ʼ�ϵ�״̬�²����м���,�Լ�״̬�²������¶ȼ��ļ��ȿ��ؿ���
	if((Err == 1) || (State == PowerOn) || (State == SelfTest) )
	{
		Heater.UseSCR = 0;
		return;
	}
	
	display1 = GetData1();
	if((DisplayNum2 < display1) && (Num1Valid == 1))//��������¶�С���趨�¶ȣ����趨ֵ��Ч������м���
	{
		if(DisplayNum2 <= (DisplayNum1-3)) //ʵ���¶����趨ֵ�¶����3��ʱ���´��¶ȴﵽ�趨ֵ�����������
  	{
			equState = 0; //�¶����״̬���¶����3���϶�����ʱ���з�������ʾ
			count = 0; //��г���ʱ����ˮ���������3�����ϣ���г������¼�ʱ
		}
		
		if((equState == 1) && (display1 == 100))
		{
			count++; //���������״̬�������ۼ�
			if(count > 15000) //�ó���1ms��һ�� 15s
			{
				s15++;
				count = 0;
			}
		}
		
		Heater.UseSCR = 1;
	}else{	//���򲻼���
		display2 = GetData2();
		if((equState == 0 ) && (DisplayNum2 == display1))
		{
			if( display2 == display1 )
			{
				if((State != Temp100) && (Num1Valid == 1))
				{
					BeepSet(200, 2);
				}
				
				equState = 1; //�ﵽ�趨�¶Ⱥ����趨�¶Ȳ���ʱ�����з�������ʾ
			}
		}
		
		if((State == Temp100) && (display2 == display1) && (Num1Valid == 1)) //��Ϊ��ˮ״̬��Ӧ����1���Ӻ��ٹرռ���
		{
			count++;
			if(count > 15000) //�ó���1ms��һ�� 15s
			{
				s15++;
				count = 0;
			}
			
			if(s15 < 5 ) //15s*5 = 1min15s
			{
				Heater.UseSCR = 1; 
				return;
			}
			BeepSet(80, 1);
			State = Pre_State;

			SetData1(DisplayNum1);
			equState = 0;	//״̬���ʱӦ���¶����״̬����
			s15 = 0;
		}
		
		Heater.UseSCR = 0;
	}
	
	
	
	
}
