#include "led.h"


extern uint16_t rel_speed;//实际速度
uint16_t set_speed;//设定速度
uint16_t dis_speed;//显示速度
extern uint8_t ADD_Mode;
extern uint8_t RUN_Status;
extern uint8_t Set_Dis;
uint16_t	dis_speed_N;
uint16_t	dis_speed_F;
extern uint16_t dis_flag;
void display(void)
{

	if(dis_flag==0)
	{
	//dis_speed=rel_speed ;
		if(RUN_Status==0)
		{
			dis_speed=set_speed;
		}
		else
		{
			if(ADD_Mode==3)
				dis_speed=set_speed;
			else
			{
				dis_speed_N=rel_speed;
				if(ADD_Mode==1)
				{
					if(dis_speed_N>dis_speed_F)
				   dis_speed=dis_speed_N;
					else
					{
						dis_speed=dis_speed_F;
						dis_speed_N=dis_speed_F;
					}
				}
				
				if(ADD_Mode==0)
				{
					if(dis_speed_N<dis_speed_F)
				   dis_speed=dis_speed_N;
					else
					{
						dis_speed=dis_speed_F;
						dis_speed_N=dis_speed_F;
					}
				}
				
				
				
				dis_speed_F=dis_speed_N;

			}
    }
		if(Set_Dis)
			dis_speed=set_speed;
		
	if (dis_speed < 9999)
	{ 
		
		int i;
		int s;	
		s = dis_speed;
		i=0;
		for (i=0;i<4;i++)
		{
			
			HAL_GPIO_WritePin(GPIOB, dig4_Pin|dig3_Pin|dig2_Pin|dig1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, G_Pin|C_Pin|D_Pin|E_Pin|F_Pin|A_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_RESET);
			
			switch (i)
			{
					case 0:
						HAL_GPIO_WritePin(GPIOB, dig4_Pin, GPIO_PIN_SET);
						break;
					case 1:
						HAL_GPIO_WritePin(GPIOB, dig3_Pin, GPIO_PIN_SET);
						break;
					case 2:
						HAL_GPIO_WritePin(GPIOB, dig2_Pin, GPIO_PIN_SET);
						break;
					case 3:
						HAL_GPIO_WritePin(GPIOB, dig1_Pin, GPIO_PIN_SET);
						break;
       }
		
			switch (s % 10)
			{
				case 0:
					HAL_GPIO_WritePin(GPIOB, G_Pin, GPIO_PIN_SET); 
					break;
				case 1:
					HAL_GPIO_WritePin(GPIOB, G_Pin|D_Pin|E_Pin|F_Pin|A_Pin, GPIO_PIN_SET);
					break;
				case 2:
					HAL_GPIO_WritePin(GPIOB, C_Pin|F_Pin, GPIO_PIN_SET);
					break;
				case 3:
					HAL_GPIO_WritePin(GPIOB, E_Pin|F_Pin, GPIO_PIN_SET);
					break;
				case 4:
					HAL_GPIO_WritePin(GPIOB, A_Pin|E_Pin|D_Pin, GPIO_PIN_SET);
					break;
				case 5:
					HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);
				  HAL_GPIO_WritePin(GPIOB, E_Pin, GPIO_PIN_SET);
					break;
				case 6:
					HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);
					break;
				case 7:
					HAL_GPIO_WritePin(GPIOB, G_Pin|D_Pin|E_Pin|F_Pin, GPIO_PIN_SET);
					break;
				case 8:
					
					break;
				case 9:
					HAL_GPIO_WritePin(GPIOB, E_Pin, GPIO_PIN_SET);
					break;
			}	
			s = s / 10;
			HAL_Delay (1);
			if (s==0)
				break;

		}
	}
}
	else
	{
		  HAL_GPIO_WritePin(GPIOB, dig4_Pin|dig3_Pin|dig2_Pin|dig1_Pin, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(GPIOB, G_Pin|C_Pin|D_Pin|E_Pin|F_Pin|A_Pin, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_RESET);
		
	}
}


