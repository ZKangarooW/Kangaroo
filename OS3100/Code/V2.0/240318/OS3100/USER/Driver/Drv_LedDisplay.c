#include "Drv_LedDisplay.h"

/**********ȫ�ֱ�������******/
uint16_t Twinkle_Time;//��˸ʱ��
uint8_t IconRun_Time;//��Ȧʱ��

/**********�ֲ���������******/
uint8_t DIG,UC,UC10;//DIG,UC������
uint8_t SPEED_Tab[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6};//��ʾ0-9
uint8_t Icon_Run[] = {0xB4, 0xD8, 0x6C};//ԲȦ������
uint8_t t;//��ʾʱ��
uint8_t Speed_ShowFlag = 0;//�ٶ���˸
uint8_t Time_ShowFlag = 0;//ʱ����˸
uint8_t TimeIcon_ShowFalg = 0;//ʱ��ð����˸
uint8_t Icon_ShowFlag = 0;//������˸

/*
*****************************************************************
 * ����ԭ�ͣ� void Check_ShowFlag(uint16_t dT)
 * ��    �ܣ� ��˸���
 * ��    ��:  dT:ִ������
 * ��    ���� uint16_t dT
*****************************************************************
*/
void Check_ShowFlag(uint16_t dT)
{
    if(sys.Run_Status)//����ʱ
    {
        TimeIcon_ShowFalg = ~TimeIcon_ShowFalg;
        Icon_ShowFlag = ~Icon_ShowFlag;
    }
    if(sys.SetMode_Option == 0)//���û������ѡ���У��򶼵���������˸
    {
        Speed_ShowFlag = 0;//����
        Time_ShowFlag = 0;//����
        Twinkle_Time = 0;//��˸��ʱ����
        return;
    }
    if(Twinkle_Time && EC11A[0].EC11A_Knob==0)//��˸��û�в�����ťʱ
    {
        Twinkle_Time -= dT;//��˸��ʱ
        if(sys.SetMode_Option == 1)//�����ٶ�
        {
            Speed_ShowFlag = ~Speed_ShowFlag;//�ٶ���˸
            Time_ShowFlag = 0;//ʱ�䳣��
        }
        else if(sys.SetMode_Option == 2)//�����¶�
        {
            Speed_ShowFlag = 0;//�ٶȳ���
            Time_ShowFlag = ~Time_ShowFlag;//ʱ����˸
        }  
        if(Twinkle_Time == 0)//�����˸����
        {
            sys.SetMode_Option = 0;//ģʽѡ������
        }        
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ� void UCdata_Display(uint8_t uc)
 * ��    �ܣ� UC�����жϿ������� 
*****************************************************************
*/
void UCdata_Display(uint8_t uc)
{
	 for(uint8_t i=0; i<7; i++)
    {
        if((uc<<i) & 0x80)
        {
            switch(i)
            {           
                case 0: HAL_GPIO_WritePin(UC_A_GPIO_Port, UC_A_Pin, GPIO_PIN_SET);break;
                case 1: HAL_GPIO_WritePin(UC_B_GPIO_Port, UC_B_Pin, GPIO_PIN_SET);break;
                case 2: HAL_GPIO_WritePin(UC_C_GPIO_Port, UC_C_Pin, GPIO_PIN_SET);break;
                case 3: HAL_GPIO_WritePin(UC_D_GPIO_Port, UC_D_Pin, GPIO_PIN_SET);break;
                case 4: HAL_GPIO_WritePin(UC_E_GPIO_Port, UC_E_Pin, GPIO_PIN_SET);break;
                case 5: HAL_GPIO_WritePin(UC_F_GPIO_Port, UC_F_Pin, GPIO_PIN_SET);break;
                case 6: HAL_GPIO_WritePin(UC_G_GPIO_Port, UC_G_Pin, GPIO_PIN_SET);break;
            }      
        }
        else
        {
            switch(i)
            {           
                case 0: HAL_GPIO_WritePin(UC_A_GPIO_Port, UC_A_Pin, GPIO_PIN_RESET);break;
                case 1: HAL_GPIO_WritePin(UC_B_GPIO_Port, UC_B_Pin, GPIO_PIN_RESET);break;
                case 2: HAL_GPIO_WritePin(UC_C_GPIO_Port, UC_C_Pin, GPIO_PIN_RESET);break;
                case 3: HAL_GPIO_WritePin(UC_D_GPIO_Port, UC_D_Pin, GPIO_PIN_RESET);break;
                case 4: HAL_GPIO_WritePin(UC_E_GPIO_Port, UC_E_Pin, GPIO_PIN_RESET);break;
                case 5: HAL_GPIO_WritePin(UC_F_GPIO_Port, UC_F_Pin, GPIO_PIN_RESET);break;
                case 6: HAL_GPIO_WritePin(UC_G_GPIO_Port, UC_G_Pin, GPIO_PIN_RESET);break;
            }
        }
    } 
}

/*
*****************************************************************
 * ����ԭ�ͣ� DIGdata_Display(uint8_t DIG)
 * ��    �ܣ� DIG�����жϿ������� 
*****************************************************************
*/
void DIGdata_Display(uint8_t DIG)
{
	 for(uint8_t i=0; i<8; i++)
    {
        if((DIG<<i) & 0x80)
        {
            switch(i)
            {           
                case 0: HAL_GPIO_WritePin(DIG1_GPIO_Port, DIG1_Pin, GPIO_PIN_RESET);break;
                case 1: HAL_GPIO_WritePin(DIG2_GPIO_Port, DIG2_Pin, GPIO_PIN_RESET);break;
                case 2: HAL_GPIO_WritePin(DIG3_GPIO_Port, DIG3_Pin, GPIO_PIN_RESET);break;
                case 3: HAL_GPIO_WritePin(DIG4_GPIO_Port, DIG4_Pin, GPIO_PIN_RESET);break;
                case 4: HAL_GPIO_WritePin(DIG5_GPIO_Port, DIG5_Pin, GPIO_PIN_RESET);break;
                case 5: HAL_GPIO_WritePin(DIG6_GPIO_Port, DIG6_Pin, GPIO_PIN_RESET);break;
                case 6: HAL_GPIO_WritePin(DIG7_GPIO_Port, DIG7_Pin, GPIO_PIN_RESET);break;
                case 7: HAL_GPIO_WritePin(DIG8_GPIO_Port, DIG8_Pin, GPIO_PIN_RESET);break;
            }      
        }
        else
        {
            switch(i)
            {           
                case 0: HAL_GPIO_WritePin(DIG1_GPIO_Port, DIG1_Pin, GPIO_PIN_SET);break;
                case 1: HAL_GPIO_WritePin(DIG2_GPIO_Port, DIG2_Pin, GPIO_PIN_SET);break;
                case 2: HAL_GPIO_WritePin(DIG3_GPIO_Port, DIG3_Pin, GPIO_PIN_SET);break;
                case 3: HAL_GPIO_WritePin(DIG4_GPIO_Port, DIG4_Pin, GPIO_PIN_SET);break;
                case 4: HAL_GPIO_WritePin(DIG5_GPIO_Port, DIG5_Pin, GPIO_PIN_SET);break;
                case 5: HAL_GPIO_WritePin(DIG6_GPIO_Port, DIG6_Pin, GPIO_PIN_SET);break;
                case 6: HAL_GPIO_WritePin(DIG7_GPIO_Port, DIG7_Pin, GPIO_PIN_SET);break;
                case 7: HAL_GPIO_WritePin(DIG8_GPIO_Port, DIG8_Pin, GPIO_PIN_SET);break;
            }
        }
    } 
}

/*
*****************************************************************
 * ����ԭ�ͣ� void DIGdata_Set(void)
 * ��    �ܣ� 1-8DIG����ȫ������
*****************************************************************
*/
void DIGdata_Set(void)
{
    HAL_GPIO_WritePin(DIG1_GPIO_Port, DIG1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(DIG2_GPIO_Port, DIG2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(DIG3_GPIO_Port, DIG3_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(DIG4_GPIO_Port, DIG4_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(DIG5_GPIO_Port, DIG5_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(DIG6_GPIO_Port, DIG6_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(DIG7_GPIO_Port, DIG7_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(DIG8_GPIO_Port, DIG8_Pin, GPIO_PIN_SET);
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Display_SpeedShow(uint16_t speed)
 * ��    �ܣ� ��ʾ�ٶ�
 * ��    ��:  speed��Ҫ��ʾ���ٶ�
 * ��    ���� uint16_t speed
*****************************************************************
*/
void Display_SpeedShow(uint16_t speed)
{
    uint8_t Val;//���ڰ�ʮ��ȡ����������
    if(t == 1)
    {
        /***********L1ǧλ***********/
        if(speed > 999)//����999ʱ
        {	
			Val=speed/1000;//ȡ��ǧλ������			
            switch(Val)
            {
                case 0:UC = SPEED_Tab[0];//����0
                    break;
                case 1:UC = SPEED_Tab[1];//����1
                    break;
                case 2:UC = SPEED_Tab[2];//����2
                    break;
                case 3:UC = SPEED_Tab[3];//����3
                    break;	
                case 4:UC = SPEED_Tab[4];//����4
                    break;	
                case 5:UC = SPEED_Tab[5];//����5
                    break;
                case 6:UC = SPEED_Tab[6];//����6
                    break;	
                case 7:UC = SPEED_Tab[7];//����7
                    break;	
                case 8:UC = SPEED_Tab[8];//����8
                    break;	
                case 9:UC = SPEED_Tab[9];//����9
                    break;
                default:
                    break;
            }	
            UCdata_Display(UC);
            if(Speed_ShowFlag >= 1 && EC11A[0].EC11A_Knob == 0)//��˸�ٶ�
                DIGdata_Display(0x00);          
            else
                DIGdata_Display(0x80);
        }
        else//С��999ʱ
        {
            DIGdata_Display(0x00);
        }  
    }
    else if(t == 2)
    {
        /***********L1��λ***********/
        if(speed > 99)//����99ʱ
        {
            Val=speed/100;//ȡ����λ������
            if(speed > 999)//�������999ʱ
                Val=Val%10;//ȡ����λ������
            switch(Val)
            {
                case 0:UC = SPEED_Tab[0];//����0
                    break;
                case 1:UC = SPEED_Tab[1];//����1
                    break;
                case 2:UC = SPEED_Tab[2];//����2
                    break;
                case 3:UC = SPEED_Tab[3];//����3
                    break;	
                case 4:UC = SPEED_Tab[4];//����4
                    break;	
                case 5:UC = SPEED_Tab[5];//����5
                    break;
                case 6:UC = SPEED_Tab[6];//����6
                    break;	
                case 7:UC = SPEED_Tab[7];//����7
                    break;	
                case 8:UC = SPEED_Tab[8];//����8
                    break;	
                case 9:UC = SPEED_Tab[9];//����9
                    break;
                default:
                    break;
            }	
            UCdata_Display(UC); 
            if(Speed_ShowFlag >= 1 && EC11A[0].EC11A_Knob == 0)
                DIGdata_Display(0x00);          
            else
                DIGdata_Display(0x40);
        }
        else
        {
            DIGdata_Display(0x00);//����ʾ
        }
        
    }
    else if(t == 3)
    {
        /***********L1ʮλ***********/
        if(speed > 9)//����9ʱ
        {
            Val=speed/10;//ȡ��ʮλ������
            if(speed > 99)//����99ʱ
                Val=Val%10;//ȡ��ʮλ������
            switch(Val)
            {
                case 0:UC = SPEED_Tab[0];//����0
                    break;
                case 1:UC = SPEED_Tab[1];//����1
                    break;
                case 2:UC = SPEED_Tab[2];//����2
                    break;
                case 3:UC = SPEED_Tab[3];//����3
                    break;	
                case 4:UC = SPEED_Tab[4];//����4
                    break;	
                case 5:UC = SPEED_Tab[5];//����5
                    break;
                case 6:UC = SPEED_Tab[6];//����6
                    break;	
                case 7:UC = SPEED_Tab[7];//����7
                    break;	
                case 8:UC = SPEED_Tab[8];//����8
                    break;	
                case 9:UC = SPEED_Tab[9];//����9
                    break;
                default:
                    break;
            }
            UCdata_Display(UC);  
            if(Speed_ShowFlag >= 1 && EC11A[0].EC11A_Knob == 0)
                DIGdata_Display(0x00);          
            else
                DIGdata_Display(0x20);         
        }
        else
        {
            DIGdata_Display(0x00);//����ʾ
        }
    }
    else if(t == 4)
    {
        /***********L1��λ***********/
        UC = SPEED_Tab[0];//����0
        UCdata_Display(UC);
        if(Speed_ShowFlag >= 1 && EC11A[0].EC11A_Knob == 0)
            DIGdata_Display(0x00);          
        else
            DIGdata_Display(0x10);
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Display_TimeShow(int32_t time)
 * ��    �ܣ� ��ʾʱ��
 * ��    ��:  time��Ҫ��ʾ��ʱ��
 * ��    ���� int32_t time
*****************************************************************
*/
void Display_TimeShow(int32_t time)
{
    uint8_t SH,H,SM,M;//���ڰ�ʮ��ȡ����������
    SH=time/3600/10;//����ʮλ��λ��Сʱ��
    H=time/3600%10;//�����λ��λ��Сʱ��
    SM=time%3600/60/10;//����ʮ��λ��λ�ķ�����
    M=time%3600/60%10;//�������λ��λ�ķ�����
    if(t == 5)
    {
        /***********L1ǧλ***********/
        switch(SH)
        {
            case 0:UC = SPEED_Tab[0];//����0
                break;
            case 1:UC = SPEED_Tab[1];//����1
                break;
            case 2:UC = SPEED_Tab[2];//����2
                break;
            case 3:UC = SPEED_Tab[3];//����3
                break;	
            case 4:UC = SPEED_Tab[4];//����4
                break;	
            case 5:UC = SPEED_Tab[5];//����5
                break;
            case 6:UC = SPEED_Tab[6];//����6
                break;	
            case 7:UC = SPEED_Tab[7];//����7
                break;	
            case 8:UC = SPEED_Tab[8];//����8
                break;	
            case 9:UC = SPEED_Tab[9];//����9
                break;
            default:
                break;
        }
        if(Time_State == 1)
            UCdata_Display(0x02);
        else            
            UCdata_Display(UC); 
        if(Time_ShowFlag >= 1 && EC11A[0].EC11A_Knob == 0)//ʱ����˸
            DIGdata_Display(0x00);          
        else        
            DIGdata_Display(0x08);
    }
    else if(t == 6)
    {
        /***********L1��λ***********/
        switch(H)
        {
            case 0:UC = SPEED_Tab[0];//����0
                break;
            case 1:UC = SPEED_Tab[1];//����1
                break;
            case 2:UC = SPEED_Tab[2];//����2
                break;
            case 3:UC = SPEED_Tab[3];//����3
                break;	
            case 4:UC = SPEED_Tab[4];//����4
                break;	
            case 5:UC = SPEED_Tab[5];//����5
                break;
            case 6:UC = SPEED_Tab[6];//����6
                break;	
            case 7:UC = SPEED_Tab[7];//����7
                break;	
            case 8:UC = SPEED_Tab[8];//����8
                break;	
            case 9:UC = SPEED_Tab[9];//����9
                break;
            default:
                break;
        }	
        if(Time_State == 1)
            UCdata_Display(0x02);
        else
            UCdata_Display(UC);  
        if(Time_ShowFlag >= 1 && EC11A[0].EC11A_Knob == 0)
            DIGdata_Display(0x00);          
        else
            DIGdata_Display(0x04);
    }
    else if(t == 7)
    {
        /***********L1ʮλ***********/
        switch(SM)
        {
            case 0:UC = SPEED_Tab[0];//����0
                break;
            case 1:UC = SPEED_Tab[1];//����1
                break;
            case 2:UC = SPEED_Tab[2];//����2
                break;
            case 3:UC = SPEED_Tab[3];//����3
                break;	
            case 4:UC = SPEED_Tab[4];//����4
                break;	
            case 5:UC = SPEED_Tab[5];//����5
                break;
            case 6:UC = SPEED_Tab[6];//����6
                break;	
            case 7:UC = SPEED_Tab[7];//����7
                break;	
            case 8:UC = SPEED_Tab[8];//����8
                break;	
            case 9:UC = SPEED_Tab[9];//����9
                break;
            default:
                break;
        }	
        if(Time_State == 1)
            UCdata_Display(0x02);
        else
            UCdata_Display(UC); 
        if(Time_ShowFlag >= 1 && EC11A[0].EC11A_Knob == 0)
            DIGdata_Display(0x00);          
        else        
            DIGdata_Display(0x02);
    }
    else if(t == 8)
    {
        /***********L1��λ***********/
        switch(M)
        {
            case 0:UC = SPEED_Tab[0];//����0
                break;
            case 1:UC = SPEED_Tab[1];//����1
                break;
            case 2:UC = SPEED_Tab[2];//����2
                break;
            case 3:UC = SPEED_Tab[3];//����3
                break;	
            case 4:UC = SPEED_Tab[4];//����4
                break;	
            case 5:UC = SPEED_Tab[5];//����5
                break;
            case 6:UC = SPEED_Tab[6];//����6
                break;	
            case 7:UC = SPEED_Tab[7];//����7
                break;	
            case 8:UC = SPEED_Tab[8];//����8
                break;	
            case 9:UC = SPEED_Tab[9];//����9
                break;
            default:
                break;
        }	
        if(Time_State == 1)
            UCdata_Display(0x02);
        else
            UCdata_Display(UC);  
        if(Time_ShowFlag >= 1 && EC11A[0].EC11A_Knob == 0)
            DIGdata_Display(0x00);          
        else
            DIGdata_Display(0x01);    
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Display_Icon(void)
 * ��    �ܣ� ��ʾͼ��
*****************************************************************
*/
void Display_Icon(void)
{
    if(t == 9)
    {
        UC = 0x18;//ʱ��ð��ͼ��        
        UCdata_Display(UC);  
        DIGdata_Set();
        if(TimeIcon_ShowFalg >= 1 && sys.Run_Status == 1 && Time_State == 0)//��˸
        {
            DIG9_OFF;
        }
        else
        {
            DIG9_ON;
        }
        DIG10_OFF;
    }
    else if(t == 10)
    {
        static uint8_t cnt;
        IconRun_Time++;
        if(IconRun_Time >= 10)//200ms��Ȧ
        {
            cnt ++;
            if(cnt == 4)
                cnt = 1;
            switch(cnt)
            {
                case 1:UC10 = Icon_Run[0];break;
                case 2:UC10 = Icon_Run[1];break;
                case 3:UC10 = Icon_Run[2];break;
            } 
            IconRun_Time = 0;
        }
        if(sys.Run_Status == 0)
            UC10 = 0xFC; 
        UC = UC10;   
        UCdata_Display(UC);  
        DIGdata_Set();
        DIG9_OFF;
        DIG10_ON;
    }
    if(t == 11)//ˢ��
    {
        DIGdata_Set();
        DIG9_OFF;
        DIG10_OFF;
        t = 0;
    }
}

/*
*****************************************************************
 * ����ԭ�ͣ�void Deal_Speed(void)
 * ��    �ܣ��ٶ���ʾ����
*****************************************************************
*/
void Deal_Speed(void)
{
    /**********SpeedL1_ADD_Mode**********/
    if(sys.Run_Status == 1)//�����������
    {
        if(Speed_ADDMode == 0)//�ڵ�������У��ٶ�δ����
        {
			Display_Speed = Speed;
			if((Rel_Speed/Tooth_Ratio) < Ctrl_Speed)
			{
				Speed_ADDMode = 1;//�������ģʽ��
			}
			else
			{
				Speed_ADDMode = 2;//�������ģʽ��
			}
        }
        if(Speed_ADDMode==1)//�ڽ������ģʽ��
        { 
            if(Display_Speed<(Rel_Speed/Tooth_Ratio))
				Display_Speed++;
			if(sys.Motor_Stop == 0)
			{
				if((Rel_Speed/Tooth_Ratio) >= Ctrl_Speed)//ʵ���ٶȴ��ڵ��ڿ����ٶ�
				{
					Speed_ADDMode = 3;//�����ȶ�ģʽ
				}
			}			
        }
		else if(Speed_ADDMode == 2)//�ٶ��½�ģʽ��
        {
            if(Display_Speed>(Rel_Speed/Tooth_Ratio))
				Display_Speed--;
			if(sys.Motor_Stop == 0)
			{
				if(!sys.Motor_Stop && (Rel_Speed/Tooth_Ratio) <= Ctrl_Speed)//ʵ���ٶ�С�ڵ��ڿ����ٶ�
				{
					Speed_ADDMode = 3;//�ȶ�ģʽ
				}
			}
        }
        else if(Speed_ADDMode == 3)//�ٶ��ȶ�ģʽ��
        {
            Display_Speed = Ctrl_Speed;//��ʾ�����ٶ�
        }
	}
	else
	{
		Speed_ADDMode = 0;
	}
}

/*
*****************************************************************
 * ����ԭ�ͣ� void Display_Show(void)
 * ��    �ܣ� ��ʾ��Ļ
*****************************************************************
*/
void Display_Show(void)
{

	t++;
	if(sys.Run_Status == 0)
	{
		Display_Speed = Set_Speed;
		Display_Time = Set_Time;
	}
	else
	{
		if(EC11A[0].EC11A_Knob > 0)
		{
			Display_Speed = Set_Speed;
		}
		else
		{
			Deal_Speed();
		}    
		Display_Time = Ctrl_Time + 59;//��ʾʱ���1����
		
	}
	Display_SpeedShow(Display_Speed);
	Display_TimeShow(Display_Time);
	Display_Icon();
}
