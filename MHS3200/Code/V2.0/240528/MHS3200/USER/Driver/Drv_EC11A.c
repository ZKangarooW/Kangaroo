#include "Drv_EC11A.h"

/**********�ṹ��************/
_EC11A_ EC11A[2];//��ť����

/**********ȫ�ֱ�������******/
uint8_t Work_Option = 1;//ѡ��λ��
uint8_t SetMode_Option;//ѡ������ģʽ
uint8_t EC11A_Knob;//��������ťʱ
uint8_t Run_Status;//ϵͳ״̬
uint8_t Work_All;//��λ������ͬ

/**********�ֲ���������******/
uint8_t EC11A_Flag,Key1_Flag;//�����ж���ʱ��־
uint8_t Key1_Press,Key2_Press;//���°�ť
uint16_t KEY1_Count,KEY2_Count;//��¼KEY1,KEY2���µ�ʱ��

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_Knob(void)
 * ��    �ܣ������ť״̬-500ms
*****************************************************************
*/
void Check_Knob(void)
{
    if(EC11A_Knob)//��ť��ת��
        EC11A_Knob--;//1S����ʱ
}

/*
*****************************************************************
 * ����ԭ�ͣ�void EC11A_Init(void)
 * ��    �ܣ�EC11A��ʼ����ʱ��
*****************************************************************
*/
void EC11A_Init(void)
{
	/**********EC11A_1**********/
	EC11A[0].EXTI_Pin = KEY1A_Pin;//EC11A��ť�ж�����
	EC11A[0].EC11A_Pin = KEY1B_Pin;//EC11A��ť��������
	EC11A[0].EC11A_GPIO = KEY1B_GPIO_Port;//EC11A��ť����GPIO�˿�
	
	EC11A[0].Key_Pin = KEY1_Pin;//EC11A������������
	EC11A[0].Key_GPIO = KEY1_GPIO_Port;//EC11A��������GPIO�˿�
	
	EC11A[0].EC11A_Fast = EC11A_FastSpeed;//�ж���ת�ٶ���ֵ
	
	/**********EC11A_2**********/
	EC11A[1].EXTI_Pin = KEY2A_Pin;//EC11A��ť�ж�����
	EC11A[1].EC11A_Pin = KEY2B_Pin;//EC11A��ť��������
	EC11A[1].EC11A_GPIO = KEY2B_GPIO_Port;//EC11A��ť����GPIO�˿�
	
	EC11A[1].Key_Pin = KEY2_Pin;//EC11A������������
	EC11A[1].Key_GPIO = KEY2_GPIO_Port;//EC11A��������GPIO�˿�
	
	EC11A[1].EC11A_Fast = EC11A_FastSpeed;//�ж���ת�ٶ���ֵ
}

/*
*****************************************************************
 * ����ԭ�ͣ�void EC11A_Speed(float dT)
 * ��    �ܣ�EC11A��ť�ٶȼ���
*****************************************************************
*/
void EC11A_Speed(float dT)
{
	/**********EC11A_1**********/
	EC11A[0].EC11A_Speed = EC11A[0].EC11A_Cnt*60/20;//һ����һ�Ρ�תһȦ20��������һ���ӵ��ٶ�
	EC11A[0].EC11A_Cnt = 0;//����⵽�ļ�������
	
	/**********EC11A_2**********/
	EC11A[1].EC11A_Speed = EC11A[1].EC11A_Cnt*60/20;//һ����һ�Ρ�תһȦ20��������һ���ӵ��ٶ�
	EC11A[1].EC11A_Cnt = 0;//����⵽�ļ�������
}

/*
*****************************************************************
 * ����ԭ�ͣ�void EC11AKey_Scan(float dT)
 * ��    �ܣ�EC11A����ɨ��
*****************************************************************
*/
void EC11AKey_Scan(float dT)
{
	/**********EC11A_1**********/
	if(HAL_GPIO_ReadPin(EC11A[0].Key_GPIO,EC11A[0].Key_Pin) == KEY_DOWN)//���°���
	{
		if(EC11A[0].LongPress == 0)//û�г�����
		{
			EC11A[0].Key_Cnt += dT;//����ʱ��++
			EC11A[0].Key_Flag = 1;//�������±�־��һ
		}
	}
	if(EC11A[0].Key_Flag == 1)//����������
	{
		if(HAL_GPIO_ReadPin(EC11A[0].Key_GPIO,EC11A[0].Key_Pin) == KEY_UP)//̧�𰴼�
		{   
			if(EC11A[0].Key_Cnt > 0.1 && EC11A[0].Key_Cnt < 1.5)//С��1.5S�ǵ���
			{
				Work_Option++;//����λ++
                #if(Integration_TYPE == 0)//���ó���������ʱ
					if(Param.type == 0 || Param.type == 2)
					{
						if(Work_Option > 2 && Work_Option < 5)//�������λ����2������λΪ5
							Work_Option = 5;//����λΪ7��
						if(Work_Option > 6)//�������λ����8������λΪ1
							Work_Option = 1;//����λΪ1��
					}
					else if(Param.type == 1 || Param.type == 3)
					{
						if(Work_Option > 6)//�������λ����6������λΪ1
							Work_Option = 1;//����λΪ1��
					}
                #elif(Integration_TYPE == 1)//���óɾ���ʱ
                    if(Work_Option > 9)//�������λ����9������λΪ1
                        Work_Option = 1;//����λΪ1��   
                #endif
                Beep_Time = 0.1;//��������0.1S
                SetMode_Option = 0;//ÿ���л���λ������ģʽ��0
                Twinkle_Time = 0;
			}
			EC11A[0].Key_Flag = 0;//�����¼��������ȴ���һ�ΰ���
			EC11A[0].LongPress = 0;//������־����
			EC11A[0].Key_Cnt = 0;//��ť��������
		}
		if(EC11A[0].Key_Cnt > 1.5 && EC11A[0].Key_Cnt < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(EC11A[0].LongPress == 0)//���û��һֱһֱ������
			{
                Work_All = 1;//����ȫ������ģʽ
                SetMode_Option = 0;//�˳�����ģʽ
                Twinkle_Time = 0;
                SetALL_int(0,&Speed_ADDMode);//�ٶ���ʾģʽ����
                /**********ͬ�������ݸ�ֵ*********/
                switch(Work_Option)
                {
                    case 1: 
                            Speed_ALL(1,&Set_Speed,&Set_Speed);//ͬ�������ٶ�
                            Time_ALL(1,&Set_Time,&Set_Time);//ͬ������ʱ��
                            break;
                    case 2: 
                            Speed_ALL(2,&Set_Speed,&Set_Speed);//ͬ�������ٶ�
                            Time_ALL(2,&Set_Time,&Set_Time);//ͬ������ʱ��
                            break;
                    case 3: 
                            
                            Speed_ALL(3,&Set_Speed,&Set_Speed);//ͬ�������ٶ�
                            Time_ALL(3,&Set_Time,&Set_Time);//ͬ������ʱ��
                            break;
                    case 4: 
                            Speed_ALL(4,&Set_Speed,&Set_Speed);//ͬ�������ٶ�
                            
                            Time_ALL(4,&Set_Time,&Set_Time);//ͬ������ʱ��
                            
                            break;
                    case 5: 
                            Speed_ALL(5,&Set_Speed,&Set_Speed);//ͬ�������ٶ�
                           
                            Time_ALL(5,&Set_Time,&Set_Time);//ͬ������ʱ��
                            
                            break;
                    case 6: 
                            Speed_ALL(6,&Set_Speed,&Set_Speed);//ͬ�������ٶ�
                            Time_ALL(6,&Set_Time,&Set_Time);//ͬ������ʱ��
                           
                            break;
                    case 7: 
                            Speed_ALL(7,&Set_Speed,&Set_Speed);//ͬ�������ٶ�
                           
                            Time_ALL(7,&Set_Time,&Set_Time);//ͬ������ʱ��
                            
                            break;
                    case 8: 
                            Speed_ALL(8,&Set_Speed,&Set_Speed);//ͬ�������ٶ�
                           
                            Time_ALL(8,&Set_Time,&Set_Time);//ͬ������ʱ��
                            
                            break;
                    case 9: 
                            Speed_ALL(9,&Set_Speed,&Set_Speed);//ͬ�������ٶ�
                           
                            Time_ALL(9,&Set_Time,&Set_Time);//ͬ������ʱ��
                            
                            break;
                }
                SetOK_Flag = 1;
                Beep_Time = 0.1;//��������0.1S
				EC11A[0].LongPress = 1;//������־��һ
			}
		}
	}
	
	/**********EC11A_2**********/
	if(HAL_GPIO_ReadPin(EC11A[1].Key_GPIO,EC11A[1].Key_Pin) == KEY_DOWN)//���°���
	{
		if(EC11A[1].LongPress == 0)//û�г�����
		{
			EC11A[1].Key_Cnt += dT;//����ʱ��++
			EC11A[1].Key_Flag = 1;//�������±�־��һ
		}
	}
	if(EC11A[1].Key_Flag == 1)//����������
	{
		if(HAL_GPIO_ReadPin(EC11A[1].Key_GPIO,EC11A[1].Key_Pin) == KEY_UP)//̧�𰴼�
		{   
			if(EC11A[1].Key_Cnt > 0.1 && EC11A[1].Key_Cnt < 1.5)//С��1.5S�ǵ���
			{
                SetMode_Option++;//����ģʽ�л�
				#if(Integration_TYPE == 0)//���ó���������ʱ
                if(Param.type <= 1)//���ó���ͨ��
				{
                    if(SetMode_Option == 1)
                        SetMode_Option = 2;//ֱ�������¶�
                    if(SetMode_Option == 3)//����ģʽֻ��2�֣�����4ʱ
                    {
                        SetMode_Option = 0;//����
                        Twinkle_Time = 0;//��˸��ʾ6S
                    }
				}
                else if(Param.type >= 1)//���óɼ��ȿ�ʱ
				{
                    if(SetMode_Option == 3)//����ģʽֻ��3�֣�����4ʱ
                    {
                        SetMode_Option = 0;//����
                        Twinkle_Time = 0;//��˸��ʾ6S
                    }
				}
				#elif(Integration_TYPE == 1)//���óɾ���ʱ
					if(SetMode_Option == 1)
                        SetMode_Option = 2;//ֱ�������¶�
                    if(SetMode_Option == 3)//����ģʽֻ��2�֣�����4ʱ
                    {
                        SetMode_Option = 0;//����
                        Twinkle_Time = 0;//��˸��ʾ6S
                    }
				#endif
                Beep_Time = 0.1;//��������0.1S
                if(SetMode_Option != 0)
                {
                    Twinkle_Time = 6000;//��˸��ʾ6S
                }
			}
			EC11A[1].Key_Flag = 0;//�����¼��������ȴ���һ�ΰ���
			EC11A[1].LongPress = 0;//������־����
			EC11A[1].Key_Cnt = 0;//��ť��������
		}
		if(EC11A[1].Key_Cnt > 1.5 && EC11A[1].Key_Cnt < 3)//����ʱ�����1.5SС��3S��ʾ����
		{
			if(EC11A[1].LongPress == 0)//���û��һֱһֱ������
			{
                if(Run_Status == 1)
                {
                    Run_Status = 0;//�ر�ϵͳ
                }
                else
                {
                    Run_Status = 1;//��ϵͳ
                    Speed_Val_L1.SumError=0x12000;//�������ϵ��
                    Speed_Val_L2.SumError=0x12000;//�������ϵ��
                    Speed_Val_L3.SumError=0x12000;//�������ϵ��
                    Speed_Val_L4.SumError=0x12000;//�������ϵ��
                    Speed_Val_L5.SumError=0x12000;//�������ϵ��
                    Speed_Val_L6.SumError=0x12000;//�������ϵ��
                    Speed_Val_L7.SumError=0x12000;//�������ϵ��
                    Speed_Val_L8.SumError=0x12000;//�������ϵ��
                    Speed_Val_L9.SumError=0x12000;//�������ϵ��
                    ADD_Wait_Count = 0;
                    SetMode_Option = 0;//�˳�����ģʽ
                }
                Beep_Time = 0.1;//��������0.1S
				EC11A[1].LongPress = 1;//������־��һ
			}
		}
	}
}


/*
*****************************************************************
 * ����ԭ�ͣ�void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
 * ��    �ܣ��ⲿ�ж�
*****************************************************************
*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	UNUSED(GPIO_Pin);
	
	/**********EC11A_1**********/
	if(GPIO_Pin == EC11A[0].EXTI_Pin)//A�����ش����ⲿ�ж�
	{
		EC11A[0].FlagTim = 1;//��ʼ��ʱ
		while(EC11A[0].TIM_Cnt <= 2)//��ʱ��һ������1ms����ʱ2ms�ڿ���A��û�е�����
		{
			if(GPIO_Pin == EC11A[0].EXTI_Pin)//��2ms�ڣ���⵽��ƽ�仯
			{ 
				EC11A[0].FlagTim = 0;//ֹͣ��ʱ
				EC11A[0].TIM_Cnt = 0;//���TIM����
				EC11A[0].EC11A_Cnt++;//��ť����
                Beep_Time = 0.1;//��������0.1S
                SetMode_Option = 0;//ÿ���л���λ������ģʽ��0
                Twinkle_Time = 0;
				EC11A[0].EC11A_Knob = 2;//����ת��ťʱ
				if(HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO,EC11A[0].EC11A_Pin) == 0)//��
				{
					Work_Option++;//����λ++
                    #if(Integration_TYPE == 0)//���ó���������ʱ
						if(Param.type == 0 || Param.type == 2)
						{
							if(Work_Option > 2 && Work_Option < 5)//�������λ����2������λΪ5
								Work_Option = 5;//����λΪ7��
							if(Work_Option > 6)//�������λ����8������λΪ1
								Work_Option = 1;//����λΪ1��
						}
						else if(Param.type == 1 || Param.type == 3)
						{
							if(Work_Option > 6)//�������λ����6������λΪ1
								Work_Option = 1;//����λΪ1��
						}
                    #elif(Integration_TYPE == 1) //���óɾ���ʱ
                        if(Work_Option > 9)//�������λ����9������λΪ1
                            Work_Option = 1;//����λΪ1��   
                    #endif
					break;
				}
				else if(HAL_GPIO_ReadPin(EC11A[0].EC11A_GPIO,EC11A[0].EC11A_Pin) == 1)//��
				{
					Work_Option--;//����λ��1
                    #if(Integration_TYPE == 0)//���ó���������ʱ 
						if(Param.type == 0 || Param.type == 2)//����
						{
							if(Work_Option > 2 && Work_Option < 5)//�������λС��5������λΪ2
								Work_Option = 2;//����λΪ2��
							if(Work_Option < 1)//�������λС��1������λΪ6
								Work_Option = 6;//����λΪ6��    
						}
						else if(Param.type == 1 || Param.type == 3)//����
						{
							if(Work_Option < 1)//�������λС��1������λΪ6
								Work_Option = 6;//����λΪ6��
						}					
                    #elif(Integration_TYPE == 1)//���óɾ���ʱ
                        if(Work_Option < 1)//�������λС��1������λΪ9
                            Work_Option = 9;//����λΪ9��   
                    #endif
					break;
				}
				break;
			}
		}
		EC11A[0].FlagTim = 0;//ֹͣ��ʱ
		EC11A[0].TIM_Cnt = 0;//���TIM����
	}
	
	/**********EC11A_2**********/
	if(GPIO_Pin == EC11A[1].EXTI_Pin)//A�����ش����ⲿ�ж�
	{
		EC11A[1].FlagTim = 1;//��ʼ��ʱ
		while(EC11A[1].TIM_Cnt <= 2)//��ʱ��һ������1ms����ʱ2ms�ڿ���A��û�е�����
		{
			if(GPIO_Pin == EC11A[1].EXTI_Pin)//��2ms�ڣ���⵽��ƽ�仯
			{ 
				EC11A[1].FlagTim = 0;//ֹͣ��ʱ
				EC11A[1].TIM_Cnt = 0;//���TIM����
				EC11A[1].EC11A_Cnt++;//��ť����
				EC11A[1].EC11A_Knob = 2;//����ת��ťʱ
				if(HAL_GPIO_ReadPin(EC11A[1].EC11A_GPIO,EC11A[1].EC11A_Pin) == 0)//��
				{
                    /*��*/
                    Set_Val(0,Work_Option,SetMode_Option);//������ֵ
					break;
				}
				else if(HAL_GPIO_ReadPin(EC11A[1].EC11A_GPIO,EC11A[1].EC11A_Pin) == 1)//��
				{
                    /*��*/
                    Set_Val(1,Work_Option,SetMode_Option);//������ֵ
					break;
				}
				break;
			}
		}
		EC11A[1].FlagTim = 0;//ֹͣ��ʱ
		EC11A[1].TIM_Cnt = 0;//���TIM����
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ�void TimCnt_Check(float dT)
 * ��    �ܣ���ʱ���������
*****************************************************************
*/
void TimCnt_Check(float dT)
{
    if(EC11A[0].FlagTim)
        EC11A[0].TIM_Cnt++;
    if(EC11A[1].FlagTim)
        EC11A[1].TIM_Cnt++;
    
}
