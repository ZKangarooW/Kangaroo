#include "user.h"
#include "tim.h"


/*
2022-08.31：旋钮左右反了，初始化转速1800，最高350-1800
*/
extern uint16_t set_speed;//设定速度
extern uint16_t rel_speed;
uint16_t PWM_Speed;
uint8_t RUN_Status;
uint8_t Start_Time;
uint8_t Stable_Mode;
extern uint8_t ADD_Mode;


void sys_init(void)
{
	PWM_Speed=0;
	RUN_Status=0;
	Start_Time=0;
	set_speed=1800;
	rel_speed =0;
	PID_init();
  ADD_Mode=3;
}

void beep(void)
{
	
	
}

void PWM_Set(void)
	{
		 if(RUN_Status)
		 {
      HAL_GPIO_WritePin(MO_GPIO_Port, MO_Pin, GPIO_PIN_SET);
			  
			 if(Start_Time)
			 {
				  
				 if(set_speed)
				 __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,45);
			 }
			 else
			 {
				     if(set_speed)
						 {
								 PID1();
								 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,PWM_Speed);
						 }
			 }
		}
		 else
		 {
			 __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,0);
			 HAL_GPIO_WritePin(MO_GPIO_Port, MO_Pin, GPIO_PIN_RESET);
		 }
 }
		





struct _pid{      

	float Kp,Ki,Kd; //定义比例、积分、微分系数
}pid;

void PID_init(){

	pid.Kp=0.035;//0.6;//3.8
	pid.Ki=0.00066;//0.00088;//0.015
	pid.Kd=0.00045;//0.02
}

int sumError1;
int lastError1;

unsigned int PID1()
{  

  int dError=0,Error1=0,B;
   
   Error1=set_speed-rel_speed;//当前误差
   sumError1=Error1+sumError1;//误差和
   dError=Error1-lastError1;//误差偏差
   lastError1=Error1;
   B=pid.Kp*Error1+pid.Ki*sumError1+pid.Kd*dError;
        

        if(B<22) B=22;
	      if(B>0&&B<2500)
        PWM_Speed=B;
        return(0);
}