#include "Drv_Motor.h"

/**********全局变量声明*******/
uint16_t Motor_PWM[15];
uint16_t Time_Val[15];

void Motor_AllON()
{
    MO1_ON; 
    MO2_ON; 
    MO3_ON; 
    MO4_ON; 
    MO5_ON; 
    MO6_ON; 
    MO7_ON; 
    MO8_ON; 
    MO9_ON; 
    MO10_ON;
    MO11_ON;
    MO12_ON;
    MO13_ON;
    MO14_ON;
    MO15_ON;
}

void Motor_AllOFF()
{
    MO1_OFF; 
    MO2_OFF; 
    MO3_OFF; 
    MO4_OFF; 
    MO5_OFF; 
    MO6_OFF; 
    MO7_OFF; 
    MO8_OFF; 
    MO9_OFF; 
    MO10_OFF;
    MO11_OFF;
    MO12_OFF;
    MO13_OFF;
    MO14_OFF;
    MO15_OFF;
}

/**
 * @brief 电机初始化
 *
 */
void Drv_Motor_Init(void)
{
    HAL_TIM_Base_Start_IT(&htim1);//开始定时器
    Motor_AllON();
}

void Pwm_Switch(uint8_t i,uint8_t val)
{
    if(i == 0)
    {
        switch(val)
        {
            case 0:
                HAL_GPIO_WritePin(PWM1_GPIO_Port, PWM1_Pin, GPIO_PIN_RESET);
            break;
            case 1:
                HAL_GPIO_WritePin(PWM2_GPIO_Port, PWM2_Pin, GPIO_PIN_RESET);
            break;
            case 2:
                HAL_GPIO_WritePin(PWM3_GPIO_Port, PWM3_Pin, GPIO_PIN_RESET);
            break;
            case 3:
                HAL_GPIO_WritePin(PWM4_GPIO_Port, PWM4_Pin, GPIO_PIN_RESET);
            break;
            case 4:
                HAL_GPIO_WritePin(PWM5_GPIO_Port, PWM5_Pin, GPIO_PIN_RESET);
            break;
            case 5:
                HAL_GPIO_WritePin(PWM6_GPIO_Port, PWM6_Pin, GPIO_PIN_RESET);
            break;
            case 6:
                HAL_GPIO_WritePin(PWM7_GPIO_Port, PWM7_Pin, GPIO_PIN_RESET);
            break;
            case 7:
                HAL_GPIO_WritePin(PWM8_GPIO_Port, PWM8_Pin, GPIO_PIN_RESET);
            break;
            case 8:
                HAL_GPIO_WritePin(PWM9_GPIO_Port, PWM9_Pin, GPIO_PIN_RESET);
            break;
            case 9:
                HAL_GPIO_WritePin(PWM10_GPIO_Port, PWM10_Pin, GPIO_PIN_RESET);
            break;
            case 10:
                HAL_GPIO_WritePin(PWM11_GPIO_Port, PWM11_Pin, GPIO_PIN_RESET);
            break;
            case 11:
                HAL_GPIO_WritePin(PWM12_GPIO_Port, PWM12_Pin, GPIO_PIN_RESET);
            break;
            case 12:
                HAL_GPIO_WritePin(PWM13_GPIO_Port, PWM13_Pin, GPIO_PIN_RESET);
            break;
            case 13:
                HAL_GPIO_WritePin(PWM14_GPIO_Port, PWM14_Pin, GPIO_PIN_RESET);
            break;
            case 14:
                HAL_GPIO_WritePin(PWM15_GPIO_Port, PWM15_Pin, GPIO_PIN_RESET);
            break;
        }
    }
    else
    {
        switch(val)
        {
            case 0:
                HAL_GPIO_WritePin(PWM1_GPIO_Port, PWM1_Pin, GPIO_PIN_SET);
            break;
            case 1:
                HAL_GPIO_WritePin(PWM2_GPIO_Port, PWM2_Pin, GPIO_PIN_SET);
            break;
            case 2:
                HAL_GPIO_WritePin(PWM3_GPIO_Port, PWM3_Pin, GPIO_PIN_SET);
            break;
            case 3:
                HAL_GPIO_WritePin(PWM4_GPIO_Port, PWM4_Pin, GPIO_PIN_SET);
            break;
            case 4:
                HAL_GPIO_WritePin(PWM5_GPIO_Port, PWM5_Pin, GPIO_PIN_SET);
            break;
            case 5:
                HAL_GPIO_WritePin(PWM6_GPIO_Port, PWM6_Pin, GPIO_PIN_SET);
            break;
            case 6:
                HAL_GPIO_WritePin(PWM7_GPIO_Port, PWM7_Pin, GPIO_PIN_SET);
            break;
            case 7:
                HAL_GPIO_WritePin(PWM8_GPIO_Port, PWM8_Pin, GPIO_PIN_SET);
            break;
            case 8:
                HAL_GPIO_WritePin(PWM9_GPIO_Port, PWM9_Pin, GPIO_PIN_SET);
            break;
            case 9:
                HAL_GPIO_WritePin(PWM10_GPIO_Port, PWM10_Pin, GPIO_PIN_SET);
            break;
            case 10:
                HAL_GPIO_WritePin(PWM11_GPIO_Port, PWM11_Pin, GPIO_PIN_SET);
            break;
            case 11:
                HAL_GPIO_WritePin(PWM12_GPIO_Port, PWM12_Pin, GPIO_PIN_SET);
            break;
            case 12:
                HAL_GPIO_WritePin(PWM13_GPIO_Port, PWM13_Pin, GPIO_PIN_SET);
            break;
            case 13:
                HAL_GPIO_WritePin(PWM14_GPIO_Port, PWM14_Pin, GPIO_PIN_SET);
            break;
            case 14:
                HAL_GPIO_WritePin(PWM15_GPIO_Port, PWM15_Pin, GPIO_PIN_SET);
            break;
        }
    }
}

void PWM_ValSet(uint8_t i)
{
    Time_Val[i]++;
    
	if(Time_Val[i] > Motor_PWM[i])
	{
		Pwm_Switch(0,i);
	}
	else
	{
		Pwm_Switch(1,i);
	}
	
	if(Time_Val[i] >= 400)
		Time_Val[i] = 0;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    /**********Motor1**********/
    PWM_ValSet(0);
    
    /**********Motor2**********/
    PWM_ValSet(1);
    
    /**********Motor3**********/
    PWM_ValSet(2);
    
    /**********Motor4**********/
    PWM_ValSet(3);
    
    /**********Motor5**********/
    PWM_ValSet(4);
    
    /**********Motor6**********/
    PWM_ValSet(5);
    
    /**********Motor7**********/
    PWM_ValSet(6);
    
    /**********Motor8**********/
    PWM_ValSet(7);
    
    /**********Motor9**********/
    PWM_ValSet(8);
    
    /**********Motor10**********/
    PWM_ValSet(9);
    
    /**********Motor11**********/
    PWM_ValSet(10);
    
    /**********Motor12**********/
    PWM_ValSet(11);
    
    /**********Motor13**********/
    PWM_ValSet(12);
    
    /**********Motor14**********/
    PWM_ValSet(13);
    
    /**********Motor15**********/
    PWM_ValSet(14);
}
