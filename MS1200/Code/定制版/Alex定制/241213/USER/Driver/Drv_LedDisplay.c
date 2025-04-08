#include "Drv_LedDisplay.h"

/*
*****************************************************************
 * 函数原型：void UCdata_Display(uint8_t uc)
 * 功    能：UC数据判断控制引脚 
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
                case 0: HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_RESET);break;
                case 1: HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_RESET);break;
                case 2: HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_RESET);break;
                case 3: HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_RESET);break;
                case 4: HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_RESET);break;
                case 5: HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_RESET);break;
                case 6: HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_RESET);break;
            }      
        }
        else
        {
            switch(i)
            {           
                case 0: HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, GPIO_PIN_SET);break;
                case 1: HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, GPIO_PIN_SET);break;
                case 2: HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, GPIO_PIN_SET);break;
                case 3: HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_SET);break;
                case 4: HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, GPIO_PIN_SET);break;
                case 5: HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, GPIO_PIN_SET);break;
                case 6: HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, GPIO_PIN_SET);break;
            }
        }
    } 
}

/*
*****************************************************************
 * 函数原型：void DIGdata_Display(uint8_t DIG)
 * 功    能：DIG数据判断控制引脚 
*****************************************************************
*/
void DIGdata_Display(uint8_t DIG)
{
	for(uint8_t i=0; i<4; i++)
    {
        if((DIG<<i) & 0x80)
        {
            switch(i)
            {           
                case 0: HAL_GPIO_WritePin(DIG1_GPIO_Port, DIG1_Pin, GPIO_PIN_SET);break;
                case 1: HAL_GPIO_WritePin(DIG2_GPIO_Port, DIG2_Pin, GPIO_PIN_SET);break;
                case 2: HAL_GPIO_WritePin(DIG3_GPIO_Port, DIG3_Pin, GPIO_PIN_SET);break;
                case 3: HAL_GPIO_WritePin(DIG4_GPIO_Port, DIG4_Pin, GPIO_PIN_SET);break;
            }      
        }
        else
        {
            switch(i)
            {           
                case 0: HAL_GPIO_WritePin(DIG1_GPIO_Port, DIG1_Pin, GPIO_PIN_RESET);break;
                case 1: HAL_GPIO_WritePin(DIG2_GPIO_Port, DIG2_Pin, GPIO_PIN_RESET);break;
                case 2: HAL_GPIO_WritePin(DIG3_GPIO_Port, DIG3_Pin, GPIO_PIN_RESET);break;
                case 3: HAL_GPIO_WritePin(DIG4_GPIO_Port, DIG4_Pin, GPIO_PIN_RESET);break;
            }
        }
    } 
}

/*
*****************************************************************
 * 函数原型：void DIGdata_Set(void)
 * 功    能：1-4DIG引脚全部拉高
*****************************************************************
*/
void DIGdata_Set(void)
{
    HAL_GPIO_WritePin(DIG1_GPIO_Port, DIG1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DIG2_GPIO_Port, DIG2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DIG3_GPIO_Port, DIG3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DIG4_GPIO_Port, DIG4_Pin, GPIO_PIN_RESET);
}
