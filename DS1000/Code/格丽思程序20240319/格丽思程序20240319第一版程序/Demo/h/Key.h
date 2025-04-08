#ifndef _KEY_H_
#define _KEY_H_

#define U8_MAX 0xFF
#define U16_MAX 0xFFFF

#define On 0
#define Off 1


typedef enum
{
		Free = 0,				//δ����
		On_Off,					//����
		Function,				//����
		Boil,		//����/ȡ������������
		Add,						//+
		Sub,						//-
}KeyValue_t;

extern KeyValue_t KeyValueScan;



typedef enum
{
	PowerOn,								//����״̬
	Temp45,									//45��״̬
	Temp55,									//����״̬
	Temp60,									//�¶�ѡ��״̬
	Temp85,									//���ڼ���״̬
	Temp90, 								//���ڳ��ȼ���״̬
	Temp100,								//���¼���״̬
	SelfTest,								//�Լ�״̬
}SystemState_t;

extern SystemState_t State;
extern SystemState_t Pre_State; //���ǰ��״̬
extern unsigned char xdata KeyProcessFlag;	//����������λ

void Kscan(void);
void KeyProcess(void);
void AddProcess(void);
void SubProcess(void);
void LongPress(void);
void SelfTestProcess(void);

#endif