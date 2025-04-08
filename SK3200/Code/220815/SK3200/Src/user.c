#include "user.h"
#include "tim.h"
extern uint16_t rel_speed;//实时速度
extern uint16_t rel_time;//实时时间
extern uint16_t set_speed;//设定速度
extern uint16_t set_time;//设定时间
extern uint8_t Run_Status;//
extern uint8_t Start_Time;//
extern uint8_t ADD_Mode;//显示增减模式
uint16_t Set_PWM;
uint16_t Stop_PWM=0;
uint16_t BEEP_Count;
extern uint8_t time_disable;//关闭计时
void Sys_Init(void)
{
	PID_init();
	HAL_GPIO_WritePin(LED_ADJ_GPIO_Port, LED_ADJ_Pin, GPIO_PIN_RESET);//开背光源
  rel_speed=0;
	//rel_time=599;
	rel_time=000;
	set_speed=0;
	//set_time=600;
	set_time=000;
	Run_Status=0;
	set_speed=20;
	 ADD_Mode=3;
	time_disable=1;
}
  void PWM_Set(void)
	{
		
		 if(Run_Status==1)
		 { 
			  PID1(); 
			 	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,Set_PWM-2);//pwm 0—400
		 }
		 else if(Run_Status==2)
			  __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,Set_PWM);
		 else
				__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,Stop_PWM);//pwm 0—400 
	}
	
	
	void beep(void)
	{
		HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_SET);
		BEEP_Count=10;
	}
struct _pid{      

	float Kp,Ki,Kd; //定义比例、积分、微分系数
}pid;
void PID_init(){

	pid.Kp=0.06;//0.06;//0.02;//0.6;//3.8
	pid.Ki=0.000645;//0.0007;//0.0004;//0.015
	pid.Kd=0.00023;//0.0003;//0.02
}


int sumError1;
int lastError1;
int B;
unsigned int PID1()
{
  int dError=0,Error1=0;
   // if((L1_Rel<2000)&&(L1_Rel>100))
   Error1=set_speed-rel_speed;//当前误差
   sumError1=Error1+sumError1;//误差和
	  //if(sumError1>3000) sumError1=3000;
   dError=Error1-lastError1;//误差偏差
   lastError1=Error1;
   B=pid.Kp*Error1+pid.Ki*sumError1+pid.Kd*dError;
        
	      if(B<2)
				Set_PWM=2;
				else if(B>200)
				Set_PWM=200;
        else Set_PWM=B;

         return(0);
}
