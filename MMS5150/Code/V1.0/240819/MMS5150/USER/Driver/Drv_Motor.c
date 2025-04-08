#include "Drv_Motor.h"

/**********全局变量声明*******/
uint16_t Motor_PWM[15];
uint16_t Time_Val;

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
    HAL_TIM_Base_Start_IT(&htim6);//开始定时器
    Motor_AllOFF();
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM1)
    {
        Time_Val++;
    
        if(Time_Val >= 200)
            Time_Val = 0;
    }
    if(htim->Instance==TIM6)
    {
        if(Time_Val > Motor_PWM[0])
        {
            HAL_GPIO_WritePin(PWM1_GPIO_Port, PWM1_Pin, GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(PWM1_GPIO_Port, PWM1_Pin, GPIO_PIN_SET);
        }
        if(Time_Val > Motor_PWM[1])
        {
            HAL_GPIO_WritePin(PWM2_GPIO_Port, PWM2_Pin, GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(PWM2_GPIO_Port, PWM2_Pin, GPIO_PIN_SET);
        }
        if(Time_Val > Motor_PWM[2])
        {
            HAL_GPIO_WritePin(PWM11_GPIO_Port, PWM11_Pin, GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(PWM11_GPIO_Port, PWM11_Pin, GPIO_PIN_SET);
        }
        if(Time_Val > Motor_PWM[3])
        {
            HAL_GPIO_WritePin(PWM3_GPIO_Port, PWM3_Pin, GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(PWM3_GPIO_Port, PWM3_Pin, GPIO_PIN_SET);
        }
        if(Time_Val > Motor_PWM[4])
        {
            HAL_GPIO_WritePin(PWM4_GPIO_Port, PWM4_Pin, GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(PWM4_GPIO_Port, PWM4_Pin, GPIO_PIN_SET);
        }
        if(Time_Val > Motor_PWM[5])
        {
            HAL_GPIO_WritePin(PWM12_GPIO_Port, PWM12_Pin, GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(PWM12_GPIO_Port, PWM12_Pin, GPIO_PIN_SET);
        }
        if(Time_Val > Motor_PWM[6])
        {
            HAL_GPIO_WritePin(PWM5_GPIO_Port, PWM5_Pin, GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(PWM5_GPIO_Port, PWM5_Pin, GPIO_PIN_SET);
        }
        if(Time_Val > Motor_PWM[7])
        {
            HAL_GPIO_WritePin(PWM6_GPIO_Port, PWM6_Pin, GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(PWM6_GPIO_Port, PWM6_Pin, GPIO_PIN_SET);
        }
        if(Time_Val > Motor_PWM[8])
        {
            HAL_GPIO_WritePin(PWM13_GPIO_Port, PWM13_Pin, GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(PWM13_GPIO_Port, PWM13_Pin, GPIO_PIN_SET);
        }
        if(Time_Val > Motor_PWM[9])
        {
            HAL_GPIO_WritePin(PWM7_GPIO_Port, PWM7_Pin, GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(PWM7_GPIO_Port, PWM7_Pin, GPIO_PIN_SET);
        }
        if(Time_Val > Motor_PWM[10])
        {
            HAL_GPIO_WritePin(PWM8_GPIO_Port, PWM8_Pin, GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(PWM8_GPIO_Port, PWM8_Pin, GPIO_PIN_SET);
        }
        if(Time_Val > Motor_PWM[11])
        {
            HAL_GPIO_WritePin(PWM14_GPIO_Port, PWM14_Pin, GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(PWM14_GPIO_Port, PWM14_Pin, GPIO_PIN_SET);
        }
        if(Time_Val > Motor_PWM[12])
        {
            HAL_GPIO_WritePin(PWM9_GPIO_Port, PWM9_Pin, GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(PWM9_GPIO_Port, PWM9_Pin, GPIO_PIN_SET);
        }
        if(Time_Val > Motor_PWM[13])
        {
            HAL_GPIO_WritePin(PWM10_GPIO_Port, PWM10_Pin, GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(PWM10_GPIO_Port, PWM10_Pin, GPIO_PIN_SET);
        }
        if(Time_Val > Motor_PWM[14])
        {
            HAL_GPIO_WritePin(PWM15_GPIO_Port, PWM15_Pin, GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(PWM15_GPIO_Port, PWM15_Pin, GPIO_PIN_SET);
        }
    }
}
