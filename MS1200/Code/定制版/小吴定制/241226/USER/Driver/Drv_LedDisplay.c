#include "Drv_LedDisplay.h"

/*
*****************************************************************
 * ����ԭ�ͣ�void UCdata_Display(uint8_t uc)
 * ��    �ܣ�UC�����жϿ������� 
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
 * ����ԭ�ͣ�void DIGdata_Display(uint8_t DIG)
 * ��    �ܣ�DIG�����жϿ������� 
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
 * ����ԭ�ͣ�void DIGdata_Set(void)
 * ��    �ܣ�1-4DIG����ȫ������
*****************************************************************
*/
void DIGdata_Set(void)
{
    HAL_GPIO_WritePin(DIG1_GPIO_Port, DIG1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DIG2_GPIO_Port, DIG2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DIG3_GPIO_Port, DIG3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DIG4_GPIO_Port, DIG4_Pin, GPIO_PIN_RESET);
}
