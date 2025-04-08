#include "key.h"

uint16_t cur=200;
extern uint8_t RUN_Status;
uint16_t KEY_Delay;
extern uint16_t	dis_speed_N;
extern uint16_t	dis_speed_F;
uint16_t dis_blink=0;
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
					      
                 if( KEY_Delay)
									 return 0;
					       uint32_t cur_time = HAL_GetTick();
	               static uint32_t start_time1 = 0;
//                 if(start_time1 == 0)
//								 start_time1 = cur_time;
								 
								 
									 if(cur_time - start_time1 < cur)
									 return KEY_OFF;

                 if(HAL_GPIO_ReadPin (GPIOx,GPIO_Pin) == 0)   
								 {
		                 
										 start_time1 = cur_time;	
                     KEY_Delay=150;									 
										 return         KEY_ON; 
								 	
								 }	

        }
        else
				{
			  
					if((HAL_GPIO_ReadPin (GPIOB,KEY2_Pin) ==1)&&(HAL_GPIO_ReadPin (GPIOB,KEY2_Pin) ==1 ) )
					{

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
extern uint8_t Start_Time;
extern uint8_t ADD_Mode;
extern int sumError1;
extern  uint16_t dis_flag;
uint16_t beep_time;
void Key_Handle(void)
{
         
	
			  if ( (Key_Scan(GPIOB,KEY2_Pin) == KEY_ON))//开始停止按键
				{  
					    if(RUN_Status==0)
							{
								RUN_Status=1;
								Start_Time=2;
								sumError1=0xf000;
								ADD_Mode=1;
								dis_speed_N=0;
								dis_speed_F=0;
								dis_blink=0;
								dis_flag=0;
								  HAL_GPIO_WritePin(GPIOA, BEEP_Pin, GPIO_PIN_SET);
								beep_time=10;

							}
							else
							{
								RUN_Status=0;
							  ADD_Mode=0;
								dis_blink=1;
							  HAL_GPIO_WritePin(GPIOA, BEEP_Pin, GPIO_PIN_SET);
								beep_time=10;
							}
				
				}
				

			
}

