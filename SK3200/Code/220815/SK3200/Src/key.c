#include "key.h"
#include "user.h"

uint16_t cur=400;//�������ӿ�Ӽ��ٶ� cur=8ms
uint16_t Scan_Status=0;//���ټӼ���־
uint8_t KEY1_Pin_ON=0;//������־
uint8_t LOCK_Status=0;//��ȫ����־ 1������ 0������
uint8_t Run_Status=0;//����״̬ 1��run     0��stop 2:����
uint8_t Wise_Status=0;//���ת������ 0��˳ʱ�� 1����ʱ��
uint8_t Start_Time=0;//
extern int set_time;
uint8_t wise_task=0;
uint8_t LOCK_time=0;
uint16_t save_speed;
extern int sumError1;
extern uint16_t rel_speed;//ʵʱ�ٶ�
extern uint8_t ADD_Mode;//��ʾ����ģʽ
extern uint16_t	dis_speed_N;
extern uint16_t	dis_speed_F;
extern uint16_t Stop_PWM;
extern uint16_t set_speed;//�趨�ٶ�
extern int rel_time;//ʵʱʱ��
extern uint16_t save_time;
extern uint8_t time_disable;//�رռ�ʱ
uint8_t lock_beep;
/*******************************************************************************
* ��   ��: Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
* ��   ��: ����ɨ��
* ��   ��: PIO_TypeDef* GPIOx,uint16_t GPIO_Pin
* �� ��ֵ: KEY_ON/KEY_OFF
*
* �޸���ʷ:
* �Ķ�ԭ��
*   ----------------------------------------------------
*******************************************************************************/
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{                        


			 
        if(HAL_GPIO_ReadPin (GPIOx,GPIO_Pin) == 0 )  
        {

					       uint32_t cur_time = HAL_GetTick();
	               static uint32_t start_time = 0;
//                 if(start_time == 0)
//								 start_time = cur_time;
								 
								 
									 if(cur_time - start_time < cur)
									 return KEY_OFF;

                 if(HAL_GPIO_ReadPin (GPIOx,GPIO_Pin) == 0)   
								 {
		                 
					           Scan_Status++;
									   //if(Scan_Status>3)
											 //cur=8;
										 start_time = cur_time;		
										 return         KEY_ON; 
								 	
								 }	

        }
        else
				{
			  
					if((HAL_GPIO_ReadPin (GPIOB,KEY2_Pin) ==1)&&(HAL_GPIO_ReadPin (GPIOB,KEY3_Pin) ==1 ) )
					{
						   if(HAL_GPIO_ReadPin (GPIOB,KEY1_Pin) ==1)
							 {
								 KEY1_Pin_ON=0;
							 }
							Scan_Status=0;
							cur=400;
						  return         KEY_OFF;
					}			
				}
				return         KEY_OFF;
}

/*******************************************************************************
* ��   ��: Key_Handle(void)
* ��   ��: ��������
* ��   ��: PIO_TypeDef* GPIOx,uint16_t GPIO_Pin
* �� ��ֵ: 
*
* �޸���ʷ:
* �Ķ�ԭ��
*   ----------------------------------------------------
*******************************************************************************/

void Key_Handle(void)
{
	     if(Run_Status==2)
       return;
         
	
			  if ( (Key_Scan(GPIOB,KEY5_Pin) == KEY_ON))//��ʼֹͣ����
				{  
					if (LOCK_Status)
		      return ;
					if(Run_Status==0)
					{
						 if(Wise_Status ==0)	
            HAL_GPIO_WritePin(GPIOA, CW_Pin, GPIO_PIN_RESET);	
					 else if(Wise_Status==1)
						 HAL_GPIO_WritePin(GPIOA, CW_Pin, GPIO_PIN_SET);	
						Run_Status =1;
					 if(rel_time==0)
					 {
						 rel_time=set_time-1;
					 }
							ADD_Mode=1;
					 
						HAL_GPIO_WritePin(MO_GPIO_Port, MO_Pin, GPIO_PIN_SET);//���kai
							 Start_Time=1;//
					 
						 sumError1=0x20000;
					    save_speed=set_speed;
					    save_time=rel_time;
					 beep();
					}
					else if(Run_Status==1)
					{
						Run_Status =2;
							ADD_Mode=0;
						save_speed=set_speed;
						set_speed=0;
						beep();
   
					}
				
				}
				
//				if(( Key_Scan(GPIOB,KEY1_Pin) == KEY_ON))//������
//				{
//					 if(LOCK_time==0)
//					 {
//						 if(LOCK_Status==0)
//						 beep();
//					    LOCK_Status=1;//����
//					  	 //lock_beep=1;
//						   
//						 LOCK_time=50;
//					 }
//					 KEY1_Pin_ON++;
//					 if(KEY1_Pin_ON>3)
//				   {
//						 beep();
//						 LOCK_Status=0;//��������				 
//						 KEY1_Pin_ON=0;
//						  LOCK_time=50;
//							
//				   }
//			  }

				
				
			  if ( (Key_Scan(GPIOB,KEY4_Pin) == KEY_ON))//����ת����
				{  
//					if (LOCK_Status)
//		          	 return ;
//					if(Run_Status ==1)
//					{
//							if(Wise_Status)
//							{
//								Wise_Status =0;//˳ʱ��
//								beep();
//								wise_task=1;
//								Run_Status =2;
//								ADD_Mode=0;
//								save_speed=set_speed;
//								set_speed=0;
//							}	
//							else
//							{
//								//HAL_GPIO_WritePin(GPIOA, CW_Pin, GPIO_PIN_SET);
//								Wise_Status =1;//��ʱ��
//								wise_task=2;
//								Run_Status =2;
//								ADD_Mode=0;
//								save_speed=set_speed;
//								set_speed=0;
//								beep();
//							}
//				}
//					else if(Run_Status ==0)
//					{
//								if(Wise_Status)
//							{
//								Wise_Status =0;//˳ʱ��
//								HAL_GPIO_WritePin(GPIOA, CW_Pin, GPIO_PIN_SET);
//								beep();

//							}	
//							else
//							{
//								HAL_GPIO_WritePin(GPIOA, CW_Pin, GPIO_PIN_RESET);
//								Wise_Status =1;//��ʱ��
//								beep();

//							}
//						
//						
//					}
//					
				}
				
				


			
}


