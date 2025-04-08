#include "Drv_LedDisplay.h"

/**********ȫ�ֱ�������******/
float Twinkle_Time;//��˸ʱ��
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
 * ����ԭ�ͣ� void Check_ShowFlag(float dT)
 * ��    �ܣ� ��˸���
 * ��    ��:  dT:ִ������
 * ��    ���� float dT
*****************************************************************
*/
void Check_ShowFlag(float dT)
{
    static float T,T1;
    if(sys.Run_Status)//����ʱ
    {
        if (T1 == 0)
        {
            TimeIcon_ShowFalg = ~TimeIcon_ShowFalg;
            Icon_ShowFlag = ~Icon_ShowFlag;
        }
        T1 += dT;
        if (T1 >= 0.5f)
        {
            T1 = 0;
        }
    }
    if(!sys.SetMode_Option)//���û������ѡ���У��򶼵���������˸
    {
        Speed_ShowFlag = 0;//����
        Time_ShowFlag = 0;//����
        Twinkle_Time = 0;//��˸��ʱ����
        return;
    }
    if(Twinkle_Time && Key_Status==0)//��˸��û�в�����ťʱ
    {
        if (T == 0)
        {
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
        }
        T += dT;
        if (T >= 0.5f)
        {
            Twinkle_Time -= 0.5f;
            if(Twinkle_Time <= 0)//�����˸����
                sys.SetMode_Option = 0;//ģʽѡ������   
            T = 0;    
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
            if(Speed_ShowFlag >= 1 && Key_Status == 0)//��˸�ٶ�
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
            if(Speed_ShowFlag >= 1 && Key_Status == 0)
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
            if(Speed_ShowFlag >= 1 && Key_Status == 0)
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
        if(Speed_ShowFlag >= 1 && Key_Status == 0)
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
        if(Time.Set <= 0)
            UCdata_Display(0x02);
        else            
            UCdata_Display(UC); 
        if(Time_ShowFlag >= 1 && Key_Status == 0)//ʱ����˸
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
        if(Time.Set <= 0)
            UCdata_Display(0x02);
        else
            UCdata_Display(UC);  
        if(Time_ShowFlag >= 1 && Key_Status == 0)
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
        if(Time.Set <= 0)
            UCdata_Display(0x02);
        else
            UCdata_Display(UC); 
        if(Time_ShowFlag >= 1 && Key_Status == 0)
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
        if(Time.Set <= 0)
            UCdata_Display(0x02);
        else
            UCdata_Display(UC);  
        if(Time_ShowFlag >= 1 && Key_Status == 0)
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
        if(TimeIcon_ShowFalg >= 1 && sys.Run_Status == 1 && Time.Set <= 0)//��˸
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
 * ����ԭ�ͣ� void Deal_Speed(void)
 * ��    �ܣ� �ٶ���ʾ����
*****************************************************************
*/
uint16_t Rel_Val;
void Deal_Speed(void)
{
    Rel_Val = Speed.Rel;
    /**********SpeedL1_ADD_Mode**********/
    if(sys.Run_Status == 1)//�����������
    {
        if(Speed.ADDMode == 0)//�ڵ�������У��ٶ�δ����
        {
            if(Speed.Ctrl > Rel_Val)//�����ٶȴ���ʵ���ٶ�
            {
                Speed.New =0;//���ڵ��ٶ�����
                Speed.Last = 0;//֮ǰ���ٶ�����
                Speed.ADDMode = 1;//�������ģʽ��
            }
            else if(Speed.Ctrl <= Rel_Val)//�����ٶ�С����ʾ�ٶ�
            {
                Speed.New=0;//���ڵ��ٶ�����
                Speed.Last = Rel_Val;//֮ǰ���ٶȵ��ڵ�ǰ��ʾ�ٶ�
                Speed.ADDMode = 2;//�������ģʽ��
            }
        }
        if(Speed.ADDMode==1)//�ڽ������ģʽ��
        { 
			if(Rel_Val >= Speed.Ctrl)//ʵ���ٶȴ��ڵ��ڿ����ٶ�
			{
				Speed.ADDMode = 3;//�����ȶ�ģʽ
				return;
			}
			Speed.New = Rel_Val;//��¼��ǰ�ٶ�
			if(Speed.New > Speed.Last)//��ǰ�ٶȴ�����һ���ٶ�
				Speed.Display = Speed.New;//��ʾ��ǰ�ٶ�
			else//��ǰ�ٶ�С����һ���ٶ�
			{
				Speed.Display = Speed.Last;//��ʾ��һ���ٶȣ������ٶ�С�ڵ�ǰ�ٶȡ����������ٶȵ�����
				Speed.New = Speed.Last;//����һ���ٶȸ�ֵ����ǰ�ٶ�
			}
			Speed.Last = Speed.New;//����ǰ�ٶȱ��� 				
        }
        else if(Speed.ADDMode == 2)//�ٶ��½�ģʽ��
        {
			if(Rel_Val <= Speed.Ctrl)//ʵ���ٶ�С�ڵ��ڿ����ٶ�
			{
				Speed.ADDMode = 3;//�ȶ�ģʽ
				return;
			}
			Speed.New = Rel_Val;//��¼��ǰ�ٶ�
			if(Speed.New < Speed.Last)//��ǰ�ٶ�С����һ���ٶ�
				Speed.Display = Speed.New;//��ʾ��ǰ�ٶ�
			else//��ǰ�ٶȴ�����һ���ٶ�
			{
				Speed.Display = Speed.Last;//��ʾ��һ���ٶȣ������ٶȴ��ڵ�ǰ�ٶȡ������½��ٶȵ�����
				Speed.New = Speed.Last;//����һ���ٶȸ�ֵ����ǰ�ٶ�
			}
			Speed.Last = Speed.New;//����ǰ�ٶȱ���
        }
        else if(Speed.ADDMode == 3)//�ٶ��ȶ�ģʽ��
        {
            Speed.Display = Speed.Ctrl;//��ʾ�����ٶ�
        }
		else if(Speed.ADDMode == 4)//�ٶ��½�ֹͣģʽ��
        {
            Speed.New = Rel_Val;//��¼��ǰ�ٶ�
            if(Speed.New < Speed.Last)//��ǰ�ٶ�С����һ���ٶ�
                Speed.Display = Speed.New;//��ʾ��ǰ�ٶ�
            else//��ǰ�ٶȴ�����һ���ٶ�
            {
                Speed.Display = Speed.Last;//��ʾ��һ���ٶȣ������ٶȴ��ڵ�ǰ�ٶȡ������½��ٶȵ�����
                Speed.New = Speed.Last;//����һ���ٶȸ�ֵ����ǰ�ٶ�
            }
            Speed.Last = Speed.New;//����ǰ�ٶȱ���
        }
    }
}


/*
*****************************************************************
 * ����ԭ�ͣ� void Display_Show(float dT)
 * ��    �ܣ� ��ʾ��Ļ
*****************************************************************
*/
void Display_Show(float dT)
{
	t++;
	if(sys.Run_Status == 0)
	{
		Speed.Display = Speed.Set;
		Time.Display = Time.Set;
	}
	else
	{
		if(sys.SetMode_Option == 1)//�������ٶ�ģʽ��
        {
            Speed.Display = Speed.Set;//��ʾ�趨�ٶ�
            Time.Display = Time.Rel+59;//��ʾʵ��ʱ��
        }
        else if(sys.SetMode_Option == 2)//������ʱ��ģʽ��
        {
            Deal_Speed();//�ٶ���ʾ����
            Time.Display = Time.Set;//��ʾ�趨ʱ�� 
        }            
        else//�ڲ�����ģʽ��
        {
            Deal_Speed();//�ٶ���ʾ���� 
            Time.Display = Time.Rel+59;//��ʾʵ��ʱ��
        }
	}
	Display_SpeedShow(Speed.Display);
	Display_TimeShow(Time.Display);
	Display_Icon();
}
