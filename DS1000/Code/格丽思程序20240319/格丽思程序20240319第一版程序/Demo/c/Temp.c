#include "Temp.h"
#include "adc.h"
#include "led.h"
#include "Buzzer.h"
#include "Key.h"
#include "time.h"

unsigned int   xdata U16_AdcValueNew = 0;
unsigned int 	 xdata U16_AdcSum = 0;
unsigned int 	 xdata TempNow = 0;

unsigned char  xdata NTC_Bad_Cnt = 0;
unsigned char  xdata NTC_Good_Cnt = 0;
unsigned char  xdata Err = 1; //�ݶ������־λ


#define  con_tabale_num   100

unsigned int  Ad2Temper();

// 0-100���϶ȶ�ӦADCֵ
const unsigned int code TemADC[] = {
	387 ,403 ,419 ,436 ,
	452 ,470 ,488 ,506 ,525 ,544 ,564 ,585 ,605 ,627 ,
	648 ,671 ,694 ,717 ,741 ,765 ,789 ,815 ,840 ,866 ,
	893 ,920 ,947 ,975 ,1003 ,1031 ,1060 ,1090 ,1119 ,1149 ,
	1180 ,1210 ,1241 ,1273 ,1304 ,1336 ,1368 ,1400 ,1433 ,1465 ,
	1498 ,1531 ,1564 ,1597 ,1630 ,1663 ,1697 ,1730 ,1763 ,1797 ,
	1807 ,1834 ,1861 ,1888 ,1915 ,1942 ,1969 ,1996 ,2023 ,2050 ,
	2077 ,2104 ,2131 ,2158 ,2185 ,2212 ,2228 ,2244 ,2261 ,2277 ,		//90-99
	2293 }; 

/*	,2212 ,2239 ,2266 ,2293 ,2320 ,
	2347   };//100 */


/**********************************************************************************
	�������ƣ�unsigned int Ad2Temper()
	�������ܣ���ǰADC��Ӧ�¶�ֵ
	���������ad ��ǰ�¶ȶ�ӦADֵ
	�������
************************************************************************************/
unsigned int Ad2Temper()
{    
    unsigned int cnt;
		unsigned int Temp;
		Temp = 0;
		cnt = 0;
    for(cnt=0;cnt<=74;cnt++)        
    {
        if(TempNow >= TemADC[cnt] )
				{
					if(TempNow < TemADC[cnt+1])
					{
						Temp = cnt + 26;
						return Temp;
					}
				}
    }
	
		return Temp;
}


/*************************************************************
�������ƣ�void Gettemp(void)
�������ܣ���ȡ��ǰ�¶�ADֵ
���������
���������
**************************************************************/
//1ms����
void Gettemp(void)
{
	static unsigned int U8_AdcCnt = 0;
	/*�¶Ȳ���*/
	ADC_EnableChannel(ADC_CH_15);	
	ADC_Start();
	ADC_GO();
	while(ADC_IS_BUSY);
	U16_AdcValueNew =  ADC_GetADCResult();   
	ADC_Stop();	
	
	
	
	if(U8_AdcCnt < 8)
		{
			U8_AdcCnt ++;
			U16_AdcSum += U16_AdcValueNew;
		}
		else
		{
			TempNow = U16_AdcSum>>3;
			U16_AdcSum = 0;
			U8_AdcCnt = 0;
		}
	
//	U8_Adc_Buf[U8_AdcCnt] = (uchar) (U16_AdcValueNew >> 4); //ȥ����4λ  ֻ��Ҫ��8λ  ��ʡROM
//	U8_AdcCnt ++;
//	if(U8_AdcCnt >= 10)
//	{//�ͻ�Ҫ�����10�Σ�ȡ�м�8��
//		for(U8_AdcCnt = 1; U8_AdcCnt <9; U8_AdcCnt ++)
//		{
//			U16_AdcSum += U8_Adc_Buf[U8_AdcCnt];
//		} 
//		U8_AdcValue = U16_AdcSum >> 3;     // U16_AdcSum / 8
}

/******************************************************************************
�������ƣ�void AD2Temp()
�������ܣ�����ǰADֵת��Ϊ�¶�ֵ
���������
�������
*******************************************************************************/
//100ms����
void AD2Temp(void)
{
	//NTC_ADC���ݴ���
	if((TempNow >= (TemADC[74]+ 500)) || (TempNow <= 100)) //��·ֵΪ0�� 100��ADֵΪTemADC[74]
	{ //��·��·�ж�
		NTC_Bad_Cnt ++;
		NTC_Good_Cnt = 0;
		if(NTC_Bad_Cnt > 1) //����2��Ϊ��·���·
		{
			Err = 1;
			
			if(DisplayNum2 != 0)
			{
				if(State != PowerOn)
				{
					BeepSet(80,1);
					if(TempNow >= (TemADC[74]+ 500)) //���նϵ籣�����Զ��������״̬
					{
						State = PowerOn;
						DisplayNum[0] = 11;
						DisplayNum[1] = 11;
						DisplayNum[2] = 11;
						DisplayNum[3] = 11;
						SetSpecialData1(0);
						SetSpecialData2(0);
						SetLed(6);
						BeepSet(180,2); //��������3������80ms����������3��
					}
				}
				DisplayNum[2] = 11;
				DisplayNum[3] = 11;
				SetSpecialData2(0);
				DisplayNum2 = 0; //��ǰ�¶����
				
			}
		}
	}else{
		NTC_Bad_Cnt = 0;
		NTC_Good_Cnt++;
		
		//��С��26���϶ȣ�ǿ��Ϊ26
		if(TempNow <= TemADC[0] )
		{
			DisplayNum2 = 26;
		}else if(TempNow >= TemADC[74])
		{//������100���϶ȣ�ǿ��Ϊ100
			DisplayNum2 = 100;
		}else{
			DisplayNum2 = Ad2Temper();
		}
		
		if(Err == 1)
		{
			if(State != PowerOn)
			{
				BeepSet(80,1);
				Cnt.TimeTo3s = 0;
				if(State != SelfTest)
				{
					SetData2(DisplayNum2); //����ˮ��ʱ��ʵʱ���µ�ǰ�¶�
				}
			}
		}
		Err = 0;
		
		if(led1sValid == 0)
		{
			if((State != PowerOn)&&(State != SelfTest))
			{
				SetData2(DisplayNum2); //����ˮ��ʱ��ʵʱ���µ�ǰ�¶�
				led1sValid = 1;
			}
		}
		
	}
	
}