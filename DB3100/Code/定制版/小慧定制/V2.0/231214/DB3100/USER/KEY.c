#include "KEY.h"

/**********ȫ�ֱ���**********/
uint16_t run_mode = 0;//����ģʽ
uint8_t Key_Status;//�ڲ�������ʱ
/**********�ֲ�����**********/
uint16_t cur=300;//�������ӿ�Ӽ��ٶ�
uint16_t Scan_Status=0;//���ټӼ���־
uint8_t KEY1_Pin_ON=0;//������־
uint8_t Key_Flag;//�������±�־
uint8_t LongPress;//����������־
float Key_Cnt;//����ʱ��

/*
*****************************************************************
 * ����ԭ�ͣ� static uint8_t Key_Scan(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
 * ��    �ܣ� ����ɨ��
 * ��    ��:  *GPIOx��gipo�ܽ� GPIO_Pin������
 * ��    ���� KEY_ON/KEY_OFF
 * ��    ���� GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin
 * ��    �ã� �ڲ�����
*****************************************************************
*/
static uint8_t Key_Scan(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    if(HAL_GPIO_ReadPin (GPIOx, GPIO_Pin) == 1 )//��������
    {
        uint32_t cur_time = HAL_GetTick();//�൱����ʱ8ms
        static uint32_t start_time = 0;
        if(cur_time - start_time < cur)
            return KEY_OFF;
        if(HAL_GPIO_ReadPin (GPIOx, GPIO_Pin) == 1)
        {
            Scan_Status++;
            if(Scan_Status > 3)//һֱ���ŵ�ʱ��
                cur = 2;
            start_time = cur_time;
            return KEY_ON;
        }
    }
    else//�ɿ�������
    {
        if((HAL_GPIO_ReadPin (GPIOB, KEY2_Pin) == 0) && (HAL_GPIO_ReadPin (GPIOB, KEY3_Pin) == 0 ) && (HAL_GPIO_ReadPin (GPIOB, KEY1_Pin) == 0 ) )
        {
            if(HAL_GPIO_ReadPin (GPIOB, KEY5_Pin) == 0)
            {
                KEY1_Pin_ON = 0;//��������
            }
            Scan_Status = 0;
            cur = 300;
            return KEY_OFF;
        }
    }
    return KEY_OFF;
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Key_Handle(float dT)
 * ��    �ܣ� ��������
*****************************************************************
*/
void Key_Handle(float dT)
{
///******************************��***************************************/
//    if((Key_Scan(GPIOB,KEY3_Pin) == KEY_ON))//��
//    {
//        if(Run_Status > 0) //�����в�������
//            return;
//        if(Select_Option == 2)//�������¶�ѡ��
//        {
//            set_temp--;//�¶�--��
//            if(set_temp < 0)//����趨�¶�С��0ʱ��������ֻ���Զ����£�
//            {
//                set_temp = 0;//���趨�¶ȱ�����0
//            }
//        }
//        if(Select_Option == 3)//������ʱ��ѡ��
//        {
//            if(time_status == 0)//���뵥λģʽ��
//            {
//                if(set_time)
//                    set_time -= 5;//ʱ���5s
//                if(set_time < 5)//С��5s���趨ֵʱ
//                {
//					set_time = 0;
//                    time_Last = 1;//��������ʱ
//                    SetTime_State = 1;//�趨ʱ����ʾ��----��
//                }  				
//            }
//            else//�ڷ�Ϊ��λ��ģʽ��
//                set_time -= 60;//ʱ���1����
//        }
//        if(Select_Option == 1)//������ģʽѡ��
//        {
//            run_mode--;//P����λ��--
//            if(run_mode < 1)//С��1ʱ���ص��ھŸ�λ��
//            {
//                run_mode = 1;
//            }
//			Flash_Read((uint8_t *)(&Param),sizeof(Param));
//			set_time=Param.P_Param[run_mode][1];//���������趨ʱ��Ϊ20min
//			set_temp=Param.P_Param[run_mode][0];//���������趨�¶�37��
//			if(set_time > 0 )
//			{
//				SetTime_State = 0;//�趨ʱ���˳���ʾ��----��
//				time_Last = 0;
//			}
//			else
//			{
//				SetTime_State = 1;//�趨ʱ����ʾ��----��
//				time_Last = 1;
//			}
//			SetOK_Flag = 1;
//        }
//        Twinkle_On = 6000;//��˸����ʱ�����ֹͣ�������ã�6S��ֹͣ��˸
//        Key_Status = 1;//��������ʱ����˸��2s����˸
//    }
// 
///******************************��***************************************/    
//    if((Key_Scan(GPIOB,KEY2_Pin) == KEY_ON))//��
//    {
//        if(Run_Status > 0) //�����в�������
//            return;
//        if(Select_Option == 2)//�������¶�ѡ��
//        {
//            set_temp++;//�¶�++��
//            if(set_temp > 1000)//����趨�¶���100��
//                set_temp = 1000;
//        }
//        if(Select_Option == 3)//������ʱ��ѡ��
//        {
//            if(time_status == 0)//���뵥λģʽ��
//            {
//                set_time += 5;//ʱ���5s
//                time_Last = 0;//���뵹��ʱ
//                SetTime_State = 0;//�趨ʱ���˳���ʾ��----��
//            }
//            else//�ڷֵ�λģʽ��
//                set_time += 60;//ʱ���60s
//            if(set_time > 86399)//��߿ɶ�ʱ23.59Сʱ
//                set_time = 86399;
//        }
//        if(Select_Option == 1)//������ģʽѡ��
//        {
//            run_mode++;//P����λ��++
//            if(run_mode > 9)//����9ʱ���ص���һ��λ��
//            {
//                run_mode = 9;
//            }
//			Flash_Read((uint8_t *)(&Param),sizeof(Param));
//			set_time=Param.P_Param[run_mode][1];//���������趨ʱ��Ϊ20min
//			set_temp=Param.P_Param[run_mode][0];//���������趨�¶�37��
//			if(set_time > 0 )
//			{
//				SetTime_State = 0;//�趨ʱ���˳���ʾ��----��
//				time_Last = 0;
//			}
//			else
//			{
//				SetTime_State = 1;//�趨ʱ����ʾ��----��
//				time_Last = 1;
//			}
//			SetOK_Flag = 1;
//        }
//        Twinkle_On = 6000;//��˸����ʱ�����ֹͣ�������ã�6S��ֹͣ��˸
//        Key_Status = 1;//��������ʱ����˸��2s����˸
//    }
//    
///*****************************�˵���*************************************/ 
//    if((Key_Scan(GPIOB,KEY1_Pin) == KEY_ON))//�˵���
//    {    
//        if(Run_Status > 0) //�����в�������
//            return;
//        Select_Option++;//����ѡ���л�
//		if(Set_Mode_Enable == 0)
//		{
//			if(Select_Option == 1)//������pģʽ��һ��ֱ�ӽ����¶��趨
//			{
//				Select_Option = 2;
//			}
//			if(Select_Option > 3)//���¶Ⱥ�ʱ������ѡ��
//			{
//				Select_Option = 0;//����������    			
//			}
//		}
//		else
//		{
//			if(Select_Option > 3)//���¶Ⱥ�ʱ���Pģʽ����ѡ��
//			{
//				Select_Option = 0;//����������    	
//			}
//		}
//        Twinkle_On = 6000;//��˸����ʱ�����ֹͣ�������ã�6S��ֹͣ��˸
//        Beep_Time = 0.1;//��������0.1S
//    }
//      
///*******************************P��*************************************/  
//if(HAL_GPIO_ReadPin(GPIOB,KEY5_Pin )== 1)//P��
//    {
//        if(Run_Status > 0) //�����в�������
//            return; 
//		if(LongPress == 0)//û�г�����
//		{
//			Key_Cnt += dT;//����ʱ��++
//			Key_Flag = 1;//�������±�־��һ
//		}
//	}
//	if(Key_Flag == 1)//����������
//	{
//        if(HAL_GPIO_ReadPin(GPIOB,KEY5_Pin )== 0)//P��
//        {
//			if(Key_Cnt < 1.5)//С��1.5S�ǵ���
//			{
//				if(Set_Mode_Enable == 0)
//				{
//					Set_Mode_Enable = 1;//��ʾpģʽ�Ŀ�
//					Select_Option = 1;//�����趨p��λ��
//					run_mode = 1;
//					Flash_Read((uint8_t *)(&Param),sizeof(Param));
//					set_time=Param.P_Param[run_mode][1];//���������趨ʱ��Ϊ20min
//					set_temp=Param.P_Param[run_mode][0];//���������趨�¶�37��
//					if(set_time > 0 )
//					{
//						SetTime_State = 0;//�趨ʱ���˳���ʾ��----��
//						time_Last = 0;
//					}
//					else
//					{
//						SetTime_State = 1;//�趨ʱ����ʾ��----��
//						time_Last = 1;
//					}
//					SetOK_Flag = 1;	
//					Twinkle_On = 6000;//��˸����ʱ�����ֹͣ�������ã�6S��ֹͣ��˸
//					Beep_Time = 0.1;//��������0.1S
//				}
//				else
//				{
//					Set_Mode_Enable = 0;//����ʾPģʽ
//					run_mode_flag = 0;//����ʾPģʽ��
//					set_time=1200;//�˳�Pģʽ�����趨ʱ��Ϊ20min
//					rel_time=1200;//�˳�Pģʽ����ʵ��ʱ��Ϊ20min
//					set_temp=370;//�˳�Pģʽ�����趨�¶�37��
//					Select_Option = 0;//����˸����
//					run_mode = 0;
//					Flash_Read((uint8_t *)(&Param),sizeof(Param));
//					set_time=Param.P_Param[run_mode][1];//���������趨ʱ��Ϊ20min
//					set_temp=Param.P_Param[run_mode][0];//���������趨�¶�37��
//					SetOK_Flag = 1;
//					Beep_Time = 0.1;//��������0.1S
//				}
//			}
//			Key_Flag = 0;//�����¼��������ȴ���һ�ΰ���
//			LongPress = 0;//������־����
//			Key_Cnt = 0;//��ť��������
//		}
//		if(Key_Cnt > 1.5 && Key_Cnt < 3)//����ʱ�����1.5SС��3S��ʾ����
//		{
//			if(LongPress == 0)//���û��һֱһֱ������
//			{
//				LongPress = 1;//������־��һ
//			}
//		}
//	}	

    
/******************************��ʼ/ֹͣ********************************/       
    if((Key_Scan(GPIOB,KEY4_Pin) == KEY_ON))//��ʼ/ֹͣ
    {
        if(Run_Status == 0)//ϵͳû����
        {
            Select_Option = 0;//�趨ѡ������
            Run_Status = 1; //ϵͳ����         
            time_disable = 0;//�رյ���ʱ
            ADD_Mode = 0;//����״̬����
			Run_Val = 0;
			SetOK_Flag = 1;	
        }
        else
        {
            Run_Status = 0;//�ر�ϵͳ
            time_disable = 0;//�رյ���ʱ
			Run_Val = 0;
            ADD_Mode = 0;//����״̬����
			set_time=Param.P_Param[0][1];//���������趨ʱ��Ϊ20min
			set_temp=Param.P_Param[0][0];//���������趨�¶�37��
			SetOK_Flag = 1;
        }
        Beep_Time = 0.1;//��������0.1S
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Check_Key(void)
 * ��    �ܣ���ⰴ��״̬-1s
*****************************************************************
*/
void Check_Key(void)
{
    if(Key_Status)
        Key_Status--;
}
