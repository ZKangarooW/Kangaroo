#include "Drv_ArrayVisuali.h"

/**********结构体************/
_Array_ Temp_Array;

/*
*****************************************************************
 * 函数原型：void Array_Check(float dT)
 * 功    能：数组检测
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
