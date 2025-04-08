#include "key.h"
#include "user.h"

uint16_t cur=400;//连续按加快加减速度 cur=8ms
uint16_t Scan_Status=0;//快速加减标志
uint8_t KEY1_Pin_ON=0;//长按标志
uint8_t LOCK_Status=0;//安全锁标志 1：锁定 0：解锁
uint8_t Run_Status=0;//运行状态 1：run     0：stop 2:减速
uint8_t Wise_Status=0;//电机转动方向 0：顺时针 1：逆时针
uint8_t Start_Time=0;//
extern int set_time;
uint8_t wise_task=0;
uint8_t LOCK_time=0;
uint16_t save_speed;
extern int sumError1;
extern uint16_t rel_speed;//实时速度
extern uint8_t ADD_Mode;//显示增减模式
extern uint16_t	dis_speed_N;
extern uint16_t	dis_speed_F;
extern uint16_t Stop_PWM;
extern uint16_t set_speed;//设定速度
extern int rel_time;//实时时间
extern uint16_t save_time;
extern uint8_t time_disable;//关闭计时
uint8_t lock_beep;
/*******************************************************************************
* 名   称: Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
* 功   能: 按键扫描
* 参   数: PIO_TypeDef* GPIOx,uint16_t GPIO_Pin
* 返 回值: KEY_ON/KEY_OFF
*
* 修改历史:
* 改动原因：
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
* 名   称: Key_Handle(void)
* 功   能: 按键处理
* 参   数: PIO_TypeDef* GPIOx,uint16_t GPIO_Pin
* 返 回值: 
*
* 修改历史:
* 改动原因：
*   ----------------------------------------------------
*******************************************************************************/

void Key_Handle(void)
{
	     if(Run_Status==2)
       return;
         
	
			  if ( (Key_Scan(GPIOB,KEY5_Pin) == KEY_ON))//开始停止按键
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
					 
						HAL_GPIO_WritePin(MO_GPIO_Port, MO_Pin, GPIO_PIN_SET);//电机kai
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
				
//				if(( Key_Scan(GPIOB,KEY1_Pin) == KEY_ON))//锁定键
//				{
//					 if(LOCK_time==0)
//					 {
//						 if(LOCK_Status==0)
//						 beep();
//					    LOCK_Status=1;//锁定
//					  	 //lock_beep=1;
//						   
//						 LOCK_time=50;
//					 }
//					 KEY1_Pin_ON++;
//					 if(KEY1_Pin_ON>3)
//				   {
//						 beep();
//						 LOCK_Status=0;//长按解锁				 
//						 KEY1_Pin_ON=0;
//						  LOCK_time=50;
//							
//				   }
//			  }

				
				
			  if ( (Key_Scan(GPIOB,KEY4_Pin) == KEY_ON))//正反转按键
				{  
//					if (LOCK_Status)
//		          	 return ;
//					if(Run_Status ==1)
//					{
//							if(Wise_Status)
//							{
//								Wise_Status =0;//顺时针
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
//								Wise_Status =1;//逆时针
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
//								Wise_Status =0;//顺时针
//								HAL_GPIO_WritePin(GPIOA, CW_Pin, GPIO_PIN_SET);
//								beep();

//							}	
//							else
//							{
//								HAL_GPIO_WritePin(GPIOA, CW_Pin, GPIO_PIN_RESET);
//								Wise_Status =1;//逆时针
//								beep();

//							}
//						
//						
//					}
//					
				}
				
				


			
}


