#include "Drv_ArrayVisuali.h"

/**********�ṹ��************/
_Array_ Temp_Array;

/*
*****************************************************************
 * ����ԭ�ͣ�void Array_Check(float dT)
 * ��    �ܣ�������
*****************************************************************
*/
void Array_Check(float dT)
{
    if(sys.Run_Status && Temp.Ctrl)
    {
        if(Temp_Array.Index < Array_Size)
        {
            Temp_Array.A[Temp_Array.Index] = Temp.Rel;
            Temp_Array.Index++;
            if(Temp_Array.Index == Array_Size)Temp_Array.Index = 0;
        }
    }
}
