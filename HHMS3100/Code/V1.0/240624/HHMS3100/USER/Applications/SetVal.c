#include "SetVal.h"

/**********ȫ�ֱ�������******/
uint8_t SetOK_Flag;//����Ƿ񲨶���ť�����ñ�־λ

/*
*****************************************************************
 * ����ԭ�ͣ� void Check_Set(void)
 * ��    �ܣ� �������
*****************************************************************
*/
void Check_Set(void)
{
    if(EC11A[1].EC11A_Knob > 0)
    {
        SetOK_Flag = 1;//��⵽������ť���ȴ��˳�����ģʽ
    }
    if(SetOK_Flag == 1)
    {
        if(sys.SetMode_Option == 0 && Twinkle_Time == 0)//���趨�ú�
        {     
            
            SetOK_Flag = 0;
        } 
    }
}

